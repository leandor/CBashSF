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
#include "..\Records\BSGNRecord.h"

int BSGNRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //iconPath
            return STRING_FIELD;
        case 8: //text
            return STRING_FIELD;
        case 9: //spells
            return FIDARRAY_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * BSGNRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //iconPath
            return ICON.value;
        case 8: //text
            return DESC.value;
        default:
            return NULL;
        }
    }

unsigned int BSGNRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //spells
            return (unsigned int)SPLO.size();
        default:
            return 0;
        }
    }

void BSGNRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //spells
            for(unsigned int p = 0;p < SPLO.size();p++)
                FieldValues[p] = SPLO[p];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void BSGNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 7: //iconPath
            ICON.Copy(FieldValue);
            break;
        case 8: //text
            DESC.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void BSGNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 9: //spells
            SPLO.clear();
            if(nSize)
                {
                SPLO.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    SPLO[x] = new unsigned int(FieldValue[x]);
                    FormIDHandler.AddMaster(SPLO[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

int BSGNRecord::DeleteField(const unsigned int Field)
    {
    unsigned int nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //iconPath
            ICON.Unload();
            break;
        case 8: //text
            DESC.Unload();
            break;
        case 9: //spells
            nSize = (unsigned int)SPLO.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete SPLO[x];
            SPLO.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }
