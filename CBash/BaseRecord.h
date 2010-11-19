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
    unsigned char flags;
    GENFLAG():flags(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            if(debugLevel > 4)
                {
                indentation += 2;
                PrintIndent(indentation);
                printf("flags = %u\n", flags);
                indentation -= 2;
                }
        }
    #endif
    bool operator ==(const GENFLAG& other) const
        {
        return flags == other.flags;
        }
    bool operator !=(const GENFLAG &other) const
        {
        return !(*this == other);
        }
    };

struct GENXNAM
    {
    unsigned int faction;
    int mod;
    GENXNAM():faction(0), mod(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("%s - %i\n", PrintFormID(faction), mod);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENXNAM& other) const
        {
        return (faction == other.faction && mod == other.mod);
        }
    bool operator !=(const GENXNAM &other) const
        {
        return !(*this == other);
        }
    };

struct GENFID
    {
    unsigned int fid;
    GENFID():fid(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("%s\n", PrintFormID(fid));
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENFID& other) const
        {
        return fid == other.fid;
        }
    bool operator !=(const GENFID &other) const
        {
        return !(*this == other);
        }
    };

struct GENSCHR
    {
    unsigned char unused1[4];
    unsigned int numRefs, compiledSize, lastIndex, scriptType;
    GENSCHR():numRefs(0), compiledSize(0), lastIndex(0), scriptType(0)
        {
        memset(&unused1, 0x00, 4);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused1      = %02X%02X%02X%02X\n", unused1[0], unused1[1], unused1[2], unused1[3]);
                }
            PrintIndent(indentation);
            printf("numRefs      = %u\n", numRefs);
            PrintIndent(indentation);
            printf("compiledSize = %u\n", compiledSize);
            PrintIndent(indentation);
            printf("lastIndex    = %u\n", lastIndex);
            PrintIndent(indentation);
            printf("scriptType   = %u\n", scriptType);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENSCHR& other) const
        {
        return (numRefs == other.numRefs &&
                compiledSize == other.compiledSize &&
                lastIndex == other.lastIndex &&
                scriptType == other.scriptType);
        }
    bool operator !=(const GENSCHR &other) const
        {
        return !(*this == other);
        }
    };

struct GENSCR_
    {
    unsigned int reference;
    bool isSCRO;
    GENSCR_():reference(0),isSCRO(false) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        indentation += 2;
        PrintIndent(indentation);
        if(isSCRO)
            if(debugLevel > 3)
                printf("SCRO = %s\n", PrintFormID(reference));
            else
                printf("SCRO\n");
        else
            if(debugLevel > 3)
                printf("SCRV = %u\n", reference);
            else
                printf("SCRV\n");
        indentation -= 2;
        }
    #endif
    bool operator ==(const GENSCR_& other) const
        {
        return (reference == other.reference &&
                isSCRO == other.isSCRO);
        }
    bool operator !=(const GENSCR_ &other) const
        {
        return !(*this == other);
        }
    };

struct GENEFID
    {
    unsigned int name;
    GENEFID():name(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        indentation += 2;
        if(debugLevel > 3)
            {
            PrintIndent(indentation);
            printf("name = %c%c%c%c\n", ((char *)&name)[0], ((char *)&name)[1], ((char *)&name)[2], ((char *)&name)[3]);
            }
        indentation -= 2;
        }
    #endif
    bool operator ==(const GENEFID &other) const
        {
        return (name == other.name);
        }
    bool operator !=(const GENEFID &other) const
        {
        return !(*this == other);
        }
    };

struct GENEFIT
    {
    unsigned int name, magnitude, area, duration, recipient;
    unsigned int actorValue;
    GENEFIT():name(0), magnitude(0), area(0), duration(0),
        recipient(0), actorValue(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("name       = %c%c%c%c\n", ((char*)&name)[0], ((char*)&name)[1], ((char*)&name)[2], ((char*)&name)[3]);
            PrintIndent(indentation);
            printf("magnitude  = %u\n", magnitude);
            PrintIndent(indentation);
            printf("area       = %u\n", area);
            PrintIndent(indentation);
            printf("duration   = %u\n", duration);
            PrintIndent(indentation);
            printf("recipient  = %u\n", recipient);
            PrintIndent(indentation);
            printf("actorValue = %i\n", actorValue);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENEFIT& other) const
        {
        return (name == other.name &&
                magnitude == other.magnitude &&
                area == other.area &&
                duration == other.duration &&
                recipient == other.recipient &&
                actorValue == other.actorValue);
        }
    bool operator !=(const GENEFIT &other) const
        {
        return !(*this == other);
        }
    };

struct GENSCIT
    {
    unsigned int script, school, visual;
    unsigned char flags, unused1[3];
    GENSCIT():script(0), school(0), visual(0), flags(0)
        {
        memset(&unused1, 0x00, 3);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("script  = %s\n", PrintFormID(script));
            PrintIndent(indentation);
            printf("school  = %u\n", school);
            PrintIndent(indentation);
            printf("visual  = %c%c%c%c\n", ((char*)&visual)[0], ((char*)&visual)[1], ((char*)&visual)[2], ((char*)&visual)[3]);
            if(debugLevel > 4)
                {
                PrintIndent(indentation);
                printf("flags   = %u\n", flags);
                }
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused1 = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENSCIT& other) const
        {
        return (script == other.script &&
                school == other.school &&
                visual == other.visual &&
                flags == other.flags);
        }
    bool operator !=(const GENSCIT &other) const
        {
        return !(*this == other);
        }
    };

struct OBMEEFME
    {
    unsigned char recordVersion, betaVersion, minorVersion, majorVersion;
    unsigned char efitParamInfo;
    unsigned char efixParamInfo;
    unsigned char reserved[0xA];
    OBMEEFME():recordVersion(0), betaVersion(0), minorVersion(0), majorVersion(0), efitParamInfo(0), efixParamInfo(0)
        {
        memset(&reserved, 0x00, 0xA);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("recordVersion = %i\n", recordVersion);
            printf("betaVersion   = %i\n", betaVersion);
            printf("minorVersion  = %i\n", minorVersion);
            printf("majorVersion  = %i\n", majorVersion);

            printf("efitParamInfo = %i\n", efitParamInfo);
            printf("efixParamInfo = %i\n", efixParamInfo);
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("reserved = ");
                for(unsigned int x = 0; x < 0xA; x++)
                    printf("%c", reserved[x]);
                pritnf("\n");
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const OBMEEFME &other) const
        {
        return (recordVersion == other.recordVersion &&
                betaVersion == other.betaVersion &&
                minorVersion == other.minorVersion &&
                majorVersion == other.majorVersion &&
                efitParamInfo == other.efitParamInfo &&
                efixParamInfo == other.efixParamInfo &&
                reserved == other.reserved);
        }
    bool operator !=(const OBMEEFME &other) const
        {
        return !(*this == other);
        }
    };

