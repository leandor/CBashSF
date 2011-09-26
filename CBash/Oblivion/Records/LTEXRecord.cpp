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
#include "LTEXRecord.h"

namespace Ob
{
LTEXRecord::LTEXHNAM::LTEXHNAM():
    types(2),
    friction(30),
    restitution(30)
    {
    //
    }

LTEXRecord::LTEXHNAM::~LTEXHNAM()
    {
    //
    }

bool LTEXRecord::LTEXHNAM::operator ==(const LTEXHNAM &other) const
    {
    return (types == other.types &&
            friction == other.friction &&
            restitution == other.restitution);
    }
bool LTEXRecord::LTEXHNAM::operator !=(const LTEXHNAM &other) const
    {
    return !(*this == other);
    }

LTEXRecord::LTEXRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LTEXRecord::LTEXRecord(LTEXRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    HNAM = srcRecord->HNAM;
    SNAM = srcRecord->SNAM;
    GNAM = srcRecord->GNAM;
    return;
    }

LTEXRecord::~LTEXRecord()
    {
    //
    }

bool LTEXRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < GNAM.value.size(); ListIndex++)
        op.Accept(GNAM.value[ListIndex]);

    return op.Stop();
    }

bool LTEXRecord::IsStone()
    {
    HNAM.Load();
    return (HNAM->types == eStone);
    }

void LTEXRecord::IsStone(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eStone : eCloth;
    }

bool LTEXRecord::IsCloth()
    {
    HNAM.Load();
    return (HNAM->types == eCloth);
    }

void LTEXRecord::IsCloth(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eCloth : eDirt;
    }

bool LTEXRecord::IsDirt()
    {
    HNAM.Load();
    return (HNAM->types == eDirt);
    }

void LTEXRecord::IsDirt(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eDirt : eDirt;
    }

bool LTEXRecord::IsGlass()
    {
    HNAM.Load();
    return (HNAM->types == eGlass);
    }

void LTEXRecord::IsGlass(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eGlass : eDirt;
    }

bool LTEXRecord::IsGrass()
    {
    HNAM.Load();
    return (HNAM->types == eGrass);
    }

void LTEXRecord::IsGrass(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eGrass : eDirt;
    }

bool LTEXRecord::IsMetal()
    {
    HNAM.Load();
    return (HNAM->types == eMetal);
    }

void LTEXRecord::IsMetal(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eMetal : eDirt;
    }

bool LTEXRecord::IsOrganic()
    {
    HNAM.Load();
    return (HNAM->types == eOrganic);
    }

void LTEXRecord::IsOrganic(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eOrganic : eDirt;
    }

bool LTEXRecord::IsSkin()
    {
    HNAM.Load();
    return (HNAM->types == eSkin);
    }

void LTEXRecord::IsSkin(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eSkin : eDirt;
    }

bool LTEXRecord::IsWater()
    {
    HNAM.Load();
    return (HNAM->types == eWater);
    }

void LTEXRecord::IsWater(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eWater : eDirt;
    }

bool LTEXRecord::IsWood()
    {
    HNAM.Load();
    return (HNAM->types == eWood);
    }

void LTEXRecord::IsWood(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eWood : eDirt;
    }

bool LTEXRecord::IsHeavyStone()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyStone);
    }

void LTEXRecord::IsHeavyStone(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyStone : eDirt;
    }

bool LTEXRecord::IsHeavyMetal()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyMetal);
    }

void LTEXRecord::IsHeavyMetal(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyMetal : eDirt;
    }

bool LTEXRecord::IsHeavyWood()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyWood);
    }

void LTEXRecord::IsHeavyWood(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyWood : eDirt;
    }

bool LTEXRecord::IsChain()
    {
    HNAM.Load();
    return (HNAM->types == eChain);
    }

void LTEXRecord::IsChain(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eChain : eDirt;
    }

bool LTEXRecord::IsSnow()
    {
    HNAM.Load();
    return (HNAM->types == eSnow);
    }

void LTEXRecord::IsSnow(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eSnow : eDirt;
    }
bool LTEXRecord::IsStoneStairs()
    {
    HNAM.Load();
    return (HNAM->types == eStoneStairs);
    }

void LTEXRecord::IsStoneStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eStoneStairs : eDirt;
    }

