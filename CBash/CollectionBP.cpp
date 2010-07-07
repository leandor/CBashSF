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
#include "Collection.h"

unsigned int Collection::GetNumGMSTRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->GMST.Records.size();
    }

unsigned int Collection::GetNumGLOBRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->GLOB.Records.size();
    }

unsigned int Collection::GetNumCLASRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->CLAS.Records.size();
    }

unsigned int Collection::GetNumFACTRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->FACT.Records.size();
    }

unsigned int Collection::GetNumHAIRRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->HAIR.Records.size();
    }

unsigned int Collection::GetNumEYESRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->EYES.Records.size();
    }

unsigned int Collection::GetNumRACERecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->RACE.Records.size();
    }

unsigned int Collection::GetNumSOUNRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->SOUN.Records.size();
    }

unsigned int Collection::GetNumSKILRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->SKIL.Records.size();
    }

unsigned int Collection::GetNumMGEFRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->MGEF.Records.size();
    }

unsigned int Collection::GetNumSCPTRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->SCPT.Records.size();
    }

unsigned int Collection::GetNumLTEXRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->LTEX.Records.size();
    }

unsigned int Collection::GetNumENCHRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->ENCH.Records.size();
    }

unsigned int Collection::GetNumSPELRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->SPEL.Records.size();
    }

unsigned int Collection::GetNumBSGNRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->BSGN.Records.size();
    }

unsigned int Collection::GetNumACTIRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->ACTI.Records.size();
    }

unsigned int Collection::GetNumAPPARecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->APPA.Records.size();
    }

unsigned int Collection::GetNumARMORecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->ARMO.Records.size();
    }

unsigned int Collection::GetNumBOOKRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->BOOK.Records.size();
    }

unsigned int Collection::GetNumCLOTRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->CLOT.Records.size();
    }

unsigned int Collection::GetNumCONTRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->CONT.Records.size();
    }

unsigned int Collection::GetNumDOORRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->DOOR.Records.size();
    }

unsigned int Collection::GetNumINGRRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->INGR.Records.size();
    }

unsigned int Collection::GetNumLIGHRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->LIGH.Records.size();
    }

unsigned int Collection::GetNumMISCRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->MISC.Records.size();
    }

unsigned int Collection::GetNumSTATRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->STAT.Records.size();
    }

unsigned int Collection::GetNumGRASRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->GRAS.Records.size();
    }

unsigned int Collection::GetNumTREERecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->TREE.Records.size();
    }

unsigned int Collection::GetNumFLORRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->FLOR.Records.size();
    }

unsigned int Collection::GetNumFURNRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->FURN.Records.size();
    }

unsigned int Collection::GetNumWEAPRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->WEAP.Records.size();
    }

unsigned int Collection::GetNumAMMORecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->AMMO.Records.size();
    }

unsigned int Collection::GetNumNPC_Records(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->NPC_.Records.size();
    }

unsigned int Collection::GetNumCREARecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->CREA.Records.size();
    }

unsigned int Collection::GetNumLVLCRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->LVLC.Records.size();
    }

unsigned int Collection::GetNumSLGMRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->SLGM.Records.size();
    }

unsigned int Collection::GetNumKEYMRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->KEYM.Records.size();
    }

unsigned int Collection::GetNumALCHRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->ALCH.Records.size();
    }

unsigned int Collection::GetNumSBSPRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->SBSP.Records.size();
    }

unsigned int Collection::GetNumSGSTRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->SGST.Records.size();
    }

unsigned int Collection::GetNumLVLIRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->LVLI.Records.size();
    }

unsigned int Collection::GetNumWTHRRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->WTHR.Records.size();
    }

unsigned int Collection::GetNumCLMTRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->CLMT.Records.size();
    }

unsigned int Collection::GetNumREGNRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->REGN.Records.size();
    }

unsigned int Collection::GetNumCELLRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->CELL.Records.size();
    }

