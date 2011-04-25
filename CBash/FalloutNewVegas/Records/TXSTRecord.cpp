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
#include "TXSTRecord.h"

namespace FNV
{
TXSTRecord::TXSTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

TXSTRecord::TXSTRecord(TXSTRecord *srcRecord):
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
    OBND = srcRecord->OBND;

    TX00 = srcRecord->TX00;
    TX01 = srcRecord->TX01;
    TX02 = srcRecord->TX02;
    TX03 = srcRecord->TX03;
    TX04 = srcRecord->TX04;
    TX05 = srcRecord->TX05;

    DODT = srcRecord->DODT;
    DNAM = srcRecord->DNAM;
    return;
    }

TXSTRecord::~TXSTRecord()
    {
    //
    }

bool TXSTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;


    return op.Stop();
    }

bool TXSTRecord::IsNoSpecularMap()
    {
    return DNAM.IsLoaded() ? (DNAM.value.value & fIsNoSpecularMap) != 0 : false;
    }

void TXSTRecord::IsNoSpecularMap(bool value)
    {
    if(!DNAM.IsLoaded()) return;
    DNAM.value.value = value ? (DNAM.value.value | fIsNoSpecularMap) : (DNAM.value.value & ~fIsNoSpecularMap);
    }

bool TXSTRecord::IsFlagMask(UINT16 Mask, bool Exact)
    {
    if(!DNAM.IsLoaded()) return false;
    return Exact ? ((DNAM.value.value & Mask) == Mask) : ((DNAM.value.value & Mask) != 0);
    }

void TXSTRecord::SetFlagMask(UINT16 Mask)
    {
    DNAM.Load();
    DNAM.value.value = Mask;
    }

UINT32 TXSTRecord::GetSize(bool forceCalc)
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

    if(OBND.IsLoaded())
        TotSize += OBND.GetSize() + 6;

    if(TX00.IsLoaded())
        {
        cSize = TX00.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(TX01.IsLoaded())
        {
        cSize = TX01.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(TX02.IsLoaded())
        {
        cSize = TX02.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(TX03.IsLoaded())
        {
        cSize = TX03.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(TX04.IsLoaded())
        {
        cSize = TX04.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(TX05.IsLoaded())
        {
        cSize = TX05.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DODT.IsLoaded())
        TotSize += DODT.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 TXSTRecord::GetType()
    {
    return 'TSXT';
    }

STRING TXSTRecord::GetStrType()
    {
    return "TXST";
    }

SINT32 TXSTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'DNBO':
                OBND.Read(buffer, subSize, curPos);
                break;
            case '00XT':
                TX00.Read(buffer, subSize, curPos);
                break;
            case '10XT':
                TX01.Read(buffer, subSize, curPos);
                break;
            case '20XT':
                TX02.Read(buffer, subSize, curPos);
                break;
            case '30XT':
                TX03.Read(buffer, subSize, curPos);
                break;
            case '40XT':
                TX04.Read(buffer, subSize, curPos);
                break;
            case '50XT':
                TX05.Read(buffer, subSize, curPos);
                break;
            case 'TDOD':
                DODT.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  TXST: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 TXSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    TX00.Unload();
    TX01.Unload();
    TX02.Unload();
    TX03.Unload();
    TX04.Unload();
    TX05.Unload();
    DODT.Unload();
    DNAM.Unload();
    return 1;
    }

SINT32 TXSTRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(TX00.IsLoaded())
        SaveHandler.writeSubRecord('00XT', TX00.value, TX00.GetSize());

    if(TX01.IsLoaded())
        SaveHandler.writeSubRecord('10XT', TX01.value, TX01.GetSize());

    if(TX02.IsLoaded())
        SaveHandler.writeSubRecord('20XT', TX02.value, TX02.GetSize());

    if(TX03.IsLoaded())
        SaveHandler.writeSubRecord('30XT', TX03.value, TX03.GetSize());

    if(TX04.IsLoaded())
        SaveHandler.writeSubRecord('40XT', TX04.value, TX04.GetSize());

    if(TX05.IsLoaded())
        SaveHandler.writeSubRecord('50XT', TX05.value, TX05.GetSize());

    if(DODT.IsLoaded())
        SaveHandler.writeSubRecord('TDOD', DODT.value, DODT.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());
    return -1;
    }

bool TXSTRecord::operator ==(const TXSTRecord &other) const
    {
    return (OBND == other.OBND &&
            DODT == other.DODT &&
            DNAM == other.DNAM &&
            EDID.equalsi(other.EDID) &&
            TX00.equalsi(other.TX00) &&
            TX01.equalsi(other.TX01) &&
            TX02.equalsi(other.TX02) &&
            TX03.equalsi(other.TX03) &&
            TX04.equalsi(other.TX04) &&
            TX05.equalsi(other.TX05)
            );
    }

bool TXSTRecord::operator !=(const TXSTRecord &other) const
    {
    return !(*this == other);
    }
}