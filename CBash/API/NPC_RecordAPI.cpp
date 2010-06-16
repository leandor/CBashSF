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
#include "..\Records\NPC_Record.h"

int NPC_Record::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<GENSNAM> *curSNAM = NULL;
    ReqRecordField<GENCNTO> *curCNTO = NULL;
    switch(subField)
        {
        case 17: //factions
            curSNAM = new ReqRecordField<GENSNAM>;
            SNAM.push_back(curSNAM);
            return (int)SNAM.size() - 1;
        case 22: //items
            curCNTO = new ReqRecordField<GENCNTO>;
            CNTO.push_back(curCNTO);
            return (int)CNTO.size() - 1;
        default:
            return -1;
        }
    }

int NPC_Record::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<GENSNAM> *curSNAM = NULL;
    ReqRecordField<GENCNTO> *curCNTO = NULL;
    switch(subField)
        {
        case 17: //factions
            curSNAM = SNAM.back();
            delete curSNAM;
            SNAM.pop_back();
            return (int)SNAM.size() - 1;
        case 22: //items
            curCNTO = CNTO.back();
            delete curCNTO;
            CNTO.pop_back();
            return (int)CNTO.size() - 1;
        default:
            return -1;
        }
    }

int NPC_Record::GetOtherFieldType(const unsigned int Field)
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
        case 10: //flags
            return UINT_FIELD;
        case 11: //baseSpell
            return USHORT_FIELD;
        case 12: //fatigue
            return USHORT_FIELD;
        case 13: //barterGold
            return USHORT_FIELD;
        case 14: //level
            return SHORT_FIELD;
        case 15: //calcMin
            return USHORT_FIELD;
        case 16: //calcMax
            return USHORT_FIELD;
        case 17: //factions
            return LIST_FIELD;
        case 18: //deathItem
            return FID_FIELD;
        case 19: //race
            return FID_FIELD;
        case 20: //spells
            return FIDARRAY_FIELD;
        case 21: //script
            return FID_FIELD;
        case 22: //items
            return LIST_FIELD;
        case 23: //aggression
            return UBYTE_FIELD;
        case 24: //confidence
            return UBYTE_FIELD;
        case 25: //energyLevel
            return UBYTE_FIELD;
        case 26: //responsibility
            return UBYTE_FIELD;
        case 27: //services
            return UINT_FIELD;
        case 28: //trainSkill
            return BYTE_FIELD;
        case 29: //trainLevel
            return UBYTE_FIELD;
        case 30: //unused1
            return BYTES_FIELD;
        case 31: //aiPackages
            return FIDARRAY_FIELD;
        case 32: //animations
            return STRINGARRAY_FIELD;
        case 33: //iclass
            return FID_FIELD;
        case 34: //armorer
            return UBYTE_FIELD;
        case 35: //athletics
            return UBYTE_FIELD;
        case 36: //blade
            return UBYTE_FIELD;
        case 37: //block
            return UBYTE_FIELD;
        case 38: //blunt
            return UBYTE_FIELD;
        case 39: //h2h
            return UBYTE_FIELD;
        case 40: //heavyArmor
            return UBYTE_FIELD;
        case 41: //alchemy
            return UBYTE_FIELD;
        case 42: //alteration
            return UBYTE_FIELD;
        case 43: //conjuration
            return UBYTE_FIELD;
        case 44: //destruction
            return UBYTE_FIELD;
        case 45: //illusion
            return UBYTE_FIELD;
        case 46: //mysticism
            return UBYTE_FIELD;
        case 47: //restoration
            return UBYTE_FIELD;
        case 48: //acrobatics
            return UBYTE_FIELD;
        case 49: //lightArmor
            return UBYTE_FIELD;
        case 50: //marksman
            return UBYTE_FIELD;
        case 51: //mercantile
            return UBYTE_FIELD;
        case 52: //security
            return UBYTE_FIELD;
        case 53: //sneak
            return UBYTE_FIELD;
        case 54: //speechcraft
            return UBYTE_FIELD;
        case 55: //health
            return USHORT_FIELD;
        case 56: //unused2
            return BYTES_FIELD;
        case 57: //strength
            return UBYTE_FIELD;
        case 58: //intelligence
            return UBYTE_FIELD;
        case 59: //willpower
            return UBYTE_FIELD;
        case 60: //agility
            return UBYTE_FIELD;
        case 61: //speed
            return UBYTE_FIELD;
        case 62: //endurance
            return UBYTE_FIELD;
        case 63: //personality
            return UBYTE_FIELD;
        case 64: //luck
            return UBYTE_FIELD;
        case 65: //hair
            return FID_FIELD;
        case 66: //hairLength
            return FLOAT_FIELD;
        case 67: //eye
            return FID_FIELD;
        case 68: //hairRed
            return UBYTE_FIELD;
        case 69: //hairGreen
            return UBYTE_FIELD;
        case 70: //hairBlue
            return UBYTE_FIELD;
        case 71: //unused3
            return BYTES_FIELD;
        case 72: //combatStyle
            return FID_FIELD;
        case 73: //fggs_p
            return BYTES_FIELD;
        case 74: //fgga_p
            return BYTES_FIELD;
        case 75: //fgts_p
            return BYTES_FIELD;
        case 76: //fnam
            return USHORT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * NPC_Record::GetOtherField(const unsigned int Field)
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
        case 10: //flags
            return &ACBS.value.flags;
        case 11: //baseSpell
            return &ACBS.value.baseSpell;
        case 12: //fatigue
            return &ACBS.value.fatigue;
        case 13: //barterGold
            return &ACBS.value.barterGold;
        case 14: //level
            return &ACBS.value.level;
        case 15: //calcMin
            return &ACBS.value.calcMin;
        case 16: //calcMax
            return &ACBS.value.calcMax;
        case 18: //deathItem
            if(INAM.IsLoaded())
                return &INAM->fid;
            return NULL;
        case 19: //race
            if(RNAM.IsLoaded())
                return &RNAM->fid;
            return NULL;
        case 21: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 23: //aggression
            return &AIDT.value.aggression;
        case 24: //confidence
            return &AIDT.value.confidence;
        case 25: //energyLevel
            return &AIDT.value.energyLevel;
        case 26: //responsibility
            return &AIDT.value.responsibility;
        case 27: //services
            return &AIDT.value.flags;
        case 28: //trainSkill
            return &AIDT.value.trainSkill;
        case 29: //trainLevel
            return &AIDT.value.trainLevel;
        case 33: //iclass
            return &CNAM.value.fid;
        case 34: //armorer
            return &DATA.value.armorer;
        case 35: //athletics
            return &DATA.value.athletics;
        case 36: //blade
            return &DATA.value.blade;
        case 37: //block
            return &DATA.value.block;
        case 38: //blunt
            return &DATA.value.blunt;
        case 39: //h2h
            return &DATA.value.h2h;
        case 40: //heavyArmor
            return &DATA.value.heavyArmor;
        case 41: //alchemy
            return &DATA.value.alchemy;
        case 42: //alteration
            return &DATA.value.alteration;
        case 43: //conjuration
            return &DATA.value.conjuration;
        case 44: //destruction
            return &DATA.value.destruction;
        case 45: //illusion
            return &DATA.value.illusion;
        case 46: //mysticism
            return &DATA.value.mysticism;
        case 47: //restoration
            return &DATA.value.restoration;
        case 48: //acrobatics
            return &DATA.value.acrobatics;
        case 49: //lightArmor
            return &DATA.value.lightArmor;
        case 50: //marksman
            return &DATA.value.marksman;
        case 51: //mercantile
            return &DATA.value.mercantile;
        case 52: //security
            return &DATA.value.security;
        case 53: //sneak
            return &DATA.value.sneak;
        case 54: //speechcraft
            return &DATA.value.speechcraft;
        case 55: //health
            return &DATA.value.health;
        case 57: //strength
            return &DATA.value.strength;
        case 58: //intelligence
            return &DATA.value.intelligence;
        case 59: //willpower
            return &DATA.value.willpower;
        case 60: //agility
            return &DATA.value.agility;
        case 61: //speed
            return &DATA.value.speed;
        case 62: //endurance
            return &DATA.value.endurance;
        case 63: //personality
            return &DATA.value.personality;
        case 64: //luck
            return &DATA.value.luck;
        case 65: //hair
            return &HNAM.value.fid;
        case 66: //hairLength
            if(LNAM.IsLoaded())
                return &LNAM->hairLength;
            return NULL;
        case 67: //eye
            if(ENAM.IsLoaded())
                return &ENAM->fid;
            return NULL;
        case 68: //hairRed
            return &HCLR.value.red;
        case 69: //hairGreen
            return &HCLR.value.green;
        case 70: //hairBlue
            return &HCLR.value.blue;
        case 72: //combatStyle
            if(ZNAM.IsLoaded())
                return &ZNAM->fid;
            return NULL;
        case 76: //fnam
            return &FNAM.value.fnam;
        default:
            return NULL;
        }
    }

