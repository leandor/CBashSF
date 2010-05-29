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

bool sortLoad(const ModFile *lhs, const ModFile *rhs)
    {
    struct stat lbuf, rbuf;
    if(stat(lhs->FileName, &lbuf) < 0)
        return false;
    if(stat(rhs->FileName, &rbuf) < 0)
        return true;
    return lbuf.st_mtime < rbuf.st_mtime;
    }

int Collection::NewMod(const char *ModName)
    {
    return -1;
    }

bool Collection::IsModAdded(const char *ModName)
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return true;
    return false;
    }

int Collection::AddMod(const char *ModName, bool CreateIfNotExist)
    {
    _chdir(ModsDir);
    //Mods may not be added after collection is loaded.
    //It would potentially mess up python accessors if it added anywhere other than the very end
    if(isLoaded)
        return -1;
    //Prevent loading mods more than once
    if(IsModAdded(ModName))
        return 0;
    if(CreateIfNotExist || FileExists(ModName))
        {
        char *FileName = new char[strlen(ModName)+1];
        strcpy_s(FileName, strlen(ModName)+1, ModName);
        ModFiles.push_back(new ModFile(FileName, CreateIfNotExist));
        //LoadOrder.push_back(FileName);
        return 0;
        }
    return -1;
    }

int Collection::SafeSaveMod(char *ModName, bool CloseMod)
    {
    _chdir(ModsDir);
    FileBuffer buffer(BUFFERSIZE);
    //Saves to a temp file, then if successful, renames any existing files, and then renames temp file to ModName
    ModFile *curModFile = NULL;
    errno_t err;
    char tName[L_tmpnam_s];
    time_t ltime;
    struct tm currentTime;
    struct stat oTimes;
    struct _utimbuf originalTimes;

    char *backupName = NULL;
    unsigned int bakAttempts = 0, bakSize = 0;

    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            curModFile = ModFiles[p];

    //Only save to files that have already been added.
    if(curModFile == NULL)
        return -1;
    err = tmpnam_s(tName, L_tmpnam_s);
    if (err)
        {
        printf("Error occurred creating unique filename.\n");
        return -1;
        }

    tName[0] = 'x';

    if(buffer.open_write(tName) == -1)
        return -1;

    //Return all FormIDs in the mod to a writable state
    CollapseFormIDs(ModName);
    //Save the mod to temp file, using FileBuffer to write in chunks
    curModFile->Save(buffer, CloseMod);

    buffer.close();

    //Return all FormIDs in the mod to an editable state
    ExpandFormIDs(ModName);

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

    if(FileExists(ModName))
        {
        stat(ModName, &oTimes);
        originalTimes.actime = oTimes.st_atime;
        originalTimes.modtime = oTimes.st_mtime;

        bakSize = (unsigned int)strlen(ModName) + (unsigned int)strlen(".bak.XXXX_XX_XX_XX_XX_XX") + 1;
        backupName = new char[bakSize];
        strcpy_s(backupName, bakSize, ModName);
        strftime(backupName + strlen(ModName), bakSize, ".bak.%Y_%m_%d_%H_%M_%S", &currentTime );

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
            strftime(backupName + strlen(ModName), bakSize, ".bak.%Y_%m_%d_%H_%M_%S", &currentTime);
            };
        err = rename(ModName, backupName);
        if(err != 0)
            printf("Error renaming \"%s\" to \"%s\"\n", ModName, backupName);
        delete []backupName;
        }

    //Rename temp file to the original ModName
    //If it fails, try to save it to a datestamped .new extension and inform the failure
    err = rename(tName, ModName);
    if(err != 0)
        {
        bakSize = (unsigned int)strlen(ModName) + (unsigned int)strlen(".new.XXXX_XX_XX_XX_XX_XX") + 1;
        backupName = new char[bakSize];

        strcpy_s(backupName, bakSize, ModName);
        strftime(backupName+strlen(ModName), bakSize, ".new.%Y_%m_%d_%H_%M_%S", &currentTime );

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
            strftime(backupName + strlen(ModName), bakSize, ".new.%Y_%m_%d_%H_%M_%S", &currentTime);
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
            printf("Error renaming \"%s\" to \"%s\"\n", tName, ModName);
            printf("Renamed \"%s\" to \"%s\"\n", tName, backupName);
            _utime(backupName, &originalTimes);
            delete []backupName;
            return 0;
            }
        }
    else
        _utime(ModName, &originalTimes);
    return 0;
    }

int Collection::SafeSaveAllChangedMods()
    {
    _chdir(ModsDir);
    return -1;
    }

