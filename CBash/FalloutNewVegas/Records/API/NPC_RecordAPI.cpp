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
#include "..\NPC_Record.h"

namespace FNV
{
UINT32 NPC_Record::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //obnd Object Bounds
            return SINT16_FIELD;
        case 8: //obnd Object Bounds
            return SINT16_FIELD;
        case 9: //obnd Object Bounds
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
        case 18: //acbs ACBS ,, Struct
            return UINT32_FIELD;
        case 19: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 20: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 21: //acbs ACBS ,, Struct
            return SINT16_FIELD;
        case 22: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 23: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 24: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 25: //acbs ACBS ,, Struct
            return FLOAT32_FIELD;
        case 26: //acbs ACBS ,, Struct
            return SINT16_FIELD;
        case 27: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 28: //snam SNAM ,, Struct
            return FORMID_FIELD;
        case 29: //snam SNAM ,, Struct
            return UINT8_FIELD;
        case 30: //snam_p SNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 31: //inam Death item
            return FORMID_FIELD;
        case 32: //vtck Voice
            return FORMID_FIELD;
        case 33: //tplt Template
            return FORMID_FIELD;
        case 34: //rnam Race
            return FORMID_FIELD;
        case 35: //splo Actor Effect
            return FORMID_FIELD;
        case 36: //eitm Unarmed Attack Effect
            return FORMID_FIELD;
        case 37: //eamt Unarmed Attack Animation
            return UINT16_FIELD;
        case 38: //dest Header
            return SINT32_FIELD;
        case 39: //dest Header
            return UINT8_FIELD;
        case 40: //dest Header
            return UINT8_FIELD;
        case 41: //dest_p Header
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 42: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 43: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 44: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 45: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 46: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 47: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 48: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 49: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 50: //dmdl Model Filename
            return ISTRING_FIELD;
        case 51: //dmdt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DMDT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 52: //scri Script
            return FORMID_FIELD;
        case 53: //cnto Item
            return FORMID_FIELD;
        case 54: //cnto Item
            return SINT32_FIELD;
        case 55: //aidt AI Data
            return UINT8_FIELD;
        case 56: //aidt AI Data
            return UINT8_FIELD;
        case 57: //aidt AI Data
            return UINT8_FIELD;
        case 58: //aidt AI Data
            return UINT8_FIELD;
        case 59: //aidt AI Data
            return UINT8_FIELD;
        case 60: //aidt_p AI Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 61: //aidt AI Data
            return UINT32_FIELD;
        case 62: //aidt AI Data
            return SINT8_FIELD;
        case 63: //aidt AI Data
            return UINT8_FIELD;
        case 64: //aidt AI Data
            return SINT8_FIELD;
        case 65: //aidt AI Data
            return UINT8_FIELD;
        case 66: //aidt AI Data
            return SINT32_FIELD;
        case 67: //pkid Package
            return FORMID_FIELD;
        case 68: //cnam Class
            return FORMID_FIELD;
        case 69: //data DATA ,, Struct
            return SINT32_FIELD;
        case 70: //data DATA ,, Struct
            return UINT8_FIELD;
        case 71: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 0;
                default:
                    return UNKNOWN_FIELD;
                }
        case 72: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 73: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 74: //pnam Head Part
            return FORMID_FIELD;
        case 75: //hnam Hair
            return FORMID_FIELD;
        case 76: //lnam Hair length
            return FLOAT32_FIELD;
        case 77: //enam Eyes
            return FORMID_FIELD;
        case 78: //hclr HCLR ,, Struct
            return UINT8_FIELD;
        case 79: //hclr HCLR ,, Struct
            return UINT8_FIELD;
        case 80: //hclr HCLR ,, Struct
            return UINT8_FIELD;
        case 81: //hclr_p HCLR ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 82: //znam Combat Style
            return FORMID_FIELD;
        case 83: //nam4 Impact Material Type
            return UINT32_FIELD;
        case 84: //fggs_p FaceGen Geometry-Symmetric
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGGS.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 85: //fgga_p FaceGen Geometry-Asymmetric
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGGA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 86: //fgts_p FaceGen Texture-Symmetric
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGTS.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 87: //nam5 Unknown
            return UINT16_FIELD;
        case 88: //nam6 Height
            return FLOAT32_FIELD;
        case 89: //nam7 Weight
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * NPC_Record::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value7 : NULL;
        case 8: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value8 : NULL;
        case 9: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value9 : NULL;
        case 10: //full Name
            return FULLActor.value;
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
        case 18: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value18 : NULL;
        case 19: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value19 : NULL;
        case 20: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value20 : NULL;
        case 21: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value21 : NULL;
        case 22: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value22 : NULL;
        case 23: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value23 : NULL;
        case 24: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value24 : NULL;
        case 25: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value25 : NULL;
        case 26: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value26 : NULL;
        case 27: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value27 : NULL;
        case 28: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value28 : NULL;
        case 29: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value29 : NULL;
        case 30: //snam_p SNAM ,, Struct
            *FieldValues = SNAM.IsLoaded() ? &SNAM->value30[0] : NULL;
            return NULL;
        case 31: //inam Death item
            return INAM.IsLoaded() ? &INAM->value31 : NULL;
        case 32: //vtck Voice
            return VTCK.IsLoaded() ? &VTCK->value32 : NULL;
        case 33: //tplt Template
            return TPLT.IsLoaded() ? &TPLT->value33 : NULL;
        case 34: //rnam Race
            return RNAM.IsLoaded() ? &RNAM->value34 : NULL;
        case 35: //splo Actor Effect
            return SPLOs.IsLoaded() ? &SPLOs->value35 : NULL;
        case 36: //eitm Unarmed Attack Effect
            return EITM.IsLoaded() ? &EITM->value36 : NULL;
        case 37: //eamt Unarmed Attack Animation
            return EAMT.IsLoaded() ? &EAMT->value37 : NULL;
        case 38: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value38 : NULL;
        case 39: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value39 : NULL;
        case 40: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value40 : NULL;
        case 41: //dest_p Header
            *FieldValues = DEST.IsLoaded() ? &DEST->DEST->value41[0] : NULL;
            return NULL;
        case 42: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value42 : NULL;
        case 43: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value43 : NULL;
        case 44: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value44 : NULL;
        case 45: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value45 : NULL;
        case 46: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value46 : NULL;
        case 47: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value47 : NULL;
        case 48: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value48 : NULL;
        case 49: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value49 : NULL;
        case 50: //dmdl Model Filename
            return DEST.IsLoaded() ? DEST->DMDL.value : NULL;
        case 51: //dmdt_p Texture Files Hashes
            *FieldValues = (DEST.IsLoaded()) ? DEST->DMDT.value : NULL;
            return NULL;
        case 52: //scri Script
            return SCRIActor.IsLoaded() ? &SCRIActor->value52 : NULL;
        case 53: //cnto Item
            return CNTO.IsLoaded() ? &CNTO->value53 : NULL;
        case 54: //cnto Item
            return CNTO.IsLoaded() ? &CNTO->value54 : NULL;
        case 55: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value55 : NULL;
        case 56: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value56 : NULL;
        case 57: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value57 : NULL;
        case 58: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value58 : NULL;
        case 59: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value59 : NULL;
        case 60: //aidt_p AI Data
            *FieldValues = AIDT.IsLoaded() ? &AIDT->value60[0] : NULL;
            return NULL;
        case 61: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value61 : NULL;
        case 62: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value62 : NULL;
        case 63: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value63 : NULL;
        case 64: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value64 : NULL;
        case 65: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value65 : NULL;
        case 66: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value66 : NULL;
        case 67: //pkid Package
            return PKID.IsLoaded() ? &PKID->value67 : NULL;
        case 68: //cnam Class
            return CNAM.IsLoaded() ? &CNAM->value68 : NULL;
        case 69: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value69 : NULL;
        case 70: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value70 : NULL;
        case 71: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value71[0] : NULL;
            return NULL;
        case 72: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value72 : NULL;
        case 73: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value73 : NULL;
        case 74: //pnam Head Part
            return PNAM.IsLoaded() ? &PNAM->value74 : NULL;
        case 75: //hnam Hair
            return HNAM.IsLoaded() ? &HNAM->value75 : NULL;
        case 76: //lnam Hair length
            return LNAM.IsLoaded() ? &LNAM->value76 : NULL;
        case 77: //enam Eyes
            return ENAM.IsLoaded() ? &ENAM->value77 : NULL;
        case 78: //hclr HCLR ,, Struct
            return HCLR.IsLoaded() ? &HCLR->value78 : NULL;
        case 79: //hclr HCLR ,, Struct
            return HCLR.IsLoaded() ? &HCLR->value79 : NULL;
        case 80: //hclr HCLR ,, Struct
            return HCLR.IsLoaded() ? &HCLR->value80 : NULL;
        case 81: //hclr_p HCLR ,, Struct
            *FieldValues = HCLR.IsLoaded() ? &HCLR->value81[0] : NULL;
            return NULL;
        case 82: //znam Combat Style
            return ZNAM.IsLoaded() ? &ZNAM->value82 : NULL;
        case 83: //nam4 Impact Material Type
            return NAM4.IsLoaded() ? &NAM4->value83 : NULL;
        case 84: //fggs_p FaceGen Geometry-Symmetric
            *FieldValues = (FGGS.IsLoaded()) ? FGGS->FGGS.value : NULL;
            return NULL;
        case 85: //fgga_p FaceGen Geometry-Asymmetric
            *FieldValues = (FGGS.IsLoaded()) ? FGGS->FGGA.value : NULL;
            return NULL;
        case 86: //fgts_p FaceGen Texture-Symmetric
            *FieldValues = (FGGS.IsLoaded()) ? FGGS->FGTS.value : NULL;
            return NULL;
        case 87: //nam5 Unknown
            return NAM5.IsLoaded() ? &NAM5->value87 : NULL;
        case 88: //nam6 Height
            return NAM6.IsLoaded() ? &NAM6->value88 : NULL;
        case 89: //nam7 Weight
            return NAM7.IsLoaded() ? &NAM7->value89 : NULL;
        default:
            return NULL;
        }
    }

