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
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class QUSTRecord : public FNVRecord //Quest
    {
    private:
        struct QUSTDATA
            {
            UINT8   flags, priority, unused1[2];
            FLOAT32 delay;

            QUSTDATA();
            ~QUSTDATA();

            bool operator ==(const QUSTDATA &other) const;
            bool operator !=(const QUSTDATA &other) const;
            };

        struct QUSTEntry //Log Entry
            {
            ReqSimpleSubRecord<UINT8> QSDT; //Stage Flags
            std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions
            StringRecord CNAM; //Log Entry
            OptSubRecord<FNVMINSCRIPT> Script; //Embedded Script
            OptSimpleSubRecord<FORMID> NAM0; //Next Quest


            enum entriesFlags
                {
                fIsCompletes = 0x00000001,
                fIsFailed = 0x00000002
                };

            QUSTEntry();
            ~QUSTEntry();

            bool IsCompletes();
            void IsCompletes(bool value);
            bool IsFailed();
            void IsFailed(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            bool operator ==(const QUSTEntry &other) const;
            bool operator !=(const QUSTEntry &other) const;
            };

        struct QUSTStage //Stage
            {
            ReqSimpleSubRecord<SINT16> INDX; //Stage Index
            std::vector<QUSTEntry *> Entries; //Log Entries

            QUSTStage();
            ~QUSTStage();

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
            std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions

            enum targetsFlags
                {
                fIsIgnoresLocks = 0x00000001
                };

            QUSTTarget();
            ~QUSTTarget();

            bool IsIgnoresLocks();
            void IsIgnoresLocks(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            bool operator ==(const QUSTTarget &other) const;
            bool operator !=(const QUSTTarget &other) const;
            };

        struct QUSTObjective
            {
            ReqSimpleSubRecord<SINT32> QOBJ; //Objective Index
            StringRecord NNAM; //Description
            std::vector<QUSTTarget *> Targets;

            QUSTObjective();
            ~QUSTObjective();

            bool operator ==(const QUSTObjective &other) const;
            bool operator !=(const QUSTObjective &other) const;
            };

        enum schrFlags
            {
            fIsEnabled = 0x0001
            };
    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<FORMID> SCRI; //Script
        StringRecord FULL; //Name
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OptSubRecord<QUSTDATA> DATA; //General
        std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions
        std::vector<QUSTStage *> Stages;
        std::vector<QUSTObjective *> Objectives;

        QUSTRecord(unsigned char *_recData=NULL);
        QUSTRecord(QUSTRecord *srcRecord);
        ~QUSTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool IsScriptEnabled();
        void IsScriptEnabled(bool value);
        bool IsScriptFlagMask(UINT16 Mask, bool Exact=false);
        void SetScriptFlagMask(UINT16 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(_FileHandler &SaveHandler);

        bool operator ==(const QUSTRecord &other) const;
        bool operator !=(const QUSTRecord &other) const;
    };
}