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
class IDLERecord : public FNVRecord //Idle Animation
    {
    private:
        struct IDLEDATA
            {
            UINT8   group, minLooping, maxLooping, unused1;
            SINT16  replayDelay;
            //Below are not always present on chunk...
            UINT8   flags, unused2;

            IDLEDATA();
            ~IDLEDATA();

            bool operator ==(const IDLEDATA &other) const;
            bool operator !=(const IDLEDATA &other) const;
            };

        enum groupType
            {
            eIdle        = 0,
            eMovement    = 1,
            eLeftArm     = 2,
            eLeftHand    = 3,
            eWeapon      = 4,
            eWeaponUp    = 5,
            eWeaponDown  = 6,
            eSpecialIdle = 7,
            eWholeBody   = 20,
            eUpperBody   = 21
            };

        enum groupFlag
            {
            fIsUnknown1      = 0x40,
            fIsNotReturnFile = 0x80
            };

        enum flagsFlags
            {
            fIsNoAttacking = 0x01
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<FNVMODEL> MODL; //Model
        OrderedSparseArray<FNVCTDA *> CTDA; //Conditions
        UnorderedPackedArray<FORMID> ANAM; //Related Idle Animations
        ReqSubRecord<IDLEDATA> DATA; //Data

        IDLERecord(unsigned char *_recData=NULL);
        IDLERecord(IDLERecord *srcRecord);
        ~IDLERecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNoAttacking();
        void   IsNoAttacking(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsIdle();
        void   IsIdle(bool value);
        bool   IsMovement();
        void   IsMovement(bool value);
        bool   IsLeftArm();
        void   IsLeftArm(bool value);
        bool   IsLeftHand();
        void   IsLeftHand(bool value);
        bool   IsWeapon();
        void   IsWeapon(bool value);
        bool   IsWeaponUp();
        void   IsWeaponUp(bool value);
        bool   IsWeaponDown();
        void   IsWeaponDown(bool value);
        bool   IsSpecialIdle();
        void   IsSpecialIdle(bool value);
        bool   IsWholeBody();
        void   IsWholeBody(bool value);
        bool   IsUpperBody();
        void   IsUpperBody(bool value);
        bool   IsType(UINT8 Type);
        void   SetType(UINT8 Type);

        bool   IsUnknown1();
        void   IsUnknown1(bool value);
        bool   IsNotReturnFile();
        void   IsNotReturnFile(bool value);
        bool   IsReturnFile();
        void   IsReturnFile(bool value);
        bool   IsIdleFlagMask(UINT8 Mask, bool Exact=false);
        void   SetIdleFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const IDLERecord &other) const;
        bool operator !=(const IDLERecord &other) const;
    };
}