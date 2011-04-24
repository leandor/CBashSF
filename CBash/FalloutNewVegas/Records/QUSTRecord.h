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
class QUSTRecord : public Record //Quest
    {
    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<FORMID> SCRI; //Script
        StringRecord FULL; //Name
        OptSubRecord<GENICON> ICON; //Large Icon Filename
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct
        OptSubRecord<GENCTDA> CTDA; //Conditions
        OptSimpleSubRecord<SINT16> INDX; //Stage Index
        OptSimpleSubRecord<UINT8> QSDT; //Stage Flags
        StringRecord CNAM; //Log Entry
        OptSubRecord<FNVSCHR> SCHR; //Basic Script Data
        OptSimpleSubRecord<FORMID> NAM0; //Next Quest
        OptSimpleSubRecord<SINT32> QOBJ; //Objective Index
        StringRecord NNAM; //Description
        OptSubRecord<GENQSTA> QSTA; //QSTA ,, Struct

        QUSTRecord(unsigned char *_recData=NULL);
        QUSTRecord(QUSTRecord *srcRecord);
        ~QUSTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool IsScriptEnabled();
        void IsScriptEnabled(bool value);
        bool IsScriptFlagMask(UINT16 Mask, bool Exact=false);
        void SetScriptFlagMask(UINT16 Mask);

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

        bool operator ==(const QUSTRecord &other) const;
        bool operator !=(const QUSTRecord &other) const;
    };
}