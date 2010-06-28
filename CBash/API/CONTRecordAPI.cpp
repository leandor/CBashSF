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
#include "..\Records\CONTRecord.h"

int CONTRecord::CreateListElement(const unsigned int subField)
    {
    ReqSubRecord<GENCNTO> *curCNTO = NULL;
    switch(subField)
        {
        case 11: //items
            curCNTO = new ReqSubRecord<GENCNTO>;
            CNTO.push_back(curCNTO);
            return (int)CNTO.size() - 1;
        default:
            return -1;
        }
    }

int CONTRecord::DeleteListElement(const unsigned int subField)
    {
    ReqSubRecord<GENCNTO> *curCNTO = NULL;
    switch(subField)
        {
        case 11: //items
            curCNTO = CNTO.back();
            delete curCNTO;
            CNTO.pop_back();
            return (int)CNTO.size() - 1;
        default:
            return -1;
        }
    }

int CONTRecord::GetOtherFieldType(const unsigned int Field)
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
        case 11: //items
            return LIST_FIELD;
        case 12: //flags
            return UBYTE_FIELD;
        case 13: //weight
            return FLOAT_FIELD;
        case 14: //soundOpen
            return FID_FIELD;
        case 15: //soundClose
            return FID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CONTRecord::GetOtherField(const unsigned int Field)
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
        case 12: //flags
            return &DATA.value.flags;
        case 13: //weight
            return &DATA.value.weight;
        case 14: //soundOpen
            if(SNAM.IsLoaded())
                return &SNAM->fid;
            return NULL;
        case 15: //soundClose
            if(QNAM.IsLoaded())
                return &QNAM->fid;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned int CONTRecord::GetFieldArraySize(const unsigned int Field)
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

void CONTRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
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

int CONTRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 11: //items
            switch(listField)
                {
                case 1: //item
                    return FID_FIELD;
                case 2: //count
                    return INT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int CONTRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 11: //items
            return (unsigned int)CNTO.size();
        default:
            return 0;
        }
    }

void * CONTRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 11: //items
            if(listIndex >= CNTO.size())
                return NULL;
            switch(listField)
                {
                case 1: //item
                    return &CNTO[listIndex]->value.item;
                case 2: //count
                    return &CNTO[listIndex]->value.count;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void CONTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void CONTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 13: //weight
            DATA.value.weight = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CONTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
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

void CONTRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 10: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 14: //soundOpen
            SNAM.Load();
            SNAM->fid = FieldValue;
            FormIDHandler.AddMaster(SNAM->fid);
            break;
        case 15: //soundClose
            QNAM.Load();
            QNAM->fid = FieldValue;
            FormIDHandler.AddMaster(QNAM->fid);
            break;
        default:
            return;
        }
    return;
    }

void CONTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 11: //items
            if(listIndex >= CNTO.size())
                return;
            switch(listField)
                {
                case 1: //item
                    CNTO[listIndex]->value.item = FieldValue;
                    FormIDHandler.AddMaster(CNTO[listIndex]->value.item);
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void CONTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    switch(subField)
        {
        case 11: //items
            if(listIndex >= CNTO.size())
                return;
            switch(listField)
                {
                case 2: //count
                    CNTO[listIndex]->value.count = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void CONTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 12: //flags
            DATA.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }


int CONTRecord::DeleteField(const unsigned int Field)
    {
    CONTDATA defaultDATA;
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
        case 11: //items
            nSize = (unsigned int)CNTO.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete CNTO[x];
            CNTO.clear();
            break;
        case 12: //flags
            DATA.value.flags = defaultDATA.flags;
            break;
        case 13: //weight
            DATA.value.weight = defaultDATA.weight;
            break;
        case 14: //soundOpen
            SNAM.Unload();
            break;
        case 15: //soundClose
            QNAM.Unload();
            break;
        default:
            return 0;
        }
    return 1;
    }

int CONTRecord::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    GENCNTO defaultCNTO;
    switch(subField)
        {
        case 11: //items
            if(listIndex >= CNTO.size())
                return 0;
            switch(listField)
                {
                case 1: //item
                    CNTO[listIndex]->value.item = defaultCNTO.item;
                    break;
                case 2: //count
                    CNTO[listIndex]->value.count = defaultCNTO.count;
                    break;
                default:
                    return 0;
                }
            break;
        default:
            return 0;
        }
    return 1;
    }