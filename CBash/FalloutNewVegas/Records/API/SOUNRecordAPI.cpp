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
#include "..\SOUNRecord.h"

namespace FNV
{
UINT32 SOUNRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 10: //fnam Sound Filename
            return ISTRING_FIELD;
        case 11: //rnam Random Chance %
            return UINT8_FIELD;
        case 12: //sndd SNDD ,, Struct
            return UINT8_FIELD;
        case 13: //sndd SNDD ,, Struct
            return UINT8_FIELD;
        case 14: //sndd SNDD ,, Struct
            return SINT8_FIELD;
        case 15: //sndd_p SNDD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 16: //sndd SNDD ,, Struct
            return UINT32_FIELD;
        case 17: //sndd SNDD ,, Struct
            return SINT16_FIELD;
        case 18: //sndd SNDD ,, Struct
            return UINT8_FIELD;
        case 19: //sndd SNDD ,, Struct
            return UINT8_FIELD;
        case 20: //sndd SNDD ,, Struct
            return SINT16_FIELD;
        case 21: //sndd SNDD ,, Struct
            return SINT16_FIELD;
        case 22: //sndd SNDD ,, Struct
            return SINT32_FIELD;
        case 23: //sndd_p SNDD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 8;
                default:
                    return UNKNOWN_FIELD;
                }
        case 24: //sndd SNDD ,, Struct
            return SINT32_FIELD;
        case 25: //sndd SNDD ,, Struct
            return SINT32_FIELD;
        case 26: //sndx SNDX ,, Struct
            return UINT8_FIELD;
        case 27: //sndx SNDX ,, Struct
            return UINT8_FIELD;
        case 28: //sndx SNDX ,, Struct
            return SINT8_FIELD;
        case 29: //sndx_p SNDX ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 30: //sndx SNDX ,, Struct
            return UINT32_FIELD;
        case 31: //sndx SNDX ,, Struct
            return SINT16_FIELD;
        case 32: //sndx SNDX ,, Struct
            return UINT8_FIELD;
        case 33: //sndx SNDX ,, Struct
            return UINT8_FIELD;
        case 34: //anam Attenuation Curve
            return UNPARSED_FIELD;
        case 35: //gnam Reverb Attenuation Control
            return SINT16_FIELD;
        case 36: //hnam Priority
            return SINT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * SOUNRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 10: //fnam Sound Filename
            return FNAM.value;
        case 11: //rnam Random Chance %
            return RNAM.IsLoaded() ? &RNAM->value11 : NULL;
        case 12: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value12 : NULL;
        case 13: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value13 : NULL;
        case 14: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value14 : NULL;
        case 15: //sndd_p SNDD ,, Struct
            *FieldValues = SNDD.IsLoaded() ? &SNDD->value15[0] : NULL;
            return NULL;
        case 16: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value16 : NULL;
        case 17: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value17 : NULL;
        case 18: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value18 : NULL;
        case 19: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value19 : NULL;
        case 20: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value20 : NULL;
        case 21: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value21 : NULL;
        case 22: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value22 : NULL;
        case 23: //sndd_p SNDD ,, Struct
            *FieldValues = SNDD.IsLoaded() ? &SNDD->value23[0] : NULL;
            return NULL;
        case 24: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value24 : NULL;
        case 25: //sndd SNDD ,, Struct
            return SNDD.IsLoaded() ? &SNDD->value25 : NULL;
        case 26: //sndx SNDX ,, Struct
            return SNDX.IsLoaded() ? &SNDX->value26 : NULL;
        case 27: //sndx SNDX ,, Struct
            return SNDX.IsLoaded() ? &SNDX->value27 : NULL;
        case 28: //sndx SNDX ,, Struct
            return SNDX.IsLoaded() ? &SNDX->value28 : NULL;
        case 29: //sndx_p SNDX ,, Struct
            *FieldValues = SNDX.IsLoaded() ? &SNDX->value29[0] : NULL;
            return NULL;
        case 30: //sndx SNDX ,, Struct
            return SNDX.IsLoaded() ? &SNDX->value30 : NULL;
        case 31: //sndx SNDX ,, Struct
            return SNDX.IsLoaded() ? &SNDX->value31 : NULL;
        case 32: //sndx SNDX ,, Struct
            return SNDX.IsLoaded() ? &SNDX->value32 : NULL;
        case 33: //sndx SNDX ,, Struct
            return SNDX.IsLoaded() ? &SNDX->value33 : NULL;
        case 34: //anam Attenuation Curve
            return UNPARSEDGET_FIELD34;
        case 35: //gnam Reverb Attenuation Control
            return GNAM.IsLoaded() ? &GNAM->value35 : NULL;
        case 36: //hnam Priority
            return HNAM.IsLoaded() ? &HNAM->value36 : NULL;
        default:
            return NULL;
        }
    }

