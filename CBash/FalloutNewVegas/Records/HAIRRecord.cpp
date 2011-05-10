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
#include "HAIRRecord.h"

namespace FNV
{
HAIRRecord::HAIRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

HAIRRecord::HAIRRecord(HAIRRecord *srcRecord):
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
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    DATA = srcRecord->DATA;
    return;
    }

HAIRRecord::~HAIRRecord()
    {
    //
    }

bool HAIRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }

    return op.Stop();
    }

bool HAIRRecord::IsPlayable()
    {
    return (DATA.value & fIsPlayable) != 0;
    }

void HAIRRecord::IsPlayable(bool value)
    {
    DATA.value = value ? (DATA.value | fIsPlayable) : (DATA.value & ~fIsPlayable);
    }

bool HAIRRecord::IsNotMale()
    {
    return (DATA.value & fIsNotMale) != 0;
    }

void HAIRRecord::IsNotMale(bool value)
    {
    DATA.value = value ? (DATA.value | fIsNotMale) : (DATA.value & ~fIsNotMale);
    }

bool HAIRRecord::IsMale()
    {
    return !IsNotMale();
    }

void HAIRRecord::IsMale(bool value)
    {
    IsNotMale(!value);
    }

bool HAIRRecord::IsNotFemale()
    {
    return (DATA.value & fIsNotFemale) != 0;
    }

void HAIRRecord::IsNotFemale(bool value)
    {
    DATA.value = value ? (DATA.value | fIsNotFemale) : (DATA.value & ~fIsNotFemale);
    }

bool HAIRRecord::IsFemale()
    {
    return !IsNotFemale();
    }

void HAIRRecord::IsFemale(bool value)
    {
    IsNotFemale(!value);
    }

bool HAIRRecord::IsFixedColor()
    {
    return (DATA.value & fIsFixedColor) != 0;
    }

void HAIRRecord::IsFixedColor(bool value)
    {
    DATA.value = value ? (DATA.value | fIsFixedColor) : (DATA.value & ~fIsFixedColor);
    }

bool HAIRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void HAIRRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value = Mask;
    }

UINT32 HAIRRecord::GetType()
    {
    return REV32(HAIR);
    }

STRING HAIRRecord::GetStrType()
    {
    return "HAIR";
    }

SINT32 HAIRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  HAIR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 HAIRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 HAIRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(DATA);
    return -1;
    }

bool HAIRRecord::operator ==(const HAIRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            DATA == other.DATA);
    }

bool HAIRRecord::operator !=(const HAIRRecord &other) const
    {
    return !(*this == other);
    }
}