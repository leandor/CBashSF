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
    if((curFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        curFormID &= 0x00FFFFFF;
    else
        curFormID = (ResolveTable[curFormID >> 24] << 24 ) | (curFormID & 0x00FFFFFF);
    return stop;
    }

bool FormIDResolver::AcceptMGEF(UINT32 &curMgefCode)
    {
    curMgefCode = (ResolveTable[curMgefCode & 0x000000FF]) | (curMgefCode & 0xFFFFFF00);
    return stop;
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
    return (faction == other.faction &&
            mod == other.mod);
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
    memset(&unused1[0], 0x00, sizeof(unused1));
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

void GENSCR_::Write(FileWriter &writer)
    {
    writer.record_write_subrecord(isSCRO ? REV32(SCRO) : REV32(SCRV), &reference, sizeof(FORMID_OR_UINT32));
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

GENSLSD::GENSLSD():
    index(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unused2[0], 0x00, sizeof(unused2));
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

void GENVARS::Write(FileWriter &writer)
    {
    WRITE(SLSD);
    WRITE(SCVR);
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

bool sortVARS::operator()(const GENVARS *lhs, const GENVARS *rhs) const
    {
    return lhs->SLSD.value.index < rhs->SLSD.value.index;
    }

FNVSCHR::FNVSCHR():
    numRefs(0),
    compiledSize(0),
    lastIndex(0),
    scriptType(0), //Object
    flags(0x0001) //Enabled
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
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
    SCHR.value.flags = value ? (SCHR.value.flags | fIsEnabled) : (SCHR.value.flags & ~fIsEnabled);
    }

bool FNVMINSCRIPT::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (SCHR.value.flags & Mask) == Mask : (SCHR.value.flags & Mask) != 0;
    }

void FNVMINSCRIPT::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

bool FNVMINSCRIPT::IsType(UINT16 Type)
    {
    return SCHR.value.scriptType == Type;
    }

void FNVMINSCRIPT::SetType(UINT16 Type)
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
    memset(&unused1[0], 0x00, sizeof(unused1));
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
    memset(&reserved[0], 0x00, sizeof(reserved));
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
            reserved[0] == other.reserved[0] &&
            reserved[1] == other.reserved[1] &&
            reserved[2] == other.reserved[2] &&
            reserved[3] == other.reserved[3] &&
            reserved[4] == other.reserved[4] &&
            reserved[5] == other.reserved[5] &&
            reserved[6] == other.reserved[6] &&
            reserved[7] == other.reserved[7] &&
            reserved[8] == other.reserved[8] &&
            reserved[9] == other.reserved[9]);
    }

bool OBMEEFME::operator !=(const OBMEEFME &other) const
    {
    return !(*this == other);
    }

OBMEEFIX::OBMEEFIX():
    efixOverrides(0),
    efixFlags(0),
    baseCost(0.0f),
    resistAV(0)
    {
    memset(&reserved[0], 0x00, sizeof(reserved));
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
            reserved[0] == other.reserved[0] &&
            reserved[1] == other.reserved[1] &&
            reserved[2] == other.reserved[2] &&
            reserved[3] == other.reserved[3] &&
            reserved[4] == other.reserved[4] &&
            reserved[5] == other.reserved[5] &&
            reserved[6] == other.reserved[6] &&
            reserved[7] == other.reserved[7] &&
            reserved[8] == other.reserved[8] &&
            reserved[9] == other.reserved[9] &&
            reserved[10] == other.reserved[10] &&
            reserved[11] == other.reserved[11] &&
            reserved[12] == other.reserved[12] &&
            reserved[13] == other.reserved[13] &&
            reserved[14] == other.reserved[14] &&
            reserved[15] == other.reserved[15]);
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
    SCIT->flags = value ? (SCIT->flags | fIsHostile) : (SCIT->flags & ~fIsHostile);
    }

bool GENEffect::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!SCIT.IsLoaded()) return false;
    return Exact ? (SCIT->flags & Mask) == Mask : (SCIT->flags & Mask) != 0;
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
    EFIT.value.rangeType = value ? eRangeSelf : eRangeTouch;
    }

bool GENEffect::IsRangeTouch()
    {
    return (EFIT.value.rangeType == eRangeTouch);
    }

void GENEffect::IsRangeTouch(bool value)
    {
    EFIT.value.rangeType = value ? eRangeTouch : eRangeSelf;
    }

bool GENEffect::IsRangeTarget()
    {
    return (EFIT.value.rangeType == eRangeTarget);
    }

void GENEffect::IsRangeTarget(bool value)
    {
    EFIT.value.rangeType = value ? eRangeTarget : eRangeSelf;
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
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingHostileOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingHostileOverride);
    }

bool GENEffect::OBME_IsUsingRecoversOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingRecoversOverride) != 0;
    }

void GENEffect::OBME_IsUsingRecoversOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingRecoversOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingRecoversOverride);
    }

bool GENEffect::OBME_IsUsingParamFlagAOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingParamFlagAOverride) != 0;
    }

void GENEffect::OBME_IsUsingParamFlagAOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingParamFlagAOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingParamFlagAOverride);
    }

bool GENEffect::OBME_IsUsingBeneficialOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingBeneficialOverride) != 0;
    }

void GENEffect::OBME_IsUsingBeneficialOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingBeneficialOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingBeneficialOverride);
    }

bool GENEffect::OBME_IsUsingEFIXParamOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingEFIXParamOverride) != 0;
    }

void GENEffect::OBME_IsUsingEFIXParamOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingEFIXParamOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingEFIXParamOverride);
    }

bool GENEffect::OBME_IsUsingSchoolOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingSchoolOverride) != 0;
    }

void GENEffect::OBME_IsUsingSchoolOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingSchoolOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingSchoolOverride);
    }

bool GENEffect::OBME_IsUsingNameOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingNameOverride) != 0;
    }

void GENEffect::OBME_IsUsingNameOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingNameOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingNameOverride);
    }

bool GENEffect::OBME_IsUsingVFXCodeOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingVFXCodeOverride) != 0;
    }

void GENEffect::OBME_IsUsingVFXCodeOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingVFXCodeOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingVFXCodeOverride);
    }

bool GENEffect::OBME_IsUsingBaseCostOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingBaseCostOverride) != 0;
    }

void GENEffect::OBME_IsUsingBaseCostOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingBaseCostOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingBaseCostOverride);
    }

bool GENEffect::OBME_IsUsingResistAVOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingResistAVOverride) != 0;
    }

void GENEffect::OBME_IsUsingResistAVOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingResistAVOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingResistAVOverride);
    }

bool GENEffect::OBME_IsUsingFXPersistsOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingFXPersistsOverride) != 0;
    }

void GENEffect::OBME_IsUsingFXPersistsOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingFXPersistsOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingFXPersistsOverride);
    }

bool GENEffect::OBME_IsUsingIconOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingIconOverride) != 0;
    }

void GENEffect::OBME_IsUsingIconOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingIconOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingIconOverride);
    }

bool GENEffect::OBME_IsUsingDoesntTeachOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingDoesntTeachOverride) != 0;
    }

void GENEffect::OBME_IsUsingDoesntTeachOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingDoesntTeachOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingDoesntTeachOverride);
    }

bool GENEffect::OBME_IsUsingUnknownFOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingUnknownFOverride) != 0;
    }

void GENEffect::OBME_IsUsingUnknownFOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingUnknownFOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingUnknownFOverride);
    }

bool GENEffect::OBME_IsUsingNoRecastOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingNoRecastOverride) != 0;
    }

void GENEffect::OBME_IsUsingNoRecastOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingNoRecastOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingNoRecastOverride);
    }

bool GENEffect::OBME_IsUsingParamFlagBOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingParamFlagBOverride) != 0;
    }

void GENEffect::OBME_IsUsingParamFlagBOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingParamFlagBOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingParamFlagBOverride);
    }

bool GENEffect::OBME_IsUsingMagnitudeIsRangeOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingMagnitudeIsRangeOverride) != 0;
    }

void GENEffect::OBME_IsUsingMagnitudeIsRangeOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingMagnitudeIsRangeOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingMagnitudeIsRangeOverride);
    }

bool GENEffect::OBME_IsUsingAtomicResistanceOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingAtomicResistanceOverride) != 0;
    }

void GENEffect::OBME_IsUsingAtomicResistanceOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingAtomicResistanceOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingAtomicResistanceOverride);
    }

bool GENEffect::OBME_IsUsingParamFlagCOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingParamFlagCOverride) != 0;
    }

void GENEffect::OBME_IsUsingParamFlagCOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingParamFlagCOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingParamFlagCOverride);
    }

bool GENEffect::OBME_IsUsingParamFlagDOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingParamFlagDOverride) != 0;
    }

void GENEffect::OBME_IsUsingParamFlagDOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingParamFlagDOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingParamFlagDOverride);
    }

bool GENEffect::OBME_IsUsingDisabledOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingDisabledOverride) != 0;
    }

void GENEffect::OBME_IsUsingDisabledOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingDisabledOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingDisabledOverride);
    }

bool GENEffect::OBME_IsUsingUnknownOOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingUnknownOOverride) != 0;
    }

void GENEffect::OBME_IsUsingUnknownOOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingUnknownOOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingUnknownOOverride);
    }

