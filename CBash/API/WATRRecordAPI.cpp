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
#include "..\Records\WATRRecord.h"

int WATRRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //texture
            return STRING_FIELD;
        case 7: //opacity
            return UBYTE_FIELD;
        case 8: //flags
            return UBYTE_FIELD;
        case 9: //material
            return STRING_FIELD;
        case 10: //sound
            return FID_FIELD;
        case 11: //windVelocity
            return FLOAT_FIELD;
        case 12: //windDirection
            return FLOAT_FIELD;
        case 13: //waveAmp
            return FLOAT_FIELD;
        case 14: //waveFreq
            return FLOAT_FIELD;
        case 15: //sunPower
            return FLOAT_FIELD;
        case 16: //reflectAmt
            return FLOAT_FIELD;
        case 17: //fresnelAmt
            return FLOAT_FIELD;
        case 18: //xSpeed
            return FLOAT_FIELD;
        case 19: //ySpeed
            return FLOAT_FIELD;
        case 20: //fogNear
            return FLOAT_FIELD;
        case 21: //fogFar
            return FLOAT_FIELD;
        case 22: //shallow.red
            return UBYTE_FIELD;
        case 23: //shallow.green
            return UBYTE_FIELD;
        case 24: //shallow.blue
            return UBYTE_FIELD;
        case 25: //shallow.unused1
            return BYTES_FIELD;
        case 26: //deep.red
            return UBYTE_FIELD;
        case 27: //deep.green
            return UBYTE_FIELD;
        case 28: //deep.blue
            return UBYTE_FIELD;
        case 29: //deep.unused1
            return BYTES_FIELD;
        case 30: //refl.red
            return UBYTE_FIELD;
        case 31: //refl.green
            return UBYTE_FIELD;
        case 32: //refl.blue
            return UBYTE_FIELD;
        case 33: //refl.unused1
            return BYTES_FIELD;
        case 34: //blend
            return UBYTE_FIELD;
        case 35: //unused1
            return BYTES_FIELD;
        case 36: //rainForce
            return FLOAT_FIELD;
        case 37: //rainVelocity
            return FLOAT_FIELD;
        case 38: //rainFalloff
            return FLOAT_FIELD;
        case 39: //rainDampner
            return FLOAT_FIELD;
        case 40: //rainSize
            return FLOAT_FIELD;
        case 41: //dispForce
            return FLOAT_FIELD;
        case 42: //dispVelocity
            return FLOAT_FIELD;
        case 43: //dispFalloff
            return FLOAT_FIELD;
        case 44: //dispDampner
            return FLOAT_FIELD;
        case 45: //dispSize
            return FLOAT_FIELD;
        case 46: //damage
            return USHORT_FIELD;
        case 47: //dayWater
            return FID_FIELD;
        case 48: //nightWater
            return FID_FIELD;
        case 49: //underWater
            return FID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * WATRRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //texture
            return TNAM.value;
        case 7: //opacity
            return &ANAM.value.opacity;
        case 8: //flags
            return &FNAM.value.flags;
        case 9: //material
            return MNAM.value;
        case 10: //sound
            if(SNAM.IsLoaded())
                return &SNAM->fid;
            return NULL;
        case 11: //windVelocity
            if(DATA.IsLoaded())
                return &DATA->windVelocity;
            return NULL;
        case 12: //windDirection
            if(DATA.IsLoaded())
                return &DATA->windDirection;
            return NULL;
        case 13: //waveAmp
            if(DATA.IsLoaded())
                return &DATA->waveAmp;
            return NULL;
        case 14: //waveFreq
            if(DATA.IsLoaded())
                return &DATA->waveFreq;
            return NULL;
        case 15: //sunPower
            if(DATA.IsLoaded())
                return &DATA->sunPower;
            return NULL;
        case 16: //reflectAmt
            if(DATA.IsLoaded())
                return &DATA->reflectAmt;
            return NULL;
        case 17: //fresnelAmt
            if(DATA.IsLoaded())
                return &DATA->fresnelAmt;
            return NULL;
        case 18: //xSpeed
            if(DATA.IsLoaded())
                return &DATA->xSpeed;
            return NULL;
        case 19: //ySpeed
            if(DATA.IsLoaded())
                return &DATA->ySpeed;
            return NULL;
        case 20: //fogNear
            if(DATA.IsLoaded())
                return &DATA->fogNear;
            return NULL;
        case 21: //fogFar
            if(DATA.IsLoaded())
                return &DATA->fogFar;
            return NULL;
        case 22: //shallow.red
            if(DATA.IsLoaded())
                return &DATA->shallow.red;
            return NULL;
        case 23: //shallow.green
            if(DATA.IsLoaded())
                return &DATA->shallow.green;
            return NULL;
        case 24: //shallow.blue
            if(DATA.IsLoaded())
                return &DATA->shallow.blue;
            return NULL;
        case 26: //deep.red
            if(DATA.IsLoaded())
                return &DATA->deep.red;
            return NULL;
        case 27: //deep.green
            if(DATA.IsLoaded())
                return &DATA->deep.green;
            return NULL;
        case 28: //deep.blue
            if(DATA.IsLoaded())
                return &DATA->deep.blue;
            return NULL;
        case 30: //refl.red
            if(DATA.IsLoaded())
                return &DATA->refl.red;
            return NULL;
        case 31: //refl.green
            if(DATA.IsLoaded())
                return &DATA->refl.green;
            return NULL;
        case 32: //refl.blue
            if(DATA.IsLoaded())
                return &DATA->refl.blue;
            return NULL;
        case 34: //blend
            if(DATA.IsLoaded())
                return &DATA->blend;
            return NULL;
        case 36: //rainForce
            if(DATA.IsLoaded())
                return &DATA->rainForce;
            return NULL;
        case 37: //rainVelocity
            if(DATA.IsLoaded())
                return &DATA->rainVelocity;
            return NULL;
        case 38: //rainFalloff
            if(DATA.IsLoaded())
                return &DATA->rainFalloff;
            return NULL;
        case 39: //rainDampner
            if(DATA.IsLoaded())
                return &DATA->rainDampner;
            return NULL;
        case 40: //rainSize
            if(DATA.IsLoaded())
                return &DATA->rainSize;
            return NULL;
        case 41: //dispForce
            if(DATA.IsLoaded())
                return &DATA->dispForce;
            return NULL;
        case 42: //dispVelocity
            if(DATA.IsLoaded())
                return &DATA->dispVelocity;
            return NULL;
        case 43: //dispFalloff
            if(DATA.IsLoaded())
                return &DATA->dispFalloff;
            return NULL;
        case 44: //dispDampner
            if(DATA.IsLoaded())
                return &DATA->dispDampner;
            return NULL;
        case 45: //dispSize
            if(DATA.IsLoaded())
                return &DATA->dispSize;
            return NULL;
        case 46: //damage
            if(DATA.IsLoaded())
                return &DATA->damage;
            return NULL;
        case 47: //dayWater
            if(GNAM.IsLoaded())
                return &GNAM->dayWater;
            return NULL;
        case 48: //nightWater
            if(GNAM.IsLoaded())
                return &GNAM->nightWater;
            return NULL;
        case 49: //underWater
            if(GNAM.IsLoaded())
                return &GNAM->underWater;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned int WATRRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 25: //shallow.unused1
            if(DATA.IsLoaded())
            	return 1;
            return 0;
        case 29: //deep.unused1
            if(DATA.IsLoaded())
            	return 1;
            return 0;
        case 33: //refl.unused1
            if(DATA.IsLoaded())
            	return 1;
            return 0;
        case 35: //unused1
            if(DATA.IsLoaded())
            	return 3;
            return 0;
        default:
            return 0;
        }
    }

void WATRRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 25: //shallow.unused1
            if(DATA.IsLoaded())
            	*FieldValues = &DATA->shallow.unused1;
            else
            	*FieldValues = NULL;
            return;
        case 29: //deep.unused1
            if(DATA.IsLoaded())
            	*FieldValues = &DATA->deep.unused1;
            else
            	*FieldValues = NULL;
            return;
        case 33: //refl.unused1
            if(DATA.IsLoaded())
            	*FieldValues = &DATA->refl.unused1;
            else
            	*FieldValues = NULL;
            return;
        case 35: //unused1
            if(DATA.IsLoaded())
            	*FieldValues = &DATA->unused1[0];
            else
            	*FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void WATRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //texture
            TNAM.Copy(FieldValue);
            break;
        case 9: //material
            MNAM.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void WATRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 7: //opacity
            ANAM.value.opacity = FieldValue;
            break;
        case 8: //flags
            FNAM.value.flags = FieldValue;
            break;
        case 22: //shallow.red
            DATA.Load();
            DATA->shallow.red = FieldValue;
            break;
        case 23: //shallow.green
            DATA.Load();
            DATA->shallow.green = FieldValue;
            break;
        case 24: //shallow.blue
            DATA.Load();
            DATA->shallow.blue = FieldValue;
            break;
        case 26: //deep.red
            DATA.Load();
            DATA->deep.red = FieldValue;
            break;
        case 27: //deep.green
            DATA.Load();
            DATA->deep.green = FieldValue;
            break;
        case 28: //deep.blue
            DATA.Load();
            DATA->deep.blue = FieldValue;
            break;
        case 30: //refl.red
            DATA.Load();
            DATA->refl.red = FieldValue;
            break;
        case 31: //refl.green
            DATA.Load();
            DATA->refl.green = FieldValue;
            break;
        case 32: //refl.blue
            DATA.Load();
            DATA->refl.blue = FieldValue;
            break;
        case 34: //blend
            DATA.Load();
            DATA->blend = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WATRRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 10: //sound
            SNAM.Load();
            SNAM->fid = FieldValue;
            FormIDHandler.AddMaster(SNAM->fid);
            break;
        case 47: //dayWater
            GNAM.Load();
            GNAM->dayWater = FieldValue;
            FormIDHandler.AddMaster(GNAM->dayWater);
            break;
        case 48: //nightWater
            GNAM.Load();
            GNAM->nightWater = FieldValue;
            FormIDHandler.AddMaster(GNAM->nightWater);
            break;
        case 49: //underWater
            GNAM.Load();
            GNAM->underWater = FieldValue;
            FormIDHandler.AddMaster(GNAM->underWater);
            break;
        default:
            return;
        }
    return;
    }

void WATRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 11: //windVelocity
            DATA.Load();
            DATA->windVelocity = FieldValue;
            break;
        case 12: //windDirection
            DATA.Load();
            DATA->windDirection = FieldValue;
            break;
        case 13: //waveAmp
            DATA.Load();
            DATA->waveAmp = FieldValue;
            break;
        case 14: //waveFreq
            DATA.Load();
            DATA->waveFreq = FieldValue;
            break;
        case 15: //sunPower
            DATA.Load();
            DATA->sunPower = FieldValue;
            break;
        case 16: //reflectAmt
            DATA.Load();
            DATA->reflectAmt = FieldValue;
            break;
        case 17: //fresnelAmt
            DATA.Load();
            DATA->fresnelAmt = FieldValue;
            break;
        case 18: //xSpeed
            DATA.Load();
            DATA->xSpeed = FieldValue;
            break;
        case 19: //ySpeed
            DATA.Load();
            DATA->ySpeed = FieldValue;
            break;
        case 20: //fogNear
            DATA.Load();
            DATA->fogNear = FieldValue;
            break;
        case 21: //fogFar
            DATA.Load();
            DATA->fogFar = FieldValue;
            break;
        case 36: //rainForce
            DATA.Load();
            DATA->rainForce = FieldValue;
            break;
        case 37: //rainVelocity
            DATA.Load();
            DATA->rainVelocity = FieldValue;
            break;
        case 38: //rainFalloff
            DATA.Load();
            DATA->rainFalloff = FieldValue;
            break;
        case 39: //rainDampner
            DATA.Load();
            DATA->rainDampner = FieldValue;
            break;
        case 40: //rainSize
            DATA.Load();
            DATA->rainSize = FieldValue;
            break;
        case 41: //dispForce
            DATA.Load();
            DATA->dispForce = FieldValue;
            break;
        case 42: //dispVelocity
            DATA.Load();
            DATA->dispVelocity = FieldValue;
            break;
        case 43: //dispFalloff
            DATA.Load();
            DATA->dispFalloff = FieldValue;
            break;
        case 44: //dispDampner
            DATA.Load();
            DATA->dispDampner = FieldValue;
            break;
        case 45: //dispSize
            DATA.Load();
            DATA->dispSize = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WATRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 25: //shallow.unused1
            if(nSize != 1)
                return;
            DATA.Load();
            DATA->shallow.unused1 = FieldValue[0];
            break;
        case 29: //deep.unused1
            if(nSize != 1)
                return;
            DATA.Load();
            DATA->deep.unused1 = FieldValue[0];
            break;
        case 33: //refl.unused1
            if(nSize != 1)
                return;
            DATA.Load();
            DATA->refl.unused1 = FieldValue[0];
            break;
        case 35: //unused1
            if(nSize != 3)
                return;
            DATA.Load();
            DATA->unused1[0] = FieldValue[0];
            DATA->unused1[1] = FieldValue[1];
            DATA->unused1[2] = FieldValue[2];
            break;
        default:
            return;
        }
    return;
    }

void WATRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 46: //damage
            DATA.Load();
            DATA->damage = FieldValue;
            break;
        default:
            return;
        }
    return;
    }
