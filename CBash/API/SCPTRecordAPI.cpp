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
#include "..\Records\SCPTRecord.h"

int SCPTRecord::CreateListElement(const unsigned int subField)
    {
    SCPTVARS *curVARS = NULL;
    ReqRecordField<GENSCR_> *curSCR_ = NULL;
    switch(subField)
        {
        case 13: //vars
            curVARS = new SCPTVARS;
            VARS.push_back(curVARS);
            return (int)VARS.size() - 1;
        case 14: //references
            curSCR_ = new ReqRecordField<GENSCR_>;
            SCR_.push_back(curSCR_);
            return (int)SCR_.size() - 1;
        default:
            return -1;
        }
    }

int SCPTRecord::DeleteListElement(const unsigned int subField)
    {
    SCPTVARS *curVARS = NULL;
    ReqRecordField<GENSCR_> *curSCR_ = NULL;
    switch(subField)
        {
        case 13: //vars
            curVARS = VARS.back();
            delete curVARS;
            VARS.pop_back();
            return (int)VARS.size() - 1;
        case 14: //references
            curSCR_ = SCR_.back();
            delete curSCR_;
            SCR_.pop_back();
            return (int)SCR_.size() - 1;
        default:
            return -1;
        }
    }

int SCPTRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //unused1
            return BYTES_FIELD;
        case 7: //numRefs
            return UINT_FIELD;
        case 8: //compiledSize
            return UINT_FIELD;
        case 9: //lastIndex
            return UINT_FIELD;
        case 10: //scriptType
            return UINT_FIELD;
        case 11: //compiled_p
            return BYTES_FIELD;
        case 12: //scriptText
            return STRING_FIELD;
        case 13: //vars
            return LIST_FIELD;
        case 14: //references
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * SCPTRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 7: //numRefs
            return &SCHR.value.numRefs;
        case 8: //compiledSize
            return &SCHR.value.compiledSize;
        case 9: //lastIndex
            return &SCHR.value.lastIndex;
        case 10: //scriptType
            return &SCHR.value.scriptType;
        case 12: //scriptText
            return SCTX.value;
        default:
            return NULL;
        }
    }

unsigned int SCPTRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //unused1
            return 4;
        case 11: //compiled_p
            return SCDA.size;
        default:
            return 0;
        }
    }

void SCPTRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 6: //unused1
            *FieldValues = &SCHR.value.unused1[0];
            return;
        case 11: //compiled_p
            *FieldValues = SCDA.value;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int SCPTRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 13: //vars
            switch(listField)
                {
                case 1: //index
                    return UINT_FIELD;
                case 2: //unused1
                    return BYTES_FIELD;
                case 3: //flags
                    return UBYTE_FIELD;
                case 4: //unused2
                    return BYTES_FIELD;
                case 5: //name
                    return STRING_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //references
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

unsigned int SCPTRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 13: //vars
            return (unsigned int)VARS.size();
        case 14: //references
            return (unsigned int)SCR_.size();
        default:
            return 0;
        }
    }

unsigned int SCPTRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 13: //vars
            switch(listField)
                {
                case 2: //unused1
                    return 12;
                case 4: //unused2
                    return 7;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

void SCPTRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 13: //vars
            if(listIndex >= VARS.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 2: //unused1
                    *FieldValues = &VARS[listIndex]->SLSD.value.unused1[0];
                    return;
                case 4: //unused2
                    *FieldValues = &VARS[listIndex]->SLSD.value.unused2[0];
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

void * SCPTRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 13: //vars
            if(listIndex >= VARS.size())
                return NULL;
            switch(listField)
                {
                case 1: //index
                    return &VARS[listIndex]->SLSD.value.index;
                case 3: //flags
                    return &VARS[listIndex]->SLSD.value.flags;
                case 5: //name
                    return VARS[listIndex]->SCVR.value;
                default:
                    return NULL;
                }
        case 14: //references
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

void SCPTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 12: //scriptText
            SCTX.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void SCPTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 6: //unused1
            if(nSize != 4)
                return;
            SCHR.value.unused1[0] = FieldValue[0];
            SCHR.value.unused1[1] = FieldValue[1];
            SCHR.value.unused1[2] = FieldValue[2];
            SCHR.value.unused1[3] = FieldValue[3];
            break;
        case 11: //compiled_p
            SCDA.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void SCPTRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 7: //numRefs
            SCHR.value.numRefs = FieldValue;
            break;
        case 8: //compiledSize
            SCHR.value.compiledSize = FieldValue;
            break;
        case 9: //lastIndex
            SCHR.value.lastIndex = FieldValue;
            break;
        case 10: //scriptType
            SCHR.value.scriptType = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SCPTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 13: //vars
            if(listIndex >= VARS.size())
                return;
            switch(listField)
                {
                case 1: //index
                    VARS[listIndex]->SLSD.value.index = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 14: //references
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
                            SCR_[listIndex]->value.isSCRO = false;
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

void SCPTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 13: //vars
            if(listIndex >= VARS.size())
                return;
            switch(listField)
                {
                case 2: //unused1
                    if(nSize != 12)
                        return;
                    VARS[listIndex]->SLSD.value.unused1[0] = FieldValue[0];
                    VARS[listIndex]->SLSD.value.unused1[1] = FieldValue[1];
                    VARS[listIndex]->SLSD.value.unused1[2] = FieldValue[2];
                    VARS[listIndex]->SLSD.value.unused1[3] = FieldValue[3];
                    VARS[listIndex]->SLSD.value.unused1[4] = FieldValue[4];
                    VARS[listIndex]->SLSD.value.unused1[5] = FieldValue[5];
                    VARS[listIndex]->SLSD.value.unused1[6] = FieldValue[6];
                    VARS[listIndex]->SLSD.value.unused1[7] = FieldValue[7];
                    VARS[listIndex]->SLSD.value.unused1[8] = FieldValue[8];
                    VARS[listIndex]->SLSD.value.unused1[9] = FieldValue[9];
                    VARS[listIndex]->SLSD.value.unused1[10] = FieldValue[10];
                    VARS[listIndex]->SLSD.value.unused1[11] = FieldValue[11];
                    break;
                case 4: //unused2
                    if(nSize != 7)
                        return;
                    VARS[listIndex]->SLSD.value.unused2[0] = FieldValue[0];
                    VARS[listIndex]->SLSD.value.unused2[1] = FieldValue[1];
                    VARS[listIndex]->SLSD.value.unused2[2] = FieldValue[2];
                    VARS[listIndex]->SLSD.value.unused2[3] = FieldValue[3];
                    VARS[listIndex]->SLSD.value.unused2[4] = FieldValue[4];
                    VARS[listIndex]->SLSD.value.unused2[5] = FieldValue[5];
                    VARS[listIndex]->SLSD.value.unused2[6] = FieldValue[6];
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

void SCPTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 13: //vars
            if(listIndex >= VARS.size())
                return;
            switch(listField)
                {
                case 3: //flags
                    VARS[listIndex]->SLSD.value.flags = FieldValue;
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

void SCPTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue)
    {
    switch(subField)
        {
        case 13: //vars
            if(listIndex >= VARS.size())
                return;
            switch(listField)
                {
                case 5: //name
                    VARS[listIndex]->SCVR.Copy(FieldValue);
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

