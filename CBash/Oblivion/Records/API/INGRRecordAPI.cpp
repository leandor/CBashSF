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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#include "..\..\..\Common.h"
#include "..\INGRRecord.h"

namespace Ob
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
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //full
            return STRING_FIELD;
        case 6: //modPath
            return ISTRING_FIELD;
        case 7: //modb
            return FLOAT32_FIELD;
        case 8: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 9: //iconPath
            return ISTRING_FIELD;
        case 10: //script
            return FORMID_FIELD;
        case 11: //weight
            return FLOAT32_FIELD;
        case 12: //value
            return SINT32_FIELD;
        case 13: //flags
            return UINT8_FLAG_FIELD;
        case 14: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 15: //effects
            if(ListFieldID == 0) //effects
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)Effects.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Effects.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return MGEFCODE_OR_UINT32_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded())
                                {
                                if(Effects.value[ListIndex]->EFID.value >= 0x80000000)
                                    return RESOLVED_MGEFCODE_FIELD;
                                return STATIC_MGEFCODE_FIELD;
                                }
                            else
                                return UINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 3: //magnitude
                    return UINT32_FIELD;
                case 4: //area
                    return UINT32_FIELD;
                case 5: //duration
                    return UINT32_FIELD;
                case 6: //rangeType
                    return UINT32_FIELD;
                case 7: //actorValue
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded())
                                {
                                switch(Effects.value[ListIndex]->OBME->EFME.value.efitParamInfo)
                                    {
                                    case 1: //It's a regular formID, so nothing fancy.
                                        return FORMID_FIELD;
                                    case 2: //It's a mgefCode, and not a formID at all.
                                        //Conditional resolution of mgefCode's based on JRoush's OBME mod
                                        //It's resolved just like a formID, except it uses the lower byte instead of the upper
                                        if(Effects.value[ListIndex]->EFIT.value.actorValue >= 0x80000000)
                                            return RESOLVED_MGEFCODE_FIELD;
                                        return STATIC_MGEFCODE_FIELD;
                                    case 3: //It's an actor value, and not a formID at all.
                                        //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                                        //It's resolved just like a formID
                                        if(Effects.value[ListIndex]->EFIT.value.actorValue >= 0x800)
                                            return RESOLVED_ACTORVALUE_FIELD;
                                        return STATIC_ACTORVALUE_FIELD;
                                    default: //It's not a formID, mgefCode, or fancied up actor value
                                        //so do nothing
                                        return UINT32_FIELD;
                                    }
                                }
                            else
                                return UINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 8: //script
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->SCIT.IsLoaded())
                                {
                                switch(Effects.value[ListIndex]->OBME->EFME.value.efixParamInfo)
                                    {
                                    case 1: //It's a regular formID, so nothing fancy.
                                        return FORMID_FIELD;
                                    case 2: //It's a mgefCode, and not a formID at all.
                                        //Conditional resolution of mgefCode's based on JRoush's OBME mod
                                        //It's resolved just like a formID, except it uses the lower byte instead of the upper
                                        if(Effects.value[ListIndex]->SCIT->script >= 0x80000000)
                                            return RESOLVED_MGEFCODE_FIELD;
                                        return STATIC_MGEFCODE_FIELD;
                                    case 3: //It's an actor value, and not a formID at all.
                                        //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                                        //It's resolved just like a formID
                                        if(Effects.value[ListIndex]->SCIT->script >= 0x800)
                                            return RESOLVED_ACTORVALUE_FIELD;
                                        return STATIC_ACTORVALUE_FIELD;
                                    default: //It's not a formID, mgefCode, or fancied up actor value
                                        //so do nothing
                                        return UINT32_FIELD;
                                    }
                                }
                            else
                                return FORMID_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 9: //school
                    return UINT32_FIELD;
                case 10: //visual
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return MGEFCODE_OR_UINT32_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->SCIT.IsLoaded())
                                {
                                if(Effects.value[ListIndex]->SCIT->visual >= 0x80000000)
                                    return RESOLVED_MGEFCODE_FIELD;
                                return STATIC_MGEFCODE_FIELD;
                                }
                            else
                                return UINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 11: //flags
                    return UINT8_FLAG_FIELD;
                case 12: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            if(Effects.value[ListIndex]->SCIT.IsLoaded())
                                return 3;
                            return 0;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 13: //full
                    return STRING_FIELD;
                //OBME Fields
                case 14: //recordVersion
                    return UINT8_FIELD;
                case 15: //betaVersion
                    return UINT8_FIELD;
                case 16: //minorVersion
                    return UINT8_FIELD;
                case 17: //majorVersion
                    return UINT8_FIELD;
                case 18: //efitParamInfo
                    return UINT8_FIELD;
                case 19: //efixParamInfo
                    return UINT8_FIELD;
                case 20: //reserved1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            if(Effects.value[ListIndex]->OBME.IsLoaded())
                                return 0xA;
                            return 0;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 21: //iconPath
                    return ISTRING_FIELD;
                case 22: //efixOverrides
                    return UINT32_FLAG_FIELD;
                case 23: //efixFlags
                    return UINT32_FLAG_FIELD;
                case 24: //baseCost
                    return FLOAT32_FIELD;
                case 25: //resistAV
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return ACTORVALUE_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                                {
                                if(Effects.value[ListIndex]->OBME->EFIX->resistAV >= 0x800)
                                    return RESOLVED_ACTORVALUE_FIELD;
                                return STATIC_ACTORVALUE_FIELD;
                                }
                            else
                                return UNKNOWN_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 26: //reserved2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                                return 0x10;
                            return 0;
                        default:
                            return UNKNOWN_FIELD;
                        }
                default:
                    return UNKNOWN_FIELD;
                }
        //OBME Fields
        case 16: //recordVersion
            return UINT8_FIELD;
        case 17: //betaVersion
            return UINT8_FIELD;
        case 18: //minorVersion
            return UINT8_FIELD;
        case 19: //majorVersion
            return UINT8_FIELD;
        case 20: //reserved
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return OBME.IsLoaded() ? 0x1C : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 21: //datx_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return (OBME.IsLoaded() && OBME->DATX.IsLoaded()) ? 0x20 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * INGRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return cleaned_flag1();
        case 2: //fid
            return &formID;
        case 3: //flags2
            return cleaned_flag2();
        case 4: //eid
            return EDID.value;
        case 5: //full
            return FULL.value;
        case 6: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 7: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 8: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 9: //iconPath
            return ICON.value;
        case 10: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 11: //weight
            return &DATA.value;
        case 12: //value
            return &ENIT.value.value;
        case 13: //flags
            return &ENIT.value.flags;
        case 14: //unused1
            *FieldValues = &ENIT.value.unused1[0];
            return NULL;
        case 15: //effects
            if(ListIndex >= Effects.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    return &Effects.value[ListIndex]->EFID.value;
                case 3: //magnitude
                    return &Effects.value[ListIndex]->EFIT.value.magnitude;
                case 4: //area
                    return &Effects.value[ListIndex]->EFIT.value.area;
                case 5: //duration
                    return &Effects.value[ListIndex]->EFIT.value.duration;
                case 6: //rangeType
                    return &Effects.value[ListIndex]->EFIT.value.rangeType;
                case 7: //actorValue
                    return &Effects.value[ListIndex]->EFIT.value.actorValue;
                case 8: //script
                    return Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->script : NULL;
                case 9: //school
                    return Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->school : NULL;
                case 10: //visual
                    return Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->visual : NULL;
                case 11: //flags
                    return Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->flags : NULL;
                case 12: //unused1
                    *FieldValues = Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->unused1[0] : NULL;
                    return NULL;
                case 13: //full
                    return Effects.value[ListIndex]->FULL.value;
                //OBME Fields
                case 14: //recordVersion
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.recordVersion : NULL;
                case 15: //betaVersion
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.betaVersion : NULL;
                case 16: //minorVersion
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.minorVersion : NULL;
                case 17: //majorVersion
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.majorVersion : NULL;
                case 18: //efitParamInfo
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.efitParamInfo : NULL;
                case 19: //efixParamInfo
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.efixParamInfo : NULL;
                case 20: //reserved1
                    *FieldValues = Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.reserved[0] : NULL;
                    return NULL;
                case 21: //iconPath
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? Effects.value[ListIndex]->OBME->EFII.value : NULL;
                case 22: //efixOverrides
                    return (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->efixOverrides : NULL;
                case 23: //efixFlags
                    return (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->efixFlags : NULL;
                case 24: //baseCost
                    return (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->baseCost : NULL;
                case 25: //resistAV
                    return (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->resistAV : NULL;
                case 26: //reserved2
                    *FieldValues = (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->reserved[0] : NULL;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        //OBME Fields
        case 16: //recordVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.recordVersion : NULL;
        case 17: //betaVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.betaVersion : NULL;
        case 18: //minorVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.minorVersion : NULL;
        case 19: //majorVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.majorVersion : NULL;
        case 20: //reserved
            *FieldValues = OBME.IsLoaded() ? &OBME->OBME.value.reserved[0] : NULL;
            return NULL;
        case 21: //datx_p
            *FieldValues = OBME.IsLoaded() ? OBME->DATX.value : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool INGRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(UINT32 *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 6: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 7: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 8: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 10: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 11: //weight
            DATA.value = *(FLOAT32 *)FieldValue;
            break;
        case 12: //value
            ENIT.value.value = *(SINT32 *)FieldValue;
            break;
        case 13: //flags
            SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 14: //unused1
            if(ArraySize != 3)
                break;
            ENIT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            ENIT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            ENIT.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 15: //effects
            if(ListFieldID == 0) //effectsSize
                {
                Effects.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Effects.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    Effects.value[ListIndex]->EFID.value = *(MGEFCODE_OR_UINT32 *)FieldValue;
                    Effects.value[ListIndex]->EFIT.value.name = *(MGEFCODE_OR_UINT32 *)FieldValue;
                    return true;
                case 3: //magnitude
                    Effects.value[ListIndex]->EFIT.value.magnitude = *(UINT32 *)FieldValue;
                    break;
                case 4: //area
                    Effects.value[ListIndex]->EFIT.value.area = *(UINT32 *)FieldValue;
                    break;
                case 5: //duration
                    Effects.value[ListIndex]->EFIT.value.duration = *(UINT32 *)FieldValue;
                    break;
                case 6: //rangeType
                    Effects.value[ListIndex]->SetRange(*(UINT32 *)FieldValue);
                    break;
                case 7: //actorValue
                    Effects.value[ListIndex]->EFIT.value.actorValue = *(FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 *)FieldValue;
                    return true;
                case 8: //script
                    Effects.value[ListIndex]->SCIT.Load();
                    Effects.value[ListIndex]->SCIT->script = *(FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 *)FieldValue;
                    return true;
                case 9: //school
                    Effects.value[ListIndex]->SCIT.Load();
                    Effects.value[ListIndex]->SCIT->school = *(UINT32 *)FieldValue;
                    break;
                case 10: //visual
                    Effects.value[ListIndex]->SCIT.Load();
                    Effects.value[ListIndex]->SCIT->visual = *(MGEFCODE_OR_UINT32 *)FieldValue;
                    return true;
                case 11: //flags
                    Effects.value[ListIndex]->SetFlagMask(*(UINT8 *)FieldValue);
                    break;
                case 12: //unused1
                    if(ArraySize != 3)
                        break;
                    Effects.value[ListIndex]->SCIT.Load();
                    Effects.value[ListIndex]->SCIT->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Effects.value[ListIndex]->SCIT->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Effects.value[ListIndex]->SCIT->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                case 13: //full
                    Effects.value[ListIndex]->FULL.Copy((STRING)FieldValue);
                    break;
                //OBME Fields
                case 14: //recordVersion
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.recordVersion = *(UINT8 *)FieldValue;
                    break;
                case 15: //betaVersion
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.betaVersion = *(UINT8 *)FieldValue;
                    break;
                case 16: //minorVersion
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.minorVersion = *(UINT8 *)FieldValue;
                    break;
                case 17: //majorVersion
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.majorVersion = *(UINT8 *)FieldValue;
                    break;
                case 18: //efitParamInfo
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.efitParamInfo = *(UINT8 *)FieldValue;
                    return true;
                case 19: //efixParamInfo
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.efixParamInfo = *(UINT8 *)FieldValue;
                    return true;
                case 20: //reserved1
                    if(ArraySize != 0xA)
                        break;
                    Effects.value[ListIndex]->OBME.Load();
                    memcpy(&Effects.value[ListIndex]->OBME->EFME.value.reserved[0], &((UINT8ARRAY)FieldValue)[0], sizeof(Effects.value[ListIndex]->OBME->EFME.value.reserved));
                    break;
                case 21: //iconPath
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFII.Copy((STRING)FieldValue);
                    break;
                case 22: //efixOverrides
                    Effects.value[ListIndex]->OBME_SetOverrideFlagMask(*(UINT32 *)FieldValue);
                    return true;
                case 23: //efixFlags
                    Effects.value[ListIndex]->OBME_SetFlagMask(*(UINT32 *)FieldValue);
                    return true;
                case 24: //baseCost
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFIX.Load();
                    Effects.value[ListIndex]->OBME->EFIX->baseCost = *(FLOAT32 *)FieldValue;
                    break;
                case 25: //resistAV
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFIX.Load();
                    Effects.value[ListIndex]->OBME->EFIX->resistAV = *(ACTORVALUE *)FieldValue;
                    return true;
                case 26: //reserved2
                    if(ArraySize != 0x10)
                        break;
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFIX.Load();
                    memcpy(&Effects.value[ListIndex]->OBME->EFIX->reserved[0], &((UINT8ARRAY)FieldValue)[0], sizeof(Effects.value[ListIndex]->OBME->EFIX->reserved));
                    break;
                default:
                    break;
                }
            break;
        //OBME Fields
        case 16: //recordVersion
            OBME.Load();
            OBME->OBME.value.recordVersion = *(UINT8 *)FieldValue;
            break;
        case 17: //betaVersion
            OBME.Load();
            OBME->OBME.value.betaVersion = *(UINT8 *)FieldValue;
            break;
        case 18: //minorVersion
            OBME.Load();
            OBME->OBME.value.minorVersion = *(UINT8 *)FieldValue;
            break;
        case 19: //majorVersion
            OBME.Load();
            OBME->OBME.value.majorVersion = *(UINT8 *)FieldValue;
            break;
        case 20: //reserved
            if(ArraySize != 0x1C)
                break;
            OBME.Load();
            memcpy(&OBME->OBME.value.reserved[0], &((UINT8ARRAY)FieldValue)[0], sizeof(OBME->OBME.value.reserved));
            break;
        case 21: //datx_p
            if(ArraySize != 0x20)
                break;
            OBME.Load();
            OBME->DATX.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void INGRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENENIT defaultENIT;
    MAGICOBME defaultOBME;

    GENEFIT defaultEFIT;
    GENSCIT defaultSCIT;
    OBMEEFME defaultEFME;
    OBMEEFIX defaultEFIX;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //full
            FULL.Unload();
            return;
        case 6: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 7: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 8: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 9: //iconPath
            ICON.Unload();
            return;
        case 10: //script
            SCRI.Unload();
            return;
        case 11: //weight
            DATA.Unload();
            return;
        case 12: //value
            ENIT.value.value = defaultENIT.value;
            return;
        case 13: //flags
            ENIT.value.flags = defaultENIT.flags;
            return;
        case 14: //unused1
            ENIT.value.unused1[0] = defaultENIT.unused1[0];
            ENIT.value.unused1[1] = defaultENIT.unused1[1];
            ENIT.value.unused1[2] = defaultENIT.unused1[2];
            return;
        case 15: //effects
            if(ListFieldID == 0) //effects
                {
                Effects.Unload();
                return;
                }

            if(ListIndex >= Effects.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    Effects.value[ListIndex]->EFID.Unload();
                    Effects.value[ListIndex]->EFIT.value.name = defaultEFIT.name;
                    return;
                case 3: //magnitude
                    Effects.value[ListIndex]->EFIT.value.magnitude = defaultEFIT.magnitude;
                    return;
                case 4: //area
                    Effects.value[ListIndex]->EFIT.value.area = defaultEFIT.area;
                    return;
                case 5: //duration
                    Effects.value[ListIndex]->EFIT.value.duration = defaultEFIT.duration;
                    return;
                case 6: //rangeType
                    Effects.value[ListIndex]->EFIT.value.rangeType = defaultEFIT.rangeType;
                    return;
                case 7: //actorValue
                    Effects.value[ListIndex]->EFIT.value.actorValue = defaultEFIT.actorValue;
                    return;
                case 8: //script
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        Effects.value[ListIndex]->SCIT->script = defaultSCIT.script;
                    return;
                case 9: //school
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        Effects.value[ListIndex]->SCIT->school = defaultSCIT.school;
                    return;
                case 10: //visual
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        Effects.value[ListIndex]->SCIT->visual = defaultSCIT.visual;
                    return;
                case 11: //flags
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        Effects.value[ListIndex]->SCIT->flags = defaultSCIT.flags;
                    return;
                case 12: //unused1
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        {
                        Effects.value[ListIndex]->SCIT->unused1[0] = defaultSCIT.unused1[0];
                        Effects.value[ListIndex]->SCIT->unused1[1] = defaultSCIT.unused1[1];
                        Effects.value[ListIndex]->SCIT->unused1[2] = defaultSCIT.unused1[2];
                        }
                    return;
                case 13: //full
                    Effects.value[ListIndex]->FULL.Unload();
                    return;
                //OBME Fields
                case 14: //recordVersion
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.recordVersion = defaultEFME.recordVersion;
                    return;
                case 15: //betaVersion
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.betaVersion = defaultEFME.betaVersion;
                    return;
                case 16: //minorVersion
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.minorVersion = defaultEFME.minorVersion;
                    return;
                case 17: //majorVersion
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.majorVersion = defaultEFME.majorVersion;
                    return;
                case 18: //efitParamInfo
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.efitParamInfo = defaultEFME.efitParamInfo;
                    return;
                case 19: //efixParamInfo
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.efixParamInfo = defaultEFME.efixParamInfo;
                    return;
                case 20: //reserved1
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        memcpy(&Effects.value[ListIndex]->OBME->EFME.value.reserved[0],&defaultEFME.reserved[0], sizeof(Effects.value[ListIndex]->OBME->EFME.value.reserved));
                    return;
                case 21: //iconPath
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFII.Unload();
                    return;
                case 22: //efixOverrides
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFIX->efixOverrides = defaultEFIX.efixOverrides;
                    return;
                case 23: //efixFlags
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFIX->efixFlags = defaultEFIX.efixFlags;
                    return;
                case 24: //baseCost
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFIX->baseCost = defaultEFIX.baseCost;
                    return;
                case 25: //resistAV
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFIX->resistAV = defaultEFIX.resistAV;
                    return;
                case 26: //reserved2
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        memcpy(&Effects.value[ListIndex]->OBME->EFIX->reserved[0],&defaultEFIX.reserved[0], sizeof(Effects.value[ListIndex]->OBME->EFIX->reserved));
                    return;
                default:
                    return;
                }
            return;
        //OBME Fields
        case 16: //recordVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.recordVersion = defaultOBME.recordVersion;
            return;
        case 17: //betaVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.betaVersion = defaultOBME.betaVersion;
            return;
        case 18: //minorVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.minorVersion = defaultOBME.minorVersion;
            return;
        case 19: //majorVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.majorVersion = defaultOBME.majorVersion;
            return;
        case 20: //reserved
            if(OBME.IsLoaded())
                memcpy(&OBME->OBME.value.reserved[0], &defaultOBME.reserved[0], sizeof(OBME->OBME.value.reserved));
            return;
        case 21: //datx_p
            if(OBME.IsLoaded())
                OBME->DATX.Unload();
            return;
        default:
            return;
        }
    return;
    }
}