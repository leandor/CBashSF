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
#include "..\ARMORecord.h"

namespace FNV
{
UINT32 ARMORecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 11: //scri Script
            return FORMID_FIELD;
        case 12: //eitm Object Effect
            return FORMID_FIELD;
        case 13: //bmdt Biped Data
            return UINT32_FIELD;
        case 14: //bmdt Biped Data
            return UINT8_FIELD;
        case 15: //bmdt_p Biped Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 16: //modl Model Filename
            return ISTRING_FIELD;
        case 17: //modt_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODT.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 18: //mods Alternate Texture
            return ISTRING_FIELD;
        case 19: //mods Alternate Texture
            return FORMID_FIELD;
        case 20: //mods Alternate Texture
            return SINT32_FIELD;
        case 21: //modd FaceGen Model Flags
            return UINT8_FIELD;
        case 22: //mod2 Model Filename
            return ISTRING_FIELD;
        case 23: //mo2t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO2T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 24: //mo2s Alternate Texture
            return ISTRING_FIELD;
        case 25: //mo2s Alternate Texture
            return FORMID_FIELD;
        case 26: //mo2s Alternate Texture
            return SINT32_FIELD;
        case 27: //icon Male icon filename
            return ISTRING_FIELD;
        case 28: //mico Male mico filename
            return ISTRING_FIELD;
        case 29: //mod3 Model Filename
            return ISTRING_FIELD;
        case 30: //mo3t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO3T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 31: //mo3s Alternate Texture
            return ISTRING_FIELD;
        case 32: //mo3s Alternate Texture
            return FORMID_FIELD;
        case 33: //mo3s Alternate Texture
            return SINT32_FIELD;
        case 34: //mosd FaceGen Model Flags
            return UINT8_FIELD;
        case 35: //mod4 Model Filename
            return ISTRING_FIELD;
        case 36: //mo4t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO4T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 37: //mo4s Alternate Texture
            return ISTRING_FIELD;
        case 38: //mo4s Alternate Texture
            return FORMID_FIELD;
        case 39: //mo4s Alternate Texture
            return SINT32_FIELD;
        case 40: //ico2 Female icon filename
            return ISTRING_FIELD;
        case 41: //mic2 Female mico filename
            return ISTRING_FIELD;
        case 42: //bmct Ragdoll Constraint Template
            return ISTRING_FIELD;
        case 43: //repl Repair List
            return FORMID_FIELD;
        case 44: //bipl Biped Model List
            return FORMID_FIELD;
        case 45: //etyp Equipment Type
            return SINT32_FIELD;
        case 46: //ynam Sound - Pick Up
            return FORMID_FIELD;
        case 47: //znam Sound - Drop
            return FORMID_FIELD;
        case 48: //data DATA ,, Struct
            return SINT32_FIELD;
        case 49: //data DATA ,, Struct
            return SINT32_FIELD;
        case 50: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 51: //dnam DNAM ,, Struct
            return SINT16_FIELD;
        case 52: //dnam DNAM ,, Struct
            return UINT16_FIELD;
        case 53: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 54: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 55: //bnam Overrides Animation Sounds
            return UINT32_FIELD;
        case 56: //snam SNAM ,, Struct
            return FORMID_FIELD;
        case 57: //snam SNAM ,, Struct
            return UINT8_FIELD;
        case 58: //snam_p SNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 59: //snam SNAM ,, Struct
            return UINT32_FIELD;
        case 60: //tnam Anmation Sounds Template
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * ARMORecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
            return FULL.value;
        case 11: //scri Script
            return SCRI.IsLoaded() ? &SCRI->value11 : NULL;
        case 12: //eitm Object Effect
            return EITM.IsLoaded() ? &EITM->value12 : NULL;
        case 13: //bmdt Biped Data
            return BMDT.IsLoaded() ? &BMDT->value13 : NULL;
        case 14: //bmdt Biped Data
            return BMDT.IsLoaded() ? &BMDT->value14 : NULL;
        case 15: //bmdt_p Biped Data
            *FieldValues = BMDT.IsLoaded() ? &BMDT->value15[0] : NULL;
            return NULL;
        case 16: //modl Model Filename
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 17: //modt_p Texture Files Hashes
            *FieldValues = (MODL.IsLoaded()) ? MODL->MODT.value : NULL;
            return NULL;
        case 18: //mods Alternate Texture
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 19: //mods Alternate Texture
            return MODL.IsLoaded() ? &MODL->MODS->value19 : NULL;
        case 20: //mods Alternate Texture
            return MODL.IsLoaded() ? &MODL->MODS->value20 : NULL;
        case 21: //modd FaceGen Model Flags
            return MODL.IsLoaded() ? &MODL->MODD->value21 : NULL;
        case 22: //mod2 Model Filename
            return MOD2.IsLoaded() ? MOD2->MOD2.value : NULL;
        case 23: //mo2t_p Texture Files Hashes
            *FieldValues = (MOD2.IsLoaded()) ? MOD2->MO2T.value : NULL;
            return NULL;
        case 24: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? MOD2->MO2S.value : NULL;
        case 25: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? &MOD2->MO2S->value25 : NULL;
        case 26: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? &MOD2->MO2S->value26 : NULL;
        case 27: //icon Male icon filename
            return ICON.value;
        case 28: //mico Male mico filename
            return MICO.value;
        case 29: //mod3 Model Filename
            return MOD3.IsLoaded() ? MOD3->MOD3.value : NULL;
        case 30: //mo3t_p Texture Files Hashes
            *FieldValues = (MOD3.IsLoaded()) ? MOD3->MO3T.value : NULL;
            return NULL;
        case 31: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? MOD3->MO3S.value : NULL;
        case 32: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? &MOD3->MO3S->value32 : NULL;
        case 33: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? &MOD3->MO3S->value33 : NULL;
        case 34: //mosd FaceGen Model Flags
            return MOD3.IsLoaded() ? &MOD3->MOSD->value34 : NULL;
        case 35: //mod4 Model Filename
            return MOD4.IsLoaded() ? MOD4->MOD4.value : NULL;
        case 36: //mo4t_p Texture Files Hashes
            *FieldValues = (MOD4.IsLoaded()) ? MOD4->MO4T.value : NULL;
            return NULL;
        case 37: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? MOD4->MO4S.value : NULL;
        case 38: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? &MOD4->MO4S->value38 : NULL;
        case 39: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? &MOD4->MO4S->value39 : NULL;
        case 40: //ico2 Female icon filename
            return ICO2.value;
        case 41: //mic2 Female mico filename
            return MIC2.value;
        case 42: //bmct Ragdoll Constraint Template
            return BMCT.value;
        case 43: //repl Repair List
            return REPL.IsLoaded() ? &REPL->value43 : NULL;
        case 44: //bipl Biped Model List
            return BIPL.IsLoaded() ? &BIPL->value44 : NULL;
        case 45: //etyp Equipment Type
            return ETYPReq.IsLoaded() ? &ETYPReq->value45 : NULL;
        case 46: //ynam Sound - Pick Up
            return YNAM.IsLoaded() ? &YNAM->value46 : NULL;
        case 47: //znam Sound - Drop
            return ZNAM.IsLoaded() ? &ZNAM->value47 : NULL;
        case 48: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value48 : NULL;
        case 49: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value49 : NULL;
        case 50: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value50 : NULL;
        case 51: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value51 : NULL;
        case 52: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value52 : NULL;
        case 53: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value53 : NULL;
        case 54: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value54[0] : NULL;
            return NULL;
        case 55: //bnam Overrides Animation Sounds
            return BNAM.IsLoaded() ? &BNAM->value55 : NULL;
        case 56: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value56 : NULL;
        case 57: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value57 : NULL;
        case 58: //snam_p SNAM ,, Struct
            *FieldValues = SNAM.IsLoaded() ? &SNAM->value58[0] : NULL;
            return NULL;
        case 59: //snam SNAM ,, Struct
            return SNAM.IsLoaded() ? &SNAM->value59 : NULL;
        case 60: //tnam Anmation Sounds Template
            return TNAM.IsLoaded() ? &TNAM->value60 : NULL;
        default:
            return NULL;
        }
    }