bool GENEffect::OBME_IsUsingNoHitEffectOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingNoHitEffectOverride) != 0;
    }

void GENEffect::OBME_IsUsingNoHitEffectOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingNoHitEffectOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingNoHitEffectOverride);
    }

bool GENEffect::OBME_IsUsingPersistOnDeathOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingPersistOnDeathOverride) != 0;
    }

void GENEffect::OBME_IsUsingPersistOnDeathOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingPersistOnDeathOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingPersistOnDeathOverride);
    }

bool GENEffect::OBME_IsUsingExplodesWithForceOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingExplodesWithForceOverride) != 0;
    }

void GENEffect::OBME_IsUsingExplodesWithForceOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingExplodesWithForceOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingExplodesWithForceOverride);
    }

bool GENEffect::OBME_IsUsingHiddenOverride()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixOverrides & fOBME_IsUsingHiddenOverride) != 0;
    }

void GENEffect::OBME_IsUsingHiddenOverride(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixOverrides = value ? (OBME->EFIX->efixOverrides | fOBME_IsUsingHiddenOverride) : (OBME->EFIX->efixOverrides & ~fOBME_IsUsingHiddenOverride);
    }

bool GENEffect::OBME_IsOverrideFlagMask(UINT32 Mask, bool Exact)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return Exact ? (OBME->EFIX->efixOverrides & Mask) == Mask : (OBME->EFIX->efixOverrides & Mask) != 0;
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
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsHostile) : (OBME->EFIX->efixFlags & ~fOBME_IsHostile);
    }

bool GENEffect::OBME_IsRecovers()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsRecovers) != 0;
    }

void GENEffect::OBME_IsRecovers(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsRecovers) : (OBME->EFIX->efixFlags & ~fOBME_IsRecovers);
    }

bool GENEffect::OBME_IsParamFlagA()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsParamFlagA) != 0;
    }

void GENEffect::OBME_IsParamFlagA(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsParamFlagA) : (OBME->EFIX->efixFlags & ~fOBME_IsParamFlagA);
    }

bool GENEffect::OBME_IsBeneficial()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsBeneficial) != 0;
    }

void GENEffect::OBME_IsBeneficial(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsBeneficial) : (OBME->EFIX->efixFlags & ~fOBME_IsBeneficial);
    }

bool GENEffect::OBME_IsFXPersists()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsFXPersists) != 0;
    }

void GENEffect::OBME_IsFXPersists(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsFXPersists) : (OBME->EFIX->efixFlags & ~fOBME_IsFXPersists);
    }

bool GENEffect::OBME_IsUnknownF()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsUnknownF) != 0;
    }

void GENEffect::OBME_IsUnknownF(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsUnknownF) : (OBME->EFIX->efixFlags & ~fOBME_IsUnknownF);
    }

bool GENEffect::OBME_IsNoRecast()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsNoRecast) != 0;
    }

void GENEffect::OBME_IsNoRecast(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsNoRecast) : (OBME->EFIX->efixFlags & ~fOBME_IsNoRecast);
    }

bool GENEffect::OBME_IsParamFlagB()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsParamFlagB) != 0;
    }

void GENEffect::OBME_IsParamFlagB(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsParamFlagB) : (OBME->EFIX->efixFlags & ~fOBME_IsParamFlagB);
    }

bool GENEffect::OBME_IsMagnitudeIsRange()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsMagnitudeIsRange) != 0;
    }

void GENEffect::OBME_IsMagnitudeIsRange(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsMagnitudeIsRange) : (OBME->EFIX->efixFlags & ~fOBME_IsMagnitudeIsRange);
    }

bool GENEffect::OBME_IsAtomicResistance()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsAtomicResistance) != 0;
    }

void GENEffect::OBME_IsAtomicResistance(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsAtomicResistance) : (OBME->EFIX->efixFlags & ~fOBME_IsAtomicResistance);
    }

bool GENEffect::OBME_IsParamFlagC()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsParamFlagC) != 0;
    }

void GENEffect::OBME_IsParamFlagC(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsParamFlagC) : (OBME->EFIX->efixFlags & ~fOBME_IsParamFlagC);
    }

bool GENEffect::OBME_IsParamFlagD()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsParamFlagD) != 0;
    }

void GENEffect::OBME_IsParamFlagD(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsParamFlagD) : (OBME->EFIX->efixFlags & ~fOBME_IsParamFlagD);
    }

bool GENEffect::OBME_IsDisabled()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsDisabled) != 0;
    }

void GENEffect::OBME_IsDisabled(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsDisabled) : (OBME->EFIX->efixFlags & ~fOBME_IsDisabled);
    }

bool GENEffect::OBME_IsUnknownO()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsUnknownO) != 0;
    }

void GENEffect::OBME_IsUnknownO(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsUnknownO) : (OBME->EFIX->efixFlags & ~fOBME_IsUnknownO);
    }

bool GENEffect::OBME_IsNoHitEffect()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsNoHitEffect) != 0;
    }

void GENEffect::OBME_IsNoHitEffect(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsNoHitEffect) : (OBME->EFIX->efixFlags & ~fOBME_IsNoHitEffect);
    }

bool GENEffect::OBME_IsPersistOnDeath()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsPersistOnDeath) != 0;
    }

void GENEffect::OBME_IsPersistOnDeath(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsPersistOnDeath) : (OBME->EFIX->efixFlags & ~fOBME_IsPersistOnDeath);
    }

bool GENEffect::OBME_IsExplodesWithForce()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsExplodesWithForce) != 0;
    }

void GENEffect::OBME_IsExplodesWithForce(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsExplodesWithForce) : (OBME->EFIX->efixFlags & ~fOBME_IsExplodesWithForce);
    }

bool GENEffect::OBME_IsHidden()
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return (OBME->EFIX->efixFlags & fOBME_IsHidden) != 0;
    }

void GENEffect::OBME_IsHidden(bool value)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return;
    OBME->EFIX->efixFlags = value ? (OBME->EFIX->efixFlags | fOBME_IsHidden) : (OBME->EFIX->efixFlags & ~fOBME_IsHidden);
    }

bool GENEffect::OBME_IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!OBME.IsLoaded() || !OBME->EFIX.IsLoaded()) return false;
    return Exact ? (OBME->EFIX->efixFlags & Mask) == Mask : (OBME->EFIX->efixFlags & Mask) != 0;
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
    memset(&unused1[0], 0x00, sizeof(unused1));
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
    memset(&unused1[0], 0x00, sizeof(unused1));
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
    memset(&unused1[0], 0x00, sizeof(unused1));
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
    operType = value ? (operType | fIsOr) : (operType & ~fIsOr);
    }

bool GENCTDA::IsRunOnTarget()
    {
    return ((operType & 0x0F) & fIsRunOnTarget) != 0;
    }

void GENCTDA::IsRunOnTarget(bool value)
    {
    operType = value ? (operType | fIsRunOnTarget) : (operType & ~fIsRunOnTarget);
    }

bool GENCTDA::IsUseGlobal()
    {
    return ((operType & 0x0F) & fIsUseGlobal) != 0;
    }

void GENCTDA::IsUseGlobal(bool value)
    {
    operType = value ? (operType | fIsUseGlobal) : (operType & ~fIsUseGlobal);
    }

bool GENCTDA::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((operType & 0x0F) & (Mask & 0x0F)) == Mask : ((operType & 0x0F) & (Mask & 0x0F)) != 0;
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
            AlmostEqual(lod3,other.lod3,2));
    }

bool GENXLOD::operator !=(const GENXLOD &other) const
    {
    return !(*this == other);
    }

GENXESP::GENXESP():
    parent(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
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
            AlmostEqual(rotZ,other.rotZ,2));
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
    memset(&unused1[0], 0x00, sizeof(unused1));
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
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unused2[0], 0x00, sizeof(unused2));
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
    memset(&reserved[0], 0x00, sizeof(reserved));
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
            reserved[0] == other.reserved[0] &&
            reserved[1] == other.reserved[1] &&
            reserved[2] == other.reserved[2] &&
            reserved[3] == other.reserved[3] &&
            reserved[4] == other.reserved[4] &&
            reserved[5] == other.reserved[5] &&
            reserved[6] == other.reserved[6] &&
            reserved[7] == other.reserved[7] &&
            reserved[8] == other.reserved[8] &&
            reserved[9] == other.reserved[9] &&
            reserved[10] == other.reserved[10] &&
            reserved[11] == other.reserved[11] &&
            reserved[12] == other.reserved[12] &&
            reserved[13] == other.reserved[13] &&
            reserved[14] == other.reserved[14] &&
            reserved[15] == other.reserved[15] &&
            reserved[16] == other.reserved[16] &&
            reserved[17] == other.reserved[17] &&
            reserved[18] == other.reserved[18] &&
            reserved[19] == other.reserved[19] &&
            reserved[20] == other.reserved[20] &&
            reserved[21] == other.reserved[21] &&
            reserved[22] == other.reserved[22] &&
            reserved[23] == other.reserved[23] &&
            reserved[24] == other.reserved[24] &&
            reserved[25] == other.reserved[25] &&
            reserved[26] == other.reserved[26] &&
            reserved[27] == other.reserved[27]);
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

GENNAM0::GENNAM0():
    x(flt_max),
    y(flt_max)
    {
    //
    }

GENNAM0::~GENNAM0()
    {
    //
    }

bool GENNAM0::operator ==(const GENNAM0 &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2));
    }

