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

//template<typename ItemType>
//void MergeSort(ItemType* srcArray, ItemType* helpArray, unsigned int size)
//{
//    ItemType* src = srcArray;
//    ItemType* dst = helpArray;
//
//    for(unsigned bSize = 2; bSize < size*2; bSize *= 2)
//    {
//        unsigned dstInd = 0;
//        for(unsigned bInd = 0; bInd < size; bInd += bSize)
//        {
//            unsigned sbInd1 = bInd, sbInd1e = bInd+bSize/2;
//            if(sbInd1e > size) sbInd1e = size;
//            unsigned sbInd2 = sbInd1e, sbInd2e = bInd+bSize;
//            if(sbInd2e > size) sbInd2e = size;
//            while(sbInd1 < sbInd1e && sbInd2 < sbInd2e)
//            {
//                if(src[sbInd1] < src[sbInd2])
//                    dst[dstInd++] = src[sbInd1++];
//                else
//                    dst[dstInd++] = src[sbInd2++];
//            }
//            while(sbInd1 < sbInd1e) dst[dstInd++] = src[sbInd1++];
//            while(sbInd2 < sbInd2e) dst[dstInd++] = src[sbInd2++];
//        }
//        ItemType* tmp = src; src = dst; dst = tmp;
//    }
//    if(src == helpArray)
//    {
//        for(unsigned i = 0; i < size; ++i)
//            dst[i] = src[i];
//    }
//}

bool compMod(ModFile *lhs, ModFile *rhs)
    {
    return *lhs < *rhs;
    }

////Insertion sort
//void sortMods(std::vector<ModFile *> &ModFiles)
//    {
//    ModFile *Temp = NULL;
//    int x = 0;
//    int numMods = (int)ModFiles.size();
//    for (int count = 0; count < numMods; count++)
//        {
//        x = count;
//        for(int index = count + 1; index < numMods; index++)
//            if(*ModFiles[index] < *ModFiles[x])
//                x = index;
//        if(x > count)
//            std::swap(ModFiles[x], ModFiles[count]);
//        }
//    }

////Insertion sort
//void sortMods(std::vector<ModFile *> &ModFiles)
//    {
//    ModFile *Temp;
//    int x = 0;
//    int numMods = (int)ModFiles.size();
//    for (int count = 1; count < numMods; ++count)
//        {
//        x = count;
//        while(x > 0 && *ModFiles[x - 1] > *ModFiles[x])
//            {
//            Temp = ModFiles[x];
//            ModFiles[x] = ModFiles[x - 1];
//            ModFiles[x - 1] = Temp;
//            x--;
//            }
//        }
//    }

bool Collection::IsModAdded(const char *ModName)
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
            return true;
    return false;
    }

int Collection::AddMod(const char *ModName, ModFlags &settings)
    {
    _chdir(ModsDir);
    //Mods may not be added after collection is loaded.
    //It would potentially mess up python accessors if it added anywhere other than the very end
    if(isLoaded)
        return -1;
    //Prevent loading mods more than once
    if(IsModAdded(ModName))
        return -1;
    bool exists = FileExists(ModName);
    settings.IsNew = !exists;
    if(exists || settings.IsDummy || settings.CreateIfNotExist)
        {
        char *FileName = new char[strlen(ModName)+1];
        strcpy_s(FileName, strlen(ModName)+1, ModName);
        ModFiles.push_back(new ModFile(FileName, settings));
        return 0;
        }
    else
        {
        printf("Unable to find %s in %s\n", ModName, ModsDir);
        throw 1;
        return -1;
        }
    return -1;
    }

int Collection::IsEmpty(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return curModFile->IsEmpty();
    }

unsigned int Collection::GetNumNewRecordTypes(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->FormIDHandler.NewTypes.size();
    }

void Collection::GetNewRecordTypes(char *ModName, unsigned int const ** RecordTypes)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    boost::unordered_set<unsigned int>::iterator it;
    unsigned int x = 0;
    for(it = curModFile->FormIDHandler.NewTypes.begin(); it != curModFile->FormIDHandler.NewTypes.end(); ++it, ++x)
        RecordTypes[x] = &(*it);
    return;
    }

int Collection::CleanMasters(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return curModFile->CleanMasters();
    }
