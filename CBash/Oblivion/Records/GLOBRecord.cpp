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
#include "GLOBRecord.h"

GLOBRecord::GLOBRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

GLOBRecord::GLOBRecord(GLOBRecord *srcRecord):
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
    FNAM = srcRecord->FNAM;
    FLTV = srcRecord->FLTV;
    }

GLOBRecord::~GLOBRecord()
    {
    //
    }

UINT32 GLOBRecord::GetType()
    {
    return 'BOLG';
    }

STRING GLOBRecord::GetStrType()
    {
    return "GLOB";
    }

SINT32 GLOBRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            case 'VTLF':
                FLTV.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  GLOB: Unknown subType = %04X\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 GLOBRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FNAM.Unload();
    FLTV.Unload();
    return 1;
    }

SINT32 GLOBRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord('DIDE', EDID.value, EDID.GetSize());

    if(FNAM.IsLoaded())
        writer.record_write_subrecord('MANF', &FNAM.value, FNAM.GetSize());

    if(FLTV.IsLoaded())
        writer.record_write_subrecord('VTLF', &FLTV.value, FLTV.GetSize());

    return -1;
    }

bool GLOBRecord::operator ==(const GLOBRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FNAM == other.FNAM &&
            FLTV == other.FLTV);
    }

bool GLOBRecord::operator !=(const GLOBRecord &other) const
    {
    return !(*this == other);
    }