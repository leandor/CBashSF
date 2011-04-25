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
#include "PACKRecord.h"

namespace FNV
{
bool PACKRecord::PACKSCRI::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void PACKRecord::PACKSCRI::IsScriptEnabled(bool value)
    {
    if(value)
        SCHR.value.flags |= fIsEnabled;
    else
        SCHR.value.flags &= ~fIsEnabled;
    }

bool PACKRecord::PACKSCRI::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    if(Exact)
        return (SCHR.value.flags & Mask) == Mask;
    else
        return (SCHR.value.flags & Mask) != 0;
    }

void PACKRecord::PACKSCRI::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

PACKRecord::PACKRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

PACKRecord::PACKRecord(PACKRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    PKDT = srcRecord->PKDT;
    PLDT = srcRecord->PLDT;
    PLD2 = srcRecord->PLD2;
    PSDT = srcRecord->PSDT;
    PTDT = srcRecord->PTDT;
    CTDA = srcRecord->CTDA;
    IDLF = srcRecord->IDLF;
    IDLC = srcRecord->IDLC;
    IDLT = srcRecord->IDLT;
    IDLA = srcRecord->IDLA;
    IDLB = srcRecord->IDLB;
    PKED = srcRecord->PKED;
    PKE2 = srcRecord->PKE2;
    CNAM = srcRecord->CNAM;
    PKFD = srcRecord->PKFD;
    PKPT = srcRecord->PKPT;
    PKW3 = srcRecord->PKW3;
    PTD2 = srcRecord->PTD2;
    PUID = srcRecord->PUID;
    PKAM = srcRecord->PKAM;
    PKDD = srcRecord->PKDD;
    if(srcRecord->POBA.IsLoaded())
        {
        POBA.Load();
        POBA->POBA = srcRecord->POBA->POBA;
        POBA->INAM = srcRecord->POBA->INAM;
        if(srcRecord->POBA->SCHR.IsLoaded())
            {
            POBA->SCHR.Load();
            POBA->SCHR->SCHR = srcRecord->POBA->SCHR->SCHR;
            POBA->SCHR->SCDA = srcRecord->POBA->SCHR->SCDA;
            POBA->SCHR->SCTX = srcRecord->POBA->SCHR->SCTX;
            POBA->SCHR->SLSD = srcRecord->POBA->SCHR->SLSD;
            POBA->SCHR->SCVR = srcRecord->POBA->SCHR->SCVR;
            POBA->SCHR->SCRO = srcRecord->POBA->SCHR->SCRO;
            POBA->SCHR->SCRV = srcRecord->POBA->SCHR->SCRV;
            }
        POBA->TNAM = srcRecord->POBA->TNAM;
        }
    if(srcRecord->POEA.IsLoaded())
        {
        POEA.Load();
        POEA->POEA = srcRecord->POEA->POEA;
        POEA->INAM = srcRecord->POEA->INAM;
        if(srcRecord->POEA->SCHR.IsLoaded())
            {
            POEA->SCHR.Load();
            POEA->SCHR->SCHR = srcRecord->POEA->SCHR->SCHR;
            POEA->SCHR->SCDA = srcRecord->POEA->SCHR->SCDA;
            POEA->SCHR->SCTX = srcRecord->POEA->SCHR->SCTX;
            POEA->SCHR->SLSD = srcRecord->POEA->SCHR->SLSD;
            POEA->SCHR->SCVR = srcRecord->POEA->SCHR->SCVR;
            POEA->SCHR->SCRO = srcRecord->POEA->SCHR->SCRO;
            POEA->SCHR->SCRV = srcRecord->POEA->SCHR->SCRV;
            }
        POEA->TNAM = srcRecord->POEA->TNAM;
        }
    if(srcRecord->POCA.IsLoaded())
        {
        POCA.Load();
        POCA->POCA = srcRecord->POCA->POCA;
        POCA->INAM = srcRecord->POCA->INAM;
        if(srcRecord->POCA->SCHR.IsLoaded())
            {
            POCA->SCHR.Load();
            POCA->SCHR->SCHR = srcRecord->POCA->SCHR->SCHR;
            POCA->SCHR->SCDA = srcRecord->POCA->SCHR->SCDA;
            POCA->SCHR->SCTX = srcRecord->POCA->SCHR->SCTX;
            POCA->SCHR->SLSD = srcRecord->POCA->SCHR->SLSD;
            POCA->SCHR->SCVR = srcRecord->POCA->SCHR->SCVR;
            POCA->SCHR->SCRO = srcRecord->POCA->SCHR->SCRO;
            POCA->SCHR->SCRV = srcRecord->POCA->SCHR->SCRV;
            }
        POCA->TNAM = srcRecord->POCA->TNAM;
        }
    return;
    }

