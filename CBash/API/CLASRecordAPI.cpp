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
#include "..\Records\CLASRecord.h"

int CLASRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //description
            return STRING_FIELD;
        case 8: //iconPath
            return STRING_FIELD;
        case 9: //primary1
            return INT_FIELD;
        case 10: //primary2
            return INT_FIELD;
        case 11: //specialization
            return UINT_FIELD;
        case 12: //major1
        case 13: //major2
        case 14: //major3
        case 15: //major4
        case 16: //major5
        case 17: //major6
        case 18: //major7
            return INT_FIELD;
        case 19: //flags
            return UINT_FIELD;
        case 20: //services
            return UINT_FIELD;
        case 21: //trainSkill
            return BYTE_FIELD;
        case 22: //trainLevel
            return UBYTE_FIELD;
        case 23: //unused1
            return BYTES_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CLASRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //description
            return DESC.value;
        case 8: //iconPath
            return ICON.value;
        case 9: //primary1
            return &DATA.value.primary[0];
        case 10: //primary2
            return &DATA.value.primary[1];
        case 11: //specialization
            return &DATA.value.specialization;
        case 12: //major1
            return &DATA.value.major[0];
        case 13: //major2
            return &DATA.value.major[1];
        case 14: //major3
            return &DATA.value.major[2];
        case 15: //major4
            return &DATA.value.major[3];
        case 16: //major5
            return &DATA.value.major[4];
        case 17: //major6
            return &DATA.value.major[5];
        case 18: //major7
            return &DATA.value.major[6];
        case 19: //flags
            return &DATA.value.flags;
        case 20: //services
            return &DATA.value.services;
        case 21: //trainSkill
            return &DATA.value.trainSkill;
        case 22: //trainLevel
            return &DATA.value.trainLevel;
        case 23: //unused1
            return &DATA.value.unused1[0];
        default:
            return NULL;
        }
    }

unsigned int CLASRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 23: //unused1
            return 2;
        default:
            return 0;
        }
    }

void CLASRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 23: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void CLASRecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 7: //description
            DESC.Copy(FieldValue);
            break;
        case 8: //iconPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void CLASRecord::SetField(const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 9: //primary1
            DATA.value.primary[0] = FieldValue;
            break;
        case 10: //primary2
            DATA.value.primary[1] = FieldValue;
            break;
        case 12: //major1
            DATA.value.major[0] = FieldValue;
            break;
        case 13: //major2
            DATA.value.major[1] = FieldValue;
            break;
        case 14: //major3
            DATA.value.major[2] = FieldValue;
            break;
        case 15: //major4
            DATA.value.major[3] = FieldValue;
            break;
        case 16: //major5
            DATA.value.major[4] = FieldValue;
            break;
        case 17: //major6
            DATA.value.major[5] = FieldValue;
            break;
        case 18: //major7
            DATA.value.major[6] = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CLASRecord::SetOtherField(const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 11: //specialization
            DATA.value.specialization = FieldValue;
            break;
        case 19: //flags
            DATA.value.flags = FieldValue;
            break;
        case 20: //services
            DATA.value.services = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CLASRecord::SetField(const unsigned int Field, char FieldValue)
    {
    switch(Field)
        {
        case 21: //trainSkill
            DATA.value.trainSkill = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CLASRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 22: //trainLevel
            DATA.value.trainLevel = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CLASRecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 23: //unused1
            if(nSize != 2)
                return;
            DATA.value.unused1[0] = FieldValue[0];
            DATA.value.unused1[1] = FieldValue[1];
            break;
        default:
            return;
        }
    return;
    }

int CLASRecord::DeleteField(const unsigned int Field)
    {
    CLASDATA defaultDATA;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //description
            DESC.Unload();
            break;
        case 8: //iconPath
            ICON.Unload();
            break;
        case 9: //primary1
            DATA.value.primary[0] = defaultDATA.primary[0];
            break;
        case 10: //primary2
            DATA.value.primary[1] = defaultDATA.primary[1];
            break;
        case 11: //specialization
            DATA.value.specialization = defaultDATA.specialization;
            break;
        case 12: //major1
            DATA.value.major[0] = defaultDATA.major[0];
            break;
        case 13: //major2
            DATA.value.major[1] = defaultDATA.major[1];
            break;
        case 14: //major3
            DATA.value.major[2] = defaultDATA.major[2];
            break;
        case 15: //major4
            DATA.value.major[3] = defaultDATA.major[3];
            break;
        case 16: //major5
            DATA.value.major[4] = defaultDATA.major[4];
            break;
        case 17: //major6
            DATA.value.major[5] = defaultDATA.major[5];
            break;
        case 18: //major7
            DATA.value.major[6] = defaultDATA.major[6];
            break;
        case 19: //flags
            DATA.value.flags = defaultDATA.flags;
            break;
        case 20: //services
            DATA.value.services = defaultDATA.services;
            break;
        case 21: //trainSkill
            DATA.value.trainSkill = defaultDATA.trainSkill;
            break;
        case 22: //trainLevel
            DATA.value.trainLevel = defaultDATA.trainLevel;
            break;
        case 23: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            break;
        default:
            return 0;
        }
    return 1;
    }
