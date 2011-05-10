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
#include "PROJRecord.h"

namespace FNV
{
PROJRecord::PROJDATA::PROJDATA():
    flags(0),
    projType(0),
    gravity(0.0f),
    speed(0.0f),
    range(0.0f),
    light(0),
    flash(0),
    tracerChance(0.0f),
    altExplProximityTrigger(0.0f),
    altExplProximityTimer(0.0f),
    explosion(0),
    sound(0),
    flashDuration(0.0f),
    fadeDuration(0.0f),
    impactForce(0.0f),
    soundCountdown(0),
    soundDisable(0),
    defaultWeaponSource(0),
    rotX(0.0f),
    rotY(0.0f),
    rotZ(0.0f),
    bouncyMult(0.0f)
    {
    //
    }

PROJRecord::PROJDATA::~PROJDATA()
    {
    //
    }

bool PROJRecord::PROJDATA::operator ==(const PROJDATA &other) const
    {
    return (flags == other.flags &&
            projType == other.projType &&
            light == other.light &&
            flash == other.flash &&
            explosion == other.explosion &&
            sound == other.sound &&
            soundCountdown == other.soundCountdown &&
            soundDisable == other.soundDisable &&
            defaultWeaponSource == other.defaultWeaponSource &&
            AlmostEqual(gravity,other.gravity,2) &&
            AlmostEqual(speed,other.speed,2) &&
            AlmostEqual(range,other.range,2) &&
            AlmostEqual(tracerChance,other.tracerChance,2) &&
            AlmostEqual(altExplProximityTrigger,other.altExplProximityTrigger,2) &&
            AlmostEqual(altExplProximityTimer,other.altExplProximityTimer,2) &&
            AlmostEqual(flashDuration,other.flashDuration,2) &&
            AlmostEqual(fadeDuration,other.fadeDuration,2) &&
            AlmostEqual(impactForce,other.impactForce,2) &&
            AlmostEqual(rotX,other.rotX,2) &&
            AlmostEqual(rotY,other.rotY,2) &&
            AlmostEqual(rotZ,other.rotZ,2) &&
            AlmostEqual(bouncyMult,other.bouncyMult,2));
    }

bool PROJRecord::PROJDATA::operator !=(const PROJDATA &other) const
    {
    return !(*this == other);
    }

PROJRecord::PROJRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PROJRecord::PROJRecord(PROJRecord *srcRecord):
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
    Destructable = srcRecord->Destructable;
    DATA = srcRecord->DATA;
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    VNAM = srcRecord->VNAM;
    return;
    }

PROJRecord::~PROJRecord()
    {
    //
    }

bool PROJRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    op.Accept(DATA.value.light);
    op.Accept(DATA.value.flash);
    op.Accept(DATA.value.explosion);
    op.Accept(DATA.value.sound);
    op.Accept(DATA.value.soundCountdown);
    op.Accept(DATA.value.soundDisable);
    op.Accept(DATA.value.defaultWeaponSource);
    return op.Stop();
    }

bool PROJRecord::IsHitscan()
    {
    return (DATA.value.flags & fIsHitscan) != 0;
    }

void PROJRecord::IsHitscan(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsHitscan) : (DATA.value.flags & ~fIsHitscan);
    }

bool PROJRecord::IsExplosion()
    {
    return (DATA.value.flags & fIsExplosion) != 0;
    }

void PROJRecord::IsExplosion(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsExplosion) : (DATA.value.flags & ~fIsExplosion);
    }

bool PROJRecord::IsAltTrigger()
    {
    return (DATA.value.flags & fIsAltTrigger) != 0;
    }

void PROJRecord::IsAltTrigger(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsAltTrigger) : (DATA.value.flags & ~fIsAltTrigger);
    }

bool PROJRecord::IsMuzzleFlash()
    {
    return (DATA.value.flags & fIsMuzzleFlash) != 0;
    }

void PROJRecord::IsMuzzleFlash(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsMuzzleFlash) : (DATA.value.flags & ~fIsMuzzleFlash);
    }

bool PROJRecord::IsDisableable()
    {
    return (DATA.value.flags & fIsDisableable) != 0;
    }

void PROJRecord::IsDisableable(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsDisableable) : (DATA.value.flags & ~fIsDisableable);
    }

bool PROJRecord::IsPickupable()
    {
    return (DATA.value.flags & fIsPickupable) != 0;
    }

void PROJRecord::IsPickupable(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsPickupable) : (DATA.value.flags & ~fIsPickupable);
    }

bool PROJRecord::IsSupersonic()
    {
    return (DATA.value.flags & fIsSupersonic) != 0;
    }

