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
class INGRRecord : public FNVRecord //Ingredient
    {
    private:
        enum flagsFlags
            {
            fIsNoAutoCalc = 0x00000001,
            fIsFood       = 0x00000002
            };

        enum eEquipTypes
            {
            eNone    = -1,
            eBigGuns = 0,
            eEnergyWeapons,
            eSmallGuns,
            eMeleeWeapons,
            eUnarmedWeapon,
            eThrownWeapons,
            eMine,
            eBodyWear,
            eHeadWear,
            eHandWear,
            eChems,
            eStimpack,
            eEdible,
            eAlcohol
            };
    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSimpleSubRecord<SINT32> ETYP; //Equipment Type
        ReqSimpleFloatSubRecord<flt_0> DATA; //Weight
        ReqSubRecord<GENENIT> ENIT; //Effect Data
        UnorderedSparseArray<FNVEffect *> Effects; //Effects

        INGRRecord(unsigned char *_recData=NULL);
        INGRRecord(INGRRecord *srcRecord);
        ~INGRRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNoAutoCalc();
        void   IsNoAutoCalc(bool value);
        bool   IsFood();
        void   IsFood(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsBigGuns();
        void   IsBigGuns(bool value);
        bool   IsEnergyWeapons();
        void   IsEnergyWeapons(bool value);
        bool   IsSmallGuns();
        void   IsSmallGuns(bool value);
        bool   IsMeleeWeapons();
        void   IsMeleeWeapons(bool value);
        bool   IsUnarmedWeapon();
        void   IsUnarmedWeapon(bool value);
        bool   IsThrownWeapons();
        void   IsThrownWeapons(bool value);
        bool   IsMine();
        void   IsMine(bool value);
        bool   IsBodyWear();
        void   IsBodyWear(bool value);
        bool   IsHeadWear();
        void   IsHeadWear(bool value);
        bool   IsHandWear();
        void   IsHandWear(bool value);
        bool   IsChems();
        void   IsChems(bool value);
        bool   IsStimpack();
        void   IsStimpack(bool value);
        bool   IsEdible();
        void   IsEdible(bool value);
        bool   IsAlcohol();
        void   IsAlcohol(bool value);
        bool   IsEquipmentType(SINT32 Type);
        void   SetEquipmentType(SINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const INGRRecord &other) const;
        bool operator !=(const INGRRecord &other) const;
        bool equals(Record *other);
    };
}