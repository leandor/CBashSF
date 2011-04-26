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
#include "..\PACKRecord.h"

namespace FNV
{
UINT32 PACKRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //pkdt PKDT ,, Struct
            return UINT32_FIELD;
        case 8: //pkdt PKDT ,, Struct
            return UINT8_FIELD;
        case 9: //pkdt_p PKDT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 11: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 12: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 13: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 14: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 15: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 16: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 17: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 18: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 19: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 20: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 21: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 22: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 23: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 24: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 25: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 26: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 27: //pkdt PKDT ,, Struct
            return UINT16_FIELD;
        case 28: //pkdt_p PKDT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 29: //pldt PLDT ,, Struct
            return SINT32_FIELD;
        case 30: //pldt PLDT ,, Struct
            return FORMID_FIELD;
        case 31: //pldt PLDT ,, Struct
            return SINT32_FIELD;
        case 32: //pld2 PLD2 ,, Struct
            return SINT32_FIELD;
        case 33: //pld2 PLD2 ,, Struct
            return FORMID_FIELD;
        case 34: //pld2 PLD2 ,, Struct
            return SINT32_FIELD;
        case 35: //psdt PSDT ,, Struct
            return SINT8_FIELD;
        case 36: //psdt PSDT ,, Struct
            return SINT8_FIELD;
        case 37: //psdt PSDT ,, Struct
            return UINT8_FIELD;
        case 38: //psdt PSDT ,, Struct
            return SINT8_FIELD;
        case 39: //psdt PSDT ,, Struct
            return SINT32_FIELD;
        case 40: //ptdt PTDT ,, Struct
            return SINT32_FIELD;
        case 41: //ptdt PTDT ,, Struct
            return FORMID_FIELD;
        case 42: //ptdt PTDT ,, Struct
            return SINT32_FIELD;
        case 43: //ptdt PTDT ,, Struct
            return FLOAT32_FIELD;
        case 44: //ctda Conditions
            return UINT8_FIELD;
        case 45: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 46: //ctda Conditions
            return UNPARSED_FIELD;
        case 47: //ctda Conditions
            return UINT32_FIELD;
        case 48: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 49: //ctda_p Conditions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 50: //ctda Conditions
            return UINT32_FIELD;
        case 51: //ctda Conditions
            return UNPARSED_FIELD;
        case 52: //idlf Flags
            return UINT8_FIELD;
        case 53: //idlc IDLC ,, Struct
            return UINT8_FIELD;
        case 54: //idlc_p IDLC ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 55: //idlt Idle Timer Setting
            return FLOAT32_FIELD;
        case 56: //idla Animation
            return FORMID_FIELD;
        case 57: //idlb_p Unused
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 58: //pke2 Escort Distance
            return UINT32_FIELD;
        case 59: //cnam Combat Style
            return FORMID_FIELD;
        case 60: //pkfd Follow - Start Location - Trigger Radius
            return FLOAT32_FIELD;
        case 61: //pkpt PKPT ,, Struct
            return UINT8_FIELD;
        case 62: //pkpt_p PKPT ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 63: //pkw3 PKW3 ,, Struct
            return UINT32_FIELD;
        case 64: //pkw3 PKW3 ,, Struct
            return UINT8_FIELD;
        case 65: //pkw3 PKW3 ,, Struct
            return UINT8_FIELD;
        case 66: //pkw3 PKW3 ,, Struct
            return UINT16_FIELD;
        case 67: //pkw3 PKW3 ,, Struct
            return UINT16_FIELD;
        case 68: //pkw3 PKW3 ,, Struct
            return UINT16_FIELD;
        case 69: //pkw3 PKW3 ,, Struct
            return FLOAT32_FIELD;
        case 70: //pkw3 PKW3 ,, Struct
            return FLOAT32_FIELD;
        case 71: //pkw3_p PKW3 ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 72: //ptd2 PTD2 ,, Struct
            return SINT32_FIELD;
        case 73: //ptd2 PTD2 ,, Struct
            return FORMID_FIELD;
        case 74: //ptd2 PTD2 ,, Struct
            return SINT32_FIELD;
        case 75: //ptd2 PTD2 ,, Struct
            return FLOAT32_FIELD;
        case 76: //pkdd PKDD ,, Struct
            return FLOAT32_FIELD;
        case 77: //pkdd PKDD ,, Struct
            return FORMID_FIELD;
        case 78: //pkdd PKDD ,, Struct
            return UINT32_FIELD;
        case 79: //pkdd_p PKDD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 80: //pkdd PKDD ,, Struct
            return UINT32_FIELD;
        case 81: //pkdd_p PKDD ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 82: //inam Idle
            return FORMID_FIELD;
        case 83: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 84: //schr Basic Script Data
            return UINT32_FIELD;
        case 85: //schr Basic Script Data
            return UINT32_FIELD;
        case 86: //schr Basic Script Data
            return UINT32_FIELD;
        case 87: //schr Basic Script Data
            return UINT16_FIELD;
        case 88: //schr Basic Script Data
            return UINT16_FIELD;
        case 89: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 90: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 91: //slsd Local Variable Data
            return UINT32_FIELD;
        case 92: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 93: //slsd Local Variable Data
            return UINT8_FIELD;
        case 94: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 95: //scvr Name
            return ISTRING_FIELD;
        case 96: //scro Global Reference
            return FORMID_FIELD;
        case 97: //scrv Local Variable
            return UINT32_FIELD;
        case 98: //tnam Topic
            return FORMID_FIELD;
        case 99: //inam Idle
            return FORMID_FIELD;
        case 100: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 101: //schr Basic Script Data
            return UINT32_FIELD;
        case 102: //schr Basic Script Data
            return UINT32_FIELD;
        case 103: //schr Basic Script Data
            return UINT32_FIELD;
        case 104: //schr Basic Script Data
            return UINT16_FIELD;
        case 105: //schr Basic Script Data
            return UINT16_FIELD;
        case 106: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 107: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 108: //slsd Local Variable Data
            return UINT32_FIELD;
        case 109: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 110: //slsd Local Variable Data
            return UINT8_FIELD;
        case 111: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 112: //scvr Name
            return ISTRING_FIELD;
        case 113: //scro Global Reference
            return FORMID_FIELD;
        case 114: //scrv Local Variable
            return UINT32_FIELD;
        case 115: //tnam Topic
            return FORMID_FIELD;
        case 116: //inam Idle
            return FORMID_FIELD;
        case 117: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 118: //schr Basic Script Data
            return UINT32_FIELD;
        case 119: //schr Basic Script Data
            return UINT32_FIELD;
        case 120: //schr Basic Script Data
            return UINT32_FIELD;
        case 121: //schr Basic Script Data
            return UINT16_FIELD;
        case 122: //schr Basic Script Data
            return UINT16_FIELD;
        case 123: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 124: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 125: //slsd Local Variable Data
            return UINT32_FIELD;
        case 126: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 127: //slsd Local Variable Data
            return UINT8_FIELD;
        case 128: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 129: //scvr Name
            return ISTRING_FIELD;
        case 130: //scro Global Reference
            return FORMID_FIELD;
        case 131: //scrv Local Variable
            return UINT32_FIELD;
        case 132: //tnam Topic
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * PACKRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value7 : NULL;
        case 8: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value8 : NULL;
        case 9: //pkdt_p PKDT ,, Struct
            *FieldValues = PKDT.IsLoaded() ? &PKDT->value9[0] : NULL;
            return NULL;
        case 10: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value10 : NULL;
        case 11: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value11 : NULL;
        case 12: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value12 : NULL;
        case 13: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value13 : NULL;
        case 14: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value14 : NULL;
        case 15: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value15 : NULL;
        case 16: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value16 : NULL;
        case 17: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value17 : NULL;
        case 18: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value18 : NULL;
        case 19: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value19 : NULL;
        case 20: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value20 : NULL;
        case 21: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value21 : NULL;
        case 22: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value22 : NULL;
        case 23: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value23 : NULL;
        case 24: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value24 : NULL;
        case 25: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value25 : NULL;
        case 26: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value26 : NULL;
        case 27: //pkdt PKDT ,, Struct
            return PKDT.IsLoaded() ? &PKDT->value27 : NULL;
        case 28: //pkdt_p PKDT ,, Struct
            *FieldValues = PKDT.IsLoaded() ? &PKDT->value28[0] : NULL;
            return NULL;
        case 29: //pldt PLDT ,, Struct
            return PLDT.IsLoaded() ? &PLDT->value29 : NULL;
        case 30: //pldt PLDT ,, Struct
            return PLDT.IsLoaded() ? &PLDT->value30 : NULL;
        case 31: //pldt PLDT ,, Struct
            return PLDT.IsLoaded() ? &PLDT->value31 : NULL;
        case 32: //pld2 PLD2 ,, Struct
            return PLD2.IsLoaded() ? &PLD2->value32 : NULL;
        case 33: //pld2 PLD2 ,, Struct
            return PLD2.IsLoaded() ? &PLD2->value33 : NULL;
        case 34: //pld2 PLD2 ,, Struct
            return PLD2.IsLoaded() ? &PLD2->value34 : NULL;
        case 35: //psdt PSDT ,, Struct
            return PSDT.IsLoaded() ? &PSDT->value35 : NULL;
        case 36: //psdt PSDT ,, Struct
            return PSDT.IsLoaded() ? &PSDT->value36 : NULL;
        case 37: //psdt PSDT ,, Struct
            return PSDT.IsLoaded() ? &PSDT->value37 : NULL;
        case 38: //psdt PSDT ,, Struct
            return PSDT.IsLoaded() ? &PSDT->value38 : NULL;
        case 39: //psdt PSDT ,, Struct
            return PSDT.IsLoaded() ? &PSDT->value39 : NULL;
        case 40: //ptdt PTDT ,, Struct
            return PTDT.IsLoaded() ? &PTDT->value40 : NULL;
        case 41: //ptdt PTDT ,, Struct
            return PTDT.IsLoaded() ? &PTDT->value41 : NULL;
        case 42: //ptdt PTDT ,, Struct
            return PTDT.IsLoaded() ? &PTDT->value42 : NULL;
        case 43: //ptdt PTDT ,, Struct
            return PTDT.IsLoaded() ? &PTDT->value43 : NULL;
        case 44: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value44 : NULL;
        case 45: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value45[0] : NULL;
            return NULL;
        case 46: //ctda Conditions
            return UNPARSEDGET_FIELD46;
        case 47: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value47 : NULL;
        case 48: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value48[0] : NULL;
            return NULL;
        case 49: //ctda_p Conditions
            *FieldValues = CTDAs.IsLoaded() ? &CTDAs->value49[0] : NULL;
            return NULL;
        case 50: //ctda Conditions
            return CTDAs.IsLoaded() ? &CTDAs->value50 : NULL;
        case 51: //ctda Conditions
            return UNPARSEDGET_FIELD51;
        case 52: //idlf Flags
            return IDLF.IsLoaded() ? &IDLF->value52 : NULL;
        case 53: //idlc IDLC ,, Struct
            return IDLC.IsLoaded() ? &IDLC->value53 : NULL;
        case 54: //idlc_p IDLC ,, Struct
            *FieldValues = IDLC.IsLoaded() ? &IDLC->value54[0] : NULL;
            return NULL;
        case 55: //idlt Idle Timer Setting
            return IDLT.IsLoaded() ? &IDLT->value55 : NULL;
        case 56: //idla Animation
            return IDLA.IsLoaded() ? &IDLA->value56 : NULL;
        case 57: //idlb_p Unused
            *FieldValues = IDLB.IsLoaded() ? &IDLB->value57[0] : NULL;
            return NULL;
        case 58: //pke2 Escort Distance
            return PKE2.IsLoaded() ? &PKE2->value58 : NULL;
        case 59: //cnam Combat Style
            return CNAM.IsLoaded() ? &CNAM->value59 : NULL;
        case 60: //pkfd Follow - Start Location - Trigger Radius
            return PKFD.IsLoaded() ? &PKFD->value60 : NULL;
        case 61: //pkpt PKPT ,, Struct
            return PKPT.IsLoaded() ? &PKPT->value61 : NULL;
        case 62: //pkpt_p PKPT ,, Struct
            *FieldValues = PKPT.IsLoaded() ? &PKPT->value62[0] : NULL;
            return NULL;
        case 63: //pkw3 PKW3 ,, Struct
            return PKW3.IsLoaded() ? &PKW3->value63 : NULL;
        case 64: //pkw3 PKW3 ,, Struct
            return PKW3.IsLoaded() ? &PKW3->value64 : NULL;
        case 65: //pkw3 PKW3 ,, Struct
            return PKW3.IsLoaded() ? &PKW3->value65 : NULL;
        case 66: //pkw3 PKW3 ,, Struct
            return PKW3.IsLoaded() ? &PKW3->value66 : NULL;
        case 67: //pkw3 PKW3 ,, Struct
            return PKW3.IsLoaded() ? &PKW3->value67 : NULL;
        case 68: //pkw3 PKW3 ,, Struct
            return PKW3.IsLoaded() ? &PKW3->value68 : NULL;
        case 69: //pkw3 PKW3 ,, Struct
            return PKW3.IsLoaded() ? &PKW3->value69 : NULL;
        case 70: //pkw3 PKW3 ,, Struct
            return PKW3.IsLoaded() ? &PKW3->value70 : NULL;
        case 71: //pkw3_p PKW3 ,, Struct
            *FieldValues = PKW3.IsLoaded() ? &PKW3->value71[0] : NULL;
            return NULL;
        case 72: //ptd2 PTD2 ,, Struct
            return PTD2.IsLoaded() ? &PTD2->value72 : NULL;
        case 73: //ptd2 PTD2 ,, Struct
            return PTD2.IsLoaded() ? &PTD2->value73 : NULL;
        case 74: //ptd2 PTD2 ,, Struct
            return PTD2.IsLoaded() ? &PTD2->value74 : NULL;
        case 75: //ptd2 PTD2 ,, Struct
            return PTD2.IsLoaded() ? &PTD2->value75 : NULL;
        case 76: //pkdd PKDD ,, Struct
            return PKDD.IsLoaded() ? &PKDD->value76 : NULL;
        case 77: //pkdd PKDD ,, Struct
            return PKDD.IsLoaded() ? &PKDD->value77 : NULL;
        case 78: //pkdd PKDD ,, Struct
            return PKDD.IsLoaded() ? &PKDD->value78 : NULL;
        case 79: //pkdd_p PKDD ,, Struct
            *FieldValues = PKDD.IsLoaded() ? &PKDD->value79[0] : NULL;
            return NULL;
        case 80: //pkdd PKDD ,, Struct
            return PKDD.IsLoaded() ? &PKDD->value80 : NULL;
        case 81: //pkdd_p PKDD ,, Struct
            *FieldValues = PKDD.IsLoaded() ? &PKDD->value81[0] : NULL;
            return NULL;
        case 82: //inam Idle
            return POBA.IsLoaded() ? &POBA->INAM->value82 : NULL;
        case 83: //schr_p Basic Script Data
            *FieldValues = (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SCHR->value83[0] : NULL;
            return NULL;
        case 84: //schr Basic Script Data
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SCHR->value84 : NULL;
        case 85: //schr Basic Script Data
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SCHR->value85 : NULL;
        case 86: //schr Basic Script Data
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SCHR->value86 : NULL;
        case 87: //schr Basic Script Data
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SCHR->value87 : NULL;
        case 88: //schr Basic Script Data
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SCHR->value88 : NULL;
        case 89: //scda_p Compiled Embedded Script
            *FieldValues = (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? POBA->SCHR->SCDA.value : NULL;
            return NULL;
        case 90: //sctx Embedded Script Source
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? POBA->SCHR->SCTX.value : NULL;
        case 91: //slsd Local Variable Data
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SLSD->value91 : NULL;
        case 92: //slsd_p Local Variable Data
            *FieldValues = (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SLSD->value92[0] : NULL;
            return NULL;
        case 93: //slsd Local Variable Data
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SLSD->value93 : NULL;
        case 94: //slsd_p Local Variable Data
            *FieldValues = (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SLSD->value94[0] : NULL;
            return NULL;
        case 95: //scvr Name
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? POBA->SCHR->SCVR.value : NULL;
        case 96: //scro Global Reference
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SCRO->value96 : NULL;
        case 97: //scrv Local Variable
            return (POBA.IsLoaded() && POBA->SCHR.IsLoaded()) ? &POBA->SCHR->SCRV->value97 : NULL;
        case 98: //tnam Topic
            return POBA.IsLoaded() ? &POBA->TNAM->value98 : NULL;
        case 99: //inam Idle
            return POEA.IsLoaded() ? &POEA->INAM->value99 : NULL;
        case 100: //schr_p Basic Script Data
            *FieldValues = (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SCHR->value100[0] : NULL;
            return NULL;
        case 101: //schr Basic Script Data
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SCHR->value101 : NULL;
        case 102: //schr Basic Script Data
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SCHR->value102 : NULL;
        case 103: //schr Basic Script Data
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SCHR->value103 : NULL;
        case 104: //schr Basic Script Data
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SCHR->value104 : NULL;
        case 105: //schr Basic Script Data
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SCHR->value105 : NULL;
        case 106: //scda_p Compiled Embedded Script
            *FieldValues = (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? POEA->SCHR->SCDA.value : NULL;
            return NULL;
        case 107: //sctx Embedded Script Source
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? POEA->SCHR->SCTX.value : NULL;
        case 108: //slsd Local Variable Data
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SLSD->value108 : NULL;
        case 109: //slsd_p Local Variable Data
            *FieldValues = (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SLSD->value109[0] : NULL;
            return NULL;
        case 110: //slsd Local Variable Data
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SLSD->value110 : NULL;
        case 111: //slsd_p Local Variable Data
            *FieldValues = (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SLSD->value111[0] : NULL;
            return NULL;
        case 112: //scvr Name
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? POEA->SCHR->SCVR.value : NULL;
        case 113: //scro Global Reference
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SCRO->value113 : NULL;
        case 114: //scrv Local Variable
            return (POEA.IsLoaded() && POEA->SCHR.IsLoaded()) ? &POEA->SCHR->SCRV->value114 : NULL;
        case 115: //tnam Topic
            return POEA.IsLoaded() ? &POEA->TNAM->value115 : NULL;
        case 116: //inam Idle
            return POCA.IsLoaded() ? &POCA->INAM->value116 : NULL;
        case 117: //schr_p Basic Script Data
            *FieldValues = (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SCHR->value117[0] : NULL;
            return NULL;
        case 118: //schr Basic Script Data
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SCHR->value118 : NULL;
        case 119: //schr Basic Script Data
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SCHR->value119 : NULL;
        case 120: //schr Basic Script Data
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SCHR->value120 : NULL;
        case 121: //schr Basic Script Data
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SCHR->value121 : NULL;
        case 122: //schr Basic Script Data
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SCHR->value122 : NULL;
        case 123: //scda_p Compiled Embedded Script
            *FieldValues = (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? POCA->SCHR->SCDA.value : NULL;
            return NULL;
        case 124: //sctx Embedded Script Source
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? POCA->SCHR->SCTX.value : NULL;
        case 125: //slsd Local Variable Data
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SLSD->value125 : NULL;
        case 126: //slsd_p Local Variable Data
            *FieldValues = (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SLSD->value126[0] : NULL;
            return NULL;
        case 127: //slsd Local Variable Data
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SLSD->value127 : NULL;
        case 128: //slsd_p Local Variable Data
            *FieldValues = (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SLSD->value128[0] : NULL;
            return NULL;
        case 129: //scvr Name
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? POCA->SCHR->SCVR.value : NULL;
        case 130: //scro Global Reference
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SCRO->value130 : NULL;
        case 131: //scrv Local Variable
            return (POCA.IsLoaded() && POCA->SCHR.IsLoaded()) ? &POCA->SCHR->SCRV->value131 : NULL;
        case 132: //tnam Topic
            return POCA.IsLoaded() ? &POCA->TNAM->value132 : NULL;
        default:
            return NULL;
        }
    }

bool PACKRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value7 = *(UINT32 *)FieldValue;
            break;
        case 8: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value8 = *(UINT8 *)FieldValue;
            break;
        case 9: //pkdt_p PKDT ,, Struct
            if(ArraySize != 1)
                break;
            PKDT.Load();
            PKDT->value9[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 10: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value10 = *(UINT16 *)FieldValue;
            break;
        case 11: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value11 = *(UINT16 *)FieldValue;
            break;
        case 12: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value12 = *(UINT16 *)FieldValue;
            break;
        case 13: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value13 = *(UINT16 *)FieldValue;
            break;
        case 14: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value14 = *(UINT16 *)FieldValue;
            break;
        case 15: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value15 = *(UINT16 *)FieldValue;
            break;
        case 16: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value16 = *(UINT16 *)FieldValue;
            break;
        case 17: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value17 = *(UINT16 *)FieldValue;
            break;
        case 18: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value18 = *(UINT16 *)FieldValue;
            break;
        case 19: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value19 = *(UINT16 *)FieldValue;
            break;
        case 20: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value20 = *(UINT16 *)FieldValue;
            break;
        case 21: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value21 = *(UINT16 *)FieldValue;
            break;
        case 22: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value22 = *(UINT16 *)FieldValue;
            break;
        case 23: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value23 = *(UINT16 *)FieldValue;
            break;
        case 24: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value24 = *(UINT16 *)FieldValue;
            break;
        case 25: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value25 = *(UINT16 *)FieldValue;
            break;
        case 26: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value26 = *(UINT16 *)FieldValue;
            break;
        case 27: //pkdt PKDT ,, Struct
            PKDT.Load();
            PKDT->value27 = *(UINT16 *)FieldValue;
            break;
        case 28: //pkdt_p PKDT ,, Struct
            if(ArraySize != 2)
                break;
            PKDT.Load();
            PKDT->value28[0] = ((UINT8 *)FieldValue)[0];
            PKDT->value28[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 29: //pldt PLDT ,, Struct
            PLDT.Load();
            PLDT->value29 = *(SINT32 *)FieldValue;
            break;
        case 30: //pldt PLDT ,, Struct
            PLDT.Load();
            PLDT->value30 = *(FORMID *)FieldValue;
            return true;
        case 31: //pldt PLDT ,, Struct
            PLDT.Load();
            PLDT->value31 = *(SINT32 *)FieldValue;
            break;
        case 32: //pld2 PLD2 ,, Struct
            PLD2.Load();
            PLD2->value32 = *(SINT32 *)FieldValue;
            break;
        case 33: //pld2 PLD2 ,, Struct
            PLD2.Load();
            PLD2->value33 = *(FORMID *)FieldValue;
            return true;
        case 34: //pld2 PLD2 ,, Struct
            PLD2.Load();
            PLD2->value34 = *(SINT32 *)FieldValue;
            break;
        case 35: //psdt PSDT ,, Struct
            PSDT.Load();
            PSDT->value35 = *(SINT8 *)FieldValue;
            break;
        case 36: //psdt PSDT ,, Struct
            PSDT.Load();
            PSDT->value36 = *(SINT8 *)FieldValue;
            break;
        case 37: //psdt PSDT ,, Struct
            PSDT.Load();
            PSDT->value37 = *(UINT8 *)FieldValue;
            break;
        case 38: //psdt PSDT ,, Struct
            PSDT.Load();
            PSDT->value38 = *(SINT8 *)FieldValue;
            break;
        case 39: //psdt PSDT ,, Struct
            PSDT.Load();
            PSDT->value39 = *(SINT32 *)FieldValue;
            break;
        case 40: //ptdt PTDT ,, Struct
            PTDT.Load();
            PTDT->value40 = *(SINT32 *)FieldValue;
            break;
        case 41: //ptdt PTDT ,, Struct
            PTDT.Load();
            PTDT->value41 = *(FORMID *)FieldValue;
            return true;
        case 42: //ptdt PTDT ,, Struct
            PTDT.Load();
            PTDT->value42 = *(SINT32 *)FieldValue;
            break;
        case 43: //ptdt PTDT ,, Struct
            PTDT.Load();
            PTDT->value43 = *(FLOAT32 *)FieldValue;
            break;
        case 44: //ctda Conditions
            CTDAs.Load();
            CTDAs->value44 = *(UINT8 *)FieldValue;
            break;
        case 45: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            CTDAs.Load();
            CTDAs->value45[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value45[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value45[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 46: //ctda Conditions
            return UNPARSEDGET_FIELD46;
        case 47: //ctda Conditions
            CTDAs.Load();
            CTDAs->value47 = *(UINT32 *)FieldValue;
            break;
        case 48: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value48[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value48[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value48[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value48[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 49: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            CTDAs.Load();
            CTDAs->value49[0] = ((UINT8 *)FieldValue)[0];
            CTDAs->value49[1] = ((UINT8 *)FieldValue)[1];
            CTDAs->value49[2] = ((UINT8 *)FieldValue)[2];
            CTDAs->value49[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 50: //ctda Conditions
            CTDAs.Load();
            CTDAs->value50 = *(UINT32 *)FieldValue;
            break;
        case 51: //ctda Conditions
            return UNPARSEDGET_FIELD51;
        case 52: //idlf Flags
            IDLF.Load();
            IDLF->value52 = *(UINT8 *)FieldValue;
            break;
        case 53: //idlc IDLC ,, Struct
            IDLC.Load();
            IDLC->value53 = *(UINT8 *)FieldValue;
            break;
        case 54: //idlc_p IDLC ,, Struct
            if(ArraySize != 3)
                break;
            IDLC.Load();
            IDLC->value54[0] = ((UINT8 *)FieldValue)[0];
            IDLC->value54[1] = ((UINT8 *)FieldValue)[1];
            IDLC->value54[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 55: //idlt Idle Timer Setting
            IDLT.Load();
            IDLT->value55 = *(FLOAT32 *)FieldValue;
            break;
        case 56: //idla Animation
            IDLA.Load();
            IDLA->value56 = *(FORMID *)FieldValue;
            return true;
        case 57: //idlb_p Unused
            if(ArraySize != 4)
                break;
            IDLB.Load();
            IDLB->value57[0] = ((UINT8 *)FieldValue)[0];
            IDLB->value57[1] = ((UINT8 *)FieldValue)[1];
            IDLB->value57[2] = ((UINT8 *)FieldValue)[2];
            IDLB->value57[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 58: //pke2 Escort Distance
            PKE2.Load();
            PKE2->value58 = *(UINT32 *)FieldValue;
            break;
        case 59: //cnam Combat Style
            CNAM.Load();
            CNAM->value59 = *(FORMID *)FieldValue;
            return true;
        case 60: //pkfd Follow - Start Location - Trigger Radius
            PKFD.Load();
            PKFD->value60 = *(FLOAT32 *)FieldValue;
            break;
        case 61: //pkpt PKPT ,, Struct
            PKPT.Load();
            PKPT->value61 = *(UINT8 *)FieldValue;
            break;
        case 62: //pkpt_p PKPT ,, Struct
            if(ArraySize != 1)
                break;
            PKPT.Load();
            PKPT->value62[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 63: //pkw3 PKW3 ,, Struct
            PKW3.Load();
            PKW3->value63 = *(UINT32 *)FieldValue;
            break;
        case 64: //pkw3 PKW3 ,, Struct
            PKW3.Load();
            PKW3->value64 = *(UINT8 *)FieldValue;
            break;
        case 65: //pkw3 PKW3 ,, Struct
            PKW3.Load();
            PKW3->value65 = *(UINT8 *)FieldValue;
            break;
        case 66: //pkw3 PKW3 ,, Struct
            PKW3.Load();
            PKW3->value66 = *(UINT16 *)FieldValue;
            break;
        case 67: //pkw3 PKW3 ,, Struct
            PKW3.Load();
            PKW3->value67 = *(UINT16 *)FieldValue;
            break;
        case 68: //pkw3 PKW3 ,, Struct
            PKW3.Load();
            PKW3->value68 = *(UINT16 *)FieldValue;
            break;
        case 69: //pkw3 PKW3 ,, Struct
            PKW3.Load();
            PKW3->value69 = *(FLOAT32 *)FieldValue;
            break;
        case 70: //pkw3 PKW3 ,, Struct
            PKW3.Load();
            PKW3->value70 = *(FLOAT32 *)FieldValue;
            break;
        case 71: //pkw3_p PKW3 ,, Struct
            if(ArraySize != 4)
                break;
            PKW3.Load();
            PKW3->value71[0] = ((UINT8 *)FieldValue)[0];
            PKW3->value71[1] = ((UINT8 *)FieldValue)[1];
            PKW3->value71[2] = ((UINT8 *)FieldValue)[2];
            PKW3->value71[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 72: //ptd2 PTD2 ,, Struct
            PTD2.Load();
            PTD2->value72 = *(SINT32 *)FieldValue;
            break;
        case 73: //ptd2 PTD2 ,, Struct
            PTD2.Load();
            PTD2->value73 = *(FORMID *)FieldValue;
            return true;
        case 74: //ptd2 PTD2 ,, Struct
            PTD2.Load();
            PTD2->value74 = *(SINT32 *)FieldValue;
            break;
        case 75: //ptd2 PTD2 ,, Struct
            PTD2.Load();
            PTD2->value75 = *(FLOAT32 *)FieldValue;
            break;
        case 76: //pkdd PKDD ,, Struct
            PKDD.Load();
            PKDD->value76 = *(FLOAT32 *)FieldValue;
            break;
        case 77: //pkdd PKDD ,, Struct
            PKDD.Load();
            PKDD->value77 = *(FORMID *)FieldValue;
            return true;
        case 78: //pkdd PKDD ,, Struct
            PKDD.Load();
            PKDD->value78 = *(UINT32 *)FieldValue;
            break;
        case 79: //pkdd_p PKDD ,, Struct
            if(ArraySize != 4)
                break;
            PKDD.Load();
            PKDD->value79[0] = ((UINT8 *)FieldValue)[0];
            PKDD->value79[1] = ((UINT8 *)FieldValue)[1];
            PKDD->value79[2] = ((UINT8 *)FieldValue)[2];
            PKDD->value79[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 80: //pkdd PKDD ,, Struct
            PKDD.Load();
            PKDD->value80 = *(UINT32 *)FieldValue;
            break;
        case 81: //pkdd_p PKDD ,, Struct
            if(ArraySize != 4)
                break;
            PKDD.Load();
            PKDD->value81[0] = ((UINT8 *)FieldValue)[0];
            PKDD->value81[1] = ((UINT8 *)FieldValue)[1];
            PKDD->value81[2] = ((UINT8 *)FieldValue)[2];
            PKDD->value81[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 82: //inam Idle
            POBA.Load();
            POBA->INAM.Load();
            POBA->INAM->value82 = *(FORMID *)FieldValue;
            return true;
        case 83: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCHR.Load();
            POBA->SCHR->SCHR->value83[0] = ((UINT8 *)FieldValue)[0];
            POBA->SCHR->SCHR->value83[1] = ((UINT8 *)FieldValue)[1];
            POBA->SCHR->SCHR->value83[2] = ((UINT8 *)FieldValue)[2];
            POBA->SCHR->SCHR->value83[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 84: //schr Basic Script Data
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCHR.Load();
            POBA->SCHR->SCHR->value84 = *(UINT32 *)FieldValue;
            break;
        case 85: //schr Basic Script Data
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCHR.Load();
            POBA->SCHR->SCHR->value85 = *(UINT32 *)FieldValue;
            break;
        case 86: //schr Basic Script Data
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCHR.Load();
            POBA->SCHR->SCHR->value86 = *(UINT32 *)FieldValue;
            break;
        case 87: //schr Basic Script Data
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCHR.Load();
            POBA->SCHR->SCHR->value87 = *(UINT16 *)FieldValue;
            break;
        case 88: //schr Basic Script Data
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCHR.Load();
            POBA->SCHR->SCHR->value88 = *(UINT16 *)FieldValue;
            break;
        case 89: //scda_p Compiled Embedded Script
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 90: //sctx Embedded Script Source
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 91: //slsd Local Variable Data
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SLSD.Load();
            POBA->SCHR->SLSD->value91 = *(UINT32 *)FieldValue;
            break;
        case 92: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SLSD.Load();
            POBA->SCHR->SLSD->value92[0] = ((UINT8 *)FieldValue)[0];
            POBA->SCHR->SLSD->value92[1] = ((UINT8 *)FieldValue)[1];
            POBA->SCHR->SLSD->value92[2] = ((UINT8 *)FieldValue)[2];
            POBA->SCHR->SLSD->value92[3] = ((UINT8 *)FieldValue)[3];
            POBA->SCHR->SLSD->value92[4] = ((UINT8 *)FieldValue)[4];
            POBA->SCHR->SLSD->value92[5] = ((UINT8 *)FieldValue)[5];
            POBA->SCHR->SLSD->value92[6] = ((UINT8 *)FieldValue)[6];
            POBA->SCHR->SLSD->value92[7] = ((UINT8 *)FieldValue)[7];
            POBA->SCHR->SLSD->value92[8] = ((UINT8 *)FieldValue)[8];
            POBA->SCHR->SLSD->value92[9] = ((UINT8 *)FieldValue)[9];
            POBA->SCHR->SLSD->value92[10] = ((UINT8 *)FieldValue)[10];
            POBA->SCHR->SLSD->value92[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 93: //slsd Local Variable Data
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SLSD.Load();
            POBA->SCHR->SLSD->value93 = *(UINT8 *)FieldValue;
            break;
        case 94: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SLSD.Load();
            POBA->SCHR->SLSD->value94[0] = ((UINT8 *)FieldValue)[0];
            POBA->SCHR->SLSD->value94[1] = ((UINT8 *)FieldValue)[1];
            POBA->SCHR->SLSD->value94[2] = ((UINT8 *)FieldValue)[2];
            POBA->SCHR->SLSD->value94[3] = ((UINT8 *)FieldValue)[3];
            POBA->SCHR->SLSD->value94[4] = ((UINT8 *)FieldValue)[4];
            POBA->SCHR->SLSD->value94[5] = ((UINT8 *)FieldValue)[5];
            POBA->SCHR->SLSD->value94[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 95: //scvr Name
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 96: //scro Global Reference
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCRO.Load();
            POBA->SCHR->SCRO->value96 = *(FORMID *)FieldValue;
            return true;
        case 97: //scrv Local Variable
            POBA.Load();
            POBA->SCHR.Load();
            POBA->SCHR->SCRV.Load();
            POBA->SCHR->SCRV->value97 = *(UINT32 *)FieldValue;
            break;
        case 98: //tnam Topic
            POBA.Load();
            POBA->TNAM.Load();
            POBA->TNAM->value98 = *(FORMID *)FieldValue;
            return true;
        case 99: //inam Idle
            POEA.Load();
            POEA->INAM.Load();
            POEA->INAM->value99 = *(FORMID *)FieldValue;
            return true;
        case 100: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCHR.Load();
            POEA->SCHR->SCHR->value100[0] = ((UINT8 *)FieldValue)[0];
            POEA->SCHR->SCHR->value100[1] = ((UINT8 *)FieldValue)[1];
            POEA->SCHR->SCHR->value100[2] = ((UINT8 *)FieldValue)[2];
            POEA->SCHR->SCHR->value100[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 101: //schr Basic Script Data
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCHR.Load();
            POEA->SCHR->SCHR->value101 = *(UINT32 *)FieldValue;
            break;
        case 102: //schr Basic Script Data
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCHR.Load();
            POEA->SCHR->SCHR->value102 = *(UINT32 *)FieldValue;
            break;
        case 103: //schr Basic Script Data
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCHR.Load();
            POEA->SCHR->SCHR->value103 = *(UINT32 *)FieldValue;
            break;
        case 104: //schr Basic Script Data
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCHR.Load();
            POEA->SCHR->SCHR->value104 = *(UINT16 *)FieldValue;
            break;
        case 105: //schr Basic Script Data
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCHR.Load();
            POEA->SCHR->SCHR->value105 = *(UINT16 *)FieldValue;
            break;
        case 106: //scda_p Compiled Embedded Script
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 107: //sctx Embedded Script Source
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 108: //slsd Local Variable Data
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SLSD.Load();
            POEA->SCHR->SLSD->value108 = *(UINT32 *)FieldValue;
            break;
        case 109: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SLSD.Load();
            POEA->SCHR->SLSD->value109[0] = ((UINT8 *)FieldValue)[0];
            POEA->SCHR->SLSD->value109[1] = ((UINT8 *)FieldValue)[1];
            POEA->SCHR->SLSD->value109[2] = ((UINT8 *)FieldValue)[2];
            POEA->SCHR->SLSD->value109[3] = ((UINT8 *)FieldValue)[3];
            POEA->SCHR->SLSD->value109[4] = ((UINT8 *)FieldValue)[4];
            POEA->SCHR->SLSD->value109[5] = ((UINT8 *)FieldValue)[5];
            POEA->SCHR->SLSD->value109[6] = ((UINT8 *)FieldValue)[6];
            POEA->SCHR->SLSD->value109[7] = ((UINT8 *)FieldValue)[7];
            POEA->SCHR->SLSD->value109[8] = ((UINT8 *)FieldValue)[8];
            POEA->SCHR->SLSD->value109[9] = ((UINT8 *)FieldValue)[9];
            POEA->SCHR->SLSD->value109[10] = ((UINT8 *)FieldValue)[10];
            POEA->SCHR->SLSD->value109[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 110: //slsd Local Variable Data
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SLSD.Load();
            POEA->SCHR->SLSD->value110 = *(UINT8 *)FieldValue;
            break;
        case 111: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SLSD.Load();
            POEA->SCHR->SLSD->value111[0] = ((UINT8 *)FieldValue)[0];
            POEA->SCHR->SLSD->value111[1] = ((UINT8 *)FieldValue)[1];
            POEA->SCHR->SLSD->value111[2] = ((UINT8 *)FieldValue)[2];
            POEA->SCHR->SLSD->value111[3] = ((UINT8 *)FieldValue)[3];
            POEA->SCHR->SLSD->value111[4] = ((UINT8 *)FieldValue)[4];
            POEA->SCHR->SLSD->value111[5] = ((UINT8 *)FieldValue)[5];
            POEA->SCHR->SLSD->value111[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 112: //scvr Name
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 113: //scro Global Reference
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCRO.Load();
            POEA->SCHR->SCRO->value113 = *(FORMID *)FieldValue;
            return true;
        case 114: //scrv Local Variable
            POEA.Load();
            POEA->SCHR.Load();
            POEA->SCHR->SCRV.Load();
            POEA->SCHR->SCRV->value114 = *(UINT32 *)FieldValue;
            break;
        case 115: //tnam Topic
            POEA.Load();
            POEA->TNAM.Load();
            POEA->TNAM->value115 = *(FORMID *)FieldValue;
            return true;
        case 116: //inam Idle
            POCA.Load();
            POCA->INAM.Load();
            POCA->INAM->value116 = *(FORMID *)FieldValue;
            return true;
        case 117: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCHR.Load();
            POCA->SCHR->SCHR->value117[0] = ((UINT8 *)FieldValue)[0];
            POCA->SCHR->SCHR->value117[1] = ((UINT8 *)FieldValue)[1];
            POCA->SCHR->SCHR->value117[2] = ((UINT8 *)FieldValue)[2];
            POCA->SCHR->SCHR->value117[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 118: //schr Basic Script Data
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCHR.Load();
            POCA->SCHR->SCHR->value118 = *(UINT32 *)FieldValue;
            break;
        case 119: //schr Basic Script Data
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCHR.Load();
            POCA->SCHR->SCHR->value119 = *(UINT32 *)FieldValue;
            break;
        case 120: //schr Basic Script Data
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCHR.Load();
            POCA->SCHR->SCHR->value120 = *(UINT32 *)FieldValue;
            break;
        case 121: //schr Basic Script Data
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCHR.Load();
            POCA->SCHR->SCHR->value121 = *(UINT16 *)FieldValue;
            break;
        case 122: //schr Basic Script Data
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCHR.Load();
            POCA->SCHR->SCHR->value122 = *(UINT16 *)FieldValue;
            break;
        case 123: //scda_p Compiled Embedded Script
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 124: //sctx Embedded Script Source
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 125: //slsd Local Variable Data
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SLSD.Load();
            POCA->SCHR->SLSD->value125 = *(UINT32 *)FieldValue;
            break;
        case 126: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SLSD.Load();
            POCA->SCHR->SLSD->value126[0] = ((UINT8 *)FieldValue)[0];
            POCA->SCHR->SLSD->value126[1] = ((UINT8 *)FieldValue)[1];
            POCA->SCHR->SLSD->value126[2] = ((UINT8 *)FieldValue)[2];
            POCA->SCHR->SLSD->value126[3] = ((UINT8 *)FieldValue)[3];
            POCA->SCHR->SLSD->value126[4] = ((UINT8 *)FieldValue)[4];
            POCA->SCHR->SLSD->value126[5] = ((UINT8 *)FieldValue)[5];
            POCA->SCHR->SLSD->value126[6] = ((UINT8 *)FieldValue)[6];
            POCA->SCHR->SLSD->value126[7] = ((UINT8 *)FieldValue)[7];
            POCA->SCHR->SLSD->value126[8] = ((UINT8 *)FieldValue)[8];
            POCA->SCHR->SLSD->value126[9] = ((UINT8 *)FieldValue)[9];
            POCA->SCHR->SLSD->value126[10] = ((UINT8 *)FieldValue)[10];
            POCA->SCHR->SLSD->value126[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 127: //slsd Local Variable Data
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SLSD.Load();
            POCA->SCHR->SLSD->value127 = *(UINT8 *)FieldValue;
            break;
        case 128: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SLSD.Load();
            POCA->SCHR->SLSD->value128[0] = ((UINT8 *)FieldValue)[0];
            POCA->SCHR->SLSD->value128[1] = ((UINT8 *)FieldValue)[1];
            POCA->SCHR->SLSD->value128[2] = ((UINT8 *)FieldValue)[2];
            POCA->SCHR->SLSD->value128[3] = ((UINT8 *)FieldValue)[3];
            POCA->SCHR->SLSD->value128[4] = ((UINT8 *)FieldValue)[4];
            POCA->SCHR->SLSD->value128[5] = ((UINT8 *)FieldValue)[5];
            POCA->SCHR->SLSD->value128[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 129: //scvr Name
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 130: //scro Global Reference
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCRO.Load();
            POCA->SCHR->SCRO->value130 = *(FORMID *)FieldValue;
            return true;
        case 131: //scrv Local Variable
            POCA.Load();
            POCA->SCHR.Load();
            POCA->SCHR->SCRV.Load();
            POCA->SCHR->SCRV->value131 = *(UINT32 *)FieldValue;
            break;
        case 132: //tnam Topic
            POCA.Load();
            POCA->TNAM.Load();
            POCA->TNAM->value132 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void PACKRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 8: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 9: //pkdt_p PKDT ,, Struct
            PKDT.Unload();
            return;
        case 10: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 11: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 12: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 13: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 14: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 15: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 16: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 17: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 18: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 19: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 20: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 21: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 22: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 23: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 24: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 25: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 26: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 27: //pkdt PKDT ,, Struct
            PKDT.Unload();
            return;
        case 28: //pkdt_p PKDT ,, Struct
            PKDT.Unload();
            return;
        case 29: //pldt PLDT ,, Struct
            PLDT.Unload();
            return;
        case 30: //pldt PLDT ,, Struct
            PLDT.Unload();
            return;
        case 31: //pldt PLDT ,, Struct
            PLDT.Unload();
            return;
        case 32: //pld2 PLD2 ,, Struct
            PLD2.Unload();
            return;
        case 33: //pld2 PLD2 ,, Struct
            PLD2.Unload();
            return;
        case 34: //pld2 PLD2 ,, Struct
            PLD2.Unload();
            return;
        case 35: //psdt PSDT ,, Struct
            PSDT.Unload();
            return;
        case 36: //psdt PSDT ,, Struct
            PSDT.Unload();
            return;
        case 37: //psdt PSDT ,, Struct
            PSDT.Unload();
            return;
        case 38: //psdt PSDT ,, Struct
            PSDT.Unload();
            return;
        case 39: //psdt PSDT ,, Struct
            PSDT.Unload();
            return;
        case 40: //ptdt PTDT ,, Struct
            PTDT.Unload();
            return;
        case 41: //ptdt PTDT ,, Struct
            PTDT.Unload();
            return;
        case 42: //ptdt PTDT ,, Struct
            PTDT.Unload();
            return;
        case 43: //ptdt PTDT ,, Struct
            PTDT.Unload();
            return;
        case 44: //ctda Conditions
            CTDAs.Unload();
            return;
        case 45: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 46: //ctda Conditions
            return UNPARSEDDEL_FIELD46;
        case 47: //ctda Conditions
            CTDAs.Unload();
            return;
        case 48: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 49: //ctda_p Conditions
            CTDAs.Unload();
            return;
        case 50: //ctda Conditions
            CTDAs.Unload();
            return;
        case 51: //ctda Conditions
            return UNPARSEDDEL_FIELD51;
        case 52: //idlf Flags
            IDLF.Unload();
            return;
        case 53: //idlc IDLC ,, Struct
            IDLC.Unload();
            return;
        case 54: //idlc_p IDLC ,, Struct
            IDLC.Unload();
            return;
        case 55: //idlt Idle Timer Setting
            IDLT.Unload();
            return;
        case 56: //idla Animation
            IDLA.Unload();
            return;
        case 57: //idlb_p Unused
            IDLB.Unload();
            return;
        case 58: //pke2 Escort Distance
            PKE2.Unload();
            return;
        case 59: //cnam Combat Style
            CNAM.Unload();
            return;
        case 60: //pkfd Follow - Start Location - Trigger Radius
            PKFD.Unload();
            return;
        case 61: //pkpt PKPT ,, Struct
            PKPT.Unload();
            return;
        case 62: //pkpt_p PKPT ,, Struct
            PKPT.Unload();
            return;
        case 63: //pkw3 PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 64: //pkw3 PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 65: //pkw3 PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 66: //pkw3 PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 67: //pkw3 PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 68: //pkw3 PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 69: //pkw3 PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 70: //pkw3 PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 71: //pkw3_p PKW3 ,, Struct
            PKW3.Unload();
            return;
        case 72: //ptd2 PTD2 ,, Struct
            PTD2.Unload();
            return;
        case 73: //ptd2 PTD2 ,, Struct
            PTD2.Unload();
            return;
        case 74: //ptd2 PTD2 ,, Struct
            PTD2.Unload();
            return;
        case 75: //ptd2 PTD2 ,, Struct
            PTD2.Unload();
            return;
        case 76: //pkdd PKDD ,, Struct
            PKDD.Unload();
            return;
        case 77: //pkdd PKDD ,, Struct
            PKDD.Unload();
            return;
        case 78: //pkdd PKDD ,, Struct
            PKDD.Unload();
            return;
        case 79: //pkdd_p PKDD ,, Struct
            PKDD.Unload();
            return;
        case 80: //pkdd PKDD ,, Struct
            PKDD.Unload();
            return;
        case 81: //pkdd_p PKDD ,, Struct
            PKDD.Unload();
            return;
        case 82: //inam Idle
            if(POBA.IsLoaded())
                POBA->INAM.Unload();
            return;
        case 83: //schr_p Basic Script Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCHR.Unload();
            return;
        case 84: //schr Basic Script Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCHR.Unload();
            return;
        case 85: //schr Basic Script Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCHR.Unload();
            return;
        case 86: //schr Basic Script Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCHR.Unload();
            return;
        case 87: //schr Basic Script Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCHR.Unload();
            return;
        case 88: //schr Basic Script Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCHR.Unload();
            return;
        case 89: //scda_p Compiled Embedded Script
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCDA.Unload();
            return;
        case 90: //sctx Embedded Script Source
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCTX.Unload();
            return;
        case 91: //slsd Local Variable Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SLSD.Unload();
            return;
        case 92: //slsd_p Local Variable Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SLSD.Unload();
            return;
        case 93: //slsd Local Variable Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SLSD.Unload();
            return;
        case 94: //slsd_p Local Variable Data
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SLSD.Unload();
            return;
        case 95: //scvr Name
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCVR.Unload();
            return;
        case 96: //scro Global Reference
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCRO.Unload();
            return;
        case 97: //scrv Local Variable
            if(POBA.IsLoaded() && POBA->SCHR.IsLoaded())
                POBA->SCHR->SCRV.Unload();
            return;
        case 98: //tnam Topic
            if(POBA.IsLoaded())
                POBA->TNAM.Unload();
            return;
        case 99: //inam Idle
            if(POEA.IsLoaded())
                POEA->INAM.Unload();
            return;
        case 100: //schr_p Basic Script Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCHR.Unload();
            return;
        case 101: //schr Basic Script Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCHR.Unload();
            return;
        case 102: //schr Basic Script Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCHR.Unload();
            return;
        case 103: //schr Basic Script Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCHR.Unload();
            return;
        case 104: //schr Basic Script Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCHR.Unload();
            return;
        case 105: //schr Basic Script Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCHR.Unload();
            return;
        case 106: //scda_p Compiled Embedded Script
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCDA.Unload();
            return;
        case 107: //sctx Embedded Script Source
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCTX.Unload();
            return;
        case 108: //slsd Local Variable Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SLSD.Unload();
            return;
        case 109: //slsd_p Local Variable Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SLSD.Unload();
            return;
        case 110: //slsd Local Variable Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SLSD.Unload();
            return;
        case 111: //slsd_p Local Variable Data
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SLSD.Unload();
            return;
        case 112: //scvr Name
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCVR.Unload();
            return;
        case 113: //scro Global Reference
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCRO.Unload();
            return;
        case 114: //scrv Local Variable
            if(POEA.IsLoaded() && POEA->SCHR.IsLoaded())
                POEA->SCHR->SCRV.Unload();
            return;
        case 115: //tnam Topic
            if(POEA.IsLoaded())
                POEA->TNAM.Unload();
            return;
        case 116: //inam Idle
            if(POCA.IsLoaded())
                POCA->INAM.Unload();
            return;
        case 117: //schr_p Basic Script Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCHR.Unload();
            return;
        case 118: //schr Basic Script Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCHR.Unload();
            return;
        case 119: //schr Basic Script Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCHR.Unload();
            return;
        case 120: //schr Basic Script Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCHR.Unload();
            return;
        case 121: //schr Basic Script Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCHR.Unload();
            return;
        case 122: //schr Basic Script Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCHR.Unload();
            return;
        case 123: //scda_p Compiled Embedded Script
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCDA.Unload();
            return;
        case 124: //sctx Embedded Script Source
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCTX.Unload();
            return;
        case 125: //slsd Local Variable Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SLSD.Unload();
            return;
        case 126: //slsd_p Local Variable Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SLSD.Unload();
            return;
        case 127: //slsd Local Variable Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SLSD.Unload();
            return;
        case 128: //slsd_p Local Variable Data
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SLSD.Unload();
            return;
        case 129: //scvr Name
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCVR.Unload();
            return;
        case 130: //scro Global Reference
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCRO.Unload();
            return;
        case 131: //scrv Local Variable
            if(POCA.IsLoaded() && POCA->SCHR.IsLoaded())
                POCA->SCHR->SCRV.Unload();
            return;
        case 132: //tnam Topic
            if(POCA.IsLoaded())
                POCA->TNAM.Unload();
            return;
        default:
            return;
        }
    }
}