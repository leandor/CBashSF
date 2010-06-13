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
static std::vector<Iterator *> Iterators;

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

int NewCollection(const char *ModsPath)
    {
    try
        {
        if(ModsPath == NULL)
            throw Ex_NULL();
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
	catch(Ex_NULL &ex)
	    {
        printf("Error creating collection\n  %s", ex.what());
        return -1;
	    }
    catch(...)
        {
        printf("Error creating collection\n");
        return -1;
        }
    return (int)Collections.size() - 1;
    }

int DeleteCollection(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            {
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
		}
    catch(...)
        {
        printf("Error erasing collection at pos %i\n", CollectionIndex);
        return -1;
        }

    return 0;
    }

////////////////////////////////////////////////////////////////////////
int AddMod(const unsigned int CollectionIndex, const char *ModName, bool CreateIfNotExist)
    {
    int status = 0;
    try
        {
        if(CollectionIndex < Collections.size())
            status = Collections[CollectionIndex]->AddMod(ModName, CreateIfNotExist, false);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error adding mod:%s\n", ModName);
        return -1;
        }
    return status;
    }

int AddMergeMod(const unsigned int CollectionIndex, const char *ModName)
    {
    int status = 0;
    try
        {
        if(CollectionIndex < Collections.size())
            status = Collections[CollectionIndex]->AddMod(ModName, false, true);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error adding merge mod:%s\n", ModName);
        return -1;
        }
    return status;
    }

int MinimalLoad(const unsigned int CollectionIndex, const bool LoadMasters)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            {
            Collections[CollectionIndex]->Load(LoadMasters, false);
            Collections[CollectionIndex]->IndexRecords();
            }
        else
            throw 1;
        }
    catch(...)
        {
        printf("MinimalLoad: Error loading records\n");
        return -1;
        }
    return 0;
    }

