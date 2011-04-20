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
#include "LTEXRecord.h"

namespace FNV
{
LTEXRecord::LTEXRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LTEXRecord::LTEXRecord(LTEXRecord *srcRecord):
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
    if(srcRecord->ICON.IsLoaded())
        {
        ICON.Load();
        ICON->ICON = srcRecord->ICON->ICON;
        ICON->MICO = srcRecord->ICON->MICO;
        }
    TNAM = srcRecord->TNAM;
    HNAM = srcRecord->HNAM;
    SNAM = srcRecord->SNAM;
    GNAM = srcRecord->GNAM;
    return;
    }

LTEXRecord::~LTEXRecord()
    {
    //
    }

bool LTEXRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(TNAM.IsLoaded())
        op.Accept(TNAM->value);
    if(GNAM.IsLoaded())
        op.Accept(GNAM->value);

    return op.Stop();
    }

UINT32 LTEXRecord::GetSize(bool forceCalc)
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

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            {
            cSize = ICON->ICON.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(ICON->MICO.IsLoaded())
            {
            cSize = ICON->MICO.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;

    if(HNAM.IsLoaded())
        TotSize += HNAM.GetSize() + 6;

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(GNAM.IsLoaded())
        TotSize += GNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 LTEXRecord::GetType()
    {
    return 'XETL';
    }

STRING LTEXRecord::GetStrType()
    {
    return "LTEX";
    }

SINT32 LTEXRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'NOCI':
                ICON.Load();
                ICON->ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                ICON.Load();
                ICON->MICO.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANG':
                GNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LTEX: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 LTEXRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    TNAM.Unload();
    HNAM.Unload();
    SNAM.Unload();
    GNAM.Unload();
    return 1;
    }

SINT32 LTEXRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            SaveHandler.writeSubRecord('NOCI', ICON->ICON.value, ICON->ICON.GetSize());

        if(ICON->MICO.IsLoaded())
            SaveHandler.writeSubRecord('OCIM', ICON->MICO.value, ICON->MICO.GetSize());

        }

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANT', TNAM.value, TNAM.GetSize());

    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANH', HNAM.value, HNAM.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(GNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANG', GNAM.value, GNAM.GetSize());

    return -1;
    }

bool LTEXRecord::operator ==(const LTEXRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON == other.ICON &&
            TNAM == other.TNAM &&
            HNAM == other.HNAM &&
            SNAM == other.SNAM &&
            GNAM == other.GNAM);
    }

bool LTEXRecord::operator !=(const LTEXRecord &other) const
    {
    return !(*this == other);
    }
}