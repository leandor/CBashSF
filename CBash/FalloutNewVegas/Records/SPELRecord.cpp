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
#include "SPELRecord.h"

namespace FNV
{
SPELRecord::SPELRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

SPELRecord::SPELRecord(SPELRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    SPIT = srcRecord->SPIT;
    if(srcRecord->EFID.IsLoaded())
        {
        EFID.Load();
        EFID->EFID = srcRecord->EFID->EFID;
        EFID->EFIT = srcRecord->EFID->EFIT;
        EFID->CTDA = srcRecord->EFID->CTDA;
        }
    return;
    }

SPELRecord::~SPELRecord()
    {
    //
    }

bool SPELRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(EFID.IsLoaded() && EFID->EFID.IsLoaded())
        op.Accept(EFID->EFID->value);
    if(EFID.IsLoaded() && EFID->CTDA.IsLoaded())
        op.Accept(EFID->CTDA->value);

    return op.Stop();
    }

bool SPELRecord::IsManualCost()
    {
    return (SPIT.value.flags & fIsManualCost) != 0;
    }

void SPELRecord::IsManualCost(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsManualCost;
    else
        SPIT.value.flags &= ~fIsManualCost;
    }

bool SPELRecord::IsStartSpell()
    {
    return (SPIT.value.flags & fIsStartSpell) != 0;
    }

void SPELRecord::IsStartSpell(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsStartSpell;
    else
        SPIT.value.flags &= ~fIsStartSpell;
    }

bool SPELRecord::IsSilenceImmune()
    {
    return (SPIT.value.flags & fIsSilenceImmune) != fIsSilenceImmune;
    }

void SPELRecord::IsSilenceImmune(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsSilenceImmune;
    else
        SPIT.value.flags &= ~fIsSilenceImmune;
    }

bool SPELRecord::IsAreaEffectIgnoresLOS()
    {
    return (SPIT.value.flags & fIsAreaEffectIgnoresLOS) != 0;
    }

void SPELRecord::IsAreaEffectIgnoresLOS(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsAreaEffectIgnoresLOS;
    else
        SPIT.value.flags &= ~fIsAreaEffectIgnoresLOS;
    }

bool SPELRecord::IsAEIgnoresLOS()
    {
    return (SPIT.value.flags & fIsAreaEffectIgnoresLOS) != 0;
    }

void SPELRecord::IsAEIgnoresLOS(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsAreaEffectIgnoresLOS;
    else
        SPIT.value.flags &= ~fIsAreaEffectIgnoresLOS;
    }

bool SPELRecord::IsScriptAlwaysApplies()
    {
    return (SPIT.value.flags & fIsScriptAlwaysApplies) != 0;
    }

void SPELRecord::IsScriptAlwaysApplies(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsScriptAlwaysApplies;
    else
        SPIT.value.flags &= ~fIsScriptAlwaysApplies;
    }

bool SPELRecord::IsDisallowAbsorbReflect()
    {
    return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
    }

void SPELRecord::IsDisallowAbsorbReflect(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsDisallowAbsorbReflect;
    else
        SPIT.value.flags &= ~fIsDisallowAbsorbReflect;
    }

bool SPELRecord::IsDisallowAbsorb()
    {
    return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
    }

void SPELRecord::IsDisallowAbsorb(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsDisallowAbsorbReflect;
    else
        SPIT.value.flags &= ~fIsDisallowAbsorbReflect;
    }

bool SPELRecord::IsDisallowReflect()
    {
    return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
    }

void SPELRecord::IsDisallowReflect(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsDisallowAbsorbReflect;
    else
        SPIT.value.flags &= ~fIsDisallowAbsorbReflect;
    }

bool SPELRecord::IsTouchExplodesWOTarget()
    {
    return (SPIT.value.flags & fIsTouchExplodesWOTarget) != 0;
    }

void SPELRecord::IsTouchExplodesWOTarget(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsTouchExplodesWOTarget;
    else
        SPIT.value.flags &= ~fIsTouchExplodesWOTarget;
    }

bool SPELRecord::IsTouchExplodes()
    {
    return (SPIT.value.flags & fIsTouchExplodesWOTarget) != 0;
    }

void SPELRecord::IsTouchExplodes(bool value)
    {
    if(value)
        SPIT.value.flags |= fIsTouchExplodesWOTarget;
    else
        SPIT.value.flags &= ~fIsTouchExplodesWOTarget;
    }

bool SPELRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((SPIT.value.flags & Mask) == Mask) : ((SPIT.value.flags & Mask) != 0);
    }

void SPELRecord::SetFlagMask(UINT8 Mask)
    {
    SPIT.value.flags = Mask;
    }

bool SPELRecord::IsActorEffect()
    {
    return (SPIT.value.spellType == eActorEffect);
    }

void SPELRecord::IsActorEffect(bool value)
    {
    if(value)
        SPIT.value.spellType = eActorEffect;
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
        SPIT.value.spellType = eActorEffect;
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
        SPIT.value.spellType = eActorEffect;
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
        SPIT.value.spellType = eActorEffect;
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
        SPIT.value.spellType = eActorEffect;
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
        SPIT.value.spellType = eActorEffect;
    }

bool SPELRecord::IsAddiction()
    {
    return (SPIT.value.spellType == eAddiction);
    }

void SPELRecord::IsAddiction(bool value)
    {
    if(value)
        SPIT.value.spellType = eAddiction;
    else if(IsPoison())
        SPIT.value.spellType = eActorEffect;
    }

bool SPELRecord::IsType(UINT32 Type)
    {
    return (SPIT.value.spellType == Type);
    }

void SPELRecord::SetType(UINT32 Type)
    {
    SPIT.value.spellType = Type;
    }



UINT32 SPELRecord::GetSize(bool forceCalc)
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

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SPIT.IsLoaded())
        TotSize += SPIT.GetSize() + 6;

    if(EFID.IsLoaded())
        {
        if(EFID->EFID.IsLoaded())
            TotSize += EFID->EFID.GetSize() + 6;
        if(EFID->EFIT.IsLoaded())
            TotSize += EFID->EFIT.GetSize() + 6;
        if(EFID->CTDA.IsLoaded())
            TotSize += EFID->CTDA.GetSize() + 6;
        }

    return TotSize;
    }

UINT32 SPELRecord::GetType()
    {
    return 'LEPS';
    }

STRING SPELRecord::GetStrType()
    {
    return "SPEL";
    }

SINT32 SPELRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'TIPS':
                SPIT.Read(buffer, subSize, curPos);
                break;
            case 'DIFE':
                EFID.Load();
                EFID->EFID.Read(buffer, subSize, curPos);
                break;
            case 'TIFE':
                EFID.Load();
                EFID->EFIT.Read(buffer, subSize, curPos);
                break;
            case 'ADTC':
                EFID.Load();
                EFID->CTDA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  SPEL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    EFID.Unload();
    return 1;
    }

SINT32 SPELRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(SPIT.IsLoaded())
        SaveHandler.writeSubRecord('TIPS', SPIT.value, SPIT.GetSize());

    if(EFID.IsLoaded())
        {
        if(EFID->EFID.IsLoaded())
            SaveHandler.writeSubRecord('DIFE', EFID->EFID.value, EFID->EFID.GetSize());

        if(EFID->EFIT.IsLoaded())
            SaveHandler.writeSubRecord('TIFE', EFID->EFIT.value, EFID->EFIT.GetSize());

        if(EFID->CTDA.IsLoaded())
            SaveHandler.writeSubRecord('ADTC', EFID->CTDA.value, EFID->CTDA.GetSize());

        }

    return -1;
    }

bool SPELRecord::operator ==(const SPELRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            SPIT == other.SPIT &&
            EFID == other.EFID);
    }

bool SPELRecord::operator !=(const SPELRecord &other) const
    {
    return !(*this == other);
    }
}