void Collection::IndexRecords(ModFile *curModFile)
    {
    //Associates record ids at the collection level, allowing for conflicts to be determined.
    //ADD DEFINITIONS HERE
    for(std::vector<GMSTRecord *>::iterator curGMST = curModFile->GMST.Records.begin();curGMST != curModFile->GMST.Records.end();curGMST++)
        GMST_ModFile_Record.insert(std::make_pair((*curGMST)->EDID.value,std::make_pair(curModFile,*curGMST)));
    for(std::vector<GMSTRecord *>::iterator curGMST = curModFile->GMST.Records.begin();curGMST != curModFile->GMST.Records.end();curGMST++)
        FID_ModFile_Record.insert(std::make_pair(&(*curGMST)->formID,std::make_pair(curModFile,*curGMST)));
    for(std::vector<GLOBRecord *>::iterator curGLOB = curModFile->GLOB.Records.begin();curGLOB != curModFile->GLOB.Records.end();curGLOB++)
        FID_ModFile_Record.insert(std::make_pair(&(*curGLOB)->formID,std::make_pair(curModFile,*curGLOB)));
    for(std::vector<CLASRecord *>::iterator curCLAS = curModFile->CLAS.Records.begin();curCLAS != curModFile->CLAS.Records.end();curCLAS++)
        FID_ModFile_Record.insert(std::make_pair(&(*curCLAS)->formID,std::make_pair(curModFile,*curCLAS)));
    for(std::vector<FACTRecord *>::iterator curFACT = curModFile->FACT.Records.begin();curFACT != curModFile->FACT.Records.end();curFACT++)
        FID_ModFile_Record.insert(std::make_pair(&(*curFACT)->formID,std::make_pair(curModFile,*curFACT)));
    for(std::vector<HAIRRecord *>::iterator curHAIR = curModFile->HAIR.Records.begin();curHAIR != curModFile->HAIR.Records.end();curHAIR++)
        FID_ModFile_Record.insert(std::make_pair(&(*curHAIR)->formID,std::make_pair(curModFile,*curHAIR)));
    for(std::vector<EYESRecord *>::iterator curEYES = curModFile->EYES.Records.begin();curEYES != curModFile->EYES.Records.end();curEYES++)
        FID_ModFile_Record.insert(std::make_pair(&(*curEYES)->formID,std::make_pair(curModFile,*curEYES)));
    for(std::vector<RACERecord *>::iterator curRACE = curModFile->RACE.Records.begin();curRACE != curModFile->RACE.Records.end();curRACE++)
        FID_ModFile_Record.insert(std::make_pair(&(*curRACE)->formID,std::make_pair(curModFile,*curRACE)));
    for(std::vector<SOUNRecord *>::iterator curSOUN = curModFile->SOUN.Records.begin();curSOUN != curModFile->SOUN.Records.end();curSOUN++)
        FID_ModFile_Record.insert(std::make_pair(&(*curSOUN)->formID,std::make_pair(curModFile,*curSOUN)));
    for(std::vector<SKILRecord *>::iterator curSKIL = curModFile->SKIL.Records.begin();curSKIL != curModFile->SKIL.Records.end();curSKIL++)
        FID_ModFile_Record.insert(std::make_pair(&(*curSKIL)->formID,std::make_pair(curModFile,*curSKIL)));
    for(std::vector<MGEFRecord *>::iterator curMGEF = curModFile->MGEF.Records.begin();curMGEF != curModFile->MGEF.Records.end();curMGEF++)
        FID_ModFile_Record.insert(std::make_pair(&(*curMGEF)->formID,std::make_pair(curModFile,*curMGEF)));
    for(std::vector<SCPTRecord *>::iterator curSCPT = curModFile->SCPT.Records.begin();curSCPT != curModFile->SCPT.Records.end();curSCPT++)
        FID_ModFile_Record.insert(std::make_pair(&(*curSCPT)->formID,std::make_pair(curModFile,*curSCPT)));
    for(std::vector<LTEXRecord *>::iterator curLTEX = curModFile->LTEX.Records.begin();curLTEX != curModFile->LTEX.Records.end();curLTEX++)
        FID_ModFile_Record.insert(std::make_pair(&(*curLTEX)->formID,std::make_pair(curModFile,*curLTEX)));
    for(std::vector<ENCHRecord *>::iterator curENCH = curModFile->ENCH.Records.begin();curENCH != curModFile->ENCH.Records.end();curENCH++)
        FID_ModFile_Record.insert(std::make_pair(&(*curENCH)->formID,std::make_pair(curModFile,*curENCH)));
    for(std::vector<SPELRecord *>::iterator curSPEL = curModFile->SPEL.Records.begin();curSPEL != curModFile->SPEL.Records.end();curSPEL++)
        FID_ModFile_Record.insert(std::make_pair(&(*curSPEL)->formID,std::make_pair(curModFile,*curSPEL)));
    for(std::vector<BSGNRecord *>::iterator curBSGN = curModFile->BSGN.Records.begin();curBSGN != curModFile->BSGN.Records.end();curBSGN++)
        FID_ModFile_Record.insert(std::make_pair(&(*curBSGN)->formID,std::make_pair(curModFile,*curBSGN)));
    for(std::vector<ACTIRecord *>::iterator curACTI = curModFile->ACTI.Records.begin();curACTI != curModFile->ACTI.Records.end();curACTI++)
        FID_ModFile_Record.insert(std::make_pair(&(*curACTI)->formID,std::make_pair(curModFile,*curACTI)));
    for(std::vector<APPARecord *>::iterator curAPPA = curModFile->APPA.Records.begin();curAPPA != curModFile->APPA.Records.end();curAPPA++)
        FID_ModFile_Record.insert(std::make_pair(&(*curAPPA)->formID,std::make_pair(curModFile,*curAPPA)));
    for(std::vector<ARMORecord *>::iterator curARMO = curModFile->ARMO.Records.begin();curARMO != curModFile->ARMO.Records.end();curARMO++)
        FID_ModFile_Record.insert(std::make_pair(&(*curARMO)->formID,std::make_pair(curModFile,*curARMO)));
    for(std::vector<BOOKRecord *>::iterator curBOOK = curModFile->BOOK.Records.begin();curBOOK != curModFile->BOOK.Records.end();curBOOK++)
        FID_ModFile_Record.insert(std::make_pair(&(*curBOOK)->formID,std::make_pair(curModFile,*curBOOK)));
    for(std::vector<CLOTRecord *>::iterator curCLOT = curModFile->CLOT.Records.begin();curCLOT != curModFile->CLOT.Records.end();curCLOT++)
        FID_ModFile_Record.insert(std::make_pair(&(*curCLOT)->formID,std::make_pair(curModFile,*curCLOT)));
    for(std::vector<CONTRecord *>::iterator curCONT = curModFile->CONT.Records.begin();curCONT != curModFile->CONT.Records.end();curCONT++)
        FID_ModFile_Record.insert(std::make_pair(&(*curCONT)->formID,std::make_pair(curModFile,*curCONT)));
    for(std::vector<DOORRecord *>::iterator curDOOR = curModFile->DOOR.Records.begin();curDOOR != curModFile->DOOR.Records.end();curDOOR++)
        FID_ModFile_Record.insert(std::make_pair(&(*curDOOR)->formID,std::make_pair(curModFile,*curDOOR)));
    for(std::vector<INGRRecord *>::iterator curINGR = curModFile->INGR.Records.begin();curINGR != curModFile->INGR.Records.end();curINGR++)
        FID_ModFile_Record.insert(std::make_pair(&(*curINGR)->formID,std::make_pair(curModFile,*curINGR)));
    for(std::vector<LIGHRecord *>::iterator curLIGH = curModFile->LIGH.Records.begin();curLIGH != curModFile->LIGH.Records.end();curLIGH++)
        FID_ModFile_Record.insert(std::make_pair(&(*curLIGH)->formID,std::make_pair(curModFile,*curLIGH)));
    for(std::vector<MISCRecord *>::iterator curMISC = curModFile->MISC.Records.begin();curMISC != curModFile->MISC.Records.end();curMISC++)
        FID_ModFile_Record.insert(std::make_pair(&(*curMISC)->formID,std::make_pair(curModFile,*curMISC)));
    for(std::vector<STATRecord *>::iterator curSTAT = curModFile->STAT.Records.begin();curSTAT != curModFile->STAT.Records.end();curSTAT++)
        FID_ModFile_Record.insert(std::make_pair(&(*curSTAT)->formID,std::make_pair(curModFile,*curSTAT)));
    for(std::vector<GRASRecord *>::iterator curGRAS = curModFile->GRAS.Records.begin();curGRAS != curModFile->GRAS.Records.end();curGRAS++)
        FID_ModFile_Record.insert(std::make_pair(&(*curGRAS)->formID,std::make_pair(curModFile,*curGRAS)));
    for(std::vector<TREERecord *>::iterator curTREE = curModFile->TREE.Records.begin();curTREE != curModFile->TREE.Records.end();curTREE++)
        FID_ModFile_Record.insert(std::make_pair(&(*curTREE)->formID,std::make_pair(curModFile,*curTREE)));
    for(std::vector<FLORRecord *>::iterator curFLOR = curModFile->FLOR.Records.begin();curFLOR != curModFile->FLOR.Records.end();curFLOR++)
        FID_ModFile_Record.insert(std::make_pair(&(*curFLOR)->formID,std::make_pair(curModFile,*curFLOR)));
    for(std::vector<FURNRecord *>::iterator curFURN = curModFile->FURN.Records.begin();curFURN != curModFile->FURN.Records.end();curFURN++)
        FID_ModFile_Record.insert(std::make_pair(&(*curFURN)->formID,std::make_pair(curModFile,*curFURN)));
    for(std::vector<WEAPRecord *>::iterator curWEAP = curModFile->WEAP.Records.begin();curWEAP != curModFile->WEAP.Records.end();curWEAP++)
        FID_ModFile_Record.insert(std::make_pair(&(*curWEAP)->formID,std::make_pair(curModFile,*curWEAP)));
    for(std::vector<AMMORecord *>::iterator curAMMO = curModFile->AMMO.Records.begin();curAMMO != curModFile->AMMO.Records.end();curAMMO++)
        FID_ModFile_Record.insert(std::make_pair(&(*curAMMO)->formID,std::make_pair(curModFile,*curAMMO)));
    for(std::vector<NPC_Record *>::iterator curNPC_ = curModFile->NPC_.Records.begin();curNPC_ != curModFile->NPC_.Records.end();curNPC_++)
        FID_ModFile_Record.insert(std::make_pair(&(*curNPC_)->formID,std::make_pair(curModFile,*curNPC_)));
    for(std::vector<CREARecord *>::iterator curCREA = curModFile->CREA.Records.begin();curCREA != curModFile->CREA.Records.end();curCREA++)
        FID_ModFile_Record.insert(std::make_pair(&(*curCREA)->formID,std::make_pair(curModFile,*curCREA)));
    for(std::vector<LVLCRecord *>::iterator curLVLC = curModFile->LVLC.Records.begin();curLVLC != curModFile->LVLC.Records.end();curLVLC++)
        FID_ModFile_Record.insert(std::make_pair(&(*curLVLC)->formID,std::make_pair(curModFile,*curLVLC)));
    for(std::vector<SLGMRecord *>::iterator curSLGM = curModFile->SLGM.Records.begin();curSLGM != curModFile->SLGM.Records.end();curSLGM++)
        FID_ModFile_Record.insert(std::make_pair(&(*curSLGM)->formID,std::make_pair(curModFile,*curSLGM)));
    for(std::vector<KEYMRecord *>::iterator curKEYM = curModFile->KEYM.Records.begin();curKEYM != curModFile->KEYM.Records.end();curKEYM++)
        FID_ModFile_Record.insert(std::make_pair(&(*curKEYM)->formID,std::make_pair(curModFile,*curKEYM)));
    for(std::vector<ALCHRecord *>::iterator curALCH = curModFile->ALCH.Records.begin();curALCH != curModFile->ALCH.Records.end();curALCH++)
        FID_ModFile_Record.insert(std::make_pair(&(*curALCH)->formID,std::make_pair(curModFile,*curALCH)));
    for(std::vector<SBSPRecord *>::iterator curSBSP = curModFile->SBSP.Records.begin();curSBSP != curModFile->SBSP.Records.end();curSBSP++)
        FID_ModFile_Record.insert(std::make_pair(&(*curSBSP)->formID,std::make_pair(curModFile,*curSBSP)));
    for(std::vector<SGSTRecord *>::iterator curSGST = curModFile->SGST.Records.begin();curSGST != curModFile->SGST.Records.end();curSGST++)
        FID_ModFile_Record.insert(std::make_pair(&(*curSGST)->formID,std::make_pair(curModFile,*curSGST)));
    for(std::vector<LVLIRecord *>::iterator curLVLI = curModFile->LVLI.Records.begin();curLVLI != curModFile->LVLI.Records.end();curLVLI++)
        FID_ModFile_Record.insert(std::make_pair(&(*curLVLI)->formID,std::make_pair(curModFile,*curLVLI)));
    for(std::vector<WTHRRecord *>::iterator curWTHR = curModFile->WTHR.Records.begin();curWTHR != curModFile->WTHR.Records.end();curWTHR++)
        FID_ModFile_Record.insert(std::make_pair(&(*curWTHR)->formID,std::make_pair(curModFile,*curWTHR)));
    for(std::vector<CLMTRecord *>::iterator curCLMT = curModFile->CLMT.Records.begin();curCLMT != curModFile->CLMT.Records.end();curCLMT++)
        FID_ModFile_Record.insert(std::make_pair(&(*curCLMT)->formID,std::make_pair(curModFile,*curCLMT)));
    for(std::vector<REGNRecord *>::iterator curREGN = curModFile->REGN.Records.begin();curREGN != curModFile->REGN.Records.end();curREGN++)
        FID_ModFile_Record.insert(std::make_pair(&(*curREGN)->formID,std::make_pair(curModFile,*curREGN)));

    for(std::vector<CELLRecord *>::iterator curCELL = curModFile->CELL.Records.begin();curCELL != curModFile->CELL.Records.end();curCELL++)
        {
        FID_ModFile_Record.insert(std::make_pair(&(*curCELL)->formID,std::make_pair(curModFile,*curCELL)));
        for(std::vector<ACHRRecord *>::iterator curACHR = (*curCELL)->ACHR.begin();curACHR != (*curCELL)->ACHR.end();curACHR++)
            FID_ModFile_Record.insert(std::make_pair(&(*curACHR)->formID,std::make_pair(curModFile,*curACHR)));

        for(std::vector<ACRERecord *>::iterator curACRE = (*curCELL)->ACRE.begin();curACRE != (*curCELL)->ACRE.end();curACRE++)
            FID_ModFile_Record.insert(std::make_pair(&(*curACRE)->formID,std::make_pair(curModFile,*curACRE)));

        for(std::vector<REFRRecord *>::iterator curREFR = (*curCELL)->REFR.begin();curREFR != (*curCELL)->REFR.end();curREFR++)
            FID_ModFile_Record.insert(std::make_pair(&(*curREFR)->formID,std::make_pair(curModFile,*curREFR)));

        if((*curCELL)->PGRD != NULL)
            FID_ModFile_Record.insert(std::make_pair(&(*curCELL)->PGRD->formID,std::make_pair(curModFile,(*curCELL)->PGRD)));
        }

    for(std::vector<WRLDRecord *>::iterator curWRLD = curModFile->WRLD.Records.begin();curWRLD != curModFile->WRLD.Records.end();curWRLD++)
        {
        FID_ModFile_Record.insert(std::make_pair(&(*curWRLD)->formID,std::make_pair(curModFile,*curWRLD)));
        if((*curWRLD)->CELL != NULL)
            {
            FID_ModFile_Record.insert(std::make_pair(&(*curWRLD)->CELL->formID,std::make_pair(curModFile,(*curWRLD)->CELL)));
            for(std::vector<ACHRRecord *>::iterator curACHR = (*curWRLD)->CELL->ACHR.begin();curACHR != (*curWRLD)->CELL->ACHR.end();curACHR++)
                FID_ModFile_Record.insert(std::make_pair(&(*curACHR)->formID,std::make_pair(curModFile,*curACHR)));

            for(std::vector<ACRERecord *>::iterator curACRE = (*curWRLD)->CELL->ACRE.begin();curACRE != (*curWRLD)->CELL->ACRE.end();curACRE++)
                FID_ModFile_Record.insert(std::make_pair(&(*curACRE)->formID,std::make_pair(curModFile,*curACRE)));

            for(std::vector<REFRRecord *>::iterator curREFR = (*curWRLD)->CELL->REFR.begin();curREFR != (*curWRLD)->CELL->REFR.end();curREFR++)
                FID_ModFile_Record.insert(std::make_pair(&(*curREFR)->formID,std::make_pair(curModFile,*curREFR)));

            if((*curWRLD)->CELL->PGRD != NULL)
                FID_ModFile_Record.insert(std::make_pair(&(*curWRLD)->CELL->PGRD->formID,std::make_pair(curModFile,(*curWRLD)->CELL->PGRD)));
            if((*curWRLD)->CELL->LAND != NULL)
                FID_ModFile_Record.insert(std::make_pair(&(*curWRLD)->CELL->LAND->formID,std::make_pair(curModFile,(*curWRLD)->CELL->LAND)));
            }

        if((*curWRLD)->ROAD != NULL)
            FID_ModFile_Record.insert(std::make_pair(&(*curWRLD)->ROAD->formID,std::make_pair(curModFile,(*curWRLD)->ROAD)));


        for(std::vector<CELLRecord *>::iterator curCELL = (*curWRLD)->CELLS.begin();curCELL != (*curWRLD)->CELLS.end();curCELL++)
            {
            FID_ModFile_Record.insert(std::make_pair(&(*curCELL)->formID,std::make_pair(curModFile,*curCELL)));
            for(std::vector<ACHRRecord *>::iterator curACHR = (*curCELL)->ACHR.begin();curACHR != (*curCELL)->ACHR.end();curACHR++)
                FID_ModFile_Record.insert(std::make_pair(&(*curACHR)->formID,std::make_pair(curModFile,*curACHR)));

            for(std::vector<ACRERecord *>::iterator curACRE = (*curCELL)->ACRE.begin();curACRE != (*curCELL)->ACRE.end();curACRE++)
                FID_ModFile_Record.insert(std::make_pair(&(*curACRE)->formID,std::make_pair(curModFile,*curACRE)));

            for(std::vector<REFRRecord *>::iterator curREFR = (*curCELL)->REFR.begin();curREFR != (*curCELL)->REFR.end();curREFR++)
                FID_ModFile_Record.insert(std::make_pair(&(*curREFR)->formID,std::make_pair(curModFile,*curREFR)));

            if((*curCELL)->PGRD != NULL)
                FID_ModFile_Record.insert(std::make_pair(&(*curCELL)->PGRD->formID,std::make_pair(curModFile,(*curCELL)->PGRD)));
            if((*curCELL)->LAND != NULL)
                FID_ModFile_Record.insert(std::make_pair(&(*curCELL)->LAND->formID,std::make_pair(curModFile,(*curCELL)->LAND)));
            }
        }

    for(std::vector<DIALRecord *>::iterator curDIAL = curModFile->DIAL.Records.begin();curDIAL != curModFile->DIAL.Records.end();curDIAL++)
        {
        FID_ModFile_Record.insert(std::make_pair(&(*curDIAL)->formID,std::make_pair(curModFile,*curDIAL)));
        for(std::vector<INFORecord *>::iterator curINFO = (*curDIAL)->INFO.begin();curINFO != (*curDIAL)->INFO.end();curINFO++)
            FID_ModFile_Record.insert(std::make_pair(&(*curINFO)->formID,std::make_pair(curModFile,*curINFO)));
        }

    for(std::vector<QUSTRecord *>::iterator curQUST = curModFile->QUST.Records.begin();curQUST != curModFile->QUST.Records.end();curQUST++)
        FID_ModFile_Record.insert(std::make_pair(&(*curQUST)->formID,std::make_pair(curModFile,*curQUST)));
    for(std::vector<IDLERecord *>::iterator curIDLE = curModFile->IDLE.Records.begin();curIDLE != curModFile->IDLE.Records.end();curIDLE++)
        FID_ModFile_Record.insert(std::make_pair(&(*curIDLE)->formID,std::make_pair(curModFile,*curIDLE)));
    for(std::vector<PACKRecord *>::iterator curPACK = curModFile->PACK.Records.begin();curPACK != curModFile->PACK.Records.end();curPACK++)
        FID_ModFile_Record.insert(std::make_pair(&(*curPACK)->formID,std::make_pair(curModFile,*curPACK)));
    for(std::vector<CSTYRecord *>::iterator curCSTY = curModFile->CSTY.Records.begin();curCSTY != curModFile->CSTY.Records.end();curCSTY++)
        FID_ModFile_Record.insert(std::make_pair(&(*curCSTY)->formID,std::make_pair(curModFile,*curCSTY)));
    for(std::vector<LSCRRecord *>::iterator curLSCR = curModFile->LSCR.Records.begin();curLSCR != curModFile->LSCR.Records.end();curLSCR++)
        FID_ModFile_Record.insert(std::make_pair(&(*curLSCR)->formID,std::make_pair(curModFile,*curLSCR)));
    for(std::vector<LVSPRecord *>::iterator curLVSP = curModFile->LVSP.Records.begin();curLVSP != curModFile->LVSP.Records.end();curLVSP++)
        FID_ModFile_Record.insert(std::make_pair(&(*curLVSP)->formID,std::make_pair(curModFile,*curLVSP)));
    for(std::vector<ANIORecord *>::iterator curANIO = curModFile->ANIO.Records.begin();curANIO != curModFile->ANIO.Records.end();curANIO++)
        FID_ModFile_Record.insert(std::make_pair(&(*curANIO)->formID,std::make_pair(curModFile,*curANIO)));
    for(std::vector<WATRRecord *>::iterator curWATR = curModFile->WATR.Records.begin();curWATR != curModFile->WATR.Records.end();curWATR++)
        FID_ModFile_Record.insert(std::make_pair(&(*curWATR)->formID,std::make_pair(curModFile,*curWATR)));
    for(std::vector<EFSHRecord *>::iterator curEFSH = curModFile->EFSH.Records.begin();curEFSH != curModFile->EFSH.Records.end();curEFSH++)
        FID_ModFile_Record.insert(std::make_pair(&(*curEFSH)->formID,std::make_pair(curModFile,*curEFSH)));
    }