bool NPC_Record::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 10: //full Name
            FULLActor.Copy((STRING)FieldValue);
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
        case 18: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value18 = *(UINT32 *)FieldValue;
            break;
        case 19: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value19 = *(UINT16 *)FieldValue;
            break;
        case 20: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value20 = *(UINT16 *)FieldValue;
            break;
        case 21: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value21 = *(SINT16 *)FieldValue;
            break;
        case 22: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value22 = *(UINT16 *)FieldValue;
            break;
        case 23: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value23 = *(UINT16 *)FieldValue;
            break;
        case 24: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value24 = *(UINT16 *)FieldValue;
            break;
        case 25: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value25 = *(FLOAT32 *)FieldValue;
            break;
        case 26: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value26 = *(SINT16 *)FieldValue;
            break;
        case 27: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value27 = *(UINT16 *)FieldValue;
            break;
        case 28: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value28 = *(FORMID *)FieldValue;
            return true;
        case 29: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value29 = *(UINT8 *)FieldValue;
            break;
        case 30: //snam_p SNAM ,, Struct
            if(ArraySize != 3)
                break;
            SNAM.Load();
            SNAM->value30[0] = ((UINT8 *)FieldValue)[0];
            SNAM->value30[1] = ((UINT8 *)FieldValue)[1];
            SNAM->value30[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 31: //inam Death item
            INAM.Load();
            INAM->value31 = *(FORMID *)FieldValue;
            return true;
        case 32: //vtck Voice
            VTCK.Load();
            VTCK->value32 = *(FORMID *)FieldValue;
            return true;
        case 33: //tplt Template
            TPLT.Load();
            TPLT->value33 = *(FORMID *)FieldValue;
            return true;
        case 34: //rnam Race
            RNAM.Load();
            RNAM->value34 = *(FORMID *)FieldValue;
            return true;
        case 35: //splo Actor Effect
            SPLOs.Load();
            SPLOs->value35 = *(FORMID *)FieldValue;
            return true;
        case 36: //eitm Unarmed Attack Effect
            EITM.Load();
            EITM->value36 = *(FORMID *)FieldValue;
            return true;
        case 37: //eamt Unarmed Attack Animation
            EAMT.Load();
            EAMT->value37 = *(UINT16 *)FieldValue;
            break;
        case 38: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value38 = *(SINT32 *)FieldValue;
            break;
        case 39: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value39 = *(UINT8 *)FieldValue;
            break;
        case 40: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value40 = *(UINT8 *)FieldValue;
            break;
        case 41: //dest_p Header
            if(ArraySize != 2)
                break;
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value41[0] = ((UINT8 *)FieldValue)[0];
            DEST->DEST->value41[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 42: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value42 = *(UINT8 *)FieldValue;
            break;
        case 43: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value43 = *(UINT8 *)FieldValue;
            break;
        case 44: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value44 = *(UINT8 *)FieldValue;
            break;
        case 45: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value45 = *(UINT8 *)FieldValue;
            break;
        case 46: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value46 = *(SINT32 *)FieldValue;
            break;
        case 47: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value47 = *(FORMID *)FieldValue;
            return true;
        case 48: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value48 = *(FORMID *)FieldValue;
            return true;
        case 49: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value49 = *(SINT32 *)FieldValue;
            break;
        case 50: //dmdl Model Filename
            DEST.Load();
            DEST->DMDL.Copy((STRING)FieldValue);
            break;
        case 51: //dmdt_p Texture Files Hashes
            DEST.Load();
            DEST->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 52: //scri Script
            SCRIActor.Load();
            SCRIActor->value52 = *(FORMID *)FieldValue;
            return true;
        case 53: //cnto Item
            CNTO.Load();
            CNTO->value53 = *(FORMID *)FieldValue;
            return true;
        case 54: //cnto Item
            CNTO.Load();
            CNTO->value54 = *(SINT32 *)FieldValue;
            break;
        case 55: //aidt AI Data
            AIDT.Load();
            AIDT->value55 = *(UINT8 *)FieldValue;
            break;
        case 56: //aidt AI Data
            AIDT.Load();
            AIDT->value56 = *(UINT8 *)FieldValue;
            break;
        case 57: //aidt AI Data
            AIDT.Load();
            AIDT->value57 = *(UINT8 *)FieldValue;
            break;
        case 58: //aidt AI Data
            AIDT.Load();
            AIDT->value58 = *(UINT8 *)FieldValue;
            break;
        case 59: //aidt AI Data
            AIDT.Load();
            AIDT->value59 = *(UINT8 *)FieldValue;
            break;
        case 60: //aidt_p AI Data
            if(ArraySize != 3)
                break;
            AIDT.Load();
            AIDT->value60[0] = ((UINT8 *)FieldValue)[0];
            AIDT->value60[1] = ((UINT8 *)FieldValue)[1];
            AIDT->value60[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 61: //aidt AI Data
            AIDT.Load();
            AIDT->value61 = *(UINT32 *)FieldValue;
            break;
        case 62: //aidt AI Data
            AIDT.Load();
            AIDT->value62 = *(SINT8 *)FieldValue;
            break;
        case 63: //aidt AI Data
            AIDT.Load();
            AIDT->value63 = *(UINT8 *)FieldValue;
            break;
        case 64: //aidt AI Data
            AIDT.Load();
            AIDT->value64 = *(SINT8 *)FieldValue;
            break;
        case 65: //aidt AI Data
            AIDT.Load();
            AIDT->value65 = *(UINT8 *)FieldValue;
            break;
        case 66: //aidt AI Data
            AIDT.Load();
            AIDT->value66 = *(SINT32 *)FieldValue;
            break;
        case 67: //pkid Package
            PKID.Load();
            PKID->value67 = *(FORMID *)FieldValue;
            return true;
        case 68: //cnam Class
            CNAM.Load();
            CNAM->value68 = *(FORMID *)FieldValue;
            return true;
        case 69: //data DATA ,, Struct
            DATA.Load();
            DATA->value69 = *(SINT32 *)FieldValue;
            break;
        case 70: //data DATA ,, Struct
            DATA.Load();
            DATA->value70 = *(UINT8 *)FieldValue;
            break;
        case 71: //data_p DATA ,, Struct
            if(ArraySize != 0)
                break;
            DATA.Load();
            break;
        case 72: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value72 = *(UINT8 *)FieldValue;
            break;
        case 73: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value73 = *(UINT8 *)FieldValue;
            break;
        case 74: //pnam Head Part
            PNAM.Load();
            PNAM->value74 = *(FORMID *)FieldValue;
            return true;
        case 75: //hnam Hair
            HNAM.Load();
            HNAM->value75 = *(FORMID *)FieldValue;
            return true;
        case 76: //lnam Hair length
            LNAM.Load();
            LNAM->value76 = *(FLOAT32 *)FieldValue;
            break;
        case 77: //enam Eyes
            ENAM.Load();
            ENAM->value77 = *(FORMID *)FieldValue;
            return true;
        case 78: //hclr HCLR ,, Struct
            HCLR.Load();
            HCLR->value78 = *(UINT8 *)FieldValue;
            break;
        case 79: //hclr HCLR ,, Struct
            HCLR.Load();
            HCLR->value79 = *(UINT8 *)FieldValue;
            break;
        case 80: //hclr HCLR ,, Struct
            HCLR.Load();
            HCLR->value80 = *(UINT8 *)FieldValue;
            break;
        case 81: //hclr_p HCLR ,, Struct
            if(ArraySize != 1)
                break;
            HCLR.Load();
            HCLR->value81[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 82: //znam Combat Style
            ZNAM.Load();
            ZNAM->value82 = *(FORMID *)FieldValue;
            return true;
        case 83: //nam4 Impact Material Type
            NAM4.Load();
            NAM4->value83 = *(UINT32 *)FieldValue;
            break;
        case 84: //fggs_p FaceGen Geometry-Symmetric
            FGGS.Load();
            FGGS->FGGS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 85: //fgga_p FaceGen Geometry-Asymmetric
            FGGS.Load();
            FGGS->FGGA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 86: //fgts_p FaceGen Texture-Symmetric
            FGGS.Load();
            FGGS->FGTS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 87: //nam5 Unknown
            NAM5.Load();
            NAM5->value87 = *(UINT16 *)FieldValue;
            break;
        case 88: //nam6 Height
            NAM6.Load();
            NAM6->value88 = *(FLOAT32 *)FieldValue;
            break;
        case 89: //nam7 Weight
            NAM7.Load();
            NAM7->value89 = *(FLOAT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void NPC_Record::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 8: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 9: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 10: //full Name
            FULLActor.Unload();
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
        case 18: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 19: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 20: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 21: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 22: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 23: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 24: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 25: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 26: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 27: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 28: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        case 29: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        case 30: //snam_p SNAM ,, Struct
            SNAM.Unload();
            return;
        case 31: //inam Death item
            INAM.Unload();
            return;
        case 32: //vtck Voice
            VTCK.Unload();
            return;
        case 33: //tplt Template
            TPLT.Unload();
            return;
        case 34: //rnam Race
            RNAM.Unload();
            return;
        case 35: //splo Actor Effect
            SPLOs.Unload();
            return;
        case 36: //eitm Unarmed Attack Effect
            EITM.Unload();
            return;
        case 37: //eamt Unarmed Attack Animation
            EAMT.Unload();
            return;
        case 38: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 39: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 40: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 41: //dest_p Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 42: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 43: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 44: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 45: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 46: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 47: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 48: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 49: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 50: //dmdl Model Filename
            if(DEST.IsLoaded())
                DEST->DMDL.Unload();
            return;
        case 51: //dmdt_p Texture Files Hashes
            if(DEST.IsLoaded())
                DEST->DMDT.Unload();
            return;
        case 52: //scri Script
            SCRIActor.Unload();
            return;
        case 53: //cnto Item
            CNTO.Unload();
            return;
        case 54: //cnto Item
            CNTO.Unload();
            return;
        case 55: //aidt AI Data
            AIDT.Unload();
            return;
        case 56: //aidt AI Data
            AIDT.Unload();
            return;
        case 57: //aidt AI Data
            AIDT.Unload();
            return;
        case 58: //aidt AI Data
            AIDT.Unload();
            return;
        case 59: //aidt AI Data
            AIDT.Unload();
            return;
        case 60: //aidt_p AI Data
            AIDT.Unload();
            return;
        case 61: //aidt AI Data
            AIDT.Unload();
            return;
        case 62: //aidt AI Data
            AIDT.Unload();
            return;
        case 63: //aidt AI Data
            AIDT.Unload();
            return;
        case 64: //aidt AI Data
            AIDT.Unload();
            return;
        case 65: //aidt AI Data
            AIDT.Unload();
            return;
        case 66: //aidt AI Data
            AIDT.Unload();
            return;
        case 67: //pkid Package
            PKID.Unload();
            return;
        case 68: //cnam Class
            CNAM.Unload();
            return;
        case 69: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 70: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 71: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 72: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 73: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 74: //pnam Head Part
            PNAM.Unload();
            return;
        case 75: //hnam Hair
            HNAM.Unload();
            return;
        case 76: //lnam Hair length
            LNAM.Unload();
            return;
        case 77: //enam Eyes
            ENAM.Unload();
            return;
        case 78: //hclr HCLR ,, Struct
            HCLR.Unload();
            return;
        case 79: //hclr HCLR ,, Struct
            HCLR.Unload();
            return;
        case 80: //hclr HCLR ,, Struct
            HCLR.Unload();
            return;
        case 81: //hclr_p HCLR ,, Struct
            HCLR.Unload();
            return;
        case 82: //znam Combat Style
            ZNAM.Unload();
            return;
        case 83: //nam4 Impact Material Type
            NAM4.Unload();
            return;
        case 84: //fggs_p FaceGen Geometry-Symmetric
            if(FGGS.IsLoaded())
                FGGS->FGGS.Unload();
            return;
        case 85: //fgga_p FaceGen Geometry-Asymmetric
            if(FGGS.IsLoaded())
                FGGS->FGGA.Unload();
            return;
        case 86: //fgts_p FaceGen Texture-Symmetric
            if(FGGS.IsLoaded())
                FGGS->FGTS.Unload();
            return;
        case 87: //nam5 Unknown
            NAM5.Unload();
            return;
        case 88: //nam6 Height
            NAM6.Unload();
            return;
        case 89: //nam7 Weight
            NAM7.Unload();
            return;
        default:
            return;
        }
    }
}