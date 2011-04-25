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
#include "QUSTRecord.h"

namespace FNV
{
QUSTRecord::QUSTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

QUSTRecord::QUSTRecord(QUSTRecord *srcRecord):
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
    SCRI = srcRecord->SCRI;
    FULL = srcRecord->FULL;
    if(srcRecord->ICON.IsLoaded())
        {
        ICON.Load();
        ICON->ICON = srcRecord->ICON->ICON;
        ICON->MICO = srcRecord->ICON->MICO;
        }
    DATA = srcRecord->DATA;
    CTDA = srcRecord->CTDA;
    INDX = srcRecord->INDX;
    QSDT = srcRecord->QSDT;
    CNAM = srcRecord->CNAM;
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
    NAM0 = srcRecord->NAM0;
    QOBJ = srcRecord->QOBJ;
    NNAM = srcRecord->NNAM;
    QSTA = srcRecord->QSTA;
    return;
    }

QUSTRecord::~QUSTRecord()
    {
    //
    }

bool QUSTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    if(SCHR.IsLoaded() && SCHR->SCRO.IsLoaded())
        op.Accept(SCHR->SCRO->value);
    if(NAM0.IsLoaded())
        op.Accept(NAM0->value);
    //if(QSTA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(QSTA->value);

    return op.Stop();
    }

bool QUSTRecord::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void QUSTRecord::IsScriptEnabled(bool value)
    {
    if(value)
        SCHR.value.flags |= fIsEnabled;
    else
        SCHR.value.flags &= ~fIsEnabled;
    }

bool QUSTRecord::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    if(Exact)
        return (SCHR.value.flags & Mask) == Mask;
    else
        return (SCHR.value.flags & Mask) != 0;
    }

void QUSTRecord::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

UINT32 QUSTRecord::GetSize(bool forceCalc)
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

    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
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

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(CTDA.IsLoaded())
        TotSize += CTDA.GetSize() + 6;

    if(INDX.IsLoaded())
        TotSize += INDX.GetSize() + 6;

    if(QSDT.IsLoaded())
        TotSize += QSDT.GetSize() + 6;

    if(CNAM.IsLoaded())
        {
        cSize = CNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

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

    if(NAM0.IsLoaded())
        TotSize += NAM0.GetSize() + 6;

    if(QOBJ.IsLoaded())
        TotSize += QOBJ.GetSize() + 6;

    if(NNAM.IsLoaded())
        {
        cSize = NNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(QSTA.IsLoaded())
        TotSize += QSTA.GetSize() + 6;

    return TotSize;
    }

UINT32 QUSTRecord::GetType()
    {
    return 'TSUQ';
    }

STRING QUSTRecord::GetStrType()
    {
    return "QUST";
    }

SINT32 QUSTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Load();
                ICON->ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                ICON.Load();
                ICON->MICO.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'ADTC':
                CTDA.Read(buffer, subSize, curPos);
                break;
            case 'XDNI':
                INDX.Read(buffer, subSize, curPos);
                break;
            case 'TDSQ':
                QSDT.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
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
            case '0MAN':
                NAM0.Read(buffer, subSize, curPos);
                break;
            case 'JBOQ':
                QOBJ.Read(buffer, subSize, curPos);
                break;
            case 'MANN':
                NNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATSQ':
                QSTA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  QUST: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 QUSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    SCRI.Unload();
    FULL.Unload();
    ICON.Unload();
    DATA.Unload();
    CTDA.Unload();
    INDX.Unload();
    QSDT.Unload();
    CNAM.Unload();
    SCHR.Unload();
    NAM0.Unload();
    QOBJ.Unload();
    NNAM.Unload();
    QSTA.Unload();
    return 1;
    }

SINT32 QUSTRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord('IRCS', SCRI.value, SCRI.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            SaveHandler.writeSubRecord('NOCI', ICON->ICON.value, ICON->ICON.GetSize());

        if(ICON->MICO.IsLoaded())
            SaveHandler.writeSubRecord('OCIM', ICON->MICO.value, ICON->MICO.GetSize());

        }

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(CTDA.IsLoaded())
        SaveHandler.writeSubRecord('ADTC', CTDA.value, CTDA.GetSize());

    if(INDX.IsLoaded())
        SaveHandler.writeSubRecord('XDNI', INDX.value, INDX.GetSize());

    if(QSDT.IsLoaded())
        SaveHandler.writeSubRecord('TDSQ', QSDT.value, QSDT.GetSize());

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());

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

    if(NAM0.IsLoaded())
        SaveHandler.writeSubRecord('0MAN', NAM0.value, NAM0.GetSize());

    if(QOBJ.IsLoaded())
        SaveHandler.writeSubRecord('JBOQ', QOBJ.value, QOBJ.GetSize());

    if(NNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANN', NNAM.value, NNAM.GetSize());

    if(QSTA.IsLoaded())
        SaveHandler.writeSubRecord('ATSQ', QSTA.value, QSTA.GetSize());

    return -1;
    }

bool QUSTRecord::operator ==(const QUSTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            SCRI == other.SCRI &&
            FULL.equals(other.FULL) &&
            ICON == other.ICON &&
            DATA == other.DATA &&
            CTDA == other.CTDA &&
            INDX == other.INDX &&
            QSDT == other.QSDT &&
            CNAM.equalsi(other.CNAM) &&
            SCHR == other.SCHR &&
            NAM0 == other.NAM0 &&
            QOBJ == other.QOBJ &&
            NNAM.equalsi(other.NNAM) &&
            QSTA == other.QSTA);
    }

bool QUSTRecord::operator !=(const QUSTRecord &other) const
    {
    return !(*this == other);
    }
}