unsigned int NPC_Record::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        case 20: //spells
            return (unsigned int)SPLO.size();
        case 30: //unused1
            return 2;
        case 31: //aiPackages
            return (unsigned int)PKID.size();
        case 32: //animations
            return (unsigned int)KFFZ.size();
        case 56: //unused2
            return 2;
        case 71: //unused3
            return 1;
        case 73: //fggs_p
            return FGGS.size;
        case 74: //fgga_p
            return FGGA.size;
        case 75: //fgts_p
            return FGTS.size;
        default:
            return 0;
        }
    }

void NPC_Record::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 20: //spells
            for(unsigned int p = 0;p < SPLO.size();p++)
                FieldValues[p] = SPLO[p];
            return;
        case 30: //unused1
            *FieldValues = &AIDT.value.unused1[0];
            return;
        case 31: //aiPackages
            for(unsigned int p = 0;p < PKID.size();p++)
                FieldValues[p] = PKID[p];
            return;
        case 32: //animations
            for(unsigned int p = 0;p < KFFZ.size();p++)
                FieldValues[p] = KFFZ[p].value;
            return;
        case 56: //unused2
            *FieldValues = &DATA.value.unused1[0];
            return;
        case 71: //unused3
            *FieldValues = &HCLR.value.unused1;
            return;
        case 73: //fggs_p
            *FieldValues = FGGS.value;
            return;
        case 74: //fgga_p
            *FieldValues = FGGA.value;
            return;
        case 75: //fgts_p
            *FieldValues = FGTS.value;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int NPC_Record::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 17: //factions
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
        case 22: //items
            switch(listField)
                {
                case 1: //item
                    return FID_FIELD;
                case 2: //count
                    return INT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int NPC_Record::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 17: //factions
            return (unsigned int)SNAM.size();
        case 22: //items
            return (unsigned int)CNTO.size();
        default:
            return 0;
        }
    }

