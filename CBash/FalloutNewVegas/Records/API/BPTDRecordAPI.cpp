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
#include "..\BPTDRecord.h"

namespace FNV
{
UINT32 BPTDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //modl Model Filename
            return STRING_FIELD;
        case 8: //modb_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 9: //modt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //mods Alternate Textures
            return ISTRING_FIELD;
        case 11: //mods Alternate Textures
            return FORMID_FIELD;
        case 12: //mods Alternate Textures
            return SINT32_FIELD;
        case 13: //modd FaceGen Model Flags
            return UINT8_FIELD;
        case 14: //bptn Part Name
            return ISTRING_FIELD;
        case 15: //bpnn Part Node
            return ISTRING_FIELD;
        case 16: //bpnt VATS Target
            return ISTRING_FIELD;
        case 17: //bpni IK Data - Start Node
            return ISTRING_FIELD;
        case 18: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 19: //bpnd BPND ,, Struct
            return UINT8_FIELD;
        case 20: //bpnd BPND ,, Struct
            return UINT8_FIELD;
        case 21: //bpnd BPND ,, Struct
            return UINT8_FIELD;
        case 22: //bpnd BPND ,, Struct
            return UNPARSED_FIELD;
        case 23: //bpnd BPND ,, Struct
            return UINT8_FIELD;
        case 24: //bpnd BPND ,, Struct
            return UINT8_FIELD;
        case 25: //bpnd BPND ,, Struct
            return UINT16_FIELD;
        case 26: //bpnd BPND ,, Struct
            return FORMID_FIELD;
        case 27: //bpnd BPND ,, Struct
            return FORMID_FIELD;
        case 28: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 29: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 30: //bpnd BPND ,, Struct
            return SINT32_FIELD;
        case 31: //bpnd BPND ,, Struct
            return FORMID_FIELD;
        case 32: //bpnd BPND ,, Struct
            return FORMID_FIELD;
        case 33: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 34: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 35: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 36: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 37: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 38: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 39: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 40: //bpnd BPND ,, Struct
            return FORMID_FIELD;
        case 41: //bpnd BPND ,, Struct
            return FORMID_FIELD;
        case 42: //bpnd BPND ,, Struct
            return UINT8_FIELD;
        case 43: //bpnd BPND ,, Struct
            return UINT8_FIELD;
        case 44: //bpnd_p BPND ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 45: //bpnd BPND ,, Struct
            return FLOAT32_FIELD;
        case 46: //nam1 Limb Replacement Model
            return ISTRING_FIELD;
        case 47: //nam4 Gore Effects - Target Bone
            return ISTRING_FIELD;
        case 48: //nam5_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM5.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 49: //raga Ragdoll
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * BPTDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //modl Model Filename
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 8: //modb_p Unknown
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODB.value : NULL;
            return NULL;
        case 9: //modt_p Texture Files Hashes
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODT.value : NULL;
            return NULL;
        case 10: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 11: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value11 : NULL;
        case 12: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value12 : NULL;
        case 13: //modd FaceGen Model Flags
            return MODL.IsLoaded() ? &MODL->MODD->value13 : NULL;
        case 14: //bptn Part Name
            return BPTN.value;
        case 15: //bpnn Part Node
            return BPNN.value;
        case 16: //bpnt VATS Target
            return BPNT.value;
        case 17: //bpni IK Data - Start Node
            return BPNI.value;
        case 18: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value18 : NULL;
        case 19: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value19 : NULL;
        case 20: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value20 : NULL;
        case 21: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value21 : NULL;
        case 22: //bpnd BPND ,, Struct
            return UNPARSEDGET_FIELD22;
        case 23: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value23 : NULL;
        case 24: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value24 : NULL;
        case 25: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value25 : NULL;
        case 26: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value26 : NULL;
        case 27: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value27 : NULL;
        case 28: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value28 : NULL;
        case 29: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value29 : NULL;
        case 30: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value30 : NULL;
        case 31: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value31 : NULL;
        case 32: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value32 : NULL;
        case 33: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value33 : NULL;
        case 34: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value34 : NULL;
        case 35: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value35 : NULL;
        case 36: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value36 : NULL;
        case 37: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value37 : NULL;
        case 38: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value38 : NULL;
        case 39: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value39 : NULL;
        case 40: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value40 : NULL;
        case 41: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value41 : NULL;
        case 42: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value42 : NULL;
        case 43: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value43 : NULL;
        case 44: //bpnd_p BPND ,, Struct
            *FieldValues = BPND.IsLoaded() ? &BPND->value44[0] : NULL;
            return NULL;
        case 45: //bpnd BPND ,, Struct
            return BPND.IsLoaded() ? &BPND->value45 : NULL;
        case 46: //nam1 Limb Replacement Model
            return NAM1.value;
        case 47: //nam4 Gore Effects - Target Bone
            return NAM4.value;
        case 48: //nam5_p Texture Files Hashes
            *FieldValues = NAM5.value;
            return NULL;
        case 49: //raga Ragdoll
            return RAGA.IsLoaded() ? &RAGA->value49 : NULL;
        default:
            return NULL;
        }
    }

