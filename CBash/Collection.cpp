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
// Collection.cpp
#include "Collection.h"
#include <direct.h>
#include <sys/utime.h>
//#include <boost/threadpool.hpp>

//SortedRecords::SortedRecords():
//    size(0),
//    mods(NULL),
//    records(NULL)
//    {
//    //
//    }
//
//SortedRecords::~SortedRecords()
//    {
//    delete []mods;
//    delete []records;
//    }
//
//void SortedRecords::push_back(ModFile *&mod, Record *&record)
//    {
//    ModFile ** temp_mods = new ModFile *[size + 1];
//    Record ** temp_records = new Record *[size + 1];
//    bool placed = false;
//    for(UINT32 x = 0, y = 0; x < size; ++y)
//        {
//        if(!placed && mods[x]->ModID > mod->ModID)
//            {
//            placed = true;
//            temp_mods[y] = mod;
//            temp_records[y] = record;
//            }
//        else
//            {
//            temp_mods[y] = mods[x];
//            temp_records[y] = records[x];
//            ++x;
//            }
//        }
//    if(!placed)
//        {
//        temp_mods[size] = mod;
//        temp_records[size] = record;
//        }
//    size++;
//    delete []mods;
//    delete []records;
//    mods = temp_mods;
//    records = temp_records;
//    }
//
//void SortedRecords::erase(UINT32 &index)
//    {
//    ModFile ** temp_mods = new ModFile *[size - 1];
//    Record ** temp_records = new Record *[size - 1];
//    for(UINT32 x = 0, y = 0; x < size; ++x)
//        {
//        if(x == index)
//            continue;
//        temp_mods[y] = mods[x];
//        temp_records[y] = records[x];
//        ++y;
//        }
//    size--;
//    delete []mods;
//    delete []records;
//    mods = temp_mods;
//    records = temp_records;
//    }

bool compModRecordPair(std::pair<ModFile *, Record *> &lhs, std::pair<ModFile *, Record *> &rhs)
    {
    return lhs.first->ModID < rhs.first->ModID;
    }

bool sortMod(ModFile *lhs, ModFile *rhs)
    {
    //Esp's sort after esm's
    //Non-existent esms sort before existing esps
    //Non-existent esms retain their relative load order
    //Existing esps sort by modified date
    //New esps load last
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
    if(lhs->Flags.IsIgnoreExisting || lhs->ModTime == 0)
        {
        if(rhs->Flags.IsIgnoreExisting || rhs->ModTime == 0)
            return true;
        return false;
        }
    if(rhs->Flags.IsIgnoreExisting || rhs->ModTime == 0)
        return false;
    return lhs->ModTime < rhs->ModTime;
    }

Collection::Collection(STRING const &ModsPath, UINT32 _CollectionType):
    ModsDir(NULL),
    IsLoaded(false),
    CollectionType(),
    identical_records(),
    changed_records()
    {
    if(_CollectionType >= eIsUnknownGameType)
        throw std::exception("CreateCollection: Error - Unable to create the collection. Invalid collection type specified.\n");
    CollectionType = (whichGameTypes)_CollectionType;
    ModsDir = new char[strlen(ModsPath)+1];
    strcpy_s(ModsDir, strlen(ModsPath)+1, ModsPath);
    }

Collection::~Collection()
    {
    delete []ModsDir;
    for(UINT32 p = 0; p < ModFiles.size(); p++)
        delete ModFiles[p];
    for(UINT32 p = 0; p < Expanders.size(); p++)
        delete Expanders[p];
    //LoadOrder255 is shared with ModFiles, so no deleting
    }

SINT32 Collection::AddMod(STRING const &_FileName, ModFlags &flags, bool IsPreloading)
    {
    _chdir(ModsDir);
    //Mods may not be added after collection is loaded.
    //Prevent loading mods more than once

    STRING ModName = DeGhostModName(_FileName);
    ModFile *ModID = IsModAdded(ModName ? ModName : _FileName);
    if(ModID != NULL)
        {
        //Suppress any warnings if masters are being loaded, or if the mod is being added with the same flags as before
        if(IsPreloading || ModID->Flags.GetFlags() == flags.GetFlags())
            {
            delete []ModName;
            return IsPreloading ? -1 : 0;
            }
        printer("AddMod: Warning - Unable to add mod \"%s\". It already exists in the collection.\n", ModName ? ModName : _FileName);
        delete []ModName;
        return -1;
        }

    if(IsLoaded)
        {
        if(!IsPreloading)
            printer("AddMod: Error - Unable to add mod \"%s\". The collection has already been loaded.\n", ModName ? ModName : _FileName);
        delete []ModName;
        return -1;
        }

    STRING FileName = new char[strlen(_FileName) + 1];
    strcpy_s(FileName, strlen(_FileName) + 1, _FileName);
    ModName = ModName ? ModName : FileName;

    switch(CollectionType)
        {
        case eIsOblivion:
            ModFiles.push_back(new TES4File(this, FileName, ModName, flags.GetFlags()));
            ModFiles.back()->TES4.whichGame = eIsOblivion;
            break;
        case eIsFallout3:
            printer("AddMod: Error - Unable to add mod \"%s\". Fallout 3 mod support is unimplemented.\n", ModName);
            delete []ModName;
            break;
        case eIsFalloutNewVegas:
            ModFiles.push_back(new FNVFile(this, FileName, ModName, flags.GetFlags()));
            ModFiles.back()->TES4.whichGame = eIsFalloutNewVegas;
            break;
        default:
            printer("AddMod: Error - Unable to add mod \"%s\". Invalid collection type.\n", ModName);
            delete []ModName;
            break;
        }
    return 0;
    }

ModFile * Collection::IsModAdded(STRING const &ModName)
    {
    for(UINT32 p = 0;p < ModFiles.size();p++)
        if(icmps(ModName, ModFiles[p]->ModName) == 0)
            return ModFiles[p];
    return NULL;
    }

