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
#include "..\Records\WEAPRecord.h"

int WEAPRecord::GetOtherFieldType(const unsigned int Field)
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
        case 11: //script
            return FID_FIELD;
        case 12: //enchantment
            return FID_FIELD;
        case 13: //enchantPoints
            return USHORT_FIELD;
        case 14: //weaponType
            return UINT_FIELD;
        case 15: //speed
            return FLOAT_FIELD;
        case 16: //reach
            return FLOAT_FIELD;
        case 17: //flags
            return UINT_FIELD;
        case 18: //value
            return UINT_FIELD;
        case 19: //health
            return UINT_FIELD;
        case 20: //weight
            return FLOAT_FIELD;
        case 21: //damage
            return USHORT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * WEAPRecord::GetOtherField(const unsigned int Field)
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
        case 11: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 12: //enchantment
            if(ENAM.IsLoaded())
                return &ENAM->fid;
            return NULL;
        case 13: //enchantPoints
            if(ANAM.IsLoaded())
                return &ANAM->enchantPoints;
            return NULL;
        case 14: //weaponType
            return &DATA.value.weaponType;
        case 15: //speed
            return &DATA.value.speed;
        case 16: //reach
            return &DATA.value.reach;
        case 17: //flags
            return &DATA.value.flags;
        case 18: //value
            return &DATA.value.value;
        case 19: //health
            return &DATA.value.health;
        case 20: //weight
            return &DATA.value.weight;
        case 21: //damage
            return &DATA.value.damage;
        default:
            return NULL;
        }
    }

unsigned int WEAPRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        default:
            return 0;
        }
    }

void WEAPRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void WEAPRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void WEAPRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 15: //speed
            DATA.value.speed = FieldValue;
            break;
        case 16: //reach
            DATA.value.reach = FieldValue;
            break;
        case 20: //weight
            DATA.value.weight = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WEAPRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void WEAPRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 11: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 12: //enchantment
            ENAM.Load();
            ENAM->fid = FieldValue;
            FormIDHandler.AddMaster(ENAM->fid);
            break;
        case 14: //weaponType
            DATA.value.weaponType = FieldValue;
            break;
        case 17: //flags
            DATA.value.flags = FieldValue;
            break;
        case 18: //value
            DATA.value.value = FieldValue;
            break;
        case 19: //health
            DATA.value.health = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WEAPRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 13: //enchantPoints
            ANAM.Load();
            ANAM->enchantPoints = FieldValue;
            break;
        case 21: //damage
            DATA.value.damage = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int WEAPRecord::DeleteField(const unsigned int Field)
    {
    WEAPDATA defaultDATA;
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
        case 11: //script
            SCRI.Unload();
            break;
        case 12: //enchantment
            ENAM.Unload();
            break;
        case 13: //enchantPoints
            ANAM.Unload();
            break;
        case 14: //weaponType
            DATA.value.weaponType = defaultDATA.weaponType;
            break;
        case 15: //speed
            DATA.value.speed = defaultDATA.speed;
            break;
        case 16: //reach
            DATA.value.reach = defaultDATA.reach;
            break;
        case 17: //flags
            DATA.value.flags = defaultDATA.flags;
            break;
        case 18: //value
            DATA.value.value = defaultDATA.value;
            break;
        case 19: //health
            DATA.value.health = defaultDATA.health;
            break;
        case 20: //weight
            DATA.value.weight = defaultDATA.weight;
            break;
        case 21: //damage
            DATA.value.damage = defaultDATA.damage;
            break;
        default:
            return 0;
        }
    return 1;
    }