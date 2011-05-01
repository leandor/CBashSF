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
class ALOCRecord : public FNVRecord //Media Location Controller
    {
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        RawRecord NAM1; //Flags and Enums, messily combined
        RawRecord NAM2; //Unknown
        RawRecord NAM3; //Unknown
        OptSimpleSubRecord<FLOAT32> NAM4; //Location Delay
        OptSimpleSubRecord<UINT32> NAM5; //Day Start
        OptSimpleSubRecord<UINT32> NAM6; //Night Start
        OptSimpleSubRecord<FLOAT32> NAM7; //Retrigger Delay
        std::vector<FORMID> HNAM; //Neutral Media Sets
        std::vector<FORMID> ZNAM; //Ally Media Sets
        std::vector<FORMID> XNAM; //Friend Media Sets
        std::vector<FORMID> YNAM; //Enemy Media Sets
        std::vector<FORMID> LNAM; //Location Media Sets
        std::vector<FORMID> GNAM; //Battle Media Sets
        OptSimpleSubRecord<FORMID> RNAM; //Conditional Faction
        RawRecord FNAM; //Unknown

        ALOCRecord(unsigned char *_recData=NULL);
        ALOCRecord(ALOCRecord *srcRecord);
        ~ALOCRecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        //UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const ALOCRecord &other) const;
        bool operator !=(const ALOCRecord &other) const;
    };
}