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

unsigned int GetMajor()
    {
    return MAJOR_VERSION;
    }

unsigned int GetMinor()
    {
    return MINOR_VERSION;
    }

unsigned int GetRevision()
    {
    return REVISION_VERSION;
    }
////////////////////////////////////////////////////////////////////////
void ValidatePointer(const void *testPointer)
    {
    if(testPointer == NULL)
        throw Ex_NULL();
    }

void ValidateCollection(const unsigned int CollectionIndex)
    {
    if(CollectionIndex >= Collections.size())
        throw Ex_INVALIDINDEX();
    if(Collections[CollectionIndex] == NULL)
        throw Ex_INVALIDINDEX();
    }

void ValidateFID(const unsigned int recordFID)
    {
    if(recordFID == 0)
        throw Ex_INVALIDFORMID();
    }

int NewCollection(const char *ModsPath)
    {
    try
        {
        ValidatePointer(ModsPath);
        for(unsigned int p = 0; p < Collections.size(); ++p)
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
int DeleteCollection(const unsigned int CollectionIndex)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        Close(CollectionIndex);
        delete Collections[CollectionIndex];
        Collections[CollectionIndex] = NULL;
        for(unsigned int p = 0; p < Collections.size(); ++p)
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
int AddMod(const unsigned int CollectionIndex, const char *ModName, unsigned int OptionFlags)
    {
    enum optionFlags
        {
        fIsMerge             = 0x00000001,
        fIsScan              = 0x00000002,
        fIsCreateIfNotExist  = 0x00000004
        };

    int status = 0;
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        status = Collections[CollectionIndex]->AddMod(ModName, (OptionFlags & fIsMerge) != 0, (OptionFlags & fIsScan) != 0, (OptionFlags & fIsCreateIfNotExist) != 0, false);
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

int MinimalLoad(const unsigned int CollectionIndex, const bool LoadMasters)
    {
    try
        {
        //printf("MinimalLoad: %u\n", CollectionIndex);
        ValidateCollection(CollectionIndex);
        Collections[CollectionIndex]->Load(LoadMasters, false);
        Collections[CollectionIndex]->IndexRecords();
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

int FullLoad(const unsigned int CollectionIndex, const bool LoadMasters)
    {
    try
        {
        //printf("FullLoad: %u\n", CollectionIndex);
        ValidateCollection(CollectionIndex);
        Collections[CollectionIndex]->Load(LoadMasters, true);
        Collections[CollectionIndex]->IndexRecords();
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
int IsModEmpty(const unsigned int CollectionIndex, char *ModName)
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

unsigned int GetNumNewRecordTypes(const unsigned int CollectionIndex, char *ModName)
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

void GetNewRecordTypes(const unsigned int CollectionIndex, char *ModName, unsigned int const **RecordTypes)
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
int CleanMasters(const unsigned int CollectionIndex, char *ModName)
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

int SafeSaveMod(const unsigned int CollectionIndex, char *curFileName, bool CloseMod)
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
int LoadRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID)
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

int UnloadRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID)
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

int UnloadModFile(const unsigned int CollectionIndex, char *ModName)
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

int UnloadAll(const unsigned int CollectionIndex)
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

int DeleteRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->DeleteRecord(ModName, recordFID, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("Error deleting record: %08X from mod:%s in collection: %i\n  %s\n", recordFID, ModName, CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error deleting record: %08X from mod:%s in collection: %i\n  Unhandled Exception\n", recordFID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int DeleteGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        Collections[CollectionIndex]->DeleteGMSTRecord(ModName, recordEDID);
        }
    catch(std::exception &ex)
        {
        printf("Error deleting GMST record: %s from mod:%s in collection: %i\n  %s\n", recordEDID, ModName, CollectionIndex, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error deleting GMST record: %s from mod:%s in collection: %i\n  Unhandled Exception\n", recordEDID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int Close(const unsigned int CollectionIndex)
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
unsigned int GetNumMods(const unsigned int CollectionIndex)
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

void GetMods(const unsigned int CollectionIndex, char **ModNames)
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
unsigned int SetRecordFormID(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int FieldValue)
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


char * GetModName(const unsigned int CollectionIndex, const unsigned int iIndex)
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

unsigned int ModIsFake(const unsigned int CollectionIndex, const unsigned int iIndex)
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

unsigned int GetCorrectedFID(const unsigned int CollectionIndex, char *ModName, unsigned int recordObjectID)
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

unsigned int UpdateAllReferences(const unsigned int CollectionIndex, char *ModName, unsigned int origFormID, unsigned int newFormID)
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

unsigned int GetNumReferences(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int referenceFormID)
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

unsigned int UpdateReferences(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int origFormID, unsigned int newFormID)
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
int IsFIDWinning(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, bool ignoreScanned)
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

int IsGMSTWinning(const unsigned int CollectionIndex, char *ModName, char *recordEDID, bool ignoreScanned)
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

int GetNumFIDConflicts(const unsigned int CollectionIndex, unsigned int recordFID, bool ignoreScanned)
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

void GetFIDConflicts(const unsigned int CollectionIndex, unsigned int recordFID, bool ignoreScanned, char **ModNames)
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

int GetNumGMSTConflicts(const unsigned int CollectionIndex, char *recordEDID, bool ignoreScanned)
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

void GetGMSTConflicts(const unsigned int CollectionIndex, char *recordEDID, bool ignoreScanned, char **ModNames)
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
unsigned int GetNumGMSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumGMSTRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumGMSTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumGMSTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumGLOBRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumGLOBRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumGLOBRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumGLOBRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCLASRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumCLASRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumCLASRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumCLASRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumFACTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumFACTRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumFACTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumFACTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumHAIRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumHAIRRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumHAIRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumHAIRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumEYESRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumEYESRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumEYESRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumEYESRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumRACERecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumRACERecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumRACERecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumRACERecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSOUNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumSOUNRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumSOUNRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumSOUNRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSKILRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumSKILRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumSKILRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumSKILRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumMGEFRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumMGEFRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumMGEFRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumMGEFRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSCPTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumSCPTRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumSCPTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumSCPTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLTEXRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumLTEXRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumLTEXRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumLTEXRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumENCHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumENCHRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumENCHRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumENCHRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSPELRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumSPELRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumSPELRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumSPELRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumBSGNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumBSGNRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumBSGNRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumBSGNRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumACTIRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumACTIRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumACTIRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumACTIRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumAPPARecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumAPPARecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumAPPARecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumAPPARecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumARMORecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumARMORecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumARMORecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumARMORecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumBOOKRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumBOOKRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumBOOKRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumBOOKRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCLOTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumCLOTRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumCLOTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumCLOTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCONTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumCONTRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumCONTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumCONTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumDOORRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumDOORRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumDOORRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumDOORRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumINGRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumINGRRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumINGRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumINGRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLIGHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumLIGHRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumLIGHRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumLIGHRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumMISCRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumMISCRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumMISCRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumMISCRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSTATRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumSTATRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumSTATRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumSTATRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumGRASRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumGRASRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumGRASRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumGRASRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumTREERecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumTREERecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumTREERecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumTREERecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumFLORRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumFLORRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumFLORRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumFLORRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumFURNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumFURNRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumFURNRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumFURNRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumWEAPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumWEAPRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumWEAPRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumWEAPRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumAMMORecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumAMMORecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumAMMORecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumAMMORecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumNPC_Records(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumNPC_Records(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumNPC_Records: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumNPC_Records: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCREARecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumCREARecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumCREARecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumCREARecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLVLCRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumLVLCRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumLVLCRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumLVLCRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSLGMRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumSLGMRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumSLGMRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumSLGMRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumKEYMRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumKEYMRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumKEYMRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumKEYMRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumALCHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumALCHRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumALCHRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumALCHRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSBSPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumSBSPRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumSBSPRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumSBSPRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSGSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumSGSTRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumSGSTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumSGSTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLVLIRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumLVLIRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumLVLIRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumLVLIRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumWTHRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumWTHRRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumWTHRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumWTHRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCLMTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumCLMTRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumCLMTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumCLMTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumREGNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumREGNRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumREGNRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumREGNRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCELLRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumCELLRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumCELLRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumCELLRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumACHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumACHRRecords(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("GetNumACHRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumACHRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumACRERecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumACRERecords(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("GetNumACRERecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumACRERecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumREFRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumREFRRecords(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("GetNumREFRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumREFRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumWRLDRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumWRLDRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumWRLDRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumWRLDRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumDIALRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumDIALRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumDIALRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumDIALRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumQUSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumQUSTRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumQUSTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumQUSTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumIDLERecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumIDLERecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumIDLERecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumIDLERecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumPACKRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumPACKRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumPACKRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumPACKRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCSTYRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumCSTYRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumCSTYRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumCSTYRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLSCRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumLSCRRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumLSCRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumLSCRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLVSPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumLVSPRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumLVSPRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumLVSPRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumANIORecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumANIORecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumANIORecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumANIORecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumWATRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumWATRRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumWATRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumWATRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumEFSHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->GetNumEFSHRecords(ModName);
        }
    catch(std::exception &ex)
        {
        printf("GetNumEFSHRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNumEFSHRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int GetTES4FieldType(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
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

unsigned int GetTES4FieldArraySize(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
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

void GetTES4FieldArray(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, void **FieldValues)
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

void * ReadTES4Field(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
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
int SetTES4FieldStr(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, char *FieldValue)
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

int SetTES4FieldStrA(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, char **FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }

int SetTES4FieldUI(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, unsigned int FieldValue)
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

int SetTES4FieldF(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, float FieldValue)
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

int SetTES4FieldR(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteTES4Field(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
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
void GetGMSTRecords(const unsigned int CollectionIndex, char *ModName, char **RecordEIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetGMSTRecords(ModName, RecordEIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetGMSTRecords: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetGMSTRecords: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }

int GetGMSTFieldType(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field)
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

void * ReadGMSTField(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field)
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
unsigned int CreateGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        return Collections[CollectionIndex]->CreateGMSTRecord(ModName, recordEDID);
        }
    catch(std::exception &ex)
        {
        printf("CreateGMSTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateGMSTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID, char *destModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(recordEDID);
        return Collections[CollectionIndex]->CopyGMSTRecord(ModName, recordEDID, destModName);
        }
    catch(std::exception &ex)
        {
        printf("CopyGMSTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyGMSTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int SetGMSTFieldStr(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, char *FieldValue)
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

int SetGMSTFieldI(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, int FieldValue)
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

int SetGMSTFieldUI(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, unsigned int FieldValue)
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

int SetGMSTFieldF(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, float FieldValue)
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

int DeleteGMSTField(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field)
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
//ADD
unsigned int GetGLOBRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetGLOBRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetGLOBRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetGLOBRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCLASRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetCLASRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetCLASRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetCLASRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetFACTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetFACTRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetFACTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFACTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetHAIRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetHAIRRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetHAIRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetHAIRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetEYESRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetEYESRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetEYESRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetEYESRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetRACERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetRACERecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetRACERecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetRACERecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSOUNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetSOUNRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetSOUNRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetSOUNRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSKILRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetSKILRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetSKILRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetSKILRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetMGEFRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetMGEFRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetMGEFRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetMGEFRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSCPTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetSCPTRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetSCPTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetSCPTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLTEXRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetLTEXRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetLTEXRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetLTEXRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetENCHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetENCHRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetENCHRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetENCHRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSPELRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetSPELRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetSPELRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetSPELRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetBSGNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetBSGNRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetBSGNRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetBSGNRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetACTIRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetACTIRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetACTIRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetACTIRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetAPPARecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetAPPARecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetAPPARecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetAPPARecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetARMORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetARMORecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetARMORecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetARMORecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetBOOKRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetBOOKRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetBOOKRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetBOOKRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCLOTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetCLOTRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetCLOTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetCLOTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCONTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetCONTRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetCONTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetCONTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetDOORRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetDOORRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetDOORRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetDOORRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetINGRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetINGRRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetINGRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetINGRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLIGHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetLIGHRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetLIGHRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetLIGHRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetMISCRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetMISCRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetMISCRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetMISCRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSTATRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetSTATRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetSTATRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetSTATRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetGRASRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetGRASRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetGRASRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetGRASRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetTREERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetTREERecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetTREERecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetTREERecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetFLORRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetFLORRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetFLORRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFLORRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetFURNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetFURNRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetFURNRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetFURNRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetWEAPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetWEAPRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetWEAPRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetWEAPRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetAMMORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetAMMORecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetAMMORecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetAMMORecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNPC_Records(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetNPC_Records(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetNPC_Records: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetNPC_Records: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCREARecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetCREARecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetCREARecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetCREARecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLVLCRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetLVLCRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetLVLCRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetLVLCRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSLGMRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetSLGMRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetSLGMRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetSLGMRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetKEYMRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetKEYMRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetKEYMRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetKEYMRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetALCHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetALCHRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetALCHRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetALCHRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSBSPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetSBSPRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetSBSPRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetSBSPRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSGSTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetSGSTRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetSGSTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetSGSTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLVLIRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetLVLIRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetLVLIRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetLVLIRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetWTHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetWTHRRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetWTHRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetWTHRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCLMTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetCLMTRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetCLMTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetCLMTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetREGNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetREGNRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetREGNRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetREGNRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCELLRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetCELLRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetCELLRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetCELLRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetACHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetACHRRecords(ModName, parentFID, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetACHRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetACHRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetACRERecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetACRERecords(ModName, parentFID, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetACRERecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetACRERecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetREFRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetREFRRecords(ModName, parentFID, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetREFRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetREFRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetWRLDRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetWRLDRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetWRLDRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetWRLDRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetDIALRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetDIALRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetDIALRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetDIALRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetQUSTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetQUSTRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetQUSTRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetQUSTRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetIDLERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetIDLERecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetIDLERecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetIDLERecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetPACKRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetPACKRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetPACKRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetPACKRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCSTYRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetCSTYRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetCSTYRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetCSTYRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLSCRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetLSCRRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetLSCRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetLSCRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLVSPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetLVSPRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetLVSPRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetLVSPRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetANIORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetANIORecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetANIORecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetANIORecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetWATRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetWATRRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetWATRRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetWATRRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int GetEFSHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        Collections[CollectionIndex]->GetEFSHRecords(ModName, RecordFIDs);
        }
    catch(std::exception &ex)
        {
        printf("GetEFSHRecords: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("GetEFSHRecords: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int GetFIDFieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
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

int GetFIDListFieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField)
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

int GetFIDListX2FieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field)
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

int GetFIDListX3FieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field)
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
unsigned int GetFIDFieldArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
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
unsigned int GetFIDListArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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
unsigned int GetFIDListX2ArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
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
unsigned int GetFIDListX3ArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
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
unsigned int GetFIDListSize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
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
unsigned int GetFIDListX2Size(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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
unsigned int GetFIDListX3Size(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
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
void GetFIDFieldArray(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, void **FieldValues)
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
void GetFIDListArray(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
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
void GetFIDListX2Array(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
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
void GetFIDListX3Array(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues)
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
void * ReadFIDField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
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

void * ReadFIDListField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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

void * ReadFIDListX2Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
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

void * ReadFIDListX3Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
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
//ADD
unsigned int CreateGLOBRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateGLOBRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateGLOBRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateGLOBRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCLASRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateCLASRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateCLASRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateCLASRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateFACTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateFACTRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateFACTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateFACTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateHAIRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateHAIRRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateHAIRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateHAIRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateEYESRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateEYESRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateEYESRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateEYESRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateRACERecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateRACERecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateRACERecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateRACERecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSOUNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateSOUNRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateSOUNRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateSOUNRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSKILRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateSKILRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateSKILRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateSKILRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateMGEFRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateMGEFRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateMGEFRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateMGEFRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSCPTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateSCPTRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateSCPTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateSCPTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLTEXRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateLTEXRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateLTEXRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateLTEXRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateENCHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateENCHRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateENCHRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateENCHRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSPELRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateSPELRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateSPELRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateSPELRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateBSGNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateBSGNRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateBSGNRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateBSGNRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateACTIRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateACTIRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateACTIRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateACTIRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateAPPARecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateAPPARecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateAPPARecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateAPPARecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateARMORecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateARMORecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateARMORecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateARMORecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateBOOKRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateBOOKRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateBOOKRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateBOOKRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCLOTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateCLOTRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateCLOTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateCLOTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCONTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateCONTRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateCONTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateCONTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateDOORRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateDOORRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateDOORRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateDOORRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateINGRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateINGRRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateINGRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateINGRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLIGHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateLIGHRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateLIGHRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateLIGHRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateMISCRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateMISCRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateMISCRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateMISCRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSTATRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateSTATRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateSTATRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateSTATRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateGRASRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateGRASRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateGRASRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateGRASRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateTREERecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateTREERecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateTREERecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateTREERecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateFLORRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateFLORRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateFLORRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateFLORRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateFURNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateFURNRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateFURNRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateFURNRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateWEAPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateWEAPRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateWEAPRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateWEAPRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateAMMORecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateAMMORecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateAMMORecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateAMMORecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateNPC_Record(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateNPC_Record(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateNPC_Record: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateNPC_Record: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCREARecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateCREARecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateCREARecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateCREARecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLVLCRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateLVLCRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateLVLCRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateLVLCRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSLGMRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateSLGMRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateSLGMRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateSLGMRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateKEYMRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateKEYMRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateKEYMRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateKEYMRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateALCHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateALCHRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateALCHRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateALCHRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSBSPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateSBSPRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateSBSPRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateSBSPRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSGSTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateSGSTRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateSGSTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateSGSTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLVLIRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateLVLIRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateLVLIRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateLVLIRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateWTHRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateWTHRRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateWTHRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateWTHRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCLMTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateCLMTRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateCLMTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateCLMTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateREGNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateREGNRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateREGNRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateREGNRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCELLRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, int isWorldCELL)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateCELLRecord(ModName, parentFID, isWorldCELL);
        }
    catch(std::exception &ex)
        {
        printf("CreateCELLRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateCELLRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateACHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateACHRRecord(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("CreateACHRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateACHRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateACRERecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateACRERecord(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("CreateACRERecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateACRERecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateREFRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateREFRRecord(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("CreateREFRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateREFRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreatePGRDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreatePGRDRecord(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("CreatePGRDRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreatePGRDRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateWRLDRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateWRLDRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateWRLDRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateWRLDRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateROADRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateROADRecord(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("CreateROADRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateROADRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLANDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateLANDRecord(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("CreateLANDRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateLANDRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateDIALRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateDIALRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateDIALRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateDIALRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateINFORecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateINFORecord(ModName, parentFID);
        }
    catch(std::exception &ex)
        {
        printf("CreateINFORecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateINFORecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateQUSTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateQUSTRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateQUSTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateQUSTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateIDLERecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateIDLERecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateIDLERecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateIDLERecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreatePACKRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreatePACKRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreatePACKRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreatePACKRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCSTYRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateCSTYRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateCSTYRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateCSTYRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLSCRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateLSCRRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateLSCRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateLSCRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLVSPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateLVSPRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateLVSPRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateLVSPRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateANIORecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateANIORecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateANIORecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateANIORecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateWATRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateWATRRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateWATRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateWATRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateEFSHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        return Collections[CollectionIndex]->CreateEFSHRecord(ModName);
        }
    catch(std::exception &ex)
        {
        printf("CreateEFSHRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateEFSHRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
//ADD
unsigned int CopyFIDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyFIDRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyFIDRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyFIDRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyGLOBRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyGLOBRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyGLOBRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyGLOBRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCLASRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyCLASRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyCLASRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyCLASRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyFACTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyFACTRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyFACTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyFACTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyHAIRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyHAIRRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyHAIRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyHAIRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyEYESRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyEYESRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyEYESRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyEYESRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyRACERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyRACERecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyRACERecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyRACERecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySOUNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopySOUNRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopySOUNRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopySOUNRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySKILRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopySKILRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopySKILRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopySKILRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyMGEFRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyMGEFRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyMGEFRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyMGEFRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySCPTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopySCPTRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopySCPTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopySCPTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLTEXRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyLTEXRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyLTEXRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyLTEXRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyENCHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyENCHRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyENCHRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyENCHRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySPELRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopySPELRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopySPELRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopySPELRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyBSGNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyBSGNRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyBSGNRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyBSGNRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyACTIRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyACTIRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyACTIRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyACTIRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyAPPARecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyAPPARecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyAPPARecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyAPPARecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyARMORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyARMORecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyARMORecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyARMORecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyBOOKRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyBOOKRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyBOOKRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyBOOKRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCLOTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyCLOTRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyCLOTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyCLOTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCONTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyCONTRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyCONTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyCONTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyDOORRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyDOORRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyDOORRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyDOORRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyINGRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyINGRRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyINGRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyINGRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLIGHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyLIGHRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyLIGHRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyLIGHRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyMISCRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyMISCRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyMISCRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyMISCRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySTATRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopySTATRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopySTATRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopySTATRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyGRASRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyGRASRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyGRASRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyGRASRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyTREERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyTREERecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyTREERecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyTREERecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyFLORRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyFLORRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyFLORRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyFLORRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyFURNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyFURNRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyFURNRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyFURNRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyWEAPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyWEAPRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyWEAPRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyWEAPRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyAMMORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyAMMORecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyAMMORecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyAMMORecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyNPC_Record(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyNPC_Record(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyNPC_Record: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyNPC_Record: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCREARecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyCREARecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyCREARecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyCREARecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLVLCRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyLVLCRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyLVLCRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyLVLCRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySLGMRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopySLGMRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopySLGMRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopySLGMRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyKEYMRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyKEYMRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyKEYMRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyKEYMRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyALCHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyALCHRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyALCHRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyALCHRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySBSPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopySBSPRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopySBSPRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopySBSPRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySGSTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopySGSTRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopySGSTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopySGSTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLVLIRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyLVLIRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyLVLIRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyLVLIRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyWTHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyWTHRRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyWTHRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyWTHRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCLMTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyCLMTRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyCLMTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyCLMTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyREGNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyREGNRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyREGNRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyREGNRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCELLRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride, int isWorldCELL)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyCELLRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride, isWorldCELL);
        }
    catch(std::exception &ex)
        {
        printf("CopyCELLRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyCELLRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyACHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyACHRRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyACHRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyACHRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyACRERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyACRERecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyACRERecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyACRERecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyREFRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyREFRRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyREFRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyREFRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyPGRDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyPGRDRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyPGRDRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyPGRDRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyWRLDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyWRLDRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyWRLDRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyWRLDRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyROADRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyROADRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyROADRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyROADRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLANDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyLANDRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyLANDRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyLANDRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyDIALRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyDIALRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyDIALRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyDIALRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyINFORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyINFORecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyINFORecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyINFORecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyQUSTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyQUSTRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyQUSTRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyQUSTRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyIDLERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyIDLERecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyIDLERecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyIDLERecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyPACKRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyPACKRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyPACKRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyPACKRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCSTYRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyCSTYRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyCSTYRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyCSTYRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLSCRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyLSCRRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyLSCRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyLSCRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLVSPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyLVSPRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyLVSPRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyLVSPRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyANIORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyANIORecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyANIORecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyANIORecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyWATRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyWATRRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyWATRRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyWATRRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyEFSHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        ValidateCollection(CollectionIndex);
        ValidatePointer(ModName);
        ValidatePointer(destModName);
        return Collections[CollectionIndex]->CopyEFSHRecord(ModName, srcRecordFID, destModName, asOverride);
        }
    catch(std::exception &ex)
        {
        printf("CopyEFSHRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CopyEFSHRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int SetFIDFieldC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char FieldValue)
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

int SetFIDFieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned char FieldValue)
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

int SetFIDFieldStr(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char *FieldValue)
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

int SetFIDFieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char **FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }

int SetFIDFieldS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, short FieldValue)
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

int SetFIDFieldUS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned short FieldValue)
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

int SetFIDFieldI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, int FieldValue)
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

int SetFIDFieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned int FieldValue)
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

int SetFIDFieldUIA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%08X\n", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int SetFIDFieldF(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, float FieldValue)
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

int SetFIDFieldR(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteFIDField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
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
int CreateFIDListElement(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField)
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
int CreateFIDListX2Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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
int CreateFIDListX3Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
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
int DeleteFIDListElement(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField)
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
int DeleteFIDListX2Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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
int DeleteFIDListX3Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
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
int SetFIDListFieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char FieldValue)
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
int SetFIDListFieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
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
int SetFIDListFieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue)
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
int SetFIDListFieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char **FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldS (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue)
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
int SetFIDListFieldUS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned short FieldValue)
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
int SetFIDListFieldI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
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
int SetFIDListFieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
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

int SetFIDListFieldUIA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue[], unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%08X\n", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }
int SetFIDListFieldF (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue)
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

int SetFIDListFieldR (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteFIDListField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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
int SetFIDListX2FieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char FieldValue)
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
int SetFIDListX2FieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue)
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
int SetFIDListX2FieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char *FieldValue)
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
int SetFIDListX2FieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char **FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldS (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, short FieldValue)
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
int SetFIDListX2FieldUS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned short FieldValue)
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
int SetFIDListX2FieldI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, int FieldValue)
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

int SetFIDListX2FieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue)
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

int SetFIDListX2FieldF (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue)
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

int SetFIDListX2FieldR (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteFIDListX2Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
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
int SetFIDListX3FieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char FieldValue)
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
int SetFIDListX3FieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char FieldValue)
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
int SetFIDListX3FieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char *FieldValue)
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
int SetFIDListX3FieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char **FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%s\n", FieldValue[p]);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldS (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, short FieldValue)
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
int SetFIDListX3FieldUS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned short FieldValue)
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
int SetFIDListX3FieldI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, int FieldValue)
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

int SetFIDListX3FieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned int FieldValue)
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

int SetFIDListX3FieldF (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, float FieldValue)
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

int SetFIDListX3FieldR (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char *FieldValue, unsigned int nSize)
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
        for(unsigned int p = 0; p < nSize; p++)
            printf("%02X", FieldValue[p]);
        printf("\n");
        return -1;
        }
    return 0;
    }

int DeleteFIDListX3Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
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
//ADD
//int StartGLOBIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eGLOB));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartGLOBIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartGLOBIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartCLASIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLAS));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartCLASIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartCLASIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartFACTIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eFACT));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartFACTIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartFACTIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartHAIRIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eHAIR));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartHAIRIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartHAIRIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartEYESIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eEYES));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartEYESIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartEYESIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartRACEIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eRACE));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartRACEIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartRACEIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartSOUNIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eSOUN));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartSOUNIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartSOUNIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartSKILIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eSKIL));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartSKILIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartSKILIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartMGEFIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eMGEF));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartMGEFIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartMGEFIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartSCPTIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eSCPT));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartSCPTIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartSCPTIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartLTEXIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eLTEX));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartLTEXIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartLTEXIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartENCHIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eENCH));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartENCHIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartENCHIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartSPELIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eSPEL));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartSPELIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartSPELIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartBSGNIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eBSGN));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartBSGNIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartBSGNIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartACTIIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eACTI));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartACTIIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartACTIIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartAPPAIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eAPPA));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartAPPAIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartAPPAIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartARMOIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eARMO));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartARMOIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartARMOIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartBOOKIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eBOOK));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartBOOKIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartBOOKIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartCLOTIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLOT));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartCLOTIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartCLOTIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartCONTIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eCONT));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartCONTIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartCONTIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartDOORIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eDOOR));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartDOORIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartDOORIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartINGRIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eINGR));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartINGRIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartINGRIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartLIGHIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eLIGH));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartLIGHIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartLIGHIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartMISCIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eMISC));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartMISCIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartMISCIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartSTATIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eSTAT));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartSTATIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartSTATIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartGRASIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eGRAS));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartGRASIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartGRASIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartTREEIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eTREE));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartTREEIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartTREEIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartFLORIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eFLOR));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartFLORIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartFLORIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartFURNIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eFURN));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartFURNIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartFURNIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartWEAPIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eWEAP));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartWEAPIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartWEAPIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartAMMOIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eAMMO));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartAMMOIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartAMMOIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartNPC_Iterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eNPC_));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartNPC_Iterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartNPC_Iterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartCREAIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eCREA));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartCREAIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartCREAIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartLVLCIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVLC));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartLVLCIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartLVLCIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartSLGMIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eSLGM));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartSLGMIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartSLGMIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartKEYMIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eKEYM));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartKEYMIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartKEYMIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartALCHIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eALCH));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartALCHIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartALCHIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartSBSPIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eSBSP));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartSBSPIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartSBSPIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartSGSTIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eSGST));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartSGSTIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartSGSTIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartLVLIIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVLI));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartLVLIIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartLVLIIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartWTHRIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eWTHR));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartWTHRIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartWTHRIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartCLMTIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLMT));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartCLMTIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartCLMTIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartREGNIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eREGN));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartREGNIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartREGNIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartCELLIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eCELL));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartCELLIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartCELLIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartWRLDIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eWRLD));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartWRLDIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartWRLDIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartDIALIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eDIAL));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartDIALIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartDIALIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartQUSTIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eQUST));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartQUSTIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartQUSTIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartIDLEIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eIDLE));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartIDLEIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartIDLEIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartPACKIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], ePACK));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartPACKIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartPACKIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartCSTYIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eCSTY));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartCSTYIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartCSTYIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartLSCRIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eLSCR));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartLSCRIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartLSCRIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartLVSPIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVSP));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartLVSPIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartLVSPIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartANIOIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eANIO));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartANIOIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartANIOIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartWATRIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eWATR));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartWATRIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartWATRIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
//int StartEFSHIterator(const unsigned int CollectionIndex)
//    {
//    try
//        {
//        ValidateCollection(CollectionIndex);
//        Iterators.push_back(new Iterator(Collections[CollectionIndex], eEFSH));
//        }
//    catch(std::exception &ex)
//        {
//        printf("StartEFSHIterator: Error\n  %s\n", ex.what());
//        return -1;
//        }
//    catch(...)
//        {
//        printf("StartEFSHIterator: Error\n  Unhandled Exception\n");
//        return -1;
//        }
//    return (unsigned int)Iterators.size() - 1;
//    }
//
////////////////////////////////////////////////////////////////////////
//long long IncrementIterator(const unsigned int IteratorID)
//    {
//    try
//        {
//        if(IteratorID < Iterators.size())
//            return Iterators[IteratorID]->IncrementIterator();
//        else
//            throw 1;
//        }
//    catch(std::exception &ex)
//        {
//        printf("IncrementIterator: Error\n  %s\n", ex.what());
//        return 0;
//        }
//    catch(...)
//        {
//        printf("IncrementIterator: Error\n  Unhandled Exception\n");
//        return 0;
//        }
//    return 0;
//    }
//
//void StopIterator(const unsigned int IteratorID)
//    {
//    try
//        {
//        if(IteratorID < Iterators.size())
//            Iterators.erase(Iterators.begin() + IteratorID);
//        else
//            throw 1;
//        }
//    catch(std::exception &ex)
//        {
//        printf("StopIterator: Error\n  %s\n", ex.what());
//        return;
//        }
//    catch(...)
//        {
//        printf("StopIterator: Error\n  Unhandled Exception\n");
//        return;
//        }
//    return;
//    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void Debug(const unsigned int CollectionIndex, const int debugLevel, const bool AllRecords)
    {
    if(AllRecords)
        printf("Loading all records!!!\n");
    Collections[CollectionIndex]->Debug(debugLevel, AllRecords);
    return;
    }
#endif
