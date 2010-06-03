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
    if(ModName == NULL)
        return (unsigned int)GMST_ModFile_Record.size();
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->GMST.Records.size();
    return 0;
    }

unsigned int Collection::GetNumGLOBRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->GLOB.Records.size();
        return cSize;
        }

    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->GLOB.Records.size();
    return 0;
    }

unsigned int Collection::GetNumCLASRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->CLAS.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->CLAS.Records.size();
    return 0;
    }

unsigned int Collection::GetNumFACTRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->FACT.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->FACT.Records.size();
    return 0;
    }

unsigned int Collection::GetNumHAIRRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->HAIR.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->HAIR.Records.size();
    return 0;
    }

unsigned int Collection::GetNumEYESRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->EYES.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->EYES.Records.size();
    return 0;
    }

unsigned int Collection::GetNumRACERecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->RACE.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->RACE.Records.size();
    return 0;
    }

unsigned int Collection::GetNumSOUNRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->SOUN.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->SOUN.Records.size();
    return 0;
    }

unsigned int Collection::GetNumSKILRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->SKIL.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->SKIL.Records.size();
    return 0;
    }

unsigned int Collection::GetNumMGEFRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->MGEF.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->MGEF.Records.size();
    return 0;
    }

unsigned int Collection::GetNumSCPTRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->SCPT.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->SCPT.Records.size();
    return 0;
    }

unsigned int Collection::GetNumLTEXRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->LTEX.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->LTEX.Records.size();
    return 0;
    }

unsigned int Collection::GetNumENCHRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->ENCH.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->ENCH.Records.size();
    return 0;
    }

unsigned int Collection::GetNumSPELRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->SPEL.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->SPEL.Records.size();
    return 0;
    }

unsigned int Collection::GetNumBSGNRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->BSGN.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->BSGN.Records.size();
    return 0;
    }

unsigned int Collection::GetNumACTIRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->ACTI.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->ACTI.Records.size();
    return 0;
    }

unsigned int Collection::GetNumAPPARecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->APPA.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->APPA.Records.size();
    return 0;
    }

unsigned int Collection::GetNumARMORecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->ARMO.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->ARMO.Records.size();
    return 0;
    }

unsigned int Collection::GetNumBOOKRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->BOOK.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->BOOK.Records.size();
    return 0;
    }

unsigned int Collection::GetNumCLOTRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->CLOT.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->CLOT.Records.size();
    return 0;
    }

unsigned int Collection::GetNumCONTRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->CONT.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->CONT.Records.size();
    return 0;
    }

unsigned int Collection::GetNumDOORRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->DOOR.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->DOOR.Records.size();
    return 0;
    }

unsigned int Collection::GetNumINGRRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->INGR.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->INGR.Records.size();
    return 0;
    }

unsigned int Collection::GetNumLIGHRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->LIGH.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->LIGH.Records.size();
    return 0;
    }

unsigned int Collection::GetNumMISCRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->MISC.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->MISC.Records.size();
    return 0;
    }

unsigned int Collection::GetNumSTATRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->STAT.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->STAT.Records.size();
    return 0;
    }

unsigned int Collection::GetNumGRASRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->GRAS.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->GRAS.Records.size();
    return 0;
    }

unsigned int Collection::GetNumTREERecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->TREE.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->TREE.Records.size();
    return 0;
    }

unsigned int Collection::GetNumFLORRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->FLOR.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->FLOR.Records.size();
    return 0;
    }

unsigned int Collection::GetNumFURNRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->FURN.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->FURN.Records.size();
    return 0;
    }

unsigned int Collection::GetNumWEAPRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->WEAP.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->WEAP.Records.size();
    return 0;
    }

unsigned int Collection::GetNumAMMORecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->AMMO.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->AMMO.Records.size();
    return 0;
    }

unsigned int Collection::GetNumNPC_Records(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->NPC_.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->NPC_.Records.size();
    return 0;
    }

unsigned int Collection::GetNumCREARecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->CREA.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->CREA.Records.size();
    return 0;
    }

unsigned int Collection::GetNumLVLCRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->LVLC.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->LVLC.Records.size();
    return 0;
    }

unsigned int Collection::GetNumSLGMRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->SLGM.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->SLGM.Records.size();
    return 0;
    }

unsigned int Collection::GetNumKEYMRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->KEYM.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->KEYM.Records.size();
    return 0;
    }

unsigned int Collection::GetNumALCHRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->ALCH.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->ALCH.Records.size();
    return 0;
    }

unsigned int Collection::GetNumSBSPRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->SBSP.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->SBSP.Records.size();
    return 0;
    }

unsigned int Collection::GetNumSGSTRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->SGST.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->SGST.Records.size();
    return 0;
    }

unsigned int Collection::GetNumLVLIRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->LVLI.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->LVLI.Records.size();
    return 0;
    }

unsigned int Collection::GetNumWTHRRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->WTHR.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->WTHR.Records.size();
    return 0;
    }

unsigned int Collection::GetNumCLMTRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->CLMT.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->CLMT.Records.size();
    return 0;
    }

