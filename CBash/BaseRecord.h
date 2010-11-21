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
// BaseRecord.h
#include "Common.h"
#include "GenericChunks.h"

class Record;

class FormIDOp
    {
    protected:
        UINT32 count;
        bool stop;
        bool result;
        
    public:
        FormIDOp();
        ~FormIDOp();
        
        virtual bool Accept(UINT32 &curFormID) abstract {};
        virtual bool AcceptMGEF(UINT32 &curMgefCode) abstract {};
        
        UINT32 GetCount();
        void ResetCount();
        bool Stop();
        bool GetResult();
    };

class FormIDResolver : public FormIDOp
    {
    private:
        const UINT8 (&ResolveTable)[255];
        
    public:
        FormIDResolver(const UINT8 (&_ResolveTable)[255]);
        ~FormIDResolver();
        
        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
    };

class FormIDMasterUpdater : public FormIDOp
    {
    private:
        FormIDHandlerClass &FormIDHandler;
        
    public:
        FormIDMasterUpdater(FormIDHandlerClass &_FormIDHandler);
        ~FormIDMasterUpdater();

        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
    };

class FormIDMatchCounter : public FormIDOp
    {
    private:
        const UINT32 &FormIDToMatch;
        
    public:
        FormIDMatchCounter(const UINT32 &_FormIDToMatch);
        ~FormIDMatchCounter();
        
        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
    };

class RecordOp
    {
    protected:
        UINT32 count;
        bool stop;
        bool result;
        
    public:
        RecordOp();
        ~RecordOp();
        
        virtual bool Accept(Record **curRecord) abstract {};
        
        UINT32 GetCount();
        void ResetCount();
        bool Stop();
        bool GetResult();
    };

class RecordReader : public RecordOp
    {
    private:
        FormIDResolver expander;
        
    public:
        RecordReader(FormIDHandlerClass &_FormIDHandler);
        ~RecordReader();
        
        bool Accept(Record **curRecord);
    };

class RecordUnloader : public RecordOp
    {
    public:
        RecordUnloader();
        ~RecordUnloader();
        
        bool Accept(Record **curRecord);
    };

class FormIDRecordRetriever : public RecordOp
    {
    private:
        UINT32 **RecordFIDs;
        
    public:
        FormIDRecordRetriever(UINT32 **_RecordFIDs);
        ~FormIDRecordRetriever();
        
        bool Accept(Record **curRecord);
    };

class EditorIDRecordRetriever : public RecordOp
    {
    private:
        STRINGARRAY RecordEditorIDs;
        
    public:
        EditorIDRecordRetriever(STRINGARRAY _RecordEditorIDs);
        ~EditorIDRecordRetriever();
        
        bool Accept(Record **curRecord);
    };

class RecordMasterChecker : public RecordOp
    {
    private:
        class FormIDMasterChecker : public FormIDOp
            {
            private:
                const UINT8 (&ExpandTable)[255];
                const UINT8 &MasterIndex;
                
            public:
                FormIDMasterChecker(const UINT8 (&_ExpandTable)[255], const UINT8 &_MasterIndex);
                ~FormIDMasterChecker();
                
                bool Accept(UINT32 &curFormID);
                bool AcceptMGEF(UINT32 &curMgefCode);
            } checker;

        RecordReader reader;

    public:
        RecordMasterChecker(FormIDHandlerClass &_FormIDHandler, const UINT8 &_MasterIndex);
        ~RecordMasterChecker();

        bool Accept(Record **curRecord);
    };

class RecordFormIDSwapper : public RecordOp
    {
    private:
        class FormIDSwapper : public FormIDOp
            {
            private:
                const UINT32 &FormIDToMatch;
                const UINT32 &FormIDToSwap;
                FormIDMasterUpdater checker;

            public:
                FormIDSwapper(const UINT32 &_FormIDToMatch, const UINT32 &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler);
                ~FormIDSwapper();
                
                bool Accept(UINT32 &curFormID);
                bool AcceptMGEF(UINT32 &curMgefCode);
            } swapper;

        RecordReader reader;

    public:
        RecordFormIDSwapper(const UINT32 &_FormIDToMatch, const UINT32 &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler);
        ~RecordFormIDSwapper();

        bool Accept(Record **curRecord);
    };

