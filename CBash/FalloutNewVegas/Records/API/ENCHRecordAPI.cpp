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
#include "..\ENCHRecord.h"

namespace FNV
{
UINT32 ENCHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 6: //eid
            return ISTRING_FIELD;
        case 7: //full Name
            return STRING_FIELD;
        case 8: //enit ENIT ,, Struct
            return UINT32_FIELD;
        case 9: //enit_p ENIT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //enit_p ENIT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 11: //enit ENIT ,, Struct
            return UINT8_FIELD;
        case 12: //enit_p ENIT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //efid Base Effect
            return FORMID_FIELD;
        case 14: //efit Effect Item
            return UINT32_FIELD;
        case 15: //efit Effect Item
            return UINT32_FIELD;
        case 16: //efit Effect Item
            return UINT32_FIELD;
        case 17: //efit Effect Item
            return UINT32_FIELD;
        case 18: //efit Effect Item
            return UNPARSED_FIELD;
        case 19: //ctda Conditions
            return UINT8_FIELD;
        case 20: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 21: //ctda Conditions
            return UNPARSED_FIELD;
        case 22: //ctda Conditions
            return UINT32_FIELD;
        case 23: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 24: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 25: //ctda Conditions
            return UINT32_FIELD;
        case 26: //ctda Conditions
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * ENCHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 6: //eid
            return EDID.value;
        case 7: //full Name
            return FULL.value;
        case 8: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value8 : NULL;
        case 9: //enit_p ENIT ,, Struct
            *FieldValues = ENIT.IsLoaded() ? &ENIT->value9[0] : NULL;
            return NULL;
        case 10: //enit_p ENIT ,, Struct
            *FieldValues = ENIT.IsLoaded() ? &ENIT->value10[0] : NULL;
            return NULL;
        case 11: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value11 : NULL;
        case 12: //enit_p ENIT ,, Struct
            *FieldValues = ENIT.IsLoaded() ? &ENIT->value12[0] : NULL;
            return NULL;
        case 13: //efid Base Effect
            return EFID.IsLoaded() ? &EFID->EFID->value13 : NULL;
        case 14: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value14 : NULL;
        case 15: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value15 : NULL;
        case 16: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value16 : NULL;
        case 17: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value17 : NULL;
        case 18: //efit Effect Item
            return UNPARSEDGET_FIELD18;
        case 19: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value19 : NULL;
        case 20: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value20[0] : NULL;
            return NULL;
        case 21: //ctda Conditions
            return UNPARSEDGET_FIELD21;
        case 22: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value22 : NULL;
        case 23: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value23[0] : NULL;
            return NULL;
        case 24: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value24[0] : NULL;
            return NULL;
        case 25: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value25 : NULL;
        case 26: //ctda Conditions
            return UNPARSEDGET_FIELD26;
        default:
            return NULL;
        }
    }

bool ENCHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 6: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 7: //full Name
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value8 = *(UINT32 *)FieldValue;
            break;
        case 9: //enit_p ENIT ,, Struct
            if(ArraySize != 4)
                break;
            ENIT.Load();
            ENIT->value9[0] = ((UINT8 *)FieldValue)[0];
            ENIT->value9[1] = ((UINT8 *)FieldValue)[1];
            ENIT->value9[2] = ((UINT8 *)FieldValue)[2];
            ENIT->value9[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 10: //enit_p ENIT ,, Struct
            if(ArraySize != 4)
                break;
            ENIT.Load();
            ENIT->value10[0] = ((UINT8 *)FieldValue)[0];
            ENIT->value10[1] = ((UINT8 *)FieldValue)[1];
            ENIT->value10[2] = ((UINT8 *)FieldValue)[2];
            ENIT->value10[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 11: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //enit_p ENIT ,, Struct
            if(ArraySize != 3)
                break;
            ENIT.Load();
            ENIT->value12[0] = ((UINT8 *)FieldValue)[0];
            ENIT->value12[1] = ((UINT8 *)FieldValue)[1];
            ENIT->value12[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 13: //efid Base Effect
            EFID.Load();
            EFID->EFID.Load();
            EFID->EFID->value13 = *(FORMID *)FieldValue;
            return true;
        case 14: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value14 = *(UINT32 *)FieldValue;
            break;
        case 15: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value15 = *(UINT32 *)FieldValue;
            break;
        case 16: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value16 = *(UINT32 *)FieldValue;
            break;
        case 17: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value17 = *(UINT32 *)FieldValue;
            break;
        case 18: //efit Effect Item
            return UNPARSEDGET_FIELD18;
        case 19: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value19 = *(UINT8 *)FieldValue;
            break;
        case 20: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value20[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value20[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value20[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 21: //ctda Conditions
            return UNPARSEDGET_FIELD21;
        case 22: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value22 = *(UINT32 *)FieldValue;
            break;
        case 23: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value23[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value23[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value23[2] = ((UINT8 *)FieldValue)[2];
            EFID->CTDA->value23[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 24: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value24[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value24[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value24[2] = ((UINT8 *)FieldValue)[2];
            EFID->CTDA->value24[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 25: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value25 = *(UINT32 *)FieldValue;
            break;
        case 26: //ctda Conditions
            return UNPARSEDGET_FIELD26;
        default:
            break;
        }
    return false;
    }

void ENCHRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 6: //eid
            EDID.Unload();
            return;
        case 7: //full Name
            FULL.Unload();
            return;
        case 8: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 9: //enit_p ENIT ,, Struct
            ENIT.Unload();
            return;
        case 10: //enit_p ENIT ,, Struct
            ENIT.Unload();
            return;
        case 11: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 12: //enit_p ENIT ,, Struct
            ENIT.Unload();
            return;
        case 13: //efid Base Effect
            if(EFID.IsLoaded())
                EFID->EFID.Unload();
            return;
        case 14: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 15: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 16: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 17: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 18: //efit Effect Item
            return UNPARSEDDEL_FIELD18;
        case 19: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 20: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 21: //ctda Conditions
            return UNPARSEDDEL_FIELD21;
        case 22: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 23: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 24: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 25: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 26: //ctda Conditions
            return UNPARSEDDEL_FIELD26;
        default:
            return;
        }
    }
}