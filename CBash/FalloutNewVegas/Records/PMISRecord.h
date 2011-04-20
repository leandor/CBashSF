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
class PMISRecord : public Record //Placed Missile
    {
    private:
        enum xespFlags
            {
            fIsOppositeParent = 0x00000001,
            fIsPopIn          = 0x00000002
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENFID> NAME; //Base
        OptSubRecord<GENFID> XEZN; //Encounter Zone
        RawRecord XRGD; //Ragdoll Data
        RawRecord XRGB; //Ragdoll Biped Data
        OptSubRecord<GENPATROL> Patrol; //Patrol Data
        OptSubRecord<FNVXOWN> Ownership; //Owner
        OptSubRecord<GENS32> XCNT; //Count
        OptSubRecord<GENFLOAT> XRDS; //Radius
        OptSubRecord<GENFLOAT> XHLP; //Health
        std::vector<ReqSubRecord<GENXPWR> *> Reflections; //Reflected/Refracted By
        std::vector<ReqSubRecord<GENXDCR> *> Decals; //Linked Decals
        OptSubRecord<GENFID> XLKR; //Linked Reference
        OptSubRecord<GENXCLP> XCLP; //Linked Reference Color
        OptSubRecord<GENACTPARENT> ActivateParents; //Activate Parents
        StringRecord XATO; //Activation Prompt
        OptSubRecord<GENXESP> XESP; //Enable Parent
        OptSubRecord<GENFID> XEMI; //Emittance
        OptSubRecord<GENFID> XMBR; //MultiBound Reference
        //OptSubRecord<GENXIBS> XIBS; //Ignored By Sandbox (Empty)
        OptSubRecord<GENXSCL> XSCL; //Scale
        OptSubRecord<GENPOSDATA> DATA; //Position/Rotation

        PMISRecord(unsigned char *_recData=NULL);
        PMISRecord(PMISRecord *srcRecord);
        ~PMISRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsOppositeParent();
        void   IsOppositeParent(bool value);
        bool   IsPopIn();
        void   IsPopIn(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

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

        bool operator ==(const PMISRecord &other) const;
        bool operator !=(const PMISRecord &other) const;
    };
}