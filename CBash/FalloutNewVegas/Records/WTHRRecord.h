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
class WTHRRecord : public Record //Weather
    {
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENFID> 0IAD; //Sunrise Image Space Modifier
        OptSubRecord<GENFID> 1IAD; //Day Image Space Modifier
        OptSubRecord<GENFID> 2IAD; //Sunset Image Space Modifier
        OptSubRecord<GENFID> 3IAD; //Night Image Space Modifier
        OptSubRecord<GENFID> 4IAD; //Unknown
        OptSubRecord<GENFID> 5IAD; //Unknown
        StringRecord DNAM; //Cloud Textures - Layer 0
        StringRecord CNAM; //Cloud Textures - Layer 1
        StringRecord ANAM; //Cloud Textures - Layer 2
        StringRecord BNAM; //Cloud Textures - Layer 3
        OptSubRecord<GENMODEL> MODL; //Model Filename
        OptSubRecord<GENLNAM> LNAM; //Unknown
        OptSubRecord<GENONAM> ONAM; //Cloud Speed
        RawRecord PNAM; //Unused
        OptSubRecord<GENNAM> NAM0; //NAM0 ,, Struct
        OptSubRecord<GENFNAM> FNAM; //FNAM ,, Struct
        OptSubRecord<GENINAM> INAM; //Unused
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct
        OptSubRecord<GENSNAM> SNAM; //SNAM ,, Struct

        WTHRRecord(unsigned char *_recData=NULL);
        WTHRRecord(WTHRRecord *srcRecord);
        ~WTHRRecord();

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

        bool operator ==(const WTHRRecord &other) const;
        bool operator !=(const WTHRRecord &other) const;
    };
}