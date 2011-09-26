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
#include "REGNRecord.h"
#include <vector>

namespace FNV
{
REGNRecord::REGNRPLD::REGNRPLD():
    posX(0.0f),
    posY(0.0f)
    {
    //
    }

REGNRecord::REGNRPLD::~REGNRPLD()
    {
    //
    }

bool REGNRecord::REGNRPLD::operator ==(const REGNRPLD &other) const
    {
    return (AlmostEqual(posX,other.posX,2) &&
            AlmostEqual(posY,other.posY,2));
    }

bool REGNRecord::REGNRPLD::operator !=(const REGNRPLD &other) const
    {
    return !(*this == other);
    }

void REGNRecord::REGNArea::Write(FileWriter &writer)
    {
    WRITE(RPLI);
    WRITE(RPLD);
    }

bool REGNRecord::REGNArea::operator ==(const REGNArea &other) const
    {
    return (RPLI == other.RPLI &&
            RPLD == other.RPLD);
    }

bool REGNRecord::REGNArea::operator !=(const REGNArea &other) const
    {
    return !(*this == other);
    }

REGNRecord::REGNRDWT::REGNRDWT():
    weather(0),
    chance(0),
    globalId(0)
    {
    //
    }

REGNRecord::REGNRDWT::~REGNRDWT()
    {
    //
    }

bool REGNRecord::REGNRDWT::operator ==(const REGNRDWT &other) const
    {
    return (weather == other.weather &&
            chance == other.chance &&
            globalId == other.globalId);
    }

bool REGNRecord::REGNRDWT::operator !=(const REGNRDWT &other) const
    {
    return !(*this == other);
    }

REGNRecord::REGNRDSD::REGNRDSD():
    sound(0),
    flags(0),
    chance(0)
    {
    //
    }

REGNRecord::REGNRDSD::~REGNRDSD()
    {
    //
    }

bool REGNRecord::REGNRDSD::IsPleasant()
    {
    return (flags & fIsPleasant) != 0;
    }

void REGNRecord::REGNRDSD::IsPleasant(bool value)
    {
    flags = value ? (flags | fIsPleasant) : (flags & ~fIsPleasant);
    }

bool REGNRecord::REGNRDSD::IsCloudy()
    {
    return (flags & fIsCloudy) != 0;
    }

void REGNRecord::REGNRDSD::IsCloudy(bool value)
    {
    flags = value ? (flags | fIsCloudy) : (flags & ~fIsCloudy);
    }

bool REGNRecord::REGNRDSD::IsRainy()
    {
    return (flags & fIsRainy) != 0;
    }

void REGNRecord::REGNRDSD::IsRainy(bool value)
    {
    flags = value ? (flags | fIsRainy) : (flags & ~fIsRainy);
    }

bool REGNRecord::REGNRDSD::IsSnowy()
    {
    return (flags & fIsSnowy) != 0;
    }

void REGNRecord::REGNRDSD::IsSnowy(bool value)
    {
    flags = value ? (flags | fIsSnowy) : (flags & ~fIsSnowy);
    }

bool REGNRecord::REGNRDSD::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((flags & Mask) == Mask) : ((flags & Mask) != 0);
    }

void REGNRecord::REGNRDSD::SetFlagMask(UINT32 Mask)
    {
    flags = Mask;
    }

bool REGNRecord::REGNRDSD::operator ==(const REGNRDSD &other) const
    {
    return (sound == other.sound &&
            flags == other.flags &&
            flags == other.flags);
    }

bool REGNRecord::REGNRDSD::operator !=(const REGNRDSD &other) const
    {
    return !(*this == other);
    }

REGNRecord::REGNRDGS::REGNRDGS():
    grass(0)
    {
    memset(&unk1[0], 0x00, sizeof(unk1));
    }

REGNRecord::REGNRDGS::~REGNRDGS()
    {
    //
    }

