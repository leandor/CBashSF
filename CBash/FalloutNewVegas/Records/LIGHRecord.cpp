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
#include "LIGHRecord.h"

namespace FNV
{
LIGHRecord::LIGHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

LIGHRecord::LIGHRecord(LIGHRecord *srcRecord):
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

    SCRI = srcRecord->SCRI;
    FULL = srcRecord->FULL;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    DATA = srcRecord->DATA;
    FNAM = srcRecord->FNAM;
    SNAM = srcRecord->SNAM;
    return;
    }

LIGHRecord::~LIGHRecord()
    {
    //
    }

bool LIGHRecord::VisitFormIDs(FormIDOp &op)
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
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);

    return op.Stop();
    }

bool LIGHRecord::IsDynamic()
    {
    return (DATA.value.flags & fIsDynamic) != 0;
    }

void LIGHRecord::IsDynamic(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsDynamic) : (DATA.value.flags & ~fIsDynamic);
    }

bool LIGHRecord::IsCanTake()
    {
    return (DATA.value.flags & fIsCanTake) != 0;
    }

void LIGHRecord::IsCanTake(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsCanTake) : (DATA.value.flags & ~fIsCanTake);
    }

bool LIGHRecord::IsTakeable()
    {
    return (DATA.value.flags & fIsCanTake) != 0;
    }

void LIGHRecord::IsTakeable(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsCanTake) : (DATA.value.flags & ~fIsCanTake);
    }

bool LIGHRecord::IsNegative()
    {
    return (DATA.value.flags & fIsNegative) != 0;
    }

void LIGHRecord::IsNegative(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNegative) : (DATA.value.flags & ~fIsNegative);
    }

bool LIGHRecord::IsFlickers()
    {
    return (DATA.value.flags & fIsFlickers) != 0;
    }

void LIGHRecord::IsFlickers(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsFlickers) : (DATA.value.flags & ~fIsFlickers);
    }

bool LIGHRecord::IsOffByDefault()
    {
    return (DATA.value.flags & fIsOffByDefault) != 0;
    }

void LIGHRecord::IsOffByDefault(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsOffByDefault) : (DATA.value.flags & ~fIsOffByDefault);
    }

bool LIGHRecord::IsFlickerSlow()
    {
    return (DATA.value.flags & fIsFlickerSlow) != 0;
    }

void LIGHRecord::IsFlickerSlow(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsFlickerSlow) : (DATA.value.flags & ~fIsFlickerSlow);
    }

bool LIGHRecord::IsPulse()
    {
    return (DATA.value.flags & fIsPulse) != 0;
    }

void LIGHRecord::IsPulse(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsPulse) : (DATA.value.flags & ~fIsPulse);
    }

bool LIGHRecord::IsPulseSlow()
    {
    return (DATA.value.flags & fIsPulseSlow) != 0;
    }

void LIGHRecord::IsPulseSlow(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsPulseSlow) : (DATA.value.flags & ~fIsPulseSlow);
    }

bool LIGHRecord::IsSpotLight()
    {
    return (DATA.value.flags & fIsSpotLight) != 0;
    }

void LIGHRecord::IsSpotLight(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsSpotLight) : (DATA.value.flags & ~fIsSpotLight);
    }

bool LIGHRecord::IsSpotShadow()
    {
    return (DATA.value.flags & fIsSpotShadow) != 0;
    }

void LIGHRecord::IsSpotShadow(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsSpotShadow) : (DATA.value.flags & ~fIsSpotShadow);
    }

bool LIGHRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void LIGHRecord::SetFlagMask(UINT32 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 LIGHRecord::GetType()
    {
    return 'HGIL';
    }

STRING LIGHRecord::GetStrType()
    {
    return "LIGH";
    }

SINT32 LIGHRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LIGH: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 LIGHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    SCRI.Unload();
    FULL.Unload();
    ICON.Unload();
    MICO.Unload();
    DATA.Unload();
    FNAM.Unload();
    SNAM.Unload();
    return 1;
    }

SINT32 LIGHRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    WRITE(EDID);
    WRITE(OBND);

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

    WRITE(SCRI);
    WRITE(FULL);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(DATA);
    WRITE(FNAM);
    WRITE(SNAM);

    return -1;
    }

bool LIGHRecord::operator ==(const LIGHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            MODL == other.MODL &&
            SCRI == other.SCRI &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            DATA == other.DATA &&
            FNAM == other.FNAM &&
            SNAM == other.SNAM);
    }

bool LIGHRecord::operator !=(const LIGHRecord &other) const
    {
    return !(*this == other);
    }
}