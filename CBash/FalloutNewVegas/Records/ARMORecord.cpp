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
#include "ARMORecord.h"

namespace FNV
{
ARMORecord::ARMORecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ARMORecord::ARMORecord(ARMORecord *srcRecord):
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
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    SCRI = srcRecord->SCRI;
    EITM = srcRecord->EITM;
    BMDT = srcRecord->BMDT;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    if(srcRecord->MOD2.IsLoaded())
        {
        MOD2.Load();
        MOD2->MOD2 = srcRecord->MOD2->MOD2;
        MOD2->MO2T = srcRecord->MOD2->MO2T;
        MOD2->MO2S = srcRecord->MOD2->MO2S;
        }
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    if(srcRecord->MOD3.IsLoaded())
        {
        MOD3.Load();
        MOD3->MOD3 = srcRecord->MOD3->MOD3;
        MOD3->MO3T = srcRecord->MOD3->MO3T;
        MOD3->MO3S = srcRecord->MOD3->MO3S;
        MOD3->MOSD = srcRecord->MOD3->MOSD;
        }
    if(srcRecord->MOD4.IsLoaded())
        {
        MOD4.Load();
        MOD4->MOD4 = srcRecord->MOD4->MOD4;
        MOD4->MO4T = srcRecord->MOD4->MO4T;
        MOD4->MO4S = srcRecord->MOD4->MO4S;
        }
    ICO2 = srcRecord->ICO2;
    MIC2 = srcRecord->MIC2;
    BMCT = srcRecord->BMCT;
    REPL = srcRecord->REPL;
    BIPL = srcRecord->BIPL;
    ETYP = srcRecord->ETYP;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    DATA = srcRecord->DATA;
    DNAM = srcRecord->DNAM;
    BNAM = srcRecord->BNAM;
    SNAM = srcRecord->SNAM;
    TNAM = srcRecord->TNAM;
    return;
    }

ARMORecord::~ARMORecord()
    {
    //
    }

bool ARMORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    if(EITM.IsLoaded())
        op.Accept(EITM->value);
    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(MOD2.IsLoaded() && MOD2->MO2S.IsLoaded())
        op.Accept(MOD2->MO2S->value);
    if(MOD3.IsLoaded() && MOD3->MO3S.IsLoaded())
        op.Accept(MOD3->MO3S->value);
    if(MOD4.IsLoaded() && MOD4->MO4S.IsLoaded())
        op.Accept(MOD4->MO4S->value);
    if(REPL.IsLoaded())
        op.Accept(REPL->value);
    if(BIPL.IsLoaded())
        op.Accept(BIPL->value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);
    //if(SNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(SNAM->value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM->value);

    return op.Stop();
    }

bool ARMORecord::IsHead()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHead) != 0;
    }

void ARMORecord::IsHead(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHead;
    else
        Dummy->flags &= ~fIsHead;
    }

bool ARMORecord::IsHair()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHair) != 0;
    }

void ARMORecord::IsHair(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHair;
    else
        Dummy->flags &= ~fIsHair;
    }

bool ARMORecord::IsUpperBody()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUpperBody) != 0;
    }

void ARMORecord::IsUpperBody(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUpperBody;
    else
        Dummy->flags &= ~fIsUpperBody;
    }

bool ARMORecord::IsLeftHand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsLeftHand) != 0;
    }

void ARMORecord::IsLeftHand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsLeftHand;
    else
        Dummy->flags &= ~fIsLeftHand;
    }

bool ARMORecord::IsRightHand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRightHand) != 0;
    }

void ARMORecord::IsRightHand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRightHand;
    else
        Dummy->flags &= ~fIsRightHand;
    }

bool ARMORecord::IsWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsWeapon) != 0;
    }

void ARMORecord::IsWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsWeapon;
    else
        Dummy->flags &= ~fIsWeapon;
    }

bool ARMORecord::IsPipBoy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPipBoy) != 0;
    }

