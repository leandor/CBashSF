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
    FNVRecord(_recData)
    {
    //
    }

REGNRecord::REGNRecord(REGNRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
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
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
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
    MICO.Unload();
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

SINT32 REGNRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(RCLR);
    WRITE(WNAM);
    WRITE(RPLI);
    WRITE(RPLD);
    WRITE(RDAT);
    WRITE(RDOT);
    WRITE(RDMP);
    WRITE(RDGS);
    WRITE(RDMD);
    WRITE(RDMO);
    WRITE(RDSI);
    WRITE(RDSB);
    WRITE(RDSD);
    WRITE(RDWT);
    WRITE(RDID);

    return -1;
    }

bool REGNRecord::operator ==(const REGNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
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