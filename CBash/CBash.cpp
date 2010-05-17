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

int NewCollection(const char *ModsPath)
    {
    try
        {
		Collections.push_back(new Collection(ModsPath));
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
        delete Collections[CollectionIndex];
		Collections.erase(Collections.begin() + CollectionIndex);
        //m_dumpMemoryReport("AfterDelete.txt", true);
		}
    catch(...)
        {
        printf("Error erasing collection at pos %i\n", CollectionIndex);
        return -1;
        }

    return 0;
    }

////////////////////////////////////////////////////////////////////////
int NewMod(const unsigned int CollectionIndex, const char *ModName)
    {
    try
        {
        Collections[CollectionIndex]->NewMod(ModName);
        }
    catch(...)
        {
        printf("Error creating mod:%s\n", ModName);
        return -1;
        }
    return 0;
    }

int AddMod(const unsigned int CollectionIndex, const char *ModName, bool CreateIfNotExist)
    {
    int status = 0;
    try
        {
        status = Collections[CollectionIndex]->AddMod(ModName, CreateIfNotExist);
        }
    catch(...)
        {
        printf("Error adding mod:%s\n", ModName);
        return -1;
        }
    return status;
    }

int MinimalLoad(const unsigned int CollectionIndex, const bool LoadMasters)
    {
    try
        {
        Collections[CollectionIndex]->Load(LoadMasters, false);
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
        Collections[CollectionIndex]->Load(LoadMasters, true);
        Collections[CollectionIndex]->Close();
        }
    catch(...)
        {
        printf("FullLoad: Error loading records\n");
        return -1;
        }
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int GetChangedMods(const unsigned int CollectionIndex)
    {
    return Collections[CollectionIndex]->GetChangedMods();
    }

int SafeSaveMod(const unsigned int CollectionIndex, char *curFileName)
	{
    try
        {
        Collections[CollectionIndex]->SafeSaveMod(curFileName);
        }
    catch(...)
        {
        printf("Error safe saving mod:%s\n", curFileName);
        return -1;
        }
    return 0;
	}

int SafeSaveAllChangedMods(const unsigned int CollectionIndex)
	{
    try
        {
        Collections[CollectionIndex]->SafeSaveAllChangedMods();
        }
    catch(...)
        {
        printf("Error safe saving all changed mods\n");
        return -1;
        }
    return 0;
	}

////////////////////////////////////////////////////////////////////////
int Close(const unsigned int CollectionIndex)
    {
    try
        {
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
    return Collections[CollectionIndex]->GetNumMods();
    }

void GetMods(const unsigned int CollectionIndex, char **ModNames)
    {
    Collections[CollectionIndex]->GetMods(ModNames);
    }

char * GetModName(const unsigned int CollectionIndex, const unsigned int iIndex)
    {
    return Collections[CollectionIndex]->GetModName(iIndex);
    }

////////////////////////////////////////////////////////////////////////
unsigned int GetNumGMSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumGMSTRecords(ModName);
    }

unsigned int GetNumGLOBRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumGLOBRecords(ModName);
    }

unsigned int GetNumCLASRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumCLASRecords(ModName);
    }

unsigned int GetNumFACTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumFACTRecords(ModName);
    }

unsigned int GetNumHAIRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumHAIRRecords(ModName);
    }

unsigned int GetNumEYESRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumEYESRecords(ModName);
    }

unsigned int GetNumRACERecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumRACERecords(ModName);
    }

unsigned int GetNumSOUNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumSOUNRecords(ModName);
    }

unsigned int GetNumSKILRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumSKILRecords(ModName);
    }

unsigned int GetNumMGEFRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumMGEFRecords(ModName);
    }

unsigned int GetNumSCPTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumSCPTRecords(ModName);
    }

unsigned int GetNumLTEXRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumLTEXRecords(ModName);
    }

unsigned int GetNumENCHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumENCHRecords(ModName);
    }

unsigned int GetNumSPELRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumSPELRecords(ModName);
    }

unsigned int GetNumBSGNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumBSGNRecords(ModName);
    }

unsigned int GetNumACTIRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumACTIRecords(ModName);
    }

unsigned int GetNumAPPARecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumAPPARecords(ModName);
    }

unsigned int GetNumARMORecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumARMORecords(ModName);
    }

unsigned int GetNumBOOKRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumBOOKRecords(ModName);
    }

unsigned int GetNumCLOTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumCLOTRecords(ModName);
    }

