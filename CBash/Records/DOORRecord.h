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

class DOORRecord : public Record
    {
    private:
        enum DOORRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eSCRI = 0x49524353,
            eSNAM = 0x4D414E53,
            eANAM = 0x4D414E41,
            eBNAM = 0x4D414E42,
            eFNAM = 0x4D414E46,
            eTNAM = 0x4D414E54

            };
    public:
        enum flagsFlags
            {
            fIsOblivionGate = 0x00000001,
            fIsAutomatic    = 0x00000002,
            fIsHidden       = 0x00000004,
            fIsMinimalUse   = 0x00000008
            };
        STRING EDID;
        STRING FULL;
        OptRecordField<GENMODEL> MODL;
        OptRecordField<GENFID> SCRI;
        OptRecordField<GENFID> SNAM;
        OptRecordField<GENFID> ANAM;
        OptRecordField<GENFID> BNAM;
        ReqRecordField<GENFLAG> FNAM;
        std::vector<unsigned int *> TNAM;
        DOORRecord(bool newRecord=false):Record(newRecord) {}
        DOORRecord(const unsigned int &newFormID):Record(newFormID) {}
        DOORRecord(DOORRecord *srcRecord):Record(true)
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
            SNAM = srcRecord->SNAM;
            ANAM = srcRecord->ANAM;
            BNAM = srcRecord->BNAM;
            FNAM = srcRecord->FNAM;
            TNAM.clear();
            TNAM.resize(srcRecord->TNAM.size());
            for(unsigned int x = 0; x < srcRecord->TNAM.size(); x++)
                TNAM[x] = new unsigned int(*srcRecord->TNAM[x]);
            return;
            }
        ~DOORRecord()
            {
            for(unsigned int x = 0; x < TNAM.size(); x++)
                delete TNAM[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();
            SCRI.Unload();
            SNAM.Unload();
            ANAM.Unload();
            BNAM.Unload();
            FNAM.Unload();
            for(unsigned int x = 0; x < TNAM.size(); x++)
                delete TNAM[x];
            TNAM.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            if(SCRI.IsLoaded())
                FormIDs.push_back(&SCRI->fid);
            if(SNAM.IsLoaded())
                FormIDs.push_back(&SNAM->fid);
            if(ANAM.IsLoaded())
                FormIDs.push_back(&ANAM->fid);
            if(BNAM.IsLoaded())
                FormIDs.push_back(&BNAM->fid);
            for(unsigned int x = 0; x < TNAM.size(); x++)
                FormIDs.push_back(TNAM[x]);
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
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eDOOR;}
        char * GetStrType() {return "DOOR";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsOblivionGate()
            {
            return (FNAM.value.flags & fIsOblivionGate) != 0;
            }
        void IsOblivionGate(bool value)
            {
            if(value)
                FNAM.value.flags |= fIsOblivionGate;
            else
                FNAM.value.flags &= ~fIsOblivionGate;
            }
        bool IsAutomatic()
            {
            return (FNAM.value.flags & fIsAutomatic) != 0;
            }
        void IsAutomatic(bool value)
            {
            if(value)
                FNAM.value.flags |= fIsAutomatic;
            else
                FNAM.value.flags &= ~fIsAutomatic;
            }
        bool IsHidden()
            {
            return (FNAM.value.flags & fIsHidden) != 0;
            }
        void IsHidden(bool value)
            {
            if(value)
                FNAM.value.flags |= fIsHidden;
            else
                FNAM.value.flags &= ~fIsHidden;
            }
        bool IsMinimalUse()
            {
            return (FNAM.value.flags & fIsMinimalUse) != 0;
            }
        void IsMinimalUse(bool value)
            {
            if(value)
                FNAM.value.flags |= fIsMinimalUse;
            else
                FNAM.value.flags &= ~fIsMinimalUse;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (FNAM.value.flags & Mask) == Mask;
            else
                return (FNAM.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            FNAM.value.flags = Mask;
            }
    };
