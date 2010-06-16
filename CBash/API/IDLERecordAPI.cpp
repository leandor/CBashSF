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
#include "..\Records\IDLERecord.h"

int IDLERecord::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    switch(subField)
        {
        case 9: //conditions
            curCTDA = new ReqRecordField<GENCTDA>;
            CTDA.push_back(curCTDA);
            return (int)CTDA.size() - 1;
        default:
            return -1;
        }
    }

int IDLERecord::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    switch(subField)
        {
        case 9: //conditions
            curCTDA = CTDA.back();
            delete curCTDA;
            CTDA.pop_back();
            return (int)CTDA.size() - 1;
        default:
            return -1;
        }
    }

int IDLERecord::GetOtherFieldType(const unsigned int Field)
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

void * IDLERecord::GetOtherField(const unsigned int Field)
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

int IDLERecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
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
                    return UINT_FIELD;
                case 6: //param2
                    return UINT_FIELD;
                case 7: //unused2
                    return BYTES_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int IDLERecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //conditions
            return (unsigned int)CTDA.size();
        default:
            return 0;
        }
    }

unsigned int IDLERecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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

unsigned int IDLERecord::GetFieldArraySize(const unsigned int Field)
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

void IDLERecord::GetFieldArray(const unsigned int Field, void **FieldValues)
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

void IDLERecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
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

void * IDLERecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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

void IDLERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void IDLERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
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

void IDLERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
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

void IDLERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
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

void IDLERecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 11: //parent
            DATA.value.parent = FieldValue;
            FormIDHandler.AddMaster(DATA.value.parent);
            break;
        case 12: //prevId
            DATA.value.prevId = FieldValue;
            FormIDHandler.AddMaster(DATA.value.prevId);
            break;
        default:
            return;
        }
    return;
    }

void IDLERecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
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

void IDLERecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
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

void IDLERecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue)
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

void IDLERecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    std::pair<unsigned int, unsigned int> newCTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
    switch(subField)
        {
        case 9: //conditions
            if(listIndex >= CTDA.size())
                return;
            switch(listField)
                {
                case 4: //ifunc
                    curCTDAFunction = Function_Arguments.find(FieldValue);
                    if(curCTDAFunction != Function_Arguments.end())
                        newCTDAFunction = curCTDAFunction->second;
                    else
                        {
                        newCTDAFunction.first = eNULL;
                        newCTDAFunction.second = eNULL;
                        }

                    CTDA[listIndex]->value.ifunc = FieldValue;

                    if(newCTDAFunction.first == eFID)
                        FormIDHandler.AddMaster(CTDA[listIndex]->value.param1);

                    if(newCTDAFunction.second == eFID)
                        FormIDHandler.AddMaster(CTDA[listIndex]->value.param2);
                    break;
                case 5: //param1
                    CTDA[listIndex]->value.param1 = FieldValue;

                    curCTDAFunction = Function_Arguments.find(CTDA[listIndex]->value.ifunc);
                    if(curCTDAFunction != Function_Arguments.end())
                        {
                        newCTDAFunction = curCTDAFunction->second;
                        if(newCTDAFunction.first == eFID)
                            FormIDHandler.AddMaster(CTDA[listIndex]->value.param1);
                        }
                    break;
                case 6: //param2
                    CTDA[listIndex]->value.param2 = FieldValue;

                    curCTDAFunction = Function_Arguments.find(CTDA[listIndex]->value.ifunc);
                    if(curCTDAFunction != Function_Arguments.end())
                        {
                        newCTDAFunction = curCTDAFunction->second;
                        if(newCTDAFunction.second == eFID)
                            FormIDHandler.AddMaster(CTDA[listIndex]->value.param2);
                        }
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
