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
#include "WRLDRecord.h"

namespace FNV
{
WRLDRecord::WRLDRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

WRLDRecord::WRLDRecord(WRLDRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    XEZN = srcRecord->XEZN;
    WNAM = srcRecord->WNAM;
    PNAM = srcRecord->PNAM;
    CNAM = srcRecord->CNAM;
    NAM2 = srcRecord->NAM2;
    NAM3 = srcRecord->NAM3;
    NAM4 = srcRecord->NAM4;
    DNAM = srcRecord->DNAM;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    MNAM = srcRecord->MNAM;
    ONAM = srcRecord->ONAM;
    INAM = srcRecord->INAM;
    DATA = srcRecord->DATA;
    NAM0 = srcRecord->NAM0;
    NAM9 = srcRecord->NAM9;
    ZNAM = srcRecord->ZNAM;
    NNAM = srcRecord->NNAM;
    XNAM = srcRecord->XNAM;
    IMPS = srcRecord->IMPS;
    IMPF = srcRecord->IMPF;
    OFST = srcRecord->OFST;
    return;
    }

WRLDRecord::~WRLDRecord()
    {
    //
    }

bool WRLDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(XEZN.IsLoaded())
        op.Accept(XEZN->value);
    if(WNAM.IsLoaded())
        op.Accept(WNAM->value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM->value);
    if(NAM2.IsLoaded())
        op.Accept(NAM2->value);
    if(NAM3.IsLoaded())
        op.Accept(NAM3->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    //if(IMPS.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(IMPS->value);

    return op.Stop();
    }

UINT32 WRLDRecord::GetType()
    {
    return 'DLRW';
    }

STRING WRLDRecord::GetStrType()
    {
    return "WRLD";
    }

SINT32 WRLDRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'NZEX':
                XEZN.Read(buffer, subSize, curPos);
                break;
            case 'MANW':
                WNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case '2MAN':
                NAM2.Read(buffer, subSize, curPos);
                break;
            case '3MAN':
                NAM3.Read(buffer, subSize, curPos);
                break;
            case '4MAN':
                NAM4.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                MNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                ONAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case '0MAN':
                NAM0.Read(buffer, subSize, curPos);
                break;
            case '9MAN':
                NAM9.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANN':
                NNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'SPMI':
                IMPS.Read(buffer, subSize, curPos);
                break;
            case 'FPMI':
                IMPF.Read(buffer, subSize, curPos);
                break;
            case 'TSFO':
                OFST.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  WRLD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 WRLDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    XEZN.Unload();
    WNAM.Unload();
    PNAM.Unload();
    CNAM.Unload();
    NAM2.Unload();
    NAM3.Unload();
    NAM4.Unload();
    DNAM.Unload();
    ICON.Unload();
    MICO.Unload();
    MNAM.Unload();
    ONAM.Unload();
    INAM.Unload();
    DATA.Unload();
    NAM0.Unload();
    NAM9.Unload();
    ZNAM.Unload();
    NNAM.Unload();
    XNAM.Unload();
    IMPS.Unload();
    IMPF.Unload();
    OFST.Unload();
    return 1;
    }

SINT32 WRLDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(XEZN);
    WRITE(WNAM);
    WRITE(PNAM);
    WRITE(CNAM);
    WRITE(NAM2);
    WRITE(NAM3);
    WRITE(NAM4);
    WRITE(DNAM);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(MNAM);
    WRITE(ONAM);
    WRITE(INAM);
    WRITE(DATA);
    WRITE(NAM0);
    WRITE(NAM9);
    WRITE(ZNAM);
    WRITE(NNAM);
    WRITE(XNAM);
    WRITE(IMPS);
    WRITE(IMPF);
    WRITE(OFST);

    return -1;
    }

bool WRLDRecord::operator ==(const WRLDRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            XEZN == other.XEZN &&
            WNAM == other.WNAM &&
            PNAM == other.PNAM &&
            CNAM == other.CNAM &&
            NAM2 == other.NAM2 &&
            NAM3 == other.NAM3 &&
            NAM4 == other.NAM4 &&
            DNAM == other.DNAM &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MNAM == other.MNAM &&
            ONAM == other.ONAM &&
            INAM == other.INAM &&
            DATA == other.DATA &&
            NAM0 == other.NAM0 &&
            NAM9 == other.NAM9 &&
            ZNAM == other.ZNAM &&
            NNAM.equalsi(other.NNAM) &&
            XNAM.equalsi(other.XNAM) &&
            IMPS == other.IMPS &&
            IMPF == other.IMPF &&
            OFST == other.OFST);
    }

bool WRLDRecord::operator !=(const WRLDRecord &other) const
    {
    return !(*this == other);
    }
}