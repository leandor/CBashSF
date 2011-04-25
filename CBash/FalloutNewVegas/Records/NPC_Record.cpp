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
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
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

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
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
    if(value)
        Dummy->flags |= fIsFemale;
    else
        Dummy->flags &= ~fIsFemale;
    }

bool NPC_Record::IsEssential()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEssential) != 0;
    }

void NPC_Record::IsEssential(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsEssential;
    else
        Dummy->flags &= ~fIsEssential;
    }

bool NPC_Record::IsCharGenFacePreset()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsCharGenFacePreset) != 0;
    }

void NPC_Record::IsCharGenFacePreset(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsCharGenFacePreset;
    else
        Dummy->flags &= ~fIsCharGenFacePreset;
    }

bool NPC_Record::IsRespawn()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRespawn) != 0;
    }

void NPC_Record::IsRespawn(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRespawn;
    else
        Dummy->flags &= ~fIsRespawn;
    }

bool NPC_Record::IsAutoCalcStats()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAutoCalcStats) != 0;
    }

void NPC_Record::IsAutoCalcStats(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsAutoCalcStats;
    else
        Dummy->flags &= ~fIsAutoCalcStats;
    }

bool NPC_Record::IsPCLevelOffset()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPCLevelOffset) != 0;
    }

void NPC_Record::IsPCLevelOffset(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPCLevelOffset;
    else
        Dummy->flags &= ~fIsPCLevelOffset;
    }

bool NPC_Record::IsUseTemplate()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseTemplate) != 0;
    }

void NPC_Record::IsUseTemplate(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseTemplate;
    else
        Dummy->flags &= ~fIsUseTemplate;
    }

bool NPC_Record::IsNoLowLevel()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoLowLevel) != 0;
    }

void NPC_Record::IsNoLowLevel(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoLowLevel;
    else
        Dummy->flags &= ~fIsNoLowLevel;
    }

bool NPC_Record::IsNoBloodSpray()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoBloodSpray) != 0;
    }

void NPC_Record::IsNoBloodSpray(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoBloodSpray;
    else
        Dummy->flags &= ~fIsNoBloodSpray;
    }

bool NPC_Record::IsNoBloodDecal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoBloodDecal) != 0;
    }

void NPC_Record::IsNoBloodDecal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoBloodDecal;
    else
        Dummy->flags &= ~fIsNoBloodDecal;
    }

bool NPC_Record::IsNoVATSMelee()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoVATSMelee) != 0;
    }

void NPC_Record::IsNoVATSMelee(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoVATSMelee;
    else
        Dummy->flags &= ~fIsNoVATSMelee;
    }

bool NPC_Record::IsCanBeAllRaces()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsCanBeAllRaces) != 0;
    }

void NPC_Record::IsCanBeAllRaces(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsCanBeAllRaces;
    else
        Dummy->flags &= ~fIsCanBeAllRaces;
    }

bool NPC_Record::IsAutoCalcService()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAutoCalcService) != 0;
    }

void NPC_Record::IsAutoCalcService(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsAutoCalcService;
    else
        Dummy->flags &= ~fIsAutoCalcService;
    }

bool NPC_Record::IsNoKnockdowns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoKnockdowns) != 0;
    }

void NPC_Record::IsNoKnockdowns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoKnockdowns;
    else
        Dummy->flags &= ~fIsNoKnockdowns;
    }

bool NPC_Record::IsNotPushable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNotPushable) != 0;
    }

void NPC_Record::IsNotPushable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNotPushable;
    else
        Dummy->flags &= ~fIsNotPushable;
    }

bool NPC_Record::IsNoHeadTracking()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoHeadTracking) != 0;
    }

void NPC_Record::IsNoHeadTracking(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoHeadTracking;
    else
        Dummy->flags &= ~fIsNoHeadTracking;
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
    if(value)
        Dummy->flags |= fIsUseTraits;
    else
        Dummy->flags &= ~fIsUseTraits;
    }

