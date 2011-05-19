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
#include "WATRRecord.h"

namespace FNV
{
WATRRecord::WATRDNAM::WATRDNAM():
    unknown1(0.0f),
    unknown2(0.0f),
    unknown3(0.0f),
    unknown4(0.0f),
    sunPower(50.0f),
    reflectAmt(0.50f),
    fresnelAmt(0.020f),
    fogNear(0.0f),
    fogFar(0.0f),
    rainForce(0.40f),
    rainVelocity(0.60f),
    rainFalloff(0.9850f),
    rainDampner(10.0f),
    dispSize(0.010f),
    dispForce(0.10f),
    dispVelocity(0.60f),
    dispFalloff(0.9850f),
    dispDampner(2.0f),
    rainSize(0.050f),
    normalsNoiseScale(1.0f),
    noise1Direction(1.0f),
    noise2Direction(1.0f),
    noise3Direction(1.0f),
    noise1Speed(1.0f),
    noise2Speed(1.0f),
    noise3Speed(1.0f),
    normalsFalloffStart(0.0f),
    normalsFalloffEnd(0.0f),
    fogAmt(1.0f),
    normalsUVScale(500.0f),
    underFogAmt(1.0f),
    underFogNear(0.0f),
    underFogFar(1000.0f),
    distAmt(250.0f),
    shininess(100.0f),
    hdrMult(1.0f),
    lightRadius(10000.0f),
    lightBright(1.0f),
    noise1UVScale(100.0f),
    noise2UVScale(100.0f),
    noise3UVScale(100.0f),
    noise1AmpScale(0.0f),
    noise2AmpScale(0.0f),
    noise3AmpScale(0.0f)
    {
    shallow.green = 128;
    shallow.blue = 128;
    deep.blue = 25;
    refl.red = 255;
    refl.green = 255;
    refl.blue = 255;
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unused2[0], 0x00, sizeof(unused2));
    }

WATRRecord::WATRDNAM::~WATRDNAM()
    {
    //
    }

bool WATRRecord::WATRDNAM::operator ==(const WATRDNAM &other) const
    {
    return (shallow == other.shallow &&
            deep == other.deep &&
            refl == other.refl &&
            AlmostEqual(unknown1,other.unknown1,2) &&
            AlmostEqual(unknown2,other.unknown2,2) &&
            AlmostEqual(unknown3,other.unknown3,2) &&
            AlmostEqual(unknown4,other.unknown4,2) &&
            AlmostEqual(sunPower,other.sunPower,2) &&
            AlmostEqual(reflectAmt,other.reflectAmt,2) &&
            AlmostEqual(fresnelAmt,other.fresnelAmt,2) &&
            AlmostEqual(fogNear,other.fogNear,2) &&
            AlmostEqual(fogFar,other.fogFar,2) &&
            AlmostEqual(rainForce,other.rainForce,2) &&
            AlmostEqual(rainVelocity,other.rainVelocity,2) &&
            AlmostEqual(rainFalloff,other.rainFalloff,2) &&
            AlmostEqual(rainDampner,other.rainDampner,2) &&
            AlmostEqual(dispSize,other.dispSize,2) &&
            AlmostEqual(dispForce,other.dispForce,2) &&
            AlmostEqual(dispVelocity,other.dispVelocity,2) &&
            AlmostEqual(dispFalloff,other.dispFalloff,2) &&
            AlmostEqual(dispDampner,other.dispDampner,2) &&
            AlmostEqual(rainSize,other.rainSize,2) &&
            AlmostEqual(normalsNoiseScale,other.normalsNoiseScale,2) &&
            AlmostEqual(noise1Direction,other.noise1Direction,2) &&
            AlmostEqual(noise2Direction,other.noise2Direction,2) &&
            AlmostEqual(noise3Direction,other.noise3Direction,2) &&
            AlmostEqual(noise1Speed,other.noise1Speed,2) &&
            AlmostEqual(noise2Speed,other.noise2Speed,2) &&
            AlmostEqual(noise3Speed,other.noise3Speed,2) &&
            AlmostEqual(normalsFalloffStart,other.normalsFalloffStart,2) &&
            AlmostEqual(normalsFalloffEnd,other.normalsFalloffEnd,2) &&
            AlmostEqual(fogAmt,other.fogAmt,2) &&
            AlmostEqual(normalsUVScale,other.normalsUVScale,2) &&
            AlmostEqual(underFogAmt,other.underFogAmt,2) &&
            AlmostEqual(underFogNear,other.underFogNear,2) &&
            AlmostEqual(underFogFar,other.underFogFar,2) &&
            AlmostEqual(distAmt,other.distAmt,2) &&
            AlmostEqual(shininess,other.shininess,2) &&
            AlmostEqual(hdrMult,other.hdrMult,2) &&
            AlmostEqual(lightRadius,other.lightRadius,2) &&
            AlmostEqual(lightBright,other.lightBright,2) &&
            AlmostEqual(noise1UVScale,other.noise1UVScale,2) &&
            AlmostEqual(noise2UVScale,other.noise2UVScale,2) &&
            AlmostEqual(noise3UVScale,other.noise3UVScale,2) &&
            AlmostEqual(noise1AmpScale,other.noise1AmpScale,2) &&
            AlmostEqual(noise2AmpScale,other.noise2AmpScale,2) &&
            AlmostEqual(noise3AmpScale,other.noise3AmpScale,2));
    }