SINT32 Collection::SaveMod(ModFile *&curModFile, SaveFlags &flags)
    {
    if(!curModFile->Flags.IsSaveable)
        {
        printer("SaveMod: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", curModFile->ModName);
        return -1;
        }

    //Saves to a temp file, then if successful, renames any existing files, and then renames temp file to ModName
    if(flags.IsCloseCollection)
        {
        //clear up some memory
        EditorID_ModFile_Record.clear();
        FormID_ModFile_Record.clear();
        ExtendedEditorID_ModFile_Record.clear();
        ExtendedFormID_ModFile_Record.clear();
        }
    else
        {
        //Saving always results in the mod being closed (otherwise the file can't be replaced with the saved file)
        //If the mod is closed, the recData pointer on all records becomes invalidated, and the record can't load new data
        //So we have to read all the data in now, and mark all records as changed so that they aren't unloaded.
        //Otherwise the program will crash upon accessing the invalid pointer
        RecordChanger changer(curModFile->FormIDHandler, Expanders);
        curModFile->VisitAllRecords(changer);
        }

    if(flags.IsCleanMasters)
        CleanModMasters(curModFile);

    RecordIndexer indexer(curModFile, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);

    _chdir(ModsDir);

    char tName[L_tmpnam_s];

    time_t ltime;
    struct tm currentTime;
    struct stat oTimes;
    struct _utimbuf originalTimes;

    static time_t lastSave = time(NULL);

    STRING backupName = NULL;
    UINT32 bakAttempts = 0, bakSize = 0;

    switch(tmpnam_s(tName, L_tmpnam_s))
        {
        case 0:
            break;
        case ERANGE:
            //Fallthrough intentional. ERANGE should never be returned.
        case EINVAL:
            //Fallthrough intentional. EINVAL should never be returned.
        default:
            printer("SaveMod: Error - Unable to save \"%s\". An unspecified error occurred when creating a unique temporary filename.\n", curModFile->FileName);
            return -1;
        }

    tName[0] = 'x';

    try
        {
        //Save the mod to temp file, using FileBuffer to write in chunks
        curModFile->Save(tName, Expanders, flags.IsCloseCollection, indexer);

        //Rename any existing files to a datestamped backup
        time(&ltime);
        if(ltime - lastSave < 60)
            ltime = lastSave + 60;
        lastSave = ltime;

        switch(_localtime64_s(&currentTime, &ltime))
            {
            case 0:
                break;
            case EINVAL:
                //Fallthrough intentional. EINVAL should never be returned.
            default:
                printer("SaveMod: Error - Unable to save \"%s\". _localtime64_s failed due to invalid arguments.\n", curModFile->FileName);
                return -1;
            }

        originalTimes.actime = ltime;
        originalTimes.modtime = ltime;

        if(curModFile->exists())
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

            switch(rename(curModFile->FileName, backupName))
                {
                case 0:
                    break;
                case EACCES:
                    printer("SaveMod: Error - Unable to rename existing file from \"%s\" to \"%s\". File or directory specified by newname already exists or could not be created (invalid path); or oldname is a directory and newname specifies a different path.\n", curModFile->FileName, backupName);
                    break;
                case ENOENT:
                    printer("SaveMod: Error - Unable to rename existing file from \"%s\" to \"%s\". File or path specified by oldname not found.\n", curModFile->FileName, backupName);
                    break;
                case EINVAL:
                    printer("SaveMod: Error - Unable to rename existing file from \"%s\" to \"%s\". Name contains invalid characters.\n", curModFile->FileName, backupName);
                    break;
                case EEXIST:
                    printer("SaveMod: Error - Unable to rename existing file from \"%s\" to \"%s\". The new file name already exists.\n", curModFile->FileName, backupName);
                    break;
                default:
                    perror("Unknown");
                    printer("SaveMod: Error - Unable to rename existing file from \"%s\" to \"%s\". Unknown details.\n", curModFile->FileName, backupName);
                    break;
                }

            delete []backupName;
            }

        //Rename temp file to the original ModName
        //If it fails, try to save it to a datestamped .new extension and inform the failure
        switch(rename(tName, curModFile->FileName))
            {
            case 0:
                _utime(curModFile->FileName, &originalTimes);
                return 0;
            case EACCES:
                printer("SaveMod: Warning - Unable to rename temporary file from \"%s\" to \"%s\". File or directory specified by newname already exists or could not be created (invalid path); or oldname is a directory and newname specifies a different path.\n", tName, curModFile->FileName);
                break;
            case ENOENT:
                printer("SaveMod: Warning - Unable to rename temporary file from \"%s\" to \"%s\". File or path specified by oldname not found.\n", tName, curModFile->FileName);
                break;
            case EINVAL:
                printer("SaveMod: Warning - Unable to rename temporary file from \"%s\" to \"%s\". Name contains invalid characters.\n", tName, curModFile->FileName);
                break;
            case EEXIST:
                printer("SaveMod: Warning - Unable to rename temporary file from \"%s\" to \"%s\". The new file name already exists.\n", tName, curModFile->FileName);
                break;
            default:
                perror("Unknown");
                printer("SaveMod: Warning - Unable to rename temporary file from \"%s\" to \"%s\". Unknown details.\n", tName, curModFile->FileName);
                break;
            }

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

        switch(rename(tName, backupName))
            {
            case 0:
                printer("SaveMod: Warning - Renamed temporary file \"%s\" to \"%s\" instead.\n", tName, backupName);
                _utime(backupName, &originalTimes);
                delete []backupName;
                return 0;
            case EACCES:
                printer("SaveMod: Error - Unable to rename temporary file from \"%s\" to \"%s\". File or directory specified by newname already exists or could not be created (invalid path); or oldname is a directory and newname specifies a different path.\n", tName, backupName);
                break;
            case ENOENT:
                printer("SaveMod: Error - Unable to rename temporary file from \"%s\" to \"%s\". File or path specified by oldname not found.\n", tName, backupName);
                break;
            case EINVAL:
                printer("SaveMod: Error - Unable to rename temporary file from \"%s\" to \"%s\". Name contains invalid characters.\n", tName, backupName);
                break;
            case EEXIST:
                printer("SaveMod: Error - Unable to rename temporary file from \"%s\" to \"%s\". The new file name already exists.\n", tName, backupName);
                break;
            default:
                perror("Unknown");
                printer("SaveMod: Error - Unable to rename temporary file from \"%s\" to \"%s\". Unknown details.\n", tName, backupName);
                break;
            }
        delete []backupName;
        return -1;
        }
    catch(...)
        {
        if(FileExists(tName))
            {
            if(remove(tName) == 0)
                printer("SaveMod: Error - Unable to save \"%s\". Temporary file \"%s\" deleted.\n", curModFile->FileName, tName);
            else
                printer("SaveMod: Error - Unable to save \"%s\". Unable to delete temporary file \"%s\"!.\n", curModFile->FileName, tName);
            }
        else
            printer("SaveMod: Error - Unable to save \"%s\".\n", curModFile->FileName);
        throw;
        return -1;
        }
    return 0;
    }

