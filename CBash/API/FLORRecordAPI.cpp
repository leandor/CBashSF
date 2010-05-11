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
#include "..\Records\FLORRecord.h"

int FLORRecord::GetOtherFieldType(const unsigned int Field)
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
        case 10: //script
            return FID_FIELD;
        case 11: //ingredient
            return FID_FIELD;
        case 12: //spring
            return UBYTE_FIELD;
        case 13: //summer
            return UBYTE_FIELD;
        case 14: //fall
            return UBYTE_FIELD;
        case 15: //winter
            return UBYTE_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * FLORRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //modPath
            return MODL.MODL.value;
        case 8: //modb
            return &MODL.MODB.value.MODB;
        case 10: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 11: //ingredient
            return &PFIG.value.fid;
        case 12: //spring
            return &PFPC.value.spring;
        case 13: //summer
            return &PFPC.value.summer;
        case 14: //fall
            return &PFPC.value.fall;
        case 15: //winter
            return &PFPC.value.winter;
        default:
            return NULL;
        }
    }

unsigned int FLORRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //modt_p
            return MODL.MODT.size;
        default:
            return 0;
        }
    }

void FLORRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //modt_p
            *FieldValues = MODL.MODT.value;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void FLORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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
            MODL.MODL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void FLORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //modb
            MODL.MODB.value.MODB = FieldValue;
            MODL.MODB.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void FLORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 9: //modt_p
            MODL.MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void FLORRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 10: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 11: //ingredient
            PFIG.value.fid = FieldValue;
            FormIDHandler.AddMaster(PFIG.value.fid);
            PFIG.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void FLORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 12: //spring
            PFPC.value.spring = FieldValue;
            break;
        case 13: //summer
            PFPC.value.summer = FieldValue;
            break;
        case 14: //fall
            PFPC.value.fall = FieldValue;
            break;
        case 15: //winter
            PFPC.value.winter = FieldValue;
            break;
        default:
            return;
        }
    return;
    }
