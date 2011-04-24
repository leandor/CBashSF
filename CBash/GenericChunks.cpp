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

#include "Common.h"
#include "GenericChunks.h"

FormIDOp::FormIDOp():
    count(0),
    stop(false),
    result(false)
    {
    //
    }

FormIDOp::~FormIDOp()
    {
    //
    }

UINT32 FormIDOp::GetCount()
    {
    return count;
    }

void FormIDOp::ResetCount()
    {
    count = 0;
    }

bool FormIDOp::Stop()
    {
    return stop;
    }

bool FormIDOp::GetResult()
    {
    return result;
    }

FormIDResolver::FormIDResolver(const UINT8 (&_ResolveTable)[256], const unsigned char * const _FileStart, const unsigned char * const _FileEnd):
    FormIDOp(),
    ResolveTable(_ResolveTable),
    FileStart(_FileStart),
    FileEnd(_FileEnd)
    {
    //
    }

FormIDResolver::~FormIDResolver()
    {
    //
    }

bool FormIDResolver::Accept(UINT32 &curFormID)
    {
    curFormID = (ResolveTable[curFormID >> 24] << 24 ) | (curFormID & 0x00FFFFFF);
    return stop;
    }

bool FormIDResolver::AcceptMGEF(UINT32 &curMgefCode)
    {
    curMgefCode = (ResolveTable[curMgefCode & 0x000000FF]) | (curMgefCode & 0xFFFFFF00);
    return stop;
    }

GENU8::GENU8():
    value(0)
    {
    //
    }

GENU8::~GENU8()
    {
    //
    }

bool GENU8::operator ==(const GENU8 &other) const
    {
    return (value == other.value);
    }

bool GENU8::operator !=(const GENU8 &other) const
    {
    return !(*this == other);
    }

GENU16::GENU16():
    value(0)
    {
    //
    }

GENU16::~GENU16()
    {
    //
    }

bool GENU16::operator ==(const GENU16 &other) const
    {
    return (value == other.value);
    }

bool GENU16::operator !=(const GENU16 &other) const
    {
    return !(*this == other);
    }

GENU32::GENU32():
    value(0)
    {
    //
    }

GENU32::~GENU32()
    {
    //
    }

bool GENU32::operator ==(const GENU32 &other) const
    {
    return (value == other.value);
    }

bool GENU32::operator !=(const GENU32 &other) const
    {
    return !(*this == other);
    }

GENS8::GENS8():
    value(0)
    {
    //
    }

GENS8::~GENS8()
    {
    //
    }

bool GENS8::operator ==(const GENS8 &other) const
    {
    return (value == other.value);
    }

bool GENS8::operator !=(const GENS8 &other) const
    {
    return !(*this == other);
    }

GENS16::GENS16():
    value(0)
    {
    //
    }

GENS16::~GENS16()
    {
    //
    }

bool GENS16::operator ==(const GENS16 &other) const
    {
    return (value == other.value);
    }

bool GENS16::operator !=(const GENS16 &other) const
    {
    return !(*this == other);
    }

GENS32::GENS32():
    value(0)
    {
    //
    }

GENS32::~GENS32()
    {
    //
    }

bool GENS32::operator ==(const GENS32 &other) const
    {
    return (value == other.value);
    }

bool GENS32::operator !=(const GENS32 &other) const
    {
    return !(*this == other);
    }

GENXNAM::GENXNAM():
    faction(0),
    mod(0)
    {
    //
    }

GENXNAM::~GENXNAM()
    {
    //
    }

bool GENXNAM::operator ==(const GENXNAM &other) const
    {
    return (faction == other.faction && mod == other.mod);
    }

bool GENXNAM::operator !=(const GENXNAM &other) const
    {
    return !(*this == other);
    }

GENSCHR::GENSCHR():
    numRefs(0),
    compiledSize(0),
    lastIndex(0),
    scriptType(0)
    {
    memset(&unused1, 0x00, 4);
    }

GENSCHR::~GENSCHR()
    {
    //
    }

bool GENSCHR::operator ==(const GENSCHR &other) const
    {
    return (numRefs == other.numRefs &&
            compiledSize == other.compiledSize &&
            lastIndex == other.lastIndex &&
            scriptType == other.scriptType);
    }

bool GENSCHR::operator !=(const GENSCHR &other) const
    {
    return !(*this == other);
    }

FNVSCHR::FNVSCHR():
    numRefs(0),
    compiledSize(0),
    lastIndex(0),
    scriptType(0),
    flags(0)
    {
    memset(&unused1, 0x00, 4);
    }

FNVSCHR::~FNVSCHR()
    {
    //
    }

bool FNVSCHR::operator ==(const FNVSCHR &other) const
    {
    return (numRefs == other.numRefs &&
            compiledSize == other.compiledSize &&
            lastIndex == other.lastIndex &&
            scriptType == other.scriptType &&
            flags == other.flags);
    }

bool FNVSCHR::operator !=(const FNVSCHR &other) const
    {
    return !(*this == other);
    }

GENSCR_::GENSCR_():
    reference(0),
    isSCRO(false)
    {
    //
    }

GENSCR_::~GENSCR_()
    {
    //
    }

GENSLSD::GENSLSD():
    index(0),
    flags(0)
    {
    memset(&unused1[0], 0, sizeof(unused1));
    memset(&unused2[0], 0, sizeof(unused2));
    }

GENSLSD::~GENSLSD()
    {
    //
    }

bool GENSLSD::operator ==(const GENSLSD &other) const
    {
    return (index == other.index &&
            flags == other.flags);
    }

