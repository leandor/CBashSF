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
#include "CPTHRecord.h"

namespace FNV
{
CPTHRecord::CPTHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CPTHRecord::CPTHRecord(CPTHRecord *srcRecord):
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
    CTDA = srcRecord->CTDA;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    SNAM = srcRecord->SNAM;
    return;
    }

CPTHRecord::~CPTHRecord()
    {
    //
    }

bool CPTHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    //if(ANAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(ANAM->value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);

    return op.Stop();
    }

bool CPTHRecord::IsDefault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDefault);
    }

void CPTHRecord::IsDefault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDefault : eDummyDefault;
    }

bool CPTHRecord::IsDisable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDisable);
    }

void CPTHRecord::IsDisable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDisable : eDummyDefault;
    }

bool CPTHRecord::IsShotList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eShotList);
    }

void CPTHRecord::IsShotList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eShotList : eDummyDefault;
    }

bool CPTHRecord::IsType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void CPTHRecord::SetType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CPTHRecord::GetType()
    {
    return REV32(CPTH);
    }

STRING CPTHRecord::GetStrType()
    {
    return "CPTH";
    }

SINT32 CPTHRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CPTH: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 CPTHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    CTDA.Unload();
    ANAM.Unload();
    DATA.Unload();
    SNAM.Unload();
    return 1;
    }

SINT32 CPTHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(CTDA);
    WRITE(ANAM);
    WRITE(DATA);
    WRITE(SNAM);

    return -1;
    }

bool CPTHRecord::operator ==(const CPTHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            CTDA == other.CTDA &&
            ANAM == other.ANAM &&
            DATA == other.DATA &&
            SNAM == other.SNAM);
    }

bool CPTHRecord::operator !=(const CPTHRecord &other) const
    {
    return !(*this == other);
    }

bool CPTHRecord::equals(const Record *other) const
    {
    return *this == *(CPTHRecord *)other;
    }
}