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
    if(srcRecord->MOD2.IsLoaded())
        {
        MOD2.Load();
        MOD2->MOD2 = srcRecord->MOD2->MOD2;
        MOD2->MO2T = srcRecord->MOD2->MO2T;
        MOD2->MO2S = srcRecord->MOD2->MO2S;
        }
    if(srcRecord->MOD3.IsLoaded())
        {
        MOD3.Load();
        MOD3->MOD3 = srcRecord->MOD3->MOD3;
        MOD3->MO3T = srcRecord->MOD3->MO3T;
        MOD3->MO3S = srcRecord->MOD3->MO3S;
        }
    EFSD = srcRecord->EFSD;
    if(srcRecord->MOD4.IsLoaded())
        {
        MOD4.Load();
        MOD4->MOD4 = srcRecord->MOD4->MOD4;
        MOD4->MO4T = srcRecord->MOD4->MO4T;
        MOD4->MO4S = srcRecord->MOD4->MO4S;
        }
    VANM = srcRecord->VANM;
    NNAM = srcRecord->NNAM;
    if(srcRecord->MWD1.IsLoaded())
        {
        MWD1.Load();
        MWD1->MWD1 = srcRecord->MWD1->MWD1;
        MWD1->MWD2 = srcRecord->MWD1->MWD2;
        MWD1->MWD3 = srcRecord->MWD1->MWD3;
        MWD1->MWD4 = srcRecord->MWD1->MWD4;
        MWD1->MWD5 = srcRecord->MWD1->MWD5;
        MWD1->MWD6 = srcRecord->MWD1->MWD6;
        MWD1->MWD7 = srcRecord->MWD1->MWD7;
        }
    INAM = srcRecord->INAM;
    WNAM = srcRecord->WNAM;
    if(srcRecord->WNM1.IsLoaded())
        {
        WNM1.Load();
        WNM1->WNM1 = srcRecord->WNM1->WNM1;
        WNM1->WNM2 = srcRecord->WNM1->WNM2;
        WNM1->WNM3 = srcRecord->WNM1->WNM3;
        WNM1->WNM4 = srcRecord->WNM1->WNM4;
        WNM1->WNM5 = srcRecord->WNM1->WNM5;
        WNM1->WNM6 = srcRecord->WNM1->WNM6;
        WNM1->WNM7 = srcRecord->WNM1->WNM7;
        }
    if(srcRecord->WMI1.IsLoaded())
        {
        WMI1.Load();
        WMI1->WMI1 = srcRecord->WMI1->WMI1;
        WMI1->WMI2 = srcRecord->WMI1->WMI2;
        WMI1->WMI3 = srcRecord->WMI1->WMI3;
        }
    SNAM = srcRecord->SNAM;
    XNAM = srcRecord->XNAM;
    NAM7 = srcRecord->NAM7;
    TNAM = srcRecord->TNAM;
    NAM6 = srcRecord->NAM6;
    UNAM = srcRecord->UNAM;
    NAM9 = srcRecord->NAM9;
    NAM8 = srcRecord->NAM8;
    WMS1 = srcRecord->WMS1;
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
        op.Accept(SCRI->value);
    if(EITM.IsLoaded())
        op.Accept(EITM->value);
    if(NAM0.IsLoaded())
        op.Accept(NAM0->value);
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(REPL.IsLoaded())
        op.Accept(REPL->value);
    if(BIPL.IsLoaded())
        op.Accept(BIPL->value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    if(MOD2.IsLoaded() && MOD2->MO2S.IsLoaded())
        op.Accept(MOD2->MO2S->value);
    if(MOD3.IsLoaded() && MOD3->MO3S.IsLoaded())
        op.Accept(MOD3->MO3S->value);
    if(EFSD.IsLoaded())
        op.Accept(EFSD->value);
    if(MOD4.IsLoaded() && MOD4->MO4S.IsLoaded())
        op.Accept(MOD4->MO4S->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);
    if(WNAM.IsLoaded())
        op.Accept(WNAM->value);
    if(WNM1.IsLoaded() && WNM1->WNM1.IsLoaded())
        op.Accept(WNM1->WNM1->value);
    if(WNM1.IsLoaded() && WNM1->WNM2.IsLoaded())
        op.Accept(WNM1->WNM2->value);
    if(WNM1.IsLoaded() && WNM1->WNM3.IsLoaded())
        op.Accept(WNM1->WNM3->value);
    if(WNM1.IsLoaded() && WNM1->WNM4.IsLoaded())
        op.Accept(WNM1->WNM4->value);
    if(WNM1.IsLoaded() && WNM1->WNM5.IsLoaded())
        op.Accept(WNM1->WNM5->value);
    if(WNM1.IsLoaded() && WNM1->WNM6.IsLoaded())
        op.Accept(WNM1->WNM6->value);
    if(WNM1.IsLoaded() && WNM1->WNM7.IsLoaded())
        op.Accept(WNM1->WNM7->value);
    if(WMI1.IsLoaded() && WMI1->WMI1.IsLoaded())
        op.Accept(WMI1->WMI1->value);
    if(WMI1.IsLoaded() && WMI1->WMI2.IsLoaded())
        op.Accept(WMI1->WMI2->value);
    if(WMI1.IsLoaded() && WMI1->WMI3.IsLoaded())
        op.Accept(WMI1->WMI3->value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);
    if(XNAM.IsLoaded())
        op.Accept(XNAM->value);
    if(NAM7.IsLoaded())
        op.Accept(NAM7->value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM->value);
    if(NAM6.IsLoaded())
        op.Accept(NAM6->value);
    if(UNAM.IsLoaded())
        op.Accept(UNAM->value);
    if(NAM9.IsLoaded())
        op.Accept(NAM9->value);
    if(NAM8.IsLoaded())
        op.Accept(NAM8->value);
    if(WMS1.IsLoaded())
        op.Accept(WMS1->value);
    if(WMS2.IsLoaded())
        op.Accept(WMS2->value);
    //if(DNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DNAM->value);
    //if(CRDT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CRDT->value);
    //if(VATS.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(VATS->value);

    return op.Stop();
    }

