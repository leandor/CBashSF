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
#include "..\Records\QUSTRecord.h"

int QUSTRecord::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    QUSTStage *curStage = NULL;
    QUSTTarget *curTarget = NULL;
    switch(subField)
        {
        case 11: //conditions
            curCTDA = new ReqRecordField<GENCTDA>;
            CTDA.push_back(curCTDA);
            return (int)CTDA.size() - 1;
        case 12: //stages
            curStage = new QUSTStage;
            Stages.push_back(curStage);
            return (int)Stages.size() - 1;
        case 13: //targets
            curTarget = new QUSTTarget;
            Targets.push_back(curTarget);
            return (int)Targets.size() - 1;
        default:
            return -1;
        }
    }

int QUSTRecord::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    QUSTStage *curStage = NULL;
    QUSTTarget *curTarget = NULL;
    switch(subField)
        {
        case 11: //conditions
            curCTDA = CTDA.back();
            delete curCTDA;
            CTDA.pop_back();
            return (int)CTDA.size() - 1;
        case 12: //stages
            curStage = Stages.back();
            delete curStage;
            Stages.pop_back();
            return (int)Stages.size() - 1;
        case 13: //targets
            curTarget = Targets.back();
            delete curTarget;
            Targets.pop_back();
            return (int)Targets.size() - 1;
        default:
            return -1;
        }
    }

int QUSTRecord::CreateListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    QUSTEntry * curEntry;
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return -1;
            switch(listField)
                {
                case 2: //entries
                    curEntry = new QUSTEntry;
                    Stages[listIndex]->Entries.push_back(curEntry);
                    return (int)Stages[listIndex]->Entries.size() - 1;
                default:
                    return -1;
                }
        case 13: //targets
            if(listIndex >= Targets.size())
                return -1;
            switch(listField)
                {
                case 4: //conditions
                    curCTDA = new ReqRecordField<GENCTDA>;
                    Targets[listIndex]->CTDA.push_back(curCTDA);
                    return (int) Targets[listIndex]->CTDA.size() - 1;
                default:
                    return -1;
                }
        default:
            return -1;
        }
    }

int QUSTRecord::DeleteListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    QUSTEntry * curEntry;
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return -1;
            switch(listField)
                {
                case 2: //entries
                    curEntry = Stages[listIndex]->Entries.back();
                    delete curEntry;
                    Stages[listIndex]->Entries.pop_back();
                    return (int)Stages[listIndex]->Entries.size() - 1;
                default:
                    return -1;
                }
        case 13: //targets
            if(listIndex >= Targets.size())
                return -1;
            switch(listField)
                {
                case 4: //conditions
                    curCTDA = Targets[listIndex]->CTDA.back();
                    delete curCTDA;
                    Targets[listIndex]->CTDA.pop_back();
                    return (int)Targets[listIndex]->CTDA.size() - 1;
                default:
                    return -1;
                }
        default:
            return -1;
        }
    }

int QUSTRecord::CreateListX3Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    ReqRecordField<GENSCR_> *curSCR_ = NULL;
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return -1;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return -1;
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            curCTDA = new ReqRecordField<GENCTDA>;
                            Stages[listIndex]->Entries[listX2Index]->CTDA.push_back(curCTDA);
                            return (int)Stages[listIndex]->Entries[listX2Index]->CTDA.size() - 1;
                        case 11: //references
                            curSCR_ = new ReqRecordField<GENSCR_>;
                            Stages[listIndex]->Entries[listX2Index]->SCR_.push_back(curSCR_);
                            return (int)Stages[listIndex]->Entries[listX2Index]->SCR_.size() - 1;
                        default:
                            return -1;
                        }
                default:
                    return -1;
                }
        default:
            return -1;
        }
    }

int QUSTRecord::DeleteListX3Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    ReqRecordField<GENCTDA> *curCTDA = NULL;
    ReqRecordField<GENSCR_> *curSCR_ = NULL;
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return -1;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return -1;
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            curCTDA = Stages[listIndex]->Entries[listX2Index]->CTDA.back();
                            delete curCTDA;
                            Stages[listIndex]->Entries[listX2Index]->CTDA.pop_back();
                            return (int)Stages[listIndex]->Entries[listX2Index]->CTDA.size() - 1;
                        case 11: //references
                            curSCR_ = Stages[listIndex]->Entries[listX2Index]->SCR_.back();
                            delete curSCR_;
                            Stages[listIndex]->Entries[listX2Index]->SCR_.pop_back();
                            return (int)Stages[listIndex]->Entries[listX2Index]->SCR_.size() - 1;
                        default:
                            return -1;
                        }
                default:
                    return -1;
                }
        default:
            return -1;
        }
    }

int QUSTRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //script
            return FID_FIELD;
        case 7: //full
            return STRING_FIELD;
        case 8: //iconPath
            return STRING_FIELD;
        case 9: //questFlags
            return UBYTE_FIELD;
        case 10: //priority
            return UBYTE_FIELD;
        case 11: //conditions
            return LIST_FIELD;
        case 12: //stages
            return LIST_FIELD;
        case 13: //targets
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * QUSTRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 7: //full
            return FULL.value;
        case 8: //iconPath
            return ICON.value;
        case 9: //questFlags
            return &DATA.value.flags;
        case 10: //priority
            return &DATA.value.priority;
        default:
            return NULL;
        }
    }

int QUSTRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 11: //conditions
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
        case 12: //stages
            switch(listField)
                {
                case 1: //stage
                    return USHORT_FIELD;
                case 2: //entries
                    return LIST_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //targets
            switch(listField)
                {
                case 1: //targetId
                    return FID_FIELD;
                case 2: //flags
                    return UBYTE_FIELD;
                case 3: //unused1
                    return BYTES_FIELD;
                case 4: //conditions
                    return LIST_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

int QUSTRecord::GetListX2FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field)
    {
    switch(subField)
        {
        case 12: //stages
            switch(listField)
                {
                case 2: //entries
                    switch(listX2Field)
                        {
                        case 1: //flags
                            return UBYTE_FIELD;
                        case 2: //conditions
                            return LIST_FIELD;
                        case 3: //text
                            return STRING_FIELD;
                        case 4: //unused1
                            return BYTES_FIELD;
                        case 5: //numRefs
                            return UINT_FIELD;
                        case 6: //compiledSize
                            return UINT_FIELD;
                        case 7: //lastIndex
                            return UINT_FIELD;
                        case 8: //scriptType
                            return UINT_FIELD;
                        case 9: //compiled_p
                            return BYTES_FIELD;
                        case 10: //scriptText
                            return STRING_FIELD;
                        case 11: //references
                            return LIST_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //targets
            switch(listField)
                {
                case 4: //conditions
                    switch(listX2Field)
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
        default:
            return UNKNOWN_FIELD;
        }
    }

int QUSTRecord::GetListX3FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field)
    {
    switch(subField)
        {
        case 12: //stages
            switch(listField)
                {
                case 2: //entries
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            switch(listX3Field)
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
                        case 11: //references
                            switch(listX3Field)
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
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int QUSTRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 11: //conditions
            return (unsigned int)CTDA.size();
        case 12: //stages
            return (unsigned int)Stages.size();
        case 13: //targets
            return (unsigned int)Targets.size();
        default:
            return 0;
        }
    }

unsigned int QUSTRecord::GetListX2Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return 0;
            switch(listField)
                {
                case 2: //entries
                    return (unsigned int)Stages[listIndex]->Entries.size();
                default:
                    return 0;
                }
        case 13: //targets
            if(listIndex >= Targets.size())
                return 0;
            switch(listField)
                {
                case 4: //conditions
                    return (unsigned int)Targets[listIndex]->CTDA.size();
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned int QUSTRecord::GetListX3Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return 0;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return 0;
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            return (unsigned int)Stages[listIndex]->Entries[listX2Index]->CTDA.size();
                        case 11: //references
                            return (unsigned int)Stages[listIndex]->Entries[listX2Index]->SCR_.size();
                        default:
                            return 0;
                        }
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned int QUSTRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 11: //conditions
            switch(listField)
                {
                case 2: //unused1
                    return 3;
                case 7: //unused2
                    return 4;
                default:
                    return 0;
                }
        case 13: //targets
            switch(listField)
                {
                case 3: //unused1
                    return 3;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned int QUSTRecord::GetListX2ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return 0;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return 0;
                    switch(listX2Field)
                        {
                        case 4: //unused1
                            return 4;
                        case 9: //compiled_p
                            return Stages[listIndex]->Entries[listX2Index]->SCDA.size;
                        default:
                            return 0;
                        }
                default:
                    return 0;
                }
        case 13: //targets
            switch(listField)
                {
                case 4: //conditions
                    switch(listX2Field)
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
        default:
            return 0;
        }
    }

unsigned int QUSTRecord::GetListX3ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    switch(subField)
        {
        case 12: //stages
            switch(listField)
                {
                case 2: //entries
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            switch(listX3Field)
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
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

void QUSTRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 11: //conditions
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
        case 13: //targets
            if(listIndex >= Targets.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 3: //unused1
                    *FieldValues = &Targets[listIndex]->QSTA.value.unused1[0];
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

void QUSTRecord::GetListX2Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
    {
    //printf("get, subField:%u, listIndex:%u, listField:%u, listX2Index:%u, listX2Field:%u\n", subField, listIndex, listField, listX2Index, listX2Field);
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        {
                        *FieldValues = NULL;
                        return;
                        }
                    switch(listX2Field)
                        {
                        case 4: //unused1
                            *FieldValues = &Stages[listIndex]->Entries[listX2Index]->SCHR.value.unused1[0];
                            return;
                        case 9: //compiled_p
                            *FieldValues = Stages[listIndex]->Entries[listX2Index]->SCDA.value;
                            return;
                        default:
                            *FieldValues = NULL;
                            return;
                        }
                default:
                    *FieldValues = NULL;
                    return;
                }
        case 13: //targets
            if(listIndex >= Targets.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 4: //conditions
                    if(listX2Index >= Targets[listIndex]->CTDA.size())
                        {
                        *FieldValues = NULL;
                        return;
                        }
                    switch(listX2Field)
                        {
                        case 2: //unused1
                            *FieldValues = &Targets[listIndex]->CTDA[listX2Index]->value.unused1[0];
                            return;
                        case 7: //unused2
                            *FieldValues = &Targets[listIndex]->CTDA[listX2Index]->value.unused2[0];
                            return;
                        default:
                            *FieldValues = NULL;
                            return;
                        }
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void QUSTRecord::GetListX3Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues)
    {
    //printf("\nget, subField:%u, listIndex:%u, listField:%u, listX2Index:%u, listX2Field:%u, listX3Index:%u, listX3Field:%u\n", subField, listIndex, listField, listX2Index, listX2Field, listX3Index, listX3Field);
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        {
                        *FieldValues = NULL;
                        return;
                        }
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            if(listX3Index >= Stages[listIndex]->Entries[listX2Index]->CTDA.size())
                                {
                                *FieldValues = NULL;
                                return;
                                }
                            switch(listX3Field)
                                {
                                case 2: //unused1
                                    *FieldValues = &Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused1[0];
                                    return;
                                case 7: //unused2
                                    *FieldValues = &Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused2[0];
                                    return;
                                default:
                                    *FieldValues = NULL;
                                    return;
                                }
                        default:
                            *FieldValues = NULL;
                            return;
                        }
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void * QUSTRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 11: //conditions
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
        case 12: //stages
            if(listIndex >= Stages.size())
                return NULL;
            switch(listField)
                {
                case 1: //stage
                    return &Stages[listIndex]->INDX.value.stage;
                default:
                    return NULL;
                }
        case 13: //targets
            if(listIndex >= Targets.size())
                return NULL;
            switch(listField)
                {
                case 1: //targetId
                    return &Targets[listIndex]->QSTA.value.targetId;
                case 2: //flags
                    return &Targets[listIndex]->QSTA.value.flags;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void * QUSTRecord::GetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return NULL;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 1: //flags
                            return &Stages[listIndex]->Entries[listX2Index]->QSDT.value.flags;
                        case 3: //text
                            return Stages[listIndex]->Entries[listX2Index]->CNAM.value;
                        case 5: //numRefs
                            return &Stages[listIndex]->Entries[listX2Index]->SCHR.value.numRefs;
                        case 6: //compiledSize
                            return &Stages[listIndex]->Entries[listX2Index]->SCHR.value.compiledSize;
                        case 7: //lastIndex
                            return &Stages[listIndex]->Entries[listX2Index]->SCHR.value.lastIndex;
                        case 8: //scriptType
                            return &Stages[listIndex]->Entries[listX2Index]->SCHR.value.scriptType;
                        case 10: //scriptText
                            return Stages[listIndex]->Entries[listX2Index]->SCTX.value;
                        default:
                            return NULL;
                        }
                default:
                    return NULL;
                }
        case 13: //targets
            if(listIndex >= Targets.size())
                return NULL;
            switch(listField)
                {
                case 4: //conditions
                    if(listX2Index >= Targets[listIndex]->CTDA.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 1: //operType
                            return &Targets[listIndex]->CTDA[listX2Index]->value.operType;
                        case 3: //compValue
                            return &Targets[listIndex]->CTDA[listX2Index]->value.compValue;
                        case 4: //ifunc
                            return &Targets[listIndex]->CTDA[listX2Index]->value.ifunc;
                        case 5: //param1
                            return &Targets[listIndex]->CTDA[listX2Index]->value.param1;
                        case 6: //param2
                            return &Targets[listIndex]->CTDA[listX2Index]->value.param2;
                        default:
                            return NULL;
                        }
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void * QUSTRecord::GetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return NULL;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            if(listX3Index >= Stages[listIndex]->Entries[listX2Index]->CTDA.size())
                                return NULL;
                            switch(listX3Field)
                                {
                                case 1: //operType
                                    return &Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.operType;
                                case 3: //compValue
                                    return &Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.compValue;
                                case 4: //ifunc
                                    return &Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.ifunc;
                                case 5: //param1
                                    return &Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.param1;
                                case 6: //param2
                                    return &Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.param2;
                                default:
                                    return NULL;
                                }
                        case 11: //references
                            if(listX3Index >= Stages[listIndex]->Entries[listX2Index]->SCR_.size())
                                return NULL;
                            switch(listX3Field)
                                {
                                case 1: //reference
                                    return &Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.reference;
                                case 2: //isSCRO
                                    return &Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.isSCRO;
                                default:
                                    return NULL;
                                }
                        default:
                            return NULL;
                        }
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void QUSTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 7: //full
            FULL.Copy(FieldValue);
            break;
        case 8: //iconPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void QUSTRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 6: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        default:
            return;
        }
    return;
    }

void QUSTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 9: //questFlags
            DATA.value.flags = FieldValue;
            break;
        case 10: //priority
            DATA.value.priority = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void QUSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 11: //conditions
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
        case 13: //targets
            if(listIndex >= Targets.size())
                return;
            switch(listField)
                {
                case 2: //flags
                    Targets[listIndex]->QSTA.value.flags = FieldValue;
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

void QUSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 11: //conditions
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
        case 13: //targets
            if(listIndex >= Targets.size())
                return;
            switch(listField)
                {
                case 3: //unused1
                    if(nSize != 3)
                        return;
                    Targets[listIndex]->QSTA.value.unused1[0] = FieldValue[0];
                    Targets[listIndex]->QSTA.value.unused1[1] = FieldValue[1];
                    Targets[listIndex]->QSTA.value.unused1[2] = FieldValue[2];
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

void QUSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue)
    {
    switch(subField)
        {
        case 11: //conditions
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

void QUSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    std::pair<unsigned int, unsigned int> newCTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
    switch(subField)
        {
        case 11: //conditions
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
        case 13: //targets
            if(listIndex >= Targets.size())
                return;
            switch(listField)
                {
                case 1: //targetId
                    Targets[listIndex]->QSTA.value.targetId = FieldValue;
                    FormIDHandler.AddMaster(Targets[listIndex]->QSTA.value.targetId);
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

void QUSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned short FieldValue)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 1: //stage
                    Stages[listIndex]->INDX.value.stage = FieldValue;
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

void QUSTRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return;
                    switch(listX2Field)
                        {
                        case 1: //flags
                            Stages[listIndex]->Entries[listX2Index]->QSDT.value.flags = FieldValue;
                            break;
                        default:
                            return;
                        }
                    break;
                default:
                    return;
                }
            break;
        case 13: //targets
            if(listIndex >= Targets.size())
                return;
            switch(listField)
                {
                case 4: //conditions
                    if(listX2Index >= Targets[listIndex]->CTDA.size())
                        return;
                    switch(listX2Field)
                        {
                        case 1: //operType
                            Targets[listIndex]->CTDA[listX2Index]->value.operType = FieldValue;
                            break;
                        default:
                            return;
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

void QUSTRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char *FieldValue)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return;
                    switch(listX2Field)
                        {
                        case 3: //text
                            Stages[listIndex]->Entries[listX2Index]->CNAM.Copy(FieldValue);
                            break;
                        case 10: //scriptText
                            Stages[listIndex]->Entries[listX2Index]->SCTX.Copy(FieldValue);
                            break;
                        default:
                            return;
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

void QUSTRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return;
                    switch(listX2Field)
                        {
                        case 4: //unused1
                            if(nSize != 4)
                                return;
                            Stages[listIndex]->Entries[listX2Index]->SCHR.value.unused1[0] = FieldValue[0];
                            Stages[listIndex]->Entries[listX2Index]->SCHR.value.unused1[1] = FieldValue[1];
                            Stages[listIndex]->Entries[listX2Index]->SCHR.value.unused1[2] = FieldValue[2];
                            Stages[listIndex]->Entries[listX2Index]->SCHR.value.unused1[3] = FieldValue[3];
                            break;
                        case 9: //compiled_p
                            Stages[listIndex]->Entries[listX2Index]->SCDA.Copy(FieldValue, nSize);
                            break;
                        default:
                            return;
                        }
                    break;
                default:
                    return;
                }
            break;
        case 13: //targets
            if(listIndex >= Targets.size())
                return;
            switch(listField)
                {
                case 4: //conditions
                    if(listX2Index >= Targets[listIndex]->CTDA.size())
                        return;
                    switch(listX2Field)
                        {
                        case 2: //unused1
                            if(nSize != 3)
                                return;
                            Targets[listIndex]->CTDA[listX2Index]->value.unused1[0] = FieldValue[0];
                            Targets[listIndex]->CTDA[listX2Index]->value.unused1[1] = FieldValue[1];
                            Targets[listIndex]->CTDA[listX2Index]->value.unused1[2] = FieldValue[2];
                            break;
                        case 7: //unused2
                            if(nSize != 4)
                                return;
                            Targets[listIndex]->CTDA[listX2Index]->value.unused2[0] = FieldValue[0];
                            Targets[listIndex]->CTDA[listX2Index]->value.unused2[1] = FieldValue[1];
                            Targets[listIndex]->CTDA[listX2Index]->value.unused2[2] = FieldValue[2];
                            Targets[listIndex]->CTDA[listX2Index]->value.unused2[3] = FieldValue[3];
                            break;
                        default:
                            return;
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

void QUSTRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue)
    {
    std::pair<unsigned int, unsigned int> newCTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return;
                    switch(listX2Field)
                        {
                        case 5: //numRefs
                            Stages[listIndex]->Entries[listX2Index]->SCHR.value.numRefs = FieldValue;
                            break;
                        case 6: //compiledSize
                            Stages[listIndex]->Entries[listX2Index]->SCHR.value.compiledSize = FieldValue;
                            break;
                        case 7: //lastIndex
                            Stages[listIndex]->Entries[listX2Index]->SCHR.value.lastIndex = FieldValue;
                            break;
                        case 8: //scriptType
                            Stages[listIndex]->Entries[listX2Index]->SCHR.value.scriptType = FieldValue;
                            break;
                        default:
                            return;
                        }
                    break;
                default:
                    return;
                }
            break;
        case 13: //targets
            if(listIndex >= Targets.size())
                return;
            switch(listField)
                {
                case 4: //conditions
                    if(listX2Index >= Targets[listIndex]->CTDA.size())
                        return;
                    switch(listX2Field)
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

                            Targets[listIndex]->CTDA[listX2Index]->value.ifunc = FieldValue;

                            if(newCTDAFunction.first == eFID)
                                FormIDHandler.AddMaster(Targets[listIndex]->CTDA[listX2Index]->value.param1);

                            if(newCTDAFunction.second == eFID)
                                FormIDHandler.AddMaster(Targets[listIndex]->CTDA[listX2Index]->value.param2);
                            break;
                        case 5: //param1
                            Targets[listIndex]->CTDA[listX2Index]->value.param1 = FieldValue;

                            curCTDAFunction = Function_Arguments.find(Targets[listIndex]->CTDA[listX2Index]->value.ifunc);
                            if(curCTDAFunction != Function_Arguments.end())
                                {
                                newCTDAFunction = curCTDAFunction->second;
                                if(newCTDAFunction.first == eFID)
                                    FormIDHandler.AddMaster(Targets[listIndex]->CTDA[listX2Index]->value.param1);
                                }
                            break;
                        case 6: //param2
                            Targets[listIndex]->CTDA[listX2Index]->value.param2 = FieldValue;

                            curCTDAFunction = Function_Arguments.find(Targets[listIndex]->CTDA[listX2Index]->value.ifunc);
                            if(curCTDAFunction != Function_Arguments.end())
                                {
                                newCTDAFunction = curCTDAFunction->second;
                                if(newCTDAFunction.second == eFID)
                                    FormIDHandler.AddMaster(Targets[listIndex]->CTDA[listX2Index]->value.param2);
                                }
                            break;
                        default:
                            return;
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

void QUSTRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue)
    {
    switch(subField)
        {
        case 13: //targets
            if(listIndex >= Targets.size())
                return;
            switch(listField)
                {
                case 4: //conditions
                    if(listX2Index >= Targets[listIndex]->CTDA.size())
                        return;
                    switch(listX2Field)
                        {
                        case 3: //compValue
                            Targets[listIndex]->CTDA[listX2Index]->value.compValue = FieldValue;
                            break;
                        default:
                            return;
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

void QUSTRecord::SetListX3Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return;
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            if(listX3Index >= Stages[listIndex]->Entries[listX2Index]->CTDA.size())
                                return;
                            switch(listX3Field)
                                {
                                case 1: //operType
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.operType = FieldValue;
                                    break;
                                default:
                                    return;
                                }
                        default:
                            return;
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

void QUSTRecord::SetListX3Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return;
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            if(listX3Index >= Stages[listIndex]->Entries[listX2Index]->CTDA.size())
                                return;
                            switch(listX3Field)
                                {
                                case 2: //unused1
                                    if(nSize != 3)
                                        return;
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused1[0] = FieldValue[0];
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused1[1] = FieldValue[1];
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused1[2] = FieldValue[2];
                                    break;
                                case 7: //unused2
                                    if(nSize != 4)
                                        return;
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused2[0] = FieldValue[0];
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused2[1] = FieldValue[1];
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused2[2] = FieldValue[2];
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.unused2[3] = FieldValue[3];
                                    break;
                                default:
                                    return;
                                }
                        default:
                            return;
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

void QUSTRecord::SetListX3Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, float FieldValue)
    {
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return;
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            if(listX3Index >= Stages[listIndex]->Entries[listX2Index]->CTDA.size())
                                return;
                            switch(listX3Field)
                                {
                                case 3: //compValue
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.compValue = FieldValue;
                                    break;
                                default:
                                    return;
                                }
                        default:
                            return;
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

void QUSTRecord::SetListX3Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned int FieldValue)
    {
    std::pair<unsigned int, unsigned int> newCTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
    switch(subField)
        {
        case 12: //stages
            if(listIndex >= Stages.size())
                return;
            switch(listField)
                {
                case 2: //entries
                    if(listX2Index >= Stages[listIndex]->Entries.size())
                        return;
                    switch(listX2Field)
                        {
                        case 2: //conditions
                            if(listX3Index >= Stages[listIndex]->Entries[listX2Index]->CTDA.size())
                                return;
                            switch(listX3Field)
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

                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.ifunc = FieldValue;

                                    if(newCTDAFunction.first == eFID)
                                        FormIDHandler.AddMaster(Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.param1);

                                    if(newCTDAFunction.second == eFID)
                                        FormIDHandler.AddMaster(Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.param2);
                                    break;
                                case 5: //param1
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.param1 = FieldValue;

                                    curCTDAFunction = Function_Arguments.find(Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.ifunc);
                                    if(curCTDAFunction != Function_Arguments.end())
                                        {
                                        newCTDAFunction = curCTDAFunction->second;
                                        if(newCTDAFunction.first == eFID)
                                            FormIDHandler.AddMaster(Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.param1);
                                        }
                                    break;
                                case 6: //param2
                                    Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.param2 = FieldValue;

                                    curCTDAFunction = Function_Arguments.find(Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.ifunc);
                                    if(curCTDAFunction != Function_Arguments.end())
                                        {
                                        newCTDAFunction = curCTDAFunction->second;
                                        if(newCTDAFunction.second == eFID)
                                            FormIDHandler.AddMaster(Stages[listIndex]->Entries[listX2Index]->CTDA[listX3Index]->value.param2);
                                        }
                                    break;
                                default:
                                    return;
                                }
                        case 11: //references
                            if(listX3Index >= Stages[listIndex]->Entries[listX2Index]->SCR_.size())
                                return;
                            switch(listX3Field)
                                {
                                case 1: //reference
                                    Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.reference = FieldValue;
                                    if(Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.isSCRO)
                                        FormIDHandler.AddMaster(Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.reference);
                                    break;
                                case 2: //isSCRO
                                    if(FieldValue)
                                        {
                                        if(!Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.isSCRO)
                                            {
                                            Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.isSCRO = true;
                                            FormIDHandler.AddMaster(Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.reference);
                                            }
                                        }
                                    else if(Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.isSCRO)
                                        Stages[listIndex]->Entries[listX2Index]->SCR_[listX3Index]->value.isSCRO = false;
                                    break;
                                default:
                                    return;
                                }
                        default:
                            return;
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