int Collection::SafeSaveMod(char *ModName, bool CloseMod)
    {
    if(CloseMod)
        {
        EDID_ModFile_Record.clear();
        FID_ModFile_Record.clear();
        }
    _chdir(ModsDir);
    _FileHandler SaveHandler(BUFFERSIZE);
    //Saves to a temp file, then if successful, renames any existing files, and then renames temp file to ModName
    ModFile *curModFile = NULL;
    char tName[L_tmpnam_s];
    errno_t err;
    time_t ltime;
    struct tm currentTime;
    struct stat oTimes;
    struct _utimbuf originalTimes;

    char *backupName = NULL;
    unsigned int bakAttempts = 0, bakSize = 0;

    curModFile = LookupModFile(ModName);

    //Only save to files that have already been added.
    if(curModFile == NULL || curModFile->Settings.IsDummy || curModFile->Settings.Merge || curModFile->Settings.Scan)
        return -1;
    err = tmpnam_s(tName, L_tmpnam_s);
    if (err)
        {
        printf("Error occurred creating unique filename.\n");
        return -1;
        }
    tName[0] = 'x';
    try
        {
        if(SaveHandler.open_ReadWrite(tName) == -1)
            return -1;

        //Save the mod to temp file, using FileBuffer to write in chunks
        curModFile->Save(SaveHandler, CloseMod);
        SaveHandler.close();

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
        }
    catch(...)
        {
        SaveHandler.close();
        printf("Error saving: %s\n", ModName);
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

void Collection::IndexRecords(ModFile *curModFile, const bool &FullLoad)
    {
    if(curModFile == NULL || curModFile->Settings.IsDummy)
        return;
    RecordReader reader(curModFile->FormIDHandler);
    //Associates record ids at the collection level, allowing for conflicts to be determined.
    //ADD DEFINITIONS HERE
    for(std::vector<GMSTRecord *>::iterator curGMST = curModFile->GMST.Records.begin();curGMST != curModFile->GMST.Records.end();curGMST++)
        EDID_ModFile_Record.insert(std::make_pair((*curGMST)->EDID.value,std::make_pair(curModFile,*curGMST)));
    for(std::vector<GMSTRecord *>::iterator curGMST = curModFile->GMST.Records.begin();curGMST != curModFile->GMST.Records.end();curGMST++)
        FID_ModFile_Record.insert(std::make_pair((*curGMST)->formID,std::make_pair(curModFile,*curGMST)));
    for(std::vector<GLOBRecord *>::iterator curGLOB = curModFile->GLOB.Records.begin();curGLOB != curModFile->GLOB.Records.end();curGLOB++)
        FID_ModFile_Record.insert(std::make_pair((*curGLOB)->formID,std::make_pair(curModFile,*curGLOB)));
    for(std::vector<CLASRecord *>::iterator curCLAS = curModFile->CLAS.Records.begin();curCLAS != curModFile->CLAS.Records.end();curCLAS++)
        FID_ModFile_Record.insert(std::make_pair((*curCLAS)->formID,std::make_pair(curModFile,*curCLAS)));
    for(std::vector<FACTRecord *>::iterator curFACT = curModFile->FACT.Records.begin();curFACT != curModFile->FACT.Records.end();curFACT++)
        FID_ModFile_Record.insert(std::make_pair((*curFACT)->formID,std::make_pair(curModFile,*curFACT)));
    for(std::vector<HAIRRecord *>::iterator curHAIR = curModFile->HAIR.Records.begin();curHAIR != curModFile->HAIR.Records.end();curHAIR++)
        FID_ModFile_Record.insert(std::make_pair((*curHAIR)->formID,std::make_pair(curModFile,*curHAIR)));
    for(std::vector<EYESRecord *>::iterator curEYES = curModFile->EYES.Records.begin();curEYES != curModFile->EYES.Records.end();curEYES++)
        FID_ModFile_Record.insert(std::make_pair((*curEYES)->formID,std::make_pair(curModFile,*curEYES)));
    for(std::vector<RACERecord *>::iterator curRACE = curModFile->RACE.Records.begin();curRACE != curModFile->RACE.Records.end();curRACE++)
        FID_ModFile_Record.insert(std::make_pair((*curRACE)->formID,std::make_pair(curModFile,*curRACE)));
    for(std::vector<SOUNRecord *>::iterator curSOUN = curModFile->SOUN.Records.begin();curSOUN != curModFile->SOUN.Records.end();curSOUN++)
        FID_ModFile_Record.insert(std::make_pair((*curSOUN)->formID,std::make_pair(curModFile,*curSOUN)));
    for(std::vector<SKILRecord *>::iterator curSKIL = curModFile->SKIL.Records.begin();curSKIL != curModFile->SKIL.Records.end();curSKIL++)
        FID_ModFile_Record.insert(std::make_pair((*curSKIL)->formID,std::make_pair(curModFile,*curSKIL)));
    for(std::vector<MGEFRecord *>::iterator curMGEF = curModFile->MGEF.Records.begin();curMGEF != curModFile->MGEF.Records.end();curMGEF++)
        FID_ModFile_Record.insert(std::make_pair((*curMGEF)->formID,std::make_pair(curModFile,*curMGEF)));
    for(std::vector<SCPTRecord *>::iterator curSCPT = curModFile->SCPT.Records.begin();curSCPT != curModFile->SCPT.Records.end();curSCPT++)
        FID_ModFile_Record.insert(std::make_pair((*curSCPT)->formID,std::make_pair(curModFile,*curSCPT)));
    for(std::vector<LTEXRecord *>::iterator curLTEX = curModFile->LTEX.Records.begin();curLTEX != curModFile->LTEX.Records.end();curLTEX++)
        FID_ModFile_Record.insert(std::make_pair((*curLTEX)->formID,std::make_pair(curModFile,*curLTEX)));
    for(std::vector<ENCHRecord *>::iterator curENCH = curModFile->ENCH.Records.begin();curENCH != curModFile->ENCH.Records.end();curENCH++)
        FID_ModFile_Record.insert(std::make_pair((*curENCH)->formID,std::make_pair(curModFile,*curENCH)));
    for(std::vector<SPELRecord *>::iterator curSPEL = curModFile->SPEL.Records.begin();curSPEL != curModFile->SPEL.Records.end();curSPEL++)
        FID_ModFile_Record.insert(std::make_pair((*curSPEL)->formID,std::make_pair(curModFile,*curSPEL)));
    for(std::vector<BSGNRecord *>::iterator curBSGN = curModFile->BSGN.Records.begin();curBSGN != curModFile->BSGN.Records.end();curBSGN++)
        FID_ModFile_Record.insert(std::make_pair((*curBSGN)->formID,std::make_pair(curModFile,*curBSGN)));
    for(std::vector<ACTIRecord *>::iterator curACTI = curModFile->ACTI.Records.begin();curACTI != curModFile->ACTI.Records.end();curACTI++)
        FID_ModFile_Record.insert(std::make_pair((*curACTI)->formID,std::make_pair(curModFile,*curACTI)));
    for(std::vector<APPARecord *>::iterator curAPPA = curModFile->APPA.Records.begin();curAPPA != curModFile->APPA.Records.end();curAPPA++)
        FID_ModFile_Record.insert(std::make_pair((*curAPPA)->formID,std::make_pair(curModFile,*curAPPA)));
    for(std::vector<ARMORecord *>::iterator curARMO = curModFile->ARMO.Records.begin();curARMO != curModFile->ARMO.Records.end();curARMO++)
        FID_ModFile_Record.insert(std::make_pair((*curARMO)->formID,std::make_pair(curModFile,*curARMO)));
    for(std::vector<BOOKRecord *>::iterator curBOOK = curModFile->BOOK.Records.begin();curBOOK != curModFile->BOOK.Records.end();curBOOK++)
        FID_ModFile_Record.insert(std::make_pair((*curBOOK)->formID,std::make_pair(curModFile,*curBOOK)));
    for(std::vector<CLOTRecord *>::iterator curCLOT = curModFile->CLOT.Records.begin();curCLOT != curModFile->CLOT.Records.end();curCLOT++)
        FID_ModFile_Record.insert(std::make_pair((*curCLOT)->formID,std::make_pair(curModFile,*curCLOT)));
    for(std::vector<CONTRecord *>::iterator curCONT = curModFile->CONT.Records.begin();curCONT != curModFile->CONT.Records.end();curCONT++)
        FID_ModFile_Record.insert(std::make_pair((*curCONT)->formID,std::make_pair(curModFile,*curCONT)));
    for(std::vector<DOORRecord *>::iterator curDOOR = curModFile->DOOR.Records.begin();curDOOR != curModFile->DOOR.Records.end();curDOOR++)
        FID_ModFile_Record.insert(std::make_pair((*curDOOR)->formID,std::make_pair(curModFile,*curDOOR)));
    for(std::vector<INGRRecord *>::iterator curINGR = curModFile->INGR.Records.begin();curINGR != curModFile->INGR.Records.end();curINGR++)
        FID_ModFile_Record.insert(std::make_pair((*curINGR)->formID,std::make_pair(curModFile,*curINGR)));
    for(std::vector<LIGHRecord *>::iterator curLIGH = curModFile->LIGH.Records.begin();curLIGH != curModFile->LIGH.Records.end();curLIGH++)
        FID_ModFile_Record.insert(std::make_pair((*curLIGH)->formID,std::make_pair(curModFile,*curLIGH)));
    for(std::vector<MISCRecord *>::iterator curMISC = curModFile->MISC.Records.begin();curMISC != curModFile->MISC.Records.end();curMISC++)
        FID_ModFile_Record.insert(std::make_pair((*curMISC)->formID,std::make_pair(curModFile,*curMISC)));
    for(std::vector<STATRecord *>::iterator curSTAT = curModFile->STAT.Records.begin();curSTAT != curModFile->STAT.Records.end();curSTAT++)
        FID_ModFile_Record.insert(std::make_pair((*curSTAT)->formID,std::make_pair(curModFile,*curSTAT)));
    for(std::vector<GRASRecord *>::iterator curGRAS = curModFile->GRAS.Records.begin();curGRAS != curModFile->GRAS.Records.end();curGRAS++)
        FID_ModFile_Record.insert(std::make_pair((*curGRAS)->formID,std::make_pair(curModFile,*curGRAS)));
    for(std::vector<TREERecord *>::iterator curTREE = curModFile->TREE.Records.begin();curTREE != curModFile->TREE.Records.end();curTREE++)
        FID_ModFile_Record.insert(std::make_pair((*curTREE)->formID,std::make_pair(curModFile,*curTREE)));
    for(std::vector<FLORRecord *>::iterator curFLOR = curModFile->FLOR.Records.begin();curFLOR != curModFile->FLOR.Records.end();curFLOR++)
        FID_ModFile_Record.insert(std::make_pair((*curFLOR)->formID,std::make_pair(curModFile,*curFLOR)));
    for(std::vector<FURNRecord *>::iterator curFURN = curModFile->FURN.Records.begin();curFURN != curModFile->FURN.Records.end();curFURN++)
        FID_ModFile_Record.insert(std::make_pair((*curFURN)->formID,std::make_pair(curModFile,*curFURN)));
    for(std::vector<WEAPRecord *>::iterator curWEAP = curModFile->WEAP.Records.begin();curWEAP != curModFile->WEAP.Records.end();curWEAP++)
        FID_ModFile_Record.insert(std::make_pair((*curWEAP)->formID,std::make_pair(curModFile,*curWEAP)));
    for(std::vector<AMMORecord *>::iterator curAMMO = curModFile->AMMO.Records.begin();curAMMO != curModFile->AMMO.Records.end();curAMMO++)
        FID_ModFile_Record.insert(std::make_pair((*curAMMO)->formID,std::make_pair(curModFile,*curAMMO)));
    for(std::vector<NPC_Record *>::iterator curNPC_ = curModFile->NPC_.Records.begin();curNPC_ != curModFile->NPC_.Records.end();curNPC_++)
        FID_ModFile_Record.insert(std::make_pair((*curNPC_)->formID,std::make_pair(curModFile,*curNPC_)));
    for(std::vector<CREARecord *>::iterator curCREA = curModFile->CREA.Records.begin();curCREA != curModFile->CREA.Records.end();curCREA++)
        FID_ModFile_Record.insert(std::make_pair((*curCREA)->formID,std::make_pair(curModFile,*curCREA)));
    for(std::vector<LVLCRecord *>::iterator curLVLC = curModFile->LVLC.Records.begin();curLVLC != curModFile->LVLC.Records.end();curLVLC++)
        FID_ModFile_Record.insert(std::make_pair((*curLVLC)->formID,std::make_pair(curModFile,*curLVLC)));
    for(std::vector<SLGMRecord *>::iterator curSLGM = curModFile->SLGM.Records.begin();curSLGM != curModFile->SLGM.Records.end();curSLGM++)
        FID_ModFile_Record.insert(std::make_pair((*curSLGM)->formID,std::make_pair(curModFile,*curSLGM)));
    for(std::vector<KEYMRecord *>::iterator curKEYM = curModFile->KEYM.Records.begin();curKEYM != curModFile->KEYM.Records.end();curKEYM++)
        FID_ModFile_Record.insert(std::make_pair((*curKEYM)->formID,std::make_pair(curModFile,*curKEYM)));
    for(std::vector<ALCHRecord *>::iterator curALCH = curModFile->ALCH.Records.begin();curALCH != curModFile->ALCH.Records.end();curALCH++)
        FID_ModFile_Record.insert(std::make_pair((*curALCH)->formID,std::make_pair(curModFile,*curALCH)));
    for(std::vector<SBSPRecord *>::iterator curSBSP = curModFile->SBSP.Records.begin();curSBSP != curModFile->SBSP.Records.end();curSBSP++)
        FID_ModFile_Record.insert(std::make_pair((*curSBSP)->formID,std::make_pair(curModFile,*curSBSP)));
    for(std::vector<SGSTRecord *>::iterator curSGST = curModFile->SGST.Records.begin();curSGST != curModFile->SGST.Records.end();curSGST++)
        FID_ModFile_Record.insert(std::make_pair((*curSGST)->formID,std::make_pair(curModFile,*curSGST)));
    for(std::vector<LVLIRecord *>::iterator curLVLI = curModFile->LVLI.Records.begin();curLVLI != curModFile->LVLI.Records.end();curLVLI++)
        FID_ModFile_Record.insert(std::make_pair((*curLVLI)->formID,std::make_pair(curModFile,*curLVLI)));
    for(std::vector<WTHRRecord *>::iterator curWTHR = curModFile->WTHR.Records.begin();curWTHR != curModFile->WTHR.Records.end();curWTHR++)
        FID_ModFile_Record.insert(std::make_pair((*curWTHR)->formID,std::make_pair(curModFile,*curWTHR)));
    for(std::vector<CLMTRecord *>::iterator curCLMT = curModFile->CLMT.Records.begin();curCLMT != curModFile->CLMT.Records.end();curCLMT++)
        FID_ModFile_Record.insert(std::make_pair((*curCLMT)->formID,std::make_pair(curModFile,*curCLMT)));
    for(std::vector<REGNRecord *>::iterator curREGN = curModFile->REGN.Records.begin();curREGN != curModFile->REGN.Records.end();curREGN++)
        FID_ModFile_Record.insert(std::make_pair((*curREGN)->formID,std::make_pair(curModFile,*curREGN)));

    for(std::vector<CELLRecord *>::iterator curCELL = curModFile->CELL.Records.begin();curCELL != curModFile->CELL.Records.end();curCELL++)
        {
        FID_ModFile_Record.insert(std::make_pair((*curCELL)->formID,std::make_pair(curModFile,*curCELL)));
        for(std::vector<ACHRRecord *>::iterator curACHR = (*curCELL)->ACHR.begin();curACHR != (*curCELL)->ACHR.end();curACHR++)
            FID_ModFile_Record.insert(std::make_pair((*curACHR)->formID,std::make_pair(curModFile,*curACHR)));

        for(std::vector<ACRERecord *>::iterator curACRE = (*curCELL)->ACRE.begin();curACRE != (*curCELL)->ACRE.end();curACRE++)
            FID_ModFile_Record.insert(std::make_pair((*curACRE)->formID,std::make_pair(curModFile,*curACRE)));

        for(std::vector<REFRRecord *>::iterator curREFR = (*curCELL)->REFR.begin();curREFR != (*curCELL)->REFR.end();curREFR++)
            FID_ModFile_Record.insert(std::make_pair((*curREFR)->formID,std::make_pair(curModFile,*curREFR)));

        if((*curCELL)->PGRD != NULL)
            FID_ModFile_Record.insert(std::make_pair((*curCELL)->PGRD->formID,std::make_pair(curModFile,(*curCELL)->PGRD)));
        }

    for(std::vector<WRLDRecord *>::iterator curWRLD = curModFile->WRLD.Records.begin();curWRLD != curModFile->WRLD.Records.end();curWRLD++)
        {
        WRLDRecord *curWRLDRecord = *curWRLD;
        FID_ModFile_Record.insert(std::make_pair(curWRLDRecord->formID,std::make_pair(curModFile,curWRLDRecord)));

        for(std::vector<CELLRecord *>::iterator curCELL = curWRLDRecord->CELLS.begin();curCELL != curWRLDRecord->CELLS.end();curCELL++)
            {
            FID_ModFile_Record.insert(std::make_pair((*curCELL)->formID,std::make_pair(curModFile,*curCELL)));
            for(std::vector<ACHRRecord *>::iterator curACHR = (*curCELL)->ACHR.begin();curACHR != (*curCELL)->ACHR.end();curACHR++)
                FID_ModFile_Record.insert(std::make_pair((*curACHR)->formID,std::make_pair(curModFile,*curACHR)));

            for(std::vector<ACRERecord *>::iterator curACRE = (*curCELL)->ACRE.begin();curACRE != (*curCELL)->ACRE.end();curACRE++)
                FID_ModFile_Record.insert(std::make_pair((*curACRE)->formID,std::make_pair(curModFile,*curACRE)));

            for(std::vector<REFRRecord *>::iterator curREFR = (*curCELL)->REFR.begin();curREFR != (*curCELL)->REFR.end();curREFR++)
                FID_ModFile_Record.insert(std::make_pair((*curREFR)->formID,std::make_pair(curModFile,*curREFR)));

            if((*curCELL)->PGRD != NULL)
                FID_ModFile_Record.insert(std::make_pair((*curCELL)->PGRD->formID,std::make_pair(curModFile,(*curCELL)->PGRD)));
            if((*curCELL)->LAND != NULL)
                FID_ModFile_Record.insert(std::make_pair((*curCELL)->LAND->formID,std::make_pair(curModFile,(*curCELL)->LAND)));

            //There might be ACHR, ACRE, or REFR records in the World CELL if it exists
            if(curWRLDRecord->CELL != NULL)
                {
                ACHRRecord *curACHRRecord = NULL;
                ACRERecord *curACRERecord = NULL;
                REFRRecord *curREFRRecord = NULL;
                CELLRecord *curCELLRecord = *curCELL;
                int gridX = 0, gridY = 0;

                reader.Accept(*curCELLRecord);
                for(unsigned int x = 0; x < curWRLDRecord->CELL->ACHR.size();)
                    {
                    curACHRRecord = curWRLDRecord->CELL->ACHR[x];
                    //Have to test each ACHR to see if it belongs to the cell. This is determined by its positioning.
                    reader.Accept(*curACHRRecord);
                    ResolveGrid(curACHRRecord->DATA.value.posX, curACHRRecord->DATA.value.posY, gridX, gridY);
                    if(!FullLoad)
                        curACHRRecord->Unload();
                    curCELLRecord->XCLC.Load();
                    if(gridX == curCELLRecord->XCLC->posX && gridY == curCELLRecord->XCLC->posY)
                        {
                        //For easier use later on, go ahead and move it to the parent cell.
                        //It will get moved back later during the save process if need be.
                        curCELLRecord->ACHR.push_back(curACHRRecord);
                        curWRLDRecord->CELL->ACHR.erase(curWRLDRecord->CELL->ACHR.begin() + x);
                        }
                    else ++x;
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELL->ACRE.size();)
                    {
                    curACRERecord = curWRLDRecord->CELL->ACRE[x];
                    reader.Accept(*curACRERecord);
                    ResolveGrid(curACRERecord->DATA.value.posX, curACRERecord->DATA.value.posY, gridX, gridY);
                    if(!FullLoad)
                        curACRERecord->Unload();
                    curCELLRecord->XCLC.Load();
                    if(gridX == curCELLRecord->XCLC->posX && gridY == curCELLRecord->XCLC->posY)
                        {
                        curCELLRecord->ACRE.push_back(curACRERecord);
                        curWRLDRecord->CELL->ACRE.erase(curWRLDRecord->CELL->ACRE.begin() + x);
                        }
                    else ++x;
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELL->REFR.size();)
                    {
                    curREFRRecord = curWRLDRecord->CELL->REFR[x];
                    reader.Accept(*curREFRRecord);
                    ResolveGrid(curREFRRecord->DATA.value.posX, curREFRRecord->DATA.value.posY, gridX, gridY);
                    if(!FullLoad)
                        curREFRRecord->Unload();
                    curCELLRecord->XCLC.Load();
                    if(gridX == curCELLRecord->XCLC->posX && gridY == curCELLRecord->XCLC->posY)
                        {
                        curCELLRecord->REFR.push_back(curREFRRecord);
                        curWRLDRecord->CELL->REFR.erase(curWRLDRecord->CELL->REFR.begin() + x);
                        }
                    else ++x;
                    }
                if(!FullLoad)
                    curCELLRecord->Unload();
                }
            }

        if(curWRLDRecord->CELL != NULL)
            {
            FID_ModFile_Record.insert(std::make_pair(curWRLDRecord->CELL->formID,std::make_pair(curModFile,curWRLDRecord->CELL)));
            for(std::vector<ACHRRecord *>::iterator curACHR = curWRLDRecord->CELL->ACHR.begin();curACHR != curWRLDRecord->CELL->ACHR.end();curACHR++)
                FID_ModFile_Record.insert(std::make_pair((*curACHR)->formID,std::make_pair(curModFile,*curACHR)));

            for(std::vector<ACRERecord *>::iterator curACRE = curWRLDRecord->CELL->ACRE.begin();curACRE != curWRLDRecord->CELL->ACRE.end();curACRE++)
                FID_ModFile_Record.insert(std::make_pair((*curACRE)->formID,std::make_pair(curModFile,*curACRE)));

            for(std::vector<REFRRecord *>::iterator curREFR = curWRLDRecord->CELL->REFR.begin();curREFR != curWRLDRecord->CELL->REFR.end();curREFR++)
                FID_ModFile_Record.insert(std::make_pair((*curREFR)->formID,std::make_pair(curModFile,*curREFR)));

            if(curWRLDRecord->CELL->PGRD != NULL)
                FID_ModFile_Record.insert(std::make_pair(curWRLDRecord->CELL->PGRD->formID,std::make_pair(curModFile,curWRLDRecord->CELL->PGRD)));
            if(curWRLDRecord->CELL->LAND != NULL)
                FID_ModFile_Record.insert(std::make_pair(curWRLDRecord->CELL->LAND->formID,std::make_pair(curModFile,curWRLDRecord->CELL->LAND)));
            }

        if(curWRLDRecord->ROAD != NULL)
            FID_ModFile_Record.insert(std::make_pair(curWRLDRecord->ROAD->formID,std::make_pair(curModFile,curWRLDRecord->ROAD)));
        }

    for(std::vector<DIALRecord *>::iterator curDIAL = curModFile->DIAL.Records.begin();curDIAL != curModFile->DIAL.Records.end();curDIAL++)
        {
        FID_ModFile_Record.insert(std::make_pair((*curDIAL)->formID,std::make_pair(curModFile,*curDIAL)));
        for(std::vector<INFORecord *>::iterator curINFO = (*curDIAL)->INFO.begin();curINFO != (*curDIAL)->INFO.end();curINFO++)
            FID_ModFile_Record.insert(std::make_pair((*curINFO)->formID,std::make_pair(curModFile,*curINFO)));
        }

    for(std::vector<QUSTRecord *>::iterator curQUST = curModFile->QUST.Records.begin();curQUST != curModFile->QUST.Records.end();curQUST++)
        FID_ModFile_Record.insert(std::make_pair((*curQUST)->formID,std::make_pair(curModFile,*curQUST)));
    for(std::vector<IDLERecord *>::iterator curIDLE = curModFile->IDLE.Records.begin();curIDLE != curModFile->IDLE.Records.end();curIDLE++)
        FID_ModFile_Record.insert(std::make_pair((*curIDLE)->formID,std::make_pair(curModFile,*curIDLE)));
    for(std::vector<PACKRecord *>::iterator curPACK = curModFile->PACK.Records.begin();curPACK != curModFile->PACK.Records.end();curPACK++)
        FID_ModFile_Record.insert(std::make_pair((*curPACK)->formID,std::make_pair(curModFile,*curPACK)));
    for(std::vector<CSTYRecord *>::iterator curCSTY = curModFile->CSTY.Records.begin();curCSTY != curModFile->CSTY.Records.end();curCSTY++)
        FID_ModFile_Record.insert(std::make_pair((*curCSTY)->formID,std::make_pair(curModFile,*curCSTY)));
    for(std::vector<LSCRRecord *>::iterator curLSCR = curModFile->LSCR.Records.begin();curLSCR != curModFile->LSCR.Records.end();curLSCR++)
        FID_ModFile_Record.insert(std::make_pair((*curLSCR)->formID,std::make_pair(curModFile,*curLSCR)));
    for(std::vector<LVSPRecord *>::iterator curLVSP = curModFile->LVSP.Records.begin();curLVSP != curModFile->LVSP.Records.end();curLVSP++)
        FID_ModFile_Record.insert(std::make_pair((*curLVSP)->formID,std::make_pair(curModFile,*curLVSP)));
    for(std::vector<ANIORecord *>::iterator curANIO = curModFile->ANIO.Records.begin();curANIO != curModFile->ANIO.Records.end();curANIO++)
        FID_ModFile_Record.insert(std::make_pair((*curANIO)->formID,std::make_pair(curModFile,*curANIO)));
    for(std::vector<WATRRecord *>::iterator curWATR = curModFile->WATR.Records.begin();curWATR != curModFile->WATR.Records.end();curWATR++)
        FID_ModFile_Record.insert(std::make_pair((*curWATR)->formID,std::make_pair(curModFile,*curWATR)));
    for(std::vector<EFSHRecord *>::iterator curEFSH = curModFile->EFSH.Records.begin();curEFSH != curModFile->EFSH.Records.end();curEFSH++)
        FID_ModFile_Record.insert(std::make_pair((*curEFSH)->formID,std::make_pair(curModFile,*curEFSH)));
    }

void Collection::IndexRecords(const bool &FullLoad)
    {
    ModFile *curModFile = NULL;
    //boost::threadpool::pool IndexThreads(NUMTHREADS);
    for(unsigned int p = 0; p < (unsigned int)ModFiles.size(); ++p)
        {
        curModFile = ModFiles[p];
        if(!curModFile->Settings.IsDummy)
            //IndexThreads.schedule(boost::bind(&Collection::IndexRecords, this, curModFile));
            IndexRecords(curModFile, FullLoad);
        }
    }

int Collection::Load(const bool &LoadMasters, const bool &FullLoad)
    {
    ModFile *curModFile = NULL;
    bool Preloading = false;
    ModFlags preloadSettings;
    preloadSettings.IsDummy = !LoadMasters;
    if(isLoaded)
        return 0;
    try
        {
        //printf("Loading Collection\n");
        _chdir(ModsDir);
        boost::threadpool::pool ReadThreads(NUMTHREADS);
        //std::vector<char *> LoadOrder;
        //Brute force approach to loading all masters
        //Could be done more elegantly with recursion
        do {
            Preloading = false;
            for(unsigned char p = 0; p < (unsigned char)ModFiles.size(); ++p)
                {
                curModFile = ModFiles[p];
                curModFile->LoadTES4();
                if(!curModFile->Settings.Merge && !curModFile->Settings.Scan)
                    for(unsigned char x = 0; x < curModFile->TES4.MAST.size(); ++x)
                        Preloading = (AddMod(curModFile->TES4.MAST[x].value, preloadSettings) == 0 || Preloading);
                }
            }while(Preloading);
        //printf("Before Sort\n");
        //for(unsigned int p = 0; p < (unsigned int)ModFiles.size(); ++p)
        //    printf("%02X: %s\n", p, ModFiles[p]->FileName);

        std::_Insertion_sort(ModFiles.begin(),ModFiles.end(),compMod);
        //sortMods(ModFiles);
        //std::sort(ModFiles.begin(), ModFiles.end());
        //printf("\n\n");
        //printf("After Sort\n");
        //for(unsigned int p = 0; p < (unsigned int)ModFiles.size(); ++p)
        //    printf("%02X: %s\n", p, ModFiles[p]->FileName);
        //LoadOrder.resize(ModFiles.size());
        AllLoadOrder.clear();
        LoadOrder255.clear();
        for(unsigned int p = 0; p < (unsigned int)ModFiles.size(); ++p)
            {
            AllLoadOrder.push_back(ModFiles[p]->FileName);
            if(!ModFiles[p]->Settings.Merge && !ModFiles[p]->Settings.Scan)
                LoadOrder255.push_back(ModFiles[p]->FileName);
            }
            //else
            //    printf("Merge - %s\n", ModFiles[p]->FileName);
        //printf("\n\n");

        //for(unsigned int p = 0; p < (unsigned int)LoadOrder.size(); ++p)
        //    printf("%02X: %s\n", p, LoadOrder[p]);
        //printf("\n\n");
        unsigned int expandedIndex = 0;
        for(unsigned int p = 0; p < (unsigned int)ModFiles.size(); ++p)
            {
            curModFile = ModFiles[p];
            //Loads GRUP and Record Headers.  Fully loads GMST records.
            curModFile->FormIDHandler.SetLoadOrder(LoadOrder255);
            //printf("%02X: %s\n", expandedIndex, curModFile->FileName);
            if(curModFile->Settings.Merge || curModFile->Settings.Scan)
                curModFile->FormIDHandler.CreateFormIDLookup(0xFF);
            else
                {
                curModFile->FormIDHandler.CreateFormIDLookup(expandedIndex);
                ++expandedIndex;
                }
            //printf("Start Load\n");
            curModFile->Load(ReadThreads, FullLoad);
            //printf("End Index\n");
            }
        //printf("End Load\n\n");
        isLoaded = true;
        }
    catch(std::exception& e)
        {
        printf("%s\n", e.what());
        isLoaded = false;
        throw;
        return -1;
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

unsigned int Collection::NextFreeExpandedFID(ModFile *curModFile, unsigned int depth)
    {
    unsigned int curFormID = curModFile->FormIDHandler.NextExpandedFID();
    FID_Range range = FID_ModFile_Record.equal_range(curFormID);
    //FormID doesn't exist in any mod, so it's free for use
    if(range.first == range.second)
        return curFormID;
    //The formID already exists, so try again (either in that mod, or being injected into that mod)
    //Wrap around and recycle any freed ids.
    if(depth < 0x00FFFFFF)
        return NextFreeExpandedFID(curModFile, depth++);
    //All formIDs are in use. Unlikely to ever occur.
    return 0;
    }

int Collection::RemoveIndex(Record *curRecord, char *ModName)
    {
    FID_Range range = FID_ModFile_Record.equal_range(curRecord->formID);
    for(; range.first != range.second; ++range.first)
        if(_stricmp(range.first->second.first->FileName, ModName) == 0)
            {
            FID_ModFile_Record.erase(range.first);
            return 0;
            }
    return -1;
    }

int Collection::LoadRecord(char *ModName, unsigned int recordFID)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;

    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL || curRecord->recData == NULL)
        return -1;

    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return 0;
    }

int Collection::UnloadRecord(char *ModName, unsigned int recordFID)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;

    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL || curRecord->recData == NULL)
        return -1;

    curRecord->Unload();
    return 0;
    }