unsigned int Collection::GetNumACHRRecords(char *ModName, unsigned int parentFID)
    {
    unsigned int cSize = 0;
    ModFile *curModFile = NULL;
    CELLRecord *worldCELLRecord = NULL;
    CELLRecord *parentRecord = NULL;
    ACHRRecord *curRecord = NULL;
    int gridX = 0, gridY = 0;

    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(curModFile == NULL || parentRecord == NULL)
        return 0;
    worldCELLRecord = LookupWorldCELL(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->ACHR.size();
    //There might be ACHR records in the World CELL if it exists
    if(worldCELLRecord != NULL)
        {
        parentRecord->Read(curModFile->FormIDHandler);
        for(unsigned int x = 0; x < worldCELLRecord->ACHR.size();)
            {
            curRecord = worldCELLRecord->ACHR[x];
            //Have to test each ACHR to see if it belongs to the cell. This is determined by its positioning.
            curRecord->Read(curModFile->FormIDHandler);
            ResolveGrid(curRecord->DATA.value.posX, curRecord->DATA.value.posY, gridX, gridY);
            curRecord->Unload();
            parentRecord->XCLC.Load();
            if(gridX == parentRecord->XCLC->posX && gridY == parentRecord->XCLC->posY)
                {
                //For easier use later on, go ahead and move it to the parent cell.
                //It will get moved back later during the save process if need be.
                parentRecord->ACHR.push_back(curRecord);
                worldCELLRecord->ACHR.erase(worldCELLRecord->ACHR.begin() + x);
                ++cSize;
                }
            else ++x;
            }
        parentRecord->Unload();
        }
    return cSize;
    }

unsigned int Collection::GetNumACRERecords(char *ModName, unsigned int parentFID)
    {
    unsigned int cSize = 0;
    ModFile *curModFile = NULL;
    CELLRecord *worldCELLRecord = NULL;
    CELLRecord *parentRecord = NULL;
    ACRERecord *curRecord = NULL;
    int gridX = 0, gridY = 0;

    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(curModFile == NULL ||parentRecord == NULL)
        return 0;
    worldCELLRecord = LookupWorldCELL(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->ACRE.size();
    //There might be ACRE records in the World CELL if it exists
    if(worldCELLRecord != NULL)
        {
        parentRecord->Read(curModFile->FormIDHandler);
        for(unsigned int x = 0; x < worldCELLRecord->ACRE.size();)
            {
            curRecord = worldCELLRecord->ACRE[x];
            //Have to test each ACRE to see if it belongs to the cell. This is determined by its positioning.
            curRecord->Read(curModFile->FormIDHandler);
            ResolveGrid(curRecord->DATA.value.posX, curRecord->DATA.value.posY, gridX, gridY);
            curRecord->Unload();
            parentRecord->XCLC.Load();
            if(gridX == parentRecord->XCLC->posX && gridY == parentRecord->XCLC->posY)
                {
                //For easier use later on, go ahead and move it to the parent cell.
                //It will get moved back later during the save process if need be.
                parentRecord->ACRE.push_back(curRecord);
                worldCELLRecord->ACRE.erase(worldCELLRecord->ACRE.begin() + x);
                ++cSize;
                }
            else ++x;
            }
        parentRecord->Unload();
        }
    return cSize;
    }

unsigned int Collection::GetNumREFRRecords(char *ModName, unsigned int parentFID)
    {
    unsigned int cSize = 0;
    ModFile *curModFile = NULL;
    CELLRecord *worldCELLRecord = NULL;
    CELLRecord *parentRecord = NULL;
    REFRRecord *curRecord = NULL;
    int gridX = 0, gridY = 0;

    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(curModFile == NULL ||parentRecord == NULL)
        return 0;
    worldCELLRecord = LookupWorldCELL(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->REFR.size();
    //There might be REFR records in the World CELL if it exists
    if(worldCELLRecord != NULL)
        {
        parentRecord->Read(curModFile->FormIDHandler);
        for(unsigned int x = 0; x < worldCELLRecord->REFR.size();)
            {
            curRecord = worldCELLRecord->REFR[x];
            //Have to test each REFR to see if it belongs to the cell. This is determined by its positioning.
            curRecord->Read(curModFile->FormIDHandler);
            ResolveGrid(curRecord->DATA.value.posX, curRecord->DATA.value.posY, gridX, gridY);
            curRecord->Unload();
            parentRecord->XCLC.Load();
            if(gridX == parentRecord->XCLC->posX && gridY == parentRecord->XCLC->posY)
                {
                //For easier use later on, go ahead and move it to the parent cell.
                //It will get moved back later during the save process if need be.
                parentRecord->REFR.push_back(curRecord);
                worldCELLRecord->REFR.erase(worldCELLRecord->REFR.begin() + x);
                ++cSize;
                }
            else ++x;
            }
        parentRecord->Unload();
        }
    return cSize;
    }

unsigned int Collection::GetNumWRLDRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->WRLD.Records.size();
    }

unsigned int Collection::GetNumDIALRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->DIAL.Records.size();
    }

unsigned int Collection::GetNumQUSTRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->QUST.Records.size();
    }

unsigned int Collection::GetNumIDLERecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->IDLE.Records.size();
    }

unsigned int Collection::GetNumPACKRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->PACK.Records.size();
    }

unsigned int Collection::GetNumCSTYRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->CSTY.Records.size();
    }

unsigned int Collection::GetNumLSCRRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->LSCR.Records.size();
    }

unsigned int Collection::GetNumLVSPRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->LVSP.Records.size();
    }

unsigned int Collection::GetNumANIORecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->ANIO.Records.size();
    }

unsigned int Collection::GetNumWATRRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->WATR.Records.size();
    }

unsigned int Collection::GetNumEFSHRecords(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->EFSH.Records.size();
    }
//ADD DEFINITIONS HERE

void Collection::GetGMSTRecords(char *ModName, char **RecordEIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->GMST.Records.size(); x++)
        RecordEIDs[x] = curModFile->GMST.Records[x]->EDID.value;
    return;
    }

void Collection::GetGLOBRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->GLOB.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->GLOB.Records[x]->formID;
    return;
    }

