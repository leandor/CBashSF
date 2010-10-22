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
#include "..\Records\ACRERecord.h"

int ACRERecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //base
            return FID_FIELD;
        case 7: //owner
            return FID_FIELD;
        case 8: //rank
            return INT_FIELD;
        case 9: //globalVariable
            return FID_FIELD;
        case 10: //lod1
            return FLOAT_FIELD;
        case 11: //lod2
            return FLOAT_FIELD;
        case 12: //lod3
            return FLOAT_FIELD;
        case 13: //parent
            return FID_FIELD;
        case 14: //parentFlags
            return UBYTE_FIELD;
        case 15: //unused1
            return BYTES_FIELD;
        case 16: //xrgd_p
            return BYTES_FIELD;
        case 17: //scale
            return FLOAT_FIELD;
        case 18: //posX
            return FLOAT_FIELD;
        case 19: //posY
            return FLOAT_FIELD;
        case 20: //posZ
            return FLOAT_FIELD;
        case 21: //rotX
            return FLOAT_FIELD;
        case 22: //rotY
            return FLOAT_FIELD;
        case 23: //rotZ
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * ACRERecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //base
            return &NAME.value.fid;
        case 7: //owner
            if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
                return &Ownership->XOWN.value.fid;
            return NULL;
        case 8: //rank
            if(Ownership.IsLoaded() && Ownership->XRNK.IsLoaded())
                return &Ownership->XRNK->rank;
            return NULL;
        case 9: //globalVariable
            if(Ownership.IsLoaded() && Ownership->XGLB.IsLoaded())
                return &Ownership->XGLB->fid;
            return NULL;
        case 10: //lod1
            if(XLOD.IsLoaded())
                return &XLOD->lod1;
            return NULL;
        case 11: //lod2
            if(XLOD.IsLoaded())
                return &XLOD->lod2;
            return NULL;
        case 12: //lod3
            if(XLOD.IsLoaded())
                return &XLOD->lod3;
            return NULL;
        case 13: //parent
            if(XESP.IsLoaded())
                return &XESP->parent;
            return NULL;
        case 14: //parentFlags
            if(XESP.IsLoaded())
                return &XESP->flags;
            return NULL;
        case 17: //scale
            if(XSCL.IsLoaded())
                return &XSCL->scale;
            return NULL;
        case 18: //posX
            return &DATA.value.posX;
        case 19: //posY
            return &DATA.value.posY;
        case 20: //posZ
            return &DATA.value.posZ;
        case 21: //rotX
            return &DATA.value.rotX;
        case 22: //rotY
            return &DATA.value.rotY;
        case 23: //rotZ
            return &DATA.value.rotZ;
        default:
            return NULL;
        }
    }
unsigned int ACRERecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 15: //unused1
            if(XESP.IsLoaded())
                return 3;
            return 0;
        case 16: //xrgd_p
            return XRGD.size;
        default:
            return 0;
        }
    }

void ACRERecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 15: //unused1
            if(XESP.IsLoaded())
                *FieldValues = &XESP->unused1[0];
            else
                *FieldValues = NULL;
            return;
        case 16: //xrgd_p
            *FieldValues = XRGD.value;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void ACRERecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void ACRERecord::SetOtherField(const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 6: //base
            NAME.value.fid = FieldValue;
            break;
        case 7: //owner
            Ownership.Load();
            Ownership->XOWN.value.fid = FieldValue;
            break;
        case 9: //globalVariable
            Ownership.Load();
            Ownership->XGLB.Load();
            Ownership->XGLB->fid = FieldValue;
            break;
        case 13: //parent
            XESP.Load();
            XESP->parent = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void ACRERecord::SetField(const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 8: //rank
            Ownership.Load();
            Ownership->XRNK.Load();
            Ownership->XRNK->rank = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void ACRERecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 14: //parentFlags
            XESP.Load();
            XESP->flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void ACRERecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 15: //unused1
            if(nSize != 3)
                return;
            XESP.Load();
            XESP->unused1[0] = FieldValue[0];
            XESP->unused1[1] = FieldValue[1];
            XESP->unused1[2] = FieldValue[2];
            break;
        case 16: //xrgd_p
            XRGD.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void ACRERecord::SetField(const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 10: //lod1
            XLOD.Load();
            XLOD->lod1 = FieldValue;
            break;
        case 11: //lod2
            XLOD.Load();
            XLOD->lod2 = FieldValue;
            break;
        case 12: //lod3
            XLOD.Load();
            XLOD->lod3 = FieldValue;
            break;
        case 17: //scale
            XSCL.Load();
            XSCL->scale = FieldValue;
            break;
        case 18: //posX
            DATA.value.posX = FieldValue;
            break;
        case 19: //posY
            DATA.value.posY = FieldValue;
            break;
        case 20: //posZ
            DATA.value.posZ = FieldValue;
            break;
        case 21: //rotX
            DATA.value.rotX = FieldValue;
            break;
        case 22: //rotY
            DATA.value.rotY = FieldValue;
            break;
        case 23: //rotZ
            DATA.value.rotZ = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int ACRERecord::DeleteField(const unsigned int Field)
    {
    GENXLOD defaultXLOD;
    GENXESP defaultXESP;
    GENPOSDATA defaultDATA;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //base
            NAME.Unload();
            break;
        case 7: //owner
            if(Ownership.IsLoaded())
                Ownership->XOWN.Unload();
            break;
        case 8: //rank
            if(Ownership.IsLoaded())
                Ownership->XRNK.Unload();
            break;
        case 9: //globalVariable
            if(Ownership.IsLoaded())
                Ownership->XGLB.Unload();
            break;
        case 10: //lod1
            if(XLOD.IsLoaded())
                XLOD->lod1 = defaultXLOD.lod1;
            break;
        case 11: //lod2
            if(XLOD.IsLoaded())
                XLOD->lod2 = defaultXLOD.lod2;
            break;
        case 12: //lod3
            if(XLOD.IsLoaded())
                XLOD->lod3 = defaultXLOD.lod3;
            break;
        case 13: //parent
            if(XESP.IsLoaded())
                XESP->parent = defaultXESP.parent;
            break;
        case 14: //parentFlags
            if(XESP.IsLoaded())
                XESP->flags = defaultXESP.flags;
            break;
        case 15: //unused1
            if(XESP.IsLoaded())
                {
                XESP->unused1[0] = defaultXESP.unused1[0];
                XESP->unused1[1] = defaultXESP.unused1[1];
                XESP->unused1[2] = defaultXESP.unused1[2];
                }
            break;
        case 16: //xrgd_p
            XRGD.Unload();
            break;
        case 17: //scale
            XSCL.Unload();
            break;
        case 18: //posX
            DATA.value.posX = defaultDATA.posX;
            break;
        case 19: //posY
            DATA.value.posY = defaultDATA.posY;
            break;
        case 20: //posZ
            DATA.value.posZ = defaultDATA.posZ;
            break;
        case 21: //rotX
            DATA.value.rotX = defaultDATA.rotX;
            break;
        case 22: //rotY
            DATA.value.rotY = defaultDATA.rotY;
            break;
        case 23: //rotZ
            DATA.value.rotZ = defaultDATA.rotZ;
            break;
        default:
            return 0;
        }
    return 1;
    }
