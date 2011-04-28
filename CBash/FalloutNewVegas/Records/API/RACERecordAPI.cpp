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
#include "..\RACERecord.h"

namespace FNV
{
UINT32 RACERecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //full
            return STRING_FIELD;
        case 8: //description
            return STRING_FIELD;
        case 9: //xnam Relation
            return FORMID_FIELD;
        case 10: //xnam Relation
            return SINT32_FIELD;
        case 11: //xnam Relation
            return UINT32_FIELD;
        case 12: //data DATA ,, Struct
            return SINT8_FIELD;
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
        case 14: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 15: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 16: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 17: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 18: //data DATA ,, Struct
            return UINT32_FIELD;
        case 19: //onam Older
            return FORMID_FIELD;
        case 20: //ynam Younger
            return FORMID_FIELD;
        case 21: //vtck Voices
            return UNPARSED_FIELD;
        case 22: //dnam Default Hair Styles
            return UNPARSED_FIELD;
        case 23: //cnam Default Hair Colors
            return UNPARSED_FIELD;
        case 24: //pnam FaceGen - Main clamp
            return FLOAT32_FIELD;
        case 25: //unam FaceGen - Face clamp
            return FLOAT32_FIELD;
        case 26: //attr_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return ATTR.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 27: //indx Index
            return UINT32_FIELD;
        case 28: //modPath
            return ISTRING_FIELD;
        case 29: //modb
            return FLOAT32_FIELD;
        case 30: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
        case 31: //mods Alternate Textures
            return ISTRING_FIELD;

        case 34: //modelFlags
            return UINT8_FIELD;
        case 35: //iconPath
            return ISTRING_FIELD;
        case 36: //smallIconPath
            return ISTRING_FIELD;
        case 37: //hnam Hairs
            return UNPARSED_FIELD;
        case 38: //enam Eyes
            return UNPARSED_FIELD;
        case 39: //fggs_p FaceGen Geometry-Symmetric
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGGS.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 40: //fgga_p FaceGen Geometry-Asymmetric
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGGA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 41: //fgts_p FaceGen Texture-Symmetric
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGTS.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 42: //snam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

void * RACERecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //full
            return FULL.value;
        case 8: //description
            return DESC.value;
        case 9: //xnam Relation
            return XNAMs.IsLoaded() ? &XNAMs->value9 : NULL;
        case 10: //xnam Relation
            return XNAMs.IsLoaded() ? &XNAMs->value10 : NULL;
        case 11: //xnam Relation
            return XNAMs.IsLoaded() ? &XNAMs->value11 : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value13[0] : NULL;
            return NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value15 : NULL;
        case 16: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value16 : NULL;
        case 17: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value17 : NULL;
        case 18: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value18 : NULL;
        case 19: //onam Older
            return ONAM.IsLoaded() ? &ONAM->value19 : NULL;
        case 20: //ynam Younger
            return YNAM.IsLoaded() ? &YNAM->value20 : NULL;
        case 21: //vtck Voices
            return UNPARSEDGET_FIELD21;
        case 22: //dnam Default Hair Styles
            return UNPARSEDGET_FIELD22;
        case 23: //cnam Default Hair Colors
            return UNPARSEDGET_FIELD23;
        case 24: //pnam FaceGen - Main clamp
            return PNAM.IsLoaded() ? &PNAM->value24 : NULL;
        case 25: //unam FaceGen - Face clamp
            return UNAM.IsLoaded() ? &UNAM->value25 : NULL;
        case 26: //attr_p Unknown
            *FieldValues = ATTR.value;
            return NULL;
        case 27: //indx Index
            return INDX.IsLoaded() ? &INDX->value27 : NULL;
        case 28: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 29: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 30: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 31: //mods Alternate Textures
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 32: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value32 : NULL;
        case 33: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value33 : NULL;
        case 34: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD->value34 : NULL;
        case 35: //iconPath
            return ICON.value;
        case 36: //smallIconPath
            return MICO.value;
        case 37: //hnam Hairs
            return UNPARSEDGET_FIELD37;
        case 38: //enam Eyes
            return UNPARSEDGET_FIELD38;
        case 39: //fggs_p FaceGen Geometry-Symmetric
            *FieldValues = (FGGS.IsLoaded()) ? FGGS->FGGS.value : NULL;
            return NULL;
        case 40: //fgga_p FaceGen Geometry-Asymmetric
            *FieldValues = (FGGS.IsLoaded()) ? FGGS->FGGA.value : NULL;
            return NULL;
        case 41: //fgts_p FaceGen Texture-Symmetric
            *FieldValues = (FGGS.IsLoaded()) ? FGGS->FGTS.value : NULL;
            return NULL;
        case 42: //snam_p Unknown
            *FieldValues = SNAM, cpNormal, True.value;
            return NULL;
        default:
            return NULL;
        }
    }

