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
#include "..\CPTHRecord.h"

namespace FNV
{
UINT32 CPTHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //ctda Conditions
            return UINT8_FIELD;
        case 8: //ctda_p Conditions
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
        case 9: //ctda Conditions
            return UNPARSED_FIELD;
        case 10: //ctda Conditions
            return UINT32_FIELD;
        case 11: //ctda_p Conditions
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
        case 13: //ctda Conditions
            return UINT32_FIELD;
        case 14: //ctda Conditions
            return UNPARSED_FIELD;
        case 15: //anam Related Camera Paths
            return UNPARSED_FIELD;
        case 16: //data Camera Zoom
            return UINT8_FIELD;
        case 17: //snam Camera Shot
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * CPTHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value7 : NULL;
        case 8: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value8[0] : NULL;
            return NULL;
        case 9: //ctda Conditions
            return UNPARSEDGET_FIELD9;
        case 10: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value10 : NULL;
        case 11: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value11[0] : NULL;
            return NULL;
        case 12: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value12[0] : NULL;
            return NULL;
        case 13: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value13 : NULL;
        case 14: //ctda Conditions
            return UNPARSEDGET_FIELD14;
        case 15: //anam Related Camera Paths
            return UNPARSEDGET_FIELD15;
        case 16: //data Camera Zoom
            return DATA.IsLoaded() ? &DATA->value16 : NULL;
        case 17: //snam Camera Shot
            return SNAM.IsLoaded() ? &SNAM->value17 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool CPTHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //ctda Conditions
            CTDAs.Load();
            CTDAs->value7 = *(UINT8 *)FieldValue;
            break;
        case 8: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            CTDAs.Load();
            CTDAs->value8[0] = ((UINT8ARRAY)FieldValue)[0];
            CTDAs->value8[1] = ((UINT8ARRAY)FieldValue)[1];
            CTDAs->value8[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 9: //ctda Conditions
            return UNPARSEDGET_FIELD9;
        case 10: //ctda Conditions
            CTDAs.Load();
            CTDAs->value10 = *(UINT32 *)FieldValue;
            break;
        case 11: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value11[0] = ((UINT8ARRAY)FieldValue)[0];
            CTDAs->value11[1] = ((UINT8ARRAY)FieldValue)[1];
            CTDAs->value11[2] = ((UINT8ARRAY)FieldValue)[2];
            CTDAs->value11[3] = ((UINT8ARRAY)FieldValue)[3];
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
        case 13: //ctda Conditions
            CTDAs.Load();
            CTDAs->value13 = *(UINT32 *)FieldValue;
            break;
        case 14: //ctda Conditions
            return UNPARSEDGET_FIELD14;
        case 15: //anam Related Camera Paths
            return UNPARSEDGET_FIELD15;
        case 16: //data Camera Zoom
            DATA.Load();
            DATA->value16 = *(UINT8 *)FieldValue;
            break;
        case 17: //snam Camera Shot
            SNAM.Load();
            SNAM->value17 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void CPTHRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //ctda Conditions
            CTDAs.Unload();
            return;
        case 8: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 9: //ctda Conditions
            return UNPARSEDDEL_FIELD9;
        case 10: //ctda Conditions
            CTDAs.Unload();
            return;
        case 11: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 12: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 13: //ctda Conditions
            CTDAs.Unload();
            return;
        case 14: //ctda Conditions
            return UNPARSEDDEL_FIELD14;
        case 15: //anam Related Camera Paths
            return UNPARSEDDEL_FIELD15;
        case 16: //data Camera Zoom
            DATA.Unload();
            return;
        case 17: //snam Camera Shot
            SNAM.Unload();
            return;
        default:
            return;
        }
    }
}