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
#include "..\Records\ROADRecord.h"

int ROADRecord::CreateListElement(const unsigned int subField)
    {
    unsigned int listSize = 0;
    switch(subField)
        {
        case 6: //PGRP
            listSize = (unsigned int)PGRP.size();
            listSize++;
            PGRP.resize(listSize);
            return (int)listSize - 1;
        case 7: //PGRR
            listSize = (unsigned int)PGRP.size();
            listSize++;
            PGRP.resize(listSize);
            return (int)listSize - 1;
        default:
            return -1;
        }
    }

int ROADRecord::DeleteListElement(const unsigned int subField)
    {
    unsigned int listSize = 0;
    switch(subField)
        {
        case 6: //PGRP
            listSize = (unsigned int)PGRP.size();
            PGRP.pop_back();
            listSize--;
            return (int)listSize - 1;
        case 7: //PGRR
            listSize = (unsigned int)PGRR.size();
            PGRP.pop_back();
            listSize--;
            return (int)listSize - 1;
        default:
            return -1;
        }
    }

int ROADRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //PGRP
            return LIST_FIELD;
        case 7: //PGRR
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

int ROADRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 6: //PGRP
            switch(listField)
                {
                case 1: //x
                    return FLOAT_FIELD;
                case 2: //y
                    return FLOAT_FIELD;
                case 3: //z
                    return FLOAT_FIELD;
                case 4: //connections
                    return UBYTE_FIELD;
                case 5: //unused1
                    return BYTES_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 7: //PGRR
            switch(listField)
                {
                case 1: //x
                    return FLOAT_FIELD;
                case 2: //y
                    return FLOAT_FIELD;
                case 3: //z
                    return FLOAT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int ROADRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //PGRP
            return (unsigned int)PGRP.size();
        case 7: //PGRR
            return (unsigned int)PGRR.size();
        default:
            return 0;
        }
    }

unsigned int ROADRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 6: //PGRP
            switch(listField)
                {
                case 5: //unused1
                    return 3;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

void ROADRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 6: //PGRP
            if(listIndex >= PGRP.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 5: //unused1
                    *FieldValues = &PGRP[listIndex].unused1[0];
                    return;
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void * ROADRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 6: //PGRP
            if(listIndex >= PGRP.size())
                return NULL;
            switch(listField)
                {
                case 1: //x
                    return &PGRP[listIndex].x;
                case 2: //y
                    return &PGRP[listIndex].y;
                case 3: //z
                    return &PGRP[listIndex].z;
                case 4: //connections
                    return &PGRP[listIndex].connections;
                default:
                    return NULL;
                }
        case 7: //PGRR
            if(listIndex >= PGRR.size())
                return NULL;
            switch(listField)
                {
                case 1: //x
                    return &PGRR[listIndex].x;
                case 2: //y
                    return &PGRR[listIndex].y;
                case 3: //z
                    return &PGRR[listIndex].z;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void ROADRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue)
    {
    switch(subField)
        {
        case 6: //PGRP
            if(listIndex >= PGRP.size())
                return;
            switch(listField)
                {
                case 1: //x
                    PGRP[listIndex].x = FieldValue;
                    break;
                case 2: //y
                    PGRP[listIndex].y = FieldValue;
                    break;
                case 3: //z
                    PGRP[listIndex].z = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 7: //PGRR
            if(listIndex >= PGRR.size())
                return;
            switch(listField)
                {
                case 1: //x
                    PGRR[listIndex].x = FieldValue;
                    break;
                case 2: //y
                    PGRR[listIndex].y = FieldValue;
                    break;
                case 3: //z
                    PGRR[listIndex].z = FieldValue;
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

void ROADRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 6: //PGRP
            if(listIndex >= PGRP.size())
                return;
            switch(listField)
                {
                case 4: //connections
                    PGRP[listIndex].connections = FieldValue;
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

void ROADRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 6: //PGRP
            if(listIndex >= PGRP.size())
                return;
            switch(listField)
                {
                case 5: //unused1
                    if(nSize != 3)
                        return;
                    PGRP[listIndex].unused1[0] = FieldValue[0];
                    PGRP[listIndex].unused1[1] = FieldValue[1];
                    PGRP[listIndex].unused1[2] = FieldValue[2];
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

int ROADRecord::DeleteField(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //PGRP
            PGRP.clear();
            break;
        case 7: //PGRR
            PGRR.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }

int ROADRecord::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    GENPGRP defaultPGRP;
    ROADPGRR defaultPGRR;
    switch(subField)
        {
        case 6: //PGRP
            if(listIndex >= PGRP.size())
                return 0;
            switch(listField)
                {
                case 1: //x
                    PGRP[listIndex].x = defaultPGRP.x;
                    break;
                case 2: //y
                    PGRP[listIndex].y = defaultPGRP.y;
                    break;
                case 3: //z
                    PGRP[listIndex].z = defaultPGRP.z;
                    break;
                case 4: //connections
                    PGRP[listIndex].connections = defaultPGRP.connections;
                    break;
                case 5: //unused1
                    PGRP[listIndex].unused1[0] = defaultPGRP.unused1[0];
                    PGRP[listIndex].unused1[1] = defaultPGRP.unused1[1];
                    PGRP[listIndex].unused1[2] = defaultPGRP.unused1[2];
                    break;
                default:
                    return 0;
                }
            break;
        case 7: //PGRR
            if(listIndex >= PGRR.size())
                return 0;
            switch(listField)
                {
                case 1: //x
                    PGRR[listIndex].x = defaultPGRR.x;
                    break;
                case 2: //y
                    PGRR[listIndex].y = defaultPGRR.y;
                    break;
                case 3: //z
                    PGRR[listIndex].z = defaultPGRR.z;
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
