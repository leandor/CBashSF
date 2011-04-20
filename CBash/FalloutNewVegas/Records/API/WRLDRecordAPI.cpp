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
#include "..\WRLDRecord.h"

namespace FNV
{
UINT32 WRLDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 4: //formVersion
            return UINT16_FIELD;
        case 5: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 6: //edid Editor ID
            return ISTRING_FIELD;
        case 7: //full Name
            return STRING_FIELD;
        case 8: //xezn Encounter Zone
            return FORMID_FIELD;
        case 9: //wnam Worldspace
            return FORMID_FIELD;
        case 10: //pnam PNAM ,, Struct
            return UINT8_FIELD;
        case 11: //pnam_p PNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 12: //cnam Climate
            return FORMID_FIELD;
        case 13: //nam2 Water
            return FORMID_FIELD;
        case 14: //nam3 LOD Water Type
            return FORMID_FIELD;
        case 15: //nam4 LOD Water Height
            return FLOAT32_FIELD;
        case 16: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 17: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 18: //icon Large Icon Filename
            return ISTRING_FIELD;
        case 19: //mico Small Icon Filename
            return ISTRING_FIELD;
        case 20: //mnam MNAM ,, Struct
            return SINT32_FIELD;
        case 21: //mnam MNAM ,, Struct
            return SINT32_FIELD;
        case 22: //mnam MNAM ,, Struct
            return SINT16_FIELD;
        case 23: //mnam MNAM ,, Struct
            return SINT16_FIELD;
        case 24: //mnam MNAM ,, Struct
            return SINT16_FIELD;
        case 25: //mnam MNAM ,, Struct
            return SINT16_FIELD;
        case 26: //onam ONAM ,, Struct
            return FLOAT32_FIELD;
        case 27: //onam ONAM ,, Struct
            return FLOAT32_FIELD;
        case 28: //onam ONAM ,, Struct
            return FLOAT32_FIELD;
        case 29: //inam Image Space
            return FORMID_FIELD;
        case 30: //data Flags
            return UINT8_FIELD;
        case 31: //nam0 NAM0 ,, Struct
            return FLOAT32_FIELD;
        case 32: //nam0 NAM0 ,, Struct
            return FLOAT32_FIELD;
        case 33: //nam9 NAM9 ,, Struct
            return FLOAT32_FIELD;
        case 34: //nam9 NAM9 ,, Struct
            return FLOAT32_FIELD;
        case 35: //znam Music
            return FORMID_FIELD;
        case 36: //nnam Canopy Shadow
            return ISTRING_FIELD;
        case 37: //xnam Water Noise Texture
            return ISTRING_FIELD;
        case 38: //imps IMPS ,, Struct
            return UINT32_FIELD;
        case 39: //imps IMPS ,, Struct
            return FORMID_FIELD;
        case 40: //imps IMPS ,, Struct
            return FORMID_FIELD;
        case 41: //impf Footstep Materials
            return UNPARSED_FIELD;
        case 42: //ofst_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return OFST.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

void * WRLDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 4: //formVersion
            return &formVersion;
        case 5: //versionControl2
            *FieldValues = &versionControl2;
            return NULL;
        case 6: //edid Editor ID
            return EDID.value;
        case 7: //full Name
            return FULL.value;
        case 8: //xezn Encounter Zone
            return XEZN.IsLoaded() ? &XEZN->value8 : NULL;
        case 9: //wnam Worldspace
            return WNAM.IsLoaded() ? &WNAM->value9 : NULL;
        case 10: //pnam PNAM ,, Struct
            return PNAM.IsLoaded() ? &PNAM->value10 : NULL;
        case 11: //pnam_p PNAM ,, Struct
            *FieldValues = PNAM.IsLoaded() ? &PNAM->value11[0] : NULL;
            return NULL;
        case 12: //cnam Climate
            return CNAM.IsLoaded() ? &CNAM->value12 : NULL;
        case 13: //nam2 Water
            return NAM2.IsLoaded() ? &NAM2->value13 : NULL;
        case 14: //nam3 LOD Water Type
            return NAM3.IsLoaded() ? &NAM3->value14 : NULL;
        case 15: //nam4 LOD Water Height
            return NAM4.IsLoaded() ? &NAM4->value15 : NULL;
        case 16: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value16 : NULL;
        case 17: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value17 : NULL;
        case 18: //icon Large Icon Filename
            return ICON.IsLoaded() ? ICON->ICON.value : NULL;
        case 19: //mico Small Icon Filename
            return ICON.IsLoaded() ? ICON->MICO.value : NULL;
        case 20: //mnam MNAM ,, Struct
            return MNAM.IsLoaded() ? &MNAM->value20 : NULL;
        case 21: //mnam MNAM ,, Struct
            return MNAM.IsLoaded() ? &MNAM->value21 : NULL;
        case 22: //mnam MNAM ,, Struct
            return MNAM.IsLoaded() ? &MNAM->value22 : NULL;
        case 23: //mnam MNAM ,, Struct
            return MNAM.IsLoaded() ? &MNAM->value23 : NULL;
        case 24: //mnam MNAM ,, Struct
            return MNAM.IsLoaded() ? &MNAM->value24 : NULL;
        case 25: //mnam MNAM ,, Struct
            return MNAM.IsLoaded() ? &MNAM->value25 : NULL;
        case 26: //onam ONAM ,, Struct
            return ONAM.IsLoaded() ? &ONAM->value26 : NULL;
        case 27: //onam ONAM ,, Struct
            return ONAM.IsLoaded() ? &ONAM->value27 : NULL;
        case 28: //onam ONAM ,, Struct
            return ONAM.IsLoaded() ? &ONAM->value28 : NULL;
        case 29: //inam Image Space
            return INAM.IsLoaded() ? &INAM->value29 : NULL;
        case 30: //data Flags
            return DATA.IsLoaded() ? &DATA->value30 : NULL;
        case 31: //nam0 NAM0 ,, Struct
            return NAM0.IsLoaded() ? &NAM0->value31 : NULL;
        case 32: //nam0 NAM0 ,, Struct
            return NAM0.IsLoaded() ? &NAM0->value32 : NULL;
        case 33: //nam9 NAM9 ,, Struct
            return NAM9.IsLoaded() ? &NAM9->value33 : NULL;
        case 34: //nam9 NAM9 ,, Struct
            return NAM9.IsLoaded() ? &NAM9->value34 : NULL;
        case 35: //znam Music
            return ZNAM.IsLoaded() ? &ZNAM->value35 : NULL;
        case 36: //nnam Canopy Shadow
            return NNAM.value;
        case 37: //xnam Water Noise Texture
            return XNAM.value;
        case 38: //imps IMPS ,, Struct
            return IMPS.IsLoaded() ? &IMPS->value38 : NULL;
        case 39: //imps IMPS ,, Struct
            return IMPS.IsLoaded() ? &IMPS->value39 : NULL;
        case 40: //imps IMPS ,, Struct
            return IMPS.IsLoaded() ? &IMPS->value40 : NULL;
        case 41: //impf Footstep Materials
            return UNPARSEDGET_FIELD41;
        case 42: //ofst_p Unknown
            *FieldValues = OFST.value;
            return NULL;
        default:
            return NULL;
        }
    }

