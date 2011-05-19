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
#include "NAVIRecord.h"

namespace FNV
{
NAVIRecord::NAVINVMI::NAVINVMI():
    mesh(0),
    location(0),
    xGrid(0),
    yGrid(0),
    unknown2(NULL),
    unknown2Size(0)
    {
    memset(&unknown1[0], 0x00, sizeof(unknown1));
    }

NAVIRecord::NAVINVMI::~NAVINVMI()
    {
    delete []unknown2;
    }

bool NAVIRecord::NAVINVMI::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < 16)
        {
        #ifdef CBASH_CHUNK_WARN
            printf("NAVIRecord::NAVINVMI: Warning - Unable to fully parse chunk (NVMI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    memcpy(&unknown1[0], buffer + curPos, 4);
    curPos += 4;
    memcpy(&mesh, buffer + curPos, 4);
    curPos += 4;
    memcpy(&location, buffer + curPos, 4);
    curPos += 4;
    memcpy(&xGrid, buffer + curPos, 2);
    curPos += 2;
    memcpy(&yGrid, buffer + curPos, 2);
    curPos += 2;
    if(subSize - 16 < subSize)  //Handle case if subSize wraps around
        {
        unknown2Size = subSize - 16;
        unknown2 = new unsigned char[unknown2Size];
        memcpy(unknown2, buffer + curPos, unknown2Size);
        curPos += unknown2Size;
        }
    return true;
    }

void NAVIRecord::NAVINVMI::Write(FileWriter &writer)
    {
    writer.record_write_subheader(REV32(NVMI), 16 + unknown2Size);
    writer.record_write(&unknown1[0], 4);
    writer.record_write(&mesh, 4);
    writer.record_write(&location, 4);
    writer.record_write(&xGrid, 2);
    writer.record_write(&yGrid, 2);
    if(unknown2Size)
        writer.record_write(unknown2, unknown2Size);
    }

NAVIRecord::NAVINVMI& NAVIRecord::NAVINVMI::operator = (const NAVINVMI &rhs)
    {
    if(this != &rhs)
        {
        mesh = rhs.mesh;
        location = rhs.location;
        xGrid = rhs.xGrid;
        yGrid = rhs.yGrid;
        unknown1[0] = rhs.unknown1[0];
        unknown1[1] = rhs.unknown1[1];
        unknown1[2] = rhs.unknown1[2];
        unknown1[3] = rhs.unknown1[3];
        unknown2Size = rhs.unknown2Size;
        delete []unknown2;
        unknown2Size = rhs.unknown2Size;
        unknown2 = new unsigned char[unknown2Size];
        memcpy(unknown2, rhs.unknown2, unknown2Size);
        }
    return *this;
    }

bool NAVIRecord::NAVINVMI::operator ==(const NAVINVMI &other) const
    {
    if(mesh == other.mesh &&
        location == other.location &&
        xGrid == other.xGrid &&
        yGrid == other.yGrid &&
        unknown1[0] == other.unknown1[0] &&
        unknown1[1] == other.unknown1[1] &&
        unknown1[2] == other.unknown1[2] &&
        unknown1[3] == other.unknown1[3] &&
        unknown2Size == other.unknown2Size)
        {
        return memcmp(unknown2, other.unknown2, unknown2Size) == 0;
        }
    return false;
    }

bool NAVIRecord::NAVINVMI::operator !=(const NAVINVMI &other) const
    {
    return !(*this == other);
    }

NAVIRecord::NAVINVCI::NAVINVCI():
    unknown1(0)
    {
    //
    }

NAVIRecord::NAVINVCI::~NAVINVCI()
    {
    //
    }

bool NAVIRecord::NAVINVCI::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(unknown1 != 0 || unknown2.size() != 0 || unknown3.size() != 0 || doors.size() != 0)
        {
        curPos += subSize;
        return false;
        }
    UINT32 initPos = curPos;
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (curPos - initPos) + 4)
        {
        #ifdef CBASH_CHUNK_WARN
            printf("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    unknown1 = *(FORMID *)(buffer + curPos);
    curPos += 4;

    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (curPos - initPos) + 4)
        {
        #ifdef CBASH_CHUNK_WARN
            printf("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    UINT32 sizeElements = *(FORMID *)(buffer + curPos) * sizeof(FORMID);
    unknown2.resize(*(FORMID *)(buffer + curPos));
    curPos += 4;
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (curPos - initPos) + sizeElements)
        {
        #ifdef CBASH_CHUNK_WARN
            printf("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    if(sizeElements)
        memcpy(&unknown2[0], buffer + curPos, sizeElements);
    curPos += sizeElements;

    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (curPos - initPos) + 4)
        {
        #ifdef CBASH_CHUNK_WARN
            printf("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    sizeElements = *(FORMID *)(buffer + curPos) * sizeof(FORMID);
    unknown3.resize(*(FORMID *)(buffer + curPos));
    curPos += 4;
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (curPos - initPos) + sizeElements)
        {
        #ifdef CBASH_CHUNK_WARN
            printf("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    if(sizeElements)
        memcpy(&unknown3[0], buffer + curPos, sizeElements);
    curPos += sizeElements;

    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (curPos - initPos) + 4)
        {
        #ifdef CBASH_CHUNK_WARN
            printf("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    sizeElements = *(FORMID *)(buffer + curPos) * sizeof(FORMID);
    doors.resize(*(FORMID *)(buffer + curPos));
    curPos += 4;
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (curPos - initPos) + sizeElements)
        {
        #ifdef CBASH_CHUNK_WARN
            printf("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    if(sizeElements)
        memcpy(&doors[0], buffer + curPos, sizeElements);
    curPos += sizeElements;
    if(subSize != (curPos - initPos))
        printf("NAVIRecord::NAVINVCI: Warning - Unable to properly parse chunk (NVCI). An "
               "unexpected format was found and there may be corrupt data present.\n");
    return true;
    }

void NAVIRecord::NAVINVCI::Write(FileWriter &writer)
    {
    if(unknown1 != 0 || unknown2.size() != 0 || unknown3.size() != 0 || doors.size() != 0)
        {
        UINT32 cSize = 16; //unknown1, and sizes for unknown2, unknown3, and doors
        cSize += unknown2.size() * sizeof(FORMID);
        cSize += unknown3.size() * sizeof(FORMID);
        cSize += doors.size() * sizeof(FORMID);
        writer.record_write_subheader(REV32(NVCI), cSize);
        writer.record_write(&unknown1, sizeof(FORMID));
        cSize = unknown2.size();
        writer.record_write(&cSize, 4);
        if(cSize)
            writer.record_write(&unknown2[0], cSize * sizeof(FORMID));
        cSize = unknown3.size();
        writer.record_write(&cSize, 4);
        if(cSize)
            writer.record_write(&unknown3[0], cSize * sizeof(FORMID));
        cSize = doors.size();
        writer.record_write(&cSize, 4);
        if(cSize)
            writer.record_write(&doors[0], cSize * sizeof(FORMID));
       }
    }

bool NAVIRecord::NAVINVCI::operator ==(const NAVINVCI &other) const
    {
    if(unknown1 == other.unknown1 &&
        unknown2.size() == other.unknown2.size() &&
        unknown3.size() == other.unknown3.size() &&
        doors.size() == other.doors.size())
        {
        //Not sure if record order matters, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < unknown2.size(); ++x)
            if(unknown2[x] != other.unknown2[x])
                return false;
        //Not sure if record order matters, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < unknown3.size(); ++x)
            if(unknown3[x] != other.unknown3[x])
                return false;
        //Not sure if record order matters, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < doors.size(); ++x)
            if(doors[x] != other.doors[x])
                return false;
        return true;
        }
    return false;
    }

bool NAVIRecord::NAVINVCI::operator !=(const NAVINVCI &other) const
    {
    return !(*this == other);
    }

NAVIRecord::NAVIRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

NAVIRecord::NAVIRecord(NAVIRecord *srcRecord):
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
    NVER = srcRecord->NVER;
    NVMI = srcRecord->NVMI;
    NVCI = srcRecord->NVCI;
    return;
    }

NAVIRecord::~NAVIRecord()
    {
    //
    }

bool NAVIRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < NVMI.value.size(); ++x)
        {
        op.Accept(NVMI.value[x]->mesh);
        op.Accept(NVMI.value[x]->location);
        }
    for(UINT32 x = 0; x < NVCI.value.size(); ++x)
        {
        op.Accept(NVCI.value[x]->unknown1);
        for(UINT32 p = 0; p < NVCI.value[x]->unknown2.size(); ++p)
            op.Accept(NVCI.value[x]->unknown2[p]);
        for(UINT32 p = 0; p < NVCI.value[x]->unknown3.size(); ++p)
            op.Accept(NVCI.value[x]->unknown3[p]);
        for(UINT32 p = 0; p < NVCI.value[x]->doors.size(); ++p)
            op.Accept(NVCI.value[x]->doors[p]);
        }

    return op.Stop();
    }

UINT32 NAVIRecord::GetType()
    {
    return REV32(NAVI);
    }

STRING NAVIRecord::GetStrType()
    {
    return "NAVI";
    }

SINT32 NAVIRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(NVER):
                NVER.Read(buffer, subSize, curPos);
                break;
            case REV32(NVMI):
                NVMI.value.push_back(new NAVINVMI);
                NVMI.value.back()->Read(buffer, subSize, curPos);
                break;
            case REV32(NVCI):
                NVCI.value.push_back(new NAVINVCI);
                NVCI.value.back()->Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  NAVI: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 NAVIRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NVER.Unload();
    NVMI.Unload();
    NVCI.Unload();
    return 1;
    }

SINT32 NAVIRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NVER);
    NVMI.Write(writer);
    NVCI.Write(writer);
    return -1;
    }

bool NAVIRecord::operator ==(const NAVIRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            NVMI == other.NVMI &&
            NVCI == other.NVCI);
    }

bool NAVIRecord::operator !=(const NAVIRecord &other) const
    {
    return !(*this == other);
    }
}