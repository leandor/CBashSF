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
#include "..\CELLRecord.h"

namespace FNV
{
UINT32 CELLRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //full Name
            return STRING_FIELD;
        case 8: //data Flags
            return UINT8_FIELD;
        case 9: //xclc XCLC ,, Struct
            return SINT32_FIELD;
        case 10: //xclc XCLC ,, Struct
            return SINT32_FIELD;
        case 11: //xclc XCLC ,, Struct
            return UINT32_FIELD;
        case 12: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 13: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 14: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 15: //xcll_p XCLL ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 16: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 17: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 18: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 19: //xcll_p XCLL ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 20: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 21: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 22: //xcll XCLL ,, Struct
            return UINT8_FIELD;
        case 23: //xcll_p XCLL ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 24: //xcll XCLL ,, Struct
            return FLOAT32_FIELD;
        case 25: //xcll XCLL ,, Struct
            return FLOAT32_FIELD;
        case 26: //xcll XCLL ,, Struct
            return SINT32_FIELD;
        case 27: //xcll XCLL ,, Struct
            return SINT32_FIELD;
        case 28: //xcll XCLL ,, Struct
            return FLOAT32_FIELD;
        case 29: //xcll XCLL ,, Struct
            return FLOAT32_FIELD;
        case 30: //xcll XCLL ,, Struct
            return FLOAT32_FIELD;
        case 31: //impf Footstep Materials
            return UNPARSED_FIELD;
        case 32: //ltmp Template
            return FORMID_FIELD;
        case 33: //lnam Inherit
            return UINT32_FIELD;
        case 34: //xclw Water Height
            return FLOAT32_FIELD;
        case 35: //xnam Water Noise Texture
            return ISTRING_FIELD;
        case 36: //xclr Regions
            return UNPARSED_FIELD;
        case 37: //xcim Image Space
            return FORMID_FIELD;
        case 38: //xcet_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 39: //xezn Encounter Zone
            return FORMID_FIELD;
        case 40: //xccm Climate
            return FORMID_FIELD;
        case 41: //xcwt Water
            return FORMID_FIELD;
        case 42: //xown Owner
            return FORMID_FIELD;
        case 43: //xrnk Faction rank
            return SINT32_FIELD;
        case 44: //xcas Acoustic Space
            return FORMID_FIELD;
        case 45: //xcmt_p Unused
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 46: //xcmo Music Type
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CELLRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //full Name
            return FULL.value;
        case 8: //data Flags
            return DATA.IsLoaded() ? &DATA->value8 : NULL;
        case 9: //xclc XCLC ,, Struct
            return XCLC.IsLoaded() ? &XCLC->value9 : NULL;
        case 10: //xclc XCLC ,, Struct
            return XCLC.IsLoaded() ? &XCLC->value10 : NULL;
        case 11: //xclc XCLC ,, Struct
            return XCLC.IsLoaded() ? &XCLC->value11 : NULL;
        case 12: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value12 : NULL;
        case 13: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value13 : NULL;
        case 14: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value14 : NULL;
        case 15: //xcll_p XCLL ,, Struct
            *FieldValues = XCLL.IsLoaded() ? &XCLL->value15[0] : NULL;
            return NULL;
        case 16: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value16 : NULL;
        case 17: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value17 : NULL;
        case 18: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value18 : NULL;
        case 19: //xcll_p XCLL ,, Struct
            *FieldValues = XCLL.IsLoaded() ? &XCLL->value19[0] : NULL;
            return NULL;
        case 20: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value20 : NULL;
        case 21: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value21 : NULL;
        case 22: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value22 : NULL;
        case 23: //xcll_p XCLL ,, Struct
            *FieldValues = XCLL.IsLoaded() ? &XCLL->value23[0] : NULL;
            return NULL;
        case 24: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value24 : NULL;
        case 25: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value25 : NULL;
        case 26: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value26 : NULL;
        case 27: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value27 : NULL;
        case 28: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value28 : NULL;
        case 29: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value29 : NULL;
        case 30: //xcll XCLL ,, Struct
            return XCLL.IsLoaded() ? &XCLL->value30 : NULL;
        case 31: //impf Footstep Materials
            return UNPARSEDGET_FIELD31;
        case 32: //ltmp Template
            return LTMP.IsLoaded() ? &LTMP->LTMP->value32 : NULL;
        case 33: //lnam Inherit
            return LTMP.IsLoaded() ? &LTMP->LNAM->value33 : NULL;
        case 34: //xclw Water Height
            return XCLW.IsLoaded() ? &XCLW->value34 : NULL;
        case 35: //xnam Water Noise Texture
            return XNAM.value;
        case 36: //xclr Regions
            return UNPARSEDGET_FIELD36;
        case 37: //xcim Image Space
            return XCIM.IsLoaded() ? &XCIM->value37 : NULL;
        case 38: //xcet_p Unknown
            *FieldValues = XCET.IsLoaded() ? &XCET->value38[0] : NULL;
            return NULL;
        case 39: //xezn Encounter Zone
            return XEZN.IsLoaded() ? &XEZN->value39 : NULL;
        case 40: //xccm Climate
            return XCCM.IsLoaded() ? &XCCM->value40 : NULL;
        case 41: //xcwt Water
            return XCWT.IsLoaded() ? &XCWT->value41 : NULL;
        case 42: //xown Owner
            return XOWN.IsLoaded() ? &XOWN->XOWN->value42 : NULL;
        case 43: //xrnk Faction rank
            return XOWN.IsLoaded() ? &XOWN->XRNK->value43 : NULL;
        case 44: //xcas Acoustic Space
            return XCAS.IsLoaded() ? &XCAS->value44 : NULL;
        case 45: //xcmt_p Unused
            *FieldValues = XCMT.IsLoaded() ? &XCMT->value45[0] : NULL;
            return NULL;
        case 46: //xcmo Music Type
            return XCMO.IsLoaded() ? &XCMO->value46 : NULL;
        default:
            return NULL;
        }
    }

