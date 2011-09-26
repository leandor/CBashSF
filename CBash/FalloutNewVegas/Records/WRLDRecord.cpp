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
#include "WRLDRecord.h"

namespace FNV
{
WRLDRecord::WRLDRecord(unsigned char *_recData):
    FNVRecord(_recData),
    CELL(NULL)
    {
    //
    }

WRLDRecord::WRLDRecord(WRLDRecord *srcRecord):
    FNVRecord(),
    CELL(NULL)
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
    XEZN = srcRecord->XEZN;
    WNAM = srcRecord->WNAM;
    PNAM = srcRecord->PNAM;
    CNAM = srcRecord->CNAM;
    NAM2 = srcRecord->NAM2;
    NAM3 = srcRecord->NAM3;
    NAM4 = srcRecord->NAM4;
    DNAM = srcRecord->DNAM;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    MNAM = srcRecord->MNAM;
    ONAM = srcRecord->ONAM;
    INAM = srcRecord->INAM;
    DATA = srcRecord->DATA;
    NAM0 = srcRecord->NAM0;
    NAM9 = srcRecord->NAM9;
    ZNAM = srcRecord->ZNAM;
    NNAM = srcRecord->NNAM;
    XNAM = srcRecord->XNAM;
    IMPS = srcRecord->IMPS;
    IMPF = srcRecord->IMPF;
    OFST = srcRecord->OFST;
    return;
    }

WRLDRecord::~WRLDRecord()
    {
    delete CELL;
    for(UINT32 x = 0; x < CELLS.size(); ++x)
        delete CELLS[x];
    }

bool WRLDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);
    op.Accept(NAM2.value);
    op.Accept(NAM3.value);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    for(UINT32 ListIndex = 0; ListIndex < IMPS.value.size(); ListIndex++)
        {
        op.Accept(IMPS.value[ListIndex]->oldImpact);
        op.Accept(IMPS.value[ListIndex]->newImpact);
        }

    return op.Stop();
    }

bool WRLDRecord::IsSmallWorld()
    {
    return (DATA.value & fIsSmallWorld) != 0;
    }

void WRLDRecord::IsSmallWorld(bool value)
    {
    DATA.value = value ? (DATA.value | fIsSmallWorld) : (DATA.value & ~fIsSmallWorld);
    }

bool WRLDRecord::IsNoFastTravel()
    {
    return (DATA.value & fIsNoFastTravel) != 0;
    }

void WRLDRecord::IsNoFastTravel(bool value)
    {
    DATA.value = value ? (DATA.value | fIsNoFastTravel) : (DATA.value & ~fIsNoFastTravel);
    }

bool WRLDRecord::IsFastTravel()
    {
    return !IsNoFastTravel();
    }

void WRLDRecord::IsFastTravel(bool value)
    {
    IsNoFastTravel(!value);
    }

bool WRLDRecord::IsNoLODWater()
    {
    return (DATA.value & fIsNoLODWater) != 0;
    }

void WRLDRecord::IsNoLODWater(bool value)
    {
    DATA.value = value ? (DATA.value | fIsNoLODWater) : (DATA.value & ~fIsNoLODWater);
    }

bool WRLDRecord::IsLODWater()
    {
    return !IsNoLODWater();
    }

void WRLDRecord::IsLODWater(bool value)
    {
    IsNoLODWater(!value);
    }

bool WRLDRecord::IsNoLODNoise()
    {
    return (DATA.value & fIsNoLODNoise) != 0;
    }

void WRLDRecord::IsNoLODNoise(bool value)
    {
    DATA.value = value ? (DATA.value | fIsNoLODNoise) : (DATA.value & ~fIsNoLODNoise);
    }

bool WRLDRecord::IsLODNoise()
    {
    return !IsNoLODNoise();
    }

void WRLDRecord::IsLODNoise(bool value)
    {
    IsNoLODNoise(!value);
    }

bool WRLDRecord::IsNoNPCFallDmg()
    {
    return (DATA.value & fIsNoNPCFallDmg) != 0;
    }

void WRLDRecord::IsNoNPCFallDmg(bool value)
    {
    DATA.value = value ? (DATA.value | fIsNoNPCFallDmg) : (DATA.value & ~fIsNoNPCFallDmg);
    }

bool WRLDRecord::IsNPCFallDmg()
    {
    return !IsNoNPCFallDmg();
    }

void WRLDRecord::IsNPCFallDmg(bool value)
    {
    IsNoNPCFallDmg(!value);
    }

bool WRLDRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void WRLDRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value = Mask;
    }

bool WRLDRecord::IsUseLandData()
    {
    return (PNAM.value & fIsUseLandData) != 0;
    }

void WRLDRecord::IsUseLandData(bool value)
    {
    PNAM.value = value ? (PNAM.value | fIsUseLandData) : (PNAM.value & ~fIsUseLandData);
    }

bool WRLDRecord::IsUseLODData()
    {
    return (PNAM.value & fIsUseLODData) != 0;
    }

void WRLDRecord::IsUseLODData(bool value)
    {
    PNAM.value = value ? (PNAM.value | fIsUseLODData) : (PNAM.value & ~fIsUseLODData);
    }

bool WRLDRecord::IsUseMapData()
    {
    return (PNAM.value & fIsUseMapData) != 0;
    }

void WRLDRecord::IsUseMapData(bool value)
    {
    PNAM.value = value ? (PNAM.value | fIsUseMapData) : (PNAM.value & ~fIsUseMapData);
    }

