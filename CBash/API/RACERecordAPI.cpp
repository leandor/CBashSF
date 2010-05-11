# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#include "..\Common.h"
#include "..\Records\RACERecord.h"

int RACERecord::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<GENXNAM> *curXNAM = NULL;
    switch(subField)
        {
        case 9: //relations
            curXNAM = new ReqRecordField<GENXNAM>;
            XNAM.push_back(curXNAM);
            return (int)XNAM.size() - 1;
        default:
            return -1;
        }
    }

int RACERecord::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<GENXNAM> *curXNAM = NULL;
    switch(subField)
        {
        case 9: //relations
            curXNAM = XNAM.back();
            delete curXNAM;
            XNAM.pop_back();
            return (int)XNAM.size() - 1;
        default:
            return -1;
        }
    }

int RACERecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //text
            return STRING_FIELD;
        case 8: //spells
            return FIDARRAY_FIELD;
        case 9: //relations
            return LIST_FIELD;
        case 10: //skill1
            return BYTE_FIELD;
        case 11: //skill1Boost
            return BYTE_FIELD;
        case 12: //skill2
            return BYTE_FIELD;
        case 13: //skill2Boost
            return BYTE_FIELD;
        case 14: //skill3
            return BYTE_FIELD;
        case 15: //skill3Boost
            return BYTE_FIELD;
        case 16: //skill4
            return BYTE_FIELD;
        case 17: //skill4Boost
            return BYTE_FIELD;
        case 18: //skill5
            return BYTE_FIELD;
        case 19: //skill5Boost
            return BYTE_FIELD;
        case 20: //skill6
            return BYTE_FIELD;
        case 21: //skill6Boost
            return BYTE_FIELD;
        case 22: //skill7
            return BYTE_FIELD;
        case 23: //skill7Boost
            return BYTE_FIELD;
        case 24: //unused1
            return BYTES_FIELD;
        case 25: //maleHeight
            return FLOAT_FIELD;
        case 26: //femaleHeight
            return FLOAT_FIELD;
        case 27: //maleWeight
            return FLOAT_FIELD;
        case 28: //femaleWeight
            return FLOAT_FIELD;
        case 29: //flags
            return UINT_FIELD;
        case 30: //maleVoice
            return FID_FIELD;
        case 31: //femaleVoice
            return FID_FIELD;
        case 32: //defaultHairMale
            return FID_FIELD;
        case 33: //defaultHairFemale
            return FID_FIELD;
        case 34: //defaultHairColor
            return UBYTE_FIELD;
        case 35: //mainClamp
            return FLOAT_FIELD;
        case 36: //faceClamp
            return FLOAT_FIELD;
        case 37: //maleStrength
            return UBYTE_FIELD;
        case 38: //maleIntelligence
            return UBYTE_FIELD;
        case 39: //maleWillpower
            return UBYTE_FIELD;
        case 40: //maleAgility
            return UBYTE_FIELD;
        case 41: //maleSpeed
            return UBYTE_FIELD;
        case 42: //maleEndurance
            return UBYTE_FIELD;
        case 43: //malePersonality
            return UBYTE_FIELD;
        case 44: //maleLuck
            return UBYTE_FIELD;
        case 45: //femaleStrength
            return UBYTE_FIELD;
        case 46: //femaleIntelligence
            return UBYTE_FIELD;
        case 47: //femaleWillpower
            return UBYTE_FIELD;
        case 48: //femaleAgility
            return UBYTE_FIELD;
        case 49: //femaleSpeed
            return UBYTE_FIELD;
        case 50: //femaleEndurance
            return UBYTE_FIELD;
        case 51: //femalePersonality
            return UBYTE_FIELD;
        case 52: //femaleLuck
            return UBYTE_FIELD;
        case 53: //head_modPath
            return STRING_FIELD;
        case 54: //head_modb
            return FLOAT_FIELD;
        case 55: //head_iconPath
            return STRING_FIELD;
        case 56: //head_modt_p
            return BYTES_FIELD;
        case 57: //maleEars_modPath
            return STRING_FIELD;
        case 58: //maleEars_modb
            return FLOAT_FIELD;
        case 59: //maleEars_iconPath
            return STRING_FIELD;
        case 60: //maleEars_modt_p
            return BYTES_FIELD;
        case 61: //femaleEars_modPath
            return STRING_FIELD;
        case 62: //femaleEars_modb
            return FLOAT_FIELD;
        case 63: //femaleEars_iconPath
            return STRING_FIELD;
        case 64: //femaleEars_modt_p
            return BYTES_FIELD;
        case 65: //mouth_modPath
            return STRING_FIELD;
        case 66: //mouth_modb
            return FLOAT_FIELD;
        case 67: //mouth_iconPath
            return STRING_FIELD;
        case 68: //mouth_modt_p
            return BYTES_FIELD;
        case 69: //teethLower_modPath
            return STRING_FIELD;
        case 70: //teethLower_modb
            return FLOAT_FIELD;
        case 71: //teethLower_iconPath
            return STRING_FIELD;
        case 72: //teethLower_modt_p
            return BYTES_FIELD;
        case 73: //teethUpper_modPath
            return STRING_FIELD;
        case 74: //teethUpper_modb
            return FLOAT_FIELD;
        case 75: //teethUpper_iconPath
            return STRING_FIELD;
        case 76: //teethUpper_modt_p
            return BYTES_FIELD;
        case 77: //tongue_modPath
            return STRING_FIELD;
        case 78: //tongue_modb
            return FLOAT_FIELD;
        case 79: //tongue_iconPath
            return STRING_FIELD;
        case 80: //tongue_modt_p
            return BYTES_FIELD;
        case 81: //leftEye_modPath
            return STRING_FIELD;
        case 82: //leftEye_modb
            return FLOAT_FIELD;
        case 83: //leftEye_iconPath
            return STRING_FIELD;
        case 84: //leftEye_modt_p
            return BYTES_FIELD;
        case 85: //rightEye_modPath
            return STRING_FIELD;
        case 86: //rightEye_modb
            return FLOAT_FIELD;
        case 87: //rightEye_iconPath
            return STRING_FIELD;
        case 88: //rightEye_modt_p
            return BYTES_FIELD;
        case 89: //maleTailModelPath
            return STRING_FIELD;
        case 90: //maleTailModel_b
            return FLOAT_FIELD;
        case 91: //maleTailModel_t_p
            return BYTES_FIELD;
        case 92: //maleUpperBodyPath
            return STRING_FIELD;
        case 93: //maleLowerBodyPath
            return STRING_FIELD;
        case 94: //maleHandPath
            return STRING_FIELD;
        case 95: //maleFootPath
            return STRING_FIELD;
        case 96: //maleTailPath
            return STRING_FIELD;
        case 97: //femaleTailModelPath
            return STRING_FIELD;
        case 98: //femaleTailModel_b
            return FLOAT_FIELD;
        case 99: //femaleTailModel_t_p
            return BYTES_FIELD;
        case 100: //femaleUpperBodyPath
            return STRING_FIELD;
        case 101: //femaleLowerBodyPath
            return STRING_FIELD;
        case 102: //femaleHandPath
            return STRING_FIELD;
        case 103: //femaleFootPath
            return STRING_FIELD;
        case 104: //femaleTailPath
            return STRING_FIELD;
        case 105: //hairs
            return FIDARRAY_FIELD;
        case 106: //eyes
            return FIDARRAY_FIELD;
        case 107: //fggs_p
            return BYTES_FIELD;
        case 108: //fgga_p
            return BYTES_FIELD;
        case 109: //fgts_p
            return BYTES_FIELD;
        case 110: //snam_p
            return BYTES_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * RACERecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //text
            return DESC.value;
        case 10: //skill1
            return &DATA.value.skills[0].value;
        case 11: //skill1Boost
            return &DATA.value.skills[0].boost;
        case 12: //skill2
            return &DATA.value.skills[1].value;
        case 13: //skill2Boost
            return &DATA.value.skills[1].boost;
        case 14: //skill3
            return &DATA.value.skills[2].value;
        case 15: //skill3Boost
            return &DATA.value.skills[2].boost;
        case 16: //skill4
            return &DATA.value.skills[3].value;
        case 17: //skill4Boost
            return &DATA.value.skills[3].boost;
        case 18: //skill5
            return &DATA.value.skills[4].value;
        case 19: //skill5Boost
            return &DATA.value.skills[4].boost;
        case 20: //skill6
            return &DATA.value.skills[5].value;
        case 21: //skill6Boost
            return &DATA.value.skills[5].boost;
        case 22: //skill7
            return &DATA.value.skills[6].value;
        case 23: //skill7Boost
            return &DATA.value.skills[6].boost;
        case 25: //maleHeight
            return &DATA.value.maleHeight;
        case 26: //femaleHeight
            return &DATA.value.femaleHeight;
        case 27: //maleWeight
            return &DATA.value.maleWeight;
        case 28: //femaleWeight
            return &DATA.value.femaleWeight;
        case 29: //flags
            return &DATA.value.flags;
        case 30: //maleVoice
            return &VNAM.value.maleVoice;
        case 31: //femaleVoice
            return &VNAM.value.femaleVoice;
        case 32: //defaultHairMale
            return &DNAM.value.defaultHairMale;
        case 33: //defaultHairFemale
            return &DNAM.value.defaultHairFemale;
        case 34: //defaultHairColor
            return &CNAM.value.defaultHairColor;
        case 35: //mainClamp
            return &PNAM.value.mainClamp;
        case 36: //faceClamp
            return &UNAM.value.faceClamp;
        case 37: //maleStrength
            return &ATTR.value.maleStrength;
        case 38: //maleIntelligence
            return &ATTR.value.maleIntelligence;
        case 39: //maleWillpower
            return &ATTR.value.maleWillpower;
        case 40: //maleAgility
            return &ATTR.value.maleAgility;
        case 41: //maleSpeed
            return &ATTR.value.maleSpeed;
        case 42: //maleEndurance
            return &ATTR.value.maleEndurance;
        case 43: //malePersonality
            return &ATTR.value.malePersonality;
        case 44: //maleLuck
            return &ATTR.value.maleLuck;
        case 45: //femaleStrength
            return &ATTR.value.femaleStrength;
        case 46: //femaleIntelligence
            return &ATTR.value.femaleIntelligence;
        case 47: //femaleWillpower
            return &ATTR.value.femaleWillpower;
        case 48: //femaleAgility
            return &ATTR.value.femaleAgility;
        case 49: //femaleSpeed
            return &ATTR.value.femaleSpeed;
        case 50: //femaleEndurance
            return &ATTR.value.femaleEndurance;
        case 51: //femalePersonality
            return &ATTR.value.femalePersonality;
        case 52: //femaleLuck
            return &ATTR.value.femaleLuck;
        case 53: //head_modPath
            return MOD0.MODL.value;
        case 54: //head_modb
            return &MOD0.MODB.value.MODB;
        case 55: //head_iconPath
            return MOD0.ICON.value;
        case 57: //maleEars_modPath
            return MOD1.MODL.value;
        case 58: //maleEars_modb
            return &MOD1.MODB.value.MODB;
        case 59: //maleEars_iconPath
            return MOD1.ICON.value;
        case 61: //femaleEars_modPath
            return MOD2.MODL.value;
        case 62: //femaleEars_modb
            return &MOD2.MODB.value.MODB;
        case 63: //femaleEars_iconPath
            return MOD2.ICON.value;
        case 65: //mouth_modPath
            return MOD3.MODL.value;
        case 66: //mouth_modb
            return &MOD3.MODB.value.MODB;
        case 67: //mouth_iconPath
            return MOD3.ICON.value;
        case 69: //teethLower_modPath
            return MOD4.MODL.value;
        case 70: //teethLower_modb
            return &MOD4.MODB.value.MODB;
        case 71: //teethLower_iconPath
            return MOD4.ICON.value;
        case 73: //teethUpper_modPath
            return MOD5.MODL.value;
        case 74: //teethUpper_modb
            return &MOD5.MODB.value.MODB;
        case 75: //teethUpper_iconPath
            return MOD5.ICON.value;
        case 77: //tongue_modPath
            return MOD6.MODL.value;
        case 78: //tongue_modb
            return &MOD6.MODB.value.MODB;
        case 79: //tongue_iconPath
            return MOD6.ICON.value;
        case 81: //leftEye_modPath
            return MOD7.MODL.value;
        case 82: //leftEye_modb
            return &MOD7.MODB.value.MODB;
        case 83: //leftEye_iconPath
            return MOD7.ICON.value;
        case 85: //rightEye_modPath
            return MOD8.MODL.value;
        case 86: //rightEye_modb
            return &MOD8.MODB.value.MODB;
        case 87: //rightEye_iconPath
            return MOD8.ICON.value;
        case 89: //maleTailModelPath
            return MMODL.MODL.value;
        case 90: //maleTailModel_b
            return &MMODL.MODB.value.MODB;
        case 92: //maleUpperBodyPath
            return MICON0.value;
        case 93: //maleLowerBodyPath
            return MICON1.value;
        case 94: //maleHandPath
            return MICON2.value;
        case 95: //maleFootPath
            return MICON3.value;
        case 96: //maleTailPath
            return MICON4.value;
        case 97: //femaleTailModelPath
            return FMODL.MODL.value;
        case 98: //femaleTailModel_b
            return &FMODL.MODB.value.MODB;
        case 100: //femaleUpperBodyPath
            return FICON0.value;
        case 101: //femaleLowerBodyPath
            return FICON1.value;
        case 102: //femaleHandPath
            return FICON2.value;
        case 103: //femaleFootPath
            return FICON3.value;
        case 104: //femaleTailPath
            return FICON4.value;
        default:
            return NULL;
        }
    }

