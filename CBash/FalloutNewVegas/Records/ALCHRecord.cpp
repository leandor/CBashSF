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
#include "ALCHRecord.h"

namespace FNV
{
ALCHRecord::ALCHENIT::ALCHENIT():
    value(0),
    flags(0),
    withdrawalEffect(0),
    addictionChance(0.0f),
    consumeSound(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

ALCHRecord::ALCHENIT::~ALCHENIT()
    {
    //
    }

bool ALCHRecord::ALCHENIT::operator ==(const ALCHENIT &other) const
    {
    return (value == other.value &&
            flags == other.flags &&
            withdrawalEffect == other.withdrawalEffect &&
            AlmostEqual(addictionChance, other.addictionChance, 2) &&
            consumeSound == other.consumeSound);
    }

bool ALCHRecord::ALCHENIT::operator !=(const ALCHENIT &other) const
    {
    return !(*this == other);
    }

ALCHRecord::ALCHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ALCHRecord::ALCHRecord(ALCHRecord *srcRecord):
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
    Destructable = srcRecord->Destructable;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    ETYP = srcRecord->ETYP;
    DATA = srcRecord->DATA;
    ENIT = srcRecord->ENIT;
    Effects = srcRecord->Effects;
    return;
    }

ALCHRecord::~ALCHRecord()
    {
    //
    }

bool ALCHRecord::VisitFormIDs(FormIDOp &op)
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
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    for(UINT32 x = 0; x < Effects.value.size(); x++)
        Effects.value[x]->VisitFormIDs(op);

    return op.Stop();
    }

bool ALCHRecord::IsNoAutoCalc()
    {
    return (ENIT.value.flags & fIsNoAutoCalc) != 0;
    }

void ALCHRecord::IsNoAutoCalc(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsNoAutoCalc) : (ENIT.value.flags & ~fIsNoAutoCalc);
    }

bool ALCHRecord::IsFood()
    {
    return (ENIT.value.flags & fIsFood) != 0;
    }

void ALCHRecord::IsFood(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsFood) : (ENIT.value.flags & ~fIsFood);
    }

bool ALCHRecord::IsMedicine()
    {
    return (ENIT.value.flags & fIsMedicine) != 0;
    }

void ALCHRecord::IsMedicine(bool value)
    {
    ENIT.value.flags = value ? (ENIT.value.flags | fIsMedicine) : (ENIT.value.flags & ~fIsMedicine);
    }

bool ALCHRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((ENIT.value.flags & Mask) == Mask) : ((ENIT.value.flags & Mask) != 0);
    }

void ALCHRecord::SetFlagMask(UINT8 Mask)
    {
    ENIT.value.flags = Mask;
    }

bool ALCHRecord::IsNone()
    {
    return (ETYP.value == eNone);
    }

void ALCHRecord::IsNone(bool value)
    {
    ETYP.value = value ? eNone : eBigGuns;
    }

bool ALCHRecord::IsBigGuns()
    {
    return (ETYP.value == eBigGuns);
    }

void ALCHRecord::IsBigGuns(bool value)
    {
    ETYP.value = value ? eBigGuns : eNone;
    }

bool ALCHRecord::IsEnergyWeapons()
    {
    return (ETYP.value == eEnergyWeapons);
    }

void ALCHRecord::IsEnergyWeapons(bool value)
    {
    ETYP.value = value ? eEnergyWeapons : eNone;
    }

bool ALCHRecord::IsSmallGuns()
    {
    return (ETYP.value == eSmallGuns);
    }

void ALCHRecord::IsSmallGuns(bool value)
    {
    ETYP.value = value ? eSmallGuns : eNone;
    }

bool ALCHRecord::IsMeleeWeapons()
    {
    return (ETYP.value == eMeleeWeapons);
    }

void ALCHRecord::IsMeleeWeapons(bool value)
    {
    ETYP.value = value ? eMeleeWeapons : eNone;
    }

bool ALCHRecord::IsUnarmedWeapon()
    {
    return (ETYP.value == eUnarmedWeapon);
    }

void ALCHRecord::IsUnarmedWeapon(bool value)
    {
    ETYP.value = value ? eUnarmedWeapon : eNone;
    }

bool ALCHRecord::IsThrownWeapons()
    {
    return (ETYP.value == eThrownWeapons);
    }

void ALCHRecord::IsThrownWeapons(bool value)
    {
    ETYP.value = value ? eThrownWeapons : eNone;
    }

bool ALCHRecord::IsMine()
    {
    return (ETYP.value == eMine);
    }

void ALCHRecord::IsMine(bool value)
    {
    ETYP.value = value ? eMine : eNone;
    }

bool ALCHRecord::IsBodyWear()
    {
    return (ETYP.value == eBodyWear);
    }

void ALCHRecord::IsBodyWear(bool value)
    {
    ETYP.value = value ? eBodyWear : eNone;
    }

bool ALCHRecord::IsHeadWear()
    {
    return (ETYP.value == eHeadWear);
    }

void ALCHRecord::IsHeadWear(bool value)
    {
    ETYP.value = value ? eHeadWear : eNone;
    }

bool ALCHRecord::IsHandWear()
    {
    return (ETYP.value == eHandWear);
    }

void ALCHRecord::IsHandWear(bool value)
    {
    ETYP.value = value ? eHandWear : eNone;
    }

bool ALCHRecord::IsChems()
    {
    return (ETYP.value == eChems);
    }

void ALCHRecord::IsChems(bool value)
    {
    ETYP.value = value ? eChems : eNone;
    }

bool ALCHRecord::IsStimpack()
    {
    return (ETYP.value == eStimpack);
    }

void ALCHRecord::IsStimpack(bool value)
    {
    ETYP.value = value ? eStimpack : eNone;
    }

bool ALCHRecord::IsEdible()
    {
    return (ETYP.value == eEdible);
    }

void ALCHRecord::IsEdible(bool value)
    {
    ETYP.value = value ? eEdible : eNone;
    }

bool ALCHRecord::IsAlcohol()
    {
    return (ETYP.value == eAlcohol);
    }

void ALCHRecord::IsAlcohol(bool value)
    {
    ETYP.value = value ? eAlcohol : eNone;
    }

bool ALCHRecord::IsEquipmentType(SINT32 Type)
    {
    return ETYP.value == Type;
    }

void ALCHRecord::SetEquipmentType(SINT32 Type)
    {
    ETYP.value = Type;
    }

UINT32 ALCHRecord::GetType()
    {
    return REV32(ALCH);
    }

STRING ALCHRecord::GetStrType()
    {
    return "ALCH";
    }

SINT32 ALCHRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize, curPos);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize, curPos);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, curPos);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, curPos);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize, curPos);
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
                //printer("FileName = %s\n", FileName);
                printer("  ALCH: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 ALCHRecord::Unload()
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
    Destructable.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    ETYP.Unload();
    DATA.Unload();
    ENIT.Unload();
    Effects.Unload();
    return 1;
    }

SINT32 ALCHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(SCRI);
    Destructable.Write(writer);
    WRITE(YNAM);
    WRITE(ZNAM);
    WRITE(ETYP);
    WRITE(DATA);
    WRITE(ENIT);
    Effects.Write(writer);
    return -1;
    }

bool ALCHRecord::operator ==(const ALCHRecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            ETYP == other.ETYP &&
            DATA == other.DATA &&
            ENIT == other.ENIT &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            Destructable == other.Destructable &&
            MODL == other.MODL &&
            Effects == other.Effects);
    }

bool ALCHRecord::operator !=(const ALCHRecord &other) const
    {
    return !(*this == other);
    }
}