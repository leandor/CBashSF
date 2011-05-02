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
#include "REFRRecord.h"

namespace FNV
{
REFRRecord::REFRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

REFRRecord::REFRRecord(REFRRecord *srcRecord):
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
    RCLR = srcRecord->RCLR;
    NAME = srcRecord->NAME;
    XEZN = srcRecord->XEZN;
    XRGD = srcRecord->XRGD;
    XRGB = srcRecord->XRGB;
    XPRM = srcRecord->XPRM;
    XTRI = srcRecord->XTRI;
    XMBP = srcRecord->XMBP;
    XMBO = srcRecord->XMBO;
    XTEL = srcRecord->XTEL;
    if(srcRecord->XMRK.IsLoaded())
        {
        XMRK.Load();
        XMRK->XMRK = srcRecord->XMRK->XMRK;
        XMRK->FNAM = srcRecord->XMRK->FNAM;
        }
    FULL = srcRecord->FULL;
    TNAM = srcRecord->TNAM;
    WMI1 = srcRecord->WMI1;
    if(srcRecord->MMRK.IsLoaded())
        {
        MMRK.Load();
        MMRK->MMRK = srcRecord->MMRK->MMRK;
        MMRK->FULL = srcRecord->MMRK->FULL;
        MMRK->CNAM = srcRecord->MMRK->CNAM;
        MMRK->BNAM = srcRecord->MMRK->BNAM;
        MMRK->MNAM = srcRecord->MMRK->MNAM;
        MMRK->NNAM = srcRecord->MMRK->NNAM;
        }
    XSRF = srcRecord->XSRF;
    XSRD = srcRecord->XSRD;
    XTRG = srcRecord->XTRG;
    XLCM = srcRecord->XLCM;
    if(srcRecord->XPRD.IsLoaded())
        {
        XPRD.Load();
        XPRD->XPRD = srcRecord->XPRD->XPRD;
        XPRD->XPPA = srcRecord->XPRD->XPPA;
        XPRD->INAM = srcRecord->XPRD->INAM;
        if(srcRecord->XPRD->SCHR.IsLoaded())
            {
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR = srcRecord->XPRD->SCHR->SCHR;
            XPRD->SCHR->SCDA = srcRecord->XPRD->SCHR->SCDA;
            XPRD->SCHR->SCTX = srcRecord->XPRD->SCHR->SCTX;
            XPRD->SCHR->SLSD = srcRecord->XPRD->SCHR->SLSD;
            XPRD->SCHR->SCVR = srcRecord->XPRD->SCHR->SCVR;
            XPRD->SCHR->SCRO = srcRecord->XPRD->SCHR->SCRO;
            XPRD->SCHR->SCRV = srcRecord->XPRD->SCHR->SCRV;
            }
        XPRD->TNAM = srcRecord->XPRD->TNAM;
        }
    XRDO = srcRecord->XRDO;
    if(srcRecord->XOWN.IsLoaded())
        {
        XOWN.Load();
        XOWN->XOWN = srcRecord->XOWN->XOWN;
        XOWN->XRNK = srcRecord->XOWN->XRNK;
        }
    XLOC = srcRecord->XLOC;
    XCNT = srcRecord->XCNT;
    XRDS = srcRecord->XRDS;
    XHLP = srcRecord->XHLP;
    XRAD = srcRecord->XRAD;
    XCHG = srcRecord->XCHG;
    if(srcRecord->XAMT.IsLoaded())
        {
        XAMT.Load();
        XAMT->XAMT = srcRecord->XAMT->XAMT;
        XAMT->XAMC = srcRecord->XAMT->XAMC;
        }
    XPWR = srcRecord->XPWR;
    XLTW = srcRecord->XLTW;
    XDCR = srcRecord->XDCR;
    XLKR = srcRecord->XLKR;
    XCLP = srcRecord->XCLP;
    XAPD = srcRecord->XAPD;
    XAPR = srcRecord->XAPR;
    XATO = srcRecord->XATO;
    XESP = srcRecord->XESP;
    XEMI = srcRecord->XEMI;
    XMBR = srcRecord->XMBR;
    XACT = srcRecord->XACT;
    ONAM = srcRecord->ONAM;
    XIBS = srcRecord->XIBS;
    XNDP = srcRecord->XNDP;
    XPOD = srcRecord->XPOD;
    XPTL = srcRecord->XPTL;
    XSED = srcRecord->XSED;
    XRMR = srcRecord->XRMR;
    XLRM = srcRecord->XLRM;
    XOCP = srcRecord->XOCP;
    XORD = srcRecord->XORD;
    XLOD = srcRecord->XLOD;
    XSCL = srcRecord->XSCL;
    DATA = srcRecord->DATA;
    return;
    }

