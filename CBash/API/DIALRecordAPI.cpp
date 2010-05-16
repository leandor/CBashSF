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
#include "..\Records\DIALRecord.h"

int DIALRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //quests
            return FIDARRAY_FIELD;
        case 7: //full
            return STRING_FIELD;
        case 8: //dialType
            return UBYTE_FIELD;
        case 9: //INFO
            return SUBRECORDS_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * DIALRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 7: //full
            return FULL.value;
        case 8: //dialType
            return &DATA.value.flags;
        default:
            return NULL;
        }
    }

unsigned int DIALRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //quests
            return (unsigned int)QSTI.size();
        case 9: //INFO
            return (unsigned int)INFO.size();
        default:
            return 0;
        }
    }

void DIALRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 6: //quests
            for(unsigned int p = 0;p < QSTI.size();p++)
                FieldValues[p] = QSTI[p];
            return;
        case 9: //INFO
            for(unsigned int p = 0;p < INFO.size();p++)
                FieldValues[p] = &INFO[p]->formID;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void DIALRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 7: //full
            FULL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void DIALRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 6: //quests
            QSTI.clear();
            if(nSize)
                {
                QSTI.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    QSTI[x] = new unsigned int(FieldValue[x]);
                    FormIDHandler.AddMaster(QSTI[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

void DIALRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 8: //dialType
            DATA.value.flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }
