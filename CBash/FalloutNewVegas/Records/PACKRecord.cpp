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
#include "PACKRecord.h"

namespace FNV
{
PACKRecord::PACKPKDT::PACKPKDT():
    flags(0),
    aiType(0),
    unused1(0),
    behaviorFlags(0),
    specificFlags(0)
    {
    memset(&unused2[0], 0x00, sizeof(unused2));
    }

PACKRecord::PACKPKDT::~PACKPKDT()
    {
    //
    }

bool PACKRecord::PACKPKDT::operator ==(const PACKPKDT &other) const
    {
    return (flags == other.flags &&
            aiType == other.aiType &&
            behaviorFlags == other.behaviorFlags &&
            specificFlags == other.specificFlags);
    }

bool PACKRecord::PACKPKDT::operator !=(const PACKPKDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPLDT::PACKPLDT():
    locType(0),
    locId(0),
    locRadius(0)
    {
    //
    }

PACKRecord::PACKPLDT::~PACKPLDT()
    {
    //
    }

bool PACKRecord::PACKPLDT::operator ==(const PACKPLDT &other) const
    {
    return (locType == other.locType &&
            locId == other.locId &&
            locRadius == other.locRadius);
    }

bool PACKRecord::PACKPLDT::operator !=(const PACKPLDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPSDT::PACKPSDT():
    month(0),
    day(0),
    date(0),
    time(0),
    duration(0)
    {
    //
    }

PACKRecord::PACKPSDT::~PACKPSDT()
    {
    //
    }

bool PACKRecord::PACKPSDT::operator ==(const PACKPSDT &other) const
    {
    return (month == other.month &&
            day == other.day &&
            date == other.date &&
            time == other.time &&
            duration == other.duration);
    }

bool PACKRecord::PACKPSDT::operator !=(const PACKPSDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPTDT::PACKPTDT():
    targetType(0),
    targetId(0),
    targetCountOrDistance(0),
    unknown(0.0f)
    {
    //
    }

PACKRecord::PACKPTDT::~PACKPTDT()
    {
    //
    }

bool PACKRecord::PACKPTDT::operator ==(const PACKPTDT &other) const
    {
    return (targetType == other.targetType &&
            targetId == other.targetId &&
            targetCountOrDistance == other.targetCountOrDistance &&
            AlmostEqual(unknown,other.unknown,2));
    }

bool PACKRecord::PACKPTDT::operator !=(const PACKPTDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPKW3::PACKPKW3():
    flags(0),
    fireRate(0),
    fireType(0),
    burstNum(0),
    minShots(0),
    maxShots(0),
    minPause(0.0f),
    maxPause(0.0f)
    {
    memset(&unused[0], 0x00, sizeof(unused));
    }

PACKRecord::PACKPKW3::~PACKPKW3()
    {
    //
    }

bool PACKRecord::PACKPKW3::operator ==(const PACKPKW3 &other) const
    {
    return (flags == other.flags &&
            fireRate == other.fireRate &&
            fireType == other.fireType &&
            burstNum == other.burstNum &&
            minShots == other.minShots &&
            maxShots == other.maxShots &&
            AlmostEqual(minPause,other.minPause,2) &&
            AlmostEqual(maxPause,other.maxPause,2));
    }

bool PACKRecord::PACKPKW3::operator !=(const PACKPKW3 &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPKDD::PACKPKDD():
    FOV(0.0f),
    topic(0),
    flags(0),
    dialType(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unknown[0], 0x00, sizeof(unknown));
    }

PACKRecord::PACKPKDD::~PACKPKDD()
    {
    //
    }

bool PACKRecord::PACKPKDD::operator ==(const PACKPKDD &other) const
    {
    return (AlmostEqual(FOV,other.FOV,2) &&
            topic == other.topic &&
            flags == other.flags &&
            dialType == other.dialType &&
            unknown[0] == other.unknown[0] &&
            unknown[1] == other.unknown[1] &&
            unknown[2] == other.unknown[2] &&
            unknown[3] == other.unknown[3]);
    }

bool PACKRecord::PACKPKDD::operator !=(const PACKPKDD &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PACKRecord::PACKRecord(PACKRecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    PKDT = srcRecord->PKDT;
    PLDT = srcRecord->PLDT;
    PLD2 = srcRecord->PLD2;
    PSDT = srcRecord->PSDT;
    PTDT = srcRecord->PTDT;
    CTDA = srcRecord->CTDA;
    IDLF = srcRecord->IDLF;
    IDLC = srcRecord->IDLC;
    IDLT = srcRecord->IDLT;
    IDLA = srcRecord->IDLA;
    IDLB = srcRecord->IDLB;
    PKE2 = srcRecord->PKE2;
    CNAM = srcRecord->CNAM;
    PKFD = srcRecord->PKFD;
    PKPT = srcRecord->PKPT;
    PKW3 = srcRecord->PKW3;
    PTD2 = srcRecord->PTD2;
    PKDD = srcRecord->PKDD;
    BeginINAM = srcRecord->BeginINAM;
    BeginSCHR = srcRecord->BeginSCHR;
    BeginSCDA = srcRecord->BeginSCDA;
    BeginSCTX = srcRecord->BeginSCTX;
    BeginVARS = srcRecord->BeginVARS;
    BeginSCR_ = srcRecord->BeginSCR_;
    BeginTNAM = srcRecord->BeginTNAM;
    EndINAM = srcRecord->EndINAM;
    EndSCHR = srcRecord->EndSCHR;
    EndSCDA = srcRecord->EndSCDA;
    EndSCTX = srcRecord->EndSCTX;
    EndVARS = srcRecord->EndVARS;
    EndSCR_ = srcRecord->EndSCR_;
    EndTNAM = srcRecord->EndTNAM;
    ChangeINAM = srcRecord->ChangeINAM;
    ChangeSCHR = srcRecord->ChangeSCHR;
    ChangeSCDA = srcRecord->ChangeSCDA;
    ChangeSCTX = srcRecord->ChangeSCTX;
    ChangeVARS = srcRecord->ChangeVARS;
    ChangeSCR_ = srcRecord->ChangeSCR_;
    ChangeTNAM = srcRecord->ChangeTNAM;
    return;
    }

PACKRecord::~PACKRecord()
    {
    //
    }

bool PACKRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(PLDT.IsLoaded() && (PLDT->locType < 2 || PLDT->locType == 4))
        op.Accept(PLDT->locId);
    if(PLD2.IsLoaded() && (PLD2->locType < 2 || PLD2->locType == 4))
        op.Accept(PLD2->locId);
    if(PTDT.IsLoaded() && PTDT->targetType < 2)
        op.Accept(PTDT->targetId);
    for(UINT32 ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);
    for(UINT32 ListIndex = 0; ListIndex < IDLA.value.size(); ListIndex++)
        op.Accept(IDLA.value[ListIndex]);
    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);
    if(PTD2.IsLoaded() && PTD2->targetType < 2)
        op.Accept(PTD2->targetId);
    if(PKDD.IsLoaded())
        op.Accept(PKDD->topic);
    op.Accept(BeginINAM.value);
    for(UINT32 ListIndex = 0; ListIndex < BeginSCR_.value.size(); ListIndex++)
        {
        if(BeginSCR_.value[ListIndex]->isSCRO)
            op.Accept(BeginSCR_.value[ListIndex]->reference);
        }
    op.Accept(BeginTNAM.value);
    op.Accept(EndINAM.value);
    for(UINT32 ListIndex = 0; ListIndex < EndSCR_.value.size(); ListIndex++)
        {
        if(EndSCR_.value[ListIndex]->isSCRO)
            op.Accept(EndSCR_.value[ListIndex]->reference);
        }
    op.Accept(EndTNAM.value);
    op.Accept(ChangeINAM.value);
    for(UINT32 ListIndex = 0; ListIndex < ChangeSCR_.value.size(); ListIndex++)
        {
        if(ChangeSCR_.value[ListIndex]->isSCRO)
            op.Accept(ChangeSCR_.value[ListIndex]->reference);
        }
    op.Accept(ChangeTNAM.value);

    return op.Stop();
    }

bool PACKRecord::IsOffersServices()
    {
    return (PKDT.value.flags & fIsOffersServices) != 0;
    }

void PACKRecord::IsOffersServices(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsOffersServices) : (PKDT.value.flags & ~fIsOffersServices);
    }

bool PACKRecord::IsMustReachLocation()
    {
    return (PKDT.value.flags & fIsMustReachLocation) != 0;
    }

void PACKRecord::IsMustReachLocation(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsMustReachLocation) : (PKDT.value.flags & ~fIsMustReachLocation);
    }

bool PACKRecord::IsMustComplete()
    {
    return (PKDT.value.flags & fIsMustComplete) != 0;
    }

void PACKRecord::IsMustComplete(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsMustComplete) : (PKDT.value.flags & ~fIsMustComplete);
    }

bool PACKRecord::IsLockAtStart()
    {
    return (PKDT.value.flags & fIsLockAtStart) != 0;
    }

void PACKRecord::IsLockAtStart(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsLockAtStart) : (PKDT.value.flags & ~fIsLockAtStart);
    }