REFRRecord::~REFRRecord()
    {
    //
    }

bool REFRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(NAME.IsLoaded())
        op.Accept(NAME->value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN->value);
    //if(XTEL.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XTEL->value);
    if(WMI1.IsLoaded())
        op.Accept(WMI1->value);
    if(MMRK.IsLoaded() && MMRK->CNAM.IsLoaded())
        op.Accept(MMRK->CNAM->value);
    if(XTRG.IsLoaded())
        op.Accept(XTRG->value);
    if(XPRD.IsLoaded() && XPRD->INAM.IsLoaded())
        op.Accept(XPRD->INAM->value);
    if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded() && XPRD->SCHR->SCRO.IsLoaded())
        op.Accept(XPRD->SCHR->SCRO->value);
    if(XPRD.IsLoaded() && XPRD->TNAM.IsLoaded())
        op.Accept(XPRD->TNAM->value);
    //if(XRDO.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XRDO->value);
    if(XOWN.IsLoaded() && XOWN->XOWN.IsLoaded())
        op.Accept(XOWN->XOWN->value);
    //if(XLOC.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XLOC->value);
    if(XAMT.IsLoaded() && XAMT->XAMT.IsLoaded())
        op.Accept(XAMT->XAMT->value);
    //if(XPWR.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XPWR->value);
    if(XLTW.IsLoaded())
        op.Accept(XLTW->value);
    //if(XDCR.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XDCR->value);
    if(XLKR.IsLoaded())
        op.Accept(XLKR->value);
    //if(XAPR.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XAPR->value);
    //if(XESP.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XESP->value);
    if(XEMI.IsLoaded())
        op.Accept(XEMI->value);
    if(XMBR.IsLoaded())
        op.Accept(XMBR->value);
    //if(XNDP.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XNDP->value);
    //if(XPOD.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XPOD->value);
    if(XLRM.IsLoaded())
        op.Accept(XLRM->value);
    //if(XORD.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XORD->value);

    return op.Stop();
    }

bool REFRRecord::IsNoAlarm()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoAlarm) != 0;
    }

void REFRRecord::IsNoAlarm(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoAlarm) : (Dummy->flags & ~fIsNoAlarm);
    }

bool REFRRecord::Is0FlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void REFRRecord::Set0FlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool REFRRecord::IsVisible()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsVisible) != 0;
    }

void REFRRecord::IsVisible(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsVisible) : (Dummy->flags & ~fIsVisible);
    }

bool REFRRecord::IsCanTravelTo()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsCanTravelTo) != 0;
    }

void REFRRecord::IsCanTravelTo(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsCanTravelTo) : (Dummy->flags & ~fIsCanTravelTo);
    }

bool REFRRecord::Is1FlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void REFRRecord::Set1FlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool REFRRecord::IsUseDefault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseDefault) != 0;
    }

void REFRRecord::IsUseDefault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseDefault) : (Dummy->flags & ~fIsUseDefault);
    }

bool REFRRecord::IsActivate()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsActivate) != 0;
    }

void REFRRecord::IsActivate(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsActivate) : (Dummy->flags & ~fIsActivate);
    }

bool REFRRecord::IsOpen()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOpen) != 0;
    }

void REFRRecord::IsOpen(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsOpen) : (Dummy->flags & ~fIsOpen);
    }

bool REFRRecord::IsOpenByDefault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOpenByDefault) != 0;
    }

void REFRRecord::IsOpenByDefault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsOpenByDefault) : (Dummy->flags & ~fIsOpenByDefault);
    }

bool REFRRecord::Is3FlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void REFRRecord::Set3FlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool REFRRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void REFRRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool REFRRecord::IsBox()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBox);
    }

void REFRRecord::IsBox(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBox : eDummyDefault;
    }

bool REFRRecord::IsSphere()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSphere);
    }

void REFRRecord::IsSphere(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSphere : eDummyDefault;
    }

bool REFRRecord::IsPortalBox()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePortalBox);
    }