bool ARMORecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
            FULL.Copy((STRING)FieldValue);
            break;
        case 11: //scri Script
            SCRI.Load();
            SCRI->value11 = *(FORMID *)FieldValue;
            return true;
        case 12: //eitm Object Effect
            EITM.Load();
            EITM->value12 = *(FORMID *)FieldValue;
            return true;
        case 13: //bmdt Biped Data
            BMDT.Load();
            BMDT->value13 = *(UINT32 *)FieldValue;
            break;
        case 14: //bmdt Biped Data
            BMDT.Load();
            BMDT->value14 = *(UINT8 *)FieldValue;
            break;
        case 15: //bmdt_p Biped Data
            if(ArraySize != 3)
                break;
            BMDT.Load();
            BMDT->value15[0] = ((UINT8 *)FieldValue)[0];
            BMDT->value15[1] = ((UINT8 *)FieldValue)[1];
            BMDT->value15[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 16: //modl Model Filename
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 17: //modt_p Texture Files Hashes
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 18: //mods Alternate Texture
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 19: //mods Alternate Texture
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value19 = *(FORMID *)FieldValue;
            return true;
        case 20: //mods Alternate Texture
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value20 = *(SINT32 *)FieldValue;
            break;
        case 21: //modd FaceGen Model Flags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value21 = *(UINT8 *)FieldValue;
            break;
        case 22: //mod2 Model Filename
            MOD2.Load();
            MOD2->MOD2.Copy((STRING)FieldValue);
            break;
        case 23: //mo2t_p Texture Files Hashes
            MOD2.Load();
            MOD2->MO2T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 24: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Copy((STRING)FieldValue);
            break;
        case 25: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Load();
            MOD2->MO2S->value25 = *(FORMID *)FieldValue;
            return true;
        case 26: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Load();
            MOD2->MO2S->value26 = *(SINT32 *)FieldValue;
            break;
        case 27: //icon Male icon filename
            ICON.Copy((STRING)FieldValue);
            break;
        case 28: //mico Male mico filename
            MICO.Copy((STRING)FieldValue);
            break;
        case 29: //mod3 Model Filename
            MOD3.Load();
            MOD3->MOD3.Copy((STRING)FieldValue);
            break;
        case 30: //mo3t_p Texture Files Hashes
            MOD3.Load();
            MOD3->MO3T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 31: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Copy((STRING)FieldValue);
            break;
        case 32: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Load();
            MOD3->MO3S->value32 = *(FORMID *)FieldValue;
            return true;
        case 33: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Load();
            MOD3->MO3S->value33 = *(SINT32 *)FieldValue;
            break;
        case 34: //mosd FaceGen Model Flags
            MOD3.Load();
            MOD3->MOSD.Load();
            MOD3->MOSD->value34 = *(UINT8 *)FieldValue;
            break;
        case 35: //mod4 Model Filename
            MOD4.Load();
            MOD4->MOD4.Copy((STRING)FieldValue);
            break;
        case 36: //mo4t_p Texture Files Hashes
            MOD4.Load();
            MOD4->MO4T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 37: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Copy((STRING)FieldValue);
            break;
        case 38: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Load();
            MOD4->MO4S->value38 = *(FORMID *)FieldValue;
            return true;
        case 39: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Load();
            MOD4->MO4S->value39 = *(SINT32 *)FieldValue;
            break;
        case 40: //ico2 Female icon filename
            ICO2.Copy((STRING)FieldValue);
            break;
        case 41: //mic2 Female mico filename
            MIC2.Copy((STRING)FieldValue);
            break;
        case 42: //bmct Ragdoll Constraint Template
            BMCT.Copy((STRING)FieldValue);
            break;
        case 43: //repl Repair List
            REPL.Load();
            REPL->value43 = *(FORMID *)FieldValue;
            return true;
        case 44: //bipl Biped Model List
            BIPL.Load();
            BIPL->value44 = *(FORMID *)FieldValue;
            return true;
        case 45: //etyp Equipment Type
            ETYPReq.Load();
            ETYPReq->value45 = *(SINT32 *)FieldValue;
            break;
        case 46: //ynam Sound - Pick Up
            YNAM.Load();
            YNAM->value46 = *(FORMID *)FieldValue;
            return true;
        case 47: //znam Sound - Drop
            ZNAM.Load();
            ZNAM->value47 = *(FORMID *)FieldValue;
            return true;
        case 48: //data DATA ,, Struct
            DATA.Load();
            DATA->value48 = *(SINT32 *)FieldValue;
            break;
        case 49: //data DATA ,, Struct
            DATA.Load();
            DATA->value49 = *(SINT32 *)FieldValue;
            break;
        case 50: //data DATA ,, Struct
            DATA.Load();
            DATA->value50 = *(FLOAT32 *)FieldValue;
            break;
        case 51: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value51 = *(SINT16 *)FieldValue;
            break;
        case 52: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value52 = *(UINT16 *)FieldValue;
            break;
        case 53: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value53 = *(FLOAT32 *)FieldValue;
            break;
        case 54: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->value54[0] = ((UINT8 *)FieldValue)[0];
            DNAM->value54[1] = ((UINT8 *)FieldValue)[1];
            DNAM->value54[2] = ((UINT8 *)FieldValue)[2];
            DNAM->value54[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 55: //bnam Overrides Animation Sounds
            BNAM.Load();
            BNAM->value55 = *(UINT32 *)FieldValue;
            break;
        case 56: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value56 = *(FORMID *)FieldValue;
            return true;
        case 57: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value57 = *(UINT8 *)FieldValue;
            break;
        case 58: //snam_p SNAM ,, Struct
            if(ArraySize != 3)
                break;
            SNAM.Load();
            SNAM->value58[0] = ((UINT8 *)FieldValue)[0];
            SNAM->value58[1] = ((UINT8 *)FieldValue)[1];
            SNAM->value58[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 59: //snam SNAM ,, Struct
            SNAM.Load();
            SNAM->value59 = *(UINT32 *)FieldValue;
            break;
        case 60: //tnam Anmation Sounds Template
            TNAM.Load();
            TNAM->value60 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void ARMORecord::DeleteField(FIELD_IDENTIFIERS)
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
            FULL.Unload();
            return;
        case 11: //scri Script
            SCRI.Unload();
            return;
        case 12: //eitm Object Effect
            EITM.Unload();
            return;
        case 13: //bmdt Biped Data
            BMDT.Unload();
            return;
        case 14: //bmdt Biped Data
            BMDT.Unload();
            return;
        case 15: //bmdt_p Biped Data
            BMDT.Unload();
            return;
        case 16: //modl Model Filename
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 17: //modt_p Texture Files Hashes
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 18: //mods Alternate Texture
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 19: //mods Alternate Texture
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 20: //mods Alternate Texture
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 21: //modd FaceGen Model Flags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 22: //mod2 Model Filename
            if(MOD2.IsLoaded())
                MOD2->MOD2.Unload();
            return;
        case 23: //mo2t_p Texture Files Hashes
            if(MOD2.IsLoaded())
                MOD2->MO2T.Unload();
            return;
        case 24: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 25: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 26: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 27: //icon Male icon filename
            ICON.Unload();
            return;
        case 28: //mico Male mico filename
            MICO.Unload();
            return;
        case 29: //mod3 Model Filename
            if(MOD3.IsLoaded())
                MOD3->MOD3.Unload();
            return;
        case 30: //mo3t_p Texture Files Hashes
            if(MOD3.IsLoaded())
                MOD3->MO3T.Unload();
            return;
        case 31: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 32: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 33: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 34: //mosd FaceGen Model Flags
            if(MOD3.IsLoaded())
                MOD3->MOSD.Unload();
            return;
        case 35: //mod4 Model Filename
            if(MOD4.IsLoaded())
                MOD4->MOD4.Unload();
            return;
        case 36: //mo4t_p Texture Files Hashes
            if(MOD4.IsLoaded())
                MOD4->MO4T.Unload();
            return;
        case 37: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 38: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 39: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 40: //ico2 Female icon filename
            ICO2.Unload();
            return;
        case 41: //mic2 Female mico filename
            MIC2.Unload();
            return;
        case 42: //bmct Ragdoll Constraint Template
            BMCT.Unload();
            return;
        case 43: //repl Repair List
            REPL.Unload();
            return;
        case 44: //bipl Biped Model List
            BIPL.Unload();
            return;
        case 45: //etyp Equipment Type
            ETYPReq.Unload();
            return;
        case 46: //ynam Sound - Pick Up
            YNAM.Unload();
            return;
        case 47: //znam Sound - Drop
            ZNAM.Unload();
            return;
        case 48: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 49: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 50: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 51: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 52: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 53: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 54: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 55: //bnam Overrides Animation Sounds
            BNAM.Unload();
            return;
        case 56: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        case 57: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        case 58: //snam_p SNAM ,, Struct
            SNAM.Unload();
            return;
        case 59: //snam SNAM ,, Struct
            SNAM.Unload();
            return;
        case 60: //tnam Anmation Sounds Template
            TNAM.Unload();
            return;
        default:
            return;
        }
    }
}