bool WEAPRecord::IsNotNormalWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNotNormalWeapon) != 0;
    }

void WEAPRecord::IsNotNormalWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNotNormalWeapon) : (Dummy->flags & ~fIsNotNormalWeapon);
    }

bool WEAPRecord::IsAutomatic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAutomatic) != 0;
    }

void WEAPRecord::IsAutomatic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAutomatic) : (Dummy->flags & ~fIsAutomatic);
    }

bool WEAPRecord::IsHasScope()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHasScope) != 0;
    }

void WEAPRecord::IsHasScope(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHasScope) : (Dummy->flags & ~fIsHasScope);
    }

bool WEAPRecord::IsCantDrop()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsCantDrop) != 0;
    }

void WEAPRecord::IsCantDrop(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsCantDrop) : (Dummy->flags & ~fIsCantDrop);
    }

bool WEAPRecord::IsHideBackpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHideBackpack) != 0;
    }

void WEAPRecord::IsHideBackpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHideBackpack) : (Dummy->flags & ~fIsHideBackpack);
    }

bool WEAPRecord::IsEmbeddedWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEmbeddedWeapon) != 0;
    }

void WEAPRecord::IsEmbeddedWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsEmbeddedWeapon) : (Dummy->flags & ~fIsEmbeddedWeapon);
    }

bool WEAPRecord::IsDontUse1stPersonISAnimations()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDontUse1stPersonISAnimations) != 0;
    }

void WEAPRecord::IsDontUse1stPersonISAnimations(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDontUse1stPersonISAnimations) : (Dummy->flags & ~fIsDontUse1stPersonISAnimations);
    }

bool WEAPRecord::IsNonPlayable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNonPlayable) != 0;
    }

void WEAPRecord::IsNonPlayable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNonPlayable) : (Dummy->flags & ~fIsNonPlayable);
    }

bool WEAPRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void WEAPRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsPlayerOnly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPlayerOnly) != 0;
    }

void WEAPRecord::IsPlayerOnly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPlayerOnly) : (Dummy->flags & ~fIsPlayerOnly);
    }

bool WEAPRecord::IsNPCsUseAmmo()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNPCsUseAmmo) != 0;
    }

void WEAPRecord::IsNPCsUseAmmo(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNPCsUseAmmo) : (Dummy->flags & ~fIsNPCsUseAmmo);
    }

bool WEAPRecord::IsNoJamAfterReload()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoJamAfterReload) != 0;
    }

void WEAPRecord::IsNoJamAfterReload(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoJamAfterReload) : (Dummy->flags & ~fIsNoJamAfterReload);
    }

bool WEAPRecord::IsOverrideActionPoints()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOverrideActionPoints) != 0;
    }

void WEAPRecord::IsOverrideActionPoints(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsOverrideActionPoints) : (Dummy->flags & ~fIsOverrideActionPoints);
    }

bool WEAPRecord::IsMinorCrime()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMinorCrime) != 0;
    }

void WEAPRecord::IsMinorCrime(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsMinorCrime) : (Dummy->flags & ~fIsMinorCrime);
    }

bool WEAPRecord::IsRangeFixed()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRangeFixed) != 0;
    }

void WEAPRecord::IsRangeFixed(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRangeFixed) : (Dummy->flags & ~fIsRangeFixed);
    }

bool WEAPRecord::IsNotUsedInNormalCombat()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNotUsedInNormalCombat) != 0;
    }

void WEAPRecord::IsNotUsedInNormalCombat(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNotUsedInNormalCombat) : (Dummy->flags & ~fIsNotUsedInNormalCombat);
    }

bool WEAPRecord::IsOverrideDamageToWeaponMult()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOverrideDamageToWeaponMult) != 0;
    }

void WEAPRecord::IsOverrideDamageToWeaponMult(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsOverrideDamageToWeaponMult) : (Dummy->flags & ~fIsOverrideDamageToWeaponMult);
    }

bool WEAPRecord::IsDontUse3rdPersonISAnimations()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDontUse3rdPersonISAnimations) != 0;
    }

void WEAPRecord::IsDontUse3rdPersonISAnimations(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDontUse3rdPersonISAnimations) : (Dummy->flags & ~fIsDontUse3rdPersonISAnimations);
    }

bool WEAPRecord::IsShortBurst()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsShortBurst) != 0;
    }

void WEAPRecord::IsShortBurst(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsShortBurst) : (Dummy->flags & ~fIsShortBurst);
    }

bool WEAPRecord::IsRumbleAlternate()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRumbleAlternate) != 0;
    }

void WEAPRecord::IsRumbleAlternate(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRumbleAlternate) : (Dummy->flags & ~fIsRumbleAlternate);
    }

bool WEAPRecord::IsLongBurst()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsLongBurst) != 0;
    }

void WEAPRecord::IsLongBurst(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsLongBurst) : (Dummy->flags & ~fIsLongBurst);
    }

