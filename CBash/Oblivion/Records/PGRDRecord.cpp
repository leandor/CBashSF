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
#include "PGRDRecord.h"
#include "CELLRecord.h"

namespace Ob
{
PGRDRecord::PGRDPGRI::PGRDPGRI():point(0), x(0.0f), y(0.0f), z(0.0f)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

PGRDRecord::PGRDPGRI::~PGRDPGRI()
    {
    //
    }

bool PGRDRecord::PGRDPGRI::operator ==(const PGRDPGRI &other) const
    {
    return (point == other.point &&
            AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2) &&
            AlmostEqual(z,other.z,2));
    }

bool PGRDRecord::PGRDPGRI::operator !=(const PGRDPGRI &other) const
    {
    return !(*this == other);
    }

PGRDRecord::PGRDPGRL::PGRDPGRL()
    {
    //First element must be allocated since it's where the reference is stored
    points.value.push_back(0);
    }

PGRDRecord::PGRDPGRL::~PGRDPGRL()
    {
    //
    }

void PGRDRecord::PGRDPGRL::Write(FileWriter &writer)
    {
    WRITEAS(points,PGRL);
    }

bool PGRDRecord::PGRDPGRL::operator ==(const PGRDPGRL &other) const
    {
    return points == other.points;
    }

bool PGRDRecord::PGRDPGRL::operator !=(const PGRDPGRL &other) const
    {
    return !(*this == other);
    }

PGRDRecord::PGRDRecord(unsigned char *_recData):
    Record(_recData),
    Parent(NULL)
    {
    //PGRD records are normally compressed due to size
    if(_recData == NULL)
        IsCompressed(true);
    }

PGRDRecord::PGRDRecord(PGRDRecord *srcRecord):
    Record(),
    Parent(NULL)
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

    DATA = srcRecord->DATA;
    PGRP = srcRecord->PGRP;
    PGAG = srcRecord->PGAG;
    PGRR = srcRecord->PGRR;
    PGRI = srcRecord->PGRI;
    PGRL = srcRecord->PGRL;
    }

PGRDRecord::~PGRDRecord()
    {
    //Parent is a shared pointer that's deleted when the CELL group is deleted
    }

bool PGRDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < PGRL.value.size(); x++)
        op.Accept(PGRL.value[x]->points.value[0]);

    return op.Stop();
    }

UINT32 PGRDRecord::GetType()
    {
    return REV32(PGRD);
    }

STRING PGRDRecord::GetStrType()
    {
    return "PGRD";
    }

Record * PGRDRecord::GetParent()
    {
    return Parent;
    }

SINT32 PGRDRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(PGRP):
                PGRP.Read(buffer, subSize);
                break;
            case REV32(PGAG):
                PGAG.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(PGRR):
                PGRR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(PGRI):
                PGRI.Read(buffer, subSize);
                break;
            case REV32(PGRL):
                PGRL.value.push_back(new PGRDPGRL);
                PGRL.value.back()->points.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  PGRD: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 PGRDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    DATA.Unload();
    PGRP.Unload();
    PGAG.Unload();
    PGRR.Unload();
    PGRI.Unload();
    PGRL.Unload();
    return 1;
    }

SINT32 PGRDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(DATA);
    WRITE(PGRP);
    WRITE(PGAG);
    WRITE(PGRR);
    WRITE(PGRI);
    PGRL.Write(writer);
    return -1;
    }

bool PGRDRecord::operator ==(const PGRDRecord &other) const
    {
    return (DATA == other.DATA &&
            PGAG == other.PGAG &&
            PGRR == other.PGRR &&
            PGRP == other.PGRP &&
            PGRL == other.PGRL);
    }

bool PGRDRecord::operator !=(const PGRDRecord &other) const
    {
    return !(*this == other);
    }

bool PGRDRecord::equals(Record *other)
    {
    return *this == *(PGRDRecord *)other;
    }

bool PGRDRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    PGRDRecord *master_pgrd = (PGRDRecord *)master;
    //Check to make sure the parent cell is attached at the same spot
    if(Parent->formID != master_pgrd->Parent->formID)
        return false;
    if(!((CELLRecord *)Parent)->IsInterior())
        {
        if(((CELLRecord *)Parent)->Parent->formID != ((CELLRecord *)master_pgrd->Parent)->Parent->formID)
            return false;
        read_self.Accept(Parent);
        read_master.Accept(master_pgrd->Parent);
        ((CELLRecord *)Parent)->XCLC.Load();
        ((CELLRecord *)master_pgrd->Parent)->XCLC.Load();
        if(((CELLRecord *)Parent)->XCLC->posX != ((CELLRecord *)master_pgrd->Parent)->XCLC->posX)
            return false;
        if(((CELLRecord *)Parent)->XCLC->posY != ((CELLRecord *)master_pgrd->Parent)->XCLC->posY)
            return false;
        }
    return true;
    }
}