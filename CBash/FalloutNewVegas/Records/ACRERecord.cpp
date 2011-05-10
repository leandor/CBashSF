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
    if(srcRecord->XPRD.IsLoaded())
        {
        XPRD.Load();
        XPRD->XPRD = srcRecord->XPRD->XPRD;
        XPRD->XPPA = srcRecord->XPRD->XPPA;
        XPRD->INAM = srcRecord->XPRD->INAM;
        if(srcRecord->XPRD->SCHR.IsLoaded())
            {
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR = srcRecord->XPRD->SCHR->SCHR;
            XPRD->SCHR->SCDA = srcRecord->XPRD->SCHR->SCDA;
            XPRD->SCHR->SCTX = srcRecord->XPRD->SCHR->SCTX;
            XPRD->SCHR->SLSD = srcRecord->XPRD->SCHR->SLSD;
            XPRD->SCHR->SCVR = srcRecord->XPRD->SCHR->SCVR;
            XPRD->SCHR->SCRO = srcRecord->XPRD->SCHR->SCRO;
            XPRD->SCHR->SCRV = srcRecord->XPRD->SCHR->SCRV;
            }
        XPRD->TNAM = srcRecord->XPRD->TNAM;
        }
    XLCM = srcRecord->XLCM;
    if(srcRecord->XOWN.IsLoaded())
        {
        XOWN.Load();
        XOWN->XOWN = srcRecord->XOWN->XOWN;
        XOWN->XRNK = srcRecord->XOWN->XRNK;
        }
    XMRC = srcRecord->XMRC;
    XCNT = srcRecord->XCNT;
    XRDS = srcRecord->XRDS;
    XHLP = srcRecord->XHLP;
    XDCR = srcRecord->XDCR;
    XLKR = srcRecord->XLKR;
    XCLP = srcRecord->XCLP;
    if(srcRecord->XAPD.IsLoaded())
        {
        XAPD.Load();
        XAPD->XAPD = srcRecord->XAPD->XAPD;
        }
    XAPR = srcRecord->XAPR;
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

    if(NAME.IsLoaded())
        op.Accept(NAME->value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN->value);
    if(XPRD.IsLoaded() && XPRD->INAM.IsLoaded())
        op.Accept(XPRD->INAM->value);
    if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded() && XPRD->SCHR->SCRO.IsLoaded())
        op.Accept(XPRD->SCHR->SCRO->value);
    if(XPRD.IsLoaded() && XPRD->TNAM.IsLoaded())
        op.Accept(XPRD->TNAM->value);
    if(XOWN.IsLoaded() && XOWN->XOWN.IsLoaded())
        op.Accept(XOWN->XOWN->value);
    if(XMRC.IsLoaded())
        op.Accept(XMRC->value);
    //if(XDCR.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XDCR->value);
    if(XLKR.IsLoaded())
        op.Accept(XLKR->value);
    //if(XAPR.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XAPR->value);
    //if(XESP.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XESP->value);
    if(XEMI.IsLoaded())
        op.Accept(XEMI->value);
    if(XMBR.IsLoaded())
        op.Accept(XMBR->value);

    return op.Stop();
    }

bool ACRERecord::IsOppositeParent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOppositeParent) != 0;
    }

void ACRERecord::IsOppositeParent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsOppositeParent) : (Dummy->flags & ~fIsOppositeParent);
    }

bool ACRERecord::IsPopIn()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPopIn) != 0;
    }

void ACRERecord::IsPopIn(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPopIn) : (Dummy->flags & ~fIsPopIn);
    }

bool ACRERecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ACRERecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 ACRERecord::GetType()
    {
    return REV32(ACRE);
    }

