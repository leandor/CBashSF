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
#include "WRLDRecord.h"
#include <vector>

WRLDRecord::WRLDRecord(unsigned char *_recData):
    Record(_recData),
    ROAD(NULL),
    CELL(NULL)
    {
    //
    }

WRLDRecord::WRLDRecord(WRLDRecord *srcRecord):
    Record(),
    ROAD(NULL),
    CELL(NULL)
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
    FULL = srcRecord->FULL;
    WNAM = srcRecord->WNAM;
    CNAM = srcRecord->CNAM;
    NAM2 = srcRecord->NAM2;
    ICON = srcRecord->ICON;
    MNAM = srcRecord->MNAM;
    DATA = srcRecord->DATA;
    NAM0 = srcRecord->NAM0;
    NAM9 = srcRecord->NAM9;
    SNAM = srcRecord->SNAM;
    OFST = srcRecord->OFST;
    }

WRLDRecord::~WRLDRecord()
    {
    delete ROAD;
    delete CELL;
    for(UINT32 x = 0; x < CELLS.size(); ++x)
        delete CELLS[x];
    }

bool WRLDRecord::HasSubRecords()
    {
    return true;
    }

bool WRLDRecord::VisitSubRecords(const UINT32 &RecordType, RecordOp &op)
    {
    bool stop;

    if(RecordType == NULL || RecordType == REV32(ROAD))
        {
        if(ROAD != NULL)
            {
            if(op.Accept(ROAD))
                return true;
            }
        }

    if(RecordType == NULL || RecordType != REV32(CELL) ||
        RecordType != REV32(PGRD) || RecordType != REV32(LAND) ||
        RecordType != REV32(REFR) || RecordType != REV32(ACHR) ||
        RecordType != REV32(ACRE))
        {
        if(CELL != NULL)
            {
            if(op.Accept(CELL))
                return true;
            }

        for(UINT32 x = 0; x < CELLS.size();++x)
            {
            stop = op.Accept(CELLS[x]);
            if(CELLS[x] == NULL)
                {
                CELLS.erase(CELLS.begin() + x);
                --x;
                }
            if(stop)
                return stop;
            }
        }

    return op.Stop();
    }

bool WRLDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);
    if(NAM2.IsLoaded())
        op.Accept(NAM2.value);

    return op.Stop();
    }

bool WRLDRecord::IsSmallWorld()
    {
    return (DATA.value & fSmallWorld) != 0;
    }

void WRLDRecord::IsSmallWorld(bool value)
    {
    DATA.value = value ? (DATA.value | fSmallWorld) : (DATA.value & ~fSmallWorld);
    }

bool WRLDRecord::IsNoFastTravel()
    {
    return (DATA.value & fNoFastTravel) != 0;
    }

void WRLDRecord::IsNoFastTravel(bool value)
    {
    DATA.value = value ? (DATA.value | fNoFastTravel) : (DATA.value & ~fNoFastTravel);
    }

bool WRLDRecord::IsFastTravel()
    {
    return !IsNoFastTravel();
    }

void WRLDRecord::IsFastTravel(bool value)
    {
    IsNoFastTravel(!value);
    }

bool WRLDRecord::IsOblivionWorldspace()
    {
    return (DATA.value & fOblivionWorldspace) != 0;
    }

void WRLDRecord::IsOblivionWorldspace(bool value)
    {
    DATA.value = value ? (DATA.value | fOblivionWorldspace) : (DATA.value & ~fOblivionWorldspace);
    }

bool WRLDRecord::IsNoLODWater()
    {
    return (DATA.value & fNoLODWater) != 0;
    }

void WRLDRecord::IsNoLODWater(bool value)
    {
    DATA.value = value ? (DATA.value | fNoLODWater) : (DATA.value & ~fNoLODWater);
    }

bool WRLDRecord::IsLODWater()
    {
    return !IsNoLODWater();
    }

void WRLDRecord::IsLODWater(bool value)
    {
    IsNoLODWater(!value);
    }

