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
#include "NPC_Record.h"

namespace FNV
{
NPC_Record::NPC_DATA::NPC_DATA():
    baseHealth(0),
    strength(0),
    perception(0),
    endurance(0),
    charisma(0),
    intelligence(0),
    agility(0),
    luck(0)
    {
    //
    }

NPC_Record::NPC_DATA::~NPC_DATA()
    {
    //
    }

bool NPC_Record::NPC_DATA::operator ==(const NPC_DATA &other) const
    {
    return (baseHealth == other.baseHealth &&
            strength == other.strength &&
            perception == other.perception &&
            endurance == other.endurance &&
            charisma == other.charisma &&
            intelligence == other.intelligence &&
            agility == other.agility &&
            luck == other.luck);
    }

bool NPC_Record::NPC_DATA::operator !=(const NPC_DATA &other) const
    {
    return !(*this == other);
    }

NPC_Record::NPC_DNAM::NPC_DNAM():
    barter(0),
    bigGuns(0),
    energy(0),
    explosives(0),
    lockpick(0),
    medicine(0),
    melee(0),
    repair(0),
    science(0),
    guns(0),
    sneak(0),
    speech(0),
    survival(0),
    unarmed(0),
    barterBoost(0),
    bigGunsBoost(0),
    energyBoost(0),
    explosivesBoost(0),
    lockpickBoost(0),
    medicineBoost(0),
    meleeBoost(0),
    repairBoost(0),
    scienceBoost(0),
    gunsBoost(0),
    sneakBoost(0),
    speechBoost(0),
    survivalBoost(0),
    unarmedBoost(0)
    {
    //
    }

NPC_Record::NPC_DNAM::~NPC_DNAM()
    {
    //
    }

bool NPC_Record::NPC_DNAM::operator ==(const NPC_DNAM &other) const
    {
    return (barter == other.barter &&
            bigGuns == other.bigGuns &&
            energy == other.energy &&
            explosives == other.explosives &&
            lockpick == other.lockpick &&
            medicine == other.medicine &&
            melee == other.melee &&
            repair == other.repair &&
            science == other.science &&
            guns == other.guns &&
            sneak == other.sneak &&
            speech == other.speech &&
            survival == other.survival &&
            unarmed == other.unarmed &&
            barterBoost == other.barterBoost &&
            bigGunsBoost == other.bigGunsBoost &&
            energyBoost == other.energyBoost &&
            explosivesBoost == other.explosivesBoost &&
            lockpickBoost == other.lockpickBoost &&
            medicineBoost == other.medicineBoost &&
            meleeBoost == other.meleeBoost &&
            repairBoost == other.repairBoost &&
            scienceBoost == other.scienceBoost &&
            gunsBoost == other.gunsBoost &&
            sneakBoost == other.sneakBoost &&
            speechBoost == other.speechBoost &&
            survivalBoost == other.survivalBoost &&
            unarmedBoost == other.unarmedBoost);
    }

bool NPC_Record::NPC_DNAM::operator !=(const NPC_DNAM &other) const
    {
    return !(*this == other);
    }

NPC_Record::NPC_Record(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }
NPC_Record::NPC_Record(NPC_Record *srcRecord):
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
    ACBS = srcRecord->ACBS;
    SNAM = srcRecord->SNAM;
    INAM = srcRecord->INAM;
    VTCK = srcRecord->VTCK;
    TPLT = srcRecord->TPLT;
    RNAM = srcRecord->RNAM;
    SPLO = srcRecord->SPLO;
    EITM = srcRecord->EITM;
    EAMT = srcRecord->EAMT;
    Destructable = srcRecord->Destructable;
    SCRI = srcRecord->SCRI;
    CNTO = srcRecord->CNTO;
    AIDT = srcRecord->AIDT;
    PKID = srcRecord->PKID;
    CNAM = srcRecord->CNAM;
    DATA = srcRecord->DATA;
    DNAM = srcRecord->DNAM;
    PNAM = srcRecord->PNAM;
    HNAM = srcRecord->HNAM;
    LNAM = srcRecord->LNAM;
    ENAM = srcRecord->ENAM;
    HCLR = srcRecord->HCLR;
    ZNAM = srcRecord->ZNAM;
    NAM4 = srcRecord->NAM4;
    FGGS = srcRecord->FGGS;
    FGGA = srcRecord->FGGA;
    FGTS = srcRecord->FGTS;
    NAM5 = srcRecord->NAM5;
    NAM6 = srcRecord->NAM6;
    NAM7 = srcRecord->NAM7;
    return;
    }

