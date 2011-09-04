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
#include "DOORRecord.h"

namespace FNV
{
DOORRecord::DOORRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

DOORRecord::DOORRecord(DOORRecord *srcRecord):
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
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    SCRI = srcRecord->SCRI;
    Destructable = srcRecord->Destructable;
    SNAM = srcRecord->SNAM;
    ANAM = srcRecord->ANAM;
    BNAM = srcRecord->BNAM;
    FNAM = srcRecord->FNAM;
    return;
    }

DOORRecord::~DOORRecord()
    {
    //
    }

bool DOORRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(ANAM.IsLoaded())
        op.Accept(ANAM.value);
    if(BNAM.IsLoaded())
        op.Accept(BNAM.value);

    return op.Stop();
    }

bool DOORRecord::IsAutomatic()
    {
    return (FNAM.value & fIsAutomatic) != 0;
    }

void DOORRecord::IsAutomatic(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsAutomatic) : (FNAM.value & ~fIsAutomatic);
    }

bool DOORRecord::IsHidden()
    {
    return (FNAM.value & fIsHidden) != 0;
    }

void DOORRecord::IsHidden(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsHidden) : (FNAM.value & ~fIsHidden);
    }

bool DOORRecord::IsMinimalUse()
    {
    return (FNAM.value & fIsMinimalUse) != 0;
    }

void DOORRecord::IsMinimalUse(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsMinimalUse) : (FNAM.value & ~fIsMinimalUse);
    }

bool DOORRecord::IsSlidingDoor()
    {
    return (FNAM.value & fIsSlidingDoor) != 0;
    }

void DOORRecord::IsSlidingDoor(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsSlidingDoor) : (FNAM.value & ~fIsSlidingDoor);
    }

bool DOORRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((FNAM.value & Mask) == Mask) : ((FNAM.value & Mask) != 0);
    }

void DOORRecord::SetFlagMask(UINT8 Mask)
    {
    FNAM.value = Mask;
    }

UINT32 DOORRecord::GetType()
    {
    return REV32(DOOR);
    }

STRING DOORRecord::GetStrType()
    {
    return "DOOR";
    }

SINT32 DOORRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(OBND):
                OBND.Read(buffer, subSize);
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
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  DOOR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 DOORRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    Destructable.Unload();
    SNAM.Unload();
    ANAM.Unload();
    BNAM.Unload();
    FNAM.Unload();
    return 1;
    }

SINT32 DOORRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(SCRI);
    Destructable.Write(writer);
    WRITE(SNAM);
    WRITE(ANAM);
    WRITE(BNAM);
    WRITE(FNAM);
    return -1;
    }

bool DOORRecord::operator ==(const DOORRecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            SNAM == other.SNAM &&
            ANAM == other.ANAM &&
            BNAM == other.BNAM &&
            FNAM == other.FNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            Destructable == other.Destructable);
    }

bool DOORRecord::operator !=(const DOORRecord &other) const
    {
    return !(*this == other);
    }

bool DOORRecord::equals(Record *other)
    {
    return *this == *(DOORRecord *)other;
    }
}