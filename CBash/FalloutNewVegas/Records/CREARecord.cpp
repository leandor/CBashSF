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
#include "CREARecord.h"

namespace FNV
{

bool CREARecord::CREASoundType::IsLeftFoot()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftFoot);
    }

void CREARecord::CREASoundType::IsLeftFoot(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftFoot : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsRightFoot()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightFoot);
    }

void CREARecord::CREASoundType::IsRightFoot(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightFoot : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsLeftBackFoot()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLeftBackFoot);
    }

void CREARecord::CREASoundType::IsLeftBackFoot(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLeftBackFoot : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsRightBackFoot()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRightBackFoot);
    }

void CREARecord::CREASoundType::IsRightBackFoot(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRightBackFoot : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsIdle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIdle);
    }

void CREARecord::CREASoundType::IsIdle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eIdle : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAware()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAware);
    }

void CREARecord::CREASoundType::IsAware(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAware : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAttack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack);
    }

void CREARecord::CREASoundType::IsAttack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsHit()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHit);
    }

void CREARecord::CREASoundType::IsHit(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHit : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsDeath()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDeath);
    }

void CREARecord::CREASoundType::IsDeath(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDeath : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWeapon);
    }

void CREARecord::CREASoundType::IsWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWeapon : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsMovementLoop()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMovementLoop);
    }

void CREARecord::CREASoundType::IsMovementLoop(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMovementLoop : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsConsciousLoop()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eConsciousLoop);
    }

void CREARecord::CREASoundType::IsConsciousLoop(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eConsciousLoop : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAuxiliary1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuxiliary1);
    }

void CREARecord::CREASoundType::IsAuxiliary1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAuxiliary1 : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAuxiliary2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuxiliary2);
    }

void CREARecord::CREASoundType::IsAuxiliary2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAuxiliary2 : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAuxiliary3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuxiliary3);
    }

void CREARecord::CREASoundType::IsAuxiliary3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAuxiliary3 : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAuxiliary4()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuxiliary4);
    }

void CREARecord::CREASoundType::IsAuxiliary4(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAuxiliary4 : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAuxiliary5()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuxiliary5);
    }

void CREARecord::CREASoundType::IsAuxiliary5(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAuxiliary5 : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAuxiliary6()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuxiliary6);
    }

void CREARecord::CREASoundType::IsAuxiliary6(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAuxiliary6 : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAuxiliary7()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuxiliary7);
    }

void CREARecord::CREASoundType::IsAuxiliary7(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAuxiliary7 : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsAuxiliary8()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuxiliary8);
    }

void CREARecord::CREASoundType::IsAuxiliary8(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAuxiliary8 : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsJump()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eJump);
    }

void CREARecord::CREASoundType::IsJump(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eJump : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsPlayRandomLoop()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlayRandomLoop);
    }

void CREARecord::CREASoundType::IsPlayRandomLoop(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlayRandomLoop : eDummyDefault;
    }

bool CREARecord::CREASoundType::IsType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::CREASoundType::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

CREARecord::CREARecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CREARecord::CREARecord(CREARecord *srcRecord):
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
        MODL->Textures.MODS.resize(srcRecord->MODL->Textures.MODS.size());
        for(UINT32 x = 0; x < srcRecord->MODL->Textures.MODS.size(); x++)
            {
            MODL->Textures.MODS[x] = new FNVMODS;
            *MODL->Textures.MODS[x] = *srcRecord->MODL->Textures.MODS[x];
            }
        MODL->MODD = srcRecord->MODL->MODD;
        }

    SPLO = srcRecord->SPLO;
    EITM = srcRecord->EITM;
    EAMT = srcRecord->EAMT;
    NIFZ = srcRecord->NIFZ;
    NIFT = srcRecord->NIFT;
    ACBS = srcRecord->ACBS;
    SNAM = srcRecord->SNAM;
    INAM = srcRecord->INAM;
    VTCK = srcRecord->VTCK;
    TPLT = srcRecord->TPLT;
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
    KFFZ = srcRecord->KFFZ;
    DATA = srcRecord->DATA;
    RNAM = srcRecord->RNAM;
    ZNAM = srcRecord->ZNAM;
    PNAM = srcRecord->PNAM;
    TNAM = srcRecord->TNAM;
    BNAM = srcRecord->BNAM;
    WNAM = srcRecord->WNAM;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    CSCR = srcRecord->CSCR;
    if(srcRecord->CSDT.IsLoaded())
        {
        CSDT.Load();
        CSDT->CSDT = srcRecord->CSDT->CSDT;
        CSDT->CSDI = srcRecord->CSDT->CSDI;
        CSDT->CSDC = srcRecord->CSDT->CSDC;
        }
    CNAM = srcRecord->CNAM;
    LNAM = srcRecord->LNAM;
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

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SPLO.IsLoaded())
        op.Accept(SPLO->value);
    if(EITM.IsLoaded())
        op.Accept(EITM->value);
    //if(SNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(SNAM->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);
    if(VTCK.IsLoaded())
        op.Accept(VTCK->value);
    if(TPLT.IsLoaded())
        op.Accept(TPLT->value);
    if(DEST.IsLoaded() && DEST->DSTD.IsLoaded())
        op.Accept(DEST->DSTD->value);
    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    //if(CNTO.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CNTO->value);
    if(PKID.IsLoaded())
        op.Accept(PKID->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    if(PNAM.IsLoaded())
        op.Accept(PNAM->value);
    if(CSCR.IsLoaded())
        op.Accept(CSCR->value);
    if(CSDT.IsLoaded() && CSDT->CSDI.IsLoaded())
        op.Accept(CSDT->CSDI->value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM->value);
    if(LNAM.IsLoaded())
        op.Accept(LNAM->value);

    return op.Stop();
    }

bool CREARecord::IsBiped()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBiped) != 0;
    }

