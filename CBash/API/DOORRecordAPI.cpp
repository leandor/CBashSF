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
#include "..\Records\DOORRecord.h"

int DOORRecord::GetOtherFieldType(const unsigned int Field)
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
        case 11: //soundOpen
            return FID_FIELD;
        case 12: //soundClose
            return FID_FIELD;
        case 13: //soundLoop
            return FID_FIELD;
        case 14: //flags
            return UBYTE_FIELD;
        case 15: //destinations
            return FIDARRAY_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * DOORRecord::GetOtherField(const unsigned int Field)
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
        case 10: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 11: //soundOpen
            if(SNAM.IsLoaded())
                return &SNAM->fid;
            return NULL;
        case 12: //soundClose
            if(ANAM.IsLoaded())
                return &ANAM->fid;
            return NULL;
        case 13: //soundLoop
            if(BNAM.IsLoaded())
                return &BNAM->fid;
            return NULL;
        case 14: //flags
            return &FNAM.value.flags;
        default:
            return NULL;
        }
    }

unsigned int DOORRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        case 15: //destinations
            return (unsigned int)TNAM.size();
        default:
            return 0;
        }
    }

void DOORRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 15: //destinations
            for(unsigned int p = 0;p < TNAM.size();p++)
                FieldValues[p] = TNAM[p];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void DOORRecord::SetField(const unsigned int Field, char *FieldValue)
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
        default:
            return;
        }
    return;
    }

void DOORRecord::SetField(const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void DOORRecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
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

void DOORRecord::SetOtherField(const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 10: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            break;
        case 11: //soundOpen
            SNAM.Load();
            SNAM->fid = FieldValue;
            break;
        case 12: //soundClose
            ANAM.Load();
            ANAM->fid = FieldValue;
            break;
        case 13: //soundLoop
            BNAM.Load();
            BNAM->fid = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void DOORRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 14: //flags
            FNAM.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void DOORRecord::SetField(const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 15: //destinations
            TNAM.clear();
            if(nSize)
                {
                TNAM.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    TNAM[x] = new unsigned int(FieldValue[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

int DOORRecord::DeleteField(const unsigned int Field)
    {
    unsigned int nSize;
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
        case 10: //script
            SCRI.Unload();
            break;
        case 11: //soundOpen
            SNAM.Unload();
            break;
        case 12: //soundClose
            ANAM.Unload();
            break;
        case 13: //soundLoop
            BNAM.Unload();
            break;
        case 14: //flags
            FNAM.Unload();
            break;
        case 15: //destinations
            nSize = (unsigned int)TNAM.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete TNAM[x];
            TNAM.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }
