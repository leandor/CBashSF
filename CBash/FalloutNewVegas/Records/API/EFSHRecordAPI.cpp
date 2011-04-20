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
#include "..\EFSHRecord.h"

namespace FNV
{
UINT32 EFSHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //icon Fill Texture
            return ISTRING_FIELD;
        case 8: //ico2 Particle Shader Texture
            return ISTRING_FIELD;
        case 9: //nam7 Holes Texture
            return ISTRING_FIELD;
        case 10: //data DATA ,, Struct
            return UINT8_FIELD;
        case 11: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 12: //data DATA ,, Struct
            return UINT32_FIELD;
        case 13: //data DATA ,, Struct
            return UINT32_FIELD;
        case 14: //data DATA ,, Struct
            return UINT32_FIELD;
        case 15: //data DATA ,, Struct
            return UINT8_FIELD;
        case 16: //data DATA ,, Struct
            return UINT8_FIELD;
        case 17: //data DATA ,, Struct
            return UINT8_FIELD;
        case 18: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 19: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 20: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 21: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 22: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 23: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 24: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 25: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 26: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 27: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 28: //data DATA ,, Struct
            return UINT8_FIELD;
        case 29: //data DATA ,, Struct
            return UINT8_FIELD;
        case 30: //data DATA ,, Struct
            return UINT8_FIELD;
        case 31: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 32: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 33: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 34: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 35: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 36: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 37: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 38: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 39: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 40: //data DATA ,, Struct
            return UINT32_FIELD;
        case 41: //data DATA ,, Struct
            return UINT32_FIELD;
        case 42: //data DATA ,, Struct
            return UINT32_FIELD;
        case 43: //data DATA ,, Struct
            return UINT32_FIELD;
        case 44: //data DATA ,, Struct
            return UINT32_FIELD;
        case 45: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 46: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 47: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 48: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 49: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 50: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 51: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 52: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 53: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 54: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 55: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 56: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 57: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 58: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 59: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 60: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 61: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 62: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 63: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 64: //data DATA ,, Struct
            return UINT8_FIELD;
        case 65: //data DATA ,, Struct
            return UINT8_FIELD;
        case 66: //data DATA ,, Struct
            return UINT8_FIELD;
        case 67: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 68: //data DATA ,, Struct
            return UINT8_FIELD;
        case 69: //data DATA ,, Struct
            return UINT8_FIELD;
        case 70: //data DATA ,, Struct
            return UINT8_FIELD;
        case 71: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 72: //data DATA ,, Struct
            return UINT8_FIELD;
        case 73: //data DATA ,, Struct
            return UINT8_FIELD;
        case 74: //data DATA ,, Struct
            return UINT8_FIELD;
        case 75: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 76: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 77: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 78: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 79: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 80: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 81: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 82: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 83: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 84: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 85: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 86: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 87: //data DATA ,, Struct
            return FORMID_FIELD;
        case 88: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 89: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 90: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 91: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 92: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 93: //data DATA ,, Struct
            return UINT8_FIELD;
        case 94: //data DATA ,, Struct
            return UINT8_FIELD;
        case 95: //data DATA ,, Struct
            return UINT8_FIELD;
        case 96: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 97: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 98: //data DATA ,, Struct
            return UINT32_FIELD;
        case 99: //data DATA ,, Struct
            return UINT32_FIELD;
        case 100: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 101: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 102: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 103: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 104: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 105: //data DATA ,, Struct
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * EFSHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //icon Fill Texture
            return ICON.value;
        case 8: //ico2 Particle Shader Texture
            return ICO2.value;
        case 9: //nam7 Holes Texture
            return NAM7.value;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value10 : NULL;
        case 11: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value11[0] : NULL;
            return NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value13 : NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value15 : NULL;
        case 16: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value16 : NULL;
        case 17: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value17 : NULL;
        case 18: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value18[0] : NULL;
            return NULL;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value19 : NULL;
        case 20: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value20 : NULL;
        case 21: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value21 : NULL;
        case 22: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value22 : NULL;
        case 23: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value23 : NULL;
        case 24: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value24 : NULL;
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
        case 31: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value31[0] : NULL;
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
        case 54: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value54 : NULL;
        case 55: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value55 : NULL;
        case 56: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value56 : NULL;
        case 57: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value57 : NULL;
        case 58: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value58 : NULL;
        case 59: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value59 : NULL;
        case 60: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value60 : NULL;
        case 61: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value61 : NULL;
        case 62: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value62 : NULL;
        case 63: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value63 : NULL;
        case 64: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value64 : NULL;
        case 65: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value65 : NULL;
        case 66: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value66 : NULL;
        case 67: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value67[0] : NULL;
            return NULL;
        case 68: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value68 : NULL;
        case 69: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value69 : NULL;
        case 70: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value70 : NULL;
        case 71: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value71[0] : NULL;
            return NULL;
        case 72: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value72 : NULL;
        case 73: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value73 : NULL;
        case 74: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value74 : NULL;
        case 75: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value75[0] : NULL;
            return NULL;
        case 76: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value76 : NULL;
        case 77: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value77 : NULL;
        case 78: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value78 : NULL;
        case 79: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value79 : NULL;
        case 80: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value80 : NULL;
        case 81: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value81 : NULL;
        case 82: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value82 : NULL;
        case 83: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value83 : NULL;
        case 84: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value84 : NULL;
        case 85: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value85 : NULL;
        case 86: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value86 : NULL;
        case 87: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value87 : NULL;
        case 88: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value88 : NULL;
        case 89: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value89 : NULL;
        case 90: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value90 : NULL;
        case 91: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value91 : NULL;
        case 92: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value92 : NULL;
        case 93: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value93 : NULL;
        case 94: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value94 : NULL;
        case 95: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value95 : NULL;
        case 96: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value96[0] : NULL;
            return NULL;
        case 97: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value97 : NULL;
        case 98: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value98 : NULL;
        case 99: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value99 : NULL;
        case 100: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value100 : NULL;
        case 101: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value101 : NULL;
        case 102: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value102 : NULL;
        case 103: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value103 : NULL;
        case 104: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value104 : NULL;
        case 105: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value105 : NULL;
        default:
            return NULL;
        }
    }