unsigned int RACERecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //spells
            return (unsigned int)SPLO.size();
        case 24: //unused1
            return 2;
        case 56: //head_modt_p
            return MOD0.MODT.size;
        case 60: //maleEars_modt_p
            return MOD1.MODT.size;
        case 64: //femaleEars_modt_p
            return MOD2.MODT.size;
        case 68: //mouth_modt_p
            return MOD3.MODT.size;
        case 72: //teethLower_modt_p
            return MOD4.MODT.size;
        case 76: //teethUpper_modt_p
            return MOD5.MODT.size;
        case 80: //tongue_modt_p
            return MOD6.MODT.size;
        case 84: //leftEye_modt_p
            return MOD7.MODT.size;
        case 88: //rightEye_modt_p
            return MOD8.MODT.size;
        case 91: //maleTailModel_t_p
            return MMODL.MODT.size;
        case 99: //femaleTailModel_t_p
            return FMODL.MODT.size;
        case 105: //hairs
            return (unsigned int)HNAM.size();
        case 106: //eyes
            return (unsigned int)ENAM.size();
        case 107: //fggs_p
            return FGGS.GetSize();
        case 108: //fgga_p
            return FGGA.GetSize();
        case 109: //fgts_p
            return FGTS.GetSize();
        case 110: //snam_p
            return SNAM.GetSize();
        default:
            return 0;
        }
    }

void RACERecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //spells
            for(unsigned int p = 0;p < SPLO.size();p++)
                FieldValues[p] = SPLO[p];
            return;
        case 24: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return;
        case 56: //head_modt_p
            *FieldValues = MOD0.MODT.value;
            return;
        case 60: //maleEars_modt_p
            *FieldValues = MOD1.MODT.value;
            return;
        case 64: //femaleEars_modt_p
            *FieldValues = MOD2.MODT.value;
            return;
        case 68: //mouth_modt_p
            *FieldValues = MOD3.MODT.value;
            return;
        case 72: //teethLower_modt_p
            *FieldValues = MOD4.MODT.value;
            return;
        case 76: //teethUpper_modt_p
            *FieldValues = MOD5.MODT.value;
            return;
        case 80: //tongue_modt_p
            *FieldValues = MOD6.MODT.value;
            return;
        case 84: //leftEye_modt_p
            *FieldValues = MOD7.MODT.value;
            return;
        case 88: //rightEye_modt_p
            *FieldValues = MOD8.MODT.value;
            return;
        case 91: //maleTailModel_t_p
            *FieldValues = MMODL.MODT.value;
            return;
        case 99: //femaleTailModel_t_p
            *FieldValues = FMODL.MODT.value;
            return;
        case 105: //hairs
            for(unsigned int p = 0;p < HNAM.size();p++)
                FieldValues[p] = &HNAM[p];
            return;
        case 106: //eyes
            for(unsigned int p = 0;p < ENAM.size();p++)
                FieldValues[p] = &ENAM[p];
            return;
        case 107: //fggs_p
            *FieldValues = FGGS.value;
            return;
        case 108: //fgga_p
            *FieldValues = FGGA.value;
            return;
        case 109: //fgts_p
            *FieldValues = FGTS.value;
            return;
        case 110: //snam_p
            *FieldValues = &SNAM.value.SNAM[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int RACERecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 9: //relations
            switch(listField)
                {
                case 1: //faction
                    return FID_FIELD;
                case 2: //mod
                    return INT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int RACERecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //relations
            return (unsigned int)XNAM.size();
        default:
            return 0;
        }
    }

void * RACERecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 9: //relations
            if(listIndex >= XNAM.size())
                return NULL;
            switch(listField)
                {
                case 1: //faction
                    return &XNAM[listIndex]->value.faction;
                case 2: //mod
                    return &XNAM[listIndex]->value.mod;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void RACERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 7: //text
            DESC.Copy(FieldValue);
            break;
        case 53: //head_modPath
            MOD0.MODL.Copy(FieldValue);
            break;
        case 55: //head_iconPath
            MOD0.ICON.Copy(FieldValue);
            break;
        case 57: //maleEars_modPath
            MOD1.MODL.Copy(FieldValue);
            break;
        case 59: //maleEars_iconPath
            MOD1.ICON.Copy(FieldValue);
            break;
        case 61: //femaleEars_modPath
            MOD2.MODL.Copy(FieldValue);
            break;
        case 63: //femaleEars_iconPath
            MOD2.ICON.Copy(FieldValue);
            break;
        case 65: //mouth_modPath
            MOD3.MODL.Copy(FieldValue);
            break;
        case 67: //mouth_iconPath
            MOD3.ICON.Copy(FieldValue);
            break;
        case 69: //teethLower_modPath
            MOD4.MODL.Copy(FieldValue);
            break;
        case 71: //teethLower_iconPath
            MOD4.ICON.Copy(FieldValue);
            break;
        case 73: //teethUpper_modPath
            MOD5.MODL.Copy(FieldValue);
            break;
        case 75: //teethUpper_iconPath
            MOD5.ICON.Copy(FieldValue);
            break;
        case 77: //tongue_modPath
            MOD6.MODL.Copy(FieldValue);
            break;
        case 79: //tongue_iconPath
            MOD6.ICON.Copy(FieldValue);
            break;
        case 81: //leftEye_modPath
            MOD7.MODL.Copy(FieldValue);
            break;
        case 83: //leftEye_iconPath
            MOD7.ICON.Copy(FieldValue);
            break;
        case 85: //rightEye_modPath
            MOD8.MODL.Copy(FieldValue);
            break;
        case 87: //rightEye_iconPath
            MOD8.ICON.Copy(FieldValue);
            break;
        case 89: //maleTailModelPath
            MMODL.MODL.Copy(FieldValue);
            break;
        case 92: //maleUpperBodyPath
            MICON0.Copy(FieldValue);
            break;
        case 93: //maleLowerBodyPath
            MICON1.Copy(FieldValue);
            break;
        case 94: //maleHandPath
            MICON2.Copy(FieldValue);
            break;
        case 95: //maleFootPath
            MICON3.Copy(FieldValue);
            break;
        case 96: //maleTailPath
            MICON4.Copy(FieldValue);
            break;
        case 97: //femaleTailModelPath
            FMODL.MODL.Copy(FieldValue);
            break;
        case 100: //femaleUpperBodyPath
            FICON0.Copy(FieldValue);
            break;
        case 101: //femaleLowerBodyPath
            FICON1.Copy(FieldValue);
            break;
        case 102: //femaleHandPath
            FICON2.Copy(FieldValue);
            break;
        case 103: //femaleFootPath
            FICON3.Copy(FieldValue);
            break;
        case 104: //femaleTailPath
            FICON4.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void RACERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //spells
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
        case 105: //hairs
            HNAM.clear();
            if(nSize)
                {
                HNAM.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    HNAM[x] = FieldValue[x];
                    FormIDHandler.AddMaster(HNAM[x]);
                    }
                }
            break;
        case 106: //eyes
            ENAM.clear();
            if(nSize)
                {
                ENAM.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    ENAM[x] = FieldValue[x];
                    FormIDHandler.AddMaster(ENAM[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

void RACERecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    switch(subField)
        {
        case 9: //relations
            if(listIndex >= XNAM.size())
                return;
            switch(listField)
                {
                case 2: //mod
                    XNAM[listIndex]->value.mod = FieldValue;
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

void RACERecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 9: //relations
            if(listIndex >= XNAM.size())
                return;
            switch(listField)
                {
                case 1: //faction
                    XNAM[listIndex]->value.faction = FieldValue;
                    FormIDHandler.AddMaster(XNAM[listIndex]->value.faction);
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

void RACERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue)
    {
    switch(Field)
        {
        case 10: //skill1
            DATA.value.skills[0].value = FieldValue;
            break;
        case 11: //skill1Boost
            DATA.value.skills[0].boost = FieldValue;
            break;
        case 12: //skill2
            DATA.value.skills[1].value = FieldValue;
            break;
        case 13: //skill2Boost
            DATA.value.skills[1].boost = FieldValue;
            break;
        case 14: //skill3
            DATA.value.skills[2].value = FieldValue;
            break;
        case 15: //skill3Boost
            DATA.value.skills[2].boost = FieldValue;
            break;
        case 16: //skill4
            DATA.value.skills[3].value = FieldValue;
            break;
        case 17: //skill4Boost
            DATA.value.skills[3].boost = FieldValue;
            break;
        case 18: //skill5
            DATA.value.skills[4].value = FieldValue;
            break;
        case 19: //skill5Boost
            DATA.value.skills[4].boost = FieldValue;
            break;
        case 20: //skill6
            DATA.value.skills[5].value = FieldValue;
            break;
        case 21: //skill6Boost
            DATA.value.skills[5].boost = FieldValue;
            break;
        case 22: //skill7
            DATA.value.skills[6].value = FieldValue;
            break;
        case 23: //skill7Boost
            DATA.value.skills[6].boost = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void RACERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 24: //unused1
            if(nSize != 2)
                return;
            DATA.value.unused1[0] = FieldValue[0];
            DATA.value.unused1[1] = FieldValue[1];
            break;
        case 56: //head_modt_p
            MOD0.MODT.Copy(FieldValue, nSize);
            break;
        case 60: //maleEars_modt_p
            MOD1.MODT.Copy(FieldValue, nSize);
            break;
        case 64: //femaleEars_modt_p
            MOD2.MODT.Copy(FieldValue, nSize);
            break;
        case 68: //mouth_modt_p
            MOD3.MODT.Copy(FieldValue, nSize);
            break;
        case 72: //teethLower_modt_p
            MOD4.MODT.Copy(FieldValue, nSize);
            break;
        case 76: //teethUpper_modt_p
            MOD5.MODT.Copy(FieldValue, nSize);
            break;
        case 80: //tongue_modt_p
            MOD6.MODT.Copy(FieldValue, nSize);
            break;
        case 84: //leftEye_modt_p
            MOD7.MODT.Copy(FieldValue, nSize);
            break;
        case 88: //rightEye_modt_p
            MOD8.MODT.Copy(FieldValue, nSize);
            break;
        case 91: //maleTailModel_t_p
            MMODL.MODT.Copy(FieldValue, nSize);
            break;
        case 99: //femaleTailModel_t_p
            FMODL.MODT.Copy(FieldValue, nSize);
            break;
        case 107: //fggs_p
            if(nSize != 200)
                return;
            FGGS.Copy(FieldValue, nSize);
            break;
        case 108: //fgga_p
            if(nSize != 120)
                return;
            FGGS.Copy(FieldValue, nSize);
            break;
        case 109: //fgts_p
            if(nSize != 200)
                return;
            FGTS.Copy(FieldValue, nSize);
            break;
        case 110: //snam_p
            if(nSize != 2)
                return;
            SNAM.value.SNAM[0] = FieldValue[0];
            SNAM.value.SNAM[1] = FieldValue[1];
            break;
        default:
            return;
        }
    return;
    }

void RACERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 25: //maleHeight
            DATA.value.maleHeight = FieldValue;
            break;
        case 26: //femaleHeight
            DATA.value.femaleHeight = FieldValue;
            break;
        case 27: //maleWeight
            DATA.value.maleWeight = FieldValue;
            break;
        case 28: //femaleWeight
            DATA.value.femaleWeight = FieldValue;
            break;
        case 35: //mainClamp
            PNAM.value.mainClamp = FieldValue;
            PNAM.isLoaded = true;
            break;
        case 36: //faceClamp
            UNAM.value.faceClamp = FieldValue;
            UNAM.isLoaded = true;
            break;
        case 54: //head_modb
            MOD0.MODB.value.MODB = FieldValue;
            MOD0.MODB.isLoaded = true;
            break;
        case 58: //maleEars_modb
            MOD1.MODB.value.MODB = FieldValue;
            MOD1.MODB.isLoaded = true;
            break;
        case 62: //femaleEars_modb
            MOD2.MODB.value.MODB = FieldValue;
            MOD2.MODB.isLoaded = true;
            break;
        case 66: //mouth_modb
            MOD3.MODB.value.MODB = FieldValue;
            MOD3.MODB.isLoaded = true;
            break;
        case 70: //teethLower_modb
            MOD4.MODB.value.MODB = FieldValue;
            MOD4.MODB.isLoaded = true;
            break;
        case 74: //teethUpper_modb
            MOD5.MODB.value.MODB = FieldValue;
            MOD5.MODB.isLoaded = true;
            break;
        case 78: //tongue_modb
            MOD6.MODB.value.MODB = FieldValue;
            MOD6.MODB.isLoaded = true;
            break;
        case 82: //leftEye_modb
            MOD7.MODB.value.MODB = FieldValue;
            MOD7.MODB.isLoaded = true;
            break;
        case 86: //rightEye_modb
            MOD8.MODB.value.MODB = FieldValue;
            MOD8.MODB.isLoaded = true;
            break;
        case 90: //maleTailModel_b
            MMODL.MODB.value.MODB = FieldValue;
            MMODL.MODB.isLoaded = true;
            break;
        case 98: //femaleTailModel_b
            FMODL.MODB.value.MODB = FieldValue;
            FMODL.MODB.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void RACERecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 29: //flags
            DATA.value.flags = FieldValue;
            break;
        case 30: //maleVoice
            if(FieldValue == formID)
                VNAM.value.maleVoice = 0;
            else
                VNAM.value.maleVoice = FieldValue;
            VNAM.isLoaded = true;
            FormIDHandler.AddMaster(VNAM.value.maleVoice);
            break;
        case 31: //femaleVoice
            if(FieldValue == formID)
                VNAM.value.femaleVoice = 0;
            else
                VNAM.value.femaleVoice = FieldValue;
            VNAM.isLoaded = true;
            FormIDHandler.AddMaster(VNAM.value.femaleVoice);
            break;
        case 32: //defaultHairMale
            DNAM.value.defaultHairMale = FieldValue;
            DNAM.isLoaded = true;
            FormIDHandler.AddMaster(DNAM.value.defaultHairMale);
            break;
        case 33: //defaultHairFemale
            DNAM.value.defaultHairFemale = FieldValue;
            DNAM.isLoaded = true;
            FormIDHandler.AddMaster(DNAM.value.defaultHairFemale);
            break;
        default:
            return;
        }
    return;
    }

void RACERecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 34: //defaultHairColor
            CNAM.value.defaultHairColor = FieldValue;
            break;
        case 37: //maleStrength
            ATTR.value.maleStrength = FieldValue;
            break;
        case 38: //maleIntelligence
            ATTR.value.maleIntelligence = FieldValue;
            break;
        case 39: //maleWillpower
            ATTR.value.maleWillpower = FieldValue;
            break;
        case 40: //maleAgility
            ATTR.value.maleAgility = FieldValue;
            break;
        case 41: //maleSpeed
            ATTR.value.maleSpeed = FieldValue;
            break;
        case 42: //maleEndurance
            ATTR.value.maleEndurance = FieldValue;
            break;
        case 43: //malePersonality
            ATTR.value.malePersonality = FieldValue;
            break;
        case 44: //maleLuck
            ATTR.value.maleLuck = FieldValue;
            break;
        case 45: //femaleStrength
            ATTR.value.femaleStrength = FieldValue;
            break;
        case 46: //femaleIntelligence
            ATTR.value.femaleIntelligence = FieldValue;
            break;
        case 47: //femaleWillpower
            ATTR.value.femaleWillpower = FieldValue;
            break;
        case 48: //femaleAgility
            ATTR.value.femaleAgility = FieldValue;
            break;
        case 49: //femaleSpeed
            ATTR.value.femaleSpeed = FieldValue;
            break;
        case 50: //femaleEndurance
            ATTR.value.femaleEndurance = FieldValue;
            break;
        case 51: //femalePersonality
            ATTR.value.femalePersonality = FieldValue;
            break;
        case 52: //femaleLuck
            ATTR.value.femaleLuck = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

