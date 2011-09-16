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
#include "..\..\..\Common.h"
#include "..\CSTYRecord.h"

namespace FNV
{
UINT32 CSTYRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //formVersion
            return UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 7: //dodgeChance
            return UINT8_FIELD;
        case 8: //lrChance
            return UINT8_FIELD;
        case 9: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 10: //lrTimerMin
            return FLOAT32_FIELD;
        case 11: //lrTimerMax
            return FLOAT32_FIELD;
        case 12: //forTimerMin
            return FLOAT32_FIELD;
        case 13: //forTimerMax
            return FLOAT32_FIELD;
        case 14: //backTimerMin
            return FLOAT32_FIELD;
        case 15: //backTimerMax
            return FLOAT32_FIELD;
        case 16: //idleTimerMin
            return FLOAT32_FIELD;
        case 17: //idleTimerMax
            return FLOAT32_FIELD;
        case 18: //blkChance
            return UINT8_FIELD;
        case 19: //atkChance
            return UINT8_FIELD;
        case 20: //unused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 21: //atkBRecoil
            return FLOAT32_FIELD;
        case 22: //atkBUnc
            return FLOAT32_FIELD;
        case 23: //atkBh2h
            return FLOAT32_FIELD;
        case 24: //pAtkChance
            return UINT8_FIELD;
        case 25: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 26: //pAtkBRecoil
            return FLOAT32_FIELD;
        case 27: //pAtkBUnc
            return FLOAT32_FIELD;
        case 28: //pAtkNormal
            return UINT8_FIELD;
        case 29: //pAtkFor
            return UINT8_FIELD;
        case 30: //pAtkBack
            return UINT8_FIELD;
        case 31: //pAtkL
            return UINT8_FIELD;
        case 32: //pAtkR
            return UINT8_FIELD;
        case 33: //unused4
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 34: //holdTimerMin
            return FLOAT32_FIELD;
        case 35: //holdTimerMax
            return FLOAT32_FIELD;
        case 36: //flags
            return UINT16_FLAG_FIELD;
        case 37: //unused5
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 38: //acroDodge
            return UINT8_FIELD;
        case 39: //rushChance
            return UINT8_FIELD;
        case 40: //unused6
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 41: //rushMult
            return FLOAT32_FIELD;
        case 42: //dodgeFMult
            return FLOAT32_FIELD;
        case 43: //dodgeFBase
            return FLOAT32_FIELD;
        case 44: //encSBase
            return FLOAT32_FIELD;
        case 45: //encSMult
            return FLOAT32_FIELD;
        case 46: //dodgeAtkMult
            return FLOAT32_FIELD;
        case 47: //dodgeNAtkMult
            return FLOAT32_FIELD;
        case 48: //dodgeBAtkMult
            return FLOAT32_FIELD;
        case 49: //dodgeBNAtkMult
            return FLOAT32_FIELD;
        case 50: //dodgeFAtkMult
            return FLOAT32_FIELD;
        case 51: //dodgeFNAtkMult
            return FLOAT32_FIELD;
        case 52: //blockMult
            return FLOAT32_FIELD;
        case 53: //blockBase
            return FLOAT32_FIELD;
        case 54: //blockAtkMult
            return FLOAT32_FIELD;
        case 55: //blockNAtkMult
            return FLOAT32_FIELD;
        case 56: //atkMult
            return FLOAT32_FIELD;
        case 57: //atkBase
            return FLOAT32_FIELD;
        case 58: //atkAtkMult
            return FLOAT32_FIELD;
        case 59: //atkNAtkMult
            return FLOAT32_FIELD;
        case 60: //atkBlockMult
            return FLOAT32_FIELD;
        case 61: //pAtkFBase
            return FLOAT32_FIELD;
        case 62: //pAtkFMult
            return FLOAT32_FIELD;
        case 63: //coverRadius
            return FLOAT32_FIELD;
        case 64: //coverChance
            return FLOAT32_FIELD;
        case 65: //waitTimerMin
            return FLOAT32_FIELD;
        case 66: //waitFireTimerMin
            return FLOAT32_FIELD;
        case 67: //waitFireTimerMax
            return FLOAT32_FIELD;
        case 68: //waitTimerMax
            return FLOAT32_FIELD;
        case 69: //fireTimerMin
            return FLOAT32_FIELD;
        case 70: //fireTimerMax
            return FLOAT32_FIELD;
        case 71: //rangedRangeMultMin
            return FLOAT32_FIELD;
        case 72: //unused7
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 73: //weaponRestrictions
            return UINT32_TYPE_FIELD;
        case 74: //rangedRangeMultMax
            return FLOAT32_FIELD;
        case 75: //targetMaxFOV
            return FLOAT32_FIELD;
        case 76: //combatRadius
            return FLOAT32_FIELD;
        case 77: //semiAutoFireDelayMultMin
            return FLOAT32_FIELD;
        case 78: //semiAutoFireDelayMultMax
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * CSTYRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //versionControl1
            *FieldValues = &flagsUnk;
            return NULL;
        case 4: //eid
            return EDID.value;
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //dodgeChance
            return &CSTD.value.dodgeChance;
        case 8: //lrChance
            return &CSTD.value.lrChance;
        case 9: //unused1
            *FieldValues = &CSTD.value.unused1[0];
            return NULL;
        case 10: //lrTimerMin
            return &CSTD.value.lrTimerMin;
        case 11: //lrTimerMax
            return &CSTD.value.lrTimerMax;
        case 12: //forTimerMin
            return &CSTD.value.forTimerMin;
        case 13: //forTimerMax
            return &CSTD.value.forTimerMax;
        case 14: //backTimerMin
            return &CSTD.value.backTimerMin;
        case 15: //backTimerMax
            return &CSTD.value.backTimerMax;
        case 16: //idleTimerMin
            return &CSTD.value.idleTimerMin;
        case 17: //idleTimerMax
            return &CSTD.value.idleTimerMax;
        case 18: //blkChance
            return &CSTD.value.blkChance;
        case 19: //atkChance
            return &CSTD.value.atkChance;
        case 20: //unused2
            *FieldValues = &CSTD.value.unused2[0];
            return NULL;
        case 21: //atkBRecoil
            return &CSTD.value.atkBRecoil;
        case 22: //atkBUnc
            return &CSTD.value.atkBUnc;
        case 23: //atkBh2h
            return &CSTD.value.atkBh2h;
        case 24: //pAtkChance
            return &CSTD.value.pAtkChance;
        case 25: //unused3
            *FieldValues = &CSTD.value.unused3[0];
            return NULL;
        case 26: //pAtkBRecoil
            return &CSTD.value.pAtkBRecoil;
        case 27: //pAtkBUnc
            return &CSTD.value.pAtkBUnc;
        case 28: //pAtkNormal
            return &CSTD.value.pAtkNormal;
        case 29: //pAtkFor
            return &CSTD.value.pAtkFor;
        case 30: //pAtkBack
            return &CSTD.value.pAtkBack;
        case 31: //pAtkL
            return &CSTD.value.pAtkL;
        case 32: //pAtkR
            return &CSTD.value.pAtkR;
        case 33: //unused4
            *FieldValues = &CSTD.value.unused4[0];
            return NULL;
        case 34: //holdTimerMin
            return &CSTD.value.holdTimerMin;
        case 35: //holdTimerMax
            return &CSTD.value.holdTimerMax;
        case 36: //flags
            return &CSTD.value.flags;
        case 37: //unused5
            *FieldValues = &CSTD.value.unused5[0];
            return NULL;
        case 38: //acroDodge
            return &CSTD.value.acroDodge;
        case 39: //rushChance
            return &CSTD.value.rushChance;
        case 40: //unused6
            *FieldValues = &CSTD.value.unused6[0];
            return NULL;
        case 41: //rushMult
            return &CSTD.value.rushMult;
        case 42: //dodgeFMult
            return &CSAD.value.dodgeFMult;
        case 43: //dodgeFBase
            return &CSAD.value.dodgeFBase;
        case 44: //encSBase
            return &CSAD.value.encSBase;
        case 45: //encSMult
            return &CSAD.value.encSMult;
        case 46: //dodgeAtkMult
            return &CSAD.value.dodgeAtkMult;
        case 47: //dodgeNAtkMult
            return &CSAD.value.dodgeNAtkMult;
        case 48: //dodgeBAtkMult
            return &CSAD.value.dodgeBAtkMult;
        case 49: //dodgeBNAtkMult
            return &CSAD.value.dodgeBNAtkMult;
        case 50: //dodgeFAtkMult
            return &CSAD.value.dodgeFAtkMult;
        case 51: //dodgeFNAtkMult
            return &CSAD.value.dodgeFNAtkMult;
        case 52: //blockMult
            return &CSAD.value.blockMult;
        case 53: //blockBase
            return &CSAD.value.blockBase;
        case 54: //blockAtkMult
            return &CSAD.value.blockAtkMult;
        case 55: //blockNAtkMult
            return &CSAD.value.blockNAtkMult;
        case 56: //atkMult
            return &CSAD.value.atkMult;
        case 57: //atkBase
            return &CSAD.value.atkBase;
        case 58: //atkAtkMult
            return &CSAD.value.atkAtkMult;
        case 59: //atkNAtkMult
            return &CSAD.value.atkNAtkMult;
        case 60: //atkBlockMult
            return &CSAD.value.atkBlockMult;
        case 61: //pAtkFBase
            return &CSAD.value.pAtkFBase;
        case 62: //pAtkFMult
            return &CSAD.value.pAtkFMult;
        case 63: //coverRadius
            return &CSSD.value.coverRadius;
        case 64: //coverChance
            return &CSSD.value.coverChance;
        case 65: //waitTimerMin
            return &CSSD.value.waitTimerMin;
        case 66: //waitTimerMax
            return &CSSD.value.waitTimerMax;
        case 67: //waitFireTimerMin
            return &CSSD.value.waitFireTimerMin;
        case 68: //waitFireTimerMax
            return &CSSD.value.waitFireTimerMax;
        case 69: //fireTimerMin
            return &CSSD.value.fireTimerMin;
        case 70: //fireTimerMax
            return &CSSD.value.fireTimerMax;
        case 71: //rangedRangeMultMin
            return &CSSD.value.rangedRangeMultMin;
        case 72: //unused7
            *FieldValues = &CSSD.value.unused1[0];
            return NULL;
        case 73: //weaponRestrictions
            return &CSSD.value.weaponRestrictions;
        case 74: //rangedRangeMultMax
            return &CSSD.value.rangedRangeMultMax;
        case 75: //targetMaxFOV
            return &CSSD.value.targetMaxFOV;
        case 76: //combatRadius
            return &CSSD.value.combatRadius;
        case 77: //semiAutoFireDelayMultMin
            return &CSSD.value.semiAutoFireDelayMultMin;
        case 78: //semiAutoFireDelayMultMax
            return &CSSD.value.semiAutoFireDelayMultMax;
        default:
            return NULL;
        }
    return NULL;
    }

