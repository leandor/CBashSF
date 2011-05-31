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
#include "ACRERecord.h"

namespace FNV
{
ACRERecord::ACRERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ACRERecord::ACRERecord(ACRERecord *srcRecord):
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

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    NAME = srcRecord->NAME;
    XEZN = srcRecord->XEZN;
    XRGD = srcRecord->XRGD;
    XRGB = srcRecord->XRGB;
    Patrol = srcRecord->Patrol;
    XLCM = srcRecord->XLCM;
    Ownership = srcRecord->Ownership;
    XMRC = srcRecord->XMRC;
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
    XIBS = srcRecord->XIBS;
    XSCL = srcRecord->XSCL;
    DATA = srcRecord->DATA;
    return;
    }

ACRERecord::~ACRERecord()
    {
    //
    }

bool ACRERecord::VisitFormIDs(FormIDOp &op)
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
    if(XMRC.IsLoaded())
        op.Accept(XMRC.value);
    for(UINT32 x = 0; x < XDCR.value.size(); x++)
        op.Accept(XDCR.value[x]->reference);
    if(XLKR.IsLoaded())
        op.Accept(XLKR.value);
    if(ActivateParents.IsLoaded())
        {
        for(UINT32 x = 0; x < ActivateParents->XAPR.value.size(); x++)
            op.Accept(ActivateParents->XAPR.value[x]->reference);
        }
    if(XESP.IsLoaded())
        op.Accept(XESP->parent);
    if(XEMI.IsLoaded())
        op.Accept(XEMI.value);
    if(XMBR.IsLoaded())
        op.Accept(XMBR.value);

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

bool ACRERecord::IsPopIn()
    {
    return XESP.IsLoaded() ? (XESP->flags & fIsPopIn) != 0 : false;
    }

void ACRERecord::IsPopIn(bool value)
    {
    if(!XESP.IsLoaded()) return;
    XESP->flags = value ? (XESP->flags | fIsPopIn) : (XESP->flags & ~fIsPopIn);
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

UINT32 ACRERecord::GetParentType()
    {
    return REV32(CELL);
    }

SINT32 ACRERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case REV32(XXXX):
                curPos += 2;
                _readBuffer(&subSize, buffer, 4, curPos);
                _readBuffer(&subType, buffer, 4, curPos);
                curPos += 2;
                break;
            default:
                subSize = 0;
                _readBuffer(&subSize, buffer, 2, curPos);
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, curPos);
                break;
            case REV32(NAME):
                NAME.Read(buffer, subSize, curPos);
                break;
            case REV32(XEZN):
                XEZN.Read(buffer, subSize, curPos);
                break;
            case REV32(XRGD):
                XRGD.Read(buffer, subSize, curPos);
                break;
            case REV32(XRGB):
                XRGB.Read(buffer, subSize, curPos);
                break;
            case REV32(XPRD):
                Patrol.Load();
                Patrol->XPRD.Read(buffer, subSize, curPos);
                break;
            case REV32(XPPA):
                //XPPA, Patrol Script Marker (Empty)
                break;
            case REV32(INAM):
                Patrol.Load();
                Patrol->INAM.Read(buffer, subSize, curPos);
                break;
            case REV32(SCHR):
                Patrol.Load();
                Patrol->SCHR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCDA):
                Patrol.Load();
                Patrol->SCDA.Read(buffer, subSize, curPos);
                break;
            case REV32(SCTX):
                Patrol.Load();
                Patrol->SCTX.Read(buffer, subSize, curPos);
                break;
            case REV32(SLSD):
                Patrol.Load();
                Patrol->VARS.value.push_back(new GENVARS);
                Patrol->VARS.value.back()->SLSD.Read(buffer, subSize, curPos);
                break;
            case REV32(SCVR):
                Patrol.Load();
                if(Patrol->VARS.value.size() == 0)
                    Patrol->VARS.value.push_back(new GENVARS);
                Patrol->VARS.value.back()->SCVR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRO):
                Patrol.Load();
                Patrol->SCR_.Read(buffer, subSize, curPos);
                Patrol->SCR_.value.back()->isSCRO = true;
                break;
            case REV32(SCRV):
                Patrol.Load();
                Patrol->SCR_.Read(buffer, subSize, curPos);
                Patrol->SCR_.value.back()->isSCRO = false;
                break;
            case REV32(TNAM):
                Patrol.Load();
                Patrol->TNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(XLCM):
                XLCM.Read(buffer, subSize, curPos);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize, curPos);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize, curPos);
                break;
            case REV32(XMRC):
                XMRC.Read(buffer, subSize, curPos);
                break;
            case REV32(XCNT):
                XCNT.Read(buffer, subSize, curPos);
                break;
            case REV32(XRDS):
                XRDS.Read(buffer, subSize, curPos);
                break;
            case REV32(XHLP):
                XHLP.Read(buffer, subSize, curPos);
                break;
            case REV32(XDCR):
                XDCR.Read(buffer, subSize, curPos);
                break;
            case REV32(XLKR):
                XLKR.Read(buffer, subSize, curPos);
                break;
            case REV32(XCLP):
                XCLP.Read(buffer, subSize, curPos);
                break;
            case REV32(XAPD):
                ActivateParents.Load();
                ActivateParents->XAPD.Read(buffer, subSize, curPos);
                break;
            case REV32(XAPR):
                ActivateParents.Load();
                ActivateParents->XAPR.Read(buffer, subSize, curPos);
                break;
            case REV32(XATO):
                XATO.Read(buffer, subSize, curPos);
                break;
            case REV32(XESP):
                XESP.Read(buffer, subSize, curPos);
                break;
            case REV32(XEMI):
                XEMI.Read(buffer, subSize, curPos);
                break;
            case REV32(XMBR):
                XMBR.Read(buffer, subSize, curPos);
                break;
            case REV32(XIBS):
                //XIBS.Read(buffer, subSize, curPos);
                XIBS.value = 1;
                break;
            case REV32(XSCL):
                XSCL.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ACRE: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    XEZN.Unload();
    XRGD.Unload();
    XRGB.Unload();
    Patrol.Unload();
    XLCM.Unload();
    Ownership.Unload();
    XMRC.Unload();
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
    XIBS.Unload();
    XSCL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 ACRERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NAME);
    WRITE(XEZN);
    WRITE(XRGD);
    WRITE(XRGB);
    Patrol.Write(writer);
    WRITE(XLCM);
    Ownership.Write(writer);
    WRITE(XMRC);
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
    if(XIBS.IsLoaded())
        WRITEEMPTY(XIBS);
    WRITE(XSCL);
    WRITE(DATA);
    return -1;
    }

bool ACRERecord::operator ==(const ACRERecord &other) const
    {
    return (NAME == other.NAME &&
            XIBS.IsLoaded() == other.XIBS.IsLoaded() &&
            XEZN == other.XEZN &&
            XLCM == other.XLCM &&
            XMRC == other.XMRC &&
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
            Patrol == other.Patrol &&
            Ownership == other.Ownership);
    }

bool ACRERecord::operator !=(const ACRERecord &other) const
    {
    return !(*this == other);
    }
}