PACKRecord::~PACKRecord()
    {
    //
    }

bool PACKRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(PLDT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(PLDT->value);
    //if(PLD2.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(PLD2->value);
    //if(PTDT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(PTDT->value);
    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    if(IDLA.IsLoaded())
        op.Accept(IDLA->value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM->value);
    //if(PTD2.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(PTD2->value);
    //if(PKDD.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(PKDD->value);
    if(POBA.IsLoaded() && POBA->INAM.IsLoaded())
        op.Accept(POBA->INAM->value);
    if(POBA.IsLoaded() && POBA->SCHR.IsLoaded() && POBA->SCHR->SCRO.IsLoaded())
        op.Accept(POBA->SCHR->SCRO->value);
    if(POBA.IsLoaded() && POBA->TNAM.IsLoaded())
        op.Accept(POBA->TNAM->value);
    if(POEA.IsLoaded() && POEA->INAM.IsLoaded())
        op.Accept(POEA->INAM->value);
    if(POEA.IsLoaded() && POEA->SCHR.IsLoaded() && POEA->SCHR->SCRO.IsLoaded())
        op.Accept(POEA->SCHR->SCRO->value);
    if(POEA.IsLoaded() && POEA->TNAM.IsLoaded())
        op.Accept(POEA->TNAM->value);
    if(POCA.IsLoaded() && POCA->INAM.IsLoaded())
        op.Accept(POCA->INAM->value);
    if(POCA.IsLoaded() && POCA->SCHR.IsLoaded() && POCA->SCHR->SCRO.IsLoaded())
        op.Accept(POCA->SCHR->SCRO->value);
    if(POCA.IsLoaded() && POCA->TNAM.IsLoaded())
        op.Accept(POCA->TNAM->value);

    return op.Stop();
    }

