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
#include "ENCHRecord.h"

namespace FNV
{

ENCHRecord::ENCHENIT::ENCHENIT():
    itemType(0),
    chargeAmount(0),
    enchantCost(0),
    flags(0)
    {
    memset(&unused1, 0x00, 3);
    }

ENCHRecord::ENCHENIT::~ENCHENIT()
    {
    //
    }

bool ENCHRecord::ENCHENIT::operator ==(const ENCHENIT &other) const
    {
    return (itemType == other.itemType &&
            //chargeAmount == other.chargeAmount && //unused in FNV
            //enchantCost == other.enchantCost && //unused in FNV
            flags == other.flags);
    }

bool ENCHRecord::ENCHENIT::operator !=(const ENCHENIT &other) const
    {
    return !(*this == other);
    }

ENCHRecord::ENCHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ENCHRecord::ENCHRecord(ENCHRecord *srcRecord):
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
    ENIT = srcRecord->ENIT;
    Effects = srcRecord->Effects;
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

    for(UINT32 x = 0; x < Effects.value.size(); x++)
        Effects.value[x]->VisitFormIDs(op);

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

bool ENCHRecord::IsHideEffect()
    {
    return (ENIT.value.flags & fIsHideEffect) != 0;
    }

void ENCHRecord::IsHideEffect(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsHideEffect) : (ENIT.value.flags & ~fIsHideEffect);
    }

bool ENCHRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((ENIT.value.flags & Mask) == Mask) : ((ENIT.value.flags & Mask) != 0);
    }

void ENCHRecord::SetFlagMask(UINT8 Mask)
    {
    ENIT.value.flags = Mask;
    }

bool ENCHRecord::IsWeapon()
    {
    return (ENIT.value.itemType == eWeapon);
    }

void ENCHRecord::IsWeapon(bool value)
    {
    ENIT.value.itemType = value ? eWeapon : eApparel;
    }

bool ENCHRecord::IsApparel()
    {
    return (ENIT.value.itemType == eApparel);
    }

void ENCHRecord::IsApparel(bool value)
    {
    ENIT.value.itemType = value ? eApparel : eWeapon;
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

SINT32 ENCHRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(ENIT):
                ENIT.Read(buffer, subSize, curPos);
                break;
            case REV32(EFID):
                Effects.value.push_back(new FNVEffect);
                Effects.value.back()->EFID.Read(buffer, subSize, curPos);
                break;
            case REV32(EFIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new FNVEffect);
                Effects.value.back()->EFIT.Read(buffer, subSize, curPos);
                break;
            case REV32(CTDA):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new FNVEffect);
                Effects.value.back()->CTDA.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ENCH: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    return 1;
    }

SINT32 ENCHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(ENIT);
    Effects.Write(writer);
    return -1;
    }

bool ENCHRecord::operator ==(const ENCHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ENIT == other.ENIT &&
            Effects == other.Effects);
    }

bool ENCHRecord::operator !=(const ENCHRecord &other) const
    {
    return !(*this == other);
    }
}