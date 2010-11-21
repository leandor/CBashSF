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
            void Debug(signed long debugLevel, size_t &indentation)
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
            bool operator ==(const ROADPGRR &other) const
                {
                return (AlmostEqual(x,other.x,2) &&
                        AlmostEqual(y,other.y,2) &&
                        AlmostEqual(z,other.z,2));
                }
            bool operator !=(const ROADPGRR &other) const
                {
                return !(*this == other);
                }
            };
    public:
        std::vector<GENPGRP> PGRP;
        std::vector<ROADPGRR> PGRR;

        ROADRecord(bool newRecord=false):Record(newRecord) {}
        ROADRecord(ROADRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eROAD)
                return;

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
        void Debug(signed long debugLevel);
        #endif

        signed long CreateListElement(const unsigned long subField);
        signed long DeleteListElement(const unsigned long subField);
        signed long GetOtherFieldType(const unsigned long Field);
        signed long GetListFieldType(const unsigned long subField, const unsigned long listField);
        unsigned long GetListSize(const unsigned long Field);
        unsigned long GetListArraySize(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void GetListArray(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues);
        void * GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, float FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eROAD;}
        char *GetStrType() {return "ROAD";}
        unsigned long GetParentType() {return eWRLD;}
        signed long WriteRecord(_FileHandler &SaveHandler);
    };
