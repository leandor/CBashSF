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
class NAVIRecord : public FNVRecord //Navigation Mesh Info Map
    {
    private:
        //This subrecord uses a very non-standard format
        //The details of unknown2 seem to vary widely based on the contents of unknown1
        //Normally, it would be expected for unknown2 to be a separate chunk with varying sig's
        struct NAVINVMI
            {
            UINT8   unknown1[4];
            FORMID  mesh, location;
            SINT16  xGrid, yGrid;
            UINT8ARRAY unknown2;
            UINT32  unknown2Size;

            NAVINVMI();
            ~NAVINVMI();

            bool Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos);
            void Write(FileWriter &writer);

            NAVINVMI& operator = (const NAVINVMI &rhs);
            bool operator ==(const NAVINVMI &other) const;
            bool operator !=(const NAVINVMI &other) const;
            };

        //This subrecord uses a very non-standard format
        //It combines a formid and several arrays of formids into a single chunk
        //Normally, it would be expected for the arrays to be in separate chunks
        struct NAVINVCI
            {
            FORMID  unknown1;
            std::vector<FORMID> unknown2;
            std::vector<FORMID> unknown3;
            std::vector<FORMID> doors;

            NAVINVCI();
            ~NAVINVCI();

            bool Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos);
            void Write(FileWriter &writer);

            bool operator ==(const NAVINVCI &other) const;
            bool operator !=(const NAVINVCI &other) const;
            };

    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<UINT32> NVER; //Version
        UnorderedSparseArray<NAVINVMI *> NVMI; //Unknown
        UnorderedSparseArray<NAVINVCI *> NVCI; //Unknown

        NAVIRecord(unsigned char *_recData=NULL);
        NAVIRecord(NAVIRecord *srcRecord);
        ~NAVIRecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const NAVIRecord &other) const;
        bool operator !=(const NAVIRecord &other) const;
    };
}