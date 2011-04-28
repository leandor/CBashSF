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

    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->Textures.MODS.resize(srcRecord->MODL->Textures.MODS.size());
        for(UINT32 x = 0; x < srcRecord->MODL->Textures.MODS.size(); x++)
            {
            MODL->Textures.MODS[x] = new FNVMODS;
            *MODL->Textures.MODS[x] = *srcRecord->MODL->Textures.MODS[x];
            }
        MODL->MODD = srcRecord->MODL->MODD;
        }

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
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void STATRecord::SetType(SINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 STATRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(OBND.IsLoaded())
        TotSize += OBND.GetSize() + 6;

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            {
            cSize = MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODB.IsLoaded())
            TotSize += MODL->MODB.GetSize() + 6;
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->Textures.IsLoaded())
            {
            cSize = MODL->Textures.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODD.IsLoaded())
            TotSize += MODL->MODD.GetSize() + 6;
        }

    if(BRUS.IsLoaded())
        TotSize += BRUS.GetSize() + 6;

    if(RNAM.IsLoaded())
        TotSize += RNAM.GetSize() + 6;

    return TotSize;
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

SINT32 STATRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());
        if(MODL->Textures.IsLoaded())
            {
            SaveHandler.writeSubRecordHeader('SDOM', MODL->Textures.GetSize());
            UINT32 cSize = MODL->Textures.MODS.size();
            SaveHandler.write(&cSize, 4);
            for(UINT32 p = 0; p < MODL->Textures.MODS.size(); ++p)
                {
                if(MODL->Textures.MODS[p]->name != NULL)
                    {
                    cSize = (UINT32)strlen(MODL->Textures.MODS[p]->name);
                    SaveHandler.write(&cSize, 4);
                    SaveHandler.write(MODL->Textures.MODS[p]->name, cSize);
                    }                

                SaveHandler.write(&MODL->Textures.MODS[p]->texture, 4);
                SaveHandler.write(&MODL->Textures.MODS[p]->index, 4);
                }
           }
        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', &MODL->MODD.value, MODL->MODD.GetSize());
        }

    if(BRUS.IsLoaded())
        SaveHandler.writeSubRecord('SURB', BRUS.value, BRUS.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

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