unsigned int Collection::GetNumREGNRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->REGN.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->REGN.Records.size();
    return 0;
    }

unsigned int Collection::GetNumCELLRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->CELL.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->CELL.Records.size();
    return 0;
    }

unsigned int Collection::GetNumACHRRecords(char *ModName, unsigned int parentFID)
    {
    if(ModName == NULL)
        return 0;

    unsigned int cSize = 0;
    ModFile *curModFile = NULL;
    CELLRecord *dummyParentRecord = NULL;
    CELLRecord *parentRecord = NULL;
    int gridX = 0, gridY = 0;
    curModFile = LookupModFile(ModName);
    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(parentRecord == NULL || curModFile == NULL)
        return 0;
    dummyParentRecord = LookupWorldCELL(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->ACHR.size();
    if(dummyParentRecord != NULL)
        {
        for(unsigned int x = 0; x < dummyParentRecord->ACHR.size();)
            {
            dummyParentRecord->ACHR[x]->Read(curModFile->FormIDHandler);
            ResolveGrid(dummyParentRecord->ACHR[x]->DATA.value.posX, dummyParentRecord->ACHR[x]->DATA.value.posY, gridX, gridY);
            if(gridX == parentRecord->XCLC.value.posX && gridY == parentRecord->XCLC.value.posY)
                {
                parentRecord->ACHR.push_back(dummyParentRecord->ACHR[x]);
                dummyParentRecord->ACHR.erase(dummyParentRecord->ACHR.begin() + x);
                ++cSize;
                }
            else ++x;
            }
        }
    return cSize;
    }

unsigned int Collection::GetNumACRERecords(char *ModName, unsigned int parentFID)
    {
    if(ModName == NULL)
        return 0;

    unsigned int cSize = 0;
    ModFile *curModFile = NULL;
    CELLRecord *dummyParentRecord = NULL;
    CELLRecord *parentRecord = NULL;
    int gridX = 0, gridY = 0;
    curModFile = LookupModFile(ModName);
    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(parentRecord == NULL || curModFile == NULL)
        return 0;
    dummyParentRecord = LookupWorldCELL(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->ACRE.size();
    if(dummyParentRecord != NULL)
        {
        for(unsigned int x = 0; x < dummyParentRecord->ACRE.size();)
            {
            dummyParentRecord->ACRE[x]->Read(curModFile->FormIDHandler);
            ResolveGrid(dummyParentRecord->ACRE[x]->DATA.value.posX, dummyParentRecord->ACRE[x]->DATA.value.posY, gridX, gridY);
            if(gridX == parentRecord->XCLC.value.posX && gridY == parentRecord->XCLC.value.posY)
                {
                parentRecord->ACRE.push_back(dummyParentRecord->ACRE[x]);
                dummyParentRecord->ACRE.erase(dummyParentRecord->ACRE.begin() + x);
                ++cSize;
                }
            else ++x;
            }
        }
    return cSize;
    }

unsigned int Collection::GetNumREFRRecords(char *ModName, unsigned int parentFID)
    {
    if(ModName == NULL)
        return 0;

    unsigned int cSize = 0;
    ModFile *curModFile = NULL;
    CELLRecord *dummyParentRecord = NULL;
    CELLRecord *parentRecord = NULL;
    int gridX = 0, gridY = 0;
    curModFile = LookupModFile(ModName);
    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(parentRecord == NULL || curModFile == NULL)
        return 0;
    dummyParentRecord = LookupWorldCELL(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->REFR.size();
    if(dummyParentRecord != NULL)
        {
        for(unsigned int x = 0; x < dummyParentRecord->REFR.size();)
            {
            dummyParentRecord->REFR[x]->Read(curModFile->FormIDHandler);
            ResolveGrid(dummyParentRecord->REFR[x]->DATA.value.posX, dummyParentRecord->REFR[x]->DATA.value.posY, gridX, gridY);
            if(gridX == parentRecord->XCLC.value.posX && gridY == parentRecord->XCLC.value.posY)
                {
                parentRecord->REFR.push_back(dummyParentRecord->REFR[x]);
                dummyParentRecord->REFR.erase(dummyParentRecord->REFR.begin() + x);
                ++cSize;
                }
            else ++x;
            }
        }
    return cSize;
    }

unsigned int Collection::GetNumWRLDRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->WRLD.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->WRLD.Records.size();
    return 0;
    }

unsigned int Collection::GetNumDIALRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->DIAL.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->DIAL.Records.size();
    return 0;
    }

unsigned int Collection::GetNumQUSTRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->QUST.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->QUST.Records.size();
    return 0;
    }

unsigned int Collection::GetNumIDLERecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->IDLE.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->IDLE.Records.size();
    return 0;
    }

unsigned int Collection::GetNumPACKRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->PACK.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->PACK.Records.size();
    return 0;
    }

unsigned int Collection::GetNumCSTYRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->CSTY.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->CSTY.Records.size();
    return 0;
    }

unsigned int Collection::GetNumLSCRRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->LSCR.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->LSCR.Records.size();
    return 0;
    }