bool LTEXRecord::IsClothStairs()
    {
    HNAM.Load();
    return (HNAM->types == eClothStairs);
    }

void LTEXRecord::IsClothStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eClothStairs : eDirt;
    }

bool LTEXRecord::IsDirtStairs()
    {
    HNAM.Load();
    return (HNAM->types == eDirtStairs);
    }

void LTEXRecord::IsDirtStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eDirtStairs : eDirt;
    }

bool LTEXRecord::IsGlassStairs()
    {
    HNAM.Load();
    return (HNAM->types == eGlassStairs);
    }

void LTEXRecord::IsGlassStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eGlassStairs : eDirt;
    }

bool LTEXRecord::IsGrassStairs()
    {
    HNAM.Load();
    return (HNAM->types == eGrassStairs);
    }

void LTEXRecord::IsGrassStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eGrassStairs : eDirt;
    }

bool LTEXRecord::IsMetalStairs()
    {
    HNAM.Load();
    return (HNAM->types == eMetalStairs);
    }

void LTEXRecord::IsMetalStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eMetalStairs : eDirt;
    }

bool LTEXRecord::IsOrganicStairs()
    {
    HNAM.Load();
    return (HNAM->types == eOrganicStairs);
    }

void LTEXRecord::IsOrganicStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eOrganicStairs : eDirt;
    }

bool LTEXRecord::IsSkinStairs()
    {
    HNAM.Load();
    return (HNAM->types == eSkinStairs);
    }

void LTEXRecord::IsSkinStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eSkinStairs : eDirt;
    }

bool LTEXRecord::IsWaterStairs()
    {
    HNAM.Load();
    return (HNAM->types == eWaterStairs);
    }

void LTEXRecord::IsWaterStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eWaterStairs : eDirt;
    }

bool LTEXRecord::IsWoodStairs()
    {
    HNAM.Load();
    return (HNAM->types == eWoodStairs);
    }

void LTEXRecord::IsWoodStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eWoodStairs : eDirt;
    }

bool LTEXRecord::IsHeavyStoneStairs()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyStoneStairs);
    }

void LTEXRecord::IsHeavyStoneStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyStoneStairs : eDirt;
    }

bool LTEXRecord::IsHeavyMetalStairs()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyMetalStairs);
    }

void LTEXRecord::IsHeavyMetalStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyMetalStairs : eDirt;
    }

bool LTEXRecord::IsHeavyWoodStairs()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyWoodStairs);
    }

void LTEXRecord::IsHeavyWoodStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyWoodStairs : eDirt;
    }

bool LTEXRecord::IsChainStairs()
    {
    HNAM.Load();
    return (HNAM->types == eChainStairs);
    }

void LTEXRecord::IsChainStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eChainStairs : eDirt;
    }

bool LTEXRecord::IsSnowStairs()
    {
    HNAM.Load();
    return (HNAM->types == eSnowStairs);
    }

void LTEXRecord::IsSnowStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eSnowStairs : eDirt;
    }

bool LTEXRecord::IsElevator()
    {
    HNAM.Load();
    return (HNAM->types == eElevator);
    }

void LTEXRecord::IsElevator(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eElevator : eDirt;
    }

bool LTEXRecord::IsType(UINT8 Type)
    {
    HNAM.Load();
    return (HNAM->types == Type);
    }

void LTEXRecord::SetType(UINT8 Type)
    {
    HNAM.Load();
    HNAM->types = Type;
    }

UINT32 LTEXRecord::GetType()
    {
    return REV32(LTEX);
    }

STRING LTEXRecord::GetStrType()
    {
    return "LTEX";
    }

SINT32 LTEXRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LTEX: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 LTEXRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    HNAM.Unload();
    SNAM.Unload();
    GNAM.Unload();
    return 1;
    }

SINT32 LTEXRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(HNAM);
    WRITE(SNAM);
    WRITE(GNAM);
    return -1;
    }

bool LTEXRecord::operator ==(const LTEXRecord &other) const
    {
    return (HNAM == other.HNAM &&
            SNAM == other.SNAM &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            GNAM == other.GNAM);
    }

bool LTEXRecord::operator !=(const LTEXRecord &other) const
    {
    return !(*this == other);
    }

bool LTEXRecord::equals(Record *other)
    {
    return *this == *(LTEXRecord *)other;
    }
}