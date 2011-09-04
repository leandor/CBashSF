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
class WEAPRecord : public FNVRecord //Weapon
    {
    private:
        #pragma pack(push)
        #pragma pack(1)
        struct WEAPDATA
            {
            SINT32  value, health;
            FLOAT32 weight;
            SINT16  damage;
            UINT8   clipSize;

            WEAPDATA();
            ~WEAPDATA();

            bool operator ==(const WEAPDATA &other) const;
            bool operator !=(const WEAPDATA &other) const;
            };
        #pragma pack(pop)

        struct WEAPDNAM
            {
            UINT32  animType;
            FLOAT32 animMult, reach;
            UINT8   flags1, gripAnim, ammoUse, reloadAnim;
            FLOAT32 minSpread, spread, unknown1, sightFOV, unknown2;
            FORMID  projectile;
            UINT8   VATSHitChance, attackAnim, projectileCount, weaponAV;
            FLOAT32 minRange, maxRange;
            UINT32  onHit, flags2;
            FLOAT32 animAttackMult, fireRate, overrideAP, leftRumble,
                    rightRumble, timeRumble, overrideDamageToWeapon,
                    shotsPerSecond, reloadTime, jamTime, aimArc;
            SINT32  skill;
            UINT32  rumbleType;
            FLOAT32 rumbleWavelength, limbDamageMult;
            SINT32  resistType;
            FLOAT32 sightUsage, semiFireDelayMin, semiFireDelayMax, unknown3;
            UINT32  effectMod1, effectMod2, effectMod3;
            FLOAT32 valueAMod1, valueAMod2, valueAMod3;
            UINT32  overridePwrAtkAnim, strengthReq;
            UINT8   unknown4, reloadAnimMod, unknown5[2];
            FLOAT32 regenRate, killImpulse, valueBMod1, valueBMod2, valueBMod3,
                    impulseDist;
            UINT32  skillReq;

            WEAPDNAM();
            ~WEAPDNAM();

            bool operator ==(const WEAPDNAM &other) const;
            bool operator !=(const WEAPDNAM &other) const;
            };

        struct WEAPCRDT //Critical Data
            {
            UINT16  critDamage;
            UINT8   unused1[2];
            FLOAT32 critMult;
            UINT8   flags, unused2[3];
            FORMID  effect;

            WEAPCRDT();
            ~WEAPCRDT();

            bool operator ==(const WEAPCRDT &other) const;
            bool operator !=(const WEAPCRDT &other) const;
            };

        struct WEAPVATS //VATS
            {
            FORMID  effect;
            FLOAT32 skill, damageMult, AP;
            //Below are not present on all chunks...
            UINT8   silenceType, modRequiredType, unused1[2];

            WEAPVATS();
            ~WEAPVATS();

            bool operator ==(const WEAPVATS &other) const;
            bool operator !=(const WEAPVATS &other) const;
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
            eEdible,
            eAlcohol
            };

        enum eWeaponAnimTypes
            {
            eHand2Hand = 0,
            eMelee1Hand,
            eMelee2Hand,
            ePistolBallistic1Hand,
            ePistolEnergy1Hand,
            eRifleBallistic2Hand,
            eRifleAutomatic2Hand,
            eRifleEnergy2Hand,
            eHandle2Hand,
            eLauncher2Hand,
            eGrenadeThrow1Hand,
            eLandMine1Hand,
            eMineDrop1Hand,
            eThrown1Hand
            };

        enum flags1Flags
            {
            fIsNotNormalWeapon              = 0x01,
            fIsAutomatic                    = 0x02,
            fIsHasScope                     = 0x04,
            fIsCantDrop                     = 0x08,
            fIsHideBackpack                 = 0x10,
            fIsEmbeddedWeapon               = 0x20,
            fIsDontUse1stPersonISAnimations = 0x40,
            fIsNonPlayable                  = 0x80
            };

        enum eGripAnimTypes
            {
            eHandGrip1 = 230,
            eHandGrip2,
            eHandGrip3,
            eHandGrip4,
            eHandGrip5,
            eHandGrip6,
            eHandGripDefault
            };

        enum eReloadAnimTypes
            {
            eReloadA = 0,
            eReloadB,
            eReloadC,
            eReloadD,
            eReloadE,
            eReloadF,
            eReloadG,
            eReloadH,
            eReloadI,
            eReloadJ,
            eReloadK,
            eReloadL,
            eReloadM,
            eReloadN,
            eReloadO,
            eReloadP,
            eReloadQ,
            eReloadR,
            eReloadS,
            //eReloadT,
            //eReloadU,
            //eReloadV,
            eReloadW,
            eReloadX,
            eReloadY,
            eReloadZ
            };

        enum eAttackAnimTypes
            {
            eAttackLeft    = 26,
            eAttackRight   = 32,
            eAttack3       = 38,
            eAttack4       = 44,
            eAttack5       = 50,
            eAttack6       = 56,
            eAttack7       = 62,
            eAttack8       = 68,
            eAttack9       = 144,
            eAttackLoop    = 74,
            eAttackSpin    = 80,
            eAttackSpin2   = 86,
            eAttackThrow   = 114,
            eAttackThrow2  = 120,
            eAttackThrow3  = 126,
            eAttackThrow4  = 132,
            eAttackThrow5  = 138,
            eAttackThrow6  = 150,
            eAttackThrow7  = 156,
            eAttackThrow8  = 162,
            ePlaceMine     = 102,
            ePlaceMine2    = 108,
            eAttackDefault = 255
            };

        enum onHitTypes
            {
            ePerception = 0,
            eEndurance,
            eLeftAttack,
            eRightAttack,
            eLeftMobility,
            eRightMobilty,
            eBrain
            };

        enum embeddedAVTypes
            {
            eNormalFormulaBehavior = 0,
            eDismemberOnly,
            eExplodeOnly,
            eNoDismemberExplode
            };

        enum flags2Flags
            {
            fIsPlayerOnly                   = 0x00000001,
            fIsNPCsUseAmmo                  = 0x00000002,
            fIsNoJamAfterReload             = 0x00000004,
            fIsOverrideActionPoints         = 0x00000008,
            fIsMinorCrime                   = 0x00000010,
            fIsRangeFixed                   = 0x00000020,
            fIsNotUsedInNormalCombat        = 0x00000040,
            fIsOverrideDamageToWeaponMult   = 0x00000080,
            fIsDontUse3rdPersonISAnimations = 0x00000100,
            fIsShortBurst                   = 0x00000200,
            fIsRumbleAlternate              = 0x00000400,
            fIsLongBurst                    = 0x00000800,
            fIsScopeHasNightVision          = 0x00001000,
            fIsScopeFromMod                 = 0x00002000
            };

        enum eRumbleTypes
            {
            eConstant = 0,
            eSquare,
            eTriangle,
            eSawtooth
            };

        enum ePowerAttackAnimOverrideTypes
            {
            eUnknown0            = 0,
            eAttackCustom1Power  = 97,
            eAttackCustom2Power  = 98,
            eAttackCustom3Power  = 99,
            eAttackCustom4Power  = 100,
            eAttackCustom5Power  = 101,
            eAttackCustomDefault = 255
            };

        enum critFlagFlags
            {
            fIsOnDeath = 0x01
            };

        enum silenceTypes
            {
            eIsNotSilent = 0,
            eIsSilent
            };

        enum modRequiredTypes
            {
            eIsNotModRequired = 0,
            eIsModRequired
            };

        enum soundLevelTypes
            {
            eLoud = 0,
            eNormal,
            eSilent
            };
    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSimpleSubRecord<FORMID> EITM; //Object Effect
        OptSimpleSubRecord<SINT16> EAMT; //Enchantment Charge Amount
        OptSimpleSubRecord<FORMID> NAM0; //Ammo
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSimpleSubRecord<FORMID> REPL; //Repair List
        ReqSimpleSubRecord<SINT32> ETYP; //Equipment Type
        OptSimpleSubRecord<FORMID> BIPL; //Biped Model List
        OptSimpleSubRecord<FORMID> YNAM; //Sound - Pick Up
        OptSimpleSubRecord<FORMID> ZNAM; //Sound - Drop
        OptSubRecord<FNVWORLDMODEL> MOD2; //Shell Casing Model
        OptSubRecord<FNVWORLDMODEL> MOD3; //Scope Model
        OptSimpleSubRecord<FORMID> EFSD; //Scope Effect
        OptSubRecord<FNVWORLDMODEL> MOD4; //World Model
        StringRecord VANM; //VATS Attack Name
        StringRecord NNAM; //Embedded Weapon Node

        //Model with Mods
        StringRecord MWD1; //Mod 1
        StringRecord MWD2; //Mod 2
        StringRecord MWD3; //Mod 1 and 2
        StringRecord MWD4; //Mod 3
        StringRecord MWD5; //Mod 1 and 3
        StringRecord MWD6; //Mod 2 and 3
        StringRecord MWD7; //Mod 1, 2 and 3

        OptSimpleSubRecord<FORMID> INAM; //Impact DataSet
        OptSimpleSubRecord<FORMID> WNAM; //1st Person Model

        //1st Person Models with Mods
        OptSimpleSubRecord<FORMID> WNM1; //Mod 1
        OptSimpleSubRecord<FORMID> WNM2; //Mod 2
        OptSimpleSubRecord<FORMID> WNM3; //Mod 1 and 2
        OptSimpleSubRecord<FORMID> WNM4; //Mod 3
        OptSimpleSubRecord<FORMID> WNM5; //Mod 1 and 3
        OptSimpleSubRecord<FORMID> WNM6; //Mod 2 and 3
        OptSimpleSubRecord<FORMID> WNM7; //Mod 1, 2 and 3

        //Weapon Mods
        OptSimpleSubRecord<FORMID> WMI1; //Mod 1
        OptSimpleSubRecord<FORMID> WMI2; //Mod 2
        OptSimpleSubRecord<FORMID> WMI3; //Mod 3

        OptSimpleSubRecord<FORMID> SNAM1; //Sound - Gun - Shoot 3D
        OptSimpleSubRecord<FORMID> SNAM2; //Sound - Gun - Shoot Dist
        OptSimpleSubRecord<FORMID> XNAM; //Sound - Gun - Shoot 2D
        OptSimpleSubRecord<FORMID> NAM7; //Sound - Gun - Shoot 3D Looping
        OptSimpleSubRecord<FORMID> TNAM; //Sound - Melee - Swing / Gun - No Ammo
        OptSimpleSubRecord<FORMID> NAM6; //Sound - Block
        OptSimpleSubRecord<FORMID> UNAM; //Sound - Idle
        OptSimpleSubRecord<FORMID> NAM9; //Sound - Equip
        OptSimpleSubRecord<FORMID> NAM8; //Sound - Unequip
        OptSimpleSubRecord<FORMID> WMS11; //Sound - Mod 1 - Shoot 3D
        OptSimpleSubRecord<FORMID> WMS12; //Sound - Mod 1 - Shoot Dist
        OptSimpleSubRecord<FORMID> WMS2; //Sound - Mod 1 - Shoot 2D
        ReqSubRecord<WEAPDATA> DATA; //Basic Weapon Data
        ReqSubRecord<WEAPDNAM> DNAM; //Advanced Weapon Data
        ReqSubRecord<WEAPCRDT> CRDT; //Critical Data
        ReqSubRecord<WEAPVATS> VATS; //VATS
        ReqSimpleSubRecord<UINT32> VNAM; //Sound Level

        WEAPRecord(unsigned char *_recData=NULL);
        WEAPRecord(WEAPRecord *srcRecord);
        ~WEAPRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNotNormalWeapon();
        void   IsNotNormalWeapon(bool value);
        bool   IsAutomatic();
        void   IsAutomatic(bool value);
        bool   IsHasScope();
        void   IsHasScope(bool value);
        bool   IsCantDrop();
        void   IsCantDrop(bool value);
        bool   IsHideBackpack();
        void   IsHideBackpack(bool value);
        bool   IsEmbeddedWeapon();
        void   IsEmbeddedWeapon(bool value);
        bool   IsDontUse1stPersonISAnimations();
        void   IsDontUse1stPersonISAnimations(bool value);
        bool   IsNonPlayable();
        void   IsNonPlayable(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsPlayerOnly();
        void   IsPlayerOnly(bool value);
        bool   IsNPCsUseAmmo();
        void   IsNPCsUseAmmo(bool value);
        bool   IsNoJamAfterReload();
        void   IsNoJamAfterReload(bool value);
        bool   IsOverrideActionPoints();
        void   IsOverrideActionPoints(bool value);
        bool   IsMinorCrime();
        void   IsMinorCrime(bool value);
        bool   IsRangeFixed();
        void   IsRangeFixed(bool value);
        bool   IsNotUsedInNormalCombat();
        void   IsNotUsedInNormalCombat(bool value);
        bool   IsOverrideDamageToWeaponMult();
        void   IsOverrideDamageToWeaponMult(bool value);
        bool   IsDontUse3rdPersonISAnimations();
        void   IsDontUse3rdPersonISAnimations(bool value);
        bool   IsShortBurst();
        void   IsShortBurst(bool value);
        bool   IsRumbleAlternate();
        void   IsRumbleAlternate(bool value);
        bool   IsLongBurst();
        void   IsLongBurst(bool value);
        bool   IsScopeHasNightVision();
        void   IsScopeHasNightVision(bool value);
        bool   IsScopeFromMod();
        void   IsScopeFromMod(bool value);
        bool   IsAdvFlagMask(UINT32 Mask, bool Exact=false);
        void   SetAdvFlagMask(UINT32 Mask);

        bool   IsCritOnDeath();
        void   IsCritOnDeath(bool value);
        bool   IsCritFlagMask(UINT8 Mask, bool Exact=false);
        void   SetCritFlagMask(UINT8 Mask);

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
        bool   IsEdible();
        void   IsEdible(bool value);
        bool   IsAlcohol();
        void   IsAlcohol(bool value);
        bool   IsEquipmentType(SINT32 Type);
        void   SetEquipmentType(SINT32 Type);

        bool   IsHand2Hand();
        void   IsHand2Hand(bool value);
        bool   IsMelee1Hand();
        void   IsMelee1Hand(bool value);
        bool   IsMelee2Hand();
        void   IsMelee2Hand(bool value);
        bool   IsPistolBallistic1Hand();
        void   IsPistolBallistic1Hand(bool value);
        bool   IsPistolEnergy1Hand();
        void   IsPistolEnergy1Hand(bool value);
        bool   IsRifleBallistic2Hand();
        void   IsRifleBallistic2Hand(bool value);
        bool   IsRifleAutomatic2Hand();
        void   IsRifleAutomatic2Hand(bool value);
        bool   IsRifleEnergy2Hand();
        void   IsRifleEnergy2Hand(bool value);
        bool   IsHandle2Hand();
        void   IsHandle2Hand(bool value);
        bool   IsLauncher2Hand();
        void   IsLauncher2Hand(bool value);
        bool   IsGrenadeThrow1Hand();
        void   IsGrenadeThrow1Hand(bool value);
        bool   IsLandMine1Hand();
        void   IsLandMine1Hand(bool value);
        bool   IsMineDrop1Hand();
        void   IsMineDrop1Hand(bool value);
        bool   IsThrown1Hand();
        void   IsThrown1Hand(bool value);
        bool   IsType(UINT32 Type);
        void   SetType(UINT32 Type);

        bool   IsGripHandGrip1();
        void   IsGripHandGrip1(bool value);
        bool   IsGripHandGrip2();
        void   IsGripHandGrip2(bool value);
        bool   IsGripHandGrip3();
        void   IsGripHandGrip3(bool value);
        bool   IsGripHandGrip4();
        void   IsGripHandGrip4(bool value);
        bool   IsGripHandGrip5();
        void   IsGripHandGrip5(bool value);
        bool   IsGripHandGrip6();
        void   IsGripHandGrip6(bool value);
        bool   IsGripDefault();
        void   IsGripDefault(bool value);
        bool   IsGripType(UINT8 Type);
        void   SetGripType(UINT8 Type);

        bool   IsReloadA();
        void   IsReloadA(bool value);
        bool   IsReloadB();
        void   IsReloadB(bool value);
        bool   IsReloadC();
        void   IsReloadC(bool value);
        bool   IsReloadD();
        void   IsReloadD(bool value);
        bool   IsReloadE();
        void   IsReloadE(bool value);
        bool   IsReloadF();
        void   IsReloadF(bool value);
        bool   IsReloadG();
        void   IsReloadG(bool value);
        bool   IsReloadH();
        void   IsReloadH(bool value);
        bool   IsReloadI();
        void   IsReloadI(bool value);
        bool   IsReloadJ();
        void   IsReloadJ(bool value);
        bool   IsReloadK();
        void   IsReloadK(bool value);
        bool   IsReloadL();
        void   IsReloadL(bool value);
        bool   IsReloadM();
        void   IsReloadM(bool value);
        bool   IsReloadN();
        void   IsReloadN(bool value);
        bool   IsReloadO();
        void   IsReloadO(bool value);
        bool   IsReloadP();
        void   IsReloadP(bool value);
        bool   IsReloadQ();
        void   IsReloadQ(bool value);
        bool   IsReloadR();
        void   IsReloadR(bool value);
        bool   IsReloadS();
        void   IsReloadS(bool value);
        bool   IsReloadW();
        void   IsReloadW(bool value);
        bool   IsReloadX();
        void   IsReloadX(bool value);
        bool   IsReloadY();
        void   IsReloadY(bool value);
        bool   IsReloadZ();
        void   IsReloadZ(bool value);
        bool   IsReloadType(UINT8 Type);
        void   SetReloadType(UINT8 Type);

        bool   IsAttackLeft();
        void   IsAttackLeft(bool value);
        bool   IsAttackRight();
        void   IsAttackRight(bool value);
        bool   IsAttack3();
        void   IsAttack3(bool value);
        bool   IsAttack4();
        void   IsAttack4(bool value);
        bool   IsAttack5();
        void   IsAttack5(bool value);
        bool   IsAttack6();
        void   IsAttack6(bool value);
        bool   IsAttack7();
        void   IsAttack7(bool value);
        bool   IsAttack8();
        void   IsAttack8(bool value);
        bool   IsAttack9();
        void   IsAttack9(bool value);
        bool   IsAttackLoop();
        void   IsAttackLoop(bool value);
        bool   IsAttackSpin();
        void   IsAttackSpin(bool value);
        bool   IsAttackSpin2();
        void   IsAttackSpin2(bool value);
        bool   IsAttackThrow();
        void   IsAttackThrow(bool value);
        bool   IsAttackThrow2();
        void   IsAttackThrow2(bool value);
        bool   IsAttackThrow3();
        void   IsAttackThrow3(bool value);
        bool   IsAttackThrow4();
        void   IsAttackThrow4(bool value);
        bool   IsAttackThrow5();
        void   IsAttackThrow5(bool value);
        bool   IsAttackThrow6();
        void   IsAttackThrow6(bool value);
        bool   IsAttackThrow7();
        void   IsAttackThrow7(bool value);
        bool   IsAttackThrow8();
        void   IsAttackThrow8(bool value);
        bool   IsAttackPlaceMine();
        void   IsAttackPlaceMine(bool value);
        bool   IsAttackPlaceMine2();
        void   IsAttackPlaceMine2(bool value);
        bool   IsAttackDefault();
        void   IsAttackDefault(bool value);
        bool   IsAttackType(UINT8 Type);
        void   SetAttackType(UINT8 Type);

        bool   IsEmbeddedAVPerception();
        void   IsEmbeddedAVPerception(bool value);
        bool   IsEmbeddedAVEndurance();
        void   IsEmbeddedAVEndurance(bool value);
        bool   IsEmbeddedAVLeftAttack();
        void   IsEmbeddedAVLeftAttack(bool value);
        bool   IsEmbeddedAVRightAttack();
        void   IsEmbeddedAVRightAttack(bool value);
        bool   IsEmbeddedAVLeftMobility();
        void   IsEmbeddedAVLeftMobility(bool value);
        bool   IsEmbeddedAVRightMobilty();
        void   IsEmbeddedAVRightMobilty(bool value);
        bool   IsEmbeddedAVBrain();
        void   IsEmbeddedAVBrain(bool value);
        bool   IsEmbeddedAVType(UINT8 Type);
        void   SetEmbeddedAVType(UINT8 Type);

        bool   IsOnHitNormalFormulaBehavior();
        void   IsOnHitNormalFormulaBehavior(bool value);
        bool   IsOnHitDismemberOnly();
        void   IsOnHitDismemberOnly(bool value);
        bool   IsOnHitExplodeOnly();
        void   IsOnHitExplodeOnly(bool value);
        bool   IsOnHitNoDismemberExplode();
        void   IsOnHitNoDismemberExplode(bool value);
        bool   IsOnHitType(UINT32 Type);
        void   SetOnHitType(UINT32 Type);

        bool   IsRumbleConstant();
        void   IsRumbleConstant(bool value);
        bool   IsRumbleSquare();
        void   IsRumbleSquare(bool value);
        bool   IsRumbleTriangle();
        void   IsRumbleTriangle(bool value);
        bool   IsRumbleSawtooth();
        void   IsRumbleSawtooth(bool value);
        bool   IsRumbleType(UINT32 Type);
        void   SetRumbleType(UINT32 Type);

        bool   IsPowerAttackAnimOverrideUnknown0();
        void   IsPowerAttackAnimOverrideUnknown0(bool value);
        bool   IsPowerAttackAnimOverrideAttackCustom1Power();
        void   IsPowerAttackAnimOverrideAttackCustom1Power(bool value);
        bool   IsPowerAttackAnimOverrideAttackCustom2Power();
        void   IsPowerAttackAnimOverrideAttackCustom2Power(bool value);
        bool   IsPowerAttackAnimOverrideAttackCustom3Power();
        void   IsPowerAttackAnimOverrideAttackCustom3Power(bool value);
        bool   IsPowerAttackAnimOverrideAttackCustom4Power();
        void   IsPowerAttackAnimOverrideAttackCustom4Power(bool value);
        bool   IsPowerAttackAnimOverrideAttackCustom5Power();
        void   IsPowerAttackAnimOverrideAttackCustom5Power(bool value);
        bool   IsPowerAttackAnimOverrideDefault();
        void   IsPowerAttackAnimOverrideDefault(bool value);
        bool   IsPowerAttackAnimOverrideType(UINT32 Type);
        void   SetPowerAttackAnimOverrideType(UINT32 Type);

        bool   IsModReloadA();
        void   IsModReloadA(bool value);
        bool   IsModReloadB();
        void   IsModReloadB(bool value);
        bool   IsModReloadC();
        void   IsModReloadC(bool value);
        bool   IsModReloadD();
        void   IsModReloadD(bool value);
        bool   IsModReloadE();
        void   IsModReloadE(bool value);
        bool   IsModReloadF();
        void   IsModReloadF(bool value);
        bool   IsModReloadG();
        void   IsModReloadG(bool value);
        bool   IsModReloadH();
        void   IsModReloadH(bool value);
        bool   IsModReloadI();
        void   IsModReloadI(bool value);
        bool   IsModReloadJ();
        void   IsModReloadJ(bool value);
        bool   IsModReloadK();
        void   IsModReloadK(bool value);
        bool   IsModReloadL();
        void   IsModReloadL(bool value);
        bool   IsModReloadM();
        void   IsModReloadM(bool value);
        bool   IsModReloadN();
        void   IsModReloadN(bool value);
        bool   IsModReloadO();
        void   IsModReloadO(bool value);
        bool   IsModReloadP();
        void   IsModReloadP(bool value);
        bool   IsModReloadQ();
        void   IsModReloadQ(bool value);
        bool   IsModReloadR();
        void   IsModReloadR(bool value);
        bool   IsModReloadS();
        void   IsModReloadS(bool value);
        bool   IsModReloadW();
        void   IsModReloadW(bool value);
        bool   IsModReloadX();
        void   IsModReloadX(bool value);
        bool   IsModReloadY();
        void   IsModReloadY(bool value);
        bool   IsModReloadZ();
        void   IsModReloadZ(bool value);
        bool   IsModType(UINT8 Type);
        void   SetModType(UINT8 Type);

        bool   IsVATSNotSilent();
        void   IsVATSNotSilent(bool value);
        bool   IsVATSSilent();
        void   IsVATSSilent(bool value);
        bool   IsVATSSilenceType(UINT8 Type);
        void   SetVATSSilenceType(UINT8 Type);

        bool   IsVATSModNotRequired();
        void   IsVATSModNotRequired(bool value);
        bool   IsVATSModRequired();
        void   IsVATSModRequired(bool value);
        bool   IsVATSModType(UINT8 Type);
        void   SetVATSModType(UINT8 Type);

        bool   IsLoud();
        void   IsLoud(bool value);
        bool   IsNormal();
        void   IsNormal(bool value);
        bool   IsSilent();
        void   IsSilent(bool value);
        bool   IsSoundLevelType(UINT32 Type);
        void   SetSoundLevelType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const WEAPRecord &other) const;
        bool operator !=(const WEAPRecord &other) const;
        bool equals(Record *other);
    };
}