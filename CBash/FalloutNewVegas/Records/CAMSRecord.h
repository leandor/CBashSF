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
class CAMSRecord : public FNVRecord //Camera Shot
    {
    private:
        struct CAMSDATA //Data
            {
            UINT32  action, location, target, flags; //Action, Location, Target, Flags
            FLOAT32 playerTimeMult, targetTimeMult, globalTimeMult; //Time Multipliers
            FLOAT32 maxTime, minTime, targetPercentBetweenActors; //Max Time, Min Time, Target % Between Actors

            CAMSDATA();
            ~CAMSDATA();

            bool operator ==(const CAMSDATA &other) const;
            bool operator !=(const CAMSDATA &other) const;
            };

        enum actionTypes
            {
            eShoot = 0,
            eFly,
            eHit,
            eZoom
            };

        enum locationTypes
            {
            eAttacker = 0,
            eProjectile,
            eTarget
            };

        enum targetTypes
            {
            eAttacker = 0,
            eProjectile,
            eTarget
            };

        enum flagFlags
            {
            fIsPosFollowsLocation = 0x00000001,
            fIsPosFollowsTarget   = 0x00000002,
            fIsDontFollowBone     = 0x00000004,
            fIsFirstPersonCamera  = 0x00000008,
            fIsNoTracer           = 0x00000010,
            fIsStartAtTimeZero    = 0x00000020
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<CAMSDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> MNAM; //Image Space Modifier

        CAMSRecord(unsigned char *_recData=NULL);
        CAMSRecord(CAMSRecord *srcRecord);
        ~CAMSRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsPosFollowsLocation();
        void   IsPosFollowsLocation(bool value);
        bool   IsPosFollowsTarget();
        void   IsPosFollowsTarget(bool value);
        bool   IsDontFollowBone();
        void   IsDontFollowBone(bool value);
        bool   IsFirstPersonCamera();
        void   IsFirstPersonCamera(bool value);
        bool   IsNoTracer();
        void   IsNoTracer(bool value);
        bool   IsStartAtTimeZero();
        void   IsStartAtTimeZero(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsActionShoot();
        void   IsActionShoot(bool value);
        bool   IsActionFly();
        void   IsActionFly(bool value);
        bool   IsActionHit();
        void   IsActionHit(bool value);
        bool   IsActionZoom();
        void   IsActionZoom(bool value);
        bool   IsActionType(UINT32 Type);
        void   SetActionType(UINT32 Type);

        bool   IsLocationAttacker();
        void   IsLocationAttacker(bool value);
        bool   IsLocationProjectile();
        void   IsLocationProjectile(bool value);
        bool   IsLocationTarget();
        void   IsLocationTarget(bool value);
        bool   IsLocationType(UINT32 Type);
        void   SetLocationType(UINT32 Type);

        bool   IsTargetAttacker();
        void   IsTargetAttacker(bool value);
        bool   IsTargetProjectile();
        void   IsTargetProjectile(bool value);
        bool   IsTargetTarget();
        void   IsTargetTarget(bool value);
        bool   IsTargetType(UINT32 Type);
        void   SetTargetType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CAMSRecord &other) const;
        bool operator !=(const CAMSRecord &other) const;
        bool equals(Record *other);
    };
}