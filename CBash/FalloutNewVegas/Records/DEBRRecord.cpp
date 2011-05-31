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
#include "DEBRRecord.h"

namespace FNV
{
DEBRRecord::DEBRModel::DEBRModel():
    percentage(0),
    modPath(NULL),
    flags(0)
    {
    //
    }

DEBRRecord::DEBRModel::~DEBRModel()
    {
    delete []modPath;
    }

bool DEBRRecord::DEBRModel::IsHasCollisionData()
    {
    return (flags & fIsHasCollisionData) != 0;
    }

void DEBRRecord::DEBRModel::IsHasCollisionData(bool value)
    {
    flags = value ? (flags | fIsHasCollisionData) : (flags & ~fIsHasCollisionData);
    }

bool DEBRRecord::DEBRModel::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((flags & Mask) == Mask) : ((flags & Mask) != 0);
    }

void DEBRRecord::DEBRModel::SetFlagMask(UINT8 Mask)
    {
    flags = Mask;
    }

bool DEBRRecord::DEBRModel::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(subSize < 3)
        {
        printer("DEBRModel: Warning - Unable to parse chunk (%c%c%c%c). Size "
               "of chunk (%u) is less than the minimum size of the subrecord (%u). "
               "The chunk has been skipped.\n",
               (buffer + curPos)[-6], (buffer + curPos)[-5], (buffer + curPos)[-4], (buffer + curPos)[-3],
               subSize, 3);
        curPos += subSize;
        return false;
        }
    memcpy(&percentage, buffer + curPos, 1);
    curPos += 1;

    UINT32 size = (UINT32)strlen((STRING)(buffer + curPos)) + 1;
    modPath = new char[size];
    strcpy_s(modPath, size, (STRING)(buffer + curPos));
    curPos += size;

    memcpy(&flags, buffer + curPos, 1);
    curPos += 1;

    size += 2;
    if(size != subSize)
        {
        printer("DEBRModel: Warning - Unable to parse chunk (%c%c%c%c). Size "
               "of chunk (%u) is not equal to the parsed size (%u). "
               "The loaded fields are likely corrupt.\n",
               (buffer + curPos)[-6], (buffer + curPos)[-5], (buffer + curPos)[-4], (buffer + curPos)[-3],
               subSize, size);
        }
    return true;
    }

void DEBRRecord::DEBRModel::Write(FileWriter &writer)
    {
    UINT32 size = 3; //null terminator, percentage, and flags
    if(modPath != NULL)
        {
        size += (UINT32)strlen(modPath);
        writer.record_write_subheader(REV32(DATA), size);
        writer.record_write(&percentage, 1);
        writer.record_write(modPath, size - 2);
        writer.record_write(&flags, 1);
        }
    else
        {
        writer.record_write_subheader(REV32(DATA), size);
        writer.record_write(&percentage, 1);
        size = 0;
        writer.record_write(&size, 1); //single null terminator
        writer.record_write(&flags, 1);
        }
    WRITE(MODT);
    }

bool DEBRRecord::DEBRModel::operator ==(const DEBRModel &other) const
    {
    return (flags == other.flags &&
            percentage == other.percentage &&
            (icmps(modPath, other.modPath) == 0) &&
            MODT == other.MODT);
    }

bool DEBRRecord::DEBRModel::operator !=(const DEBRModel &other) const
    {
    return !(*this == other);
    }

DEBRRecord::DEBRModels::DEBRModels()
    {
    //
    }

DEBRRecord::DEBRModels::~DEBRModels()
    {
    Unload();
    }

bool DEBRRecord::DEBRModels::IsLoaded() const
    {
    return (MODS.size() != 0);
    }

void DEBRRecord::DEBRModels::Load()
    {
    //
    }

void DEBRRecord::DEBRModels::Unload()
    {
    for(UINT32 x = 0; x < MODS.size(); ++x)
        delete MODS[x];
    MODS.clear();
    }

void DEBRRecord::DEBRModels::resize(UINT32 newSize)
    {
    //Shrink
    UINT32 size = MODS.size();
    for(; size > newSize;)
        delete MODS[--size];
    MODS.resize(newSize);
    //Grow
    for(; size < newSize;)
        MODS[size++] = new DEBRModel;
    }

void DEBRRecord::DEBRModels::Write(FileWriter &writer)
    {
    for(UINT32 p = 0; p < MODS.size(); p++)
        MODS[p]->Write(writer);
    }

DEBRRecord::DEBRModels& DEBRRecord::DEBRModels::operator = (const DEBRModels &rhs)
    {
    if(this != &rhs)
        {
        Unload();
        if(rhs.MODS.size() != 0)
            {
            MODS.resize(rhs.MODS.size());
            UINT32 pathSize = 0;
            for(UINT32 p = 0; p < rhs.MODS.size(); p++)
                {
                MODS[p] = new DEBRModel;
                MODS[p]->percentage = rhs.MODS[p]->percentage;

                if(rhs.MODS[p]->modPath != NULL)
                    {
                    pathSize = (UINT32)strlen(rhs.MODS[p]->modPath) + 1;
                    MODS[p]->modPath = new char[pathSize];
                    strcpy_s(MODS[p]->modPath, pathSize, rhs.MODS[p]->modPath);
                    }
                MODS[p]->flags = rhs.MODS[p]->flags;
                }
            }
        }
    return *this;
    }

bool DEBRRecord::DEBRModels::operator ==(const DEBRModels &other) const
    {
    if(MODS.size() == other.MODS.size())
        {
        //Not sure if record order matters on debris models, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < MODS.size(); ++x)
            if(*MODS[x] != *other.MODS[x])
                return false;
        return true;
        }
    return false;
    }

bool DEBRRecord::DEBRModels::operator !=(const DEBRModels &other) const
    {
    return !(*this == other);
    }

DEBRRecord::DEBRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

DEBRRecord::DEBRRecord(DEBRRecord *srcRecord):
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

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    Models = srcRecord->Models;
    return;
    }

DEBRRecord::~DEBRRecord()
    {
    //
    }

UINT32 DEBRRecord::GetType()
    {
    return REV32(DEBR);
    }

STRING DEBRRecord::GetStrType()
    {
    return "DEBR";
    }

SINT32 DEBRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case REV32(XXXX):
                curPos += 2;
                _readBuffer(&subSize, buffer, 4, curPos);
                _readBuffer(&subType, buffer, 4, curPos);
                curPos += 2;
                break;
            default:
                subSize = 0;
                _readBuffer(&subSize, buffer, 2, curPos);
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                Models.MODS.push_back(new DEBRModel);
                Models.MODS.back()->Read(buffer, subSize, curPos);
                break;
            case REV32(MODT):
                if(Models.MODS.size() == 0)
                    Models.MODS.push_back(new DEBRModel);
                Models.MODS.back()->MODT.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  DEBR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 DEBRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    Models.Unload();
    return 1;
    }

SINT32 DEBRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    Models.Write(writer);
    return -1;
    }

bool DEBRRecord::operator ==(const DEBRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            Models == other.Models);
    }

bool DEBRRecord::operator !=(const DEBRRecord &other) const
    {
    return !(*this == other);
    }
}