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
        enum HAIRSubRecords {
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
        StringRecord EDID;
        StringRecord FULL;
        OptSubRecord<GENMODEL> MODL;
        StringRecord ICON;
        ReqSubRecord<GENFLAG> DATA;

        HAIRRecord(bool newRecord=false):Record(newRecord) {}
        HAIRRecord(HAIRRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eHAIR)
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
            ICON = srcRecord->ICON;
            DATA = srcRecord->DATA;
            }
        ~HAIRRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();
            ICON.Unload();
            DATA.Unload();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        unsigned long GetFieldArraySize(const unsigned long Field);
        void GetFieldArray(const unsigned long Field, void **FieldValues);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetField(const unsigned long Field, float FieldValue);
        void SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize);
        void SetField(const unsigned long Field, unsigned char FieldValue);

        signed long DeleteField(const unsigned long Field);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eHAIR;}
        char *GetStrType() {return "HAIR";}
        signed long WriteRecord(_FileHandler &SaveHandler);
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
