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

class ROADRecord : public Record
    {
    private:
        enum ROADSubrecords {
            ePGRP = 0x50524750,
            ePGRR = 0x52524750
            };
        struct ROADPGRR
            {
            float x, y, z;
            ROADPGRR():x(0.0f), y(0.0f), z(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("x = %f\n", x);
                    PrintIndent(indentation);
                    printf("y = %f\n", y);
                    PrintIndent(indentation);
                    printf("z = %f\n", z);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        std::vector<GENPGRP> PGRP;
        std::vector<ROADPGRR> PGRR;

        ROADRecord(bool newRecord=false):Record(newRecord) {}
        ROADRecord(const unsigned int &newFormID):Record(newFormID) {}
        ROADRecord(ROADRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            PGRP = srcRecord->PGRP;
            PGRR = srcRecord->PGRR;
            return;
            }
        ~ROADRecord() {}
        void Unload()
            {
            IsLoaded(false);
            PGRP.clear();
            PGRR.clear();
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eROAD;}
        char * GetStrType() {return "ROAD";}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
    };
