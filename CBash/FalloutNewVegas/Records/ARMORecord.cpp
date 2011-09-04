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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#include "..\..\Common.h"
#include "ARMORecord.h"

namespace FNV
{
ARMORecord::FNVSNAM::FNVSNAM():
    sound(0),
    chance(0),
    type(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

ARMORecord::FNVSNAM::~FNVSNAM()
    {
    //
    }

bool ARMORecord::FNVSNAM::IsWalk()
    {
    return (type == eWalk);
    }

void ARMORecord::FNVSNAM::IsWalk(bool value)
    {
    type = value ? eWalk : eSneak;
    }

bool ARMORecord::FNVSNAM::IsSneak()
    {
    return (type == eSneak);
    }

void ARMORecord::FNVSNAM::IsSneak(bool value)
    {
    type = value ? eSneak : eWalk;
    }

bool ARMORecord::FNVSNAM::IsRun()
    {
    return (type == eRun);
    }

void ARMORecord::FNVSNAM::IsRun(bool value)
    {
    type = value ? eRun : eWalk;
    }

bool ARMORecord::FNVSNAM::IsSneakArmor()
    {
    return (type == eSneakArmor);
    }

void ARMORecord::FNVSNAM::IsSneakArmor(bool value)
    {
    type = value ? eSneakArmor : eWalk;
    }

bool ARMORecord::FNVSNAM::IsRunArmor()
    {
    return (type == eRunArmor);
    }

void ARMORecord::FNVSNAM::IsRunArmor(bool value)
    {
    type = value ? eRunArmor : eWalk;
    }

bool ARMORecord::FNVSNAM::IsWalkArmor()
    {
    return (type == eWalkArmor);
    }

void ARMORecord::FNVSNAM::IsWalkArmor(bool value)
    {
    type = value ? eWalkArmor : eWalk;
    }

bool ARMORecord::FNVSNAM::IsType(UINT32 Type)
    {
    return type == Type;
    }

void ARMORecord::FNVSNAM::SetType(UINT32 Type)
    {
    type = Type;
    }

bool ARMORecord::FNVSNAM::operator ==(const FNVSNAM &other) const
    {
    return (sound == other.sound &&
            chance == other.chance &&
            type == other.type);
    }

bool ARMORecord::FNVSNAM::operator !=(const FNVSNAM &other) const
    {
    return !(*this == other);
    }

ARMORecord::ARMORecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ARMORecord::ARMORecord(ARMORecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    SCRI = srcRecord->SCRI;
    EITM = srcRecord->EITM;
    BMDT = srcRecord->BMDT;
    MODL = srcRecord->MODL;
    MOD2 = srcRecord->MOD2;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    MOD3 = srcRecord->MOD3;
    MOD4 = srcRecord->MOD4;
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
    Sounds = srcRecord->Sounds;
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
        op.Accept(SCRI.value);
    if(EITM.IsLoaded())
        op.Accept(EITM.value);
    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(MOD2.IsLoaded())
        {
        for(UINT32 x = 0; x < MOD2->Textures.MODS.size(); x++)
            op.Accept(MOD2->Textures.MODS[x]->texture);
        }
    if(MOD3.IsLoaded())
        {
        for(UINT32 x = 0; x < MOD3->Textures.MODS.size(); x++)
            op.Accept(MOD3->Textures.MODS[x]->texture);
        }
    if(MOD4.IsLoaded())
        {
        for(UINT32 x = 0; x < MOD4->Textures.MODS.size(); x++)
            op.Accept(MOD4->Textures.MODS[x]->texture);
        }
    if(REPL.IsLoaded())
        op.Accept(REPL.value);
    if(BIPL.IsLoaded())
        op.Accept(BIPL.value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    for(UINT32 x = 0; x < Sounds.value.size(); x++)
        op.Accept(Sounds.value[x]->sound);
    if(TNAM.IsLoaded())
        op.Accept(TNAM.value);

    return op.Stop();
    }

bool ARMORecord::IsHead()
    {
    return (BMDT.value.bipedFlags & fIsHead) != 0;
    }

void ARMORecord::IsHead(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsHead) : (BMDT.value.bipedFlags & ~fIsHead);
    }

bool ARMORecord::IsHair()
    {
    return (BMDT.value.bipedFlags & fIsHair) != 0;
    }

void ARMORecord::IsHair(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsHair) : (BMDT.value.bipedFlags & ~fIsHair);
    }

bool ARMORecord::IsUpperBody()
    {
    return (BMDT.value.bipedFlags & fIsUpperBody) != 0;
    }

void ARMORecord::IsUpperBody(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsUpperBody) : (BMDT.value.bipedFlags & ~fIsUpperBody);
    }