void REFRRecord::IsPortalBox(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePortalBox : eDummyDefault;
    }

bool REFRRecord::Is0Type(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void REFRRecord::Set0Type(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool REFRRecord::IsUnidentified()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnidentified);
    }

void REFRRecord::IsUnidentified(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUnidentified : eDummyDefault;
    }

bool REFRRecord::IsStatic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStatic);
    }

void REFRRecord::IsStatic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStatic : eDummyDefault;
    }

bool REFRRecord::IsAnimStatic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAnimStatic);
    }

void REFRRecord::IsAnimStatic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAnimStatic : eDummyDefault;
    }

bool REFRRecord::IsTransparent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTransparent);
    }

void REFRRecord::IsTransparent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTransparent : eDummyDefault;
    }

bool REFRRecord::IsClutter()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eClutter);
    }

void REFRRecord::IsClutter(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eClutter : eDummyDefault;
    }

bool REFRRecord::IsWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWeapon);
    }

void REFRRecord::IsWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWeapon : eDummyDefault;
    }

bool REFRRecord::IsProjectile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProjectile);
    }

void REFRRecord::IsProjectile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eProjectile : eDummyDefault;
    }

bool REFRRecord::IsSpell()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSpell);
    }

void REFRRecord::IsSpell(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSpell : eDummyDefault;
    }

bool REFRRecord::IsBiped()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBiped);
    }

void REFRRecord::IsBiped(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBiped : eDummyDefault;
    }

bool REFRRecord::IsTrees()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTrees);
    }

void REFRRecord::IsTrees(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTrees : eDummyDefault;
    }

bool REFRRecord::IsProps()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProps);
    }

void REFRRecord::IsProps(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eProps : eDummyDefault;
    }

bool REFRRecord::IsWater()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWater);
    }

void REFRRecord::IsWater(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWater : eDummyDefault;
    }

bool REFRRecord::IsTrigger()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTrigger);
    }

void REFRRecord::IsTrigger(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTrigger : eDummyDefault;
    }

bool REFRRecord::IsTerrain()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTerrain);
    }

void REFRRecord::IsTerrain(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTerrain : eDummyDefault;
    }

bool REFRRecord::IsTrap()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTrap);
    }

void REFRRecord::IsTrap(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTrap : eDummyDefault;
    }

bool REFRRecord::IsNonCollidable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNonCollidable);
    }

void REFRRecord::IsNonCollidable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNonCollidable : eDummyDefault;
    }

bool REFRRecord::IsCloudTrap()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCloudTrap);
    }

void REFRRecord::IsCloudTrap(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCloudTrap : eDummyDefault;
    }

bool REFRRecord::IsGround()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGround);
    }

void REFRRecord::IsGround(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGround : eDummyDefault;
    }

bool REFRRecord::IsPortal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePortal);
    }

void REFRRecord::IsPortal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePortal : eDummyDefault;
    }

bool REFRRecord::IsDebrisSmall()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDebrisSmall);
    }

void REFRRecord::IsDebrisSmall(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDebrisSmall : eDummyDefault;
    }

bool REFRRecord::IsDebrisLarge()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDebrisLarge);
    }

void REFRRecord::IsDebrisLarge(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDebrisLarge : eDummyDefault;
    }

bool REFRRecord::IsAcousticSpace()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAcousticSpace);
    }

void REFRRecord::IsAcousticSpace(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAcousticSpace : eDummyDefault;
    }

bool REFRRecord::IsActorZone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eActorZone);
    }

void REFRRecord::IsActorZone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eActorZone : eDummyDefault;
    }

bool REFRRecord::IsProjectileZone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProjectileZone);
    }

void REFRRecord::IsProjectileZone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eProjectileZone : eDummyDefault;
    }

bool REFRRecord::IsGasTrap()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGasTrap);
    }

void REFRRecord::IsGasTrap(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGasTrap : eDummyDefault;
    }

bool REFRRecord::IsShellCasing()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eShellCasing);
    }

void REFRRecord::IsShellCasing(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eShellCasing : eDummyDefault;
    }

bool REFRRecord::IsTransparentSmall()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTransparentSmall);
    }

void REFRRecord::IsTransparentSmall(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTransparentSmall : eDummyDefault;
    }

bool REFRRecord::IsInvisibleWall()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eInvisibleWall);
    }

