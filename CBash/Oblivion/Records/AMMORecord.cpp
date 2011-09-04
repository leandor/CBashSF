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
#include "AMMORecord.h"

namespace Ob
{
AMMORecord::AMMODATA::AMMODATA():
    speed(0.0f),
    flags(0),
    value(0),
    weight(0.0f),
    damage(0)
    {
    memset(&unused1[0], 0xCD, sizeof(unused1));
    }

AMMORecord::AMMODATA::~AMMODATA()
    {
    //
    }

bool AMMORecord::AMMODATA::operator ==(const AMMODATA &other) const
    {
    return (AlmostEqual(speed,other.speed,2) &&
            flags == other.flags &&
            value == other.value &&
            AlmostEqual(weight,other.weight,2) &&
            damage == other.damage);
    }

bool AMMORecord::AMMODATA::operator !=(const AMMODATA &other) const
    {
    return !(*this == other);
    }

AMMORecord::AMMORecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

AMMORecord::AMMORecord(AMMORecord *srcRecord):
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
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    ENAM = srcRecord->ENAM;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    return;
    }

AMMORecord::~AMMORecord()
    {
    //
    }

bool AMMORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool AMMORecord::IsNotNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void AMMORecord::IsNotNormalWeapon(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNotNormalWeapon) : (DATA.value.flags & ~fIsNotNormalWeapon);
    }

bool AMMORecord::IsNotNormal()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void AMMORecord::IsNotNormal(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNotNormalWeapon) : (DATA.value.flags & ~fIsNotNormalWeapon);
    }

bool AMMORecord::IsNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) == 0;
    }

void AMMORecord::IsNormalWeapon(bool value)
    {
    DATA.value.flags = value ? DATA.value.flags & ~fIsNotNormalWeapon : DATA.value.flags | fIsNotNormalWeapon;
    }

bool AMMORecord::IsNormal()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) == 0;
    }

void AMMORecord::IsNormal(bool value)
    {
    DATA.value.flags = value ? DATA.value.flags & ~fIsNotNormalWeapon : DATA.value.flags | fIsNotNormalWeapon;
    }

bool AMMORecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void AMMORecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 AMMORecord::GetType()
    {
    return REV32(AMMO);
    }

STRING AMMORecord::GetStrType()
    {
    return "AMMO";
    }

SINT32 AMMORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  AMMO: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 AMMORecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    ENAM.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 AMMORecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(ENAM);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool AMMORecord::operator ==(const AMMORecord &other) const
    {
    return (ENAM == other.ENAM &&
            ANAM == other.ANAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MODL == other.MODL);
    }

bool AMMORecord::operator !=(const AMMORecord &other) const
    {
    return !(*this == other);
    }

bool AMMORecord::equals(Record *other)
    {
    return *this == *(AMMORecord *)other;
    }
}