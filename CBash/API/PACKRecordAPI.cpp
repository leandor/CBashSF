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
#include "..\Records\PACKRecord.h"

int PACKRecord::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    switch(subField)
        {
        case 20: //conditions
            curCTDA = new ReqRecordField<GENCTDA>;
            CTDA.push_back(curCTDA);
            return (int)CTDA.size() - 1;
        default:
            return -1;
        }
    }

int PACKRecord::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    switch(subField)
        {
        case 20: //conditions
            curCTDA = CTDA.back();
            delete curCTDA;
            CTDA.pop_back();
            return (int)CTDA.size() - 1;
        default:
            return -1;
        }
    }

int PACKRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //flags
            return UINT_FIELD;
        case 7: //aiType
            return UBYTE_FIELD;
        case 8: //unused1
            return BYTES_FIELD;
        case 9: //locType
            return INT_FIELD;
        case 10: //locId
            return UINT_FIELD;
        case 11: //locRadius
            return INT_FIELD;
        case 12: //month
            return BYTE_FIELD;
        case 13: //day
            return BYTE_FIELD;
        case 14: //date
            return UBYTE_FIELD;
        case 15: //time
            return BYTE_FIELD;
        case 16: //duration
            return INT_FIELD;
        case 17: //targetType
            return INT_FIELD;
        case 18: //targetId
            return UINT_FIELD;
        case 19: //targetCount
            return INT_FIELD;
        case 20: //conditions
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * PACKRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //flags
            return &PKDT.value.flags;
        case 7: //aiType
            return &PKDT.value.aiType;
        case 9: //locType
            if(PLDT.IsLoaded())
                return &PLDT->locType;
            return NULL;
        case 10: //locId
            if(PLDT.IsLoaded())
                return &PLDT->locId;
            return NULL;
        case 11: //locRadius
            if(PLDT.IsLoaded())
                return &PLDT->locRadius;
            return NULL;
        case 12: //month
            return &PSDT.value.month;
        case 13: //day
            return &PSDT.value.day;
        case 14: //date
            return &PSDT.value.date;
        case 15: //time
            return &PSDT.value.time;
        case 16: //duration
            return &PSDT.value.duration;
        case 17: //targetType
            if(PTDT.IsLoaded())
                return &PTDT->targetType;
            return NULL;
        case 18: //targetId
            if(PTDT.IsLoaded())
                return &PTDT->targetId;
            return NULL;
        case 19: //targetCount
            if(PTDT.IsLoaded())
                return &PTDT->targetCount;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned int PACKRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //unused1
            return 3;
        default:
            return 0;
        }
    }

void PACKRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //unused1
            *FieldValues = &PKDT.value.unused1[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int PACKRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 20: //conditions
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

unsigned int PACKRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 20: //conditions
            return (unsigned int)CTDA.size();
        default:
            return 0;
        }
    }

unsigned int PACKRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 20: //conditions
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

void PACKRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 20: //conditions
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

void * PACKRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 20: //conditions
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

void PACKRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void PACKRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 6: //flags
            PKDT.value.flags = FieldValue;
            break;
        case 10: //locId
            PLDT.Load();
            PLDT->locId = FieldValue;
            if(PLDT->locType != 5)
                FormIDHandler.AddMaster(PLDT->locId);
            break;
        case 18: //targetId
            PTDT.Load();
            PTDT->targetId = FieldValue;
            if(PTDT->targetType != 2)
                FormIDHandler.AddMaster(PTDT->targetId);
            break;
        default:
            return;
        }
    return;
    }

void PACKRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 7: //aiType
            PKDT.value.aiType = FieldValue;
            break;
        case 14: //date
            PSDT.value.date = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void PACKRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //unused1
            if(nSize != 3)
                return;
            PKDT.value.unused1[0] = FieldValue[0];
            PKDT.value.unused1[1] = FieldValue[1];
            PKDT.value.unused1[2] = FieldValue[2];
            break;
        default:
            return;
        }
    return;
    }

void PACKRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 9: //locType
            PLDT.Load();
            PLDT->locType = FieldValue;
            break;
        case 11: //locRadius
            PLDT.Load();
            PLDT->locRadius = FieldValue;
            break;
        case 16: //duration
            PSDT.value.duration = FieldValue;
            break;
        case 17: //targetType
            PTDT.Load();
            PTDT->targetType = FieldValue;
            break;
        case 19: //targetCount
            PTDT.Load();
            PTDT->targetCount = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void PACKRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue)
    {
    switch(Field)
        {
        case 12: //month
            PSDT.value.month = FieldValue;
            break;
        case 13: //day
            PSDT.value.day = FieldValue;
            break;
        case 15: //time
            PSDT.value.time = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void PACKRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 20: //conditions
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

void PACKRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 20: //conditions
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

void PACKRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue)
    {
    switch(subField)
        {
        case 20: //conditions
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

void PACKRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    std::pair<unsigned int, unsigned int> newCTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
    switch(subField)
        {
        case 20: //conditions
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

int PACKRecord::DeleteField(const unsigned int Field)
    {
    PACKPKDT defaultPKDT;
    PACKPLDT defaultPLDT;
    PACKPSDT defaultPSDT;
    PACKPTDT defaultPTDT;
    unsigned int nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //flags
            PKDT.value.flags = defaultPKDT.flags;
            break;
        case 7: //aiType
            PKDT.value.aiType = defaultPKDT.aiType;
            break;
        case 8: //unused1
            PKDT.value.unused1[0] = defaultPKDT.unused1[0];
            PKDT.value.unused1[1] = defaultPKDT.unused1[1];
            PKDT.value.unused1[2] = defaultPKDT.unused1[2];
            break;
        case 9: //locType
            if(PLDT.IsLoaded())
                PLDT->locType = defaultPLDT.locType;
            break;
        case 10: //locId
            if(PLDT.IsLoaded())
                PLDT->locId = defaultPLDT.locId;
            break;
        case 11: //locRadius
            if(PLDT.IsLoaded())
                PLDT->locRadius = defaultPLDT.locRadius;
            break;
        case 12: //month
            PSDT.value.month = defaultPSDT.month;
            break;
        case 13: //day
            PSDT.value.day = defaultPSDT.day;
            break;
        case 14: //date
            PSDT.value.date = defaultPSDT.date;
            break;
        case 15: //time
            PSDT.value.time = defaultPSDT.time;
            break;
        case 16: //duration
            PSDT.value.duration = defaultPSDT.duration;
            break;
        case 17: //targetType
            if(PTDT.IsLoaded())
                PTDT->targetType = defaultPTDT.targetType;
            break;
        case 18: //targetId
            if(PTDT.IsLoaded())
                PTDT->targetId = defaultPTDT.targetId;
            break;
        case 19: //targetCount
            if(PTDT.IsLoaded())
                PTDT->targetCount = defaultPTDT.targetCount;
            break;
        case 20: //conditions
            nSize = (unsigned int)CTDA.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete CTDA[x];
            CTDA.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }

int PACKRecord::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    GENCTDA defaultCTDA;
    switch(subField)
        {
        case 20: //conditions
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
