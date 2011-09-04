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
#include "LVLIRecord.h"

namespace Ob
{
LVLIRecord::LVLIRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LVLIRecord::LVLIRecord(LVLIRecord *srcRecord):
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
    LVLD = srcRecord->LVLD;
    LVLF = srcRecord->LVLF;
    Entries = srcRecord->Entries;
    //DATA = srcRecord->DATA;
    return;
    }

LVLIRecord::~LVLIRecord()
    {
    //
    }

bool LVLIRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < Entries.value.size(); ListIndex++)
        op.Accept(Entries.value[ListIndex]->listId);

    return op.Stop();
    }

bool LVLIRecord::IsCalcFromAllLevels()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fCalcFromAllLevels) != 0 : false;
    }

void LVLIRecord::IsCalcFromAllLevels(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fCalcFromAllLevels) : (*LVLF.value & ~fCalcFromAllLevels);
    }

bool LVLIRecord::IsCalcForEachItem()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fCalcForEachItem) != 0 : false;
    }

void LVLIRecord::IsCalcForEachItem(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fCalcForEachItem) : (*LVLF.value & ~fCalcForEachItem);
    }

bool LVLIRecord::IsUseAllSpells()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fUseAllSpells) != 0 : false;
    }

void LVLIRecord::IsUseAllSpells(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fUseAllSpells) : (*LVLF.value & ~fUseAllSpells);
    }

bool LVLIRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    LVLF.Load();
    return Exact ? ((*LVLF.value & Mask) == Mask) : ((*LVLF.value & Mask) != 0);
    }

void LVLIRecord::SetFlagMask(UINT8 Mask)
    {
    LVLF.Load();
    *LVLF.value = Mask;
    }

UINT32 LVLIRecord::GetType()
    {
    return REV32(LVLI);
    }

STRING LVLIRecord::GetStrType()
    {
    return "LVLI";
    }

SINT32 LVLIRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(LVLD):
                LVLD.Read(buffer, subSize);
                if((LVLD.value & fAltCalcFromAllLevels) != 0)
                    {
                    LVLD.value &= ~fAltCalcFromAllLevels;
                    IsCalcFromAllLevels(true);
                    }
                break;
            case REV32(LVLF):
                LVLF.Read(buffer, subSize);
                break;
            case REV32(LVLO):
                Entries.Read(buffer, subSize);
                break;
            case REV32(DATA):
                {
                ReqSubRecord<UINT8> DATA;
                DATA.Read(buffer, subSize);
                if(DATA.value != 0)
                    {
                    LVLF.Load();
                    IsCalcForEachItem(true);
                    }
                }
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LVLI: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 LVLIRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    LVLD.Unload();
    LVLF.Unload();
    Entries.Unload();
    //DATA.Unload();
    return 1;
    }

SINT32 LVLIRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(LVLD);
    WRITE(LVLF);
    WRITEAS(Entries,LVLO);
    //WRITE(DATA);
    return -1;
    }

bool LVLIRecord::operator ==(const LVLIRecord &other) const
    {
    return (LVLD == other.LVLD &&
            LVLF == other.LVLF &&
            EDID.equalsi(other.EDID) &&
            Entries == other.Entries);
    }

bool LVLIRecord::operator !=(const LVLIRecord &other) const
    {
    return !(*this == other);
    }

bool LVLIRecord::equals(Record *other)
    {
    return *this == *(LVLIRecord *)other;
    }
}