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

//Internal Functions
void Validate(const char *ModsPath);
void Validate(const unsigned long CollectionIndex);

//Exported Functions
extern "C" __declspec(dllexport) unsigned long GetMajor();
extern "C" __declspec(dllexport) unsigned long GetMinor();
extern "C" __declspec(dllexport) unsigned long GetRevision();
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int NewCollection(const char *ModsPath);
extern "C" __declspec(dllexport) int DeleteCollection(const unsigned long CollectionIndex);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int AddMod(const unsigned long CollectionIndex, const char *ModName, unsigned long SettingFlags);
extern "C" __declspec(dllexport) int MinimalLoad(const unsigned long CollectionIndex, const bool LoadMasters);
extern "C" __declspec(dllexport) int FullLoad(const unsigned long CollectionIndex, const bool LoadMasters);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int IsModEmpty(const unsigned long CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned long GetNumNewRecordTypes(const unsigned long CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) void GetNewRecordTypes(const unsigned long CollectionIndex, char *ModName, unsigned long const **RecordTypes);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int CleanMasters(const unsigned long CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) int SafeSaveMod(const unsigned long CollectionIndex, char *ModName, bool CloseMod);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int LoadRecord(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID);
extern "C" __declspec(dllexport) int UnloadRecord(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID);
extern "C" __declspec(dllexport) int UnloadModFile(const unsigned long CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) int UnloadAll(const unsigned long CollectionIndex);
extern "C" __declspec(dllexport) int Close(const unsigned long CollectionIndex);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned long CreateRecord(const unsigned long CollectionIndex, char *ModName, const unsigned long RecordType, unsigned long RecordFID, char *RecordEditorID, const unsigned long ParentFID, unsigned long CreateFlags);
extern "C" __declspec(dllexport) unsigned long CopyRecord(const unsigned long CollectionIndex, char *ModName, unsigned long RecordFID, char *DestModName, unsigned long DestParentFID, unsigned long CreateFlags);
extern "C" __declspec(dllexport) int DeleteRecord(const unsigned long CollectionIndex, char *ModName, unsigned long RecordFID, char *RecordEditorID, unsigned long ParentFID);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned long GetNumMods(const unsigned long CollectionIndex);
extern "C" __declspec(dllexport) void GetMods(const unsigned long CollectionIndex, char **ModNames);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned long SetRecordFormID(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, unsigned long FieldValue);
extern "C" __declspec(dllexport) char * GetModName(const unsigned long CollectionIndex, const unsigned long iIndex);
extern "C" __declspec(dllexport) unsigned long ModIsFake(const unsigned long CollectionIndex, const unsigned long iIndex);
extern "C" __declspec(dllexport) unsigned long GetCorrectedFID(const unsigned long CollectionIndex, char *ModName, unsigned long recordObjectID);
extern "C" __declspec(dllexport) unsigned long UpdateAllReferences(const unsigned long CollectionIndex, char *ModName, unsigned long origFormID, unsigned long newFormID);
extern "C" __declspec(dllexport) unsigned long GetNumReferences(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, unsigned long referenceFormID);
extern "C" __declspec(dllexport) unsigned long UpdateReferences(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, unsigned long origFormID, unsigned long newFormID);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int IsFIDWinning(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, bool ignoreScanned);
extern "C" __declspec(dllexport) int IsGMSTWinning(const unsigned long CollectionIndex, char *ModName, char *recordEDID, bool ignoreScanned);
extern "C" __declspec(dllexport) int GetNumFIDConflicts(const unsigned long CollectionIndex, unsigned long recordFID, bool ignoreScanned);
extern "C" __declspec(dllexport) void GetFIDConflicts(const unsigned long CollectionIndex, unsigned long recordFID, bool ignoreScanned, char **ModNames);
extern "C" __declspec(dllexport) int GetNumGMSTConflicts(const unsigned long CollectionIndex, char *recordEDID, bool ignoreScanned);
extern "C" __declspec(dllexport) void GetGMSTConflicts(const unsigned long CollectionIndex, char *recordEDID, bool ignoreScanned, char **ModNames);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned long GetNumRecords(const unsigned long CollectionIndex, char *ModName, const unsigned long RecordType);
extern "C" __declspec(dllexport) void GetRecordFormIDs(const unsigned long CollectionIndex, char *ModName, const unsigned long RecordType, unsigned long **RecordFIDs);
extern "C" __declspec(dllexport) void GetRecordEditorIDs(const unsigned long CollectionIndex, char *ModName, const unsigned long RecordType, char **RecordEIDs);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int GetTES4FieldType(const unsigned long CollectionIndex, char *ModName, const unsigned long Field);
extern "C" __declspec(dllexport) unsigned long GetTES4FieldArraySize(const unsigned long CollectionIndex, char *ModName, const unsigned long Field);
extern "C" __declspec(dllexport) void GetTES4FieldArray(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, void **FieldValues);
extern "C" __declspec(dllexport) void * ReadTES4Field(const unsigned long CollectionIndex, char *ModName, const unsigned long Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetTES4FieldStr (const unsigned long CollectionIndex, char *ModName, const unsigned long Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetTES4FieldStrA(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, char **FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int SetTES4FieldUI(const unsigned long CollectionIndex, char *ModName, const unsigned long Field, unsigned long FieldValue);
extern "C" __declspec(dllexport) int SetTES4FieldF (const unsigned long CollectionIndex, char *ModName, const unsigned long Field, float FieldValue);
extern "C" __declspec(dllexport) int SetTES4FieldR (const unsigned long CollectionIndex, char *ModName, const unsigned long Field, char *FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int DeleteTES4Field (const unsigned long CollectionIndex, char *ModName, const unsigned long Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int GetGMSTFieldType(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field);
extern "C" __declspec(dllexport) void * ReadGMSTField(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetGMSTFieldStr (const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldI (const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field, long FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldUI(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field, unsigned long FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldF (const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field, float FieldValue);
extern "C" __declspec(dllexport) int DeleteGMSTField(const unsigned long CollectionIndex, char *ModName, char *recordEDID, const unsigned long Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int GetFIDFieldType(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field);
extern "C" __declspec(dllexport) int GetFIDListFieldType(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField);
extern "C" __declspec(dllexport) int GetFIDListX2FieldType(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField, const unsigned long listX2Field);
extern "C" __declspec(dllexport) int GetFIDListX3FieldType(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listField, const unsigned long listX2Field, const unsigned long listX3Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned long GetFIDFieldArraySize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field);
extern "C" __declspec(dllexport) unsigned long GetFIDListArraySize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
extern "C" __declspec(dllexport) unsigned long GetFIDListX2ArraySize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
extern "C" __declspec(dllexport) unsigned long GetFIDListX3ArraySize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned long GetFIDListSize(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field);
extern "C" __declspec(dllexport) unsigned long GetFIDListX2Size(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
extern "C" __declspec(dllexport) unsigned long GetFIDListX3Size(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void GetFIDFieldArray(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, void **FieldValues);
extern "C" __declspec(dllexport) void GetFIDListArray(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues);
extern "C" __declspec(dllexport) void GetFIDListX2Array(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, void **FieldValues);
extern "C" __declspec(dllexport) void GetFIDListX3Array(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, void **FieldValues);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void * ReadFIDField(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field);
extern "C" __declspec(dllexport) void * ReadFIDListField(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
extern "C" __declspec(dllexport) void * ReadFIDListX2Field(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
extern "C" __declspec(dllexport) void * ReadFIDListX3Field(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetFIDFieldC  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, signed char FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldUC (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned char FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldStr  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldStrA (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, char **FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int SetFIDFieldS  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, short FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldUS (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned short FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldI  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, long FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldUI (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned long FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldUIA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned long FieldValue[], unsigned long nSize);
extern "C" __declspec(dllexport) int SetFIDFieldF  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, float FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldR  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field, unsigned char *FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int DeleteFIDField(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int CreateFIDListElement(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField);
extern "C" __declspec(dllexport) int CreateFIDListX2Element(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
extern "C" __declspec(dllexport) int CreateFIDListX3Element(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int DeleteFIDListElement(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField);
extern "C" __declspec(dllexport) int DeleteFIDListX2Element(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
extern "C" __declspec(dllexport) int DeleteFIDListX3Element(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetFIDListFieldC (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, signed char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldUC(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldStr (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, char *FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldStrA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, char **FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int SetFIDListFieldS  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldUS (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldI  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, long FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldUI (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldUIA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue[], unsigned long nSize);
extern "C" __declspec(dllexport) int SetFIDListFieldF  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, float FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldR  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int DeleteFIDListField(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetFIDListX2FieldC (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, signed char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldUC(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldStr (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldStrA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, char **FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int SetFIDListX2FieldS  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldUS (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldI (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, long FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldUI(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned long FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldF (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, float FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldR (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned char *FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int DeleteFIDListX2Field(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetFIDListX3FieldC (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, signed char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldUC(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, unsigned char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldStr (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldStrA(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, char **FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int SetFIDListX3FieldS  (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldUS (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, unsigned short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldI (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, long FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldUI(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, unsigned long FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldF (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, float FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldR (const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field, unsigned char *FieldValue, unsigned long nSize);
extern "C" __declspec(dllexport) int DeleteFIDListX3Field(const unsigned long CollectionIndex, char *ModName, unsigned long recordFID, const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, const unsigned long listX3Index, const unsigned long listX3Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
extern "C" __declspec(dllexport) void Debug(const unsigned long CollectionIndex, const int debugLevel, const bool AllRecords);
#endif