SINT32 Collection::Load()
    {
    ModFile *curModFile = NULL;
    RecordIndexer indexer(EditorID_ModFile_Record, FormID_ModFile_Record);
    RecordIndexer extended_indexer(ExtendedEditorID_ModFile_Record, ExtendedFormID_ModFile_Record);
    bool Preloading = false;
    std::vector<std::pair<ModFile *, std::vector<Record *> > > DeletedRecords;

    if(IsLoaded)
        {
        printer("Load: Warning - Unable to load collection. It is already loaded.\n");
        return 0;
        }
    try
        {
        _chdir(ModsDir);
        //Brute force approach to loading all masters
        //Could be done more elegantly with recursion
        //printer("Before Preloading\n");
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
                        Preloading = (AddMod(curModFile->TES4.MAST[x], preloadFlags, true) == 0 || Preloading);
                    }
                }
        }while(Preloading);
        //printer("Load order before sort\n");
        //for(UINT32 x = 0; x < ModFiles.size(); ++x)
        //    printer("%02X: %s\n", x, ModFiles[x]->FileName);
        //printer("\n");
        std::_Insertion_sort(ModFiles.begin(), ModFiles.end(), sortMod);
        std::vector<STRING> strLoadOrder255;
        std::vector<STRING> strTempLoadOrder;
        std::vector< std::vector<STRING> > strAllLoadOrder;
        LoadOrder255.clear(); //shouldn't be needed
        //printer("Load order:\n");
        for(UINT32 p = 0; p < (UINT32)ModFiles.size(); ++p)
            {
            curModFile = ModFiles[p];
            curModFile->ModID = p;
            //printer("ModID %02X: %s", p, curModFile->FileName);
            if(curModFile->Flags.IsInLoadOrder)
                {
                if(LoadOrder255.size() >= 255)
                    throw std::exception("Tried to load more than 255 mods.");
                LoadOrder255.push_back(curModFile);
                strLoadOrder255.push_back(curModFile->ModName);
                //printer(" , OrderID %02X", LoadOrder255.size() - 1);
                }
            else if(!curModFile->Flags.IsIgnoreAbsentMasters) //every mod not in the std load order exists as if it and its masters are the only ones loaded
                {//No need to sort since the masters should be in order well enough
                for(UINT8 x = 0; x < curModFile->TES4.MAST.size(); ++x)
                    strTempLoadOrder.push_back(curModFile->TES4.MAST[x]);
                strAllLoadOrder.push_back(strTempLoadOrder);
                strTempLoadOrder.clear();
                }
            //printer("\n");
            }
        //printer("Load Set\n");
        UINT8 expandedIndex = 0;
        UINT32 x = 0;

        for(UINT32 p = 0; p < (UINT32)ModFiles.size(); ++p)
            {
            curModFile = ModFiles[p];
            RecordReader read_parser(curModFile);
            //Loads GRUP and Record Headers.  Fully loads GMST records.
            if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters)
                curModFile->FormIDHandler.SetLoadOrder(strLoadOrder255);
            else
                {
                curModFile->FormIDHandler.SetLoadOrder(strAllLoadOrder[x]);
                ++x;
                }
            if(curModFile->Flags.IsSkipNewRecords)
                curModFile->FormIDHandler.CreateFormIDLookup(0xFF);
            else
                {
                if(curModFile->Flags.IsInLoadOrder)
                    {
                    curModFile->FormIDHandler.CreateFormIDLookup(expandedIndex);
                    ++expandedIndex;
                    }
                else
                    curModFile->FormIDHandler.CreateFormIDLookup((UINT8)curModFile->TES4.MAST.size());
                }
            Expanders.push_back(new FormIDResolver(curModFile->FormIDHandler.ExpandTable, curModFile->FormIDHandler.FileStart, curModFile->FormIDHandler.FileEnd));
            DeletedRecords.push_back(std::make_pair(curModFile, std::vector<Record *>()));
            if(curModFile->Flags.IsExtendedConflicts)
                {
                extended_indexer.SetModFile(curModFile);
                curModFile->Load(read_parser, extended_indexer, Expanders, DeletedRecords.back().second);
                }
            else
                {
                indexer.SetModFile(curModFile);
                curModFile->Load(read_parser, indexer, Expanders, DeletedRecords.back().second);
                }
            }
        //printer("Loaded\n");
        strAllLoadOrder.clear();
        UndeleteRecords(DeletedRecords);
        IsLoaded = true;
        }
    catch(...)
        {
        IsLoaded = false;
        throw;
        }
    return 0;
    }

void Collection::UndeleteRecords(std::vector<std::pair<ModFile *, std::vector<Record *> > > &DeletedRecords)
    {
    //Deleted records are only composed of their header. All of their data is missing.
    //This makes undeleting a record a bit tricky since you can't just toggle the records IsDeleted flag.
    //This function tries to restore the data of all deleted records so that toggling the IsDeleted flag works as expected.
    //It goes through the mod's masters, and uses the data from the newest record that hasn't been deleted.
    //It is typically unable to restore the data to deleted injected records
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    Record *WinningRecord = NULL;
    ModFile *WinningModFile = NULL;
    SINT32 ModID = -1;
    for(UINT32 ListIndex = 0; ListIndex < DeletedRecords.size(); ++ListIndex)
        {
        curModFile = DeletedRecords[ListIndex].first;
        std::vector<Record *> &curRecords = DeletedRecords[ListIndex].second;
        if(!curModFile->Flags.IsLoadMasters || !curModFile->Flags.IsInLoadOrder ||
            curModFile->Flags.IsExtendedConflicts || curModFile->Flags.IsIgnoreAbsentMasters)
            {
            curRecords.clear();
            continue;
            }
        UINT8 &CollapsedIndex = curModFile->FormIDHandler.CollapsedIndex;
        const UINT8 (&CollapseTable)[256] = curModFile->FormIDHandler.CollapseTable;

        for(UINT32 z = 0; z < curRecords.size(); ++z)
            {
            ModID = -1;
            curRecord = curRecords[z];
            WinningRecord = NULL;

            if(curRecord->IsKeyedByEditorID())
                {
                //This is problematic because the EditorID will have been deleted.
                //The only recourse is to try and find its match by FormID (which isn't 100% reliable)
                //Luckily, these records should almost never be marked as deleted, so efficiency isn't a concern
                STRING RecordEditorID = NULL;
                for(EditorID_Iterator it = EditorID_ModFile_Record.begin(); it != EditorID_ModFile_Record.end(); ++it)
                    if(it->second->formID == curRecord->formID)
                        {
                        RecordEditorID = it->second->GetEditorIDKey();
                        //DPRINT("%s recovered", RecordEditorID);
                        break;
                        }

                if(RecordEditorID != NULL)
                    {
                    for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                        {
                        WinningModFile = range.first->second->GetParentMod();
                        if((SINT32)WinningModFile->ModID > ModID && (WinningModFile->Flags.IsInLoadOrder || WinningModFile->Flags.IsIgnoreAbsentMasters))
                            //If the CollapseTable at a given expanded index is set to something other than the mod's CollapsedIndex,
                            // that means the mod has that other mod as a master.
                            if(CollapseTable[WinningModFile->FormIDHandler.ExpandedIndex] != CollapsedIndex)
                                {
                                if(range.first->second->IsDeleted() == false)
                                    {
                                    ModID = WinningModFile->ModID;
                                    WinningRecord = range.first->second;
                                    }
                                }
                        }
                    }
                if(WinningRecord != NULL)
                    EditorID_ModFile_Record.insert(std::make_pair(RecordEditorID,curRecord));
                }
            else
                {
                for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
                    {
                    WinningModFile = range.first->second->GetParentMod();
                    if((SINT32)WinningModFile->ModID > ModID && (WinningModFile->Flags.IsInLoadOrder || WinningModFile->Flags.IsIgnoreAbsentMasters))
                        //If the CollapseTable at a given expanded index is set to something other than the mod's CollapsedIndex,
                        // that means the mod has that other mod as a master.
                        if(CollapseTable[WinningModFile->FormIDHandler.ExpandedIndex] != CollapsedIndex)
                            {
                            if(range.first->second->IsDeleted() == false)
                                {
                                ModID = WinningModFile->ModID;
                                WinningRecord = range.first->second;
                                }
                            }
                    }
                }
            if(WinningRecord != NULL)
                curRecord->SetData(WinningRecord->GetData());
            else
                {
                //Deleted injected record?
                printer("Load: Warning - Unable to undelete record %08X in \"%s\". Was not able to determine its source record.\n", curRecord->formID, curModFile->FileName);
                }
            }
        }
    }

