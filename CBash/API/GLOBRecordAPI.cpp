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
#include "..\Records\GLOBRecord.h"

int GLOBRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //format
            return CHAR_FIELD;
        case 7: //value
            //Regardless of format, it is always stored as a float. Go figure.
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * GLOBRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //format
            return &FNAM.value.format;
        case 7: //value
            return &FLTV.value.value;
        default:
            return NULL;
        }
    }

void GLOBRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue)
    {
    switch(Field)
        {
        case 6: //format
            FNAM.value.format = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void GLOBRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void GLOBRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 7: //value
            FLTV.value.value = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int GLOBRecord::DeleteField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //format
            FNAM.Unload();
            break;
        case 7: //value
            //Regardless of format, it is always stored as a float. Go figure.
            FLTV.Unload();
            break;
        default:
            return 0;
        }
    return 1;
    }