unsigned int NPC_Record::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 17: //factions
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

void NPC_Record::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 17: //factions
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

void * NPC_Record::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 17: //factions
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
        case 22: //items
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
        default:
            return NULL;
        }
    }

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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
        default:
            return;
        }
    return;
    }

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 66: //hairLength
            LNAM.Load();
            LNAM->hairLength = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        case 30: //unused1
            if(nSize != 2)
                return;
            AIDT.value.unused1[0] = FieldValue[0];
            AIDT.value.unused1[1] = FieldValue[1];
            break;
        case 56: //unused2
            if(nSize != 2)
                return;
            DATA.value.unused1[0] = FieldValue[0];
            DATA.value.unused1[1] = FieldValue[1];
            break;
        case 71: //unused3
            if(nSize != 1)
                return;
            HCLR.value.unused1 = FieldValue[0];
            break;
        case 73: //fggs_p
            FGGS.Copy(FieldValue, nSize);
            break;
        case 74: //fgga_p
            FGGA.Copy(FieldValue, nSize);
            break;
        case 75: //fgts_p
            FGTS.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void NPC_Record::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 10: //flags
            SetFlagMask(FieldValue);
            //ACBS.value.flags = FieldValue;
            break;
        case 18: //deathItem
            INAM.Load();
            INAM->fid = FieldValue;
            FormIDHandler.AddMaster(INAM->fid);
            break;
        case 19: //race
            RNAM.Load();
            RNAM->fid = FieldValue;
            FormIDHandler.AddMaster(RNAM->fid);
            break;
        case 21: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 27: //services
            SetServicesFlagMask(FieldValue);
            //AIDT.value.flags = FieldValue;
            break;
        case 33: //iclass
            CNAM.value.fid = FieldValue;
            FormIDHandler.AddMaster(CNAM.value.fid);
            break;
        case 65: //hair
            HNAM.value.fid = FieldValue;
            HNAM.isLoaded = true;
            FormIDHandler.AddMaster(HNAM.value.fid);
            break;
        case 67: //eye
            ENAM.Load();
            ENAM->fid = FieldValue;
            FormIDHandler.AddMaster(ENAM->fid);
            break;
        case 72: //combatStyle
            ZNAM.Load();
            ZNAM->fid = FieldValue;
            FormIDHandler.AddMaster(ZNAM->fid);
            break;
        default:
            return;
        }
    return;
    }

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 11: //baseSpell
            ACBS.value.baseSpell = FieldValue;
            break;
        case 12: //fatigue
            ACBS.value.fatigue = FieldValue;
            break;
        case 13: //barterGold
            ACBS.value.barterGold = FieldValue;
            break;
        case 15: //calcMin
            ACBS.value.calcMin = FieldValue;
            break;
        case 16: //calcMax
            ACBS.value.calcMax = FieldValue;
            break;
        case 55: //health
            DATA.value.health = FieldValue;
            break;
        case 76: //fnam
            FNAM.value.fnam = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, short FieldValue)
    {
    switch(Field)
        {
        case 14: //level
            ACBS.value.level = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void NPC_Record::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 17: //factions
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
        case 22: //items
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
        default:
            return;
        }
    return;
    }

