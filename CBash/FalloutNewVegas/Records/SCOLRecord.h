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
class SCOLRecord : public FNVRecord //Static Collection
    {
    private:
        struct SCOLDATA //Placement
            {
            FLOAT32 posX, posY, posZ, rotX, rotY, rotZ, scale;

            SCOLDATA();
            ~SCOLDATA();

            bool operator ==(const SCOLDATA &other) const;
            bool operator !=(const SCOLDATA &other) const;
            };

        struct SCOLPart //Part
            {
            ReqSimpleSubRecord<FORMID> ONAM; //Static
            UnorderedPackedArray<SCOLDATA> DATA; //Placements

            void Write(FileWriter &writer);

            bool operator ==(const SCOLPart &other) const;
            bool operator !=(const SCOLPart &other) const;
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        OptSubRecord<FNVMODEL> MODL; //Model
        UnorderedSparseArray<SCOLPart *> Parts; //Parts

        SCOLRecord(unsigned char *_recData=NULL);
        SCOLRecord(SCOLRecord *srcRecord);
        ~SCOLRecord();

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

        bool operator ==(const SCOLRecord &other) const;
        bool operator !=(const SCOLRecord &other) const;
        bool equals(Record *other);
    };
}