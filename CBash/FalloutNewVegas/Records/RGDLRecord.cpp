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
#include "RGDLRecord.h"

namespace FNV
{
RGDLRecord::RGDLRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

RGDLRecord::RGDLRecord(RGDLRecord *srcRecord):
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
    NVER = srcRecord->NVER;
    DATA = srcRecord->DATA;
    XNAM = srcRecord->XNAM;
    TNAM = srcRecord->TNAM;
    RAFD = srcRecord->RAFD;
    RAFB = srcRecord->RAFB;
    RAPS = srcRecord->RAPS;
    ANAM = srcRecord->ANAM;
    return;
    }

RGDLRecord::~RGDLRecord()
    {
    //
    }

bool RGDLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(XNAM.IsLoaded())
        op.Accept(XNAM->value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM->value);

    return op.Stop();
    }

UINT32 RGDLRecord::GetSize(bool forceCalc)
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

    if(NVER.IsLoaded())
        TotSize += NVER.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(XNAM.IsLoaded())
        TotSize += XNAM.GetSize() + 6;

    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;

    if(RAFD.IsLoaded())
        TotSize += RAFD.GetSize() + 6;

    if(RAFB.IsLoaded())
        TotSize += RAFB.GetSize() + 6;

    if(RAPS.IsLoaded())
        TotSize += RAPS.GetSize() + 6;

    if(ANAM.IsLoaded())
        {
        cSize = ANAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

UINT32 RGDLRecord::GetType()
    {
    return 'LDGR';
    }

STRING RGDLRecord::GetStrType()
    {
    return "RGDL";
    }

SINT32 RGDLRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'REVN':
                NVER.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case 'DFAR':
                RAFD.Read(buffer, subSize, curPos);
                break;
            case 'BFAR':
                RAFB.Read(buffer, subSize, curPos);
                break;
            case 'SPAR':
                RAPS.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  RGDL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 RGDLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NVER.Unload();
    DATA.Unload();
    XNAM.Unload();
    TNAM.Unload();
    RAFD.Unload();
    RAFB.Unload();
    RAPS.Unload();
    ANAM.Unload();
    return 1;
    }

SINT32 RGDLRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(NVER.IsLoaded())
        SaveHandler.writeSubRecord('REVN', NVER.value, NVER.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(XNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANX', XNAM.value, XNAM.GetSize());

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANT', TNAM.value, TNAM.GetSize());

    if(RAFD.IsLoaded())
        SaveHandler.writeSubRecord('DFAR', RAFD.value, RAFD.GetSize());

    if(RAFB.IsLoaded())
        SaveHandler.writeSubRecord('BFAR', RAFB.value, RAFB.GetSize());

    if(RAPS.IsLoaded())
        SaveHandler.writeSubRecord('SPAR', RAPS.value, RAPS.GetSize());

    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord('MANA', ANAM.value, ANAM.GetSize());

    return -1;
    }

bool RGDLRecord::operator ==(const RGDLRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            DATA == other.DATA &&
            XNAM == other.XNAM &&
            TNAM == other.TNAM &&
            RAFD == other.RAFD &&
            RAFB == other.RAFB &&
            RAPS == other.RAPS &&
            ANAM.equalsi(other.ANAM));
    }

bool RGDLRecord::operator !=(const RGDLRecord &other) const
    {
    return !(*this == other);
    }
}