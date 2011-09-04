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
#include "SKILRecord.h"

namespace Ob
{
SKILRecord::SKILDATA::SKILDATA():
    action(26),
    attribute(0),
    specialization(0),
    use0(1.0f),
    use1(1.0f)
    {
    //
    }

SKILRecord::SKILDATA::~SKILDATA()
    {
    //
    }

bool SKILRecord::SKILDATA::operator ==(const SKILDATA &other) const
    {
    return (action == other.action &&
            attribute == other.attribute &&
            specialization == other.specialization &&
            AlmostEqual(use0,other.use0,2) &&
            AlmostEqual(use1,other.use1,2));
    }

bool SKILRecord::SKILDATA::operator !=(const SKILDATA &other) const
    {
    return !(*this == other);
    }

SKILRecord::SKILRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SKILRecord::SKILRecord(SKILRecord *srcRecord):
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

    INDX = srcRecord->INDX;
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    DATA = srcRecord->DATA;
    ANAM = srcRecord->ANAM;
    JNAM = srcRecord->JNAM;
    ENAM = srcRecord->ENAM;
    MNAM = srcRecord->MNAM;
    }

SKILRecord::~SKILRecord()
    {
    //
    }

UINT32 SKILRecord::GetType()
    {
    return REV32(SKIL);
    }

STRING SKILRecord::GetStrType()
    {
    return "SKIL";
    }

SINT32 SKILRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(INDX):
                INDX.Read(buffer, subSize);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(JNAM):
                JNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SKIL: Unknown subType = %04X\n", subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 SKILRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    INDX.Unload();
    DESC.Unload();
    ICON.Unload();
    DATA.Unload();
    ANAM.Unload();
    JNAM.Unload();
    ENAM.Unload();
    MNAM.Unload();
    return 1;
    }

SINT32 SKILRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(INDX);
    WRITE(DESC);
    WRITE(ICON);
    WRITE(DATA);
    WRITE(ANAM);
    WRITE(JNAM);
    WRITE(ENAM);
    WRITE(MNAM);
    return -1;
    }

bool SKILRecord::operator ==(const SKILRecord &other) const
    {
    return (INDX == other.INDX &&
            DATA == other.DATA &&
            DESC.equals(other.DESC) &&
            ANAM.equals(other.ANAM) &&
            JNAM.equals(other.JNAM) &&
            ENAM.equals(other.ENAM) &&
            MNAM.equals(other.MNAM) &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON));
    }

bool SKILRecord::operator !=(const SKILRecord &other) const
    {
    return !(*this == other);
    }

bool SKILRecord::equals(Record *other)
    {
    return *this == *(SKILRecord *)other;
    }
}