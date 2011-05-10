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
#include "..\..\Common.h"
#include "WEAPRecord.h"

namespace FNV
{
WEAPRecord::WEAPDATA::WEAPDATA():
    value(0),
    health(0),
    weight(0.0f),
    damage(0),
    clipSize(0)
    {
    //
    }

WEAPRecord::WEAPDATA::~WEAPDATA()
    {
    //
    }

bool WEAPRecord::WEAPDATA::operator ==(const WEAPDATA &other) const
    {
    return (value == other.value &&
            health == other.health &&
            damage == other.damage &&
            clipSize == other.clipSize &&
            AlmostEqual(weight,other.weight,2));
    }

bool WEAPRecord::WEAPDATA::operator !=(const WEAPDATA &other) const
    {
    return !(*this == other);
    }

WEAPRecord::WEAPDNAM::WEAPDNAM():
    animType(0),
    animMult(0.0f),
    reach(0.0f),
    flags1(0),
    gripAnim(0),
    ammoUse(0),
    reloadAnim(0),
    minSpread(0.0f),
    spread(0.0f),
    unknown1(0.0f),
    sightFOV(0.0f),
    unknown2(0.0f),
    projectile(0),
    VATSHitChance(0),
    attackAnim(0),
    projectileCount(0),
    weaponAV(0),
    minRange(0.0f),
    maxRange(0.0f),
    onHit(0),
    flags2(0),
    animAttackMult(0.0f),
    fireRate(0.0f),
    overrideAP(0.0f),
    leftRumble(0.0f),
    rightRumble(0.0f),
    timeRumble(0.0f),
    overrideDamageToWeapon(0.0f),
    shotsPerSecond(0.0f),
    reloadTime(0.0f),
    jamTime(0.0f),
    aimArc(0.0f),
    skill(0),
    rumbleType(0),
    rumbleWavelength(0.0f),
    limbDamageMult(0.0f),
    resistType(0),
    sightUsage(0.0f),
    semiFireDelayMin(0.0f),
    semiFireDelayMax(0.0f),
    unknown3(0.0f),
    effectMod1(0),
    effectMod2(0),
    effectMod3(0),
    valueAMod1(0.0f),
    valueAMod2(0.0f),
    valueAMod3(0.0f),
    overridePwrAtkAnim(0),
    strengthReq(0),
    unknown4(0),
    reloadAnimMod(0),
    regenRate(0.0f),
    killImpulse(0.0f),
    valueBMod1(0.0f),
    valueBMod2(0.0f),
    valueBMod3(0.0f),
    impulseDist(0.0f),
    skillReq(0)
    {
    memset(&unknown5[0], 0x00, 2);
    }

WEAPRecord::WEAPDNAM::~WEAPDNAM()
    {
    //
    }

bool WEAPRecord::WEAPDNAM::operator ==(const WEAPDNAM &other) const
    {
    return (animType == other.animType &&
            flags1 == other.flags1 &&
            gripAnim == other.gripAnim &&
            ammoUse == other.ammoUse &&
            reloadAnim == other.reloadAnim &&
            projectile == other.projectile &&
            VATSHitChance == other.VATSHitChance &&
            attackAnim == other.attackAnim &&
            projectileCount == other.projectileCount &&
            weaponAV == other.weaponAV &&
            onHit == other.onHit &&
            flags2 == other.flags2 &&
            skill == other.skill &&
            rumbleType == other.rumbleType &&
            resistType == other.resistType &&
            effectMod1 == other.effectMod1 &&
            effectMod2 == other.effectMod2 &&
            effectMod3 == other.effectMod3 &&
            overridePwrAtkAnim == other.overridePwrAtkAnim &&
            strengthReq == other.strengthReq &&
            unknown4 == other.unknown4 &&
            reloadAnimMod == other.reloadAnimMod &&
            skillReq == other.skillReq &&
            unknown5[0] == other.unknown5[0] &&
            unknown5[1] == other.unknown5[1] &&
            AlmostEqual(animMult,other.animMult,2) &&
            AlmostEqual(reach,other.reach,2) &&
            AlmostEqual(minSpread,other.minSpread,2) &&
            AlmostEqual(spread,other.spread,2) &&
            AlmostEqual(unknown1,other.unknown1,2) &&
            AlmostEqual(sightFOV,other.sightFOV,2) &&
            AlmostEqual(unknown2,other.unknown2,2) &&
            AlmostEqual(minRange,other.minRange,2) &&
            AlmostEqual(maxRange,other.maxRange,2) &&
            AlmostEqual(animAttackMult,other.animAttackMult,2) &&
            AlmostEqual(fireRate,other.fireRate,2) &&
            AlmostEqual(overrideAP,other.overrideAP,2) &&
            AlmostEqual(leftRumble,other.leftRumble,2) &&
            AlmostEqual(rightRumble,other.rightRumble,2) &&
            AlmostEqual(timeRumble,other.timeRumble,2) &&
            AlmostEqual(overrideDamageToWeapon,other.overrideDamageToWeapon,2) &&
            AlmostEqual(shotsPerSecond,other.shotsPerSecond,2) &&
            AlmostEqual(reloadTime,other.reloadTime,2) &&
            AlmostEqual(jamTime,other.jamTime,2) &&
            AlmostEqual(aimArc,other.aimArc,2) &&
            AlmostEqual(rumbleWavelength,other.rumbleWavelength,2) &&
            AlmostEqual(limbDamageMult,other.limbDamageMult,2) &&
            AlmostEqual(sightUsage,other.sightUsage,2) &&
            AlmostEqual(semiFireDelayMin,other.semiFireDelayMin,2) &&
            AlmostEqual(semiFireDelayMax,other.semiFireDelayMax,2) &&
            AlmostEqual(unknown3,other.unknown3,2) &&
            AlmostEqual(valueAMod1,other.valueAMod1,2) &&
            AlmostEqual(valueAMod2,other.valueAMod2,2) &&
            AlmostEqual(valueAMod3,other.valueAMod3,2) &&
            AlmostEqual(regenRate,other.regenRate,2) &&
            AlmostEqual(killImpulse,other.killImpulse,2) &&
            AlmostEqual(valueBMod1,other.valueBMod1,2) &&
            AlmostEqual(valueBMod2,other.valueBMod2,2) &&
            AlmostEqual(valueBMod3,other.valueBMod3,2) &&
            AlmostEqual(impulseDist,other.impulseDist,2));
    }

bool WEAPRecord::WEAPDNAM::operator !=(const WEAPDNAM &other) const
    {
    return !(*this == other);
    }

WEAPRecord::WEAPCRDT::WEAPCRDT():
    critDamage(0),
    critMult(0.0f),
    flags(0),
    effect(0)
    {
    memset(&unused1[0], 0x00, 2);
    memset(&unused2[0], 0x00, 3);
    }

WEAPRecord::WEAPCRDT::~WEAPCRDT()
    {
    //
    }

bool WEAPRecord::WEAPCRDT::operator ==(const WEAPCRDT &other) const
    {
    return (critDamage == other.critDamage &&
            flags == other.flags &&
            effect == other.effect &&
            AlmostEqual(critMult,other.critMult,2));
    }

bool WEAPRecord::WEAPCRDT::operator !=(const WEAPCRDT &other) const
    {
    return !(*this == other);
    }

WEAPRecord::WEAPVATS::WEAPVATS():
    effect(0),
    skill(0.0f),
    damageMult(0.0f),
    AP(0.0f),
    silenceType(0),
    modRequiredType(0)
    {
    memset(&unused1[0], 0x00, 2);
    }

WEAPRecord::WEAPVATS::~WEAPVATS()
    {
    //
    }

bool WEAPRecord::WEAPVATS::operator ==(const WEAPVATS &other) const
    {
    return (effect == other.effect &&
            silenceType == other.silenceType &&
            modRequiredType == other.modRequiredType &&
            AlmostEqual(skill,other.skill,2) &&
            AlmostEqual(damageMult,other.damageMult,2) &&
            AlmostEqual(AP,other.AP,2));
    }

bool WEAPRecord::WEAPVATS::operator !=(const WEAPVATS &other) const
    {
    return !(*this == other);
    }

WEAPRecord::WEAPRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

WEAPRecord::WEAPRecord(WEAPRecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SCRI = srcRecord->SCRI;
    EITM = srcRecord->EITM;
    EAMT = srcRecord->EAMT;
    NAM0 = srcRecord->NAM0;
    Destructable = srcRecord->Destructable;
    REPL = srcRecord->REPL;
    ETYP = srcRecord->ETYP;
    BIPL = srcRecord->BIPL;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    MOD2 = srcRecord->MOD2;
    MOD3 = srcRecord->MOD3;
    EFSD = srcRecord->EFSD;
    MOD4 = srcRecord->MOD4;
    VANM = srcRecord->VANM;
    NNAM = srcRecord->NNAM;
    MWD1 = srcRecord->MWD1;
    MWD2 = srcRecord->MWD2;
    MWD3 = srcRecord->MWD3;
    MWD4 = srcRecord->MWD4;
    MWD5 = srcRecord->MWD5;
    MWD6 = srcRecord->MWD6;
    MWD7 = srcRecord->MWD7;
    INAM = srcRecord->INAM;
    WNAM = srcRecord->WNAM;
    WNM1 = srcRecord->WNM1;
    WNM2 = srcRecord->WNM2;
    WNM3 = srcRecord->WNM3;
    WNM4 = srcRecord->WNM4;
    WNM5 = srcRecord->WNM5;
    WNM6 = srcRecord->WNM6;
    WNM7 = srcRecord->WNM7;
    WMI1 = srcRecord->WMI1;
    WMI2 = srcRecord->WMI2;
    WMI3 = srcRecord->WMI3;
    SNAM1 = srcRecord->SNAM1;
    SNAM2 = srcRecord->SNAM2;
    XNAM = srcRecord->XNAM;
    NAM7 = srcRecord->NAM7;
    TNAM = srcRecord->TNAM;
    NAM6 = srcRecord->NAM6;
    UNAM = srcRecord->UNAM;
    NAM9 = srcRecord->NAM9;
    NAM8 = srcRecord->NAM8;
    WMS11 = srcRecord->WMS11;
    WMS12 = srcRecord->WMS12;
    WMS2 = srcRecord->WMS2;
    DATA = srcRecord->DATA;
    DNAM = srcRecord->DNAM;
    CRDT = srcRecord->CRDT;
    VATS = srcRecord->VATS;
    VNAM = srcRecord->VNAM;
    return;
    }

WEAPRecord::~WEAPRecord()
    {
    //
    }

bool WEAPRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(EITM.IsLoaded())
        op.Accept(EITM.value);
    if(NAM0.IsLoaded())
        op.Accept(NAM0.value);
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(REPL.IsLoaded())
        op.Accept(REPL.value);
    if(BIPL.IsLoaded())
        op.Accept(BIPL.value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    if(MOD2.IsLoaded())
        {
        for(UINT32 x = 0; x < MOD2->Textures.MODS.size(); x++)
            op.Accept(MOD2->Textures.MODS[x]->texture);
        }
    if(MOD3.IsLoaded())
        {
        for(UINT32 x = 0; x < MOD3->Textures.MODS.size(); x++)
            op.Accept(MOD3->Textures.MODS[x]->texture);
        }
    if(EFSD.IsLoaded())
        op.Accept(EFSD.value);
    if(MOD4.IsLoaded())
        {
        for(UINT32 x = 0; x < MOD4->Textures.MODS.size(); x++)
            op.Accept(MOD4->Textures.MODS[x]->texture);
        }
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);
    if(WNM1.IsLoaded())
        op.Accept(WNM1.value);
    if(WNM2.IsLoaded())
        op.Accept(WNM2.value);
    if(WNM3.IsLoaded())
        op.Accept(WNM3.value);
    if(WNM4.IsLoaded())
        op.Accept(WNM4.value);
    if(WNM5.IsLoaded())
        op.Accept(WNM5.value);
    if(WNM6.IsLoaded())
        op.Accept(WNM6.value);
    if(WNM7.IsLoaded())
        op.Accept(WNM7.value);
    if(WMI1.IsLoaded())
        op.Accept(WMI1.value);
    if(WMI2.IsLoaded())
        op.Accept(WMI2.value);
    if(WMI3.IsLoaded())
        op.Accept(WMI3.value);
    if(SNAM1.IsLoaded())
        op.Accept(SNAM1.value);
    if(SNAM2.IsLoaded())
        op.Accept(SNAM2.value);
    if(XNAM.IsLoaded())
        op.Accept(XNAM.value);
    if(NAM7.IsLoaded())
        op.Accept(NAM7.value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM.value);
    if(NAM6.IsLoaded())
        op.Accept(NAM6.value);
    if(UNAM.IsLoaded())
        op.Accept(UNAM.value);
    if(NAM9.IsLoaded())
        op.Accept(NAM9.value);
    if(NAM8.IsLoaded())
        op.Accept(NAM8.value);
    if(WMS11.IsLoaded())
        op.Accept(WMS11.value);
    if(WMS12.IsLoaded())
        op.Accept(WMS12.value);
    if(WMS2.IsLoaded())
        op.Accept(WMS2.value);
    op.Accept(DNAM.value.projectile);
    op.Accept(CRDT.value.effect);
    op.Accept(VATS.value.effect);
    return op.Stop();
    }