SINT32 Collection::Unload()
    {
    RecordUnloader unloader;
    for(UINT32 ListIndex = 0; ListIndex < ModFiles.size(); ++ListIndex)
        ModFiles[ListIndex]->VisitAllRecords(unloader);
    return 0;
    }

FormID_Iterator Collection::LookupRecord(ModFile *&curModFile, const FORMID &RecordFormID, Record *&curRecord)
    {
    for(FormID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.equal_range(RecordFormID) : FormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
        {
        curRecord = range.first->second;
        if(curRecord->GetParentMod() == curModFile)
            return range.first;
        }
    curRecord = NULL;
    return curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.end() : FormID_ModFile_Record.end();
    }

EditorID_Iterator Collection::LookupRecord(ModFile *&curModFile, STRING const &RecordEditorID, Record *&curRecord)
    {
    for(EditorID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID) : EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
        {
        curRecord = range.first->second;
        if(curRecord->GetParentMod() == curModFile)
            return range.first;
        }
    curRecord = NULL;
    return curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record.end() : EditorID_ModFile_Record.end();
    }

FormID_Iterator Collection::LookupWinningRecord(const FORMID &RecordFormID, ModFile *&WinningModFile, Record *&WinningRecord, const bool GetExtendedConflicts)
    {
    WinningModFile = NULL;
    WinningRecord = NULL;

    FormID_Iterator Winning_it;
    SINT32 ModID = -1;
    ModFile *curModFile = NULL;
    for(FormID_Range range = FormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
        {
        curModFile = range.first->second->GetParentMod();
        if((SINT32)curModFile->ModID > ModID && (curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters))
            {
            ModID = curModFile->ModID;
            WinningModFile = curModFile;
            WinningRecord = range.first->second;
            Winning_it = range.first;
            }
        }
    if(GetExtendedConflicts)
        {
        for(FormID_Range range = ExtendedFormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
            {
            curModFile = range.first->second->GetParentMod();
            if((SINT32)curModFile->ModID > ModID && (curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters))
                {
                ModID = curModFile->ModID;
                WinningModFile = curModFile;
                WinningRecord = range.first->second;
                Winning_it = range.first;
                }
            }
        }
    if(ModID > -1)
        return Winning_it;

    return FormID_ModFile_Record.end();
    }

EditorID_Iterator Collection::LookupWinningRecord(STRING const &RecordEditorID, ModFile *&WinningModFile, Record *&WinningRecord, const bool GetExtendedConflicts)
    {
    WinningModFile = NULL;
    WinningRecord = NULL;

    EditorID_Iterator Winning_it;
    SINT32 ModID = -1;
    ModFile *curModFile = NULL;
    for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
        {
        curModFile = range.first->second->GetParentMod();
        if((SINT32)curModFile->ModID > ModID && (curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters))
            {
            ModID = curModFile->ModID;
            WinningModFile = curModFile;
            WinningRecord = range.first->second;
            Winning_it = range.first;
            }
        }
    if(GetExtendedConflicts)
        {
        for(EditorID_Range range = ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
            {
            curModFile = range.first->second->GetParentMod();
            if((SINT32)curModFile->ModID > ModID && (curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters))
                {
                ModID = curModFile->ModID;
                WinningModFile = curModFile;
                WinningRecord = range.first->second;
                Winning_it = range.first;
                }
            }
        }
    if(ModID > -1)
        return Winning_it;

    return EditorID_ModFile_Record.end();
    }

UINT32 Collection::IsRecordWinning(Record *&curRecord, const bool GetExtendedConflicts)
    {
    ModFile *curModFile = curRecord->GetParentMod();

    if(curModFile->Flags.IsExtendedConflicts && !GetExtendedConflicts)
        return false;
    ModFile *WinningModfile = NULL;
    Record *WinningRecord = NULL;

    if(curRecord->IsKeyedByEditorID())
        LookupWinningRecord(curRecord->GetEditorIDKey(), WinningModfile, WinningRecord, GetExtendedConflicts);
    else
        LookupWinningRecord(curRecord->formID, WinningModfile, WinningRecord, GetExtendedConflicts);

    return curRecord == WinningRecord;
    }

UINT32 Collection::GetNumRecordConflicts(Record *&curRecord, const bool GetExtendedConflicts)
    {
    UINT32 count = 0;
    if(curRecord->IsKeyedByEditorID())
        {
        STRING RecordEditorID = curRecord->GetEditorIDKey();
        if(RecordEditorID != NULL)
            {
            count = (UINT32)EditorID_ModFile_Record.count(RecordEditorID);
            if(GetExtendedConflicts)
                count += (UINT32)ExtendedEditorID_ModFile_Record.count(RecordEditorID);
            }
        }
    else
        {
        count = (UINT32)FormID_ModFile_Record.count(curRecord->formID);
        if(GetExtendedConflicts)
            count += (UINT32)ExtendedFormID_ModFile_Record.count(curRecord->formID);
        }
    return count;
    }

SINT32 Collection::GetRecordConflicts(Record *&curRecord, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts)
    {
    ModFile *curModFile = NULL;
    if(curRecord->IsKeyedByEditorID())
        {
        STRING RecordEditorID = curRecord->GetEditorIDKey();
        if(RecordEditorID != NULL)
            {
            for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                {
                curModFile = range.first->second->GetParentMod();
                if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters)
                    sortedConflicts.push_back(std::make_pair(curModFile, range.first->second));
                }
            if(GetExtendedConflicts)
                {
                for(EditorID_Range range = ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                    {
                    curModFile = range.first->second->GetParentMod();
                    if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters)
                        sortedConflicts.push_back(std::make_pair(curModFile, range.first->second));
                    }
                }
            }
        }
    else
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
            {
            curModFile = range.first->second->GetParentMod();
            if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters)
                sortedConflicts.push_back(std::make_pair(curModFile, range.first->second));
            }
        if(GetExtendedConflicts)
            {
            for(FormID_Range range = ExtendedFormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
                {
                curModFile = range.first->second->GetParentMod();
                if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreAbsentMasters)
                    sortedConflicts.push_back(std::make_pair(curModFile, range.first->second));
                }
            }
        }

    UINT32 y = (UINT32)sortedConflicts.size();
    if(y)
        {
        std::sort(sortedConflicts.begin(), sortedConflicts.end(), compModRecordPair);
        for(UINT32 x = 0; x < y; ++x)
            RecordIDs[x] = sortedConflicts[y - (x + 1)].second;
        sortedConflicts.clear();
        }
    return y;
    }

SINT32 Collection::GetRecordHistory(Record *&curRecord, RECORDIDARRAY RecordIDs)
    {
    ModFile *curModFile = curRecord->GetParentMod();
    if(curModFile->Flags.IsExtendedConflicts)
        {
        printer("GetRecordHistory: Warning - No history available. Mod \"%s\" uses extended conflicts.\n", curModFile->ModName);
        return -1;
        }

    UINT8 curCollapsedIndex = curModFile->FormIDHandler.CollapsedIndex;
    const UINT8 (&CollapseTable)[256] = curModFile->FormIDHandler.CollapseTable;

    ModFile *testModFile = NULL;
    if(curRecord->IsKeyedByEditorID())
        {
        STRING RecordEditorID = curRecord->GetEditorIDKey();
        if(RecordEditorID != NULL)
            {
            for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                {
                testModFile = range.first->second->GetParentMod();
                if(testModFile->Flags.IsInLoadOrder || testModFile->Flags.IsIgnoreAbsentMasters)
                    if(CollapseTable[testModFile->FormIDHandler.ExpandedIndex] != curCollapsedIndex)
                        sortedConflicts.push_back(std::make_pair(testModFile, range.first->second));
                }
            }
        }
    else
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
            {
            testModFile = range.first->second->GetParentMod();
            if(testModFile->Flags.IsInLoadOrder || testModFile->Flags.IsIgnoreAbsentMasters)
                if(CollapseTable[testModFile->FormIDHandler.ExpandedIndex] != curCollapsedIndex)
                    sortedConflicts.push_back(std::make_pair(testModFile, range.first->second));
            }
        }

    UINT32 y = (UINT32)sortedConflicts.size();
    if(y)
        {
        std::sort(sortedConflicts.begin(), sortedConflicts.end(), compModRecordPair);
        for(UINT32 x = 0; x < y; ++x)
            RecordIDs[x] = sortedConflicts[x].second;
        sortedConflicts.clear();
        }
    return y;
    }

