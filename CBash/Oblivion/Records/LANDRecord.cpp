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
#include "LANDRecord.h"
#include "CELLRecord.h"

namespace Ob
{
LANDRecord::LANDNORMALS::LANDNORMALS():
    x(0),
    y(0),
    z(0)
    {
    //
    }

LANDRecord::LANDNORMALS::~LANDNORMALS()
    {
    //
    }

bool LANDRecord::LANDNORMALS::operator ==(const LANDNORMALS &other) const
    {
    return (x == other.x &&
            y == other.y &&
            z == other.z);
    }

bool LANDRecord::LANDNORMALS::operator !=(const LANDNORMALS &other) const
    {
    return !(*this == other);
    }

bool LANDRecord::LANDVNML::operator ==(const LANDVNML &other) const
    {
    //Record order matters on normals, so equality testing is easy
    for(UINT32 x = 0; x < 33; ++x)
        for(UINT32 y = 0; y < 33; ++y)
            if(VNML[x][y] != other.VNML[x][y])
                return false;
    return true;
    }

bool LANDRecord::LANDVNML::operator !=(const LANDVNML &other) const
    {
    return !(*this == other);
    }

LANDRecord::LANDVHGT::LANDVHGT():
    offset(0.0f)
    {
    memset(&VHGT[0][0], 0, 1089);
    memset(&unused1[0], 0, sizeof(unused1));
    }

LANDRecord::LANDVHGT::~LANDVHGT()
    {
    //
    }

bool LANDRecord::LANDVHGT::operator ==(const LANDVHGT &other) const
    {
    if(AlmostEqual(offset,other.offset,2))
        {
        //Record order matters on heights, so equality testing is easy
        for(UINT32 x = 0; x < 33; ++x)
            for(UINT32 y = 0; y < 33; ++y)
                if(VHGT[x][y] != other.VHGT[x][y])
                    return false;
        return true;
        }

    return false;
    }

bool LANDRecord::LANDVHGT::operator !=(const LANDVHGT &other) const
    {
    return !(*this == other);
    }

LANDRecord::LANDCOLORS::LANDCOLORS():
    red(0),
    green(0),
    blue(0)
    {
    //
    }

LANDRecord::LANDCOLORS::~LANDCOLORS()
    {
    //
    }

bool LANDRecord::LANDCOLORS::operator ==(const LANDCOLORS &other) const
    {
    return (red == other.red &&
            green == other.green &&
            blue == other.blue);
    }

bool LANDRecord::LANDCOLORS::operator !=(const LANDCOLORS &other) const
    {
    return !(*this == other);
    }

bool LANDRecord::LANDVCLR::operator ==(const LANDVCLR &other) const
    {
    //Record order matters on colors, so equality testing is easy
    for(UINT32 x = 0; x < 33; ++x)
        for(UINT32 y = 0; y < 33; ++y)
            if(VCLR[x][y] != other.VCLR[x][y])
                return false;
    return true;
    }

bool LANDRecord::LANDVCLR::operator !=(const LANDVCLR &other) const
    {
    return !(*this == other);
    }

LANDRecord::LANDGENTXT::LANDGENTXT():
    texture(0),
    quadrant(0),
    unused1(0),
    layer(-1)
    {
    //
    }

LANDRecord::LANDGENTXT::~LANDGENTXT()
    {
    //
    }

bool LANDRecord::LANDGENTXT::operator ==(const LANDGENTXT &other) const
    {
    return (texture == other.texture &&
            quadrant == other.quadrant &&
            layer == other.layer);
    }

bool LANDRecord::LANDGENTXT::operator !=(const LANDGENTXT &other) const
    {
    return !(*this == other);
    }

LANDRecord::LANDVTXT::LANDVTXT():
    position(0),
    opacity(0.0f)
    {
    memset(&unused1[0], 0, sizeof(unused1));
    }

LANDRecord::LANDVTXT::~LANDVTXT()
    {
    //
    }

bool LANDRecord::LANDVTXT::operator ==(const LANDVTXT &other) const
    {
    return (position == other.position &&
            AlmostEqual(opacity,other.opacity,2));
    }

bool LANDRecord::LANDVTXT::operator !=(const LANDVTXT &other) const
    {
    return !(*this == other);
    }

void LANDRecord::LANDLAYERS::Write(FileWriter &writer)
    {
    WRITE(ATXT);
    WRITE(VTXT);
    }

bool LANDRecord::LANDLAYERS::operator ==(const LANDLAYERS &other) const
    {
    return (ATXT == other.ATXT &&
            VTXT == other.VTXT);
    }

bool LANDRecord::LANDLAYERS::operator !=(const LANDLAYERS &other) const
    {
    return !(*this == other);
    }

LANDRecord::LANDRecord(unsigned char *_recData):
    Record(_recData),
    WestLand(NULL),
    EastLand(NULL),
    NorthLand(NULL),
    SouthLand(NULL)
    {
    //LAND records are normally compressed due to size
    if(_recData == NULL)
        IsCompressed(true);
    }

LANDRecord::LANDRecord(LANDRecord *srcRecord):
    Record(),
    WestLand(NULL),
    EastLand(NULL),
    NorthLand(NULL),
    SouthLand(NULL)
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    DATA = srcRecord->DATA;
    VNML = srcRecord->VNML;
    VHGT = srcRecord->VHGT;
    VCLR = srcRecord->VCLR;
    BTXT = srcRecord->BTXT;
    Layers = srcRecord->Layers;
    VTEX = srcRecord->VTEX;
    return;
    }

