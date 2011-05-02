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
#include "LTEXRecord.h"

namespace FNV
{
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

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
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
        op.Accept(TNAM->value);
    if(GNAM.IsLoaded())
        op.Accept(GNAM->value);

    return op.Stop();
    }

bool LTEXRecord::IsStone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStone);
    }

void LTEXRecord::IsStone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStone : eDummyDefault;
    }

bool LTEXRecord::IsCloth()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCloth);
    }

void LTEXRecord::IsCloth(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCloth : eDummyDefault;
    }

bool LTEXRecord::IsDirt()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDirt);
    }

void LTEXRecord::IsDirt(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDirt : eDummyDefault;
    }

bool LTEXRecord::IsGlass()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGlass);
    }

void LTEXRecord::IsGlass(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGlass : eDummyDefault;
    }

bool LTEXRecord::IsGrass()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGrass);
    }

void LTEXRecord::IsGrass(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGrass : eDummyDefault;
    }

bool LTEXRecord::IsMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMetal);
    }

void LTEXRecord::IsMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMetal : eDummyDefault;
    }

bool LTEXRecord::IsOrganic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOrganic);
    }

void LTEXRecord::IsOrganic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eOrganic : eDummyDefault;
    }

bool LTEXRecord::IsSkin()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSkin);
    }

void LTEXRecord::IsSkin(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSkin : eDummyDefault;
    }

bool LTEXRecord::IsWater()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWater);
    }

void LTEXRecord::IsWater(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWater : eDummyDefault;
    }

bool LTEXRecord::IsWood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWood);
    }

void LTEXRecord::IsWood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eWood : eDummyDefault;
    }

bool LTEXRecord::IsHeavyStone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHeavyStone);
    }

void LTEXRecord::IsHeavyStone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHeavyStone : eDummyDefault;
    }

bool LTEXRecord::IsHeavyMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHeavyMetal);
    }

void LTEXRecord::IsHeavyMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHeavyMetal : eDummyDefault;
    }

bool LTEXRecord::IsHeavyWood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHeavyWood);
    }

void LTEXRecord::IsHeavyWood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHeavyWood : eDummyDefault;
    }

bool LTEXRecord::IsChain()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eChain);
    }

void LTEXRecord::IsChain(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eChain : eDummyDefault;
    }

bool LTEXRecord::IsSnow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSnow);
    }

void LTEXRecord::IsSnow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSnow : eDummyDefault;
    }

bool LTEXRecord::IsElevator()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eElevator);
    }

void LTEXRecord::IsElevator(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eElevator : eDummyDefault;
    }

bool LTEXRecord::IsHollowMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHollowMetal);
    }

void LTEXRecord::IsHollowMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHollowMetal : eDummyDefault;
    }

bool LTEXRecord::IsSheetMetal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSheetMetal);
    }

void LTEXRecord::IsSheetMetal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSheetMetal : eDummyDefault;
    }

bool LTEXRecord::IsSand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSand);
    }

void LTEXRecord::IsSand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSand : eDummyDefault;
    }

bool LTEXRecord::IsBrokenConcrete()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBrokenConcrete);
    }

void LTEXRecord::IsBrokenConcrete(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBrokenConcrete : eDummyDefault;
    }

bool LTEXRecord::IsVehicleBody()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVehicleBody);
    }

void LTEXRecord::IsVehicleBody(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVehicleBody : eDummyDefault;
    }

bool LTEXRecord::IsVehiclePartSolid()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVehiclePartSolid);
    }

void LTEXRecord::IsVehiclePartSolid(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVehiclePartSolid : eDummyDefault;
    }

bool LTEXRecord::IsVehiclePartHollow()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVehiclePartHollow);
    }

void LTEXRecord::IsVehiclePartHollow(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVehiclePartHollow : eDummyDefault;
    }

bool LTEXRecord::IsBarrel()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBarrel);
    }

void LTEXRecord::IsBarrel(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBarrel : eDummyDefault;
    }

bool LTEXRecord::IsBottle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBottle);
    }

void LTEXRecord::IsBottle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBottle : eDummyDefault;
    }

bool LTEXRecord::IsSodaCan()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSodaCan);
    }

void LTEXRecord::IsSodaCan(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSodaCan : eDummyDefault;
    }

bool LTEXRecord::IsPistol()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePistol);
    }

void LTEXRecord::IsPistol(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePistol : eDummyDefault;
    }

bool LTEXRecord::IsRifle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRifle);
    }

void LTEXRecord::IsRifle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRifle : eDummyDefault;
    }

bool LTEXRecord::IsShoppingCart()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eShoppingCart);
    }

void LTEXRecord::IsShoppingCart(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eShoppingCart : eDummyDefault;
    }

bool LTEXRecord::IsLunchBox()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLunchBox);
    }

void LTEXRecord::IsLunchBox(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLunchBox : eDummyDefault;
    }

bool LTEXRecord::IsBabyRattle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBabyRattle);
    }

void LTEXRecord::IsBabyRattle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBabyRattle : eDummyDefault;
    }

bool LTEXRecord::IsRubberBall()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRubberBall);
    }

void LTEXRecord::IsRubberBall(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRubberBall : eDummyDefault;
    }

bool LTEXRecord::Is0Type(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void LTEXRecord::Set0Type(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 LTEXRecord::GetType()
    {
    return 'XETL';
    }

STRING LTEXRecord::GetStrType()
    {
    return "LTEX";
    }

SINT32 LTEXRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANG':
                GNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LTEX: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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

SINT32 LTEXRecord::WriteRecord(_FileHandler &SaveHandler)
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
}