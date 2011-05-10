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
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
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
    SCHR.value.flags = value ? (SCHR.value.flags | fIsEnabled) : (SCHR.value.flags & ~fIsEnabled);
    }

bool QUSTRecord::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (SCHR.value.flags & Mask) == Mask : (SCHR.value.flags & Mask) != 0;
    }

void QUSTRecord::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

UINT32 QUSTRecord::GetType()
    {
    return REV32(QUST);
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize, curPos);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, curPos);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, curPos);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize, curPos);
                break;
            case REV32(INDX):
                INDX.Read(buffer, subSize, curPos);
                break;
            case REV32(QSDT):
                QSDT.Read(buffer, subSize, curPos);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(SCHR):
                SCHR.Load();
                SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCDA):
                SCHR.Load();
                SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case REV32(SCTX):
                SCHR.Load();
                SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case REV32(SLSD):
                SCHR.Load();
                SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case REV32(SCVR):
                SCHR.Load();
                SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRO):
                SCHR.Load();
                SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRV):
                SCHR.Load();
                SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize, curPos);
                break;
            case REV32(QOBJ):
                QOBJ.Read(buffer, subSize, curPos);
                break;
            case REV32(NNAM):
                NNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(QSTA):
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
    MICO.Unload();
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

SINT32 QUSTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(SCRI);
    WRITE(FULL);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(DATA);
    WRITE(CTDA);
    WRITE(INDX);
    WRITE(QSDT);
    WRITE(CNAM);

    if(SCHR.IsLoaded())
        {
        if(SCHR->SCHR.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCHR), SCHR->SCHR.value, SCHR->SCHR.GetSize());

        if(SCHR->SCDA.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCDA), SCHR->SCDA.value, SCHR->SCDA.GetSize());

        if(SCHR->SCTX.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCTX), SCHR->SCTX.value, SCHR->SCTX.GetSize());

        if(SCHR->SLSD.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SLSD), SCHR->SLSD.value, SCHR->SLSD.GetSize());

        if(SCHR->SCVR.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCVR), SCHR->SCVR.value, SCHR->SCVR.GetSize());

        if(SCHR->SCRO.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCRO), SCHR->SCRO.value, SCHR->SCRO.GetSize());

        if(SCHR->SCRV.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCRV), SCHR->SCRV.value, SCHR->SCRV.GetSize());

        }

    WRITE(NAM0);
    WRITE(QOBJ);
    WRITE(NNAM);
    WRITE(QSTA);

    return -1;
    }

bool QUSTRecord::operator ==(const QUSTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            SCRI == other.SCRI &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
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