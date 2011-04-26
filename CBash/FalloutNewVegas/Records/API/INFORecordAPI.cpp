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
#include "..\INFORecord.h"

namespace FNV
{
UINT32 INFORecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
            return MISSING_FIELD;
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
        case 7: //data DATA ,, Struct
            return UINT8_FIELD;
        case 8: //data DATA ,, Struct
            return UINT8_FIELD;
        case 9: //data DATA ,, Struct
            return UINT8_FIELD;
        case 10: //data DATA ,, Struct
            return UINT8_FIELD;
        case 11: //qsti Quest
            return FORMID_FIELD;
        case 12: //tpic Topic
            return FORMID_FIELD;
        case 13: //pnam Previous INFO
            return FORMID_FIELD;
        case 14: //name Topic
            return FORMID_FIELD;
        case 15: //trdt TRDT ,, Struct
            return UINT32_FIELD;
        case 16: //trdt TRDT ,, Struct
            return SINT32_FIELD;
        case 17: //trdt_p TRDT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 18: //trdt TRDT ,, Struct
            return UINT8_FIELD;
        case 19: //trdt_p TRDT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 20: //trdt TRDT ,, Struct
            return FORMID_FIELD;
        case 21: //trdt TRDT ,, Struct
            return UINT8_FIELD;
        case 22: //trdt_p TRDT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 23: //nam1 Response Text
            return ISTRING_FIELD;
        case 24: //nam2 Script Notes
            return ISTRING_FIELD;
        case 25: //nam3 Edits
            return ISTRING_FIELD;
        case 26: //snam Speaker Animation
            return FORMID_FIELD;
        case 27: //lnam Listener Animation
            return FORMID_FIELD;
        case 28: //ctda Conditions
            return UINT8_FIELD;
        case 29: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 30: //ctda Conditions
            return UNPARSED_FIELD;
        case 31: //ctda Conditions
            return UINT32_FIELD;
        case 32: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 33: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 34: //ctda Conditions
            return UINT32_FIELD;
        case 35: //ctda Conditions
            return UNPARSED_FIELD;
        case 36: //tclt Choice
            return FORMID_FIELD;
        case 37: //tclf Topic
            return FORMID_FIELD;
        case 38: //tcfu Info
            return FORMID_FIELD;
        case 39: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 40: //schr Basic Script Data
            return UINT32_FIELD;
        case 41: //schr Basic Script Data
            return UINT32_FIELD;
        case 42: //schr Basic Script Data
            return UINT32_FIELD;
        case 43: //schr Basic Script Data
            return UINT16_FIELD;
        case 44: //schr Basic Script Data
            return UINT16_FIELD;
        case 45: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 46: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 47: //slsd Local Variable Data
            return UINT32_FIELD;
        case 48: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 49: //slsd Local Variable Data
            return UINT8_FIELD;
        case 50: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 51: //scvr Name
            return ISTRING_FIELD;
        case 52: //scro Global Reference
            return FORMID_FIELD;
        case 53: //scrv Local Variable
            return UINT32_FIELD;
        case 54: //sndd Unused
            return FORMID_FIELD;
        case 55: //rnam Prompt
            return ISTRING_FIELD;
        case 56: //anam Speaker
            return FORMID_FIELD;
        case 57: //knam ActorValue/Perk
            return FORMID_FIELD;
        case 58: //dnam Speech Challenge
            return UINT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * INFORecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
           *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value6 : NULL;
        case 8: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value7 : NULL;
        case 9: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value8 : NULL;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value9 : NULL;
        case 11: //qsti Quest
            return QSTI.IsLoaded() ? &QSTI->value10 : NULL;
        case 12: //tpic Topic
            return TPIC.IsLoaded() ? &TPIC->value11 : NULL;
        case 13: //pnam Previous INFO
            return PNAM.IsLoaded() ? &PNAM->value12 : NULL;
        case 14: //name Topic
            return NAME.IsLoaded() ? &NAME->value13 : NULL;
        case 15: //trdt TRDT ,, Struct
            return TRDT.IsLoaded() ? &TRDT->value14 : NULL;
        case 16: //trdt TRDT ,, Struct
            return TRDT.IsLoaded() ? &TRDT->value15 : NULL;
        case 17: //trdt_p TRDT ,, Struct
            *FieldValues = TRDT.IsLoaded() ? &TRDT->value16[0] : NULL;
            return NULL;
        case 18: //trdt TRDT ,, Struct
            return TRDT.IsLoaded() ? &TRDT->value17 : NULL;
        case 19: //trdt_p TRDT ,, Struct
            *FieldValues = TRDT.IsLoaded() ? &TRDT->value18[0] : NULL;
            return NULL;
        case 20: //trdt TRDT ,, Struct
            return TRDT.IsLoaded() ? &TRDT->value19 : NULL;
        case 21: //trdt TRDT ,, Struct
            return TRDT.IsLoaded() ? &TRDT->value20 : NULL;
        case 22: //trdt_p TRDT ,, Struct
            *FieldValues = TRDT.IsLoaded() ? &TRDT->value21[0] : NULL;
            return NULL;
        case 23: //nam1 Response Text
            return NAM1.value;
        case 24: //nam2 Script Notes
            return NAM2.value;
        case 25: //nam3 Edits
            return NAM3.value;
        case 26: //snam Speaker Animation
            return SNAM.IsLoaded() ? &SNAM->value25 : NULL;
        case 27: //lnam Listener Animation
            return LNAM.IsLoaded() ? &LNAM->value26 : NULL;
        case 28: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value27 : NULL;
        case 29: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value28[0] : NULL;
            return NULL;
        case 30: //ctda Conditions
            return UNPARSEDGET_FIELD29;
        case 31: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value30 : NULL;
        case 32: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value31[0] : NULL;
            return NULL;
        case 33: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value32[0] : NULL;
            return NULL;
        case 34: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value33 : NULL;
        case 35: //ctda Conditions
            return UNPARSEDGET_FIELD34;
        case 36: //tclt Choice
            return TCLT.IsLoaded() ? &TCLT->value35 : NULL;
        case 37: //tclf Topic
            return TCLF.IsLoaded() ? &TCLF->value36 : NULL;
        case 38: //tcfu Info
            return TCFU.IsLoaded() ? &TCFU->value37 : NULL;
        case 39: //schr_p Basic Script Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SCHR->value38[0] : NULL;
            return NULL;
        case 40: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value39 : NULL;
        case 41: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value40 : NULL;
        case 42: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value41 : NULL;
        case 43: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value42 : NULL;
        case 44: //schr Basic Script Data
            return SCHR.IsLoaded() ? &SCHR->SCHR->value43 : NULL;
        case 45: //scda_p Compiled Embedded Script
            *FieldValues = (SCHR.IsLoaded()) ? SCHR->SCDA.value : NULL;
            return NULL;
        case 46: //sctx Embedded Script Source
            return SCHR.IsLoaded() ? SCHR->SCTX.value : NULL;
        case 47: //slsd Local Variable Data
            return SCHR.IsLoaded() ? &SCHR->SLSD->value46 : NULL;
        case 48: //slsd_p Local Variable Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value47[0] : NULL;
            return NULL;
        case 49: //slsd Local Variable Data
            return SCHR.IsLoaded() ? &SCHR->SLSD->value48 : NULL;
        case 50: //slsd_p Local Variable Data
            *FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value49[0] : NULL;
            return NULL;
        case 51: //scvr Name
            return SCHR.IsLoaded() ? SCHR->SCVR.value : NULL;
        case 52: //scro Global Reference
            return SCHR.IsLoaded() ? &SCHR->SCRO->value51 : NULL;
        case 53: //scrv Local Variable
            return SCHR.IsLoaded() ? &SCHR->SCRV->value52 : NULL;
        case 54: //sndd Unused
            return SNDD.IsLoaded() ? &SNDD->value53 : NULL;
        case 55: //rnam Prompt
            return RNAM.value;
        case 56: //anam Speaker
            return ANAM.IsLoaded() ? &ANAM->value55 : NULL;
        case 57: //knam ActorValue/Perk
            return KNAM.IsLoaded() ? &KNAM->value56 : NULL;
        case 58: //dnam Speech Challenge
            return DNAM.IsLoaded() ? &DNAM->value57 : NULL;
        default:
            return NULL;
        }
    }

