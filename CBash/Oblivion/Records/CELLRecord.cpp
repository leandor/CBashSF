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
#include "CELLRecord.h"
#include <vector>

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
    LAND(NULL),
    Parent(NULL)
    {
    //
    }

CELLRecord::CELLRecord(CELLRecord *srcRecord):
    Record(),
    PGRD(NULL),
    LAND(NULL),
    Parent(NULL)
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
    DATA = srcRecord->DATA;
    XCLL = srcRecord->XCLL;
    XCMT = srcRecord->XCMT;
    if(srcRecord->Ownership.IsLoaded())
        {
        Ownership.Load();
        Ownership->XOWN = srcRecord->Ownership->XOWN;
        Ownership->XRNK = srcRecord->Ownership->XRNK;
        Ownership->XGLB = srcRecord->Ownership->XGLB;
        }
    XCCM = srcRecord->XCCM;
    XCLW = srcRecord->XCLW;
    XCLR = srcRecord->XCLR;
    XCLC = srcRecord->XCLC;
    XCWT = srcRecord->XCWT;
    return;
    }

CELLRecord::~CELLRecord()
    {
    for(UINT32 x = 0; x < ACHR.size(); ++x)
        delete ACHR[x];
    for(UINT32 x = 0; x < ACRE.size(); ++x)
        delete ACRE[x];
    for(UINT32 x = 0; x < REFR.size(); ++x)
        delete REFR[x];
    delete PGRD;
    delete LAND;
    //Parent is a shared pointer that's deleted when the WRLD group is deleted
    }

bool CELLRecord::HasSubRecords()
    {
    return true;
    }

bool CELLRecord::VisitSubRecords(const UINT32 &RecordType, RecordOp &op)
    {
    bool stop;

    if(RecordType == NULL || RecordType == REV32(ACHR))
        for(UINT32 x = 0; x < ACHR.size();++x)
            {
            stop = op.Accept(ACHR[x]);
            if(ACHR[x] == NULL)
                {
                ACHR.erase(ACHR.begin() + x);
                --x;
                }
            if(stop)
                return stop;
            }

    if(RecordType == NULL || RecordType == REV32(ACRE))
        for(UINT32 x = 0; x < ACRE.size();++x)
            {
            stop = op.Accept(ACRE[x]);
            if(ACRE[x] == NULL)
                {
                ACRE.erase(ACRE.begin() + x);
                --x;
                }
            if(stop)
                return stop;
            }

    if(RecordType == NULL || RecordType == REV32(REFR))
        for(UINT32 x = 0; x < REFR.size();++x)
            {
            stop = op.Accept(REFR[x]);
            if(REFR[x] == NULL)
                {
                REFR.erase(REFR.begin() + x);
                --x;
                }
            if(stop)
                return stop;
            }

    if(RecordType == NULL || RecordType == REV32(PGRD))
        {
        if(PGRD != NULL)
            {
            if(op.Accept(PGRD))
                return true;
            }
        }

    if(RecordType == NULL || RecordType == REV32(LAND))
        {
        if(LAND != NULL)
            {
            if(op.Accept(LAND))
                return true;
            }
        }

    return op.Stop();
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
    for(UINT32 x = 0; x < XCLR.size(); x++)
        op.Accept(XCLR[x]);

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

UINT32 CELLRecord::GetParentType()
    {
    if(Parent != NULL)
        return Parent->GetType();
    return 0;
    }

SINT32 CELLRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(XCLL):
                XCLL.Read(buffer, subSize, curPos);
                break;
            case REV32(XCMT):
                XCMT.Read(buffer, subSize, curPos);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize, curPos);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize, curPos);
                break;
            case REV32(XGLB):
                Ownership.Load();
                Ownership->XGLB.Read(buffer, subSize, curPos);
                break;
            case REV32(XCCM):
                XCCM.Read(buffer, subSize, curPos);
                break;
            case REV32(XCLW):
                XCLW.Read(buffer, subSize, curPos);
                break;
            case REV32(XCLR):
                if(subSize % sizeof(UINT32) == 0)
                    {
                    if(subSize == 0)
                        break;
                    XCLR.resize(subSize / sizeof(UINT32));
                    _readBuffer(&XCLR[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized XCLR size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case REV32(XCLC):
                XCLC.Read(buffer, subSize, curPos);
                break;
            case REV32(XCWT):
                XCWT.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CELL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    DATA.Unload();
    XCLL.Unload();
    XCMT.Unload();
    Ownership.Unload();
    XCCM.Unload();
    XCLW.Unload();
    XCLR.clear();
    XCLC.Unload();
    XCWT.Unload();
    return 1;
    }

SINT32 CELLRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        writer.record_write_subrecord(REV32(FULL), FULL.value, FULL.GetSize());
    if(DATA.IsLoaded())
        writer.record_write_subrecord(REV32(DATA), &DATA.value, DATA.GetSize());
    if(XCLL.IsLoaded())
        writer.record_write_subrecord(REV32(XCLL), XCLL.value, XCLL.GetSize());
    if(XCMT.IsLoaded())
        writer.record_write_subrecord(REV32(XCMT), &XCMT.value, XCMT.GetSize());

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        writer.record_write_subrecord(REV32(XOWN), &Ownership->XOWN.value, Ownership->XOWN.GetSize());
        if(Ownership->XRNK.IsLoaded())
            writer.record_write_subrecord(REV32(XRNK), Ownership->XRNK.value, Ownership->XRNK.GetSize());
        if(Ownership->XGLB.IsLoaded())
            writer.record_write_subrecord(REV32(XGLB), &Ownership->XGLB.value, Ownership->XGLB.GetSize());
        }

    if(XCCM.IsLoaded())
        writer.record_write_subrecord(REV32(XCCM), &XCCM.value, XCCM.GetSize());
    if(XCLW.IsLoaded())
        writer.record_write_subrecord(REV32(XCLW), &XCLW.value, XCLW.GetSize());

    if(XCLR.size())
        writer.record_write_subrecord(REV32(XCLR), &XCLR[0], (UINT32)XCLR.size() * sizeof(UINT32));
    //else
    //    writer.record_write_subheader(REV32(XCLR), 0);

    if(XCLC.IsLoaded() && !IsInterior())
        writer.record_write_subrecord(REV32(XCLC), XCLC.value, XCLC.GetSize());
    if(XCWT.IsLoaded())
        writer.record_write_subrecord(REV32(XCWT), &XCWT.value, XCWT.GetSize());
    return -1;
    }

bool CELLRecord::operator ==(const CELLRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        FULL.equals(other.FULL) &&
        DATA == other.DATA &&
        XCLL == other.XCLL &&
        XCMT == other.XCMT &&
        Ownership == other.Ownership &&
        XCCM == other.XCCM &&
        XCLW == other.XCLW &&
        XCLC == other.XCLC &&
        XCWT == other.XCWT &&
        XCLR.size() == other.XCLR.size())
        {
        //Not sure if record order matters on regions, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < XCLR.size(); ++x)
            if(XCLR[x] != other.XCLR[x])
                return false;
        return true;
        }

    return false;
    }

bool CELLRecord::operator !=(const CELLRecord &other) const
    {
    return !(*this == other);
    }