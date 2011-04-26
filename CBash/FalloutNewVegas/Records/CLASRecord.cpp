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
#include "CLASRecord.h"

namespace FNV
{
CLASRecord::CLASRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CLASRecord::CLASRecord(CLASRecord *srcRecord):
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
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    DATA = srcRecord->DATA;
    ATTR = srcRecord->ATTR;
    return;
    }

CLASRecord::~CLASRecord()
    {
    //
    }

bool CLASRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;


    return op.Stop();
    }

bool CLASRecord::IsPlayable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPlayable) != 0;
    }

void CLASRecord::IsPlayable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPlayable;
    else
        Dummy->flags &= ~fIsPlayable;
    }

bool CLASRecord::IsGuard()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsGuard) != 0;
    }

void CLASRecord::IsGuard(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsGuard;
    else
        Dummy->flags &= ~fIsGuard;
    }

bool CLASRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CLASRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CLASRecord::IsServicesWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesWeapons) != 0;
    }

void CLASRecord::IsServicesWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesWeapons;
    else
        Dummy->flags &= ~fIsServicesWeapons;
    }

bool CLASRecord::IsServicesArmor()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesArmor) != 0;
    }

void CLASRecord::IsServicesArmor(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesArmor;
    else
        Dummy->flags &= ~fIsServicesArmor;
    }

bool CLASRecord::IsServicesClothing()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesClothing) != 0;
    }

void CLASRecord::IsServicesClothing(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesClothing;
    else
        Dummy->flags &= ~fIsServicesClothing;
    }

bool CLASRecord::IsServicesBooks()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesBooks) != 0;
    }

void CLASRecord::IsServicesBooks(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesBooks;
    else
        Dummy->flags &= ~fIsServicesBooks;
    }

bool CLASRecord::IsServicesFood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesFood) != 0;
    }

void CLASRecord::IsServicesFood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesFood;
    else
        Dummy->flags &= ~fIsServicesFood;
    }

bool CLASRecord::IsServicesChems()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesChems) != 0;
    }

void CLASRecord::IsServicesChems(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesChems;
    else
        Dummy->flags &= ~fIsServicesChems;
    }

bool CLASRecord::IsServicesStimpacks()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesStimpacks) != 0;
    }

void CLASRecord::IsServicesStimpacks(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesStimpacks;
    else
        Dummy->flags &= ~fIsServicesStimpacks;
    }

bool CLASRecord::IsServicesLights()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesLights) != 0;
    }

void CLASRecord::IsServicesLights(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesLights;
    else
        Dummy->flags &= ~fIsServicesLights;
    }

bool CLASRecord::IsServicesMiscItems()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesMiscItems) != 0;
    }

void CLASRecord::IsServicesMiscItems(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesMiscItems;
    else
        Dummy->flags &= ~fIsServicesMiscItems;
    }

bool CLASRecord::IsServicesPotions()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesPotions) != 0;
    }

void CLASRecord::IsServicesPotions(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesPotions;
    else
        Dummy->flags &= ~fIsServicesPotions;
    }

bool CLASRecord::IsServicesTraining()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesTraining) != 0;
    }

void CLASRecord::IsServicesTraining(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesTraining;
    else
        Dummy->flags &= ~fIsServicesTraining;
    }

bool CLASRecord::IsServicesRecharge()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesRecharge) != 0;
    }

void CLASRecord::IsServicesRecharge(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesRecharge;
    else
        Dummy->flags &= ~fIsServicesRecharge;
    }

bool CLASRecord::IsServicesRepair()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsServicesRepair) != 0;
    }

void CLASRecord::IsServicesRepair(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsServicesRepair;
    else
        Dummy->flags &= ~fIsServicesRepair;
    }

bool CLASRecord::IsServicesFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CLASRecord::SetServicesFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CLASRecord::GetSize(bool forceCalc)
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

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
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

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(ATTR.IsLoaded())
        TotSize += ATTR.GetSize() + 6;

    return TotSize;
    }

UINT32 CLASRecord::GetType()
    {
    return 'SALC';
    }

STRING CLASRecord::GetStrType()
    {
    return "CLAS";
    }

SINT32 CLASRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'CSED':
                DESC.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'RTTA':
                ATTR.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CLAS: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CLASRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    MICO.Unload();
    DATA.Unload();
    ATTR.Unload();
    return 1;
    }

SINT32 CLASRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord('CSED', DESC.value, DESC.GetSize());

    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', ICON.value, ICON.GetSize());

    if(MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MICO.value, MICO.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(ATTR.IsLoaded())
        SaveHandler.writeSubRecord('RTTA', ATTR.value, ATTR.GetSize());

    return -1;
    }

bool CLASRecord::operator ==(const CLASRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            DATA == other.DATA &&
            ATTR == other.ATTR);
    }

bool CLASRecord::operator !=(const CLASRecord &other) const
    {
    return !(*this == other);
    }
}