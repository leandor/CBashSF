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
class LSCTRecord : public FNVRecord //Load Screen Type
    {
    private:
        struct LSCTDATA
            {
            UINT32  screenType; //Type
            //Data 1
            UINT32  x, y, width, height;
            FLOAT32 orientation;
            UINT32  font1;
            FLOAT32 font1Red, font1Green, font1Blue;
            UINT32  alignmentType;
            UINT8   unknown1[20];
            //Data 2
            UINT32  font2;
            FLOAT32 font2Red, font2Green, font2Blue;
            UINT8   unknown2[4];
            UINT32  stats;

            LSCTDATA();
            ~LSCTDATA();

            bool operator ==(const LSCTDATA &other) const;
            bool operator !=(const LSCTDATA &other) const;
            };

        enum eScreenTypeTypes
            {
            eNone       = 0,
            eXPProgress = 1,
            eObjective  = 2,
            eTip        = 3,
            eStats      = 4
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<LSCTDATA> DATA; //Data

        LSCTRecord(unsigned char *_recData=NULL);
        LSCTRecord(LSCTRecord *srcRecord);
        ~LSCTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsXPProgress();
        void   IsXPProgress(bool value);
        bool   IsObjective();
        void   IsObjective(bool value);
        bool   IsTip();
        void   IsTip(bool value);
        bool   IsStats();
        void   IsStats(bool value);
        bool   IsType(UINT32 Type, bool Exact=false);
        void   SetType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(_FileHandler &SaveHandler);

        bool operator ==(const LSCTRecord &other) const;
        bool operator !=(const LSCTRecord &other) const;
    };
}