NPC_Record::~NPC_Record()
    {
    //
    }

bool NPC_Record::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(UINT32 x = 0; x < SNAM.value.size(); x++)
        op.Accept(SNAM.value[x]->faction);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(VTCK.IsLoaded())
        op.Accept(VTCK.value);
    if(TPLT.IsLoaded())
        op.Accept(TPLT.value);
    if(RNAM.IsLoaded())
        op.Accept(RNAM.value);
    for(UINT32 x = 0; x < SPLO.value.size(); x++)
        op.Accept(SPLO.value[x]);
    if(EITM.IsLoaded())
        op.Accept(EITM.value);
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(UINT32 x = 0; x < CNTO.value.size(); ++x)
        {
        op.Accept(CNTO.value[x]->CNTO.value.item);
        if(CNTO.value[x]->IsGlobal())
            op.Accept(CNTO.value[x]->COED->globalOrRank);
        }
    for(UINT32 x = 0; x < PKID.value.size(); x++)
        op.Accept(PKID.value[x]);
    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);
    for(UINT32 x = 0; x < PNAM.value.size(); x++)
        op.Accept(PNAM.value[x]);
    if(HNAM.IsLoaded())
        op.Accept(HNAM.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    return op.Stop();
    }

bool NPC_Record::IsFemale()
    {
    return (ACBS.value.flags & fIsFemale) != 0;
    }

void NPC_Record::IsFemale(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsFemale) : (ACBS.value.flags & ~fIsFemale);
    }

bool NPC_Record::IsEssential()
    {
    return (ACBS.value.flags & fIsEssential) != 0;
    }

void NPC_Record::IsEssential(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsEssential) : (ACBS.value.flags & ~fIsEssential);
    }

bool NPC_Record::IsCharGenFacePreset()
    {
    return (ACBS.value.flags & fIsCharGenFacePreset) != 0;
    }

void NPC_Record::IsCharGenFacePreset(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsCharGenFacePreset) : (ACBS.value.flags & ~fIsCharGenFacePreset);
    }

bool NPC_Record::IsRespawn()
    {
    return (ACBS.value.flags & fIsRespawn) != 0;
    }

void NPC_Record::IsRespawn(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsRespawn) : (ACBS.value.flags & ~fIsRespawn);
    }

bool NPC_Record::IsAutoCalcStats()
    {
    return (ACBS.value.flags & fIsAutoCalcStats) != 0;
    }

void NPC_Record::IsAutoCalcStats(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsAutoCalcStats) : (ACBS.value.flags & ~fIsAutoCalcStats);
    }

bool NPC_Record::IsPCLevelOffset()
    {
    return (ACBS.value.flags & fIsPCLevelOffset) != 0;
    }

void NPC_Record::IsPCLevelOffset(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsPCLevelOffset) : (ACBS.value.flags & ~fIsPCLevelOffset);
    }

bool NPC_Record::IsUseTemplate()
    {
    return (ACBS.value.flags & fIsUseTemplate) != 0;
    }

void NPC_Record::IsUseTemplate(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsUseTemplate) : (ACBS.value.flags & ~fIsUseTemplate);
    }

bool NPC_Record::IsNoLowLevel()
    {
    return (ACBS.value.flags & fIsNoLowLevel) != 0;
    }

void NPC_Record::IsNoLowLevel(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoLowLevel) : (ACBS.value.flags & ~fIsNoLowLevel);
    }

bool NPC_Record::IsNoBloodSpray()
    {
    return (ACBS.value.flags & fIsNoBloodSpray) != 0;
    }

void NPC_Record::IsNoBloodSpray(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoBloodSpray) : (ACBS.value.flags & ~fIsNoBloodSpray);
    }

bool NPC_Record::IsNoBloodDecal()
    {
    return (ACBS.value.flags & fIsNoBloodDecal) != 0;
    }

void NPC_Record::IsNoBloodDecal(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoBloodDecal) : (ACBS.value.flags & ~fIsNoBloodDecal);
    }

bool NPC_Record::IsNoVATSMelee()
    {
    return (ACBS.value.flags & fIsNoVATSMelee) != 0;
    }

