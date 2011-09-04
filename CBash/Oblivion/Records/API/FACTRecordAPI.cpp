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

namespace Ob
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
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //full
            return STRING_FIELD;
        case 6: //relations
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
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 7: //flags
            return UINT8_FLAG_FIELD;
        case 8: //crimeGoldMultiplier
            return FLOAT32_FIELD;
        case 9: //ranks
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
            return cleaned_flag1();
        case 2: //fid
            return &formID;
        case 3: //flags2
            return cleaned_flag2();
        case 4: //eid
            return EDID.value;
        case 5: //full
            return FULL.value;
        case 6: //relations
            if(ListIndex >= XNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //faction
                    return &XNAM.value[ListIndex]->faction;
                case 2: //mod
                    return &XNAM.value[ListIndex]->mod;
                default:
                    return NULL;
                }
            return NULL;
        case 7: //flags
            return &DATA.value;
        case 8: //crimeGoldMultiplier
            return CNAM.value;
        case 9: //ranks
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
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(UINT32 *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 6: //relations
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
                default:
                    break;
                }
            break;
        case 7: //flags
            SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 8: //crimeGoldMultiplier
            CNAM.Load();
            *CNAM.value = *(FLOAT32 *)FieldValue;
            break;
        case 9: //ranks
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
        default:
            break;
        }
    return false;
    }

void FACTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENXNAM defaultXNAM;
    FACTRNAM defaultRNAM;

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
        case 5: //full
            FULL.Unload();
            return;
        case 6: //relations
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
                default:
                    return;
                }
            return;
        case 7: //flags
            DATA.Unload();
            return;
        case 8: //crimeGoldMultiplier
            CNAM.Unload();
            return;
        case 9: //ranks
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
        default:
            return;
        }
    return;
    }
}