void REFRRecord::IsInvisibleWall(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eInvisibleWall : eDummyDefault;
    }

bool REFRRecord::IsTransparentSmallAnim()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTransparentSmallAnim);
    }

void REFRRecord::IsTransparentSmallAnim(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTransparentSmallAnim : eDummyDefault;
    }

bool REFRRecord::IsDeadBip()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDeadBip);
    }

void REFRRecord::IsDeadBip(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDeadBip : eDummyDefault;
    }

bool REFRRecord::IsCharController()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCharController);
    }

void REFRRecord::IsCharController(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCharController : eDummyDefault;
    }

bool REFRRecord::IsAvoidBox()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAvoidBox);
    }

void REFRRecord::IsAvoidBox(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAvoidBox : eDummyDefault;
    }

bool REFRRecord::IsCollisionBox()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCollisionBox);
    }

void REFRRecord::IsCollisionBox(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCollisionBox : eDummyDefault;
    }

bool REFRRecord::IsCameraSphere()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCameraSphere);
    }

void REFRRecord::IsCameraSphere(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCameraSphere : eDummyDefault;
    }

bool REFRRecord::IsDoorDetection()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDoorDetection);
    }

void REFRRecord::IsDoorDetection(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDoorDetection : eDummyDefault;
    }

bool REFRRecord::IsCameraPick()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCameraPick);
    }

void REFRRecord::IsCameraPick(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCameraPick : eDummyDefault;
    }

bool REFRRecord::IsItemPick()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eItemPick);
    }

void REFRRecord::IsItemPick(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eItemPick : eDummyDefault;
    }

bool REFRRecord::IsLineOfSight()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLineOfSight);
    }

void REFRRecord::IsLineOfSight(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLineOfSight : eDummyDefault;
    }

bool REFRRecord::IsPathPick()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePathPick);
    }

void REFRRecord::IsPathPick(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePathPick : eDummyDefault;
    }

bool REFRRecord::IsCustomPick1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCustomPick1);
    }

void REFRRecord::IsCustomPick1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCustomPick1 : eDummyDefault;
    }

bool REFRRecord::IsCustomPick2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCustomPick2);
    }

void REFRRecord::IsCustomPick2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCustomPick2 : eDummyDefault;
    }

bool REFRRecord::IsSpellExplosion()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSpellExplosion);
    }

void REFRRecord::IsSpellExplosion(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSpellExplosion : eDummyDefault;
    }

bool REFRRecord::IsDroppingPick()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDroppingPick);
    }

void REFRRecord::IsDroppingPick(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDroppingPick : eDummyDefault;
    }

bool REFRRecord::Is1Type(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void REFRRecord::Set1Type(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool REFRRecord::IsMarkerNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMarkerNone);
    }

void REFRRecord::IsMarkerNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMarkerNone : eDummyDefault;
    }

bool REFRRecord::IsCity()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCity);
    }

void REFRRecord::IsCity(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCity : eDummyDefault;
    }

bool REFRRecord::IsSettlement()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSettlement);
    }

void REFRRecord::IsSettlement(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSettlement : eDummyDefault;
    }

bool REFRRecord::IsEncampment()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEncampment);
    }

void REFRRecord::IsEncampment(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEncampment : eDummyDefault;
    }

bool REFRRecord::IsNaturalLandmark()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNaturalLandmark);
    }

void REFRRecord::IsNaturalLandmark(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNaturalLandmark : eDummyDefault;
    }

bool REFRRecord::IsCave()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCave);
    }

void REFRRecord::IsCave(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCave : eDummyDefault;
    }

bool REFRRecord::IsFactory()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFactory);
    }

void REFRRecord::IsFactory(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFactory : eDummyDefault;
    }

bool REFRRecord::IsMonument()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMonument);
    }

void REFRRecord::IsMonument(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMonument : eDummyDefault;
    }

bool REFRRecord::IsMilitary()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMilitary);
    }

void REFRRecord::IsMilitary(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMilitary : eDummyDefault;
    }

bool REFRRecord::IsOffice()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOffice);
    }

void REFRRecord::IsOffice(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eOffice : eDummyDefault;
    }

bool REFRRecord::IsTownRuins()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTownRuins);
    }

void REFRRecord::IsTownRuins(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTownRuins : eDummyDefault;
    }

bool REFRRecord::IsUrbanRuins()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUrbanRuins);
    }

