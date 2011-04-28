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
#include "SOUNRecord.h"

namespace FNV
{
SOUNRecord::SOUNSNDD::SOUNSNDD():
    minDistance(0),
    maxDistance(0),
    freqAdjustment(0),
    unused1(0),
    flags(0),
    staticAtten(0),
    stopTime(0),
    startTime(0),
    reverb(0),
    priority(0),
    x(0),
    y(0)
    {
    memset(&attenCurve[0], 0x00, 10);
    }

SOUNRecord::SOUNSNDD::~SOUNSNDD()
    {
    //
    }

bool SOUNRecord::SOUNSNDD::operator ==(const SOUNSNDD &other) const
    {
    return (minDistance == other.minDistance &&
            maxDistance == other.maxDistance &&
            freqAdjustment == other.freqAdjustment &&
            flags == other.flags &&
            staticAtten == other.staticAtten &&
            stopTime == other.stopTime &&
            startTime == other.startTime &&
            reverb == other.reverb &&
            priority == other.priority &&
            x == other.x &&
            y == other.y &&
            attenCurve[0] == other.attenCurve[0] &&
            attenCurve[1] == other.attenCurve[1] &&
            attenCurve[2] == other.attenCurve[2] &&
            attenCurve[3] == other.attenCurve[3] &&
            attenCurve[4] == other.attenCurve[4]);
    }

bool SOUNRecord::SOUNSNDD::operator !=(const SOUNSNDD &other) const
    {
    return !(*this == other);
    }

SOUNRecord::SOUNRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

SOUNRecord::SOUNRecord(SOUNRecord *srcRecord):
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
    FNAM = srcRecord->FNAM;
    RNAM = srcRecord->RNAM;
    SNDD = srcRecord->SNDD;
    return;
    }

SOUNRecord::~SOUNRecord()
    {
    //
    }

bool SOUNRecord::IsRandomFrequencyShift()
    {
    return (SNDD.value.flags & fIsRandomFrequencyShift) != 0;
    }

void SOUNRecord::IsRandomFrequencyShift(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsRandomFrequencyShift) : (SNDD.value.flags & ~fIsRandomFrequencyShift);
    }

bool SOUNRecord::IsPlayAtRandom()
    {
    return (SNDD.value.flags & fIsPlayAtRandom) != 0;
    }

void SOUNRecord::IsPlayAtRandom(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsPlayAtRandom) : (SNDD.value.flags & ~fIsPlayAtRandom);
    }

bool SOUNRecord::IsEnvironmentIgnored()
    {
    return (SNDD.value.flags & fIsEnvironmentIgnored) != 0;
    }

void SOUNRecord::IsEnvironmentIgnored(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsEnvironmentIgnored) : (SNDD.value.flags & ~fIsEnvironmentIgnored);
    }

bool SOUNRecord::IsRandomLocation()
    {
    return (SNDD.value.flags & fIsRandomLocation) != 0;
    }

void SOUNRecord::IsRandomLocation(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsRandomLocation) : (SNDD.value.flags & ~fIsRandomLocation);
    }

bool SOUNRecord::IsLoop()
    {
    return (SNDD.value.flags & fIsLoop) != 0;
    }

void SOUNRecord::IsLoop(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsLoop) : (SNDD.value.flags & ~fIsLoop);
    }

bool SOUNRecord::IsMenuSound()
    {
    return (SNDD.value.flags & fIsMenuSound) != 0;
    }

void SOUNRecord::IsMenuSound(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsMenuSound) : (SNDD.value.flags & ~fIsMenuSound);
    }

bool SOUNRecord::Is2D()
    {
    return (SNDD.value.flags & fIs2D) != 0;
    }

void SOUNRecord::Is2D(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIs2D) : (SNDD.value.flags & ~fIs2D);
    }

bool SOUNRecord::Is360LFE()
    {
    return (SNDD.value.flags & fIs360LFE) != 0;
    }

void SOUNRecord::Is360LFE(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIs360LFE) : (SNDD.value.flags & ~fIs360LFE);
    }

bool SOUNRecord::IsDialogueSound()
    {
    return (SNDD.value.flags & fIsDialogueSound) != 0;
    }

void SOUNRecord::IsDialogueSound(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsDialogueSound) : (SNDD.value.flags & ~fIsDialogueSound);
    }

bool SOUNRecord::IsEnvelopeFast()
    {
    return (SNDD.value.flags & fIsEnvelopeFast) != 0;
    }

void SOUNRecord::IsEnvelopeFast(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsEnvelopeFast) : (SNDD.value.flags & ~fIsEnvelopeFast);
    }

bool SOUNRecord::IsEnvelopeSlow()
    {
    return (SNDD.value.flags & fIsEnvelopeSlow) != 0;
    }

void SOUNRecord::IsEnvelopeSlow(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsEnvelopeSlow) : (SNDD.value.flags & ~fIsEnvelopeSlow);
    }

bool SOUNRecord::Is2DRadius()
    {
    return (SNDD.value.flags & fIs2DRadius) != 0;
    }

void SOUNRecord::Is2DRadius(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIs2DRadius) : (SNDD.value.flags & ~fIs2DRadius);
    }

bool SOUNRecord::IsMuteWhenSubmerged()
    {
    return (SNDD.value.flags & fIsMuteWhenSubmerged) != 0;
    }

void SOUNRecord::IsMuteWhenSubmerged(bool value)
    {
    SNDD.value.flags = value ? (SNDD.value.flags | fIsMuteWhenSubmerged) : (SNDD.value.flags & ~fIsMuteWhenSubmerged);
    }

bool SOUNRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((SNDD.value.flags & Mask) == Mask) : ((SNDD.value.flags & Mask) != 0);
    }

void SOUNRecord::SetFlagMask(UINT32 Mask)
    {
    SNDD.value.flags = Mask;
    }

UINT32 SOUNRecord::GetSize(bool forceCalc)
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

    if(FNAM.IsLoaded())
        {
        cSize = FNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(RNAM.IsLoaded())
        TotSize += RNAM.GetSize() + 6;

    TotSize += SNDD.GetSize() + 6;

    return TotSize;
    }

UINT32 SOUNRecord::GetType()
    {
    return 'NUOS';
    }

STRING SOUNRecord::GetStrType()
    {
    return "SOUN";
    }

SINT32 SOUNRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            case 'DDNS':
                SNDD.Read(buffer, subSize, curPos);
                break;
            case 'XDNS': //auto update to SNDD
                SNDD.Read(buffer, subSize, curPos);
                break;
            case 'MANA': //auto update to SNDD
                _readBuffer(&SNDD.value.attenCurve[0], buffer, subSize, curPos);
                break;
            case 'MANG': //auto update to SNDD
                _readBuffer(&SNDD.value.reverb, buffer, subSize, curPos);
                break;
            case 'MANH': //auto update to SNDD
                _readBuffer(&SNDD.value.priority, buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  SOUN: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    OBND.Unload();
    FNAM.Unload();
    RNAM.Unload();
    SNDD.Unload();
    return 1;
    }

SINT32 SOUNRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', &OBND.value, OBND.GetSize());

    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANF', FNAM.value, FNAM.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

    SaveHandler.writeSubRecord('DDNS', &SNDD.value, SNDD.GetSize());

    return -1;
    }

bool SOUNRecord::operator ==(const SOUNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FNAM.equalsi(other.FNAM) &&
            RNAM == other.RNAM &&
            SNDD == other.SNDD);
    }

bool SOUNRecord::operator !=(const SOUNRecord &other) const
    {
    return !(*this == other);
    }
}