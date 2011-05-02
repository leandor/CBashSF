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
#include "LTEXRecord.h"
#include <vector>

LTEXRecord::LTEXHNAM::LTEXHNAM():
    types(0),
    friction(0),
    restitution(0)
    {
    //
    }

LTEXRecord::LTEXHNAM::~LTEXHNAM()
    {
    //
    }

bool LTEXRecord::LTEXHNAM::operator ==(const LTEXHNAM &other) const
    {
    return (types == other.types &&
            friction == other.friction &&
            restitution == other.restitution);
    }
bool LTEXRecord::LTEXHNAM::operator !=(const LTEXHNAM &other) const
    {
    return !(*this == other);
    }

LTEXRecord::LTEXRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LTEXRecord::LTEXRecord(LTEXRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    ICON = srcRecord->ICON;
    HNAM = srcRecord->HNAM;
    SNAM = srcRecord->SNAM;

    GNAM.resize(srcRecord->GNAM.size());
    for(UINT32 x = 0; x < srcRecord->GNAM.size(); x++)
        GNAM[x] = srcRecord->GNAM[x];
    return;
    }

LTEXRecord::~LTEXRecord()
    {
    //
    }

bool LTEXRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < GNAM.size(); x++)
        op.Accept(GNAM[x]);

    return op.Stop();
    }

bool LTEXRecord::IsStone()
    {
    HNAM.Load();
    return (HNAM.value.types == eStone);
    }

void LTEXRecord::IsStone(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eStone : eCloth;
    }

bool LTEXRecord::IsCloth()
    {
    HNAM.Load();
    return (HNAM.value.types == eCloth);
    }

void LTEXRecord::IsCloth(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eCloth : eStone;
    }

bool LTEXRecord::IsDirt()
    {
    HNAM.Load();
    return (HNAM.value.types == eDirt);
    }

void LTEXRecord::IsDirt(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eDirt : eStone;
    }

bool LTEXRecord::IsGlass()
    {
    HNAM.Load();
    return (HNAM.value.types == eGlass);
    }

void LTEXRecord::IsGlass(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eGlass : eStone;
    }

bool LTEXRecord::IsGrass()
    {
    HNAM.Load();
    return (HNAM.value.types == eGrass);
    }

void LTEXRecord::IsGrass(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eGrass : eStone;
    }

bool LTEXRecord::IsMetal()
    {
    HNAM.Load();
    return (HNAM.value.types == eMetal);
    }

void LTEXRecord::IsMetal(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eMetal : eStone;
    }

bool LTEXRecord::IsOrganic()
    {
    HNAM.Load();
    return (HNAM.value.types == eOrganic);
    }

void LTEXRecord::IsOrganic(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eOrganic : eStone;
    }

bool LTEXRecord::IsSkin()
    {
    HNAM.Load();
    return (HNAM.value.types == eSkin);
    }

void LTEXRecord::IsSkin(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eSkin : eStone;
    }

bool LTEXRecord::IsWater()
    {
    HNAM.Load();
    return (HNAM.value.types == eWater);
    }

void LTEXRecord::IsWater(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eWater : eStone;
    }

bool LTEXRecord::IsWood()
    {
    HNAM.Load();
    return (HNAM.value.types == eWood);
    }

void LTEXRecord::IsWood(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eWood : eStone;
    }

bool LTEXRecord::IsHeavyStone()
    {
    HNAM.Load();
    return (HNAM.value.types == eHeavyStone);
    }

void LTEXRecord::IsHeavyStone(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eHeavyStone : eStone;
    }

bool LTEXRecord::IsHeavyMetal()
    {
    HNAM.Load();
    return (HNAM.value.types == eHeavyMetal);
    }

void LTEXRecord::IsHeavyMetal(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eHeavyMetal : eStone;
    }

bool LTEXRecord::IsHeavyWood()
    {
    HNAM.Load();
    return (HNAM.value.types == eHeavyWood);
    }

void LTEXRecord::IsHeavyWood(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eHeavyWood : eStone;
    }

bool LTEXRecord::IsChain()
    {
    HNAM.Load();
    return (HNAM.value.types == eChain);
    }

void LTEXRecord::IsChain(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eChain : eStone;
    }

bool LTEXRecord::IsSnow()
    {
    HNAM.Load();
    return (HNAM.value.types == eSnow);
    }

void LTEXRecord::IsSnow(bool value)
    {
    HNAM.Load();
    HNAM.value.types = value ? eSnow : eStone;
    }

bool LTEXRecord::IsType(UINT8 Type)
    {
    HNAM.Load();
    return (HNAM.value.types == Type);
    }

void LTEXRecord::SetType(UINT8 Type)
    {
    HNAM.Load();
    HNAM.value.types = Type;
    }

UINT32 LTEXRecord::GetType()
    {
    return 'XETL';
    }


STRING LTEXRecord::GetStrType()
    {
    return "LTEX";
    }

SINT32 LTEXRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    FORMID curFormID = 0;
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
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANG':
                _readBuffer(&curFormID,buffer,subSize,curPos);
                GNAM.push_back(curFormID);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LTEX: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 LTEXRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    HNAM.Unload();
    SNAM.Unload();
    GNAM.clear();
    return 1;
    }

SINT32 LTEXRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord('DIDE', EDID.value, EDID.GetSize());
    if(ICON.IsLoaded())
        writer.record_write_subrecord('NOCI', ICON.value, ICON.GetSize());
    if(HNAM.IsLoaded())
        writer.record_write_subrecord('MANH', &HNAM.value, HNAM.GetSize());
    if(SNAM.IsLoaded())
        writer.record_write_subrecord('MANS', &SNAM.value, SNAM.GetSize());
    for(UINT32 p = 0; p < GNAM.size(); p++)
        writer.record_write_subrecord('MANG', &GNAM[p], sizeof(UINT32));
    return -1;
    }

bool LTEXRecord::operator ==(const LTEXRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        ICON.equals(other.ICON) &&
        HNAM == other.HNAM &&
        SNAM == other.SNAM &&
        GNAM.size() == other.GNAM.size())
        {
        //Not sure if record order matters on grasses, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < GNAM.size(); ++x)
            if(GNAM[x] != other.GNAM[x])
                return false;
        return true;
        }
    return false;
    }

bool LTEXRecord::operator !=(const LTEXRecord &other) const
    {
    return !(*this == other);
    }