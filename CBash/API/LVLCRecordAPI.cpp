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
#include "..\Records\LVLCRecord.h"

int LVLCRecord::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<LVLLVLO> *curEntry = NULL;
    switch(subField)
        {
        case 10: //entries
            curEntry = new ReqRecordField<LVLLVLO>;
            Entries.push_back(curEntry);
            return (int)Entries.size() - 1;
        default:
            return -1;
        }
    }

int LVLCRecord::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<LVLLVLO> *curEntry = NULL;
    switch(subField)
        {
        case 10: //entries
            curEntry = Entries.back();
            delete curEntry;
            Entries.pop_back();
            return (int)Entries.size() - 1;
        default:
            return -1;
        }
    }

int LVLCRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //chanceNone
            return UBYTE_FIELD;
        case 7: //flags
            return UBYTE_FIELD;
        case 8: //script
            return FID_FIELD;
        case 9: //template
            return FID_FIELD;
        case 10: //entries
            return LIST_FIELD;
        case 11: //data_p
            return UNKNOWN_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LVLCRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //chanceNone
            return &LVLD.value.chanceNone;
        case 7: //flags
            return &LVLF.value.flags;
        case 8: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 9: //template
            if(TNAM.IsLoaded())
                return &TNAM->fid;
            return NULL;
        default:
            return NULL;
        }
    }

int LVLCRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 10: //entries
            switch(listField)
                {
                case 1: //level
                    return SHORT_FIELD;
                case 2: //unused1
                    return BYTES_FIELD;
                case 3: //listId
                    return FID_FIELD;
                case 4: //count
                    return SHORT_FIELD;
                case 5: //unused2
                    return BYTES_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int LVLCRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 10: //entries
            return (unsigned int)Entries.size();
        default:
            return 0;
        }
    }

unsigned int LVLCRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 10: //entries
            switch(listField)
                {
                case 2: //unused1
                    return 2;
                case 5: //unused2
                    return 2;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

void LVLCRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 10: //entries
            if(listIndex >= Entries.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 2: //unused1
                    *FieldValues = &Entries[listIndex]->value.unused1[0];
                    return;
                case 5: //unused2
                    *FieldValues = &Entries[listIndex]->value.unused2[0];
                    return;
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void * LVLCRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 10: //entries
            if(listIndex >= Entries.size())
                return NULL;
            switch(listField)
                {
                case 1: //level
                    return &Entries[listIndex]->value.level;
                case 3: //listId
                    return &Entries[listIndex]->value.listId;
                case 4: //count
                    return &Entries[listIndex]->value.count;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void LVLCRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void LVLCRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 6: //chanceNone
            LVLD.value.chanceNone = FieldValue;
            LVLD.isLoaded = true;
            break;
        case 7: //flags
            LVLF.value.flags = FieldValue;
            LVLF.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void LVLCRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 8: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 9: //template
            TNAM.Load();
            TNAM->fid = FieldValue;
            FormIDHandler.AddMaster(TNAM->fid);
            break;
        default:
            return;
        }
    return;
    }

void LVLCRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue)
    {
    switch(subField)
        {
        case 10: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 1: //level
                    Entries[listIndex]->value.level = FieldValue;
                    break;
                case 4: //count
                    Entries[listIndex]->value.count = FieldValue;
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

void LVLCRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 10: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 2: //unused1
                    if(nSize != 2)
                        return;
                    Entries[listIndex]->value.unused1[0] = FieldValue[0];
                    Entries[listIndex]->value.unused1[1] = FieldValue[1];
                    break;
                case 5: //unused2
                    if(nSize != 2)
                        return;
                    Entries[listIndex]->value.unused2[0] = FieldValue[0];
                    Entries[listIndex]->value.unused2[1] = FieldValue[1];
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

void LVLCRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 10: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 3: //listId
                    Entries[listIndex]->value.listId = FieldValue;
                    FormIDHandler.AddMaster(Entries[listIndex]->value.listId);
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
