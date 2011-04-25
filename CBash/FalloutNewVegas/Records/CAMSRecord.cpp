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
#include "CAMSRecord.h"

namespace FNV
{
CAMSRecord::CAMSRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CAMSRecord::CAMSRecord(CAMSRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    DATA = srcRecord->DATA;
    MNAM = srcRecord->MNAM;
    return;
    }

CAMSRecord::~CAMSRecord()
    {
    //
    }

bool CAMSRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(MNAM.IsLoaded())
        op.Accept(MNAM->value);

    return op.Stop();
    }

bool CAMSRecord::IsPosFollowsLocation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPosFollowsLocation) != 0;
    }

void CAMSRecord::IsPosFollowsLocation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPosFollowsLocation;
    else
        Dummy->flags &= ~fIsPosFollowsLocation;
    }

bool CAMSRecord::IsPosFollowsTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPosFollowsTarget) != 0;
    }

void CAMSRecord::IsPosFollowsTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPosFollowsTarget;
    else
        Dummy->flags &= ~fIsPosFollowsTarget;
    }

bool CAMSRecord::IsDontFollowBone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDontFollowBone) != 0;
    }

void CAMSRecord::IsDontFollowBone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDontFollowBone;
    else
        Dummy->flags &= ~fIsDontFollowBone;
    }

bool CAMSRecord::IsFirstPersonCamera()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFirstPersonCamera) != 0;
    }

void CAMSRecord::IsFirstPersonCamera(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsFirstPersonCamera;
    else
        Dummy->flags &= ~fIsFirstPersonCamera;
    }

bool CAMSRecord::IsNoTracer()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoTracer) != 0;
    }

void CAMSRecord::IsNoTracer(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoTracer;
    else
        Dummy->flags &= ~fIsNoTracer;
    }

bool CAMSRecord::IsStartAtTimeZero()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsStartAtTimeZero) != 0;
    }

void CAMSRecord::IsStartAtTimeZero(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsStartAtTimeZero;
    else
        Dummy->flags &= ~fIsStartAtTimeZero;
    }

bool CAMSRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CAMSRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CAMSRecord::IsActionShoot()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eShoot);
    }

void CAMSRecord::IsActionShoot(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eShoot;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsActionFly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFly);
    }

void CAMSRecord::IsActionFly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eFly;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsActionHit()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHit);
    }

void CAMSRecord::IsActionHit(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHit;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsActionZoom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eZoom);
    }

void CAMSRecord::IsActionZoom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eZoom;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsActionType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CAMSRecord::SetActionType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CAMSRecord::IsLocationAttacker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttacker);
    }

void CAMSRecord::IsLocationAttacker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAttacker;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsLocationProjectile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProjectile);
    }

void CAMSRecord::IsLocationProjectile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eProjectile;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsLocationTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTarget);
    }

void CAMSRecord::IsLocationTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eTarget;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsLocationType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CAMSRecord::SetLocationType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CAMSRecord::IsTargetAttacker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttacker);
    }

void CAMSRecord::IsTargetAttacker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAttacker;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsTargetProjectile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProjectile);
    }

void CAMSRecord::IsTargetProjectile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eProjectile;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsTargetTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTarget);
    }

void CAMSRecord::IsTargetTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eTarget;
    else
        Dummy->flags = eDummyDefault;
    }

bool CAMSRecord::IsTargetType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CAMSRecord::SetTargetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CAMSRecord::GetSize(bool forceCalc)
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

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(MNAM.IsLoaded())
        TotSize += MNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 CAMSRecord::GetType()
    {
    return 'SMAC';
    }

STRING CAMSRecord::GetStrType()
    {
    return "CAMS";
    }

SINT32 CAMSRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                MNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CAMS: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CAMSRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    DATA.Unload();
    MNAM.Unload();
    return 1;
    }

SINT32 CAMSRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

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

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(MNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANM', MNAM.value, MNAM.GetSize());

    return -1;
    }

bool CAMSRecord::operator ==(const CAMSRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            DATA == other.DATA &&
            MNAM == other.MNAM);
    }

bool CAMSRecord::operator !=(const CAMSRecord &other) const
    {
    return !(*this == other);
    }
}