bool NPC_Record::IsUseStats()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseStats) != 0;
    }

void NPC_Record::IsUseStats(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseStats;
    else
        Dummy->flags &= ~fIsUseStats;
    }

bool NPC_Record::IsUseFactions()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseFactions) != 0;
    }

void NPC_Record::IsUseFactions(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseFactions;
    else
        Dummy->flags &= ~fIsUseFactions;
    }

bool NPC_Record::IsUseAEList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAEList) != 0;
    }

void NPC_Record::IsUseAEList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseAEList;
    else
        Dummy->flags &= ~fIsUseAEList;
    }

bool NPC_Record::IsUseAIData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAIData) != 0;
    }

void NPC_Record::IsUseAIData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseAIData;
    else
        Dummy->flags &= ~fIsUseAIData;
    }

bool NPC_Record::IsUseAIPackages()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAIPackages) != 0;
    }

void NPC_Record::IsUseAIPackages(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseAIPackages;
    else
        Dummy->flags &= ~fIsUseAIPackages;
    }

bool NPC_Record::IsUseModelAnim()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseModelAnim) != 0;
    }

void NPC_Record::IsUseModelAnim(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseModelAnim;
    else
        Dummy->flags &= ~fIsUseModelAnim;
    }

bool NPC_Record::IsUseBaseData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseBaseData) != 0;
    }

void NPC_Record::IsUseBaseData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseBaseData;
    else
        Dummy->flags &= ~fIsUseBaseData;
    }

bool NPC_Record::IsUseInventory()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseInventory) != 0;
    }

void NPC_Record::IsUseInventory(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseInventory;
    else
        Dummy->flags &= ~fIsUseInventory;
    }

bool NPC_Record::IsUseScript()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseScript) != 0;
    }

void NPC_Record::IsUseScript(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseScript;
    else
        Dummy->flags &= ~fIsUseScript;
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
    if(value)
        Dummy->flags |= fIsAggroRadiusBehavior;
    else
        Dummy->flags &= ~fIsAggroRadiusBehavior;
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
    if(value)
        Dummy->flags = eUnaggressive;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsAggressive()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAggressive);
    }

void NPC_Record::IsAggressive(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAggressive;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsVeryAggressive()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryAggressive);
    }

void NPC_Record::IsVeryAggressive(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eVeryAggressive;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsFrenzied()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFrenzied);
    }

void NPC_Record::IsFrenzied(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eFrenzied;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsAggressionType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
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
    if(value)
        Dummy->flags = eCowardly;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsCautious()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCautious);
    }

void NPC_Record::IsCautious(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCautious;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsAverage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAverage);
    }

void NPC_Record::IsAverage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAverage;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsBrave()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBrave);
    }

void NPC_Record::IsBrave(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eBrave;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsFoolhardy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFoolhardy);
    }

void NPC_Record::IsFoolhardy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eFoolhardy;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsConfidenceType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
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
    if(value)
        Dummy->flags = eNeutral;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsAfraid()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAfraid);
    }

void NPC_Record::IsAfraid(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAfraid;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsAnnoyed()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAnnoyed);
    }

void NPC_Record::IsAnnoyed(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAnnoyed;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsCocky()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCocky);
    }

void NPC_Record::IsCocky(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCocky;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsDrugged()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDrugged);
    }

void NPC_Record::IsDrugged(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDrugged;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsPleasant()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePleasant);
    }

void NPC_Record::IsPleasant(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = ePleasant;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsAngry()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAngry);
    }

void NPC_Record::IsAngry(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAngry;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsSad()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSad);
    }

void NPC_Record::IsSad(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eSad;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsMoodType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
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
    if(value)
        Dummy->flags = eHelpsNobody;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsHelpsAllies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHelpsAllies);
    }

void NPC_Record::IsHelpsAllies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHelpsAllies;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsHelpsFriendsAndAllies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHelpsFriendsAndAllies);
    }

