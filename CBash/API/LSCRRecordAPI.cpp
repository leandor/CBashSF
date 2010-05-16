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
#include "..\Records\LSCRRecord.h"

int LSCRRecord::CreateListElement(const unsigned int subField)
    {
    ReqRecordField<LSCRLNAM> *curLNAM = NULL;
    switch(subField)
        {
        case 8: //locations
            curLNAM = new ReqRecordField<LSCRLNAM>;
            LNAM.push_back(curLNAM);
            return (int)LNAM.size() - 1;
        default:
            return -1;
        }
    }

int LSCRRecord::DeleteListElement(const unsigned int subField)
    {
    ReqRecordField<LSCRLNAM> *curLNAM = NULL;
    switch(subField)
        {
        case 8: //locations
            curLNAM = LNAM.back();
            delete curLNAM;
            LNAM.pop_back();
            return (int)LNAM.size() - 1;
        default:
            return -1;
        }
    }

int LSCRRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //iconPath
            return STRING_FIELD;
        case 7: //text
            return STRING_FIELD;
        case 8: //locations
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LSCRRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //iconPath
            return ICON.value;
        case 7: //text
            return DESC.value;
        default:
            return NULL;
        }
    }

int LSCRRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 8: //locations
            switch(listField)
                {
                case 1: //direct
                    return FID_FIELD;
                case 2: //indirect
                    return FID_FIELD;
                case 3: //gridY
                    return SHORT_FIELD;
                case 4: //gridX
                    return SHORT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int LSCRRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //locations
            return (unsigned int)LNAM.size();
        default:
            return 0;
        }
    }

void * LSCRRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 8: //locations
            if(listIndex >= LNAM.size())
                return NULL;
            switch(listField)
                {
                case 1: //direct
                    return &LNAM[listIndex]->value.direct;
                case 2: //indirect
                    return &LNAM[listIndex]->value.indirect;
                case 3: //gridY
                    return &LNAM[listIndex]->value.gridY;
                case 4: //gridX
                    return &LNAM[listIndex]->value.gridX;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void LSCRRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //iconPath
            ICON.Copy(FieldValue);
            break;
        case 7: //text
            DESC.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void LSCRRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 8: //locations
            if(listIndex >= LNAM.size())
                return;
            switch(listField)
                {
                case 1: //direct
                    LNAM[listIndex]->value.direct = FieldValue;
                    FormIDHandler.AddMaster(LNAM[listIndex]->value.direct);
                    break;
                case 2: //indirect
                    LNAM[listIndex]->value.indirect = FieldValue;
                    FormIDHandler.AddMaster(LNAM[listIndex]->value.indirect);
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

void LSCRRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue)
    {
    switch(subField)
        {
        case 8: //locations
            if(listIndex >= LNAM.size())
                return;
            switch(listField)
                {
                case 3: //gridY
                    LNAM[listIndex]->value.gridY = FieldValue;
                    break;
                case 4: //gridX
                    LNAM[listIndex]->value.gridX = FieldValue;
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