void CREARecord::IsBiped(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsBiped) : (Dummy->flags & ~fIsBiped);
    }

bool CREARecord::IsEssential()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEssential) != 0;
    }

void CREARecord::IsEssential(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsEssential) : (Dummy->flags & ~fIsEssential);
    }

bool CREARecord::IsWeaponAndShield()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsWeaponAndShield) != 0;
    }

void CREARecord::IsWeaponAndShield(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsWeaponAndShield) : (Dummy->flags & ~fIsWeaponAndShield);
    }

bool CREARecord::IsRespawn()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRespawn) != 0;
    }

void CREARecord::IsRespawn(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRespawn) : (Dummy->flags & ~fIsRespawn);
    }

bool CREARecord::IsSwims()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSwims) != 0;
    }

void CREARecord::IsSwims(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsSwims) : (Dummy->flags & ~fIsSwims);
    }

bool CREARecord::IsFlies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFlies) != 0;
    }

void CREARecord::IsFlies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsFlies) : (Dummy->flags & ~fIsFlies);
    }

bool CREARecord::IsWalks()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsWalks) != 0;
    }

void CREARecord::IsWalks(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsWalks) : (Dummy->flags & ~fIsWalks);
    }

bool CREARecord::IsPCLevelOffset()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPCLevelOffset) != 0;
    }

void CREARecord::IsPCLevelOffset(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPCLevelOffset) : (Dummy->flags & ~fIsPCLevelOffset);
    }

bool CREARecord::IsUnknown1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown1) != 0;
    }

void CREARecord::IsUnknown1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUnknown1) : (Dummy->flags & ~fIsUnknown1);
    }

bool CREARecord::IsNoLowLevel()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoLowLevel) != 0;
    }

void CREARecord::IsNoLowLevel(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoLowLevel) : (Dummy->flags & ~fIsNoLowLevel);
    }

bool CREARecord::IsNoBloodSpray()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoBloodSpray) != 0;
    }

void CREARecord::IsNoBloodSpray(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoBloodSpray) : (Dummy->flags & ~fIsNoBloodSpray);
    }

bool CREARecord::IsNoBloodDecal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoBloodDecal) != 0;
    }

void CREARecord::IsNoBloodDecal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoBloodDecal) : (Dummy->flags & ~fIsNoBloodDecal);
    }

bool CREARecord::IsNoHead()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoHead) != 0;
    }

void CREARecord::IsNoHead(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoHead) : (Dummy->flags & ~fIsNoHead);
    }

bool CREARecord::IsNoRightArm()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoRightArm) != 0;
    }

void CREARecord::IsNoRightArm(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoRightArm) : (Dummy->flags & ~fIsNoRightArm);
    }

bool CREARecord::IsNoLeftArm()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoLeftArm) != 0;
    }

void CREARecord::IsNoLeftArm(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoLeftArm) : (Dummy->flags & ~fIsNoLeftArm);
    }

bool CREARecord::IsNoCombatInWater()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoCombatInWater) != 0;
    }

void CREARecord::IsNoCombatInWater(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoCombatInWater) : (Dummy->flags & ~fIsNoCombatInWater);
    }

bool CREARecord::IsNoShadow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoShadow) != 0;
    }

void CREARecord::IsNoShadow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoShadow) : (Dummy->flags & ~fIsNoShadow);
    }

bool CREARecord::IsNoVATSMelee()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoVATSMelee) != 0;
    }

void CREARecord::IsNoVATSMelee(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoVATSMelee) : (Dummy->flags & ~fIsNoVATSMelee);
    }

bool CREARecord::IsAllowPCDialogue()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAllowPCDialogue) != 0;
    }

void CREARecord::IsAllowPCDialogue(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAllowPCDialogue) : (Dummy->flags & ~fIsAllowPCDialogue);
    }

bool CREARecord::IsCantOpenDoors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsCantOpenDoors) != 0;
    }

void CREARecord::IsCantOpenDoors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsCantOpenDoors) : (Dummy->flags & ~fIsCantOpenDoors);
    }

bool CREARecord::IsImmobile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsImmobile) != 0;
    }

void CREARecord::IsImmobile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsImmobile) : (Dummy->flags & ~fIsImmobile);
    }

bool CREARecord::IsTiltFrontBack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTiltFrontBack) != 0;
    }

void CREARecord::IsTiltFrontBack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsTiltFrontBack) : (Dummy->flags & ~fIsTiltFrontBack);
    }

bool CREARecord::IsTiltLeftRight()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTiltLeftRight) != 0;
    }

void CREARecord::IsTiltLeftRight(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsTiltLeftRight) : (Dummy->flags & ~fIsTiltLeftRight);
    }

bool CREARecord::IsNoKnockdowns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoKnockdowns) != 0;
    }

void CREARecord::IsNoKnockdowns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoKnockdowns) : (Dummy->flags & ~fIsNoKnockdowns);
    }

bool CREARecord::IsNotPushable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNotPushable) != 0;
    }

void CREARecord::IsNotPushable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNotPushable) : (Dummy->flags & ~fIsNotPushable);
    }

bool CREARecord::IsAllowPickpocket()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAllowPickpocket) != 0;
    }

void CREARecord::IsAllowPickpocket(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAllowPickpocket) : (Dummy->flags & ~fIsAllowPickpocket);
    }

bool CREARecord::IsGhost()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsGhost) != 0;
    }

void CREARecord::IsGhost(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsGhost) : (Dummy->flags & ~fIsGhost);
    }

bool CREARecord::IsNoHeadTracking()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoHeadTracking) != 0;
    }

void CREARecord::IsNoHeadTracking(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoHeadTracking) : (Dummy->flags & ~fIsNoHeadTracking);
    }

bool CREARecord::IsInvulnerable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsInvulnerable) != 0;
    }

void CREARecord::IsInvulnerable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsInvulnerable) : (Dummy->flags & ~fIsInvulnerable);
    }