bool CELLRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //full Name
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //data Flags
            DATA.Load();
            DATA->value8 = *(UINT8 *)FieldValue;
            break;
        case 9: //xclc XCLC ,, Struct
            XCLC.Load();
            XCLC->value9 = *(SINT32 *)FieldValue;
            break;
        case 10: //xclc XCLC ,, Struct
            XCLC.Load();
            XCLC->value10 = *(SINT32 *)FieldValue;
            break;
        case 11: //xclc XCLC ,, Struct
            XCLC.Load();
            XCLC->value11 = *(UINT32 *)FieldValue;
            break;
        case 12: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value12 = *(UINT8 *)FieldValue;
            break;
        case 13: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value13 = *(UINT8 *)FieldValue;
            break;
        case 14: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value14 = *(UINT8 *)FieldValue;
            break;
        case 15: //xcll_p XCLL ,, Struct
            if(ArraySize != 1)
                break;
            XCLL.Load();
            XCLL->value15[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 16: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value16 = *(UINT8 *)FieldValue;
            break;
        case 17: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value17 = *(UINT8 *)FieldValue;
            break;
        case 18: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value18 = *(UINT8 *)FieldValue;
            break;
        case 19: //xcll_p XCLL ,, Struct
            if(ArraySize != 1)
                break;
            XCLL.Load();
            XCLL->value19[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 20: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value20 = *(UINT8 *)FieldValue;
            break;
        case 21: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value21 = *(UINT8 *)FieldValue;
            break;
        case 22: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value22 = *(UINT8 *)FieldValue;
            break;
        case 23: //xcll_p XCLL ,, Struct
            if(ArraySize != 1)
                break;
            XCLL.Load();
            XCLL->value23[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 24: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value24 = *(FLOAT32 *)FieldValue;
            break;
        case 25: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value25 = *(FLOAT32 *)FieldValue;
            break;
        case 26: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value26 = *(SINT32 *)FieldValue;
            break;
        case 27: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value27 = *(SINT32 *)FieldValue;
            break;
        case 28: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value28 = *(FLOAT32 *)FieldValue;
            break;
        case 29: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value29 = *(FLOAT32 *)FieldValue;
            break;
        case 30: //xcll XCLL ,, Struct
            XCLL.Load();
            XCLL->value30 = *(FLOAT32 *)FieldValue;
            break;
        case 31: //impf Footstep Materials
            return UNPARSEDGET_FIELD31;
        case 32: //ltmp Template
            LTMP.Load();
            LTMP->LTMP.Load();
            LTMP->LTMP->value32 = *(FORMID *)FieldValue;
            return true;
        case 33: //lnam Inherit
            LTMP.Load();
            LTMP->LNAM.Load();
            LTMP->LNAM->value33 = *(UINT32 *)FieldValue;
            break;
        case 34: //xclw Water Height
            XCLW.Load();
            XCLW->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //xnam Water Noise Texture
            XNAM.Copy((STRING)FieldValue);
            break;
        case 36: //xclr Regions
            return UNPARSEDGET_FIELD36;
        case 37: //xcim Image Space
            XCIM.Load();
            XCIM->value37 = *(FORMID *)FieldValue;
            return true;
        case 38: //xcet_p Unknown
            if(ArraySize != 1)
                break;
            XCET.Load();
            XCET->value38[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 39: //xezn Encounter Zone
            XEZN.Load();
            XEZN->value39 = *(FORMID *)FieldValue;
            return true;
        case 40: //xccm Climate
            XCCM.Load();
            XCCM->value40 = *(FORMID *)FieldValue;
            return true;
        case 41: //xcwt Water
            XCWT.Load();
            XCWT->value41 = *(FORMID *)FieldValue;
            return true;
        case 42: //xown Owner
            XOWN.Load();
            XOWN->XOWN.Load();
            XOWN->XOWN->value42 = *(FORMID *)FieldValue;
            return true;
        case 43: //xrnk Faction rank
            XOWN.Load();
            XOWN->XRNK.Load();
            XOWN->XRNK->value43 = *(SINT32 *)FieldValue;
            break;
        case 44: //xcas Acoustic Space
            XCAS.Load();
            XCAS->value44 = *(FORMID *)FieldValue;
            return true;
        case 45: //xcmt_p Unused
            if(ArraySize != 1)
                break;
            XCMT.Load();
            XCMT->value45[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 46: //xcmo Music Type
            XCMO.Load();
            XCMO->value46 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void CELLRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //full Name
            FULL.Unload();
            return;
        case 8: //data Flags
            DATA.Unload();
            return;
        case 9: //xclc XCLC ,, Struct
            XCLC.Unload();
            return;
        case 10: //xclc XCLC ,, Struct
            XCLC.Unload();
            return;
        case 11: //xclc XCLC ,, Struct
            XCLC.Unload();
            return;
        case 12: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 13: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 14: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 15: //xcll_p XCLL ,, Struct
            XCLL.Unload();
            return;
        case 16: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 17: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 18: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 19: //xcll_p XCLL ,, Struct
            XCLL.Unload();
            return;
        case 20: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 21: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 22: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 23: //xcll_p XCLL ,, Struct
            XCLL.Unload();
            return;
        case 24: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 25: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 26: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 27: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 28: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 29: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 30: //xcll XCLL ,, Struct
            XCLL.Unload();
            return;
        case 31: //impf Footstep Materials
            return UNPARSEDDEL_FIELD31;
        case 32: //ltmp Template
            if(LTMP.IsLoaded())
                LTMP->LTMP.Unload();
            return;
        case 33: //lnam Inherit
            if(LTMP.IsLoaded())
                LTMP->LNAM.Unload();
            return;
        case 34: //xclw Water Height
            XCLW.Unload();
            return;
        case 35: //xnam Water Noise Texture
            XNAM.Unload();
            return;
        case 36: //xclr Regions
            return UNPARSEDDEL_FIELD36;
        case 37: //xcim Image Space
            XCIM.Unload();
            return;
        case 38: //xcet_p Unknown
            XCET.Unload();
            return;
        case 39: //xezn Encounter Zone
            XEZN.Unload();
            return;
        case 40: //xccm Climate
            XCCM.Unload();
            return;
        case 41: //xcwt Water
            XCWT.Unload();
            return;
        case 42: //xown Owner
            if(XOWN.IsLoaded())
                XOWN->XOWN.Unload();
            return;
        case 43: //xrnk Faction rank
            if(XOWN.IsLoaded())
                XOWN->XRNK.Unload();
            return;
        case 44: //xcas Acoustic Space
            XCAS.Unload();
            return;
        case 45: //xcmt_p Unused
            XCMT.Unload();
            return;
        case 46: //xcmo Music Type
            XCMO.Unload();
            return;
        default:
            return;
        }
    }
}