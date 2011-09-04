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
#include "..\..\Allocator.h"
#include "CELLRecord.h"
//#include "ROADRecord.h"
#include <vector>

namespace Ob
{
class WRLDRecord : public Record
    {
    private:
        enum flagsFlags
            {
            fSmallWorld         = 0x00000001,
            fNoFastTravel       = 0x00000002,
            fOblivionWorldspace = 0x00000004,
            fNoLODWater         = 0x00000010
            };

        enum eSNAMType
            {
            eDefault = 0,
            ePublic  = 1,
            eDungeon = 2
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<FORMID> WNAM; //Parent Worldspace
        OptSimpleSubRecord<FORMID> CNAM; //Climate
        OptSimpleSubRecord<FORMID/*, 0x18*/> NAM2; //Water
        StringRecord ICON; //Large Icon Filename
        SemiOptSubRecord<GENMNAM> MNAM; //Map Data
        ReqSimpleSubRecord<UINT8, fSmallWorld> DATA; //Flags
        ReqSubRecord<GENNAM0> NAM0; //Min Object Bounds
        ReqSubRecord<GENNAM9> NAM9; //Max Object Bounds
        OptSimpleSubRecord<UINT32> SNAM; //Sound Type
        RawRecord OFST; //Unknown

        Record *ROAD;
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
        bool   IsOblivionWorldspace();
        void   IsOblivionWorldspace(bool value);
        bool   IsNoLODWater();
        void   IsNoLODWater(bool value);
        bool   IsLODWater();
        void   IsLODWater(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsDefaultMusic();
        void   IsDefaultMusic(bool value);
        bool   IsPublicMusic();
        void   IsPublicMusic(bool value);
        bool   IsDungeonMusic();
        void   IsDungeonMusic(bool value);
        bool   IsMusicType(UINT32 Type);
        void   SetMusicType(UINT32 Type);

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