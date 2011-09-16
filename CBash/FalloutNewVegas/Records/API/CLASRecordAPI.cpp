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
#include "..\CLASRecord.h"

namespace FNV
{
UINT32 CLASRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 8: //description
            return STRING_FIELD;
        case 9: //iconPath
            return ISTRING_FIELD;
        case 10: //smallIconPath
            return ISTRING_FIELD;
        case 11: //tagSkills1
            return SINT32_FIELD;
        case 12: //tagSkills2
            return SINT32_FIELD;
        case 13: //tagSkills3
            return SINT32_FIELD;
        case 14: //tagSkills4
            return SINT32_FIELD;
        case 15: //flags
            return UINT32_FLAG_FIELD;
        case 16: //services
            return UINT32_FLAG_FIELD;
        case 17: //trainSkill
            return SINT8_FIELD;
        case 18: //trainLevel
            return UINT8_FIELD;
        case 19: //unused1
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
        case 20: //strength
            return UINT8_FIELD;
        case 21: //perception
            return UINT8_FIELD;
        case 22: //endurance
            return UINT8_FIELD;
        case 23: //charisma
            return UINT8_FIELD;
        case 24: //intelligence
            return UINT8_FIELD;
        case 25: //agility
            return UINT8_FIELD;
        case 26: //luck
            return UINT8_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * CLASRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //description
            return DESC.value;
        case 9: //iconPath
            return ICON.value;
        case 10: //smallIconPath
            return MICO.value;
        case 11: //tagSkills1
            return &DATA.value.tagSkills[0];
        case 12: //tagSkills2
            return &DATA.value.tagSkills[1];
        case 13: //tagSkills3
            return &DATA.value.tagSkills[2];
        case 14: //tagSkills4
            return &DATA.value.tagSkills[3];
        case 15: //flags
            return &DATA.value.flags;
        case 16: //services
            return &DATA.value.services;
        case 17: //trainSkill
            return &DATA.value.trainSkill;
        case 18: //trainLevel
            return &DATA.value.trainLevel;
        case 19: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 20: //strength
            return &ATTR.value.strength;
        case 21: //perception
            return &ATTR.value.perception;
        case 22: //endurance
            return &ATTR.value.endurance;
        case 23: //charisma
            return &ATTR.value.charisma;
        case 24: //intelligence
            return &ATTR.value.intelligence;
        case 25: //agility
            return &ATTR.value.agility;
        case 26: //luck
            return &ATTR.value.luck;
        default:
            return NULL;
        }
    return NULL;
    }

bool CLASRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 8: //description
            DESC.Copy((STRING)FieldValue);
            break;
        case 9: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 10: //smallIconPath
            MICO.Copy((STRING)FieldValue);
            break;
        case 11: //tagSkills1
            DATA.value.tagSkills[0] = *(SINT32 *)FieldValue;
            break;
        case 12: //tagSkills2
            DATA.value.tagSkills[1] = *(SINT32 *)FieldValue;
            break;
        case 13: //tagSkills3
            DATA.value.tagSkills[2] = *(SINT32 *)FieldValue;
            break;
        case 14: //tagSkills4
            DATA.value.tagSkills[3] = *(SINT32 *)FieldValue;
            break;
        case 15: //flags
            SetFlagMask(*(UINT32 *)FieldValue);
            break;
        case 16: //services
            SetServicesFlagMask(*(UINT32 *)FieldValue);
            break;
        case 17: //trainSkill
            DATA.value.trainSkill = *(SINT8 *)FieldValue;
            break;
        case 18: //trainLevel
            DATA.value.trainLevel = *(UINT8 *)FieldValue;
            break;
        case 19: //unused1
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 20: //strength
            ATTR.value.strength = *(UINT8 *)FieldValue;
            break;
        case 21: //perception
            ATTR.value.perception = *(UINT8 *)FieldValue;
            break;
        case 22: //endurance
            ATTR.value.endurance = *(UINT8 *)FieldValue;
            break;
        case 23: //charisma
            ATTR.value.charisma = *(UINT8 *)FieldValue;
            break;
        case 24: //intelligence
            ATTR.value.intelligence = *(UINT8 *)FieldValue;
            break;
        case 25: //agility
            ATTR.value.agility = *(UINT8 *)FieldValue;
            break;
        case 26: //luck
            ATTR.value.luck = *(UINT8 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CLASRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    CLASDATA defaultDATA;
    CLASATTR defaultATTR;

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
        case 8: //description
            DESC.Unload();
            return;
        case 9: //iconPath
            ICON.Unload();
            return;
        case 10: //smallIconPath
            MICO.Unload();
            return;
        case 11: //tagSkills1
            DATA.value.tagSkills[0] = defaultDATA.tagSkills[0];
            return;
        case 12: //tagSkills2
            DATA.value.tagSkills[1] = defaultDATA.tagSkills[1];
            return;
        case 13: //tagSkills3
            DATA.value.tagSkills[2] = defaultDATA.tagSkills[2];
            return;
        case 14: //tagSkills4
            DATA.value.tagSkills[3] = defaultDATA.tagSkills[3];
            return;
        case 15: //flags
            SetFlagMask(defaultDATA.flags);
            return;
        case 16: //services
            SetServicesFlagMask(defaultDATA.services);
            return;
        case 17: //trainSkill
            DATA.value.trainSkill = defaultDATA.trainSkill;
            return;
        case 18: //trainLevel
            DATA.value.trainLevel = defaultDATA.trainLevel;
            return;
        case 19: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 20: //strength
            ATTR.value.strength = defaultATTR.strength;
            return;
        case 21: //perception
            ATTR.value.perception = defaultATTR.perception;
            return;
        case 22: //endurance
            ATTR.value.endurance = defaultATTR.endurance;
            return;
        case 23: //charisma
            ATTR.value.charisma = defaultATTR.charisma;
            return;
        case 24: //intelligence
            ATTR.value.intelligence = defaultATTR.intelligence;
            return;
        case 25: //agility
            ATTR.value.agility = defaultATTR.agility;
            return;
        case 26: //luck
            ATTR.value.luck = defaultATTR.luck;
            return;
        default:
            return;
        }
    }
}