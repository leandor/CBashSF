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
#include "SPELRecord.h"

namespace Ob
{
SPELRecord::SPELSPIT::SPELSPIT():
    spellType(0),
    cost(0),
    levelType(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

SPELRecord::SPELSPIT::~SPELSPIT()
    {
    //
    }

bool SPELRecord::SPELSPIT::operator ==(const SPELSPIT &other) const
    {
    return (spellType == other.spellType &&
            cost == other.cost &&
            levelType == other.levelType &&
            flags == other.flags);
    }

bool SPELRecord::SPELSPIT::operator !=(const SPELSPIT &other) const
    {
    return !(*this == other);
    }

SPELRecord::SPELRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SPELRecord::SPELRecord(SPELRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    SPIT = srcRecord->SPIT;
    Effects = srcRecord->Effects;
    OBME = srcRecord->OBME;
    }

SPELRecord::~SPELRecord()
    {
    //
    }

bool SPELRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < Effects.value.size(); ListIndex++)
        Effects.value[ListIndex]->VisitFormIDs(op);

    return op.Stop();
    }

bool SPELRecord::IsManualCost()
    {
    return (SPIT.value.flags & fIsManualCost) != 0;
    }

void SPELRecord::IsManualCost(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsManualCost) : (SPIT.value.flags & ~fIsManualCost);
    }

bool SPELRecord::IsStartSpell()
    {
    return (SPIT.value.flags & fIsStartSpell) != 0;
    }

void SPELRecord::IsStartSpell(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsStartSpell) : (SPIT.value.flags & ~fIsStartSpell);
    }

bool SPELRecord::IsSilenceImmune()
    {
    return (SPIT.value.flags & fIsSilenceImmune) == fIsSilenceImmune;
    }

void SPELRecord::IsSilenceImmune(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsSilenceImmune) : (SPIT.value.flags & ~fIsSilenceImmune);
    }

bool SPELRecord::IsAreaEffectIgnoresLOS()
    {
    return (SPIT.value.flags & fIsAreaEffectIgnoresLOS) != 0;
    }

void SPELRecord::IsAreaEffectIgnoresLOS(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsAreaEffectIgnoresLOS) : (SPIT.value.flags & ~fIsAreaEffectIgnoresLOS);
    }

bool SPELRecord::IsAEIgnoresLOS()
    {
    return (SPIT.value.flags & fIsAreaEffectIgnoresLOS) != 0;
    }

void SPELRecord::IsAEIgnoresLOS(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsAreaEffectIgnoresLOS) : (SPIT.value.flags & ~fIsAreaEffectIgnoresLOS);
    }

bool SPELRecord::IsScriptAlwaysApplies()
    {
    return (SPIT.value.flags & fIsScriptAlwaysApplies) != 0;
    }

void SPELRecord::IsScriptAlwaysApplies(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsScriptAlwaysApplies) : (SPIT.value.flags & ~fIsScriptAlwaysApplies);
    }

bool SPELRecord::IsDisallowAbsorbReflect()
    {
    return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
    }

void SPELRecord::IsDisallowAbsorbReflect(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsDisallowAbsorbReflect) : (SPIT.value.flags & ~fIsDisallowAbsorbReflect);
    }

bool SPELRecord::IsDisallowAbsorb()
    {
    return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
    }

void SPELRecord::IsDisallowAbsorb(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsDisallowAbsorbReflect) : (SPIT.value.flags & ~fIsDisallowAbsorbReflect);
    }

bool SPELRecord::IsDisallowReflect()
    {
    return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
    }

void SPELRecord::IsDisallowReflect(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsDisallowAbsorbReflect) : (SPIT.value.flags & ~fIsDisallowAbsorbReflect);
    }

bool SPELRecord::IsTouchExplodesWOTarget()
    {
    return (SPIT.value.flags & fIsTouchExplodesWOTarget) != 0;
    }

void SPELRecord::IsTouchExplodesWOTarget(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsTouchExplodesWOTarget) : (SPIT.value.flags & ~fIsTouchExplodesWOTarget);
    }

bool SPELRecord::IsTouchExplodes()
    {
    return (SPIT.value.flags & fIsTouchExplodesWOTarget) != 0;
    }

void SPELRecord::IsTouchExplodes(bool value)
    {
    SPIT.value.flags = value ? (SPIT.value.flags | fIsTouchExplodesWOTarget) : (SPIT.value.flags & ~fIsTouchExplodesWOTarget);
    }

bool SPELRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((SPIT.value.flags & Mask) == Mask) : ((SPIT.value.flags & Mask) != 0);
    }

void SPELRecord::SetFlagMask(UINT8 Mask)
    {
    SPIT.value.flags = Mask;
    }

bool SPELRecord::IsSpell()
    {
    return (SPIT.value.spellType == eSpell);
    }

void SPELRecord::IsSpell(bool value)
    {
    if(value)
        SPIT.value.spellType = eSpell;
    else if(IsSpell())
        SPIT.value.spellType = eDisease;
    }

bool SPELRecord::IsDisease()
    {
    return (SPIT.value.spellType == eDisease);
    }

void SPELRecord::IsDisease(bool value)
    {
    if(value)
        SPIT.value.spellType = eDisease;
    else if(IsDisease())
        SPIT.value.spellType = eSpell;
    }

bool SPELRecord::IsPower()
    {
    return (SPIT.value.spellType == ePower);
    }

