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
#pragma once
// Collection.h
#include "ModFile.h"
#include <vector>
#include <list>
#include <map>

class Collection
    {
    private:
        char *ModsDir;
        std::vector<ModFile *> ModFiles;
        std::vector<char *> LoadOrder;
        //std::list<char *> LoadOrder;
        //std::vector<int> LoadRecordTypes;
        bool isLoaded;
    public:
        std::multimap<char *, std::pair<ModFile *, Record *>, sameStr> GMST_ModFile_Record;
        std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID> FID_ModFile_Record;

        Collection(const char *ModsPath):ModsDir(NULL), isLoaded(false)
            {
            ModsDir = new char[strlen(ModsPath)+1];
            strcpy_s(ModsDir, strlen(ModsPath)+1, ModsPath);
            }
        ~Collection()
            {
            delete []ModsDir;
            for(unsigned int p = 0; p < ModFiles.size(); p++)
                delete ModFiles[p];
            }

        int NewMod(const char *ModName);
        bool IsModAdded(const char *ModName);
        int AddMod(const char *ModName, bool CreateIfNotExist=false);
        int SafeSaveMod(char *ModName);
        int SafeSaveAllChangedMods();

        void IndexRecords(ModFile *curModFile);
        int Load(const bool &LoadMasters, const bool &FullLoad);
        unsigned int NextFreeExpandedFID(ModFile *curModFile);
        void CollapseFormIDs(char *ModName = NULL);
        void ExpandFormIDs(char *ModName = NULL);
        void ReindexFormIDs();
        int Close();

        template <class T>
        int LookupRecord(char *ModName, unsigned int &recordFID, ModFile *&curModFile, T *&curRecord)
            {
            std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;

            if(recordFID == 0)
                {curModFile = NULL; curRecord = NULL; return 0;}

            it = FID_ModFile_Record.find(&recordFID);
            if(it == FID_ModFile_Record.end())
                {curModFile = NULL; curRecord = NULL; return 0;}

            if(ModName == NULL)
                curModFile = it->second.first;
            else
                //curModFile = LookupModFile(ModName);
                {
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;++it, ++x)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        break;
                        }
                }
            if(curModFile == NULL)
                {curRecord = NULL; return 0;}
            curRecord = (T *)it->second.second;
            return 1;
            }
        int LookupGMSTRecord(char *ModName, char *recordEDID, ModFile *&curModFile, GMSTRecord *&curRecord);

        CELLRecord *LookupCELLParent(ModFile *&curModFile, CELLRecord *&curCELL);
        void ResolveGrid(const float &posX, const float &posY, int &gridX, int &gridY);

        ModFile *LookupModFile(char *ModName);
        char * GetModName(const unsigned int iIndex);
        int GetModIndex(const char *ModName);


        unsigned int GetNumMods();
        //ADD DEFINITIONS HERE
        unsigned int GetNumGMSTRecords(char *ModName);
        unsigned int GetNumGLOBRecords(char *ModName);
        unsigned int GetNumCLASRecords(char *ModName);
        unsigned int GetNumFACTRecords(char *ModName);
        unsigned int GetNumHAIRRecords(char *ModName);
        unsigned int GetNumEYESRecords(char *ModName);
        unsigned int GetNumRACERecords(char *ModName);
        unsigned int GetNumSOUNRecords(char *ModName);
        unsigned int GetNumSKILRecords(char *ModName);
        unsigned int GetNumMGEFRecords(char *ModName);
        unsigned int GetNumSCPTRecords(char *ModName);
        unsigned int GetNumLTEXRecords(char *ModName);
        unsigned int GetNumENCHRecords(char *ModName);
        unsigned int GetNumSPELRecords(char *ModName);
        unsigned int GetNumBSGNRecords(char *ModName);
        unsigned int GetNumACTIRecords(char *ModName);
        unsigned int GetNumAPPARecords(char *ModName);
        unsigned int GetNumARMORecords(char *ModName);
        unsigned int GetNumBOOKRecords(char *ModName);
        unsigned int GetNumCLOTRecords(char *ModName);
        unsigned int GetNumCONTRecords(char *ModName);
        unsigned int GetNumDOORRecords(char *ModName);
        unsigned int GetNumINGRRecords(char *ModName);
        unsigned int GetNumLIGHRecords(char *ModName);
        unsigned int GetNumMISCRecords(char *ModName);
        unsigned int GetNumSTATRecords(char *ModName);
        unsigned int GetNumGRASRecords(char *ModName);
        unsigned int GetNumTREERecords(char *ModName);
        unsigned int GetNumFLORRecords(char *ModName);
        unsigned int GetNumFURNRecords(char *ModName);
        unsigned int GetNumWEAPRecords(char *ModName);
        unsigned int GetNumAMMORecords(char *ModName);
        unsigned int GetNumNPC_Records(char *ModName);
        unsigned int GetNumCREARecords(char *ModName);
        unsigned int GetNumLVLCRecords(char *ModName);
        unsigned int GetNumSLGMRecords(char *ModName);
        unsigned int GetNumKEYMRecords(char *ModName);
        unsigned int GetNumALCHRecords(char *ModName);
        unsigned int GetNumSBSPRecords(char *ModName);
        unsigned int GetNumSGSTRecords(char *ModName);
        unsigned int GetNumLVLIRecords(char *ModName);
        unsigned int GetNumWTHRRecords(char *ModName);
        unsigned int GetNumCLMTRecords(char *ModName);
        unsigned int GetNumREGNRecords(char *ModName);
        unsigned int GetNumCELLRecords(char *ModName);
        unsigned int GetNumACHRRecords(char *ModName, unsigned int parentFID);
        unsigned int GetNumACRERecords(char *ModName, unsigned int parentFID);
        unsigned int GetNumREFRRecords(char *ModName, unsigned int parentFID);
        unsigned int GetNumWRLDRecords(char *ModName);
        unsigned int GetNumDIALRecords(char *ModName);
        unsigned int GetNumQUSTRecords(char *ModName);
        unsigned int GetNumIDLERecords(char *ModName);
        unsigned int GetNumPACKRecords(char *ModName);
        unsigned int GetNumCSTYRecords(char *ModName);
        unsigned int GetNumLSCRRecords(char *ModName);
        unsigned int GetNumLVSPRecords(char *ModName);
        unsigned int GetNumANIORecords(char *ModName);
        unsigned int GetNumWATRRecords(char *ModName);
        unsigned int GetNumEFSHRecords(char *ModName);

        void GetMods(char **ModNames);

        //ADD DEFINITIONS HERE
        void GetGMSTRecords(char *ModName, char **RecordEIDs);
        void GetGLOBRecords(char *ModName, unsigned int **RecordFIDs);
        void GetCLASRecords(char *ModName, unsigned int **RecordFIDs);
        void GetFACTRecords(char *ModName, unsigned int **RecordFIDs);
        void GetHAIRRecords(char *ModName, unsigned int **RecordFIDs);
        void GetEYESRecords(char *ModName, unsigned int **RecordFIDs);
        void GetRACERecords(char *ModName, unsigned int **RecordFIDs);
        void GetSOUNRecords(char *ModName, unsigned int **RecordFIDs);
        void GetSKILRecords(char *ModName, unsigned int **RecordFIDs);
        void GetMGEFRecords(char *ModName, unsigned int **RecordFIDs);
        void GetSCPTRecords(char *ModName, unsigned int **RecordFIDs);
        void GetLTEXRecords(char *ModName, unsigned int **RecordFIDs);
        void GetENCHRecords(char *ModName, unsigned int **RecordFIDs);
        void GetSPELRecords(char *ModName, unsigned int **RecordFIDs);
        void GetBSGNRecords(char *ModName, unsigned int **RecordFIDs);
        void GetACTIRecords(char *ModName, unsigned int **RecordFIDs);
        void GetAPPARecords(char *ModName, unsigned int **RecordFIDs);
        void GetARMORecords(char *ModName, unsigned int **RecordFIDs);
        void GetBOOKRecords(char *ModName, unsigned int **RecordFIDs);
        void GetCLOTRecords(char *ModName, unsigned int **RecordFIDs);
        void GetCONTRecords(char *ModName, unsigned int **RecordFIDs);
        void GetDOORRecords(char *ModName, unsigned int **RecordFIDs);
        void GetINGRRecords(char *ModName, unsigned int **RecordFIDs);
        void GetLIGHRecords(char *ModName, unsigned int **RecordFIDs);
        void GetMISCRecords(char *ModName, unsigned int **RecordFIDs);
        void GetSTATRecords(char *ModName, unsigned int **RecordFIDs);
        void GetGRASRecords(char *ModName, unsigned int **RecordFIDs);
        void GetTREERecords(char *ModName, unsigned int **RecordFIDs);
        void GetFLORRecords(char *ModName, unsigned int **RecordFIDs);
        void GetFURNRecords(char *ModName, unsigned int **RecordFIDs);
        void GetWEAPRecords(char *ModName, unsigned int **RecordFIDs);
        void GetAMMORecords(char *ModName, unsigned int **RecordFIDs);
        void GetNPC_Records(char *ModName, unsigned int **RecordFIDs);
        void GetCREARecords(char *ModName, unsigned int **RecordFIDs);
        void GetLVLCRecords(char *ModName, unsigned int **RecordFIDs);
        void GetSLGMRecords(char *ModName, unsigned int **RecordFIDs);
        void GetKEYMRecords(char *ModName, unsigned int **RecordFIDs);
        void GetALCHRecords(char *ModName, unsigned int **RecordFIDs);
        void GetSBSPRecords(char *ModName, unsigned int **RecordFIDs);
        void GetSGSTRecords(char *ModName, unsigned int **RecordFIDs);
        void GetLVLIRecords(char *ModName, unsigned int **RecordFIDs);
        void GetWTHRRecords(char *ModName, unsigned int **RecordFIDs);
        void GetCLMTRecords(char *ModName, unsigned int **RecordFIDs);
        void GetREGNRecords(char *ModName, unsigned int **RecordFIDs);
        void GetCELLRecords(char *ModName, unsigned int **RecordFIDs);
        void GetACHRRecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs);
        void GetACRERecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs);
        void GetREFRRecords(char *ModName, unsigned int parentFID, unsigned int **RecordFIDs);
        void GetWRLDRecords(char *ModName, unsigned int **RecordFIDs);
        void GetDIALRecords(char *ModName, unsigned int **RecordFIDs);
        void GetQUSTRecords(char *ModName, unsigned int **RecordFIDs);
        void GetIDLERecords(char *ModName, unsigned int **RecordFIDs);
        void GetPACKRecords(char *ModName, unsigned int **RecordFIDs);
        void GetCSTYRecords(char *ModName, unsigned int **RecordFIDs);
        void GetLSCRRecords(char *ModName, unsigned int **RecordFIDs);
        void GetLVSPRecords(char *ModName, unsigned int **RecordFIDs);
        void GetANIORecords(char *ModName, unsigned int **RecordFIDs);
        void GetWATRRecords(char *ModName, unsigned int **RecordFIDs);
        void GetEFSHRecords(char *ModName, unsigned int **RecordFIDs);
        int GetChangedMods();

        int GetTES4FieldType(char *ModName, const unsigned int Field);
        int GetGMSTFieldType(char *ModName, char *recordEDID, const unsigned int Field);
        int GetFIDFieldType(char *ModName, unsigned int recordFID, const unsigned int Field);
        int GetFIDListFieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField);
        int GetFIDListX2FieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field);
        int GetFIDListX3FieldType(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field);

        unsigned int GetFIDListSize(char *ModName, unsigned int recordFID, const unsigned int Field);
        unsigned int GetFIDListX2Size(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetFIDListX3Size(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);

        unsigned int GetTES4FieldArraySize(char *ModName, const unsigned int Field);
        unsigned int GetFIDFieldArraySize(char *ModName, unsigned int recordFID, const unsigned int Field);
        unsigned int GetFIDListArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetFIDListX2ArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        unsigned int GetFIDListX3ArraySize(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field);

        void GetTES4FieldArray(char *ModName, const unsigned int Field, void **FieldValues);
        void GetFIDFieldArray(char *ModName, unsigned int recordFID, const unsigned int Field, void **FieldValues);
        void GetFIDListArray(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void GetFIDListX2Array(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues);
        void GetFIDListX3Array(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues);

        void * ReadTES4Field(char *ModName, const unsigned int Field);
        void * ReadGMSTField(char *ModName, char *recordEDID, const unsigned int Field);
        void * ReadFIDField(char *ModName, unsigned int recordFID, const unsigned int Field);
        void * ReadFIDListField(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void * ReadFIDListX2Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        void * ReadFIDListX3Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field);

        unsigned int CreateGMSTRecord(char *ModName, char *recordEDID);
        unsigned int CopyGMSTRecord(char *ModName, char *srcRecordEDID, char *destModName);
        //ADD
        unsigned int CreateGLOBRecord(char *ModName);
        unsigned int CreateCLASRecord(char *ModName);
        unsigned int CreateFACTRecord(char *ModName);
        unsigned int CreateHAIRRecord(char *ModName);
        unsigned int CreateEYESRecord(char *ModName);
        unsigned int CreateRACERecord(char *ModName);
        unsigned int CreateSOUNRecord(char *ModName);
        unsigned int CreateSKILRecord(char *ModName);
        unsigned int CreateMGEFRecord(char *ModName);
        unsigned int CreateSCPTRecord(char *ModName);
        unsigned int CreateLTEXRecord(char *ModName);
        unsigned int CreateENCHRecord(char *ModName);
        unsigned int CreateSPELRecord(char *ModName);
        unsigned int CreateBSGNRecord(char *ModName);
        unsigned int CreateACTIRecord(char *ModName);
        unsigned int CreateAPPARecord(char *ModName);
        unsigned int CreateARMORecord(char *ModName);
        unsigned int CreateBOOKRecord(char *ModName);
        unsigned int CreateCLOTRecord(char *ModName);
        unsigned int CreateCONTRecord(char *ModName);
        unsigned int CreateDOORRecord(char *ModName);
        unsigned int CreateINGRRecord(char *ModName);
        unsigned int CreateLIGHRecord(char *ModName);
        unsigned int CreateMISCRecord(char *ModName);
        unsigned int CreateSTATRecord(char *ModName);
        unsigned int CreateGRASRecord(char *ModName);
        unsigned int CreateTREERecord(char *ModName);
        unsigned int CreateFLORRecord(char *ModName);
        unsigned int CreateFURNRecord(char *ModName);
        unsigned int CreateWEAPRecord(char *ModName);
        unsigned int CreateAMMORecord(char *ModName);
        unsigned int CreateNPC_Record(char *ModName);
        unsigned int CreateCREARecord(char *ModName);
        unsigned int CreateLVLCRecord(char *ModName);
        unsigned int CreateSLGMRecord(char *ModName);
        unsigned int CreateKEYMRecord(char *ModName);
        unsigned int CreateALCHRecord(char *ModName);
        unsigned int CreateSBSPRecord(char *ModName);
        unsigned int CreateSGSTRecord(char *ModName);
        unsigned int CreateLVLIRecord(char *ModName);
        unsigned int CreateWTHRRecord(char *ModName);
        unsigned int CreateCLMTRecord(char *ModName);
        unsigned int CreateREGNRecord(char *ModName);
        unsigned int CreateCELLRecord(char *ModName, unsigned int parentFID);
        unsigned int CreateACHRRecord(char *ModName, unsigned int parentFID);
        unsigned int CreateACRERecord(char *ModName, unsigned int parentFID);
        unsigned int CreateREFRRecord(char *ModName, unsigned int parentFID);
        unsigned int CreatePGRDRecord(char *ModName, unsigned int parentFID);
        unsigned int CreateLANDRecord(char *ModName, unsigned int parentFID);
        unsigned int CreateWRLDRecord(char *ModName);
        unsigned int CreateROADRecord(char *ModName, unsigned int parentFID);
        unsigned int CreateDIALRecord(char *ModName);
        unsigned int CreateINFORecord(char *ModName, unsigned int parentFID);
        unsigned int CreateQUSTRecord(char *ModName);
        unsigned int CreateIDLERecord(char *ModName);
        unsigned int CreatePACKRecord(char *ModName);
        unsigned int CreateCSTYRecord(char *ModName);
        unsigned int CreateLSCRRecord(char *ModName);
        unsigned int CreateLVSPRecord(char *ModName);
        unsigned int CreateANIORecord(char *ModName);
        unsigned int CreateWATRRecord(char *ModName);
        unsigned int CreateEFSHRecord(char *ModName);

        //ADD
        unsigned int CopyFIDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyGLOBRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyCLASRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyFACTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyHAIRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyEYESRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyRACERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopySOUNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopySKILRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyMGEFRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopySCPTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyLTEXRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyENCHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopySPELRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyBSGNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyACTIRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyAPPARecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyARMORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyBOOKRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyCLOTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyCONTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyDOORRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyINGRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyLIGHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyMISCRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopySTATRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyGRASRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyTREERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyFLORRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyFURNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyWEAPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyAMMORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyNPC_Record(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyCREARecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyLVLCRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopySLGMRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyKEYMRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyALCHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopySBSPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopySGSTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyLVLIRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyWTHRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyCLMTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyREGNRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyCELLRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
        unsigned int CopyACHRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
        unsigned int CopyACRERecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
        unsigned int CopyREFRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
        unsigned int CopyPGRDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
        unsigned int CopyWRLDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyROADRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
        unsigned int CopyLANDRecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
        unsigned int CopyDIALRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyINFORecord(char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
        unsigned int CopyQUSTRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyIDLERecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyPACKRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyCSTYRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyLSCRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyLVSPRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyANIORecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyWATRRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
        unsigned int CopyEFSHRecord(char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);

        int CreateFIDListElement(char *ModName, unsigned int recordFID, const unsigned int subField);
        int CreateFIDListX2Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int CreateFIDListX3Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);

        int DeleteFIDListElement(char *ModName, unsigned int recordFID, const unsigned int subField);
        int DeleteFIDListX2Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int DeleteFIDListX3Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);

        template<class T>
        void SetTES4Field(char *ModName, const unsigned int Field, T FieldValue, unsigned int nSize)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                for(unsigned int p = 0;p < ModFiles.size();p++)
                    if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                        {
                        curModFile = ModFiles[p];
                        curRecord = &curModFile->TES4;
                        curRecord->SetField(curModFile->FormIDHandler, Field, FieldValue, nSize);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetTES4Field(char *ModName, const unsigned int Field, T FieldValue)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                for(unsigned int p = 0;p < ModFiles.size();p++)
                    if(_stricmp(ModFiles[p]->FileName, ModName) == 0)
                        {
                        curModFile = ModFiles[p];
                        curRecord = &curModFile->TES4;
                        curRecord->SetField(curModFile->FormIDHandler, Field, FieldValue);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetGMSTField(char *ModName, char *recordEDID, const unsigned int Field, T FieldValue)
            {
            try
                {
                std::multimap<char*,std::pair<ModFile *, Record *>, sameStr>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = GMST_ModFile_Record.find(recordEDID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != GMST_ModFile_Record.end())
                        it->second.second->SetField(curModFile->FormIDHandler, Field, FieldValue);
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)GMST_ModFile_Record.count(recordEDID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        it->second.second->SetField(curModFile->FormIDHandler, Field, FieldValue);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetFIDField(char *ModName, unsigned int recordFID, const unsigned int Field, T FieldValue, unsigned int nSize)
            {
            try
                {
                std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = FID_ModFile_Record.find(&recordFID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != FID_ModFile_Record.end())
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetField(curModFile->FormIDHandler, Field, FieldValue, nSize);
                        }
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetField(curModFile->FormIDHandler, Field, FieldValue, nSize);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetFIDField(char *ModName, unsigned int recordFID, const unsigned int Field, T FieldValue)
            {
            try
                {
                std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = FID_ModFile_Record.find(&recordFID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != FID_ModFile_Record.end())
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetField(curModFile->FormIDHandler, Field, FieldValue);
                        }
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetField(curModFile->FormIDHandler, Field, FieldValue);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetFIDListField(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, T FieldValue, unsigned int nSize)
            {
            try
                {
                std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = FID_ModFile_Record.find(&recordFID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != FID_ModFile_Record.end())
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListField(curModFile->FormIDHandler, subField, listIndex, listField, FieldValue, nSize);
                        }
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListField(curModFile->FormIDHandler, subField, listIndex, listField, FieldValue, nSize);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetFIDListField(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, T FieldValue)
            {
            try
                {
                std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = FID_ModFile_Record.find(&recordFID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != FID_ModFile_Record.end())
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListField(curModFile->FormIDHandler, subField, listIndex, listField, FieldValue);
                        }
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListField(curModFile->FormIDHandler, subField, listIndex, listField, FieldValue);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetFIDListX2Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field, T FieldValue, unsigned int nSize)
            {
            try
                {
                std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = FID_ModFile_Record.find(&recordFID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != FID_ModFile_Record.end())
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListX2Field(curModFile->FormIDHandler, subField, listIndex, listField, listX2Index, listX2Field, FieldValue, nSize);
                        }
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListX2Field(curModFile->FormIDHandler, subField, listIndex, listField, listX2Index, listX2Field, FieldValue, nSize);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetFIDListX2Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field, T FieldValue)
            {
            try
                {
                std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = FID_ModFile_Record.find(&recordFID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != FID_ModFile_Record.end())
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListX2Field(curModFile->FormIDHandler, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
                        }
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListX2Field(curModFile->FormIDHandler, subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetFIDListX3Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field, const unsigned int listX3Index, const unsigned int listX3Field, T FieldValue, unsigned int nSize)
            {
            try
                {
                std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = FID_ModFile_Record.find(&recordFID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != FID_ModFile_Record.end())
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListX3Field(curModFile->FormIDHandler, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue, nSize);
                        }
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListX3Field(curModFile->FormIDHandler, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue, nSize);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        template<class T>
        void SetFIDListX3Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field, const unsigned int listX3Index, const unsigned int listX3Field, T FieldValue)
            {
            try
                {
                std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                it = FID_ModFile_Record.find(&recordFID);
                //Updating whichever value is winning.
                if(ModName == NULL)
                    {
                    if(it != FID_ModFile_Record.end())
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListX3Field(curModFile->FormIDHandler, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
                        }
                    return;
                    }
                //Else, update a specific mod's value.
                unsigned int count = (unsigned int)FID_ModFile_Record.count(&recordFID);
                for(unsigned int x = 0; x < count;it++, x++)
                    if(_stricmp(it->second.first->FileName, ModName) == 0 )
                        {
                        curModFile = it->second.first;
                        curRecord = it->second.second;
                        curRecord->Read(curModFile->fileBuffer, curModFile->FormIDHandler);
                        curRecord->SetListX3Field(curModFile->FormIDHandler, subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
                        return;
                        }
                }
            catch(...)
                {
                throw;
                }
            return;
            }

        #ifdef _DEBUG
        void Debug(int debugLevel, bool AllRecords);
        #endif
    };

class Iterator
    {
    protected:
        unsigned int recordType;
        std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator it;
        std::multimap<FormID, std::pair<ModFile *, Record *>, sortFormID>::iterator end;
    public:
        Iterator(Collection *nCollection, unsigned int recType):recordType(recType), it(nCollection->FID_ModFile_Record.begin()), end(nCollection->FID_ModFile_Record.end()) {}
        ~Iterator() {}
        long long IncrementIterator()
            {
            unsigned int formID;
            for(;it != end;it++)
                if(it->second.second->GetType() == recordType)
                    {
                    formID = it->second.second->formID;
                    it++;
                    return formID;
                    }
            return -1;
            }
    };