bool GENNAM0::operator !=(const GENNAM0 &other) const
    {
    return !(*this == other);
    }

GENNAM9::GENNAM9():
    x(flt_max),
    y(flt_max)
    {
    //For whatever reason, the CS defaults these two to an invalid float
    memset(&((unsigned char *)&x)[3], 0xFF, 1);
    memset(&((unsigned char *)&y)[3], 0xFF, 1);
    }

GENNAM9::~GENNAM9()
    {
    //
    }

bool GENNAM9::operator ==(const GENNAM9 &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2));
    }

bool GENNAM9::operator !=(const GENNAM9 &other) const
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

RACESKILL::RACESKILL():
    value(-1),
    boost(0)
    {
    //
    }

RACESKILL::~RACESKILL()
    {
    //
    }

bool RACESKILL::operator ==(const RACESKILL &other) const
    {
    return (value == other.value &&
            boost == other.boost);
    }

bool RACESKILL::operator !=(const RACESKILL &other) const
    {
    return !(*this == other);
    }

RACEDATA::RACEDATA():
    maleHeight(1.0f),
    femaleHeight(1.0f),
    maleWeight(1.0f),
    femaleWeight(1.0f),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

RACEDATA::~RACEDATA()
    {
    //
    }

bool RACEDATA::operator ==(const RACEDATA &other) const
    {
    return (skills[0] == other.skills[0] &&
            skills[1] == other.skills[1] &&
            skills[2] == other.skills[2] &&
            skills[3] == other.skills[3] &&
            skills[4] == other.skills[4] &&
            skills[5] == other.skills[5] &&
            skills[6] == other.skills[6] &&
            AlmostEqual(maleHeight,other.maleHeight,2) &&
            AlmostEqual(femaleHeight,other.femaleHeight,2) &&
            AlmostEqual(maleWeight,other.maleWeight,2) &&
            AlmostEqual(femaleWeight,other.femaleWeight,2) &&
            flags == other.flags);
    }

bool RACEDATA::operator !=(const RACEDATA &other) const
    {
    return !(*this == other);
    }

RACESNAM::RACESNAM()
    {
    memset(&SNAM[0], 0x00, sizeof(SNAM));
    }

RACESNAM::~RACESNAM()
    {
    //
    }

bool RACESNAM::operator ==(const RACESNAM &other) const
    {
    return (SNAM[0] == other.SNAM[0] &&
            SNAM[1] == other.SNAM[1]);
    }

bool RACESNAM::operator !=(const RACESNAM &other) const
    {
    return !(*this == other);
    }

RACEVNAM::RACEVNAM():
    maleVoice(0),
    femaleVoice(0)
    {
    //
    }

RACEVNAM::~RACEVNAM()
    {
    //
    }

bool RACEVNAM::operator ==(const RACEVNAM &other) const
    {
    return (maleVoice == other.maleVoice &&
            femaleVoice == other.femaleVoice);
    }

bool RACEVNAM::operator !=(const RACEVNAM &other) const
    {
    return !(*this == other);
    }

RACEDNAM::RACEDNAM():
    defaultHairMale(0),
    defaultHairFemale(0)
    {
    //
    }

RACEDNAM::~RACEDNAM()
    {
    //
    }

bool RACEDNAM::operator ==(const RACEDNAM &other) const
    {
    return (defaultHairMale == other.defaultHairMale &&
            defaultHairFemale == other.defaultHairFemale);
    }

bool RACEDNAM::operator !=(const RACEDNAM &other) const
    {
    return !(*this == other);
    }

RACECNAM::RACECNAM():
    defaultHairMale(0),
    defaultHairFemale(0)
    {
    //
    }

RACECNAM::~RACECNAM()
    {
    //
    }

bool RACECNAM::operator ==(const RACECNAM &other) const
    {
    return (defaultHairMale == other.defaultHairMale &&
            defaultHairFemale == other.defaultHairFemale);
    }

bool RACECNAM::operator !=(const RACECNAM &other) const
    {
    return !(*this == other);
    }

//Fallout New Vegas Chunks
GENOBND::GENOBND():
    x1(0),
    y1(0),
    z1(0),
    x2(0),
    y2(0),
    z2(0)
    {
    //
    }

GENOBND::~GENOBND()
    {
    //
    }

bool GENOBND::operator ==(const GENOBND &other) const
    {
    return (x1 == other.x1 &&
            y1 == other.y1 &&
            z1 == other.z1 &&
            x2 == other.x2 &&
            y2 == other.y2 &&
            z2 == other.z2);
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
    unused2(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
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

bool GENPATROL::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void GENPATROL::IsScriptEnabled(bool value)
    {
    SCHR.value.flags = value ? (SCHR.value.flags | fIsEnabled) : (SCHR.value.flags & ~fIsEnabled);
    }

bool GENPATROL::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (SCHR.value.flags & Mask) == Mask : (SCHR.value.flags & Mask) != 0;
    }

void GENPATROL::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

bool GENPATROL::IsObject()
    {
    return SCHR.value.scriptType == eObject;
    }

void GENPATROL::IsObject(bool value)
    {
    SCHR.value.scriptType = value ? eObject : eQuest;
    }

bool GENPATROL::IsQuest()
    {
    return SCHR.value.scriptType == eQuest;
    }

void GENPATROL::IsQuest(bool value)
    {
    SCHR.value.scriptType = value ? eQuest : eObject;
    }

bool GENPATROL::IsEffect()
    {
    return SCHR.value.scriptType == eEffect;
    }

void GENPATROL::IsEffect(bool value)
    {
    SCHR.value.scriptType = value ? eEffect : eObject;
    }

bool GENPATROL::IsType(UINT16 Type)
    {
    return SCHR.value.scriptType == Type;
    }

void GENPATROL::SetType(UINT16 Type)
    {
    SCHR.value.scriptType = Type;
    }

void GENPATROL::Write(FileWriter &writer)
    {
    WRITE(XPRD);
    WRITEEMPTY(XPPA);
    WRITE(INAM);
    SCHR.value.numRefs = SCR_.value.size(); //Just to ensure that the value is correct
    SCHR.value.compiledSize = SCDA.GetSize(); //Just to ensure that the value is correct
    //for(UINT32 x = 0; x < VARS.value.size(); ++x) //Just to ensure that the value is correct
    //    SCHR.value.lastIndex = (SCHR.value.lastIndex > VARS.value[x]->SLSD.value.index) ? SCHR.value.lastIndex : VARS.value[x]->SLSD.value.index;
    WRITE(SCHR);
    WRITE(SCDA);
    WRITE(SCTX);
    VARS.Write(writer);
    SCR_.Write(writer, true);
    WRITE(TNAM);
    }

bool GENPATROL::operator ==(const GENPATROL &other) const
    {
    return (XPRD == other.XPRD &&
            SCHR == other.SCHR &&
            INAM == other.INAM &&
            TNAM == other.TNAM &&
            SCDA == other.SCDA &&
            SCTX.equalsi(other.SCTX) &&
            VARS == other.VARS &&
            SCR_ == other.SCR_);
    }
bool GENPATROL::operator !=(const GENPATROL &other) const
    {
    return !(*this == other);
    }

FNVXNAM::FNVXNAM():
    faction(0),
    mod(0),
    groupReactionType(0)
    {
    //
    }

FNVXNAM::~FNVXNAM()
    {
    //
    }

bool FNVXNAM::IsNeutral()
    {
    return groupReactionType == eNeutral;
    }

void FNVXNAM::IsNeutral(bool value)
    {
    groupReactionType = value ? eNeutral : eEnemy;
    }

bool FNVXNAM::IsEnemy()
    {
    return groupReactionType == eEnemy;
    }

void FNVXNAM::IsEnemy(bool value)
    {
    groupReactionType = value ? eEnemy : eNeutral;
    }

bool FNVXNAM::IsAlly()
    {
    return groupReactionType == eAlly;
    }

void FNVXNAM::IsAlly(bool value)
    {
    groupReactionType = value ? eAlly : eNeutral;
    }

bool FNVXNAM::IsFriend()
    {
    return groupReactionType == eFriend;
    }

void FNVXNAM::IsFriend(bool value)
    {
    groupReactionType = value ? eFriend : eNeutral;
    }

bool FNVXNAM::IsType(UINT32 Type)
    {
    return groupReactionType == Type;
    }

void FNVXNAM::SetType(UINT32 Type)
    {
    groupReactionType = Type;
    }

bool FNVXNAM::operator ==(const FNVXNAM &other) const
    {
    return (faction == other.faction &&
            mod == other.mod &&
            groupReactionType == other.groupReactionType);
    }

bool FNVXNAM::operator !=(const FNVXNAM &other) const
    {
    return !(*this == other);
    }

FNVMODS::FNVMODS():
    name(NULL),
    texture(0),
    index(0)
    {
    //
    }

FNVMODS::~FNVMODS()
    {
    delete []name;
    }

bool FNVMODS::operator ==(const FNVMODS &other) const
    {
    return (texture == other.texture &&
            index == other.index &&
            icmps(name, other.name) == 0);
    }

bool FNVMODS::operator !=(const FNVMODS &other) const
    {
    return !(*this == other);
    }

FNVAlternateTextures::FNVAlternateTextures()
    {
    //
    }

FNVAlternateTextures::~FNVAlternateTextures()
    {
    Unload();
    }

UINT32 FNVAlternateTextures::GetSize() const
    {
    if(MODS.size())
        {
        UINT32 cSize = 4; // num elements field
        for(UINT32 x = 0; x < MODS.size(); ++x)
            {
            cSize += 12; // string size, New Texture, 3D Index fields
            if(MODS[x]->name != NULL)
                cSize += (UINT32)strlen(MODS[x]->name);
            }
        return cSize;
        }
    return 0;
    }

bool FNVAlternateTextures::IsLoaded() const
    {
    return (MODS.size() != 0);
    }

void FNVAlternateTextures::Load()
    {
    //
    }

void FNVAlternateTextures::Unload()
    {
    for(UINT32 x = 0; x < MODS.size(); ++x)
        delete MODS[x];
    MODS.clear();
    }

void FNVAlternateTextures::resize(UINT32 newSize)
    {
    //Shrink
    UINT32 size = MODS.size();
    for(; size > newSize;)
        delete MODS[--size];
    MODS.resize(newSize);
    //Grow
    for(; size < newSize;)
        MODS[size++] = new FNVMODS;
    }

bool FNVAlternateTextures::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(MODS.size() != 0)
        {
        curPos += subSize;
        return false;
        }
    UINT32 numElements = 0;
    UINT32 sizeString = 0;
    memcpy(&numElements, buffer + curPos, 4);
    curPos += 4;
    for(UINT32 x = 0; x < numElements; ++x)
        {
        MODS.push_back(new FNVMODS);
        memcpy(&sizeString, buffer + curPos, 4);
        curPos += 4;
        if(sizeString > 0)
            {
            MODS.back()->name = new char[sizeString + 1];
            MODS.back()->name[sizeString] = 0x00;
            memcpy(MODS.back()->name, buffer + curPos, sizeString);
            curPos += sizeString;
            }
        memcpy(&MODS.back()->texture, buffer + curPos, 4);
        curPos += 4;
        memcpy(&MODS.back()->index, buffer + curPos, 4);
        curPos += 4;
        }
    return true;
    }

