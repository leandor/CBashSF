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
#include "..\TERMRecord.h"

namespace FNV
{
UINT32 TERMRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 33: //desc Description
            return STRING_FIELD;
        case 34: //snam Sound - Looping
            return FORMID_FIELD;
        case 35: //pnam Password Note
            return FORMID_FIELD;
        case 36: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 37: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 38: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 39: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 40: //itxt Item Text
            return ISTRING_FIELD;
        case 41: //rnam Result Text
            return ISTRING_FIELD;
        case 42: //anam Flags
            return UINT8_FIELD;
        case 43: //inam Display Note
            return FORMID_FIELD;
        case 44: //tnam Sub Menu
            return FORMID_FIELD;
        case 45: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 46: //schr Basic Script Data
            return UINT32_FIELD;
        case 47: //schr Basic Script Data
            return UINT32_FIELD;
        case 48: //schr Basic Script Data
            return UINT32_FIELD;
        case 49: //schr Basic Script Data
            return UINT16_FIELD;
        case 50: //schr Basic Script Data
            return UINT16_FIELD;
        case 51: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 52: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 53: //slsd Local Variable Data
            return UINT32_FIELD;
        case 54: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 55: //slsd Local Variable Data
            return UINT8_FIELD;
        case 56: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 57: //scvr Name
            return ISTRING_FIELD;
        case 58: //scro Global Reference
            return FORMID_FIELD;
        case 59: //scrv Local Variable
            return UINT32_FIELD;
        case 60: //ctda Conditions
            return UINT8_FIELD;
        case 61: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 62: //ctda Conditions
            return UNPARSED_FIELD;
        case 63: //ctda Conditions
            return UINT32_FIELD;
        case 64: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 65: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 66: //ctda Conditions
            return UINT32_FIELD;
        case 67: //ctda Conditions
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * TERMRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 33: //desc Description
            return DESCReq.value;
        case 34: //snam Sound - Looping
            return SNAM.IsLoaded() ? &SNAM->value34 : NULL;
        case 35: //pnam Password Note
            return PNAM.IsLoaded() ? &PNAM->value35 : NULL;
        case 36: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value36 : NULL;
        case 37: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value37 : NULL;
        case 38: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value38 : NULL;
        case 39: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value39[0] : NULL;
            return NULL;
        case 40: //itxt Item Text
            return ITXT.IsLoaded() ? ITXT->ITXT.value : NULL;
        case 41: //rnam Result Text
            return ITXT.IsLoaded() ? ITXT->RNAM.value : NULL;
        case 42: //anam Flags
            return ITXT.IsLoaded() ? &ITXT->ANAM->value42 : NULL;
        case 43: //inam Display Note
            return INAM.IsLoaded() ? &INAM->value43 : NULL;
        case 44: //tnam Sub Menu
            return TNAM.IsLoaded() ? &TNAM->value44 : NULL;
        case 45: //schr_p Basic Script Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SCHR->value45[0] : NULL;
            return NULL;
        case 46: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value46 : NULL;
        case 47: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value47 : NULL;
        case 48: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value48 : NULL;
        case 49: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value49 : NULL;
        case 50: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value50 : NULL;
        case 51: //scda_p Compiled Embedded Script
            *FieldValues = (SCHR.IsLoaded()) ? SCHR->SCDA.value : NULL;
            return NULL;
        case 52: //sctx Embedded Script Source
            return SCHR.IsLoaded() ? SCHR->SCTX.value : NULL;
        case 53: //slsd Local Variable Data
            return SCHR.IsLoaded() ? &SCHR->SLSD->value53 : NULL;
        case 54: //slsd_p Local Variable Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value54[0] : NULL;
            return NULL;
        case 55: //slsd Local Variable Data
            return SCHR.IsLoaded() ? &SCHR->SLSD->value55 : NULL;
        case 56: //slsd_p Local Variable Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value56[0] : NULL;
            return NULL;
        case 57: //scvr Name
            return SCHR.IsLoaded() ? SCHR->SCVR.value : NULL;
        case 58: //scro Global Reference
            return SCHR.IsLoaded() ? &SCHR->SCRO->value58 : NULL;
        case 59: //scrv Local Variable
            return SCHR.IsLoaded() ? &SCHR->SCRV->value59 : NULL;
        case 60: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value60 : NULL;
        case 61: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value61[0] : NULL;
            return NULL;
        case 62: //ctda Conditions
            return UNPARSEDGET_FIELD62;
        case 63: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value63 : NULL;
        case 64: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value64[0] : NULL;
            return NULL;
        case 65: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value65[0] : NULL;
            return NULL;
        case 66: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value66 : NULL;
        case 67: //ctda Conditions
            return UNPARSEDGET_FIELD67;
        default:
            return NULL;
        }
    }