int Collection::UnloadModFile(char *ModName)
    {
    ModFile *curModFile = LookupModFile(ModName);

    RecordUnloader unloader;
    curModFile->VisitRecords(unloader);
    return 0;
    }

int Collection::UnloadAll()
    {
    Record *curRecord = NULL;
    for(FID_Iterator it = FID_ModFile_Record.begin(); it != FID_ModFile_Record.end(); ++it)
        {
        curRecord = it->second.second;
        if(curRecord != NULL && curRecord->recData != NULL)
            curRecord->Unload();
        }
    return 0;
    }

unsigned int Collection::CreateRecord(char *ModName, const unsigned int RecordType, const unsigned int ParentFID, unsigned int CreateFlags)
    {
    CreateRecordOptions options(CreateFlags);
    ModFile *curModFile = NULL;
    Record *DummyRecord = NULL;
    Record *ParentRecord = NULL;

    //Lookup the required data, and ensure it exists
    if(ParentFID)
        {
        LookupRecord(ModName, ParentFID, curModFile, ParentRecord);
        if(ParentRecord == NULL)
            return 0;
        }
    else
        {
        curModFile = LookupModFile(ModName);
        }
    if(curModFile == NULL)
        return 0;

    //Create the new record
    Record *curRecord = curModFile->CreateRecord(RecordType, DummyRecord, ParentRecord, options);
    if(curRecord == NULL)
        return 0;

    //See if an existing record was returned instead of a new record
    if(curRecord->formID != 0)
        return curRecord->formID;

    //Assign the new record an unused formID
    unsigned int newRecordFID = curRecord->formID = NextFreeExpandedFID(curModFile);

    //Index the new record
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return newRecordFID;
    }

