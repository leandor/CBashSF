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

struct GENFLAG
    {
    UINT8 flags;
    
    GENFLAG();
    ~GENFLAG();
    
    bool operator ==(const GENFLAG& other) const;
    bool operator !=(const GENFLAG &other) const;
    };

struct GENXNAM
    {
    FORMID faction;
    SINT32 mod;
    
    GENXNAM();
    ~GENXNAM();
    
    bool operator ==(const GENXNAM& other) const;
    bool operator !=(const GENXNAM &other) const;
    };

struct GENFID
    {
    FORMID fid;
    
    GENFID();
    ~GENFID();

    bool operator ==(const GENFID& other) const;
    bool operator !=(const GENFID &other) const;
    };

struct GENSCHR
    {
    UINT8 unused1[4];
    UINT32 numRefs, compiledSize, lastIndex, scriptType;
    
    GENSCHR();
    ~GENSCHR();

    bool operator ==(const GENSCHR& other) const;
    bool operator !=(const GENSCHR &other) const;
    };

struct GENSCR_
    {
    FORMID_OR_UINT32 reference;
    bool isSCRO;
    
    GENSCR_();
    ~GENSCR_();

    bool operator ==(const GENSCR_& other) const;
    bool operator !=(const GENSCR_ &other) const;
    };

struct GENEFID
    {
    UINT32 name;
    
    GENEFID();
    ~GENEFID();

    bool operator ==(const GENEFID &other) const;
    bool operator !=(const GENEFID &other) const;
    };

struct GENEFIT
    {
    UINT32 name, magnitude, area, duration;
    FORMID recipient;
    UINT32 actorValue;
    
    GENEFIT();
    ~GENEFIT();

    bool operator ==(const GENEFIT& other) const;
    bool operator !=(const GENEFIT &other) const;
    };

struct GENSCIT
    {
    FORMID script;
    UINT32 school, visual;
    UINT8 flags, unused1[3];
    
    GENSCIT();
    ~GENSCIT();

    bool operator ==(const GENSCIT& other) const;
    bool operator !=(const GENSCIT &other) const;
    };

struct OBMEEFME
    {
    UINT8 recordVersion, betaVersion, minorVersion, majorVersion;
    UINT8 efitParamInfo;
    UINT8 efixParamInfo;
    UINT8 reserved[0xA];
    
    OBMEEFME();
    ~OBMEEFME();

    bool operator ==(const OBMEEFME &other) const;
    bool operator !=(const OBMEEFME &other) const;
    };

struct OBMEEFIX
    {
    UINT32 efixOverrideMask;
    UINT32 efixFlags;
    FLOAT32 baseCost;
    UINT32 resistAV;
    UINT8 reserved[0x10];
    
    OBMEEFIX();
    ~OBMEEFIX();

    bool operator ==(const OBMEEFIX &other) const;
    bool operator !=(const OBMEEFIX &other) const;
    };

struct OBMEEffect
    {
    ReqSubRecord<OBMEEFME> EFME;
    StringRecord EFII;
    OptSubRecord<OBMEEFIX> EFIX;

    bool operator ==(const OBMEEffect& other) const;
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
        fIsHostile = 0x00000001
        };
    enum eRanges
        {
        eRangeSelf    = 0,
        eRangeTouch   = 1,
        eRangeTarget  = 2
        };

    bool operator ==(const GENEffect& other) const;
    bool operator !=(const GENEffect &other) const;
    
    bool IsHostile();
    void IsHostile(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);
    bool IsRangeSelf();
    void IsRangeSelf(bool value);
    bool IsRangeTouch();
    void IsRangeTouch(bool value);
    bool IsRangeTarget();
    void IsRangeTarget(bool value);
    bool IsRange(UINT32 Mask);
    void SetRange(UINT32 Mask);
    };

struct GENANAM
    {
    UINT16 enchantPoints;
    
    GENANAM();
    ~GENANAM();

    bool operator ==(const GENANAM &other) const;
    bool operator !=(const GENANAM &other) const;
    };

struct GENUFLAG
    {
    UINT32 flags;
    
    GENUFLAG();
    ~GENUFLAG();

    bool operator ==(const GENUFLAG &other) const;
    bool operator !=(const GENUFLAG &other) const;
    };

