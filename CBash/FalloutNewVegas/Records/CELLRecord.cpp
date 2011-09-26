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

namespace FNV
{
CELLRecord::CELLXCLC::CELLXCLC():
    posX(0),
    posY(0),
    flags(0)
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
            posY == other.posY &&
            flags == other.flags);
    }

bool CELLRecord::CELLXCLC::operator !=(const CELLXCLC &other) const
    {
    return !(*this == other);
    }

CELLRecord::CELLRecord(unsigned char *_recData):
    FNVRecord(_recData),
    LAND(NULL)
    {
    //
    }

CELLRecord::CELLRecord(CELLRecord *srcRecord):
    FNVRecord(),
    LAND(NULL)
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
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    XCLC = srcRecord->XCLC;
    XCLL = srcRecord->XCLL;
    IMPS = srcRecord->IMPS;
    IMPF = srcRecord->IMPF;
    LTMP = srcRecord->LTMP;
    LNAM = srcRecord->LNAM;
    XCLW = srcRecord->XCLW;
    XNAM = srcRecord->XNAM;
    XCLR = srcRecord->XCLR;
    XCIM = srcRecord->XCIM;
    XCET = srcRecord->XCET;
    XEZN = srcRecord->XEZN;
    XCCM = srcRecord->XCCM;
    XCWT = srcRecord->XCWT;
    Ownership = srcRecord->Ownership;
    XCAS = srcRecord->XCAS;
    XCMT = srcRecord->XCMT;
    XCMO = srcRecord->XCMO;
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
    for(UINT32 x = 0; x < PGRE.size(); ++x)
        delete PGRE[x];
    for(UINT32 x = 0; x < PMIS.size(); ++x)
        delete PMIS[x];
    for(UINT32 x = 0; x < PBEA.size(); ++x)
        delete PBEA[x];
    for(UINT32 x = 0; x < PFLA.size(); ++x)
        delete PFLA[x];
    for(UINT32 x = 0; x < PCBE.size(); ++x)
        delete PCBE[x];
    for(UINT32 x = 0; x < NAVM.size(); ++x)
        delete NAVM[x];
    delete LAND;
    }

bool CELLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < IMPS.value.size(); ListIndex++)
        {
        op.Accept(IMPS.value[ListIndex]->oldImpact);
        op.Accept(IMPS.value[ListIndex]->newImpact);
        }
    op.Accept(LTMP.value);
    for(UINT32 x = 0; x < XCLR.value.size(); x++)
        op.Accept(XCLR.value[x]);
    if(XCIM.IsLoaded())
        op.Accept(XCIM.value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(XCCM.IsLoaded())
        op.Accept(XCCM.value);
    if(XCWT.IsLoaded())
        op.Accept(XCWT.value);
    if(Ownership.IsLoaded())
        op.Accept(Ownership->XOWN.value);
    if(XCAS.IsLoaded())
        op.Accept(XCAS.value);
    if(XCMO.IsLoaded())
        op.Accept(XCMO.value);
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
    if(IsInterior()) return false;
    return (DATA.value & fForceHideLand) != 0;
    }

void CELLRecord::IsForceHideLand(bool value)
    {
    if(IsInterior()) return;
    DATA.value = value ? (DATA.value | fForceHideLand) : (DATA.value & ~fForceHideLand);
    }

bool CELLRecord::IsOblivionInterior()
    {
    if(!IsInterior()) return false;
    return (DATA.value & fIsOblivionInterior) != 0;
    }

