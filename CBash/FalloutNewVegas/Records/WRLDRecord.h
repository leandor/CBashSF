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
class WRLDRecord : public FNVRecord //Worldspace
    {
    private:
        enum pnamFlags
            {
            fIsUseLandData          = 0x00000001,
            fIsUseLODData           = 0x00000002,
            fIsUseMapData           = 0x00000004,
            fIsUseWaterData         = 0x00000008,
            fIsUseClimateData       = 0x00000010,
            fIsUseImageSpaceData    = 0x00000020,
            fIsUnknown1             = 0x00000040,
            fIsNeedsWaterAdjustment = 0x00000080
            };

        enum flagsFlags
            {
            fIsSmallWorld   = 0x00000001,
            fIsNoFastTravel = 0x00000002,
            fIsUnknown2     = 0x00000004,
            fIsNoLODWater   = 0x00000010,
            fIsNoLODNoise   = 0x00000020,
            fIsNoNPCFallDmg = 0x00000040
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<FORMID> XEZN; //Encounter Zone
        OptSimpleSubRecord<FORMID> WNAM; //Worldspace
        OptSimpleSubRecord<UINT16> PNAM; //PNAM
        OptSimpleSubRecord<FORMID> CNAM; //Climate
        OptSimpleSubRecord<FORMID> NAM2; //Water
        OptSimpleSubRecord<FORMID> NAM3; //LOD Water Type
        OptSimpleSubRecord<FLOAT32> NAM4; //LOD Water Height
        OptSubRecord<GENDNAM> DNAM; //Land Data
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OptSubRecord<GENMNAM> MNAM; //Map Data
        OptSubRecord<GENONAM> ONAM; //World Map Offset Data
        OptSimpleSubRecord<FORMID> INAM; //Image Space
        OptSimpleSubRecord<UINT8> DATA; //Flags
        OptSubRecord<GENNAM> NAM0; //Min Object Bounds
        OptSubRecord<GENNAM> NAM9; //Max Object Bounds
        OptSimpleSubRecord<FORMID> ZNAM; //Music
        StringRecord NNAM; //Canopy Shadow
        StringRecord XNAM; //Water Noise Texture
        std::vector<ReqSubRecord<GENIMPS> *> IMPS; //Swapped Impact
        std::vector<StringRecord> IMPF; //Footstep Materials
        RawRecord OFST; //Unknown

        Record *ROAD;
        Record *CELL;
        std::vector<Record *> CELLS;

        WRLDRecord(unsigned char *_recData=NULL);
        WRLDRecord(WRLDRecord *srcRecord);
        ~WRLDRecord();

        bool   HasSubRecords();
        bool   VisitSubRecords(const UINT32 &RecordType, RecordOp &op);
        bool   VisitFormIDs(FormIDOp &op);

        bool   IsSmallWorld();
        void   IsSmallWorld(bool value);
        bool   IsNoFastTravel();
        void   IsNoFastTravel(bool value);
        bool   IsFastTravel();
        void   IsFastTravel(bool value);
        bool   IsNoLODWater();
        void   IsNoLODWater(bool value);
        bool   IsLODWater();
        void   IsLODWater(bool value);
        bool   IsNoLODNoise();
        void   IsNoLODNoise(bool value);
        bool   IsLODNoise();
        void   IsLODNoise(bool value);
        bool   IsNoNPCFallDmg();
        void   IsNoNPCFallDmg(bool value);
        bool   IsNPCFallDmg();
        void   IsNPCFallDmg(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsUseLandData();
        void   IsUseLandData(bool value);
        bool   IsUseLODData();
        void   IsUseLODData(bool value);
        bool   IsUseMapData();
        void   IsUseMapData(bool value);
        bool   IsUseWaterData();
        void   IsUseWaterData(bool value);
        bool   IsUseClimateData();
        void   IsUseClimateData(bool value);
        bool   IsUseImageSpaceData();
        void   IsUseImageSpaceData(bool value);
        bool   IsNeedsWaterAdjustment();
        void   IsNeedsWaterAdjustment(bool value);
        bool   IsUseFlagMask(UINT16 Mask, bool Exact=false);
        void   SetUseFlagMask(UINT16 Mask);

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

        bool operator ==(const WRLDRecord &other) const;
        bool operator !=(const WRLDRecord &other) const;
    };
}