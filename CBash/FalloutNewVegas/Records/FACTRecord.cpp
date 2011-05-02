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
bool sortRNAM::operator()(const FACTRecord::FACTRNAM *lhs, const FACTRecord::FACTRNAM *rhs) const
    {
    return lhs->RNAM.value < rhs->RNAM.value;
    }

FACTRecord::FACTDATA::FACTDATA():
    flags(0)
    {
    memset(&unused1, 0x00, 2);
    }

FACTRecord::FACTDATA::~FACTDATA()
    {
    //
    }

bool FACTRecord::FACTDATA::operator ==(const FACTDATA &other) const
    {
    return (flags == other.flags);
    }

bool FACTRecord::FACTDATA::operator !=(const FACTDATA &other) const
    {
    return !(*this == other);
    }

void FACTRecord::FACTRNAM::Write(FileWriter &writer)
    {
    WRITE(RNAM);
    WRITE(MNAM);
    WRITE(FNAM);
    WRITE(INAM);
    }

bool FACTRecord::FACTRNAM::operator ==(const FACTRNAM &other) const
    {
    return (RNAM == other.RNAM &&
            MNAM.equals(other.MNAM) &&
            FNAM.equals(other.FNAM) &&
            INAM.equalsi(other.INAM));
    }

bool FACTRecord::FACTRNAM::operator !=(const FACTRNAM &other) const
    {
    return !(*this == other);
    }

FACTRecord::FACTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

FACTRecord::FACTRecord(FACTRecord *srcRecord):
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
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    CNAM = srcRecord->CNAM;
    RNAM = srcRecord->RNAM;
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

    for(UINT32 x = 0; x < XNAM.value.size(); x++)
        op.Accept(XNAM.value[x]->faction);
    if(WMI1.IsLoaded())
        op.Accept(WMI1.value);

    return op.Stop();
    }

bool FACTRecord::IsHiddenFromPC()
    {
    return (DATA.value.flags & fIsHiddenFromPC) != 0;
    }

void FACTRecord::IsHiddenFromPC(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsHiddenFromPC) : (DATA.value.flags & ~fIsHiddenFromPC);
    }

bool FACTRecord::IsEvil()
    {
    return (DATA.value.flags & fIsEvil) != 0;
    }

void FACTRecord::IsEvil(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsEvil) : (DATA.value.flags & ~fIsEvil);
    }

bool FACTRecord::IsSpecialCombat()
    {
    return (DATA.value.flags & fIsSpecialCombat) != 0;
    }

void FACTRecord::IsSpecialCombat(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsSpecialCombat) : (DATA.value.flags & ~fIsSpecialCombat);
    }

bool FACTRecord::IsTrackCrime()
    {
    return (DATA.value.flags & fIsTrackCrime) != 0;
    }

void FACTRecord::IsTrackCrime(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsTrackCrime) : (DATA.value.flags & ~fIsTrackCrime);
    }

bool FACTRecord::IsAllowSell()
    {
    return (DATA.value.flags & fIsAllowSell) != 0;
    }

void FACTRecord::IsAllowSell(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsAllowSell) : (DATA.value.flags & ~fIsAllowSell);
    }

bool FACTRecord::IsFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void FACTRecord::SetFlagMask(UINT16 Mask)
    {
    DATA.value.flags = Mask;
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
                RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->MNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->INAM.Read(buffer, subSize, curPos);
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

SINT32 FACTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(XNAM);
    WRITE(DATA);
    WRITE(CNAM);
    RNAM.Write(writer);
    WRITE(WMI1);
    return -1;
    }

bool FACTRecord::operator ==(const FACTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
        FULL.equals(other.FULL) &&
        DATA == other.DATA &&
        CNAM == other.CNAM &&
        WMI1 == other.WMI1 &&
        XNAM == other.XNAM &&
        RNAM == other.RNAM);
    }

bool FACTRecord::operator !=(const FACTRecord &other) const
    {
    return !(*this == other);
    }
}