void NPC_Record::IsNoVATSMelee(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoVATSMelee) : (ACBS.value.flags & ~fIsNoVATSMelee);
    }

bool NPC_Record::IsCanBeAllRaces()
    {
    return (ACBS.value.flags & fIsCanBeAllRaces) != 0;
    }

void NPC_Record::IsCanBeAllRaces(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsCanBeAllRaces) : (ACBS.value.flags & ~fIsCanBeAllRaces);
    }

bool NPC_Record::IsAutoCalcService()
    {
    return (ACBS.value.flags & fIsAutoCalcService) != 0;
    }

void NPC_Record::IsAutoCalcService(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsAutoCalcService) : (ACBS.value.flags & ~fIsAutoCalcService);
    }

bool NPC_Record::IsNoKnockdowns()
    {
    return (ACBS.value.flags & fIsNoKnockdowns) != 0;
    }

void NPC_Record::IsNoKnockdowns(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoKnockdowns) : (ACBS.value.flags & ~fIsNoKnockdowns);
    }

bool NPC_Record::IsNotPushable()
    {
    return (ACBS.value.flags & fIsNotPushable) != 0;
    }

void NPC_Record::IsNotPushable(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNotPushable) : (ACBS.value.flags & ~fIsNotPushable);
    }

bool NPC_Record::IsNoHeadTracking()
    {
    return (ACBS.value.flags & fIsNoHeadTracking) != 0;
    }

void NPC_Record::IsNoHeadTracking(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoHeadTracking) : (ACBS.value.flags & ~fIsNoHeadTracking);
    }

bool NPC_Record::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((ACBS.value.flags & Mask) == Mask) : ((ACBS.value.flags & Mask) != 0);
    }

void NPC_Record::SetFlagMask(UINT32 Mask)
    {
    ACBS.value.flags = Mask;
    }

bool NPC_Record::IsUseTraits()
    {
    return (ACBS.value.templateFlags & fIsUseTraits) != 0;
    }

void NPC_Record::IsUseTraits(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseTraits) : (ACBS.value.templateFlags & ~fIsUseTraits);
    }

bool NPC_Record::IsUseStats()
    {
    return (ACBS.value.templateFlags & fIsUseStats) != 0;
    }

void NPC_Record::IsUseStats(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseStats) : (ACBS.value.templateFlags & ~fIsUseStats);
    }

bool NPC_Record::IsUseFactions()
    {
    return (ACBS.value.templateFlags & fIsUseFactions) != 0;
    }

void NPC_Record::IsUseFactions(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseFactions) : (ACBS.value.templateFlags & ~fIsUseFactions);
    }

bool NPC_Record::IsUseAEList()
    {
    return (ACBS.value.templateFlags & fIsUseAEList) != 0;
    }

void NPC_Record::IsUseAEList(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseAEList) : (ACBS.value.templateFlags & ~fIsUseAEList);
    }

bool NPC_Record::IsUseAIData()
    {
    return (ACBS.value.templateFlags & fIsUseAIData) != 0;
    }

void NPC_Record::IsUseAIData(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseAIData) : (ACBS.value.templateFlags & ~fIsUseAIData);
    }

bool NPC_Record::IsUseAIPackages()
    {
    return (ACBS.value.templateFlags & fIsUseAIPackages) != 0;
    }

void NPC_Record::IsUseAIPackages(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseAIPackages) : (ACBS.value.templateFlags & ~fIsUseAIPackages);
    }

bool NPC_Record::IsUseModelAnim()
    {
    return (ACBS.value.templateFlags & fIsUseModelAnim) != 0;
    }

void NPC_Record::IsUseModelAnim(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseModelAnim) : (ACBS.value.templateFlags & ~fIsUseModelAnim);
    }

bool NPC_Record::IsUseBaseData()
    {
    return (ACBS.value.templateFlags & fIsUseBaseData) != 0;
    }

void NPC_Record::IsUseBaseData(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseBaseData) : (ACBS.value.templateFlags & ~fIsUseBaseData);
    }

bool NPC_Record::IsUseInventory()
    {
    return (ACBS.value.templateFlags & fIsUseInventory) != 0;
    }

void NPC_Record::IsUseInventory(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseInventory) : (ACBS.value.templateFlags & ~fIsUseInventory);
    }

