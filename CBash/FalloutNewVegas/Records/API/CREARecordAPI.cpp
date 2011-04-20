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
#include "..\CREARecord.h"

namespace FNV
{
UINT32 CREARecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 18: //splo Actor Effect
            return FORMID_FIELD;
        case 19: //eitm Unarmed Attack Effect
            return FORMID_FIELD;
        case 20: //eamt Unarmed Attack Animation
            return UINT16_FIELD;
        case 21: //nifz Model List
            return UNPARSED_FIELD;
        case 22: //nift_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NIFT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 23: //acbs ACBS ,, Struct
            return UINT32_FIELD;
        case 24: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 25: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 26: //acbs ACBS ,, Struct
            return SINT16_FIELD;
        case 27: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 28: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 29: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 30: //acbs ACBS ,, Struct
            return FLOAT32_FIELD;
        case 31: //acbs ACBS ,, Struct
            return SINT16_FIELD;
        case 32: //acbs ACBS ,, Struct
            return UINT16_FIELD;
        case 33: //snam SNAM ,, Struct
            return FORMID_FIELD;
        case 34: //snam SNAM ,, Struct
            return UINT8_FIELD;
        case 35: //snam_p SNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 36: //inam Death item
            return FORMID_FIELD;
        case 37: //vtck Voice
            return FORMID_FIELD;
        case 38: //tplt Template
            return FORMID_FIELD;
        case 39: //dest Header
            return SINT32_FIELD;
        case 40: //dest Header
            return UINT8_FIELD;
        case 41: //dest Header
            return UINT8_FIELD;
        case 42: //dest_p Header
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 43: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 44: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 45: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 46: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 47: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 48: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 49: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 50: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 51: //dmdl Model Filename
            return ISTRING_FIELD;
        case 52: //dmdt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DMDT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 53: //scri Script
            return FORMID_FIELD;
        case 54: //cnto Item
            return FORMID_FIELD;
        case 55: //cnto Item
            return SINT32_FIELD;
        case 56: //aidt AI Data
            return UINT8_FIELD;
        case 57: //aidt AI Data
            return UINT8_FIELD;
        case 58: //aidt AI Data
            return UINT8_FIELD;
        case 59: //aidt AI Data
            return UINT8_FIELD;
        case 60: //aidt AI Data
            return UINT8_FIELD;
        case 61: //aidt_p AI Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 62: //aidt AI Data
            return UINT32_FIELD;
        case 63: //aidt AI Data
            return SINT8_FIELD;
        case 64: //aidt AI Data
            return UINT8_FIELD;
        case 65: //aidt AI Data
            return SINT8_FIELD;
        case 66: //aidt AI Data
            return UINT8_FIELD;
        case 67: //aidt AI Data
            return SINT32_FIELD;
        case 68: //pkid Package
            return FORMID_FIELD;
        case 69: //kffz Animations
            return UNPARSED_FIELD;
        case 70: //data DATA ,, Struct
            return UINT8_FIELD;
        case 71: //data DATA ,, Struct
            return UINT8_FIELD;
        case 72: //data DATA ,, Struct
            return UINT8_FIELD;
        case 73: //data DATA ,, Struct
            return UINT8_FIELD;
        case 74: //data DATA ,, Struct
            return SINT16_FIELD;
        case 75: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 76: //data DATA ,, Struct
            return SINT16_FIELD;
        case 77: //data DATA ,, Struct
            return UINT8_FIELD;
        case 78: //rnam Attack reach
            return UINT8_FIELD;
        case 79: //znam Combat Style
            return FORMID_FIELD;
        case 80: //pnam Body Part Data
            return FORMID_FIELD;
        case 81: //tnam Turning Speed
            return FLOAT32_FIELD;
        case 82: //bnam Base Scale
            return FLOAT32_FIELD;
        case 83: //wnam Foot Weight
            return FLOAT32_FIELD;
        case 84: //nam4 Impact Material Type
            return UINT32_FIELD;
        case 85: //nam5 Sound Level
            return UINT32_FIELD;
        case 86: //cscr Inherits Sounds from
            return FORMID_FIELD;
        case 87: //csdt Type
            return UINT32_FIELD;
        case 88: //csdi Sound
            return FORMID_FIELD;
        case 89: //csdc Sound Chance
            return UINT8_FIELD;
        case 90: //cnam Impact Dataset
            return FORMID_FIELD;
        case 91: //lnam Melee Weapon List
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CREARecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 18: //splo Actor Effect
            return SPLOs.IsLoaded() ? &SPLOs->value18 : NULL;
        case 19: //eitm Unarmed Attack Effect
            return EITM.IsLoaded() ? &EITM->value19 : NULL;
        case 20: //eamt Unarmed Attack Animation
            return EAMT.IsLoaded() ? &EAMT->value20 : NULL;
        case 21: //nifz Model List
            return UNPARSEDGET_FIELD21;
        case 22: //nift_p Texture Files Hashes
            *FieldValues = NIFT.value;
            return NULL;
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
        case 28: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value28 : NULL;
        case 29: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value29 : NULL;
        case 30: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value30 : NULL;
        case 31: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value31 : NULL;
        case 32: //acbs ACBS ,, Struct
            return ACBS.IsLoaded() ? &ACBS->value32 : NULL;
        case 33: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value33 : NULL;
        case 34: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value34 : NULL;
        case 35: //snam_p SNAM ,, Struct
            *FieldValues = SNAM.IsLoaded() ? &SNAM->value35[0] : NULL;
            return NULL;
        case 36: //inam Death item
            return INAM.IsLoaded() ? &INAM->value36 : NULL;
        case 37: //vtck Voice
            return VTCK.IsLoaded() ? &VTCK->value37 : NULL;
        case 38: //tplt Template
            return TPLT.IsLoaded() ? &TPLT->value38 : NULL;
        case 39: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value39 : NULL;
        case 40: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value40 : NULL;
        case 41: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value41 : NULL;
        case 42: //dest_p Header
            *FieldValues = DEST.IsLoaded() ? &DEST->DEST->value42[0] : NULL;
            return NULL;
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
        case 50: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value50 : NULL;
        case 51: //dmdl Model Filename
            return DEST.IsLoaded() ? DEST->DMDL.value : NULL;
        case 52: //dmdt_p Texture Files Hashes
            *FieldValues = (DEST.IsLoaded()) ? DEST->DMDT.value : NULL;
            return NULL;
        case 53: //scri Script
            return SCRIActor.IsLoaded() ? &SCRIActor->value53 : NULL;
        case 54: //cnto Item
            return CNTO.IsLoaded() ? &CNTO->value54 : NULL;
        case 55: //cnto Item
            return CNTO.IsLoaded() ? &CNTO->value55 : NULL;
        case 56: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value56 : NULL;
        case 57: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value57 : NULL;
        case 58: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value58 : NULL;
        case 59: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value59 : NULL;
        case 60: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value60 : NULL;
        case 61: //aidt_p AI Data
            *FieldValues = AIDT.IsLoaded() ? &AIDT->value61[0] : NULL;
            return NULL;
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
        case 67: //aidt AI Data
            return AIDT.IsLoaded() ? &AIDT->value67 : NULL;
        case 68: //pkid Package
            return PKID.IsLoaded() ? &PKID->value68 : NULL;
        case 69: //kffz Animations
            return UNPARSEDGET_FIELD69;
        case 70: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value70 : NULL;
        case 71: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value71 : NULL;
        case 72: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value72 : NULL;
        case 73: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value73 : NULL;
        case 74: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value74 : NULL;
        case 75: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value75[0] : NULL;
            return NULL;
        case 76: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value76 : NULL;
        case 77: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value77 : NULL;
        case 78: //rnam Attack reach
            return RNAM.IsLoaded() ? &RNAM->value78 : NULL;
        case 79: //znam Combat Style
            return ZNAM.IsLoaded() ? &ZNAM->value79 : NULL;
        case 80: //pnam Body Part Data
            return PNAM.IsLoaded() ? &PNAM->value80 : NULL;
        case 81: //tnam Turning Speed
            return TNAM.IsLoaded() ? &TNAM->value81 : NULL;
        case 82: //bnam Base Scale
            return BNAM.IsLoaded() ? &BNAM->value82 : NULL;
        case 83: //wnam Foot Weight
            return WNAM.IsLoaded() ? &WNAM->value83 : NULL;
        case 84: //nam4 Impact Material Type
            return NAM4.IsLoaded() ? &NAM4->value84 : NULL;
        case 85: //nam5 Sound Level
            return NAM5.IsLoaded() ? &NAM5->value85 : NULL;
        case 86: //cscr Inherits Sounds from
            return CSCR.IsLoaded() ? &CSCR->value86 : NULL;
        case 87: //csdt Type
            return CSDT.IsLoaded() ? &CSDT->CSDT->value87 : NULL;
        case 88: //csdi Sound
            return CSDT.IsLoaded() ? &CSDT->CSDI->value88 : NULL;
        case 89: //csdc Sound Chance
            return CSDT.IsLoaded() ? &CSDT->CSDC->value89 : NULL;
        case 90: //cnam Impact Dataset
            return CNAM.IsLoaded() ? &CNAM->value90 : NULL;
        case 91: //lnam Melee Weapon List
            return LNAM.IsLoaded() ? &LNAM->value91 : NULL;
        default:
            return NULL;
        }
    }

