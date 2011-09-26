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
#include "..\..\Common.h"
#include "CREARecord.h"

namespace Ob
{
CREARecord::CREADATA::CREADATA():
    creatureType(eCreature),
    combat(50),
    magic(50),
    stealth(50),
    soul(eCommon),
    unused1(0x00),
    health(50),
    attackDamage(0),
    strength(50),
    intelligence(50),
    willpower(50),
    agility(50),
    speed(50),
    endurance(50),
    personality(50),
    luck(50)
    {
    memset(&unused2[0], 0x00, sizeof(unused2));
    }

CREARecord::CREADATA::~CREADATA()
    {
    //
    }

bool CREARecord::CREADATA::operator ==(const CREADATA &other) const
    {
    return (creatureType == other.creatureType &&
            combat == other.combat &&
            magic == other.magic &&
            stealth == other.stealth &&
            soul == other.soul &&
            health == other.health &&
            attackDamage == other.attackDamage &&
            strength == other.strength &&
            intelligence == other.intelligence &&
            willpower == other.willpower &&
            agility == other.agility &&
            speed == other.speed &&
            endurance == other.endurance &&
            personality == other.personality &&
            luck == other.luck);
    }

bool CREARecord::CREADATA::operator !=(const CREADATA &other) const
    {
    return !(*this == other);
    }

bool CREARecord::CREASound::IsLeftFoot()
    {
    return (CSDT.value == eLeftFoot);
    }

void CREARecord::CREASound::IsLeftFoot(bool value)
    {
    if(value)
        CSDT.value = eLeftFoot;
    else if(IsLeftFoot())
        CSDT.value = eRightFoot;
    }

bool CREARecord::CREASound::IsRightFoot()
    {
    return (CSDT.value == eRightFoot);
    }

void CREARecord::CREASound::IsRightFoot(bool value)
    {
    if(value)
        CSDT.value = eRightFoot;
    else if(IsRightFoot())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsLeftBackFoot()
    {
    return (CSDT.value == eLeftBackFoot);
    }

void CREARecord::CREASound::IsLeftBackFoot(bool value)
    {
    if(value)
        CSDT.value = eLeftBackFoot;
    else if(IsLeftBackFoot())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsRightBackFoot()
    {
    return (CSDT.value == eRightBackFoot);
    }

void CREARecord::CREASound::IsRightBackFoot(bool value)
    {
    if(value)
        CSDT.value = eRightBackFoot;
    else if(IsRightBackFoot())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsIdle()
    {
    return (CSDT.value == eIdle);
    }

void CREARecord::CREASound::IsIdle(bool value)
    {
    if(value)
        CSDT.value = eIdle;
    else if(IsIdle())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsAware()
    {
    return (CSDT.value == eAware);
    }

void CREARecord::CREASound::IsAware(bool value)
    {
    if(value)
        CSDT.value = eAware;
    else if(IsAware())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsAttack()
    {
    return (CSDT.value == eAttack);
    }

void CREARecord::CREASound::IsAttack(bool value)
    {
    if(value)
        CSDT.value = eAttack;
    else if(IsAttack())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsHit()
    {
    return (CSDT.value == eHit);
    }

void CREARecord::CREASound::IsHit(bool value)
    {
    if(value)
        CSDT.value = eHit;
    else if(IsHit())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsDeath()
    {
    return (CSDT.value == eDeath);
    }

void CREARecord::CREASound::IsDeath(bool value)
    {
    if(value)
        CSDT.value = eDeath;
    else if(IsDeath())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsWeapon()
    {
    return (CSDT.value == eWeapon);
    }

void CREARecord::CREASound::IsWeapon(bool value)
    {
    if(value)
        CSDT.value = eWeapon;
    else if(IsWeapon())
        CSDT.value = eLeftFoot;
    }

bool CREARecord::CREASound::IsType(UINT32 Type)
    {
    return (CSDT.value == Type);
    }

void CREARecord::CREASound::SetType(UINT32 Type)
    {
    CSDT.value = Type;
    }

void CREARecord::CREASound::Write(FileWriter &writer)
    {
    WRITE(CSDT);
    WRITE(CSDI);
    WRITE(CSDC);
    }

bool CREARecord::CREASound::operator ==(const CREASound &other) const
    {
    return (CSDT == other.CSDT &&
            CSDI == other.CSDI &&
            CSDC == other.CSDC);
    }

bool CREARecord::CREASound::operator !=(const CREASound &other) const
    {
    return !(*this == other);
    }

CREARecord::CREARecord(unsigned char *_recData):
    Record(_recData)
    {
    //Creature AI differs by default from NPC AI
    AIDT.value.aggression = 70;
    //Creature Configuration differs by default from NPC Configuration
    ACBS.value.flags = fIsWalks | fIsNoLowLevel;
    }

CREARecord::CREARecord(CREARecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    SPLO = srcRecord->SPLO;

    NIFZ = srcRecord->NIFZ;
    NIFT = srcRecord->NIFT;
    ACBS = srcRecord->ACBS;
    SNAM = srcRecord->SNAM;
    INAM = srcRecord->INAM;
    SCRI = srcRecord->SCRI;
    CNTO = srcRecord->CNTO;
    AIDT = srcRecord->AIDT;
    PKID = srcRecord->PKID;
    KFFZ = srcRecord->KFFZ;
    DATA = srcRecord->DATA;
    RNAM = srcRecord->RNAM;
    ZNAM = srcRecord->ZNAM;
    TNAM = srcRecord->TNAM;
    BNAM = srcRecord->BNAM;
    WNAM = srcRecord->WNAM;
    CSCR = srcRecord->CSCR;
    NAM0 = srcRecord->NAM0;
    NAM1 = srcRecord->NAM1;
    Sounds = srcRecord->Sounds;
    return;
    }

CREARecord::~CREARecord()
    {
    //
    }

bool CREARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < SPLO.value.size(); ListIndex++)
        op.Accept(SPLO.value[ListIndex]);
    for(UINT32 ListIndex = 0; ListIndex < SNAM.value.size(); ListIndex++)
        op.Accept(SNAM.value[ListIndex]->faction);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(UINT32 ListIndex = 0; ListIndex < CNTO.value.size(); ListIndex++)
        op.Accept(CNTO.value[ListIndex]->item);
    for(UINT32 ListIndex = 0; ListIndex < PKID.value.size(); ListIndex++)
        op.Accept(PKID.value[ListIndex]);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    if(CSCR.IsLoaded())
        op.Accept(CSCR.value);
    for(UINT32 ListIndex = 0; ListIndex < Sounds.value.size(); ListIndex++)
        op.Accept(Sounds.value[ListIndex]->CSDI.value);

    return op.Stop();
    }

bool CREARecord::IsBiped()
    {
    return (ACBS.value.flags & fIsBiped) != 0;
    }

void CREARecord::IsBiped(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsBiped) : (ACBS.value.flags & ~fIsBiped);
    }

bool CREARecord::IsEssential()
    {
    return (ACBS.value.flags & fIsEssential) != 0;
    }

void CREARecord::IsEssential(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsEssential) : (ACBS.value.flags & ~fIsEssential);
    }

bool CREARecord::IsWeaponAndShield()
    {
    return (ACBS.value.flags & fIsWeaponAndShield) != 0;
    }

void CREARecord::IsWeaponAndShield(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsWeaponAndShield) : (ACBS.value.flags & ~fIsWeaponAndShield);
    }

bool CREARecord::IsRespawn()
    {
    return (ACBS.value.flags & fIsRespawn) != 0;
    }

void CREARecord::IsRespawn(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsRespawn) : (ACBS.value.flags & ~fIsRespawn);
    }

bool CREARecord::IsSwims()
    {
    return (ACBS.value.flags & fIsSwims) != 0;
    }

void CREARecord::IsSwims(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsSwims) : (ACBS.value.flags & ~fIsSwims);
    }

bool CREARecord::IsFlies()
    {
    return (ACBS.value.flags & fIsFlies) != 0;
    }

void CREARecord::IsFlies(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsFlies) : (ACBS.value.flags & ~fIsFlies);
    }

bool CREARecord::IsWalks()
    {
    return (ACBS.value.flags & fIsWalks) != 0;
    }

void CREARecord::IsWalks(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsWalks) : (ACBS.value.flags & ~fIsWalks);
    }

