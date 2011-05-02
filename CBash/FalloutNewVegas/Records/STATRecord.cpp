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
        op.Accept(RNAM->value);

    return op.Stop();
    }

bool STATRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void STATRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool STATRecord::IsBushA()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushA);
    }

void STATRecord::IsBushA(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushA : eDummyDefault;
    }

bool STATRecord::IsBushB()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushB);
    }

void STATRecord::IsBushB(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushB : eDummyDefault;
    }

bool STATRecord::IsBushC()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushC);
    }

void STATRecord::IsBushC(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushC : eDummyDefault;
    }

bool STATRecord::IsBushD()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushD);
    }

void STATRecord::IsBushD(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushD : eDummyDefault;
    }

bool STATRecord::IsBushE()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushE);
    }

void STATRecord::IsBushE(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushE : eDummyDefault;
    }

bool STATRecord::IsBushF()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushF);
    }

void STATRecord::IsBushF(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushF : eDummyDefault;
    }

bool STATRecord::IsBushG()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushG);
    }

void STATRecord::IsBushG(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushG : eDummyDefault;
    }

bool STATRecord::IsBushH()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushH);
    }

void STATRecord::IsBushH(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushH : eDummyDefault;
    }

bool STATRecord::IsBushI()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushI);
    }

void STATRecord::IsBushI(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushI : eDummyDefault;
    }

bool STATRecord::IsBushJ()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBushJ);
    }

void STATRecord::IsBushJ(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBushJ : eDummyDefault;
    }

bool STATRecord::IsType(SINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void STATRecord::SetType(SINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
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
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            MODL == other.MODL &&
            BRUS == other.BRUS &&
            RNAM == other.RNAM);
    }

bool STATRecord::operator !=(const STATRecord &other) const
    {
    return !(*this == other);
    }
}