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
// Collection.cpp
#include "Collection.h"
#include <direct.h>
#include <sys/utime.h>
#include <boost/threadpool.hpp>

bool compMod(ModFile *lhs, ModFile *rhs)
    {
    return *lhs < *rhs;
    }

bool sortMod(ModFile *lhs, ModFile *rhs)
    {
    if(lhs->TES4.IsESM())
        {
        if(rhs->TES4.IsESM())
            {
            if(lhs->ModTime == 0)
                {
                if(rhs->ModTime == 0)
                    return true;
                return false;
                }
            if(rhs->ModTime == 0)
                return true;
            return lhs->ModTime < rhs->ModTime;
            }
        return true;
        }
    if(rhs->TES4.IsESM())
        return false;
    //Esp's sort after esp's
    //Non-existent esps sort before existing esps
    //Non-existent esps retain their relative load order
    //Existing esps sort by modified date
    //New esps load last
    //if(lhs->Settings.IsNew)
    //    printf("New mod: %s\n", lhs->FileName);
    //if(rhs->Settings.IsNew)
    //    printf("New mod: %s\n", rhs->FileName);
    if(!FileExists(lhs->FileName))
        {
        if(!FileExists(rhs->FileName))
            return true;
        return false;
        }
    if(!FileExists(rhs->FileName))
        return false;
    if(lhs->ModTime == 0)
        {
        if(rhs->ModTime == 0)
            return false;
        return true;
        }
    if(rhs->ModTime == 0)
        return false;
    return lhs->ModTime < rhs->ModTime;
    }

Collection::Collection(STRING const &ModsPath, UINT32 _CollectionType):
    ModsDir(NULL),
    IsLoaded(false),
    CollectionType((collectionType)_CollectionType)
    {
    ModsDir = new char[strlen(ModsPath)+1];
    strcpy_s(ModsDir, strlen(ModsPath)+1, ModsPath);
    }

Collection::~Collection()
    {
    delete []ModsDir;
    for(UINT32 p = 0; p < ModFiles.size(); p++)
        delete ModFiles[p];
    //LoadOrder255 is shared with ModFiles, so no deleting
    }

SINT32 Collection::AddMod(STRING const &ModName, ModFlags &flags)
    {
    _chdir(ModsDir);
    //Mods may not be added after collection is loaded.
    //Prevent loading mods more than once
    if(IsLoaded || IsModAdded(ModName))
        return -1;

    STRING FileName = new char[strlen(ModName)+1];
    strcpy_s(FileName, strlen(ModName) + 1, ModName);
    switch(CollectionType)
        {
        case eTES4:
            ModFiles.push_back(new TES4File(FileName, flags.GetFlags()));
            break;
        case eFO3:
            printf("Unimplemented\n");
            throw 1;
            break;
        case eFNV:
            printf("Unimplemented\n");
            throw 1;
            break;
        default:
            break;
        }
    return 1;
    }