bool GENSLSD::operator !=(const GENSLSD &other) const
    {
    return !(*this == other);
    }

bool GENVARS::IsLongOrShort()
    {
    return (SLSD.value.flags & fIsLongOrShort) != 0;
    }

void GENVARS::IsLongOrShort(bool value)
    {
    SLSD.value.flags = value ? (SLSD.value.flags | fIsLongOrShort) : (SLSD.value.flags & ~fIsLongOrShort);
    }

bool GENVARS::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((SLSD.value.flags & Mask) == Mask) : ((SLSD.value.flags & Mask) != 0);
    }

void GENVARS::SetFlagMask(UINT8 Mask)
    {
    SLSD.value.flags = Mask;
    }

bool GENVARS::operator ==(const GENVARS &other) const
    {
    return (SLSD == other.SLSD &&
            SCVR.equalsi(other.SCVR));
    }

bool GENVARS::operator !=(const GENVARS &other) const
    {
    return !(*this == other);
    }

bool GENSCR_::operator ==(const GENSCR_ &other) const
    {
    return (reference == other.reference &&
            isSCRO == other.isSCRO);
    }

bool GENSCR_::operator !=(const GENSCR_ &other) const
    {
    return !(*this == other);
    }

FNVMINSCRIPT::FNVMINSCRIPT()
    {
    //
    }

FNVMINSCRIPT::~FNVMINSCRIPT()
    {
    for(UINT32 x = 0; x < SCR_.size(); x++)
        delete SCR_[x];
    }

bool FNVMINSCRIPT::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void FNVMINSCRIPT::IsScriptEnabled(bool value)
    {
    if(value)
        SCHR.value.flags |= fIsEnabled;
    else
        SCHR.value.flags &= ~fIsEnabled;
    }

bool FNVMINSCRIPT::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    if(Exact)
        return (SCHR.value.flags & Mask) == Mask;
    else
        return (SCHR.value.flags & Mask) != 0;
    }

void FNVMINSCRIPT::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

bool FNVMINSCRIPT::IsType(UINT32 Type)
    {
    return SCHR.value.scriptType == Type;
    }

void FNVMINSCRIPT::SetType(UINT32 Type)
    {
    SCHR.value.scriptType = Type;
    }

bool FNVMINSCRIPT::operator ==(const FNVMINSCRIPT &other) const
    {
    if(SCHR == other.SCHR &&
        SCDA == other.SCDA &&
        SCTX.equalsi(other.SCTX) &&
        SCR_.size() == other.SCR_.size())
        {
        //Record order matters on references, so equality testing is easy
        for(UINT32 x = 0; x < SCR_.size(); ++x)
            if(*SCR_[x] != *other.SCR_[x])
                return false;
        return true;
        }

    return false;
    }

bool FNVMINSCRIPT::operator !=(const FNVMINSCRIPT &other) const
    {
    return !(*this == other);
    }

GENEFIT::GENEFIT():
    name(0),
    magnitude(0),
    area(0),
    duration(0),
    rangeType(0),
    actorValue(0)
    {
    //
    }

GENEFIT::~GENEFIT()
    {
    //
    }

bool GENEFIT::operator ==(const GENEFIT &other) const
    {
    return (name == other.name &&
            magnitude == other.magnitude &&
            area == other.area &&
            duration == other.duration &&
            rangeType == other.rangeType &&
            actorValue == other.actorValue);
    }

bool GENEFIT::operator !=(const GENEFIT &other) const
    {
    return !(*this == other);
    }

GENSCIT::GENSCIT():
    script(0),
    school(0),
    visual(0),
    flags(0)
    {
    memset(&unused1, 0x00, 3);
    }

GENSCIT::~GENSCIT()
    {
    //
    }

bool GENSCIT::operator ==(const GENSCIT &other) const
    {
    return (script == other.script &&
            school == other.school &&
            visual == other.visual &&
            flags == other.flags);
    }

bool GENSCIT::operator !=(const GENSCIT &other) const
    {
    return !(*this == other);
    }

OBMEEFME::OBMEEFME():
    recordVersion(0),
    betaVersion(0),
    minorVersion(0),
    majorVersion(0),
    efitParamInfo(0),
    efixParamInfo(0)
    {
    memset(&reserved, 0x00, 0xA);
    }

OBMEEFME::~OBMEEFME()
    {
    //
    }

bool OBMEEFME::operator ==(const OBMEEFME &other) const
    {
    return (recordVersion == other.recordVersion &&
            betaVersion == other.betaVersion &&
            minorVersion == other.minorVersion &&
            majorVersion == other.majorVersion &&
            efitParamInfo == other.efitParamInfo &&
            efixParamInfo == other.efixParamInfo &&
            reserved == other.reserved);
    }

bool OBMEEFME::operator !=(const OBMEEFME &other) const
    {
    return !(*this == other);
    }

OBMEEFIX::OBMEEFIX():
    efixOverrides(0),
    efixFlags(0),
    baseCost(0.0),
    resistAV(0)
    {
    memset(&reserved, 0x00, 0x10);
    }

OBMEEFIX::~OBMEEFIX()
    {
    //
    }

bool OBMEEFIX::operator ==(const OBMEEFIX &other) const
    {
    return (efixOverrides == other.efixOverrides &&
            efixFlags == other.efixFlags &&
            AlmostEqual(baseCost,other.baseCost,2) &&
            resistAV == other.resistAV &&
            reserved == other.reserved);
    }

bool OBMEEFIX::operator !=(const OBMEEFIX &other) const
    {
    return !(*this == other);
    }

bool OBMEEffect::operator ==(const OBMEEffect &other) const
    {
    return (EFME == other.EFME &&
            EFII.equals(other.EFII) &&
            EFIX == other.EFIX);
    }
