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
#include "EYESRecord.h"

namespace FNV
{
EYESRecord::EYESRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

EYESRecord::EYESRecord(EYESRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    DATA = srcRecord->DATA;
    return;
    }

EYESRecord::~EYESRecord()
    {
    //
    }

bool EYESRecord::IsPlayable()
    {
    return (DATA.value & fIsPlayable) != 0;
    }

void EYESRecord::IsPlayable(bool value)
    {
    DATA.value = value ? (DATA.value | fIsPlayable) : (DATA.value & ~fIsPlayable);
    }

bool EYESRecord::IsNotMale()
    {
    return (DATA.value & fIsNotMale) != 0;
    }

void EYESRecord::IsNotMale(bool value)
    {
    DATA.value = value ? (DATA.value | fIsNotMale) : (DATA.value & ~fIsNotMale);
    }

bool EYESRecord::IsMale()
    {
    return !IsNotMale();
    }

void EYESRecord::IsMale(bool value)
    {
    IsNotMale(!value);
    }

bool EYESRecord::IsNotFemale()
    {
    return (DATA.value & fIsNotFemale) != 0;
    }

void EYESRecord::IsNotFemale(bool value)
    {
    DATA.value = value ? (DATA.value | fIsNotFemale) : (DATA.value & ~fIsNotFemale);
    }

bool EYESRecord::IsFemale()
    {
    return !IsNotFemale();
    }

void EYESRecord::IsFemale(bool value)
    {
    IsNotFemale(!value);
    }

bool EYESRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void EYESRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value = Mask;
    }

UINT32 EYESRecord::GetType()
    {
    return 'SEYE';
    }

STRING EYESRecord::GetStrType()
    {
    return "EYES";
    }

SINT32 EYESRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  EYES: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 EYESRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    ICON.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 EYESRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(ICON);
    WRITE(DATA);
    return -1;
    }

bool EYESRecord::operator ==(const EYESRecord &other) const
    {
    return (DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON));
    }

bool EYESRecord::operator !=(const EYESRecord &other) const
    {
    return !(*this == other);
    }
}