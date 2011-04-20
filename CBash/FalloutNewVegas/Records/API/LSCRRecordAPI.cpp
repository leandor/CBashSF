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
#include "..\LSCRRecord.h"

namespace FNV
{
UINT32 LSCRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //icon Large Icon Filename
            return ISTRING_FIELD;
        case 8: //mico Small Icon Filename
            return ISTRING_FIELD;
        case 9: //desc Description
            return STRING_FIELD;
        case 10: //lnam LNAM ,, Struct
            return FORMID_FIELD;
        case 11: //lnam LNAM ,, Struct
            return FORMID_FIELD;
        case 12: //lnam LNAM ,, Struct
            return SINT16_FIELD;
        case 13: //lnam LNAM ,, Struct
            return SINT16_FIELD;
        case 14: //wmi1 Load Screen Type
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LSCRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //icon Large Icon Filename
            return ICON.IsLoaded() ? ICON->ICON.value : NULL;
        case 8: //mico Small Icon Filename
            return ICON.IsLoaded() ? ICON->MICO.value : NULL;
        case 9: //desc Description
            return DESCReq.value;
        case 10: //lnam LNAM ,, Struct
            return LNAM.IsLoaded() ? &LNAM->value10 : NULL;
        case 11: //lnam LNAM ,, Struct
            return LNAM.IsLoaded() ? &LNAM->value11 : NULL;
        case 12: //lnam LNAM ,, Struct
            return LNAM.IsLoaded() ? &LNAM->value12 : NULL;
        case 13: //lnam LNAM ,, Struct
            return LNAM.IsLoaded() ? &LNAM->value13 : NULL;
        case 14: //wmi1 Load Screen Type
            return WMI1.IsLoaded() ? &WMI1->value14 : NULL;
        default:
            return NULL;
        }
    }

bool LSCRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //icon Large Icon Filename
            ICON.Load();
            ICON->ICON.Copy((STRING)FieldValue);
            break;
        case 8: //mico Small Icon Filename
            ICON.Load();
            ICON->MICO.Copy((STRING)FieldValue);
            break;
        case 9: //desc Description
            DESCReq.Copy((STRING)FieldValue);
            break;
        case 10: //lnam LNAM ,, Struct
            LNAM.Load();
            LNAM->value10 = *(FORMID *)FieldValue;
            return true;
        case 11: //lnam LNAM ,, Struct
            LNAM.Load();
            LNAM->value11 = *(FORMID *)FieldValue;
            return true;
        case 12: //lnam LNAM ,, Struct
            LNAM.Load();
            LNAM->value12 = *(SINT16 *)FieldValue;
            break;
        case 13: //lnam LNAM ,, Struct
            LNAM.Load();
            LNAM->value13 = *(SINT16 *)FieldValue;
            break;
        case 14: //wmi1 Load Screen Type
            WMI1.Load();
            WMI1->value14 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void LSCRRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //icon Large Icon Filename
            if(ICON.IsLoaded())
                ICON->ICON.Unload();
            return;
        case 8: //mico Small Icon Filename
            if(ICON.IsLoaded())
                ICON->MICO.Unload();
            return;
        case 9: //desc Description
            DESCReq.Unload();
            return;
        case 10: //lnam LNAM ,, Struct
            LNAM.Unload();
            return;
        case 11: //lnam LNAM ,, Struct
            LNAM.Unload();
            return;
        case 12: //lnam LNAM ,, Struct
            LNAM.Unload();
            return;
        case 13: //lnam LNAM ,, Struct
            LNAM.Unload();
            return;
        case 14: //wmi1 Load Screen Type
            WMI1.Unload();
            return;
        default:
            return;
        }
    }
}