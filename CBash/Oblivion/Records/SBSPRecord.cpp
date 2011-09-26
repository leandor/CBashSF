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
#include "SBSPRecord.h"

namespace Ob
{
SBSPRecord::SBSPDNAM::SBSPDNAM():
    sizeX(0.0f),
    sizeY(0.0f),
    sizeZ(0.0f)
    {
    //
    }

SBSPRecord::SBSPDNAM::~SBSPDNAM()
    {
    //
    }

bool SBSPRecord::SBSPDNAM::operator ==(const SBSPDNAM &other) const
    {
    return (AlmostEqual(sizeX,other.sizeX,2) &&
            AlmostEqual(sizeY,other.sizeY,2) &&
            AlmostEqual(sizeZ,other.sizeZ,2));
    }

bool SBSPRecord::SBSPDNAM::operator !=(const SBSPDNAM &other) const
    {
    return !(*this == other);
    }

SBSPRecord::SBSPRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SBSPRecord::SBSPRecord(SBSPRecord *srcRecord):
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
    DNAM = srcRecord->DNAM;
    }

SBSPRecord::~SBSPRecord()
    {
    //
    }

UINT32 SBSPRecord::GetType()
    {
    return REV32(SBSP);
    }

STRING SBSPRecord::GetStrType()
    {
    return "SBSP";
    }

SINT32 SBSPRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SBSP: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 SBSPRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DNAM.Unload();
    return 1;
    }

SINT32 SBSPRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DNAM);
    return -1;
    }

bool SBSPRecord::operator ==(const SBSPRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DNAM == other.DNAM);
    }

bool SBSPRecord::operator !=(const SBSPRecord &other) const
    {
    return !(*this == other);
    }

bool SBSPRecord::equals(Record *other)
    {
    return *this == *(SBSPRecord *)other;
    }
}