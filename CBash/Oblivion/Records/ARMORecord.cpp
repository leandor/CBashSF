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
#include "ARMORecord.h"

ARMORecord::ARMODATA::ARMODATA():
    strength(0),
    value(0),
    health(0),
    weight(0.0f)
    {
    //
    }

ARMORecord::ARMODATA::~ARMODATA()
    {
    //
    }

bool ARMORecord::ARMODATA::operator ==(const ARMODATA &other) const
    {
    return (strength == other.strength &&
            value == other.value &&
            health == other.health &&
            AlmostEqual(weight,other.weight,2));
    }

bool ARMORecord::ARMODATA::operator !=(const ARMODATA &other) const
    {
    return !(*this == other);
    }

ARMORecord::ARMORecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ARMORecord::ARMORecord(ARMORecord *srcRecord):
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
    FULL = srcRecord->FULL;
    SCRI = srcRecord->SCRI;
    ENAM = srcRecord->ENAM;
    ANAM = srcRecord->ANAM;
    BMDT = srcRecord->BMDT;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODT = srcRecord->MODL->MODT;
        }
    if(srcRecord->MOD2.IsLoaded())
        {
        MOD2.Load();
        MOD2->MODB = srcRecord->MOD2->MODB;
        MOD2->MODL = srcRecord->MOD2->MODL;
        MOD2->MODT = srcRecord->MOD2->MODT;
        }
    ICON = srcRecord->ICON;
    if(srcRecord->MOD3.IsLoaded())
        {
        MOD3.Load();
        MOD3->MODB = srcRecord->MOD3->MODB;
        MOD3->MODL = srcRecord->MOD3->MODL;
        MOD3->MODT = srcRecord->MOD3->MODT;
        }
    if(srcRecord->MOD4.IsLoaded())
        {
        MOD4.Load();
        MOD4->MODB = srcRecord->MOD4->MODB;
        MOD4->MODL = srcRecord->MOD4->MODL;
        MOD4->MODT = srcRecord->MOD4->MODT;
        }
    ICO2 = srcRecord->ICO2;
    DATA = srcRecord->DATA;
    return;
    }

ARMORecord::~ARMORecord()
    {
    //
    }

bool ARMORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool ARMORecord::IsHead()
    {
    return (BMDT.value & fIsHead) != 0;
    }

void ARMORecord::IsHead(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHead) : (BMDT.value & ~fIsHead);
    }

bool ARMORecord::IsHair()
    {
    return (BMDT.value & fIsHair) != 0;
    }

void ARMORecord::IsHair(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHair) : (BMDT.value & ~fIsHair);
    }

bool ARMORecord::IsUpperBody()
    {
    return (BMDT.value & fIsUpperBody) != 0;
    }

void ARMORecord::IsUpperBody(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsUpperBody) : (BMDT.value & ~fIsUpperBody);
    }

bool ARMORecord::IsLowerBody()
    {
    return (BMDT.value & fIsLowerBody) != 0;
    }

void ARMORecord::IsLowerBody(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsLowerBody) : (BMDT.value & ~fIsLowerBody);
    }

bool ARMORecord::IsHand()
    {
    return (BMDT.value & fIsHand) != 0;
    }

void ARMORecord::IsHand(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHand) : (BMDT.value & ~fIsHand);
    }

bool ARMORecord::IsFoot()
    {
    return (BMDT.value & fIsFoot) != 0;
    }

void ARMORecord::IsFoot(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsFoot) : (BMDT.value & ~fIsFoot);
    }

bool ARMORecord::IsRightRing()
    {
    return (BMDT.value & fIsRightRing) != 0;
    }

void ARMORecord::IsRightRing(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsRightRing) : (BMDT.value & ~fIsRightRing);
    }

bool ARMORecord::IsLeftRing()
    {
    return (BMDT.value & fIsLeftRing) != 0;
    }

