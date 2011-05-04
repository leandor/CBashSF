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
#include "..\RCPERecord.h"

namespace FNV
{
UINT32 RCPERecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //full
            return STRING_FIELD;
        case 8: //ctda Conditions
            return UINT8_FIELD;
        case 9: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 10: //ctda Conditions
            return UNPARSED_FIELD;
        case 11: //ctda Conditions
            return UINT32_FIELD;
        case 12: //ctda_p Conditions
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
        case 13: //ctda_p Conditions
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
        case 14: //ctda Conditions
            return UINT32_FIELD;
        case 15: //ctda Conditions
            return UNPARSED_FIELD;
        case 16: //data DATA ,, Struct
            return UNPARSED_FIELD;
        case 17: //data DATA ,, Struct
            return UINT32_FIELD;
        case 18: //data DATA ,, Struct
            return FORMID_FIELD;
        case 19: //data DATA ,, Struct
            return FORMID_FIELD;
        case 20: //rcil Item
            return FORMID_FIELD;
        case 21: //rcqy Quantity
            return UINT32_FIELD;
        case 22: //rcod Item
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * RCPERecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //full
            return FULL.value;
        case 8: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value8 : NULL;
        case 9: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value9[0] : NULL;
            return NULL;
        case 10: //ctda Conditions
            return UNPARSEDGET_FIELD10;
        case 11: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value11 : NULL;
        case 12: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value12[0] : NULL;
            return NULL;
        case 13: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value13[0] : NULL;
            return NULL;
        case 14: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value14 : NULL;
        case 15: //ctda Conditions
            return UNPARSEDGET_FIELD15;
        case 16: //data DATA ,, Struct
            return UNPARSEDGET_FIELD16;
        case 17: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value17 : NULL;
        case 18: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value18 : NULL;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value19 : NULL;
        case 20: //rcil Item
            return RCIL.IsLoaded() ? &RCIL->value20 : NULL;
        case 21: //rcqy Quantity
            return RCQY.IsLoaded() ? &RCQY->value21 : NULL;
        case 22: //rcod Item
            return RCOD.IsLoaded() ? &RCOD->value22 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool RCPERecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //ctda Conditions
            CTDAs.Load();
            CTDAs->value8 = *(UINT8 *)FieldValue;
            break;
        case 9: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            CTDAs.Load();
            CTDAs->value9[0] = ((UINT8ARRAY)FieldValue)[0];
            CTDAs->value9[1] = ((UINT8ARRAY)FieldValue)[1];
            CTDAs->value9[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 10: //ctda Conditions
            return UNPARSEDGET_FIELD10;
        case 11: //ctda Conditions
            CTDAs.Load();
            CTDAs->value11 = *(UINT32 *)FieldValue;
            break;
        case 12: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value12[0] = ((UINT8ARRAY)FieldValue)[0];
            CTDAs->value12[1] = ((UINT8ARRAY)FieldValue)[1];
            CTDAs->value12[2] = ((UINT8ARRAY)FieldValue)[2];
            CTDAs->value12[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 13: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value13[0] = ((UINT8ARRAY)FieldValue)[0];
            CTDAs->value13[1] = ((UINT8ARRAY)FieldValue)[1];
            CTDAs->value13[2] = ((UINT8ARRAY)FieldValue)[2];
            CTDAs->value13[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 14: //ctda Conditions
            CTDAs.Load();
            CTDAs->value14 = *(UINT32 *)FieldValue;
            break;
        case 15: //ctda Conditions
            return UNPARSEDGET_FIELD15;
        case 16: //data DATA ,, Struct
            return UNPARSEDGET_FIELD16;
        case 17: //data DATA ,, Struct
            DATA.Load();
            DATA->value17 = *(UINT32 *)FieldValue;
            break;
        case 18: //data DATA ,, Struct
            DATA.Load();
            DATA->value18 = *(FORMID *)FieldValue;
            return true;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->value19 = *(FORMID *)FieldValue;
            return true;
        case 20: //rcil Item
            RCIL.Load();
            RCIL->value20 = *(FORMID *)FieldValue;
            return true;
        case 21: //rcqy Quantity
            RCQY.Load();
            RCQY->value21 = *(UINT32 *)FieldValue;
            break;
        case 22: //rcod Item
            RCOD.Load();
            RCOD->value22 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void RCPERecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //full
            FULL.Unload();
            return;
        case 8: //ctda Conditions
            CTDAs.Unload();
            return;
        case 9: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 10: //ctda Conditions
            return UNPARSEDDEL_FIELD10;
        case 11: //ctda Conditions
            CTDAs.Unload();
            return;
        case 12: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 13: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 14: //ctda Conditions
            CTDAs.Unload();
            return;
        case 15: //ctda Conditions
            return UNPARSEDDEL_FIELD15;
        case 16: //data DATA ,, Struct
            return UNPARSEDDEL_FIELD16;
        case 17: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 18: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 19: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 20: //rcil Item
            RCIL.Unload();
            return;
        case 21: //rcqy Quantity
            RCQY.Unload();
            return;
        case 22: //rcod Item
            RCOD.Unload();
            return;
        default:
            return;
        }
    }
}