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

//Possibly extra crap exposed. Copied from NPC_ and hastily incorporated, may have missed stuff.
class CREARecord : public Record
    {
    private:
        enum CREARecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eSPLO = 0x4F4C5053,

            eNIFZ = 0x5A46494E,
            eNIFT = 0x5446494E,

            eACBS = 0x53424341,
            eSNAM = 0x4D414E53,
            eINAM = 0x4D414E49,

            eSCRI = 0x49524353,
            eCNTO = 0x4F544E43,

            eAIDT = 0x54444941,
            ePKID = 0x44494B50,
            eKFFZ = 0x5A46464B,
            eDATA = 0x41544144,

            eRNAM = 0x4D414E52,
            eZNAM = 0x4D414E5A,

            eTNAM = 0x4D414E54,
            eBNAM = 0x4D414E42,
            eWNAM = 0x4D414E57,

            eCSCR = 0x52435343,

            eNAM0 = 0x304D414E,
            eNAM1 = 0x314D414E,

            eCSDT = 0x54445343,
            eCSDI = 0x49445343,
            eCSDC = 0x43445343
            };
        struct CREADATA
            {
            unsigned char creatureType, combat, magic, stealth, soul, unused1;
            unsigned short health;
            unsigned char unused2[2];
            unsigned short attackDamage;
            unsigned char strength, intelligence, willpower,
                agility, speed, endurance, personality, luck;
            CREADATA():creatureType(0), combat(0), magic(0),
                stealth(0), soul(0), unused1(0x00), health(0),
                attackDamage(0), strength(0), intelligence(0),
                willpower(0), agility(0), speed(0),
                endurance(0), personality(0), luck(0)
                {
                memset(&unused2, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("creatureType = %u\n", creatureType);
                    PrintIndent(indentation);
                    printf("combat       = %u\n", combat);
                    PrintIndent(indentation);
                    printf("magic        = %u\n", magic);
                    PrintIndent(indentation);
                    printf("stealth      = %u\n", stealth);
                    PrintIndent(indentation);
                    printf("soul         = %u\n", soul);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1      = %02X\n", unused1);
                        }
                    PrintIndent(indentation);
                    printf("health       = %u\n", health);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused2      = %02X%02X\n", unused2[0], unused2[1]);
                        }
                    PrintIndent(indentation);
                    printf("attackDamage = %u\n", attackDamage);
                    PrintIndent(indentation);
                    printf("strength     = %u\n", strength);
                    PrintIndent(indentation);
                    printf("intelligence = %u\n", intelligence);
                    PrintIndent(indentation);
                    printf("willpower    = %u\n", willpower);
                    PrintIndent(indentation);
                    printf("agility      = %u\n", agility);
                    PrintIndent(indentation);
                    printf("speed        = %u\n", speed);
                    PrintIndent(indentation);
                    printf("endurance    = %u\n", endurance);
                    PrintIndent(indentation);
                    printf("personality  = %u\n", personality);
                    PrintIndent(indentation);
                    printf("luck         = %u\n", luck);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CREADATA &other) const
                {
                return (creatureType == other.creatureType && 
                        combat == other.combat && 
                        magic == other.magic && 
                        stealth == other.stealth && 
                        soul == other.soul && 
                        health == other.health && 
                        attackDamage == other.attackDamage && 
                        strength == other.strength && 
                        intelligence == other.intelligence && 
                        willpower == other.willpower && 
                        agility == other.agility && 
                        speed == other.speed && 
                        endurance == other.endurance && 
                        personality == other.personality && 
                        luck == other.luck);
                }
            bool operator !=(const CREADATA &other) const
                {
                return !(*this == other);
                }
            };
        struct CREARNAM
            {
            unsigned char attackReach;
            CREARNAM():attackReach(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("attackReach  = %u\n", attackReach);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CREARNAM &other) const
                {
                return (attackReach == other.attackReach);
                }
            bool operator !=(const CREARNAM &other) const
                {
                return !(*this == other);
                }
            };
        struct CREATNAM
            {
            float turningSpeed;
            CREATNAM():turningSpeed(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("turningSpeed  = %f\n", turningSpeed);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CREATNAM &other) const
                {
                return (AlmostEqual(turningSpeed,other.turningSpeed,2));
                }
            bool operator !=(const CREATNAM &other) const
                {
                return !(*this == other);
                }
            };
        struct CREABNAM
            {
            float baseScale;
            CREABNAM():baseScale(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("baseScale  = %f\n", baseScale);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CREABNAM &other) const
                {
                return (AlmostEqual(baseScale,other.baseScale,2));
                }
            bool operator !=(const CREABNAM &other) const
                {
                return !(*this == other);
                }
            };
        struct CREAWNAM
            {
            float footWeight;
            CREAWNAM():footWeight(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("footWeight  = %f\n", footWeight);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CREAWNAM &other) const
                {
                return (AlmostEqual(footWeight,other.footWeight,2));
                }
            bool operator !=(const CREAWNAM &other) const
                {
                return !(*this == other);
                }
            };
        struct CREACSDT
            {
            unsigned int type;
            CREACSDT():type(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("type = %u\n", type);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CREACSDT &other) const
                {
                return (type == other.type);
                }
            bool operator !=(const CREACSDT &other) const
                {
                return !(*this == other);
                }
            };
        struct CREACSDC
            {
            unsigned char chance;
            CREACSDC():chance(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("chance = %u\n", chance);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CREACSDC &other) const
                {
                return (chance == other.chance);
                }
            bool operator !=(const CREACSDC &other) const
                {
                return !(*this == other);
                }
            };
        struct CREASound
            {
            ReqRecordField<CREACSDT> CSDT;
            ReqRecordField<GENFID> CSDI;
            ReqRecordField<CREACSDC> CSDC;
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    CSDT.Debug("CSDT", debugLevel, indentation);
                    CSDI.Debug("CSDI", debugLevel, indentation);
                    CSDC.Debug("CSDC", debugLevel, indentation);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const CREASound &other) const
                {
                return (CSDT == other.CSDT && 
                        CSDI == other.CSDI && 
                        CSDC == other.CSDC);
                }
            bool operator !=(const CREASound &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsFlags
            {
            fIsBiped           = 0x00000001,
            fIsEssential       = 0x00000002,
            fIsWeaponAndShield = 0x00000004,
            fIsRespawn         = 0x00000008,
            fIsSwims           = 0x00000010,
            fIsFlies           = 0x00000020,
            fIsWalks           = 0x00000040,
            fIsPCLevelOffset   = 0x00000080,
            fIsNoLowLevel      = 0x00000200,
            fIsNoBloodSpray    = 0x00000800,
            fIsNoBloodDecal    = 0x00001000,
            fIsNoHead          = 0x00008000,
            fIsNoRightArm      = 0x00010000,
            fIsNoLeftArm       = 0x00020000,
            fIsNoCombatInWater = 0x00040000,
            fIsNoShadow        = 0x00080000,
            fIsNoCorpseCheck   = 0x00100000
            };
        enum servicesFlags
            {
            fWeapons     = 0x00000001,
            fArmor       = 0x00000002,
            fClothing    = 0x00000004,
            fBooks       = 0x00000008,
            fIngredients = 0x00000010,
            fLights      = 0x00000080,
            fApparatus   = 0x00000100,
            fMiscItems   = 0x00000400,
            fSpells      = 0x00000800,
            fMagicItems  = 0x00001000,
            fPotions     = 0x00002000,
            fTraining    = 0x00004000,
            fRecharge    = 0x00010000,
            fRepair      = 0x00020000
            };
        enum eCreatureType
            {
            eCreature = 0,
            eDaedra   = 1,
            eUndead   = 2,
            eHumanoid = 3,
            eHorse    = 4,
            eGiant    = 5
            };
        enum eSoulType
            {
            eNone    = 0,
            ePetty   = 1,
            eLesser  = 2,
            eCommon  = 3,
            eGreater = 4,
            eGrand   = 5
            };
        STRING EDID;
        STRING FULL;
        OptRecordField<GENMODEL> MODL;
        std::vector<unsigned int *> SPLO;
        std::vector<ISTRING> NIFZ;
        RAWBYTES NIFT;
        ReqRecordField<GENACBS> ACBS;
        std::vector<ReqRecordField<GENSNAM> *> SNAM;
        OptRecordField<GENFID> INAM;
        OptRecordField<GENFID> SCRI;
        std::vector<ReqRecordField<GENCNTO> *> CNTO;
        ReqRecordField<GENAIDT> AIDT;
        std::vector<unsigned int *> PKID;
        std::vector<STRING> KFFZ;
        ReqRecordField<CREADATA> DATA;
        ReqRecordField<CREARNAM> RNAM;
        OptRecordField<GENFID> ZNAM;
        ReqRecordField<CREATNAM> TNAM;
        ReqRecordField<CREABNAM> BNAM;
        ReqRecordField<CREAWNAM> WNAM;
        OptRecordField<GENFID> CSCR;
        ISTRING NAM0;
        ISTRING NAM1;
        std::vector<CREASound *> Sounds;

        CREARecord(bool newRecord=false):Record(newRecord) {}
        CREARecord(const unsigned int &newFormID):Record(newFormID) {}
        CREARecord(CREARecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            if(srcRecord->MODL.IsLoaded())
                {
                MODL.Load();
                MODL->MODB = srcRecord->MODL->MODB;
                MODL->MODL = srcRecord->MODL->MODL;
                MODL->MODT = srcRecord->MODL->MODT;
                }
            SPLO.clear();
            SPLO.resize(srcRecord->SPLO.size());
            for(unsigned int x = 0; x < srcRecord->SPLO.size(); x++)
                SPLO[x] = new unsigned int(*srcRecord->SPLO[x]);
            NIFZ.clear();
            NIFZ.resize(srcRecord->NIFZ.size());
            for(unsigned int x = 0; x < srcRecord->NIFZ.size(); x++)
                NIFZ[x].Copy(srcRecord->NIFZ[x]);
            NIFT = srcRecord->NIFT;
            ACBS = srcRecord->ACBS;
            SNAM.clear();
            SNAM.resize(srcRecord->SNAM.size());
            for(unsigned int x = 0; x < srcRecord->SNAM.size(); x++)
                {
                SNAM[x] = new ReqRecordField<GENSNAM>;
                *SNAM[x] = *srcRecord->SNAM[x];
                }
            INAM = srcRecord->INAM;
            SCRI = srcRecord->SCRI;
            CNTO.clear();
            CNTO.resize(srcRecord->CNTO.size());
            for(unsigned int x = 0; x < srcRecord->CNTO.size(); x++)
                {
                CNTO[x] = new ReqRecordField<GENCNTO>;
                *CNTO[x] = *srcRecord->CNTO[x];
                }
            AIDT = srcRecord->AIDT;
            PKID.clear();
            PKID.resize(srcRecord->PKID.size());
            for(unsigned int x = 0; x < srcRecord->PKID.size(); x++)
                PKID[x] = new unsigned int(*srcRecord->PKID[x]);
            KFFZ.clear();
            KFFZ.resize(srcRecord->KFFZ.size());
            for(unsigned int x = 0; x < srcRecord->KFFZ.size(); x++)
                KFFZ[x].Copy(srcRecord->KFFZ[x]);

            DATA = srcRecord->DATA;
            RNAM = srcRecord->RNAM;
            ZNAM = srcRecord->ZNAM;
            TNAM = srcRecord->TNAM;
            BNAM = srcRecord->BNAM;
            WNAM = srcRecord->WNAM;
            CSCR = srcRecord->CSCR;
            NAM0 = srcRecord->NAM0;
            NAM1 = srcRecord->NAM1;
            Sounds.clear();
            Sounds.resize(srcRecord->Sounds.size());
            for(unsigned int x = 0; x < srcRecord->Sounds.size(); x++)
                {
                Sounds[x] = new CREASound;
                Sounds[x]->CSDT = srcRecord->Sounds[x]->CSDT;
                Sounds[x]->CSDI = srcRecord->Sounds[x]->CSDI;
                Sounds[x]->CSDC = srcRecord->Sounds[x]->CSDC;
                }
            return;
            }
        ~CREARecord()
            {
            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            for(unsigned int x = 0; x < SNAM.size(); x++)
                delete SNAM[x];
            for(unsigned int x = 0; x < CNTO.size(); x++)
                delete CNTO[x];
            for(unsigned int x = 0; x < PKID.size(); x++)
                delete PKID[x];
            for(unsigned int x = 0; x < Sounds.size(); x++)
                delete Sounds[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();

            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            SPLO.clear();

            NIFZ.clear();

            NIFT.Unload();
            ACBS.Unload();

            for(unsigned int x = 0; x < SNAM.size(); x++)
                delete SNAM[x];
            SNAM.clear();

            INAM.Unload();
            SCRI.Unload();

            for(unsigned int x = 0; x < CNTO.size(); x++)
                delete CNTO[x];
            CNTO.clear();

            AIDT.Unload();

            for(unsigned int x = 0; x < PKID.size(); x++)
                delete PKID[x];
            PKID.clear();

            KFFZ.clear();

            DATA.Unload();
            RNAM.Unload();
            ZNAM.Unload();
            TNAM.Unload();
            BNAM.Unload();
            WNAM.Unload();
            CSCR.Unload();
            NAM0.Unload();
            NAM1.Unload();

            for(unsigned int x = 0; x < Sounds.size(); x++)
                delete Sounds[x];
            Sounds.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            for(unsigned int x = 0; x < SPLO.size(); x++)
                FormIDs.push_back(SPLO[x]);
            for(unsigned int x = 0; x < SNAM.size(); x++)
                FormIDs.push_back(&SNAM[x]->value.faction);
            if(INAM.IsLoaded())
                FormIDs.push_back(&INAM->fid);
            if(SCRI.IsLoaded())
                FormIDs.push_back(&SCRI->fid);
            for(unsigned int x = 0; x < CNTO.size(); x++)
                FormIDs.push_back(&CNTO[x]->value.item);
            for(unsigned int x = 0; x < PKID.size(); x++)
                FormIDs.push_back(PKID[x]);
            if(ZNAM.IsLoaded())
                FormIDs.push_back(&ZNAM->fid);
            if(CSCR.IsLoaded())
                FormIDs.push_back(&CSCR->fid);
            for(unsigned int x = 0; x < Sounds.size(); x++)
                FormIDs.push_back(&Sounds[x]->CSDI.value.fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, short FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char **FieldValue, unsigned int nSize);

        int DeleteField(const unsigned int Field);
        int DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eCREA;}
        char * GetStrType() {return "CREA";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsBiped()
            {
            return (ACBS.value.flags & fIsBiped) != 0;
            }
        void IsBiped(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsBiped;
            else
                ACBS.value.flags &= ~fIsBiped;
            }
        bool IsEssential()
            {
            return (ACBS.value.flags & fIsEssential) != 0;
            }
        void IsEssential(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsEssential;
            else
                ACBS.value.flags &= ~fIsEssential;
            }
        bool IsWeaponAndShield()
            {
            return (ACBS.value.flags & fIsWeaponAndShield) != 0;
            }
        void IsWeaponAndShield(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsWeaponAndShield;
            else
                ACBS.value.flags &= ~fIsWeaponAndShield;
            }
        bool IsRespawn()
            {
            return (ACBS.value.flags & fIsRespawn) != 0;
            }
        void IsRespawn(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsRespawn;
            else
                ACBS.value.flags &= ~fIsRespawn;
            }
        bool IsSwims()
            {
            return (ACBS.value.flags & fIsSwims) != 0;
            }
        void IsSwims(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsSwims;
            else
                ACBS.value.flags &= ~fIsSwims;
            }
        bool IsFlies()
            {
            return (ACBS.value.flags & fIsFlies) != 0;
            }
        void IsFlies(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsFlies;
            else
                ACBS.value.flags &= ~fIsFlies;
            }
        bool IsWalks()
            {
            return (ACBS.value.flags & fIsWalks) != 0;
            }
        void IsWalks(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsWalks;
            else
                ACBS.value.flags &= ~fIsWalks;
            }
        bool IsPCLevelOffset()
            {
            return (ACBS.value.flags & fIsPCLevelOffset) != 0;
            }
        void IsPCLevelOffset(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsPCLevelOffset;
            else
                ACBS.value.flags &= ~fIsPCLevelOffset;
            }
        bool IsNoLowLevel()
            {
            return (ACBS.value.flags & fIsNoLowLevel) != 0;
            }
        void IsNoLowLevel(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoLowLevel;
            else
                ACBS.value.flags &= ~fIsNoLowLevel;
            }
        bool IsLowLevel()
            {
            return !IsNoLowLevel();
            }
        void IsLowLevel(bool value)
            {
            IsNoLowLevel(!value);
            }
        bool IsNoBloodSpray()
            {
            return (ACBS.value.flags & fIsNoBloodSpray) != 0;
            }
        void IsNoBloodSpray(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoBloodSpray;
            else
                ACBS.value.flags &= ~fIsNoBloodSpray;
            }
        bool IsBloodSpray()
            {
            return !IsNoBloodSpray();
            }
        void IsBloodSpray(bool value)
            {
            IsNoBloodSpray(!value);
            }
        bool IsNoBloodDecal()
            {
            return (ACBS.value.flags & fIsNoBloodDecal) != 0;
            }
        void IsNoBloodDecal(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoBloodDecal;
            else
                ACBS.value.flags &= ~fIsNoBloodDecal;
            }
        bool IsBloodDecal()
            {
            return !IsNoBloodDecal();
            }
        void IsBloodDecal(bool value)
            {
            IsNoBloodDecal(!value);
            }
        bool IsNoHead()
            {
            return (ACBS.value.flags & fIsNoHead) != 0;
            }
        void IsNoHead(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoHead;
            else
                ACBS.value.flags &= ~fIsNoHead;
            }
        bool IsHead()
            {
            return !IsNoHead();
            }
        void IsHead(bool value)
            {
            IsNoHead(!value);
            }
        bool IsNoRightArm()
            {
            return (ACBS.value.flags & fIsNoRightArm) != 0;
            }
        void IsNoRightArm(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoRightArm;
            else
                ACBS.value.flags &= ~fIsNoRightArm;
            }
        bool IsRightArm()
            {
            return !IsNoRightArm();
            }
        void IsRightArm(bool value)
            {
            IsNoRightArm(!value);
            }
        bool IsNoLeftArm()
            {
            return (ACBS.value.flags & fIsNoLeftArm) != 0;
            }
        void IsNoLeftArm(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoLeftArm;
            else
                ACBS.value.flags &= ~fIsNoLeftArm;
            }
        bool IsLeftArm()
            {
            return !IsNoLeftArm();
            }
        void IsLeftArm(bool value)
            {
            IsNoLeftArm(!value);
            }
        bool IsNoCombatInWater()
            {
            return (ACBS.value.flags & fIsNoCombatInWater) != 0;
            }
        void IsNoCombatInWater(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoCombatInWater;
            else
                ACBS.value.flags &= ~fIsNoCombatInWater;
            }
        bool IsCombatInWater()
            {
            return !IsNoCombatInWater();
            }
        void IsCombatInWater(bool value)
            {
            IsNoCombatInWater(!value);
            }
        bool IsNoShadow()
            {
            return (ACBS.value.flags & fIsNoShadow) != 0;
            }
        void IsNoShadow(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoShadow;
            else
                ACBS.value.flags &= ~fIsNoShadow;
            }
        bool IsShadow()
            {
            return !IsNoShadow();
            }
        void IsShadow(bool value)
            {
            IsNoShadow(!value);
            }
        bool IsNoCorpseCheck()
            {
            return (ACBS.value.flags & fIsNoCorpseCheck) != 0;
            }
        void IsNoCorpseCheck(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoCorpseCheck;
            else
                ACBS.value.flags &= ~fIsNoCorpseCheck;
            }
        bool IsCorpseCheck()
            {
            return !IsNoCorpseCheck();
            }
        void IsCorpseCheck(bool value)
            {
            IsNoCorpseCheck(!value);
            }
        bool IsFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (ACBS.value.flags & Mask) == Mask;
            else
                return (ACBS.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned int Mask)
            {
            ACBS.value.flags = Mask;
            }
        bool IsCreature()
            {
            return (DATA.value.creatureType == eCreature);
            }
        void IsCreature(bool value)
            {
            if(value)
                DATA.value.creatureType = eCreature;
            else if(IsCreature())
                DATA.value.creatureType = eDaedra;
            }
        bool IsDaedra()
            {
            return (DATA.value.creatureType == eDaedra);
            }
        void IsDaedra(bool value)
            {
            if(value)
                DATA.value.creatureType = eDaedra;
            else if(IsDaedra())
                DATA.value.creatureType = eCreature;
            }
        bool IsUndead()
            {
            return (DATA.value.creatureType == eUndead);
            }
        void IsUndead(bool value)
            {
            if(value)
                DATA.value.creatureType = eUndead;
            else if(IsUndead())
                DATA.value.creatureType = eCreature;
            }
        bool IsHumanoid()
            {
            return (DATA.value.creatureType == eHumanoid);
            }
        void IsHumanoid(bool value)
            {
            if(value)
                DATA.value.creatureType = eHumanoid;
            else if(IsHumanoid())
                DATA.value.creatureType = eCreature;
            }
        bool IsHorse()
            {
            return (DATA.value.creatureType == eHorse);
            }
        void IsHorse(bool value)
            {
            if(value)
                DATA.value.creatureType = eHorse;
            else if(IsHorse())
                DATA.value.creatureType = eCreature;
            }
        bool IsGiant()
            {
            return (DATA.value.creatureType == eGiant);
            }
        void IsGiant(bool value)
            {
            if(value)
                DATA.value.creatureType = eGiant;
            else if(IsGiant())
                DATA.value.creatureType = eCreature;
            }
        bool IsType(unsigned char Type)
            {
            return (DATA.value.creatureType == Type);
            }
        void SetType(unsigned char Type)
            {
            DATA.value.creatureType = Type;
            }
        bool IsNoSoul()
            {
            return (DATA.value.soul == eNone);
            }
        void IsNoSoul(bool value)
            {
            if(value)
                DATA.value.soul = eNone;
            else if(IsNoSoul())
                DATA.value.soul = ePetty;
            }
        bool IsPettySoul()
            {
            return (DATA.value.soul == ePetty);
            }
        void IsPettySoul(bool value)
            {
            if(value)
                DATA.value.soul = ePetty;
            else if(IsPettySoul())
                DATA.value.soul = eNone;
            }
        bool IsLesserSoul()
            {
            return (DATA.value.soul == eLesser);
            }
        void IsLesserSoul(bool value)
            {
            if(value)
                DATA.value.soul = eLesser;
            else if(IsLesserSoul())
                DATA.value.soul = eNone;
            }
        bool IsCommonSoul()
            {
            return (DATA.value.soul == eCommon);
            }
        void IsCommonSoul(bool value)
            {
            if(value)
                DATA.value.soul = eCommon;
            else if(IsCommonSoul())
                DATA.value.soul = eNone;
            }
        bool IsGreaterSoul()
            {
            return (DATA.value.soul == eGreater);
            }
        void IsGreaterSoul(bool value)
            {
            if(value)
                DATA.value.soul = eGreater;
            else if(IsGreaterSoul())
                DATA.value.soul = eNone;
            }
        bool IsGrandSoul()
            {
            return (DATA.value.soul == eGrand);
            }
        void IsGrandSoul(bool value)
            {
            if(value)
                DATA.value.soul = eGrand;
            else if(IsGrandSoul())
                DATA.value.soul = eNone;
            }
        bool IsSoul(unsigned char Type)
            {
            return (DATA.value.soul == Type);
            }
        void SetSoul(unsigned char Type)
            {
            DATA.value.soul = Type;
            }
        bool IsServicesWeapons()
            {
            return (AIDT.value.flags & fWeapons) != 0;
            }
        void IsServicesWeapons(bool value)
            {
            if(value)
                AIDT.value.flags |= fWeapons;
            else
                AIDT.value.flags &= ~fWeapons;
            }
        bool IsServicesArmor()
            {
            return (AIDT.value.flags & fArmor) != 0;
            }
        void IsServicesArmor(bool value)
            {
            if(value)
                AIDT.value.flags |= fArmor;
            else
                AIDT.value.flags &= ~fArmor;
            }
        bool IsServicesClothing()
            {
            return (AIDT.value.flags & fClothing) != 0;
            }
        void IsServicesClothing(bool value)
            {
            if(value)
                AIDT.value.flags |= fClothing;
            else
                AIDT.value.flags &= ~fClothing;
            }
        bool IsServicesBooks()
            {
            return (AIDT.value.flags & fBooks) != 0;
            }
        void IsServicesBooks(bool value)
            {
            if(value)
                AIDT.value.flags |= fBooks;
            else
                AIDT.value.flags &= ~fBooks;
            }
        bool IsServicesIngredients()
            {
            return (AIDT.value.flags & fIngredients) != 0;
            }
        void IsServicesIngredients(bool value)
            {
            if(value)
                AIDT.value.flags |= fIngredients;
            else
                AIDT.value.flags &= ~fIngredients;
            }
        bool IsServicesLights()
            {
            return (AIDT.value.flags & fLights) != 0;
            }
        void IsServicesLights(bool value)
            {
            if(value)
                AIDT.value.flags |= fLights;
            else
                AIDT.value.flags &= ~fLights;
            }
        bool IsServicesApparatus()
            {
            return (AIDT.value.flags & fApparatus) != 0;
            }
        void IsServicesApparatus(bool value)
            {
            if(value)
                AIDT.value.flags |= fApparatus;
            else
                AIDT.value.flags &= ~fApparatus;
            }
        bool IsServicesMiscItems()
            {
            return (AIDT.value.flags & fMiscItems) != 0;
            }
        void IsServicesMiscItems(bool value)
            {
            if(value)
                AIDT.value.flags |= fMiscItems;
            else
                AIDT.value.flags &= ~fMiscItems;
            }
        bool IsServicesSpells()
            {
            return (AIDT.value.flags & fSpells) != 0;
            }
        void IsServicesSpells(bool value)
            {
            if(value)
                AIDT.value.flags |= fSpells;
            else
                AIDT.value.flags &= ~fSpells;
            }
        bool IsServicesMagicItems()
            {
            return (AIDT.value.flags & fMagicItems) != 0;
            }
        void IsServicesMagicItems(bool value)
            {
            if(value)
                AIDT.value.flags |= fMagicItems;
            else
                AIDT.value.flags &= ~fMagicItems;
            }
        bool IsServicesPotions()
            {
            return (AIDT.value.flags & fPotions) != 0;
            }
        void IsServicesPotions(bool value)
            {
            if(value)
                AIDT.value.flags |= fPotions;
            else
                AIDT.value.flags &= ~fPotions;
            }
        bool IsServicesTraining()
            {
            return (AIDT.value.flags & fTraining) != 0;
            }
        void IsServicesTraining(bool value)
            {
            if(value)
                AIDT.value.flags |= fTraining;
            else
                AIDT.value.flags &= ~fTraining;
            }
        bool IsServicesRecharge()
            {
            return (AIDT.value.flags & fRecharge) != 0;
            }
        void IsServicesRecharge(bool value)
            {
            if(value)
                AIDT.value.flags |= fRecharge;
            else
                AIDT.value.flags &= ~fRecharge;
            }
        bool IsServicesRepair()
            {
            return (AIDT.value.flags & fRepair) != 0;
            }
        void IsServicesRepair(bool value)
            {
            if(value)
                AIDT.value.flags |= fRepair;
            else
                AIDT.value.flags &= ~fRepair;
            }
        bool IsServicesFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (AIDT.value.flags & Mask) == Mask;
            else
                return (AIDT.value.flags & Mask) != 0;
            }
        void SetServicesFlagMask(unsigned int Mask)
            {
            AIDT.value.flags = Mask;
            }
    };
