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
#include "..\..\Common.h"
#include "..\IDLERecord.h"

signed long IDLERecord::CreateListElement(const unsigned long subField)
    {
    ReqSubRecord<GENCTDA> *curCTDA = NULL;
    switch(subField)
        {
        case 9: //conditions
            curCTDA = new ReqSubRecord<GENCTDA>;
            CTDA.push_back(curCTDA);
            return (signed long)CTDA.size() - 1;
        default:
            return -1;
        }
    }

signed long IDLERecord::DeleteListElement(const unsigned long subField)
    {
    ReqSubRecord<GENCTDA> *curCTDA = NULL;
    switch(subField)
        {
        case 9: //conditions
            curCTDA = CTDA.back();
            delete curCTDA;
            CTDA.pop_back();
            return (signed long)CTDA.size() - 1;
        default:
            return -1;
        }
    }

signed long IDLERecord::GetOtherFieldType(const unsigned long Field)
    {
    switch(Field)
        {
        case 6: //modPath
            return STRING_FIELD;
        case 7: //modb
            return FLOAT_FIELD;
        case 8: //modt_p
            return BYTES_FIELD;
        case 9: //conditions
            return LIST_FIELD;
        case 10: //group
            return UBYTE_FIELD;
        case 11: //parent
            return UINT_FIELD;
        case 12: //prevId
            return UINT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * IDLERecord::GetOtherField(const unsigned long Field)
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
        case 10: //group
            return &ANAM.value.group;
        case 11: //parent
            return &DATA.value.parent;
        case 12: //prevId
            return &DATA.value.prevId;
        default:
            return NULL;
        }
    }

