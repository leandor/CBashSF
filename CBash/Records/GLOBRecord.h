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

class GLOBRecord : public Record
    {
    private:
        enum GLOBSubRecords {
            eEDID = 0x44494445,
            eFNAM = 0x4D414E46,
            eFLTV = 0x56544C46
            };
        struct GLOBFNAM
            {
            char format;
            GLOBFNAM():format('f') {}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("format = %c\n", format);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const GLOBFNAM &other) const
                {
                return (format == other.format);
                }
            bool operator !=(const GLOBFNAM &other) const
                {
                return !(*this == other);
                }
            };

        struct GLOBFLTV
            {
            float value;
            GLOBFLTV():value(0.0f) {}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("value = %f\n", value);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const GLOBFLTV &other) const
                {
                return (AlmostEqual(value,other.value,2));
                }
            bool operator !=(const GLOBFLTV &other) const
                {
                return !(*this == other);
                }
            };
    public:
        StringRecord EDID;
        ReqSubRecord<GLOBFNAM> FNAM;
        ReqSubRecord<GLOBFLTV> FLTV;

        GLOBRecord(bool newRecord=false):Record(newRecord) {}
        GLOBRecord(GLOBRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eGLOB)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FNAM = srcRecord->FNAM;
            FLTV = srcRecord->FLTV;
            }
        ~GLOBRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FNAM.Unload();
            FLTV.Unload();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        void SetField(const unsigned long Field, char FieldValue);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetField(const unsigned long Field, float FieldValue);

        signed long DeleteField(const unsigned long Field);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eGLOB;}
        char *GetStrType() {return "GLOB";}
        signed long WriteRecord(_FileHandler &SaveHandler);
    };
