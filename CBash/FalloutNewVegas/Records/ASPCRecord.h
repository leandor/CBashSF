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
class ASPCRecord : public FNVRecord //Acoustic Space
    {
    private:
        enum eEnvTypes
            {
            eNone = 0,
            eDefault,
            eGeneric,
            ePaddedCell,
            eRoom,
            eBathroom,
            eLivingroom,
            eStoneRoom,
            eAuditorium,
            eConcerthall,
            eCave,
            eArena,
            eHangar,
            eCarpetedHallway,
            eHallway,
            eStoneCorridor,
            eAlley,
            eForest,
            eCity,
            eMountains,
            eQuarry,
            ePlain,
            eParkinglot,
            eSewerpipe,
            eUnderwater,
            eSmallRoom,
            eMediumRoom,
            eLargeRoom,
            eMediumHall,
            eLargeHall,
            ePlate
            };

        enum eSpaceTypes
            {
            eIsExterior = 0,
            eIsInterior
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        OptSimpleSubRecord<FORMID> DawnSNAM; //Dawn / Default Loop
        OptSimpleSubRecord<FORMID> AfternoonSNAM; //Afternoon
        OptSimpleSubRecord<FORMID> DuskSNAM; //Dusk
        OptSimpleSubRecord<FORMID> NightSNAM; //Night
        OptSimpleSubRecord<FORMID> WallaSNAM; //Walla
        OptSimpleSubRecord<UINT32> WNAM; //Walla Trigger Count
        OptSimpleSubRecord<FORMID> RDAT; //Use Sound from Region (Interiors Only)
        OptSimpleSubRecord<UINT32> ANAM; //Environment Type
        OptSimpleSubRecord<UINT32> INAM; //Is Interior

        ASPCRecord(unsigned char *_recData=NULL);
        ASPCRecord(ASPCRecord *srcRecord);
        ~ASPCRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsDefault();
        void   IsDefault(bool value);
        bool   IsGeneric();
        void   IsGeneric(bool value);
        bool   IsPaddedCell();
        void   IsPaddedCell(bool value);
        bool   IsRoom();
        void   IsRoom(bool value);
        bool   IsBathroom();
        void   IsBathroom(bool value);
        bool   IsLivingroom();
        void   IsLivingroom(bool value);
        bool   IsStoneRoom();
        void   IsStoneRoom(bool value);
        bool   IsAuditorium();
        void   IsAuditorium(bool value);
        bool   IsConcerthall();
        void   IsConcerthall(bool value);
        bool   IsCave();
        void   IsCave(bool value);
        bool   IsArena();
        void   IsArena(bool value);
        bool   IsHangar();
        void   IsHangar(bool value);
        bool   IsCarpetedHallway();
        void   IsCarpetedHallway(bool value);
        bool   IsHallway();
        void   IsHallway(bool value);
        bool   IsStoneCorridor();
        void   IsStoneCorridor(bool value);
        bool   IsAlley();
        void   IsAlley(bool value);
        bool   IsForest();
        void   IsForest(bool value);
        bool   IsCity();
        void   IsCity(bool value);
        bool   IsMountains();
        void   IsMountains(bool value);
        bool   IsQuarry();
        void   IsQuarry(bool value);
        bool   IsPlain();
        void   IsPlain(bool value);
        bool   IsParkinglot();
        void   IsParkinglot(bool value);
        bool   IsSewerpipe();
        void   IsSewerpipe(bool value);
        bool   IsUnderwater();
        void   IsUnderwater(bool value);
        bool   IsSmallRoom();
        void   IsSmallRoom(bool value);
        bool   IsMediumRoom();
        void   IsMediumRoom(bool value);
        bool   IsLargeRoom();
        void   IsLargeRoom(bool value);
        bool   IsMediumHall();
        void   IsMediumHall(bool value);
        bool   IsLargeHall();
        void   IsLargeHall(bool value);
        bool   IsPlate();
        void   IsPlate(bool value);
        bool   IsEnvironmentType(UINT32 Type, bool Exact=false);
        void   SetEnvironmentType(UINT32 Type);

        bool   IsExterior();
        void   IsExterior(bool value);
        bool   IsInterior();
        void   IsInterior(bool value);
        bool   IsSpaceType(UINT32 Type, bool Exact=false);
        void   SetSpaceType(UINT32 Type);

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

        bool operator ==(const ASPCRecord &other) const;
        bool operator !=(const ASPCRecord &other) const;
    };
}