struct OBMEEFIX
    {
    unsigned int efixOverrideMask;
    unsigned int efixFlags;
    float baseCost;
    unsigned int resistAV;
    unsigned char reserved[0x10];
    OBMEEFIX():efixOverrideMask(0), efixFlags(0), baseCost(0.0), resistAV(0)
        {
        memset(&reserved, 0x00, 0x10);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("efixOverrideMask = %i\n", efixOverrideMask);
            printf("efixFlags        = %i\n", efixFlags);
            printf("baseCost         = %f\n", baseCost);
            printf("resistAV         = %i\n", resistAV);

            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("reserved = ");
                for(unsigned int x = 0; x < 0x10; x++)
                    printf("%c", reserved[x]);
                pritnf("\n");
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const OBMEEFIX &other) const
        {
        return (efixOverrideMask == other.efixOverrideMask &&
                efixFlags == other.efixFlags &&
                AlmostEqual(baseCost,other.baseCost,2) &&
                resistAV == other.resistAV &&
                reserved == other.reserved);
        }
    bool operator !=(const OBMEEFIX &other) const
        {
        return !(*this == other);
        }
    };

struct OBMEEffect
    {
    ReqSubRecord<OBMEEFME> EFME;
    STRING EFII;
    OptSubRecord<OBMEEFIX> EFIX;
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        EFME.Debug("EFME", debugLevel, indentation);
        EFII.Debug("EFII", debugLevel, indentation);
        EFIX.Debug("EFIX", debugLevel, indentation);
        }
    #endif
    bool operator ==(const OBMEEffect& other) const
        {
        return (EFME == other.EFME &&
                EFII == other.EFII &&
                EFIX == other.EFIX);
        }
    bool operator !=(const OBMEEffect &other) const
        {
        return !(*this == other);
        }
    };

struct GENEffect
    {
    ReqSubRecord<GENEFID> EFID;
    ReqSubRecord<GENEFIT> EFIT;
    OptSubRecord<GENSCIT> SCIT;
    STRING FULL;
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
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        EFID.Debug("EFID", debugLevel, indentation);
        EFIT.Debug("EFIT", debugLevel, indentation);
        SCIT.Debug("SCIT", debugLevel, indentation);
        FULL.Debug("FULL", debugLevel, indentation);
        OBME.Debug("OBME", debugLevel, indentation);
        }
    #endif
    bool operator ==(const GENEffect& other) const
        {
        return (EFID == other.EFID &&
                EFIT == other.EFIT &&
                SCIT == other.SCIT &&
                FULL == other.FULL &&
                OBME == other.OBME);
        }
    bool operator !=(const GENEffect &other) const
        {
        return !(*this == other);
        }
    bool IsHostile()
        {
        if(!SCIT.IsLoaded()) return false;
        return (SCIT->flags & fIsHostile) != 0;
        }
    void IsHostile(bool value)
        {
        if(!SCIT.IsLoaded()) return;
        if(value)
            SCIT->flags |= fIsHostile;
        else
            SCIT->flags &= ~fIsHostile;
        }
    bool IsFlagMask(unsigned char Mask, bool Exact=false)
        {
        if(!SCIT.IsLoaded()) return false;
        if(Exact)
            return (SCIT->flags & Mask) == Mask;
        else
            return (SCIT->flags & Mask) != 0;
        }
    void SetFlagMask(unsigned char Mask)
        {
        if(!SCIT.IsLoaded()) return;
        SCIT->flags = Mask;
        }
    bool IsRangeSelf()
        {
        return (EFIT.value.recipient == eRangeSelf);
        }
    void IsRangeSelf(bool value)
        {
        if(value)
            EFIT.value.recipient = eRangeSelf;
        else
            EFIT.value.recipient = eRangeTouch;
        }
    bool IsRangeTouch()
        {
        return (EFIT.value.recipient == eRangeTouch);
        }
    void IsRangeTouch(bool value)
        {
        if(value)
            EFIT.value.recipient = eRangeTouch;
        else
            EFIT.value.recipient = eRangeSelf;
        }
    bool IsRangeTarget()
        {
        return (EFIT.value.recipient == eRangeTarget);
        }
    void IsRangeTarget(bool value)
        {
        if(value)
            EFIT.value.recipient = eRangeTarget;
        else
            EFIT.value.recipient = eRangeSelf;
        }
    bool IsRange(unsigned int Mask)
        {
        return (EFIT.value.recipient == Mask);
        }
    void SetRange(unsigned int Mask)
        {
        EFIT.value.recipient = Mask;
        }
    };

struct GENANAM
    {
    unsigned short enchantPoints;
    GENANAM():enchantPoints(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            if(debugLevel > 4)
                {
                indentation += 2;
                PrintIndent(indentation);
                printf("enchantPoints = %u\n", enchantPoints);
                indentation -= 2;
                }
        }
    #endif
    bool operator ==(const GENANAM &other) const
        {
        return (enchantPoints == other.enchantPoints);
        }
    bool operator !=(const GENANAM &other) const
        {
        return !(*this == other);
        }
    };

struct GENUFLAG
    {
    unsigned int flags;
    GENUFLAG():flags(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            if(debugLevel > 4)
                {
                indentation += 2;
                PrintIndent(indentation);
                printf("flags = %u\n", flags);
                indentation -= 2;
                }
        }
    #endif
    bool operator ==(const GENUFLAG &other) const
        {
        return (flags == other.flags);
        }
    bool operator !=(const GENUFLAG &other) const
        {
        return !(*this == other);
        }
    };

struct GENWEIGHT
    {
    float weight;
    GENWEIGHT():weight(0.0f) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("weight = %f\n", weight);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENWEIGHT &other) const
        {
        return AlmostEqual(weight,other.weight,2);
        }
    bool operator !=(const GENWEIGHT &other) const
        {
        return !(*this == other);
        }
    };

struct GENENIT
    {
    int value;
    unsigned char flags;
    unsigned char unused1[3];
    GENENIT():value(0), flags(0)
        {
        memset(&unused1, 0x00, 3);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("value = %i\n", value);
            if(debugLevel > 4)
                {
                PrintIndent(indentation);
                printf("flags = %u\n", flags);
                }
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused1 = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENENIT &other) const
        {
        return (value == other.value &&
                flags == other.flags);
        }
    bool operator !=(const GENENIT &other) const
        {
        return !(*this == other);
        }
    };

struct GENVALUEWEIGHT
    {
    unsigned int value;
    float weight;
    GENVALUEWEIGHT():value(0), weight(0.0f) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("value = %u\n", value);
            PrintIndent(indentation);
            printf("weight = %f\n", weight);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENVALUEWEIGHT &other) const
        {
        return (value == other.value &&
                AlmostEqual(weight,other.weight,2));
        }
    bool operator !=(const GENVALUEWEIGHT &other) const
        {
        return !(*this == other);
        }
    };

