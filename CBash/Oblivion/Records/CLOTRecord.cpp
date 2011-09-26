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
#include "CLOTRecord.h"

namespace Ob
{
CLOTRecord::CLOTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CLOTRecord::CLOTRecord(CLOTRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    SCRI = srcRecord->SCRI;
    ENAM = srcRecord->ENAM;
    ANAM = srcRecord->ANAM;
    BMDT = srcRecord->BMDT;
    MODL = srcRecord->MODL;
    MOD2 = srcRecord->MOD2;
    ICON = srcRecord->ICON;
    MOD3 = srcRecord->MOD3;
    MOD4 = srcRecord->MOD4;
    ICO2 = srcRecord->ICO2;
    DATA = srcRecord->DATA;
    return;
    }

CLOTRecord::~CLOTRecord()
    {
    //
    }

bool CLOTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool CLOTRecord::IsHead()
    {
    return (BMDT.value & fIsHead) != 0;
    }

void CLOTRecord::IsHead(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHead) : (BMDT.value & ~fIsHead);
    }

bool CLOTRecord::IsHair()
    {
    return (BMDT.value & fIsHair) != 0;
    }

void CLOTRecord::IsHair(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHair) : (BMDT.value & ~fIsHair);
    }

bool CLOTRecord::IsUpperBody()
    {
    return (BMDT.value & fIsUpperBody) != 0;
    }

void CLOTRecord::IsUpperBody(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsUpperBody) : (BMDT.value & ~fIsUpperBody);
    }

bool CLOTRecord::IsLowerBody()
    {
    return (BMDT.value & fIsLowerBody) != 0;
    }

void CLOTRecord::IsLowerBody(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsLowerBody) : (BMDT.value & ~fIsLowerBody);
    }

bool CLOTRecord::IsHand()
    {
    return (BMDT.value & fIsHand) != 0;
    }

void CLOTRecord::IsHand(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHand) : (BMDT.value & ~fIsHand);
    }

bool CLOTRecord::IsFoot()
    {
    return (BMDT.value & fIsFoot) != 0;
    }

void CLOTRecord::IsFoot(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsFoot) : (BMDT.value & ~fIsFoot);
    }

bool CLOTRecord::IsRightRing()
    {
    return (BMDT.value & fIsRightRing) != 0;
    }

void CLOTRecord::IsRightRing(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsRightRing) : (BMDT.value & ~fIsRightRing);
    }

bool CLOTRecord::IsLeftRing()
    {
    return (BMDT.value & fIsLeftRing) != 0;
    }

void CLOTRecord::IsLeftRing(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsLeftRing) : (BMDT.value & ~fIsLeftRing);
    }

bool CLOTRecord::IsAmulet()
    {
    return (BMDT.value & fIsAmulet) != 0;
    }

void CLOTRecord::IsAmulet(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsAmulet) : (BMDT.value & ~fIsAmulet);
    }

bool CLOTRecord::IsWeapon()
    {
    return (BMDT.value & fIsWeapon) != 0;
    }

void CLOTRecord::IsWeapon(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsWeapon) : (BMDT.value & ~fIsWeapon);
    }

bool CLOTRecord::IsBackWeapon()
    {
    return (BMDT.value & fIsBackWeapon) != 0;
    }

void CLOTRecord::IsBackWeapon(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsBackWeapon) : (BMDT.value & ~fIsBackWeapon);
    }

bool CLOTRecord::IsSideWeapon()
    {
    return (BMDT.value & fIsSideWeapon) != 0;
    }

void CLOTRecord::IsSideWeapon(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsSideWeapon) : (BMDT.value & ~fIsSideWeapon);
    }

bool CLOTRecord::IsQuiver()
    {
    return (BMDT.value & fIsQuiver) != 0;
    }

void CLOTRecord::IsQuiver(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsQuiver) : (BMDT.value & ~fIsQuiver);
    }

bool CLOTRecord::IsShield()
    {
    return (BMDT.value & fIsShield) != 0;
    }

void CLOTRecord::IsShield(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsShield) : (BMDT.value & ~fIsShield);
    }

bool CLOTRecord::IsTorch()
    {
    return (BMDT.value & fIsTorch) != 0;
    }

