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
#include "NAVIRecord.h"

namespace FNV
{
NAVIRecord::NAVIRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

NAVIRecord::NAVIRecord(NAVIRecord *srcRecord):
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
    NVER = srcRecord->NVER;
    NVMI = srcRecord->NVMI;
    NVCI = srcRecord->NVCI;
    return;
    }

NAVIRecord::~NAVIRecord()
    {
    //
    }

bool NAVIRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(NVMI.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(NVMI->value);
    //if(NVCI.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(NVCI->value);

    return op.Stop();
    }

UINT32 NAVIRecord::GetType()
    {
    return 'IVAN';
    }

STRING NAVIRecord::GetStrType()
    {
    return "NAVI";
    }

SINT32 NAVIRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'REVN':
                NVER.Read(buffer, subSize, curPos);
                break;
            case 'IMVN':
                NVMI.Read(buffer, subSize, curPos);
                break;
            case 'ICVN':
                NVCI.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  NAVI: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 NAVIRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NVER.Unload();
    NVMI.Unload();
    NVCI.Unload();
    return 1;
    }

SINT32 NAVIRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NVER);
    WRITE(NVMI);
    WRITE(NVCI);

    return -1;
    }

bool NAVIRecord::operator ==(const NAVIRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            NVMI == other.NVMI &&
            NVCI == other.NVCI);
    }

bool NAVIRecord::operator !=(const NAVIRecord &other) const
    {
    return !(*this == other);
    }
}