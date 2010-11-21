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
#include "..\..\Common.h"
#include "..\MGEFRecord.h"

signed long MGEFRecord::GetOtherFieldType(const unsigned long Field)
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
            return UINT_FIELD;
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
        //OBME Fields
        case 30: //recordVersion
            return UBYTE_FIELD;
        case 31: //betaVersion
            return UBYTE_FIELD;
        case 32: //minorVersion
            return UBYTE_FIELD;
        case 33: //majorVersion
            return UBYTE_FIELD;
        case 34: //mgefParamAInfo
            return UBYTE_FIELD;
        case 35: //mgefParamBInfo
            return UBYTE_FIELD;
        case 36: //reserved1
            return BYTES_FIELD;
        case 37: //handlerCode
            return UINT_FIELD;
        case 38: //mgefFlagOverrides
            return UINT_FIELD;
        case 39: //mgefParamB
            return UINT_FIELD;
        case 40: //reserved2
            return BYTES_FIELD;
        case 41: //mgefCode
            return UINT_FIELD;
        case 42: //datx_p
            return BYTES_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * MGEFRecord::GetOtherField(const unsigned long Field)
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
        case 9: //modPath
            if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
                return MODL->MODL.value;
            return NULL;
        case 10: //modb
            if(MODL.IsLoaded() && MODL->MODB.IsLoaded())
                return &MODL->MODB.value.MODB;
            return NULL;
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
        //OBME Fields
        case 30: //recordVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.recordVersion;
            return NULL;
        case 31: //betaVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.betaVersion;
            return NULL;
        case 32: //minorVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.minorVersion;
            return NULL;
        case 33: //majorVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.majorVersion;
            return NULL;
        case 34: //mgefParamAInfo
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.mgefParamAInfo;
            return NULL;
        case 35: //mgefParamBInfo
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.mgefParamBInfo;
            return NULL;
        case 37: //handlerCode
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.handlerCode;
            return NULL;
        case 38: //mgefFlagOverrides
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.mgefFlagOverrides;
            return NULL;
        case 39: //mgefParamB
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.mgefParamB;
            return NULL;
        case 41: //mgefCode
            if(OBME.IsLoaded() && OBME->EDDX.IsLoaded())
                return &OBME->EDDX.value.mgefCode;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned long MGEFRecord::GetFieldArraySize(const unsigned long Field)
    {
    switch(Field)
        {
        case 11: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        case 18: //unused1
            return 2;
        case 29: //counterEffects
            return (unsigned long)ESCE.size();
        //OBME Fields
        case 36: //reserved1
            return 0x2;
        case 40: //reserved2
            return 0x1C;
        case 42: //datx_p
            return 0x20;
        default:
            return 0;
        }
    }

