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
#include "NAVMRecord.h"
#include "CELLRecord.h"

namespace FNV
{
NAVMRecord::NAVMDATA::NAVMDATA():
    cell(0),
    numVertices(0),
    numTriangles(0),
    numConnections(0),
    numNVCA(0),
    numDoors(0)
    {
    //
    }

NAVMRecord::NAVMDATA::~NAVMDATA()
    {
    //
    }

bool NAVMRecord::NAVMDATA::operator ==(const NAVMDATA &other) const
    {
    return (cell == other.cell &&
            numVertices == other.numVertices &&
            numTriangles == other.numTriangles &&
            numConnections == other.numConnections &&
            numNVCA == other.numNVCA &&
            numDoors == other.numDoors);
    }

bool NAVMRecord::NAVMDATA::operator !=(const NAVMDATA &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMVertex::NAVMVertex():
    x(0.0f),
    y(0.0f),
    z(0.0f)
    {
    //
    }

NAVMRecord::NAVMVertex::~NAVMVertex()
    {
    //
    }

bool NAVMRecord::NAVMVertex::operator ==(const NAVMVertex &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2) &&
            AlmostEqual(z,other.z,2));
    }

bool NAVMRecord::NAVMVertex::operator !=(const NAVMVertex &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMNVTR::NAVMNVTR():
    vertex1(0),
    vertex2(0),
    vertex3(0),
    edge1(0),
    edge2(0),
    edge3(0),
    flags(0)
    {
    //
    }

NAVMRecord::NAVMNVTR::~NAVMNVTR()
    {
    //
    }

bool NAVMRecord::NAVMNVTR::IsTriangle0External()
    {
    return (flags & fIsTriangle0External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle0External(bool value)
    {
    flags = value ? (flags | fIsTriangle0External) : (flags & ~fIsTriangle0External);
    }

bool NAVMRecord::NAVMNVTR::IsTriangle1External()
    {
    return (flags & fIsTriangle1External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle1External(bool value)
    {
    flags = value ? (flags | fIsTriangle1External) : (flags & ~fIsTriangle1External);
    }

bool NAVMRecord::NAVMNVTR::IsTriangle2External()
    {
    return (flags & fIsTriangle2External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle2External(bool value)
    {
    flags = value ? (flags | fIsTriangle2External) : (flags & ~fIsTriangle2External);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown4()
    {
    return (flags & fIsUnknown4) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown4(bool value)
    {
    flags = value ? (flags | fIsUnknown4) : (flags & ~fIsUnknown4);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown5()
    {
    return (flags & fIsUnknown5) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown5(bool value)
    {
    flags = value ? (flags | fIsUnknown5) : (flags & ~fIsUnknown5);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown6()
    {
    return (flags & fIsUnknown6) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown6(bool value)
    {
    flags = value ? (flags | fIsUnknown6) : (flags & ~fIsUnknown6);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown7()
    {
    return (flags & fIsUnknown7) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown7(bool value)
    {
    flags = value ? (flags | fIsUnknown7) : (flags & ~fIsUnknown7);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown8()
    {
    return (flags & fIsUnknown8) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown8(bool value)
    {
    flags = value ? (flags | fIsUnknown8) : (flags & ~fIsUnknown8);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown9()
    {
    return (flags & fIsUnknown9) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown9(bool value)
    {
    flags = value ? (flags | fIsUnknown9) : (flags & ~fIsUnknown9);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown10()
    {
    return (flags & fIsUnknown10) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown10(bool value)
    {
    flags = value ? (flags | fIsUnknown10) : (flags & ~fIsUnknown10);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown11()
    {
    return (flags & fIsUnknown11) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown11(bool value)
    {
    flags = value ? (flags | fIsUnknown11) : (flags & ~fIsUnknown11);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown12()
    {
    return (flags & fIsUnknown12) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown12(bool value)
    {
    flags = value ? (flags | fIsUnknown12) : (flags & ~fIsUnknown12);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown13()
    {
    return (flags & fIsUnknown13) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown13(bool value)
    {
    flags = value ? (flags | fIsUnknown13) : (flags & ~fIsUnknown13);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown14()
    {
    return (flags & fIsUnknown14) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown14(bool value)
    {
    flags = value ? (flags | fIsUnknown14) : (flags & ~fIsUnknown14);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown15()
    {
    return (flags & fIsUnknown15) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown15(bool value)
    {
    flags = value ? (flags | fIsUnknown15) : (flags & ~fIsUnknown15);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown16()
    {
    return (flags & fIsUnknown16) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown16(bool value)
    {
    flags = value ? (flags | fIsUnknown16) : (flags & ~fIsUnknown16);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown17()
    {
    return (flags & fIsUnknown17) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown17(bool value)
    {
    flags = value ? (flags | fIsUnknown17) : (flags & ~fIsUnknown17);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown18()
    {
    return (flags & fIsUnknown18) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown18(bool value)
    {
    flags = value ? (flags | fIsUnknown18) : (flags & ~fIsUnknown18);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown19()
    {
    return (flags & fIsUnknown19) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown19(bool value)
    {
    flags = value ? (flags | fIsUnknown19) : (flags & ~fIsUnknown19);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown20()
    {
    return (flags & fIsUnknown20) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown20(bool value)
    {
    flags = value ? (flags | fIsUnknown20) : (flags & ~fIsUnknown20);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown21()
    {
    return (flags & fIsUnknown21) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown21(bool value)
    {
    flags = value ? (flags | fIsUnknown21) : (flags & ~fIsUnknown21);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown22()
    {
    return (flags & fIsUnknown22) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown22(bool value)
    {
    flags = value ? (flags | fIsUnknown22) : (flags & ~fIsUnknown22);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown23()
    {
    return (flags & fIsUnknown23) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown23(bool value)
    {
    flags = value ? (flags | fIsUnknown23) : (flags & ~fIsUnknown23);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown24()
    {
    return (flags & fIsUnknown24) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown24(bool value)
    {
    flags = value ? (flags | fIsUnknown24) : (flags & ~fIsUnknown24);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown25()
    {
    return (flags & fIsUnknown25) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown25(bool value)
    {
    flags = value ? (flags | fIsUnknown25) : (flags & ~fIsUnknown25);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown26()
    {
    return (flags & fIsUnknown26) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown26(bool value)
    {
    flags = value ? (flags | fIsUnknown26) : (flags & ~fIsUnknown26);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown27()
    {
    return (flags & fIsUnknown27) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown27(bool value)
    {
    flags = value ? (flags | fIsUnknown27) : (flags & ~fIsUnknown27);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown28()
    {
    return (flags & fIsUnknown28) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown28(bool value)
    {
    flags = value ? (flags | fIsUnknown28) : (flags & ~fIsUnknown28);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown29()
    {
    return (flags & fIsUnknown29) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown29(bool value)
    {
    flags = value ? (flags | fIsUnknown29) : (flags & ~fIsUnknown29);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown30()
    {
    return (flags & fIsUnknown30) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown30(bool value)
    {
    flags = value ? (flags | fIsUnknown30) : (flags & ~fIsUnknown30);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown31()
    {
    return (flags & fIsUnknown31) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown31(bool value)
    {
    flags = value ? (flags | fIsUnknown31) : (flags & ~fIsUnknown31);
    }

bool NAVMRecord::NAVMNVTR::IsUnknown32()
    {
    return (flags & fIsUnknown32) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown32(bool value)
    {
    flags = value ? (flags | fIsUnknown32) : (flags & ~fIsUnknown32);
    }

bool NAVMRecord::NAVMNVTR::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((flags & Mask) == Mask) : ((flags & Mask) != 0);
    }

void NAVMRecord::NAVMNVTR::SetFlagMask(UINT32 Mask)
    {
    flags = Mask;
    }

bool NAVMRecord::NAVMNVTR::operator ==(const NAVMNVTR &other) const
    {
    return (vertex1 == other.vertex1 &&
            vertex2 == other.vertex2 &&
            vertex3 == other.vertex3 &&
            edge1 == other.edge1 &&
            edge2 == other.edge2 &&
            edge3 == other.edge3 &&
            flags == other.flags);
    }

bool NAVMRecord::NAVMNVTR::operator !=(const NAVMNVTR &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMNVDP::NAVMNVDP():
    door(0),
    unknown1(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

NAVMRecord::NAVMNVDP::~NAVMNVDP()
    {
    //
    }

bool NAVMRecord::NAVMNVDP::operator ==(const NAVMNVDP &other) const
    {
    return (door == other.door &&
            unknown1 == other.unknown1);
    }

bool NAVMRecord::NAVMNVDP::operator !=(const NAVMNVDP &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMNVEX::NAVMNVEX():
    mesh(0),
    triangle(0)
    {
    memset(&unknown1[0], 0x00, sizeof(unknown1));
    }

NAVMRecord::NAVMNVEX::~NAVMNVEX()
    {
    //
    }

bool NAVMRecord::NAVMNVEX::operator ==(const NAVMNVEX &other) const
    {
    return (unknown1[0] == other.unknown1[0] &&
            unknown1[1] == other.unknown1[1] &&
            unknown1[2] == other.unknown1[2] &&
            unknown1[3] == other.unknown1[3] &&
            mesh == other.mesh &&
            triangle == other.triangle);
    }

bool NAVMRecord::NAVMNVEX::operator !=(const NAVMNVEX &other) const
    {
    return !(*this == other);
    }

NAVMRecord::NAVMRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

NAVMRecord::NAVMRecord(NAVMRecord *srcRecord):
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
    NVER = srcRecord->NVER;
    DATA = srcRecord->DATA;
    NVVX = srcRecord->NVVX;
    NVTR = srcRecord->NVTR;
    NVCA = srcRecord->NVCA;
    NVDP = srcRecord->NVDP;
    NVGD = srcRecord->NVGD;
    NVEX = srcRecord->NVEX;
    return;
    }

NAVMRecord::~NAVMRecord()
    {
    //
    }

bool NAVMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(DATA.value.cell);
    for(UINT32 ListIndex = 0; ListIndex < NVDP.value.size(); ListIndex++)
        op.Accept(NVDP.value[ListIndex].door);
    for(UINT32 ListIndex = 0; ListIndex < NVEX.value.size(); ListIndex++)
        op.Accept(NVEX.value[ListIndex].mesh);

    return op.Stop();
    }

UINT32 NAVMRecord::GetType()
    {
    return REV32(NAVM);
    }

STRING NAVMRecord::GetStrType()
    {
    return "NAVM";
    }

SINT32 NAVMRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(NVER):
                NVER.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(NVVX):
                NVVX.Read(buffer, subSize);
                break;
            case REV32(NVTR):
                NVTR.Read(buffer, subSize);
                break;
            case REV32(NVCA):
                NVCA.Read(buffer, subSize);
                break;
            case REV32(NVDP):
                NVDP.Read(buffer, subSize);
                break;
            case REV32(NVGD):
                NVGD.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NVEX):
                NVEX.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  NAVM: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 NAVMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    NVER.Unload();
    DATA.Unload();
    NVVX.Unload();
    NVTR.Unload();
    NVCA.Unload();
    NVDP.Unload();
    NVGD.Unload();
    NVEX.Unload();
    return 1;
    }

SINT32 NAVMRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NVER);
    WRITE(DATA);
    WRITE(NVVX);
    WRITE(NVTR);
    WRITE(NVCA);
    WRITE(NVDP);
    WRITE(NVGD);
    WRITE(NVEX);
    return -1;
    }

bool NAVMRecord::operator ==(const NAVMRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            DATA == other.DATA &&
            NVVX == other.NVVX &&
            NVTR == other.NVTR &&
            NVCA == other.NVCA &&
            NVDP == other.NVDP &&
            NVGD == other.NVGD &&
            NVEX == other.NVEX);
    }

bool NAVMRecord::operator !=(const NAVMRecord &other) const
    {
    return !(*this == other);
    }

bool NAVMRecord::equals(Record *other)
    {
    return *this == *(NAVMRecord *)other;
    }

bool NAVMRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    CELLRecord *parent_cell = (CELLRecord *)GetParentRecord(), *master_cell = (CELLRecord *)((NAVMRecord *)master)->GetParentRecord();
    //Check to make sure the parent cell is attached at the same spot
    if(parent_cell->formID != master_cell->formID)
        return false;
    if(!parent_cell->IsInterior())
        {
        if(parent_cell->GetParentRecord()->formID != master_cell->GetParentRecord()->formID)
            return false;
        read_self.Accept((Record *&)parent_cell);
        read_master.Accept((Record *&)master_cell);
        parent_cell->XCLC.Load();
        master_cell->XCLC.Load();
        if(parent_cell->XCLC->posX != master_cell->XCLC->posX)
            return false;
        if(parent_cell->XCLC->posY != master_cell->XCLC->posY)
            return false;
        }
    return true;
    }
}