bool PACKRecord::IsLockAtEnd()
    {
    return (PKDT.value.flags & fIsLockAtEnd) != 0;
    }

void PACKRecord::IsLockAtEnd(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsLockAtEnd) : (PKDT.value.flags & ~fIsLockAtEnd);
    }

bool PACKRecord::IsLockAtLocation()
    {
    return (PKDT.value.flags & fIsLockAtLocation) != 0;
    }

void PACKRecord::IsLockAtLocation(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsLockAtLocation) : (PKDT.value.flags & ~fIsLockAtLocation);
    }

bool PACKRecord::IsUnlockAtStart()
    {
    return (PKDT.value.flags & fIsUnlockAtStart) != 0;
    }

void PACKRecord::IsUnlockAtStart(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsUnlockAtStart) : (PKDT.value.flags & ~fIsUnlockAtStart);
    }

bool PACKRecord::IsUnlockAtEnd()
    {
    return (PKDT.value.flags & fIsUnlockAtEnd) != 0;
    }

void PACKRecord::IsUnlockAtEnd(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsUnlockAtEnd) : (PKDT.value.flags & ~fIsUnlockAtEnd);
    }

bool PACKRecord::IsUnlockAtLocation()
    {
    return (PKDT.value.flags & fIsUnlockAtLocation) != 0;
    }

void PACKRecord::IsUnlockAtLocation(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsUnlockAtLocation) : (PKDT.value.flags & ~fIsUnlockAtLocation);
    }

bool PACKRecord::IsContinueIfPcNear()
    {
    return (PKDT.value.flags & fIsContinueIfPcNear) != 0;
    }

void PACKRecord::IsContinueIfPcNear(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsContinueIfPcNear) : (PKDT.value.flags & ~fIsContinueIfPcNear);
    }

bool PACKRecord::IsOncePerDay()
    {
    return (PKDT.value.flags & fIsOncePerDay) != 0;
    }

void PACKRecord::IsOncePerDay(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsOncePerDay) : (PKDT.value.flags & ~fIsOncePerDay);
    }

bool PACKRecord::IsSkipFallout()
    {
    return (PKDT.value.flags & fIsSkipFallout) != 0;
    }

void PACKRecord::IsSkipFallout(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsSkipFallout) : (PKDT.value.flags & ~fIsSkipFallout);
    }

bool PACKRecord::IsAlwaysRun()
    {
    return (PKDT.value.flags & fIsAlwaysRun) != 0;
    }

void PACKRecord::IsAlwaysRun(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsAlwaysRun) : (PKDT.value.flags & ~fIsAlwaysRun);
    }

bool PACKRecord::IsAlwaysSneak()
    {
    return (PKDT.value.flags & fIsAlwaysSneak) != 0;
    }

void PACKRecord::IsAlwaysSneak(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsAlwaysSneak) : (PKDT.value.flags & ~fIsAlwaysSneak);
    }

bool PACKRecord::IsAllowSwimming()
    {
    return (PKDT.value.flags & fIsAllowSwimming) != 0;
    }

void PACKRecord::IsAllowSwimming(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsAllowSwimming) : (PKDT.value.flags & ~fIsAllowSwimming);
    }

bool PACKRecord::IsAllowFalls()
    {
    return (PKDT.value.flags & fIsAllowFalls) != 0;
    }

void PACKRecord::IsAllowFalls(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsAllowFalls) : (PKDT.value.flags & ~fIsAllowFalls);
    }

bool PACKRecord::IsHeadTrackingOff()
    {
    return (PKDT.value.flags & fIsHeadTrackingOff) != 0;
    }

void PACKRecord::IsHeadTrackingOff(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsHeadTrackingOff) : (PKDT.value.flags & ~fIsHeadTrackingOff);
    }

bool PACKRecord::IsUnequipWeapons()
    {
    return (PKDT.value.flags & fIsUnequipWeapons) != 0;
    }

void PACKRecord::IsUnequipWeapons(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsUnequipWeapons) : (PKDT.value.flags & ~fIsUnequipWeapons);
    }

bool PACKRecord::IsDefensiveCombat()
    {
    return (PKDT.value.flags & fIsDefensiveCombat) != 0;
    }

void PACKRecord::IsDefensiveCombat(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsDefensiveCombat) : (PKDT.value.flags & ~fIsDefensiveCombat);
    }

bool PACKRecord::IsWeaponDrawn()
    {
    return (PKDT.value.flags & fIsWeaponDrawn) != 0;
    }

void PACKRecord::IsWeaponDrawn(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsWeaponDrawn) : (PKDT.value.flags & ~fIsWeaponDrawn);
    }

bool PACKRecord::IsNoIdleAnims()
    {
    return (PKDT.value.flags & fIsNoIdleAnims) != 0;
    }

void PACKRecord::IsNoIdleAnims(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsNoIdleAnims) : (PKDT.value.flags & ~fIsNoIdleAnims);
    }

bool PACKRecord::IsPretendInCombat()
    {
    return (PKDT.value.flags & fIsPretendInCombat) != 0;
    }

void PACKRecord::IsPretendInCombat(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsPretendInCombat) : (PKDT.value.flags & ~fIsPretendInCombat);
    }

bool PACKRecord::IsContinueDuringCombat()
    {
    return (PKDT.value.flags & fIsContinueDuringCombat) != 0;
    }

void PACKRecord::IsContinueDuringCombat(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsContinueDuringCombat) : (PKDT.value.flags & ~fIsContinueDuringCombat);
    }

bool PACKRecord::IsNoCombatAlert()
    {
    return (PKDT.value.flags & fIsNoCombatAlert) != 0;
    }

void PACKRecord::IsNoCombatAlert(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsNoCombatAlert) : (PKDT.value.flags & ~fIsNoCombatAlert);
    }

bool PACKRecord::IsNoWarnAttackBehavior()
    {
    return (PKDT.value.flags & fIsNoWarnAttackBehavior) != 0;
    }

void PACKRecord::IsNoWarnAttackBehavior(bool value)
    {
    PKDT.value.flags = value ? (PKDT.value.flags | fIsNoWarnAttackBehavior) : (PKDT.value.flags & ~fIsNoWarnAttackBehavior);
    }

bool PACKRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((PKDT.value.flags & Mask) == Mask) : ((PKDT.value.flags & Mask) != 0);
    }

void PACKRecord::SetFlagMask(UINT32 Mask)
    {
    PKDT.value.flags = Mask;
    }

bool PACKRecord::IsHellosToPlayer()
    {
    return (PKDT.value.behaviorFlags & fIsHellosToPlayer) != 0;
    }

void PACKRecord::IsHellosToPlayer(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsHellosToPlayer) : (PKDT.value.behaviorFlags & ~fIsHellosToPlayer);
    }

bool PACKRecord::IsRandomConversations()
    {
    return (PKDT.value.behaviorFlags & fIsRandomConversations) != 0;
    }

void PACKRecord::IsRandomConversations(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsRandomConversations) : (PKDT.value.behaviorFlags & ~fIsRandomConversations);
    }

bool PACKRecord::IsObserveCombatBehavior()
    {
    return (PKDT.value.behaviorFlags & fIsObserveCombatBehavior) != 0;
    }

void PACKRecord::IsObserveCombatBehavior(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsObserveCombatBehavior) : (PKDT.value.behaviorFlags & ~fIsObserveCombatBehavior);
    }

bool PACKRecord::IsUnknown4()
    {
    return (PKDT.value.behaviorFlags & fIsUnknown4) != 0;
    }

void PACKRecord::IsUnknown4(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsUnknown4) : (PKDT.value.behaviorFlags & ~fIsUnknown4);
    }

bool PACKRecord::IsReactionToPlayerActions()
    {
    return (PKDT.value.behaviorFlags & fIsReactionToPlayerActions) != 0;
    }

