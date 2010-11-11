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
#include "..\Records\EFSHRecord.h"

int EFSHRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //fillTexture
            return STRING_FIELD;
        case 7: //particleTexture
            return STRING_FIELD;
        case 8: //flags
            return UBYTE_FIELD;
        case 9: //unused1
            return BYTES_FIELD;
        case 10: //memSBlend
            return UINT_FIELD;
        case 11: //memBlendOp
            return UINT_FIELD;
        case 12: //memZFunc
            return UINT_FIELD;
        case 13: //fillRed
            return UBYTE_FIELD;
        case 14: //fillGreen
            return UBYTE_FIELD;
        case 15: //fillBlue
            return UBYTE_FIELD;
        case 16: //unused2
            return BYTES_FIELD;
        case 17: //fillAIn
            return FLOAT_FIELD;
        case 18: //fillAFull
            return FLOAT_FIELD;
        case 19: //fillAOut
            return FLOAT_FIELD;
        case 20: //fillAPRatio
            return FLOAT_FIELD;
        case 21: //fillAAmp
            return FLOAT_FIELD;
        case 22: //fillAFreq
            return FLOAT_FIELD;
        case 23: //fillAnimSpdU
            return FLOAT_FIELD;
        case 24: //fillAnimSpdV
            return FLOAT_FIELD;
        case 25: //edgeOff
            return FLOAT_FIELD;
        case 26: //edgeRed
            return UBYTE_FIELD;
        case 27: //edgeGreen
            return UBYTE_FIELD;
        case 28: //edgeBlue
            return UBYTE_FIELD;
        case 29: //unused3
            return BYTES_FIELD;
        case 30: //edgeAIn
            return FLOAT_FIELD;
        case 31: //edgeAFull
            return FLOAT_FIELD;
        case 32: //edgeAOut
            return FLOAT_FIELD;
        case 33: //edgeAPRatio
            return FLOAT_FIELD;
        case 34: //edgeAAmp
            return FLOAT_FIELD;
        case 35: //edgeAFreq
            return FLOAT_FIELD;
        case 36: //fillAFRatio
            return FLOAT_FIELD;
        case 37: //edgeAFRatio
            return FLOAT_FIELD;
        case 38: //memDBlend
            return UBYTE_FIELD;
        case 39: //partSBlend
            return UBYTE_FIELD;
        case 40: //partBlendOp
            return UBYTE_FIELD;
        case 41: //partZFunc
            return UBYTE_FIELD;
        case 42: //partDBlend
            return UBYTE_FIELD;
        case 43: //partBUp
            return FLOAT_FIELD;
        case 44: //partBFull
            return FLOAT_FIELD;
        case 45: //partBDown
            return FLOAT_FIELD;
        case 46: //partBFRatio
            return FLOAT_FIELD;
        case 47: //partBPRatio
            return FLOAT_FIELD;
        case 48: //partLTime
            return FLOAT_FIELD;
        case 49: //partLDelta
            return FLOAT_FIELD;
        case 50: //partNSpd
            return FLOAT_FIELD;
        case 51: //partNAcc
            return FLOAT_FIELD;
        case 52: //partVel1
            return FLOAT_FIELD;
        case 53: //partVel2
            return FLOAT_FIELD;
        case 54: //partVel3
            return FLOAT_FIELD;
        case 55: //partAcc1
            return FLOAT_FIELD;
        case 56: //partAcc2
            return FLOAT_FIELD;
        case 57: //partAcc3
            return FLOAT_FIELD;
        case 58: //partKey1
            return FLOAT_FIELD;
        case 59: //partKey2
            return FLOAT_FIELD;
        case 60: //partKey1Time
            return FLOAT_FIELD;
        case 61: //partKey2Time
            return FLOAT_FIELD;
        case 62: //key1Red
            return UBYTE_FIELD;
        case 63: //key1Green
            return UBYTE_FIELD;
        case 64: //key1Blue
            return UBYTE_FIELD;
        case 65: //unused4
            return BYTES_FIELD;
        case 66: //key2Red
            return UBYTE_FIELD;
        case 67: //key2Green
            return UBYTE_FIELD;
        case 68: //key2Blue
            return UBYTE_FIELD;
        case 69: //unused5
            return BYTES_FIELD;
        case 70: //key3Red
            return UBYTE_FIELD;
        case 71: //key3Green
            return UBYTE_FIELD;
        case 72: //key3Blue
            return UBYTE_FIELD;
        case 73: //unused6
            return BYTES_FIELD;
        case 74: //key1A
            return FLOAT_FIELD;
        case 75: //key2A
            return FLOAT_FIELD;
        case 76: //key3A
            return FLOAT_FIELD;
        case 77: //key1Time
            return FLOAT_FIELD;
        case 78: //key2Time
            return FLOAT_FIELD;
        case 79: //key3Time
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * EFSHRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //fillTexture
            return ICON.value;
        case 7: //particleTexture
            return ICO2.value;
        case 8: //flags
            return &DATA.value.flags;
        case 10: //memSBlend
            return &DATA.value.memSBlend;
        case 11: //memBlendOp
            return &DATA.value.memBlendOp;
        case 12: //memZFunc
            return &DATA.value.memZFunc;
        case 13: //fillRed
            return &DATA.value.fill.red;
        case 14: //fillGreen
            return &DATA.value.fill.green;
        case 15: //fillBlue
            return &DATA.value.fill.blue;
        case 17: //fillAIn
            return &DATA.value.fillAIn;
        case 18: //fillAFull
            return &DATA.value.fillAFull;
        case 19: //fillAOut
            return &DATA.value.fillAOut;
        case 20: //fillAPRatio
            return &DATA.value.fillAPRatio;
        case 21: //fillAAmp
            return &DATA.value.fillAAmp;
        case 22: //fillAFreq
            return &DATA.value.fillAFreq;
        case 23: //fillAnimSpdU
            return &DATA.value.fillAnimSpdU;
        case 24: //fillAnimSpdV
            return &DATA.value.fillAnimSpdV;
        case 25: //edgeOff
            return &DATA.value.edgeOff;
        case 26: //edgeRed
            return &DATA.value.edge.red;
        case 27: //edgeGreen
            return &DATA.value.edge.green;
        case 28: //edgeBlue
            return &DATA.value.edge.blue;
        case 30: //edgeAIn
            return &DATA.value.edgeAIn;
        case 31: //edgeAFull
            return &DATA.value.edgeAFull;
        case 32: //edgeAOut
            return &DATA.value.edgeAOut;
        case 33: //edgeAPRatio
            return &DATA.value.edgeAPRatio;
        case 34: //edgeAAmp
            return &DATA.value.edgeAAmp;
        case 35: //edgeAFreq
            return &DATA.value.edgeAFreq;
        case 36: //fillAFRatio
            return &DATA.value.fillAFRatio;
        case 37: //edgeAFRatio
            return &DATA.value.edgeAFRatio;
        case 38: //memDBlend
            return &DATA.value.memDBlend;
        case 39: //partSBlend
            return &DATA.value.partSBlend;
        case 40: //partBlendOp
            return &DATA.value.partBlendOp;
        case 41: //partZFunc
            return &DATA.value.partZFunc;
        case 42: //partDBlend
            return &DATA.value.partDBlend;
        case 43: //partBUp
            return &DATA.value.partBUp;
        case 44: //partBFull
            return &DATA.value.partBFull;
        case 45: //partBDown
            return &DATA.value.partBDown;
        case 46: //partBFRatio
            return &DATA.value.partBFRatio;
        case 47: //partBPRatio
            return &DATA.value.partBPRatio;
        case 48: //partLTime
            return &DATA.value.partLTime;
        case 49: //partLDelta
            return &DATA.value.partLDelta;
        case 50: //partNSpd
            return &DATA.value.partNSpd;
        case 51: //partNAcc
            return &DATA.value.partNAcc;
        case 52: //partVel1
            return &DATA.value.partVel1;
        case 53: //partVel2
            return &DATA.value.partVel2;
        case 54: //partVel3
            return &DATA.value.partVel3;
        case 55: //partAcc1
            return &DATA.value.partAcc1;
        case 56: //partAcc2
            return &DATA.value.partAcc2;
        case 57: //partAcc3
            return &DATA.value.partAcc3;
        case 58: //partKey1
            return &DATA.value.partKey1;
        case 59: //partKey2
            return &DATA.value.partKey2;
        case 60: //partKey1Time
            return &DATA.value.partKey1Time;
        case 61: //partKey2Time
            return &DATA.value.partKey2Time;
        case 62: //key1Red
            return &DATA.value.key1.red;
        case 63: //key1Green
            return &DATA.value.key1.green;
        case 64: //key1Blue
            return &DATA.value.key1.blue;
        case 66: //key2Red
            return &DATA.value.key2.red;
        case 67: //key2Green
            return &DATA.value.key2.green;
        case 68: //key2Blue
            return &DATA.value.key2.blue;
        case 70: //key3Red
            return &DATA.value.key3.red;
        case 71: //key3Green
            return &DATA.value.key3.green;
        case 72: //key3Blue
            return &DATA.value.key3.blue;
        case 74: //key1A
            return &DATA.value.key1A;
        case 75: //key2A
            return &DATA.value.key2A;
        case 76: //key3A
            return &DATA.value.key3A;
        case 77: //key1Time
            return &DATA.value.key1Time;
        case 78: //key2Time
            return &DATA.value.key2Time;
        case 79: //key3Time
            return &DATA.value.key3Time;
        default:
            return NULL;
        }
    }