bool WRLDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 4: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 5: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8 *)FieldValue)[0];
            versionControl2[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 6: //edid Editor ID
            EDID.Copy((STRING)FieldValue);
            break;
        case 7: //full Name
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //xezn Encounter Zone
            XEZN.Load();
            XEZN->value8 = *(FORMID *)FieldValue;
            return true;
        case 9: //wnam Worldspace
            WNAM.Load();
            WNAM->value9 = *(FORMID *)FieldValue;
            return true;
        case 10: //pnam PNAM ,, Struct
            PNAM.Load();
            PNAM->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //pnam_p PNAM ,, Struct
            if(ArraySize != 1)
                break;
            PNAM.Load();
            PNAM->value11[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 12: //cnam Climate
            CNAM.Load();
            CNAM->value12 = *(FORMID *)FieldValue;
            return true;
        case 13: //nam2 Water
            NAM2.Load();
            NAM2->value13 = *(FORMID *)FieldValue;
            return true;
        case 14: //nam3 LOD Water Type
            NAM3.Load();
            NAM3->value14 = *(FORMID *)FieldValue;
            return true;
        case 15: //nam4 LOD Water Height
            NAM4.Load();
            NAM4->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //icon Large Icon Filename
            ICON.Load();
            ICON->ICON.Copy((STRING)FieldValue);
            break;
        case 19: //mico Small Icon Filename
            ICON.Load();
            ICON->MICO.Copy((STRING)FieldValue);
            break;
        case 20: //mnam MNAM ,, Struct
            MNAM.Load();
            MNAM->value20 = *(SINT32 *)FieldValue;
            break;
        case 21: //mnam MNAM ,, Struct
            MNAM.Load();
            MNAM->value21 = *(SINT32 *)FieldValue;
            break;
        case 22: //mnam MNAM ,, Struct
            MNAM.Load();
            MNAM->value22 = *(SINT16 *)FieldValue;
            break;
        case 23: //mnam MNAM ,, Struct
            MNAM.Load();
            MNAM->value23 = *(SINT16 *)FieldValue;
            break;
        case 24: //mnam MNAM ,, Struct
            MNAM.Load();
            MNAM->value24 = *(SINT16 *)FieldValue;
            break;
        case 25: //mnam MNAM ,, Struct
            MNAM.Load();
            MNAM->value25 = *(SINT16 *)FieldValue;
            break;
        case 26: //onam ONAM ,, Struct
            ONAM.Load();
            ONAM->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //onam ONAM ,, Struct
            ONAM.Load();
            ONAM->value27 = *(FLOAT32 *)FieldValue;
            break;
        case 28: //onam ONAM ,, Struct
            ONAM.Load();
            ONAM->value28 = *(FLOAT32 *)FieldValue;
            break;
        case 29: //inam Image Space
            INAM.Load();
            INAM->value29 = *(FORMID *)FieldValue;
            return true;
        case 30: //data Flags
            DATA.Load();
            DATA->value30 = *(UINT8 *)FieldValue;
            break;
        case 31: //nam0 NAM0 ,, Struct
            NAM0.Load();
            NAM0->value31 = *(FLOAT32 *)FieldValue;
            break;
        case 32: //nam0 NAM0 ,, Struct
            NAM0.Load();
            NAM0->value32 = *(FLOAT32 *)FieldValue;
            break;
        case 33: //nam9 NAM9 ,, Struct
            NAM9.Load();
            NAM9->value33 = *(FLOAT32 *)FieldValue;
            break;
        case 34: //nam9 NAM9 ,, Struct
            NAM9.Load();
            NAM9->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //znam Music
            ZNAM.Load();
            ZNAM->value35 = *(FORMID *)FieldValue;
            return true;
        case 36: //nnam Canopy Shadow
            NNAM.Copy((STRING)FieldValue);
            break;
        case 37: //xnam Water Noise Texture
            XNAM.Copy((STRING)FieldValue);
            break;
        case 38: //imps IMPS ,, Struct
            IMPS.Load();
            IMPS->value38 = *(UINT32 *)FieldValue;
            break;
        case 39: //imps IMPS ,, Struct
            IMPS.Load();
            IMPS->value39 = *(FORMID *)FieldValue;
            return true;
        case 40: //imps IMPS ,, Struct
            IMPS.Load();
            IMPS->value40 = *(FORMID *)FieldValue;
            return true;
        case 41: //impf Footstep Materials
            return UNPARSEDGET_FIELD41;
        case 42: //ofst_p Unknown
            OFST.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void WRLDRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //formVersion
            formVersion = 0;
            return;
        case 5: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 6: //edid Editor ID
            EDID.Unload();
            return;
        case 7: //full Name
            FULL.Unload();
            return;
        case 8: //xezn Encounter Zone
            XEZN.Unload();
            return;
        case 9: //wnam Worldspace
            WNAM.Unload();
            return;
        case 10: //pnam PNAM ,, Struct
            PNAM.Unload();
            return;
        case 11: //pnam_p PNAM ,, Struct
            PNAM.Unload();
            return;
        case 12: //cnam Climate
            CNAM.Unload();
            return;
        case 13: //nam2 Water
            NAM2.Unload();
            return;
        case 14: //nam3 LOD Water Type
            NAM3.Unload();
            return;
        case 15: //nam4 LOD Water Height
            NAM4.Unload();
            return;
        case 16: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 17: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 18: //icon Large Icon Filename
            if(ICON.IsLoaded())
                ICON->ICON.Unload();
            return;
        case 19: //mico Small Icon Filename
            if(ICON.IsLoaded())
                ICON->MICO.Unload();
            return;
        case 20: //mnam MNAM ,, Struct
            MNAM.Unload();
            return;
        case 21: //mnam MNAM ,, Struct
            MNAM.Unload();
            return;
        case 22: //mnam MNAM ,, Struct
            MNAM.Unload();
            return;
        case 23: //mnam MNAM ,, Struct
            MNAM.Unload();
            return;
        case 24: //mnam MNAM ,, Struct
            MNAM.Unload();
            return;
        case 25: //mnam MNAM ,, Struct
            MNAM.Unload();
            return;
        case 26: //onam ONAM ,, Struct
            ONAM.Unload();
            return;
        case 27: //onam ONAM ,, Struct
            ONAM.Unload();
            return;
        case 28: //onam ONAM ,, Struct
            ONAM.Unload();
            return;
        case 29: //inam Image Space
            INAM.Unload();
            return;
        case 30: //data Flags
            DATA.Unload();
            return;
        case 31: //nam0 NAM0 ,, Struct
            NAM0.Unload();
            return;
        case 32: //nam0 NAM0 ,, Struct
            NAM0.Unload();
            return;
        case 33: //nam9 NAM9 ,, Struct
            NAM9.Unload();
            return;
        case 34: //nam9 NAM9 ,, Struct
            NAM9.Unload();
            return;
        case 35: //znam Music
            ZNAM.Unload();
            return;
        case 36: //nnam Canopy Shadow
            NNAM.Unload();
            return;
        case 37: //xnam Water Noise Texture
            XNAM.Unload();
            return;
        case 38: //imps IMPS ,, Struct
            IMPS.Unload();
            return;
        case 39: //imps IMPS ,, Struct
            IMPS.Unload();
            return;
        case 40: //imps IMPS ,, Struct
            IMPS.Unload();
            return;
        case 41: //impf Footstep Materials
            return UNPARSEDDEL_FIELD41;
        case 42: //ofst_p Unknown
            OFST.Unload();
            return;
        default:
            return;
        }
    }
}