bool NPC_Record::IsUseScript()
    {
    return (ACBS.value.templateFlags & fIsUseScript) != 0;
    }

void NPC_Record::IsUseScript(bool value)
    {
    ACBS.value.templateFlags = value ? (ACBS.value.templateFlags | fIsUseScript) : (ACBS.value.templateFlags & ~fIsUseScript);
    }

bool NPC_Record::IsTemplateFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? ((ACBS.value.templateFlags & Mask) == Mask) : ((ACBS.value.templateFlags & Mask) != 0);
    }

void NPC_Record::SetTemplateFlagMask(UINT16 Mask)
    {
    ACBS.value.templateFlags = Mask;
    }

bool NPC_Record::IsAggroRadiusBehavior()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->aggroFlags & fIsAggroRadiusBehavior) != 0;
    }

void NPC_Record::IsAggroRadiusBehavior(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->aggroFlags = value ? (AIDT->aggroFlags | fIsAggroRadiusBehavior) : (AIDT->aggroFlags & ~fIsAggroRadiusBehavior);
    }

bool NPC_Record::IsAggroFlagMask(UINT8 Mask, bool Exact)
    {
    if(!AIDT.IsLoaded()) return false;
    return Exact ? ((AIDT->aggroFlags & Mask) == Mask) : ((AIDT->aggroFlags & Mask) != 0);
    }

void NPC_Record::SetAggroFlagMask(UINT8 Mask)
    {
    AIDT.Load();
    AIDT->aggroFlags = Mask;
    }

bool NPC_Record::IsServicesWeapons()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesWeapons) != 0;
    }

void NPC_Record::IsServicesWeapons(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesWeapons) : (AIDT->flags & ~fIsServicesWeapons);
    }

bool NPC_Record::IsServicesArmor()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesArmor) != 0;
    }

void NPC_Record::IsServicesArmor(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesArmor) : (AIDT->flags & ~fIsServicesArmor);
    }

bool NPC_Record::IsServicesClothing()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesClothing) != 0;
    }

void NPC_Record::IsServicesClothing(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesClothing) : (AIDT->flags & ~fIsServicesClothing);
    }

bool NPC_Record::IsServicesBooks()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesBooks) != 0;
    }

void NPC_Record::IsServicesBooks(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesBooks) : (AIDT->flags & ~fIsServicesBooks);
    }

bool NPC_Record::IsServicesFood()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesFood) != 0;
    }

void NPC_Record::IsServicesFood(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesFood) : (AIDT->flags & ~fIsServicesFood);
    }

bool NPC_Record::IsServicesChems()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesChems) != 0;
    }

void NPC_Record::IsServicesChems(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesChems) : (AIDT->flags & ~fIsServicesChems);
    }

bool NPC_Record::IsServicesStimpacks()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesStimpacks) != 0;
    }

void NPC_Record::IsServicesStimpacks(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesStimpacks) : (AIDT->flags & ~fIsServicesStimpacks);
    }

bool NPC_Record::IsServicesLights()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesLights) != 0;
    }

void NPC_Record::IsServicesLights(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesLights) : (AIDT->flags & ~fIsServicesLights);
    }

bool NPC_Record::IsServicesMiscItems()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesMiscItems) != 0;
    }

void NPC_Record::IsServicesMiscItems(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesMiscItems) : (AIDT->flags & ~fIsServicesMiscItems);
    }

bool NPC_Record::IsServicesPotions()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesPotions) != 0;
    }

void NPC_Record::IsServicesPotions(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesPotions) : (AIDT->flags & ~fIsServicesPotions);
    }

bool NPC_Record::IsServicesTraining()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesTraining) != 0;
    }

void NPC_Record::IsServicesTraining(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesTraining) : (AIDT->flags & ~fIsServicesTraining);
    }

bool NPC_Record::IsServicesRecharge()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesRecharge) != 0;
    }

void NPC_Record::IsServicesRecharge(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesRecharge) : (AIDT->flags & ~fIsServicesRecharge);
    }

bool NPC_Record::IsServicesRepair()
    {
    if(!AIDT.IsLoaded()) return false;
    return (AIDT->flags & fIsServicesRepair) != 0;
    }

void NPC_Record::IsServicesRepair(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->flags = value ? (AIDT->flags | fIsServicesRepair) : (AIDT->flags & ~fIsServicesRepair);
    }

