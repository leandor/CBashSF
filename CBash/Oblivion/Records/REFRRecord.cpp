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
#include "REFRRecord.h"

REFRRecord::REFRXTEL::REFRXTEL():
    destinationFid(0)
    {
    //
    }

REFRRecord::REFRXTEL::~REFRXTEL()
    {
    //
    }

bool REFRRecord::REFRXTEL::operator ==(const REFRXTEL &other) const
    {
    return (destinationFid == other.destinationFid &&
            destination == other.destination);
    }

bool REFRRecord::REFRXTEL::operator !=(const REFRXTEL &other) const
    {
    return !(*this == other);
    }

REFRRecord::REFRXLOC::REFRXLOC():
    level(0xFF), //Level actually defaults to 0, but this makes it write out if set to 0
    key(0),
    flags(0)
    {
    memset(&unused1, 0x00, 3);
    memset(&unused2, 0x00, 4);
    memset(&unused3, 0x00, 3);
    }

REFRRecord::REFRXLOC::~REFRXLOC()
    {
    //
    }

bool REFRRecord::REFRXLOC::operator ==(const REFRXLOC &other) const
    {
    return (level == other.level &&
            key == other.key &&
            flags == other.flags);
    }

bool REFRRecord::REFRXLOC::operator !=(const REFRXLOC &other) const
    {
    return !(*this == other);
    }

REFRRecord::REFRXSED::REFRXSED():
    seed(0),
    isOffset(true)
    {
    //
    }

REFRRecord::REFRXSED::~REFRXSED()
    {
    //
    }

bool REFRRecord::REFRXSED::operator ==(const REFRXSED &other) const
    {
    if(!isOffset)
        {
        if(!other.isOffset)
            return (seed == other.seed);
        }
    else if(other.isOffset)
        return offset == other.offset;
    return false;
    }

bool REFRRecord::REFRXSED::operator !=(const REFRXSED &other) const
    {
    return !(*this == other);
    }

bool REFRRecord::REFRMAPMARKER::operator ==(const REFRMAPMARKER &other) const
    {
    return (FNAM == other.FNAM &&
            FULL.equals(other.FULL) &&
            TNAM == other.TNAM);
    }

bool REFRRecord::REFRMAPMARKER::operator !=(const REFRMAPMARKER &other) const
    {
    return !(*this == other);
    }

REFRRecord::REFRRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

REFRRecord::REFRRecord(REFRRecord *srcRecord):
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
    NAME = srcRecord->NAME;
    XTEL = srcRecord->XTEL;
    XLOC = srcRecord->XLOC;
    if(srcRecord->Ownership.IsLoaded())
        {
        Ownership.Load();
        Ownership->XOWN = srcRecord->Ownership->XOWN;
        Ownership->XRNK = srcRecord->Ownership->XRNK;
        Ownership->XGLB = srcRecord->Ownership->XGLB;
        }
    XESP = srcRecord->XESP;
    XTRG = srcRecord->XTRG;
    XSED = srcRecord->XSED;
    XLOD = srcRecord->XLOD;
    XCHG = srcRecord->XCHG;
    XHLT = srcRecord->XHLT;
    if(srcRecord->XPCI.IsLoaded())
        {
        XPCI.Load();
        XPCI->XPCI = srcRecord->XPCI->XPCI;
        XPCI->FULL = srcRecord->XPCI->FULL;
        }
    XLCM = srcRecord->XLCM;
    XRTM = srcRecord->XRTM;
    XACT = srcRecord->XACT;
    XCNT = srcRecord->XCNT;
    if(srcRecord->Marker.IsLoaded())
        {
        Marker.Load();
        Marker->FNAM = srcRecord->Marker->FNAM;
        Marker->FULL = srcRecord->Marker->FULL;
        Marker->TNAM = srcRecord->Marker->TNAM;
        }
    if(srcRecord->IsOpenByDefault())//bool ONAM; //Open by Default, empty marker, written whenever fOpenByDefault is true
        IsOpenByDefault(true);
    XSCL = srcRecord->XSCL;
    XSOL = srcRecord->XSOL;
    DATA = srcRecord->DATA;
    }

REFRRecord::~REFRRecord()
    {
    //
    }