bool CREARecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CREARecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsUseTraits()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseTraits) != 0;
    }

void CREARecord::IsUseTraits(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseTraits) : (Dummy->flags & ~fIsUseTraits);
    }

bool CREARecord::IsUseStats()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseStats) != 0;
    }

void CREARecord::IsUseStats(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseStats) : (Dummy->flags & ~fIsUseStats);
    }

bool CREARecord::IsUseFactions()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseFactions) != 0;
    }

void CREARecord::IsUseFactions(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseFactions) : (Dummy->flags & ~fIsUseFactions);
    }

bool CREARecord::IsUseAEList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAEList) != 0;
    }

void CREARecord::IsUseAEList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseAEList) : (Dummy->flags & ~fIsUseAEList);
    }

bool CREARecord::IsUseAIData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAIData) != 0;
    }

void CREARecord::IsUseAIData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseAIData) : (Dummy->flags & ~fIsUseAIData);
    }

bool CREARecord::IsUseAIPackages()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAIPackages) != 0;
    }

void CREARecord::IsUseAIPackages(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseAIPackages) : (Dummy->flags & ~fIsUseAIPackages);
    }

bool CREARecord::IsUseModelAnim()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseModelAnim) != 0;
    }

void CREARecord::IsUseModelAnim(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseModelAnim) : (Dummy->flags & ~fIsUseModelAnim);
    }

bool CREARecord::IsUseBaseData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseBaseData) != 0;
    }

void CREARecord::IsUseBaseData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseBaseData) : (Dummy->flags & ~fIsUseBaseData);
    }

bool CREARecord::IsUseInventory()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseInventory) != 0;
    }

void CREARecord::IsUseInventory(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseInventory) : (Dummy->flags & ~fIsUseInventory);
    }

bool CREARecord::IsUseScript()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseScript) != 0;
    }

void CREARecord::IsUseScript(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseScript) : (Dummy->flags & ~fIsUseScript);
    }

bool CREARecord::IsTemplateFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CREARecord::SetTemplateFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsAggroRadiusBehavior()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAggroRadiusBehavior) != 0;
    }

void CREARecord::IsAggroRadiusBehavior(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAggroRadiusBehavior) : (Dummy->flags & ~fIsAggroRadiusBehavior);
    }

bool CREARecord::IsAggroFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CREARecord::SetAggroFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsAnimal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAnimal);
    }

void CREARecord::IsAnimal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAnimal : eDummyDefault;
    }

bool CREARecord::IsMutatedAnimal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMutatedAnimal);
    }

void CREARecord::IsMutatedAnimal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMutatedAnimal : eDummyDefault;
    }

bool CREARecord::IsMutatedInsect()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMutatedInsect);
    }

void CREARecord::IsMutatedInsect(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMutatedInsect : eDummyDefault;
    }

bool CREARecord::IsAbomination()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAbomination);
    }

void CREARecord::IsAbomination(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAbomination : eDummyDefault;
    }

bool CREARecord::IsSuperMutant()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSuperMutant);
    }

void CREARecord::IsSuperMutant(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSuperMutant : eDummyDefault;
    }

bool CREARecord::IsFeralGhoul()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFeralGhoul);
    }

void CREARecord::IsFeralGhoul(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFeralGhoul : eDummyDefault;
    }

bool CREARecord::IsRobot()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRobot);
    }

void CREARecord::IsRobot(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRobot : eDummyDefault;
    }

bool CREARecord::IsGiant()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGiant);
    }

void CREARecord::IsGiant(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGiant : eDummyDefault;
    }

bool CREARecord::IsType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::SetType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsAttackLeft()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLeft);
    }

void CREARecord::IsAttackLeft(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLeft : eDummyDefault;
    }

bool CREARecord::IsAttackLeftUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLeftUp);
    }

void CREARecord::IsAttackLeftUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLeftUp : eDummyDefault;
    }

bool CREARecord::IsAttackLeftDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLeftDown);
    }

void CREARecord::IsAttackLeftDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLeftDown : eDummyDefault;
    }

bool CREARecord::IsAttackLeftIS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLeftIS);
    }

void CREARecord::IsAttackLeftIS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLeftIS : eDummyDefault;
    }

bool CREARecord::IsAttackLeftISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLeftISUp);
    }

void CREARecord::IsAttackLeftISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLeftISUp : eDummyDefault;
    }

bool CREARecord::IsAttackLeftISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLeftISDown);
    }

void CREARecord::IsAttackLeftISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLeftISDown : eDummyDefault;
    }

bool CREARecord::IsAttackRight()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackRight);
    }

void CREARecord::IsAttackRight(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackRight : eDummyDefault;
    }

bool CREARecord::IsAttackRightUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackRightUp);
    }

void CREARecord::IsAttackRightUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackRightUp : eDummyDefault;
    }

bool CREARecord::IsAttackRightDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackRightDown);
    }

void CREARecord::IsAttackRightDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackRightDown : eDummyDefault;
    }

bool CREARecord::IsAttackRightIS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackRightIS);
    }

void CREARecord::IsAttackRightIS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackRightIS : eDummyDefault;
    }

bool CREARecord::IsAttackRightISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackRightISUp);
    }

void CREARecord::IsAttackRightISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackRightISUp : eDummyDefault;
    }

bool CREARecord::IsAttackRightISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackRightISDown);
    }

void CREARecord::IsAttackRightISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackRightISDown : eDummyDefault;
    }

bool CREARecord::IsAttack3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack3);
    }

void CREARecord::IsAttack3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack3 : eDummyDefault;
    }

bool CREARecord::IsAttack3Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack3Up);
    }

void CREARecord::IsAttack3Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack3Up : eDummyDefault;
    }

bool CREARecord::IsAttack3Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack3Down);
    }

