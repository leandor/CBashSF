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
#include "..\Records\TES4Record.h"

int TES4Record::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //version
            return FLOAT_FIELD;
        case 7: //numRecords
            return UINT_FIELD;
        case 8: //nextObject
            return UINT_FIELD;
        case 9: //ofst_p
            return BYTES_FIELD;
        case 10: //dele_p
            return BYTES_FIELD;
        case 11: //author
            return STRING_FIELD;
        case 12: //description
            return STRING_FIELD;
        case 13: //masters
            return STRINGARRAY_FIELD;
        case 14: //DATA
            return JUNK_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * TES4Record::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid, not present on TES4
            //return EDID.value;
            return NULL;
        case 6: //version
            return &HEDR.value.version;
        case 7: //numRecords
            return &HEDR.value.numRecords;
        case 8: //nextObject
            return &HEDR.value.nextObject;
        case 11: //author
            return CNAM.value;
        case 12: //description
            return SNAM.value;
        case 14: //DATA
            return NULL;
        default:
            return NULL;
        }
    }

void TES4Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char **FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 13: //masters
            MAST.clear();
            if(nSize)
                {
                MAST.resize(nSize);
                for(unsigned int x = 0; x < nSize; x++)
                    {
                    MAST[x].Copy(FieldValue[x]);
                    }
                }
            break;
        default:
            return;
        }
    return;
    }

void TES4Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 9: //ofst_p
            OFST.Copy(FieldValue, nSize);
            break;
        case 10: //dele_p
            DELE.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void TES4Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 6: //version
            HEDR.value.version = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void TES4Record::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 7: //numRecords
            HEDR.value.numRecords = FieldValue;
            break;
        case 8: //nextObject
            HEDR.value.nextObject = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void TES4Record::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid, not present on TES4
            //EDID.Copy(FieldValue);
            return;
        case 11: //author
            CNAM.Copy(FieldValue);
            break;
        case 12: //description
            SNAM.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

unsigned int TES4Record::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //ofst_p
            return OFST.GetSize();
        case 10: //dele_p
            return DELE.GetSize();
        case 13: //masters
            return (unsigned int)MAST.size();
        default:
            return 0;
        }
    }

void TES4Record::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //ofst_p
            *FieldValues = OFST.value;
            //memcpy(*FieldValues, OFST.value, OFST.size);
            //for(unsigned int x = 0; x < OFST.size; x++)
                //printf("%02X", ((*FieldValues)[x]));
                //printf("%02X", OFST.value[x]);
                //printf("\n\n");
                //((char *)(*FieldValues))[x] = OFST.value[x];
            //memcpy(*FieldValues, OFST.value, OFST.size);
            return;
        case 10: //dele_p
            *FieldValues = DELE.value;
            //memcpy(*FieldValues, DELE.value, DELE.size);
            return;
        case 13: //masters
            for(unsigned int p = 0;p < MAST.size();p++)
                FieldValues[p] = MAST[p].value;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }
