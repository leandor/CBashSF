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
#include "..\IDLERecord.h"

namespace FNV
{
UINT32 IDLERecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //modPath
            return ISTRING_FIELD;
        case 8: //modb
            return FLOAT32_FIELD;
        case 9: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 10: //mods Alternate Textures
            return ISTRING_FIELD;

        case 13: //modelFlags
            return UINT8_FIELD;
        case 14: //ctda Conditions
            return UINT8_FIELD;
        case 15: //ctda_p Conditions
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
        case 16: //ctda Conditions
            return UNPARSED_FIELD;
        case 17: //ctda Conditions
            return UINT32_FIELD;
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
            return UNKNOWN_FIELD;
        case 19: //ctda_p Conditions
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
        case 20: //ctda Conditions
            return UINT32_FIELD;
        case 21: //ctda Conditions
            return UNPARSED_FIELD;
        case 22: //anam Related Idle Animations
            return UNPARSED_FIELD;
        case 23: //data DATA ,, Struct
            return UINT8_FIELD;
        case 24: //data DATA ,, Struct
            return UINT8_FIELD;
        case 25: //data DATA ,, Struct
            return UINT8_FIELD;
        case 26: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 27: //data DATA ,, Struct
            return SINT16_FIELD;
        case 28: //data DATA ,, Struct
            return UINT8_FIELD;
        case 29: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * IDLERecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 8: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 9: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 10: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 11: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value11 : NULL;
        case 12: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value12 : NULL;
        case 13: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD->value13 : NULL;
        case 14: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value14 : NULL;
        case 15: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value15[0] : NULL;
            return NULL;
        case 16: //ctda Conditions
            return UNPARSEDGET_FIELD16;
        case 17: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value17 : NULL;
        case 18: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value18[0] : NULL;
            return NULL;
        case 19: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value19[0] : NULL;
            return NULL;
        case 20: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value20 : NULL;
        case 21: //ctda Conditions
            return UNPARSEDGET_FIELD21;
        case 22: //anam Related Idle Animations
            return UNPARSEDGET_FIELD22;
        case 23: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value23 : NULL;
        case 24: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value24 : NULL;
        case 25: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value25 : NULL;
        case 26: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value26[0] : NULL;
            return NULL;
        case 27: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value27 : NULL;
        case 28: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value28 : NULL;
        case 29: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value29[0] : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool IDLERecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 8: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 11: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value11 = *(FORMID *)FieldValue;
            return true;
        case 12: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value12 = *(SINT32 *)FieldValue;
            break;
        case 13: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value13 = *(UINT8 *)FieldValue;
            break;
        case 14: //ctda Conditions
            CTDAs.Load();
            CTDAs->value14 = *(UINT8 *)FieldValue;
            break;
        case 15: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            CTDAs.Load();
            CTDAs->value15[0] = ((UINT8ARRAY)FieldValue)[0];
            CTDAs->value15[1] = ((UINT8ARRAY)FieldValue)[1];
            CTDAs->value15[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 16: //ctda Conditions
            return UNPARSEDGET_FIELD16;
        case 17: //ctda Conditions
            CTDAs.Load();
            CTDAs->value17 = *(UINT32 *)FieldValue;
            break;
        case 18: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value18[0] = ((UINT8ARRAY)FieldValue)[0];
            CTDAs->value18[1] = ((UINT8ARRAY)FieldValue)[1];
            CTDAs->value18[2] = ((UINT8ARRAY)FieldValue)[2];
            CTDAs->value18[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 19: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value19[0] = ((UINT8ARRAY)FieldValue)[0];
            CTDAs->value19[1] = ((UINT8ARRAY)FieldValue)[1];
            CTDAs->value19[2] = ((UINT8ARRAY)FieldValue)[2];
            CTDAs->value19[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 20: //ctda Conditions
            CTDAs.Load();
            CTDAs->value20 = *(UINT32 *)FieldValue;
            break;
        case 21: //ctda Conditions
            return UNPARSEDGET_FIELD21;
        case 22: //anam Related Idle Animations
            return UNPARSEDGET_FIELD22;
        case 23: //data DATA ,, Struct
            DATA.Load();
            DATA->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //data DATA ,, Struct
            DATA.Load();
            DATA->value24 = *(UINT8 *)FieldValue;
            break;
        case 25: //data DATA ,, Struct
            DATA.Load();
            DATA->value25 = *(UINT8 *)FieldValue;
            break;
        case 26: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value26[0] = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 27: //data DATA ,, Struct
            DATA.Load();
            DATA->value27 = *(SINT16 *)FieldValue;
            break;
        case 28: //data DATA ,, Struct
            DATA.Load();
            DATA->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value29[0] = ((UINT8ARRAY)FieldValue)[0];
            break;
        default:
            break;
        }
    return false;
    }

void IDLERecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 8: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 9: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 10: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 11: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 12: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 13: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 14: //ctda Conditions
            CTDAs.Unload();
            return;
        case 15: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 16: //ctda Conditions
            return UNPARSEDDEL_FIELD16;
        case 17: //ctda Conditions
            CTDAs.Unload();
            return;
        case 18: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 19: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 20: //ctda Conditions
            CTDAs.Unload();
            return;
        case 21: //ctda Conditions
            return UNPARSEDDEL_FIELD21;
        case 22: //anam Related Idle Animations
            return UNPARSEDDEL_FIELD22;
        case 23: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 24: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 25: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 26: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 27: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 28: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 29: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}