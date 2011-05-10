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
#include "LVLCRecord.h"
#include <vector>

LVLCRecord::LVLCRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LVLCRecord::LVLCRecord(LVLCRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    LVLD = srcRecord->LVLD;
    LVLF = srcRecord->LVLF;
    SCRI = srcRecord->SCRI;
    TNAM = srcRecord->TNAM;
    Entries.clear();
    Entries.resize(srcRecord->Entries.size());
    for(UINT32 x = 0; x < srcRecord->Entries.size(); x++)
        {
        Entries[x] = new ReqSubRecord<LVLLVLO>;
        *Entries[x] = *srcRecord->Entries[x];
        }
    return;
    }

LVLCRecord::~LVLCRecord()
    {
    for(UINT32 x = 0; x < Entries.size(); x++)
        delete Entries[x];
    }

bool LVLCRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM.value);
    for(UINT32 x = 0; x < Entries.size(); x++)
        op.Accept(Entries[x]->value.listId);

    return op.Stop();
    }

bool LVLCRecord::IsCalcFromAllLevels()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fCalcFromAllLevels) != 0 : false;
    }

void LVLCRecord::IsCalcFromAllLevels(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fCalcFromAllLevels) : (*LVLF.value & ~fCalcFromAllLevels);
    }

bool LVLCRecord::IsCalcForEachItem()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fCalcForEachItem) != 0 : false;
    }

void LVLCRecord::IsCalcForEachItem(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fCalcForEachItem) : (*LVLF.value & ~fCalcForEachItem);
    }

bool LVLCRecord::IsUseAllSpells()
    {
    return LVLF.IsLoaded() ? (*LVLF.value & fUseAllSpells) != 0 : false;
    }

void LVLCRecord::IsUseAllSpells(bool value)
    {
    LVLF.Load();
    *LVLF.value = value ? (*LVLF.value | fUseAllSpells) : (*LVLF.value & ~fUseAllSpells);
    }

bool LVLCRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    LVLF.Load();
    return Exact ? ((*LVLF.value & Mask) == Mask) : ((*LVLF.value & Mask) != 0);
    }

void LVLCRecord::SetFlagMask(UINT8 Mask)
    {
    if(Mask)
        {
        LVLF.Load();
        *LVLF.value = Mask;
        }
    else
        LVLF.Unload();
    }

UINT32 LVLCRecord::GetType()
    {
    return REV32(LVLC);
    }

STRING LVLCRecord::GetStrType()
    {
    return "LVLC";
    }

SINT32 LVLCRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    ReqSubRecord<LVLLVLO> *newEntry = NULL;
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
            case REV32(LVLD):
                LVLD.Read(buffer, subSize, curPos);
                if((LVLD.value & fAltCalcFromAllLevels) != 0)
                    {
                    LVLD.value &= ~fAltCalcFromAllLevels;
                    IsCalcFromAllLevels(true);
                    }
                break;
            case REV32(LVLF):
                LVLF.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize, curPos);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(LVLO):
                newEntry = new ReqSubRecord<LVLLVLO>;
                newEntry->Read(buffer, subSize, curPos);
                Entries.push_back(newEntry);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LVLC: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 LVLCRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    LVLD.Unload();
    LVLF.Unload();
    SCRI.Unload();
    TNAM.Unload();
    for(UINT32 x = 0; x < Entries.size(); x++)
        delete Entries[x];
    Entries.clear();
    return 1;
    }

SINT32 LVLCRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());
    if(LVLD.IsLoaded())
        writer.record_write_subrecord(REV32(LVLD), &LVLD.value, LVLD.GetSize());
    if(LVLF.IsLoaded())
        writer.record_write_subrecord(REV32(LVLF), LVLF.value, LVLF.GetSize());
    if(SCRI.IsLoaded())
        writer.record_write_subrecord(REV32(SCRI), &SCRI.value, SCRI.GetSize());
    if(TNAM.IsLoaded())
        writer.record_write_subrecord(REV32(TNAM), &TNAM.value, TNAM.GetSize());
    for(UINT32 p = 0; p < Entries.size(); p++)
        if(Entries[p]->IsLoaded())
            writer.record_write_subrecord(REV32(LVLO), &Entries[p]->value, Entries[p]->GetSize());
    return -1;
    }

bool LVLCRecord::operator ==(const LVLCRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        LVLD == other.LVLD &&
        LVLF == other.LVLF &&
        SCRI == other.SCRI &&
        TNAM == other.TNAM &&
        Entries.size() == other.Entries.size())
        {
        //Not sure if record order matters on entries, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < Entries.size(); ++x)
            if(*Entries[x] != *other.Entries[x])
                return false;

        return true;
        }

    return false;
    }

bool LVLCRecord::operator !=(const LVLCRecord &other) const
    {
    return !(*this == other);
    }