bool CREARecord::IsPCLevelOffset()
    {
    return (ACBS.value.flags & fIsPCLevelOffset) != 0;
    }

void CREARecord::IsPCLevelOffset(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsPCLevelOffset) : (ACBS.value.flags & ~fIsPCLevelOffset);
    }

bool CREARecord::IsNoLowLevel()
    {
    return (ACBS.value.flags & fIsNoLowLevel) != 0;
    }

void CREARecord::IsNoLowLevel(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoLowLevel) : (ACBS.value.flags & ~fIsNoLowLevel);
    }

bool CREARecord::IsLowLevel()
    {
    return !IsNoLowLevel();
    }

void CREARecord::IsLowLevel(bool value)
    {
    IsNoLowLevel(!value);
    }

bool CREARecord::IsNoBloodSpray()
    {
    return (ACBS.value.flags & fIsNoBloodSpray) != 0;
    }

void CREARecord::IsNoBloodSpray(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoBloodSpray) : (ACBS.value.flags & ~fIsNoBloodSpray);
    }

bool CREARecord::IsBloodSpray()
    {
    return !IsNoBloodSpray();
    }

void CREARecord::IsBloodSpray(bool value)
    {
    IsNoBloodSpray(!value);
    }

bool CREARecord::IsNoBloodDecal()
    {
    return (ACBS.value.flags & fIsNoBloodDecal) != 0;
    }

