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
class SPELRecord : public FNVRecord //Actor Effect
    {
    private:
        struct SPELSPIT
            {
            UINT32  spellType, cost, levelType; // Type, Cost (Unused), Level (Unused)
            UINT8   flags, unused1[3];

            SPELSPIT();
            ~SPELSPIT();

            bool operator ==(const SPELSPIT &other) const;
            bool operator !=(const SPELSPIT &other) const;
            };

        enum flagsFlags
            {
            fIsManualCost            = 0x00000001,
            fIsStartSpell            = 0x00000004,
            fIsSilenceImmune         = 0x0000000A,
            fIsAreaEffectIgnoresLOS  = 0x00000010,
            fIsScriptAlwaysApplies   = 0x00000020,
            fIsDisallowAbsorbReflect = 0x00000040,
            fIsTouchExplodesWOTarget = 0x00000080
            };

        enum eSpellType
            {
            eActorEffect = 0,
            eDisease     = 1,
            ePower       = 2,
            eLesserPower = 3,
            eAbility     = 4,
            ePoison      = 5,
            eAddiction   = 10
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        ReqSubRecord<SPELSPIT> SPIT; //Data
        UnorderedSparseArray<FNVEffect *> Effects; //Effects

        SPELRecord(unsigned char *_recData=NULL);
        SPELRecord(SPELRecord *srcRecord);
        ~SPELRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsManualCost();
        void   IsManualCost(bool value);
        bool   IsStartSpell();
        void   IsStartSpell(bool value);
        bool   IsSilenceImmune();
        void   IsSilenceImmune(bool value);
        bool   IsAreaEffectIgnoresLOS();
        void   IsAreaEffectIgnoresLOS(bool value);
        bool   IsAEIgnoresLOS();
        void   IsAEIgnoresLOS(bool value);
        bool   IsScriptAlwaysApplies();
        void   IsScriptAlwaysApplies(bool value);
        bool   IsDisallowAbsorbReflect();
        void   IsDisallowAbsorbReflect(bool value);
        bool   IsDisallowAbsorb();
        void   IsDisallowAbsorb(bool value);
        bool   IsDisallowReflect();
        void   IsDisallowReflect(bool value);
        bool   IsTouchExplodesWOTarget();
        void   IsTouchExplodesWOTarget(bool value);
        bool   IsTouchExplodes();
        void   IsTouchExplodes(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsActorEffect();
        void   IsActorEffect(bool value);
        bool   IsDisease();
        void   IsDisease(bool value);
        bool   IsPower();
        void   IsPower(bool value);
        bool   IsLesserPower();
        void   IsLesserPower(bool value);
        bool   IsAbility();
        void   IsAbility(bool value);
        bool   IsPoison();
        void   IsPoison(bool value);
        bool   IsAddiction();
        void   IsAddiction(bool value);
        bool   IsType(UINT32 Type);
        void   SetType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const SPELRecord &other) const;
        bool operator !=(const SPELRecord &other) const;
    };
}