struct GENCNTO
    {
    unsigned int item;
    int count;
    GENCNTO():item(0), count(1) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("%s, %i\n", PrintFormID(item), count);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENCNTO &other) const
        {
        return (item == other.item &&
                count == other.count);
        }
    bool operator !=(const GENCNTO &other) const
        {
        return !(*this == other);
        }
    };

struct GENACBS
    {
    unsigned int flags;
    unsigned short baseSpell, fatigue, barterGold;
    short level;
    unsigned short calcMin, calcMax;
    GENACBS():flags(0), baseSpell(0), fatigue(0), barterGold(0),
        level(1), calcMin(0), calcMax(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            if(debugLevel > 4)
                {
                PrintIndent(indentation);
                printf("flags      = %u\n", flags);
                }
            PrintIndent(indentation);
            printf("baseSpell  = %u\n", baseSpell);
            PrintIndent(indentation);
            printf("fatigue    = %u\n", fatigue);
            PrintIndent(indentation);
            printf("barterGold = %u\n", barterGold);
            PrintIndent(indentation);
            printf("level      = %i\n", level);
            PrintIndent(indentation);
            printf("calcMin    = %u\n", calcMin);
            PrintIndent(indentation);
            printf("calcMax    = %u\n", calcMax);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENACBS &other) const
        {
        return (flags == other.flags &&
                baseSpell == other.baseSpell &&
                fatigue == other.fatigue &&
                barterGold == other.barterGold &&
                level == other.level &&
                calcMin == other.calcMin &&
                calcMax == other.calcMax);
        }
    bool operator !=(const GENACBS &other) const
        {
        return !(*this == other);
        }
    };

struct GENSNAM
    {
    unsigned int faction;
    unsigned char rank, unused1[3];
    GENSNAM():faction(0), rank(0)
        {
        memset(&unused1, 0x00, 3);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            if(debugLevel > 4)
                printf("%s - %i (%02X%02X%02X)\n", PrintFormID(faction), rank, unused1[0], unused1[1], unused1[2]);
            else if (debugLevel > 3)
                printf("%s - %i\n", PrintFormID(faction), rank);
            else
                printf("SNAM\n");
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENSNAM &other) const
        {
        return (faction == other.faction &&
                rank == other.rank);
        }
    bool operator !=(const GENSNAM &other) const
        {
        return !(*this == other);
        }
    };

struct GENAIDT
    {
    unsigned char aggression, confidence, energyLevel, responsibility;
    unsigned int flags;
    char trainSkill;
    unsigned char trainLevel, unused1[2];
    GENAIDT():aggression(5), confidence(50), energyLevel(50),
        responsibility(50), flags(0), trainSkill(0), trainLevel(0)
        {
        memset(&unused1, 0x00, 2);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("aggression     = %u\n", aggression);
            PrintIndent(indentation);
            printf("confidence     = %u\n", confidence);
            PrintIndent(indentation);
            printf("energyLevel    = %u\n", energyLevel);
            PrintIndent(indentation);
            printf("responsibility = %u\n", responsibility);
            if(debugLevel > 4)
                {
                PrintIndent(indentation);
                printf("flags          = %u\n", flags);
                }
            PrintIndent(indentation);
            printf("trainSkill     = %i\n", trainSkill);
            PrintIndent(indentation);
            printf("trainLevel     = %u\n", trainLevel);
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused1        = %02X%02X\n", unused1[0], unused1[1]);
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENAIDT &other) const
        {
        return (aggression == other.aggression &&
                confidence == other.confidence &&
                energyLevel == other.energyLevel &&
                responsibility == other.responsibility &&
                flags == other.flags &&
                trainSkill == other.trainSkill &&
                trainLevel == other.trainLevel);
        }
    bool operator !=(const GENAIDT &other) const
        {
        return !(*this == other);
        }
    };

struct GENCTDA
    {
    unsigned char operType, unused1[3];
    float compValue;
    unsigned int ifunc;
    unsigned int param1, param2;
    unsigned char unused2[4];
    GENCTDA():operType(0), compValue(0.0f), ifunc(0), param1(0), param2(0)
        {
        memset(&unused1, 0x00, 3);
        memset(&unused2, 0x00, 4);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            if(Comparison_Name.find(operType) != Comparison_Name.end())
                printf("operType  = %u, %s\n", operType, Comparison_Name.find(operType)->second);
            else
                printf("operType  = %u, Unknown Comparison!!!\n", operType);
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused1   = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                }
            PrintIndent(indentation);
            printf("compValue = %f\n", compValue);
            PrintIndent(indentation);
            if(Function_Name.find(ifunc) != Function_Name.end())
                printf("ifunc     = %u, %s\n", ifunc, Function_Name.find(ifunc)->second);
            else
                printf("ifunc     = %u, Unknown Function!!!\n", ifunc);
            if(Function_Arguments.find(ifunc) != Function_Arguments.end())
                {
                if(Function_Arguments.find(ifunc)->second.first == eFID)
                    {
                    PrintIndent(indentation);
                    printf("param1    = %s\n", PrintFormID(param1));
                    }
                else if(Function_Arguments.find(ifunc)->second.first == eInt)
                    {
                    PrintIndent(indentation);
                    printf("param1    = %u\n", param1);
                    }
                }
            else
                {
                PrintIndent(indentation);
                printf("param1    = %u\n", param1);
                }
            if(Function_Arguments.find(ifunc) != Function_Arguments.end())
                {
                if(Function_Arguments.find(ifunc)->second.second == eFID)
                    {
                    PrintIndent(indentation);
                    printf("param2    = %s\n", PrintFormID(param2));
                    }
                else if(Function_Arguments.find(ifunc)->second.second == eInt)
                    {
                    PrintIndent(indentation);
                    printf("param2    = %u\n", param2);
                    }
                }
            else
                {
                PrintIndent(indentation);
                printf("param2    = %u\n", param2);
                }
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused2   = %02X%02X%02X\n", unused2[0], unused2[1], unused2[2], unused2[3]);
                }
            indentation -= 2;
            }
        else
            printf("CTDA\n");
        }
    #endif
    bool operator ==(const GENCTDA &other) const
        {
        return (operType == other.operType &&
                AlmostEqual(compValue,other.compValue,2) &&
                ifunc == other.ifunc &&
                param1 == other.param1 &&
                param2 == other.param2);
        }
    bool operator !=(const GENCTDA &other) const
        {
        return !(*this == other);
        }
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
    bool IsEqual()
        {
        return ((operType & 0xF0) == eEqual);
        }
    void IsEqual(bool value)
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
    bool IsNotEqual()
        {
        return ((operType & 0xF0) == eNotEqual);
        }
    void IsNotEqual(bool value)
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
    bool IsGreater()
        {
        return ((operType & 0xF0) == eGreater);
        }
    void IsGreater(bool value)
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
    bool IsGreaterOrEqual()
        {
        return ((operType & 0xF0) == eGreaterOrEqual);
        }
    void IsGreaterOrEqual(bool value)
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
    bool IsLess()
        {
        return ((operType & 0xF0) == eLess);
        }
    void IsLess(bool value)
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
    bool IsLessOrEqual()
        {
        return ((operType & 0xF0) == eLessOrEqual);
        }
    void IsLessOrEqual(bool value)
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
    bool IsType(unsigned char Type)
        {
        return ((operType & 0xF0) == (Type & 0xF0));
        }
    void SetType(unsigned char Type)
        {
        Type &= 0xF0;
        operType &= 0x0F;
        operType |= Type;
        }
    bool IsNone()
        {
        return ((operType & 0x0F) == fIsNone);
        }
    void IsNone(bool value)
        {
        if(value)
            operType &= 0xF0;
        }
    bool IsOr()
        {
        return ((operType & 0x0F) & fIsOr) != 0;
        }
    void IsOr(bool value)
        {
        if(value)
            operType |= fIsOr;
        else
            operType &= ~fIsOr;
        }
    bool IsRunOnTarget()
        {
        return ((operType & 0x0F) & fIsRunOnTarget) != 0;
        }
    void IsRunOnTarget(bool value)
        {
        if(value)
            operType |= fIsRunOnTarget;
        else
            operType &= ~fIsRunOnTarget;
        }
    bool IsUseGlobal()
        {
        return ((operType & 0x0F) & fIsUseGlobal) != 0;
        }
    void IsUseGlobal(bool value)
        {
        if(value)
            operType |= fIsUseGlobal;
        else
            operType &= ~fIsUseGlobal;
        }
    bool IsFlagMask(unsigned char Mask, bool Exact=false)
        {
        if(Exact)
            return ((operType & 0x0F) & (Mask & 0x0F)) == Mask;
        else
            return ((operType & 0x0F) & (Mask & 0x0F)) != 0;
        }
    void SetFlagMask(unsigned char Mask)
        {
        Mask &= 0x0F;
        operType &= 0xF0;
        operType |= Mask;
        }
    };