bool OBMEEffect::operator !=(const OBMEEffect &other) const
    {
    return !(*this == other);
    }

bool GENEffect::operator ==(const GENEffect &other) const
    {
    return (EFID == other.EFID &&
            EFIT == other.EFIT &&
            SCIT == other.SCIT &&
            FULL.equals(other.FULL) &&
            OBME == other.OBME);
    }

bool GENEffect::operator !=(const GENEffect &other) const
    {
    return !(*this == other);
    }

bool GENEffect::IsHostile()
    {
    if(!SCIT.IsLoaded()) return false;
    return (SCIT->flags & fIsHostile) != 0;
    }

void GENEffect::IsHostile(bool value)
    {
    if(!SCIT.IsLoaded()) return;
    if(value)
        SCIT->flags |= fIsHostile;
    else
        SCIT->flags &= ~fIsHostile;
    }

bool GENEffect::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!SCIT.IsLoaded()) return false;
    if(Exact)
        return (SCIT->flags & Mask) == Mask;
    else
        return (SCIT->flags & Mask) != 0;
    }

void GENEffect::SetFlagMask(UINT8 Mask)
    {
    SCIT.Load();
    SCIT->flags = Mask;
    }

bool GENEffect::IsRangeSelf()
    {
    return (EFIT.value.rangeType == eRangeSelf);
    }

void GENEffect::IsRangeSelf(bool value)
    {
    if(value)
        EFIT.value.rangeType = eRangeSelf;
    else
        EFIT.value.rangeType = eRangeTouch;
    }

bool GENEffect::IsRangeTouch()
    {
    return (EFIT.value.rangeType == eRangeTouch);
    }

void GENEffect::IsRangeTouch(bool value)
    {
    if(value)
        EFIT.value.rangeType = eRangeTouch;
    else
        EFIT.value.rangeType = eRangeSelf;
    }

bool GENEffect::IsRangeTarget()
    {
    return (EFIT.value.rangeType == eRangeTarget);
    }

void GENEffect::IsRangeTarget(bool value)
    {
    if(value)
        EFIT.value.rangeType = eRangeTarget;
    else
        EFIT.value.rangeType = eRangeSelf;
    }

bool GENEffect::IsRange(UINT32 Mask)
    {
    return (EFIT.value.rangeType == Mask);
    }

void GENEffect::SetRange(UINT32 Mask)
    {
    EFIT.value.rangeType = Mask;
    }

bool GENEffect::OBME_IsUsingHostileOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingHostileOverride) != 0;
    }

void GENEffect::OBME_IsUsingHostileOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingHostileOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingHostileOverride;
    }

bool GENEffect::OBME_IsUsingRecoversOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingRecoversOverride) != 0;
    }

void GENEffect::OBME_IsUsingRecoversOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingRecoversOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingRecoversOverride;
    }

bool GENEffect::OBME_IsUsingParamFlagAOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingParamFlagAOverride) != 0;
    }

void GENEffect::OBME_IsUsingParamFlagAOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingParamFlagAOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingParamFlagAOverride;
    }

bool GENEffect::OBME_IsUsingBeneficialOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingBeneficialOverride) != 0;
    }

void GENEffect::OBME_IsUsingBeneficialOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingBeneficialOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingBeneficialOverride;
    }

bool GENEffect::OBME_IsUsingEFIXParamOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingEFIXParamOverride) != 0;
    }

void GENEffect::OBME_IsUsingEFIXParamOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingEFIXParamOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingEFIXParamOverride;
    }

bool GENEffect::OBME_IsUsingSchoolOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingSchoolOverride) != 0;
    }

void GENEffect::OBME_IsUsingSchoolOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingSchoolOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingSchoolOverride;
    }

bool GENEffect::OBME_IsUsingNameOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingNameOverride) != 0;
    }

void GENEffect::OBME_IsUsingNameOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingNameOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingNameOverride;
    }

bool GENEffect::OBME_IsUsingVFXCodeOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingVFXCodeOverride) != 0;
    }

void GENEffect::OBME_IsUsingVFXCodeOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingVFXCodeOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingVFXCodeOverride;
    }

bool GENEffect::OBME_IsUsingBaseCostOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingBaseCostOverride) != 0;
    }

void GENEffect::OBME_IsUsingBaseCostOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingBaseCostOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingBaseCostOverride;
    }

bool GENEffect::OBME_IsUsingResistAVOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingResistAVOverride) != 0;
    }

void GENEffect::OBME_IsUsingResistAVOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingResistAVOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingResistAVOverride;
    }

bool GENEffect::OBME_IsUsingFXPersistsOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingFXPersistsOverride) != 0;
    }

void GENEffect::OBME_IsUsingFXPersistsOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingFXPersistsOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingFXPersistsOverride;
    }

bool GENEffect::OBME_IsUsingIconOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingIconOverride) != 0;
    }

void GENEffect::OBME_IsUsingIconOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingIconOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingIconOverride;
    }

bool GENEffect::OBME_IsUsingDoesntTeachOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingDoesntTeachOverride) != 0;
    }

void GENEffect::OBME_IsUsingDoesntTeachOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingDoesntTeachOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingDoesntTeachOverride;
    }

bool GENEffect::OBME_IsUsingUnknownFOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingUnknownFOverride) != 0;
    }

void GENEffect::OBME_IsUsingUnknownFOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingUnknownFOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingUnknownFOverride;
    }

