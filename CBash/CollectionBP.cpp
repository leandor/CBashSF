# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
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
    dummyParentRecord = LookupCELLParent(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->ACHR.size();
    if(dummyParentRecord != NULL)
        {
        for(unsigned int x = 0; x < dummyParentRecord->ACHR.size();)
            {
            dummyParentRecord->ACHR[x]->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
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
    dummyParentRecord = LookupCELLParent(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->ACRE.size();
    if(dummyParentRecord != NULL)
        {
        for(unsigned int x = 0; x < dummyParentRecord->ACRE.size();)
            {
            dummyParentRecord->ACRE[x]->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
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
    dummyParentRecord = LookupCELLParent(curModFile, parentRecord);

    cSize += (unsigned int)parentRecord->REFR.size();
    if(dummyParentRecord != NULL)
        {
        for(unsigned int x = 0; x < dummyParentRecord->REFR.size();)
            {
            dummyParentRecord->REFR[x]->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
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
