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
#include "..\ACTIRecord.h"

namespace FNV
{
UINT32 ACTIRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //boundX
            return SINT16_FIELD;
        case 8: //boundY
            return SINT16_FIELD;
        case 9: //boundZ
            return SINT16_FIELD;
        case 10: //full Name
            return STRING_FIELD;
        case 11: //modl Model Filename
            return STRING_FIELD;
        case 12: //modb_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //modt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //mods Alternate Textures
            return STRING_FIELD;
        case 15: //mods Alternate Textures
            return FORMID_FIELD;
        case 16: //mods Alternate Textures
            return SINT32_FIELD;
        case 17: //modd FaceGen Model Flags
            return UINT8_FIELD;
        case 18: //scri Script
            return FORMID_FIELD;
        case 19: //dest Header
            return SINT32_FIELD;
        case 20: //dest Header
            return UINT8_FIELD;
        case 21: //dest Header
            return UINT8_FIELD;
        case 22: //dest_p Header
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 23: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 24: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 25: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 26: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 27: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 28: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 29: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 30: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 31: //dmdl Model Filename
            return ISTRING_FIELD;
        case 32: //dmdt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DMDT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 33: //snam Sound - Looping
            return FORMID_FIELD;
        case 34: //vnam Sound - Activation
            return FORMID_FIELD;
        case 35: //inam Radio Template
            return FORMID_FIELD;
        case 36: //rnam Radio Station
            return FORMID_FIELD;
        case 37: //wnam Water Type
            return FORMID_FIELD;
        case 38: //xato Activation Prompt
            return ISTRING_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * ACTIRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //boundX
            return OBND.IsLoaded() ? &OBND->x : NULL;
        case 8: //boundY
            return OBND.IsLoaded() ? &OBND->y : NULL;
        case 9: //boundZ
            return OBND.IsLoaded() ? &OBND->z : NULL;
        case 10: //full Name
            return FULL.value;
        case 11: //modl Model Filename
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 12: //modb_p Unknown
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODB.value : NULL;
            return NULL;
        case 13: //modt_p Texture Files Hashes
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODT.value : NULL;
            return NULL;
        case 14: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 15: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value15 : NULL;
        case 16: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value16 : NULL;
        case 17: //modd FaceGen Model Flags
            return MODL.IsLoaded() ? &MODL->MODD->value17 : NULL;
        case 18: //scri Script
            return SCRI.IsLoaded() ? &SCRI->value18 : NULL;
        case 19: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value19 : NULL;
        case 20: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value20 : NULL;
        case 21: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value21 : NULL;
        case 22: //dest_p Header
            *FieldValues = DEST.IsLoaded() ? &DEST->DEST->value22[0] : NULL;
            return NULL;
        case 23: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value23 : NULL;
        case 24: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value24 : NULL;
        case 25: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value25 : NULL;
        case 26: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value26 : NULL;
        case 27: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value27 : NULL;
        case 28: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value28 : NULL;
        case 29: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value29 : NULL;
        case 30: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value30 : NULL;
        case 31: //dmdl Model Filename
            return DEST.IsLoaded() ? DEST->DMDL.value : NULL;
        case 32: //dmdt_p Texture Files Hashes
            *FieldValues = (DEST.IsLoaded()) ? DEST->DMDT.value : NULL;
            return NULL;
        case 33: //snam Sound - Looping
            return SNAM.IsLoaded() ? &SNAM->value33 : NULL;
        case 34: //vnam Sound - Activation
            return VNAM.IsLoaded() ? &VNAM->value34 : NULL;
        case 35: //inam Radio Template
            return INAM.IsLoaded() ? &INAM->value35 : NULL;
        case 36: //rnam Radio Station
            return RNAM.IsLoaded() ? &RNAM->value36 : NULL;
        case 37: //wnam Water Type
            return WNAM.IsLoaded() ? &WNAM->value37 : NULL;
        case 38: //xato Activation Prompt
            return XATO.value;
        default:
            return NULL;
        }
    }

