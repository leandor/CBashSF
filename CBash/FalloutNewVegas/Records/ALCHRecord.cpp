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
    memset(&unused1, 0x00, 3);
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
            addictionChance == other.addictionChance &&
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
    if(srcRecord->EFID.IsLoaded())
        {
        EFID.Load();
        EFID->EFID = srcRecord->EFID->EFID;
        EFID->EFIT = srcRecord->EFID->EFIT;
        EFID->CTDA = srcRecord->EFID->CTDA;
        }
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
        op.Accept(SCRI->value);
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    //if(ENIT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(ENIT->value);
    if(EFID.IsLoaded() && EFID->EFID.IsLoaded())
        op.Accept(EFID->EFID->value);
    if(EFID.IsLoaded() && EFID->CTDA.IsLoaded())
        op.Accept(EFID->CTDA->value);

    return op.Stop();
    }

bool ALCHRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void ALCHRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool ALCHRecord::IsBigGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBigGuns);
    }

void ALCHRecord::IsBigGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBigGuns : eDummyDefault;
    }

bool ALCHRecord::IsEnergyWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEnergyWeapons);
    }

void ALCHRecord::IsEnergyWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEnergyWeapons : eDummyDefault;
    }

bool ALCHRecord::IsSmallGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSmallGuns);
    }

void ALCHRecord::IsSmallGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSmallGuns : eDummyDefault;
    }

bool ALCHRecord::IsMeleeWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMeleeWeapons);
    }

void ALCHRecord::IsMeleeWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMeleeWeapons : eDummyDefault;
    }

bool ALCHRecord::IsUnarmedWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnarmedWeapon);
    }

void ALCHRecord::IsUnarmedWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUnarmedWeapon : eDummyDefault;
    }

bool ALCHRecord::IsThrownWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eThrownWeapons);
    }

void ALCHRecord::IsThrownWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eThrownWeapons : eDummyDefault;
    }

bool ALCHRecord::IsMine()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMine);
    }

void ALCHRecord::IsMine(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMine : eDummyDefault;
    }

bool ALCHRecord::IsBodyWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBodyWear);
    }

void ALCHRecord::IsBodyWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBodyWear : eDummyDefault;
    }

bool ALCHRecord::IsHeadWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHeadWear);
    }

void ALCHRecord::IsHeadWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHeadWear : eDummyDefault;
    }

bool ALCHRecord::IsHandWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandWear);
    }

void ALCHRecord::IsHandWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandWear : eDummyDefault;
    }

bool ALCHRecord::IsChems()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eChems);
    }

void ALCHRecord::IsChems(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eChems : eDummyDefault;
    }

bool ALCHRecord::IsStimpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStimpack);
    }

void ALCHRecord::IsStimpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStimpack : eDummyDefault;
    }

bool ALCHRecord::IsFood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFood);
    }

void ALCHRecord::IsFood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFood : eDummyDefault;
    }

bool ALCHRecord::IsAlcohol()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAlcohol);
    }

void ALCHRecord::IsAlcohol(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAlcohol : eDummyDefault;
    }

bool ALCHRecord::IsEquipmentType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void ALCHRecord::SetEquipmentType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 ALCHRecord::GetType()
    {
    return 'HCLA';
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
            case 'DNBO':
                OBND.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
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
            case 'SDOM':
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'TSED':
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize, curPos);
                break;
            case 'DTSD':
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize, curPos);
                break;
            case 'LDMD':
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, curPos);
                break;
            case 'TDMD':
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, curPos);
                break;
            case 'FTSD':
                //Marks end of a destruction stage
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case 'PYTE':
                ETYP.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'TINE':
                ENIT.Read(buffer, subSize, curPos);
                break;
            case 'DIFE':
                EFID.Load();
                EFID->EFID.Read(buffer, subSize, curPos);
                break;
            case 'TIFE':
                EFID.Load();
                EFID->EFIT.Read(buffer, subSize, curPos);
                break;
            case 'ADTC':
                EFID.Load();
                EFID->CTDA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ALCH: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
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
    EFID.Unload();
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

    if(EFID.IsLoaded())
        {
        if(EFID->EFID.IsLoaded())
            SaveHandler.writeSubRecord('DIFE', EFID->EFID.value, EFID->EFID.GetSize());

        if(EFID->EFIT.IsLoaded())
            SaveHandler.writeSubRecord('TIFE', EFID->EFIT.value, EFID->EFIT.GetSize());

        if(EFID->CTDA.IsLoaded())
            SaveHandler.writeSubRecord('ADTC', EFID->CTDA.value, EFID->CTDA.GetSize());

        }

    return -1;
    }

bool ALCHRecord::operator ==(const ALCHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            SCRI == other.SCRI &&
            Destructable == other.Destructable &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            ETYP == other.ETYP &&
            DATA == other.DATA &&
            ENIT == other.ENIT &&
            EFID == other.EFID);
    }

bool ALCHRecord::operator !=(const ALCHRecord &other) const
    {
    return !(*this == other);
    }
}