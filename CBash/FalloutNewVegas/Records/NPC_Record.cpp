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
    if(srcRecord->DEST.IsLoaded())
        {
        DEST.Load();
        DEST->DEST = srcRecord->DEST->DEST;
        DEST->DSTD = srcRecord->DEST->DSTD;
        DEST->DMDL = srcRecord->DEST->DMDL;
        DEST->DMDT = srcRecord->DEST->DMDT;
        DEST->DSTF = srcRecord->DEST->DSTF;
        }
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
    if(srcRecord->FGGS.IsLoaded())
        {
        FGGS.Load();
        FGGS->FGGS = srcRecord->FGGS->FGGS;
        FGGS->FGGA = srcRecord->FGGS->FGGA;
        FGGS->FGTS = srcRecord->FGGS->FGTS;
        }
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
    //if(SNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(SNAM->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);
    if(VTCK.IsLoaded())
        op.Accept(VTCK->value);
    if(TPLT.IsLoaded())
        op.Accept(TPLT->value);
    if(RNAM.IsLoaded())
        op.Accept(RNAM->value);
    if(SPLO.IsLoaded())
        op.Accept(SPLO->value);
    if(EITM.IsLoaded())
        op.Accept(EITM->value);
    if(DEST.IsLoaded() && DEST->DSTD.IsLoaded())
        op.Accept(DEST->DSTD->value);
    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    //if(CNTO.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CNTO->value);
    if(PKID.IsLoaded())
        op.Accept(PKID->value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM->value);
    if(PNAM.IsLoaded())
        op.Accept(PNAM->value);
    if(HNAM.IsLoaded())
        op.Accept(HNAM->value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);

    return op.Stop();
    }

bool NPC_Record::IsFemale()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFemale) != 0;
    }

void NPC_Record::IsFemale(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsFemale) : (Dummy->flags & ~fIsFemale);
    }

bool NPC_Record::IsEssential()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEssential) != 0;
    }

void NPC_Record::IsEssential(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsEssential) : (Dummy->flags & ~fIsEssential);
    }

bool NPC_Record::IsCharGenFacePreset()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsCharGenFacePreset) != 0;
    }

void NPC_Record::IsCharGenFacePreset(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsCharGenFacePreset) : (Dummy->flags & ~fIsCharGenFacePreset);
    }

bool NPC_Record::IsRespawn()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRespawn) != 0;
    }

void NPC_Record::IsRespawn(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRespawn) : (Dummy->flags & ~fIsRespawn);
    }

bool NPC_Record::IsAutoCalcStats()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAutoCalcStats) != 0;
    }

void NPC_Record::IsAutoCalcStats(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAutoCalcStats) : (Dummy->flags & ~fIsAutoCalcStats);
    }

bool NPC_Record::IsPCLevelOffset()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPCLevelOffset) != 0;
    }

void NPC_Record::IsPCLevelOffset(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPCLevelOffset) : (Dummy->flags & ~fIsPCLevelOffset);
    }

bool NPC_Record::IsUseTemplate()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseTemplate) != 0;
    }

void NPC_Record::IsUseTemplate(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseTemplate) : (Dummy->flags & ~fIsUseTemplate);
    }

bool NPC_Record::IsNoLowLevel()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoLowLevel) != 0;
    }

void NPC_Record::IsNoLowLevel(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoLowLevel) : (Dummy->flags & ~fIsNoLowLevel);
    }

bool NPC_Record::IsNoBloodSpray()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoBloodSpray) != 0;
    }

void NPC_Record::IsNoBloodSpray(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoBloodSpray) : (Dummy->flags & ~fIsNoBloodSpray);
    }

bool NPC_Record::IsNoBloodDecal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoBloodDecal) != 0;
    }

void NPC_Record::IsNoBloodDecal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoBloodDecal) : (Dummy->flags & ~fIsNoBloodDecal);
    }

bool NPC_Record::IsNoVATSMelee()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoVATSMelee) != 0;
    }

void NPC_Record::IsNoVATSMelee(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoVATSMelee) : (Dummy->flags & ~fIsNoVATSMelee);
    }

bool NPC_Record::IsCanBeAllRaces()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsCanBeAllRaces) != 0;
    }

