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
#include "..\ALCHRecord.h"

namespace FNV
{
UINT32 ALCHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 10: //full
            return STRING_FIELD;
        case 11: //modPath
            return ISTRING_FIELD;
        case 12: //modb
            return FLOAT32_FIELD;
        case 13: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //altTextures
            if(!MODL.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return MODL->Textures.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return STRING_FIELD;
                case 2: //texture
                    return FORMID_FIELD;
                case 3: //index
                    return SINT32_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }

        case 17: //modelFlags
            return UINT8_FIELD;
        case 18: //iconPath
            return ISTRING_FIELD;
        case 19: //smallIconPath
            return ISTRING_FIELD;
        case 20: //scri Script
            return FORMID_FIELD;
        case 21: //dest Header
            return SINT32_FIELD;
        case 22: //dest Header
            return UINT8_FIELD;
        case 23: //dest Header
            return UINT8_FIELD;
        case 24: //dest_p Header
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 25: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 26: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 27: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 28: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 29: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 30: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 31: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 32: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 33: //dmdl Model Filename
            return ISTRING_FIELD;
        case 34: //dmdt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DMDT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 35: //ynam Sound - Pick Up
            return FORMID_FIELD;
        case 36: //znam Sound - Drop
            return FORMID_FIELD;
        case 37: //etyp Equipment Type
            return SINT32_FIELD;
        case 38: //data Weight
            return FLOAT32_FIELD;
        case 39: //enit ENIT ,, Struct
            return SINT32_FIELD;
        case 40: //enit ENIT ,, Struct
            return UINT8_FIELD;
        case 41: //enit_p ENIT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 42: //enit ENIT ,, Struct
            return FORMID_FIELD;
        case 43: //enit ENIT ,, Struct
            return FLOAT32_FIELD;
        case 44: //enit ENIT ,, Struct
            return FORMID_FIELD;
        case 45: //efid Base Effect
            return FORMID_FIELD;
        case 46: //efit Effect Item
            return UINT32_FIELD;
        case 47: //efit Effect Item
            return UINT32_FIELD;
        case 48: //efit Effect Item
            return UINT32_FIELD;
        case 49: //efit Effect Item
            return UINT32_FIELD;
        case 50: //efit Effect Item
            return UNPARSED_FIELD;
        case 51: //ctda Conditions
            return UINT8_FIELD;
        case 52: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 53: //ctda Conditions
            return UNPARSED_FIELD;
        case 54: //ctda Conditions
            return UINT32_FIELD;
        case 55: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 56: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 57: //ctda Conditions
            return UINT32_FIELD;
        case 58: //ctda Conditions
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * ALCHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 10: //full
            return FULLReq.value;
        case 11: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 12: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 13: //modt_p
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODT.value : NULL;
            return NULL;
        case 14: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 15: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value15 : NULL;
        case 16: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value16 : NULL;
        case 17: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD->value17 : NULL;
        case 18: //iconPath
            return ICON.value;
        case 19: //smallIconPath
            return MICO.value;
        case 20: //scri Script
            return SCRI.IsLoaded() ? &SCRI->value20 : NULL;
        case 21: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value21 : NULL;
        case 22: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value22 : NULL;
        case 23: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value23 : NULL;
        case 24: //dest_p Header
            *FieldValues = DEST.IsLoaded() ? &DEST->DEST->value24[0] : NULL;
            return NULL;
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
        case 31: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value31 : NULL;
        case 32: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value32 : NULL;
        case 33: //dmdl Model Filename
            return DEST.IsLoaded() ? DEST->DMDL.value : NULL;
        case 34: //dmdt_p Texture Files Hashes
            *FieldValues = (DEST.IsLoaded()) ? DEST->DMDT.value : NULL;
            return NULL;
        case 35: //ynam Sound - Pick Up
            return YNAM.IsLoaded() ? &YNAM->value35 : NULL;
        case 36: //znam Sound - Drop
            return ZNAM.IsLoaded() ? &ZNAM->value36 : NULL;
        case 37: //etyp Equipment Type
            return ETYPReq.IsLoaded() ? &ETYPReq->value37 : NULL;
        case 38: //data Weight
            return DATA.IsLoaded() ? &DATA->value38 : NULL;
        case 39: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value39 : NULL;
        case 40: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value40 : NULL;
        case 41: //enit_p ENIT ,, Struct
            *FieldValues = ENIT.IsLoaded() ? &ENIT->value41[0] : NULL;
            return NULL;
        case 42: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value42 : NULL;
        case 43: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value43 : NULL;
        case 44: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value44 : NULL;
        case 45: //efid Base Effect
            return EFID.IsLoaded() ? &EFID->EFID->value45 : NULL;
        case 46: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value46 : NULL;
        case 47: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value47 : NULL;
        case 48: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value48 : NULL;
        case 49: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value49 : NULL;
        case 50: //efit Effect Item
            return UNPARSEDGET_FIELD50;
        case 51: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value51 : NULL;
        case 52: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value52[0] : NULL;
            return NULL;
        case 53: //ctda Conditions
            return UNPARSEDGET_FIELD53;
        case 54: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value54 : NULL;
        case 55: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value55[0] : NULL;
            return NULL;
        case 56: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value56[0] : NULL;
            return NULL;
        case 57: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value57 : NULL;
        case 58: //ctda Conditions
            return UNPARSEDGET_FIELD58;
        default:
            return NULL;
        }
    }