bool ACTIRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //boundX
            OBND.Load();
            OBND->x = *(SINT16 *)FieldValue;
            break;
        case 8: //boundY
            OBND.Load();
            OBND->y = *(SINT16 *)FieldValue;
            break;
        case 9: //boundZ
            OBND.Load();
            OBND->z = *(SINT16 *)FieldValue;
            break;
        case 10: //full Name
            FULL.Copy((STRING)FieldValue);
            break;
        case 11: //modl Model Filename
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 12: //modb_p Unknown
            MODL.Load();
            MODL->MODB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 13: //modt_p Texture Files Hashes
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 14: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 15: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value15 = *(FORMID *)FieldValue;
            return true;
        case 16: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value16 = *(SINT32 *)FieldValue;
            break;
        case 17: //modd FaceGen Model Flags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value17 = *(UINT8 *)FieldValue;
            break;
        case 18: //scri Script
            SCRI.Load();
            SCRI->value18 = *(FORMID *)FieldValue;
            return true;
        case 19: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value19 = *(SINT32 *)FieldValue;
            break;
        case 20: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value20 = *(UINT8 *)FieldValue;
            break;
        case 21: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value21 = *(UINT8 *)FieldValue;
            break;
        case 22: //dest_p Header
            if(ArraySize != 2)
                break;
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value22[0] = ((UINT8 *)FieldValue)[0];
            DEST->DEST->value22[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 23: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value24 = *(UINT8 *)FieldValue;
            break;
        case 25: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value25 = *(UINT8 *)FieldValue;
            break;
        case 26: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value26 = *(UINT8 *)FieldValue;
            break;
        case 27: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value27 = *(SINT32 *)FieldValue;
            break;
        case 28: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value28 = *(FORMID *)FieldValue;
            return true;
        case 29: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value29 = *(FORMID *)FieldValue;
            return true;
        case 30: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value30 = *(SINT32 *)FieldValue;
            break;
        case 31: //dmdl Model Filename
            DEST.Load();
            DEST->DMDL.Copy((STRING)FieldValue);
            break;
        case 32: //dmdt_p Texture Files Hashes
            DEST.Load();
            DEST->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 33: //snam Sound - Looping
            SNAM.Load();
            SNAM->value33 = *(FORMID *)FieldValue;
            return true;
        case 34: //vnam Sound - Activation
            VNAM.Load();
            VNAM->value34 = *(FORMID *)FieldValue;
            return true;
        case 35: //inam Radio Template
            INAM.Load();
            INAM->value35 = *(FORMID *)FieldValue;
            return true;
        case 36: //rnam Radio Station
            RNAM.Load();
            RNAM->value36 = *(FORMID *)FieldValue;
            return true;
        case 37: //wnam Water Type
            WNAM.Load();
            WNAM->value37 = *(FORMID *)FieldValue;
            return true;
        case 38: //xato Activation Prompt
            XATO.Copy((STRING)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void ACTIRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //boundX
            if(OBND.IsLoaded())
                OBND->x = defaultOBND.x;
            return;
        case 8: //boundY
            if(OBND.IsLoaded())
                OBND->y = defaultOBND.y;
            return;
        case 9: //boundZ
            if(OBND.IsLoaded())
                OBND->z = defaultOBND.z;
            return;
        case 10: //full Name
            FULL.Unload();
            return;
        case 11: //modl Model Filename
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 12: //modb_p Unknown
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 13: //modt_p Texture Files Hashes
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 14: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 15: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 16: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 17: //modd FaceGen Model Flags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 18: //scri Script
            SCRI.Unload();
            return;
        case 19: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 20: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 21: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 22: //dest_p Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 23: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 24: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 25: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 26: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 27: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 28: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 29: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 30: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 31: //dmdl Model Filename
            if(DEST.IsLoaded())
                DEST->DMDL.Unload();
            return;
        case 32: //dmdt_p Texture Files Hashes
            if(DEST.IsLoaded())
                DEST->DMDT.Unload();
            return;
        case 33: //snam Sound - Looping
            SNAM.Unload();
            return;
        case 34: //vnam Sound - Activation
            VNAM.Unload();
            return;
        case 35: //inam Radio Template
            INAM.Unload();
            return;
        case 36: //rnam Radio Station
            RNAM.Unload();
            return;
        case 37: //wnam Water Type
            WNAM.Unload();
            return;
        case 38: //xato Activation Prompt
            XATO.Unload();
            return;
        default:
            return;
        }
    }
}