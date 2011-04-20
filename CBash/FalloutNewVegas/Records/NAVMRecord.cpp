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
#include "NAVMRecord.h"

namespace FNV
{
NAVMRecord::NAVMRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

NAVMRecord::NAVMRecord(NAVMRecord *srcRecord):
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
    NVVX = srcRecord->NVVX;
    NVTR = srcRecord->NVTR;
    NVCA = srcRecord->NVCA;
    NVDP = srcRecord->NVDP;
    NVGD = srcRecord->NVGD;
    NVEX = srcRecord->NVEX;
    return;
    }

NAVMRecord::~NAVMRecord()
    {
    //
    }

bool NAVMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);
    //if(NVDP.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(NVDP->value);
    //if(NVEX.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(NVEX->value);

    return op.Stop();
    }

UINT32 NAVMRecord::GetSize(bool forceCalc)
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

    if(NVVX.IsLoaded())
        TotSize += NVVX.GetSize() + 6;

    if(NVTR.IsLoaded())
        TotSize += NVTR.GetSize() + 6;

    if(NVCA.IsLoaded())
        TotSize += NVCA.GetSize() + 6;

    if(NVDP.IsLoaded())
        TotSize += NVDP.GetSize() + 6;

    if(NVGD.IsLoaded())
        TotSize += NVGD.GetSize() + 6;

    if(NVEX.IsLoaded())
        TotSize += NVEX.GetSize() + 6;

    return TotSize;
    }

UINT32 NAVMRecord::GetType()
    {
    return 'MVAN';
    }

STRING NAVMRecord::GetStrType()
    {
    return "NAVM";
    }

SINT32 NAVMRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'XVVN':
                NVVX.Read(buffer, subSize, curPos);
                break;
            case 'RTVN':
                NVTR.Read(buffer, subSize, curPos);
                break;
            case 'ACVN':
                NVCA.Read(buffer, subSize, curPos);
                break;
            case 'PDVN':
                NVDP.Read(buffer, subSize, curPos);
                break;
            case 'DGVN':
                NVGD.Read(buffer, subSize, curPos);
                break;
            case 'XEVN':
                NVEX.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  NAVM: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 NAVMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NVER.Unload();
    DATA.Unload();
    NVVX.Unload();
    NVTR.Unload();
    NVCA.Unload();
    NVDP.Unload();
    NVGD.Unload();
    NVEX.Unload();
    return 1;
    }

SINT32 NAVMRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(NVER.IsLoaded())
        SaveHandler.writeSubRecord('REVN', NVER.value, NVER.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(NVVX.IsLoaded())
        SaveHandler.writeSubRecord('XVVN', NVVX.value, NVVX.GetSize());

    if(NVTR.IsLoaded())
        SaveHandler.writeSubRecord('RTVN', NVTR.value, NVTR.GetSize());

    if(NVCA.IsLoaded())
        SaveHandler.writeSubRecord('ACVN', NVCA.value, NVCA.GetSize());

    if(NVDP.IsLoaded())
        SaveHandler.writeSubRecord('PDVN', NVDP.value, NVDP.GetSize());

    if(NVGD.IsLoaded())
        SaveHandler.writeSubRecord('DGVN', NVGD.value, NVGD.GetSize());

    if(NVEX.IsLoaded())
        SaveHandler.writeSubRecord('XEVN', NVEX.value, NVEX.GetSize());

    return -1;
    }

bool NAVMRecord::operator ==(const NAVMRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            DATA == other.DATA &&
            NVVX == other.NVVX &&
            NVTR == other.NVTR &&
            NVCA == other.NVCA &&
            NVDP == other.NVDP &&
            NVGD == other.NVGD &&
            NVEX == other.NVEX);
    }

bool NAVMRecord::operator !=(const NAVMRecord &other) const
    {
    return !(*this == other);
    }
}