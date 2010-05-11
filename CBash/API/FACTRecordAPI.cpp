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
#include "..\Records\FACTRecord.h"

int FACTRecord::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<GENXNAM> *curXNAM = NULL;
    ReqRecordField<FACTRNAM> *curRNAM = NULL;
    switch(subField)
        {
        case 7: //relations
            curXNAM = new ReqRecordField<GENXNAM>;
            XNAM.push_back(curXNAM);
            return (int)XNAM.size() - 1;
        case 10: //ranks
            curRNAM = new ReqRecordField<FACTRNAM>;
            RNAM.push_back(curRNAM);
            return (int)RNAM.size() - 1;
        default:
            return -1;
        }
    }

int FACTRecord::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<GENXNAM> *curXNAM = NULL;
    ReqRecordField<FACTRNAM> *curRNAM = NULL;
    switch(subField)
        {
        case 9: //relations
            curXNAM = XNAM.back();
            delete curXNAM;
            XNAM.pop_back();
            return (int)XNAM.size() - 1;
        case 10: //ranks
            curRNAM = RNAM.back();
            delete curRNAM;
            RNAM.pop_back();
            return (int)RNAM.size() - 1;
        default:
            return -1;
        }
    }

int FACTRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //relations
            return LIST_FIELD;
        case 8: //flags
            return UBYTE_FIELD;
        case 9: //crimeGoldMultiplier
            return FLOAT_FIELD;
        case 10: //ranks
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * FACTRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 8: //flags
            return &DATA.value.flags;
        case 9: //crimeGoldMultiplier
            return &CNAM.value.crimeGoldMultiplier;
        default:
            return NULL;
        }
    }

int FACTRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 7: //relations
            switch(listField)
                {
                case 1: //faction
                    return FID_FIELD;
                case 2: //mod
                    return INT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //ranks
            switch(listField)
                {
                case 1: //rank
                    return INT_FIELD;
                case 2: //male
                    return STRING_FIELD;
                case 3: //female
                    return STRING_FIELD;
                case 4: //insigniaPath
                    return STRING_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int FACTRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 7: //relations
            return (unsigned int)XNAM.size();
        case 10: //ranks
            return (unsigned int)RNAM.size();
        default:
            return 0;
        }
    }

void * FACTRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 7: //relations
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
        case 10: //ranks
            if(listIndex >= RNAM.size())
                return NULL;
            switch(listField)
                {
                case 1: //rank
                    return &RNAM[listIndex]->value.RNAM;
                case 2: //male
                    return RNAM[listIndex]->value.MNAM.value;
                case 3: //female
                    return RNAM[listIndex]->value.FNAM.value;
                case 4: //insigniaPath
                    return RNAM[listIndex]->value.INAM.value;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void FACTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void FACTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 8: //flags
            DATA.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void FACTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 9: //crimeGoldMultiplier
            CNAM.value.crimeGoldMultiplier = FieldValue;
            CNAM.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void FACTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    switch(subField)
        {
        case 7: //relations
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
        case 10: //ranks
            if(listIndex >= RNAM.size())
                return;
            switch(listField)
                {
                case 1: //rank
                    RNAM[listIndex]->value.RNAM = FieldValue;
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

void FACTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 7: //relations
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

void FACTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue)
    {
    switch(subField)
        {
        case 10: //ranks
            if(listIndex >= RNAM.size())
                return;
            switch(listField)
                {
                case 2: //male
                    RNAM[listIndex]->value.MNAM.Copy(FieldValue);
                    break;
                case 3: //female
                    RNAM[listIndex]->value.FNAM.Copy(FieldValue);
                    break;
                case 4: //insigniaPath
                    RNAM[listIndex]->value.INAM.Copy(FieldValue);
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
