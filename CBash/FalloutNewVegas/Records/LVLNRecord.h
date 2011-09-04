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
class LVLNRecord : public FNVRecord //Leveled NPC
    {
    private:
        enum flagsFlags
            {
            fCalcFromAllLevels = 0x00000001,
            fCalcForEachItem   = 0x00000002,
            fUseAll            = 0x00000004
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        ReqSimpleSubRecord<UINT8> LVLD; //Chance none
        ReqSimpleSubRecord<UINT8> LVLF; //Flags
        UnorderedSparseArray<FNVLVLO *> Entries; //Leveled List Entries
        OptSubRecord<FNVMODEL> MODL; //Model

        LVLNRecord(unsigned char *_recData=NULL);
        LVLNRecord(LVLNRecord *srcRecord);
        ~LVLNRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsCalcFromAllLevels();
        void   IsCalcFromAllLevels(bool value);
        bool   IsCalcForEachItem();
        void   IsCalcForEachItem(bool value);
        bool   IsUseAll();
        void   IsUseAll(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const LVLNRecord &other) const;
        bool operator !=(const LVLNRecord &other) const;
        bool equals(Record *other);
    };
}