signed long IDLERecord::GetListFieldType(const unsigned long subField, const unsigned long listField)
    {
    switch(subField)
        {
        case 9: //conditions
            switch(listField)
                {
                case 1: //operType
                    return UBYTE_FIELD;
                case 2: //unused1
                    return BYTES_FIELD;
                case 3: //compValue
                    return FLOAT_FIELD;
                case 4: //ifunc
                    return UINT_FIELD;
                case 5: //param1
                    return FID_OR_UINT_FIELD;
                case 6: //param2
                    return FID_OR_UINT_FIELD;
                case 7: //unused2
                    return BYTES_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned long IDLERecord::GetListSize(const unsigned long Field)
    {
    switch(Field)
        {
        case 9: //conditions
            return (unsigned long)CTDA.size();
        default:
            return 0;
        }
    }

unsigned long IDLERecord::GetListArraySize(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    switch(subField)
        {
        case 9: //conditions
            switch(listField)
                {
                case 2: //unused1
                    return 3;
                case 7: //unused2
                    return 4;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned long IDLERecord::GetFieldArraySize(const unsigned long Field)
    {
    switch(Field)
        {
        case 8: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        default:
            return 0;
        }
    }

void IDLERecord::GetFieldArray(const unsigned long Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //modt_p
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

void IDLERecord::GetListArray(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues)
    {
    switch(subField)
        {
        case 9: //conditions
            if(listIndex >= CTDA.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 2: //unused1
                    *FieldValues = &CTDA[listIndex]->value.unused1[0];
                    return;
                case 7: //unused2
                    *FieldValues = &CTDA[listIndex]->value.unused2[0];
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

void * IDLERecord::GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    switch(subField)
        {
        case 9: //conditions
            if(listIndex >= CTDA.size())
                return NULL;
            switch(listField)
                {
                case 1: //operType
                    return &CTDA[listIndex]->value.operType;
                case 3: //compValue
                    return &CTDA[listIndex]->value.compValue;
                case 4: //ifunc
                    return &CTDA[listIndex]->value.ifunc;
                case 5: //param1
                    return &CTDA[listIndex]->value.param1;
                case 6: //param2
                    return &CTDA[listIndex]->value.param2;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void IDLERecord::SetField(const unsigned long Field, char *FieldValue)
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
        default:
            return;
        }
    return;
    }

void IDLERecord::SetField(const unsigned long Field, float FieldValue)
    {
    switch(Field)
        {
        case 7: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void IDLERecord::SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize)
    {
    switch(Field)
        {
        case 8: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void IDLERecord::SetField(const unsigned long Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 10: //group
            ANAM.value.group = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void IDLERecord::SetOtherField(const unsigned long Field, unsigned long FieldValue)
    {
    switch(Field)
        {
        case 11: //parent
            DATA.value.parent = FieldValue;
            break;
        case 12: //prevId
            DATA.value.prevId = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void IDLERecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 9: //conditions
            if(listIndex >= CTDA.size())
                return;
            switch(listField)
                {
                case 1: //operType
                    CTDA[listIndex]->value.operType = FieldValue;
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

void IDLERecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize)
    {
    switch(subField)
        {
        case 9: //conditions
            if(listIndex >= CTDA.size())
                return;
            switch(listField)
                {
                case 2: //unused1
                    if(nSize != 3)
                        return;
                    CTDA[listIndex]->value.unused1[0] = FieldValue[0];
                    CTDA[listIndex]->value.unused1[1] = FieldValue[1];
                    CTDA[listIndex]->value.unused1[2] = FieldValue[2];
                    break;
                case 7: //unused2
                    if(nSize != 4)
                        return;
                    CTDA[listIndex]->value.unused2[0] = FieldValue[0];
                    CTDA[listIndex]->value.unused2[1] = FieldValue[1];
                    CTDA[listIndex]->value.unused2[2] = FieldValue[2];
                    CTDA[listIndex]->value.unused2[3] = FieldValue[3];
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

void IDLERecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, float FieldValue)
    {
    switch(subField)
        {
        case 9: //conditions
            if(listIndex >= CTDA.size())
                return;
            switch(listField)
                {
                case 3: //compValue
                    CTDA[listIndex]->value.compValue = FieldValue;
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

void IDLERecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue)
    {
    switch(subField)
        {
        case 9: //conditions
            if(listIndex >= CTDA.size())
                return;
            switch(listField)
                {
                case 4: //ifunc
                    CTDA[listIndex]->value.ifunc = FieldValue;
                    break;
                case 5: //param1
                    CTDA[listIndex]->value.param1 = FieldValue;
                    break;
                case 6: //param2
                    CTDA[listIndex]->value.param2 = FieldValue;
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

signed long IDLERecord::DeleteField(const unsigned long Field)
    {
    IDLEDATA defaultDATA;
    unsigned long nSize;
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
        case 9: //conditions
            nSize = (unsigned long)CTDA.size();
            for(unsigned long x = 0; x < nSize; x++)
                delete CTDA[x];
            CTDA.clear();
            break;
        case 10: //group
            ANAM.Unload();
            break;
        case 11: //parent
            DATA.value.parent = defaultDATA.parent;
            break;
        case 12: //prevId
            DATA.value.prevId = defaultDATA.prevId;
            break;
        default:
            return 0;
        }
    return 1;
    }

signed long IDLERecord::DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    GENCTDA defaultCTDA;
    switch(subField)
        {
        case 9: //conditions
            if(listIndex >= CTDA.size())
                return 0;
            switch(listField)
                {
                case 1: //operType
                    CTDA[listIndex]->value.operType = defaultCTDA.operType;
                    break;
                case 2: //unused1
                    CTDA[listIndex]->value.unused1[0] = defaultCTDA.unused1[0];
                    CTDA[listIndex]->value.unused1[1] = defaultCTDA.unused1[1];
                    CTDA[listIndex]->value.unused1[2] = defaultCTDA.unused1[2];
                    break;
                case 3: //compValue
                    CTDA[listIndex]->value.compValue = defaultCTDA.compValue;
                    break;
                case 4: //ifunc
                    CTDA[listIndex]->value.ifunc = defaultCTDA.ifunc;
                    break;
                case 5: //param1
                    CTDA[listIndex]->value.param1 = defaultCTDA.param1;
                    break;
                case 6: //param2
                    CTDA[listIndex]->value.param2 = defaultCTDA.param2;
                    break;
                case 7: //unused2
                    CTDA[listIndex]->value.unused2[0] = defaultCTDA.unused2[0];
                    CTDA[listIndex]->value.unused2[1] = defaultCTDA.unused2[1];
                    CTDA[listIndex]->value.unused2[2] = defaultCTDA.unused2[2];
                    CTDA[listIndex]->value.unused2[3] = defaultCTDA.unused2[3];
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
