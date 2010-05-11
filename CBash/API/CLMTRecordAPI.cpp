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
            return MODL.MODL.value;
        case 10: //modb
            return &MODL.MODB.value.MODB;
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
            return MODL.MODT.size;
        default:
            return 0;
        }
    }

void CLMTRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 11: //modt_p
            *FieldValues = MODL.MODT.value;
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

void CLMTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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
            MODL.MODL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void CLMTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    //All size maintenence done by Create/Delete
    switch(subField)
        {
        case 6: //weathers
            if(listIndex >= Weathers.size())
                return;
            switch(listField)
                {
                case 1: //weather
                    Weathers[listIndex].weather = FieldValue;
                    FormIDHandler.AddMaster(Weathers[listIndex].weather);
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    }

void CLMTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    //All size maintenence done by Create/Delete
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

void CLMTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 10: //modb
            MODL.MODB.value.MODB = FieldValue;
            MODL.MODB.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void CLMTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 11: //modt_p
            MODL.MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void CLMTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
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
