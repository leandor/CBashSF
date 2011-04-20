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
#include "..\..\..\Common.h"
#include "..\LSCTRecord.h"

namespace FNV
{
UINT32 LSCTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 4: //formVersion
            return UINT16_FIELD;
        case 5: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 6: //edid Editor ID
            return ISTRING_FIELD;
        case 7: //data DATA ,, Struct
            return UINT32_FIELD;
        case 8: //data DATA ,, Struct
            return UINT32_FIELD;
        case 9: //data DATA ,, Struct
            return UINT32_FIELD;
        case 10: //data DATA ,, Struct
            return UINT32_FIELD;
        case 11: //data DATA ,, Struct
            return UINT32_FIELD;
        case 12: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 13: //data DATA ,, Struct
            return UINT32_FIELD;
        case 14: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 15: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 16: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 17: //data DATA ,, Struct
            return UINT32_FIELD;
        case 18: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 20;
                default:
                    return UNKNOWN_FIELD;
                }
        case 19: //data DATA ,, Struct
            return UINT32_FIELD;
        case 20: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 21: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 22: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 23: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 24: //data DATA ,, Struct
            return UINT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LSCTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //versionControl1
            *FieldValues = &flagsUnk;
            return NULL;
        case 4: //formVersion
            return &formVersion;
        case 5: //versionControl2
            *FieldValues = &versionControl2;
            return NULL;
        case 6: //edid Editor ID
            return EDID.value;
        case 7: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value7 : NULL;
        case 8: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value8 : NULL;
        case 9: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value9 : NULL;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value10 : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value11 : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value13 : NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value15 : NULL;
        case 16: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value16 : NULL;
        case 17: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value17 : NULL;
        case 18: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value18[0] : NULL;
            return NULL;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value19 : NULL;
        case 20: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value20 : NULL;
        case 21: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value21 : NULL;
        case 22: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value22 : NULL;
        case 23: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value23[0] : NULL;
            return NULL;
        case 24: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value24 : NULL;
        default:
            return NULL;
        }
    }

bool LSCTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8 *)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8 *)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8 *)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 4: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 5: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8 *)FieldValue)[0];
            versionControl2[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 6: //edid Editor ID
            EDID.Copy((STRING)FieldValue);
            break;
        case 7: //data DATA ,, Struct
            DATA.Load();
            DATA->value7 = *(UINT32 *)FieldValue;
            break;
        case 8: //data DATA ,, Struct
            DATA.Load();
            DATA->value8 = *(UINT32 *)FieldValue;
            break;
        case 9: //data DATA ,, Struct
            DATA.Load();
            DATA->value9 = *(UINT32 *)FieldValue;
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->value10 = *(UINT32 *)FieldValue;
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->value11 = *(UINT32 *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->value12 = *(FLOAT32 *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->value13 = *(UINT32 *)FieldValue;
            break;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //data DATA ,, Struct
            DATA.Load();
            DATA->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //data DATA ,, Struct
            DATA.Load();
            DATA->value17 = *(UINT32 *)FieldValue;
            break;
        case 18: //data_p DATA ,, Struct
            if(ArraySize != 20)
                break;
            DATA.Load();
            DATA->value18[0] = ((UINT8 *)FieldValue)[0];
            DATA->value18[1] = ((UINT8 *)FieldValue)[1];
            DATA->value18[2] = ((UINT8 *)FieldValue)[2];
            DATA->value18[3] = ((UINT8 *)FieldValue)[3];
            DATA->value18[4] = ((UINT8 *)FieldValue)[4];
            DATA->value18[5] = ((UINT8 *)FieldValue)[5];
            DATA->value18[6] = ((UINT8 *)FieldValue)[6];
            DATA->value18[7] = ((UINT8 *)FieldValue)[7];
            DATA->value18[8] = ((UINT8 *)FieldValue)[8];
            DATA->value18[9] = ((UINT8 *)FieldValue)[9];
            DATA->value18[10] = ((UINT8 *)FieldValue)[10];
            DATA->value18[11] = ((UINT8 *)FieldValue)[11];
            DATA->value18[12] = ((UINT8 *)FieldValue)[12];
            DATA->value18[13] = ((UINT8 *)FieldValue)[13];
            DATA->value18[14] = ((UINT8 *)FieldValue)[14];
            DATA->value18[15] = ((UINT8 *)FieldValue)[15];
            DATA->value18[16] = ((UINT8 *)FieldValue)[16];
            DATA->value18[17] = ((UINT8 *)FieldValue)[17];
            DATA->value18[18] = ((UINT8 *)FieldValue)[18];
            DATA->value18[19] = ((UINT8 *)FieldValue)[19];
            break;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->value19 = *(UINT32 *)FieldValue;
            break;
        case 20: //data DATA ,, Struct
            DATA.Load();
            DATA->value20 = *(FLOAT32 *)FieldValue;
            break;
        case 21: //data DATA ,, Struct
            DATA.Load();
            DATA->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //data DATA ,, Struct
            DATA.Load();
            DATA->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //data_p DATA ,, Struct
            if(ArraySize != 4)
                break;
            DATA.Load();
            DATA->value23[0] = ((UINT8 *)FieldValue)[0];
            DATA->value23[1] = ((UINT8 *)FieldValue)[1];
            DATA->value23[2] = ((UINT8 *)FieldValue)[2];
            DATA->value23[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 24: //data DATA ,, Struct
            DATA.Load();
            DATA->value24 = *(UINT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void LSCTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //formVersion
            formVersion = 0;
            return;
        case 5: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 6: //edid Editor ID
            EDID.Unload();
            return;
        case 7: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 8: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 9: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 10: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 11: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 12: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 13: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 14: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 17: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 18: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 19: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 20: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 21: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 22: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 23: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 24: //data DATA ,, Struct
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}