void MGEFRecord::GetFieldArray(const unsigned long Field, void **FieldValues)
    {
    switch(Field)
        {
        case 11: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 18: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return;
        case 29: //counterEffects
            *FieldValues = &ESCE[0];
            //for(unsigned long p = 0;p < ESCE.size();p++)
            //    FieldValues[p] = &ESCE[p];
            return;

        //OBME Fields
        case 36: //reserved1
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                *FieldValues = &OBME->OBME.value.reserved1[0];
            else
                *FieldValues = NULL;
            return;
        case 40: //reserved2
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                *FieldValues = &OBME->OBME.value.reserved2[0];
            else
                *FieldValues = NULL;
            return;
        case 42: //datx_p
            if(OBME.IsLoaded() && OBME->DATX.IsLoaded())
                *FieldValues = OBME->DATX.value;
            else
                *FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void MGEFRecord::SetField(const unsigned long Field, char *FieldValue)
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
        case 9: //modPath
            MODL.Load();
            MODL->MODL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(const unsigned long Field, float FieldValue)
    {
    switch(Field)
        {
        case 10: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
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

void MGEFRecord::SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize)
    {
    switch(Field)
        {
        case 11: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        case 18: //unused1
            if(nSize != 2)
                return;
            DATA.value.unused1[0] = FieldValue[0];
            DATA.value.unused1[1] = FieldValue[1];
            break;
        //OBME Fields
        case 36: //reserved1
            if(nSize != 0x2)
                return;
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.reserved1[0] = FieldValue[0];
            OBME->OBME.value.reserved1[1] = FieldValue[1];
            break;
        case 40: //reserved2
            if(nSize != 0x1C)
                return;
            OBME.Load();
            OBME->OBME.Load();
            memcpy(&OBME->OBME.value.reserved2[0], &FieldValue[0], 0x1C);
            break;
        case 42: //datx_p
            if(nSize != 0x20)
                return;
            OBME.Load();
            OBME->DATX.Load();
            OBME->DATX.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetOtherField(const unsigned long Field, unsigned long FieldValue)
    {
    switch(Field)
        {
        case 12: //flags
            DATA.value.flags = FieldValue;
            break;
        case 14: //associated
            DATA.value.associated = FieldValue;
            break;
        case 16: //resistValue
            DATA.value.resistValue = FieldValue;
            break;
        case 19: //light
            DATA.value.light = FieldValue;
            break;
        case 21: //effectShader
            DATA.value.effectShader = FieldValue;
            break;
        case 22: //enchantEffect
            DATA.value.enchantEffect = FieldValue;
            break;
        case 23: //castingSound
            DATA.value.castingSound = FieldValue;
            break;
        case 24: //boltSound
            DATA.value.boltSound = FieldValue;
            break;
        case 25: //hitSound
            DATA.value.hitSound = FieldValue;
            break;
        case 26: //areaSound
            DATA.value.areaSound = FieldValue;
            break;
        //OBME Fields
        case 37: //handlerCode
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.handlerCode = FieldValue;
            break;
        case 38: //mgefFlagOverrides
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.mgefFlagOverrides = FieldValue;
            break;
        case 39: //mgefParamB
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.mgefParamB = FieldValue;
            break;
        case 41: //mgefCode
            OBME.Load();
            OBME->EDDX.Load();
            OBME->EDDX.value.mgefCode = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(const unsigned long Field, signed long FieldValue)
    {
    switch(Field)
        {
        case 15: //school
            DATA.value.school = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(const unsigned long Field, unsigned short FieldValue)
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

void MGEFRecord::SetField(const unsigned long Field, unsigned long FieldValue[], unsigned long nSize)
    {
    switch(Field)
        {
        case 29: //counterEffects
            ESCE.clear();
            if(nSize)
                {
                for(unsigned long x = 0; x < nSize; x++)
                    ESCE.push_back(FieldValue[x]);
                }
            break;
        default:
            return;
        }
    return;
    }

void MGEFRecord::SetField(const unsigned long Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        //OBME Fields
        case 30: //recordVersion
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.recordVersion = FieldValue;
            break;
        case 31: //betaVersion
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.betaVersion = FieldValue;
            break;
        case 32: //minorVersion
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.minorVersion = FieldValue;
            break;
        case 33: //majorVersion
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.majorVersion = FieldValue;
            break;
        case 34: //mgefParamAInfo
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.mgefParamAInfo = FieldValue;
            break;
        case 35: //mgefParamBInfo
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.mgefParamBInfo = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

signed long MGEFRecord::DeleteField(const unsigned long Field)
    {
    MGEFDATA defaultDATA;
    MGEFOBME defaultOBME;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //text
            DESC.Unload();
            break;
        case 8: //iconPath
            ICON.Unload();
            break;
        case 9: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            break;
        case 10: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            break;
        case 11: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            break;
        case 12: //flags
            DATA.value.flags = defaultDATA.flags;
            break;
        case 13: //baseCost
            DATA.value.baseCost = defaultDATA.baseCost;
            break;
        case 14: //associated
            DATA.value.associated = defaultDATA.associated;
            break;
        case 15: //school
            DATA.value.school = defaultDATA.school;
            break;
        case 16: //resistValue
            DATA.value.resistValue = defaultDATA.resistValue;
            break;
        case 17: //unk1
            DATA.value.unk1 = defaultDATA.unk1;
            break;
        case 18: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            break;
        case 19: //light
            DATA.value.light = defaultDATA.light;
            break;
        case 20: //projectileSpeed
            DATA.value.projectileSpeed = defaultDATA.projectileSpeed;
            break;
        case 21: //effectShader
            DATA.value.effectShader = defaultDATA.effectShader;
            break;
        case 22: //enchantEffect
            DATA.value.enchantEffect = defaultDATA.enchantEffect;
            break;
        case 23: //castingSound
            DATA.value.castingSound = defaultDATA.castingSound;
            break;
        case 24: //boltSound
            DATA.value.boltSound = defaultDATA.boltSound;
            break;
        case 25: //hitSound
            DATA.value.hitSound = defaultDATA.hitSound;
            break;
        case 26: //areaSound
            DATA.value.areaSound = defaultDATA.areaSound;
            break;
        case 27: //cefEnchantment
            DATA.value.cefEnchantment = defaultDATA.cefEnchantment;
            break;
        case 28: //cefBarter
            DATA.value.cefBarter = defaultDATA.cefBarter;
            break;
        case 29: //counterEffects
            ESCE.clear();
            break;
        //OBME Fields
        case 30: //recordVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.recordVersion = defaultOBME.recordVersion;
            break;
        case 31: //betaVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.betaVersion = defaultOBME.betaVersion;
            break;
        case 32: //minorVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.minorVersion = defaultOBME.minorVersion;
            break;
        case 33: //majorVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.majorVersion = defaultOBME.majorVersion;
            break;
        case 34: //mgefParamAInfo
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.mgefParamAInfo = defaultOBME.mgefParamAInfo;
            break;
        case 35: //mgefParamBInfo
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.mgefParamBInfo = defaultOBME.mgefParamBInfo;
            break;
        case 36: //reserved1
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                {
                OBME->OBME.value.reserved1[0] = defaultOBME.reserved1[0];
                OBME->OBME.value.reserved1[1] = defaultOBME.reserved1[1];
                }
            break;
        case 37: //handlerCode
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.handlerCode = defaultOBME.handlerCode;
            break;
        case 38: //mgefFlagOverrides
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.mgefFlagOverrides = defaultOBME.mgefFlagOverrides;
            break;
        case 39: //mgefParamB
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                OBME->OBME.value.mgefParamB = defaultOBME.mgefParamB;
            break;
        case 40: //reserved2
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                memcpy(&OBME->OBME.value.reserved2[0], &defaultOBME.reserved2[0], 0x1C);
            break;
        case 41: //mgefCode
            if(OBME.IsLoaded() && OBME->EDDX.IsLoaded())
                OBME->EDDX.Unload();
            break;
        case 42: //datx_p
            if(OBME.IsLoaded() && OBME->DATX.IsLoaded())
                OBME->DATX.Unload();
            break;
        default:
            return 0;
        }
    return 1;
    }
