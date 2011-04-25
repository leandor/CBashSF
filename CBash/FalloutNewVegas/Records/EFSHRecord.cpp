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
#include "EFSHRecord.h"

namespace FNV
{
EFSHRecord::EFSHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

EFSHRecord::EFSHRecord(EFSHRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    ICO2 = srcRecord->ICO2;
    NAM7 = srcRecord->NAM7;
    DATA = srcRecord->DATA;
    return;
    }

EFSHRecord::~EFSHRecord()
    {
    //
    }

bool EFSHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);

    return op.Stop();
    }



bool EFSHRecord::IsNoMemShader()
    {
    return (DATA.value.flags & fIsNoMemShader) != 0;
    }

void EFSHRecord::IsNoMemShader(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoMemShader) : (DATA.value.flags & ~fIsNoMemShader);
    }

bool EFSHRecord::IsNoMembraneShader()
    {
    return (DATA.value.flags & fIsNoMemShader) != 0;
    }

void EFSHRecord::IsNoMembraneShader(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoMemShader) : (DATA.value.flags & ~fIsNoMemShader);
    }

bool EFSHRecord::IsNoPartShader()
    {
    return (DATA.value.flags & fIsNoPartShader) != 0;
    }

void EFSHRecord::IsNoPartShader(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoPartShader) : (DATA.value.flags & ~fIsNoPartShader);
    }

bool EFSHRecord::IsNoParticleShader()
    {
    return (DATA.value.flags & fIsNoPartShader) != 0;
    }

void EFSHRecord::IsNoParticleShader(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoPartShader) : (DATA.value.flags & ~fIsNoPartShader);
    }

bool EFSHRecord::IsEdgeInverse()
    {
    return (DATA.value.flags & fIsEdgeInverse) != 0;
    }

void EFSHRecord::IsEdgeInverse(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsEdgeInverse) : (DATA.value.flags & ~fIsEdgeInverse);
    }

bool EFSHRecord::IsEdgeEffectInverse()
    {
    return (DATA.value.flags & fIsEdgeInverse) != 0;
    }

void EFSHRecord::IsEdgeEffectInverse(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsEdgeInverse) : (DATA.value.flags & ~fIsEdgeInverse);
    }

bool EFSHRecord::IsMemSkinOnly()
    {
    return (DATA.value.flags & fIsMemSkinOnly) != 0;
    }

void EFSHRecord::IsMemSkinOnly(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsMemSkinOnly) : (DATA.value.flags & ~fIsMemSkinOnly);
    }

bool EFSHRecord::IsMembraneShaderSkinOnly()
    {
    return (DATA.value.flags & fIsMemSkinOnly) != 0;
    }

void EFSHRecord::IsMembraneShaderSkinOnly(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsMemSkinOnly) : (DATA.value.flags & ~fIsMemSkinOnly);
    }

bool EFSHRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void EFSHRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 EFSHRecord::GetSize(bool forceCalc)
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

    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ICO2.IsLoaded())
        {
        cSize = ICO2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM7.IsLoaded())
        {
        cSize = NAM7.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

UINT32 EFSHRecord::GetType()
    {
    return 'HSFE';
    }

STRING EFSHRecord::GetStrType()
    {
    return "EFSH";
    }

SINT32 EFSHRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case '2OCI':
                ICO2.Read(buffer, subSize, curPos);
                break;
            case '7MAN':
                NAM7.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  EFSH: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 EFSHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    ICO2.Unload();
    NAM7.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 EFSHRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', ICON.value, ICON.GetSize());

    if(ICO2.IsLoaded())
        SaveHandler.writeSubRecord('2OCI', ICO2.value, ICO2.GetSize());

    if(NAM7.IsLoaded())
        SaveHandler.writeSubRecord('7MAN', NAM7.value, NAM7.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    return -1;
    }

bool EFSHRecord::operator ==(const EFSHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            ICO2.equalsi(other.ICO2) &&
            NAM7.equalsi(other.NAM7) &&
            DATA == other.DATA);
    }

bool EFSHRecord::operator !=(const EFSHRecord &other) const
    {
    return !(*this == other);
    }
}