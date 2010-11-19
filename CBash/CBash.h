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
void Validate(const unsigned int CollectionIndex);

//Exported Functions
extern "C" __declspec(dllexport) unsigned int GetMajor();
extern "C" __declspec(dllexport) unsigned int GetMinor();
extern "C" __declspec(dllexport) unsigned int GetRevision();
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int NewCollection(const char *ModsPath);
extern "C" __declspec(dllexport) int DeleteCollection(const unsigned int CollectionIndex);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int AddMod(const unsigned int CollectionIndex, const char *ModName, unsigned int SettingFlags);
extern "C" __declspec(dllexport) int MinimalLoad(const unsigned int CollectionIndex, const bool LoadMasters);
extern "C" __declspec(dllexport) int FullLoad(const unsigned int CollectionIndex, const bool LoadMasters);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int IsModEmpty(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumNewRecordTypes(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) void GetNewRecordTypes(const unsigned int CollectionIndex, char *ModName, unsigned int const **RecordTypes);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int CleanMasters(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) int SafeSaveMod(const unsigned int CollectionIndex, char *ModName, bool CloseMod);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int LoadRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID);
extern "C" __declspec(dllexport) int UnloadRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID);
extern "C" __declspec(dllexport) int UnloadModFile(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) int UnloadAll(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) int Close(const unsigned int CollectionIndex);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int CreateRecord(const unsigned int CollectionIndex, char *ModName, const unsigned int RecordType, const unsigned int ParentFID, unsigned int CreateFlags);
extern "C" __declspec(dllexport) unsigned int CopyRecord(const unsigned int CollectionIndex, char *ModName, unsigned int RecordFID, char *DestModName, unsigned int DestParentFID, unsigned int CreateFlags);
extern "C" __declspec(dllexport) int DeleteRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int parentFID);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int CreateGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID);
extern "C" __declspec(dllexport) unsigned int CopyGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID, char *destModName);
extern "C" __declspec(dllexport) int DeleteGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int GetNumMods(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) void GetMods(const unsigned int CollectionIndex, char **ModNames);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int SetRecordFormID(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int FieldValue);
extern "C" __declspec(dllexport) char * GetModName(const unsigned int CollectionIndex, const unsigned int iIndex);
extern "C" __declspec(dllexport) unsigned int ModIsFake(const unsigned int CollectionIndex, const unsigned int iIndex);
extern "C" __declspec(dllexport) unsigned int GetCorrectedFID(const unsigned int CollectionIndex, char *ModName, unsigned int recordObjectID);
extern "C" __declspec(dllexport) unsigned int UpdateAllReferences(const unsigned int CollectionIndex, char *ModName, unsigned int origFormID, unsigned int newFormID);
extern "C" __declspec(dllexport) unsigned int GetNumReferences(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int referenceFormID);
extern "C" __declspec(dllexport) unsigned int UpdateReferences(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int origFormID, unsigned int newFormID);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int IsFIDWinning(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, bool ignoreScanned);
extern "C" __declspec(dllexport) int IsGMSTWinning(const unsigned int CollectionIndex, char *ModName, char *recordEDID, bool ignoreScanned);
extern "C" __declspec(dllexport) int GetNumFIDConflicts(const unsigned int CollectionIndex, unsigned int recordFID, bool ignoreScanned);
extern "C" __declspec(dllexport) void GetFIDConflicts(const unsigned int CollectionIndex, unsigned int recordFID, bool ignoreScanned, char **ModNames);
extern "C" __declspec(dllexport) int GetNumGMSTConflicts(const unsigned int CollectionIndex, char *recordEDID, bool ignoreScanned);
extern "C" __declspec(dllexport) void GetGMSTConflicts(const unsigned int CollectionIndex, char *recordEDID, bool ignoreScanned, char **ModNames);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int GetNumRecords(const unsigned int CollectionIndex, char *ModName, const unsigned int RecordType);
extern "C" __declspec(dllexport) void GetRecordFormIDs(const unsigned int CollectionIndex, char *ModName, const unsigned int RecordType, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) void GetRecordEditorIDs(const unsigned int CollectionIndex, char *ModName, const unsigned int RecordType, char **RecordEIDs);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int GetTES4FieldType(const unsigned int CollectionIndex, char *ModName, const unsigned int Field);
extern "C" __declspec(dllexport) unsigned int GetTES4FieldArraySize(const unsigned int CollectionIndex, char *ModName, const unsigned int Field);
extern "C" __declspec(dllexport) void GetTES4FieldArray(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, void **FieldValues);
extern "C" __declspec(dllexport) void * ReadTES4Field(const unsigned int CollectionIndex, char *ModName, const unsigned int Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetTES4FieldStr (const unsigned int CollectionIndex, char *ModName, const unsigned int Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetTES4FieldStrA(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, char **FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int SetTES4FieldUI(const unsigned int CollectionIndex, char *ModName, const unsigned int Field, unsigned int FieldValue);
extern "C" __declspec(dllexport) int SetTES4FieldF (const unsigned int CollectionIndex, char *ModName, const unsigned int Field, float FieldValue);
extern "C" __declspec(dllexport) int SetTES4FieldR (const unsigned int CollectionIndex, char *ModName, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int DeleteTES4Field (const unsigned int CollectionIndex, char *ModName, const unsigned int Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int GetGMSTFieldType(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field);
extern "C" __declspec(dllexport) void * ReadGMSTField(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetGMSTFieldStr (const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldI (const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, int FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldUI(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, unsigned int FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldF (const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, float FieldValue);
extern "C" __declspec(dllexport) int DeleteGMSTField(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int GetFIDFieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field);
extern "C" __declspec(dllexport) int GetFIDListFieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField);
extern "C" __declspec(dllexport) int GetFIDListX2FieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field);
extern "C" __declspec(dllexport) int GetFIDListX3FieldType(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int GetFIDFieldArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field);
extern "C" __declspec(dllexport) unsigned int GetFIDListArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
extern "C" __declspec(dllexport) unsigned int GetFIDListX2ArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
extern "C" __declspec(dllexport) unsigned int GetFIDListX3ArraySize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int GetFIDListSize(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field);
extern "C" __declspec(dllexport) unsigned int GetFIDListX2Size(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
extern "C" __declspec(dllexport) unsigned int GetFIDListX3Size(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void GetFIDFieldArray(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, void **FieldValues);
extern "C" __declspec(dllexport) void GetFIDListArray(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
extern "C" __declspec(dllexport) void GetFIDListX2Array(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues);
extern "C" __declspec(dllexport) void GetFIDListX3Array(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void * ReadFIDField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field);
extern "C" __declspec(dllexport) void * ReadFIDListField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
extern "C" __declspec(dllexport) void * ReadFIDListX2Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
extern "C" __declspec(dllexport) void * ReadFIDListX3Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetFIDFieldC  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldUC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned char FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldStr  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldStrA (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, char **FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int SetFIDFieldS  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, short FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldUS (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned short FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldI  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, int FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldUI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned int FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldUIA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);
extern "C" __declspec(dllexport) int SetFIDFieldF  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, float FieldValue);
extern "C" __declspec(dllexport) int SetFIDFieldR  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int DeleteFIDField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int CreateFIDListElement(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField);
extern "C" __declspec(dllexport) int CreateFIDListX2Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
extern "C" __declspec(dllexport) int CreateFIDListX3Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int DeleteFIDListElement(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField);
extern "C" __declspec(dllexport) int DeleteFIDListX2Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
extern "C" __declspec(dllexport) int DeleteFIDListX3Element(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetFIDListFieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char **FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int SetFIDListFieldS  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldUS (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldI  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldUI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldUIA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue[], unsigned int nSize);
extern "C" __declspec(dllexport) int SetFIDListFieldF  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue);
extern "C" __declspec(dllexport) int SetFIDListFieldR  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int DeleteFIDListField(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetFIDListX2FieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char **FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int SetFIDListX2FieldS  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldUS (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, int FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldF (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX2FieldR (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int DeleteFIDListX2Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetFIDListX3FieldC (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldUC(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldStr (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldStrA(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char **FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int SetFIDListX3FieldS  (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldUS (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned short FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldI (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, int FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldUI(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned int FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldF (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, float FieldValue);
extern "C" __declspec(dllexport) int SetFIDListX3FieldR (const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char *FieldValue, unsigned int nSize);
extern "C" __declspec(dllexport) int DeleteFIDListX3Field(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
extern "C" __declspec(dllexport) void Debug(const unsigned int CollectionIndex, const int debugLevel, const bool AllRecords);
#endif
