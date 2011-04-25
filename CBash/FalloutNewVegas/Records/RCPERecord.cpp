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
#include "RCPERecord.h"

namespace FNV
{
RCPERecord::RCPERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

RCPERecord::RCPERecord(RCPERecord *srcRecord):
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
    CTDA = srcRecord->CTDA;
    DATA = srcRecord->DATA;
    RCIL = srcRecord->RCIL;
    RCQY = srcRecord->RCQY;
    RCOD = srcRecord->RCOD;
    return;
    }

RCPERecord::~RCPERecord()
    {
    //
    }

bool RCPERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);
    if(RCIL.IsLoaded())
        op.Accept(RCIL->value);
    if(RCOD.IsLoaded())
        op.Accept(RCOD->value);

    return op.Stop();
    }

UINT32 RCPERecord::GetSize(bool forceCalc)
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

    if(CTDA.IsLoaded())
        TotSize += CTDA.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(RCIL.IsLoaded())
        TotSize += RCIL.GetSize() + 6;

    if(RCQY.IsLoaded())
        TotSize += RCQY.GetSize() + 6;

    if(RCOD.IsLoaded())
        TotSize += RCOD.GetSize() + 6;

    return TotSize;
    }

UINT32 RCPERecord::GetType()
    {
    return 'EPCR';
    }

STRING RCPERecord::GetStrType()
    {
    return "RCPE";
    }

SINT32 RCPERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'ADTC':
                CTDA.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'LICR':
                RCIL.Read(buffer, subSize, curPos);
                break;
            case 'YQCR':
                RCQY.Read(buffer, subSize, curPos);
                break;
            case 'DOCR':
                RCOD.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  RCPE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 RCPERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    CTDA.Unload();
    DATA.Unload();
    RCIL.Unload();
    RCQY.Unload();
    RCOD.Unload();
    return 1;
    }

SINT32 RCPERecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(CTDA.IsLoaded())
        SaveHandler.writeSubRecord('ADTC', CTDA.value, CTDA.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(RCIL.IsLoaded())
        SaveHandler.writeSubRecord('LICR', RCIL.value, RCIL.GetSize());

    if(RCQY.IsLoaded())
        SaveHandler.writeSubRecord('YQCR', RCQY.value, RCQY.GetSize());

    if(RCOD.IsLoaded())
        SaveHandler.writeSubRecord('DOCR', RCOD.value, RCOD.GetSize());

    return -1;
    }

bool RCPERecord::operator ==(const RCPERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            CTDA == other.CTDA &&
            DATA == other.DATA &&
            RCIL == other.RCIL &&
            RCQY == other.RCQY &&
            RCOD == other.RCOD);
    }

bool RCPERecord::operator !=(const RCPERecord &other) const
    {
    return !(*this == other);
    }
}