void FNVAlternateTextures::Write(FileWriter &writer)
    {
    UINT32 cSize = MODS.size();
    if(cSize)
        {
        writer.record_write_subheader(REV32(MODS), GetSize());
        writer.record_write(&cSize, 4);
        for(UINT32 p = 0; p < MODS.size(); ++p)
            {
            if(MODS[p]->name != NULL)
                {
                cSize = (UINT32)strlen(MODS[p]->name);
                writer.record_write(&cSize, 4);
                writer.record_write(MODS[p]->name, cSize);
                }
            writer.record_write(&MODS[p]->texture, 4);
            writer.record_write(&MODS[p]->index, 4);
            }
       }
    }

void FNVAlternateTextures::Write(UINT32 _Type, FileWriter &writer)
    {
    UINT32 cSize = MODS.size();
    if(cSize)
        {
        writer.record_write_subheader(_Type, GetSize());
        writer.record_write(&cSize, 4);
        for(UINT32 p = 0; p < MODS.size(); ++p)
            {
            if(MODS[p]->name != NULL)
                {
                cSize = (UINT32)strlen(MODS[p]->name);
                writer.record_write(&cSize, 4);
                writer.record_write(MODS[p]->name, cSize);
                }
            writer.record_write(&MODS[p]->texture, 4);
            writer.record_write(&MODS[p]->index, 4);
            }
       }
    }

FNVAlternateTextures& FNVAlternateTextures::operator = (const FNVAlternateTextures &rhs)
    {
    if(this != &rhs)
        {
        if(rhs.MODS.size() != 0)
            {
            Unload();
            MODS.resize(rhs.MODS.size());
            UINT32 nameSize = 0;
            for(UINT32 p = 0; p < rhs.MODS.size(); p++)
                {
                MODS[p] = new FNVMODS;
                if(rhs.MODS[p]->name != NULL)
                    {
                    nameSize = (UINT32)strlen(rhs.MODS[p]->name) + 1;
                    MODS[p]->name = new char[nameSize];
                    strcpy_s(MODS[p]->name, nameSize, rhs.MODS[p]->name);
                    }
                MODS[p]->texture = rhs.MODS[p]->texture;
                MODS[p]->index = rhs.MODS[p]->index;
                }
            }
        else
            Unload();
        }
    return *this;
    }

bool FNVAlternateTextures::operator ==(const FNVAlternateTextures &other) const
    {
    if(MODS.size() == other.MODS.size())
        {
        //Not sure if record order matters on alternate textures, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < MODS.size(); ++x)
            if(*MODS[x] != *other.MODS[x])
                return false;
        return true;
        }
    return false;
    }

bool FNVAlternateTextures::operator !=(const FNVAlternateTextures &other) const
    {
    return !(*this == other);
    }

FNVMODEL::FNVMODEL()
    {
    //
    }

FNVMODEL::~FNVMODEL()
    {
    //
    }

bool FNVMODEL::IsHead()
    {
    return (MODD.value & fIsHead) != 0;
    }

void FNVMODEL::IsHead(bool value)
    {
    MODD.value = value ? (MODD.value | fIsHead) : (MODD.value & ~fIsHead);
    }

bool FNVMODEL::IsTorso()
    {
    return (MODD.value & fIsTorso) != 0;
    }

void FNVMODEL::IsTorso(bool value)
    {
    MODD.value = value ? (MODD.value | fIsTorso) : (MODD.value & ~fIsTorso);
    }

bool FNVMODEL::IsRightHand()
    {
    return (MODD.value & fIsRightHand) != 0;
    }

void FNVMODEL::IsRightHand(bool value)
    {
    MODD.value = value ? (MODD.value | fIsRightHand) : (MODD.value & ~fIsRightHand);
    }

bool FNVMODEL::IsLeftHand()
    {
    return (MODD.value & fIsLeftHand) != 0;
    }

void FNVMODEL::IsLeftHand(bool value)
    {
    MODD.value = value ? (MODD.value | fIsLeftHand) : (MODD.value & ~fIsLeftHand);
    }

bool FNVMODEL::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((MODD.value & Mask) == Mask) : ((MODD.value & Mask) != 0);
    }

void FNVMODEL::SetFlagMask(UINT8 Mask)
    {
    MODD.value = Mask;
    }

void FNVMODEL::Write(FileWriter &writer)
    {
    WRITE(MODL);
    WRITE(MODB);
    WRITE(MODT);
    Textures.Write(writer);
    WRITE(MODD);
    }

bool FNVMODEL::operator ==(const FNVMODEL &other) const
    {
    return (MODB == other.MODB &&
            MODD == other.MODD &&
            MODL.equalsi(other.MODL) &&
            MODT == other.MODT &&
            Textures == other.Textures);
    }

bool FNVMODEL::operator !=(const FNVMODEL &other) const
    {
    return !(*this == other);
    }

bool FNVBIPEDMODEL::IsHead()
    {
    return (MODD.value & fIsHead) != 0;
    }

void FNVBIPEDMODEL::IsHead(bool value)
    {
    MODD.value = value ? (MODD.value | fIsHead) : (MODD.value & ~fIsHead);
    }

bool FNVBIPEDMODEL::IsTorso()
    {
    return (MODD.value & fIsTorso) != 0;
    }

void FNVBIPEDMODEL::IsTorso(bool value)
    {
    MODD.value = value ? (MODD.value | fIsTorso) : (MODD.value & ~fIsTorso);
    }

bool FNVBIPEDMODEL::IsRightHand()
    {
    return (MODD.value & fIsRightHand) != 0;
    }

void FNVBIPEDMODEL::IsRightHand(bool value)
    {
    MODD.value = value ? (MODD.value | fIsRightHand) : (MODD.value & ~fIsRightHand);
    }

bool FNVBIPEDMODEL::IsLeftHand()
    {
    return (MODD.value & fIsLeftHand) != 0;
    }

void FNVBIPEDMODEL::IsLeftHand(bool value)
    {
    MODD.value = value ? (MODD.value | fIsLeftHand) : (MODD.value & ~fIsLeftHand);
    }

bool FNVBIPEDMODEL::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((MODD.value & Mask) == Mask) : ((MODD.value & Mask) != 0);
    }

void FNVBIPEDMODEL::SetFlagMask(UINT8 Mask)
    {
    MODD.value = Mask;
    }

void FNVBIPEDMODEL::Write(FileWriter &writer)
    {
    WRITE(MODL);
    WRITE(MODT);
    Textures.Write(writer);
    WRITE(MODD);
    }

bool FNVBIPEDMODEL::operator ==(const FNVBIPEDMODEL &other) const
    {
    return (MODD == other.MODD &&
            MODL.equalsi(other.MODL) &&
            MODT == other.MODT &&
            Textures == other.Textures);
    }

bool FNVBIPEDMODEL::operator !=(const FNVBIPEDMODEL &other) const
    {
    return !(*this == other);
    }

void FNVWORLDMODEL::Write(FileWriter &writer)
    {
    WRITE(MODL);
    WRITE(MODT);
    Textures.Write(writer);
    }

bool FNVWORLDMODEL::operator ==(const FNVWORLDMODEL &other) const
    {
    return (MODL.equalsi(other.MODL) &&
            MODT == other.MODT &&
            Textures == other.Textures);
    }

bool FNVWORLDMODEL::operator !=(const FNVWORLDMODEL &other) const
    {
    return !(*this == other);
    }


