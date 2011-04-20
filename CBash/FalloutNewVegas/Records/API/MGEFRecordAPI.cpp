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
#include "..\MGEFRecord.h"

namespace FNV
{
UINT32 MGEFRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 8: //desc Description
            return STRING_FIELD;
        case 9: //icon Large Icon Filename
            return ISTRING_FIELD;
        case 10: //mico Small Icon Filename
            return ISTRING_FIELD;
        case 11: //modl Model Filename
            return STRING_FIELD;
        case 12: //modb_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //modt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //mods Alternate Textures
            return STRING_FIELD;
        case 15: //mods Alternate Textures
            return FORMID_FIELD;
        case 16: //mods Alternate Textures
            return SINT32_FIELD;
        case 17: //modd FaceGen Model Flags
            return UINT8_FIELD;
        case 18: //data DATA ,, Struct
            return UINT32_FIELD;
        case 19: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 20: //data DATA ,, Struct
            return FORMID_FIELD;
        case 21: //data DATA ,, Struct
            return SINT32_FIELD;
        case 22: //data DATA ,, Struct
            return UNPARSED_FIELD;
        case 23: //data DATA ,, Struct
            return UINT16_FIELD;
        case 24: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 25: //data DATA ,, Struct
            return FORMID_FIELD;
        case 26: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 27: //data DATA ,, Struct
            return FORMID_FIELD;
        case 28: //data DATA ,, Struct
            return FORMID_FIELD;
        case 29: //data DATA ,, Struct
            return FORMID_FIELD;
        case 30: //data DATA ,, Struct
            return FORMID_FIELD;
        case 31: //data DATA ,, Struct
            return FORMID_FIELD;
        case 32: //data DATA ,, Struct
            return FORMID_FIELD;
        case 33: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 34: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 35: //data DATA ,, Struct
            return UINT32_FIELD;
        case 36: //data DATA ,, Struct
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * MGEFRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //desc Description
            return DESCReq.value;
        case 9: //icon Large Icon Filename
            return ICON.IsLoaded() ? ICON->ICON.value : NULL;
        case 10: //mico Small Icon Filename
            return ICON.IsLoaded() ? ICON->MICO.value : NULL;
        case 11: //modl Model Filename
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 12: //modb_p Unknown
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODB.value : NULL;
            return NULL;
        case 13: //modt_p Texture Files Hashes
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODT.value : NULL;
            return NULL;
        case 14: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 15: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value15 : NULL;
        case 16: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value16 : NULL;
        case 17: //modd FaceGen Model Flags
            return MODL.IsLoaded() ? &MODL->MODD->value17 : NULL;
        case 18: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value18 : NULL;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value19 : NULL;
        case 20: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value20 : NULL;
        case 21: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value21 : NULL;
        case 22: //data DATA ,, Struct
            return UNPARSEDGET_FIELD22;
        case 23: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value23 : NULL;
        case 24: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value24[0] : NULL;
            return NULL;
        case 25: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value25 : NULL;
        case 26: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value26 : NULL;
        case 27: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value27 : NULL;
        case 28: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value28 : NULL;
        case 29: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value29 : NULL;
        case 30: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value30 : NULL;
        case 31: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value31 : NULL;
        case 32: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value32 : NULL;
        case 33: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value33 : NULL;
        case 34: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value34 : NULL;
        case 35: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value35 : NULL;
        case 36: //data DATA ,, Struct
            return UNPARSEDGET_FIELD36;
        default:
            return NULL;
        }
    }

bool MGEFRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 8: //desc Description
            DESCReq.Copy((STRING)FieldValue);
            break;
        case 9: //icon Large Icon Filename
            ICON.Load();
            ICON->ICON.Copy((STRING)FieldValue);
            break;
        case 10: //mico Small Icon Filename
            ICON.Load();
            ICON->MICO.Copy((STRING)FieldValue);
            break;
        case 11: //modl Model Filename
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 12: //modb_p Unknown
            MODL.Load();
            MODL->MODB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 13: //modt_p Texture Files Hashes
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 14: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 15: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value15 = *(FORMID *)FieldValue;
            return true;
        case 16: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value16 = *(SINT32 *)FieldValue;
            break;
        case 17: //modd FaceGen Model Flags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value17 = *(UINT8 *)FieldValue;
            break;
        case 18: //data DATA ,, Struct
            DATA.Load();
            DATA->value18 = *(UINT32 *)FieldValue;
            break;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->value19 = *(FLOAT32 *)FieldValue;
            break;
        case 20: //data DATA ,, Struct
            DATA.Load();
            DATA->value20 = *(FORMID *)FieldValue;
            return true;
        case 21: //data DATA ,, Struct
            DATA.Load();
            DATA->value21 = *(SINT32 *)FieldValue;
            break;
        case 22: //data DATA ,, Struct
            return UNPARSEDGET_FIELD22;
        case 23: //data DATA ,, Struct
            DATA.Load();
            DATA->value23 = *(UINT16 *)FieldValue;
            break;
        case 24: //data_p DATA ,, Struct
            if(ArraySize != 2)
                break;
            DATA.Load();
            DATA->value24[0] = ((UINT8 *)FieldValue)[0];
            DATA->value24[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 25: //data DATA ,, Struct
            DATA.Load();
            DATA->value25 = *(FORMID *)FieldValue;
            return true;
        case 26: //data DATA ,, Struct
            DATA.Load();
            DATA->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //data DATA ,, Struct
            DATA.Load();
            DATA->value27 = *(FORMID *)FieldValue;
            return true;
        case 28: //data DATA ,, Struct
            DATA.Load();
            DATA->value28 = *(FORMID *)FieldValue;
            return true;
        case 29: //data DATA ,, Struct
            DATA.Load();
            DATA->value29 = *(FORMID *)FieldValue;
            return true;
        case 30: //data DATA ,, Struct
            DATA.Load();
            DATA->value30 = *(FORMID *)FieldValue;
            return true;
        case 31: //data DATA ,, Struct
            DATA.Load();
            DATA->value31 = *(FORMID *)FieldValue;
            return true;
        case 32: //data DATA ,, Struct
            DATA.Load();
            DATA->value32 = *(FORMID *)FieldValue;
            return true;
        case 33: //data DATA ,, Struct
            DATA.Load();
            DATA->value33 = *(FLOAT32 *)FieldValue;
            break;
        case 34: //data DATA ,, Struct
            DATA.Load();
            DATA->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //data DATA ,, Struct
            DATA.Load();
            DATA->value35 = *(UINT32 *)FieldValue;
            break;
        case 36: //data DATA ,, Struct
            return UNPARSEDGET_FIELD36;
        default:
            break;
        }
    return false;
    }

void MGEFRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 8: //desc Description
            DESCReq.Unload();
            return;
        case 9: //icon Large Icon Filename
            if(ICON.IsLoaded())
                ICON->ICON.Unload();
            return;
        case 10: //mico Small Icon Filename
            if(ICON.IsLoaded())
                ICON->MICO.Unload();
            return;
        case 11: //modl Model Filename
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 12: //modb_p Unknown
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 13: //modt_p Texture Files Hashes
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 14: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 15: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 16: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 17: //modd FaceGen Model Flags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 18: //data DATA ,, Struct
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
            return UNPARSEDDEL_FIELD22;
        case 23: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 24: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 25: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 26: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 27: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 28: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 29: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 30: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 31: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 32: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 33: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 34: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 35: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 36: //data DATA ,, Struct
            return UNPARSEDDEL_FIELD36;
        default:
            return;
        }
    }
}