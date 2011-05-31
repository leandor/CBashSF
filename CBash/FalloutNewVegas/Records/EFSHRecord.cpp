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
#include "EFSHRecord.h"

namespace FNV
{
EFSHRecord::EFSHDATA::EFSHDATA():
    flags(0),
    memSBlend(0),
    memBlendOp(0),
    memZFunc(0),
    fillAIn(0.0f),
    fillAFull(0.0f),
    fillAOut(0.0f),
    fillAPRatio(0.0f),
    fillAAmp(0.0f),
    fillAFreq(0.0f),
    fillAnimSpdU(0.0f),
    fillAnimSpdV(0.0f),
    edgeEffOff(0.0f),
    edgeEffAIn(0.0f),
    edgeEffAFull(0.0f),
    edgeEffAOut(0.0f),
    edgeEffAPRatio(0.0f),
    edgeEffAAmp(0.0f),
    edgeEffAFreq(0.0f),
    fillAFRatio(0.0f),
    edgeEffAFRatio(0.0f),
    memDBlend(0),
    partSBlend(0),
    partBlendOp(0),
    partZFunc(0),
    partDBlend(0),
    partBUp(0.0f),
    partBFull(0.0f),
    partBDown(0.0f),
    partBFRatio(0.0f),
    partBPRatio(0.0f),
    partLTime(0.0f),
    partLDelta(0.0f),
    partNSpd(0.0f),
    partNAcc(0.0f),
    partVel1(0.0f),
    partVel2(0.0f),
    partVel3(0.0f),
    partAcc1(0.0f),
    partAcc2(0.0f),
    partAcc3(0.0f),
    partKey1(0.0f),
    partKey2(0.0f),
    partKey1Time(0.0f),
    partKey2Time(0.0f),
    key1A(0.0f),
    key2A(0.0f),
    key3A(0.0f),
    key1Time(0.0f),
    key2Time(0.0f),
    key3Time(0.0f),
    partInitSpd(0.0f),
    partInitRot(0.0f),
    partInitRotDelta(0.0f),
    partRotSpd(0.0f),
    partRotDelta(0.0f),
    addon(0),
    holesSTime(0.0f),
    holesETime(0.0f),
    holesSValue(0.0f),
    holesEValue(0.0f),
    edgeWidth(0.0f),
    explWindSpd(0.0f),
    textCountU(0),
    textCountV(0),
    addonFITime(0.0f),
    addonFOTime(0.0f),
    addonScaleStart(0.0f),
    addonScaleEnd(0.0f),
    addonScaleInTime(0.0f),
    addonScaleOutTime(0.0f)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

EFSHRecord::EFSHDATA::~EFSHDATA()
    {
    //
    }

bool EFSHRecord::EFSHDATA::operator ==(const EFSHDATA &other) const
    {
    return (flags == other.flags &&
            memSBlend == other.memSBlend &&
            memBlendOp == other.memBlendOp &&
            memZFunc == other.memZFunc &&
            memDBlend == other.memDBlend &&
            partSBlend == other.partSBlend &&
            partBlendOp == other.partBlendOp &&
            partZFunc == other.partZFunc &&
            partDBlend == other.partDBlend &&
            addon == other.addon &&
            fill == other.fill &&
            edgeEff == other.edgeEff &&
            key1 == other.key1 &&
            key2 == other.key2 &&
            key3 == other.key3 &&
            edge == other.edge &&
            textCountU == other.textCountU &&
            textCountV == other.textCountV &&
            AlmostEqual(fillAIn,other.fillAIn,2) &&
            AlmostEqual(fillAFull,other.fillAFull,2) &&
            AlmostEqual(fillAOut,other.fillAOut,2) &&
            AlmostEqual(fillAPRatio,other.fillAPRatio,2) &&
            AlmostEqual(fillAAmp,other.fillAAmp,2) &&
            AlmostEqual(fillAFreq,other.fillAFreq,2) &&
            AlmostEqual(fillAnimSpdU,other.fillAnimSpdU,2) &&
            AlmostEqual(fillAnimSpdV,other.fillAnimSpdV,2) &&
            AlmostEqual(edgeEffOff,other.edgeEffOff,2) &&
            AlmostEqual(edgeEffAIn,other.edgeEffAIn,2) &&
            AlmostEqual(edgeEffAFull,other.edgeEffAFull,2) &&
            AlmostEqual(edgeEffAOut,other.edgeEffAOut,2) &&
            AlmostEqual(edgeEffAPRatio,other.edgeEffAPRatio,2) &&
            AlmostEqual(edgeEffAAmp,other.edgeEffAAmp,2) &&
            AlmostEqual(edgeEffAFreq,other.edgeEffAFreq,2) &&
            AlmostEqual(fillAFRatio,other.fillAFRatio,2) &&
            AlmostEqual(edgeEffAFRatio,other.edgeEffAFRatio,2) &&
            AlmostEqual(partBUp,other.partBUp,2) &&
            AlmostEqual(partBFull,other.partBFull,2) &&
            AlmostEqual(partBDown,other.partBDown,2) &&
            AlmostEqual(partBFRatio,other.partBFRatio,2) &&
            AlmostEqual(partBPRatio,other.partBPRatio,2) &&
            AlmostEqual(partLTime,other.partLTime,2) &&
            AlmostEqual(partLDelta,other.partLDelta,2) &&
            AlmostEqual(partNSpd,other.partNSpd,2) &&
            AlmostEqual(partNAcc,other.partNAcc,2) &&
            AlmostEqual(partVel1,other.partVel1,2) &&
            AlmostEqual(partVel2,other.partVel2,2) &&
            AlmostEqual(partVel3,other.partVel3,2) &&
            AlmostEqual(partAcc1,other.partAcc1,2) &&
            AlmostEqual(partAcc2,other.partAcc2,2) &&
            AlmostEqual(partAcc3,other.partAcc3,2) &&
            AlmostEqual(partKey1,other.partKey1,2) &&
            AlmostEqual(partKey2,other.partKey2,2) &&
            AlmostEqual(partKey1Time,other.partKey1Time,2) &&
            AlmostEqual(partKey2Time,other.partKey2Time,2) &&
            AlmostEqual(key1A,other.key1A,2) &&
            AlmostEqual(key2A,other.key2A,2) &&
            AlmostEqual(key3A,other.key3A,2) &&
            AlmostEqual(key1Time,other.key1Time,2) &&
            AlmostEqual(key2Time,other.key2Time,2) &&
            AlmostEqual(key3Time,other.key3Time,2) &&
            AlmostEqual(partInitSpd,other.partInitSpd,2) &&
            AlmostEqual(partInitRot,other.partInitRot,2) &&
            AlmostEqual(partInitRotDelta,other.partInitRotDelta,2) &&
            AlmostEqual(partRotSpd,other.partRotSpd,2) &&
            AlmostEqual(partRotDelta,other.partRotDelta,2) &&
            AlmostEqual(holesSTime,other.holesSTime,2) &&
            AlmostEqual(holesETime,other.holesETime,2) &&
            AlmostEqual(holesSValue,other.holesSValue,2) &&
            AlmostEqual(holesEValue,other.holesEValue,2) &&
            AlmostEqual(edgeWidth,other.edgeWidth,2) &&
            AlmostEqual(explWindSpd,other.explWindSpd,2) &&
            AlmostEqual(addonFITime,other.addonFITime,2) &&
            AlmostEqual(addonFOTime,other.addonFOTime,2) &&
            AlmostEqual(addonScaleStart,other.addonScaleStart,2) &&
            AlmostEqual(addonScaleEnd,other.addonScaleEnd,2) &&
            AlmostEqual(addonScaleInTime,other.addonScaleInTime,2) &&
            AlmostEqual(addonScaleOutTime,other.addonScaleOutTime,2));
    }

bool EFSHRecord::EFSHDATA::operator !=(const EFSHDATA &other) const
    {
    return !(*this == other);
    }

EFSHRecord::EFSHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

EFSHRecord::EFSHRecord(EFSHRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    ICO2 = srcRecord->ICO2;
    NAM7 = srcRecord->NAM7;
    DATA = srcRecord->DATA;
    return;
    }

EFSHRecord::~EFSHRecord()
    {
    //
    }

bool EFSHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(DATA.value.addon);

