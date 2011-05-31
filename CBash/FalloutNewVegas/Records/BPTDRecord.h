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
class BPTDRecord : public FNVRecord //Body Part Data
    {
    private:
        struct BPTDBPND
            {
            FLOAT32 damageMult;
            UINT8   flags, partType, healthPercent;
            SINT8   actorValue;
            UINT8   hitChance, explodableExplosionChance;
            UINT16  explodableDebrisCount;
            FORMID  explodableDebris, explodableExplosion;
            FLOAT32 maxTrackAngle, explodableDebrisScale;
            SINT32  severableDebrisCount;
            FORMID  severableDebris, severableExplosion;
            FLOAT32 severableDebrisScale;

            //Gore Positioning
            FLOAT32 transX, transY, transZ, rotX, rotY, rotZ;

            FORMID  severableImpact, explodableImpact;
            UINT8   severableDecalCount, explodableDecalCount, unused1[2];
            FLOAT32 limbReplaceScale;

            BPTDBPND();
            ~BPTDBPND();

            bool operator ==(const BPTDBPND &other) const;
            bool operator !=(const BPTDBPND &other) const;
            };

        struct BPTDPart // Body Part
            {
            StringRecord BPTN; //Part Name
            StringRecord BPNN; //Part Node
            StringRecord BPNT; //VATS Target
            StringRecord BPNI; //IK Data - Start Node
            ReqSubRecord<BPTDBPND> BPND; //Data
            StringRecord NAM1; //Limb Replacement Model
            StringRecord NAM4; //Gore Effects - Target Bone
            RawRecord NAM5; //Texture Files Hashes

            enum flagFlags
                {
                fIsSeverable          = 0x00000001,
                fIsIKData             = 0x00000002,
                fIsIKDataBipedData    = 0x00000004,
                fIsExplodable         = 0x00000008,
                fIsIKDataIsHead       = 0x00000010,
                fIsIKDataHeadTracking = 0x00000020,
                fIsAbsoluteHitChance  = 0x00000040
                };

            enum partTypes
                {
                eTorso = 0,
                eHead1,
                eHead2,
                eLeftArm1,
                eLeftArm2,
                eRightArm1,
                eRightArm2,
                eLeftLeg1,
                eLeftLeg2,
                eLeftLeg3,
                eRightLeg1,
                eRightLeg2,
                eRightLeg3,
                eBrain,
                eWeapon
                };

            bool   IsSeverable();
            void   IsSeverable(bool value);
            bool   IsIKData();
            void   IsIKData(bool value);
            bool   IsIKDataBipedData();
            void   IsIKDataBipedData(bool value);
            bool   IsExplodable();
            void   IsExplodable(bool value);
            bool   IsIKDataIsHead();
            void   IsIKDataIsHead(bool value);
            bool   IsIKDataHeadTracking();
            void   IsIKDataHeadTracking(bool value);
            bool   IsAbsoluteHitChance();
            void   IsAbsoluteHitChance(bool value);
            bool   IsFlagMask(UINT8 Mask, bool Exact=false);
            void   SetFlagMask(UINT8 Mask);

            bool   IsTorso();
            void   IsTorso(bool value);
            bool   IsHead1();
            void   IsHead1(bool value);
            bool   IsHead2();
            void   IsHead2(bool value);
            bool   IsLeftArm1();
            void   IsLeftArm1(bool value);
            bool   IsLeftArm2();
            void   IsLeftArm2(bool value);
            bool   IsRightArm1();
            void   IsRightArm1(bool value);
            bool   IsRightArm2();
            void   IsRightArm2(bool value);
            bool   IsLeftLeg1();
            void   IsLeftLeg1(bool value);
            bool   IsLeftLeg2();
            void   IsLeftLeg2(bool value);
            bool   IsLeftLeg3();
            void   IsLeftLeg3(bool value);
            bool   IsRightLeg1();
            void   IsRightLeg1(bool value);
            bool   IsRightLeg2();
            void   IsRightLeg2(bool value);
            bool   IsRightLeg3();
            void   IsRightLeg3(bool value);
            bool   IsBrain();
            void   IsBrain(bool value);
            bool   IsWeapon();
            void   IsWeapon(bool value);
            bool   IsType(UINT8 Type);
            void   SetType(UINT8 Type);

            void Write(FileWriter &writer);

            bool operator ==(const BPTDPart &other) const;
            bool operator !=(const BPTDPart &other) const;
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<FNVMODEL> MODL; //Model
        UnorderedSparseArray<BPTDPart *> Parts; // Body Parts
        ReqSimpleSubRecord<FORMID> RAGA; //Ragdoll

        BPTDRecord(unsigned char *_recData=NULL);
        BPTDRecord(BPTDRecord *srcRecord);
        ~BPTDRecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const BPTDRecord &other) const;
        bool operator !=(const BPTDRecord &other) const;
    };
}