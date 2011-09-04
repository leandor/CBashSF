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

namespace Ob
{
class CLMTRecord : public Record //Climate
    {
    private:
        struct CLMTWLST
            {
            FORMID  weather;
            SINT32  chance;

            CLMTWLST();
            ~CLMTWLST();

            bool operator ==(const CLMTWLST &other) const;
            bool operator !=(const CLMTWLST &other) const;
            };

        struct CLMTTNAM
            {
            UINT8   riseBegin, riseEnd, setBegin, setEnd, volatility, phaseLength;

            CLMTTNAM();
            ~CLMTTNAM();

            bool operator ==(const CLMTTNAM &other) const;
            bool operator !=(const CLMTTNAM &other) const;
            };

    public:
        StringRecord EDID; //Editor ID
        UnorderedPackedArray<CLMTWLST> Weathers; //Weather Types
        StringRecord FNAM; //Sun Texture
        StringRecord GNAM; //Sun Glare Texture
        OptSubRecord<GENMODEL> MODL; //Model
        ReqSubRecord<CLMTTNAM> TNAM; //Timing

        CLMTRecord(unsigned char *_recData=NULL);
        CLMTRecord(CLMTRecord *srcRecord);
        ~CLMTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CLMTRecord &other) const;
        bool operator !=(const CLMTRecord &other) const;
        bool equals(Record *other);
    };
}