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

class FLORRecord : public Record
    {
    private:
        enum FLORSubRecords {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eSCRI = 0x49524353,
            ePFIG = 0x47494650,
            ePFPC = 0x43504650
            };
        struct FLORPFPC
            {
            unsigned char spring, summer, fall, winter;
            FLORPFPC():spring(0), summer(0), fall(0), winter(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("spring = %u\n", spring);
                    PrintIndent(indentation);
                    printf("summer = %u\n", summer);
                    PrintIndent(indentation);
                    printf("fall   = %u\n", fall);
                    PrintIndent(indentation);
                    printf("winter = %u\n", winter);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const FLORPFPC &other) const
                {
                return (spring == other.spring &&
                        summer == other.summer &&
                        fall == other.fall &&
                        winter == other.winter);
                }
            bool operator !=(const FLORPFPC &other) const
                {
                return !(*this == other);
                }
            };
    public:
        STRING EDID;
        STRING FULL;
        OptSubRecord<GENMODEL> MODL;
        OptSubRecord<GENFID> SCRI;
        SubRecord<GENFID> PFIG;
        ReqSubRecord<FLORPFPC> PFPC;

        FLORRecord(bool newRecord=false):Record(newRecord) {}
        FLORRecord(const unsigned int &newFormID):Record(newFormID) {}
        FLORRecord(FLORRecord *srcRecord):Record(true)
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
            SCRI = srcRecord->SCRI;
            PFIG = srcRecord->PFIG;
            PFPC = srcRecord->PFPC;
            return;
            }
        ~FLORRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();
            SCRI.Unload();
            PFIG.Unload();
            PFPC.Unload();
            }

        void VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return;
            if(SCRI.IsLoaded())
                op.Accept(SCRI->fid);
            if(PFIG.IsLoaded())
                op.Accept(PFIG.value.fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(const unsigned int Field, char *FieldValue);
        void SetField(const unsigned int Field, float FieldValue);
        void SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(const unsigned int Field, unsigned int FieldValue);
        void SetField(const unsigned int Field, unsigned char FieldValue);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eFLOR;}
        char * GetStrType() {return "FLOR";}
        int WriteRecord(_FileHandler &SaveHandler);
    };
