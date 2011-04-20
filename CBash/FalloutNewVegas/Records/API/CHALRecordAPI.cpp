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
#include "..\CHALRecord.h"

namespace FNV
{
UINT32 CHALRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //full Name
            return STRING_FIELD;
        case 8: //scri Script
            return FORMID_FIELD;
        case 9: //desc Description
            return STRING_FIELD;
        case 10: //data DATA ,, Struct
            return UINT32_FIELD;
        case 11: //data DATA ,, Struct
            return UINT32_FIELD;
        case 12: //data DATA ,, Struct
            return UINT32_FIELD;
        case 13: //data DATA ,, Struct
            return UINT32_FIELD;
        case 14: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 15: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 16: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 17: //snam (depends on type)
            return FORMID_FIELD;
        case 18: //xnam (depends on type)
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CHALRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //full Name
            return FULL.value;
        case 8: //scri Script
            return SCRI.IsLoaded() ? &SCRI->value8 : NULL;
        case 9: //desc Description
            return DESC.value;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value10 : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value11 : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value13 : NULL;
        case 14: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value14[0] : NULL;
            return NULL;
        case 15: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value15[0] : NULL;
            return NULL;
        case 16: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value16[0] : NULL;
            return NULL;
        case 17: //snam (depends on type)
            return SNAM.IsLoaded() ? &SNAM->value17 : NULL;
        case 18: //xnam (depends on type)
            return XNAM.IsLoaded() ? &XNAM->value18 : NULL;
        default:
            return NULL;
        }
    }

bool CHALRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //full Name
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //scri Script
            SCRI.Load();
            SCRI->value8 = *(FORMID *)FieldValue;
            return true;
        case 9: //desc Description
            DESC.Copy((STRING)FieldValue);
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
            DATA->value12 = *(UINT32 *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->value13 = *(UINT32 *)FieldValue;
            break;
        case 14: //data_p DATA ,, Struct
            if(ArraySize != 2)
                break;
            DATA.Load();
            DATA->value14[0] = ((UINT8 *)FieldValue)[0];
            DATA->value14[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 15: //data_p DATA ,, Struct
            if(ArraySize != 2)
                break;
            DATA.Load();
            DATA->value15[0] = ((UINT8 *)FieldValue)[0];
            DATA->value15[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 16: //data_p DATA ,, Struct
            if(ArraySize != 4)
                break;
            DATA.Load();
            DATA->value16[0] = ((UINT8 *)FieldValue)[0];
            DATA->value16[1] = ((UINT8 *)FieldValue)[1];
            DATA->value16[2] = ((UINT8 *)FieldValue)[2];
            DATA->value16[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 17: //snam (depends on type)
            SNAM.Load();
            SNAM->value17 = *(FORMID *)FieldValue;
            return true;
        case 18: //xnam (depends on type)
            XNAM.Load();
            XNAM->value18 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void CHALRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //full Name
            FULL.Unload();
            return;
        case 8: //scri Script
            SCRI.Unload();
            return;
        case 9: //desc Description
            DESC.Unload();
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
        case 14: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 17: //snam (depends on type)
            SNAM.Unload();
            return;
        case 18: //xnam (depends on type)
            XNAM.Unload();
            return;
        default:
            return;
        }
    }
}