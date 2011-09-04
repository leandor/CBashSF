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
#include "ALOCRecord.h"

namespace FNV
{
ALOCRecord::ALOCRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ALOCRecord::ALOCRecord(ALOCRecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    NAM3 = srcRecord->NAM3;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    NAM6 = srcRecord->NAM6;
    NAM7 = srcRecord->NAM7;
    HNAM = srcRecord->HNAM;
    ZNAM = srcRecord->ZNAM;
    XNAM = srcRecord->XNAM;
    YNAM = srcRecord->YNAM;
    LNAM = srcRecord->LNAM;
    GNAM = srcRecord->GNAM;
    RNAM = srcRecord->RNAM;
    FNAM = srcRecord->FNAM;
    return;
    }

ALOCRecord::~ALOCRecord()
    {
    //
    }

bool ALOCRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(HNAM.IsLoaded())
        op.Accept(HNAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    if(XNAM.IsLoaded())
        op.Accept(XNAM->value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    if(LNAM.IsLoaded())
        op.Accept(LNAM->value);
    if(GNAM.IsLoaded())
        op.Accept(GNAM->value);
    if(RNAM.IsLoaded())
        op.Accept(RNAM->value);

    return op.Stop();
    }

UINT32 ALOCRecord::GetType()
    {
    return REV32(ALOC);
    }

STRING ALOCRecord::GetStrType()
    {
    return "ALOC";
    }

SINT32 ALOCRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                EDID.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize);
                break;
            case REV32(NAM3):
                NAM3.Read(buffer, subSize);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize);
                break;
            case REV32(NAM5):
                NAM5.Read(buffer, subSize);
                break;
            case REV32(NAM6):
                NAM6.Read(buffer, subSize);
                break;
            case REV32(NAM7):
                NAM7.Read(buffer, subSize);
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ALOC: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 ALOCRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    NAM1.Unload();
    NAM2.Unload();
    NAM3.Unload();
    NAM4.Unload();
    NAM5.Unload();
    NAM6.Unload();
    NAM7.Unload();
    HNAM.Unload();
    ZNAM.Unload();
    XNAM.Unload();
    YNAM.Unload();
    LNAM.Unload();
    GNAM.Unload();
    RNAM.Unload();
    FNAM.Unload();
    return 1;
    }

SINT32 ALOCRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(NAM1);
    WRITE(NAM2);
    WRITE(NAM3);
    WRITE(NAM4);
    WRITE(NAM5);
    WRITE(NAM6);
    WRITE(NAM7);
    WRITE(HNAM);
    WRITE(ZNAM);
    WRITE(XNAM);
    WRITE(YNAM);
    WRITE(LNAM);
    WRITE(GNAM);
    WRITE(RNAM);
    WRITE(FNAM);

    return -1;
    }

bool ALOCRecord::operator ==(const ALOCRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NAM1 == other.NAM1 &&
            NAM2 == other.NAM2 &&
            NAM3 == other.NAM3 &&
            NAM4 == other.NAM4 &&
            NAM5 == other.NAM5 &&
            NAM6 == other.NAM6 &&
            NAM7 == other.NAM7 &&
            HNAM == other.HNAM &&
            ZNAM == other.ZNAM &&
            XNAM == other.XNAM &&
            YNAM == other.YNAM &&
            LNAM == other.LNAM &&
            GNAM == other.GNAM &&
            RNAM == other.RNAM &&
            FNAM == other.FNAM);
    }

bool ALOCRecord::operator !=(const ALOCRecord &other) const
    {
    return !(*this == other);
    }

bool ALOCRecord::equals(const Record *other) const
    {
    return *this == *(ALOCRecord *)other;
    }
}