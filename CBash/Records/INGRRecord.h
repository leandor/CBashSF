# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#pragma once
#include "..\Common.h"
#include "..\BaseRecord.h"
#include <vector>

class INGRRecord : public Record
    {
    private:
        enum INGRRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eSCRI = 0x49524353,
            eDATA = 0x41544144,
            eENIT = 0x54494E45,

            eEFID = 0x44494645,
            eEFIT = 0x54494645,
            eSCIT = 0x54494353
            };
    public:
        enum flagsFlags
            {
            fIsNoAutoCalc = 0x00000001,
            fIsFood       = 0x00000002
            };
        STRING EDID;
        STRING FULL;
        GENMODEL MODL;
        STRING ICON;
        OptRecordField<GENFID> SCRI;
        ReqRecordField<GENWEIGHT> DATA;
        ReqRecordField<GENENIT> ENIT;
        std::vector<GENEffect *> Effects;

        INGRRecord(bool newRecord=false):Record(newRecord) {}
        INGRRecord(const unsigned int &newFormID):Record(newFormID) {}
        INGRRecord(INGRRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            ICON = srcRecord->ICON;
            SCRI = srcRecord->SCRI;
            DATA = srcRecord->DATA;
            ENIT = srcRecord->ENIT;
            Effects.clear();
            Effects.resize(srcRecord->Effects.size());
            for(unsigned int x = 0; x < srcRecord->Effects.size(); x++)
                {
                Effects[x] = new GENEffect;
                Effects[x]->EFID = srcRecord->Effects[x]->EFID;
                Effects[x]->EFIT = srcRecord->Effects[x]->EFIT;
                Effects[x]->SCIT = srcRecord->Effects[x]->SCIT;
                Effects[x]->FULL = srcRecord->Effects[x]->FULL;
                }
            return;
            }
        ~INGRRecord()
            {
            for(unsigned int x = 0; x < Effects.size(); x++)
                delete Effects[x];
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(SCRI.IsLoaded())
                FormIDHandler.ExpandFormID(SCRI->fid);
            for(unsigned int x = 0; x < Effects.size(); x++)
                if(Effects[x]->SCIT.IsLoaded())
                    FormIDHandler.ExpandFormID(Effects[x]->SCIT->script);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(SCRI.IsLoaded())
                FormIDHandler.CollapseFormID(SCRI->fid);
            for(unsigned int x = 0; x < Effects.size(); x++)
                if(Effects[x]->SCIT.IsLoaded())
                    FormIDHandler.CollapseFormID(Effects[x]->SCIT->script);
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
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eINGR;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
        bool IsNoAutoCalc()
            {
            return (ENIT.value.flags & fIsNoAutoCalc) != 0;
            }
        void IsNoAutoCalc(bool value)
            {
            if(value)
                ENIT.value.flags |= fIsNoAutoCalc;
            else
                ENIT.value.flags &= ~fIsNoAutoCalc;
            }
        bool IsFood()
            {
            return (ENIT.value.flags & fIsFood) != 0;
            }
        void IsFood(bool value)
            {
            if(value)
                ENIT.value.flags |= fIsFood;
            else
                ENIT.value.flags &= ~fIsFood;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (ENIT.value.flags & Mask) == Mask;
            else
                return (ENIT.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            ENIT.value.flags = Mask;
            }
    };