LANDRecord::~LANDRecord()
    {
    //Parent is a shared pointer that's deleted when the WRLD group is deleted
    //WestLand,EastLand,NorthLand,SouthLand are all shared and are deleted when the LAND is deleted
    }

bool LANDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < BTXT.value.size(); ++x)
        op.Accept(BTXT.value[x]->texture);
    for(UINT32 x = 0; x < Layers.value.size(); ++x)
        op.Accept(Layers.value[x]->ATXT.value.texture);
    for(UINT32 x = 0; x < VTEX.value.size(); x++)
        op.Accept(VTEX.value[x]);

    return op.Stop();
    }

UINT8 LANDRecord::CalcQuadrant(const UINT32 &row, const UINT32 &column)
    {
    if(column > 16)
        {
        if(row > 16) return eTopRight;
        else return eBottomRight;
        }
    else
        {
        if(row > 16) return eTopLeft;
        else return eBottomLeft;
        }
    }

UINT16 LANDRecord::CalcPosition(const UINT8 &curQuadrant, const UINT32 &row, const UINT32 &column)
    {
    switch(curQuadrant)
        {
        case eTopRight:
            return (unsigned short)((column - 16) + ((row - 16) * 17));
        case eBottomRight:
            return (unsigned short)((column - 16) + ((row) * 17));
        case eTopLeft:
            return (unsigned short)((column) + ((row - 16) * 17));
        case eBottomLeft:
            return (unsigned short)(column + (row * 17));
        default:
            return 0;
        }
    }

UINT32 LANDRecord::GetType()
    {
    return REV32(LAND);
    }

STRING LANDRecord::GetStrType()
    {
    return "LAND";
    }

FLOAT32 LANDRecord::CalcHeight(const UINT32 &row, const UINT32 &column)
    {
    if(!VHGT.IsLoaded())
        return 0.0f;

    FLOAT32 fRetValue = VHGT->offset * 8.0f;

    for(UINT32 curRow = 0; curRow <= row; ++curRow)
        fRetValue += (VHGT->VHGT[curRow][0] * 8.0f);

    for(UINT32 curColumn = 1; curColumn <= column; ++curColumn)
        fRetValue += (VHGT->VHGT[row][curColumn] * 8.0f);

    return fRetValue;
    }

SINT32 LANDRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(VNML):
                VNML.Read(buffer, subSize);
                break;
            case REV32(VHGT):
                VHGT.Read(buffer, subSize);
                break;
            case REV32(VCLR):
                VCLR.Read(buffer, subSize);
                break;
            case REV32(BTXT):
                BTXT.Read(buffer, subSize);
                break;
            case REV32(ATXT):
                Layers.value.push_back(new LANDLAYERS);
                Layers.value.back()->ATXT.Read(buffer, subSize);
                break;
            case REV32(VTXT):
                if(Layers.value.size() == 0)
                    Layers.value.push_back(new LANDLAYERS);
                Layers.value.back()->VTXT.Read(buffer, subSize);
                //switch(curTexture.value.quadrant)
                //    {
                //    case eBottomLeft:
                //        for(UINT32 x = 0; x < VTXT.size(); ++x)
                //            Merged->Points[(VTXT[x].position % 17)][(VTXT[x].position / 17)].AlphaLayer[curTexture.value.layer] = VTXT[x].opacity;
                //        break;
                //    case eBottomRight:
                //        for(UINT32 x = 0; x < VTXT.size(); ++x)
                //            Merged->Points[(VTXT[x].position % 17) + 16][(VTXT[x].position / 17)].AlphaLayer[curTexture.value.layer] = VTXT[x].opacity;
                //        break;
                //    case eTopLeft:
                //        for(UINT32 x = 0; x < VTXT.size(); ++x)
                //            Merged->Points[(VTXT[x].position % 17)][(VTXT[x].position / 17) + 16].AlphaLayer[curTexture.value.layer] = VTXT[x].opacity;
                //        break;
                //    case eTopRight:
                //        for(UINT32 x = 0; x < VTXT.size(); ++x)
                //            Merged->Points[(VTXT[x].position % 17) + 16][(VTXT[x].position / 17) + 16].AlphaLayer[curTexture.value.layer] = VTXT[x].opacity;
                //        break;
                //    default:
                //        printer("Invalid ATXT quadrant when parsing VTXT: %u\n", curTexture.value.quadrant);
                //        break;
                //    }
                break;
            case REV32(VTEX):
                VTEX.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LAND: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 LANDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    DATA.Unload();
    VNML.Unload();
    VHGT.Unload();
    VCLR.Unload();
    BTXT.Unload();
    Layers.Unload();
    VTEX.Unload();
    return 1;
    }

SINT32 LANDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(DATA);
    WRITE(VNML);
    WRITE(VHGT);
    WRITE(VCLR);
    WRITE(BTXT);
    Layers.Write(writer);
    WRITE(VTEX);

    return -1;
    }

bool LANDRecord::operator ==(const LANDRecord &other) const
    {
    return (DATA == other.DATA &&
            VNML == other.VNML &&
            VHGT == other.VHGT &&
            VCLR == other.VCLR &&
            BTXT == other.BTXT &&
            Layers == other.Layers &&
            VTEX == other.VTEX);
    }

bool LANDRecord::operator !=(const LANDRecord &other) const
    {
    return !(*this == other);
    }

bool LANDRecord::equals(Record *other)
    {
    return *this == *(LANDRecord *)other;
    }

bool LANDRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    CELLRecord *parent_cell = (CELLRecord *)GetParentRecord(), *master_cell = (CELLRecord *)((LANDRecord *)master)->GetParentRecord();
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