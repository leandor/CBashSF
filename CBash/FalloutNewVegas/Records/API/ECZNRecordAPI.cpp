/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "..\..\..\Common.h"
#include "..\ECZNRecord.h"

namespace FNV
{
UINT32 ECZNRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //data DATA ,, Struct
            return FORMID_FIELD;
        case 8: //data DATA ,, Struct
            return SINT8_FIELD;
        case 9: //data DATA ,, Struct
            return SINT8_FIELD;
        case 10: //data DATA ,, Struct
            return UINT8_FIELD;
        case 11: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * ECZNRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value7 : NULL;
        case 8: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value8 : NULL;
        case 9: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value9 : NULL;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value10 : NULL;
        case 11: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value11[0] : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool ECZNRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //data DATA ,, Struct
            DATA.Load();
            DATA->value7 = *(FORMID *)FieldValue;
            return true;
        case 8: //data DATA ,, Struct
            DATA.Load();
            DATA->value8 = *(SINT8 *)FieldValue;
            break;
        case 9: //data DATA ,, Struct
            DATA.Load();
            DATA->value9 = *(SINT8 *)FieldValue;
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value11[0] = ((UINT8ARRAY)FieldValue)[0];
            break;
        default:
            break;
        }
    return false;
    }

void ECZNRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 8: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 9: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 10: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 11: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}