bool BPTDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //modl Model Filename
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 8: //modb_p Unknown
            MODL.Load();
            MODL->MODB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //modt_p Texture Files Hashes
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
        case 13: //modd FaceGen Model Flags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value13 = *(UINT8 *)FieldValue;
            break;
        case 14: //bptn Part Name
            BPTN.Copy((STRING)FieldValue);
            break;
        case 15: //bpnn Part Node
            BPNN.Copy((STRING)FieldValue);
            break;
        case 16: //bpnt VATS Target
            BPNT.Copy((STRING)FieldValue);
            break;
        case 17: //bpni IK Data - Start Node
            BPNI.Copy((STRING)FieldValue);
            break;
        case 18: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value18 = *(FLOAT32 *)FieldValue;
            break;
        case 19: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value19 = *(UINT8 *)FieldValue;
            break;
        case 20: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value20 = *(UINT8 *)FieldValue;
            break;
        case 21: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value21 = *(UINT8 *)FieldValue;
            break;
        case 22: //bpnd BPND ,, Struct
            return UNPARSEDGET_FIELD22;
        case 23: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value24 = *(UINT8 *)FieldValue;
            break;
        case 25: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value25 = *(UINT16 *)FieldValue;
            break;
        case 26: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value26 = *(FORMID *)FieldValue;
            return true;
        case 27: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value27 = *(FORMID *)FieldValue;
            return true;
        case 28: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value28 = *(FLOAT32 *)FieldValue;
            break;
        case 29: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value29 = *(FLOAT32 *)FieldValue;
            break;
        case 30: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value30 = *(SINT32 *)FieldValue;
            break;
        case 31: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value31 = *(FORMID *)FieldValue;
            return true;
        case 32: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value32 = *(FORMID *)FieldValue;
            return true;
        case 33: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value33 = *(FLOAT32 *)FieldValue;
            break;
        case 34: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value35 = *(FLOAT32 *)FieldValue;
            break;
        case 36: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value36 = *(FLOAT32 *)FieldValue;
            break;
        case 37: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value37 = *(FLOAT32 *)FieldValue;
            break;
        case 38: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value38 = *(FLOAT32 *)FieldValue;
            break;
        case 39: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value39 = *(FLOAT32 *)FieldValue;
            break;
        case 40: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value40 = *(FORMID *)FieldValue;
            return true;
        case 41: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value41 = *(FORMID *)FieldValue;
            return true;
        case 42: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value42 = *(UINT8 *)FieldValue;
            break;
        case 43: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value43 = *(UINT8 *)FieldValue;
            break;
        case 44: //bpnd_p BPND ,, Struct
            if(ArraySize != 2)
                break;
            BPND.Load();
            BPND->value44[0] = ((UINT8 *)FieldValue)[0];
            BPND->value44[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 45: //bpnd BPND ,, Struct
            BPND.Load();
            BPND->value45 = *(FLOAT32 *)FieldValue;
            break;
        case 46: //nam1 Limb Replacement Model
            NAM1.Copy((STRING)FieldValue);
            break;
        case 47: //nam4 Gore Effects - Target Bone
            NAM4.Copy((STRING)FieldValue);
            break;
        case 48: //nam5_p Texture Files Hashes
            NAM5.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 49: //raga Ragdoll
            RAGA.Load();
            RAGA->value49 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void BPTDRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //modl Model Filename
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 8: //modb_p Unknown
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 9: //modt_p Texture Files Hashes
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
        case 13: //modd FaceGen Model Flags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 14: //bptn Part Name
            BPTN.Unload();
            return;
        case 15: //bpnn Part Node
            BPNN.Unload();
            return;
        case 16: //bpnt VATS Target
            BPNT.Unload();
            return;
        case 17: //bpni IK Data - Start Node
            BPNI.Unload();
            return;
        case 18: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 19: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 20: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 21: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 22: //bpnd BPND ,, Struct
            return UNPARSEDDEL_FIELD22;
        case 23: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 24: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 25: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 26: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 27: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 28: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 29: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 30: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 31: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 32: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 33: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 34: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 35: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 36: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 37: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 38: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 39: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 40: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 41: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 42: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 43: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 44: //bpnd_p BPND ,, Struct
            BPND.Unload();
            return;
        case 45: //bpnd BPND ,, Struct
            BPND.Unload();
            return;
        case 46: //nam1 Limb Replacement Model
            NAM1.Unload();
            return;
        case 47: //nam4 Gore Effects - Target Bone
            NAM4.Unload();
            return;
        case 48: //nam5_p Texture Files Hashes
            NAM5.Unload();
            return;
        case 49: //raga Ragdoll
            RAGA.Unload();
            return;
        default:
            return;
        }
    }
}