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
#include "SOUNRecord.h"

namespace Ob
{
SOUNRecord::SOUNSNDX::SOUNSNDX():
    minDistance(0),
    maxDistance(0),
    freqAdjustment(0),
    unused1(0),
    flags(0),
    staticAtten(0),
    stopTime(0),
    startTime(0)
    {
    memset(&unused2[0], 0x00, sizeof(unused2));
    }

SOUNRecord::SOUNSNDX::~SOUNSNDX()
    {
    //
    }

bool SOUNRecord::SOUNSNDX::operator ==(const SOUNSNDX &other) const
    {
    return (minDistance == other.minDistance &&
            maxDistance == other.maxDistance &&
            freqAdjustment == other.freqAdjustment &&
            flags == other.flags &&
            staticAtten == other.staticAtten &&
            stopTime == other.stopTime &&
            startTime == other.startTime);
    }

bool SOUNRecord::SOUNSNDX::operator !=(const SOUNSNDX &other) const
    {
    return !(*this == other);
    }

SOUNRecord::SOUNRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SOUNRecord::SOUNRecord(SOUNRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    FNAM = srcRecord->FNAM;
    SNDX = srcRecord->SNDX;
    }

SOUNRecord::~SOUNRecord()
    {
    //
    }

bool SOUNRecord::IsRandomFrequencyShift()
    {
    return (SNDX.value.flags & fIsRandomFrequencyShift) != 0;
    }

void SOUNRecord::IsRandomFrequencyShift(bool value)
    {
    SNDX.value.flags = value ? (SNDX.value.flags | fIsRandomFrequencyShift) : (SNDX.value.flags & ~fIsRandomFrequencyShift);
    }

bool SOUNRecord::IsPlayAtRandom()
    {
    return (SNDX.value.flags & fIsPlayAtRandom) != 0;
    }

void SOUNRecord::IsPlayAtRandom(bool value)
    {
    SNDX.value.flags = value ? (SNDX.value.flags | fIsPlayAtRandom) : (SNDX.value.flags & ~fIsPlayAtRandom);
    }

bool SOUNRecord::IsEnvironmentIgnored()
    {
    return (SNDX.value.flags & fIsEnvironmentIgnored) != 0;
    }

void SOUNRecord::IsEnvironmentIgnored(bool value)
    {
    SNDX.value.flags = value ? (SNDX.value.flags | fIsEnvironmentIgnored) : (SNDX.value.flags & ~fIsEnvironmentIgnored);
    }

bool SOUNRecord::IsRandomLocation()
    {
    return (SNDX.value.flags & fIsRandomLocation) != 0;
    }

void SOUNRecord::IsRandomLocation(bool value)
    {
    SNDX.value.flags = value ? (SNDX.value.flags | fIsRandomLocation) : (SNDX.value.flags & ~fIsRandomLocation);
    }

bool SOUNRecord::IsLoop()
    {
    return (SNDX.value.flags & fIsLoop) != 0;
    }

void SOUNRecord::IsLoop(bool value)
    {
    SNDX.value.flags = value ? (SNDX.value.flags | fIsLoop) : (SNDX.value.flags & ~fIsLoop);
    }

bool SOUNRecord::IsMenuSound()
    {
    return (SNDX.value.flags & fIsMenuSound) != 0;
    }

void SOUNRecord::IsMenuSound(bool value)
    {
    SNDX.value.flags = value ? (SNDX.value.flags | fIsMenuSound) : (SNDX.value.flags & ~fIsMenuSound);
    }

bool SOUNRecord::Is2D()
    {
    return (SNDX.value.flags & fIs2D) != 0;
    }

void SOUNRecord::Is2D(bool value)
    {
    SNDX.value.flags = value ? (SNDX.value.flags | fIs2D) : (SNDX.value.flags & ~fIs2D);
    }

bool SOUNRecord::Is360LFE()
    {
    return (SNDX.value.flags & fIs360LFE) != 0;
    }

void SOUNRecord::Is360LFE(bool value)
    {
    SNDX.value.flags = value ? (SNDX.value.flags | fIs360LFE) : (SNDX.value.flags & ~fIs360LFE);
    }

bool SOUNRecord::IsFlagMask(unsigned short Mask, bool Exact)
    {
    return Exact ? ((SNDX.value.flags & Mask) == Mask) : ((SNDX.value.flags & Mask) != 0);
    }

void SOUNRecord::SetFlagMask(unsigned short Mask)
    {
    SNDX.value.flags = Mask;
    }

UINT32 SOUNRecord::GetType()
    {
    return REV32(SOUN);
    }

STRING SOUNRecord::GetStrType()
    {
    return "SOUN";
    }

SINT32 SOUNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(FNAM):
                FNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNDD):
            case REV32(SNDX):
                SNDX.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SOUN: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 SOUNRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FNAM.Unload();
    SNDX.Unload();
    return 1;
    }

SINT32 SOUNRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FNAM);
    WRITE(SNDX);
    return -1;
    }

bool SOUNRecord::operator ==(const SOUNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FNAM.equalsi(other.FNAM) &&
            SNDX == other.SNDX);
    }

bool SOUNRecord::operator !=(const SOUNRecord &other) const
    {
    return !(*this == other);
    }

bool SOUNRecord::equals(Record *other)
    {
    return *this == *(SOUNRecord *)other;
    }
}