struct GENCLR
    {
    unsigned char red, green, blue, unused1;
    GENCLR():red(0), green(0), blue(0), unused1(0) {}
    GENCLR(unsigned char rRed, unsigned char rGreen, unsigned char rBlue, unsigned char unused):red(rRed), green(rGreen), blue(rBlue), unused1(unused) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("red     = %u\n", red);
            PrintIndent(indentation);
            printf("green   = %u\n", green);
            PrintIndent(indentation);
            printf("blue    = %u\n", blue);
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused1 = %02X\n", unused1);
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENCLR &other) const
        {
        return (red == other.red &&
                green == other.green &&
                blue == other.blue);
        }
    bool operator !=(const GENCLR &other) const
        {
        return !(*this == other);
        }
    };

struct MODELMODB
    {
    float MODB;
    MODELMODB():MODB(0.0f) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        indentation += 2;
        if(debugLevel > 3)
            {
            PrintIndent(indentation);
            printf("MODB = %f\n", MODB);
            }
        indentation -= 2;
        }
    #endif
    bool operator ==(const MODELMODB &other) const
        {
        return AlmostEqual(MODB,other.MODB,2);
        }
    bool operator !=(const MODELMODB &other) const
        {
        return !(*this == other);
        }
    };

struct GENMODEL
    {
    ReqSubRecord<MODELMODB> MODB;
    STRING MODL;
    RAWBYTES MODT;
    #ifdef _DEBUG
    void Debug(char *name, int debugLevel, size_t &indentation)
        {
        if(name != NULL)
            {
            PrintIndent(indentation);
            printf("%s\n", name);
            }
        if(debugLevel > 3)
            {
            indentation += 2;
            MODL.Debug("MODL", debugLevel, indentation);
            MODB.Debug("MODB", debugLevel, indentation);
            MODT.Debug("MODT", debugLevel, indentation);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENMODEL &other) const
        {
        return (MODB == other.MODB &&
                MODL == other.MODL &&
                MODT == other.MODT);
        }
    bool operator !=(const GENMODEL &other) const
        {
        return !(*this == other);
        }
    };

struct GENRANK
    {
    int rank;
    GENRANK():rank(0) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        indentation += 2;
        if(debugLevel > 3)
            {
            PrintIndent(indentation);
            printf("rank = %i\n", rank);
            }
        indentation -= 2;
        }
    #endif
    bool operator ==(const GENRANK &other) const
        {
        return (rank == other.rank);
        }
    bool operator !=(const GENRANK &other) const
        {
        return !(*this == other);
        }
    };

struct GENXOWN
    {
    ReqSubRecord<GENFID> XOWN;
    SemiOptSubRecord<GENRANK> XRNK;
    OptSubRecord<GENFID> XGLB;
    #ifdef _DEBUG
    void Debug(char *name, int debugLevel, size_t &indentation)
        {
        if(name != NULL)
            {
            PrintIndent(indentation);
            printf("%s\n", name);
            }
        if(debugLevel > 3)
            {
            indentation += 2;
            XOWN.Debug("XOWN", debugLevel, indentation);
            XRNK.Debug("XRNK", debugLevel, indentation);
            XGLB.Debug("XGLB", debugLevel, indentation);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENXOWN &other) const
        {
        return (XOWN == other.XOWN &&
                XRNK == other.XRNK &&
                XGLB == other.XGLB);
        }
    bool operator !=(const GENXOWN &other) const
        {
        return !(*this == other);
        }
    };

struct GENXPCI
    {
    OptSubRecord<GENFID> XPCI;
    STRING FULL;
    #ifdef _DEBUG
    void Debug(char *name, int debugLevel, size_t &indentation)
        {
        if(name != NULL)
            {
            PrintIndent(indentation);
            printf("%s\n", name);
            }
        if(debugLevel > 3)
            {
            indentation += 2;
            XPCI.Debug("XPCI", debugLevel, indentation);
            FULL.Debug("FULL", debugLevel, indentation);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENXPCI &other) const
        {
        return (XPCI == other.XPCI &&
                FULL == other.FULL);
        }
    bool operator !=(const GENXPCI &other) const
        {
        return !(*this == other);
        }
    };

struct GENXLOD
    {
    float lod1, lod2, lod3;
    GENXLOD():lod1(0.0f), lod2(0.0f), lod3(0.0f) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("lod1 = %f\n", lod1);
            PrintIndent(indentation);
            printf("lod2 = %f\n", lod2);
            PrintIndent(indentation);
            printf("lod3 = %f\n", lod3);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENXLOD &other) const
        {
        return (AlmostEqual(lod1,other.lod1,2) &&
                AlmostEqual(lod2,other.lod2,2) &&
                AlmostEqual(lod3,other.lod3,2)
                );
        }
    bool operator !=(const GENXLOD &other) const
        {
        return !(*this == other);
        }
    };

struct GENXESP
    {
    unsigned int parent;
    unsigned char flags, unused1[3];
    GENXESP():parent(0), flags(0)
        {
        memset(&unused1, 0x00, 3);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("parent  = %s\n", PrintFormID(parent));
            if(debugLevel > 4)
                {
                PrintIndent(indentation);
                printf("flags   = %u\n", flags);
                }
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused1 = %c%c%c\n", unused1[0], unused1[1], unused1[2]);
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENXESP &other) const
        {
        return (parent == other.parent &&
                flags == other.flags);
        }
    bool operator !=(const GENXESP &other) const
        {
        return !(*this == other);
        }
    };

struct GENXSCL
    {
    float scale;
    GENXSCL():scale(1.0f) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        indentation += 2;
        if(debugLevel > 3)
            {
            PrintIndent(indentation);
            printf("scale = %f\n", scale);
            }
        indentation -= 2;
        }
    #endif
    bool operator ==(const GENXSCL &other) const
        {
        return (AlmostEqual(scale,other.scale,2));
        }
    bool operator !=(const GENXSCL &other) const
        {
        return !(*this == other);
        }
    };

