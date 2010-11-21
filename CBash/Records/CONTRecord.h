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
        enum CONTSubRecords {
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
            void Debug(signed long debugLevel, size_t &indentation)
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
        StringRecord EDID;
        StringRecord FULL;
        OptSubRecord<GENMODEL> MODL;
        OptSubRecord<GENFID> SCRI;
        std::vector<ReqSubRecord<GENCNTO> *> CNTO;
        ReqSubRecord<CONTDATA> DATA;
        OptSubRecord<GENFID> SNAM;
        OptSubRecord<GENFID> QNAM;

        CONTRecord(bool newRecord=false):Record(newRecord) {}
        CONTRecord(CONTRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eCONT)
                return;

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

            CNTO.clear();
            CNTO.resize(srcRecord->CNTO.size());
            for(unsigned long x = 0; x < srcRecord->CNTO.size(); x++)
                {
                CNTO[x] = new ReqSubRecord<GENCNTO>;
                *CNTO[x] = *srcRecord->CNTO[x];
                }

            DATA = srcRecord->DATA;
            SNAM = srcRecord->SNAM;
            QNAM = srcRecord->QNAM;
            return;
            }
        ~CONTRecord()
            {
            for(unsigned long x = 0; x < CNTO.size(); x++)
                delete CNTO[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();
            SCRI.Unload();

            for(unsigned long x = 0; x < CNTO.size(); x++)
                delete CNTO[x];
            CNTO.clear();

            DATA.Unload();
            SNAM.Unload();
            QNAM.Unload();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            if(SCRI.IsLoaded())
                op.Accept(SCRI->fid);
            for(unsigned long x = 0; x < CNTO.size(); x++)
                op.Accept(CNTO[x]->value.item);
            if(SNAM.IsLoaded())
                op.Accept(SNAM->fid);
            if(QNAM.IsLoaded())
                op.Accept(QNAM->fid);

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
        void SetField(const unsigned long Field, float FieldValue);
        void SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize);
        void SetOtherField(const unsigned long Field, unsigned long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, signed long FieldValue);
        void SetField(const unsigned long Field, unsigned char FieldValue);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eCONT;}
        char *GetStrType() {return "CONT";}
        signed long WriteRecord(_FileHandler &SaveHandler);
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