void PACKRecord::IsReactionToPlayerActions(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsReactionToPlayerActions) : (PKDT.value.behaviorFlags & ~fIsReactionToPlayerActions);
    }

bool PACKRecord::IsFriendlyFireComments()
    {
    return (PKDT.value.behaviorFlags & fIsFriendlyFireComments) != 0;
    }

void PACKRecord::IsFriendlyFireComments(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsFriendlyFireComments) : (PKDT.value.behaviorFlags & ~fIsFriendlyFireComments);
    }

bool PACKRecord::IsAggroRadiusBehavior()
    {
    return (PKDT.value.behaviorFlags & fIsAggroRadiusBehavior) != 0;
    }

void PACKRecord::IsAggroRadiusBehavior(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsAggroRadiusBehavior) : (PKDT.value.behaviorFlags & ~fIsAggroRadiusBehavior);
    }

bool PACKRecord::IsAllowIdleChatter()
    {
    return (PKDT.value.behaviorFlags & fIsAllowIdleChatter) != 0;
    }

void PACKRecord::IsAllowIdleChatter(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsAllowIdleChatter) : (PKDT.value.behaviorFlags & ~fIsAllowIdleChatter);
    }

bool PACKRecord::IsAvoidRadiation()
    {
    return (PKDT.value.behaviorFlags & fIsAvoidRadiation) != 0;
    }

void PACKRecord::IsAvoidRadiation(bool value)
    {
    PKDT.value.behaviorFlags = value ? (PKDT.value.behaviorFlags | fIsAvoidRadiation) : (PKDT.value.behaviorFlags & ~fIsAvoidRadiation);
    }

bool PACKRecord::IsBehaviorFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? ((PKDT.value.behaviorFlags & Mask) == Mask) : ((PKDT.value.behaviorFlags & Mask) != 0);
    }

void PACKRecord::SetBehaviorFlagMask(UINT16 Mask)
    {
    PKDT.value.behaviorFlags = Mask;
    }

bool PACKRecord::IsHide()//Ambush only
    {
    return (IsAIAmbush() && PKDT.value.specificFlags & fIsHide) != 0;
    }

void PACKRecord::IsHide(bool value)//Ambush only
    {
    if(!IsAIAmbush()) return;
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsHide) : (PKDT.value.specificFlags & ~fIsHide);
    }

bool PACKRecord::IsNoEating()
    {
    return (!IsAIAmbush() && PKDT.value.specificFlags & fIsNoEating) != 0;
    }

void PACKRecord::IsNoEating(bool value)
    {
    if(IsAIAmbush()) return;
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsNoEating) : (PKDT.value.specificFlags & ~fIsNoEating);
    }

bool PACKRecord::IsNoSleeping()
    {
    return (!IsAIUseItemAt() && PKDT.value.specificFlags & fIsNoSleeping) != 0;
    }

void PACKRecord::IsNoSleeping(bool value)
    {
    if(IsAIUseItemAt()) return;
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsNoSleeping) : (PKDT.value.specificFlags & ~fIsNoSleeping);
    }

bool PACKRecord::IsSitDown()//Use Item At only
    {
    return (IsAIUseItemAt() && PKDT.value.specificFlags & fIsSitDown) != 0;
    }

void PACKRecord::IsSitDown(bool value)//Use Item At only
    {
    if(!IsAIUseItemAt()) return;
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsSitDown) : (PKDT.value.specificFlags & ~fIsSitDown);
    }

bool PACKRecord::IsNoConversation()
    {
    return (!IsAIGuard() && PKDT.value.specificFlags & fIsNoConversation) != 0;
    }

void PACKRecord::IsNoConversation(bool value)
    {
    if(IsAIGuard()) return;
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsNoConversation) : (PKDT.value.specificFlags & ~fIsNoConversation);
    }

bool PACKRecord::IsRemainNearReference()//Guard only
    {
    return (IsAIGuard() && PKDT.value.specificFlags & fIsRemainNearReference) != 0;
    }

void PACKRecord::IsRemainNearReference(bool value)//Guard only
    {
    if(!IsAIGuard()) return;
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsRemainNearReference) : (PKDT.value.specificFlags & ~fIsRemainNearReference);
    }

bool PACKRecord::IsNoIdleMarkers()
    {
    return (PKDT.value.specificFlags & fIsNoIdleMarkers) != 0;
    }

void PACKRecord::IsNoIdleMarkers(bool value)
    {
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsNoIdleMarkers) : (PKDT.value.specificFlags & ~fIsNoIdleMarkers);
    }

bool PACKRecord::IsNoFurniture()
    {
    return (PKDT.value.specificFlags & fIsNoFurniture) != 0;
    }

void PACKRecord::IsNoFurniture(bool value)
    {
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsNoFurniture) : (PKDT.value.specificFlags & ~fIsNoFurniture);
    }

bool PACKRecord::IsNoWandering()
    {
    return (PKDT.value.specificFlags & fIsNoWandering) != 0;
    }

void PACKRecord::IsNoWandering(bool value)
    {
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsNoWandering) : (PKDT.value.specificFlags & ~fIsNoWandering);
    }

bool PACKRecord::IsAllowBuying()
    {
    return (PKDT.value.specificFlags & fIsAllowBuying) != 0;
    }

void PACKRecord::IsAllowBuying(bool value)
    {
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsAllowBuying) : (PKDT.value.specificFlags & ~fIsAllowBuying);
    }

bool PACKRecord::IsAllowKilling()
    {
    return (PKDT.value.specificFlags & fIsAllowKilling) != 0;
    }

void PACKRecord::IsAllowKilling(bool value)
    {
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsAllowKilling) : (PKDT.value.specificFlags & ~fIsAllowKilling);
    }

bool PACKRecord::IsAllowStealing()
    {
    return (PKDT.value.specificFlags & fIsAllowStealing) != 0;
    }

void PACKRecord::IsAllowStealing(bool value)
    {
    PKDT.value.specificFlags = value ? (PKDT.value.specificFlags | fIsAllowStealing) : (PKDT.value.specificFlags & ~fIsAllowStealing);
    }

bool PACKRecord::IsSpecificFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? ((PKDT.value.specificFlags & Mask) == Mask) : ((PKDT.value.specificFlags & Mask) != 0);
    }

void PACKRecord::SetSpecificFlagMask(UINT16 Mask)
    {
    PKDT.value.specificFlags = Mask;
    }

bool PACKRecord::IsRunInSequence()
    {
    return (IDLF.value & fIsRunInSequence) != 0;
    }

void PACKRecord::IsRunInSequence(bool value)
    {
    IDLF.value = value ? (IDLF.value | fIsRunInSequence) : (IDLF.value & ~fIsRunInSequence);
    }

bool PACKRecord::IsDoOnce()
    {
    return (IDLF.value & fIsDoOnce) != 0;
    }

void PACKRecord::IsDoOnce(bool value)
    {
    IDLF.value = value ? (IDLF.value | fIsDoOnce) : (IDLF.value & ~fIsDoOnce);
    }

bool PACKRecord::IsIdleFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((IDLF.value & Mask) == Mask) : ((IDLF.value & Mask) != 0);
    }

void PACKRecord::SetIdleFlagMask(UINT8 Mask)
    {
    IDLF.value = Mask;
    }

bool PACKRecord::IsAlwaysHit()
    {
    if(!PKW3.IsLoaded()) return false;
    return (PKW3->flags & fIsAlwaysHit) != 0;
    }

void PACKRecord::IsAlwaysHit(bool value)
    {
    if(!PKW3.IsLoaded()) return;
    PKW3->flags = value ? (PKW3->flags | fIsAlwaysHit) : (PKW3->flags & ~fIsAlwaysHit);
    }

bool PACKRecord::IsDoNoDamage()
    {
    if(!PKW3.IsLoaded()) return false;
    return (PKW3->flags & fIsDoNoDamage) != 0;
    }

void PACKRecord::IsDoNoDamage(bool value)
    {
    if(!PKW3.IsLoaded()) return;
    PKW3->flags = value ? (PKW3->flags | fIsDoNoDamage) : (PKW3->flags & ~fIsDoNoDamage);
    }

bool PACKRecord::IsCrouchToReload()
    {
    if(!PKW3.IsLoaded()) return false;
    return (PKW3->flags & fIsCrouchToReload) != 0;
    }