void ARMORecord::IsLeftRing(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsLeftRing) : (BMDT.value & ~fIsLeftRing);
    }

bool ARMORecord::IsAmulet()
    {
    return (BMDT.value & fIsAmulet) != 0;
    }

void ARMORecord::IsAmulet(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsAmulet) : (BMDT.value & ~fIsAmulet);
    }

bool ARMORecord::IsWeapon()
    {
    return (BMDT.value & fIsWeapon) != 0;
    }

void ARMORecord::IsWeapon(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsWeapon) : (BMDT.value & ~fIsWeapon);
    }

bool ARMORecord::IsBackWeapon()
    {
    return (BMDT.value & fIsBackWeapon) != 0;
    }

void ARMORecord::IsBackWeapon(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsBackWeapon) : (BMDT.value & ~fIsBackWeapon);
    }

bool ARMORecord::IsSideWeapon()
    {
    return (BMDT.value & fIsSideWeapon) != 0;
    }

void ARMORecord::IsSideWeapon(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsSideWeapon) : (BMDT.value & ~fIsSideWeapon);
    }

bool ARMORecord::IsQuiver()
    {
    return (BMDT.value & fIsQuiver) != 0;
    }

void ARMORecord::IsQuiver(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsQuiver) : (BMDT.value & ~fIsQuiver);
    }

bool ARMORecord::IsShield()
    {
    return (BMDT.value & fIsShield) != 0;
    }

void ARMORecord::IsShield(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsShield) : (BMDT.value & ~fIsShield);
    }

bool ARMORecord::IsTorch()
    {
    return (BMDT.value & fIsTorch) != 0;
    }

void ARMORecord::IsTorch(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsTorch) : (BMDT.value & ~fIsTorch);
    }

bool ARMORecord::IsTail()
    {
    return (BMDT.value & fIsTail) != 0;
    }

void ARMORecord::IsTail(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsTail) : (BMDT.value & ~fIsTail);
    }

bool ARMORecord::IsHideRings()
    {
    return (BMDT.value & fIsHideRings) != 0;
    }

void ARMORecord::IsHideRings(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHideRings) : (BMDT.value & ~fIsHideRings);
    }

bool ARMORecord::IsHideAmulets()
    {
    return (BMDT.value & fIsHideAmulets) != 0;
    }

void ARMORecord::IsHideAmulets(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHideAmulets) : (BMDT.value & ~fIsHideAmulets);
    }

bool ARMORecord::IsNonPlayable()
    {
    return (BMDT.value & fIsNonPlayable) != 0;
    }

void ARMORecord::IsNonPlayable(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsNonPlayable) : (BMDT.value & ~fIsNonPlayable);
    }

bool ARMORecord::IsHeavyArmor()
    {
    return (BMDT.value & fIsHeavyArmor) != 0;
    }

void ARMORecord::IsHeavyArmor(bool value)
    {
    BMDT.value = value ? (BMDT.value | fIsHeavyArmor) : (BMDT.value & ~fIsHeavyArmor);
    }

bool ARMORecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((BMDT.value & Mask) == Mask) : ((BMDT.value & Mask) != 0);
    }

void ARMORecord::SetFlagMask(UINT32 Mask)
    {
    BMDT.value = Mask;
    }

UINT32 ARMORecord::GetType()
    {
    return 'OMRA';
    }

STRING ARMORecord::GetStrType()
    {
    return "ARMO";
    }