bool EFSHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //icon Fill Texture
            ICON.Copy((STRING)FieldValue);
            break;
        case 8: //ico2 Particle Shader Texture
            ICO2.Copy((STRING)FieldValue);
            break;
        case 9: //nam7 Holes Texture
            NAM7.Copy((STRING)FieldValue);
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //data_p DATA ,, Struct
            if(ArraySize != 3)
                break;
            DATA.Load();
            DATA->value11[0] = ((UINT8 *)FieldValue)[0];
            DATA->value11[1] = ((UINT8 *)FieldValue)[1];
            DATA->value11[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->value12 = *(UINT32 *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->value13 = *(UINT32 *)FieldValue;
            break;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->value14 = *(UINT32 *)FieldValue;
            break;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->value15 = *(UINT8 *)FieldValue;
            break;
        case 16: //data DATA ,, Struct
            DATA.Load();
            DATA->value16 = *(UINT8 *)FieldValue;
            break;
        case 17: //data DATA ,, Struct
            DATA.Load();
            DATA->value17 = *(UINT8 *)FieldValue;
            break;
        case 18: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value18[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->value19 = *(FLOAT32 *)FieldValue;
            break;
        case 20: //data DATA ,, Struct
            DATA.Load();
            DATA->value20 = *(FLOAT32 *)FieldValue;
            break;
        case 21: //data DATA ,, Struct
            DATA.Load();
            DATA->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //data DATA ,, Struct
            DATA.Load();
            DATA->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //data DATA ,, Struct
            DATA.Load();
            DATA->value23 = *(FLOAT32 *)FieldValue;
            break;
        case 24: //data DATA ,, Struct
            DATA.Load();
            DATA->value24 = *(FLOAT32 *)FieldValue;
            break;
        case 25: //data DATA ,, Struct
            DATA.Load();
            DATA->value25 = *(FLOAT32 *)FieldValue;
            break;
        case 26: //data DATA ,, Struct
            DATA.Load();
            DATA->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //data DATA ,, Struct
            DATA.Load();
            DATA->value27 = *(FLOAT32 *)FieldValue;
            break;
        case 28: //data DATA ,, Struct
            DATA.Load();
            DATA->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //data DATA ,, Struct
            DATA.Load();
            DATA->value29 = *(UINT8 *)FieldValue;
            break;
        case 30: //data DATA ,, Struct
            DATA.Load();
            DATA->value30 = *(UINT8 *)FieldValue;
            break;
        case 31: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value31[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 32: //data DATA ,, Struct
            DATA.Load();
            DATA->value32 = *(FLOAT32 *)FieldValue;
            break;
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
            DATA->value35 = *(FLOAT32 *)FieldValue;
            break;
        case 36: //data DATA ,, Struct
            DATA.Load();
            DATA->value36 = *(FLOAT32 *)FieldValue;
            break;
        case 37: //data DATA ,, Struct
            DATA.Load();
            DATA->value37 = *(FLOAT32 *)FieldValue;
            break;
        case 38: //data DATA ,, Struct
            DATA.Load();
            DATA->value38 = *(FLOAT32 *)FieldValue;
            break;
        case 39: //data DATA ,, Struct
            DATA.Load();
            DATA->value39 = *(FLOAT32 *)FieldValue;
            break;
        case 40: //data DATA ,, Struct
            DATA.Load();
            DATA->value40 = *(UINT32 *)FieldValue;
            break;
        case 41: //data DATA ,, Struct
            DATA.Load();
            DATA->value41 = *(UINT32 *)FieldValue;
            break;
        case 42: //data DATA ,, Struct
            DATA.Load();
            DATA->value42 = *(UINT32 *)FieldValue;
            break;
        case 43: //data DATA ,, Struct
            DATA.Load();
            DATA->value43 = *(UINT32 *)FieldValue;
            break;
        case 44: //data DATA ,, Struct
            DATA.Load();
            DATA->value44 = *(UINT32 *)FieldValue;
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
            DATA->value47 = *(FLOAT32 *)FieldValue;
            break;
        case 48: //data DATA ,, Struct
            DATA.Load();
            DATA->value48 = *(FLOAT32 *)FieldValue;
            break;
        case 49: //data DATA ,, Struct
            DATA.Load();
            DATA->value49 = *(FLOAT32 *)FieldValue;
            break;
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
        case 54: //data DATA ,, Struct
            DATA.Load();
            DATA->value54 = *(FLOAT32 *)FieldValue;
            break;
        case 55: //data DATA ,, Struct
            DATA.Load();
            DATA->value55 = *(FLOAT32 *)FieldValue;
            break;
        case 56: //data DATA ,, Struct
            DATA.Load();
            DATA->value56 = *(FLOAT32 *)FieldValue;
            break;
        case 57: //data DATA ,, Struct
            DATA.Load();
            DATA->value57 = *(FLOAT32 *)FieldValue;
            break;
        case 58: //data DATA ,, Struct
            DATA.Load();
            DATA->value58 = *(FLOAT32 *)FieldValue;
            break;
        case 59: //data DATA ,, Struct
            DATA.Load();
            DATA->value59 = *(FLOAT32 *)FieldValue;
            break;
        case 60: //data DATA ,, Struct
            DATA.Load();
            DATA->value60 = *(FLOAT32 *)FieldValue;
            break;
        case 61: //data DATA ,, Struct
            DATA.Load();
            DATA->value61 = *(FLOAT32 *)FieldValue;
            break;
        case 62: //data DATA ,, Struct
            DATA.Load();
            DATA->value62 = *(FLOAT32 *)FieldValue;
            break;
        case 63: //data DATA ,, Struct
            DATA.Load();
            DATA->value63 = *(FLOAT32 *)FieldValue;
            break;
        case 64: //data DATA ,, Struct
            DATA.Load();
            DATA->value64 = *(UINT8 *)FieldValue;
            break;
        case 65: //data DATA ,, Struct
            DATA.Load();
            DATA->value65 = *(UINT8 *)FieldValue;
            break;
        case 66: //data DATA ,, Struct
            DATA.Load();
            DATA->value66 = *(UINT8 *)FieldValue;
            break;
        case 67: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value67[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 68: //data DATA ,, Struct
            DATA.Load();
            DATA->value68 = *(UINT8 *)FieldValue;
            break;
        case 69: //data DATA ,, Struct
            DATA.Load();
            DATA->value69 = *(UINT8 *)FieldValue;
            break;
        case 70: //data DATA ,, Struct
            DATA.Load();
            DATA->value70 = *(UINT8 *)FieldValue;
            break;
        case 71: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value71[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 72: //data DATA ,, Struct
            DATA.Load();
            DATA->value72 = *(UINT8 *)FieldValue;
            break;
        case 73: //data DATA ,, Struct
            DATA.Load();
            DATA->value73 = *(UINT8 *)FieldValue;
            break;
        case 74: //data DATA ,, Struct
            DATA.Load();
            DATA->value74 = *(UINT8 *)FieldValue;
            break;
        case 75: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value75[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 76: //data DATA ,, Struct
            DATA.Load();
            DATA->value76 = *(FLOAT32 *)FieldValue;
            break;
        case 77: //data DATA ,, Struct
            DATA.Load();
            DATA->value77 = *(FLOAT32 *)FieldValue;
            break;
        case 78: //data DATA ,, Struct
            DATA.Load();
            DATA->value78 = *(FLOAT32 *)FieldValue;
            break;
        case 79: //data DATA ,, Struct
            DATA.Load();
            DATA->value79 = *(FLOAT32 *)FieldValue;
            break;
        case 80: //data DATA ,, Struct
            DATA.Load();
            DATA->value80 = *(FLOAT32 *)FieldValue;
            break;
        case 81: //data DATA ,, Struct
            DATA.Load();
            DATA->value81 = *(FLOAT32 *)FieldValue;
            break;
        case 82: //data DATA ,, Struct
            DATA.Load();
            DATA->value82 = *(FLOAT32 *)FieldValue;
            break;
        case 83: //data DATA ,, Struct
            DATA.Load();
            DATA->value83 = *(FLOAT32 *)FieldValue;
            break;
        case 84: //data DATA ,, Struct
            DATA.Load();
            DATA->value84 = *(FLOAT32 *)FieldValue;
            break;
        case 85: //data DATA ,, Struct
            DATA.Load();
            DATA->value85 = *(FLOAT32 *)FieldValue;
            break;
        case 86: //data DATA ,, Struct
            DATA.Load();
            DATA->value86 = *(FLOAT32 *)FieldValue;
            break;
        case 87: //data DATA ,, Struct
            DATA.Load();
            DATA->value87 = *(FORMID *)FieldValue;
            return true;
        case 88: //data DATA ,, Struct
            DATA.Load();
            DATA->value88 = *(FLOAT32 *)FieldValue;
            break;
        case 89: //data DATA ,, Struct
            DATA.Load();
            DATA->value89 = *(FLOAT32 *)FieldValue;
            break;
        case 90: //data DATA ,, Struct
            DATA.Load();
            DATA->value90 = *(FLOAT32 *)FieldValue;
            break;
        case 91: //data DATA ,, Struct
            DATA.Load();
            DATA->value91 = *(FLOAT32 *)FieldValue;
            break;
        case 92: //data DATA ,, Struct
            DATA.Load();
            DATA->value92 = *(FLOAT32 *)FieldValue;
            break;
        case 93: //data DATA ,, Struct
            DATA.Load();
            DATA->value93 = *(UINT8 *)FieldValue;
            break;
        case 94: //data DATA ,, Struct
            DATA.Load();
            DATA->value94 = *(UINT8 *)FieldValue;
            break;
        case 95: //data DATA ,, Struct
            DATA.Load();
            DATA->value95 = *(UINT8 *)FieldValue;
            break;
        case 96: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value96[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 97: //data DATA ,, Struct
            DATA.Load();
            DATA->value97 = *(FLOAT32 *)FieldValue;
            break;
        case 98: //data DATA ,, Struct
            DATA.Load();
            DATA->value98 = *(UINT32 *)FieldValue;
            break;
        case 99: //data DATA ,, Struct
            DATA.Load();
            DATA->value99 = *(UINT32 *)FieldValue;
            break;
        case 100: //data DATA ,, Struct
            DATA.Load();
            DATA->value100 = *(FLOAT32 *)FieldValue;
            break;
        case 101: //data DATA ,, Struct
            DATA.Load();
            DATA->value101 = *(FLOAT32 *)FieldValue;
            break;
        case 102: //data DATA ,, Struct
            DATA.Load();
            DATA->value102 = *(FLOAT32 *)FieldValue;
            break;
        case 103: //data DATA ,, Struct
            DATA.Load();
            DATA->value103 = *(FLOAT32 *)FieldValue;
            break;
        case 104: //data DATA ,, Struct
            DATA.Load();
            DATA->value104 = *(FLOAT32 *)FieldValue;
            break;
        case 105: //data DATA ,, Struct
            DATA.Load();
            DATA->value105 = *(FLOAT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void EFSHRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //icon Fill Texture
            ICON.Unload();
            return;
        case 8: //ico2 Particle Shader Texture
            ICO2.Unload();
            return;
        case 9: //nam7 Holes Texture
            NAM7.Unload();
            return;
        case 10: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 11: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 12: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 13: //data DATA ,, Struct
            DATA.Unload();
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
        case 18: //data_p DATA ,, Struct
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
            DATA.Unload();
            return;
        case 23: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 24: //data DATA ,, Struct
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
        case 31: //data_p DATA ,, Struct
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
        case 54: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 55: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 56: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 57: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 58: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 59: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 60: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 61: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 62: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 63: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 64: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 65: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 66: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 67: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 68: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 69: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 70: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 71: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 72: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 73: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 74: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 75: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 76: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 77: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 78: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 79: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 80: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 81: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 82: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 83: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 84: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 85: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 86: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 87: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 88: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 89: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 90: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 91: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 92: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 93: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 94: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 95: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 96: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 97: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 98: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 99: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 100: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 101: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 102: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 103: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 104: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 105: //data DATA ,, Struct
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}