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
#include "..\LSCRRecord.h"

namespace FNV
{
UINT32 LSCRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //iconPath
            return ISTRING_FIELD;
        case 8: //smallIconPath
            return ISTRING_FIELD;
        case 9: //text
            return STRING_FIELD;
        case 10: //locations
            if(ListFieldID == 0) //locations
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)LNAM.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= LNAM.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //direct
                    return FORMID_FIELD;
                case 2: //indirect
                    return FORMID_FIELD;
                case 3: //gridY
                    return SINT16_FIELD;
                case 4: //gridX
                    return SINT16_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 11: //screentype
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * LSCRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //iconPath
            return ICON.value;
        case 8: //smallIconPath
            return MICO.value;
        case 9: //text
            return DESC.value;
        case 10: //locations
            if(ListIndex >= LNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //direct
                    return &LNAM.value[ListIndex]->direct;
                case 2: //indirect
                    return &LNAM.value[ListIndex]->indirect;
                case 3: //gridY
                    return &LNAM.value[ListIndex]->gridY;
                case 4: //gridX
                    return &LNAM.value[ListIndex]->gridX;
                default:
                    return NULL;
                }
            return NULL;
        case 11: //screentype
            return &WMI1.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool LSCRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 8: //smallIconPath
            MICO.Copy((STRING)FieldValue);
            break;
        case 9: //text
            DESC.Copy((STRING)FieldValue);
            break;
        case 10: //locations
            if(ListFieldID == 0) //locationsSize
                {
                LNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= LNAM.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //direct
                    LNAM.value[ListIndex]->direct = *(FORMID *)FieldValue;
                    return true;
                case 2: //indirect
                    LNAM.value[ListIndex]->indirect = *(FORMID *)FieldValue;
                    return true;
                case 3: //gridY
                    LNAM.value[ListIndex]->gridY = *(SINT16 *)FieldValue;
                    break;
                case 4: //gridX
                    LNAM.value[ListIndex]->gridX = *(SINT16 *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 11: //screentype
            WMI1.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void LSCRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    LSCRLNAM defaultLNAM;
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
        case 7: //iconPath
            ICON.Unload();
            return;
        case 8: //smallIconPath
            MICO.Unload();
            return;
        case 9: //text
            DESC.Unload();
            return;
        case 10: //locations
            if(ListFieldID == 0) //locationsSize
                {
                LNAM.Unload();
                return;
                }

            if(ListIndex >= LNAM.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //direct
                    LNAM.value[ListIndex]->direct = defaultLNAM.direct;
                    return;
                case 2: //indirect
                    LNAM.value[ListIndex]->indirect = defaultLNAM.indirect;
                    return;
                case 3: //gridY
                    LNAM.value[ListIndex]->gridY = defaultLNAM.gridY;
                    return;
                case 4: //gridX
                    LNAM.value[ListIndex]->gridX = defaultLNAM.gridX;
                    return;
                default:
                    return;
                }
            return;
        case 11: //screentype
            WMI1.Unload();
            return;
        default:
            return;
        }
    }
}