bool WEAPRecord::IsScopeHasNightVision()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsScopeHasNightVision) != 0;
    }

void WEAPRecord::IsScopeHasNightVision(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsScopeHasNightVision) : (Dummy->flags & ~fIsScopeHasNightVision);
    }

bool WEAPRecord::IsScopeFromMod()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsScopeFromMod) != 0;
    }

void WEAPRecord::IsScopeFromMod(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsScopeFromMod) : (Dummy->flags & ~fIsScopeFromMod);
    }

bool WEAPRecord::IsAdvFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void WEAPRecord::SetAdvFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsCritOnDeath()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOnDeath) != 0;
    }

void WEAPRecord::IsCritOnDeath(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsOnDeath) : (Dummy->flags & ~fIsOnDeath);
    }

bool WEAPRecord::IsCritFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void WEAPRecord::SetCritFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void WEAPRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool WEAPRecord::IsBigGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBigGuns);
    }

void WEAPRecord::IsBigGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBigGuns : eDummyDefault;
    }

bool WEAPRecord::IsEnergyWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEnergyWeapons);
    }

void WEAPRecord::IsEnergyWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEnergyWeapons : eDummyDefault;
    }

bool WEAPRecord::IsSmallGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSmallGuns);
    }

void WEAPRecord::IsSmallGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSmallGuns : eDummyDefault;
    }

bool WEAPRecord::IsMeleeWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMeleeWeapons);
    }

void WEAPRecord::IsMeleeWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMeleeWeapons : eDummyDefault;
    }

bool WEAPRecord::IsUnarmedWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnarmedWeapon);
    }

void WEAPRecord::IsUnarmedWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUnarmedWeapon : eDummyDefault;
    }

bool WEAPRecord::IsThrownWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eThrownWeapons);
    }

void WEAPRecord::IsThrownWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eThrownWeapons : eDummyDefault;
    }

bool WEAPRecord::IsMine()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMine);
    }

void WEAPRecord::IsMine(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMine : eDummyDefault;
    }

bool WEAPRecord::IsBodyWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBodyWear);
    }

void WEAPRecord::IsBodyWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBodyWear : eDummyDefault;
    }

bool WEAPRecord::IsHeadWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHeadWear);
    }

void WEAPRecord::IsHeadWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHeadWear : eDummyDefault;
    }

bool WEAPRecord::IsHandWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandWear);
    }

void WEAPRecord::IsHandWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandWear : eDummyDefault;
    }

bool WEAPRecord::IsChems()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eChems);
    }

void WEAPRecord::IsChems(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eChems : eDummyDefault;
    }

bool WEAPRecord::IsStimpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStimpack);
    }

void WEAPRecord::IsStimpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStimpack : eDummyDefault;
    }

bool WEAPRecord::IsFood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFood);
    }

void WEAPRecord::IsFood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFood : eDummyDefault;
    }

bool WEAPRecord::IsAlcohol()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAlcohol);
    }

void WEAPRecord::IsAlcohol(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAlcohol : eDummyDefault;
    }

bool WEAPRecord::IsEquipmentType(SINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetEquipmentType(SINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsHand2Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHand2Hand);
    }

void WEAPRecord::IsHand2Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHand2Hand : eDummyDefault;
    }

bool WEAPRecord::IsMelee1Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMelee1Hand);
    }

void WEAPRecord::IsMelee1Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMelee1Hand : eDummyDefault;
    }

bool WEAPRecord::IsMelee2Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMelee2Hand);
    }

void WEAPRecord::IsMelee2Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMelee2Hand : eDummyDefault;
    }

bool WEAPRecord::IsPistolBallistic1Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePistolBallistic1Hand);
    }

void WEAPRecord::IsPistolBallistic1Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePistolBallistic1Hand : eDummyDefault;
    }

bool WEAPRecord::IsPistolEnergy1Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePistolEnergy1Hand);
    }

void WEAPRecord::IsPistolEnergy1Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePistolEnergy1Hand : eDummyDefault;
    }

bool WEAPRecord::IsRifleBallistic2Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRifleBallistic2Hand);
    }

void WEAPRecord::IsRifleBallistic2Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRifleBallistic2Hand : eDummyDefault;
    }

bool WEAPRecord::IsRifleAutomatic2Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRifleAutomatic2Hand);
    }

void WEAPRecord::IsRifleAutomatic2Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRifleAutomatic2Hand : eDummyDefault;
    }

bool WEAPRecord::IsRifleEnergy2Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRifleEnergy2Hand);
    }

void WEAPRecord::IsRifleEnergy2Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRifleEnergy2Hand : eDummyDefault;
    }

bool WEAPRecord::IsHandle2Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandle2Hand);
    }

void WEAPRecord::IsHandle2Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandle2Hand : eDummyDefault;
    }

bool WEAPRecord::IsLauncher2Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLauncher2Hand);
    }

void WEAPRecord::IsLauncher2Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLauncher2Hand : eDummyDefault;
    }

bool WEAPRecord::IsGrenadeThrow1Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGrenadeThrow1Hand);
    }

void WEAPRecord::IsGrenadeThrow1Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGrenadeThrow1Hand : eDummyDefault;
    }

bool WEAPRecord::IsLandMine1Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLandMine1Hand);
    }

void WEAPRecord::IsLandMine1Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLandMine1Hand : eDummyDefault;
    }

bool WEAPRecord::IsMineDrop1Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMineDrop1Hand);
    }

void WEAPRecord::IsMineDrop1Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMineDrop1Hand : eDummyDefault;
    }

