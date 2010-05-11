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
#include "..\Records\SOUNRecord.h"

int SOUNRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //soundFile
            return STRING_FIELD;
        case 7: //minDistance
            return UBYTE_FIELD;
        case 8: //maxDistance
            return UBYTE_FIELD;
        case 9: //freqAdjustment
            return BYTE_FIELD;
        case 10: //unused1
            return UBYTE_FIELD;
        case 11: //flags
            return USHORT_FIELD;
        case 12: //unused2
            return BYTES_FIELD;
        case 13: //staticAtten
            return SHORT_FIELD;
        case 14: //stopTime
            return UBYTE_FIELD;
        case 15: //startTime
            return UBYTE_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * SOUNRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //soundFile
            return FNAM.value;
        case 7: //minDistance
            return &SNDX.value.minDistance;
        case 8: //maxDistance
            return &SNDX.value.maxDistance;
        case 9: //freqAdjustment
            return &SNDX.value.freqAdjustment;
        case 10: //unused1
            return &SNDX.value.unused1;
        case 11: //flags
            return &SNDX.value.flags;
        case 13: //staticAtten
            return &SNDX.value.staticAtten;
        case 14: //stopTime
            return &SNDX.value.stopTime;
        case 15: //startTime
            return &SNDX.value.startTime;
        default:
            return NULL;
        }
    }

unsigned int SOUNRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 12: //unused2
            return 2;
        default:
            return 0;
        }
    }

void SOUNRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 12: //unused2
            *FieldValues = &SNDX.value.unused2[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void SOUNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //soundFile
            FNAM.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void SOUNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 7: //minDistance
            SNDX.value.minDistance = FieldValue;
            break;
        case 8: //maxDistance
            SNDX.value.maxDistance = FieldValue;
            break;
        case 10: //unused1
            SNDX.value.unused1 = FieldValue;
            break;
        case 14: //stopTime
            SNDX.value.stopTime = FieldValue;
            break;
        case 15: //startTime
            SNDX.value.startTime = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SOUNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue)
    {
    switch(Field)
        {
        case 9: //freqAdjustment
            SNDX.value.freqAdjustment = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SOUNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 11: //flags
            SNDX.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SOUNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 12: //unused2
            if(nSize != 2)
                return;
            SNDX.value.unused2[0] = FieldValue[0];
            SNDX.value.unused2[1] = FieldValue[1];
            break;
        default:
            return;
        }
    return;
    }

void SOUNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, short FieldValue)
    {
    switch(Field)
        {
        case 13: //staticAtten
            SNDX.value.staticAtten = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

