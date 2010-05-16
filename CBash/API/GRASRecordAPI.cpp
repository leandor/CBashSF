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
#include "..\Records\GRASRecord.h"

int GRASRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //modPath
            return STRING_FIELD;
        case 7: //modb
            return FLOAT_FIELD;
        case 8: //modt_p
            return BYTES_FIELD;
        case 9: //density
            return UBYTE_FIELD;
        case 10: //minSlope
            return UBYTE_FIELD;
        case 11: //maxSlope
            return UBYTE_FIELD;
        case 12: //unused1
            return BYTES_FIELD;
        case 13: //waterDistance
            return USHORT_FIELD;
        case 14: //unused2
            return BYTES_FIELD;
        case 15: //waterOp
            return UINT_FIELD;
        case 16: //posRange
            return FLOAT_FIELD;
        case 17: //heightRange
            return FLOAT_FIELD;
        case 18: //colorRange
            return FLOAT_FIELD;
        case 19: //wavePeriod
            return FLOAT_FIELD;
        case 20: //flags
            return UBYTE_FIELD;
        case 21: //unused3
            return BYTES_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * GRASRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //modPath
            return MODL.MODL.value;
        case 7: //modb
            return &MODL.MODB.value.MODB;
        case 9: //density
            return &DATA.value.density;
        case 10: //minSlope
            return &DATA.value.minSlope;
        case 11: //maxSlope
            return &DATA.value.maxSlope;
        case 13: //waterDistance
            return &DATA.value.waterDistance;
        case 15: //waterOp
            return &DATA.value.waterOp;
        case 16: //posRange
            return &DATA.value.posRange;
        case 17: //heightRange
            return &DATA.value.heightRange;
        case 18: //colorRange
            return &DATA.value.colorRange;
        case 19: //wavePeriod
            return &DATA.value.wavePeriod;
        case 20: //flags
            return &DATA.value.flags;
        default:
            return NULL;
        }
    }

unsigned int GRASRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //modt_p
            return MODL.MODT.size;
        case 12: //unused1
            return 1;
        case 14: //unused2
            return 2;
        case 21: //unused3
            return 3;
        default:
            return 0;
        }
    }

void GRASRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //modt_p
            *FieldValues = MODL.MODT.value;
            return;
        case 12: //unused1
            *FieldValues = &DATA.value.unused1;
            return;
        case 14: //unused2
            *FieldValues = &DATA.value.unused2[0];
            return;
        case 21: //unused3
            *FieldValues = &DATA.value.unused3[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void GRASRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //modPath
            MODL.MODL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void GRASRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 7: //modb
            MODL.MODB.value.MODB = FieldValue;
            MODL.MODB.isLoaded = true;
            break;
        case 16: //posRange
            DATA.value.posRange = FieldValue;
            break;
        case 17: //heightRange
            DATA.value.heightRange = FieldValue;
            break;
        case 18: //colorRange
            DATA.value.colorRange = FieldValue;
            break;
        case 19: //wavePeriod
            DATA.value.wavePeriod = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void GRASRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //modt_p
            MODL.MODT.Copy(FieldValue, nSize);
            break;
        case 12: //unused1
            if(nSize != 1)
                return;
            DATA.value.unused1 = FieldValue[0];
            break;
        case 14: //unused2
            if(nSize != 2)
                return;
            DATA.value.unused2[0] = FieldValue[0];
            DATA.value.unused2[1] = FieldValue[1];
            break;
        case 21: //unused3
            if(nSize != 3)
                return;
            DATA.value.unused3[0] = FieldValue[0];
            DATA.value.unused3[1] = FieldValue[1];
            DATA.value.unused3[2] = FieldValue[2];
            break;
        default:
            return;
        }
    return;
    }

void GRASRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 9: //density
            DATA.value.density = FieldValue;
            break;
        case 10: //minSlope
            DATA.value.minSlope = FieldValue;
            break;
        case 11: //maxSlope
            DATA.value.maxSlope = FieldValue;
            break;
        case 20: //flags
            DATA.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void GRASRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 13: //waterDistance
            DATA.value.waterDistance = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void GRASRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 15: //waterOp
            DATA.value.waterOp = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