void ARMORecord::IsPipBoy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPipBoy;
    else
        Dummy->flags &= ~fIsPipBoy;
    }

bool ARMORecord::IsBackpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBackpack) != 0;
    }

void ARMORecord::IsBackpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsBackpack;
    else
        Dummy->flags &= ~fIsBackpack;
    }

bool ARMORecord::IsNecklace()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNecklace) != 0;
    }

void ARMORecord::IsNecklace(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNecklace;
    else
        Dummy->flags &= ~fIsNecklace;
    }

bool ARMORecord::IsHeadband()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHeadband) != 0;
    }

void ARMORecord::IsHeadband(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHeadband;
    else
        Dummy->flags &= ~fIsHeadband;
    }

bool ARMORecord::IsHat()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHat) != 0;
    }

void ARMORecord::IsHat(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHat;
    else
        Dummy->flags &= ~fIsHat;
    }

bool ARMORecord::IsEyeGlasses()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEyeGlasses) != 0;
    }

void ARMORecord::IsEyeGlasses(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsEyeGlasses;
    else
        Dummy->flags &= ~fIsEyeGlasses;
    }

bool ARMORecord::IsNoseRing()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoseRing) != 0;
    }

void ARMORecord::IsNoseRing(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoseRing;
    else
        Dummy->flags &= ~fIsNoseRing;
    }

bool ARMORecord::IsEarrings()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsEarrings) != 0;
    }

void ARMORecord::IsEarrings(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsEarrings;
    else
        Dummy->flags &= ~fIsEarrings;
    }

bool ARMORecord::IsMask()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMask) != 0;
    }

void ARMORecord::IsMask(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsMask;
    else
        Dummy->flags &= ~fIsMask;
    }

bool ARMORecord::IsChoker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsChoker) != 0;
    }

void ARMORecord::IsChoker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsChoker;
    else
        Dummy->flags &= ~fIsChoker;
    }

bool ARMORecord::IsMouthObject()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMouthObject) != 0;
    }

void ARMORecord::IsMouthObject(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsMouthObject;
    else
        Dummy->flags &= ~fIsMouthObject;
    }

bool ARMORecord::IsBodyAddon1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBodyAddon1) != 0;
    }

void ARMORecord::IsBodyAddon1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsBodyAddon1;
    else
        Dummy->flags &= ~fIsBodyAddon1;
    }

bool ARMORecord::IsBodyAddon2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBodyAddon2) != 0;
    }

void ARMORecord::IsBodyAddon2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsBodyAddon2;
    else
        Dummy->flags &= ~fIsBodyAddon2;
    }

bool ARMORecord::IsBodyAddon3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBodyAddon3) != 0;
    }

void ARMORecord::IsBodyAddon3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsBodyAddon3;
    else
        Dummy->flags &= ~fIsBodyAddon3;
    }

bool ARMORecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ARMORecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool ARMORecord::IsUnknown1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown1) != 0;
    }

void ARMORecord::IsUnknown1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown1;
    else
        Dummy->flags &= ~fIsUnknown1;
    }

bool ARMORecord::IsUnknown2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown2) != 0;
    }

void ARMORecord::IsUnknown2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown2;
    else
        Dummy->flags &= ~fIsUnknown2;
    }

bool ARMORecord::IsHasBackpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHasBackpack) != 0;
    }

void ARMORecord::IsHasBackpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHasBackpack;
    else
        Dummy->flags &= ~fIsHasBackpack;
    }

bool ARMORecord::IsMedium()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMedium) != 0;
    }

void ARMORecord::IsMedium(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsMedium;
    else
        Dummy->flags &= ~fIsMedium;
    }

bool ARMORecord::IsUnknown3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown3) != 0;
    }

void ARMORecord::IsUnknown3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown3;
    else
        Dummy->flags &= ~fIsUnknown3;
    }

bool ARMORecord::IsPowerArmor()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPowerArmor) != 0;
    }

void ARMORecord::IsPowerArmor(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPowerArmor;
    else
        Dummy->flags &= ~fIsPowerArmor;
    }