unsigned int Collection::GetNumLVSPRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->LVSP.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->LVSP.Records.size();
    return 0;
    }

unsigned int Collection::GetNumANIORecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->ANIO.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->ANIO.Records.size();
    return 0;
    }

unsigned int Collection::GetNumWATRRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->WATR.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->WATR.Records.size();
    return 0;
    }

unsigned int Collection::GetNumEFSHRecords(char *ModName)
    {
    unsigned int cSize = 0;
    if(ModName == NULL)
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            cSize += (unsigned int)ModFiles[p]->EFSH.Records.size();
        return cSize;
        }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return (unsigned int)ModFiles[p]->EFSH.Records.size();
    return 0;
    }
//ADD DEFINITIONS HERE

void Collection::GetGMSTRecords(char *ModName, char **RecordEIDs)
    {
    unsigned int p = 0;
    if(ModName == NULL)
        for(std::multimap<char*,std::pair<ModFile *, Record *>, sameStr>::iterator curGMST = GMST_ModFile_Record.begin();curGMST!=GMST_ModFile_Record.end();curGMST++, p++)
            RecordEIDs[p] = curGMST->first;
    else
        {
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                for(unsigned int x = 0; x < ModFiles[p]->GMST.Records.size(); x++)
                    RecordEIDs[x] = ModFiles[p]->GMST.Records[x]->EDID.value;
                return;
                }
        }
    return;
    }

void Collection::GetGLOBRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->GLOB.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->GLOB.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->GLOB.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->GLOB.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetCLASRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->CLAS.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->CLAS.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->CLAS.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->CLAS.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetFACTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->FACT.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->FACT.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->FACT.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->FACT.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetHAIRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->HAIR.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->HAIR.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->HAIR.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->HAIR.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetEYESRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->EYES.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->EYES.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->EYES.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->EYES.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetRACERecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->RACE.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->RACE.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->RACE.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->RACE.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetSOUNRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->SOUN.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->SOUN.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->SOUN.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->SOUN.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetSKILRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->SKIL.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->SKIL.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->SKIL.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->SKIL.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetMGEFRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->MGEF.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->MGEF.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->MGEF.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->MGEF.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetSCPTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->SCPT.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->SCPT.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->SCPT.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->SCPT.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetLTEXRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->LTEX.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->LTEX.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->LTEX.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->LTEX.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetENCHRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->ENCH.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->ENCH.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->ENCH.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->ENCH.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetSPELRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->SPEL.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->SPEL.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->SPEL.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->SPEL.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetBSGNRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->BSGN.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->BSGN.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->BSGN.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->BSGN.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetACTIRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->ACTI.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->ACTI.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->ACTI.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->ACTI.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetAPPARecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->APPA.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->APPA.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->APPA.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->APPA.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetARMORecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->ARMO.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->ARMO.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->ARMO.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->ARMO.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetBOOKRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->BOOK.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->BOOK.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->BOOK.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->BOOK.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetCLOTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->CLOT.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->CLOT.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->CLOT.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->CLOT.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetCONTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->CONT.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->CONT.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->CONT.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->CONT.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetDOORRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->DOOR.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->DOOR.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->DOOR.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->DOOR.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetINGRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->INGR.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->INGR.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->INGR.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->INGR.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetLIGHRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->LIGH.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->LIGH.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->LIGH.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->LIGH.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetMISCRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->MISC.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->MISC.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->MISC.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->MISC.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetSTATRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->STAT.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->STAT.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->STAT.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->STAT.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetGRASRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->GRAS.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->GRAS.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->GRAS.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->GRAS.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetTREERecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->TREE.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->TREE.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->TREE.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->TREE.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetFLORRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->FLOR.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->FLOR.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->FLOR.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->FLOR.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetFURNRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->FURN.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->FURN.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->FURN.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->FURN.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetWEAPRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->WEAP.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->WEAP.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->WEAP.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->WEAP.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetAMMORecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->AMMO.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->AMMO.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->AMMO.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->AMMO.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetNPC_Records(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->NPC_.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->NPC_.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->NPC_.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->NPC_.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetCREARecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->CREA.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->CREA.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->CREA.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->CREA.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetLVLCRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->LVLC.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->LVLC.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->LVLC.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->LVLC.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetSLGMRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->SLGM.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->SLGM.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->SLGM.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->SLGM.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetKEYMRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->KEYM.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->KEYM.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->KEYM.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->KEYM.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetALCHRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->ALCH.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->ALCH.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->ALCH.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->ALCH.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetSBSPRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->SBSP.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->SBSP.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->SBSP.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->SBSP.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetSGSTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->SGST.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->SGST.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->SGST.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->SGST.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetLVLIRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->LVLI.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->LVLI.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->LVLI.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->LVLI.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetWTHRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->WTHR.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->WTHR.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->WTHR.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->WTHR.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetCLMTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->CLMT.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->CLMT.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->CLMT.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->CLMT.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetREGNRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->REGN.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->REGN.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->REGN.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->REGN.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetCELLRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->CELL.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->CELL.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->CELL.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->CELL.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetACHRRecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    if(ModName == NULL)
        return;

    ModFile *curModFile = LookupModFile(ModName);
    CELLRecord *parentRecord = NULL;

    unsigned int numRecords = 0;

    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(parentRecord == NULL || curModFile == NULL)
        return;

    numRecords = (unsigned int)parentRecord->ACHR.size();
    for(unsigned int x = 0; x < numRecords; x++)
        RecordFIDs[x] = &parentRecord->ACHR[x]->formID;

    return;
    }

