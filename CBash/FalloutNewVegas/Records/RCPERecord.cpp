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
#include "RCPERecord.h"

namespace FNV
{
RCPERecord::RCPERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

RCPERecord::RCPERecord(RCPERecord *srcRecord):
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
    CTDA = srcRecord->CTDA;
    DATA = srcRecord->DATA;
    RCIL = srcRecord->RCIL;
    RCQY = srcRecord->RCQY;
    RCOD = srcRecord->RCOD;
    return;
    }

RCPERecord::~RCPERecord()
    {
    //
    }

bool RCPERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);
    if(RCIL.IsLoaded())
        op.Accept(RCIL->value);
    if(RCOD.IsLoaded())
        op.Accept(RCOD->value);

    return op.Stop();
    }

UINT32 RCPERecord::GetType()
    {
    return REV32(RCPE);
    }

STRING RCPERecord::GetStrType()
    {
    return "RCPE";
    }

SINT32 RCPERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(RCIL):
                RCIL.Read(buffer, subSize);
                break;
            case REV32(RCQY):
                RCQY.Read(buffer, subSize);
                break;
            case REV32(RCOD):
                RCOD.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  RCPE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 RCPERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    CTDA.Unload();
    DATA.Unload();
    RCIL.Unload();
    RCQY.Unload();
    RCOD.Unload();
    return 1;
    }

SINT32 RCPERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(CTDA);
    WRITE(DATA);
    WRITE(RCIL);
    WRITE(RCQY);
    WRITE(RCOD);

    return -1;
    }

bool RCPERecord::operator ==(const RCPERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            CTDA == other.CTDA &&
            DATA == other.DATA &&
            RCIL == other.RCIL &&
            RCQY == other.RCQY &&
            RCOD == other.RCOD);
    }

bool RCPERecord::operator !=(const RCPERecord &other) const
    {
    return !(*this == other);
    }

bool RCPERecord::equals(const Record *other) const
    {
    return *this == *(RCPERecord *)other;
    }
}