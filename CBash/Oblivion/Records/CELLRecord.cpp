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
#include "CELLRecord.h"

namespace Ob
{
CELLRecord::CELLXCLL::CELLXCLL():
    fogNear(0),
    fogFar(0),
    directionalXY(0),
    directionalZ(0),
    directionalFade(1.0f),
    fogClip(0)
    {
    //
    }

CELLRecord::CELLXCLL::~CELLXCLL()
    {
    //
    }

bool CELLRecord::CELLXCLL::operator ==(const CELLXCLL &other) const
    {
    return (ambient == other.ambient &&
            directional == other.directional &&
            fog == other.fog &&
            AlmostEqual(fogNear,other.fogNear,2) &&
            AlmostEqual(fogFar,other.fogFar,2) &&
            directionalXY == other.directionalXY &&
            directionalZ == other.directionalZ &&
            AlmostEqual(directionalFade,other.directionalFade,2) &&
            AlmostEqual(fogClip,other.fogClip,2));
    }

bool CELLRecord::CELLXCLL::operator !=(const CELLXCLL &other) const
    {
    return !(*this == other);
    }

CELLRecord::CELLXCLC::CELLXCLC():
    posX(0),
    posY(0)
    {
    //
    }

CELLRecord::CELLXCLC::~CELLXCLC()
    {
    //
    }

bool CELLRecord::CELLXCLC::operator ==(const CELLXCLC &other) const
    {
    return (posX == other.posX &&
            posY == other.posY);
    }

bool CELLRecord::CELLXCLC::operator !=(const CELLXCLC &other) const
    {
    return !(*this == other);
    }

CELLRecord::CELLRecord(unsigned char *_recData):
    Record(_recData),
    PGRD(NULL),
    LAND(NULL)
    {
    //
    }

CELLRecord::CELLRecord(CELLRecord *srcRecord):
    Record(),
    PGRD(NULL),
    LAND(NULL)
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
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    XCLL = srcRecord->XCLL;
    XCMT = srcRecord->XCMT;
    Ownership = srcRecord->Ownership;
    XCCM = srcRecord->XCCM;
    XCLW = srcRecord->XCLW;
    XCLR = srcRecord->XCLR;
    XCLC = srcRecord->XCLC;
    XCWT = srcRecord->XCWT;
    return;
    }

CELLRecord::~CELLRecord()
    {
    //
    //ACHRs are owned at the mod level, so must be destroyed there
    //ACREs are owned at the mod level, so must be destroyed there
    //REFRs are owned at the mod level, so must be destroyed there
    //PGRD is owned at the mod level, so must be destroyed there
    //LAND is owned at the mod level, so must be destroyed there
    //Parent is a shared pointer that's deleted when the WRLD group is deleted
    }

bool CELLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(Ownership.IsLoaded())
        {
        if(Ownership->XOWN.IsLoaded())
            op.Accept(Ownership->XOWN.value);
        if(Ownership->XGLB.IsLoaded())
            op.Accept(Ownership->XGLB.value);
        }
    if(XCCM.IsLoaded())
        op.Accept(XCCM.value);
    for(UINT32 ListIndex = 0; ListIndex < XCLR.value.size(); ListIndex++)
        op.Accept(XCLR.value[ListIndex]);

    if(XCWT.IsLoaded())
        op.Accept(XCWT.value);

    return op.Stop();
    }

bool CELLRecord::IsInterior()
    {
    return (DATA.value & fIsInterior) != 0;
    }

void CELLRecord::IsInterior(bool value)
    {
    DATA.value = value ? (DATA.value | fIsInterior) : (DATA.value & ~fIsInterior);
    }

bool CELLRecord::IsHasWater()
    {
    return (DATA.value & fHasWater) != 0;
    }

void CELLRecord::IsHasWater(bool value)
    {
    DATA.value = value ? (DATA.value | fHasWater) : (DATA.value & ~fHasWater);
    }

bool CELLRecord::IsInvertFastTravel()
    {
    return (DATA.value & fInvertFastTravel) != 0;
    }

void CELLRecord::IsInvertFastTravel(bool value)
    {
    DATA.value = value ? (DATA.value | fInvertFastTravel) : (DATA.value & ~fInvertFastTravel);
    }

bool CELLRecord::IsForceHideLand()
    {
    return (DATA.value & fForceHideLand) != 0;
    }

void CELLRecord::IsForceHideLand(bool value)
    {
    DATA.value = value ? (DATA.value | fForceHideLand) : (DATA.value & ~fForceHideLand);
    }

bool CELLRecord::IsPublicPlace()
    {
    return (DATA.value & fPublicPlace) != 0;
    }

void CELLRecord::IsPublicPlace(bool value)
    {
    DATA.value = value ? (DATA.value | fPublicPlace) : (DATA.value & ~fPublicPlace);
    }

bool CELLRecord::IsHandChanged()
    {
    return (DATA.value & fHandChanged) != 0;
    }

void CELLRecord::IsHandChanged(bool value)
    {
    DATA.value = value ? (DATA.value | fHandChanged) : (DATA.value & ~fHandChanged);
    }

bool CELLRecord::IsBehaveLikeExterior()
    {
    return (DATA.value & fBehaveLikeExterior) != 0;
    }

void CELLRecord::IsBehaveLikeExterior(bool value)
    {
    DATA.value = value ? (DATA.value | fBehaveLikeExterior) : (DATA.value & ~fBehaveLikeExterior);
    }

bool CELLRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void CELLRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value = Mask;
    }