void Collection::GetACRERecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    if(ModName == NULL)
        return;

    ModFile *curModFile = LookupModFile(ModName);
    CELLRecord *parentRecord = NULL;

    unsigned int numRecords = 0;

    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(parentRecord == NULL || curModFile == NULL)
        return;

    numRecords = (unsigned int)parentRecord->ACRE.size();
    for(unsigned int x = 0; x < numRecords; x++)
        RecordFIDs[x] = &parentRecord->ACRE[x]->formID;

    return;
    }

void Collection::GetREFRRecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs)
    {
    if(ModName == NULL)
        return;

    ModFile *curModFile = LookupModFile(ModName);
    CELLRecord *parentRecord = NULL;

    unsigned int numRecords = 0;

    LookupRecord(ModName, parentFID, curModFile, parentRecord);
    if(parentRecord == NULL || curModFile == NULL)
        return;

    numRecords = (unsigned int)parentRecord->REFR.size();
    for(unsigned int x = 0; x < numRecords; x++)
        RecordFIDs[x] = &parentRecord->REFR[x]->formID;

    return;
    }

void Collection::GetWRLDRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->WRLD.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->WRLD.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->WRLD.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->WRLD.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetDIALRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->DIAL.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->DIAL.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->DIAL.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->DIAL.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetQUSTRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->QUST.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->QUST.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->QUST.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->QUST.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetIDLERecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->IDLE.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->IDLE.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->IDLE.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->IDLE.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetPACKRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->PACK.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->PACK.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->PACK.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->PACK.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetCSTYRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->CSTY.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->CSTY.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->CSTY.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->CSTY.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetLSCRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->LSCR.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->LSCR.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->LSCR.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->LSCR.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetLVSPRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->LVSP.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->LVSP.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->LVSP.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->LVSP.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetANIORecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->ANIO.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->ANIO.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->ANIO.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->ANIO.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetWATRRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->WATR.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->WATR.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->WATR.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->WATR.Records[x]->formID;
                return;
                }
    return;
    }

void Collection::GetEFSHRecords(char *ModName, unsigned int **RecordFIDs)
    {
    unsigned int p = 0, numRecords = 0;
    if(ModName == NULL)
        for(;p < ModFiles.size();p++)
            {
            numRecords = (unsigned int)ModFiles[p]->EFSH.Records.size();
            for(unsigned int x = 0; x < numRecords; x++)
                RecordFIDs[(p*numRecords)+x] = &ModFiles[p]->EFSH.Records[x]->formID;
            }
    else
        for(;p < ModFiles.size();p++)
            if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                {
                numRecords = (unsigned int)ModFiles[p]->EFSH.Records.size();
                for(unsigned int x = 0; x < numRecords; x++)
                    RecordFIDs[x] = &ModFiles[p]->EFSH.Records[x]->formID;
                return;
                }
    return;
    }
