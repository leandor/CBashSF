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
class ARMARecord : public Record //Armor Addon
    {
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<GENBMDT> BMDT; //Biped Data
        OptSubRecord<GENMODEL> MODL; //Model Filename
        OptSubRecord<GENMOD2> MOD2; //Model Filename
        StringRecord ICON; //Male icon filename
        StringRecord MICO; //Male mico filename
        OptSubRecord<GENMOD3> MOD3; //Model Filename
        OptSubRecord<GENMOD4> MOD4; //Model Filename
        StringRecord ICO2; //Female icon filename
        StringRecord MIC2; //Female mico filename
        OptSubRecord<GENS32> ETYP; //Equipment Type
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct
        OptSubRecord<GENDNAM> DNAM; //DNAM ,, Struct

        ARMARecord(unsigned char *_recData=NULL);
        ARMARecord(ARMARecord *srcRecord);
        ~ARMARecord();

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

        bool operator ==(const ARMARecord &other) const;
        bool operator !=(const ARMARecord &other) const;
    };
}