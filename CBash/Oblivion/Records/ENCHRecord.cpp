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
#include "ENCHRecord.h"

namespace Ob
{
ENCHRecord::ENCHENIT::ENCHENIT():
    itemType(0),
    chargeAmount(0),
    enchantCost(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

ENCHRecord::ENCHENIT::~ENCHENIT()
    {
    //
    }

bool ENCHRecord::ENCHENIT::operator ==(const ENCHENIT &other) const
    {
    return (itemType == other.itemType &&
            chargeAmount == other.chargeAmount &&
            enchantCost == other.enchantCost &&
            flags == other.flags);
    }

bool ENCHRecord::ENCHENIT::operator !=(const ENCHENIT &other) const
    {
    return !(*this == other);
    }

ENCHRecord::ENCHRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ENCHRecord::ENCHRecord(ENCHRecord *srcRecord):
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
    ENIT = srcRecord->ENIT;
    Effects = srcRecord->Effects;
    OBME = srcRecord->OBME;
    return;
    }

ENCHRecord::~ENCHRecord()
    {
    //
    }

bool ENCHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < Effects.value.size(); ListIndex++)
        Effects.value[ListIndex]->VisitFormIDs(op);

    return op.Stop();
    }

bool ENCHRecord::IsNoAutoCalc()
    {
    return (ENIT.value.flags & fIsNoAutoCalc) != 0;
    }

void ENCHRecord::IsNoAutoCalc(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsNoAutoCalc) : (ENIT.value.flags & ~fIsNoAutoCalc);
    }

bool ENCHRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((ENIT.value.flags & Mask) == Mask) : ((ENIT.value.flags & Mask) != 0);
    }

void ENCHRecord::SetFlagMask(UINT8 Mask)
    {
    ENIT.value.flags = Mask;
    }

bool ENCHRecord::IsScroll()
    {
    return (ENIT.value.itemType == eScroll);
    }

void ENCHRecord::IsScroll(bool value)
    {
    ENIT.value.itemType = value ? eScroll : eStaff;
    }

bool ENCHRecord::IsStaff()
    {
    return (ENIT.value.itemType == eStaff);
    }

void ENCHRecord::IsStaff(bool value)
    {
    ENIT.value.itemType = value ? eStaff : eScroll;
    }

bool ENCHRecord::IsWeapon()
    {
    return (ENIT.value.itemType == eWeapon);
    }

void ENCHRecord::IsWeapon(bool value)
    {
    ENIT.value.itemType = value ? eWeapon : eScroll;
    }

bool ENCHRecord::IsApparel()
    {
    return (ENIT.value.itemType == eApparel);
    }

void ENCHRecord::IsApparel(bool value)
    {
    ENIT.value.itemType = value ? eApparel : eScroll;
    }

bool ENCHRecord::IsType(UINT32 Type)
    {
    return (ENIT.value.itemType == Type);
    }

void ENCHRecord::SetType(UINT32 Type)
    {
    ENIT.value.itemType = Type;
    }

UINT32 ENCHRecord::GetType()
    {
    return REV32(ENCH);
    }

STRING ENCHRecord::GetStrType()
    {
    return "ENCH";
    }

SINT32 ENCHRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    bool bNoOBME = true;
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
            case REV32(OBME):
                OBME.Load();
                OBME->OBME.Read(buffer, subSize);
                break;
            case REV32(FULL):
                if(Effects.value.size() == 0)
                    FULL.Read(buffer, subSize, CompressedOnDisk);
                else
                    Effects.value.back()->FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ENIT):
                ENIT.Read(buffer, subSize);
                break;
            case REV32(EFME):
                bNoOBME = false;
                Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFME.Read(buffer, subSize);
                break;
            case REV32(EFID):
                if(bNoOBME || Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFID.Read(buffer, subSize);
                bNoOBME = true;
                break;
            case REV32(EFIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFIT.Read(buffer, subSize);
                break;
            case REV32(SCIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->SCIT.Read(buffer, subSize);
                break;
            case REV32(EFII):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFII.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(EFIX):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFIX.Read(buffer, subSize);
                break;
            case REV32(EFXX):
                buffer += subSize;
                break;
            case REV32(DATX):
                OBME.Load();
                OBME->DATX.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ENCH: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 ENCHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    ENIT.Unload();
    Effects.Unload();
    OBME.Unload();
    return 1;
    }

SINT32 ENCHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    if(OBME.IsLoaded())
        OBME->WRITE(OBME);
    WRITE(FULL);
    WRITE(ENIT);
    Effects.Write(writer);
    if(OBME.IsLoaded())
        {
        if(Effects.value.size())
            WRITEEMPTY(EFXX);
        if(OBME->DATX.IsLoaded())
            OBME->WRITE(DATX);
        }
    return -1;
    }

bool ENCHRecord::operator ==(const ENCHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ENIT == other.ENIT &&
            OBME == other.OBME &&
            Effects == other.Effects);
    }

bool ENCHRecord::operator !=(const ENCHRecord &other) const
    {
    return !(*this == other);
    }

bool ENCHRecord::equals(Record *other)
    {
    return *this == *(ENCHRecord *)other;
    }
}