class Record
    {
    protected:
        enum ExtendedSize
            {
            eXXXX=0x58585858
            };
        enum headerFlags
            {
            fIsESM                  = 0x00000001,
            //fIsTaken              = 0x00000002, //From OBSE, unconfirmed, requires fIsDeleted also be set
            fIsDeleted              = 0x00000020,
            fIsBorderRegion         = 0x00000040,
            fTurnOffFire            = 0x00000080,
            fCastsShadows           = 0x00000200,
            fIsQuestOrPersistent    = 0x00000400,
            fIsInitiallyDisabled    = 0x00000800,
            fIsIgnored              = 0x00001000,
            //fIsTemporary            = 0x00004000, //From OBSE, unconfirmed
            fIsVisibleWhenDistant   = 0x00008000,
            fIsDangerousOrOffLimits = 0x00020000,
            fIsCompressed           = 0x00040000,
            fCantWait               = 0x00080000
            };
        enum unkHeaderFlags
            {
            _fIsLoaded              = 0x80000000 //Not an actual flag. Used only by CBash internally. Won't be written.
            };

    public:
        unsigned char *recData;
        UINT32 flags;
        FORMID formID;
        UINT32 flagsUnk;

        Record(bool _IsNewRecord=false);
        virtual ~Record();
        
        virtual void Unload() abstract {};
        virtual UINT32 GetSize(bool forceCalc=false) abstract {};
        virtual UINT32 GetType() abstract {};
        virtual STRING GetStrType() abstract {};
        virtual SINT32 WriteRecord(_FileHandler &SaveHandler) abstract {};
        virtual SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize) abstract {};
        
        virtual SINT32 GetOtherFieldType(const UINT32 Field);
        SINT32 GetFieldType(const UINT32 Field);
        
        virtual void * GetOtherField(const UINT32 Field);
        void * GetField(const UINT32 Field);
        
        virtual void SetOtherField(const UINT32 Field, UINT32 FieldValue);
        void SetField(const UINT32 Field, UINT32 FieldValue);
        virtual void SetField(const UINT32 Field, STRINGARRAY FieldValue, UINT32 nSize);
        virtual void SetField(const UINT32 Field, UINT8ARRAY FieldValue, UINT32 nSize);
        virtual void SetField(const UINT32 Field, FLOAT32 FieldValue);
        virtual void SetField(const UINT32 Field, SINT32 FieldValue);
        virtual void SetField(const UINT32 Field, STRING FieldValue);
        virtual void SetField(const UINT32 Field, SINT8 FieldValue);
        virtual void SetField(const UINT32 Field, UINT8 FieldValue);
        virtual void SetField(const UINT32 Field, UINT32 FieldValue[], UINT32 nSize);
        virtual void SetField(const UINT32 Field, SINT16 FieldValue);
        virtual void SetField(const UINT32 Field, UINT16 FieldValue);
        
        virtual UINT32 GetFieldArraySize(const UINT32 Field);
        virtual UINT32 GetListSize(const UINT32 Field);
        virtual UINT32 GetListX2Size(const UINT32 subField, const UINT32 listIndex, const UINT32 listField);
        virtual UINT32 GetListX3Size(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field);
        virtual UINT32 GetListArraySize(const UINT32 subField, const UINT32 listIndex, const UINT32 listField);
        virtual UINT32 GetListX2ArraySize(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field);
        virtual UINT32 GetListX3ArraySize(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field);
        
        virtual SINT32 GetListFieldType(const UINT32 subField, const UINT32 listField);
        virtual SINT32 GetListX2FieldType(const UINT32 subField, const UINT32 listField, const UINT32 listX2Field);
        virtual SINT32 GetListX3FieldType(const UINT32 subField, const UINT32 listField, const UINT32 listX2Field, const UINT32 listX3Field);
        virtual void * GetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField);
        virtual void * GetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field);
        virtual void * GetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field);
        
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, UINT8ARRAY FieldValue, UINT32 nSize);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, STRINGARRAY FieldValue, UINT32 nSize);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, SINT8 FieldValue);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, UINT8 FieldValue);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, STRING FieldValue);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, SINT16 FieldValue);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, UINT16 FieldValue);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, SINT32 FieldValue);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, UINT32 FieldValue);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, UINT32 FieldValue[], UINT32 nSize);
        virtual void SetListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, FLOAT32 FieldValue);
        
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, UINT8ARRAY FieldValue, UINT32 nSize);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, STRINGARRAY FieldValue, UINT32 nSize);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, SINT8 FieldValue);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, UINT8 FieldValue);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, STRING FieldValue);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, SINT16 FieldValue);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, UINT16 FieldValue);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, SINT32 FieldValue);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, UINT32 FieldValue);
        virtual void SetListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, FLOAT32 FieldValue);
        
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, UINT8ARRAY FieldValue, UINT32 nSize);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, STRINGARRAY FieldValue, UINT32 nSize);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, SINT8 FieldValue);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, UINT8 FieldValue);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, STRING FieldValue);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, SINT16 FieldValue);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, UINT16 FieldValue);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, SINT32 FieldValue);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, UINT32 FieldValue);
        virtual void SetListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, FLOAT32 FieldValue);
        
        virtual void GetFieldArray(const UINT32 Field, void **FieldValues);
        virtual void GetListArray(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, void **FieldValues);
        virtual void GetListX2Array(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, void **FieldValues);
        virtual void GetListX3Array(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field, void **FieldValues);
        
        virtual SINT32 CreateListElement(const UINT32 subField);
        virtual SINT32 CreateListX2Element(const UINT32 subField, const UINT32 listIndex, const UINT32 listField);
        virtual SINT32 CreateListX3Element(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field);
        
        virtual SINT32 DeleteListElement(const UINT32 subField);
        virtual SINT32 DeleteListX2Element(const UINT32 subField, const UINT32 listIndex, const UINT32 listField);
        virtual SINT32 DeleteListX3Element(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field);
        
        virtual SINT32 DeleteField(const UINT32 Field);
        virtual SINT32 DeleteListField(const UINT32 subField, const UINT32 listIndex, const UINT32 listField);
        virtual SINT32 DeleteListX2Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field);
        virtual SINT32 DeleteListX3Field(const UINT32 subField, const UINT32 listIndex, const UINT32 listField, const UINT32 listX2Index, const UINT32 listX2Field, const UINT32 listX3Index, const UINT32 listX3Field);
        
        virtual UINT32 GetParentType();
        
        virtual bool IsKeyedByEditorID();
        virtual bool HasSubRecords();
        
        virtual bool VisitSubRecords(const UINT32 &RecordType, RecordOp &op);
        virtual bool VisitFormIDs(FormIDOp &op);
        
        bool Read();
        UINT32 Write(_FileHandler &SaveHandler, FormIDHandlerClass &FormIDHandler);
        
        bool IsDeleted() const;
        void IsDeleted(bool value);
        bool IsBorderRegion();
        void IsBorderRegion(bool value);
        bool IsTurnOffFire();
        void IsTurnOffFire(bool value);
        bool IsCastsShadows();
        void IsCastsShadows(bool value);
        bool IsQuestOrPersistent();
        void IsQuestOrPersistent(bool value);
        bool IsQuest();
        void IsQuest(bool value);
        bool IsPersistent();
        void IsPersistent(bool value);
        bool IsInitiallyDisabled();
        void IsInitiallyDisabled(bool value);
        bool IsIgnored();
        void IsIgnored(bool value);
        bool IsVisibleWhenDistant();
        void IsVisibleWhenDistant(bool value);
        bool IsVWD();
        void IsVWD(bool value);
        bool IsTemporary();
        void IsTemporary(bool value);
        bool IsDangerousOrOffLimits();
        void IsDangerousOrOffLimits(bool value);
        bool IsDangerous();
        void IsDangerous(bool value);
        bool IsOffLimits();
        void IsOffLimits(bool value);
        bool IsCompressed();
        void IsCompressed(bool value);
        bool IsCantWait();
        void IsCantWait(bool value);
        bool IsHeaderFlagMask(UINT32 Mask, bool Exact=false);
        void SetHeaderFlagMask(UINT32 Mask);
        bool IsLoaded();
        void IsLoaded(bool value);
    };