bool ARMORecord::IsNonPlayable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNonPlayable) != 0;
    }

void ARMORecord::IsNonPlayable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNonPlayable;
    else
        Dummy->flags &= ~fIsNonPlayable;
    }

bool ARMORecord::IsHeavy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHeavy) != 0;
    }

void ARMORecord::IsHeavy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHeavy;
    else
        Dummy->flags &= ~fIsHeavy;
    }

bool ARMORecord::IsExtraFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ARMORecord::SetExtraFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool ARMORecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void ARMORecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eNone;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsBigGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBigGuns);
    }

void ARMORecord::IsBigGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eBigGuns;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsEnergyWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEnergyWeapons);
    }

void ARMORecord::IsEnergyWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eEnergyWeapons;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsSmallGuns()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSmallGuns);
    }

void ARMORecord::IsSmallGuns(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eSmallGuns;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsMeleeWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMeleeWeapons);
    }

void ARMORecord::IsMeleeWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eMeleeWeapons;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsUnarmedWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnarmedWeapon);
    }

void ARMORecord::IsUnarmedWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eUnarmedWeapon;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsThrownWeapons()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eThrownWeapons);
    }

void ARMORecord::IsThrownWeapons(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eThrownWeapons;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsMine()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMine);
    }

void ARMORecord::IsMine(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eMine;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsBodyWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBodyWear);
    }

void ARMORecord::IsBodyWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eBodyWear;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsHeadWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHeadWear);
    }

void ARMORecord::IsHeadWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHeadWear;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsHandWear()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHandWear);
    }

void ARMORecord::IsHandWear(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHandWear;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsChems()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eChems);
    }

void ARMORecord::IsChems(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eChems;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsStimpack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStimpack);
    }

void ARMORecord::IsStimpack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eStimpack;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsFood()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFood);
    }

void ARMORecord::IsFood(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eFood;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsAlcohol()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAlcohol);
    }

void ARMORecord::IsAlcohol(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAlcohol;
    else
        Dummy->flags = eDummyDefault;
    }

bool ARMORecord::IsEquipmentType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void ARMORecord::SetEquipmentType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool ARMORecord::IsModulatesVoice()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsModulatesVoice) != 0;
    }

void ARMORecord::IsModulatesVoice(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsModulatesVoice;
    else
        Dummy->flags &= ~fIsModulatesVoice;
    }

