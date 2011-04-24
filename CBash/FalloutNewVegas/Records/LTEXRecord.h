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
            eElevator,
            eHollowMetal,
            eSheetMetal,
            eSand,
            eBrokenConcrete,
            eVehicleBody,
            eVehiclePartSolid,
            eVehiclePartHollow,
            eBarrel,
            eBottle,
            eSodaCan,
            ePistol,
            eRifle,
            eShoppingCart,
            eLunchBox,
            eBabyRattle,
            eRubberBall
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENICON> ICON; //Icon Filenames
        OptSimpleSubRecord<FORMID> TNAM; //Texture
        OptSubRecord<LTEXHNAM> HNAM; //Havok Data
        OptSimpleSubRecord<UINT8> SNAM; //Texture Specular Exponent
        std::vector<FORMID> GNAM; //Grasses

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
        bool   IsElevator();
        void   IsElevator(bool value);
        bool   IsHollowMetal();
        void   IsHollowMetal(bool value);
        bool   IsSheetMetal();
        void   IsSheetMetal(bool value);
        bool   IsSand();
        void   IsSand(bool value);
        bool   IsBrokenConcrete();
        void   IsBrokenConcrete(bool value);
        bool   IsVehicleBody();
        void   IsVehicleBody(bool value);
        bool   IsVehiclePartSolid();
        void   IsVehiclePartSolid(bool value);
        bool   IsVehiclePartHollow();
        void   IsVehiclePartHollow(bool value);
        bool   IsBarrel();
        void   IsBarrel(bool value);
        bool   IsBottle();
        void   IsBottle(bool value);
        bool   IsSodaCan();
        void   IsSodaCan(bool value);
        bool   IsPistol();
        void   IsPistol(bool value);
        bool   IsRifle();
        void   IsRifle(bool value);
        bool   IsShoppingCart();
        void   IsShoppingCart(bool value);
        bool   IsLunchBox();
        void   IsLunchBox(bool value);
        bool   IsBabyRattle();
        void   IsBabyRattle(bool value);
        bool   IsRubberBall();
        void   IsRubberBall(bool value);
        bool   IsType(UINT8 Type, bool Exact=false);
        void   SetType(UINT8 Type);

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

        bool operator ==(const LTEXRecord &other) const;
        bool operator !=(const LTEXRecord &other) const;
    };
}