bool REFRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(NAME.value);
    if(XTEL.IsLoaded())
        op.Accept(XTEL->destinationFid);
    if(XLOC.IsLoaded())
        op.Accept(XLOC->key);
    if(Ownership.IsLoaded())
        {
        if(Ownership->XOWN.IsLoaded())
            op.Accept(Ownership->XOWN.value);
        if(Ownership->XGLB.IsLoaded())
            op.Accept(Ownership->XGLB.value);
        }
    if(XESP.IsLoaded())
        op.Accept(XESP->parent);
    if(XTRG.IsLoaded())
        op.Accept(XTRG.value);
    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        op.Accept(XPCI->XPCI.value);
    if(XRTM.IsLoaded())
        op.Accept(XRTM.value);

    return op.Stop();
    }

bool REFRRecord::IsOppositeParent()
    {
    if(!XESP.IsLoaded()) return false;
    return (XESP->flags & fIsOppositeParent) != 0;
    }

void REFRRecord::IsOppositeParent(bool value)
    {
    if(!XESP.IsLoaded()) return;
    XESP->flags = value ? (XESP->flags | fIsOppositeParent) : (XESP->flags & ~fIsOppositeParent);
    }

bool REFRRecord::IsParentFlagMask(UINT8 Mask, bool Exact)
    {
    if(!XESP.IsLoaded()) return false;
    return Exact ? ((XESP->flags & Mask) == Mask) : ((XESP->flags & Mask) != 0);
    }

void REFRRecord::SetParentFlagMask(UINT8 Mask)
    {
    XESP.Load();
    XESP->flags = Mask;
    }

bool REFRRecord::IsVisible()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->FNAM.value & fVisible) != 0;
    }

void REFRRecord::IsVisible(bool value)
    {
    if(!Marker.IsLoaded()) return;
    Marker->FNAM.value = value ? (Marker->FNAM.value | fVisible) : (Marker->FNAM.value & ~fVisible);
    }

bool REFRRecord::IsCanTravelTo()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->FNAM.value & fCanTravelTo) != 0;
    }

void REFRRecord::IsCanTravelTo(bool value)
    {
    if(!Marker.IsLoaded()) return;
    Marker->FNAM.value = value ? (Marker->FNAM.value | fCanTravelTo) : (Marker->FNAM.value & ~fCanTravelTo);
    }

bool REFRRecord::IsMapFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Marker.IsLoaded()) return false;
    return Exact ? ((Marker->FNAM.value & Mask) == Mask) : ((Marker->FNAM.value & Mask) != 0);
    }

void REFRRecord::SetMapFlagMask(UINT8 Mask)
    {
    Marker.Load();
    Marker->FNAM.value = Mask;
    }

bool REFRRecord::IsUseDefault()
    {
    return (XACT.value & fUseDefault) != 0;
    }

void REFRRecord::IsUseDefault(bool value)
    {
    XACT.value = value ? (XACT.value | fUseDefault) : (XACT.value & ~fUseDefault);
    }

bool REFRRecord::IsActivate()
    {
    return (XACT.value & fActivate) != 0;
    }

void REFRRecord::IsActivate(bool value)
    {
    XACT.value = value ? (XACT.value | fActivate) : (XACT.value & ~fActivate);
    }

bool REFRRecord::IsOpen()
    {
    return (XACT.value & fOpen) != 0;
    }

void REFRRecord::IsOpen(bool value)
    {
    XACT.value = value ? (XACT.value | fOpen) : (XACT.value & ~fOpen);
    }

bool REFRRecord::IsOpenByDefault()
    {
    return (XACT.value & fOpenByDefault) != 0;
    }

void REFRRecord::IsOpenByDefault(bool value)
    {
    XACT.value = value ? (XACT.value | fOpenByDefault) : (XACT.value & ~fOpenByDefault);
    }

bool REFRRecord::IsActionFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((XACT.value & Mask) == Mask) : ((XACT.value & Mask) != 0);
    }

void REFRRecord::SetActionFlagMask(UINT32 Mask)
    {
    XACT.value = Mask;
    }

bool REFRRecord::IsLeveledLock()
    {
    if(!XLOC.IsLoaded()) return false;
    return (XLOC->flags & fLeveledLock) != 0;
    }

void REFRRecord::IsLeveledLock(bool value)
    {
    if(!XLOC.IsLoaded()) return;
    XLOC->flags = value ? (XLOC->flags | fLeveledLock) : (XLOC->flags & ~fLeveledLock);
    }

bool REFRRecord::IsLockFlagMask(UINT8 Mask, bool Exact)
    {
    if(!XLOC.IsLoaded()) return false;
    return Exact ? ((XLOC->flags & Mask) == Mask) : ((XLOC->flags & Mask) != 0);
    }

void REFRRecord::SetLockFlagMask(UINT8 Mask)
    {
    XLOC.Load();
    XLOC->flags = Mask;
    }

