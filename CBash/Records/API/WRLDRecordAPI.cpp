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
#include "..\WRLDRecord.h"

signed long WRLDRecord::GetOtherFieldType(const unsigned long Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //parent
            return FID_FIELD;
        case 8: //climate
            return FID_FIELD;
        case 9: //water
            return FID_FIELD;
        case 10: //mapPath
            return STRING_FIELD;
        case 11: //dimX
            return INT_FIELD;
        case 12: //dimY
            return INT_FIELD;
        case 13: //NWCellX
            return SHORT_FIELD;
        case 14: //NWCellY
            return SHORT_FIELD;
        case 15: //SECellX
            return SHORT_FIELD;
        case 16: //SECellY
            return SHORT_FIELD;
        case 17: //flags
            return UBYTE_FIELD;
        case 18: //unknown00
            return FLOAT_FIELD;
        case 19: //unknown01
            return FLOAT_FIELD;
        case 20: //unknown90
            return FLOAT_FIELD;
        case 21: //unknown91
            return FLOAT_FIELD;
        case 22: //soundType
            return UINT_FIELD;
        case 23: //ofst_p
            return BYTES_FIELD;
        case 24: //ROAD
            return SUBRECORD_FIELD;
        case 25: //CELL
            return SUBRECORD_FIELD;
        case 26: //CELLS
            return SUBRECORDS_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * WRLDRecord::GetOtherField(const unsigned long Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //parent
            if(WNAM.IsLoaded())
                return &WNAM->fid;
            return NULL;
        case 8: //climate
            if(CNAM.IsLoaded())
                return &CNAM->fid;
            return NULL;
        case 9: //water
            if(NAM2.IsLoaded())
                return &NAM2->fid;
            return NULL;
        case 10: //mapPath
            return ICON.value;
        case 11: //dimX
            if(MNAM.IsLoaded())
                return &MNAM->dimX;
            return NULL;
        case 12: //dimY
            if(MNAM.IsLoaded())
                return &MNAM->dimY;
            return NULL;
        case 13: //NWCellX
            if(MNAM.IsLoaded())
                return &MNAM->NWCellX;
            return NULL;
        case 14: //NWCellY
            if(MNAM.IsLoaded())
                return &MNAM->NWCellY;
            return NULL;
        case 15: //SECellX
            if(MNAM.IsLoaded())
                return &MNAM->SECellX;
            return NULL;
        case 16: //SECellY
            if(MNAM.IsLoaded())
                return &MNAM->SECellY;
            return NULL;
        case 17: //flags
            return &DATA.value.flags;
        case 18: //unknown00
            return &NAM0.value.unk1;
        case 19: //unknown01
            return &NAM0.value.unk2;
        case 20: //unknown90
            return &NAM9.value.unk1;
        case 21: //unknown91
            return &NAM9.value.unk2;
        case 22: //soundType
            if(SNAM.IsLoaded())
                return &SNAM->flags;
            return NULL;
        case 24: //ROAD
            if(ROAD != NULL)
                return &ROAD->formID;
            return NULL;
        case 25: //CELL
            if(CELL != NULL)
                return &CELL->formID;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned long WRLDRecord::GetFieldArraySize(const unsigned long Field)
    {
    switch(Field)
        {
        case 23: //ofst_p
            return OFST.size;
        case 26: //CELLS
            return (unsigned long)CELLS.size();
        default:
            return 0;
        }
    }

void WRLDRecord::GetFieldArray(const unsigned long Field, void **FieldValues)
    {
    switch(Field)
        {
        case 23: //ofst_p
            *FieldValues = OFST.value;
            return;
        case 26: //CELLS
            for(unsigned long p = 0;p < CELLS.size();p++)
                FieldValues[p] = &CELLS[p]->formID;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void WRLDRecord::SetField(const unsigned long Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 10: //mapPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void WRLDRecord::SetOtherField(const unsigned long Field, unsigned long FieldValue)
    {
    switch(Field)
        {
        case 7: //parent
            WNAM.Load();
            WNAM->fid = FieldValue;
            break;
        case 8: //climate
            CNAM.Load();
            CNAM->fid = FieldValue;
            break;
        case 9: //water
            NAM2.Load();
            NAM2->fid = FieldValue;
            break;
        case 22: //soundType
            SNAM.Load();
            SNAM->flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WRLDRecord::SetField(const unsigned long Field, signed long FieldValue)
    {
    switch(Field)
        {
        case 11: //dimX
            MNAM.Load();
            MNAM->dimX = FieldValue;
            break;
        case 12: //dimY
            MNAM.Load();
            MNAM->dimY = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WRLDRecord::SetField(const unsigned long Field, short FieldValue)
    {
    switch(Field)
        {
        case 13: //NWCellX
            MNAM.Load();
            MNAM->NWCellX = FieldValue;
            break;
        case 14: //NWCellY
            MNAM.Load();
            MNAM->NWCellY = FieldValue;
            break;
        case 15: //SECellX
            MNAM.Load();
            MNAM->SECellX = FieldValue;
            break;
        case 16: //SECellY
            MNAM.Load();
            MNAM->SECellY = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WRLDRecord::SetField(const unsigned long Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 17: //flags
            DATA.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WRLDRecord::SetField(const unsigned long Field, float FieldValue)
    {
    switch(Field)
        {
        case 18: //unknown00
            NAM0.value.unk1 = FieldValue;
            break;
        case 19: //unknown01
            NAM0.value.unk2 = FieldValue;
            break;
        case 20: //unknown90
            NAM9.value.unk1 = FieldValue;
            break;
        case 21: //unknown91
            NAM9.value.unk2 = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void WRLDRecord::SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize)
    {
    switch(Field)
        {
        case 23: //ofst_p
            OFST.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

signed long WRLDRecord::DeleteField(const unsigned long Field)
    {
    WRLDMNAM defaultMNAM;
    WRLDUNK defaultUNK;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //parent
            WNAM.Unload();
            break;
        case 8: //climate
            CNAM.Unload();
            break;
        case 9: //water
            NAM2.Unload();
            break;
        case 10: //mapPath
            ICON.Unload();
            break;
        case 11: //dimX
            if(MNAM.IsLoaded())
                MNAM->dimX = defaultMNAM.dimX;
            break;
        case 12: //dimY
            if(MNAM.IsLoaded())
                MNAM->dimY = defaultMNAM.dimY;
            break;
        case 13: //NWCellX
            if(MNAM.IsLoaded())
                MNAM->NWCellX = defaultMNAM.NWCellX;
            break;
        case 14: //NWCellY
            if(MNAM.IsLoaded())
                MNAM->NWCellY = defaultMNAM.NWCellY;
            break;
        case 15: //SECellX
            if(MNAM.IsLoaded())
                MNAM->SECellX = defaultMNAM.SECellX;
            break;
        case 16: //SECellY
            if(MNAM.IsLoaded())
                MNAM->SECellY = defaultMNAM.SECellY;
            break;
        case 17: //flags
            DATA.Unload();
            break;
        case 18: //unknown00
            NAM0.value.unk1 = defaultUNK.unk1;
            break;
        case 19: //unknown01
            NAM0.value.unk2 = defaultUNK.unk2;
            break;
        case 20: //unknown90
            NAM9.value.unk1 = defaultUNK.unk1;
            break;
        case 21: //unknown91
            NAM9.value.unk2 = defaultUNK.unk2;
            break;
        case 22: //soundType
            SNAM.Unload();
            break;
        case 23: //ofst_p
            OFST.Unload();
            break;
        default:
            return 0;
        }
    return 1;
    }