bool FNVCTDA::VisitFormIDs(FormIDOp &op)
    {
    Function_Arguments_Iterator curCTDAFunction;

    if(IsUseGlobal())
        op.Accept(compValue);

    curCTDAFunction = FNVFunction_Arguments.find(ifunc);
    if(curCTDAFunction != FNVFunction_Arguments.end())
        {
        const FunctionArguments &CTDAFunction = curCTDAFunction->second;
        if(CTDAFunction.first == eFORMID)
            op.Accept(param1);
        if(CTDAFunction.second == eFORMID)
            op.Accept(param2);
        else if(CTDAFunction.second == eVATSPARAM)
            {
            if(param1 < VATSFUNCTIONSIZE)
                {
                if(VATSFunction_Argument[param1] == eFORMID)
                    op.Accept(param2);
                }
            else
                printer("Warning: CTDA uses an unknown VATS function (%d)!\n", param1);
            }
        }
    else
        printer("Warning: CTDA uses an unknown function (%d)!\n", ifunc);

    if(IsResultOnReference())
        op.Accept(reference);
    return op.Stop();
    }

FNVCTDA::FNVCTDA():
    operType(0),
    compValue(0),
    ifunc(5), //GetLocked, for its eNone, eNone param types...so that new conditions don't try to resolve either param1 or param2 until ifunc is set
    param1(0),
    param2(0),
    runOnType(0),
    reference(0)
    {
    memset(&unused1, 0x00, 3);
    }

FNVCTDA::~FNVCTDA()
    {
    //
    }

bool FNVCTDA::operator ==(const FNVCTDA &other) const
    {
    return (operType == other.operType &&
            (IsUseGlobal() ? compValue == other.compValue : AlmostEqual(*(FLOAT32 *)&compValue,*(FLOAT32 *)&other.compValue,2)) &&
            ifunc == other.ifunc &&
            param1 == other.param1 &&
            param2 == other.param2 &&
            runOnType == other.runOnType &&
            reference == other.reference);
    }

bool FNVCTDA::operator !=(const FNVCTDA &other) const
    {
    return !(*this == other);
    }

bool FNVCTDA::IsEqual()
    {
    return ((operType & 0xF0) == eEqual);
    }

void FNVCTDA::IsEqual(bool value)
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

bool FNVCTDA::IsNotEqual()
    {
    return ((operType & 0xF0) == eNotEqual);
    }

void FNVCTDA::IsNotEqual(bool value)
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

bool FNVCTDA::IsGreater()
    {
    return ((operType & 0xF0) == eGreater);
    }

void FNVCTDA::IsGreater(bool value)
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

bool FNVCTDA::IsGreaterOrEqual()
    {
    return ((operType & 0xF0) == eGreaterOrEqual);
    }

void FNVCTDA::IsGreaterOrEqual(bool value)
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

bool FNVCTDA::IsLess()
    {
    return ((operType & 0xF0) == eLess);
    }

void FNVCTDA::IsLess(bool value)
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

bool FNVCTDA::IsLessOrEqual()
    {
    return ((operType & 0xF0) == eLessOrEqual);
    }

void FNVCTDA::IsLessOrEqual(bool value)
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

bool FNVCTDA::IsType(UINT8 Type)
    {
    return ((operType & 0xF0) == (Type & 0xF0));
    }

void FNVCTDA::SetType(UINT8 Type)
    {
    Type &= 0xF0;
    operType &= 0x0F;
    operType |= Type;
    }

bool FNVCTDA::IsNone()
    {
    return ((operType & 0x0F) == fIsNone);
    }

void FNVCTDA::IsNone(bool value)
    {
    if(value)
        operType &= 0xF0;
    }

bool FNVCTDA::IsOr()
    {
    return ((operType & 0x0F) & fIsOr) != 0;
    }

void FNVCTDA::IsOr(bool value)
    {
    operType = value ? (operType | fIsOr) : (operType & ~fIsOr);
    }

bool FNVCTDA::IsRunOnTarget()
    {
    return ((operType & 0x0F) & fIsRunOnTarget) != 0;
    }

void FNVCTDA::IsRunOnTarget(bool value)
    {
    operType = value ? (operType | fIsRunOnTarget) : (operType & ~fIsRunOnTarget);
    }

bool FNVCTDA::IsUseGlobal() const
    {
    return ((operType & 0x0F) & fIsUseGlobal) != 0;
    }

void FNVCTDA::IsUseGlobal(bool value)
    {
    operType = value ? (operType | fIsUseGlobal) : (operType & ~fIsUseGlobal);
    }

bool FNVCTDA::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((operType & 0x0F) & (Mask & 0x0F)) == Mask : ((operType & 0x0F) & (Mask & 0x0F)) != 0;
    }

void FNVCTDA::SetFlagMask(UINT8 Mask)
    {
    Mask &= 0x0F;
    operType &= 0xF0;
    operType |= Mask;
    }

bool FNVCTDA::IsResultOnSubject()
    {
    return (runOnType == eSubject);
    }

void FNVCTDA::IsResultOnSubject(bool value)
    {
    runOnType = value ? eSubject : eTarget;
    }

bool FNVCTDA::IsResultOnTarget()
    {
    return (runOnType == eTarget);
    }

void FNVCTDA::IsResultOnTarget(bool value)
    {
    runOnType = value ? eTarget : eSubject;
    }

bool FNVCTDA::IsResultOnReference()
    {
    return (runOnType == eReference);
    }

void FNVCTDA::IsResultOnReference(bool value)
    {
    runOnType = value ? eReference : eSubject;
    }

bool FNVCTDA::IsResultOnCombatTarget()
    {
    return (runOnType == eCombatTarget);
    }

void FNVCTDA::IsResultOnCombatTarget(bool value)
    {
    runOnType = value ? eCombatTarget : eSubject;
    }

bool FNVCTDA::IsResultOnLinkedReference()
    {
    return (runOnType == eLinkedReference);
    }

void FNVCTDA::IsResultOnLinkedReference(bool value)
    {
    runOnType = value ? eLinkedReference : eSubject;
    }

bool FNVCTDA::IsResultOnType(UINT32 Type)
    {
    return runOnType == Type;
    }

void FNVCTDA::SetResultOnType(UINT32 Type)
    {
    runOnType = Type;
    }

FNVEFIT::FNVEFIT():
    magnitude(0),
    area(0),
    duration(0),
    rangeType(0),
    actorValue(-1)
    {
    //
    }

FNVEFIT::~FNVEFIT()
    {
    //
    }

bool FNVEFIT::operator ==(const FNVEFIT &other) const
    {
    return (magnitude == other.magnitude &&
            area == other.area &&
            duration == other.duration &&
            rangeType == other.rangeType &&
            actorValue == other.actorValue);
    }

bool FNVEFIT::operator !=(const FNVEFIT &other) const
    {
    return !(*this == other);
    }

bool FNVEffect::VisitFormIDs(FormIDOp &op)
    {
    op.Accept(EFID.value);
    for(UINT32 p = 0; p < CTDA.value.size(); p++)
        CTDA.value[p]->VisitFormIDs(op);
    return op.Stop();
    }

void FNVEffect::Write(FileWriter &writer)
    {
    WRITE(EFID);
    WRITE(EFIT);
    CTDA.Write(REV32(CTDA), writer, true);
    }

bool FNVEffect::IsRangeSelf()
    {
    return (EFIT.value.rangeType == eRangeSelf);
    }

void FNVEffect::IsRangeSelf(bool value)
    {
    EFIT.value.rangeType = value ? eRangeSelf : eRangeTouch;
    }

bool FNVEffect::IsRangeTouch()
    {
    return (EFIT.value.rangeType == eRangeTouch);
    }

void FNVEffect::IsRangeTouch(bool value)
    {
    EFIT.value.rangeType = value ? eRangeTouch : eRangeSelf;
    }

bool FNVEffect::IsRangeTarget()
    {
    return (EFIT.value.rangeType == eRangeTarget);
    }

void FNVEffect::IsRangeTarget(bool value)
    {
    EFIT.value.rangeType = value ? eRangeTarget : eRangeSelf;
    }

bool FNVEffect::IsRange(UINT32 Mask)
    {
    return (EFIT.value.rangeType == Mask);
    }

void FNVEffect::SetRange(UINT32 Mask)
    {
    EFIT.value.rangeType = Mask;
    }

bool FNVEffect::operator ==(const FNVEffect &other) const
    {
    return (EFID == other.EFID &&
            EFIT == other.EFIT &&
            CTDA == other.CTDA);
    }

bool FNVEffect::operator !=(const FNVEffect &other) const
    {
    return !(*this == other);
    }

DESTDSTD::DESTDSTD():
    health(0),
    index(0),
    stage(0),
    flags(0),
    dps(0),
    explosion(0),
    debris(0),
    debrisCount(0)
    {
    //
    }

DESTDSTD::~DESTDSTD()
    {
    //
    }

bool DESTDSTD::operator ==(const DESTDSTD &other) const
    {
    return (health == other.health &&
            index == other.index &&
            stage == other.stage &&
            flags == other.flags &&
            dps == other.dps &&
            explosion == other.explosion &&
            debris == other.debris &&
            debrisCount == other.debrisCount);
    }

bool DESTDSTD::operator !=(const DESTDSTD &other) const
    {
    return !(*this == other);
    }

void DESTSTAGE::Write(FileWriter &writer)
    {
    WRITE(DSTD);
    if(DMDL.IsLoaded())
        {
        WRITE(DMDL);
        WRITE(DMDT);
        }
    WRITEEMPTY(DSTF);
    }

bool DESTSTAGE::IsCapDamage()
    {
    return (DSTD.value.flags & fIsCapDamage) != 0;
    }