unsigned int Collection::CopyRecord(char *ModName, unsigned int RecordFID, char *DestModName, unsigned int DestParentFID, unsigned int CreateFlags)
    {
    CreateRecordOptions options(CreateFlags);
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;

    LookupRecord(ModName, RecordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;

    ModFile *DestModFile = NULL;
    Record *ParentRecord = NULL;
    Record *RecordCopy = NULL;

    if(options.SetAsOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(DestModName, RecordFID, DestModFile, RecordCopy);
        if(DestModFile != NULL || RecordCopy != NULL)
            return RecordFID;
        }

    if(DestParentFID)
        {
        //See if the parent record already exists in the destination mod
        LookupRecord(DestModName, DestParentFID, DestModFile, ParentRecord);
        if(ParentRecord == NULL)
            {
            //If it doesn't, try and create it.
            CreateRecordOptions parentOptions;
            parentOptions.SetAsOverride = options.SetAsOverride;
            DestParentFID = CopyRecord(ModName, DestParentFID, DestModName, 0, parentOptions.GetFlagField());
            LookupRecord(DestModName, DestParentFID, DestModFile, ParentRecord);
            if(ParentRecord == NULL)
                return 0;
            }
        }
    else
        {
        DestModFile = LookupModFile(DestModName);
        }
    if(DestModFile == NULL || curModFile == DestModFile)
        return 0;

    //Ensure the record has been fully read
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);

    //Create the record copy
    RecordCopy = curModFile->CreateRecord(curRecord->GetType(), curRecord, ParentRecord, options);
    if(RecordCopy == NULL)
        return 0;

    //See if an existing record was returned instead of the requested copy
    if(RecordCopy->formID != curRecord->formID)
        return RecordCopy->formID;

    //Give the record a new formID if it isn't an override record
    if(!options.SetAsOverride)
        RecordCopy->formID = NextFreeExpandedFID(DestModFile);

    //See if the destination mod masters need updating
    FormIDMasterUpdater checker(DestModFile->FormIDHandler);
    checker.Accept(RecordCopy->formID);
    RecordCopy->VisitFormIDs(checker);

    //Index the record
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));

    return RecordCopy->formID;
    }

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

    curRecord = new GMSTRecord(recordEDID);
    unsigned int newRecordFID = curRecord->formID = NextFreeExpandedFID(curModFile);

    curModFile->GMST.Records.push_back(curRecord);
    EDID_ModFile_Record.insert(std::make_pair(curRecord->EDID.value,std::make_pair(curModFile,curRecord)));
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
    RecordReader reader(srcMod->FormIDHandler);

    //Ensure the record has been fully read
    reader.Accept(*srcRecord);
    copyRecord = new GMSTRecord(srcRecord);
    destMod->GMST.Records.push_back(copyRecord);
    //Add any master as necessary, and register the formID
    FormIDMasterUpdater checker(destMod->FormIDHandler);
    checker.Accept(copyRecord->formID);
    copyRecord->VisitFormIDs(checker);
    EDID_ModFile_Record.insert(std::make_pair(copyRecord->EDID.value, std::make_pair(destMod, copyRecord)));
    return 1;
    }

