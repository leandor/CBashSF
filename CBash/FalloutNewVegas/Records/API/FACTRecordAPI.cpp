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
#include "..\FACTRecord.h"

namespace FNV
{
UINT32 FACTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 8: //relations
            if(ListFieldID == 0) //relations
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)XNAM.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= XNAM.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //faction
                    return FORMID_FIELD;
                case 2: //mod
                    return SINT32_FIELD;
                case 3: //groupReactionType
                    return UINT32_TYPE_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 9: //flags
            return UINT16_FLAG_FIELD;
        case 10: //unused1
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
        case 11: //crimeGoldMultiplier
            return FLOAT32_FIELD;
        case 12: //ranks
            if(ListFieldID == 0) //ranks
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)RNAM.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= RNAM.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //rank
                    return SINT32_FIELD;
                case 2: //male
                    return STRING_FIELD;
                case 3: //female
                    return STRING_FIELD;
                case 4: //insigniaPath
                    return ISTRING_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 13: //reputation
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * FACTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //relations
            if(ListIndex >= XNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //faction
                    return &XNAM.value[ListIndex]->faction;
                case 2: //mod
                    return &XNAM.value[ListIndex]->mod;
                case 3: //groupReactionType
                    return &XNAM.value[ListIndex]->groupReactionType;
                default:
                    return NULL;
                }
            return NULL;
        case 9: //flags
            return &DATA.value.flags;
        case 10: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 11: ///crimeGoldMultiplier
            return CNAM.value;
        case 12: //ranks
            if(ListIndex >= RNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //rank
                    return &RNAM.value[ListIndex]->RNAM.value;
                case 2: //male
                    return RNAM.value[ListIndex]->MNAM.value;
                case 3: //female
                    return RNAM.value[ListIndex]->FNAM.value;
                case 4: //insigniaPath
                    return RNAM.value[ListIndex]->INAM.value;
                default:
                    return NULL;
                }
            return NULL;
        case 13: //reputation
            return WMI1.IsLoaded() ? &WMI1.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool FACTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 8: //relations
            if(ListFieldID == 0) //relationsSize
                {
                XNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= XNAM.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //faction
                    XNAM.value[ListIndex]->faction = *(FORMID *)FieldValue;
                    return true;
                case 2: //mod
                    XNAM.value[ListIndex]->mod = *(SINT32 *)FieldValue;
                    break;
                case 3: //groupReactionType
                    XNAM.value[ListIndex]->SetType(*(UINT32 *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 9: //flags
            SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 10: //unused1
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 11: //crimeGoldMultiplier
            CNAM.Load();
            *CNAM.value = *(FLOAT32 *)FieldValue;
            break;
        case 12: //ranks
            if(ListFieldID == 0) //ranksSize
                {
                RNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= RNAM.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //rank
                    RNAM.value[ListIndex]->RNAM.value = *(SINT32 *)FieldValue;
                    break;
                case 2: //male
                    RNAM.value[ListIndex]->MNAM.Copy((STRING)FieldValue);
                    break;
                case 3: //female
                    RNAM.value[ListIndex]->FNAM.Copy((STRING)FieldValue);
                    break;
                case 4: //insigniaPath
                    RNAM.value[ListIndex]->INAM.Copy((STRING)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 13: //reputation
            WMI1.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void FACTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    FNVXNAM defaultXNAM;
    FACTDATA defaultDATA;
    FACTRNAM defaultRNAM;

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
        case 8: //relations
            if(ListFieldID == 0) //relations
                {
                XNAM.Unload();
                return;
                }

            if(ListIndex >= XNAM.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //faction
                    XNAM.value[ListIndex]->faction = defaultXNAM.faction;
                    return;
                case 2: //mod
                    XNAM.value[ListIndex]->mod = defaultXNAM.mod;
                    return;
                case 3: //groupReactionType
                    XNAM.value[ListIndex]->groupReactionType = defaultXNAM.groupReactionType;
                    return;
                default:
                    return;
                }
            return;
        case 9: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 10: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 11: //crimeGoldMultiplier
            CNAM.Unload();
            return;
        case 12: //ranks
            if(ListFieldID == 0) //ranks
                {
                RNAM.Unload();
                return;
                }

            if(ListIndex >= RNAM.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //rank
                    RNAM.value[ListIndex]->RNAM.value = defaultRNAM.RNAM.value;
                    return;
                case 2: //male
                    RNAM.value[ListIndex]->MNAM.Unload();
                    return;
                case 3: //female
                    RNAM.value[ListIndex]->FNAM.Unload();
                    return;
                case 4: //insigniaPath
                    RNAM.value[ListIndex]->INAM.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 13: //reputation
            WMI1.Unload();
            return;
        default:
            return;
        }
    }
}