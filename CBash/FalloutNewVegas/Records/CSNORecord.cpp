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
#include "CSNORecord.h"

namespace FNV
{
CSNORecord::CSNORecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CSNORecord::CSNORecord(CSNORecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        }
    MODL = srcRecord->MODL;
    MOD2 = srcRecord->MOD2;
    MOD3 = srcRecord->MOD3;
    MOD4 = srcRecord->MOD4;
    if(srcRecord->ICON.IsLoaded())
        {
        ICON.Load();
        ICON->ICON = srcRecord->ICON->ICON;
        }
    if(srcRecord->ICO2.IsLoaded())
        {
        ICO2.Load();
        ICO2->ICO2 = srcRecord->ICO2->ICO2;
        }
    return;
    }

CSNORecord::~CSNORecord()
    {
    //
    }

bool CSNORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);

    return op.Stop();
    }

UINT32 CSNORecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-16];

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

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            {
            cSize = MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(MODL.IsLoaded())
        {
        cSize = MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD2.IsLoaded())
        {
        cSize = MOD2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD3.IsLoaded())
        {
        cSize = MOD3.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD4.IsLoaded())
        {
        cSize = MOD4.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            {
            cSize = ICON->ICON.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(ICO2.IsLoaded())
        {
        if(ICO2->ICO2.IsLoaded())
            {
            cSize = ICO2->ICO2.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    return TotSize;
    }

UINT32 CSNORecord::GetType()
    {
    return 'ONSC';
    }

STRING CSNORecord::GetStrType()
    {
    return "CSNO";
    }

SINT32 CSNORecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Read(buffer, subSize, curPos);
                break;
            case '2DOM':
                MOD2.Read(buffer, subSize, curPos);
                break;
            case '3DOM':
                MOD3.Read(buffer, subSize, curPos);
                break;
            case '4DOM':
                MOD4.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Load();
                ICON->ICON.Read(buffer, subSize, curPos);
                break;
            case '2OCI':
                ICO2.Load();
                ICO2->ICO2.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CSNO: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CSNORecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    MODL.Unload();
    MODL.Unload();
    MOD2.Unload();
    MOD3.Unload();
    MOD4.Unload();
    ICON.Unload();
    ICO2.Unload();
    return 1;
    }

SINT32 CSNORecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());

        }

    if(MODL.IsLoaded())
        SaveHandler.writeSubRecord('LDOM', MODL.value, MODL.GetSize());

    if(MOD2.IsLoaded())
        SaveHandler.writeSubRecord('2DOM', MOD2.value, MOD2.GetSize());

    if(MOD3.IsLoaded())
        SaveHandler.writeSubRecord('3DOM', MOD3.value, MOD3.GetSize());

    if(MOD4.IsLoaded())
        SaveHandler.writeSubRecord('4DOM', MOD4.value, MOD4.GetSize());

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            SaveHandler.writeSubRecord('NOCI', ICON->ICON.value, ICON->ICON.GetSize());

        }

    if(ICO2.IsLoaded())
        {
        if(ICO2->ICO2.IsLoaded())
            SaveHandler.writeSubRecord('2OCI', ICO2->ICO2.value, ICO2->ICO2.GetSize());

        }

    return -1;
    }

bool CSNORecord::operator ==(const CSNORecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA &&
            MODL == other.MODL &&
            MODL.equalsi(other.MODL) &&
            MOD2.equalsi(other.MOD2) &&
            MOD3.equalsi(other.MOD3) &&
            MOD4.equalsi(other.MOD4) &&
            ICON == other.ICON &&
            ICO2 == other.ICO2);
    }

bool CSNORecord::operator !=(const CSNORecord &other) const
    {
    return !(*this == other);
    }
}