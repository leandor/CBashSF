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
#include "WEAPRecord.h"

namespace Ob
{
WEAPRecord::WEAPDATA::WEAPDATA():
    weaponType(0),
    speed(0.0f),
    reach(0.0f),
    flags(0),
    value(0),
    health(0),
    weight(0.0f),
    damage(0)
    {
    //
    }

WEAPRecord::WEAPDATA::~WEAPDATA()
    {
    //
    }

bool WEAPRecord::WEAPDATA::operator ==(const WEAPDATA &other) const
    {
    return (weaponType == other.weaponType &&
            AlmostEqual(speed,other.speed,2) &&
            AlmostEqual(reach,other.reach,2) &&
            flags == other.flags &&
            value == other.value &&
            health == other.health &&
            AlmostEqual(weight,other.weight,2) &&
            damage == other.damage);
    }

bool WEAPRecord::WEAPDATA::operator !=(const WEAPDATA &other) const
    {
    return !(*this == other);
    }

WEAPRecord::WEAPRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

WEAPRecord::WEAPRecord(WEAPRecord *srcRecord):Record()
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
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    SCRI = srcRecord->SCRI;
    ENAM = srcRecord->ENAM;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    }

WEAPRecord::~WEAPRecord()
    {
    //
    }

bool WEAPRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool WEAPRecord::IsNotNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void WEAPRecord::IsNotNormalWeapon(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNotNormalWeapon) : (DATA.value.flags & ~fIsNotNormalWeapon);
    }

bool WEAPRecord::IsNotNormal()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void WEAPRecord::IsNotNormal(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNotNormalWeapon) : (DATA.value.flags & ~fIsNotNormalWeapon);
    }

bool WEAPRecord::IsNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) == 0;
    }

void WEAPRecord::IsNormalWeapon(bool value)
    {
    DATA.value.flags = value ? DATA.value.flags & ~fIsNotNormalWeapon : DATA.value.flags | fIsNotNormalWeapon;
    }

bool WEAPRecord::IsNormal()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) == 0;
    }

void WEAPRecord::IsNormal(bool value)
    {
    DATA.value.flags = value ? DATA.value.flags & ~fIsNotNormalWeapon : DATA.value.flags | fIsNotNormalWeapon;
    }

bool WEAPRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void WEAPRecord::SetFlagMask(UINT32 Mask)
    {
    DATA.value.flags = Mask;
    }

bool WEAPRecord::IsBlade1Hand()
    {
    return (DATA.value.weaponType == eBlade1Hand);
    }

void WEAPRecord::IsBlade1Hand(bool value)
    {
    if(value)
        DATA.value.weaponType = eBlade1Hand;
    else if(IsBlade1Hand())
        DATA.value.weaponType = eBlade2Hand;
    }

bool WEAPRecord::IsBlade2Hand()
    {
    return (DATA.value.weaponType == eBlade2Hand);
    }

void WEAPRecord::IsBlade2Hand(bool value)
    {
    if(value)
        DATA.value.weaponType = eBlade2Hand;
    else if(IsBlade2Hand())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsBlunt1Hand()
    {
    return (DATA.value.weaponType == eBlunt1Hand);
    }

void WEAPRecord::IsBlunt1Hand(bool value)
    {
    if(value)
        DATA.value.weaponType = eBlunt1Hand;
    else if(IsBlunt1Hand())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsBlunt2Hand()
    {
    return (DATA.value.weaponType == eBlunt2Hand);
    }

void WEAPRecord::IsBlunt2Hand(bool value)
    {
    if(value)
        DATA.value.weaponType = eBlunt2Hand;
    else if(IsBlunt2Hand())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsStaff()
    {
    return (DATA.value.weaponType == eStaff);
    }

void WEAPRecord::IsStaff(bool value)
    {
    if(value)
        DATA.value.weaponType = eStaff;
    else if(IsStaff())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsBow()
    {
    return (DATA.value.weaponType == eBow);
    }

void WEAPRecord::IsBow(bool value)
    {
    if(value)
        DATA.value.weaponType = eBow;
    else if(IsBow())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsType(UINT32 Type)
    {
    return (DATA.value.weaponType == Type);
    }

void WEAPRecord::SetType(UINT32 Type)
    {
    DATA.value.weaponType = Type;
    }

UINT32 WEAPRecord::GetType()
    {
    return REV32(WEAP);
    }

STRING WEAPRecord::GetStrType()
    {
    return "WEAP";
    }

SINT32 WEAPRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
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
                printer("  WEAP: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 WEAPRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    SCRI.Unload();
    ENAM.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 WEAPRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(SCRI);
    WRITE(ENAM);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool WEAPRecord::operator ==(const WEAPRecord &other) const
    {
    return (ANAM == other.ANAM &&
            SCRI == other.SCRI &&
            ENAM == other.ENAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MODL == other.MODL);
    }

bool WEAPRecord::operator !=(const WEAPRecord &other) const
    {
    return !(*this == other);
    }

bool WEAPRecord::equals(Record *other)
    {
    return *this == *(WEAPRecord *)other;
    }
}