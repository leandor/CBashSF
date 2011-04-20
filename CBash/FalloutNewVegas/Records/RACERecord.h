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
class RACERecord : public Record //Race
    {
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        OptSubRecord<GENXNAM> XNAM; //Relation
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct
        OptSubRecord<GENFID> ONAM; //Older
        OptSubRecord<GENFID> YNAM; //Younger
        OptSubRecord<GENNAM2> NAM2; //Unknown Marker
        OptSubRecord<GENVTCK> VTCK; //Voices
        OptSubRecord<GENDNAM> DNAM; //Default Hair Styles
        OptSubRecord<GENCNAM> CNAM; //Default Hair Colors
        OptSubRecord<GENFLOAT> PNAM; //FaceGen - Main clamp
        OptSubRecord<GENFLOAT> UNAM; //FaceGen - Face clamp
        RawRecord ATTR; //Unknown
        OptSubRecord<GENNAM> NAM0; //Head Data Marker
        OptSubRecord<GENMNAM> MNAM; //Male Data Marker
        OptSubRecord<GENU32> INDX; //Index
        OptSubRecord<GENMODEL> MODL; //Model Filename
        OptSubRecord<GENICON> ICON; //Large Icon Filename
        OptSubRecord<GENFNAM> FNAM; //Female Data Marker
        OptSubRecord<GENNAM1> NAM1; //Body Data Marker
        OptSubRecord<GENHNAM> HNAM; //Hairs
        OptSubRecord<GENENAM> ENAM; //Eyes
        OptSubRecord<GENFGGS> FGGS; //FaceGen Geometry-Symmetric
        RawRecord SNAM; //Unknown

        RACERecord(unsigned char *_recData=NULL);
        RACERecord(RACERecord *srcRecord);
        ~RACERecord();

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

        bool operator ==(const RACERecord &other) const;
        bool operator !=(const RACERecord &other) const;
    };
}