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
#include "PROJRecord.h"

namespace FNV
{
PROJRecord::PROJRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PROJRecord::PROJRecord(PROJRecord *srcRecord):
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
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    if(srcRecord->DEST.IsLoaded())
        {
        DEST.Load();
        DEST->DEST = srcRecord->DEST->DEST;
        DEST->DSTD = srcRecord->DEST->DSTD;
        DEST->DMDL = srcRecord->DEST->DMDL;
        DEST->DMDT = srcRecord->DEST->DMDT;
        DEST->DSTF = srcRecord->DEST->DSTF;
        }
    DATA = srcRecord->DATA;
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    VNAM = srcRecord->VNAM;
    return;
    }

PROJRecord::~PROJRecord()
    {
    //
    }

bool PROJRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(DEST.IsLoaded() && DEST->DSTD.IsLoaded())
        op.Accept(DEST->DSTD->value);
    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);

    return op.Stop();
    }

bool PROJRecord::IsHitscan()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHitscan) != 0;
    }

void PROJRecord::IsHitscan(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHitscan) : (Dummy->flags & ~fIsHitscan);
    }

bool PROJRecord::IsExplosion()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsExplosion) != 0;
    }

void PROJRecord::IsExplosion(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsExplosion) : (Dummy->flags & ~fIsExplosion);
    }

bool PROJRecord::IsAltTrigger()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAltTrigger) != 0;
    }

void PROJRecord::IsAltTrigger(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAltTrigger) : (Dummy->flags & ~fIsAltTrigger);
    }

bool PROJRecord::IsMuzzleFlash()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMuzzleFlash) != 0;
    }

void PROJRecord::IsMuzzleFlash(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsMuzzleFlash) : (Dummy->flags & ~fIsMuzzleFlash);
    }

bool PROJRecord::IsDisableable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDisableable) != 0;
    }

void PROJRecord::IsDisableable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDisableable) : (Dummy->flags & ~fIsDisableable);
    }

bool PROJRecord::IsPickupable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPickupable) != 0;
    }

void PROJRecord::IsPickupable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPickupable) : (Dummy->flags & ~fIsPickupable);
    }

bool PROJRecord::IsSupersonic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSupersonic) != 0;
    }

void PROJRecord::IsSupersonic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsSupersonic) : (Dummy->flags & ~fIsSupersonic);
    }

bool PROJRecord::IsPinsLimbs()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPinsLimbs) != 0;
    }

void PROJRecord::IsPinsLimbs(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPinsLimbs) : (Dummy->flags & ~fIsPinsLimbs);
    }

bool PROJRecord::IsPassSmallTransparent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPassSmallTransparent) != 0;
    }

void PROJRecord::IsPassSmallTransparent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPassSmallTransparent) : (Dummy->flags & ~fIsPassSmallTransparent);
    }

bool PROJRecord::IsDetonates()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDetonates) != 0;
    }

void PROJRecord::IsDetonates(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDetonates) : (Dummy->flags & ~fIsDetonates);
    }

bool PROJRecord::IsRotation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRotation) != 0;
    }

void PROJRecord::IsRotation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRotation) : (Dummy->flags & ~fIsRotation);
    }

bool PROJRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void PROJRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool PROJRecord::IsMissile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMissile);
    }

void PROJRecord::IsMissile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMissile : eDummyDefault;
    }

bool PROJRecord::IsLobber()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLobber);
    }

void PROJRecord::IsLobber(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLobber : eDummyDefault;
    }

bool PROJRecord::IsBeam()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBeam);
    }

void PROJRecord::IsBeam(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBeam : eDummyDefault;
    }

bool PROJRecord::IsFlame()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFlame);
    }

void PROJRecord::IsFlame(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFlame : eDummyDefault;
    }

bool PROJRecord::IsContinuousBeam()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eContinuousBeam);
    }

void PROJRecord::IsContinuousBeam(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eContinuousBeam : eDummyDefault;
    }

bool PROJRecord::IsType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void PROJRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool PROJRecord::IsLoud()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLoud);
    }

void PROJRecord::IsLoud(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLoud : eDummyDefault;
    }

bool PROJRecord::IsNormal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNormal);
    }

void PROJRecord::IsNormal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNormal : eDummyDefault;
    }

bool PROJRecord::IsSilent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSilent);
    }

void PROJRecord::IsSilent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSilent : eDummyDefault;
    }

