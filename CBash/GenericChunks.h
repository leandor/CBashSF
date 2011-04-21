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
#pragma once
// BaseRecord.h
#include "Common.h"
#include <vector>

class FormIDOp
    {
    protected:
        UINT32 count;
        bool stop;
        bool result;

    public:
        FormIDOp();
        ~FormIDOp();

        virtual bool Accept(UINT32 &curFormID) abstract {};
        virtual bool AcceptMGEF(UINT32 &curMgefCode) abstract {};

        UINT32 GetCount();
        void ResetCount();
        bool Stop();
        bool GetResult();
    };

class FormIDResolver : public FormIDOp
    {
    private:
        const UINT8 (&ResolveTable)[256];

    public:
        const unsigned char * const FileStart;
        const unsigned char * const FileEnd;

        FormIDResolver(const UINT8 (&_ResolveTable)[256], const unsigned char * const _FileStart, const unsigned char * const _FileEnd);
        ~FormIDResolver();

        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
        bool IsValid(const unsigned char * const _SrcBuf);
    };

struct GENU8
    {
    UINT8  value;

    GENU8();
    ~GENU8();

    bool operator ==(const GENU8 &other) const;
    bool operator !=(const GENU8 &other) const;
    };

struct GENU16
    {
    UINT16 value;

    GENU16();
    ~GENU16();

    bool operator ==(const GENU16 &other) const;
    bool operator !=(const GENU16 &other) const;
    };

struct GENU32
    {
    UINT32 value;

    GENU32();
    ~GENU32();

    bool operator ==(const GENU32 &other) const;
    bool operator !=(const GENU32 &other) const;
    };

struct GENS8
    {
    SINT8  value;

    GENS8();
    ~GENS8();

    bool operator ==(const GENS8 &other) const;
    bool operator !=(const GENS8 &other) const;
    };

struct GENS16
    {
    SINT16 value;

    GENS16();
    ~GENS16();

    bool operator ==(const GENS16 &other) const;
    bool operator !=(const GENS16 &other) const;
    };

struct GENS32
    {
    SINT32 value;

    GENS32();
    ~GENS32();

    bool operator ==(const GENS32 &other) const;
    bool operator !=(const GENS32 &other) const;
    };

struct GENFLOAT
    {
    FLOAT32 value;

    GENFLOAT();
    ~GENFLOAT();

    bool operator ==(const GENFLOAT &other) const;
    bool operator !=(const GENFLOAT &other) const;
    };

typedef GENU32 GENFID;
typedef GENU32 GENEFID;

struct GENXNAM
    {
    FORMID  faction;
    SINT32  mod;

    GENXNAM();
    ~GENXNAM();

    bool operator ==(const GENXNAM &other) const;
    bool operator !=(const GENXNAM &other) const;
    };

struct GENSCHR
    {
    UINT8   unused1[4];
    UINT32  numRefs, compiledSize, lastIndex, scriptType;

    GENSCHR();
    ~GENSCHR();

    bool operator ==(const GENSCHR &other) const;
    bool operator !=(const GENSCHR &other) const;
    };

struct GENSCR_
    {
    FORMID_OR_UINT32 reference;
    bool    isSCRO;

    GENSCR_();
    ~GENSCR_();

    bool operator ==(const GENSCR_ &other) const;
    bool operator !=(const GENSCR_ &other) const;
    };

struct GENSLSD
    {
    UINT32  index;
    UINT8   unused1[12], flags, unused2[7];

    GENSLSD();
    ~GENSLSD();

    bool operator ==(const GENSLSD &other) const;
    bool operator !=(const GENSLSD &other) const;
    };