void CREARecord::IsAttack3Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack3Down : eDummyDefault;
    }

bool CREARecord::IsAttack3IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack3IS);
    }

void CREARecord::IsAttack3IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack3IS : eDummyDefault;
    }

bool CREARecord::IsAttack3ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack3ISUp);
    }

void CREARecord::IsAttack3ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack3ISUp : eDummyDefault;
    }

bool CREARecord::IsAttack3ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack3ISDown);
    }

void CREARecord::IsAttack3ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack3ISDown : eDummyDefault;
    }

bool CREARecord::IsAttack4()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack4);
    }

void CREARecord::IsAttack4(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack4 : eDummyDefault;
    }

bool CREARecord::IsAttack4Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack4Up);
    }

void CREARecord::IsAttack4Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack4Up : eDummyDefault;
    }

bool CREARecord::IsAttack4Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack4Down);
    }

void CREARecord::IsAttack4Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack4Down : eDummyDefault;
    }

bool CREARecord::IsAttack4IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack4IS);
    }

void CREARecord::IsAttack4IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack4IS : eDummyDefault;
    }

bool CREARecord::IsAttack4ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack4ISUp);
    }

void CREARecord::IsAttack4ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack4ISUp : eDummyDefault;
    }

bool CREARecord::IsAttack4ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack4ISDown);
    }

void CREARecord::IsAttack4ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack4ISDown : eDummyDefault;
    }

bool CREARecord::IsAttack5()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack5);
    }

void CREARecord::IsAttack5(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack5 : eDummyDefault;
    }

bool CREARecord::IsAttack5Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack5Up);
    }

void CREARecord::IsAttack5Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack5Up : eDummyDefault;
    }

bool CREARecord::IsAttack5Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack5Down);
    }

void CREARecord::IsAttack5Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack5Down : eDummyDefault;
    }

bool CREARecord::IsAttack5IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack5IS);
    }

void CREARecord::IsAttack5IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack5IS : eDummyDefault;
    }

bool CREARecord::IsAttack5ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack5ISUp);
    }

void CREARecord::IsAttack5ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack5ISUp : eDummyDefault;
    }

bool CREARecord::IsAttack5ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack5ISDown);
    }

void CREARecord::IsAttack5ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack5ISDown : eDummyDefault;
    }

bool CREARecord::IsAttack6()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack6);
    }

void CREARecord::IsAttack6(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack6 : eDummyDefault;
    }

bool CREARecord::IsAttack6Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack6Up);
    }

void CREARecord::IsAttack6Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack6Up : eDummyDefault;
    }

bool CREARecord::IsAttack6Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack6Down);
    }

void CREARecord::IsAttack6Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack6Down : eDummyDefault;
    }

bool CREARecord::IsAttack6IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack6IS);
    }

void CREARecord::IsAttack6IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack6IS : eDummyDefault;
    }

bool CREARecord::IsAttack6ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack6ISUp);
    }

void CREARecord::IsAttack6ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack6ISUp : eDummyDefault;
    }

bool CREARecord::IsAttack6ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack6ISDown);
    }

void CREARecord::IsAttack6ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack6ISDown : eDummyDefault;
    }

bool CREARecord::IsAttack7()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack7);
    }

void CREARecord::IsAttack7(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack7 : eDummyDefault;
    }

bool CREARecord::IsAttack7Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack7Up);
    }

void CREARecord::IsAttack7Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack7Up : eDummyDefault;
    }

bool CREARecord::IsAttack7Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack7Down);
    }

void CREARecord::IsAttack7Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack7Down : eDummyDefault;
    }

bool CREARecord::IsAttack7IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack7IS);
    }

void CREARecord::IsAttack7IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack7IS : eDummyDefault;
    }

bool CREARecord::IsAttack7ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack7ISUp);
    }

void CREARecord::IsAttack7ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack7ISUp : eDummyDefault;
    }

bool CREARecord::IsAttack7ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack7ISDown);
    }

void CREARecord::IsAttack7ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack7ISDown : eDummyDefault;
    }

bool CREARecord::IsAttack8()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack8);
    }

void CREARecord::IsAttack8(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack8 : eDummyDefault;
    }

bool CREARecord::IsAttack8Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack8Up);
    }

void CREARecord::IsAttack8Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack8Up : eDummyDefault;
    }

bool CREARecord::IsAttack8Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack8Down);
    }

void CREARecord::IsAttack8Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack8Down : eDummyDefault;
    }

bool CREARecord::IsAttack8IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack8IS);
    }

void CREARecord::IsAttack8IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack8IS : eDummyDefault;
    }

bool CREARecord::IsAttack8ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack8ISUp);
    }

void CREARecord::IsAttack8ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack8ISUp : eDummyDefault;
    }

bool CREARecord::IsAttack8ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttack8ISDown);
    }

void CREARecord::IsAttack8ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttack8ISDown : eDummyDefault;
    }

bool CREARecord::IsAttackLoop()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLoop);
    }

void CREARecord::IsAttackLoop(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLoop : eDummyDefault;
    }

bool CREARecord::IsAttackLoopUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLoopUp);
    }

void CREARecord::IsAttackLoopUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLoopUp : eDummyDefault;
    }

bool CREARecord::IsAttackLoopDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLoopDown);
    }

void CREARecord::IsAttackLoopDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLoopDown : eDummyDefault;
    }

bool CREARecord::IsAttackLoopIS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLoopIS);
    }

void CREARecord::IsAttackLoopIS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLoopIS : eDummyDefault;
    }

bool CREARecord::IsAttackLoopISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLoopISUp);
    }

void CREARecord::IsAttackLoopISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLoopISUp : eDummyDefault;
    }

bool CREARecord::IsAttackLoopISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLoopISDown);
    }

void CREARecord::IsAttackLoopISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLoopISDown : eDummyDefault;
    }

