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
// CBash.h
//#define _UNICODE
#include "MacroDefinitions.h"
#include "Collection.h"

#ifdef COMPILING_CBASH
    #define DLLEXTERN extern "C" __declspec(dllexport)
#else
    #define DLLEXTERN extern "C" __declspec(dllimport)
#endif

//Exported Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Version info functions
DLLEXTERN UINT32 GetVersionMajor();
DLLEXTERN UINT32 GetVersionMinor();
DLLEXTERN UINT32 GetVersionRevision();
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Logging action functions
DLLEXTERN void RedirectMessages(SINT32 (*_LoggingCallback)(const STRING));
DLLEXTERN void AllowRaising(void (*_RaiseCallback)());
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Collection action functions
DLLEXTERN Collection * CreateCollection(STRING const ModsPath, const UINT32 CollectionType);
DLLEXTERN SINT32 DeleteCollection(Collection *CollectionID);
DLLEXTERN SINT32 LoadCollection(Collection *CollectionID);
DLLEXTERN SINT32 UnloadCollection(Collection *CollectionID);
DLLEXTERN SINT32 GetCollectionType(Collection *CollectionID);
DLLEXTERN SINT32 UnloadAllCollections();
DLLEXTERN SINT32 DeleteAllCollections();
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Mod action functions
DLLEXTERN SINT32 AddMod(Collection *CollectionID, STRING const ModName, const UINT32 ModFlagsField);
DLLEXTERN SINT32 LoadMod(ModFile *ModID);
DLLEXTERN SINT32 UnloadMod(ModFile *ModID);
DLLEXTERN SINT32 CleanModMasters(ModFile *ModID);
DLLEXTERN SINT32 SaveMod(ModFile *ModID, const UINT32 SaveFlagsField, STRING const DestinationName);
////////////////////////////////////////////////////////////////////////
//Mod info functions
DLLEXTERN SINT32 GetAllNumMods(Collection *CollectionID);
DLLEXTERN SINT32 GetAllModIDs(Collection *CollectionID, MODIDARRAY ModIDs);
DLLEXTERN SINT32 GetLoadOrderNumMods(Collection *CollectionID);
DLLEXTERN SINT32 GetLoadOrderModIDs(Collection *CollectionID, MODIDARRAY ModIDs);
DLLEXTERN STRING GetFileNameByID(ModFile *ModID);
DLLEXTERN STRING GetFileNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);
DLLEXTERN STRING GetModNameByID(ModFile *ModID);
DLLEXTERN STRING GetModNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);
DLLEXTERN ModFile * GetModIDByName(Collection *CollectionID, STRING const ModName);
DLLEXTERN ModFile * GetModIDByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);
DLLEXTERN SINT32 GetModLoadOrderByName(Collection *CollectionID, STRING const ModName);
DLLEXTERN SINT32 GetModLoadOrderByID(ModFile *ModID);
DLLEXTERN ModFile * GetModIDByRecordID(Record *RecordID);
DLLEXTERN Collection * GetCollectionIDByRecordID(Record *RecordID);
DLLEXTERN Collection * GetCollectionIDByModID(ModFile *ModID);
//DLLEXTERN SINT32 GetShortIDIndex(Collection *CollectionID, const SINT32 ModID, STRING const ModName);
DLLEXTERN UINT32 IsModEmpty(ModFile *ModID);
DLLEXTERN SINT32 GetModNumTypes(ModFile *ModID);
DLLEXTERN SINT32 GetModTypes(ModFile *ModID, UINT32ARRAY RecordTypes);
DLLEXTERN SINT32 GetModNumEmptyGRUPs(ModFile *ModID);
DLLEXTERN SINT32 GetModNumOrphans(ModFile *ModID);
DLLEXTERN SINT32 GetModOrphansFormIDs(ModFile *ModID, FORMIDARRAY FormIDs);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//FormID functions
DLLEXTERN STRING GetLongIDName(Record *RecordID, const UINT32 FormID, const bool IsMGEFCode);
DLLEXTERN UINT32 MakeShortFormID(ModFile *ModID, const UINT32 ObjectID, const bool IsMGEFCode);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Record action functions
DLLEXTERN Record * CreateRecord(ModFile *ModID, const UINT32 RecordType, const FORMID RecordFormID, STRING const RecordEditorID, Record *ParentID, const UINT32 CreateFlags);
DLLEXTERN Record * CopyRecord(Record *RecordID, ModFile *DestModID, Record *DestParentID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, const UINT32 CreateFlags);
DLLEXTERN SINT32 UnloadRecord(Record *RecordID);
DLLEXTERN SINT32 ResetRecord(Record *RecordID);
DLLEXTERN SINT32 DeleteRecord(Record *RecordID);
////////////////////////////////////////////////////////////////////////
//Record info functions
DLLEXTERN Record * GetRecordID(ModFile *ModID, const FORMID RecordFormID, STRING const RecordEditorID);
DLLEXTERN SINT32 GetNumRecords(ModFile *ModID, const UINT32 RecordType);
DLLEXTERN SINT32 GetRecordIDs(ModFile *ModID, const UINT32 RecordType, RECORDIDARRAY RecordIDs);
DLLEXTERN SINT32 IsRecordWinning(Record *RecordID, const bool GetExtendedConflicts);
DLLEXTERN SINT32 GetNumRecordConflicts(Record *RecordID, const bool GetExtendedConflicts);
DLLEXTERN SINT32 GetRecordConflicts(Record *RecordID, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts);
DLLEXTERN SINT32 GetRecordHistory(Record *RecordID, RECORDIDARRAY RecordIDs);
DLLEXTERN SINT32 GetNumIdenticalToMasterRecords(ModFile *ModID);
DLLEXTERN SINT32 GetIdenticalToMasterRecords(ModFile *ModID, RECORDIDARRAY RecordIDs);
////////////////////////////////////////////////////////////////////////
//Mod or Record action functions
DLLEXTERN SINT32 UpdateReferences(ModFile *ModID, Record *RecordID, FORMIDARRAY OldFormIDs, FORMIDARRAY NewFormIDs, UINT32ARRAY Changes, const UINT32 ArraySize);
////////////////////////////////////////////////////////////////////////
//Mod or Record info functions
DLLEXTERN SINT32 GetRecordUpdatedReferences(Collection *CollectionID, Record *RecordID);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Field action functions
DLLEXTERN SINT32 SetIDFields(Record *RecordID, const FORMID FormID, STRING const EditorID);
DLLEXTERN void   SetField(Record *RecordID, FIELD_IDENTIFIERS, void *FieldValue, const UINT32 ArraySize);
DLLEXTERN void   DeleteField(Record *RecordID, FIELD_IDENTIFIERS);
////////////////////////////////////////////////////////////////////////
//Field info functions
DLLEXTERN UINT32 GetFieldAttribute(Record *RecordID, FIELD_IDENTIFIERS, const UINT32 WhichAttribute);
DLLEXTERN void * GetField(Record *RecordID, FIELD_IDENTIFIERS, void **FieldValues);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////