bool WEAPRecord::IsNotNormalWeapon()
    {
    return (DNAM.value.flags1 & fIsNotNormalWeapon) != 0;
    }

void WEAPRecord::IsNotNormalWeapon(bool value)
    {
    DNAM.value.flags1 = value ? (DNAM.value.flags1 | fIsNotNormalWeapon) : (DNAM.value.flags1 & ~fIsNotNormalWeapon);
    }

bool WEAPRecord::IsAutomatic()
    {
    return (DNAM.value.flags1 & fIsAutomatic) != 0;
    }

void WEAPRecord::IsAutomatic(bool value)
    {
    DNAM.value.flags1 = value ? (DNAM.value.flags1 | fIsAutomatic) : (DNAM.value.flags1 & ~fIsAutomatic);
    }

bool WEAPRecord::IsHasScope()
    {
    return (DNAM.value.flags1 & fIsHasScope) != 0;
    }

void WEAPRecord::IsHasScope(bool value)
    {
    DNAM.value.flags1 = value ? (DNAM.value.flags1 | fIsHasScope) : (DNAM.value.flags1 & ~fIsHasScope);
    }

bool WEAPRecord::IsCantDrop()
    {
    return (DNAM.value.flags1 & fIsCantDrop) != 0;
    }

void WEAPRecord::IsCantDrop(bool value)
    {
    DNAM.value.flags1 = value ? (DNAM.value.flags1 | fIsCantDrop) : (DNAM.value.flags1 & ~fIsCantDrop);
    }

bool WEAPRecord::IsHideBackpack()
    {
    return (DNAM.value.flags1 & fIsHideBackpack) != 0;
    }

void WEAPRecord::IsHideBackpack(bool value)
    {
    DNAM.value.flags1 = value ? (DNAM.value.flags1 | fIsHideBackpack) : (DNAM.value.flags1 & ~fIsHideBackpack);
    }

bool WEAPRecord::IsEmbeddedWeapon()
    {
    return (DNAM.value.flags1 & fIsEmbeddedWeapon) != 0;
    }

void WEAPRecord::IsEmbeddedWeapon(bool value)
    {
    DNAM.value.flags1 = value ? (DNAM.value.flags1 | fIsEmbeddedWeapon) : (DNAM.value.flags1 & ~fIsEmbeddedWeapon);
    }

bool WEAPRecord::IsDontUse1stPersonISAnimations()
    {
    return (DNAM.value.flags1 & fIsDontUse1stPersonISAnimations) != 0;
    }

void WEAPRecord::IsDontUse1stPersonISAnimations(bool value)
    {
    DNAM.value.flags1 = value ? (DNAM.value.flags1 | fIsDontUse1stPersonISAnimations) : (DNAM.value.flags1 & ~fIsDontUse1stPersonISAnimations);
    }

bool WEAPRecord::IsNonPlayable()
    {
    return (DNAM.value.flags1 & fIsNonPlayable) != 0;
    }

void WEAPRecord::IsNonPlayable(bool value)
    {
    DNAM.value.flags1 = value ? (DNAM.value.flags1 | fIsNonPlayable) : (DNAM.value.flags1 & ~fIsNonPlayable);
    }

bool WEAPRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DNAM.value.flags1 & Mask) == Mask) : ((DNAM.value.flags1 & Mask) != 0);
    }

void WEAPRecord::SetFlagMask(UINT8 Mask)
    {
    DNAM.value.flags1 = Mask;
    }

bool WEAPRecord::IsPlayerOnly()
    {
    return (DNAM.value.flags2 & fIsPlayerOnly) != 0;
    }

void WEAPRecord::IsPlayerOnly(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsPlayerOnly) : (DNAM.value.flags2 & ~fIsPlayerOnly);
    }

bool WEAPRecord::IsNPCsUseAmmo()
    {
    return (DNAM.value.flags2 & fIsNPCsUseAmmo) != 0;
    }

void WEAPRecord::IsNPCsUseAmmo(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsNPCsUseAmmo) : (DNAM.value.flags2 & ~fIsNPCsUseAmmo);
    }