bool WRLDRecord::IsUseWaterData()
    {
    return (PNAM.value & fIsUseWaterData) != 0;
    }

void WRLDRecord::IsUseWaterData(bool value)
    {
    PNAM.value = value ? (PNAM.value | fIsUseWaterData) : (PNAM.value & ~fIsUseWaterData);
    }

bool WRLDRecord::IsUseClimateData()
    {
    return (PNAM.value & fIsUseClimateData) != 0;
    }

void WRLDRecord::IsUseClimateData(bool value)
    {
    PNAM.value = value ? (PNAM.value | fIsUseClimateData) : (PNAM.value & ~fIsUseClimateData);
    }

bool WRLDRecord::IsUseImageSpaceData()
    {
    return (PNAM.value & fIsUseImageSpaceData) != 0;
    }

void WRLDRecord::IsUseImageSpaceData(bool value)
    {
    PNAM.value = value ? (PNAM.value | fIsUseImageSpaceData) : (PNAM.value & ~fIsUseImageSpaceData);
    }

bool WRLDRecord::IsNeedsWaterAdjustment()
    {
    return (PNAM.value & fIsNeedsWaterAdjustment) != 0;
    }

void WRLDRecord::IsNeedsWaterAdjustment(bool value)
    {
    PNAM.value = value ? (PNAM.value | fIsNeedsWaterAdjustment) : (PNAM.value & ~fIsNeedsWaterAdjustment);
    }

bool WRLDRecord::IsUseFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? ((PNAM.value & Mask) == Mask) : ((PNAM.value & Mask) != 0);
    }

void WRLDRecord::SetUseFlagMask(UINT16 Mask)
    {
    PNAM.value = Mask;
    }

UINT32 WRLDRecord::GetType()
    {
    return REV32(WRLD);
    }

STRING WRLDRecord::GetStrType()
    {
    return "WRLD";
    }

SINT32 WRLDRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(XEZN):
                XEZN.Read(buffer, subSize);
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize);
                break;
            case REV32(NAM3):
                NAM3.Read(buffer, subSize);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                ONAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize);
                break;
            case REV32(NAM9):
                NAM9.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(NNAM):
                NNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(IMPS):
                IMPS.Read(buffer, subSize);
                break;
            case REV32(IMPF):
                IMPF.Read(buffer, subSize);
                break;
            case REV32(OFST):
                OFST.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WRLD: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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
    XEZN.Unload();
    WNAM.Unload();
    PNAM.Unload();
    CNAM.Unload();
    NAM2.Unload();
    NAM3.Unload();
    NAM4.Unload();
    DNAM.Unload();
    ICON.Unload();
    MICO.Unload();
    MNAM.Unload();
    ONAM.Unload();
    INAM.Unload();
    DATA.Unload();
    NAM0.Unload();
    NAM9.Unload();
    ZNAM.Unload();
    NNAM.Unload();
    XNAM.Unload();
    IMPS.Unload();
    IMPF.Unload();
    OFST.Unload();
    return 1;
    }

SINT32 WRLDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(XEZN);
    WRITE(WNAM);
    WRITE(PNAM);
    WRITE(CNAM);
    WRITE(NAM2);
    WRITE(NAM3);
    WRITE(NAM4);
    WRITE(DNAM);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(MNAM);
    WRITE(ONAM);
    WRITE(INAM);
    WRITE(DATA);
    WRITE(NAM0);
    WRITE(NAM9);
    WRITE(ZNAM);
    WRITEREQ(NNAM);
    WRITEREQ(XNAM);
    WRITE(IMPS);
    WRITE(IMPF);
    WRITE(OFST);

    return -1;
    }

bool WRLDRecord::operator ==(const WRLDRecord &other) const
    {
    return (XEZN == other.XEZN &&
            WNAM == other.WNAM &&
            PNAM == other.PNAM &&
            CNAM == other.CNAM &&
            NAM2 == other.NAM2 &&
            NAM3 == other.NAM3 &&
            NAM4 == other.NAM4 &&
            DNAM == other.DNAM &&
            MNAM == other.MNAM &&
            ONAM == other.ONAM &&
            INAM == other.INAM &&
            DATA == other.DATA &&
            NAM0 == other.NAM0 &&
            NAM9 == other.NAM9 &&
            ZNAM == other.ZNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            NNAM.equalsi(other.NNAM) &&
            XNAM.equalsi(other.XNAM) &&
            IMPS == other.IMPS &&
            IMPF == other.IMPF &&
            OFST == other.OFST);
    }

bool WRLDRecord::operator !=(const WRLDRecord &other) const
    {
    return !(*this == other);
    }

bool WRLDRecord::equals(Record *other)
    {
    return *this == *(WRLDRecord *)other;
    }

bool WRLDRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //              all child records have been visited
    const WRLDRecord *master_wrld = (WRLDRecord *)master;

    if(CELLS.size() > master_wrld->CELLS.size())
        return false;

    if(CELL != NULL)
        {
        if(master_wrld->CELL != NULL)
            {
            if(identical_records.count(CELL) == 0)
                return false;
            }
        else
            return false;
        }

    for(UINT32 ListIndex = 0; ListIndex < CELLS.size(); ++ListIndex)
        if(identical_records.count(CELLS[ListIndex]) == 0)
                return false;
    return true;
    }
}