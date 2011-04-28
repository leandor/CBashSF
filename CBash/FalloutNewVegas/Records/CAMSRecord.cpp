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

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
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
                MODL->Textures.Read(buffer, subSize, curPos);
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