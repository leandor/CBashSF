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
#include "..\QUSTRecord.h"

namespace FNV
{
UINT32 QUSTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //scri Script
            return FORMID_FIELD;
        case 8: //full Name
            return STRING_FIELD;
        case 9: //icon Large Icon Filename
            return ISTRING_FIELD;
        case 10: //mico Small Icon Filename
            return ISTRING_FIELD;
        case 11: //data DATA ,, Struct
            return UINT8_FIELD;
        case 12: //data DATA ,, Struct
            return UINT8_FIELD;
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
        case 15: //ctda Conditions
            return UINT8_FIELD;
        case 16: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 17: //ctda Conditions
            return UNPARSED_FIELD;
        case 18: //ctda Conditions
            return UINT32_FIELD;
        case 19: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 20: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 21: //ctda Conditions
            return UINT32_FIELD;
        case 22: //ctda Conditions
            return UNPARSED_FIELD;
        case 23: //indx Stage Index
            return SINT16_FIELD;
        case 24: //qsdt Stage Flags
            return UINT8_FIELD;
        case 25: //cnam Log Entry
            return ISTRING_FIELD;
        case 26: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 27: //schr Basic Script Data
            return UINT32_FIELD;
        case 28: //schr Basic Script Data
            return UINT32_FIELD;
        case 29: //schr Basic Script Data
            return UINT32_FIELD;
        case 30: //schr Basic Script Data
            return UINT16_FIELD;
        case 31: //schr Basic Script Data
            return UINT16_FIELD;
        case 32: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 33: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 34: //slsd Local Variable Data
            return UINT32_FIELD;
        case 35: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 36: //slsd Local Variable Data
            return UINT8_FIELD;
        case 37: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 38: //scvr Name
            return ISTRING_FIELD;
        case 39: //scro Global Reference
            return FORMID_FIELD;
        case 40: //scrv Local Variable
            return UINT32_FIELD;
        case 41: //nam0 Next Quest
            return FORMID_FIELD;
        case 42: //qobj Objective Index
            return SINT32_FIELD;
        case 43: //nnam Description
            return ISTRING_FIELD;
        case 44: //qsta QSTA ,, Struct
            return FORMID_FIELD;
        case 45: //qsta QSTA ,, Struct
            return UINT8_FIELD;
        case 46: //qsta_p QSTA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

void * QUSTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //scri Script
            return SCRI.IsLoaded() ? &SCRI->value7 : NULL;
        case 8: //full Name
            return FULL.value;
        case 9: //icon Large Icon Filename
            return ICON.IsLoaded() ? ICON->ICON.value : NULL;
        case 10: //mico Small Icon Filename
            return ICON.IsLoaded() ? ICON->MICO.value : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value11 : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value13[0] : NULL;
            return NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value15 : NULL;
        case 16: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value16[0] : NULL;
            return NULL;
        case 17: //ctda Conditions
            return UNPARSEDGET_FIELD17;
        case 18: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value18 : NULL;
        case 19: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value19[0] : NULL;
            return NULL;
        case 20: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value20[0] : NULL;
            return NULL;
        case 21: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value21 : NULL;
        case 22: //ctda Conditions
            return UNPARSEDGET_FIELD22;
        case 23: //indx Stage Index
            return INDX.IsLoaded() ? &INDX->value23 : NULL;
        case 24: //qsdt Stage Flags
            return QSDT.IsLoaded() ? &QSDT->value24 : NULL;
        case 25: //cnam Log Entry
            return CNAM.value;
        case 26: //schr_p Basic Script Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SCHR->value26[0] : NULL;
            return NULL;
        case 27: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value27 : NULL;
        case 28: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value28 : NULL;
        case 29: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value29 : NULL;
        case 30: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value30 : NULL;
        case 31: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value31 : NULL;
        case 32: //scda_p Compiled Embedded Script
            *FieldValues = (SCHR.IsLoaded()) ? SCHR->SCDA.value : NULL;
            return NULL;
        case 33: //sctx Embedded Script Source
            return SCHR.IsLoaded() ? SCHR->SCTX.value : NULL;
        case 34: //slsd Local Variable Data
            return SCHR.IsLoaded() ? &SCHR->SLSD->value34 : NULL;
        case 35: //slsd_p Local Variable Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value35[0] : NULL;
            return NULL;
        case 36: //slsd Local Variable Data
            return SCHR.IsLoaded() ? &SCHR->SLSD->value36 : NULL;
        case 37: //slsd_p Local Variable Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value37[0] : NULL;
            return NULL;
        case 38: //scvr Name
            return SCHR.IsLoaded() ? SCHR->SCVR.value : NULL;
        case 39: //scro Global Reference
            return SCHR.IsLoaded() ? &SCHR->SCRO->value39 : NULL;
        case 40: //scrv Local Variable
            return SCHR.IsLoaded() ? &SCHR->SCRV->value40 : NULL;
        case 41: //nam0 Next Quest
            return NAM0.IsLoaded() ? &NAM0->value41 : NULL;
        case 42: //qobj Objective Index
            return QOBJ.IsLoaded() ? &QOBJ->value42 : NULL;
        case 43: //nnam Description
            return NNAM.value;
        case 44: //qsta QSTA ,, Struct
            return QSTA.IsLoaded() ? &QSTA->value44 : NULL;
        case 45: //qsta QSTA ,, Struct
            return QSTA.IsLoaded() ? &QSTA->value45 : NULL;
        case 46: //qsta_p QSTA ,, Struct
            *FieldValues = QSTA.IsLoaded() ? &QSTA->value46[0] : NULL;
            return NULL;
        default:
            return NULL;
        }
    }

