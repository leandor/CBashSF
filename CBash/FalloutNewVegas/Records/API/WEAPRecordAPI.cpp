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
#include "..\WEAPRecord.h"

namespace FNV
{
UINT32 WEAPRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 18: //icon Large Icon Filename
            return ISTRING_FIELD;
        case 19: //mico Small Icon Filename
            return ISTRING_FIELD;
        case 20: //scri Script
            return FORMID_FIELD;
        case 21: //eitm Object Effect
            return FORMID_FIELD;
        case 22: //eamt Enchantment Charge Amount
            return SINT16_FIELD;
        case 23: //nam0 Ammo
            return FORMID_FIELD;
        case 24: //dest Header
            return SINT32_FIELD;
        case 25: //dest Header
            return UINT8_FIELD;
        case 26: //dest Header
            return UINT8_FIELD;
        case 27: //dest_p Header
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 28: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 29: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 30: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 31: //dstd Destruction Stage Data
            return UINT8_FIELD;
        case 32: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 33: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 34: //dstd Destruction Stage Data
            return FORMID_FIELD;
        case 35: //dstd Destruction Stage Data
            return SINT32_FIELD;
        case 36: //dmdl Model Filename
            return ISTRING_FIELD;
        case 37: //dmdt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DMDT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 38: //repl Repair List
            return FORMID_FIELD;
        case 39: //etyp Equipment Type
            return SINT32_FIELD;
        case 40: //bipl Biped Model List
            return FORMID_FIELD;
        case 41: //ynam Sound - Pick Up
            return FORMID_FIELD;
        case 42: //znam Sound - Drop
            return FORMID_FIELD;
        case 43: //mod2 Model Filename
            return ISTRING_FIELD;
        case 44: //mo2t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO2T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 45: //mo2s Alternate Texture
            return ISTRING_FIELD;
        case 46: //mo2s Alternate Texture
            return FORMID_FIELD;
        case 47: //mo2s Alternate Texture
            return SINT32_FIELD;
        case 48: //mod3 Model Filename
            return ISTRING_FIELD;
        case 49: //mo3t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO3T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 50: //mo3s Alternate Texture
            return ISTRING_FIELD;
        case 51: //mo3s Alternate Texture
            return FORMID_FIELD;
        case 52: //mo3s Alternate Texture
            return SINT32_FIELD;
        case 53: //efsd Scope Effect
            return FORMID_FIELD;
        case 54: //mod4 Model Filename
            return ISTRING_FIELD;
        case 55: //mo4t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO4T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 56: //mo4s Alternate Texture
            return ISTRING_FIELD;
        case 57: //mo4s Alternate Texture
            return FORMID_FIELD;
        case 58: //mo4s Alternate Texture
            return SINT32_FIELD;
        case 59: //vanm VATS Attack Name
            return ISTRING_FIELD;
        case 60: //nnam Embedded Weapon Node
            return ISTRING_FIELD;
        case 61: //mwd1 Mod 1
            return ISTRING_FIELD;
        case 62: //mwd2 Mod 2
            return ISTRING_FIELD;
        case 63: //mwd3 Mod 1 and 2
            return ISTRING_FIELD;
        case 64: //mwd4 Mod 3
            return ISTRING_FIELD;
        case 65: //mwd5 Mod 1 and 3
            return ISTRING_FIELD;
        case 66: //mwd6 Mod 2 and 3
            return ISTRING_FIELD;
        case 67: //mwd7 Mod 1, 2 and 3
            return ISTRING_FIELD;
        case 68: //inam Impact DataSet
            return FORMID_FIELD;
        case 69: //wnam 1st Person Model
            return FORMID_FIELD;
        case 70: //wnm1 Mod 1
            return FORMID_FIELD;
        case 71: //wnm2 Mod 2
            return FORMID_FIELD;
        case 72: //wnm3 Mod 1 and 2
            return FORMID_FIELD;
        case 73: //wnm4 Mod 3
            return FORMID_FIELD;
        case 74: //wnm5 Mod 1 and 3
            return FORMID_FIELD;
        case 75: //wnm6 Mod 2 and 3
            return FORMID_FIELD;
        case 76: //wnm7 Mod 1, 2 and 3
            return FORMID_FIELD;
        case 77: //wmi1 Mod 1
            return FORMID_FIELD;
        case 78: //wmi2 Mod 2
            return FORMID_FIELD;
        case 79: //wmi3 Mod 3
            return FORMID_FIELD;
        case 80: //snam Sound - Gun - Shoot Dist
            return FORMID_FIELD;
        case 81: //xnam Sound - Gun - Shoot 2D
            return FORMID_FIELD;
        case 82: //nam7 Sound - Gun - Shoot 3D Looping
            return FORMID_FIELD;
        case 83: //tnam Sound - Melee - Swing / Gun - No Ammo
            return FORMID_FIELD;
        case 84: //nam6 Sound - Block
            return FORMID_FIELD;
        case 85: //unam Sound - Idle
            return FORMID_FIELD;
        case 86: //nam9 Sound - Equip
            return FORMID_FIELD;
        case 87: //nam8 Sound - Unequip
            return FORMID_FIELD;
        case 88: //wms1 Sound - Mod 1 - Shoot Dist
            return FORMID_FIELD;
        case 89: //wms2 Sound - Mod 1 - Shoot 2D
            return FORMID_FIELD;
        case 90: //data DATA ,, Struct
            return SINT32_FIELD;
        case 91: //data DATA ,, Struct
            return SINT32_FIELD;
        case 92: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 93: //data DATA ,, Struct
            return SINT16_FIELD;
        case 94: //data DATA ,, Struct
            return UINT8_FIELD;
        case 95: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 96: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 97: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 98: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 99: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 100: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 101: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 102: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 103: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 104: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 105: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 106: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 107: //dnam DNAM ,, Struct
            return FORMID_FIELD;
        case 108: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 109: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 110: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 111: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 112: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 113: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 114: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 115: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 116: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 117: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 118: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 119: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 120: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 121: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 122: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 123: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 124: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 125: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 126: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 127: //dnam DNAM ,, Struct
            return UNPARSED_FIELD;
        case 128: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 129: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 130: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 131: //dnam DNAM ,, Struct
            return UNPARSED_FIELD;
        case 132: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 133: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 134: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 135: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 136: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 137: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 138: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 139: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 140: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 141: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 142: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 143: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 144: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 145: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 146: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 147: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 148: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 149: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 150: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 151: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 152: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 153: //dnam DNAM ,, Struct
            return UINT32_FIELD;
        case 154: //crdt CRDT ,, Struct
            return UINT16_FIELD;
        case 155: //crdt_p CRDT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 156: //crdt CRDT ,, Struct
            return FLOAT32_FIELD;
        case 157: //crdt CRDT ,, Struct
            return UINT8_FIELD;
        case 158: //crdt_p CRDT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 159: //crdt CRDT ,, Struct
            return FORMID_FIELD;
        case 160: //vats VATS ,, Struct
            return FORMID_FIELD;
        case 161: //vats VATS ,, Struct
            return FLOAT32_FIELD;
        case 162: //vats VATS ,, Struct
            return FLOAT32_FIELD;
        case 163: //vats VATS ,, Struct
            return FLOAT32_FIELD;
        case 164: //vats VATS ,, Struct
            return UINT8_FIELD;
        case 165: //vats VATS ,, Struct
            return UINT8_FIELD;
        case 166: //vats_p VATS ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 167: //vnam Sound Level
            return UINT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * WEAPRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 18: //icon Large Icon Filename
            return ICON.IsLoaded() ? ICON->ICON.value : NULL;
        case 19: //mico Small Icon Filename
            return ICON.IsLoaded() ? ICON->MICO.value : NULL;
        case 20: //scri Script
            return SCRI.IsLoaded() ? &SCRI->value20 : NULL;
        case 21: //eitm Object Effect
            return EITM.IsLoaded() ? &EITM->value21 : NULL;
        case 22: //eamt Enchantment Charge Amount
            return EAMT.IsLoaded() ? &EAMT->value22 : NULL;
        case 23: //nam0 Ammo
            return NAM0.IsLoaded() ? &NAM0->value23 : NULL;
        case 24: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value24 : NULL;
        case 25: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value25 : NULL;
        case 26: //dest Header
            return DEST.IsLoaded() ? &DEST->DEST->value26 : NULL;
        case 27: //dest_p Header
            *FieldValues = DEST.IsLoaded() ? &DEST->DEST->value27[0] : NULL;
            return NULL;
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
        case 33: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value33 : NULL;
        case 34: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value34 : NULL;
        case 35: //dstd Destruction Stage Data
            return DEST.IsLoaded() ? &DEST->DSTD->value35 : NULL;
        case 36: //dmdl Model Filename
            return DEST.IsLoaded() ? DEST->DMDL.value : NULL;
        case 37: //dmdt_p Texture Files Hashes
            *FieldValues = (DEST.IsLoaded()) ? DEST->DMDT.value : NULL;
            return NULL;
        case 38: //repl Repair List
            return REPL.IsLoaded() ? &REPL->value38 : NULL;
        case 39: //etyp Equipment Type
            return ETYPReq.IsLoaded() ? &ETYPReq->value39 : NULL;
        case 40: //bipl Biped Model List
            return BIPL.IsLoaded() ? &BIPL->value40 : NULL;
        case 41: //ynam Sound - Pick Up
            return YNAM.IsLoaded() ? &YNAM->value41 : NULL;
        case 42: //znam Sound - Drop
            return ZNAM.IsLoaded() ? &ZNAM->value42 : NULL;
        case 43: //mod2 Model Filename
            return MOD2.IsLoaded() ? MOD2->MOD2.value : NULL;
        case 44: //mo2t_p Texture Files Hashes
            *FieldValues = (MOD2.IsLoaded()) ? MOD2->MO2T.value : NULL;
            return NULL;
        case 45: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? MOD2->MO2S.value : NULL;
        case 46: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? &MOD2->MO2S->value46 : NULL;
        case 47: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? &MOD2->MO2S->value47 : NULL;
        case 48: //mod3 Model Filename
            return MOD3.IsLoaded() ? MOD3->MOD3.value : NULL;
        case 49: //mo3t_p Texture Files Hashes
            *FieldValues = (MOD3.IsLoaded()) ? MOD3->MO3T.value : NULL;
            return NULL;
        case 50: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? MOD3->MO3S.value : NULL;
        case 51: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? &MOD3->MO3S->value51 : NULL;
        case 52: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? &MOD3->MO3S->value52 : NULL;
        case 53: //efsd Scope Effect
            return EFSD.IsLoaded() ? &EFSD->value53 : NULL;
        case 54: //mod4 Model Filename
            return MOD4.IsLoaded() ? MOD4->MOD4.value : NULL;
        case 55: //mo4t_p Texture Files Hashes
            *FieldValues = (MOD4.IsLoaded()) ? MOD4->MO4T.value : NULL;
            return NULL;
        case 56: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? MOD4->MO4S.value : NULL;
        case 57: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? &MOD4->MO4S->value57 : NULL;
        case 58: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? &MOD4->MO4S->value58 : NULL;
        case 59: //vanm VATS Attack Name
            return VANM.value;
        case 60: //nnam Embedded Weapon Node
            return NNAM.value;
        case 61: //mwd1 Mod 1
            return MWD1.IsLoaded() ? MWD1->MWD1.value : NULL;
        case 62: //mwd2 Mod 2
            return MWD1.IsLoaded() ? MWD1->MWD2.value : NULL;
        case 63: //mwd3 Mod 1 and 2
            return MWD1.IsLoaded() ? MWD1->MWD3.value : NULL;
        case 64: //mwd4 Mod 3
            return MWD1.IsLoaded() ? MWD1->MWD4.value : NULL;
        case 65: //mwd5 Mod 1 and 3
            return MWD1.IsLoaded() ? MWD1->MWD5.value : NULL;
        case 66: //mwd6 Mod 2 and 3
            return MWD1.IsLoaded() ? MWD1->MWD6.value : NULL;
        case 67: //mwd7 Mod 1, 2 and 3
            return MWD1.IsLoaded() ? MWD1->MWD7.value : NULL;
        case 68: //inam Impact DataSet
            return INAM.IsLoaded() ? &INAM->value68 : NULL;
        case 69: //wnam 1st Person Model
            return WNAM.IsLoaded() ? &WNAM->value69 : NULL;
        case 70: //wnm1 Mod 1
            return WNM1.IsLoaded() ? &WNM1->WNM1->value70 : NULL;
        case 71: //wnm2 Mod 2
            return WNM1.IsLoaded() ? &WNM1->WNM2->value71 : NULL;
        case 72: //wnm3 Mod 1 and 2
            return WNM1.IsLoaded() ? &WNM1->WNM3->value72 : NULL;
        case 73: //wnm4 Mod 3
            return WNM1.IsLoaded() ? &WNM1->WNM4->value73 : NULL;
        case 74: //wnm5 Mod 1 and 3
            return WNM1.IsLoaded() ? &WNM1->WNM5->value74 : NULL;
        case 75: //wnm6 Mod 2 and 3
            return WNM1.IsLoaded() ? &WNM1->WNM6->value75 : NULL;
        case 76: //wnm7 Mod 1, 2 and 3
            return WNM1.IsLoaded() ? &WNM1->WNM7->value76 : NULL;
        case 77: //wmi1 Mod 1
            return WMI1.IsLoaded() ? &WMI1->WMI1->value77 : NULL;
        case 78: //wmi2 Mod 2
            return WMI1.IsLoaded() ? &WMI1->WMI2->value78 : NULL;
        case 79: //wmi3 Mod 3
            return WMI1.IsLoaded() ? &WMI1->WMI3->value79 : NULL;
        case 80: //snam Sound - Gun - Shoot Dist
            return SNAM.IsLoaded() ? &SNAM->value80 : NULL;
        case 81: //xnam Sound - Gun - Shoot 2D
            return XNAM.IsLoaded() ? &XNAM->value81 : NULL;
        case 82: //nam7 Sound - Gun - Shoot 3D Looping
            return NAM7.IsLoaded() ? &NAM7->value82 : NULL;
        case 83: //tnam Sound - Melee - Swing / Gun - No Ammo
            return TNAM.IsLoaded() ? &TNAM->value83 : NULL;
        case 84: //nam6 Sound - Block
            return NAM6.IsLoaded() ? &NAM6->value84 : NULL;
        case 85: //unam Sound - Idle
            return UNAM.IsLoaded() ? &UNAM->value85 : NULL;
        case 86: //nam9 Sound - Equip
            return NAM9.IsLoaded() ? &NAM9->value86 : NULL;
        case 87: //nam8 Sound - Unequip
            return NAM8.IsLoaded() ? &NAM8->value87 : NULL;
        case 88: //wms1 Sound - Mod 1 - Shoot Dist
            return WMS1.IsLoaded() ? &WMS1->value88 : NULL;
        case 89: //wms2 Sound - Mod 1 - Shoot 2D
            return WMS2.IsLoaded() ? &WMS2->value89 : NULL;
        case 90: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value90 : NULL;
        case 91: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value91 : NULL;
        case 92: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value92 : NULL;
        case 93: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value93 : NULL;
        case 94: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value94 : NULL;
        case 95: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value95 : NULL;
        case 96: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value96 : NULL;
        case 97: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value97 : NULL;
        case 98: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value98 : NULL;
        case 99: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value99 : NULL;
        case 100: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value100 : NULL;
        case 101: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value101 : NULL;
        case 102: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value102 : NULL;
        case 103: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value103 : NULL;
        case 104: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value104 : NULL;
        case 105: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value105 : NULL;
        case 106: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value106 : NULL;
        case 107: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value107 : NULL;
        case 108: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value108 : NULL;
        case 109: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value109 : NULL;
        case 110: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value110 : NULL;
        case 111: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value111 : NULL;
        case 112: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value112 : NULL;
        case 113: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value113 : NULL;
        case 114: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value114 : NULL;
        case 115: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value115 : NULL;
        case 116: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value116 : NULL;
        case 117: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value117 : NULL;
        case 118: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value118 : NULL;
        case 119: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value119 : NULL;
        case 120: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value120 : NULL;
        case 121: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value121 : NULL;
        case 122: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value122 : NULL;
        case 123: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value123 : NULL;
        case 124: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value124 : NULL;
        case 125: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value125 : NULL;
        case 126: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value126 : NULL;
        case 127: //dnam DNAM ,, Struct
            return UNPARSEDGET_FIELD127;
        case 128: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value128 : NULL;
        case 129: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value129 : NULL;
        case 130: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value130 : NULL;
        case 131: //dnam DNAM ,, Struct
            return UNPARSEDGET_FIELD131;
        case 132: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value132 : NULL;
        case 133: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value133 : NULL;
        case 134: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value134 : NULL;
        case 135: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value135 : NULL;
        case 136: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value136 : NULL;
        case 137: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value137 : NULL;
        case 138: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value138 : NULL;
        case 139: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value139 : NULL;
        case 140: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value140 : NULL;
        case 141: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value141 : NULL;
        case 142: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value142 : NULL;
        case 143: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value143 : NULL;
        case 144: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value144[0] : NULL;
            return NULL;
        case 145: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value145 : NULL;
        case 146: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value146[0] : NULL;
            return NULL;
        case 147: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value147 : NULL;
        case 148: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value148 : NULL;
        case 149: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value149 : NULL;
        case 150: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value150 : NULL;
        case 151: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value151 : NULL;
        case 152: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value152 : NULL;
        case 153: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value153 : NULL;
        case 154: //crdt CRDT ,, Struct
            return CRDT.IsLoaded() ? &CRDT->value154 : NULL;
        case 155: //crdt_p CRDT ,, Struct
            *FieldValues = CRDT.IsLoaded() ? &CRDT->value155[0] : NULL;
            return NULL;
        case 156: //crdt CRDT ,, Struct
            return CRDT.IsLoaded() ? &CRDT->value156 : NULL;
        case 157: //crdt CRDT ,, Struct
            return CRDT.IsLoaded() ? &CRDT->value157 : NULL;
        case 158: //crdt_p CRDT ,, Struct
            *FieldValues = CRDT.IsLoaded() ? &CRDT->value158[0] : NULL;
            return NULL;
        case 159: //crdt CRDT ,, Struct
            return CRDT.IsLoaded() ? &CRDT->value159 : NULL;
        case 160: //vats VATS ,, Struct
            return VATS.IsLoaded() ? &VATS->value160 : NULL;
        case 161: //vats VATS ,, Struct
            return VATS.IsLoaded() ? &VATS->value161 : NULL;
        case 162: //vats VATS ,, Struct
            return VATS.IsLoaded() ? &VATS->value162 : NULL;
        case 163: //vats VATS ,, Struct
            return VATS.IsLoaded() ? &VATS->value163 : NULL;
        case 164: //vats VATS ,, Struct
            return VATS.IsLoaded() ? &VATS->value164 : NULL;
        case 165: //vats VATS ,, Struct
            return VATS.IsLoaded() ? &VATS->value165 : NULL;
        case 166: //vats_p VATS ,, Struct
            *FieldValues = VATS.IsLoaded() ? &VATS->value166[0] : NULL;
            return NULL;
        case 167: //vnam Sound Level
            return VNAM.IsLoaded() ? &VNAM->value167 : NULL;
        default:
            return NULL;
        }
    }

