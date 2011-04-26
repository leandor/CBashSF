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
class CCRDRecord : public FNVRecord //Caravan Card
    {
    private:
        enum suitTypes
            {
            eNone = 0,
            eHearts,
            eSpades,
            eDiamonds,
            eClubs,
            eJoker
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSimpleSubRecord<FORMID> YNAM; //Sound - Pick Up
        OptSimpleSubRecord<FORMID> ZNAM; //Sound - Drop
        StringRecord TX00; //Face High Res Image
        StringRecord TX01; //Back High Res Image
        OptSimpleSubRecord<UINT32> INTV1; //Card Suit
        OptSimpleSubRecord<UINT32> INTV2; //Card Value
        OptSimpleSubRecord<UINT32> DATA; //Value

        CCRDRecord(unsigned char *_recData=NULL);
        CCRDRecord(CCRDRecord *srcRecord);
        ~CCRDRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsHearts();
        void   IsHearts(bool value);
        bool   IsSpades();
        void   IsSpades(bool value);
        bool   IsDiamonds();
        void   IsDiamonds(bool value);
        bool   IsClubs();
        void   IsClubs(bool value);
        bool   IsJoker();
        void   IsJoker(bool value);
        bool   IsType(UINT32 Type, bool Exact=false);
        void   SetType(UINT32 Type);

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

        bool operator ==(const CCRDRecord &other) const;
        bool operator !=(const CCRDRecord &other) const;
    };
}