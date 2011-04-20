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
#include "ALOCRecord.h"

namespace FNV
{
ALOCRecord::ALOCRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ALOCRecord::ALOCRecord(ALOCRecord *srcRecord):
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
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    NAM3 = srcRecord->NAM3;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    NAM6 = srcRecord->NAM6;
    NAM7 = srcRecord->NAM7;
    HNAM = srcRecord->HNAM;
    ZNAM = srcRecord->ZNAM;
    XNAM = srcRecord->XNAM;
    YNAM = srcRecord->YNAM;
    LNAM = srcRecord->LNAM;
    GNAM = srcRecord->GNAM;
    RNAM = srcRecord->RNAM;
    FNAM = srcRecord->FNAM;
    return;
    }

ALOCRecord::~ALOCRecord()
    {
    //
    }

bool ALOCRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(HNAM.IsLoaded())
        op.Accept(HNAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    if(XNAM.IsLoaded())
        op.Accept(XNAM->value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    if(LNAM.IsLoaded())
        op.Accept(LNAM->value);
    if(GNAM.IsLoaded())
        op.Accept(GNAM->value);
    if(RNAM.IsLoaded())
        op.Accept(RNAM->value);

    return op.Stop();
    }

UINT32 ALOCRecord::GetSize(bool forceCalc)
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

    if(NAM1.IsLoaded())
        {
        cSize = NAM1.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM2.IsLoaded())
        {
        cSize = NAM2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM3.IsLoaded())
        {
        cSize = NAM3.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM4.IsLoaded())
        TotSize += NAM4.GetSize() + 6;

    if(NAM5.IsLoaded())
        TotSize += NAM5.GetSize() + 6;

    if(NAM6.IsLoaded())
        TotSize += NAM6.GetSize() + 6;

    if(NAM7.IsLoaded())
        TotSize += NAM7.GetSize() + 6;

    if(HNAM.IsLoaded())
        TotSize += HNAM.GetSize() + 6;

    if(ZNAM.IsLoaded())
        TotSize += ZNAM.GetSize() + 6;

    if(XNAM.IsLoaded())
        TotSize += XNAM.GetSize() + 6;

    if(YNAM.IsLoaded())
        TotSize += YNAM.GetSize() + 6;

    if(LNAM.IsLoaded())
        TotSize += LNAM.GetSize() + 6;

    if(GNAM.IsLoaded())
        TotSize += GNAM.GetSize() + 6;

    if(RNAM.IsLoaded())
        TotSize += RNAM.GetSize() + 6;

    if(FNAM.IsLoaded())
        {
        cSize = FNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

UINT32 ALOCRecord::GetType()
    {
    return 'COLA';
    }

STRING ALOCRecord::GetStrType()
    {
    return "ALOC";
    }

SINT32 ALOCRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case '1MAN':
                NAM1.Read(buffer, subSize, curPos);
                break;
            case '2MAN':
                NAM2.Read(buffer, subSize, curPos);
                break;
            case '3MAN':
                NAM3.Read(buffer, subSize, curPos);
                break;
            case '4MAN':
                NAM4.Read(buffer, subSize, curPos);
                break;
            case '5MAN':
                NAM5.Read(buffer, subSize, curPos);
                break;
            case '6MAN':
                NAM6.Read(buffer, subSize, curPos);
                break;
            case '7MAN':
                NAM7.Read(buffer, subSize, curPos);
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANL':
                LNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANG':
                GNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ALOC: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 ALOCRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    NAM1.Unload();
    NAM2.Unload();
    NAM3.Unload();
    NAM4.Unload();
    NAM5.Unload();
    NAM6.Unload();
    NAM7.Unload();
    HNAM.Unload();
    ZNAM.Unload();
    XNAM.Unload();
    YNAM.Unload();
    LNAM.Unload();
    GNAM.Unload();
    RNAM.Unload();
    FNAM.Unload();
    return 1;
    }

SINT32 ALOCRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(NAM1.IsLoaded())
        SaveHandler.writeSubRecord('1MAN', NAM1.value, NAM1.GetSize());

    if(NAM2.IsLoaded())
        SaveHandler.writeSubRecord('2MAN', NAM2.value, NAM2.GetSize());

    if(NAM3.IsLoaded())
        SaveHandler.writeSubRecord('3MAN', NAM3.value, NAM3.GetSize());

    if(NAM4.IsLoaded())
        SaveHandler.writeSubRecord('4MAN', NAM4.value, NAM4.GetSize());

    if(NAM5.IsLoaded())
        SaveHandler.writeSubRecord('5MAN', NAM5.value, NAM5.GetSize());

    if(NAM6.IsLoaded())
        SaveHandler.writeSubRecord('6MAN', NAM6.value, NAM6.GetSize());

    if(NAM7.IsLoaded())
        SaveHandler.writeSubRecord('7MAN', NAM7.value, NAM7.GetSize());

    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANH', HNAM.value, HNAM.GetSize());

    if(ZNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANZ', ZNAM.value, ZNAM.GetSize());

    if(XNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANX', XNAM.value, XNAM.GetSize());

    if(YNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANY', YNAM.value, YNAM.GetSize());

    if(LNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANL', LNAM.value, LNAM.GetSize());

    if(GNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANG', GNAM.value, GNAM.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANF', FNAM.value, FNAM.GetSize());

    return -1;
    }

bool ALOCRecord::operator ==(const ALOCRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NAM1 == other.NAM1 &&
            NAM2 == other.NAM2 &&
            NAM3 == other.NAM3 &&
            NAM4 == other.NAM4 &&
            NAM5 == other.NAM5 &&
            NAM6 == other.NAM6 &&
            NAM7 == other.NAM7 &&
            HNAM == other.HNAM &&
            ZNAM == other.ZNAM &&
            XNAM == other.XNAM &&
            YNAM == other.YNAM &&
            LNAM == other.LNAM &&
            GNAM == other.GNAM &&
            RNAM == other.RNAM &&
            FNAM == other.FNAM);
    }

bool ALOCRecord::operator !=(const ALOCRecord &other) const
    {
    return !(*this == other);
    }
}