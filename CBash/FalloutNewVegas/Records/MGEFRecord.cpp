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
#include "MGEFRecord.h"

namespace FNV
{
MGEFRecord::MGEFRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

MGEFRecord::MGEFRecord(MGEFRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    DESC = srcRecord->DESC;
    if(srcRecord->ICON.IsLoaded())
        {
        ICON.Load();
        ICON->ICON = srcRecord->ICON->ICON;
        ICON->MICO = srcRecord->ICON->MICO;
        }
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    DATA = srcRecord->DATA;
    return;
    }

MGEFRecord::~MGEFRecord()
    {
    //
    }

bool MGEFRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);

    return op.Stop();
    }

bool MGEFRecord::IsHostile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHostile) != 0;
    }

void MGEFRecord::IsHostile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHostile;
    else
        Dummy->flags &= ~fIsHostile;
    }

bool MGEFRecord::IsRecover()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRecover) != 0;
    }

void MGEFRecord::IsRecover(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRecover;
    else
        Dummy->flags &= ~fIsRecover;
    }

bool MGEFRecord::IsDetrimental()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDetrimental) != 0;
    }

void MGEFRecord::IsDetrimental(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDetrimental;
    else
        Dummy->flags &= ~fIsDetrimental;
    }

bool MGEFRecord::IsSelf()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSelf) != 0;
    }

void MGEFRecord::IsSelf(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsSelf;
    else
        Dummy->flags &= ~fIsSelf;
    }

bool MGEFRecord::IsTouch()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTouch) != 0;
    }

void MGEFRecord::IsTouch(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsTouch;
    else
        Dummy->flags &= ~fIsTouch;
    }

bool MGEFRecord::IsTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTarget) != 0;
    }

void MGEFRecord::IsTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsTarget;
    else
        Dummy->flags &= ~fIsTarget;
    }

bool MGEFRecord::IsNoDuration()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoDuration) != 0;
    }

void MGEFRecord::IsNoDuration(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoDuration;
    else
        Dummy->flags &= ~fIsNoDuration;
    }

bool MGEFRecord::IsNoMagnitude()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoMagnitude) != 0;
    }

void MGEFRecord::IsNoMagnitude(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoMagnitude;
    else
        Dummy->flags &= ~fIsNoMagnitude;
    }

bool MGEFRecord::IsNoArea()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoArea) != 0;
    }

void MGEFRecord::IsNoArea(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoArea;
    else
        Dummy->flags &= ~fIsNoArea;
    }

bool MGEFRecord::IsFXPersist()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFXPersist) != 0;
    }

void MGEFRecord::IsFXPersist(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsFXPersist;
    else
        Dummy->flags &= ~fIsFXPersist;
    }

bool MGEFRecord::IsGoryVisuals()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsGoryVisuals) != 0;
    }

void MGEFRecord::IsGoryVisuals(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsGoryVisuals;
    else
        Dummy->flags &= ~fIsGoryVisuals;
    }

bool MGEFRecord::IsDisplayNameOnly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDisplayNameOnly) != 0;
    }

void MGEFRecord::IsDisplayNameOnly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDisplayNameOnly;
    else
        Dummy->flags &= ~fIsDisplayNameOnly;
    }

bool MGEFRecord::IsRadioBroadcast()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRadioBroadcast) != 0;
    }

void MGEFRecord::IsRadioBroadcast(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRadioBroadcast;
    else
        Dummy->flags &= ~fIsRadioBroadcast;
    }

bool MGEFRecord::IsUseSkill()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseSkill) != 0;
    }

void MGEFRecord::IsUseSkill(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseSkill;
    else
        Dummy->flags &= ~fIsUseSkill;
    }

bool MGEFRecord::IsUseAttr()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseAttr) != 0;
    }

void MGEFRecord::IsUseAttr(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUseAttr;
    else
        Dummy->flags &= ~fIsUseAttr;
    }

bool MGEFRecord::IsPainless()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPainless) != 0;
    }

void MGEFRecord::IsPainless(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPainless;
    else
        Dummy->flags &= ~fIsPainless;
    }

bool MGEFRecord::IsSprayType()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSprayType) != 0;
    }

void MGEFRecord::IsSprayType(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsSprayType;
    else
        Dummy->flags &= ~fIsSprayType;
    }

bool MGEFRecord::IsBoltType()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBoltType) != 0;
    }

