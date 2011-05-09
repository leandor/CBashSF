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
#include "LVLIRecord.h"

namespace FNV
{
LVLIRecord::LVLIRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

LVLIRecord::LVLIRecord(LVLIRecord *srcRecord):
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
    OBND = srcRecord->OBND;
    LVLD = srcRecord->LVLD;
    LVLF = srcRecord->LVLF;
    Entries = srcRecord->Entries;
    MODL = srcRecord->MODL;
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

bool LVLIRecord::IsCalcFromAllLevels()
    {
    return (LVLF.value & fCalcFromAllLevels) != 0;
    }

void LVLIRecord::IsCalcFromAllLevels(bool value)
    {
    LVLF.value = value ? (LVLF.value | fCalcFromAllLevels) : (LVLF.value & ~fCalcFromAllLevels);
    }

bool LVLIRecord::IsCalcForEachItem()
    {
    return (LVLF.value & fCalcForEachItem) != 0;
    }

void LVLIRecord::IsCalcForEachItem(bool value)
    {
    LVLF.value = value ? (LVLF.value | fCalcForEachItem) : (LVLF.value & ~fCalcForEachItem);
    }

bool LVLIRecord::IsUseAll()
    {
    return (LVLF.value & fUseAll) != 0;
    }

void LVLIRecord::IsUseAll(bool value)
    {
    LVLF.value = value ? (LVLF.value | fUseAll) : (LVLF.value & ~fUseAll);
    }

bool LVLIRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((LVLF.value & Mask) == Mask) : ((LVLF.value & Mask) != 0);
    }

void LVLIRecord::SetFlagMask(UINT8 Mask)
    {
    LVLF.value = Mask;
    }

UINT32 LVLIRecord::GetType()
    {
    return 'CLVL';
    }

STRING LVLIRecord::GetStrType()
    {
    return "LVLI";
    }

SINT32 LVLIRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case 'XXXX':
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
            case 'DIDE':
                EDID.Read(buffer, subSize, curPos);
                break;
            case 'DNBO':
                OBND.Read(buffer, subSize, curPos);
                break;
            case 'DLVL':
                LVLD.Read(buffer, subSize, curPos);
                break;
            case 'FLVL':
                LVLF.Read(buffer, subSize, curPos);
                break;
            case 'OLVL':
                Entries.value.push_back(new FNVLVLO);
                Entries.value.back()->LVLO.Read(buffer, subSize, curPos);
                break;
            case 'DEOC':
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new FNVLVLO);
                Entries.value.back()->COED.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case 'BDOM':
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case 'TDOM':
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case 'SDOM':
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LVLI: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    OBND.Unload();
    LVLD.Unload();
    LVLF.Unload();
    Entries.Unload();
    MODL.Unload();
    return 1;
    }

SINT32 LVLIRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(LVLD);
    WRITE(LVLF);
    Entries.Write(writer);
    MODL.Write(writer);
    return -1;
    }

bool LVLIRecord::operator ==(const LVLIRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            LVLD == other.LVLD &&
            LVLF == other.LVLF &&
            Entries == other.Entries &&
            MODL == other.MODL);
    }

bool LVLIRecord::operator !=(const LVLIRecord &other) const
    {
    return !(*this == other);
    }
}