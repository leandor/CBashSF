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
class IMADRecord : public FNVRecord //Image Space Modifier
    {
    public:
        StringRecord EDID; //Editor ID
        RawRecord DNAM; //Unknown
        RawRecord BNAM; //Unknown
        RawRecord VNAM; //Unknown
        RawRecord TNAM; //Unknown
        RawRecord NAM3; //Unknown
        RawRecord RNAM; //Unknown
        RawRecord SNAM; //Unknown
        RawRecord UNAM; //Unknown
        RawRecord NAM1; //Unknown
        RawRecord NAM2; //Unknown
        RawRecord WNAM; //Unknown
        RawRecord XNAM; //Unknown
        RawRecord YNAM; //Unknown
        RawRecord NAM4; //Unknown
        RawRecord _00_IAD; //Unknown
        RawRecord _40_IAD; //Unknown
        RawRecord _01_IAD; //Unknown
        RawRecord _41_IAD; //Unknown
        RawRecord _02_IAD; //Unknown
        RawRecord _42_IAD; //Unknown
        RawRecord _03_IAD; //Unknown
        RawRecord _43_IAD; //Unknown
        RawRecord _04_IAD; //Unknown
        RawRecord _44_IAD; //Unknown
        RawRecord _05_IAD; //Unknown
        RawRecord _45_IAD; //Unknown
        RawRecord _06_IAD; //Unknown
        RawRecord _46_IAD; //Unknown
        RawRecord _07_IAD; //Unknown
        RawRecord _47_IAD; //Unknown
        RawRecord _08_IAD; //Unknown
        RawRecord _48_IAD; //Unknown
        RawRecord _09_IAD; //Unknown
        RawRecord _49_IAD; //Unknown
        RawRecord _0A_IAD; //Unknown
        RawRecord _4A_IAD; //Unknown
        RawRecord _0B_IAD; //Unknown
        RawRecord _4B_IAD; //Unknown
        RawRecord _0C_IAD; //Unknown
        RawRecord _4C_IAD; //Unknown
        RawRecord _0D_IAD; //Unknown
        RawRecord _4D_IAD; //Unknown
        RawRecord _0E_IAD; //Unknown
        RawRecord _4E_IAD; //Unknown
        RawRecord _0F_IAD; //Unknown
        RawRecord _4F_IAD; //Unknown
        RawRecord _10_IAD; //Unknown
        RawRecord _50_IAD; //Unknown
        RawRecord _11_IAD; //Unknown
        RawRecord _51_IAD; //Unknown
        RawRecord _12_IAD; //Unknown
        RawRecord _52_IAD; //Unknown
        RawRecord _13_IAD; //Unknown
        RawRecord _53_IAD; //Unknown
        RawRecord _14_IAD; //Unknown
        RawRecord _54_IAD; //Unknown
        OptSimpleSubRecord<FORMID> RDSD; //Sound - Intro
        OptSimpleSubRecord<FORMID> RDSI; //Sound - Outro

        IMADRecord(unsigned char *_recData=NULL);
        IMADRecord(IMADRecord *srcRecord);
        ~IMADRecord();

        bool   VisitFormIDs(FormIDOp &op);

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

        bool operator ==(const IMADRecord &other) const;
        bool operator !=(const IMADRecord &other) const;
    };
}