bool REFRRecord::IsNoMarker()
    {
    if(!Marker.IsLoaded()) return true;
    return (Marker->TNAM.value.markerType == eMarkerNone);
    }

void REFRRecord::IsNoMarker(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eMarkerNone;
    else if(IsNoMarker())
        Marker->TNAM.value.markerType = eCamp;
    }

bool REFRRecord::IsCamp()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eCamp);
    }

void REFRRecord::IsCamp(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eCamp;
    else if(IsCamp())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsCave()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eCave);
    }

void REFRRecord::IsCave(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eCave;
    else if(IsCave())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsCity()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eCity);
    }

void REFRRecord::IsCity(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eCity;
    else if(IsCity())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsElvenRuin()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eElvenRuin);
    }

void REFRRecord::IsElvenRuin(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eElvenRuin;
    else if(IsElvenRuin())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsFortRuin()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eFortRuin);
    }

void REFRRecord::IsFortRuin(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eFortRuin;
    else if(IsFortRuin())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsMine()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eMine);
    }

void REFRRecord::IsMine(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eMine;
    else if(IsMine())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsLandmark()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eLandmark);
    }

void REFRRecord::IsLandmark(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eLandmark;
    else if(IsLandmark())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsTavern()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eTavern);
    }

void REFRRecord::IsTavern(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eTavern;
    else if(IsTavern())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsSettlement()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eSettlement);
    }

void REFRRecord::IsSettlement(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eSettlement;
    else if(IsSettlement())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsDaedricShrine()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eDaedricShrine);
    }

void REFRRecord::IsDaedricShrine(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eDaedricShrine;
    else if(IsDaedricShrine())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsOblivionGate()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eOblivionGate);
    }

void REFRRecord::IsOblivionGate(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eOblivionGate;
    else if(IsOblivionGate())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsUnknownDoorIcon()
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == eUnknownDoorIcon);
    }

