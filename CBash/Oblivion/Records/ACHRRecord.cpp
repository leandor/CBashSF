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
#include "ACHRRecord.h"
#include "CELLRecord.h"

namespace Ob
{
ACHRRecord::ACHRRecord(unsigned char *_recData):
    Record(_recData),
    Parent(NULL)
    {
    //ACHR records are normally persistent
    if(_recData == NULL)
        IsPersistent(true);
    }

ACHRRecord::ACHRRecord(ACHRRecord *srcRecord):
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

    EDID = srcRecord->EDID;
    NAME = srcRecord->NAME;
    XPCI = srcRecord->XPCI;
    XLOD = srcRecord->XLOD;
    XESP = srcRecord->XESP;
    XMRC = srcRecord->XMRC;
    XHRS = srcRecord->XHRS;
    XRGD = srcRecord->XRGD;
    XSCL = srcRecord->XSCL;
    DATA = srcRecord->DATA;
    return;
    }

ACHRRecord::~ACHRRecord()
    {
    //Parent is a shared pointer that's deleted when the CELL group is deleted
    }

bool ACHRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(NAME.value);
    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        op.Accept(XPCI->XPCI.value);
    if(XESP.IsLoaded())
        op.Accept(XESP->parent);
    if(XMRC.IsLoaded())
        op.Accept(XMRC.value);
    if(XHRS.IsLoaded())
        op.Accept(XHRS.value);

    return op.Stop();
    }

bool ACHRRecord::IsOppositeParent()
    {
    return XESP.IsLoaded() ? (XESP->flags & fIsOppositeParent) != 0 : false;
    }

void ACHRRecord::IsOppositeParent(bool value)
    {
    if(!XESP.IsLoaded()) return;
    XESP->flags = value ? (XESP->flags | fIsOppositeParent) : (XESP->flags & ~fIsOppositeParent);
    }

bool ACHRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!XESP.IsLoaded()) return false;
    return Exact ? ((XESP->flags & Mask) == Mask) : ((XESP->flags & Mask) != 0);
    }

void ACHRRecord::SetFlagMask(UINT8 Mask)
    {
    XESP.Load();
    XESP->flags = Mask;
    }

UINT32 ACHRRecord::GetType()
    {
    return REV32(ACHR);
    }

STRING ACHRRecord::GetStrType()
    {
    return "ACHR";
    }

Record * ACHRRecord::GetParent()
    {
    return Parent;
    }

SINT32 ACHRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(XPCI):
                XPCI.Load();
                XPCI->XPCI.Read(buffer, subSize);
                break;
            case REV32(FULL):
                XPCI.Load();
                XPCI->FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XLOD):
                XLOD.Read(buffer, subSize);
                break;
            case REV32(XESP):
                XESP.Read(buffer, subSize);
                break;
            case REV32(XMRC):
                XMRC.Read(buffer, subSize);
                break;
            case REV32(XHRS):
                XHRS.Read(buffer, subSize);
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
                printer("  ACHR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 ACHRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NAME.Unload();
    XPCI.Unload();
    XLOD.Unload();
    XESP.Unload();
    XMRC.Unload();
    XHRS.Unload();
    XRGD.Unload();
    XSCL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 ACHRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NAME);
    XPCI.Write(writer);
    WRITE(XLOD);
    WRITE(XESP);
    WRITE(XMRC);
    WRITE(XHRS);
    WRITE(XRGD);
    WRITE(XSCL);
    WRITE(DATA);
    return -1;
    }

bool ACHRRecord::operator ==(const ACHRRecord &other) const
    {
    return (NAME == other.NAME &&
            XMRC == other.XMRC &&
            XHRS == other.XHRS &&
            XESP == other.XESP &&
            DATA == other.DATA &&
            XSCL == other.XSCL &&
            XLOD == other.XLOD &&
            EDID.equalsi(other.EDID) &&
            XPCI == other.XPCI &&
            XRGD == other.XRGD);
    }

bool ACHRRecord::operator !=(const ACHRRecord &other) const
    {
    return !(*this == other);
    }

bool ACHRRecord::equals(Record *other)
    {
    return *this == *(ACHRRecord *)other;
    }

bool ACHRRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    ACHRRecord *master_achr = (ACHRRecord *)master;
    //Check to make sure the parent cell is attached at the same spot
    if(Parent->formID != master_achr->Parent->formID)
        return false;
    if(!((CELLRecord *)Parent)->IsInterior())
        {
        if(((CELLRecord *)Parent)->Parent->formID != ((CELLRecord *)master_achr->Parent)->Parent->formID)
            return false;
        read_self.Accept(Parent);
        read_master.Accept(master_achr->Parent);
        ((CELLRecord *)Parent)->XCLC.Load();
        ((CELLRecord *)master_achr->Parent)->XCLC.Load();
        if(((CELLRecord *)Parent)->XCLC->posX != ((CELLRecord *)master_achr->Parent)->XCLC->posX)
            return false;
        if(((CELLRecord *)Parent)->XCLC->posY != ((CELLRecord *)master_achr->Parent)->XCLC->posY)
            return false;
        }
    return true;
    }
}