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
#include "..\WATRRecord.h"

namespace FNV
{
UINT32 WATRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //full Name
            return STRING_FIELD;
        case 8: //nnam Noise Map
            return ISTRING_FIELD;
        case 9: //anam Opacity
            return UINT8_FIELD;
        case 10: //fnam Flags
            return UINT8_FIELD;
        case 11: //mnam Material ID
            return ISTRING_FIELD;
        case 12: //snam Sound
            return FORMID_FIELD;
        case 13: //xnam Actor Effect
            return FORMID_FIELD;
        case 14: //data Damage
            return UINT16_FIELD;
        case 15: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 16: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 17: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 18: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 19: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 20: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 21: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 22: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 23: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 24: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 25: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 26: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 27: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 28: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 29: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 30: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 31: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 32: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 33: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 34: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 35: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 36: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 37: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 38: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 39: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 40: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 41: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 42: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 43: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 44: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 45: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 46: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 47: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 48: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 49: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 50: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 51: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 52: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 53: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 54: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 55: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 56: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 57: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 58: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 59: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 60: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 61: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 62: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 63: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 64: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 65: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 66: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 67: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 68: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 69: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 70: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 71: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 72: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 73: //gnam GNAM ,, Struct
            return FORMID_FIELD;
        case 74: //gnam GNAM ,, Struct
            return FORMID_FIELD;
        case 75: //gnam GNAM ,, Struct
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * WATRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //full Name
            return FULL.value;
        case 8: //nnam Noise Map
            return NNAM.value;
        case 9: //anam Opacity
            return ANAM.IsLoaded() ? &ANAM->value9 : NULL;
        case 10: //fnam Flags
            return FNAM.IsLoaded() ? &FNAM->value10 : NULL;
        case 11: //mnam Material ID
            return MNAM.value;
        case 12: //snam Sound
            return SNAM.IsLoaded() ? &SNAM->value12 : NULL;
        case 13: //xnam Actor Effect
            return XNAM.IsLoaded() ? &XNAM->value13 : NULL;
        case 14: //data Damage
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value15 : NULL;
        case 16: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value16 : NULL;
        case 17: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value17 : NULL;
        case 18: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value18 : NULL;
        case 19: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value19 : NULL;
        case 20: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value20 : NULL;
        case 21: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value21 : NULL;
        case 22: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value22[0] : NULL;
            return NULL;
        case 23: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value23 : NULL;
        case 24: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value24 : NULL;
        case 25: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value25 : NULL;
        case 26: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value26 : NULL;
        case 27: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value27 : NULL;
        case 28: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value28[0] : NULL;
            return NULL;
        case 29: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value29 : NULL;
        case 30: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value30 : NULL;
        case 31: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value31 : NULL;
        case 32: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value32[0] : NULL;
            return NULL;
        case 33: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value33 : NULL;
        case 34: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value34 : NULL;
        case 35: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value35 : NULL;
        case 36: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value36[0] : NULL;
            return NULL;
        case 37: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value37[0] : NULL;
            return NULL;
        case 38: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value38 : NULL;
        case 39: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value39 : NULL;
        case 40: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value40 : NULL;
        case 41: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value41 : NULL;
        case 42: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value42 : NULL;
        case 43: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value43 : NULL;
        case 44: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value44 : NULL;
        case 45: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value45 : NULL;
        case 46: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value46 : NULL;
        case 47: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value47 : NULL;
        case 48: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value48 : NULL;
        case 49: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value49 : NULL;
        case 50: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value50 : NULL;
        case 51: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value51 : NULL;
        case 52: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value52 : NULL;
        case 53: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value53 : NULL;
        case 54: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value54 : NULL;
        case 55: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value55 : NULL;
        case 56: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value56 : NULL;
        case 57: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value57 : NULL;
        case 58: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value58 : NULL;
        case 59: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value59 : NULL;
        case 60: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value60 : NULL;
        case 61: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value61 : NULL;
        case 62: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value62 : NULL;
        case 63: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value63 : NULL;
        case 64: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value64 : NULL;
        case 65: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value65 : NULL;
        case 66: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value66 : NULL;
        case 67: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value67 : NULL;
        case 68: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value68 : NULL;
        case 69: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value69 : NULL;
        case 70: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value70 : NULL;
        case 71: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value71 : NULL;
        case 72: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value72 : NULL;
        case 73: //gnam GNAM ,, Struct
            return GNAM.IsLoaded() ? &GNAM->value73 : NULL;
        case 74: //gnam GNAM ,, Struct
            return GNAM.IsLoaded() ? &GNAM->value74 : NULL;
        case 75: //gnam GNAM ,, Struct
            return GNAM.IsLoaded() ? &GNAM->value75 : NULL;
        default:
            return NULL;
        }
    }