void PACKRecord::IsCrouchToReload(bool value)
    {
    if(!PKW3.IsLoaded()) return;
    PKW3->flags = value ? (PKW3->flags | fIsCrouchToReload) : (PKW3->flags & ~fIsCrouchToReload);
    }

bool PACKRecord::IsHoldFireWhenBlocked()
    {
    if(!PKW3.IsLoaded()) return false;
    return (PKW3->flags & fIsHoldFireWhenBlocked) != 0;
    }

void PACKRecord::IsHoldFireWhenBlocked(bool value)
    {
    if(!PKW3.IsLoaded()) return;
    PKW3->flags = value ? (PKW3->flags | fIsHoldFireWhenBlocked) : (PKW3->flags & ~fIsHoldFireWhenBlocked);
    }

bool PACKRecord::IsWeaponFlagMask(UINT32 Mask, bool Exact)
    {
    if(!PKW3.IsLoaded()) return false;
    return Exact ? ((PKW3->flags & Mask) == Mask) : ((PKW3->flags & Mask) != 0);
    }

void PACKRecord::SetWeaponFlagMask(UINT32 Mask)
    {
    PKW3.Load();
    PKW3->flags = Mask;
    }

bool PACKRecord::IsNoHeadtracking()
    {
    if(!PKDD.IsLoaded()) return false;
    return (PKDD->flags & fIsNoHeadtracking) != 0;
    }

void PACKRecord::IsNoHeadtracking(bool value)
    {
    if(!PKDD.IsLoaded()) return;
    PKDD->flags = value ? (PKDD->flags | fIsNoHeadtracking) : (PKDD->flags & ~fIsNoHeadtracking);
    }

bool PACKRecord::IsDontControlTargetMovement()
    {
    if(!PKDD.IsLoaded()) return false;
    return (PKDD->flags & fIsDontControlTargetMovement) != 0;
    }

void PACKRecord::IsDontControlTargetMovement(bool value)
    {
    if(!PKDD.IsLoaded()) return;
    PKDD->flags = value ? (PKDD->flags | fIsDontControlTargetMovement) : (PKDD->flags & ~fIsDontControlTargetMovement);
    }

bool PACKRecord::IsDialogueFlagMask(UINT32 Mask, bool Exact)
    {
    if(!PKDD.IsLoaded()) return false;
    return Exact ? ((PKDD->flags & Mask) == Mask) : ((PKDD->flags & Mask) != 0);
    }

void PACKRecord::SetDialogueFlagMask(UINT32 Mask)
    {
    PKDD.Load();
    PKDD->flags = Mask;
    }

bool PACKRecord::IsBeginScriptEnabled()
    {
    return (BeginSCHR.value.flags & fIsEnabled) != 0;
    }

void PACKRecord::IsBeginScriptEnabled(bool value)
    {
    BeginSCHR.value.flags = value ? (BeginSCHR.value.flags | fIsEnabled) : (BeginSCHR.value.flags & ~fIsEnabled);
    }

bool PACKRecord::IsBeginScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (BeginSCHR.value.flags & Mask) == Mask : (BeginSCHR.value.flags & Mask) != 0;
    }

void PACKRecord::SetBeginScriptFlagMask(UINT16 Mask)
    {
    BeginSCHR.value.flags = Mask;
    }

bool PACKRecord::IsEndScriptEnabled()
    {
    return (EndSCHR.value.flags & fIsEnabled) != 0;
    }

void PACKRecord::IsEndScriptEnabled(bool value)
    {
    EndSCHR.value.flags = value ? (EndSCHR.value.flags | fIsEnabled) : (EndSCHR.value.flags & ~fIsEnabled);
    }

bool PACKRecord::IsEndScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (EndSCHR.value.flags & Mask) == Mask : (EndSCHR.value.flags & Mask) != 0;
    }

void PACKRecord::SetEndScriptFlagMask(UINT16 Mask)
    {
    EndSCHR.value.flags = Mask;
    }

bool PACKRecord::IsChangeScriptEnabled()
    {
    return (ChangeSCHR.value.flags & fIsEnabled) != 0;
    }

void PACKRecord::IsChangeScriptEnabled(bool value)
    {
    ChangeSCHR.value.flags = value ? (ChangeSCHR.value.flags | fIsEnabled) : (ChangeSCHR.value.flags & ~fIsEnabled);
    }

bool PACKRecord::IsChangeScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (ChangeSCHR.value.flags & Mask) == Mask : (ChangeSCHR.value.flags & Mask) != 0;
    }

void PACKRecord::SetChangeScriptFlagMask(UINT16 Mask)
    {
    ChangeSCHR.value.flags = Mask;
    }

bool PACKRecord::IsAIFind()
    {
    return PKDT.value.aiType == eAIFind;
    }

void PACKRecord::IsAIFind(bool value)
    {
    PKDT.value.aiType = value ? eAIFind : eAIFollow;
    }

bool PACKRecord::IsAIFollow()
    {
    return PKDT.value.aiType == eAIFollow;
    }

void PACKRecord::IsAIFollow(bool value)
    {
    PKDT.value.aiType = value ? eAIFollow : eAIFind;
    }

bool PACKRecord::IsAIEscort()
    {
    return PKDT.value.aiType == eAIEscort;
    }

void PACKRecord::IsAIEscort(bool value)
    {
    PKDT.value.aiType = value ? eAIEscort : eAIFind;
    }

bool PACKRecord::IsAIEat()
    {
    return PKDT.value.aiType == eAIEat;
    }

void PACKRecord::IsAIEat(bool value)
    {
    PKDT.value.aiType = value ? eAIEat : eAIFind;
    }

bool PACKRecord::IsAISleep()
    {
    return PKDT.value.aiType == eAISleep;
    }

void PACKRecord::IsAISleep(bool value)
    {
    PKDT.value.aiType = value ? eAISleep : eAIFind;
    }

bool PACKRecord::IsAIWander()
    {
    return PKDT.value.aiType == eAIWander;
    }

void PACKRecord::IsAIWander(bool value)
    {
    PKDT.value.aiType = value ? eAIWander : eAIFind;
    }

bool PACKRecord::IsAITravel()
    {
    return PKDT.value.aiType == eAITravel;
    }

void PACKRecord::IsAITravel(bool value)
    {
    PKDT.value.aiType = value ? eAITravel : eAIFind;
    }

bool PACKRecord::IsAIAccompany()
    {
    return PKDT.value.aiType == eAIAccompany;
    }

void PACKRecord::IsAIAccompany(bool value)
    {
    PKDT.value.aiType = value ? eAIAccompany : eAIFind;
    }

bool PACKRecord::IsAIUseItemAt()
    {
    return PKDT.value.aiType == eAIUseItemAt;
    }

void PACKRecord::IsAIUseItemAt(bool value)
    {
    PKDT.value.aiType = value ? eAIUseItemAt : eAIFind;
    }

bool PACKRecord::IsAIAmbush()
    {
    return PKDT.value.aiType == eAIAmbush;
    }

void PACKRecord::IsAIAmbush(bool value)
    {
    PKDT.value.aiType = value ? eAIAmbush : eAIFind;
    }

bool PACKRecord::IsAIFleeNotCombat()
    {
    return PKDT.value.aiType == eAIFleeNotCombat;
    }

void PACKRecord::IsAIFleeNotCombat(bool value)
    {
    PKDT.value.aiType = value ? eAIFleeNotCombat : eAIFind;
    }

bool PACKRecord::IsAISandbox()
    {
    return PKDT.value.aiType == eAISandbox;
    }

void PACKRecord::IsAISandbox(bool value)
    {
    PKDT.value.aiType = value ? eAISandbox : eAIFind;
    }

bool PACKRecord::IsAIPatrol()
    {
    return PKDT.value.aiType == eAIPatrol;
    }

void PACKRecord::IsAIPatrol(bool value)
    {
    PKDT.value.aiType = value ? eAIPatrol : eAIFind;
    }

bool PACKRecord::IsAIGuard()
    {
    return PKDT.value.aiType == eAIGuard;
    }

void PACKRecord::IsAIGuard(bool value)
    {
    PKDT.value.aiType = value ? eAIGuard : eAIFind;
    }

bool PACKRecord::IsAIDialogue()
    {
    return PKDT.value.aiType == eAIDialogue;
    }

void PACKRecord::IsAIDialogue(bool value)
    {
    PKDT.value.aiType = value ? eAIDialogue : eAIFind;
    }

bool PACKRecord::IsAIUseWeapon()
    {
    return PKDT.value.aiType == eAIUseWeapon;
    }