UINT32 PACKRecord::GetSize(bool forceCalc)
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

    if(PKDT.IsLoaded())
        TotSize += PKDT.GetSize() + 6;

    if(PLDT.IsLoaded())
        TotSize += PLDT.GetSize() + 6;

    if(PLD2.IsLoaded())
        TotSize += PLD2.GetSize() + 6;

    if(PSDT.IsLoaded())
        TotSize += PSDT.GetSize() + 6;

    if(PTDT.IsLoaded())
        TotSize += PTDT.GetSize() + 6;

    if(CTDA.IsLoaded())
        TotSize += CTDA.GetSize() + 6;

    if(IDLF.IsLoaded())
        TotSize += IDLF.GetSize() + 6;

    if(IDLC.IsLoaded())
        TotSize += IDLC.GetSize() + 6;

    if(IDLT.IsLoaded())
        TotSize += IDLT.GetSize() + 6;

    if(IDLA.IsLoaded())
        TotSize += IDLA.GetSize() + 6;

    if(IDLB.IsLoaded())
        TotSize += IDLB.GetSize() + 6;

    if(PKED.IsLoaded())
        TotSize += PKED.GetSize() + 6;

    if(PKE2.IsLoaded())
        TotSize += PKE2.GetSize() + 6;

    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;

    if(PKFD.IsLoaded())
        TotSize += PKFD.GetSize() + 6;

    if(PKPT.IsLoaded())
        TotSize += PKPT.GetSize() + 6;

    if(PKW3.IsLoaded())
        TotSize += PKW3.GetSize() + 6;

    if(PTD2.IsLoaded())
        TotSize += PTD2.GetSize() + 6;

    if(PUID.IsLoaded())
        TotSize += PUID.GetSize() + 6;

    if(PKAM.IsLoaded())
        TotSize += PKAM.GetSize() + 6;

    if(PKDD.IsLoaded())
        TotSize += PKDD.GetSize() + 6;

    if(POBA.IsLoaded())
        {
        if(POBA->POBA.IsLoaded())
            TotSize += POBA->POBA.GetSize() + 6;
        if(POBA->INAM.IsLoaded())
            TotSize += POBA->INAM.GetSize() + 6;
        if(POBA->SCHR.IsLoaded())
            {
            if(POBA->SCHR->SCHR.IsLoaded())
                TotSize += POBA->SCHR->SCHR.GetSize() + 6;
            if(POBA->SCHR->SCDA.IsLoaded())
                {
                cSize = POBA->SCHR->SCDA.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POBA->SCHR->SCTX.IsLoaded())
                {
                cSize = POBA->SCHR->SCTX.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POBA->SCHR->SLSD.IsLoaded())
                TotSize += POBA->SCHR->SLSD.GetSize() + 6;
            if(POBA->SCHR->SCVR.IsLoaded())
                {
                cSize = POBA->SCHR->SCVR.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POBA->SCHR->SCRO.IsLoaded())
                TotSize += POBA->SCHR->SCRO.GetSize() + 6;
            if(POBA->SCHR->SCRV.IsLoaded())
                TotSize += POBA->SCHR->SCRV.GetSize() + 6;
            }
        if(POBA->TNAM.IsLoaded())
            TotSize += POBA->TNAM.GetSize() + 6;
        }

    if(POEA.IsLoaded())
        {
        if(POEA->POEA.IsLoaded())
            TotSize += POEA->POEA.GetSize() + 6;
        if(POEA->INAM.IsLoaded())
            TotSize += POEA->INAM.GetSize() + 6;
        if(POEA->SCHR.IsLoaded())
            {
            if(POEA->SCHR->SCHR.IsLoaded())
                TotSize += POEA->SCHR->SCHR.GetSize() + 6;
            if(POEA->SCHR->SCDA.IsLoaded())
                {
                cSize = POEA->SCHR->SCDA.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POEA->SCHR->SCTX.IsLoaded())
                {
                cSize = POEA->SCHR->SCTX.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POEA->SCHR->SLSD.IsLoaded())
                TotSize += POEA->SCHR->SLSD.GetSize() + 6;
            if(POEA->SCHR->SCVR.IsLoaded())
                {
                cSize = POEA->SCHR->SCVR.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POEA->SCHR->SCRO.IsLoaded())
                TotSize += POEA->SCHR->SCRO.GetSize() + 6;
            if(POEA->SCHR->SCRV.IsLoaded())
                TotSize += POEA->SCHR->SCRV.GetSize() + 6;
            }
        if(POEA->TNAM.IsLoaded())
            TotSize += POEA->TNAM.GetSize() + 6;
        }

    if(POCA.IsLoaded())
        {
        if(POCA->POCA.IsLoaded())
            TotSize += POCA->POCA.GetSize() + 6;
        if(POCA->INAM.IsLoaded())
            TotSize += POCA->INAM.GetSize() + 6;
        if(POCA->SCHR.IsLoaded())
            {
            if(POCA->SCHR->SCHR.IsLoaded())
                TotSize += POCA->SCHR->SCHR.GetSize() + 6;
            if(POCA->SCHR->SCDA.IsLoaded())
                {
                cSize = POCA->SCHR->SCDA.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POCA->SCHR->SCTX.IsLoaded())
                {
                cSize = POCA->SCHR->SCTX.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POCA->SCHR->SLSD.IsLoaded())
                TotSize += POCA->SCHR->SLSD.GetSize() + 6;
            if(POCA->SCHR->SCVR.IsLoaded())
                {
                cSize = POCA->SCHR->SCVR.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(POCA->SCHR->SCRO.IsLoaded())
                TotSize += POCA->SCHR->SCRO.GetSize() + 6;
            if(POCA->SCHR->SCRV.IsLoaded())
                TotSize += POCA->SCHR->SCRV.GetSize() + 6;
            }
        if(POCA->TNAM.IsLoaded())
            TotSize += POCA->TNAM.GetSize() + 6;
        }

    return TotSize;
    }