void CREARecord::IsNoBloodDecal(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoBloodDecal) : (ACBS.value.flags & ~fIsNoBloodDecal);
    }

bool CREARecord::IsBloodDecal()
    {
    return !IsNoBloodDecal();
    }

void CREARecord::IsBloodDecal(bool value)
    {
    IsNoBloodDecal(!value);
    }

bool CREARecord::IsNoHead()
    {
    return (ACBS.value.flags & fIsNoHead) != 0;
    }

void CREARecord::IsNoHead(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoHead) : (ACBS.value.flags & ~fIsNoHead);
    }

bool CREARecord::IsHead()
    {
    return !IsNoHead();
    }

void CREARecord::IsHead(bool value)
    {
    IsNoHead(!value);
    }

bool CREARecord::IsNoRightArm()
    {
    return (ACBS.value.flags & fIsNoRightArm) != 0;
    }

void CREARecord::IsNoRightArm(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoRightArm) : (ACBS.value.flags & ~fIsNoRightArm);
    }

bool CREARecord::IsRightArm()
    {
    return !IsNoRightArm();
    }

void CREARecord::IsRightArm(bool value)
    {
    IsNoRightArm(!value);
    }

bool CREARecord::IsNoLeftArm()
    {
    return (ACBS.value.flags & fIsNoLeftArm) != 0;
    }

void CREARecord::IsNoLeftArm(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoLeftArm) : (ACBS.value.flags & ~fIsNoLeftArm);
    }

bool CREARecord::IsLeftArm()
    {
    return !IsNoLeftArm();
    }

void CREARecord::IsLeftArm(bool value)
    {
    IsNoLeftArm(!value);
    }

bool CREARecord::IsNoCombatInWater()
    {
    return (ACBS.value.flags & fIsNoCombatInWater) != 0;
    }

void CREARecord::IsNoCombatInWater(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoCombatInWater) : (ACBS.value.flags & ~fIsNoCombatInWater);
    }

bool CREARecord::IsCombatInWater()
    {
    return !IsNoCombatInWater();
    }

void CREARecord::IsCombatInWater(bool value)
    {
    IsNoCombatInWater(!value);
    }

bool CREARecord::IsNoShadow()
    {
    return (ACBS.value.flags & fIsNoShadow) != 0;
    }

void CREARecord::IsNoShadow(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoShadow) : (ACBS.value.flags & ~fIsNoShadow);
    }

bool CREARecord::IsShadow()
    {
    return !IsNoShadow();
    }

void CREARecord::IsShadow(bool value)
    {
    IsNoShadow(!value);
    }

bool CREARecord::IsNoCorpseCheck()
    {
    return (ACBS.value.flags & fIsNoCorpseCheck) != 0;
    }

