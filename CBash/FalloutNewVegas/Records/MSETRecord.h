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
class MSETRecord : public Record //Media Set
    {
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<GENU32> NAM1; //Type
        StringRecord NAM2; //Loop (B) / Battle (D) / Day Outer (L)
        StringRecord NAM3; //Explore (D) / Day Middle (L)
        StringRecord NAM4; //Suspense (D) / Day Inner (L)
        StringRecord NAM5; //Night Outer (L)
        StringRecord NAM6; //Night Middle (L)
        StringRecord NAM7; //Night Inner (L)
        OptSubRecord<GENFLOAT> NAM8; //Loop dB (B) / Battle dB (D) / Day Outer dB (L)
        OptSubRecord<GENFLOAT> NAM9; //Explore dB (D) / Day Middle dB (L)
        OptSubRecord<GENFLOAT> NAM0; //Suspense dB (D) / Day Inner dB (L)
        OptSubRecord<GENFLOAT> ANAM; //Night Outer dB (L)
        OptSubRecord<GENFLOAT> BNAM; //Night Middle dB (L)
        OptSubRecord<GENFLOAT> CNAM; //Night Inner dB (L)
        OptSubRecord<GENFLOAT> JNAM; //Day Outer Boundary % (L)
        OptSubRecord<GENFLOAT> KNAM; //Day Middle Boundary % (L)
        OptSubRecord<GENFLOAT> LNAM; //Day Inner Boundary % (L)
        OptSubRecord<GENFLOAT> MNAM; //Night Outer Boundary % (L)
        OptSubRecord<GENFLOAT> NNAM; //Night Middle Boundary % (L)
        OptSubRecord<GENFLOAT> ONAM; //Night Inner Boundary % (L)
        OptSubRecord<GENU8> PNAM; //Enable Flags
        OptSubRecord<GENFLOAT> DNAM; //Wait Time (B) / Minimum Time On (D,L) / Daytime Min (I)
        OptSubRecord<GENFLOAT> ENAM; //Loop Fade Out (B) / Looping/Random Crossfade Overlap (D,L) / Nighttime Min (I)
        OptSubRecord<GENFLOAT> FNAM; //Recovery Time (B) / Layer Crossfade Time (D,L) / Daytime Max (I)
        OptSubRecord<GENFLOAT> GNAM; //Nighttime Max (I)
        OptSubRecord<GENFID> HNAM; //Intro (B,D) / Daytime (I)
        OptSubRecord<GENFID> INAM; //Outro (B,D) / Nighttime (I)
        RawRecord DATA; //Unknown

        MSETRecord(unsigned char *_recData=NULL);
        MSETRecord(MSETRecord *srcRecord);
        ~MSETRecord();

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

        bool operator ==(const MSETRecord &other) const;
        bool operator !=(const MSETRecord &other) const;
    };
}