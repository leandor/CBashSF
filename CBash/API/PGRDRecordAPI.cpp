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
#include "..\Records\PGRDRecord.h"

int PGRDRecord::CreateListElement(const unsigned int subField)
    {
    unsigned int listSize = 0;
    switch(subField)
        {
        case 7: //PGRP
            listSize = (unsigned int)PGRP.size();
            listSize++;
            PGRP.resize(listSize);
            return (int)listSize - 1;
        case 10: //PGRI
            listSize = (unsigned int)PGRI.size();
            listSize++;
            PGRI.resize(listSize);
            return (int)listSize - 1;
        case 11: //PGRL
            PGRL.push_back(new PGRDPGRL);
            return (int)PGRL.size() - 1;
        default:
            return -1;
        }
    }

int PGRDRecord::DeleteListElement(const unsigned int subField)
    {
    unsigned int listSize = 0;
    PGRDPGRL *curPGRL = NULL;
    switch(subField)
        {
        case 7: //PGRP
            listSize = (unsigned int)PGRP.size();
            PGRP.pop_back();
            listSize--;
            return (int)listSize - 1;
        case 10: //PGRI
            listSize = (unsigned int)PGRI.size();
            PGRI.pop_back();
            listSize--;
            return (int)listSize - 1;
        case 11: //PGRL
            curPGRL = PGRL.back();
            delete curPGRL;
            PGRL.pop_back();
            return (int)PGRL.size() - 1;
        default:
            return -1;
        }
    }

int PGRDRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //count
            return USHORT_FIELD;
        case 7: //PGRP
            return LIST_FIELD;
        case 8: //PGAG
            return BYTES_FIELD;
        case 9: //PGRR
            return BYTES_FIELD;
        case 10: //PGRI
            return LIST_FIELD;
        case 11: //PGRL
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * PGRDRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //count
            return &DATA.value.count;
        default:
            return NULL;
        }
    }

int PGRDRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 7: //PGRP
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
        case 10: //PGRI
            switch(listField)
                {
                case 1: //point
                    return USHORT_FIELD;
                case 2: //unused1
                    return BYTES_FIELD;
                case 3: //x
                    return FLOAT_FIELD;
                case 4: //y
                    return FLOAT_FIELD;
                case 5: //z
                    return FLOAT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 11: //PGRL
            switch(listField)
                {
                case 1: //reference
                    return FID_FIELD;
                case 2: //points
                    return UINTARRAY_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int PGRDRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 7: //PGRP
            return (unsigned int)PGRP.size();
        case 10: //PGRI
            return (unsigned int)PGRI.size();
        case 11: //PGRL
            return (unsigned int)PGRL.size();
        default:
            return 0;
        }
    }

unsigned int PGRDRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 7: //PGRP
            switch(listField)
                {
                case 5: //unused1
                    return 3;
                default:
                    return 0;
                }
        case 10: //PGRI
            switch(listField)
                {
                case 2: //unused1
                    return 2;
                default:
                    return 0;
                }
        case 11: //PGRL
            if(listIndex >= PGRL.size())
                return 0;
            switch(listField)
                {
                case 2: //points
                    return (unsigned int)PGRL[listIndex]->points.size() - 1;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned int PGRDRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 8: //PGAG
            return PGAG.size;
        case 9: //PGRR
            return PGRR.size;
        default:
            return 0;
        }
    }

void PGRDRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 8: //PGAG
            *FieldValues = PGAG.value;
            return;
        case 9: //PGRR
            *FieldValues = PGRR.value;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void PGRDRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 7: //PGRP
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
        case 10: //PGRI
            if(listIndex >= PGRI.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 2: //unused1
                    *FieldValues = &PGRI[listIndex].unused1[0];
                    return;
                default:
                    *FieldValues = NULL;
                    return;
                }
        case 11: //PGRL
            if(listIndex >= PGRL.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 2: //points
                    if(PGRL[listIndex]->points.size() - 1 == 0)
                        *FieldValues = NULL;
                    else
                        *FieldValues = &PGRL[listIndex]->points[1];
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

void * PGRDRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 7: //PGRP
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
        case 10: //PGRI
            if(listIndex >= PGRI.size())
                return NULL;
            switch(listField)
                {
                case 1: //point
                    return &PGRI[listIndex].point;
                case 3: //x
                    return &PGRI[listIndex].x;
                case 4: //y
                    return &PGRI[listIndex].y;
                case 5: //z
                    return &PGRI[listIndex].z;
                default:
                    return NULL;
                }
        case 11: //PGRL
            if(listIndex >= PGRL.size())
                return NULL;
            switch(listField)
                {
                case 1: //reference
                    if(PGRL[listIndex]->points.size() == 0)
                        return NULL;
                    else
                        return &PGRL[listIndex]->points[0];
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void PGRDRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 6: //count
            DATA.value.count = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void PGRDRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 8: //PGAG
            PGAG.Copy(FieldValue, nSize);
            break;
        case 9: //PGRR
            PGRR.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void PGRDRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue)
    {
    switch(subField)
        {
        case 7: //PGRP
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
        case 10: //PGRI
            if(listIndex >= PGRI.size())
                return;
            switch(listField)
                {
                case 3: //x
                    PGRI[listIndex].x = FieldValue;
                case 4: //y
                    PGRI[listIndex].y = FieldValue;
                case 5: //z
                    PGRI[listIndex].z = FieldValue;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void PGRDRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 7: //PGRP
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

void PGRDRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 7: //PGRP
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
        case 10: //PGRI
            if(listIndex >= PGRI.size())
                return;
            switch(listField)
                {
                case 2: //unused1
                    if(nSize != 2)
                        return;
                    PGRI[listIndex].unused1[0] = FieldValue[0];
                    PGRI[listIndex].unused1[1] = FieldValue[1];
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

void PGRDRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned short FieldValue)
    {
    switch(subField)
        {
        case 10: //PGRI
            if(listIndex >= PGRI.size())
                return;
            switch(listField)
                {
                case 1: //point
                    PGRI[listIndex].point = FieldValue;
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

void PGRDRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 11: //PGRL
            if(listIndex >= PGRL.size())
                return;
            switch(listField)
                {
                case 1: //reference
                    if(PGRL[listIndex]->points.size() == 0)
                        PGRL[listIndex]->points.resize(1);
                    PGRL[listIndex]->points[0] = FieldValue;
                    FormIDHandler.AddMaster(PGRL[listIndex]->points[0]);
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

void PGRDRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue[], unsigned int nSize)
    {
    unsigned int reference = 0;
    switch(subField)
        {
        case 11: //PGRL
            if(listIndex >= PGRL.size())
                return;
            switch(listField)
                {
                case 2: //points
                    if(PGRL[listIndex]->points.size())
                        reference = PGRL[listIndex]->points[0];
                    PGRL[listIndex]->points.clear();
                    PGRL[listIndex]->points.resize(nSize + 1);
                    PGRL[listIndex]->points[0] = reference;
                    if(nSize)
                        for(unsigned int x = 0; x < nSize; x++)
                            PGRL[listIndex]->points[x + 1] = FieldValue[x];
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
