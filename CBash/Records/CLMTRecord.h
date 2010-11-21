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
        enum CLMTSubRecords {
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
            unsigned long weather;
            signed long chance;
            CLMTWLST():weather(0), chance(0){}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
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
            bool operator ==(const CLMTWLST &other) const
                {
                return (weather == other.weather &&
                        chance == other.chance);
                }
            bool operator !=(const CLMTWLST &other) const
                {
                return !(*this == other);
                }
            };

        struct CLMTTNAM
            {
            unsigned char riseBegin, riseEnd, setBegin,
                setEnd, volatility, phaseLength;
            CLMTTNAM():riseBegin(0), riseEnd(0), setBegin(0),
                setEnd(0), volatility(0), phaseLength(0) {}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
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
            bool operator ==(const CLMTTNAM &other) const
                {
                return (riseBegin == other.riseBegin &&
                        riseEnd == other.riseEnd &&
                        setBegin == other.setBegin &&
                        setEnd == other.setEnd &&
                        volatility == other.volatility &&
                        phaseLength == other.phaseLength);
                }
            bool operator !=(const CLMTTNAM &other) const
                {
                return !(*this == other);
                }
            };
    public:
        StringRecord EDID;
        std::vector<CLMTWLST> Weathers;
        InsensitiveStringRecord FNAM;
        InsensitiveStringRecord GNAM;
        OptSubRecord<GENMODEL> MODL;
        ReqSubRecord<CLMTTNAM> TNAM;

        CLMTRecord(bool newRecord=false):Record(newRecord) {}
        CLMTRecord(CLMTRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eCLMT)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            Weathers = srcRecord->Weathers;
            FNAM = srcRecord->FNAM;
            GNAM = srcRecord->GNAM;
            if(srcRecord->MODL.IsLoaded())
                {
                MODL.Load();
                MODL->MODB = srcRecord->MODL->MODB;
                MODL->MODL = srcRecord->MODL->MODL;
                MODL->MODT = srcRecord->MODL->MODT;
                }
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
            MODL.Unload();
            TNAM.Unload();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            for(unsigned long x = 0; x < Weathers.size(); x++)
                op.Accept(Weathers[x].weather);

            return op.Stop();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long CreateListElement(const unsigned long subField);
        signed long DeleteListElement(const unsigned long subField);
        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        unsigned long GetFieldArraySize(const unsigned long Field);
        void GetFieldArray(const unsigned long Field, void **FieldValues);
        signed long GetListFieldType(const unsigned long subField, const unsigned long listField);
        unsigned long GetListSize(const unsigned long Field);
        void * GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, signed long FieldValue);
        void SetField(const unsigned long Field, float FieldValue);
        void SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize);
        void SetField(const unsigned long Field, unsigned char FieldValue);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eCLMT;}
        char *GetStrType() {return "CLMT";}
        signed long WriteRecord(_FileHandler &SaveHandler);
    };
