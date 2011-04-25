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
#include "REGNRecord.h"

namespace FNV
{
REGNRecord::REGNRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

REGNRecord::REGNRecord(REGNRecord *srcRecord):
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
    if(srcRecord->ICON.IsLoaded())
        {
        ICON.Load();
        ICON->ICON = srcRecord->ICON->ICON;
        ICON->MICO = srcRecord->ICON->MICO;
        }
    RCLR = srcRecord->RCLR;
    WNAM = srcRecord->WNAM;
    RPLI = srcRecord->RPLI;
    RPLD = srcRecord->RPLD;
    RDAT = srcRecord->RDAT;
    RDOT = srcRecord->RDOT;
    RDMP = srcRecord->RDMP;
    RDGS = srcRecord->RDGS;
    RDMD = srcRecord->RDMD;
    RDMO = srcRecord->RDMO;
    RDSI = srcRecord->RDSI;
    RDSB = srcRecord->RDSB;
    RDSD = srcRecord->RDSD;
    RDWT = srcRecord->RDWT;
    RDID = srcRecord->RDID;
    return;
    }

REGNRecord::~REGNRecord()
    {
    //
    }

bool REGNRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(WNAM.IsLoaded())
        op.Accept(WNAM->value);
    //if(RDOT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(RDOT->value);
    //if(RDGS.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(RDGS->value);
    if(RDMO.IsLoaded())
        op.Accept(RDMO->value);
    if(RDSI.IsLoaded())
        op.Accept(RDSI->value);
    if(RDSB.IsLoaded())
        op.Accept(RDSB->value);
    //if(RDSD.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(RDSD->value);
    //if(RDWT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(RDWT->value);
    //if(RDID.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(RDID->value);

    return op.Stop();
    }

UINT32 REGNRecord::GetSize(bool forceCalc)
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

    if(RCLR.IsLoaded())
        TotSize += RCLR.GetSize() + 6;

    if(WNAM.IsLoaded())
        TotSize += WNAM.GetSize() + 6;

    if(RPLI.IsLoaded())
        TotSize += RPLI.GetSize() + 6;

    if(RPLD.IsLoaded())
        TotSize += RPLD.GetSize() + 6;

    if(RDAT.IsLoaded())
        TotSize += RDAT.GetSize() + 6;

    if(RDOT.IsLoaded())
        TotSize += RDOT.GetSize() + 6;

    if(RDMP.IsLoaded())
        {
        cSize = RDMP.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(RDGS.IsLoaded())
        TotSize += RDGS.GetSize() + 6;

    if(RDMD.IsLoaded())
        TotSize += RDMD.GetSize() + 6;

    if(RDMO.IsLoaded())
        TotSize += RDMO.GetSize() + 6;

    if(RDSI.IsLoaded())
        TotSize += RDSI.GetSize() + 6;

    if(RDSB.IsLoaded())
        TotSize += RDSB.GetSize() + 6;

    if(RDSD.IsLoaded())
        TotSize += RDSD.GetSize() + 6;

    if(RDWT.IsLoaded())
        TotSize += RDWT.GetSize() + 6;

    if(RDID.IsLoaded())
        TotSize += RDID.GetSize() + 6;

    return TotSize;
    }

UINT32 REGNRecord::GetType()
    {
    return 'NGER';
    }

STRING REGNRecord::GetStrType()
    {
    return "REGN";
    }

