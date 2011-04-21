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
class ARMARecord : public Record //Armor Addon
    {
    private:
        enum bmdtBipedFlags
            {
            fIsHead        = 0x00000001,
            fIsHair        = 0x00000002,
            fIsUpperBody   = 0x00000004,
            fIsLeftHand    = 0x00000008,
            fIsRightHand   = 0x00000010,
            fIsWeapon      = 0x00000020,
            fIsPipBoy      = 0x00000040,
            fIsBackpack    = 0x00000080,
            fIsNecklace    = 0x00000100,
            fIsHeadband    = 0x00000200,
            fIsHat         = 0x00000400,
            fIsEyeGlasses  = 0x00000800,
            fIsNoseRing    = 0x00001000,
            fIsEarrings    = 0x00002000,
            fIsMask        = 0x00004000,
            fIsChoker      = 0x00008000,
            fIsMouthObject = 0x00010000,
            fIsBodyAddon1  = 0x00020000,
            fIsBodyAddon2  = 0x00040000,
            fIsBodyAddon3  = 0x00080000
            };

        enum bmdtGeneralFlags
            {
            fIsUnknown1    = 0x0001,
            fIsUnknown2    = 0x0002,
            fIsHasBackpack = 0x0004,
            fIsMedium      = 0x0008,
            fIsUnknown3    = 0x0010,
            fIsPowerArmor  = 0x0020,
            fIsNonPlayable = 0x0040,
            fIsHeavy       = 0x0080
            };

        enum eEquipTypes
            {
            eNone    = -1,
            eBigGuns = 0,
            eEnergyWeapons,
            eSmallGuns,
            eMeleeWeapons,
            eUnarmedWeapon,
            eThrownWeapons,
            eMine,
            eBodyWear,
            eHeadWear,
            eHandWear,
            eChems,
            eStimpack,
            eFood,
            eAlcohol
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<GENBMDT> BMDT; //Biped Data
        OptSubRecord<FNVBIPEDMODEL> MODL; //Male Biped Model
        OptSubRecord<FNVWORLDMODEL> MOD2; //Male World Model
        StringRecord ICON; //Male icon filename
        StringRecord MICO; //Male mico filename
        OptSubRecord<FNVBIPEDMODEL> MOD3; //Female Biped Model
        OptSubRecord<FNVWORLDMODEL> MOD4; //Female World Model
        StringRecord ICO2; //Female icon filename
        StringRecord MIC2; //Female mico filename
        OptSubRecord<GENS32> ETYP; //Equipment Type
        OptSubRecord<FNVEQUIPDATA> DATA; //Equipment Data
        OptSubRecord<FNVEQUIPDNAM> DNAM; //Extra Equipment Data

        ARMARecord(unsigned char *_recData=NULL);
        ARMARecord(ARMARecord *srcRecord);
        ~ARMARecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHead();
        void   IsHead(bool value);
        bool   IsHair();
        void   IsHair(bool value);
        bool   IsUpperBody();
        void   IsUpperBody(bool value);
        bool   IsLeftHand();
        void   IsLeftHand(bool value);
        bool   IsRightHand();
        void   IsRightHand(bool value);
        bool   IsWeapon();
        void   IsWeapon(bool value);
        bool   IsPipBoy();
        void   IsPipBoy(bool value);
        bool   IsBackpack();
        void   IsBackpack(bool value);
        bool   IsNecklace();
        void   IsNecklace(bool value);
        bool   IsHeadband();
        void   IsHeadband(bool value);
        bool   IsHat();
        void   IsHat(bool value);
        bool   IsEyeGlasses();
        void   IsEyeGlasses(bool value);
        bool   IsNoseRing();
        void   IsNoseRing(bool value);
        bool   IsEarrings();
        void   IsEarrings(bool value);
        bool   IsMask();
        void   IsMask(bool value);
        bool   IsChoker();
        void   IsChoker(bool value);
        bool   IsMouthObject();
        void   IsMouthObject(bool value);
        bool   IsBodyAddon1();
        void   IsBodyAddon1(bool value);
        bool   IsBodyAddon2();
        void   IsBodyAddon2(bool value);
        bool   IsBodyAddon3();
        void   IsBodyAddon3(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsUnknown1();
        void   IsUnknown1(bool value);
        bool   IsUnknown2();
        void   IsUnknown2(bool value);
        bool   IsHasBackpack();
        void   IsHasBackpack(bool value);
        bool   IsMedium();
        void   IsMedium(bool value);
        bool   IsUnknown3();
        void   IsUnknown3(bool value);
        bool   IsPowerArmor();
        void   IsPowerArmor(bool value);
        bool   IsNonPlayable();
        void   IsNonPlayable(bool value);
        bool   IsHeavy();
        void   IsHeavy(bool value);
        bool   IsExtraFlagMask(UINT8 Mask, bool Exact=false);
        void   SetExtraFlagMask(UINT8 Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsBigGuns();
        void   IsBigGuns(bool value);
        bool   IsEnergyWeapons();
        void   IsEnergyWeapons(bool value);
        bool   IsSmallGuns();
        void   IsSmallGuns(bool value);
        bool   IsMeleeWeapons();
        void   IsMeleeWeapons(bool value);
        bool   IsUnarmedWeapon();
        void   IsUnarmedWeapon(bool value);
        bool   IsThrownWeapons();
        void   IsThrownWeapons(bool value);
        bool   IsMine();
        void   IsMine(bool value);
        bool   IsBodyWear();
        void   IsBodyWear(bool value);
        bool   IsHeadWear();
        void   IsHeadWear(bool value);
        bool   IsHandWear();
        void   IsHandWear(bool value);
        bool   IsChems();
        void   IsChems(bool value);
        bool   IsStimpack();
        void   IsStimpack(bool value);
        bool   IsFood();
        void   IsFood(bool value);
        bool   IsAlcohol();
        void   IsAlcohol(bool value);
        bool   IsEquipmentType(SINT32 Type, bool Exact=false);
        void   SetEquipmentType(SINT32 Type);

        bool   IsModulatesVoice();
        void   IsModulatesVoice(bool value);
        bool   IsDNAMFlagMask(UINT16 Mask, bool Exact=false);
        void   SetDNAMFlagMask(UINT16 Mask);

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

        bool operator ==(const ARMARecord &other) const;
        bool operator !=(const ARMARecord &other) const;
    };
}