int Collection::DeleteRecord(char *ModName, unsigned int recordFID, unsigned int parentFID)
    {
    Record *curRecord = NULL;
    Record *curParentRecord = NULL;
    ModFile *curModFile = NULL;
    ModFile *curParentModFile = NULL;
    Record *curChild = NULL;
    bool hasParent = (parentFID != 0);
    FID_Iterator it = LookupRecord(ModName, recordFID, curModFile, curRecord);

    if(hasParent)
        {
        LookupRecord(ModName, parentFID, curParentModFile, curParentRecord);
        if(curParentModFile == NULL || curParentRecord == NULL || curParentModFile != curModFile)
            {
            throw 1;
            return -1;
            }
        }

    if(it == FID_ModFile_Record.end() || curModFile == NULL || curRecord == NULL)
        {
        throw 1;
        return -1;
        }

    switch(curRecord->GetType())
        {
        case eGLOB:
            curModFile->GLOB.DeleteRecord(curRecord);
            break;
        case eCLAS:
            curModFile->CLAS.DeleteRecord(curRecord);
            break;
        case eFACT:
            curModFile->FACT.DeleteRecord(curRecord);
            break;
        case eHAIR:
            curModFile->HAIR.DeleteRecord(curRecord);
            break;
        case eEYES:
            curModFile->EYES.DeleteRecord(curRecord);
            break;
        case eRACE:
            curModFile->RACE.DeleteRecord(curRecord);
            break;
        case eSOUN:
            curModFile->SOUN.DeleteRecord(curRecord);
            break;
        case eSKIL:
            curModFile->SKIL.DeleteRecord(curRecord);
            break;
        case eMGEF:
            curModFile->MGEF.DeleteRecord(curRecord);
            break;
        case eSCPT:
            curModFile->SCPT.DeleteRecord(curRecord);
            break;
        case eLTEX:
            curModFile->LTEX.DeleteRecord(curRecord);
            break;
        case eENCH:
            curModFile->ENCH.DeleteRecord(curRecord);
            break;
        case eSPEL:
            curModFile->SPEL.DeleteRecord(curRecord);
            break;
        case eBSGN:
            curModFile->BSGN.DeleteRecord(curRecord);
            break;
        case eACTI:
            curModFile->ACTI.DeleteRecord(curRecord);
            break;
        case eAPPA:
            curModFile->APPA.DeleteRecord(curRecord);
            break;
        case eARMO:
            curModFile->ARMO.DeleteRecord(curRecord);
            break;
        case eBOOK:
            curModFile->BOOK.DeleteRecord(curRecord);
            break;
        case eCLOT:
            curModFile->CLOT.DeleteRecord(curRecord);
            break;
        case eCONT:
            curModFile->CONT.DeleteRecord(curRecord);
            break;
        case eDOOR:
            curModFile->DOOR.DeleteRecord(curRecord);
            break;
        case eINGR:
            curModFile->INGR.DeleteRecord(curRecord);
            break;
        case eLIGH:
            curModFile->LIGH.DeleteRecord(curRecord);
            break;
        case eMISC:
            curModFile->MISC.DeleteRecord(curRecord);
            break;
        case eSTAT:
            curModFile->STAT.DeleteRecord(curRecord);
            break;
        case eGRAS:
            curModFile->GRAS.DeleteRecord(curRecord);
            break;
        case eTREE:
            curModFile->TREE.DeleteRecord(curRecord);
            break;
        case eFLOR:
            curModFile->FLOR.DeleteRecord(curRecord);
            break;
        case eFURN:
            curModFile->FURN.DeleteRecord(curRecord);
            break;
        case eWEAP:
            curModFile->WEAP.DeleteRecord(curRecord);
            break;
        case eAMMO:
            curModFile->AMMO.DeleteRecord(curRecord);
            break;
        case eNPC_:
            curModFile->NPC_.DeleteRecord(curRecord);
            break;
        case eCREA:
            curModFile->CREA.DeleteRecord(curRecord);
            break;
        case eLVLC:
            curModFile->LVLC.DeleteRecord(curRecord);
            break;
        case eSLGM:
            curModFile->SLGM.DeleteRecord(curRecord);
            break;
        case eKEYM:
            curModFile->KEYM.DeleteRecord(curRecord);
            break;
        case eALCH:
            curModFile->ALCH.DeleteRecord(curRecord);
            break;
        case eSBSP:
            curModFile->SBSP.DeleteRecord(curRecord);
            break;
        case eSGST:
            curModFile->SGST.DeleteRecord(curRecord);
            break;
        case eLVLI:
            curModFile->LVLI.DeleteRecord(curRecord);
            break;
        case eWTHR:
            curModFile->WTHR.DeleteRecord(curRecord);
            break;
        case eCLMT:
            curModFile->CLMT.DeleteRecord(curRecord);
            break;
        case eREGN:
            curModFile->REGN.DeleteRecord(curRecord);
            break;
        ///////////////////////////////////////////////
        case eCELL:
            DeleteCELL((CELLRecord *)curRecord, ModName);

            if(hasParent)
                curModFile->WRLD.DeleteRecord(curParentRecord, curRecord);
            else
                curModFile->CELL.DeleteRecord(curRecord, NULL);
            break;
        //Fall-through is intentional
        case ePGRD:
        case eLAND:
        case eACHR:
        case eACRE:
        case eREFR:
            if(hasParent)
                {
                if(((CELLRecord *)curParentRecord)->IsInterior())
                    curModFile->CELL.DeleteRecord(curParentRecord, curRecord);
                else
                    curModFile->WRLD.DeleteRecord(curParentRecord, curRecord);
                }
            else
                {
                printf("Error deleting %s record: %08X\nUnable to find parent CELL record: %08x\n", curRecord->GetStrType(), recordFID, parentFID);
                throw 1;
                return 0;
                }
            break;
        case eWRLD:
            curChild = ((WRLDRecord *)curRecord)->ROAD;
            RemoveIndex(curChild, ModName);
            delete curChild;
            ((WRLDRecord *)curRecord)->ROAD = NULL;

            curChild = ((WRLDRecord *)curRecord)->CELL;
            DeleteCELL((CELLRecord *)curChild, ModName);
            RemoveIndex(curChild, ModName);
            delete curChild;
            ((WRLDRecord *)curRecord)->CELL = NULL;

            for(unsigned int p = 0; p < ((WRLDRecord *)curRecord)->CELLS.size(); ++p)
                {
                curChild = ((WRLDRecord *)curRecord)->CELLS[p];
                DeleteCELL((CELLRecord *)curChild, ModName);
                RemoveIndex(curChild, ModName);
                delete curChild;
                }
            ((WRLDRecord *)curRecord)->CELLS.clear();

            curModFile->WRLD.DeleteRecord(curRecord, NULL);
            break;
        case eROAD:
            if(hasParent)
                curModFile->WRLD.DeleteRecord(curParentRecord, curRecord);
            else
                {
                printf("Error deleting %s record: %08X\nUnable to find parent WRLD record: %08x\n", curRecord->GetStrType(), recordFID, parentFID);
                throw 1;
                return 0;
                }
            break;
        case eDIAL:
            for(unsigned int p = 0; p < ((DIALRecord *)curRecord)->INFO.size(); ++p)
                {
                curChild = ((DIALRecord *)curRecord)->INFO[p];
                RemoveIndex(curChild, ModName);
                delete curChild;
                }
            ((DIALRecord *)curRecord)->INFO.clear();

            curModFile->DIAL.DeleteRecord(curRecord, NULL);
            break;
        case eINFO:
            if(hasParent)
                curModFile->DIAL.DeleteRecord(curParentRecord, curRecord);
            else
                {
                printf("Error deleting %s record: %08X\nUnable to find parent INFO record: %08x\n", curRecord->GetStrType(), recordFID, parentFID);
                throw 1;
                return 0;
                }
            break;
        ///////////////////////////////////////////////
        case eQUST:
            curModFile->QUST.DeleteRecord(curRecord);
            break;
        case eIDLE:
            curModFile->IDLE.DeleteRecord(curRecord);
            break;
        case ePACK:
            curModFile->PACK.DeleteRecord(curRecord);
            break;
        case eCSTY:
            curModFile->CSTY.DeleteRecord(curRecord);
            break;
        case eLSCR:
            curModFile->LSCR.DeleteRecord(curRecord);
            break;
        case eLVSP:
            curModFile->LVSP.DeleteRecord(curRecord);
            break;
        case eANIO:
            curModFile->ANIO.DeleteRecord(curRecord);
            break;
        case eWATR:
            curModFile->WATR.DeleteRecord(curRecord);
            break;
        case eEFSH:
            curModFile->EFSH.DeleteRecord(curRecord);
            break;
        default:
            printf("Error deleting record: %08X. Unknown type: %s\n", recordFID, curRecord->GetStrType());
            break;
        }

    FID_ModFile_Record.erase(it);
    return 0;
    }

