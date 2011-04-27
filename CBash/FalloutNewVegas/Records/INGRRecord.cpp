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
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SCRI = srcRecord->SCRI;
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

INGRRecord::~INGRRecord()
    {
    //
    }

bool INGRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    if(EFID.IsLoaded() && EFID->EFID.IsLoaded())
        op.Accept(EFID->EFID->value);
    if(EFID.IsLoaded() && EFID->CTDA.IsLoaded())
        op.Accept(EFID->CTDA->value);

    return op.Stop();
    }

bool INGRRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void INGRRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool INGRRecord::IsBigGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBigGuns);
    }

void INGRRecord::IsBigGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBigGuns : eDummyDefault;
    }

bool INGRRecord::IsEnergyWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEnergyWeapons);
    }

void INGRRecord::IsEnergyWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEnergyWeapons : eDummyDefault;
    }

bool INGRRecord::IsSmallGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSmallGuns);
    }

void INGRRecord::IsSmallGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSmallGuns : eDummyDefault;
    }

bool INGRRecord::IsMeleeWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMeleeWeapons);
    }

void INGRRecord::IsMeleeWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMeleeWeapons : eDummyDefault;
    }

bool INGRRecord::IsUnarmedWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnarmedWeapon);
    }

void INGRRecord::IsUnarmedWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUnarmedWeapon : eDummyDefault;
    }

bool INGRRecord::IsThrownWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eThrownWeapons);
    }

void INGRRecord::IsThrownWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eThrownWeapons : eDummyDefault;
    }

bool INGRRecord::IsMine()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMine);
    }

void INGRRecord::IsMine(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMine : eDummyDefault;
    }

bool INGRRecord::IsBodyWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBodyWear);
    }

void INGRRecord::IsBodyWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBodyWear : eDummyDefault;
    }

bool INGRRecord::IsHeadWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHeadWear);
    }

void INGRRecord::IsHeadWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHeadWear : eDummyDefault;
    }

bool INGRRecord::IsHandWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandWear);
    }

void INGRRecord::IsHandWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHandWear : eDummyDefault;
    }

bool INGRRecord::IsChems()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eChems);
    }

void INGRRecord::IsChems(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eChems : eDummyDefault;
    }

bool INGRRecord::IsStimpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStimpack);
    }

void INGRRecord::IsStimpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStimpack : eDummyDefault;
    }

bool INGRRecord::IsFood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFood);
    }

void INGRRecord::IsFood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFood : eDummyDefault;
    }

bool INGRRecord::IsAlcohol()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAlcohol);
    }

void INGRRecord::IsAlcohol(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAlcohol : eDummyDefault;
    }

bool INGRRecord::IsEquipmentType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void INGRRecord::SetEquipmentType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 INGRRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(OBND.IsLoaded())
        TotSize += OBND.GetSize() + 6;

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            {
            cSize = MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODB.IsLoaded())
            {
            cSize = MODL->MODB.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODS.IsLoaded())
            TotSize += MODL->MODS.GetSize() + 6;
        if(MODL->MODD.IsLoaded())
            TotSize += MODL->MODD.GetSize() + 6;
        }

    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MICO.IsLoaded())
        {
        cSize = MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;

    if(ETYP.IsLoaded())
        TotSize += ETYP.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(ENIT.IsLoaded())
        TotSize += ENIT.GetSize() + 6;

    if(EFID.IsLoaded())
        {
        if(EFID->EFID.IsLoaded())
            TotSize += EFID->EFID.GetSize() + 6;
        if(EFID->EFIT.IsLoaded())
            TotSize += EFID->EFIT.GetSize() + 6;
        if(EFID->CTDA.IsLoaded())
            TotSize += EFID->CTDA.GetSize() + 6;
        }

    return TotSize;
    }

UINT32 INGRRecord::GetType()
    {
    return 'RGNI';
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
                MODL->MODS.Read(buffer, subSize, curPos);
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
    EFID.Unload();
    return 1;
    }

SINT32 INGRRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());

        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', MODL->MODB.value, MODL->MODB.GetSize());

        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());

        if(MODL->MODS.IsLoaded())
            SaveHandler.writeSubRecord('SDOM', MODL->MODS.value, MODL->MODS.GetSize());

        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', MODL->MODD.value, MODL->MODD.GetSize());

        }

    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', ICON.value, ICON.GetSize());

    if(MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MICO.value, MICO.GetSize());

    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord('IRCS', SCRI.value, SCRI.GetSize());

    if(ETYP.IsLoaded())
        SaveHandler.writeSubRecord('PYTE', ETYP.value, ETYP.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(ENIT.IsLoaded())
        SaveHandler.writeSubRecord('TINE', ENIT.value, ENIT.GetSize());

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

bool INGRRecord::operator ==(const INGRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            SCRI == other.SCRI &&
            ETYP == other.ETYP &&
            DATA == other.DATA &&
            ENIT == other.ENIT &&
            EFID == other.EFID);
    }

bool INGRRecord::operator !=(const INGRRecord &other) const
    {
    return !(*this == other);
    }
}