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
class NPC_Record : public Record //Non-Player Character
    {
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<GENACBS> ACBS; //ACBS ,, Struct
        OptSubRecord<GENSNAM> SNAM; //SNAM ,, Struct
        OptSubRecord<GENFID> INAM; //Death item
        OptSubRecord<GENFID> VTCK; //Voice
        OptSubRecord<GENFID> TPLT; //Template
        OptSubRecord<GENFID> RNAM; //Race
        OptSubRecord<GENFID> SPLO; //Actor Effect
        OptSubRecord<GENFID> EITM; //Unarmed Attack Effect
        OptSubRecord<GENU16> EAMT; //Unarmed Attack Animation
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSubRecord<GENFID> SCRI; //Script
        std::vector<FNVCNTO *> CNTO;  //Items
        OptSubRecord<GENAIDT> AIDT; //AI Data
        OptSubRecord<GENFID> PKID; //Package
        OptSubRecord<GENFID> CNAM; //Class
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct
        OptSubRecord<GENDNAM> DNAM; //DNAM ,, Struct
        OptSubRecord<GENFID> PNAM; //Head Part
        OptSubRecord<GENFID> HNAM; //Hair
        OptSubRecord<GENFLOAT> LNAM; //Hair length
        OptSubRecord<GENFID> ENAM; //Eyes
        OptSubRecord<GENHCLR> HCLR; //HCLR ,, Struct
        OptSubRecord<GENFID> ZNAM; //Combat Style
        OptSubRecord<GENU32> NAM4; //Impact Material Type
        OptSubRecord<GENFGGS> FGGS; //FaceGen Geometry-Symmetric
        OptSubRecord<GENU16> NAM5; //Unknown
        OptSubRecord<GENFLOAT> NAM6; //Height
        OptSubRecord<GENFLOAT> NAM7; //Weight

        NPC_Record(unsigned char *_recData=NULL);
        NPC_Record(NPC_Record *srcRecord);
        ~NPC_Record();

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

        bool operator ==(const NPC_Record &other) const;
        bool operator !=(const NPC_Record &other) const;
    };
}