void NPC_Record::IsCanBeAllRaces(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsCanBeAllRaces) : (Dummy->flags & ~fIsCanBeAllRaces);
    }

bool NPC_Record::IsAutoCalcService()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAutoCalcService) != 0;
    }

void NPC_Record::IsAutoCalcService(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAutoCalcService) : (Dummy->flags & ~fIsAutoCalcService);
    }

bool NPC_Record::IsNoKnockdowns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoKnockdowns) != 0;
    }

void NPC_Record::IsNoKnockdowns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoKnockdowns) : (Dummy->flags & ~fIsNoKnockdowns);
    }

bool NPC_Record::IsNotPushable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNotPushable) != 0;
    }

void NPC_Record::IsNotPushable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNotPushable) : (Dummy->flags & ~fIsNotPushable);
    }

bool NPC_Record::IsNoHeadTracking()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoHeadTracking) != 0;
    }

void NPC_Record::IsNoHeadTracking(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoHeadTracking) : (Dummy->flags & ~fIsNoHeadTracking);
    }

bool NPC_Record::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void NPC_Record::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool NPC_Record::IsUseTraits()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseTraits) != 0;
    }

void NPC_Record::IsUseTraits(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseTraits) : (Dummy->flags & ~fIsUseTraits);
    }

bool NPC_Record::IsUseStats()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseStats) != 0;
    }

void NPC_Record::IsUseStats(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseStats) : (Dummy->flags & ~fIsUseStats);
    }

bool NPC_Record::IsUseFactions()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseFactions) != 0;
    }

void NPC_Record::IsUseFactions(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseFactions) : (Dummy->flags & ~fIsUseFactions);
    }

bool NPC_Record::IsUseAEList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAEList) != 0;
    }

void NPC_Record::IsUseAEList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseAEList) : (Dummy->flags & ~fIsUseAEList);
    }

bool NPC_Record::IsUseAIData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAIData) != 0;
    }

void NPC_Record::IsUseAIData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseAIData) : (Dummy->flags & ~fIsUseAIData);
    }

bool NPC_Record::IsUseAIPackages()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAIPackages) != 0;
    }

void NPC_Record::IsUseAIPackages(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseAIPackages) : (Dummy->flags & ~fIsUseAIPackages);
    }

bool NPC_Record::IsUseModelAnim()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseModelAnim) != 0;
    }

void NPC_Record::IsUseModelAnim(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseModelAnim) : (Dummy->flags & ~fIsUseModelAnim);
    }

bool NPC_Record::IsUseBaseData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseBaseData) != 0;
    }

void NPC_Record::IsUseBaseData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseBaseData) : (Dummy->flags & ~fIsUseBaseData);
    }

bool NPC_Record::IsUseInventory()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseInventory) != 0;
    }

void NPC_Record::IsUseInventory(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseInventory) : (Dummy->flags & ~fIsUseInventory);
    }

bool NPC_Record::IsUseScript()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseScript) != 0;
    }

void NPC_Record::IsUseScript(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseScript) : (Dummy->flags & ~fIsUseScript);
    }

bool NPC_Record::IsTemplateFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void NPC_Record::SetTemplateFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool NPC_Record::IsAggroRadiusBehavior()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAggroRadiusBehavior) != 0;
    }

void NPC_Record::IsAggroRadiusBehavior(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAggroRadiusBehavior) : (Dummy->flags & ~fIsAggroRadiusBehavior);
    }

bool NPC_Record::IsAggroFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void NPC_Record::SetAggroFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool NPC_Record::IsUnaggressive()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnaggressive);
    }

void NPC_Record::IsUnaggressive(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUnaggressive : eDummyDefault;
    }

bool NPC_Record::IsAggressive()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAggressive);
    }

void NPC_Record::IsAggressive(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAggressive : eDummyDefault;
    }

bool NPC_Record::IsVeryAggressive()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryAggressive);
    }

void NPC_Record::IsVeryAggressive(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVeryAggressive : eDummyDefault;
    }

bool NPC_Record::IsFrenzied()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFrenzied);
    }

void NPC_Record::IsFrenzied(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFrenzied : eDummyDefault;
    }

bool NPC_Record::IsAggressionType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void NPC_Record::SetAggressionType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool NPC_Record::IsCowardly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCowardly);
    }

