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
class CSTYRecord : public FNVRecord //Combat Style
    {
    private:
        struct CSTYCSTD //Advanced Standard
            {
            UINT8   dodgeChance, lrChance, unused1[2];
            FLOAT32 lrTimerMin, lrTimerMax, forTimerMin, forTimerMax, backTimerMin,
                    backTimerMax, idleTimerMin, idleTimerMax;
            UINT8   blkChance, atkChance, unused2[2];
            FLOAT32 atkBRecoil, atkBUnc, atkBh2h;
            UINT8   pAtkChance, unused3[3];
            FLOAT32 pAtkBRecoil, pAtkBUnc;
            UINT8   pAtkNormal, pAtkFor, pAtkBack, pAtkL, pAtkR, unused4[3];
            FLOAT32 holdTimerMin, holdTimerMax;
            UINT16  flags;
            UINT8   unused5[2], acroDodge, rushChance, unused6[2];
            FLOAT32 rushMult;

            CSTYCSTD();
            ~CSTYCSTD();

            bool operator ==(const CSTYCSTD &other) const;
            bool operator !=(const CSTYCSTD &other) const;
            };

        struct CSTYCSAD //Advanced - Advanced
            {
            FLOAT32 dodgeFMult, dodgeFBase, encSBase, encSMult, dodgeAtkMult,
                    dodgeNAtkMult, dodgeBAtkMult, dodgeBNAtkMult,
                    dodgeFAtkMult, dodgeFNAtkMult, blockMult, blockBase,
                    blockAtkMult, blockNAtkMult, atkMult, atkBase, atkAtkMult,
                    atkNAtkMult, atkBlockMult, pAtkFBase, pAtkFMult;

            CSTYCSAD();
            ~CSTYCSAD();

            bool operator ==(const CSTYCSAD &other) const;
            bool operator !=(const CSTYCSAD &other) const;
            };

        struct CSTYCSSD //Simple
            {
            FLOAT32 coverRadius, coverChance, waitTimerMin, waitTimerMax,
                    waitFireTimerMin, waitFireTimerMax, fireTimerMin,
                    fireTimerMax, rangedRangeMultMin;
            UINT8   unused1[4];
            UINT32  weaponRestrictions;
            FLOAT32 rangedRangeMultMax, targetMaxFOV, combatRadius,
                    semiAutoFireDelayMultMin, semiAutoFireDelayMultMax;

            CSTYCSSD();
            ~CSTYCSSD();

            bool operator ==(const CSTYCSSD &other) const;
            bool operator !=(const CSTYCSSD &other) const;
            };

        enum flagsFlags
            {
            fIsUseChanceForAttack      = 0x00000001,
            fIsMeleeAlertOK            = 0x00000002,
            fIsFleeForSurvival         = 0x00000004,
            fIsIgnoreThreats           = 0x00000010,
            fIsIgnoreDamagingSelf      = 0x00000020,
            fIsIgnoreDamagingGroup     = 0x00000040,
            fIsIgnoreDamagingSpectator = 0x00000080,
            fIsNoUseStealthboy         = 0x00000100
            };

        enum restrictionTypes
            {
            eNone       = 0,
            eMeleeOnly  = 1,
            eRangedOnly = 2
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<CSTYCSTD> CSTD; //Advanced Standard
        ReqSubRecord<CSTYCSAD> CSAD; //Advanced - Advanced
        ReqSubRecord<CSTYCSSD> CSSD; //Simple

        CSTYRecord(unsigned char *_recData=NULL);
        CSTYRecord(CSTYRecord *srcRecord);
        ~CSTYRecord();

        bool   IsUseChanceForAttack();
        void   IsUseChanceForAttack(bool value);
        bool   IsMeleeAlertOK();
        void   IsMeleeAlertOK(bool value);
        bool   IsFleeForSurvival();
        void   IsFleeForSurvival(bool value);
        bool   IsIgnoreThreats();
        void   IsIgnoreThreats(bool value);
        bool   IsIgnoreDamagingSelf();
        void   IsIgnoreDamagingSelf(bool value);
        bool   IsIgnoreDamagingGroup();
        void   IsIgnoreDamagingGroup(bool value);
        bool   IsIgnoreDamagingSpectator();
        void   IsIgnoreDamagingSpectator(bool value);
        bool   IsNoUseStealthboy();
        void   IsNoUseStealthboy(bool value);
        bool   IsFlagMask(UINT16 Mask, bool Exact=false);
        void   SetFlagMask(UINT16 Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsMeleeOnly();
        void   IsMeleeOnly(bool value);
        bool   IsRangedOnly();
        void   IsRangedOnly(bool value);
        bool   IsType(UINT32 Type);
        void   SetType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CSTYRecord &other) const;
        bool operator !=(const CSTYRecord &other) const;
        bool equals(Record *other);
    };
}