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
#include "PERKRecord.h"

namespace FNV
{
PERKRecord::PERKRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

PERKRecord::PERKRecord(PERKRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    DESC = srcRecord->DESC;
    if(srcRecord->ICON.IsLoaded())
        {
        ICON.Load();
        ICON->ICON = srcRecord->ICON->ICON;
        ICON->MICO = srcRecord->ICON->MICO;
        }
    CTDA = srcRecord->CTDA;
    DATA = srcRecord->DATA;
    PRKE = srcRecord->PRKE;
    PRKC = srcRecord->PRKC;
    CTDA = srcRecord->CTDA;
    if(srcRecord->EPFT.IsLoaded())
        {
        EPFT.Load();
        EPFT->EPFT = srcRecord->EPFT->EPFT;
        EPFT->DATA = srcRecord->EPFT->DATA;
        }
    EPF2 = srcRecord->EPF2;
    EPF3 = srcRecord->EPF3;
    if(srcRecord->SCHR.IsLoaded())
        {
        SCHR.Load();
        SCHR->SCHR = srcRecord->SCHR->SCHR;
        SCHR->SCDA = srcRecord->SCHR->SCDA;
        SCHR->SCTX = srcRecord->SCHR->SCTX;
        SCHR->SLSD = srcRecord->SCHR->SLSD;
        SCHR->SCVR = srcRecord->SCHR->SCVR;
        SCHR->SCRO = srcRecord->SCHR->SCRO;
        SCHR->SCRV = srcRecord->SCHR->SCRV;
        }
    PRKF = srcRecord->PRKF;
    return;
    }

PERKRecord::~PERKRecord()
    {
    //
    }

bool PERKRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    //if(PRKE.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(PRKE->value);
    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    if(EPFT.IsLoaded() && EPFT->DATA.IsLoaded())
        op.Accept(EPFT->DATA->value);
    if(SCHR.IsLoaded() && SCHR->SCRO.IsLoaded())
        op.Accept(SCHR->SCRO->value);

    return op.Stop();
    }

