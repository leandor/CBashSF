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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#include "..\..\..\Common.h"
#include "..\LVLCRecord.h"

namespace Ob
{
UINT32 LVLCRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //chanceNone
            return UINT8_FIELD;
        case 6: //flags
            return UINT8_FLAG_FIELD;
        case 7: //script
            return FORMID_FIELD;
        case 8: //template
            return FORMID_FIELD;
        case 9: //entries
            if(ListFieldID == 0) //entries
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)Entries.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= Entries.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //level
                    return SINT16_FIELD;
                case 2: //unused1
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
                case 3: //listId
                    return FORMID_FIELD;
                case 4: //count
                    return SINT16_FIELD;
                case 5: //unused2
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
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * LVLCRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return cleaned_flag1();
        case 2: //fid
            return &formID;
        case 3: //flags2
            return cleaned_flag2();
        case 4: //eid
            return EDID.value;
        case 5: //chanceNone
            return &LVLD.value;
        case 6: //flags
            return LVLF.IsLoaded() ? LVLF.value : NULL;
        case 7: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 8: //template
            return TNAM.IsLoaded() ? &TNAM.value : NULL;
        case 9: //entries
            if(ListIndex >= Entries.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //level
                    return &Entries.value[ListIndex]->level;
                case 2: //unused1
                    *FieldValues = &Entries.value[ListIndex]->unused1[0];
                    return NULL;
                case 3: //listId
                    return &Entries.value[ListIndex]->listId;
                case 4: //count
                    return &Entries.value[ListIndex]->count;
                case 5: //unused2
                    *FieldValues = &Entries.value[ListIndex]->unused2[0];
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool LVLCRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(UINT32 *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //chanceNone
            LVLD.value = *(UINT8 *)FieldValue;
            if((LVLD.value & fAltCalcFromAllLevels) != 0)
                {
                LVLD.value &= ~fAltCalcFromAllLevels;
                IsCalcFromAllLevels(true);
                }
            break;
        case 6: //flags
            SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 7: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 8: //template
            TNAM.value = *(FORMID *)FieldValue;
            return true;
        case 9: //entries
            if(ListFieldID == 0) //entriesSize
                {
                Entries.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Entries.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //level
                    Entries.value[ListIndex]->level = *(SINT16 *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 2)
                        break;
                    Entries.value[ListIndex]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Entries.value[ListIndex]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 3: //listId
                    Entries.value[ListIndex]->listId = *(FORMID *)FieldValue;
                    return true;
                case 4: //count
                    Entries.value[ListIndex]->count = *(SINT16 *)FieldValue;
                    break;
                case 5: //unused2
                    if(ArraySize != 2)
                        break;
                    Entries.value[ListIndex]->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    Entries.value[ListIndex]->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void LVLCRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    LVLLVLO defaultLVLO;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //chanceNone
            LVLD.Unload();
            return;
        case 6: //flags
            LVLF.Unload();
            return;
        case 7: //script
            SCRI.Unload();
            return;
        case 8: //template
            TNAM.Unload();
            return;
        case 9: //entries
            if(ListFieldID == 0) //entries
                {
                Entries.Unload();
                return;
                }

            if(ListIndex >= Entries.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //level
                    Entries.value[ListIndex]->level = defaultLVLO.level;
                    return;
                case 2: //unused1
                    Entries.value[ListIndex]->unused1[0] = defaultLVLO.unused1[0];
                    Entries.value[ListIndex]->unused1[1] = defaultLVLO.unused1[1];
                    return;
                case 3: //listId
                    Entries.value[ListIndex]->listId = defaultLVLO.listId;
                    return;
                case 4: //count
                    Entries.value[ListIndex]->count = defaultLVLO.count;
                    return;
                case 5: //unused2
                    Entries.value[ListIndex]->unused2[0] = defaultLVLO.unused2[0];
                    Entries.value[ListIndex]->unused2[1] = defaultLVLO.unused2[1];
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    return;
    }
}