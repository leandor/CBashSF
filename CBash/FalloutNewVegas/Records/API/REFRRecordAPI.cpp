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
#include "..\REFRRecord.h"

namespace FNV
{
UINT32 REFRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //rclr_p Unused
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return RCLR.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 8: //name Base
            return FORMID_FIELD;
        case 9: //xezn Encounter Zone
            return FORMID_FIELD;
        case 10: //xrgd_p Ragdoll Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGD.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 11: //xrgb_p Ragdoll Biped Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 12: //xprm XPRM ,, Struct
            return FLOAT32_FIELD;
        case 13: //xprm XPRM ,, Struct
            return FLOAT32_FIELD;
        case 14: //xprm XPRM ,, Struct
            return FLOAT32_FIELD;
        case 15: //xprm XPRM ,, Struct
            return FLOAT32_FIELD;
        case 16: //xprm XPRM ,, Struct
            return FLOAT32_FIELD;
        case 17: //xprm XPRM ,, Struct
            return FLOAT32_FIELD;
        case 18: //xprm XPRM ,, Struct
            return FLOAT32_FIELD;
        case 19: //xprm XPRM ,, Struct
            return UINT32_FIELD;
        case 20: //xtri Collision Layer
            return UINT32_FIELD;
        case 21: //xmbo XMBO ,, Struct
            return FLOAT32_FIELD;
        case 22: //xmbo XMBO ,, Struct
            return FLOAT32_FIELD;
        case 23: //xmbo XMBO ,, Struct
            return FLOAT32_FIELD;
        case 24: //xtel XTEL ,, Struct
            return FORMID_FIELD;
        case 25: //xtel XTEL ,, Struct
            return FLOAT32_FIELD;
        case 26: //xtel XTEL ,, Struct
            return FLOAT32_FIELD;
        case 27: //xtel XTEL ,, Struct
            return FLOAT32_FIELD;
        case 28: //xtel XTEL ,, Struct
            return FLOAT32_FIELD;
        case 29: //xtel XTEL ,, Struct
            return FLOAT32_FIELD;
        case 30: //xtel XTEL ,, Struct
            return FLOAT32_FIELD;
        case 31: //xtel XTEL ,, Struct
            return UINT32_FIELD;
        case 32: //fnam Flags
            return UINT8_FIELD;
        case 33: //full Name
            return STRING_FIELD;
        case 34: //tnam TNAM ,, Struct
            return UINT8_FIELD;
        case 35: //tnam_p TNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 36: //wmi1 Reputation
            return FORMID_FIELD;
        case 37: //full_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FULL.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 38: //cnam Audio Location
            return FORMID_FIELD;
        case 39: //bnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return BNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 40: //mnam
            return FLOAT32_FIELD;
        case 41: //nnam
            return FLOAT32_FIELD;
        case 42: //xsrf_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XSRF.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 43: //xsrd_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XSRD.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 44: //xtrg Target
            return FORMID_FIELD;
        case 45: //xlcm Level Modifier
            return SINT32_FIELD;
        case 46: //xprd Idle Time
            return FLOAT32_FIELD;
        case 47: //inam Idle
            return FORMID_FIELD;
        case 48: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 49: //schr Basic Script Data
            return UINT32_FIELD;
        case 50: //schr Basic Script Data
            return UINT32_FIELD;
        case 51: //schr Basic Script Data
            return UINT32_FIELD;
        case 52: //schr Basic Script Data
            return UINT16_FIELD;
        case 53: //schr Basic Script Data
            return UINT16_FIELD;
        case 54: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 55: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 56: //slsd Local Variable Data
            return UINT32_FIELD;
        case 57: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 58: //slsd Local Variable Data
            return UINT8_FIELD;
        case 59: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 60: //scvr Name
            return ISTRING_FIELD;
        case 61: //scro Global Reference
            return FORMID_FIELD;
        case 62: //scrv Local Variable
            return UINT32_FIELD;
        case 63: //tnam Topic
            return FORMID_FIELD;
        case 64: //xrdo XRDO ,, Struct
            return FLOAT32_FIELD;
        case 65: //xrdo XRDO ,, Struct
            return UINT32_FIELD;
        case 66: //xrdo XRDO ,, Struct
            return FLOAT32_FIELD;
        case 67: //xrdo XRDO ,, Struct
            return FORMID_FIELD;
        case 68: //xown Owner
            return FORMID_FIELD;
        case 69: //xrnk Faction rank
            return SINT32_FIELD;
        case 70: //xloc XLOC ,, Struct
            return UINT8_FIELD;
        case 71: //xloc_p XLOC ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 72: //xloc XLOC ,, Struct
            return FORMID_FIELD;
        case 73: //xloc XLOC ,, Struct
            return UINT8_FIELD;
        case 74: //xloc_p XLOC ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 75: //xloc_p XLOC ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 8;
                default:
                    return UNKNOWN_FIELD;
                }
        case 76: //xcnt Count
            return SINT32_FIELD;
        case 77: //xrds Radius
            return FLOAT32_FIELD;
        case 78: //xhlp Health
            return FLOAT32_FIELD;
        case 79: //xrad Radiation
            return FLOAT32_FIELD;
        case 80: //xchg Charge
            return FLOAT32_FIELD;
        case 81: //xamt Type
            return FORMID_FIELD;
        case 82: //xamc Count
            return SINT32_FIELD;
        case 83: //xpwr XPWR ,, Struct
            return FORMID_FIELD;
        case 84: //xpwr XPWR ,, Struct
            return UINT32_FIELD;
        case 85: //xltw Water
            return FORMID_FIELD;
        case 86: //xdcr XDCR ,, Struct
            return FORMID_FIELD;
        case 87: //xdcr_p XDCR ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XDCR.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 88: //xlkr Linked Reference
            return FORMID_FIELD;
        case 89: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 90: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 91: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 92: //xclp_p XCLP ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 93: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 94: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 95: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 96: //xclp_p XCLP ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 97: //xapd Flags
            return UINT8_FIELD;
        case 98: //xapr XAPR ,, Struct
            return FORMID_FIELD;
        case 99: //xapr XAPR ,, Struct
            return FLOAT32_FIELD;
        case 100: //xato Activation Prompt
            return ISTRING_FIELD;
        case 101: //xesp Enable Parent
            return FORMID_FIELD;
        case 102: //xesp Enable Parent
            return UINT8_FIELD;
        case 103: //xesp_p Enable Parent
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 104: //xemi Emittance
            return FORMID_FIELD;
        case 105: //xmbr MultiBound Reference
            return FORMID_FIELD;
        case 106: //xact Action Flag
            return UINT32_FIELD;
        case 107: //xndp XNDP ,, Struct
            return FORMID_FIELD;
        case 108: //xndp XNDP ,, Struct
            return UINT16_FIELD;
        case 109: //xndp_p XNDP ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 110: //xpod Portal Data
            return UNPARSED_FIELD;
        case 111: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 112: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 113: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 114: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 115: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 116: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 117: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 118: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 119: //xptl XPTL ,, Struct
            return FLOAT32_FIELD;
        case 120: //xsed SpeedTree Seed
            return UINT8_FIELD;
        case 121: //xrmr XRMR ,, Struct
            return UINT16_FIELD;
        case 122: //xrmr_p XRMR ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 123: //xlrm Linked Room
            return FORMID_FIELD;
        case 124: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 125: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 126: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 127: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 128: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 129: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 130: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 131: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 132: //xocp XOCP ,, Struct
            return FLOAT32_FIELD;
        case 133: //xord Linked Occlusion Planes
            return UNPARSED_FIELD;
        case 134: //xlod Distant LOD Data
            return FLOAT32_FIELD;
        case 135: //xlod Distant LOD Data
            return FLOAT32_FIELD;
        case 136: //xlod Distant LOD Data
            return FLOAT32_FIELD;
        case 137: //xscl Scale
            return FLOAT32_FIELD;
        case 138: //data Position/Rotation
            return FLOAT32_FIELD;
        case 139: //data Position/Rotation
            return FLOAT32_FIELD;
        case 140: //data Position/Rotation
            return FLOAT32_FIELD;
        case 141: //data Position/Rotation
            return FLOAT32_FIELD;
        case 142: //data Position/Rotation
            return FLOAT32_FIELD;
        case 143: //data Position/Rotation
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * REFRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //rclr_p Unused
            *FieldValues = RCLR.value;
            return NULL;
        case 8: //name Base
            return NAME.IsLoaded() ? &NAME->value8 : NULL;
        case 9: //xezn Encounter Zone
            return XEZN.IsLoaded() ? &XEZN->value9 : NULL;
        case 10: //xrgd_p Ragdoll Data
            *FieldValues = XRGD.value;
            return NULL;
        case 11: //xrgb_p Ragdoll Biped Data
            *FieldValues = XRGB.value;
            return NULL;
        case 12: //xprm XPRM ,, Struct
            return XPRM.IsLoaded() ? &XPRM->value12 : NULL;
        case 13: //xprm XPRM ,, Struct
            return XPRM.IsLoaded() ? &XPRM->value13 : NULL;
        case 14: //xprm XPRM ,, Struct
            return XPRM.IsLoaded() ? &XPRM->value14 : NULL;
        case 15: //xprm XPRM ,, Struct
            return XPRM.IsLoaded() ? &XPRM->value15 : NULL;
        case 16: //xprm XPRM ,, Struct
            return XPRM.IsLoaded() ? &XPRM->value16 : NULL;
        case 17: //xprm XPRM ,, Struct
            return XPRM.IsLoaded() ? &XPRM->value17 : NULL;
        case 18: //xprm XPRM ,, Struct
            return XPRM.IsLoaded() ? &XPRM->value18 : NULL;
        case 19: //xprm XPRM ,, Struct
            return XPRM.IsLoaded() ? &XPRM->value19 : NULL;
        case 20: //xtri Collision Layer
            return XTRI.IsLoaded() ? &XTRI->value20 : NULL;
        case 21: //xmbo XMBO ,, Struct
            return XMBO.IsLoaded() ? &XMBO->value21 : NULL;
        case 22: //xmbo XMBO ,, Struct
            return XMBO.IsLoaded() ? &XMBO->value22 : NULL;
        case 23: //xmbo XMBO ,, Struct
            return XMBO.IsLoaded() ? &XMBO->value23 : NULL;
        case 24: //xtel XTEL ,, Struct
            return XTEL.IsLoaded() ? &XTEL->value24 : NULL;
        case 25: //xtel XTEL ,, Struct
            return XTEL.IsLoaded() ? &XTEL->value25 : NULL;
        case 26: //xtel XTEL ,, Struct
            return XTEL.IsLoaded() ? &XTEL->value26 : NULL;
        case 27: //xtel XTEL ,, Struct
            return XTEL.IsLoaded() ? &XTEL->value27 : NULL;
        case 28: //xtel XTEL ,, Struct
            return XTEL.IsLoaded() ? &XTEL->value28 : NULL;
        case 29: //xtel XTEL ,, Struct
            return XTEL.IsLoaded() ? &XTEL->value29 : NULL;
        case 30: //xtel XTEL ,, Struct
            return XTEL.IsLoaded() ? &XTEL->value30 : NULL;
        case 31: //xtel XTEL ,, Struct
            return XTEL.IsLoaded() ? &XTEL->value31 : NULL;
        case 32: //fnam Flags
            return XMRK.IsLoaded() ? &XMRK->FNAM->value32 : NULL;
        case 33: //full Name
            return FULLReq.value;
        case 34: //tnam TNAM ,, Struct
            return TNAM.IsLoaded() ? &TNAM->value34 : NULL;
        case 35: //tnam_p TNAM ,, Struct
            *FieldValues = TNAM.IsLoaded() ? &TNAM->value35[0] : NULL;
            return NULL;
        case 36: //wmi1 Reputation
            return WMI1.IsLoaded() ? &WMI1->value36 : NULL;
        case 37: //full_p Unknown
            *FieldValues = (MMRK.IsLoaded()) ? MMRK->FULL.value : NULL;
            return NULL;
        case 38: //cnam Audio Location
            return MMRK.IsLoaded() ? &MMRK->CNAM->value38 : NULL;
        case 39: //bnam_p Unknown
            *FieldValues = (MMRK.IsLoaded()) ? MMRK->BNAM.value : NULL;
            return NULL;
        case 40: //mnam
            return MMRK.IsLoaded() ? &MMRK->MNAM->value40 : NULL;
        case 41: //nnam
            return MMRK.IsLoaded() ? &MMRK->NNAM->value41 : NULL;
        case 42: //xsrf_p Unknown
            *FieldValues = XSRF.value;
            return NULL;
        case 43: //xsrd_p Unknown
            *FieldValues = XSRD.value;
            return NULL;
        case 44: //xtrg Target
            return XTRG.IsLoaded() ? &XTRG->value44 : NULL;
        case 45: //xlcm Level Modifier
            return XLCM.IsLoaded() ? &XLCM->value45 : NULL;
        case 46: //xprd Idle Time
            return XPRD.IsLoaded() ? &XPRD->XPRD->value46 : NULL;
        case 47: //inam Idle
            return XPRD.IsLoaded() ? &XPRD->INAM->value47 : NULL;
        case 48: //schr_p Basic Script Data
            *FieldValues = (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value48[0] : NULL;
            return NULL;
        case 49: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value49 : NULL;
        case 50: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value50 : NULL;
        case 51: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value51 : NULL;
        case 52: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value52 : NULL;
        case 53: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value53 : NULL;
        case 54: //scda_p Compiled Embedded Script
            *FieldValues = (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? XPRD->SCHR->SCDA.value : NULL;
            return NULL;
        case 55: //sctx Embedded Script Source
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? XPRD->SCHR->SCTX.value : NULL;
        case 56: //slsd Local Variable Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SLSD->value56 : NULL;
        case 57: //slsd_p Local Variable Data
            *FieldValues = (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SLSD->value57[0] : NULL;
            return NULL;
        case 58: //slsd Local Variable Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SLSD->value58 : NULL;
        case 59: //slsd_p Local Variable Data
            *FieldValues = (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SLSD->value59[0] : NULL;
            return NULL;
        case 60: //scvr Name
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? XPRD->SCHR->SCVR.value : NULL;
        case 61: //scro Global Reference
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCRO->value61 : NULL;
        case 62: //scrv Local Variable
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCRV->value62 : NULL;
        case 63: //tnam Topic
            return XPRD.IsLoaded() ? &XPRD->TNAM->value63 : NULL;
        case 64: //xrdo XRDO ,, Struct
            return XRDO.IsLoaded() ? &XRDO->value64 : NULL;
        case 65: //xrdo XRDO ,, Struct
            return XRDO.IsLoaded() ? &XRDO->value65 : NULL;
        case 66: //xrdo XRDO ,, Struct
            return XRDO.IsLoaded() ? &XRDO->value66 : NULL;
        case 67: //xrdo XRDO ,, Struct
            return XRDO.IsLoaded() ? &XRDO->value67 : NULL;
        case 68: //xown Owner
            return XOWN.IsLoaded() ? &XOWN->XOWN->value68 : NULL;
        case 69: //xrnk Faction rank
            return XOWN.IsLoaded() ? &XOWN->XRNK->value69 : NULL;
        case 70: //xloc XLOC ,, Struct
            return XLOC.IsLoaded() ? &XLOC->value70 : NULL;
        case 71: //xloc_p XLOC ,, Struct
            *FieldValues = XLOC.IsLoaded() ? &XLOC->value71[0] : NULL;
            return NULL;
        case 72: //xloc XLOC ,, Struct
            return XLOC.IsLoaded() ? &XLOC->value72 : NULL;
        case 73: //xloc XLOC ,, Struct
            return XLOC.IsLoaded() ? &XLOC->value73 : NULL;
        case 74: //xloc_p XLOC ,, Struct
            *FieldValues = XLOC.IsLoaded() ? &XLOC->value74[0] : NULL;
            return NULL;
        case 75: //xloc_p XLOC ,, Struct
            *FieldValues = XLOC.IsLoaded() ? &XLOC->value75[0] : NULL;
            return NULL;
        case 76: //xcnt Count
            return XCNT.IsLoaded() ? &XCNT->value76 : NULL;
        case 77: //xrds Radius
            return XRDS.IsLoaded() ? &XRDS->value77 : NULL;
        case 78: //xhlp Health
            return XHLP.IsLoaded() ? &XHLP->value78 : NULL;
        case 79: //xrad Radiation
            return XRAD.IsLoaded() ? &XRAD->value79 : NULL;
        case 80: //xchg Charge
            return XCHG.IsLoaded() ? &XCHG->value80 : NULL;
        case 81: //xamt Type
            return XAMT.IsLoaded() ? &XAMT->XAMT->value81 : NULL;
        case 82: //xamc Count
            return XAMT.IsLoaded() ? &XAMT->XAMC->value82 : NULL;
        case 83: //xpwr XPWR ,, Struct
            return XPWR.IsLoaded() ? &XPWR->value83 : NULL;
        case 84: //xpwr XPWR ,, Struct
            return XPWR.IsLoaded() ? &XPWR->value84 : NULL;
        case 85: //xltw Water
            return XLTW.IsLoaded() ? &XLTW->value85 : NULL;
        case 86: //xdcr XDCR ,, Struct
            return XDCR.IsLoaded() ? &XDCR->value86 : NULL;
        case 87: //xdcr_p XDCR ,, Struct
            *FieldValues = XDCR.value;
            return NULL;
        case 88: //xlkr Linked Reference
            return XLKR.IsLoaded() ? &XLKR->value88 : NULL;
        case 89: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value89 : NULL;
        case 90: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value90 : NULL;
        case 91: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value91 : NULL;
        case 92: //xclp_p XCLP ,, Struct
            *FieldValues = XCLP.IsLoaded() ? &XCLP->value92[0] : NULL;
            return NULL;
        case 93: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value93 : NULL;
        case 94: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value94 : NULL;
        case 95: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value95 : NULL;
        case 96: //xclp_p XCLP ,, Struct
            *FieldValues = XCLP.IsLoaded() ? &XCLP->value96[0] : NULL;
            return NULL;
        case 97: //xapd Flags
            return XAPD.IsLoaded() ? &XAPD->value97 : NULL;
        case 98: //xapr XAPR ,, Struct
            return XAPR.IsLoaded() ? &XAPR->value98 : NULL;
        case 99: //xapr XAPR ,, Struct
            return XAPR.IsLoaded() ? &XAPR->value99 : NULL;
        case 100: //xato Activation Prompt
            return XATO.value;
        case 101: //xesp Enable Parent
            return XESP.IsLoaded() ? &XESP->value101 : NULL;
        case 102: //xesp Enable Parent
            return XESP.IsLoaded() ? &XESP->value102 : NULL;
        case 103: //xesp_p Enable Parent
            *FieldValues = XESP.IsLoaded() ? &XESP->value103[0] : NULL;
            return NULL;
        case 104: //xemi Emittance
            return XEMI.IsLoaded() ? &XEMI->value104 : NULL;
        case 105: //xmbr MultiBound Reference
            return XMBR.IsLoaded() ? &XMBR->value105 : NULL;
        case 106: //xact Action Flag
            return XACT.IsLoaded() ? &XACT->value106 : NULL;
        case 107: //xndp XNDP ,, Struct
            return XNDP.IsLoaded() ? &XNDP->value107 : NULL;
        case 108: //xndp XNDP ,, Struct
            return XNDP.IsLoaded() ? &XNDP->value108 : NULL;
        case 109: //xndp_p XNDP ,, Struct
            *FieldValues = XNDP.IsLoaded() ? &XNDP->value109[0] : NULL;
            return NULL;
        case 110: //xpod Portal Data
            return UNPARSEDGET_FIELD110;
        case 111: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value111 : NULL;
        case 112: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value112 : NULL;
        case 113: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value113 : NULL;
        case 114: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value114 : NULL;
        case 115: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value115 : NULL;
        case 116: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value116 : NULL;
        case 117: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value117 : NULL;
        case 118: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value118 : NULL;
        case 119: //xptl XPTL ,, Struct
            return XPTL.IsLoaded() ? &XPTL->value119 : NULL;
        case 120: //xsed SpeedTree Seed
            return XSED.IsLoaded() ? &XSED->value120 : NULL;
        case 121: //xrmr XRMR ,, Struct
            return XRMR.IsLoaded() ? &XRMR->value121 : NULL;
        case 122: //xrmr_p XRMR ,, Struct
            *FieldValues = XRMR.IsLoaded() ? &XRMR->value122[0] : NULL;
            return NULL;
        case 123: //xlrm Linked Room
            return XLRM.IsLoaded() ? &XLRM->value123 : NULL;
        case 124: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value124 : NULL;
        case 125: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value125 : NULL;
        case 126: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value126 : NULL;
        case 127: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value127 : NULL;
        case 128: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value128 : NULL;
        case 129: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value129 : NULL;
        case 130: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value130 : NULL;
        case 131: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value131 : NULL;
        case 132: //xocp XOCP ,, Struct
            return XOCP.IsLoaded() ? &XOCP->value132 : NULL;
        case 133: //xord Linked Occlusion Planes
            return UNPARSEDGET_FIELD133;
        case 134: //xlod Distant LOD Data
            return XLOD.IsLoaded() ? &XLOD->value134 : NULL;
        case 135: //xlod Distant LOD Data
            return XLOD.IsLoaded() ? &XLOD->value135 : NULL;
        case 136: //xlod Distant LOD Data
            return XLOD.IsLoaded() ? &XLOD->value136 : NULL;
        case 137: //xscl Scale
            return XSCL.IsLoaded() ? &XSCL->value137 : NULL;
        case 138: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value138 : NULL;
        case 139: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value139 : NULL;
        case 140: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value140 : NULL;
        case 141: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value141 : NULL;
        case 142: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value142 : NULL;
        case 143: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value143 : NULL;
        default:
            return NULL;
        }
    }

bool REFRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //rclr_p Unused
            RCLR.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 8: //name Base
            NAME.Load();
            NAME->value8 = *(FORMID *)FieldValue;
            return true;
        case 9: //xezn Encounter Zone
            XEZN.Load();
            XEZN->value9 = *(FORMID *)FieldValue;
            return true;
        case 10: //xrgd_p Ragdoll Data
            XRGD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //xrgb_p Ragdoll Biped Data
            XRGB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 12: //xprm XPRM ,, Struct
            XPRM.Load();
            XPRM->value12 = *(FLOAT32 *)FieldValue;
            break;
        case 13: //xprm XPRM ,, Struct
            XPRM.Load();
            XPRM->value13 = *(FLOAT32 *)FieldValue;
            break;
        case 14: //xprm XPRM ,, Struct
            XPRM.Load();
            XPRM->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //xprm XPRM ,, Struct
            XPRM.Load();
            XPRM->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //xprm XPRM ,, Struct
            XPRM.Load();
            XPRM->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //xprm XPRM ,, Struct
            XPRM.Load();
            XPRM->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //xprm XPRM ,, Struct
            XPRM.Load();
            XPRM->value18 = *(FLOAT32 *)FieldValue;
            break;
        case 19: //xprm XPRM ,, Struct
            XPRM.Load();
            XPRM->value19 = *(UINT32 *)FieldValue;
            break;
        case 20: //xtri Collision Layer
            XTRI.Load();
            XTRI->value20 = *(UINT32 *)FieldValue;
            break;
        case 21: //xmbo XMBO ,, Struct
            XMBO.Load();
            XMBO->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //xmbo XMBO ,, Struct
            XMBO.Load();
            XMBO->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //xmbo XMBO ,, Struct
            XMBO.Load();
            XMBO->value23 = *(FLOAT32 *)FieldValue;
            break;
        case 24: //xtel XTEL ,, Struct
            XTEL.Load();
            XTEL->value24 = *(FORMID *)FieldValue;
            return true;
        case 25: //xtel XTEL ,, Struct
            XTEL.Load();
            XTEL->value25 = *(FLOAT32 *)FieldValue;
            break;
        case 26: //xtel XTEL ,, Struct
            XTEL.Load();
            XTEL->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //xtel XTEL ,, Struct
            XTEL.Load();
            XTEL->value27 = *(FLOAT32 *)FieldValue;
            break;
        case 28: //xtel XTEL ,, Struct
            XTEL.Load();
            XTEL->value28 = *(FLOAT32 *)FieldValue;
            break;
        case 29: //xtel XTEL ,, Struct
            XTEL.Load();
            XTEL->value29 = *(FLOAT32 *)FieldValue;
            break;
        case 30: //xtel XTEL ,, Struct
            XTEL.Load();
            XTEL->value30 = *(FLOAT32 *)FieldValue;
            break;
        case 31: //xtel XTEL ,, Struct
            XTEL.Load();
            XTEL->value31 = *(UINT32 *)FieldValue;
            break;
        case 32: //fnam Flags
            XMRK.Load();
            XMRK->FNAM.Load();
            XMRK->FNAM->value32 = *(UINT8 *)FieldValue;
            break;
        case 33: //full Name
            FULLReq.Copy((STRING)FieldValue);
            break;
        case 34: //tnam TNAM ,, Struct
            TNAM.Load();
            TNAM->value34 = *(UINT8 *)FieldValue;
            break;
        case 35: //tnam_p TNAM ,, Struct
            if(ArraySize != 1)
                break;
            TNAM.Load();
            TNAM->value35[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 36: //wmi1 Reputation
            WMI1.Load();
            WMI1->value36 = *(FORMID *)FieldValue;
            return true;
        case 37: //full_p Unknown
            MMRK.Load();
            MMRK->FULL.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 38: //cnam Audio Location
            MMRK.Load();
            MMRK->CNAM.Load();
            MMRK->CNAM->value38 = *(FORMID *)FieldValue;
            return true;
        case 39: //bnam_p Unknown
            MMRK.Load();
            MMRK->BNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 40: //mnam
            MMRK.Load();
            MMRK->MNAM.Load();
            MMRK->MNAM->value40 = *(FLOAT32 *)FieldValue;
            break;
        case 41: //nnam
            MMRK.Load();
            MMRK->NNAM.Load();
            MMRK->NNAM->value41 = *(FLOAT32 *)FieldValue;
            break;
        case 42: //xsrf_p Unknown
            XSRF.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 43: //xsrd_p Unknown
            XSRD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 44: //xtrg Target
            XTRG.Load();
            XTRG->value44 = *(FORMID *)FieldValue;
            return true;
        case 45: //xlcm Level Modifier
            XLCM.Load();
            XLCM->value45 = *(SINT32 *)FieldValue;
            break;
        case 46: //xprd Idle Time
            XPRD.Load();
            XPRD->XPRD.Load();
            XPRD->XPRD->value46 = *(FLOAT32 *)FieldValue;
            break;
        case 47: //inam Idle
            XPRD.Load();
            XPRD->INAM.Load();
            XPRD->INAM->value47 = *(FORMID *)FieldValue;
            return true;
        case 48: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value48[0] = ((UINT8 *)FieldValue)[0];
            XPRD->SCHR->SCHR->value48[1] = ((UINT8 *)FieldValue)[1];
            XPRD->SCHR->SCHR->value48[2] = ((UINT8 *)FieldValue)[2];
            XPRD->SCHR->SCHR->value48[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 49: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value49 = *(UINT32 *)FieldValue;
            break;
        case 50: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value50 = *(UINT32 *)FieldValue;
            break;
        case 51: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value51 = *(UINT32 *)FieldValue;
            break;
        case 52: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value52 = *(UINT16 *)FieldValue;
            break;
        case 53: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value53 = *(UINT16 *)FieldValue;
            break;
        case 54: //scda_p Compiled Embedded Script
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 55: //sctx Embedded Script Source
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 56: //slsd Local Variable Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SLSD.Load();
            XPRD->SCHR->SLSD->value56 = *(UINT32 *)FieldValue;
            break;
        case 57: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SLSD.Load();
            XPRD->SCHR->SLSD->value57[0] = ((UINT8 *)FieldValue)[0];
            XPRD->SCHR->SLSD->value57[1] = ((UINT8 *)FieldValue)[1];
            XPRD->SCHR->SLSD->value57[2] = ((UINT8 *)FieldValue)[2];
            XPRD->SCHR->SLSD->value57[3] = ((UINT8 *)FieldValue)[3];
            XPRD->SCHR->SLSD->value57[4] = ((UINT8 *)FieldValue)[4];
            XPRD->SCHR->SLSD->value57[5] = ((UINT8 *)FieldValue)[5];
            XPRD->SCHR->SLSD->value57[6] = ((UINT8 *)FieldValue)[6];
            XPRD->SCHR->SLSD->value57[7] = ((UINT8 *)FieldValue)[7];
            XPRD->SCHR->SLSD->value57[8] = ((UINT8 *)FieldValue)[8];
            XPRD->SCHR->SLSD->value57[9] = ((UINT8 *)FieldValue)[9];
            XPRD->SCHR->SLSD->value57[10] = ((UINT8 *)FieldValue)[10];
            XPRD->SCHR->SLSD->value57[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 58: //slsd Local Variable Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SLSD.Load();
            XPRD->SCHR->SLSD->value58 = *(UINT8 *)FieldValue;
            break;
        case 59: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SLSD.Load();
            XPRD->SCHR->SLSD->value59[0] = ((UINT8 *)FieldValue)[0];
            XPRD->SCHR->SLSD->value59[1] = ((UINT8 *)FieldValue)[1];
            XPRD->SCHR->SLSD->value59[2] = ((UINT8 *)FieldValue)[2];
            XPRD->SCHR->SLSD->value59[3] = ((UINT8 *)FieldValue)[3];
            XPRD->SCHR->SLSD->value59[4] = ((UINT8 *)FieldValue)[4];
            XPRD->SCHR->SLSD->value59[5] = ((UINT8 *)FieldValue)[5];
            XPRD->SCHR->SLSD->value59[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 60: //scvr Name
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 61: //scro Global Reference
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCRO.Load();
            XPRD->SCHR->SCRO->value61 = *(FORMID *)FieldValue;
            return true;
        case 62: //scrv Local Variable
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCRV.Load();
            XPRD->SCHR->SCRV->value62 = *(UINT32 *)FieldValue;
            break;
        case 63: //tnam Topic
            XPRD.Load();
            XPRD->TNAM.Load();
            XPRD->TNAM->value63 = *(FORMID *)FieldValue;
            return true;
        case 64: //xrdo XRDO ,, Struct
            XRDO.Load();
            XRDO->value64 = *(FLOAT32 *)FieldValue;
            break;
        case 65: //xrdo XRDO ,, Struct
            XRDO.Load();
            XRDO->value65 = *(UINT32 *)FieldValue;
            break;
        case 66: //xrdo XRDO ,, Struct
            XRDO.Load();
            XRDO->value66 = *(FLOAT32 *)FieldValue;
            break;
        case 67: //xrdo XRDO ,, Struct
            XRDO.Load();
            XRDO->value67 = *(FORMID *)FieldValue;
            return true;
        case 68: //xown Owner
            XOWN.Load();
            XOWN->XOWN.Load();
            XOWN->XOWN->value68 = *(FORMID *)FieldValue;
            return true;
        case 69: //xrnk Faction rank
            XOWN.Load();
            XOWN->XRNK.Load();
            XOWN->XRNK->value69 = *(SINT32 *)FieldValue;
            break;
        case 70: //xloc XLOC ,, Struct
            XLOC.Load();
            XLOC->value70 = *(UINT8 *)FieldValue;
            break;
        case 71: //xloc_p XLOC ,, Struct
            if(ArraySize != 3)
                break;
            XLOC.Load();
            XLOC->value71[0] = ((UINT8 *)FieldValue)[0];
            XLOC->value71[1] = ((UINT8 *)FieldValue)[1];
            XLOC->value71[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 72: //xloc XLOC ,, Struct
            XLOC.Load();
            XLOC->value72 = *(FORMID *)FieldValue;
            return true;
        case 73: //xloc XLOC ,, Struct
            XLOC.Load();
            XLOC->value73 = *(UINT8 *)FieldValue;
            break;
        case 74: //xloc_p XLOC ,, Struct
            if(ArraySize != 3)
                break;
            XLOC.Load();
            XLOC->value74[0] = ((UINT8 *)FieldValue)[0];
            XLOC->value74[1] = ((UINT8 *)FieldValue)[1];
            XLOC->value74[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 75: //xloc_p XLOC ,, Struct
            if(ArraySize != 8)
                break;
            XLOC.Load();
            XLOC->value75[0] = ((UINT8 *)FieldValue)[0];
            XLOC->value75[1] = ((UINT8 *)FieldValue)[1];
            XLOC->value75[2] = ((UINT8 *)FieldValue)[2];
            XLOC->value75[3] = ((UINT8 *)FieldValue)[3];
            XLOC->value75[4] = ((UINT8 *)FieldValue)[4];
            XLOC->value75[5] = ((UINT8 *)FieldValue)[5];
            XLOC->value75[6] = ((UINT8 *)FieldValue)[6];
            XLOC->value75[7] = ((UINT8 *)FieldValue)[7];
            break;
        case 76: //xcnt Count
            XCNT.Load();
            XCNT->value76 = *(SINT32 *)FieldValue;
            break;
        case 77: //xrds Radius
            XRDS.Load();
            XRDS->value77 = *(FLOAT32 *)FieldValue;
            break;
        case 78: //xhlp Health
            XHLP.Load();
            XHLP->value78 = *(FLOAT32 *)FieldValue;
            break;
        case 79: //xrad Radiation
            XRAD.Load();
            XRAD->value79 = *(FLOAT32 *)FieldValue;
            break;
        case 80: //xchg Charge
            XCHG.Load();
            XCHG->value80 = *(FLOAT32 *)FieldValue;
            break;
        case 81: //xamt Type
            XAMT.Load();
            XAMT->XAMT.Load();
            XAMT->XAMT->value81 = *(FORMID *)FieldValue;
            return true;
        case 82: //xamc Count
            XAMT.Load();
            XAMT->XAMC.Load();
            XAMT->XAMC->value82 = *(SINT32 *)FieldValue;
            break;
        case 83: //xpwr XPWR ,, Struct
            XPWR.Load();
            XPWR->value83 = *(FORMID *)FieldValue;
            return true;
        case 84: //xpwr XPWR ,, Struct
            XPWR.Load();
            XPWR->value84 = *(UINT32 *)FieldValue;
            break;
        case 85: //xltw Water
            XLTW.Load();
            XLTW->value85 = *(FORMID *)FieldValue;
            return true;
        case 86: //xdcr XDCR ,, Struct
            XDCR.Load();
            XDCR->value86 = *(FORMID *)FieldValue;
            return true;
        case 87: //xdcr_p XDCR ,, Struct
            XDCR.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 88: //xlkr Linked Reference
            XLKR.Load();
            XLKR->value88 = *(FORMID *)FieldValue;
            return true;
        case 89: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value89 = *(UINT8 *)FieldValue;
            break;
        case 90: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value90 = *(UINT8 *)FieldValue;
            break;
        case 91: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value91 = *(UINT8 *)FieldValue;
            break;
        case 92: //xclp_p XCLP ,, Struct
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->value92[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 93: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value93 = *(UINT8 *)FieldValue;
            break;
        case 94: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value94 = *(UINT8 *)FieldValue;
            break;
        case 95: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value95 = *(UINT8 *)FieldValue;
            break;
        case 96: //xclp_p XCLP ,, Struct
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->value96[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 97: //xapd Flags
            XAPD.Load();
            XAPD->value97 = *(UINT8 *)FieldValue;
            break;
        case 98: //xapr XAPR ,, Struct
            XAPR.Load();
            XAPR->value98 = *(FORMID *)FieldValue;
            return true;
        case 99: //xapr XAPR ,, Struct
            XAPR.Load();
            XAPR->value99 = *(FLOAT32 *)FieldValue;
            break;
        case 100: //xato Activation Prompt
            XATO.Copy((STRING)FieldValue);
            break;
        case 101: //xesp Enable Parent
            XESP.Load();
            XESP->value101 = *(FORMID *)FieldValue;
            return true;
        case 102: //xesp Enable Parent
            XESP.Load();
            XESP->value102 = *(UINT8 *)FieldValue;
            break;
        case 103: //xesp_p Enable Parent
            if(ArraySize != 3)
                break;
            XESP.Load();
            XESP->value103[0] = ((UINT8 *)FieldValue)[0];
            XESP->value103[1] = ((UINT8 *)FieldValue)[1];
            XESP->value103[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 104: //xemi Emittance
            XEMI.Load();
            XEMI->value104 = *(FORMID *)FieldValue;
            return true;
        case 105: //xmbr MultiBound Reference
            XMBR.Load();
            XMBR->value105 = *(FORMID *)FieldValue;
            return true;
        case 106: //xact Action Flag
            XACT.Load();
            XACT->value106 = *(UINT32 *)FieldValue;
            break;
        case 107: //xndp XNDP ,, Struct
            XNDP.Load();
            XNDP->value107 = *(FORMID *)FieldValue;
            return true;
        case 108: //xndp XNDP ,, Struct
            XNDP.Load();
            XNDP->value108 = *(UINT16 *)FieldValue;
            break;
        case 109: //xndp_p XNDP ,, Struct
            if(ArraySize != 2)
                break;
            XNDP.Load();
            XNDP->value109[0] = ((UINT8 *)FieldValue)[0];
            XNDP->value109[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 110: //xpod Portal Data
            return UNPARSEDGET_FIELD110;
        case 111: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value111 = *(FLOAT32 *)FieldValue;
            break;
        case 112: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value112 = *(FLOAT32 *)FieldValue;
            break;
        case 113: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value113 = *(FLOAT32 *)FieldValue;
            break;
        case 114: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value114 = *(FLOAT32 *)FieldValue;
            break;
        case 115: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value115 = *(FLOAT32 *)FieldValue;
            break;
        case 116: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value116 = *(FLOAT32 *)FieldValue;
            break;
        case 117: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value117 = *(FLOAT32 *)FieldValue;
            break;
        case 118: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value118 = *(FLOAT32 *)FieldValue;
            break;
        case 119: //xptl XPTL ,, Struct
            XPTL.Load();
            XPTL->value119 = *(FLOAT32 *)FieldValue;
            break;
        case 120: //xsed SpeedTree Seed
            XSED.Load();
            XSED->value120 = *(UINT8 *)FieldValue;
            break;
        case 121: //xrmr XRMR ,, Struct
            XRMR.Load();
            XRMR->value121 = *(UINT16 *)FieldValue;
            break;
        case 122: //xrmr_p XRMR ,, Struct
            if(ArraySize != 2)
                break;
            XRMR.Load();
            XRMR->value122[0] = ((UINT8 *)FieldValue)[0];
            XRMR->value122[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 123: //xlrm Linked Room
            XLRM.Load();
            XLRM->value123 = *(FORMID *)FieldValue;
            return true;
        case 124: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value124 = *(FLOAT32 *)FieldValue;
            break;
        case 125: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value125 = *(FLOAT32 *)FieldValue;
            break;
        case 126: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value126 = *(FLOAT32 *)FieldValue;
            break;
        case 127: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value127 = *(FLOAT32 *)FieldValue;
            break;
        case 128: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value128 = *(FLOAT32 *)FieldValue;
            break;
        case 129: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value129 = *(FLOAT32 *)FieldValue;
            break;
        case 130: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value130 = *(FLOAT32 *)FieldValue;
            break;
        case 131: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value131 = *(FLOAT32 *)FieldValue;
            break;
        case 132: //xocp XOCP ,, Struct
            XOCP.Load();
            XOCP->value132 = *(FLOAT32 *)FieldValue;
            break;
        case 133: //xord Linked Occlusion Planes
            return UNPARSEDGET_FIELD133;
        case 134: //xlod Distant LOD Data
            XLOD.Load();
            XLOD->value134 = *(FLOAT32 *)FieldValue;
            break;
        case 135: //xlod Distant LOD Data
            XLOD.Load();
            XLOD->value135 = *(FLOAT32 *)FieldValue;
            break;
        case 136: //xlod Distant LOD Data
            XLOD.Load();
            XLOD->value136 = *(FLOAT32 *)FieldValue;
            break;
        case 137: //xscl Scale
            XSCL.Load();
            XSCL->value137 = *(FLOAT32 *)FieldValue;
            break;
        case 138: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value138 = *(FLOAT32 *)FieldValue;
            break;
        case 139: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value139 = *(FLOAT32 *)FieldValue;
            break;
        case 140: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value140 = *(FLOAT32 *)FieldValue;
            break;
        case 141: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value141 = *(FLOAT32 *)FieldValue;
            break;
        case 142: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value142 = *(FLOAT32 *)FieldValue;
            break;
        case 143: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value143 = *(FLOAT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void REFRRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //rclr_p Unused
            RCLR.Unload();
            return;
        case 8: //name Base
            NAME.Unload();
            return;
        case 9: //xezn Encounter Zone
            XEZN.Unload();
            return;
        case 10: //xrgd_p Ragdoll Data
            XRGD.Unload();
            return;
        case 11: //xrgb_p Ragdoll Biped Data
            XRGB.Unload();
            return;
        case 12: //xprm XPRM ,, Struct
            XPRM.Unload();
            return;
        case 13: //xprm XPRM ,, Struct
            XPRM.Unload();
            return;
        case 14: //xprm XPRM ,, Struct
            XPRM.Unload();
            return;
        case 15: //xprm XPRM ,, Struct
            XPRM.Unload();
            return;
        case 16: //xprm XPRM ,, Struct
            XPRM.Unload();
            return;
        case 17: //xprm XPRM ,, Struct
            XPRM.Unload();
            return;
        case 18: //xprm XPRM ,, Struct
            XPRM.Unload();
            return;
        case 19: //xprm XPRM ,, Struct
            XPRM.Unload();
            return;
        case 20: //xtri Collision Layer
            XTRI.Unload();
            return;
        case 21: //xmbo XMBO ,, Struct
            XMBO.Unload();
            return;
        case 22: //xmbo XMBO ,, Struct
            XMBO.Unload();
            return;
        case 23: //xmbo XMBO ,, Struct
            XMBO.Unload();
            return;
        case 24: //xtel XTEL ,, Struct
            XTEL.Unload();
            return;
        case 25: //xtel XTEL ,, Struct
            XTEL.Unload();
            return;
        case 26: //xtel XTEL ,, Struct
            XTEL.Unload();
            return;
        case 27: //xtel XTEL ,, Struct
            XTEL.Unload();
            return;
        case 28: //xtel XTEL ,, Struct
            XTEL.Unload();
            return;
        case 29: //xtel XTEL ,, Struct
            XTEL.Unload();
            return;
        case 30: //xtel XTEL ,, Struct
            XTEL.Unload();
            return;
        case 31: //xtel XTEL ,, Struct
            XTEL.Unload();
            return;
        case 32: //fnam Flags
            if(XMRK.IsLoaded())
                XMRK->FNAM.Unload();
            return;
        case 33: //full Name
            FULLReq.Unload();
            return;
        case 34: //tnam TNAM ,, Struct
            TNAM.Unload();
            return;
        case 35: //tnam_p TNAM ,, Struct
            TNAM.Unload();
            return;
        case 36: //wmi1 Reputation
            WMI1.Unload();
            return;
        case 37: //full_p Unknown
            if(MMRK.IsLoaded())
                MMRK->FULL.Unload();
            return;
        case 38: //cnam Audio Location
            if(MMRK.IsLoaded())
                MMRK->CNAM.Unload();
            return;
        case 39: //bnam_p Unknown
            if(MMRK.IsLoaded())
                MMRK->BNAM.Unload();
            return;
        case 40: //mnam
            if(MMRK.IsLoaded())
                MMRK->MNAM.Unload();
            return;
        case 41: //nnam
            if(MMRK.IsLoaded())
                MMRK->NNAM.Unload();
            return;
        case 42: //xsrf_p Unknown
            XSRF.Unload();
            return;
        case 43: //xsrd_p Unknown
            XSRD.Unload();
            return;
        case 44: //xtrg Target
            XTRG.Unload();
            return;
        case 45: //xlcm Level Modifier
            XLCM.Unload();
            return;
        case 46: //xprd Idle Time
            if(XPRD.IsLoaded())
                XPRD->XPRD.Unload();
            return;
        case 47: //inam Idle
            if(XPRD.IsLoaded())
                XPRD->INAM.Unload();
            return;
        case 48: //schr_p Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 49: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 50: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 51: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 52: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 53: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 54: //scda_p Compiled Embedded Script
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCDA.Unload();
            return;
        case 55: //sctx Embedded Script Source
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCTX.Unload();
            return;
        case 56: //slsd Local Variable Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SLSD.Unload();
            return;
        case 57: //slsd_p Local Variable Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SLSD.Unload();
            return;
        case 58: //slsd Local Variable Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SLSD.Unload();
            return;
        case 59: //slsd_p Local Variable Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SLSD.Unload();
            return;
        case 60: //scvr Name
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCVR.Unload();
            return;
        case 61: //scro Global Reference
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCRO.Unload();
            return;
        case 62: //scrv Local Variable
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCRV.Unload();
            return;
        case 63: //tnam Topic
            if(XPRD.IsLoaded())
                XPRD->TNAM.Unload();
            return;
        case 64: //xrdo XRDO ,, Struct
            XRDO.Unload();
            return;
        case 65: //xrdo XRDO ,, Struct
            XRDO.Unload();
            return;
        case 66: //xrdo XRDO ,, Struct
            XRDO.Unload();
            return;
        case 67: //xrdo XRDO ,, Struct
            XRDO.Unload();
            return;
        case 68: //xown Owner
            if(XOWN.IsLoaded())
                XOWN->XOWN.Unload();
            return;
        case 69: //xrnk Faction rank
            if(XOWN.IsLoaded())
                XOWN->XRNK.Unload();
            return;
        case 70: //xloc XLOC ,, Struct
            XLOC.Unload();
            return;
        case 71: //xloc_p XLOC ,, Struct
            XLOC.Unload();
            return;
        case 72: //xloc XLOC ,, Struct
            XLOC.Unload();
            return;
        case 73: //xloc XLOC ,, Struct
            XLOC.Unload();
            return;
        case 74: //xloc_p XLOC ,, Struct
            XLOC.Unload();
            return;
        case 75: //xloc_p XLOC ,, Struct
            XLOC.Unload();
            return;
        case 76: //xcnt Count
            XCNT.Unload();
            return;
        case 77: //xrds Radius
            XRDS.Unload();
            return;
        case 78: //xhlp Health
            XHLP.Unload();
            return;
        case 79: //xrad Radiation
            XRAD.Unload();
            return;
        case 80: //xchg Charge
            XCHG.Unload();
            return;
        case 81: //xamt Type
            if(XAMT.IsLoaded())
                XAMT->XAMT.Unload();
            return;
        case 82: //xamc Count
            if(XAMT.IsLoaded())
                XAMT->XAMC.Unload();
            return;
        case 83: //xpwr XPWR ,, Struct
            XPWR.Unload();
            return;
        case 84: //xpwr XPWR ,, Struct
            XPWR.Unload();
            return;
        case 85: //xltw Water
            XLTW.Unload();
            return;
        case 86: //xdcr XDCR ,, Struct
            XDCR.Unload();
            return;
        case 87: //xdcr_p XDCR ,, Struct
            XDCR.Unload();
            return;
        case 88: //xlkr Linked Reference
            XLKR.Unload();
            return;
        case 89: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 90: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 91: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 92: //xclp_p XCLP ,, Struct
            XCLP.Unload();
            return;
        case 93: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 94: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 95: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 96: //xclp_p XCLP ,, Struct
            XCLP.Unload();
            return;
        case 97: //xapd Flags
            XAPD.Unload();
            return;
        case 98: //xapr XAPR ,, Struct
            XAPR.Unload();
            return;
        case 99: //xapr XAPR ,, Struct
            XAPR.Unload();
            return;
        case 100: //xato Activation Prompt
            XATO.Unload();
            return;
        case 101: //xesp Enable Parent
            XESP.Unload();
            return;
        case 102: //xesp Enable Parent
            XESP.Unload();
            return;
        case 103: //xesp_p Enable Parent
            XESP.Unload();
            return;
        case 104: //xemi Emittance
            XEMI.Unload();
            return;
        case 105: //xmbr MultiBound Reference
            XMBR.Unload();
            return;
        case 106: //xact Action Flag
            XACT.Unload();
            return;
        case 107: //xndp XNDP ,, Struct
            XNDP.Unload();
            return;
        case 108: //xndp XNDP ,, Struct
            XNDP.Unload();
            return;
        case 109: //xndp_p XNDP ,, Struct
            XNDP.Unload();
            return;
        case 110: //xpod Portal Data
            return UNPARSEDDEL_FIELD110;
        case 111: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 112: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 113: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 114: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 115: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 116: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 117: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 118: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 119: //xptl XPTL ,, Struct
            XPTL.Unload();
            return;
        case 120: //xsed SpeedTree Seed
            XSED.Unload();
            return;
        case 121: //xrmr XRMR ,, Struct
            XRMR.Unload();
            return;
        case 122: //xrmr_p XRMR ,, Struct
            XRMR.Unload();
            return;
        case 123: //xlrm Linked Room
            XLRM.Unload();
            return;
        case 124: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 125: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 126: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 127: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 128: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 129: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 130: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 131: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 132: //xocp XOCP ,, Struct
            XOCP.Unload();
            return;
        case 133: //xord Linked Occlusion Planes
            return UNPARSEDDEL_FIELD133;
        case 134: //xlod Distant LOD Data
            XLOD.Unload();
            return;
        case 135: //xlod Distant LOD Data
            XLOD.Unload();
            return;
        case 136: //xlod Distant LOD Data
            XLOD.Unload();
            return;
        case 137: //xscl Scale
            XSCL.Unload();
            return;
        case 138: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 139: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 140: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 141: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 142: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 143: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        default:
            return;
        }
    }
}