UINT32 PERKRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-16];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            {
            cSize = ICON->ICON.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(ICON->MICO.IsLoaded())
            {
            cSize = ICON->MICO.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(CTDA.IsLoaded())
        TotSize += CTDA.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(PRKE.IsLoaded())
        TotSize += PRKE.GetSize() + 6;

    if(PRKC.IsLoaded())
        TotSize += PRKC.GetSize() + 6;

    if(CTDA.IsLoaded())
        TotSize += CTDA.GetSize() + 6;

    if(EPFT.IsLoaded())
        {
        if(EPFT->EPFT.IsLoaded())
            TotSize += EPFT->EPFT.GetSize() + 6;
        if(EPFT->DATA.IsLoaded())
            TotSize += EPFT->DATA.GetSize() + 6;
        }

    if(EPF2.IsLoaded())
        {
        cSize = EPF2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(EPF3.IsLoaded())
        TotSize += EPF3.GetSize() + 6;

    if(SCHR.IsLoaded())
        {
        if(SCHR->SCHR.IsLoaded())
            TotSize += SCHR->SCHR.GetSize() + 6;
        if(SCHR->SCDA.IsLoaded())
            {
            cSize = SCHR->SCDA.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(SCHR->SCTX.IsLoaded())
            {
            cSize = SCHR->SCTX.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(SCHR->SLSD.IsLoaded())
            TotSize += SCHR->SLSD.GetSize() + 6;
        if(SCHR->SCVR.IsLoaded())
            {
            cSize = SCHR->SCVR.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(SCHR->SCRO.IsLoaded())
            TotSize += SCHR->SCRO.GetSize() + 6;
        if(SCHR->SCRV.IsLoaded())
            TotSize += SCHR->SCRV.GetSize() + 6;
        }

    if(PRKF.IsLoaded())
        TotSize += PRKF.GetSize() + 6;

    return TotSize;
    }

UINT32 PERKRecord::GetType()
    {
    return 'KREP';
    }

STRING PERKRecord::GetStrType()
    {
    return "PERK";
    }

SINT32 PERKRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'CSED':
                DESC.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Load();
                ICON->ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                ICON.Load();
                ICON->MICO.Read(buffer, subSize, curPos);
                break;
            case 'ADTC':
                CTDA.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'EKRP':
                PRKE.Read(buffer, subSize, curPos);
                break;
            case 'CKRP':
                PRKC.Read(buffer, subSize, curPos);
                break;
            case 'ADTC':
                CTDA.Read(buffer, subSize, curPos);
                break;
            case 'TFPE':
                EPFT.Load();
                EPFT->EPFT.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                EPFT.Load();
                EPFT->DATA.Read(buffer, subSize, curPos);
                break;
            case '2FPE':
                EPF2.Read(buffer, subSize, curPos);
                break;
            case '3FPE':
                EPF3.Read(buffer, subSize, curPos);
                break;
            case 'RHCS':
                SCHR.Load();
                SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case 'ADCS':
                SCHR.Load();
                SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case 'XTCS':
                SCHR.Load();
                SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case 'DSLS':
                SCHR.Load();
                SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case 'RVCS':
                SCHR.Load();
                SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case 'ORCS':
                SCHR.Load();
                SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case 'VRCS':
                SCHR.Load();
                SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case 'FKRP':
                //PRKF.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  PERK: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 PERKRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    CTDA.Unload();
    DATA.Unload();
    PRKE.Unload();
    PRKC.Unload();
    CTDA.Unload();
    EPFT.Unload();
    EPF2.Unload();
    EPF3.Unload();
    SCHR.Unload();
    //PRKF.Unload(); //FILL IN MANUALLY
    return 1;
    }

SINT32 PERKRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord('CSED', DESC.value, DESC.GetSize());

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            SaveHandler.writeSubRecord('NOCI', ICON->ICON.value, ICON->ICON.GetSize());

        if(ICON->MICO.IsLoaded())
            SaveHandler.writeSubRecord('OCIM', ICON->MICO.value, ICON->MICO.GetSize());

        }

    if(CTDA.IsLoaded())
        SaveHandler.writeSubRecord('ADTC', CTDA.value, CTDA.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(PRKE.IsLoaded())
        SaveHandler.writeSubRecord('EKRP', PRKE.value, PRKE.GetSize());

    if(PRKC.IsLoaded())
        SaveHandler.writeSubRecord('CKRP', PRKC.value, PRKC.GetSize());

    if(CTDA.IsLoaded())
        SaveHandler.writeSubRecord('ADTC', CTDA.value, CTDA.GetSize());

    if(EPFT.IsLoaded())
        {
        if(EPFT->EPFT.IsLoaded())
            SaveHandler.writeSubRecord('TFPE', EPFT->EPFT.value, EPFT->EPFT.GetSize());

        if(EPFT->DATA.IsLoaded())
            SaveHandler.writeSubRecord('ATAD', EPFT->DATA.value, EPFT->DATA.GetSize());

        }

    if(EPF2.IsLoaded())
        SaveHandler.writeSubRecord('2FPE', EPF2.value, EPF2.GetSize());

    if(EPF3.IsLoaded())
        SaveHandler.writeSubRecord('3FPE', EPF3.value, EPF3.GetSize());

    if(SCHR.IsLoaded())
        {
        if(SCHR->SCHR.IsLoaded())
            SaveHandler.writeSubRecord('RHCS', SCHR->SCHR.value, SCHR->SCHR.GetSize());

        if(SCHR->SCDA.IsLoaded())
            SaveHandler.writeSubRecord('ADCS', SCHR->SCDA.value, SCHR->SCDA.GetSize());

        if(SCHR->SCTX.IsLoaded())
            SaveHandler.writeSubRecord('XTCS', SCHR->SCTX.value, SCHR->SCTX.GetSize());

        if(SCHR->SLSD.IsLoaded())
            SaveHandler.writeSubRecord('DSLS', SCHR->SLSD.value, SCHR->SLSD.GetSize());

        if(SCHR->SCVR.IsLoaded())
            SaveHandler.writeSubRecord('RVCS', SCHR->SCVR.value, SCHR->SCVR.GetSize());

        if(SCHR->SCRO.IsLoaded())
            SaveHandler.writeSubRecord('ORCS', SCHR->SCRO.value, SCHR->SCRO.GetSize());

        if(SCHR->SCRV.IsLoaded())
            SaveHandler.writeSubRecord('VRCS', SCHR->SCRV.value, SCHR->SCRV.GetSize());

        }

    //if(PRKF.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('FKRP', PRKF.value, PRKF.GetSize());

    return -1;
    }

bool PERKRecord::operator ==(const PERKRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON == other.ICON &&
            CTDA == other.CTDA &&
            DATA == other.DATA &&
            PRKE == other.PRKE &&
            PRKC == other.PRKC &&
            CTDA == other.CTDA &&
            EPFT == other.EPFT &&
            EPF2.equalsi(other.EPF2) &&
            EPF3 == other.EPF3 &&
            SCHR == other.SCHR &&
            //Empty);
    }

bool PERKRecord::operator !=(const PERKRecord &other) const
    {
    return !(*this == other);
    }
}