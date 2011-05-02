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

bool sortRNAM(FACTRecord::FACTRNAM *lhs, FACTRecord::FACTRNAM *rhs)
    {
    return lhs->RNAM.value < rhs->RNAM.value;
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
    Record(_recData)
    {
    //
    }

FACTRecord::FACTRecord(FACTRecord *srcRecord):
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

    XNAM.clear();
    XNAM.resize(srcRecord->XNAM.size());
    for(UINT32 x = 0; x < srcRecord->XNAM.size(); x++)
        {
        XNAM[x] = new ReqSubRecord<GENXNAM>;
        *XNAM[x] = *srcRecord->XNAM[x];
        }

    DATA = srcRecord->DATA;
    CNAM = srcRecord->CNAM;

    RNAM.clear();
    RNAM.resize(srcRecord->RNAM.size());
    for(UINT32 x = 0; x < srcRecord->RNAM.size(); x++)
        {
        RNAM[x] = new FACTRNAM;
        *RNAM[x] = *srcRecord->RNAM[x];
        }
    }

FACTRecord::~FACTRecord()
    {
    for(UINT32 x = 0; x < XNAM.size(); x++)
        delete XNAM[x];
    for(UINT32 x = 0; x < RNAM.size(); x++)
        delete RNAM[x];
    }

bool FACTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < XNAM.size(); x++)
        op.Accept(XNAM[x]->value.faction);

    return op.Stop();
    }

bool FACTRecord::IsHiddenFromPC()
    {
    return (DATA.value & fIsHiddenFromPC) != 0;
    }

void FACTRecord::IsHiddenFromPC(bool value)
    {
    DATA.value = value ? (DATA.value | fIsHiddenFromPC) : (DATA.value & ~fIsHiddenFromPC);
    }

bool FACTRecord::IsEvil()
    {
    return (DATA.value & fIsEvil) != 0;
    }

void FACTRecord::IsEvil(bool value)
    {
    DATA.value = value ? (DATA.value | fIsEvil) : (DATA.value & ~fIsEvil);
    }

bool FACTRecord::IsSpecialCombat()
    {
    return (DATA.value & fIsSpecialCombat) != 0;
    }

void FACTRecord::IsSpecialCombat(bool value)
    {
    DATA.value = value ? (DATA.value | fIsSpecialCombat) : (DATA.value & ~fIsSpecialCombat);
    }

bool FACTRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void FACTRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value = Mask;
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
                XNAM.push_back(new ReqSubRecord<GENXNAM>);
                XNAM.back()->Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.push_back(new FACTRNAM);
                RNAM.back()->RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                if(RNAM.size() == 0)
                    RNAM.push_back(new FACTRNAM);
                RNAM.back()->MNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                if(RNAM.size() == 0)
                    RNAM.push_back(new FACTRNAM);
                RNAM.back()->FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                if(RNAM.size() == 0)
                    RNAM.push_back(new FACTRNAM);
                RNAM.back()->INAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  FACT: Unknown subType = %04X\n", subType);
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

    for(UINT32 x = 0; x < XNAM.size(); x++)
        delete XNAM[x];
    XNAM.clear();

    DATA.Unload();
    CNAM.Unload();

    for(UINT32 x = 0; x < RNAM.size(); x++)
        delete RNAM[x];
    RNAM.clear();
    return 1;
    }

SINT32 FACTRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord('DIDE', EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        writer.record_write_subrecord('LLUF', FULL.value, FULL.GetSize());
    for(UINT32 p = 0; p < XNAM.size(); p++)
        if(XNAM[p]->IsLoaded())
            writer.record_write_subrecord('MANX', &XNAM[p]->value, XNAM[p]->GetSize());

    if(DATA.IsLoaded())
        writer.record_write_subrecord('ATAD', &DATA.value, DATA.GetSize());
    if(CNAM.IsLoaded())
        writer.record_write_subrecord('MANC', CNAM.value, CNAM.GetSize());

    std::sort(RNAM.begin(), RNAM.end(), sortRNAM);
    for(UINT32 p = 0; p < RNAM.size(); p++)
        {
        writer.record_write_subrecord('MANR', &RNAM[p]->RNAM.value, RNAM[p]->RNAM.GetSize());
        if(RNAM[p]->MNAM.IsLoaded())
            writer.record_write_subrecord('MANM', RNAM[p]->MNAM.value, RNAM[p]->MNAM.GetSize());
        if(RNAM[p]->FNAM.IsLoaded())
            writer.record_write_subrecord('MANF', RNAM[p]->FNAM.value, RNAM[p]->FNAM.GetSize());
        if(RNAM[p]->INAM.IsLoaded())
            writer.record_write_subrecord('MANI', RNAM[p]->INAM.value, RNAM[p]->INAM.GetSize());
        }
    return -1;
    }

bool FACTRecord::operator ==(const FACTRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        FULL.equals(other.FULL) &&
        DATA == other.DATA &&
        CNAM == other.CNAM &&
        XNAM.size() == other.XNAM.size() &&
        RNAM.size() == other.RNAM.size())
        {
        //Not sure if record order matters on relations, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < XNAM.size(); ++x)
            if(*XNAM[x] != *other.XNAM[x])
                return false;

        //Record order doesn't matter on faction ranks, so equality testing isn't easy
        //Instead, they're keyed by faction rank (RNAM.value.RNAM)
        //The proper solution would be to see if each rank matches the other
        //But they're usually ordered, so the lazy approach is to not bother
        //Fix-up later
        for(UINT32 x = 0; x < RNAM.size(); ++x)
            if(*RNAM[x] != *other.RNAM[x])
                return false;
        return true;
        }
    return false;
    }

bool FACTRecord::operator !=(const FACTRecord &other) const
    {
    return !(*this == other);
    }