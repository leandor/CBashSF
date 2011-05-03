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
#include <vector>

class CONTRecord : public Record
    {
    private:
        #pragma pack(push)
        #pragma pack(1)
        struct CONTDATA
            {
            UINT8   flags;
            FLOAT32 weight;

            CONTDATA();
            ~CONTDATA();

            bool operator ==(const CONTDATA &other) const;
            bool operator !=(const CONTDATA &other) const;
            };
        #pragma pack(pop)

        enum flagsFlags
            {
            fIsRespawn = 0x00000001
            };

    public:
        StringRecord EDID;
        StringRecord FULL;
        OptSubRecord<GENMODEL> MODL;
        OptSimpleSubRecord<FORMID> SCRI;
        std::vector<ReqSubRecord<GENCNTO> *> CNTO;
        ReqSubRecord<CONTDATA> DATA;
        OptSimpleSubRecord<FORMID> SNAM;
        OptSimpleSubRecord<FORMID> QNAM;

        CONTRecord(unsigned char *_recData=NULL);
        CONTRecord(CONTRecord *srcRecord);
        ~CONTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsRespawn();
        void   IsRespawn(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CONTRecord &other) const;
        bool operator !=(const CONTRecord &other) const;
    };