SINT32 ARMORecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'MANE':
                ENAM.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'TDMB':
                BMDT.Read(buffer, subSize, curPos);
                break;

            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case 'BDOM':
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case 'TDOM':
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;

            case '2DOM':
                MOD2.Load();
                MOD2->MODL.Read(buffer, subSize, curPos);
                break;
            case 'B2OM':
                MOD2.Load();
                MOD2->MODB.Read(buffer, subSize, curPos);
                break;
            case 'T2OM':
                MOD2.Load();
                MOD2->MODT.Read(buffer, subSize, curPos);
                break;

            case '3DOM':
                MOD3.Load();
                MOD3->MODL.Read(buffer, subSize, curPos);
                break;
            case 'B3OM':
                MOD3.Load();
                MOD3->MODB.Read(buffer, subSize, curPos);
                break;
            case 'T3OM':
                MOD3.Load();
                MOD3->MODT.Read(buffer, subSize, curPos);
                break;

            case '4DOM':
                MOD4.Load();
                MOD4->MODL.Read(buffer, subSize, curPos);
                break;
            case 'B4OM':
                MOD4.Load();
                MOD4->MODB.Read(buffer, subSize, curPos);
                break;
            case 'T4OM':
                MOD4.Load();
                MOD4->MODT.Read(buffer, subSize, curPos);
                break;

            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case '2OCI':
                ICO2.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ARMO: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 ARMORecord::Unload()
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

SINT32 ARMORecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord('DIDE', EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        writer.record_write_subrecord('LLUF', FULL.value, FULL.GetSize());
    if(SCRI.IsLoaded())
        writer.record_write_subrecord('IRCS', &SCRI.value, SCRI.GetSize());
    if(ENAM.IsLoaded())
        writer.record_write_subrecord('MANE', &ENAM.value, ENAM.GetSize());
    if(ANAM.IsLoaded())
        writer.record_write_subrecord('MANA', &ANAM.value, ANAM.GetSize());
    if(BMDT.IsLoaded())
        writer.record_write_subrecord('TDMB', &BMDT.value, BMDT.GetSize());

    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        writer.record_write_subrecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            writer.record_write_subrecord('BDOM', &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            writer.record_write_subrecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());
        }

    if(MOD2.IsLoaded() && MOD2->MODL.IsLoaded())
        {
        writer.record_write_subrecord('2DOM', MOD2->MODL.value, MOD2->MODL.GetSize());
        if(MOD2->MODB.IsLoaded())
            writer.record_write_subrecord('B2OM', &MOD2->MODB.value, MOD2->MODB.GetSize());
        if(MOD2->MODT.IsLoaded())
            writer.record_write_subrecord('T2OM', MOD2->MODT.value, MOD2->MODT.GetSize());
        }
    if(ICON.IsLoaded())
        writer.record_write_subrecord('NOCI', ICON.value, ICON.GetSize());

    if(MOD3.IsLoaded() && MOD3->MODL.IsLoaded())
        {
        writer.record_write_subrecord('3DOM', MOD3->MODL.value, MOD3->MODL.GetSize());
        if(MOD3->MODB.IsLoaded())
            writer.record_write_subrecord('B3OM', &MOD3->MODB.value, MOD3->MODB.GetSize());
        if(MOD3->MODT.IsLoaded())
            writer.record_write_subrecord('T3OM', MOD3->MODT.value, MOD3->MODT.GetSize());
        }

    if(MOD4.IsLoaded() && MOD4->MODL.IsLoaded())
        {
        writer.record_write_subrecord('4DOM', MOD4->MODL.value, MOD4->MODL.GetSize());
        if(MOD4->MODB.IsLoaded())
            writer.record_write_subrecord('B4OM', &MOD4->MODB.value, MOD4->MODB.GetSize());
        if(MOD4->MODT.IsLoaded())
            writer.record_write_subrecord('T4OM', MOD4->MODT.value, MOD4->MODT.GetSize());
        }
    if(ICO2.IsLoaded())
        writer.record_write_subrecord('2OCI', ICO2.value, ICO2.GetSize());

    if(DATA.IsLoaded())
        writer.record_write_subrecord('ATAD', &DATA.value, DATA.GetSize());
    return -1;
    }

bool ARMORecord::operator ==(const ARMORecord &other) const
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

bool ARMORecord::operator !=(const ARMORecord &other) const
    {
    return !(*this == other);
    }