bool TERMRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 33: //desc Description
            DESCReq.Copy((STRING)FieldValue);
            break;
        case 34: //snam Sound - Looping
            SNAM.Load();
            SNAM->value34 = *(FORMID *)FieldValue;
            return true;
        case 35: //pnam Password Note
            PNAM.Load();
            PNAM->value35 = *(FORMID *)FieldValue;
            return true;
        case 36: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value36 = *(UINT8 *)FieldValue;
            break;
        case 37: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value37 = *(UINT8 *)FieldValue;
            break;
        case 38: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value38 = *(UINT8 *)FieldValue;
            break;
        case 39: //dnam_p DNAM ,, Struct
            if(ArraySize != 1)
                break;
            DNAM.Load();
            DNAM->value39[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 40: //itxt Item Text
            ITXT.Load();
            ITXT->ITXT.Copy((STRING)FieldValue);
            break;
        case 41: //rnam Result Text
            ITXT.Load();
            ITXT->RNAM.Copy((STRING)FieldValue);
            break;
        case 42: //anam Flags
            ITXT.Load();
            ITXT->ANAM.Load();
            ITXT->ANAM->value42 = *(UINT8 *)FieldValue;
            break;
        case 43: //inam Display Note
            INAM.Load();
            INAM->value43 = *(FORMID *)FieldValue;
            return true;
        case 44: //tnam Sub Menu
            TNAM.Load();
            TNAM->value44 = *(FORMID *)FieldValue;
            return true;
        case 45: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value45[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SCHR->value45[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SCHR->value45[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SCHR->value45[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 46: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value46 = *(UINT32 *)FieldValue;
            break;
        case 47: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value47 = *(UINT32 *)FieldValue;
            break;
        case 48: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value48 = *(UINT32 *)FieldValue;
            break;
        case 49: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value49 = *(UINT16 *)FieldValue;
            break;
        case 50: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value50 = *(UINT16 *)FieldValue;
            break;
        case 51: //scda_p Compiled Embedded Script
            SCHR.Load();
            SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 52: //sctx Embedded Script Source
            SCHR.Load();
            SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 53: //slsd Local Variable Data
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value53 = *(UINT32 *)FieldValue;
            break;
        case 54: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value54[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SLSD->value54[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SLSD->value54[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SLSD->value54[3] = ((UINT8 *)FieldValue)[3];
            SCHR->SLSD->value54[4] = ((UINT8 *)FieldValue)[4];
            SCHR->SLSD->value54[5] = ((UINT8 *)FieldValue)[5];
            SCHR->SLSD->value54[6] = ((UINT8 *)FieldValue)[6];
            SCHR->SLSD->value54[7] = ((UINT8 *)FieldValue)[7];
            SCHR->SLSD->value54[8] = ((UINT8 *)FieldValue)[8];
            SCHR->SLSD->value54[9] = ((UINT8 *)FieldValue)[9];
            SCHR->SLSD->value54[10] = ((UINT8 *)FieldValue)[10];
            SCHR->SLSD->value54[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 55: //slsd Local Variable Data
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value55 = *(UINT8 *)FieldValue;
            break;
        case 56: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value56[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SLSD->value56[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SLSD->value56[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SLSD->value56[3] = ((UINT8 *)FieldValue)[3];
            SCHR->SLSD->value56[4] = ((UINT8 *)FieldValue)[4];
            SCHR->SLSD->value56[5] = ((UINT8 *)FieldValue)[5];
            SCHR->SLSD->value56[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 57: //scvr Name
            SCHR.Load();
            SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 58: //scro Global Reference
            SCHR.Load();
            SCHR->SCRO.Load();
            SCHR->SCRO->value58 = *(FORMID *)FieldValue;
            return true;
        case 59: //scrv Local Variable
            SCHR.Load();
            SCHR->SCRV.Load();
            SCHR->SCRV->value59 = *(UINT32 *)FieldValue;
            break;
        case 60: //ctda Conditions
            CTDAs.Load();
            CTDAs->value60 = *(UINT8 *)FieldValue;
            break;
        case 61: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            CTDAs.Load();
            CTDAs->value61[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value61[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value61[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 62: //ctda Conditions
            return UNPARSEDGET_FIELD62;
        case 63: //ctda Conditions
            CTDAs.Load();
            CTDAs->value63 = *(UINT32 *)FieldValue;
            break;
        case 64: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value64[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value64[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value64[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value64[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 65: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value65[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value65[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value65[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value65[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 66: //ctda Conditions
            CTDAs.Load();
            CTDAs->value66 = *(UINT32 *)FieldValue;
            break;
        case 67: //ctda Conditions
            return UNPARSEDGET_FIELD67;
        default:
            break;
        }
    return false;
    }

void TERMRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 33: //desc Description
            DESCReq.Unload();
            return;
        case 34: //snam Sound - Looping
            SNAM.Unload();
            return;
        case 35: //pnam Password Note
            PNAM.Unload();
            return;
        case 36: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 37: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 38: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 39: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 40: //itxt Item Text
            if(ITXT.IsLoaded())
                ITXT->ITXT.Unload();
            return;
        case 41: //rnam Result Text
            if(ITXT.IsLoaded())
                ITXT->RNAM.Unload();
            return;
        case 42: //anam Flags
            if(ITXT.IsLoaded())
                ITXT->ANAM.Unload();
            return;
        case 43: //inam Display Note
            INAM.Unload();
            return;
        case 44: //tnam Sub Menu
            TNAM.Unload();
            return;
        case 45: //schr_p Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 46: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 47: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 48: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 49: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 50: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 51: //scda_p Compiled Embedded Script
            if(SCHR.IsLoaded())
                SCHR->SCDA.Unload();
            return;
        case 52: //sctx Embedded Script Source
            if(SCHR.IsLoaded())
                SCHR->SCTX.Unload();
            return;
        case 53: //slsd Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 54: //slsd_p Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 55: //slsd Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 56: //slsd_p Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 57: //scvr Name
            if(SCHR.IsLoaded())
                SCHR->SCVR.Unload();
            return;
        case 58: //scro Global Reference
            if(SCHR.IsLoaded())
                SCHR->SCRO.Unload();
            return;
        case 59: //scrv Local Variable
            if(SCHR.IsLoaded())
                SCHR->SCRV.Unload();
            return;
        case 60: //ctda Conditions
            CTDAs.Unload();
            return;
        case 61: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 62: //ctda Conditions
            return UNPARSEDDEL_FIELD62;
        case 63: //ctda Conditions
            CTDAs.Unload();
            return;
        case 64: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 65: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 66: //ctda Conditions
            CTDAs.Unload();
            return;
        case 67: //ctda Conditions
            return UNPARSEDDEL_FIELD67;
        default:
            return;
        }
    }
}