bool NPC_Record::IsServicesFlagMask(UINT32 Mask, bool Exact)
    {
    if(!AIDT.IsLoaded()) return false;
    return Exact ? ((AIDT->flags & Mask) == Mask) : ((AIDT->flags & Mask) != 0);
    }

void NPC_Record::SetServicesFlagMask(UINT32 Mask)
    {
    AIDT.Load();
    AIDT->flags = Mask;
    }

bool NPC_Record::IsUnaggressive()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->aggression == eUnaggressive;
    }

void NPC_Record::IsUnaggressive(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->aggression = value ? eUnaggressive : eAggressive;
    }

bool NPC_Record::IsAggressive()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->aggression == eAggressive;
    }

void NPC_Record::IsAggressive(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->aggression = value ? eAggressive : eUnaggressive;
    }

bool NPC_Record::IsVeryAggressive()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->aggression == eVeryAggressive;
    }

void NPC_Record::IsVeryAggressive(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->aggression = value ? eVeryAggressive : eUnaggressive;
    }

bool NPC_Record::IsFrenzied()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->aggression == eFrenzied;
    }

void NPC_Record::IsFrenzied(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->aggression = value ? eFrenzied : eUnaggressive;
    }

bool NPC_Record::IsAggressionType(UINT8 Type)
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->aggression == Type;
    }

void NPC_Record::SetAggressionType(UINT8 Type)
    {
    AIDT.Load();
    AIDT->aggression = Type;
    }

bool NPC_Record::IsCowardly()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->confidence == eCowardly;
    }

void NPC_Record::IsCowardly(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->confidence = value ? eCowardly : eCautious;
    }

bool NPC_Record::IsCautious()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->confidence == eCautious;
    }

void NPC_Record::IsCautious(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->confidence = value ? eCautious : eCowardly;
    }

bool NPC_Record::IsAverage()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->confidence == eAverage;
    }

void NPC_Record::IsAverage(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->confidence = value ? eAverage : eCowardly;
    }

bool NPC_Record::IsBrave()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->confidence == eBrave;
    }

void NPC_Record::IsBrave(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->confidence = value ? eBrave : eCowardly;
    }

bool NPC_Record::IsFoolhardy()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->confidence == eFoolhardy;
    }

void NPC_Record::IsFoolhardy(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->confidence = value ? eFoolhardy : eCowardly;
    }

bool NPC_Record::IsConfidenceType(UINT8 Type)
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->confidence == Type;
    }

void NPC_Record::SetConfidenceType(UINT8 Type)
    {
    AIDT.Load();
    AIDT->confidence = Type;
    }

bool NPC_Record::IsNeutral()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == eNeutral;
    }

void NPC_Record::IsNeutral(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->mood = value ? eNeutral : eAfraid;
    }

bool NPC_Record::IsAfraid()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == eAfraid;
    }

void NPC_Record::IsAfraid(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->mood = value ? eAfraid : eNeutral;
    }

bool NPC_Record::IsAnnoyed()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == eAnnoyed;
    }

void NPC_Record::IsAnnoyed(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->mood = value ? eAnnoyed : eNeutral;
    }

bool NPC_Record::IsCocky()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == eCocky;
    }

void NPC_Record::IsCocky(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->mood = value ? eCocky : eNeutral;
    }

bool NPC_Record::IsDrugged()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == eDrugged;
    }

void NPC_Record::IsDrugged(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->mood = value ? eDrugged : eNeutral;
    }

bool NPC_Record::IsPleasant()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == ePleasant;
    }

void NPC_Record::IsPleasant(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->mood = value ? ePleasant : eNeutral;
    }

bool NPC_Record::IsAngry()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == eAngry;
    }

void NPC_Record::IsAngry(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->mood = value ? eAngry : eNeutral;
    }

bool NPC_Record::IsSad()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == eSad;
    }

void NPC_Record::IsSad(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->mood = value ? eSad : eNeutral;
    }

bool NPC_Record::IsMoodType(UINT8 Type)
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->mood == Type;
    }

void NPC_Record::SetMoodType(UINT8 Type)
    {
    AIDT.Load();
    AIDT->mood = Type;
    }

bool NPC_Record::IsHelpsNobody()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->assistance == eHelpsNobody;
    }

void NPC_Record::IsHelpsNobody(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->assistance = value ? eHelpsNobody : eHelpsAllies;
    }

