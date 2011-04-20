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
#include "..\IPCTRecord.h"

namespace FNV
{
UINT32 IPCTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
            return STRING_FIELD;
        case 11: //mods Alternate Textures
            return FORMID_FIELD;
        case 12: //mods Alternate Textures
            return SINT32_FIELD;
        case 13: //modd FaceGen Model Flags
            return UINT8_FIELD;
        case 14: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 15: //data DATA ,, Struct
            return UINT32_FIELD;
        case 16: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 17: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 18: //data DATA ,, Struct
            return UINT32_FIELD;
        case 19: //data DATA ,, Struct
            return UINT32_FIELD;
        case 20: //dodt Decal Data
            return FLOAT32_FIELD;
        case 21: //dodt Decal Data
            return FLOAT32_FIELD;
        case 22: //dodt Decal Data
            return FLOAT32_FIELD;
        case 23: //dodt Decal Data
            return FLOAT32_FIELD;
        case 24: //dodt Decal Data
            return FLOAT32_FIELD;
        case 25: //dodt Decal Data
            return FLOAT32_FIELD;
        case 26: //dodt Decal Data
            return FLOAT32_FIELD;
        case 27: //dodt Decal Data
            return UINT8_FIELD;
        case 28: //dodt Decal Data
            return UINT8_FIELD;
        case 29: //dodt_p Decal Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 30: //dodt Decal Data
            return UINT8_FIELD;
        case 31: //dodt Decal Data
            return UINT8_FIELD;
        case 32: //dodt Decal Data
            return UINT8_FIELD;
        case 33: //dodt_p Decal Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 34: //dnam Texture Set
            return FORMID_FIELD;
        case 35: //snam Sound 1
            return FORMID_FIELD;
        case 36: //nam1 Sound 2
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * IPCTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value15 : NULL;
        case 16: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value16 : NULL;
        case 17: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value17 : NULL;
        case 18: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value18 : NULL;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value19 : NULL;
        case 20: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value20 : NULL;
        case 21: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value21 : NULL;
        case 22: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value22 : NULL;
        case 23: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value23 : NULL;
        case 24: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value24 : NULL;
        case 25: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value25 : NULL;
        case 26: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value26 : NULL;
        case 27: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value27 : NULL;
        case 28: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value28 : NULL;
        case 29: //dodt_p Decal Data
            *FieldValues = DODT.IsLoaded() ? &DODT->value29[0] : NULL;
            return NULL;
        case 30: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value30 : NULL;
        case 31: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value31 : NULL;
        case 32: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value32 : NULL;
        case 33: //dodt_p Decal Data
            *FieldValues = DODT.IsLoaded() ? &DODT->value33[0] : NULL;
            return NULL;
        case 34: //dnam Texture Set
            return DNAM.IsLoaded() ? &DNAM->value34 : NULL;
        case 35: //snam Sound 1
            return SNAM.IsLoaded() ? &SNAM->value35 : NULL;
        case 36: //nam1 Sound 2
            return NAM1.IsLoaded() ? &NAM1->value36 : NULL;
        default:
            return NULL;
        }
    }

bool IPCTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->value15 = *(UINT32 *)FieldValue;
            break;
        case 16: //data DATA ,, Struct
            DATA.Load();
            DATA->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //data DATA ,, Struct
            DATA.Load();
            DATA->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //data DATA ,, Struct
            DATA.Load();
            DATA->value18 = *(UINT32 *)FieldValue;
            break;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->value19 = *(UINT32 *)FieldValue;
            break;
        case 20: //dodt Decal Data
            DODT.Load();
            DODT->value20 = *(FLOAT32 *)FieldValue;
            break;
        case 21: //dodt Decal Data
            DODT.Load();
            DODT->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //dodt Decal Data
            DODT.Load();
            DODT->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //dodt Decal Data
            DODT.Load();
            DODT->value23 = *(FLOAT32 *)FieldValue;
            break;
        case 24: //dodt Decal Data
            DODT.Load();
            DODT->value24 = *(FLOAT32 *)FieldValue;
            break;
        case 25: //dodt Decal Data
            DODT.Load();
            DODT->value25 = *(FLOAT32 *)FieldValue;
            break;
        case 26: //dodt Decal Data
            DODT.Load();
            DODT->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //dodt Decal Data
            DODT.Load();
            DODT->value27 = *(UINT8 *)FieldValue;
            break;
        case 28: //dodt Decal Data
            DODT.Load();
            DODT->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //dodt_p Decal Data
            if(ArraySize != 2)
                break;
            DODT.Load();
            DODT->value29[0] = ((UINT8 *)FieldValue)[0];
            DODT->value29[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 30: //dodt Decal Data
            DODT.Load();
            DODT->value30 = *(UINT8 *)FieldValue;
            break;
        case 31: //dodt Decal Data
            DODT.Load();
            DODT->value31 = *(UINT8 *)FieldValue;
            break;
        case 32: //dodt Decal Data
            DODT.Load();
            DODT->value32 = *(UINT8 *)FieldValue;
            break;
        case 33: //dodt_p Decal Data
            if(ArraySize != 1)
                break;
            DODT.Load();
            DODT->value33[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 34: //dnam Texture Set
            DNAM.Load();
            DNAM->value34 = *(FORMID *)FieldValue;
            return true;
        case 35: //snam Sound 1
            SNAM.Load();
            SNAM->value35 = *(FORMID *)FieldValue;
            return true;
        case 36: //nam1 Sound 2
            NAM1.Load();
            NAM1->value36 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void IPCTRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 14: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 17: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 18: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 19: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 20: //dodt Decal Data
            DODT.Unload();
            return;
        case 21: //dodt Decal Data
            DODT.Unload();
            return;
        case 22: //dodt Decal Data
            DODT.Unload();
            return;
        case 23: //dodt Decal Data
            DODT.Unload();
            return;
        case 24: //dodt Decal Data
            DODT.Unload();
            return;
        case 25: //dodt Decal Data
            DODT.Unload();
            return;
        case 26: //dodt Decal Data
            DODT.Unload();
            return;
        case 27: //dodt Decal Data
            DODT.Unload();
            return;
        case 28: //dodt Decal Data
            DODT.Unload();
            return;
        case 29: //dodt_p Decal Data
            DODT.Unload();
            return;
        case 30: //dodt Decal Data
            DODT.Unload();
            return;
        case 31: //dodt Decal Data
            DODT.Unload();
            return;
        case 32: //dodt Decal Data
            DODT.Unload();
            return;
        case 33: //dodt_p Decal Data
            DODT.Unload();
            return;
        case 34: //dnam Texture Set
            DNAM.Unload();
            return;
        case 35: //snam Sound 1
            SNAM.Unload();
            return;
        case 36: //nam1 Sound 2
            NAM1.Unload();
            return;
        default:
            return;
        }
    }
}