bool INFORecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 5: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8 *)FieldValue)[0];
            versionControl2[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 7: //data DATA ,, Struct
            DATA.Load();
            DATA->value6 = *(UINT8 *)FieldValue;
            break;
        case 8: //data DATA ,, Struct
            DATA.Load();
            DATA->value7 = *(UINT8 *)FieldValue;
            break;
        case 9: //data DATA ,, Struct
            DATA.Load();
            DATA->value8 = *(UINT8 *)FieldValue;
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->value9 = *(UINT8 *)FieldValue;
            break;
        case 11: //qsti Quest
            QSTI.Load();
            QSTI->value10 = *(FORMID *)FieldValue;
            return true;
        case 12: //tpic Topic
            TPIC.Load();
            TPIC->value11 = *(FORMID *)FieldValue;
            return true;
        case 13: //pnam Previous INFO
            PNAM.Load();
            PNAM->value12 = *(FORMID *)FieldValue;
            return true;
        case 14: //name Topic
            NAME.Load();
            NAME->value13 = *(FORMID *)FieldValue;
            return true;
        case 15: //trdt TRDT ,, Struct
            TRDT.Load();
            TRDT->value14 = *(UINT32 *)FieldValue;
            break;
        case 16: //trdt TRDT ,, Struct
            TRDT.Load();
            TRDT->value15 = *(SINT32 *)FieldValue;
            break;
        case 17: //trdt_p TRDT ,, Struct
            if(ArraySize != 4)
                break;
            TRDT.Load();
            TRDT->value16[0] = ((UINT8 *)FieldValue)[0];
            TRDT->value16[1] = ((UINT8 *)FieldValue)[1];
            TRDT->value16[2] = ((UINT8 *)FieldValue)[2];
            TRDT->value16[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 18: //trdt TRDT ,, Struct
            TRDT.Load();
            TRDT->value17 = *(UINT8 *)FieldValue;
            break;
        case 19: //trdt_p TRDT ,, Struct
            if(ArraySize != 3)
                break;
            TRDT.Load();
            TRDT->value18[0] = ((UINT8 *)FieldValue)[0];
            TRDT->value18[1] = ((UINT8 *)FieldValue)[1];
            TRDT->value18[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 20: //trdt TRDT ,, Struct
            TRDT.Load();
            TRDT->value19 = *(FORMID *)FieldValue;
            return true;
        case 21: //trdt TRDT ,, Struct
            TRDT.Load();
            TRDT->value20 = *(UINT8 *)FieldValue;
            break;
        case 22: //trdt_p TRDT ,, Struct
            if(ArraySize != 3)
                break;
            TRDT.Load();
            TRDT->value21[0] = ((UINT8 *)FieldValue)[0];
            TRDT->value21[1] = ((UINT8 *)FieldValue)[1];
            TRDT->value21[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 23: //nam1 Response Text
            NAM1.Copy((STRING)FieldValue);
            break;
        case 24: //nam2 Script Notes
            NAM2.Copy((STRING)FieldValue);
            break;
        case 25: //nam3 Edits
            NAM3.Copy((STRING)FieldValue);
            break;
        case 26: //snam Speaker Animation
            SNAM.Load();
            SNAM->value25 = *(FORMID *)FieldValue;
            return true;
        case 27: //lnam Listener Animation
            LNAM.Load();
            LNAM->value26 = *(FORMID *)FieldValue;
            return true;
        case 28: //ctda Conditions
            CTDAs.Load();
            CTDAs->value27 = *(UINT8 *)FieldValue;
            break;
        case 29: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            CTDAs.Load();
            CTDAs->value28[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value28[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value28[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 30: //ctda Conditions
            return UNPARSEDGET_FIELD29;
        case 31: //ctda Conditions
            CTDAs.Load();
            CTDAs->value30 = *(UINT32 *)FieldValue;
            break;
        case 32: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value31[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value31[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value31[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value31[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 33: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value32[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value32[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value32[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value32[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 34: //ctda Conditions
            CTDAs.Load();
            CTDAs->value33 = *(UINT32 *)FieldValue;
            break;
        case 35: //ctda Conditions
            return UNPARSEDGET_FIELD34;
        case 36: //tclt Choice
            TCLT.Load();
            TCLT->value35 = *(FORMID *)FieldValue;
            return true;
        case 37: //tclf Topic
            TCLF.Load();
            TCLF->value36 = *(FORMID *)FieldValue;
            return true;
        case 38: //tcfu Info
            TCFU.Load();
            TCFU->value37 = *(FORMID *)FieldValue;
            return true;
        case 39: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value38[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SCHR->value38[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SCHR->value38[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SCHR->value38[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 40: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value39 = *(UINT32 *)FieldValue;
            break;
        case 41: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value40 = *(UINT32 *)FieldValue;
            break;
        case 42: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value41 = *(UINT32 *)FieldValue;
            break;
        case 43: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value42 = *(UINT16 *)FieldValue;
            break;
        case 44: //schr Basic Script Data
            SCHR.Load();
            SCHR->SCHR.Load();
            SCHR->SCHR->value43 = *(UINT16 *)FieldValue;
            break;
        case 45: //scda_p Compiled Embedded Script
            SCHR.Load();
            SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 46: //sctx Embedded Script Source
            SCHR.Load();
            SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 47: //slsd Local Variable Data
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value46 = *(UINT32 *)FieldValue;
            break;
        case 48: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value47[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SLSD->value47[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SLSD->value47[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SLSD->value47[3] = ((UINT8 *)FieldValue)[3];
            SCHR->SLSD->value47[4] = ((UINT8 *)FieldValue)[4];
            SCHR->SLSD->value47[5] = ((UINT8 *)FieldValue)[5];
            SCHR->SLSD->value47[6] = ((UINT8 *)FieldValue)[6];
            SCHR->SLSD->value47[7] = ((UINT8 *)FieldValue)[7];
            SCHR->SLSD->value47[8] = ((UINT8 *)FieldValue)[8];
            SCHR->SLSD->value47[9] = ((UINT8 *)FieldValue)[9];
            SCHR->SLSD->value47[10] = ((UINT8 *)FieldValue)[10];
            SCHR->SLSD->value47[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 49: //slsd Local Variable Data
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value48 = *(UINT8 *)FieldValue;
            break;
        case 50: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            SCHR.Load();
            SCHR->SLSD.Load();
            SCHR->SLSD->value49[0] = ((UINT8 *)FieldValue)[0];
            SCHR->SLSD->value49[1] = ((UINT8 *)FieldValue)[1];
            SCHR->SLSD->value49[2] = ((UINT8 *)FieldValue)[2];
            SCHR->SLSD->value49[3] = ((UINT8 *)FieldValue)[3];
            SCHR->SLSD->value49[4] = ((UINT8 *)FieldValue)[4];
            SCHR->SLSD->value49[5] = ((UINT8 *)FieldValue)[5];
            SCHR->SLSD->value49[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 51: //scvr Name
            SCHR.Load();
            SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 52: //scro Global Reference
            SCHR.Load();
            SCHR->SCRO.Load();
            SCHR->SCRO->value51 = *(FORMID *)FieldValue;
            return true;
        case 53: //scrv Local Variable
            SCHR.Load();
            SCHR->SCRV.Load();
            SCHR->SCRV->value52 = *(UINT32 *)FieldValue;
            break;
        case 54: //sndd Unused
            SNDD.Load();
            SNDD->value53 = *(FORMID *)FieldValue;
            return true;
        case 55: //rnam Prompt
            RNAM.Copy((STRING)FieldValue);
            break;
        case 56: //anam Speaker
            ANAM.Load();
            ANAM->value55 = *(FORMID *)FieldValue;
            return true;
        case 57: //knam ActorValue/Perk
            KNAM.Load();
            KNAM->value56 = *(FORMID *)FieldValue;
            return true;
        case 58: //dnam Speech Challenge
            DNAM.Load();
            DNAM->value57 = *(UINT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void INFORecord::DeleteField(FIELD_IDENTIFIERS)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //data DATA ,, Struct
            DATA.Unload();
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
        case 11: //qsti Quest
            QSTI.Unload();
            return;
        case 12: //tpic Topic
            TPIC.Unload();
            return;
        case 13: //pnam Previous INFO
            PNAM.Unload();
            return;
        case 14: //name Topic
            NAME.Unload();
            return;
        case 15: //trdt TRDT ,, Struct
            TRDT.Unload();
            return;
        case 16: //trdt TRDT ,, Struct
            TRDT.Unload();
            return;
        case 17: //trdt_p TRDT ,, Struct
            TRDT.Unload();
            return;
        case 18: //trdt TRDT ,, Struct
            TRDT.Unload();
            return;
        case 19: //trdt_p TRDT ,, Struct
            TRDT.Unload();
            return;
        case 20: //trdt TRDT ,, Struct
            TRDT.Unload();
            return;
        case 21: //trdt TRDT ,, Struct
            TRDT.Unload();
            return;
        case 22: //trdt_p TRDT ,, Struct
            TRDT.Unload();
            return;
        case 23: //nam1 Response Text
            NAM1.Unload();
            return;
        case 24: //nam2 Script Notes
            NAM2.Unload();
            return;
        case 25: //nam3 Edits
            NAM3.Unload();
            return;
        case 26: //snam Speaker Animation
            SNAM.Unload();
            return;
        case 27: //lnam Listener Animation
            LNAM.Unload();
            return;
        case 28: //ctda Conditions
            CTDAs.Unload();
            return;
        case 29: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 30: //ctda Conditions
            return UNPARSEDDEL_FIELD29;
        case 31: //ctda Conditions
            CTDAs.Unload();
            return;
        case 32: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 33: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 34: //ctda Conditions
            CTDAs.Unload();
            return;
        case 35: //ctda Conditions
            return UNPARSEDDEL_FIELD34;
        case 36: //tclt Choice
            TCLT.Unload();
            return;
        case 37: //tclf Topic
            TCLF.Unload();
            return;
        case 38: //tcfu Info
            TCFU.Unload();
            return;
        case 39: //schr_p Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 40: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 41: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 42: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 43: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 44: //schr Basic Script Data
            if(SCHR.IsLoaded())
                SCHR->SCHR.Unload();
            return;
        case 45: //scda_p Compiled Embedded Script
            if(SCHR.IsLoaded())
                SCHR->SCDA.Unload();
            return;
        case 46: //sctx Embedded Script Source
            if(SCHR.IsLoaded())
                SCHR->SCTX.Unload();
            return;
        case 47: //slsd Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 48: //slsd_p Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 49: //slsd Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 50: //slsd_p Local Variable Data
            if(SCHR.IsLoaded())
                SCHR->SLSD.Unload();
            return;
        case 51: //scvr Name
            if(SCHR.IsLoaded())
                SCHR->SCVR.Unload();
            return;
        case 52: //scro Global Reference
            if(SCHR.IsLoaded())
                SCHR->SCRO.Unload();
            return;
        case 53: //scrv Local Variable
            if(SCHR.IsLoaded())
                SCHR->SCRV.Unload();
            return;
        case 54: //sndd Unused
            SNDD.Unload();
            return;
        case 55: //rnam Prompt
            RNAM.Unload();
            return;
        case 56: //anam Speaker
            ANAM.Unload();
            return;
        case 57: //knam ActorValue/Perk
            KNAM.Unload();
            return;
        case 58: //dnam Speech Challenge
            DNAM.Unload();
            return;
        default:
            return;
        }
    }
}