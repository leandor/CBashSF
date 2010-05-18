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
#pragma once
#include "..\Common.h"
#include "..\BaseRecord.h"
#include <vector>

class QUSTRecord : public Record
    {
    private:
        enum QUSTRecordFields {
            eEDID = 0x44494445,
            eSCRI = 0x49524353,
            eFULL = 0x4C4C5546,
            eICON = 0x4E4F4349,
            eDATA = 0x41544144,
            eCTDA = 0x41445443,
            eCTDT = 0x54445443,
            eINDX = 0x58444E49,
            eQSDT = 0x54445351,

            eCNAM = 0x4D414E43,
            eSCHR = 0x52484353,
            eSCDA = 0x41444353,
            eSCTX = 0x58544353,
            eSCRV = 0x56524353,
            eSCRO = 0x4F524353,
            eQSTA = 0x41545351
            };
        struct QUSTDATA
            {
            unsigned char flags, priority;
            QUSTDATA():flags(0), priority(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags    = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    printf("priority = %u\n", priority);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct QUSTEntry
            {
            ReqRecordField<GENFLAG> QSDT;
            std::vector<ReqRecordField<GENCTDA> *> CTDA;
            STRING CNAM;
            ReqRecordField<GENSCHR> SCHR;
            RAWBYTES SCDA;
            NONNULLSTRING SCTX;
            std::vector<ReqRecordField<GENSCR_> *> SCR_;
            ~QUSTEntry()
                {
                for(unsigned int x = 0; x < CTDA.size(); x++)
                    delete CTDA[x];
                for(unsigned int x = 0; x < SCR_.size(); x++)
                    delete SCR_[x];
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    QSDT.Debug("QSDT", debugLevel, indentation);
                    if(CTDA.size())
                        {
                        PrintIndent(indentation);
                        printf("CTDA:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < CTDA.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            CTDA[p]->Debug(NULL, debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    CNAM.Debug("CNAM", debugLevel, indentation);
                    SCHR.Debug("SCHR", debugLevel, indentation);
                    SCDA.Debug("SCDA", debugLevel, indentation);
                    SCTX.Debug("SCTX", debugLevel, indentation);
                    if(SCR_.size())
                        {
                        PrintIndent(indentation);
                        printf("SCR_:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < SCR_.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            SCR_[p]->Debug(NULL, debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    indentation -= 2;
                    }
                }
            #endif
            enum entriesFlags
                {
                fIsCompletes = 0x00000001
                };
            bool IsCompletes()
                {
                return (QSDT.value.flags & fIsCompletes) != 0;
                }
            void IsCompletes(bool value)
                {
                if(value)
                    QSDT.value.flags |= fIsCompletes;
                else
                    QSDT.value.flags &= ~fIsCompletes;
                }
            bool IsFlagMask(unsigned char Mask, bool Exact=false)
                {
                if(Exact)
                    return (QSDT.value.flags & Mask) == Mask;
                else
                    return (QSDT.value.flags & Mask) != 0;
                }
            void SetFlagMask(unsigned char Mask)
                {
                QSDT.value.flags = Mask;
                }
            };
        struct QUSTINDX
            {
            unsigned short stage;
            QUSTINDX():stage(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("stage = %u\n", stage);
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct QUSTStage
            {
            ReqRecordField<QUSTINDX> INDX;
            std::vector<QUSTEntry *> Entries;
            ~QUSTStage()
                {
                for(unsigned int x = 0; x < Entries.size(); x++)
                    delete Entries[x];
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    INDX.Debug("INDX", debugLevel, indentation);
                    if(Entries.size())
                        {
                        PrintIndent(indentation);
                        printf("Entries:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < Entries.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            Entries[p]->Debug(debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct QUSTQSTA
            {
            unsigned int targetId;
            unsigned char flags, unused1[3];
            QUSTQSTA():targetId(0), flags(0)
                {
                memset(&unused1, 0x00, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("targetId = %s\n", PrintFormID(targetId));
                    PrintIndent(indentation);
                    printf("flags    = %u\n", flags);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1  = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct QUSTTarget
            {
            ReqRecordField<QUSTQSTA> QSTA;
            std::vector<ReqRecordField<GENCTDA> *> CTDA;
            ~QUSTTarget()
                {
                for(unsigned int x = 0; x < CTDA.size(); x++)
                    delete CTDA[x];
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    QSTA.Debug("QSTA", debugLevel, indentation);
                    if(CTDA.size())
                        {
                        PrintIndent(indentation);
                        printf("CTDA:\n");
                        indentation += 2;
                        for(unsigned int p = 0;p < CTDA.size();p++)
                            {
                            PrintIndent(indentation);
                            printf("Index: %u\n", p);
                            CTDA[p]->Debug(NULL, debugLevel, indentation);
                            }
                        indentation -= 2;
                        }
                    indentation -= 2;
                    }
                }
            #endif
            enum targetsFlags
                {
                fIsIgnoresLocks = 0x00000001
                };
            bool IsIgnoresLocks()
                {
                return (QSTA.value.flags & fIsIgnoresLocks) != 0;
                }
            void IsIgnoresLocks(bool value)
                {
                if(value)
                    QSTA.value.flags |= fIsIgnoresLocks;
                else
                    QSTA.value.flags &= ~fIsIgnoresLocks;
                }
            bool IsFlagMask(unsigned char Mask, bool Exact=false)
                {
                if(Exact)
                    return (QSTA.value.flags & Mask) == Mask;
                else
                    return (QSTA.value.flags & Mask) != 0;
                }
            void SetFlagMask(unsigned char Mask)
                {
                QSTA.value.flags = Mask;
                }
            };
    public:
        enum flagsFlags
            {
            fIsStartEnabled   = 0x00000001,
            fIsRepeatedTopics = 0x00000004,
            fIsRepeatedStages = 0x00000008
            };
        STRING EDID;
        OptRecordField<GENFID> SCRI;
        STRING FULL;
        STRING ICON;
        ReqRecordField<QUSTDATA> DATA;
        std::vector<ReqRecordField<GENCTDA> *> CTDA;
        std::vector<QUSTStage *> Stages;
        std::vector<QUSTTarget *> Targets;

        QUSTRecord(bool newRecord=false):Record(newRecord) {}
        QUSTRecord(const unsigned int &newFormID):Record(newFormID) {}
        QUSTRecord(QUSTRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            SCRI = srcRecord->SCRI;
            FULL = srcRecord->FULL;
            ICON = srcRecord->ICON;
            DATA = srcRecord->DATA;

            CTDA.clear();
            CTDA.resize(srcRecord->CTDA.size());
            for(unsigned int x = 0; x < srcRecord->CTDA.size(); x++)
                {
                CTDA[x] = new ReqRecordField<GENCTDA>;
                *CTDA[x] = *srcRecord->CTDA[x];
                }
            Stages.clear();
            Stages.resize(srcRecord->Stages.size());
            for(unsigned int x = 0; x < srcRecord->Stages.size(); x++)
                {
                Stages[x] = new QUSTStage;
                Stages[x]->INDX = srcRecord->Stages[x]->INDX;
                Stages[x]->Entries.clear();
                Stages[x]->Entries.resize(srcRecord->Stages[x]->Entries.size());
                for(unsigned int y = 0; y < srcRecord->Stages[x]->Entries.size(); y++)
                    {
                    Stages[x]->Entries[y] = new QUSTEntry;
                    Stages[x]->Entries[y]->QSDT = srcRecord->Stages[x]->Entries[y]->QSDT;
                    Stages[x]->Entries[y]->CTDA.clear();
                    Stages[x]->Entries[y]->CTDA.resize(srcRecord->Stages[x]->Entries[y]->CTDA.size());
                    for(unsigned int p = 0; p < srcRecord->Stages[x]->Entries[y]->CTDA.size(); p++)
                        {
                        Stages[x]->Entries[y]->CTDA[p] = new ReqRecordField<GENCTDA>;
                        *Stages[x]->Entries[y]->CTDA[p] = *srcRecord->Stages[x]->Entries[y]->CTDA[p];
                        }
                    Stages[x]->Entries[y]->CNAM = srcRecord->Stages[x]->Entries[y]->CNAM;
                    Stages[x]->Entries[y]->SCHR = srcRecord->Stages[x]->Entries[y]->SCHR;
                    Stages[x]->Entries[y]->SCDA = srcRecord->Stages[x]->Entries[y]->SCDA;
                    Stages[x]->Entries[y]->SCTX = srcRecord->Stages[x]->Entries[y]->SCTX;
                    Stages[x]->Entries[y]->SCR_.clear();
                    Stages[x]->Entries[y]->SCR_.resize(srcRecord->Stages[x]->Entries[y]->SCR_.size());
                    for(unsigned int p = 0; p < srcRecord->Stages[x]->Entries[y]->SCR_.size(); p++)
                        {
                        Stages[x]->Entries[y]->SCR_[p] = new ReqRecordField<GENSCR_>;
                        *Stages[x]->Entries[y]->SCR_[p] = *srcRecord->Stages[x]->Entries[y]->SCR_[p];
                        }
                    }
                }
            Targets.clear();
            Targets.resize(srcRecord->Targets.size());
            for(unsigned int x = 0; x < srcRecord->Targets.size(); x++)
                {
                Targets[x] = new QUSTTarget;
                Targets[x]->QSTA = srcRecord->Targets[x]->QSTA;
                Targets[x]->CTDA.clear();
                Targets[x]->CTDA.resize(srcRecord->Targets[x]->CTDA.size());
                for(unsigned int y = 0; y < srcRecord->Targets[x]->CTDA.size(); y++)
                    {
                    Targets[x]->CTDA[y] = new ReqRecordField<GENCTDA>;
                    *Targets[x]->CTDA[y] = *srcRecord->Targets[x]->CTDA[y];
                    }
                }
            return;
            }
        ~QUSTRecord()
            {
            for(unsigned int x = 0; x < CTDA.size(); x++)
                delete CTDA[x];
            for(unsigned int x = 0; x < Stages.size(); x++)
                delete Stages[x];
            for(unsigned int x = 0; x < Targets.size(); x++)
                delete Targets[x];
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            std::pair<unsigned int, unsigned int> CTDAFunction;
            std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
            if(SCRI.IsLoaded())
                FormIDHandler.ExpandFormID(SCRI->fid);
            for(unsigned int x = 0; x < CTDA.size(); x++)
                {
                curCTDAFunction = Function_Arguments.find(CTDA[x]->value.ifunc);
                if(curCTDAFunction != Function_Arguments.end())
                    {
                    CTDAFunction = curCTDAFunction->second;
                    if(CTDAFunction.first == eFID)
                        FormIDHandler.ExpandFormID(CTDA[x]->value.param1);
                    if(CTDAFunction.second == eFID)
                        FormIDHandler.ExpandFormID(CTDA[x]->value.param2);
                    }
                }
            for(unsigned int x = 0; x < Stages.size(); x++)
                {
                for(unsigned int y = 0; y < Stages[x]->Entries.size(); y++)
                    {
                    for(unsigned int p = 0; p < Stages[x]->Entries[y]->CTDA.size(); p++)
                        {
                        curCTDAFunction = Function_Arguments.find(Stages[x]->Entries[y]->CTDA[p]->value.ifunc);
                        if(CTDAFunction.first == eFID)
                            FormIDHandler.ExpandFormID(Stages[x]->Entries[y]->CTDA[p]->value.param1);
                        if(CTDAFunction.second == eFID)
                            FormIDHandler.ExpandFormID(Stages[x]->Entries[y]->CTDA[p]->value.param2);
                        }
                    for(unsigned int p = 0; p < Stages[x]->Entries[y]->SCR_.size(); p++)
                        if(Stages[x]->Entries[y]->SCR_[p]->value.isSCRO)
                            FormIDHandler.ExpandFormID(Stages[x]->Entries[y]->SCR_[p]->value.reference);
                    }
                }

            for(unsigned int x = 0; x < Targets.size(); x++)
                {
                FormIDHandler.ExpandFormID(Targets[x]->QSTA.value.targetId);
                for(unsigned int y = 0; y < Targets[x]->CTDA.size(); y++)
                    {
                    curCTDAFunction = Function_Arguments.find(Targets[x]->CTDA[y]->value.ifunc);
                    if(curCTDAFunction != Function_Arguments.end())
                        {
                        CTDAFunction = curCTDAFunction->second;
                        if(CTDAFunction.first == eFID)
                            FormIDHandler.ExpandFormID(Targets[x]->CTDA[y]->value.param1);
                        if(CTDAFunction.second == eFID)
                            FormIDHandler.ExpandFormID(Targets[x]->CTDA[y]->value.param2);
                        }
                    }
                }
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            std::pair<unsigned int, unsigned int> CTDAFunction;
            std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
            if(SCRI.IsLoaded())
                FormIDHandler.CollapseFormID(SCRI->fid);
            for(unsigned int x = 0; x < CTDA.size(); x++)
                {
                curCTDAFunction = Function_Arguments.find(CTDA[x]->value.ifunc);
                if(curCTDAFunction != Function_Arguments.end())
                    {
                    CTDAFunction = curCTDAFunction->second;
                    if(CTDAFunction.first == eFID)
                        FormIDHandler.CollapseFormID(CTDA[x]->value.param1);
                    if(CTDAFunction.second == eFID)
                        FormIDHandler.CollapseFormID(CTDA[x]->value.param2);
                    }
                }
            for(unsigned int x = 0; x < Stages.size(); x++)
                {
                for(unsigned int y = 0; y < Stages[x]->Entries.size(); y++)
                    {
                    for(unsigned int p = 0; p < Stages[x]->Entries[y]->CTDA.size(); p++)
                        {
                        curCTDAFunction = Function_Arguments.find(Stages[x]->Entries[y]->CTDA[p]->value.ifunc);
                        if(CTDAFunction.first == eFID)
                            FormIDHandler.CollapseFormID(Stages[x]->Entries[y]->CTDA[p]->value.param1);
                        if(CTDAFunction.second == eFID)
                            FormIDHandler.CollapseFormID(Stages[x]->Entries[y]->CTDA[p]->value.param2);
                        }
                    for(unsigned int p = 0; p < Stages[x]->Entries[y]->SCR_.size(); p++)
                        if(Stages[x]->Entries[y]->SCR_[p]->value.isSCRO)
                            FormIDHandler.CollapseFormID(Stages[x]->Entries[y]->SCR_[p]->value.reference);
                    }
                }

            for(unsigned int x = 0; x < Targets.size(); x++)
                {
                FormIDHandler.CollapseFormID(Targets[x]->QSTA.value.targetId);
                for(unsigned int y = 0; y < Targets[x]->CTDA.size(); y++)
                    {
                    curCTDAFunction = Function_Arguments.find(Targets[x]->CTDA[y]->value.ifunc);
                    if(curCTDAFunction != Function_Arguments.end())
                        {
                        CTDAFunction = curCTDAFunction->second;
                        if(CTDAFunction.first == eFID)
                            FormIDHandler.CollapseFormID(Targets[x]->CTDA[y]->value.param1);
                        if(CTDAFunction.second == eFID)
                            FormIDHandler.CollapseFormID(Targets[x]->CTDA[y]->value.param2);
                        }
                    }
                }
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int CreateListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int DeleteListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        int CreateListX3Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field);
        int DeleteListX3Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        int GetListX2FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field);
        int GetListX3FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListX2Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetListX3Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetListX2ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        unsigned int GetListX3ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void GetListX2Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues);
        void GetListX3Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void * GetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field);
        void * GetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned short FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char *FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue);
        void SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue);
        void SetListX3Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char FieldValue);
        void SetListX3Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char *FieldValue, unsigned int nSize);
        void SetListX3Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, float FieldValue);
        void SetListX3Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned int FieldValue);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eQUST;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);

        bool IsStartEnabled()
            {
            return (DATA.value.flags & fIsStartEnabled) != 0;
            }
        void IsStartEnabled(bool value)
            {
            if(value)
                DATA.value.flags |= fIsStartEnabled;
            else
                DATA.value.flags &= ~fIsStartEnabled;
            }
        bool IsRepeatedTopics()
            {
            return (DATA.value.flags & fIsRepeatedTopics) != 0;
            }
        void IsRepeatedTopics(bool value)
            {
            if(value)
                DATA.value.flags |= fIsRepeatedTopics;
            else
                DATA.value.flags &= ~fIsRepeatedTopics;
            }
        bool IsRepeatedStages()
            {
            return (DATA.value.flags & fIsRepeatedStages) != 0;
            }
        void IsRepeatedStages(bool value)
            {
            if(value)
                DATA.value.flags |= fIsRepeatedStages;
            else
                DATA.value.flags &= ~fIsRepeatedStages;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            DATA.value.flags = Mask;
            }
    };
