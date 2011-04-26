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
#include "..\REGNRecord.h"

namespace FNV
{
UINT32 REGNRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //iconPath
            return ISTRING_FIELD;
        case 8: //smallIconPath
            return ISTRING_FIELD;
        case 9: //rclr RCLR ,, Struct
            return UINT8_FIELD;
        case 10: //rclr RCLR ,, Struct
            return UINT8_FIELD;
        case 11: //rclr RCLR ,, Struct
            return UINT8_FIELD;
        case 12: //rclr_p RCLR ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //wnam Worldspace
            return FORMID_FIELD;
        case 14: //rpli Edge Fall-off
            return UINT32_FIELD;
        case 15: //rpld RPLD ,, Struct
            return FLOAT32_FIELD;
        case 16: //rpld RPLD ,, Struct
            return FLOAT32_FIELD;
        case 17: //rdat RDAT ,, Struct
            return UINT32_FIELD;
        case 18: //rdat RDAT ,, Struct
            return UINT8_FIELD;
        case 19: //rdat RDAT ,, Struct
            return UINT8_FIELD;
        case 20: //rdat_p RDAT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 0;
                default:
                    return UNKNOWN_FIELD;
                }
        case 21: //rdot RDOT ,, Struct
            return FORMID_FIELD;
        case 22: //rdot RDOT ,, Struct
            return UINT16_FIELD;
        case 23: //rdot_p RDOT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 24: //rdot RDOT ,, Struct
            return FLOAT32_FIELD;
        case 25: //rdot RDOT ,, Struct
            return UINT8_FIELD;
        case 26: //rdot RDOT ,, Struct
            return UINT8_FIELD;
        case 27: //rdot RDOT ,, Struct
            return UINT8_FIELD;
        case 28: //rdot RDOT ,, Struct
            return UINT8_FIELD;
        case 29: //rdot RDOT ,, Struct
            return UINT16_FIELD;
        case 30: //rdot RDOT ,, Struct
            return UINT16_FIELD;
        case 31: //rdot_p RDOT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 32: //rdot RDOT ,, Struct
            return FLOAT32_FIELD;
        case 33: //rdot RDOT ,, Struct
            return FLOAT32_FIELD;
        case 34: //rdot RDOT ,, Struct
            return FLOAT32_FIELD;
        case 35: //rdot RDOT ,, Struct
            return FLOAT32_FIELD;
        case 36: //rdot RDOT ,, Struct
            return UINT16_FIELD;
        case 37: //rdot RDOT ,, Struct
            return UINT16_FIELD;
        case 38: //rdot RDOT ,, Struct
            return UINT16_FIELD;
        case 39: //rdot_p RDOT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 40: //rdot_p RDOT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 41: //rdmp Map Name
            return ISTRING_FIELD;
        case 42: //rdgs RDGS ,, Struct
            return FORMID_FIELD;
        case 43: //rdgs_p RDGS ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 44: //rdmd Music Type
            return UINT32_FIELD;
        case 45: //rdmo Music
            return FORMID_FIELD;
        case 46: //rdsi Incidental MediaSet
            return FORMID_FIELD;
        case 47: //rdsb Battle MediaSet
            return FORMID_FIELD;
        case 48: //rdsd RDSD ,, Struct
            return FORMID_FIELD;
        case 49: //rdsd RDSD ,, Struct
            return UINT32_FIELD;
        case 50: //rdsd RDSD ,, Struct
            return UINT32_FIELD;
        case 51: //rdwt RDWT ,, Struct
            return FORMID_FIELD;
        case 52: //rdwt RDWT ,, Struct
            return UINT32_FIELD;
        case 53: //rdwt RDWT ,, Struct
            return FORMID_FIELD;
        case 54: //rdid Imposters
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * REGNRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 9: //rclr RCLR ,, Struct
            return RCLR.IsLoaded() ? &RCLR->value9 : NULL;
        case 10: //rclr RCLR ,, Struct
            return RCLR.IsLoaded() ? &RCLR->value10 : NULL;
        case 11: //rclr RCLR ,, Struct
            return RCLR.IsLoaded() ? &RCLR->value11 : NULL;
        case 12: //rclr_p RCLR ,, Struct
            *FieldValues = RCLR.IsLoaded() ? &RCLR->value12[0] : NULL;
            return NULL;
        case 13: //wnam Worldspace
            return WNAM.IsLoaded() ? &WNAM->value13 : NULL;
        case 14: //rpli Edge Fall-off
            return RPLI.IsLoaded() ? &RPLI->value14 : NULL;
        case 15: //rpld RPLD ,, Struct
            return RPLD.IsLoaded() ? &RPLD->value15 : NULL;
        case 16: //rpld RPLD ,, Struct
            return RPLD.IsLoaded() ? &RPLD->value16 : NULL;
        case 17: //rdat RDAT ,, Struct
            return RDAT.IsLoaded() ? &RDAT->value17 : NULL;
        case 18: //rdat RDAT ,, Struct
            return RDAT.IsLoaded() ? &RDAT->value18 : NULL;
        case 19: //rdat RDAT ,, Struct
            return RDAT.IsLoaded() ? &RDAT->value19 : NULL;
        case 20: //rdat_p RDAT ,, Struct
            *FieldValues = RDAT.IsLoaded() ? &RDAT->value20[0] : NULL;
            return NULL;
        case 21: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value21 : NULL;
        case 22: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value22 : NULL;
        case 23: //rdot_p RDOT ,, Struct
            *FieldValues = RDOT.IsLoaded() ? &RDOT->value23[0] : NULL;
            return NULL;
        case 24: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value24 : NULL;
        case 25: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value25 : NULL;
        case 26: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value26 : NULL;
        case 27: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value27 : NULL;
        case 28: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value28 : NULL;
        case 29: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value29 : NULL;
        case 30: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value30 : NULL;
        case 31: //rdot_p RDOT ,, Struct
            *FieldValues = RDOT.IsLoaded() ? &RDOT->value31[0] : NULL;
            return NULL;
        case 32: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value32 : NULL;
        case 33: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value33 : NULL;
        case 34: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value34 : NULL;
        case 35: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value35 : NULL;
        case 36: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value36 : NULL;
        case 37: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value37 : NULL;
        case 38: //rdot RDOT ,, Struct
            return RDOT.IsLoaded() ? &RDOT->value38 : NULL;
        case 39: //rdot_p RDOT ,, Struct
            *FieldValues = RDOT.IsLoaded() ? &RDOT->value39[0] : NULL;
            return NULL;
        case 40: //rdot_p RDOT ,, Struct
            *FieldValues = RDOT.IsLoaded() ? &RDOT->value40[0] : NULL;
            return NULL;
        case 41: //rdmp Map Name
            return RDMP.value;
        case 42: //rdgs RDGS ,, Struct
            return RDGS.IsLoaded() ? &RDGS->value42 : NULL;
        case 43: //rdgs_p RDGS ,, Struct
            *FieldValues = RDGS.IsLoaded() ? &RDGS->value43[0] : NULL;
            return NULL;
        case 44: //rdmd Music Type
            return RDMD.IsLoaded() ? &RDMD->value44 : NULL;
        case 45: //rdmo Music
            return RDMO.IsLoaded() ? &RDMO->value45 : NULL;
        case 46: //rdsi Incidental MediaSet
            return RDSI.IsLoaded() ? &RDSI->value46 : NULL;
        case 47: //rdsb Battle MediaSet
            return RDSB.IsLoaded() ? &RDSB->value47 : NULL;
        case 48: //rdsd RDSD ,, Struct
            return RDSD.IsLoaded() ? &RDSD->value48 : NULL;
        case 49: //rdsd RDSD ,, Struct
            return RDSD.IsLoaded() ? &RDSD->value49 : NULL;
        case 50: //rdsd RDSD ,, Struct
            return RDSD.IsLoaded() ? &RDSD->value50 : NULL;
        case 51: //rdwt RDWT ,, Struct
            return RDWT.IsLoaded() ? &RDWT->value51 : NULL;
        case 52: //rdwt RDWT ,, Struct
            return RDWT.IsLoaded() ? &RDWT->value52 : NULL;
        case 53: //rdwt RDWT ,, Struct
            return RDWT.IsLoaded() ? &RDWT->value53 : NULL;
        case 54: //rdid Imposters
            return UNPARSEDGET_FIELD54;
        default:
            return NULL;
        }
    }

