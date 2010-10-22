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
#include "..\Records\CLMTRecord.h"

int CLMTRecord::CreateListElement(const unsigned int subField)
    {
    switch(subField)
        {
        case 6: //weathers
            Weathers.resize(Weathers.size() + 1);
            return (unsigned int)Weathers.size() - 1;
        default:
            return -1;
        }
    }

int CLMTRecord::DeleteListElement(const unsigned int subField)
    {
    switch(subField)
        {
        case 6: //weathers
            Weathers.pop_back();
            return (unsigned int)Weathers.size() - 1;
        default:
            return -1;
        }
    }

int CLMTRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //weathers
            return LIST_FIELD;
        case 7: //sunPath
            return STRING_FIELD;
        case 8: //glarePath
            return STRING_FIELD;
        case 9: //modPath
            return STRING_FIELD;
        case 10: //modb
            return FLOAT_FIELD;
        case 11: //modt_p
            return BYTES_FIELD;
        case 12: //riseBegin
            return UBYTE_FIELD;
        case 13: //riseEnd
            return UBYTE_FIELD;
        case 14: //setBegin
            return UBYTE_FIELD;
        case 15: //setEnd
            return UBYTE_FIELD;
        case 16: //volatility
            return UBYTE_FIELD;
        case 17: //phaseLength
            return UBYTE_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CLMTRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 7: //sunPath
            return FNAM.value;
        case 8: //glarePath
            return GNAM.value;
        case 9: //modPath
            if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
                return MODL->MODL.value;
            return NULL;
        case 10: //modb
            if(MODL.IsLoaded() && MODL->MODB.IsLoaded())
                return &MODL->MODB.value.MODB;
            return NULL;
        case 12: //riseBegin
            return &TNAM.value.riseBegin;
        case 13: //riseEnd
            return &TNAM.value.riseEnd;
        case 14: //setBegin
            return &TNAM.value.setBegin;
        case 15: //setEnd
            return &TNAM.value.setEnd;
        case 16: //volatility
            return &TNAM.value.volatility;
        case 17: //phaseLength
            return &TNAM.value.phaseLength;
        default:
            return NULL;
        }
    }

unsigned int CLMTRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 11: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        default:
            return 0;
        }
    }

void CLMTRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 11: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int CLMTRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 6: //weathers
            switch(listField)
                {
                case 1: //weather
                    return FID_FIELD;
                case 2: //chance
                    return INT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int CLMTRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //weathers
            return (unsigned int)Weathers.size();
        default:
            return 0;
        }
    }

void * CLMTRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 6: //weathers
            if(listIndex >= Weathers.size())
                return NULL;
            switch(listField)
                {
                case 1: //weather
                    return &Weathers[listIndex].weather;
                case 2: //chance
                    return &Weathers[listIndex].chance;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void CLMTRecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 7: //sunPath
            FNAM.Copy(FieldValue);
            break;
        case 8: //glarePath
            GNAM.Copy(FieldValue);
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

void CLMTRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 6: //weathers
            if(listIndex >= Weathers.size())
                return;
            switch(listField)
                {
                case 1: //weather
                    Weathers[listIndex].weather = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    }

void CLMTRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    switch(subField)
        {
        case 6: //weathers
            if(listIndex >= Weathers.size())
                return;
            switch(listField)
                {
                case 2: //chance
                    Weathers[listIndex].chance = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    }

void CLMTRecord::SetField(const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 10: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CLMTRecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 11: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void CLMTRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 12: //riseBegin
            TNAM.value.riseBegin = FieldValue;
            break;
        case 13: //riseEnd
            TNAM.value.riseEnd = FieldValue;
            break;
        case 14: //setBegin
            TNAM.value.setBegin = FieldValue;
            break;
        case 15: //setEnd
            TNAM.value.setEnd = FieldValue;
            break;
        case 16: //volatility
            TNAM.value.volatility = FieldValue;
            break;
        case 17: //phaseLength
            TNAM.value.phaseLength = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int CLMTRecord::DeleteField(const unsigned int Field)
    {
    CLMTTNAM defaultTNAM;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //weathers
            Weathers.clear();
            break;
        case 7: //sunPath
            FNAM.Unload();
            break;
        case 8: //glarePath
            GNAM.Unload();
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
        case 12: //riseBegin
            TNAM.value.riseBegin = defaultTNAM.riseBegin;
            break;
        case 13: //riseEnd
            TNAM.value.riseEnd = defaultTNAM.riseEnd;
            break;
        case 14: //setBegin
            TNAM.value.setBegin = defaultTNAM.setBegin;
            break;
        case 15: //setEnd
            TNAM.value.setEnd = defaultTNAM.setEnd;
            break;
        case 16: //volatility
            TNAM.value.volatility = defaultTNAM.volatility;
            break;
        case 17: //phaseLength
            TNAM.value.phaseLength = defaultTNAM.phaseLength;
            break;
        default:
            return 0;
        }
    return 1;
    }

int CLMTRecord::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    CLMTWLST defaultWLST;
    switch(subField)
        {
        case 6: //weathers
            if(listIndex >= Weathers.size())
                return 0;
            switch(listField)
                {
                case 1: //weather
                    Weathers[listIndex].weather = defaultWLST.weather;
                    break;
                case 2: //chance
                    Weathers[listIndex].chance = defaultWLST.chance;
                    break;
                default:
                    return 0;
                }
            break;
        default:
            return 0;
        }
    return 0;
    }