unsigned int GetNumCONTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumCONTRecords(ModName);
    }

unsigned int GetNumDOORRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumDOORRecords(ModName);
    }

unsigned int GetNumINGRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumINGRRecords(ModName);
    }

unsigned int GetNumLIGHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumLIGHRecords(ModName);
    }

unsigned int GetNumMISCRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumMISCRecords(ModName);
    }

unsigned int GetNumSTATRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumSTATRecords(ModName);
    }

unsigned int GetNumGRASRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumGRASRecords(ModName);
    }

unsigned int GetNumTREERecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumTREERecords(ModName);
    }

unsigned int GetNumFLORRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumFLORRecords(ModName);
    }

unsigned int GetNumFURNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumFURNRecords(ModName);
    }

unsigned int GetNumWEAPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumWEAPRecords(ModName);
    }

unsigned int GetNumAMMORecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumAMMORecords(ModName);
    }

unsigned int GetNumNPC_Records(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumNPC_Records(ModName);
    }

unsigned int GetNumCREARecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumCREARecords(ModName);
    }

unsigned int GetNumLVLCRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumLVLCRecords(ModName);
    }

unsigned int GetNumSLGMRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumSLGMRecords(ModName);
    }

unsigned int GetNumKEYMRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumKEYMRecords(ModName);
    }

unsigned int GetNumALCHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumALCHRecords(ModName);
    }

unsigned int GetNumSBSPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumSBSPRecords(ModName);
    }

unsigned int GetNumSGSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumSGSTRecords(ModName);
    }

unsigned int GetNumLVLIRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumLVLIRecords(ModName);
    }

unsigned int GetNumWTHRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumWTHRRecords(ModName);
    }

unsigned int GetNumCLMTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumCLMTRecords(ModName);
    }

unsigned int GetNumREGNRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumREGNRecords(ModName);
    }

unsigned int GetNumCELLRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumCELLRecords(ModName);
    }

unsigned int GetNumACHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->GetNumACHRRecords(ModName, parentFID);
    }

unsigned int GetNumACRERecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->GetNumACRERecords(ModName, parentFID);
    }

unsigned int GetNumREFRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->GetNumREFRRecords(ModName, parentFID);
    }

unsigned int GetNumWRLDRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumWRLDRecords(ModName);
    }

unsigned int GetNumDIALRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumDIALRecords(ModName);
    }

unsigned int GetNumQUSTRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumQUSTRecords(ModName);
    }

unsigned int GetNumIDLERecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumIDLERecords(ModName);
    }

unsigned int GetNumPACKRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumPACKRecords(ModName);
    }

unsigned int GetNumCSTYRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumCSTYRecords(ModName);
    }

unsigned int GetNumLSCRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumLSCRRecords(ModName);
    }

unsigned int GetNumLVSPRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumLVSPRecords(ModName);
    }

unsigned int GetNumANIORecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumANIORecords(ModName);
    }

unsigned int GetNumWATRRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumWATRRecords(ModName);
    }