int Collection::Load(const bool &LoadMasters, const bool &FullLoad)
    {
    ModFile *curModFile = NULL;
    if(isLoaded)
        return 0;
    try
        {
        _chdir(ModsDir);
        boost::threadpool::pool ReadThreads(NUMTHREADS);
        std::sort(ModFiles.begin(), ModFiles.end(), sortLoad);
        LoadOrder.resize(ModFiles.size());
        for(unsigned char p = 0; p < (unsigned char)ModFiles.size(); ++p)
            LoadOrder[p] = ModFiles[p]->FileName;
        //LoadOrder.sort(sortLoad);
        for(unsigned char p = 0; p < (unsigned char)ModFiles.size(); ++p)
            {
            curModFile = ModFiles[p];
            //Loads GRUP and Record Headers.  Fully loads GMST records.
            curModFile->LoadTES4();
            curModFile->FormIDHandler.SetLoadOrder(LoadOrder);
            curModFile->FormIDHandler.UpdateFormIDLookup(p);
            //curModFile->Load(true);
            curModFile->Load(ReadThreads, FullLoad);
            IndexRecords(curModFile);
            }
        isLoaded = true;
        }
    catch(...)
        {
        printf("Failed Load?\n");
        isLoaded = false;
        throw;
        return -1;
        }
    return 0;
    }

