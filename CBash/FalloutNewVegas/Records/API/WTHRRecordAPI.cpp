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
#include "..\WTHRRecord.h"

namespace FNV
{
UINT32 WTHRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //0iad Sunrise Image Space Modifier
            return FORMID_FIELD;
        case 8: //1iad Day Image Space Modifier
            return FORMID_FIELD;
        case 9: //2iad Sunset Image Space Modifier
            return FORMID_FIELD;
        case 10: //3iad Night Image Space Modifier
            return FORMID_FIELD;
        case 11: //4iad Unknown
            return FORMID_FIELD;
        case 12: //5iad Unknown
            return FORMID_FIELD;
        case 13: //dnam Cloud Textures - Layer 0
            return ISTRING_FIELD;
        case 14: //cnam Cloud Textures - Layer 1
            return ISTRING_FIELD;
        case 15: //anam Cloud Textures - Layer 2
            return ISTRING_FIELD;
        case 16: //bnam Cloud Textures - Layer 3
            return ISTRING_FIELD;
        case 17: //modl Model Filename
            return STRING_FIELD;
        case 18: //modb_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 19: //modt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 20: //mods Alternate Textures
            return STRING_FIELD;
        case 21: //mods Alternate Textures
            return FORMID_FIELD;
        case 22: //mods Alternate Textures
            return SINT32_FIELD;
        case 23: //modd FaceGen Model Flags
            return UINT8_FIELD;
        case 24: //lnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 25: //onam Cloud Speed
            return UNPARSED_FIELD;
        case 26: //pnam_p Unused
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return PNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 27: //nam0 NAM0 ,, Struct
            return UINT8_FIELD;
        case 28: //nam0 NAM0 ,, Struct
            return UINT8_FIELD;
        case 29: //nam0 NAM0 ,, Struct
            return UINT8_FIELD;
        case 30: //nam0_p NAM0 ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 31: //fnam FNAM ,, Struct
            return FLOAT32_FIELD;
        case 32: //fnam FNAM ,, Struct
            return FLOAT32_FIELD;
        case 33: //fnam FNAM ,, Struct
            return FLOAT32_FIELD;
        case 34: //fnam FNAM ,, Struct
            return FLOAT32_FIELD;
        case 35: //fnam FNAM ,, Struct
            return FLOAT32_FIELD;
        case 36: //fnam FNAM ,, Struct
            return FLOAT32_FIELD;
        case 37: //inam_p Unused
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 304;
                default:
                    return UNKNOWN_FIELD;
                }
        case 38: //data DATA ,, Struct
            return UINT8_FIELD;
        case 39: //data DATA ,, Struct
            return UINT8_FIELD;
        case 40: //data DATA ,, Struct
            return UINT8_FIELD;
        case 41: //data DATA ,, Struct
            return UINT8_FIELD;
        case 42: //data DATA ,, Struct
            return UINT8_FIELD;
        case 43: //data DATA ,, Struct
            return UINT8_FIELD;
        case 44: //data DATA ,, Struct
            return UINT8_FIELD;
        case 45: //data DATA ,, Struct
            return UINT8_FIELD;
        case 46: //data DATA ,, Struct
            return UINT8_FIELD;
        case 47: //data DATA ,, Struct
            return UINT8_FIELD;
        case 48: //data DATA ,, Struct
            return UINT8_FIELD;
        case 49: //data DATA ,, Struct
            return UINT8_FIELD;
        case 50: //data DATA ,, Struct
            return UINT8_FIELD;
        case 51: //data DATA ,, Struct
            return UINT8_FIELD;
        case 52: //data DATA ,, Struct
            return UINT8_FIELD;
        case 53: //snam SNAM ,, Struct
            return FORMID_FIELD;
        case 54: //snam SNAM ,, Struct
            return UINT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * WTHRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //0iad Sunrise Image Space Modifier
            return 0IAD.IsLoaded() ? &0IAD->value7 : NULL;
        case 8: //1iad Day Image Space Modifier
            return 1IAD.IsLoaded() ? &1IAD->value8 : NULL;
        case 9: //2iad Sunset Image Space Modifier
            return 2IAD.IsLoaded() ? &2IAD->value9 : NULL;
        case 10: //3iad Night Image Space Modifier
            return 3IAD.IsLoaded() ? &3IAD->value10 : NULL;
        case 11: //4iad Unknown
            return 4IAD.IsLoaded() ? &4IAD->value11 : NULL;
        case 12: //5iad Unknown
            return 5IAD.IsLoaded() ? &5IAD->value12 : NULL;
        case 13: //dnam Cloud Textures - Layer 0
            return DNAM.value;
        case 14: //cnam Cloud Textures - Layer 1
            return CNAM.value;
        case 15: //anam Cloud Textures - Layer 2
            return ANAM.value;
        case 16: //bnam Cloud Textures - Layer 3
            return BNAM.value;
        case 17: //modl Model Filename
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 18: //modb_p Unknown
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODB.value : NULL;
            return NULL;
        case 19: //modt_p Texture Files Hashes
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODT.value : NULL;
            return NULL;
        case 20: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 21: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value21 : NULL;
        case 22: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value22 : NULL;
        case 23: //modd FaceGen Model Flags
            return MODL.IsLoaded() ? &MODL->MODD->value23 : NULL;
        case 24: //lnam_p Unknown
            *FieldValues = LNAM.IsLoaded() ? &LNAM->value24[0] : NULL;
            return NULL;
        case 25: //onam Cloud Speed
            return UNPARSEDGET_FIELD25;
        case 26: //pnam_p Unused
            *FieldValues = PNAM.value;
            return NULL;
        case 27: //nam0 NAM0 ,, Struct
            return NAM0.IsLoaded() ? &NAM0->value27 : NULL;
        case 28: //nam0 NAM0 ,, Struct
            return NAM0.IsLoaded() ? &NAM0->value28 : NULL;
        case 29: //nam0 NAM0 ,, Struct
            return NAM0.IsLoaded() ? &NAM0->value29 : NULL;
        case 30: //nam0_p NAM0 ,, Struct
            *FieldValues = NAM0.IsLoaded() ? &NAM0->value30[0] : NULL;
            return NULL;
        case 31: //fnam FNAM ,, Struct
            return FNAM.IsLoaded() ? &FNAM->value31 : NULL;
        case 32: //fnam FNAM ,, Struct
            return FNAM.IsLoaded() ? &FNAM->value32 : NULL;
        case 33: //fnam FNAM ,, Struct
            return FNAM.IsLoaded() ? &FNAM->value33 : NULL;
        case 34: //fnam FNAM ,, Struct
            return FNAM.IsLoaded() ? &FNAM->value34 : NULL;
        case 35: //fnam FNAM ,, Struct
            return FNAM.IsLoaded() ? &FNAM->value35 : NULL;
        case 36: //fnam FNAM ,, Struct
            return FNAM.IsLoaded() ? &FNAM->value36 : NULL;
        case 37: //inam_p Unused
            *FieldValues = INAM.IsLoaded() ? &INAM->value37[0] : NULL;
            return NULL;
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
        case 53: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value53 : NULL;
        case 54: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value54 : NULL;
        default:
            return NULL;
        }
    }