bool CREARecord::IsAttackSpin()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin);
    }

void CREARecord::IsAttackSpin(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin : eDummyDefault;
    }

bool CREARecord::IsAttackSpinUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpinUp);
    }

void CREARecord::IsAttackSpinUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpinUp : eDummyDefault;
    }

bool CREARecord::IsAttackSpinDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpinDown);
    }

void CREARecord::IsAttackSpinDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpinDown : eDummyDefault;
    }

bool CREARecord::IsAttackSpinIS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpinIS);
    }

void CREARecord::IsAttackSpinIS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpinIS : eDummyDefault;
    }

bool CREARecord::IsAttackSpinISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpinISUp);
    }

void CREARecord::IsAttackSpinISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpinISUp : eDummyDefault;
    }

bool CREARecord::IsAttackSpinISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpinISDown);
    }

void CREARecord::IsAttackSpinISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpinISDown : eDummyDefault;
    }

bool CREARecord::IsAttackSpin2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin2);
    }

void CREARecord::IsAttackSpin2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin2 : eDummyDefault;
    }

bool CREARecord::IsAttackSpin2Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin2Up);
    }

void CREARecord::IsAttackSpin2Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin2Up : eDummyDefault;
    }

bool CREARecord::IsAttackSpin2Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin2Down);
    }

void CREARecord::IsAttackSpin2Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin2Down : eDummyDefault;
    }

bool CREARecord::IsAttackSpin2IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin2IS);
    }

void CREARecord::IsAttackSpin2IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin2IS : eDummyDefault;
    }

bool CREARecord::IsAttackSpin2ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin2ISUp);
    }

void CREARecord::IsAttackSpin2ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin2ISUp : eDummyDefault;
    }

bool CREARecord::IsAttackSpin2ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackSpin2ISDown);
    }

void CREARecord::IsAttackSpin2ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackSpin2ISDown : eDummyDefault;
    }

bool CREARecord::IsAttackPower()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackPower);
    }

void CREARecord::IsAttackPower(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackPower : eDummyDefault;
    }

bool CREARecord::IsAttackForwardPower()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackForwardPower);
    }

void CREARecord::IsAttackForwardPower(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackForwardPower : eDummyDefault;
    }

bool CREARecord::IsAttackBackPower()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackBackPower);
    }

void CREARecord::IsAttackBackPower(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackBackPower : eDummyDefault;
    }

bool CREARecord::IsAttackLeftPower()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackLeftPower);
    }

void CREARecord::IsAttackLeftPower(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackLeftPower : eDummyDefault;
    }

bool CREARecord::IsAttackRightPower()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackRightPower);
    }

void CREARecord::IsAttackRightPower(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackRightPower : eDummyDefault;
    }

bool CREARecord::IsPlaceMine()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine);
    }

void CREARecord::IsPlaceMine(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine : eDummyDefault;
    }

bool CREARecord::IsPlaceMineUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMineUp);
    }

void CREARecord::IsPlaceMineUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMineUp : eDummyDefault;
    }

bool CREARecord::IsPlaceMineDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMineDown);
    }

void CREARecord::IsPlaceMineDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMineDown : eDummyDefault;
    }

bool CREARecord::IsPlaceMineIS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMineIS);
    }

void CREARecord::IsPlaceMineIS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMineIS : eDummyDefault;
    }

bool CREARecord::IsPlaceMineISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMineISUp);
    }

void CREARecord::IsPlaceMineISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMineISUp : eDummyDefault;
    }

bool CREARecord::IsPlaceMineISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMineISDown);
    }

void CREARecord::IsPlaceMineISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMineISDown : eDummyDefault;
    }

bool CREARecord::IsPlaceMine2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine2);
    }

void CREARecord::IsPlaceMine2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine2 : eDummyDefault;
    }

bool CREARecord::IsPlaceMine2Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine2Up);
    }

void CREARecord::IsPlaceMine2Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine2Up : eDummyDefault;
    }

bool CREARecord::IsPlaceMine2Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine2Down);
    }

void CREARecord::IsPlaceMine2Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine2Down : eDummyDefault;
    }

bool CREARecord::IsPlaceMine2IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine2IS);
    }

void CREARecord::IsPlaceMine2IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine2IS : eDummyDefault;
    }

bool CREARecord::IsPlaceMine2ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine2ISUp);
    }

void CREARecord::IsPlaceMine2ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine2ISUp : eDummyDefault;
    }

bool CREARecord::IsPlaceMine2ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlaceMine2ISDown);
    }

void CREARecord::IsPlaceMine2ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlaceMine2ISDown : eDummyDefault;
    }

bool CREARecord::IsAttackThrow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow);
    }

void CREARecord::IsAttackThrow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow : eDummyDefault;
    }

bool CREARecord::IsAttackThrowUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrowUp);
    }

void CREARecord::IsAttackThrowUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrowUp : eDummyDefault;
    }

bool CREARecord::IsAttackThrowDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrowDown);
    }

void CREARecord::IsAttackThrowDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrowDown : eDummyDefault;
    }

bool CREARecord::IsAttackThrowIS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrowIS);
    }

void CREARecord::IsAttackThrowIS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrowIS : eDummyDefault;
    }

bool CREARecord::IsAttackThrowISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrowISUp);
    }

void CREARecord::IsAttackThrowISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrowISUp : eDummyDefault;
    }

bool CREARecord::IsAttackThrowISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrowISDown);
    }

void CREARecord::IsAttackThrowISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrowISDown : eDummyDefault;
    }

bool CREARecord::IsAttackThrow2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow2);
    }

void CREARecord::IsAttackThrow2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow2 : eDummyDefault;
    }

bool CREARecord::IsAttackThrow2Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow2Up);
    }

void CREARecord::IsAttackThrow2Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow2Up : eDummyDefault;
    }