int Collection::DeleteCELL(CELLRecord *curCell, char *ModName)
    {
    if(curCell == NULL || ModName == NULL)
        return -1;
    Record *curChild = NULL;

    curChild = curCell->PGRD;
    RemoveIndex(curChild, ModName);
    delete curChild;
    curCell->PGRD = NULL;

    curChild = curCell->LAND;
    RemoveIndex(curChild, ModName);
    delete curChild;
    curCell->LAND = NULL;

    for(unsigned int p = 0; p < curCell->ACHR.size(); ++p)
        {
        curChild = curCell->ACHR[p];
        RemoveIndex(curChild, ModName);
        delete curChild;
        }
    curCell->ACHR.clear();

    for(unsigned int p = 0; p < curCell->ACRE.size(); ++p)
        {
        curChild = curCell->ACRE[p];
        RemoveIndex(curChild, ModName);
        delete curChild;
        }
    curCell->ACRE.clear();

    for(unsigned int p = 0; p < curCell->REFR.size(); ++p)
        {
        curChild = curCell->REFR[p];
        RemoveIndex(curChild, ModName);
        delete curChild;
        }
    curCell->REFR.clear();
    return 0;
    }

int Collection::DeleteGMSTRecord(char *ModName, char *recordEDID)
    {
    if(recordEDID == NULL)
        {
        throw 1;
        return -1;
        }
    GMSTRecord *curRecord = NULL;
    ModFile *curModFile = NULL;
    EDID_Iterator it;
    it = LookupGMSTRecord(ModName, recordEDID, curModFile, curRecord);

    if(it == EDID_ModFile_Record.end() || curModFile == NULL || curRecord == NULL)
        {
        throw 1;
        return -1;
        }

    curRecord = (GMSTRecord *)(it->second.second);
    std::vector<GMSTRecord *>::iterator GMST_it;
    GMST_it = std::find(curModFile->GMST.Records.begin(), curModFile->GMST.Records.end(), curRecord);
    if(GMST_it == curModFile->GMST.Records.end())
        {
        printf("Record %08X not found in %s\n", curRecord->formID, curRecord->GetStrType());
        throw 1;
        return -1;
        }
    delete curRecord;
    curModFile->GMST.Records.erase(GMST_it);

    EDID_ModFile_Record.erase(it);
    return 0;
    }

int Collection::Close()
    {
    for(unsigned int p = 0;p < ModFiles.size();p++)
        ModFiles[p]->Close();
    return -1;
    }

EDID_Iterator Collection::LookupGMSTRecord(char *ModName, char *recordEDID, ModFile *&curModFile, GMSTRecord *&curRecord)
    {
    curRecord = NULL;
    curModFile = NULL;
    EDID_Range range = EDID_ModFile_Record.equal_range(recordEDID);
    for(; range.first != range.second; ++range.first)
        if(_stricmp(range.first->second.first->FileName, ModName) == 0)
            {
            curModFile = range.first->second.first;
            break;
            }
    if(curModFile == NULL)
        return EDID_ModFile_Record.end();
    curRecord = (GMSTRecord *)range.first->second.second;
    return range.first;
    }

void Collection::ResolveGrid(const float &posX, const float &posY, int &gridX, int &gridY)
    {
    gridX = (int)floor(posX / 4096.0);
    gridY = (int)floor(posY / 4096.0);
    return;
    }

unsigned int Collection::GetNumRecords(char *ModName, const unsigned int RecordType)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return (unsigned int)curModFile->GetNumRecords(RecordType);
    }

void Collection::GetRecordFormIDs(char *ModName, const unsigned int RecordType, unsigned int **RecordFIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    FormIDRecordRetriever retriever(RecordFIDs);
    curModFile->VisitTopRecords(RecordType, retriever);
    return;
    }

void Collection::GetRecordEditorIDs(char *ModName, const unsigned int RecordType, char **RecordEditorIDs)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    EditorIDRecordRetriever retriever(RecordEditorIDs);
    curModFile->VisitTopRecords(RecordType, retriever);
    return;
    }

unsigned int Collection::GetNumMods()
    {
    unsigned int count = (unsigned int)ModFiles.size();
    for(unsigned int p = 0;p < ModFiles.size();++p)
        {
        if(ModFiles[p]->Settings.IsDummy || ModFiles[p]->Settings.Scan || ModFiles[p]->Settings.Merge)
            --count;
        }
    return count;
    }

