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
#include "TREERecord.h"

namespace FNV
{
TREERecord::TREECNAM::TREECNAM():
    curvature(0.0f),
    minAngle(0.0f),
    maxAngle(0.0f),
    branchDim(0.0f),
    leafDim(0.0f),
    shadowRadius(0),
    rockSpeed(0.0f),
    rustleSpeed(0.0f)
    {
    //
    }

TREERecord::TREECNAM::~TREECNAM()
    {
    //
    }

bool TREERecord::TREECNAM::operator ==(const TREECNAM &other) const
    {
    return (AlmostEqual(curvature,other.curvature,2) &&
            AlmostEqual(minAngle,other.minAngle,2) &&
            AlmostEqual(maxAngle,other.maxAngle,2) &&
            AlmostEqual(branchDim,other.branchDim,2) &&
            AlmostEqual(leafDim,other.leafDim,2) &&
            shadowRadius == other.shadowRadius &&
            AlmostEqual(rockSpeed,other.rockSpeed,2) &&
            AlmostEqual(rustleSpeed,other.rustleSpeed,2));
    }

bool TREERecord::TREECNAM::operator !=(const TREECNAM &other) const
    {
    return !(*this == other);
    }

TREERecord::TREEBNAM::TREEBNAM():
    widthBill(0.0f),
    heightBill(0.0f)
    {
    //
    }

TREERecord::TREEBNAM::~TREEBNAM()
    {
    //
    }

bool TREERecord::TREEBNAM::operator ==(const TREEBNAM &other) const
    {
    return (AlmostEqual(widthBill,other.widthBill,2) &&
            AlmostEqual(heightBill,other.heightBill,2));
    }

bool TREERecord::TREEBNAM::operator !=(const TREEBNAM &other) const
    {
    return !(*this == other);
    }

TREERecord::TREERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

TREERecord::TREERecord(TREERecord *srcRecord):
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
    OBND = srcRecord->OBND;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SNAM = srcRecord->SNAM;
    CNAM = srcRecord->CNAM;
    BNAM = srcRecord->BNAM;
    return;
    }

TREERecord::~TREERecord()
    {
    //
    }

bool TREERecord::VisitFormIDs(FormIDOp &op)
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

UINT32 TREERecord::GetType()
    {
    return REV32(TREE);
    }

STRING TREERecord::GetStrType()
    {
    return "TREE";
    }

SINT32 TREERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(OBND):
                OBND.Read(buffer, subSize, curPos);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, curPos);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  TREE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 TREERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    SNAM.Unload();
    CNAM.Unload();
    BNAM.Unload();
    return 1;
    }

SINT32 TREERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(SNAM);
    WRITE(CNAM);
    WRITE(BNAM);
    return -1;
    }

bool TREERecord::operator ==(const TREERecord &other) const
    {
    return (OBND == other.OBND &&
            SNAM == other.SNAM &&
            CNAM == other.CNAM &&
            BNAM == other.BNAM &&
            MODL == other.MODL &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO));
    }

bool TREERecord::operator !=(const TREERecord &other) const
    {
    return !(*this == other);
    }
}