void NPC_Record::IsCowardly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCowardly : eDummyDefault;
    }

bool NPC_Record::IsCautious()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCautious);
    }

void NPC_Record::IsCautious(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCautious : eDummyDefault;
    }

bool NPC_Record::IsAverage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAverage);
    }

void NPC_Record::IsAverage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAverage : eDummyDefault;
    }

bool NPC_Record::IsBrave()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBrave);
    }

void NPC_Record::IsBrave(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBrave : eDummyDefault;
    }

bool NPC_Record::IsFoolhardy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFoolhardy);
    }

void NPC_Record::IsFoolhardy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFoolhardy : eDummyDefault;
    }

bool NPC_Record::IsConfidenceType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void NPC_Record::SetConfidenceType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool NPC_Record::IsNeutral()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNeutral);
    }

void NPC_Record::IsNeutral(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNeutral : eDummyDefault;
    }

bool NPC_Record::IsAfraid()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAfraid);
    }

void NPC_Record::IsAfraid(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAfraid : eDummyDefault;
    }

bool NPC_Record::IsAnnoyed()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAnnoyed);
    }

void NPC_Record::IsAnnoyed(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAnnoyed : eDummyDefault;
    }

bool NPC_Record::IsCocky()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCocky);
    }

void NPC_Record::IsCocky(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCocky : eDummyDefault;
    }

bool NPC_Record::IsDrugged()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDrugged);
    }

void NPC_Record::IsDrugged(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDrugged : eDummyDefault;
    }

bool NPC_Record::IsPleasant()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePleasant);
    }

void NPC_Record::IsPleasant(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePleasant : eDummyDefault;
    }

bool NPC_Record::IsAngry()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAngry);
    }

void NPC_Record::IsAngry(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAngry : eDummyDefault;
    }

bool NPC_Record::IsSad()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSad);
    }

void NPC_Record::IsSad(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSad : eDummyDefault;
    }

bool NPC_Record::IsMoodType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void NPC_Record::SetMoodType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool NPC_Record::IsHelpsNobody()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHelpsNobody);
    }

void NPC_Record::IsHelpsNobody(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHelpsNobody : eDummyDefault;
    }

bool NPC_Record::IsHelpsAllies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHelpsAllies);
    }

void NPC_Record::IsHelpsAllies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHelpsAllies : eDummyDefault;
    }

bool NPC_Record::IsHelpsFriendsAndAllies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHelpsFriendsAndAllies);
    }

void NPC_Record::IsHelpsFriendsAndAllies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHelpsFriendsAndAllies : eDummyDefault;
    }

bool NPC_Record::IsAssistanceType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void NPC_Record::SetAssistanceType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool NPC_Record::IsStone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStone);
    }

void NPC_Record::IsStone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStone : eDummyDefault;
    }

bool NPC_Record::IsDirt()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDirt);
    }

void NPC_Record::IsDirt(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDirt : eDummyDefault;
    }

bool NPC_Record::IsGrass()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGrass);
    }

void NPC_Record::IsGrass(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGrass : eDummyDefault;
    }

bool NPC_Record::IsGlass()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGlass);
    }

void NPC_Record::IsGlass(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGlass : eDummyDefault;
    }

bool NPC_Record::IsMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMetal);
    }

void NPC_Record::IsMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMetal : eDummyDefault;
    }

bool NPC_Record::IsWood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWood);
    }

void NPC_Record::IsWood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWood : eDummyDefault;
    }

bool NPC_Record::IsOrganic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganic);
    }

void NPC_Record::IsOrganic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eOrganic : eDummyDefault;
    }

bool NPC_Record::IsCloth()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCloth);
    }

void NPC_Record::IsCloth(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCloth : eDummyDefault;
    }

bool NPC_Record::IsWater()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWater);
    }

void NPC_Record::IsWater(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWater : eDummyDefault;
    }

bool NPC_Record::IsHollowMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHollowMetal);
    }

void NPC_Record::IsHollowMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHollowMetal : eDummyDefault;
    }

bool NPC_Record::IsOrganicBug()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganicBug);
    }

void NPC_Record::IsOrganicBug(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eOrganicBug : eDummyDefault;
    }

