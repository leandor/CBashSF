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
#include <map>

#ifndef NUMTHREADS
#define NUMTHREADS    boost::thread::hardware_concurrency()
#endif

struct sameStr
    {
    bool operator()( const char* s1, const char* s2 ) const
        {
        return _stricmp( s1, s2 ) < 0;
        }
    };

typedef std::multimap<unsigned int, std::pair<ModFile *, Record *> >   FID_Map;
typedef std::multimap<char *, std::pair<ModFile *, Record *>, sameStr> EDID_Map;

typedef FID_Map::iterator FID_Iterator;
typedef EDID_Map::iterator EDID_Iterator;

typedef std::pair<FID_Iterator, FID_Iterator> FID_Range;
typedef std::pair<EDID_Iterator, EDID_Iterator> EDID_Range;

class Collection
    {
    private:
        char *ModsDir;
        std::vector<ModFile *> ModFiles;
        std::vector<char *> LoadOrder255;
		std::vector<char *> AllLoadOrder;
        //std::vector<int> LoadRecordTypes;
        bool isLoaded;
    public:
        EDID_Map EDID_ModFile_Record;
        FID_Map FID_ModFile_Record;

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

        bool IsModAdded(const char *ModName);
        int AddMod(const char *ModName, ModFlags &settings);

        int IsEmpty(char *ModName);
        unsigned int GetNumNewRecordTypes(char *ModName);
        void GetNewRecordTypes(char *ModName, unsigned int const **RecordTypes);

        int CleanMasters(char *ModName);
        int SafeSaveMod(char *ModName, bool CloseMod=false);

        void IndexRecords(ModFile *curModFile, const bool &FullLoad);
        void IndexRecords(const bool &FullLoad);
        int Load(const bool &LoadMasters, const bool &FullLoad);
        unsigned int NextFreeExpandedFID(ModFile *curModFile, unsigned int depth = 0);
        int RemoveIndex(Record *curRecord, char *ModName);
        int LoadRecord(char *ModName, unsigned int recordFID);
        int UnloadRecord(char *ModName, unsigned int recordFID);
        int UnloadModFile(char *ModName);
        int UnloadAll();
        int Close();

        unsigned int CreateRecord(char *ModName, const unsigned int RecordType, const unsigned int ParentFID, unsigned int CreateFlags);
        unsigned int CopyRecord(char *ModName, unsigned int RecordFID, char *DestModName, unsigned int DestParentFID, unsigned int CreateFlags);
        unsigned int CreateGMSTRecord(char *ModName, char *recordEDID);
        unsigned int CopyGMSTRecord(char *ModName, char *srcRecordEDID, char *destModName);
        int DeleteRecord(char *ModName, unsigned int recordFID, unsigned int parentFID);
        int DeleteCELL(CELLRecord *curCell, char *ModName);
        int DeleteGMSTRecord(char *ModName, char *recordEDID);

        template <class T>
        FID_Iterator LookupRecord(char *ModName, const unsigned int &recordFID, ModFile *&curModFile, T *&curRecord)
            {
            curRecord = NULL;
            curModFile = NULL;

            FID_Range range = FID_ModFile_Record.equal_range(recordFID);
            for(; range.first != range.second; ++range.first)
                if(_stricmp(range.first->second.first->FileName, ModName) == 0)
                    {
                    curModFile = range.first->second.first;
                    break;
                    }

            if(curModFile == NULL)
                return FID_ModFile_Record.end();
            curRecord = (T *)range.first->second.second;
            return range.first;
            }
        EDID_Iterator LookupGMSTRecord(char *ModName, char *recordEDID, ModFile *&curModFile, GMSTRecord *&curRecord);

        void ResolveGrid(const float &posX, const float &posY, int &gridX, int &gridY);

        ModFile *LookupModFile(char *ModName);
        unsigned int SetRecordFormID(char *ModName, unsigned int recordFID, unsigned int FieldValue);
        unsigned int GetNumMods();
        char * GetModName(const unsigned int iIndex);
        unsigned int ModIsFake(const unsigned int iIndex);
        unsigned int GetCorrectedFID(char *ModName, unsigned int recordObjectID);
        unsigned int UpdateReferences(char *ModName, unsigned int origFormID, unsigned int newFormID);
        unsigned int GetNumReferences(char *ModName, unsigned int recordFID, unsigned int referenceFormID);
        unsigned int UpdateReferences(char *ModName, unsigned int recordFID, unsigned int origFormID, unsigned int newFormID);
        int GetModIndex(const char *ModName);

        int IsWinning(char *ModName, unsigned int recordFID, bool ignoreScanned);
        int IsWinning(char *ModName, char *recordEDID, bool ignoreScanned);

        int GetNumFIDConflicts(unsigned int recordFID, bool ignoreScanned);
        void GetFIDConflicts(unsigned int recordFID, bool ignoreScanned, char **ModNames);

        int GetNumGMSTConflicts(char *recordEDID, bool ignoreScanned);
        void GetGMSTConflicts(char *recordEDID, bool ignoreScanned, char **ModNames);

        unsigned int GetNumRecords(char *ModName, const unsigned int RecordType);
        void GetRecordFormIDs(char *ModName, const unsigned int RecordType, unsigned int **RecordFIDs);
        void GetRecordEditorIDs(char *ModName, const unsigned int RecordType, char **RecordEditorIDs);
        void GetMods(char **ModNames);

        //ADD DEFINITIONS HERE
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

        int CreateFIDListElement(char *ModName, unsigned int recordFID, const unsigned int subField);
        int CreateFIDListX2Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int CreateFIDListX3Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);

        int DeleteFIDListElement(char *ModName, unsigned int recordFID, const unsigned int subField);
        int DeleteFIDListX2Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int DeleteFIDListX3Element(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);

        int DeleteTES4Field(char *ModName, const unsigned int Field);
        int DeleteGMSTField(char *ModName, char *recordEDID, const unsigned int Field);
        int DeleteFIDField(char *ModName, unsigned int recordFID, const unsigned int Field);
        int DeleteFIDListField(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int DeleteFIDListX2Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        int DeleteFIDListX3Field(char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field);

        template<class T>
        void SetTES4Field(char *ModName, const unsigned int Field, T FieldValue, unsigned int nSize)
            {
            try
                {
                ModFile *curModFile = LookupModFile(ModName);
                if(curModFile == NULL)
                    return;

                curModFile->TES4.SetField(Field, FieldValue, nSize);
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curModFile->TES4.formID);
                curModFile->TES4.VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = LookupModFile(ModName);
                if(curModFile == NULL)
                    return;

                ((Record *)&curModFile->TES4)->SetField(Field, FieldValue);
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curModFile->TES4.formID);
                curModFile->TES4.VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                GMSTRecord *curRecord = NULL;
                LookupGMSTRecord(ModName, recordEDID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                ((Record *)curRecord)->SetField(Field, FieldValue);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(*curRecord);
                curRecord->SetField(Field, FieldValue, nSize);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(*curRecord);
                curRecord->SetField(Field, FieldValue);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(*curRecord);
                curRecord->SetListField(subField, listIndex, listField, FieldValue, nSize);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(*curRecord);
                curRecord->SetListField(subField, listIndex, listField, FieldValue);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(*curRecord);
                curRecord->SetListX2Field(subField, listIndex, listField, listX2Index, listX2Field, FieldValue, nSize);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(*curRecord);
                curRecord->SetListX2Field(subField, listIndex, listField, listX2Index, listX2Field, FieldValue);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(*curRecord);
                curRecord->SetListX3Field(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue, nSize);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(*curRecord);
                curRecord->SetListX3Field(subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field, FieldValue);
                curRecord->recData = NULL;
                FormIDMasterUpdater checker(curModFile->FormIDHandler);
                checker.Accept(curRecord->formID);
                curRecord->VisitFormIDs(checker);
                return;
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
