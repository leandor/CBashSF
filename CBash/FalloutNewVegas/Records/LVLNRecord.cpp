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
#include "LVLNRecord.h"

namespace FNV
{
LVLNRecord::LVLNRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

LVLNRecord::LVLNRecord(LVLNRecord *srcRecord):
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
        return;

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    LVLD = srcRecord->LVLD;
    LVLF = srcRecord->LVLF;
    Entries = srcRecord->Entries;
    MODL = srcRecord->MODL;
    return;
    }

LVLNRecord::~LVLNRecord()
    {
    //
    }

bool LVLNRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < Entries.value.size(); x++)
        {
        op.Accept(Entries.value[x]->LVLO.value.listId);
        if(Entries.value[x]->IsGlobal())
            op.Accept(Entries.value[x]->COED->globalOrRank);
        }
    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }

    return op.Stop();
    }

bool LVLNRecord::IsCalcFromAllLevels()
    {
    return (LVLF.value & fCalcFromAllLevels) != 0;
    }

void LVLNRecord::IsCalcFromAllLevels(bool value)
    {
    LVLF.value = value ? (LVLF.value | fCalcFromAllLevels) : (LVLF.value & ~fCalcFromAllLevels);
    }

bool LVLNRecord::IsCalcForEachItem()
    {
    return (LVLF.value & fCalcForEachItem) != 0;
    }

void LVLNRecord::IsCalcForEachItem(bool value)
    {
    LVLF.value = value ? (LVLF.value | fCalcForEachItem) : (LVLF.value & ~fCalcForEachItem);
    }

bool LVLNRecord::IsUseAll()
    {
    return (LVLF.value & fUseAll) != 0;
    }

void LVLNRecord::IsUseAll(bool value)
    {
    LVLF.value = value ? (LVLF.value | fUseAll) : (LVLF.value & ~fUseAll);
    }

bool LVLNRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((LVLF.value & Mask) == Mask) : ((LVLF.value & Mask) != 0);
    }

void LVLNRecord::SetFlagMask(UINT8 Mask)
    {
    LVLF.value = Mask;
    }

UINT32 LVLNRecord::GetType()
    {
    return REV32(LVLN);
    }

STRING LVLNRecord::GetStrType()
    {
    return "LVLN";
    }

SINT32 LVLNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(LVLD):
                LVLD.Read(buffer, subSize);
                break;
            case REV32(LVLF):
                LVLF.Read(buffer, subSize);
                break;
            case REV32(LVLO):
                Entries.value.push_back(new FNVLVLO);
                Entries.value.back()->LVLO.Read(buffer, subSize);
                break;
            case REV32(COED):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new FNVLVLO);
                Entries.value.back()->COED.Read(buffer, subSize);
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
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LVLN: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 LVLNRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    LVLD.Unload();
    LVLF.Unload();
    Entries.Unload();
    MODL.Unload();
    return 1;
    }

SINT32 LVLNRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(LVLD);
    WRITE(LVLF);
    Entries.Write(writer);
    MODL.Write(writer);
    return -1;
    }

bool LVLNRecord::operator ==(const LVLNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            LVLD == other.LVLD &&
            LVLF == other.LVLF &&
            Entries == other.Entries &&
            MODL == other.MODL);
    }

bool LVLNRecord::operator !=(const LVLNRecord &other) const
    {
    return !(*this == other);
    }

bool LVLNRecord::equals(Record *other)
    {
    return *this == *(LVLNRecord *)other;
    }
}