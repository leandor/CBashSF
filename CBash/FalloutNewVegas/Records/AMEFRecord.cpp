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
#include "AMEFRecord.h"

namespace FNV
{
AMEFRecord::AMEFRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

AMEFRecord::AMEFRecord(AMEFRecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    return;
    }

AMEFRecord::~AMEFRecord()
    {
    //
    }

bool AMEFRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

bool AMEFRecord::IsDamage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDamage);
    }

void AMEFRecord::IsDamage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDamage : eDummyDefault;
    }

bool AMEFRecord::IsDR()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDR);
    }

void AMEFRecord::IsDR(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDR : eDummyDefault;
    }

bool AMEFRecord::IsDT()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDT);
    }

void AMEFRecord::IsDT(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDT : eDummyDefault;
    }

bool AMEFRecord::IsSpread()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSpread);
    }

void AMEFRecord::IsSpread(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSpread : eDummyDefault;
    }

bool AMEFRecord::IsCondition()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCondition);
    }

void AMEFRecord::IsCondition(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCondition : eDummyDefault;
    }

bool AMEFRecord::IsFatigue()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFatigue);
    }

void AMEFRecord::IsFatigue(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFatigue : eDummyDefault;
    }

bool AMEFRecord::IsModType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void AMEFRecord::SetModType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool AMEFRecord::IsAdd()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAdd);
    }

void AMEFRecord::IsAdd(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAdd : eDummyDefault;
    }

bool AMEFRecord::IsMultiply()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMultiply);
    }

void AMEFRecord::IsMultiply(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMultiply : eDummyDefault;
    }

bool AMEFRecord::IsSubtract()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSubtract);
    }

void AMEFRecord::IsSubtract(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSubtract : eDummyDefault;
    }

bool AMEFRecord::IsOpType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void AMEFRecord::SetOpType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 AMEFRecord::GetType()
    {
    return REV32(AMEF);
    }

STRING AMEFRecord::GetStrType()
    {
    return "AMEF";
    }

SINT32 AMEFRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                EDID.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  AMEF: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 AMEFRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 AMEFRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DATA);

    return -1;
    }

bool AMEFRecord::operator ==(const AMEFRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA);
    }

bool AMEFRecord::operator !=(const AMEFRecord &other) const
    {
    return !(*this == other);
    }

bool AMEFRecord::equals(const Record *other) const
    {
    return *this == *(AMEFRecord *)other;
    }
}