struct GENPOSDATA
    {
    float posX, posY, posZ, rotX, rotY, rotZ;
    GENPOSDATA():posX(0.0f), posY(0.0f), posZ(0.0f), rotX(0.0f), rotY(0.0f), rotZ(0.0f) {}
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        indentation += 2;
        if(debugLevel > 3)
            {
            PrintIndent(indentation);
            printf("Position:\n");
            indentation += 2;
            PrintIndent(indentation);
            printf("posX = %f\n", posX);
            PrintIndent(indentation);
            printf("posY = %f\n", posY);
            PrintIndent(indentation);
            printf("posZ = %f\n", posZ);
            indentation -= 2;
            PrintIndent(indentation);
            printf("Rotation:\n");
            indentation += 2;
            PrintIndent(indentation);
            printf("rotX = %f\n", rotX);
            PrintIndent(indentation);
            printf("rotY = %f\n", rotY);
            PrintIndent(indentation);
            printf("rotZ = %f\n", rotZ);
            indentation -= 2;
            }
        indentation -= 2;
        }
    #endif
    bool operator ==(const GENPOSDATA &other) const
        {
        return (AlmostEqual(posX,other.posX,2) &&
                AlmostEqual(posY,other.posY,2) &&
                AlmostEqual(posZ,other.posZ,2) &&
                AlmostEqual(rotX,other.rotX,2) &&
                AlmostEqual(rotY,other.rotY,2) &&
                AlmostEqual(rotZ,other.rotZ,2)
                );
        }
    bool operator !=(const GENPOSDATA &other) const
        {
        return !(*this == other);
        }
    };

struct GENPGRP
    {
    float x, y, z;
    unsigned char connections;
    unsigned char unused1[3];
    GENPGRP():x(0.0f), y(0.0f), z(0.0f), connections(0)
        {
        memset(&unused1, 0x00, 3);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("x           = %f\n", x);
            PrintIndent(indentation);
            printf("y           = %f\n", y);
            PrintIndent(indentation);
            printf("z           = %f\n", z);
            if(debugLevel > 4)
                {
                PrintIndent(indentation);
                printf("connections = %u\n", connections);
                }
            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("unused1     = %c%c%c\n", unused1[0], unused1[1], unused1[2]);
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const GENPGRP &other) const
        {
        return (AlmostEqual(x,other.x,2) &&
                AlmostEqual(y,other.y,2) &&
                AlmostEqual(z,other.z,2) &&
                connections == other.connections);
        }
    bool operator !=(const GENPGRP &other) const
        {
        return !(*this == other);
        }
    };