void CELLRecord::IsOblivionInterior(bool value)
    {
    if(!IsInterior()) return;
    DATA.value = value ? (DATA.value | fIsOblivionInterior) : (DATA.value & ~fIsOblivionInterior);
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

bool CELLRecord::IsQuad1ForceHidden()
    {
    if(!XCLC.IsLoaded()) return false;
    return (XCLC->flags & fIsQuad1ForceHidden) != 0;
    }

void CELLRecord::IsQuad1ForceHidden(bool value)
    {
    if(!XCLC.IsLoaded()) return;
    XCLC->flags = value ? (XCLC->flags | fIsQuad1ForceHidden) : (XCLC->flags & ~fIsQuad1ForceHidden);
    }

bool CELLRecord::IsQuad2ForceHidden()
    {
    if(!XCLC.IsLoaded()) return false;
    return (XCLC->flags & fIsQuad2ForceHidden) != 0;
    }

void CELLRecord::IsQuad2ForceHidden(bool value)
    {
    if(!XCLC.IsLoaded()) return;
    XCLC->flags = value ? (XCLC->flags | fIsQuad2ForceHidden) : (XCLC->flags & ~fIsQuad2ForceHidden);
    }

bool CELLRecord::IsQuad3ForceHidden()
    {
    if(!XCLC.IsLoaded()) return false;
    return (XCLC->flags & fIsQuad3ForceHidden) != 0;
    }

void CELLRecord::IsQuad3ForceHidden(bool value)
    {
    if(!XCLC.IsLoaded()) return;
    XCLC->flags = value ? (XCLC->flags | fIsQuad3ForceHidden) : (XCLC->flags & ~fIsQuad3ForceHidden);
    }

bool CELLRecord::IsQuad4ForceHidden()
    {
    if(!XCLC.IsLoaded()) return false;
    return (XCLC->flags & fIsQuad4ForceHidden) != 0;
    }

void CELLRecord::IsQuad4ForceHidden(bool value)
    {
    if(!XCLC.IsLoaded()) return;
    XCLC->flags = value ? (XCLC->flags | fIsQuad4ForceHidden) : (XCLC->flags & ~fIsQuad4ForceHidden);
    }

bool CELLRecord::IsQuadFlagMask(UINT32 Mask, bool Exact)
    {
    if(!XCLC.IsLoaded()) return false;
    return Exact ? ((XCLC->flags & Mask) == Mask) : ((XCLC->flags & Mask) != 0);
    }

void CELLRecord::SetQuadFlagMask(UINT32 Mask)
    {
    XCLC.Load();
    XCLC->flags = Mask;
    }

bool CELLRecord::IsLightAmbientInherited()
    {
    return (LNAM.value & fIsAmbientInherited) != 0;
    }

void CELLRecord::IsLightAmbientInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsAmbientInherited) : (LNAM.value & ~fIsAmbientInherited);
    }

bool CELLRecord::IsLightDirectionalColorInherited()
    {
    return (LNAM.value & fIsDirectionalColorInherited) != 0;
    }

void CELLRecord::IsLightDirectionalColorInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsDirectionalColorInherited) : (LNAM.value & ~fIsDirectionalColorInherited);
    }

bool CELLRecord::IsLightFogColorInherited()
    {
    return (LNAM.value & fIsFogColorInherited) != 0;
    }

void CELLRecord::IsLightFogColorInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsFogColorInherited) : (LNAM.value & ~fIsFogColorInherited);
    }

bool CELLRecord::IsLightFogNearInherited()
    {
    return (LNAM.value & fIsFogNearInherited) != 0;
    }

void CELLRecord::IsLightFogNearInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsFogNearInherited) : (LNAM.value & ~fIsFogNearInherited);
    }

bool CELLRecord::IsLightFogFarInherited()
    {
    return (LNAM.value & fIsFogFarInherited) != 0;
    }

void CELLRecord::IsLightFogFarInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsFogFarInherited) : (LNAM.value & ~fIsFogFarInherited);
    }

bool CELLRecord::IsLightDirectionalRotationInherited()
    {
    return (LNAM.value & fIsDirectionalRotationInherited) != 0;
    }

void CELLRecord::IsLightDirectionalRotationInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsDirectionalRotationInherited) : (LNAM.value & ~fIsDirectionalRotationInherited);
    }

bool CELLRecord::IsLightDirectionalFadeInherited()
    {
    return (LNAM.value & fIsDirectionalFadeInherited) != 0;
    }

void CELLRecord::IsLightDirectionalFadeInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsDirectionalFadeInherited) : (LNAM.value & ~fIsDirectionalFadeInherited);
    }

bool CELLRecord::IsLightFogClipInherited()
    {
    return (LNAM.value & fIsFogClipInherited) != 0;
    }

void CELLRecord::IsLightFogClipInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsFogClipInherited) : (LNAM.value & ~fIsFogClipInherited);
    }

bool CELLRecord::IsLightFogPowerInherited()
    {
    return (LNAM.value & fIsFogPowerInherited) != 0;
    }

void CELLRecord::IsLightFogPowerInherited(bool value)
    {
    LNAM.value = value ? (LNAM.value | fIsFogPowerInherited) : (LNAM.value & ~fIsFogPowerInherited);
    }

bool CELLRecord::IsLightFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((LNAM.value & Mask) == Mask) : ((LNAM.value & Mask) != 0);
    }