SINT32 REGNRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'NOCI':
                ICON.Load();
                ICON->ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                ICON.Load();
                ICON->MICO.Read(buffer, subSize, curPos);
                break;
            case 'RLCR':
                RCLR.Read(buffer, subSize, curPos);
                break;
            case 'MANW':
                WNAM.Read(buffer, subSize, curPos);
                break;
            case 'ILPR':
                RPLI.Read(buffer, subSize, curPos);
                break;
            case 'DLPR':
                RPLD.Read(buffer, subSize, curPos);
                break;
            case 'TADR':
                RDAT.Read(buffer, subSize, curPos);
                break;
            case 'TODR':
                RDOT.Read(buffer, subSize, curPos);
                break;
            case 'PMDR':
                RDMP.Read(buffer, subSize, curPos);
                break;
            case 'SGDR':
                RDGS.Read(buffer, subSize, curPos);
                break;
            case 'DMDR':
                RDMD.Read(buffer, subSize, curPos);
                break;
            case 'OMDR':
                RDMO.Read(buffer, subSize, curPos);
                break;
            case 'ISDR':
                RDSI.Read(buffer, subSize, curPos);
                break;
            case 'BSDR':
                RDSB.Read(buffer, subSize, curPos);
                break;
            case 'DSDR':
                RDSD.Read(buffer, subSize, curPos);
                break;
            case 'TWDR':
                RDWT.Read(buffer, subSize, curPos);
                break;
            case 'DIDR':
                RDID.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  REGN: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 REGNRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    RCLR.Unload();
    WNAM.Unload();
    RPLI.Unload();
    RPLD.Unload();
    RDAT.Unload();
    RDOT.Unload();
    RDMP.Unload();
    RDGS.Unload();
    RDMD.Unload();
    RDMO.Unload();
    RDSI.Unload();
    RDSB.Unload();
    RDSD.Unload();
    RDWT.Unload();
    RDID.Unload();
    return 1;
    }

SINT32 REGNRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            SaveHandler.writeSubRecord('NOCI', ICON->ICON.value, ICON->ICON.GetSize());

        if(ICON->MICO.IsLoaded())
            SaveHandler.writeSubRecord('OCIM', ICON->MICO.value, ICON->MICO.GetSize());

        }

    if(RCLR.IsLoaded())
        SaveHandler.writeSubRecord('RLCR', RCLR.value, RCLR.GetSize());

    if(WNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANW', WNAM.value, WNAM.GetSize());

    if(RPLI.IsLoaded())
        SaveHandler.writeSubRecord('ILPR', RPLI.value, RPLI.GetSize());

    if(RPLD.IsLoaded())
        SaveHandler.writeSubRecord('DLPR', RPLD.value, RPLD.GetSize());

    if(RDAT.IsLoaded())
        SaveHandler.writeSubRecord('TADR', RDAT.value, RDAT.GetSize());

    if(RDOT.IsLoaded())
        SaveHandler.writeSubRecord('TODR', RDOT.value, RDOT.GetSize());

    if(RDMP.IsLoaded())
        SaveHandler.writeSubRecord('PMDR', RDMP.value, RDMP.GetSize());

    if(RDGS.IsLoaded())
        SaveHandler.writeSubRecord('SGDR', RDGS.value, RDGS.GetSize());

    if(RDMD.IsLoaded())
        SaveHandler.writeSubRecord('DMDR', RDMD.value, RDMD.GetSize());

    if(RDMO.IsLoaded())
        SaveHandler.writeSubRecord('OMDR', RDMO.value, RDMO.GetSize());

    if(RDSI.IsLoaded())
        SaveHandler.writeSubRecord('ISDR', RDSI.value, RDSI.GetSize());

    if(RDSB.IsLoaded())
        SaveHandler.writeSubRecord('BSDR', RDSB.value, RDSB.GetSize());

    if(RDSD.IsLoaded())
        SaveHandler.writeSubRecord('DSDR', RDSD.value, RDSD.GetSize());

    if(RDWT.IsLoaded())
        SaveHandler.writeSubRecord('TWDR', RDWT.value, RDWT.GetSize());

    if(RDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDR', RDID.value, RDID.GetSize());

    return -1;
    }

bool REGNRecord::operator ==(const REGNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON == other.ICON &&
            RCLR == other.RCLR &&
            WNAM == other.WNAM &&
            RPLI == other.RPLI &&
            RPLD == other.RPLD &&
            RDAT == other.RDAT &&
            RDOT == other.RDOT &&
            RDMP.equalsi(other.RDMP) &&
            RDGS == other.RDGS &&
            RDMD == other.RDMD &&
            RDMO == other.RDMO &&
            RDSI == other.RDSI &&
            RDSB == other.RDSB &&
            RDSD == other.RDSD &&
            RDWT == other.RDWT &&
            RDID == other.RDID);
    }

bool REGNRecord::operator !=(const REGNRecord &other) const
    {
    return !(*this == other);
    }
}