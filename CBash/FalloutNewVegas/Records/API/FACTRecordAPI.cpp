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
#include "..\FACTRecord.h"

namespace FNV
{
UINT32 FACTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 8: //xnam Relation
            return FORMID_FIELD;
        case 9: //xnam Relation
            return SINT32_FIELD;
        case 10: //xnam Relation
            return UINT32_FIELD;
        case 11: //data DATA ,, Struct
            return UINT8_FIELD;
        case 12: //data DATA ,, Struct
            return UINT8_FIELD;
        case 13: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //cnam Unused
            return FLOAT32_FIELD;
        case 15: //rnam Rank#
            return SINT32_FIELD;
        case 16: //mnam Male
            return ISTRING_FIELD;
        case 17: //fnam Female
            return ISTRING_FIELD;
        case 18: //inam Insignia (Unused)
            return ISTRING_FIELD;
        case 19: //wmi1 Reputation
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * FACTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //xnam Relation
            return XNAMs.IsLoaded() ? &XNAMs->value8 : NULL;
        case 9: //xnam Relation
            return XNAMs.IsLoaded() ? &XNAMs->value9 : NULL;
        case 10: //xnam Relation
            return XNAMs.IsLoaded() ? &XNAMs->value10 : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value11 : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value13[0] : NULL;
            return NULL;
        case 14: //cnam Unused
            return CNAM.IsLoaded() ? &CNAM->value14 : NULL;
        case 15: //rnam Rank#
            return RNAM.IsLoaded() ? &RNAM->RNAM->value15 : NULL;
        case 16: //mnam Male
            return RNAM.IsLoaded() ? RNAM->MNAM.value : NULL;
        case 17: //fnam Female
            return RNAM.IsLoaded() ? RNAM->FNAM.value : NULL;
        case 18: //inam Insignia (Unused)
            return RNAM.IsLoaded() ? RNAM->INAM.value : NULL;
        case 19: //wmi1 Reputation
            return WMI1.IsLoaded() ? &WMI1->value19 : NULL;
        default:
            return NULL;
        }
    }

bool FACTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 8: //xnam Relation
            XNAMs.Load();
            XNAMs->value8 = *(FORMID *)FieldValue;
            return true;
        case 9: //xnam Relation
            XNAMs.Load();
            XNAMs->value9 = *(SINT32 *)FieldValue;
            break;
        case 10: //xnam Relation
            XNAMs.Load();
            XNAMs->value10 = *(UINT32 *)FieldValue;
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->value12 = *(UINT8 *)FieldValue;
            break;
        case 13: //data_p DATA ,, Struct
            if(ArraySize != 2)
                break;
            DATA.Load();
            DATA->value13[0] = ((UINT8 *)FieldValue)[0];
            DATA->value13[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 14: //cnam Unused
            CNAM.Load();
            CNAM->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //rnam Rank#
            RNAM.Load();
            RNAM->RNAM.Load();
            RNAM->RNAM->value15 = *(SINT32 *)FieldValue;
            break;
        case 16: //mnam Male
            RNAM.Load();
            RNAM->MNAM.Copy((STRING)FieldValue);
            break;
        case 17: //fnam Female
            RNAM.Load();
            RNAM->FNAM.Copy((STRING)FieldValue);
            break;
        case 18: //inam Insignia (Unused)
            RNAM.Load();
            RNAM->INAM.Copy((STRING)FieldValue);
            break;
        case 19: //wmi1 Reputation
            WMI1.Load();
            WMI1->value19 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void FACTRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 8: //xnam Relation
            XNAMs.Unload();
            return;
        case 9: //xnam Relation
            XNAMs.Unload();
            return;
        case 10: //xnam Relation
            XNAMs.Unload();
            return;
        case 11: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 12: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 13: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 14: //cnam Unused
            CNAM.Unload();
            return;
        case 15: //rnam Rank#
            if(RNAM.IsLoaded())
                RNAM->RNAM.Unload();
            return;
        case 16: //mnam Male
            if(RNAM.IsLoaded())
                RNAM->MNAM.Unload();
            return;
        case 17: //fnam Female
            if(RNAM.IsLoaded())
                RNAM->FNAM.Unload();
            return;
        case 18: //inam Insignia (Unused)
            if(RNAM.IsLoaded())
                RNAM->INAM.Unload();
            return;
        case 19: //wmi1 Reputation
            WMI1.Unload();
            return;
        default:
            return;
        }
    }
}