bool CREARecord::IsAttackThrow2Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow2Down);
    }

void CREARecord::IsAttackThrow2Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow2Down : eDummyDefault;
    }

bool CREARecord::IsAttackThrow2IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow2IS);
    }

void CREARecord::IsAttackThrow2IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow2IS : eDummyDefault;
    }

bool CREARecord::IsAttackThrow2ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow2ISUp);
    }

void CREARecord::IsAttackThrow2ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow2ISUp : eDummyDefault;
    }

bool CREARecord::IsAttackThrow2ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow2ISDown);
    }

void CREARecord::IsAttackThrow2ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow2ISDown : eDummyDefault;
    }

bool CREARecord::IsAttackThrow3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow3);
    }

void CREARecord::IsAttackThrow3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow3 : eDummyDefault;
    }

bool CREARecord::IsAttackThrow3Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow3Up);
    }

void CREARecord::IsAttackThrow3Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow3Up : eDummyDefault;
    }

bool CREARecord::IsAttackThrow3Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow3Down);
    }

void CREARecord::IsAttackThrow3Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow3Down : eDummyDefault;
    }

bool CREARecord::IsAttackThrow3IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow3IS);
    }

void CREARecord::IsAttackThrow3IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow3IS : eDummyDefault;
    }

bool CREARecord::IsAttackThrow3ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow3ISUp);
    }

void CREARecord::IsAttackThrow3ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow3ISUp : eDummyDefault;
    }

bool CREARecord::IsAttackThrow3ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow3ISDown);
    }

void CREARecord::IsAttackThrow3ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow3ISDown : eDummyDefault;
    }

bool CREARecord::IsAttackThrow4()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow4);
    }

void CREARecord::IsAttackThrow4(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow4 : eDummyDefault;
    }

bool CREARecord::IsAttackThrow4Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow4Up);
    }

void CREARecord::IsAttackThrow4Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow4Up : eDummyDefault;
    }

bool CREARecord::IsAttackThrow4Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow4Down);
    }

void CREARecord::IsAttackThrow4Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow4Down : eDummyDefault;
    }

bool CREARecord::IsAttackThrow4IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow4IS);
    }

void CREARecord::IsAttackThrow4IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow4IS : eDummyDefault;
    }

bool CREARecord::IsAttackThrow4ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow4ISUp);
    }

void CREARecord::IsAttackThrow4ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow4ISUp : eDummyDefault;
    }

bool CREARecord::IsAttackThrow4ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow4ISDown);
    }

void CREARecord::IsAttackThrow4ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow4ISDown : eDummyDefault;
    }

bool CREARecord::IsAttackThrow5()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow5);
    }

void CREARecord::IsAttackThrow5(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow5 : eDummyDefault;
    }

bool CREARecord::IsAttackThrow5Up()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow5Up);
    }

void CREARecord::IsAttackThrow5Up(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow5Up : eDummyDefault;
    }

bool CREARecord::IsAttackThrow5Down()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow5Down);
    }

void CREARecord::IsAttackThrow5Down(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow5Down : eDummyDefault;
    }

bool CREARecord::IsAttackThrow5IS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow5IS);
    }

void CREARecord::IsAttackThrow5IS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow5IS : eDummyDefault;
    }

bool CREARecord::IsAttackThrow5ISUp()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow5ISUp);
    }

void CREARecord::IsAttackThrow5ISUp(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow5ISUp : eDummyDefault;
    }

bool CREARecord::IsAttackThrow5ISDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttackThrow5ISDown);
    }

void CREARecord::IsAttackThrow5ISDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttackThrow5ISDown : eDummyDefault;
    }

bool CREARecord::IsPipBoy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePipBoy);
    }

void CREARecord::IsPipBoy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePipBoy : eDummyDefault;
    }

bool CREARecord::IsPipBoyChild()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePipBoyChild);
    }

void CREARecord::IsPipBoyChild(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePipBoyChild : eDummyDefault;
    }

bool CREARecord::IsANY()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eANY);
    }

void CREARecord::IsANY(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eANY : eDummyDefault;
    }

bool CREARecord::IsAttackAnimType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::SetAttackAnimType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsLoud()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLoud);
    }

void CREARecord::IsLoud(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLoud : eDummyDefault;
    }

bool CREARecord::IsNormal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNormal);
    }

void CREARecord::IsNormal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNormal : eDummyDefault;
    }

bool CREARecord::IsSilent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSilent);
    }

void CREARecord::IsSilent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSilent : eDummyDefault;
    }

bool CREARecord::IsSoundLevelType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::SetSoundLevelType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsUnaggressive()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnaggressive);
    }

void CREARecord::IsUnaggressive(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUnaggressive : eDummyDefault;
    }

bool CREARecord::IsAggressive()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAggressive);
    }

void CREARecord::IsAggressive(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAggressive : eDummyDefault;
    }

bool CREARecord::IsVeryAggressive()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryAggressive);
    }

void CREARecord::IsVeryAggressive(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVeryAggressive : eDummyDefault;
    }

bool CREARecord::IsFrenzied()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFrenzied);
    }

void CREARecord::IsFrenzied(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFrenzied : eDummyDefault;
    }

bool CREARecord::IsAggressionType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::SetAggressionType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsCowardly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCowardly);
    }

void CREARecord::IsCowardly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCowardly : eDummyDefault;
    }

bool CREARecord::IsCautious()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCautious);
    }

void CREARecord::IsCautious(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCautious : eDummyDefault;
    }

bool CREARecord::IsAverage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAverage);
    }

void CREARecord::IsAverage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAverage : eDummyDefault;
    }

bool CREARecord::IsBrave()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBrave);
    }

void CREARecord::IsBrave(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBrave : eDummyDefault;
    }

bool CREARecord::IsFoolhardy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFoolhardy);
    }

