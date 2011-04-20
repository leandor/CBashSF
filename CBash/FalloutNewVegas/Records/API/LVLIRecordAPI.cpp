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
#include "..\LVLIRecord.h"

namespace FNV
{
UINT32 LVLIRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //obnd Object Bounds
            return SINT16_FIELD;
        case 8: //obnd Object Bounds
            return SINT16_FIELD;
        case 9: //obnd Object Bounds
            return SINT16_FIELD;
        case 10: //lvld Chance none
            return UINT8_FIELD;
        case 11: //lvlf Flags
            return UINT8_FIELD;
        case 12: //lvlo LVLO ,, Struct
            return SINT16_FIELD;
        case 13: //lvlo_p LVLO ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //lvlo LVLO ,, Struct
            return FORMID_FIELD;
        case 15: //lvlo LVLO ,, Struct
            return SINT16_FIELD;
        case 16: //lvlo_p LVLO ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 17: //coed Extra Data
            return FORMID_FIELD;
        case 18: //coed_p Extra Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 19: //modl Model Filename
            return STRING_FIELD;
        case 20: //modb_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 21: //modt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 22: //mods Alternate Textures
            return STRING_FIELD;
        case 23: //mods Alternate Textures
            return FORMID_FIELD;
        case 24: //mods Alternate Textures
            return SINT32_FIELD;
        case 25: //modd FaceGen Model Flags
            return UINT8_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LVLIRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value7 : NULL;
        case 8: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value8 : NULL;
        case 9: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value9 : NULL;
        case 10: //lvld Chance none
            return LVLD.IsLoaded() ? &LVLD->value10 : NULL;
        case 11: //lvlf Flags
            return LVLF.IsLoaded() ? &LVLF->value11 : NULL;
        case 12: //lvlo LVLO ,, Struct
            return LVLO.IsLoaded() ? &LVLO->value12 : NULL;
        case 13: //lvlo_p LVLO ,, Struct
            *FieldValues = LVLO.IsLoaded() ? &LVLO->value13[0] : NULL;
            return NULL;
        case 14: //lvlo LVLO ,, Struct
            return LVLO.IsLoaded() ? &LVLO->value14 : NULL;
        case 15: //lvlo LVLO ,, Struct
            return LVLO.IsLoaded() ? &LVLO->value15 : NULL;
        case 16: //lvlo_p LVLO ,, Struct
            *FieldValues = LVLO.IsLoaded() ? &LVLO->value16[0] : NULL;
            return NULL;
        case 17: //coed Extra Data
            return COED.IsLoaded() ? &COED->value17 : NULL;
        case 18: //coed_p Extra Data
            *FieldValues = COED.IsLoaded() ? &COED->value18[0] : NULL;
            return NULL;
        case 19: //modl Model Filename
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 20: //modb_p Unknown
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODB.value : NULL;
            return NULL;
        case 21: //modt_p Texture Files Hashes
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODT.value : NULL;
            return NULL;
        case 22: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 23: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value23 : NULL;
        case 24: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value24 : NULL;
        case 25: //modd FaceGen Model Flags
            return MODL.IsLoaded() ? &MODL->MODD->value25 : NULL;
        default:
            return NULL;
        }
    }

bool LVLIRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value7 = *(SINT16 *)FieldValue;
            break;
        case 8: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value8 = *(SINT16 *)FieldValue;
            break;
        case 9: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value9 = *(SINT16 *)FieldValue;
            break;
        case 10: //lvld Chance none
            LVLD.Load();
            LVLD->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //lvlf Flags
            LVLF.Load();
            LVLF->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //lvlo LVLO ,, Struct
            LVLO.Load();
            LVLO->value12 = *(SINT16 *)FieldValue;
            break;
        case 13: //lvlo_p LVLO ,, Struct
            if(ArraySize != 2)
                break;
            LVLO.Load();
            LVLO->value13[0] = ((UINT8 *)FieldValue)[0];
            LVLO->value13[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 14: //lvlo LVLO ,, Struct
            LVLO.Load();
            LVLO->value14 = *(FORMID *)FieldValue;
            return true;
        case 15: //lvlo LVLO ,, Struct
            LVLO.Load();
            LVLO->value15 = *(SINT16 *)FieldValue;
            break;
        case 16: //lvlo_p LVLO ,, Struct
            if(ArraySize != 2)
                break;
            LVLO.Load();
            LVLO->value16[0] = ((UINT8 *)FieldValue)[0];
            LVLO->value16[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 17: //coed Extra Data
            COED.Load();
            COED->value17 = *(FORMID *)FieldValue;
            return true;
        case 18: //coed_p Extra Data
            if(ArraySize != 4)
                break;
            COED.Load();
            COED->value18[0] = ((UINT8 *)FieldValue)[0];
            COED->value18[1] = ((UINT8 *)FieldValue)[1];
            COED->value18[2] = ((UINT8 *)FieldValue)[2];
            COED->value18[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 19: //modl Model Filename
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 20: //modb_p Unknown
            MODL.Load();
            MODL->MODB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 21: //modt_p Texture Files Hashes
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 22: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 23: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value23 = *(FORMID *)FieldValue;
            return true;
        case 24: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value24 = *(SINT32 *)FieldValue;
            break;
        case 25: //modd FaceGen Model Flags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value25 = *(UINT8 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void LVLIRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 8: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 9: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 10: //lvld Chance none
            LVLD.Unload();
            return;
        case 11: //lvlf Flags
            LVLF.Unload();
            return;
        case 12: //lvlo LVLO ,, Struct
            LVLO.Unload();
            return;
        case 13: //lvlo_p LVLO ,, Struct
            LVLO.Unload();
            return;
        case 14: //lvlo LVLO ,, Struct
            LVLO.Unload();
            return;
        case 15: //lvlo LVLO ,, Struct
            LVLO.Unload();
            return;
        case 16: //lvlo_p LVLO ,, Struct
            LVLO.Unload();
            return;
        case 17: //coed Extra Data
            COED.Unload();
            return;
        case 18: //coed_p Extra Data
            COED.Unload();
            return;
        case 19: //modl Model Filename
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 20: //modb_p Unknown
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 21: //modt_p Texture Files Hashes
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 22: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 23: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 24: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 25: //modd FaceGen Model Flags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        default:
            return;
        }
    }
}