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
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class EYESRecord : public FNVRecord //Eyes
    {
    private:
        enum flagsFlags
            {
            fIsPlayable  = 0x00000001,
            fIsNotMale   = 0x00000002,
            fIsNotFemale = 0x00000004
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord ICON; //Texture
        ReqSimpleSubRecord<UINT8> DATA; //Flags

        EYESRecord(unsigned char *_recData=NULL);
        EYESRecord(EYESRecord *srcRecord);
        ~EYESRecord();

        bool   IsPlayable();
        void   IsPlayable(bool value);
        bool   IsNotMale();
        void   IsNotMale(bool value);
        bool   IsMale();
        void   IsMale(bool value);
        bool   IsNotFemale();
        void   IsNotFemale(bool value);
        bool   IsFemale();
        void   IsFemale(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(_FileHandler &SaveHandler);

        bool operator ==(const EYESRecord &other) const;
        bool operator !=(const EYESRecord &other) const;
    };
}