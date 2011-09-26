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
#include "PFLARecord.h"
#include "CELLRecord.h"

namespace FNV
{
PFLARecord::PFLARecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PFLARecord::PFLARecord(PFLARecord *srcRecord):
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
    NAME = srcRecord->NAME;
    XEZN = srcRecord->XEZN;
    XRGD = srcRecord->XRGD;
    XRGB = srcRecord->XRGB;
    Patrol = srcRecord->Patrol;
    Ownership = srcRecord->Ownership;
    XCNT = srcRecord->XCNT;
    XRDS = srcRecord->XRDS;
    XHLP = srcRecord->XHLP;
    XDCR = srcRecord->XDCR;
    XLKR = srcRecord->XLKR;
    XCLP = srcRecord->XCLP;
    ActivateParents = srcRecord->ActivateParents;
    XATO = srcRecord->XATO;
    XESP = srcRecord->XESP;
    XEMI = srcRecord->XEMI;
    XMBR = srcRecord->XMBR;
    XPWR = srcRecord->XPWR;
    XIBS = srcRecord->XIBS;
    XSCL = srcRecord->XSCL;
    DATA = srcRecord->DATA;
    return;
    }

PFLARecord::~PFLARecord()
    {
    //
    }

bool PFLARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(NAME.value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(Patrol.IsLoaded())
        {
        op.Accept(Patrol->INAM.value);
        for(UINT32 x = 0; x < Patrol->SCR_.value.size(); x++)
            if(Patrol->SCR_.value[x]->isSCRO)
                op.Accept(Patrol->SCR_.value[x]->reference);
        op.Accept(Patrol->TNAM.value);
        }
    if(Ownership.IsLoaded())
        op.Accept(Ownership->XOWN.value);
    for(UINT32 x = 0; x < XDCR.value.size(); x++)
        op.Accept(XDCR.value[x]->reference);
    if(XLKR.IsLoaded())
        op.Accept(XLKR.value);
    if(ActivateParents.IsLoaded())
        for(UINT32 x = 0; x < ActivateParents->XAPR.value.size(); x++)
            op.Accept(ActivateParents->XAPR.value[x]->reference);
    if(XESP.IsLoaded())
        op.Accept(XESP->parent);
    if(XEMI.IsLoaded())
        op.Accept(XEMI.value);
    if(XMBR.IsLoaded())
        op.Accept(XMBR.value);
    for(UINT32 x = 0; x < XPWR.value.size(); x++)
        op.Accept(XPWR.value[x]->reference);

    return op.Stop();
    }

bool PFLARecord::IsOppositeParent()
    {
    return XESP.IsLoaded() ? (XESP->flags & fIsOppositeParent) != 0 : false;
    }

void PFLARecord::IsOppositeParent(bool value)
    {
    if(!XESP.IsLoaded()) return;
    XESP->flags = value ? (XESP->flags | fIsOppositeParent) : (XESP->flags & ~fIsOppositeParent);
    }

bool PFLARecord::IsPopIn()
    {
    return XESP.IsLoaded() ? (XESP->flags & fIsPopIn) != 0 : false;
    }

void PFLARecord::IsPopIn(bool value)
    {
    if(!XESP.IsLoaded()) return;
    XESP->flags = value ? (XESP->flags | fIsPopIn) : (XESP->flags & ~fIsPopIn);
    }

bool PFLARecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!XESP.IsLoaded()) return false;
    return Exact ? ((XESP->flags & Mask) == Mask) : ((XESP->flags & Mask) != 0);
    }

void PFLARecord::SetFlagMask(UINT8 Mask)
    {
    XESP.Load();
    XESP->flags = Mask;
    }

UINT32 PFLARecord::GetType()
    {
    return REV32(PFLA);
    }

STRING PFLARecord::GetStrType()
    {
    return "PFLA";
    }