void MGEFRecord::IsBoltType(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsBoltType;
    else
        Dummy->flags &= ~fIsBoltType;
    }

bool MGEFRecord::IsFogType()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFogType) != 0;
    }

void MGEFRecord::IsFogType(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsFogType;
    else
        Dummy->flags &= ~fIsFogType;
    }

bool MGEFRecord::IsNoHitEffect()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoHitEffect) != 0;
    }

void MGEFRecord::IsNoHitEffect(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoHitEffect;
    else
        Dummy->flags &= ~fIsNoHitEffect;
    }

bool MGEFRecord::IsPersistOnDeath()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPersistOnDeath) != 0;
    }

void MGEFRecord::IsPersistOnDeath(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPersistOnDeath;
    else
        Dummy->flags &= ~fIsPersistOnDeath;
    }

bool MGEFRecord::IsUnknown1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown1) != 0;
    }

void MGEFRecord::IsUnknown1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown1;
    else
        Dummy->flags &= ~fIsUnknown1;
    }

bool MGEFRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void MGEFRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool MGEFRecord::IsValueModifier()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eValueModifier);
    }

void MGEFRecord::IsValueModifier(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eValueModifier;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsScript()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eScript);
    }

void MGEFRecord::IsScript(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eScript;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsDispel()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDispel);
    }

void MGEFRecord::IsDispel(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDispel;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsCureDisease()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCureDisease);
    }

void MGEFRecord::IsCureDisease(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCureDisease;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsInvisibility()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eInvisibility);
    }

void MGEFRecord::IsInvisibility(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eInvisibility;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsChameleon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eChameleon);
    }

void MGEFRecord::IsChameleon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eChameleon;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsLight()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLight);
    }

void MGEFRecord::IsLight(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eLight;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsLock()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLock);
    }

void MGEFRecord::IsLock(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eLock;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsOpen()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eOpen);
    }

void MGEFRecord::IsOpen(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eOpen;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsBoundItem()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBoundItem);
    }

void MGEFRecord::IsBoundItem(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eBoundItem;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsSummonCreature()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSummonCreature);
    }

void MGEFRecord::IsSummonCreature(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eSummonCreature;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsParalysis()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eParalysis);
    }

void MGEFRecord::IsParalysis(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eParalysis;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsCureParalysis()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCureParalysis);
    }

void MGEFRecord::IsCureParalysis(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCureParalysis;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsCureAddiction()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCureAddiction);
    }

void MGEFRecord::IsCureAddiction(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCureAddiction;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsCurePoison()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCurePoison);
    }

void MGEFRecord::IsCurePoison(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCurePoison;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsConcussion()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eConcussion);
    }

void MGEFRecord::IsConcussion(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eConcussion;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsValueAndParts()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eValueAndParts);
    }

void MGEFRecord::IsValueAndParts(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eValueAndParts;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsLimbCondition()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLimbCondition);
    }

void MGEFRecord::IsLimbCondition(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eLimbCondition;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsTurbo()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTurbo);
    }

void MGEFRecord::IsTurbo(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eTurbo;
    else
        Dummy->flags = eDummyDefault;
    }

bool MGEFRecord::IsType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void MGEFRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 MGEFRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-16];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            {
            cSize = ICON->ICON.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(ICON->MICO.IsLoaded())
            {
            cSize = ICON->MICO.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
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

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

UINT32 MGEFRecord::GetType()
    {
    return 'FEGM';
    }

STRING MGEFRecord::GetStrType()
    {
    return "MGEF";
    }

SINT32 MGEFRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'CSED':
                DESC.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Load();
                ICON->ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                ICON.Load();
                ICON->MICO.Read(buffer, subSize, curPos);
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
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  MGEF: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 MGEFRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    MODL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 MGEFRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord('CSED', DESC.value, DESC.GetSize());

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            SaveHandler.writeSubRecord('NOCI', ICON->ICON.value, ICON->ICON.GetSize());

        if(ICON->MICO.IsLoaded())
            SaveHandler.writeSubRecord('OCIM', ICON->MICO.value, ICON->MICO.GetSize());

        }

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

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    return -1;
    }

bool MGEFRecord::operator ==(const MGEFRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON == other.ICON &&
            MODL == other.MODL &&
            DATA == other.DATA);
    }

bool MGEFRecord::operator !=(const MGEFRecord &other) const
    {
    return !(*this == other);
    }
}