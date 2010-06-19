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

class SKILRecord : public Record
    {
    private:
        enum SKILRecordFields {
            eEDID = 0x44494445,
            eINDX = 0x58444E49,
            eDESC = 0x43534544,
            eICON = 0x4E4F4349,
            eDATA = 0x41544144,
            eANAM = 0x4D414E41,
            eJNAM = 0x4D414E4A,
            eENAM = 0x4D414E45,
            eMNAM = 0x4D414E4D
            };

        struct SKILINDX
            {
            int skill;
            SKILINDX():skill(26) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("skill = %i\n", skill);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const SKILINDX &other) const
                {
                return (skill == other.skill);
                }
            bool operator !=(const SKILINDX &other) const
                {
                return !(*this == other);
                }
            };

        struct SKILDATA
            {
            int action, attribute;
            unsigned int specialization;
            float use0, use1;
            SKILDATA():action(26), attribute(0), specialization(0),
                use0(1.0f), use1(1.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("action         = %i\n", action);
                    PrintIndent(indentation);
                    printf("attribute      = %i\n", attribute);
                    PrintIndent(indentation);
                    printf("specialization = %u\n", specialization);
                    PrintIndent(indentation);
                    printf("use0           = %f\n", use0);
                    PrintIndent(indentation);
                    printf("use1           = %f\n", use1);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const SKILDATA &other) const
                {
                return (action == other.action && 
                        attribute == other.attribute && 
                        specialization == other.specialization && 
                        AlmostEqual(use0,other.use0,2) && 
                        AlmostEqual(use1,other.use1,2));
                }
            bool operator !=(const SKILDATA &other) const
                {
                return !(*this == other);
                }
            };

    public:
        STRING EDID;
        ReqRecordField<SKILINDX> INDX;
        STRING DESC;
        STRING ICON;
        ReqRecordField<SKILDATA> DATA;
        STRING ANAM;
        STRING JNAM;
        STRING ENAM;
        STRING MNAM;

        SKILRecord(bool newRecord=false):Record(newRecord) {}
        SKILRecord(const unsigned int &newFormID):Record(newFormID) {}
        SKILRecord(SKILRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;

            INDX = srcRecord->INDX;
            DESC = srcRecord->DESC;
            ICON = srcRecord->ICON;
            DATA = srcRecord->DATA;
            ANAM = srcRecord->ANAM;
            JNAM = srcRecord->JNAM;
            ENAM = srcRecord->ENAM;
            MNAM = srcRecord->MNAM;
            }
        ~SKILRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            INDX.Unload();
            DESC.Unload();
            ICON.Unload();
            DATA.Unload();
            ANAM.Unload();
            JNAM.Unload();
            ENAM.Unload();
            MNAM.Unload();
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eSKIL;}
        char * GetStrType() {return "SKIL";}
        int WriteRecord(_FileHandler &SaveHandler);
    };
