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
#include "..\CSNORecord.h"

namespace FNV
{
UINT32 CSNORecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
            return UNKNOWN_FIELD;
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
            return UNKNOWN_FIELD;
        case 7: //full
            return STRING_FIELD;
        case 8: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 9: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 10: //data DATA ,, Struct
            return UINT32_FIELD;
        case 11: //data DATA ,, Struct
            return UINT32_FIELD;
        case 12: //data DATA ,, Struct
            return UINT32_FIELD;
        case 13: //data DATA ,, Struct
            return FORMID_FIELD;
        case 14: //data DATA ,, Struct
            return FORMID_FIELD;
        case 15: //data DATA ,, Struct
            return UINT32_FIELD;
        case 16: //modl Roulette Chip
            return ISTRING_FIELD;
        case 17: //modl Slot Machine Model
            return ISTRING_FIELD;
        case 18: //mod2 Slot Machine Model (again?)
            return ISTRING_FIELD;
        case 19: //mod3 BlackJack Table Model
            return ISTRING_FIELD;
        case 20: //mod4 Roulette Table Model
            return ISTRING_FIELD;
        case 21: //icon Symbol W
            return ISTRING_FIELD;
        case 22: //ico2 Deck 4
            return ISTRING_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * CSNORecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //full
            return FULL.value;
        case 8: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value8 : NULL;
        case 9: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value9 : NULL;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value10 : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value11 : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value13 : NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value15 : NULL;
        case 16: //modl Roulette Chip
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 17: //modl Slot Machine Model
            return MODL.value;
        case 18: //mod2 Slot Machine Model (again?)
            return MOD2.value;
        case 19: //mod3 BlackJack Table Model
            return MOD3.value;
        case 20: //mod4 Roulette Table Model
            return MOD4.value;
        case 21: //icon Symbol W
            return ICON.value;
        case 22: //ico2 Deck 4
            return ICO2.IsLoaded() ? ICO2->ICO2.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool CSNORecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
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
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //data DATA ,, Struct
            DATA.Load();
            DATA->value8 = *(FLOAT32 *)FieldValue;
            break;
        case 9: //data DATA ,, Struct
            DATA.Load();
            DATA->value9 = *(FLOAT32 *)FieldValue;
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->value10 = *(UINT32 *)FieldValue;
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->value11 = *(UINT32 *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->value12 = *(UINT32 *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->value13 = *(FORMID *)FieldValue;
            return true;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->value14 = *(FORMID *)FieldValue;
            return true;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->value15 = *(UINT32 *)FieldValue;
            break;
        case 16: //modl Roulette Chip
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 17: //modl Slot Machine Model
            MODL.Copy((STRING)FieldValue);
            break;
        case 18: //mod2 Slot Machine Model (again?)
            MOD2.Copy((STRING)FieldValue);
            break;
        case 19: //mod3 BlackJack Table Model
            MOD3.Copy((STRING)FieldValue);
            break;
        case 20: //mod4 Roulette Table Model
            MOD4.Copy((STRING)FieldValue);
            break;
        case 21: //icon Symbol W
            ICON.Copy((STRING)FieldValue);
            break;
        case 22: //ico2 Deck 4
            ICO2.Load();
            ICO2->ICO2.Copy((STRING)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void CSNORecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //full
            FULL.Unload();
            return;
        case 8: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 9: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 10: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 11: //data DATA ,, Struct
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
        case 16: //modl Roulette Chip
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 17: //modl Slot Machine Model
            MODL.Unload();
            return;
        case 18: //mod2 Slot Machine Model (again?)
            MOD2.Unload();
            return;
        case 19: //mod3 BlackJack Table Model
            MOD3.Unload();
            return;
        case 20: //mod4 Roulette Table Model
            MOD4.Unload();
            return;
        case 21: //icon Symbol W
            ICON.Unload();
            return;
        case 22: //ico2 Deck 4
            if(ICO2.IsLoaded())
                ICO2->ICO2.Unload();
            return;
        default:
            return;
        }
    }
}