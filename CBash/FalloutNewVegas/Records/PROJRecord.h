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
class PROJRecord : public FNVRecord //Projectile
    {
    private:
        struct PROJDATA
            {
            UINT16  flags, projType;
            FLOAT32 gravity, speed, range;
            FORMID  light, flash;
            FLOAT32 tracerChance, altExplProximityTrigger, altExplProximityTimer;
            FORMID  explosion, sound;
            FLOAT32 flashDuration, fadeDuration, impactForce;
            FORMID  soundCountdown, soundDisable, defaultWeaponSource;
            //Below are not always in chunk...
            FLOAT32 rotX, rotY, rotZ, bouncyMult;

            PROJDATA();
            ~PROJDATA();

            bool operator ==(const PROJDATA &other) const;
            bool operator !=(const PROJDATA &other) const;
            };

        enum flagsFlags
            {
            fIsHitscan              = 0x0001,
            fIsExplosion            = 0x0002,
            fIsAltTrigger           = 0x0004,
            fIsMuzzleFlash          = 0x0008,
            fIsDisableable          = 0x0020,
            fIsPickupable           = 0x0040,
            fIsSupersonic           = 0x0080,
            fIsPinsLimbs            = 0x0100,
            fIsPassSmallTransparent = 0x0200,
            fIsDetonates            = 0x0400,
            fIsRotation             = 0x0800
            };

        enum projTypeTypes
            {
            eMissile        = 1,
            eLobber         = 2,
            eBeam           = 4,
            eFlame          = 8,
            eContinuousBeam = 16
            };

        enum soundLevelTypes
            {
            eLoud = 0,
            eNormal,
            eSilent
            };
    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        ReqSubRecord<PROJDATA> DATA; //Data
        StringRecord NAM1; //Model Filename
        RawRecord NAM2; //Texture Files Hashes
        OptSimpleSubRecord<UINT32> VNAM; //Sound Level

        PROJRecord(unsigned char *_recData=NULL);
        PROJRecord(PROJRecord *srcRecord);
        ~PROJRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHitscan();
        void   IsHitscan(bool value);
        bool   IsExplosion();
        void   IsExplosion(bool value);
        bool   IsAltTrigger();
        void   IsAltTrigger(bool value);
        bool   IsMuzzleFlash();
        void   IsMuzzleFlash(bool value);
        bool   IsDisableable();
        void   IsDisableable(bool value);
        bool   IsPickupable();
        void   IsPickupable(bool value);
        bool   IsSupersonic();
        void   IsSupersonic(bool value);
        bool   IsPinsLimbs();
        void   IsPinsLimbs(bool value);
        bool   IsPassSmallTransparent();
        void   IsPassSmallTransparent(bool value);
        bool   IsDetonates();
        void   IsDetonates(bool value);
        bool   IsRotation();
        void   IsRotation(bool value);
        bool   IsFlagMask(UINT16 Mask, bool Exact=false);
        void   SetFlagMask(UINT16 Mask);

        bool   IsMissile();
        void   IsMissile(bool value);
        bool   IsLobber();
        void   IsLobber(bool value);
        bool   IsBeam();
        void   IsBeam(bool value);
        bool   IsFlame();
        void   IsFlame(bool value);
        bool   IsContinuousBeam();
        void   IsContinuousBeam(bool value);
        bool   IsType(UINT16 Type);
        void   SetType(UINT16 Type);

        bool   IsLoud();
        void   IsLoud(bool value);
        bool   IsNormal();
        void   IsNormal(bool value);
        bool   IsSilent();
        void   IsSilent(bool value);
        bool   IsSoundLevelType(UINT32 Type);
        void   SetSoundLevelType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const PROJRecord &other) const;
        bool operator !=(const PROJRecord &other) const;
        bool equals(Record *other);
    };
}