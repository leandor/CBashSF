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

class CONTRecord : public Record
    {
    private:
        enum CONTRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eSCRI = 0x49524353,
            eCNTO = 0x4F544E43,
            eDATA = 0x41544144,
            eSNAM = 0x4D414E53,
            eQNAM = 0x4D414E51
            };
        #pragma pack(push)
        #pragma pack(1)
        struct CONTDATA
            {
            unsigned char flags;
            float weight;
            CONTDATA():flags(0), weight(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    printf("weight = %f\n", weight);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CONTDATA &other) const
                {
                return (flags == other.flags && 
                        AlmostEqual(weight,other.weight,2));
                }
            bool operator !=(const CONTDATA &other) const
                {
                return !(*this == other);
                }
            };
        #pragma pack(pop)
    public:
        enum flagsFlags
            {
            fIsRespawn = 0x00000001
            };
        STRING EDID;
        STRING FULL;
        GENMODEL MODL;
        OptRecordField<GENFID> SCRI;
        std::vector<ReqRecordField<GENCNTO> *> CNTO;
        ReqRecordField<CONTDATA> DATA;
        OptRecordField<GENFID> SNAM;
        OptRecordField<GENFID> QNAM;

        CONTRecord(bool newRecord=false):Record(newRecord) {}
        CONTRecord(const unsigned int &newFormID):Record(newFormID) {}
        CONTRecord(CONTRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            SCRI = srcRecord->SCRI;

            CNTO.clear();
            CNTO.resize(srcRecord->CNTO.size());
            for(unsigned int x = 0; x < srcRecord->CNTO.size(); x++)
                {
                CNTO[x] = new ReqRecordField<GENCNTO>;
                *CNTO[x] = *srcRecord->CNTO[x];
                }

            DATA = srcRecord->DATA;
            SNAM = srcRecord->SNAM;
            QNAM = srcRecord->QNAM;
            return;
            }
        ~CONTRecord()
            {
            for(unsigned int x = 0; x < CNTO.size(); x++)
                delete CNTO[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            SCRI.Unload();

            for(unsigned int x = 0; x < CNTO.size(); x++)
                delete CNTO[x];
            CNTO.clear();

            DATA.Unload();
            SNAM.Unload();
            QNAM.Unload();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            if(SCRI.IsLoaded())
                FormIDs.push_back(&SCRI->fid);
            for(unsigned int x = 0; x < CNTO.size(); x++)
                FormIDs.push_back(&CNTO[x]->value.item);
            if(SNAM.IsLoaded())
                FormIDs.push_back(&SNAM->fid);
            if(QNAM.IsLoaded())
                FormIDs.push_back(&QNAM->fid);
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
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eCONT;}
        char * GetStrType() {return "CONT";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsRespawn()
            {
            return (DATA.value.flags & fIsRespawn) != 0;
            }
        void IsRespawn(bool value)
            {
            if(value)
                DATA.value.flags |= fIsRespawn;
            else
                DATA.value.flags &= ~fIsRespawn;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            DATA.value.flags = Mask;
            }
    };