unsigned int EFSHRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //unused1
            return 3;
        case 16: //unused2
            return 1;
        case 29: //unused3
            return 1;
        case 65: //unused4
            return 1;
        case 69: //unused5
            return 1;
        case 73: //unused6
            return 1;
        default:
            return 0;
        }
    }

void EFSHRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return;
        case 16: //unused2
            *FieldValues = &DATA.value.fill.unused1;
            return;
        case 29: //unused3
            *FieldValues = &DATA.value.edge.unused1;
            return;
        case 65: //unused4
            *FieldValues = &DATA.value.key1.unused1;
            return;
        case 69: //unused5
            *FieldValues = &DATA.value.key2.unused1;
            return;
        case 73: //unused6
            *FieldValues = &DATA.value.key3.unused1;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void EFSHRecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //fillTexture
            ICON.Copy(FieldValue);
            break;
        case 7: //particleTexture
            ICO2.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void EFSHRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 8: //flags
            DATA.value.flags = FieldValue;
            break;
        case 13: //fillRed
            DATA.value.fill.red = FieldValue;
            break;
        case 14: //fillGreen
            DATA.value.fill.green = FieldValue;
            break;
        case 15: //fillBlue
            DATA.value.fill.blue = FieldValue;
            break;
        case 26: //edgeRed
            DATA.value.edge.red = FieldValue;
            break;
        case 27: //edgeGreen
            DATA.value.edge.green = FieldValue;
            break;
        case 28: //edgeBlue
            DATA.value.edge.blue = FieldValue;
            break;
        case 38: //memDBlend
            DATA.value.memDBlend = FieldValue;
            break;
        case 39: //partSBlend
            DATA.value.partSBlend = FieldValue;
            break;
        case 40: //partBlendOp
            DATA.value.partBlendOp = FieldValue;
            break;
        case 41: //partZFunc
            DATA.value.partZFunc = FieldValue;
            break;
        case 42: //partDBlend
            DATA.value.partDBlend = FieldValue;
            break;
        case 62: //key1Red
            DATA.value.key1.red = FieldValue;
            break;
        case 63: //key1Green
            DATA.value.key1.green = FieldValue;
            break;
        case 64: //key1Blue
            DATA.value.key1.blue = FieldValue;
            break;
        case 66: //key2Red
            DATA.value.key2.red = FieldValue;
            break;
        case 67: //key2Green
            DATA.value.key2.green = FieldValue;
            break;
        case 68: //key2Blue
            DATA.value.key2.blue = FieldValue;
            break;
        case 70: //key3Red
            DATA.value.key3.red = FieldValue;
            break;
        case 71: //key3Green
            DATA.value.key3.green = FieldValue;
            break;
        case 72: //key3Blue
            DATA.value.key3.blue = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void EFSHRecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 9: //unused1
            if(nSize != 3)
                return;
            DATA.value.unused1[0] = FieldValue[0];
            DATA.value.unused1[1] = FieldValue[1];
            DATA.value.unused1[2] = FieldValue[2];
            break;
        case 16: //unused2
            if(nSize != 1)
                return;
            DATA.value.fill.unused1 = FieldValue[0];
            break;
        case 29: //unused3
            if(nSize != 1)
                return;
            DATA.value.edge.unused1 = FieldValue[0];
            break;
        case 65: //unused4
            if(nSize != 1)
                return;
            DATA.value.key1.unused1 = FieldValue[0];
            break;
        case 69: //unused5
            if(nSize != 1)
                return;
            DATA.value.key2.unused1 = FieldValue[0];
            break;
        case 73: //unused6
            if(nSize != 1)
                return;
            DATA.value.key3.unused1 = FieldValue[0];
            break;
        default:
            return;
        }
    return;
    }

