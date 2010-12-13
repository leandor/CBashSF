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
#include "Oblivion/TES4File.h"
#include <vector>
#include <map>
#include "Visitors.h"

class Collection
    {
    private:
        STRING ModsDir;
        bool IsLoaded;
        enum collectionType
            {
            eTES4,
            eFO3,
            eFNV,
            eUnknownCollection
            } CollectionType;

    public:
        std::vector<ModFile *> ModFiles;
        std::vector<ModFile *> LoadOrder255;
        std::vector<FormIDResolver *> Expanders;

        EditorID_Map EditorID_ModFile_Record;
        FormID_Map FormID_ModFile_Record;
        EditorID_Map ExtendedEditorID_ModFile_Record;
        FormID_Map ExtendedFormID_ModFile_Record;

        Collection(STRING const &ModsPath, UINT32 _CollectionType);
        ~Collection();

        SINT32 AddMod(STRING const &ModName, ModFlags &flags);
        bool IsModAdded(STRING const &ModName);
        SINT32 SaveMod(ModFile *curModFile, bool CloseCollection=false);

        SINT32 Load();
        SINT32 Unload();

        FormID_Iterator LookupRecord(ModFile *&curModFile, const FORMID &RecordFormID, Record *&curRecord);
        EditorID_Iterator LookupRecord(ModFile *&curModFile, STRING const &RecordEditorID, Record *&curRecord);

        UINT32 IsRecordWinning(ModFile *curModFile, const FORMID &RecordFormID, STRING const &RecordEditorID, const bool GetExtendedConflicts);
        UINT32 GetNumRecordConflicts(const FORMID &RecordFormID, STRING const &RecordEditorID, const bool GetExtendedConflicts);
        void   GetRecordConflicts(const FORMID &RecordFormID, STRING const &RecordEditorID, UINT32ARRAY ModIDs, const bool GetExtendedConflicts);

        UINT32 NextFreeExpandedFormID(ModFile *&curModFile, UINT32 depth = 0);
        UINT32 CreateRecord(ModFile *curModFile, const UINT32 &RecordType, FORMID RecordFormID, STRING const &RecordEditorID, const FORMID &ParentFormID, UINT32 CreateFlags);
        UINT32 CopyRecord(ModFile *curModFile, const FORMID &RecordFormID, STRING const &RecordEditorID, ModFile *DestModFile, FORMID DestParentFormID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, UINT32 CreateFlags);
        SINT32 DeleteRecord(ModFile *curModFile, const FORMID &RecordFormID, STRING const &RecordEditorID, const FORMID &ParentFormID);

        SINT32 SetRecordIDs(ModFile *curModFile, const FORMID &RecordFormID, STRING const &RecordEditorID, const FORMID &FormIDValue, STRING const &EditorIDValue);
    };