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
#include "..\Records\ARMORecord.h"

int ARMORecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //script
            return FID_FIELD;
        case 8: //enchantment
            return FID_FIELD;
        case 9: //enchantPoints
            return USHORT_FIELD;
        case 10: //flags
            return UINT_FIELD;
        case 11: //maleBody_modPath
            return STRING_FIELD;
        case 12: //maleBody_modb
            return FLOAT_FIELD;
        case 13: //maleBody_modt_p
            return BYTES_FIELD;
        case 14: //maleWorld_modPath
            return STRING_FIELD;
        case 15: //maleWorld_modb
            return FLOAT_FIELD;
        case 16: //maleWorld_modt_p
            return BYTES_FIELD;
        case 17: //maleIconPath
            return STRING_FIELD;
        case 18: //femaleBody_modPath
            return STRING_FIELD;
        case 19: //femaleBody_modb
            return FLOAT_FIELD;
        case 20: //femaleBody_modt_p
            return BYTES_FIELD;
        case 21: //femaleWorld_modPath
            return STRING_FIELD;
        case 22: //femaleWorld_modb
            return FLOAT_FIELD;
        case 23: //femaleWorld_modt_p
            return BYTES_FIELD;
        case 24: //femaleIconPath
            return STRING_FIELD;
        case 25: //strength
            return USHORT_FIELD;
        case 26: //value
            return UINT_FIELD;
        case 27: //health
            return UINT_FIELD;
        case 28: //weight
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * ARMORecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 8: //enchantment
            if(ENAM.IsLoaded())
                return &ENAM->fid;
            return NULL;
        case 9: //enchantPoints
            if(ANAM.IsLoaded())
                return &ANAM->enchantPoints;
            return NULL;
        case 10: //flags
            return &BMDT.value.flags;
        case 11: //maleBody_modPath
            return MODL.MODL.value;
        case 12: //maleBody_modb
            return &MODL.MODB.value.MODB;
        case 14: //maleWorld_modPath
            return MOD2.MODL.value;
        case 15: //maleWorld_modb
            return &MOD2.MODB.value.MODB;
        case 17: //maleIconPath
            return ICON.value;
        case 18: //femaleBody_modPath
            return MOD3.MODL.value;
        case 19: //femaleBody_modb
            return &MOD3.MODB.value.MODB;
        case 21: //femaleWorld_modPath
            return MOD4.MODL.value;
        case 22: //femaleWorld_modb
            return &MOD4.MODB.value.MODB;
        case 24: //femaleIconPath
            return ICO2.value;
        case 25: //strength
            return &DATA.value.strength;
        case 26: //value
            return &DATA.value.value;
        case 27: //health
            return &DATA.value.health;
        case 28: //weight
            return &DATA.value.weight;
        default:
            return NULL;
        }
    }

unsigned int ARMORecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 13: //maleBody_modt_p
            return MODL.MODT.size;
        case 16: //maleWorld_modt_p
            return MOD2.MODT.size;
        case 20: //femaleBody_modt_p
            return MOD3.MODT.size;
        case 23: //femaleWorld_modt_p
            return MOD4.MODT.size;
        default:
            return 0;
        }
    }

void ARMORecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 13: //maleBody_modt_p
            *FieldValues = MODL.MODT.value;
            return;
        case 16: //maleWorld_modt_p
            *FieldValues = MOD2.MODT.value;
            return;
        case 20: //femaleBody_modt_p
            *FieldValues = MOD3.MODT.value;
            return;
        case 23: //femaleWorld_modt_p
            *FieldValues = MOD4.MODT.value;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void ARMORecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 11: //maleBody_modPath
            MODL.MODL.Copy(FieldValue);
            break;
        case 14: //maleWorld_modPath
            MOD2.MODL.Copy(FieldValue);
            break;
        case 17: //maleIconPath
            ICON.Copy(FieldValue);
            break;
        case 18: //femaleBody_modPath
            MOD3.MODL.Copy(FieldValue);
            break;
        case 21: //femaleWorld_modPath
            MOD4.MODL.Copy(FieldValue);
            break;
        case 24: //femaleIconPath
            ICO2.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void ARMORecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 7: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 8: //enchantment
            ENAM.Load();
            ENAM->fid = FieldValue;
            FormIDHandler.AddMaster(ENAM->fid);
            break;
        case 10: //flags
            BMDT.value.flags = FieldValue;
            break;
        case 26: //value
            DATA.value.value = FieldValue;
            break;
        case 27: //health
            DATA.value.health = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void ARMORecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 9: //enchantPoints
            ANAM.Load();
            ANAM->enchantPoints = FieldValue;
            break;
        case 25: //strength
            DATA.value.strength = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void ARMORecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 12: //maleBody_modb
            MODL.MODB.value.MODB = FieldValue;
            MODL.MODB.isLoaded = true;
            break;
        case 15: //maleWorld_modb
            MOD2.MODB.value.MODB = FieldValue;
            MOD2.MODB.isLoaded = true;
            break;
        case 19: //femaleBody_modb
            MOD3.MODB.value.MODB = FieldValue;
            MOD3.MODB.isLoaded = true;
            break;
        case 22: //femaleWorld_modb
            MOD4.MODB.value.MODB = FieldValue;
            MOD4.MODB.isLoaded = true;
            break;
        case 28: //weight
            DATA.value.weight = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void ARMORecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 13: //maleBody_modt_p
            MODL.MODT.Copy(FieldValue, nSize);
            break;
        case 16: //maleWorld_modt_p
            MOD2.MODT.Copy(FieldValue, nSize);
            break;
        case 20: //femaleBody_modt_p
            MOD3.MODT.Copy(FieldValue, nSize);
            break;
        case 23: //femaleWorld_modt_p
            MOD4.MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }
