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
//        ModFile ** mods;
//        Record ** records;
//
//        SortedRecords();
//        ~SortedRecords();
//
//	    void push_back(ModFile *&mod, Record *&record);
//	    void erase(UINT32 &index);
//    };

//struct IndexedRecords
//    {
//    SortedRecords loadordered, extended;
//    };

//typedef std::map<UINT32, SortedRecords>   FormID_Map;
//typedef std::map<STRING, SortedRecords, sameStr> EditorID_Map;
//
//typedef FormID_Map::iterator FormID_Iterator;
//typedef EditorID_Map::iterator EditorID_Iterator;

class Collection
    {
    private:
        STRING ModsDir;
        bool IsLoaded;

        whichGameTypes CollectionType;
    public:
        std::vector<ModFile *> ModFiles;
        std::vector<ModFile *> LoadOrder255;
        std::vector<FormIDResolver *> Expanders;

        EditorID_Map EditorID_ModFile_Record;
        FormID_Map FormID_ModFile_Record;

        EditorID_Map ExtendedEditorID_ModFile_Record;
        FormID_Map ExtendedFormID_ModFile_Record;

        boost::unordered_set<Record *> identical_records;

        Collection(STRING const &ModsPath, UINT32 _CollectionType);
        ~Collection();

        SINT32 AddMod(STRING const &_FileName, ModFlags &flags, bool IsPreloading=false);
        bool IsModAdded(STRING const &ModName);
        SINT32 SaveMod(ModFile *&curModFile, bool CloseCollection=false);

        SINT32 Load();
        SINT32 Unload();

        FormID_Iterator LookupRecord(ModFile *&curModFile, const FORMID &RecordFormID, Record *&curRecord);
        EditorID_Iterator LookupRecord(ModFile *&curModFile, STRING const &RecordEditorID, Record *&curRecord);

        UINT32 IsRecordWinning(ModFile *&curModFile, Record *&curRecord, const bool GetExtendedConflicts);
        UINT32 GetNumRecordConflicts(Record *&curRecord, const bool GetExtendedConflicts);
        SINT32 GetRecordConflicts(Record *&curRecord, MODIDARRAY ModIDs, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts);
        SINT32 GetRecordHistory(ModFile *&curModFile, Record *&curRecord, MODIDARRAY ModIDs, RECORDIDARRAY RecordIDs);

        UINT32 NextFreeExpandedFormID(ModFile *&curModFile, UINT32 depth = 0);
        Record * CreateRecord(ModFile *&curModFile, const UINT32 &RecordType, FORMID RecordFormID, STRING const &RecordEditorID, const FORMID &ParentFormID, UINT32 CreateFlags);
        Record * CopyRecord(ModFile *&curModFile, Record *&curRecord, ModFile *&DestModFile, const FORMID &DestParentFormID, FORMID DestRecordFormID, STRING const &DestRecordEditorID, UINT32 CreateFlags);

        SINT32 SetIDFields(ModFile *&curModFile, Record *&RecordID, FORMID FormID, STRING const &EditorID);
    };

//
//class RecordIndexer : public RecordOp
//    {
//    private:
//        EditorID_Map &EditorID_ModFile_Record;
//        FormID_Map &FormID_ModFile_Record;
//        ModFile *curModFile;
//        //bool IsExtended;
//
//    public:
//        RecordIndexer(ModFile *_curModFile, EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map);
//        RecordIndexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map);
//        ~RecordIndexer();
//
//        bool Accept(Record *&curRecord);
//
//        void SetModFile(ModFile *_curModFile);
//        //void SetIsExtended(bool UseExtended);
//    };