void PACKRecord::IsAIUseWeapon(bool value)
    {
    PKDT.value.aiType = value ? eAIUseWeapon : eAIFind;
    }

bool PACKRecord::IsAIType(UINT8 Type)
    {
    return PKDT.value.aiType == Type;
    }

void PACKRecord::SetAIType(UINT8 Type)
    {
    PKDT.value.aiType = Type;
    }

bool PACKRecord::IsLoc1NearReference()
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == eLocNearReference;
    }

void PACKRecord::IsLoc1NearReference(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    PLDT->locType = value ? eLocNearReference : eLocInCell;
    }

bool PACKRecord::IsLoc1InCell()
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == eLocInCell;
    }

void PACKRecord::IsLoc1InCell(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    PLDT->locType = value ? eLocInCell : eLocNearReference;
    }

bool PACKRecord::IsLoc1NearCurrentLocation()
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == eLocNearCurrentLocation;
    }

void PACKRecord::IsLoc1NearCurrentLocation(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    PLDT->locType = value ? eLocNearCurrentLocation : eLocNearReference;
    }

bool PACKRecord::IsLoc1NearEditorLocation()
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == eLocNearEditorLocation;
    }

void PACKRecord::IsLoc1NearEditorLocation(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    PLDT->locType = value ? eLocNearEditorLocation : eLocNearReference;
    }

bool PACKRecord::IsLoc1ObjectID()
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == eLocObjectID;
    }

void PACKRecord::IsLoc1ObjectID(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    PLDT->locType = value ? eLocObjectID : eLocNearReference;
    }

bool PACKRecord::IsLoc1ObjectType()
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == eLocObjectType;
    }

void PACKRecord::IsLoc1ObjectType(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    PLDT->locType = value ? eLocObjectType : eLocNearReference;
    }

bool PACKRecord::IsLoc1NearLinkedReference()
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == eLocNearLinkedReference;
    }

void PACKRecord::IsLoc1NearLinkedReference(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    PLDT->locType = value ? eLocNearLinkedReference : eLocNearReference;
    }

bool PACKRecord::IsLoc1AtPackageLocation()
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == eLocAtPackageLocation;
    }

void PACKRecord::IsLoc1AtPackageLocation(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    PLDT->locType = value ? eLocAtPackageLocation : eLocNearReference;
    }

bool PACKRecord::IsLoc1Type(SINT32 Type)
    {
    if(!PLDT.IsLoaded()) return false;
    return PLDT->locType == Type;
    }

void PACKRecord::SetLoc1Type(SINT32 Type)
    {
    PLDT.Load();
    PLDT->locType = Type;
    }

bool PACKRecord::IsLoc2NearReference()
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == eLocNearReference;
    }

void PACKRecord::IsLoc2NearReference(bool value)
    {
    if(!PLD2.IsLoaded()) return;
    PLD2->locType = value ? eLocNearReference : eLocInCell;
    }

bool PACKRecord::IsLoc2InCell()
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == eLocInCell;
    }

void PACKRecord::IsLoc2InCell(bool value)
    {
    if(!PLD2.IsLoaded()) return;
    PLD2->locType = value ? eLocInCell : eLocNearReference;
    }

bool PACKRecord::IsLoc2NearCurrentLocation()
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == eLocNearCurrentLocation;
    }

void PACKRecord::IsLoc2NearCurrentLocation(bool value)
    {
    if(!PLD2.IsLoaded()) return;
    PLD2->locType = value ? eLocNearCurrentLocation : eLocNearReference;
    }

bool PACKRecord::IsLoc2NearEditorLocation()
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == eLocNearEditorLocation;
    }

void PACKRecord::IsLoc2NearEditorLocation(bool value)
    {
    if(!PLD2.IsLoaded()) return;
    PLD2->locType = value ? eLocNearEditorLocation : eLocNearReference;
    }

bool PACKRecord::IsLoc2ObjectID()
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == eLocObjectID;
    }

void PACKRecord::IsLoc2ObjectID(bool value)
    {
    if(!PLD2.IsLoaded()) return;
    PLD2->locType = value ? eLocObjectID : eLocNearReference;
    }

bool PACKRecord::IsLoc2ObjectType()
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == eLocObjectType;
    }

void PACKRecord::IsLoc2ObjectType(bool value)
    {
    if(!PLD2.IsLoaded()) return;
    PLD2->locType = value ? eLocObjectType : eLocNearReference;
    }

bool PACKRecord::IsLoc2NearLinkedReference()
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == eLocNearLinkedReference;
    }

void PACKRecord::IsLoc2NearLinkedReference(bool value)
    {
    if(!PLD2.IsLoaded()) return;
    PLD2->locType = value ? eLocNearLinkedReference : eLocNearReference;
    }

bool PACKRecord::IsLoc2AtPackageLocation()
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == eLocAtPackageLocation;
    }

void PACKRecord::IsLoc2AtPackageLocation(bool value)
    {
    if(!PLD2.IsLoaded()) return;
    PLD2->locType = value ? eLocAtPackageLocation : eLocNearReference;
    }

bool PACKRecord::IsLoc2Type(SINT32 Type)
    {
    if(!PLD2.IsLoaded()) return false;
    return PLD2->locType == Type;
    }

void PACKRecord::SetLoc2Type(SINT32 Type)
    {
    PLD2.Load();
    PLD2->locType = Type;
    }

bool PACKRecord::IsTarget1Reference()
    {
    if(!PTDT.IsLoaded()) return false;
    return PTDT->targetType == eTargetReference;
    }

void PACKRecord::IsTarget1Reference(bool value)
    {
    if(!PTDT.IsLoaded()) return;
    PTDT->targetType = value ? eTargetReference : eTargetObjectID;
    }

bool PACKRecord::IsTarget1ObjectID()
    {
    if(!PTDT.IsLoaded()) return false;
    return PTDT->targetType == eTargetObjectID;
    }

void PACKRecord::IsTarget1ObjectID(bool value)
    {
    if(!PTDT.IsLoaded()) return;
    PTDT->targetType = value ? eTargetObjectID : eTargetReference;
    }

bool PACKRecord::IsTarget1ObjectType()
    {
    if(!PTDT.IsLoaded()) return false;
    return PTDT->targetType == eTargetObjectType;
    }

void PACKRecord::IsTarget1ObjectType(bool value)
    {
    if(!PTDT.IsLoaded()) return;
    PTDT->targetType = value ? eTargetObjectType : eTargetReference;
    }

bool PACKRecord::IsTarget1LinkedReference()
    {
    if(!PTDT.IsLoaded()) return false;
    return PTDT->targetType == eTargetLinkedReference;
    }

void PACKRecord::IsTarget1LinkedReference(bool value)
    {
    if(!PTDT.IsLoaded()) return;
    PTDT->targetType = value ? eTargetLinkedReference : eTargetReference;
    }

bool PACKRecord::IsTarget1Type(SINT32 Type)
    {
    if(!PTDT.IsLoaded()) return false;
    return PTDT->targetType == Type;
    }

void PACKRecord::SetTarget1Type(SINT32 Type)
    {
    PTDT.Load();
    PTDT->targetType = Type;
    }

bool PACKRecord::IsTarget2Reference()
    {
    if(!PTD2.IsLoaded()) return false;
    return PTD2->targetType == eTargetReference;
    }

void PACKRecord::IsTarget2Reference(bool value)
    {
    if(!PTD2.IsLoaded()) return;
    PTD2->targetType = value ? eTargetReference : eTargetObjectID;
    }

bool PACKRecord::IsTarget2ObjectID()
    {
    if(!PTD2.IsLoaded()) return false;
    return PTD2->targetType == eTargetObjectID;
    }

void PACKRecord::IsTarget2ObjectID(bool value)
    {
    if(!PTD2.IsLoaded()) return;
    PTD2->targetType = value ? eTargetObjectID : eTargetReference;
    }

bool PACKRecord::IsTarget2ObjectType()
    {
    if(!PTD2.IsLoaded()) return false;
    return PTD2->targetType == eTargetObjectType;
    }

void PACKRecord::IsTarget2ObjectType(bool value)
    {
    if(!PTD2.IsLoaded()) return;
    PTD2->targetType = value ? eTargetObjectType : eTargetReference;
    }

bool PACKRecord::IsTarget2LinkedReference()
    {
    if(!PTD2.IsLoaded()) return false;
    return PTD2->targetType == eTargetLinkedReference;
    }

