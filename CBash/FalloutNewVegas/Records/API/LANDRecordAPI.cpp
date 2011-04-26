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
#include "..\LANDRecord.h"

namespace FNV
{
UINT32 LANDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 4: //eid
            return MISSING_FIELD;
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
        case 7: //data_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DATA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 8: //vnml_p Vertex Normals
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return VNML.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 9: //vhgt_p Vertext Height Map
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return VHGT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //vclr_p Vertex Colours
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return VCLR.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 11: //btxt BTXT ,, Struct
            return FORMID_FIELD;
        case 12: //btxt BTXT ,, Struct
            return UINT8_FIELD;
        case 13: //btxt_p BTXT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //btxt BTXT ,, Struct
            return SINT16_FIELD;
        case 15: //atxt ATXT ,, Struct
            return FORMID_FIELD;
        case 16: //atxt ATXT ,, Struct
            return UINT8_FIELD;
        case 17: //atxt_p ATXT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 18: //atxt ATXT ,, Struct
            return SINT16_FIELD;
        case 19: //vtxt_p Alpha Layer Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return VTXT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 20: //vtex Textures
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LANDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
           *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //data_p Unknown
            *FieldValues = DATA.value;
            return NULL;
        case 8: //vnml_p Vertex Normals
            *FieldValues = VNML.value;
            return NULL;
        case 9: //vhgt_p Vertext Height Map
            *FieldValues = VHGT.value;
            return NULL;
        case 10: //vclr_p Vertex Colours
            *FieldValues = VCLR.value;
            return NULL;
        case 11: //btxt BTXT ,, Struct
            return BTXT.IsLoaded() ? &BTXT->value10 : NULL;
        case 12: //btxt BTXT ,, Struct
            return BTXT.IsLoaded() ? &BTXT->value11 : NULL;
        case 13: //btxt_p BTXT ,, Struct
            *FieldValues = BTXT.IsLoaded() ? &BTXT->value12[0] : NULL;
            return NULL;
        case 14: //btxt BTXT ,, Struct
            return BTXT.IsLoaded() ? &BTXT->value13 : NULL;
        case 15: //atxt ATXT ,, Struct
            return ATXT.IsLoaded() ? &ATXT->value14 : NULL;
        case 16: //atxt ATXT ,, Struct
            return ATXT.IsLoaded() ? &ATXT->value15 : NULL;
        case 17: //atxt_p ATXT ,, Struct
            *FieldValues = ATXT.IsLoaded() ? &ATXT->value16[0] : NULL;
            return NULL;
        case 18: //atxt ATXT ,, Struct
            return ATXT.IsLoaded() ? &ATXT->value17 : NULL;
        case 19: //vtxt_p Alpha Layer Data
            *FieldValues = VTXT.value;
            return NULL;
        case 20: //vtex Textures
            return UNPARSEDGET_FIELD19;
        default:
            return NULL;
        }
    }

bool LANDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 5: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8 *)FieldValue)[0];
            versionControl2[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 7: //data_p Unknown
            DATA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 8: //vnml_p Vertex Normals
            VNML.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //vhgt_p Vertext Height Map
            VHGT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //vclr_p Vertex Colours
            VCLR.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //btxt BTXT ,, Struct
            BTXT.Load();
            BTXT->value10 = *(FORMID *)FieldValue;
            return true;
        case 12: //btxt BTXT ,, Struct
            BTXT.Load();
            BTXT->value11 = *(UINT8 *)FieldValue;
            break;
        case 13: //btxt_p BTXT ,, Struct
            if(ArraySize != 1)
                break;
            BTXT.Load();
            BTXT->value12[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 14: //btxt BTXT ,, Struct
            BTXT.Load();
            BTXT->value13 = *(SINT16 *)FieldValue;
            break;
        case 15: //atxt ATXT ,, Struct
            ATXT.Load();
            ATXT->value14 = *(FORMID *)FieldValue;
            return true;
        case 16: //atxt ATXT ,, Struct
            ATXT.Load();
            ATXT->value15 = *(UINT8 *)FieldValue;
            break;
        case 17: //atxt_p ATXT ,, Struct
            if(ArraySize != 1)
                break;
            ATXT.Load();
            ATXT->value16[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 18: //atxt ATXT ,, Struct
            ATXT.Load();
            ATXT->value17 = *(SINT16 *)FieldValue;
            break;
        case 19: //vtxt_p Alpha Layer Data
            VTXT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 20: //vtex Textures
            return UNPARSEDGET_FIELD19;
        default:
            break;
        }
    return false;
    }

void LANDRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //data_p Unknown
            DATA.Unload();
            return;
        case 8: //vnml_p Vertex Normals
            VNML.Unload();
            return;
        case 9: //vhgt_p Vertext Height Map
            VHGT.Unload();
            return;
        case 10: //vclr_p Vertex Colours
            VCLR.Unload();
            return;
        case 11: //btxt BTXT ,, Struct
            BTXT.Unload();
            return;
        case 12: //btxt BTXT ,, Struct
            BTXT.Unload();
            return;
        case 13: //btxt_p BTXT ,, Struct
            BTXT.Unload();
            return;
        case 14: //btxt BTXT ,, Struct
            BTXT.Unload();
            return;
        case 15: //atxt ATXT ,, Struct
            ATXT.Unload();
            return;
        case 16: //atxt ATXT ,, Struct
            ATXT.Unload();
            return;
        case 17: //atxt_p ATXT ,, Struct
            ATXT.Unload();
            return;
        case 18: //atxt ATXT ,, Struct
            ATXT.Unload();
            return;
        case 19: //vtxt_p Alpha Layer Data
            VTXT.Unload();
            return;
        case 20: //vtex Textures
            return UNPARSEDDEL_FIELD19;
        default:
            return;
        }
    }
}