unsigned int Collection::NextFreeExpandedFID(ModFile *curModFile)
    {
    unsigned int curFormID = curModFile->FormIDHandler.NextExpandedFID();
    if(FID_ModFile_Record.find(&curFormID) == FID_ModFile_Record.end())
        return curFormID;
    for(unsigned int x = 0;x < 0x00FFFFFF; ++x)
        {
        //Wrap around and recycle any freed ids.
        curFormID = curModFile->FormIDHandler.NextExpandedFID();
        if(FID_ModFile_Record.find(&curFormID) == FID_ModFile_Record.end())
            return curFormID;
        }
    //All formIDs are in use. Unlikely to ever occur.
    return 0;
    }

void Collection::CollapseFormIDs(char *ModName)
    {
    for(unsigned int p = 0;p < ModFiles.size(); p++)
        {
        if(ModName == NULL || _stricmp(ModFiles[p]->FileName, ModName) == 0)
            {
            ModFiles[p]->CollapseFormIDs();
            if(ModName != NULL)
                break;
            }
        }
    }

void Collection::ExpandFormIDs(char *ModName)
    {
    for(unsigned int p = 0;p < ModFiles.size(); p++)
        {
        if(ModName == NULL || _stricmp(ModFiles[p]->FileName, ModName) == 0)
            {
            ModFiles[p]->ExpandFormIDs();
            if(ModName != NULL)
                break;
            }
        }
    }

