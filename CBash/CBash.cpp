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
// CBash.cpp
#include "CBash.h"
#include "Collection.h"
#include <vector>
//#include "mmgr.h"

static std::vector<Collection *> Collections;
//static std::vector<Iterator *> Iterators;

unsigned long GetMajor()
    {
    return MAJOR_VERSION;
    }

unsigned long GetMinor()
    {
    return MINOR_VERSION;
    }

unsigned long GetRevision()
    {
    return REVISION_VERSION;
    }
////////////////////////////////////////////////////////////////////////
void ValidatePointer(const void *testPointer)
    {
    if(testPointer == NULL)
        throw Ex_NULL();
    }

void ValidateCollection(const unsigned long CollectionIndex)
    {
    if(CollectionIndex >= Collections.size())
        throw Ex_INVALIDINDEX();
    if(Collections[CollectionIndex] == NULL)
        throw Ex_INVALIDINDEX();
    }

void ValidateFID(const unsigned long recordFID)
    {
    if(recordFID == 0)
        throw Ex_INVALIDFORMID();
    }

int NewCollection(const char *ModsPath)
    {
    try
        {
        ValidatePointer(ModsPath);
        for(unsigned long p = 0; p < Collections.size(); ++p)
            {
            if(Collections[p] == NULL)
                {
                Collections[p] = new Collection(ModsPath);
                return p;
                }
            }
        Collections.push_back(new Collection(ModsPath));
        }
    catch(std::exception &ex)
        {
        printf("Error creating collection\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error creating collection\n  Unhandled Exception\n");
        return -1;
        }
    return (int)Collections.size() - 1;
    }

#pragma warning( push )
#pragma warning( disable : 4101 ) //Disable warning about deliberately unused variable (Ex_INVALIDINDEX &ex)
int DeleteCollection(const unsigned long CollectionIndex)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        Close(CollectionIndex);
        delete Collections[CollectionIndex];
        Collections[CollectionIndex] = NULL;
        for(unsigned long p = 0; p < Collections.size(); ++p)
            {
            if(Collections[p] != NULL)
                return 0;
            }
        Collections.clear();
        //Collections.erase(Collections.begin() + CollectionIndex);
        //m_dumpMemoryReport("AfterDelete.txt", true);
        }
    catch(Ex_INVALIDINDEX &ex) {} //Silently fail if deleting an already deleted collection
    catch(std::exception &ex)
        {
        printf("Error erasing collection at pos %i\n  %s\n", CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error erasing collection at pos %i\n  Unhandled Exception\n", CollectionIndex);
        return -1;
        }
    return 0;
    }
#pragma warning( pop )

////////////////////////////////////////////////////////////////////////
int AddMod(const unsigned long CollectionIndex, const char *ModName, unsigned long SettingFlags)
    {
    ModFlags settings(SettingFlags);

    int status = 0;
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        status = Collections[CollectionIndex]->AddMod(ModName, settings);
        }
    catch(std::exception &ex)
        {
        printf("Error adding mod:%s\n  %s\n", ModName, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error adding mod:%s\n  Unhandled Exception\n", ModName);
        return -1;
        }
    return status;
    }

