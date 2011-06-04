/*
GPL License and Copyright Notice ============================================
 This file is part of CBash.

 CBash is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 CBash is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with CBash; if not, write to the Free Software Foundation,
 Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

 CBash copyright (C) 2010 Waruddar
=============================================================================
*/
// Visitors.cpp
#include "Visitors.h"
#include "Oblivion/Records/MGEFRecord.h"

FormIDMasterUpdater::FormIDMasterUpdater(FormIDHandlerClass &_FormIDHandler):
    FormIDOp(),
    FormIDHandler(_FormIDHandler),
    ExpandedIndex(_FormIDHandler.ExpandedIndex),
    CollapsedIndex(_FormIDHandler.CollapsedIndex),
    ExpandTable(_FormIDHandler.ExpandTable),
    CollapseTable(_FormIDHandler.CollapseTable)
    {
    //
    }

FormIDMasterUpdater::~FormIDMasterUpdater()
    {
    //
    }

bool FormIDMasterUpdater::Accept(UINT32 &curFormID)
    {
    //If formID is not set, or the formID belongs to the engine, do nothing
    //Any formID whose objectID is less than END_HARDCODED_IDS is given the 00 modIndex by the engine regardless of what it actually is
    //I.e. the CS will complain of duplicate formIDs if a mod has both 0x00000042 and 0x01000042
    //In short, formIDs with an objectID < END_HARDCODED_IDS all collide. They don't use the modIndex.
    if((curFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        {
        curFormID &= 0x00FFFFFF;
        return stop;
        }

    UINT32 modIndex = curFormID >> 24;
    //printer("Checking %08X against %02X, %02X, %02X\n", curFormID, ExpandedIndex, CollapseTable[modIndex], CollapsedIndex);
    //If the formID belongs to the mod, or if the master is already present, do nothing
    if((modIndex == ExpandedIndex) || (CollapseTable[modIndex] != CollapsedIndex))
        return stop;

    //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
    if(modIndex >= FormIDHandler.LoadOrder255.size())
        {
        curFormID = (ExpandTable[CollapseTable[modIndex]] << 24) | (curFormID & 0x00FFFFFF);
        return stop;
        }
    FormIDHandler.AddMaster(FormIDHandler.LoadOrder255[modIndex]);
    ++count;
    return stop;
    }

bool FormIDMasterUpdater::AcceptMGEF(UINT32 &curMgefCode)
    {
    //If MgefCode is not set, do nothing
    if(curMgefCode == 0)
        return stop;

    UINT32 modIndex = curMgefCode & 0x000000FF;
    //If the MgefCode belongs to the mod, or if the master is already present, do nothing
    if((modIndex == ExpandedIndex) || (CollapseTable[modIndex] != CollapsedIndex))
        return stop;

    //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
    if(modIndex >= FormIDHandler.LoadOrder255.size())
        {
        curMgefCode = (ExpandTable[CollapseTable[modIndex]]) | (curMgefCode & 0xFFFFFF00);
        return stop;
        }

    FormIDHandler.AddMaster(FormIDHandler.LoadOrder255[modIndex]);
    ++count;
    return stop;
    }

FormIDMatchCounter::FormIDMatchCounter(const UINT32 &_FormIDToMatch):
    FormIDOp(),
    FormIDToMatch(_FormIDToMatch)
    {
    //
    }

FormIDMatchCounter::~FormIDMatchCounter()
    {
    //
    }

bool FormIDMatchCounter::Accept(UINT32 &curFormID)
    {
    if(curFormID == FormIDToMatch)
        ++count;
    return stop;
    }

bool FormIDMatchCounter::AcceptMGEF(UINT32 &curMgefCode)
    {
    if(curMgefCode == FormIDToMatch)
        ++count;
    return stop;
    }

RecordUnloader::RecordUnloader():
    RecordOp()
    {
    //
    }

RecordUnloader::~RecordUnloader()
    {
    //
    }

bool RecordUnloader::Accept(Record *&curRecord)
    {
    if(!curRecord->IsChanged())
        {
        curRecord->Unload();
        ++count;
        }
    return stop;
    }

RecordIDRetriever::RecordIDRetriever(RECORDIDARRAY _RecordIDs):
    RecordOp(),
    RecordIDs(_RecordIDs)
    {
    //
    }

RecordIDRetriever::~RecordIDRetriever()
    {
    //
    }

bool RecordIDRetriever::Accept(Record *&curRecord)
    {
    RecordIDs[count++] = curRecord;
    return stop;
    }

RecordMasterChecker::FormIDMasterChecker::FormIDMasterChecker(const UINT8 (&_CollapseTable)[256], const UINT8 &_MasterIndex):
    FormIDOp(),
    CollapseTable(_CollapseTable),
    MasterIndex(_MasterIndex)
    {
    //
    }

RecordMasterChecker::FormIDMasterChecker::~FormIDMasterChecker()
    {
    //
    }

bool RecordMasterChecker::FormIDMasterChecker::Accept(UINT32 &curFormID)
    {
    //Short-circuit the function if the master has already been found to be in use
    if(result)
        return result;

    //Any formID <= 0x800 is hardcoded in the engine and doesn't 'belong' to a mod.
    if((curFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        return false;

    //Check if the master index is in use
    result = CollapseTable[curFormID >> 24] == MasterIndex;
    return result;
    }

bool RecordMasterChecker::FormIDMasterChecker::AcceptMGEF(UINT32 &curMgefCode)
    {
    //Short-circuit the function if the master has already been found to be in use
    if(result)
        return result;

    //Check if the master index is in use
    result = CollapseTable[curMgefCode & 0x000000FF] == MasterIndex;
    return result;
    }

RecordMasterChecker::RecordMasterChecker(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders, const UINT8 &_MasterIndex):
    RecordOp(),
    reader(_FormIDHandler, _Expanders),
    checker(_FormIDHandler.CollapseTable, _MasterIndex)
    {
    //
    }

RecordMasterChecker::~RecordMasterChecker()
    {
    //
    }

bool RecordMasterChecker::Accept(Record *&curRecord)
    {
    if(stop)
        return stop;

    //Ensure the record is read
    reader.Accept(curRecord);

    //See if the master is in use
    checker.Accept(curRecord->formID);
    curRecord->VisitFormIDs(checker);
    stop = checker.GetResult();

    //If the record was read unload it again
    if(reader.GetResult())
        curRecord->Unload();

    return stop;
    }

RecordFormIDSwapper::FormIDSwapper::FormIDSwapper(const UINT32 &_FormIDToMatch, const UINT32 &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler):
    FormIDOp(),
    FormIDToMatch(_FormIDToMatch),
    FormIDToSwap(_FormIDToSwap),
    checker(_FormIDHandler)
    {
    //
    }

RecordFormIDSwapper::FormIDSwapper::~FormIDSwapper()
    {
    //
    }

bool RecordFormIDSwapper::FormIDSwapper::Accept(UINT32 &curFormID)
    {
    result = curFormID == FormIDToMatch;
    if(result)
        {
        curFormID = FormIDToSwap;
        checker.Accept(curFormID);
        ++count;
        }
    return stop;
    }

bool RecordFormIDSwapper::FormIDSwapper::AcceptMGEF(UINT32 &curMgefCode)
    {
    result = curMgefCode == FormIDToMatch;
    if(result)
        {
        curMgefCode = FormIDToSwap;
        checker.Accept(curMgefCode);
        ++count;
        }
    return stop;
    }

RecordFormIDSwapper::RecordFormIDSwapper(const UINT32 &_FormIDToMatch, const UINT32 &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    reader(_FormIDHandler, _Expanders),
    swapper(_FormIDToMatch, _FormIDToSwap, _FormIDHandler)
    {
    //
    }

RecordFormIDSwapper::~RecordFormIDSwapper()
    {
    //
    }

bool RecordFormIDSwapper::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    reader.Accept(curRecord);

    //Perform the swap
    stop = curRecord->VisitFormIDs(swapper);

    //Check if anything was swapped
    if(count != swapper.GetCount())
        {
        //If so, mark the record as changed
        curRecord->IsChanged(true);
        count = swapper.GetCount();
        }

    //If the record was read, but not changed, unload it again
    if(reader.GetResult() && !curRecord->IsChanged())
        curRecord->Unload();

    return stop;
    }

RecordIndexer::RecordIndexer(ModFile *_curModFile, EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map):
    RecordOp(),
    curModFile(_curModFile),
    EditorID_ModFile_Record(_EditorID_Map),
    FormID_ModFile_Record(_FormID_Map)
    {
    //
    }

RecordIndexer::RecordIndexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map):
    RecordOp(),
    EditorID_ModFile_Record(_EditorID_Map),
    FormID_ModFile_Record(_FormID_Map)
    {
    //
    }

RecordIndexer::~RecordIndexer()
    {
    //
    }

bool RecordIndexer::Accept(Record *&curRecord)
    {
    if(curRecord->IsKeyedByEditorID())
        EditorID_ModFile_Record.insert(std::make_pair(curRecord->GetEditorIDKey(),std::make_pair(curModFile,curRecord)));
    else
        FormID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return false;
    }

void RecordIndexer::SetModFile(ModFile *_curModFile)
    {
    curModFile = _curModFile;
    }

RecordDeindexer::RecordDeindexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map):
    RecordOp(),
    EditorID_ModFile_Record(_EditorID_Map),
    FormID_ModFile_Record(_FormID_Map)
    {
    //
    }

RecordDeindexer::~RecordDeindexer()
    {
    //
    }

bool RecordDeindexer::Accept(Record *&curRecord)
    {
    //De-Index the record
    if(curRecord->IsKeyedByEditorID())
        {
        for(EditorID_Range range = EditorID_ModFile_Record.equal_range(curRecord->GetEditorIDKey()); range.first != range.second; ++range.first)
            if(range.first->second.second == curRecord)
                {
                EditorID_ModFile_Record.erase(range.first);
                ++count;
                result = true;
                return false;
                }
        }
    else
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
            if(range.first->second.second == curRecord)
                {
                FormID_ModFile_Record.erase(range.first);
                ++count;
                result = true;
                return false;
                }
        }
    return false;
    }

RecordDeleter::RecordDeleter(Record *_RecordToDelete, EditorID_Map &_EditorID_ModFile_Record, FormID_Map &_FormID_ModFile_Record):
    RecordOp(),
    deindexer(_EditorID_ModFile_Record, _FormID_ModFile_Record),
    RecordToDelete(_RecordToDelete)
    {
    //
    }

RecordDeleter::~RecordDeleter()
    {
    //
    }

bool RecordDeleter::Accept(Record *&curRecord)
    {
    if(curRecord == NULL || curRecord == NULL)
        return false;

    if(RecordToDelete == NULL || curRecord == RecordToDelete)
        {
        //De-Index the record
        deindexer.Accept(curRecord);
        //De-index any subrecords
        curRecord->VisitSubRecords(NULL, deindexer);
        //Mark the record for deletion
        curRecord = NULL;
        ++count;
        result = true;
        stop = RecordToDelete != NULL;
        return stop;
        }
    return false;
    }

RecordChanger::RecordChanger(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    reader(_FormIDHandler, _Expanders)
    {
    //
    }

RecordChanger::~RecordChanger()
    {
    //
    }

bool RecordChanger::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    reader.Accept(curRecord);
    //Mark it as changed
    curRecord->IsChanged(true);

    return stop;
    }