void CREARecord::IsFoolhardy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFoolhardy : eDummyDefault;
    }

bool CREARecord::IsConfidenceType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::SetConfidenceType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsNeutral()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNeutral);
    }

void CREARecord::IsNeutral(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNeutral : eDummyDefault;
    }

bool CREARecord::IsAfraid()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAfraid);
    }

void CREARecord::IsAfraid(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAfraid : eDummyDefault;
    }

bool CREARecord::IsAnnoyed()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAnnoyed);
    }

void CREARecord::IsAnnoyed(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAnnoyed : eDummyDefault;
    }

bool CREARecord::IsCocky()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCocky);
    }

void CREARecord::IsCocky(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCocky : eDummyDefault;
    }

bool CREARecord::IsDrugged()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDrugged);
    }

void CREARecord::IsDrugged(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDrugged : eDummyDefault;
    }

bool CREARecord::IsPleasant()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePleasant);
    }

void CREARecord::IsPleasant(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePleasant : eDummyDefault;
    }

bool CREARecord::IsAngry()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAngry);
    }

void CREARecord::IsAngry(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAngry : eDummyDefault;
    }

bool CREARecord::IsSad()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSad);
    }

void CREARecord::IsSad(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSad : eDummyDefault;
    }

bool CREARecord::IsMoodType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::SetMoodType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsHelpsNobody()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHelpsNobody);
    }

void CREARecord::IsHelpsNobody(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHelpsNobody : eDummyDefault;
    }

bool CREARecord::IsHelpsAllies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHelpsAllies);
    }

void CREARecord::IsHelpsAllies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHelpsAllies : eDummyDefault;
    }

bool CREARecord::IsHelpsFriendsAndAllies()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHelpsFriendsAndAllies);
    }

void CREARecord::IsHelpsFriendsAndAllies(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHelpsFriendsAndAllies : eDummyDefault;
    }

bool CREARecord::IsAssistanceType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::SetAssistanceType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CREARecord::IsStone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStone);
    }

void CREARecord::IsStone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStone : eDummyDefault;
    }

bool CREARecord::IsDirt()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDirt);
    }

void CREARecord::IsDirt(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDirt : eDummyDefault;
    }

bool CREARecord::IsGrass()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGrass);
    }

void CREARecord::IsGrass(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGrass : eDummyDefault;
    }

bool CREARecord::IsGlass()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGlass);
    }

void CREARecord::IsGlass(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGlass : eDummyDefault;
    }

bool CREARecord::IsMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMetal);
    }

void CREARecord::IsMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMetal : eDummyDefault;
    }

bool CREARecord::IsWood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWood);
    }

void CREARecord::IsWood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWood : eDummyDefault;
    }

bool CREARecord::IsOrganic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganic);
    }

void CREARecord::IsOrganic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eOrganic : eDummyDefault;
    }

bool CREARecord::IsCloth()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCloth);
    }

void CREARecord::IsCloth(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCloth : eDummyDefault;
    }

bool CREARecord::IsWater()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWater);
    }

void CREARecord::IsWater(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWater : eDummyDefault;
    }

bool CREARecord::IsHollowMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHollowMetal);
    }

void CREARecord::IsHollowMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHollowMetal : eDummyDefault;
    }

bool CREARecord::IsOrganicBug()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganicBug);
    }

void CREARecord::IsOrganicBug(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eOrganicBug : eDummyDefault;
    }

bool CREARecord::IsOrganicGlow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganicGlow);
    }

void CREARecord::IsOrganicGlow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eOrganicGlow : eDummyDefault;
    }

bool CREARecord::IsImpactType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CREARecord::SetImpactType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CREARecord::GetSize(bool forceCalc)
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
            TotSize += MODL->MODB.GetSize() + 6;
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->Textures.IsLoaded())
            {
            cSize = MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODD.IsLoaded())
            TotSize += MODL->MODD.GetSize() + 6;
        }

    if(SPLO.IsLoaded())
        TotSize += SPLO.GetSize() + 6;

    if(EITM.IsLoaded())
        TotSize += EITM.GetSize() + 6;

    if(EAMT.IsLoaded())
        TotSize += EAMT.GetSize() + 6;

    if(NIFZ.IsLoaded())
        TotSize += NIFZ.GetSize() + 6;

    if(NIFT.IsLoaded())
        {
        cSize = NIFT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
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

    if(KFFZ.IsLoaded())
        TotSize += KFFZ.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(RNAM.IsLoaded())
        TotSize += RNAM.GetSize() + 6;

    if(ZNAM.IsLoaded())
        TotSize += ZNAM.GetSize() + 6;

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;

    if(BNAM.IsLoaded())
        TotSize += BNAM.GetSize() + 6;

    if(WNAM.IsLoaded())
        TotSize += WNAM.GetSize() + 6;

    if(NAM4.IsLoaded())
        TotSize += NAM4.GetSize() + 6;

    if(NAM5.IsLoaded())
        TotSize += NAM5.GetSize() + 6;

    if(CSCR.IsLoaded())
        TotSize += CSCR.GetSize() + 6;

    if(CSDT.IsLoaded())
        {
        if(CSDT->CSDT.IsLoaded())
            TotSize += CSDT->CSDT.GetSize() + 6;
        if(CSDT->CSDI.IsLoaded())
            TotSize += CSDT->CSDI.GetSize() + 6;
        if(CSDT->CSDC.IsLoaded())
            TotSize += CSDT->CSDC.GetSize() + 6;
        }

    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;

    if(LNAM.IsLoaded())
        TotSize += LNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 CREARecord::GetType()
    {
    return 'AERC';
    }

STRING CREARecord::GetStrType()
    {
    return "CREA";
    }

SINT32 CREARecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'OLPS':
                SPLO.Read(buffer, subSize, curPos);
                break;
            case 'MTIE':
                EITM.Read(buffer, subSize, curPos);
                break;
            case 'TMAE':
                EAMT.Read(buffer, subSize, curPos);
                break;
            case 'ZFIN':
                NIFZ.Read(buffer, subSize, curPos);
                break;
            case 'TFIN':
                NIFT.Read(buffer, subSize, curPos);
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
            case 'ZFFK':
                KFFZ.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANB':
                BNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANW':
                WNAM.Read(buffer, subSize, curPos);
                break;
            case '4MAN':
                NAM4.Read(buffer, subSize, curPos);
                break;
            case '5MAN':
                NAM5.Read(buffer, subSize, curPos);
                break;
            case 'RCSC':
                CSCR.Read(buffer, subSize, curPos);
                break;
            case 'TDSC':
                CSDT.Load();
                CSDT->CSDT.Read(buffer, subSize, curPos);
                break;
            case 'IDSC':
                CSDT.Load();
                CSDT->CSDI.Read(buffer, subSize, curPos);
                break;
            case 'CDSC':
                CSDT.Load();
                CSDT->CSDC.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANL':
                LNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CREA: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CREARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SPLO.Unload();
    EITM.Unload();
    EAMT.Unload();
    NIFZ.Unload();
    NIFT.Unload();
    ACBS.Unload();
    SNAM.Unload();
    INAM.Unload();
    VTCK.Unload();
    TPLT.Unload();
    DEST.Unload();
    SCRI.Unload();
    CNTO.Unload();
    AIDT.Unload();
    PKID.Unload();
    KFFZ.Unload();
    DATA.Unload();
    RNAM.Unload();
    ZNAM.Unload();
    PNAM.Unload();
    TNAM.Unload();
    BNAM.Unload();
    WNAM.Unload();
    NAM4.Unload();
    NAM5.Unload();
    CSCR.Unload();
    CSDT.Unload();
    CNAM.Unload();
    LNAM.Unload();
    return 1;
    }