void DESTSTAGE::IsCapDamage(bool value)
    {
    DSTD.value.flags = value ? (DSTD.value.flags | fIsCapDamage) : (DSTD.value.flags & ~fIsCapDamage);
    }

bool DESTSTAGE::IsDisable()
    {
    return (DSTD.value.flags & fIsDisable) != 0;
    }

void DESTSTAGE::IsDisable(bool value)
    {
    DSTD.value.flags = value ? (DSTD.value.flags | fIsDisable) : (DSTD.value.flags & ~fIsDisable);
    }

bool DESTSTAGE::IsDestroy()
    {
    return (DSTD.value.flags & fIsDestroy) != 0;
    }

void DESTSTAGE::IsDestroy(bool value)
    {
    DSTD.value.flags = value ? (DSTD.value.flags | fIsDestroy) : (DSTD.value.flags & ~fIsDestroy);
    }

bool DESTSTAGE::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DSTD.value.flags & Mask) == Mask) : ((DSTD.value.flags & Mask) != 0);
    }

void DESTSTAGE::SetFlagMask(UINT8 Mask)
    {
    DSTD.value.flags = Mask;
    }

bool DESTSTAGE::operator ==(const DESTSTAGE &other) const
    {
    return (DSTD == other.DSTD &&
            DMDL.equalsi(other.DMDL) &&
            DMDT == other.DMDT);
    }

bool DESTSTAGE::operator !=(const DESTSTAGE &other) const
    {
    return !(*this == other);
    }

bool sortDESTStages::operator()(const DESTSTAGE *lhs, const DESTSTAGE *rhs) const
    {
    return lhs->DSTD.value.index < rhs->DSTD.value.index;
    }

GENDEST::GENDEST():
    health(0),
    count(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

GENDEST::~GENDEST()
    {
    //
    }

bool GENDEST::operator ==(const GENDEST &other) const
    {
    return (health == other.health &&
            count == other.count &&
            flags == other.flags);
    }

bool GENDEST::operator !=(const GENDEST &other) const
    {
    return !(*this == other);
    }

void GENDESTRUCT::Write(FileWriter &writer)
    {
    WRITE(DEST);
    Stages.Write(writer);
    }

bool GENDESTRUCT::IsVATSTargetable()
    {
    return (DEST.value.flags & fIsVATSTargetable) != 0;
    }

void GENDESTRUCT::IsVATSTargetable(bool value)
    {
    DEST.value.flags = value ? (DEST.value.flags | fIsVATSTargetable) : (DEST.value.flags & ~fIsVATSTargetable);
    }

bool GENDESTRUCT::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DEST.value.flags & Mask) == Mask) : ((DEST.value.flags & Mask) != 0);
    }

void GENDESTRUCT::SetFlagMask(UINT8 Mask)
    {
    DEST.value.flags = Mask;
    }

bool GENDESTRUCT::operator ==(const GENDESTRUCT &other) const
    {
    return (DEST == other.DEST &&
            Stages == other.Stages);
    }
bool GENDESTRUCT::operator !=(const GENDESTRUCT &other) const
    {
    return !(*this == other);
    }

GENBMDT::GENBMDT():
    bipedFlags(0),
    generalFlags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

GENBMDT::~GENBMDT()
    {
    //
    }

bool GENBMDT::operator ==(const GENBMDT &other) const
    {
    return (bipedFlags == other.bipedFlags &&
            generalFlags == other.generalFlags);
    }

bool GENBMDT::operator !=(const GENBMDT &other) const
    {
    return !(*this == other);
    }

FNVEQUIPDATA::FNVEQUIPDATA():
    value(0),
    health(0),
    weight(0.0f)
    {
    //
    }

FNVEQUIPDATA::~FNVEQUIPDATA()
    {
    //
    }

bool FNVEQUIPDATA::operator ==(const FNVEQUIPDATA &other) const
    {
    return (value == other.value &&
            health == other.health &&
            AlmostEqual(weight,other.weight,2));
    }

bool FNVEQUIPDATA::operator !=(const FNVEQUIPDATA &other) const
    {
    return !(*this == other);
    }

FNVEQUIPDNAM::FNVEQUIPDNAM():
    AR(0),
    flags(0),
    DT(0.0f)
    {
    memset(&unknown[0], 0x00, sizeof(unknown));
    }

FNVEQUIPDNAM::~FNVEQUIPDNAM()
    {
    //
    }

bool FNVEQUIPDNAM::operator ==(const FNVEQUIPDNAM &other) const
    {
    return (AR == other.AR &&
            flags == other.flags &&
            AlmostEqual(DT,other.DT,2) &&
            unknown[0] == other.unknown[0] &&
            unknown[1] == other.unknown[1] &&
            unknown[2] == other.unknown[2] &&
            unknown[3] == other.unknown[3]);
    }

bool FNVEQUIPDNAM::operator !=(const FNVEQUIPDNAM &other) const
    {
    return !(*this == other);
    }

GENCOED::GENCOED():
    owner(0),
    globalOrRank(0),
    condition(0.0f)
    {
    //
    }

GENCOED::~GENCOED()
    {
    //
    }

bool GENCOED::operator ==(const GENCOED &other) const
    {
    return (owner == other.owner &&
            globalOrRank == other.globalOrRank &&
            AlmostEqual(condition,other.condition,2));
    }

bool GENCOED::operator !=(const GENCOED &other) const
    {
    return !(*this == other);
    }

bool FNVCNTO::IsGlobal()
    {
    //Not properly implemented, requires being able to tell if COED->owner is a npc record
    //...the current model doesn't allow a record to lookup another record...
    //As well, the geck wiki states that the global variable isn't even used by FO3/FNV

    //So the current hack is to see if the globalOrRank is likely to be a rank or global
    //It seems highly unlikely that any faction will have anywhere close to END_HARDCODED_IDS ranks (0x800)
    //So CBash assumes that if globalOrRank is > END_HARDCODED_IDS, then it must be a global
    //So false positives shouldn't be a problem
    //False negatives could occur though...
    //There aren't many records < END_HARDCODED_IDS, but 7 of them are globals
    //GameYear (0x35), GameMonth (0x36), GameDay (0x37),
    //GameHour (0x38), GameDaysPassed (0x39), TimeScale (0x3A),
    //PlayCredits (0x63)
    //It seems unlikely that these specific globals would be used in this context
    if(COED.IsLoaded())
        return COED->globalOrRank > END_HARDCODED_IDS;
    return false;
    }

bool FNVCNTO::IsRank()
    {
    //Not properly implemented, requires being able to tell if COED->owner is a faction record
    //...the current model doesn't allow a record to lookup another record...
    //As well, the geck wiki states that the global variable isn't even used by FO3/FNV

    //So the current hack is to see if the globalOrRank is likely to be a rank or global
    //It seems highly unlikely that any faction will have anywhere close to END_HARDCODED_IDS ranks (0x800)
    //So CBash assumes that if globalOrRank is < END_HARDCODED_IDS, then it must be a rank
    //So false negatives shouldn't be a problem
    //False positives could occur though...
    //There aren't many records < END_HARDCODED_IDS, but 7 of them are globals
    //GameYear (0x35), GameMonth (0x36), GameDay (0x37),
    //GameHour (0x38), GameDaysPassed (0x39), TimeScale (0x3A),
    //PlayCredits (0x63)
    //It seems unlikely that these specific globals would be used in this context
    if(COED.IsLoaded())
        return COED->globalOrRank < END_HARDCODED_IDS;
    return false;
    }

void FNVCNTO::Write(FileWriter &writer)
    {
    WRITE(CNTO);
    WRITE(COED);
    }

bool FNVCNTO::operator ==(const FNVCNTO &other) const
    {
    return (CNTO == other.CNTO &&
            COED == other.COED);
    }

bool FNVCNTO::operator !=(const FNVCNTO &other) const
    {
    return !(*this == other);
    }

GENDNAM::GENDNAM():
    defaultLandHeight(-2048.0f),
    defaultWaterHeight(0.0f)
    {
    //
    }

GENDNAM::~GENDNAM()
    {
    //
    }

bool GENDNAM::operator ==(const GENDNAM &other) const
    {
    return (AlmostEqual(defaultLandHeight,other.defaultLandHeight,2) &&
            AlmostEqual(defaultWaterHeight,other.defaultWaterHeight,2));
    }

bool GENDNAM::operator !=(const GENDNAM &other) const
    {
    return !(*this == other);
    }

GENONAM::GENONAM():
    mapScale(1.0f),
    xCellOffset(0.0f),
    yCellOffset(0.0f)
    {
    //
    }

GENONAM::~GENONAM()
    {
    //
    }

bool GENONAM::operator ==(const GENONAM &other) const
    {
    return (AlmostEqual(mapScale,other.mapScale,2) &&
            AlmostEqual(xCellOffset,other.xCellOffset,2) &&
            AlmostEqual(yCellOffset,other.yCellOffset,2));
    }

bool GENONAM::operator !=(const GENONAM &other) const
    {
    return !(*this == other);
    }

GENIMPS::GENIMPS():
    material(0),
    oldImpact(0),
    newImpact(0)
    {
    //
    }

GENIMPS::~GENIMPS()
    {
    //
    }

bool GENIMPS::operator ==(const GENIMPS &other) const
    {
    return (material == other.material &&
            oldImpact == other.oldImpact &&
            newImpact == other.newImpact);
    }