bool WRLDRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void WRLDRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value = Mask;
    }

bool WRLDRecord::IsDefaultMusic()
    {
    return (SNAM.value == eDefault);
    }

void WRLDRecord::IsDefaultMusic(bool value)
    {
    if(value)
        SNAM.value = eDefault;
    else if(IsDefaultMusic())
        SNAM.value = ePublic;
    }

bool WRLDRecord::IsPublicMusic()
    {
    return (SNAM.value == ePublic);
    }

void WRLDRecord::IsPublicMusic(bool value)
    {
    if(value)
        SNAM.value = ePublic;
    else if(IsPublicMusic())
        SNAM.value = eDefault;
    }

bool WRLDRecord::IsDungeonMusic()
    {
    return (SNAM.value == eDungeon);
    }

void WRLDRecord::IsDungeonMusic(bool value)
    {
    if(value)
        SNAM.value = eDungeon;
    else if(IsDungeonMusic())
        SNAM.value = eDefault;
    }

bool WRLDRecord::IsMusicType(UINT32 Type)
    {
    return (SNAM.value == Type);
    }

void WRLDRecord::SetMusicType(UINT32 Type)
    {
    SNAM.value = Type;
    }

UINT32 WRLDRecord::GetType()
    {
    return REV32(WRLD);
    }

STRING WRLDRecord::GetStrType()
    {
    return "WRLD";
    }

SINT32 WRLDRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, curPos);
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize, curPos);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, curPos);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM9):
                NAM9.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(OFST):
                OFST.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WRLD: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 WRLDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    WNAM.Unload();
    CNAM.Unload();
    NAM2.Unload();
    ICON.Unload();
    MNAM.Unload();
    DATA.Unload();
    NAM0.Unload();
    NAM9.Unload();
    SNAM.Unload();
    OFST.Unload();
    return 1;
    }

SINT32 WRLDRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        writer.record_write_subrecord(REV32(FULL), FULL.value, FULL.GetSize());
    if(WNAM.IsLoaded())
        writer.record_write_subrecord(REV32(WNAM), &WNAM.value, WNAM.GetSize());
    if(CNAM.IsLoaded())
        writer.record_write_subrecord(REV32(CNAM), &CNAM.value, CNAM.GetSize());
    if(NAM2.IsLoaded())
        writer.record_write_subrecord(REV32(NAM2), &NAM2.value, NAM2.GetSize());
    if(ICON.IsLoaded())
        writer.record_write_subrecord(REV32(ICON), ICON.value, ICON.GetSize());
    if(MNAM.IsLoaded())
        writer.record_write_subrecord(REV32(MNAM), MNAM.value, MNAM.GetSize());
    if(DATA.IsLoaded())
        writer.record_write_subrecord(REV32(DATA), &DATA.value, DATA.GetSize());
    if(NAM0.IsLoaded())
        writer.record_write_subrecord(REV32(NAM0), &NAM0.value, NAM0.GetSize());
    if(NAM9.IsLoaded())
        writer.record_write_subrecord(REV32(NAM9), &NAM9.value, NAM9.GetSize());
    if(SNAM.IsLoaded())
        writer.record_write_subrecord(REV32(SNAM), &SNAM.value, SNAM.GetSize());
    if(OFST.IsLoaded())
        writer.record_write_subrecord(REV32(OFST), OFST.value, OFST.GetSize());
    return -1;
    }

bool WRLDRecord::operator ==(const WRLDRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            WNAM == other.WNAM &&
            CNAM == other.CNAM &&
            NAM2 == other.NAM2 &&
            ICON.equalsi(other.ICON) &&
            MNAM == other.MNAM &&
            DATA == other.DATA &&
            NAM0 == other.NAM0 &&
            NAM9 == other.NAM9 &&
            SNAM == other.SNAM &&
            OFST == other.OFST);
    }

bool WRLDRecord::operator !=(const WRLDRecord &other) const
    {
    return !(*this == other);
    }