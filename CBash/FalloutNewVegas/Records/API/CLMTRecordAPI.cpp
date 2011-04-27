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
#include "..\CLMTRecord.h"

namespace FNV
{
UINT32 CLMTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //wlst Weather Types ,, Array
            return FORMID_FIELD;
        case 8: //wlst Weather Types ,, Array
            return SINT32_FIELD;
        case 9: //wlst Weather Types ,, Array
            return FORMID_FIELD;
        case 10: //fnam Sun Texture
            return ISTRING_FIELD;
        case 11: //gnam Sun Glare Texture
            return ISTRING_FIELD;
        case 12: //modPath
            return ISTRING_FIELD;
        case 13: //modb
            return FLOAT32_FIELD;
        case 14: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
        case 15: //altTextures
            if(!MODL.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return MODL->Textures.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return STRING_FIELD;
                case 2: //texture
                    return FORMID_FIELD;
                case 3: //index
                    return SINT32_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }

        case 18: //modelFlags
            return UINT8_FIELD;
        case 19: //tnam TNAM ,, Struct
            return UINT8_FIELD;
        case 20: //tnam TNAM ,, Struct
            return UINT8_FIELD;
        case 21: //tnam TNAM ,, Struct
            return UINT8_FIELD;
        case 22: //tnam TNAM ,, Struct
            return UINT8_FIELD;
        case 23: //tnam TNAM ,, Struct
            return UINT8_FIELD;
        case 24: //tnam TNAM ,, Struct
            return UINT8_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CLMTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //wlst Weather Types ,, Array
            return WLST.IsLoaded() ? &WLST->value7 : NULL;
        case 8: //wlst Weather Types ,, Array
            return WLST.IsLoaded() ? &WLST->value8 : NULL;
        case 9: //wlst Weather Types ,, Array
            return WLST.IsLoaded() ? &WLST->value9 : NULL;
        case 10: //fnam Sun Texture
            return FNAM.value;
        case 11: //gnam Sun Glare Texture
            return GNAM.value;
        case 12: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 13: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 14: //modt_p
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODT.value : NULL;
            return NULL;
        case 15: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 16: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value16 : NULL;
        case 17: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value17 : NULL;
        case 18: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD->value18 : NULL;
        case 19: //tnam TNAM ,, Struct
            return TNAM.IsLoaded() ? &TNAM->value19 : NULL;
        case 20: //tnam TNAM ,, Struct
            return TNAM.IsLoaded() ? &TNAM->value20 : NULL;
        case 21: //tnam TNAM ,, Struct
            return TNAM.IsLoaded() ? &TNAM->value21 : NULL;
        case 22: //tnam TNAM ,, Struct
            return TNAM.IsLoaded() ? &TNAM->value22 : NULL;
        case 23: //tnam TNAM ,, Struct
            return TNAM.IsLoaded() ? &TNAM->value23 : NULL;
        case 24: //tnam TNAM ,, Struct
            return TNAM.IsLoaded() ? &TNAM->value24 : NULL;
        default:
            return NULL;
        }
    }

bool CLMTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
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
        case 7: //wlst Weather Types ,, Array
            WLST.Load();
            WLST->value7 = *(FORMID *)FieldValue;
            return true;
        case 8: //wlst Weather Types ,, Array
            WLST.Load();
            WLST->value8 = *(SINT32 *)FieldValue;
            break;
        case 9: //wlst Weather Types ,, Array
            WLST.Load();
            WLST->value9 = *(FORMID *)FieldValue;
            return true;
        case 10: //fnam Sun Texture
            FNAM.Copy((STRING)FieldValue);
            break;
        case 11: //gnam Sun Glare Texture
            GNAM.Copy((STRING)FieldValue);
            break;
        case 12: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 13: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 14: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 15: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 16: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value16 = *(FORMID *)FieldValue;
            return true;
        case 17: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value17 = *(SINT32 *)FieldValue;
            break;
        case 18: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value18 = *(UINT8 *)FieldValue;
            break;
        case 19: //tnam TNAM ,, Struct
            TNAM.Load();
            TNAM->value19 = *(UINT8 *)FieldValue;
            break;
        case 20: //tnam TNAM ,, Struct
            TNAM.Load();
            TNAM->value20 = *(UINT8 *)FieldValue;
            break;
        case 21: //tnam TNAM ,, Struct
            TNAM.Load();
            TNAM->value21 = *(UINT8 *)FieldValue;
            break;
        case 22: //tnam TNAM ,, Struct
            TNAM.Load();
            TNAM->value22 = *(UINT8 *)FieldValue;
            break;
        case 23: //tnam TNAM ,, Struct
            TNAM.Load();
            TNAM->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //tnam TNAM ,, Struct
            TNAM.Load();
            TNAM->value24 = *(UINT8 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CLMTRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //wlst Weather Types ,, Array
            WLST.Unload();
            return;
        case 8: //wlst Weather Types ,, Array
            WLST.Unload();
            return;
        case 9: //wlst Weather Types ,, Array
            WLST.Unload();
            return;
        case 10: //fnam Sun Texture
            FNAM.Unload();
            return;
        case 11: //gnam Sun Glare Texture
            GNAM.Unload();
            return;
        case 12: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 13: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 14: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 15: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 16: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 17: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 18: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 19: //tnam TNAM ,, Struct
            TNAM.Unload();
            return;
        case 20: //tnam TNAM ,, Struct
            TNAM.Unload();
            return;
        case 21: //tnam TNAM ,, Struct
            TNAM.Unload();
            return;
        case 22: //tnam TNAM ,, Struct
            TNAM.Unload();
            return;
        case 23: //tnam TNAM ,, Struct
            TNAM.Unload();
            return;
        case 24: //tnam TNAM ,, Struct
            TNAM.Unload();
            return;
        default:
            return;
        }
    }
}