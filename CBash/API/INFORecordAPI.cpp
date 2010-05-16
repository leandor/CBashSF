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
#include "..\Records\INFORecord.h"

int INFORecord::CreateListElement(const unsigned int subField)
    {
    INFOResponse *curResponse = NULL;
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    ReqRecordField<GENSCR_> *curSCR_ = NULL;
    switch(subField)
        {
        case 13: //responses
            curResponse = new INFOResponse;
            Responses.push_back(curResponse);
            return (int)Responses.size() - 1;
        case 14: //conditions
            curCTDA = new ReqRecordField<GENCTDA>;
            CTDA.push_back(curCTDA);
            return (int)CTDA.size() - 1;
        case 24: //references
            curSCR_ = new ReqRecordField<GENSCR_>;
            SCR_.push_back(curSCR_);
            return (int)SCR_.size() - 1;
        default:
            return -1;
        }
    }

int INFORecord::DeleteListElement(const unsigned int subField)
    {
    INFOResponse *curResponse = NULL;
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    ReqRecordField<GENSCR_> *curSCR_ = NULL;
    switch(subField)
        {
        case 13: //responses
            curResponse = Responses.back();
            delete curResponse;
            Responses.pop_back();
            return (int)Responses.size() - 1;
        case 14: //conditions
            curCTDA = CTDA.back();
            delete curCTDA;
            CTDA.pop_back();
            return (int)CTDA.size() - 1;
        case 24: //references
            curSCR_ = SCR_.back();
            delete curSCR_;
            SCR_.pop_back();
            return (int)SCR_.size() - 1;
        default:
            return -1;
        }
    }

int INFORecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //dialType
            return UBYTE_FIELD;
        case 7: //flags
            return UBYTE_FIELD;
        case 8: //unused1
            return BYTES_FIELD;
        case 9: //quest
            return FID_FIELD;
        case 10: //topic
            return FID_FIELD;
        case 11: //prevInfo
            return FID_FIELD;
        case 12: //addTopics
            return FIDARRAY_FIELD;
        case 13: //responses
            return LIST_FIELD;
        case 14: //conditions
            return LIST_FIELD;
        case 15: //choices
            return FIDARRAY_FIELD;
        case 16: //linksFrom
            return FIDARRAY_FIELD;
        case 17: //unused2
            return BYTES_FIELD;
        case 18: //numRefs
            return UINT_FIELD;
        case 19: //compiledSize
            return UINT_FIELD;
        case 20: //lastIndex
            return UINT_FIELD;
        case 21: //scriptType
            return UINT_FIELD;
        case 22: //compiled_p
            return BYTES_FIELD;
        case 23: //scriptText
            return STRING_FIELD;
        case 24: //references
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * INFORecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //dialType
            return &DATA.value.dialType;
        case 7: //flags
            return &DATA.value.flags;
        case 9: //quest
            return &QSTI.value.fid;
        case 10: //topic
            if(TPIC.IsLoaded())
                return &TPIC->fid;
            return NULL;
        case 11: //prevInfo
            if(PNAM.IsLoaded())
                return &PNAM->fid;
            return NULL;
        case 18: //numRefs
            return &SCHR.value.numRefs;
        case 19: //compiledSize
            return &SCHR.value.compiledSize;
        case 20: //lastIndex
            return &SCHR.value.lastIndex;
        case 21: //scriptType
            return &SCHR.value.scriptType;
        case 23: //scriptText
            return SCTX.value;
        default:
            return NULL;
        }
    }

int INFORecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 13: //responses
            switch(listField)
                {
                case 1: //emotionType
                    return UINT_FIELD;
                case 2: //emotionValue
                    return INT_FIELD;
                case 3: //unused1
                    return BYTES_FIELD;
                case 4: //responseNum
                    return UBYTE_FIELD;
                case 5: //unused2
                    return BYTES_FIELD;
                case 6: //responseText
                    return STRING_FIELD;
                case 7: //actorNotes
                    return STRING_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //conditions
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
        case 24: //references
            switch(listField)
                {
                case 1: //reference
                    return UINT_FIELD;
                case 2: //isSCRO
                    return UINT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int INFORecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 13: //responses
            return (unsigned int)Responses.size();
        case 14: //conditions
            return (unsigned int)CTDA.size();
        case 24: //references
            return (unsigned int)SCR_.size();
        default:
            return 0;
        }
    }