void CREARecord::IsNoCorpseCheck(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoCorpseCheck) : (ACBS.value.flags & ~fIsNoCorpseCheck);
    }

bool CREARecord::IsCorpseCheck()
    {
    return !IsNoCorpseCheck();
    }

void CREARecord::IsCorpseCheck(bool value)
    {
    IsNoCorpseCheck(!value);
    }

bool CREARecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((ACBS.value.flags & Mask) == Mask) : ((ACBS.value.flags & Mask) != 0);
    }

void CREARecord::SetFlagMask(UINT32 Mask)
    {
    ACBS.value.flags = Mask;
    }

bool CREARecord::IsCreature()
    {
    return (DATA.value.creatureType == eCreature);
    }

void CREARecord::IsCreature(bool value)
    {
    if(value)
        DATA.value.creatureType = eCreature;
    else if(IsCreature())
        DATA.value.creatureType = eDaedra;
    }

bool CREARecord::IsDaedra()
    {
    return (DATA.value.creatureType == eDaedra);
    }

void CREARecord::IsDaedra(bool value)
    {
    if(value)
        DATA.value.creatureType = eDaedra;
    else if(IsDaedra())
        DATA.value.creatureType = eCreature;
    }

bool CREARecord::IsUndead()
    {
    return (DATA.value.creatureType == eUndead);
    }

void CREARecord::IsUndead(bool value)
    {
    if(value)
        DATA.value.creatureType = eUndead;
    else if(IsUndead())
        DATA.value.creatureType = eCreature;
    }

bool CREARecord::IsHumanoid()
    {
    return (DATA.value.creatureType == eHumanoid);
    }

void CREARecord::IsHumanoid(bool value)
    {
    if(value)
        DATA.value.creatureType = eHumanoid;
    else if(IsHumanoid())
        DATA.value.creatureType = eCreature;
    }

bool CREARecord::IsHorse()
    {
    return (DATA.value.creatureType == eHorse);
    }

void CREARecord::IsHorse(bool value)
    {
    if(value)
        DATA.value.creatureType = eHorse;
    else if(IsHorse())
        DATA.value.creatureType = eCreature;
    }

bool CREARecord::IsGiant()
    {
    return (DATA.value.creatureType == eGiant);
    }

void CREARecord::IsGiant(bool value)
    {
    if(value)
        DATA.value.creatureType = eGiant;
    else if(IsGiant())
        DATA.value.creatureType = eCreature;
    }

bool CREARecord::IsType(UINT8 Type)
    {
    return (DATA.value.creatureType == Type);
    }

void CREARecord::SetType(UINT8 Type)
    {
    DATA.value.creatureType = Type;
    }

bool CREARecord::IsNoSoul()
    {
    return (DATA.value.soul == eNone);
    }

void CREARecord::IsNoSoul(bool value)
    {
    if(value)
        DATA.value.soul = eNone;
    else if(IsNoSoul())
        DATA.value.soul = ePetty;
    }

bool CREARecord::IsPettySoul()
    {
    return (DATA.value.soul == ePetty);
    }

void CREARecord::IsPettySoul(bool value)
    {
    if(value)
        DATA.value.soul = ePetty;
    else if(IsPettySoul())
        DATA.value.soul = eNone;
    }

bool CREARecord::IsLesserSoul()
    {
    return (DATA.value.soul == eLesser);
    }

void CREARecord::IsLesserSoul(bool value)
    {
    if(value)
        DATA.value.soul = eLesser;
    else if(IsLesserSoul())
        DATA.value.soul = eNone;
    }

bool CREARecord::IsCommonSoul()
    {
    return (DATA.value.soul == eCommon);
    }

void CREARecord::IsCommonSoul(bool value)
    {
    if(value)
        DATA.value.soul = eCommon;
    else if(IsCommonSoul())
        DATA.value.soul = eNone;
    }

bool CREARecord::IsGreaterSoul()
    {
    return (DATA.value.soul == eGreater);
    }

void CREARecord::IsGreaterSoul(bool value)
    {
    if(value)
        DATA.value.soul = eGreater;
    else if(IsGreaterSoul())
        DATA.value.soul = eNone;
    }