bool NPC_Record::IsHelpsAllies()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->assistance == eHelpsAllies;
    }

void NPC_Record::IsHelpsAllies(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->assistance = value ? eHelpsAllies : eHelpsNobody;
    }

bool NPC_Record::IsHelpsFriendsAndAllies()
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->assistance == eHelpsFriendsAndAllies;
    }

void NPC_Record::IsHelpsFriendsAndAllies(bool value)
    {
    if(!AIDT.IsLoaded()) return;
    AIDT->assistance = value ? eHelpsFriendsAndAllies : eHelpsNobody;
    }

bool NPC_Record::IsAssistanceType(UINT8 Type)
    {
    if(!AIDT.IsLoaded()) return false;
    return AIDT->assistance == Type;
    }

void NPC_Record::SetAssistanceType(UINT8 Type)
    {
    AIDT.Load();
    AIDT->assistance = Type;
    }

bool NPC_Record::IsStone()
    {
    return NAM4.value == eStone;
    }

void NPC_Record::IsStone(bool value)
    {
    NAM4.value = value ? eStone : eDirt;
    }

bool NPC_Record::IsDirt()
    {
    return NAM4.value == eDirt;
    }

void NPC_Record::IsDirt(bool value)
    {
    NAM4.value = value ? eDirt : eStone;
    }

bool NPC_Record::IsGrass()
    {
    return NAM4.value == eGrass;
    }

void NPC_Record::IsGrass(bool value)
    {
    NAM4.value = value ? eGrass : eStone;
    }

bool NPC_Record::IsGlass()
    {
    return NAM4.value == eGlass;
    }

void NPC_Record::IsGlass(bool value)
    {
    NAM4.value = value ? eGlass : eStone;
    }

bool NPC_Record::IsMetal()
    {
    return NAM4.value == eMetal;
    }

void NPC_Record::IsMetal(bool value)
    {
    NAM4.value = value ? eMetal : eStone;
    }

bool NPC_Record::IsWood()
    {
    return NAM4.value == eWood;
    }

void NPC_Record::IsWood(bool value)
    {
    NAM4.value = value ? eWood : eStone;
    }

bool NPC_Record::IsOrganic()
    {
    return NAM4.value == eOrganic;
    }

void NPC_Record::IsOrganic(bool value)
    {
    NAM4.value = value ? eOrganic : eStone;
    }

bool NPC_Record::IsCloth()
    {
    return NAM4.value == eCloth;
    }

void NPC_Record::IsCloth(bool value)
    {
    NAM4.value = value ? eCloth : eStone;
    }

bool NPC_Record::IsWater()
    {
    return NAM4.value == eWater;
    }

void NPC_Record::IsWater(bool value)
    {
    NAM4.value = value ? eWater : eStone;
    }

bool NPC_Record::IsHollowMetal()
    {
    return NAM4.value == eHollowMetal;
    }

void NPC_Record::IsHollowMetal(bool value)
    {
    NAM4.value = value ? eHollowMetal : eStone;
    }

bool NPC_Record::IsOrganicBug()
    {
    return NAM4.value == eOrganicBug;
    }

void NPC_Record::IsOrganicBug(bool value)
    {
    NAM4.value = value ? eOrganicBug : eStone;
    }

bool NPC_Record::IsOrganicGlow()
    {
    return NAM4.value == eOrganicGlow;
    }

void NPC_Record::IsOrganicGlow(bool value)
    {
    NAM4.value = value ? eOrganicGlow : eStone;
    }

bool NPC_Record::IsImpactType(UINT32 Type)
    {
    return NAM4.value == Type;
    }

void NPC_Record::SetImpactType(UINT32 Type)
    {
    NAM4.value = Type;
    }

UINT32 NPC_Record::GetType()
    {
    return REV32(NPC_);
    }

STRING NPC_Record::GetStrType()
    {
    return "NPC_";
    }

