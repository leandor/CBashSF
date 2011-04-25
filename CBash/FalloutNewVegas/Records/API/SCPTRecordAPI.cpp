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
#include "..\SCPTRecord.h"

namespace FNV
{
UINT32 SCPTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 8: //schr Basic Script Data
            return UINT32_FIELD;
        case 9: //schr Basic Script Data
            return UINT32_FIELD;
        case 10: //schr Basic Script Data
            return UINT32_FIELD;
        case 11: //schr Basic Script Data
            return UINT16_FIELD;
        case 12: //schr Basic Script Data
            return UINT16_FIELD;
        case 13: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 15: //slsd Local Variable Data
            return UINT32_FIELD;
        case 16: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 17: //slsd Local Variable Data
            return UINT8_FIELD;
        case 18: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 19: //scvr Name
            return ISTRING_FIELD;
        case 20: //scro Global Reference
            return FORMID_FIELD;
        case 21: //scrv Local Variable
            return UINT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * SCPTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //schr_p Basic Script Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SCHR->value7[0] : NULL;
            return NULL;
        case 8: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value8 : NULL;
        case 9: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value9 : NULL;
        case 10: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value10 : NULL;
        case 11: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value11 : NULL;
        case 12: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value12 : NULL;
        case 13: //scda_p Compiled Embedded Script
            *FieldValues = (SCHR.IsLoaded()) ? SCHR->SCDA.value : NULL;
            return NULL;
        case 14: //sctx Embedded Script Source
            return SCHR.IsLoaded() ? SCHR->SCTX.value : NULL;
        case 15: //slsd Local Variable Data
            return SCHR.IsLoaded() ? &SCHR->SLSD->value15 : NULL;
        case 16: //slsd_p Local Variable Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value16[0] : NULL;
            return NULL;
        case 17: //slsd Local Variable Data
            return SCHR.IsLoaded() ? &SCHR->SLSD->value17 : NULL;
        case 18: //slsd_p Local Variable Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value18[0] : NULL;
            return NULL;
        case 19: //scvr Name
            return SCHR.IsLoaded() ? SCHR->SCVR.value : NULL;
        case 20: //scro Global Reference
            return SCHR.IsLoaded() ? &SCHR->SCRO->value20 : NULL;
        case 21: //scrv Local Variable
            return SCHR.IsLoaded() ? &SCHR->SCRV->value21 : NULL;
        default:
            return NULL;
        }
    }

bool SCPTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value7[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SCHR->value7[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SCHR->value7[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SCHR->value7[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 8: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value8 = *(UINT32 *)FieldValue;
            break;
        case 9: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value9 = *(UINT32 *)FieldValue;
            break;
        case 10: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value10 = *(UINT32 *)FieldValue;
            break;
        case 11: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value11 = *(UINT16 *)FieldValue;
            break;
        case 12: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value12 = *(UINT16 *)FieldValue;
            break;
        case 13: //scda_p Compiled Embedded Script
            SCHR.Load();
            SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 14: //sctx Embedded Script Source
            SCHR.Load();
            SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 15: //slsd Local Variable Data
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value15 = *(UINT32 *)FieldValue;
            break;
        case 16: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value16[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SLSD->value16[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SLSD->value16[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SLSD->value16[3] = ((UINT8 *)FieldValue)[3];
            SCHR->SLSD->value16[4] = ((UINT8 *)FieldValue)[4];
            SCHR->SLSD->value16[5] = ((UINT8 *)FieldValue)[5];
            SCHR->SLSD->value16[6] = ((UINT8 *)FieldValue)[6];
            SCHR->SLSD->value16[7] = ((UINT8 *)FieldValue)[7];
            SCHR->SLSD->value16[8] = ((UINT8 *)FieldValue)[8];
            SCHR->SLSD->value16[9] = ((UINT8 *)FieldValue)[9];
            SCHR->SLSD->value16[10] = ((UINT8 *)FieldValue)[10];
            SCHR->SLSD->value16[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 17: //slsd Local Variable Data
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value17 = *(UINT8 *)FieldValue;
            break;
        case 18: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value18[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SLSD->value18[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SLSD->value18[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SLSD->value18[3] = ((UINT8 *)FieldValue)[3];
            SCHR->SLSD->value18[4] = ((UINT8 *)FieldValue)[4];
            SCHR->SLSD->value18[5] = ((UINT8 *)FieldValue)[5];
            SCHR->SLSD->value18[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 19: //scvr Name
            SCHR.Load();
            SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 20: //scro Global Reference
            SCHR.Load();
            SCHR->SCRO.Load();
            SCHR->SCRO->value20 = *(FORMID *)FieldValue;
            return true;
        case 21: //scrv Local Variable
            SCHR.Load();
            SCHR->SCRV.Load();
            SCHR->SCRV->value21 = *(UINT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void SCPTRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //schr_p Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 8: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 9: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 10: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 11: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 12: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 13: //scda_p Compiled Embedded Script
            if(SCHR.IsLoaded())
                SCHR->SCDA.Unload();
            return;
        case 14: //sctx Embedded Script Source
            if(SCHR.IsLoaded())
                SCHR->SCTX.Unload();
            return;
        case 15: //slsd Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 16: //slsd_p Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 17: //slsd Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 18: //slsd_p Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 19: //scvr Name
            if(SCHR.IsLoaded())
                SCHR->SCVR.Unload();
            return;
        case 20: //scro Global Reference
            if(SCHR.IsLoaded())
                SCHR->SCRO.Unload();
            return;
        case 21: //scrv Local Variable
            if(SCHR.IsLoaded())
                SCHR->SCRV.Unload();
            return;
        default:
            return;
        }
    }
}