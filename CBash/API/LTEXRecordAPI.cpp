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
#include "..\Records\LTEXRecord.h"

int LTEXRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //iconPath
            return STRING_FIELD;
        case 7: //flags
            return UBYTE_FIELD;
        case 8: //friction
            return UBYTE_FIELD;
        case 9: //restitution
            return UBYTE_FIELD;
        case 10: //specular
            return UBYTE_FIELD;
        case 11: //grass
            return FIDARRAY_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LTEXRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //iconPath
            return ICON.value;
        case 7: //flags
            return &HNAM.value.flags;
        case 8: //friction
            return &HNAM.value.friction;
        case 9: //restitution
            return &HNAM.value.restitution;
        case 10: //specular
            return &SNAM.value.specular;
        default:
            return NULL;
        }
    }

unsigned int LTEXRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 11: //grass
            return (unsigned int)GNAM.size();
        default:
            return 0;
        }
    }

void LTEXRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 11: //grass
            for(unsigned int p = 0;p < GNAM.size();p++)
                FieldValues[p] = GNAM[p];
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void LTEXRecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //iconPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void LTEXRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 7: //flags
            HNAM.value.flags = FieldValue;
            HNAM.isLoaded = true;
            break;
        case 8: //friction
            HNAM.value.friction = FieldValue;
            HNAM.isLoaded = true;
            break;
        case 9: //restitution
            HNAM.value.restitution = FieldValue;
            HNAM.isLoaded = true;
            break;
        case 10: //specular
            SNAM.value.specular = FieldValue;
            SNAM.isLoaded = true;
            break;
        default:
            return;
        }
    return;
    }

void LTEXRecord::SetField(const unsigned int Field, unsigned int FieldValue[], unsigned int nSize)
    {
    switch(Field)
        {
        case 11: //grass
            GNAM.clear();
            if(nSize)
                {
                GNAM.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    GNAM[x] = new unsigned int(FieldValue[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

int LTEXRecord::DeleteField(const unsigned int Field)
    {
    LTEXHNAM defaultHNAM;
    unsigned int nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //iconPath
            ICON.Unload();
            break;
        case 7: //flags
            HNAM.value.flags = defaultHNAM.flags;
            break;
        case 8: //friction
            HNAM.value.friction = defaultHNAM.friction;
            break;
        case 9: //restitution
            HNAM.value.restitution = defaultHNAM.restitution;
            break;
        case 10: //specular
            SNAM.Unload();
            break;
        case 11: //grass
            nSize = (unsigned int)GNAM.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete GNAM[x];
            GNAM.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }
