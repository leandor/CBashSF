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
class RGDLRecord : public Record //Ragdoll
    {
    private:
        struct RGDLDATA // General Data
            {
            UINT32  numBones;
            UINT8   unused1[4], feedbackType;
            UINT8   footIKType, lookIKType, grabIKType; //Broken, don't use
            UINT8   matchPoseType, unused2;

            RGDLDATA();
            ~RGDLDATA();

            bool operator ==(const RGDLDATA &other) const;
            bool operator !=(const RGDLDATA &other) const;
            };

        struct RGDLRAFD // Feedback Data
            {
            FLOAT32 blendAmt, hierachyGain, posGain,
                    velGain, accGain, snapGain, velDamping,
                    snapLinVel, snapAngVel, snapLinDist,
                    snapAngDist, posLinVel, posAngVel;
            SINT32  posProjectileVel, posMeleeVel;

            RGDLRAFD();
            ~RGDLRAFD();

            bool operator ==(const RGDLRAFD &other) const;
            bool operator !=(const RGDLRAFD &other) const;
            };

        struct RGDLRAPS // Pose Matching Data
            {
            UINT16  matchBones1, matchBones2, matchBones3;
            UINT8   flags, unused;
            FLOAT32 motorsStrength, poseDelay, errorAllowance,
                    disableDisplacement;

            RGDLRAPS();
            ~RGDLRAPS();

            bool operator ==(const RGDLRAPS &other) const;
            bool operator !=(const RGDLRAPS &other) const;
            };

        enum flagsFlags
            {
            fIsDisableOnMove = 0x01
            };

        enum feedbackTypes
            {
            eNoFeedback = 0,
            eFeedback
            };

        enum footIKTypes
            {
            eNoFootIK = 0,
            eFootIK
            };

        enum lookIKTypes
            {
            eNoLookIK = 0,
            eLookIK
            };

        enum grabIKTypes
            {
            eNoGrabIK = 0,
            eGrabIK
            };

        enum matchPoseTypes
            {
            eNoMatchPose = 0,
            eMatchPose
            };

    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<UINT32> NVER; //Version
        OptSubRecord<RGDLDATA> DATA; // General Data
        OptSimpleSubRecord<FORMID> XNAM; //Actor Base
        OptSimpleSubRecord<FORMID> TNAM; //Body Part Data
        OptSubRecord<RGDLRAFD> RAFD; // Feedback Data
        std::vector<UINT16> RAFB; //Feedback Dynamic Bones
        OptSubRecord<RGDLRAPS> RAPS; //Pose Matching Data
        StringRecord ANAM; //Death Pose

        RGDLRecord(unsigned char *_recData=NULL);
        RGDLRecord(RGDLRecord *srcRecord);
        ~RGDLRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsDisableOnMove();
        void   IsDisableOnMove(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsNoFeedback();
        void   IsNoFeedback(bool value);
        bool   IsFeedback();
        void   IsFeedback(bool value);
        bool   IsFeedbackType(UINT8 Type, bool Exact=false);
        void   SetFeedbackType(UINT8 Type);

        bool   IsNoFootIK();
        void   IsNoFootIK(bool value);
        bool   IsFootIK();
        void   IsFootIK(bool value);
        bool   IsFootType(UINT8 Type, bool Exact=false);
        void   SetFootType(UINT8 Type);

        bool   IsNoLookIK();
        void   IsNoLookIK(bool value);
        bool   IsLookIK();
        void   IsLookIK(bool value);
        bool   IsLookType(UINT8 Type, bool Exact=false);
        void   SetLookType(UINT8 Type);

        bool   IsNoGrabIK();
        void   IsNoGrabIK(bool value);
        bool   IsGrabIK();
        void   IsGrabIK(bool value);
        bool   IsGrabType(UINT8 Type, bool Exact=false);
        void   SetGrabType(UINT8 Type);

        bool   IsNoMatchPose();
        void   IsNoMatchPose(bool value);
        bool   IsMatchPose();
        void   IsMatchPose(bool value);
        bool   IsMatchType(UINT8 Type, bool Exact=false);
        void   SetMatchType(UINT8 Type);

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

        bool operator ==(const RGDLRecord &other) const;
        bool operator !=(const RGDLRecord &other) const;
    };
}