bool REGNRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 8: //smallIconPath
            MICO.Copy((STRING)FieldValue);
            break;
        case 9: //rclr RCLR ,, Struct
            RCLR.Load();
            RCLR->value9 = *(UINT8 *)FieldValue;
            break;
        case 10: //rclr RCLR ,, Struct
            RCLR.Load();
            RCLR->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //rclr RCLR ,, Struct
            RCLR.Load();
            RCLR->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //rclr_p RCLR ,, Struct
            if(ArraySize != 1)
                break;
            RCLR.Load();
            RCLR->value12[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 13: //wnam Worldspace
            WNAM.Load();
            WNAM->value13 = *(FORMID *)FieldValue;
            return true;
        case 14: //rpli Edge Fall-off
            RPLI.Load();
            RPLI->value14 = *(UINT32 *)FieldValue;
            break;
        case 15: //rpld RPLD ,, Struct
            RPLD.Load();
            RPLD->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //rpld RPLD ,, Struct
            RPLD.Load();
            RPLD->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //rdat RDAT ,, Struct
            RDAT.Load();
            RDAT->value17 = *(UINT32 *)FieldValue;
            break;
        case 18: //rdat RDAT ,, Struct
            RDAT.Load();
            RDAT->value18 = *(UINT8 *)FieldValue;
            break;
        case 19: //rdat RDAT ,, Struct
            RDAT.Load();
            RDAT->value19 = *(UINT8 *)FieldValue;
            break;
        case 20: //rdat_p RDAT ,, Struct
            if(ArraySize != 0)
                break;
            RDAT.Load();
            break;
        case 21: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value21 = *(FORMID *)FieldValue;
            return true;
        case 22: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value22 = *(UINT16 *)FieldValue;
            break;
        case 23: //rdot_p RDOT ,, Struct
            if(ArraySize != 2)
                break;
            RDOT.Load();
            RDOT->value23[0] = ((UINT8 *)FieldValue)[0];
            RDOT->value23[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 24: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value24 = *(FLOAT32 *)FieldValue;
            break;
        case 25: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value25 = *(UINT8 *)FieldValue;
            break;
        case 26: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value26 = *(UINT8 *)FieldValue;
            break;
        case 27: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value27 = *(UINT8 *)FieldValue;
            break;
        case 28: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value29 = *(UINT16 *)FieldValue;
            break;
        case 30: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value30 = *(UINT16 *)FieldValue;
            break;
        case 31: //rdot_p RDOT ,, Struct
            if(ArraySize != 4)
                break;
            RDOT.Load();
            RDOT->value31[0] = ((UINT8 *)FieldValue)[0];
            RDOT->value31[1] = ((UINT8 *)FieldValue)[1];
            RDOT->value31[2] = ((UINT8 *)FieldValue)[2];
            RDOT->value31[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 32: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value32 = *(FLOAT32 *)FieldValue;
            break;
        case 33: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value33 = *(FLOAT32 *)FieldValue;
            break;
        case 34: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value35 = *(FLOAT32 *)FieldValue;
            break;
        case 36: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value36 = *(UINT16 *)FieldValue;
            break;
        case 37: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value37 = *(UINT16 *)FieldValue;
            break;
        case 38: //rdot RDOT ,, Struct
            RDOT.Load();
            RDOT->value38 = *(UINT16 *)FieldValue;
            break;
        case 39: //rdot_p RDOT ,, Struct
            if(ArraySize != 2)
                break;
            RDOT.Load();
            RDOT->value39[0] = ((UINT8 *)FieldValue)[0];
            RDOT->value39[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 40: //rdot_p RDOT ,, Struct
            if(ArraySize != 4)
                break;
            RDOT.Load();
            RDOT->value40[0] = ((UINT8 *)FieldValue)[0];
            RDOT->value40[1] = ((UINT8 *)FieldValue)[1];
            RDOT->value40[2] = ((UINT8 *)FieldValue)[2];
            RDOT->value40[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 41: //rdmp Map Name
            RDMP.Copy((STRING)FieldValue);
            break;
        case 42: //rdgs RDGS ,, Struct
            RDGS.Load();
            RDGS->value42 = *(FORMID *)FieldValue;
            return true;
        case 43: //rdgs_p RDGS ,, Struct
            if(ArraySize != 4)
                break;
            RDGS.Load();
            RDGS->value43[0] = ((UINT8 *)FieldValue)[0];
            RDGS->value43[1] = ((UINT8 *)FieldValue)[1];
            RDGS->value43[2] = ((UINT8 *)FieldValue)[2];
            RDGS->value43[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 44: //rdmd Music Type
            RDMD.Load();
            RDMD->value44 = *(UINT32 *)FieldValue;
            break;
        case 45: //rdmo Music
            RDMO.Load();
            RDMO->value45 = *(FORMID *)FieldValue;
            return true;
        case 46: //rdsi Incidental MediaSet
            RDSI.Load();
            RDSI->value46 = *(FORMID *)FieldValue;
            return true;
        case 47: //rdsb Battle MediaSet
            RDSB.Load();
            RDSB->value47 = *(FORMID *)FieldValue;
            return true;
        case 48: //rdsd RDSD ,, Struct
            RDSD.Load();
            RDSD->value48 = *(FORMID *)FieldValue;
            return true;
        case 49: //rdsd RDSD ,, Struct
            RDSD.Load();
            RDSD->value49 = *(UINT32 *)FieldValue;
            break;
        case 50: //rdsd RDSD ,, Struct
            RDSD.Load();
            RDSD->value50 = *(UINT32 *)FieldValue;
            break;
        case 51: //rdwt RDWT ,, Struct
            RDWT.Load();
            RDWT->value51 = *(FORMID *)FieldValue;
            return true;
        case 52: //rdwt RDWT ,, Struct
            RDWT.Load();
            RDWT->value52 = *(UINT32 *)FieldValue;
            break;
        case 53: //rdwt RDWT ,, Struct
            RDWT.Load();
            RDWT->value53 = *(FORMID *)FieldValue;
            return true;
        case 54: //rdid Imposters
            return UNPARSEDGET_FIELD54;
        default:
            break;
        }
    return false;
    }

void REGNRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //iconPath
            ICON.Unload();
            return;
        case 8: //smallIconPath
            MICO.Unload();
            return;
        case 9: //rclr RCLR ,, Struct
            RCLR.Unload();
            return;
        case 10: //rclr RCLR ,, Struct
            RCLR.Unload();
            return;
        case 11: //rclr RCLR ,, Struct
            RCLR.Unload();
            return;
        case 12: //rclr_p RCLR ,, Struct
            RCLR.Unload();
            return;
        case 13: //wnam Worldspace
            WNAM.Unload();
            return;
        case 14: //rpli Edge Fall-off
            RPLI.Unload();
            return;
        case 15: //rpld RPLD ,, Struct
            RPLD.Unload();
            return;
        case 16: //rpld RPLD ,, Struct
            RPLD.Unload();
            return;
        case 17: //rdat RDAT ,, Struct
            RDAT.Unload();
            return;
        case 18: //rdat RDAT ,, Struct
            RDAT.Unload();
            return;
        case 19: //rdat RDAT ,, Struct
            RDAT.Unload();
            return;
        case 20: //rdat_p RDAT ,, Struct
            RDAT.Unload();
            return;
        case 21: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 22: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 23: //rdot_p RDOT ,, Struct
            RDOT.Unload();
            return;
        case 24: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 25: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 26: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 27: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 28: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 29: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 30: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 31: //rdot_p RDOT ,, Struct
            RDOT.Unload();
            return;
        case 32: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 33: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 34: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 35: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 36: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 37: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 38: //rdot RDOT ,, Struct
            RDOT.Unload();
            return;
        case 39: //rdot_p RDOT ,, Struct
            RDOT.Unload();
            return;
        case 40: //rdot_p RDOT ,, Struct
            RDOT.Unload();
            return;
        case 41: //rdmp Map Name
            RDMP.Unload();
            return;
        case 42: //rdgs RDGS ,, Struct
            RDGS.Unload();
            return;
        case 43: //rdgs_p RDGS ,, Struct
            RDGS.Unload();
            return;
        case 44: //rdmd Music Type
            RDMD.Unload();
            return;
        case 45: //rdmo Music
            RDMO.Unload();
            return;
        case 46: //rdsi Incidental MediaSet
            RDSI.Unload();
            return;
        case 47: //rdsb Battle MediaSet
            RDSB.Unload();
            return;
        case 48: //rdsd RDSD ,, Struct
            RDSD.Unload();
            return;
        case 49: //rdsd RDSD ,, Struct
            RDSD.Unload();
            return;
        case 50: //rdsd RDSD ,, Struct
            RDSD.Unload();
            return;
        case 51: //rdwt RDWT ,, Struct
            RDWT.Unload();
            return;
        case 52: //rdwt RDWT ,, Struct
            RDWT.Unload();
            return;
        case 53: //rdwt RDWT ,, Struct
            RDWT.Unload();
            return;
        case 54: //rdid Imposters
            return UNPARSEDDEL_FIELD54;
        default:
            return;
        }
    }
}