bool ARMORecord::IsLeftHand()
    {
    return (BMDT.value.bipedFlags & fIsLeftHand) != 0;
    }

void ARMORecord::IsLeftHand(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsLeftHand) : (BMDT.value.bipedFlags & ~fIsLeftHand);
    }

bool ARMORecord::IsRightHand()
    {
    return (BMDT.value.bipedFlags & fIsRightHand) != 0;
    }

void ARMORecord::IsRightHand(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsRightHand) : (BMDT.value.bipedFlags & ~fIsRightHand);
    }

bool ARMORecord::IsWeapon()
    {
    return (BMDT.value.bipedFlags & fIsWeapon) != 0;
    }

void ARMORecord::IsWeapon(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsWeapon) : (BMDT.value.bipedFlags & ~fIsWeapon);
    }

bool ARMORecord::IsPipBoy()
    {
    return (BMDT.value.bipedFlags & fIsPipBoy) != 0;
    }

void ARMORecord::IsPipBoy(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsPipBoy) : (BMDT.value.bipedFlags & ~fIsPipBoy);
    }

bool ARMORecord::IsBackpack()
    {
    return (BMDT.value.bipedFlags & fIsBackpack) != 0;
    }

void ARMORecord::IsBackpack(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsBackpack) : (BMDT.value.bipedFlags & ~fIsBackpack);
    }

bool ARMORecord::IsNecklace()
    {
    return (BMDT.value.bipedFlags & fIsNecklace) != 0;
    }

void ARMORecord::IsNecklace(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsNecklace) : (BMDT.value.bipedFlags & ~fIsNecklace);
    }

bool ARMORecord::IsHeadband()
    {
    return (BMDT.value.bipedFlags & fIsHeadband) != 0;
    }

void ARMORecord::IsHeadband(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsHeadband) : (BMDT.value.bipedFlags & ~fIsHeadband);
    }

bool ARMORecord::IsHat()
    {
    return (BMDT.value.bipedFlags & fIsHat) != 0;
    }

void ARMORecord::IsHat(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsHat) : (BMDT.value.bipedFlags & ~fIsHat);
    }

bool ARMORecord::IsEyeGlasses()
    {
    return (BMDT.value.bipedFlags & fIsEyeGlasses) != 0;
    }

void ARMORecord::IsEyeGlasses(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsEyeGlasses) : (BMDT.value.bipedFlags & ~fIsEyeGlasses);
    }

bool ARMORecord::IsNoseRing()
    {
    return (BMDT.value.bipedFlags & fIsNoseRing) != 0;
    }

void ARMORecord::IsNoseRing(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsNoseRing) : (BMDT.value.bipedFlags & ~fIsNoseRing);
    }

bool ARMORecord::IsEarrings()
    {
    return (BMDT.value.bipedFlags & fIsEarrings) != 0;
    }

void ARMORecord::IsEarrings(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsEarrings) : (BMDT.value.bipedFlags & ~fIsEarrings);
    }

bool ARMORecord::IsMask()
    {
    return (BMDT.value.bipedFlags & fIsMask) != 0;
    }

void ARMORecord::IsMask(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsMask) : (BMDT.value.bipedFlags & ~fIsMask);
    }

bool ARMORecord::IsChoker()
    {
    return (BMDT.value.bipedFlags & fIsChoker) != 0;
    }

void ARMORecord::IsChoker(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsChoker) : (BMDT.value.bipedFlags & ~fIsChoker);
    }

bool ARMORecord::IsMouthObject()
    {
    return (BMDT.value.bipedFlags & fIsMouthObject) != 0;
    }

void ARMORecord::IsMouthObject(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsMouthObject) : (BMDT.value.bipedFlags & ~fIsMouthObject);
    }

bool ARMORecord::IsBodyAddon1()
    {
    return (BMDT.value.bipedFlags & fIsBodyAddon1) != 0;
    }

void ARMORecord::IsBodyAddon1(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsBodyAddon1) : (BMDT.value.bipedFlags & ~fIsBodyAddon1);
    }