bool WEAPRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 18: //icon Large Icon Filename
            ICON.Load();
            ICON->ICON.Copy((STRING)FieldValue);
            break;
        case 19: //mico Small Icon Filename
            ICON.Load();
            ICON->MICO.Copy((STRING)FieldValue);
            break;
        case 20: //scri Script
            SCRI.Load();
            SCRI->value20 = *(FORMID *)FieldValue;
            return true;
        case 21: //eitm Object Effect
            EITM.Load();
            EITM->value21 = *(FORMID *)FieldValue;
            return true;
        case 22: //eamt Enchantment Charge Amount
            EAMT.Load();
            EAMT->value22 = *(SINT16 *)FieldValue;
            break;
        case 23: //nam0 Ammo
            NAM0.Load();
            NAM0->value23 = *(FORMID *)FieldValue;
            return true;
        case 24: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value24 = *(SINT32 *)FieldValue;
            break;
        case 25: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value25 = *(UINT8 *)FieldValue;
            break;
        case 26: //dest Header
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value26 = *(UINT8 *)FieldValue;
            break;
        case 27: //dest_p Header
            if(ArraySize != 2)
                break;
            DEST.Load();
            DEST->DEST.Load();
            DEST->DEST->value27[0] = ((UINT8 *)FieldValue)[0];
            DEST->DEST->value27[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 28: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value29 = *(UINT8 *)FieldValue;
            break;
        case 30: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value30 = *(UINT8 *)FieldValue;
            break;
        case 31: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value31 = *(UINT8 *)FieldValue;
            break;
        case 32: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value32 = *(SINT32 *)FieldValue;
            break;
        case 33: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value33 = *(FORMID *)FieldValue;
            return true;
        case 34: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value34 = *(FORMID *)FieldValue;
            return true;
        case 35: //dstd Destruction Stage Data
            DEST.Load();
            DEST->DSTD.Load();
            DEST->DSTD->value35 = *(SINT32 *)FieldValue;
            break;
        case 36: //dmdl Model Filename
            DEST.Load();
            DEST->DMDL.Copy((STRING)FieldValue);
            break;
        case 37: //dmdt_p Texture Files Hashes
            DEST.Load();
            DEST->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 38: //repl Repair List
            REPL.Load();
            REPL->value38 = *(FORMID *)FieldValue;
            return true;
        case 39: //etyp Equipment Type
            ETYPReq.Load();
            ETYPReq->value39 = *(SINT32 *)FieldValue;
            break;
        case 40: //bipl Biped Model List
            BIPL.Load();
            BIPL->value40 = *(FORMID *)FieldValue;
            return true;
        case 41: //ynam Sound - Pick Up
            YNAM.Load();
            YNAM->value41 = *(FORMID *)FieldValue;
            return true;
        case 42: //znam Sound - Drop
            ZNAM.Load();
            ZNAM->value42 = *(FORMID *)FieldValue;
            return true;
        case 43: //mod2 Model Filename
            MOD2.Load();
            MOD2->MOD2.Copy((STRING)FieldValue);
            break;
        case 44: //mo2t_p Texture Files Hashes
            MOD2.Load();
            MOD2->MO2T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 45: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Copy((STRING)FieldValue);
            break;
        case 46: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Load();
            MOD2->MO2S->value46 = *(FORMID *)FieldValue;
            return true;
        case 47: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Load();
            MOD2->MO2S->value47 = *(SINT32 *)FieldValue;
            break;
        case 48: //mod3 Model Filename
            MOD3.Load();
            MOD3->MOD3.Copy((STRING)FieldValue);
            break;
        case 49: //mo3t_p Texture Files Hashes
            MOD3.Load();
            MOD3->MO3T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 50: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Copy((STRING)FieldValue);
            break;
        case 51: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Load();
            MOD3->MO3S->value51 = *(FORMID *)FieldValue;
            return true;
        case 52: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Load();
            MOD3->MO3S->value52 = *(SINT32 *)FieldValue;
            break;
        case 53: //efsd Scope Effect
            EFSD.Load();
            EFSD->value53 = *(FORMID *)FieldValue;
            return true;
        case 54: //mod4 Model Filename
            MOD4.Load();
            MOD4->MOD4.Copy((STRING)FieldValue);
            break;
        case 55: //mo4t_p Texture Files Hashes
            MOD4.Load();
            MOD4->MO4T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 56: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Copy((STRING)FieldValue);
            break;
        case 57: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Load();
            MOD4->MO4S->value57 = *(FORMID *)FieldValue;
            return true;
        case 58: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Load();
            MOD4->MO4S->value58 = *(SINT32 *)FieldValue;
            break;
        case 59: //vanm VATS Attack Name
            VANM.Copy((STRING)FieldValue);
            break;
        case 60: //nnam Embedded Weapon Node
            NNAM.Copy((STRING)FieldValue);
            break;
        case 61: //mwd1 Mod 1
            MWD1.Load();
            MWD1->MWD1.Copy((STRING)FieldValue);
            break;
        case 62: //mwd2 Mod 2
            MWD1.Load();
            MWD1->MWD2.Copy((STRING)FieldValue);
            break;
        case 63: //mwd3 Mod 1 and 2
            MWD1.Load();
            MWD1->MWD3.Copy((STRING)FieldValue);
            break;
        case 64: //mwd4 Mod 3
            MWD1.Load();
            MWD1->MWD4.Copy((STRING)FieldValue);
            break;
        case 65: //mwd5 Mod 1 and 3
            MWD1.Load();
            MWD1->MWD5.Copy((STRING)FieldValue);
            break;
        case 66: //mwd6 Mod 2 and 3
            MWD1.Load();
            MWD1->MWD6.Copy((STRING)FieldValue);
            break;
        case 67: //mwd7 Mod 1, 2 and 3
            MWD1.Load();
            MWD1->MWD7.Copy((STRING)FieldValue);
            break;
        case 68: //inam Impact DataSet
            INAM.Load();
            INAM->value68 = *(FORMID *)FieldValue;
            return true;
        case 69: //wnam 1st Person Model
            WNAM.Load();
            WNAM->value69 = *(FORMID *)FieldValue;
            return true;
        case 70: //wnm1 Mod 1
            WNM1.Load();
            WNM1->WNM1.Load();
            WNM1->WNM1->value70 = *(FORMID *)FieldValue;
            return true;
        case 71: //wnm2 Mod 2
            WNM1.Load();
            WNM1->WNM2.Load();
            WNM1->WNM2->value71 = *(FORMID *)FieldValue;
            return true;
        case 72: //wnm3 Mod 1 and 2
            WNM1.Load();
            WNM1->WNM3.Load();
            WNM1->WNM3->value72 = *(FORMID *)FieldValue;
            return true;
        case 73: //wnm4 Mod 3
            WNM1.Load();
            WNM1->WNM4.Load();
            WNM1->WNM4->value73 = *(FORMID *)FieldValue;
            return true;
        case 74: //wnm5 Mod 1 and 3
            WNM1.Load();
            WNM1->WNM5.Load();
            WNM1->WNM5->value74 = *(FORMID *)FieldValue;
            return true;
        case 75: //wnm6 Mod 2 and 3
            WNM1.Load();
            WNM1->WNM6.Load();
            WNM1->WNM6->value75 = *(FORMID *)FieldValue;
            return true;
        case 76: //wnm7 Mod 1, 2 and 3
            WNM1.Load();
            WNM1->WNM7.Load();
            WNM1->WNM7->value76 = *(FORMID *)FieldValue;
            return true;
        case 77: //wmi1 Mod 1
            WMI1.Load();
            WMI1->WMI1.Load();
            WMI1->WMI1->value77 = *(FORMID *)FieldValue;
            return true;
        case 78: //wmi2 Mod 2
            WMI1.Load();
            WMI1->WMI2.Load();
            WMI1->WMI2->value78 = *(FORMID *)FieldValue;
            return true;
        case 79: //wmi3 Mod 3
            WMI1.Load();
            WMI1->WMI3.Load();
            WMI1->WMI3->value79 = *(FORMID *)FieldValue;
            return true;
        case 80: //snam Sound - Gun - Shoot Dist
            SNAM.Load();
            SNAM->value80 = *(FORMID *)FieldValue;
            return true;
        case 81: //xnam Sound - Gun - Shoot 2D
            XNAM.Load();
            XNAM->value81 = *(FORMID *)FieldValue;
            return true;
        case 82: //nam7 Sound - Gun - Shoot 3D Looping
            NAM7.Load();
            NAM7->value82 = *(FORMID *)FieldValue;
            return true;
        case 83: //tnam Sound - Melee - Swing / Gun - No Ammo
            TNAM.Load();
            TNAM->value83 = *(FORMID *)FieldValue;
            return true;
        case 84: //nam6 Sound - Block
            NAM6.Load();
            NAM6->value84 = *(FORMID *)FieldValue;
            return true;
        case 85: //unam Sound - Idle
            UNAM.Load();
            UNAM->value85 = *(FORMID *)FieldValue;
            return true;
        case 86: //nam9 Sound - Equip
            NAM9.Load();
            NAM9->value86 = *(FORMID *)FieldValue;
            return true;
        case 87: //nam8 Sound - Unequip
            NAM8.Load();
            NAM8->value87 = *(FORMID *)FieldValue;
            return true;
        case 88: //wms1 Sound - Mod 1 - Shoot Dist
            WMS1.Load();
            WMS1->value88 = *(FORMID *)FieldValue;
            return true;
        case 89: //wms2 Sound - Mod 1 - Shoot 2D
            WMS2.Load();
            WMS2->value89 = *(FORMID *)FieldValue;
            return true;
        case 90: //data DATA ,, Struct
            DATA.Load();
            DATA->value90 = *(SINT32 *)FieldValue;
            break;
        case 91: //data DATA ,, Struct
            DATA.Load();
            DATA->value91 = *(SINT32 *)FieldValue;
            break;
        case 92: //data DATA ,, Struct
            DATA.Load();
            DATA->value92 = *(FLOAT32 *)FieldValue;
            break;
        case 93: //data DATA ,, Struct
            DATA.Load();
            DATA->value93 = *(SINT16 *)FieldValue;
            break;
        case 94: //data DATA ,, Struct
            DATA.Load();
            DATA->value94 = *(UINT8 *)FieldValue;
            break;
        case 95: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value95 = *(UINT32 *)FieldValue;
            break;
        case 96: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value96 = *(FLOAT32 *)FieldValue;
            break;
        case 97: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value97 = *(FLOAT32 *)FieldValue;
            break;
        case 98: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value98 = *(UINT8 *)FieldValue;
            break;
        case 99: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value99 = *(UINT8 *)FieldValue;
            break;
        case 100: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value100 = *(UINT8 *)FieldValue;
            break;
        case 101: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value101 = *(UINT8 *)FieldValue;
            break;
        case 102: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value102 = *(FLOAT32 *)FieldValue;
            break;
        case 103: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value103 = *(FLOAT32 *)FieldValue;
            break;
        case 104: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value104 = *(FLOAT32 *)FieldValue;
            break;
        case 105: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value105 = *(FLOAT32 *)FieldValue;
            break;
        case 106: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value106 = *(FLOAT32 *)FieldValue;
            break;
        case 107: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value107 = *(FORMID *)FieldValue;
            return true;
        case 108: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value108 = *(UINT8 *)FieldValue;
            break;
        case 109: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value109 = *(UINT8 *)FieldValue;
            break;
        case 110: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value110 = *(UINT8 *)FieldValue;
            break;
        case 111: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value111 = *(UINT8 *)FieldValue;
            break;
        case 112: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value112 = *(FLOAT32 *)FieldValue;
            break;
        case 113: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value113 = *(FLOAT32 *)FieldValue;
            break;
        case 114: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value114 = *(UINT32 *)FieldValue;
            break;
        case 115: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value115 = *(UINT32 *)FieldValue;
            break;
        case 116: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value116 = *(FLOAT32 *)FieldValue;
            break;
        case 117: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value117 = *(FLOAT32 *)FieldValue;
            break;
        case 118: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value118 = *(FLOAT32 *)FieldValue;
            break;
        case 119: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value119 = *(FLOAT32 *)FieldValue;
            break;
        case 120: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value120 = *(FLOAT32 *)FieldValue;
            break;
        case 121: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value121 = *(FLOAT32 *)FieldValue;
            break;
        case 122: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value122 = *(FLOAT32 *)FieldValue;
            break;
        case 123: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value123 = *(FLOAT32 *)FieldValue;
            break;
        case 124: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value124 = *(FLOAT32 *)FieldValue;
            break;
        case 125: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value125 = *(FLOAT32 *)FieldValue;
            break;
        case 126: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value126 = *(FLOAT32 *)FieldValue;
            break;
        case 127: //dnam DNAM ,, Struct
            return UNPARSEDGET_FIELD127;
        case 128: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value128 = *(UINT32 *)FieldValue;
            break;
        case 129: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value129 = *(FLOAT32 *)FieldValue;
            break;
        case 130: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value130 = *(FLOAT32 *)FieldValue;
            break;
        case 131: //dnam DNAM ,, Struct
            return UNPARSEDGET_FIELD131;
        case 132: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value132 = *(FLOAT32 *)FieldValue;
            break;
        case 133: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value133 = *(FLOAT32 *)FieldValue;
            break;
        case 134: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value134 = *(FLOAT32 *)FieldValue;
            break;
        case 135: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value135 = *(FLOAT32 *)FieldValue;
            break;
        case 136: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value136 = *(UINT32 *)FieldValue;
            break;
        case 137: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value137 = *(UINT32 *)FieldValue;
            break;
        case 138: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value138 = *(UINT32 *)FieldValue;
            break;
        case 139: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value139 = *(FLOAT32 *)FieldValue;
            break;
        case 140: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value140 = *(FLOAT32 *)FieldValue;
            break;
        case 141: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value141 = *(FLOAT32 *)FieldValue;
            break;
        case 142: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value142 = *(UINT32 *)FieldValue;
            break;
        case 143: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value143 = *(UINT32 *)FieldValue;
            break;
        case 144: //dnam_p DNAM ,, Struct
            if(ArraySize != 1)
                break;
            DNAM.Load();
            DNAM->value144[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 145: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value145 = *(UINT8 *)FieldValue;
            break;
        case 146: //dnam_p DNAM ,, Struct
            if(ArraySize != 2)
                break;
            DNAM.Load();
            DNAM->value146[0] = ((UINT8 *)FieldValue)[0];
            DNAM->value146[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 147: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value147 = *(FLOAT32 *)FieldValue;
            break;
        case 148: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value148 = *(FLOAT32 *)FieldValue;
            break;
        case 149: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value149 = *(FLOAT32 *)FieldValue;
            break;
        case 150: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value150 = *(FLOAT32 *)FieldValue;
            break;
        case 151: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value151 = *(FLOAT32 *)FieldValue;
            break;
        case 152: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value152 = *(FLOAT32 *)FieldValue;
            break;
        case 153: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value153 = *(UINT32 *)FieldValue;
            break;
        case 154: //crdt CRDT ,, Struct
            CRDT.Load();
            CRDT->value154 = *(UINT16 *)FieldValue;
            break;
        case 155: //crdt_p CRDT ,, Struct
            if(ArraySize != 2)
                break;
            CRDT.Load();
            CRDT->value155[0] = ((UINT8 *)FieldValue)[0];
            CRDT->value155[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 156: //crdt CRDT ,, Struct
            CRDT.Load();
            CRDT->value156 = *(FLOAT32 *)FieldValue;
            break;
        case 157: //crdt CRDT ,, Struct
            CRDT.Load();
            CRDT->value157 = *(UINT8 *)FieldValue;
            break;
        case 158: //crdt_p CRDT ,, Struct
            if(ArraySize != 3)
                break;
            CRDT.Load();
            CRDT->value158[0] = ((UINT8 *)FieldValue)[0];
            CRDT->value158[1] = ((UINT8 *)FieldValue)[1];
            CRDT->value158[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 159: //crdt CRDT ,, Struct
            CRDT.Load();
            CRDT->value159 = *(FORMID *)FieldValue;
            return true;
        case 160: //vats VATS ,, Struct
            VATS.Load();
            VATS->value160 = *(FORMID *)FieldValue;
            return true;
        case 161: //vats VATS ,, Struct
            VATS.Load();
            VATS->value161 = *(FLOAT32 *)FieldValue;
            break;
        case 162: //vats VATS ,, Struct
            VATS.Load();
            VATS->value162 = *(FLOAT32 *)FieldValue;
            break;
        case 163: //vats VATS ,, Struct
            VATS.Load();
            VATS->value163 = *(FLOAT32 *)FieldValue;
            break;
        case 164: //vats VATS ,, Struct
            VATS.Load();
            VATS->value164 = *(UINT8 *)FieldValue;
            break;
        case 165: //vats VATS ,, Struct
            VATS.Load();
            VATS->value165 = *(UINT8 *)FieldValue;
            break;
        case 166: //vats_p VATS ,, Struct
            if(ArraySize != 2)
                break;
            VATS.Load();
            VATS->value166[0] = ((UINT8 *)FieldValue)[0];
            VATS->value166[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 167: //vnam Sound Level
            VNAM.Load();
            VNAM->value167 = *(UINT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void WEAPRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 18: //icon Large Icon Filename
            if(ICON.IsLoaded())
                ICON->ICON.Unload();
            return;
        case 19: //mico Small Icon Filename
            if(ICON.IsLoaded())
                ICON->MICO.Unload();
            return;
        case 20: //scri Script
            SCRI.Unload();
            return;
        case 21: //eitm Object Effect
            EITM.Unload();
            return;
        case 22: //eamt Enchantment Charge Amount
            EAMT.Unload();
            return;
        case 23: //nam0 Ammo
            NAM0.Unload();
            return;
        case 24: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 25: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 26: //dest Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
            return;
        case 27: //dest_p Header
            if(DEST.IsLoaded())
                DEST->DEST.Unload();
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
        case 33: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 34: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 35: //dstd Destruction Stage Data
            if(DEST.IsLoaded())
                DEST->DSTD.Unload();
            return;
        case 36: //dmdl Model Filename
            if(DEST.IsLoaded())
                DEST->DMDL.Unload();
            return;
        case 37: //dmdt_p Texture Files Hashes
            if(DEST.IsLoaded())
                DEST->DMDT.Unload();
            return;
        case 38: //repl Repair List
            REPL.Unload();
            return;
        case 39: //etyp Equipment Type
            ETYPReq.Unload();
            return;
        case 40: //bipl Biped Model List
            BIPL.Unload();
            return;
        case 41: //ynam Sound - Pick Up
            YNAM.Unload();
            return;
        case 42: //znam Sound - Drop
            ZNAM.Unload();
            return;
        case 43: //mod2 Model Filename
            if(MOD2.IsLoaded())
                MOD2->MOD2.Unload();
            return;
        case 44: //mo2t_p Texture Files Hashes
            if(MOD2.IsLoaded())
                MOD2->MO2T.Unload();
            return;
        case 45: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 46: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 47: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 48: //mod3 Model Filename
            if(MOD3.IsLoaded())
                MOD3->MOD3.Unload();
            return;
        case 49: //mo3t_p Texture Files Hashes
            if(MOD3.IsLoaded())
                MOD3->MO3T.Unload();
            return;
        case 50: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 51: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 52: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 53: //efsd Scope Effect
            EFSD.Unload();
            return;
        case 54: //mod4 Model Filename
            if(MOD4.IsLoaded())
                MOD4->MOD4.Unload();
            return;
        case 55: //mo4t_p Texture Files Hashes
            if(MOD4.IsLoaded())
                MOD4->MO4T.Unload();
            return;
        case 56: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 57: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 58: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 59: //vanm VATS Attack Name
            VANM.Unload();
            return;
        case 60: //nnam Embedded Weapon Node
            NNAM.Unload();
            return;
        case 61: //mwd1 Mod 1
            if(MWD1.IsLoaded())
                MWD1->MWD1.Unload();
            return;
        case 62: //mwd2 Mod 2
            if(MWD1.IsLoaded())
                MWD1->MWD2.Unload();
            return;
        case 63: //mwd3 Mod 1 and 2
            if(MWD1.IsLoaded())
                MWD1->MWD3.Unload();
            return;
        case 64: //mwd4 Mod 3
            if(MWD1.IsLoaded())
                MWD1->MWD4.Unload();
            return;
        case 65: //mwd5 Mod 1 and 3
            if(MWD1.IsLoaded())
                MWD1->MWD5.Unload();
            return;
        case 66: //mwd6 Mod 2 and 3
            if(MWD1.IsLoaded())
                MWD1->MWD6.Unload();
            return;
        case 67: //mwd7 Mod 1, 2 and 3
            if(MWD1.IsLoaded())
                MWD1->MWD7.Unload();
            return;
        case 68: //inam Impact DataSet
            INAM.Unload();
            return;
        case 69: //wnam 1st Person Model
            WNAM.Unload();
            return;
        case 70: //wnm1 Mod 1
            if(WNM1.IsLoaded())
                WNM1->WNM1.Unload();
            return;
        case 71: //wnm2 Mod 2
            if(WNM1.IsLoaded())
                WNM1->WNM2.Unload();
            return;
        case 72: //wnm3 Mod 1 and 2
            if(WNM1.IsLoaded())
                WNM1->WNM3.Unload();
            return;
        case 73: //wnm4 Mod 3
            if(WNM1.IsLoaded())
                WNM1->WNM4.Unload();
            return;
        case 74: //wnm5 Mod 1 and 3
            if(WNM1.IsLoaded())
                WNM1->WNM5.Unload();
            return;
        case 75: //wnm6 Mod 2 and 3
            if(WNM1.IsLoaded())
                WNM1->WNM6.Unload();
            return;
        case 76: //wnm7 Mod 1, 2 and 3
            if(WNM1.IsLoaded())
                WNM1->WNM7.Unload();
            return;
        case 77: //wmi1 Mod 1
            if(WMI1.IsLoaded())
                WMI1->WMI1.Unload();
            return;
        case 78: //wmi2 Mod 2
            if(WMI1.IsLoaded())
                WMI1->WMI2.Unload();
            return;
        case 79: //wmi3 Mod 3
            if(WMI1.IsLoaded())
                WMI1->WMI3.Unload();
            return;
        case 80: //snam Sound - Gun - Shoot Dist
            SNAM.Unload();
            return;
        case 81: //xnam Sound - Gun - Shoot 2D
            XNAM.Unload();
            return;
        case 82: //nam7 Sound - Gun - Shoot 3D Looping
            NAM7.Unload();
            return;
        case 83: //tnam Sound - Melee - Swing / Gun - No Ammo
            TNAM.Unload();
            return;
        case 84: //nam6 Sound - Block
            NAM6.Unload();
            return;
        case 85: //unam Sound - Idle
            UNAM.Unload();
            return;
        case 86: //nam9 Sound - Equip
            NAM9.Unload();
            return;
        case 87: //nam8 Sound - Unequip
            NAM8.Unload();
            return;
        case 88: //wms1 Sound - Mod 1 - Shoot Dist
            WMS1.Unload();
            return;
        case 89: //wms2 Sound - Mod 1 - Shoot 2D
            WMS2.Unload();
            return;
        case 90: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 91: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 92: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 93: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 94: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 95: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 96: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 97: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 98: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 99: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 100: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 101: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 102: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 103: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 104: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 105: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 106: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 107: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 108: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 109: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 110: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 111: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 112: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 113: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 114: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 115: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 116: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 117: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 118: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 119: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 120: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 121: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 122: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 123: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 124: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 125: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 126: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 127: //dnam DNAM ,, Struct
            return UNPARSEDDEL_FIELD127;
        case 128: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 129: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 130: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 131: //dnam DNAM ,, Struct
            return UNPARSEDDEL_FIELD131;
        case 132: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 133: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 134: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 135: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 136: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 137: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 138: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 139: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 140: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 141: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 142: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 143: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 144: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 145: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 146: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 147: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 148: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 149: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 150: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 151: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 152: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 153: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 154: //crdt CRDT ,, Struct
            CRDT.Unload();
            return;
        case 155: //crdt_p CRDT ,, Struct
            CRDT.Unload();
            return;
        case 156: //crdt CRDT ,, Struct
            CRDT.Unload();
            return;
        case 157: //crdt CRDT ,, Struct
            CRDT.Unload();
            return;
        case 158: //crdt_p CRDT ,, Struct
            CRDT.Unload();
            return;
        case 159: //crdt CRDT ,, Struct
            CRDT.Unload();
            return;
        case 160: //vats VATS ,, Struct
            VATS.Unload();
            return;
        case 161: //vats VATS ,, Struct
            VATS.Unload();
            return;
        case 162: //vats VATS ,, Struct
            VATS.Unload();
            return;
        case 163: //vats VATS ,, Struct
            VATS.Unload();
            return;
        case 164: //vats VATS ,, Struct
            VATS.Unload();
            return;
        case 165: //vats VATS ,, Struct
            VATS.Unload();
            return;
        case 166: //vats_p VATS ,, Struct
            VATS.Unload();
            return;
        case 167: //vnam Sound Level
            VNAM.Unload();
            return;
        default:
            return;
        }
    }
}