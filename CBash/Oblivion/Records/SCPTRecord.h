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

class SCPTRecord : public Record
    {
    private:
        enum scriptTypeTypes
            {
            eObject      = 0x00000000,
            eQuest       = 0x00000001,
            eMagicEffect = 0x00000100
            };

    public:
        StringRecord EDID;
        ReqSubRecord<GENSCHR> SCHR;
        RawRecord SCDA;
        NonNullStringRecord SCTX;
        std::vector<GENVARS *> VARS;
        std::vector<ReqSubRecord<GENSCR_> *> SCR_;

        SCPTRecord(unsigned char *_recData=NULL);
        SCPTRecord(SCPTRecord *srcRecord);
        ~SCPTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsObject();
        void   IsObject(bool value);
        bool   IsQuest();
        void   IsQuest(bool value);
        bool   IsMagicEffect();
        void   IsMagicEffect(bool value);
        bool   IsType(UINT32 Type);
        void   SetType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const SCPTRecord &other) const;
        bool operator !=(const SCPTRecord &other) const;
    };