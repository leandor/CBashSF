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
#include "ACTIRecord.h"

namespace FNV
{
ACTIRecord::ACTIRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ACTIRecord::ACTIRecord(ACTIRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    SCRI = srcRecord->SCRI;
    Destructable = srcRecord->Destructable;
    SNAM = srcRecord->SNAM;
    VNAM = srcRecord->VNAM;
    INAM = srcRecord->INAM;
    RNAM = srcRecord->RNAM;
    WNAM = srcRecord->WNAM;
    XATO = srcRecord->XATO;
    return;
    }

ACTIRecord::~ACTIRecord()
    {
    //
    }

bool ACTIRecord::VisitFormIDs(FormIDOp &op)
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
    if(VNAM.IsLoaded())
        op.Accept(VNAM.value);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(RNAM.IsLoaded())
        op.Accept(RNAM.value);
    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);

    return op.Stop();
    }

UINT32 ACTIRecord::GetType()
    {
    return 'ITCA';
    }

STRING ACTIRecord::GetStrType()
    {
    return "ACTI";
    }

SINT32 ACTIRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case 'XXXX':
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
            case 'DIDE':
                EDID.Read(buffer, subSize, curPos);
                break;
            case 'DNBO':
                OBND.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case 'BDOM':
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case 'TDOM':
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case 'SDOM':
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'TSED':
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize, curPos);
                break;
            case 'DTSD':
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize, curPos);
                break;
            case 'LDMD':
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, curPos);
                break;
            case 'TDMD':
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, curPos);
                break;
            case 'FTSD':
                //Marks end of a destruction stage
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANV':
                VNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANW':
                WNAM.Read(buffer, subSize, curPos);
                break;
            case 'OTAX':
                XATO.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ACTI: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 ACTIRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    Destructable.Unload();
    SNAM.Unload();
    VNAM.Unload();
    INAM.Unload();
    RNAM.Unload();
    WNAM.Unload();
    XATO.Unload();
    return 1;
    }

SINT32 ACTIRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(SCRI);
    Destructable.Write(writer);
    WRITE(SNAM);
    WRITE(VNAM);
    WRITE(INAM);
    WRITE(RNAM);
    WRITE(WNAM);
    WRITE(XATO);
    return -1;
    }

bool ACTIRecord::operator ==(const ACTIRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            SCRI == other.SCRI &&
            SNAM == other.SNAM &&
            VNAM == other.VNAM &&
            INAM == other.INAM &&
            RNAM == other.RNAM &&
            WNAM == other.WNAM &&
            MODL == other.MODL &&
            XATO.equalsi(other.XATO) &&
            Destructable == other.Destructable);
    }

bool ACTIRecord::operator !=(const ACTIRecord &other) const
    {
    return !(*this == other);
    }
}