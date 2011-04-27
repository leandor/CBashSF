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
#include "..\INGRRecord.h"

namespace FNV
{
UINT32 INGRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 21: //etyp Equipment Type
            return SINT32_FIELD;
        case 22: //data Weight
            return FLOAT32_FIELD;
        case 23: //enit ENIT ,, Struct
            return SINT32_FIELD;
        case 24: //enit ENIT ,, Struct
            return UINT8_FIELD;
        case 25: //enit_p ENIT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 26: //efid Base Effect
            return FORMID_FIELD;
        case 27: //efit Effect Item
            return UINT32_FIELD;
        case 28: //efit Effect Item
            return UINT32_FIELD;
        case 29: //efit Effect Item
            return UINT32_FIELD;
        case 30: //efit Effect Item
            return UINT32_FIELD;
        case 31: //efit Effect Item
            return UNPARSED_FIELD;
        case 32: //ctda Conditions
            return UINT8_FIELD;
        case 33: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 34: //ctda Conditions
            return UNPARSED_FIELD;
        case 35: //ctda Conditions
            return UINT32_FIELD;
        case 36: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 37: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 38: //ctda Conditions
            return UINT32_FIELD;
        case 39: //ctda Conditions
            return UNPARSED_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * INGRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
            return FULL.value;
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
        case 21: //etyp Equipment Type
            return ETYPReq.IsLoaded() ? &ETYPReq->value21 : NULL;
        case 22: //data Weight
            return DATA.IsLoaded() ? &DATA->value22 : NULL;
        case 23: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value23 : NULL;
        case 24: //enit ENIT ,, Struct
            return ENIT.IsLoaded() ? &ENIT->value24 : NULL;
        case 25: //enit_p ENIT ,, Struct
            *FieldValues = ENIT.IsLoaded() ? &ENIT->value25[0] : NULL;
            return NULL;
        case 26: //efid Base Effect
            return EFID.IsLoaded() ? &EFID->EFID->value26 : NULL;
        case 27: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value27 : NULL;
        case 28: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value28 : NULL;
        case 29: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value29 : NULL;
        case 30: //efit Effect Item
            return EFID.IsLoaded() ? &EFID->EFIT->value30 : NULL;
        case 31: //efit Effect Item
            return UNPARSEDGET_FIELD31;
        case 32: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value32 : NULL;
        case 33: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value33[0] : NULL;
            return NULL;
        case 34: //ctda Conditions
            return UNPARSEDGET_FIELD34;
        case 35: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value35 : NULL;
        case 36: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value36[0] : NULL;
            return NULL;
        case 37: //ctda_p Conditions
            *FieldValues = EFID.IsLoaded() ? &EFID->CTDA->value37[0] : NULL;
            return NULL;
        case 38: //ctda Conditions
            return EFID.IsLoaded() ? &EFID->CTDA->value38 : NULL;
        case 39: //ctda Conditions
            return UNPARSEDGET_FIELD39;
        default:
            return NULL;
        }
    }

bool INGRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
            FULL.Copy((STRING)FieldValue);
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
        case 21: //etyp Equipment Type
            ETYPReq.Load();
            ETYPReq->value21 = *(SINT32 *)FieldValue;
            break;
        case 22: //data Weight
            DATA.Load();
            DATA->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value23 = *(SINT32 *)FieldValue;
            break;
        case 24: //enit ENIT ,, Struct
            ENIT.Load();
            ENIT->value24 = *(UINT8 *)FieldValue;
            break;
        case 25: //enit_p ENIT ,, Struct
            if(ArraySize != 3)
                break;
            ENIT.Load();
            ENIT->value25[0] = ((UINT8 *)FieldValue)[0];
            ENIT->value25[1] = ((UINT8 *)FieldValue)[1];
            ENIT->value25[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 26: //efid Base Effect
            EFID.Load();
            EFID->EFID.Load();
            EFID->EFID->value26 = *(FORMID *)FieldValue;
            return true;
        case 27: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value27 = *(UINT32 *)FieldValue;
            break;
        case 28: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value28 = *(UINT32 *)FieldValue;
            break;
        case 29: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value29 = *(UINT32 *)FieldValue;
            break;
        case 30: //efit Effect Item
            EFID.Load();
            EFID->EFIT.Load();
            EFID->EFIT->value30 = *(UINT32 *)FieldValue;
            break;
        case 31: //efit Effect Item
            return UNPARSEDGET_FIELD31;
        case 32: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value32 = *(UINT8 *)FieldValue;
            break;
        case 33: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value33[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value33[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value33[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 34: //ctda Conditions
            return UNPARSEDGET_FIELD34;
        case 35: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value35 = *(UINT32 *)FieldValue;
            break;
        case 36: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value36[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value36[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value36[2] = ((UINT8 *)FieldValue)[2];
            EFID->CTDA->value36[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 37: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value37[0] = ((UINT8 *)FieldValue)[0];
            EFID->CTDA->value37[1] = ((UINT8 *)FieldValue)[1];
            EFID->CTDA->value37[2] = ((UINT8 *)FieldValue)[2];
            EFID->CTDA->value37[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 38: //ctda Conditions
            EFID.Load();
            EFID->CTDA.Load();
            EFID->CTDA->value38 = *(UINT32 *)FieldValue;
            break;
        case 39: //ctda Conditions
            return UNPARSEDGET_FIELD39;
        default:
            break;
        }
    return false;
    }

void INGRRecord::DeleteField(FIELD_IDENTIFIERS)
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
            FULL.Unload();
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
        case 21: //etyp Equipment Type
            ETYPReq.Unload();
            return;
        case 22: //data Weight
            DATA.Unload();
            return;
        case 23: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 24: //enit ENIT ,, Struct
            ENIT.Unload();
            return;
        case 25: //enit_p ENIT ,, Struct
            ENIT.Unload();
            return;
        case 26: //efid Base Effect
            if(EFID.IsLoaded())
                EFID->EFID.Unload();
            return;
        case 27: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 28: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 29: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 30: //efit Effect Item
            if(EFID.IsLoaded())
                EFID->EFIT.Unload();
            return;
        case 31: //efit Effect Item
            return UNPARSEDDEL_FIELD31;
        case 32: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 33: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 34: //ctda Conditions
            return UNPARSEDDEL_FIELD34;
        case 35: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 36: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 37: //ctda_p Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 38: //ctda Conditions
            if(EFID.IsLoaded())
                EFID->CTDA.Unload();
            return;
        case 39: //ctda Conditions
            return UNPARSEDDEL_FIELD39;
        default:
            return;
        }
    }
}