void Collection::ReindexFormIDs()
    {
    CollapseFormIDs();
    std::sort(ModFiles.begin(), ModFiles.end(), sortLoad);
    //LoadOrder.sort(sortLoad);
    //LoadOrder.unique(sameFile);
    ExpandFormIDs();
    }

int Collection::LoadRecord(char *ModName, unsigned int recordFID)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;

    LookupRecord(ModName, recordFID, curModFile, curRecord);

    if(curModFile == NULL || curRecord == NULL)
        return -1;

    curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
    return 0;
    }

int Collection::UnloadRecord(char *ModName, unsigned int recordFID)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;

    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;

    curRecord->Unload();
    return 0;
    }

int Collection::DeleteRecord(char *ModName, unsigned int recordFID)
    {
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curRecord = it->second.second;
            delete curRecord;
            FID_ModFile_Record.erase(it);
            return 0;
            }
        return -1;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curRecord = it->second.second;
            delete curRecord;
            FID_ModFile_Record.erase(it);
            return 0;
            }
    return -1;
    }

int Collection::Close()
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        ModFiles[p]->Close();
    return -1;
    }

int Collection::LookupGMSTRecord(char *ModName, char *recordEDID, ModFile *&curModFile, GMSTRecord *&curRecord)
    {
    std::multimap<char *, std::pair<ModFile *, Record *>, sameStr>::iterator it;

    if(recordEDID == NULL)
        {curModFile = NULL; curRecord = NULL; return 0;}

    it = GMST_ModFile_Record.find(recordEDID);
    if(it == GMST_ModFile_Record.end())
        {curModFile = NULL; curRecord = NULL; return 0;}

    if(ModName == NULL)
        curModFile = it->second.first;
    else
        curModFile = LookupModFile(ModName);
        //{
        //unsigned int count = (unsigned int)GMST_ModFile_Record.count(recordEDID);
        //for(unsigned int x = 0; x < count;++it, ++x)
        //    if(_stricmp(it->second.first->FileName, ModName) == 0 )
        //        {
        //        curModFile = it->second.first;
        //        break;
        //        }
        //}
    if(curModFile == NULL)
        {curRecord = NULL; return 0;}
    curRecord = (GMSTRecord *)it->second.second;
    return 1;
    }