bool WEAPRecord::IsNoJamAfterReload()
    {
    return (DNAM.value.flags2 & fIsNoJamAfterReload) != 0;
    }

void WEAPRecord::IsNoJamAfterReload(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsNoJamAfterReload) : (DNAM.value.flags2 & ~fIsNoJamAfterReload);
    }

bool WEAPRecord::IsOverrideActionPoints()
    {
    return (DNAM.value.flags2 & fIsOverrideActionPoints) != 0;
    }

void WEAPRecord::IsOverrideActionPoints(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsOverrideActionPoints) : (DNAM.value.flags2 & ~fIsOverrideActionPoints);
    }

bool WEAPRecord::IsMinorCrime()
    {
    return (DNAM.value.flags2 & fIsMinorCrime) != 0;
    }

void WEAPRecord::IsMinorCrime(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsMinorCrime) : (DNAM.value.flags2 & ~fIsMinorCrime);
    }

bool WEAPRecord::IsRangeFixed()
    {
    return (DNAM.value.flags2 & fIsRangeFixed) != 0;
    }

void WEAPRecord::IsRangeFixed(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsRangeFixed) : (DNAM.value.flags2 & ~fIsRangeFixed);
    }

bool WEAPRecord::IsNotUsedInNormalCombat()
    {
    return (DNAM.value.flags2 & fIsNotUsedInNormalCombat) != 0;
    }

void WEAPRecord::IsNotUsedInNormalCombat(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsNotUsedInNormalCombat) : (DNAM.value.flags2 & ~fIsNotUsedInNormalCombat);
    }

bool WEAPRecord::IsOverrideDamageToWeaponMult()
    {
    return (DNAM.value.flags2 & fIsOverrideDamageToWeaponMult) != 0;
    }

void WEAPRecord::IsOverrideDamageToWeaponMult(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsOverrideDamageToWeaponMult) : (DNAM.value.flags2 & ~fIsOverrideDamageToWeaponMult);
    }

bool WEAPRecord::IsDontUse3rdPersonISAnimations()
    {
    return (DNAM.value.flags2 & fIsDontUse3rdPersonISAnimations) != 0;
    }

void WEAPRecord::IsDontUse3rdPersonISAnimations(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsDontUse3rdPersonISAnimations) : (DNAM.value.flags2 & ~fIsDontUse3rdPersonISAnimations);
    }

bool WEAPRecord::IsShortBurst()
    {
    return (DNAM.value.flags2 & fIsShortBurst) != 0;
    }

void WEAPRecord::IsShortBurst(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsShortBurst) : (DNAM.value.flags2 & ~fIsShortBurst);
    }

bool WEAPRecord::IsRumbleAlternate()
    {
    return (DNAM.value.flags2 & fIsRumbleAlternate) != 0;
    }

void WEAPRecord::IsRumbleAlternate(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsRumbleAlternate) : (DNAM.value.flags2 & ~fIsRumbleAlternate);
    }

bool WEAPRecord::IsLongBurst()
    {
    return (DNAM.value.flags2 & fIsLongBurst) != 0;
    }

void WEAPRecord::IsLongBurst(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsLongBurst) : (DNAM.value.flags2 & ~fIsLongBurst);
    }

bool WEAPRecord::IsScopeHasNightVision()
    {
    return (DNAM.value.flags2 & fIsScopeHasNightVision) != 0;
    }

void WEAPRecord::IsScopeHasNightVision(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsScopeHasNightVision) : (DNAM.value.flags2 & ~fIsScopeHasNightVision);
    }

bool WEAPRecord::IsScopeFromMod()
    {
    return (DNAM.value.flags2 & fIsScopeFromMod) != 0;
    }

void WEAPRecord::IsScopeFromMod(bool value)
    {
    DNAM.value.flags2 = value ? (DNAM.value.flags2 | fIsScopeFromMod) : (DNAM.value.flags2 & ~fIsScopeFromMod);
    }

bool WEAPRecord::IsAdvFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((DNAM.value.flags2 & Mask) == Mask) : ((DNAM.value.flags2 & Mask) != 0);
    }

void WEAPRecord::SetAdvFlagMask(UINT32 Mask)
    {
    DNAM.value.flags2 = Mask;
    }

bool WEAPRecord::IsCritOnDeath()
    {
    return (CRDT.value.flags & fIsOnDeath) != 0;
    }

void WEAPRecord::IsCritOnDeath(bool value)
    {
    CRDT.value.flags = value ? (CRDT.value.flags | fIsOnDeath) : (CRDT.value.flags & ~fIsOnDeath);
    }

bool WEAPRecord::IsCritFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((CRDT.value.flags & Mask) == Mask) : ((CRDT.value.flags & Mask) != 0);
    }

void WEAPRecord::SetCritFlagMask(UINT32 Mask)
    {
    CRDT.value.flags = Mask;
    }

bool WEAPRecord::IsNone()
    {
    return (ETYP.value == eNone);
    }

void WEAPRecord::IsNone(bool value)
    {
    ETYP.value = value ? eNone : eBigGuns;
    }

bool WEAPRecord::IsBigGuns()
    {
    return (ETYP.value == eBigGuns);
    }

void WEAPRecord::IsBigGuns(bool value)
    {
    ETYP.value = value ? eBigGuns : eNone;
    }

bool WEAPRecord::IsEnergyWeapons()
    {
    return (ETYP.value == eEnergyWeapons);
    }

void WEAPRecord::IsEnergyWeapons(bool value)
    {
    ETYP.value = value ? eEnergyWeapons : eNone;
    }

bool WEAPRecord::IsSmallGuns()
    {
    return (ETYP.value == eSmallGuns);
    }

void WEAPRecord::IsSmallGuns(bool value)
    {
    ETYP.value = value ? eSmallGuns : eNone;
    }

bool WEAPRecord::IsMeleeWeapons()
    {
    return (ETYP.value == eMeleeWeapons);
    }

void WEAPRecord::IsMeleeWeapons(bool value)
    {
    ETYP.value = value ? eMeleeWeapons : eNone;
    }

bool WEAPRecord::IsUnarmedWeapon()
    {
    return (ETYP.value == eUnarmedWeapon);
    }

void WEAPRecord::IsUnarmedWeapon(bool value)
    {
    ETYP.value = value ? eUnarmedWeapon : eNone;
    }

bool WEAPRecord::IsThrownWeapons()
    {
    return (ETYP.value == eThrownWeapons);
    }

void WEAPRecord::IsThrownWeapons(bool value)
    {
    ETYP.value = value ? eThrownWeapons : eNone;
    }

bool WEAPRecord::IsMine()
    {
    return (ETYP.value == eMine);
    }

void WEAPRecord::IsMine(bool value)
    {
    ETYP.value = value ? eMine : eNone;
    }

bool WEAPRecord::IsBodyWear()
    {
    return (ETYP.value == eBodyWear);
    }

void WEAPRecord::IsBodyWear(bool value)
    {
    ETYP.value = value ? eBodyWear : eNone;
    }

bool WEAPRecord::IsHeadWear()
    {
    return (ETYP.value == eHeadWear);
    }

void WEAPRecord::IsHeadWear(bool value)
    {
    ETYP.value = value ? eHeadWear : eNone;
    }

bool WEAPRecord::IsHandWear()
    {
    return (ETYP.value == eHandWear);
    }

void WEAPRecord::IsHandWear(bool value)
    {
    ETYP.value = value ? eHandWear : eNone;
    }

bool WEAPRecord::IsChems()
    {
    return (ETYP.value == eChems);
    }

void WEAPRecord::IsChems(bool value)
    {
    ETYP.value = value ? eChems : eNone;
    }

bool WEAPRecord::IsStimpack()
    {
    return (ETYP.value == eStimpack);
    }

void WEAPRecord::IsStimpack(bool value)
    {
    ETYP.value = value ? eStimpack : eNone;
    }

bool WEAPRecord::IsEdible()
    {
    return (ETYP.value == eEdible);
    }

void WEAPRecord::IsEdible(bool value)
    {
    ETYP.value = value ? eEdible : eNone;
    }

bool WEAPRecord::IsAlcohol()
    {
    return (ETYP.value == eAlcohol);
    }

void WEAPRecord::IsAlcohol(bool value)
    {
    ETYP.value = value ? eAlcohol : eNone;
    }

bool WEAPRecord::IsEquipmentType(SINT32 Type)
    {
    return ETYP.value == Type;
    }

void WEAPRecord::SetEquipmentType(SINT32 Type)
    {
    ETYP.value = Type;
    }

bool WEAPRecord::IsHand2Hand()
    {
    return (DNAM.value.animType == eHand2Hand);
    }

