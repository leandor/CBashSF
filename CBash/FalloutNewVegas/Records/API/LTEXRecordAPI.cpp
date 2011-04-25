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
#include "..\LTEXRecord.h"

namespace FNV
{
UINT32 LTEXRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 6: //eid
            return ISTRING_FIELD;
        case 7: //icon Large Icon Filename
            return ISTRING_FIELD;
        case 8: //mico Small Icon Filename
            return ISTRING_FIELD;
        case 9: //tnam Texture
            return FORMID_FIELD;
        case 10: //hnam HNAM ,, Struct
            return UINT8_FIELD;
        case 11: //hnam HNAM ,, Struct
            return UINT8_FIELD;
        case 12: //hnam HNAM ,, Struct
            return UINT8_FIELD;
        case 13: //snam Texture Specular Exponent
            return UINT8_FIELD;
        case 14: //gnam Grass
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * LTEXRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 6: //eid
            return EDID.value;
        case 7: //icon Large Icon Filename
            return ICON.IsLoaded() ? ICON->ICON.value : NULL;
        case 8: //mico Small Icon Filename
            return ICON.IsLoaded() ? ICON->MICO.value : NULL;
        case 9: //tnam Texture
            return TNAM.IsLoaded() ? &TNAM->value9 : NULL;
        case 10: //hnam HNAM ,, Struct
            return HNAM.IsLoaded() ? &HNAM->value10 : NULL;
        case 11: //hnam HNAM ,, Struct
            return HNAM.IsLoaded() ? &HNAM->value11 : NULL;
        case 12: //hnam HNAM ,, Struct
            return HNAM.IsLoaded() ? &HNAM->value12 : NULL;
        case 13: //snam Texture Specular Exponent
            return SNAM.IsLoaded() ? &SNAM->value13 : NULL;
        case 14: //gnam Grass
            return GNAM.IsLoaded() ? &GNAM->value14 : NULL;
        default:
            return NULL;
        }
    }

bool LTEXRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 6: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 7: //icon Large Icon Filename
            ICON.Load();
            ICON->ICON.Copy((STRING)FieldValue);
            break;
        case 8: //mico Small Icon Filename
            ICON.Load();
            ICON->MICO.Copy((STRING)FieldValue);
            break;
        case 9: //tnam Texture
            TNAM.Load();
            TNAM->value9 = *(FORMID *)FieldValue;
            return true;
        case 10: //hnam HNAM ,, Struct
            HNAM.Load();
            HNAM->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //hnam HNAM ,, Struct
            HNAM.Load();
            HNAM->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //hnam HNAM ,, Struct
            HNAM.Load();
            HNAM->value12 = *(UINT8 *)FieldValue;
            break;
        case 13: //snam Texture Specular Exponent
            SNAM.Load();
            SNAM->value13 = *(UINT8 *)FieldValue;
            break;
        case 14: //gnam Grass
            GNAM.Load();
            GNAM->value14 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void LTEXRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 6: //eid
            EDID.Unload();
            return;
        case 7: //icon Large Icon Filename
            if(ICON.IsLoaded())
                ICON->ICON.Unload();
            return;
        case 8: //mico Small Icon Filename
            if(ICON.IsLoaded())
                ICON->MICO.Unload();
            return;
        case 9: //tnam Texture
            TNAM.Unload();
            return;
        case 10: //hnam HNAM ,, Struct
            HNAM.Unload();
            return;
        case 11: //hnam HNAM ,, Struct
            HNAM.Unload();
            return;
        case 12: //hnam HNAM ,, Struct
            HNAM.Unload();
            return;
        case 13: //snam Texture Specular Exponent
            SNAM.Unload();
            return;
        case 14: //gnam Grass
            GNAM.Unload();
            return;
        default:
            return;
        }
    }
}