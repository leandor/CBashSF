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
#include "..\AMMORecord.h"

signed long AMMORecord::GetOtherFieldType(const unsigned long Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //modPath
            return STRING_FIELD;
        case 8: //modb
            return FLOAT_FIELD;
        case 9: //modt_p
            return BYTES_FIELD;
        case 10: //iconPath
            return STRING_FIELD;
        case 11: //enchantment
            return FID_FIELD;
        case 12: //enchantPoints
            return USHORT_FIELD;
        case 13: //speed
            return FLOAT_FIELD;
        case 14: //flags
            return UBYTE_FIELD;
        case 15: //unused1
            return BYTES_FIELD;
        case 16: //value
            return UINT_FIELD;
        case 17: //weight
            return FLOAT_FIELD;
        case 18: //damage
            return USHORT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * AMMORecord::GetOtherField(const unsigned long Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //modPath
            if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
                return MODL->MODL.value;
            return NULL;
        case 8: //modb
            if(MODL.IsLoaded() && MODL->MODB.IsLoaded())
                return &MODL->MODB.value.MODB;
            return NULL;
        case 10: //iconPath
            return ICON.value;
        case 11: //enchantment
            if(ENAM.IsLoaded())
                return &ENAM->fid;
            return NULL;
        case 12: //enchantPoints
            if(ANAM.IsLoaded())
                return &ANAM->enchantPoints;
            return NULL;
        case 13: //speed
            return &DATA.value.speed;
        case 14: //flags
            return &DATA.value.flags;
        case 16: //value
            return &DATA.value.value;
        case 17: //weight
            return &DATA.value.weight;
        case 18: //damage
            return &DATA.value.damage;
        default:
            return NULL;
        }
    }

unsigned long AMMORecord::GetFieldArraySize(const unsigned long Field)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        case 15: //unused1
            return 3;
        default:
            return 0;
        }
    }

void AMMORecord::GetFieldArray(const unsigned long Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 15: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void AMMORecord::SetField(const unsigned long Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 7: //modPath
            MODL.Load();
            MODL->MODL.Copy(FieldValue);
            break;
        case 10: //iconPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void AMMORecord::SetField(const unsigned long Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 13: //speed
            DATA.value.speed = FieldValue;
            break;
        case 17: //weight
            DATA.value.weight = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void AMMORecord::SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize)
    {
    switch(Field)
        {
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        case 15: //unused1
            if(nSize != 3)
                return;
            DATA.value.unused1[0] = FieldValue[0];
            DATA.value.unused1[1] = FieldValue[1];
            DATA.value.unused1[2] = FieldValue[2];
            break;
        default:
            return;
        }
    return;
    }

void AMMORecord::SetOtherField(const unsigned long Field, unsigned long FieldValue)
    {
    switch(Field)
        {
        case 11: //enchantment
            ENAM.Load();
            ENAM->fid = FieldValue;
            break;
        case 16: //value
            DATA.value.value = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void AMMORecord::SetField(const unsigned long Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 12: //enchantPoints
            ANAM.Load();
            ANAM->enchantPoints = FieldValue;
            break;
        case 18: //damage
            DATA.value.damage = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void AMMORecord::SetField(const unsigned long Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 14: //flags
            DATA.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

signed long AMMORecord::DeleteField(const unsigned long Field)
    {
    AMMODATA defaultDATA;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            break;
        case 8: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            break;
        case 9: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            break;
        case 10: //iconPath
            ICON.Unload();
            break;
        case 11: //enchantment
            ENAM.Unload();
            break;
        case 12: //enchantPoints
            ANAM.Unload();
            break;
        case 13: //speed
            DATA.value.speed = defaultDATA.speed;
            break;
        case 14: //flags
            DATA.value.flags = defaultDATA.flags;
            break;
        case 15: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            DATA.value.unused1[2] = defaultDATA.unused1[2];
            break;
        case 16: //value
            DATA.value.value = defaultDATA.value;
            break;
        case 17: //weight
            DATA.value.weight = defaultDATA.weight;
            break;
        case 18: //damage
            DATA.value.damage = defaultDATA.damage;
            break;
        default:
            return 0;
        }
    return 1;
    }