bool REGNRecord::REGNRDGS::operator ==(const REGNRDGS &other) const
    {
    return (grass == other.grass);
    }

bool REGNRecord::REGNRDGS::operator !=(const REGNRDGS &other) const
    {
    return !(*this == other);
    }

REGNRecord::REGNRDOT::REGNRDOT():
    objectId(0),
    parentIndex(0),
    density(0.0f),
    clustering(0),
    minSlope(0),
    maxSlope(0),
    flags(0),
    radiusWRTParent(0),
    radius(0),
    maxHeight(0.0f),
    sink(0.0f),
    sinkVar(0.0f),
    sizeVar(0.0f),
    angleVarX(0),
    angleVarY(0),
    angleVarZ(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unk1[0], 0x00, sizeof(unk1));
    memset(&unused2[0], 0x00, sizeof(unused2));
    memset(&unk2[0], 0x00, sizeof(unk2));
    }

REGNRecord::REGNRDOT::~REGNRDOT()
    {
    //
    }

bool REGNRecord::REGNRDOT::IsConformToSlope()
    {
    return (flags & fIsConformToSlope) != 0;
    }

void REGNRecord::REGNRDOT::IsConformToSlope(bool value)
    {
    flags = value ? (flags | fIsConformToSlope) : (flags & ~fIsConformToSlope);
    }

bool REGNRecord::REGNRDOT::IsPaintVertices()
    {
    return (flags & fIsPaintVertices) != 0;
    }

void REGNRecord::REGNRDOT::IsPaintVertices(bool value)
    {
    flags = value ? (flags | fIsPaintVertices) : (flags & ~fIsPaintVertices);
    }

bool REGNRecord::REGNRDOT::IsSizeVariance()
    {
    return (flags & fIsSizeVariance) != 0;
    }

void REGNRecord::REGNRDOT::IsSizeVariance(bool value)
    {
    flags = value ? (flags | fIsSizeVariance) : (flags & ~fIsSizeVariance);
    }

bool REGNRecord::REGNRDOT::IsXVariance()
    {
    return (flags & fIsXVariance) != 0;
    }

void REGNRecord::REGNRDOT::IsXVariance(bool value)
    {
    flags = value ? (flags | fIsXVariance) : (flags & ~fIsXVariance);
    }

bool REGNRecord::REGNRDOT::IsYVariance()
    {
    return (flags & fIsYVariance) != 0;
    }

void REGNRecord::REGNRDOT::IsYVariance(bool value)
    {
    flags = value ? (flags | fIsYVariance) : (flags & ~fIsYVariance);
    }

bool REGNRecord::REGNRDOT::IsZVariance()
    {
    return (flags & fIsZVariance) != 0;
    }

void REGNRecord::REGNRDOT::IsZVariance(bool value)
    {
    flags = value ? (flags | fIsZVariance) : (flags & ~fIsZVariance);
    }

bool REGNRecord::REGNRDOT::IsTree()
    {
    return (flags & fIsTree) != 0;
    }

void REGNRecord::REGNRDOT::IsTree(bool value)
    {
    flags = value ? (flags | fIsTree) : (flags & ~fIsTree);
    }

bool REGNRecord::REGNRDOT::IsHugeRock()
    {
    return (flags & fIsHugeRock) != 0;
    }

void REGNRecord::REGNRDOT::IsHugeRock(bool value)
    {
    flags = value ? (flags | fIsHugeRock) : (flags & ~fIsHugeRock);
    }

bool REGNRecord::REGNRDOT::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((flags & Mask) == Mask) : ((flags & Mask) != 0);
    }

void REGNRecord::REGNRDOT::SetFlagMask(UINT8 Mask)
    {
    flags = Mask;
    }