bool WTHRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //0iad Sunrise Image Space Modifier
            0IAD.Load();
            0IAD->value7 = *(FORMID *)FieldValue;
            return true;
        case 8: //1iad Day Image Space Modifier
            1IAD.Load();
            1IAD->value8 = *(FORMID *)FieldValue;
            return true;
        case 9: //2iad Sunset Image Space Modifier
            2IAD.Load();
            2IAD->value9 = *(FORMID *)FieldValue;
            return true;
        case 10: //3iad Night Image Space Modifier
            3IAD.Load();
            3IAD->value10 = *(FORMID *)FieldValue;
            return true;
        case 11: //4iad Unknown
            4IAD.Load();
            4IAD->value11 = *(FORMID *)FieldValue;
            return true;
        case 12: //5iad Unknown
            5IAD.Load();
            5IAD->value12 = *(FORMID *)FieldValue;
            return true;
        case 13: //dnam Cloud Textures - Layer 0
            DNAM.Copy((STRING)FieldValue);
            break;
        case 14: //cnam Cloud Textures - Layer 1
            CNAM.Copy((STRING)FieldValue);
            break;
        case 15: //anam Cloud Textures - Layer 2
            ANAM.Copy((STRING)FieldValue);
            break;
        case 16: //bnam Cloud Textures - Layer 3
            BNAM.Copy((STRING)FieldValue);
            break;
        case 17: //modl Model Filename
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 18: //modb_p Unknown
            MODL.Load();
            MODL->MODB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 19: //modt_p Texture Files Hashes
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 20: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 21: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value21 = *(FORMID *)FieldValue;
            return true;
        case 22: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value22 = *(SINT32 *)FieldValue;
            break;
        case 23: //modd FaceGen Model Flags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //lnam_p Unknown
            if(ArraySize != 4)
                break;
            LNAM.Load();
            LNAM->value24[0] = ((UINT8 *)FieldValue)[0];
            LNAM->value24[1] = ((UINT8 *)FieldValue)[1];
            LNAM->value24[2] = ((UINT8 *)FieldValue)[2];
            LNAM->value24[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 25: //onam Cloud Speed
            return UNPARSEDGET_FIELD25;
        case 26: //pnam_p Unused
            PNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 27: //nam0 NAM0 ,, Struct
            NAM0.Load();
            NAM0->value27 = *(UINT8 *)FieldValue;
            break;
        case 28: //nam0 NAM0 ,, Struct
            NAM0.Load();
            NAM0->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //nam0 NAM0 ,, Struct
            NAM0.Load();
            NAM0->value29 = *(UINT8 *)FieldValue;
            break;
        case 30: //nam0_p NAM0 ,, Struct
            if(ArraySize != 1)
                break;
            NAM0.Load();
            NAM0->value30[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 31: //fnam FNAM ,, Struct
            FNAM.Load();
            FNAM->value31 = *(FLOAT32 *)FieldValue;
            break;
        case 32: //fnam FNAM ,, Struct
            FNAM.Load();
            FNAM->value32 = *(FLOAT32 *)FieldValue;
            break;
        case 33: //fnam FNAM ,, Struct
            FNAM.Load();
            FNAM->value33 = *(FLOAT32 *)FieldValue;
            break;
        case 34: //fnam FNAM ,, Struct
            FNAM.Load();
            FNAM->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //fnam FNAM ,, Struct
            FNAM.Load();
            FNAM->value35 = *(FLOAT32 *)FieldValue;
            break;
        case 36: //fnam FNAM ,, Struct
            FNAM.Load();
            FNAM->value36 = *(FLOAT32 *)FieldValue;
            break;
        case 37: //inam_p Unused
            if(ArraySize != 304)
                break;
            INAM.Load();
            INAM->value37[0] = ((UINT8 *)FieldValue)[0];
            INAM->value37[1] = ((UINT8 *)FieldValue)[1];
            INAM->value37[2] = ((UINT8 *)FieldValue)[2];
            INAM->value37[3] = ((UINT8 *)FieldValue)[3];
            INAM->value37[4] = ((UINT8 *)FieldValue)[4];
            INAM->value37[5] = ((UINT8 *)FieldValue)[5];
            INAM->value37[6] = ((UINT8 *)FieldValue)[6];
            INAM->value37[7] = ((UINT8 *)FieldValue)[7];
            INAM->value37[8] = ((UINT8 *)FieldValue)[8];
            INAM->value37[9] = ((UINT8 *)FieldValue)[9];
            INAM->value37[10] = ((UINT8 *)FieldValue)[10];
            INAM->value37[11] = ((UINT8 *)FieldValue)[11];
            INAM->value37[12] = ((UINT8 *)FieldValue)[12];
            INAM->value37[13] = ((UINT8 *)FieldValue)[13];
            INAM->value37[14] = ((UINT8 *)FieldValue)[14];
            INAM->value37[15] = ((UINT8 *)FieldValue)[15];
            INAM->value37[16] = ((UINT8 *)FieldValue)[16];
            INAM->value37[17] = ((UINT8 *)FieldValue)[17];
            INAM->value37[18] = ((UINT8 *)FieldValue)[18];
            INAM->value37[19] = ((UINT8 *)FieldValue)[19];
            INAM->value37[20] = ((UINT8 *)FieldValue)[20];
            INAM->value37[21] = ((UINT8 *)FieldValue)[21];
            INAM->value37[22] = ((UINT8 *)FieldValue)[22];
            INAM->value37[23] = ((UINT8 *)FieldValue)[23];
            INAM->value37[24] = ((UINT8 *)FieldValue)[24];
            INAM->value37[25] = ((UINT8 *)FieldValue)[25];
            INAM->value37[26] = ((UINT8 *)FieldValue)[26];
            INAM->value37[27] = ((UINT8 *)FieldValue)[27];
            INAM->value37[28] = ((UINT8 *)FieldValue)[28];
            INAM->value37[29] = ((UINT8 *)FieldValue)[29];
            INAM->value37[30] = ((UINT8 *)FieldValue)[30];
            INAM->value37[31] = ((UINT8 *)FieldValue)[31];
            INAM->value37[32] = ((UINT8 *)FieldValue)[32];
            INAM->value37[33] = ((UINT8 *)FieldValue)[33];
            INAM->value37[34] = ((UINT8 *)FieldValue)[34];
            INAM->value37[35] = ((UINT8 *)FieldValue)[35];
            INAM->value37[36] = ((UINT8 *)FieldValue)[36];
            INAM->value37[37] = ((UINT8 *)FieldValue)[37];
            INAM->value37[38] = ((UINT8 *)FieldValue)[38];
            INAM->value37[39] = ((UINT8 *)FieldValue)[39];
            INAM->value37[40] = ((UINT8 *)FieldValue)[40];
            INAM->value37[41] = ((UINT8 *)FieldValue)[41];
            INAM->value37[42] = ((UINT8 *)FieldValue)[42];
            INAM->value37[43] = ((UINT8 *)FieldValue)[43];
            INAM->value37[44] = ((UINT8 *)FieldValue)[44];
            INAM->value37[45] = ((UINT8 *)FieldValue)[45];
            INAM->value37[46] = ((UINT8 *)FieldValue)[46];
            INAM->value37[47] = ((UINT8 *)FieldValue)[47];
            INAM->value37[48] = ((UINT8 *)FieldValue)[48];
            INAM->value37[49] = ((UINT8 *)FieldValue)[49];
            INAM->value37[50] = ((UINT8 *)FieldValue)[50];
            INAM->value37[51] = ((UINT8 *)FieldValue)[51];
            INAM->value37[52] = ((UINT8 *)FieldValue)[52];
            INAM->value37[53] = ((UINT8 *)FieldValue)[53];
            INAM->value37[54] = ((UINT8 *)FieldValue)[54];
            INAM->value37[55] = ((UINT8 *)FieldValue)[55];
            INAM->value37[56] = ((UINT8 *)FieldValue)[56];
            INAM->value37[57] = ((UINT8 *)FieldValue)[57];
            INAM->value37[58] = ((UINT8 *)FieldValue)[58];
            INAM->value37[59] = ((UINT8 *)FieldValue)[59];
            INAM->value37[60] = ((UINT8 *)FieldValue)[60];
            INAM->value37[61] = ((UINT8 *)FieldValue)[61];
            INAM->value37[62] = ((UINT8 *)FieldValue)[62];
            INAM->value37[63] = ((UINT8 *)FieldValue)[63];
            INAM->value37[64] = ((UINT8 *)FieldValue)[64];
            INAM->value37[65] = ((UINT8 *)FieldValue)[65];
            INAM->value37[66] = ((UINT8 *)FieldValue)[66];
            INAM->value37[67] = ((UINT8 *)FieldValue)[67];
            INAM->value37[68] = ((UINT8 *)FieldValue)[68];
            INAM->value37[69] = ((UINT8 *)FieldValue)[69];
            INAM->value37[70] = ((UINT8 *)FieldValue)[70];
            INAM->value37[71] = ((UINT8 *)FieldValue)[71];
            INAM->value37[72] = ((UINT8 *)FieldValue)[72];
            INAM->value37[73] = ((UINT8 *)FieldValue)[73];
            INAM->value37[74] = ((UINT8 *)FieldValue)[74];
            INAM->value37[75] = ((UINT8 *)FieldValue)[75];
            INAM->value37[76] = ((UINT8 *)FieldValue)[76];
            INAM->value37[77] = ((UINT8 *)FieldValue)[77];
            INAM->value37[78] = ((UINT8 *)FieldValue)[78];
            INAM->value37[79] = ((UINT8 *)FieldValue)[79];
            INAM->value37[80] = ((UINT8 *)FieldValue)[80];
            INAM->value37[81] = ((UINT8 *)FieldValue)[81];
            INAM->value37[82] = ((UINT8 *)FieldValue)[82];
            INAM->value37[83] = ((UINT8 *)FieldValue)[83];
            INAM->value37[84] = ((UINT8 *)FieldValue)[84];
            INAM->value37[85] = ((UINT8 *)FieldValue)[85];
            INAM->value37[86] = ((UINT8 *)FieldValue)[86];
            INAM->value37[87] = ((UINT8 *)FieldValue)[87];
            INAM->value37[88] = ((UINT8 *)FieldValue)[88];
            INAM->value37[89] = ((UINT8 *)FieldValue)[89];
            INAM->value37[90] = ((UINT8 *)FieldValue)[90];
            INAM->value37[91] = ((UINT8 *)FieldValue)[91];
            INAM->value37[92] = ((UINT8 *)FieldValue)[92];
            INAM->value37[93] = ((UINT8 *)FieldValue)[93];
            INAM->value37[94] = ((UINT8 *)FieldValue)[94];
            INAM->value37[95] = ((UINT8 *)FieldValue)[95];
            INAM->value37[96] = ((UINT8 *)FieldValue)[96];
            INAM->value37[97] = ((UINT8 *)FieldValue)[97];
            INAM->value37[98] = ((UINT8 *)FieldValue)[98];
            INAM->value37[99] = ((UINT8 *)FieldValue)[99];
            INAM->value37[100] = ((UINT8 *)FieldValue)[100];
            INAM->value37[101] = ((UINT8 *)FieldValue)[101];
            INAM->value37[102] = ((UINT8 *)FieldValue)[102];
            INAM->value37[103] = ((UINT8 *)FieldValue)[103];
            INAM->value37[104] = ((UINT8 *)FieldValue)[104];
            INAM->value37[105] = ((UINT8 *)FieldValue)[105];
            INAM->value37[106] = ((UINT8 *)FieldValue)[106];
            INAM->value37[107] = ((UINT8 *)FieldValue)[107];
            INAM->value37[108] = ((UINT8 *)FieldValue)[108];
            INAM->value37[109] = ((UINT8 *)FieldValue)[109];
            INAM->value37[110] = ((UINT8 *)FieldValue)[110];
            INAM->value37[111] = ((UINT8 *)FieldValue)[111];
            INAM->value37[112] = ((UINT8 *)FieldValue)[112];
            INAM->value37[113] = ((UINT8 *)FieldValue)[113];
            INAM->value37[114] = ((UINT8 *)FieldValue)[114];
            INAM->value37[115] = ((UINT8 *)FieldValue)[115];
            INAM->value37[116] = ((UINT8 *)FieldValue)[116];
            INAM->value37[117] = ((UINT8 *)FieldValue)[117];
            INAM->value37[118] = ((UINT8 *)FieldValue)[118];
            INAM->value37[119] = ((UINT8 *)FieldValue)[119];
            INAM->value37[120] = ((UINT8 *)FieldValue)[120];
            INAM->value37[121] = ((UINT8 *)FieldValue)[121];
            INAM->value37[122] = ((UINT8 *)FieldValue)[122];
            INAM->value37[123] = ((UINT8 *)FieldValue)[123];
            INAM->value37[124] = ((UINT8 *)FieldValue)[124];
            INAM->value37[125] = ((UINT8 *)FieldValue)[125];
            INAM->value37[126] = ((UINT8 *)FieldValue)[126];
            INAM->value37[127] = ((UINT8 *)FieldValue)[127];
            INAM->value37[128] = ((UINT8 *)FieldValue)[128];
            INAM->value37[129] = ((UINT8 *)FieldValue)[129];
            INAM->value37[130] = ((UINT8 *)FieldValue)[130];
            INAM->value37[131] = ((UINT8 *)FieldValue)[131];
            INAM->value37[132] = ((UINT8 *)FieldValue)[132];
            INAM->value37[133] = ((UINT8 *)FieldValue)[133];
            INAM->value37[134] = ((UINT8 *)FieldValue)[134];
            INAM->value37[135] = ((UINT8 *)FieldValue)[135];
            INAM->value37[136] = ((UINT8 *)FieldValue)[136];
            INAM->value37[137] = ((UINT8 *)FieldValue)[137];
            INAM->value37[138] = ((UINT8 *)FieldValue)[138];
            INAM->value37[139] = ((UINT8 *)FieldValue)[139];
            INAM->value37[140] = ((UINT8 *)FieldValue)[140];
            INAM->value37[141] = ((UINT8 *)FieldValue)[141];
            INAM->value37[142] = ((UINT8 *)FieldValue)[142];
            INAM->value37[143] = ((UINT8 *)FieldValue)[143];
            INAM->value37[144] = ((UINT8 *)FieldValue)[144];
            INAM->value37[145] = ((UINT8 *)FieldValue)[145];
            INAM->value37[146] = ((UINT8 *)FieldValue)[146];
            INAM->value37[147] = ((UINT8 *)FieldValue)[147];
            INAM->value37[148] = ((UINT8 *)FieldValue)[148];
            INAM->value37[149] = ((UINT8 *)FieldValue)[149];
            INAM->value37[150] = ((UINT8 *)FieldValue)[150];
            INAM->value37[151] = ((UINT8 *)FieldValue)[151];
            INAM->value37[152] = ((UINT8 *)FieldValue)[152];
            INAM->value37[153] = ((UINT8 *)FieldValue)[153];
            INAM->value37[154] = ((UINT8 *)FieldValue)[154];
            INAM->value37[155] = ((UINT8 *)FieldValue)[155];
            INAM->value37[156] = ((UINT8 *)FieldValue)[156];
            INAM->value37[157] = ((UINT8 *)FieldValue)[157];
            INAM->value37[158] = ((UINT8 *)FieldValue)[158];
            INAM->value37[159] = ((UINT8 *)FieldValue)[159];
            INAM->value37[160] = ((UINT8 *)FieldValue)[160];
            INAM->value37[161] = ((UINT8 *)FieldValue)[161];
            INAM->value37[162] = ((UINT8 *)FieldValue)[162];
            INAM->value37[163] = ((UINT8 *)FieldValue)[163];
            INAM->value37[164] = ((UINT8 *)FieldValue)[164];
            INAM->value37[165] = ((UINT8 *)FieldValue)[165];
            INAM->value37[166] = ((UINT8 *)FieldValue)[166];
            INAM->value37[167] = ((UINT8 *)FieldValue)[167];
            INAM->value37[168] = ((UINT8 *)FieldValue)[168];
            INAM->value37[169] = ((UINT8 *)FieldValue)[169];
            INAM->value37[170] = ((UINT8 *)FieldValue)[170];
            INAM->value37[171] = ((UINT8 *)FieldValue)[171];
            INAM->value37[172] = ((UINT8 *)FieldValue)[172];
            INAM->value37[173] = ((UINT8 *)FieldValue)[173];
            INAM->value37[174] = ((UINT8 *)FieldValue)[174];
            INAM->value37[175] = ((UINT8 *)FieldValue)[175];
            INAM->value37[176] = ((UINT8 *)FieldValue)[176];
            INAM->value37[177] = ((UINT8 *)FieldValue)[177];
            INAM->value37[178] = ((UINT8 *)FieldValue)[178];
            INAM->value37[179] = ((UINT8 *)FieldValue)[179];
            INAM->value37[180] = ((UINT8 *)FieldValue)[180];
            INAM->value37[181] = ((UINT8 *)FieldValue)[181];
            INAM->value37[182] = ((UINT8 *)FieldValue)[182];
            INAM->value37[183] = ((UINT8 *)FieldValue)[183];
            INAM->value37[184] = ((UINT8 *)FieldValue)[184];
            INAM->value37[185] = ((UINT8 *)FieldValue)[185];
            INAM->value37[186] = ((UINT8 *)FieldValue)[186];
            INAM->value37[187] = ((UINT8 *)FieldValue)[187];
            INAM->value37[188] = ((UINT8 *)FieldValue)[188];
            INAM->value37[189] = ((UINT8 *)FieldValue)[189];
            INAM->value37[190] = ((UINT8 *)FieldValue)[190];
            INAM->value37[191] = ((UINT8 *)FieldValue)[191];
            INAM->value37[192] = ((UINT8 *)FieldValue)[192];
            INAM->value37[193] = ((UINT8 *)FieldValue)[193];
            INAM->value37[194] = ((UINT8 *)FieldValue)[194];
            INAM->value37[195] = ((UINT8 *)FieldValue)[195];
            INAM->value37[196] = ((UINT8 *)FieldValue)[196];
            INAM->value37[197] = ((UINT8 *)FieldValue)[197];
            INAM->value37[198] = ((UINT8 *)FieldValue)[198];
            INAM->value37[199] = ((UINT8 *)FieldValue)[199];
            INAM->value37[200] = ((UINT8 *)FieldValue)[200];
            INAM->value37[201] = ((UINT8 *)FieldValue)[201];
            INAM->value37[202] = ((UINT8 *)FieldValue)[202];
            INAM->value37[203] = ((UINT8 *)FieldValue)[203];
            INAM->value37[204] = ((UINT8 *)FieldValue)[204];
            INAM->value37[205] = ((UINT8 *)FieldValue)[205];
            INAM->value37[206] = ((UINT8 *)FieldValue)[206];
            INAM->value37[207] = ((UINT8 *)FieldValue)[207];
            INAM->value37[208] = ((UINT8 *)FieldValue)[208];
            INAM->value37[209] = ((UINT8 *)FieldValue)[209];
            INAM->value37[210] = ((UINT8 *)FieldValue)[210];
            INAM->value37[211] = ((UINT8 *)FieldValue)[211];
            INAM->value37[212] = ((UINT8 *)FieldValue)[212];
            INAM->value37[213] = ((UINT8 *)FieldValue)[213];
            INAM->value37[214] = ((UINT8 *)FieldValue)[214];
            INAM->value37[215] = ((UINT8 *)FieldValue)[215];
            INAM->value37[216] = ((UINT8 *)FieldValue)[216];
            INAM->value37[217] = ((UINT8 *)FieldValue)[217];
            INAM->value37[218] = ((UINT8 *)FieldValue)[218];
            INAM->value37[219] = ((UINT8 *)FieldValue)[219];
            INAM->value37[220] = ((UINT8 *)FieldValue)[220];
            INAM->value37[221] = ((UINT8 *)FieldValue)[221];
            INAM->value37[222] = ((UINT8 *)FieldValue)[222];
            INAM->value37[223] = ((UINT8 *)FieldValue)[223];
            INAM->value37[224] = ((UINT8 *)FieldValue)[224];
            INAM->value37[225] = ((UINT8 *)FieldValue)[225];
            INAM->value37[226] = ((UINT8 *)FieldValue)[226];
            INAM->value37[227] = ((UINT8 *)FieldValue)[227];
            INAM->value37[228] = ((UINT8 *)FieldValue)[228];
            INAM->value37[229] = ((UINT8 *)FieldValue)[229];
            INAM->value37[230] = ((UINT8 *)FieldValue)[230];
            INAM->value37[231] = ((UINT8 *)FieldValue)[231];
            INAM->value37[232] = ((UINT8 *)FieldValue)[232];
            INAM->value37[233] = ((UINT8 *)FieldValue)[233];
            INAM->value37[234] = ((UINT8 *)FieldValue)[234];
            INAM->value37[235] = ((UINT8 *)FieldValue)[235];
            INAM->value37[236] = ((UINT8 *)FieldValue)[236];
            INAM->value37[237] = ((UINT8 *)FieldValue)[237];
            INAM->value37[238] = ((UINT8 *)FieldValue)[238];
            INAM->value37[239] = ((UINT8 *)FieldValue)[239];
            INAM->value37[240] = ((UINT8 *)FieldValue)[240];
            INAM->value37[241] = ((UINT8 *)FieldValue)[241];
            INAM->value37[242] = ((UINT8 *)FieldValue)[242];
            INAM->value37[243] = ((UINT8 *)FieldValue)[243];
            INAM->value37[244] = ((UINT8 *)FieldValue)[244];
            INAM->value37[245] = ((UINT8 *)FieldValue)[245];
            INAM->value37[246] = ((UINT8 *)FieldValue)[246];
            INAM->value37[247] = ((UINT8 *)FieldValue)[247];
            INAM->value37[248] = ((UINT8 *)FieldValue)[248];
            INAM->value37[249] = ((UINT8 *)FieldValue)[249];
            INAM->value37[250] = ((UINT8 *)FieldValue)[250];
            INAM->value37[251] = ((UINT8 *)FieldValue)[251];
            INAM->value37[252] = ((UINT8 *)FieldValue)[252];
            INAM->value37[253] = ((UINT8 *)FieldValue)[253];
            INAM->value37[254] = ((UINT8 *)FieldValue)[254];
            INAM->value37[255] = ((UINT8 *)FieldValue)[255];
            INAM->value37[256] = ((UINT8 *)FieldValue)[256];
            INAM->value37[257] = ((UINT8 *)FieldValue)[257];
            INAM->value37[258] = ((UINT8 *)FieldValue)[258];
            INAM->value37[259] = ((UINT8 *)FieldValue)[259];
            INAM->value37[260] = ((UINT8 *)FieldValue)[260];
            INAM->value37[261] = ((UINT8 *)FieldValue)[261];
            INAM->value37[262] = ((UINT8 *)FieldValue)[262];
            INAM->value37[263] = ((UINT8 *)FieldValue)[263];
            INAM->value37[264] = ((UINT8 *)FieldValue)[264];
            INAM->value37[265] = ((UINT8 *)FieldValue)[265];
            INAM->value37[266] = ((UINT8 *)FieldValue)[266];
            INAM->value37[267] = ((UINT8 *)FieldValue)[267];
            INAM->value37[268] = ((UINT8 *)FieldValue)[268];
            INAM->value37[269] = ((UINT8 *)FieldValue)[269];
            INAM->value37[270] = ((UINT8 *)FieldValue)[270];
            INAM->value37[271] = ((UINT8 *)FieldValue)[271];
            INAM->value37[272] = ((UINT8 *)FieldValue)[272];
            INAM->value37[273] = ((UINT8 *)FieldValue)[273];
            INAM->value37[274] = ((UINT8 *)FieldValue)[274];
            INAM->value37[275] = ((UINT8 *)FieldValue)[275];
            INAM->value37[276] = ((UINT8 *)FieldValue)[276];
            INAM->value37[277] = ((UINT8 *)FieldValue)[277];
            INAM->value37[278] = ((UINT8 *)FieldValue)[278];
            INAM->value37[279] = ((UINT8 *)FieldValue)[279];
            INAM->value37[280] = ((UINT8 *)FieldValue)[280];
            INAM->value37[281] = ((UINT8 *)FieldValue)[281];
            INAM->value37[282] = ((UINT8 *)FieldValue)[282];
            INAM->value37[283] = ((UINT8 *)FieldValue)[283];
            INAM->value37[284] = ((UINT8 *)FieldValue)[284];
            INAM->value37[285] = ((UINT8 *)FieldValue)[285];
            INAM->value37[286] = ((UINT8 *)FieldValue)[286];
            INAM->value37[287] = ((UINT8 *)FieldValue)[287];
            INAM->value37[288] = ((UINT8 *)FieldValue)[288];
            INAM->value37[289] = ((UINT8 *)FieldValue)[289];
            INAM->value37[290] = ((UINT8 *)FieldValue)[290];
            INAM->value37[291] = ((UINT8 *)FieldValue)[291];
            INAM->value37[292] = ((UINT8 *)FieldValue)[292];
            INAM->value37[293] = ((UINT8 *)FieldValue)[293];
            INAM->value37[294] = ((UINT8 *)FieldValue)[294];
            INAM->value37[295] = ((UINT8 *)FieldValue)[295];
            INAM->value37[296] = ((UINT8 *)FieldValue)[296];
            INAM->value37[297] = ((UINT8 *)FieldValue)[297];
            INAM->value37[298] = ((UINT8 *)FieldValue)[298];
            INAM->value37[299] = ((UINT8 *)FieldValue)[299];
            INAM->value37[300] = ((UINT8 *)FieldValue)[300];
            INAM->value37[301] = ((UINT8 *)FieldValue)[301];
            INAM->value37[302] = ((UINT8 *)FieldValue)[302];
            INAM->value37[303] = ((UINT8 *)FieldValue)[303];
            break;
        case 38: //data DATA ,, Struct
            DATA.Load();
            DATA->value38 = *(UINT8 *)FieldValue;
            break;
        case 39: //data DATA ,, Struct
            DATA.Load();
            DATA->value39 = *(UINT8 *)FieldValue;
            break;
        case 40: //data DATA ,, Struct
            DATA.Load();
            DATA->value40 = *(UINT8 *)FieldValue;
            break;
        case 41: //data DATA ,, Struct
            DATA.Load();
            DATA->value41 = *(UINT8 *)FieldValue;
            break;
        case 42: //data DATA ,, Struct
            DATA.Load();
            DATA->value42 = *(UINT8 *)FieldValue;
            break;
        case 43: //data DATA ,, Struct
            DATA.Load();
            DATA->value43 = *(UINT8 *)FieldValue;
            break;
        case 44: //data DATA ,, Struct
            DATA.Load();
            DATA->value44 = *(UINT8 *)FieldValue;
            break;
        case 45: //data DATA ,, Struct
            DATA.Load();
            DATA->value45 = *(UINT8 *)FieldValue;
            break;
        case 46: //data DATA ,, Struct
            DATA.Load();
            DATA->value46 = *(UINT8 *)FieldValue;
            break;
        case 47: //data DATA ,, Struct
            DATA.Load();
            DATA->value47 = *(UINT8 *)FieldValue;
            break;
        case 48: //data DATA ,, Struct
            DATA.Load();
            DATA->value48 = *(UINT8 *)FieldValue;
            break;
        case 49: //data DATA ,, Struct
            DATA.Load();
            DATA->value49 = *(UINT8 *)FieldValue;
            break;
        case 50: //data DATA ,, Struct
            DATA.Load();
            DATA->value50 = *(UINT8 *)FieldValue;
            break;
        case 51: //data DATA ,, Struct
            DATA.Load();
            DATA->value51 = *(UINT8 *)FieldValue;
            break;
        case 52: //data DATA ,, Struct
            DATA.Load();
            DATA->value52 = *(UINT8 *)FieldValue;
            break;
        case 53: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value53 = *(FORMID *)FieldValue;
            return true;
        case 54: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value54 = *(UINT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void WTHRRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //0iad Sunrise Image Space Modifier
            0IAD.Unload();
            return;
        case 8: //1iad Day Image Space Modifier
            1IAD.Unload();
            return;
        case 9: //2iad Sunset Image Space Modifier
            2IAD.Unload();
            return;
        case 10: //3iad Night Image Space Modifier
            3IAD.Unload();
            return;
        case 11: //4iad Unknown
            4IAD.Unload();
            return;
        case 12: //5iad Unknown
            5IAD.Unload();
            return;
        case 13: //dnam Cloud Textures - Layer 0
            DNAM.Unload();
            return;
        case 14: //cnam Cloud Textures - Layer 1
            CNAM.Unload();
            return;
        case 15: //anam Cloud Textures - Layer 2
            ANAM.Unload();
            return;
        case 16: //bnam Cloud Textures - Layer 3
            BNAM.Unload();
            return;
        case 17: //modl Model Filename
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 18: //modb_p Unknown
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 19: //modt_p Texture Files Hashes
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 20: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 21: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 22: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 23: //modd FaceGen Model Flags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 24: //lnam_p Unknown
            LNAM.Unload();
            return;
        case 25: //onam Cloud Speed
            return UNPARSEDDEL_FIELD25;
        case 26: //pnam_p Unused
            PNAM.Unload();
            return;
        case 27: //nam0 NAM0 ,, Struct
            NAM0.Unload();
            return;
        case 28: //nam0 NAM0 ,, Struct
            NAM0.Unload();
            return;
        case 29: //nam0 NAM0 ,, Struct
            NAM0.Unload();
            return;
        case 30: //nam0_p NAM0 ,, Struct
            NAM0.Unload();
            return;
        case 31: //fnam FNAM ,, Struct
            FNAM.Unload();
            return;
        case 32: //fnam FNAM ,, Struct
            FNAM.Unload();
            return;
        case 33: //fnam FNAM ,, Struct
            FNAM.Unload();
            return;
        case 34: //fnam FNAM ,, Struct
            FNAM.Unload();
            return;
        case 35: //fnam FNAM ,, Struct
            FNAM.Unload();
            return;
        case 36: //fnam FNAM ,, Struct
            FNAM.Unload();
            return;
        case 37: //inam_p Unused
            INAM.Unload();
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
        case 53: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        case 54: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        default:
            return;
        }
    }
}