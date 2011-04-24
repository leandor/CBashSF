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
class REGNRecord : public Record //Region
    {
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENICON> ICON; //Large Icon Filename
        OptSubRecord<GENRCLR> RCLR; //RCLR ,, Struct
        OptSimpleSubRecord<FORMID> WNAM; //Worldspace
        OptSimpleSubRecord<UINT32> RPLI; //Edge Fall-off
        OptSubRecord<GENRPLD> RPLD; //RPLD ,, Struct
        OptSubRecord<GENRDAT> RDAT; //RDAT ,, Struct
        OptSubRecord<GENRDOT> RDOT; //RDOT ,, Struct
        StringRecord RDMP; //Map Name
        OptSubRecord<GENRDGS> RDGS; //RDGS ,, Struct
        OptSimpleSubRecord<UINT32> RDMD; //Music Type
        OptSimpleSubRecord<FORMID> RDMO; //Music
        OptSimpleSubRecord<FORMID> RDSI; //Incidental MediaSet
        OptSimpleSubRecord<FORMID> RDSB; //Battle MediaSet
        OptSubRecord<GENRDSD> RDSD; //RDSD ,, Struct
        OptSubRecord<GENRDWT> RDWT; //RDWT ,, Struct
        OptSubRecord<GENRDID> RDID; //Imposters

        REGNRecord(unsigned char *_recData=NULL);
        REGNRecord(REGNRecord *srcRecord);
        ~REGNRecord();

        bool   VisitFormIDs(FormIDOp &op);

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

        bool operator ==(const REGNRecord &other) const;
        bool operator !=(const REGNRecord &other) const;
    };
}