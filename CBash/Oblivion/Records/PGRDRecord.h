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
class PGRDRecord : public Record
    {
    private:
        //struct PGRDPGRR
        //    {
        //    unsigned short start, end;
        //    PGRDPGRR():start(0), end(0) {}
        //    #ifdef _DEBUG
        //    void Debug(SINT32 debugLevel, size_t &indentation)
        //        {
        //        if(debugLevel > 3)
        //            {
        //            indentation += 2;
        //            PrintIndent(indentation);
        //            printer("start = %u\n", start);
        //            PrintIndent(indentation);
        //            printer("end   = %u\n", end);
        //            indentation -= 2;
        //            }
        //        }
        //    #endif
        //    };

        struct PGRDPGRI
            {
            UINT16  point;
            UINT8   unused1[2];
            FLOAT32 x, y, z;

            PGRDPGRI();
            ~PGRDPGRI();

            bool operator ==(const PGRDPGRI &other) const;
            bool operator !=(const PGRDPGRI &other) const;
            };

        struct PGRDPGRL
            {
            UnorderedPackedArray<UINT32> points;

            PGRDPGRL();
            ~PGRDPGRL();

            void Write(FileWriter &writer);

            bool operator ==(const PGRDPGRL &other) const;
            bool operator !=(const PGRDPGRL &other) const;
            };

    public:
        ReqSimpleSubRecord<UINT16> DATA; //Point Count
        UnorderedPackedArray<GENPGRP> PGRP; //Points
        RawRecord PGAG; //Unknown
        RawRecord PGRR; //UnorderedPackedArray<PGRDPGRR> ? //Point-to-Point Connections
        UnorderedPackedArray<PGRDPGRI> PGRI; //Inter-cell Connections
        UnorderedSparseArray<PGRDPGRL *> PGRL; //Point-to-Reference Mappings

        Record *Parent;

        PGRDRecord(unsigned char *_recData=NULL);
        PGRDRecord(PGRDRecord *srcRecord);
        ~PGRDRecord();

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

        bool operator ==(const PGRDRecord &other) const;
        bool operator !=(const PGRDRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}