bool GENIMPS::operator !=(const GENIMPS &other) const
    {
    return !(*this == other);
    }

GENXPRM::GENXPRM():
    xBound(0.0f),
    yBound(0.0f),
    zBound(0.0f),
    red(0.0f),
    green(0.0f),
    blue(0.0f),
    unknown(0.0f),
    type(0)
    {
    //
    }

GENXPRM::~GENXPRM()
    {
    //
    }

bool GENXPRM::operator ==(const GENXPRM &other) const
    {
    return (AlmostEqual(xBound,other.xBound,2) &&
            AlmostEqual(yBound,other.yBound,2) &&
            AlmostEqual(zBound,other.zBound,2) &&
            AlmostEqual(red,other.red,2) &&
            AlmostEqual(green,other.green,2) &&
            AlmostEqual(blue,other.blue,2) &&
            AlmostEqual(unknown,other.unknown,2) &&
            type == other.type);
    }

bool GENXPRM::operator !=(const GENXPRM &other) const
    {
    return !(*this == other);
    }

GENXMBO::GENXMBO():
    x(0.0f),
    y(0.0f),
    z(0.0f)
    {
    //
    }

GENXMBO::~GENXMBO()
    {
    //
    }

bool GENXMBO::operator ==(const GENXMBO &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2) &&
            AlmostEqual(z,other.z,2));
    }

bool GENXMBO::operator !=(const GENXMBO &other) const
    {
    return !(*this == other);
    }

GENXTEL::GENXTEL():
    destinationFid(0),
    flags(0)
    {
    //
    }

GENXTEL::~GENXTEL()
    {
    //
    }

bool GENXTEL::operator ==(const GENXTEL &other) const
    {
    return (destinationFid == other.destinationFid &&
            flags == other.flags &&
            destination == other.destination);
    }

bool GENXTEL::operator !=(const GENXTEL &other) const
    {
    return !(*this == other);
    }

void GENMAPDATA::Write(FileWriter &writer)
    {
    WRITEEMPTY(XMRK);
    WRITE(FNAM);
    WRITE(FULL);
    WRITE(TNAM);
    WRITE(WMI1);
    }

bool GENMAPDATA::operator ==(const GENMAPDATA &other) const
    {
    return (FNAM == other.FNAM &&
            FULL.equals(other.FULL) &&
            TNAM == other.TNAM &&
            WMI1 == other.WMI1);
    }

bool GENMAPDATA::operator !=(const GENMAPDATA &other) const
    {
    return !(*this == other);
    }

void GENAUDIODATA::Write(FileWriter &writer)
    {
    WRITEEMPTY(MMRK);
    WRITE(FULL);
    WRITE(CNAM);
    WRITE(BNAM);
    WRITE(MNAM);
    WRITE(NNAM);
    }

bool GENAUDIODATA::operator ==(const GENAUDIODATA &other) const
    {
    return (FULL == other.FULL &&
            CNAM == other.CNAM &&
            BNAM == other.BNAM &&
            MNAM == other.MNAM &&
            NNAM == other.NNAM);
    }

bool GENAUDIODATA::operator !=(const GENAUDIODATA &other) const
    {
    return !(*this == other);
    }

GENXRDO::GENXRDO():
    rangeRadius(0.0f),
    rangeType(0),
    staticPercentage(0.0f),
    positionReference(0)
    {
    //
    }

GENXRDO::~GENXRDO()
    {
    //
    }

bool GENXRDO::operator ==(const GENXRDO &other) const
    {
    return (AlmostEqual(rangeRadius,other.rangeRadius,2) &&
            rangeType == other.rangeType &&
            AlmostEqual(staticPercentage,other.staticPercentage,2) &&
            positionReference == other.positionReference);
    }

bool GENXRDO::operator !=(const GENXRDO &other) const
    {
    return !(*this == other);
    }

void GENAMMO::Write(FileWriter &writer)
    {
    WRITE(XAMT);
    WRITE(XAMC);
    }

bool GENAMMO::operator ==(const GENAMMO &other) const
    {
    return (XAMT == other.XAMT &&
            XAMC == other.XAMC);
    }

bool GENAMMO::operator !=(const GENAMMO &other) const
    {
    return !(*this == other);
    }

GENXPWR::GENXPWR():
    reference(0),
    type(0)
    {
    //
    }

GENXPWR::~GENXPWR()
    {
    //
    }

bool GENXPWR::IsReflection()
    {
    return type == eReflection;
    }

void GENXPWR::IsReflection(bool value)
    {
    type = value ? eReflection : eRefraction;
    }

bool GENXPWR::IsRefraction()
    {
    return type == eRefraction;
    }

void GENXPWR::IsRefraction(bool value)
    {
    type = value ? eRefraction : eReflection;
    }

bool GENXPWR::IsType(UINT32 Type)
    {
    return type == Type;
    }

void GENXPWR::SetType(UINT32 Type)
    {
    type = Type;
    }

bool GENXPWR::operator ==(const GENXPWR &other) const
    {
    return (reference == other.reference &&
            type == other.type);
    }

bool GENXPWR::operator !=(const GENXPWR &other) const
    {
    return !(*this == other);
    }

GENXDCR::GENXDCR():
    reference(0)
    {
    memset(&unknown1[0], 0x00, sizeof(unknown1));
    }

GENXDCR::~GENXDCR()
    {
    //
    }

bool GENXDCR::operator ==(const GENXDCR &other) const
    {
    return (reference == other.reference);
    }

bool GENXDCR::operator !=(const GENXDCR &other) const
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

GENXAPR::GENXAPR():
    reference(0),
    delay(0.0f)
    {
    //
    }

GENXAPR::~GENXAPR()
    {
    //
    }

bool GENXAPR::operator ==(const GENXAPR &other) const
    {
    return (reference == other.reference &&
            AlmostEqual(delay,other.delay,2));
    }

bool GENXAPR::operator !=(const GENXAPR &other) const
    {
    return !(*this == other);
    }

bool GENACTPARENT::IsParentActivateOnly()
    {
    return (XAPD.value & fIsParentActivateOnly) != 0;
    }

void GENACTPARENT::IsParentActivateOnly(bool value)
    {
    XAPD.value = value ? (XAPD.value | fIsParentActivateOnly) : (XAPD.value & ~fIsParentActivateOnly);
    }

bool GENACTPARENT::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((XAPD.value & Mask) == Mask) : ((XAPD.value & Mask) != 0);
    }

void GENACTPARENT::SetFlagMask(UINT8 Mask)
    {
    XAPD.value = Mask;
    }

void GENACTPARENT::Write(FileWriter &writer)
    {
    WRITE(XAPD);
    WRITE(XAPR);
    }

bool GENACTPARENT::operator ==(const GENACTPARENT &other) const
    {
    return (XAPD == other.XAPD &&
            XAPR == other.XAPR);
    }

bool GENACTPARENT::operator !=(const GENACTPARENT &other) const
    {
    return !(*this == other);
    }

GENXNDP::GENXNDP():
    navMesh(0),
    unknown1(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

GENXNDP::~GENXNDP()
    {
    //
    }

bool GENXNDP::operator ==(const GENXNDP &other) const
    {
    return (navMesh == other.navMesh &&
            unknown1 == other.unknown1);
    }

bool GENXNDP::operator !=(const GENXNDP &other) const
    {
    return !(*this == other);
    }

GENPOSITION::GENPOSITION():
    width(0.0f),
    height(0.0f),
    xPos(0.0f),
    yPos(0.0f),
    zPos(0.0f),
    q1(0.0f),
    q2(0.0f),
    q3(0.0f),
    q4(0.0f)
    {
    //
    }

GENPOSITION::~GENPOSITION()
    {
    //
    }

bool GENPOSITION::operator ==(const GENPOSITION &other) const
    {
    return (AlmostEqual(width,other.width,2) &&
            AlmostEqual(height,other.height,2) &&
            AlmostEqual(xPos,other.xPos,2) &&
            AlmostEqual(yPos,other.yPos,2) &&
            AlmostEqual(zPos,other.zPos,2) &&
            AlmostEqual(q1,other.q1,2) &&
            AlmostEqual(q2,other.q2,2) &&
            AlmostEqual(q3,other.q3,2) &&
            AlmostEqual(q4,other.q4,2));
    }

bool GENPOSITION::operator !=(const GENPOSITION &other) const
    {
    return !(*this == other);
    }

GENXRMR::GENXRMR():
    count(0)
    {
    memset(&unknown1[0], 0x00, sizeof(unknown1));
    }

GENXRMR::~GENXRMR()
    {
    //
    }

bool GENXRMR::operator ==(const GENXRMR &other) const
    {
    return (count == other.count &&
            unknown1[0] == other.unknown1[0] &&
            unknown1[1] == other.unknown1[1]);
    }

bool GENXRMR::operator !=(const GENXRMR &other) const
    {
    return !(*this == other);
    }

void GENROOM::Write(FileWriter &writer)
    {
    WRITE(XRMR);
    WRITE(XLRM);
    }

bool GENROOM::operator ==(const GENROOM &other) const
    {
    return (XRMR == other.XRMR &&
            XLRM == other.XLRM);
    }

bool GENROOM::operator !=(const GENROOM &other) const
    {
    return !(*this == other);
    }

void FNVXOWN::Write(FileWriter &writer)
    {
    WRITE(XOWN);
    WRITE(XRNK);
    }

bool FNVXOWN::operator ==(const FNVXOWN &other) const
    {
    return (XOWN == other.XOWN &&
            XRNK == other.XRNK);
    }

bool FNVXOWN::operator !=(const FNVXOWN &other) const
    {
    return !(*this == other);
    }

FNVXLOC::FNVXLOC():
    level(0),
    key(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unused2[0], 0x00, sizeof(unused2));
    memset(&unknown[0], 0x00, sizeof(unknown));
    }