struct MAGICOBME
    {
    unsigned char recordVersion, betaVersion, minorVersion, majorVersion;
    unsigned char reserved[0x1C];
    MAGICOBME():recordVersion(0), betaVersion(0), minorVersion(0), majorVersion(0)
        {
        memset(&reserved, 0x00, 0x1C);
        }
    #ifdef _DEBUG
    void Debug(int debugLevel, size_t &indentation)
        {
        if(debugLevel > 3)
            {
            indentation += 2;
            PrintIndent(indentation);
            printf("recordVersion = %i\n", recordVersion);
            printf("betaVersion = %i\n", betaVersion);
            printf("minorVersion = %i\n", minorVersion);
            printf("majorVersion = %i\n", majorVersion);

            if(debugLevel > 5)
                {
                PrintIndent(indentation);
                printf("reserved = ");
                for(unsigned int x = 0; x < 0x1C; x++)
                    printf("%c", reserved[x]);
                pritnf("\n");
                }
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const MAGICOBME &other) const
        {
        return (recordVersion == other.recordVersion &&
                betaVersion == other.betaVersion &&
                minorVersion == other.minorVersion &&
                majorVersion == other.majorVersion &&
                reserved == other.reserved);
        }
    bool operator !=(const MAGICOBME &other) const
        {
        return !(*this == other);
        }
    };

struct OBMEMAGIC
    {
    ReqSubRecord<MAGICOBME> OBME;
    RAWBYTES DATX;
    #ifdef _DEBUG
    void Debug(char *name, int debugLevel, size_t &indentation)
        {
        if(name != NULL)
            {
            PrintIndent(indentation);
            printf("%s\n", name);
            }
        if(debugLevel > 3)
            {
            indentation += 2;
            OBME.Debug("OBME", debugLevel, indentation);
            DATX.Debug("DATX", debugLevel, indentation);
            indentation -= 2;
            }
        }
    #endif
    bool operator ==(const OBMEMAGIC &other) const
        {
        return (OBME == other.OBME &&
                DATX == other.DATX);
        }
    bool operator !=(const OBMEMAGIC &other) const
        {
        return !(*this == other);
        }
    };

class FormIDOp
    {
    protected:
        unsigned int count;
    public:
        FormIDOp():count(0) {}
        virtual bool Accept(unsigned int &curFormID) abstract {};
        virtual bool AcceptMGEF(unsigned int &curMgefCode) {return true;};
        unsigned int GetCount() {return count;};
        void ResetCount() {count = 0;};
    };

class FormIDResolver : public FormIDOp
    {
    private:
        const unsigned char (&ResolveTable)[255];
    public:
        FormIDResolver(const unsigned char (&cResolveTable)[255]):FormIDOp(),ResolveTable(cResolveTable) {}
        bool Accept(unsigned int &curFormID)
            {
            if(curFormID)
                curFormID = (ResolveTable[curFormID >> 24] << 24 ) | (curFormID & 0x00FFFFFF);
            return true;
            }
        bool AcceptMGEF(unsigned int &curMgefCode)
            {
            if(curMgefCode)
                curMgefCode = (ResolveTable[curMgefCode & 0x000000FF]) | (curMgefCode & 0xFFFFFF00);
            return true;
            }
    };

class FormIDMasterUpdater : public FormIDOp
    {
    private:
        _FormIDHandler &FormIDHandler;
    public:
        FormIDMasterUpdater(_FormIDHandler &cFormIDHandler):FormIDOp(),FormIDHandler(cFormIDHandler) {}
        bool Accept(unsigned int &curFormID)
            {
            unsigned int modIndex = curFormID >> 24;
            //If formID is not set, or the formID belongs to the engine, or the formID belongs to the mod, or if the master is already present, do nothing
            if((curFormID == 0) || (curFormID < END_HARDCODED_IDS) || (modIndex == FormIDHandler.ExpandedIndex) || (FormIDHandler.CollapseTable[modIndex] != FormIDHandler.CollapsedIndex))
                return true;
            //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
            if(modIndex >= FormIDHandler.LoadOrder255.size())
                {
                #ifdef _DEBUG
                printf("Something's rotten in FormIDMasterUpdater. modIndex:%i, ModFiles.Size:%i\n", modIndex, LoadOrder255.size());
                #endif
                FormIDResolver collapser(FormIDHandler.CollapseTable);
                collapser.Accept(curFormID);
                FormIDResolver expander(FormIDHandler.ExpandTable);
                expander.Accept(curFormID);
                return true;
                }
            FormIDHandler.AddMaster(FormIDHandler.LoadOrder255[modIndex]);
            ++count;
            return true;
            }
        bool AcceptMGEF(unsigned int &curMgefCode)
            {
            unsigned int modIndex = curMgefCode << 24;
            //If formID is not set, or the formID belongs to the engine, or the formID belongs to the mod, or if the master is already present, do nothing
            if((curMgefCode == 0) || (curMgefCode < END_HARDCODED_IDS) || (modIndex == FormIDHandler.ExpandedIndex) || (FormIDHandler.CollapseTable[modIndex] != FormIDHandler.CollapsedIndex))
                return true;
            //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
            if(modIndex >= FormIDHandler.LoadOrder255.size())
                {
                #ifdef _DEBUG
                printf("Something's rotten in MGEF FormIDMasterUpdater. modIndex:%i, ModFiles.Size:%i\n", modIndex, LoadOrder255.size());
                #endif
                FormIDResolver collapser(FormIDHandler.CollapseTable);
                collapser.AcceptMGEF(curMgefCode);
                FormIDResolver expander(FormIDHandler.ExpandTable);
                expander.AcceptMGEF(curMgefCode);
                return true;
                }
            FormIDHandler.AddMaster(FormIDHandler.LoadOrder255[modIndex]);
            ++count;
            return true;
            }
    };

class FormIDMasterChecker : public FormIDOp
    {
    private:
        const unsigned char (&ExpandTable)[255];
        const unsigned char &MasterIndex;
    public:
        FormIDMasterChecker(const unsigned char (&cExpandTable)[255],const unsigned char &cMasterIndex):FormIDOp(),ExpandTable(cExpandTable),MasterIndex(cMasterIndex) {}
        bool Accept(unsigned int &curFormID)
            {
            if(curFormID < END_HARDCODED_IDS) //Any formID <= 0x800 is hardcoded in the engine and doesn't 'belong' to a mod.
                return false;
            if(ExpandTable[MasterIndex] == (curFormID >> 24))
                {
                ++count;
                return true;
                }
            return false;
            }
        bool AcceptMGEF(unsigned int &curMgefCode)
            {
            if(ExpandTable[MasterIndex] == (curMgefCode & 0x000000FF))
                {
                ++count;
                return true;
                }
            return false;
            }
    };

class FormIDMatchCounter : public FormIDOp
    {
    private:
        const unsigned int &FormIDToMatch;
    public:
        FormIDMatchCounter(const unsigned int &cFormID):FormIDOp(),FormIDToMatch(cFormID) {}
        bool Accept(unsigned int &curFormID)
            {
            if(curFormID == FormIDToMatch)
                ++count;
            return true;
            }
        bool AcceptMGEF(unsigned int &curMgefCode)
            {
            if(curMgefCode == FormIDToMatch)
                ++count;
            return true;
            }
    };

class FormIDSwapper : public FormIDOp
    {
    private:
        const unsigned int &FormIDToMatch;
        const unsigned int &FormIDToSwap;
        FormIDMasterUpdater checker;
    public:
        FormIDSwapper(const unsigned int &cMatch,const unsigned int &cSwap,_FormIDHandler &cFormIDHandler):FormIDOp(),FormIDToMatch(cMatch),FormIDToSwap(cSwap),checker(cFormIDHandler) {}
        bool Accept(unsigned int &curFormID)
            {
            if(curFormID == FormIDToMatch)
                {
                curFormID = FormIDToSwap;
                checker.Accept(curFormID);
                ++count;
                }
            return true;
            }
        bool AcceptMGEF(unsigned int &curMgefCode)
            {
            if(curMgefCode == FormIDToMatch)
                {
                curMgefCode = FormIDToSwap;
                checker.Accept(curMgefCode);
                ++count;
                }
            return true;
            }
    };

class Record
    {
    protected:
        enum ExtendedSize
            {
            eXXXX=0x58585858
            };
        enum headerFlags
            {
            fIsESM                  = 0x00000001,
            //fIsTaken              = 0x00000002, //From OBSE, unconfirmed, requires fIsDeleted also be set
            fIsDeleted              = 0x00000020,
            fIsBorderRegion         = 0x00000040,
            fTurnOffFire            = 0x00000080,
            fCastsShadows           = 0x00000200,
            fIsQuestOrPersistent    = 0x00000400,
            fIsInitiallyDisabled    = 0x00000800,
            fIsIgnored              = 0x00001000,
            //fIsTemporary            = 0x00004000, //From OBSE, unconfirmed
            fIsVisibleWhenDistant   = 0x00008000,
            fIsDangerousOrOffLimits = 0x00020000,
            fIsCompressed           = 0x00040000,
            fCantWait               = 0x00080000
            };
        enum unkHeaderFlags
            {
            _fIsLoaded              = 0x80000000 //Not an actual flag. Used only by CBash internally. Won't be written.
            };
    public:
        unsigned char *recData;
        unsigned int flags, formID, flagsUnk;

        Record(bool newRecord=false):flags(0), formID(0), flagsUnk(0), recData(NULL) {IsLoaded(newRecord);}

        virtual ~Record() {}
        #ifdef _DEBUG
        virtual void Debug(int debugLevel) abstract {};
        #endif

        virtual int GetOtherFieldType(const unsigned int Field) {return UNKNOWN_FIELD;}
        int GetFieldType(const unsigned int Field)
            {
            switch(Field)
                {
                case 0: //recType
                    return GetType();
                //case 1: //size
                //    return UINT_FIELD;
                case 2: //flags1
                    return UINT_FIELD;
                case 3: //fid
                    return FID_FIELD;
                case 4: //flags2
                    return UINT_FIELD;
                case 5: //eid
                    return STRING_FIELD;
                default:
                    return GetOtherFieldType(Field);
                }
            }
        virtual void * GetOtherField(const unsigned int Field) {return NULL;}
        void * GetField(const unsigned int Field)
            {
            switch(Field)
                {
                //case 0: //recType
                //    return &Header.Header.type;
                //case 1: //size
                //    return &Header.Header.size;
                case 2: //flags1
                    return &flags;
                case 3: //fid
                    return &formID;
                case 4: //flags2
                    return &flagsUnk;
                default:
                    return GetOtherField(Field);
                }
            }
        virtual void SetOtherField(const unsigned int Field, unsigned int FieldValue) {return;}
        void SetField(const unsigned int Field, unsigned int FieldValue)
            {
            switch(Field)
                {
                case 2: //flags1
                    SetHeaderFlagMask(FieldValue);
                    return;
                //case 3: //fid
                //    formID = FieldValue;
                //    return;
                case 4: //flags2
                    flagsUnk = FieldValue;
                    return;
                default:
                    SetOtherField(Field, FieldValue);
                    return;
                }
            }
        virtual void SetField(const unsigned int Field, char **FieldValue, unsigned int nSize) {return;}
        virtual void SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize) {return;}
        virtual void SetField(const unsigned int Field, float FieldValue) {return;}
        virtual void SetField(const unsigned int Field, int FieldValue) {return;}
        virtual void SetField(const unsigned int Field, char *FieldValue) {return;}
        virtual void SetField(const unsigned int Field, char FieldValue) {return;}
        virtual void SetField(const unsigned int Field, unsigned char FieldValue) {return;}
        virtual void SetField(const unsigned int Field, unsigned int FieldValue[], unsigned int nSize) {return;}
        virtual void SetField(const unsigned int Field, short FieldValue) {return;}
        virtual void SetField(const unsigned int Field, unsigned short FieldValue) {return;}

        virtual unsigned int GetFieldArraySize(const unsigned int Field) {return 0;}
        virtual unsigned int GetListSize(const unsigned int Field) {return 0;}
        virtual unsigned int GetListX2Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField) {return 0;}
        virtual unsigned int GetListX3Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned int listX2Index, const unsigned int listX2Field) {return 0;}

        virtual unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField) {return 0;}
        virtual unsigned int GetListX2ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field) {return 0;}
        virtual unsigned int GetListX3ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field) {return 0;}

        virtual int GetListFieldType(const unsigned int subField, const unsigned int listField) {return UNKNOWN_FIELD;}
        virtual int GetListX2FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field) {return UNKNOWN_FIELD;}
        virtual int GetListX3FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field, const unsigned int listX3Field) {return UNKNOWN_FIELD;}

        virtual void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField) {return NULL;}
        virtual void * GetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field) {return NULL;}
        virtual void * GetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field) {return NULL;}

        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char **FieldValue, unsigned int nSize) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char FieldValue) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned short FieldValue) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue[], unsigned int nSize) {return;}
        virtual void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue) {return;}

        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char **FieldValue, unsigned int nSize) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char FieldValue) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, char *FieldValue) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, short FieldValue) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned short FieldValue) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, int FieldValue) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue) {return;}
        virtual void SetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue) {return;}

        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char *FieldValue, unsigned int nSize) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char **FieldValue, unsigned int nSize) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char FieldValue) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned char FieldValue) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, char *FieldValue) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, short FieldValue) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned short FieldValue) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, int FieldValue) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, unsigned int FieldValue) {return;}
        virtual void SetListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, float FieldValue) {return;}

        virtual void GetFieldArray(const unsigned int Field, void **FieldValues)
            {*FieldValues = NULL;return;}
        virtual void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
            {*FieldValues = NULL;return;}
        virtual void GetListX2Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
            {*FieldValues = NULL;return;}
        virtual void GetListX3Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field, void **FieldValues)
            {*FieldValues = NULL;return;}

        virtual int CreateListElement(const unsigned int subField) {return -1;}
        virtual int CreateListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField) {return -1;}
        virtual int CreateListX3Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field) {return -1;}

        virtual int DeleteListElement(const unsigned int subField) {return -1;}
        virtual int DeleteListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField) {return -1;}
        virtual int DeleteListX3Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field) {return -1;}

        virtual int DeleteField(const unsigned int Field) {return -1;}
        virtual int DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField) {return -1;}
        virtual int DeleteListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field) {return -1;}
        virtual int DeleteListX3Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, const unsigned listX3Index, const unsigned int listX3Field) {return -1;}

        virtual void Unload() abstract {};
        virtual unsigned int GetSize(bool forceCalc=false) abstract {};
        virtual unsigned int GetType() {return eUnknown;}
        virtual char * GetStrType() abstract {}
        virtual void VisitFormIDs(FormIDOp &op) {};

        bool Read();

        virtual void CopyFrom(Record *temp) {return;}
        virtual int WriteRecord(_FileHandler &SaveHandler) abstract {};
        unsigned int Write(_FileHandler &SaveHandler, _FormIDHandler &FormIDHandler);
        virtual int ParseRecord(unsigned char *buffer, const unsigned int &recSize) abstract {};

        bool IsDeleted() const
            {
            return (flags & fIsDeleted) != 0;
            }
        void IsDeleted(bool value)
            {
            if(value)
                flags |= fIsDeleted;
            else
                flags &= ~fIsDeleted;
            }
        bool IsBorderRegion()
            {
            return (flags & fIsBorderRegion) != 0;
            }
        void IsBorderRegion(bool value)
            {
            if(value)
                flags |= fIsBorderRegion;
            else
                flags &= ~fIsBorderRegion;
            }
        bool IsTurnOffFire()
            {
            return (flags & fTurnOffFire) != 0;
            }
        void IsTurnOffFire(bool value)
            {
            if(value)
                flags |= fTurnOffFire;
            else
                flags &= ~fTurnOffFire;
            }
        bool IsCastsShadows()
            {
            return (flags & fCastsShadows) != 0;
            }
        void IsCastsShadows(bool value)
            {
            if(value)
                flags |= fCastsShadows;
            else
                flags &= ~fCastsShadows;
            }
        bool IsQuestOrPersistent()
            {
            return (flags & fIsQuestOrPersistent) != 0;
            }
        void IsQuestOrPersistent(bool value)
            {
            if(value)
                flags |= fIsQuestOrPersistent;
            else
                flags &= ~fIsQuestOrPersistent;
            }
        bool IsQuest()
            {
            return (flags & fIsQuestOrPersistent) != 0;
            }
        void IsQuest(bool value)
            {
            if(value)
                flags |= fIsQuestOrPersistent;
            else
                flags &= ~fIsQuestOrPersistent;
            }
        bool IsPersistent()
            {
            return (flags & fIsQuestOrPersistent) != 0;
            }
        void IsPersistent(bool value)
            {
            if(value)
                flags |= fIsQuestOrPersistent;
            else
                flags &= ~fIsQuestOrPersistent;
            }
        bool IsInitiallyDisabled()
            {
            return (flags & fIsInitiallyDisabled) != 0;
            }
        void IsInitiallyDisabled(bool value)
            {
            if(value)
                flags |= fIsInitiallyDisabled;
            else
                flags &= ~fIsInitiallyDisabled;
            }
        bool IsIgnored()
            {
            return (flags & fIsIgnored) != 0;
            }
        void IsIgnored(bool value)
            {
            if(value)
                flags |= fIsIgnored;
            else
                flags &= ~fIsIgnored;
            }
        bool IsVisibleWhenDistant()
            {
            return (flags & fIsVisibleWhenDistant) != 0;
            }
        void IsVisibleWhenDistant(bool value)
            {
            if(value)
                flags |= fIsVisibleWhenDistant;
            else
                flags &= ~fIsVisibleWhenDistant;
            }
        bool IsVWD()
            {
            return (flags & fIsVisibleWhenDistant) != 0;
            }
        void IsVWD(bool value)
            {
            if(value)
                flags |= fIsVisibleWhenDistant;
            else
                flags &= ~fIsVisibleWhenDistant;
            }
        bool IsTemporary()
            {
            return (flags & (fIsVisibleWhenDistant | fIsQuestOrPersistent)) != 0;
            }
        void IsTemporary(bool value)
            {
            if(value)
                {
                flags &= ~fIsVisibleWhenDistant;
                flags &= ~fIsQuestOrPersistent;
                }
            else
                flags |= fIsQuestOrPersistent;
            }
        bool IsDangerousOrOffLimits()
            {
            return (flags & fIsDangerousOrOffLimits) != 0;
            }
        void IsDangerousOrOffLimits(bool value)
            {
            if(value)
                flags |= fIsDangerousOrOffLimits;
            else
                flags &= ~fIsDangerousOrOffLimits;
            }
        bool IsDangerous()
            {
            return (flags & fIsDangerousOrOffLimits) != 0;
            }
        void IsDangerous(bool value)
            {
            if(value)
                flags |= fIsDangerousOrOffLimits;
            else
                flags &= ~fIsDangerousOrOffLimits;
            }
        bool IsOffLimits()
            {
            return (flags & fIsDangerousOrOffLimits) != 0;
            }
        void IsOffLimits(bool value)
            {
            if(value)
                flags |= fIsDangerousOrOffLimits;
            else
                flags &= ~fIsDangerousOrOffLimits;
            }
        bool IsCompressed()
            {
            return (flags & fIsCompressed) != 0;
            }
        void IsCompressed(bool value)
            {
            if(value)
                flags |= fIsCompressed;
            else
                flags &= ~fIsCompressed;
            }
        bool IsCantWait()
            {
            return (flags & fCantWait) != 0;
            }
        void IsCantWait(bool value)
            {
            if(value)
                flags |= fCantWait;
            else
                flags &= ~fCantWait;
            }
        bool IsHeaderFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (flags & Mask) == Mask;
            else
                return (flags & Mask) != 0;
            }
        void SetHeaderFlagMask(unsigned int Mask)
            {
            bool loaded = IsLoaded();
            flags = Mask;
            IsLoaded(loaded);
            }
        bool IsLoaded()
            {
            return (flags & _fIsLoaded) != 0;
            }
        void IsLoaded(bool value)
            {
            if(value)
                flags |= _fIsLoaded;
            else
                flags &= ~_fIsLoaded;
            }
    };