void REFRRecord::IsUnknownDoorIcon(bool value)
    {
    if(!Marker.IsLoaded()) return;
    if(value)
        Marker->TNAM.value.markerType = eUnknownDoorIcon;
    else if(IsUnknownDoorIcon())
        Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsMarkerType(UINT8 Type)
    {
    if(!Marker.IsLoaded()) return false;
    return (Marker->TNAM.value.markerType == Type);
    }

void REFRRecord::SetMarkerType(UINT8 Type)
    {
    Marker.Load();
    Marker->TNAM.value.markerType = Type;
    }

bool REFRRecord::IsNoSoul()
    {
    return (XSOL.value == eNone);
    }

void REFRRecord::IsNoSoul(bool value)
    {
    if(value)
        XSOL.value = eNone;
    else if(IsNoSoul())
        XSOL.value = ePetty;
    }

bool REFRRecord::IsPettySoul()
    {
    return (XSOL.value == ePetty);
    }

void REFRRecord::IsPettySoul(bool value)
    {
    if(value)
        XSOL.value = ePetty;
    else if(IsPettySoul())
        XSOL.value = eNone;
    }

bool REFRRecord::IsLesserSoul()
    {
    return (XSOL.value == eLesser);
    }

void REFRRecord::IsLesserSoul(bool value)
    {
    if(value)
        XSOL.value = eLesser;
    else if(IsLesserSoul())
        XSOL.value = eNone;
    }

bool REFRRecord::IsCommonSoul()
    {
    return (XSOL.value == eCommon);
    }

void REFRRecord::IsCommonSoul(bool value)
    {
    if(value)
        XSOL.value = eCommon;
    else if(IsCommonSoul())
        XSOL.value = eNone;
    }

bool REFRRecord::IsGreaterSoul()
    {
    return (XSOL.value == eGreater);
    }

void REFRRecord::IsGreaterSoul(bool value)
    {
    if(value)
        XSOL.value = eGreater;
    else if(IsGreaterSoul())
        XSOL.value = eNone;
    }

bool REFRRecord::IsGrandSoul()
    {
    return (XSOL.value == eGrand);
    }

void REFRRecord::IsGrandSoul(bool value)
    {
    if(value)
        XSOL.value = eGrand;
    else if(IsGrandSoul())
        XSOL.value = eNone;
    }

bool REFRRecord::IsSoul(UINT8 Type)
    {
    return (XSOL.value == Type);
    }

void REFRRecord::SetSoul(UINT8 Type)
    {
    XSOL.value = Type;
    }

UINT32 REFRRecord::GetType()
    {
    return REV32(REFR);
    }

STRING REFRRecord::GetStrType()
    {
    return "REFR";
    }

UINT32 REFRRecord::GetParentType()
    {
    return REV32(CELL);
    }

SINT32 REFRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    UINT32 lastChunk = 0;
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
            case REV32(NAME):
                NAME.Read(buffer, subSize, curPos);
                break;
            case REV32(XTEL):
                XTEL.Read(buffer, subSize, curPos);
                break;
            case REV32(XLOC):
                switch(subSize)
                    {
                    case 12: //unused2 is absent, so shift the values read into it
                        XLOC.Read(buffer, subSize, curPos);
                        XLOC->flags = XLOC->unused2[0];
                        XLOC->unused3[0] = XLOC->unused2[1];
                        XLOC->unused3[1] = XLOC->unused2[2];
                        XLOC->unused3[2] = XLOC->unused2[3];
                        memset(&XLOC->unused2[0], 0x00, 4);
                        break;
                    default:
                        XLOC.Read(buffer, subSize, curPos);
                        break;
                    }
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
            case REV32(XESP):
                XESP.Read(buffer, subSize, curPos);
                break;
            case REV32(XTRG):
                XTRG.Read(buffer, subSize, curPos);
                break;
            case REV32(XSED):
                switch(subSize)
                    {
                    case 1:
                        //if it's a single byte then it's an offset into the list of seed values in the TREE record
                        XSED.Load();
                        XSED->isOffset = true;
                        //XSED.size = 1;
                        _readBuffer(&XSED->offset, buffer, 1, curPos);
                        break;
                    case 4:
                        //if it's 4 byte it's the seed value directly
                        XSED.Load();
                        XSED->isOffset = false;
                        //XSED.size = 4;
                        _readBuffer(&XSED->seed, buffer, 4, curPos);
                        break;
                    default:
                        printer("  REFR: %08X - Unknown XSED size = %u\n", formID, subSize);
                        printer("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(XLOD):
                XLOD.Read(buffer, subSize, curPos);
                break;
            case REV32(XCHG):
                XCHG.Read(buffer, subSize, curPos);
                break;
            case REV32(XHLT):
                XHLT.Read(buffer, subSize, curPos);
                break;
            case REV32(XPCI):
                XPCI.Load();
                XPCI->XPCI.Read(buffer, subSize, curPos);
                lastChunk = REV32(XPCI);
                break;
            case REV32(FULL):
                switch(lastChunk)
                    {
                    case REV32(XPCI):
                        XPCI.Load();
                        XPCI->FULL.Read(buffer, subSize, curPos);
                        break;
                    case REV32(XMRK):
                        Marker->FULL.Read(buffer, subSize, curPos);
                        break;
                    default:
                        printer("  REFR: %08X - Unexpected FULL chunk\n", formID);
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(XLCM):
                XLCM.Read(buffer, subSize, curPos);
                break;
            case REV32(XRTM):
                XRTM.Read(buffer, subSize, curPos);
                break;
            case REV32(XACT):
                XACT.Read(buffer, subSize, curPos);
                break;
            case REV32(XCNT):
                XCNT.Read(buffer, subSize, curPos);
                break;
            case REV32(XMRK):
                Marker.Load();
                curPos += subSize;
                lastChunk = REV32(XMRK);
                break;
            case REV32(FNAM):
                Marker.Load();
                Marker->FNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(TNAM):
                Marker.Load();
                Marker->TNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(ONAM):
                IsOpenByDefault(true);
                curPos += subSize;
                break;
            case REV32(XSCL):
                XSCL.Read(buffer, subSize, curPos);
                break;
            case REV32(XSOL):
                XSOL.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  REFR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 REFRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NAME.Unload();
    XTEL.Unload();
    XLOC.Unload();
    Ownership.Unload();
    XESP.Unload();
    XTRG.Unload();
    XSED.Unload();
    XLOD.Unload();
    XCHG.Unload();
    XHLT.Unload();
    XPCI.Unload();
    XLCM.Unload();
    XRTM.Unload();
    XACT.Unload();
    XCNT.Unload();
    Marker.Unload();
    XSCL.Unload();
    XSOL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 REFRRecord::WriteRecord(FileWriter &writer)
    {
    char null = 0;

    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());

    if(NAME.IsLoaded())
        writer.record_write_subrecord(REV32(NAME), &NAME.value, NAME.GetSize());

    if(XTEL.IsLoaded())
        writer.record_write_subrecord(REV32(XTEL), XTEL.value, XTEL.GetSize());

    if(XLOC.IsLoaded())
        writer.record_write_subrecord(REV32(XLOC), XLOC.value, XLOC.GetSize());

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        writer.record_write_subrecord(REV32(XOWN), &Ownership->XOWN.value, Ownership->XOWN.GetSize());
        if(Ownership->XRNK.IsLoaded())
            writer.record_write_subrecord(REV32(XRNK), Ownership->XRNK.value, Ownership->XRNK.GetSize());
        if(Ownership->XGLB.IsLoaded())
            writer.record_write_subrecord(REV32(XGLB), &Ownership->XGLB.value, Ownership->XGLB.GetSize());
        }

    if(XESP.IsLoaded())
        writer.record_write_subrecord(REV32(XESP), XESP.value, XESP.GetSize());

    if(XTRG.IsLoaded())
        writer.record_write_subrecord(REV32(XTRG), &XTRG.value, XTRG.GetSize());

    if(XSED.IsLoaded())
        if(XSED->isOffset)
            writer.record_write_subrecord(REV32(XSED), &XSED->offset, 1);
        else
            writer.record_write_subrecord(REV32(XSED), &XSED->seed, 4);

    if(XLOD.IsLoaded())
        writer.record_write_subrecord(REV32(XLOD), XLOD.value, XLOD.GetSize());

    if(XCHG.IsLoaded())
        writer.record_write_subrecord(REV32(XCHG), &XCHG.value, XCHG.GetSize());

    if(XHLT.IsLoaded())
        writer.record_write_subrecord(REV32(XHLT), &XHLT.value, XHLT.GetSize());

    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        {
        writer.record_write_subrecord(REV32(XPCI), &XPCI->XPCI.value, XPCI->XPCI.GetSize());
        if(XPCI->FULL.IsLoaded())
            writer.record_write_subrecord(REV32(FULL), XPCI->FULL.value, XPCI->FULL.GetSize());
        else
            writer.record_write_subrecord(REV32(FULL), &null, 1);
        }

    if(XLCM.IsLoaded())
        writer.record_write_subrecord(REV32(XLCM), &XLCM.value, XLCM.GetSize());

    if(XRTM.IsLoaded())
        writer.record_write_subrecord(REV32(XRTM), &XRTM.value, XRTM.GetSize());

    if(XACT.IsLoaded())
        writer.record_write_subrecord(REV32(XACT), &XACT.value, XACT.GetSize());

    if(XCNT.IsLoaded())
        writer.record_write_subrecord(REV32(XCNT), &XCNT.value, XCNT.GetSize());

    if(Marker.IsLoaded())
        {
        writer.record_write_subheader(REV32(XMRK), 0);
        if(Marker->FNAM.IsLoaded())
            writer.record_write_subrecord(REV32(FNAM), &Marker->FNAM.value, Marker->FNAM.GetSize());
        if(Marker->FULL.IsLoaded())
            writer.record_write_subrecord(REV32(FULL), Marker->FULL.value, Marker->FULL.GetSize());
        if(Marker->TNAM.IsLoaded())
            writer.record_write_subrecord(REV32(TNAM), &Marker->TNAM.value, Marker->TNAM.GetSize());
        }

    if(IsOpenByDefault()) //ONAM
        writer.record_write_subheader(REV32(ONAM), 0);

    if(XSCL.IsLoaded())
        writer.record_write_subrecord(REV32(XSCL), &XSCL.value, XSCL.GetSize());

    if(XSOL.IsLoaded())
        writer.record_write_subrecord(REV32(XSOL), &XSOL.value, XSOL.GetSize());

    if(DATA.IsLoaded())
        writer.record_write_subrecord(REV32(DATA), &DATA.value, DATA.GetSize());

    return -1;
    }

bool REFRRecord::operator ==(const REFRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NAME == other.NAME &&
            XTEL == other.XTEL &&
            XLOC == other.XLOC &&
            Ownership == other.Ownership &&
            XESP == other.XESP &&
            XTRG == other.XTRG &&
            XSED == other.XSED &&
            XLOD == other.XLOD &&
            XCHG == other.XCHG &&
            XHLT == other.XHLT &&
            XPCI == other.XPCI &&
            XLCM == other.XLCM &&
            XRTM == other.XRTM &&
            XACT == other.XACT &&
            XCNT == other.XCNT &&
            Marker == other.Marker &&
            XSCL == other.XSCL &&
            XSOL == other.XSOL &&
            DATA == other.DATA);
    }

bool REFRRecord::operator !=(const REFRRecord &other) const
    {
    return !(*this == other);
    }