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
    private:
        enum typeTypes
            {
            eNone = -1,
            eBattle = 0,
            eLocation,
            eDungeon,
            eIncidential
            };

        enum flagsFlags
            {
            fIsDayOuter = 0x01,
            fIsDayMiddle = 0x02,
            fIsDayInner = 0x04,
            fIsNightOuter = 0x08,
            fIsNightMiddle = 0x10,
            fIsNightInner = 0x20
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<UINT32> NAM1; //Type
        StringRecord NAM2; //Loop (B) / Battle (D) / Day Outer (L)
        StringRecord NAM3; //Explore (D) / Day Middle (L)
        StringRecord NAM4; //Suspense (D) / Day Inner (L)
        StringRecord NAM5; //Night Outer (L)
        StringRecord NAM6; //Night Middle (L)
        StringRecord NAM7; //Night Inner (L)
        OptSimpleSubRecord<FLOAT32> NAM8; //Loop dB (B) / Battle dB (D) / Day Outer dB (L)
        OptSimpleSubRecord<FLOAT32> NAM9; //Explore dB (D) / Day Middle dB (L)
        OptSimpleSubRecord<FLOAT32> NAM0; //Suspense dB (D) / Day Inner dB (L)
        OptSimpleSubRecord<FLOAT32> ANAM; //Night Outer dB (L)
        OptSimpleSubRecord<FLOAT32> BNAM; //Night Middle dB (L)
        OptSimpleSubRecord<FLOAT32> CNAM; //Night Inner dB (L)
        OptSimpleSubRecord<FLOAT32> JNAM; //Day Outer Boundary % (L)
        OptSimpleSubRecord<FLOAT32> KNAM; //Day Middle Boundary % (L)
        OptSimpleSubRecord<FLOAT32> LNAM; //Day Inner Boundary % (L)
        OptSimpleSubRecord<FLOAT32> MNAM; //Night Outer Boundary % (L)
        OptSimpleSubRecord<FLOAT32> NNAM; //Night Middle Boundary % (L)
        OptSimpleSubRecord<FLOAT32> ONAM; //Night Inner Boundary % (L)
        OptSimpleSubRecord<UINT8> PNAM; //Enable Flags
        OptSimpleSubRecord<FLOAT32> DNAM; //Wait Time (B) / Minimum Time On (D,L) / Daytime Min (I)
        OptSimpleSubRecord<FLOAT32> ENAM; //Loop Fade Out (B) / Looping/Random Crossfade Overlap (D,L) / Nighttime Min (I)
        OptSimpleSubRecord<FLOAT32> FNAM; //Recovery Time (B) / Layer Crossfade Time (D,L) / Daytime Max (I)
        OptSimpleSubRecord<FLOAT32> GNAM; //Nighttime Max (I)
        OptSimpleSubRecord<FORMID> HNAM; //Intro (B,D) / Daytime (I)
        OptSimpleSubRecord<FORMID> INAM; //Outro (B,D) / Nighttime (I)
        RawRecord DATA; //Unknown

        MSETRecord(unsigned char *_recData=NULL);
        MSETRecord(MSETRecord *srcRecord);
        ~MSETRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsDayOuter();
        void   IsDayOuter(bool value);
        bool   IsDayMiddle();
        void   IsDayMiddle(bool value);
        bool   IsDayInner();
        void   IsDayInner(bool value);
        bool   IsNightOuter();
        void   IsNightOuter(bool value);
        bool   IsNightMiddle();
        void   IsNightMiddle(bool value);
        bool   IsNightInner();
        void   IsNightInner(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsBattle();
        void   IsBattle(bool value);
        bool   IsLocation();
        void   IsLocation(bool value);
        bool   IsDungeon();
        void   IsDungeon(bool value);
        bool   IsIncidential();
        void   IsIncidential(bool value);
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

        bool operator ==(const MSETRecord &other) const;
        bool operator !=(const MSETRecord &other) const;
    };
}