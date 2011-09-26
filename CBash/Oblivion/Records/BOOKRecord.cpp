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
#include "BOOKRecord.h"

namespace Ob
{
BOOKRecord::BOOKDATA::BOOKDATA():
    flags(0),
    teaches(-1),
    value(0),
    weight(0.0f)
    {
    //
    }

BOOKRecord::BOOKDATA::~BOOKDATA()
    {
    //
    }

bool BOOKRecord::BOOKDATA::operator ==(const BOOKDATA &other) const
    {
    return (flags == other.flags &&
            teaches == other.teaches &&
            value == other.value &&
            AlmostEqual(weight,other.weight,2));
    }

bool BOOKRecord::BOOKDATA::operator !=(const BOOKDATA &other) const
    {
    return !(*this == other);
    }

BOOKRecord::BOOKRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

BOOKRecord::BOOKRecord(BOOKRecord *srcRecord):
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
    DESC = srcRecord->DESC;
    SCRI = srcRecord->SCRI;
    ENAM = srcRecord->ENAM;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    return;
    }

BOOKRecord::~BOOKRecord()
    {
    //
    }

bool BOOKRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool BOOKRecord::IsScroll()
    {
    return (DATA.value.flags & fIsScroll) != 0;
    }

void BOOKRecord::IsScroll(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsScroll) : (DATA.value.flags & ~fIsScroll);
    }

bool BOOKRecord::IsFixed()
    {
    return (DATA.value.flags & fIsFixed) != 0;
    }

void BOOKRecord::IsFixed(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsFixed) : (DATA.value.flags & ~fIsFixed);
    }

bool BOOKRecord::IsCantBeTaken()
    {
    return (DATA.value.flags & fIsFixed) != 0;
    }

void BOOKRecord::IsCantBeTaken(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsFixed) : (DATA.value.flags & ~fIsFixed);
    }

bool BOOKRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void BOOKRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 BOOKRecord::GetType()
    {
    return REV32(BOOK);
    }

STRING BOOKRecord::GetStrType()
    {
    return "BOOK";
    }

SINT32 BOOKRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  BOOK: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 BOOKRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    DESC.Unload();
    SCRI.Unload();
    ENAM.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 BOOKRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(DESC);
    WRITE(SCRI);
    WRITE(ENAM);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool BOOKRecord::operator ==(const BOOKRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            DESC.equals(other.DESC) &&
            SCRI == other.SCRI &&
            ENAM == other.ENAM &&
            ANAM == other.ANAM &&
            DATA == other.DATA);
    }

bool BOOKRecord::operator !=(const BOOKRecord &other) const
    {
    return !(*this == other);
    }

bool BOOKRecord::equals(Record *other)
    {
    return *this == *(BOOKRecord *)other;
    }
}