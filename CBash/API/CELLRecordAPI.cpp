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
#include "..\Records\CELLRecord.h"

int CELLRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //flags
            return UBYTE_FIELD;
        case 8: //ambientRed
            return UBYTE_FIELD;
        case 9: //ambientGreen
            return UBYTE_FIELD;
        case 10: //ambientBlue
            return UBYTE_FIELD;
        case 11: //unused1
            return BYTES_FIELD;
        case 12: //directionalRed
            return UBYTE_FIELD;
        case 13: //directionalGreen
            return UBYTE_FIELD;
        case 14: //directionalBlue
            return UBYTE_FIELD;
        case 15: //unused2
            return BYTES_FIELD;
        case 16: //fogRed
            return UBYTE_FIELD;
        case 17: //fogGreen
            return UBYTE_FIELD;
        case 18: //fogBlue
            return UBYTE_FIELD;
        case 19: //unused3
            return BYTES_FIELD;
        case 20: //fogNear
            return FLOAT_FIELD;
        case 21: //fogFar
            return FLOAT_FIELD;
        case 22: //directionalXY
            return INT_FIELD;
        case 23: //directionalZ
            return INT_FIELD;
        case 24: //directionalFade
            return FLOAT_FIELD;
        case 25: //fogClip
            return FLOAT_FIELD;
        case 26: //music
            return UBYTE_FIELD;
        case 27: //owner
            return FID_FIELD;
        case 28: //rank
            return INT_FIELD;
        case 29: //globalVariable
            return FID_FIELD;
        case 30: //climate
            return FID_FIELD;
        case 31: //waterHeight
            return FLOAT_FIELD;
        case 32: //regions
            return FIDARRAY_FIELD;
        case 33: //posX
            if(!IsInterior())
                return INT_FIELD;
            return UNKNOWN_FIELD;
        case 34: //posY
            if(!IsInterior())
                return INT_FIELD;
            return UNKNOWN_FIELD;
        case 35: //water
            return FID_FIELD;
        case 36: //ACHR
            return SUBRECORDS_FIELD;
        case 37: //ACRE
            return SUBRECORDS_FIELD;
        case 38: //REFR
            return SUBRECORDS_FIELD;
        case 39: //PGRD
            return SUBRECORD_FIELD;
        case 40: //LAND
            return SUBRECORD_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CELLRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //flags
            return &DATA.value.flags;
        case 8: //ambientRed
            if(XCLL.IsLoaded())
                return &XCLL->ambient.red;
            return NULL;
        case 9: //ambientGreen
            if(XCLL.IsLoaded())
                return &XCLL->ambient.green;
            return NULL;
        case 10: //ambientBlue
            if(XCLL.IsLoaded())
                return &XCLL->ambient.blue;
            return NULL;
        case 11: //unused1
            if(XCLL.IsLoaded())
                return &XCLL->ambient.unused1;
            return NULL;
        case 12: //directionalRed
            if(XCLL.IsLoaded())
                return &XCLL->directional.red;
            return NULL;
        case 13: //directionalGreen
            if(XCLL.IsLoaded())
                return &XCLL->directional.green;
            return NULL;
        case 14: //directionalBlue
            if(XCLL.IsLoaded())
                return &XCLL->directional.blue;
            return NULL;
        case 15: //unused2
            if(XCLL.IsLoaded())
                return &XCLL->directional.unused1;
            return NULL;
        case 16: //fogRed
            if(XCLL.IsLoaded())
                return &XCLL->fog.red;
            return NULL;
        case 17: //fogGreen
            if(XCLL.IsLoaded())
                return &XCLL->fog.green;
            return NULL;
        case 18: //fogBlue
            if(XCLL.IsLoaded())
                return &XCLL->fog.blue;
            return NULL;
        case 19: //unused3
            if(XCLL.IsLoaded())
                return &XCLL->fog.unused1;
            return NULL;
        case 20: //fogNear
            if(XCLL.IsLoaded())
                return &XCLL->fogNear;
            return NULL;
        case 21: //fogFar
            if(XCLL.IsLoaded())
                return &XCLL->fogFar;
            return NULL;
        case 22: //directionalXY
            if(XCLL.IsLoaded())
                return &XCLL->directionalXY;
            return NULL;
        case 23: //directionalZ
            if(XCLL.IsLoaded())
                return &XCLL->directionalZ;
            return NULL;
        case 24: //directionalFade
            if(XCLL.IsLoaded())
                return &XCLL->directionalFade;
            return NULL;
        case 25: //fogClip
            if(XCLL.IsLoaded())
                return &XCLL->fogClip;
            return NULL;
        case 26: //music
            return &XCMT.value.flags;
        case 27: //owner
            if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
                return &Ownership->XOWN.value.fid;
            return NULL;
        case 28: //rank
            if(Ownership.IsLoaded() && Ownership->XRNK.IsLoaded())
                return &Ownership->XRNK->rank;
            return NULL;
        case 29: //globalVariable
            if(Ownership.IsLoaded() && Ownership->XGLB.IsLoaded())
                return &Ownership->XGLB->fid;
            return NULL;
        case 30: //climate
            return &XCCM.value.fid;
        case 31: //waterHeight
            return &XCLW.value.waterHeight;
        case 33: //posX
            if(!IsInterior())
                return &XCLC.value.posX;
            else
                return NULL;
        case 34: //posY
            if(!IsInterior())
                return &XCLC.value.posY;
            else
                return NULL;
        case 35: //water
            return &XCWT.value.fid;
        case 39: //PGRD
            if(PGRD != NULL)
                return &PGRD->formID;
            return NULL;
        case 40: //LAND
            if(LAND != NULL)
                return &LAND->formID;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned int CELLRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 11: //unused1
            if(XCLL.IsLoaded())
                return 1;
            return 0;
        case 15: //unused2
            if(XCLL.IsLoaded())
                return 1;
            return 0;
        case 19: //unused3
            if(XCLL.IsLoaded())
                return 1;
            return 0;
        case 36: //ACHR
            return (unsigned int)ACHR.size();
        case 37: //ACRE
            return (unsigned int)ACRE.size();
        case 38: //REFR
            return (unsigned int)REFR.size();
        default:
            return 0;
        }
    }

void CELLRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 11: //unused1
            if(XCLL.IsLoaded())
                *FieldValues = &XCLL->ambient.unused1;
            else
                *FieldValues = NULL;
            return;
        case 15: //unused2
            if(XCLL.IsLoaded())
                *FieldValues = &XCLL->directional.unused1;
            else
                *FieldValues = NULL;
            return;
        case 19: //unused3
            if(XCLL.IsLoaded())
                *FieldValues = &XCLL->fog.unused1;
            else
                *FieldValues = NULL;
            return;
        case 32: //regions
            for(unsigned int p = 0;p < XCLR.size();p++)
                FieldValues[p] = &XCLR[p];
            return;
        case 36: //ACHR
            for(unsigned int p = 0;p < ACHR.size();p++)
                FieldValues[p] = &ACHR[p]->formID;
            return;
        case 37: //ACRE
            for(unsigned int p = 0;p < ACRE.size();p++)
                FieldValues[p] = &ACRE[p]->formID;
            return;
        case 38: //REFR
            for(unsigned int p = 0;p < REFR.size();p++)
                FieldValues[p] = &REFR[p]->formID;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void CELLRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void CELLRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 7: //flags
            DATA.value.flags = FieldValue;
            break;
        case 8: //ambientRed
            XCLL.Load();
            XCLL->ambient.red = FieldValue;
            break;
        case 9: //ambientGreen
            XCLL.Load();
            XCLL->ambient.green = FieldValue;
            break;
        case 10: //ambientBlue
            XCLL.Load();
            XCLL->ambient.blue = FieldValue;
            break;
        case 12: //directionalRed
            XCLL.Load();
            XCLL->directional.red = FieldValue;
            break;
        case 13: //directionalGreen
            XCLL.Load();
            XCLL->directional.green = FieldValue;
            break;
        case 14: //directionalBlue
            XCLL.Load();
            XCLL->directional.blue = FieldValue;
            break;
        case 16: //fogRed
            XCLL.Load();
            XCLL->fog.red = FieldValue;
            break;
        case 17: //fogGreen
            XCLL.Load();
            XCLL->fog.green = FieldValue;
            break;
        case 18: //fogBlue
            XCLL.Load();
            XCLL->fog.blue = FieldValue;
            break;
        case 26: //music
            XCMT.value.flags = FieldValue;
            XCMT.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void CELLRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 11: //unused1
            if(nSize != 1)
                return;
            XCLL.Load();
            XCLL->ambient.unused1 = FieldValue[0];
            break;
        case 15: //unused2
            if(nSize != 1)
                return;
            XCLL.Load();
            XCLL->directional.unused1 = FieldValue[0];
            break;
        case 19: //unused3
            if(nSize != 1)
                return;
            XCLL.Load();
            XCLL->fog.unused1 = FieldValue[0];
            break;
        default:
            return;
        }
    return;
    }

void CELLRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 20: //fogNear
            XCLL.Load();
            XCLL->fogNear = FieldValue;
            break;
        case 21: //fogFar
            XCLL.Load();
            XCLL->fogFar = FieldValue;
            break;
        case 24: //directionalFade
            XCLL.Load();
            XCLL->directionalFade = FieldValue;
            break;
        case 25: //fogClip
            XCLL.Load();
            XCLL->fogClip = FieldValue;
            break;
        case 31: //waterHeight
            XCLW.value.waterHeight = FieldValue;
            XCLW.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void CELLRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 22: //directionalXY
            XCLL.Load();
            XCLL->directionalXY = FieldValue;
            break;
        case 23: //directionalZ
            XCLL.Load();
            XCLL->directionalZ = FieldValue;
            break;
        case 28: //rank
            Ownership.Load();
            Ownership->XRNK.Load();
            Ownership->XRNK->rank = FieldValue;
            break;
        case 33: //posX
            if(IsInterior())
                return;
            XCLC.value.posX = FieldValue;
            XCLC.isLoaded = true;
            break;
        case 34: //posY
            if(IsInterior())
                return;
            XCLC.value.posY = FieldValue;
            XCLC.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void CELLRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 27: //owner
            Ownership.Load();
            Ownership->XOWN.value.fid = FieldValue;
            FormIDHandler.AddMaster(Ownership->XOWN.value.fid);
            break;
        case 29: //globalVariable
            Ownership.Load();
            Ownership->XGLB.Load();
            Ownership->XGLB->fid = FieldValue;
            FormIDHandler.AddMaster(Ownership->XGLB->fid);
            break;
        case 30: //climate
            XCCM.value.fid = FieldValue;
            XCCM.isLoaded = true;
            FormIDHandler.AddMaster(XCCM.value.fid);
            break;
        case 35: //water
            XCWT.value.fid = FieldValue;
            XCWT.isLoaded = true;
            FormIDHandler.AddMaster(XCWT.value.fid);
            break;
        default:
            return;
        }
    return;
    }

void CELLRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 32: //regions
            XCLR.clear();
            if(nSize)
                {
                XCLR.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    XCLR[x] = FieldValue[x];
                    FormIDHandler.AddMaster(XCLR[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }
