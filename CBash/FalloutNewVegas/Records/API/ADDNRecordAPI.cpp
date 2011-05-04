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
#include "..\ADDNRecord.h"

namespace FNV
{
UINT32 ADDNRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //boundX
            return SINT16_FIELD;
        case 8: //boundY
            return SINT16_FIELD;
        case 9: //boundZ
            return SINT16_FIELD;
        case 10: //modPath
            return ISTRING_FIELD;
        case 11: //modb
            return FLOAT32_FIELD;
        case 12: //modt_p
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
        case 13: //mods Alternate Textures
            return ISTRING_FIELD;

        case 16: //modelFlags
            return UINT8_FIELD;
        case 17: //data Node Index
            return SINT32_FIELD;
        case 18: //snam Sound
            return FORMID_FIELD;
        case 19: //dnam DNAM ,, Struct
            return UINT16_FIELD;
        case 20: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * ADDNRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //boundX
            return OBND.IsLoaded() ? &OBND->x : NULL;
        case 8: //boundY
            return OBND.IsLoaded() ? &OBND->y : NULL;
        case 9: //boundZ
            return OBND.IsLoaded() ? &OBND->z : NULL;
        case 10: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 11: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 12: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 13: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 14: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value14 : NULL;
        case 15: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value15 : NULL;
        case 16: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD->value16 : NULL;
        case 17: //data Node Index
            return DATA.IsLoaded() ? &DATA->value17 : NULL;
        case 18: //snam Sound
            return SNAM.IsLoaded() ? &SNAM->value18 : NULL;
        case 19: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value19 : NULL;
        case 20: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value20[0] : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool ADDNRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //boundX
            OBND.Load();
            OBND->x = *(SINT16 *)FieldValue;
            break;
        case 8: //boundY
            OBND.Load();
            OBND->y = *(SINT16 *)FieldValue;
            break;
        case 9: //boundZ
            OBND.Load();
            OBND->z = *(SINT16 *)FieldValue;
            break;
        case 10: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 11: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 12: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 13: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 14: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value14 = *(FORMID *)FieldValue;
            return true;
        case 15: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value15 = *(SINT32 *)FieldValue;
            break;
        case 16: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value16 = *(UINT8 *)FieldValue;
            break;
        case 17: //data Node Index
            DATA.Load();
            DATA->value17 = *(SINT32 *)FieldValue;
            break;
        case 18: //snam Sound
            SNAM.Load();
            SNAM->value18 = *(FORMID *)FieldValue;
            return true;
        case 19: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value19 = *(UINT16 *)FieldValue;
            break;
        case 20: //dnam_p DNAM ,, Struct
            if(ArraySize != 2)
                break;
            DNAM.Load();
            DNAM->value20[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->value20[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        default:
            break;
        }
    return false;
    }

void ADDNRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //boundX
            if(OBND.IsLoaded())
                OBND->x = defaultOBND.x;
            return;
        case 8: //boundY
            if(OBND.IsLoaded())
                OBND->y = defaultOBND.y;
            return;
        case 9: //boundZ
            if(OBND.IsLoaded())
                OBND->z = defaultOBND.z;
            return;
        case 10: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 11: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 12: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 13: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 14: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 15: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 16: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 17: //data Node Index
            DATA.Unload();
            return;
        case 18: //snam Sound
            SNAM.Unload();
            return;
        case 19: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 20: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        default:
            return;
        }
    }
}