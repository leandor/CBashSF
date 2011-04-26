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
#include "..\IDLMRecord.h"

namespace FNV
{
UINT32 IDLMRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //obnd Object Bounds
            return SINT16_FIELD;
        case 8: //obnd Object Bounds
            return SINT16_FIELD;
        case 9: //obnd Object Bounds
            return SINT16_FIELD;
        case 10: //idlf Flags
            return UINT8_FIELD;
        case 11: //idlc IDLC ,, Struct
            return UINT8_FIELD;
        case 12: //idlc_p IDLC ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //idlt Idle Timer Setting
            return FLOAT32_FIELD;
        case 14: //idla Animations
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * IDLMRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value7 : NULL;
        case 8: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value8 : NULL;
        case 9: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value9 : NULL;
        case 10: //idlf Flags
            return IDLF.IsLoaded() ? &IDLF->value10 : NULL;
        case 11: //idlc IDLC ,, Struct
            return IDLC.IsLoaded() ? &IDLC->value11 : NULL;
        case 12: //idlc_p IDLC ,, Struct
            *FieldValues = IDLC.IsLoaded() ? &IDLC->value12[0] : NULL;
            return NULL;
        case 13: //idlt Idle Timer Setting
            return IDLT.IsLoaded() ? &IDLT->value13 : NULL;
        case 14: //idla Animations
            return UNPARSEDGET_FIELD14;
        default:
            return NULL;
        }
    }

bool IDLMRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value7 = *(SINT16 *)FieldValue;
            break;
        case 8: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value8 = *(SINT16 *)FieldValue;
            break;
        case 9: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value9 = *(SINT16 *)FieldValue;
            break;
        case 10: //idlf Flags
            IDLF.Load();
            IDLF->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //idlc IDLC ,, Struct
            IDLC.Load();
            IDLC->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //idlc_p IDLC ,, Struct
            if(ArraySize != 3)
                break;
            IDLC.Load();
            IDLC->value12[0] = ((UINT8 *)FieldValue)[0];
            IDLC->value12[1] = ((UINT8 *)FieldValue)[1];
            IDLC->value12[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 13: //idlt Idle Timer Setting
            IDLT.Load();
            IDLT->value13 = *(FLOAT32 *)FieldValue;
            break;
        case 14: //idla Animations
            return UNPARSEDGET_FIELD14;
        default:
            break;
        }
    return false;
    }

void IDLMRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 8: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 9: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 10: //idlf Flags
            IDLF.Unload();
            return;
        case 11: //idlc IDLC ,, Struct
            IDLC.Unload();
            return;
        case 12: //idlc_p IDLC ,, Struct
            IDLC.Unload();
            return;
        case 13: //idlt Idle Timer Setting
            IDLT.Unload();
            return;
        case 14: //idla Animations
            return UNPARSEDDEL_FIELD14;
        default:
            return;
        }
    }
}