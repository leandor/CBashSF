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
class STATRecord : public FNVRecord //Static
    {
    private:
        enum passthroughTypes
            {
            eNone  = -1,
            eBushA = 0,
            eBushB,
            eBushC,
            eBushD,
            eBushE,
            eBushF,
            eBushG,
            eBushH,
            eBushI,
            eBushJ
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        OptSubRecord<FNVMODEL> MODL; //Model
        SemiOptSimpleSubRecord<SINT8> BRUS; //Passthrough Sound
        OptSimpleSubRecord<FORMID> RNAM; //Sound - Looping/Random

        STATRecord(unsigned char *_recData=NULL);
        STATRecord(STATRecord *srcRecord);
        ~STATRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsSoundNone();
        void   IsSoundNone(bool value);
        bool   IsSoundBushA();
        void   IsSoundBushA(bool value);
        bool   IsSoundBushB();
        void   IsSoundBushB(bool value);
        bool   IsSoundBushC();
        void   IsSoundBushC(bool value);
        bool   IsSoundBushD();
        void   IsSoundBushD(bool value);
        bool   IsSoundBushE();
        void   IsSoundBushE(bool value);
        bool   IsSoundBushF();
        void   IsSoundBushF(bool value);
        bool   IsSoundBushG();
        void   IsSoundBushG(bool value);
        bool   IsSoundBushH();
        void   IsSoundBushH(bool value);
        bool   IsSoundBushI();
        void   IsSoundBushI(bool value);
        bool   IsSoundBushJ();
        void   IsSoundBushJ(bool value);
        bool   IsSoundType(SINT8 Type);
        void   SetSoundType(SINT8 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const STATRecord &other) const;
        bool operator !=(const STATRecord &other) const;
        bool equals(Record *other);
    };
}