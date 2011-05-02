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
class ECZNRecord : public FNVRecord //Encounter Zone
    {
    private:
        struct ECZNDATA // Data
            {
            FORMID  owner; // Owner
            SINT8   rank, minLevel ;// Rank, Minimum Level
            UINT8   flags, unused1; // Flags, Unused

            ECZNDATA();
            ~ECZNDATA();

            bool operator ==(const ECZNDATA &other) const;
            bool operator !=(const ECZNDATA &other) const;
            };

        enum flagsFlags
            {
            fIsNeverResets          = 0x01,
            fIsMatchPCBelowMinLevel = 0x02
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct

        ECZNRecord(unsigned char *_recData=NULL);
        ECZNRecord(ECZNRecord *srcRecord);
        ~ECZNRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNeverResets();
        void   IsNeverResets(bool value);
        bool   IsMatchPCBelowMinLevel();
        void   IsMatchPCBelowMinLevel(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

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

        bool operator ==(const ECZNRecord &other) const;
        bool operator !=(const ECZNRecord &other) const;
    };
}