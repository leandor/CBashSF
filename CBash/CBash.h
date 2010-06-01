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
extern "C" __declspec(dllexport) unsigned int GetMajor();
extern "C" __declspec(dllexport) unsigned int GetMinor();
extern "C" __declspec(dllexport) unsigned int GetRevision();
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int NewCollection(const char *ModsPath);
extern "C" __declspec(dllexport) int DeleteCollection(const unsigned int CollectionIndex);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int NewMod(const unsigned int CollectionIndex, const char *ModName);
extern "C" __declspec(dllexport) int AddMod(const unsigned int CollectionIndex, const char *ModName, bool CreateIfNotExist);
extern "C" __declspec(dllexport) int MinimalLoad(const unsigned int CollectionIndex, const bool LoadMasters);
extern "C" __declspec(dllexport) int FullLoad(const unsigned int CollectionIndex, const bool LoadMasters);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int GetChangedMods(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) int SafeSaveMod(const unsigned int CollectionIndex, char *ModName, bool CloseMod);
extern "C" __declspec(dllexport) int SafeSaveAllChangedMods(const unsigned int CollectionIndex);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int LoadRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID);
extern "C" __declspec(dllexport) int UnloadRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID);
extern "C" __declspec(dllexport) int DeleteRecord(const unsigned int CollectionIndex, char *ModName, unsigned int recordFID, unsigned int parentFID);
extern "C" __declspec(dllexport) int DeleteGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID);
extern "C" __declspec(dllexport) int Close(const unsigned int CollectionIndex);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int GetNumMods(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) void GetMods(const unsigned int CollectionIndex, char **ModNames);
extern "C" __declspec(dllexport) char * GetModName(const unsigned int CollectionIndex, const unsigned int iIndex);
extern "C" __declspec(dllexport) unsigned int GetCorrectedFID(const unsigned int CollectionIndex, char *ModName, unsigned int recordObjectID);
////////////////////////////////////////////////////////////////////////
//ADD
extern "C" __declspec(dllexport) unsigned int GetNumGMSTRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumGLOBRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumCLASRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumFACTRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumHAIRRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumEYESRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumRACERecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumSOUNRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumSKILRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumMGEFRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumSCPTRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumLTEXRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumENCHRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumSPELRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumBSGNRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumACTIRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumAPPARecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumARMORecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumBOOKRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumCLOTRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumCONTRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumDOORRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumINGRRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumLIGHRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumMISCRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumSTATRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumGRASRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumTREERecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumFLORRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumFURNRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumWEAPRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumAMMORecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumNPC_Records(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumCREARecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumLVLCRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumSLGMRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumKEYMRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumALCHRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumSBSPRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumSGSTRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumLVLIRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumWTHRRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumCLMTRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumREGNRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumCELLRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumACHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int GetNumACRERecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int GetNumREFRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int GetNumWRLDRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumDIALRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumQUSTRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumIDLERecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumPACKRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumCSTYRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumLSCRRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumLVSPRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumANIORecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumWATRRecords(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int GetNumEFSHRecords(const unsigned int CollectionIndex, char *ModName);
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
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) void GetGMSTs(const unsigned int CollectionIndex, char *ModName, char **RecordEIDs);
extern "C" __declspec(dllexport) int GetGMSTFieldType(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field);
extern "C" __declspec(dllexport) void * ReadGMSTField(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) unsigned int CreateGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID);
extern "C" __declspec(dllexport) unsigned int CopyGMSTRecord(const unsigned int CollectionIndex, char *ModName, char *recordEDID, char *destModName);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) int SetGMSTFieldStr (const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, char *FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldI (const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, int FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldUI(const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, unsigned int FieldValue);
extern "C" __declspec(dllexport) int SetGMSTFieldF (const unsigned int CollectionIndex, char *ModName, char *recordEDID, const unsigned int Field, float FieldValue);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//ADD
extern "C" __declspec(dllexport) unsigned int GetGLOBRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetCLASRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetFACTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetHAIRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetEYESRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetRACERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetSOUNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetSKILRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetMGEFRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetSCPTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetLTEXRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetENCHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetSPELRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetBSGNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetACTIRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetAPPARecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetARMORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetBOOKRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetCLOTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetCONTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetDOORRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetINGRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetLIGHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetMISCRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetSTATRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetGRASRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetTREERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetFLORRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetFURNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetWEAPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetAMMORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetNPC_Records(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetCREARecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetLVLCRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetSLGMRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetKEYMRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetALCHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetSBSPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetSGSTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetLVLIRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetWTHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetCLMTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetREGNRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetCELLRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetACHRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetACRERecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetREFRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetWRLDRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetDIALRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetQUSTRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetIDLERecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetPACKRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetCSTYRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetLSCRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetLVSPRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetANIORecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetWATRRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
extern "C" __declspec(dllexport) unsigned int GetEFSHRecords(const unsigned int CollectionIndex, char *ModName, unsigned int **RecordFIDs);
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
//ADD
extern "C" __declspec(dllexport) unsigned int CreateGLOBRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateCLASRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateFACTRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateHAIRRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateEYESRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateRACERecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateSOUNRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateSKILRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateMGEFRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateSCPTRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateLTEXRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateENCHRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateSPELRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateBSGNRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateACTIRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateAPPARecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateARMORecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateBOOKRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateCLOTRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateCONTRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateDOORRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateINGRRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateLIGHRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateMISCRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateSTATRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateGRASRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateTREERecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateFLORRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateFURNRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateWEAPRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateAMMORecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateNPC_Record(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateCREARecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateLVLCRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateSLGMRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateKEYMRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateALCHRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateSBSPRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateSGSTRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateLVLIRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateWTHRRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateCLMTRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateREGNRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateCELLRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID, bool isWorldCELL);
extern "C" __declspec(dllexport) unsigned int CreateACHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int CreateACRERecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int CreateREFRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int CreatePGRDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int CreateWRLDRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateROADRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int CreateLANDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);

extern "C" __declspec(dllexport) unsigned int CreateDIALRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateINFORecord(const unsigned int CollectionIndex, char *ModName, unsigned int parentFID);
extern "C" __declspec(dllexport) unsigned int CreateQUSTRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateIDLERecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreatePACKRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateCSTYRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateLSCRRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateLVSPRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateANIORecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateWATRRecord(const unsigned int CollectionIndex, char *ModName);
extern "C" __declspec(dllexport) unsigned int CreateEFSHRecord(const unsigned int CollectionIndex, char *ModName);
////////////////////////////////////////////////////////////////////////
//ADD
extern "C" __declspec(dllexport) unsigned int CopyFIDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyGLOBRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyCLASRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyFACTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyHAIRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyEYESRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyRACERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopySOUNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopySKILRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyMGEFRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopySCPTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyLTEXRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyENCHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopySPELRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyBSGNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyACTIRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyAPPARecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyARMORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyBOOKRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyCLOTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyCONTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyDOORRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyINGRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyLIGHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyMISCRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopySTATRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyGRASRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyTREERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyFLORRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyFURNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyWEAPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyAMMORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyNPC_Record(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyCREARecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyLVLCRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopySLGMRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyKEYMRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyALCHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopySBSPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopySGSTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyLVLIRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyWTHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyCLMTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyREGNRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyCELLRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride, bool isWorldCELL);
extern "C" __declspec(dllexport) unsigned int CopyACHRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyACRERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyREFRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyPGRDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyWRLDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyROADRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyLANDRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyDIALRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyINFORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, unsigned int destParentFID, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyQUSTRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyIDLERecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyPACKRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyCSTYRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyLSCRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyLVSPRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyANIORecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyWATRRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
extern "C" __declspec(dllexport) unsigned int CopyEFSHRecord(const unsigned int CollectionIndex, char *ModName, unsigned int srcRecordFID, char *destModName, bool asOverride);
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
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//ADD
extern "C" __declspec(dllexport) unsigned int StartGLOBIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartCLASIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartFACTIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartHAIRIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartEYESIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartRACEIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartSOUNIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartSKILIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartMGEFIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartSCPTIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartLTEXIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartENCHIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartSPELIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartBSGNIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartACTIIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartAPPAIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartARMOIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartBOOKIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartCLOTIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartCONTIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartDOORIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartINGRIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartLIGHIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartMISCIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartSTATIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartGRASIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartTREEIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartFLORIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartFURNIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartWEAPIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartAMMOIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartNPC_Iterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartCREAIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartLVLCIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartSLGMIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartKEYMIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartALCHIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartSBSPIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartSGSTIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartLVLIIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartWTHRIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartCLMTIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartREGNIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartCELLIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartWRLDIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartDIALIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartQUSTIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartIDLEIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartPACKIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartCSTYIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartLSCRIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartLVSPIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartANIOIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartWATRIterator(const unsigned int CollectionIndex);
extern "C" __declspec(dllexport) unsigned int StartEFSHIterator(const unsigned int CollectionIndex);
////////////////////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) long long IncrementIterator(const unsigned int IteratorID);
extern "C" __declspec(dllexport) unsigned int IteratorAtEnd(const unsigned int IteratorID);
extern "C" __declspec(dllexport) void StopIterator(const unsigned int IteratorID);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
extern "C" __declspec(dllexport) void Debug(const unsigned int CollectionIndex, const int debugLevel, const bool AllRecords);
#endif
