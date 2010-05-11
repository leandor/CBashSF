# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#pragma once
#include "..\Common.h"
#include "..\BaseRecord.h"
#include <vector>

class INFORecord : public Record
    {
    private:
        enum INFORecordFields {
            eEDID = 0x44494445,
            eDATA = 0x41544144,
            eQSTI = 0x49545351,
            eTPIC = 0x43495054,
            ePNAM = 0x4D414E50,
            eNAME = 0x454D414E,
            eTRDT = 0x54445254,
            eNAM1 = 0x314D414E,
            eNAM2 = 0x324D414E,
            eCTDA = 0x41445443,
            eCTDT = 0x54445443,
            eTCLT = 0x544C4354,
            eTCLF = 0x464C4354,
            eSCHD = 0x44484353,
            eSCHR = 0x52484353,
            eSCDA = 0x41444353,
            eSCTX = 0x58544353,
            eSCRV = 0x56524353,
            eSCRO = 0x4F524353
            };

        struct INFODATA
            {
            unsigned char dialType, flags, unused1;
            INFODATA():dialType(0), flags(0), unused1(0x02) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("dialType = %u\n", dialType);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags    = %u\n", flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1  = %02X\n", unused1);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct INFOTRDT
            {
            unsigned int emotionType;
            int emotionValue;
            unsigned char unused1[4], responseNum, unused2[3];
            INFOTRDT():emotionType(0), emotionValue(0), responseNum(0)
                {
                memset(&unused1, 0x00, 4);
                memset(&unused2, 0x00, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("emotionType  = %u\n", emotionType);
                    PrintIndent(indentation);
                    printf("emotionValue = %i\n", emotionValue);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1      = %02X%02X%02X%02X\n", unused1[0], unused1[1], unused1[2], unused1[3]);
                        }
                    PrintIndent(indentation);
                    printf("responseNum  = %u\n", responseNum);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2      = %02X%02X%02X\n", unused2[0], unused2[1], unused2[2]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
        struct INFOResponse
            {
            ReqRecordField<INFOTRDT> TRDT;
            STRING NAM1;
            STRING NAM2;
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    TRDT.Debug("TRDT", debugLevel, indentation);
                    NAM1.Debug("responseText", debugLevel, indentation);
                    NAM2.Debug("actorNotes", debugLevel, indentation);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        STRING EDID;
        ReqRecordField<INFODATA> DATA;
        ReqRecordField<GENFID> QSTI;
        OptRecordField<GENFID> TPIC;
        OptRecordField<GENFID> PNAM;
        std::vector<unsigned int *> NAME;
        std::vector<INFOResponse *> Responses;
        std::vector<ReqRecordField<GENCTDA> *> CTDA;
        std::vector<unsigned int *> TCLT;
        std::vector<unsigned int *> TCLF;
        //RAWBYTES SCHD;
        ReqRecordField<GENSCHR> SCHR;
        RAWBYTES SCDA;
        NONNULLSTRING SCTX;
        std::vector<ReqRecordField<GENSCR_> *> SCR_;

        INFORecord(bool newRecord=false):Record(newRecord) {}
        INFORecord(const unsigned int &newFormID):Record(newFormID) {}
        INFORecord(INFORecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            DATA = srcRecord->DATA;
            QSTI = srcRecord->QSTI;
            TPIC = srcRecord->TPIC;
            PNAM = srcRecord->PNAM;
            NAME.clear();
            NAME.resize(srcRecord->NAME.size());
            for(unsigned int x = 0; x < srcRecord->NAME.size(); x++)
                NAME[x] = new unsigned int(*srcRecord->NAME[x]);
            Responses.clear();
            Responses.resize(srcRecord->Responses.size());
            for(unsigned int x = 0; x < srcRecord->Responses.size(); x++)
                {
                Responses[x] = new INFOResponse;
                Responses[x]->TRDT = srcRecord->Responses[x]->TRDT;
                Responses[x]->NAM1 = srcRecord->Responses[x]->NAM1;
                Responses[x]->NAM2 = srcRecord->Responses[x]->NAM2;
                }
            CTDA.clear();
            CTDA.resize(srcRecord->CTDA.size());
            for(unsigned int x = 0; x < srcRecord->CTDA.size(); x++)
                {
                CTDA[x] = new ReqRecordField<GENCTDA>;
                *CTDA[x] = *srcRecord->CTDA[x];
                }
            TCLT.clear();
            TCLT.resize(srcRecord->TCLT.size());
            for(unsigned int x = 0; x < srcRecord->TCLT.size(); x++)
                TCLT[x] = new unsigned int(*srcRecord->TCLT[x]);
            TCLF.clear();
            TCLF.resize(srcRecord->TCLF.size());
            for(unsigned int x = 0; x < srcRecord->TCLF.size(); x++)
                TCLF[x] = new unsigned int(*srcRecord->TCLF[x]);
            //SCHD = srcRecord->SCHD;
            SCHR = srcRecord->SCHR;
            SCDA = srcRecord->SCDA;
            SCTX = srcRecord->SCTX;
            SCR_.clear();
            SCR_.resize(srcRecord->SCR_.size());
            for(unsigned int x = 0; x < srcRecord->SCR_.size(); x++)
                {
                SCR_[x] = new ReqRecordField<GENSCR_>;
                *SCR_[x] = *srcRecord->SCR_[x];
                }
            return;
            }
        ~INFORecord()
            {
            for(unsigned int x = 0; x < NAME.size(); x++)
                delete NAME[x];
            for(unsigned int x = 0; x < Responses.size(); x++)
                delete Responses[x];
            for(unsigned int x = 0; x < CTDA.size(); x++)
                delete CTDA[x];
            for(unsigned int x = 0; x < TCLT.size(); x++)
                delete TCLT[x];
            for(unsigned int x = 0; x < TCLF.size(); x++)
                delete TCLF[x];
            for(unsigned int x = 0; x < SCR_.size(); x++)
                delete SCR_[x];
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            std::pair<unsigned int, unsigned int> CTDAFunction;
            std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
            FormIDHandler.ExpandFormID(QSTI.value.fid);
            if(TPIC.IsLoaded())
                FormIDHandler.ExpandFormID(TPIC->fid);
            if(PNAM.IsLoaded())
                FormIDHandler.ExpandFormID(PNAM->fid);
            for(unsigned int x = 0; x < NAME.size(); x++)
                FormIDHandler.ExpandFormID(NAME[x]);
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
            for(unsigned int x = 0; x < TCLT.size(); x++)
                FormIDHandler.ExpandFormID(TCLT[x]);
            for(unsigned int x = 0; x < TCLF.size(); x++)
                FormIDHandler.ExpandFormID(TCLF[x]);
            for(unsigned int x = 0; x < SCR_.size(); x++)
                if(SCR_[x]->value.isSCRO)
                    FormIDHandler.ExpandFormID(SCR_[x]->value.reference);
            }
        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            std::pair<unsigned int, unsigned int> CTDAFunction;
            std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
            FormIDHandler.CollapseFormID(QSTI.value.fid);
            if(TPIC.IsLoaded())
                FormIDHandler.CollapseFormID(TPIC->fid);
            if(PNAM.IsLoaded())
                FormIDHandler.CollapseFormID(PNAM->fid);
            for(unsigned int x = 0; x < NAME.size(); x++)
                FormIDHandler.CollapseFormID(NAME[x]);
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
            for(unsigned int x = 0; x < TCLT.size(); x++)
                FormIDHandler.CollapseFormID(TCLT[x]);
            for(unsigned int x = 0; x < TCLF.size(); x++)
                FormIDHandler.CollapseFormID(TCLF[x]);
            for(unsigned int x = 0; x < SCR_.size(); x++)
                if(SCR_[x]->value.isSCRO)
                    FormIDHandler.CollapseFormID(SCR_[x]->value.reference);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eINFO;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
    };
