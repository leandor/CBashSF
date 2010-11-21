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
#include "..\LSCRRecord.h"

signed long LSCRRecord::CreateListElement(const unsigned long subField)
    {
    ReqSubRecord<LSCRLNAM> *curLNAM = NULL;
    switch(subField)
        {
        case 8: //locations
            curLNAM = new ReqSubRecord<LSCRLNAM>;
            LNAM.push_back(curLNAM);
            return (signed long)LNAM.size() - 1;
        default:
            return -1;
        }
    }

signed long LSCRRecord::DeleteListElement(const unsigned long subField)
    {
    ReqSubRecord<LSCRLNAM> *curLNAM = NULL;
    switch(subField)
        {
        case 8: //locations
            curLNAM = LNAM.back();
            delete curLNAM;
            LNAM.pop_back();
            return (signed long)LNAM.size() - 1;
        default:
            return -1;
        }
    }

signed long LSCRRecord::GetOtherFieldType(const unsigned long Field)
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

void * LSCRRecord::GetOtherField(const unsigned long Field)
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

signed long LSCRRecord::GetListFieldType(const unsigned long subField, const unsigned long listField)
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

unsigned long LSCRRecord::GetListSize(const unsigned long Field)
    {
    switch(Field)
        {
        case 8: //locations
            return (unsigned long)LNAM.size();
        default:
            return 0;
        }
    }

void * LSCRRecord::GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
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

void LSCRRecord::SetField(const unsigned long Field, char *FieldValue)
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

void LSCRRecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue)
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
                    break;
                case 2: //indirect
                    LNAM[listIndex]->value.indirect = FieldValue;
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

void LSCRRecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, short FieldValue)
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

signed long LSCRRecord::DeleteField(const unsigned long Field)
    {
    unsigned long nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //iconPath
            ICON.Unload();
            break;
        case 7: //text
            DESC.Unload();
            break;
        case 8: //locations
            nSize = (unsigned long)LNAM.size();
            for(unsigned long x = 0; x < nSize; x++)
                delete LNAM[x];
            LNAM.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }

signed long LSCRRecord::DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    LSCRLNAM defaultLNAM;
    switch(subField)
        {
        case 8: //locations
            if(listIndex >= LNAM.size())
                return 0;
            switch(listField)
                {
                case 1: //direct
                    LNAM[listIndex]->value.direct = defaultLNAM.direct;
                    break;
                case 2: //indirect
                    LNAM[listIndex]->value.indirect = defaultLNAM.indirect;
                    break;
                case 3: //gridY
                    LNAM[listIndex]->value.gridY = defaultLNAM.gridY;
                    break;
                case 4: //gridX
                    LNAM[listIndex]->value.gridX = defaultLNAM.gridX;
                    break;
                default:
                    return 0;
                }
            break;
        default:
            return 0;
        }
    return 1;
    }
