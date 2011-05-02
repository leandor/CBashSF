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
#include "EXPLRecord.h"

namespace FNV
{
EXPLRecord::EXPLRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

EXPLRecord::EXPLRecord(EXPLRecord *srcRecord):
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

    EITM = srcRecord->EITM;
    MNAM = srcRecord->MNAM;
    DATA = srcRecord->DATA;
    INAM = srcRecord->INAM;
    return;
    }

EXPLRecord::~EXPLRecord()
    {
    //
    }

bool EXPLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(EITM.IsLoaded())
        op.Accept(EITM->value);
    if(MNAM.IsLoaded())
        op.Accept(MNAM->value);
    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);

    return op.Stop();
    }

bool EXPLRecord::IsUnknown1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown1) != 0;
    }

void EXPLRecord::IsUnknown1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUnknown1) : (Dummy->flags & ~fIsUnknown1);
    }

bool EXPLRecord::IsAlwaysUsesWorldOrientation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAlwaysUsesWorldOrientation) != 0;
    }

void EXPLRecord::IsAlwaysUsesWorldOrientation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAlwaysUsesWorldOrientation) : (Dummy->flags & ~fIsAlwaysUsesWorldOrientation);
    }

bool EXPLRecord::IsAlwaysKnockDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAlwaysKnockDown) != 0;
    }

void EXPLRecord::IsAlwaysKnockDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAlwaysKnockDown) : (Dummy->flags & ~fIsAlwaysKnockDown);
    }

bool EXPLRecord::IsFormulaKnockDown()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFormulaKnockDown) != 0;
    }

void EXPLRecord::IsFormulaKnockDown(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsFormulaKnockDown) : (Dummy->flags & ~fIsFormulaKnockDown);
    }

bool EXPLRecord::IsIgnoreLOS()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIgnoreLOS) != 0;
    }

void EXPLRecord::IsIgnoreLOS(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIgnoreLOS) : (Dummy->flags & ~fIsIgnoreLOS);
    }

bool EXPLRecord::IsPushExplosionSourceRefOnly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPushExplosionSourceRefOnly) != 0;
    }

void EXPLRecord::IsPushExplosionSourceRefOnly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPushExplosionSourceRefOnly) : (Dummy->flags & ~fIsPushExplosionSourceRefOnly);
    }

bool EXPLRecord::IsIgnoreImageSpaceSwap()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIgnoreImageSpaceSwap) != 0;
    }

void EXPLRecord::IsIgnoreImageSpaceSwap(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIgnoreImageSpaceSwap) : (Dummy->flags & ~fIsIgnoreImageSpaceSwap);
    }

bool EXPLRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void EXPLRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool EXPLRecord::IsLoud()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLoud);
    }

void EXPLRecord::IsLoud(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLoud : eDummyDefault;
    }

bool EXPLRecord::IsNormal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNormal);
    }

void EXPLRecord::IsNormal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNormal : eDummyDefault;
    }

bool EXPLRecord::IsSilent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSilent);
    }

void EXPLRecord::IsSilent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSilent : eDummyDefault;
    }

bool EXPLRecord::IsSoundLevelType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void EXPLRecord::SetSoundLevelType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 EXPLRecord::GetType()
    {
    return 'LPXE';
    }

STRING EXPLRecord::GetStrType()
    {
    return "EXPL";
    }

SINT32 EXPLRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'MTIE':
                EITM.Read(buffer, subSize, curPos);
                break;
            case 'MANM':
                MNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  EXPL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 EXPLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    EITM.Unload();
    MNAM.Unload();
    DATA.Unload();
    INAM.Unload();
    return 1;
    }

SINT32 EXPLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);

    MODL.Write(writer);

    WRITE(EITM);
    WRITE(MNAM);
    WRITE(DATA);
    WRITE(INAM);

    return -1;
    }

bool EXPLRecord::operator ==(const EXPLRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            EITM == other.EITM &&
            MNAM == other.MNAM &&
            DATA == other.DATA &&
            INAM == other.INAM);
    }

bool EXPLRecord::operator !=(const EXPLRecord &other) const
    {
    return !(*this == other);
    }
}