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
#include "APPARecord.h"

namespace Ob
{
APPARecord::APPADATA::APPADATA():
    apparatus(0),
    value(25),
    weight(1.0f),
    quality(10.0f)
    {
    //
    }

APPARecord::APPADATA::~APPADATA()
    {
    //
    }

bool APPARecord::APPADATA::operator ==(const APPADATA &other) const
    {
    return (apparatus == other.apparatus &&
            value == other.value &&
            AlmostEqual(weight,other.weight,2) &&
            AlmostEqual(quality,other.quality,2));
    }

bool APPARecord::APPADATA::operator !=(const APPADATA &other) const
    {
    return !(*this == other);
    }

APPARecord::APPARecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

APPARecord::APPARecord(APPARecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    SCRI = srcRecord->SCRI;
    DATA = srcRecord->DATA;
    return;
    }

APPARecord::~APPARecord()
    {
    //
    }

bool APPARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);

    return op.Stop();
    }

bool APPARecord::IsMortarPestle()
    {
    return (DATA.value.apparatus == eMortarPestle);
    }

void APPARecord::IsMortarPestle(bool value)
    {
    DATA.value.apparatus = value ? eMortarPestle : eAlembic;
    }

bool APPARecord::IsAlembic()
    {
    return (DATA.value.apparatus == eAlembic);
    }

void APPARecord::IsAlembic(bool value)
    {
    DATA.value.apparatus = value ? eAlembic : eMortarPestle;
    }

bool APPARecord::IsCalcinator()
    {
    return (DATA.value.apparatus == eCalcinator);
    }

void APPARecord::IsCalcinator(bool value)
    {
    DATA.value.apparatus = value ? eCalcinator : eMortarPestle;
    }

bool APPARecord::IsRetort()
    {
    return (DATA.value.apparatus == eRetort);
    }

void APPARecord::IsRetort(bool value)
    {
    DATA.value.apparatus = value ? eRetort : eMortarPestle;
    }

bool APPARecord::IsType(UINT8 Type)
    {
    return (DATA.value.apparatus == Type);
    }

void APPARecord::SetType(UINT8 Type)
    {
    DATA.value.apparatus = Type;
    }

UINT32 APPARecord::GetType()
    {
    return REV32(APPA);
    }

STRING APPARecord::GetStrType()
    {
    return "APPA";
    }

SINT32 APPARecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  APPA: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 APPARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    SCRI.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 APPARecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(SCRI);
    WRITE(DATA);
    return -1;
    }

bool APPARecord::operator ==(const APPARecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            SCRI == other.SCRI &&
            DATA == other.DATA);
    }

bool APPARecord::operator !=(const APPARecord &other) const
    {
    return !(*this == other);
    }

bool APPARecord::equals(Record *other)
    {
    return *this == *(APPARecord *)other;
    }
}