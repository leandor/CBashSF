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
#include "..\Common.h"
#include "..\BaseRecord.h"
#include <vector>

class SPELRecord : public Record
    {
    private:
        enum SPELSubRecords {
            eEDID = 0x44494445,
            eOBME = 0x454D424F,
            eFULL = 0x4C4C5546,
            eSPIT = 0x54495053,

            eEFME = 0x454D4645,
            eEFID = 0x44494645,
            eEFIT = 0x54494645,
            eSCIT = 0x54494353,
            eEFII = 0x49494645,
            eEFIX = 0x58494645,

            eEFXX = 0x58584645,
            eDATX = 0x58544144,
            eBadScript = 0x0000C079
            };
        struct SPELSPIT
            {
            unsigned long spellType, cost, level;
            unsigned char flags, unused1[3];
            SPELSPIT():spellType(0), cost(0), level(0), flags(0)
                {
                memset(&unused1, 0x00, 3);
                }
            #ifdef _DEBUG
            void Debug(signed long debugLevel, unsigned long &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("spellType = %u\n", spellType);
                    PrintIndent(indentation);
                    printf("cost      = %u\n", cost);
                    PrintIndent(indentation);
                    printf("level     = %u\n", level);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags     = %u\n", flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1   = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const SPELSPIT &other) const
                {
                return (spellType == other.spellType &&
                        cost == other.cost &&
                        level == other.level &&
                        flags == other.flags);
                }
            bool operator !=(const SPELSPIT &other) const
                {
                return !(*this == other);
                }
            };

    public:
        enum flagsFlags
            {
            fIsManualCost            = 0x00000001,
            fIsStartSpell            = 0x00000004,
            fIsSilenceImmune         = 0x0000000A,
            fIsAreaEffectIgnoresLOS  = 0x00000010,
            fIsScriptAlwaysApplies   = 0x00000020,
            fIsDisallowAbsorbReflect = 0x00000040,
            fIsTouchExplodesWOTarget = 0x00000080
            };
        enum eSpellType
            {
            eSpell       = 0,
            eDisease     = 1,
            ePower       = 2,
            eLesserPower = 3,
            eAbility     = 4,
            ePoison      = 5
            };
        enum eSpellLevel
            {
            eNovice     = 0,
            eApprentice = 1,
            eJourneyman = 2,
            eExpert     = 3,
            eMaster     = 4
            };
        StringRecord EDID;
        StringRecord FULL;
        ReqSubRecord<SPELSPIT> SPIT;
        std::vector<GENEffect *> Effects;
        OptSubRecord<OBMEMAGIC> OBME;

        SPELRecord(bool newRecord=false):Record(newRecord) {}
        SPELRecord(SPELRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eSPEL)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            SPIT = srcRecord->SPIT;
            Effects.clear();
            Effects.resize(srcRecord->Effects.size());
            for(unsigned long x = 0; x < srcRecord->Effects.size(); x++)
                {
                Effects[x] = new GENEffect;
                Effects[x]->EFID = srcRecord->Effects[x]->EFID;
                Effects[x]->EFIT = srcRecord->Effects[x]->EFIT;
                Effects[x]->SCIT = srcRecord->Effects[x]->SCIT;
                Effects[x]->FULL = srcRecord->Effects[x]->FULL;
                if(srcRecord->Effects[x]->OBME.IsLoaded())
                    {
                    Effects[x]->OBME.Load();
                    Effects[x]->OBME->EFME = srcRecord->Effects[x]->OBME->EFME;
                    Effects[x]->OBME->EFII = srcRecord->Effects[x]->OBME->EFII;
                    Effects[x]->OBME->EFIX = srcRecord->Effects[x]->OBME->EFIX;
                    }
                }
            if(srcRecord->OBME.IsLoaded())
                {
                OBME.Load();
                OBME->OBME = srcRecord->OBME->OBME;
                OBME->DATX = srcRecord->OBME->DATX;
                }
            return;
            }
        ~SPELRecord()
            {
            for(unsigned long x = 0; x < Effects.size(); x++)
                delete Effects[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            SPIT.Unload();
            for(unsigned long x = 0; x < Effects.size(); x++)
                delete Effects[x];
            Effects.clear();
            OBME.Unload();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            for(unsigned long x = 0; x < Effects.size(); x++)
                {
                if(Effects[x]->OBME.IsLoaded())
                    {
                    if(Effects[x]->EFID.value.name >= 0x80000000)
                        op.AcceptMGEF(Effects[x]->EFID.value.name);
                    if(Effects[x]->EFIT.value.name >= 0x80000000)
                        op.AcceptMGEF(Effects[x]->EFIT.value.name);
                    switch(Effects[x]->OBME->EFME.value.efitParamInfo)
                        {
                        case 1: //It's a regular formID, so nothing fancy.
                            op.Accept(Effects[x]->EFIT.value.actorValue);
                            break;
                        case 2: //It's a mgefCode, and not a formID at all.
                            //Conditional resolution of mgefCode's based on JRoush's OBME mod
                            //It's resolved just like a formID, except it uses the lower byte instead of the upper
                            if(Effects[x]->EFIT.value.actorValue >= 0x80000000)
                                op.AcceptMGEF(Effects[x]->EFIT.value.actorValue);
                            break;
                        case 3: //It's an actor value, and not a formID at all.
                            //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                            //It's resolved just like a formID
                            if(Effects[x]->EFIT.value.actorValue >= 0x800)
                                op.Accept(Effects[x]->EFIT.value.actorValue);
                            break;
                        default: //It's not a formID, mgefCode, or fancied up actor value
                            //so do nothing
                            break;
                        }
                    if(Effects[x]->SCIT.IsLoaded())
                        {
                        if(Effects[x]->SCIT->visual >= 0x80000000)
                            op.AcceptMGEF(Effects[x]->SCIT->visual);
                        switch(Effects[x]->OBME->EFME.value.efixParamInfo)
                            {
                            case 1: //It's a regular formID, so nothing fancy.
                                op.Accept(Effects[x]->SCIT->script);
                                break;
                            case 2: //It's a mgefCode, and not a formID at all.
                                //Conditional resolution of mgefCode's based on JRoush's OBME mod
                                //It's resolved just like a formID, except it uses the lower byte instead of the upper
                                if(Effects[x]->SCIT->script >= 0x80000000)
                                    op.AcceptMGEF(Effects[x]->SCIT->script);
                                break;
                            case 3: //It's an actor value, and not a formID at all.
                                //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                                //It's resolved just like a formID
                                if(Effects[x]->SCIT->script >= 0x800)
                                    op.Accept(Effects[x]->SCIT->script);
                                break;
                            default: //It's not a formID, mgefCode, or fancied up actor value
                                //so do nothing
                                break;
                            }
                        }
                    if(Effects[x]->OBME->EFIX.IsLoaded())
                        if(Effects[x]->OBME->EFIX->resistAV >= 0x800)
                            op.Accept(Effects[x]->OBME->EFIX->resistAV);
                    }
                else
                    {
                    if(Effects[x]->SCIT.IsLoaded())
                        op.Accept(Effects[x]->SCIT->script);
                    }
                }

            return op.Stop();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long CreateListElement(const unsigned long subField);
        signed long DeleteListElement(const unsigned long subField);
        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        unsigned long GetFieldArraySize(const unsigned long Field);
        void GetFieldArray(const unsigned long Field, void **FieldValues);
        signed long GetListFieldType(const unsigned long subField, const unsigned long listField);
        unsigned long GetListSize(const unsigned long Field);
        unsigned long GetListArraySize(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void GetListArray(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues);
        void * GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetOtherField(const unsigned long Field, unsigned long FieldValue);
        void SetField(const unsigned long Field, unsigned char FieldValue);
        void SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, char *FieldValue);
        //OBME Fields
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, float FieldValue);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eSPEL;}
        char *GetStrType() {return "SPEL";}
        signed long WriteRecord(_FileHandler &SaveHandler);
        bool IsManualCost()
            {
            return (SPIT.value.flags & fIsManualCost) != 0;
            }
        void IsManualCost(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsManualCost;
            else
                SPIT.value.flags &= ~fIsManualCost;
            }
        bool IsStartSpell()
            {
            return (SPIT.value.flags & fIsStartSpell) != 0;
            }
        void IsStartSpell(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsStartSpell;
            else
                SPIT.value.flags &= ~fIsStartSpell;
            }
        bool IsSilenceImmune()
            {
            return (SPIT.value.flags & fIsSilenceImmune) != fIsSilenceImmune;
            }
        void IsSilenceImmune(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsSilenceImmune;
            else
                SPIT.value.flags &= ~fIsSilenceImmune;
            }
        bool IsAreaEffectIgnoresLOS()
            {
            return (SPIT.value.flags & fIsAreaEffectIgnoresLOS) != 0;
            }
        void IsAreaEffectIgnoresLOS(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsAreaEffectIgnoresLOS;
            else
                SPIT.value.flags &= ~fIsAreaEffectIgnoresLOS;
            }
        bool IsAEIgnoresLOS()
            {
            return (SPIT.value.flags & fIsAreaEffectIgnoresLOS) != 0;
            }
        void IsAEIgnoresLOS(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsAreaEffectIgnoresLOS;
            else
                SPIT.value.flags &= ~fIsAreaEffectIgnoresLOS;
            }
        bool IsScriptAlwaysApplies()
            {
            return (SPIT.value.flags & fIsScriptAlwaysApplies) != 0;
            }
        void IsScriptAlwaysApplies(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsScriptAlwaysApplies;
            else
                SPIT.value.flags &= ~fIsScriptAlwaysApplies;
            }
        bool IsDisallowAbsorbReflect()
            {
            return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
            }
        void IsDisallowAbsorbReflect(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsDisallowAbsorbReflect;
            else
                SPIT.value.flags &= ~fIsDisallowAbsorbReflect;
            }
        bool IsDisallowAbsorb()
            {
            return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
            }
        void IsDisallowAbsorb(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsDisallowAbsorbReflect;
            else
                SPIT.value.flags &= ~fIsDisallowAbsorbReflect;
            }
        bool IsDisallowReflect()
            {
            return (SPIT.value.flags & fIsDisallowAbsorbReflect) != 0;
            }
        void IsDisallowReflect(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsDisallowAbsorbReflect;
            else
                SPIT.value.flags &= ~fIsDisallowAbsorbReflect;
            }
        bool IsTouchExplodesWOTarget()
            {
            return (SPIT.value.flags & fIsTouchExplodesWOTarget) != 0;
            }
        void IsTouchExplodesWOTarget(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsTouchExplodesWOTarget;
            else
                SPIT.value.flags &= ~fIsTouchExplodesWOTarget;
            }
        bool IsTouchExplodes()
            {
            return (SPIT.value.flags & fIsTouchExplodesWOTarget) != 0;
            }
        void IsTouchExplodes(bool value)
            {
            if(value)
                SPIT.value.flags |= fIsTouchExplodesWOTarget;
            else
                SPIT.value.flags &= ~fIsTouchExplodesWOTarget;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (SPIT.value.flags & Mask) == Mask;
            else
                return (SPIT.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            SPIT.value.flags = Mask;
            }
        bool IsSpell()
            {
            return (SPIT.value.spellType == eSpell);
            }
        void IsSpell(bool value)
            {
            if(value)
                SPIT.value.spellType = eSpell;
            else if(IsSpell())
                SPIT.value.spellType = eDisease;
            }
        bool IsDisease()
            {
            return (SPIT.value.spellType == eDisease);
            }
        void IsDisease(bool value)
            {
            if(value)
                SPIT.value.spellType = eDisease;
            else if(IsDisease())
                SPIT.value.spellType = eSpell;
            }
        bool IsPower()
            {
            return (SPIT.value.spellType == ePower);
            }
        void IsPower(bool value)
            {
            if(value)
                SPIT.value.spellType = ePower;
            else if(IsPower())
                SPIT.value.spellType = eSpell;
            }
        bool IsLesserPower()
            {
            return (SPIT.value.spellType == eLesserPower);
            }
        void IsLesserPower(bool value)
            {
            if(value)
                SPIT.value.spellType = eLesserPower;
            else if(IsLesserPower())
                SPIT.value.spellType = eSpell;
            }
        bool IsAbility()
            {
            return (SPIT.value.spellType == eAbility);
            }
        void IsAbility(bool value)
            {
            if(value)
                SPIT.value.spellType = eAbility;
            else if(IsAbility())
                SPIT.value.spellType = eSpell;
            }
        bool IsPoison()
            {
            return (SPIT.value.spellType == ePoison);
            }
        void IsPoison(bool value)
            {
            if(value)
                SPIT.value.spellType = ePoison;
            else if(IsPoison())
                SPIT.value.spellType = eSpell;
            }
        bool IsType(unsigned long Type)
            {
            return (SPIT.value.spellType == Type);
            }
        void SetType(unsigned long Type)
            {
            SPIT.value.spellType = Type;
            }
        bool IsNovice()
            {
            return (SPIT.value.level == eNovice);
            }
        void IsNovice(bool value)
            {
            if(value)
                SPIT.value.level = eNovice;
            else if(IsNovice())
                SPIT.value.level = eApprentice;
            }
        bool IsApprentice()
            {
            return (SPIT.value.level == eApprentice);
            }
        void IsApprentice(bool value)
            {
            if(value)
                SPIT.value.level = eApprentice;
            else if(IsApprentice())
                SPIT.value.level = eNovice;
            }
        bool IsJourneyman()
            {
            return (SPIT.value.level == eJourneyman);
            }
        void IsJourneyman(bool value)
            {
            if(value)
                SPIT.value.level = eJourneyman;
            else if(IsJourneyman())
                SPIT.value.level = eNovice;
            }
        bool IsExpert()
            {
            return (SPIT.value.level == eExpert);
            }
        void IsExpert(bool value)
            {
            if(value)
                SPIT.value.level = eExpert;
            else if(IsExpert())
                SPIT.value.level = eNovice;
            }
        bool IsMaster()
            {
            return (SPIT.value.level == eMaster);
            }
        void IsMaster(bool value)
            {
            if(value)
                SPIT.value.level = eMaster;
            else if(IsMaster())
                SPIT.value.level = eNovice;
            }
        bool IsLevel(unsigned long Type)
            {
            return (SPIT.value.level == Type);
            }
        void SetLevel(unsigned long Type)
            {
            SPIT.value.level = Type;
            }
    };