bool WEAPRecord::IsThrown1Hand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eThrown1Hand);
    }

void WEAPRecord::IsThrown1Hand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eThrown1Hand : eDummyDefault;
    }

bool WEAPRecord::IsType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsGripHandGrip1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandGrip1);
    }

void WEAPRecord::IsGripHandGrip1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandGrip1 : eDummyDefault;
    }

bool WEAPRecord::IsGripHandGrip2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandGrip2);
    }

void WEAPRecord::IsGripHandGrip2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandGrip2 : eDummyDefault;
    }

bool WEAPRecord::IsGripHandGrip3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandGrip3);
    }

void WEAPRecord::IsGripHandGrip3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandGrip3 : eDummyDefault;
    }

bool WEAPRecord::IsGripHandGrip4()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandGrip4);
    }

void WEAPRecord::IsGripHandGrip4(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandGrip4 : eDummyDefault;
    }

bool WEAPRecord::IsGripHandGrip5()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandGrip5);
    }

void WEAPRecord::IsGripHandGrip5(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandGrip5 : eDummyDefault;
    }

bool WEAPRecord::IsGripHandGrip6()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandGrip6);
    }

void WEAPRecord::IsGripHandGrip6(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandGrip6 : eDummyDefault;
    }

bool WEAPRecord::IsGripDefault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDefault);
    }

void WEAPRecord::IsGripDefault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDefault : eDummyDefault;
    }

bool WEAPRecord::IsGripType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetGripType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsReloadAnimReloadA()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadA);
    }

void WEAPRecord::IsReloadAnimReloadA(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadA : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadB()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadB);
    }

void WEAPRecord::IsReloadAnimReloadB(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadB : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadC()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadC);
    }

void WEAPRecord::IsReloadAnimReloadC(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadC : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadD()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadD);
    }

void WEAPRecord::IsReloadAnimReloadD(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadD : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadE()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadE);
    }

void WEAPRecord::IsReloadAnimReloadE(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadE : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadF()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadF);
    }

void WEAPRecord::IsReloadAnimReloadF(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadF : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadG()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadG);
    }

void WEAPRecord::IsReloadAnimReloadG(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadG : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadH()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadH);
    }

void WEAPRecord::IsReloadAnimReloadH(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadH : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadI()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadI);
    }

void WEAPRecord::IsReloadAnimReloadI(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadI : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadJ()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadJ);
    }

void WEAPRecord::IsReloadAnimReloadJ(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadJ : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadK);
    }

void WEAPRecord::IsReloadAnimReloadK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadK : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadL()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadL);
    }

void WEAPRecord::IsReloadAnimReloadL(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadL : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadM()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadM);
    }

void WEAPRecord::IsReloadAnimReloadM(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadM : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadN()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadN);
    }

void WEAPRecord::IsReloadAnimReloadN(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadN : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadO()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadO);
    }

void WEAPRecord::IsReloadAnimReloadO(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadO : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadP()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadP);
    }

void WEAPRecord::IsReloadAnimReloadP(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadP : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadQ()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadQ);
    }

void WEAPRecord::IsReloadAnimReloadQ(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadQ : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadR()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadR);
    }

void WEAPRecord::IsReloadAnimReloadR(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadR : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadS);
    }

void WEAPRecord::IsReloadAnimReloadS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadS : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadW()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadW);
    }

void WEAPRecord::IsReloadAnimReloadW(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadW : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadX()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadX);
    }

void WEAPRecord::IsReloadAnimReloadX(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadX : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadY()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadY);
    }

void WEAPRecord::IsReloadAnimReloadY(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadY : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimReloadZ()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadZ);
    }

void WEAPRecord::IsReloadAnimReloadZ(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadZ : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetReloadAnimType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsAttackLeft()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLeft);
    }

void WEAPRecord::IsAttackLeft(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLeft : eDummyDefault;
    }

bool WEAPRecord::IsAttackRight()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackRight);
    }

void WEAPRecord::IsAttackRight(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackRight : eDummyDefault;
    }

bool WEAPRecord::IsAttack3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack3);
    }

void WEAPRecord::IsAttack3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack3 : eDummyDefault;
    }

bool WEAPRecord::IsAttack4()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack4);
    }

void WEAPRecord::IsAttack4(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack4 : eDummyDefault;
    }

bool WEAPRecord::IsAttack5()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack5);
    }

void WEAPRecord::IsAttack5(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack5 : eDummyDefault;
    }

bool WEAPRecord::IsAttack6()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack6);
    }

void WEAPRecord::IsAttack6(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack6 : eDummyDefault;
    }

bool WEAPRecord::IsAttack7()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack7);
    }

void WEAPRecord::IsAttack7(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack7 : eDummyDefault;
    }

bool WEAPRecord::IsAttack8()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack8);
    }

void WEAPRecord::IsAttack8(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack8 : eDummyDefault;
    }

bool WEAPRecord::IsAttack9()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack9);
    }

void WEAPRecord::IsAttack9(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack9 : eDummyDefault;
    }

bool WEAPRecord::IsAttackLoop()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLoop);
    }

void WEAPRecord::IsAttackLoop(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLoop : eDummyDefault;
    }

bool WEAPRecord::IsAttackSpin()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin);
    }

void WEAPRecord::IsAttackSpin(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin : eDummyDefault;
    }

bool WEAPRecord::IsAttackSpin2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin2);
    }

void WEAPRecord::IsAttackSpin2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin2 : eDummyDefault;
    }