bool WATRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //full Name
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //nnam Noise Map
            NNAM.Copy((STRING)FieldValue);
            break;
        case 9: //anam Opacity
            ANAM.Load();
            ANAM->value9 = *(UINT8 *)FieldValue;
            break;
        case 10: //fnam Flags
            FNAM.Load();
            FNAM->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //mnam Material ID
            MNAM.Copy((STRING)FieldValue);
            break;
        case 12: //snam Sound
            SNAM.Load();
            SNAM->value12 = *(FORMID *)FieldValue;
            return true;
        case 13: //xnam Actor Effect
            XNAM.Load();
            XNAM->value13 = *(FORMID *)FieldValue;
            return true;
        case 14: //data Damage
            DATA.Load();
            DATA->value14 = *(UINT16 *)FieldValue;
            break;
        case 15: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value18 = *(FLOAT32 *)FieldValue;
            break;
        case 19: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value19 = *(FLOAT32 *)FieldValue;
            break;
        case 20: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value20 = *(FLOAT32 *)FieldValue;
            break;
        case 21: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->value22[0] = ((UINT8 *)FieldValue)[0];
            DNAM->value22[1] = ((UINT8 *)FieldValue)[1];
            DNAM->value22[2] = ((UINT8 *)FieldValue)[2];
            DNAM->value22[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 23: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value23 = *(FLOAT32 *)FieldValue;
            break;
        case 24: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value24 = *(FLOAT32 *)FieldValue;
            break;
        case 25: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value25 = *(UINT8 *)FieldValue;
            break;
        case 26: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value26 = *(UINT8 *)FieldValue;
            break;
        case 27: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value27 = *(UINT8 *)FieldValue;
            break;
        case 28: //dnam_p DNAM ,, Struct
            if(ArraySize != 1)
                break;
            DNAM.Load();
            DNAM->value28[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 29: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value29 = *(UINT8 *)FieldValue;
            break;
        case 30: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value30 = *(UINT8 *)FieldValue;
            break;
        case 31: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value31 = *(UINT8 *)FieldValue;
            break;
        case 32: //dnam_p DNAM ,, Struct
            if(ArraySize != 1)
                break;
            DNAM.Load();
            DNAM->value32[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 33: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value33 = *(UINT8 *)FieldValue;
            break;
        case 34: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value34 = *(UINT8 *)FieldValue;
            break;
        case 35: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value35 = *(UINT8 *)FieldValue;
            break;
        case 36: //dnam_p DNAM ,, Struct
            if(ArraySize != 1)
                break;
            DNAM.Load();
            DNAM->value36[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 37: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->value37[0] = ((UINT8 *)FieldValue)[0];
            DNAM->value37[1] = ((UINT8 *)FieldValue)[1];
            DNAM->value37[2] = ((UINT8 *)FieldValue)[2];
            DNAM->value37[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 38: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value38 = *(FLOAT32 *)FieldValue;
            break;
        case 39: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value39 = *(FLOAT32 *)FieldValue;
            break;
        case 40: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value40 = *(FLOAT32 *)FieldValue;
            break;
        case 41: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value41 = *(FLOAT32 *)FieldValue;
            break;
        case 42: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value42 = *(FLOAT32 *)FieldValue;
            break;
        case 43: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value43 = *(FLOAT32 *)FieldValue;
            break;
        case 44: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value44 = *(FLOAT32 *)FieldValue;
            break;
        case 45: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value45 = *(FLOAT32 *)FieldValue;
            break;
        case 46: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value46 = *(FLOAT32 *)FieldValue;
            break;
        case 47: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value47 = *(FLOAT32 *)FieldValue;
            break;
        case 48: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value48 = *(FLOAT32 *)FieldValue;
            break;
        case 49: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value49 = *(FLOAT32 *)FieldValue;
            break;
        case 50: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value50 = *(FLOAT32 *)FieldValue;
            break;
        case 51: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value51 = *(FLOAT32 *)FieldValue;
            break;
        case 52: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value52 = *(FLOAT32 *)FieldValue;
            break;
        case 53: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value53 = *(FLOAT32 *)FieldValue;
            break;
        case 54: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value54 = *(FLOAT32 *)FieldValue;
            break;
        case 55: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value55 = *(FLOAT32 *)FieldValue;
            break;
        case 56: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value56 = *(FLOAT32 *)FieldValue;
            break;
        case 57: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value57 = *(FLOAT32 *)FieldValue;
            break;
        case 58: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value58 = *(FLOAT32 *)FieldValue;
            break;
        case 59: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value59 = *(FLOAT32 *)FieldValue;
            break;
        case 60: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value60 = *(FLOAT32 *)FieldValue;
            break;
        case 61: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value61 = *(FLOAT32 *)FieldValue;
            break;
        case 62: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value62 = *(FLOAT32 *)FieldValue;
            break;
        case 63: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value63 = *(FLOAT32 *)FieldValue;
            break;
        case 64: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value64 = *(FLOAT32 *)FieldValue;
            break;
        case 65: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value65 = *(FLOAT32 *)FieldValue;
            break;
        case 66: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value66 = *(FLOAT32 *)FieldValue;
            break;
        case 67: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value67 = *(FLOAT32 *)FieldValue;
            break;
        case 68: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value68 = *(FLOAT32 *)FieldValue;
            break;
        case 69: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value69 = *(FLOAT32 *)FieldValue;
            break;
        case 70: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value70 = *(FLOAT32 *)FieldValue;
            break;
        case 71: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value71 = *(FLOAT32 *)FieldValue;
            break;
        case 72: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value72 = *(FLOAT32 *)FieldValue;
            break;
        case 73: //gnam GNAM ,, Struct
            GNAM.Load();
            GNAM->value73 = *(FORMID *)FieldValue;
            return true;
        case 74: //gnam GNAM ,, Struct
            GNAM.Load();
            GNAM->value74 = *(FORMID *)FieldValue;
            return true;
        case 75: //gnam GNAM ,, Struct
            GNAM.Load();
            GNAM->value75 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void WATRRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //full Name
            FULL.Unload();
            return;
        case 8: //nnam Noise Map
            NNAM.Unload();
            return;
        case 9: //anam Opacity
            ANAM.Unload();
            return;
        case 10: //fnam Flags
            FNAM.Unload();
            return;
        case 11: //mnam Material ID
            MNAM.Unload();
            return;
        case 12: //snam Sound
            SNAM.Unload();
            return;
        case 13: //xnam Actor Effect
            XNAM.Unload();
            return;
        case 14: //data Damage
            DATA.Unload();
            return;
        case 15: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 16: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 17: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 18: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 19: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 20: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 21: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 22: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 23: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 24: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 25: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 26: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 27: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 28: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 29: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 30: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 31: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 32: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 33: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 34: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 35: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 36: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 37: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 38: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 39: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 40: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 41: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 42: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 43: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 44: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 45: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 46: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 47: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 48: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 49: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 50: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 51: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 52: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 53: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 54: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 55: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 56: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 57: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 58: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 59: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 60: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 61: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 62: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 63: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 64: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 65: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 66: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 67: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 68: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 69: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 70: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 71: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 72: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 73: //gnam GNAM ,, Struct
            GNAM.Unload();
            return;
        case 74: //gnam GNAM ,, Struct
            GNAM.Unload();
            return;
        case 75: //gnam GNAM ,, Struct
            GNAM.Unload();
            return;
        default:
            return;
        }
    }
}