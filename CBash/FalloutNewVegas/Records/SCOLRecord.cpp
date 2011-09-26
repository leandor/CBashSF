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
#include "SCOLRecord.h"

namespace FNV
{
SCOLRecord::SCOLDATA::SCOLDATA():
    posX(0.0f),
    posY(0.0f),
    posZ(0.0f),
    rotX(0.0f),
    rotY(0.0f),
    rotZ(0.0f),
    scale(1.0f)
    {
    //
    }

SCOLRecord::SCOLDATA::~SCOLDATA()
    {
    //
    }

bool SCOLRecord::SCOLDATA::operator ==(const SCOLDATA &other) const
    {
    return (AlmostEqual(posX, other.posX, 2) &&
            AlmostEqual(posY, other.posY, 2) &&
            AlmostEqual(posZ, other.posZ, 2) &&
            AlmostEqual(rotX, other.rotX, 2) &&
            AlmostEqual(rotY, other.rotY, 2) &&
            AlmostEqual(rotZ, other.rotZ, 2) &&
            AlmostEqual(scale, other.scale, 2));
    }

bool SCOLRecord::SCOLDATA::operator !=(const SCOLDATA &other) const
    {
    return !(*this == other);
    }

void SCOLRecord::SCOLPart::Write(FileWriter &writer)
    {
    WRITE(ONAM);
    WRITE(DATA);
    }

bool SCOLRecord::SCOLPart::operator ==(const SCOLPart &other) const
    {
    return (ONAM == other.ONAM &&
            DATA == other.DATA);
    }
bool SCOLRecord::SCOLPart::operator !=(const SCOLPart &other) const
    {
    return !(*this == other);
    }

SCOLRecord::SCOLRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

SCOLRecord::SCOLRecord(SCOLRecord *srcRecord):
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
    Parts = srcRecord->Parts;
    return;
    }

SCOLRecord::~SCOLRecord()
    {
    //
    }

bool SCOLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(UINT32 x = 0; x < Parts.value.size(); x++)
        op.Accept(Parts.value[x]->ONAM.value);

    return op.Stop();
    }

UINT32 SCOLRecord::GetType()
    {
    return REV32(SCOL);
    }

STRING SCOLRecord::GetStrType()
    {
    return "SCOL";
    }

SINT32 SCOLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ONAM):
                Parts.value.push_back(new SCOLPart);
                Parts.value.back()->ONAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new SCOLPart);
                Parts.value.back()->DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SCOL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 SCOLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    Parts.Unload();
    return 1;
    }

SINT32 SCOLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    Parts.Write(writer);
    return -1;
    }

bool SCOLRecord::operator ==(const SCOLRecord &other) const
    {
    return (OBND == other.OBND &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            Parts == other.Parts);
    }

bool SCOLRecord::operator !=(const SCOLRecord &other) const
    {
    return !(*this == other);
    }

bool SCOLRecord::equals(Record *other)
    {
    return *this == *(SCOLRecord *)other;
    }
}