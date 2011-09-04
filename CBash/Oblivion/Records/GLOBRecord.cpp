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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#include "..\..\Common.h"
#include "GLOBRecord.h"

namespace Ob
{
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
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
    return REV32(GLOB);
    }

STRING GLOBRecord::GetStrType()
    {
    return "GLOB";
    }

SINT32 GLOBRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(FLTV):
                FLTV.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  GLOB: Unknown subType = %04X\n", subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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
    WRITE(EDID);

    WRITE(FNAM);

    WRITE(FLTV);

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

bool GLOBRecord::equals(Record *other)
    {
    return *this == *(GLOBRecord *)other;
    }
}