bool CREARecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 18: //splo Actor Effect
            SPLOs.Load();
            SPLOs->value18 = *(FORMID *)FieldValue;
            return true;
        case 19: //eitm Unarmed Attack Effect
            EITM.Load();
            EITM->value19 = *(FORMID *)FieldValue;
            return true;
        case 20: //eamt Unarmed Attack Animation
            EAMT.Load();
            EAMT->value20 = *(UINT16 *)FieldValue;
            break;
        case 21: //nifz Model List
            return UNPARSEDGET_FIELD21;
        case 22: //nift_p Texture Files Hashes
            NIFT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 23: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value23 = *(UINT32 *)FieldValue;
            break;
        case 24: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value24 = *(UINT16 *)FieldValue;
            break;
        case 25: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value25 = *(UINT16 *)FieldValue;
            break;
        case 26: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value26 = *(SINT16 *)FieldValue;
            break;
        case 27: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value27 = *(UINT16 *)FieldValue;
            break;
        case 28: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value28 = *(UINT16 *)FieldValue;
            break;
        case 29: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value29 = *(UINT16 *)FieldValue;
            break;
        case 30: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value30 = *(FLOAT32 *)FieldValue;
            break;
        case 31: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value31 = *(SINT16 *)FieldValue;
            break;
        case 32: //acbs ACBS ,, Struct
            ACBS.Load();
            ACBS->value32 = *(UINT16 *)FieldValue;
            break;
        case 33: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value33 = *(FORMID *)FieldValue;
            return true;
        case 34: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value34 = *(UINT8 *)FieldValue;
            break;
        case 35: //snam_p SNAM ,, Struct
            if(ArraySize != 3)
                break;
            SNAM.Load();
            SNAM->value35[0] = ((UINT8 *)FieldValue)[0];
            SNAM->value35[1] = ((UINT8 *)FieldValue)[1];
            SNAM->value35[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 36: //inam Death item
            INAM.Load();
            INAM->value36 = *(FORMID *)FieldValue;
            return true;
        case 37: //vtck Voice
            VTCK.Load();
            VTCK->value37 = *(FORMID *)FieldValue;
            return true;
        case 38: //tplt Template
            TPLT.Load();
            TPLT->value38 = *(FORMID *)FieldValue;
            return true;
        case 39: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value39 = *(SINT32 *)FieldValue;
            break;
        case 40: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value40 = *(UINT8 *)FieldValue;
            break;
        case 41: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value41 = *(UINT8 *)FieldValue;
            break;
        case 42: //dest_p Header
            if(ArraySize != 2)
                break;
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value42[0] = ((UINT8 *)FieldValue)[0];
            DEST->DEST->value42[1] = ((UINT8 *)FieldValue)[1];
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
            DEST->DSTD->value46 = *(UINT8 *)FieldValue;
            break;
        case 47: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value47 = *(SINT32 *)FieldValue;
            break;
        case 48: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value48 = *(FORMID *)FieldValue;
            return true;
        case 49: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value49 = *(FORMID *)FieldValue;
            return true;
        case 50: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value50 = *(SINT32 *)FieldValue;
            break;
        case 51: //dmdl Model Filename
            DEST.Load();
            DEST->DMDL.Copy((STRING)FieldValue);
            break;
        case 52: //dmdt_p Texture Files Hashes
            DEST.Load();
            DEST->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 53: //scri Script
            SCRIActor.Load();
            SCRIActor->value53 = *(FORMID *)FieldValue;
            return true;
        case 54: //cnto Item
            CNTO.Load();
            CNTO->value54 = *(FORMID *)FieldValue;
            return true;
        case 55: //cnto Item
            CNTO.Load();
            CNTO->value55 = *(SINT32 *)FieldValue;
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
        case 60: //aidt AI Data
            AIDT.Load();
            AIDT->value60 = *(UINT8 *)FieldValue;
            break;
        case 61: //aidt_p AI Data
            if(ArraySize != 3)
                break;
            AIDT.Load();
            AIDT->value61[0] = ((UINT8 *)FieldValue)[0];
            AIDT->value61[1] = ((UINT8 *)FieldValue)[1];
            AIDT->value61[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 62: //aidt AI Data
            AIDT.Load();
            AIDT->value62 = *(UINT32 *)FieldValue;
            break;
        case 63: //aidt AI Data
            AIDT.Load();
            AIDT->value63 = *(SINT8 *)FieldValue;
            break;
        case 64: //aidt AI Data
            AIDT.Load();
            AIDT->value64 = *(UINT8 *)FieldValue;
            break;
        case 65: //aidt AI Data
            AIDT.Load();
            AIDT->value65 = *(SINT8 *)FieldValue;
            break;
        case 66: //aidt AI Data
            AIDT.Load();
            AIDT->value66 = *(UINT8 *)FieldValue;
            break;
        case 67: //aidt AI Data
            AIDT.Load();
            AIDT->value67 = *(SINT32 *)FieldValue;
            break;
        case 68: //pkid Package
            PKID.Load();
            PKID->value68 = *(FORMID *)FieldValue;
            return true;
        case 69: //kffz Animations
            return UNPARSEDGET_FIELD69;
        case 70: //data DATA ,, Struct
            DATA.Load();
            DATA->value70 = *(UINT8 *)FieldValue;
            break;
        case 71: //data DATA ,, Struct
            DATA.Load();
            DATA->value71 = *(UINT8 *)FieldValue;
            break;
        case 72: //data DATA ,, Struct
            DATA.Load();
            DATA->value72 = *(UINT8 *)FieldValue;
            break;
        case 73: //data DATA ,, Struct
            DATA.Load();
            DATA->value73 = *(UINT8 *)FieldValue;
            break;
        case 74: //data DATA ,, Struct
            DATA.Load();
            DATA->value74 = *(SINT16 *)FieldValue;
            break;
        case 75: //data_p DATA ,, Struct
            if(ArraySize != 2)
                break;
            DATA.Load();
            DATA->value75[0] = ((UINT8 *)FieldValue)[0];
            DATA->value75[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 76: //data DATA ,, Struct
            DATA.Load();
            DATA->value76 = *(SINT16 *)FieldValue;
            break;
        case 77: //data DATA ,, Struct
            DATA.Load();
            DATA->value77 = *(UINT8 *)FieldValue;
            break;
        case 78: //rnam Attack reach
            RNAM.Load();
            RNAM->value78 = *(UINT8 *)FieldValue;
            break;
        case 79: //znam Combat Style
            ZNAM.Load();
            ZNAM->value79 = *(FORMID *)FieldValue;
            return true;
        case 80: //pnam Body Part Data
            PNAM.Load();
            PNAM->value80 = *(FORMID *)FieldValue;
            return true;
        case 81: //tnam Turning Speed
            TNAM.Load();
            TNAM->value81 = *(FLOAT32 *)FieldValue;
            break;
        case 82: //bnam Base Scale
            BNAM.Load();
            BNAM->value82 = *(FLOAT32 *)FieldValue;
            break;
        case 83: //wnam Foot Weight
            WNAM.Load();
            WNAM->value83 = *(FLOAT32 *)FieldValue;
            break;
        case 84: //nam4 Impact Material Type
            NAM4.Load();
            NAM4->value84 = *(UINT32 *)FieldValue;
            break;
        case 85: //nam5 Sound Level
            NAM5.Load();
            NAM5->value85 = *(UINT32 *)FieldValue;
            break;
        case 86: //cscr Inherits Sounds from
            CSCR.Load();
            CSCR->value86 = *(FORMID *)FieldValue;
            return true;
        case 87: //csdt Type
            CSDT.Load();
            CSDT->CSDT.Load();
            CSDT->CSDT->value87 = *(UINT32 *)FieldValue;
            break;
        case 88: //csdi Sound
            CSDT.Load();
            CSDT->CSDI.Load();
            CSDT->CSDI->value88 = *(FORMID *)FieldValue;
            return true;
        case 89: //csdc Sound Chance
            CSDT.Load();
            CSDT->CSDC.Load();
            CSDT->CSDC->value89 = *(UINT8 *)FieldValue;
            break;
        case 90: //cnam Impact Dataset
            CNAM.Load();
            CNAM->value90 = *(FORMID *)FieldValue;
            return true;
        case 91: //lnam Melee Weapon List
            LNAM.Load();
            LNAM->value91 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void CREARecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 18: //splo Actor Effect
            SPLOs.Unload();
            return;
        case 19: //eitm Unarmed Attack Effect
            EITM.Unload();
            return;
        case 20: //eamt Unarmed Attack Animation
            EAMT.Unload();
            return;
        case 21: //nifz Model List
            return UNPARSEDDEL_FIELD21;
        case 22: //nift_p Texture Files Hashes
            NIFT.Unload();
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
        case 28: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 29: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 30: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 31: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 32: //acbs ACBS ,, Struct
            ACBS.Unload();
            return;
        case 33: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        case 34: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        case 35: //snam_p SNAM ,, Struct
            SNAM.Unload();
            return;
        case 36: //inam Death item
            INAM.Unload();
            return;
        case 37: //vtck Voice
            VTCK.Unload();
            return;
        case 38: //tplt Template
            TPLT.Unload();
            return;
        case 39: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 40: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 41: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 42: //dest_p Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
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
        case 50: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 51: //dmdl Model Filename
            if(DEST.IsLoaded())
                DEST->DMDL.Unload();
            return;
        case 52: //dmdt_p Texture Files Hashes
            if(DEST.IsLoaded())
                DEST->DMDT.Unload();
            return;
        case 53: //scri Script
            SCRIActor.Unload();
            return;
        case 54: //cnto Item
            CNTO.Unload();
            return;
        case 55: //cnto Item
            CNTO.Unload();
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
        case 60: //aidt AI Data
            AIDT.Unload();
            return;
        case 61: //aidt_p AI Data
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
        case 67: //aidt AI Data
            AIDT.Unload();
            return;
        case 68: //pkid Package
            PKID.Unload();
            return;
        case 69: //kffz Animations
            return UNPARSEDDEL_FIELD69;
        case 70: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 71: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 72: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 73: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 74: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 75: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 76: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 77: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 78: //rnam Attack reach
            RNAM.Unload();
            return;
        case 79: //znam Combat Style
            ZNAM.Unload();
            return;
        case 80: //pnam Body Part Data
            PNAM.Unload();
            return;
        case 81: //tnam Turning Speed
            TNAM.Unload();
            return;
        case 82: //bnam Base Scale
            BNAM.Unload();
            return;
        case 83: //wnam Foot Weight
            WNAM.Unload();
            return;
        case 84: //nam4 Impact Material Type
            NAM4.Unload();
            return;
        case 85: //nam5 Sound Level
            NAM5.Unload();
            return;
        case 86: //cscr Inherits Sounds from
            CSCR.Unload();
            return;
        case 87: //csdt Type
            if(CSDT.IsLoaded())
                CSDT->CSDT.Unload();
            return;
        case 88: //csdi Sound
            if(CSDT.IsLoaded())
                CSDT->CSDI.Unload();
            return;
        case 89: //csdc Sound Chance
            if(CSDT.IsLoaded())
                CSDT->CSDC.Unload();
            return;
        case 90: //cnam Impact Dataset
            CNAM.Unload();
            return;
        case 91: //lnam Melee Weapon List
            LNAM.Unload();
            return;
        default:
            return;
        }
    }
}