int MinimalLoad(const unsigned long CollectionIndex, const bool LoadMasters)
    {
    try
        {
        //printf("MinimalLoad: %u\n", CollectionIndex);
        ValidateCollection(CollectionIndex);
        Collections[CollectionIndex]->Load(LoadMasters, false);
        Collections[CollectionIndex]->IndexRecords(false);
        }
    catch(std::exception &ex)
        {
        printf("MinimalLoad: Error loading records\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("MinimalLoad: Error loading records\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }

int FullLoad(const unsigned long CollectionIndex, const bool LoadMasters)
    {
    try
        {
        //printf("FullLoad: %u\n", CollectionIndex);
        ValidateCollection(CollectionIndex);
        Collections[CollectionIndex]->Load(LoadMasters, true);
        Collections[CollectionIndex]->IndexRecords(true);
        }
    catch(std::exception &ex)
        {
        printf("FullLoad: Error loading records\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("FullLoad: Error loading records\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int IsModEmpty(const unsigned long CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->IsEmpty(ModName);
        }
    catch(std::exception &ex)
        {
        printf("IsModEmpty: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("IsModEmpty: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned long GetNumNewRecordTypes(const unsigned long CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumNewRecordTypes(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumNewRecordTypes: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumNewRecordTypes: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

void GetNewRecordTypes(const unsigned long CollectionIndex, char *ModName, unsigned long const **RecordTypes)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetNewRecordTypes(ModName, RecordTypes);
        }
    catch(std::exception &ex)
        {
        printf("GetNewRecordTypes: Error\n  %s\n", ex.what());
        }
    catch(...)
        {
        printf("GetNewRecordTypes: Error\n  Unhandled Exception\n");
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
int CleanMasters(const unsigned long CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CleanMasters(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CleanMasters: Error loading records\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CleanMasters: Error loading records\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

int SafeSaveMod(const unsigned long CollectionIndex, char *curFileName, bool CloseMod)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(curFileName);
        Collections[CollectionIndex]->SafeSaveMod(curFileName, CloseMod);
        if(CloseMod)
            DeleteCollection(CollectionIndex);
        }
    catch(std::exception &ex)
        {
        printf("Error safe saving mod:%s\n  %s\n", curFileName, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error safe saving mod:%s\n  Unhandled Exception\n", curFileName);
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int LoadRecord(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->LoadRecord(ModName, recordFID);
        }
    catch(std::exception &ex)
        {
        printf("Error loading record: %08X from mod:%s in collection: %i\n  %s\n", recordFID, ModName, CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error loading record: %08X from mod:%s in collection: %i\n  Unhandled Exception\n", recordFID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int UnloadRecord(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->UnloadRecord(ModName, recordFID);
        }
    catch(std::exception &ex)
        {
        printf("Error unloading record: %08X from mod:%s in collection: %i\n  %s\n", recordFID, ModName, CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error unloading record: %08X from mod:%s in collection: %i\n  Unhandled Exception\n", recordFID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int UnloadModFile(const unsigned long CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->UnloadModFile(ModName);
        }
    catch(std::exception &ex)
        {
        printf("Error unloading records from mod:%s in collection: %i\n  %s\n", ModName, CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error unloading records from mod:%s in collection: %i\n  Unhandled Exception\n", ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int UnloadAll(const unsigned long CollectionIndex)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        Collections[CollectionIndex]->UnloadAll();
        }
    catch(std::exception &ex)
        {
        printf("Error unloading all records from collection: %i\n  %s\n", CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error unloading all records from collection: %i\n  Unhandled Exception\n", CollectionIndex);
        return -1;
        }
    return 0;
    }

int DeleteRecord(const unsigned long CollectionIndex, char *ModName, unsigned long RecordFID, char *RecordEditorID, unsigned long ParentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->DeleteRecord(ModName, RecordFID, RecordEditorID, ParentFID);
        }
    catch(std::exception &ex)
        {
        printf("Error deleting record: %08X from mod:%s in collection: %i\n  %s\n", RecordFID, ModName, CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error deleting record: %08X from mod:%s in collection: %i\n  Unhandled Exception\n", RecordFID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int Close(const unsigned long CollectionIndex)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        Collections[CollectionIndex]->Close();
        }
    catch(std::exception &ex)
        {
        printf("Error closing collection at %i\n  %s\n", CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error closing collection at %i\n  Unhandled Exception\n", CollectionIndex);
        return -1;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
unsigned long GetNumMods(const unsigned long CollectionIndex)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        return Collections[CollectionIndex]->GetNumMods();
        }
    catch(std::exception &ex)
        {
        printf("GetNumMods: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("GetNumMods: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }

void GetMods(const unsigned long CollectionIndex, char **ModNames)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        Collections[CollectionIndex]->GetMods(ModNames);
        }
    catch(std::exception &ex)
        {
        printf("GetMods: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetMods: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
unsigned long SetRecordFormID(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, unsigned long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->SetRecordFormID(ModName, recordFID, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("SetRecordFormID: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("SetRecordFormID: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }


char * GetModName(const unsigned long CollectionIndex, const unsigned long iIndex)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        return Collections[CollectionIndex]->GetModName(iIndex);
        }
    catch(std::exception &ex)
        {
        printf("GetModName: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("GetModName: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }

unsigned long ModIsFake(const unsigned long CollectionIndex, const unsigned long iIndex)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        return Collections[CollectionIndex]->ModIsFake(iIndex);
        }
    catch(std::exception &ex)
        {
        printf("ModIsFake: Error\n  %s\n", ex.what());
        return 1;
        }
    catch(...)
        {
        printf("ModIsFake: Error\n  Unhandled Exception\n");
        return 1;
        }
    return 1;
    }

unsigned long GetCorrectedFID(const unsigned long CollectionIndex, char *ModName, unsigned long recordObjectID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetCorrectedFID(ModName, recordObjectID);
        }
    catch(std::exception &ex)
        {
        printf("Error getting corrected formID: %08x from mod:%s in collection: %i\n  %s\n", recordObjectID, ModName, CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error getting corrected formID: %08x from mod:%s in collection: %i\n  Unhandled Exception\n", recordObjectID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

unsigned long UpdateAllReferences(const unsigned long CollectionIndex, char *ModName, unsigned long origFormID, unsigned long newFormID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->UpdateReferences(ModName, origFormID, newFormID);
        }
    catch(std::exception &ex)
        {
        printf("UpdateAllReferences: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("UpdateAllReferences: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned long GetNumReferences(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, unsigned long referenceFormID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumReferences(ModName, recordFID, referenceFormID);
        }
    catch(std::exception &ex)
        {
        printf("GetNumReferences: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumReferences: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned long UpdateReferences(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, unsigned long origFormID, unsigned long newFormID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->UpdateReferences(ModName, recordFID, origFormID, newFormID);
        }
    catch(std::exception &ex)
        {
        printf("UpdateReferences: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("UpdateReferences: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int IsFIDWinning(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, bool ignoreScanned)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->IsWinning(ModName, recordFID, ignoreScanned);
        }
    catch(std::exception &ex)
        {
        printf("IsFIDWinning: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("IsFIDWinning: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

int IsGMSTWinning(const unsigned long CollectionIndex, char *ModName, char *recordEDID, bool ignoreScanned)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        return Collections[CollectionIndex]->IsWinning(ModName, recordEDID, ignoreScanned);
        }
    catch(std::exception &ex)
        {
        printf("IsGMSTWinning: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("IsGMSTWinning: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

int GetNumFIDConflicts(const unsigned long CollectionIndex, unsigned long recordFID, bool ignoreScanned)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        return Collections[CollectionIndex]->GetNumFIDConflicts(recordFID, ignoreScanned);
        }
    catch(std::exception &ex)
        {
        printf("GetNumFIDConflict: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumFIDConflict: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

void GetFIDConflicts(const unsigned long CollectionIndex, unsigned long recordFID, bool ignoreScanned, char **ModNames)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        Collections[CollectionIndex]->GetFIDConflicts(recordFID, ignoreScanned, ModNames);
        return;
        }
    catch(std::exception &ex)
        {
        printf("GetFIDConflicts: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetFIDConflicts: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }

int GetNumGMSTConflicts(const unsigned long CollectionIndex, char *recordEDID, bool ignoreScanned)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(recordEDID);
        return Collections[CollectionIndex]->GetNumGMSTConflicts(recordEDID, ignoreScanned);
        }
    catch(std::exception &ex)
        {
        printf("GetNumGMSTConflicts: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumGMSTConflicts: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

void GetGMSTConflicts(const unsigned long CollectionIndex, char *recordEDID, bool ignoreScanned, char **ModNames)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(recordEDID);
        Collections[CollectionIndex]->GetGMSTConflicts(recordEDID, ignoreScanned, ModNames);
        return;
        }
    catch(std::exception &ex)
        {
        printf("GetGMSTConflicts: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetGMSTConflicts: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
unsigned long GetNumRecords(const unsigned long CollectionIndex, char *ModName, const unsigned long RecordType)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumRecords(ModName, RecordType);
        }
    catch(std::exception &ex)
        {
        printf("GetNumRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

void GetRecordFormIDs(const unsigned long CollectionIndex, char *ModName, const unsigned long RecordType, unsigned long **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetRecordFormIDs(ModName, RecordType, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetRecordFormIDs: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetRecordFormIDs: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }

void GetRecordEditorIDs(const unsigned long CollectionIndex, char *ModName, const unsigned long RecordType, char **RecordEIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetRecordEditorIDs(ModName, RecordType, RecordEIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetRecordEditorIDs: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetRecordEditorIDs: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int GetTES4FieldType(const unsigned long CollectionIndex, char *ModName, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetTES4FieldType(ModName, Field);
        }
    catch(std::exception &ex)
        {
        printf("GetNumEFSHRecords: Error\n  %s\n", ex.what());
        return UNKNOWN_FIELD;
        }
    catch(...)
        {
        printf("GetNumEFSHRecords: Error\n  Unhandled Exception\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

unsigned long GetTES4FieldArraySize(const unsigned long CollectionIndex, char *ModName, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetTES4FieldArraySize(ModName, Field);
        }
    catch(std::exception &ex)
        {
        printf("GetTES4FieldArraySize: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetTES4FieldArraySize: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

void GetTES4FieldArray(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, void **FieldValues)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetTES4FieldArray(ModName, Field, FieldValues);
        }
    catch(std::exception &ex)
        {
        printf("GetTES4FieldArray: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetTES4FieldArray: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }

void * ReadTES4Field(const unsigned long CollectionIndex, char *ModName, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->ReadTES4Field(ModName, Field);
        }
    catch(std::exception &ex)
        {
        printf("ReadTES4Field: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("ReadTES4Field: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }

////////////////////////////////////////////////////////////////////////
int SetTES4FieldStr(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, char *FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %s\n  %s\n", ModName, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %s\n  Unhandled Exception\n", ModName, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetTES4FieldStrA(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, char **FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValues:\n", ModName, Field);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }

int SetTES4FieldUI(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, unsigned long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %i\n  %s\n", ModName, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetTES4FieldF(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, float FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %f\n  %s\n", ModName, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %f\n  Unhandled Exception\n", ModName, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetTES4FieldR(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, unsigned char *FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nRaw Value:\n", ModName, Field);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteTES4Field(const unsigned long CollectionIndex, char *ModName, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->DeleteTES4Field(ModName, Field);
        }
    catch(std::exception &ex)
        {
        printf("Error deleting:\nMod: %s\nRecord: TES4\nField: %i\n  %s\n", ModName, Field, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error deleting:\nMod: %s\nRecord: TES4\nField: %i\n  Unhandled Exception\n", ModName, Field);
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int GetGMSTFieldType(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        return Collections[CollectionIndex]->GetGMSTFieldType(ModName, recordEDID, Field);
        }
    catch(std::exception &ex)
        {
        printf("GetGMSTFieldType: Error\n  %s\n", ex.what());
        return UNKNOWN_FIELD;
        }
    catch(...)
        {
        printf("GetGMSTFieldType: Error\n  Unhandled Exception\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * ReadGMSTField(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        return Collections[CollectionIndex]->ReadGMSTField(ModName, recordEDID, Field);
        }
    catch(std::exception &ex)
        {
        printf("ReadGMSTField: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("ReadGMSTField: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int SetGMSTFieldStr(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field, char *FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %s\n  %s\n", ModName, recordEDID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %s\n  Unhandled Exception\n", ModName, recordEDID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetGMSTFieldI(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field, long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %i\n  %s\n", ModName, recordEDID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordEDID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetGMSTFieldUI(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field, unsigned long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %i\n  %s\n", ModName, recordEDID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordEDID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetGMSTFieldF(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field, float FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %f\n  %s\n", ModName, recordEDID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %f\n  Unhandled Exception\n", ModName, recordEDID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int DeleteGMSTField(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        Collections[CollectionIndex]->DeleteGMSTField(ModName, recordEDID, Field);
        }
    catch(std::exception &ex)
        {
        printf("Error deleting:\nMod: %s\nRecord: %s\nField: %i\n  %s\n", ModName, recordEDID, Field, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error deleting:\nMod: %s\nRecord: %s\nField: %i\n  Unhandled Exception\n", ModName, recordEDID, Field);
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int GetFIDFieldType(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDFieldType(ModName, recordFID, Field);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDFieldType: Error\n  %s\n", ex.what());
        return UNKNOWN_FIELD;
        }
    catch(...)
        {
        printf("GetFIDFieldType: Error\n  Unhandled Exception\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

int GetFIDListFieldType(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListFieldType(ModName, recordFID, subField, listField);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListFieldType: Error\n  %s\n", ex.what());
        return UNKNOWN_FIELD;
        }
    catch(...)
        {
        printf("GetFIDListFieldType: Error\n  Unhandled Exception\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

int GetFIDListX2FieldType(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField, const unsigned long listX2Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListX2FieldType(ModName, recordFID, subField, listField, listX2Field);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListX2FieldType: Error\n  %s\n", ex.what());
        return UNKNOWN_FIELD;
        }
    catch(...)
        {
        printf("GetFIDListX2FieldType: Error\n  Unhandled Exception\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

int GetFIDListX3FieldType(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField, const unsigned long listX2Field, const unsigned long listX3Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListX3FieldType(ModName, recordFID, subField, listField, listX2Field, listX3Field);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListX3FieldType: Error\n  %s\n", ex.what());
        return UNKNOWN_FIELD;
        }
    catch(...)
        {
        printf("GetFIDListX3FieldType: Error\n  Unhandled Exception\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }
////////////////////////////////////////////////////////////////////////
unsigned long GetFIDFieldArraySize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDFieldArraySize(ModName, recordFID, Field);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDFieldArraySize: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFIDFieldArraySize: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
unsigned long GetFIDListArraySize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListArraySize(ModName, recordFID, subField, listIndex, listField);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListArraySize: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFIDListArraySize: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
unsigned long GetFIDListX2ArraySize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListX2ArraySize(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListX2ArraySize: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFIDListX2ArraySize: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
unsigned long GetFIDListX3ArraySize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListX3ArraySize(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListX3ArraySize: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFIDListX3ArraySize: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
unsigned long GetFIDListSize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListSize(ModName, recordFID, Field);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListSize: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFIDListSize: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
unsigned long GetFIDListX2Size(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListX2Size(ModName, recordFID, subField, listIndex, listField);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListX2Size: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFIDListX2Size: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
unsigned long GetFIDListX3Size(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListX3Size(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListX3Size: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFIDListX3Size: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
void GetFIDFieldArray(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, void **FieldValues)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDFieldArray(ModName, recordFID, Field, FieldValues);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDFieldArray: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetFIDFieldArray: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }
void GetFIDListArray(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListArray(ModName, recordFID, subField, listIndex, listField, FieldValues);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListArray: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetFIDListArray: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }
void GetFIDListX2Array(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, void **FieldValues)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListX2Array(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValues);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListX2Array: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetFIDListX2Array: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }
void GetFIDListX3Array(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, void **FieldValues)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetFIDListX3Array(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValues);
        }
    catch(std::exception &ex)
        {
        printf("GetFIDListX3Array: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetFIDListX3Array: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
void * ReadFIDField(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->ReadFIDField(ModName, recordFID, Field);
        }
    catch(std::exception &ex)
        {
        printf("ReadFIDField: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("ReadFIDField: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }

void * ReadFIDListField(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->ReadFIDListField(ModName, recordFID, subField, listIndex, listField);
        }
    catch(std::exception &ex)
        {
        printf("ReadFIDListField: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("ReadFIDListField: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }

void * ReadFIDListX2Field(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->ReadFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        }
    catch(std::exception &ex)
        {
        printf("ReadFIDListX2Field: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("ReadFIDListX2Field: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }

void * ReadFIDListX3Field(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->ReadFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
        }
    catch(std::exception &ex)
        {
        printf("ReadFIDListX3Field: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("ReadFIDListX3Field: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }
////////////////////////////////////////////////////////////////////////
unsigned long CreateRecord(const unsigned long CollectionIndex, char *ModName, const unsigned long RecordType, unsigned long RecordFID, char *RecordEditorID, const unsigned long ParentFID, unsigned long CreateFlags)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateRecord(ModName, RecordType, RecordFID, RecordEditorID, ParentFID, CreateFlags);
        }
    catch(std::exception &ex)
        {
        printf("CreateRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned long CopyRecord(const unsigned long CollectionIndex, char *ModName, unsigned long RecordFID, char *DestModName, unsigned long DestParentFID, unsigned long CreateFlags)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(DestModName);
        return Collections[CollectionIndex]->CopyRecord(ModName, RecordFID, DestModName, DestParentFID, CreateFlags);
        }
    catch(std::exception &ex)
        {
        printf("CopyRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int SetFIDFieldC(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, signed char FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  %s\n", ModName, recordFID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  Unhandled Exception\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDFieldUC(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned char FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  %s\n", ModName, recordFID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  Unhandled Exception\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDFieldStr(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, char *FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n  %s\n", ModName, recordFID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n  Unhandled Exception\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDFieldStrA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, char **FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValues:\n", ModName, recordFID, Field);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }

int SetFIDFieldS(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, short FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDFieldUS(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned short FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDFieldI(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDFieldUI(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDFieldUIA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned long FieldValue[], unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValues:\n", ModName, recordFID, Field);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%08X\n", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int SetFIDFieldF(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, float FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n  %s\n", ModName, recordFID, Field, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n  Unhandled Exception\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDFieldR(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned char *FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nRaw Value:\n", ModName, recordFID, Field);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteFIDField(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->DeleteFIDField(ModName, recordFID, Field);
        }
    catch(std::exception &ex)
        {
        printf("Error deleting:\nMod: %s\nFormID: %08X\nField: %i\n  %s\n", ModName, recordFID, Field, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error deleting:\nMod: %s\nFormID: %08X\nField: %i\n  Unhandled Exception\n", ModName, recordFID, Field);
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int CreateFIDListElement(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateFIDListElement(ModName, recordFID, subField);
        }
    catch(std::exception &ex)
        {
        printf("CreateFIDListElement: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("CreateFIDListElement: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }
int CreateFIDListX2Element(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateFIDListX2Element(ModName, recordFID, subField, listIndex, listField);
        }
    catch(std::exception &ex)
        {
        printf("CreateFIDListX2Element: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("CreateFIDListX2Element: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }
int CreateFIDListX3Element(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateFIDListX3Element(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        }
    catch(std::exception &ex)
        {
        printf("CreateFIDListX3Element: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("CreateFIDListX3Element: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int DeleteFIDListElement(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->DeleteFIDListElement(ModName, recordFID, subField);
        }
    catch(std::exception &ex)
        {
        printf("DeleteFIDListElement: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("DeleteFIDListElement: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }
int DeleteFIDListX2Element(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->DeleteFIDListX2Element(ModName, recordFID, subField, listIndex, listField);
        }
    catch(std::exception &ex)
        {
        printf("DeleteFIDListX2Element: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("DeleteFIDListX2Element: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }
int DeleteFIDListX3Element(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->DeleteFIDListX3Element(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        }
    catch(std::exception &ex)
        {
        printf("DeleteFIDListX3Element: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("DeleteFIDListX3Element: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int SetFIDListFieldC (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, signed char FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldUC(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldStr (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, char *FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldStrA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, char **FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValues:\n", ModName, recordFID, subField);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldS (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, short FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldUS(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned short FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldI (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldUI(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListFieldUIA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue[], unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nsubField: %i\nValues:\n", ModName, recordFID, subField);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%08X\n", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }
int SetFIDListFieldF (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, float FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListFieldR (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nRaw Value:\n", ModName, recordFID, subField);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteFIDListField(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->DeleteFIDListField(ModName, recordFID, subField, listIndex, listField);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\n  %s\n", ModName, recordFID, subField, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\n  Unhandled Exception\n", ModName, recordFID, subField);
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int SetFIDListX2FieldC (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, signed char FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldUC(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned char FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldStr (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, char *FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldStrA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, char **FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValues:\n", ModName, recordFID, subField);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldS (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, short FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldUS(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned short FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldI (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListX2FieldUI(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListX2FieldF (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, float FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListX2FieldR (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned char *FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nRaw Value:\n", ModName, recordFID, subField);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteFIDListX2Field(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->DeleteFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        }
    catch(std::exception &ex)
        {
        printf("Error deleting:\nMod: %s\nFormID: %08X\nField: %i\n  %s\n", ModName, recordFID, subField, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error deleting:\nMod: %s\nFormID: %08X\nField: %i\n  Unhandled Exception\n", ModName, recordFID, subField);
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int SetFIDListX3FieldC (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, signed char FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldUC(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, unsigned char FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldStr (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, char *FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldStrA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, char **FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValues:\n", ModName, recordFID, subField);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldS (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, short FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldUS(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, unsigned short FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldI (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListX3FieldUI(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, unsigned long FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListX3FieldF (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, float FieldValue)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n  %s\n", ModName, recordFID, subField, FieldValue, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n  Unhandled Exception\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListX3FieldR (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, unsigned char *FieldValue, unsigned long nSize)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(FieldValue);
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue, nSize);
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nRaw Value:\n", ModName, recordFID, subField);
        for(unsigned long p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteFIDListX3Field(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->DeleteFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
        }
    catch(std::exception &ex)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\n  %s\n", ModName, recordFID, subField, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\n  Unhandled Exception\n", ModName, recordFID, subField);
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void Debug(const unsigned long CollectionIndex, const int debugLevel, const bool AllRecords)
    {
    if(AllRecords)
        printf("Loading all records!!!\n");
    Collections[CollectionIndex]->Debug(debugLevel, AllRecords);
    return;
    }
#endif
