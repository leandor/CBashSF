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
#include "CONTRecord.h"

namespace FNV
{
CONTRecord::CONTDATA::CONTDATA():
    flags(0),
    weight(0.0f)
    {
    //
    }

CONTRecord::CONTDATA::~CONTDATA()
    {
    //
    }

bool CONTRecord::CONTDATA::operator ==(const CONTDATA &other) const
    {
    return (flags == other.flags &&
            AlmostEqual(weight,other.weight,2));
    }

bool CONTRecord::CONTDATA::operator !=(const CONTDATA &other) const
    {
    return !(*this == other);
    }

CONTRecord::CONTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CONTRecord::CONTRecord(CONTRecord *srcRecord):
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
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    SCRI = srcRecord->SCRI;
    CNTO = srcRecord->CNTO;
    Destructable = srcRecord->Destructable;
    DATA = srcRecord->DATA;
    SNAM = srcRecord->SNAM;
    QNAM = srcRecord->QNAM;
    RNAM = srcRecord->RNAM;
    return;
    }

CONTRecord::~CONTRecord()
    {
    //
    }

bool CONTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(UINT32 x = 0; x < CNTO.value.size(); ++x)
        {
        op.Accept(CNTO.value[x]->CNTO.value.item);
        if(CNTO.value[x]->IsGlobal())
            op.Accept(CNTO.value[x]->COED->globalOrRank);
        }
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(QNAM.IsLoaded())
        op.Accept(QNAM.value);
    if(RNAM.IsLoaded())
        op.Accept(RNAM.value);

    return op.Stop();
    }

bool CONTRecord::IsRespawn()
    {
    return (DATA.value.flags & fIsRespawn) != 0;
    }

void CONTRecord::IsRespawn(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsRespawn) : (DATA.value.flags & ~fIsRespawn);
    }

bool CONTRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void CONTRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 CONTRecord::GetType()
    {
    return REV32(CONT);
    }

STRING CONTRecord::GetStrType()
    {
    return "CONT";
    }

SINT32 CONTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(CNTO):
                CNTO.value.push_back(new FNVCNTO);
                CNTO.value.back()->CNTO.Read(buffer, subSize);
                break;
            case REV32(COED):
                if(CNTO.value.size() == 0)
                    CNTO.value.push_back(new FNVCNTO);
                CNTO.value.back()->COED.Read(buffer, subSize);
                break;
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(QNAM):
                QNAM.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CONT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 CONTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    CNTO.Unload();
    Destructable.Unload();
    DATA.Unload();
    SNAM.Unload();
    QNAM.Unload();
    RNAM.Unload();
    return 1;
    }

SINT32 CONTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(SCRI);
    CNTO.Write(writer);
    Destructable.Write(writer);
    WRITE(DATA);
    WRITE(SNAM);
    WRITE(QNAM);
    WRITE(RNAM);
    return -1;
    }

bool CONTRecord::operator ==(const CONTRecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            DATA == other.DATA &&
            SNAM == other.SNAM &&
            QNAM == other.QNAM &&
            RNAM == other.RNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            CNTO == other.CNTO &&
            MODL == other.MODL &&
            Destructable == other.Destructable);
    }

bool CONTRecord::operator !=(const CONTRecord &other) const
    {
    return !(*this == other);
    }

bool CONTRecord::equals(Record *other)
    {
    return *this == *(CONTRecord *)other;
    }
}