bool CREARecord::IsGrandSoul()
    {
    return (DATA.value.soul == eGrand);
    }

void CREARecord::IsGrandSoul(bool value)
    {
    if(value)
        DATA.value.soul = eGrand;
    else if(IsGrandSoul())
        DATA.value.soul = eNone;
    }

bool CREARecord::IsSoul(UINT8 Type)
    {
    return (DATA.value.soul == Type);
    }

void CREARecord::SetSoul(UINT8 Type)
    {
    DATA.value.soul = Type;
    }

bool CREARecord::IsServicesWeapons()
    {
    return (AIDT.value.flags & fWeapons) != 0;
    }

void CREARecord::IsServicesWeapons(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fWeapons) : (AIDT.value.flags & ~fWeapons);
    }

bool CREARecord::IsServicesArmor()
    {
    return (AIDT.value.flags & fArmor) != 0;
    }

void CREARecord::IsServicesArmor(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fArmor) : (AIDT.value.flags & ~fArmor);
    }

bool CREARecord::IsServicesClothing()
    {
    return (AIDT.value.flags & fClothing) != 0;
    }

void CREARecord::IsServicesClothing(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fClothing) : (AIDT.value.flags & ~fClothing);
    }

bool CREARecord::IsServicesBooks()
    {
    return (AIDT.value.flags & fBooks) != 0;
    }

void CREARecord::IsServicesBooks(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fBooks) : (AIDT.value.flags & ~fBooks);
    }

bool CREARecord::IsServicesIngredients()
    {
    return (AIDT.value.flags & fIngredients) != 0;
    }

void CREARecord::IsServicesIngredients(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fIngredients) : (AIDT.value.flags & ~fIngredients);
    }

bool CREARecord::IsServicesLights()
    {
    return (AIDT.value.flags & fLights) != 0;
    }

void CREARecord::IsServicesLights(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fLights) : (AIDT.value.flags & ~fLights);
    }

bool CREARecord::IsServicesApparatus()
    {
    return (AIDT.value.flags & fApparatus) != 0;
    }

void CREARecord::IsServicesApparatus(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fApparatus) : (AIDT.value.flags & ~fApparatus);
    }

bool CREARecord::IsServicesMiscItems()
    {
    return (AIDT.value.flags & fMiscItems) != 0;
    }

void CREARecord::IsServicesMiscItems(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fMiscItems) : (AIDT.value.flags & ~fMiscItems);
    }

bool CREARecord::IsServicesSpells()
    {
    return (AIDT.value.flags & fSpells) != 0;
    }

void CREARecord::IsServicesSpells(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fSpells) : (AIDT.value.flags & ~fSpells);
    }

bool CREARecord::IsServicesMagicItems()
    {
    return (AIDT.value.flags & fMagicItems) != 0;
    }

void CREARecord::IsServicesMagicItems(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fMagicItems) : (AIDT.value.flags & ~fMagicItems);
    }

bool CREARecord::IsServicesPotions()
    {
    return (AIDT.value.flags & fPotions) != 0;
    }

void CREARecord::IsServicesPotions(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fPotions) : (AIDT.value.flags & ~fPotions);
    }

bool CREARecord::IsServicesTraining()
    {
    return (AIDT.value.flags & fTraining) != 0;
    }

void CREARecord::IsServicesTraining(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fTraining) : (AIDT.value.flags & ~fTraining);
    }

bool CREARecord::IsServicesRecharge()
    {
    return (AIDT.value.flags & fRecharge) != 0;
    }

void CREARecord::IsServicesRecharge(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fRecharge) : (AIDT.value.flags & ~fRecharge);
    }

bool CREARecord::IsServicesRepair()
    {
    return (AIDT.value.flags & fRepair) != 0;
    }

void CREARecord::IsServicesRepair(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fRepair) : (AIDT.value.flags & ~fRepair);
    }

bool CREARecord::IsServicesFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((AIDT.value.flags & Mask) == Mask) : ((AIDT.value.flags & Mask) != 0);
    }

void CREARecord::SetServicesFlagMask(UINT32 Mask)
    {
    AIDT.value.flags = Mask;
    }

UINT32 CREARecord::GetType()
    {
    return REV32(CREA);
    }