void Collection::GetCLASRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->CLAS.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->CLAS.Records[x]->formID;
    return;
    }

void Collection::GetFACTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->FACT.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->FACT.Records[x]->formID;
    return;
    }

void Collection::GetHAIRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->HAIR.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->HAIR.Records[x]->formID;
    return;
    }

void Collection::GetEYESRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->EYES.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->EYES.Records[x]->formID;
    return;
    }

void Collection::GetRACERecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->RACE.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->RACE.Records[x]->formID;
    return;
    }

void Collection::GetSOUNRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->SOUN.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->SOUN.Records[x]->formID;
    return;
    }

void Collection::GetSKILRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->SKIL.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->SKIL.Records[x]->formID;
    return;
    }

void Collection::GetMGEFRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->MGEF.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->MGEF.Records[x]->formID;
    return;
    }

void Collection::GetSCPTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->SCPT.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->SCPT.Records[x]->formID;
    return;
    }

void Collection::GetLTEXRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->LTEX.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->LTEX.Records[x]->formID;
    return;
    }

void Collection::GetENCHRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->ENCH.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->ENCH.Records[x]->formID;
    return;
    }

void Collection::GetSPELRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->SPEL.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->SPEL.Records[x]->formID;
    return;
    }

void Collection::GetBSGNRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->BSGN.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->BSGN.Records[x]->formID;
    return;
    }

void Collection::GetACTIRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->ACTI.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->ACTI.Records[x]->formID;
    return;
    }

void Collection::GetAPPARecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->APPA.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->APPA.Records[x]->formID;
    return;
    }

void Collection::GetARMORecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->ARMO.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->ARMO.Records[x]->formID;
    return;
    }

void Collection::GetBOOKRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->BOOK.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->BOOK.Records[x]->formID;
    return;
    }

void Collection::GetCLOTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->CLOT.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->CLOT.Records[x]->formID;
    return;
    }

void Collection::GetCONTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->CONT.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->CONT.Records[x]->formID;
    return;
    }

void Collection::GetDOORRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->DOOR.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->DOOR.Records[x]->formID;
    return;
    }

void Collection::GetINGRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->INGR.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->INGR.Records[x]->formID;
    return;
    }

void Collection::GetLIGHRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->LIGH.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->LIGH.Records[x]->formID;
    return;
    }

void Collection::GetMISCRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->MISC.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->MISC.Records[x]->formID;
    return;
    }

void Collection::GetSTATRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->STAT.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->STAT.Records[x]->formID;
    return;
    }

void Collection::GetGRASRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->GRAS.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->GRAS.Records[x]->formID;
    return;
    }

void Collection::GetTREERecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->TREE.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->TREE.Records[x]->formID;
    return;
    }

void Collection::GetFLORRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->FLOR.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->FLOR.Records[x]->formID;
    return;
    }

void Collection::GetFURNRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->FURN.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->FURN.Records[x]->formID;
    return;
    }

void Collection::GetWEAPRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->WEAP.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->WEAP.Records[x]->formID;
    return;
    }

void Collection::GetAMMORecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->AMMO.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->AMMO.Records[x]->formID;
    return;
    }

void Collection::GetNPC_Records(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->NPC_.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->NPC_.Records[x]->formID;
    return;
    }

void Collection::GetCREARecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->CREA.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->CREA.Records[x]->formID;
    return;
    }

void Collection::GetLVLCRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->LVLC.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->LVLC.Records[x]->formID;
    return;
    }

void Collection::GetSLGMRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->SLGM.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->SLGM.Records[x]->formID;
    return;
    }

void Collection::GetKEYMRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->KEYM.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->KEYM.Records[x]->formID;
    return;
    }

void Collection::GetALCHRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->ALCH.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->ALCH.Records[x]->formID;
    return;
    }

void Collection::GetSBSPRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->SBSP.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->SBSP.Records[x]->formID;
    return;
    }

void Collection::GetSGSTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->SGST.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->SGST.Records[x]->formID;
    return;
    }

void Collection::GetLVLIRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->LVLI.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->LVLI.Records[x]->formID;
    return;
    }

void Collection::GetWTHRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->WTHR.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->WTHR.Records[x]->formID;
    return;
    }

void Collection::GetCLMTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->CLMT.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->CLMT.Records[x]->formID;
    return;
    }

void Collection::GetREGNRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->REGN.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->REGN.Records[x]->formID;
    return;
    }

void Collection::GetCELLRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->CELL.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->CELL.Records[x]->formID;
    return;
    }

void Collection::GetACHRRecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = NULL;
    CELLRecord *parentRecord = NULL;
    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(curModFile == NULL || parentRecord == NULL)
        return;
    for(unsigned int x = 0; x < parentRecord->ACHR.size(); x++)
        RecordFIDs[x] = &parentRecord->ACHR[x]->formID;
    return;
    }

