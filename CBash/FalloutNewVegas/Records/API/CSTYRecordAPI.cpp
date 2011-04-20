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
#include "..\CSTYRecord.h"

namespace FNV
{
UINT32 CSTYRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 8: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 9: //cstd_p CSTD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 11: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 12: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 13: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 14: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 15: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 16: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 17: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 18: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 19: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 20: //cstd_p CSTD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 21: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 22: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 23: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 24: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 25: //cstd_p CSTD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 26: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 27: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 28: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 29: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 30: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 31: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 32: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 33: //cstd_p CSTD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 34: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 35: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 36: //cstd CSTD ,, Struct
            return UINT16_FIELD;
        case 37: //cstd_p CSTD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 38: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 39: //cstd CSTD ,, Struct
            return UINT8_FIELD;
        case 40: //cstd_p CSTD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 41: //cstd CSTD ,, Struct
            return FLOAT32_FIELD;
        case 42: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 43: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 44: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 45: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 46: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 47: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 48: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 49: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 50: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 51: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 52: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 53: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 54: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 55: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 56: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 57: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 58: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 59: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 60: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 61: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 62: //csad CSAD ,, Struct
            return FLOAT32_FIELD;
        case 63: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 64: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 65: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 66: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 67: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 68: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 69: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 70: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 71: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 72: //cssd_p CSSD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 73: //cssd CSSD ,, Struct
            return UINT32_FIELD;
        case 74: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 75: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 76: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 77: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        case 78: //cssd CSSD ,, Struct
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CSTYRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value7 : NULL;
        case 8: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value8 : NULL;
        case 9: //cstd_p CSTD ,, Struct
            *FieldValues = CSTD.IsLoaded() ? &CSTD->value9[0] : NULL;
            return NULL;
        case 10: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value10 : NULL;
        case 11: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value11 : NULL;
        case 12: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value12 : NULL;
        case 13: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value13 : NULL;
        case 14: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value14 : NULL;
        case 15: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value15 : NULL;
        case 16: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value16 : NULL;
        case 17: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value17 : NULL;
        case 18: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value18 : NULL;
        case 19: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value19 : NULL;
        case 20: //cstd_p CSTD ,, Struct
            *FieldValues = CSTD.IsLoaded() ? &CSTD->value20[0] : NULL;
            return NULL;
        case 21: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value21 : NULL;
        case 22: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value22 : NULL;
        case 23: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value23 : NULL;
        case 24: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value24 : NULL;
        case 25: //cstd_p CSTD ,, Struct
            *FieldValues = CSTD.IsLoaded() ? &CSTD->value25[0] : NULL;
            return NULL;
        case 26: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value26 : NULL;
        case 27: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value27 : NULL;
        case 28: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value28 : NULL;
        case 29: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value29 : NULL;
        case 30: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value30 : NULL;
        case 31: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value31 : NULL;
        case 32: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value32 : NULL;
        case 33: //cstd_p CSTD ,, Struct
            *FieldValues = CSTD.IsLoaded() ? &CSTD->value33[0] : NULL;
            return NULL;
        case 34: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value34 : NULL;
        case 35: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value35 : NULL;
        case 36: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value36 : NULL;
        case 37: //cstd_p CSTD ,, Struct
            *FieldValues = CSTD.IsLoaded() ? &CSTD->value37[0] : NULL;
            return NULL;
        case 38: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value38 : NULL;
        case 39: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value39 : NULL;
        case 40: //cstd_p CSTD ,, Struct
            *FieldValues = CSTD.IsLoaded() ? &CSTD->value40[0] : NULL;
            return NULL;
        case 41: //cstd CSTD ,, Struct
            return CSTD.IsLoaded() ? &CSTD->value41 : NULL;
        case 42: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value42 : NULL;
        case 43: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value43 : NULL;
        case 44: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value44 : NULL;
        case 45: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value45 : NULL;
        case 46: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value46 : NULL;
        case 47: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value47 : NULL;
        case 48: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value48 : NULL;
        case 49: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value49 : NULL;
        case 50: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value50 : NULL;
        case 51: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value51 : NULL;
        case 52: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value52 : NULL;
        case 53: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value53 : NULL;
        case 54: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value54 : NULL;
        case 55: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value55 : NULL;
        case 56: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value56 : NULL;
        case 57: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value57 : NULL;
        case 58: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value58 : NULL;
        case 59: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value59 : NULL;
        case 60: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value60 : NULL;
        case 61: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value61 : NULL;
        case 62: //csad CSAD ,, Struct
            return CSAD.IsLoaded() ? &CSAD->value62 : NULL;
        case 63: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value63 : NULL;
        case 64: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value64 : NULL;
        case 65: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value65 : NULL;
        case 66: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value66 : NULL;
        case 67: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value67 : NULL;
        case 68: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value68 : NULL;
        case 69: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value69 : NULL;
        case 70: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value70 : NULL;
        case 71: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value71 : NULL;
        case 72: //cssd_p CSSD ,, Struct
            *FieldValues = CSSD.IsLoaded() ? &CSSD->value72[0] : NULL;
            return NULL;
        case 73: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value73 : NULL;
        case 74: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value74 : NULL;
        case 75: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value75 : NULL;
        case 76: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value76 : NULL;
        case 77: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value77 : NULL;
        case 78: //cssd CSSD ,, Struct
            return CSSD.IsLoaded() ? &CSSD->value78 : NULL;
        default:
            return NULL;
        }
    }

