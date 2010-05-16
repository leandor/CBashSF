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
        case 14: //color.red
            return UBYTE_FIELD;
        case 15: //color.green
            return UBYTE_FIELD;
        case 16: //color.blue
            return UBYTE_FIELD;
        case 17: //color.unused1
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
            return MODL.MODL.value;
        case 7: //modb
            return &MODL.MODB.value.MODB;
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
        case 14: //color.red
            return &DATA.value.color.red;
        case 15: //color.green
            return &DATA.value.color.green;
        case 16: //color.blue
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
            return MODL.MODT.size;
        case 17: //color.unused1
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
            *FieldValues = MODL.MODT.value;
            return;
        case 17: //color.unused1
            *FieldValues = &DATA.value.color.unused1;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void LIGHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //modPath
            MODL.MODL.Copy(FieldValue);
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

void LIGHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 7: //modb
            MODL.MODB.value.MODB = FieldValue;
            MODL.MODB.isLoaded = true;
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

void LIGHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //modt_p
            MODL.MODT.Copy(FieldValue, nSize);
            break;
        case 17: //color.unused1
            if(nSize != 1)
                return;
            DATA.value.color.unused1 = FieldValue[0];
            break;
        default:
            return;
        }
    return;
    }

void LIGHRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 9: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
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
            FormIDHandler.AddMaster(SNAM->fid);
            break;
        default:
            return;
        }
    return;
    }

void LIGHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue)
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

void LIGHRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 14: //color.red
            DATA.value.color.red = FieldValue;
            break;
        case 15: //color.green
            DATA.value.color.green = FieldValue;
            break;
        case 16: //color.blue
            DATA.value.color.blue = FieldValue;
            break;
        default:
            return;
        }
    return;
    }
