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
#include "GRASRecord.h"

namespace FNV
{
GRASRecord::GRASDATA::GRASDATA():
    density(0),
    minSlope(0),
    maxSlope(0),
    unused1(0xCD),
    waterDistance(0),
    waterOp(0),
    posRange(0.0f),
    heightRange(0.0f),
    colorRange(0.0f),
    wavePeriod(0.0f),
    flags(0)
    {
    memset(&unused2[0], 0xCD, sizeof(unused2));
    memset(&unused3[0], 0xCD, sizeof(unused3));
    }

GRASRecord::GRASDATA::~GRASDATA()
    {
    //
    }

bool GRASRecord::GRASDATA::operator ==(const GRASDATA &other) const
    {
    return (density == other.density &&
            minSlope == other.minSlope &&
            maxSlope == other.maxSlope &&
            waterDistance == other.waterDistance &&
            waterOp == other.waterOp &&
            AlmostEqual(posRange,other.posRange,2) &&
            AlmostEqual(heightRange,other.heightRange,2) &&
            AlmostEqual(colorRange,other.colorRange,2) &&
            AlmostEqual(wavePeriod,other.wavePeriod,2) &&
            flags == other.flags);
    }

bool GRASRecord::GRASDATA::operator !=(const GRASDATA &other) const
    {
    return !(*this == other);
    }

GRASRecord::GRASRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

GRASRecord::GRASRecord(GRASRecord *srcRecord):
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
    MODL = srcRecord->MODL;
    DATA = srcRecord->DATA;
    return;
    }

GRASRecord::~GRASRecord()
    {
    //
    }

bool GRASRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }

    return op.Stop();
    }

bool GRASRecord::IsVLighting()
    {
    return (DATA.value.flags & fIsVLighting) != 0;
    }

void GRASRecord::IsVLighting(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsVLighting) : (DATA.value.flags & ~fIsVLighting);
    }

bool GRASRecord::IsUScaling()
    {
    return (DATA.value.flags & fIsUScaling) != 0;
    }

void GRASRecord::IsUScaling(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsUScaling) : (DATA.value.flags & ~fIsUScaling);
    }

bool GRASRecord::IsFitSlope()
    {
    return (DATA.value.flags & fIsFitSlope) != 0;
    }

void GRASRecord::IsFitSlope(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsFitSlope) : (DATA.value.flags & ~fIsFitSlope);
    }

bool GRASRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void GRASRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 GRASRecord::GetType()
    {
    return REV32(GRAS);
    }

STRING GRASRecord::GetStrType()
    {
    return "GRAS";
    }

SINT32 GRASRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  GRAS: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 GRASRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 GRASRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(DATA);
    return -1;
    }

bool GRASRecord::operator ==(const GRASRecord &other) const
    {
    return (OBND == other.OBND &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL);
    }

bool GRASRecord::operator !=(const GRASRecord &other) const
    {
    return !(*this == other);
    }

bool GRASRecord::equals(Record *other)
    {
    return *this == *(GRASRecord *)other;
    }
}