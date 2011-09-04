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

namespace FNV
{

LTEXRecord::LTEXHNAM::LTEXHNAM():
    types(0),
    friction(0),
    restitution(0)
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
    FNVRecord(_recData)
    {
    //
    }

LTEXRecord::LTEXRecord(LTEXRecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    TNAM = srcRecord->TNAM;
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

    if(TNAM.IsLoaded())
        op.Accept(TNAM.value);
    for(UINT32 x = 0; x < GNAM.value.size(); ++x)
        op.Accept(GNAM.value[x]);

    return op.Stop();
    }

bool LTEXRecord::IsStone()
    {
    return (HNAM.value.types == eStone);
    }

void LTEXRecord::IsStone(bool value)
    {
    HNAM.value.types = value ? eStone : eCloth;
    }

bool LTEXRecord::IsCloth()
    {
    return (HNAM.value.types == eCloth);
    }

void LTEXRecord::IsCloth(bool value)
    {
    HNAM.value.types = value ? eCloth : eStone;
    }

bool LTEXRecord::IsDirt()
    {
    return (HNAM.value.types == eDirt);
    }

void LTEXRecord::IsDirt(bool value)
    {
    HNAM.value.types = value ? eDirt : eStone;
    }

bool LTEXRecord::IsGlass()
    {
    return (HNAM.value.types == eGlass);
    }

void LTEXRecord::IsGlass(bool value)
    {
    HNAM.value.types = value ? eGlass : eStone;
    }

bool LTEXRecord::IsGrass()
    {
    return (HNAM.value.types == eGrass);
    }

void LTEXRecord::IsGrass(bool value)
    {
    HNAM.value.types = value ? eGrass : eStone;
    }

bool LTEXRecord::IsMetal()
    {
    return (HNAM.value.types == eMetal);
    }

void LTEXRecord::IsMetal(bool value)
    {
    HNAM.value.types = value ? eMetal : eStone;
    }

bool LTEXRecord::IsOrganic()
    {
    return (HNAM.value.types == eOrganic);
    }

void LTEXRecord::IsOrganic(bool value)
    {
    HNAM.value.types = value ? eOrganic : eStone;
    }

bool LTEXRecord::IsSkin()
    {
    return (HNAM.value.types == eSkin);
    }

void LTEXRecord::IsSkin(bool value)
    {
    HNAM.value.types = value ? eSkin : eStone;
    }

bool LTEXRecord::IsWater()
    {
    return (HNAM.value.types == eWater);
    }

void LTEXRecord::IsWater(bool value)
    {
    HNAM.value.types = value ? eWater : eStone;
    }

bool LTEXRecord::IsWood()
    {
    return (HNAM.value.types == eWood);
    }

void LTEXRecord::IsWood(bool value)
    {
    HNAM.value.types = value ? eWood : eStone;
    }

bool LTEXRecord::IsHeavyStone()
    {
    return (HNAM.value.types == eHeavyStone);
    }

void LTEXRecord::IsHeavyStone(bool value)
    {
    HNAM.value.types = value ? eHeavyStone : eStone;
    }

bool LTEXRecord::IsHeavyMetal()
    {
    return (HNAM.value.types == eHeavyMetal);
    }

void LTEXRecord::IsHeavyMetal(bool value)
    {
    HNAM.value.types = value ? eHeavyMetal : eStone;
    }

bool LTEXRecord::IsHeavyWood()
    {
    return (HNAM.value.types == eHeavyWood);
    }

void LTEXRecord::IsHeavyWood(bool value)
    {
    HNAM.value.types = value ? eHeavyWood : eStone;
    }

bool LTEXRecord::IsChain()
    {
    return (HNAM.value.types == eChain);
    }

void LTEXRecord::IsChain(bool value)
    {
    HNAM.value.types = value ? eChain : eStone;
    }

bool LTEXRecord::IsSnow()
    {
    return (HNAM.value.types == eSnow);
    }

void LTEXRecord::IsSnow(bool value)
    {
    HNAM.value.types = value ? eSnow : eStone;
    }

bool LTEXRecord::IsElevator()
    {
    return (HNAM.value.types == eElevator);
    }

void LTEXRecord::IsElevator(bool value)
    {
    HNAM.value.types = value ? eElevator : eStone;
    }

bool LTEXRecord::IsHollowMetal()
    {
    return (HNAM.value.types == eHollowMetal);
    }

void LTEXRecord::IsHollowMetal(bool value)
    {
    HNAM.value.types = value ? eHollowMetal : eStone;
    }

bool LTEXRecord::IsSheetMetal()
    {
    return (HNAM.value.types == eSheetMetal);
    }

void LTEXRecord::IsSheetMetal(bool value)
    {
    HNAM.value.types = value ? eSheetMetal : eStone;
    }

bool LTEXRecord::IsSand()
    {
    return (HNAM.value.types == eSand);
    }

void LTEXRecord::IsSand(bool value)
    {
    HNAM.value.types = value ? eSand : eStone;
    }

bool LTEXRecord::IsBrokenConcrete()
    {
    return (HNAM.value.types == eBrokenConcrete);
    }

void LTEXRecord::IsBrokenConcrete(bool value)
    {
    HNAM.value.types = value ? eBrokenConcrete : eStone;
    }

bool LTEXRecord::IsVehicleBody()
    {
    return (HNAM.value.types == eVehicleBody);
    }

void LTEXRecord::IsVehicleBody(bool value)
    {
    HNAM.value.types = value ? eVehicleBody : eStone;
    }

bool LTEXRecord::IsVehiclePartSolid()
    {
    return (HNAM.value.types == eVehiclePartSolid);
    }

void LTEXRecord::IsVehiclePartSolid(bool value)
    {
    HNAM.value.types = value ? eVehiclePartSolid : eStone;
    }

bool LTEXRecord::IsVehiclePartHollow()
    {
    return (HNAM.value.types == eVehiclePartHollow);
    }

void LTEXRecord::IsVehiclePartHollow(bool value)
    {
    HNAM.value.types = value ? eVehiclePartHollow : eStone;
    }

bool LTEXRecord::IsBarrel()
    {
    return (HNAM.value.types == eBarrel);
    }

void LTEXRecord::IsBarrel(bool value)
    {
    HNAM.value.types = value ? eBarrel : eStone;
    }

bool LTEXRecord::IsBottle()
    {
    return (HNAM.value.types == eBottle);
    }

void LTEXRecord::IsBottle(bool value)
    {
    HNAM.value.types = value ? eBottle : eStone;
    }

bool LTEXRecord::IsSodaCan()
    {
    return (HNAM.value.types == eSodaCan);
    }

void LTEXRecord::IsSodaCan(bool value)
    {
    HNAM.value.types = value ? eSodaCan : eStone;
    }

bool LTEXRecord::IsPistol()
    {
    return (HNAM.value.types == ePistol);
    }

void LTEXRecord::IsPistol(bool value)
    {
    HNAM.value.types = value ? ePistol : eStone;
    }

bool LTEXRecord::IsRifle()
    {
    return (HNAM.value.types == eRifle);
    }

void LTEXRecord::IsRifle(bool value)
    {
    HNAM.value.types = value ? eRifle : eStone;
    }

bool LTEXRecord::IsShoppingCart()
    {
    return (HNAM.value.types == eShoppingCart);
    }

void LTEXRecord::IsShoppingCart(bool value)
    {
    HNAM.value.types = value ? eShoppingCart : eStone;
    }

bool LTEXRecord::IsLunchBox()
    {
    return (HNAM.value.types == eLunchBox);
    }

void LTEXRecord::IsLunchBox(bool value)
    {
    HNAM.value.types = value ? eLunchBox : eStone;
    }

bool LTEXRecord::IsBabyRattle()
    {
    return (HNAM.value.types == eBabyRattle);
    }

void LTEXRecord::IsBabyRattle(bool value)
    {
    HNAM.value.types = value ? eBabyRattle : eStone;
    }

bool LTEXRecord::IsRubberBall()
    {
    return (HNAM.value.types == eRubberBall);
    }

void LTEXRecord::IsRubberBall(bool value)
    {
    HNAM.value.types = value ? eRubberBall : eStone;
    }

bool LTEXRecord::IsType(UINT8 Type)
    {
    return HNAM.value.types == Type;
    }

void LTEXRecord::SetType(UINT8 Type)
    {
    HNAM.value.types = Type;
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
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
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
    MICO.Unload();
    TNAM.Unload();
    HNAM.Unload();
    SNAM.Unload();
    GNAM.Unload();
    return 1;
    }

SINT32 LTEXRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(TNAM);
    WRITE(HNAM);
    WRITE(SNAM);
    WRITE(GNAM);
    return -1;
    }

bool LTEXRecord::operator ==(const LTEXRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            TNAM == other.TNAM &&
            HNAM == other.HNAM &&
            SNAM == other.SNAM &&
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