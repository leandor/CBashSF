# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
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
        case 13: //fill.red
            return UBYTE_FIELD;
        case 14: //fill.green
            return UBYTE_FIELD;
        case 15: //fill.blue
            return UBYTE_FIELD;
        case 16: //fill.unused1
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
        case 26: //edge.red
            return UBYTE_FIELD;
        case 27: //edge.green
            return UBYTE_FIELD;
        case 28: //edge.blue
            return UBYTE_FIELD;
        case 29: //edge.unused1
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
        case 62: //key1.red
            return UBYTE_FIELD;
        case 63: //key1.green
            return UBYTE_FIELD;
        case 64: //key1.blue
            return UBYTE_FIELD;
        case 65: //key1.unused1
            return BYTES_FIELD;
        case 66: //key2.red
            return UBYTE_FIELD;
        case 67: //key2.green
            return UBYTE_FIELD;
        case 68: //key2.blue
            return UBYTE_FIELD;
        case 69: //key2.unused1
            return BYTES_FIELD;
        case 70: //key3.red
            return UBYTE_FIELD;
        case 71: //key3.green
            return UBYTE_FIELD;
        case 72: //key3.blue
            return UBYTE_FIELD;
        case 73: //key2.unused1
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
        case 13: //fill.red
            return &DATA.value.fill.red;
        case 14: //fill.green
            return &DATA.value.fill.green;
        case 15: //fill.blue
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
        case 26: //edge.red
            return &DATA.value.edge.red;
        case 27: //edge.green
            return &DATA.value.edge.green;
        case 28: //edge.blue
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
        case 62: //key1.red
            return &DATA.value.key1.red;
        case 63: //key1.green
            return &DATA.value.key1.green;
        case 64: //key1.blue
            return &DATA.value.key1.blue;
        case 66: //key2.red
            return &DATA.value.key2.red;
        case 67: //key2.green
            return &DATA.value.key2.green;
        case 68: //key2.blue
            return &DATA.value.key2.blue;
        case 70: //key3.red
            return &DATA.value.key3.red;
        case 71: //key3.green
            return &DATA.value.key3.green;
        case 72: //key3.blue
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
        case 16: //fill.unused1
            return 1;
        case 29: //edge.unused1
            return 1;
        case 65: //key1.unused1
            return 1;
        case 69: //key2.unused1
            return 1;
        case 73: //key2.unused1
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
        case 16: //fill.unused1
            *FieldValues = &DATA.value.fill.unused1;
            return;
        case 29: //edge.unused1
            *FieldValues = &DATA.value.edge.unused1;
            return;
        case 65: //key1.unused1
            *FieldValues = &DATA.value.key1.unused1;
            return;
        case 69: //key2.unused1
            *FieldValues = &DATA.value.key2.unused1;
            return;
        case 73: //key2.unused1
            *FieldValues = &DATA.value.key2.unused1;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void EFSHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void EFSHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 8: //flags
            DATA.value.flags = FieldValue;
            break;
        case 13: //fill.red
            DATA.value.fill.red = FieldValue;
            break;
        case 14: //fill.green
            DATA.value.fill.green = FieldValue;
            break;
        case 15: //fill.blue
            DATA.value.fill.blue = FieldValue;
            break;
        case 26: //edge.red
            DATA.value.edge.red = FieldValue;
            break;
        case 27: //edge.green
            DATA.value.edge.green = FieldValue;
            break;
        case 28: //edge.blue
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
        case 62: //key1.red
            DATA.value.key1.red = FieldValue;
            break;
        case 63: //key1.green
            DATA.value.key1.green = FieldValue;
            break;
        case 64: //key1.blue
            DATA.value.key1.blue = FieldValue;
            break;
        case 66: //key2.red
            DATA.value.key2.red = FieldValue;
            break;
        case 67: //key2.green
            DATA.value.key2.green = FieldValue;
            break;
        case 68: //key2.blue
            DATA.value.key2.blue = FieldValue;
            break;
        case 70: //key3.red
            DATA.value.key3.red = FieldValue;
            break;
        case 71: //key3.green
            DATA.value.key3.green = FieldValue;
            break;
        case 72: //key3.blue
            DATA.value.key3.blue = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void EFSHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
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
        case 16: //fill.unused1
            if(nSize != 1)
                return;
            DATA.value.fill.unused1 = FieldValue[0];
            break;
        case 29: //edge.unused1
            if(nSize != 1)
                return;
            DATA.value.edge.unused1 = FieldValue[0];
            break;
        case 65: //key1.unused1
            if(nSize != 1)
                return;
            DATA.value.key1.unused1 = FieldValue[0];
            break;
        case 69: //key2.unused1
            if(nSize != 1)
                return;
            DATA.value.key2.unused1 = FieldValue[0];
            break;
        case 73: //key2.unused1
            if(nSize != 1)
                return;
            DATA.value.key2.unused1 = FieldValue[0];
            break;
        default:
            return;
        }
    return;
    }

void EFSHRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
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

void EFSHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
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