bool Collection::IsModAdded(STRING const &ModName)
    {
    for(UINT32 p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return true;
    return false;
    }

SINT32 Collection::SaveMod(ModFile *curModFile, bool CloseCollection)
    {
    if(!curModFile->Flags.IsSaveable)
        return -1;

    //Saves to a temp file, then if successful, renames any existing files, and then renames temp file to ModName
    if(CloseCollection)
        {
        //clear up some memory
        EditorID_ModFile_Record.clear();
        FormID_ModFile_Record.clear();
        ExtendedEditorID_ModFile_Record.clear();
        ExtendedFormID_ModFile_Record.clear();
        }

    _chdir(ModsDir);

    char tName[L_tmpnam_s];
    errno_t err;
    time_t ltime;
    struct tm currentTime;
    struct stat oTimes;
    struct _utimbuf originalTimes;

    static time_t lastSave = time(NULL);

    STRING backupName = NULL;
    UINT32 bakAttempts = 0, bakSize = 0;

    err = tmpnam_s(tName, L_tmpnam_s);
    if (err)
        {
        printf("Error occurred creating unique filename.\n");
        return -1;
        }
    tName[0] = 'x';

    try
        {
        //Save the mod to temp file, using FileBuffer to write in chunks
        curModFile->Save(tName, CloseCollection);

        //Rename any existing files to a datestamped backup
        time(&ltime);
        if(ltime - lastSave < 60)
            ltime = lastSave + 60;
        lastSave =  ltime;

        err = _localtime64_s(&currentTime, &ltime);
        if (err)
            {
            printf(" _localtime64_s failed due to invalid arguments.");
            return -1;
            }
        originalTimes.actime = ltime;
        originalTimes.modtime = ltime;

        if(FileExists(curModFile->FileName))
            {
            stat(curModFile->FileName, &oTimes);
            originalTimes.actime = oTimes.st_atime;
            originalTimes.modtime = oTimes.st_mtime;

            bakSize = (UINT32)strlen(curModFile->FileName) + (UINT32)strlen(".bak.XXXX_XX_XX_XX_XX_XX") + 1;
            backupName = new char[bakSize];
            strcpy_s(backupName, bakSize, curModFile->FileName);
            strftime(backupName + strlen(curModFile->FileName), bakSize, ".bak.%Y_%m_%d_%H_%M_%S", &currentTime );

            //If the backup name already exists, wait in 1 second increments until a free name is available
            //If 10 tries pass, then give up.
            bakAttempts = 0;
            while(FileExists(backupName))
                {
                if(bakAttempts > 10)
                    break;
                bakAttempts++;
                currentTime.tm_min++;
                mktime(&currentTime);
                strftime(backupName + strlen(curModFile->FileName), bakSize, ".bak.%Y_%m_%d_%H_%M_%S", &currentTime);
                };
            err = rename(curModFile->FileName, backupName);
            if(err != 0)
                printf("Error renaming \"%s\" to \"%s\"\n", curModFile->FileName, backupName);
            delete []backupName;
            }

        //Rename temp file to the original ModName
        //If it fails, try to save it to a datestamped .new extension and inform the failure
        err = rename(tName, curModFile->FileName);
        if(err != 0)
            {
            bakSize = (UINT32)strlen(curModFile->FileName) + (UINT32)strlen(".new.XXXX_XX_XX_XX_XX_XX") + 1;
            backupName = new char[bakSize];

            strcpy_s(backupName, bakSize, curModFile->FileName);
            strftime(backupName+strlen(curModFile->FileName), bakSize, ".new.%Y_%m_%d_%H_%M_%S", &currentTime );

            //If the backup name already exists, wait in 1 second increments until a free name is available
            //If 10 tries pass, then give up.
            bakAttempts = 0;
            while(FileExists(backupName))
                {
                if(bakAttempts > 10)
                    break;
                bakAttempts++;
                currentTime.tm_min++;
                mktime(&currentTime);
                strftime(backupName + strlen(curModFile->FileName), bakSize, ".new.%Y_%m_%d_%H_%M_%S", &currentTime);
                };

            err = rename(tName, backupName);
            if(err != 0)
                {
                printf("Error renaming \"%s\" to \"%s\"\n", tName, backupName);
                delete []backupName;
                return -1;
                }
            else
                {
                printf("Error renaming \"%s\" to \"%s\"\n", tName, curModFile->FileName);
                printf("Renamed \"%s\" to \"%s\"\n", tName, backupName);
                _utime(backupName, &originalTimes);
                delete []backupName;
                return 0;
                }
            }
        else
            _utime(curModFile->FileName, &originalTimes);
        }
    catch(...)
        {
        printf("Error saving: %s\n", curModFile->FileName);
        if(FileExists(tName))
            {
            remove(tName);
            printf("  Temp file %s removed.\n", tName);
            }
        throw 1;
        return -1;
        }
    return 0;
    }

SINT32 Collection::Load()
    {
    #ifdef CBASH_USE_LOGGING
        CLOGGER;
        BOOST_LOG_FUNCTION();
        BOOST_LOG_SEV(lg, trace) << "Load flags = " << LoadFlags;
    #endif

    ModFile *curModFile = NULL;
    RecordIndexer indexer(EditorID_ModFile_Record, FormID_ModFile_Record);
    RecordIndexer extended_indexer(ExtendedEditorID_ModFile_Record, ExtendedFormID_ModFile_Record);
    bool Preloading = false;

    if(IsLoaded)
        return 0;
    try
        {
        _chdir(ModsDir);
        //Brute force approach to loading all masters
        //Could be done more elegantly with recursion
        do {
            Preloading = false;
            for(UINT32 p = 0; p < (UINT32)ModFiles.size(); ++p)
                {
                curModFile = ModFiles[p];
                curModFile->LoadTES4();
                if(curModFile->Flags.IsAddMasters)
                    {
                    //Any new mods loaded this way inherit their flags
                    ModFlags preloadFlags(curModFile->Flags.GetFlags());
                    preloadFlags.IsNoLoad = !curModFile->Flags.IsLoadMasters;
                    //preloadFlags.IsInLoadOrder = !preloadFlags.IsNoLoad;
                    for(UINT8 x = 0; x < curModFile->TES4.MAST.size(); ++x)
                        Preloading = (AddMod(curModFile->TES4.MAST[x].value, preloadFlags) == 0 || Preloading);
                    }
                }
        }while(Preloading);

        std::_Insertion_sort(ModFiles.begin(), ModFiles.end(), sortMod);
        std::vector<STRING> strLoadOrder255;
        LoadOrder255.clear();
        strLoadOrder255.clear();
        for(UINT32 p = 0; p < (UINT32)ModFiles.size(); ++p)
            {
            curModFile = ModFiles[p];
            curModFile->ModID = p;
            if(curModFile->Flags.IsInLoadOrder)
                {
                if(p >= 255)
                    throw std::exception("Tried to load more than 255 mods.");
                LoadOrder255.push_back(curModFile);
                strLoadOrder255.push_back(curModFile->FileName);
                }
            }

        UINT8 expandedIndex = 0;
        for(UINT32 p = 0; p < (UINT32)ModFiles.size(); ++p)
            {
            curModFile = ModFiles[p];
            //Loads GRUP and Record Headers.  Fully loads GMST records.
            curModFile->FormIDHandler.SetLoadOrder(strLoadOrder255);
            if(curModFile->Flags.IsSkipNewRecords)
                curModFile->FormIDHandler.CreateFormIDLookup(0xFF);
            else
                {
                curModFile->FormIDHandler.CreateFormIDLookup(expandedIndex);
                ++expandedIndex;
                }
            if(curModFile->Flags.IsExtendedConflicts)
                {
                extended_indexer.SetModFile(curModFile);
                curModFile->Load(extended_indexer);
                }
            else
                {
                indexer.SetModFile(curModFile);
                curModFile->Load(indexer);
                }
            }
        IsLoaded = true;
        }
    catch(std::exception& e)
        {
        printf("Failed Load %s\n", e.what());
        IsLoaded = false;
        throw;
        return -1;
        }
    catch(...)
        {
        printf("Failed Load?\n");
        IsLoaded = false;
        throw;
        return -1;
        }
    return 0;
    }

SINT32 Collection::Unload()
    {
    Record *curRecord = NULL;
    for(FormID_Iterator it = FormID_ModFile_Record.begin(); it != FormID_ModFile_Record.end(); ++it)
        {
        curRecord = it->second.second;
        if(curRecord != NULL && !curRecord->IsChanged())
            curRecord->Unload();
        }
    for(EditorID_Iterator it = EditorID_ModFile_Record.begin(); it != EditorID_ModFile_Record.end(); ++it)
        {
        curRecord = it->second.second;
        if(curRecord != NULL && !curRecord->IsChanged())
            curRecord->Unload();
        }
    for(FormID_Iterator it = ExtendedFormID_ModFile_Record.begin(); it != ExtendedFormID_ModFile_Record.end(); ++it)
        {
        curRecord = it->second.second;
        if(curRecord != NULL && !curRecord->IsChanged())
            curRecord->Unload();
        }
    for(EditorID_Iterator it = ExtendedEditorID_ModFile_Record.begin(); it != ExtendedEditorID_ModFile_Record.end(); ++it)
        {
        curRecord = it->second.second;
        if(curRecord != NULL && !curRecord->IsChanged())
            curRecord->Unload();
        }
    return 0;
    }

FormID_Iterator Collection::LookupRecord(ModFile *&curModFile, const FORMID &RecordFormID, Record *&curRecord)
    {
    curRecord = NULL;
    FormID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.equal_range(RecordFormID) : FormID_ModFile_Record.equal_range(RecordFormID);
    for(; range.first != range.second; ++range.first)
        if(range.first->second.first == curModFile)
            {
            curRecord = range.first->second.second;
            return range.first;
            }
    return curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.end() : FormID_ModFile_Record.end();
    }

EditorID_Iterator Collection::LookupRecord(ModFile *&curModFile, STRING const &RecordEditorID, Record *&curRecord)
    {
    curRecord = NULL;

    EditorID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID) : EditorID_ModFile_Record.equal_range(RecordEditorID);
    for(; range.first != range.second; ++range.first)
        if(range.first->second.first == curModFile)
            {
            curRecord = range.first->second.second;
            return range.first;
            }
    return curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record.end() : EditorID_ModFile_Record.end();
    }