bool ARMORecord::IsBodyAddon2()
    {
    return (BMDT.value.bipedFlags & fIsBodyAddon2) != 0;
    }

void ARMORecord::IsBodyAddon2(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsBodyAddon2) : (BMDT.value.bipedFlags & ~fIsBodyAddon2);
    }

bool ARMORecord::IsBodyAddon3()
    {
    return (BMDT.value.bipedFlags & fIsBodyAddon3) != 0;
    }

void ARMORecord::IsBodyAddon3(bool value)
    {
    BMDT.value.bipedFlags = value ? (BMDT.value.bipedFlags | fIsBodyAddon3) : (BMDT.value.bipedFlags & ~fIsBodyAddon3);
    }

bool ARMORecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((BMDT.value.bipedFlags & Mask) == Mask) : ((BMDT.value.bipedFlags & Mask) != 0);
    }

void ARMORecord::SetFlagMask(UINT32 Mask)
    {
    BMDT.value.bipedFlags = Mask;
    }

bool ARMORecord::IsUnknown1()
    {
    return (BMDT.value.generalFlags & fIsUnknown1) != 0;
    }

void ARMORecord::IsUnknown1(bool value)
    {
    BMDT.value.generalFlags = value ? (BMDT.value.generalFlags | fIsUnknown1) : (BMDT.value.generalFlags & ~fIsUnknown1);
    }

bool ARMORecord::IsUnknown2()
    {
    return (BMDT.value.generalFlags & fIsUnknown2) != 0;
    }

void ARMORecord::IsUnknown2(bool value)
    {
    BMDT.value.generalFlags = value ? (BMDT.value.generalFlags | fIsUnknown2) : (BMDT.value.generalFlags & ~fIsUnknown2);
    }

bool ARMORecord::IsHasBackpack()
    {
    return (BMDT.value.generalFlags & fIsHasBackpack) != 0;
    }

void ARMORecord::IsHasBackpack(bool value)
    {
    BMDT.value.generalFlags = value ? (BMDT.value.generalFlags | fIsHasBackpack) : (BMDT.value.generalFlags & ~fIsHasBackpack);
    }

bool ARMORecord::IsMedium()
    {
    return (BMDT.value.generalFlags & fIsMedium) != 0;
    }

void ARMORecord::IsMedium(bool value)
    {
    BMDT.value.generalFlags = value ? (BMDT.value.generalFlags | fIsMedium) : (BMDT.value.generalFlags & ~fIsMedium);
    }

bool ARMORecord::IsUnknown3()
    {
    return (BMDT.value.generalFlags & fIsUnknown3) != 0;
    }

void ARMORecord::IsUnknown3(bool value)
    {
    BMDT.value.generalFlags = value ? (BMDT.value.generalFlags | fIsUnknown3) : (BMDT.value.generalFlags & ~fIsUnknown3);
    }

bool ARMORecord::IsPowerArmor()
    {
    return (BMDT.value.generalFlags & fIsPowerArmor) != 0;
    }

void ARMORecord::IsPowerArmor(bool value)
    {
    BMDT.value.generalFlags = value ? (BMDT.value.generalFlags | fIsPowerArmor) : (BMDT.value.generalFlags & ~fIsPowerArmor);
    }

bool ARMORecord::IsNonPlayable()
    {
    return (BMDT.value.generalFlags & fIsNonPlayable) != 0;
    }

void ARMORecord::IsNonPlayable(bool value)
    {
    BMDT.value.generalFlags = value ? (BMDT.value.generalFlags | fIsNonPlayable) : (BMDT.value.generalFlags & ~fIsNonPlayable);
    }

bool ARMORecord::IsHeavy()
    {
    return (BMDT.value.generalFlags & fIsHeavy) != 0;
    }

void ARMORecord::IsHeavy(bool value)
    {
    BMDT.value.generalFlags = value ? (BMDT.value.generalFlags | fIsHeavy) : (BMDT.value.generalFlags & ~fIsHeavy);
    }

bool ARMORecord::IsExtraFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((BMDT.value.generalFlags & Mask) == Mask) : ((BMDT.value.generalFlags & Mask) != 0);
    }

void ARMORecord::SetExtraFlagMask(UINT8 Mask)
    {
    BMDT.value.generalFlags = Mask;
    }

bool ARMORecord::IsModulatesVoice()
    {
    return (DNAM.value.flags & fIsModulatesVoice) != 0;
    }