void REFRRecord::IsUrbanRuins(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUrbanRuins : eDummyDefault;
    }

bool REFRRecord::IsSewerRuins()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSewerRuins);
    }

void REFRRecord::IsSewerRuins(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSewerRuins : eDummyDefault;
    }

bool REFRRecord::IsMetro()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMetro);
    }

void REFRRecord::IsMetro(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMetro : eDummyDefault;
    }

bool REFRRecord::IsVault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVault);
    }

void REFRRecord::IsVault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVault : eDummyDefault;
    }

bool REFRRecord::Is2Type(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void REFRRecord::Set2Type(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool REFRRecord::IsRadius()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRadius);
    }

void REFRRecord::IsRadius(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRadius : eDummyDefault;
    }

bool REFRRecord::IsEverywhere()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEverywhere);
    }

void REFRRecord::IsEverywhere(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEverywhere : eDummyDefault;
    }

bool REFRRecord::IsWorldAndLinkedInteriors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWorldAndLinkedInteriors);
    }

void REFRRecord::IsWorldAndLinkedInteriors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWorldAndLinkedInteriors : eDummyDefault;
    }

bool REFRRecord::IsLinkedInteriors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLinkedInteriors);
    }

void REFRRecord::IsLinkedInteriors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLinkedInteriors : eDummyDefault;
    }

bool REFRRecord::IsCurrentCellOnly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCurrentCellOnly);
    }

void REFRRecord::IsCurrentCellOnly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCurrentCellOnly : eDummyDefault;
    }

bool REFRRecord::Is3Type(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void REFRRecord::Set3Type(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool REFRRecord::IsReflection()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eReflection);
    }

void REFRRecord::IsReflection(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eReflection : eDummyDefault;
    }

bool REFRRecord::IsRefraction()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRefraction);
    }

void REFRRecord::IsRefraction(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRefraction : eDummyDefault;
    }

bool REFRRecord::Is4Type(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void REFRRecord::Set4Type(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool REFRRecord::IsOppositeParent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOppositeParent) != 0;
    }

void REFRRecord::IsOppositeParent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsOppositeParent) : (Dummy->flags & ~fIsOppositeParent);
    }

bool REFRRecord::IsPopIn()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPopIn) != 0;
    }

void REFRRecord::IsPopIn(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPopIn) : (Dummy->flags & ~fIsPopIn);
    }

bool REFRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void REFRRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 REFRRecord::GetType()
    {
    return 'RFER';
    }

STRING REFRRecord::GetStrType()
    {
    return "REFR";
    }

