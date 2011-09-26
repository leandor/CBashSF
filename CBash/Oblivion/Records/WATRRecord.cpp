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
#include "WATRRecord.h"

namespace Ob
{
WATRRecord::WATRDATA::WATRDATA():
    windVelocity(0.1f),
    windDirection(90.0f),
    waveAmp(0.5f),
    waveFreq(1.0f),
    sunPower(50.0f),
    reflectAmt(0.5f),
    fresnelAmt(0.025f),
    xSpeed(0.0f),
    ySpeed(0.0f),
    fogNear(27852.801f),
    fogFar(163840.0f),
    shallow(0, 128, 128, 0),
    deep(0, 0, 25, 0),
    refl(255, 255, 255, 0),
    blend(50),
    rainForce(0.1f),
    rainVelocity(0.6f),
    rainFalloff(0.985f),
    rainDampner(2.0f),
    rainSize(0.01f),
    dispForce(0.4f),
    dispVelocity(0.6f),
    dispFalloff(0.985f),
    dispDampner(10.0f),
    dispSize(0.05f),
    damage(0)
    {
    memset(&unused1[0], 0xCD, sizeof(unused1));
    }

WATRRecord::WATRDATA::~WATRDATA()
    {
    //
    }

bool WATRRecord::WATRDATA::operator ==(const WATRDATA &other) const
    {
    return (damage == other.damage &&
            blend == other.blend &&
            AlmostEqual(windVelocity,other.windVelocity,2) &&
            AlmostEqual(windDirection,other.windDirection,2) &&
            AlmostEqual(waveAmp,other.waveAmp,2) &&
            AlmostEqual(waveFreq,other.waveFreq,2) &&
            AlmostEqual(sunPower,other.sunPower,2) &&
            AlmostEqual(reflectAmt,other.reflectAmt,2) &&
            AlmostEqual(fresnelAmt,other.fresnelAmt,2) &&
            AlmostEqual(xSpeed,other.xSpeed,2) &&
            AlmostEqual(ySpeed,other.ySpeed,2) &&
            AlmostEqual(fogNear,other.fogNear,2) &&
            AlmostEqual(fogFar,other.fogFar,2) &&
            AlmostEqual(rainForce,other.rainForce,2) &&
            AlmostEqual(rainVelocity,other.rainVelocity,2) &&
            AlmostEqual(rainFalloff,other.rainFalloff,2) &&
            AlmostEqual(rainDampner,other.rainDampner,2) &&
            AlmostEqual(rainSize,other.rainSize,2) &&
            AlmostEqual(dispForce,other.dispForce,2) &&
            AlmostEqual(dispVelocity,other.dispVelocity,2) &&
            AlmostEqual(dispFalloff,other.dispFalloff,2) &&
            AlmostEqual(dispDampner,other.dispDampner,2) &&
            AlmostEqual(dispSize,other.dispSize,2) &&
            shallow == other.shallow &&
            deep == other.deep &&
            refl == other.refl);
    }

bool WATRRecord::WATRDATA::operator !=(const WATRDATA &other) const
    {
    return !(*this == other);
    }

WATRRecord::WATRGNAM::WATRGNAM():
    dayWater(0),
    nightWater(0),
    underWater(0)
    {
    //
    }

WATRRecord::WATRGNAM::~WATRGNAM()
    {
    //
    }

bool WATRRecord::WATRGNAM::operator ==(const WATRGNAM &other) const
    {
    return (dayWater == other.dayWater &&
            nightWater == other.nightWater &&
            underWater == other.underWater);
    }

bool WATRRecord::WATRGNAM::operator !=(const WATRGNAM &other) const
    {
    return !(*this == other);
    }

WATRRecord::WATRRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

WATRRecord::WATRRecord(WATRRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    TNAM = srcRecord->TNAM;
    ANAM = srcRecord->ANAM;
    FNAM = srcRecord->FNAM;
    MNAM = srcRecord->MNAM;
    SNAM = srcRecord->SNAM;
    DATA = srcRecord->DATA;
    GNAM = srcRecord->GNAM;
    }

WATRRecord::~WATRRecord()
    {
    //
    }

bool WATRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(GNAM.IsLoaded())
        {
        op.Accept(GNAM->dayWater);
        op.Accept(GNAM->nightWater);
        op.Accept(GNAM->underWater);
        }

    return op.Stop();
    }

bool WATRRecord::IsCausesDmg()
    {
    return (FNAM.value & fIsCausesDamage) != 0;
    }

void WATRRecord::IsCausesDmg(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsCausesDamage) : (FNAM.value & ~fIsCausesDamage);
    }

bool WATRRecord::IsCausesDamage()
    {
    return (FNAM.value & fIsCausesDamage) != 0;
    }

void WATRRecord::IsCausesDamage(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsCausesDamage) : (FNAM.value & ~fIsCausesDamage);
    }

bool WATRRecord::IsReflective()
    {
    return (FNAM.value & fIsReflective) != 0;
    }

void WATRRecord::IsReflective(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsReflective) : (FNAM.value & ~fIsReflective);
    }

bool WATRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((FNAM.value & Mask) == Mask) : ((FNAM.value & Mask) != 0);
    }

void WATRRecord::SetFlagMask(UINT8 Mask)
    {
    FNAM.value = Mask;
    }

UINT32 WATRRecord::GetType()
    {
    return REV32(WATR);
    }

STRING WATRRecord::GetStrType()
    {
    return "WATR";
    }

SINT32 WATRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WATR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 WATRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    TNAM.Unload();
    ANAM.Unload();
    FNAM.Unload();
    MNAM.Unload();
    SNAM.Unload();
    DATA.Unload();
    GNAM.Unload();
    return 1;
    }

SINT32 WATRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(TNAM);
    WRITE(ANAM);
    WRITE(FNAM);
    WRITE(MNAM);
    WRITE(SNAM);
    WRITE(DATA);
    WRITE(GNAM);
    return -1;
    }

bool WATRRecord::operator ==(const WATRRecord &other) const
    {
    return (ANAM == other.ANAM &&
            FNAM == other.FNAM &&
            SNAM == other.SNAM &&
            GNAM == other.GNAM &&
            EDID.equalsi(other.EDID) &&
            TNAM.equalsi(other.TNAM) &&
            MNAM.equalsi(other.MNAM) &&
            DATA == other.DATA);
    }

bool WATRRecord::operator !=(const WATRRecord &other) const
    {
    return !(*this == other);
    }

bool WATRRecord::equals(Record *other)
    {
    return *this == *(WATRRecord *)other;
    }
}