SINT32 PFLARecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(XEZN):
                XEZN.Read(buffer, subSize);
                break;
            case REV32(XRGD):
                XRGD.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XRGB):
                XRGB.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XPRD):
                Patrol.Load();
                Patrol->XPRD.Read(buffer, subSize);
                break;
            case REV32(XPPA):
                //XPPA, Patrol Script Marker (Empty)
                break;
            case REV32(INAM):
                Patrol.Load();
                Patrol->INAM.Read(buffer, subSize);
                break;
            case REV32(SCHR):
                Patrol.Load();
                Patrol->SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                Patrol.Load();
                Patrol->SCDA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCTX):
                Patrol.Load();
                Patrol->SCTX.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SLSD):
                Patrol.Load();
                Patrol->VARS.value.push_back(new GENVARS);
                Patrol->VARS.value.back()->SLSD.Read(buffer, subSize);
                break;
            case REV32(SCVR):
                Patrol.Load();
                if(Patrol->VARS.value.size() == 0)
                    Patrol->VARS.value.push_back(new GENVARS);
                Patrol->VARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRO):
                Patrol.Load();
                Patrol->SCR_.Read(buffer, subSize);
                Patrol->SCR_.value.back()->isSCRO = true;
                break;
            case REV32(SCRV):
                Patrol.Load();
                Patrol->SCR_.Read(buffer, subSize);
                Patrol->SCR_.value.back()->isSCRO = false;
                break;
            case REV32(TNAM):
                Patrol.Load();
                Patrol->TNAM.Read(buffer, subSize);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize);
                break;
            case REV32(XCNT):
                XCNT.Read(buffer, subSize);
                break;
            case REV32(XRDS):
                XRDS.Read(buffer, subSize);
                break;
            case REV32(XHLP):
                XHLP.Read(buffer, subSize);
                break;
            case REV32(XDCR):
                XDCR.Read(buffer, subSize);
                break;
            case REV32(XLKR):
                XLKR.Read(buffer, subSize);
                break;
            case REV32(XCLP):
                XCLP.Read(buffer, subSize);
                break;
            case REV32(XAPD):
                ActivateParents.Load();
                ActivateParents->XAPD.Read(buffer, subSize);
                break;
            case REV32(XAPR):
                ActivateParents.Load();
                ActivateParents->XAPR.Read(buffer, subSize);
                break;
            case REV32(XATO):
                XATO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XESP):
                XESP.Read(buffer, subSize);
                break;
            case REV32(XEMI):
                XEMI.Read(buffer, subSize);
                break;
            case REV32(XMBR):
                XMBR.Read(buffer, subSize);
                break;
            case REV32(XPWR):
                XPWR.Read(buffer, subSize);
                break;
            case REV32(XIBS):
                //XIBS.Read(buffer, subSize);
                XIBS.value = 1;
                break;
            case REV32(XSCL):
                XSCL.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  PFLA: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 PFLARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    NAME.Unload();
    XEZN.Unload();
    XRGD.Unload();
    XRGB.Unload();
    Patrol.Unload();
    Ownership.Unload();
    XCNT.Unload();
    XRDS.Unload();
    XHLP.Unload();
    XDCR.Unload();
    XLKR.Unload();
    XCLP.Unload();
    ActivateParents.Unload();
    XATO.Unload();
    XESP.Unload();
    XEMI.Unload();
    XMBR.Unload();
    XPWR.Unload();
    XIBS.Unload();
    XSCL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 PFLARecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NAME);
    WRITE(XEZN);
    WRITE(XRGD);
    WRITE(XRGB);
    Patrol.Write(writer);
    Ownership.Write(writer);
    WRITE(XCNT);
    WRITE(XRDS);
    WRITE(XHLP);
    WRITE(XDCR);
    WRITE(XLKR);
    WRITE(XCLP);
    ActivateParents.Write(writer);
    WRITE(XATO);
    WRITE(XESP);
    WRITE(XEMI);
    WRITE(XMBR);
    WRITE(XPWR);
    if(XIBS.IsLoaded())
        WRITEEMPTY(XIBS);
    WRITE(XSCL);
    WRITE(DATA);
    return -1;
    }

bool PFLARecord::operator ==(const PFLARecord &other) const
    {
    return (NAME == other.NAME &&
            XIBS.IsLoaded() == other.XIBS.IsLoaded() &&
            XEZN == other.XEZN &&
            XCNT == other.XCNT &&
            XRDS == other.XRDS &&
            XHLP == other.XHLP &&
            XLKR == other.XLKR &&
            XCLP == other.XCLP &&
            XESP == other.XESP &&
            XEMI == other.XEMI &&
            XMBR == other.XMBR &&
            DATA == other.DATA &&
            XSCL == other.XSCL &&
            XDCR == other.XDCR &&
            EDID.equalsi(other.EDID) &&
            XATO.equals(other.XATO) &&
            XRGD == other.XRGD &&
            XRGB == other.XRGB &&
            ActivateParents == other.ActivateParents &&
            XPWR == other.XPWR &&
            Patrol == other.Patrol &&
            Ownership == other.Ownership);
    }

bool PFLARecord::operator !=(const PFLARecord &other) const
    {
    return !(*this == other);
    }

bool PFLARecord::equals(Record *other)
    {
    return *this == *(PFLARecord *)other;
    }

bool PFLARecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    CELLRecord *parent_cell = (CELLRecord *)GetParentRecord(), *master_cell = (CELLRecord *)((PFLARecord *)master)->GetParentRecord();
    //Check to make sure the parent cell is attached at the same spot
    if(parent_cell->formID != master_cell->formID)
        return false;
    if(!parent_cell->IsInterior())
        {
        if(parent_cell->GetParentRecord()->formID != master_cell->GetParentRecord()->formID)
            return false;
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