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
    FNVRecord(_recData)
    {
    //
    }

CAMSRecord::CAMSRecord(CAMSRecord *srcRecord):
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

    MODL = srcRecord->MODL;

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

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
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
    Dummy->flags = value ? (Dummy->flags | fIsPosFollowsLocation) : (Dummy->flags & ~fIsPosFollowsLocation);
    }

bool CAMSRecord::IsPosFollowsTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPosFollowsTarget) != 0;
    }

void CAMSRecord::IsPosFollowsTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPosFollowsTarget) : (Dummy->flags & ~fIsPosFollowsTarget);
    }

bool CAMSRecord::IsDontFollowBone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDontFollowBone) != 0;
    }

void CAMSRecord::IsDontFollowBone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDontFollowBone) : (Dummy->flags & ~fIsDontFollowBone);
    }

bool CAMSRecord::IsFirstPersonCamera()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFirstPersonCamera) != 0;
    }

void CAMSRecord::IsFirstPersonCamera(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsFirstPersonCamera) : (Dummy->flags & ~fIsFirstPersonCamera);
    }

bool CAMSRecord::IsNoTracer()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoTracer) != 0;
    }

void CAMSRecord::IsNoTracer(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoTracer) : (Dummy->flags & ~fIsNoTracer);
    }

bool CAMSRecord::IsStartAtTimeZero()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsStartAtTimeZero) != 0;
    }

void CAMSRecord::IsStartAtTimeZero(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsStartAtTimeZero) : (Dummy->flags & ~fIsStartAtTimeZero);
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
    Dummy->flags = value ? eShoot : eDummyDefault;
    }

bool CAMSRecord::IsActionFly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFly);
    }

void CAMSRecord::IsActionFly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFly : eDummyDefault;
    }

bool CAMSRecord::IsActionHit()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHit);
    }

void CAMSRecord::IsActionHit(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHit : eDummyDefault;
    }

bool CAMSRecord::IsActionZoom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eZoom);
    }

void CAMSRecord::IsActionZoom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eZoom : eDummyDefault;
    }

bool CAMSRecord::IsActionType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
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
    Dummy->flags = value ? eAttacker : eDummyDefault;
    }

bool CAMSRecord::IsLocationProjectile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProjectile);
    }

void CAMSRecord::IsLocationProjectile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eProjectile : eDummyDefault;
    }

bool CAMSRecord::IsLocationTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTarget);
    }

void CAMSRecord::IsLocationTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTarget : eDummyDefault;
    }

bool CAMSRecord::IsLocationType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
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
    Dummy->flags = value ? eAttacker : eDummyDefault;
    }

bool CAMSRecord::IsTargetProjectile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProjectile);
    }

void CAMSRecord::IsTargetProjectile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eProjectile : eDummyDefault;
    }

bool CAMSRecord::IsTargetTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTarget);
    }

void CAMSRecord::IsTargetTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTarget : eDummyDefault;
    }

bool CAMSRecord::IsTargetType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void CAMSRecord::SetTargetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CAMSRecord::GetType()
    {
    return REV32(CAMS);
    }

STRING CAMSRecord::GetStrType()
    {
    return "CAMS";
    }

SINT32 CAMSRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
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
                EDID.Read(buffer, subSize);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CAMS: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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

SINT32 CAMSRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);

    MODL.Write(writer);

    WRITE(DATA);
    WRITE(MNAM);

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

bool CAMSRecord::equals(const Record *other) const
    {
    return *this == *(CAMSRecord *)other;
    }
}