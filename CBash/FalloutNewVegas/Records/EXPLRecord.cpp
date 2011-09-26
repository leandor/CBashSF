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
#include "EXPLRecord.h"

namespace FNV
{
EXPLRecord::EXPLDATA::EXPLDATA():
    force(0.0f),
    damage(0.0f),
    radius(0.0f),
    light(0),
    sound1(0),
    flags(0),
    ISRadius(0.0f),
    impactDataSet(0),
    sound2(0),
    radLevel(0.0f),
    radTime(0.0f),
    radRadius(0.0f),
    soundLevel(0)
    {
    //
    }

EXPLRecord::EXPLDATA::~EXPLDATA()
    {
    //
    }

bool EXPLRecord::EXPLDATA::operator ==(const EXPLDATA &other) const
    {
    return (light == other.light &&
            sound1 == other.sound1 &&
            flags == other.flags &&
            impactDataSet == other.impactDataSet &&
            sound2 == other.sound2 &&
            soundLevel == other.soundLevel &&
            AlmostEqual(force,other.force,2) &&
            AlmostEqual(damage,other.damage,2) &&
            AlmostEqual(radius,other.radius,2) &&
            AlmostEqual(ISRadius,other.ISRadius,2) &&
            AlmostEqual(radLevel,other.radLevel,2) &&
            AlmostEqual(radTime,other.radTime,2) &&
            AlmostEqual(radRadius,other.radRadius,2));
    }

bool EXPLRecord::EXPLDATA::operator !=(const EXPLDATA &other) const
    {
    return !(*this == other);
    }

EXPLRecord::EXPLRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

EXPLRecord::EXPLRecord(EXPLRecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    EITM = srcRecord->EITM;
    MNAM = srcRecord->MNAM;
    DATA = srcRecord->DATA;
    INAM = srcRecord->INAM;
    return;
    }

EXPLRecord::~EXPLRecord()
    {
    //
    }

bool EXPLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(EITM.IsLoaded())
        op.Accept(EITM.value);
    if(MNAM.IsLoaded())
        op.Accept(MNAM.value);
    op.Accept(DATA.value.light);
    op.Accept(DATA.value.sound1);
    op.Accept(DATA.value.impactDataSet);
    op.Accept(DATA.value.sound2);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);

    return op.Stop();
    }

bool EXPLRecord::IsUnknown1()
    {
    return (DATA.value.flags & fIsUnknown1) != 0;
    }

void EXPLRecord::IsUnknown1(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsUnknown1) : (DATA.value.flags & ~fIsUnknown1);
    }

bool EXPLRecord::IsAlwaysUsesWorldOrientation()
    {
    return (DATA.value.flags & fIsAlwaysUsesWorldOrientation) != 0;
    }

void EXPLRecord::IsAlwaysUsesWorldOrientation(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsAlwaysUsesWorldOrientation) : (DATA.value.flags & ~fIsAlwaysUsesWorldOrientation);
    }

bool EXPLRecord::IsAlwaysKnockDown()
    {
    return (DATA.value.flags & fIsAlwaysKnockDown) != 0;
    }

void EXPLRecord::IsAlwaysKnockDown(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsAlwaysKnockDown) : (DATA.value.flags & ~fIsAlwaysKnockDown);
    }

bool EXPLRecord::IsFormulaKnockDown()
    {
    return (DATA.value.flags & fIsFormulaKnockDown) != 0;
    }

void EXPLRecord::IsFormulaKnockDown(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsFormulaKnockDown) : (DATA.value.flags & ~fIsFormulaKnockDown);
    }

bool EXPLRecord::IsIgnoreLOS()
    {
    return (DATA.value.flags & fIsIgnoreLOS) != 0;
    }

void EXPLRecord::IsIgnoreLOS(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsIgnoreLOS) : (DATA.value.flags & ~fIsIgnoreLOS);
    }

bool EXPLRecord::IsPushExplosionSourceRefOnly()
    {
    return (DATA.value.flags & fIsPushExplosionSourceRefOnly) != 0;
    }

void EXPLRecord::IsPushExplosionSourceRefOnly(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsPushExplosionSourceRefOnly) : (DATA.value.flags & ~fIsPushExplosionSourceRefOnly);
    }

bool EXPLRecord::IsIgnoreImageSpaceSwap()
    {
    return (DATA.value.flags & fIsIgnoreImageSpaceSwap) != 0;
    }

void EXPLRecord::IsIgnoreImageSpaceSwap(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsIgnoreImageSpaceSwap) : (DATA.value.flags & ~fIsIgnoreImageSpaceSwap);
    }

bool EXPLRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void EXPLRecord::SetFlagMask(UINT32 Mask)
    {
    DATA.value.flags = Mask;
    }

bool EXPLRecord::IsLoud()
    {
    return DATA.value.soundLevel == eLoud;
    }

void EXPLRecord::IsLoud(bool value)
    {
    DATA.value.soundLevel = value ? eLoud : eNormal;
    }

bool EXPLRecord::IsNormal()
    {
    return DATA.value.soundLevel == eNormal;
    }

void EXPLRecord::IsNormal(bool value)
    {
    DATA.value.soundLevel = value ? eNormal : eLoud;
    }

bool EXPLRecord::IsSilent()
    {
    return DATA.value.soundLevel == eSilent;
    }

void EXPLRecord::IsSilent(bool value)
    {
    DATA.value.soundLevel = value ? eSilent : eLoud;
    }

bool EXPLRecord::IsSoundLevelType(UINT8 Type)
    {
    return DATA.value.soundLevel == Type;
    }

void EXPLRecord::SetSoundLevelType(UINT8 Type)
    {
    DATA.value.soundLevel = Type;
    }

UINT32 EXPLRecord::GetType()
    {
    return REV32(EXPL);
    }

STRING EXPLRecord::GetStrType()
    {
    return "EXPL";
    }

SINT32 EXPLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(EITM):
                EITM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  EXPL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 EXPLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    EITM.Unload();
    MNAM.Unload();
    DATA.Unload();
    INAM.Unload();
    return 1;
    }

SINT32 EXPLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(EITM);
    WRITE(MNAM);
    WRITE(DATA);
    WRITE(INAM);
    return -1;
    }

bool EXPLRecord::operator ==(const EXPLRecord &other) const
    {
    return (OBND == other.OBND &&
            EITM == other.EITM &&
            MNAM == other.MNAM &&
            DATA == other.DATA &&
            INAM == other.INAM &&
            MODL == other.MODL &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL));
    }

bool EXPLRecord::operator !=(const EXPLRecord &other) const
    {
    return !(*this == other);
    }

bool EXPLRecord::equals(Record *other)
    {
    return *this == *(EXPLRecord *)other;
    }
}