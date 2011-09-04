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
#include "FLORRecord.h"

namespace Ob
{
FLORRecord::FLORPFPC::FLORPFPC():
    spring(0),
    summer(0),
    fall(0),
    winter(0)
    {
    //
    }

FLORRecord::FLORPFPC::~FLORPFPC()
    {
    //
    }

bool FLORRecord::FLORPFPC::operator ==(const FLORPFPC &other) const
    {
    return (spring == other.spring &&
            summer == other.summer &&
            fall == other.fall &&
            winter == other.winter);
    }

bool FLORRecord::FLORPFPC::operator !=(const FLORPFPC &other) const
    {
    return !(*this == other);
    }

FLORRecord::FLORRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

FLORRecord::FLORRecord(FLORRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    SCRI = srcRecord->SCRI;
    PFIG = srcRecord->PFIG;
    PFPC = srcRecord->PFPC;
    return;
    }

FLORRecord::~FLORRecord()
    {
    //
    }

bool FLORRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(PFIG.IsLoaded())
        op.Accept(PFIG.value);

    return op.Stop();
    }

UINT32 FLORRecord::GetType()
    {
    return REV32(FLOR);
    }

STRING FLORRecord::GetStrType()
    {
    return "FLOR";
    }

SINT32 FLORRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(PFIG):
                PFIG.Read(buffer, subSize);
                break;
            case REV32(PFPC):
                PFPC.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  FLOR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 FLORRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    PFIG.Unload();
    PFPC.Unload();
    return 1;
    }

SINT32 FLORRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(SCRI);
    WRITE(PFIG);
    WRITE(PFPC);
    return -1;
    }

bool FLORRecord::operator ==(const FLORRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            SCRI == other.SCRI &&
            PFIG == other.PFIG &&
            PFPC == other.PFPC);
    }

bool FLORRecord::operator !=(const FLORRecord &other) const
    {
    return !(*this == other);
    }

bool FLORRecord::equals(Record *other)
    {
    return *this == *(FLORRecord *)other;
    }
}