void CELLRecord::SetLightFlagMask(UINT32 Mask)
    {
    LNAM.value = Mask;
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
            case REV32(XCLC):
                XCLC.Read(buffer, subSize);
                break;
            case REV32(XCLL):
                XCLL.Read(buffer, subSize);
                break;
            case REV32(IMPS):
                IMPS.Read(buffer, subSize);
                break;
            case REV32(IMPF):
                IMPF.Read(buffer, subSize);
                break;
            case REV32(LTMP):
                LTMP.Read(buffer, subSize);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            case REV32(XCLW):
                XCLW.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XCLR):
                XCLR.Read(buffer, subSize);
                break;
            case REV32(XCIM):
                XCIM.Read(buffer, subSize);
                break;
            case REV32(XCET):
                XCET.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XEZN):
                XEZN.Read(buffer, subSize);
                break;
            case REV32(XCCM):
                XCCM.Read(buffer, subSize);
                break;
            case REV32(XCWT):
                XCWT.Read(buffer, subSize);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize);
                break;
            case REV32(XCAS):
                XCAS.Read(buffer, subSize);
                break;
            case REV32(XCMT):
                XCMT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XCMO):
                XCMO.Read(buffer, subSize);
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
    DATA.Unload();
    XCLC.Unload();
    XCLL.Unload();
    IMPS.Unload();
    IMPF.Unload();
    LTMP.Unload();
    LNAM.Unload();
    XCLW.Unload();
    XNAM.Unload();
    XCLR.Unload();
    XCIM.Unload();
    XCET.Unload();
    XEZN.Unload();
    XCCM.Unload();
    XCWT.Unload();
    Ownership.Unload();
    XCAS.Unload();
    XCMT.Unload();
    XCMO.Unload();
    return 1;
    }

SINT32 CELLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    //DATA.Unload(); //need to keep IsInterior around
    WRITE(XCLC);
    WRITE(XCLL);
    WRITE(IMPS);
    WRITE(IMPF);
    if(LNAM.value != 0 || LTMP.value != 0)
        {
        WRITE(LTMP);
        WRITE(LNAM);
        }
    if(XCLW.IsLoaded())
        WRITE(XCLW);
    else if(IsHasWater())
        WRITEREQ(XCLW);
    WRITE(XNAM);
    WRITE(XCLR);
    WRITE(XCIM);
    WRITE(XCET);
    WRITE(XEZN);
    WRITE(XCCM);
    WRITE(XCWT);
    Ownership.Write(writer);
    WRITE(XCAS);
    WRITE(XCMT);
    WRITE(XCMO);
    return -1;
    }

bool CELLRecord::operator ==(const CELLRecord &other) const
    {
    return (DATA == other.DATA &&
            XCLC == other.XCLC &&
            XCLL == other.XCLL &&
            IMPF == other.IMPF &&
            LTMP == other.LTMP &&
            LNAM == other.LNAM &&
            XCLW == other.XCLW &&
            XCIM == other.XCIM &&
            XEZN == other.XEZN &&
            XCCM == other.XCCM &&
            XCWT == other.XCWT &&
            XCAS == other.XCAS &&
            XCMO == other.XCMO &&
            IMPS == other.IMPS &&
            XCLR == other.XCLR &&
            Ownership == other.Ownership &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            XNAM.equalsi(other.XNAM) &&
            XCET == other.XCET &&
            XCMT == other.XCMT);
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
    if(PGRE.size() > master_cell->PGRE.size())
        return false;
    if(PMIS.size() > master_cell->PMIS.size())
        return false;
    if(PBEA.size() > master_cell->PBEA.size())
        return false;
    if(PFLA.size() > master_cell->PFLA.size())
        return false;
    if(PCBE.size() > master_cell->PCBE.size())
        return false;
    if(NAVM.size() > master_cell->NAVM.size())
        return false;

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

    for(UINT32 ListIndex = 0; ListIndex < PGRE.size(); ++ListIndex)
        if(identical_records.count(PGRE[ListIndex]) == 0)
                return false;

    for(UINT32 ListIndex = 0; ListIndex < PMIS.size(); ++ListIndex)
        if(identical_records.count(PMIS[ListIndex]) == 0)
                return false;

    for(UINT32 ListIndex = 0; ListIndex < PBEA.size(); ++ListIndex)
        if(identical_records.count(PBEA[ListIndex]) == 0)
                return false;

    for(UINT32 ListIndex = 0; ListIndex < PFLA.size(); ++ListIndex)
        if(identical_records.count(PFLA[ListIndex]) == 0)
                return false;

    for(UINT32 ListIndex = 0; ListIndex < PCBE.size(); ++ListIndex)
        if(identical_records.count(PCBE[ListIndex]) == 0)
                return false;

    for(UINT32 ListIndex = 0; ListIndex < NAVM.size(); ++ListIndex)
        if(identical_records.count(NAVM[ListIndex]) == 0)
                return false;
    return true;
    }
}