UINT32 PACKRecord::GetType()
    {
    return 'KCAP';
    }

STRING PACKRecord::GetStrType()
    {
    return "PACK";
    }

SINT32 PACKRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'TDKP':
                PKDT.Read(buffer, subSize, curPos);
                break;
            case 'TDLP':
                PLDT.Read(buffer, subSize, curPos);
                break;
            case '2DLP':
                PLD2.Read(buffer, subSize, curPos);
                break;
            case 'TDSP':
                PSDT.Read(buffer, subSize, curPos);
                break;
            case 'TDTP':
                PTDT.Read(buffer, subSize, curPos);
                break;
            case 'ADTC':
                CTDA.Read(buffer, subSize, curPos);
                break;
            case 'FLDI':
                IDLF.Read(buffer, subSize, curPos);
                break;
            case 'CLDI':
                IDLC.Read(buffer, subSize, curPos);
                break;
            case 'TLDI':
                IDLT.Read(buffer, subSize, curPos);
                break;
            case 'ALDI':
                IDLA.Read(buffer, subSize, curPos);
                break;
            case 'BLDI':
                IDLB.Read(buffer, subSize, curPos);
                break;
            case 'DEKP':
                //PKED.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case '2EKP':
                PKE2.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'DFKP':
                PKFD.Read(buffer, subSize, curPos);
                break;
            case 'TPKP':
                PKPT.Read(buffer, subSize, curPos);
                break;
            case '3WKP':
                PKW3.Read(buffer, subSize, curPos);
                break;
            case '2DTP':
                PTD2.Read(buffer, subSize, curPos);
                break;
            case 'DIUP':
                //PUID.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MAKP':
                //PKAM.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'DDKP':
                PKDD.Read(buffer, subSize, curPos);
                break;
            case 'ABOP':
                //POBA.Load();
                //POBA->POBA.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MANI':
                POBA.Load();
                POBA->INAM.Read(buffer, subSize, curPos);
                break;
            case 'RHCS':
                POBA.Load();
                POBA->SCHR.Load();
                POBA->SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case 'ADCS':
                POBA.Load();
                POBA->SCHR.Load();
                POBA->SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case 'XTCS':
                POBA.Load();
                POBA->SCHR.Load();
                POBA->SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case 'DSLS':
                POBA.Load();
                POBA->SCHR.Load();
                POBA->SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case 'RVCS':
                POBA.Load();
                POBA->SCHR.Load();
                POBA->SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case 'ORCS':
                POBA.Load();
                POBA->SCHR.Load();
                POBA->SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case 'VRCS':
                POBA.Load();
                POBA->SCHR.Load();
                POBA->SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                POBA.Load();
                POBA->TNAM.Read(buffer, subSize, curPos);
                break;
            case 'AEOP':
                //POEA.Load();
                //POEA->POEA.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MANI':
                POEA.Load();
                POEA->INAM.Read(buffer, subSize, curPos);
                break;
            case 'RHCS':
                POEA.Load();
                POEA->SCHR.Load();
                POEA->SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case 'ADCS':
                POEA.Load();
                POEA->SCHR.Load();
                POEA->SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case 'XTCS':
                POEA.Load();
                POEA->SCHR.Load();
                POEA->SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case 'DSLS':
                POEA.Load();
                POEA->SCHR.Load();
                POEA->SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case 'RVCS':
                POEA.Load();
                POEA->SCHR.Load();
                POEA->SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case 'ORCS':
                POEA.Load();
                POEA->SCHR.Load();
                POEA->SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case 'VRCS':
                POEA.Load();
                POEA->SCHR.Load();
                POEA->SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                POEA.Load();
                POEA->TNAM.Read(buffer, subSize, curPos);
                break;
            case 'ACOP':
                //POCA.Load();
                //POCA->POCA.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MANI':
                POCA.Load();
                POCA->INAM.Read(buffer, subSize, curPos);
                break;
            case 'RHCS':
                POCA.Load();
                POCA->SCHR.Load();
                POCA->SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case 'ADCS':
                POCA.Load();
                POCA->SCHR.Load();
                POCA->SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case 'XTCS':
                POCA.Load();
                POCA->SCHR.Load();
                POCA->SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case 'DSLS':
                POCA.Load();
                POCA->SCHR.Load();
                POCA->SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case 'RVCS':
                POCA.Load();
                POCA->SCHR.Load();
                POCA->SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case 'ORCS':
                POCA.Load();
                POCA->SCHR.Load();
                POCA->SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case 'VRCS':
                POCA.Load();
                POCA->SCHR.Load();
                POCA->SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                POCA.Load();
                POCA->TNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  PACK: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 PACKRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    PKDT.Unload();
    PLDT.Unload();
    PLD2.Unload();
    PSDT.Unload();
    PTDT.Unload();
    CTDA.Unload();
    IDLF.Unload();
    IDLC.Unload();
    IDLT.Unload();
    IDLA.Unload();
    IDLB.Unload();
    //PKED.Unload(); //FILL IN MANUALLY
    PKE2.Unload();
    CNAM.Unload();
    PKFD.Unload();
    PKPT.Unload();
    PKW3.Unload();
    PTD2.Unload();
    //PUID.Unload(); //FILL IN MANUALLY
    //PKAM.Unload(); //FILL IN MANUALLY
    PKDD.Unload();
    POBA.Unload();
    POEA.Unload();
    POCA.Unload();
    return 1;
    }

