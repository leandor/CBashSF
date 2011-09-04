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

namespace Ob
{
class LTEXRecord : public Record //Landscape Texture
    {
    private:
        struct LTEXHNAM
            {
            UINT8   types, friction, restitution;

            LTEXHNAM();
            ~LTEXHNAM();

            bool operator ==(const LTEXHNAM &other) const;
            bool operator !=(const LTEXHNAM &other) const;
            };

        enum typesTypes
            {
            eStone = 0,
            eCloth,
            eDirt,
            eGlass,
            eGrass,
            eMetal,
            eOrganic,
            eSkin,
            eWater,
            eWood,
            eHeavyStone,
            eHeavyMetal,
            eHeavyWood,
            eChain,
            eSnow,
            eStoneStairs,
            eClothStairs,
            eDirtStairs,
            eGlassStairs,
            eGrassStairs,
            eMetalStairs,
            eOrganicStairs,
            eSkinStairs,
            eWaterStairs,
            eWoodStairs,
            eHeavyStoneStairs,
            eHeavyMetalStairs,
            eHeavyWoodStairs,
            eChainStairs,
            eSnowStairs,
            eElevator
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord ICON; //Large Icon Filename
        SemiOptSubRecord<LTEXHNAM> HNAM;
        SemiOptSimpleSubRecord<UINT8, 30> SNAM; //Texture Specular Exponent
        UnorderedSparseArray<FORMID> GNAM;

        LTEXRecord(unsigned char *_recData=NULL);
        LTEXRecord(LTEXRecord *srcRecord);
        ~LTEXRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsStone();
        void   IsStone(bool value);
        bool   IsCloth();
        void   IsCloth(bool value);
        bool   IsDirt();
        void   IsDirt(bool value);
        bool   IsGlass();
        void   IsGlass(bool value);
        bool   IsGrass();
        void   IsGrass(bool value);
        bool   IsMetal();
        void   IsMetal(bool value);
        bool   IsOrganic();
        void   IsOrganic(bool value);
        bool   IsSkin();
        void   IsSkin(bool value);
        bool   IsWater();
        void   IsWater(bool value);
        bool   IsWood();
        void   IsWood(bool value);
        bool   IsHeavyStone();
        void   IsHeavyStone(bool value);
        bool   IsHeavyMetal();
        void   IsHeavyMetal(bool value);
        bool   IsHeavyWood();
        void   IsHeavyWood(bool value);
        bool   IsChain();
        void   IsChain(bool value);
        bool   IsSnow();
        void   IsSnow(bool value);
        bool   IsStoneStairs();
        void   IsStoneStairs(bool value);
        bool   IsClothStairs();
        void   IsClothStairs(bool value);
        bool   IsDirtStairs();
        void   IsDirtStairs(bool value);
        bool   IsGlassStairs();
        void   IsGlassStairs(bool value);
        bool   IsGrassStairs();
        void   IsGrassStairs(bool value);
        bool   IsMetalStairs();
        void   IsMetalStairs(bool value);
        bool   IsOrganicStairs();
        void   IsOrganicStairs(bool value);
        bool   IsSkinStairs();
        void   IsSkinStairs(bool value);
        bool   IsWaterStairs();
        void   IsWaterStairs(bool value);
        bool   IsWoodStairs();
        void   IsWoodStairs(bool value);
        bool   IsHeavyStoneStairs();
        void   IsHeavyStoneStairs(bool value);
        bool   IsHeavyMetalStairs();
        void   IsHeavyMetalStairs(bool value);
        bool   IsHeavyWoodStairs();
        void   IsHeavyWoodStairs(bool value);
        bool   IsChainStairs();
        void   IsChainStairs(bool value);
        bool   IsSnowStairs();
        void   IsSnowStairs(bool value);
        bool   IsElevator();
        void   IsElevator(bool value);
        bool   IsType(UINT8 Type);
        void   SetType(UINT8 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const LTEXRecord &other) const;
        bool operator !=(const LTEXRecord &other) const;
        bool equals(Record *other);
    };
}