CELLRecord *Collection::LookupCELLParent(ModFile *&curModFile, CELLRecord *&curCELL)
    {
    if(curCELL->IsInterior())
        return NULL;
    static CELLRecord *lastCELLRecord_1 = curModFile->WRLD.Records[0]->CELLS[0];
    static CELLRecord *lastCELLRecord_2 = curModFile->WRLD.Records[0]->CELLS[0];
    static CELLRecord *lastRetValue_1 = NULL;
    static CELLRecord *lastRetValue_2 = NULL;

    if(lastCELLRecord_1 == curCELL)
        return lastRetValue_1;
    if(lastCELLRecord_2 == curCELL)
        {
        std::swap(lastCELLRecord_1, lastCELLRecord_2);
        std::swap(lastRetValue_1, lastRetValue_2);
        return lastRetValue_1;
        }

    WRLDRecord *curWorldRecord = NULL;
    for(unsigned int x = 0; x < curModFile->WRLD.Records.size(); ++x)
        {
        curWorldRecord = curModFile->WRLD.Records[x];
        for(unsigned int p = 0; p < curWorldRecord->CELLS.size(); ++p)
            if(curWorldRecord->CELLS[p] == curCELL)
                {
                lastCELLRecord_2 = lastCELLRecord_1;
                lastCELLRecord_1 = curWorldRecord->CELLS[p];
                lastRetValue_2 = lastRetValue_1;
                lastRetValue_1 = curWorldRecord->CELL;
                return lastRetValue_1;
                }
        }
    return NULL;
    }

void Collection::ResolveGrid(const float &posX, const float &posY, int &gridX, int &gridY)
    {
    gridX = (int)floor(posX / 4096.0);
    gridY = (int)floor(posY / 4096.0);
    return;
    }

void Collection::GetMods(char **ModNames)
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        ModNames[p] = ModFiles[p]->FileName;
    return;
    }

char * Collection::GetModName(const unsigned int iIndex)
    {
    return ModFiles[iIndex]->FileName;
    }

int Collection::GetModIndex(const char *ModName)
    {
    if(ModName == NULL)
        return -1;
    static unsigned int lastModIndex_1 = 0;
    static unsigned int lastModIndex_2 = 0;
    if(_stricmp(ModName, ModFiles[lastModIndex_1]->FileName) == 0)
        return lastModIndex_1;

    if(_stricmp(ModName, ModFiles[lastModIndex_2]->FileName) == 0)
        {
        std::swap(lastModIndex_1, lastModIndex_2);
        return lastModIndex_1;
        }

    for(unsigned int x = 0; x < ModFiles.size();x++)
        if(_stricmp(ModName, ModFiles[x]->FileName) == 0)
            {
            lastModIndex_2 = lastModIndex_1;
            lastModIndex_1 = x;
            return lastModIndex_1;
            }
    return -1;
    }

unsigned int Collection::GetNumMods()
    {
    return (unsigned int)ModFiles.size();
    }

ModFile *Collection::LookupModFile(char *ModName)
    {
    //Caching the last results causes sporadic crashing...fix later
    //static ModFile *lastModFile_1 = ModFiles[0];
    //static ModFile *lastModFile_2 = ModFiles[0];
    //if(_stricmp(lastModFile_1->FileName, ModName) == 0)
    //    return lastModFile_1;
    //if(_stricmp(lastModFile_2->FileName, ModName) == 0)
    //    {
    //    std::swap(lastModFile_1, lastModFile_2);
    //    return lastModFile_1;
    //    }
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            {
            //lastModFile_2 = lastModFile_1;
            //lastModFile_1 = ModFiles[p];
            //return lastModFile_1;
            return ModFiles[p];
            }
    return NULL;
    }

int Collection::GetChangedMods()
    {
    return -1;
    }