void WEAPRecord::IsHand2Hand(bool value)
    {
    DNAM.value.animType = value ? eHand2Hand : eMelee1Hand;
    }

bool WEAPRecord::IsMelee1Hand()
    {
    return (DNAM.value.animType == eMelee1Hand);
    }

void WEAPRecord::IsMelee1Hand(bool value)
    {
    DNAM.value.animType = value ? eMelee1Hand : eHand2Hand;
    }

bool WEAPRecord::IsMelee2Hand()
    {
    return (DNAM.value.animType == eMelee2Hand);
    }

void WEAPRecord::IsMelee2Hand(bool value)
    {
    DNAM.value.animType = value ? eMelee2Hand : eHand2Hand;
    }

bool WEAPRecord::IsPistolBallistic1Hand()
    {
    return (DNAM.value.animType == ePistolBallistic1Hand);
    }

void WEAPRecord::IsPistolBallistic1Hand(bool value)
    {
    DNAM.value.animType = value ? ePistolBallistic1Hand : eHand2Hand;
    }

bool WEAPRecord::IsPistolEnergy1Hand()
    {
    return (DNAM.value.animType == ePistolEnergy1Hand);
    }

void WEAPRecord::IsPistolEnergy1Hand(bool value)
    {
    DNAM.value.animType = value ? ePistolEnergy1Hand : eHand2Hand;
    }

bool WEAPRecord::IsRifleBallistic2Hand()
    {
    return (DNAM.value.animType == eRifleBallistic2Hand);
    }

void WEAPRecord::IsRifleBallistic2Hand(bool value)
    {
    DNAM.value.animType = value ? eRifleBallistic2Hand : eHand2Hand;
    }

bool WEAPRecord::IsRifleAutomatic2Hand()
    {
    return (DNAM.value.animType == eRifleAutomatic2Hand);
    }

void WEAPRecord::IsRifleAutomatic2Hand(bool value)
    {
    DNAM.value.animType = value ? eRifleAutomatic2Hand : eHand2Hand;
    }

bool WEAPRecord::IsRifleEnergy2Hand()
    {
    return (DNAM.value.animType == eRifleEnergy2Hand);
    }

void WEAPRecord::IsRifleEnergy2Hand(bool value)
    {
    DNAM.value.animType = value ? eRifleEnergy2Hand : eHand2Hand;
    }

bool WEAPRecord::IsHandle2Hand()
    {
    return (DNAM.value.animType == eHandle2Hand);
    }

void WEAPRecord::IsHandle2Hand(bool value)
    {
    DNAM.value.animType = value ? eHandle2Hand : eHand2Hand;
    }

bool WEAPRecord::IsLauncher2Hand()
    {
    return (DNAM.value.animType == eLauncher2Hand);
    }

void WEAPRecord::IsLauncher2Hand(bool value)
    {
    DNAM.value.animType = value ? eLauncher2Hand : eHand2Hand;
    }

bool WEAPRecord::IsGrenadeThrow1Hand()
    {
    return (DNAM.value.animType == eGrenadeThrow1Hand);
    }

void WEAPRecord::IsGrenadeThrow1Hand(bool value)
    {
    DNAM.value.animType = value ? eGrenadeThrow1Hand : eHand2Hand;
    }

bool WEAPRecord::IsLandMine1Hand()
    {
    return (DNAM.value.animType == eLandMine1Hand);
    }

void WEAPRecord::IsLandMine1Hand(bool value)
    {
    DNAM.value.animType = value ? eLandMine1Hand : eHand2Hand;
    }

bool WEAPRecord::IsMineDrop1Hand()
    {
    return (DNAM.value.animType == eMineDrop1Hand);
    }

void WEAPRecord::IsMineDrop1Hand(bool value)
    {
    DNAM.value.animType = value ? eMineDrop1Hand : eHand2Hand;
    }

bool WEAPRecord::IsThrown1Hand()
    {
    return (DNAM.value.animType == eThrown1Hand);
    }

void WEAPRecord::IsThrown1Hand(bool value)
    {
    DNAM.value.animType = value ? eThrown1Hand : eHand2Hand;
    }

bool WEAPRecord::IsType(UINT8 Type)
    {
    return DNAM.value.animType == Type;
    }

void WEAPRecord::SetType(UINT8 Type)
    {
    DNAM.value.animType = Type;
    }

bool WEAPRecord::IsGripHandGrip1()
    {
    return (DNAM.value.gripAnim == eHandGrip1);
    }

void WEAPRecord::IsGripHandGrip1(bool value)
    {
    DNAM.value.gripAnim = value ? eHandGrip1 : eHandGrip2;
    }

bool WEAPRecord::IsGripHandGrip2()
    {
    return (DNAM.value.gripAnim == eHandGrip2);
    }

void WEAPRecord::IsGripHandGrip2(bool value)
    {
    DNAM.value.gripAnim = value ? eHandGrip2 : eHandGrip1;
    }

bool WEAPRecord::IsGripHandGrip3()
    {
    return (DNAM.value.gripAnim == eHandGrip3);
    }

void WEAPRecord::IsGripHandGrip3(bool value)
    {
    DNAM.value.gripAnim = value ? eHandGrip3 : eHandGrip1;
    }

bool WEAPRecord::IsGripHandGrip4()
    {
    return (DNAM.value.gripAnim == eHandGrip4);
    }

void WEAPRecord::IsGripHandGrip4(bool value)
    {
    DNAM.value.gripAnim = value ? eHandGrip4 : eHandGrip1;
    }

bool WEAPRecord::IsGripHandGrip5()
    {
    return (DNAM.value.gripAnim == eHandGrip5);
    }

void WEAPRecord::IsGripHandGrip5(bool value)
    {
    DNAM.value.gripAnim = value ? eHandGrip5 : eHandGrip1;
    }

bool WEAPRecord::IsGripHandGrip6()
    {
    return (DNAM.value.gripAnim == eHandGrip6);
    }

void WEAPRecord::IsGripHandGrip6(bool value)
    {
    DNAM.value.gripAnim = value ? eHandGrip6 : eHandGrip1;
    }

bool WEAPRecord::IsGripDefault()
    {
    return (DNAM.value.gripAnim == eHandGripDefault);
    }

void WEAPRecord::IsGripDefault(bool value)
    {
    DNAM.value.gripAnim = value ? eHandGripDefault : eHandGrip1;
    }

bool WEAPRecord::IsGripType(UINT8 Type)
    {
    return DNAM.value.gripAnim == Type;
    }

void WEAPRecord::SetGripType(UINT8 Type)
    {
    DNAM.value.gripAnim = Type;
    }

bool WEAPRecord::IsReloadA()
    {
    return (DNAM.value.reloadAnim == eReloadA);
    }

void WEAPRecord::IsReloadA(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadA : eReloadB;
    }

bool WEAPRecord::IsReloadB()
    {
    return (DNAM.value.reloadAnim == eReloadB);
    }

void WEAPRecord::IsReloadB(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadB : eReloadA;
    }

bool WEAPRecord::IsReloadC()
    {
    return (DNAM.value.reloadAnim == eReloadC);
    }

void WEAPRecord::IsReloadC(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadC : eReloadA;
    }

bool WEAPRecord::IsReloadD()
    {
    return (DNAM.value.reloadAnim == eReloadD);
    }

void WEAPRecord::IsReloadD(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadD : eReloadA;
    }

bool WEAPRecord::IsReloadE()
    {
    return (DNAM.value.reloadAnim == eReloadE);
    }

void WEAPRecord::IsReloadE(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadE : eReloadA;
    }

bool WEAPRecord::IsReloadF()
    {
    return (DNAM.value.reloadAnim == eReloadF);
    }

void WEAPRecord::IsReloadF(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadF : eReloadA;
    }

bool WEAPRecord::IsReloadG()
    {
    return (DNAM.value.reloadAnim == eReloadG);
    }

void WEAPRecord::IsReloadG(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadG : eReloadA;
    }

bool WEAPRecord::IsReloadH()
    {
    return (DNAM.value.reloadAnim == eReloadH);
    }

void WEAPRecord::IsReloadH(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadH : eReloadA;
    }

bool WEAPRecord::IsReloadI()
    {
    return (DNAM.value.reloadAnim == eReloadI);
    }

void WEAPRecord::IsReloadI(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadI : eReloadA;
    }

bool WEAPRecord::IsReloadJ()
    {
    return (DNAM.value.reloadAnim == eReloadJ);
    }

void WEAPRecord::IsReloadJ(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadJ : eReloadA;
    }

bool WEAPRecord::IsReloadK()
    {
    return (DNAM.value.reloadAnim == eReloadK);
    }