void Collection::GetACRERecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = NULL;
    CELLRecord *parentRecord = NULL;
    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(curModFile == NULL || parentRecord == NULL)
        return;
    for(unsigned int x = 0; x < parentRecord->ACRE.size(); x++)
        RecordFIDs[x] = &parentRecord->ACRE[x]->formID;
    return;
    }

void Collection::GetREFRRecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = NULL;
    CELLRecord *parentRecord = NULL;
    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(curModFile == NULL || parentRecord == NULL)
        return;
    for(unsigned int x = 0; x < parentRecord->REFR.size(); x++)
        RecordFIDs[x] = &parentRecord->REFR[x]->formID;
    return;
    }

void Collection::GetWRLDRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->WRLD.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->WRLD.Records[x]->formID;
    return;
    }

void Collection::GetDIALRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->DIAL.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->DIAL.Records[x]->formID;
    return;
    }

void Collection::GetQUSTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->QUST.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->QUST.Records[x]->formID;
    return;
    }

void Collection::GetIDLERecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->IDLE.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->IDLE.Records[x]->formID;
    return;
    }

void Collection::GetPACKRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->PACK.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->PACK.Records[x]->formID;
    return;
    }

void Collection::GetCSTYRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->CSTY.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->CSTY.Records[x]->formID;
    return;
    }

void Collection::GetLSCRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->LSCR.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->LSCR.Records[x]->formID;
    return;
    }

void Collection::GetLVSPRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->LVSP.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->LVSP.Records[x]->formID;
    return;
    }

void Collection::GetANIORecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->ANIO.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->ANIO.Records[x]->formID;
    return;
    }

void Collection::GetWATRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->WATR.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->WATR.Records[x]->formID;
    return;
    }

void Collection::GetEFSHRecords(char *ModName, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    for(unsigned int x = 0; x < curModFile->EFSH.Records.size(); ++x)
        RecordFIDs[x] = &curModFile->EFSH.Records[x]->formID;
    return;
    }