bool GENEffect::OBME_IsUsingNoRecastOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingNoRecastOverride) != 0;
    }

void GENEffect::OBME_IsUsingNoRecastOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingNoRecastOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingNoRecastOverride;
    }

bool GENEffect::OBME_IsUsingParamFlagBOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingParamFlagBOverride) != 0;
    }

void GENEffect::OBME_IsUsingParamFlagBOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingParamFlagBOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingParamFlagBOverride;
    }

bool GENEffect::OBME_IsUsingMagnitudeIsRangeOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingMagnitudeIsRangeOverride) != 0;
    }

void GENEffect::OBME_IsUsingMagnitudeIsRangeOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingMagnitudeIsRangeOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingMagnitudeIsRangeOverride;
    }

bool GENEffect::OBME_IsUsingAtomicResistanceOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingAtomicResistanceOverride) != 0;
    }

void GENEffect::OBME_IsUsingAtomicResistanceOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingAtomicResistanceOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingAtomicResistanceOverride;
    }

bool GENEffect::OBME_IsUsingParamFlagCOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingParamFlagCOverride) != 0;
    }

void GENEffect::OBME_IsUsingParamFlagCOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingParamFlagCOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingParamFlagCOverride;
    }

bool GENEffect::OBME_IsUsingParamFlagDOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingParamFlagDOverride) != 0;
    }

void GENEffect::OBME_IsUsingParamFlagDOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingParamFlagDOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingParamFlagDOverride;
    }

bool GENEffect::OBME_IsUsingDisabledOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingDisabledOverride) != 0;
    }

void GENEffect::OBME_IsUsingDisabledOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingDisabledOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingDisabledOverride;
    }

bool GENEffect::OBME_IsUsingUnknownOOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingUnknownOOverride) != 0;
    }

void GENEffect::OBME_IsUsingUnknownOOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingUnknownOOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingUnknownOOverride;
    }

bool GENEffect::OBME_IsUsingNoHitEffectOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingNoHitEffectOverride) != 0;
    }

void GENEffect::OBME_IsUsingNoHitEffectOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingNoHitEffectOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingNoHitEffectOverride;
    }

bool GENEffect::OBME_IsUsingPersistOnDeathOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingPersistOnDeathOverride) != 0;
    }

void GENEffect::OBME_IsUsingPersistOnDeathOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingPersistOnDeathOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingPersistOnDeathOverride;
    }

bool GENEffect::OBME_IsUsingExplodesWithForceOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingExplodesWithForceOverride) != 0;
    }

void GENEffect::OBME_IsUsingExplodesWithForceOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingExplodesWithForceOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingExplodesWithForceOverride;
    }

bool GENEffect::OBME_IsUsingHiddenOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingHiddenOverride) != 0;
    }

void GENEffect::OBME_IsUsingHiddenOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixOverrides |= fOBME_IsUsingHiddenOverride;
    else
        OBME->EFIX->efixOverrides &= ~fOBME_IsUsingHiddenOverride;
    }

bool GENEffect::OBME_IsOverrideFlagMask(UINT32 Mask, bool Exact)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    if(Exact)
        return (OBME->EFIX->efixOverrides & Mask) == Mask;
    else
        return (OBME->EFIX->efixOverrides & Mask) != 0;
    }

void GENEffect::OBME_SetOverrideFlagMask(UINT32 Mask)
    {
    if(Mask == 0 && OBME.IsLoaded())
        OBME->EFIX.Unload();
    else
        {
        OBME.Load();
        OBME->EFIX.Load();
        OBME->EFIX->efixOverrides = Mask;
        }
    }

bool GENEffect::OBME_IsHostile()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsHostile) != 0;
    }

void GENEffect::OBME_IsHostile(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsHostile;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsHostile;
    }

bool GENEffect::OBME_IsRecovers()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsRecovers) != 0;
    }

void GENEffect::OBME_IsRecovers(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsRecovers;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsRecovers;
    }

bool GENEffect::OBME_IsParamFlagA()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsParamFlagA) != 0;
    }

void GENEffect::OBME_IsParamFlagA(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsParamFlagA;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsParamFlagA;
    }

bool GENEffect::OBME_IsBeneficial()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsBeneficial) != 0;
    }

void GENEffect::OBME_IsBeneficial(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsBeneficial;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsBeneficial;
    }

bool GENEffect::OBME_IsFXPersists()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsFXPersists) != 0;
    }

void GENEffect::OBME_IsFXPersists(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsFXPersists;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsFXPersists;
    }

bool GENEffect::OBME_IsUnknownF()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsUnknownF) != 0;
    }

void GENEffect::OBME_IsUnknownF(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsUnknownF;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsUnknownF;
    }

bool GENEffect::OBME_IsNoRecast()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsNoRecast) != 0;
    }

void GENEffect::OBME_IsNoRecast(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsNoRecast;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsNoRecast;
    }

bool GENEffect::OBME_IsParamFlagB()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsParamFlagB) != 0;
    }

void GENEffect::OBME_IsParamFlagB(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsParamFlagB;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsParamFlagB;
    }

bool GENEffect::OBME_IsMagnitudeIsRange()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsMagnitudeIsRange) != 0;
    }

void GENEffect::OBME_IsMagnitudeIsRange(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsMagnitudeIsRange;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsMagnitudeIsRange;
    }

bool GENEffect::OBME_IsAtomicResistance()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsAtomicResistance) != 0;
    }

void GENEffect::OBME_IsAtomicResistance(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsAtomicResistance;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsAtomicResistance;
    }

