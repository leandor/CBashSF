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
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace Ob
{
class QUSTRecord : public Record //Quest
    {
    private:
        struct QUSTDATA
            {
            UINT8   flags, priority;

            QUSTDATA();
            ~QUSTDATA();

            bool operator ==(const QUSTDATA &other) const;
            bool operator !=(const QUSTDATA &other) const;
            };

        struct QUSTEntry //Log Entry
            {
            ReqSimpleSubRecord<UINT8> QSDT; //Stage Flags
            OrderedSparseArray<GENCTDA *> CTDA; //Conditions
            StringRecord CNAM; //Log Entry
            ReqSubRecord<GENSCHR> SCHR; //Basic Script Data
            RawRecord SCDA; //Unknown (Script Header?)
            NonNullStringRecord SCTX; //Script Source
            OrderedSparseArray<GENSCR_ *> SCR_; //References

            enum entriesFlags
                {
                fIsCompletes = 0x00000001
                };

            enum scriptTypeTypes
                {
                eObject = 0x0000,
                eQuest  = 0x0001,
                eEffect = 0x0100
                };

            bool IsCompletes();
            void IsCompletes(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            bool IsObject();
            void IsObject(bool value);
            bool IsQuest();
            void IsQuest(bool value);
            bool IsEffect();
            void IsEffect(bool value);
            bool IsType(UINT16 Type);
            void SetType(UINT16 Type);

            void Write(FileWriter &writer);

            bool operator ==(const QUSTEntry &other) const;
            bool operator !=(const QUSTEntry &other) const;
            };

        struct QUSTStage //Stage
            {
            ReqSimpleSubRecord<UINT16> INDX; //Stage Index
            UnorderedSparseArray<QUSTEntry *> Entries; //Log Entries

            void Write(FileWriter &writer);

            bool operator ==(const QUSTStage &other) const;
            bool operator !=(const QUSTStage &other) const;
            };

        struct QUSTQSTA //Target
            {
            FORMID  targetId; //Target
            UINT8   flags, unused1[3]; //Flags, Unused

            QUSTQSTA();
            ~QUSTQSTA();

            bool operator ==(const QUSTQSTA &other) const;
            bool operator !=(const QUSTQSTA &other) const;
            };

        struct QUSTTarget //Target
            {
            ReqSubRecord<QUSTQSTA> QSTA; //Target
            OrderedSparseArray<GENCTDA *> CTDA; //Conditions

            enum targetsFlags
                {
                fIsIgnoresLocks = 0x00000001
                };

            bool IsIgnoresLocks();
            void IsIgnoresLocks(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            void Write(FileWriter &writer);

            bool operator ==(const QUSTTarget &other) const;
            bool operator !=(const QUSTTarget &other) const;
            };

        enum flagsFlags
            {
            fIsStartEnabled   = 0x00000001,
            fIsRepeatedTopics = 0x00000004,
            fIsRepeatedStages = 0x00000008
            };

    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<FORMID> SCRI; //Script
        StringRecord FULL; //Name
        StringRecord ICON; //Large Icon Filename
        ReqSubRecord<QUSTDATA> DATA; //General
        OrderedSparseArray<GENCTDA *> CTDA; //Conditions
        UnorderedSparseArray<QUSTStage *> Stages; //Stages
        UnorderedSparseArray<QUSTTarget *> Targets; //Targets

        QUSTRecord(unsigned char *_recData=NULL);
        QUSTRecord(QUSTRecord *srcRecord);
        ~QUSTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsStartEnabled();
        void   IsStartEnabled(bool value);
        bool   IsRepeatedTopics();
        void   IsRepeatedTopics(bool value);
        bool   IsRepeatedStages();
        void   IsRepeatedStages(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const QUSTRecord &other) const;
        bool operator !=(const QUSTRecord &other) const;
        bool equals(Record *other);
    };
}