void WEAPRecord::IsReloadK(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadK : eReloadA;
    }

bool WEAPRecord::IsReloadL()
    {
    return (DNAM.value.reloadAnim == eReloadL);
    }

void WEAPRecord::IsReloadL(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadL : eReloadA;
    }

bool WEAPRecord::IsReloadM()
    {
    return (DNAM.value.reloadAnim == eReloadM);
    }

void WEAPRecord::IsReloadM(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadM : eReloadA;
    }

bool WEAPRecord::IsReloadN()
    {
    return (DNAM.value.reloadAnim == eReloadN);
    }

void WEAPRecord::IsReloadN(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadN : eReloadA;
    }

bool WEAPRecord::IsReloadO()
    {
    return (DNAM.value.reloadAnim == eReloadO);
    }

void WEAPRecord::IsReloadO(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadO : eReloadA;
    }

bool WEAPRecord::IsReloadP()
    {
    return (DNAM.value.reloadAnim == eReloadP);
    }

void WEAPRecord::IsReloadP(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadP : eReloadA;
    }

bool WEAPRecord::IsReloadQ()
    {
    return (DNAM.value.reloadAnim == eReloadQ);
    }

void WEAPRecord::IsReloadQ(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadQ : eReloadA;
    }

bool WEAPRecord::IsReloadR()
    {
    return (DNAM.value.reloadAnim == eReloadR);
    }

void WEAPRecord::IsReloadR(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadR : eReloadA;
    }

bool WEAPRecord::IsReloadS()
    {
    return (DNAM.value.reloadAnim == eReloadS);
    }

void WEAPRecord::IsReloadS(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadS : eReloadA;
    }

bool WEAPRecord::IsReloadW()
    {
    return (DNAM.value.reloadAnim == eReloadW);
    }

void WEAPRecord::IsReloadW(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadW : eReloadA;
    }

bool WEAPRecord::IsReloadX()
    {
    return (DNAM.value.reloadAnim == eReloadX);
    }

void WEAPRecord::IsReloadX(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadX : eReloadA;
    }

bool WEAPRecord::IsReloadY()
    {
    return (DNAM.value.reloadAnim == eReloadY);
    }

void WEAPRecord::IsReloadY(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadY : eReloadA;
    }

bool WEAPRecord::IsReloadZ()
    {
    return (DNAM.value.reloadAnim == eReloadZ);
    }

void WEAPRecord::IsReloadZ(bool value)
    {
    DNAM.value.reloadAnim = value ? eReloadZ : eReloadA;
    }

bool WEAPRecord::IsReloadType(UINT8 Type)
    {
    return DNAM.value.reloadAnim == Type;
    }

void WEAPRecord::SetReloadType(UINT8 Type)
    {
    DNAM.value.reloadAnim = Type;
    }

bool WEAPRecord::IsAttackLeft()
    {
    return (DNAM.value.attackAnim == eAttackLeft);
    }

void WEAPRecord::IsAttackLeft(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackLeft : eAttackRight;
    }

bool WEAPRecord::IsAttackRight()
    {
    return (DNAM.value.attackAnim == eAttackRight);
    }

void WEAPRecord::IsAttackRight(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackRight : eAttackLeft;
    }

bool WEAPRecord::IsAttack3()
    {
    return (DNAM.value.attackAnim == eAttack3);
    }

void WEAPRecord::IsAttack3(bool value)
    {
    DNAM.value.attackAnim = value ? eAttack3 : eAttackLeft;
    }

bool WEAPRecord::IsAttack4()
    {
    return (DNAM.value.attackAnim == eAttack4);
    }

void WEAPRecord::IsAttack4(bool value)
    {
    DNAM.value.attackAnim = value ? eAttack4 : eAttackLeft;
    }

bool WEAPRecord::IsAttack5()
    {
    return (DNAM.value.attackAnim == eAttack5);
    }

void WEAPRecord::IsAttack5(bool value)
    {
    DNAM.value.attackAnim = value ? eAttack5 : eAttackLeft;
    }

bool WEAPRecord::IsAttack6()
    {
    return (DNAM.value.attackAnim == eAttack6);
    }

void WEAPRecord::IsAttack6(bool value)
    {
    DNAM.value.attackAnim = value ? eAttack6 : eAttackLeft;
    }

bool WEAPRecord::IsAttack7()
    {
    return (DNAM.value.attackAnim == eAttack7);
    }

void WEAPRecord::IsAttack7(bool value)
    {
    DNAM.value.attackAnim = value ? eAttack7 : eAttackLeft;
    }

bool WEAPRecord::IsAttack8()
    {
    return (DNAM.value.attackAnim == eAttack8);
    }

void WEAPRecord::IsAttack8(bool value)
    {
    DNAM.value.attackAnim = value ? eAttack8 : eAttackLeft;
    }

bool WEAPRecord::IsAttack9()
    {
    return (DNAM.value.attackAnim == eAttack9);
    }

void WEAPRecord::IsAttack9(bool value)
    {
    DNAM.value.attackAnim = value ? eAttack9 : eAttackLeft;
    }

bool WEAPRecord::IsAttackLoop()
    {
    return (DNAM.value.attackAnim == eAttackLoop);
    }

void WEAPRecord::IsAttackLoop(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackLoop : eAttackLeft;
    }

bool WEAPRecord::IsAttackSpin()
    {
    return (DNAM.value.attackAnim == eAttackSpin);
    }

void WEAPRecord::IsAttackSpin(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackSpin : eAttackLeft;
    }

bool WEAPRecord::IsAttackSpin2()
    {
    return (DNAM.value.attackAnim == eAttackSpin2);
    }

void WEAPRecord::IsAttackSpin2(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackSpin2 : eAttackLeft;
    }

bool WEAPRecord::IsAttackThrow()
    {
    return (DNAM.value.attackAnim == eAttackThrow);
    }

void WEAPRecord::IsAttackThrow(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackThrow : eAttackLeft;
    }

bool WEAPRecord::IsAttackThrow2()
    {
    return (DNAM.value.attackAnim == eAttackThrow2);
    }

void WEAPRecord::IsAttackThrow2(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackThrow2 : eAttackLeft;
    }

bool WEAPRecord::IsAttackThrow3()
    {
    return (DNAM.value.attackAnim == eAttackThrow3);
    }

void WEAPRecord::IsAttackThrow3(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackThrow3 : eAttackLeft;
    }

bool WEAPRecord::IsAttackThrow4()
    {
    return (DNAM.value.attackAnim == eAttackThrow4);
    }

void WEAPRecord::IsAttackThrow4(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackThrow4 : eAttackLeft;
    }

bool WEAPRecord::IsAttackThrow5()
    {
    return (DNAM.value.attackAnim == eAttackThrow5);
    }

void WEAPRecord::IsAttackThrow5(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackThrow5 : eAttackLeft;
    }

bool WEAPRecord::IsAttackThrow6()
    {
    return (DNAM.value.attackAnim == eAttackThrow6);
    }

void WEAPRecord::IsAttackThrow6(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackThrow6 : eAttackLeft;
    }

bool WEAPRecord::IsAttackThrow7()
    {
    return (DNAM.value.attackAnim == eAttackThrow7);
    }

void WEAPRecord::IsAttackThrow7(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackThrow7 : eAttackLeft;
    }

bool WEAPRecord::IsAttackThrow8()
    {
    return (DNAM.value.attackAnim == eAttackThrow8);
    }

void WEAPRecord::IsAttackThrow8(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackThrow8 : eAttackLeft;
    }

bool WEAPRecord::IsAttackPlaceMine()
    {
    return (DNAM.value.attackAnim == ePlaceMine);
    }

void WEAPRecord::IsAttackPlaceMine(bool value)
    {
    DNAM.value.attackAnim = value ? ePlaceMine : eAttackLeft;
    }

bool WEAPRecord::IsAttackPlaceMine2()
    {
    return (DNAM.value.attackAnim == ePlaceMine2);
    }

void WEAPRecord::IsAttackPlaceMine2(bool value)
    {
    DNAM.value.attackAnim = value ? ePlaceMine2 : eAttackLeft;
    }

bool WEAPRecord::IsAttackDefault()
    {
    return (DNAM.value.attackAnim == eAttackDefault);
    }

void WEAPRecord::IsAttackDefault(bool value)
    {
    DNAM.value.attackAnim = value ? eAttackDefault : eAttackLeft;
    }

bool WEAPRecord::IsAttackType(UINT8 Type)
    {
    return DNAM.value.attackAnim == Type;
    }

void WEAPRecord::SetAttackType(UINT8 Type)
    {
    DNAM.value.attackAnim = Type;
    }