void Collection::GetMods(char **ModNames)
    {
    ModFile *curModFile = NULL;
    for(unsigned int p = 0;p < AllLoadOrder.size();++p)
        {
        curModFile = LookupModFile(AllLoadOrder[p]);
        if(!curModFile->Settings.IsDummy)
            ModNames[p] = AllLoadOrder[p];
        }
    return;
    }

char * Collection::GetModName(const unsigned int iIndex)
    {
    if(iIndex < AllLoadOrder.size())
        return AllLoadOrder[iIndex];
    return NULL;
    }

unsigned int Collection::SetRecordFormID(char *ModName, unsigned int recordFID, unsigned int FieldValue)
    {
    if(recordFID == FieldValue)
        return 0;
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    Record *destRecord = NULL;
    //If the recordFID is already in use, do nothing.
    LookupRecord(ModName, FieldValue, curModFile, destRecord);
    if(curModFile != NULL || destRecord != NULL)
        return 0;

    FID_Iterator it = LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL || it == FID_ModFile_Record.end())
        return 0;
    FID_ModFile_Record.erase(it);
    curRecord->formID = FieldValue;
    FormIDMasterUpdater checker(curModFile->FormIDHandler);
    checker.Accept(curRecord->formID);
    FID_ModFile_Record.insert(std::make_pair(curRecord->formID,std::make_pair(curModFile,curRecord)));
    return FieldValue;
    }

unsigned int Collection::ModIsFake(const unsigned int iIndex)
    {
    ModFile *curModFile = NULL;
    if(iIndex < AllLoadOrder.size())
        {
        curModFile = LookupModFile(AllLoadOrder[iIndex]);
        return curModFile->Settings.IsDummy;
        }
    return 1;
    }

unsigned int Collection::GetCorrectedFID(char *ModName, unsigned int recordObjectID)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return curModFile->FormIDHandler.AssignToMod(recordObjectID);
    }

unsigned int Collection::UpdateReferences(char *ModName, unsigned int origFormID, unsigned int newFormID)
    {
    if(origFormID == newFormID)
        return 0;
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    FormIDSwapper swapper(origFormID, newFormID, curModFile->FormIDHandler);
    RecordFormIDVisitor allSwapper(curModFile->FormIDHandler, swapper, true);

    //Commented out GRUPs don't contain any formIDs that could be updated.
    //curModFile->GMST.VisitRecords(allSwapper);
    //curModFile->GLOB.VisitRecords(allSwapper);
    //curModFile->CLAS.VisitRecords(allSwapper);
    curModFile->FACT.VisitRecords(allSwapper);
    //curModFile->HAIR.VisitRecords(allSwapper);
    //curModFile->EYES.VisitRecords(allSwapper);
    curModFile->RACE.VisitRecords(allSwapper);
    //curModFile->SOUN.VisitRecords(allSwapper);
    //curModFile->SKIL.VisitRecords(allSwapper);
    curModFile->MGEF.VisitRecords(allSwapper);
    curModFile->SCPT.VisitRecords(allSwapper);
    curModFile->LTEX.VisitRecords(allSwapper);
    curModFile->ENCH.VisitRecords(allSwapper);
    curModFile->SPEL.VisitRecords(allSwapper);
    curModFile->BSGN.VisitRecords(allSwapper);
    curModFile->ACTI.VisitRecords(allSwapper);
    curModFile->APPA.VisitRecords(allSwapper);
    curModFile->ARMO.VisitRecords(allSwapper);
    curModFile->BOOK.VisitRecords(allSwapper);
    curModFile->CLOT.VisitRecords(allSwapper);
    curModFile->CONT.VisitRecords(allSwapper);
    curModFile->DOOR.VisitRecords(allSwapper);
    curModFile->INGR.VisitRecords(allSwapper);
    curModFile->LIGH.VisitRecords(allSwapper);
    curModFile->MISC.VisitRecords(allSwapper);
    //curModFile->STAT.VisitRecords(allSwapper);
    //curModFile->GRAS.VisitRecords(allSwapper);
    //curModFile->TREE.VisitRecords(allSwapper);
    curModFile->FLOR.VisitRecords(allSwapper);
    curModFile->FURN.VisitRecords(allSwapper);
    curModFile->WEAP.VisitRecords(allSwapper);
    curModFile->AMMO.VisitRecords(allSwapper);
    curModFile->NPC_.VisitRecords(allSwapper);
    curModFile->CREA.VisitRecords(allSwapper);
    curModFile->LVLC.VisitRecords(allSwapper);
    curModFile->SLGM.VisitRecords(allSwapper);
    curModFile->KEYM.VisitRecords(allSwapper);
    curModFile->ALCH.VisitRecords(allSwapper);
    //curModFile->SBSP.VisitRecords(allSwapper);
    curModFile->SGST.VisitRecords(allSwapper);
    curModFile->LVLI.VisitRecords(allSwapper);
    curModFile->WTHR.VisitRecords(allSwapper);
    curModFile->CLMT.VisitRecords(allSwapper);
    curModFile->REGN.VisitRecords(allSwapper);
    curModFile->CELL.VisitRecords(allSwapper);
    curModFile->WRLD.VisitRecords(allSwapper);
    curModFile->DIAL.VisitRecords(allSwapper);
    curModFile->QUST.VisitRecords(allSwapper);
    curModFile->IDLE.VisitRecords(allSwapper);
    curModFile->PACK.VisitRecords(allSwapper);
    //curModFile->CSTY.VisitRecords(allSwapper);
    curModFile->LSCR.VisitRecords(allSwapper);
    curModFile->LVSP.VisitRecords(allSwapper);
    curModFile->ANIO.VisitRecords(allSwapper);
    curModFile->WATR.VisitRecords(allSwapper);
    //curModFile->EFSH.VisitRecords(allSwapper);

    return allSwapper.GetCount();
    }


unsigned int Collection::GetNumReferences(char *ModName, unsigned int recordFID, unsigned int referenceFormID)
    {
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;

    FormIDMatchCounter counter(referenceFormID);
    curRecord->VisitFormIDs(counter);
    return counter.GetCount();
    }

unsigned int Collection::UpdateReferences(char *ModName, unsigned int recordFID, unsigned int origFormID, unsigned int newFormID)
    {
    if(origFormID == newFormID)
        return 0;
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    FormIDSwapper swapper(origFormID, newFormID,curModFile->FormIDHandler);
    curRecord->VisitFormIDs(swapper);
    unsigned int count = swapper.GetCount();
    if(count)
        curRecord->recData = NULL;
    return count;
    }

int Collection::GetModIndex(const char *ModName)
    {
    if(ModName == NULL)
        return -1;
    static unsigned int lastModIndex_1 = 0;
    static unsigned int lastModIndex_2 = 0;
    if(_stricmp(ModName, AllLoadOrder[lastModIndex_1]) == 0)
        return lastModIndex_1;

    if(_stricmp(ModName, AllLoadOrder[lastModIndex_2]) == 0)
        {
        std::swap(lastModIndex_1, lastModIndex_2);
        return lastModIndex_1;
        }

    for(unsigned int x = 0; x < AllLoadOrder.size();++x)
        if(_stricmp(ModName, AllLoadOrder[x]) == 0)
            {
            lastModIndex_2 = lastModIndex_1;
            lastModIndex_1 = x;
            return lastModIndex_1;
            }
    return -1;
    }

int Collection::IsWinning(char *ModName, unsigned int recordFID, bool ignoreScanned)
    {
    int isWinning = 0;
    FID_Range range = FID_ModFile_Record.equal_range(recordFID);

    std::vector<ModFile *> sortedConflicts;
    sortedConflicts.reserve(300);  //Enough for the worst case of all 255 loaded mods having conflicts, plus some for imported mods
    for(; range.first != range.second; ++range.first)
        if(!(ignoreScanned && range.first->second.first->Settings.Scan))
            sortedConflicts.push_back(range.first->second.first);

    if(sortedConflicts.size())
        {
        //std::partial_sort(sortedConflicts.begin(), sortedConflicts.end(), sortLoad);
        //sortMods(sortedConflicts);
        std::_Insertion_sort(sortedConflicts.begin(), sortedConflicts.end(),compMod);
        //std::sort(sortedConflicts.begin(), sortedConflicts.end(), sortLoad);
        isWinning = _stricmp(sortedConflicts[sortedConflicts.size() - 1]->FileName, ModName) == 0;
        sortedConflicts.clear();
        }
    return isWinning;
    }

int Collection::IsWinning(char *ModName, char *recordEDID, bool ignoreScanned)
    {
    int isWinning = 0;
    EDID_Range range = EDID_ModFile_Record.equal_range(recordEDID);

    std::vector<ModFile *> sortedConflicts;
    sortedConflicts.reserve(300);  //Enough for the worst case of all 255 loaded mods having conflicts, plus some for imported mods
    for(; range.first != range.second; ++range.first)
        if(!(ignoreScanned && range.first->second.first->Settings.Scan))
            sortedConflicts.push_back(range.first->second.first);

    if(sortedConflicts.size())
        {
        //std::partial_sort(sortedConflicts.begin(), sortedConflicts.end(), sortLoad);
        //sortMods(sortedConflicts);
        std::_Insertion_sort(sortedConflicts.begin(), sortedConflicts.end(),compMod);
        //std::sort(sortedConflicts.begin(), sortedConflicts.end(), sortLoad);
        isWinning = _stricmp(sortedConflicts[sortedConflicts.size() - 1]->FileName, ModName) == 0;
        sortedConflicts.clear();
        }
    return isWinning;
    }