void SPELRecord::IsPower(bool value)
    {
    if(value)
        SPIT.value.spellType = ePower;
    else if(IsPower())
        SPIT.value.spellType = eSpell;
    }

bool SPELRecord::IsLesserPower()
    {
    return (SPIT.value.spellType == eLesserPower);
    }

void SPELRecord::IsLesserPower(bool value)
    {
    if(value)
        SPIT.value.spellType = eLesserPower;
    else if(IsLesserPower())
        SPIT.value.spellType = eSpell;
    }

bool SPELRecord::IsAbility()
    {
    return (SPIT.value.spellType == eAbility);
    }

void SPELRecord::IsAbility(bool value)
    {
    if(value)
        SPIT.value.spellType = eAbility;
    else if(IsAbility())
        SPIT.value.spellType = eSpell;
    }

bool SPELRecord::IsPoison()
    {
    return (SPIT.value.spellType == ePoison);
    }

void SPELRecord::IsPoison(bool value)
    {
    if(value)
        SPIT.value.spellType = ePoison;
    else if(IsPoison())
        SPIT.value.spellType = eSpell;
    }

bool SPELRecord::IsType(UINT32 Type)
    {
    return (SPIT.value.spellType == Type);
    }

void SPELRecord::SetType(UINT32 Type)
    {
    SPIT.value.spellType = Type;
    }

bool SPELRecord::IsNovice()
    {
    return (SPIT.value.levelType == eNovice);
    }

void SPELRecord::IsNovice(bool value)
    {
    if(value)
        SPIT.value.levelType = eNovice;
    else if(IsNovice())
        SPIT.value.levelType = eApprentice;
    }

bool SPELRecord::IsApprentice()
    {
    return (SPIT.value.levelType == eApprentice);
    }

void SPELRecord::IsApprentice(bool value)
    {
    if(value)
        SPIT.value.levelType = eApprentice;
    else if(IsApprentice())
        SPIT.value.levelType = eNovice;
    }

bool SPELRecord::IsJourneyman()
    {
    return (SPIT.value.levelType == eJourneyman);
    }

void SPELRecord::IsJourneyman(bool value)
    {
    if(value)
        SPIT.value.levelType = eJourneyman;
    else if(IsJourneyman())
        SPIT.value.levelType = eNovice;
    }

bool SPELRecord::IsExpert()
    {
    return (SPIT.value.levelType == eExpert);
    }

void SPELRecord::IsExpert(bool value)
    {
    if(value)
        SPIT.value.levelType = eExpert;
    else if(IsExpert())
        SPIT.value.levelType = eNovice;
    }

bool SPELRecord::IsMaster()
    {
    return (SPIT.value.levelType == eMaster);
    }

void SPELRecord::IsMaster(bool value)
    {
    if(value)
        SPIT.value.levelType = eMaster;
    else if(IsMaster())
        SPIT.value.levelType = eNovice;
    }

bool SPELRecord::IsLevel(UINT32 Type)
    {
    return (SPIT.value.levelType == Type);
    }

void SPELRecord::SetLevel(UINT32 Type)
    {
    SPIT.value.levelType = Type;
    }

UINT32 SPELRecord::GetType()
    {
    return REV32(SPEL);
    }

STRING SPELRecord::GetStrType()
    {
    return "SPEL";
    }

SINT32 SPELRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    bool bNoOBME = true;
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
            case REV32(OBME):
                OBME.Load();
                OBME->OBME.Read(buffer, subSize);
                break;
            case REV32(FULL):
                if(Effects.value.size())
                    Effects.value.back()->FULL.Read(buffer, subSize, CompressedOnDisk);
                else
                    FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SPIT):
                SPIT.Read(buffer, subSize);
                break;
            case REV32(EFME):
                bNoOBME = false;
                Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFME.Read(buffer, subSize);
                break;
            case REV32(EFID):
                if(bNoOBME || Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFID.Read(buffer, subSize);
                bNoOBME = true;
                break;
            case REV32(EFIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFIT.Read(buffer, subSize);
                break;
            case REV32(SCIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->SCIT.Read(buffer, subSize);
                if(Effects.value.back()->SCIT->script == eBadScript)
                    Effects.value.back()->SCIT->script = 0x00000000;
                break;
            case REV32(EFII):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFII.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(EFIX):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFIX.Read(buffer, subSize);
                break;
            case REV32(EFXX):
                buffer += subSize;
                break;
            case REV32(DATX):
                OBME.Load();
                OBME->DATX.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SPEL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 SPELRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    SPIT.Unload();
    Effects.Unload();
    OBME.Unload();
    return 1;
    }

SINT32 SPELRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    if(OBME.IsLoaded())
        OBME->WRITE(OBME);
    WRITE(FULL);
    WRITE(SPIT);
    Effects.Write(writer);
    if(OBME.IsLoaded())
        {
        if(Effects.value.size())
            WRITEEMPTY(EFXX);
        if(OBME->DATX.IsLoaded())
            OBME->WRITE(DATX);
        }
    return -1;
    }

bool SPELRecord::operator ==(const SPELRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            SPIT == other.SPIT &&
            OBME == other.OBME &&
            Effects == other.Effects);
    }

bool SPELRecord::operator !=(const SPELRecord &other) const
    {
    return !(*this == other);
    }

bool SPELRecord::equals(Record *other)
    {
    return *this == *(SPELRecord *)other;
    }
}