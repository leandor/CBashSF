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
#include "..\Records\TREERecord.h"

int TREERecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //modPath
            return STRING_FIELD;
        case 7: //modb
            return FLOAT_FIELD;
        case 8: //modt_p
            return BYTES_FIELD;
        case 9: //iconPath
            return STRING_FIELD;
        case 10: //speedTree
            return UINTARRAY_FIELD;
        case 11: //curvature
            return FLOAT_FIELD;
        case 12: //minAngle
            return FLOAT_FIELD;
        case 13: //maxAngle
            return FLOAT_FIELD;
        case 14: //branchDim
            return FLOAT_FIELD;
        case 15: //leafDim
            return FLOAT_FIELD;
        case 16: //shadowRadius
            return INT_FIELD;
        case 17: //rockSpeed
            return FLOAT_FIELD;
        case 18: //rustleSpeed
            return FLOAT_FIELD;
        case 19: //widthBill
            return FLOAT_FIELD;
        case 20: //heightBill
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * TREERecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //modPath
            if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
                return MODL->MODL.value;
            return NULL;
        case 7: //modb
            if(MODL.IsLoaded() && MODL->MODB.IsLoaded())
                return &MODL->MODB.value.MODB;
            return NULL;
        case 9: //iconPath
            return ICON.value;
        case 11: //curvature
            return &CNAM.value.curvature;
        case 12: //minAngle
            return &CNAM.value.minAngle;
        case 13: //maxAngle
            return &CNAM.value.maxAngle;
        case 14: //branchDim
            return &CNAM.value.branchDim;
        case 15: //leafDim
            return &CNAM.value.leafDim;
        case 16: //shadowRadius
            return &CNAM.value.shadowRadius;
        case 17: //rockSpeed
            return &CNAM.value.rockSpeed;
        case 18: //rustleSpeed
            return &CNAM.value.rustleSpeed;
        case 19: //widthBill
            return &BNAM.value.widthBill;
        case 20: //heightBill
            return &BNAM.value.heightBill;
        default:
            return NULL;
        }
    }

unsigned int TREERecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        case 10: //speedTree
            return (unsigned int)SNAM.size();
        default:
            return 0;
        }
    }

void TREERecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 10: //speedTree
            *FieldValues = &SNAM[0];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void TREERecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //modPath
            MODL.Load();
            MODL->MODL.Copy(FieldValue);
            break;
        case 9: //iconPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void TREERecord::SetField(const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 7: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 11: //curvature
            CNAM.value.curvature = FieldValue;
            break;
        case 12: //minAngle
            CNAM.value.minAngle = FieldValue;
            break;
        case 13: //maxAngle
            CNAM.value.maxAngle = FieldValue;
            break;
        case 14: //branchDim
            CNAM.value.branchDim = FieldValue;
            break;
        case 15: //leafDim
            CNAM.value.leafDim = FieldValue;
            break;
        case 17: //rockSpeed
            CNAM.value.rockSpeed = FieldValue;
            break;
        case 18: //rustleSpeed
            CNAM.value.rustleSpeed = FieldValue;
            break;
        case 19: //widthBill
            BNAM.value.widthBill = FieldValue;
            break;
        case 20: //heightBill
            BNAM.value.heightBill = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void TREERecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void TREERecord::SetField(const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 10: //speedTree
            SNAM.clear();
            if(nSize)
                {
                for(unsigned int x = 0; x < nSize; x++)
                    SNAM.push_back(FieldValue[x]);
                }
            break;
        default:
            return;
        }
    return;
    }

void TREERecord::SetField(const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 16: //shadowRadius
            CNAM.value.shadowRadius = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int TREERecord::DeleteField(const unsigned int Field)
    {
    TREECNAM defaultCNAM;
    TREEBNAM defaultBNAM;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            break;
        case 7: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            break;
        case 8: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            break;
        case 9: //iconPath
            ICON.Unload();
            break;
        case 10: //speedTree
            SNAM.clear();
            break;
        case 11: //curvature
            CNAM.value.curvature = defaultCNAM.curvature;
            break;
        case 12: //minAngle
            CNAM.value.minAngle = defaultCNAM.minAngle;
            break;
        case 13: //maxAngle
            CNAM.value.maxAngle = defaultCNAM.maxAngle;
            break;
        case 14: //branchDim
            CNAM.value.branchDim = defaultCNAM.branchDim;
            break;
        case 15: //leafDim
            CNAM.value.leafDim = defaultCNAM.leafDim;
            break;
        case 16: //shadowRadius
            CNAM.value.shadowRadius = defaultCNAM.shadowRadius;
            break;
        case 17: //rockSpeed
            CNAM.value.rockSpeed = defaultCNAM.rockSpeed;
            break;
        case 18: //rustleSpeed
            CNAM.value.rustleSpeed = defaultCNAM.rustleSpeed;
            break;
        case 19: //widthBill
            BNAM.value.widthBill = defaultBNAM.widthBill;
            break;
        case 20: //heightBill
            BNAM.value.heightBill = defaultBNAM.heightBill;
            break;
        default:
            return 0;
        }
    return 1;
    }
