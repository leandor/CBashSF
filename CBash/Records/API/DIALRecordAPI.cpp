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
#include "..\DIALRecord.h"

signed long DIALRecord::GetOtherFieldType(const unsigned long Field)
    {
    switch(Field)
        {
        case 6: //quests
            return FIDARRAY_FIELD;
        case 7: //removedQuests
            return FIDARRAY_FIELD;
        case 8: //full
            return STRING_FIELD;
        case 9: //dialType
            return UBYTE_FIELD;
        case 10: //INFO
            return SUBRECORDS_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * DIALRecord::GetOtherField(const unsigned long Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 8: //full
            return FULL.value;
        case 9: //dialType
            return &DATA.value.flags;
        default:
            return NULL;
        }
    }

unsigned long DIALRecord::GetFieldArraySize(const unsigned long Field)
    {
    switch(Field)
        {
        case 6: //quests
            return (unsigned long)QSTI.size();
        case 7: //removedQuests
            return (unsigned long)QSTR.size();
        case 10: //INFO
            return (unsigned long)INFO.size();
        default:
            return 0;
        }
    }

void DIALRecord::GetFieldArray(const unsigned long Field, void **FieldValues)
    {
    switch(Field)
        {
        case 6: //quests
            for(unsigned long p = 0;p < QSTI.size();p++)
                FieldValues[p] = QSTI[p];
            return;
        case 7: //removedQuests
            for(unsigned long p = 0;p < QSTR.size();p++)
                FieldValues[p] = QSTR[p];
            return;
        case 10: //INFO
            for(unsigned long p = 0;p < INFO.size();p++)
                FieldValues[p] = &INFO[p]->formID;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void DIALRecord::SetField(const unsigned long Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 8: //full
            FULL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void DIALRecord::SetField(const unsigned long Field, unsigned long FieldValue[], unsigned long nSize)
    {
    switch(Field)
        {
        case 6: //quests
            for(unsigned long x = 0; x < QSTI.size(); x++)
                delete QSTI[x];
            QSTI.clear();
            if(nSize)
                {
                QSTI.resize(nSize);
                for(unsigned long x = 0; x < nSize; x++)
                    {
                    QSTI[x] = new unsigned long(FieldValue[x]);
                    }
                }
            break;
        case 7: //removedQuests
            for(unsigned long x = 0; x < QSTR.size(); x++)
                delete QSTR[x];
            QSTR.clear();
            if(nSize)
                {
                QSTR.resize(nSize);
                for(unsigned long x = 0; x < nSize; x++)
                    {
                    QSTR[x] = new unsigned long(FieldValue[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

void DIALRecord::SetField(const unsigned long Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 9: //dialType
            DATA.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

signed long DIALRecord::DeleteField(const unsigned long Field)
    {
    unsigned long nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //quests
            nSize = (unsigned long)QSTI.size();
            for(unsigned long x = 0; x < nSize; x++)
                delete QSTI[x];
            QSTI.clear();
            break;
        case 7: //removedQuests
            nSize = (unsigned long)QSTR.size();
            for(unsigned long x = 0; x < nSize; x++)
                delete QSTR[x];
            QSTR.clear();
            break;
        case 8: //full
            FULL.Unload();
            break;
        case 9: //dialType
            DATA.Unload();
            break;
        default:
            return 0;
        }
    return 1;
    }