void PACKRecord::IsTarget2LinkedReference(bool value)
    {
    if(!PTD2.IsLoaded()) return;
    PTD2->targetType = value ? eTargetLinkedReference : eTargetReference;
    }

bool PACKRecord::IsTarget2Type(SINT32 Type)
    {
    if(!PTD2.IsLoaded()) return false;
    return PTD2->targetType == Type;
    }

void PACKRecord::SetTarget2Type(SINT32 Type)
    {
    PTD2.Load();
    PTD2->targetType = Type;
    }

bool PACKRecord::IsAnyDay()
    {
    return PSDT.value.day == eAnyDay;
    }

void PACKRecord::IsAnyDay(bool value)
    {
    PSDT.value.day = value ? eAnyDay : eSunday;
    }

bool PACKRecord::IsSunday()
    {
    return PSDT.value.day == eSunday;
    }

void PACKRecord::IsSunday(bool value)
    {
    PSDT.value.day = value ? eSunday : eAnyDay;
    }

bool PACKRecord::IsMonday()
    {
    return PSDT.value.day == eMonday;
    }

void PACKRecord::IsMonday(bool value)
    {
    PSDT.value.day = value ? eMonday : eAnyDay;
    }

bool PACKRecord::IsTuesday()
    {
    return PSDT.value.day == eTuesday;
    }

void PACKRecord::IsTuesday(bool value)
    {
    PSDT.value.day = value ? eTuesday : eAnyDay;
    }

bool PACKRecord::IsWednesday()
    {
    return PSDT.value.day == eWednesday;
    }

void PACKRecord::IsWednesday(bool value)
    {
    PSDT.value.day = value ? eWednesday : eAnyDay;
    }

bool PACKRecord::IsThursday()
    {
    return PSDT.value.day == eThursday;
    }

void PACKRecord::IsThursday(bool value)
    {
    PSDT.value.day = value ? eThursday : eAnyDay;
    }

bool PACKRecord::IsFriday()
    {
    return PSDT.value.day == eFriday;
    }

void PACKRecord::IsFriday(bool value)
    {
    PSDT.value.day = value ? eFriday : eAnyDay;
    }

bool PACKRecord::IsSaturday()
    {
    return PSDT.value.day == eSaturday;
    }

void PACKRecord::IsSaturday(bool value)
    {
    PSDT.value.day = value ? eSaturday : eAnyDay;
    }

bool PACKRecord::IsWeekdays()
    {
    return PSDT.value.day == eWeekdays;
    }

void PACKRecord::IsWeekdays(bool value)
    {
    PSDT.value.day = value ? eWeekdays : eAnyDay;
    }

bool PACKRecord::IsWeekends()
    {
    return PSDT.value.day == eWeekends;
    }

void PACKRecord::IsWeekends(bool value)
    {
    PSDT.value.day = value ? eWeekends : eAnyDay;
    }

bool PACKRecord::IsMWF()
    {
    return PSDT.value.day == eMWF;
    }

void PACKRecord::IsMWF(bool value)
    {
    PSDT.value.day = value ? eMWF : eAnyDay;
    }

bool PACKRecord::IsTTh()
    {
    return PSDT.value.day == eTTh;
    }

void PACKRecord::IsTTh(bool value)
    {
    PSDT.value.day = value ? eTTh : eAnyDay;
    }

bool PACKRecord::IsDayType(SINT8 Type)
    {
    return PSDT.value.day == Type;
    }

void PACKRecord::SetDayType(SINT8 Type)
    {
    PSDT.value.day = Type;
    }

bool PACKRecord::IsNotRepeatable()
    {
    return PKPT.value == eNotRepeatable;
    }

void PACKRecord::IsNotRepeatable(bool value)
    {
    PKPT.value = value ? eNotRepeatable : eRepeatable;
    }

bool PACKRecord::IsRepeatable()
    {
    return PKPT.value == eRepeatable;
    }

void PACKRecord::IsRepeatable(bool value)
    {
    PKPT.value = value ? eRepeatable : eNotRepeatable;
    }

bool PACKRecord::IsRepeatType(UINT16 Type)
    {
    return PKPT.value == Type;
    }

void PACKRecord::SetRepeatType(UINT16 Type)
    {
    PKPT.value = Type;
    }

bool PACKRecord::IsAutoFire()
    {
    if(!PKW3.IsLoaded()) return false;
    return PKW3->fireRate == eAutoFire;
    }

void PACKRecord::IsAutoFire(bool value)
    {
    if(!PKW3.IsLoaded()) return;
    PKW3->fireRate = value ? eAutoFire : eVolleyFire;
    }

bool PACKRecord::IsVolleyFire()
    {
    if(!PKW3.IsLoaded()) return false;
    return PKW3->fireRate == eVolleyFire;
    }

void PACKRecord::IsVolleyFire(bool value)
    {
    if(!PKW3.IsLoaded()) return;
    PKW3->fireRate = value ? eVolleyFire : eAutoFire;
    }

bool PACKRecord::IsFireType(UINT8 Type)
    {
    if(!PKW3.IsLoaded()) return false;
    return PKW3->fireRate == Type;
    }

void PACKRecord::SetFireType(UINT8 Type)
    {
    PKW3.Load();
    PKW3->fireRate = Type;
    }

bool PACKRecord::IsNumberOfBursts()
    {
    if(!PKW3.IsLoaded()) return false;
    return PKW3->fireType == eNumberOfBursts;
    }

void PACKRecord::IsNumberOfBursts(bool value)
    {
    if(!PKW3.IsLoaded()) return;
    PKW3->fireType = value ? eNumberOfBursts : eRepeatFire;
    }

bool PACKRecord::IsRepeatFire()
    {
    if(!PKW3.IsLoaded()) return false;
    return PKW3->fireType == eRepeatFire;
    }

void PACKRecord::IsRepeatFire(bool value)
    {
    if(!PKW3.IsLoaded()) return;
    PKW3->fireType = value ? eRepeatFire : eNumberOfBursts;
    }

bool PACKRecord::IsFireCountType(UINT8 Type)
    {
    if(!PKW3.IsLoaded()) return false;
    return PKW3->fireType == Type;
    }

void PACKRecord::SetFireCountType(UINT8 Type)
    {
    PKW3.Load();
    PKW3->fireType = Type;
    }

bool PACKRecord::IsConversation()
    {
    if(!PKDD.IsLoaded()) return false;
    return PKDD->dialType == eConversation;
    }

void PACKRecord::IsConversation(bool value)
    {
    if(!PKDD.IsLoaded()) return;
    PKDD->dialType = value ? eConversation : eSayTo;
    }

bool PACKRecord::IsSayTo()
    {
    if(!PKDD.IsLoaded()) return false;
    return PKDD->dialType == eSayTo;
    }

void PACKRecord::IsSayTo(bool value)
    {
    if(!PKDD.IsLoaded()) return;
    PKDD->dialType = value ? eSayTo : eConversation;
    }

bool PACKRecord::IsDialogueType(UINT32 Type)
    {
    if(!PKDD.IsLoaded()) return false;
    return PKDD->dialType == Type;
    }

void PACKRecord::SetDialogueType(UINT32 Type)
    {
    PKDD.Load();
    PKDD->dialType = Type;
    }

bool PACKRecord::IsBeginObject()
    {
    return BeginSCHR.value.scriptType == eObject;
    }

void PACKRecord::IsBeginObject(bool value)
    {
    BeginSCHR.value.scriptType = value ? eObject : eQuest;
    }

bool PACKRecord::IsBeginQuest()
    {
    return BeginSCHR.value.scriptType == eQuest;
    }

void PACKRecord::IsBeginQuest(bool value)
    {
    BeginSCHR.value.scriptType = value ? eQuest : eObject;
    }

bool PACKRecord::IsBeginEffect()
    {
    return BeginSCHR.value.scriptType == eEffect;
    }

void PACKRecord::IsBeginEffect(bool value)
    {
    BeginSCHR.value.scriptType = value ? eEffect : eObject;
    }

bool PACKRecord::IsBeginType(UINT16 Type)
    {
    return BeginSCHR.value.scriptType == Type;
    }

void PACKRecord::SetBeginType(UINT16 Type)
    {
    BeginSCHR.value.scriptType = Type;
    }

bool PACKRecord::IsEndObject()
    {
    return EndSCHR.value.scriptType == eObject;
    }

void PACKRecord::IsEndObject(bool value)
    {
    EndSCHR.value.scriptType = value ? eObject : eQuest;
    }

