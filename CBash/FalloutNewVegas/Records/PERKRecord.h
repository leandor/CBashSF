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
class PERKRecord : public FNVRecord //Perk
    {
    private:
        struct PERKDATA
            {
            UINT8   trait, minLevel, ranks, playable, hidden;

            PERKDATA();
            ~PERKDATA();

            bool operator ==(const PERKDATA &other) const;
            bool operator !=(const PERKDATA &other) const;
            };

        struct PERKPRKE // Header
            {
            UINT8   perkType, rank, priority;

            PERKPRKE();
            ~PERKPRKE();

            bool operator ==(const PERKPRKE &other) const;
            bool operator !=(const PERKPRKE &other) const;
            };

        struct PRKEDATA // Effect Data
            {
            union //Determined by PRKE->perkType
                {
                struct PRKEDATA1 // Quest + Stage
                    {
                    FORMID  quest;
                    SINT8   stage;
                    UINT8   unused1[3];
                    } DATA1;
                struct PRKEDATA2 // Ability
                    {
                    FORMID  ability;
                    } DATA2;
                struct PRKEDATA3 // Entry Point
                    {
                    UINT8   entry, func, count;
                    } DATA3;
                };

            PRKEDATA();
            ~PRKEDATA();

            bool operator ==(const PRKEDATA &other) const;
            bool operator !=(const PRKEDATA &other) const;
            };

        struct PERKCondition // Perk Condition
            {
            OptSimpleSubRecord<SINT8> PRKC; //Run On
            std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions

            bool   operator ==(const PERKCondition &other) const;
            bool   operator !=(const PERKCondition &other) const;
            };

        struct PERKEPFD // Data
            {
            union //Determined mainly by EPFT->value
                {
                UINT8   unknown[4]; //default
                FLOAT32 float1; // EPFT->value == 1
                struct EPFDDATA1 // Quest + Stage
                    {
                    FLOAT32 float1;
                    FLOAT32 float2;
                    } DATA1; // EPFT->value == 2
                FORMID leveledItem; // EPFT->value == 3
                UINT8  unused; // EPFT->value == 4
                struct EPFDDATA2 // Ability
                    {
                    UINT32  actorValue;
                    FLOAT32 float1;
                    } DATA2; // EPFT->value == 2 and DATA->DATA3.func == 5
                };

            PERKEPFD();
            ~PERKEPFD();

            bool operator ==(const PERKEPFD &other) const;
            bool operator !=(const PERKEPFD &other) const;
            };

        struct PERKEffect // Effect
            {
            OptSubRecord<PERKPRKE> PRKE; //Header
            OptSubRecord<PRKEDATA> DATA; //Effect Data
            std::vector<PERKConditions *> Conditions; // Perk Conditions

            OptSimpleSubRecord<UINT8> EPFT; //Type
            OptSubRecord<PERKEPFD> EPFD; //Data
            StringRecord EPF2; //Button Label
            OptSimpleSubRecord<UINT16> EPF3; //Script Flags
            ReqSubRecord<FNVSCHR> SCHR;
            RawRecord SCDA;
            NonNullStringRecord SCTX;
            std::vector<GENVARS *> VARS;
            std::vector<ReqSubRecord<GENSCR_> *> SCR_;
            //OptSubRecord<GENPRKF> PRKF; //End Marker

            enum epf3Flags
                {
                fIsRunImmediately = 0x0001
                };

            enum schrFlags
                {
                fIsEnabled = 0x0001
                };

            bool   IsRunImmediately();
            void   IsRunImmediately(bool value);
            bool   IsFlagMask(UINT16 Mask, bool Exact=false);
            void   SetFlagMask(UINT16 Mask);

            bool IsScriptEnabled();
            void IsScriptEnabled(bool value);
            bool IsScriptFlagMask(UINT16 Mask, bool Exact=false);
            void SetScriptFlagMask(UINT16 Mask);

            bool   operator ==(const PERKEffect &other) const;
            bool   operator !=(const PERKEffect &other) const;
            };

        enum traitTypes
            {
            eNotTrait = 0,
            eTrait
            };

        enum playableTypes
            {
            eNotPlayable = 0,
            ePlayable
            };

        enum hiddenTypes
            {
            eNotHidden = 0,
            eHidden
            };

        enum perkTypeTypes
            {
            eQuestStage = 0,
            eAbility,
            eEntryPoint
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions
        OptSubRecord<PERKDATA> DATA; //Data
        std::vector<ReqSubRecord<PERKEffect> *> PRKE; //Effects

        PERKRecord(unsigned char *_recData=NULL);
        PERKRecord(PERKRecord *srcRecord);
        ~PERKRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNotTrait();
        void   IsNotTrait(bool value);
        bool   IsTrait();
        void   IsTrait(bool value);
        bool   IsTraitType(UINT8 Type, bool Exact=false);
        void   SetTraitType(UINT8 Type);

        bool   IsNotPlayable();
        void   IsNotPlayable(bool value);
        bool   IsPlayable();
        void   IsPlayable(bool value);
        bool   IsPlayableType(UINT8 Type, bool Exact=false);
        void   SetPlayableType(UINT8 Type);

        bool   IsNotHidden();
        void   IsNotHidden(bool value);
        bool   IsHidden();
        void   IsHidden(bool value);
        bool   IsHiddenType(UINT8 Type, bool Exact=false);
        void   SetHiddenType(UINT8 Type);

        bool   IsQuestStage();
        void   IsQuestStage(bool value);
        bool   IsAbility();
        void   IsAbility(bool value);
        bool   IsEntryPoint();
        void   IsEntryPoint(bool value);
        bool   IsType(UINT8 Type, bool Exact=false);
        void   SetType(UINT8 Type);

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

        bool operator ==(const PERKRecord &other) const;
        bool operator !=(const PERKRecord &other) const;
    };
}