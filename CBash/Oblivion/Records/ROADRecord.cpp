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
#include "ROADRecord.h"

namespace Ob
{
ROADRecord::ROADPGRR::ROADPGRR():
    x(0.0f),
    y(0.0f),
    z(0.0f)
    {
    //
    }

ROADRecord::ROADPGRR::~ROADPGRR()
    {
    //
    }

bool ROADRecord::ROADPGRR::operator ==(const ROADPGRR &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2) &&
            AlmostEqual(z,other.z,2));
    }

bool ROADRecord::ROADPGRR::operator !=(const ROADPGRR &other) const
    {
    return !(*this == other);
    }

ROADRecord::ROADRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ROADRecord::ROADRecord(ROADRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    PGRP = srcRecord->PGRP;
    PGRR = srcRecord->PGRR;
    return;
    }

ROADRecord::~ROADRecord()
    {
    //Parent is a shared pointer that's deleted when the WRLD group is deleted
    }

UINT32 ROADRecord::GetType()
    {
    return REV32(ROAD);
    }

STRING ROADRecord::GetStrType()
    {
    return "ROAD";
    }

SINT32 ROADRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(PGRP):
                PGRP.Read(buffer, subSize);
                break;
            case REV32(PGRR):
                PGRR.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ROADPGRR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 ROADRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    PGRP.Unload();
    PGRR.Unload();
    return 1;
    }

SINT32 ROADRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(PGRP);
    WRITE(PGRR);
    return -1;
    }

bool ROADRecord::operator ==(const ROADRecord &other) const
    {
    return (PGRP == other.PGRP &&
            PGRP == other.PGRP);
    }

bool ROADRecord::operator !=(const ROADRecord &other) const
    {
    return !(*this == other);
    }

bool ROADRecord::equals(Record *other)
    {
    return *this == *(ROADRecord *)other;
    }

bool ROADRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //Check to make sure the parent cell is attached at the same spot
    if(GetParentRecord()->formID != ((ROADRecord *)master)->GetParentRecord()->formID)
        return false;
    return true;
    }
}