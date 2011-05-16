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
#include "..\LVLIRecord.h"

namespace FNV
{
UINT32 LVLIRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //boundX1
            return SINT16_FIELD;
        case 8: //boundY1
            return SINT16_FIELD;
        case 9: //boundZ1
            return SINT16_FIELD;
        case 10: //boundX2
            return SINT16_FIELD;
        case 11: //boundY2
            return SINT16_FIELD;
        case 12: //boundZ2
            return SINT16_FIELD;
        case 13: //chanceNone
            return UINT8_FIELD;
        case 14: //flags
            return UINT8_FLAG_FIELD;
        case 15: //globalId
            return FORMID_FIELD;
        case 16: //entries
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
                case 6: //owner
                    return FORMID_FIELD;
                case 7: //globalOrRank
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return Entries.value[ListIndex]->IsGlobal() ? FORMID_FIELD : UINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                case 8: //condition
                    return FLOAT32_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * LVLIRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //boundX1
            return &OBND.value.x1;
        case 8: //boundY1
            return &OBND.value.y1;
        case 9: //boundZ1
            return &OBND.value.z1;
        case 10: //boundX2
            return &OBND.value.x2;
        case 11: //boundY2
            return &OBND.value.y2;
        case 12: //boundZ2
            return &OBND.value.z2;
        case 13: //chanceNone
            return &LVLD.value;
        case 14: //flags
            return &LVLF.value;
        case 15: //globalId
            return &LVLG.value;
        case 16: //entries
            if(ListIndex >= Entries.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //level
                    return &Entries.value[ListIndex]->LVLO.value.level;
                case 2: //unused1
                    *FieldValues = &Entries.value[ListIndex]->LVLO.value.unused1[0];
                    return NULL;
                case 3: //listId
                    return &Entries.value[ListIndex]->LVLO.value.listId;
                case 4: //count
                    return &Entries.value[ListIndex]->LVLO.value.count;
                case 5: //unused2
                    *FieldValues = &Entries.value[ListIndex]->LVLO.value.unused2[0];
                    return NULL;
                case 6: //owner
                    return Entries.value[ListIndex]->COED.IsLoaded() ? &Entries.value[ListIndex]->COED->owner : NULL;
                case 7: //globalOrRank
                    return Entries.value[ListIndex]->COED.IsLoaded() ? &Entries.value[ListIndex]->COED->globalOrRank : NULL;
                case 8: //condition
                    return Entries.value[ListIndex]->COED.IsLoaded() ? &Entries.value[ListIndex]->COED->condition : NULL;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool LVLIRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //boundX1
            OBND.value.x1 = *(SINT16 *)FieldValue;
            break;
        case 8: //boundY1
            OBND.value.y1 = *(SINT16 *)FieldValue;
            break;
        case 9: //boundZ1
            OBND.value.z1 = *(SINT16 *)FieldValue;
            break;
        case 10: //boundX2
            OBND.value.x2 = *(SINT16 *)FieldValue;
            break;
        case 11: //boundY2
            OBND.value.y2 = *(SINT16 *)FieldValue;
            break;
        case 12: //boundZ2
            OBND.value.z2 = *(SINT16 *)FieldValue;
            break;
        case 13: //chanceNone
            LVLD.value = *(UINT8 *)FieldValue;
            break;
        case 14: //flags
            LVLF.value = *(UINT8 *)FieldValue;
            break;
        case 15: //globalId
            LVLG.value = *(FORMID *)FieldValue;
            return true;
        case 16: //entries
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
                    Entries.value[ListIndex]->LVLO.value.level = *(SINT16 *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 2)
                        break;
                    Entries.value[ListIndex]->LVLO.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Entries.value[ListIndex]->LVLO.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 3: //listId
                    Entries.value[ListIndex]->LVLO.value.listId = *(FORMID *)FieldValue;
                    return true;
                case 4: //count
                    Entries.value[ListIndex]->LVLO.value.count = *(SINT16 *)FieldValue;
                    break;
                case 5: //unused2
                    if(ArraySize != 2)
                        break;
                    Entries.value[ListIndex]->LVLO.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    Entries.value[ListIndex]->LVLO.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 6: //owner
                    Entries.value[ListIndex]->COED.Load();
                    Entries.value[ListIndex]->COED->owner = *(FORMID *)FieldValue;
                    return true;
                case 7: //globalOrRank
                    Entries.value[ListIndex]->COED.Load();
                    Entries.value[ListIndex]->COED->globalOrRank = *(FORMID_OR_UINT32 *)FieldValue;
                    return true;
                case 8: //condition
                    Entries.value[ListIndex]->COED.Load();
                    Entries.value[ListIndex]->COED->condition = *(FLOAT32 *)FieldValue;
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

void LVLIRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    LVLLVLO defaultLVLO;
    GENCOED defaultCOED;
    FNVMODS defaultMODS;
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
        case 7: //boundX1
            OBND.value.x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            OBND.value.y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            OBND.value.z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            OBND.value.x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            OBND.value.y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            OBND.value.z2 = defaultOBND.z2;
            return;
        case 13: //chanceNone
            LVLD.Unload();
            return;
        case 14: //flags
            LVLF.Unload();
            return;
        case 15: //globalId
            LVLG.Unload();
            return;
        case 16: //entries
            if(ListFieldID == 0) //entriesSize
                {
                Entries.Unload();
                return;
                }

            if(ListIndex >= Entries.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //level
                    Entries.value[ListIndex]->LVLO.value.level = defaultLVLO.level;
                    return;
                case 2: //unused1
                    Entries.value[ListIndex]->LVLO.value.unused1[0] = defaultLVLO.unused1[0];
                    Entries.value[ListIndex]->LVLO.value.unused1[1] = defaultLVLO.unused1[1];
                    return;
                case 3: //listId
                    Entries.value[ListIndex]->LVLO.value.listId = defaultLVLO.listId;
                    return;
                case 4: //count
                    Entries.value[ListIndex]->LVLO.value.count = defaultLVLO.count;
                    return;
                case 5: //unused2
                    Entries.value[ListIndex]->LVLO.value.unused2[0] = defaultLVLO.unused2[0];
                    Entries.value[ListIndex]->LVLO.value.unused2[1] = defaultLVLO.unused2[1];
                    return;
                case 6: //owner
                    if(Entries.value[ListIndex]->COED.IsLoaded())
                        Entries.value[ListIndex]->COED->owner = defaultCOED.owner;
                    return;
                case 7: //globalOrRank
                    if(Entries.value[ListIndex]->COED.IsLoaded())
                        Entries.value[ListIndex]->COED->globalOrRank = defaultCOED.globalOrRank;
                    return;
                case 8: //condition
                    if(Entries.value[ListIndex]->COED.IsLoaded())
                        Entries.value[ListIndex]->COED->condition = defaultCOED.condition;
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    }
}