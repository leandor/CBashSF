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
#include "..\PMISRecord.h"

namespace FNV
{
UINT32 PMISRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //name Base
            return FORMID_FIELD;
        case 8: //xezn Encounter Zone
            return FORMID_FIELD;
        case 9: //xrgd_p Ragdoll Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGD.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //xrgb_p Ragdoll Biped Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 11: //xprd Idle Time
            return FLOAT32_FIELD;
        case 12: //inam Idle
            return FORMID_FIELD;
        case 13: //schr_p Basic Script Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 14: //schr Basic Script Data
            return UINT32_FIELD;
        case 15: //schr Basic Script Data
            return UINT32_FIELD;
        case 16: //schr Basic Script Data
            return UINT32_FIELD;
        case 17: //schr Basic Script Data
            return UINT16_FIELD;
        case 18: //schr Basic Script Data
            return UINT16_FIELD;
        case 19: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 20: //sctx Embedded Script Source
            return ISTRING_FIELD;
        case 21: //slsd Local Variable Data
            return UINT32_FIELD;
        case 22: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return UNKNOWN_FIELD;
                }
        case 23: //slsd Local Variable Data
            return UINT8_FIELD;
        case 24: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return UNKNOWN_FIELD;
                }
        case 25: //scvr Name
            return ISTRING_FIELD;
        case 26: //scro Global Reference
            return FORMID_FIELD;
        case 27: //scrv Local Variable
            return UINT32_FIELD;
        case 28: //tnam Topic
            return FORMID_FIELD;
        case 29: //xown Owner
            return FORMID_FIELD;
        case 30: //xrnk Faction rank
            return SINT32_FIELD;
        case 31: //xcnt Count
            return SINT32_FIELD;
        case 32: //xrds Radius
            return FLOAT32_FIELD;
        case 33: //xhlp Health
            return FLOAT32_FIELD;
        case 34: //xpwr XPWR ,, Struct
            return FORMID_FIELD;
        case 35: //xpwr XPWR ,, Struct
            return UINT32_FIELD;
        case 36: //xdcr XDCR ,, Struct
            return FORMID_FIELD;
        case 37: //xdcr_p XDCR ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XDCR.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 38: //xlkr Linked Reference
            return FORMID_FIELD;
        case 39: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 40: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 41: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 42: //xclp_p XCLP ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 43: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 44: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 45: //xclp XCLP ,, Struct
            return UINT8_FIELD;
        case 46: //xclp_p XCLP ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 47: //xapd Flags
            return UINT8_FIELD;
        case 48: //xapr XAPR ,, Struct
            return FORMID_FIELD;
        case 49: //xapr XAPR ,, Struct
            return FLOAT32_FIELD;
        case 50: //xato Activation Prompt
            return ISTRING_FIELD;
        case 51: //xesp Enable Parent
            return FORMID_FIELD;
        case 52: //xesp Enable Parent
            return UINT8_FIELD;
        case 53: //xesp_p Enable Parent
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        case 54: //xemi Emittance
            return FORMID_FIELD;
        case 55: //xmbr MultiBound Reference
            return FORMID_FIELD;
        case 56: //xscl Scale
            return FLOAT32_FIELD;
        case 57: //data Position/Rotation
            return FLOAT32_FIELD;
        case 58: //data Position/Rotation
            return FLOAT32_FIELD;
        case 59: //data Position/Rotation
            return FLOAT32_FIELD;
        case 60: //data Position/Rotation
            return FLOAT32_FIELD;
        case 61: //data Position/Rotation
            return FLOAT32_FIELD;
        case 62: //data Position/Rotation
            return FLOAT32_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * PMISRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //name Base
            return NAME.IsLoaded() ? &NAME->value7 : NULL;
        case 8: //xezn Encounter Zone
            return XEZN.IsLoaded() ? &XEZN->value8 : NULL;
        case 9: //xrgd_p Ragdoll Data
            *FieldValues = XRGD.value;
            return NULL;
        case 10: //xrgb_p Ragdoll Biped Data
            *FieldValues = XRGB.value;
            return NULL;
        case 11: //xprd Idle Time
            return XPRD.IsLoaded() ? &XPRD->XPRD->value11 : NULL;
        case 12: //inam Idle
            return XPRD.IsLoaded() ? &XPRD->INAM->value12 : NULL;
        case 13: //schr_p Basic Script Data
            *FieldValues = (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value13[0] : NULL;
            return NULL;
        case 14: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value14 : NULL;
        case 15: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value15 : NULL;
        case 16: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value16 : NULL;
        case 17: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value17 : NULL;
        case 18: //schr Basic Script Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCHR->value18 : NULL;
        case 19: //scda_p Compiled Embedded Script
            *FieldValues = (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? XPRD->SCHR->SCDA.value : NULL;
            return NULL;
        case 20: //sctx Embedded Script Source
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? XPRD->SCHR->SCTX.value : NULL;
        case 21: //slsd Local Variable Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SLSD->value21 : NULL;
        case 22: //slsd_p Local Variable Data
            *FieldValues = (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SLSD->value22[0] : NULL;
            return NULL;
        case 23: //slsd Local Variable Data
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SLSD->value23 : NULL;
        case 24: //slsd_p Local Variable Data
            *FieldValues = (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SLSD->value24[0] : NULL;
            return NULL;
        case 25: //scvr Name
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? XPRD->SCHR->SCVR.value : NULL;
        case 26: //scro Global Reference
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCRO->value26 : NULL;
        case 27: //scrv Local Variable
            return (XPRD.IsLoaded() && XPRD->SCHR.IsLoaded()) ? &XPRD->SCHR->SCRV->value27 : NULL;
        case 28: //tnam Topic
            return XPRD.IsLoaded() ? &XPRD->TNAM->value28 : NULL;
        case 29: //xown Owner
            return XOWN.IsLoaded() ? &XOWN->XOWN->value29 : NULL;
        case 30: //xrnk Faction rank
            return XOWN.IsLoaded() ? &XOWN->XRNK->value30 : NULL;
        case 31: //xcnt Count
            return XCNT.IsLoaded() ? &XCNT->value31 : NULL;
        case 32: //xrds Radius
            return XRDS.IsLoaded() ? &XRDS->value32 : NULL;
        case 33: //xhlp Health
            return XHLP.IsLoaded() ? &XHLP->value33 : NULL;
        case 34: //xpwr XPWR ,, Struct
            return XPWR.IsLoaded() ? &XPWR->value34 : NULL;
        case 35: //xpwr XPWR ,, Struct
            return XPWR.IsLoaded() ? &XPWR->value35 : NULL;
        case 36: //xdcr XDCR ,, Struct
            return XDCR.IsLoaded() ? &XDCR->value36 : NULL;
        case 37: //xdcr_p XDCR ,, Struct
            *FieldValues = XDCR.value;
            return NULL;
        case 38: //xlkr Linked Reference
            return XLKR.IsLoaded() ? &XLKR->value38 : NULL;
        case 39: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value39 : NULL;
        case 40: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value40 : NULL;
        case 41: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value41 : NULL;
        case 42: //xclp_p XCLP ,, Struct
            *FieldValues = XCLP.IsLoaded() ? &XCLP->value42[0] : NULL;
            return NULL;
        case 43: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value43 : NULL;
        case 44: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value44 : NULL;
        case 45: //xclp XCLP ,, Struct
            return XCLP.IsLoaded() ? &XCLP->value45 : NULL;
        case 46: //xclp_p XCLP ,, Struct
            *FieldValues = XCLP.IsLoaded() ? &XCLP->value46[0] : NULL;
            return NULL;
        case 47: //xapd Flags
            return XAPD.IsLoaded() ? &XAPD->value47 : NULL;
        case 48: //xapr XAPR ,, Struct
            return XAPR.IsLoaded() ? &XAPR->value48 : NULL;
        case 49: //xapr XAPR ,, Struct
            return XAPR.IsLoaded() ? &XAPR->value49 : NULL;
        case 50: //xato Activation Prompt
            return XATO.value;
        case 51: //xesp Enable Parent
            return XESP.IsLoaded() ? &XESP->value51 : NULL;
        case 52: //xesp Enable Parent
            return XESP.IsLoaded() ? &XESP->value52 : NULL;
        case 53: //xesp_p Enable Parent
            *FieldValues = XESP.IsLoaded() ? &XESP->value53[0] : NULL;
            return NULL;
        case 54: //xemi Emittance
            return XEMI.IsLoaded() ? &XEMI->value54 : NULL;
        case 55: //xmbr MultiBound Reference
            return XMBR.IsLoaded() ? &XMBR->value55 : NULL;
        case 56: //xscl Scale
            return XSCL.IsLoaded() ? &XSCL->value56 : NULL;
        case 57: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value57 : NULL;
        case 58: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value58 : NULL;
        case 59: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value59 : NULL;
        case 60: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value60 : NULL;
        case 61: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value61 : NULL;
        case 62: //data Position/Rotation
            return DATAPosRot.IsLoaded() ? &DATAPosRot->value62 : NULL;
        default:
            return NULL;
        }
    }

bool PMISRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //name Base
            NAME.Load();
            NAME->value7 = *(FORMID *)FieldValue;
            return true;
        case 8: //xezn Encounter Zone
            XEZN.Load();
            XEZN->value8 = *(FORMID *)FieldValue;
            return true;
        case 9: //xrgd_p Ragdoll Data
            XRGD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //xrgb_p Ragdoll Biped Data
            XRGB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //xprd Idle Time
            XPRD.Load();
            XPRD->XPRD.Load();
            XPRD->XPRD->value11 = *(FLOAT32 *)FieldValue;
            break;
        case 12: //inam Idle
            XPRD.Load();
            XPRD->INAM.Load();
            XPRD->INAM->value12 = *(FORMID *)FieldValue;
            return true;
        case 13: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value13[0] = ((UINT8 *)FieldValue)[0];
            XPRD->SCHR->SCHR->value13[1] = ((UINT8 *)FieldValue)[1];
            XPRD->SCHR->SCHR->value13[2] = ((UINT8 *)FieldValue)[2];
            XPRD->SCHR->SCHR->value13[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 14: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value14 = *(UINT32 *)FieldValue;
            break;
        case 15: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value15 = *(UINT32 *)FieldValue;
            break;
        case 16: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value16 = *(UINT32 *)FieldValue;
            break;
        case 17: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value17 = *(UINT16 *)FieldValue;
            break;
        case 18: //schr Basic Script Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCHR.Load();
            XPRD->SCHR->SCHR->value18 = *(UINT16 *)FieldValue;
            break;
        case 19: //scda_p Compiled Embedded Script
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 20: //sctx Embedded Script Source
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCTX.Copy((STRING)FieldValue);
            break;
        case 21: //slsd Local Variable Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SLSD.Load();
            XPRD->SCHR->SLSD->value21 = *(UINT32 *)FieldValue;
            break;
        case 22: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SLSD.Load();
            XPRD->SCHR->SLSD->value22[0] = ((UINT8 *)FieldValue)[0];
            XPRD->SCHR->SLSD->value22[1] = ((UINT8 *)FieldValue)[1];
            XPRD->SCHR->SLSD->value22[2] = ((UINT8 *)FieldValue)[2];
            XPRD->SCHR->SLSD->value22[3] = ((UINT8 *)FieldValue)[3];
            XPRD->SCHR->SLSD->value22[4] = ((UINT8 *)FieldValue)[4];
            XPRD->SCHR->SLSD->value22[5] = ((UINT8 *)FieldValue)[5];
            XPRD->SCHR->SLSD->value22[6] = ((UINT8 *)FieldValue)[6];
            XPRD->SCHR->SLSD->value22[7] = ((UINT8 *)FieldValue)[7];
            XPRD->SCHR->SLSD->value22[8] = ((UINT8 *)FieldValue)[8];
            XPRD->SCHR->SLSD->value22[9] = ((UINT8 *)FieldValue)[9];
            XPRD->SCHR->SLSD->value22[10] = ((UINT8 *)FieldValue)[10];
            XPRD->SCHR->SLSD->value22[11] = ((UINT8 *)FieldValue)[11];
            break;
        case 23: //slsd Local Variable Data
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SLSD.Load();
            XPRD->SCHR->SLSD->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SLSD.Load();
            XPRD->SCHR->SLSD->value24[0] = ((UINT8 *)FieldValue)[0];
            XPRD->SCHR->SLSD->value24[1] = ((UINT8 *)FieldValue)[1];
            XPRD->SCHR->SLSD->value24[2] = ((UINT8 *)FieldValue)[2];
            XPRD->SCHR->SLSD->value24[3] = ((UINT8 *)FieldValue)[3];
            XPRD->SCHR->SLSD->value24[4] = ((UINT8 *)FieldValue)[4];
            XPRD->SCHR->SLSD->value24[5] = ((UINT8 *)FieldValue)[5];
            XPRD->SCHR->SLSD->value24[6] = ((UINT8 *)FieldValue)[6];
            break;
        case 25: //scvr Name
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCVR.Copy((STRING)FieldValue);
            break;
        case 26: //scro Global Reference
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCRO.Load();
            XPRD->SCHR->SCRO->value26 = *(FORMID *)FieldValue;
            return true;
        case 27: //scrv Local Variable
            XPRD.Load();
            XPRD->SCHR.Load();
            XPRD->SCHR->SCRV.Load();
            XPRD->SCHR->SCRV->value27 = *(UINT32 *)FieldValue;
            break;
        case 28: //tnam Topic
            XPRD.Load();
            XPRD->TNAM.Load();
            XPRD->TNAM->value28 = *(FORMID *)FieldValue;
            return true;
        case 29: //xown Owner
            XOWN.Load();
            XOWN->XOWN.Load();
            XOWN->XOWN->value29 = *(FORMID *)FieldValue;
            return true;
        case 30: //xrnk Faction rank
            XOWN.Load();
            XOWN->XRNK.Load();
            XOWN->XRNK->value30 = *(SINT32 *)FieldValue;
            break;
        case 31: //xcnt Count
            XCNT.Load();
            XCNT->value31 = *(SINT32 *)FieldValue;
            break;
        case 32: //xrds Radius
            XRDS.Load();
            XRDS->value32 = *(FLOAT32 *)FieldValue;
            break;
        case 33: //xhlp Health
            XHLP.Load();
            XHLP->value33 = *(FLOAT32 *)FieldValue;
            break;
        case 34: //xpwr XPWR ,, Struct
            XPWR.Load();
            XPWR->value34 = *(FORMID *)FieldValue;
            return true;
        case 35: //xpwr XPWR ,, Struct
            XPWR.Load();
            XPWR->value35 = *(UINT32 *)FieldValue;
            break;
        case 36: //xdcr XDCR ,, Struct
            XDCR.Load();
            XDCR->value36 = *(FORMID *)FieldValue;
            return true;
        case 37: //xdcr_p XDCR ,, Struct
            XDCR.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 38: //xlkr Linked Reference
            XLKR.Load();
            XLKR->value38 = *(FORMID *)FieldValue;
            return true;
        case 39: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value39 = *(UINT8 *)FieldValue;
            break;
        case 40: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value40 = *(UINT8 *)FieldValue;
            break;
        case 41: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value41 = *(UINT8 *)FieldValue;
            break;
        case 42: //xclp_p XCLP ,, Struct
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->value42[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 43: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value43 = *(UINT8 *)FieldValue;
            break;
        case 44: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value44 = *(UINT8 *)FieldValue;
            break;
        case 45: //xclp XCLP ,, Struct
            XCLP.Load();
            XCLP->value45 = *(UINT8 *)FieldValue;
            break;
        case 46: //xclp_p XCLP ,, Struct
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->value46[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 47: //xapd Flags
            XAPD.Load();
            XAPD->value47 = *(UINT8 *)FieldValue;
            break;
        case 48: //xapr XAPR ,, Struct
            XAPR.Load();
            XAPR->value48 = *(FORMID *)FieldValue;
            return true;
        case 49: //xapr XAPR ,, Struct
            XAPR.Load();
            XAPR->value49 = *(FLOAT32 *)FieldValue;
            break;
        case 50: //xato Activation Prompt
            XATO.Copy((STRING)FieldValue);
            break;
        case 51: //xesp Enable Parent
            XESP.Load();
            XESP->value51 = *(FORMID *)FieldValue;
            return true;
        case 52: //xesp Enable Parent
            XESP.Load();
            XESP->value52 = *(UINT8 *)FieldValue;
            break;
        case 53: //xesp_p Enable Parent
            if(ArraySize != 3)
                break;
            XESP.Load();
            XESP->value53[0] = ((UINT8 *)FieldValue)[0];
            XESP->value53[1] = ((UINT8 *)FieldValue)[1];
            XESP->value53[2] = ((UINT8 *)FieldValue)[2];
            break;
        case 54: //xemi Emittance
            XEMI.Load();
            XEMI->value54 = *(FORMID *)FieldValue;
            return true;
        case 55: //xmbr MultiBound Reference
            XMBR.Load();
            XMBR->value55 = *(FORMID *)FieldValue;
            return true;
        case 56: //xscl Scale
            XSCL.Load();
            XSCL->value56 = *(FLOAT32 *)FieldValue;
            break;
        case 57: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value57 = *(FLOAT32 *)FieldValue;
            break;
        case 58: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value58 = *(FLOAT32 *)FieldValue;
            break;
        case 59: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value59 = *(FLOAT32 *)FieldValue;
            break;
        case 60: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value60 = *(FLOAT32 *)FieldValue;
            break;
        case 61: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value61 = *(FLOAT32 *)FieldValue;
            break;
        case 62: //data Position/Rotation
            DATAPosRot.Load();
            DATAPosRot->value62 = *(FLOAT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void PMISRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //name Base
            NAME.Unload();
            return;
        case 8: //xezn Encounter Zone
            XEZN.Unload();
            return;
        case 9: //xrgd_p Ragdoll Data
            XRGD.Unload();
            return;
        case 10: //xrgb_p Ragdoll Biped Data
            XRGB.Unload();
            return;
        case 11: //xprd Idle Time
            if(XPRD.IsLoaded())
                XPRD->XPRD.Unload();
            return;
        case 12: //inam Idle
            if(XPRD.IsLoaded())
                XPRD->INAM.Unload();
            return;
        case 13: //schr_p Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 14: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 15: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 16: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 17: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 18: //schr Basic Script Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCHR.Unload();
            return;
        case 19: //scda_p Compiled Embedded Script
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCDA.Unload();
            return;
        case 20: //sctx Embedded Script Source
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCTX.Unload();
            return;
        case 21: //slsd Local Variable Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SLSD.Unload();
            return;
        case 22: //slsd_p Local Variable Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SLSD.Unload();
            return;
        case 23: //slsd Local Variable Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SLSD.Unload();
            return;
        case 24: //slsd_p Local Variable Data
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SLSD.Unload();
            return;
        case 25: //scvr Name
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCVR.Unload();
            return;
        case 26: //scro Global Reference
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCRO.Unload();
            return;
        case 27: //scrv Local Variable
            if(XPRD.IsLoaded() && XPRD->SCHR.IsLoaded())
                XPRD->SCHR->SCRV.Unload();
            return;
        case 28: //tnam Topic
            if(XPRD.IsLoaded())
                XPRD->TNAM.Unload();
            return;
        case 29: //xown Owner
            if(XOWN.IsLoaded())
                XOWN->XOWN.Unload();
            return;
        case 30: //xrnk Faction rank
            if(XOWN.IsLoaded())
                XOWN->XRNK.Unload();
            return;
        case 31: //xcnt Count
            XCNT.Unload();
            return;
        case 32: //xrds Radius
            XRDS.Unload();
            return;
        case 33: //xhlp Health
            XHLP.Unload();
            return;
        case 34: //xpwr XPWR ,, Struct
            XPWR.Unload();
            return;
        case 35: //xpwr XPWR ,, Struct
            XPWR.Unload();
            return;
        case 36: //xdcr XDCR ,, Struct
            XDCR.Unload();
            return;
        case 37: //xdcr_p XDCR ,, Struct
            XDCR.Unload();
            return;
        case 38: //xlkr Linked Reference
            XLKR.Unload();
            return;
        case 39: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 40: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 41: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 42: //xclp_p XCLP ,, Struct
            XCLP.Unload();
            return;
        case 43: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 44: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 45: //xclp XCLP ,, Struct
            XCLP.Unload();
            return;
        case 46: //xclp_p XCLP ,, Struct
            XCLP.Unload();
            return;
        case 47: //xapd Flags
            XAPD.Unload();
            return;
        case 48: //xapr XAPR ,, Struct
            XAPR.Unload();
            return;
        case 49: //xapr XAPR ,, Struct
            XAPR.Unload();
            return;
        case 50: //xato Activation Prompt
            XATO.Unload();
            return;
        case 51: //xesp Enable Parent
            XESP.Unload();
            return;
        case 52: //xesp Enable Parent
            XESP.Unload();
            return;
        case 53: //xesp_p Enable Parent
            XESP.Unload();
            return;
        case 54: //xemi Emittance
            XEMI.Unload();
            return;
        case 55: //xmbr MultiBound Reference
            XMBR.Unload();
            return;
        case 56: //xscl Scale
            XSCL.Unload();
            return;
        case 57: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 58: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 59: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 60: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 61: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        case 62: //data Position/Rotation
            DATAPosRot.Unload();
            return;
        default:
            return;
        }
    }
}