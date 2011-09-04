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
#include "IDLERecord.h"

namespace Ob
{
IDLERecord::IDLEDATA::IDLEDATA():
    parent(0),
    prevId(0)
    {
    //
    }

IDLERecord::IDLEDATA::~IDLEDATA()
    {
    //
    }

bool IDLERecord::IDLEDATA::operator ==(const IDLEDATA &other) const
    {
    return (parent == other.parent &&
            prevId == other.prevId);
    }
bool IDLERecord::IDLEDATA::operator !=(const IDLEDATA &other) const
    {
    return !(*this == other);
    }

IDLERecord::IDLERecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

IDLERecord::IDLERecord(IDLERecord *srcRecord):
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
    MODL = srcRecord->MODL;
    CTDA = srcRecord->CTDA;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    return;
    }

IDLERecord::~IDLERecord()
    {
    //
    }

bool IDLERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);

    op.Accept(DATA.value.parent);
    op.Accept(DATA.value.prevId);

    return op.Stop();
    }

bool IDLERecord::IsLowerBody()
    {
    return ((ANAM.value & ~0x80) == eLowerBody);
    }

void IDLERecord::IsLowerBody(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    else if(IsLowerBody())
        ANAM.value = ANAM.value & 0x80 | eLeftArm;
    }

bool IDLERecord::IsLeftArm()
    {
    return ((ANAM.value & ~0x80) == eLeftArm);
    }

void IDLERecord::IsLeftArm(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eLeftArm;
    else if(IsLeftArm())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsLeftHand()
    {
    return ((ANAM.value & ~0x80) == eLeftHand);
    }

void IDLERecord::IsLeftHand(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eLeftHand;
    else if(IsLeftHand())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsRightArm()
    {
    return ((ANAM.value & ~0x80) == eRightArm);
    }

void IDLERecord::IsRightArm(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eRightArm;
    else if(IsRightArm())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsSpecialIdle()
    {
    return ((ANAM.value & ~0x80) == eSpecialIdle);
    }

void IDLERecord::IsSpecialIdle(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eSpecialIdle;
    else if(IsLeftArm())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsWholeBody()
    {
    return ((ANAM.value & ~0x80) == eWholeBody);
    }

void IDLERecord::IsWholeBody(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eWholeBody;
    else if(IsWholeBody())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsUpperBody()
    {
    return ((ANAM.value & ~0x80) == eUpperBody);
    }

void IDLERecord::IsUpperBody(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eUpperBody;
    else if(IsUpperBody())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsType(UINT8 Type)
    {
    return ((ANAM.value & ~0x80) == (Type & ~0x80));
    }

void IDLERecord::SetType(UINT8 Type)
    {
    ANAM.value = ANAM.value & 0x80 | (Type & ~0x80);
    }

bool IDLERecord::IsNotReturnFile()
    {
    return (ANAM.value & fIsNotReturnFile) != 0;
    }

void IDLERecord::IsNotReturnFile(bool value)
    {
    ANAM.value = value ? (ANAM.value | fIsNotReturnFile) : (ANAM.value & ~fIsNotReturnFile);
    }

bool IDLERecord::IsReturnFile()
    {
    return !(IsNotReturnFile());
    }

void IDLERecord::IsReturnFile(bool value)
    {
    IsNotReturnFile(!value);
    }

bool IDLERecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? (((ANAM.value & 0x80) & (Mask & 0x80)) == Mask) : (((ANAM.value & 0x80) & (Mask & 0x80)) != 0);
    }

void IDLERecord::SetFlagMask(UINT8 Mask)
    {
    ANAM.value = ANAM.value & ~0x80 | (Mask & 0x80);
    }

UINT32 IDLERecord::GetType()
    {
    return REV32(IDLE);
    }

STRING IDLERecord::GetStrType()
    {
    return "IDLE";
    }

SINT32 IDLERecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(CTDT):
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  IDLE: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 IDLERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    CTDA.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 IDLERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    MODL.Write(writer);
    CTDA.Write(writer, true);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool IDLERecord::operator ==(const IDLERecord &other) const
    {
    return (ANAM == other.ANAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            CTDA == other.CTDA);
    }

bool IDLERecord::operator !=(const IDLERecord &other) const
    {
    return !(*this == other);
    }

bool IDLERecord::equals(Record *other)
    {
    return *this == *(IDLERecord *)other;
    }
}