bool WEAPRecord::IsEmbeddedAVPerception()
    {
    return (DNAM.value.weaponAV == ePerception);
    }

void WEAPRecord::IsEmbeddedAVPerception(bool value)
    {
    DNAM.value.weaponAV = value ? ePerception : eEndurance;
    }

bool WEAPRecord::IsEmbeddedAVEndurance()
    {
    return (DNAM.value.weaponAV == eEndurance);
    }

void WEAPRecord::IsEmbeddedAVEndurance(bool value)
    {
    DNAM.value.weaponAV = value ? eEndurance : ePerception;
    }

bool WEAPRecord::IsEmbeddedAVLeftAttack()
    {
    return (DNAM.value.weaponAV == eLeftAttack);
    }

void WEAPRecord::IsEmbeddedAVLeftAttack(bool value)
    {
    DNAM.value.weaponAV = value ? eLeftAttack : ePerception;
    }

bool WEAPRecord::IsEmbeddedAVRightAttack()
    {
    return (DNAM.value.weaponAV == eRightAttack);
    }

void WEAPRecord::IsEmbeddedAVRightAttack(bool value)
    {
    DNAM.value.weaponAV = value ? eRightAttack : ePerception;
    }

bool WEAPRecord::IsEmbeddedAVLeftMobility()
    {
    return (DNAM.value.weaponAV == eLeftMobility);
    }

void WEAPRecord::IsEmbeddedAVLeftMobility(bool value)
    {
    DNAM.value.weaponAV = value ? eLeftMobility : ePerception;
    }

bool WEAPRecord::IsEmbeddedAVRightMobilty()
    {
    return (DNAM.value.weaponAV == eRightMobilty);
    }

void WEAPRecord::IsEmbeddedAVRightMobilty(bool value)
    {
    DNAM.value.weaponAV = value ? eRightMobilty : ePerception;
    }

bool WEAPRecord::IsEmbeddedAVBrain()
    {
    return (DNAM.value.weaponAV == eBrain);
    }

void WEAPRecord::IsEmbeddedAVBrain(bool value)
    {
    DNAM.value.weaponAV = value ? eBrain : ePerception;
    }

bool WEAPRecord::IsEmbeddedAVType(UINT8 Type)
    {
    return DNAM.value.weaponAV == Type;
    }

void WEAPRecord::SetEmbeddedAVType(UINT8 Type)
    {
    DNAM.value.weaponAV = Type;
    }

bool WEAPRecord::IsOnHitNormalFormulaBehavior()
    {
    return (DNAM.value.onHit == eNormalFormulaBehavior);
    }

void WEAPRecord::IsOnHitNormalFormulaBehavior(bool value)
    {
    DNAM.value.onHit = value ? eNormalFormulaBehavior : eDismemberOnly;
    }

bool WEAPRecord::IsOnHitDismemberOnly()
    {
    return (DNAM.value.onHit == eDismemberOnly);
    }

void WEAPRecord::IsOnHitDismemberOnly(bool value)
    {
    DNAM.value.onHit = value ? eDismemberOnly : eNormalFormulaBehavior;
    }

bool WEAPRecord::IsOnHitExplodeOnly()
    {
    return (DNAM.value.onHit == eExplodeOnly);
    }

void WEAPRecord::IsOnHitExplodeOnly(bool value)
    {
    DNAM.value.onHit = value ? eExplodeOnly : eNormalFormulaBehavior;
    }

bool WEAPRecord::IsOnHitNoDismemberExplode()
    {
    return (DNAM.value.onHit == eNoDismemberExplode);
    }

void WEAPRecord::IsOnHitNoDismemberExplode(bool value)
    {
    DNAM.value.onHit = value ? eNoDismemberExplode : eNormalFormulaBehavior;
    }

bool WEAPRecord::IsOnHitType(UINT32 Type)
    {
    return DNAM.value.onHit == Type;
    }

void WEAPRecord::SetOnHitType(UINT32 Type)
    {
    DNAM.value.onHit = Type;
    }

bool WEAPRecord::IsRumbleConstant()
    {
    return (DNAM.value.rumbleType == eConstant);
    }

void WEAPRecord::IsRumbleConstant(bool value)
    {
    DNAM.value.rumbleType = value ? eConstant : eSquare;
    }

bool WEAPRecord::IsRumbleSquare()
    {
    return (DNAM.value.rumbleType == eSquare);
    }

void WEAPRecord::IsRumbleSquare(bool value)
    {
    DNAM.value.rumbleType = value ? eSquare : eConstant;
    }

bool WEAPRecord::IsRumbleTriangle()
    {
    return (DNAM.value.rumbleType == eTriangle);
    }

void WEAPRecord::IsRumbleTriangle(bool value)
    {
    DNAM.value.rumbleType = value ? eTriangle : eConstant;
    }

bool WEAPRecord::IsRumbleSawtooth()
    {
    return (DNAM.value.rumbleType == eSawtooth);
    }

void WEAPRecord::IsRumbleSawtooth(bool value)
    {
    DNAM.value.rumbleType = value ? eSawtooth : eConstant;
    }

bool WEAPRecord::IsRumbleType(UINT32 Type)
    {
    return DNAM.value.rumbleType == Type;
    }