bool ARMORecord::IsDNAMFlagMask(UINT16 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ARMORecord::SetDNAMFlagMask(UINT16 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 ARMORecord::GetSize(bool forceCalc)
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

    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;

    if(EITM.IsLoaded())
        TotSize += EITM.GetSize() + 6;

    if(BMDT.IsLoaded())
        TotSize += BMDT.GetSize() + 6;

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            {
            cSize = MODL->MODL.GetSize();
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

    if(MOD2.IsLoaded())
        {
        if(MOD2->MOD2.IsLoaded())
            {
            cSize = MOD2->MOD2.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD2->MO2T.IsLoaded())
            {
            cSize = MOD2->MO2T.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD2->MO2S.IsLoaded())
            TotSize += MOD2->MO2S.GetSize() + 6;
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

    if(MOD3.IsLoaded())
        {
        if(MOD3->MOD3.IsLoaded())
            {
            cSize = MOD3->MOD3.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD3->MO3T.IsLoaded())
            {
            cSize = MOD3->MO3T.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD3->MO3S.IsLoaded())
            TotSize += MOD3->MO3S.GetSize() + 6;
        if(MOD3->MOSD.IsLoaded())
            TotSize += MOD3->MOSD.GetSize() + 6;
        }

    if(MOD4.IsLoaded())
        {
        if(MOD4->MOD4.IsLoaded())
            {
            cSize = MOD4->MOD4.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD4->MO4T.IsLoaded())
            {
            cSize = MOD4->MO4T.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD4->MO4S.IsLoaded())
            TotSize += MOD4->MO4S.GetSize() + 6;
        }

    if(ICO2.IsLoaded())
        {
        cSize = ICO2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MIC2.IsLoaded())
        {
        cSize = MIC2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(BMCT.IsLoaded())
        {
        cSize = BMCT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(REPL.IsLoaded())
        TotSize += REPL.GetSize() + 6;

    if(BIPL.IsLoaded())
        TotSize += BIPL.GetSize() + 6;

    if(ETYP.IsLoaded())
        TotSize += ETYP.GetSize() + 6;

    if(YNAM.IsLoaded())
        TotSize += YNAM.GetSize() + 6;

    if(ZNAM.IsLoaded())
        TotSize += ZNAM.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    if(BNAM.IsLoaded())
        TotSize += BNAM.GetSize() + 6;

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 ARMORecord::GetType()
    {
    return 'OMRA';
    }

STRING ARMORecord::GetStrType()
    {
    return "ARMO";
    }

SINT32 ARMORecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'MTIE':
                EITM.Read(buffer, subSize, curPos);
                break;
            case 'TDMB':
                BMDT.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
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
            case '2DOM':
                MOD2.Load();
                MOD2->MOD2.Read(buffer, subSize, curPos);
                break;
            case 'T2OM':
                MOD2.Load();
                MOD2->MO2T.Read(buffer, subSize, curPos);
                break;
            case 'S2OM':
                MOD2.Load();
                MOD2->MO2S.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case '3DOM':
                MOD3.Load();
                MOD3->MOD3.Read(buffer, subSize, curPos);
                break;
            case 'T3OM':
                MOD3.Load();
                MOD3->MO3T.Read(buffer, subSize, curPos);
                break;
            case 'S3OM':
                MOD3.Load();
                MOD3->MO3S.Read(buffer, subSize, curPos);
                break;
            case 'DSOM':
                MOD3.Load();
                MOD3->MOSD.Read(buffer, subSize, curPos);
                break;
            case '4DOM':
                MOD4.Load();
                MOD4->MOD4.Read(buffer, subSize, curPos);
                break;
            case 'T4OM':
                MOD4.Load();
                MOD4->MO4T.Read(buffer, subSize, curPos);
                break;
            case 'S4OM':
                MOD4.Load();
                MOD4->MO4S.Read(buffer, subSize, curPos);
                break;
            case '2OCI':
                ICO2.Read(buffer, subSize, curPos);
                break;
            case '2CIM':
                MIC2.Read(buffer, subSize, curPos);
                break;
            case 'TCMB':
                BMCT.Read(buffer, subSize, curPos);
                break;
            case 'LPER':
                REPL.Read(buffer, subSize, curPos);
                break;
            case 'LPIB':
                BIPL.Read(buffer, subSize, curPos);
                break;
            case 'PYTE':
                ETYP.Read(buffer, subSize, curPos);
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANZ':
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANB':
                BNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ARMO: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 ARMORecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    SCRI.Unload();
    EITM.Unload();
    BMDT.Unload();
    MODL.Unload();
    MOD2.Unload();
    ICON.Unload();
    MICO.Unload();
    MOD3.Unload();
    MOD4.Unload();
    ICO2.Unload();
    MIC2.Unload();
    BMCT.Unload();
    REPL.Unload();
    BIPL.Unload();
    ETYP.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    DATA.Unload();
    DNAM.Unload();
    BNAM.Unload();
    SNAM.Unload();
    TNAM.Unload();
    return 1;
    }

SINT32 ARMORecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord('IRCS', SCRI.value, SCRI.GetSize());

    if(EITM.IsLoaded())
        SaveHandler.writeSubRecord('MTIE', EITM.value, EITM.GetSize());

    if(BMDT.IsLoaded())
        SaveHandler.writeSubRecord('TDMB', BMDT.value, BMDT.GetSize());

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());

        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());

        if(MODL->MODS.IsLoaded())
            SaveHandler.writeSubRecord('SDOM', MODL->MODS.value, MODL->MODS.GetSize());

        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', MODL->MODD.value, MODL->MODD.GetSize());

        }

    if(MOD2.IsLoaded())
        {
        if(MOD2->MOD2.IsLoaded())
            SaveHandler.writeSubRecord('2DOM', MOD2->MOD2.value, MOD2->MOD2.GetSize());

        if(MOD2->MO2T.IsLoaded())
            SaveHandler.writeSubRecord('T2OM', MOD2->MO2T.value, MOD2->MO2T.GetSize());

        if(MOD2->MO2S.IsLoaded())
            SaveHandler.writeSubRecord('S2OM', MOD2->MO2S.value, MOD2->MO2S.GetSize());

        }

    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', ICON.value, ICON.GetSize());

    if(MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MICO.value, MICO.GetSize());

    if(MOD3.IsLoaded())
        {
        if(MOD3->MOD3.IsLoaded())
            SaveHandler.writeSubRecord('3DOM', MOD3->MOD3.value, MOD3->MOD3.GetSize());

        if(MOD3->MO3T.IsLoaded())
            SaveHandler.writeSubRecord('T3OM', MOD3->MO3T.value, MOD3->MO3T.GetSize());

        if(MOD3->MO3S.IsLoaded())
            SaveHandler.writeSubRecord('S3OM', MOD3->MO3S.value, MOD3->MO3S.GetSize());

        if(MOD3->MOSD.IsLoaded())
            SaveHandler.writeSubRecord('DSOM', MOD3->MOSD.value, MOD3->MOSD.GetSize());

        }

    if(MOD4.IsLoaded())
        {
        if(MOD4->MOD4.IsLoaded())
            SaveHandler.writeSubRecord('4DOM', MOD4->MOD4.value, MOD4->MOD4.GetSize());

        if(MOD4->MO4T.IsLoaded())
            SaveHandler.writeSubRecord('T4OM', MOD4->MO4T.value, MOD4->MO4T.GetSize());

        if(MOD4->MO4S.IsLoaded())
            SaveHandler.writeSubRecord('S4OM', MOD4->MO4S.value, MOD4->MO4S.GetSize());

        }

    if(ICO2.IsLoaded())
        SaveHandler.writeSubRecord('2OCI', ICO2.value, ICO2.GetSize());

    if(MIC2.IsLoaded())
        SaveHandler.writeSubRecord('2CIM', MIC2.value, MIC2.GetSize());

    if(BMCT.IsLoaded())
        SaveHandler.writeSubRecord('TCMB', BMCT.value, BMCT.GetSize());

    if(REPL.IsLoaded())
        SaveHandler.writeSubRecord('LPER', REPL.value, REPL.GetSize());

    if(BIPL.IsLoaded())
        SaveHandler.writeSubRecord('LPIB', BIPL.value, BIPL.GetSize());

    if(ETYP.IsLoaded())
        SaveHandler.writeSubRecord('PYTE', ETYP.value, ETYP.GetSize());

    if(YNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANY', YNAM.value, YNAM.GetSize());

    if(ZNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANZ', ZNAM.value, ZNAM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    if(BNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANB', BNAM.value, BNAM.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANT', TNAM.value, TNAM.GetSize());

    return -1;
    }

bool ARMORecord::operator ==(const ARMORecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            SCRI == other.SCRI &&
            EITM == other.EITM &&
            BMDT == other.BMDT &&
            MODL == other.MODL &&
            MOD2 == other.MOD2 &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4 &&
            ICO2.equalsi(other.ICO2) &&
            MIC2.equalsi(other.MIC2) &&
            BMCT.equalsi(other.BMCT) &&
            REPL == other.REPL &&
            BIPL == other.BIPL &&
            ETYP == other.ETYP &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            DATA == other.DATA &&
            DNAM == other.DNAM &&
            BNAM == other.BNAM &&
            SNAM == other.SNAM &&
            TNAM == other.TNAM);
    }

bool ARMORecord::operator !=(const ARMORecord &other) const
    {
    return !(*this == other);
    }
}