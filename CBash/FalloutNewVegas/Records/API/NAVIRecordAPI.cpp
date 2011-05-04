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
#include "..\NAVIRecord.h"

namespace FNV
{
UINT32 NAVIRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
            return UNKNOWN_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //formVersion
            return UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 7: //nver Version
            return UINT32_FIELD;
        case 8: //nvmi_p NVMI ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 9: //nvmi NVMI ,, Struct
            return FORMID_FIELD;
        case 10: //nvmi NVMI ,, Struct
            return FORMID_FIELD;
        case 11: //nvmi NVMI ,, Struct
            return SINT16_FIELD;
        case 12: //nvmi NVMI ,, Struct
            return SINT16_FIELD;
        case 13: //nvmi_p NVMI ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NVMI.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 14: //nvci NVCI ,, Struct
            return FORMID_FIELD;
        case 15: //nvci NVCI ,, Struct
            return FORMID_FIELD;
        case 16: //nvci NVCI ,, Struct
            return FORMID_FIELD;
        case 17: //nvci NVCI ,, Struct
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * NAVIRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 4: //eid
            return EDID.value;
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //nver Version
            return NVER.IsLoaded() ? &NVER->value7 : NULL;
        case 8: //nvmi_p NVMI ,, Struct
            *FieldValues = NVMI.IsLoaded() ? &NVMI->value8[0] : NULL;
            return NULL;
        case 9: //nvmi NVMI ,, Struct
            return NVMI.IsLoaded() ? &NVMI->value9 : NULL;
        case 10: //nvmi NVMI ,, Struct
            return NVMI.IsLoaded() ? &NVMI->value10 : NULL;
        case 11: //nvmi NVMI ,, Struct
            return NVMI.IsLoaded() ? &NVMI->value11 : NULL;
        case 12: //nvmi NVMI ,, Struct
            return NVMI.IsLoaded() ? &NVMI->value12 : NULL;
        case 13: //nvmi_p NVMI ,, Struct
            *FieldValues = NVMI.value;
            return NULL;
        case 14: //nvci NVCI ,, Struct
            return NVCI.IsLoaded() ? &NVCI->value14 : NULL;
        case 15: //nvci NVCI ,, Struct
            return NVCI.IsLoaded() ? &NVCI->value15 : NULL;
        case 16: //nvci NVCI ,, Struct
            return NVCI.IsLoaded() ? &NVCI->value16 : NULL;
        case 17: //nvci NVCI ,, Struct
            return NVCI.IsLoaded() ? &NVCI->value17 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool NAVIRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //nver Version
            NVER.Load();
            NVER->value7 = *(UINT32 *)FieldValue;
            break;
        case 8: //nvmi_p NVMI ,, Struct
            if(ArraySize != 4)
                break;
            NVMI.Load();
            NVMI->value8[0] = ((UINT8ARRAY)FieldValue)[0];
            NVMI->value8[1] = ((UINT8ARRAY)FieldValue)[1];
            NVMI->value8[2] = ((UINT8ARRAY)FieldValue)[2];
            NVMI->value8[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 9: //nvmi NVMI ,, Struct
            NVMI.Load();
            NVMI->value9 = *(FORMID *)FieldValue;
            return true;
        case 10: //nvmi NVMI ,, Struct
            NVMI.Load();
            NVMI->value10 = *(FORMID *)FieldValue;
            return true;
        case 11: //nvmi NVMI ,, Struct
            NVMI.Load();
            NVMI->value11 = *(SINT16 *)FieldValue;
            break;
        case 12: //nvmi NVMI ,, Struct
            NVMI.Load();
            NVMI->value12 = *(SINT16 *)FieldValue;
            break;
        case 13: //nvmi_p NVMI ,, Struct
            NVMI.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 14: //nvci NVCI ,, Struct
            NVCI.Load();
            NVCI->value14 = *(FORMID *)FieldValue;
            return true;
        case 15: //nvci NVCI ,, Struct
            NVCI.Load();
            NVCI->value15 = *(FORMID *)FieldValue;
            return true;
        case 16: //nvci NVCI ,, Struct
            NVCI.Load();
            NVCI->value16 = *(FORMID *)FieldValue;
            return true;
        case 17: //nvci NVCI ,, Struct
            NVCI.Load();
            NVCI->value17 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void NAVIRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //nver Version
            NVER.Unload();
            return;
        case 8: //nvmi_p NVMI ,, Struct
            NVMI.Unload();
            return;
        case 9: //nvmi NVMI ,, Struct
            NVMI.Unload();
            return;
        case 10: //nvmi NVMI ,, Struct
            NVMI.Unload();
            return;
        case 11: //nvmi NVMI ,, Struct
            NVMI.Unload();
            return;
        case 12: //nvmi NVMI ,, Struct
            NVMI.Unload();
            return;
        case 13: //nvmi_p NVMI ,, Struct
            NVMI.Unload();
            return;
        case 14: //nvci NVCI ,, Struct
            NVCI.Unload();
            return;
        case 15: //nvci NVCI ,, Struct
            NVCI.Unload();
            return;
        case 16: //nvci NVCI ,, Struct
            NVCI.Unload();
            return;
        case 17: //nvci NVCI ,, Struct
            NVCI.Unload();
            return;
        default:
            return;
        }
    }
}