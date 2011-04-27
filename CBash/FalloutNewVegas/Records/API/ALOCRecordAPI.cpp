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
#include "..\ALOCRecord.h"

namespace FNV
{
UINT32 ALOCRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //full
            return STRING_FIELD;
        case 8: //nam1_p Flags and Enums, messily combined
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM1.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 9: //nam2_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM2.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //nam3_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM3.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 11: //nam4 Location Delay
            return FLOAT32_FIELD;
        case 12: //nam5 Day Start
            return UINT32_FIELD;
        case 13: //nam6 Night Start
            return UINT32_FIELD;
        case 14: //nam7 Retrigger Delay
            return FLOAT32_FIELD;
        case 15: //hnam Media Set
            return FORMID_FIELD;
        case 16: //znam Media Set
            return FORMID_FIELD;
        case 17: //xnam Media Set
            return FORMID_FIELD;
        case 18: //ynam Media Set
            return FORMID_FIELD;
        case 19: //lnam Media Set
            return FORMID_FIELD;
        case 20: //gnam Media Set
            return FORMID_FIELD;
        case 21: //rnam Conditional Faction
            return FORMID_FIELD;
        case 22: //fnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

void * ALOCRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //nam1_p Flags and Enums, messily combined
            *FieldValues = NAM1.value;
            return NULL;
        case 9: //nam2_p Unknown
            *FieldValues = NAM2.value;
            return NULL;
        case 10: //nam3_p Unknown
            *FieldValues = NAM3.value;
            return NULL;
        case 11: //nam4 Location Delay
            return NAM4.IsLoaded() ? &NAM4->value11 : NULL;
        case 12: //nam5 Day Start
            return NAM5.IsLoaded() ? &NAM5->value12 : NULL;
        case 13: //nam6 Night Start
            return NAM6.IsLoaded() ? &NAM6->value13 : NULL;
        case 14: //nam7 Retrigger Delay
            return NAM7.IsLoaded() ? &NAM7->value14 : NULL;
        case 15: //hnam Media Set
            return HNAM.IsLoaded() ? &HNAM->value15 : NULL;
        case 16: //znam Media Set
            return ZNAM.IsLoaded() ? &ZNAM->value16 : NULL;
        case 17: //xnam Media Set
            return XNAM.IsLoaded() ? &XNAM->value17 : NULL;
        case 18: //ynam Media Set
            return YNAM.IsLoaded() ? &YNAM->value18 : NULL;
        case 19: //lnam Media Set
            return LNAM.IsLoaded() ? &LNAM->value19 : NULL;
        case 20: //gnam Media Set
            return GNAM.IsLoaded() ? &GNAM->value20 : NULL;
        case 21: //rnam Conditional Faction
            return RNAM.IsLoaded() ? &RNAM->value21 : NULL;
        case 22: //fnam_p Unknown
            *FieldValues = FNAM.value;
            return NULL;
        default:
            return NULL;
        }
    }

bool ALOCRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //nam1_p Flags and Enums, messily combined
            NAM1.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //nam2_p Unknown
            NAM2.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //nam3_p Unknown
            NAM3.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //nam4 Location Delay
            NAM4.Load();
            NAM4->value11 = *(FLOAT32 *)FieldValue;
            break;
        case 12: //nam5 Day Start
            NAM5.Load();
            NAM5->value12 = *(UINT32 *)FieldValue;
            break;
        case 13: //nam6 Night Start
            NAM6.Load();
            NAM6->value13 = *(UINT32 *)FieldValue;
            break;
        case 14: //nam7 Retrigger Delay
            NAM7.Load();
            NAM7->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //hnam Media Set
            HNAM.Load();
            HNAM->value15 = *(FORMID *)FieldValue;
            return true;
        case 16: //znam Media Set
            ZNAM.Load();
            ZNAM->value16 = *(FORMID *)FieldValue;
            return true;
        case 17: //xnam Media Set
            XNAM.Load();
            XNAM->value17 = *(FORMID *)FieldValue;
            return true;
        case 18: //ynam Media Set
            YNAM.Load();
            YNAM->value18 = *(FORMID *)FieldValue;
            return true;
        case 19: //lnam Media Set
            LNAM.Load();
            LNAM->value19 = *(FORMID *)FieldValue;
            return true;
        case 20: //gnam Media Set
            GNAM.Load();
            GNAM->value20 = *(FORMID *)FieldValue;
            return true;
        case 21: //rnam Conditional Faction
            RNAM.Load();
            RNAM->value21 = *(FORMID *)FieldValue;
            return true;
        case 22: //fnam_p Unknown
            FNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void ALOCRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 8: //nam1_p Flags and Enums, messily combined
            NAM1.Unload();
            return;
        case 9: //nam2_p Unknown
            NAM2.Unload();
            return;
        case 10: //nam3_p Unknown
            NAM3.Unload();
            return;
        case 11: //nam4 Location Delay
            NAM4.Unload();
            return;
        case 12: //nam5 Day Start
            NAM5.Unload();
            return;
        case 13: //nam6 Night Start
            NAM6.Unload();
            return;
        case 14: //nam7 Retrigger Delay
            NAM7.Unload();
            return;
        case 15: //hnam Media Set
            HNAM.Unload();
            return;
        case 16: //znam Media Set
            ZNAM.Unload();
            return;
        case 17: //xnam Media Set
            XNAM.Unload();
            return;
        case 18: //ynam Media Set
            YNAM.Unload();
            return;
        case 19: //lnam Media Set
            LNAM.Unload();
            return;
        case 20: //gnam Media Set
            GNAM.Unload();
            return;
        case 21: //rnam Conditional Faction
            RNAM.Unload();
            return;
        case 22: //fnam_p Unknown
            FNAM.Unload();
            return;
        default:
            return;
        }
    }
}