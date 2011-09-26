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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#include "..\..\Common.h"
#include "FACTRecord.h"

namespace Ob
{
bool sortRNAM::operator()(const FACTRecord::FACTRNAM *lhs, const FACTRecord::FACTRNAM *rhs) const
    {
    return lhs->RNAM.value < rhs->RNAM.value;
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    CNAM = srcRecord->CNAM;
    RNAM = srcRecord->RNAM;
    }

FACTRecord::~FACTRecord()
    {
    //
    }

bool FACTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < XNAM.value.size(); ListIndex++)
        op.Accept(XNAM.value[ListIndex]->faction);

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
    return REV32(FACT);
    }

STRING FACTRecord::GetStrType()
    {
    return "FACT";
    }

SINT32 FACTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->RNAM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->MNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FNAM):
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->FNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(INAM):
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->INAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  FACT: Unknown subType = %04X\n", subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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
    return 1;
    }

SINT32 FACTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    XNAM.Write(REV32(XNAM), writer, true);
    WRITE(DATA);
    WRITE(CNAM);
    RNAM.Write(writer);
    return -1;
    }

bool FACTRecord::operator ==(const FACTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA &&
            CNAM == other.CNAM &&
            XNAM == other.XNAM &&
            RNAM == other.RNAM);
    }

bool FACTRecord::operator !=(const FACTRecord &other) const
    {
    return !(*this == other);
    }

bool FACTRecord::equals(Record *other)
    {
    return *this == *(FACTRecord *)other;
    }
}