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
class AMMORecord : public FNVRecord //Ammunition
    {
    private:
        #pragma pack(push)
        #pragma pack(1)
        struct AMMODATA
            {
            FLOAT32 speed; //Speed
            UINT8   flags; //Flags
            UINT8   unused[3]; //Unused
            SINT32  value; //Value
            UINT8   clipRounds; //Clip Rounds

            AMMODATA();
            ~AMMODATA();

            bool operator ==(const AMMODATA &other) const;
            bool operator !=(const AMMODATA &other) const;
            };
        #pragma pack(pop)

        struct AMMODAT2
            {
            UINT32  projectilesPerShot; //Proj. per Shot
            FORMID  projectile; //Projectile
            FLOAT32 weight; //Weight
            //Below are not always present on chunk...
            FORMID  consumedAmmo; //Consumed Ammo
            FLOAT32 consumedPercentage; //Consumed Percentage

            AMMODAT2();
            ~AMMODAT2();

            bool operator ==(const AMMODAT2 &other) const;
            bool operator !=(const AMMODAT2 &other) const;
            };

        enum flagsFlags
            {
            fIsNotNormalWeapon = 0x01,
            fIsNonPlayable     = 0x02
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSimpleSubRecord<FORMID> YNAM; //Sound - Pick Up
        OptSimpleSubRecord<FORMID> ZNAM; //Sound - Drop
        ReqSubRecord<AMMODATA> DATA; //Ammo Data
        OptSubRecord<AMMODAT2> DAT2; //Extra Ammo Data
        StringRecord ONAM; //Short Name
        StringRecord QNAM; //Abbrev.
        UnorderedSparseArray<FORMID> RCIL; //Ammo Effects

        AMMORecord(unsigned char *_recData=NULL);
        AMMORecord(AMMORecord *srcRecord);
        ~AMMORecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNotNormalWeapon();
        void   IsNotNormalWeapon(bool value);
        bool   IsNonPlayable();
        void   IsNonPlayable(bool value);
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

        bool operator ==(const AMMORecord &other) const;
        bool operator !=(const AMMORecord &other) const;
        bool equals(Record *other);
    };
}