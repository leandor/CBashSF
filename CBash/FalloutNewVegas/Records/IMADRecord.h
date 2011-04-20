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
class IMADRecord : public Record //Image Space Modifier
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
        RawRecord _00_; //Unknown
        RawRecord _40_; //Unknown
        RawRecord _01_; //Unknown
        RawRecord _41_; //Unknown
        RawRecord _02_; //Unknown
        RawRecord _42_; //Unknown
        RawRecord _03_; //Unknown
        RawRecord _43_; //Unknown
        RawRecord _04_; //Unknown
        RawRecord _44_; //Unknown
        RawRecord _05_; //Unknown
        RawRecord _45_; //Unknown
        RawRecord _06_; //Unknown
        RawRecord _46_; //Unknown
        RawRecord _07_; //Unknown
        RawRecord _47_; //Unknown
        RawRecord _08_; //Unknown
        RawRecord _48_; //Unknown
        RawRecord _09_; //Unknown
        RawRecord _49_; //Unknown
        RawRecord _0A_; //Unknown
        RawRecord _4A_; //Unknown
        RawRecord _0B_; //Unknown
        RawRecord _4B_; //Unknown
        RawRecord _0C_; //Unknown
        RawRecord _4C_; //Unknown
        RawRecord _0D_; //Unknown
        RawRecord _4D_; //Unknown
        RawRecord _0E_; //Unknown
        RawRecord _4E_; //Unknown
        RawRecord _0F_; //Unknown
        RawRecord _4F_; //Unknown
        RawRecord _10_; //Unknown
        RawRecord _50_; //Unknown
        RawRecord _11_; //Unknown
        RawRecord _51_; //Unknown
        RawRecord _12_; //Unknown
        RawRecord _52_; //Unknown
        RawRecord _13_; //Unknown
        RawRecord _53_; //Unknown
        RawRecord _14_; //Unknown
        RawRecord _54_; //Unknown
        OptSubRecord<GENFID> RDSD; //Sound - Intro
        OptSubRecord<GENFID> RDSI; //Sound - Outro

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