void NPC_Record::IsHelpsFriendsAndAllies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHelpsFriendsAndAllies;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsAssistanceType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
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
    if(value)
        Dummy->flags = eStone;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsDirt()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDirt);
    }

void NPC_Record::IsDirt(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDirt;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsGrass()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGrass);
    }

void NPC_Record::IsGrass(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eGrass;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsGlass()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGlass);
    }

void NPC_Record::IsGlass(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eGlass;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMetal);
    }

void NPC_Record::IsMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eMetal;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsWood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWood);
    }

void NPC_Record::IsWood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eWood;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsOrganic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganic);
    }

void NPC_Record::IsOrganic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eOrganic;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsCloth()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCloth);
    }

void NPC_Record::IsCloth(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCloth;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsWater()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWater);
    }

void NPC_Record::IsWater(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eWater;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsHollowMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHollowMetal);
    }

void NPC_Record::IsHollowMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHollowMetal;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsOrganicBug()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganicBug);
    }

void NPC_Record::IsOrganicBug(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eOrganicBug;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsOrganicGlow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganicGlow);
    }

void NPC_Record::IsOrganicGlow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eOrganicGlow;
    else
        Dummy->flags = eDummyDefault;
    }

bool NPC_Record::IsImpactType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void NPC_Record::SetImpactType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 NPC_Record::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(OBND.IsLoaded())
        TotSize += OBND.GetSize() + 6;

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            {
            cSize = MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODB.IsLoaded())
            {
            cSize = MODL->MODB.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODS.IsLoaded())
            TotSize += MODL->MODS.GetSize() + 6;
        if(MODL->MODD.IsLoaded())
            TotSize += MODL->MODD.GetSize() + 6;
        }

    if(ACBS.IsLoaded())
        TotSize += ACBS.GetSize() + 6;

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(INAM.IsLoaded())
        TotSize += INAM.GetSize() + 6;

    if(VTCK.IsLoaded())
        TotSize += VTCK.GetSize() + 6;

    if(TPLT.IsLoaded())
        TotSize += TPLT.GetSize() + 6;

    if(RNAM.IsLoaded())
        TotSize += RNAM.GetSize() + 6;

    if(SPLO.IsLoaded())
        TotSize += SPLO.GetSize() + 6;

    if(EITM.IsLoaded())
        TotSize += EITM.GetSize() + 6;

    if(EAMT.IsLoaded())
        TotSize += EAMT.GetSize() + 6;

    if(DEST.IsLoaded())
        {
        if(DEST->DEST.IsLoaded())
            TotSize += DEST->DEST.GetSize() + 6;
        if(DEST->DSTD.IsLoaded())
            TotSize += DEST->DSTD.GetSize() + 6;
        if(DEST->DMDL.IsLoaded())
            {
            cSize = DEST->DMDL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(DEST->DMDT.IsLoaded())
            {
            cSize = DEST->DMDT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(DEST->DSTF.IsLoaded())
            TotSize += DEST->DSTF.GetSize() + 6;
        }

    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;

    if(CNTO.IsLoaded())
        TotSize += CNTO.GetSize() + 6;

    if(AIDT.IsLoaded())
        TotSize += AIDT.GetSize() + 6;

    if(PKID.IsLoaded())
        TotSize += PKID.GetSize() + 6;

    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(HNAM.IsLoaded())
        TotSize += HNAM.GetSize() + 6;

    if(LNAM.IsLoaded())
        TotSize += LNAM.GetSize() + 6;

    if(ENAM.IsLoaded())
        TotSize += ENAM.GetSize() + 6;

    if(HCLR.IsLoaded())
        TotSize += HCLR.GetSize() + 6;

    if(ZNAM.IsLoaded())
        TotSize += ZNAM.GetSize() + 6;

    if(NAM4.IsLoaded())
        TotSize += NAM4.GetSize() + 6;

    if(FGGS.IsLoaded())
        {
        if(FGGS->FGGS.IsLoaded())
            {
            cSize = FGGS->FGGS.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FGGS->FGGA.IsLoaded())
            {
            cSize = FGGS->FGGA.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FGGS->FGTS.IsLoaded())
            {
            cSize = FGGS->FGTS.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(NAM5.IsLoaded())
        TotSize += NAM5.GetSize() + 6;

    if(NAM6.IsLoaded())
        TotSize += NAM6.GetSize() + 6;

    if(NAM7.IsLoaded())
        TotSize += NAM7.GetSize() + 6;

    return TotSize;
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
                MODL->MODS.Read(buffer, subSize, curPos);
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

SINT32 NPC_Record::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());

        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', MODL->MODB.value, MODL->MODB.GetSize());

        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());

        if(MODL->MODS.IsLoaded())
            SaveHandler.writeSubRecord('SDOM', MODL->MODS.value, MODL->MODS.GetSize());

        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', MODL->MODD.value, MODL->MODD.GetSize());

        }

    if(ACBS.IsLoaded())
        SaveHandler.writeSubRecord('SBCA', ACBS.value, ACBS.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(INAM.IsLoaded())
        SaveHandler.writeSubRecord('MANI', INAM.value, INAM.GetSize());

    if(VTCK.IsLoaded())
        SaveHandler.writeSubRecord('KCTV', VTCK.value, VTCK.GetSize());

    if(TPLT.IsLoaded())
        SaveHandler.writeSubRecord('TLPT', TPLT.value, TPLT.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

    if(SPLO.IsLoaded())
        SaveHandler.writeSubRecord('OLPS', SPLO.value, SPLO.GetSize());

    if(EITM.IsLoaded())
        SaveHandler.writeSubRecord('MTIE', EITM.value, EITM.GetSize());

    if(EAMT.IsLoaded())
        SaveHandler.writeSubRecord('TMAE', EAMT.value, EAMT.GetSize());

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

    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord('IRCS', SCRI.value, SCRI.GetSize());

    if(CNTO.IsLoaded())
        SaveHandler.writeSubRecord('OTNC', CNTO.value, CNTO.GetSize());

    if(AIDT.IsLoaded())
        SaveHandler.writeSubRecord('TDIA', AIDT.value, AIDT.GetSize());

    if(PKID.IsLoaded())
        SaveHandler.writeSubRecord('DIKP', PKID.value, PKID.GetSize());

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', PNAM.value, PNAM.GetSize());

    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANH', HNAM.value, HNAM.GetSize());

    if(LNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANL', LNAM.value, LNAM.GetSize());

    if(ENAM.IsLoaded())
        SaveHandler.writeSubRecord('MANE', ENAM.value, ENAM.GetSize());

    if(HCLR.IsLoaded())
        SaveHandler.writeSubRecord('RLCH', HCLR.value, HCLR.GetSize());

    if(ZNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANZ', ZNAM.value, ZNAM.GetSize());

    if(NAM4.IsLoaded())
        SaveHandler.writeSubRecord('4MAN', NAM4.value, NAM4.GetSize());

    if(FGGS.IsLoaded())
        {
        if(FGGS->FGGS.IsLoaded())
            SaveHandler.writeSubRecord('SGGF', FGGS->FGGS.value, FGGS->FGGS.GetSize());

        if(FGGS->FGGA.IsLoaded())
            SaveHandler.writeSubRecord('AGGF', FGGS->FGGA.value, FGGS->FGGA.GetSize());

        if(FGGS->FGTS.IsLoaded())
            SaveHandler.writeSubRecord('STGF', FGGS->FGTS.value, FGGS->FGTS.GetSize());

        }

    if(NAM5.IsLoaded())
        SaveHandler.writeSubRecord('5MAN', NAM5.value, NAM5.GetSize());

    if(NAM6.IsLoaded())
        SaveHandler.writeSubRecord('6MAN', NAM6.value, NAM6.GetSize());

    if(NAM7.IsLoaded())
        SaveHandler.writeSubRecord('7MAN', NAM7.value, NAM7.GetSize());

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