SINT32 PACKRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(PKDT.IsLoaded())
        SaveHandler.writeSubRecord('TDKP', PKDT.value, PKDT.GetSize());

    if(PLDT.IsLoaded())
        SaveHandler.writeSubRecord('TDLP', PLDT.value, PLDT.GetSize());

    if(PLD2.IsLoaded())
        SaveHandler.writeSubRecord('2DLP', PLD2.value, PLD2.GetSize());

    if(PSDT.IsLoaded())
        SaveHandler.writeSubRecord('TDSP', PSDT.value, PSDT.GetSize());

    if(PTDT.IsLoaded())
        SaveHandler.writeSubRecord('TDTP', PTDT.value, PTDT.GetSize());

    if(CTDA.IsLoaded())
        SaveHandler.writeSubRecord('ADTC', CTDA.value, CTDA.GetSize());

    if(IDLF.IsLoaded())
        SaveHandler.writeSubRecord('FLDI', IDLF.value, IDLF.GetSize());

    if(IDLC.IsLoaded())
        SaveHandler.writeSubRecord('CLDI', IDLC.value, IDLC.GetSize());

    if(IDLT.IsLoaded())
        SaveHandler.writeSubRecord('TLDI', IDLT.value, IDLT.GetSize());

    if(IDLA.IsLoaded())
        SaveHandler.writeSubRecord('ALDI', IDLA.value, IDLA.GetSize());

    if(IDLB.IsLoaded())
        SaveHandler.writeSubRecord('BLDI', IDLB.value, IDLB.GetSize());

    //if(PKED.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('DEKP', PKED.value, PKED.GetSize());

    if(PKE2.IsLoaded())
        SaveHandler.writeSubRecord('2EKP', PKE2.value, PKE2.GetSize());

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());

    if(PKFD.IsLoaded())
        SaveHandler.writeSubRecord('DFKP', PKFD.value, PKFD.GetSize());

    if(PKPT.IsLoaded())
        SaveHandler.writeSubRecord('TPKP', PKPT.value, PKPT.GetSize());

    if(PKW3.IsLoaded())
        SaveHandler.writeSubRecord('3WKP', PKW3.value, PKW3.GetSize());

    if(PTD2.IsLoaded())
        SaveHandler.writeSubRecord('2DTP', PTD2.value, PTD2.GetSize());

    //if(PUID.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('DIUP', PUID.value, PUID.GetSize());

    //if(PKAM.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('MAKP', PKAM.value, PKAM.GetSize());

    if(PKDD.IsLoaded())
        SaveHandler.writeSubRecord('DDKP', PKDD.value, PKDD.GetSize());

    if(POBA.IsLoaded())
        {
        //if(POBA->POBA.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('ABOP', POBA->POBA.value, POBA->POBA.GetSize());

        if(POBA->INAM.IsLoaded())
            SaveHandler.writeSubRecord('MANI', POBA->INAM.value, POBA->INAM.GetSize());

        if(POBA->SCHR.IsLoaded())
            {
            if(POBA->SCHR->SCHR.IsLoaded())
                SaveHandler.writeSubRecord('RHCS', POBA->SCHR->SCHR.value, POBA->SCHR->SCHR.GetSize());

            if(POBA->SCHR->SCDA.IsLoaded())
                SaveHandler.writeSubRecord('ADCS', POBA->SCHR->SCDA.value, POBA->SCHR->SCDA.GetSize());

            if(POBA->SCHR->SCTX.IsLoaded())
                SaveHandler.writeSubRecord('XTCS', POBA->SCHR->SCTX.value, POBA->SCHR->SCTX.GetSize());

            if(POBA->SCHR->SLSD.IsLoaded())
                SaveHandler.writeSubRecord('DSLS', POBA->SCHR->SLSD.value, POBA->SCHR->SLSD.GetSize());

            if(POBA->SCHR->SCVR.IsLoaded())
                SaveHandler.writeSubRecord('RVCS', POBA->SCHR->SCVR.value, POBA->SCHR->SCVR.GetSize());

            if(POBA->SCHR->SCRO.IsLoaded())
                SaveHandler.writeSubRecord('ORCS', POBA->SCHR->SCRO.value, POBA->SCHR->SCRO.GetSize());

            if(POBA->SCHR->SCRV.IsLoaded())
                SaveHandler.writeSubRecord('VRCS', POBA->SCHR->SCRV.value, POBA->SCHR->SCRV.GetSize());

            }
        if(POBA->TNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANT', POBA->TNAM.value, POBA->TNAM.GetSize());

        }

    if(POEA.IsLoaded())
        {
        //if(POEA->POEA.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('AEOP', POEA->POEA.value, POEA->POEA.GetSize());

        if(POEA->INAM.IsLoaded())
            SaveHandler.writeSubRecord('MANI', POEA->INAM.value, POEA->INAM.GetSize());

        if(POEA->SCHR.IsLoaded())
            {
            if(POEA->SCHR->SCHR.IsLoaded())
                SaveHandler.writeSubRecord('RHCS', POEA->SCHR->SCHR.value, POEA->SCHR->SCHR.GetSize());

            if(POEA->SCHR->SCDA.IsLoaded())
                SaveHandler.writeSubRecord('ADCS', POEA->SCHR->SCDA.value, POEA->SCHR->SCDA.GetSize());

            if(POEA->SCHR->SCTX.IsLoaded())
                SaveHandler.writeSubRecord('XTCS', POEA->SCHR->SCTX.value, POEA->SCHR->SCTX.GetSize());

            if(POEA->SCHR->SLSD.IsLoaded())
                SaveHandler.writeSubRecord('DSLS', POEA->SCHR->SLSD.value, POEA->SCHR->SLSD.GetSize());

            if(POEA->SCHR->SCVR.IsLoaded())
                SaveHandler.writeSubRecord('RVCS', POEA->SCHR->SCVR.value, POEA->SCHR->SCVR.GetSize());

            if(POEA->SCHR->SCRO.IsLoaded())
                SaveHandler.writeSubRecord('ORCS', POEA->SCHR->SCRO.value, POEA->SCHR->SCRO.GetSize());

            if(POEA->SCHR->SCRV.IsLoaded())
                SaveHandler.writeSubRecord('VRCS', POEA->SCHR->SCRV.value, POEA->SCHR->SCRV.GetSize());

            }
        if(POEA->TNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANT', POEA->TNAM.value, POEA->TNAM.GetSize());

        }

    if(POCA.IsLoaded())
        {
        //if(POCA->POCA.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('ACOP', POCA->POCA.value, POCA->POCA.GetSize());

        if(POCA->INAM.IsLoaded())
            SaveHandler.writeSubRecord('MANI', POCA->INAM.value, POCA->INAM.GetSize());

        if(POCA->SCHR.IsLoaded())
            {
            if(POCA->SCHR->SCHR.IsLoaded())
                SaveHandler.writeSubRecord('RHCS', POCA->SCHR->SCHR.value, POCA->SCHR->SCHR.GetSize());

            if(POCA->SCHR->SCDA.IsLoaded())
                SaveHandler.writeSubRecord('ADCS', POCA->SCHR->SCDA.value, POCA->SCHR->SCDA.GetSize());

            if(POCA->SCHR->SCTX.IsLoaded())
                SaveHandler.writeSubRecord('XTCS', POCA->SCHR->SCTX.value, POCA->SCHR->SCTX.GetSize());

            if(POCA->SCHR->SLSD.IsLoaded())
                SaveHandler.writeSubRecord('DSLS', POCA->SCHR->SLSD.value, POCA->SCHR->SLSD.GetSize());

            if(POCA->SCHR->SCVR.IsLoaded())
                SaveHandler.writeSubRecord('RVCS', POCA->SCHR->SCVR.value, POCA->SCHR->SCVR.GetSize());

            if(POCA->SCHR->SCRO.IsLoaded())
                SaveHandler.writeSubRecord('ORCS', POCA->SCHR->SCRO.value, POCA->SCHR->SCRO.GetSize());

            if(POCA->SCHR->SCRV.IsLoaded())
                SaveHandler.writeSubRecord('VRCS', POCA->SCHR->SCRV.value, POCA->SCHR->SCRV.GetSize());

            }
        if(POCA->TNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANT', POCA->TNAM.value, POCA->TNAM.GetSize());

        }

    return -1;
    }

bool PACKRecord::operator ==(const PACKRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            PKDT == other.PKDT &&
            PLDT == other.PLDT &&
            PLD2 == other.PLD2 &&
            PSDT == other.PSDT &&
            PTDT == other.PTDT &&
            CTDA == other.CTDA &&
            IDLF == other.IDLF &&
            IDLC == other.IDLC &&
            IDLT == other.IDLT &&
            IDLA == other.IDLA &&
            IDLB == other.IDLB &&
            //Empty &&
            PKE2 == other.PKE2 &&
            CNAM == other.CNAM &&
            PKFD == other.PKFD &&
            PKPT == other.PKPT &&
            PKW3 == other.PKW3 &&
            PTD2 == other.PTD2 &&
            //Empty &&
            //Empty &&
            PKDD == other.PKDD &&
            //EmptyINAM == other.INAM &&
            //EmptyINAM == other.INAM &&
            //EmptyINAM == other.INAM);
    }

bool PACKRecord::operator !=(const PACKRecord &other) const
    {
    return !(*this == other);
    }
}