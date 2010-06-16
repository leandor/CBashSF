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

class SCPTRecord : public Record
    {
    private:
        enum SCPTRecordFields {
            eEDID = 0x44494445,
            eSCHR = 0x52484353,
            eSCDA = 0x41444353,
            eSCTX = 0x58544353,
            eSCVR = 0x52564353,
            eSLSD = 0x44534C53,
            eSCRV = 0x56524353,
            eSCRO = 0x4F524353
            };
        struct SCPTSLSD
            {
            unsigned int index;
            unsigned char unused1[12], flags, unused2[7];
            SCPTSLSD():index(0), flags(0)
                {
                memset(&unused1[0], 0, sizeof(unused1));
                memset(&unused2[0], 0, sizeof(unused2));
                }
            bool operator ==(const SCPTSLSD &other) const
                {
                return (index == other.index && 
                        flags == other.flags);
                }
            bool operator !=(const SCPTSLSD &other) const
                {
                return !(*this == other);
                }
            };

        struct SCPTVARS
            {
            ReqRecordField<SCPTSLSD> SLSD;
            STRING SCVR;
            bool operator ==(const SCPTVARS &other) const
                {
                return (SLSD == other.SLSD && 
                        SCVR == other.SCVR);
                }
            bool operator !=(const SCPTVARS &other) const
                {
                return !(*this == other);
                }
            enum flagsFlags
                {
                fIsLongOrShort = 0x00000001
                };
            bool IsLongOrShort()
                {
                return (SLSD.value.flags & fIsLongOrShort) != 0;
                }
            void IsLongOrShort(bool value)
                {
                if(value)
                    SLSD.value.flags |= fIsLongOrShort;
                else
                    SLSD.value.flags &= ~fIsLongOrShort;
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("index       = %u\n", SLSD.value.index);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1     = ");
                        for(int m = 0; m < 12; m++)
                            printf("%02X", SLSD.value.unused1[m]);
                        printf("\n");
                        }
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags       = %u\n", SLSD.value.flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2     = ");
                        for(int m = 0; m < 7; m++)
                            printf("%02X", SLSD.value.unused2[m]);
                        printf("\n");
                        }
                    PrintIndent(indentation);
                    if(IsLongOrShort())
                        printf("SCVR (LorS) = %s\n", SCVR.value);
                    else
                        printf("SCVR        = %s\n", SCVR.value);
                    indentation -= 2;
                    }
                else
                    printf("      SLSD/SCVR\n");
                }
            #endif
            };

    public:
        STRING EDID;
        ReqRecordField<GENSCHR> SCHR;
        RAWBYTES SCDA;
        NONNULLSTRING SCTX;

        std::vector<SCPTVARS *> VARS;
        std::vector<ReqRecordField<GENSCR_> *> SCR_;
        SCPTRecord(bool newRecord=false):Record(newRecord) {}
        SCPTRecord(const unsigned int &newFormID):Record(newFormID) {}
        SCPTRecord(SCPTRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            SCHR = srcRecord->SCHR;
            SCDA = srcRecord->SCDA;
            SCTX = srcRecord->SCTX;

            VARS.clear();
            VARS.resize(srcRecord->VARS.size());
            for(unsigned int x = 0; x < srcRecord->VARS.size(); x++)
                {
                VARS[x] = new SCPTVARS;
                VARS[x]->SLSD = srcRecord->VARS[x]->SLSD;
                VARS[x]->SCVR = srcRecord->VARS[x]->SCVR;
                }

            SCR_.clear();
            SCR_.resize(srcRecord->SCR_.size());
            for(unsigned int x = 0; x < srcRecord->SCR_.size(); x++)
                {
                SCR_[x] = new ReqRecordField<GENSCR_>;
                *SCR_[x] = *srcRecord->SCR_[x];
                }

            return;
            }
        ~SCPTRecord()
            {
            for(unsigned int x = 0; x < VARS.size(); x++)
                delete VARS[x];
            for(unsigned int x = 0; x < SCR_.size(); x++)
                delete SCR_[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            SCHR.Unload();
            SCDA.Unload();
            SCTX.Unload();
            for(unsigned int x = 0; x < VARS.size(); x++)
                delete VARS[x];
            VARS.clear();
            for(unsigned int x = 0; x < SCR_.size(); x++)
                delete SCR_[x];
            SCR_.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            for(unsigned int x = 0; x < SCR_.size(); x++)
                if(SCR_[x]->value.isSCRO)
                    FormIDs.push_back(&SCR_[x]->value.reference);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eSCPT;}
        char * GetStrType() {return "SCPT";}
        int WriteRecord(_FileHandler &SaveHandler);
    };