void PROJRecord::IsSupersonic(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsSupersonic) : (DATA.value.flags & ~fIsSupersonic);
    }

bool PROJRecord::IsPinsLimbs()
    {
    return (DATA.value.flags & fIsPinsLimbs) != 0;
    }

void PROJRecord::IsPinsLimbs(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsPinsLimbs) : (DATA.value.flags & ~fIsPinsLimbs);
    }

bool PROJRecord::IsPassSmallTransparent()
    {
    return (DATA.value.flags & fIsPassSmallTransparent) != 0;
    }

void PROJRecord::IsPassSmallTransparent(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsPassSmallTransparent) : (DATA.value.flags & ~fIsPassSmallTransparent);
    }

bool PROJRecord::IsDetonates()
    {
    return (DATA.value.flags & fIsDetonates) != 0;
    }

void PROJRecord::IsDetonates(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsDetonates) : (DATA.value.flags & ~fIsDetonates);
    }

bool PROJRecord::IsRotation()
    {
    return (DATA.value.flags & fIsRotation) != 0;
    }

void PROJRecord::IsRotation(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsRotation) : (DATA.value.flags & ~fIsRotation);
    }

bool PROJRecord::IsFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void PROJRecord::SetFlagMask(UINT16 Mask)
    {
    DATA.value.flags = Mask;
    }

bool PROJRecord::IsMissile()
    {
    return DATA.value.projType == eMissile;
    }

void PROJRecord::IsMissile(bool value)
    {
    DATA.value.projType = value ? eMissile : eLobber;
    }

bool PROJRecord::IsLobber()
    {
    return DATA.value.projType == eLobber;
    }

void PROJRecord::IsLobber(bool value)
    {
    DATA.value.projType = value ? eLobber : eMissile;
    }

bool PROJRecord::IsBeam()
    {
    return DATA.value.projType == eBeam;
    }

void PROJRecord::IsBeam(bool value)
    {
    DATA.value.projType = value ? eBeam : eMissile;
    }

bool PROJRecord::IsFlame()
    {
    return DATA.value.projType == eFlame;
    }

void PROJRecord::IsFlame(bool value)
    {
    DATA.value.projType = value ? eFlame : eMissile;
    }

bool PROJRecord::IsContinuousBeam()
    {
    return DATA.value.projType == eContinuousBeam;
    }

void PROJRecord::IsContinuousBeam(bool value)
    {
    DATA.value.projType = value ? eContinuousBeam : eMissile;
    }

bool PROJRecord::IsType(UINT16 Type)
    {
    return DATA.value.projType == Type;
    }

void PROJRecord::SetType(UINT16 Type)
    {
    DATA.value.projType = Type;
    }

bool PROJRecord::IsLoud()
    {
    return VNAM.value == eLoud;
    }

void PROJRecord::IsLoud(bool value)
    {
    VNAM.value = value ? eLoud : eNormal;
    }

bool PROJRecord::IsNormal()
    {
    return VNAM.value == eNormal;
    }

void PROJRecord::IsNormal(bool value)
    {
    VNAM.value = value ? eNormal : eLoud;
    }

bool PROJRecord::IsSilent()
    {
    return VNAM.value == eSilent;
    }

void PROJRecord::IsSilent(bool value)
    {
    VNAM.value = value ? eSilent : eLoud;
    }

bool PROJRecord::IsSoundLevelType(UINT32 Type)
    {
    return VNAM.value == Type;
    }

void PROJRecord::SetSoundLevelType(UINT32 Type)
    {
    VNAM.value = Type;
    }

UINT32 PROJRecord::GetType()
    {
    return REV32(PROJ);
    }

STRING PROJRecord::GetStrType()
    {
    return "PROJ";
    }

SINT32 PROJRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize, curPos);
                break;
            case REV32(VNAM):
                VNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  PROJ: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 PROJRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    Destructable.Unload();
    DATA.Unload();
    NAM1.Unload();
    NAM2.Unload();
    VNAM.Unload();
    return 1;
    }

SINT32 PROJRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    Destructable.Write(writer);
    WRITE(DATA);
    WRITE(NAM1);
    WRITE(NAM2);
    WRITE(VNAM);
    return -1;
    }

bool PROJRecord::operator ==(const PROJRecord &other) const
    {
    return (OBND == other.OBND &&
            DATA == other.DATA &&
            NAM2 == other.NAM2 &&
            VNAM == other.VNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NAM1.equalsi(other.NAM1) &&
            MODL == other.MODL &&
            Destructable == other.Destructable);
    }

bool PROJRecord::operator !=(const PROJRecord &other) const
    {
    return !(*this == other);
    }
}