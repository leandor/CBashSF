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
#include "..\MESGRecord.h"

namespace FNV
{
UINT32 MESGRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //desc Description
            return STRING_FIELD;
        case 8: //full Name
            return STRING_FIELD;
        case 9: //inam Icon
            return FORMID_FIELD;
        case 10: //dnam Flags
            return UINT32_FIELD;
        case 11: //tnam Display Time
            return UINT32_FIELD;
        case 12: //itxt Button Text
            return ISTRING_FIELD;
        case 13: //ctda Conditions
            return UINT8_FIELD;
        case 14: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 15: //ctda Conditions
            return UNPARSED_FIELD;
        case 16: //ctda Conditions
            return UINT32_FIELD;
        case 17: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 18: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 19: //ctda Conditions
            return UINT32_FIELD;
        case 20: //ctda Conditions
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * MESGRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //desc Description
            return DESCReq.value;
        case 8: //full Name
            return FULL.value;
        case 9: //inam Icon
            return INAM.IsLoaded() ? &INAM->value9 : NULL;
        case 10: //dnam Flags
            return DNAM.IsLoaded() ? &DNAM->value10 : NULL;
        case 11: //tnam Display Time
            return TNAM.IsLoaded() ? &TNAM->value11 : NULL;
        case 12: //itxt Button Text
            return ITXT.value;
        case 13: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value13 : NULL;
        case 14: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value14[0] : NULL;
            return NULL;
        case 15: //ctda Conditions
            return UNPARSEDGET_FIELD15;
        case 16: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value16 : NULL;
        case 17: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value17[0] : NULL;
            return NULL;
        case 18: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value18[0] : NULL;
            return NULL;
        case 19: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value19 : NULL;
        case 20: //ctda Conditions
            return UNPARSEDGET_FIELD20;
        default:
            return NULL;
        }
    }

bool MESGRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //desc Description
            DESCReq.Copy((STRING)FieldValue);
            break;
        case 8: //full Name
            FULL.Copy((STRING)FieldValue);
            break;
        case 9: //inam Icon
            INAM.Load();
            INAM->value9 = *(FORMID *)FieldValue;
            return true;
        case 10: //dnam Flags
            DNAM.Load();
            DNAM->value10 = *(UINT32 *)FieldValue;
            break;
        case 11: //tnam Display Time
            TNAM.Load();
            TNAM->value11 = *(UINT32 *)FieldValue;
            break;
        case 12: //itxt Button Text
            ITXT.Copy((STRING)FieldValue);
            break;
        case 13: //ctda Conditions
            CTDAs.Load();
            CTDAs->value13 = *(UINT8 *)FieldValue;
            break;
        case 14: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            CTDAs.Load();
            CTDAs->value14[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value14[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value14[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 15: //ctda Conditions
            return UNPARSEDGET_FIELD15;
        case 16: //ctda Conditions
            CTDAs.Load();
            CTDAs->value16 = *(UINT32 *)FieldValue;
            break;
        case 17: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value17[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value17[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value17[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value17[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 18: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value18[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value18[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value18[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value18[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 19: //ctda Conditions
            CTDAs.Load();
            CTDAs->value19 = *(UINT32 *)FieldValue;
            break;
        case 20: //ctda Conditions
            return UNPARSEDGET_FIELD20;
        default:
            break;
        }
    return false;
    }

void MESGRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //desc Description
            DESCReq.Unload();
            return;
        case 8: //full Name
            FULL.Unload();
            return;
        case 9: //inam Icon
            INAM.Unload();
            return;
        case 10: //dnam Flags
            DNAM.Unload();
            return;
        case 11: //tnam Display Time
            TNAM.Unload();
            return;
        case 12: //itxt Button Text
            ITXT.Unload();
            return;
        case 13: //ctda Conditions
            CTDAs.Unload();
            return;
        case 14: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 15: //ctda Conditions
            return UNPARSEDDEL_FIELD15;
        case 16: //ctda Conditions
            CTDAs.Unload();
            return;
        case 17: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 18: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 19: //ctda Conditions
            CTDAs.Unload();
            return;
        case 20: //ctda Conditions
            return UNPARSEDDEL_FIELD20;
        default:
            return;
        }
    }
}