void NPC_Record::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 17: //factions
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
        default:
            return;
        }
    return;
    }

void NPC_Record::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    switch(subField)
        {
        case 22: //items
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

void NPC_Record::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 17: //factions
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

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 20: //spells
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
        case 31: //aiPackages
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

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 23: //aggression
            AIDT.value.aggression = FieldValue;
            break;
        case 24: //confidence
            AIDT.value.confidence = FieldValue;
            break;
        case 25: //energyLevel
            AIDT.value.energyLevel = FieldValue;
            break;
        case 26: //responsibility
            AIDT.value.responsibility = FieldValue;
            break;
        case 29: //trainLevel
            AIDT.value.trainLevel = FieldValue;
            break;
        case 34: //armorer
            DATA.value.armorer = FieldValue;
            break;
        case 35: //athletics
            DATA.value.athletics = FieldValue;
            break;
        case 36: //blade
            DATA.value.blade = FieldValue;
            break;
        case 37: //block
            DATA.value.block = FieldValue;
            break;
        case 38: //blunt
            DATA.value.blunt = FieldValue;
            break;
        case 39: //h2h
            DATA.value.h2h = FieldValue;
            break;
        case 40: //heavyArmor
            DATA.value.heavyArmor = FieldValue;
            break;
        case 41: //alchemy
            DATA.value.alchemy = FieldValue;
            break;
        case 42: //alteration
            DATA.value.alteration = FieldValue;
            break;
        case 43: //conjuration
            DATA.value.conjuration = FieldValue;
            break;
        case 44: //destruction
            DATA.value.destruction = FieldValue;
            break;
        case 45: //illusion
            DATA.value.illusion = FieldValue;
            break;
        case 46: //mysticism
            DATA.value.mysticism = FieldValue;
            break;
        case 47: //restoration
            DATA.value.restoration = FieldValue;
            break;
        case 48: //acrobatics
            DATA.value.acrobatics = FieldValue;
            break;
        case 49: //lightArmor
            DATA.value.lightArmor = FieldValue;
            break;
        case 50: //marksman
            DATA.value.marksman = FieldValue;
            break;
        case 51: //mercantile
            DATA.value.mercantile = FieldValue;
            break;
        case 52: //security
            DATA.value.security = FieldValue;
            break;
        case 53: //sneak
            DATA.value.sneak = FieldValue;
            break;
        case 54: //speechcraft
            DATA.value.speechcraft = FieldValue;
            break;
        case 57: //strength
            DATA.value.strength = FieldValue;
            break;
        case 58: //intelligence
            DATA.value.intelligence = FieldValue;
            break;
        case 59: //willpower
            DATA.value.willpower = FieldValue;
            break;
        case 60: //agility
            DATA.value.agility = FieldValue;
            break;
        case 61: //speed
            DATA.value.speed = FieldValue;
            break;
        case 62: //endurance
            DATA.value.endurance = FieldValue;
            break;
        case 63: //personality
            DATA.value.personality = FieldValue;
            break;
        case 64: //luck
            DATA.value.luck = FieldValue;
            break;
        case 68: //hairRed
            HCLR.value.red = FieldValue;
            break;
        case 69: //hairGreen
            HCLR.value.green = FieldValue;
            break;
        case 70: //hairBlue
            HCLR.value.blue = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue)
    {
    switch(Field)
        {
        case 28: //trainSkill
            AIDT.value.trainSkill = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void NPC_Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char **FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 32: //animations
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

int NPC_Record::DeleteField(const unsigned int Field)
    {
    GENAIDT defaultAIDT;
    GENACBS defaultACBS;
    NPC_DATA defaultDATA;
    GENCLR defaultHCLR;
    NPC_FNAM defaultFNAM;
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
        case 10: //flags
            ACBS.value.flags = defaultACBS.flags;
            break;
        case 11: //baseSpell
            ACBS.value.baseSpell = defaultACBS.baseSpell;
            break;
        case 12: //fatigue
            ACBS.value.fatigue = defaultACBS.fatigue;
            break;
        case 13: //barterGold
            ACBS.value.barterGold = defaultACBS.barterGold;
            break;
        case 14: //level
            ACBS.value.level = defaultACBS.level;
            break;
        case 15: //calcMin
            ACBS.value.calcMin = defaultACBS.calcMin;
            break;
        case 16: //calcMax
            ACBS.value.calcMax = defaultACBS.calcMax;
            break;
        case 18: //deathItem
            INAM.Unload();
            break;
        case 19: //race
            RNAM.Unload();
            break;
        case 20: //spells
            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            SPLO.clear();
            break;
        case 21: //script
            SCRI.Unload();
            break;
        case 23: //aggression
            AIDT.value.aggression = defaultAIDT.aggression;
            break;
        case 24: //confidence
            AIDT.value.confidence = defaultAIDT.confidence;
            break;
        case 25: //energyLevel
            AIDT.value.confidence = defaultAIDT.confidence;
            break;
        case 26: //responsibility
            AIDT.value.responsibility = defaultAIDT.responsibility;
            break;
        case 27: //services
            AIDT.value.flags = defaultAIDT.flags;
            break;
        case 28: //trainSkill
            AIDT.value.trainSkill = defaultAIDT.trainSkill;
            break;
        case 29: //trainLevel
            AIDT.value.trainLevel = defaultAIDT.trainLevel;
            break;
        case 30: //unused1
            AIDT.value.unused1[0] = defaultAIDT.unused1[0];
            AIDT.value.unused1[1] = defaultAIDT.unused1[1];
            break;
        case 31: //aiPackages
            for(unsigned int x = 0; x < PKID.size(); x++)
                delete PKID[x];
            PKID.clear();
            break;
        case 32: //animations
            KFFZ.clear();
            break;
        case 33: //iclass
            CNAM.Unload();
            break;
        case 34: //armorer
            DATA.value.armorer = defaultDATA.armorer;
            break;
        case 35: //athletics
            DATA.value.athletics = defaultDATA.athletics;
            break;
        case 36: //blade
            DATA.value.blade = defaultDATA.blade;
            break;
        case 37: //block
            DATA.value.block = defaultDATA.block;
            break;
        case 38: //blunt
            DATA.value.blunt = defaultDATA.blunt;
            break;
        case 39: //h2h
            DATA.value.h2h = defaultDATA.h2h;
            break;
        case 40: //heavyArmor
            DATA.value.heavyArmor = defaultDATA.heavyArmor;
            break;
        case 41: //alchemy
            DATA.value.alchemy = defaultDATA.alchemy;
            break;
        case 42: //alteration
            DATA.value.alteration = defaultDATA.alteration;
            break;
        case 43: //conjuration
            DATA.value.conjuration = defaultDATA.conjuration;
            break;
        case 44: //destruction
            DATA.value.destruction = defaultDATA.destruction;
            break;
        case 45: //illusion
            DATA.value.illusion = defaultDATA.illusion;
            break;
        case 46: //mysticism
            DATA.value.mysticism = defaultDATA.mysticism;
            break;
        case 47: //restoration
            DATA.value.restoration = defaultDATA.restoration;
            break;
        case 48: //acrobatics
            DATA.value.acrobatics = defaultDATA.acrobatics;
            break;
        case 49: //lightArmor
            DATA.value.lightArmor = defaultDATA.lightArmor;
            break;
        case 50: //marksman
            DATA.value.marksman = defaultDATA.marksman;
            break;
        case 51: //mercantile
            DATA.value.mercantile = defaultDATA.mercantile;
            break;
        case 52: //security
            DATA.value.security = defaultDATA.security;
            break;
        case 53: //sneak
            DATA.value.sneak = defaultDATA.sneak;
            break;
        case 54: //speechcraft
            DATA.value.speechcraft = defaultDATA.speechcraft;
            break;
        case 55: //health
            DATA.value.health = defaultDATA.health;
            break;
        case 56: //unused2
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            break;
        case 57: //strength
            DATA.value.strength = defaultDATA.strength;
            break;
        case 58: //intelligence
            DATA.value.intelligence = defaultDATA.intelligence;
            break;
        case 59: //willpower
            DATA.value.willpower = defaultDATA.willpower;
            break;
        case 60: //agility
            DATA.value.agility = defaultDATA.agility;
            break;
        case 61: //speed
            DATA.value.speed = defaultDATA.speed;
            break;
        case 62: //endurance
            DATA.value.endurance = defaultDATA.endurance;
            break;
        case 63: //personality
            DATA.value.personality = defaultDATA.personality;
            break;
        case 64: //luck
            DATA.value.luck = defaultDATA.luck;
            break;
        case 65: //hair
            HNAM.Unload();
            break;
        case 66: //hairLength
            LNAM.Unload();
            break;
        case 67: //eye
            ENAM.Unload();
            break;
        case 68: //hairRed
            HCLR.value.red = defaultHCLR.red;
            break;
        case 69: //hairGreen
            HCLR.value.green = defaultHCLR.green;
            break;
        case 70: //hairBlue
            HCLR.value.blue = defaultHCLR.blue;
            break;
        case 71: //unused3
            HCLR.value.unused1 = defaultHCLR.unused1;
            break;
        case 72: //combatStyle
            ZNAM.Unload();
            break;
        case 73: //fggs_p
            FGGS.Unload();
            break;
        case 74: //fgga_p
            FGGA.Unload();
            break;
        case 75: //fgts_p
            FGTS.Unload();
            break;
        case 76: //fnam
            FNAM.value.fnam = defaultFNAM.fnam;
            break;
        default:
            return 0;
        }
    return 1;
    }

int NPC_Record::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    GENSNAM defaultSNAM;
    GENCNTO defaultCNTO;
    switch(subField)
        {
        case 17: //factions
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
        case 22: //items
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
        default:
            return 0;
        }
    return 1;
    }