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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#pragma once
// Collection.h
#include "ModFile.h"
#include "Oblivion/TES4File.h"
#include "FalloutNewVegas/FNVFile.h"
#include <vector>
#include <map>
#include "Visitors.h"

//class SortedRecords
//    {
//    public:
//        UINT32 size;
//        Record ** records;
//
//        SortedRecords();
//        ~SortedRecords();
//
//	    void push_back(Record *&record);
//	    void erase(UINT32 &index);
//    };

//struct IndexedRecords
//    {
//    SortedRecords loadordered, extended;
//    };

//typedef std::map<FORMID, SortedRecords>   FormID_Map;
//typedef std::map<STRING, SortedRecords, sameStr> EditorID_Map;
//
//typedef FormID_Map::iterator FormID_Iterator;
//typedef EditorID_Map::iterator EditorID_Iterator;

class Collection
    {
    private:
        STRING ModsDir;
        bool IsLoaded;
        std::vector<Record *> sortedConflicts;

    public:
        whichGameTypes CollectionType;

        std::vector<ModFile *> ModFiles;
        std::vector<ModFile *> LoadOrder255;
        std::vector<FormIDResolver *> Expanders;

        EditorID_Map EditorID_ModFile_Record;
        FormID_Map FormID_ModFile_Record;

        EditorID_Map ExtendedEditorID_ModFile_Record;
        FormID_Map ExtendedFormID_ModFile_Record;

        boost::unordered_set<Record *> identical_records;
        boost::unordered_set<Record *> changed_records;
        std::vector<GenericOp *> closing_ops;

        Collection(STRING const &ModsPath, UINT32 _CollectionType);
        ~Collection();

        SINT32 AddMod(STRING const &_FileName, ModFlags &flags, bool IsPreloading=false);
        ModFile * IsModAdded(STRING const &ModName);
        SINT32 SaveMod(ModFile *&curModFile, SaveFlags &flags, STRING const DestinationName);

        SINT32 Load();
        void   UndeleteRecords(std::vector<std::pair<ModFile *, std::vector<Record *> > > &DeletedRecords);
        SINT32 Unload();

        FormID_Iterator LookupRecord(ModFile *&curModFile, const FORMID &RecordFormID, Record *&curRecord);
        EditorID_Iterator LookupRecord(ModFile *&curModFile, STRING const &RecordEditorID, Record *&curRecord);
        FormID_Iterator LookupWinningRecord(const FORMID &RecordFormID, ModFile *&WinningModFile, Record *&WinningRecord, const bool GetExtendedConflicts=false);
        EditorID_Iterator LookupWinningRecord(STRING const &RecordEditorID, ModFile *&WinningModFile, Record *&WinningRecord, const bool GetExtendedConflicts=false);

        UINT32 GetNumRecordConflicts(Record *&curRecord, const bool GetExtendedConflicts);
        SINT32 GetRecordConflicts(Record *&curRecord, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts);
        SINT32 GetRecordHistory(Record *&curRecord, RECORDIDARRAY RecordIDs);

        UINT32 NextFreeExpandedFormID(ModFile *&curModFile, UINT32 depth = 0);
        Record * CreateRecord(ModFile *&curModFile, const UINT32 &RecordType, FORMID RecordFormID, STRING const &RecordEditorID, const FORMID &ParentFormID, UINT32 CreateFlags);
        Record * CopyRecord(Record *&curRecord, ModFile *&DestModFile, const FORMID &DestParentFormID, FORMID DestRecordFormID, STRING const &DestRecordEditorID, UINT32 CreateFlags);
        SINT32 CleanModMasters(ModFile *curModFile);

        SINT32 SetIDFields(Record *&RecordID, FORMID FormID, STRING const &EditorID);
    };

class RecordReader : public RecordOp
    {
    private:
        FormIDResolver expander;
        std::vector<FormIDResolver *> &Expanders;

    public:
        RecordReader(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        RecordReader(Record *RecordID);
        RecordReader(ModFile *ModID);
        ~RecordReader();

        bool Accept(Record *&curRecord);
    };

class RecordDeindexer : public RecordOp
    {
    private:
        EditorID_Map &EditorID_ModFile_Record;
        FormID_Map &FormID_ModFile_Record;

    public:
        RecordDeindexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map);
        RecordDeindexer(Record *RecordID);
        RecordDeindexer(ModFile *ModID);
        ~RecordDeindexer();

        bool Accept(Record *&curRecord);
    };

class IdenticalToMasterRetriever : public RecordOp
    {
    private:
        EditorID_Map &EditorID_ModFile_Record;
        FormID_Map &FormID_ModFile_Record;
        const std::vector<ModFile *> &LoadOrder255;
        const UINT8 &MasterIndex;
        boost::unordered_set<Record *> &identical_records;
        std::vector<FormIDResolver *> &Expanders;

        RecordReader reader;

    public:
        IdenticalToMasterRetriever(ModFile *ModID);
        ~IdenticalToMasterRetriever();

        bool Accept(Record *&curRecord);
    };

class RecordFormIDSwapper : public RecordOp
    {
    private:
        FormIDSwapper swapper;
        RecordReader reader;

    public:
        RecordFormIDSwapper(const UINT32 &_FormIDToMatch, const UINT32 &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordFormIDSwapper();

        bool Accept(Record *&curRecord);
    };

class RecordFormIDMapper : public RecordOp
    {
    private:
        class FormIDMapper : public FormIDOp
            {
            private:
                std::map<FORMID, std::vector<Record *> > &formID_users;

            public:
                Record *curRecord;

                FormIDMapper(std::map<FORMID, std::vector<Record *> > &_formID_users);
                ~FormIDMapper();

                bool Accept(UINT32 &curFormID);
                bool AcceptMGEF(UINT32 &curMgefCode);
            } mapper;

        RecordReader reader;

    public:
        RecordFormIDMapper(std::map<FORMID, std::vector<Record *> > &_formID_users, FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordFormIDMapper();

        bool Accept(Record *&curRecord);
    };

class RecordMasterCollector : public RecordOp
    {
    private:
        RecordReader reader;

    public:
        class FormIDMasterCollector : public FormIDOp
            {
            public:
                UINT8 UsedTable[256];
                UINT8 (&CollapseTable)[256];

                FormIDMasterCollector(UINT8 (&CollapseTable)[256]);
                ~FormIDMasterCollector();

                bool Accept(UINT32 &curFormID);
                bool AcceptMGEF(UINT32 &curMgefCode);
            } collector;

        RecordMasterCollector(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordMasterCollector();

        bool Accept(Record *&curRecord);
    };

class RecordChanger : public RecordOp
    {
    private:
        RecordReader reader;

    public:
        RecordChanger(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordChanger();

        bool Accept(Record *&curRecord);
    };