struct GENVARS
    {
    ReqSubRecord<GENSLSD> SLSD;
    StringRecord SCVR;

    enum flagsFlags
        {
        fIsLongOrShort = 0x00000001
        };

    bool   IsLongOrShort();
    void   IsLongOrShort(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    bool operator ==(const GENVARS &other) const;
    bool operator !=(const GENVARS &other) const;
    };

struct GENSCRIPT
    {
    ReqSubRecord<GENSCHR> SCHR;
    RawRecord SCDA;
    NonNullStringRecord SCTX;
    std::vector<GENVARS *> VARS;
    std::vector<ReqSubRecord<GENSCR_> *> SCR_;

    GENSCRIPT();
    ~GENSCRIPT();

    void Copy(GENSCRIPT &rhs);

    bool   IsType(UINT32 Type);
    void   SetType(UINT32 Type);

    bool   VisitFormIDs(FormIDOp &op);
    UINT32 GetSize();
    void writeSubRecords(_FileHandler &SaveHandler);

    bool operator ==(const GENSCRIPT &other) const;
    bool operator !=(const GENSCRIPT &other) const;
    };

struct GENMINSCRIPT
    {
    ReqSubRecord<GENSCHR> SCHR;
    RawRecord SCDA;
    NonNullStringRecord SCTX;
    std::vector<ReqSubRecord<GENSCR_> *> SCR_;

    GENMINSCRIPT();
    ~GENMINSCRIPT();

    void Copy(GENMINSCRIPT &rhs);

    bool   IsType(UINT32 Type);
    void   SetType(UINT32 Type);

    bool   VisitFormIDs(FormIDOp &op);
    UINT32 GetSize();
    void writeSubRecords(_FileHandler &SaveHandler);

    bool operator ==(const GENMINSCRIPT &other) const;
    bool operator !=(const GENMINSCRIPT &other) const;
    };

struct GENEFIT
    {
    MGEFCODE_OR_UINT32 name;
    UINT32  magnitude, area, duration, rangeType;
    FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 actorValue;

    GENEFIT();
    ~GENEFIT();

    bool operator ==(const GENEFIT &other) const;
    bool operator !=(const GENEFIT &other) const;
    };

struct GENSCIT
    {
    FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 script;
    UINT32  school;
    MGEFCODE_OR_UINT32 visual;
    UINT8   flags, unused1[3];

    GENSCIT();
    ~GENSCIT();

    bool operator ==(const GENSCIT &other) const;
    bool operator !=(const GENSCIT &other) const;
    };

struct OBMEEFME
    {
    UINT8   recordVersion, betaVersion, minorVersion, majorVersion;
    UINT8   efitParamInfo;
    UINT8   efixParamInfo;
    UINT8   reserved[0xA];

    OBMEEFME();
    ~OBMEEFME();

    bool operator ==(const OBMEEFME &other) const;
    bool operator !=(const OBMEEFME &other) const;
    };

struct OBMEEFIX
    {
    UINT32  efixOverrides;
    UINT32  efixFlags;
    FLOAT32 baseCost;
    ACTORVALUE resistAV;
    UINT8   reserved[0x10];

    OBMEEFIX();
    ~OBMEEFIX();

    bool operator ==(const OBMEEFIX &other) const;
    bool operator !=(const OBMEEFIX &other) const;
    };

struct OBMEEffect
    {
    ReqSubRecord<OBMEEFME> EFME;
    StringRecord EFII;
    OBMEEFIXSubRecord<OBMEEFIX> EFIX;

    bool operator ==(const OBMEEffect &other) const;
    bool operator !=(const OBMEEffect &other) const;
    };

struct GENEffect
    {
    ReqSubRecord<GENEFID> EFID;
    ReqSubRecord<GENEFIT> EFIT;
    OptSubRecord<GENSCIT> SCIT;
    StringRecord FULL;
    OptSubRecord<OBMEEffect> OBME;

    enum SCITFlags
        {
        fIsHostile = 0x01
        };

    enum eRanges
        {
        eRangeSelf    = 0,
        eRangeTouch   = 1,
        eRangeTarget  = 2
        };

    enum OBMEOverrideFlags
        {
        fOBME_IsHostile           = 0x00000001,
        fOBME_IsRecovers          = 0x00000002,
        fOBME_IsParamFlagA        = 0x00000004,
        fOBME_IsBeneficial        = 0x00000008,
        fOBME_IsFXPersists        = 0x00000400,
        fOBME_IsUnknownF          = 0x00004000,
        fOBME_IsNoRecast          = 0x00008000,
        fOBME_IsParamFlagB        = 0x00010000,
        fOBME_IsMagnitudeIsRange  = 0x00020000,
        fOBME_IsAtomicResistance  = 0x00040000,
        fOBME_IsParamFlagC        = 0x00080000,
        fOBME_IsParamFlagD        = 0x00100000,
        fOBME_IsDisabled          = 0x00400000,
        fOBME_IsUnknownO          = 0x00800000,
        fOBME_IsNoHitEffect       = 0x08000000,
        fOBME_IsPersistOnDeath    = 0x10000000,
        fOBME_IsExplodesWithForce = 0x20000000,
        fOBME_IsHidden            = 0x40000000
        //fOBME_IsMagnitudeIsFeet = 0x80000000 //Marked as Deprecated
        };

    enum OBMEUsingOverrideFlags
        {
        fOBME_IsUsingHostileOverride           = 0x00000001,
        fOBME_IsUsingRecoversOverride          = 0x00000002,
        fOBME_IsUsingParamFlagAOverride        = 0x00000004,
        fOBME_IsUsingBeneficialOverride        = 0x00000008,
        fOBME_IsUsingEFIXParamOverride         = 0x00000010,
        fOBME_IsUsingSchoolOverride            = 0x00000020,
        fOBME_IsUsingNameOverride              = 0x00000040,
        fOBME_IsUsingVFXCodeOverride           = 0x00000080,
        fOBME_IsUsingBaseCostOverride          = 0x00000100,
        fOBME_IsUsingResistAVOverride          = 0x00000200,
        fOBME_IsUsingFXPersistsOverride        = 0x00000400,
        fOBME_IsUsingIconOverride              = 0x00000800,
        fOBME_IsUsingDoesntTeachOverride       = 0x00001000,
        fOBME_IsUsingUnknownFOverride          = 0x00004000,
        fOBME_IsUsingNoRecastOverride          = 0x00008000,
        fOBME_IsUsingParamFlagBOverride        = 0x00010000,
        fOBME_IsUsingMagnitudeIsRangeOverride  = 0x00020000,
        fOBME_IsUsingAtomicResistanceOverride  = 0x00040000,
        fOBME_IsUsingParamFlagCOverride        = 0x00080000,
        fOBME_IsUsingParamFlagDOverride        = 0x00100000,
        fOBME_IsUsingDisabledOverride          = 0x00400000,
        fOBME_IsUsingUnknownOOverride          = 0x00800000,
        fOBME_IsUsingNoHitEffectOverride       = 0x08000000,
        fOBME_IsUsingPersistOnDeathOverride    = 0x10000000,
        fOBME_IsUsingExplodesWithForceOverride = 0x20000000,
        fOBME_IsUsingHiddenOverride            = 0x40000000
        //fOBME_IsUsingMagnitudeIsFeetOverride = 0x80000000 //Marked as Deprecated
        };

    bool operator ==(const GENEffect &other) const;
    bool operator !=(const GENEffect &other) const;

    bool IsHostile();
    void IsHostile(bool value);
    bool IsFlagMask(UINT8   Mask, bool Exact=false);
    void SetFlagMask(UINT8   Mask);

    bool IsRangeSelf();
    void IsRangeSelf(bool value);
    bool IsRangeTouch();
    void IsRangeTouch(bool value);
    bool IsRangeTarget();
    void IsRangeTarget(bool value);
    bool IsRange(UINT32  Mask);
    void SetRange(UINT32  Mask);

    bool OBME_IsUsingHostileOverride();
    void OBME_IsUsingHostileOverride(bool value);
    bool OBME_IsUsingRecoversOverride();
    void OBME_IsUsingRecoversOverride(bool value);
    bool OBME_IsUsingParamFlagAOverride();
    void OBME_IsUsingParamFlagAOverride(bool value);
    bool OBME_IsUsingBeneficialOverride();
    void OBME_IsUsingBeneficialOverride(bool value);
    bool OBME_IsUsingEFIXParamOverride();
    void OBME_IsUsingEFIXParamOverride(bool value);
    bool OBME_IsUsingSchoolOverride();
    void OBME_IsUsingSchoolOverride(bool value);
    bool OBME_IsUsingNameOverride();
    void OBME_IsUsingNameOverride(bool value);
    bool OBME_IsUsingVFXCodeOverride();
    void OBME_IsUsingVFXCodeOverride(bool value);
    bool OBME_IsUsingBaseCostOverride();
    void OBME_IsUsingBaseCostOverride(bool value);
    bool OBME_IsUsingResistAVOverride();
    void OBME_IsUsingResistAVOverride(bool value);
    bool OBME_IsUsingFXPersistsOverride();
    void OBME_IsUsingFXPersistsOverride(bool value);
    bool OBME_IsUsingIconOverride();
    void OBME_IsUsingIconOverride(bool value);
    bool OBME_IsUsingDoesntTeachOverride();
    void OBME_IsUsingDoesntTeachOverride(bool value);
    bool OBME_IsUsingUnknownFOverride();
    void OBME_IsUsingUnknownFOverride(bool value);
    bool OBME_IsUsingNoRecastOverride();
    void OBME_IsUsingNoRecastOverride(bool value);
    bool OBME_IsUsingParamFlagBOverride();
    void OBME_IsUsingParamFlagBOverride(bool value);
    bool OBME_IsUsingMagnitudeIsRangeOverride();
    void OBME_IsUsingMagnitudeIsRangeOverride(bool value);
    bool OBME_IsUsingAtomicResistanceOverride();
    void OBME_IsUsingAtomicResistanceOverride(bool value);
    bool OBME_IsUsingParamFlagCOverride();
    void OBME_IsUsingParamFlagCOverride(bool value);
    bool OBME_IsUsingParamFlagDOverride();
    void OBME_IsUsingParamFlagDOverride(bool value);
    bool OBME_IsUsingDisabledOverride();
    void OBME_IsUsingDisabledOverride(bool value);
    bool OBME_IsUsingUnknownOOverride();
    void OBME_IsUsingUnknownOOverride(bool value);
    bool OBME_IsUsingNoHitEffectOverride();
    void OBME_IsUsingNoHitEffectOverride(bool value);
    bool OBME_IsUsingPersistOnDeathOverride();
    void OBME_IsUsingPersistOnDeathOverride(bool value);
    bool OBME_IsUsingExplodesWithForceOverride();
    void OBME_IsUsingExplodesWithForceOverride(bool value);
    bool OBME_IsUsingHiddenOverride();
    void OBME_IsUsingHiddenOverride(bool value);

    bool OBME_IsOverrideFlagMask(UINT32 Mask, bool Exact=false);
    void OBME_SetOverrideFlagMask(UINT32 Mask);

    bool OBME_IsHostile();
    void OBME_IsHostile(bool value);
    bool OBME_IsRecovers();
    void OBME_IsRecovers(bool value);
    bool OBME_IsParamFlagA();
    void OBME_IsParamFlagA(bool value);
    bool OBME_IsBeneficial();
    void OBME_IsBeneficial(bool value);
    bool OBME_IsFXPersists();
    void OBME_IsFXPersists(bool value);
    bool OBME_IsUnknownF();
    void OBME_IsUnknownF(bool value);
    bool OBME_IsNoRecast();
    void OBME_IsNoRecast(bool value);
    bool OBME_IsParamFlagB();
    void OBME_IsParamFlagB(bool value);
    bool OBME_IsMagnitudeIsRange();
    void OBME_IsMagnitudeIsRange(bool value);
    bool OBME_IsAtomicResistance();
    void OBME_IsAtomicResistance(bool value);
    bool OBME_IsParamFlagC();
    void OBME_IsParamFlagC(bool value);
    bool OBME_IsParamFlagD();
    void OBME_IsParamFlagD(bool value);
    bool OBME_IsDisabled();
    void OBME_IsDisabled(bool value);
    bool OBME_IsUnknownO();
    void OBME_IsUnknownO(bool value);
    bool OBME_IsNoHitEffect();
    void OBME_IsNoHitEffect(bool value);
    bool OBME_IsPersistOnDeath();
    void OBME_IsPersistOnDeath(bool value);
    bool OBME_IsExplodesWithForce();
    void OBME_IsExplodesWithForce(bool value);
    bool OBME_IsHidden();
    void OBME_IsHidden(bool value);

    bool OBME_IsFlagMask(UINT32 Mask, bool Exact=false);
    void OBME_SetFlagMask(UINT32 Mask);
    };

struct GENENIT
    {
    SINT32  value;
    UINT8   flags;
    UINT8   unused1[3];

    GENENIT();
    ~GENENIT();

    bool operator ==(const GENENIT &other) const;
    bool operator !=(const GENENIT &other) const;
    };

struct GENVALUEWEIGHT
    {
    UINT32  value;
    FLOAT32 weight;

    GENVALUEWEIGHT();
    ~GENVALUEWEIGHT();

    bool operator ==(const GENVALUEWEIGHT &other) const;
    bool operator !=(const GENVALUEWEIGHT &other) const;
    };

struct GENCNTO
    {
    FORMID  item;
    SINT32  count;

    GENCNTO();
    ~GENCNTO();

    bool operator ==(const GENCNTO &other) const;
    bool operator !=(const GENCNTO &other) const;
    };

struct GENACBS
    {
    UINT32  flags;
    UINT16  baseSpell, fatigue, barterGold;
    SINT16  level;
    UINT16  calcMin, calcMax;

    GENACBS();
    ~GENACBS();

    bool operator ==(const GENACBS &other) const;
    bool operator !=(const GENACBS &other) const;
    };

struct GENSNAM
    {
    FORMID  faction;
    UINT8   rank, unused1[3];

    GENSNAM();
    ~GENSNAM();

    bool operator ==(const GENSNAM &other) const;
    bool operator !=(const GENSNAM &other) const;
    };

struct GENAIDT
    {
    UINT8   aggression, confidence, energyLevel, responsibility;
    UINT32  flags;
    SINT8   trainSkill;
    UINT8   trainLevel, unused1[2];

    GENAIDT();
    ~GENAIDT();

    bool operator ==(const GENAIDT &other) const;
    bool operator !=(const GENAIDT &other) const;
    };

struct GENCTDA
    {
    UINT8   operType, unused1[3];
    FLOAT32 compValue;
    UINT32  ifunc;
    FORMID_OR_UINT32 param1, param2;
    UINT8   unused2[4];

    enum operTypeType
        {
        eEqual          = 0x00,
        eNotEqual       = 0x20,
        eGreater        = 0x40,
        eGreaterOrEqual = 0x60,
        eLess           = 0x80,
        eLessOrEqual    = 0xA0
        };
    enum operTypeFlag
        {
        fIsNone        = 0x00,
        fIsOr          = 0x01,
        fIsRunOnTarget = 0x02,
        fIsUseGlobal   = 0x04
        };

    GENCTDA();
    ~GENCTDA();

    bool operator ==(const GENCTDA &other) const;
    bool operator !=(const GENCTDA &other) const;

    bool IsEqual();
    void IsEqual(bool value);
    bool IsNotEqual();
    void IsNotEqual(bool value);
    bool IsGreater();
    void IsGreater(bool value);
    bool IsGreaterOrEqual();
    void IsGreaterOrEqual(bool value);
    bool IsLess();
    void IsLess(bool value);
    bool IsLessOrEqual();
    void IsLessOrEqual(bool value);
    bool IsType(UINT8 Type);
    void SetType(UINT8 Type);

    bool IsNone();
    void IsNone(bool value);
    bool IsOr();
    void IsOr(bool value);
    bool IsRunOnTarget();
    void IsRunOnTarget(bool value);
    bool IsUseGlobal();
    void IsUseGlobal(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);
    };

struct GENCLR
    {
    UINT8   red, green, blue, unused1;

    GENCLR(UINT8   _red=0, UINT8   _green=0, UINT8   _blue=0, UINT8   _unused1=0);
    ~GENCLR();

    bool operator ==(const GENCLR &other) const;
    bool operator !=(const GENCLR &other) const;
    };

struct GENMODEL
    {
    ReqSubRecord<GENFLOAT> MODB;
    StringRecord MODL;
    RawRecord MODT;

    bool operator ==(const GENMODEL &other) const;
    bool operator !=(const GENMODEL &other) const;
    };

struct GENXOWN
    {
    ReqSubRecord<GENFID> XOWN;
    SemiOptSubRecord<GENS32> XRNK;
    OptSubRecord<GENFID> XGLB;

    bool operator ==(const GENXOWN &other) const;
    bool operator !=(const GENXOWN &other) const;
    };

struct GENXPCI
    {
    OptSubRecord<GENFID> XPCI;
    StringRecord FULL;

    bool operator ==(const GENXPCI &other) const;
    bool operator !=(const GENXPCI &other) const;
    };

struct GENXLOD
    {
    FLOAT32 lod1, lod2, lod3;

    GENXLOD();
    ~GENXLOD();

    bool operator ==(const GENXLOD &other) const;
    bool operator !=(const GENXLOD &other) const;
    };

struct GENXESP
    {
    FORMID  parent;
    UINT8   flags, unused1[3];

    GENXESP();
    ~GENXESP();

    bool operator ==(const GENXESP &other) const;
    bool operator !=(const GENXESP &other) const;
    };

struct GENXSCL
    {
    FLOAT32 scale;

    GENXSCL();
    ~GENXSCL();

    bool operator ==(const GENXSCL &other) const;
    bool operator !=(const GENXSCL &other) const;
    };

struct GENPOSDATA
    {
    FLOAT32 posX, posY, posZ, rotX, rotY, rotZ;

    GENPOSDATA();
    ~GENPOSDATA();

    bool operator ==(const GENPOSDATA &other) const;
    bool operator !=(const GENPOSDATA &other) const;
    };

struct GENPGRP
    {
    FLOAT32 x, y, z;
    UINT8   connections;
    UINT8   unused1[3];

    GENPGRP();
    ~GENPGRP();

    bool operator ==(const GENPGRP &other) const;
    bool operator !=(const GENPGRP &other) const;
    };

struct LVLLVLO
    {
    SINT16  level;
    UINT8   unused1[2];
    UINT32  listId;
    SINT16  count;
    UINT8   unused2[2];

    LVLLVLO();
    ~LVLLVLO();

    bool operator ==(const LVLLVLO &other) const;
    bool operator !=(const LVLLVLO &other) const;
    };

struct MAGICOBME
    {
    UINT8   recordVersion, betaVersion, minorVersion, majorVersion;
    UINT8   reserved[0x1C];

    MAGICOBME();
    ~MAGICOBME();

    bool operator ==(const MAGICOBME &other) const;
    bool operator !=(const MAGICOBME &other) const;
    };

struct OBMEMAGIC
    {
    ReqSubRecord<MAGICOBME> OBME;
    RawRecord DATX;

    bool operator ==(const OBMEMAGIC &other) const;
    bool operator !=(const OBMEMAGIC &other) const;
    };


struct GENMNAM
    {
    SINT32  dimX, dimY;
    SINT16  NWCellX, NWCellY, SECellX, SECellY;

    GENMNAM();
    ~GENMNAM();

    bool operator ==(const GENMNAM &other) const;
    bool operator !=(const GENMNAM &other) const;
    };

struct GENNAM
    {
    FLOAT32 x, y;

    GENNAM();
    ~GENNAM();

    bool operator ==(const GENNAM &other) const;
    bool operator !=(const GENNAM &other) const;
    };

struct GENTNAM
    {
    UINT8   markerType, unused1;

    GENTNAM();
    ~GENTNAM();

    bool operator ==(const GENTNAM &other) const;
    bool operator !=(const GENTNAM &other) const;
    };

//Unfilled
struct GENDNAM
    {
    FLOAT32  defaultLandHeight, defaultWaterHeight;

    GENDNAM();
    ~GENDNAM();

    bool operator ==(const GENDNAM &other) const;
    bool operator !=(const GENDNAM &other) const;
    };

struct GENONAM
    {
    FLOAT32  mapScale, xCellOffset, yCellOffset;

    GENONAM();
    ~GENONAM();

    bool operator ==(const GENONAM &other) const;
    bool operator !=(const GENONAM &other) const;
    };

struct GENIMPS
    {
    UINT32   material;
    FORMID   oldImpact, newImpact;

    GENIMPS();
    ~GENIMPS();

    bool operator ==(const GENIMPS &other) const;
    bool operator !=(const GENIMPS &other) const;
    };

struct GENXPRM
    {
    FLOAT32  xBound, yBound, zBound;
    FLOAT32  red, green, blue, unknown;
    UINT32   type;

    GENXPRM();
    ~GENXPRM();

    bool operator ==(const GENXPRM &other) const;
    bool operator !=(const GENXPRM &other) const;
    };

struct GENXMBO
    {
    FLOAT32  x, y, z;

    GENXMBO();
    ~GENXMBO();

    bool operator ==(const GENXMBO &other) const;
    bool operator !=(const GENXMBO &other) const;
    };

struct GENXTEL
    {
    FORMID  destinationFid;
    GENPOSDATA destination;
    UINT32 flags;

    GENXTEL();
    ~GENXTEL();

    bool operator ==(const GENXTEL &other) const;
    bool operator !=(const GENXTEL &other) const;
    };

struct GENXMRK
    {
    ReqSubRecord<GENU8> FNAM; //Flags
    StringRecord FULL; //Name
    ReqSubRecord<GENTNAM> TNAM; //Type
    OptSubRecord<GENFID> WMI1; //Reputation

    bool operator ==(const GENXMRK &other) const;
    bool operator !=(const GENXMRK &other) const;
    };

struct GENMMRK
    {
    RawRecord FULL; //Unknown
    OptSubRecord<GENFID> CNAM; //Audio Location
    RawRecord BNAM; //Unknown
    OptSubRecord<GENFLOAT> MNAM; //Unknown
    OptSubRecord<GENFLOAT> NNAM; //Unknown

    bool operator ==(const GENXMRK &other) const;
    bool operator !=(const GENXMRK &other) const;
    };

struct GENXRDO
    {
    FLOAT32  rangeRadius;
    UINT32 rangeType;
    FLOAT32 staticPercentage;
    FORMID positionReference;

    GENXRDO();
    ~GENXRDO();

    bool operator ==(const GENXRDO &other) const;
    bool operator !=(const GENXRDO &other) const;
    };

struct GENAMMO
    {
    OptSubRecord<GENFID> XAMT; //Type
    OptSubRecord<GENS32> XAMC; //Count

    bool operator ==(const GENAMMO &other) const;
    bool operator !=(const GENAMMO &other) const;
    };

struct GENXPWR
    {
    OptSubRecord<GENFID> XAMT; //Reference
    OptSubRecord<GENU32> XAMC; //Flags

    bool operator ==(const GENXPWR &other) const;
    bool operator !=(const GENXPWR &other) const;
    };

struct GENXDCR
    {
    FORMID reference; //Reference
    //Unknown? OptSubRecord<GENS32> XAMC; //Count

    GENXDCR();
    ~GENXDCR();

    bool operator ==(const GENXDCR &other) const;
    bool operator !=(const GENXDCR &other) const;
    };

struct GENXCLP
    {
    GENCLR start; //Link Start Color
    GENCLR end; //Link End Color

    bool operator ==(const GENXCLP &other) const;
    bool operator !=(const GENXCLP &other) const;
    };

struct GENXAPR
    {
    FORMID reference; //Reference
    FLOAT32 delay; //Delay

    GENXAPR();
    ~GENXAPR();

    bool operator ==(const GENXAPR &other) const;
    bool operator !=(const GENXAPR &other) const;
    };

struct GENACTPARENT
    {
    OptSubRecord<GENU8> XAPD; //Flags
    std::vector<ReqSubRecord<GENXAPR> *> XAPR; //Activate Parent Refs

    enum flagsFlags
        {
        fIsParentActivateOnly = 0x00000001
        };

    bool   IsParentActivateOnly();
    void   IsParentActivateOnly(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    bool operator ==(const GENACTPARENT &other) const;
    bool operator !=(const GENACTPARENT &other) const;
    };

struct GENXNDP
    {
    FORMID navMesh; //Navigation Mesh
    UINT16 unknown1; //Unknown
    UINT8  unused1[2]; //Unused

    GENXNDP();
    ~GENXNDP();

    bool operator ==(const GENXNDP &other) const;
    bool operator !=(const GENXNDP &other) const;
    };

struct GENPOSITION
    {
    FLOAT32 width, height; //Size
    FLOAT32 xPos, yPos, zPos; //Position
    FLOAT32 q1, q2, q3, q4; //Rotation (Quaternion?)

    GENPOSITION();
    ~GENPOSITION();

    bool operator ==(const GENPOSITION &other) const;
    bool operator !=(const GENPOSITION &other) const;
    };

struct GENXRMR
    {
    UINT16 count; //Linked Rooms Count
    UINT8  unknown1[2]; //Unknown

    GENXRMR();
    ~GENXRMR();

    bool operator ==(const GENXRMR &other) const;
    bool operator !=(const GENXRMR &other) const;
    };

struct GENROOM
    {
    OptSubRecord<GENXRMR> XRMR; //Room Data
    std::vector<FORMID> XLRM; //Linked Rooms

    bool operator ==(const GENROOM &other) const;
    bool operator !=(const GENROOM &other) const;
    };

//Fallout New Vegas Chunks

struct GENOBND
    {
    SINT16   x;
    SINT16   y;
    SINT16   z;

    GENOBND();
    ~GENOBND();

    bool operator ==(const GENOBND &other) const;
    bool operator !=(const GENOBND &other) const;
    };

struct GENDODT
    {
    FLOAT32 minWidth, maxWidth, minHeight, maxHeight, depth, shininess;
    FLOAT32 scale;
    UINT8   passes;
    UINT8   flags;
    UINT8   unused1[2];
    UINT8   red, green, blue, unused2;

    enum DODTFlags
        {
        fIsParallax      = 0x00000001,
        fIsAlphaBlending = 0x00000002,
        fIsAlphaTesting  = 0x00000004
        };

    GENDODT();
    ~GENDODT();

    bool operator ==(const GENDODT &other) const;
    bool operator !=(const GENDODT &other) const;

    bool IsParallax();
    void IsParallax(bool value);
    bool IsAlphaBlending();
    void IsAlphaBlending(bool value);
    bool IsAlphaTesting();
    void IsAlphaTesting(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);
    };

struct GENPATROL
    {
    ReqSubRecord<GENFLOAT> XPRD; //Idle Time
    ReqSubRecord<GENFID> INAM; //Idle
    OptSubRecord<GENSCRIPT> Script; //Script
    ReqSubRecord<GENFID> TNAM; //Topic

    bool operator ==(const GENPATROL &other) const;
    bool operator !=(const GENPATROL &other) const;
    };

struct GENXCLP
    {
    GENCLR start;
    GENCLR end;

    bool operator ==(const GENXCLP &other) const;
    bool operator !=(const GENXCLP &other) const;
    };

//Unfilled
struct FNVXOWN
    {
    ReqSubRecord<GENFID> XOWN;
    SemiOptSubRecord<GENS32> XRNK; //Faction Rank

    bool operator ==(const FNVXOWN &other) const;
    bool operator !=(const FNVXOWN &other) const;
    };

struct FNVXLOC
    {
    UINT8   level, unused1[3];
    FORMID  key;
    UINT8   flags, unused2[3], unknown[8];

    FNVXLOC();
    ~FNVXLOC();

    bool operator ==(const FNVXLOC &other) const;
    bool operator !=(const FNVXLOC &other) const;
    };

struct FNVXLOC
    {
    UINT8   level, unused1[3];
    FORMID  key;
    UINT8   flags, unused2[3], unknown[8];

    FNVXLOC();
    ~FNVXLOC();

    bool operator ==(const FNVXLOC &other) const;
    bool operator !=(const FNVXLOC &other) const;
    };

struct FNVMODS //Alternate Texture
    {
    STRING  name; //3D Name
    FORMID  texture; //New Texture
    SINT32  index; //3D Index

    FNVMODS();
    ~FNVMODS();

    bool operator ==(const FNVMODS &other) const;
    bool operator !=(const FNVMODS &other) const;
    };

struct FNVMODEL
    {
    StringRecord MODL; //Model Filename
    OptSubRecord<GENFLOAT> MODB; //Bound Radius (Unknown?)
    RawRecord MODT; //Texture Files Hashes
    std::vector<FNVMODS *> MODS; //Alternate Textures
    OptSubRecord<GENU8> MODD; //FaceGen Model Flags

    enum moddFlags
        {
        fIsHead      = 0x00000001,
        fIsTorso     = 0x00000002,
        fIsRightHand = 0x00000004,
        fIsLeftHand  = 0x00000008
        };

    bool   IsHead();
    void   IsHead(bool value);
    bool   IsTorso();
    void   IsTorso(bool value);
    bool   IsRightHand();
    void   IsRightHand(bool value);
    bool   IsLeftHand();
    void   IsLeftHand(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    bool operator ==(const GENMODEL &other) const;
    bool operator !=(const GENMODEL &other) const;
    };

struct FNVBIPEDMODEL
    {
    StringRecord MODL; //Model Filename
    RawRecord MODT; //Texture Files Hashes
    std::vector<FNVMODS *> MODS; //Alternate Textures
    OptSubRecord<GENU8> MODD; //FaceGen Model Flags

    enum moddFlags
        {
        fIsHead      = 0x00000001,
        fIsTorso     = 0x00000002,
        fIsRightHand = 0x00000004,
        fIsLeftHand  = 0x00000008
        };

    bool   IsHead();
    void   IsHead(bool value);
    bool   IsTorso();
    void   IsTorso(bool value);
    bool   IsRightHand();
    void   IsRightHand(bool value);
    bool   IsLeftHand();
    void   IsLeftHand(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    bool operator ==(const FNVBIPEDMODEL &other) const;
    bool operator !=(const FNVBIPEDMODEL &other) const;
    };

struct FNVWORLDMODEL
    {
    StringRecord MODL; //Model Filename
    RawRecord MODT; //Texture Files Hashes
    std::vector<FNVMODS *> MODS; //Alternate Textures

    bool operator ==(const FNVWORLDMODEL &other) const;
    bool operator !=(const FNVWORLDMODEL &other) const;
    };

struct FNVEQUIPDATA
    {
    SINT32  value, health; //Value, Health
    FLOAT32 weight; //Weight

    FNVEQUIPDATA();
    ~FNVEQUIPDATA();

    bool operator ==(const FNVEQUIPDATA &other) const;
    bool operator !=(const FNVEQUIPDATA &other) const;
    };

struct FNVEQUIPDNAM
    {
    SINT16  AR; //Armor Resistance
    UINT16  flags; //Flags
    FLOAT32 DT; //Damage Threshold
    UINT8   unknown[4]; //Unknown ?

    FNVEQUIPDNAM();
    ~FNVEQUIPDNAM();

    bool operator ==(const FNVEQUIPDNAM &other) const;
    bool operator !=(const FNVEQUIPDNAM &other) const;
    };


struct GENBMDT
    {
    UINT32  bipedFlags; //Type
    UINT8   generalFlags; //Flags

    GENBMDT();
    ~GENBMDT();

    bool operator ==(const GENBMDT &other) const;
    bool operator !=(const GENBMDT &other) const;
    };

struct GENDEST //Destructable Header
    {
    SINT32  health; //Health
    UINT8   count; //Count
    UINT8   flags; //Flags
    UINT8   unused[2]; //Unused

    GENDEST();
    ~GENDEST();

    bool operator ==(const GENDEST &other) const;
    bool operator !=(const GENDEST &other) const;
    };

struct DESTMODEL
    {
    StringRecord MODL; //Model Filename
    RawRecord MODT; //Texture Files Hashes

    bool operator ==(const DESTMODEL &other) const;
    bool operator !=(const DESTMODEL &other) const;
    };

struct DESTSTAGE //Destructable Stage
    {
    OptSubRecord<DESTDSTD> DSTD; //Destruction Stage Data
    std::vector<DESTMODEL *> Models;

    bool operator ==(const DESTSTAGE &other) const;
    bool operator !=(const DESTSTAGE &other) const;
    };

struct GENDESTRUCT //Destructable
    {
    OptSubRecord<GENDEST> DEST; //Destructable Header
    std::vector<DESTSTAGE *> Stages; //Destructable Stages

    enum flagsFlags
        {
        fIsVATSTargetable = 0x01
        };

    GENDESTRUCT();
    ~GENDESTRUCT();

    bool   IsVATSTargetable();
    void   IsVATSTargetable(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    bool operator ==(const GENDESTRUCT &other) const;
    bool operator !=(const GENDESTRUCT &other) const;
    };

struct FNVCTDA //Condition
    {
    UINT8   operType, unused1[3]; //Type, Unused
    FORMID_OR_FLOAT32 compValue; //Float or Global (if fIsUseGlobal is true)
    UINT32  ifunc;
    FORMID_OR_UINT32 param1, param2;
    UINT32  runOn; //Run On
    FORMID_OR_UINT32 reference; //Reference (if runOn == 2) or Unused

    enum operTypeType
        {
        eEqual          = 0x00,
        eNotEqual       = 0x20,
        eGreater        = 0x40,
        eGreaterOrEqual = 0x60,
        eLess           = 0x80,
        eLessOrEqual    = 0xA0
        };

    enum operTypeFlag
        {
        fIsNone        = 0x00,
        fIsOr          = 0x01,
        fIsRunOnTarget = 0x02,
        fIsUseGlobal   = 0x04
        };

    enum operRunOnType
        {
        eSubject = 0,
        eTarget,
        eReference,
        eCombatTarget,
        eLinkedReference
        };

    FNVCTDA();
    ~FNVCTDA();

    bool operator ==(const FNVCTDA &other) const;
    bool operator !=(const FNVCTDA &other) const;

    bool IsEqual();
    void IsEqual(bool value);
    bool IsNotEqual();
    void IsNotEqual(bool value);
    bool IsGreater();
    void IsGreater(bool value);
    bool IsGreaterOrEqual();
    void IsGreaterOrEqual(bool value);
    bool IsLess();
    void IsLess(bool value);
    bool IsLessOrEqual();
    void IsLessOrEqual(bool value);
    bool IsType(UINT8 Type);
    void SetType(UINT8 Type);

    bool IsNone();
    void IsNone(bool value);
    bool IsOr();
    void IsOr(bool value);
    bool IsRunOnTarget();
    void IsRunOnTarget(bool value);
    bool IsUseGlobal();
    void IsUseGlobal(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);

    bool   IsRunOnSubject();
    void   IsRunOnSubject(bool value);
    bool   IsRunOnTarget();
    void   IsRunOnTarget(bool value);
    bool   IsRunOnReference();
    void   IsRunOnReference(bool value);
    bool   IsRunOnCombatTarget();
    void   IsRunOnCombatTarget(bool value);
    bool   IsRunOnLinkedReference();
    void   IsRunOnLinkedReference(bool value);
    bool   IsRunOnType(UINT8 Type, bool Exact=false);
    void   SetRunOnType(UINT8 Type);
    };

struct FNVENIT //Effect Data
    {
    SINT32  value; //Value
    UINT8   flags; //Flags?
    UINT8   unused1[3]; //Unused
    FORMID  withdrawalEffect; //Withdrawal Effect
    FLOAT32 addictionChance; //Addiction Chance
    FORMID  consumeSound; //Sound - Consume

    FNVENIT();
    ~FNVENIT();

    bool operator ==(const FNVENIT &other) const;
    bool operator !=(const FNVENIT &other) const;
    };

struct FNVEFIT
    {
    UINT32  magnitude, area, duration, rangeType;
    ACTORVALUE actorValue;

    FNVEFIT();
    ~FNVEFIT();

    bool operator ==(const FNVEFIT &other) const;
    bool operator !=(const FNVEFIT &other) const;
    };

struct FNVEffect
    {
    ReqSubRecord<GENEFID> EFID; //Effect ID
    ReqSubRecord<FNVEFIT> EFIT; //Effect Data
    std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions

    enum eRanges
        {
        eRangeSelf    = 0,
        eRangeTouch   = 1,
        eRangeTarget  = 2
        };

    bool operator ==(const FNVEffect &other) const;
    bool operator !=(const FNVEffect &other) const;

    bool IsRangeSelf();
    void IsRangeSelf(bool value);
    bool IsRangeTouch();
    void IsRangeTouch(bool value);
    bool IsRangeTarget();
    void IsRangeTarget(bool value);
    bool IsRange(UINT32  Mask);
    void SetRange(UINT32  Mask);
    };

struct FNVAIDT
    {
    UINT8   aggression, confidence, energyLevel, responsibility, mood, unused1[3];
    UINT32  flags;
    SINT8   trainSkill;
    UINT8   trainLevel, assistance, aggroFlags;
    SINT32  aggroRadius;

    FNVAIDT();
    ~FNVAIDT();

    bool operator ==(const FNVAIDT &other) const;
    bool operator !=(const FNVAIDT &other) const;
    };

struct FNVACBS // Configuration
    {
    UINT32  flags; // Flags
    UINT16  fatigue, barterGold; // Fatigue, Barter gold
    SINT16  level; // Level or Level Multiplier
    UINT16  calcMin, calcMax, speedMult; // Calc min, Calc max, Speed Multiplier
    FLOAT32 karma; // Karma (Alignment)
    SINT16  dispBase; // Disposition Base
    UINT16  templateFlags; // Template Flags

    FNVACBS();
    ~FNVACBS();

    bool operator ==(const FNVACBS &other) const;
    bool operator !=(const FNVACBS &other) const;
    };

struct GENCOED // Extra Data
    {
    FORMID  owner; // Owner
    FORMID_OR_UINT32 globalOrRank; // Global Variable / Required Rank (global if owner is NPC_, rank if owner is FACT)
    FLOAT32 condition; // Item Condition

    GENCOED();
    ~GENCOED();

    bool operator ==(const GENCOED &other) const;
    bool operator !=(const GENCOED &other) const;
    };

struct FNVCNTO
    {
    ReqSubRecord<GENCNTO> CNTO;
    OptSubRecord<GENCOED> COED;

    bool IsGlobal();
    bool IsRank();
    bool IsUnused();

    bool operator ==(const FNVCNTO &other) const;
    bool operator !=(const FNVCNTO &other) const;
    };