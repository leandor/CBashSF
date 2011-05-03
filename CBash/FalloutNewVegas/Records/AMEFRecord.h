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
class AMEFRecord : public FNVRecord //Ammo Effect
    {
    private:
        struct AMEFDATA
            {
            UINT32  type; //Type
            UINT32  op; //Operation
            FLOAT32 value; //Value

            AMEFDATA();
            ~AMEFDATA();

            bool operator ==(const AMEFDATA &other) const;
            bool operator !=(const AMEFDATA &other) const;
            };

        enum eModType
            {
            eDamage = 0,
            eDR,
            eDT,
            eSpread,
            eCondition,
            eFatigue
            };

        enum eOperationType
            {
            eAdd = 0,
            eMultiply,
            eSubtract
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<AMEFDATA> DATA; //Data

        AMEFRecord(unsigned char *_recData=NULL);
        AMEFRecord(AMEFRecord *srcRecord);
        ~AMEFRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsDamage();
        void   IsDamage(bool value);
        bool   IsDR();
        void   IsDR(bool value);
        bool   IsDT();
        void   IsDT(bool value);
        bool   IsSpread();
        void   IsSpread(bool value);
        bool   IsCondition();
        void   IsCondition(bool value);
        bool   IsFatigue();
        void   IsFatigue(bool value);
        bool   IsModType(UINT32 Type);
        void   SetModType(UINT32 Type);

        bool   IsAdd();
        void   IsAdd(bool value);
        bool   IsMultiply();
        void   IsMultiply(bool value);
        bool   IsSubtract();
        void   IsSubtract(bool value);
        bool   IsOpType(UINT32 Type);
        void   SetOpType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const AMEFRecord &other) const;
        bool operator !=(const AMEFRecord &other) const;
    };
}