STRING CREARecord::GetStrType()
    {
    return "CREA";
    }

SINT32 CREARecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    FORMID curFormID = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SPLO):
                SPLO.Read(buffer, subSize);
                break;
            case REV32(NIFZ):
                NIFZ.Read(buffer, subSize);
                break;
            case REV32(NIFT):
                NIFT.Read(buffer, subSize, CompressedOnDisk);
                //Hack
                {
                bool unload_nift = true;
                for(UINT32 x = 0; x < NIFT.GetSize(); ++x)
                    if(NIFT.value[x] != 0)
                        {
                        unload_nift = false;
                        break;
                        }
                if(unload_nift)
                    NIFT.Unload();
                }
                break;
            case REV32(ACBS):
                ACBS.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(CNTO):
                CNTO.Read(buffer, subSize);
                break;
            case REV32(AIDT):
                AIDT.Read(buffer, subSize);
                break;
            case REV32(PKID):
                PKID.Read(buffer, subSize);
                break;
            case REV32(KFFZ):
                KFFZ.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize);
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(CSCR):
                CSCR.Read(buffer, subSize);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(CSDT):
                Sounds.value.push_back(new CREASound);
                Sounds.value.back()->CSDT.Read(buffer, subSize);
                break;
            case REV32(CSDI):
                if(Sounds.value.size() == 0)
                    Sounds.value.push_back(new CREASound);
                Sounds.value.back()->CSDI.Read(buffer, subSize);
                break;
            case REV32(CSDC):
                if(Sounds.value.size() == 0)
                    Sounds.value.push_back(new CREASound);
                Sounds.value.back()->CSDC.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CREA: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        }
    return 0;
    }

SINT32 CREARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    SPLO.Unload();
    NIFZ.Unload();
    NIFT.Unload();
    ACBS.Unload();
    SNAM.Unload();
    INAM.Unload();
    SCRI.Unload();
    CNTO.Unload();
    AIDT.Unload();
    PKID.Unload();
    KFFZ.Unload();
    DATA.Unload();
    RNAM.Unload();
    ZNAM.Unload();
    TNAM.Unload();
    BNAM.Unload();
    WNAM.Unload();
    CSCR.Unload();
    NAM0.Unload();
    NAM1.Unload();
    Sounds.Unload();
    return 1;
    }

SINT32 CREARecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(SPLO);
    WRITE(NIFZ);
    WRITE(NIFT);
    WRITE(ACBS);
    WRITE(SNAM);
    WRITE(INAM);
    WRITE(SCRI);
    WRITE(CNTO);
    WRITE(AIDT);
    WRITE(PKID);
    WRITE(KFFZ);
    WRITE(DATA);
    WRITE(RNAM);
    WRITE(ZNAM);
    WRITE(TNAM);
    WRITE(BNAM);
    WRITE(WNAM);
    WRITE(CSCR);
    WRITE(NAM0);
    WRITE(NAM1);
    Sounds.Write(writer);
    return -1;
    }

bool CREARecord::operator ==(const CREARecord &other) const
    {
    return (ACBS == other.ACBS &&
            INAM == other.INAM &&
            SCRI == other.SCRI &&
            AIDT == other.AIDT &&
            DATA == other.DATA &&
            RNAM == other.RNAM &&
            ZNAM == other.ZNAM &&
            TNAM == other.TNAM &&
            BNAM == other.BNAM &&
            WNAM == other.WNAM &&
            CSCR == other.CSCR &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NAM0.equalsi(other.NAM0) &&
            NAM1.equalsi(other.NAM1) &&
            MODL == other.MODL &&
            NIFT == other.NIFT &&
            SPLO == other.SPLO &&
            SNAM == other.SNAM &&
            CNTO == other.CNTO &&
            PKID == other.PKID &&
            Sounds == other.Sounds &&
            NIFZ.equalsi(other.NIFZ) &&
            KFFZ.equalsi(other.KFFZ));
    }

bool CREARecord::operator !=(const CREARecord &other) const
    {
    return !(*this == other);
    }

bool CREARecord::equals(Record *other)
    {
    return *this == *(CREARecord *)other;
    }
}