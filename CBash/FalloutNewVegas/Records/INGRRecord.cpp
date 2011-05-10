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
#include "INGRRecord.h"

namespace FNV
{
INGRRecord::INGRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

INGRRecord::INGRRecord(INGRRecord *srcRecord):
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
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SCRI = srcRecord->SCRI;
    ETYP = srcRecord->ETYP;
    DATA = srcRecord->DATA;
    ENIT = srcRecord->ENIT;
    Effects = srcRecord->Effects;
    return;
    }

INGRRecord::~INGRRecord()
    {
    //
    }

bool INGRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(UINT32 x = 0; x < Effects.value.size(); x++)
        Effects.value[x]->VisitFormIDs(op);

    return op.Stop();
    }

bool INGRRecord::IsNoAutoCalc()
    {
    return (ENIT.value.flags & fIsNoAutoCalc) != 0;
    }

void INGRRecord::IsNoAutoCalc(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsNoAutoCalc) : (ENIT.value.flags & ~fIsNoAutoCalc);
    }

bool INGRRecord::IsFood()
    {
    return (ENIT.value.flags & fIsFood) != 0;
    }

void INGRRecord::IsFood(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsFood) : (ENIT.value.flags & ~fIsFood);
    }

bool INGRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((ENIT.value.flags & Mask) == Mask) : ((ENIT.value.flags & Mask) != 0);
    }

void INGRRecord::SetFlagMask(UINT8 Mask)
    {
    ENIT.value.flags = Mask;
    }

bool INGRRecord::IsNone()
    {
    return (ETYP.value == eNone);
    }

void INGRRecord::IsNone(bool value)
    {
    ETYP.value = value ? eNone : eBigGuns;
    }

bool INGRRecord::IsBigGuns()
    {
    return (ETYP.value == eBigGuns);
    }

void INGRRecord::IsBigGuns(bool value)
    {
    ETYP.value = value ? eBigGuns : eNone;
    }

bool INGRRecord::IsEnergyWeapons()
    {
    return (ETYP.value == eEnergyWeapons);
    }

void INGRRecord::IsEnergyWeapons(bool value)
    {
    ETYP.value = value ? eEnergyWeapons : eNone;
    }

bool INGRRecord::IsSmallGuns()
    {
    return (ETYP.value == eSmallGuns);
    }

void INGRRecord::IsSmallGuns(bool value)
    {
    ETYP.value = value ? eSmallGuns : eNone;
    }

bool INGRRecord::IsMeleeWeapons()
    {
    return (ETYP.value == eMeleeWeapons);
    }

void INGRRecord::IsMeleeWeapons(bool value)
    {
    ETYP.value = value ? eMeleeWeapons : eNone;
    }

bool INGRRecord::IsUnarmedWeapon()
    {
    return (ETYP.value == eUnarmedWeapon);
    }

void INGRRecord::IsUnarmedWeapon(bool value)
    {
    ETYP.value = value ? eUnarmedWeapon : eNone;
    }

bool INGRRecord::IsThrownWeapons()
    {
    return (ETYP.value == eThrownWeapons);
    }

void INGRRecord::IsThrownWeapons(bool value)
    {
    ETYP.value = value ? eThrownWeapons : eNone;
    }

bool INGRRecord::IsMine()
    {
    return (ETYP.value == eMine);
    }

void INGRRecord::IsMine(bool value)
    {
    ETYP.value = value ? eMine : eNone;
    }

bool INGRRecord::IsBodyWear()
    {
    return (ETYP.value == eBodyWear);
    }

void INGRRecord::IsBodyWear(bool value)
    {
    ETYP.value = value ? eBodyWear : eNone;
    }

bool INGRRecord::IsHeadWear()
    {
    return (ETYP.value == eHeadWear);
    }

void INGRRecord::IsHeadWear(bool value)
    {
    ETYP.value = value ? eHeadWear : eNone;
    }

bool INGRRecord::IsHandWear()
    {
    return (ETYP.value == eHandWear);
    }

void INGRRecord::IsHandWear(bool value)
    {
    ETYP.value = value ? eHandWear : eNone;
    }

bool INGRRecord::IsChems()
    {
    return (ETYP.value == eChems);
    }

void INGRRecord::IsChems(bool value)
    {
    ETYP.value = value ? eChems : eNone;
    }

bool INGRRecord::IsStimpack()
    {
    return (ETYP.value == eStimpack);
    }

void INGRRecord::IsStimpack(bool value)
    {
    ETYP.value = value ? eStimpack : eNone;
    }

bool INGRRecord::IsEdible()
    {
    return (ETYP.value == eEdible);
    }

void INGRRecord::IsEdible(bool value)
    {
    ETYP.value = value ? eEdible : eNone;
    }

bool INGRRecord::IsAlcohol()
    {
    return (ETYP.value == eAlcohol);
    }

void INGRRecord::IsAlcohol(bool value)
    {
    ETYP.value = value ? eAlcohol : eNone;
    }

bool INGRRecord::IsEquipmentType(SINT32 Type)
    {
    return ETYP.value == Type;
    }

void INGRRecord::SetEquipmentType(SINT32 Type)
    {
    ETYP.value = Type;
    }

UINT32 INGRRecord::GetType()
    {
    return REV32(INGR);
    }

STRING INGRRecord::GetStrType()
    {
    return "INGR";
    }

SINT32 INGRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(OBND):
                OBND.Read(buffer, subSize, curPos);
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
            case REV32(MICO):
                MICO.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize, curPos);
                break;
            case REV32(ETYP):
                ETYP.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
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
                //printf("FileName = %s\n", FileName);
                printf("  INGR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 INGRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    SCRI.Unload();
    ETYP.Unload();
    DATA.Unload();
    ENIT.Unload();
    Effects.Unload();
    return 1;
    }

SINT32 INGRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(SCRI);
    WRITE(ETYP);
    WRITE(DATA);
    WRITE(ENIT);
    Effects.Write(writer);
    return -1;
    }

bool INGRRecord::operator ==(const INGRRecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            ETYP == other.ETYP &&
            DATA == other.DATA &&
            ENIT == other.ENIT &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MODL == other.MODL &&
            Effects == other.Effects);
    }

bool INGRRecord::operator !=(const INGRRecord &other) const
    {
    return !(*this == other);
    }
}