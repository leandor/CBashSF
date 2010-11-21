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
#include "..\..\Common.h"
#include "..\SKILRecord.h"

signed long SKILRecord::GetOtherFieldType(const unsigned long Field)
    {
    switch(Field)
        {
        case 6: //skill
            return INT_FIELD;
        case 7: //description
            return STRING_FIELD;
        case 8: //iconPath
            return STRING_FIELD;
        case 9: //action
            return INT_FIELD;
        case 10: //attribute
            return INT_FIELD;
        case 11: //specialization
            return UINT_FIELD;
        case 12: //use0
            return FLOAT_FIELD;
        case 13: //use1
            return FLOAT_FIELD;
        case 14: //apprentice
            return STRING_FIELD;
        case 15: //journeyman
            return STRING_FIELD;
        case 16: //expert
            return STRING_FIELD;
        case 17: //master
            return STRING_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * SKILRecord::GetOtherField(const unsigned long Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //skill
            return &INDX.value.skill;
        case 7: //description
            return DESC.value;
        case 8: //iconPath
            return ICON.value;
        case 9: //action
            return &DATA.value.action;
        case 10: //attribute
            return &DATA.value.attribute;
        case 11: //specialization
            return &DATA.value.specialization;
        case 12: //use0
            return &DATA.value.use0;
        case 13: //use1
            return &DATA.value.use1;
        case 14: //apprentice
            return ANAM.value;
        case 15: //journeyman
            return JNAM.value;
        case 16: //expert
            return ENAM.value;
        case 17: //master
            return MNAM.value;
        default:
            return NULL;
        }
    }

void SKILRecord::SetField(const unsigned long Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 7: //description
            DESC.Copy(FieldValue);
            break;
        case 8: //iconPath
            ICON.Copy(FieldValue);
            break;
        case 14: //apprentice
            ANAM.Copy(FieldValue);
            break;
        case 15: //journeyman
            JNAM.Copy(FieldValue);
            break;
        case 16: //expert
            ENAM.Copy(FieldValue);
            break;
        case 17: //master
            MNAM.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void SKILRecord::SetField(const unsigned long Field, signed long FieldValue)
    {
    switch(Field)
        {
        case 6: //skill
            INDX.value.skill = FieldValue;
            break;
        case 9: //action
            DATA.value.action = FieldValue;
            break;
        case 10: //attribute
            DATA.value.attribute = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SKILRecord::SetOtherField(const unsigned long Field, unsigned long FieldValue)
    {
    switch(Field)
        {
        case 11: //specialization
            DATA.value.specialization = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SKILRecord::SetField(const unsigned long Field, float FieldValue)
    {
    switch(Field)
        {
        case 12: //use0
            DATA.value.use0 = FieldValue;
            break;
        case 13: //use1
            DATA.value.use1 = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

signed long SKILRecord::DeleteField(const unsigned long Field)
    {
    SKILDATA defaultDATA;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //skill
            INDX.Unload();
            break;
        case 7: //description
            DESC.Unload();
            break;
        case 8: //iconPath
            ICON.Unload();
            break;
        case 9: //action
            ICON.Unload();
            break;
        case 10: //attribute
            DATA.value.attribute = defaultDATA.attribute;
            break;
        case 11: //specialization
            DATA.value.specialization = defaultDATA.specialization;
            break;
        case 12: //use0
            DATA.value.use0 = defaultDATA.use0;
            break;
        case 13: //use1
            DATA.value.use1 = defaultDATA.use1;
            break;
        case 14: //apprentice
            ANAM.Unload();
            break;
        case 15: //journeyman
            JNAM.Unload();
            break;
        case 16: //expert
            ENAM.Unload();
            break;
        case 17: //master
            MNAM.Unload();
            break;
        default:
            return 0;
        }
    return 1;
    }