bool GENEffect::OBME_IsParamFlagC()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsParamFlagC) != 0;
    }

void GENEffect::OBME_IsParamFlagC(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsParamFlagC;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsParamFlagC;
    }

bool GENEffect::OBME_IsParamFlagD()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsParamFlagD) != 0;
    }

void GENEffect::OBME_IsParamFlagD(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsParamFlagD;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsParamFlagD;
    }

bool GENEffect::OBME_IsDisabled()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsDisabled) != 0;
    }

void GENEffect::OBME_IsDisabled(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsDisabled;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsDisabled;
    }

bool GENEffect::OBME_IsUnknownO()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsUnknownO) != 0;
    }

void GENEffect::OBME_IsUnknownO(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsUnknownO;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsUnknownO;
    }

bool GENEffect::OBME_IsNoHitEffect()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsNoHitEffect) != 0;
    }

void GENEffect::OBME_IsNoHitEffect(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsNoHitEffect;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsNoHitEffect;
    }

bool GENEffect::OBME_IsPersistOnDeath()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsPersistOnDeath) != 0;
    }

void GENEffect::OBME_IsPersistOnDeath(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsPersistOnDeath;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsPersistOnDeath;
    }

bool GENEffect::OBME_IsExplodesWithForce()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsExplodesWithForce) != 0;
    }

void GENEffect::OBME_IsExplodesWithForce(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsExplodesWithForce;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsExplodesWithForce;
    }

bool GENEffect::OBME_IsHidden()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsHidden) != 0;
    }

void GENEffect::OBME_IsHidden(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    if(value)
        OBME->EFIX->efixFlags |= fOBME_IsHidden;
    else
        OBME->EFIX->efixFlags &= ~fOBME_IsHidden;
    }

bool GENEffect::OBME_IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    if(Exact)
        return (OBME->EFIX->efixFlags & Mask) == Mask;
    else
        return (OBME->EFIX->efixFlags & Mask) != 0;
    }

void GENEffect::OBME_SetFlagMask(UINT32 Mask)
    {
    OBME.Load();
    OBME->EFIX.Load();
    OBME->EFIX->efixFlags = Mask;
    }

GENENIT::GENENIT():
    value(0),
    flags(0)
    {
    memset(&unused1, 0x00, 3);
    }

GENENIT::~GENENIT()
    {
    //
    }

bool GENENIT::operator ==(const GENENIT &other) const
    {
    return (value == other.value &&
            flags == other.flags);
    }

bool GENENIT::operator !=(const GENENIT &other) const
    {
    return !(*this == other);
    }

GENVALUEWEIGHT::GENVALUEWEIGHT():
    value(0),
    weight(0.0f)
    {
    //
    }

GENVALUEWEIGHT::~GENVALUEWEIGHT()
    {
    //
    }

bool GENVALUEWEIGHT::operator ==(const GENVALUEWEIGHT &other) const
    {
    return (value == other.value &&
            AlmostEqual(weight,other.weight,2));
    }

bool GENVALUEWEIGHT::operator !=(const GENVALUEWEIGHT &other) const
    {
    return !(*this == other);
    }

GENCNTO::GENCNTO():
    item(0),
    count(1)
    {
    //
    }

GENCNTO::~GENCNTO()
    {
    //
    }

bool GENCNTO::operator ==(const GENCNTO &other) const
    {
    return (item == other.item &&
            count == other.count);
    }

bool GENCNTO::operator !=(const GENCNTO &other) const
    {
    return !(*this == other);
    }

GENACBS::GENACBS():
    flags(0),
    baseSpell(0),
    fatigue(0),
    barterGold(0),
    level(1),
    calcMin(0),
    calcMax(0)
    {
    //
    }

GENACBS::~GENACBS()
    {
    //
    }

bool GENACBS::operator ==(const GENACBS &other) const
    {
    return (flags == other.flags &&
            baseSpell == other.baseSpell &&
            fatigue == other.fatigue &&
            barterGold == other.barterGold &&
            level == other.level &&
            calcMin == other.calcMin &&
            calcMax == other.calcMax);
    }

bool GENACBS::operator !=(const GENACBS &other) const
    {
    return !(*this == other);
    }

GENSNAM::GENSNAM():
    faction(0),
    rank(0)
    {
    memset(&unused1, 0x00, 3);
    }

GENSNAM::~GENSNAM()
    {
    //
    }

bool GENSNAM::operator ==(const GENSNAM &other) const
    {
    return (faction == other.faction &&
            rank == other.rank);
    }

bool GENSNAM::operator !=(const GENSNAM &other) const
    {
    return !(*this == other);
    }

GENAIDT::GENAIDT():
    aggression(5),
    confidence(50),
    energyLevel(50),
    responsibility(50),
    flags(0),
    trainSkill(0),
    trainLevel(0)
    {
    memset(&unused1, 0x00, 2);
    }

GENAIDT::~GENAIDT()
    {
    //
    }

bool GENAIDT::operator ==(const GENAIDT &other) const
    {
    return (aggression == other.aggression &&
            confidence == other.confidence &&
            energyLevel == other.energyLevel &&
            responsibility == other.responsibility &&
            flags == other.flags &&
            trainSkill == other.trainSkill &&
            trainLevel == other.trainLevel);
    }

bool GENAIDT::operator !=(const GENAIDT &other) const
    {
    return !(*this == other);
    }

GENCTDA::GENCTDA():
    operType(0),
    compValue(0.0f),
    ifunc(0),
    param1(0),
    param2(0)
    {
    memset(&unused1, 0x00, 3);
    memset(&unused2, 0x00, 4);
    }

GENCTDA::~GENCTDA()
    {
    //
    }