struct GENWEIGHT
    {
    FLOAT32 weight;
    
    GENWEIGHT();
    ~GENWEIGHT();

    bool operator ==(const GENWEIGHT &other) const;
    bool operator !=(const GENWEIGHT &other) const;
    };

struct GENENIT
    {
    SINT32 value;
    UINT8 flags;
    UINT8 unused1[3];
    
    GENENIT();
    ~GENENIT();

    bool operator ==(const GENENIT &other) const;
    bool operator !=(const GENENIT &other) const;
    };

struct GENVALUEWEIGHT
    {
    UINT32 value;
    FLOAT32 weight;
    
    GENVALUEWEIGHT();
    ~GENVALUEWEIGHT();

    bool operator ==(const GENVALUEWEIGHT &other) const;
    bool operator !=(const GENVALUEWEIGHT &other) const;
    };

struct GENCNTO
    {
    FORMID item;
    SINT32 count;
    
    GENCNTO();
    ~GENCNTO();

    bool operator ==(const GENCNTO &other) const;
    bool operator !=(const GENCNTO &other) const;
    };

struct GENACBS
    {
    UINT32 flags;
    UINT16 baseSpell, fatigue, barterGold;
    SINT16 level;
    UINT16 calcMin, calcMax;
    
    GENACBS();
    ~GENACBS();

    bool operator ==(const GENACBS &other) const;
    bool operator !=(const GENACBS &other) const;
    };

struct GENSNAM
    {
    FORMID faction;
    UINT8 rank, unused1[3];
    
    GENSNAM();
    ~GENSNAM();

    bool operator ==(const GENSNAM &other) const;
    bool operator !=(const GENSNAM &other) const;
    };

struct GENAIDT
    {
    UINT8 aggression, confidence, energyLevel, responsibility;
    UINT32 flags;
    SINT8 trainSkill;
    UINT8 trainLevel, unused1[2];
    
    GENAIDT();
    ~GENAIDT();

    bool operator ==(const GENAIDT &other) const;
    bool operator !=(const GENAIDT &other) const;
    };

struct GENCTDA
    {
    UINT8 operType, unused1[3];
    FLOAT32 compValue;
    UINT32 ifunc;
    FORMID_OR_UINT32 param1, param2;
    UINT8 unused2[4];
        
    enum operTypeType
        {
        eEqual          = 0x00000000,
        eNotEqual       = 0x00000020,
        eGreater        = 0x00000040,
        eGreaterOrEqual = 0x00000060,
        eLess           = 0x00000080,
        eLessOrEqual    = 0x000000A0
        };
    enum operTypeFlag
        {
        fIsNone        = 0x00000000,
        fIsOr          = 0x00000001,
        fIsRunOnTarget = 0x00000002,
        fIsUseGlobal   = 0x00000004
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
    UINT8 red, green, blue, unused1;
    
    GENCLR(UINT8 _red=0, UINT8 _green=0, UINT8 _blue=0, UINT8 _unused1=0);
    ~GENCLR();

    bool operator ==(const GENCLR &other) const;
    bool operator !=(const GENCLR &other) const;
    };

struct MODELMODB
    {
    FLOAT32 MODB;
    
    MODELMODB();
    ~MODELMODB();

    bool operator ==(const MODELMODB &other) const;
    bool operator !=(const MODELMODB &other) const;
    };

struct GENMODEL
    {
    ReqSubRecord<MODELMODB> MODB;
    StringRecord MODL;
    RawRecord MODT;

    bool operator ==(const GENMODEL &other) const;
    bool operator !=(const GENMODEL &other) const;
    };

struct GENRANK
    {
    SINT32 rank;
    
    GENRANK();
    ~GENRANK();

    bool operator ==(const GENRANK &other) const;
    bool operator !=(const GENRANK &other) const;
    };

struct GENXOWN
    {
    ReqSubRecord<GENFID> XOWN;
    SemiOptSubRecord<GENRANK> XRNK;
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
    FORMID parent;
    UINT8 flags, unused1[3];
    
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
    UINT8 connections;
    UINT8 unused1[3];
    
    GENPGRP();
    ~GENPGRP();

    bool operator ==(const GENPGRP &other) const;
    bool operator !=(const GENPGRP &other) const;
    };

struct MAGICOBME
    {
    UINT8 recordVersion, betaVersion, minorVersion, majorVersion;
    UINT8 reserved[0x1C];
    
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