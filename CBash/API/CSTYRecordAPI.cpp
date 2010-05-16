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
#include "..\Common.h"
#include "..\Records\CSTYRecord.h"

int CSTYRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //dodgeChance
            return UBYTE_FIELD;
        case 7: //lrChance
            return UBYTE_FIELD;
        case 8: //unused1
            return BYTES_FIELD;
        case 9: //lrTimerMin
            return FLOAT_FIELD;
        case 10: //lrTimerMax
            return FLOAT_FIELD;
        case 11: //forTimerMin
            return FLOAT_FIELD;
        case 12: //forTimerMax
            return FLOAT_FIELD;
        case 13: //backTimerMin
            return FLOAT_FIELD;
        case 14: //backTimerMax
            return FLOAT_FIELD;
        case 15: //idleTimerMin
            return FLOAT_FIELD;
        case 16: //idleTimerMax
            return FLOAT_FIELD;
        case 17: //blkChance
            return UBYTE_FIELD;
        case 18: //atkChance
            return UBYTE_FIELD;
        case 19: //unused2
            return BYTES_FIELD;
        case 20: //atkBRecoil
            return FLOAT_FIELD;
        case 21: //atkBUnc
            return FLOAT_FIELD;
        case 22: //atkBh2h
            return FLOAT_FIELD;
        case 23: //pAtkChance
            return UBYTE_FIELD;
        case 24: //unused3
            return BYTES_FIELD;
        case 25: //pAtkBRecoil
            return FLOAT_FIELD;
        case 26: //pAtkBUnc
            return FLOAT_FIELD;
        case 27: //pAtkNormal
            return UBYTE_FIELD;
        case 28: //pAtkFor
            return UBYTE_FIELD;
        case 29: //pAtkBack
            return UBYTE_FIELD;
        case 30: //pAtkL
            return UBYTE_FIELD;
        case 31: //pAtkR
            return UBYTE_FIELD;
        case 32: //unused4
            return BYTES_FIELD;
        case 33: //holdTimerMin
            return FLOAT_FIELD;
        case 34: //holdTimerMax
            return FLOAT_FIELD;
        case 35: //flagsA
            return UBYTE_FIELD;
        case 36: //acroDodge
            return UBYTE_FIELD;
        case 37: //unused5
            return BYTES_FIELD;
        case 38: //rMultOpt
            return FLOAT_FIELD;
        case 39: //rMultMax
            return FLOAT_FIELD;
        case 40: //mDistance
            return FLOAT_FIELD;
        case 41: //rDistance
            return FLOAT_FIELD;
        case 42: //buffStand
            return FLOAT_FIELD;
        case 43: //rStand
            return FLOAT_FIELD;
        case 44: //groupStand
            return FLOAT_FIELD;
        case 45: //rushChance
            return UBYTE_FIELD;
        case 46: //unused6
            return BYTES_FIELD;
        case 47: //rushMult
            return FLOAT_FIELD;
        case 48: //flagsB
            return UINT_FIELD;
        case 49: //dodgeFMult
            return FLOAT_FIELD;
        case 50: //dodgeFBase
            return FLOAT_FIELD;
        case 51: //encSBase
            return FLOAT_FIELD;
        case 52: //encSMult
            return FLOAT_FIELD;
        case 53: //dodgeAtkMult
            return FLOAT_FIELD;
        case 54: //dodgeNAtkMult
            return FLOAT_FIELD;
        case 55: //dodgeBAtkMult
            return FLOAT_FIELD;
        case 56: //dodgeBNAtkMult
            return FLOAT_FIELD;
        case 57: //dodgeFAtkMult
            return FLOAT_FIELD;
        case 58: //dodgeFNAtkMult
            return FLOAT_FIELD;
        case 59: //blockMult
            return FLOAT_FIELD;
        case 60: //blockBase
            return FLOAT_FIELD;
        case 61: //blockAtkMult
            return FLOAT_FIELD;
        case 62: //blockNAtkMult
            return FLOAT_FIELD;
        case 63: //atkMult
            return FLOAT_FIELD;
        case 64: //atkBase
            return FLOAT_FIELD;
        case 65: //atkAtkMult
            return FLOAT_FIELD;
        case 66: //atkNAtkMult
            return FLOAT_FIELD;
        case 67: //atkBlockMult
            return FLOAT_FIELD;
        case 68: //pAtkFBase
            return FLOAT_FIELD;
        case 69: //pAtkFMult
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CSTYRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //dodgeChance
            return &CSTD.value.dodgeChance;
        case 7: //lrChance
            return &CSTD.value.lrChance;
        case 9: //lrTimerMin
            return &CSTD.value.lrTimerMin;
        case 10: //lrTimerMax
            return &CSTD.value.lrTimerMax;
        case 11: //forTimerMin
            return &CSTD.value.forTimerMin;
        case 12: //forTimerMax
            return &CSTD.value.forTimerMax;
        case 13: //backTimerMin
            return &CSTD.value.backTimerMin;
        case 14: //backTimerMax
            return &CSTD.value.backTimerMax;
        case 15: //idleTimerMin
            return &CSTD.value.idleTimerMin;
        case 16: //idleTimerMax
            return &CSTD.value.idleTimerMax;
        case 17: //blkChance
            return &CSTD.value.blkChance;
        case 18: //atkChance
            return &CSTD.value.atkChance;
        case 20: //atkBRecoil
            return &CSTD.value.atkBRecoil;
        case 21: //atkBUnc
            return &CSTD.value.atkBUnc;
        case 22: //atkBh2h
            return &CSTD.value.atkBh2h;
        case 23: //pAtkChance
            return &CSTD.value.pAtkChance;
        case 25: //pAtkBRecoil
            return &CSTD.value.pAtkBRecoil;
        case 26: //pAtkBUnc
            return &CSTD.value.pAtkBUnc;
        case 27: //pAtkNormal
            return &CSTD.value.pAtkNormal;
        case 28: //pAtkFor
            return &CSTD.value.pAtkFor;
        case 29: //pAtkBack
            return &CSTD.value.pAtkBack;
        case 30: //pAtkL
            return &CSTD.value.pAtkL;
        case 31: //pAtkR
            return &CSTD.value.pAtkR;
        case 33: //holdTimerMin
            return &CSTD.value.holdTimerMin;
        case 34: //holdTimerMax
            return &CSTD.value.holdTimerMax;
        case 35: //flagsA
            return &CSTD.value.flagsA;
        case 36: //acroDodge
            return &CSTD.value.acroDodge;
        case 38: //rMultOpt
            return &CSTD.value.rMultOpt;
        case 39: //rMultMax
            return &CSTD.value.rMultMax;
        case 40: //mDistance
            return &CSTD.value.mDistance;
        case 41: //rDistance
            return &CSTD.value.rDistance;
        case 42: //buffStand
            return &CSTD.value.buffStand;
        case 43: //rStand
            return &CSTD.value.rStand;
        case 44: //groupStand
            return &CSTD.value.groupStand;
        case 45: //rushChance
            return &CSTD.value.rushChance;
        case 47: //rushMult
            return &CSTD.value.rushMult;
        case 48: //flagsB
            return &CSTD.value.flagsB;
        case 49: //dodgeFMult
            if(CSAD.IsLoaded())
                return &CSAD->dodgeFMult;
            return NULL;
        case 50: //dodgeFBase
            if(CSAD.IsLoaded())
                return &CSAD->dodgeFBase;
            return NULL;
        case 51: //encSBase
            if(CSAD.IsLoaded())
                return &CSAD->encSBase;
            return NULL;
        case 52: //encSMult
            if(CSAD.IsLoaded())
                return &CSAD->encSMult;
            return NULL;
        case 53: //dodgeAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->dodgeAtkMult;
            return NULL;
        case 54: //dodgeNAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->dodgeNAtkMult;
            return NULL;
        case 55: //dodgeBAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->dodgeBAtkMult;
            return NULL;
        case 56: //dodgeBNAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->dodgeBNAtkMult;
            return NULL;
        case 57: //dodgeFAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->dodgeFAtkMult;
            return NULL;
        case 58: //dodgeFNAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->dodgeFNAtkMult;
            return NULL;
        case 59: //blockMult
            if(CSAD.IsLoaded())
                return &CSAD->blockMult;
            return NULL;
        case 60: //blockBase
            if(CSAD.IsLoaded())
                return &CSAD->blockBase;
            return NULL;
        case 61: //blockAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->blockAtkMult;
            return NULL;
        case 62: //blockNAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->blockNAtkMult;
            return NULL;
        case 63: //atkMult
            if(CSAD.IsLoaded())
                return &CSAD->atkMult;
            return NULL;
        case 64: //atkBase
            if(CSAD.IsLoaded())
                return &CSAD->atkBase;
            return NULL;
        case 65: //atkAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->atkAtkMult;
            return NULL;
        case 66: //atkNAtkMult
            if(CSAD.IsLoaded())
                return &CSAD->atkNAtkMult;
            return NULL;
        case 67: //atkBlockMult
            if(CSAD.IsLoaded())
                return &CSAD->atkBlockMult;
            return NULL;
        case 68: //pAtkFBase
            if(CSAD.IsLoaded())
                return &CSAD->pAtkFBase;
            return NULL;
        case 69: //pAtkFMult
            if(CSAD.IsLoaded())
                return &CSAD->pAtkFMult;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned int CSTYRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //unused1
            return 2;
        case 19: //unused2
            return 2;
        case 24: //unused3
            return 3;
        case 32: //unused4
            return 3;
        case 37: //unused5
            return 2;
        case 46: //unused6
            return 3;
        default:
            return 0;
        }
    }

void CSTYRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //unused1
            *FieldValues = &CSTD.value.unused1[0];
            return;
        case 19: //unused2
            *FieldValues = &CSTD.value.unused2[0];
            return;
        case 24: //unused3
            *FieldValues = &CSTD.value.unused3[0];
            return;
        case 32: //unused4
            *FieldValues = &CSTD.value.unused4[0];
            return;
        case 37: //unused5
            *FieldValues = &CSTD.value.unused5[0];
            return;
        case 46: //unused6
            *FieldValues = &CSTD.value.unused6[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void CSTYRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void CSTYRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 6: //dodgeChance
            CSTD.value.dodgeChance = FieldValue;
            break;
        case 7: //lrChance
            CSTD.value.lrChance = FieldValue;
            break;
        case 17: //blkChance
            CSTD.value.blkChance = FieldValue;
            break;
        case 18: //atkChance
            CSTD.value.atkChance = FieldValue;
            break;
        case 23: //pAtkChance
            CSTD.value.pAtkChance = FieldValue;
            break;
        case 27: //pAtkNormal
            CSTD.value.pAtkNormal = FieldValue;
            break;
        case 28: //pAtkFor
            CSTD.value.pAtkFor = FieldValue;
            break;
        case 29: //pAtkBack
            CSTD.value.pAtkBack = FieldValue;
            break;
        case 30: //pAtkL
            CSTD.value.pAtkL = FieldValue;
            break;
        case 31: //pAtkR
            CSTD.value.pAtkR = FieldValue;
            break;
        case 35: //flagsA
            CSTD.value.flagsA = FieldValue;
            break;
        case 36: //acroDodge
            CSTD.value.acroDodge = FieldValue;
            break;
        case 45: //rushChance
            CSTD.value.rushChance = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CSTYRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //unused1
            if(nSize != 2)
                return;
            CSTD.value.unused1[0] = FieldValue[0];
            CSTD.value.unused1[1] = FieldValue[1];
            break;
        case 19: //unused2
            if(nSize != 2)
                return;
            CSTD.value.unused2[0] = FieldValue[0];
            CSTD.value.unused2[1] = FieldValue[1];
            break;
        case 24: //unused3
            if(nSize != 3)
                return;
            CSTD.value.unused3[0] = FieldValue[0];
            CSTD.value.unused3[1] = FieldValue[1];
            CSTD.value.unused3[2] = FieldValue[2];
            break;
        case 32: //unused4
            if(nSize != 3)
                return;
            CSTD.value.unused4[0] = FieldValue[0];
            CSTD.value.unused4[1] = FieldValue[1];
            CSTD.value.unused4[2] = FieldValue[2];
            break;
        case 37: //unused5
            if(nSize != 2)
                return;
            CSTD.value.unused5[0] = FieldValue[0];
            CSTD.value.unused5[1] = FieldValue[1];
            break;
        case 46: //unused6
            if(nSize != 3)
                return;
            CSTD.value.unused6[0] = FieldValue[0];
            CSTD.value.unused6[1] = FieldValue[1];
            CSTD.value.unused6[2] = FieldValue[2];
            break;
        default:
            return;
        }
    return;
    }

void CSTYRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 9: //lrTimerMin
            CSTD.value.lrTimerMin = FieldValue;
            break;
        case 10: //lrTimerMax
            CSTD.value.lrTimerMax = FieldValue;
            break;
        case 11: //forTimerMin
            CSTD.value.forTimerMin = FieldValue;
            break;
        case 12: //forTimerMax
            CSTD.value.forTimerMax = FieldValue;
            break;
        case 13: //backTimerMin
            CSTD.value.backTimerMin = FieldValue;
            break;
        case 14: //backTimerMax
            CSTD.value.backTimerMax = FieldValue;
            break;
        case 15: //idleTimerMin
            CSTD.value.idleTimerMin = FieldValue;
            break;
        case 16: //idleTimerMax
            CSTD.value.idleTimerMax = FieldValue;
            break;
        case 20: //atkBRecoil
            CSTD.value.atkBRecoil = FieldValue;
            break;
        case 21: //atkBUnc
            CSTD.value.atkBUnc = FieldValue;
            break;
        case 22: //atkBh2h
            CSTD.value.atkBh2h = FieldValue;
            break;
        case 25: //pAtkBRecoil
            CSTD.value.pAtkBRecoil = FieldValue;
            break;
        case 26: //pAtkBUnc
            CSTD.value.pAtkBUnc = FieldValue;
            break;
        case 33: //holdTimerMin
            CSTD.value.holdTimerMin = FieldValue;
            break;
        case 34: //holdTimerMax
            CSTD.value.holdTimerMax = FieldValue;
            break;
        case 38: //rMultOpt
            CSTD.value.rMultOpt = FieldValue;
            break;
        case 39: //rMultMax
            CSTD.value.rMultMax = FieldValue;
            break;
        case 40: //mDistance
            CSTD.value.mDistance = FieldValue;
            break;
        case 41: //rDistance
            CSTD.value.rDistance = FieldValue;
            break;
        case 42: //buffStand
            CSTD.value.buffStand = FieldValue;
            break;
        case 43: //rStand
            CSTD.value.rStand = FieldValue;
            break;
        case 44: //groupStand
            CSTD.value.groupStand = FieldValue;
            break;
        case 47: //rushMult
            CSTD.value.rushMult = FieldValue;
            break;
        case 49: //dodgeFMult
            CSAD.Load();
            CSAD->dodgeFMult = FieldValue;
            break;
        case 50: //dodgeFBase
            CSAD.Load();
            CSAD->dodgeFBase = FieldValue;
            break;
        case 51: //encSBase
            CSAD.Load();
            CSAD->encSBase = FieldValue;
            break;
        case 52: //encSMult
            CSAD.Load();
            CSAD->encSMult = FieldValue;
            break;
        case 53: //dodgeAtkMult
            CSAD.Load();
            CSAD->dodgeAtkMult = FieldValue;
            break;
        case 54: //dodgeNAtkMult
            CSAD.Load();
            CSAD->dodgeNAtkMult = FieldValue;
            break;
        case 55: //dodgeBAtkMult
            CSAD.Load();
            CSAD->dodgeBAtkMult = FieldValue;
            break;
        case 56: //dodgeBNAtkMult
            CSAD.Load();
            CSAD->dodgeBNAtkMult = FieldValue;
            break;
        case 57: //dodgeFAtkMult
            CSAD.Load();
            CSAD->dodgeFAtkMult = FieldValue;
            break;
        case 58: //dodgeFNAtkMult
            CSAD.Load();
            CSAD->dodgeFNAtkMult = FieldValue;
            break;
        case 59: //blockMult
            CSAD.Load();
            CSAD->blockMult = FieldValue;
            break;
        case 60: //blockBase
            CSAD.Load();
            CSAD->blockBase = FieldValue;
            break;
        case 61: //blockAtkMult
            CSAD.Load();
            CSAD->blockAtkMult = FieldValue;
            break;
        case 62: //blockNAtkMult
            CSAD.Load();
            CSAD->blockNAtkMult = FieldValue;
            break;
        case 63: //atkMult
            CSAD.Load();
            CSAD->atkMult = FieldValue;
            break;
        case 64: //atkBase
            CSAD.Load();
            CSAD->atkBase = FieldValue;
            break;
        case 65: //atkAtkMult
            CSAD.Load();
            CSAD->atkAtkMult = FieldValue;
            break;
        case 66: //atkNAtkMult
            CSAD.Load();
            CSAD->atkNAtkMult = FieldValue;
            break;
        case 67: //atkBlockMult
            CSAD.Load();
            CSAD->atkBlockMult = FieldValue;
            break;
        case 68: //pAtkFBase
            CSAD.Load();
            CSAD->pAtkFBase = FieldValue;
            break;
        case 69: //pAtkFMult
            CSAD.Load();
            CSAD->pAtkFMult = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CSTYRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 48: //flagsB
            CSTD.value.flagsB = FieldValue;
            break;
        default:
            return;
        }
    return;
    }
