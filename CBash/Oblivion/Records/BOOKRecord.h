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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace Ob
{
class BOOKRecord : public Record //Book
    {
    private:
        #pragma pack(push)
        #pragma pack(2)
        struct BOOKDATA
            {
            UINT8   flags;
            SINT8   teaches;
            UINT32  value;
            FLOAT32 weight;

            BOOKDATA();
            ~BOOKDATA();

            bool operator ==(const BOOKDATA &other) const;
            bool operator !=(const BOOKDATA &other) const;
            };
        #pragma pack(pop)

        enum flagsFlags
            {
            fIsScroll = 0x00000001,
            fIsFixed  = 0x00000002
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<GENMODEL> MODL; //Model
        StringRecord ICON; //Large Icon Filename
        StringRecord DESC; //Description
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSimpleSubRecord<FORMID> ENAM; //Enchantment
        OptSimpleSubRecord<UINT16> ANAM; //Enchantment Points
        ReqSubRecord<BOOKDATA> DATA; //Data

        BOOKRecord(unsigned char *_recData=NULL);
        BOOKRecord(BOOKRecord *srcRecord);
        ~BOOKRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsScroll();
        void   IsScroll(bool value);
        bool   IsFixed();
        void   IsFixed(bool value);
        bool   IsCantBeTaken();
        void   IsCantBeTaken(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const BOOKRecord &other) const;
        bool operator !=(const BOOKRecord &other) const;
        bool equals(Record *other);
    };
}