UINT32 Collection::IsRecordWinning(ModFile *curModFile, const FORMID &RecordFormID, STRING const &RecordEditorID, const bool GetExtendedConflicts)
    {
    bool bIsWinning = false;

    std::vector<ModFile *> sortedConflicts;
    sortedConflicts.reserve(300);  //Enough for the worst case of all 255 loaded mods having conflicts, plus some for extended conflict mods

    if(RecordFormID != 0)
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
            sortedConflicts.push_back(range.first->second.first);
        if(GetExtendedConflicts)
            {
            for(FormID_Range range = ExtendedFormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
                sortedConflicts.push_back(range.first->second.first);
            }
        }
    else if(RecordEditorID != NULL)
        {
        for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
            sortedConflicts.push_back(range.first->second.first);
        if(GetExtendedConflicts)
            {
            for(EditorID_Range range = ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                sortedConflicts.push_back(range.first->second.first);
            }
        }

    if(sortedConflicts.size())
        {
        std::sort(sortedConflicts.begin(), sortedConflicts.end(), compMod);
        bIsWinning = sortedConflicts[sortedConflicts.size()] == curModFile;
        sortedConflicts.clear();
        }
    return bIsWinning;
    }

UINT32 Collection::GetNumRecordConflicts(const FORMID &RecordFormID, STRING const &RecordEditorID, const bool GetExtendedConflicts)
    {
    UINT32 count = 0;
    if(RecordFormID != 0)
        {
        count = FormID_ModFile_Record.count(RecordFormID);
        if(GetExtendedConflicts)
            count += ExtendedFormID_ModFile_Record.count(RecordFormID);
        }            
    else if(RecordEditorID != NULL)
        {
        count = EditorID_ModFile_Record.count(RecordEditorID);
        if(GetExtendedConflicts)
            count += ExtendedEditorID_ModFile_Record.count(RecordEditorID);
        }
    return count;
    }

void Collection::GetRecordConflicts(const FORMID &RecordFormID, STRING const &RecordEditorID, UINT32ARRAY ModIDs, const bool GetExtendedConflicts)
    {
    std::vector<ModFile *> sortedConflicts;
    sortedConflicts.reserve(300);  //Enough for the worst case of all 255 loaded mods having conflicts, plus some for extended conflict mods
    //std::set<UINT32> conflicts;
    if(RecordFormID != 0)
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
            sortedConflicts.push_back(range.first->second.first);
        if(GetExtendedConflicts)
            {
            for(FormID_Range range = ExtendedFormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
                sortedConflicts.push_back(range.first->second.first);
            }
        }
    else if(RecordEditorID != NULL)
        {
        for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
            sortedConflicts.push_back(range.first->second.first);
        if(GetExtendedConflicts)
            {
            for(EditorID_Range range = ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                sortedConflicts.push_back(range.first->second.first);
            }
        }

    if(sortedConflicts.size())
        {
        std::sort(sortedConflicts.begin(), sortedConflicts.end(), compMod);
        UINT32 x = 0;
        for(SINT32 y = (SINT32)sortedConflicts.size() - 1; y >= 0; --y, ++x)
            ModIDs[x] = sortedConflicts[y]->ModID;
        sortedConflicts.clear();
        }
    }

UINT32 Collection::NextFreeExpandedFormID(ModFile *&curModFile, UINT32 depth)
    {
    UINT32 curFormID = curModFile->FormIDHandler.NextExpandedFormID();
    FormID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.equal_range(curFormID) : FormID_ModFile_Record.equal_range(curFormID);
    //FormID doesn't exist in any mod, so it's free for use
    if(range.first == range.second)
        return curFormID;
    //The formID already exists, so try again (either in that mod, or being injected into that mod)
    //Wrap around and recycle any freed ids.
    if(depth < 0x00FFFFFF)
        return NextFreeExpandedFormID(curModFile, ++depth);
    //All formIDs are in use. Unlikely to ever occur.
    return 0;
    }

UINT32 Collection::CreateRecord(ModFile *curModFile, const UINT32 &RecordType, FORMID RecordFormID, STRING const &RecordEditorID, const FORMID &ParentFormID, UINT32 CreateFlags)
    {
    if(!curModFile->Flags.IsInLoadOrder)
        return 0;

    CreateRecordOptions options(CreateFlags);
    Record *DummyRecord = NULL;
    Record *ParentRecord = NULL;

    //See if the requested record already exists
    if(RecordFormID != 0)
        LookupRecord(curModFile, RecordFormID, DummyRecord);
    else if(RecordEditorID != NULL)
        LookupRecord(curModFile, RecordEditorID, DummyRecord);
    if(DummyRecord != NULL)
        return DummyRecord->formID;

    //Lookup the required data, and ensure it exists
    if(ParentFormID)
        {
        LookupRecord(curModFile, ParentFormID, ParentRecord);
        if(ParentRecord == NULL)
            return 0;
        }

    //Create the new record
    Record *curRecord = curModFile->CreateRecord(RecordType, RecordEditorID, DummyRecord, ParentRecord, options);
    if(curRecord == NULL)
        return 0;

    //See if an existing record was returned instead of a new record
    if(curRecord->formID != 0)
        return curRecord->formID;

    //Assign the new record an unused formID
    if(RecordFormID == 0)
        RecordFormID = curRecord->formID = NextFreeExpandedFormID(curModFile);
    else
        curRecord->formID = RecordFormID;

    //Index the new record
    RecordIndexer indexer(curModFile, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);
    indexer.Accept(&curRecord);

    return RecordFormID;
    }

UINT32 Collection::CopyRecord(ModFile *curModFile, const FORMID &RecordFormID, STRING const &RecordEditorID, ModFile *DestModFile, FORMID DestParentFormID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, UINT32 CreateFlags)
    {
    if(!curModFile->Flags.IsInLoadOrder)
        return 0;

    CreateRecordOptions options(CreateFlags);
    Record *curRecord = NULL;

    //Lookup the required data, and ensure it exists
    if(RecordFormID != 0)
        LookupRecord(curModFile, RecordFormID, curRecord);
    else if(RecordEditorID != NULL)
        LookupRecord(curModFile, RecordEditorID, curRecord);
    if(curRecord == NULL)
        return 0;

    Record *ParentRecord = NULL;
    Record *RecordCopy = NULL;

    if(options.SetAsOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        if(RecordFormID != 0)
            LookupRecord(DestModFile, RecordFormID, RecordCopy);
        else if(RecordEditorID != NULL)
            LookupRecord(DestModFile, RecordEditorID, RecordCopy);
        if(RecordCopy != NULL)
            return RecordFormID;
        }

    if(DestParentFormID)
        {
        //See if the parent record already exists in the destination mod
        LookupRecord(DestModFile, DestParentFormID, ParentRecord);
        if(ParentRecord == NULL)
            {
            //If it doesn't, try and create it.
            CreateRecordOptions parentOptions;
            parentOptions.SetAsOverride = options.SetAsOverride;
            DestParentFormID = CopyRecord(curModFile, DestParentFormID, 0, DestModFile, 0, 0, 0, parentOptions.GetFlags());
            LookupRecord(DestModFile, DestParentFormID, ParentRecord);
            if(ParentRecord == NULL)
                return 0;
            }
        }
    if(curModFile == DestModFile)
        return 0;

    //Ensure the record has been fully read
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(&curRecord);

    //Create the record copy
    RecordCopy = DestModFile->CreateRecord(curRecord->GetType(), DestRecordEditorID ? DestRecordEditorID : RecordEditorID, curRecord, ParentRecord, options);
    if(RecordCopy == NULL)
        return 0;

    //See if an existing record was returned instead of the requested copy
    if(RecordCopy->formID != curRecord->formID)
        return RecordCopy->formID;

    //Give the record a new formID if it isn't an override record
    if(!options.SetAsOverride)
        RecordCopy->formID = DestRecordFormID ? DestRecordFormID : NextFreeExpandedFormID(DestModFile);

    //See if the destination mod masters need updating
    FormIDMasterUpdater checker(DestModFile->FormIDHandler);
    checker.Accept(RecordCopy->formID);
    RecordCopy->VisitFormIDs(checker);

    //Index the record
    RecordIndexer indexer(DestModFile, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);
    indexer.Accept(&RecordCopy);

    return RecordCopy->formID;
    }

SINT32 Collection::DeleteRecord(ModFile *curModFile, const FORMID &RecordFormID, STRING const &RecordEditorID, const FORMID &ParentFormID)
    {
    if(!curModFile->Flags.IsInLoadOrder)
        return 0;

    Record *curRecord = NULL;
    Record *ParentRecord = NULL;

    //Ensure requested record exists
    if(RecordFormID != 0)
        LookupRecord(curModFile, RecordFormID, curRecord);
    else if(RecordEditorID != NULL)
        LookupRecord(curModFile, RecordEditorID, curRecord);
    if(curRecord == NULL)
        throw Ex_INVALIDINDEX();

    //Lookup the required data, and ensure it exists
    if(ParentFormID)
        {
        LookupRecord(curModFile, ParentFormID, ParentRecord);
        if(ParentRecord == NULL)
            throw Ex_INVALIDINDEX();
        }

    RecordDeleter deleter(curRecord, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);

    UINT32 RecordType = curRecord->GetType();
    UINT32 TopType = ParentRecord != NULL ? (ParentRecord->GetParentType() ? ParentRecord->GetParentType() : ParentRecord->GetType()) : RecordType;

    curModFile->VisitRecords(TopType, RecordType, deleter, true);
    return deleter.GetCount();
    }

SINT32 Collection::SetRecordIDs(ModFile *curModFile, const FORMID &RecordFormID, STRING const &RecordEditorID, const FORMID &FormIDValue, STRING const &EditorIDValue)
    {
    bool bChangingFormID = RecordFormID != FormIDValue;
    bool bChangingEditorID = false;

    if(RecordEditorID == NULL)
        {
        if(EditorIDValue != NULL)
            bChangingEditorID = true;
        }
    else
        {
        if(EditorIDValue == NULL)
            bChangingEditorID = true;
        else if(strcmpi(RecordEditorID, EditorIDValue) != 0)
            bChangingEditorID = true;
        }
    
    if(!(bChangingFormID || bChangingEditorID))
        return -1;

    Record *curRecord = NULL;
    FormID_Map &curFormID_Map = curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record;
    EditorID_Map &curEditorID_Map = curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record;

    bool bDeIndexed = false;

    //If the FormIDValue is already in use by the mod, do nothing.
    if(bChangingFormID && FormIDValue != 0)
        LookupRecord(curModFile, FormIDValue, curRecord);

    //If the EditorIDValue is already in use by the mod, do nothing.
    if(bChangingEditorID && EditorIDValue != NULL)
        LookupRecord(curModFile, EditorIDValue, curRecord);

    if(curRecord != NULL)
        return -1;

    //Lookup the required data, and ensure it exists
    //De-index the record
    FormID_Iterator formID_it = LookupRecord(curModFile, RecordFormID, curRecord);
    if(curRecord != NULL || formID_it != curFormID_Map.end())
        {
        //Not allowed to set the formID to 0 if the record is keyed by it
        bChangingFormID = bChangingFormID && FormIDValue != 0;
        if(bChangingFormID)
            {
            curFormID_Map.erase(formID_it);
            bDeIndexed = true;
            }
        }
    else
        {
        EditorID_Iterator editorID_it = LookupRecord(curModFile, RecordEditorID, curRecord);
        if(curRecord != NULL || editorID_it != curEditorID_Map.end())
            {
            //Not allowed to delete the editorID if the record is keyed by it
            bChangingEditorID = bChangingEditorID && EditorIDValue != NULL;
            if(bChangingEditorID)
                {
                curEditorID_Map.erase(editorID_it);
                bDeIndexed = true;
                }
            }
        else
            return -1;
        }

    //Update the formID
    if(bChangingFormID)
        {
        curRecord->formID = FormIDValue;
        FormIDMasterUpdater checker(curModFile->FormIDHandler);
        checker.Accept(curRecord->formID);
        }

    //Update the editorID
    if(bChangingEditorID)
        curRecord->SetField(4, 0, 0, 0, 0, 0, 0, (void *)EditorIDValue, 0);

    //Re-index the record
    if(bDeIndexed)
        {
        RecordIndexer indexer(curModFile, curEditorID_Map, curFormID_Map);
        indexer.Accept(&curRecord);
        }
    return (bChangingFormID || bChangingEditorID) ? 1 : -1;
    }