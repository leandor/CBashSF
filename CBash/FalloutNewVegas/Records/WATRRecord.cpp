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
#include "WATRRecord.h"

namespace FNV
{
WATRRecord::WATRRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

WATRRecord::WATRRecord(WATRRecord *srcRecord):
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
    NNAM = srcRecord->NNAM;
    ANAM = srcRecord->ANAM;
    FNAM = srcRecord->FNAM;
    MNAM = srcRecord->MNAM;
    SNAM = srcRecord->SNAM;
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    DNAM = srcRecord->DNAM;
    GNAM = srcRecord->GNAM;
    return;
    }

WATRRecord::~WATRRecord()
    {
    //
    }

bool WATRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);
    if(XNAM.IsLoaded())
        op.Accept(XNAM->value);
    //if(GNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(GNAM->value);

    return op.Stop();
    }

bool WATRRecord::IsCausesDmg()
    {
    return (FNAM.value.value & fIsCausesDamage) != 0;
    }

void WATRRecord::IsCausesDmg(bool value)
    {
    if(value)
        FNAM.value.value |= fIsCausesDamage;
    else
        FNAM.value.value &= ~fIsCausesDamage;
    }

bool WATRRecord::IsCausesDamage()
    {
    return (FNAM.value.value & fIsCausesDamage) != 0;
    }

void WATRRecord::IsCausesDamage(bool value)
    {
    if(value)
        FNAM.value.value |= fIsCausesDamage;
    else
        FNAM.value.value &= ~fIsCausesDamage;
    }

bool WATRRecord::IsReflective()
    {
    return (FNAM.value.value & fIsReflective) != 0;
    }

void WATRRecord::IsReflective(bool value)
    {
    if(value)
        FNAM.value.value |= fIsReflective;
    else
        FNAM.value.value &= ~fIsReflective;
    }

bool WATRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((FNAM.value.value & Mask) == Mask) : ((FNAM.value.value & Mask) != 0);
    }

void WATRRecord::SetFlagMask(UINT8 Mask)
    {
    FNAM.value.value = Mask;
    }

UINT32 WATRRecord::GetSize(bool forceCalc)
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

    if(NNAM.IsLoaded())
        {
        cSize = NNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;

    if(FNAM.IsLoaded())
        TotSize += FNAM.GetSize() + 6;

    if(MNAM.IsLoaded())
        {
        cSize = MNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(XNAM.IsLoaded())
        TotSize += XNAM.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    if(GNAM.IsLoaded())
        TotSize += GNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 WATRRecord::GetType()
    {
    return 'RTAW';
    }

STRING WATRRecord::GetStrType()
    {
    return "WATR";
    }

SINT32 WATRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'MANN':
                NNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                MNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANG':
                GNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  WATR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 WATRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    NNAM.Unload();
    ANAM.Unload();
    FNAM.Unload();
    MNAM.Unload();
    SNAM.Unload();
    XNAM.Unload();
    DATA.Unload();
    DNAM.Unload();
    GNAM.Unload();
    return 1;
    }

SINT32 WATRRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(NNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANN', NNAM.value, NNAM.GetSize());

    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord('MANA', ANAM.value, ANAM.GetSize());

    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANF', FNAM.value, FNAM.GetSize());

    if(MNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANM', MNAM.value, MNAM.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(XNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANX', XNAM.value, XNAM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    if(GNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANG', GNAM.value, GNAM.GetSize());

    return -1;
    }

bool WATRRecord::operator ==(const WATRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NNAM.equalsi(other.NNAM) &&
            ANAM == other.ANAM &&
            FNAM == other.FNAM &&
            MNAM.equalsi(other.MNAM) &&
            SNAM == other.SNAM &&
            XNAM == other.XNAM &&
            DATA == other.DATA &&
            DNAM == other.DNAM &&
            GNAM == other.GNAM);
    }

bool WATRRecord::operator !=(const WATRRecord &other) const
    {
    return !(*this == other);
    }
}