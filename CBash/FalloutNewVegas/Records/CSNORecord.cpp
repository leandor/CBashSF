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
    FNVRecord(_recData)
    {
    //
    }

CSNORecord::CSNORecord(CSNORecord *srcRecord):
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

bool CSNORecord::IsDealerStayOnSoft17()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDealerStayOnSoft17) != 0;
    }

void CSNORecord::IsDealerStayOnSoft17(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDealerStayOnSoft17) : (Dummy->flags & ~fIsDealerStayOnSoft17);
    }

bool CSNORecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CSNORecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CSNORecord::GetType()
    {
    return REV32(CSNO);
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
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODL):
                MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MOD2):
                MOD2.Read(buffer, subSize, curPos);
                break;
            case REV32(MOD3):
                MOD3.Read(buffer, subSize, curPos);
                break;
            case REV32(MOD4):
                MOD4.Read(buffer, subSize, curPos);
                break;
            case REV32(ICON):
                ICON.Load();
                ICON->ICON.Read(buffer, subSize, curPos);
                break;
            case REV32(ICO2):
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

SINT32 CSNORecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DATA);

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MODL), MODL->MODL.value, MODL->MODL.GetSize());

        }

    WRITE(MODL);
    WRITE(MOD2);
    WRITE(MOD3);
    WRITE(MOD4);

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            SaveHandler.writeSubRecord(REV32(ICON), ICON->ICON.value, ICON->ICON.GetSize());

        }

    if(ICO2.IsLoaded())
        {
        if(ICO2->ICO2.IsLoaded())
            SaveHandler.writeSubRecord(REV32(ICO2), ICO2->ICO2.value, ICO2->ICO2.GetSize());

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