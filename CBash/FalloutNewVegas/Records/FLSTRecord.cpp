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
#include "FLSTRecord.h"

namespace FNV
{
FLSTRecord::FLSTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

FLSTRecord::FLSTRecord(FLSTRecord *srcRecord):
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
        return;

    EDID = srcRecord->EDID;
    LNAM = srcRecord->LNAM;
    return;
    }

FLSTRecord::~FLSTRecord()
    {
    //
    }

bool FLSTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(LNAM.IsLoaded())
        op.Accept(LNAM->value);

    return op.Stop();
    }

UINT32 FLSTRecord::GetType()
    {
    return REV32(FLST);
    }

STRING FLSTRecord::GetStrType()
    {
    return "FLST";
    }

SINT32 FLSTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  FLST: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 FLSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    LNAM.Unload();
    return 1;
    }

SINT32 FLSTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(LNAM);

    return -1;
    }

bool FLSTRecord::operator ==(const FLSTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            LNAM == other.LNAM);
    }

bool FLSTRecord::operator !=(const FLSTRecord &other) const
    {
    return !(*this == other);
    }

bool FLSTRecord::equals(const Record *other) const
    {
    return *this == *(FLSTRecord *)other;
    }
}