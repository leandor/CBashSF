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
#include "CPTHRecord.h"

namespace FNV
{
CPTHRecord::CPTHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CPTHRecord::CPTHRecord(CPTHRecord *srcRecord):
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
    CTDA = srcRecord->CTDA;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    SNAM = srcRecord->SNAM;
    return;
    }

CPTHRecord::~CPTHRecord()
    {
    //
    }

bool CPTHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    //if(ANAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(ANAM->value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);

    return op.Stop();
    }

bool CPTHRecord::IsDefault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDefault);
    }

void CPTHRecord::IsDefault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDefault;
    else
        Dummy->flags = eDummyDefault;
    }

bool CPTHRecord::IsDisable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDisable);
    }

void CPTHRecord::IsDisable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDisable;
    else
        Dummy->flags = eDummyDefault;
    }

bool CPTHRecord::IsShotList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eShotList);
    }

void CPTHRecord::IsShotList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eShotList;
    else
        Dummy->flags = eDummyDefault;
    }

bool CPTHRecord::IsType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CPTHRecord::SetType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CPTHRecord::GetSize(bool forceCalc)
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

    if(CTDA.IsLoaded())
        TotSize += CTDA.GetSize() + 6;

    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 CPTHRecord::GetType()
    {
    return 'HTPC';
    }

STRING CPTHRecord::GetStrType()
    {
    return "CPTH";
    }

SINT32 CPTHRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'ADTC':
                CTDA.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CPTH: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CPTHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    CTDA.Unload();
    ANAM.Unload();
    DATA.Unload();
    SNAM.Unload();
    return 1;
    }

SINT32 CPTHRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(CTDA.IsLoaded())
        SaveHandler.writeSubRecord('ADTC', CTDA.value, CTDA.GetSize());

    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord('MANA', ANAM.value, ANAM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    return -1;
    }

bool CPTHRecord::operator ==(const CPTHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            CTDA == other.CTDA &&
            ANAM == other.ANAM &&
            DATA == other.DATA &&
            SNAM == other.SNAM);
    }

bool CPTHRecord::operator !=(const CPTHRecord &other) const
    {
    return !(*this == other);
    }
}