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
            return MODL.MODL.value;
        case 8: //modb
            return &MODL.MODB.value.MODB;
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
            return MODL.MODT.size;
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
            *FieldValues = MODL.MODT.value;
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

void DOORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void DOORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
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

void DOORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
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

void DOORRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 10: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 11: //soundOpen
            SNAM.Load();
            SNAM->fid = FieldValue;
            FormIDHandler.AddMaster(SNAM->fid);
            break;
        case 12: //soundClose
            ANAM.Load();
            ANAM->fid = FieldValue;
            FormIDHandler.AddMaster(ANAM->fid);
            break;
        case 13: //soundLoop
            BNAM.Load();
            BNAM->fid = FieldValue;
            FormIDHandler.AddMaster(BNAM->fid);
            break;
        default:
            return;
        }
    return;
    }

void DOORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
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

void DOORRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
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
                    FormIDHandler.AddMaster(TNAM[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }
