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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
// Visitors.cpp
#include "Visitors.h"
#include "Oblivion/Records/MGEFRecord.h"

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
        curRecord->Unload();
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

FormIDSwapper::FormIDSwapper(const UINT32 &_FormIDToMatch, const UINT32 &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler):
    FormIDOp(),
    FormIDToMatch(_FormIDToMatch),
    FormIDToSwap(_FormIDToSwap),
    checker(_FormIDHandler)
    {
    //
    }

FormIDSwapper::~FormIDSwapper()
    {
    //
    }

bool FormIDSwapper::Accept(UINT32 &curFormID)
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

bool FormIDSwapper::AcceptMGEF(UINT32 &curMgefCode)
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
    if(curRecord->formID != 0)
        FormID_ModFile_Record.insert(std::make_pair(curRecord->formID,curRecord));
    if(curRecord->IsKeyedByEditorID() && curRecord->GetEditorIDKey() != NULL) //Should only be null on deleted records (they'll get indexed after being undeleted)
        EditorID_ModFile_Record.insert(std::make_pair(curRecord->GetEditorIDKey(),curRecord));
    return false;
    }

void RecordIndexer::SetModFile(ModFile *_curModFile)
    {
    curModFile = _curModFile;
    }