class RecordOp
    {
    protected:
        unsigned int count;
    public:
        RecordOp():count(0) {}
        virtual bool Accept(Record &curRecord) abstract {};
        unsigned int GetCount() {return count;};
        void ResetCount() {count = 0;};
    };

class RecordReader : public RecordOp
    {
    private:
        FormIDResolver expander;
    public:
        RecordReader(_FormIDHandler &FormIDHandler):RecordOp(),expander(FormIDHandler.ExpandTable) {}
        bool Accept(Record &curRecord)
            {
            if(curRecord.Read())
                {
                curRecord.VisitFormIDs(expander);
                ++count;
                }
            return true;
            }
    };

class RecordUnloader : public RecordOp
    {
    public:
        RecordUnloader():RecordOp() {}
        bool Accept(Record &curRecord)
            {
            if(curRecord.recData != NULL)
                {
                curRecord.Unload();
                ++count;
                }
            return true;
            }
    };

class RecordFormIDVisitor : public RecordOp
    {
    private:
        RecordReader reader;
        FormIDOp &op;
        const bool bOpChangesRecord;
    public:
        RecordFormIDVisitor(_FormIDHandler &FormIDHandler,FormIDOp &Op, bool OpChangesRecord=false):RecordOp(),reader(FormIDHandler),op(Op),bOpChangesRecord(OpChangesRecord) {}
        bool Accept(Record &curRecord)
            {
            bool loaded = reader.Accept(curRecord);
            op.ResetCount();
            curRecord.VisitFormIDs(op);
            unsigned int opCount = op.GetCount();
            if(opCount)
                {
                if(bOpChangesRecord)
                    curRecord.recData = NULL;
                count += opCount;
                }
            if(loaded && curRecord.recData != NULL)
                curRecord.Unload();
            return true;
            }
    };

class FormIDRecordRetriever : public RecordOp
    {
    private:
        unsigned int **RecordFIDs;
    public:
        FormIDRecordRetriever(unsigned int **cRecordFIDs):RecordOp(), RecordFIDs(cRecordFIDs) {}
        bool Accept(Record &curRecord)
            {
            RecordFIDs[count] = &curRecord.formID;
            ++count;
            return true;
            }
    };

class EditorIDRecordRetriever : public RecordOp
    {
    private:
        char **RecordEditorIDs;
    public:
        EditorIDRecordRetriever(char **cRecordEditorIDs):RecordOp(), RecordEditorIDs(cRecordEditorIDs) {}
        bool Accept(Record &curRecord)
            {
            char *editorID = (char *)curRecord.GetField(5);
            if(editorID != NULL)
                {
                RecordEditorIDs[count] = editorID;
                ++count;
                }
            return true;
            }
    };
