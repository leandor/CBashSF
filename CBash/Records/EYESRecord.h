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

class EYESRecord : public Record
    {
    private:
        enum EYESRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eICON = 0x4E4F4349,
            eDATA = 0x41544144
            };
    public:
        enum flagsFlags
            {
            fIsPlayable   = 0x00000001
            };
        STRING EDID;
        STRING FULL;
        STRING ICON;
        ReqRecordField<GENFLAG> DATA;

        EYESRecord(bool newRecord=false):Record(newRecord) {}
        EYESRecord(const unsigned int &newFormID):Record(newFormID) {}
        EYESRecord(EYESRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            ICON = srcRecord->ICON;
            DATA = srcRecord->DATA;
            }
        ~EYESRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            ICON.Unload();
            DATA.Unload();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler) {}
        void CollapseFormIDs(_FormIDHandler &FormIDHandler) {}

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eEYES;}
        char * GetStrType() {return "EYES";}
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
