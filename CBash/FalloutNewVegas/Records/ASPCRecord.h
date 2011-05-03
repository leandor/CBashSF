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
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        ReqSimpleSubRecord<FORMID> DawnSNAM; //Dawn / Default Loop
        ReqSimpleSubRecord<FORMID> AfternoonSNAM; //Afternoon
        ReqSimpleSubRecord<FORMID> DuskSNAM; //Dusk
        ReqSimpleSubRecord<FORMID> NightSNAM; //Night
        ReqSimpleSubRecord<FORMID> WallaSNAM; //Walla
        ReqSimpleSubRecord<UINT32> WNAM; //Walla Trigger Count
        OptSimpleSubRecord<FORMID> RDAT; //Use Sound from Region (Interiors Only)
        ReqSimpleSubRecord<UINT32> ANAM; //Environment Type
        ReqSimpleSubRecord<UINT32> INAM; //Is Interior

        ASPCRecord(unsigned char *_recData=NULL);
        ASPCRecord(ASPCRecord *srcRecord);
        ~ASPCRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsEnvironmentNone();
        void   IsEnvironmentNone(bool value);
        bool   IsEnvironmentDefault();
        void   IsEnvironmentDefault(bool value);
        bool   IsEnvironmentGeneric();
        void   IsEnvironmentGeneric(bool value);
        bool   IsEnvironmentPaddedCell();
        void   IsEnvironmentPaddedCell(bool value);
        bool   IsEnvironmentRoom();
        void   IsEnvironmentRoom(bool value);
        bool   IsEnvironmentBathroom();
        void   IsEnvironmentBathroom(bool value);
        bool   IsEnvironmentLivingroom();
        void   IsEnvironmentLivingroom(bool value);
        bool   IsEnvironmentStoneRoom();
        void   IsEnvironmentStoneRoom(bool value);
        bool   IsEnvironmentAuditorium();
        void   IsEnvironmentAuditorium(bool value);
        bool   IsEnvironmentConcerthall();
        void   IsEnvironmentConcerthall(bool value);
        bool   IsEnvironmentCave();
        void   IsEnvironmentCave(bool value);
        bool   IsEnvironmentArena();
        void   IsEnvironmentArena(bool value);
        bool   IsEnvironmentHangar();
        void   IsEnvironmentHangar(bool value);
        bool   IsEnvironmentCarpetedHallway();
        void   IsEnvironmentCarpetedHallway(bool value);
        bool   IsEnvironmentHallway();
        void   IsEnvironmentHallway(bool value);
        bool   IsEnvironmentStoneCorridor();
        void   IsEnvironmentStoneCorridor(bool value);
        bool   IsEnvironmentAlley();
        void   IsEnvironmentAlley(bool value);
        bool   IsEnvironmentForest();
        void   IsEnvironmentForest(bool value);
        bool   IsEnvironmentCity();
        void   IsEnvironmentCity(bool value);
        bool   IsEnvironmentMountains();
        void   IsEnvironmentMountains(bool value);
        bool   IsEnvironmentQuarry();
        void   IsEnvironmentQuarry(bool value);
        bool   IsEnvironmentPlain();
        void   IsEnvironmentPlain(bool value);
        bool   IsEnvironmentParkinglot();
        void   IsEnvironmentParkinglot(bool value);
        bool   IsEnvironmentSewerpipe();
        void   IsEnvironmentSewerpipe(bool value);
        bool   IsEnvironmentUnderwater();
        void   IsEnvironmentUnderwater(bool value);
        bool   IsEnvironmentSmallRoom();
        void   IsEnvironmentSmallRoom(bool value);
        bool   IsEnvironmentMediumRoom();
        void   IsEnvironmentMediumRoom(bool value);
        bool   IsEnvironmentLargeRoom();
        void   IsEnvironmentLargeRoom(bool value);
        bool   IsEnvironmentMediumHall();
        void   IsEnvironmentMediumHall(bool value);
        bool   IsEnvironmentLargeHall();
        void   IsEnvironmentLargeHall(bool value);
        bool   IsEnvironmentPlate();
        void   IsEnvironmentPlate(bool value);
        bool   IsEnvironmentType(UINT32 Type);
        void   SetEnvironmentType(UINT32 Type);

        bool   IsSpaceExterior();
        void   IsSpaceExterior(bool value);
        bool   IsSpaceInterior();
        void   IsSpaceInterior(bool value);
        bool   IsSpaceType(UINT32 Type);
        void   SetSpaceType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const ASPCRecord &other) const;
        bool operator !=(const ASPCRecord &other) const;
    };
}