bool RACERecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 8: //description
            DESC.Copy((STRING)FieldValue);
            break;
        case 9: //xnam Relation
            XNAMs.Load();
            XNAMs->value9 = *(FORMID *)FieldValue;
            return true;
        case 10: //xnam Relation
            XNAMs.Load();
            XNAMs->value10 = *(SINT32 *)FieldValue;
            break;
        case 11: //xnam Relation
            XNAMs.Load();
            XNAMs->value11 = *(UINT32 *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->value12 = *(SINT8 *)FieldValue;
            break;
        case 13: //data_p DATA ,, Struct
            if(ArraySize != 2)
                break;
            DATA.Load();
            DATA->value13[0] = ((UINT8 *)FieldValue)[0];
            DATA->value13[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //data DATA ,, Struct
            DATA.Load();
            DATA->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //data DATA ,, Struct
            DATA.Load();
            DATA->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //data DATA ,, Struct
            DATA.Load();
            DATA->value18 = *(UINT32 *)FieldValue;
            break;
        case 19: //onam Older
            ONAM.Load();
            ONAM->value19 = *(FORMID *)FieldValue;
            return true;
        case 20: //ynam Younger
            YNAM.Load();
            YNAM->value20 = *(FORMID *)FieldValue;
            return true;
        case 21: //vtck Voices
            return UNPARSEDGET_FIELD21;
        case 22: //dnam Default Hair Styles
            return UNPARSEDGET_FIELD22;
        case 23: //cnam Default Hair Colors
            return UNPARSEDGET_FIELD23;
        case 24: //pnam FaceGen - Main clamp
            PNAM.Load();
            PNAM->value24 = *(FLOAT32 *)FieldValue;
            break;
        case 25: //unam FaceGen - Face clamp
            UNAM.Load();
            UNAM->value25 = *(FLOAT32 *)FieldValue;
            break;
        case 26: //attr_p Unknown
            ATTR.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 27: //indx Index
            INDX.Load();
            INDX->value27 = *(UINT32 *)FieldValue;
            break;
        case 28: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 29: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 30: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 31: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 32: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value32 = *(FORMID *)FieldValue;
            return true;
        case 33: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value33 = *(SINT32 *)FieldValue;
            break;
        case 34: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value34 = *(UINT8 *)FieldValue;
            break;
        case 35: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 36: //smallIconPath
            MICO.Copy((STRING)FieldValue);
            break;
        case 37: //hnam Hairs
            return UNPARSEDGET_FIELD37;
        case 38: //enam Eyes
            return UNPARSEDGET_FIELD38;
        case 39: //fggs_p FaceGen Geometry-Symmetric
            FGGS.Load();
            FGGS->FGGS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 40: //fgga_p FaceGen Geometry-Asymmetric
            FGGS.Load();
            FGGS->FGGA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 41: //fgts_p FaceGen Texture-Symmetric
            FGGS.Load();
            FGGS->FGTS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 42: //snam_p Unknown
            SNAM, cpNormal, True.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void RACERecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //full
            FULL.Unload();
            return;
        case 8: //description
            DESC.Unload();
            return;
        case 9: //xnam Relation
            XNAMs.Unload();
            return;
        case 10: //xnam Relation
            XNAMs.Unload();
            return;
        case 11: //xnam Relation
            XNAMs.Unload();
            return;
        case 12: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 13: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 14: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 17: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 18: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 19: //onam Older
            ONAM.Unload();
            return;
        case 20: //ynam Younger
            YNAM.Unload();
            return;
        case 21: //vtck Voices
            return UNPARSEDDEL_FIELD21;
        case 22: //dnam Default Hair Styles
            return UNPARSEDDEL_FIELD22;
        case 23: //cnam Default Hair Colors
            return UNPARSEDDEL_FIELD23;
        case 24: //pnam FaceGen - Main clamp
            PNAM.Unload();
            return;
        case 25: //unam FaceGen - Face clamp
            UNAM.Unload();
            return;
        case 26: //attr_p Unknown
            ATTR.Unload();
            return;
        case 27: //indx Index
            INDX.Unload();
            return;
        case 28: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 29: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 30: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 31: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 32: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 33: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 34: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 35: //iconPath
            ICON.Unload();
            return;
        case 36: //smallIconPath
            MICO.Unload();
            return;
        case 37: //hnam Hairs
            return UNPARSEDDEL_FIELD37;
        case 38: //enam Eyes
            return UNPARSEDDEL_FIELD38;
        case 39: //fggs_p FaceGen Geometry-Symmetric
            if(FGGS.IsLoaded())
                FGGS->FGGS.Unload();
            return;
        case 40: //fgga_p FaceGen Geometry-Asymmetric
            if(FGGS.IsLoaded())
                FGGS->FGGA.Unload();
            return;
        case 41: //fgts_p FaceGen Texture-Symmetric
            if(FGGS.IsLoaded())
                FGGS->FGTS.Unload();
            return;
        case 42: //snam_p Unknown
            SNAM, cpNormal, True.Unload();
            return;
        default:
            return;
        }
    }
}