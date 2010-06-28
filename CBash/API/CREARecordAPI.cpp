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
#include "..\Common.h"
#include "..\Records\CREARecord.h"

int CREARecord::CreateListElement(const unsigned int subField)
    {
    ReqSubRecord<GENSNAM> *curSNAM = NULL;
    ReqSubRecord<GENCNTO> *curCNTO = NULL;
    CREASound *curSound = NULL;
    switch(subField)
        {
        case 20: //factions
            curSNAM = new ReqSubRecord<GENSNAM>;
            SNAM.push_back(curSNAM);
            return (int)SNAM.size() - 1;
        case 23: //items
            curCNTO = new ReqSubRecord<GENCNTO>;
            CNTO.push_back(curCNTO);
            return (int)CNTO.size() - 1;
        case 59: //sounds
            curSound = new CREASound;
            Sounds.push_back(curSound);
            return (int)Sounds.size() - 1;
        default:
            return -1;
        }
    }

int CREARecord::DeleteListElement(const unsigned int subField)
    {
    ReqSubRecord<GENSNAM> *curSNAM = NULL;
    ReqSubRecord<GENCNTO> *curCNTO = NULL;
    CREASound *curSound = NULL;
    switch(subField)
        {
        case 20: //factions
            curSNAM = SNAM.back();
            delete curSNAM;
            SNAM.pop_back();
            return (int)SNAM.size() - 1;
        case 23: //items
            curCNTO = CNTO.back();
            delete curCNTO;
            CNTO.pop_back();
            return (int)CNTO.size() - 1;
        case 59: //sounds
            curSound = Sounds.back();
            delete curSound;
            Sounds.pop_back();
            return (int)Sounds.size() - 1;
        default:
            return -1;
        }
    }

int CREARecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //modPath
            return STRING_FIELD;
        case 8: //modb
            return FLOAT_FIELD;
        case 9: //modt_p
            return BYTES_FIELD;
        case 10: //spells
            return FIDARRAY_FIELD;
        case 11: //bodyParts
            return STRINGARRAY_FIELD;
        case 12: //nift_p
            return BYTES_FIELD;
        case 13: //flags
            return UINT_FIELD;
        case 14: //baseSpell
            return USHORT_FIELD;
        case 15: //fatigue
            return USHORT_FIELD;
        case 16: //barterGold
            return USHORT_FIELD;
        case 17: //level
            return SHORT_FIELD;
        case 18: //calcMin
            return USHORT_FIELD;
        case 19: //calcMax
            return USHORT_FIELD;
        case 20: //factions
            return LIST_FIELD;
        case 21: //deathItem
            return FID_FIELD;
        case 22: //script
            return FID_FIELD;
        case 23: //items
            return LIST_FIELD;
        case 24: //aggression
            return UBYTE_FIELD;
        case 25: //confidence
            return UBYTE_FIELD;
        case 26: //energyLevel
            return UBYTE_FIELD;
        case 27: //responsibility
            return UBYTE_FIELD;
        case 28: //services
            return UINT_FIELD;
        case 29: //trainSkill
            return BYTE_FIELD;
        case 30: //trainLevel
            return UBYTE_FIELD;
        case 31: //unused1
            return BYTES_FIELD;
        case 32: //aiPackages
            return FIDARRAY_FIELD;
        case 33: //animations
            return STRINGARRAY_FIELD;
        case 34: //creatureType
            return UBYTE_FIELD;
        case 35: //combat
            return UBYTE_FIELD;
        case 36: //magic
            return UBYTE_FIELD;
        case 37: //stealth
            return UBYTE_FIELD;
        case 38: //soul
            return UBYTE_FIELD;
        case 39: //unused2
            return BYTES_FIELD;
        case 40: //health
            return USHORT_FIELD;
        case 41: //unused3
            return BYTES_FIELD;
        case 42: //attackDamage
            return USHORT_FIELD;
        case 43: //strength
            return UBYTE_FIELD;
        case 44: //intelligence
            return UBYTE_FIELD;
        case 45: //willpower
            return UBYTE_FIELD;
        case 46: //agility
            return UBYTE_FIELD;
        case 47: //speed
            return UBYTE_FIELD;
        case 48: //endurance
            return UBYTE_FIELD;
        case 49: //personality
            return UBYTE_FIELD;
        case 50: //luck
            return UBYTE_FIELD;
        case 51: //attackReach
            return UBYTE_FIELD;
        case 52: //combatStyle
            return FID_FIELD;
        case 53: //turningSpeed
            return FLOAT_FIELD;
        case 54: //baseScale
            return FLOAT_FIELD;
        case 55: //footWeight
            return FLOAT_FIELD;
        case 56: //inheritsSoundsFrom
            return FID_FIELD;
        case 57: //bloodSprayPath
            return STRING_FIELD;
        case 58: //bloodDecalPath
            return STRING_FIELD;
        case 59: //sounds
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CREARecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //modPath
            if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
                return MODL->MODL.value;
            return NULL;
        case 8: //modb
            if(MODL.IsLoaded() && MODL->MODB.IsLoaded())
                return &MODL->MODB.value.MODB;
            return NULL;
        case 13: //flags
            return &ACBS.value.flags;
        case 14: //baseSpell
            return &ACBS.value.baseSpell;
        case 15: //fatigue
            return &ACBS.value.fatigue;
        case 16: //barterGold
            return &ACBS.value.barterGold;
        case 17: //level
            return &ACBS.value.level;
        case 18: //calcMin
            return &ACBS.value.calcMin;
        case 19: //calcMax
            return &ACBS.value.calcMax;
        case 21: //deathItem
            if(INAM.IsLoaded())
                return &INAM->fid;
            return NULL;
        case 22: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 24: //aggression
            return &AIDT.value.aggression;
        case 25: //confidence
            return &AIDT.value.confidence;
        case 26: //energyLevel
            return &AIDT.value.energyLevel;
        case 27: //responsibility
            return &AIDT.value.responsibility;
        case 28: //services
            return &AIDT.value.flags;
        case 29: //trainSkill
            return &AIDT.value.trainSkill;
        case 30: //trainLevel
            return &AIDT.value.trainLevel;
        case 34: //creatureType
            return &DATA.value.creatureType;
        case 35: //combat
            return &DATA.value.combat;
        case 36: //magic
            return &DATA.value.magic;
        case 37: //stealth
            return &DATA.value.stealth;
        case 38: //soul
            return &DATA.value.soul;
        case 40: //health
            return &DATA.value.health;
        case 42: //attackDamage
            return &DATA.value.attackDamage;
        case 43: //strength
            return &DATA.value.strength;
        case 44: //intelligence
            return &DATA.value.intelligence;
        case 45: //willpower
            return &DATA.value.willpower;
        case 46: //agility
            return &DATA.value.agility;
        case 47: //speed
            return &DATA.value.speed;
        case 48: //endurance
            return &DATA.value.endurance;
        case 49: //personality
            return &DATA.value.personality;
        case 50: //luck
            return &DATA.value.luck;
        case 51: //attackReach
            return &RNAM.value.attackReach;
        case 52: //combatStyle
            if(ZNAM.IsLoaded())
                return &ZNAM->fid;
            return NULL;
        case 53: //turningSpeed
            return &TNAM.value.turningSpeed;
        case 54: //baseScale
            return &BNAM.value.baseScale;
        case 55: //footWeight
            return &WNAM.value.footWeight;
        case 56: //inheritsSoundsFrom
            if(CSCR.IsLoaded())
                return &CSCR->fid;
            return NULL;
        case 57: //bloodSprayPath
            return NAM0.value;
        case 58: //bloodDecalPath
            return NAM1.value;
        default:
            return NULL;
        }
    }

unsigned int CREARecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        case 10: //spells
            return (unsigned int)SPLO.size();
        case 11: //bodyParts
            return (unsigned int)NIFZ.size();
        case 12: //nift_p
            return NIFT.size;
        case 31: //unused1
            return 2;
        case 32: //aiPackages
            return (unsigned int)PKID.size();
        case 33: //animations
            return (unsigned int)KFFZ.size();
        case 39: //unused2
            return 1;
        case 41: //unused3
            return 2;
        default:
            return 0;
        }
    }

void CREARecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 10: //spells
            for(unsigned int p = 0;p < SPLO.size();p++)
                FieldValues[p] = SPLO[p];
            return;
        case 11: //bodyParts
            for(unsigned int p = 0;p < NIFZ.size();p++)
                FieldValues[p] = NIFZ[p].value;
            return;
        case 12: //nift_p
            *FieldValues = NIFT.value;
            return;
        case 31: //unused1
            *FieldValues = &AIDT.value.unused1[0];
            return;
        case 32: //aiPackages
            for(unsigned int p = 0;p < PKID.size();p++)
                FieldValues[p] = PKID[p];
            return;
        case 33: //animations
            for(unsigned int p = 0;p < KFFZ.size();p++)
                FieldValues[p] = KFFZ[p].value;
            return;
        case 39: //unused2
            *FieldValues = &DATA.value.unused1;
            return;
        case 41: //unused3
            *FieldValues = &DATA.value.unused2[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int CREARecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 20: //factions
            switch(listField)
                {
                case 1: //faction
                    return FID_FIELD;
                case 2: //rank
                    return UBYTE_FIELD;
                case 3: //unused1
                    return BYTES_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 23: //items
            switch(listField)
                {
                case 1: //item
                    return FID_FIELD;
                case 2: //count
                    return INT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 59: //sounds
            switch(listField)
                {
                case 1: //type
                    return UINT_FIELD;
                case 2: //sound
                    return FID_FIELD;
                case 3: //chance
                    return UBYTE_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int CREARecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 20: //factions
            return (unsigned int)SNAM.size();
        case 23: //items
            return (unsigned int)CNTO.size();
        case 59: //sounds
            return (unsigned int)Sounds.size();
        default:
            return 0;
        }
    }

unsigned int CREARecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 20: //factions
            switch(listField)
                {
                case 3: //unused1
                    return 3;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

void CREARecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 20: //factions
            if(listIndex >= SNAM.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 3: //unused1
                    *FieldValues = &SNAM[listIndex]->value.unused1[0];
                    return;
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void * CREARecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 20: //factions
            if(listIndex >= SNAM.size())
                return NULL;
            switch(listField)
                {
                case 1: //faction
                    return &SNAM[listIndex]->value.faction;
                case 2: //rank
                    return &SNAM[listIndex]->value.rank;
                default:
                    return NULL;
                }
        case 23: //items
            if(listIndex >= CNTO.size())
                return NULL;
            switch(listField)
                {
                case 1: //item
                    return &CNTO[listIndex]->value.item;
                case 2: //count
                    return &CNTO[listIndex]->value.count;
                default:
                    return NULL;
                }
        case 59: //sounds
            if(listIndex >= Sounds.size())
                return NULL;
            switch(listField)
                {
                case 1: //type
                    return &Sounds[listIndex]->CSDT.value.type;
                case 2: //sound
                    return &Sounds[listIndex]->CSDI.value.fid;
                case 3: //chance
                    return &Sounds[listIndex]->CSDC.value.chance;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 7: //modPath
            MODL.Load();
            MODL->MODL.Copy(FieldValue);
            break;
        case 57: //bloodSprayPath
            NAM0.Copy(FieldValue);
            break;
        case 58: //bloodDecalPath
            NAM1.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 53: //turningSpeed
            TNAM.value.turningSpeed = FieldValue;
            break;
        case 54: //baseScale
            BNAM.value.baseScale = FieldValue;
            break;
        case 55: //footWeight
            WNAM.value.footWeight = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        case 12: //nift_p
            NIFT.Copy(FieldValue, nSize);
            break;
        case 31: //unused1
            if(nSize != 2)
                return;
            AIDT.value.unused1[0] = FieldValue[0];
            AIDT.value.unused1[1] = FieldValue[1];
            break;
        case 39: //unused2
            if(nSize != 1)
                return;
            DATA.value.unused1 = FieldValue[0];
            break;
        case 41: //unused3
            if(nSize != 2)
                return;
            DATA.value.unused2[0] = FieldValue[0];
            DATA.value.unused2[1] = FieldValue[1];
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 13: //flags
            ACBS.value.flags = FieldValue;
            break;
        case 21: //deathItem
            INAM.Load();
            INAM->fid = FieldValue;
            FormIDHandler.AddMaster(INAM->fid);
            break;
        case 22: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 28: //services
            AIDT.value.flags = FieldValue;
            break;
        case 52: //combatStyle
            ZNAM.Load();
            ZNAM->fid = FieldValue;
            FormIDHandler.AddMaster(ZNAM->fid);
            break;
        case 56: //inheritsSoundsFrom
            CSCR.Load();
            CSCR->fid = FieldValue;
            FormIDHandler.AddMaster(CSCR->fid);
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 14: //baseSpell
            ACBS.value.baseSpell = FieldValue;
            break;
        case 15: //fatigue
            ACBS.value.fatigue = FieldValue;
            break;
        case 16: //barterGold
            ACBS.value.barterGold = FieldValue;
            break;
        case 18: //calcMin
            ACBS.value.calcMin = FieldValue;
            break;
        case 19: //calcMax
            ACBS.value.calcMax = FieldValue;
            break;
        case 40: //health
            DATA.value.health = FieldValue;
            break;
        case 42: //attackDamage
            DATA.value.attackDamage = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, short FieldValue)
    {
    switch(Field)
        {
        case 17: //level
            ACBS.value.level = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 20: //factions
            if(listIndex >= SNAM.size())
                return;
            switch(listField)
                {
                case 1: //faction
                    SNAM[listIndex]->value.faction = FieldValue;
                    FormIDHandler.AddMaster(SNAM[listIndex]->value.faction);
                    break;
                default:
                    return;
                }
            break;
        case 23: //items
            if(listIndex >= CNTO.size())
                return;
            switch(listField)
                {
                case 1: //item
                    CNTO[listIndex]->value.item = FieldValue;
                    FormIDHandler.AddMaster(CNTO[listIndex]->value.item);
                    break;
                default:
                    return;
                }
            break;
        case 59: //sounds
            if(listIndex >= Sounds.size())
                return;
            switch(listField)
                {
                case 1: //type
                    Sounds[listIndex]->CSDT.value.type = FieldValue;
                    break;
                case 2: //sound
                    Sounds[listIndex]->CSDI.value.fid = FieldValue;
                    FormIDHandler.AddMaster(Sounds[listIndex]->CSDI.value.fid);
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 20: //factions
            if(listIndex >= SNAM.size())
                return;
            switch(listField)
                {
                case 2: //rank
                    SNAM[listIndex]->value.rank = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 59: //sounds
            if(listIndex >= Sounds.size())
                return;
            switch(listField)
                {
                case 3: //chance
                    Sounds[listIndex]->CSDC.value.chance = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    switch(subField)
        {
        case 23: //items
            if(listIndex >= CNTO.size())
                return;
            switch(listField)
                {
                case 2: //count
                    CNTO[listIndex]->value.count = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 20: //factions
            if(listIndex >= SNAM.size())
                return;
            switch(listField)
                {
                case 3: //unused1
                    if(nSize != 3)
                        return;
                    SNAM[listIndex]->value.unused1[0] = FieldValue[0];
                    SNAM[listIndex]->value.unused1[1] = FieldValue[1];
                    SNAM[listIndex]->value.unused1[2] = FieldValue[2];
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 10: //spells
            SPLO.clear();
            if(nSize)
                {
                SPLO.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    SPLO[x] = new unsigned int(FieldValue[x]);
                    FormIDHandler.AddMaster(SPLO[x]);
                    }
                }
            break;
        case 32: //aiPackages
            PKID.clear();
            if(nSize)
                {
                PKID.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    PKID[x] = new unsigned int(FieldValue[x]);
                    FormIDHandler.AddMaster(PKID[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 24: //aggression
            AIDT.value.aggression = FieldValue;
            break;
        case 25: //confidence
            AIDT.value.confidence = FieldValue;
            break;
        case 26: //energyLevel
            AIDT.value.energyLevel = FieldValue;
            break;
        case 27: //responsibility
            AIDT.value.responsibility = FieldValue;
            break;
        case 30: //trainLevel
            AIDT.value.trainLevel = FieldValue;
            break;
        case 34: //creatureType
            DATA.value.creatureType = FieldValue;
            break;
        case 35: //combat
            DATA.value.combat = FieldValue;
            break;
        case 36: //magic
            DATA.value.magic = FieldValue;
            break;
        case 37: //stealth
            DATA.value.stealth = FieldValue;
            break;
        case 38: //soul
            DATA.value.soul = FieldValue;
            break;

        case 43: //strength
            DATA.value.strength = FieldValue;
            break;
        case 44: //intelligence
            DATA.value.intelligence = FieldValue;
            break;
        case 45: //willpower
            DATA.value.willpower = FieldValue;
            break;
        case 46: //agility
            DATA.value.agility = FieldValue;
            break;
        case 47: //speed
            DATA.value.speed = FieldValue;
            break;
        case 48: //endurance
            DATA.value.endurance = FieldValue;
            break;
        case 49: //personality
            DATA.value.personality = FieldValue;
            break;
        case 50: //luck
            DATA.value.luck = FieldValue;
            break;
        case 51: //attackReach
            RNAM.value.attackReach = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue)
    {
    switch(Field)
        {
        case 29: //trainSkill
            AIDT.value.trainSkill = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CREARecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char **FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 11: //bodyParts
            NIFZ.clear();
            if(nSize)
                {
                NIFZ.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    NIFZ[x] = ISTRING(FieldValue[x]);
                    }
                }
            break;
        case 33: //animations
            KFFZ.clear();
            if(nSize)
                {
                KFFZ.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    KFFZ[x] = STRING(FieldValue[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

int CREARecord::DeleteField(const unsigned int Field)
    {
    GENAIDT defaultAIDT;
    GENACBS defaultACBS;
    CREADATA defaultDATA;
    unsigned int nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            break;
        case 8: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            break;
        case 9: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            break;
        case 10: //spells
            nSize = (unsigned int)SPLO.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete SPLO[x];
            SPLO.clear();
            break;
        case 11: //bodyParts
            NIFZ.clear();
            break;
        case 12: //nift_p
            NIFT.Unload();
            break;
        case 13: //flags
            ACBS.value.flags = defaultACBS.flags;
            break;
        case 14: //baseSpell
            ACBS.value.baseSpell = defaultACBS.baseSpell;
            break;
        case 15: //fatigue
            ACBS.value.fatigue = defaultACBS.fatigue;
            break;
        case 16: //barterGold
            ACBS.value.barterGold = defaultACBS.barterGold;
            break;
        case 17: //level
            ACBS.value.level = defaultACBS.level;
            break;
        case 18: //calcMin
            ACBS.value.calcMin = defaultACBS.calcMin;
            break;
        case 19: //calcMax
            ACBS.value.calcMax = defaultACBS.calcMax;
            break;
        case 20: //factions
            nSize = (unsigned int)SNAM.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete SNAM[x];
            SNAM.clear();
            break;
        case 21: //deathItem
            INAM.Unload();
            break;
        case 22: //script
            SCRI.Unload();
            break;
        case 23: //items
            nSize = (unsigned int)CNTO.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete CNTO[x];
            CNTO.clear();
            break;
        case 24: //aggression
            AIDT.value.aggression = defaultAIDT.aggression;
            break;
        case 25: //confidence
            AIDT.value.confidence = defaultAIDT.confidence;
            break;
        case 26: //energyLevel
            AIDT.value.confidence = defaultAIDT.confidence;
            break;
        case 27: //responsibility
            AIDT.value.responsibility = defaultAIDT.responsibility;
            break;
        case 28: //services
            AIDT.value.flags = defaultAIDT.flags;
            break;
        case 29: //trainSkill
            AIDT.value.trainSkill = defaultAIDT.trainSkill;
            break;
        case 30: //trainLevel
            AIDT.value.trainLevel = defaultAIDT.trainLevel;
            break;
        case 31: //unused1
            AIDT.value.unused1[0] = defaultAIDT.unused1[0];
            AIDT.value.unused1[1] = defaultAIDT.unused1[1];
            break;
        case 32: //aiPackages
            nSize = (unsigned int)PKID.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete PKID[x];
            PKID.clear();
            break;
        case 33: //animations
            KFFZ.clear();
            break;
        case 34: //creatureType
            DATA.value.creatureType = defaultDATA.creatureType;
            break;
        case 35: //combat
            DATA.value.combat = defaultDATA.combat;
            break;
        case 36: //magic
            DATA.value.magic = defaultDATA.magic;
            break;
        case 37: //stealth
            DATA.value.stealth = defaultDATA.stealth;
            break;
        case 38: //soul
            DATA.value.soul = defaultDATA.soul;
            break;
        case 39: //unused2
            DATA.value.unused1 = defaultDATA.unused1;
            break;
        case 40: //health
            DATA.value.health = defaultDATA.health;
            break;
        case 41: //unused3
            DATA.value.unused2[0] = defaultDATA.unused2[0];
            DATA.value.unused2[1] = defaultDATA.unused2[1];
            break;
        case 42: //attackDamage
            DATA.value.attackDamage = defaultDATA.attackDamage;
            break;
        case 43: //strength
            DATA.value.strength = defaultDATA.strength;
            break;
        case 44: //intelligence
            DATA.value.intelligence = defaultDATA.intelligence;
            break;
        case 45: //willpower
            DATA.value.willpower = defaultDATA.willpower;
            break;
        case 46: //agility
            DATA.value.agility = defaultDATA.agility;
            break;
        case 47: //speed
            DATA.value.speed = defaultDATA.speed;
            break;
        case 48: //endurance
            DATA.value.endurance = defaultDATA.endurance;
            break;
        case 49: //personality
            DATA.value.personality = defaultDATA.personality;
            break;
        case 50: //luck
            DATA.value.luck = defaultDATA.luck;
            break;
        case 51: //attackReach
            RNAM.Unload();
            break;
        case 52: //combatStyle
            ZNAM.Unload();
            break;
        case 53: //turningSpeed
            TNAM.Unload();
            break;
        case 54: //baseScale
            BNAM.Unload();
            break;
        case 55: //footWeight
            WNAM.Unload();
            break;
        case 56: //inheritsSoundsFrom
            CSCR.Unload();
            break;
        case 57: //bloodSprayPath
            NAM0.Unload();
            break;
        case 58: //bloodDecalPath
            NAM1.Unload();
            break;
        case 59: //sounds
            nSize = (unsigned int)Sounds.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete Sounds[x];
            Sounds.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }

int CREARecord::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    GENSNAM defaultSNAM;
    GENCNTO defaultCNTO;
    switch(subField)
        {
        case 20: //factions
            if(listIndex >= SNAM.size())
                return 0;
            switch(listField)
                {
                case 1: //faction
                    SNAM[listIndex]->value.faction = defaultSNAM.faction;
                    break;
                case 2: //rank
                    SNAM[listIndex]->value.rank = defaultSNAM.rank;
                    break;
                case 3: //unused1
                    SNAM[listIndex]->value.unused1[0] = defaultSNAM.unused1[0];
                    SNAM[listIndex]->value.unused1[1] = defaultSNAM.unused1[1];
                    SNAM[listIndex]->value.unused1[2] = defaultSNAM.unused1[2];
                    break;
                default:
                    return 0;
                }
            break;
        case 23: //items
            if(listIndex >= CNTO.size())
                return 0;
            switch(listField)
                {
                case 1: //item
                    CNTO[listIndex]->value.item = defaultCNTO.item;
                    break;
                case 2: //count
                    CNTO[listIndex]->value.count = defaultCNTO.count;
                    break;
                default:
                    return 0;
                }
            break;
        case 59: //sounds
            if(listIndex >= Sounds.size())
                return 0;
            switch(listField)
                {
                case 1: //type
                    Sounds[listIndex]->CSDT.Unload();
                    break;
                case 2: //sound
                    Sounds[listIndex]->CSDI.Unload();
                    break;
                case 3: //chance
                    Sounds[listIndex]->CSDC.Unload();
                    break;
                default:
                    return 0;
                }
            break;
        default:
            return 0;
        }
    return 1;
    }