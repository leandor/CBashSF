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

class NPC_Record : public Record
    {
    private:
        enum NPC_SubRecords {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eACBS = 0x53424341,
            eSNAM = 0x4D414E53,
            eINAM = 0x4D414E49,
            eRNAM = 0x4D414E52,

            eSPLO = 0x4F4C5053,
            eSCRI = 0x49524353,
            eCNTO = 0x4F544E43,

            eAIDT = 0x54444941,
            ePKID = 0x44494B50,
            eKFFZ = 0x5A46464B,
            eCNAM = 0x4D414E43,
            eDATA = 0x41544144,

            eHNAM = 0x4D414E48,
            eLNAM = 0x4D414E4C,
            eENAM = 0x4D414E45,
            eHCLR = 0x524C4348,
            eZNAM = 0x4D414E5A,

            eFGGS = 0x53474746,
            eFGGA = 0x41474746,
            eFGTS = 0x53544746,
            eFNAM = 0x4D414E46
            };
        #pragma pack(push)
        #pragma pack(1)
        struct NPC_DATA
            {
            unsigned char armorer, athletics, blade, block, blunt,
                h2h, heavyArmor, alchemy, alteration,
                conjuration, destruction, illusion,
                mysticism, restoration, acrobatics,
                lightArmor, marksman, mercantile,
                security, sneak, speechcraft;
            unsigned short health;
            unsigned char unused1[2], strength, intelligence,
                willpower, agility, speed, endurance,
                personality, luck;
            NPC_DATA():armorer(0), athletics(0), blade(0),
                block(0), blunt(0), h2h(0), heavyArmor(0), alchemy(0),
                alteration(0), conjuration(0), destruction(0),
                illusion(0), mysticism(0), restoration(0),
                acrobatics(0), lightArmor(0), marksman(0),
                mercantile(0), security(0), sneak(0), speechcraft(0),
                health(0), strength(0), intelligence(0), willpower(0),
                agility(0), speed(0), endurance(0), personality(0),
                luck(0)
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
                    printf("armorer      = %u\n", armorer);
                    PrintIndent(indentation);
                    printf("athletics    = %u\n", athletics);
                    PrintIndent(indentation);
                    printf("blade        = %u\n", blade);
                    PrintIndent(indentation);
                    printf("block        = %u\n", block);
                    PrintIndent(indentation);
                    printf("blunt        = %u\n", blunt);
                    PrintIndent(indentation);
                    printf("h2h          = %u\n", h2h);
                    PrintIndent(indentation);
                    printf("heavyArmor   = %u\n", heavyArmor);
                    PrintIndent(indentation);
                    printf("alchemy      = %u\n", alchemy);
                    PrintIndent(indentation);
                    printf("alteration   = %u\n", alteration);
                    PrintIndent(indentation);
                    printf("conjuration  = %u\n", conjuration);
                    PrintIndent(indentation);
                    printf("destruction  = %u\n", destruction);
                    PrintIndent(indentation);
                    printf("illusion     = %u\n", illusion);
                    PrintIndent(indentation);
                    printf("mysticism    = %u\n", mysticism);
                    PrintIndent(indentation);
                    printf("restoration  = %u\n", restoration);
                    PrintIndent(indentation);
                    printf("acrobatics   = %u\n", acrobatics);
                    PrintIndent(indentation);
                    printf("lightArmor   = %u\n", lightArmor);
                    PrintIndent(indentation);
                    printf("marksman     = %u\n", marksman);
                    PrintIndent(indentation);
                    printf("mercantile   = %u\n", mercantile);
                    PrintIndent(indentation);
                    printf("security     = %u\n", security);
                    PrintIndent(indentation);
                    printf("sneak        = %u\n", sneak);
                    PrintIndent(indentation);
                    printf("speechcraft  = %u\n", speechcraft);
                    PrintIndent(indentation);
                    printf("health       = %u\n", health);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1      = %02X%02X\n", unused1[0], unused1[1]);
                        }
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
            bool operator ==(const NPC_DATA &other) const
                {
                return (armorer == other.armorer && 
                        athletics == other.athletics && 
                        blade == other.blade && 
                        block == other.block && 
                        blunt == other.blunt && 
                        h2h == other.h2h && 
                        heavyArmor == other.heavyArmor && 
                        alchemy == other.alchemy && 
                        alteration == other.alteration && 
                        conjuration == other.conjuration && 
                        destruction == other.destruction && 
                        illusion == other.illusion && 
                        mysticism == other.mysticism && 
                        restoration == other.restoration && 
                        acrobatics == other.acrobatics && 
                        lightArmor == other.lightArmor && 
                        marksman == other.marksman && 
                        mercantile == other.mercantile && 
                        security == other.security && 
                        sneak == other.sneak && 
                        speechcraft == other.speechcraft && 
                        health == other.health && 
                        strength == other.strength && 
                        intelligence == other.intelligence && 
                        willpower == other.willpower && 
                        agility == other.agility && 
                        speed == other.speed && 
                        endurance == other.endurance && 
                        personality == other.personality && 
                        luck == other.luck);
                }
            bool operator !=(const NPC_DATA &other) const
                {
                return !(*this == other);
                }
            };
        #pragma pack(pop)
        struct NPC_LNAM
            {
            float hairLength;
            NPC_LNAM():hairLength(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("hairLength = %f\n", hairLength);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const NPC_LNAM &other) const
                {
                return (AlmostEqual(hairLength,other.hairLength,2));
                }
            bool operator !=(const NPC_LNAM &other) const
                {
                return !(*this == other);
                }
            };
        struct NPC_FNAM
            {
            unsigned short fnam;
            NPC_FNAM():fnam(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("fnam = %u\n", fnam);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const NPC_FNAM &other) const
                {
                return (fnam == other.fnam);
                }
            bool operator !=(const NPC_FNAM &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsFlags
            {
            fIsFemale         = 0x00000001,
            fIsEssential      = 0x00000002,
            fIsRespawn        = 0x00000008,
            fIsAutoCalc       = 0x00000010,
            fIsPCLevelOffset  = 0x00000080,
            fIsNoLowLevel     = 0x00000200,
            fIsNoRumors       = 0x00002000,
            fIsSummonable     = 0x00004000,
            fIsNoPersuasion   = 0x00008000,
            fIsCanCorpseCheck = 0x00100000
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
        STRING EDID;
        STRING FULL;
        OptSubRecord<GENMODEL> MODL;
        ReqSubRecord<GENACBS> ACBS;
        std::vector<ReqSubRecord<GENSNAM> *> SNAM;
        OptSubRecord<GENFID> INAM;
        OptSubRecord<GENFID> RNAM;
        std::vector<unsigned int *> SPLO;
        OptSubRecord<GENFID> SCRI;
        std::vector<ReqSubRecord<GENCNTO> *> CNTO;
        ReqSubRecord<GENAIDT> AIDT;
        std::vector<unsigned int *> PKID;
        std::vector<STRING> KFFZ;
        ReqSubRecord<GENFID> CNAM;
        ReqSubRecord<NPC_DATA> DATA;
        OptSubRecord<GENFID> HNAM;
        SemiOptSubRecord<NPC_LNAM> LNAM;
        OptSubRecord<GENFID> ENAM;
        ReqSubRecord<GENCLR> HCLR;
        OptSubRecord<GENFID> ZNAM;
        RAWBYTES FGGS;
        RAWBYTES FGGA;
        RAWBYTES FGTS;
        ReqSubRecord<NPC_FNAM> FNAM;

        NPC_Record(bool newRecord=false):Record(newRecord) {IsCompressed(true);}
        NPC_Record(const unsigned int &newFormID):Record(newFormID) {IsCompressed(true);}
        NPC_Record(NPC_Record *srcRecord):Record(true)
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
            ACBS = srcRecord->ACBS;
            SNAM.clear();
            SNAM.resize(srcRecord->SNAM.size());
            for(unsigned int x = 0; x < srcRecord->SNAM.size(); x++)
                {
                SNAM[x] = new ReqSubRecord<GENSNAM>;
                *SNAM[x] = *srcRecord->SNAM[x];
                }
            INAM = srcRecord->INAM;
            RNAM = srcRecord->RNAM;
            SPLO.clear();
            SPLO.resize(srcRecord->SPLO.size());
            for(unsigned int x = 0; x < srcRecord->SPLO.size(); x++)
                SPLO[x] = new unsigned int(*srcRecord->SPLO[x]);
            SCRI = srcRecord->SCRI;
            CNTO.clear();
            CNTO.resize(srcRecord->CNTO.size());
            for(unsigned int x = 0; x < srcRecord->CNTO.size(); x++)
                {
                CNTO[x] = new ReqSubRecord<GENCNTO>;
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
            CNAM = srcRecord->CNAM;
            DATA = srcRecord->DATA;
            HNAM = srcRecord->HNAM;
            LNAM = srcRecord->LNAM;
            ENAM = srcRecord->ENAM;
            HCLR = srcRecord->HCLR;
            ZNAM = srcRecord->ZNAM;
            FGGS = srcRecord->FGGS;
            FGGA = srcRecord->FGGA;
            FGTS = srcRecord->FGTS;
            FNAM = srcRecord->FNAM;
            return;
            }
        ~NPC_Record()
            {
            for(unsigned int x = 0; x < SNAM.size(); x++)
                delete SNAM[x];
            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            for(unsigned int x = 0; x < CNTO.size(); x++)
                delete CNTO[x];
            for(unsigned int x = 0; x < PKID.size(); x++)
                delete PKID[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();
            ACBS.Unload();

            for(unsigned int x = 0; x < SNAM.size(); x++)
                delete SNAM[x];
            SNAM.clear();

            INAM.Unload();
            RNAM.Unload();

            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            SPLO.clear();

            SCRI.Unload();

            for(unsigned int x = 0; x < CNTO.size(); x++)
                delete CNTO[x];
            CNTO.clear();

            AIDT.Unload();

            for(unsigned int x = 0; x < PKID.size(); x++)
                delete PKID[x];
            PKID.clear();

            KFFZ.clear();

            CNAM.Unload();
            DATA.Unload();
            HNAM.Unload();
            LNAM.Unload();
            ENAM.Unload();
            HCLR.Unload();
            ZNAM.Unload();
            FGGS.Unload();
            FGGA.Unload();
            FGTS.Unload();
            FNAM.Unload();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            for(unsigned int x = 0; x < SNAM.size(); x++)
                FormIDs.push_back(&SNAM[x]->value.faction);
            if(INAM.IsLoaded())
                FormIDs.push_back(&INAM->fid);
            if(RNAM.IsLoaded())
                FormIDs.push_back(&RNAM->fid);
            for(unsigned int x = 0; x < SPLO.size(); x++)
                FormIDs.push_back(SPLO[x]);
            if(SCRI.IsLoaded())
                FormIDs.push_back(&SCRI->fid);
            for(unsigned int x = 0; x < CNTO.size(); x++)
                FormIDs.push_back(&CNTO[x]->value.item);
            for(unsigned int x = 0; x < PKID.size(); x++)
                FormIDs.push_back(PKID[x]);
            FormIDs.push_back(&CNAM.value.fid);
            if(HNAM.IsLoaded())
                FormIDs.push_back(&HNAM->fid);
            if(ENAM.IsLoaded())
                FormIDs.push_back(&ENAM->fid);
            if(ZNAM.IsLoaded())
                FormIDs.push_back(&ZNAM->fid);
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
        unsigned int GetType() {return eNPC_;}
        char * GetStrType() {return "NPC_";}
        int WriteRecord(_FileHandler &SaveHandler);

        bool IsFemale()
            {
            return (ACBS.value.flags & fIsFemale) != 0;
            }
        void IsFemale(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsFemale;
            else
                ACBS.value.flags &= ~fIsFemale;
            }
        bool IsMale()
            {
            return !IsFemale();
            }
        void IsMale(bool value)
            {
            IsFemale(!value);
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
        bool IsAutoCalc()
            {
            return (ACBS.value.flags & fIsAutoCalc) != 0;
            }
        void IsAutoCalc(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsAutoCalc;
            else
                ACBS.value.flags &= ~fIsAutoCalc;
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
        bool IsNoRumors()
            {
            return (ACBS.value.flags & fIsNoRumors) != 0;
            }
        void IsNoRumors(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoRumors;
            else
                ACBS.value.flags &= ~fIsNoRumors;
            }
        bool IsRumors()
            {
            return !IsNoRumors();
            }
        void IsRumors(bool value)
            {
            IsNoRumors(!value);
            }
        bool IsSummonable()
            {
            return (ACBS.value.flags & fIsSummonable) != 0;
            }
        void IsSummonable(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsSummonable;
            else
                ACBS.value.flags &= ~fIsSummonable;
            }
        bool IsNoPersuasion()
            {
            return (ACBS.value.flags & fIsNoPersuasion) != 0;
            }
        void IsNoPersuasion(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsNoPersuasion;
            else
                ACBS.value.flags &= ~fIsNoPersuasion;
            }
        bool IsPersuasion()
            {
            return !IsNoPersuasion();
            }
        void IsPersuasion(bool value)
            {
            IsNoPersuasion(!value);
            }
        bool IsCanCorpseCheck()
            {
            return (ACBS.value.flags & fIsCanCorpseCheck) != 0;
            }
        void IsCanCorpseCheck(bool value)
            {
            if(value)
                ACBS.value.flags |= fIsCanCorpseCheck;
            else
                ACBS.value.flags &= ~fIsCanCorpseCheck;
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
