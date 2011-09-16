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
        case 13: //soundPath
            return ISTRING_FIELD;
        case 14: //chance
            return UINT8_FIELD;
        case 15: //minDistance
            return UINT8_FIELD;
        case 16: //maxDistance
            return UINT8_FIELD;
        case 17: //freqAdjustment
            return SINT8_FIELD;
        case 18: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 19: //flags
            return UINT32_FLAG_FIELD;
        case 20: //staticAtten
            return SINT16_FIELD;
        case 21: //stopTime
            return UINT8_FIELD;
        case 22: //startTime
            return UINT8_FIELD;
        case 23: //attenCurve
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return SINT16_ARRAY_FIELD;
                case 1: //fieldSize
                    return 5;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 24: //reverb
            return SINT16_FIELD;
        case 25: //priority
            return SINT32_FIELD;
        case 26: //x
            return SINT32_FIELD;
        case 27: //y
            return SINT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
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
        case 13: //soundPath
            return FNAM.value;
        case 14: //chance
            return RNAM.IsLoaded() ? RNAM.value : NULL;
        case 15: //minDistance
            return &SNDD.value.minDistance;
        case 16: //maxDistance
            return &SNDD.value.maxDistance;
        case 17: //freqAdjustment
            return &SNDD.value.freqAdjustment;
        case 18: //unused1
            *FieldValues = &SNDD.value.unused1;
            return NULL;
        case 19: //flags
            return &SNDD.value.flags;
        case 20: //staticAtten
            return &SNDD.value.staticAtten;
        case 21: //stopTime
            return &SNDD.value.stopTime;
        case 22: //startTime
            return &SNDD.value.startTime;
        case 23: //attenCurve
            *FieldValues = &SNDD.value.attenCurve[0];
            return NULL;
        case 24: //reverb
            return &SNDD.value.reverb;
        case 25: //priority
            return &SNDD.value.priority;
        case 26: //x
            return &SNDD.value.x;
        case 27: //y
            return &SNDD.value.y;
        default:
            return NULL;
        }
    return NULL;
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
        case 13: //soundPath
            FNAM.Copy((STRING)FieldValue);
            break;
        case 14: //chance
            RNAM.Load();
            *RNAM.value = *(UINT8 *)FieldValue;
            break;
        case 15: //minDistance
            SNDD.value.minDistance = *(UINT8 *)FieldValue;
            break;
        case 16: //maxDistance
            SNDD.value.maxDistance = *(UINT8 *)FieldValue;
            break;
        case 17: //freqAdjustment
            SNDD.value.freqAdjustment = *(SINT8 *)FieldValue;
            break;
        case 18: //unused1
            if(ArraySize != 1)
                break;
            SNDD.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 19: //flags
            SetFlagMask(*(UINT32 *)FieldValue);
            break;
        case 20: //staticAtten
            SNDD.value.staticAtten = *(SINT16 *)FieldValue;
            break;
        case 21: //stopTime
            SNDD.value.stopTime = *(UINT8 *)FieldValue;
            break;
        case 22: //startTime
            SNDD.value.startTime = *(UINT8 *)FieldValue;
            break;
        case 23: //attenCurve
            if(ArraySize != 5)
                break;
            SNDD.value.attenCurve[0] = ((SINT16ARRAY)FieldValue)[0];
            SNDD.value.attenCurve[1] = ((SINT16ARRAY)FieldValue)[1];
            SNDD.value.attenCurve[2] = ((SINT16ARRAY)FieldValue)[2];
            SNDD.value.attenCurve[3] = ((SINT16ARRAY)FieldValue)[3];
            SNDD.value.attenCurve[4] = ((SINT16ARRAY)FieldValue)[4];
            break;
        case 24: //reverb
            SNDD.value.reverb = *(SINT16 *)FieldValue;
            break;
        case 25: //priority
            SNDD.value.priority = *(SINT32 *)FieldValue;
            break;
        case 26: //x
            SNDD.value.x = *(SINT32 *)FieldValue;
            break;
        case 27: //y
            SNDD.value.y = *(SINT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void SOUNRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    SOUNSNDD defaultSNDD;

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
        case 13: //soundPath
            FNAM.Unload();
            return;
        case 14: //chance
            RNAM.Unload();
            return;
        case 15: //minDistance
            SNDD.value.minDistance = defaultSNDD.minDistance;
            return;
        case 16: //maxDistance
            SNDD.value.maxDistance = defaultSNDD.maxDistance;
            return;
        case 17: //freqAdjustment
            SNDD.value.freqAdjustment = defaultSNDD.freqAdjustment;
            return;
        case 18: //unused1
            SNDD.value.unused1 = defaultSNDD.unused1;
            return;
        case 19: //flags
            SetFlagMask(defaultSNDD.flags);
            return;
        case 20: //staticAtten
            SNDD.value.staticAtten = defaultSNDD.staticAtten;
            return;
        case 21: //stopTime
            SNDD.value.stopTime = defaultSNDD.stopTime;
            return;
        case 22: //startTime
            SNDD.value.startTime = defaultSNDD.startTime;
            return;
        case 23: //attenCurve
            SNDD.value.attenCurve[0] = defaultSNDD.attenCurve[0];
            SNDD.value.attenCurve[1] = defaultSNDD.attenCurve[1];
            SNDD.value.attenCurve[2] = defaultSNDD.attenCurve[2];
            SNDD.value.attenCurve[3] = defaultSNDD.attenCurve[3];
            SNDD.value.attenCurve[4] = defaultSNDD.attenCurve[4];
            return;
        case 24: //reverb
            SNDD.value.reverb = defaultSNDD.reverb;
            return;
        case 25: //priority
            SNDD.value.priority = defaultSNDD.priority;
            return;
        case 26: //x
            SNDD.value.x = defaultSNDD.x;
            return;
        case 27: //y
            SNDD.value.y = defaultSNDD.y;
            return;
        default:
            return;
        }
    }
}