bool WATRRecord::WATRDNAM::operator !=(const WATRDNAM &other) const
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
    FNVRecord(_recData)
    {
    //
    }

WATRRecord::WATRRecord(WATRRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    NNAM = srcRecord->NNAM;
    ANAM = srcRecord->ANAM;
    FNAM = srcRecord->FNAM;
    MNAM = srcRecord->MNAM;
    SNAM = srcRecord->SNAM;
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    DNAM = srcRecord->DNAM;
    GNAM = srcRecord->GNAM;
    return;
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
    if(XNAM.IsLoaded())
        op.Accept(XNAM.value);
    op.Accept(GNAM.value.dayWater);
    op.Accept(GNAM.value.nightWater);
    op.Accept(GNAM.value.underWater);

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

SINT32 WATRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, curPos);
                break;
            case REV32(NNAM):
                NNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize, curPos);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                switch(subSize)
                    {
                    case sizeof(DATA.value):
                        DATA.Read(buffer, subSize, curPos);
                        break;
                    case 186:
                        //last field of older DATA format is damage, and rest are congruent with DNAM
                        //last three fields of DNAM will be at their default value
                        DNAM.Read(buffer, subSize - 2, curPos);
                        DATA.Read(buffer, 2, curPos);
                        break;
                    default:
                        printf("  WATR: %08X - Unexpected DATA size\n", formID);
                        CBASH_CHUNK_DEBUG
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  WATR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    FULL.Unload();
    NNAM.Unload();
    ANAM.Unload();
    FNAM.Unload();
    MNAM.Unload();
    SNAM.Unload();
    XNAM.Unload();
    DATA.Unload();
    DNAM.Unload();
    GNAM.Unload();
    return 1;
    }

SINT32 WATRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITEREQ(NNAM);
    WRITE(ANAM);
    WRITE(FNAM);
    WRITEREQ(MNAM);
    WRITE(SNAM);
    WRITE(XNAM);
    WRITE(DATA);
    WRITE(DNAM);
    WRITE(GNAM);
    return -1;
    }

bool WATRRecord::operator ==(const WATRRecord &other) const
    {
    return (ANAM == other.ANAM &&
            FNAM == other.FNAM &&
            SNAM == other.SNAM &&
            XNAM == other.XNAM &&
            DNAM == other.DNAM &&
            GNAM == other.GNAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NNAM.equalsi(other.NNAM) &&
            MNAM.equalsi(other.MNAM));
    }

bool WATRRecord::operator !=(const WATRRecord &other) const
    {
    return !(*this == other);
    }
}