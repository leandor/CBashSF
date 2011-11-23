/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
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
    memset(&attenCurve[0], 0x00, sizeof(attenCurve));
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

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
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            case REV32(SNDD):
                SNDD.Read(buffer, subSize);
                break;
            case REV32(SNDX): //auto update to SNDD
                SNDD.Read(buffer, subSize);
                break;
            case REV32(ANAM): //auto update to SNDD
                memcpy(&SNDD.value.attenCurve[0], buffer, subSize);
                buffer += subSize;
                break;
            case REV32(GNAM): //auto update to SNDD
                memcpy(&SNDD.value.reverb, buffer, subSize);
                buffer += subSize;
                break;
            case REV32(HNAM): //auto update to SNDD
                memcpy(&SNDD.value.priority, buffer, subSize);
                buffer += subSize;
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
    OBND.Unload();
    FNAM.Unload();
    RNAM.Unload();
    SNDD.Unload();
    return 1;
    }

SINT32 SOUNRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FNAM);
    WRITE(RNAM);
    WRITE(SNDD);
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

bool SOUNRecord::equals(Record *other)
    {
    return *this == *(SOUNRecord *)other;
    }
}