SINT32 REFRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'RLCR':
                RCLR.Read(buffer, subSize, curPos);
                break;
            case 'EMAN':
                NAME.Read(buffer, subSize, curPos);
                break;
            case 'NZEX':
                XEZN.Read(buffer, subSize, curPos);
                break;
            case 'DGRX':
                XRGD.Read(buffer, subSize, curPos);
                break;
            case 'BGRX':
                XRGB.Read(buffer, subSize, curPos);
                break;
            case 'MRPX':
                XPRM.Read(buffer, subSize, curPos);
                break;
            case 'IRTX':
                XTRI.Read(buffer, subSize, curPos);
                break;
            case 'PBMX':
                //XMBP.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'OBMX':
                XMBO.Read(buffer, subSize, curPos);
                break;
            case 'LETX':
                XTEL.Read(buffer, subSize, curPos);
                break;
            case 'KRMX':
                //XMRK.Load();
                //XMRK->XMRK.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MANF':
                XMRK.Load();
                XMRK->FNAM.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case '1IMW':
                WMI1.Read(buffer, subSize, curPos);
                break;
            case 'KRMM':
                //MMRK.Load();
                //MMRK->MMRK.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'LLUF':
                MMRK.Load();
                MMRK->FULL.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                MMRK.Load();
                MMRK->CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANB':
                MMRK.Load();
                MMRK->BNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                MMRK.Load();
                MMRK->MNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANN':
                MMRK.Load();
                MMRK->NNAM.Read(buffer, subSize, curPos);
                break;
            case 'FRSX':
                XSRF.Read(buffer, subSize, curPos);
                break;
            case 'DRSX':
                XSRD.Read(buffer, subSize, curPos);
                break;
            case 'GRTX':
                XTRG.Read(buffer, subSize, curPos);
                break;
            case 'MCLX':
                XLCM.Read(buffer, subSize, curPos);
                break;
            case 'DRPX':
                XPRD.Load();
                XPRD->XPRD.Read(buffer, subSize, curPos);
                break;
            case 'APPX':
                //XPRD.Load();
                //XPRD->XPPA.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MANI':
                XPRD.Load();
                XPRD->INAM.Read(buffer, subSize, curPos);
                break;
            case 'RHCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case 'ADCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case 'XTCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case 'DSLS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case 'RVCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case 'ORCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case 'VRCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                XPRD.Load();
                XPRD->TNAM.Read(buffer, subSize, curPos);
                break;
            case 'ODRX':
                XRDO.Read(buffer, subSize, curPos);
                break;
            case 'NWOX':
                XOWN.Load();
                XOWN->XOWN.Read(buffer, subSize, curPos);
                break;
            case 'KNRX':
                XOWN.Load();
                XOWN->XRNK.Read(buffer, subSize, curPos);
                break;
            case 'COLX':
                XLOC.Read(buffer, subSize, curPos);
                break;
            case 'TNCX':
                XCNT.Read(buffer, subSize, curPos);
                break;
            case 'SDRX':
                XRDS.Read(buffer, subSize, curPos);
                break;
            case 'PLHX':
                XHLP.Read(buffer, subSize, curPos);
                break;
            case 'DARX':
                XRAD.Read(buffer, subSize, curPos);
                break;
            case 'GHCX':
                XCHG.Read(buffer, subSize, curPos);
                break;
            case 'TMAX':
                XAMT.Load();
                XAMT->XAMT.Read(buffer, subSize, curPos);
                break;
            case 'CMAX':
                XAMT.Load();
                XAMT->XAMC.Read(buffer, subSize, curPos);
                break;
            case 'RWPX':
                XPWR.Read(buffer, subSize, curPos);
                break;
            case 'WTLX':
                XLTW.Read(buffer, subSize, curPos);
                break;
            case 'RCDX':
                XDCR.Read(buffer, subSize, curPos);
                break;
            case 'RKLX':
                XLKR.Read(buffer, subSize, curPos);
                break;
            case 'PLCX':
                XCLP.Read(buffer, subSize, curPos);
                break;
            case 'DPAX':
                XAPD.Read(buffer, subSize, curPos);
                break;
            case 'RPAX':
                XAPR.Read(buffer, subSize, curPos);
                break;
            case 'OTAX':
                XATO.Read(buffer, subSize, curPos);
                break;
            case 'PSEX':
                XESP.Read(buffer, subSize, curPos);
                break;
            case 'IMEX':
                XEMI.Read(buffer, subSize, curPos);
                break;
            case 'RBMX':
                XMBR.Read(buffer, subSize, curPos);
                break;
            case 'TCAX':
                XACT.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                //ONAM.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'SBIX':
                //XIBS.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'PDNX':
                XNDP.Read(buffer, subSize, curPos);
                break;
            case 'DOPX':
                XPOD.Read(buffer, subSize, curPos);
                break;
            case 'LTPX':
                XPTL.Read(buffer, subSize, curPos);
                break;
            case 'DESX':
                XSED.Read(buffer, subSize, curPos);
                break;
            case 'RMRX':
                XRMR.Read(buffer, subSize, curPos);
                break;
            case 'MRLX':
                XLRM.Read(buffer, subSize, curPos);
                break;
            case 'PCOX':
                XOCP.Read(buffer, subSize, curPos);
                break;
            case 'DROX':
                XORD.Read(buffer, subSize, curPos);
                break;
            case 'DOLX':
                XLOD.Read(buffer, subSize, curPos);
                break;
            case 'LCSX':
                XSCL.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  REFR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 REFRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    RCLR.Unload();
    NAME.Unload();
    XEZN.Unload();
    XRGD.Unload();
    XRGB.Unload();
    XPRM.Unload();
    XTRI.Unload();
    //XMBP.Unload(); //FILL IN MANUALLY
    XMBO.Unload();
    XTEL.Unload();
    XMRK.Unload();
    FULL.Unload();
    TNAM.Unload();
    WMI1.Unload();
    MMRK.Unload();
    XSRF.Unload();
    XSRD.Unload();
    XTRG.Unload();
    XLCM.Unload();
    XPRD.Unload();
    XRDO.Unload();
    XOWN.Unload();
    XLOC.Unload();
    XCNT.Unload();
    XRDS.Unload();
    XHLP.Unload();
    XRAD.Unload();
    XCHG.Unload();
    XAMT.Unload();
    XPWR.Unload();
    XLTW.Unload();
    XDCR.Unload();
    XLKR.Unload();
    XCLP.Unload();
    XAPD.Unload();
    XAPR.Unload();
    XATO.Unload();
    XESP.Unload();
    XEMI.Unload();
    XMBR.Unload();
    XACT.Unload();
    //ONAM.Unload(); //FILL IN MANUALLY
    //XIBS.Unload(); //FILL IN MANUALLY
    XNDP.Unload();
    XPOD.Unload();
    XPTL.Unload();
    XSED.Unload();
    XRMR.Unload();
    XLRM.Unload();
    XOCP.Unload();
    XORD.Unload();
    XLOD.Unload();
    XSCL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 REFRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(RCLR);
    WRITE(NAME);
    WRITE(XEZN);
    WRITE(XRGD);
    WRITE(XRGB);
    WRITE(XPRM);
    WRITE(XTRI);

    //if(XMBP.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('PBMX', XMBP.value, XMBP.GetSize());
    WRITE(XMBO);
    WRITE(XTEL);

    if(XMRK.IsLoaded())
        {
        //if(XMRK->XMRK.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('KRMX', XMRK->XMRK.value, XMRK->XMRK.GetSize());

        if(XMRK->FNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANF', XMRK->FNAM.value, XMRK->FNAM.GetSize());

        }

    WRITE(FULL);
    WRITE(TNAM);
    WRITE(WMI1);

    if(MMRK.IsLoaded())
        {
        //if(MMRK->MMRK.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('KRMM', MMRK->MMRK.value, MMRK->MMRK.GetSize());

        if(MMRK->FULL.IsLoaded())
            SaveHandler.writeSubRecord('LLUF', MMRK->FULL.value, MMRK->FULL.GetSize());

        if(MMRK->CNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANC', MMRK->CNAM.value, MMRK->CNAM.GetSize());

        if(MMRK->BNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANB', MMRK->BNAM.value, MMRK->BNAM.GetSize());

        if(MMRK->MNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANM', MMRK->MNAM.value, MMRK->MNAM.GetSize());

        if(MMRK->NNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANN', MMRK->NNAM.value, MMRK->NNAM.GetSize());

        }

    WRITE(XSRF);
    WRITE(XSRD);
    WRITE(XTRG);
    WRITE(XLCM);

    if(XPRD.IsLoaded())
        {
        if(XPRD->XPRD.IsLoaded())
            SaveHandler.writeSubRecord('DRPX', XPRD->XPRD.value, XPRD->XPRD.GetSize());

        //if(XPRD->XPPA.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('APPX', XPRD->XPPA.value, XPRD->XPPA.GetSize());

        if(XPRD->INAM.IsLoaded())
            SaveHandler.writeSubRecord('MANI', XPRD->INAM.value, XPRD->INAM.GetSize());

        if(XPRD->SCHR.IsLoaded())
            {
            if(XPRD->SCHR->SCHR.IsLoaded())
                SaveHandler.writeSubRecord('RHCS', XPRD->SCHR->SCHR.value, XPRD->SCHR->SCHR.GetSize());

            if(XPRD->SCHR->SCDA.IsLoaded())
                SaveHandler.writeSubRecord('ADCS', XPRD->SCHR->SCDA.value, XPRD->SCHR->SCDA.GetSize());

            if(XPRD->SCHR->SCTX.IsLoaded())
                SaveHandler.writeSubRecord('XTCS', XPRD->SCHR->SCTX.value, XPRD->SCHR->SCTX.GetSize());

            if(XPRD->SCHR->SLSD.IsLoaded())
                SaveHandler.writeSubRecord('DSLS', XPRD->SCHR->SLSD.value, XPRD->SCHR->SLSD.GetSize());

            if(XPRD->SCHR->SCVR.IsLoaded())
                SaveHandler.writeSubRecord('RVCS', XPRD->SCHR->SCVR.value, XPRD->SCHR->SCVR.GetSize());

            if(XPRD->SCHR->SCRO.IsLoaded())
                SaveHandler.writeSubRecord('ORCS', XPRD->SCHR->SCRO.value, XPRD->SCHR->SCRO.GetSize());

            if(XPRD->SCHR->SCRV.IsLoaded())
                SaveHandler.writeSubRecord('VRCS', XPRD->SCHR->SCRV.value, XPRD->SCHR->SCRV.GetSize());

            }
        if(XPRD->TNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANT', XPRD->TNAM.value, XPRD->TNAM.GetSize());

        }

    WRITE(XRDO);

    if(XOWN.IsLoaded())
        {
        if(XOWN->XOWN.IsLoaded())
            SaveHandler.writeSubRecord('NWOX', XOWN->XOWN.value, XOWN->XOWN.GetSize());

        if(XOWN->XRNK.IsLoaded())
            SaveHandler.writeSubRecord('KNRX', XOWN->XRNK.value, XOWN->XRNK.GetSize());

        }

    WRITE(XLOC);
    WRITE(XCNT);
    WRITE(XRDS);
    WRITE(XHLP);
    WRITE(XRAD);
    WRITE(XCHG);

    if(XAMT.IsLoaded())
        {
        if(XAMT->XAMT.IsLoaded())
            SaveHandler.writeSubRecord('TMAX', XAMT->XAMT.value, XAMT->XAMT.GetSize());

        if(XAMT->XAMC.IsLoaded())
            SaveHandler.writeSubRecord('CMAX', XAMT->XAMC.value, XAMT->XAMC.GetSize());

        }

    WRITE(XPWR);
    WRITE(XLTW);
    WRITE(XDCR);
    WRITE(XLKR);
    WRITE(XCLP);
    WRITE(XAPD);
    WRITE(XAPR);
    WRITE(XATO);
    WRITE(XESP);
    WRITE(XEMI);
    WRITE(XMBR);
    WRITE(XACT);

    //if(ONAM.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('MANO', ONAM.value, ONAM.GetSize());

    //if(XIBS.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('SBIX', XIBS.value, XIBS.GetSize());
    WRITE(XNDP);
    WRITE(XPOD);
    WRITE(XPTL);
    WRITE(XSED);
    WRITE(XRMR);
    WRITE(XLRM);
    WRITE(XOCP);
    WRITE(XORD);
    WRITE(XLOD);
    WRITE(XSCL);
    WRITE(DATA);

    return -1;
    }

bool REFRRecord::operator ==(const REFRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            RCLR == other.RCLR &&
            NAME == other.NAME &&
            XEZN == other.XEZN &&
            XRGD == other.XRGD &&
            XRGB == other.XRGB &&
            XPRM == other.XPRM &&
            XTRI == other.XTRI &&
            //Empty &&
            XMBO == other.XMBO &&
            XTEL == other.XTEL &&
            //EmptyFNAM == other.FNAM &&
            FULL.equals(other.FULL) &&
            TNAM == other.TNAM &&
            WMI1 == other.WMI1 &&
            //EmptyFULL == other.FULL &&
            XSRF == other.XSRF &&
            XSRD == other.XSRD &&
            XTRG == other.XTRG &&
            XLCM == other.XLCM &&
            XPRD == other.XPRD &&
            XRDO == other.XRDO &&
            XOWN == other.XOWN &&
            XLOC == other.XLOC &&
            XCNT == other.XCNT &&
            XRDS == other.XRDS &&
            XHLP == other.XHLP &&
            XRAD == other.XRAD &&
            XCHG == other.XCHG &&
            XAMT == other.XAMT &&
            XPWR == other.XPWR &&
            XLTW == other.XLTW &&
            XDCR == other.XDCR &&
            XLKR == other.XLKR &&
            XCLP == other.XCLP &&
            XAPD == other.XAPD &&
            XAPR == other.XAPR &&
            XATO.equalsi(other.XATO) &&
            XESP == other.XESP &&
            XEMI == other.XEMI &&
            XMBR == other.XMBR &&
            XACT == other.XACT &&
            //Empty &&
            //Empty &&
            XNDP == other.XNDP &&
            XPOD == other.XPOD &&
            XPTL == other.XPTL &&
            XSED == other.XSED &&
            XRMR == other.XRMR &&
            XLRM == other.XLRM &&
            XOCP == other.XOCP &&
            XORD == other.XORD &&
            XLOD == other.XLOD &&
            XSCL == other.XSCL &&
            DATA == other.DATA);
    }

bool REFRRecord::operator !=(const REFRRecord &other) const
    {
    return !(*this == other);
    }
}