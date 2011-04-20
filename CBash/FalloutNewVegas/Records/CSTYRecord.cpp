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
#include "CSTYRecord.h"

namespace FNV
{
CSTYRecord::CSTYRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CSTYRecord::CSTYRecord(CSTYRecord *srcRecord):
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
    CSTD = srcRecord->CSTD;
    CSAD = srcRecord->CSAD;
    CSSD = srcRecord->CSSD;
    return;
    }

CSTYRecord::~CSTYRecord()
    {
    //
    }

bool CSTYRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;


    return op.Stop();
    }

UINT32 CSTYRecord::GetSize(bool forceCalc)
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

    if(CSTD.IsLoaded())
        TotSize += CSTD.GetSize() + 6;

    if(CSAD.IsLoaded())
        TotSize += CSAD.GetSize() + 6;

    if(CSSD.IsLoaded())
        TotSize += CSSD.GetSize() + 6;

    return TotSize;
    }

UINT32 CSTYRecord::GetType()
    {
    return 'YTSC';
    }

STRING CSTYRecord::GetStrType()
    {
    return "CSTY";
    }

SINT32 CSTYRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'DTSC':
                CSTD.Read(buffer, subSize, curPos);
                break;
            case 'DASC':
                CSAD.Read(buffer, subSize, curPos);
                break;
            case 'DSSC':
                CSSD.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CSTY: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CSTYRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    CSTD.Unload();
    CSAD.Unload();
    CSSD.Unload();
    return 1;
    }

SINT32 CSTYRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(CSTD.IsLoaded())
        SaveHandler.writeSubRecord('DTSC', CSTD.value, CSTD.GetSize());

    if(CSAD.IsLoaded())
        SaveHandler.writeSubRecord('DASC', CSAD.value, CSAD.GetSize());

    if(CSSD.IsLoaded())
        SaveHandler.writeSubRecord('DSSC', CSSD.value, CSSD.GetSize());

    return -1;
    }

bool CSTYRecord::operator ==(const CSTYRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            CSTD == other.CSTD &&
            CSAD == other.CSAD &&
            CSSD == other.CSSD);
    }

bool CSTYRecord::operator !=(const CSTYRecord &other) const
    {
    return !(*this == other);
    }
}