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
#include "..\PROJRecord.h"

namespace FNV
{
UINT32 PROJRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //boundX
            return SINT16_FIELD;
        case 8: //boundY
            return SINT16_FIELD;
        case 9: //boundZ
            return SINT16_FIELD;
        case 10: //full Name
            return STRING_FIELD;
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
            return ISTRING_FIELD;
        case 15: //mods Alternate Textures
            return FORMID_FIELD;
        case 16: //mods Alternate Textures
            return SINT32_FIELD;
        case 17: //modd FaceGen Model Flags
            return UINT8_FIELD;
        case 18: //dest Header
            return SINT32_FIELD;
        case 19: //dest Header
            return UINT8_FIELD;
        case 20: //dest Header
            return UINT8_FIELD;
        case 21: //dest_p Header
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 22: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 23: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 24: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 25: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 26: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 27: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 28: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 29: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 30: //dmdl Model Filename
            return ISTRING_FIELD;
        case 31: //dmdt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DMDT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 32: //data DATA ,, Struct
            return UINT16_FIELD;
        case 33: //data DATA ,, Struct
            return UINT16_FIELD;
        case 34: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 35: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 36: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 37: //data DATA ,, Struct
            return FORMID_FIELD;
        case 38: //data DATA ,, Struct
            return FORMID_FIELD;
        case 39: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 40: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 41: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 42: //data DATA ,, Struct
            return FORMID_FIELD;
        case 43: //data DATA ,, Struct
            return FORMID_FIELD;
        case 44: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 45: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 46: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 47: //data DATA ,, Struct
            return FORMID_FIELD;
        case 48: //data DATA ,, Struct
            return FORMID_FIELD;
        case 49: //data DATA ,, Struct
            return FORMID_FIELD;
        case 50: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 51: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 52: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 53: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 54: //nam1 Model Filename
            return ISTRING_FIELD;
        case 55: //nam2_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM2.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 56: //vnam Sound Level
            return UINT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * PROJRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 10: //full Name
            return FULL.value;
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
        case 18: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value18 : NULL;
        case 19: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value19 : NULL;
        case 20: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value20 : NULL;
        case 21: //dest_p Header
            *FieldValues = DEST.IsLoaded() ? &DEST->DEST->value21[0] : NULL;
            return NULL;
        case 22: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value22 : NULL;
        case 23: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value23 : NULL;
        case 24: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value24 : NULL;
        case 25: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value25 : NULL;
        case 26: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value26 : NULL;
        case 27: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value27 : NULL;
        case 28: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value28 : NULL;
        case 29: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value29 : NULL;
        case 30: //dmdl Model Filename
            return DEST.IsLoaded() ? DEST->DMDL.value : NULL;
        case 31: //dmdt_p Texture Files Hashes
            *FieldValues = (DEST.IsLoaded()) ? DEST->DMDT.value : NULL;
            return NULL;
        case 32: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value32 : NULL;
        case 33: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value33 : NULL;
        case 34: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value34 : NULL;
        case 35: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value35 : NULL;
        case 36: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value36 : NULL;
        case 37: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value37 : NULL;
        case 38: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value38 : NULL;
        case 39: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value39 : NULL;
        case 40: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value40 : NULL;
        case 41: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value41 : NULL;
        case 42: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value42 : NULL;
        case 43: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value43 : NULL;
        case 44: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value44 : NULL;
        case 45: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value45 : NULL;
        case 46: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value46 : NULL;
        case 47: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value47 : NULL;
        case 48: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value48 : NULL;
        case 49: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value49 : NULL;
        case 50: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value50 : NULL;
        case 51: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value51 : NULL;
        case 52: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value52 : NULL;
        case 53: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value53 : NULL;
        case 54: //nam1 Model Filename
            return NAM1.value;
        case 55: //nam2_p Texture Files Hashes
            *FieldValues = NAM2.value;
            return NULL;
        case 56: //vnam Sound Level
            return VNAM.IsLoaded() ? &VNAM->value56 : NULL;
        default:
            return NULL;
        }
    }