SINT32 NPC_Record::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
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
            case REV32(ACBS):
                ACBS.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize, curPos);
                break;
            case REV32(VTCK):
                VTCK.Read(buffer, subSize, curPos);
                break;
            case REV32(TPLT):
                TPLT.Read(buffer, subSize, curPos);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(SPLO):
                SPLO.Read(buffer, subSize, curPos);
                break;
            case REV32(EITM):
                EITM.Read(buffer, subSize, curPos);
                break;
            case REV32(EAMT):
                EAMT.Read(buffer, subSize, curPos);
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize, curPos);
                break;
            case REV32(CNTO):
                CNTO.value.push_back(new FNVCNTO);
                CNTO.value.back()->CNTO.Read(buffer, subSize, curPos);
                break;
            case REV32(COED):
                if(CNTO.value.size() == 0)
                    CNTO.value.push_back(new FNVCNTO);
                CNTO.value.back()->COED.Read(buffer, subSize, curPos);
                break;
            case REV32(AIDT):
                AIDT.Read(buffer, subSize, curPos);
                break;
            case REV32(PKID):
                PKID.Read(buffer, subSize, curPos);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize, curPos);
                break;
            case REV32(HCLR):
                HCLR.Read(buffer, subSize, curPos);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize, curPos);
                break;
            case REV32(FGGS):
                FGGS.Read(buffer, subSize, curPos);
                break;
            case REV32(FGGA):
                FGGA.Read(buffer, subSize, curPos);
                break;
            case REV32(FGTS):
                FGTS.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM5):
                NAM5.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM6):
                NAM6.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM7):
                NAM7.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  NPC_: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 NPC_Record::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ACBS.Unload();
    SNAM.Unload();
    INAM.Unload();
    VTCK.Unload();
    TPLT.Unload();
    RNAM.Unload();
    SPLO.Unload();
    EITM.Unload();
    EAMT.Unload();
    Destructable.Unload();
    SCRI.Unload();
    CNTO.Unload();
    AIDT.Unload();
    PKID.Unload();
    CNAM.Unload();
    DATA.Unload();
    DNAM.Unload();
    PNAM.Unload();
    HNAM.Unload();
    LNAM.Unload();
    ENAM.Unload();
    HCLR.Unload();
    ZNAM.Unload();
    NAM4.Unload();
    FGGS.Unload();
    FGGA.Unload();
    FGTS.Unload();
    NAM5.Unload();
    NAM6.Unload();
    NAM7.Unload();
    return 1;
    }

SINT32 NPC_Record::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ACBS);
    WRITE(SNAM);
    WRITE(INAM);
    WRITE(VTCK);
    WRITE(TPLT);
    WRITE(RNAM);
    WRITE(SPLO);
    WRITE(EITM);
    WRITE(EAMT);
    Destructable.Write(writer);
    WRITE(SCRI);
    CNTO.Write(writer);
    WRITE(AIDT);
    WRITE(PKID);
    WRITE(CNAM);
    WRITE(DATA);
    WRITE(DNAM);
    WRITE(PNAM);
    WRITE(HNAM);
    WRITE(LNAM);
    WRITE(ENAM);
    WRITE(HCLR);
    WRITE(ZNAM);
    WRITE(NAM4);
    WRITE(FGGS);
    WRITE(FGGA);
    WRITE(FGTS);
    WRITE(NAM5);
    WRITE(NAM6);
    WRITE(NAM7);
    return -1;
    }

bool NPC_Record::operator ==(const NPC_Record &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ACBS == other.ACBS &&
            SNAM == other.SNAM &&
            INAM == other.INAM &&
            VTCK == other.VTCK &&
            TPLT == other.TPLT &&
            RNAM == other.RNAM &&
            SPLO == other.SPLO &&
            EITM == other.EITM &&
            EAMT == other.EAMT &&
            Destructable == other.Destructable &&
            SCRI == other.SCRI &&
            CNTO == other.CNTO &&
            AIDT == other.AIDT &&
            PKID == other.PKID &&
            CNAM == other.CNAM &&
            DATA == other.DATA &&
            DNAM == other.DNAM &&
            PNAM == other.PNAM &&
            HNAM == other.HNAM &&
            LNAM == other.LNAM &&
            ENAM == other.ENAM &&
            HCLR == other.HCLR &&
            ZNAM == other.ZNAM &&
            NAM4 == other.NAM4 &&
            FGGS == other.FGGS &&
            FGGA == other.FGGA &&
            FGTS == other.FGTS &&
            NAM5 == other.NAM5 &&
            NAM6 == other.NAM6 &&
            NAM7 == other.NAM7);
    }

bool NPC_Record::operator !=(const NPC_Record &other) const
    {
    return !(*this == other);
    }
}