STRING ACRERecord::GetStrType()
    {
    return "ACRE";
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
                XPRD.Load();
                XPRD->XPRD.Read(buffer, subSize, curPos);
                break;
            case REV32(XPPA):
                //XPRD.Load();
                //XPRD->XPPA.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case REV32(INAM):
                XPRD.Load();
                XPRD->INAM.Read(buffer, subSize, curPos);
                break;
            case REV32(SCHR):
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCDA):
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case REV32(SCTX):
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case REV32(SLSD):
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case REV32(SCVR):
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRO):
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRV):
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case REV32(TNAM):
                XPRD.Load();
                XPRD->TNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(XLCM):
                XLCM.Read(buffer, subSize, curPos);
                break;
            case REV32(XOWN):
                XOWN.Load();
                XOWN->XOWN.Read(buffer, subSize, curPos);
                break;
            case REV32(XRNK):
                XOWN.Load();
                XOWN->XRNK.Read(buffer, subSize, curPos);
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
                XAPD.Load();
                XAPD->XAPD.Read(buffer, subSize, curPos);
                break;
            case REV32(XAPR):
                XAPR.Read(buffer, subSize, curPos);
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
                //XIBS.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case REV32(XSCL):
                XSCL.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ACRE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
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
    XPRD.Unload();
    XLCM.Unload();
    XOWN.Unload();
    XMRC.Unload();
    XCNT.Unload();
    XRDS.Unload();
    XHLP.Unload();
    XDCR.Unload();
    XLKR.Unload();
    XCLP.Unload();
    XAPD.Unload();
    XAPR.Unload();
    XATO.Unload();
    XESP.Unload();
    XEMI.Unload();
    XMBR.Unload();
    //XIBS.Unload(); //FILL IN MANUALLY
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

    if(XPRD.IsLoaded())
        {
        if(XPRD->XPRD.IsLoaded())
            SaveHandler.writeSubRecord(REV32(XPRD), XPRD->XPRD.value, XPRD->XPRD.GetSize());

        //if(XPRD->XPPA.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord(REV32(XPPA), XPRD->XPPA.value, XPRD->XPPA.GetSize());

        if(XPRD->INAM.IsLoaded())
            SaveHandler.writeSubRecord(REV32(INAM), XPRD->INAM.value, XPRD->INAM.GetSize());

        if(XPRD->SCHR.IsLoaded())
            {
            if(XPRD->SCHR->SCHR.IsLoaded())
                SaveHandler.writeSubRecord(REV32(SCHR), XPRD->SCHR->SCHR.value, XPRD->SCHR->SCHR.GetSize());

            if(XPRD->SCHR->SCDA.IsLoaded())
                SaveHandler.writeSubRecord(REV32(SCDA), XPRD->SCHR->SCDA.value, XPRD->SCHR->SCDA.GetSize());

            if(XPRD->SCHR->SCTX.IsLoaded())
                SaveHandler.writeSubRecord(REV32(SCTX), XPRD->SCHR->SCTX.value, XPRD->SCHR->SCTX.GetSize());

            if(XPRD->SCHR->SLSD.IsLoaded())
                SaveHandler.writeSubRecord(REV32(SLSD), XPRD->SCHR->SLSD.value, XPRD->SCHR->SLSD.GetSize());

            if(XPRD->SCHR->SCVR.IsLoaded())
                SaveHandler.writeSubRecord(REV32(SCVR), XPRD->SCHR->SCVR.value, XPRD->SCHR->SCVR.GetSize());

            if(XPRD->SCHR->SCRO.IsLoaded())
                SaveHandler.writeSubRecord(REV32(SCRO), XPRD->SCHR->SCRO.value, XPRD->SCHR->SCRO.GetSize());

            if(XPRD->SCHR->SCRV.IsLoaded())
                SaveHandler.writeSubRecord(REV32(SCRV), XPRD->SCHR->SCRV.value, XPRD->SCHR->SCRV.GetSize());

            }
        if(XPRD->TNAM.IsLoaded())
            SaveHandler.writeSubRecord(REV32(TNAM), XPRD->TNAM.value, XPRD->TNAM.GetSize());

        }

    WRITE(XLCM);

    if(XOWN.IsLoaded())
        {
        if(XOWN->XOWN.IsLoaded())
            SaveHandler.writeSubRecord(REV32(XOWN), XOWN->XOWN.value, XOWN->XOWN.GetSize());

        if(XOWN->XRNK.IsLoaded())
            SaveHandler.writeSubRecord(REV32(XRNK), XOWN->XRNK.value, XOWN->XRNK.GetSize());

        }

    WRITE(XMRC);
    WRITE(XCNT);
    WRITE(XRDS);
    WRITE(XHLP);
    WRITE(XDCR);
    WRITE(XLKR);
    WRITE(XCLP);

    if(XAPD.IsLoaded())
        {
        if(XAPD->XAPD.IsLoaded())
            SaveHandler.writeSubRecord(REV32(XAPD), XAPD->XAPD.value, XAPD->XAPD.GetSize());

        }

    WRITE(XAPR);
    WRITE(XATO);
    WRITE(XESP);
    WRITE(XEMI);
    WRITE(XMBR);

    //if(XIBS.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(XIBS), XIBS.value, XIBS.GetSize());
    WRITE(XSCL);
    WRITE(DATA);

    return -1;
    }

bool ACRERecord::operator ==(const ACRERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NAME == other.NAME &&
            XEZN == other.XEZN &&
            XRGD == other.XRGD &&
            XRGB == other.XRGB &&
            XPRD == other.XPRD &&
            XLCM == other.XLCM &&
            XOWN == other.XOWN &&
            XMRC == other.XMRC &&
            XCNT == other.XCNT &&
            XRDS == other.XRDS &&
            XHLP == other.XHLP &&
            XDCR == other.XDCR &&
            XLKR == other.XLKR &&
            XCLP == other.XCLP &&
            XAPD == other.XAPD &&
            XAPR == other.XAPR &&
            XATO.equalsi(other.XATO) &&
            XESP == other.XESP &&
            XEMI == other.XEMI &&
            XMBR == other.XMBR &&
            //Empty &&
            XSCL == other.XSCL &&
            DATA == other.DATA);
    }

bool ACRERecord::operator !=(const ACRERecord &other) const
    {
    return !(*this == other);
    }
}