unsigned int GetNumEFSHRecords(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->GetNumEFSHRecords(ModName);
    }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int GetTES4FieldType(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
    {
    return Collections[CollectionIndex]->GetTES4FieldType(ModName, Field);
    }

unsigned int GetTES4FieldArraySize(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
    {
    return Collections[CollectionIndex]->GetTES4FieldArraySize(ModName, Field);
    }

void GetTES4FieldArray(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, void **FieldValues)
    {
    Collections[CollectionIndex]->GetTES4FieldArray(ModName, Field, FieldValues);
    }

void * ReadTES4Field(const unsigned int CollectionIndex, char *ModName, const unsigned int Field)
    {
    return Collections[CollectionIndex]->ReadTES4Field(ModName, Field);
    }

////////////////////////////////////////////////////////////////////////
int SetTES4FieldStr(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, char *FieldValue)
    {
    try
        {
        Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
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
        Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
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
        Collections[CollectionIndex]->SetTES4Field(ModName, Field, FieldValue);
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
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void GetGMSTs(const unsigned int CollectionIndex, char *ModName, char **RecordEIDs)
    {
    Collections[CollectionIndex]->GetGMSTRecords(ModName, RecordEIDs);
    }

int GetGMSTFieldType(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field)
    {
    return Collections[CollectionIndex]->GetGMSTFieldType(ModName, recordEDID, Field);
    }

void * ReadGMSTField(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field)
    {
    return Collections[CollectionIndex]->ReadGMSTField(ModName, recordEDID, Field);
    }

////////////////////////////////////////////////////////////////////////
unsigned int CreateGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID)
    {
    return Collections[CollectionIndex]->CreateGMSTRecord(ModName, recordEDID);
    }

unsigned int CopyGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID, char *destModName)
    {
    return Collections[CollectionIndex]->CopyGMSTRecord(ModName, recordEDID, destModName);
    }

////////////////////////////////////////////////////////////////////////
int SetGMSTFieldStr(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, char *FieldValue)
    {
    try
        {
        Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetGMSTField(ModName, recordEDID, Field, FieldValue);
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
    Collections[CollectionIndex]->GetGLOBRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetCLASRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetCLASRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetFACTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetFACTRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetHAIRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetHAIRRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetEYESRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetEYESRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetRACERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetRACERecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetSOUNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetSOUNRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetSKILRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetSKILRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetMGEFRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetMGEFRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetSCPTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetSCPTRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetLTEXRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetLTEXRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetENCHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetENCHRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetSPELRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetSPELRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetBSGNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetBSGNRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetACTIRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetACTIRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetAPPARecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetAPPARecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetARMORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetARMORecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetBOOKRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetBOOKRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetCLOTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetCLOTRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetCONTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetCONTRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetDOORRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetDOORRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetINGRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetINGRRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetLIGHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetLIGHRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetMISCRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetMISCRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetSTATRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetSTATRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetGRASRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetGRASRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetTREERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetTREERecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetFLORRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetFLORRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetFURNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetFURNRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetWEAPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetWEAPRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetAMMORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetAMMORecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetNPC_Records(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetNPC_Records(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetCREARecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetCREARecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetLVLCRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetLVLCRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetSLGMRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetSLGMRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetKEYMRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetKEYMRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetALCHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetALCHRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetSBSPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetSBSPRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetSGSTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetSGSTRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetLVLIRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetLVLIRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetWTHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetWTHRRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetCLMTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetCLMTRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetREGNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetREGNRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetCELLRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetCELLRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetACHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetACHRRecords(ModName, parentFID, RecordFIDs);
    return 0;
    }

unsigned int GetACRERecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetACRERecords(ModName, parentFID, RecordFIDs);
    return 0;
    }

unsigned int GetREFRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetREFRRecords(ModName, parentFID, RecordFIDs);
    return 0;
    }

unsigned int GetWRLDRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetWRLDRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetDIALRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetDIALRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetQUSTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetQUSTRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetIDLERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetIDLERecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetPACKRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetPACKRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetCSTYRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetCSTYRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetLSCRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetLSCRRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetLVSPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetLVSPRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetANIORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetANIORecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetWATRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetWATRRecords(ModName, RecordFIDs);
    return 0;
    }

unsigned int GetEFSHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs)
    {
    Collections[CollectionIndex]->GetEFSHRecords(ModName, RecordFIDs);
    return 0;
    }

////////////////////////////////////////////////////////////////////////
int GetFIDFieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    return Collections[CollectionIndex]->GetFIDFieldType(ModName, recordFID, Field);
    }

int GetFIDListFieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField)
    {
    return Collections[CollectionIndex]->GetFIDListFieldType(ModName, recordFID, subField, listField);
    }

int GetFIDListX2FieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field)
    {
    return Collections[CollectionIndex]->GetFIDListX2FieldType(ModName, recordFID, subField, listField, listX2Field);
    }

int GetFIDListX3FieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field)
    {
    return Collections[CollectionIndex]->GetFIDListX3FieldType(ModName, recordFID, subField, listField, listX2Field, listX3Field);
    }
////////////////////////////////////////////////////////////////////////
unsigned int GetFIDFieldArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    return Collections[CollectionIndex]->GetFIDFieldArraySize(ModName, recordFID, Field);
    }
unsigned int GetFIDListArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    return Collections[CollectionIndex]->GetFIDListArraySize(ModName, recordFID, subField, listIndex, listField);
    }
unsigned int GetFIDListX2ArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    return Collections[CollectionIndex]->GetFIDListX2ArraySize(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
    }
unsigned int GetFIDListX3ArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    return Collections[CollectionIndex]->GetFIDListX3ArraySize(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
    }
////////////////////////////////////////////////////////////////////////
unsigned int GetFIDListSize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    return Collections[CollectionIndex]->GetFIDListSize(ModName, recordFID, Field);
    }
