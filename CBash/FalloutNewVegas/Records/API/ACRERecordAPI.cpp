/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "..\..\..\Common.h"
#include "..\ACRERecord.h"

namespace FNV
{
UINT32 ACRERecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //base
            return FORMID_FIELD;
        case 8: //encounterZone
            return FORMID_FIELD;
        case 9: //xrgd_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGD.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 10: //xrgb_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGB.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 11: //idleTime
            return FLOAT32_FIELD;
        case 12: //idle
            return FORMID_FIELD;
        case 13: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Patrol.IsLoaded() ? 4 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 14: //numRefs
            return UINT32_FIELD;
        case 15: //compiledSize
            return UINT32_FIELD;
        case 16: //lastIndex
            return UINT32_FIELD;
        case 17: //scriptType
            return UINT16_TYPE_FIELD;
        case 18: //scriptFlags
            return UINT16_FLAG_FIELD;
        case 19: //compiled_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Patrol.IsLoaded() ? Patrol->SCDA.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 20: //scriptText
            return ISTRING_FIELD;
        case 21: //vars
            if(!Patrol.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //vars
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)Patrol->VARS.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //index
                    return UINT32_FIELD;
                case 2: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 12;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                case 3: //flags
                    return UINT8_FLAG_FIELD;
                case 4: //unused2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 7;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                case 5: //name
                    return ISTRING_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 22: //references
            if(!Patrol.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //references
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return FORMID_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (UINT32)Patrol->SCR_.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return Patrol->SCR_.value[ListIndex]->isSCRO ? FORMID_FIELD : UINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 23: //topic
            return FORMID_FIELD;
        case 24: //levelMod
            return SINT32_FIELD;
        case 25: //owner
            return FORMID_FIELD;
        case 26: //rank
            return SINT32_FIELD;
        case 27: //merchantContainer
            return FORMID_FIELD;
        case 28: //count
            return SINT32_FIELD;
        case 29: //radius
            return FLOAT32_FIELD;
        case 30: //health
            return FLOAT32_FIELD;
        case 31: //decals
            if(ListFieldID == 0) //decals
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)XDCR.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= XDCR.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    return FORMID_FIELD;
                case 2: //unknown1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 24;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 32: //linkedReference
            return FORMID_FIELD;
        case 33: //startRed
            return UINT8_FIELD;
        case 34: //startGreen
            return UINT8_FIELD;
        case 35: //startBlue
            return UINT8_FIELD;
        case 36: //unused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLP.IsLoaded() ? 1 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 37: //endRed
            return UINT8_FIELD;
        case 38: //endGreen
            return UINT8_FIELD;
        case 39: //endBlue
            return UINT8_FIELD;
        case 40: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLP.IsLoaded() ? 1 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 41: //activateParentFlags
            return UINT8_FLAG_FIELD;
        case 42: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //activateParentRefs
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)ActivateParents->XAPR.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    return FORMID_FIELD;
                case 2: //delay
                    return FLOAT32_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 43: //prompt
            return STRING_FIELD;
        case 44: //parent
            return FORMID_FIELD;
        case 45: //parentFlags
            return UINT8_FLAG_FIELD;
        case 46: //unused4
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XESP.IsLoaded() ? 3 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 47: //emittance
            return FORMID_FIELD;
        case 48: //boundRef
            return FORMID_FIELD;
        case 49: //ignoredBySandbox
            return BOOL_FIELD;
        case 50: //scale
            return FLOAT32_FIELD;
        case 51: //posX
            return FLOAT32_FIELD;
        case 52: //posY
            return FLOAT32_FIELD;
        case 53: //posZ
            return FLOAT32_FIELD;
        case 54: //rotX
            return RADIAN_FIELD;
        case 55: //rotY
            return RADIAN_FIELD;
        case 56: //rotZ
            return RADIAN_FIELD;
        case 57: //Parent
            return PARENTRECORD_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * ACRERecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //base
            return &NAME.value;
        case 8: //encounterZone
            return &XEZN.value;
        case 9: //xrgd_p
            *FieldValues = XRGD.value;
            return NULL;
        case 10: //xrgb_p
            *FieldValues = XRGB.value;
            return NULL;
        case 11: //idleTime
            return Patrol.IsLoaded() ? &Patrol->XPRD.value : NULL;
        case 12: //idle
            return Patrol.IsLoaded() ? &Patrol->INAM.value : NULL;
        case 13: //unused1
            *FieldValues = Patrol.IsLoaded() ? &Patrol->SCHR.value.unused1[0] : NULL;
            return NULL;
        case 14: //numRefs
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.numRefs : NULL;
        case 15: //compiledSize
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.compiledSize : NULL;
        case 16: //lastIndex
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.lastIndex : NULL;
        case 17: //scriptType
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.scriptType : NULL;
        case 18: //scriptFlags
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.flags : NULL;
        case 19: //compiled_p
            *FieldValues = Patrol.IsLoaded() ? Patrol->SCDA.value : NULL;
            return NULL;
        case 20: //scriptText
            return Patrol.IsLoaded() ? Patrol->SCTX.value : NULL;
        case 21: //vars
            if(!Patrol.IsLoaded())
                return NULL;

            if(ListIndex >= Patrol->VARS.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //index
                    return &Patrol->VARS.value[ListIndex]->SLSD.value.index;
                case 2: //unused1
                    *FieldValues = &Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0];
                    return NULL;
                case 3: //flags
                    return &Patrol->VARS.value[ListIndex]->SLSD.value.flags;
                case 4: //unused2
                    *FieldValues = &Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0];
                    return NULL;
                case 5: //name
                    return Patrol->VARS.value[ListIndex]->SCVR.value;
                default:
                    return NULL;
                }
            return NULL;
        case 22: //references
            if(!Patrol.IsLoaded())
                {
                *FieldValues = NULL;
                return NULL;
                }
            for(UINT32 x = 0; x < Patrol->SCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = Patrol->SCR_.value[x]->reference;
            return NULL;
        case 23: //topic
            return Patrol.IsLoaded() ? &Patrol->TNAM.value : NULL;
        case 24: //levelMod
            return &XLCM.value;
        case 25: //owner
            return Ownership.IsLoaded() ? &Ownership->XOWN.value : NULL;
        case 26: //rank
            return Ownership.IsLoaded() ? Ownership->XRNK.value : NULL;
        case 27: //merchantContainer
            return &XMRC.value;
        case 28: //count
            return &XCNT.value;
        case 29: //radius
            return &XRDS.value;
        case 30: //health
            return &XHLP.value;
        case 31: //decals
            if(ListIndex >= XDCR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //reference
                    return &XDCR.value[ListIndex]->reference;
                case 2: //unknown1
                    *FieldValues = &XDCR.value[ListIndex]->unknown1[0];
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 32: //linkedReference
            return &XLKR.value;
        case 33: //startRed
            return XCLP.IsLoaded() ? &XCLP->start.red : NULL;
        case 34: //startGreen
            return XCLP.IsLoaded() ? &XCLP->start.green : NULL;
        case 35: //startBlue
            return XCLP.IsLoaded() ? &XCLP->start.blue : NULL;
        case 36: //unused2
            *FieldValues = XCLP.IsLoaded() ? &XCLP->start.unused1 : NULL;
            return NULL;
        case 37: //endRed
            return XCLP.IsLoaded() ? &XCLP->end.red : NULL;
        case 38: //endGreen
            return XCLP.IsLoaded() ? &XCLP->end.green : NULL;
        case 39: //endBlue
            return XCLP.IsLoaded() ? &XCLP->end.blue : NULL;
        case 40: //unused3
            *FieldValues = XCLP.IsLoaded() ? &XCLP->end.unused1 : NULL;
            return NULL;
        case 41: //activateParentFlags
            return ActivateParents.IsLoaded() ? &ActivateParents->XAPD.value : NULL;
        case 42: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return NULL;

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //reference
                    return &ActivateParents->XAPR.value[ListIndex]->reference;
                case 2: //delay
                    return &ActivateParents->XAPR.value[ListIndex]->delay;
                default:
                    return NULL;
                }
            return NULL;
        case 43: //prompt
            return XATO.value;
        case 44: //parent
            return XESP.IsLoaded() ? &XESP->parent : NULL;
        case 45: //parentFlags
            return XESP.IsLoaded() ? &XESP->flags : NULL;
        case 46: //unused4
            *FieldValues = XESP.IsLoaded() ? &XESP->unused1[0] : NULL;
            return NULL;
        case 47: //emittance
            return &XEMI.value;
        case 48: //boundRef
            return &XMBR.value;
        case 49: //ignoredBySandbox
            return &XIBS.value;
        case 50: //scale
            return &XSCL.value;
        case 51: //posX
            return &DATA.value.posX;
        case 52: //posY
            return &DATA.value.posY;
        case 53: //posZ
            return &DATA.value.posZ;
        case 54: //rotX
            return &DATA.value.rotX;
        case 55: //rotY
            return &DATA.value.rotY;
        case 56: //rotZ
            return &DATA.value.rotZ;
        case 57: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool ACRERecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //base
            NAME.value = *(FORMID *)FieldValue;
            return true;
        case 8: //encounterZone
            XEZN.value = *(FORMID *)FieldValue;
            return true;
        case 9: //xrgd_p
            XRGD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //xrgp_p
            XRGB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //idleTime
            Patrol.Load();
            Patrol->XPRD.value = *(FLOAT32 *)FieldValue;
            break;
        case 12: //idle
            Patrol.Load();
            Patrol->INAM.value = *(FORMID *)FieldValue;
            return true;
        case 13: //unused1
            if(ArraySize != 4)
                break;
            Patrol.Load();
            Patrol->SCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Patrol->SCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            Patrol->SCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            Patrol->SCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 14: //numRefs
            Patrol.Load();
            Patrol->SCHR.value.numRefs = *(UINT32 *)FieldValue;
            break;
        case 15: //compiledSize
            Patrol.Load();
            Patrol->SCHR.value.compiledSize = *(UINT32 *)FieldValue;
            break;
        case 16: //lastIndex
            Patrol.Load();
            Patrol->SCHR.value.lastIndex = *(UINT32 *)FieldValue;
            break;
        case 17: //scriptType
            Patrol.Load();
            Patrol->SetType(*(UINT16 *)FieldValue);
            break;
        case 18: //scriptFlags
            Patrol.Load();
            Patrol->SetScriptFlagMask(*(UINT16 *)FieldValue);
            break;
        case 19: //compiled_p
            Patrol.Load();
            Patrol->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            Patrol->SCHR.value.compiledSize = ArraySize;
            break;
        case 20: //scriptText
            Patrol.Load();
            Patrol->SCTX.Copy((STRING)FieldValue);
            break;
        case 21: //VARS
            Patrol.Load();
            if(ListFieldID == 0) //VARSSize
                {
                Patrol->VARS.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //index
                    Patrol->VARS.value[ListIndex]->SLSD.value.index = *(UINT32 *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 12)
                        break;
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                    break;
                case 3: //flags
                    Patrol->VARS.value[ListIndex]->SetFlagMask(*(UINT8 *)FieldValue);
                    break;
                case 4: //unused2
                    if(ArraySize != 7)
                        break;
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                    break;
                case 5: //name
                    Patrol->VARS.value[ListIndex]->SCVR.Copy((STRING)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 22: //references
            Patrol.Load();
            if(ListFieldID == 0) //referencesSize
                {
                Patrol->SCR_.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    //Borrowing ArraySize to flag if the new value is a formID
                    Patrol->SCR_.value[ListIndex]->reference = *(UINT32 *)FieldValue;
                    Patrol->SCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;
                    return ArraySize != 0;
                default:
                    break;
                }
            break;
        case 23: //topic
            Patrol.Load();
            Patrol->TNAM.value = *(FORMID *)FieldValue;
            return true;
        case 24: //levelMod
            XLCM.value = *(SINT32 *)FieldValue;
            break;
        case 25: //owner
            Ownership.Load();
            Ownership->XOWN.value = *(FORMID *)FieldValue;
            return true;
        case 26: //rank
            Ownership.Load();
            *Ownership->XRNK.value = *(SINT32 *)FieldValue;
            break;
        case 27: //merchantContainer
            XMRC.value = *(FORMID *)FieldValue;
            return true;
        case 28: //count
            XCNT.value = *(SINT32 *)FieldValue;
            break;
        case 29: //radius
            XRDS.value = *(FLOAT32 *)FieldValue;
            break;
        case 30: //health
            XHLP.value = *(FLOAT32 *)FieldValue;
            break;
        case 31: //decals
            if(ListFieldID == 0) //decalsSize
                {
                XDCR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= XDCR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    XDCR.value[ListIndex]->reference = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown1
                    if(ArraySize != 24)
                        break;
                    XDCR.value[ListIndex]->unknown1[0] = ((UINT8ARRAY)FieldValue)[0];
                    XDCR.value[ListIndex]->unknown1[1] = ((UINT8ARRAY)FieldValue)[1];
                    XDCR.value[ListIndex]->unknown1[2] = ((UINT8ARRAY)FieldValue)[2];
                    XDCR.value[ListIndex]->unknown1[3] = ((UINT8ARRAY)FieldValue)[3];
                    XDCR.value[ListIndex]->unknown1[4] = ((UINT8ARRAY)FieldValue)[4];
                    XDCR.value[ListIndex]->unknown1[5] = ((UINT8ARRAY)FieldValue)[5];
                    XDCR.value[ListIndex]->unknown1[6] = ((UINT8ARRAY)FieldValue)[6];
                    XDCR.value[ListIndex]->unknown1[7] = ((UINT8ARRAY)FieldValue)[7];
                    XDCR.value[ListIndex]->unknown1[8] = ((UINT8ARRAY)FieldValue)[8];
                    XDCR.value[ListIndex]->unknown1[9] = ((UINT8ARRAY)FieldValue)[9];
                    XDCR.value[ListIndex]->unknown1[10] = ((UINT8ARRAY)FieldValue)[10];
                    XDCR.value[ListIndex]->unknown1[11] = ((UINT8ARRAY)FieldValue)[11];
                    XDCR.value[ListIndex]->unknown1[12] = ((UINT8ARRAY)FieldValue)[12];
                    XDCR.value[ListIndex]->unknown1[13] = ((UINT8ARRAY)FieldValue)[13];
                    XDCR.value[ListIndex]->unknown1[14] = ((UINT8ARRAY)FieldValue)[14];
                    XDCR.value[ListIndex]->unknown1[15] = ((UINT8ARRAY)FieldValue)[15];
                    XDCR.value[ListIndex]->unknown1[16] = ((UINT8ARRAY)FieldValue)[16];
                    XDCR.value[ListIndex]->unknown1[17] = ((UINT8ARRAY)FieldValue)[17];
                    XDCR.value[ListIndex]->unknown1[18] = ((UINT8ARRAY)FieldValue)[18];
                    XDCR.value[ListIndex]->unknown1[19] = ((UINT8ARRAY)FieldValue)[19];
                    XDCR.value[ListIndex]->unknown1[20] = ((UINT8ARRAY)FieldValue)[20];
                    XDCR.value[ListIndex]->unknown1[21] = ((UINT8ARRAY)FieldValue)[21];
                    XDCR.value[ListIndex]->unknown1[22] = ((UINT8ARRAY)FieldValue)[22];
                    XDCR.value[ListIndex]->unknown1[23] = ((UINT8ARRAY)FieldValue)[23];
                    break;
                default:
                    break;
                }
            break;
        case 32: //linkedReference
            XLKR.value = *(FORMID *)FieldValue;
            return true;
        case 33: //startRed
            XCLP.Load();
            XCLP->start.red = *(UINT8 *)FieldValue;
            break;
        case 34: //startGreen
            XCLP.Load();
            XCLP->start.green = *(UINT8 *)FieldValue;
            break;
        case 35: //startBlue
            XCLP.Load();
            XCLP->start.blue = *(UINT8 *)FieldValue;
            break;
        case 36: //unused2
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->start.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 37: //endRed
            XCLP.Load();
            XCLP->end.red = *(UINT8 *)FieldValue;
            break;
        case 38: //endGreen
            XCLP.Load();
            XCLP->end.green = *(UINT8 *)FieldValue;
            break;
        case 39: //endBlue
            XCLP.Load();
            XCLP->end.blue = *(UINT8 *)FieldValue;
            break;
        case 40: //unused3
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->end.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 41: //activateParentFlags
            ActivateParents.Load();
            ActivateParents->SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 42: //activateParentRefs
            ActivateParents.Load();
            if(ListFieldID == 0) //decalsSize
                {
                ActivateParents->XAPR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    ActivateParents->XAPR.value[ListIndex]->reference = *(FORMID *)FieldValue;
                    return true;
                case 2: //delay
                    ActivateParents->XAPR.value[ListIndex]->delay = *(FLOAT32 *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 43: //prompt
            XATO.Copy((STRING)FieldValue);
            break;
        case 44: //parent
            XESP.Load();
            XESP->parent = *(FORMID *)FieldValue;
            return true;
        case 45: //parentFlags
            SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 46: //unused4
            if(ArraySize != 3)
                break;
            XESP.Load();
            XESP->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            XESP->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            XESP->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 47: //emittance
            XEMI.value = *(FORMID *)FieldValue;
            return true;
        case 48: //boundRef
            XMBR.value = *(FORMID *)FieldValue;
            return true;
        case 49: //ignoredBySandbox
            XIBS.value = *(UINT8 *)FieldValue;
            break;
        case 50: //scale
            XSCL.value = *(FLOAT32 *)FieldValue;
            break;
        case 51: //posX
            DATA.value.posX = *(FLOAT32 *)FieldValue;
            break;
        case 52: //posY
            DATA.value.posY = *(FLOAT32 *)FieldValue;
            break;
        case 53: //posZ
            DATA.value.posZ = *(FLOAT32 *)FieldValue;
            break;
        case 54: //rotX
            DATA.value.rotX = *(FLOAT32 *)FieldValue;
            break;
        case 55: //rotY
            DATA.value.rotY = *(FLOAT32 *)FieldValue;
            break;
        case 56: //rotZ
            DATA.value.rotZ = *(FLOAT32 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void ACRERecord::DeleteField(FIELD_IDENTIFIERS)
    {
    FNVSCHR defaultSCHR;

    GENVARS defaultVARS;
    GENSCR_ defaultSCR_;
    GENCLR defaultCLR;
    GENXDCR defaultXDCR;
    GENXAPR defaultXAPR;
    GENXESP defaultXESP;
    GENPOSDATA defaultDATA;
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
        case 7: //base
            NAME.Unload();
            return;
        case 8: //encounterZone
            XEZN.Unload();
            return;
        case 9: //xrgd_p
            XRGD.Unload();
            return;
        case 10: //xrgp_p
            XRGB.Unload();
            return;
        case 11: //idleTime
            if(Patrol.IsLoaded())
                Patrol->XPRD.Unload();
            return;
        case 12: //idle
            if(Patrol.IsLoaded())
                Patrol->INAM.Unload();
            return;
        case 13: //unused1
            if(Patrol.IsLoaded())
                {
                Patrol->SCHR.value.unused1[0] = defaultSCHR.unused1[0];
                Patrol->SCHR.value.unused1[1] = defaultSCHR.unused1[1];
                Patrol->SCHR.value.unused1[2] = defaultSCHR.unused1[2];
                Patrol->SCHR.value.unused1[3] = defaultSCHR.unused1[3];
                }
            return;
        case 14: //numRefs
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 15: //compiledSize
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 16: //lastIndex
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 17: //scriptType
            if(Patrol.IsLoaded())
                Patrol->SetType(defaultSCHR.scriptType);
            return;
        case 18: //scriptFlags
            if(Patrol.IsLoaded())
                Patrol->SetScriptFlagMask(defaultSCHR.flags);
            return;
        case 19: //compiled_p
            if(Patrol.IsLoaded())
                Patrol->SCDA.Unload();
            return;
        case 20: //scriptText
            if(Patrol.IsLoaded())
                Patrol->SCTX.Unload();
            return;
        case 21: //VARS
            if(!Patrol.IsLoaded())
                return;

            if(ListFieldID == 0) //varsSize
                {
                Patrol->VARS.Unload();
                return;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //index
                    Patrol->VARS.value[ListIndex]->SLSD.value.index = defaultVARS.SLSD.value.index;
                    return;
                case 2: //unused1
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                    return;
                case 3: //flags
                    Patrol->VARS.value[ListIndex]->SetFlagMask(defaultVARS.SLSD.value.flags);
                    return;
                case 4: //unused2
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                    return;
                case 5: //name
                    Patrol->VARS.value[ListIndex]->SCVR.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 22: //references
            if(!Patrol.IsLoaded())
                return;

            if(ListFieldID == 0) //references
                {
                Patrol->SCR_.Unload();
                return;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    Patrol->SCR_.value[ListIndex]->reference = defaultSCR_.reference;
                    Patrol->SCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;
                    return;
                default:
                    return;
                }
            return;
        case 23: //topic
            if(Patrol.IsLoaded())
                Patrol->TNAM.Unload();
            return;
        case 24: //levelMod
            XLCM.Unload();
            return;
        case 25: //owner
            if(Ownership.IsLoaded())
                Ownership->XOWN.Unload();
            return;
        case 26: //rank
            if(Ownership.IsLoaded())
                Ownership->XRNK.Unload();
            return;
        case 27: //merchantContainer
            XMRC.Unload();
            return;
        case 28: //count
            XCNT.Unload();
            return;
        case 29: //radius
            XRDS.Unload();
            return;
        case 30: //health
            XHLP.Unload();
            return;
        case 31: //decals
            if(ListFieldID == 0) //decalsSize
                {
                XDCR.Unload();
                return;
                }

            if(ListIndex >= XDCR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    XDCR.value[ListIndex]->reference = defaultXDCR.reference;
                    return;
                case 2: //unknown1
                    XDCR.value[ListIndex]->unknown1[0] = defaultXDCR.unknown1[0];
                    XDCR.value[ListIndex]->unknown1[1] = defaultXDCR.unknown1[1];
                    XDCR.value[ListIndex]->unknown1[2] = defaultXDCR.unknown1[2];
                    XDCR.value[ListIndex]->unknown1[3] = defaultXDCR.unknown1[3];
                    XDCR.value[ListIndex]->unknown1[4] = defaultXDCR.unknown1[4];
                    XDCR.value[ListIndex]->unknown1[5] = defaultXDCR.unknown1[5];
                    XDCR.value[ListIndex]->unknown1[6] = defaultXDCR.unknown1[6];
                    XDCR.value[ListIndex]->unknown1[7] = defaultXDCR.unknown1[7];
                    XDCR.value[ListIndex]->unknown1[8] = defaultXDCR.unknown1[8];
                    XDCR.value[ListIndex]->unknown1[9] = defaultXDCR.unknown1[9];
                    XDCR.value[ListIndex]->unknown1[10] = defaultXDCR.unknown1[10];
                    XDCR.value[ListIndex]->unknown1[11] = defaultXDCR.unknown1[11];
                    XDCR.value[ListIndex]->unknown1[12] = defaultXDCR.unknown1[12];
                    XDCR.value[ListIndex]->unknown1[13] = defaultXDCR.unknown1[13];
                    XDCR.value[ListIndex]->unknown1[14] = defaultXDCR.unknown1[14];
                    XDCR.value[ListIndex]->unknown1[15] = defaultXDCR.unknown1[15];
                    XDCR.value[ListIndex]->unknown1[16] = defaultXDCR.unknown1[16];
                    XDCR.value[ListIndex]->unknown1[17] = defaultXDCR.unknown1[17];
                    XDCR.value[ListIndex]->unknown1[18] = defaultXDCR.unknown1[18];
                    XDCR.value[ListIndex]->unknown1[19] = defaultXDCR.unknown1[19];
                    XDCR.value[ListIndex]->unknown1[20] = defaultXDCR.unknown1[20];
                    XDCR.value[ListIndex]->unknown1[21] = defaultXDCR.unknown1[21];
                    XDCR.value[ListIndex]->unknown1[22] = defaultXDCR.unknown1[22];
                    XDCR.value[ListIndex]->unknown1[23] = defaultXDCR.unknown1[23];
                    return;
                default:
                    return;
                }
            return;
        case 32: //linkedReference
            XLKR.Unload();
            return;
        case 33: //startRed
            if(XCLP.IsLoaded())
                XCLP->start.red = defaultCLR.red;
            return;
        case 34: //startGreen
            if(XCLP.IsLoaded())
                XCLP->start.green = defaultCLR.green;
            return;
        case 35: //startBlue
            if(XCLP.IsLoaded())
                XCLP->start.blue = defaultCLR.blue;
            return;
        case 36: //unused2
            if(XCLP.IsLoaded())
                XCLP->start.unused1 = defaultCLR.unused1;
            return;
        case 37: //endRed
            if(XCLP.IsLoaded())
                XCLP->end.red = defaultCLR.red;
            return;
        case 38: //endGreen
            if(XCLP.IsLoaded())
                XCLP->end.green = defaultCLR.green;
            return;
        case 39: //endBlue
            if(XCLP.IsLoaded())
                XCLP->end.blue = defaultCLR.blue;
            return;
        case 40: //unused3
            if(XCLP.IsLoaded())
                XCLP->end.unused1 = defaultCLR.unused1;
            return;
        case 41: //activateParentFlags
            if(ActivateParents.IsLoaded())
                ActivateParents->XAPD.Unload();
            return;
        case 42: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return;

            if(ListFieldID == 0) //decalsSize
                {
                ActivateParents->XAPR.Unload();
                return;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    ActivateParents->XAPR.value[ListIndex]->reference = defaultXAPR.reference;
                    return;
                case 2: //delay
                    ActivateParents->XAPR.value[ListIndex]->delay = defaultXAPR.delay;
                    return;
                default:
                    return;
                }
            return;
        case 43: //prompt
            XATO.Unload();
            return;
        case 44: //parent
            if(XESP.IsLoaded())
                XESP->parent = defaultXESP.parent;
            return;
        case 45: //parentFlags
            if(XESP.IsLoaded())
                SetFlagMask(defaultXESP.flags);
            return;
        case 46: //unused4
            if(XESP.IsLoaded())
                {
                XESP->unused1[0] = defaultXESP.unused1[0];
                XESP->unused1[1] = defaultXESP.unused1[1];
                XESP->unused1[2] = defaultXESP.unused1[2];
                }
            return;
        case 47: //emittance
            XEMI.Unload();
            return;
        case 48: //boundRef
            XMBR.Unload();
            return;
        case 49: //ignoredBySandbox
            XIBS.Unload();
            return;
        case 50: //scale
            XSCL.Unload();
            return;
        case 51: //posX
            DATA.value.posX = defaultDATA.posX;
            return;
        case 52: //posY
            DATA.value.posY = defaultDATA.posY;
            return;
        case 53: //posZ
            DATA.value.posZ = defaultDATA.posZ;
            return;
        case 54: //rotX
            DATA.value.rotX = defaultDATA.rotX;
            return;
        case 55: //rotY
            DATA.value.rotY = defaultDATA.rotY;
            return;
        case 56: //rotZ
            DATA.value.rotZ = defaultDATA.rotZ;
            return;
        default:
            return;
        }
    }
}