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

class CLMTRecord : public Record
    {
    private:
        enum CLMTRecordFields {
            eEDID = 0x44494445,
            eWLST = 0x54534C57,
            eFNAM = 0x4D414E46,
            eGNAM = 0x4D414E47,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eTNAM = 0x4D414E54
            };

        struct CLMTWLST
            {
            unsigned int weather;
            int chance;
            CLMTWLST():weather(0), chance(0){}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("weather = %s\n", PrintFormID(weather));
                    PrintIndent(indentation);
                    printf("chance  = %i\n", chance);
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct CLMTTNAM
            {
            unsigned char riseBegin, riseEnd, setBegin,
                setEnd, volatility, phaseLength;
            CLMTTNAM():riseBegin(0), riseEnd(0), setBegin(0),
                setEnd(0), volatility(0), phaseLength(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("riseBegin   = %u\n", riseBegin);
                    PrintIndent(indentation);
                    printf("riseEnd     = %u\n", riseEnd);
                    PrintIndent(indentation);
                    printf("setBegin    = %u\n", setBegin);
                    PrintIndent(indentation);
                    printf("setEnd      = %u\n", setEnd);
                    PrintIndent(indentation);
                    printf("volatility  = %u\n", volatility);
                    PrintIndent(indentation);
                    printf("phaseLength = %u\n", phaseLength);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        STRING EDID;
        std::vector<CLMTWLST> Weathers;
        STRING FNAM;
        STRING GNAM;
        GENMODEL MODL;
        ReqRecordField<CLMTTNAM> TNAM;
        CLMTRecord(bool newRecord=false):Record(newRecord) {}
        CLMTRecord(const unsigned int &newFormID):Record(newFormID) {}
        CLMTRecord(CLMTRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            Weathers = srcRecord->Weathers;
            FNAM = srcRecord->FNAM;
            GNAM = srcRecord->GNAM;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            TNAM = srcRecord->TNAM;
            return;
            }
        ~CLMTRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            Weathers.clear();
            FNAM.Unload();
            GNAM.Unload();
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            TNAM.Unload();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < Weathers.size(); x++)
                FormIDHandler.ExpandFormID(Weathers[x].weather);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < Weathers.size(); x++)
                FormIDHandler.CollapseFormID(Weathers[x].weather);
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
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eCLMT;}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
    };