unsigned int GetFIDListX2Size(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    return Collections[CollectionIndex]->GetFIDListX2Size(ModName, recordFID, subField, listIndex, listField);
    }
unsigned int GetFIDListX3Size(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    return Collections[CollectionIndex]->GetFIDListX3Size(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
    }
////////////////////////////////////////////////////////////////////////
void GetFIDFieldArray(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, void **FieldValues)
    {
    return Collections[CollectionIndex]->GetFIDFieldArray(ModName, recordFID, Field, FieldValues);
    }
void GetFIDListArray(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    return Collections[CollectionIndex]->GetFIDListArray(ModName, recordFID, subField, listIndex, listField, FieldValues);
    }
void GetFIDListX2Array(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
    {
    return Collections[CollectionIndex]->GetFIDListX2Array(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValues);
    }
void GetFIDListX3Array(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues)
    {
    return Collections[CollectionIndex]->GetFIDListX3Array(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValues);
    }
////////////////////////////////////////////////////////////////////////
void * ReadFIDField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    return Collections[CollectionIndex]->ReadFIDField(ModName, recordFID, Field);
    }

void * ReadFIDListField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    return Collections[CollectionIndex]->ReadFIDListField(ModName, recordFID, subField, listIndex, listField);
    }

void * ReadFIDListX2Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    return Collections[CollectionIndex]->ReadFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
    }

void * ReadFIDListX3Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    return Collections[CollectionIndex]->ReadFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
    }
////////////////////////////////////////////////////////////////////////
//ADD
unsigned int CreateGLOBRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateGLOBRecord(ModName);
    }

unsigned int CreateCLASRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateCLASRecord(ModName);
    }

unsigned int CreateFACTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateFACTRecord(ModName);
    }

unsigned int CreateHAIRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateHAIRRecord(ModName);
    }

unsigned int CreateEYESRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateEYESRecord(ModName);
    }

unsigned int CreateRACERecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateRACERecord(ModName);
    }

unsigned int CreateSOUNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateSOUNRecord(ModName);
    }

unsigned int CreateSKILRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateSKILRecord(ModName);
    }

unsigned int CreateMGEFRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateMGEFRecord(ModName);
    }

unsigned int CreateSCPTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateSCPTRecord(ModName);
    }

unsigned int CreateLTEXRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateLTEXRecord(ModName);
    }

unsigned int CreateENCHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateENCHRecord(ModName);
    }

unsigned int CreateSPELRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateSPELRecord(ModName);
    }

unsigned int CreateBSGNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateBSGNRecord(ModName);
    }

unsigned int CreateACTIRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateACTIRecord(ModName);
    }

unsigned int CreateAPPARecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateAPPARecord(ModName);
    }

unsigned int CreateARMORecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateARMORecord(ModName);
    }

unsigned int CreateBOOKRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateBOOKRecord(ModName);
    }

unsigned int CreateCLOTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateCLOTRecord(ModName);
    }

unsigned int CreateCONTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateCONTRecord(ModName);
    }

unsigned int CreateDOORRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateDOORRecord(ModName);
    }

unsigned int CreateINGRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateINGRRecord(ModName);
    }

unsigned int CreateLIGHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateLIGHRecord(ModName);
    }

unsigned int CreateMISCRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateMISCRecord(ModName);
    }

unsigned int CreateSTATRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateSTATRecord(ModName);
    }

unsigned int CreateGRASRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateGRASRecord(ModName);
    }

unsigned int CreateTREERecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateTREERecord(ModName);
    }

unsigned int CreateFLORRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateFLORRecord(ModName);
    }

unsigned int CreateFURNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateFURNRecord(ModName);
    }

unsigned int CreateWEAPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateWEAPRecord(ModName);
    }

unsigned int CreateAMMORecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateAMMORecord(ModName);
    }

unsigned int CreateNPC_Record(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateNPC_Record(ModName);
    }

unsigned int CreateCREARecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateCREARecord(ModName);
    }

unsigned int CreateLVLCRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateLVLCRecord(ModName);
    }

unsigned int CreateSLGMRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateSLGMRecord(ModName);
    }

unsigned int CreateKEYMRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateKEYMRecord(ModName);
    }

unsigned int CreateALCHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateALCHRecord(ModName);
    }

