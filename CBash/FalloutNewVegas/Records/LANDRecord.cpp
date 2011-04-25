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
#include "LANDRecord.h"

namespace FNV
{
LANDRecord::LANDRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LANDRecord::LANDRecord(LANDRecord *srcRecord):
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

    DATA = srcRecord->DATA;
    VNML = srcRecord->VNML;
    VHGT = srcRecord->VHGT;
    VCLR = srcRecord->VCLR;
    BTXT = srcRecord->BTXT;
    ATXT = srcRecord->ATXT;
    VTXT = srcRecord->VTXT;
    VTEX = srcRecord->VTEX;
    return;
    }

LANDRecord::~LANDRecord()
    {
    //
    }

bool LANDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(BTXT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(BTXT->value);
    //if(ATXT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(ATXT->value);
    //if(VTEX.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(VTEX->value);

    return op.Stop();
    }

UINT32 LANDRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(VNML.IsLoaded())
        {
        cSize = VNML.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(VHGT.IsLoaded())
        {
        cSize = VHGT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(VCLR.IsLoaded())
        {
        cSize = VCLR.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(BTXT.IsLoaded())
        TotSize += BTXT.GetSize() + 6;

    if(ATXT.IsLoaded())
        TotSize += ATXT.GetSize() + 6;

    if(VTXT.IsLoaded())
        {
        cSize = VTXT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(VTEX.IsLoaded())
        TotSize += VTEX.GetSize() + 6;

    return TotSize;
    }

UINT32 LANDRecord::GetType()
    {
    return 'DNAL';
    }

STRING LANDRecord::GetStrType()
    {
    return "LAND";
    }

SINT32 LANDRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'LMNV':
                VNML.Read(buffer, subSize, curPos);
                break;
            case 'TGHV':
                VHGT.Read(buffer, subSize, curPos);
                break;
            case 'RLCV':
                VCLR.Read(buffer, subSize, curPos);
                break;
            case 'TXTB':
                BTXT.Read(buffer, subSize, curPos);
                break;
            case 'TXTA':
                ATXT.Read(buffer, subSize, curPos);
                break;
            case 'TXTV':
                VTXT.Read(buffer, subSize, curPos);
                break;
            case 'XETV':
                VTEX.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LAND: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 LANDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    DATA.Unload();
    VNML.Unload();
    VHGT.Unload();
    VCLR.Unload();
    BTXT.Unload();
    ATXT.Unload();
    VTXT.Unload();
    VTEX.Unload();
    return 1;
    }

SINT32 LANDRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(VNML.IsLoaded())
        SaveHandler.writeSubRecord('LMNV', VNML.value, VNML.GetSize());

    if(VHGT.IsLoaded())
        SaveHandler.writeSubRecord('TGHV', VHGT.value, VHGT.GetSize());

    if(VCLR.IsLoaded())
        SaveHandler.writeSubRecord('RLCV', VCLR.value, VCLR.GetSize());

    if(BTXT.IsLoaded())
        SaveHandler.writeSubRecord('TXTB', BTXT.value, BTXT.GetSize());

    if(ATXT.IsLoaded())
        SaveHandler.writeSubRecord('TXTA', ATXT.value, ATXT.GetSize());

    if(VTXT.IsLoaded())
        SaveHandler.writeSubRecord('TXTV', VTXT.value, VTXT.GetSize());

    if(VTEX.IsLoaded())
        SaveHandler.writeSubRecord('XETV', VTEX.value, VTEX.GetSize());

    return -1;
    }

bool LANDRecord::operator ==(const LANDRecord &other) const
    {
    return (DATA == other.DATA &&
            VNML == other.VNML &&
            VHGT == other.VHGT &&
            VCLR == other.VCLR &&
            BTXT == other.BTXT &&
            ATXT == other.ATXT &&
            VTXT == other.VTXT &&
            VTEX == other.VTEX);
    }

bool LANDRecord::operator !=(const LANDRecord &other) const
    {
    return !(*this == other);
    }
}