bool PACKRecord::IsEndQuest()
    {
    return EndSCHR.value.scriptType == eQuest;
    }

void PACKRecord::IsEndQuest(bool value)
    {
    EndSCHR.value.scriptType = value ? eQuest : eObject;
    }

bool PACKRecord::IsEndEffect()
    {
    return EndSCHR.value.scriptType == eEffect;
    }

void PACKRecord::IsEndEffect(bool value)
    {
    EndSCHR.value.scriptType = value ? eEffect : eObject;
    }

bool PACKRecord::IsEndType(UINT16 Type)
    {
    return EndSCHR.value.scriptType == Type;
    }

void PACKRecord::SetEndType(UINT16 Type)
    {
    EndSCHR.value.scriptType = Type;
    }

bool PACKRecord::IsChangeObject()
    {
    return ChangeSCHR.value.scriptType == eObject;
    }

void PACKRecord::IsChangeObject(bool value)
    {
    ChangeSCHR.value.scriptType = value ? eObject : eQuest;
    }

bool PACKRecord::IsChangeQuest()
    {
    return ChangeSCHR.value.scriptType == eQuest;
    }

void PACKRecord::IsChangeQuest(bool value)
    {
    ChangeSCHR.value.scriptType = value ? eQuest : eObject;
    }

bool PACKRecord::IsChangeEffect()
    {
    return ChangeSCHR.value.scriptType == eEffect;
    }

void PACKRecord::IsChangeEffect(bool value)
    {
    ChangeSCHR.value.scriptType = value ? eEffect : eObject;
    }

bool PACKRecord::IsChangeType(UINT16 Type)
    {
    return ChangeSCHR.value.scriptType == Type;
    }

void PACKRecord::SetChangeType(UINT16 Type)
    {
    ChangeSCHR.value.scriptType = Type;
    }

UINT32 PACKRecord::GetType()
    {
    return REV32(PACK);
    }

STRING PACKRecord::GetStrType()
    {
    return "PACK";
    }

SINT32 PACKRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 lastChunk = 0;
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
            case REV32(PKDT):
                PKDT.Read(buffer, subSize);
                break;
            case REV32(PLDT):
                PLDT.Read(buffer, subSize);
                break;
            case REV32(PLD2):
                PLD2.Read(buffer, subSize);
                //Testing snippet. PLD2 can occur twice in some cases? Second one is always equal to first though...
                //if(PLD2.IsLoaded())
                //    {
                //    OptSubRecord<PACKPLDT> PLD2a;
                //    PLD2a.Read(buffer, subSize);
                //    if(PLD2 != PLD2a)
                //        {
                //        printer("  INFO: %08X - Unexpected PLD2 chunk\n", formID);
                //        CBASH_CHUNK_DEBUG
                //        }
                //    }
                //else
                //    PLD2.Read(buffer, subSize);
                break;
            case REV32(PSDT):
                PSDT.Read(buffer, subSize);
                break;
            case REV32(PTDT):
                PTDT.Read(buffer, subSize);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(IDLF):
                IDLF.Read(buffer, subSize);
                break;
            case REV32(IDLC):
                //Idle Animation Count (may be a UINT32 instead, but only the lower 8 bits are used, so skip extra)
                IDLC.Read(buffer, 1);
                buffer += subSize - 1;
                //Testing snippet. Verified that the extra bits aren't in use in FalloutNV.esm
                //switch(subSize)
                //    {
                //    case 1:
                //        IDLC.Read(buffer, subSize);
                //        break;
                //    case 4:
                //        {
                //        IDLC.Read(buffer, 1);
                //        UINT32 test = 0;
                //        _readBuffer(&test, buffer, 3, curPos);
                //        if(test != 0)
                //            {
                //            printer("  INFO: %08X - Unexpected IDLC value. Expected (0) and got (%u). IDLC = %u.\n", formID, test, IDLC.value);
                //            CBASH_CHUNK_DEBUG
                //            printer("  Size = %i\n", subSize);
                //            printer("  CurPos = %04x\n\n", buffer - 6);
                //            }
                //        }
                //        break;
                //    default:
                //        printer("  INFO: %08X - Unexpected IDLC chunk size. Expected (1 or 4) and got (%u)\n", formID, subSize);
                //        CBASH_CHUNK_DEBUG
                //        printer("  Size = %i\n", subSize);
                //        printer("  CurPos = %04x\n\n", buffer - 6);
                //        buffer += subSize;
                //        break;
                //    }
                break;
            case REV32(IDLT):
                IDLT.Read(buffer, subSize);
                break;
            case REV32(IDLA):
                IDLA.Read(buffer, subSize);
                break;
            case REV32(IDLB):
                IDLB.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(PKE2):
                PKE2.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(PKFD):
                PKFD.Read(buffer, subSize);
                break;
            case REV32(PKPT):
                PKPT.Read(buffer, subSize);
                break;
            case REV32(PKW3):
                PKW3.Read(buffer, subSize);
                break;
            case REV32(PTD2):
                PTD2.Read(buffer, subSize);
                break;
            case REV32(PKDD):
                PKDD.Read(buffer, subSize);
                break;
            case REV32(INAM):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        BeginINAM.Read(buffer, subSize);
                        break;
                    case REV32(POEA):
                        EndINAM.Read(buffer, subSize);
                        break;
                    case REV32(POCA):
                        ChangeINAM.Read(buffer, subSize);
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected INAM chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(SCHR):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        BeginSCHR.Read(buffer, subSize);
                        break;
                    case REV32(POEA):
                        EndSCHR.Read(buffer, subSize);
                        break;
                    case REV32(POCA):
                        ChangeSCHR.Read(buffer, subSize);
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected SCHR chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(SCDA):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        BeginSCDA.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case REV32(POEA):
                        EndSCDA.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case REV32(POCA):
                        ChangeSCDA.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected SCDA chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(SCTX):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        BeginSCTX.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case REV32(POEA):
                        EndSCTX.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case REV32(POCA):
                        ChangeSCTX.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected SCTX chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(SLSD):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        BeginVARS.value.push_back(new GENVARS);
                        BeginVARS.value.back()->SLSD.Read(buffer, subSize);
                        break;
                    case REV32(POEA):
                        EndVARS.value.push_back(new GENVARS);
                        EndVARS.value.back()->SLSD.Read(buffer, subSize);
                        break;
                    case REV32(POCA):
                        ChangeVARS.value.push_back(new GENVARS);
                        ChangeVARS.value.back()->SLSD.Read(buffer, subSize);
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected SLSD chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(SCVR):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        if(BeginVARS.value.size() == 0)
                            BeginVARS.value.push_back(new GENVARS);
                        BeginVARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case REV32(POEA):
                        if(EndVARS.value.size() == 0)
                            EndVARS.value.push_back(new GENVARS);
                        EndVARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case REV32(POCA):
                        if(ChangeVARS.value.size() == 0)
                            ChangeVARS.value.push_back(new GENVARS);
                        ChangeVARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected SCVR chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(SCRV):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        BeginSCR_.Read(buffer, subSize);
                        BeginSCR_.value.back()->isSCRO = false;
                        break;
                    case REV32(POEA):
                        EndSCR_.Read(buffer, subSize);
                        EndSCR_.value.back()->isSCRO = false;
                        break;
                    case REV32(POCA):
                        ChangeSCR_.Read(buffer, subSize);
                        ChangeSCR_.value.back()->isSCRO = false;
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected SCRV chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(SCRO):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        BeginSCR_.Read(buffer, subSize);
                        BeginSCR_.value.back()->isSCRO = true;
                        break;
                    case REV32(POEA):
                        EndSCR_.Read(buffer, subSize);
                        EndSCR_.value.back()->isSCRO = true;
                        break;
                    case REV32(POCA):
                        ChangeSCR_.Read(buffer, subSize);
                        ChangeSCR_.value.back()->isSCRO = true;
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected SCRO chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(TNAM):
                switch(lastChunk)
                    {
                    case REV32(POBA):
                        BeginTNAM.Read(buffer, subSize);
                        break;
                    case REV32(POEA):
                        EndTNAM.Read(buffer, subSize);
                        break;
                    case REV32(POCA):
                        ChangeTNAM.Read(buffer, subSize);
                        break;
                    default:
                        printer("  INFO: %08X - Unexpected TNAM chunk\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(POBA):
                lastChunk = REV32(POBA);
                break;
            case REV32(POEA):
                lastChunk = REV32(POEA);
                break;
            case REV32(POCA):
                lastChunk = REV32(POCA);
                break;
            case REV32(PKED):
                //Testing snippet. TES4Edit isn't clear, but presumably this chunk only occurs when IsAIEat is true...
                if(!IsAIEat())
                    {
                    printer("  INFO: %08X - Unexpected PKED chunk\n", formID);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n\n", buffer - 6);
                    buffer += subSize;
                    }
                break;
            case REV32(PUID):
                //Testing snippet. TES4Edit isn't clear, but presumably this chunk only occurs when IsAIUseItemAt is true...
                if(!IsAIUseItemAt())
                    {
                    printer("  INFO: %08X - Unexpected PUID chunk\n", formID);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n\n", buffer - 6);
                    buffer += subSize;
                    }
                break;
            case REV32(PKAM):
                //Testing snippet. TES4Edit isn't clear, but presumably this chunk only occurs when IsAIAmbush is true...
                if(!IsAIAmbush())
                    {
                    printer("  INFO: %08X - Unexpected PKAM chunk\n", formID);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n\n", buffer - 6);
                    buffer += subSize;
                    }
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  PACK: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 PACKRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    PKDT.Unload();
    PLDT.Unload();
    PLD2.Unload();
    PSDT.Unload();
    PTDT.Unload();
    CTDA.Unload();
    IDLF.Unload();
    IDLC.Unload();
    IDLT.Unload();
    IDLA.Unload();
    IDLB.Unload();
    PKE2.Unload();
    CNAM.Unload();
    PKFD.Unload();
    PKPT.Unload();
    PKW3.Unload();
    PTD2.Unload();
    PKDD.Unload();
    BeginINAM.Unload();
    BeginSCHR.Unload();
    BeginSCDA.Unload();
    BeginSCTX.Unload();
    BeginVARS.Unload();
    BeginSCR_.Unload();
    BeginTNAM.Unload();
    EndINAM.Unload();
    EndSCHR.Unload();
    EndSCDA.Unload();
    EndSCTX.Unload();
    EndVARS.Unload();
    EndSCR_.Unload();
    EndTNAM.Unload();
    ChangeINAM.Unload();
    ChangeSCHR.Unload();
    ChangeSCDA.Unload();
    ChangeSCTX.Unload();
    ChangeVARS.Unload();
    ChangeSCR_.Unload();
    ChangeTNAM.Unload();
    return 1;
    }

SINT32 PACKRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(PKDT);
    WRITE(PLDT);
    WRITE(PLD2);
    WRITE(PSDT);
    WRITE(PTDT);
    CTDA.Write(writer, true);
    if(IDLF.IsLoaded() || IDLC.IsLoaded() || IDLT.IsLoaded() || IDLA.IsLoaded() || IDLB.IsLoaded())
        {
        WRITEREQ(IDLF);
        WRITE(IDLC);
        WRITEREQ(IDLT);
        WRITE(IDLA);
        WRITE(IDLB);
        }
    if(IsAIEat())
        WRITEEMPTY(PKED);
    WRITE(PKE2);
    WRITE(CNAM);
    if(IsAIFollow())
        WRITEREQ(PKFD);
    if(IsAIPatrol())
        WRITEREQ(PKPT);
    WRITE(PKW3);
    WRITE(PTD2);
    if(IsAIUseItemAt())
        WRITEEMPTY(PUID);
    if(IsAIAmbush())
        WRITEEMPTY(PKAM);
    WRITE(PKDD);

    WRITEEMPTY(POBA);
    WRITEAS(BeginINAM,INAM);
    BeginSCHR.value.numRefs = (UINT32)BeginSCR_.value.size(); //Just to ensure that the value is correct
    BeginSCHR.value.compiledSize = BeginSCDA.GetSize(); //Just to ensure that the value is correct
    //for(UINT32 x = 0; x < BeginVARS.value.size(); ++x) //Just to ensure that the value is correct
    //    BeginSCHR.value.lastIndex = (BeginSCHR.value.lastIndex > BeginVARS.value[x]->SLSD.value.index) ? BeginSCHR.value.lastIndex : BeginVARS.value[x]->SLSD.value.index;
    WRITEAS(BeginSCHR,SCHR);
    WRITEAS(BeginSCDA,SCDA);
    WRITEAS(BeginSCTX,SCTX);
    BeginVARS.Write(writer);
    BeginSCR_.Write(writer, true);
    WRITEAS(BeginTNAM,TNAM);

    WRITEEMPTY(POEA);
    WRITEAS(EndINAM,INAM);
    EndSCHR.value.numRefs = (UINT32)EndSCR_.value.size(); //Just to ensure that the value is correct
    EndSCHR.value.compiledSize = EndSCDA.GetSize(); //Just to ensure that the value is correct
    //for(UINT32 x = 0; x < EndVARS.value.size(); ++x) //Just to ensure that the value is correct
    //    EndSCHR.value.lastIndex = (EndSCHR.value.lastIndex > EndVARS.value[x]->SLSD.value.index) ? EndSCHR.value.lastIndex : EndVARS.value[x]->SLSD.value.index;
    WRITEAS(EndSCHR,SCHR);
    WRITEAS(EndSCDA,SCDA);
    WRITEAS(EndSCTX,SCTX);
    EndVARS.Write(writer);
    EndSCR_.Write(writer, true);
    WRITEAS(EndTNAM,TNAM);

    WRITEEMPTY(POCA);
    WRITEAS(ChangeINAM,INAM);
    ChangeSCHR.value.numRefs = (UINT32)ChangeSCR_.value.size(); //Just to ensure that the value is correct
    ChangeSCHR.value.compiledSize = ChangeSCDA.GetSize(); //Just to ensure that the value is correct
    //for(UINT32 x = 0; x < ChangeVARS.value.size(); ++x) //Just to ensure that the value is correct
    //    ChangeSCHR.value.lastIndex = (ChangeSCHR.value.lastIndex > ChangeVARS.value[x]->SLSD.value.index) ? ChangeSCHR.value.lastIndex : ChangeVARS.value[x]->SLSD.value.index;
    WRITEAS(ChangeSCHR,SCHR);
    WRITEAS(ChangeSCDA,SCDA);
    WRITEAS(ChangeSCTX,SCTX);
    ChangeVARS.Write(writer);
    ChangeSCR_.Write(writer, true);
    WRITEAS(ChangeTNAM,TNAM);
    return -1;
    }

