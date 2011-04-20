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
class CREARecord : public Record //Creature
    {
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<GENMODEL> MODL; //Model Filename
        OptSubRecord<GENFID> SPLO; //Actor Effect
        OptSubRecord<GENFID> EITM; //Unarmed Attack Effect
        OptSubRecord<GENU16> EAMT; //Unarmed Attack Animation
        OptSubRecord<GENNIFZ> NIFZ; //Model List
        RawRecord NIFT; //Texture Files Hashes
        OptSubRecord<GENACBS> ACBS; //ACBS ,, Struct
        OptSubRecord<GENSNAM> SNAM; //SNAM ,, Struct
        OptSubRecord<GENFID> INAM; //Death item
        OptSubRecord<GENFID> VTCK; //Voice
        OptSubRecord<GENFID> TPLT; //Template
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSubRecord<GENFID> SCRI; //Script
        OptSubRecord<GENCNTO> CNTO; //Item
        OptSubRecord<GENAIDT> AIDT; //AI Data
        OptSubRecord<GENFID> PKID; //Package
        OptSubRecord<GENKFFZ> KFFZ; //Animations
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct
        OptSubRecord<GENU8> RNAM; //Attack reach
        OptSubRecord<GENFID> ZNAM; //Combat Style
        OptSubRecord<GENFID> PNAM; //Body Part Data
        OptSubRecord<GENFLOAT> TNAM; //Turning Speed
        OptSubRecord<GENFLOAT> BNAM; //Base Scale
        OptSubRecord<GENFLOAT> WNAM; //Foot Weight
        OptSubRecord<GENU32> NAM4; //Impact Material Type
        OptSubRecord<GENU32> NAM5; //Sound Level
        OptSubRecord<GENFID> CSCR; //Inherits Sounds from
        OptSubRecord<GENCSDT> CSDT; //Type
        OptSubRecord<GENFID> CNAM; //Impact Dataset
        OptSubRecord<GENFID> LNAM; //Melee Weapon List

        CREARecord(unsigned char *_recData=NULL);
        CREARecord(CREARecord *srcRecord);
        ~CREARecord();

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

        bool operator ==(const CREARecord &other) const;
        bool operator !=(const CREARecord &other) const;
    };
}