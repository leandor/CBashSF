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
#include "..\Records\LIGHRecord.h"

int LIGHRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //modPath
            return STRING_FIELD;
        case 7: //modb
            return FLOAT_FIELD;
        case 8: //modt_p
            return BYTES_FIELD;
        case 9: //script
            return FID_FIELD;
        case 10: //full
            return STRING_FIELD;
        case 11: //iconPath
            return STRING_FIELD;
        case 12: //duration
            return INT_FIELD;
        case 13: //radius
            return UINT_FIELD;
        case 14: //red
            return UBYTE_FIELD;
        case 15: //green
            return UBYTE_FIELD;
        case 16: //blue
            return UBYTE_FIELD;
        case 17: //unused1
            return BYTES_FIELD;
        case 18: //flags
            return UINT_FIELD;
        case 19: //falloff
            return FLOAT_FIELD;
        case 20: //fov
            return FLOAT_FIELD;
        case 21: //value
            return UINT_FIELD;
        case 22: //weight
            return FLOAT_FIELD;
        case 23: //fade
            return FLOAT_FIELD;
        case 24: //sound
            return FID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LIGHRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //modPath
            if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
                return MODL->MODL.value;
            return NULL;
        case 7: //modb
            if(MODL.IsLoaded() && MODL->MODB.IsLoaded())
                return &MODL->MODB.value.MODB;
            return NULL;
        case 9: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 10: //full
            return FULL.value;
        case 11: //iconPath
            return ICON.value;
        case 12: //duration
            return &DATA.value.duration;
        case 13: //radius
            return &DATA.value.radius;
        case 14: //red
            return &DATA.value.color.red;
        case 15: //green
            return &DATA.value.color.green;
        case 16: //blue
            return &DATA.value.color.blue;
        case 18: //flags
            return &DATA.value.flags;
        case 19: //falloff
            return &DATA.value.falloff;
        case 20: //fov
            return &DATA.value.fov;
        case 21: //value
            return &DATA.value.value;
        case 22: //weight
            return &DATA.value.weight;
        case 23: //fade
            if(FNAM.IsLoaded())
                return &FNAM->fade;
            return NULL;
        case 24: //sound
            if(SNAM.IsLoaded())
                return &SNAM->fid;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned int LIGHRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        case 17: //unused1
            return 1;
        default:
            return 0;
        }
    }

void LIGHRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 17: //unused1
            *FieldValues = &DATA.value.color.unused1;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void LIGHRecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //modPath
            MODL.Load();
            MODL->MODL.Copy(FieldValue);
            break;
        case 10: //full
            FULL.Copy(FieldValue);
            break;
        case 11: //iconPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void LIGHRecord::SetField(const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 7: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 19: //falloff
            DATA.value.falloff = FieldValue;
            break;
        case 20: //fov
            DATA.value.fov = FieldValue;
            break;
        case 22: //weight
            DATA.value.weight = FieldValue;
            break;
        case 23: //fade
            FNAM.Load();
            FNAM->fade = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void LIGHRecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        case 17: //unused1
            if(nSize != 1)
                return;
            DATA.value.color.unused1 = FieldValue[0];
            break;
        default:
            return;
        }
    return;
    }

void LIGHRecord::SetOtherField(const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 9: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            break;
        case 13: //radius
            DATA.value.radius = FieldValue;
            break;
        case 18: //flags
            DATA.value.flags = FieldValue;
            break;
        case 21: //value
            DATA.value.value = FieldValue;
            break;
        case 24: //sound
            SNAM.Load();
            SNAM->fid = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void LIGHRecord::SetField(const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 12: //duration
            DATA.value.duration = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void LIGHRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 14: //red
            DATA.value.color.red = FieldValue;
            break;
        case 15: //green
            DATA.value.color.green = FieldValue;
            break;
        case 16: //blue
            DATA.value.color.blue = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int LIGHRecord::DeleteField(const unsigned int Field)
    {
    LIGHDATA defaultDATA;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            break;
        case 7: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            break;
        case 8: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            break;
        case 9: //script
            SCRI.Unload();
            break;
        case 10: //full
            FULL.Unload();
            break;
        case 11: //iconPath
            ICON.Unload();
            break;
        case 12: //duration
            DATA.value.duration = defaultDATA.duration;
            break;
        case 13: //radius
            DATA.value.radius = defaultDATA.radius;
            break;
        case 14: //red
            DATA.value.color.red = defaultDATA.color.red;
            break;
        case 15: //green
            DATA.value.color.green = defaultDATA.color.green;
            break;
        case 16: //blue
            DATA.value.color.blue = defaultDATA.color.blue;
            break;
        case 17: //unused1
            DATA.value.color.unused1 = defaultDATA.color.unused1;
            break;
        case 18: //flags
            DATA.value.flags = defaultDATA.flags;
            break;
        case 19: //falloff
            DATA.value.falloff = defaultDATA.falloff;
            break;
        case 20: //fov
            DATA.value.fov = defaultDATA.fov;
            break;
        case 21: //value
            DATA.value.value = defaultDATA.value;
            break;
        case 22: //weight
            DATA.value.weight = defaultDATA.weight;
            break;
        case 23: //fade
            FNAM.Unload();
            break;
        case 24: //sound
            SNAM.Unload();
            break;
        default:
            return 0;
        }
    return 1;
    }