int FullLoad(const unsigned int CollectionIndex, const bool LoadMasters)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            {
            Collections[CollectionIndex]->Load(LoadMasters, true);
            Collections[CollectionIndex]->IndexRecords();
            }
        else
            throw 1;
        }
    catch(...)
        {
        printf("FullLoad: Error loading records\n");
        return -1;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int CleanMasters(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(ModName == NULL)
            throw 1;
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CleanMasters(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CleanMasters: Error loading records\n");
        return 0;
        }
    return 0;
    }

int SafeSaveMod(const unsigned int CollectionIndex, char *curFileName, bool CloseMod)
	{
    try
        {
        if(CollectionIndex < Collections.size())
            {
            Collections[CollectionIndex]->SafeSaveMod(curFileName, CloseMod);
            if(CloseMod)
                DeleteCollection(CollectionIndex);
            }
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error safe saving mod:%s\n", curFileName);
        return -1;
        }
    return 0;
	}
////////////////////////////////////////////////////////////////////////
int LoadRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->LoadRecord(ModName, recordFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error loading record: %08X from mod:%s in collection: %i\n", recordFID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int UnloadRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->UnloadRecord(ModName, recordFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error unloading record: %08X from mod:%s in collection: %i\n", recordFID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int UnloadModFile(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->UnloadModFile(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error unloading records from mod:%s in collection: %i\n", ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int UnloadAll(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->UnloadAll();
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error unloading all records from collection: %i\n", CollectionIndex);
        return -1;
        }
    return 0;
    }

int DeleteRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->DeleteRecord(ModName, recordFID, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error deleting record: %08X from mod:%s in collection: %i\n", recordFID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int DeleteGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->DeleteGMSTRecord(ModName, recordEDID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error deleting GMST record: %s from mod:%s in collection: %i\n", recordEDID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

int Close(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->Close();
        }
    catch(...)
        {
        printf("Error closing collection at %i\n", CollectionIndex);
        return -1;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
unsigned int GetNumMods(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumMods();
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumMods: Error\n");
        return -1;
        }
    return 0;
    }

void GetMods(const unsigned int CollectionIndex, char **ModNames)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetMods(ModNames);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetMods: Error\n");
        return;
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
unsigned int SetRecordFormID(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->SetRecordFormID(ModName, recordFID, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("SetRecordFormID: Error\n");
        return 0;
        }
    return 0;
    }


char * GetModName(const unsigned int CollectionIndex, const unsigned int iIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetModName(iIndex);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetModName: Error\n");
        return NULL;
        }
    return NULL;
    }

unsigned int GetCorrectedFID(const unsigned int CollectionIndex, char *ModName, unsigned int recordObjectID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetCorrectedFID(ModName, recordObjectID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error getting corrected formID: %08x from mod:%s in collection: %i\n", recordObjectID, ModName, CollectionIndex);
        return -1;
        }
    return 0;
    }

unsigned int UpdateAllReferences(const unsigned int CollectionIndex, char *ModName, unsigned int origFormID, unsigned int newFormID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->UpdateReferences(ModName, origFormID, newFormID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("UpdateAllReferences: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int UpdateReferences(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int origFormID, unsigned int newFormID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->UpdateReferences(ModName, recordFID, origFormID, newFormID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("UpdateReferences: Error\n");
        return 0;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int GetNumFIDConflicts(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumFIDConflicts(ModName, recordFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumFIDConflict: Error\n");
        return 0;
        }
    return 0;
    }

void GetFIDConflicts(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, char **ModNames)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            {
            Collections[CollectionIndex]->GetFIDConflicts(ModName, recordFID, ModNames);
            return;
            }
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDConflicts: Error\n");
        return;
        }
    return;
    }
    
int GetNumGMSTConflicts(const unsigned int CollectionIndex, char *ModName, char *recordEDID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumGMSTConflicts(ModName, recordEDID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumGMSTConflicts: Error\n");
        return 0;
        }
    return 0;
    }

void GetGMSTConflicts(const unsigned int CollectionIndex, char *ModName, char *recordEDID, char **ModNames)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            {
            Collections[CollectionIndex]->GetGMSTConflicts(ModName, recordEDID, ModNames);
            return;
            }
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetGMSTConflicts: Error\n");
        return;
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
unsigned int GetNumGMSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumGMSTRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumGMSTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumGLOBRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumGLOBRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumGLOBRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCLASRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumCLASRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumCLASRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumFACTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumFACTRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumFACTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumHAIRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumHAIRRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumHAIRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumEYESRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumEYESRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumEYESRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumRACERecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumRACERecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumRACERecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSOUNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumSOUNRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumSOUNRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSKILRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumSKILRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumSKILRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumMGEFRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumMGEFRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumMGEFRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSCPTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumSCPTRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumSCPTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLTEXRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumLTEXRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumLTEXRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumENCHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumENCHRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumENCHRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSPELRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumSPELRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumSPELRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumBSGNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumBSGNRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumBSGNRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumACTIRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumACTIRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumACTIRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumAPPARecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumAPPARecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumAPPARecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumARMORecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumARMORecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumARMORecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumBOOKRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumBOOKRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumBOOKRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCLOTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumCLOTRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumCLOTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCONTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumCONTRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumCONTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumDOORRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumDOORRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumDOORRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumINGRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumINGRRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumINGRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLIGHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumLIGHRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumLIGHRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumMISCRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumMISCRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumMISCRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSTATRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumSTATRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumSTATRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumGRASRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumGRASRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumGRASRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumTREERecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumTREERecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumTREERecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumFLORRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumFLORRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumFLORRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumFURNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumFURNRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumFURNRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumWEAPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumWEAPRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumWEAPRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumAMMORecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumAMMORecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumAMMORecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumNPC_Records(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumNPC_Records(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumNPC_Records: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCREARecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumCREARecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumCREARecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLVLCRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumLVLCRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumLVLCRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSLGMRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumSLGMRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumSLGMRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumKEYMRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumKEYMRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumKEYMRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumALCHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumALCHRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumALCHRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSBSPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumSBSPRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumSBSPRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumSGSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumSGSTRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumSGSTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLVLIRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumLVLIRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumLVLIRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumWTHRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumWTHRRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumWTHRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCLMTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumCLMTRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumCLMTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumREGNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumREGNRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumREGNRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCELLRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumCELLRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumCELLRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumACHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumACHRRecords(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumACHRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumACRERecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumACRERecords(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumACRERecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumREFRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumREFRRecords(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumREFRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumWRLDRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumWRLDRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumWRLDRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumDIALRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumDIALRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumDIALRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumQUSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumQUSTRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumQUSTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumIDLERecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumIDLERecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumIDLERecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumPACKRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumPACKRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumPACKRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumCSTYRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumCSTYRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumCSTYRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLSCRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumLSCRRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumLSCRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumLVSPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumLVSPRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumLVSPRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumANIORecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumANIORecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumANIORecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumWATRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumWATRRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumWATRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNumEFSHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetNumEFSHRecords(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumEFSHRecords: Error\n");
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
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetTES4FieldType(ModName, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNumEFSHRecords: Error\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

unsigned int GetTES4FieldArraySize(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetTES4FieldArraySize(ModName, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetTES4FieldArraySize: Error\n");
        return 0;
        }
    return 0;
    }

void GetTES4FieldArray(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, void **FieldValues)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetTES4FieldArray(ModName, Field, FieldValues);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetTES4FieldArray: Error\n");
        return;
        }
    return;
    }

void * ReadTES4Field(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->ReadTES4Field(ModName, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("ReadTES4Field: Error\n");
        return NULL;
        }
    return NULL;
    }

////////////////////////////////////////////////////////////////////////
int SetTES4FieldStr(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, char *FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %s\n", ModName, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetTES4FieldStrA(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, char **FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue, nSize);
        else
            throw 1;
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
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %i\n", ModName, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetTES4FieldF(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, float FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: TES4\nField: %i\nValue: %f\n", ModName, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetTES4FieldR(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue, nSize);
        else
            throw 1;
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
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void GetGMSTRecords(const unsigned int CollectionIndex, char *ModName, char **RecordEIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetGMSTRecords(ModName, RecordEIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetGMSTRecords: Error\n");
        return;
        }
    return;
    }

int GetGMSTFieldType(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetGMSTFieldType(ModName, recordEDID, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetGMSTFieldType: Error\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * ReadGMSTField(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->ReadGMSTField(ModName, recordEDID, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("ReadGMSTField: Error\n");
        return NULL;
        }
    return NULL;
    }

////////////////////////////////////////////////////////////////////////
unsigned int CreateGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateGMSTRecord(ModName, recordEDID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateGMSTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID, char *destModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyGMSTRecord(ModName, recordEDID, destModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyGMSTRecord: Error\n");
        return 0;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int SetGMSTFieldStr(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, char *FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %s\n", ModName, recordEDID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetGMSTFieldI(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %i\n", ModName, recordEDID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetGMSTFieldUI(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, unsigned int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %i\n", ModName, recordEDID, Field, FieldValue);
        return -1;
        }
    return 0;
    }

int SetGMSTFieldF(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, float FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nRecord: %s\nField: %i\nValue: %f\n", ModName, recordEDID, Field, FieldValue);
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
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetGLOBRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetGLOBRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCLASRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetCLASRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetCLASRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetFACTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetFACTRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFACTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetHAIRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetHAIRRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetHAIRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetEYESRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetEYESRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetEYESRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetRACERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetRACERecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetRACERecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSOUNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetSOUNRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetSOUNRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSKILRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetSKILRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetSKILRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetMGEFRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetMGEFRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetMGEFRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSCPTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetSCPTRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetSCPTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLTEXRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetLTEXRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetLTEXRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetENCHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetENCHRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetENCHRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSPELRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetSPELRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetSPELRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetBSGNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetBSGNRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetBSGNRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetACTIRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetACTIRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetACTIRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetAPPARecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetAPPARecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetAPPARecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetARMORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetARMORecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetARMORecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetBOOKRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetBOOKRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetBOOKRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCLOTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetCLOTRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetCLOTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCONTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetCONTRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetCONTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetDOORRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetDOORRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetDOORRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetINGRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetINGRRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetINGRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLIGHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetLIGHRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetLIGHRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetMISCRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetMISCRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetMISCRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSTATRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetSTATRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetSTATRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetGRASRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetGRASRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetGRASRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetTREERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetTREERecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetTREERecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetFLORRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetFLORRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFLORRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetFURNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetFURNRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFURNRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetWEAPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetWEAPRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetWEAPRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetAMMORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetAMMORecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetAMMORecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetNPC_Records(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetNPC_Records(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetNPC_Records: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCREARecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetCREARecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetCREARecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLVLCRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetLVLCRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetLVLCRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSLGMRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetSLGMRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetSLGMRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetKEYMRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetKEYMRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetKEYMRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetALCHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetALCHRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetALCHRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSBSPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetSBSPRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetSBSPRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetSGSTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetSGSTRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetSGSTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLVLIRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetLVLIRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetLVLIRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetWTHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetWTHRRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetWTHRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCLMTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetCLMTRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetCLMTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetREGNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetREGNRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetREGNRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCELLRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetCELLRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetCELLRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetACHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetACHRRecords(ModName, parentFID, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetACHRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetACRERecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetACRERecords(ModName, parentFID, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetACRERecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetREFRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetREFRRecords(ModName, parentFID, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetREFRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetWRLDRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetWRLDRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetWRLDRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetDIALRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetDIALRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetDIALRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetQUSTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetQUSTRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetQUSTRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetIDLERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetIDLERecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetIDLERecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetPACKRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetPACKRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetPACKRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetCSTYRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetCSTYRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetCSTYRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLSCRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetLSCRRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetLSCRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetLVSPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetLVSPRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetLVSPRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetANIORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetANIORecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetANIORecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetWATRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetWATRRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetWATRRecords: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int GetEFSHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->GetEFSHRecords(ModName, RecordFIDs);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetEFSHRecords: Error\n");
        return 0;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int GetFIDFieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDFieldType(ModName, recordFID, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDFieldType: Error\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

int GetFIDListFieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListFieldType(ModName, recordFID, subField, listField);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListFieldType: Error\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

int GetFIDListX2FieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListX2FieldType(ModName, recordFID, subField, listField, listX2Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListX2FieldType: Error\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

int GetFIDListX3FieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListX3FieldType(ModName, recordFID, subField, listField, listX2Field, listX3Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListX3FieldType: Error\n");
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }
////////////////////////////////////////////////////////////////////////
unsigned int GetFIDFieldArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDFieldArraySize(ModName, recordFID, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDFieldArraySize: Error\n");
        return 0;
        }
    return 0;
    }
unsigned int GetFIDListArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListArraySize(ModName, recordFID, subField, listIndex, listField);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListArraySize: Error\n");
        return 0;
        }
    return 0;
    }
unsigned int GetFIDListX2ArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListX2ArraySize(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListX2ArraySize: Error\n");
        return 0;
        }
    return 0;
    }
unsigned int GetFIDListX3ArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListX3ArraySize(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListX3ArraySize: Error\n");
        return 0;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
unsigned int GetFIDListSize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListSize(ModName, recordFID, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListSize: Error\n");
        return 0;
        }
    return 0;
    }
unsigned int GetFIDListX2Size(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListX2Size(ModName, recordFID, subField, listIndex, listField);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListX2Size: Error\n");
        return 0;
        }
    return 0;
    }
unsigned int GetFIDListX3Size(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListX3Size(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListX3Size: Error\n");
        return 0;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
void GetFIDFieldArray(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, void **FieldValues)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDFieldArray(ModName, recordFID, Field, FieldValues);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDFieldArray: Error\n");
        return;
        }
    return;
    }
void GetFIDListArray(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListArray(ModName, recordFID, subField, listIndex, listField, FieldValues);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListArray: Error\n");
        return;
        }
    return;
    }
void GetFIDListX2Array(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListX2Array(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValues);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListX2Array: Error\n");
        return;
        }
    return;
    }
void GetFIDListX3Array(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->GetFIDListX3Array(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValues);
        else
            throw 1;
        }
    catch(...)
        {
        printf("GetFIDListX3Array: Error\n");
        return;
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
void * ReadFIDField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->ReadFIDField(ModName, recordFID, Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("ReadFIDField: Error\n");
        return NULL;
        }
    return NULL;
    }

void * ReadFIDListField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->ReadFIDListField(ModName, recordFID, subField, listIndex, listField);
        else
            throw 1;
        }
    catch(...)
        {
        printf("ReadFIDListField: Error\n");
        return NULL;
        }
    return NULL;
    }

void * ReadFIDListX2Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->ReadFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("ReadFIDListX2Field: Error\n");
        return NULL;
        }
    return NULL;
    }

void * ReadFIDListX3Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->ReadFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("ReadFIDListX3Field: Error\n");
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
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateGLOBRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateGLOBRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCLASRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateCLASRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateCLASRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateFACTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateFACTRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateFACTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateHAIRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateHAIRRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateHAIRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateEYESRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateEYESRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateEYESRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateRACERecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateRACERecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateRACERecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSOUNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateSOUNRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateSOUNRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSKILRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateSKILRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateSKILRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateMGEFRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateMGEFRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateMGEFRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSCPTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateSCPTRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateSCPTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLTEXRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateLTEXRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateLTEXRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateENCHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateENCHRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateENCHRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSPELRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateSPELRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateSPELRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateBSGNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateBSGNRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateBSGNRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateACTIRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateACTIRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateACTIRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateAPPARecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateAPPARecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateAPPARecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateARMORecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateARMORecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateARMORecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateBOOKRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateBOOKRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateBOOKRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCLOTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateCLOTRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateCLOTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCONTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateCONTRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateCONTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateDOORRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateDOORRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateDOORRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateINGRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateINGRRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateINGRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLIGHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateLIGHRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateLIGHRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateMISCRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateMISCRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateMISCRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSTATRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateSTATRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateSTATRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateGRASRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateGRASRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateGRASRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateTREERecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateTREERecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateTREERecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateFLORRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateFLORRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateFLORRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateFURNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateFURNRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateFURNRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateWEAPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateWEAPRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateWEAPRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateAMMORecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateAMMORecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateAMMORecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateNPC_Record(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateNPC_Record(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateNPC_Record: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCREARecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateCREARecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateCREARecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLVLCRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateLVLCRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateLVLCRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSLGMRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateSLGMRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateSLGMRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateKEYMRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateKEYMRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateKEYMRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateALCHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateALCHRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateALCHRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSBSPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateSBSPRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateSBSPRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateSGSTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateSGSTRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateSGSTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLVLIRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateLVLIRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateLVLIRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateWTHRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateWTHRRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateWTHRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCLMTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateCLMTRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateCLMTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateREGNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateREGNRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateREGNRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCELLRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, bool isWorldCELL)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateCELLRecord(ModName, parentFID, isWorldCELL);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateCELLRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateACHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateACHRRecord(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateACHRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateACRERecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateACRERecord(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateACRERecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateREFRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateREFRRecord(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateREFRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreatePGRDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreatePGRDRecord(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreatePGRDRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateWRLDRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateWRLDRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateWRLDRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateROADRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateROADRecord(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateROADRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLANDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateLANDRecord(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateLANDRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateDIALRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateDIALRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateDIALRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateINFORecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateINFORecord(ModName, parentFID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateINFORecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateQUSTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateQUSTRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateQUSTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateIDLERecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateIDLERecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateIDLERecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreatePACKRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreatePACKRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreatePACKRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateCSTYRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateCSTYRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateCSTYRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLSCRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateLSCRRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateLSCRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateLVSPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateLVSPRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateLVSPRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateANIORecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateANIORecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateANIORecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateWATRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateWATRRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateWATRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CreateEFSHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateEFSHRecord(ModName);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateEFSHRecord: Error\n");
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
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyFIDRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyFIDRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyGLOBRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyGLOBRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyGLOBRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCLASRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyCLASRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyCLASRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyFACTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyFACTRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyFACTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyHAIRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyHAIRRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyHAIRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyEYESRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyEYESRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyEYESRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyRACERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyRACERecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyRACERecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySOUNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopySOUNRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopySOUNRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySKILRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopySKILRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopySKILRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyMGEFRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyMGEFRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyMGEFRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySCPTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopySCPTRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopySCPTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLTEXRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyLTEXRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyLTEXRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyENCHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyENCHRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyENCHRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySPELRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopySPELRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopySPELRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyBSGNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyBSGNRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyBSGNRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyACTIRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyACTIRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyACTIRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyAPPARecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyAPPARecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyAPPARecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyARMORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyARMORecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyARMORecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyBOOKRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyBOOKRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyBOOKRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCLOTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyCLOTRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyCLOTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCONTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyCONTRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyCONTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyDOORRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyDOORRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyDOORRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyINGRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyINGRRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyINGRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLIGHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyLIGHRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyLIGHRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyMISCRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyMISCRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyMISCRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySTATRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopySTATRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopySTATRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyGRASRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyGRASRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyGRASRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyTREERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyTREERecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyTREERecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyFLORRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyFLORRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyFLORRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyFURNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyFURNRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyFURNRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyWEAPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyWEAPRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyWEAPRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyAMMORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyAMMORecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyAMMORecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyNPC_Record(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyNPC_Record(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyNPC_Record: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCREARecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyCREARecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyCREARecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLVLCRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyLVLCRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyLVLCRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySLGMRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopySLGMRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopySLGMRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyKEYMRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyKEYMRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyKEYMRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyALCHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyALCHRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyALCHRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySBSPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopySBSPRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopySBSPRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopySGSTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopySGSTRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopySGSTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLVLIRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyLVLIRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyLVLIRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyWTHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyWTHRRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyWTHRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCLMTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyCLMTRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyCLMTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyREGNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyREGNRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyREGNRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCELLRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride, bool isWorldCELL)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyCELLRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride, isWorldCELL);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyCELLRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyACHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyACHRRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyACHRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyACRERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyACRERecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyACRERecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyREFRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyREFRRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyREFRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyPGRDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyPGRDRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyPGRDRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyWRLDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyWRLDRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyWRLDRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyROADRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyROADRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyROADRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLANDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyLANDRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyLANDRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyDIALRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyDIALRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyDIALRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyINFORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyINFORecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyINFORecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyQUSTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyQUSTRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyQUSTRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyIDLERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyIDLERecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyIDLERecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyPACKRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyPACKRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyPACKRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyCSTYRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyCSTYRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyCSTYRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLSCRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyLSCRRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyLSCRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyLVSPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyLVSPRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyLVSPRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyANIORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyANIORecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyANIORecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyWATRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyWATRRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyWATRRecord: Error\n");
        return 0;
        }
    return 0;
    }

unsigned int CopyEFSHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CopyEFSHRecord(ModName, srcRecordFID, destModName, asOverride);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CopyEFSHRecord: Error\n");
        return 0;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int SetFIDFieldC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDFieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned char FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDFieldStr(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char *FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDFieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char **FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue, nSize);
        else
            throw 1;
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
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDFieldUS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned short FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDFieldI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDFieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDFieldUIA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue, nSize);
        else
            throw 1;
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
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n", ModName, recordFID, Field, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDFieldR(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue, nSize);
        else
            throw 1;
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
////////////////////////////////////////////////////////////////////////
int CreateFIDListElement(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateFIDListElement(ModName, recordFID, subField);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateFIDListElement: Error\n");
        return -1;
        }
    return 0;
    }
int CreateFIDListX2Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateFIDListX2Element(ModName, recordFID, subField, listIndex, listField);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateFIDListX2Element: Error\n");
        return -1;
        }
    return 0;
    }
int CreateFIDListX3Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->CreateFIDListX3Element(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("CreateFIDListX3Element: Error\n");
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int DeleteFIDListElement(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->DeleteFIDListElement(ModName, recordFID, subField);
        else
            throw 1;
        }
    catch(...)
        {
        printf("DeleteFIDListElement: Error\n");
        return -1;
        }
    return 0;
    }
int DeleteFIDListX2Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->DeleteFIDListX2Element(ModName, recordFID, subField, listIndex, listField);
        else
            throw 1;
        }
    catch(...)
        {
        printf("DeleteFIDListX2Element: Error\n");
        return -1;
        }
    return 0;
    }
int DeleteFIDListX3Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            return Collections[CollectionIndex]->DeleteFIDListX3Element(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
        else
            throw 1;
        }
    catch(...)
        {
        printf("DeleteFIDListX3Element: Error\n");
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
int SetFIDListFieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char **FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue, nSize);
        else
            throw 1;
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
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldUS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned short FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }

int SetFIDListFieldUIA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue[], unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue, nSize);
        else
            throw 1;
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
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListFieldR (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue, nSize);
        else
            throw 1;
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
////////////////////////////////////////////////////////////////////////
int SetFIDListX2FieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char *FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char **FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue, nSize);
        else
            throw 1;
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
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldUS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned short FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldF (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX2FieldR (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue, nSize);
        else
            throw 1;
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
////////////////////////////////////////////////////////////////////////
int SetFIDListX3FieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %c\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char *FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %s\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char **FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue, nSize);
        else
            throw 1;
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
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldUS(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned short FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned int FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %i\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldF (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, float FieldValue)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
        else
            throw 1;
        }
    catch(...)
        {
        printf("Error setting:\nMod: %s\nFormID: %08X\nField: %i\nValue: %f\n", ModName, recordFID, subField, FieldValue);
        return -1;
        }
    return 0;
    }
int SetFIDListX3FieldR (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char *FieldValue, unsigned int nSize)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue, nSize);
        else
            throw 1;
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
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//ADD
int StartGLOBIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eGLOB));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartGLOBIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartCLASIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLAS));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartCLASIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartFACTIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eFACT));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartFACTIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartHAIRIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eHAIR));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartHAIRIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartEYESIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eEYES));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartEYESIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartRACEIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eRACE));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartRACEIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartSOUNIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eSOUN));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartSOUNIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartSKILIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eSKIL));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartSKILIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartMGEFIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eMGEF));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartMGEFIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartSCPTIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eSCPT));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartSCPTIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartLTEXIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eLTEX));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartLTEXIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartENCHIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eENCH));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartENCHIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartSPELIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eSPEL));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartSPELIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartBSGNIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eBSGN));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartBSGNIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartACTIIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eACTI));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartACTIIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartAPPAIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eAPPA));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartAPPAIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartARMOIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eARMO));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartARMOIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartBOOKIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eBOOK));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartBOOKIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartCLOTIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLOT));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartCLOTIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartCONTIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eCONT));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartCONTIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartDOORIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eDOOR));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartDOORIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartINGRIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eINGR));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartINGRIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartLIGHIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eLIGH));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartLIGHIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartMISCIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eMISC));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartMISCIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartSTATIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eSTAT));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartSTATIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartGRASIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eGRAS));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartGRASIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartTREEIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eTREE));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartTREEIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartFLORIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eFLOR));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartFLORIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartFURNIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eFURN));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartFURNIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartWEAPIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eWEAP));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartWEAPIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartAMMOIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eAMMO));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartAMMOIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartNPC_Iterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eNPC_));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartNPC_Iterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartCREAIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eCREA));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartCREAIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartLVLCIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVLC));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartLVLCIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartSLGMIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eSLGM));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartSLGMIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartKEYMIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eKEYM));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartKEYMIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartALCHIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eALCH));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartALCHIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartSBSPIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eSBSP));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartSBSPIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartSGSTIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eSGST));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartSGSTIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartLVLIIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVLI));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartLVLIIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartWTHRIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eWTHR));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartWTHRIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartCLMTIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLMT));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartCLMTIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartREGNIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eREGN));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartREGNIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartCELLIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eCELL));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartCELLIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartWRLDIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eWRLD));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartWRLDIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartDIALIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eDIAL));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartDIALIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartQUSTIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eQUST));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartQUSTIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartIDLEIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eIDLE));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartIDLEIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartPACKIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], ePACK));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartPACKIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartCSTYIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eCSTY));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartCSTYIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartLSCRIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eLSCR));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartLSCRIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartLVSPIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVSP));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartLVSPIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartANIOIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eANIO));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartANIOIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartWATRIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eWATR));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartWATRIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

int StartEFSHIterator(const unsigned int CollectionIndex)
    {
    try
        {
        if(CollectionIndex < Collections.size())
            Iterators.push_back(new Iterator(Collections[CollectionIndex], eEFSH));
        else
            throw 1;
        }
    catch(...)
        {
        printf("StartEFSHIterator: Error\n");
        return -1;
        }
    return (unsigned int)Iterators.size() - 1;
    }

////////////////////////////////////////////////////////////////////////
long long IncrementIterator(const unsigned int IteratorID)
    {
    try
        {
        if(IteratorID < Iterators.size())
            return Iterators[IteratorID]->IncrementIterator();
        else
            throw 1;
        }
    catch(...)
        {
        printf("IncrementIterator: Error\n");
        return 0;
        }
    return 0;
    }

void StopIterator(const unsigned int IteratorID)
    {
    try
        {
        if(IteratorID < Iterators.size())
            Iterators.erase(Iterators.begin() + IteratorID);
        else
            throw 1;
        }
    catch(...)
        {
        printf("StopIterator: Error\n");
        return;
        }
    return;
    }
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
