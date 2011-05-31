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
#include "STATRecord.h"

namespace FNV
{
STATRecord::STATRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

STATRecord::STATRecord(STATRecord *srcRecord):
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
    BRUS = srcRecord->BRUS;
    RNAM = srcRecord->RNAM;
    return;
    }

STATRecord::~STATRecord()
    {
    //
    }

bool STATRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(RNAM.IsLoaded())
        op.Accept(RNAM.value);

    return op.Stop();
    }

bool STATRecord::IsSoundNone()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eNone);
    }

void STATRecord::IsSoundNone(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eNone : eBushA;
    }

bool STATRecord::IsSoundBushA()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushA);
    }

void STATRecord::IsSoundBushA(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushA : eNone;
    }

bool STATRecord::IsSoundBushB()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushB);
    }

void STATRecord::IsSoundBushB(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushB : eNone;
    }

bool STATRecord::IsSoundBushC()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushC);
    }

void STATRecord::IsSoundBushC(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushC : eNone;
    }

bool STATRecord::IsSoundBushD()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushD);
    }

void STATRecord::IsSoundBushD(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushD : eNone;
    }

bool STATRecord::IsSoundBushE()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushE);
    }

void STATRecord::IsSoundBushE(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushE : eNone;
    }

bool STATRecord::IsSoundBushF()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushF);
    }

void STATRecord::IsSoundBushF(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushF : eNone;
    }

bool STATRecord::IsSoundBushG()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushG);
    }

void STATRecord::IsSoundBushG(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushG : eNone;
    }

bool STATRecord::IsSoundBushH()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushH);
    }

void STATRecord::IsSoundBushH(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushH : eNone;
    }

bool STATRecord::IsSoundBushI()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushI);
    }

void STATRecord::IsSoundBushI(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushI : eNone;
    }

bool STATRecord::IsSoundBushJ()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushJ);
    }

void STATRecord::IsSoundBushJ(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushJ : eNone;
    }

bool STATRecord::IsSoundType(SINT8 Type)
    {
    if(!BRUS.IsLoaded()) return false;
    return *BRUS.value == Type;
    }

void STATRecord::SetSoundType(SINT8 Type)
    {
    BRUS.Load();
    *BRUS.value = Type;
    }

UINT32 STATRecord::GetType()
    {
    return REV32(STAT);
    }

STRING STATRecord::GetStrType()
    {
    return "STAT";
    }

SINT32 STATRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(BRUS):
                BRUS.Read(buffer, subSize, curPos);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  STAT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 STATRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    BRUS.Unload();
    RNAM.Unload();
    return 1;
    }

SINT32 STATRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(BRUS);
    WRITE(RNAM);
    return -1;
    }

bool STATRecord::operator ==(const STATRecord &other) const
    {
    return (OBND == other.OBND &&
            BRUS == other.BRUS &&
            RNAM == other.RNAM &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL);
    }

bool STATRecord::operator !=(const STATRecord &other) const
    {
    return !(*this == other);
    }
}