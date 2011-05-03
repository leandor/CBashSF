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
class DOORRecord : public FNVRecord //Door
    {
    private:
        enum flagsFlags
            {
            fIsAutomatic   = 0x00000002,
            fIsHidden      = 0x00000004,
            fIsMinimalUse  = 0x00000008,
            fIsSlidingDoor = 0x00000010
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSimpleSubRecord<FORMID> SNAM; //Sound - Open
        OptSimpleSubRecord<FORMID> ANAM; //Sound - Close
        OptSimpleSubRecord<FORMID> BNAM; //Sound - Looping
        OptSimpleSubRecord<UINT8> FNAM; //Flags

        DOORRecord(unsigned char *_recData=NULL);
        DOORRecord(DOORRecord *srcRecord);
        ~DOORRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsAutomatic();
        void   IsAutomatic(bool value);
        bool   IsHidden();
        void   IsHidden(bool value);
        bool   IsMinimalUse();
        void   IsMinimalUse(bool value);
        bool   IsSlidingDoor();
        void   IsSlidingDoor(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const DOORRecord &other) const;
        bool operator !=(const DOORRecord &other) const;
    };
}