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

class RecordOp
    {
    protected:
        UINT32 count;
        bool stop;
        bool result;

    public:
        RecordOp();
        ~RecordOp();

        virtual bool Accept(Record *&curRecord);

        UINT32 GetCount();
        void ResetCount();
        bool Stop();
        bool GetResult();
    };

class RecordReader : public RecordOp
    {
    private:
        FormIDResolver expander;
        std::vector<FormIDResolver *> &Expanders;

    public:
        RecordReader(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordReader();

        bool Accept(Record *&curRecord);
    };

class RecordProcessor
    {
    protected:
        FileReader &reader;
        FormIDHandlerClass &FormIDHandler;
        boost::unordered_set<UINT32> &UsedFormIDs;

        bool IsSkipNewRecords;
        bool IsTrackNewTypes;
        bool IsAddMasters;

        FormIDResolver expander;
    public:
        RecordOp &parser;
        const ModFlags &Flags;

        RecordProcessor(FileReader &reader, FormIDHandlerClass &_FormIDHandler, RecordOp &parser, const ModFlags &_Flags, boost::unordered_set<UINT32> &_UsedFormIDs);
        virtual ~RecordProcessor();

        virtual bool operator()(Record *&curRecord);
        void IsEmpty(bool value);
    };

class FNVRecordProcessor : public RecordProcessor
    {
    public:
        FNVRecordProcessor(FileReader &reader, FormIDHandlerClass &_FormIDHandler, RecordOp &_reader, const ModFlags &_Flags, boost::unordered_set<UINT32> &_UsedFormIDs);
        ~FNVRecordProcessor();

        bool operator()(Record *&curRecord);
    };

class Record
    {
    protected:
        unsigned char *recData;

        enum headerFlags
            {
            fIsESM                  = 0x00000001,
            //fIsTaken              = 0x00000002, //From OBSE, unconfirmed, requires fIsDeleted also be set
            fIsDeleted              = 0x00000020,
            fIsBorderRegion         = 0x00000040,
            fIsTurnOffFire          = 0x00000080,
            fIsCastsShadows         = 0x00000200,
            fIsQuestOrPersistent    = 0x00000400,
            fIsInitiallyDisabled    = 0x00000800,
            fIsIgnored              = 0x00001000,
            //fIsTemporary          = 0x00004000, //From OBSE, unconfirmed
            fIsVisibleWhenDistant   = 0x00008000,
            fIsDangerousOrOffLimits = 0x00020000,
            fIsCompressed           = 0x00040000,
            fIsCantWait             = 0x00080000
            };

        enum cBashRecordFlags
            {
            _fIsLoaded = 0x80000000 //Not an actual flag. Used only by CBash internally. Won't be written.
            };

    public:
        UINT32 flags;
        FORMID formID;
        UINT32 flagsUnk; //Version Control Info 1, FNV
        //UINT16 formVersion; //FNV
        //UINT8 versionControl2[2]; //FNV

        Record(unsigned char *_recData=NULL);
        virtual ~Record();

        virtual SINT32 Unload() abstract {};
        //virtual UINT32 GetSize(bool forceCalc=false) abstract {};
        virtual UINT32 GetType() abstract {};
        virtual STRING GetStrType() abstract {};
        virtual SINT32 WriteRecord(FileWriter &writer) abstract {};
        virtual SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize) abstract {};

        virtual UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        virtual void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        virtual bool SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        virtual void DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        virtual UINT32 GetParentType();

        virtual bool IsKeyedByEditorID();
        virtual bool HasSubRecords();

        virtual bool VisitSubRecords(const UINT32 &RecordType, RecordOp &op);
        virtual bool VisitFormIDs(FormIDOp &op);

        virtual bool Read();
        bool IsValid(FormIDResolver &expander);
        //FormIDResolver& GetCorrectExpander(std::vector<FormIDResolver *> &Expanders, FormIDResolver &defaultResolver);
        virtual UINT32 Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);

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
        bool IsHeaderUnknownFlagMask(UINT32 Mask, bool Exact=false);
        void SetHeaderUnknownFlagMask(UINT32 Mask);
        bool IsLoaded();
        void IsLoaded(bool value);
        bool IsChanged(bool value=false);
    };

class FNVRecord : public Record
    {
    protected:
        enum FNVHeaderFlags
            {
            fIsESM                              = 0x00000001,
            fIsTaken                            = 0x00000002, //From OBSE, unconfirmed, requires fIsDeleted also be set
            fUnknown1                           = 0x00000004,
            fUnknown2                           = 0x00000008,
            fUnknown3                           = 0x00000010,
            fIsDeleted                          = 0x00000020,
            fIsBorderRegion                     = 0x00000040, //Has Tree LOD / Constant / Hidden From Local Map (FNV)
            fIsTurnOffFire                      = 0x00000080,
            fIsInaccessible                     = 0x00000100, // (FNV)
            fIsCastsShadows                     = 0x00000200, //On Local Map / Motion Blur (FNV)
            fIsQuestOrPersistent                = 0x00000400,
            fIsInitiallyDisabled                = 0x00000800,
            fIsIgnored                          = 0x00001000,
            fIsNoVoiceFilter                    = 0x00002000, // (FNV)
            fIsTemporary                        = 0x00004000, //From OBSE, unconfirmed
            fIsVisibleWhenDistant               = 0x00008000,
            fIsRandomAnimStartOrHighPriorityLOD = 0x00010000, // (FNV)
            fIsDangerousOrOffLimits             = 0x00020000, // Radio Station (Talking Activator) (FNV)
            fIsCompressed                       = 0x00040000,
            fIsCantWait                         = 0x00080000, // Platform Specific Texture (FNV)
            fUnknown4                           = 0x00100000,
            fUnknown5                           = 0x00200000,
            fUnknown6                           = 0x00400000,
            fUnknown7                           = 0x00800000,
            fUnknown8                           = 0x01000000,
            fIsObstacleOrNoAIAcquire            = 0x02000000, // (FNV)
            fIsNavMeshFilter                    = 0x03000000, //? (FNV)
            //fIsNavMeshBoundBox                = 0x04000000, //? (FNV)
            fIsNavMeshBoundBox                  = 0x08000000, // (FNV)
            fIsNonPipboyOrAutoReflected         = 0x10000000, // (FNV)
            fIsChildUsableOrAutoRefracted       = 0x20000000, // (FNV)
            fIsNavMeshGround                    = 0x40000000, // (FNV)
            fUnknown9                           = 0x80000000
            };

    public:
        UINT16 formVersion; //FNV
        UINT8  versionControl2[2]; //FNV

        FNVRecord(unsigned char *_recData=NULL);
        virtual ~FNVRecord();

        bool Read();
        UINT32 Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders);
    };