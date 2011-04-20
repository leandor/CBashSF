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
class PACKRecord : public Record //Package
    {
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENPKDT> PKDT; //PKDT ,, Struct
        OptSubRecord<GENPLDT> PLDT; //PLDT ,, Struct
        OptSubRecord<GENPLD2> PLD2; //PLD2 ,, Struct
        OptSubRecord<GENPSDT> PSDT; //PSDT ,, Struct
        OptSubRecord<GENPTDT> PTDT; //PTDT ,, Struct
        OptSubRecord<GENCTDA> CTDA; //Conditions
        OptSubRecord<GENU8> IDLF; //Flags
        OptSubRecord<GENIDLC> IDLC; //IDLC ,, Struct
        OptSubRecord<GENFLOAT> IDLT; //Idle Timer Setting
        OptSubRecord<GENFID> IDLA; //Animation
        OptSubRecord<GENIDLB> IDLB; //Unused
        OptSubRecord<GENPKED> PKED; //Eat Marker
        OptSubRecord<GENU32> PKE2; //Escort Distance
        OptSubRecord<GENFID> CNAM; //Combat Style
        OptSubRecord<GENFLOAT> PKFD; //Follow - Start Location - Trigger Radius
        OptSubRecord<GENPKPT> PKPT; //PKPT ,, Struct
        OptSubRecord<GENPKW3> PKW3; //PKW3 ,, Struct
        OptSubRecord<GENPTD2> PTD2; //PTD2 ,, Struct
        OptSubRecord<GENPUID> PUID; //Use Item Marker
        OptSubRecord<GENPKAM> PKAM; //Ambush Marker
        OptSubRecord<GENPKDD> PKDD; //PKDD ,, Struct
        OptSubRecord<GENPOBA> POBA; //OnBegin Marker
        OptSubRecord<GENPOEA> POEA; //OnEnd Marker
        OptSubRecord<GENPOCA> POCA; //OnChange Marker

        PACKRecord(unsigned char *_recData=NULL);
        PACKRecord(PACKRecord *srcRecord);
        ~PACKRecord();

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

        bool operator ==(const PACKRecord &other) const;
        bool operator !=(const PACKRecord &other) const;
    };
}