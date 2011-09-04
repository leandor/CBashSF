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
#include "..\LTEXRecord.h"

namespace Ob
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
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //iconPath
            return ISTRING_FIELD;
        case 6: //types
            return UINT8_TYPE_FIELD;
        case 7: //friction
            return UINT8_FIELD;
        case 8: //restitution
            return UINT8_FIELD;
        case 9: //specular
            return UINT8_FIELD;
        case 10: //grass
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (UINT32)GNAM.value.size();
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * LTEXRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return cleaned_flag1();
        case 2: //fid
            return &formID;
        case 3: //flags2
            return cleaned_flag2();
        case 4: //eid
            return EDID.value;
        case 5: //iconPath
            return ICON.value;
        case 6: //types
            return HNAM.IsLoaded() ? &HNAM->types : NULL;
        case 7: //friction
            return HNAM.IsLoaded() ? &HNAM->friction : NULL;
        case 8: //restitution
            return HNAM.IsLoaded() ? &HNAM->restitution : NULL;
        case 9: //specular
            return SNAM.IsLoaded() ? SNAM.value : NULL;
        case 10: //grass
            *FieldValues = GNAM.value.size() ? &GNAM.value[0] : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool LTEXRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(UINT32 *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 6: //types
            SetType(*(UINT8 *)FieldValue);
            break;
        case 7: //friction
            HNAM.Load();
            HNAM->friction = *(UINT8 *)FieldValue;
            break;
        case 8: //restitution
            HNAM.Load();
            HNAM->restitution = *(UINT8 *)FieldValue;
            break;
        case 9: //specular
            SNAM.Load();
            *SNAM.value = *(UINT8 *)FieldValue;
            break;
        case 10: //grass
            GNAM.resize(ArraySize);
            for(UINT32 x = 0; x < ArraySize; x++)
                GNAM.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        default:
            break;
        }
    return false;
    }

void LTEXRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    LTEXHNAM defaultHNAM;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //iconPath
            ICON.Unload();
            return;
        case 6: //types
            if(HNAM.IsLoaded())
                HNAM->types = defaultHNAM.types;
            return;
        case 7: //friction
            if(HNAM.IsLoaded())
                HNAM->friction = defaultHNAM.friction;
            return;
        case 8: //restitution
            if(HNAM.IsLoaded())
                HNAM->restitution = defaultHNAM.restitution;
            return;
        case 9: //specular
            SNAM.Unload();
            return;
        case 10: //grass
            GNAM.Unload();
            return;
        default:
            return;
        }
    return;
    }
}