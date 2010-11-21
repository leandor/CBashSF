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
#include "..\GMSTRecord.h"

signed long GMSTRecord::GetOtherFieldType(const unsigned long Field)
    {
    switch(Field)
        {
        case 6: //value
            switch(DATA.format)
                {
                case 's':
                    return STRING_FIELD;
                case 'i':
                    return INT_FIELD;
                case 'f':
                    return FLOAT_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

void * GMSTRecord::GetOtherField(const unsigned long Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //value
            switch(DATA.format)
                {
                case 's':
                    return DATA.s;
                case 'i':
                    return &DATA.i;
                case 'f':
                    return &DATA.f;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void GMSTRecord::SetField(const unsigned long Field, signed long FieldValue)
    {
    switch(Field)
        {
        case 6: //value
            if(DATA.format == 'i')
                DATA.i = FieldValue;
            return;
        default:
            return;
        }
    }

void GMSTRecord::SetField(const unsigned long Field, float FieldValue)
    {
    switch(Field)
        {
        case 6: //value
            if(DATA.format == 'f')
                DATA.f = FieldValue;
            return;
        default:
            return;
        }
    }

void GMSTRecord::SetField(const unsigned long Field, char *FieldValue)
    {
    unsigned long nSize;
    switch(Field)
        {
        //case 5: //eid, unsettable due to conflicts with EDID_ModFile_Record
            //It invalidates the keys. Would have to erase original entry, set new entry.
            //But, it would have to be done at the collection level.
            //EDID.Copy(FieldValue);
            //return;
        case 6: //value
            if(DATA.format == 's')
                {
                //changing strings is one of the easy ways to change the Header.size, so update as needed
                if(DATA.s != NULL)
                    {
                    delete []DATA.s;
                    }
                nSize = (unsigned long)strlen(FieldValue) + 1;
                DATA.s = new char[nSize];
                strcpy_s(DATA.s, nSize, FieldValue);
                }
            break;
        default:
            return;
        }
    return;
    }

signed long GMSTRecord::DeleteField(const unsigned long Field)
    {
    GMSTDATA defaultDATA;
    switch(Field)
        {
        case 6: //value
            switch(DATA.format)
                {
                case 's':
                    delete []DATA.s;
                    DATA.s = defaultDATA.s;
                    break;
                case 'i':
                    DATA.i = defaultDATA.i;
                    break;
                case 'f':
                    DATA.f = defaultDATA.f;
                    break;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    return 1;
    }