bool GENCTDA::operator ==(const GENCTDA &other) const
    {
    return (operType == other.operType &&
            AlmostEqual(compValue,other.compValue,2) &&
            ifunc == other.ifunc &&
            param1 == other.param1 &&
            param2 == other.param2);
    }

bool GENCTDA::operator !=(const GENCTDA &other) const
    {
    return !(*this == other);
    }

bool GENCTDA::IsEqual()
    {
    return ((operType & 0xF0) == eEqual);
    }

void GENCTDA::IsEqual(bool value)
    {
    if(value)
        {
        operType &= 0x0F;
        operType |= eEqual;
        }
    else if(IsEqual())
        {
        operType &= 0x0F;
        operType |= eNotEqual;
        }
    }

bool GENCTDA::IsNotEqual()
    {
    return ((operType & 0xF0) == eNotEqual);
    }

void GENCTDA::IsNotEqual(bool value)
    {
    if(value)
        {
        operType &= 0x0F;
        operType |= eNotEqual;
        }
    else if(IsNotEqual())
        {
        operType &= 0x0F;
        operType |= eEqual;
        }
    }

bool GENCTDA::IsGreater()
    {
    return ((operType & 0xF0) == eGreater);
    }

void GENCTDA::IsGreater(bool value)
    {
    if(value)
        {
        operType &= 0x0F;
        operType |= eGreater;
        }
    else if(IsGreater())
        {
        operType &= 0x0F;
        operType |= eEqual;
        }
    }

bool GENCTDA::IsGreaterOrEqual()
    {
    return ((operType & 0xF0) == eGreaterOrEqual);
    }

void GENCTDA::IsGreaterOrEqual(bool value)
    {
    if(value)
        {
        operType &= 0x0F;
        operType |= eGreaterOrEqual;
        }
    else if(IsGreaterOrEqual())
        {
        operType &= 0x0F;
        operType |= eEqual;
        }
    }

bool GENCTDA::IsLess()
    {
    return ((operType & 0xF0) == eLess);
    }

void GENCTDA::IsLess(bool value)
    {
    if(value)
        {
        operType &= 0x0F;
        operType |= eLess;
        }
    else if(IsLess())
        {
        operType &= 0x0F;
        operType |= eEqual;
        }
    }

bool GENCTDA::IsLessOrEqual()
    {
    return ((operType & 0xF0) == eLessOrEqual);
    }

void GENCTDA::IsLessOrEqual(bool value)
    {
    if(value)
        {
        operType &= 0x0F;
        operType |= eLessOrEqual;
        }
    else if(IsNotEqual())
        {
        operType &= 0x0F;
        operType |= eEqual;
        }
    }

bool GENCTDA::IsType(UINT8 Type)
    {
    return ((operType & 0xF0) == (Type & 0xF0));
    }

void GENCTDA::SetType(UINT8 Type)
    {
    Type &= 0xF0;
    operType &= 0x0F;
    operType |= Type;
    }

bool GENCTDA::IsNone()
    {
    return ((operType & 0x0F) == fIsNone);
    }

void GENCTDA::IsNone(bool value)
    {
    if(value)
        operType &= 0xF0;
    }

bool GENCTDA::IsOr()
    {
    return ((operType & 0x0F) & fIsOr) != 0;
    }

void GENCTDA::IsOr(bool value)
    {
    if(value)
        operType |= fIsOr;
    else
        operType &= ~fIsOr;
    }

bool GENCTDA::IsRunOnTarget()
    {
    return ((operType & 0x0F) & fIsRunOnTarget) != 0;
    }

void GENCTDA::IsRunOnTarget(bool value)
    {
    if(value)
        operType |= fIsRunOnTarget;
    else
        operType &= ~fIsRunOnTarget;
    }

bool GENCTDA::IsUseGlobal()
    {
    return ((operType & 0x0F) & fIsUseGlobal) != 0;
    }

void GENCTDA::IsUseGlobal(bool value)
    {
    if(value)
        operType |= fIsUseGlobal;
    else
        operType &= ~fIsUseGlobal;
    }

bool GENCTDA::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(Exact)
        return ((operType & 0x0F) & (Mask & 0x0F)) == Mask;
    else
        return ((operType & 0x0F) & (Mask & 0x0F)) != 0;
    }

void GENCTDA::SetFlagMask(UINT8 Mask)
    {
    Mask &= 0x0F;
    operType &= 0xF0;
    operType |= Mask;
    }

GENCLR::GENCLR(UINT8 _red, UINT8 _green, UINT8 _blue, UINT8 _unused1):
    red(_red),
    green(_green),
    blue(_blue),
    unused1(_unused1)
    {
    //
    }

GENCLR::~GENCLR()
    {
    //
    }

bool GENCLR::operator ==(const GENCLR &other) const
    {
    return (red == other.red &&
            green == other.green &&
            blue == other.blue);
    }

bool GENCLR::operator !=(const GENCLR &other) const
    {
    return !(*this == other);
    }

bool GENMODEL::operator ==(const GENMODEL &other) const
    {
    return (MODB == other.MODB &&
            MODL.equalsi(other.MODL) &&
            MODT == other.MODT);
    }

bool GENMODEL::operator !=(const GENMODEL &other) const
    {
    return !(*this == other);
    }

bool GENXOWN::operator ==(const GENXOWN &other) const
    {
    return (XOWN == other.XOWN &&
            XRNK == other.XRNK &&
            XGLB == other.XGLB);
    }

bool GENXOWN::operator !=(const GENXOWN &other) const
    {
    return !(*this == other);
    }

bool GENXPCI::operator ==(const GENXPCI &other) const
    {
    return (XPCI == other.XPCI &&
            FULL.equalsi(other.FULL));
    }

bool GENXPCI::operator !=(const GENXPCI &other) const
    {
    return !(*this == other);
    }

GENXLOD::GENXLOD():
    lod1(0.0f),
    lod2(0.0f),
    lod3(0.0f)
    {
    //
    }

GENXLOD::~GENXLOD()
    {
    //
    }

bool GENXLOD::operator ==(const GENXLOD &other) const
    {
    return (AlmostEqual(lod1,other.lod1,2) &&
            AlmostEqual(lod2,other.lod2,2) &&
            AlmostEqual(lod3,other.lod3,2)
            );
    }

bool GENXLOD::operator !=(const GENXLOD &other) const
    {
    return !(*this == other);
    }

GENXESP::GENXESP():
    parent(0),
    flags(0)
    {
    memset(&unused1, 0x00, 3);
    }

GENXESP::~GENXESP()
    {
    //
    }

bool GENXESP::operator ==(const GENXESP &other) const
    {
    return (parent == other.parent &&
            flags == other.flags);
    }

bool GENXESP::operator !=(const GENXESP &other) const
    {
    return !(*this == other);
    }

GENXSCL::GENXSCL():
    scale(1.0f)
    {
    //
    }

GENXSCL::~GENXSCL()
    {
    //
    }

bool GENXSCL::operator ==(const GENXSCL &other) const
    {
    return (AlmostEqual(scale,other.scale,2));
    }

bool GENXSCL::operator !=(const GENXSCL &other) const
    {
    return !(*this == other);
    }

GENPOSDATA::GENPOSDATA():
    posX(0.0f),
    posY(0.0f),
    posZ(0.0f),
    rotX(0.0f),
    rotY(0.0f),
    rotZ(0.0f)
    {
    //
    }

GENPOSDATA::~GENPOSDATA()
    {
    //
    }

bool GENPOSDATA::operator ==(const GENPOSDATA &other) const
    {
    return (AlmostEqual(posX,other.posX,2) &&
            AlmostEqual(posY,other.posY,2) &&
            AlmostEqual(posZ,other.posZ,2) &&
            AlmostEqual(rotX,other.rotX,2) &&
            AlmostEqual(rotY,other.rotY,2) &&
            AlmostEqual(rotZ,other.rotZ,2)
            );
    }

bool GENPOSDATA::operator !=(const GENPOSDATA &other) const
    {
    return !(*this == other);
    }

GENPGRP::GENPGRP():
    x(0.0f),
    y(0.0f),
    z(0.0f),
    connections(0)
    {
    memset(&unused1, 0x00, 3);
    }

GENPGRP::~GENPGRP()
    {
    //
    }

bool GENPGRP::operator ==(const GENPGRP &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2) &&
            AlmostEqual(z,other.z,2) &&
            connections == other.connections);
    }

bool GENPGRP::operator !=(const GENPGRP &other) const
    {
    return !(*this == other);
    }

LVLLVLO::LVLLVLO():
    level(0),
    listId(0),
    count(1)
    {
    memset(&unused1, 0x00, 2);
    memset(&unused2, 0x00, 2);
    }

LVLLVLO::~LVLLVLO()
    {
    //
    }

bool LVLLVLO::operator ==(const LVLLVLO &other) const
    {
    return (level == other.level &&
            listId == other.listId &&
            count == other.count);
    }

bool LVLLVLO::operator !=(const LVLLVLO &other) const
    {
    return !(*this == other);
    }

MAGICOBME::MAGICOBME():
    recordVersion(0),
    betaVersion(0),
    minorVersion(0),
    majorVersion(0)
    {
    memset(&reserved, 0x00, 0x1C);
    }

MAGICOBME::~MAGICOBME()
    {
    //
    }

bool MAGICOBME::operator ==(const MAGICOBME &other) const
    {
    return (recordVersion == other.recordVersion &&
            betaVersion == other.betaVersion &&
            minorVersion == other.minorVersion &&
            majorVersion == other.majorVersion &&
            reserved == other.reserved);
    }

bool MAGICOBME::operator !=(const MAGICOBME &other) const
    {
    return !(*this == other);
    }

bool OBMEMAGIC::operator ==(const OBMEMAGIC &other) const
    {
    return (OBME == other.OBME &&
            DATX == other.DATX);
    }

bool OBMEMAGIC::operator !=(const OBMEMAGIC &other) const
    {
    return !(*this == other);
    }

GENMNAM::GENMNAM():
    dimX(0),
    dimY(0),
    NWCellX(0),
    NWCellY(0),
    SECellX(0),
    SECellY(0)
    {
    //
    }

GENMNAM::~GENMNAM()
    {
    //
    }

bool GENMNAM::operator ==(const GENMNAM &other) const
    {
    return (dimX == other.dimX &&
            dimY == other.dimY &&
            NWCellX == other.NWCellX &&
            NWCellY == other.NWCellY &&
            SECellX == other.SECellX &&
            SECellY == other.SECellY);
    }

bool GENMNAM::operator !=(const GENMNAM &other) const
    {
    return !(*this == other);
    }

GENNAM::GENNAM():
    x(0.0f),
    y(0.0f)
    {
    //
    }

GENNAM::~GENNAM()
    {
    //
    }

bool GENNAM::operator ==(const GENNAM &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2));
    }

bool GENNAM::operator !=(const GENNAM &other) const
    {
    return !(*this == other);
    }

GENTNAM::GENTNAM():
    markerType(0),
    unused1(0)
    {
    //
    }