int Collection::GetTES4FieldType(char *ModName, const unsigned int Field)
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return ModFiles[p]->TES4.GetFieldType(Field);
    return -1;
    }

int Collection::GetGMSTFieldType(char *ModName, char *recordEDID, const unsigned int Field)
    {
    std::multimap<char*,std::pair<ModFile *, Record *>, sameStr>::iterator it;
    it = GMST_ModFile_Record.find(recordEDID);
    if(ModName == NULL)
        {
        if(it != GMST_ModFile_Record.end())
            return it->second.second->GetFieldType(Field);
        return -1;
        }
    unsigned int count = (unsigned int)GMST_ModFile_Record.count(recordEDID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            return it->second.second->GetFieldType(Field);
    return -1;
    }

int Collection::GetFIDFieldType(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetFieldType(Field);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetFieldType(Field);
            }
    return 0;
    }

int Collection::GetFIDListFieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListFieldType(subField, listField);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListFieldType(subField, listField);
            }
    return 0;
    }

int Collection::GetFIDListX2FieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX2FieldType(subField, listField, listX2Field);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX2FieldType(subField, listField, listX2Field);
            }
    return 0;
    }

int Collection::GetFIDListX3FieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX3FieldType(subField, listField, listX2Field, listX3Field);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX3FieldType(subField, listField, listX2Field, listX3Field);
            }
    return 0;
    }

unsigned int Collection::GetTES4FieldArraySize(char *ModName, const unsigned int Field)
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return ModFiles[p]->TES4.GetFieldArraySize(Field);
    return -1;
    }

void Collection::GetTES4FieldArray(char *ModName, const unsigned int Field, void **FieldValues)
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            {
            ModFiles[p]->TES4.GetFieldArray(Field, FieldValues);
            return;
            }
    return;
    }

unsigned int Collection::GetFIDFieldArraySize(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetFieldArraySize(Field);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetFieldArraySize(Field);
            }
    return 0;
    }

unsigned int Collection::GetFIDListSize(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListSize(Field);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListSize(Field);
            }
    return 0;
    }

unsigned int Collection::GetFIDListX2Size(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX2Size(subField, listIndex, listField);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX2Size(subField, listIndex, listField);
            }
    return 0;
    }

unsigned int Collection::GetFIDListX3Size(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX3Size(subField, listIndex, listField, listX2Index, listX2Field);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX3Size(subField, listIndex, listField, listX2Index, listX2Field);
            }
    return 0;
    }

unsigned int Collection::GetFIDListArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListArraySize(subField, listIndex, listField);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListArraySize(subField, listIndex, listField);
            }
    return 0;
    }

unsigned int Collection::GetFIDListX2ArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX2ArraySize(subField, listIndex, listField, listX2Index, listX2Field);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX2ArraySize(subField, listIndex, listField, listX2Index, listX2Field);
            }
    return 0;
    }

unsigned int Collection::GetFIDListX3ArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX3ArraySize(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
            }
        return 0;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX3ArraySize(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
            }
    return 0;
    }

void Collection::GetFIDFieldArray(char *ModName, unsigned int recordFID, const unsigned int Field, void **FieldValues)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            curRecord->GetFieldArray(Field, FieldValues);
            }
        return;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            curRecord->GetFieldArray(Field, FieldValues);
            return;
            }
    return;
    }

void Collection::GetFIDListArray(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            curRecord->GetListArray(subField, listIndex, listField, FieldValues);
            }
        return;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            curRecord->GetListArray(subField, listIndex, listField, FieldValues);
            return;
            }
    return;
    }

void Collection::GetFIDListX2Array(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            curRecord->GetListX2Array(subField, listIndex, listField, listX2Index, listX2Field, FieldValues);
            }
        return;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            curRecord->GetListX2Array(subField, listIndex, listField, listX2Index, listX2Field, FieldValues);
            return;
            }
    return;
    }

void Collection::GetFIDListX3Array(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            curRecord->GetListX3Array(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValues);
            }
        return;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            curRecord->GetListX3Array(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValues);
            return;
            }
    return;
    }

void * Collection::ReadTES4Field(char *ModName, const unsigned int Field)
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return ModFiles[p]->TES4.GetField(Field);
    return NULL;
    }

void * Collection::ReadGMSTField(char *ModName, char *recordEDID, const unsigned int Field)
    {
    std::multimap<char*,std::pair<ModFile *, Record *>, sameStr>::iterator it;
    it = GMST_ModFile_Record.find(recordEDID);
    if(ModName == NULL)
        {
        if(it != GMST_ModFile_Record.end())
            return it->second.second->GetField(Field);
        return NULL;
        }
    unsigned int count = (unsigned int)GMST_ModFile_Record.count(recordEDID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            return it->second.second->GetField(Field);
    return NULL;
    }

void * Collection::ReadFIDField(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetField(Field);
            }
        return NULL;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetField(Field);
            }
    return NULL;
    }

void * Collection::ReadFIDListField(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListField(subField, listIndex, listField);
            }
        return NULL;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListField(subField, listIndex, listField);
            }
    return NULL;
    }
void * Collection::ReadFIDListX2Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX2Field(subField, listIndex, listField, listX2Index, listX2Field);
            }
        return NULL;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX2Field(subField, listIndex, listField, listX2Index, listX2Field);
            }
    return NULL;
    }
void * Collection::ReadFIDListX3Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX3Field(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
            }
        return NULL;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            return curRecord->GetListX3Field(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
            }
    return NULL;
    }


int Collection::CreateFIDListElement(char *ModName, unsigned int recordFID, const unsigned int subField)
    {
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    int listIndex = -1;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            listIndex = curRecord->CreateListElement(subField);
            }
        return listIndex;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            listIndex = curRecord->CreateListElement(subField);
            return listIndex;
            }
    return -1;
    }

int Collection::CreateFIDListX2Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    int rListIndex = -1;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            rListIndex = curRecord->CreateListX2Element(subField, listIndex, listField);
            }
        return rListIndex;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            rListIndex = curRecord->CreateListX2Element(subField, listIndex, listField);
            return rListIndex;
            }
    return -1;
    }

