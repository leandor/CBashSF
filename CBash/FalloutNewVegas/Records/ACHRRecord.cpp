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
#include "ACHRRecord.h"

namespace FNV
{
ACHRRecord::ACHRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ACHRRecord::ACHRRecord(ACHRRecord *srcRecord):
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
    XMRC = srcRecord->XMRC;
    XCNT = srcRecord->XCNT;
    XRDS = srcRecord->XRDS;
    XHLP = srcRecord->XHLP;
    XDCR = srcRecord->XDCR;
    XLKR = srcRecord->XLKR;
    XCLP = srcRecord->XCLP;
    XAPD = srcRecord->XAPD;
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

ACHRRecord::~ACHRRecord()
    {
    //
    }

bool ACHRRecord::VisitFormIDs(FormIDOp &op)
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
bool ACHRRecord::IsOppositeParent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOppositeParent) != 0;
    }

void ACHRRecord::IsOppositeParent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsOppositeParent;
    else
        Dummy->flags &= ~fIsOppositeParent;
    }

bool ACHRRecord::IsPopIn()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPopIn) != 0;
    }

void ACHRRecord::IsPopIn(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPopIn;
    else
        Dummy->flags &= ~fIsPopIn;
    }

bool ACHRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ACHRRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 ACHRRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAME.IsLoaded())
        TotSize += NAME.GetSize() + 6;

    if(XEZN.IsLoaded())
        TotSize += XEZN.GetSize() + 6;

    if(XRGD.IsLoaded())
        {
        cSize = XRGD.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XRGB.IsLoaded())
        {
        cSize = XRGB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XPRD.IsLoaded())
        {
        if(XPRD->XPRD.IsLoaded())
            TotSize += XPRD->XPRD.GetSize() + 6;
        if(XPRD->XPPA.IsLoaded())
            TotSize += XPRD->XPPA.GetSize() + 6;
        if(XPRD->INAM.IsLoaded())
            TotSize += XPRD->INAM.GetSize() + 6;
        if(XPRD->SCHR.IsLoaded())
            {
            if(XPRD->SCHR->SCHR.IsLoaded())
                TotSize += XPRD->SCHR->SCHR.GetSize() + 6;
            if(XPRD->SCHR->SCDA.IsLoaded())
                {
                cSize = XPRD->SCHR->SCDA.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(XPRD->SCHR->SCTX.IsLoaded())
                {
                cSize = XPRD->SCHR->SCTX.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(XPRD->SCHR->SLSD.IsLoaded())
                TotSize += XPRD->SCHR->SLSD.GetSize() + 6;
            if(XPRD->SCHR->SCVR.IsLoaded())
                {
                cSize = XPRD->SCHR->SCVR.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(XPRD->SCHR->SCRO.IsLoaded())
                TotSize += XPRD->SCHR->SCRO.GetSize() + 6;
            if(XPRD->SCHR->SCRV.IsLoaded())
                TotSize += XPRD->SCHR->SCRV.GetSize() + 6;
            }
        if(XPRD->TNAM.IsLoaded())
            TotSize += XPRD->TNAM.GetSize() + 6;
        }

    if(XLCM.IsLoaded())
        TotSize += XLCM.GetSize() + 6;

    if(XMRC.IsLoaded())
        TotSize += XMRC.GetSize() + 6;

    if(XCNT.IsLoaded())
        TotSize += XCNT.GetSize() + 6;

    if(XRDS.IsLoaded())
        TotSize += XRDS.GetSize() + 6;

    if(XHLP.IsLoaded())
        TotSize += XHLP.GetSize() + 6;

    if(XDCR.IsLoaded())
        TotSize += XDCR.GetSize() + 6;

    if(XLKR.IsLoaded())
        TotSize += XLKR.GetSize() + 6;

    if(XCLP.IsLoaded())
        TotSize += XCLP.GetSize() + 6;

    if(XAPD.IsLoaded())
        TotSize += XAPD.GetSize() + 6;

    if(XAPR.IsLoaded())
        TotSize += XAPR.GetSize() + 6;

    if(XATO.IsLoaded())
        {
        cSize = XATO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XESP.IsLoaded())
        TotSize += XESP.GetSize() + 6;

    if(XEMI.IsLoaded())
        TotSize += XEMI.GetSize() + 6;

    if(XMBR.IsLoaded())
        TotSize += XMBR.GetSize() + 6;

    if(XIBS.IsLoaded())
        TotSize += XIBS.GetSize() + 6;

    if(XSCL.IsLoaded())
        TotSize += XSCL.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

UINT32 ACHRRecord::GetType()
    {
    return 'RHCA';
    }

STRING ACHRRecord::GetStrType()
    {
    return "ACHR";
    }

SINT32 ACHRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case 'XXXX':
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
            case 'DIDE':
                EDID.Read(buffer, subSize, curPos);
                break;
            case 'EMAN':
                NAME.Read(buffer, subSize, curPos);
                break;
            case 'NZEX':
                XEZN.Read(buffer, subSize, curPos);
                break;
            case 'DGRX':
                XRGD.Read(buffer, subSize, curPos);
                break;
            case 'BGRX':
                XRGB.Read(buffer, subSize, curPos);
                break;
            case 'DRPX':
                XPRD.Load();
                XPRD->XPRD.Read(buffer, subSize, curPos);
                break;
            case 'APPX':
                //XPRD.Load();
                //XPRD->XPPA.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MANI':
                XPRD.Load();
                XPRD->INAM.Read(buffer, subSize, curPos);
                break;
            case 'RHCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case 'ADCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case 'XTCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case 'DSLS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case 'RVCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case 'ORCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case 'VRCS':
                XPRD.Load();
                XPRD->SCHR.Load();
                XPRD->SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                XPRD.Load();
                XPRD->TNAM.Read(buffer, subSize, curPos);
                break;
            case 'MCLX':
                XLCM.Read(buffer, subSize, curPos);
                break;
            case 'CRMX':
                XMRC.Read(buffer, subSize, curPos);
                break;
            case 'TNCX':
                XCNT.Read(buffer, subSize, curPos);
                break;
            case 'SDRX':
                XRDS.Read(buffer, subSize, curPos);
                break;
            case 'PLHX':
                XHLP.Read(buffer, subSize, curPos);
                break;
            case 'RCDX':
                XDCR.Read(buffer, subSize, curPos);
                break;
            case 'RKLX':
                XLKR.Read(buffer, subSize, curPos);
                break;
            case 'PLCX':
                XCLP.Read(buffer, subSize, curPos);
                break;
            case 'DPAX':
                XAPD.Read(buffer, subSize, curPos);
                break;
            case 'RPAX':
                XAPR.Read(buffer, subSize, curPos);
                break;
            case 'OTAX':
                XATO.Read(buffer, subSize, curPos);
                break;
            case 'PSEX':
                XESP.Read(buffer, subSize, curPos);
                break;
            case 'IMEX':
                XEMI.Read(buffer, subSize, curPos);
                break;
            case 'RBMX':
                XMBR.Read(buffer, subSize, curPos);
                break;
            case 'SBIX':
                //XIBS.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'LCSX':
                XSCL.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ACHR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    XEZN.Unload();
    XRGD.Unload();
    XRGB.Unload();
    XPRD.Unload();
    XLCM.Unload();
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

SINT32 ACHRRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(NAME.IsLoaded())
        SaveHandler.writeSubRecord('EMAN', NAME.value, NAME.GetSize());

    if(XEZN.IsLoaded())
        SaveHandler.writeSubRecord('NZEX', XEZN.value, XEZN.GetSize());

    if(XRGD.IsLoaded())
        SaveHandler.writeSubRecord('DGRX', XRGD.value, XRGD.GetSize());

    if(XRGB.IsLoaded())
        SaveHandler.writeSubRecord('BGRX', XRGB.value, XRGB.GetSize());

    if(XPRD.IsLoaded())
        {
        if(XPRD->XPRD.IsLoaded())
            SaveHandler.writeSubRecord('DRPX', XPRD->XPRD.value, XPRD->XPRD.GetSize());

        //if(XPRD->XPPA.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('APPX', XPRD->XPPA.value, XPRD->XPPA.GetSize());

        if(XPRD->INAM.IsLoaded())
            SaveHandler.writeSubRecord('MANI', XPRD->INAM.value, XPRD->INAM.GetSize());

        if(XPRD->SCHR.IsLoaded())
            {
            if(XPRD->SCHR->SCHR.IsLoaded())
                SaveHandler.writeSubRecord('RHCS', XPRD->SCHR->SCHR.value, XPRD->SCHR->SCHR.GetSize());

            if(XPRD->SCHR->SCDA.IsLoaded())
                SaveHandler.writeSubRecord('ADCS', XPRD->SCHR->SCDA.value, XPRD->SCHR->SCDA.GetSize());

            if(XPRD->SCHR->SCTX.IsLoaded())
                SaveHandler.writeSubRecord('XTCS', XPRD->SCHR->SCTX.value, XPRD->SCHR->SCTX.GetSize());

            if(XPRD->SCHR->SLSD.IsLoaded())
                SaveHandler.writeSubRecord('DSLS', XPRD->SCHR->SLSD.value, XPRD->SCHR->SLSD.GetSize());

            if(XPRD->SCHR->SCVR.IsLoaded())
                SaveHandler.writeSubRecord('RVCS', XPRD->SCHR->SCVR.value, XPRD->SCHR->SCVR.GetSize());

            if(XPRD->SCHR->SCRO.IsLoaded())
                SaveHandler.writeSubRecord('ORCS', XPRD->SCHR->SCRO.value, XPRD->SCHR->SCRO.GetSize());

            if(XPRD->SCHR->SCRV.IsLoaded())
                SaveHandler.writeSubRecord('VRCS', XPRD->SCHR->SCRV.value, XPRD->SCHR->SCRV.GetSize());

            }
        if(XPRD->TNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANT', XPRD->TNAM.value, XPRD->TNAM.GetSize());

        }

    if(XLCM.IsLoaded())
        SaveHandler.writeSubRecord('MCLX', XLCM.value, XLCM.GetSize());

    if(XMRC.IsLoaded())
        SaveHandler.writeSubRecord('CRMX', XMRC.value, XMRC.GetSize());

    if(XCNT.IsLoaded())
        SaveHandler.writeSubRecord('TNCX', XCNT.value, XCNT.GetSize());

    if(XRDS.IsLoaded())
        SaveHandler.writeSubRecord('SDRX', XRDS.value, XRDS.GetSize());

    if(XHLP.IsLoaded())
        SaveHandler.writeSubRecord('PLHX', XHLP.value, XHLP.GetSize());

    if(XDCR.IsLoaded())
        SaveHandler.writeSubRecord('RCDX', XDCR.value, XDCR.GetSize());

    if(XLKR.IsLoaded())
        SaveHandler.writeSubRecord('RKLX', XLKR.value, XLKR.GetSize());

    if(XCLP.IsLoaded())
        SaveHandler.writeSubRecord('PLCX', XCLP.value, XCLP.GetSize());

    if(XAPD.IsLoaded())
        SaveHandler.writeSubRecord('DPAX', XAPD.value, XAPD.GetSize());

    if(XAPR.IsLoaded())
        SaveHandler.writeSubRecord('RPAX', XAPR.value, XAPR.GetSize());

    if(XATO.IsLoaded())
        SaveHandler.writeSubRecord('OTAX', XATO.value, XATO.GetSize());

    if(XESP.IsLoaded())
        SaveHandler.writeSubRecord('PSEX', XESP.value, XESP.GetSize());

    if(XEMI.IsLoaded())
        SaveHandler.writeSubRecord('IMEX', XEMI.value, XEMI.GetSize());

    if(XMBR.IsLoaded())
        SaveHandler.writeSubRecord('RBMX', XMBR.value, XMBR.GetSize());

    //if(XIBS.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('SBIX', XIBS.value, XIBS.GetSize());

    if(XSCL.IsLoaded())
        SaveHandler.writeSubRecord('LCSX', XSCL.value, XSCL.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    return -1;
    }

bool ACHRRecord::operator ==(const ACHRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NAME == other.NAME &&
            XEZN == other.XEZN &&
            XRGD == other.XRGD &&
            XRGB == other.XRGB &&
            XPRD == other.XPRD &&
            XLCM == other.XLCM &&
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

bool ACHRRecord::operator !=(const ACHRRecord &other) const
    {
    return !(*this == other);
    }
}