bool CELLRecord::IsDefaultMusic()
    {
    XCMT.Load();
    return XCMT.value == eDefault;
    }

void CELLRecord::IsDefaultMusic(bool value)
    {
    XCMT.Load();
    if(value)
        XCMT.value = eDefault;
    else if(IsDefaultMusic())
        XCMT.value = ePublic;
    }

bool CELLRecord::IsPublicMusic()
    {
    XCMT.Load();
    return XCMT.value == ePublic;
    }

void CELLRecord::IsPublicMusic(bool value)
    {
    XCMT.Load();
    if(value)
        XCMT.value = ePublic;
    else if(IsPublicMusic())
        XCMT.value = eDefault;
    }

bool CELLRecord::IsDungeonMusic()
    {
    XCMT.Load();
    return XCMT.value == eDungeon;
    }

void CELLRecord::IsDungeonMusic(bool value)
    {
    XCMT.Load();
    if(value)
        XCMT.value = eDungeon;
    else if(IsDungeonMusic())
        XCMT.value = eDefault;
    }

bool CELLRecord::IsMusicType(UINT8 Type)
    {
    XCMT.Load();
    return XCMT.value == Type;
    }

void CELLRecord::SetMusicType(UINT8 Type)
    {
    XCMT.Load();
    XCMT.value = Type;
    }

UINT32 CELLRecord::GetType()
    {
    return REV32(CELL);
    }

STRING CELLRecord::GetStrType()
    {
    return "CELL";
    }

SINT32 CELLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(XCLL):
                XCLL.Read(buffer, subSize);
                break;
            case REV32(XCMT):
                XCMT.Read(buffer, subSize);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize);
                break;
            case REV32(XGLB):
                Ownership.Load();
                Ownership->XGLB.Read(buffer, subSize);
                break;
            case REV32(XCCM):
                XCCM.Read(buffer, subSize);
                break;
            case REV32(XCLW):
                XCLW.Read(buffer, subSize);
                break;
            case REV32(XCLR):
                XCLR.Read(buffer, subSize);
                break;
            case REV32(XCLC):
                XCLC.Read(buffer, subSize);
                break;
            case REV32(XCWT):
                XCWT.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CELL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 CELLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    //DATA.Unload(); //need to keep IsInterior around
    XCLL.Unload();
    XCMT.Unload();
    Ownership.Unload();
    XCCM.Unload();
    XCLW.Unload();
    XCLR.Unload();
    XCLC.Unload();
    XCWT.Unload();
    return 1;
    }

SINT32 CELLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);

    WRITE(FULL);
    WRITE(DATA);
    WRITE(XCLL);
    WRITE(XCMT);
    Ownership.Write(writer);

    WRITE(XCCM);
    WRITE(XCLW);
    WRITE(XCLR);
    if(!IsInterior())
        WRITE(XCLC);
    WRITE(XCWT);
    return -1;
    }

bool CELLRecord::operator ==(const CELLRecord &other) const
    {
    return (DATA == other.DATA &&
            XCMT == other.XCMT &&
            XCCM == other.XCCM &&
            XCWT == other.XCWT &&
            XCLL == other.XCLL &&
            XCLC == other.XCLC &&
            XCLW == other.XCLW &&
            Ownership == other.Ownership &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            XCLR == other.XCLR);
    }

bool CELLRecord::operator !=(const CELLRecord &other) const
    {
    return !(*this == other);
    }

bool CELLRecord::equals(Record *other)
    {
    return *this == *(CELLRecord *)other;
    }

bool CELLRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //              all child records have been visited

    CELLRecord *master_cell = (CELLRecord *)master;
    //Check to make sure the CELLs are attached at the same spot
    if(!IsInterior())
        if(GetParentRecord()->formID != master_cell->GetParentRecord()->formID)
            return false;

    if(ACHR.size() > master_cell->ACHR.size())
        return false;
    if(ACRE.size() > master_cell->ACRE.size())
        return false;
    if(REFR.size() > master_cell->REFR.size())
        return false;

    if(PGRD != NULL)
        {
        if(master_cell->PGRD != NULL)
            {
            if(identical_records.count(PGRD) == 0)
                return false;
            }
        else
            return false;
        }

    if(LAND != NULL)
        {
        if(master_cell->LAND != NULL)
            {
            if(identical_records.count(LAND) == 0)
                return false;
            }
        else
            return false;
        }

    for(UINT32 ListIndex = 0; ListIndex < ACHR.size(); ++ListIndex)
        if(identical_records.count(ACHR[ListIndex]) == 0)
                return false;

    for(UINT32 ListIndex = 0; ListIndex < ACRE.size(); ++ListIndex)
        if(identical_records.count(ACRE[ListIndex]) == 0)
                return false;

    for(UINT32 ListIndex = 0; ListIndex < REFR.size(); ++ListIndex)
        if(identical_records.count(REFR[ListIndex]) == 0)
                return false;

    //The cell and all its contents are dupes, so remove the child records from identical_records
    // This prevents Bash from trying to double delete records (first the cell, and later a child that was in the cell)
    identical_records.erase(PGRD);
    identical_records.erase(LAND);

    for(UINT32 ListIndex = 0; ListIndex < ACHR.size(); ++ListIndex)
        identical_records.erase(ACHR[ListIndex]);

    for(UINT32 ListIndex = 0; ListIndex < ACRE.size(); ++ListIndex)
        identical_records.erase(ACRE[ListIndex]);

    for(UINT32 ListIndex = 0; ListIndex < REFR.size(); ++ListIndex)
        identical_records.erase(REFR[ListIndex]);

    return true;
    }
}