UINT32 Collection::NextFreeExpandedFormID(ModFile *&curModFile, UINT32 depth)
    {
    UINT32 curFormID = curModFile->FormIDHandler.NextExpandedFormID();
    FormID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.equal_range(curFormID) : FormID_ModFile_Record.equal_range(curFormID);
    //FormID doesn't exist in any mod, so it's free for use
    if(range.first == range.second)
        return curFormID;
    //The formID already exists, so try again (either in that mod, or being injected into that mod)
    //Wrap around and check for any freed formIDs until they're all checked. Unlikely to ever occur.
    return (depth < 0x00FFFFFF) ? NextFreeExpandedFormID(curModFile, ++depth) : 0;
    }

Record * Collection::CreateRecord(ModFile *&curModFile, const UINT32 &RecordType, FORMID RecordFormID, STRING const &RecordEditorID, const FORMID &ParentFormID, UINT32 CreateFlags)
    {
    if(!curModFile->Flags.IsInLoadOrder)
        {
        printer("CreateRecord: Error - Unable to create any records in mod \"%s\". It is not in the load order.\n", curModFile->ModName);
        return NULL;
        }

    CreateRecordOptions options(CreateFlags);
    Record *DummyRecord = NULL;
    Record *ParentRecord = NULL;

    if((RecordFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        RecordFormID &= 0x00FFFFFF;

    //See if the requested record already exists
    if(RecordFormID != 0)
        LookupRecord(curModFile, RecordFormID, DummyRecord);
    else if(RecordEditorID != NULL)
        LookupRecord(curModFile, RecordEditorID, DummyRecord);

    if(DummyRecord != NULL)
        return DummyRecord;

    //Lookup the required data, and ensure it exists
    if(ParentFormID)
        {
        LookupRecord(curModFile, ParentFormID, ParentRecord);
        if(ParentRecord == NULL)
            {
            printer("CreateRecord: Error - Unable to locate parent record (%08X). It does not exist in \"%s\".\n", ParentFormID, curModFile->ModName);
            return NULL;
            }
        }

    //Create the new record
    Record *curRecord = curModFile->CreateRecord(RecordType, RecordEditorID, DummyRecord, ParentRecord, options);
    if(curRecord == NULL)
        {
        printer("CreateRecord: Error - Unable to create record of type \"%c%c%c%c\" in mod \"%s\". An unknown error occurred.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], curModFile->ModName);
        return NULL;
        }

    //See if an existing record was returned instead of a new record
    if(options.ExistingReturned)
        return curRecord;

    //Assign the new record a formID
    //Ideally, if keyed by editor id, assign a new formID so that FormIDMasterUpdater doesn't add unneeded masters
    //curRecord->formID = (RecordFormID == 0 || curRecord->IsKeyedByEditorID()) ? NextFreeExpandedFormID(curModFile) : RecordFormID;

    //Trying to keep existing formID if possible to make TES4Edit happy
    // and so future undeleting of EditorID keyed records has a chance of working
    curRecord->formID = RecordFormID == 0 ? NextFreeExpandedFormID(curModFile) : RecordFormID;

    //Then the destination mod's tables get used so that they can be updated
    FormIDMasterUpdater checker(curModFile->FormIDHandler);
    checker.Accept(curRecord->formID);
    //curRecord->VisitFormIDs(checker); //Shouldn't be needed unless a record defaults to having formIDs set (none do atm)

    //Index the new record
    RecordIndexer indexer(curModFile, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);
    indexer.Accept(curRecord);

    return curRecord;
    }

Record * Collection::CopyRecord(Record *&curRecord, ModFile *&DestModFile, const FORMID &DestParentFormID, FORMID DestRecordFormID, STRING const &DestRecordEditorID, UINT32 CreateFlags)
    {
    ModFile *curModFile = curRecord->GetParentMod();
    if(!curModFile->Flags.IsInLoadOrder && !curModFile->Flags.IsIgnoreAbsentMasters)
        {
        printer("CopyRecord: Error - Unable to copy any records from source mod \"%s\". It is not in the load order and may require absent masters.\n", curModFile->ModName);
        return NULL;
        }

    CreateRecordOptions options(CreateFlags);
    Record *ParentRecord = NULL;
    Record *RecordCopy = NULL;

    if(options.SetAsOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        if(curRecord->IsKeyedByEditorID())
            LookupRecord(DestModFile, DestRecordEditorID ? DestRecordEditorID : curRecord->GetEditorIDKey(), RecordCopy);
        else
            LookupRecord(DestModFile, DestRecordFormID ? DestRecordFormID : curRecord->formID, RecordCopy);
        }
    else if(DestRecordFormID != 0)
        {
        //If the objectID of a formID is less than END_HARDCODED_IDS, then it doesn't use the modIndex portion
        //instead, it "belongs" to the engine, and they all override each other
        if((DestRecordFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
            DestRecordFormID &= 0x00FFFFFF;

        //See if its trying to copy a record that already exists in the destination mod
        if(curRecord->IsKeyedByEditorID())
            LookupRecord(DestModFile, DestRecordEditorID ? DestRecordEditorID : curRecord->GetEditorIDKey(), RecordCopy);
        else
            LookupRecord(DestModFile, DestRecordFormID, RecordCopy);
        }
    else if(curRecord->IsKeyedByEditorID())
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(DestModFile, DestRecordEditorID ? DestRecordEditorID : curRecord->GetEditorIDKey(), RecordCopy);
        }

    if(RecordCopy != NULL)
        return RecordCopy;

    if(DestParentFormID)
        {
        //See if the parent record already exists in the destination mod
        LookupRecord(DestModFile, DestParentFormID, ParentRecord);
        if(ParentRecord == NULL)
            {
            ModFile *ParentModFile = NULL;
            //If it doesn't, try and create it.
            if(options.CopyWinningParent)
                LookupWinningRecord(DestParentFormID, ParentModFile, ParentRecord);
            else
                LookupRecord(curModFile, DestParentFormID, ParentRecord);
            if(ParentRecord == NULL)
                {
                printer("CopyRecord: Error - Unable to locate destination parent record (%08X). It does not exist in \"%s\" or \"%s\".\n", DestParentFormID, DestModFile->ModName, curModFile->ModName);
                return NULL;
                }
            ParentRecord = CopyRecord(ParentRecord, DestModFile, ParentRecord->GetParentRecord() != NULL ? ParentRecord->GetParentRecord()->formID : 0, 0, 0, options.GetFlags());
            if(ParentRecord == NULL)
                {
                printer("CopyRecord: Error - Unable to copy missing destination parent record (%08X). It does not exist in \"%s\", and there was an error copying it from \"%s\".\n", DestParentFormID, DestModFile->ModName, curModFile->ModName);
                return NULL;
                }
            }
        }

    if(curModFile == DestModFile && options.SetAsOverride)
        {
        printer("CopyRecord: Error - Unable to copy (%08X) as an override record. Source and destination mods \"%s\" are the same.\n", curRecord->formID, curModFile->ModName);
        return NULL;
        }

    if(!DestModFile->Flags.IsInLoadOrder && !options.SetAsOverride)
        {
        printer("CopyRecord: Error - Unable to copy (%08X) as a new record. Destination \"%s\" is not in the load order.\n", curRecord->formID, DestModFile->ModName);
        return NULL;
        }

    //Create the record copy
    RecordCopy = DestModFile->CreateRecord(curRecord->GetType(), DestRecordEditorID, curRecord, ParentRecord, options);
    if(RecordCopy == NULL)
        {
        printer("CopyRecord: Error - Unable to create the copied record (%08X). An unknown error occurred when copying the record from \"%s\" to \"%s\".\n", curRecord->formID, DestModFile->ModName, curModFile->ModName);
        return NULL;
        }

    //See if an existing record was returned instead of the requested copy
    if(options.ExistingReturned)
        return RecordCopy;

    //Give the record a new formID if it isn't an override record
    if(!options.SetAsOverride)
        RecordCopy->formID = DestRecordFormID ? DestRecordFormID : NextFreeExpandedFormID(DestModFile);
    //DPRINT("Copied %08X from %s to %s", RecordCopy->formID, curRecord->GetParentMod()->FileName, DestModFile->FileName);

    //Ideally, assign the formID to the destination mod so that FormIDMasterUpdater doesn't add unneeded masters
    //else if(RecordCopy->IsKeyedByEditorID())
    //    RecordCopy->formID = NextFreeExpandedFormID(DestModFile);
    //Trying to keep existing formID if possible to make TES4Edit happy
    // and so future undeleting of EditorID keyed records has a chance of working

    //See if the destination mod masters need updating
    //Ensure the record has been fully read
    //Uses the source mod's formID resolution tables
    RecordReader reader(curModFile->FormIDHandler, Expanders);
    reader.Accept(RecordCopy);

    //Then the destination mod's tables get used so that they can be updated
    FormIDMasterUpdater checker(DestModFile->FormIDHandler);
    checker.Accept(RecordCopy->formID);
    RecordCopy->VisitFormIDs(checker);

    //Index the record
    RecordIndexer indexer(DestModFile, DestModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, DestModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);
    indexer.Accept(RecordCopy);

    if(reader.GetResult()) //If the record was read, go ahead and unload it
        RecordCopy->Unload();
    return RecordCopy;
    }

SINT32 Collection::CleanModMasters(ModFile *curModFile)
    {
    if(!curModFile->Flags.IsInLoadOrder)
        {
        printer("CleanModMasters: Error - Unable to clean \"%s\"'s masters. It is not in the load order.\n", curModFile->ModName);
        return NULL;
        }

    RecordMasterCollector collector(curModFile->FormIDHandler, Expanders);
    curModFile->VisitAllRecords(collector);

    UINT32 cleaned = 0;
    for(SINT32 ListIndex = curModFile->TES4.MAST.size() - 1; ListIndex >= 0 ; --ListIndex)
        {
        if(collector.collector.UsedTable[ListIndex] == 0)
            {
            delete []curModFile->TES4.MAST[ListIndex];
            curModFile->TES4.MAST.erase(curModFile->TES4.MAST.begin() + ListIndex);
            cleaned++;
            }
        }
    if(cleaned > 0)
        curModFile->FormIDHandler.UpdateFormIDLookup();
    return cleaned;
    }

SINT32 Collection::SetIDFields(Record *&RecordID, FORMID FormID, STRING const &EditorID)
    {
    ModFile *curModFile = RecordID->GetParentMod();

    if((FormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        FormID &= 0x00FFFFFF;
    bool bChangingFormID = RecordID->formID != FormID;
    bool bChangingEditorID = false;
    STRING RecordEditorID = RecordID->GetEditorIDKey();
    if(RecordEditorID == NULL)
        {
        if(EditorID != NULL)
            bChangingEditorID = true;
        }
    else
        {
        if(EditorID == NULL)
            bChangingEditorID = true;
        else if(cmps(RecordEditorID, EditorID) != 0)
            bChangingEditorID = true;
        }

    //Not allowed to set the FormID to 0
    bChangingFormID = bChangingFormID && FormID != 0;
    //Not allowed to delete the EditorID if the record is keyed by it
    if(RecordID->IsKeyedByEditorID())
        bChangingEditorID = bChangingEditorID && EditorID != NULL;

    if(!(bChangingFormID || bChangingEditorID))
        return -1;

    Record *curRecord = NULL;

    //If the FormID is already in use by the mod, do nothing.
    if(bChangingFormID)
        LookupRecord(curModFile, FormID, curRecord);

    if(curRecord != NULL)
        {
        printer("SetRecordIDs: Error - Unable to set the new record ids (%08X, %s) on record (%08X, %s) in mod \"%s\". The formID is already in use.\n", FormID, EditorID, curRecord->formID, curRecord->GetEditorIDKey(), curModFile->ModName);
        return -1;
        }

    //If the EditorID is already in use by the mod, do nothing.
    //This only cares about records keyed by editorID since they'd get the most confused
    if(bChangingEditorID && EditorID != NULL)
        LookupRecord(curModFile, EditorID, curRecord);

    if(curRecord != NULL)
        {
        printer("SetRecordIDs: Error - Unable to set the new record ids (%08X, %s) on record (%08X, %s) in mod \"%s\". The EditorID is already in use.\n", FormID, EditorID, curRecord->formID, curRecord->GetEditorIDKey(), curModFile->ModName);
        return -1;
        }

    //De-index the record
    if(bChangingFormID || (bChangingEditorID && RecordID->IsKeyedByEditorID()))
        {
        RecordDeindexer deindexer(RecordID);
        deindexer.Accept(RecordID);
        if(deindexer.GetCount() == 0)
            {
            printer("SetRecordIDs: Error - Unable to set the new record ids (%08X, %s) on record (%08X, %s) in mod \"%s\". Unable to deindex the record.\n", FormID, EditorID, RecordID->formID, RecordID->GetEditorIDKey(), curModFile->ModName);
            return -1;
            }
        }

    //Update the formID
    if(bChangingFormID)
        {
        RecordID->formID = FormID;
        FormIDMasterUpdater checker(curModFile->FormIDHandler);
        checker.Accept(RecordID->formID);
        }

    //Update the editorID
    if(bChangingEditorID)
        {
        //Ensure the record is fully loaded, otherwise any changes could be lost when the record is later loaded
        RecordReader reader(curModFile->FormIDHandler, Expanders);
        reader.Accept(RecordID);
        RecordID->SetEditorIDKey(EditorID);
        RecordID->IsChanged(true);
        }

    //Re-index the record
    if(bChangingFormID || (bChangingEditorID && RecordID->IsKeyedByEditorID()))
        {
        RecordIndexer indexer(curModFile, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);
        indexer.Accept(RecordID);
        }
    return (bChangingFormID || bChangingEditorID) ? 1 : -1;
    }

RecordDeindexer::RecordDeindexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map):
    RecordOp(),
    EditorID_ModFile_Record(_EditorID_Map),
    FormID_ModFile_Record(_FormID_Map)
    {
    //
    }

RecordDeindexer::RecordDeindexer(Record *RecordID):
    RecordOp(),
    EditorID_ModFile_Record(RecordID->GetParentMod()->Flags.IsExtendedConflicts ? RecordID->GetParentMod()->Parent->ExtendedEditorID_ModFile_Record: RecordID->GetParentMod()->Parent->EditorID_ModFile_Record),
    FormID_ModFile_Record(RecordID->GetParentMod()->Flags.IsExtendedConflicts ? RecordID->GetParentMod()->Parent->ExtendedFormID_ModFile_Record: RecordID->GetParentMod()->Parent->FormID_ModFile_Record)
    {
    //
    }

RecordDeindexer::RecordDeindexer(ModFile *ModID):
    RecordOp(),
    EditorID_ModFile_Record(ModID->Flags.IsExtendedConflicts ? ModID->Parent->ExtendedEditorID_ModFile_Record: ModID->Parent->EditorID_ModFile_Record),
    FormID_ModFile_Record(ModID->Flags.IsExtendedConflicts ? ModID->Parent->ExtendedFormID_ModFile_Record: ModID->Parent->FormID_ModFile_Record)
    {
    //
    }

RecordDeindexer::~RecordDeindexer()
    {
    //
    }

bool RecordDeindexer::Accept(Record *&curRecord)
    {
    if(curRecord != NULL)
        {
        //De-Index the record
        if(curRecord->formID != 0)
            {
            for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
                if(range.first->second == curRecord)
                    {
                    FormID_ModFile_Record.erase(range.first);
                    ++count;
                    result = true;
                    break;
                    }
            }
        if(curRecord->IsKeyedByEditorID() && curRecord->GetEditorIDKey() != NULL) //Should only be null on deleted records that weren't able to be undeleted
            {
            for(EditorID_Range range = EditorID_ModFile_Record.equal_range(curRecord->GetEditorIDKey()); range.first != range.second; ++range.first)
                if(range.first->second == curRecord)
                    {
                    EditorID_ModFile_Record.erase(range.first);
                    ++count;
                    result = true;
                    break;
                    }
            }
        }
    return false;
    }

IdenticalToMasterRetriever::IdenticalToMasterRetriever(ModFile *ModID):
    RecordOp(),
    reader(ModID->FormIDHandler, ModID->Parent->Expanders),
    MasterIndex(ModID->FormIDHandler.ExpandedIndex),
    LoadOrder255(ModID->Parent->LoadOrder255),
    identical_records(ModID->Parent->identical_records),
    EditorID_ModFile_Record(ModID->Flags.IsExtendedConflicts ? ModID->Parent->ExtendedEditorID_ModFile_Record: ModID->Parent->EditorID_ModFile_Record),
    FormID_ModFile_Record(ModID->Flags.IsExtendedConflicts ? ModID->Parent->ExtendedFormID_ModFile_Record: ModID->Parent->FormID_ModFile_Record),
    Expanders(ModID->Parent->Expanders)
    {
    //
    }

IdenticalToMasterRetriever::~IdenticalToMasterRetriever()
    {
    //
    }

bool IdenticalToMasterRetriever::Accept(Record *&curRecord)
    {
    UINT8 ModIndex = (UINT8)(curRecord->formID >> 24);

    //The record has no master
    if(ModIndex == MasterIndex)
        return false;

    Record *master_record = NULL;
    ModFile *master_mod = LoadOrder255[ModIndex];
    if(curRecord->IsKeyedByEditorID() && curRecord->GetEditorIDKey() != NULL) //Should only be null on deleted records (they'll get indexed after being undeleted)
        {
        for(EditorID_Range range = EditorID_ModFile_Record.equal_range(curRecord->GetEditorIDKey()); range.first != range.second; ++range.first)
            if(range.first->second->GetParentMod() == master_mod)
                {
                master_record = range.first->second;
                break;
                }
        }
    else if(curRecord->formID != 0)
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
            if(range.first->second->GetParentMod() == master_mod)
                {
                master_record = range.first->second;
                break;
                }
        }

    if(master_record == NULL)
        return false;

    RecordReader read_other(master_mod->FormIDHandler, Expanders);

    if(curRecord->master_equality(master_record, reader, read_other, identical_records))
        identical_records.insert(curRecord);

    return false;
    }

RecordReader::RecordReader(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    expander(_FormIDHandler.ExpandTable, _FormIDHandler.FileStart, _FormIDHandler.FileEnd),
    Expanders(_Expanders)
    {
    //
    }

RecordReader::RecordReader(Record *RecordID):
    RecordOp(),
    expander(RecordID->GetParentMod()->FormIDHandler.ExpandTable, RecordID->GetParentMod()->FormIDHandler.FileStart, RecordID->GetParentMod()->FormIDHandler.FileEnd),
    Expanders(RecordID->GetParentMod()->Parent->Expanders)
    {
    //
    }

RecordReader::RecordReader(ModFile *ModID):
    RecordOp(),
    expander(ModID->FormIDHandler.ExpandTable, ModID->FormIDHandler.FileStart, ModID->FormIDHandler.FileEnd),
    Expanders(ModID->Parent->Expanders)
    {
    //
    }

RecordReader::~RecordReader()
    {
    //
    }

bool RecordReader::Accept(Record *&curRecord)
    {
    result = curRecord->Read();
    if(result)
        {
        if(curRecord->IsValid(expander))
            curRecord->VisitFormIDs(expander);
        else
            {
            SINT32 index = -1;
            for(UINT32 x = 0; x < Expanders.size(); ++x)
                if(curRecord->IsValid(*Expanders[x]))
                    {
                    //if(index != -1)
                    //    printer("Multiple 'Correct' expanders found! Using last one found (likely incorrect unless lucky)\n");
                    index = x;
                    break;
                    }
            if(index == -1)
                {
                printer("Unable to find the correct expander!\n");
                curRecord->VisitFormIDs(expander);
                }
            else
                curRecord->VisitFormIDs(*Expanders[index]);
            }
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

RecordFormIDMapper::FormIDMapper::FormIDMapper(std::map<FORMID, std::vector<Record *> > &_formID_users):
    FormIDOp(),
    formID_users(_formID_users),
    curRecord(NULL)
    {
    //
    }

RecordFormIDMapper::FormIDMapper::~FormIDMapper()
    {
    //
    }

bool RecordFormIDMapper::FormIDMapper::Accept(UINT32 &curFormID)
    {
    formID_users[curFormID].push_back(curRecord);
    return stop;
    }

bool RecordFormIDMapper::FormIDMapper::AcceptMGEF(UINT32 &curMgefCode)
    {
    formID_users[curMgefCode].push_back(curRecord);
    return stop;
    }

RecordFormIDMapper::RecordFormIDMapper(std::map<FORMID, std::vector<Record *> > &_formID_users, FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    reader(_FormIDHandler, _Expanders),
    mapper(_formID_users)
    {
    //
    }

RecordFormIDMapper::~RecordFormIDMapper()
    {
    //
    }

bool RecordFormIDMapper::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    reader.Accept(curRecord);

    //Perform the map
    mapper.curRecord = curRecord;
    stop = curRecord->VisitFormIDs(mapper);

    //If the record was read, but not changed, unload it again
    if(reader.GetResult() && !curRecord->IsChanged())
        curRecord->Unload();

    return stop;
    }

RecordMasterCollector::FormIDMasterCollector::FormIDMasterCollector(UINT8 (&_CollapseTable)[256]):
    FormIDOp(),
    CollapseTable(_CollapseTable)
    {
    memset(&UsedTable[0], 0x00, sizeof(UsedTable));
    }

RecordMasterCollector::FormIDMasterCollector::~FormIDMasterCollector()
    {
    //
    }

bool RecordMasterCollector::FormIDMasterCollector::Accept(UINT32 &curFormID)
    {
    //Any formID <= 0x800 is hardcoded in the engine and doesn't 'belong' to a mod.
    if((curFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        return stop;
    UsedTable[CollapseTable[curFormID >> 24]] = 1;
    return stop;
    }

bool RecordMasterCollector::FormIDMasterCollector::AcceptMGEF(UINT32 &curMgefCode)
    {
    UsedTable[CollapseTable[curMgefCode & 0x000000FF]] = 1;
    return stop;
    }

RecordMasterCollector::RecordMasterCollector(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    reader(_FormIDHandler, _Expanders),
    collector(_FormIDHandler.CollapseTable)
    {
    //
    }

RecordMasterCollector::~RecordMasterCollector()
    {
    //
    }

bool RecordMasterCollector::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    reader.Accept(curRecord);

    collector.Accept(curRecord->formID);
    curRecord->VisitFormIDs(collector);

    return stop;
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