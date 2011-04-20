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
class ALOCRecord : public Record //Media Location Controller
    {
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        RawRecord NAM1; //Flags and Enums, messily combined
        RawRecord NAM2; //Unknown
        RawRecord NAM3; //Unknown
        OptSubRecord<GENFLOAT> NAM4; //Location Delay
        OptSubRecord<GENU32> NAM5; //Day Start
        OptSubRecord<GENU32> NAM6; //Night Start
        OptSubRecord<GENFLOAT> NAM7; //Retrigger Delay
        OptSubRecord<GENFID> HNAM; //Media Set
        OptSubRecord<GENFID> ZNAM; //Media Set
        OptSubRecord<GENFID> XNAM; //Media Set
        OptSubRecord<GENFID> YNAM; //Media Set
        OptSubRecord<GENFID> LNAM; //Media Set
        OptSubRecord<GENFID> GNAM; //Media Set
        OptSubRecord<GENFID> RNAM; //Conditional Faction
        RawRecord FNAM; //Unknown

        ALOCRecord(unsigned char *_recData=NULL);
        ALOCRecord(ALOCRecord *srcRecord);
        ~ALOCRecord();

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

        bool operator ==(const ALOCRecord &other) const;
        bool operator !=(const ALOCRecord &other) const;
    };
}