int Collection::CreateFIDListX3Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    int rListIndex = -1;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            rListIndex = curRecord->CreateListX3Element(subField, listIndex, listField, listX2Index, listX2Field);
            }
        return rListIndex;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            rListIndex = curRecord->CreateListX3Element(subField, listIndex, listField, listX2Index, listX2Field);
            return rListIndex;
            }
    return -1;
    }

int Collection::DeleteFIDListElement(char *ModName, unsigned int recordFID, const unsigned int subField)
    {
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    int listIndex = -1;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            listIndex = curRecord->DeleteListElement(subField);
            }
        return listIndex;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            listIndex = curRecord->DeleteListElement(subField);
            return listIndex;
            }
    return -1;
    }

int Collection::DeleteFIDListX2Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    int rListIndex = -1;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            rListIndex = curRecord->DeleteListX2Element(subField, listIndex, listField);
            }
        return rListIndex;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            rListIndex = curRecord->DeleteListX2Element(subField, listIndex, listField);
            return rListIndex;
            }
    return -1;
    }

int Collection::DeleteFIDListX3Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    int rListIndex = -1;
    std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
    it = FID_ModFile_Record.find(&recordFID);
    if(ModName == NULL)
        {
        if(it != FID_ModFile_Record.end())
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            rListIndex = curRecord->DeleteListX3Element(subField, listIndex, listField, listX2Index, listX2Field);
            }
        return rListIndex;
        }
    unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
    for(unsigned int x = 0; x < count;it++, x++)
        if(_stricmp(it->second.first->FileName, ModName) == 0 )
            {
            curModFile = it->second.first;
            curRecord = it->second.second;
            curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
            rListIndex = curRecord->DeleteListX3Element(subField, listIndex, listField, listX2Index, listX2Field);
            return rListIndex;
            }
    return -1;
    }

#ifdef _DEBUG
void Collection::Debug(int debugLevel, bool AllRecords)
    {
    try
        {
        for(unsigned int p = 0;p < ModFiles.size();p++)
            {
            //ADD DEFINITIONS HERE
            ModFiles[p]->TES4.Debug(debugLevel);
            ModFiles[p]->GMST.Debug(debugLevel);
            ModFiles[p]->GLOB.Debug(debugLevel);
            ModFiles[p]->CLAS.Debug(debugLevel);
            ModFiles[p]->FACT.Debug(debugLevel);
            ModFiles[p]->HAIR.Debug(debugLevel);
            ModFiles[p]->EYES.Debug(debugLevel);
            ModFiles[p]->RACE.Debug(debugLevel);
            ModFiles[p]->SOUN.Debug(debugLevel);
            ModFiles[p]->SKIL.Debug(debugLevel);
            ModFiles[p]->MGEF.Debug(debugLevel);
            ModFiles[p]->SCPT.Debug(debugLevel);
            ModFiles[p]->LTEX.Debug(debugLevel);
            ModFiles[p]->ENCH.Debug(debugLevel);
            ModFiles[p]->SPEL.Debug(debugLevel);
            ModFiles[p]->BSGN.Debug(debugLevel);
            ModFiles[p]->ACTI.Debug(debugLevel);
            ModFiles[p]->APPA.Debug(debugLevel);
            ModFiles[p]->ARMO.Debug(debugLevel);
            ModFiles[p]->BOOK.Debug(debugLevel);
            ModFiles[p]->CLOT.Debug(debugLevel);
            ModFiles[p]->CONT.Debug(debugLevel);
            ModFiles[p]->DOOR.Debug(debugLevel);
            ModFiles[p]->INGR.Debug(debugLevel);
            ModFiles[p]->LIGH.Debug(debugLevel);
            ModFiles[p]->MISC.Debug(debugLevel);
            ModFiles[p]->STAT.Debug(debugLevel);
            ModFiles[p]->GRAS.Debug(debugLevel);
            ModFiles[p]->TREE.Debug(debugLevel);
            ModFiles[p]->FLOR.Debug(debugLevel);
            ModFiles[p]->FURN.Debug(debugLevel);
            ModFiles[p]->WEAP.Debug(debugLevel);
            ModFiles[p]->AMMO.Debug(debugLevel);
            ModFiles[p]->NPC_.Debug(debugLevel);
            ModFiles[p]->CREA.Debug(debugLevel);
            ModFiles[p]->LVLC.Debug(debugLevel);
            ModFiles[p]->SLGM.Debug(debugLevel);
            ModFiles[p]->KEYM.Debug(debugLevel);
            ModFiles[p]->ALCH.Debug(debugLevel);
            ModFiles[p]->SBSP.Debug(debugLevel);
            ModFiles[p]->SGST.Debug(debugLevel);
            ModFiles[p]->LVLI.Debug(debugLevel);
            ModFiles[p]->WTHR.Debug(debugLevel);
            ModFiles[p]->CLMT.Debug(debugLevel);
            ModFiles[p]->REGN.Debug(debugLevel);
            //ModFiles[p]->CELL.Read(ModFiles[p]->fileBuffer);
            ModFiles[p]->CELL.Debug(debugLevel);
            //ModFiles[p]->WRLD.Read(ModFiles[p]->fileBuffer);
            ModFiles[p]->WRLD.Debug(debugLevel);
            ModFiles[p]->DIAL.Debug(debugLevel);
            ModFiles[p]->QUST.Debug(debugLevel);
            ModFiles[p]->IDLE.Debug(debugLevel);
            ModFiles[p]->PACK.Debug(debugLevel);
            ModFiles[p]->CSTY.Debug(debugLevel);
            ModFiles[p]->LSCR.Debug(debugLevel);
            ModFiles[p]->LVSP.Debug(debugLevel);
            ModFiles[p]->ANIO.Debug(debugLevel);
            ModFiles[p]->WATR.Debug(debugLevel);
            ModFiles[p]->EFSH.Debug(debugLevel);
            }
        }
    catch(...)
        {
        throw;
        }
    return;
    }
#endif