bool CSTYRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //dodgeChance
            CSTD.value.dodgeChance = *(UINT8 *)FieldValue;
            break;
        case 8: //lrChance
            CSTD.value.lrChance = *(UINT8 *)FieldValue;
            break;
        case 9: //unused1
            if(ArraySize != 2)
                break;
            CSTD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 10: //lrTimerMin
            CSTD.value.lrTimerMin = *(FLOAT32 *)FieldValue;
            break;
        case 11: //lrTimerMax
            CSTD.value.lrTimerMax = *(FLOAT32 *)FieldValue;
            break;
        case 12: //forTimerMin
            CSTD.value.forTimerMin = *(FLOAT32 *)FieldValue;
            break;
        case 13: //forTimerMax
            CSTD.value.forTimerMax = *(FLOAT32 *)FieldValue;
            break;
        case 14: //backTimerMin
            CSTD.value.backTimerMin = *(FLOAT32 *)FieldValue;
            break;
        case 15: //backTimerMax
            CSTD.value.backTimerMax = *(FLOAT32 *)FieldValue;
            break;
        case 16: //idleTimerMin
            CSTD.value.idleTimerMin = *(FLOAT32 *)FieldValue;
            break;
        case 17: //idleTimerMax
            CSTD.value.idleTimerMax = *(FLOAT32 *)FieldValue;
            break;
        case 18: //blkChance
            CSTD.value.blkChance = *(UINT8 *)FieldValue;
            break;
        case 19: //atkChance
            CSTD.value.atkChance = *(UINT8 *)FieldValue;
            break;
        case 20: //unused2
            if(ArraySize != 2)
                break;
            CSTD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 21: //atkBRecoil
            CSTD.value.atkBRecoil = *(FLOAT32 *)FieldValue;
            break;
        case 22: //atkBUnc
            CSTD.value.atkBUnc = *(FLOAT32 *)FieldValue;
            break;
        case 23: //atkBh2h
            CSTD.value.atkBh2h = *(FLOAT32 *)FieldValue;
            break;
        case 24: //pAtkChance
            CSTD.value.pAtkChance = *(UINT8 *)FieldValue;
            break;
        case 25: //unused3
            if(ArraySize != 3)
                break;
            CSTD.value.unused3[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused3[1] = ((UINT8ARRAY)FieldValue)[1];
            CSTD.value.unused3[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 26: //pAtkBRecoil
            CSTD.value.pAtkBRecoil = *(FLOAT32 *)FieldValue;
            break;
        case 27: //pAtkBUnc
            CSTD.value.pAtkBUnc = *(FLOAT32 *)FieldValue;
            break;
        case 28: //pAtkNormal
            CSTD.value.pAtkNormal = *(UINT8 *)FieldValue;
            break;
        case 29: //pAtkFor
            CSTD.value.pAtkFor = *(UINT8 *)FieldValue;
            break;
        case 30: //pAtkBack
            CSTD.value.pAtkBack = *(UINT8 *)FieldValue;
            break;
        case 31: //pAtkL
            CSTD.value.pAtkL = *(UINT8 *)FieldValue;
            break;
        case 32: //pAtkR
            CSTD.value.pAtkR = *(UINT8 *)FieldValue;
            break;
        case 33: //unused4
            if(ArraySize != 3)
                break;
            CSTD.value.unused4[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused4[1] = ((UINT8ARRAY)FieldValue)[1];
            CSTD.value.unused4[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 34: //holdTimerMin
            CSTD.value.holdTimerMin = *(FLOAT32 *)FieldValue;
            break;
        case 35: //holdTimerMax
            CSTD.value.holdTimerMax = *(FLOAT32 *)FieldValue;
            break;
        case 36: //flags
            SetFlagMask(*(UINT16 *)FieldValue);
            break;
        case 37: //unused5
            if(ArraySize != 2)
                break;
            CSTD.value.unused5[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused5[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 38: //acroDodge
            CSTD.value.acroDodge = *(UINT8 *)FieldValue;
            break;
        case 39: //rushChance
            CSTD.value.rushChance = *(UINT8 *)FieldValue;
            break;
        case 40: //unused6
            if(ArraySize != 2)
                break;
            CSTD.value.unused6[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused6[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 41: //rushMult
            CSTD.value.rushMult = *(FLOAT32 *)FieldValue;
            break;
        case 42: //dodgeFMult
            CSAD.value.dodgeFMult = *(FLOAT32 *)FieldValue;
            break;
        case 43: //dodgeFBase
            CSAD.value.dodgeFBase = *(FLOAT32 *)FieldValue;
            break;
        case 44: //encSBase
            CSAD.value.encSBase = *(FLOAT32 *)FieldValue;
            break;
        case 45: //encSMult
            CSAD.value.encSMult = *(FLOAT32 *)FieldValue;
            break;
        case 46: //dodgeAtkMult
            CSAD.value.dodgeAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 47: //dodgeNAtkMult
            CSAD.value.dodgeNAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 48: //dodgeBAtkMult
            CSAD.value.dodgeBAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 49: //dodgeBNAtkMult
            CSAD.value.dodgeBNAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 50: //dodgeFAtkMult
            CSAD.value.dodgeFAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 51: //dodgeFNAtkMult
            CSAD.value.dodgeFNAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 52: //blockMult
            CSAD.value.blockMult = *(FLOAT32 *)FieldValue;
            break;
        case 53: //blockBase
            CSAD.value.blockBase = *(FLOAT32 *)FieldValue;
            break;
        case 54: //blockAtkMult
            CSAD.value.blockAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 55: //blockNAtkMult
            CSAD.value.blockNAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 56: //atkMult
            CSAD.value.atkMult = *(FLOAT32 *)FieldValue;
            break;
        case 57: //atkBase
            CSAD.value.atkBase = *(FLOAT32 *)FieldValue;
            break;
        case 58: //atkAtkMult
            CSAD.value.atkAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 59: //atkNAtkMult
            CSAD.value.atkNAtkMult = *(FLOAT32 *)FieldValue;
            break;
        case 60: //atkBlockMult
            CSAD.value.atkBlockMult = *(FLOAT32 *)FieldValue;
            break;
        case 61: //pAtkFBase
            CSAD.value.pAtkFBase = *(FLOAT32 *)FieldValue;
            break;
        case 62: //pAtkFMult
            CSAD.value.pAtkFMult = *(FLOAT32 *)FieldValue;
            break;
        case 63: //coverRadius
            CSSD.value.coverRadius = *(FLOAT32 *)FieldValue;
            break;
        case 64: //coverChance
            CSSD.value.coverChance = *(FLOAT32 *)FieldValue;
            break;
        case 65: //waitTimerMin
            CSSD.value.waitTimerMin = *(FLOAT32 *)FieldValue;
            break;
        case 66: //waitTimerMax
            CSSD.value.waitTimerMax = *(FLOAT32 *)FieldValue;
            break;
        case 67: //waitFireTimerMin
            CSSD.value.waitFireTimerMin = *(FLOAT32 *)FieldValue;
            break;
        case 68: //waitFireTimerMax
            CSSD.value.waitFireTimerMax = *(FLOAT32 *)FieldValue;
            break;
        case 69: //fireTimerMin
            CSSD.value.fireTimerMin = *(FLOAT32 *)FieldValue;
            break;
        case 70: //fireTimerMax
            CSSD.value.fireTimerMax = *(FLOAT32 *)FieldValue;
            break;
        case 71: //rangedRangeMultMin
            CSSD.value.rangedRangeMultMin = *(FLOAT32 *)FieldValue;
            break;
        case 72: //unused7
            if(ArraySize != 4)
                break;
            CSSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            CSSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            CSSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            CSSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 73: //weaponRestrictions
            SetType(*(UINT32 *)FieldValue);
            break;
        case 74: //rangedRangeMultMax
            CSSD.value.rangedRangeMultMax = *(FLOAT32 *)FieldValue;
            break;
        case 75: //targetMaxFOV
            CSSD.value.targetMaxFOV = *(FLOAT32 *)FieldValue;
            break;
        case 76: //combatRadius
            CSSD.value.combatRadius = *(FLOAT32 *)FieldValue;
            break;
        case 77: //semiAutoFireDelayMultMin
            CSSD.value.semiAutoFireDelayMultMin = *(FLOAT32 *)FieldValue;
            break;
        case 78: //semiAutoFireDelayMultMax
            CSSD.value.semiAutoFireDelayMultMax = *(FLOAT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CSTYRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    CSTYCSTD defaultCSTD;
    CSTYCSAD defaultCSAD;
    CSTYCSSD defaultCSSD;
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //dodgeChance
            CSTD.value.dodgeChance = defaultCSTD.dodgeChance;
            return;
        case 8: //lrChance
            CSTD.value.lrChance = defaultCSTD.lrChance;
            return;
        case 9: //unused1
            CSTD.value.unused1[0] = defaultCSTD.unused1[0];
            CSTD.value.unused1[1] = defaultCSTD.unused1[1];
            return;
        case 10: //lrTimerMin
            CSTD.value.lrTimerMin = defaultCSTD.lrTimerMin;
            return;
        case 11: //lrTimerMax
            CSTD.value.lrTimerMax = defaultCSTD.lrTimerMax;
            return;
        case 12: //forTimerMin
            CSTD.value.forTimerMin = defaultCSTD.forTimerMin;
            return;
        case 13: //forTimerMax
            CSTD.value.forTimerMax = defaultCSTD.forTimerMax;
            return;
        case 14: //backTimerMin
            CSTD.value.backTimerMin = defaultCSTD.backTimerMin;
            return;
        case 15: //backTimerMax
            CSTD.value.backTimerMax = defaultCSTD.backTimerMax;
            return;
        case 16: //idleTimerMin
            CSTD.value.idleTimerMin = defaultCSTD.idleTimerMin;
            return;
        case 17: //idleTimerMax
            CSTD.value.idleTimerMax = defaultCSTD.idleTimerMax;
            return;
        case 18: //blkChance
            CSTD.value.blkChance = defaultCSTD.blkChance;
            return;
        case 19: //atkChance
            CSTD.value.atkChance = defaultCSTD.atkChance;
            return;
        case 20: //unused2
            CSTD.value.unused2[0] = defaultCSTD.unused2[0];
            CSTD.value.unused2[1] = defaultCSTD.unused2[1];
            return;
        case 21: //atkBRecoil
            CSTD.value.atkBRecoil = defaultCSTD.atkBRecoil;
            return;
        case 22: //atkBUnc
            CSTD.value.atkBUnc = defaultCSTD.atkBUnc;
            return;
        case 23: //atkBh2h
            CSTD.value.atkBh2h = defaultCSTD.atkBh2h;
            return;
        case 24: //pAtkChance
            CSTD.value.pAtkChance = defaultCSTD.pAtkChance;
            return;
        case 25: //unused3
            CSTD.value.unused3[0] = defaultCSTD.unused3[0];
            CSTD.value.unused3[1] = defaultCSTD.unused3[1];
            CSTD.value.unused3[2] = defaultCSTD.unused3[2];
            return;
        case 26: //pAtkBRecoil
            CSTD.value.pAtkBRecoil = defaultCSTD.pAtkBRecoil;
            return;
        case 27: //pAtkBUnc
            CSTD.value.pAtkBUnc = defaultCSTD.pAtkBUnc;
            return;
        case 28: //pAtkNormal
            CSTD.value.pAtkNormal = defaultCSTD.pAtkNormal;
            return;
        case 29: //pAtkFor
            CSTD.value.pAtkFor = defaultCSTD.pAtkFor;
            return;
        case 30: //pAtkBack
            CSTD.value.pAtkBack = defaultCSTD.pAtkBack;
            return;
        case 31: //pAtkL
            CSTD.value.pAtkL = defaultCSTD.pAtkL;
            return;
        case 32: //pAtkR
            CSTD.value.pAtkR = defaultCSTD.pAtkR;
            return;
        case 33: //unused4
            CSTD.value.unused4[0] = defaultCSTD.unused4[0];
            CSTD.value.unused4[1] = defaultCSTD.unused4[1];
            CSTD.value.unused4[2] = defaultCSTD.unused4[2];
            return;
        case 34: //holdTimerMin
            CSTD.value.holdTimerMin = defaultCSTD.holdTimerMin;
            return;
        case 35: //holdTimerMax
            CSTD.value.holdTimerMax = defaultCSTD.holdTimerMax;
            return;
        case 36: //flags
            SetFlagMask(defaultCSTD.flags);
            return;
        case 37: //unused5
            CSTD.value.unused5[0] = defaultCSTD.unused5[0];
            CSTD.value.unused5[1] = defaultCSTD.unused5[1];
            return;
        case 38: //acroDodge
            CSTD.value.acroDodge = defaultCSTD.acroDodge;
            return;
        case 39: //rushChance
            CSTD.value.rushChance = defaultCSTD.rushChance;
            return;
        case 40: //unused6
            CSTD.value.unused6[0] = defaultCSTD.unused6[0];
            CSTD.value.unused6[1] = defaultCSTD.unused6[1];
            return;
        case 41: //rushMult
            CSTD.value.rushMult = defaultCSTD.rushMult;
            return;
        case 42: //dodgeFMult
            CSAD.value.dodgeFMult = defaultCSAD.dodgeFMult;
            return;
        case 43: //dodgeFBase
            CSAD.value.dodgeFBase = defaultCSAD.dodgeFBase;
            return;
        case 44: //encSBase
            CSAD.value.encSBase = defaultCSAD.encSBase;
            return;
        case 45: //encSMult
            CSAD.value.encSMult = defaultCSAD.encSMult;
            return;
        case 46: //dodgeAtkMult
            CSAD.value.dodgeAtkMult = defaultCSAD.dodgeAtkMult;
            return;
        case 47: //dodgeNAtkMult
            CSAD.value.dodgeNAtkMult = defaultCSAD.dodgeNAtkMult;
            return;
        case 48: //dodgeBAtkMult
            CSAD.value.dodgeBAtkMult = defaultCSAD.dodgeBAtkMult;
            return;
        case 49: //dodgeBNAtkMult
            CSAD.value.dodgeBNAtkMult = defaultCSAD.dodgeBNAtkMult;
            return;
        case 50: //dodgeFAtkMult
            CSAD.value.dodgeFAtkMult = defaultCSAD.dodgeFAtkMult;
            return;
        case 51: //dodgeFNAtkMult
            CSAD.value.dodgeFNAtkMult = defaultCSAD.dodgeFNAtkMult;
            return;
        case 52: //blockMult
            CSAD.value.blockMult = defaultCSAD.blockMult;
            return;
        case 53: //blockBase
            CSAD.value.blockBase = defaultCSAD.blockBase;
            return;
        case 54: //blockAtkMult
            CSAD.value.blockAtkMult = defaultCSAD.blockAtkMult;
            return;
        case 55: //blockNAtkMult
            CSAD.value.blockNAtkMult = defaultCSAD.blockNAtkMult;
            return;
        case 56: //atkMult
            CSAD.value.atkMult = defaultCSAD.atkMult;
            return;
        case 57: //atkBase
            CSAD.value.atkBase = defaultCSAD.atkBase;
            return;
        case 58: //atkAtkMult
            CSAD.value.atkAtkMult = defaultCSAD.atkAtkMult;
            return;
        case 59: //atkNAtkMult
            CSAD.value.atkNAtkMult = defaultCSAD.atkNAtkMult;
            return;
        case 60: //atkBlockMult
            CSAD.value.atkBlockMult = defaultCSAD.atkBlockMult;
            return;
        case 61: //pAtkFBase
            CSAD.value.pAtkFBase = defaultCSAD.pAtkFBase;
            return;
        case 62: //pAtkFMult
            CSAD.value.pAtkFMult = defaultCSAD.pAtkFMult;
            return;
        case 63: //coverRadius
            CSSD.value.coverRadius = defaultCSSD.coverRadius;
            return;
        case 64: //coverChance
            CSSD.value.coverChance = defaultCSSD.coverChance;
            return;
        case 65: //waitTimerMin
            CSSD.value.waitTimerMin = defaultCSSD.waitTimerMin;
            return;
        case 66: //waitTimerMax
            CSSD.value.waitTimerMax = defaultCSSD.waitTimerMax;
            return;
        case 67: //waitFireTimerMin
            CSSD.value.waitFireTimerMin =defaultCSSD.waitFireTimerMin;
            break;
        case 68: //waitFireTimerMax
            CSSD.value.waitFireTimerMax = defaultCSSD.waitFireTimerMax;
            break;
        case 69: //fireTimerMin
            CSSD.value.fireTimerMin = defaultCSSD.fireTimerMin;
            return;
        case 70: //fireTimerMax
            CSSD.value.fireTimerMax = defaultCSSD.fireTimerMax;
            return;
        case 71: //rangedRangeMultMin
            CSSD.value.rangedRangeMultMin = defaultCSSD.rangedRangeMultMin;
            return;
        case 72: //unused7
            CSSD.value.unused1[0] = defaultCSSD.unused1[0];
            CSSD.value.unused1[1] = defaultCSSD.unused1[1];
            CSSD.value.unused1[2] = defaultCSSD.unused1[2];
            CSSD.value.unused1[3] = defaultCSSD.unused1[3];
            return;
        case 73: //weaponRestrictions
            SetType(defaultCSSD.weaponRestrictions);
            return;
        case 74: //rangedRangeMultMax
            CSSD.value.rangedRangeMultMax = defaultCSSD.rangedRangeMultMax;
            return;
        case 75: //targetMaxFOV
            CSSD.value.targetMaxFOV = defaultCSSD.targetMaxFOV;
            return;
        case 76: //combatRadius
            CSSD.value.combatRadius = defaultCSSD.combatRadius;
            return;
        case 77: //semiAutoFireDelayMultMin
            CSSD.value.semiAutoFireDelayMultMin = defaultCSSD.semiAutoFireDelayMultMin;
            return;
        case 78: //semiAutoFireDelayMultMax
            CSSD.value.semiAutoFireDelayMultMax = defaultCSSD.semiAutoFireDelayMultMax;
            return;
        default:
            return;
        }
    }
}