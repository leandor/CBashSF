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

typedef std::multimap<unsigned long, std::pair<ModFile *, Record *> >   FID_Map;
typedef std::multimap<char *, std::pair<ModFile *, Record *>, sameStr> EDID_Map;

typedef FID_Map::iterator FID_Iterator;
typedef EDID_Map::iterator EDID_Iterator;

typedef std::pair<FID_Iterator, FID_Iterator> FID_Range;
typedef std::pair<EDID_Iterator, EDID_Iterator> EDID_Range;

class RecordDeleter : public RecordOp
    {
    private:
        EDID_Map &EDID_ModFile_Record;
        FID_Map &FID_ModFile_Record;
        Record *RecordToDelete;
    public:
        RecordDeleter(Record *_RecordToDelete, EDID_Map &_EDID_ModFile_Record, FID_Map &_FID_ModFile_Record):RecordOp(),
            EDID_ModFile_Record(_EDID_ModFile_Record),
            FID_ModFile_Record(_FID_ModFile_Record),
            RecordToDelete(_RecordToDelete)
            {}
        bool Accept(Record **curRecord)
            {
            if(curRecord == NULL || (*curRecord) == NULL)
                return false;

            if(RecordToDelete == NULL || (*curRecord) == RecordToDelete)
                {
                //De-Index the record
                if((*curRecord)->IsKeyedByEditorID())
                    {
                    for(EDID_Range range = EDID_ModFile_Record.equal_range((char *)(*curRecord)->GetField(5)); range.first != range.second; ++range.first)
                        if(range.first->second.second == (*curRecord))
                            {
                            EDID_ModFile_Record.erase(range.first);
                            break;
                            }
                    }
                else
                    {
                    for(FID_Range range = FID_ModFile_Record.equal_range((*curRecord)->formID); range.first != range.second; ++range.first)
                        if(range.first->second.second == (*curRecord))
                            {
                            FID_ModFile_Record.erase(range.first);
                            break;
                            }
                    }
                if((*curRecord)->HasSubRecords())
                    {
                    RecordDeleter SubRecordDeleter(NULL, EDID_ModFile_Record, FID_ModFile_Record);
                    (*curRecord)->VisitSubRecords(NULL, SubRecordDeleter);
                    }
                //Delete the record
                delete (*curRecord);
                (*curRecord) = NULL;
                ++count;
                result = true;
                stop = RecordToDelete != NULL;
                return stop;
                }
            return false;
            }
    };

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
            for(unsigned long p = 0; p < ModFiles.size(); p++)
                delete ModFiles[p];
            }

        bool IsModAdded(const char *ModName);
        int AddMod(const char *ModName, ModFlags &settings);

        int IsEmpty(char *ModName);
        unsigned long GetNumNewRecordTypes(char *ModName);
        void GetNewRecordTypes(char *ModName, unsigned long const **RecordTypes);

        int CleanMasters(char *ModName);
        int SafeSaveMod(char *ModName, bool CloseMod=false);

        void IndexRecords(ModFile *curModFile, const bool &FullLoad);
        void IndexRecords(const bool &FullLoad);
        int Load(const bool &LoadMasters, const bool &FullLoad);
        unsigned long NextFreeExpandedFID(ModFile *curModFile, unsigned long depth = 0);
        int LoadRecord(char *ModName, unsigned long recordFID);
        int UnloadRecord(char *ModName, unsigned long recordFID);
        int UnloadModFile(char *ModName);
        int UnloadAll();
        int Close();

        unsigned long CreateRecord(char *ModName, const unsigned long RecordType, unsigned long RecordFID, char *RecordEditorID, const unsigned long ParentFID, unsigned long CreateFlags);
        unsigned long CopyRecord(char *ModName, unsigned long RecordFID, char *DestModName, unsigned long DestParentFID, unsigned long CreateFlags);

        int DeleteRecord(char *ModName, unsigned long RecordFID, char *RecordEditorID, unsigned long ParentFID);

        template <class T>
        FID_Iterator LookupRecord(char *ModName, const unsigned long &recordFID, ModFile *&curModFile, T *&curRecord)
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
        EDID_Iterator LookupRecordByEditorID(char *ModName, char *RecordEDID, ModFile *&curModFile, Record *&curRecord);

        void ResolveGrid(const float &posX, const float &posY, int &gridX, int &gridY);

        ModFile *LookupModFile(char *ModName);
        unsigned long SetRecordFormID(char *ModName, unsigned long recordFID, unsigned long FieldValue);
        unsigned long GetNumMods();
        char * GetModName(const unsigned long iIndex);
        unsigned long ModIsFake(const unsigned long iIndex);
        unsigned long GetCorrectedFID(char *ModName, unsigned long recordObjectID);
        unsigned long UpdateReferences(char *ModName, unsigned long origFormID, unsigned long newFormID);
        unsigned long GetNumReferences(char *ModName, unsigned long recordFID, unsigned long referenceFormID);
        unsigned long UpdateReferences(char *ModName, unsigned long recordFID, unsigned long origFormID, unsigned long newFormID);
        int GetModIndex(const char *ModName);

        int IsWinning(char *ModName, unsigned long recordFID, bool ignoreScanned);
        int IsWinning(char *ModName, char *recordEDID, bool ignoreScanned);

        int GetNumFIDConflicts(unsigned long recordFID, bool ignoreScanned);
        void GetFIDConflicts(unsigned long recordFID, bool ignoreScanned, char **ModNames);

        int GetNumGMSTConflicts(char *recordEDID, bool ignoreScanned);
        void GetGMSTConflicts(char *recordEDID, bool ignoreScanned, char **ModNames);

        unsigned long GetNumRecords(char *ModName, const unsigned long RecordType);
        void GetRecordFormIDs(char *ModName, const unsigned long RecordType, unsigned long **RecordFIDs);
        void GetRecordEditorIDs(char *ModName, const unsigned long RecordType, char **RecordEditorIDs);
        void GetMods(char **ModNames);

        //ADD DEFINITIONS HERE
        int GetTES4FieldType(char *ModName, const unsigned long Field);
        int GetGMSTFieldType(char *ModName, char *recordEDID, const unsigned long Field);
        int GetFIDFieldType(char *ModName, unsigned long recordFID, const unsigned long Field);
        int GetFIDListFieldType(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField);
        int GetFIDListX2FieldType(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField, const unsigned long listX2Field);
        int GetFIDListX3FieldType(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField, const unsigned long listX2Field, const unsigned long listX3Field);

        unsigned long GetFIDListSize(char *ModName, unsigned long recordFID, const unsigned long Field);
        unsigned long GetFIDListX2Size(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        unsigned long GetFIDListX3Size(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);

        unsigned long GetTES4FieldArraySize(char *ModName, const unsigned long Field);
        unsigned long GetFIDFieldArraySize(char *ModName, unsigned long recordFID, const unsigned long Field);
        unsigned long GetFIDListArraySize(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        unsigned long GetFIDListX2ArraySize(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
        unsigned long GetFIDListX3ArraySize(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field);

        void GetTES4FieldArray(char *ModName, const unsigned long Field, void **FieldValues);
        void GetFIDFieldArray(char *ModName, unsigned long recordFID, const unsigned long Field, void **FieldValues);
        void GetFIDListArray(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues);
        void GetFIDListX2Array(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, void **FieldValues);
        void GetFIDListX3Array(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, void **FieldValues);

        void * ReadTES4Field(char *ModName, const unsigned long Field);
        void * ReadGMSTField(char *ModName, char *recordEDID, const unsigned long Field);
        void * ReadFIDField(char *ModName, unsigned long recordFID, const unsigned long Field);
        void * ReadFIDListField(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void * ReadFIDListX2Field(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
        void * ReadFIDListX3Field(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field);

        int CreateFIDListElement(char *ModName, unsigned long recordFID, const unsigned long subField);
        int CreateFIDListX2Element(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        int CreateFIDListX3Element(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);

        int DeleteFIDListElement(char *ModName, unsigned long recordFID, const unsigned long subField);
        int DeleteFIDListX2Element(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        int DeleteFIDListX3Element(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);

        int DeleteTES4Field(char *ModName, const unsigned long Field);
        int DeleteGMSTField(char *ModName, char *recordEDID, const unsigned long Field);
        int DeleteFIDField(char *ModName, unsigned long recordFID, const unsigned long Field);
        int DeleteFIDListField(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        int DeleteFIDListX2Field(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
        int DeleteFIDListX3Field(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field);

        template<class T>
        void SetTES4Field(char *ModName, const unsigned long Field, T FieldValue, unsigned long nSize)
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
        void SetTES4Field(char *ModName, const unsigned long Field, T FieldValue)
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
        void SetGMSTField(char *ModName, char *recordEDID, const unsigned long Field, T FieldValue)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecordByEditorID(ModName, recordEDID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
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
        void SetFIDField(char *ModName, unsigned long recordFID, const unsigned long Field, T FieldValue, unsigned long nSize)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(&curRecord);
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
        void SetFIDField(char *ModName, unsigned long recordFID, const unsigned long Field, T FieldValue)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(&curRecord);
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
        void SetFIDListField(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, T FieldValue, unsigned long nSize)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(&curRecord);
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
        void SetFIDListField(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, T FieldValue)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(&curRecord);
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
        void SetFIDListX2Field(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, T FieldValue, unsigned long nSize)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(&curRecord);
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
        void SetFIDListX2Field(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, T FieldValue)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(&curRecord);
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
        void SetFIDListX3Field(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, T FieldValue, unsigned long nSize)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(&curRecord);
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
        void SetFIDListX3Field(char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, T FieldValue)
            {
            try
                {
                ModFile *curModFile = NULL;
                Record *curRecord = NULL;
                LookupRecord(ModName, recordFID, curModFile, curRecord);
                if(curModFile == NULL || curRecord == NULL)
                    return;
                RecordReader reader(curModFile->FormIDHandler);
                reader.Accept(&curRecord);
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
