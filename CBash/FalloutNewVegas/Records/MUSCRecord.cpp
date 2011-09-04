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
#include "MUSCRecord.h"

namespace FNV
{
MUSCRecord::MUSCRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

MUSCRecord::MUSCRecord(MUSCRecord *srcRecord):
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
    FNAM = srcRecord->FNAM;
    ANAM = srcRecord->ANAM;
    return;
    }

MUSCRecord::~MUSCRecord()
    {
    //
    }

bool MUSCRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

UINT32 MUSCRecord::GetType()
    {
    return REV32(MUSC);
    }

STRING MUSCRecord::GetStrType()
    {
    return "MUSC";
    }

SINT32 MUSCRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  MUSC: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 MUSCRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FNAM.Unload();
    ANAM.Unload();
    return 1;
    }

SINT32 MUSCRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FNAM);
    WRITE(ANAM);

    return -1;
    }

bool MUSCRecord::operator ==(const MUSCRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FNAM.equalsi(other.FNAM) &&
            ANAM == other.ANAM);
    }

bool MUSCRecord::operator !=(const MUSCRecord &other) const
    {
    return !(*this == other);
    }

bool MUSCRecord::equals(const Record *other) const
    {
    return *this == *(MUSCRecord *)other;
    }
}