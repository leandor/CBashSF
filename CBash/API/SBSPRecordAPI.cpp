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
#include "..\Records\SBSPRecord.h"

int SBSPRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //sizeX
            return FLOAT_FIELD;
        case 7: //sizeY
            return FLOAT_FIELD;
        case 8: //sizeZ
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * SBSPRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //sizeX
            return &DNAM.value.sizeX;
        case 7: //sizeY
            return &DNAM.value.sizeY;
        case 8: //sizeZ
            return &DNAM.value.sizeZ;
        default:
            return NULL;
        }
    }

void SBSPRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void SBSPRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 6: //sizeX
            DNAM.value.sizeX = FieldValue;
            break;
        case 7: //sizeY
            DNAM.value.sizeY = FieldValue;
            break;
        case 8: //sizeZ
            DNAM.value.sizeZ = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int SBSPRecord::DeleteField(const unsigned int Field)
    {
    SBSPDNAM defaultDNAM;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //sizeX
            DNAM.value.sizeX = defaultDNAM.sizeX;
            break;
        case 7: //sizeY
            DNAM.value.sizeY = defaultDNAM.sizeY;
            break;
        case 8: //sizeZ
            DNAM.value.sizeZ = defaultDNAM.sizeZ;
            break;
        default:
            return 0;
        }
    return 1;
    }