bool PACKRecord::operator ==(const PACKRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            PKDT == other.PKDT &&
            PLDT == other.PLDT &&
            PLD2 == other.PLD2 &&
            PSDT == other.PSDT &&
            PTDT == other.PTDT &&
            IDLF == other.IDLF &&
            IDLC == other.IDLC &&
            IDLT == other.IDLT &&
            IDLA == other.IDLA &&
            IDLB == other.IDLB &&
            PKE2 == other.PKE2 &&
            CNAM == other.CNAM &&
            PKFD == other.PKFD &&
            PKPT == other.PKPT &&
            PKW3 == other.PKW3 &&
            PTD2 == other.PTD2 &&
            PKDD == other.PKDD &&
            BeginTNAM == other.BeginTNAM &&
            BeginINAM == other.BeginINAM &&
            EndTNAM == other.EndTNAM &&
            EndINAM == other.EndINAM &&
            CTDA == other.CTDA &&
            ChangeTNAM == other.ChangeTNAM &&
            ChangeINAM == other.ChangeINAM &&
            BeginSCHR == other.BeginSCHR &&
            BeginSCDA == other.BeginSCDA &&
            BeginSCTX.equalsi(other.BeginSCTX) &&
            BeginVARS == other.BeginVARS &&
            BeginSCR_ == other.BeginSCR_ &&
            EndSCHR == other.EndSCHR &&
            EndSCDA == other.EndSCDA &&
            EndSCTX.equalsi(other.EndSCTX) &&
            EndVARS == other.EndVARS &&
            EndSCR_ == other.EndSCR_ &&
            ChangeSCHR == other.ChangeSCHR &&
            ChangeSCDA == other.ChangeSCDA &&
            ChangeSCTX.equalsi(other.ChangeSCTX) &&
            ChangeVARS == other.ChangeVARS &&
            ChangeSCR_ == other.ChangeSCR_);
    }

bool PACKRecord::operator !=(const PACKRecord &other) const
    {
    return !(*this == other);
    }

bool PACKRecord::equals(Record *other)
    {
    return *this == *(PACKRecord *)other;
    }
}