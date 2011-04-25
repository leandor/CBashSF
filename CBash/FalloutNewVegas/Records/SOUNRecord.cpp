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
    SNDX = srcRecord->SNDX;
    ANAM = srcRecord->ANAM;
    GNAM = srcRecord->GNAM;
    HNAM = srcRecord->HNAM;
    return;
    }

SOUNRecord::~SOUNRecord()
    {
    //
    }

bool SOUNRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;


    return op.Stop();
    }

bool SOUNRecord::IsRandomFrequencyShift()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRandomFrequencyShift) != 0;
    }

void SOUNRecord::IsRandomFrequencyShift(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRandomFrequencyShift;
    else
        Dummy->flags &= ~fIsRandomFrequencyShift;
    }

bool SOUNRecord::IsPlayAtRandom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPlayAtRandom) != 0;
    }

void SOUNRecord::IsPlayAtRandom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPlayAtRandom;
    else
        Dummy->flags &= ~fIsPlayAtRandom;
    }

bool SOUNRecord::IsEnvironmentIgnored()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEnvironmentIgnored) != 0;
    }

void SOUNRecord::IsEnvironmentIgnored(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsEnvironmentIgnored;
    else
        Dummy->flags &= ~fIsEnvironmentIgnored;
    }

bool SOUNRecord::IsRandomLocation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRandomLocation) != 0;
    }

void SOUNRecord::IsRandomLocation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRandomLocation;
    else
        Dummy->flags &= ~fIsRandomLocation;
    }

bool SOUNRecord::IsLoop()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsLoop) != 0;
    }

void SOUNRecord::IsLoop(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsLoop;
    else
        Dummy->flags &= ~fIsLoop;
    }

bool SOUNRecord::IsMenuSound()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMenuSound) != 0;
    }

void SOUNRecord::IsMenuSound(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsMenuSound;
    else
        Dummy->flags &= ~fIsMenuSound;
    }

bool SOUNRecord::Is2D()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIs2D) != 0;
    }

void SOUNRecord::Is2D(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIs2D;
    else
        Dummy->flags &= ~fIs2D;
    }

bool SOUNRecord::Is360LFE()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIs360LFE) != 0;
    }

void SOUNRecord::Is360LFE(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIs360LFE;
    else
        Dummy->flags &= ~fIs360LFE;
    }

bool SOUNRecord::IsDialogueSound()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDialogueSound) != 0;
    }

void SOUNRecord::IsDialogueSound(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDialogueSound;
    else
        Dummy->flags &= ~fIsDialogueSound;
    }

bool SOUNRecord::IsEnvelopeFast()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEnvelopeFast) != 0;
    }

void SOUNRecord::IsEnvelopeFast(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsEnvelopeFast;
    else
        Dummy->flags &= ~fIsEnvelopeFast;
    }

bool SOUNRecord::IsEnvelopeSlow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEnvelopeSlow) != 0;
    }

void SOUNRecord::IsEnvelopeSlow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsEnvelopeSlow;
    else
        Dummy->flags &= ~fIsEnvelopeSlow;
    }

bool SOUNRecord::Is2DRadius()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIs2DRadius) != 0;
    }

void SOUNRecord::Is2DRadius(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIs2DRadius;
    else
        Dummy->flags &= ~fIs2DRadius;
    }

bool SOUNRecord::IsMuteWhenSubmerged()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMuteWhenSubmerged) != 0;
    }

void SOUNRecord::IsMuteWhenSubmerged(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsMuteWhenSubmerged;
    else
        Dummy->flags &= ~fIsMuteWhenSubmerged;
    }

bool SOUNRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void SOUNRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
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

    if(SNDD.IsLoaded())
        TotSize += SNDD.GetSize() + 6;

    if(SNDX.IsLoaded())
        TotSize += SNDX.GetSize() + 6;

    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;

    if(GNAM.IsLoaded())
        TotSize += GNAM.GetSize() + 6;

    if(HNAM.IsLoaded())
        TotSize += HNAM.GetSize() + 6;

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
            case 'XDNS':
                SNDX.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'MANG':
                GNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
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
    SNDX.Unload();
    ANAM.Unload();
    GNAM.Unload();
    HNAM.Unload();
    return 1;
    }

SINT32 SOUNRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANF', FNAM.value, FNAM.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

    if(SNDD.IsLoaded())
        SaveHandler.writeSubRecord('DDNS', SNDD.value, SNDD.GetSize());

    if(SNDX.IsLoaded())
        SaveHandler.writeSubRecord('XDNS', SNDX.value, SNDX.GetSize());

    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord('MANA', ANAM.value, ANAM.GetSize());

    if(GNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANG', GNAM.value, GNAM.GetSize());

    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANH', HNAM.value, HNAM.GetSize());

    return -1;
    }

bool SOUNRecord::operator ==(const SOUNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FNAM.equalsi(other.FNAM) &&
            RNAM == other.RNAM &&
            SNDD == other.SNDD &&
            SNDX == other.SNDX &&
            ANAM == other.ANAM &&
            GNAM == other.GNAM &&
            HNAM == other.HNAM);
    }

bool SOUNRecord::operator !=(const SOUNRecord &other) const
    {
    return !(*this == other);
    }
}