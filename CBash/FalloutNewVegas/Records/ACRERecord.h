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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class ACRERecord : public FNVRecord //Placed Creature
    {
    private:
        enum xespFlags
            {
            fIsOppositeParent = 0x00000001,
            fIsPopIn          = 0x00000002
            };
    public:
        StringRecord EDID; //Editor ID
        ReqSimpleSubRecord<FORMID> NAME; //Base
        OptSimpleSubRecord<FORMID> XEZN; //Encounter Zone
        RawRecord XRGD; //Ragdoll Data
        RawRecord XRGB; //Ragdoll Biped Data
        OptSubRecord<GENPATROL> Patrol; //Patrol Data
        OptSimpleSubRecord<SINT32> XLCM; //Level Modifier
        OptSubRecord<FNVXOWN> Ownership; //Owner
        OptSimpleSubRecord<FORMID> XMRC; //Merchant Container
        OptSimpleSubRecord<SINT32> XCNT; //Count
        OptSimpleFloatSubRecord<flt_0> XRDS; //Radius
        OptSimpleFloatSubRecord<flt_0> XHLP; //Health
        UnorderedSparseArray<GENXDCR *> XDCR; //Linked Decals
        OptSimpleSubRecord<FORMID> XLKR; //Linked Reference
        OptSubRecord<GENXCLP> XCLP; //Linked Reference Color
        OptSubRecord<GENACTPARENT> ActivateParents; //Activate Parents
        StringRecord XATO; //Activation Prompt
        OptSubRecord<GENXESP> XESP; //Enable Parent
        OptSimpleSubRecord<FORMID> XEMI; //Emittance
        OptSimpleSubRecord<FORMID> XMBR; //MultiBound Reference
        OptSimpleSubRecord<UINT8> XIBS; //Ignored By Sandbox (Empty, boolean, if != 0, write empty)
        OptSimpleFloatSubRecord<flt_1> XSCL; //Scale
        ReqSubRecord<GENPOSDATA> DATA; //Position/Rotation

        Record *Parent;

        ACRERecord(unsigned char *_recData=NULL);
        ACRERecord(ACRERecord *srcRecord);
        ~ACRERecord();

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

        UINT32 GetType();
        STRING GetStrType();
        Record * GetParent();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const ACRERecord &other) const;
        bool operator !=(const ACRERecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}