bool NPC_Record::IsOrganicGlow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganicGlow);
    }

void NPC_Record::IsOrganicGlow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eOrganicGlow : eDummyDefault;
    }

bool NPC_Record::IsImpactType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void NPC_Record::SetImpactType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 NPC_Record::GetType()
    {
    return '_CPN';
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
            case 'SBCA':
                ACBS.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            case 'KCTV':
                VTCK.Read(buffer, subSize, curPos);
                break;
            case 'TLPT':
                TPLT.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            case 'OLPS':
                SPLO.Read(buffer, subSize, curPos);
                break;
            case 'MTIE':
                EITM.Read(buffer, subSize, curPos);
                break;
            case 'TMAE':
                EAMT.Read(buffer, subSize, curPos);
                break;
            case 'TSED':
                DEST.Load();
                DEST->DEST.Read(buffer, subSize, curPos);
                break;
            case 'DTSD':
                DEST.Load();
                DEST->DSTD.Read(buffer, subSize, curPos);
                break;
            case 'LDMD':
                DEST.Load();
                DEST->DMDL.Read(buffer, subSize, curPos);
                break;
            case 'TDMD':
                DEST.Load();
                DEST->DMDT.Read(buffer, subSize, curPos);
                break;
            case 'FTSD':
                //DEST.Load();
                //DEST->DSTF.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'OTNC':
                CNTO.Read(buffer, subSize, curPos);
                break;
            case 'TDIA':
                AIDT.Read(buffer, subSize, curPos);
                break;
            case 'DIKP':
                PKID.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANL':
                LNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANE':
                ENAM.Read(buffer, subSize, curPos);
                break;
            case 'RLCH':
                HCLR.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case '4MAN':
                NAM4.Read(buffer, subSize, curPos);
                break;
            case 'SGGF':
                FGGS.Load();
                FGGS->FGGS.Read(buffer, subSize, curPos);
                break;
            case 'AGGF':
                FGGS.Load();
                FGGS->FGGA.Read(buffer, subSize, curPos);
                break;
            case 'STGF':
                FGGS.Load();
                FGGS->FGTS.Read(buffer, subSize, curPos);
                break;
            case '5MAN':
                NAM5.Read(buffer, subSize, curPos);
                break;
            case '6MAN':
                NAM6.Read(buffer, subSize, curPos);
                break;
            case '7MAN':
                NAM7.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  NPC_: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
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
    DEST.Unload();
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

    if(DEST.IsLoaded())
        {
        if(DEST->DEST.IsLoaded())
            SaveHandler.writeSubRecord('TSED', DEST->DEST.value, DEST->DEST.GetSize());

        if(DEST->DSTD.IsLoaded())
            SaveHandler.writeSubRecord('DTSD', DEST->DSTD.value, DEST->DSTD.GetSize());

        if(DEST->DMDL.IsLoaded())
            SaveHandler.writeSubRecord('LDMD', DEST->DMDL.value, DEST->DMDL.GetSize());

        if(DEST->DMDT.IsLoaded())
            SaveHandler.writeSubRecord('TDMD', DEST->DMDT.value, DEST->DMDT.GetSize());

        //if(DEST->DSTF.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('FTSD', DEST->DSTF.value, DEST->DSTF.GetSize());

        }

    WRITE(SCRI);
    WRITE(CNTO);
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

    if(FGGS.IsLoaded())
        {
        if(FGGS->FGGS.IsLoaded())
            SaveHandler.writeSubRecord('SGGF', FGGS->FGGS.value, FGGS->FGGS.GetSize());

        if(FGGS->FGGA.IsLoaded())
            SaveHandler.writeSubRecord('AGGF', FGGS->FGGA.value, FGGS->FGGA.GetSize());

        if(FGGS->FGTS.IsLoaded())
            SaveHandler.writeSubRecord('STGF', FGGS->FGTS.value, FGGS->FGTS.GetSize());

        }

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
            DEST == other.DEST &&
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
            NAM5 == other.NAM5 &&
            NAM6 == other.NAM6 &&
            NAM7 == other.NAM7);
    }

bool NPC_Record::operator !=(const NPC_Record &other) const
    {
    return !(*this == other);
    }
}