bool REGNRecord::REGNRDOT::operator ==(const REGNRDOT &other) const
    {
    return (objectId == other.objectId &&
            parentIndex == other.parentIndex &&
            clustering == other.clustering &&
            minSlope == other.minSlope &&
            maxSlope == other.maxSlope &&
            flags == other.flags &&
            radiusWRTParent == other.radiusWRTParent &&
            radius == other.radius &&
            angleVarX == other.angleVarX &&
            angleVarY == other.angleVarY &&
            angleVarZ == other.angleVarZ &&
            AlmostEqual(density,other.density,2) &&
            AlmostEqual(maxHeight,other.maxHeight,2) &&
            AlmostEqual(sink,other.sink,2) &&
            AlmostEqual(sinkVar,other.sinkVar,2) &&
            AlmostEqual(sizeVar,other.sizeVar,2));
    }

bool REGNRecord::REGNRDOT::operator !=(const REGNRDOT &other) const
    {
    return !(*this == other);
    }

REGNRecord::REGNRDAT::REGNRDAT():
    entryType(0),
    flags(0),
    priority(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

REGNRecord::REGNRDAT::~REGNRDAT()
    {
    //
    }

bool REGNRecord::REGNRDAT::operator ==(const REGNRDAT &other) const
    {
    return (entryType == other.entryType &&
            flags == other.flags &&
            priority == other.priority);
    }

bool REGNRecord::REGNRDAT::operator !=(const REGNRDAT &other) const
    {
    return !(*this == other);
    }

bool REGNRecord::REGNEntry::IsOverride()
    {
    return (RDAT.value.flags & fIsOverride) != 0;
    }

void REGNRecord::REGNEntry::IsOverride(bool value)
    {
    RDAT.value.flags = value ? (RDAT.value.flags | fIsOverride) : (RDAT.value.flags & ~fIsOverride);
    }

bool REGNRecord::REGNEntry::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((RDAT.value.flags & Mask) == Mask) : ((RDAT.value.flags & Mask) != 0);
    }

void REGNRecord::REGNEntry::SetFlagMask(UINT8 Mask)
    {
    RDAT.value.flags = Mask;
    }

bool REGNRecord::REGNEntry::IsObject()
    {
    return (RDAT.value.entryType == eObject);
    }

void REGNRecord::REGNEntry::IsObject(bool value)
    {
    if(value)
        RDAT.value.entryType = eObject;
    else if(IsObject())
        RDAT.value.entryType = eWeather;
    }

bool REGNRecord::REGNEntry::IsWeather()
    {
    return (RDAT.value.entryType == eWeather);
    }

void REGNRecord::REGNEntry::IsWeather(bool value)
    {
    if(value)
        RDAT.value.entryType = eWeather;
    else if(IsWeather())
        RDAT.value.entryType = eObject;
    }

bool REGNRecord::REGNEntry::IsMap()
    {
    return (RDAT.value.entryType == eMap);
    }

void REGNRecord::REGNEntry::IsMap(bool value)
    {
    if(value)
        RDAT.value.entryType = eMap;
    else if(IsMap())
        RDAT.value.entryType = eObject;
    }

bool REGNRecord::REGNEntry::IsLand()
    {
    return (RDAT.value.entryType == eLand);
    }

void REGNRecord::REGNEntry::IsLand(bool value)
    {
    if(value)
        RDAT.value.entryType = eLand;
    else if(IsLand())
        RDAT.value.entryType = eObject;
    }

bool REGNRecord::REGNEntry::IsGrass()
    {
    return (RDAT.value.entryType == eGrass);
    }

void REGNRecord::REGNEntry::IsGrass(bool value)
    {
    if(value)
        RDAT.value.entryType = eGrass;
    else if(IsGrass())
        RDAT.value.entryType = eObject;
    }

bool REGNRecord::REGNEntry::IsSound()
    {
    return (RDAT.value.entryType == eSound);
    }

void REGNRecord::REGNEntry::IsSound(bool value)
    {
    if(value)
        RDAT.value.entryType = eSound;
    else if(IsSound())
        RDAT.value.entryType = eObject;
    }

