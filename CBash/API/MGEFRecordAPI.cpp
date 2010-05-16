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
#include "..\Records\MGEFRecord.h"

int MGEFRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //text
            return STRING_FIELD;
        case 8: //iconPath
            return STRING_FIELD;
        case 9: //modPath
            return STRING_FIELD;
        case 10: //modb
            return FLOAT_FIELD;
        case 11: //modt_p
            return BYTES_FIELD;
        case 12: //flags
            return UINT_FIELD;
        case 13: //baseCost
            return FLOAT_FIELD;
        case 14: //associated
            return FID_FIELD;
        case 15: //school
            return INT_FIELD;
        case 16: //resistValue
            return INT_FIELD;
        case 17: //unk1
            return USHORT_FIELD;
        case 18: //unused1
            return BYTES_FIELD;
        case 19: //light
            return FID_FIELD;
        case 20: //projectileSpeed
            return FLOAT_FIELD;
        case 21: //effectShader
            return FID_FIELD;
        case 22: //enchantEffect
            return FID_FIELD;
        case 23: //castingSound
            return FID_FIELD;
        case 24: //boltSound
            return FID_FIELD;
        case 25: //hitSound
            return FID_FIELD;
        case 26: //areaSound
            return FID_FIELD;
        case 27: //cefEnchantment
            return FLOAT_FIELD;
        case 28: //cefBarter
            return FLOAT_FIELD;
        case 29: //counterEffects
            return UINTARRAY_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * MGEFRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //text
            return DESC.value;
        case 8: //iconPath
            return ICON.value;
        case 9: //MODL.modPath
            return MODL.MODL.value;
        case 10: //modb
            return &MODL.MODB.value.MODB;
        case 12: //flags
            return &DATA.value.flags;
        case 13: //baseCost
            return &DATA.value.baseCost;
        case 14: //associated
            return &DATA.value.associated;
        case 15: //school
            return &DATA.value.school;
        case 16: //resistValue
            return &DATA.value.resistValue;
        case 17: //unk1
            return &DATA.value.unk1;
        case 19: //light
            return &DATA.value.light;
        case 20: //projectileSpeed
            return &DATA.value.projectileSpeed;
        case 21: //effectShader
            return &DATA.value.effectShader;
        case 22: //enchantEffect
            return &DATA.value.enchantEffect;
        case 23: //castingSound
            return &DATA.value.castingSound;
        case 24: //boltSound
            return &DATA.value.boltSound;
        case 25: //hitSound
            return &DATA.value.hitSound;
        case 26: //areaSound
            return &DATA.value.areaSound;
        case 27: //cefEnchantment
            return &DATA.value.cefEnchantment;
        case 28: //cefBarter
            return &DATA.value.cefBarter;
        default:
            return NULL;
        }
    }

unsigned int MGEFRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 11: //MODL.modt_p
            return MODL.MODT.size;
        case 18: //unused1
            return 2;
        case 29: //counterEffects
            return (unsigned int)ESCE.size();
        default:
            return 0;
        }
    }

void MGEFRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 11: //MODL.modt_p
            *FieldValues = MODL.MODT.value;
            return;
        case 18: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return;
        case 29: //counterEffects
            *FieldValues = &ESCE[0];
            //for(unsigned int p = 0;p < ESCE.size();p++)
            //    FieldValues[p] = &ESCE[p];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void MGEFRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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
        case 8: //iconPath
            ICON.Copy(FieldValue);
            break;
        case 9: //MODL.modPath
            MODL.MODL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 10: //MODL.modb
            MODL.MODB.value.MODB = FieldValue;
            MODL.MODB.isLoaded = true;
            break;
        case 13: //baseCost
            DATA.value.baseCost = FieldValue;
            break;
        case 20: //projectileSpeed
            DATA.value.projectileSpeed = FieldValue;
            break;
        case 27: //cefEnchantment
            DATA.value.cefEnchantment = FieldValue;
            break;
        case 28: //cefBarter
            DATA.value.cefBarter = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 11: //MODL.modt_p
            MODL.MODT.Copy(FieldValue, nSize);
            break;
        case 18: //unused1
            if(nSize != 2)
                return;
            DATA.value.unused1[0] = FieldValue[0];
            DATA.value.unused1[1] = FieldValue[1];
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 12: //flags
            DATA.value.flags = FieldValue;
            break;
        case 14: //associated
            DATA.value.associated = FieldValue;
            FormIDHandler.AddMaster(DATA.value.associated);
            break;
        case 19: //light
            DATA.value.light = FieldValue;
            FormIDHandler.AddMaster(DATA.value.light);
            break;
        case 21: //effectShader
            DATA.value.effectShader = FieldValue;
            FormIDHandler.AddMaster(DATA.value.effectShader);
            break;
        case 22: //enchantEffect
            DATA.value.enchantEffect = FieldValue;
            FormIDHandler.AddMaster(DATA.value.enchantEffect);
            break;
        case 23: //castingSound
            DATA.value.castingSound = FieldValue;
            FormIDHandler.AddMaster(DATA.value.castingSound);
            break;
        case 24: //boltSound
            DATA.value.boltSound = FieldValue;
            FormIDHandler.AddMaster(DATA.value.boltSound);
            break;
        case 25: //hitSound
            DATA.value.hitSound = FieldValue;
            FormIDHandler.AddMaster(DATA.value.hitSound);
            break;
        case 26: //areaSound
            DATA.value.areaSound = FieldValue;
            FormIDHandler.AddMaster(DATA.value.areaSound);
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 15: //school
            DATA.value.school = FieldValue;
            break;
        case 16: //resistValue
            DATA.value.resistValue = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 17: //unk1
            DATA.value.unk1 = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 29: //counterEffects
            ESCE.clear();
            if(nSize)
                {
                for(unsigned int x = 0; x < nSize; x++)
                    ESCE.push_back(FieldValue[x]);
                }
            break;
        default:
            return;
        }
    return;
    }
