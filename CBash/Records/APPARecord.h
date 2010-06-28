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

class APPARecord : public Record
    {
    private:
        enum APPASubRecords {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eSCRI = 0x49524353,
            eDATA = 0x41544144
            };
        #pragma pack(push)
        #pragma pack(1)
        struct APPADATA
            {
            unsigned char apparatus;
            unsigned int value;
            float weight, quality;
            APPADATA():apparatus(0), value(25), weight(1.0f), quality(10.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("apparatus = %u\n", apparatus);
                    PrintIndent(indentation);
                    printf("value     = %u\n", value);
                    PrintIndent(indentation);
                    printf("weight    = %f\n", weight);
                    PrintIndent(indentation);
                    printf("quality   = %f\n", quality);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const APPADATA &other) const
                {
                return (apparatus == other.apparatus && 
                        value == other.value && 
                        AlmostEqual(weight,other.weight,2) && 
                        AlmostEqual(quality,other.quality,2));
                }
            bool operator !=(const APPADATA &other) const
                {
                return !(*this == other);
                }
            };
        #pragma pack(pop)
    public:
        enum eApparatusType
            {
            eMortarPestle = 0,
            eAlembic      = 1,
            eCalcinator   = 2,
            eRetort       = 3
            };
        STRING EDID;
        STRING FULL;
        OptSubRecord<GENMODEL> MODL;
        STRING ICON;
        OptSubRecord<GENFID> SCRI;
        ReqSubRecord<APPADATA> DATA;

        APPARecord(bool newRecord=false):Record(newRecord) {}
        APPARecord(const unsigned int &newFormID):Record(newFormID) {}
        APPARecord(APPARecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            if(srcRecord->MODL.IsLoaded())
                {
                MODL.Load();
                MODL->MODB = srcRecord->MODL->MODB;
                MODL->MODL = srcRecord->MODL->MODL;
                MODL->MODT = srcRecord->MODL->MODT;
                }
            ICON = srcRecord->ICON;
            SCRI = srcRecord->SCRI;
            DATA = srcRecord->DATA;
            return;
            }
        ~APPARecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();
            ICON.Unload();
            SCRI.Unload();
            DATA.Unload();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            if(SCRI.IsLoaded())
                FormIDs.push_back(&SCRI->fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eAPPA;}
        char * GetStrType() {return "APPA";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsMortarPestle()
            {
            return (DATA.value.apparatus == eMortarPestle);
            }
        void IsMortarPestle(bool value)
            {
            if(value)
                DATA.value.apparatus = eMortarPestle;
            else
                DATA.value.apparatus = eAlembic;
            }
        bool IsAlembic()
            {
            return (DATA.value.apparatus == eAlembic);
            }
        void IsAlembic(bool value)
            {
            if(value)
                DATA.value.apparatus = eAlembic;
            else
                DATA.value.apparatus = eMortarPestle;
            }
        bool IsCalcinator()
            {
            return (DATA.value.apparatus == eCalcinator);
            }
        void IsCalcinator(bool value)
            {
            if(value)
                DATA.value.apparatus = eCalcinator;
            else
                DATA.value.apparatus = eMortarPestle;
            }
        bool IsRetort()
            {
            return (DATA.value.apparatus == eRetort);
            }
        void IsRetort(bool value)
            {
            if(value)
                DATA.value.apparatus = eRetort;
            else
                DATA.value.apparatus = eMortarPestle;
            }
        bool IsType(unsigned char Type)
            {
            return (DATA.value.apparatus == Type);
            }
        void SetType(unsigned char Type)
            {
            DATA.value.apparatus = Type;
            }
    };