bool REGNRecord::REGNEntry::IsImposter()
    {
    return (RDAT.value.entryType == eImposter);
    }

void REGNRecord::REGNEntry::IsImposter(bool value)
    {
    if(value)
        RDAT.value.entryType = eImposter;
    else if(IsImposter())
        RDAT.value.entryType = eObject;
    }

bool REGNRecord::REGNEntry::IsType(UINT32 Type)
    {
    return (RDAT.value.entryType == Type);
    }

void REGNRecord::REGNEntry::SetType(UINT32 Type)
    {
    RDAT.value.entryType = Type;
    }

bool REGNRecord::REGNEntry::IsDefaultMusic()
    {
    return RDMD.IsLoaded() ? (*RDMD.value == eDefault) : false;
    }

void REGNRecord::REGNEntry::IsDefaultMusic(bool value)
    {
    RDMD.Load();
    if(value)
        *RDMD.value = eDefault;
    else if(IsDefaultMusic())
        *RDMD.value = ePublic;
    }

bool REGNRecord::REGNEntry::IsPublicMusic()
    {
    return RDMD.IsLoaded() ? (*RDMD.value == ePublic) : false;
    }

void REGNRecord::REGNEntry::IsPublicMusic(bool value)
    {
    RDMD.Load();
    if(value)
        *RDMD.value = ePublic;
    else if(IsPublicMusic())
        *RDMD.value = eDefault;
    }

bool REGNRecord::REGNEntry::IsDungeonMusic()
    {
    return RDMD.IsLoaded() ? (*RDMD.value == eDungeon) : false;
    }

void REGNRecord::REGNEntry::IsDungeonMusic(bool value)
    {
    RDMD.Load();
    if(value)
        *RDMD.value = eDungeon;
    else if(IsDungeonMusic())
        *RDMD.value = eDefault;
    }

bool REGNRecord::REGNEntry::IsMusicType(UINT32 Type)
    {
    return RDMD.IsLoaded() ? (*RDMD.value == Type) : false;
    }

void REGNRecord::REGNEntry::SetMusicType(UINT32 Type)
    {
    RDMD.Load();
    *RDMD.value = Type;
    }

void REGNRecord::REGNEntry::Write(FileWriter &writer)
    {
    WRITE(RDAT);
    switch(RDAT.value.entryType)
        {
        case eObject:
            WRITEREQ(RDOT);
            break;
        case eWeather:
            WRITE(RDWT);
            break;
        case eMap:
            WRITE(RDMP);
            break;
        case eLand:
            WRITE(ICON);
            break;
        case eGrass:
            WRITE(RDGS);
            break;
        case eSound:
            WRITE(RDMD);
            WRITE(RDMO);
            WRITE(RDSI);
            WRITE(RDSB);
            WRITEREQ(RDSD);
            break;
        case eImposter:
            WRITE(RDID);
            break;
        default:
            //printer("!!!%08X: Unknown REGN Entry type: %i, Index:%i!!!\n", formID, RDAT.value.entryType, p);
            break;
        }
    }

bool REGNRecord::REGNEntry::operator ==(const REGNEntry &other) const
    {
    return (RDAT == other.RDAT &&
            RDMD == other.RDMD &&
            RDMO == other.RDMO &&
            RDSI == other.RDSI &&
            RDMP.equals(other.RDMP) &&
            ICON.equalsi(other.ICON) &&
            RDSB == other.RDSB &&
            RDID == other.RDID &&
            RDSD == other.RDSD &&
            RDGS == other.RDGS &&
            RDWT == other.RDWT &&
            RDOT == other.RDOT);
    }

bool REGNRecord::REGNEntry::operator !=(const REGNEntry &other) const
    {
    return !(*this == other);
    }

REGNRecord::REGNRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

REGNRecord::REGNRecord(REGNRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    RCLR = srcRecord->RCLR;
    WNAM = srcRecord->WNAM;
    Areas = srcRecord->Areas;
    Entries = srcRecord->Entries;
    return;
    }

REGNRecord::~REGNRecord()
    {
    //
    }

bool REGNRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);
    for(UINT32 ListIndex = 0; ListIndex < Entries.value.size(); ListIndex++)
        {
        for(UINT32 ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDOT.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDOT.value[ListX2Index].objectId);
        for(UINT32 ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDGS.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDGS.value[ListX2Index].grass);
        for(UINT32 ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDSD.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDSD.value[ListX2Index].sound);
        for(UINT32 ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDWT.value.size(); ListX2Index++)
            {
            op.Accept(Entries.value[ListIndex]->RDWT.value[ListX2Index].weather);
            op.Accept(Entries.value[ListIndex]->RDWT.value[ListX2Index].globalId);
            }
        if(Entries.value[ListIndex]->RDMO.IsLoaded())
            op.Accept(Entries.value[ListIndex]->RDMO.value);
        if(Entries.value[ListIndex]->RDSI.IsLoaded())
            op.Accept(Entries.value[ListIndex]->RDSI.value);
        for(UINT32 ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDSB.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDSB.value[ListX2Index]);
        for(UINT32 ListX2Index = 0; ListX2Index < Entries.value[ListIndex]->RDID.value.size(); ListX2Index++)
            op.Accept(Entries.value[ListIndex]->RDID.value[ListX2Index]);
        }

    return op.Stop();
    }

UINT32 REGNRecord::GetType()
    {
    return REV32(REGN);
    }

STRING REGNRecord::GetStrType()
    {
    return "REGN";
    }

SINT32 REGNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                if(Entries.value.size() != 0 && Entries.value.back()->IsLand())
                    Entries.value.back()->ICON.Read(buffer, subSize, CompressedOnDisk);
                else
                    ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(RCLR):
                RCLR.Read(buffer, subSize);
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(RPLI):
                Areas.value.push_back(new REGNArea);
                Areas.value.back()->RPLI.Read(buffer, subSize);
                break;
            case REV32(RPLD):
                if(Areas.value.size() == 0)
                    Areas.value.push_back(new REGNArea);
                Areas.value.back()->RPLD.Read(buffer, subSize);
                break;
            case REV32(RDAT):
                Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDAT.Read(buffer, subSize);
                break;
            case REV32(RDOT):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDOT.Read(buffer, subSize);
                break;
            case REV32(RDMP):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDMP.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(RDGS):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDGS.Read(buffer, subSize);
                break;
            case REV32(RDMD):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDMD.Read(buffer, subSize);
                break;
            case REV32(RDMO):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDMO.Read(buffer, subSize);
                break;
            case REV32(RDSI):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDSI.Read(buffer, subSize);
                break;
            case REV32(RDSB):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDSB.Read(buffer, subSize);
                break;
            case REV32(RDSD):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDSD.Read(buffer, subSize);
                break;
            case REV32(RDWT):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDWT.Read(buffer, subSize);
                break;
            case REV32(RDID):
                if(Entries.value.size() == 0)
                    Entries.value.push_back(new REGNEntry);
                Entries.value.back()->RDID.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  REGN: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 REGNRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    MICO.Unload();
    RCLR.Unload();
    WNAM.Unload();
    Areas.Unload();
    Entries.Unload();
    return 1;
    }

SINT32 REGNRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(RCLR);
    WRITE(WNAM);
    Areas.Write(writer);
    Entries.Write(writer);
    return -1;
    }

bool REGNRecord::operator ==(const REGNRecord &other) const
    {
    return (RCLR == other.RCLR &&
            WNAM == other.WNAM &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            Areas == other.Areas &&
            Entries == other.Entries);

    return false;
    }

bool REGNRecord::operator !=(const REGNRecord &other) const
    {
    return !(*this == other);
    }

bool REGNRecord::equals(Record *other)
    {
    return *this == *(REGNRecord *)other;
    }
}