bool SOUNRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 10: //fnam Sound Filename
            FNAM.Copy((STRING)FieldValue);
            break;
        case 11: //rnam Random Chance %
            RNAM.Load();
            RNAM->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value12 = *(UINT8 *)FieldValue;
            break;
        case 13: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value13 = *(UINT8 *)FieldValue;
            break;
        case 14: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value14 = *(SINT8 *)FieldValue;
            break;
        case 15: //sndd_p SNDD ,, Struct
            if(ArraySize != 1)
                break;
            SNDD.Load();
            SNDD->value15[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 16: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value16 = *(UINT32 *)FieldValue;
            break;
        case 17: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value17 = *(SINT16 *)FieldValue;
            break;
        case 18: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value18 = *(UINT8 *)FieldValue;
            break;
        case 19: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value19 = *(UINT8 *)FieldValue;
            break;
        case 20: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value20 = *(SINT16 *)FieldValue;
            break;
        case 21: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value21 = *(SINT16 *)FieldValue;
            break;
        case 22: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value22 = *(SINT32 *)FieldValue;
            break;
        case 23: //sndd_p SNDD ,, Struct
            if(ArraySize != 8)
                break;
            SNDD.Load();
            SNDD->value23[0] = ((UINT8 *)FieldValue)[0];
            SNDD->value23[1] = ((UINT8 *)FieldValue)[1];
            SNDD->value23[2] = ((UINT8 *)FieldValue)[2];
            SNDD->value23[3] = ((UINT8 *)FieldValue)[3];
            SNDD->value23[4] = ((UINT8 *)FieldValue)[4];
            SNDD->value23[5] = ((UINT8 *)FieldValue)[5];
            SNDD->value23[6] = ((UINT8 *)FieldValue)[6];
            SNDD->value23[7] = ((UINT8 *)FieldValue)[7];
            break;
        case 24: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value24 = *(SINT32 *)FieldValue;
            break;
        case 25: //sndd SNDD ,, Struct
            SNDD.Load();
            SNDD->value25 = *(SINT32 *)FieldValue;
            break;
        case 26: //sndx SNDX ,, Struct
            SNDX.Load();
            SNDX->value26 = *(UINT8 *)FieldValue;
            break;
        case 27: //sndx SNDX ,, Struct
            SNDX.Load();
            SNDX->value27 = *(UINT8 *)FieldValue;
            break;
        case 28: //sndx SNDX ,, Struct
            SNDX.Load();
            SNDX->value28 = *(SINT8 *)FieldValue;
            break;
        case 29: //sndx_p SNDX ,, Struct
            if(ArraySize != 1)
                break;
            SNDX.Load();
            SNDX->value29[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 30: //sndx SNDX ,, Struct
            SNDX.Load();
            SNDX->value30 = *(UINT32 *)FieldValue;
            break;
        case 31: //sndx SNDX ,, Struct
            SNDX.Load();
            SNDX->value31 = *(SINT16 *)FieldValue;
            break;
        case 32: //sndx SNDX ,, Struct
            SNDX.Load();
            SNDX->value32 = *(UINT8 *)FieldValue;
            break;
        case 33: //sndx SNDX ,, Struct
            SNDX.Load();
            SNDX->value33 = *(UINT8 *)FieldValue;
            break;
        case 34: //anam Attenuation Curve
            return UNPARSEDGET_FIELD34;
        case 35: //gnam Reverb Attenuation Control
            GNAM.Load();
            GNAM->value35 = *(SINT16 *)FieldValue;
            break;
        case 36: //hnam Priority
            HNAM.Load();
            HNAM->value36 = *(SINT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void SOUNRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 10: //fnam Sound Filename
            FNAM.Unload();
            return;
        case 11: //rnam Random Chance %
            RNAM.Unload();
            return;
        case 12: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 13: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 14: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 15: //sndd_p SNDD ,, Struct
            SNDD.Unload();
            return;
        case 16: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 17: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 18: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 19: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 20: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 21: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 22: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 23: //sndd_p SNDD ,, Struct
            SNDD.Unload();
            return;
        case 24: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 25: //sndd SNDD ,, Struct
            SNDD.Unload();
            return;
        case 26: //sndx SNDX ,, Struct
            SNDX.Unload();
            return;
        case 27: //sndx SNDX ,, Struct
            SNDX.Unload();
            return;
        case 28: //sndx SNDX ,, Struct
            SNDX.Unload();
            return;
        case 29: //sndx_p SNDX ,, Struct
            SNDX.Unload();
            return;
        case 30: //sndx SNDX ,, Struct
            SNDX.Unload();
            return;
        case 31: //sndx SNDX ,, Struct
            SNDX.Unload();
            return;
        case 32: //sndx SNDX ,, Struct
            SNDX.Unload();
            return;
        case 33: //sndx SNDX ,, Struct
            SNDX.Unload();
            return;
        case 34: //anam Attenuation Curve
            return UNPARSEDDEL_FIELD34;
        case 35: //gnam Reverb Attenuation Control
            GNAM.Unload();
            return;
        case 36: //hnam Priority
            HNAM.Unload();
            return;
        default:
            return;
        }
    }
}