bool PROJRecord::IsSoundLevelType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void PROJRecord::SetSoundLevelType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 PROJRecord::GetSize(bool forceCalc)
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
            {
            cSize = MODL->MODB.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODS.IsLoaded())
            TotSize += MODL->MODS.GetSize() + 6;
        if(MODL->MODD.IsLoaded())
            TotSize += MODL->MODD.GetSize() + 6;
        }

    if(DEST.IsLoaded())
        {
        if(DEST->DEST.IsLoaded())
            TotSize += DEST->DEST.GetSize() + 6;
        if(DEST->DSTD.IsLoaded())
            TotSize += DEST->DSTD.GetSize() + 6;
        if(DEST->DMDL.IsLoaded())
            {
            cSize = DEST->DMDL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(DEST->DMDT.IsLoaded())
            {
            cSize = DEST->DMDT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(DEST->DSTF.IsLoaded())
            TotSize += DEST->DSTF.GetSize() + 6;
        }

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(NAM1.IsLoaded())
        {
        cSize = NAM1.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM2.IsLoaded())
        {
        cSize = NAM2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(VNAM.IsLoaded())
        TotSize += VNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 PROJRecord::GetType()
    {
    return 'JORP';
    }

STRING PROJRecord::GetStrType()
    {
    return "PROJ";
    }

SINT32 PROJRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                MODL->MODS.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case 'TSED':
                DEST.Load();
                DEST->DEST.Read(buffer, subSize, curPos);
                break;
            case 'DTSD':
                DEST.Load();
                DEST->DSTD.Read(buffer, subSize, curPos);
                break;
            case 'LDMD':
                DEST.Load();
                DEST->DMDL.Read(buffer, subSize, curPos);
                break;
            case 'TDMD':
                DEST.Load();
                DEST->DMDT.Read(buffer, subSize, curPos);
                break;
            case 'FTSD':
                //DEST.Load();
                //DEST->DSTF.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case '1MAN':
                NAM1.Read(buffer, subSize, curPos);
                break;
            case '2MAN':
                NAM2.Read(buffer, subSize, curPos);
                break;
            case 'MANV':
                VNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  PROJ: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 PROJRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    DEST.Unload();
    DATA.Unload();
    NAM1.Unload();
    NAM2.Unload();
    VNAM.Unload();
    return 1;
    }

SINT32 PROJRecord::WriteRecord(_FileHandler &SaveHandler)
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
            SaveHandler.writeSubRecord('BDOM', MODL->MODB.value, MODL->MODB.GetSize());

        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());

        if(MODL->MODS.IsLoaded())
            SaveHandler.writeSubRecord('SDOM', MODL->MODS.value, MODL->MODS.GetSize());

        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', MODL->MODD.value, MODL->MODD.GetSize());

        }

    if(DEST.IsLoaded())
        {
        if(DEST->DEST.IsLoaded())
            SaveHandler.writeSubRecord('TSED', DEST->DEST.value, DEST->DEST.GetSize());

        if(DEST->DSTD.IsLoaded())
            SaveHandler.writeSubRecord('DTSD', DEST->DSTD.value, DEST->DSTD.GetSize());

        if(DEST->DMDL.IsLoaded())
            SaveHandler.writeSubRecord('LDMD', DEST->DMDL.value, DEST->DMDL.GetSize());

        if(DEST->DMDT.IsLoaded())
            SaveHandler.writeSubRecord('TDMD', DEST->DMDT.value, DEST->DMDT.GetSize());

        //if(DEST->DSTF.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('FTSD', DEST->DSTF.value, DEST->DSTF.GetSize());

        }

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(NAM1.IsLoaded())
        SaveHandler.writeSubRecord('1MAN', NAM1.value, NAM1.GetSize());

    if(NAM2.IsLoaded())
        SaveHandler.writeSubRecord('2MAN', NAM2.value, NAM2.GetSize());

    if(VNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANV', VNAM.value, VNAM.GetSize());

    return -1;
    }

bool PROJRecord::operator ==(const PROJRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            DEST == other.DEST &&
            DATA == other.DATA &&
            NAM1.equalsi(other.NAM1) &&
            NAM2 == other.NAM2 &&
            VNAM == other.VNAM);
    }

bool PROJRecord::operator !=(const PROJRecord &other) const
    {
    return !(*this == other);
    }
}