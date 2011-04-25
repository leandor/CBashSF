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
#include "MSETRecord.h"

namespace FNV
{
MSETRecord::MSETRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

MSETRecord::MSETRecord(MSETRecord *srcRecord):
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
    NAM8 = srcRecord->NAM8;
    NAM9 = srcRecord->NAM9;
    NAM0 = srcRecord->NAM0;
    ANAM = srcRecord->ANAM;
    BNAM = srcRecord->BNAM;
    CNAM = srcRecord->CNAM;
    JNAM = srcRecord->JNAM;
    KNAM = srcRecord->KNAM;
    LNAM = srcRecord->LNAM;
    MNAM = srcRecord->MNAM;
    NNAM = srcRecord->NNAM;
    ONAM = srcRecord->ONAM;
    PNAM = srcRecord->PNAM;
    DNAM = srcRecord->DNAM;
    ENAM = srcRecord->ENAM;
    FNAM = srcRecord->FNAM;
    GNAM = srcRecord->GNAM;
    HNAM = srcRecord->HNAM;
    INAM = srcRecord->INAM;
    DATA = srcRecord->DATA;
    return;
    }

MSETRecord::~MSETRecord()
    {
    //
    }

bool MSETRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(HNAM.IsLoaded())
        op.Accept(HNAM->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);

    return op.Stop();
    }

bool MSETRecord::IsDayOuter()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDayOuter) != 0;
    }

void MSETRecord::IsDayOuter(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDayOuter;
    else
        Dummy->flags &= ~fIsDayOuter;
    }

bool MSETRecord::IsDayMiddle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDayMiddle) != 0;
    }

void MSETRecord::IsDayMiddle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDayMiddle;
    else
        Dummy->flags &= ~fIsDayMiddle;
    }

bool MSETRecord::IsDayInner()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDayInner) != 0;
    }

void MSETRecord::IsDayInner(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDayInner;
    else
        Dummy->flags &= ~fIsDayInner;
    }

bool MSETRecord::IsNightOuter()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNightOuter) != 0;
    }

void MSETRecord::IsNightOuter(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNightOuter;
    else
        Dummy->flags &= ~fIsNightOuter;
    }

bool MSETRecord::IsNightMiddle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNightMiddle) != 0;
    }

void MSETRecord::IsNightMiddle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNightMiddle;
    else
        Dummy->flags &= ~fIsNightMiddle;
    }

bool MSETRecord::IsNightInner()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNightInner) != 0;
    }

void MSETRecord::IsNightInner(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNightInner;
    else
        Dummy->flags &= ~fIsNightInner;
    }

bool MSETRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void MSETRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool MSETRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void MSETRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eNone;
    else
        Dummy->flags = eDummyDefault;
    }

bool MSETRecord::IsBattle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBattle);
    }

void MSETRecord::IsBattle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eBattle;
    else
        Dummy->flags = eDummyDefault;
    }

bool MSETRecord::IsLocation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLocation);
    }

void MSETRecord::IsLocation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eLocation;
    else
        Dummy->flags = eDummyDefault;
    }

bool MSETRecord::IsDungeon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDungeon);
    }

void MSETRecord::IsDungeon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDungeon;
    else
        Dummy->flags = eDummyDefault;
    }

bool MSETRecord::IsIncidential()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIncidential);
    }

void MSETRecord::IsIncidential(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eIncidential;
    else
        Dummy->flags = eDummyDefault;
    }

bool MSETRecord::IsType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void MSETRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 MSETRecord::GetSize(bool forceCalc)
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

    if(NAM1.IsLoaded())
        TotSize += NAM1.GetSize() + 6;

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
        {
        cSize = NAM4.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM5.IsLoaded())
        {
        cSize = NAM5.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM6.IsLoaded())
        {
        cSize = NAM6.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM7.IsLoaded())
        {
        cSize = NAM7.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM8.IsLoaded())
        TotSize += NAM8.GetSize() + 6;

    if(NAM9.IsLoaded())
        TotSize += NAM9.GetSize() + 6;

    if(NAM0.IsLoaded())
        TotSize += NAM0.GetSize() + 6;

    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;

    if(BNAM.IsLoaded())
        TotSize += BNAM.GetSize() + 6;

    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;

    if(JNAM.IsLoaded())
        TotSize += JNAM.GetSize() + 6;

    if(KNAM.IsLoaded())
        TotSize += KNAM.GetSize() + 6;

    if(LNAM.IsLoaded())
        TotSize += LNAM.GetSize() + 6;

    if(MNAM.IsLoaded())
        TotSize += MNAM.GetSize() + 6;

    if(NNAM.IsLoaded())
        TotSize += NNAM.GetSize() + 6;

    if(ONAM.IsLoaded())
        TotSize += ONAM.GetSize() + 6;

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    if(ENAM.IsLoaded())
        TotSize += ENAM.GetSize() + 6;

    if(FNAM.IsLoaded())
        TotSize += FNAM.GetSize() + 6;

    if(GNAM.IsLoaded())
        TotSize += GNAM.GetSize() + 6;

    if(HNAM.IsLoaded())
        TotSize += HNAM.GetSize() + 6;

    if(INAM.IsLoaded())
        TotSize += INAM.GetSize() + 6;

    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