bool WEAPRecord::IsAttackThrow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow);
    }

void WEAPRecord::IsAttackThrow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow : eDummyDefault;
    }

bool WEAPRecord::IsAttackThrow2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow2);
    }

void WEAPRecord::IsAttackThrow2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow2 : eDummyDefault;
    }

bool WEAPRecord::IsAttackThrow3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow3);
    }

void WEAPRecord::IsAttackThrow3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow3 : eDummyDefault;
    }

bool WEAPRecord::IsAttackThrow4()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow4);
    }

void WEAPRecord::IsAttackThrow4(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow4 : eDummyDefault;
    }

bool WEAPRecord::IsAttackThrow5()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow5);
    }

void WEAPRecord::IsAttackThrow5(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow5 : eDummyDefault;
    }

bool WEAPRecord::IsAttackThrow6()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow6);
    }

void WEAPRecord::IsAttackThrow6(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow6 : eDummyDefault;
    }

bool WEAPRecord::IsAttackThrow7()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow7);
    }

void WEAPRecord::IsAttackThrow7(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow7 : eDummyDefault;
    }

bool WEAPRecord::IsAttackThrow8()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow8);
    }

void WEAPRecord::IsAttackThrow8(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow8 : eDummyDefault;
    }

bool WEAPRecord::AttackIsPlaceMine()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine);
    }

void WEAPRecord::IsAttackPlaceMine(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine : eDummyDefault;
    }

bool WEAPRecord::IsAttackPlaceMine2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine2);
    }

void WEAPRecord::IsAttackPlaceMine2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine2 : eDummyDefault;
    }

bool WEAPRecord::IsAttackDefault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDefault);
    }

void WEAPRecord::IsAttackDefault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDefault : eDummyDefault;
    }

bool WEAPRecord::IsAttackType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetAttackType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsEmbeddedAVPerception()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePerception);
    }

void WEAPRecord::IsEmbeddedAVPerception(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePerception : eDummyDefault;
    }

bool WEAPRecord::IsEmbeddedAVEndurance()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEndurance);
    }

void WEAPRecord::IsEmbeddedAVEndurance(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEndurance : eDummyDefault;
    }

bool WEAPRecord::IsEmbeddedAVLeftAttack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftAttack);
    }

void WEAPRecord::IsEmbeddedAVLeftAttack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftAttack : eDummyDefault;
    }

bool WEAPRecord::IsEmbeddedAVRightAttack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightAttack);
    }

void WEAPRecord::IsEmbeddedAVRightAttack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightAttack : eDummyDefault;
    }

bool WEAPRecord::IsEmbeddedAVLeftMobility()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftMobility);
    }

void WEAPRecord::IsEmbeddedAVLeftMobility(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftMobility : eDummyDefault;
    }

bool WEAPRecord::IsEmbeddedAVRightMobilty()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightMobilty);
    }

void WEAPRecord::IsEmbeddedAVRightMobilty(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightMobilty : eDummyDefault;
    }

bool WEAPRecord::IsEmbeddedAVBrain()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBrain);
    }

void WEAPRecord::IsEmbeddedAVBrain(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBrain : eDummyDefault;
    }

bool WEAPRecord::IsEmbeddedAVType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetEmbeddedAVType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsOnHitNormalFormulaBehavior()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNormalFormulaBehavior);
    }

void WEAPRecord::IsOnHitNormalFormulaBehavior(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNormalFormulaBehavior : eDummyDefault;
    }

bool WEAPRecord::IsOnHitDismemberOnly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDismemberOnly);
    }

void WEAPRecord::IsOnHitDismemberOnly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDismemberOnly : eDummyDefault;
    }

bool WEAPRecord::IsOnHitExplodeOnly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eExplodeOnly);
    }

void WEAPRecord::IsOnHitExplodeOnly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eExplodeOnly : eDummyDefault;
    }

bool WEAPRecord::IsOnHitNoDismemberExplode()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoDismemberExplode);
    }

void WEAPRecord::IsOnHitNoDismemberExplode(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoDismemberExplode : eDummyDefault;
    }

bool WEAPRecord::IsOnHitType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetOnHitType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsRumbleConstant()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eConstant);
    }

void WEAPRecord::IsRumbleConstant(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eConstant : eDummyDefault;
    }

bool WEAPRecord::IsRumbleSquare()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSquare);
    }

void WEAPRecord::IsRumbleSquare(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSquare : eDummyDefault;
    }

bool WEAPRecord::IsRumbleTriangle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTriangle);
    }

void WEAPRecord::IsRumbleTriangle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTriangle : eDummyDefault;
    }

bool WEAPRecord::IsRumbleSawtooth()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSawtooth);
    }

void WEAPRecord::IsRumbleSawtooth(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSawtooth : eDummyDefault;
    }

bool WEAPRecord::IsRumbleType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetRumbleType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideUnknown0()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnknown0);
    }

void WEAPRecord::IsPowerAttackAnimOverrideUnknown0(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUnknown0 : eDummyDefault;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom1Power()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackCustom1Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom1Power(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackCustom1Power : eDummyDefault;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom2Power()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackCustom2Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom2Power(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackCustom2Power : eDummyDefault;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom3Power()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackCustom3Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom3Power(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackCustom3Power : eDummyDefault;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom4Power()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackCustom4Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom4Power(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackCustom4Power : eDummyDefault;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideAttackCustom5Power()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackCustom5Power);
    }

void WEAPRecord::IsPowerAttackAnimOverrideAttackCustom5Power(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackCustom5Power : eDummyDefault;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideDefault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDefault);
    }

void WEAPRecord::IsPowerAttackAnimOverrideDefault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDefault : eDummyDefault;
    }

bool WEAPRecord::IsPowerAttackAnimOverrideType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetPowerAttackAnimOverrideType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsReloadAnimModReloadA()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadA);
    }