void WEAPRecord::SetRumbleType(UINT32 Type)
    {
    DNAM.value.rumbleType = Type;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideUnknown0()
    {
    return (DNAM.value.overridePwrAtkAnim == eUnknown0);
    }

void WEAPRecord::IsPowerAttackAnimOverrideUnknown0(bool value)
    {
    DNAM.value.overridePwrAtkAnim = value ? eUnknown0 : eAttackCustom1Power;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom1Power()
    {
    return (DNAM.value.overridePwrAtkAnim == eAttackCustom1Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom1Power(bool value)
    {
    DNAM.value.overridePwrAtkAnim = value ? eAttackCustom1Power : eAttackCustom2Power;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom2Power()
    {
    return (DNAM.value.overridePwrAtkAnim == eAttackCustom2Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom2Power(bool value)
    {
    DNAM.value.overridePwrAtkAnim = value ? eAttackCustom2Power : eAttackCustom1Power;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom3Power()
    {
    return (DNAM.value.overridePwrAtkAnim == eAttackCustom3Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom3Power(bool value)
    {
    DNAM.value.overridePwrAtkAnim = value ? eAttackCustom3Power : eAttackCustom1Power;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom4Power()
    {
    return (DNAM.value.overridePwrAtkAnim == eAttackCustom4Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom4Power(bool value)
    {
    DNAM.value.overridePwrAtkAnim = value ? eAttackCustom4Power : eAttackCustom1Power;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom5Power()
    {
    return (DNAM.value.overridePwrAtkAnim == eAttackCustom5Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom5Power(bool value)
    {
    DNAM.value.overridePwrAtkAnim = value ? eAttackCustom5Power : eAttackCustom1Power;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideDefault()
    {
    return (DNAM.value.overridePwrAtkAnim == eAttackCustomDefault);
    }

void WEAPRecord::IsPowerAttackAnimOverrideDefault(bool value)
    {
    DNAM.value.overridePwrAtkAnim = value ? eAttackCustomDefault : eAttackCustom1Power;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideType(UINT32 Type)
    {
    return DNAM.value.overridePwrAtkAnim == Type;
    }

void WEAPRecord::SetPowerAttackAnimOverrideType(UINT32 Type)
    {
    DNAM.value.overridePwrAtkAnim = Type;
    }

bool WEAPRecord::IsModReloadA()
    {
    return (DNAM.value.reloadAnimMod == eReloadA);
    }

void WEAPRecord::IsModReloadA(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadA : eReloadB;
    }

bool WEAPRecord::IsModReloadB()
    {
    return (DNAM.value.reloadAnimMod == eReloadB);
    }

void WEAPRecord::IsModReloadB(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadB : eReloadA;
    }

bool WEAPRecord::IsModReloadC()
    {
    return (DNAM.value.reloadAnimMod == eReloadC);
    }

void WEAPRecord::IsModReloadC(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadC : eReloadA;
    }

bool WEAPRecord::IsModReloadD()
    {
    return (DNAM.value.reloadAnimMod == eReloadD);
    }

void WEAPRecord::IsModReloadD(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadD : eReloadA;
    }

bool WEAPRecord::IsModReloadE()
    {
    return (DNAM.value.reloadAnimMod == eReloadE);
    }

void WEAPRecord::IsModReloadE(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadE : eReloadA;
    }

bool WEAPRecord::IsModReloadF()
    {
    return (DNAM.value.reloadAnimMod == eReloadF);
    }

void WEAPRecord::IsModReloadF(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadF : eReloadA;
    }

bool WEAPRecord::IsModReloadG()
    {
    return (DNAM.value.reloadAnimMod == eReloadG);
    }

void WEAPRecord::IsModReloadG(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadG : eReloadA;
    }

bool WEAPRecord::IsModReloadH()
    {
    return (DNAM.value.reloadAnimMod == eReloadH);
    }

void WEAPRecord::IsModReloadH(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadH : eReloadA;
    }

bool WEAPRecord::IsModReloadI()
    {
    return (DNAM.value.reloadAnimMod == eReloadI);
    }

void WEAPRecord::IsModReloadI(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadI : eReloadA;
    }

bool WEAPRecord::IsModReloadJ()
    {
    return (DNAM.value.reloadAnimMod == eReloadJ);
    }

void WEAPRecord::IsModReloadJ(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadJ : eReloadA;
    }

bool WEAPRecord::IsModReloadK()
    {
    return (DNAM.value.reloadAnimMod == eReloadK);
    }

void WEAPRecord::IsModReloadK(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadK : eReloadA;
    }

bool WEAPRecord::IsModReloadL()
    {
    return (DNAM.value.reloadAnimMod == eReloadL);
    }

void WEAPRecord::IsModReloadL(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadL : eReloadA;
    }

bool WEAPRecord::IsModReloadM()
    {
    return (DNAM.value.reloadAnimMod == eReloadM);
    }

void WEAPRecord::IsModReloadM(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadM : eReloadA;
    }

bool WEAPRecord::IsModReloadN()
    {
    return (DNAM.value.reloadAnimMod == eReloadN);
    }

void WEAPRecord::IsModReloadN(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadN : eReloadA;
    }

bool WEAPRecord::IsModReloadO()
    {
    return (DNAM.value.reloadAnimMod == eReloadO);
    }

void WEAPRecord::IsModReloadO(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadO : eReloadA;
    }

bool WEAPRecord::IsModReloadP()
    {
    return (DNAM.value.reloadAnimMod == eReloadP);
    }

void WEAPRecord::IsModReloadP(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadP : eReloadA;
    }

bool WEAPRecord::IsModReloadQ()
    {
    return (DNAM.value.reloadAnimMod == eReloadQ);
    }

void WEAPRecord::IsModReloadQ(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadQ : eReloadA;
    }

bool WEAPRecord::IsModReloadR()
    {
    return (DNAM.value.reloadAnimMod == eReloadR);
    }

void WEAPRecord::IsModReloadR(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadR : eReloadA;
    }

bool WEAPRecord::IsModReloadS()
    {
    return (DNAM.value.reloadAnimMod == eReloadS);
    }

void WEAPRecord::IsModReloadS(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadS : eReloadA;
    }

bool WEAPRecord::IsModReloadW()
    {
    return (DNAM.value.reloadAnimMod == eReloadW);
    }

void WEAPRecord::IsModReloadW(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadW : eReloadA;
    }

bool WEAPRecord::IsModReloadX()
    {
    return (DNAM.value.reloadAnimMod == eReloadX);
    }

void WEAPRecord::IsModReloadX(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadX : eReloadA;
    }

bool WEAPRecord::IsModReloadY()
    {
    return (DNAM.value.reloadAnimMod == eReloadY);
    }

void WEAPRecord::IsModReloadY(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadY : eReloadA;
    }

bool WEAPRecord::IsModReloadZ()
    {
    return (DNAM.value.reloadAnimMod == eReloadZ);
    }

void WEAPRecord::IsModReloadZ(bool value)
    {
    DNAM.value.reloadAnimMod = value ? eReloadZ : eReloadA;
    }

bool WEAPRecord::IsModType(UINT8 Type)
    {
    return DNAM.value.reloadAnimMod == Type;
    }

void WEAPRecord::SetModType(UINT8 Type)
    {
    DNAM.value.reloadAnimMod = Type;
    }

bool WEAPRecord::IsVATSNotSilent()
    {
    return (VATS.value.silenceType == eIsNotSilent);
    }

void WEAPRecord::IsVATSNotSilent(bool value)
    {
    VATS.value.silenceType = value ? eIsNotSilent : eIsSilent;
    }

bool WEAPRecord::IsVATSSilent()
    {
    return (VATS.value.silenceType == eIsSilent);
    }

void WEAPRecord::IsVATSSilent(bool value)
    {
    VATS.value.silenceType = value ? eIsSilent : eIsNotSilent;
    }

bool WEAPRecord::IsVATSSilenceType(UINT8 Type)
    {
    return VATS.value.silenceType == Type;
    }

void WEAPRecord::SetVATSSilenceType(UINT8 Type)
    {
    VATS.value.silenceType = Type;
    }

bool WEAPRecord::IsVATSModNotRequired()
    {
    return (VATS.value.modRequiredType == eIsNotModRequired);
    }

void WEAPRecord::IsVATSModNotRequired(bool value)
    {
    VATS.value.modRequiredType = value ? eIsNotModRequired : eIsModRequired;
    }

bool WEAPRecord::IsVATSModRequired()
    {
    return (VATS.value.modRequiredType == eIsModRequired);
    }

void WEAPRecord::IsVATSModRequired(bool value)
    {
    VATS.value.modRequiredType = value ? eIsModRequired : eIsNotModRequired;
    }

bool WEAPRecord::IsVATSModType(UINT8 Type)
    {
    return VATS.value.modRequiredType == Type;
    }

void WEAPRecord::SetVATSModType(UINT8 Type)
    {
    VATS.value.modRequiredType = Type;
    }

bool WEAPRecord::IsLoud()
    {
    return (VNAM.value == eLoud);
    }

void WEAPRecord::IsLoud(bool value)
    {
    VNAM.value = value ? eLoud : eNormal;
    }

bool WEAPRecord::IsNormal()
    {
    return (VNAM.value == eNormal);
    }

void WEAPRecord::IsNormal(bool value)
    {
    VNAM.value = value ? eNormal : eLoud;
    }

bool WEAPRecord::IsSilent()
    {
    return (VNAM.value == eSilent);
    }

void WEAPRecord::IsSilent(bool value)
    {
    VNAM.value = value ? eSilent : eNormal;
    }

bool WEAPRecord::IsSoundLevelType(UINT32 Type)
    {
    return VNAM.value == Type;
    }

void WEAPRecord::SetSoundLevelType(UINT32 Type)
    {
    VNAM.value = Type;
    }

UINT32 WEAPRecord::GetType()
    {
    return REV32(WEAP);
    }

STRING WEAPRecord::GetStrType()
    {
    return "WEAP";
    }

SINT32 WEAPRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    UINT32 curSound = 0;
    enum curSounds
        {
        fIsGun3DRead   = 0x01,
        fIsShoot3DRead = 0x02
        };
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case REV32(XXXX):
                curPos += 2;
                _readBuffer(&subSize, buffer, 4, curPos);
                _readBuffer(&subType, buffer, 4, curPos);
                curPos += 2;
                break;
            default:
                subSize = 0;
                _readBuffer(&subSize, buffer, 2, curPos);
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, curPos);
                break;
            case REV32(OBND):
                OBND.Read(buffer, subSize, curPos);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, curPos);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize, curPos);
                break;
            case REV32(EITM):
                EITM.Read(buffer, subSize, curPos);
                break;
            case REV32(EAMT):
                EAMT.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize, curPos);
                break;
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize, curPos);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize, curPos);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, curPos);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, curPos);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                break;
            case REV32(REPL):
                REPL.Read(buffer, subSize, curPos);
                break;
            case REV32(ETYP):
                ETYP.Read(buffer, subSize, curPos);
                break;
            case REV32(BIPL):
                BIPL.Read(buffer, subSize, curPos);
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(MOD2):
                MOD2.Load();
                MOD2->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MO2T):
                MOD2.Load();
                MOD2->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(MO2S):
                MOD2.Load();
                MOD2->Textures.Read(buffer, subSize, curPos);
                break;
            case REV32(MOD3):
                MOD3.Load();
                MOD3->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MO3T):
                MOD3.Load();
                MOD3->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(MO3S):
                MOD3.Load();
                MOD3->Textures.Read(buffer, subSize, curPos);
                break;
            case REV32(EFSD):
                EFSD.Read(buffer, subSize, curPos);
                break;
            case REV32(MOD4):
                MOD4.Load();
                MOD4->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MO4T):
                MOD4.Load();
                MOD4->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(MO4S):
                MOD4.Load();
                MOD4->Textures.Read(buffer, subSize, curPos);
                break;
            case REV32(VANM):
                VANM.Read(buffer, subSize, curPos);
                break;
            case REV32(NNAM):
                NNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(MWD1):
                MWD1.Read(buffer, subSize, curPos);
                break;
            case REV32(MWD2):
                MWD2.Read(buffer, subSize, curPos);
                break;
            case REV32(MWD3):
                MWD3.Read(buffer, subSize, curPos);
                break;
            case REV32(MWD4):
                MWD4.Read(buffer, subSize, curPos);
                break;
            case REV32(MWD5):
                MWD5.Read(buffer, subSize, curPos);
                break;
            case REV32(MWD6):
                MWD6.Read(buffer, subSize, curPos);
                break;
            case REV32(MWD7):
                MWD7.Read(buffer, subSize, curPos);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize, curPos);
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(WNM1):
                WNM1.Read(buffer, subSize, curPos);
                break;
            case REV32(WNM2):
                WNM2.Read(buffer, subSize, curPos);
                break;
            case REV32(WNM3):
                WNM3.Read(buffer, subSize, curPos);
                break;
            case REV32(WNM4):
                WNM4.Read(buffer, subSize, curPos);
                break;
            case REV32(WNM5):
                WNM5.Read(buffer, subSize, curPos);
                break;
            case REV32(WNM6):
                WNM6.Read(buffer, subSize, curPos);
                break;
            case REV32(WNM7):
                WNM7.Read(buffer, subSize, curPos);
                break;
            case REV32(WMI1):
                WMI1.Read(buffer, subSize, curPos);
                break;
            case REV32(WMI2):
                WMI2.Read(buffer, subSize, curPos);
                break;
            case REV32(WMI3):
                WMI3.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                if((curSound & fIsGun3DRead) == 0)
                    SNAM1.Read(buffer, subSize, curPos);
                else
                    SNAM2.Read(buffer, subSize, curPos);
                curSound |= fIsGun3DRead;
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM7):
                NAM7.Read(buffer, subSize, curPos);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM6):
                NAM6.Read(buffer, subSize, curPos);
                break;
            case REV32(UNAM):
                UNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM9):
                NAM9.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM8):
                NAM8.Read(buffer, subSize, curPos);
                break;
            case REV32(WMS1):
                if((curSound & fIsShoot3DRead) == 0)
                    WMS11.Read(buffer, subSize, curPos);
                else
                    WMS12.Read(buffer, subSize, curPos);
                curSound |= fIsShoot3DRead;
                break;
            case REV32(WMS2):
                WMS2.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(CRDT):
                CRDT.Read(buffer, subSize, curPos);
                break;
            case REV32(VATS):
                VATS.Read(buffer, subSize, curPos);
                break;
            case REV32(VNAM):
                VNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  WEAP: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 WEAPRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    SCRI.Unload();
    EITM.Unload();
    EAMT.Unload();
    NAM0.Unload();
    Destructable.Unload();
    REPL.Unload();
    ETYP.Unload();
    BIPL.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    MOD2.Unload();
    MOD3.Unload();
    EFSD.Unload();
    MOD4.Unload();
    VANM.Unload();
    NNAM.Unload();
    MWD1.Unload();
    MWD2.Unload();
    MWD3.Unload();
    MWD4.Unload();
    MWD5.Unload();
    MWD6.Unload();
    MWD7.Unload();
    INAM.Unload();
    WNAM.Unload();
    WNM1.Unload();
    WNM2.Unload();
    WNM3.Unload();
    WNM4.Unload();
    WNM5.Unload();
    WNM6.Unload();
    WNM7.Unload();
    WMI1.Unload();
    WMI2.Unload();
    WMI3.Unload();
    SNAM1.Unload();
    SNAM2.Unload();
    XNAM.Unload();
    NAM7.Unload();
    TNAM.Unload();
    NAM6.Unload();
    UNAM.Unload();
    NAM9.Unload();
    NAM8.Unload();
    WMS11.Unload();
    WMS12.Unload();
    WMS2.Unload();
    DATA.Unload();
    DNAM.Unload();
    CRDT.Unload();
    VATS.Unload();
    VNAM.Unload();
    return 1;
    }

SINT32 WEAPRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(SCRI);
    WRITE(EITM);
    WRITE(EAMT);
    WRITE(NAM0);
    Destructable.Write(writer);
    WRITE(REPL);
    WRITE(ETYP);
    WRITE(BIPL);
    WRITE(YNAM);
    WRITE(ZNAM);
    if(MOD2.IsLoaded())
        {
        MOD2->WRITEAS(MODL, MOD2);
        MOD2->WRITEAS(MODT, MO2T);
        MOD2->WRITEAS(Textures, MO2S);
        }
    if(MOD3.IsLoaded())
        {
        MOD3->WRITEAS(MODL, MOD3);
        MOD3->WRITEAS(MODT, MO3T);
        MOD3->WRITEAS(Textures, MO3S);
        }
    WRITE(EFSD);
    if(MOD4.IsLoaded())
        {
        MOD4->WRITEAS(MODL, MOD4);
        MOD4->WRITEAS(MODT, MO4T);
        MOD4->WRITEAS(Textures, MO4S);
        }
    WRITE(VANM);
    WRITE(NNAM);

    WRITE(MWD1);
    WRITE(MWD2);
    WRITE(MWD3);
    WRITE(MWD4);
    WRITE(MWD5);
    WRITE(MWD6);
    WRITE(MWD7);
    WRITE(INAM);
    WRITE(WNAM);
    WRITE(WNM1);
    WRITE(WNM2);
    WRITE(WNM3);
    WRITE(WNM4);
    WRITE(WNM5);
    WRITE(WNM6);
    WRITE(WNM7);
    WRITE(WMI1);
    WRITE(WMI2);
    WRITE(WMI3);
    WRITEAS(SNAM1, SNAM);
    if(SNAM2.IsLoaded() && !SNAM1.IsLoaded()) //SNAM1 must be written even if empty for SNAM2 to work
        writer.record_write_subrecord(REV32(SNAM), &SNAM1.value, sizeof(SNAM1.value));
    WRITEAS(SNAM2, SNAM);
    WRITE(XNAM);
    WRITE(NAM7);
    WRITE(TNAM);
    WRITE(NAM6);
    WRITE(UNAM);
    WRITE(NAM9);
    WRITE(NAM8);
    WRITEAS(WMS11, WMS1);
    if(WMS12.IsLoaded() && !WMS11.IsLoaded()) //WMS11 must be written even if empty for WMS12 to work
        writer.record_write_subrecord(REV32(WMS1), &WMS11.value, sizeof(WMS11.value));
    WRITEAS(WMS12, WMS1);
    WRITE(WMS2);
    WRITE(DATA);
    WRITE(DNAM);
    WRITE(CRDT);
    WRITE(VATS);
    WRITE(VNAM);
    return -1;
    }

