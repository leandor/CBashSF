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
#include "ACRERecord.h"
#include "CELLRecord.h"

namespace Ob
{
ACRERecord::ACRERecord(unsigned char *_recData):
    Record(_recData)
    {
    //ACRE records are normally temporary
    if(_recData == NULL)
        IsTemporary(true);
    }

ACRERecord::ACRERecord(ACRERecord *srcRecord):
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
    NAME = srcRecord->NAME;
    Ownership = srcRecord->Ownership;
    XLOD = srcRecord->XLOD;
    XESP = srcRecord->XESP;
    XRGD = srcRecord->XRGD;
    XSCL = srcRecord->XSCL;
    DATA = srcRecord->DATA;
    return;
    }

ACRERecord::~ACRERecord()
    {
    //Parent is a shared pointer that's deleted when the CELL group is deleted
    }

bool ACRERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(NAME.value);
    if(Ownership.IsLoaded())
        {
        if(Ownership->XOWN.IsLoaded())
            op.Accept(Ownership->XOWN.value);
        if(Ownership->XGLB.IsLoaded())
            op.Accept(Ownership->XGLB.value);
        }
    if(XESP.IsLoaded())
        op.Accept(XESP->parent);

    return op.Stop();
    }

bool ACRERecord::IsOppositeParent()
    {
    return XESP.IsLoaded() ? (XESP->flags & fIsOppositeParent) != 0 : false;
    }

void ACRERecord::IsOppositeParent(bool value)
    {
    if(!XESP.IsLoaded()) return;
    XESP->flags = value ? (XESP->flags | fIsOppositeParent) : (XESP->flags & ~fIsOppositeParent);
    }

bool ACRERecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!XESP.IsLoaded()) return false;
    return Exact ? ((XESP->flags & Mask) == Mask) : ((XESP->flags & Mask) != 0);
    }

void ACRERecord::SetFlagMask(UINT8 Mask)
    {
    XESP.Load();
    XESP->flags = Mask;
    }

UINT32 ACRERecord::GetType()
    {
    return REV32(ACRE);
    }

STRING ACRERecord::GetStrType()
    {
    return "ACRE";
    }

SINT32 ACRERecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(NAME):
                NAME.Read(buffer, subSize);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize);
                break;
            case REV32(XGLB):
                Ownership.Load();
                Ownership->XGLB.Read(buffer, subSize);
                break;
            case REV32(XLOD):
                XLOD.Read(buffer, subSize);
                break;
            case REV32(XESP):
                XESP.Read(buffer, subSize);
                break;
            case REV32(XRGD):
                XRGD.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XSCL):
                XSCL.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ACRE: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 ACRERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NAME.Unload();
    Ownership.Unload();
    XLOD.Unload();
    XESP.Unload();
    XRGD.Unload();
    XSCL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 ACRERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NAME);
    Ownership.Write(writer);

    WRITE(XLOD);
    WRITE(XESP);
    WRITE(XRGD);
    WRITE(XSCL);
    WRITE(DATA);

    return -1;
    }

bool ACRERecord::operator ==(const ACRERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NAME == other.NAME &&
            Ownership == other.Ownership &&
            XLOD == other.XLOD &&
            XESP == other.XESP &&
            XRGD == other.XRGD &&
            XSCL == other.XSCL &&
            DATA == other.DATA);
    }

bool ACRERecord::operator !=(const ACRERecord &other) const
    {
    return !(*this == other);
    }

bool ACRERecord::equals(Record *other)
    {
    return *this == *(ACRERecord *)other;
    }

bool ACRERecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    CELLRecord *parent_cell = (CELLRecord *)GetParentRecord(), *master_cell = (CELLRecord *)master->GetParentRecord();
    Record *parent_wrld = parent_cell->GetParentRecord(), *master_wrld = master_cell->GetParentRecord();
    //Check to make sure the parent cell is attached at the same spot
    if(parent_cell->formID != master_cell->formID)
        return false;
    if(parent_wrld != NULL)
        {
        if(master_wrld != NULL)
            {
            if(parent_wrld->formID != master_wrld->formID)
                return false;
            }
        else
            return false;
        }
    else if(master_wrld != NULL)
        return false;
    if(parent_wrld)
        {
        read_self.Accept((Record *&)parent_cell);
        read_master.Accept((Record *&)master_cell);
        parent_cell->XCLC.Load();
        master_cell->XCLC.Load();
        if(parent_cell->XCLC->posX != master_cell->XCLC->posX)
            return false;
        if(parent_cell->XCLC->posY != master_cell->XCLC->posY)
            return false;
        }
    return true;
    }
}