    return op.Stop();
    }

bool EFSHRecord::IsNoMemShader()
    {
    return (DATA.value.flags & fIsNoMemShader) != 0;
    }

void EFSHRecord::IsNoMemShader(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoMemShader) : (DATA.value.flags & ~fIsNoMemShader);
    }

bool EFSHRecord::IsNoMembraneShader()
    {
    return (DATA.value.flags & fIsNoMemShader) != 0;
    }

void EFSHRecord::IsNoMembraneShader(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoMemShader) : (DATA.value.flags & ~fIsNoMemShader);
    }

bool EFSHRecord::IsNoPartShader()
    {
    return (DATA.value.flags & fIsNoPartShader) != 0;
    }

void EFSHRecord::IsNoPartShader(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoPartShader) : (DATA.value.flags & ~fIsNoPartShader);
    }

bool EFSHRecord::IsNoParticleShader()
    {
    return (DATA.value.flags & fIsNoPartShader) != 0;
    }

void EFSHRecord::IsNoParticleShader(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoPartShader) : (DATA.value.flags & ~fIsNoPartShader);
    }

bool EFSHRecord::IsEdgeInverse()
    {
    return (DATA.value.flags & fIsEdgeInverse) != 0;
    }

void EFSHRecord::IsEdgeInverse(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsEdgeInverse) : (DATA.value.flags & ~fIsEdgeInverse);
    }

bool EFSHRecord::IsEdgeEffectInverse()
    {
    return (DATA.value.flags & fIsEdgeInverse) != 0;
    }

void EFSHRecord::IsEdgeEffectInverse(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsEdgeInverse) : (DATA.value.flags & ~fIsEdgeInverse);
    }

bool EFSHRecord::IsMemSkinOnly()
    {
    return (DATA.value.flags & fIsMemSkinOnly) != 0;
    }

void EFSHRecord::IsMemSkinOnly(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsMemSkinOnly) : (DATA.value.flags & ~fIsMemSkinOnly);
    }

bool EFSHRecord::IsMembraneShaderSkinOnly()
    {
    return (DATA.value.flags & fIsMemSkinOnly) != 0;
    }

void EFSHRecord::IsMembraneShaderSkinOnly(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsMemSkinOnly) : (DATA.value.flags & ~fIsMemSkinOnly);
    }

bool EFSHRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void EFSHRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 EFSHRecord::GetType()
    {
    return REV32(EFSH);
    }

STRING EFSHRecord::GetStrType()
    {
    return "EFSH";
    }

SINT32 EFSHRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, curPos);
                break;
            case REV32(ICO2):
                ICO2.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM7):
                NAM7.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  EFSH: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 EFSHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    ICON.Unload();
    ICO2.Unload();
    NAM7.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 EFSHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(ICO2);
    WRITE(NAM7);
    WRITE(DATA);
    return -1;
    }

bool EFSHRecord::operator ==(const EFSHRecord &other) const
    {
    return (DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            ICO2.equalsi(other.ICO2) &&
            NAM7.equalsi(other.NAM7));
    }

bool EFSHRecord::operator !=(const EFSHRecord &other) const
    {
    return !(*this == other);
    }
}