void WEAPRecord::IsReloadAnimModReloadA(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadA : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadB()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadB);
    }

void WEAPRecord::IsReloadAnimModReloadB(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadB : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadC()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadC);
    }

void WEAPRecord::IsReloadAnimModReloadC(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadC : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadD()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadD);
    }

void WEAPRecord::IsReloadAnimModReloadD(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadD : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadE()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadE);
    }

void WEAPRecord::IsReloadAnimModReloadE(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadE : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadF()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadF);
    }

void WEAPRecord::IsReloadAnimModReloadF(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadF : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadG()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadG);
    }

void WEAPRecord::IsReloadAnimModReloadG(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadG : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadH()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadH);
    }

void WEAPRecord::IsReloadAnimModReloadH(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadH : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadI()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadI);
    }

void WEAPRecord::IsReloadAnimModReloadI(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadI : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadJ()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadJ);
    }

void WEAPRecord::IsReloadAnimModReloadJ(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadJ : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadK);
    }

void WEAPRecord::IsReloadAnimModReloadK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadK : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadL()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadL);
    }

void WEAPRecord::IsReloadAnimModReloadL(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadL : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadM()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadM);
    }

void WEAPRecord::IsReloadAnimModReloadM(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadM : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadN()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadN);
    }

void WEAPRecord::IsReloadAnimModReloadN(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadN : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadO()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadO);
    }

void WEAPRecord::IsReloadAnimModReloadO(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadO : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadP()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadP);
    }

void WEAPRecord::IsReloadAnimModReloadP(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadP : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadQ()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadQ);
    }

void WEAPRecord::IsReloadAnimModReloadQ(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadQ : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadR()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadR);
    }

void WEAPRecord::IsReloadAnimModReloadR(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadR : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadS);
    }

void WEAPRecord::IsReloadAnimModReloadS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadS : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadW()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadW);
    }

void WEAPRecord::IsReloadAnimModReloadW(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadW : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadX()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadX);
    }

void WEAPRecord::IsReloadAnimModReloadX(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadX : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadY()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadY);
    }

void WEAPRecord::IsReloadAnimModReloadY(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadY : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModReloadZ()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReloadZ);
    }

void WEAPRecord::IsReloadAnimModReloadZ(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReloadZ : eDummyDefault;
    }

bool WEAPRecord::IsReloadAnimModType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetReloadAnimModType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsVATSNotSilent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIsNotSilent);
    }

void WEAPRecord::IsVATSNotSilent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eIsNotSilent : eDummyDefault;
    }

bool WEAPRecord::IsVATSSilent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIsSilent);
    }

void WEAPRecord::IsVATSSilent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eIsSilent : eDummyDefault;
    }

bool WEAPRecord::IsVATSSilenceType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetVATSSilenceType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsVATSModNotRequired()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIsNotModRequired);
    }

void WEAPRecord::IsVATSModNotRequired(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eIsNotModRequired : eDummyDefault;
    }

bool WEAPRecord::IsVATSModRequired()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIsModRequired);
    }

void WEAPRecord::IsVATSModRequired(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eIsModRequired : eDummyDefault;
    }

bool WEAPRecord::IsVATSModType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetVATSModType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool WEAPRecord::IsLoud()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLoud);
    }

void WEAPRecord::IsLoud(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLoud : eDummyDefault;
    }

bool WEAPRecord::IsNormal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNormal);
    }

void WEAPRecord::IsNormal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNormal : eDummyDefault;
    }

bool WEAPRecord::IsSilent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSilent);
    }

void WEAPRecord::IsSilent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSilent : eDummyDefault;
    }