GENTNAM::~GENTNAM()
    {
    //
    }

bool GENTNAM::operator ==(const GENTNAM &other) const
    {
    return (markerType == other.markerType);
    }

bool GENTNAM::operator !=(const GENTNAM &other) const
    {
    return !(*this == other);
    }
//Fallout New Vegas Chunks

GENOBND::GENOBND():
    x(0),
    y(0),
    z(0)
    {
    //
    }

GENOBND::~GENOBND()
    {
    //
    }

bool GENOBND::operator ==(const GENOBND &other) const
    {
    return (x == other.x &&
            y == other.y &&
            z == other.z);
    }

bool GENOBND::operator !=(const GENOBND &other) const
    {
    return !(*this == other);
    }

GENDODT::GENDODT():
    minWidth(0.0f),
    maxWidth(0.0f),
    minHeight(0.0f),
    maxHeight(0.0f),
    depth(0.0f),
    shininess(0.0f),
    scale(0.0f),
    passes(0),
    flags(0),
    red(0),
    green(0),
    blue(0),
    unused2(0x00)
    {
    memset(&unused1[0], 0x00, 2);
    }

GENDODT::~GENDODT()
    {
    //
    }

bool GENDODT::operator ==(const GENDODT &other) const
    {
    return (passes == other.passes &&
            flags == other.flags &&
            red == other.red &&
            green == other.green &&
            blue == other.blue &&
            AlmostEqual(minWidth,other.minWidth,2) &&
            AlmostEqual(maxWidth,other.maxWidth,2) &&
            AlmostEqual(minHeight,other.minHeight,2) &&
            AlmostEqual(maxHeight,other.maxHeight,2) &&
            AlmostEqual(depth,other.depth,2) &&
            AlmostEqual(shininess,other.shininess,2) &&
            AlmostEqual(scale,other.scale,2));
    }

bool GENDODT::operator !=(const GENDODT &other) const
    {
    return !(*this == other);
    }

bool GENDODT::IsParallax()
    {
    return (flags & fIsParallax) != 0;
    }

void GENDODT::IsParallax(bool value)
    {
    if(value)
        flags |= fIsParallax;
    else
        flags &= ~fIsParallax;
    }

bool GENDODT::IsAlphaBlending()
    {
    return (flags & fIsAlphaBlending) != 0;
    }

void GENDODT::IsAlphaBlending(bool value)
    {
    if(value)
        flags |= fIsAlphaBlending;
    else
        flags &= ~fIsAlphaBlending;
    }

bool GENDODT::IsAlphaTesting()
    {
    return (flags & fIsAlphaTesting) != 0;
    }

void GENDODT::IsAlphaTesting(bool value)
    {
    if(value)
        flags |= fIsAlphaTesting;
    else
        flags &= ~fIsAlphaTesting;
    }

bool GENDODT::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(Exact)
        return (flags & Mask) == Mask;
    else
        return (flags & Mask) != 0;
    }

void GENDODT::SetFlagMask(UINT8 Mask)
    {
    flags = Mask;
    }

bool GENPATROL::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void GENPATROL::IsScriptEnabled(bool value)
    {
    if(value)
        SCHR.value.flags |= fIsEnabled;
    else
        SCHR.value.flags &= ~fIsEnabled;
    }

bool GENPATROL::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    if(Exact)
        return (SCHR.value.flags & Mask) == Mask;
    else
        return (SCHR.value.flags & Mask) != 0;
    }

void GENPATROL::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

bool GENPATROL::operator ==(const GENPATROL &other) const
    {
    return (XPRD == other.XPRD &&
            Script == other.Script &&
            INAM == other.INAM &&
            TNAM == other.TNAM);
    }

bool GENPATROL::operator !=(const GENPATROL &other) const
    {
    return !(*this == other);
    }

bool GENXCLP::operator ==(const GENXCLP &other) const
    {
    return (start == other.start &&
            end == other.end);
    }

bool GENXCLP::operator !=(const GENXCLP &other) const
    {
    return !(*this == other);
    }

GLOBFNAM::GLOBFNAM():
    format('f')
    {
    //
    }

GLOBFNAM::~GLOBFNAM()
    {
    //
    }

bool GLOBFNAM::operator ==(const GLOBFNAM &other) const
    {
    return (format == other.format);
    }

bool GLOBFNAM::operator !=(const GLOBFNAM &other) const
    {
    return !(*this == other);
    }

bool FNVXNAM::IsNeutral()
    {
    return groupReactionType == eNeutral;
    }

void FNVXNAM::IsNeutral(bool value)
    {
    if(value)
        groupReactionType = eNeutral;
    else
        groupReactionType = eEnemy;
    }

bool FNVXNAM::IsEnemy()
    {
    return groupReactionType == eEnemy;
    }

void FNVXNAM::IsEnemy(bool value)
    {
    if(value)
        groupReactionType = eEnemy;
    else
        groupReactionType = eNeutral;
    }

bool FNVXNAM::IsAlly()
    {
    return groupReactionType == eAlly;
    }

void FNVXNAM::IsAlly(bool value)
    {
    if(value)
        groupReactionType = eAlly;
    else
        groupReactionType = eNeutral;
    }

bool FNVXNAM::IsFriend()
    {
    return groupReactionType == eFriend;
    }

void FNVXNAM::IsFriend(bool value)
    {
    if(value)
        groupReactionType = eFriend;
    else
        groupReactionType = eNeutral;
    }

bool FNVXNAM::IsType(UINT32 Type)
    {
    return groupReactionType == Type;
    }

void FNVXNAM::SetType(UINT32 Type)
    {
    groupReactionType = Mask;
    }