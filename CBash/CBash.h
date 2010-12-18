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
// CBash.h
//#define _UNICODE
#include "MacroDefinitions.h"

//Exported Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Version info functions
EXPORT_FUNC UINT32 GetVersionMajor();
EXPORT_FUNC UINT32 GetVersionMinor();
EXPORT_FUNC UINT32 GetVersionRevision();
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Logging action functions
#ifdef CBASH_USE_LOGGING
    EXPORT_FUNC SINT32 SetLogging(const UINT32 CollectionID, SINT32 (*_LoggingCallback)(const STRING), UINT32 LoggingLevel, UINT32 LoggingFlags);
#endif
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Collection action functions
EXPORT_FUNC SINT32 CreateCollection(STRING const ModsPath, const UINT32 CollectionType);
EXPORT_FUNC SINT32 DeleteCollection(const UINT32 CollectionID);
EXPORT_FUNC SINT32 LoadCollection(const UINT32 CollectionID);
EXPORT_FUNC SINT32 UnloadCollection(const UINT32 CollectionID);
EXPORT_FUNC SINT32 DeleteAllCollections();
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Mod action functions
EXPORT_FUNC SINT32 AddMod(const UINT32 CollectionID, STRING const ModName, const UINT32 ModFlagsField);
EXPORT_FUNC SINT32 LoadMod(const UINT32 CollectionID, const UINT32 ModID);
EXPORT_FUNC SINT32 UnloadMod(const UINT32 CollectionID, const UINT32 ModID);
EXPORT_FUNC SINT32 CleanModMasters(const UINT32 CollectionID, const UINT32 ModID);
EXPORT_FUNC SINT32 SaveMod(const UINT32 CollectionID, const UINT32 ModID, const bool CloseCollection);
////////////////////////////////////////////////////////////////////////
//Mod info functions
EXPORT_FUNC SINT32 GetNumMods(const UINT32 CollectionID);
EXPORT_FUNC SINT32 GetModIDs(const UINT32 CollectionID, UINT32ARRAY ModIDs);
EXPORT_FUNC STRING GetModNameByID(const UINT32 CollectionID, const UINT32 ModID);
EXPORT_FUNC STRING GetModNameByLoadOrder(const UINT32 CollectionID, const UINT32 ModIndex);
EXPORT_FUNC SINT32 GetModIDByName(const UINT32 CollectionID, STRING const ModName);
EXPORT_FUNC SINT32 GetModIDByLoadOrder(const UINT32 CollectionID, const UINT32 ModIndex);
EXPORT_FUNC SINT32 GetModLoadOrderByName(const UINT32 CollectionID, STRING const ModName);
EXPORT_FUNC SINT32 GetModLoadOrderByID(const UINT32 CollectionID, const UINT32 ModID);
EXPORT_FUNC UINT32 IsModEmpty(const UINT32 CollectionID, const UINT32 ModID);
EXPORT_FUNC SINT32 GetModNumTypes(const UINT32 CollectionID, const UINT32 ModID);
EXPORT_FUNC void   GetModTypes(const UINT32 CollectionID, const UINT32 ModID, UINT32ARRAY RecordTypes);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Record action functions
EXPORT_FUNC UINT32 CreateRecord(const UINT32 CollectionID, const UINT32 ModID, const UINT32 RecordType, const FORMID RecordFormID, STRING const RecordEditorID, const FORMID ParentFormID, const UINT32 CreateFlags);
EXPORT_FUNC SINT32 DeleteRecord(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, const FORMID ParentFormID);
EXPORT_FUNC UINT32 CopyRecord(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, const UINT32 DestModID, const UINT32 DestParentFormID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, const UINT32 CreateFlags);
EXPORT_FUNC SINT32 UnloadRecord(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID);
EXPORT_FUNC SINT32 SetRecordIDs(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, const FORMID FormIDValue, STRING const EditorIDValue);
////////////////////////////////////////////////////////////////////////
//Record info functions
EXPORT_FUNC SINT32 GetNumRecords(const UINT32 CollectionID, const UINT32 ModID, const UINT32 RecordType);
EXPORT_FUNC void   GetRecordFormIDs(const UINT32 CollectionID, const UINT32 ModID, const UINT32 RecordType, FORMIDARRAY RecordFormIDs);
EXPORT_FUNC void   GetRecordEditorIDs(const UINT32 CollectionID, const UINT32 ModID, const UINT32 RecordType, STRINGARRAY RecordEditorIDs);
EXPORT_FUNC SINT32 IsRecordWinning(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, const bool GetExtendedConflicts);
EXPORT_FUNC SINT32 GetNumRecordConflicts(const UINT32 CollectionID, const FORMID RecordFormID, STRING const RecordEditorID, const bool GetExtendedConflicts);
EXPORT_FUNC void   GetRecordConflicts(const UINT32 CollectionID, const FORMID RecordFormID, STRING const RecordEditorID, UINT32ARRAY ModIDs, const bool GetExtendedConflicts);
EXPORT_FUNC void   GetRecordHistory(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, UINT32ARRAY ModIDs);
////////////////////////////////////////////////////////////////////////
//Mod or Record action functions
EXPORT_FUNC SINT32 UpdateReferences(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, const FORMID FormIDToReplace, const FORMID ReplacementFormID);
////////////////////////////////////////////////////////////////////////
//Mod or Record info functions
EXPORT_FUNC SINT32 GetNumReferences(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, const FORMID FormIDToMatch);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Field action functions
EXPORT_FUNC void   SetField(const UINT32 CollectionID, const UINT32 ModID, FORMID RecordFormID, STRING RecordEditorID, FIELD_IDENTIFIERS, void *FieldValue, const UINT32 ArraySize);
EXPORT_FUNC void   DeleteField(const UINT32 CollectionID, const UINT32 ModID, FORMID RecordFormID, STRING RecordEditorID, FIELD_IDENTIFIERS);
////////////////////////////////////////////////////////////////////////
//Field info functions
EXPORT_FUNC UINT32 GetFieldAttribute(const UINT32 CollectionID, const UINT32 ModID, FORMID RecordFormID, STRING RecordEditorID, FIELD_IDENTIFIERS, const UINT32 WhichAttribute);
EXPORT_FUNC void * GetField(const UINT32 CollectionID, const UINT32 ModID, FORMID RecordFormID, STRING RecordEditorID, FIELD_IDENTIFIERS, void **FieldValues);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////