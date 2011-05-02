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
#include "..\ASPCRecord.h"

namespace FNV
{
UINT32 ASPCRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 13: //dawnOrDefaultLoop
            return FORMID_FIELD;
        case 14: //afternoon
            return FORMID_FIELD;
        case 15: //dusk
            return FORMID_FIELD;
        case 16: //night
            return FORMID_FIELD;
        case 17: //walla
            return FORMID_FIELD;
        case 18: //wallaTriggerCount
            return UINT32_FIELD;
        case 19: //regionSound
            return FORMID_FIELD;
        case 20: //environmentType
            return UINT32_TYPE_FIELD;
        case 21: //spaceType
            return UINT32_TYPE_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * ASPCRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 13: //dawnOrDefaultLoop
            return &DawnSNAM.value;
        case 14: //afternoon
            return &AfternoonSNAM.value;
        case 15: //dusk
            return &DuskSNAM.value;
        case 16: //night
            return &NightSNAM.value;
        case 17: //walla
            return &WallaSNAM.value;
        case 18: //wallaTriggerCount
            return &WNAM.value;
        case 19: //regionSound
            return RDAT.IsLoaded() ? &RDAT.value : NULL;
        case 20: //environmentType
            return &ANAM.value;
        case 21: //spaceType
            return &INAM.value;
        default:
            return NULL;
        }
    }

bool ASPCRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 13: //dawnOrDefaultLoop
            DawnSNAM.value = *(FORMID *)FieldValue;
            return true;
        case 14: //afternoon
            AfternoonSNAM.value = *(FORMID *)FieldValue;
            return true;
        case 15: //dusk
            DuskSNAM.value = *(FORMID *)FieldValue;
            return true;
        case 16: //night
            NightSNAM.value = *(FORMID *)FieldValue;
            return true;
        case 17: //walla
            WallaSNAM.value = *(FORMID *)FieldValue;
            return true;
        case 18: //wallaTriggerCount
            WNAM.value = *(UINT32 *)FieldValue;
            break;
        case 19: //regionSound
            RDAT.value = *(FORMID *)FieldValue;
            return true;
        case 20: //environmentType
            SetEnvironmentType(*(UINT32 *)FieldValue);
            break;
        case 21: //spaceType
            SetSpaceType(*(UINT32 *)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void ASPCRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
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
        case 13: //dawnOrDefaultLoop
            DawnSNAM.Unload();
            return;
        case 14: //afternoon
            AfternoonSNAM.Unload();
            return;
        case 15: //dusk
            DuskSNAM.Unload();
            return;
        case 16: //night
            NightSNAM.Unload();
            return;
        case 17: //walla
            WallaSNAM.Unload();
            return;
        case 18: //wallaTriggerCount
            WNAM.Unload();
            return;
        case 19: //regionSound
            RDAT.Unload();
            return;
        case 20: //environmentType
            ANAM.Unload();
            return;
        case 21: //spaceType
            INAM.Unload();
            return;
        default:
            return;
        }
    }
}