bool WEAPRecord::IsSoundLevelType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void WEAPRecord::SetSoundLevelType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 WEAPRecord::GetType()
    {
    return 'PAEW';
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
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case 'XXXX':
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
            case 'DIDE':
                EDID.Read(buffer, subSize, curPos);
                break;
            case 'DNBO':
                OBND.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case 'BDOM':
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case 'TDOM':
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case 'SDOM':
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'MTIE':
                EITM.Read(buffer, subSize, curPos);
                break;
            case 'TMAE':
                EAMT.Read(buffer, subSize, curPos);
                break;
            case '0MAN':
                NAM0.Read(buffer, subSize, curPos);
                break;
            case 'TSED':
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize, curPos);
                break;
            case 'DTSD':
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize, curPos);
                break;
            case 'LDMD':
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, curPos);
                break;
            case 'TDMD':
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, curPos);
                break;
            case 'FTSD':
                //Marks end of a destruction stage
                break;
            case 'LPER':
                REPL.Read(buffer, subSize, curPos);
                break;
            case 'PYTE':
                ETYP.Read(buffer, subSize, curPos);
                break;
            case 'LPIB':
                BIPL.Read(buffer, subSize, curPos);
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case '2DOM':
                MOD2.Load();
                MOD2->MOD2.Read(buffer, subSize, curPos);
                break;
            case 'T2OM':
                MOD2.Load();
                MOD2->MO2T.Read(buffer, subSize, curPos);
                break;
            case 'S2OM':
                MOD2.Load();
                MOD2->MO2S.Read(buffer, subSize, curPos);
                break;
            case '3DOM':
                MOD3.Load();
                MOD3->MOD3.Read(buffer, subSize, curPos);
                break;
            case 'T3OM':
                MOD3.Load();
                MOD3->MO3T.Read(buffer, subSize, curPos);
                break;
            case 'S3OM':
                MOD3.Load();
                MOD3->MO3S.Read(buffer, subSize, curPos);
                break;
            case 'DSFE':
                EFSD.Read(buffer, subSize, curPos);
                break;
            case '4DOM':
                MOD4.Load();
                MOD4->MOD4.Read(buffer, subSize, curPos);
                break;
            case 'T4OM':
                MOD4.Load();
                MOD4->MO4T.Read(buffer, subSize, curPos);
                break;
            case 'S4OM':
                MOD4.Load();
                MOD4->MO4S.Read(buffer, subSize, curPos);
                break;
            case 'MNAV':
                VANM.Read(buffer, subSize, curPos);
                break;
            case 'MANN':
                NNAM.Read(buffer, subSize, curPos);
                break;
            case '1DWM':
                MWD1.Load();
                MWD1->MWD1.Read(buffer, subSize, curPos);
                break;
            case '2DWM':
                MWD1.Load();
                MWD1->MWD2.Read(buffer, subSize, curPos);
                break;
            case '3DWM':
                MWD1.Load();
                MWD1->MWD3.Read(buffer, subSize, curPos);
                break;
            case '4DWM':
                MWD1.Load();
                MWD1->MWD4.Read(buffer, subSize, curPos);
                break;
            case '5DWM':
                MWD1.Load();
                MWD1->MWD5.Read(buffer, subSize, curPos);
                break;
            case '6DWM':
                MWD1.Load();
                MWD1->MWD6.Read(buffer, subSize, curPos);
                break;
            case '7DWM':
                MWD1.Load();
                MWD1->MWD7.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            case 'MANW':
                WNAM.Read(buffer, subSize, curPos);
                break;
            case '1MNW':
                WNM1.Load();
                WNM1->WNM1.Read(buffer, subSize, curPos);
                break;
            case '2MNW':
                WNM1.Load();
                WNM1->WNM2.Read(buffer, subSize, curPos);
                break;
            case '3MNW':
                WNM1.Load();
                WNM1->WNM3.Read(buffer, subSize, curPos);
                break;
            case '4MNW':
                WNM1.Load();
                WNM1->WNM4.Read(buffer, subSize, curPos);
                break;
            case '5MNW':
                WNM1.Load();
                WNM1->WNM5.Read(buffer, subSize, curPos);
                break;
            case '6MNW':
                WNM1.Load();
                WNM1->WNM6.Read(buffer, subSize, curPos);
                break;
            case '7MNW':
                WNM1.Load();
                WNM1->WNM7.Read(buffer, subSize, curPos);
                break;
            case '1IMW':
                WMI1.Load();
                WMI1->WMI1.Read(buffer, subSize, curPos);
                break;
            case '2IMW':
                WMI1.Load();
                WMI1->WMI2.Read(buffer, subSize, curPos);
                break;
            case '3IMW':
                WMI1.Load();
                WMI1->WMI3.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case '7MAN':
                NAM7.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case '6MAN':
                NAM6.Read(buffer, subSize, curPos);
                break;
            case 'MANU':
                UNAM.Read(buffer, subSize, curPos);
                break;
            case '9MAN':
                NAM9.Read(buffer, subSize, curPos);
                break;
            case '8MAN':
                NAM8.Read(buffer, subSize, curPos);
                break;
            case '1SMW':
                WMS1.Read(buffer, subSize, curPos);
                break;
            case '2SMW':
                WMS2.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'TDRC':
                CRDT.Read(buffer, subSize, curPos);
                break;
            case 'STAV':
                VATS.Read(buffer, subSize, curPos);
                break;
            case 'MANV':
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
    INAM.Unload();
    WNAM.Unload();
    WNM1.Unload();
    WMI1.Unload();
    SNAM.Unload();
    XNAM.Unload();
    NAM7.Unload();
    TNAM.Unload();
    NAM6.Unload();
    UNAM.Unload();
    NAM9.Unload();
    NAM8.Unload();
    WMS1.Unload();
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
        if(MOD2->MOD2.IsLoaded())
            SaveHandler.writeSubRecord('2DOM', MOD2->MOD2.value, MOD2->MOD2.GetSize());

        if(MOD2->MO2T.IsLoaded())
            SaveHandler.writeSubRecord('T2OM', MOD2->MO2T.value, MOD2->MO2T.GetSize());

        if(MOD2->MO2S.IsLoaded())
            SaveHandler.writeSubRecord('S2OM', MOD2->MO2S.value, MOD2->MO2S.GetSize());

        }

    if(MOD3.IsLoaded())
        {
        if(MOD3->MOD3.IsLoaded())
            SaveHandler.writeSubRecord('3DOM', MOD3->MOD3.value, MOD3->MOD3.GetSize());

        if(MOD3->MO3T.IsLoaded())
            SaveHandler.writeSubRecord('T3OM', MOD3->MO3T.value, MOD3->MO3T.GetSize());

        if(MOD3->MO3S.IsLoaded())
            SaveHandler.writeSubRecord('S3OM', MOD3->MO3S.value, MOD3->MO3S.GetSize());

        }

    WRITE(EFSD);

    if(MOD4.IsLoaded())
        {
        if(MOD4->MOD4.IsLoaded())
            SaveHandler.writeSubRecord('4DOM', MOD4->MOD4.value, MOD4->MOD4.GetSize());

        if(MOD4->MO4T.IsLoaded())
            SaveHandler.writeSubRecord('T4OM', MOD4->MO4T.value, MOD4->MO4T.GetSize());

        if(MOD4->MO4S.IsLoaded())
            SaveHandler.writeSubRecord('S4OM', MOD4->MO4S.value, MOD4->MO4S.GetSize());

        }

    WRITE(VANM);
    WRITE(NNAM);

    if(MWD1.IsLoaded())
        {
        if(MWD1->MWD1.IsLoaded())
            SaveHandler.writeSubRecord('1DWM', MWD1->MWD1.value, MWD1->MWD1.GetSize());

        if(MWD1->MWD2.IsLoaded())
            SaveHandler.writeSubRecord('2DWM', MWD1->MWD2.value, MWD1->MWD2.GetSize());

        if(MWD1->MWD3.IsLoaded())
            SaveHandler.writeSubRecord('3DWM', MWD1->MWD3.value, MWD1->MWD3.GetSize());

        if(MWD1->MWD4.IsLoaded())
            SaveHandler.writeSubRecord('4DWM', MWD1->MWD4.value, MWD1->MWD4.GetSize());

        if(MWD1->MWD5.IsLoaded())
            SaveHandler.writeSubRecord('5DWM', MWD1->MWD5.value, MWD1->MWD5.GetSize());

        if(MWD1->MWD6.IsLoaded())
            SaveHandler.writeSubRecord('6DWM', MWD1->MWD6.value, MWD1->MWD6.GetSize());

        if(MWD1->MWD7.IsLoaded())
            SaveHandler.writeSubRecord('7DWM', MWD1->MWD7.value, MWD1->MWD7.GetSize());

        }

    WRITE(INAM);
    WRITE(WNAM);

    if(WNM1.IsLoaded())
        {
        if(WNM1->WNM1.IsLoaded())
            SaveHandler.writeSubRecord('1MNW', WNM1->WNM1.value, WNM1->WNM1.GetSize());

        if(WNM1->WNM2.IsLoaded())
            SaveHandler.writeSubRecord('2MNW', WNM1->WNM2.value, WNM1->WNM2.GetSize());

        if(WNM1->WNM3.IsLoaded())
            SaveHandler.writeSubRecord('3MNW', WNM1->WNM3.value, WNM1->WNM3.GetSize());

        if(WNM1->WNM4.IsLoaded())
            SaveHandler.writeSubRecord('4MNW', WNM1->WNM4.value, WNM1->WNM4.GetSize());

        if(WNM1->WNM5.IsLoaded())
            SaveHandler.writeSubRecord('5MNW', WNM1->WNM5.value, WNM1->WNM5.GetSize());

        if(WNM1->WNM6.IsLoaded())
            SaveHandler.writeSubRecord('6MNW', WNM1->WNM6.value, WNM1->WNM6.GetSize());

        if(WNM1->WNM7.IsLoaded())
            SaveHandler.writeSubRecord('7MNW', WNM1->WNM7.value, WNM1->WNM7.GetSize());

        }

    if(WMI1.IsLoaded())
        {
        if(WMI1->WMI1.IsLoaded())
            SaveHandler.writeSubRecord('1IMW', WMI1->WMI1.value, WMI1->WMI1.GetSize());

        if(WMI1->WMI2.IsLoaded())
            SaveHandler.writeSubRecord('2IMW', WMI1->WMI2.value, WMI1->WMI2.GetSize());

        if(WMI1->WMI3.IsLoaded())
            SaveHandler.writeSubRecord('3IMW', WMI1->WMI3.value, WMI1->WMI3.GetSize());

        }

    WRITE(SNAM);
    WRITE(XNAM);
    WRITE(NAM7);
    WRITE(TNAM);
    WRITE(NAM6);
    WRITE(UNAM);
    WRITE(NAM9);
    WRITE(NAM8);
    WRITE(WMS1);
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
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            SCRI == other.SCRI &&
            EITM == other.EITM &&
            EAMT == other.EAMT &&
            NAM0 == other.NAM0 &&
            Destructable == other.Destructable &&
            REPL == other.REPL &&
            ETYP == other.ETYP &&
            BIPL == other.BIPL &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            MOD2 == other.MOD2 &&
            MOD3 == other.MOD3 &&
            EFSD == other.EFSD &&
            MOD4 == other.MOD4 &&
            VANM.equalsi(other.VANM) &&
            NNAM.equalsi(other.NNAM) &&
            MWD1 == other.MWD1 &&
            INAM == other.INAM &&
            WNAM == other.WNAM &&
            WNM1 == other.WNM1 &&
            WMI1 == other.WMI1 &&
            SNAM == other.SNAM &&
            XNAM == other.XNAM &&
            NAM7 == other.NAM7 &&
            TNAM == other.TNAM &&
            NAM6 == other.NAM6 &&
            UNAM == other.UNAM &&
            NAM9 == other.NAM9 &&
            NAM8 == other.NAM8 &&
            WMS1 == other.WMS1 &&
            WMS2 == other.WMS2 &&
            DATA == other.DATA &&
            DNAM == other.DNAM &&
            CRDT == other.CRDT &&
            VATS == other.VATS &&
            VNAM == other.VNAM);
    }

bool WEAPRecord::operator !=(const WEAPRecord &other) const
    {
    return !(*this == other);
    }
}