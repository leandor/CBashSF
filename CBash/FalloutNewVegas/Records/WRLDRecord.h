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

 CBash copyright (C) 2010-2011 Waruddar
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
            fIsUseLandData          = 0x0001,
            fIsUseLODData           = 0x0002,
            fIsUseMapData           = 0x0004,
            fIsUseWaterData         = 0x0008,
            fIsUseClimateData       = 0x0010,
            fIsUseImageSpaceData    = 0x0020,
            fIsUnknown1             = 0x0040,
            fIsNeedsWaterAdjustment = 0x0080
            };

        enum flagsFlags
            {
            fIsSmallWorld   = 0x01,
            fIsNoFastTravel = 0x02,
            fIsUnknown2     = 0x04,
            fIsNoLODWater   = 0x10,
            fIsNoLODNoise   = 0x20,
            fIsNoNPCFallDmg = 0x40
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<FORMID> XEZN; //Encounter Zone
        OptSimpleSubRecord<FORMID> WNAM; //Parent Worldspace
        OptSimpleSubRecord<UINT16> PNAM; //Parent Flags
        OptSimpleSubRecord<FORMID> CNAM; //Climate
        ReqSimpleSubRecord<FORMID, 0x18> NAM2; //Water
        ReqSimpleSubRecord<FORMID, 0x18> NAM3; //LOD Water Type
        SemiOptSimpleFloatSubRecord<flt_0> NAM4; //LOD Water Height
        ReqSubRecord<GENDNAM> DNAM; //Land Data
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        SemiOptSubRecord<GENMNAM> MNAM; //Map Data
        ReqSubRecord<GENONAM> ONAM; //World Map Offset Data
        OptSimpleSubRecord<FORMID> INAM; //Image Space
        ReqSimpleSubRecord<UINT8, fIsSmallWorld> DATA; //Flags
        ReqSubRecord<GENNAM0> NAM0; //Min Object Bounds
        ReqSubRecord<GENNAM9> NAM9; //Max Object Bounds
        OptSimpleSubRecord<FORMID> ZNAM; //Music
        StringRecord NNAM; //Canopy Shadow (REQ)
        StringRecord XNAM; //Water Noise Texture (REQ)
        UnorderedSparseArray<GENIMPS *> IMPS; //Swapped Impact
        OptSubRecord<GENIMPF> IMPF; //Footstep Materials
        RawRecord OFST; //Unknown

        //Record *ROAD;
        Record *CELL;
        std::vector<Record *> CELLS;

        WRLDRecord(unsigned char *_recData=NULL);
        WRLDRecord(WRLDRecord *srcRecord);
        ~WRLDRecord();

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

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const WRLDRecord &other) const;
        bool operator !=(const WRLDRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}