bool ALCHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 10: //full
            FULLReq.Copy((STRING)FieldValue);
            break;
        case 11: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 12: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 13: //modt_p
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
        case 17: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value17 = *(UINT8 *)FieldValue;
            break;
        case 18: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 19: //smallIconPath
            MICO.Copy((STRING)FieldValue);
            break;
        case 20: //scri Script
            SCRI.Load();
            SCRI->value20 = *(FORMID *)FieldValue;
            return true;
        case 21: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value21 = *(SINT32 *)FieldValue;
            break;
        case 22: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value22 = *(UINT8 *)FieldValue;
            break;
        case 23: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //dest_p Header
            if(ArraySize != 2)
                break;
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value24[0] = ((UINT8 *)FieldValue)[0];
            DEST->DEST->value24[1] = ((UINT8 *)FieldValue)[1];
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
            DEST->DSTD->value27 = *(UINT8 *)FieldValue;
            break;
        case 28: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value29 = *(SINT32 *)FieldValue;
            break;
        case 30: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value30 = *(FORMID *)FieldValue;
            return true;
        case 31: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value31 = *(FORMID *)FieldValue;
            return true;
        case 32: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value32 = *(SINT32 *)FieldValue;
            break;
        case 33: //dmdl Model Filename
            DEST.Load();
            DEST->DMDL.Copy((STRING)FieldValue);
            break;
        case 34: //dmdt_p Texture Files Hashes
            DEST.Load();
            DEST->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 35: //ynam Sound - Pick Up
            YNAM.Load();
            YNAM->value35 = *(FORMID *)FieldValue;
            return true;
        case 36: //znam Sound - Drop
            ZNAM.Load();
            ZNAM->value36 = *(FORMID *)FieldValue;
            return true;
        case 37: //etyp Equipment Type
            ETYPReq.Load();
            ETYPReq->value37 = *(SINT32 *)FieldValue;
            break;
        case 38: //data Weight
            DATA.Load();
            DATA->value38 = *(FLOAT32 *)FieldValue;
            break;
        case 39: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value39 = *(SINT32 *)FieldValue;
            break;
        case 40: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value40 = *(UINT8 *)FieldValue;
            break;
        case 41: //enit_p ENIT ,, Struct
            if(ArraySize != 3)
                break;
            ENIT.Load();
            ENIT->value41[0] = ((UINT8 *)FieldValue)[0];
            ENIT->value41[1] = ((UINT8 *)FieldValue)[1];
            ENIT->value41[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 42: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value42 = *(FORMID *)FieldValue;
            return true;
        case 43: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value43 = *(FLOAT32 *)FieldValue;
            break;
        case 44: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value44 = *(FORMID *)FieldValue;
            return true;
        case 45: //efid Base Effect
            EFID.Load();
            EFID->EFID.Load();
            EFID->EFID->value45 = *(FORMID *)FieldValue;
            return true;
        case 46: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value46 = *(UINT32 *)FieldValue;
            break;
        case 47: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value47 = *(UINT32 *)FieldValue;
            break;
        case 48: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value48 = *(UINT32 *)FieldValue;
            break;
        case 49: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value49 = *(UINT32 *)FieldValue;
            break;
        case 50: //efit Effect Item
            return UNPARSEDGET_FIELD50;
        case 51: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value51 = *(UINT8 *)FieldValue;
            break;
        case 52: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value52[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value52[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value52[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 53: //ctda Conditions
            return UNPARSEDGET_FIELD53;
        case 54: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value54 = *(UINT32 *)FieldValue;
            break;
        case 55: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value55[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value55[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value55[2] = ((UINT8 *)FieldValue)[2];
            EFID->CTDA->value55[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 56: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value56[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value56[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value56[2] = ((UINT8 *)FieldValue)[2];
            EFID->CTDA->value56[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 57: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value57 = *(UINT32 *)FieldValue;
            break;
        case 58: //ctda Conditions
            return UNPARSEDGET_FIELD58;
        default:
            break;
        }
    return false;
    }

void ALCHRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 10: //full
            FULLReq.Unload();
            return;
        case 11: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 12: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 13: //modt_p
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
        case 17: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 18: //iconPath
            ICON.Unload();
            return;
        case 19: //smallIconPath
            MICO.Unload();
            return;
        case 20: //scri Script
            SCRI.Unload();
            return;
        case 21: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 22: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 23: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 24: //dest_p Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
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
        case 31: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 32: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 33: //dmdl Model Filename
            if(DEST.IsLoaded())
                DEST->DMDL.Unload();
            return;
        case 34: //dmdt_p Texture Files Hashes
            if(DEST.IsLoaded())
                DEST->DMDT.Unload();
            return;
        case 35: //ynam Sound - Pick Up
            YNAM.Unload();
            return;
        case 36: //znam Sound - Drop
            ZNAM.Unload();
            return;
        case 37: //etyp Equipment Type
            ETYPReq.Unload();
            return;
        case 38: //data Weight
            DATA.Unload();
            return;
        case 39: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 40: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 41: //enit_p ENIT ,, Struct
            ENIT.Unload();
            return;
        case 42: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 43: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 44: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 45: //efid Base Effect
            if(EFID.IsLoaded())
                EFID->EFID.Unload();
            return;
        case 46: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 47: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 48: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 49: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 50: //efit Effect Item
            return UNPARSEDDEL_FIELD50;
        case 51: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 52: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 53: //ctda Conditions
            return UNPARSEDDEL_FIELD53;
        case 54: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 55: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 56: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 57: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 58: //ctda Conditions
            return UNPARSEDDEL_FIELD58;
        default:
            return;
        }
    }
}