bool QUSTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //scri Script
            SCRI.Load();
            SCRI->value7 = *(FORMID *)FieldValue;
            return true;
        case 8: //full Name
            FULL.Copy((STRING)FieldValue);
            break;
        case 9: //icon Large Icon Filename
            ICON.Load();
            ICON->ICON.Copy((STRING)FieldValue);
            break;
        case 10: //mico Small Icon Filename
            ICON.Load();
            ICON->MICO.Copy((STRING)FieldValue);
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->value12 = *(UINT8 *)FieldValue;
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
        case 15: //ctda Conditions
            CTDAs.Load();
            CTDAs->value15 = *(UINT8 *)FieldValue;
            break;
        case 16: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            CTDAs.Load();
            CTDAs->value16[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value16[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value16[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 17: //ctda Conditions
            return UNPARSEDGET_FIELD17;
        case 18: //ctda Conditions
            CTDAs.Load();
            CTDAs->value18 = *(UINT32 *)FieldValue;
            break;
        case 19: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value19[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value19[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value19[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value19[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 20: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value20[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value20[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value20[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value20[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 21: //ctda Conditions
            CTDAs.Load();
            CTDAs->value21 = *(UINT32 *)FieldValue;
            break;
        case 22: //ctda Conditions
            return UNPARSEDGET_FIELD22;
        case 23: //indx Stage Index
            INDX.Load();
            INDX->value23 = *(SINT16 *)FieldValue;
            break;
        case 24: //qsdt Stage Flags
            QSDT.Load();
            QSDT->value24 = *(UINT8 *)FieldValue;
            break;
        case 25: //cnam Log Entry
            CNAM.Copy((STRING)FieldValue);
            break;
        case 26: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value26[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SCHR->value26[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SCHR->value26[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SCHR->value26[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 27: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value27 = *(UINT32 *)FieldValue;
            break;
        case 28: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value28 = *(UINT32 *)FieldValue;
            break;
        case 29: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value29 = *(UINT32 *)FieldValue;
            break;
        case 30: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value30 = *(UINT16 *)FieldValue;
            break;
        case 31: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value31 = *(UINT16 *)FieldValue;
            break;
        case 32: //scda_p Compiled Embedded Script
            SCHR.Load();
            SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 33: //sctx Embedded Script Source
            SCHR.Load();
            SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 34: //slsd Local Variable Data
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value34 = *(UINT32 *)FieldValue;
            break;
        case 35: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value35[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SLSD->value35[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SLSD->value35[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SLSD->value35[3] = ((UINT8 *)FieldValue)[3];
            SCHR->SLSD->value35[4] = ((UINT8 *)FieldValue)[4];
            SCHR->SLSD->value35[5] = ((UINT8 *)FieldValue)[5];
            SCHR->SLSD->value35[6] = ((UINT8 *)FieldValue)[6];
            SCHR->SLSD->value35[7] = ((UINT8 *)FieldValue)[7];
            SCHR->SLSD->value35[8] = ((UINT8 *)FieldValue)[8];
            SCHR->SLSD->value35[9] = ((UINT8 *)FieldValue)[9];
            SCHR->SLSD->value35[10] = ((UINT8 *)FieldValue)[10];
            SCHR->SLSD->value35[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 36: //slsd Local Variable Data
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value36 = *(UINT8 *)FieldValue;
            break;
        case 37: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value37[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SLSD->value37[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SLSD->value37[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SLSD->value37[3] = ((UINT8 *)FieldValue)[3];
            SCHR->SLSD->value37[4] = ((UINT8 *)FieldValue)[4];
            SCHR->SLSD->value37[5] = ((UINT8 *)FieldValue)[5];
            SCHR->SLSD->value37[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 38: //scvr Name
            SCHR.Load();
            SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 39: //scro Global Reference
            SCHR.Load();
            SCHR->SCRO.Load();
            SCHR->SCRO->value39 = *(FORMID *)FieldValue;
            return true;
        case 40: //scrv Local Variable
            SCHR.Load();
            SCHR->SCRV.Load();
            SCHR->SCRV->value40 = *(UINT32 *)FieldValue;
            break;
        case 41: //nam0 Next Quest
            NAM0.Load();
            NAM0->value41 = *(FORMID *)FieldValue;
            return true;
        case 42: //qobj Objective Index
            QOBJ.Load();
            QOBJ->value42 = *(SINT32 *)FieldValue;
            break;
        case 43: //nnam Description
            NNAM.Copy((STRING)FieldValue);
            break;
        case 44: //qsta QSTA ,, Struct
            QSTA.Load();
            QSTA->value44 = *(FORMID *)FieldValue;
            return true;
        case 45: //qsta QSTA ,, Struct
            QSTA.Load();
            QSTA->value45 = *(UINT8 *)FieldValue;
            break;
        case 46: //qsta_p QSTA ,, Struct
            if(ArraySize != 3)
                break;
            QSTA.Load();
            QSTA->value46[0] = ((UINT8 *)FieldValue)[0];
            QSTA->value46[1] = ((UINT8 *)FieldValue)[1];
            QSTA->value46[2] = ((UINT8 *)FieldValue)[2];
            break;
        default:
            break;
        }
    return false;
    }

void QUSTRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //scri Script
            SCRI.Unload();
            return;
        case 8: //full Name
            FULL.Unload();
            return;
        case 9: //icon Large Icon Filename
            if(ICON.IsLoaded())
                ICON->ICON.Unload();
            return;
        case 10: //mico Small Icon Filename
            if(ICON.IsLoaded())
                ICON->MICO.Unload();
            return;
        case 11: //data DATA ,, Struct
            DATA.Unload();
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
        case 15: //ctda Conditions
            CTDAs.Unload();
            return;
        case 16: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 17: //ctda Conditions
            return UNPARSEDDEL_FIELD17;
        case 18: //ctda Conditions
            CTDAs.Unload();
            return;
        case 19: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 20: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 21: //ctda Conditions
            CTDAs.Unload();
            return;
        case 22: //ctda Conditions
            return UNPARSEDDEL_FIELD22;
        case 23: //indx Stage Index
            INDX.Unload();
            return;
        case 24: //qsdt Stage Flags
            QSDT.Unload();
            return;
        case 25: //cnam Log Entry
            CNAM.Unload();
            return;
        case 26: //schr_p Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 27: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 28: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 29: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 30: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 31: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 32: //scda_p Compiled Embedded Script
            if(SCHR.IsLoaded())
                SCHR->SCDA.Unload();
            return;
        case 33: //sctx Embedded Script Source
            if(SCHR.IsLoaded())
                SCHR->SCTX.Unload();
            return;
        case 34: //slsd Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 35: //slsd_p Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 36: //slsd Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 37: //slsd_p Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 38: //scvr Name
            if(SCHR.IsLoaded())
                SCHR->SCVR.Unload();
            return;
        case 39: //scro Global Reference
            if(SCHR.IsLoaded())
                SCHR->SCRO.Unload();
            return;
        case 40: //scrv Local Variable
            if(SCHR.IsLoaded())
                SCHR->SCRV.Unload();
            return;
        case 41: //nam0 Next Quest
            NAM0.Unload();
            return;
        case 42: //qobj Objective Index
            QOBJ.Unload();
            return;
        case 43: //nnam Description
            NNAM.Unload();
            return;
        case 44: //qsta QSTA ,, Struct
            QSTA.Unload();
            return;
        case 45: //qsta QSTA ,, Struct
            QSTA.Unload();
            return;
        case 46: //qsta_p QSTA ,, Struct
            QSTA.Unload();
            return;
        default:
            return;
        }
    }
}