bool WEAPRecord::operator ==(const WEAPRecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            EITM == other.EITM &&
            EAMT == other.EAMT &&
            NAM0 == other.NAM0 &&
            REPL == other.REPL &&
            ETYP == other.ETYP &&
            BIPL == other.BIPL &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            EFSD == other.EFSD &&
            INAM == other.INAM &&
            WNAM == other.WNAM &&
            WMI1 == other.WMI1 &&
            WMI2 == other.WMI2 &&
            WMI3 == other.WMI3 &&
            WNM1 == other.WNM1 &&
            WNM2 == other.WNM2 &&
            WNM3 == other.WNM3 &&
            WNM4 == other.WNM4 &&
            WNM5 == other.WNM5 &&
            WNM6 == other.WNM6 &&
            WNM7 == other.WNM7 &&
            SNAM1 == other.SNAM1 &&
            SNAM2 == other.SNAM2 &&
            XNAM == other.XNAM &&
            NAM7 == other.NAM7 &&
            TNAM == other.TNAM &&
            NAM6 == other.NAM6 &&
            UNAM == other.UNAM &&
            NAM9 == other.NAM9 &&
            NAM8 == other.NAM8 &&
            WMS11 == other.WMS11 &&
            WMS12 == other.WMS12 &&
            WMS2 == other.WMS2 &&
            DATA == other.DATA &&
            DNAM == other.DNAM &&
            CRDT == other.CRDT &&
            VATS == other.VATS &&
            VNAM == other.VNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            VANM.equalsi(other.VANM) &&
            NNAM.equalsi(other.NNAM) &&
            MWD1.equalsi(other.MWD1) &&
            MWD2.equalsi(other.MWD2) &&
            MWD3.equalsi(other.MWD3) &&
            MWD4.equalsi(other.MWD4) &&
            MWD5.equalsi(other.MWD5) &&
            MWD6.equalsi(other.MWD6) &&
            MWD7.equalsi(other.MWD7) &&
            MODL == other.MODL &&
            MOD2 == other.MOD2 &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4 &&
            Destructable == other.Destructable);
    }

bool WEAPRecord::operator !=(const WEAPRecord &other) const
    {
    return !(*this == other);
    }
}