unsigned int INFORecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 13: //responses
            switch(listField)
                {
                case 3: //unused1
                    return 4;
                case 5: //unused2
                    return 3;
                default:
                    return 0;
                }
        case 14: //conditions
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

unsigned int INFORecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //unused1
            return 1;
        case 12: //addTopics
            return (unsigned int)NAME.size();
        case 15: //choices
            return (unsigned int)TCLT.size();
        case 16: //linksFrom
            return (unsigned int)TCLF.size();
        case 17: //unused2
            return 4;
        case 22: //compiled_p
            return SCDA.size;
        default:
            return 0;
        }
    }

void INFORecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //unused1
            *FieldValues = &DATA.value.unused1;
            return;
        case 12: //addTopics
            for(unsigned int p = 0;p < NAME.size();p++)
                FieldValues[p] = NAME[p];
            return;
        case 15: //choices
            for(unsigned int p = 0;p < TCLT.size();p++)
                FieldValues[p] = TCLT[p];
            return;
        case 16: //linksFrom
            for(unsigned int p = 0;p < TCLF.size();p++)
                FieldValues[p] = TCLF[p];
            return;
        case 17: //unused2
            *FieldValues = &SCHR.value.unused1[0];
            return;
        case 22: //compiled_p
            *FieldValues = SCDA.value;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void INFORecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 13: //responses
            if(listIndex >= Responses.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 3: //unused1
                    *FieldValues = &Responses[listIndex]->TRDT.value.unused1[0];
                    return;
                case 5: //unused2
                    *FieldValues = &Responses[listIndex]->TRDT.value.unused2[0];
                    return;
                default:
                    *FieldValues = NULL;
                    return;
                }
        case 14: //conditions
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

void * INFORecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 13: //responses
            if(listIndex >= Responses.size())
                return NULL;
            switch(listField)
                {
                case 1: //emotionType
                    return &Responses[listIndex]->TRDT.value.emotionType;
                case 2: //emotionValue
                    return &Responses[listIndex]->TRDT.value.emotionValue;
                case 4: //responseNum
                    return &Responses[listIndex]->TRDT.value.responseNum;
                case 6: //responseText
                    return Responses[listIndex]->NAM1.value;
                case 7: //actorNotes
                    return Responses[listIndex]->NAM2.value;
                default:
                    return NULL;
                }
        case 14: //conditions
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
        case 24: //references
            if(listIndex >= SCR_.size())
                return NULL;
            switch(listField)
                {
                case 1: //reference
                    return &SCR_[listIndex]->value.reference;
                case 2: //isSCRO
                    return &SCR_[listIndex]->value.isSCRO;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void INFORecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 23: //scriptText
            SCTX.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void INFORecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 6: //dialType
            DATA.value.dialType = FieldValue;
            break;
        case 7: //flags
            DATA.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void INFORecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //unused1
            if(nSize != 1)
                return;
            DATA.value.unused1 = FieldValue[0];
            break;
        case 17: //unused2
            if(nSize != 4)
                return;
            SCHR.value.unused1[0] = FieldValue[0];
            SCHR.value.unused1[1] = FieldValue[1];
            SCHR.value.unused1[2] = FieldValue[2];
            SCHR.value.unused1[3] = FieldValue[3];
            break;
        case 22: //compiled_p
            SCDA.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void INFORecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 9: //quest
            QSTI.value.fid = FieldValue;
            FormIDHandler.AddMaster(QSTI.value.fid);
            break;
        case 10: //topic
            TPIC.Load();
            TPIC->fid = FieldValue;
            FormIDHandler.AddMaster(TPIC->fid);
            break;
        case 11: //prevInfo
            PNAM.Load();
            PNAM->fid = FieldValue;
            FormIDHandler.AddMaster(PNAM->fid);
            break;
        case 18: //numRefs
            SCHR.value.numRefs = FieldValue;
            break;
        case 19: //compiledSize
            SCHR.value.compiledSize = FieldValue;
            break;
        case 20: //lastIndex
            SCHR.value.lastIndex = FieldValue;
            break;
        case 21: //scriptType
            SCHR.value.scriptType = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void INFORecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 12: //addTopics
            NAME.clear();
            if(nSize)
                {
                NAME.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    NAME[x] = new unsigned int(FieldValue[x]);
                    FormIDHandler.AddMaster(NAME[x]);
                    }
                }
            break;
        case 15: //choices
            TCLT.clear();
            if(nSize)
                {
                TCLT.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    TCLT[x] = new unsigned int(FieldValue[x]);
                    FormIDHandler.AddMaster(TCLT[x]);
                    }
                }
            break;
        case 16: //linksFrom
            TCLF.clear();
            if(nSize)
                {
                TCLF.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    TCLF[x] = new unsigned int(FieldValue[x]);
                    FormIDHandler.AddMaster(TCLF[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

void INFORecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    std::pair<unsigned int, unsigned int> newCTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
    switch(subField)
        {
        case 13: //responses
            if(listIndex >= Responses.size())
                return;
            switch(listField)
                {
                case 1: //emotionType
                    Responses[listIndex]->TRDT.value.emotionType = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 14: //conditions
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
        case 24: //references
            if(listIndex >= SCR_.size())
                return;
            switch(listField)
                {
                case 1: //reference
                    SCR_[listIndex]->value.reference = FieldValue;
                    if(SCR_[listIndex]->value.isSCRO)
                        FormIDHandler.AddMaster(SCR_[listIndex]->value.reference);
                    break;
                case 2: //isSCRO
                    if(FieldValue)
                        {
                        if(!SCR_[listIndex]->value.isSCRO)
                            {
                            SCR_[listIndex]->value.isSCRO = true;
                            FormIDHandler.AddMaster(SCR_[listIndex]->value.reference);
                            }
                        }
                    else if(SCR_[listIndex]->value.isSCRO)
                            {
                            SCR_[listIndex]->value.isSCRO = false;
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

void INFORecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    switch(subField)
        {
        case 13: //responses
            if(listIndex >= Responses.size())
                return;
            switch(listField)
                {
                case 2: //emotionValue
                    Responses[listIndex]->TRDT.value.emotionValue = FieldValue;
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

void INFORecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 13: //responses
            if(listIndex >= Responses.size())
                return;
            switch(listField)
                {
                case 3: //unused1
                    if(nSize != 4)
                        return;
                    Responses[listIndex]->TRDT.value.unused1[0] = FieldValue[0];
                    Responses[listIndex]->TRDT.value.unused1[1] = FieldValue[1];
                    Responses[listIndex]->TRDT.value.unused1[2] = FieldValue[2];
                    Responses[listIndex]->TRDT.value.unused1[3] = FieldValue[3];
                    break;
                case 5: //unused2
                    if(nSize != 3)
                        return;
                    Responses[listIndex]->TRDT.value.unused2[0] = FieldValue[0];
                    Responses[listIndex]->TRDT.value.unused2[1] = FieldValue[1];
                    Responses[listIndex]->TRDT.value.unused2[2] = FieldValue[2];
                    break;
                default:
                    return;
                }
            break;
        case 14: //conditions
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

void INFORecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 13: //responses
            if(listIndex >= Responses.size())
                return;
            switch(listField)
                {
                case 4: //responseNum
                    Responses[listIndex]->TRDT.value.responseNum = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 14: //conditions
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

void INFORecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue)
    {
    switch(subField)
        {
        case 13: //responses
            if(listIndex >= Responses.size())
                return;
            switch(listField)
                {
                case 6: //responseText
                    Responses[listIndex]->NAM1.Copy(FieldValue);
                    break;
                case 7: //actorNotes
                    Responses[listIndex]->NAM2.Copy(FieldValue);
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

void INFORecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue)
    {
    switch(subField)
        {
        case 14: //conditions
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