int Collection::GetNumFIDConflicts(unsigned int recordFID, bool ignoreScanned)
    {
    unsigned int count = (unsigned int)FID_ModFile_Record.count(recordFID);
    if(ignoreScanned)
        {
        FID_Iterator it = FID_ModFile_Record.find(recordFID);
        unsigned int scanned = 0;
        for(unsigned int x = 0; x < count;++it, ++x)
            if(it->second.first->Settings.Scan)
                ++scanned;
        count -= scanned;
        }
    return count;
    }

void Collection::GetFIDConflicts(unsigned int recordFID, bool ignoreScanned, char **ModNames)
    {
    FID_Range range = FID_ModFile_Record.equal_range(recordFID);

    std::vector<ModFile *> sortedConflicts;
    sortedConflicts.reserve(300);  //Enough for the worst case of all 255 loaded mods having conflicts, plus some for imported mods
    for(; range.first != range.second; ++range.first)
        if(!(ignoreScanned && range.first->second.first->Settings.Scan))
            sortedConflicts.push_back(range.first->second.first);
    //std::sort(sortedConflicts.begin(), sortedConflicts.end(), sortLoad);
    //sortMods(sortedConflicts);
    std::_Insertion_sort(sortedConflicts.begin(), sortedConflicts.end(),compMod);
    unsigned int x = 0;
    for(int y = (int)sortedConflicts.size() - 1; y >= 0; --y, ++x)
        ModNames[x] = sortedConflicts[y]->FileName;
    sortedConflicts.clear();
    }

int Collection::GetNumGMSTConflicts(char *recordEDID, bool ignoreScanned)
    {
    unsigned int count = (unsigned int)EDID_ModFile_Record.count(recordEDID);
    if(ignoreScanned)
        {
        EDID_Iterator it = EDID_ModFile_Record.find(recordEDID);
        unsigned int scanned = 0;
        for(unsigned int x = 0; x < count;++it, ++x)
            if(it->second.first->Settings.Scan)
                ++scanned;
        count -= scanned;
        }
    return count;
    }

void Collection::GetGMSTConflicts(char *recordEDID, bool ignoreScanned, char **ModNames)
    {
    EDID_Range range = EDID_ModFile_Record.equal_range(recordEDID);

    std::vector<ModFile *> sortedConflicts;
    sortedConflicts.reserve(300);  //Enough for the worst case of all 255 loaded mods having conflicts, plus some for imported mods
    for(; range.first != range.second; ++range.first)
        if(!(ignoreScanned && range.first->second.first->Settings.Scan))
            sortedConflicts.push_back(range.first->second.first);
    //std::sort(sortedConflicts.begin(), sortedConflicts.end(), sortLoad);
    //sortMods(sortedConflicts);
    std::_Insertion_sort(sortedConflicts.begin(), sortedConflicts.end(),compMod);
    unsigned int x = 0;
    for(int y = (int)sortedConflicts.size() - 1; y >= 0; --y, ++x)
        ModNames[x] = sortedConflicts[y]->FileName;
    sortedConflicts.clear();
    }

ModFile *Collection::LookupModFile(char *ModName)
    {
    if(ModName == NULL)
        return NULL;
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

int Collection::GetTES4FieldType(char *ModName, const unsigned int Field)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return UNKNOWN_FIELD;
    return curModFile->TES4.GetFieldType(Field);
    }

int Collection::GetGMSTFieldType(char *ModName, char *recordEDID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    GMSTRecord *curRecord = NULL;
    LookupGMSTRecord(ModName, recordEDID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return UNKNOWN_FIELD;
    return curRecord->GetFieldType(Field);
    }

int Collection::GetFIDFieldType(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return UNKNOWN_FIELD;
    return curRecord->GetFieldType(Field);
    }

int Collection::GetFIDListFieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return UNKNOWN_FIELD;
    return curRecord->GetListFieldType(subField, listField);
    }

int Collection::GetFIDListX2FieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return UNKNOWN_FIELD;
    return curRecord->GetListX2FieldType(subField, listField, listX2Field);
    }

int Collection::GetFIDListX3FieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return UNKNOWN_FIELD;
    return curRecord->GetListX3FieldType(subField, listField, listX2Field, listX3Field);
    }

unsigned int Collection::GetTES4FieldArraySize(char *ModName, const unsigned int Field)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return 0;
    return curModFile->TES4.GetFieldArraySize(Field);
    }

void Collection::GetTES4FieldArray(char *ModName, const unsigned int Field, void **FieldValues)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return;
    curModFile->TES4.GetFieldArray(Field, FieldValues);
    return;
    }

unsigned int Collection::GetFIDFieldArraySize(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetFieldArraySize(Field);
    }

unsigned int Collection::GetFIDListSize(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListSize(Field);
    }

unsigned int Collection::GetFIDListX2Size(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListX2Size(subField, listIndex, listField);
    }

unsigned int Collection::GetFIDListX3Size(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListX3Size(subField, listIndex, listField, listX2Index, listX2Field);
    }

unsigned int Collection::GetFIDListArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListArraySize(subField, listIndex, listField);
    }

unsigned int Collection::GetFIDListX2ArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListX2ArraySize(subField, listIndex, listField, listX2Index, listX2Field);
    }

unsigned int Collection::GetFIDListX3ArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return 0;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListX3ArraySize(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
    }

void Collection::GetFIDFieldArray(char *ModName, unsigned int recordFID, const unsigned int Field, void **FieldValues)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    curRecord->GetFieldArray(Field, FieldValues);
    return;
    }

void Collection::GetFIDListArray(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    curRecord->GetListArray(subField, listIndex, listField, FieldValues);
    return;
    }

void Collection::GetFIDListX2Array(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    curRecord->GetListX2Array(subField, listIndex, listField, listX2Index, listX2Field, FieldValues);
    return;
    }

void Collection::GetFIDListX3Array(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    curRecord->GetListX3Array(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValues);
    return;
    }

void * Collection::ReadTES4Field(char *ModName, const unsigned int Field)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return NULL;
    return curModFile->TES4.GetField(Field);
    }

void * Collection::ReadGMSTField(char *ModName, char *recordEDID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    GMSTRecord *curRecord = NULL;
    LookupGMSTRecord(ModName, recordEDID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return NULL;
    return curRecord->GetField(Field);
    }

void * Collection::ReadFIDField(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return NULL;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetField(Field);
    }

void * Collection::ReadFIDListField(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return NULL;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListField(subField, listIndex, listField);
    }

void * Collection::ReadFIDListX2Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return NULL;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListX2Field(subField, listIndex, listField, listX2Index, listX2Field);
    }

void * Collection::ReadFIDListX3Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return NULL;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->GetListX3Field(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
    }


int Collection::CreateFIDListElement(char *ModName, unsigned int recordFID, const unsigned int subField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->CreateListElement(subField);
    }

int Collection::CreateFIDListX2Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->CreateListX2Element(subField, listIndex, listField);
    }

int Collection::CreateFIDListX3Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->CreateListX3Element(subField, listIndex, listField, listX2Index, listX2Field);
    }

int Collection::DeleteFIDListElement(char *ModName, unsigned int recordFID, const unsigned int subField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->DeleteListElement(subField);
    }

int Collection::DeleteFIDListX2Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->DeleteListX2Element(subField, listIndex, listField);
    }

int Collection::DeleteFIDListX3Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->DeleteListX3Element(subField, listIndex, listField, listX2Index, listX2Field);
    }

int Collection::DeleteTES4Field(char *ModName, const unsigned int Field)
    {
    ModFile *curModFile = LookupModFile(ModName);
    if(curModFile == NULL)
        return -1;

    return curModFile->TES4.DeleteField(Field);
    }

int Collection::DeleteGMSTField(char *ModName, char *recordEDID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    GMSTRecord *curRecord = NULL;
    LookupGMSTRecord(ModName, recordEDID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    return curRecord->DeleteField(Field);
    }

int Collection::DeleteFIDField(char *ModName, unsigned int recordFID, const unsigned int Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->DeleteField(Field);
    }

int Collection::DeleteFIDListField(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->DeleteListField(subField, listIndex, listField);
    }

int Collection::DeleteFIDListX2Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->DeleteListX2Field(subField, listIndex, listField, listX2Index, listX2Field);
    }

int Collection::DeleteFIDListX3Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    LookupRecord(ModName, recordFID, curModFile, curRecord);
    if(curModFile == NULL || curRecord == NULL)
        return -1;
    RecordReader reader(curModFile->FormIDHandler);
    reader.Accept(*curRecord);
    return curRecord->DeleteListX3Field(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
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