//ADD DEFINITIONS HERE
unsigned int Collection::CreateGMSTRecord(char *ModName, char *recordEDID)
    {
    ModFile *curModFile = NULL;
    GMSTRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new GMSTRecord(newRecordFID, recordEDID);
        curModFile->GMST.Records.push_back(curRecord);
        GMST_ModFile_Record.insert(std::make_pair(curRecord->EDID.value,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CopyGMSTRecord(char *ModName, char *srcRecordEDID, char *destModName)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    GMSTRecord *srcRecord = NULL;
    GMSTRecord *copyRecord = NULL;

    LookupGMSTRecord(ModName, srcRecordEDID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new GMSTRecord(srcRecord);

    destMod->GMST.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    destMod->FormIDHandler.AddMaster(srcRecord->formID);

    GMST_ModFile_Record.insert(std::make_pair(copyRecord->EDID.value, std::make_pair(destMod, copyRecord)));
    return 1;
    }

//ADD
unsigned int Collection::CreateGLOBRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    GLOBRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new GLOBRecord(newRecordFID);
        curModFile->GLOB.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateCLASRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    CLASRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new CLASRecord(newRecordFID);
        curModFile->CLAS.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateFACTRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    FACTRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new FACTRecord(newRecordFID);
        curModFile->FACT.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateHAIRRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    HAIRRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new HAIRRecord(newRecordFID);
        curModFile->HAIR.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateEYESRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    EYESRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new EYESRecord(newRecordFID);
        curModFile->EYES.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateRACERecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    RACERecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new RACERecord(newRecordFID);
        curModFile->RACE.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateSOUNRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    SOUNRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new SOUNRecord(newRecordFID);
        curModFile->SOUN.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateSKILRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    SKILRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new SKILRecord(newRecordFID);
        curModFile->SKIL.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateMGEFRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    MGEFRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new MGEFRecord(newRecordFID);
        curModFile->MGEF.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateSCPTRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    SCPTRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new SCPTRecord(newRecordFID);
        curModFile->SCPT.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateLTEXRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    LTEXRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new LTEXRecord(newRecordFID);
        curModFile->LTEX.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateENCHRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    ENCHRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new ENCHRecord(newRecordFID);
        curModFile->ENCH.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateSPELRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    SPELRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new SPELRecord(newRecordFID);
        curModFile->SPEL.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateBSGNRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    BSGNRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new BSGNRecord(newRecordFID);
        curModFile->BSGN.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateACTIRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    ACTIRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new ACTIRecord(newRecordFID);
        curModFile->ACTI.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateAPPARecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    APPARecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new APPARecord(newRecordFID);
        curModFile->APPA.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateARMORecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    ARMORecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new ARMORecord(newRecordFID);
        curModFile->ARMO.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateBOOKRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    BOOKRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new BOOKRecord(newRecordFID);
        curModFile->BOOK.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateCLOTRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    CLOTRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new CLOTRecord(newRecordFID);
        curModFile->CLOT.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateCONTRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    CONTRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new CONTRecord(newRecordFID);
        curModFile->CONT.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateDOORRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    DOORRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new DOORRecord(newRecordFID);
        curModFile->DOOR.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateINGRRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    INGRRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new INGRRecord(newRecordFID);
        curModFile->INGR.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateLIGHRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    LIGHRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new LIGHRecord(newRecordFID);
        curModFile->LIGH.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateMISCRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    MISCRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new MISCRecord(newRecordFID);
        curModFile->MISC.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateSTATRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    STATRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new STATRecord(newRecordFID);
        curModFile->STAT.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateGRASRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    GRASRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new GRASRecord(newRecordFID);
        curModFile->GRAS.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateTREERecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    TREERecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new TREERecord(newRecordFID);
        curModFile->TREE.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateFLORRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    FLORRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new FLORRecord(newRecordFID);
        curModFile->FLOR.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateFURNRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    FURNRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new FURNRecord(newRecordFID);
        curModFile->FURN.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateWEAPRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    WEAPRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new WEAPRecord(newRecordFID);
        curModFile->WEAP.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateAMMORecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    AMMORecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new AMMORecord(newRecordFID);
        curModFile->AMMO.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateNPC_Record(char *ModName)
    {
    ModFile *curModFile = NULL;
    NPC_Record *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new NPC_Record(newRecordFID);
        curModFile->NPC_.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateCREARecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    CREARecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new CREARecord(newRecordFID);
        curModFile->CREA.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateLVLCRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    LVLCRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new LVLCRecord(newRecordFID);
        curModFile->LVLC.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateSLGMRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    SLGMRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new SLGMRecord(newRecordFID);
        curModFile->SLGM.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateKEYMRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    KEYMRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new KEYMRecord(newRecordFID);
        curModFile->KEYM.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateALCHRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    ALCHRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new ALCHRecord(newRecordFID);
        curModFile->ALCH.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateSBSPRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    SBSPRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new SBSPRecord(newRecordFID);
        curModFile->SBSP.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateSGSTRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    SGSTRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new SGSTRecord(newRecordFID);
        curModFile->SGST.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateLVLIRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    LVLIRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new LVLIRecord(newRecordFID);
        curModFile->LVLI.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateWTHRRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    WTHRRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new WTHRRecord(newRecordFID);
        curModFile->WTHR.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateCLMTRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    CLMTRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new CLMTRecord(newRecordFID);
        curModFile->CLMT.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateREGNRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    REGNRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new REGNRecord(newRecordFID);
        curModFile->REGN.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateCELLRecord(char *ModName, unsigned int parentFID, bool isWorldCELL)
    {
    ModFile *curModFile = NULL;
    CELLRecord *curRecord = NULL;
    WRLDRecord *parentRecord = NULL;
    unsigned int newRecordFID = 0;
    bool hasParent = (parentFID != 0);
    if(hasParent)
        {
        LookupRecord(ModName, parentFID, curModFile, parentRecord);
        if(isWorldCELL && parentRecord->CELL != NULL)
            return 0;
        }
    else
        curModFile = LookupModFile(ModName);

    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new CELLRecord(newRecordFID);
        curRecord->IsInterior(!hasParent);
        if(hasParent)
            {
            if(isWorldCELL)
                parentRecord->CELL = curRecord;
            else
                parentRecord->CELLS.push_back(curRecord);
            }
        else
            curModFile->CELL.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateACHRRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    ACHRRecord *destRecord = NULL;
    unsigned int newRecordFID = 0;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod != NULL && destParentRecord != NULL)
        {
        newRecordFID = NextFreeExpandedFID(destMod);
        destRecord = new ACHRRecord(newRecordFID);
        destParentRecord->ACHR.push_back(destRecord);
        FID_ModFile_Record.insert(std::make_pair(&destRecord->formID,std::make_pair(destMod,destRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateACRERecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    ACRERecord *destRecord = NULL;
    unsigned int newRecordFID = 0;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod != NULL && destParentRecord != NULL)
        {
        newRecordFID = NextFreeExpandedFID(destMod);
        destRecord = new ACRERecord(newRecordFID);
        destParentRecord->ACRE.push_back(destRecord);
        FID_ModFile_Record.insert(std::make_pair(&destRecord->formID,std::make_pair(destMod,destRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateREFRRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    REFRRecord *destRecord = NULL;
    unsigned int newRecordFID = 0;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod != NULL && destParentRecord != NULL)
        {
        newRecordFID = NextFreeExpandedFID(destMod);
        destRecord = new REFRRecord(newRecordFID);
        destParentRecord->REFR.push_back(destRecord);
        FID_ModFile_Record.insert(std::make_pair(&destRecord->formID,std::make_pair(destMod,destRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreatePGRDRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    unsigned int newRecordFID = 0;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod != NULL && destParentRecord != NULL && destParentRecord->PGRD == NULL)
        {
        newRecordFID = NextFreeExpandedFID(destMod);
        destParentRecord->PGRD = new PGRDRecord(newRecordFID);
        FID_ModFile_Record.insert(std::make_pair(&destParentRecord->PGRD->formID,std::make_pair(destMod,destParentRecord->PGRD)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateWRLDRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    WRLDRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new WRLDRecord(newRecordFID);
        curModFile->WRLD.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateROADRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    WRLDRecord *destParentRecord = NULL;
    unsigned int newRecordFID = 0;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod != NULL && destParentRecord != NULL && destParentRecord->ROAD == NULL)
        {
        newRecordFID = NextFreeExpandedFID(destMod);
        destParentRecord->ROAD = new ROADRecord(newRecordFID);
        FID_ModFile_Record.insert(std::make_pair(&destParentRecord->ROAD->formID,std::make_pair(destMod,destParentRecord->ROAD)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateLANDRecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    unsigned int newRecordFID = 0;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod != NULL && destParentRecord != NULL && destParentRecord->LAND == NULL)
        {
        newRecordFID = NextFreeExpandedFID(destMod);
        destParentRecord->LAND = new LANDRecord(newRecordFID);
        FID_ModFile_Record.insert(std::make_pair(&destParentRecord->LAND->formID,std::make_pair(destMod,destParentRecord->LAND)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateDIALRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    DIALRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new DIALRecord(newRecordFID);
        curModFile->DIAL.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateINFORecord(char *ModName, unsigned int parentFID)
    {
    ModFile *destMod = NULL;
    DIALRecord *destParentRecord = NULL;
    INFORecord *destRecord = NULL;
    unsigned int newRecordFID = 0;

    LookupRecord(ModName, parentFID, destMod, destParentRecord);
    if(destMod != NULL && destParentRecord != NULL)
        {
        newRecordFID = NextFreeExpandedFID(destMod);
        destRecord = new INFORecord(newRecordFID);
        destParentRecord->INFO.push_back(destRecord);
        FID_ModFile_Record.insert(std::make_pair(&destRecord->formID,std::make_pair(destMod,destRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateQUSTRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    QUSTRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new QUSTRecord(newRecordFID);
        curModFile->QUST.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateIDLERecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    IDLERecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new IDLERecord(newRecordFID);
        curModFile->IDLE.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreatePACKRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    PACKRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new PACKRecord(newRecordFID);
        curModFile->PACK.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateCSTYRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    CSTYRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new CSTYRecord(newRecordFID);
        curModFile->CSTY.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateLSCRRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    LSCRRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new LSCRRecord(newRecordFID);
        curModFile->LSCR.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateLVSPRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    LVSPRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new LVSPRecord(newRecordFID);
        curModFile->LVSP.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateANIORecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    ANIORecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new ANIORecord(newRecordFID);
        curModFile->ANIO.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateWATRRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    WATRRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new WATRRecord(newRecordFID);
        curModFile->WATR.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

unsigned int Collection::CreateEFSHRecord(char *ModName)
    {
    ModFile *curModFile = NULL;
    EFSHRecord *curRecord = NULL;
    unsigned int newRecordFID = 0;
    curModFile = LookupModFile(ModName);
    if(curModFile != NULL)
        {
        newRecordFID = NextFreeExpandedFID(curModFile);
        curRecord = new EFSHRecord(newRecordFID);
        curModFile->EFSH.Records.push_back(curRecord);
        FID_ModFile_Record.insert(std::make_pair(&curRecord->formID,std::make_pair(curModFile,curRecord)));
        }
    return newRecordFID;
    }

        //ADD
unsigned int Collection::CopyFIDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&srcRecordFID);
    //Return if the srcRecordFID isn't found
    if(it == FID_ModFile_Record.end())
        return 0;
    return 0;
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
    return 0;
    }
unsigned int Collection::CopyGLOBRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    GLOBRecord *srcRecord = NULL;
    GLOBRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new GLOBRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->GLOB.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCLASRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CLASRecord *srcRecord = NULL;
    CLASRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new CLASRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->CLAS.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyFACTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    FACTRecord *srcRecord = NULL;
    FACTRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new FACTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->FACT.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyHAIRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    HAIRRecord *srcRecord = NULL;
    HAIRRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new HAIRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->HAIR.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyEYESRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    EYESRecord *srcRecord = NULL;
    EYESRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new EYESRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->EYES.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyRACERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    RACERecord *srcRecord = NULL;
    RACERecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new RACERecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->RACE.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySOUNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    SOUNRecord *srcRecord = NULL;
    SOUNRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new SOUNRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->SOUN.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySKILRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    SKILRecord *srcRecord = NULL;
    SKILRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new SKILRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->SKIL.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyMGEFRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    MGEFRecord *srcRecord = NULL;
    MGEFRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new MGEFRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->MGEF.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySCPTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    SCPTRecord *srcRecord = NULL;
    SCPTRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new SCPTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->SCPT.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLTEXRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    LTEXRecord *srcRecord = NULL;
    LTEXRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new LTEXRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->LTEX.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyENCHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    ENCHRecord *srcRecord = NULL;
    ENCHRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new ENCHRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->ENCH.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySPELRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    SPELRecord *srcRecord = NULL;
    SPELRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new SPELRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->SPEL.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyBSGNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    BSGNRecord *srcRecord = NULL;
    BSGNRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new BSGNRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->BSGN.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyACTIRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    ACTIRecord *srcRecord = NULL;
    ACTIRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new ACTIRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->ACTI.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyAPPARecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    APPARecord *srcRecord = NULL;
    APPARecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new APPARecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->APPA.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyARMORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    ARMORecord *srcRecord = NULL;
    ARMORecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new ARMORecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->ARMO.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyBOOKRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    BOOKRecord *srcRecord = NULL;
    BOOKRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new BOOKRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->BOOK.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCLOTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CLOTRecord *srcRecord = NULL;
    CLOTRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new CLOTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->CLOT.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCONTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CONTRecord *srcRecord = NULL;
    CONTRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new CONTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->CONT.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyDOORRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    DOORRecord *srcRecord = NULL;
    DOORRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new DOORRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->DOOR.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyINGRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    INGRRecord *srcRecord = NULL;
    INGRRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new INGRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->INGR.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLIGHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    LIGHRecord *srcRecord = NULL;
    LIGHRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new LIGHRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->LIGH.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyMISCRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    MISCRecord *srcRecord = NULL;
    MISCRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new MISCRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->MISC.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySTATRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    STATRecord *srcRecord = NULL;
    STATRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new STATRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->STAT.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyGRASRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    GRASRecord *srcRecord = NULL;
    GRASRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new GRASRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->GRAS.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyTREERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    TREERecord *srcRecord = NULL;
    TREERecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new TREERecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->TREE.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyFLORRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    FLORRecord *srcRecord = NULL;
    FLORRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new FLORRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->FLOR.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyFURNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    FURNRecord *srcRecord = NULL;
    FURNRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new FURNRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->FURN.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyWEAPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    WEAPRecord *srcRecord = NULL;
    WEAPRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new WEAPRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->WEAP.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyAMMORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    AMMORecord *srcRecord = NULL;
    AMMORecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new AMMORecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->AMMO.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyNPC_Record(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    NPC_Record *srcRecord = NULL;
    NPC_Record *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new NPC_Record(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->NPC_.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCREARecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CREARecord *srcRecord = NULL;
    CREARecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new CREARecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->CREA.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLVLCRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    LVLCRecord *srcRecord = NULL;
    LVLCRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new LVLCRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->LVLC.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySLGMRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    SLGMRecord *srcRecord = NULL;
    SLGMRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new SLGMRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->SLGM.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyKEYMRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    KEYMRecord *srcRecord = NULL;
    KEYMRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new KEYMRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->KEYM.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyALCHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    ALCHRecord *srcRecord = NULL;
    ALCHRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new ALCHRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->ALCH.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySBSPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    SBSPRecord *srcRecord = NULL;
    SBSPRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new SBSPRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->SBSP.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopySGSTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    SGSTRecord *srcRecord = NULL;
    SGSTRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new SGSTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->SGST.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLVLIRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    LVLIRecord *srcRecord = NULL;
    LVLIRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new LVLIRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->LVLI.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyWTHRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    WTHRRecord *srcRecord = NULL;
    WTHRRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new WTHRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->WTHR.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCLMTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CLMTRecord *srcRecord = NULL;
    CLMTRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new CLMTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->CLMT.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyREGNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    REGNRecord *srcRecord = NULL;
    REGNRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new REGNRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->REGN.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCELLRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride, bool isWorldCELL)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    WRLDRecord *destParentRecord = NULL;
    CELLRecord *srcRecord = NULL;
    CELLRecord *copyRecord = NULL;
    bool hasParent = (destParentFID != 0);

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    if(hasParent)
        {
        LookupRecord(destModName, destParentFID, destMod, destParentRecord);
        if(isWorldCELL && destParentRecord->CELL != NULL)
            return 0;
        }
    else
        destMod = LookupModFile(destModName);

    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        {return 0;}

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new CELLRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    copyRecord->IsInterior(!hasParent);
    if(hasParent)
        {
        if(isWorldCELL)
            destParentRecord->CELL = copyRecord;
        else
            destParentRecord->CELLS.push_back(copyRecord);
        }
    else
        destMod->CELL.Records.push_back(copyRecord);

    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);
    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyACHRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    ACHRRecord *srcRecord = NULL;
    ACHRRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || destParentRecord == NULL || srcMod == destMod)
        {return 0;}

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new ACHRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destParentRecord->ACHR.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyACRERecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    ACRERecord *srcRecord = NULL;
    ACRERecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || destParentRecord == NULL || srcMod == destMod)
        {return 0;}

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new ACRERecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destParentRecord->ACRE.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyREFRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    REFRRecord *srcRecord = NULL;
    REFRRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || destParentRecord == NULL || srcMod == destMod)
        {return 0;}

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new REFRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destParentRecord->REFR.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyPGRDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    PGRDRecord *srcRecord = NULL;
    PGRDRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(destParentRecord == NULL || destParentRecord->PGRD != NULL || srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        {return 0;}

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new PGRDRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destParentRecord->PGRD = copyRecord;

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyWRLDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    WRLDRecord *srcRecord = NULL;
    WRLDRecord *copyRecord = NULL;
    //CELLRecord *worldCellRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new WRLDRecord(srcRecord);
    //if(srcRecord->CELL != NULL)
    //    {
    //    srcRecord->CELL->Read(srcMod->FormIDHandler);
    //    copyRecord->CELL = new CELLRecord(srcRecord->CELL);
    //    }
    if(!asOverride)
        {
        copyRecord->formID = NextFreeExpandedFID(destMod);
        //if(copyRecord->CELL != NULL)
        //    copyRecord->CELL->formID = NextFreeExpandedFID(destMod);
        }

    destMod->WRLD.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyROADRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    WRLDRecord *destParentRecord = NULL;
    ROADRecord *srcRecord = NULL;
    ROADRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(destParentRecord == NULL || destParentRecord->ROAD != NULL || srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        {return 0;}

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new ROADRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destParentRecord->ROAD = copyRecord;

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLANDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CELLRecord *destParentRecord = NULL;
    LANDRecord *srcRecord = NULL;
    LANDRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(destParentRecord == NULL || destParentRecord->LAND != NULL || srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        {return 0;}

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new LANDRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destParentRecord->LAND = copyRecord;

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyDIALRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    DIALRecord *srcRecord = NULL;
    DIALRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new DIALRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->DIAL.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyINFORecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    DIALRecord *destParentRecord = NULL;
    INFORecord *srcRecord = NULL;
    INFORecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    LookupRecord(destModName, destParentFID, destMod, destParentRecord);

    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || destParentRecord == NULL || srcMod == destMod)
        {return 0;}

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new INFORecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destParentRecord->INFO.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyQUSTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    QUSTRecord *srcRecord = NULL;
    QUSTRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new QUSTRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->QUST.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyIDLERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    IDLERecord *srcRecord = NULL;
    IDLERecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new IDLERecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->IDLE.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyPACKRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    PACKRecord *srcRecord = NULL;
    PACKRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new PACKRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->PACK.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyCSTYRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    CSTYRecord *srcRecord = NULL;
    CSTYRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new CSTYRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->CSTY.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLSCRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    LSCRRecord *srcRecord = NULL;
    LSCRRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new LSCRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->LSCR.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyLVSPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    LVSPRecord *srcRecord = NULL;
    LVSPRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new LVSPRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->LVSP.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyANIORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    ANIORecord *srcRecord = NULL;
    ANIORecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new ANIORecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->ANIO.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyWATRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    WATRRecord *srcRecord = NULL;
    WATRRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new WATRRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->WATR.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }

unsigned int Collection::CopyEFSHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride)
    {
    ModFile *srcMod = NULL;
    ModFile *destMod = NULL;
    EFSHRecord *srcRecord = NULL;
    EFSHRecord *copyRecord = NULL;

    LookupRecord(ModName, srcRecordFID, srcMod, srcRecord);
    destMod = LookupModFile(destModName);

    //Throw in the towel if either the source or destination mod doesn't exist, or if they're the same
    if(srcMod == NULL || destMod == NULL || srcRecord == NULL || srcMod == destMod)
        return 0;

    //Ensure the record has been fully read
    srcRecord->Read(srcMod->FormIDHandler);

    copyRecord = new EFSHRecord(srcRecord);
    if(!asOverride)
        copyRecord->formID = NextFreeExpandedFID(destMod);

    destMod->EFSH.Records.push_back(copyRecord);

    //Add any master as necessary, and register the formID
    if(asOverride)
        destMod->FormIDHandler.AddMaster(srcRecordFID);

    FID_ModFile_Record.insert(std::make_pair(&copyRecord->formID,std::make_pair(destMod,copyRecord)));
    return copyRecord->formID;
    }