bool PROJRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 10: //full Name
            FULL.Copy((STRING)FieldValue);
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
        case 18: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value18 = *(SINT32 *)FieldValue;
            break;
        case 19: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value19 = *(UINT8 *)FieldValue;
            break;
        case 20: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value20 = *(UINT8 *)FieldValue;
            break;
        case 21: //dest_p Header
            if(ArraySize != 2)
                break;
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value21[0] = ((UINT8 *)FieldValue)[0];
            DEST->DEST->value21[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 22: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value22 = *(UINT8 *)FieldValue;
            break;
        case 23: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value24 = *(UINT8 *)FieldValue;
            break;
        case 25: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value25 = *(UINT8 *)FieldValue;
            break;
        case 26: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value26 = *(SINT32 *)FieldValue;
            break;
        case 27: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value27 = *(FORMID *)FieldValue;
            return true;
        case 28: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value28 = *(FORMID *)FieldValue;
            return true;
        case 29: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value29 = *(SINT32 *)FieldValue;
            break;
        case 30: //dmdl Model Filename
            DEST.Load();
            DEST->DMDL.Copy((STRING)FieldValue);
            break;
        case 31: //dmdt_p Texture Files Hashes
            DEST.Load();
            DEST->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 32: //data DATA ,, Struct
            DATA.Load();
            DATA->value32 = *(UINT16 *)FieldValue;
            break;
        case 33: //data DATA ,, Struct
            DATA.Load();
            DATA->value33 = *(UINT16 *)FieldValue;
            break;
        case 34: //data DATA ,, Struct
            DATA.Load();
            DATA->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //data DATA ,, Struct
            DATA.Load();
            DATA->value35 = *(FLOAT32 *)FieldValue;
            break;
        case 36: //data DATA ,, Struct
            DATA.Load();
            DATA->value36 = *(FLOAT32 *)FieldValue;
            break;
        case 37: //data DATA ,, Struct
            DATA.Load();
            DATA->value37 = *(FORMID *)FieldValue;
            return true;
        case 38: //data DATA ,, Struct
            DATA.Load();
            DATA->value38 = *(FORMID *)FieldValue;
            return true;
        case 39: //data DATA ,, Struct
            DATA.Load();
            DATA->value39 = *(FLOAT32 *)FieldValue;
            break;
        case 40: //data DATA ,, Struct
            DATA.Load();
            DATA->value40 = *(FLOAT32 *)FieldValue;
            break;
        case 41: //data DATA ,, Struct
            DATA.Load();
            DATA->value41 = *(FLOAT32 *)FieldValue;
            break;
        case 42: //data DATA ,, Struct
            DATA.Load();
            DATA->value42 = *(FORMID *)FieldValue;
            return true;
        case 43: //data DATA ,, Struct
            DATA.Load();
            DATA->value43 = *(FORMID *)FieldValue;
            return true;
        case 44: //data DATA ,, Struct
            DATA.Load();
            DATA->value44 = *(FLOAT32 *)FieldValue;
            break;
        case 45: //data DATA ,, Struct
            DATA.Load();
            DATA->value45 = *(FLOAT32 *)FieldValue;
            break;
        case 46: //data DATA ,, Struct
            DATA.Load();
            DATA->value46 = *(FLOAT32 *)FieldValue;
            break;
        case 47: //data DATA ,, Struct
            DATA.Load();
            DATA->value47 = *(FORMID *)FieldValue;
            return true;
        case 48: //data DATA ,, Struct
            DATA.Load();
            DATA->value48 = *(FORMID *)FieldValue;
            return true;
        case 49: //data DATA ,, Struct
            DATA.Load();
            DATA->value49 = *(FORMID *)FieldValue;
            return true;
        case 50: //data DATA ,, Struct
            DATA.Load();
            DATA->value50 = *(FLOAT32 *)FieldValue;
            break;
        case 51: //data DATA ,, Struct
            DATA.Load();
            DATA->value51 = *(FLOAT32 *)FieldValue;
            break;
        case 52: //data DATA ,, Struct
            DATA.Load();
            DATA->value52 = *(FLOAT32 *)FieldValue;
            break;
        case 53: //data DATA ,, Struct
            DATA.Load();
            DATA->value53 = *(FLOAT32 *)FieldValue;
            break;
        case 54: //nam1 Model Filename
            NAM1.Copy((STRING)FieldValue);
            break;
        case 55: //nam2_p Texture Files Hashes
            NAM2.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 56: //vnam Sound Level
            VNAM.Load();
            VNAM->value56 = *(UINT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void PROJRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 10: //full Name
            FULL.Unload();
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
        case 18: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 19: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 20: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 21: //dest_p Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 22: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 23: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 24: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 25: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 26: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 27: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 28: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 29: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 30: //dmdl Model Filename
            if(DEST.IsLoaded())
                DEST->DMDL.Unload();
            return;
        case 31: //dmdt_p Texture Files Hashes
            if(DEST.IsLoaded())
                DEST->DMDT.Unload();
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
            DATA.Unload();
            return;
        case 37: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 38: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 39: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 40: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 41: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 42: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 43: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 44: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 45: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 46: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 47: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 48: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 49: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 50: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 51: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 52: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 53: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 54: //nam1 Model Filename
            NAM1.Unload();
            return;
        case 55: //nam2_p Texture Files Hashes
            NAM2.Unload();
            return;
        case 56: //vnam Sound Level
            VNAM.Unload();
            return;
        default:
            return;
        }
    }
}