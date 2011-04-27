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
#include "AMEFRecord.h"

namespace FNV
{
AMEFRecord::AMEFRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

AMEFRecord::AMEFRecord(AMEFRecord *srcRecord):
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
    return;
    }

AMEFRecord::~AMEFRecord()
    {
    //
    }

bool AMEFRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;


    return op.Stop();
    }

bool AMEFRecord::IsDamage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDamage);
    }

void AMEFRecord::IsDamage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDamage : eDummyDefault;
    }

bool AMEFRecord::IsDR()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDR);
    }

void AMEFRecord::IsDR(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDR : eDummyDefault;
    }

bool AMEFRecord::IsDT()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDT);
    }

void AMEFRecord::IsDT(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDT : eDummyDefault;
    }

bool AMEFRecord::IsSpread()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSpread);
    }

void AMEFRecord::IsSpread(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSpread : eDummyDefault;
    }

bool AMEFRecord::IsCondition()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCondition);
    }

void AMEFRecord::IsCondition(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCondition : eDummyDefault;
    }

bool AMEFRecord::IsFatigue()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFatigue);
    }

void AMEFRecord::IsFatigue(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFatigue : eDummyDefault;
    }

bool AMEFRecord::IsModType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void AMEFRecord::SetModType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool AMEFRecord::IsAdd()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAdd);
    }

void AMEFRecord::IsAdd(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAdd : eDummyDefault;
    }

bool AMEFRecord::IsMultiply()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMultiply);
    }

void AMEFRecord::IsMultiply(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMultiply : eDummyDefault;
    }

bool AMEFRecord::IsSubtract()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSubtract);
    }

void AMEFRecord::IsSubtract(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSubtract : eDummyDefault;
    }

bool AMEFRecord::IsOpType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void AMEFRecord::SetOpType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 AMEFRecord::GetSize(bool forceCalc)
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

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

UINT32 AMEFRecord::GetType()
    {
    return 'FEMA';
    }

STRING AMEFRecord::GetStrType()
    {
    return "AMEF";
    }

SINT32 AMEFRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            default:
                //printf("FileName = %s\n", FileName);
                printf("  AMEF: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 AMEFRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 AMEFRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    return -1;
    }

bool AMEFRecord::operator ==(const AMEFRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA);
    }

bool AMEFRecord::operator !=(const AMEFRecord &other) const
    {
    return !(*this == other);
    }
}