unsigned int CreateSBSPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateSBSPRecord(ModName);
    }

unsigned int CreateSGSTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateSGSTRecord(ModName);
    }

unsigned int CreateLVLIRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateLVLIRecord(ModName);
    }

unsigned int CreateWTHRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateWTHRRecord(ModName);
    }

unsigned int CreateCLMTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateCLMTRecord(ModName);
    }

unsigned int CreateREGNRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateREGNRecord(ModName);
    }

unsigned int CreateCELLRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->CreateCELLRecord(ModName, parentFID);
    }

unsigned int CreateACHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->CreateACHRRecord(ModName, parentFID);
    }

unsigned int CreateACRERecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->CreateACRERecord(ModName, parentFID);
    }

unsigned int CreateREFRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->CreateREFRRecord(ModName, parentFID);
    }

unsigned int CreatePGRDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->CreatePGRDRecord(ModName, parentFID);
    }

unsigned int CreateWRLDRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateWRLDRecord(ModName);
    }

unsigned int CreateROADRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->CreateROADRecord(ModName, parentFID);
    }

unsigned int CreateLANDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->CreateLANDRecord(ModName, parentFID);
    }


unsigned int CreateDIALRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateDIALRecord(ModName);
    }

unsigned int CreateINFORecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID)
    {
    return Collections[CollectionIndex]->CreateINFORecord(ModName, parentFID);
    }

unsigned int CreateQUSTRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateQUSTRecord(ModName);
    }

unsigned int CreateIDLERecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateIDLERecord(ModName);
    }

unsigned int CreatePACKRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreatePACKRecord(ModName);
    }

unsigned int CreateCSTYRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateCSTYRecord(ModName);
    }

unsigned int CreateLSCRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateLSCRRecord(ModName);
    }

unsigned int CreateLVSPRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateLVSPRecord(ModName);
    }

unsigned int CreateANIORecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateANIORecord(ModName);
    }

unsigned int CreateWATRRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateWATRRecord(ModName);
    }

unsigned int CreateEFSHRecord(const unsigned int CollectionIndex, char *ModName)
    {
    return Collections[CollectionIndex]->CreateEFSHRecord(ModName);
    }
////////////////////////////////////////////////////////////////////////
//ADD
unsigned int CopyFIDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyFIDRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyGLOBRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyGLOBRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyCLASRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyCLASRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyFACTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyFACTRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyHAIRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyHAIRRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyEYESRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyEYESRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyRACERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyRACERecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopySOUNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopySOUNRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopySKILRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopySKILRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyMGEFRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyMGEFRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopySCPTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopySCPTRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyLTEXRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyLTEXRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyENCHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyENCHRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopySPELRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopySPELRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyBSGNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyBSGNRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyACTIRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyACTIRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyAPPARecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyAPPARecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyARMORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyARMORecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyBOOKRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyBOOKRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyCLOTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyCLOTRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyCONTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyCONTRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyDOORRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyDOORRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyINGRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyINGRRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyLIGHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyLIGHRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyMISCRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyMISCRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopySTATRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopySTATRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyGRASRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyGRASRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyTREERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyTREERecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyFLORRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyFLORRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyFURNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyFURNRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyWEAPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyWEAPRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyAMMORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyAMMORecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyNPC_Record(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyNPC_Record(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyCREARecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyCREARecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyLVLCRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyLVLCRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopySLGMRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopySLGMRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyKEYMRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyKEYMRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyALCHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyALCHRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopySBSPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopySBSPRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopySGSTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopySGSTRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyLVLIRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyLVLIRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyWTHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyWTHRRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyCLMTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyCLMTRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyREGNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyREGNRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyCELLRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyCELLRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
    }

unsigned int CopyACHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyACHRRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
    }

unsigned int CopyACRERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyACRERecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
    }

unsigned int CopyREFRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyREFRRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
    }

unsigned int CopyPGRDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyPGRDRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
    }

unsigned int CopyWRLDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyWRLDRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyROADRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyROADRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
    }

unsigned int CopyLANDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyLANDRecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
    }

unsigned int CopyDIALRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyDIALRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyINFORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyINFORecord(ModName, srcRecordFID, destModName, destParentFID, asOverride);
    }

unsigned int CopyQUSTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyQUSTRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyIDLERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyIDLERecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyPACKRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyPACKRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyCSTYRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyCSTYRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyLSCRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyLSCRRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyLVSPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyLVSPRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyANIORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyANIORecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyWATRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyWATRRecord(ModName, srcRecordFID, destModName, asOverride);
    }