void ARMORecord::IsModulatesVoice(bool value)
    {
    DNAM.value.flags = value ? (DNAM.value.flags | fIsModulatesVoice) : (DNAM.value.flags & ~fIsModulatesVoice);
    }

bool ARMORecord::IsVoiceFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? ((DNAM.value.flags & Mask) == Mask) : ((DNAM.value.flags & Mask) != 0);
    }

void ARMORecord::SetVoiceFlagMask(UINT16 Mask)
    {
    DNAM.value.flags = Mask;
    }

bool ARMORecord::IsNone()
    {
    return (ETYP.value == eNone);
    }

void ARMORecord::IsNone(bool value)
    {
    ETYP.value = value ? eNone : eBigGuns;
    }

bool ARMORecord::IsBigGuns()
    {
    return (ETYP.value == eBigGuns);
    }

void ARMORecord::IsBigGuns(bool value)
    {
    ETYP.value = value ? eBigGuns : eNone;
    }

bool ARMORecord::IsEnergyWeapons()
    {
    return (ETYP.value == eEnergyWeapons);
    }

void ARMORecord::IsEnergyWeapons(bool value)
    {
    ETYP.value = value ? eEnergyWeapons : eNone;
    }

bool ARMORecord::IsSmallGuns()
    {
    return (ETYP.value == eSmallGuns);
    }

void ARMORecord::IsSmallGuns(bool value)
    {
    ETYP.value = value ? eSmallGuns : eNone;
    }

bool ARMORecord::IsMeleeWeapons()
    {
    return (ETYP.value == eMeleeWeapons);
    }

void ARMORecord::IsMeleeWeapons(bool value)
    {
    ETYP.value = value ? eMeleeWeapons : eNone;
    }

bool ARMORecord::IsUnarmedWeapon()
    {
    return (ETYP.value == eUnarmedWeapon);
    }

void ARMORecord::IsUnarmedWeapon(bool value)
    {
    ETYP.value = value ? eUnarmedWeapon : eNone;
    }

bool ARMORecord::IsThrownWeapons()
    {
    return (ETYP.value == eThrownWeapons);
    }

void ARMORecord::IsThrownWeapons(bool value)
    {
    ETYP.value = value ? eThrownWeapons : eNone;
    }

bool ARMORecord::IsMine()
    {
    return (ETYP.value == eMine);
    }

void ARMORecord::IsMine(bool value)
    {
    ETYP.value = value ? eMine : eNone;
    }

bool ARMORecord::IsBodyWear()
    {
    return (ETYP.value == eBodyWear);
    }

void ARMORecord::IsBodyWear(bool value)
    {
    ETYP.value = value ? eBodyWear : eNone;
    }

bool ARMORecord::IsHeadWear()
    {
    return (ETYP.value == eHeadWear);
    }

void ARMORecord::IsHeadWear(bool value)
    {
    ETYP.value = value ? eHeadWear : eNone;
    }

bool ARMORecord::IsHandWear()
    {
    return (ETYP.value == eHandWear);
    }

void ARMORecord::IsHandWear(bool value)
    {
    ETYP.value = value ? eHandWear : eNone;
    }

bool ARMORecord::IsChems()
    {
    return (ETYP.value == eChems);
    }

void ARMORecord::IsChems(bool value)
    {
    ETYP.value = value ? eChems : eNone;
    }

bool ARMORecord::IsStimpack()
    {
    return (ETYP.value == eStimpack);
    }

void ARMORecord::IsStimpack(bool value)
    {
    ETYP.value = value ? eStimpack : eNone;
    }

bool ARMORecord::IsEdible()
    {
    return (ETYP.value == eEdible);
    }

void ARMORecord::IsEdible(bool value)
    {
    ETYP.value = value ? eEdible : eNone;
    }

bool ARMORecord::IsAlcohol()
    {
    return (ETYP.value == eAlcohol);
    }

void ARMORecord::IsAlcohol(bool value)
    {
    ETYP.value = value ? eAlcohol : eNone;
    }

bool ARMORecord::IsEquipmentType(SINT32 Type)
    {
    return ETYP.value == Type;
    }

void ARMORecord::SetEquipmentType(SINT32 Type)
    {
    ETYP.value = Type;
    }

bool ARMORecord::IsNotOverridingSounds()
    {
    return (BNAM.value == eNotOverridingSounds);
    }

void ARMORecord::IsNotOverridingSounds(bool value)
    {
    BNAM.value = value ? eNotOverridingSounds : eOverridingSounds;
    }

bool ARMORecord::IsOverridingSounds()
    {
    return (BNAM.value == eOverridingSounds);
    }

void ARMORecord::IsOverridingSounds(bool value)
    {
    BNAM.value = value ? eOverridingSounds : eNotOverridingSounds;
    }

bool ARMORecord::IsOverrideType(UINT32 Type)
    {
    return BNAM.value == Type;
    }

void ARMORecord::SetOverrideType(UINT32 Type)
    {
    BNAM.value = Type;
    }

UINT32 ARMORecord::GetType()
    {
    return REV32(ARMO);
    }

STRING ARMORecord::GetStrType()
    {
    return "ARMO";
    }

SINT32 ARMORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(EITM):
                EITM.Read(buffer, subSize);
                break;
            case REV32(BMDT):
                BMDT.Read(buffer, subSize);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(MOD2):
                MOD2.Load();
                MOD2->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO2T):
                MOD2.Load();
                MOD2->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO2S):
                MOD2.Load();
                MOD2->Textures.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD3):
                MOD3.Load();
                MOD3->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO3T):
                MOD3.Load();
                MOD3->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO3S):
                MOD3.Load();
                MOD3->Textures.Read(buffer, subSize);
                break;
            case REV32(MOSD):
                MOD3.Load();
                MOD3->MODD.Read(buffer, subSize);
                break;
            case REV32(MOD4):
                MOD4.Load();
                MOD4->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO4T):
                MOD4.Load();
                MOD4->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO4S):
                MOD4.Load();
                MOD4->Textures.Read(buffer, subSize);
                break;
            case REV32(ICO2):
                ICO2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MIC2):
                MIC2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BMCT):
                BMCT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(REPL):
                REPL.Read(buffer, subSize);
                break;
            case REV32(BIPL):
                BIPL.Read(buffer, subSize);
                break;
            case REV32(ETYP):
                ETYP.Read(buffer, subSize);
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                Sounds.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ARMO: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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
    Sounds.Unload();
    TNAM.Unload();
    return 1;
    }

SINT32 ARMORecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    WRITE(SCRI);
    WRITE(EITM);
    WRITE(BMDT);
    MODL.Write(writer);
    if(MOD2.IsLoaded())
        {
        MOD2->WRITEAS(MODL,MOD2);
        MOD2->WRITEAS(MODT,MO2T);
        MOD2->WRITEAS(Textures,MO2S);
        }
    WRITE(ICON);
    WRITE(MICO);
    if(MOD3.IsLoaded())
        {
        MOD3->WRITEAS(MODL,MOD3);
        MOD3->WRITEAS(MODT,MO3T);
        MOD3->WRITEAS(Textures,MO3S);
        MOD3->WRITEAS(MODD,MOSD);
        }
    if(MOD4.IsLoaded())
        {
        MOD4->WRITEAS(MODL,MOD4);
        MOD4->WRITEAS(MODT,MO4T);
        MOD4->WRITEAS(Textures,MO4S);
        }
    WRITE(ICO2);
    WRITE(MIC2);
    WRITE(BMCT);
    WRITE(REPL);
    WRITE(BIPL);
    WRITE(ETYP);
    WRITE(YNAM);
    WRITE(ZNAM);
    WRITE(DATA);
    WRITE(DNAM);
    WRITE(BNAM);
    WRITEAS(Sounds,SNAM);
    WRITE(TNAM);
    return -1;
    }

bool ARMORecord::operator ==(const ARMORecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            EITM == other.EITM &&
            BMDT == other.BMDT &&
            REPL == other.REPL &&
            BIPL == other.BIPL &&
            ETYP == other.ETYP &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            TNAM == other.TNAM &&
            DATA == other.DATA &&
            DNAM == other.DNAM &&
            BNAM == other.BNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            ICO2.equalsi(other.ICO2) &&
            MIC2.equalsi(other.MIC2) &&
            BMCT.equalsi(other.BMCT) &&
            MODL == other.MODL &&
            MOD2 == other.MOD2 &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4 &&
            Sounds == other.Sounds);
    }

bool ARMORecord::operator !=(const ARMORecord &other) const
    {
    return !(*this == other);
    }

bool ARMORecord::equals(Record *other)
    {
    return *this == *(ARMORecord *)other;
    }
}