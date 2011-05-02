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
        OptSimpleSubRecord<SINT8> BRUS; //Passthrough Sound
        OptSimpleSubRecord<FORMID> RNAM; //Sound - Looping/Random

        STATRecord(unsigned char *_recData=NULL);
        STATRecord(STATRecord *srcRecord);
        ~STATRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsBushA();
        void   IsBushA(bool value);
        bool   IsBushB();
        void   IsBushB(bool value);
        bool   IsBushC();
        void   IsBushC(bool value);
        bool   IsBushD();
        void   IsBushD(bool value);
        bool   IsBushE();
        void   IsBushE(bool value);
        bool   IsBushF();
        void   IsBushF(bool value);
        bool   IsBushG();
        void   IsBushG(bool value);
        bool   IsBushH();
        void   IsBushH(bool value);
        bool   IsBushI();
        void   IsBushI(bool value);
        bool   IsBushJ();
        void   IsBushJ(bool value);
        bool   IsType(SINT8 Type, bool Exact=false);
        void   SetType(SINT8 Type);

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

        bool operator ==(const STATRecord &other) const;
        bool operator !=(const STATRecord &other) const;
    };
}