void CLOTRecord::IsTorch(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsTorch) : (BMDT.value & ~fIsTorch);
    }

bool CLOTRecord::IsTail()
    {
    return (BMDT.value & fIsTail) != 0;
    }

void CLOTRecord::IsTail(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsTail) : (BMDT.value & ~fIsTail);
    }

bool CLOTRecord::IsHideRings()
    {
    return (BMDT.value & fIsHideRings) != 0;
    }

void CLOTRecord::IsHideRings(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHideRings) : (BMDT.value & ~fIsHideRings);
    }

bool CLOTRecord::IsHideAmulets()
    {
    return (BMDT.value & fIsHideAmulets) != 0;
    }

void CLOTRecord::IsHideAmulets(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHideAmulets) : (BMDT.value & ~fIsHideAmulets);
    }

bool CLOTRecord::IsNonPlayable()
    {
    return (BMDT.value & fIsNonPlayable) != 0;
    }

void CLOTRecord::IsNonPlayable(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsNonPlayable) : (BMDT.value & ~fIsNonPlayable);
    }

bool CLOTRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((BMDT.value & Mask) == Mask) : ((BMDT.value & Mask) != 0);
    }

void CLOTRecord::SetFlagMask(UINT32 Mask)
    {
    BMDT.value = Mask;
    }

UINT32 CLOTRecord::GetType()
    {
    return REV32(CLOT);
    }

STRING CLOTRecord::GetStrType()
    {
    return "CLOT";
    }

SINT32 CLOTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(BMDT):
                BMDT.Read(buffer, subSize);
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
            case REV32(MOD2):
                MOD2.Load();
                MOD2->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO2B):
                MOD2.Load();
                MOD2->MODB.Read(buffer, subSize);
                break;
            case REV32(MO2T):
                MOD2.Load();
                MOD2->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD3):
                MOD3.Load();
                MOD3->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO3B):
                MOD3.Load();
                MOD3->MODB.Read(buffer, subSize);
                break;
            case REV32(MO3T):
                MOD3.Load();
                MOD3->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD4):
                MOD4.Load();
                MOD4->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO4B):
                MOD4.Load();
                MOD4->MODB.Read(buffer, subSize);
                break;
            case REV32(MO4T):
                MOD4.Load();
                MOD4->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICO2):
                ICO2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CLOT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 CLOTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    SCRI.Unload();
    ENAM.Unload();
    ANAM.Unload();
    BMDT.Unload();
    MODL.Unload();
    MOD2.Unload();
    ICON.Unload();
    MOD3.Unload();
    MOD4.Unload();
    ICO2.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 CLOTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(SCRI);
    WRITE(ENAM);
    WRITE(ANAM);
    WRITE(BMDT);
    MODL.Write(writer);
    if(MOD2.IsLoaded())
        {
        MOD2->WRITEAS(MODL,MOD2);
        MOD2->WRITEAS(MODB,MO2B);
        MOD2->WRITEAS(MODT,MO2T);
        }
    WRITE(ICON);
    if(MOD3.IsLoaded())
        {
        MOD3->WRITEAS(MODL,MOD3);
        MOD3->WRITEAS(MODB,MO3B);
        MOD3->WRITEAS(MODT,MO3T);
        }
    if(MOD4.IsLoaded())
        {
        MOD4->WRITEAS(MODL,MOD4);
        MOD4->WRITEAS(MODB,MO4B);
        MOD4->WRITEAS(MODT,MO4T);
        }
    WRITE(ICO2);
    WRITE(DATA);
    return -1;
    }

bool CLOTRecord::operator ==(const CLOTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            SCRI == other.SCRI &&
            ENAM == other.ENAM &&
            ANAM == other.ANAM &&
            BMDT == other.BMDT &&
            MODL == other.MODL &&
            MOD2 == other.MOD2 &&
            ICON.equalsi(other.ICON) &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4 &&
            ICO2.equalsi(other.ICO2) &&
            DATA == other.DATA);
    }

bool CLOTRecord::operator !=(const CLOTRecord &other) const
    {
    return !(*this == other);
    }

bool CLOTRecord::equals(Record *other)
    {
    return *this == *(CLOTRecord *)other;
    }
}