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

class HAIRRecord : public Record
    {
    private:
        enum HAIRRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eDATA = 0x41544144
            };
    public:
        enum flagsFlags
            {
            fIsPlayable   = 0x00000001,
            fIsNotMale    = 0x00000002,
            fIsNotFemale  = 0x00000004,
            fIsFixedColor = 0x00000008
            };
        STRING EDID;
        STRING FULL;
        GENMODEL MODL;
        STRING ICON;
        ReqRecordField<GENFLAG> DATA;

        HAIRRecord(bool newRecord=false):Record(newRecord) {}
        HAIRRecord(const unsigned int &newFormID):Record(newFormID) {}
        HAIRRecord(HAIRRecord *srcRecord):Record(true)
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
            DATA = srcRecord->DATA;
            }
        ~HAIRRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            ICON.Unload();
            DATA.Unload();
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
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eHAIR;}
        char * GetStrType() {return "HAIR";}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
        bool IsPlayable()
            {
            return (DATA.value.flags & fIsPlayable) != 0;
            }
        void IsPlayable(bool value)
            {
            if(value)
                DATA.value.flags |= fIsPlayable;
            else
                DATA.value.flags &= ~fIsPlayable;
            }
        bool IsNotMale()
            {
            return (DATA.value.flags & fIsNotMale) != 0;
            }
        void IsNotMale(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNotMale;
            else
                DATA.value.flags &= ~fIsNotMale;
            }
        bool IsMale()
            {
            return !IsNotMale();
            }
        void IsMale(bool value)
            {
            if(value)
                IsNotMale(false);
            else
                IsNotMale(true);
            }
        bool IsNotFemale()
            {
            return (DATA.value.flags & fIsNotFemale) != 0;
            }
        void IsNotFemale(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNotFemale;
            else
                DATA.value.flags &= ~fIsNotFemale;
            }
        bool IsFemale()
            {
            return !IsNotFemale();
            }
        void IsFemale(bool value)
            {
            if(value)
                IsNotFemale(false);
            else
                IsNotFemale(true);
            }
        bool IsFixedColor()
            {
            return (DATA.value.flags & fIsFixedColor) != 0;
            }
        void IsFixedColor(bool value)
            {
            if(value)
                DATA.value.flags |= fIsFixedColor;
            else
                DATA.value.flags &= ~fIsFixedColor;
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