FNVXLOC::~FNVXLOC()
    {
    //
    }

bool FNVXLOC::operator ==(const FNVXLOC &other) const
    {
    return (level == other.level &&
            key == other.key &&
            flags == other.flags &&
            unknown[0] == other.unknown[0] &&
            unknown[1] == other.unknown[1] &&
            unknown[2] == other.unknown[2] &&
            unknown[3] == other.unknown[3] &&
            unknown[4] == other.unknown[4] &&
            unknown[5] == other.unknown[5] &&
            unknown[6] == other.unknown[6] &&
            unknown[7] == other.unknown[7]);
    }

bool FNVXLOC::operator !=(const FNVXLOC &other) const
    {
    return !(*this == other);
    }

FNVAIDT::FNVAIDT():
    aggression(0),
    confidence(0),
    energyLevel(0),
    responsibility(0),
    mood(0),
    flags(0),
    trainSkill(0),
    trainLevel(0),
    assistance(0),
    aggroFlags(0),
    aggroRadius(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

FNVAIDT::~FNVAIDT()
    {
    //
    }

bool FNVAIDT::operator ==(const FNVAIDT &other) const
    {
    return (aggression == other.aggression &&
            confidence == other.confidence &&
            energyLevel == other.energyLevel &&
            responsibility == other.responsibility &&
            mood == other.mood &&
            flags == other.flags &&
            trainSkill == other.trainSkill &&
            trainLevel == other.trainLevel &&
            assistance == other.assistance &&
            aggroFlags == other.aggroFlags &&
            aggroRadius == other.aggroRadius);
    }

bool FNVAIDT::operator !=(const FNVAIDT &other) const
    {
    return !(*this == other);
    }

FNVACBS::FNVACBS():
    flags(0),
    fatigue(0),
    barterGold(0),
    level(0),
    calcMin(0),
    calcMax(0),
    speedMult(0),
    karma(0.0f),
    dispBase(0),
    templateFlags(0)
    {
    //
    }

FNVACBS::~FNVACBS()
    {
    //
    }

bool FNVACBS::operator ==(const FNVACBS &other) const
    {
    return (flags == other.flags &&
            fatigue == other.fatigue &&
            barterGold == other.barterGold &&
            level == other.level &&
            calcMin == other.calcMin &&
            calcMax == other.calcMax &&
            speedMult == other.speedMult &&
            AlmostEqual(karma,other.karma,2) &&
            dispBase == other.dispBase &&
            templateFlags == other.templateFlags);
    }

bool FNVACBS::operator !=(const FNVACBS &other) const
    {
    return !(*this == other);
    }

bool FNVLVLO::IsGlobal()
    {
    //Not properly implemented, requires being able to tell if COED->owner is a npc record
    //...the current model doesn't allow a record to lookup another record...
    //As well, the geck wiki states that the global variable isn't even used by FO3/FNV

    //So the current hack is to see if the globalOrRank is likely to be a rank or global
    //It seems highly unlikely that any faction will have anywhere close to END_HARDCODED_IDS ranks (0x800)
    //So CBash assumes that if globalOrRank is > END_HARDCODED_IDS, then it must be a global
    //So false positives shouldn't be a problem
    //False negatives could occur though...
    //There aren't many records < END_HARDCODED_IDS, but 7 of them are globals
    //GameYear (0x35), GameMonth (0x36), GameDay (0x37),
    //GameHour (0x38), GameDaysPassed (0x39), TimeScale (0x3A),
    //PlayCredits (0x63)
    //It seems unlikely that these specific globals would be used in this context
    if(COED.IsLoaded())
        return COED->globalOrRank > END_HARDCODED_IDS;
    return false;
    }

bool FNVLVLO::IsRank()
    {
    //Not properly implemented, requires being able to tell if COED->owner is a faction record
    //...the current model doesn't allow a record to lookup another record...
    //As well, the geck wiki states that the global variable isn't even used by FO3/FNV

    //So the current hack is to see if the globalOrRank is likely to be a rank or global
    //It seems highly unlikely that any faction will have anywhere close to END_HARDCODED_IDS ranks (0x800)
    //So CBash assumes that if globalOrRank is < END_HARDCODED_IDS, then it must be a rank
    //So false negatives shouldn't be a problem
    //False positives could occur though...
    //There aren't many records < END_HARDCODED_IDS, but 7 of them are globals
    //GameYear (0x35), GameMonth (0x36), GameDay (0x37),
    //GameHour (0x38), GameDaysPassed (0x39), TimeScale (0x3A),
    //PlayCredits (0x63)
    //It seems unlikely that these specific globals would be used in this context
    if(COED.IsLoaded())
        return COED->globalOrRank < END_HARDCODED_IDS;
    return false;
    }

void FNVLVLO::Write(FileWriter &writer)
    {
    WRITE(LVLO);
    WRITE(COED);
    }

bool FNVLVLO::operator ==(const FNVLVLO &other) const
    {
    return (LVLO == other.LVLO &&
            COED == other.COED);
    }

bool FNVLVLO::operator !=(const FNVLVLO &other) const
    {
    return !(*this == other);
    }

SURVDATA::SURVDATA():
    threshold(0),
    actorEffect(0)
    {
    //
    }

SURVDATA::~SURVDATA()
    {
    //
    }

bool SURVDATA::operator ==(const SURVDATA &other) const
    {
    return (threshold == other.threshold &&
            actorEffect == other.actorEffect);
    }

bool SURVDATA::operator !=(const SURVDATA &other) const
    {
    return !(*this == other);
    }

FNVLIGHT::FNVLIGHT():
    fogNear(0.0f),
    fogFar(0.0f),
    directionalXY(0),
    directionalZ(0),
    directionalFade(0.0f),
    fogClip(0.0f),
    fogPower(0.0f)
    {
    //
    }

FNVLIGHT::~FNVLIGHT()
    {
    //
    }

bool FNVLIGHT::operator ==(const FNVLIGHT &other) const
    {
    return (ambient == other.ambient &&
            directional == other.directional &&
            fog == other.fog &&
            AlmostEqual(fogNear,other.fogNear,2) &&
            AlmostEqual(fogFar,other.fogFar,2) &&
            directionalXY == other.directionalXY &&
            directionalZ == other.directionalZ &&
            AlmostEqual(directionalFade,other.directionalFade,2) &&
            AlmostEqual(fogClip,other.fogClip,2) &&
            AlmostEqual(fogPower,other.fogPower,2));
    }

bool FNVLIGHT::operator !=(const FNVLIGHT &other) const
    {
    return !(*this == other);
    }

GENXPOD::GENXPOD():
    room1(0),
    room2(0)
    {
    //
    }
GENXPOD::~GENXPOD()
    {
    //
    }

bool GENXPOD::operator ==(const GENXPOD &other) const
    {
    return (room1 == other.room1 &&
            room2 == other.room2);
    }

bool GENXPOD::operator !=(const GENXPOD &other) const
    {
    return !(*this == other);
    }

GENXORD::GENXORD():
    right(0),
    left(0),
    bottom(0),
    top(0)
    {
    //
    }
GENXORD::~GENXORD()
    {
    //
    }

bool GENXORD::operator ==(const GENXORD &other) const
    {
    return (right == other.right &&
            left == other.left &&
            bottom == other.bottom &&
            top == other.top);
    }

bool GENXORD::operator !=(const GENXORD &other) const
    {
    return !(*this == other);
    }

GENIMPF::GENIMPF()
    {
    memset(&concSolid[0], 0x00, sizeof(concSolid));
    memset(&concBroken[0], 0x00, sizeof(concBroken));
    memset(&metalSolid[0], 0x00, sizeof(metalSolid));
    memset(&metalHollow[0], 0x00, sizeof(metalHollow));
    memset(&metalSheet[0], 0x00, sizeof(metalSheet));
    memset(&wood[0], 0x00, sizeof(wood));
    memset(&sand[0], 0x00, sizeof(sand));
    memset(&dirt[0], 0x00, sizeof(dirt));
    memset(&grass[0], 0x00, sizeof(grass));
    memset(&water[0], 0x00, sizeof(water));
    }

GENIMPF::~GENIMPF()
    {
    //
    }

bool GENIMPF::operator ==(const GENIMPF &other) const
    {
    return (cmps(&concSolid[0], &other.concSolid[0]) == 0 &&
            cmps(&concBroken[0], &other.concBroken[0]) == 0 &&
            cmps(&metalSolid[0], &other.metalSolid[0]) == 0 &&
            cmps(&metalHollow[0], &other.metalHollow[0]) == 0 &&
            cmps(&metalSheet[0], &other.metalSheet[0]) == 0 &&
            cmps(&wood[0], &other.wood[0]) == 0 &&
            cmps(&sand[0], &other.sand[0]) == 0 &&
            cmps(&dirt[0], &other.dirt[0]) == 0 &&
            cmps(&grass[0], &other.grass[0]) == 0 &&
            cmps(&water[0], &other.water[0]) == 0);
    }

bool GENIMPF::operator !=(const GENIMPF &other) const
    {
    return !(*this == other);
    }