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
    return (BRUS.value == eNone);
    }

void STATRecord::IsSoundNone(bool value)
    {
    BRUS.value = value ? eNone : eBushA;
    }

bool STATRecord::IsSoundBushA()
    {
    return (BRUS.value == eBushA);
    }

void STATRecord::IsSoundBushA(bool value)
    {
    BRUS.value = value ? eBushA : eNone;
    }

bool STATRecord::IsSoundBushB()
    {
    return (BRUS.value == eBushB);
    }

void STATRecord::IsSoundBushB(bool value)
    {
    BRUS.value = value ? eBushB : eNone;
    }

bool STATRecord::IsSoundBushC()
    {
    return (BRUS.value == eBushC);
    }

void STATRecord::IsSoundBushC(bool value)
    {
    BRUS.value = value ? eBushC : eNone;
    }

bool STATRecord::IsSoundBushD()
    {
    return (BRUS.value == eBushD);
    }

void STATRecord::IsSoundBushD(bool value)
    {
    BRUS.value = value ? eBushD : eNone;
    }

bool STATRecord::IsSoundBushE()
    {
    return (BRUS.value == eBushE);
    }

void STATRecord::IsSoundBushE(bool value)
    {
    BRUS.value = value ? eBushE : eNone;
    }

bool STATRecord::IsSoundBushF()
    {
    return (BRUS.value == eBushF);
    }

void STATRecord::IsSoundBushF(bool value)
    {
    BRUS.value = value ? eBushF : eNone;
    }

bool STATRecord::IsSoundBushG()
    {
    return (BRUS.value == eBushG);
    }

void STATRecord::IsSoundBushG(bool value)
    {
    BRUS.value = value ? eBushG : eNone;
    }

bool STATRecord::IsSoundBushH()
    {
    return (BRUS.value == eBushH);
    }

void STATRecord::IsSoundBushH(bool value)
    {
    BRUS.value = value ? eBushH : eNone;
    }

bool STATRecord::IsSoundBushI()
    {
    return (BRUS.value == eBushI);
    }

void STATRecord::IsSoundBushI(bool value)
    {
    BRUS.value = value ? eBushI : eNone;
    }

bool STATRecord::IsSoundBushJ()
    {
    return (BRUS.value == eBushJ);
    }

void STATRecord::IsSoundBushJ(bool value)
    {
    BRUS.value = value ? eBushJ : eNone;
    }

bool STATRecord::IsSoundType(SINT8 Type)
    {
    return BRUS.value == Type;
    }

void STATRecord::SetSoundType(SINT8 Type)
    {
    BRUS.value = Type;
    }

UINT32 STATRecord::GetType()
    {
    return 'TATS';
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
            case 'SURB':
                BRUS.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  STAT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
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