bool CSTYRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value7 = *(UINT8 *)FieldValue;
            break;
        case 8: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value8 = *(UINT8 *)FieldValue;
            break;
        case 9: //cstd_p CSTD ,, Struct
            if(ArraySize != 2)
                break;
            CSTD.Load();
            CSTD->value9[0] = ((UINT8 *)FieldValue)[0];
            CSTD->value9[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 10: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value10 = *(FLOAT32 *)FieldValue;
            break;
        case 11: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value11 = *(FLOAT32 *)FieldValue;
            break;
        case 12: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value12 = *(FLOAT32 *)FieldValue;
            break;
        case 13: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value13 = *(FLOAT32 *)FieldValue;
            break;
        case 14: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value18 = *(UINT8 *)FieldValue;
            break;
        case 19: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value19 = *(UINT8 *)FieldValue;
            break;
        case 20: //cstd_p CSTD ,, Struct
            if(ArraySize != 2)
                break;
            CSTD.Load();
            CSTD->value20[0] = ((UINT8 *)FieldValue)[0];
            CSTD->value20[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 21: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value23 = *(FLOAT32 *)FieldValue;
            break;
        case 24: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value24 = *(UINT8 *)FieldValue;
            break;
        case 25: //cstd_p CSTD ,, Struct
            if(ArraySize != 3)
                break;
            CSTD.Load();
            CSTD->value25[0] = ((UINT8 *)FieldValue)[0];
            CSTD->value25[1] = ((UINT8 *)FieldValue)[1];
            CSTD->value25[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 26: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value27 = *(FLOAT32 *)FieldValue;
            break;
        case 28: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value29 = *(UINT8 *)FieldValue;
            break;
        case 30: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value30 = *(UINT8 *)FieldValue;
            break;
        case 31: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value31 = *(UINT8 *)FieldValue;
            break;
        case 32: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value32 = *(UINT8 *)FieldValue;
            break;
        case 33: //cstd_p CSTD ,, Struct
            if(ArraySize != 3)
                break;
            CSTD.Load();
            CSTD->value33[0] = ((UINT8 *)FieldValue)[0];
            CSTD->value33[1] = ((UINT8 *)FieldValue)[1];
            CSTD->value33[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 34: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value35 = *(FLOAT32 *)FieldValue;
            break;
        case 36: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value36 = *(UINT16 *)FieldValue;
            break;
        case 37: //cstd_p CSTD ,, Struct
            if(ArraySize != 2)
                break;
            CSTD.Load();
            CSTD->value37[0] = ((UINT8 *)FieldValue)[0];
            CSTD->value37[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 38: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value38 = *(UINT8 *)FieldValue;
            break;
        case 39: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value39 = *(UINT8 *)FieldValue;
            break;
        case 40: //cstd_p CSTD ,, Struct
            if(ArraySize != 2)
                break;
            CSTD.Load();
            CSTD->value40[0] = ((UINT8 *)FieldValue)[0];
            CSTD->value40[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 41: //cstd CSTD ,, Struct
            CSTD.Load();
            CSTD->value41 = *(FLOAT32 *)FieldValue;
            break;
        case 42: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value42 = *(FLOAT32 *)FieldValue;
            break;
        case 43: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value43 = *(FLOAT32 *)FieldValue;
            break;
        case 44: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value44 = *(FLOAT32 *)FieldValue;
            break;
        case 45: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value45 = *(FLOAT32 *)FieldValue;
            break;
        case 46: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value46 = *(FLOAT32 *)FieldValue;
            break;
        case 47: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value47 = *(FLOAT32 *)FieldValue;
            break;
        case 48: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value48 = *(FLOAT32 *)FieldValue;
            break;
        case 49: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value49 = *(FLOAT32 *)FieldValue;
            break;
        case 50: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value50 = *(FLOAT32 *)FieldValue;
            break;
        case 51: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value51 = *(FLOAT32 *)FieldValue;
            break;
        case 52: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value52 = *(FLOAT32 *)FieldValue;
            break;
        case 53: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value53 = *(FLOAT32 *)FieldValue;
            break;
        case 54: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value54 = *(FLOAT32 *)FieldValue;
            break;
        case 55: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value55 = *(FLOAT32 *)FieldValue;
            break;
        case 56: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value56 = *(FLOAT32 *)FieldValue;
            break;
        case 57: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value57 = *(FLOAT32 *)FieldValue;
            break;
        case 58: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value58 = *(FLOAT32 *)FieldValue;
            break;
        case 59: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value59 = *(FLOAT32 *)FieldValue;
            break;
        case 60: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value60 = *(FLOAT32 *)FieldValue;
            break;
        case 61: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value61 = *(FLOAT32 *)FieldValue;
            break;
        case 62: //csad CSAD ,, Struct
            CSAD.Load();
            CSAD->value62 = *(FLOAT32 *)FieldValue;
            break;
        case 63: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value63 = *(FLOAT32 *)FieldValue;
            break;
        case 64: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value64 = *(FLOAT32 *)FieldValue;
            break;
        case 65: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value65 = *(FLOAT32 *)FieldValue;
            break;
        case 66: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value66 = *(FLOAT32 *)FieldValue;
            break;
        case 67: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value67 = *(FLOAT32 *)FieldValue;
            break;
        case 68: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value68 = *(FLOAT32 *)FieldValue;
            break;
        case 69: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value69 = *(FLOAT32 *)FieldValue;
            break;
        case 70: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value70 = *(FLOAT32 *)FieldValue;
            break;
        case 71: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value71 = *(FLOAT32 *)FieldValue;
            break;
        case 72: //cssd_p CSSD ,, Struct
            if(ArraySize != 4)
                break;
            CSSD.Load();
            CSSD->value72[0] = ((UINT8 *)FieldValue)[0];
            CSSD->value72[1] = ((UINT8 *)FieldValue)[1];
            CSSD->value72[2] = ((UINT8 *)FieldValue)[2];
            CSSD->value72[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 73: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value73 = *(UINT32 *)FieldValue;
            break;
        case 74: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value74 = *(FLOAT32 *)FieldValue;
            break;
        case 75: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value75 = *(FLOAT32 *)FieldValue;
            break;
        case 76: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value76 = *(FLOAT32 *)FieldValue;
            break;
        case 77: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value77 = *(FLOAT32 *)FieldValue;
            break;
        case 78: //cssd CSSD ,, Struct
            CSSD.Load();
            CSSD->value78 = *(FLOAT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CSTYRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 8: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 9: //cstd_p CSTD ,, Struct
            CSTD.Unload();
            return;
        case 10: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 11: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 12: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 13: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 14: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 15: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 16: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 17: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 18: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 19: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 20: //cstd_p CSTD ,, Struct
            CSTD.Unload();
            return;
        case 21: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 22: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 23: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 24: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 25: //cstd_p CSTD ,, Struct
            CSTD.Unload();
            return;
        case 26: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 27: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 28: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 29: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 30: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 31: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 32: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 33: //cstd_p CSTD ,, Struct
            CSTD.Unload();
            return;
        case 34: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 35: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 36: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 37: //cstd_p CSTD ,, Struct
            CSTD.Unload();
            return;
        case 38: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 39: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 40: //cstd_p CSTD ,, Struct
            CSTD.Unload();
            return;
        case 41: //cstd CSTD ,, Struct
            CSTD.Unload();
            return;
        case 42: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 43: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 44: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 45: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 46: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 47: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 48: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 49: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 50: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 51: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 52: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 53: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 54: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 55: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 56: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 57: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 58: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 59: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 60: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 61: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 62: //csad CSAD ,, Struct
            CSAD.Unload();
            return;
        case 63: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 64: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 65: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 66: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 67: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 68: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 69: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 70: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 71: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 72: //cssd_p CSSD ,, Struct
            CSSD.Unload();
            return;
        case 73: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 74: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 75: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 76: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 77: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        case 78: //cssd CSSD ,, Struct
            CSSD.Unload();
            return;
        default:
            return;
        }
    }
}