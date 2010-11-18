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
#include "..\Records\LVLIRecord.h"

int LVLIRecord::CreateListElement(const unsigned int subField)
    {
    ReqSubRecord<LVLLVLO> *curEntry = NULL;
    switch(subField)
        {
        case 10: //entries
            curEntry = new ReqSubRecord<LVLLVLO>;
            Entries.push_back(curEntry);
            return (int)Entries.size() - 1;
        default:
            return -1;
        }
    }

int LVLIRecord::DeleteListElement(const unsigned int subField)
    {
    ReqSubRecord<LVLLVLO> *curEntry = NULL;
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

int LVLIRecord::GetOtherFieldType(const unsigned int Field)
    {
    //The jump in numbering from case 7 to case 10 is deliberate
    //It allows LVLC, LVLI, and LVSP to share a common id scheme
    switch(Field)
        {
        case 6: //chanceNone
            return UBYTE_FIELD;
        case 7: //flags
            return UBYTE_FIELD;
        case 10: //entries
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LVLIRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //chanceNone
            return &LVLD.value.chanceNone;
        case 7: //flags
            if(LVLF.IsLoaded())
                return &LVLF->flags;
            return NULL;
        default:
            return NULL;
        }
    }

int LVLIRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
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

unsigned int LVLIRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 10: //entries
            return (unsigned int)Entries.size();
        default:
            return 0;
        }
    }

unsigned int LVLIRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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

void LVLIRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
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

void * LVLIRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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

void LVLIRecord::SetField(const unsigned int Field, char *FieldValue)
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

void LVLIRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 6: //chanceNone
            LVLD.value.chanceNone = FieldValue;
            if((LVLD.value.chanceNone & fAltCalcFromAllLevels) != 0)
                {
                LVLD.value.chanceNone &= ~fAltCalcFromAllLevels;
                LVLF.Load();
                IsCalcFromAllLevels(true);
                }
            break;
        case 7: //flags
            LVLF.Load();
            LVLF->flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void LVLIRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue)
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

void LVLIRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
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

void LVLIRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
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

int LVLIRecord::DeleteField(const unsigned int Field)
    {
    unsigned int nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //chanceNone
            LVLD.Unload();
            break;
        case 7: //flags
            LVLF.Unload();
            break;
        case 10: //entries
            nSize = (unsigned int)Entries.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete Entries[x];
            Entries.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }

int LVLIRecord::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    LVLLVLO defaultLVLO;
    switch(subField)
        {
        case 10: //entries
            if(listIndex >= Entries.size())
                return 0;
            switch(listField)
                {
                case 1: //level
                    Entries[listIndex]->value.level = defaultLVLO.level;
                    break;
                case 2: //unused1
                    Entries[listIndex]->value.unused1[0] = defaultLVLO.unused1[0];
                    Entries[listIndex]->value.unused1[1] = defaultLVLO.unused1[1];
                    break;
                case 3: //listId
                    Entries[listIndex]->value.listId = defaultLVLO.listId;
                    break;
                case 4: //count
                    Entries[listIndex]->value.count = defaultLVLO.count;
                    break;
                case 5: //unused2
                    Entries[listIndex]->value.unused2[0] = defaultLVLO.unused2[0];
                    Entries[listIndex]->value.unused2[1] = defaultLVLO.unused2[1];
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
