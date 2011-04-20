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
#include "FACTRecord.h"

namespace FNV
{
FACTRecord::FACTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

FACTRecord::FACTRecord(FACTRecord *srcRecord):
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
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    CNAM = srcRecord->CNAM;
    if(srcRecord->RNAM.IsLoaded())
        {
        RNAM.Load();
        RNAM->RNAM = srcRecord->RNAM->RNAM;
        RNAM->MNAM = srcRecord->RNAM->MNAM;
        RNAM->FNAM = srcRecord->RNAM->FNAM;
        RNAM->INAM = srcRecord->RNAM->INAM;
        }
    WMI1 = srcRecord->WMI1;
    return;
    }

FACTRecord::~FACTRecord()
    {
    //
    }

bool FACTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(XNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XNAM->value);
    if(WMI1.IsLoaded())
        op.Accept(WMI1->value);

    return op.Stop();
    }

UINT32 FACTRecord::GetSize(bool forceCalc)
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

    if(XNAM.IsLoaded())
        TotSize += XNAM.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;

    if(RNAM.IsLoaded())
        {
        if(RNAM->RNAM.IsLoaded())
            TotSize += RNAM->RNAM.GetSize() + 6;
        if(RNAM->MNAM.IsLoaded())
            {
            cSize = RNAM->MNAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(RNAM->FNAM.IsLoaded())
            {
            cSize = RNAM->FNAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(RNAM->INAM.IsLoaded())
            {
            cSize = RNAM->INAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(WMI1.IsLoaded())
        TotSize += WMI1.GetSize() + 6;

    return TotSize;
    }

UINT32 FACTRecord::GetType()
    {
    return 'TCAF';
    }

STRING FACTRecord::GetStrType()
    {
    return "FACT";
    }

SINT32 FACTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Load();
                RNAM->RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                RNAM.Load();
                RNAM->MNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                RNAM.Load();
                RNAM->FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                RNAM.Load();
                RNAM->INAM.Read(buffer, subSize, curPos);
                break;
            case '1IMW':
                WMI1.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  FACT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 FACTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    XNAM.Unload();
    DATA.Unload();
    CNAM.Unload();
    RNAM.Unload();
    WMI1.Unload();
    return 1;
    }

SINT32 FACTRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(XNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANX', XNAM.value, XNAM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());

    if(RNAM.IsLoaded())
        {
        if(RNAM->RNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANR', RNAM->RNAM.value, RNAM->RNAM.GetSize());

        if(RNAM->MNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANM', RNAM->MNAM.value, RNAM->MNAM.GetSize());

        if(RNAM->FNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANF', RNAM->FNAM.value, RNAM->FNAM.GetSize());

        if(RNAM->INAM.IsLoaded())
            SaveHandler.writeSubRecord('MANI', RNAM->INAM.value, RNAM->INAM.GetSize());

        }

    if(WMI1.IsLoaded())
        SaveHandler.writeSubRecord('1IMW', WMI1.value, WMI1.GetSize());

    return -1;
    }

bool FACTRecord::operator ==(const FACTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            XNAM == other.XNAM &&
            DATA == other.DATA &&
            CNAM == other.CNAM &&
            RNAM == other.RNAM &&
            WMI1 == other.WMI1);
    }

bool FACTRecord::operator !=(const FACTRecord &other) const
    {
    return !(*this == other);
    }
}