//ADD DEFINITIONS HERE
unsigned int Collection::CreateGMSTRecord(char *ModName, char *recordEDID)
    {
    ModFile *curModFile = NULL;
    GMSTRecord *curRecord = NULL;
    //Check and see if the GMST already exists
    LookupGMSTRecord(ModName, recordEDID, curModFile, curRecord);
    if(curModFile != NULL || curRecord != NULL)
        return 0;

    curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    curRecord = new GMSTRecord(newRecordFID, recordEDID);
    curModFile->GMST.Records.push_back(curRecord);
    GMST_ModFile_Record.insert(std::make_pair(curRecord->EDID.value,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CopyGMSTRecord(char *ModName, char *srcRecordEDID, char *destModName)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    GMSTRecord *srcRecord = NULL;
    GMSTRecord *copyRecord = NULL;

    //Check and see if the GMST already exists
    LookupGMSTRecord(destModName, srcRecordEDID, destMod, copyRecord);
    if(destMod != NULL || copyRecord != NULL)
        return 0;

    destMod = LookupModFile(destModName);
    if(destMod == NULL)
        return 0;

    LookupGMSTRecord(ModName, srcRecordEDID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new GMSTRecord(srcRecord);
    destMod->GMST.Records.push_back(copyRecord);
    //Add any master as necessary, and register the formID
    copyRecord->AddMasters(destMod->FormIDHandler);
    GMST_ModFile_Record.insert(std::make_pair(copyRecord->EDID.value, std::make_pair(destMod, copyRecord)));
    return 1;
    }

//ADD
unsigned int Collection::CreateGLOBRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    GLOBRecord *curRecord = new GLOBRecord(newRecordFID);
    curModFile->GLOB.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateCLASRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    CLASRecord *curRecord = new CLASRecord(newRecordFID);
    curModFile->CLAS.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateFACTRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    FACTRecord *curRecord = new FACTRecord(newRecordFID);
    curModFile->FACT.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateHAIRRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    HAIRRecord *curRecord = new HAIRRecord(newRecordFID);
    curModFile->HAIR.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateEYESRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    EYESRecord *curRecord = new EYESRecord(newRecordFID);
    curModFile->EYES.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateRACERecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    RACERecord *curRecord = new RACERecord(newRecordFID);
    curModFile->RACE.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateSOUNRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    SOUNRecord *curRecord = new SOUNRecord(newRecordFID);
    curModFile->SOUN.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateSKILRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    SKILRecord *curRecord = new SKILRecord(newRecordFID);
    curModFile->SKIL.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateMGEFRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    MGEFRecord *curRecord = new MGEFRecord(newRecordFID);
    curModFile->MGEF.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateSCPTRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    SCPTRecord *curRecord = new SCPTRecord(newRecordFID);
    curModFile->SCPT.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateLTEXRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    LTEXRecord *curRecord = new LTEXRecord(newRecordFID);
    curModFile->LTEX.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateENCHRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    ENCHRecord *curRecord = new ENCHRecord(newRecordFID);
    curModFile->ENCH.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateSPELRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    SPELRecord *curRecord = new SPELRecord(newRecordFID);
    curModFile->SPEL.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateBSGNRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    BSGNRecord *curRecord = new BSGNRecord(newRecordFID);
    curModFile->BSGN.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateACTIRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    ACTIRecord *curRecord = new ACTIRecord(newRecordFID);
    curModFile->ACTI.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateAPPARecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    APPARecord *curRecord = new APPARecord(newRecordFID);
    curModFile->APPA.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateARMORecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    ARMORecord *curRecord = new ARMORecord(newRecordFID);
    curModFile->ARMO.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateBOOKRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    BOOKRecord *curRecord = new BOOKRecord(newRecordFID);
    curModFile->BOOK.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateCLOTRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    CLOTRecord *curRecord = new CLOTRecord(newRecordFID);
    curModFile->CLOT.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateCONTRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    CONTRecord *curRecord = new CONTRecord(newRecordFID);
    curModFile->CONT.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateDOORRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    DOORRecord *curRecord = new DOORRecord(newRecordFID);
    curModFile->DOOR.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateINGRRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    INGRRecord *curRecord = new INGRRecord(newRecordFID);
    curModFile->INGR.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateLIGHRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    LIGHRecord *curRecord = new LIGHRecord(newRecordFID);
    curModFile->LIGH.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateMISCRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    MISCRecord *curRecord = new MISCRecord(newRecordFID);
    curModFile->MISC.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateSTATRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    STATRecord *curRecord = new STATRecord(newRecordFID);
    curModFile->STAT.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateGRASRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    GRASRecord *curRecord = new GRASRecord(newRecordFID);
    curModFile->GRAS.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateTREERecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    TREERecord *curRecord = new TREERecord(newRecordFID);
    curModFile->TREE.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateFLORRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    FLORRecord *curRecord = new FLORRecord(newRecordFID);
    curModFile->FLOR.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateFURNRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    FURNRecord *curRecord = new FURNRecord(newRecordFID);
    curModFile->FURN.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateWEAPRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    WEAPRecord *curRecord = new WEAPRecord(newRecordFID);
    curModFile->WEAP.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateAMMORecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    AMMORecord *curRecord = new AMMORecord(newRecordFID);
    curModFile->AMMO.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateNPC_Record(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    NPC_Record *curRecord = new NPC_Record(newRecordFID);
    curModFile->NPC_.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateCREARecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    CREARecord *curRecord = new CREARecord(newRecordFID);
    curModFile->CREA.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateLVLCRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    LVLCRecord *curRecord = new LVLCRecord(newRecordFID);
    curModFile->LVLC.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateSLGMRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    SLGMRecord *curRecord = new SLGMRecord(newRecordFID);
    curModFile->SLGM.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateKEYMRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    KEYMRecord *curRecord = new KEYMRecord(newRecordFID);
    curModFile->KEYM.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateALCHRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    ALCHRecord *curRecord = new ALCHRecord(newRecordFID);
    curModFile->ALCH.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateSBSPRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    SBSPRecord *curRecord = new SBSPRecord(newRecordFID);
    curModFile->SBSP.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateSGSTRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    SGSTRecord *curRecord = new SGSTRecord(newRecordFID);
    curModFile->SGST.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateLVLIRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    LVLIRecord *curRecord = new LVLIRecord(newRecordFID);
    curModFile->LVLI.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateWTHRRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    WTHRRecord *curRecord = new WTHRRecord(newRecordFID);
    curModFile->WTHR.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateCLMTRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    CLMTRecord *curRecord = new CLMTRecord(newRecordFID);
    curModFile->CLMT.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateREGNRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    REGNRecord *curRecord = new REGNRecord(newRecordFID);
    curModFile->REGN.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateCELLRecord(char *ModName, unsigned int parentFID, int isWorldCELL)
    {
    ModFile *curModFile = NULL;
    WRLDRecord *parentRecord = NULL;
    bool hasParent = (parentFID != 0);
    if(hasParent)
        {
        LookupRecord(ModName, parentFID, curModFile, parentRecord);
        if(parentRecord == NULL || (isWorldCELL > 0 && parentRecord->CELL != NULL))
            return 0;
        }
    else
        curModFile = LookupModFile(ModName);

    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);

    CELLRecord *curRecord = new CELLRecord(newRecordFID);
    curRecord->IsInterior(!hasParent);
    if(hasParent)
        {
        curRecord->Parent = parentRecord;
        if(isWorldCELL > 0)
            parentRecord->CELL = curRecord;
        else
            parentRecord->CELLS.push_back(curRecord);
        }
    else
        curModFile->CELL.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));

    return newRecordFID;
    }

unsigned int Collection::CreateACHRRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(destMod);
    ACHRRecord *destRecord = new ACHRRecord(newRecordFID);
    destParentRecord->ACHR.push_back(destRecord);
    FID_ModFile_Record.insert(std::make_pair(destRecord->formID,std::make_pair(destMod,destRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateACRERecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(destMod);
    ACRERecord *destRecord = new ACRERecord(newRecordFID);
    destParentRecord->ACRE.push_back(destRecord);
    FID_ModFile_Record.insert(std::make_pair(destRecord->formID,std::make_pair(destMod,destRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateREFRRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(destMod);
    REFRRecord *destRecord = new REFRRecord(newRecordFID);
    destParentRecord->REFR.push_back(destRecord);
    FID_ModFile_Record.insert(std::make_pair(destRecord->formID,std::make_pair(destMod,destRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreatePGRDRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL || destParentRecord->PGRD != NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(destMod);
    destParentRecord->PGRD = new PGRDRecord(newRecordFID);
    FID_ModFile_Record.insert(std::make_pair(destParentRecord->PGRD->formID,std::make_pair(destMod,destParentRecord->PGRD)));
    return newRecordFID;
    }

unsigned int Collection::CreateWRLDRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    WRLDRecord *curRecord = new WRLDRecord(newRecordFID);
    curModFile->WRLD.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateROADRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    WRLDRecord *destParentRecord = NULL;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL || destParentRecord->ROAD != NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(destMod);
    destParentRecord->ROAD = new ROADRecord(newRecordFID);
    FID_ModFile_Record.insert(std::make_pair(destParentRecord->ROAD->formID,std::make_pair(destMod,destParentRecord->ROAD)));
    return newRecordFID;
    }

unsigned int Collection::CreateLANDRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL || destParentRecord->LAND != NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(destMod);
    destParentRecord->LAND = new LANDRecord(newRecordFID);
    FID_ModFile_Record.insert(std::make_pair(destParentRecord->LAND->formID,std::make_pair(destMod,destParentRecord->LAND)));
    return newRecordFID;
    }

unsigned int Collection::CreateDIALRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    DIALRecord *curRecord = new DIALRecord(newRecordFID);
    curModFile->DIAL.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateINFORecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    DIALRecord *destParentRecord = NULL;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(destMod);
    INFORecord *destRecord = new INFORecord(newRecordFID);
    destParentRecord->INFO.push_back(destRecord);
    FID_ModFile_Record.insert(std::make_pair(destRecord->formID,std::make_pair(destMod,destRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateQUSTRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    QUSTRecord *curRecord = new QUSTRecord(newRecordFID);
    curModFile->QUST.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateIDLERecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    IDLERecord *curRecord = new IDLERecord(newRecordFID);
    curModFile->IDLE.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreatePACKRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    PACKRecord *curRecord = new PACKRecord(newRecordFID);
    curModFile->PACK.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateCSTYRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    CSTYRecord *curRecord = new CSTYRecord(newRecordFID);
    curModFile->CSTY.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateLSCRRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    LSCRRecord *curRecord = new LSCRRecord(newRecordFID);
    curModFile->LSCR.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateLVSPRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    LVSPRecord *curRecord = new LVSPRecord(newRecordFID);
    curModFile->LVSP.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateANIORecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    ANIORecord *curRecord = new ANIORecord(newRecordFID);
    curModFile->ANIO.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateWATRRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    WATRRecord *curRecord = new WATRRecord(newRecordFID);
    curModFile->WATR.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CreateEFSHRecord(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;

    unsigned int newRecordFID = NextFreeExpandedFID(curModFile);
    EFSHRecord *curRecord = new EFSHRecord(newRecordFID);
    curModFile->EFSH.Records.push_back(curRecord);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

//ADD
unsigned int Collection::CopyFIDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    return 0;
    //std::multimap<unsigned int, std::pair<ModFile *, Record *> >::iterator it;
    //it = FID_ModFile_Record.find(srcRecordFID);
    //Return if the srcRecordFID isn't found
    //if(it == FID_ModFile_Record.end())
    //    return 0;
    //return 0;
    ////switch(it->second.second->Header.Header.type)
    ////    {
    ////    case eGLOB:
    ////        CopyGLOBRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eCLAS:
    ////        CopyCLASRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eFACT:
    ////        CopyFACTRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eHAIR:
    ////        CopyHAIRRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eEYES:
    ////        CopyEYESRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eRACE:
    ////        CopyRACERecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eSOUN:
    ////        CopySOUNRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eSKIL:
    ////        CopySKILRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eMGEF:
    ////        CopyMGEFRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eSCPT:
    ////        CopySCPTRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eLTEX:
    ////        CopyLTEXRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eENCH:
    ////        CopyENCHRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eSPEL:
    ////        CopySPELRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eBSGN:
    ////        CopyBSGNRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eACTI:
    ////        CopyACTIRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eAPPA:
    ////        CopyAPPARecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eARMO:
    ////        CopyARMORecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eBOOK:
    ////        CopyBOOKRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eCLOT:
    ////        CopyCLOTRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eCONT:
    ////        CopyCONTRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eDOOR:
    ////        CopyDOORRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eINGR:
    ////        CopyINGRRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eLIGH:
    ////        CopyLIGHRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eMISC:
    ////        CopyMISCRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eSTAT:
    ////        CopySTATRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eGRAS:
    ////        CopyGRASRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eTREE:
    ////        CopyTREERecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eFLOR:
    ////        CopyFLORRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eFURN:
    ////        CopyFURNRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eWEAP:
    ////        CopyWEAPRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eAMMO:
    ////        CopyAMMORecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eNPC_:
    ////        CopyNPC_Record(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eCREA:
    ////        CopyCREARecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eLVLC:
    ////        CopyLVLCRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eSLGM:
    ////        CopySLGMRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eKEYM:
    ////        CopyKEYMRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eALCH:
    ////        CopyALCHRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eSBSP:
    ////        CopySBSPRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eSGST:
    ////        CopySGSTRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eLVLI:
    ////        CopyLVLIRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eWTHR:
    ////        CopyWTHRRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eCLMT:
    ////        CopyCLMTRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eREGN:
    ////        CopyREGNRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eQUST:
    ////        CopyQUSTRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eIDLE:
    ////        CopyIDLERecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case ePACK:
    ////        CopyPACKRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eCSTY:
    ////        CopyCSTYRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eLSCR:
    ////        CopyLSCRRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eLVSP:
    ////        CopyLVSPRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eANIO:
    ////        CopyANIORecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eWATR:
    ////        CopyWATRRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    case eEFSH:
    ////        CopyEFSHRecord(ModName, srcRecordFID, destModName, asOverride);
    ////        break;
    ////    default:
    ////        printf("CopyFIDRecord: Unknown recordType, %i\n", it->second.second->Header.Header.type);
    ////        return 0;
    ////    }
    //return 0;
    }
unsigned int Collection::CopyGLOBRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    GLOBRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    GLOBRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new GLOBRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->GLOB.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCLASRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    CLASRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    CLASRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new CLASRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->CLAS.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyFACTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    FACTRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    FACTRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new FACTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->FACT.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyHAIRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    HAIRRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    HAIRRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new HAIRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->HAIR.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyEYESRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    EYESRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    EYESRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new EYESRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->EYES.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyRACERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    RACERecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    RACERecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new RACERecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->RACE.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySOUNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    SOUNRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    SOUNRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new SOUNRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->SOUN.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySKILRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    SKILRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    SKILRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new SKILRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->SKIL.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyMGEFRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    MGEFRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    MGEFRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new MGEFRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->MGEF.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySCPTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    SCPTRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    SCPTRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new SCPTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->SCPT.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLTEXRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    LTEXRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    LTEXRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new LTEXRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->LTEX.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyENCHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ENCHRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    ENCHRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new ENCHRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->ENCH.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySPELRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    SPELRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    SPELRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new SPELRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->SPEL.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyBSGNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    BSGNRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    BSGNRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new BSGNRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->BSGN.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyACTIRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ACTIRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    ACTIRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new ACTIRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->ACTI.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyAPPARecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    APPARecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    APPARecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new APPARecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->APPA.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyARMORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ARMORecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    ARMORecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new ARMORecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->ARMO.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyBOOKRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    BOOKRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    BOOKRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new BOOKRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->BOOK.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCLOTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    CLOTRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    CLOTRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new CLOTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->CLOT.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCONTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    CONTRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    CONTRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new CONTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->CONT.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyDOORRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    DOORRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    DOORRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new DOORRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->DOOR.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyINGRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    INGRRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    INGRRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new INGRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->INGR.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLIGHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    LIGHRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    LIGHRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new LIGHRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->LIGH.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyMISCRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    MISCRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    MISCRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new MISCRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->MISC.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySTATRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    STATRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    STATRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new STATRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->STAT.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyGRASRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    GRASRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    GRASRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new GRASRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->GRAS.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyTREERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    TREERecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    TREERecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new TREERecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->TREE.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyFLORRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    FLORRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    FLORRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new FLORRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->FLOR.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyFURNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    FURNRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    FURNRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new FURNRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->FURN.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyWEAPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    WEAPRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    WEAPRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new WEAPRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->WEAP.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyAMMORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    AMMORecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    AMMORecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new AMMORecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->AMMO.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyNPC_Record(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    NPC_Record *srcRecord = NULL;
    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    NPC_Record *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new NPC_Record(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->NPC_.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCREARecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    CREARecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    CREARecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new CREARecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->CREA.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLVLCRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    LVLCRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    LVLCRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new LVLCRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->LVLC.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySLGMRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    SLGMRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    SLGMRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new SLGMRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->SLGM.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyKEYMRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    KEYMRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    KEYMRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new KEYMRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->KEYM.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyALCHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ALCHRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    ALCHRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new ALCHRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->ALCH.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySBSPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    SBSPRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    SBSPRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new SBSPRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->SBSP.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySGSTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    SGSTRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    SGSTRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new SGSTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->SGST.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLVLIRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    LVLIRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    LVLIRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new LVLIRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->LVLI.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyWTHRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    WTHRRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    WTHRRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new WTHRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->WTHR.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCLMTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    CLMTRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    CLMTRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new CLMTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->CLMT.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyREGNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    REGNRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    REGNRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new REGNRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->REGN.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCELLRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride, int isWorldCELL)
    {
    ModFile *srcMod = NULL;
    CELLRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    if(isWorldCELL == 2 && srcRecord->Parent != NULL)
        if(((WRLDRecord *)srcRecord->Parent)->CELL == srcRecord)
            isWorldCELL = 1;
        else
            isWorldCELL = 0;

    ModFile *destMod = NULL;
    WRLDRecord *destParentRecord = NULL;
    CELLRecord *copyRecord = NULL;

    bool hasParent = (destParentFID != 0);
    if(hasParent)
        {
        //See if the parent world record already exists
        LookupRecord(destModName, destParentFID, destMod, destParentRecord);
        if(destParentRecord == NULL || (isWorldCELL > 0 && destParentRecord->CELL != NULL))
            {
            //If it doesn't, try and create it.
            destParentFID = CopyWRLDRecord(ModName, destParentFID, destModName, asOverride);
            LookupRecord(destModName, destParentFID, destMod, destParentRecord);
            if(destParentRecord == NULL || (isWorldCELL > 0 && destParentRecord->CELL != NULL))
                return 0;
            }
        }
    else
        {
        if(asOverride)
            {
            //See if its trying to copy a record that already exists in the destination mod
            LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
            if(destMod != NULL || copyRecord != NULL)
                return srcRecordFID;
            }
        destMod = LookupModFile(destModName);
        }

    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new CELLRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    copyRecord->IsInterior(!hasParent);
    if(hasParent)
        {
        copyRecord->Parent = destParentRecord;
        if(isWorldCELL > 0)
            destParentRecord->CELL = copyRecord;
        else
            destParentRecord->CELLS.push_back(copyRecord);
        }
    else
        destMod->CELL.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyACHRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ACHRRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    ACHRRecord *copyRecord = NULL;
    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    CELLRecord *destParentRecord = NULL;
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new ACHRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destParentRecord->ACHR.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyACRERecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ACRERecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    ACRERecord *copyRecord = NULL;
    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    CELLRecord *destParentRecord = NULL;
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new ACRERecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destParentRecord->ACRE.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyREFRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    REFRRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    REFRRecord *copyRecord = NULL;
    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    CELLRecord *destParentRecord = NULL;
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new REFRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destParentRecord->REFR.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyPGRDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    PGRDRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    PGRDRecord *copyRecord = NULL;
    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    CELLRecord *destParentRecord = NULL;
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL || destParentRecord->PGRD != NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new PGRDRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destParentRecord->PGRD = copyRecord;
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyWRLDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    WRLDRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    WRLDRecord *copyRecord = NULL;
    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new WRLDRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->WRLD.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyROADRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ROADRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    ROADRecord *copyRecord = NULL;
    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    WRLDRecord *destParentRecord = NULL;
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(destMod == NULL || destParentRecord == NULL || destParentRecord->ROAD != NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new ROADRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destParentRecord->ROAD = copyRecord;
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLANDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    LANDRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    LANDRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    CELLRecord *destParentRecord = NULL;
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(destMod == NULL || destParentRecord == NULL || destParentRecord->LAND != NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new LANDRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destParentRecord->LAND = copyRecord;
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyDIALRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    DIALRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    DIALRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new DIALRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->DIAL.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyINFORecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    INFORecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    INFORecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    DIALRecord *destParentRecord = NULL;
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);
    if(destMod == NULL || destParentRecord == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new INFORecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destParentRecord->INFO.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyQUSTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    QUSTRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    QUSTRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new QUSTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->QUST.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyIDLERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    IDLERecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    IDLERecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new IDLERecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->IDLE.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyPACKRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    PACKRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    PACKRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new PACKRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->PACK.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCSTYRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    CSTYRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    CSTYRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new CSTYRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->CSTY.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLSCRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    LSCRRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    LSCRRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new LSCRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->LSCR.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLVSPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    LVSPRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    LVSPRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new LVSPRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->LVSP.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyANIORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ANIORecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    ANIORecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new ANIORecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->ANIO.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyWATRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    WATRRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    WATRRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new WATRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->WATR.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyEFSHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    EFSHRecord *srcRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(srcMod == NULL || srcRecord == NULL)
        return 0;

    ModFile *destMod = NULL;
    EFSHRecord *copyRecord = NULL;

    if(asOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(destModName, srcRecordFID, destMod, copyRecord);
        if(destMod != NULL || copyRecord != NULL)
            return srcRecordFID;
        }

    destMod = LookupModFile(destModName);
    if(destMod == NULL || srcMod == destMod)
        return 0;

    srcRecord->Read(srcMod->FormIDHandler);
    copyRecord = new EFSHRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);
    copyRecord->AddMasters(destMod->FormIDHandler);

    destMod->EFSH.Records.push_back(copyRecord);
    FID_ModFile_Record.insert(std::make_pair(copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }
