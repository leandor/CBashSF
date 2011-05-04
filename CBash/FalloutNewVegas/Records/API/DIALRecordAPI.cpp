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
#include "..\DIALRecord.h"

namespace FNV
{
UINT32 DIALRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //qsti Quest
            return FORMID_FIELD;
        case 8: //infc Unknown
            return FORMID_FIELD;
        case 9: //infx Unknown
            return SINT32_FIELD;
        case 10: //qstr Quest
            return FORMID_FIELD;
        case 11: //full
            return STRING_FIELD;
        case 12: //pnam Priority
            return FLOAT32_FIELD;
        case 13: //tdum
            return ISTRING_FIELD;
        case 14: //data DATA ,, Struct
            return UINT8_FIELD;
        case 15: //data DATA ,, Struct
            return UINT8_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * DIALRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //qsti Quest
            return QSTI.IsLoaded() ? &QSTI->value7 : NULL;
        case 8: //infc Unknown
            return INFC.IsLoaded() ? &INFC->value8 : NULL;
        case 9: //infx Unknown
            return INFX.IsLoaded() ? &INFX->value9 : NULL;
        case 10: //qstr Quest
            return QSTR.IsLoaded() ? &QSTR->value10 : NULL;
        case 11: //full
            return FULL.value;
        case 12: //pnam Priority
            return PNAM.IsLoaded() ? &PNAM->value12 : NULL;
        case 13: //tdum
            return TDUM.value;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value15 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool DIALRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //qsti Quest
            QSTI.Load();
            QSTI->value7 = *(FORMID *)FieldValue;
            return true;
        case 8: //infc Unknown
            INFC.Load();
            INFC->value8 = *(FORMID *)FieldValue;
            return true;
        case 9: //infx Unknown
            INFX.Load();
            INFX->value9 = *(SINT32 *)FieldValue;
            break;
        case 10: //qstr Quest
            QSTR.Load();
            QSTR->value10 = *(FORMID *)FieldValue;
            return true;
        case 11: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 12: //pnam Priority
            PNAM.Load();
            PNAM->value12 = *(FLOAT32 *)FieldValue;
            break;
        case 13: //tdum
            TDUM.Copy((STRING)FieldValue);
            break;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->value14 = *(UINT8 *)FieldValue;
            break;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->value15 = *(UINT8 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void DIALRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //qsti Quest
            QSTI.Unload();
            return;
        case 8: //infc Unknown
            INFC.Unload();
            return;
        case 9: //infx Unknown
            INFX.Unload();
            return;
        case 10: //qstr Quest
            QSTR.Unload();
            return;
        case 11: //full
            FULL.Unload();
            return;
        case 12: //pnam Priority
            PNAM.Unload();
            return;
        case 13: //tdum
            TDUM.Unload();
            return;
        case 14: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data DATA ,, Struct
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}