SINT32 CREARecord::WriteRecord(_FileHandler &SaveHandler)
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
            SaveHandler.writeSubRecord('BDOM', &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());
        if(MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MODL->Textures.GetSize());
            UINT32 cSize = MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MODL->Textures.MODS.size(); ++p)
                {
                if(MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MODL->Textures.MODS[p]->name, cSize);
                    }                

                SaveHandler.write(&MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MODL->MODD.value, MODL->MODD.GetSize());
        }

    if(SPLO.IsLoaded())
        SaveHandler.writeSubRecord('OLPS', SPLO.value, SPLO.GetSize());

    if(EITM.IsLoaded())
        SaveHandler.writeSubRecord('MTIE', EITM.value, EITM.GetSize());

    if(EAMT.IsLoaded())
        SaveHandler.writeSubRecord('TMAE', EAMT.value, EAMT.GetSize());

    if(NIFZ.IsLoaded())
        SaveHandler.writeSubRecord('ZFIN', NIFZ.value, NIFZ.GetSize());

    if(NIFT.IsLoaded())
        SaveHandler.writeSubRecord('TFIN', NIFT.value, NIFT.GetSize());

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

    if(KFFZ.IsLoaded())
        SaveHandler.writeSubRecord('ZFFK', KFFZ.value, KFFZ.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

    if(ZNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANZ', ZNAM.value, ZNAM.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', PNAM.value, PNAM.GetSize());

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANT', TNAM.value, TNAM.GetSize());

    if(BNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANB', BNAM.value, BNAM.GetSize());

    if(WNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANW', WNAM.value, WNAM.GetSize());

    if(NAM4.IsLoaded())
        SaveHandler.writeSubRecord('4MAN', NAM4.value, NAM4.GetSize());

    if(NAM5.IsLoaded())
        SaveHandler.writeSubRecord('5MAN', NAM5.value, NAM5.GetSize());

    if(CSCR.IsLoaded())
        SaveHandler.writeSubRecord('RCSC', CSCR.value, CSCR.GetSize());

    if(CSDT.IsLoaded())
        {
        if(CSDT->CSDT.IsLoaded())
            SaveHandler.writeSubRecord('TDSC', CSDT->CSDT.value, CSDT->CSDT.GetSize());

        if(CSDT->CSDI.IsLoaded())
            SaveHandler.writeSubRecord('IDSC', CSDT->CSDI.value, CSDT->CSDI.GetSize());

        if(CSDT->CSDC.IsLoaded())
            SaveHandler.writeSubRecord('CDSC', CSDT->CSDC.value, CSDT->CSDC.GetSize());

        }

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());

    if(LNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANL', LNAM.value, LNAM.GetSize());

    return -1;
    }

bool CREARecord::operator ==(const CREARecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            SPLO == other.SPLO &&
            EITM == other.EITM &&
            EAMT == other.EAMT &&
            NIFZ == other.NIFZ &&
            NIFT == other.NIFT &&
            ACBS == other.ACBS &&
            SNAM == other.SNAM &&
            INAM == other.INAM &&
            VTCK == other.VTCK &&
            TPLT == other.TPLT &&
            DEST == other.DEST &&
            SCRI == other.SCRI &&
            CNTO == other.CNTO &&
            AIDT == other.AIDT &&
            PKID == other.PKID &&
            KFFZ == other.KFFZ &&
            DATA == other.DATA &&
            RNAM == other.RNAM &&
            ZNAM == other.ZNAM &&
            PNAM == other.PNAM &&
            TNAM == other.TNAM &&
            BNAM == other.BNAM &&
            WNAM == other.WNAM &&
            NAM4 == other.NAM4 &&
            NAM5 == other.NAM5 &&
            CSCR == other.CSCR &&
            CSDT == other.CSDT &&
            CNAM == other.CNAM &&
            LNAM == other.LNAM);
    }

bool CREARecord::operator !=(const CREARecord &other) const
    {
    return !(*this == other);
    }
}