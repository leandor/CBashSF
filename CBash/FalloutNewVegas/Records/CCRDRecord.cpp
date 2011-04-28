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
#include "CCRDRecord.h"

namespace FNV
{
CCRDRecord::CCRDRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CCRDRecord::CCRDRecord(CCRDRecord *srcRecord):
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

    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SCRI = srcRecord->SCRI;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    if(srcRecord->TX00.IsLoaded())
        {
        TX00.Load();
        TX00->TX00 = srcRecord->TX00->TX00;
        TX00->TX01 = srcRecord->TX00->TX01;
        }
    if(srcRecord->INTV.IsLoaded())
        {
        INTV.Load();
        INTV->INTV = srcRecord->INTV->INTV;
        }
    INTV = srcRecord->INTV;
    DATA = srcRecord->DATA;
    return;
    }

CCRDRecord::~CCRDRecord()
    {
    //
    }

bool CCRDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);

    return op.Stop();
    }


bool CCRDRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void CCRDRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool CCRDRecord::IsHearts()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHearts);
    }

void CCRDRecord::IsHearts(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHearts : eDummyDefault;
    }

bool CCRDRecord::IsSpades()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSpades);
    }

void CCRDRecord::IsSpades(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSpades : eDummyDefault;
    }

bool CCRDRecord::IsDiamonds()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDiamonds);
    }

void CCRDRecord::IsDiamonds(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDiamonds : eDummyDefault;
    }

bool CCRDRecord::IsClubs()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eClubs);
    }

void CCRDRecord::IsClubs(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eClubs : eDummyDefault;
    }

bool CCRDRecord::IsJoker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eJoker);
    }

void CCRDRecord::IsJoker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eJoker : eDummyDefault;
    }

bool CCRDRecord::IsType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CCRDRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CCRDRecord::GetSize(bool forceCalc)
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

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

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

    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MICO.IsLoaded())
        {
        cSize = MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;

    if(YNAM.IsLoaded())
        TotSize += YNAM.GetSize() + 6;

    if(ZNAM.IsLoaded())
        TotSize += ZNAM.GetSize() + 6;

    if(TX00.IsLoaded())
        {
        if(TX00->TX00.IsLoaded())
            {
            cSize = TX00->TX00.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(TX00->TX01.IsLoaded())
            {
            cSize = TX00->TX01.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(INTV.IsLoaded())
        {
        if(INTV->INTV.IsLoaded())
            TotSize += INTV->INTV.GetSize() + 6;
        }

    if(INTV.IsLoaded())
        TotSize += INTV.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

UINT32 CCRDRecord::GetType()
    {
    return 'DRCC';
    }

STRING CCRDRecord::GetStrType()
    {
    return "CCRD";
    }

SINT32 CCRDRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case '00XT':
                TX00.Load();
                TX00->TX00.Read(buffer, subSize, curPos);
                break;
            case '10XT':
                TX00.Load();
                TX00->TX01.Read(buffer, subSize, curPos);
                break;
            case 'VTNI':
                INTV.Load();
                INTV->INTV.Read(buffer, subSize, curPos);
                break;
            case 'VTNI':
                INTV.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CCRD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CCRDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    SCRI.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    TX00.Unload();
    INTV.Unload();
    INTV.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 CCRDRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

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

    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', ICON.value, ICON.GetSize());

    if(MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MICO.value, MICO.GetSize());

    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord('IRCS', SCRI.value, SCRI.GetSize());

    if(YNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANY', YNAM.value, YNAM.GetSize());

    if(ZNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANZ', ZNAM.value, ZNAM.GetSize());

    if(TX00.IsLoaded())
        {
        if(TX00->TX00.IsLoaded())
            SaveHandler.writeSubRecord('00XT', TX00->TX00.value, TX00->TX00.GetSize());

        if(TX00->TX01.IsLoaded())
            SaveHandler.writeSubRecord('10XT', TX00->TX01.value, TX00->TX01.GetSize());

        }

    if(INTV.IsLoaded())
        {
        if(INTV->INTV.IsLoaded())
            SaveHandler.writeSubRecord('VTNI', INTV->INTV.value, INTV->INTV.GetSize());

        }

    if(INTV.IsLoaded())
        SaveHandler.writeSubRecord('VTNI', INTV.value, INTV.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    return -1;
    }

bool CCRDRecord::operator ==(const CCRDRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            SCRI == other.SCRI &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            TX00 == other.TX00 &&
            INTV == other.INTV &&
            INTV == other.INTV &&
            DATA == other.DATA);
    }

bool CCRDRecord::operator !=(const CCRDRecord &other) const
    {
    return !(*this == other);
    }
}