void EFSHRecord::SetOtherField(const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 10: //memSBlend
            DATA.value.memSBlend = FieldValue;
            break;
        case 11: //memBlendOp
            DATA.value.memBlendOp = FieldValue;
            break;
        case 12: //memZFunc
            DATA.value.memZFunc = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void EFSHRecord::SetField(const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 17: //fillAIn
            DATA.value.fillAIn = FieldValue;
            break;
        case 18: //fillAFull
            DATA.value.fillAFull = FieldValue;
            break;
        case 19: //fillAOut
            DATA.value.fillAOut = FieldValue;
            break;
        case 20: //fillAPRatio
            DATA.value.fillAPRatio = FieldValue;
            break;
        case 21: //fillAAmp
            DATA.value.fillAAmp = FieldValue;
            break;
        case 22: //fillAFreq
            DATA.value.fillAFreq = FieldValue;
            break;
        case 23: //fillAnimSpdU
            DATA.value.fillAnimSpdU = FieldValue;
            break;
        case 24: //fillAnimSpdV
            DATA.value.fillAnimSpdV = FieldValue;
            break;
        case 25: //edgeOff
            DATA.value.edgeOff = FieldValue;
            break;
        case 30: //edgeAIn
            DATA.value.edgeAIn = FieldValue;
            break;
        case 31: //edgeAFull
            DATA.value.edgeAFull = FieldValue;
            break;
        case 32: //edgeAOut
            DATA.value.edgeAOut = FieldValue;
            break;
        case 33: //edgeAPRatio
            DATA.value.edgeAPRatio = FieldValue;
            break;
        case 34: //edgeAAmp
            DATA.value.edgeAAmp = FieldValue;
            break;
        case 35: //edgeAFreq
            DATA.value.edgeAFreq = FieldValue;
            break;
        case 36: //fillAFRatio
            DATA.value.fillAFRatio = FieldValue;
            break;
        case 37: //edgeAFRatio
            DATA.value.edgeAFRatio = FieldValue;
            break;
        case 43: //partBUp
            DATA.value.partBUp = FieldValue;
            break;
        case 44: //partBFull
            DATA.value.partBFull = FieldValue;
            break;
        case 45: //partBDown
            DATA.value.partBDown = FieldValue;
            break;
        case 46: //partBFRatio
            DATA.value.partBFRatio = FieldValue;
            break;
        case 47: //partBPRatio
            DATA.value.partBPRatio = FieldValue;
            break;
        case 48: //partLTime
            DATA.value.partLTime = FieldValue;
            break;
        case 49: //partLDelta
            DATA.value.partLDelta = FieldValue;
            break;
        case 50: //partNSpd
            DATA.value.partNSpd = FieldValue;
            break;
        case 51: //partNAcc
            DATA.value.partNAcc = FieldValue;
            break;
        case 52: //partVel1
            DATA.value.partVel1 = FieldValue;
            break;
        case 53: //partVel2
            DATA.value.partVel2 = FieldValue;
            break;
        case 54: //partVel3
            DATA.value.partVel3 = FieldValue;
            break;
        case 55: //partAcc1
            DATA.value.partAcc1 = FieldValue;
            break;
        case 56: //partAcc2
            DATA.value.partAcc2 = FieldValue;
            break;
        case 57: //partAcc3
            DATA.value.partAcc3 = FieldValue;
            break;
        case 58: //partKey1
            DATA.value.partKey1 = FieldValue;
            break;
        case 59: //partKey2
            DATA.value.partKey2 = FieldValue;
            break;
        case 60: //partKey1Time
            DATA.value.partKey1Time = FieldValue;
            break;
        case 61: //partKey2Time
            DATA.value.partKey2Time = FieldValue;
            break;
        case 74: //key1A
            DATA.value.key1A = FieldValue;
            break;
        case 75: //key2A
            DATA.value.key2A = FieldValue;
            break;
        case 76: //key3A
            DATA.value.key3A = FieldValue;
            break;
        case 77: //key1Time
            DATA.value.key1Time = FieldValue;
            break;
        case 78: //key2Time
            DATA.value.key2Time = FieldValue;
            break;
        case 79: //key3Time
            DATA.value.key3Time = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int EFSHRecord::DeleteField(const unsigned int Field)
    {
    EFSHDATA defaultDATA;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //fillTexture
            ICON.Unload();
            break;
        case 7: //particleTexture
            ICO2.Unload();
            break;
        case 8: //flags
            DATA.value.flags = defaultDATA.flags;
            break;
        case 9: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            DATA.value.unused1[2] = defaultDATA.unused1[2];
            break;
        case 10: //memSBlend
            DATA.value.memSBlend = defaultDATA.memSBlend;
            break;
        case 11: //memBlendOp
            DATA.value.memBlendOp = defaultDATA.memBlendOp;
            break;
        case 12: //memZFunc
            DATA.value.memZFunc = defaultDATA.memZFunc;
            break;
        case 13: //fillRed
            DATA.value.fill.red = defaultDATA.fill.red;
            break;
        case 14: //fillGreen
            DATA.value.fill.green = defaultDATA.fill.green;
            break;
        case 15: //fillBlue
            DATA.value.fill.blue = defaultDATA.fill.blue;
            break;
        case 16: //unused2
            DATA.value.fill.unused1 = defaultDATA.fill.unused1;
            break;
        case 17: //fillAIn
            DATA.value.fillAIn = defaultDATA.fillAIn;
            break;
        case 18: //fillAFull
            DATA.value.fillAFull = defaultDATA.fillAFull;
            break;
        case 19: //fillAOut
            DATA.value.fillAOut = defaultDATA.fillAOut;
            break;
        case 20: //fillAPRatio
            DATA.value.fillAPRatio = defaultDATA.fillAPRatio;
            break;
        case 21: //fillAAmp
            DATA.value.fillAAmp = defaultDATA.fillAAmp;
            break;
        case 22: //fillAFreq
            DATA.value.fillAFreq = defaultDATA.fillAFreq;
            break;
        case 23: //fillAnimSpdU
            DATA.value.fillAnimSpdU = defaultDATA.fillAnimSpdU;
            break;
        case 24: //fillAnimSpdV
            DATA.value.fillAnimSpdV = defaultDATA.fillAnimSpdV;
            break;
        case 25: //edgeOff
            DATA.value.edgeOff = defaultDATA.edgeOff;
            break;
        case 26: //edgeRed
            DATA.value.edge.red = defaultDATA.edge.red;
            break;
        case 27: //edgeGreen
            DATA.value.edge.green = defaultDATA.edge.green;
            break;
        case 28: //edgeBlue
            DATA.value.edge.blue = defaultDATA.edge.blue;
            break;
        case 29: //unused3
            DATA.value.edge.unused1 = defaultDATA.edge.unused1;
            break;
        case 30: //edgeAIn
            DATA.value.edgeAIn = defaultDATA.edgeAIn;
            break;
        case 31: //edgeAFull
            DATA.value.edgeAFull = defaultDATA.edgeAFull;
            break;
        case 32: //edgeAOut
            DATA.value.edgeAOut = defaultDATA.edgeAOut;
            break;
        case 33: //edgeAPRatio
            DATA.value.edgeAPRatio = defaultDATA.edgeAPRatio;
            break;
        case 34: //edgeAAmp
            DATA.value.edgeAAmp = defaultDATA.edgeAAmp;
            break;
        case 35: //edgeAFreq
            DATA.value.edgeAFreq = defaultDATA.edgeAFreq;
            break;
        case 36: //fillAFRatio
            DATA.value.fillAFRatio = defaultDATA.fillAFRatio;
            break;
        case 37: //edgeAFRatio
            DATA.value.edgeAFRatio = defaultDATA.edgeAFRatio;
            break;
        case 38: //memDBlend
            DATA.value.memDBlend = defaultDATA.memDBlend;
            break;
        case 39: //partSBlend
            DATA.value.partSBlend = defaultDATA.partSBlend;
            break;
        case 40: //partBlendOp
            DATA.value.partBlendOp = defaultDATA.partBlendOp;
            break;
        case 41: //partZFunc
            DATA.value.partZFunc = defaultDATA.partZFunc;
            break;
        case 42: //partDBlend
            DATA.value.partDBlend = defaultDATA.partDBlend;
            break;
        case 43: //partBUp
            DATA.value.partBUp = defaultDATA.partBUp;
            break;
        case 44: //partBFull
            DATA.value.partBFull = defaultDATA.partBFull;
            break;
        case 45: //partBDown
            DATA.value.partBDown = defaultDATA.partBDown;
            break;
        case 46: //partBFRatio
            DATA.value.partBFRatio = defaultDATA.partBFRatio;
            break;
        case 47: //partBPRatio
            DATA.value.partBPRatio = defaultDATA.partBPRatio;
            break;
        case 48: //partLTime
            DATA.value.partLTime = defaultDATA.partLTime;
            break;
        case 49: //partLDelta
            DATA.value.partLDelta = defaultDATA.partLDelta;
            break;
        case 50: //partNSpd
            DATA.value.partNSpd = defaultDATA.partNSpd;
            break;
        case 51: //partNAcc
            DATA.value.partNAcc = defaultDATA.partNAcc;
            break;
        case 52: //partVel1
            DATA.value.partVel1 = defaultDATA.partVel1;
            break;
        case 53: //partVel2
            DATA.value.partVel2 = defaultDATA.partVel2;
            break;
        case 54: //partVel3
            DATA.value.partVel3 = defaultDATA.partVel3;
            break;
        case 55: //partAcc1
            DATA.value.partAcc1 = defaultDATA.partAcc1;
            break;
        case 56: //partAcc2
            DATA.value.partAcc2 = defaultDATA.partAcc2;
            break;
        case 57: //partAcc3
            DATA.value.partAcc3 = defaultDATA.partAcc3;
            break;
        case 58: //partKey1
            DATA.value.partKey1 = defaultDATA.partKey1;
            break;
        case 59: //partKey2
            DATA.value.partKey2 = defaultDATA.partKey2;
            break;
        case 60: //partKey1Time
            DATA.value.partKey1Time = defaultDATA.partKey1Time;
            break;
        case 61: //partKey2Time
            DATA.value.partKey2Time = defaultDATA.partKey2Time;
            break;
        case 62: //key1Red
            DATA.value.key1.red = defaultDATA.key1.red;
            break;
        case 63: //key1Green
            DATA.value.key1.green = defaultDATA.key1.green;
            break;
        case 64: //key1Blue
            DATA.value.key1.blue = defaultDATA.key1.blue;
            break;
        case 65: //unused4
            DATA.value.key1.unused1 = defaultDATA.key1.unused1;
            break;
        case 66: //key2Red
            DATA.value.key2.red = defaultDATA.key2.red;
            break;
        case 67: //key2Green
            DATA.value.key2.green = defaultDATA.key2.green;
            break;
        case 68: //key2Blue
            DATA.value.key2.blue = defaultDATA.key2.blue;
            break;
        case 69: //unused5
            DATA.value.key2.unused1 = defaultDATA.key2.unused1;
            break;
        case 70: //key3Red
            DATA.value.key3.red = defaultDATA.key3.red;
            break;
        case 71: //key3Green
            DATA.value.key3.green = defaultDATA.key3.green;
            break;
        case 72: //key3Blue
            DATA.value.key3.blue = defaultDATA.key3.blue;
            break;
        case 73: //unused6
            DATA.value.key3.unused1 = defaultDATA.key3.unused1;
            break;
        case 74: //key1A
            DATA.value.key1A = defaultDATA.key1A;
            break;
        case 75: //key2A
            DATA.value.key2A = defaultDATA.key2A;
            break;
        case 76: //key3A
            DATA.value.key3A = defaultDATA.key3A;
            break;
        case 77: //key1Time
            DATA.value.key1Time = defaultDATA.key1Time;
            break;
        case 78: //key2Time
            DATA.value.key2Time = defaultDATA.key2Time;
            break;
        case 79: //key3Time
            DATA.value.key3Time = defaultDATA.key3Time;
            break;
        default:
            return 0;
        }
    return 1;
    }