unsigned int CopyEFSHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return Collections[CollectionIndex]->CopyEFSHRecord(ModName, srcRecordFID, destModName, asOverride);
    }

////////////////////////////////////////////////////////////////////////
int SetFIDFieldC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char FieldValue)
    {
    try
        {
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDField(ModName, recordFID, Field, FieldValue);
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
////////////////////////////////////////////////////////////////////////
int CreateFIDListElement(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField)
    {
    return Collections[CollectionIndex]->CreateFIDListElement(ModName, recordFID, subField);
    }
int CreateFIDListX2Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    return Collections[CollectionIndex]->CreateFIDListX2Element(ModName, recordFID, subField, listIndex, listField);
    }
int CreateFIDListX3Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    return Collections[CollectionIndex]->CreateFIDListX3Element(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
    }
////////////////////////////////////////////////////////////////////////
int DeleteFIDListElement(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField)
    {
    return Collections[CollectionIndex]->DeleteFIDListElement(ModName, recordFID, subField);
    }
int DeleteFIDListX2Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    return Collections[CollectionIndex]->DeleteFIDListX2Element(ModName, recordFID, subField, listIndex, listField);
    }
int DeleteFIDListX3Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    return Collections[CollectionIndex]->DeleteFIDListX3Element(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field);
    }
////////////////////////////////////////////////////////////////////////
int SetFIDListFieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char FieldValue)
    {
    try
        {
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListField(ModName, recordFID, subField, listIndex, listField, FieldValue);
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
////////////////////////////////////////////////////////////////////////
int SetFIDListX2FieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char FieldValue)
    {
    try
        {
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX2Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
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
////////////////////////////////////////////////////////////////////////
int SetFIDListX3FieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char FieldValue)
    {
    try
        {
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
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
        Collections[CollectionIndex]->SetFIDListX3Field(ModName, recordFID, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
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
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//ADD
unsigned int StartGLOBIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eGLOB));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartCLASIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLAS));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartFACTIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eFACT));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartHAIRIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eHAIR));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartEYESIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eEYES));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartRACEIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eRACE));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartSOUNIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eSOUN));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartSKILIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eSKIL));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartMGEFIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eMGEF));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartSCPTIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eSCPT));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartLTEXIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eLTEX));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartENCHIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eENCH));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartSPELIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eSPEL));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartBSGNIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eBSGN));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartACTIIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eACTI));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartAPPAIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eAPPA));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartARMOIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eARMO));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartBOOKIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eBOOK));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartCLOTIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLOT));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartCONTIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eCONT));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartDOORIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eDOOR));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartINGRIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eINGR));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartLIGHIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eLIGH));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartMISCIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eMISC));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartSTATIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eSTAT));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartGRASIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eGRAS));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartTREEIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eTREE));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartFLORIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eFLOR));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartFURNIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eFURN));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartWEAPIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eWEAP));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartAMMOIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eAMMO));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartNPC_Iterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eNPC_));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartCREAIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eCREA));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartLVLCIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVLC));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartSLGMIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eSLGM));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartKEYMIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eKEYM));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartALCHIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eALCH));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartSBSPIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eSBSP));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartSGSTIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eSGST));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartLVLIIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVLI));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartWTHRIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eWTHR));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartCLMTIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eCLMT));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartREGNIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eREGN));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartCELLIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eCELL));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartWRLDIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eWRLD));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartDIALIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eDIAL));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartQUSTIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eQUST));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartIDLEIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eIDLE));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartPACKIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], ePACK));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartCSTYIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eCSTY));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartLSCRIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eLSCR));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartLVSPIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eLVSP));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartANIOIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eANIO));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartWATRIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eWATR));
    return (unsigned int)Iterators.size() - 1;
    }

unsigned int StartEFSHIterator(const unsigned int CollectionIndex)
    {
    Iterators.push_back(new Iterator(Collections[CollectionIndex], eEFSH));
    return (unsigned int)Iterators.size() - 1;
    }

////////////////////////////////////////////////////////////////////////
long long IncrementIterator(const unsigned int IteratorID)
    {
    return Iterators[IteratorID]->IncrementIterator();
    }

void StopIterator(const unsigned int IteratorID)
    {
    Iterators.erase(Iterators.begin() + IteratorID);
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
