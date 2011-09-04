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

namespace FNV
{
class TERMRecord : public FNVRecord //Terminal
    {
    private:
        struct TERMDNAM
            {
            UINT8   difficultyType, flags, serverType, unused1; //unused1 not always present

            TERMDNAM();
            ~TERMDNAM();

            bool operator ==(const TERMDNAM &other) const;
            bool operator !=(const TERMDNAM &other) const;
            };

        struct TERMMenu
            {
            StringRecord ITXT; //Text
            StringRecord RNAM; //Result Text
            ReqSimpleSubRecord<UINT8> ANAM; //Flags
            OptSimpleSubRecord<FORMID> INAM; //Display Note
            OptSimpleSubRecord<FORMID> TNAM; //Sub Menu
            ReqSubRecord<FNVSCHR> SCHR;
            RawRecord SCDA;
            NonNullStringRecord SCTX;
            OrderedSparseArray<GENVARS *, sortVARS> VARS;
            OrderedSparseArray<GENSCR_ *> SCR_;
            OrderedSparseArray<FNVCTDA *> CTDA; //Conditions

            enum flagFlags
                {
                fIsAddNote     = 0x01,
                fIsForceRedraw = 0x02
                };

            enum schrFlags
                {
                fIsEnabled = 0x0001
                };

            enum scriptTypeTypes
                {
                eObject = 0x0000,
                eQuest  = 0x0001,
                eEffect = 0x0100
                };

            void Write(FileWriter &writer);

            bool IsAddNote();
            void IsAddNote(bool value);
            bool IsForceRedraw();
            void IsForceRedraw(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            bool IsScriptEnabled();
            void IsScriptEnabled(bool value);
            bool IsScriptFlagMask(UINT16 Mask, bool Exact=false);
            void SetScriptFlagMask(UINT16 Mask);

            bool IsObject();
            void IsObject(bool value);
            bool IsQuest();
            void IsQuest(bool value);
            bool IsEffect();
            void IsEffect(bool value);
            bool IsType(UINT16 Type);
            void SetType(UINT16 Type);

            bool operator ==(const TERMMenu &other) const;
            bool operator !=(const TERMMenu &other) const;
            };

        enum difficultyTypes
            {
            eVeryEasy = 0,
            eEasy,
            eAverage,
            eHard,
            eVeryHard,
            eRequiresKey
            };

        enum flagsFlags
            {
            fIsLeveled                            = 0x01,
            fIsUnlocked                           = 0x02,
            fIsAlternateColors                    = 0x04,
            fIsHideWelcomeTextWhenDisplayingImage = 0x08
            };

        enum serverTypes
            {
            eServer1 = 0,
            eServer2,
            eServer3,
            eServer4,
            eServer5,
            eServer6,
            eServer7,
            eServer8,
            eServer9,
            eServer10
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        StringRecord DESC; //Description
        OptSimpleSubRecord<FORMID> SNAM; //Sound - Looping
        OptSimpleSubRecord<FORMID> PNAM; //Password Note
        ReqSubRecord<TERMDNAM> DNAM; //Data
        UnorderedSparseArray<TERMMenu *> Menus; //Menu Items;

        TERMRecord(unsigned char *_recData=NULL);
        TERMRecord(TERMRecord *srcRecord);
        ~TERMRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsLeveled();
        void   IsLeveled(bool value);
        bool   IsUnlocked();
        void   IsUnlocked(bool value);
        bool   IsAlternateColors();
        void   IsAlternateColors(bool value);
        bool   IsHideWelcomeTextWhenDisplayingImage();
        void   IsHideWelcomeTextWhenDisplayingImage(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsVeryEasy();
        void   IsVeryEasy(bool value);
        bool   IsEasy();
        void   IsEasy(bool value);
        bool   IsAverage();
        void   IsAverage(bool value);
        bool   IsHard();
        void   IsHard(bool value);
        bool   IsVeryHard();
        void   IsVeryHard(bool value);
        bool   IsRequiresKey();
        void   IsRequiresKey(bool value);
        bool   IsLockType(UINT8 Type);
        void   SetLockType(UINT8 Type);

        bool   IsServer1();
        void   IsServer1(bool value);
        bool   IsServer2();
        void   IsServer2(bool value);
        bool   IsServer3();
        void   IsServer3(bool value);
        bool   IsServer4();
        void   IsServer4(bool value);
        bool   IsServer5();
        void   IsServer5(bool value);
        bool   IsServer6();
        void   IsServer6(bool value);
        bool   IsServer7();
        void   IsServer7(bool value);
        bool   IsServer8();
        void   IsServer8(bool value);
        bool   IsServer9();
        void   IsServer9(bool value);
        bool   IsServer10();
        void   IsServer10(bool value);
        bool   IsServerType(UINT8 Type);
        void   SetServerType(UINT8 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const TERMRecord &other) const;
        bool operator !=(const TERMRecord &other) const;
        bool equals(Record *other);
    };
}