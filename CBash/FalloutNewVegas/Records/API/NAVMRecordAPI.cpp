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
#include "..\NAVMRecord.h"

namespace FNV
{
UINT32 NAVMRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
            return UNKNOWN_FIELD;
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
            return UNKNOWN_FIELD;
        case 7: //nver Version
            return UINT32_FIELD;
        case 8: //data DATA ,, Struct
            return FORMID_FIELD;
        case 9: //data DATA ,, Struct
            return UINT32_FIELD;
        case 10: //data DATA ,, Struct
            return UINT32_FIELD;
        case 11: //data DATA ,, Struct
            return UINT32_FIELD;
        case 12: //data DATA ,, Struct
            return UINT32_FIELD;
        case 13: //data DATA ,, Struct
            return UINT32_FIELD;
        case 14: //nvvx NVVX ,, Struct
            return FLOAT32_FIELD;
        case 15: //nvvx NVVX ,, Struct
            return FLOAT32_FIELD;
        case 16: //nvvx NVVX ,, Struct
            return FLOAT32_FIELD;
        case 17: //nvtr NVTR ,, Struct
            return SINT16_FIELD;
        case 18: //nvtr NVTR ,, Struct
            return SINT16_FIELD;
        case 19: //nvtr NVTR ,, Struct
            return UINT32_FIELD;
        case 20: //nvca Unknown
            return UNPARSED_FIELD;
        case 21: //nvdp NVDP ,, Struct
            return FORMID_FIELD;
        case 22: //nvdp NVDP ,, Struct
            return UINT16_FIELD;
        case 23: //nvdp_p NVDP ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 24: //nvgd_p NVGD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NVGD.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 25: //nvgd_p NVGD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 26: //nvgd NVGD ,, Struct
            return FLOAT32_FIELD;
        case 27: //nvgd NVGD ,, Struct
            return FLOAT32_FIELD;
        case 28: //nvgd NVGD ,, Struct
            return FLOAT32_FIELD;
        case 29: //nvgd NVGD ,, Struct
            return FLOAT32_FIELD;
        case 30: //nvgd NVGD ,, Struct
            return FLOAT32_FIELD;
        case 31: //nvgd NVGD ,, Struct
            return FLOAT32_FIELD;
        case 32: //nvgd NVGD ,, Struct
            return FLOAT32_FIELD;
        case 33: //nvgd NVGD ,, Struct
            return FLOAT32_FIELD;
        case 34: //nvgd NVGD ,, Struct
            return UINT16_FIELD;
        case 35: //nvex_p NVEX ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 36: //nvex NVEX ,, Struct
            return FORMID_FIELD;
        case 37: //nvex NVEX ,, Struct
            return UINT16_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * NAVMRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //nver Version
            return NVER.IsLoaded() ? &NVER->value7 : NULL;
        case 8: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value8 : NULL;
        case 9: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value9 : NULL;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value10 : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value11 : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value13 : NULL;
        case 14: //nvvx NVVX ,, Struct
            return NVVX.IsLoaded() ? &NVVX->value14 : NULL;
        case 15: //nvvx NVVX ,, Struct
            return NVVX.IsLoaded() ? &NVVX->value15 : NULL;
        case 16: //nvvx NVVX ,, Struct
            return NVVX.IsLoaded() ? &NVVX->value16 : NULL;
        case 17: //nvtr NVTR ,, Struct
            return NVTR.IsLoaded() ? &NVTR->value17 : NULL;
        case 18: //nvtr NVTR ,, Struct
            return NVTR.IsLoaded() ? &NVTR->value18 : NULL;
        case 19: //nvtr NVTR ,, Struct
            return NVTR.IsLoaded() ? &NVTR->value19 : NULL;
        case 20: //nvca Unknown
            return UNPARSEDGET_FIELD20;
        case 21: //nvdp NVDP ,, Struct
            return NVDP.IsLoaded() ? &NVDP->value21 : NULL;
        case 22: //nvdp NVDP ,, Struct
            return NVDP.IsLoaded() ? &NVDP->value22 : NULL;
        case 23: //nvdp_p NVDP ,, Struct
            *FieldValues = NVDP.IsLoaded() ? &NVDP->value23[0] : NULL;
            return NULL;
        case 24: //nvgd_p NVGD ,, Struct
            *FieldValues = NVGD.value;
            return NULL;
        case 25: //nvgd_p NVGD ,, Struct
            *FieldValues = NVGD.IsLoaded() ? &NVGD->value25[0] : NULL;
            return NULL;
        case 26: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value26 : NULL;
        case 27: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value27 : NULL;
        case 28: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value28 : NULL;
        case 29: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value29 : NULL;
        case 30: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value30 : NULL;
        case 31: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value31 : NULL;
        case 32: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value32 : NULL;
        case 33: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value33 : NULL;
        case 34: //nvgd NVGD ,, Struct
            return NVGD.IsLoaded() ? &NVGD->value34 : NULL;
        case 35: //nvex_p NVEX ,, Struct
            *FieldValues = NVEX.IsLoaded() ? &NVEX->value35[0] : NULL;
            return NULL;
        case 36: //nvex NVEX ,, Struct
            return NVEX.IsLoaded() ? &NVEX->value36 : NULL;
        case 37: //nvex NVEX ,, Struct
            return NVEX.IsLoaded() ? &NVEX->value37 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool NAVMRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
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
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //nver Version
            NVER.Load();
            NVER->value7 = *(UINT32 *)FieldValue;
            break;
        case 8: //data DATA ,, Struct
            DATA.Load();
            DATA->value8 = *(FORMID *)FieldValue;
            return true;
        case 9: //data DATA ,, Struct
            DATA.Load();
            DATA->value9 = *(UINT32 *)FieldValue;
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->value10 = *(UINT32 *)FieldValue;
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->value11 = *(UINT32 *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->value12 = *(UINT32 *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->value13 = *(UINT32 *)FieldValue;
            break;
        case 14: //nvvx NVVX ,, Struct
            NVVX.Load();
            NVVX->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //nvvx NVVX ,, Struct
            NVVX.Load();
            NVVX->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //nvvx NVVX ,, Struct
            NVVX.Load();
            NVVX->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //nvtr NVTR ,, Struct
            NVTR.Load();
            NVTR->value17 = *(SINT16 *)FieldValue;
            break;
        case 18: //nvtr NVTR ,, Struct
            NVTR.Load();
            NVTR->value18 = *(SINT16 *)FieldValue;
            break;
        case 19: //nvtr NVTR ,, Struct
            NVTR.Load();
            NVTR->value19 = *(UINT32 *)FieldValue;
            break;
        case 20: //nvca Unknown
            return UNPARSEDGET_FIELD20;
        case 21: //nvdp NVDP ,, Struct
            NVDP.Load();
            NVDP->value21 = *(FORMID *)FieldValue;
            return true;
        case 22: //nvdp NVDP ,, Struct
            NVDP.Load();
            NVDP->value22 = *(UINT16 *)FieldValue;
            break;
        case 23: //nvdp_p NVDP ,, Struct
            if(ArraySize != 2)
                break;
            NVDP.Load();
            NVDP->value23[0] = ((UINT8ARRAY)FieldValue)[0];
            NVDP->value23[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 24: //nvgd_p NVGD ,, Struct
            NVGD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 25: //nvgd_p NVGD ,, Struct
            if(ArraySize != 4)
                break;
            NVGD.Load();
            NVGD->value25[0] = ((UINT8ARRAY)FieldValue)[0];
            NVGD->value25[1] = ((UINT8ARRAY)FieldValue)[1];
            NVGD->value25[2] = ((UINT8ARRAY)FieldValue)[2];
            NVGD->value25[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 26: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value27 = *(FLOAT32 *)FieldValue;
            break;
        case 28: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value28 = *(FLOAT32 *)FieldValue;
            break;
        case 29: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value29 = *(FLOAT32 *)FieldValue;
            break;
        case 30: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value30 = *(FLOAT32 *)FieldValue;
            break;
        case 31: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value31 = *(FLOAT32 *)FieldValue;
            break;
        case 32: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value32 = *(FLOAT32 *)FieldValue;
            break;
        case 33: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value33 = *(FLOAT32 *)FieldValue;
            break;
        case 34: //nvgd NVGD ,, Struct
            NVGD.Load();
            NVGD->value34 = *(UINT16 *)FieldValue;
            break;
        case 35: //nvex_p NVEX ,, Struct
            if(ArraySize != 4)
                break;
            NVEX.Load();
            NVEX->value35[0] = ((UINT8ARRAY)FieldValue)[0];
            NVEX->value35[1] = ((UINT8ARRAY)FieldValue)[1];
            NVEX->value35[2] = ((UINT8ARRAY)FieldValue)[2];
            NVEX->value35[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 36: //nvex NVEX ,, Struct
            NVEX.Load();
            NVEX->value36 = *(FORMID *)FieldValue;
            return true;
        case 37: //nvex NVEX ,, Struct
            NVEX.Load();
            NVEX->value37 = *(UINT16 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void NAVMRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //nver Version
            NVER.Unload();
            return;
        case 8: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 9: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 10: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 11: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 12: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 13: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 14: //nvvx NVVX ,, Struct
            NVVX.Unload();
            return;
        case 15: //nvvx NVVX ,, Struct
            NVVX.Unload();
            return;
        case 16: //nvvx NVVX ,, Struct
            NVVX.Unload();
            return;
        case 17: //nvtr NVTR ,, Struct
            NVTR.Unload();
            return;
        case 18: //nvtr NVTR ,, Struct
            NVTR.Unload();
            return;
        case 19: //nvtr NVTR ,, Struct
            NVTR.Unload();
            return;
        case 20: //nvca Unknown
            return UNPARSEDDEL_FIELD20;
        case 21: //nvdp NVDP ,, Struct
            NVDP.Unload();
            return;
        case 22: //nvdp NVDP ,, Struct
            NVDP.Unload();
            return;
        case 23: //nvdp_p NVDP ,, Struct
            NVDP.Unload();
            return;
        case 24: //nvgd_p NVGD ,, Struct
            NVGD.Unload();
            return;
        case 25: //nvgd_p NVGD ,, Struct
            NVGD.Unload();
            return;
        case 26: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 27: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 28: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 29: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 30: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 31: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 32: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 33: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 34: //nvgd NVGD ,, Struct
            NVGD.Unload();
            return;
        case 35: //nvex_p NVEX ,, Struct
            NVEX.Unload();
            return;
        case 36: //nvex NVEX ,, Struct
            NVEX.Unload();
            return;
        case 37: //nvex NVEX ,, Struct
            NVEX.Unload();
            return;
        default:
            return;
        }
    }
}