UINT32 MSETRecord::GetType()
    {
    return 'TESM';
    }

STRING MSETRecord::GetStrType()
    {
    return "MSET";
    }

SINT32 MSETRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case '8MAN':
                NAM8.Read(buffer, subSize, curPos);
                break;
            case '9MAN':
                NAM9.Read(buffer, subSize, curPos);
                break;
            case '0MAN':
                NAM0.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'MANB':
                BNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANJ':
                JNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANK':
                KNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANL':
                LNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                MNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANN':
                NNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                ONAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANE':
                ENAM.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANG':
                GNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  MSET: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 MSETRecord::Unload()
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
    NAM8.Unload();
    NAM9.Unload();
    NAM0.Unload();
    ANAM.Unload();
    BNAM.Unload();
    CNAM.Unload();
    JNAM.Unload();
    KNAM.Unload();
    LNAM.Unload();
    MNAM.Unload();
    NNAM.Unload();
    ONAM.Unload();
    PNAM.Unload();
    DNAM.Unload();
    ENAM.Unload();
    FNAM.Unload();
    GNAM.Unload();
    HNAM.Unload();
    INAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 MSETRecord::WriteRecord(_FileHandler &SaveHandler)
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

    if(NAM8.IsLoaded())
        SaveHandler.writeSubRecord('8MAN', NAM8.value, NAM8.GetSize());

    if(NAM9.IsLoaded())
        SaveHandler.writeSubRecord('9MAN', NAM9.value, NAM9.GetSize());

    if(NAM0.IsLoaded())
        SaveHandler.writeSubRecord('0MAN', NAM0.value, NAM0.GetSize());

    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord('MANA', ANAM.value, ANAM.GetSize());

    if(BNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANB', BNAM.value, BNAM.GetSize());

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());

    if(JNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANJ', JNAM.value, JNAM.GetSize());

    if(KNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANK', KNAM.value, KNAM.GetSize());

    if(LNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANL', LNAM.value, LNAM.GetSize());

    if(MNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANM', MNAM.value, MNAM.GetSize());

    if(NNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANN', NNAM.value, NNAM.GetSize());

    if(ONAM.IsLoaded())
        SaveHandler.writeSubRecord('MANO', ONAM.value, ONAM.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', PNAM.value, PNAM.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    if(ENAM.IsLoaded())
        SaveHandler.writeSubRecord('MANE', ENAM.value, ENAM.GetSize());

    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANF', FNAM.value, FNAM.GetSize());

    if(GNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANG', GNAM.value, GNAM.GetSize());

    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANH', HNAM.value, HNAM.GetSize());

    if(INAM.IsLoaded())
        SaveHandler.writeSubRecord('MANI', INAM.value, INAM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    return -1;
    }

bool MSETRecord::operator ==(const MSETRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NAM1 == other.NAM1 &&
            NAM2.equalsi(other.NAM2) &&
            NAM3.equalsi(other.NAM3) &&
            NAM4.equalsi(other.NAM4) &&
            NAM5.equalsi(other.NAM5) &&
            NAM6.equalsi(other.NAM6) &&
            NAM7.equalsi(other.NAM7) &&
            NAM8 == other.NAM8 &&
            NAM9 == other.NAM9 &&
            NAM0 == other.NAM0 &&
            ANAM == other.ANAM &&
            BNAM == other.BNAM &&
            CNAM == other.CNAM &&
            JNAM == other.JNAM &&
            KNAM == other.KNAM &&
            LNAM == other.LNAM &&
            MNAM == other.MNAM &&
            NNAM == other.NNAM &&
            ONAM == other.ONAM &&
            PNAM == other.PNAM &&
            DNAM == other.DNAM &&
            ENAM == other.ENAM &&
            FNAM == other.FNAM &&
            GNAM == other.GNAM &&
            HNAM == other.HNAM &&
            INAM == other.INAM &&
            DATA == other.DATA);
    }

bool MSETRecord::operator !=(const MSETRecord &other) const
    {
    return !(*this == other);
    }
}