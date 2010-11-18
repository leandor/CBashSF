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
#include "..\Common.h"
#include "..\Records\SPELRecord.h"

int SPELRecord::CreateListElement(const unsigned int subField)
    {
    GENEffect *curEffect = NULL;
    switch(subField)
        {
        case 12: //Effects
            curEffect = new GENEffect;
            Effects.push_back(curEffect);
            return (int)Effects.size() - 1;
        default:
            return -1;
        }
    }

int SPELRecord::DeleteListElement(const unsigned int subField)
    {
    GENEffect *curEffect = NULL;
    switch(subField)
        {
        case 12: //Effects
            curEffect = Effects.back();
            delete curEffect;
            Effects.pop_back();
            return (int)Effects.size() - 1;
        default:
            return -1;
        }
    }

int SPELRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //spellType
            return UINT_FIELD;
        case 8: //cost
            return UINT_FIELD;
        case 9: //level
            return UINT_FIELD;
        case 10: //flags
            return UBYTE_FIELD;
        case 11: //unused1
            return BYTES_FIELD;
        case 12: //Effects
            return LIST_FIELD;
        //OBME Fields
        case 13: //recordVersion
            return UBYTE_FIELD;
        case 14: //betaVersion
            return UBYTE_FIELD;
        case 15: //minorVersion
            return UBYTE_FIELD;
        case 16: //majorVersion
            return UBYTE_FIELD;
        case 17: //reserved
            return BYTES_FIELD;
        case 18: //datx_p
            return BYTES_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * SPELRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //spellType
            return &SPIT.value.spellType;
        case 8: //cost
            return &SPIT.value.cost;
        case 9: //level
            return &SPIT.value.level;
        case 10: //flags
            return &SPIT.value.flags;
        //OBME Fields
        case 11: //recordVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.recordVersion;
            return NULL;
        case 12: //betaVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.betaVersion;
            return NULL;
        case 13: //minorVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.minorVersion;
            return NULL;
        case 14: //majorVersion
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                return &OBME->OBME.value.majorVersion;
            return NULL;
        default:
            return NULL;
        }
    }

unsigned int SPELRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 11: //unused1
            return 3;
        //OBME Fields
        case 17: //reserved
            return 0x1C;
        case 18: //datx_p
            return 0x20;
        default:
            return 0;
        }
    }

void SPELRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 11: //unused1
            *FieldValues = &SPIT.value.unused1[0];
            return;
        //OBME Fields
        case 17: //reserved
            if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
                *FieldValues = &OBME->OBME.value.reserved[0];
            else
                *FieldValues = NULL;
            return;
        case 18: //datx_p
            if(OBME.IsLoaded() && OBME->DATX.IsLoaded())
                *FieldValues = OBME->DATX.value;
            else
                *FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int SPELRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
    {
    switch(subField)
        {
        case 12: //Effects
            switch(listField)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    return UINT_FIELD;
                case 3: //magnitude
                    return UINT_FIELD;
                case 4: //area
                    return UINT_FIELD;
                case 5: //duration
                    return UINT_FIELD;
                case 6: //recipient
                    return UINT_FIELD;
                case 7: //actorValue
                    return UINT_FIELD;
                case 8: //script
                    return FID_FIELD;
                case 9: //school
                    return UINT_FIELD;
                case 10: //visual
                    return UINT_FIELD;
                case 11: //flags
                    return UBYTE_FIELD;
                case 12: //unused1
                    return BYTES_FIELD;
                case 13: //full
                    return STRING_FIELD;
                //OBME Fields
                case 14: //recordVersion
                    return UBYTE_FIELD;
                case 15: //betaVersion
                    return UBYTE_FIELD;
                case 16: //minorVersion
                    return UBYTE_FIELD;
                case 17: //majorVersion
                    return UBYTE_FIELD;
                case 18: //efitParamInfo
                    return UBYTE_FIELD;
                case 19: //efixParamInfo
                    return UBYTE_FIELD;
                case 20: //reserved1
                    return BYTES_FIELD;
                case 21: //iconPath
                    return STRING_FIELD;
                case 22: //efixOverrideMask
                    return UINT_FIELD;
                case 23: //efixFlags
                    return UINT_FIELD;
                case 24: //baseCost
                    return FLOAT_FIELD;
                case 25: //resistAV
                    return UINT_FIELD;
                case 26: //reserved2
                    return BYTES_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int SPELRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 12: //Effects
            return (unsigned int)Effects.size();
        default:
            return 0;
        }
    }

unsigned int SPELRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 12: //Effects
            switch(listField)
                {
                case 12: //unused1
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        return 3;
                    return 0;
                //OBME Fields
                case 20: //reserved1
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        return 0xA;
                    return 0;
                case 26: //reserved2
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        return 0x10;
                    return 0;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

void SPELRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
    {
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 12: //unused1
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        *FieldValues = &Effects[listIndex]->SCIT->unused1[0];
                    else
                        *FieldValues = NULL;
                    return;
                //OBME Fields
                case 20: //reserved1
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        *FieldValues = &Effects[listIndex]->OBME->EFME.value.reserved[0];
                    else
                        *FieldValues = NULL;
                    return;
                case 26: //reserved2
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        *FieldValues = &Effects[listIndex]->OBME->EFIX->reserved[0];
                    else
                        *FieldValues = NULL;
                    return;
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void * SPELRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                return NULL;
            switch(listField)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    return &Effects[listIndex]->EFID.value.name;
                case 3: //magnitude
                    return &Effects[listIndex]->EFIT.value.magnitude;
                case 4: //area
                    return &Effects[listIndex]->EFIT.value.area;
                case 5: //duration
                    return &Effects[listIndex]->EFIT.value.duration;
                case 6: //recipient
                    return &Effects[listIndex]->EFIT.value.recipient;
                case 7: //actorValue
                    return &Effects[listIndex]->EFIT.value.actorValue;
                case 8: //script
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        return &Effects[listIndex]->SCIT->script;
                    else
                        return NULL;
                case 9: //school
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        return &Effects[listIndex]->SCIT->school;
                    else
                        return NULL;
                case 10: //visual
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        return &Effects[listIndex]->SCIT->visual;
                    else
                        return NULL;
                case 11: //flags
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        return &Effects[listIndex]->SCIT->flags;
                    else
                        return NULL;
                case 13: //full
                    return Effects[listIndex]->FULL.value;
                //OBME Fields
                case 14: //recordVersion
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        return &Effects[listIndex]->OBME->EFME.value.recordVersion;
                    else
                        return NULL;
                case 15: //betaVersion
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        return &Effects[listIndex]->OBME->EFME.value.betaVersion;
                    else
                        return NULL;
                case 16: //minorVersion
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        return &Effects[listIndex]->OBME->EFME.value.minorVersion;
                    else
                        return NULL;
                case 17: //majorVersion
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        return &Effects[listIndex]->OBME->EFME.value.majorVersion;
                    else
                        return NULL;
                case 18: //efitParamInfo
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        return &Effects[listIndex]->OBME->EFME.value.efitParamInfo;
                    else
                        return NULL;
                case 19: //efixParamInfo
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        return &Effects[listIndex]->OBME->EFME.value.efixParamInfo;
                    else
                        return NULL;
                case 21: //iconPath
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFII.IsLoaded())
                        return Effects[listIndex]->OBME->EFII.value;
                    else
                        return NULL;
                case 22: //efixOverrideMask
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        return &Effects[listIndex]->OBME->EFIX->efixOverrideMask;
                    else
                        return NULL;
                case 23: //efixFlags
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        return &Effects[listIndex]->OBME->EFIX->efixFlags;
                    else
                        return NULL;
                case 24: //baseCost
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        return &Effects[listIndex]->OBME->EFIX->baseCost;
                    else
                        return NULL;
                case 25: //resistAV
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        return &Effects[listIndex]->OBME->EFIX->resistAV;
                    else
                        return NULL;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void SPELRecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void SPELRecord::SetOtherField(const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 7: //spellType
            SPIT.value.spellType = FieldValue;
            break;
        case 8: //cost
            SPIT.value.cost = FieldValue;
            break;
        case 9: //level
            SPIT.value.level = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SPELRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 10: //flags
            SPIT.value.flags = FieldValue;
            break;
        //OBME Fields
        case 13: //recordVersion
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.recordVersion = FieldValue;
            break;
        case 14: //betaVersion
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.betaVersion = FieldValue;
            break;
        case 15: //minorVersion
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.minorVersion = FieldValue;
            break;
        case 16: //majorVersion
            OBME.Load();
            OBME->OBME.Load();
            OBME->OBME.value.majorVersion = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SPELRecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 11: //unused1
            if(nSize != 3)
                return;
            SPIT.value.unused1[0] = FieldValue[0];
            SPIT.value.unused1[1] = FieldValue[1];
            SPIT.value.unused1[2] = FieldValue[2];
            break;
        //OBME Fields
        case 17: //reserved
            if(nSize != 0x1C)
                return;
            OBME.Load();
            OBME->OBME.Load();
            memcpy(&OBME->OBME.value.reserved[0], &FieldValue[0], 0x1C);
            break;
        case 18: //datx_p
            if(nSize != 0x20)
                return;
            OBME.Load();
            OBME->DATX.Load();
            OBME->DATX.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void SPELRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
    {
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                return;
            switch(listField)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    Effects[listIndex]->EFID.value.name = FieldValue;
                    Effects[listIndex]->EFIT.value.name = FieldValue;
                    break;
                case 3: //magnitude
                    Effects[listIndex]->EFIT.value.magnitude = FieldValue;
                    break;
                case 4: //area
                    Effects[listIndex]->EFIT.value.area = FieldValue;
                    break;
                case 5: //duration
                    Effects[listIndex]->EFIT.value.duration = FieldValue;
                    break;
                case 6: //recipient
                    Effects[listIndex]->EFIT.value.recipient = FieldValue;
                    break;
                case 7: //actorValue
                    Effects[listIndex]->EFIT.value.actorValue = FieldValue;
                    break;
                case 8: //script
                    Effects[listIndex]->SCIT.Load();
                    Effects[listIndex]->SCIT->script = FieldValue;
                    break;
                case 9: //school
                    Effects[listIndex]->SCIT.Load();
                    Effects[listIndex]->SCIT->school = FieldValue;
                    break;
                case 10: //visual
                    Effects[listIndex]->SCIT.Load();
                    Effects[listIndex]->SCIT->visual = FieldValue;
                    break;
                //OBME Fields
                case 22: //efixOverrideMask
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFIX.Load();
                    Effects[listIndex]->OBME->EFIX->efixOverrideMask = FieldValue;
                    break;
                case 23: //efixFlags
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFIX.Load();
                    Effects[listIndex]->OBME->EFIX->efixFlags = FieldValue;
                    break;
                case 25: //resistAV
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFIX.Load();
                    Effects[listIndex]->OBME->EFIX->resistAV = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void SPELRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                return;
            switch(listField)
                {
                case 11: //flags
                    Effects[listIndex]->SCIT.Load();
                    Effects[listIndex]->SCIT->flags = FieldValue;
                    break;
                //OBME Fields
                case 14: //recordVersion
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFME.Load();
                    Effects[listIndex]->OBME->EFME.value.recordVersion = FieldValue;
                    break;
                case 15: //betaVersion
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFME.Load();
                    Effects[listIndex]->OBME->EFME.value.betaVersion = FieldValue;
                    break;
                case 16: //minorVersion
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFME.Load();
                    Effects[listIndex]->OBME->EFME.value.minorVersion = FieldValue;
                    break;
                case 17: //majorVersion
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFME.Load();
                    Effects[listIndex]->OBME->EFME.value.majorVersion = FieldValue;
                    break;
                case 18: //efitParamInfo
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFME.Load();
                    Effects[listIndex]->OBME->EFME.value.efitParamInfo = FieldValue;
                    break;
                case 19: //efixParamInfo
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFME.Load();
                    Effects[listIndex]->OBME->EFME.value.efixParamInfo = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void SPELRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue)
    {
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                return;
            switch(listField)
                {
                //OBME Fields
                case 24: //baseCost
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFIX.Load();
                    Effects[listIndex]->OBME->EFIX->baseCost = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void SPELRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                return;
            switch(listField)
                {
                case 12: //unused1
                    if(nSize != 3)
                        return;
                    Effects[listIndex]->SCIT.Load();
                    Effects[listIndex]->SCIT->unused1[0] = FieldValue[0];
                    Effects[listIndex]->SCIT->unused1[1] = FieldValue[1];
                    Effects[listIndex]->SCIT->unused1[2] = FieldValue[2];
                    break;
                //OBME Fields
                case 20: //reserved1
                    if(nSize != 0xA)
                        return;
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFME.Load();
                    memcpy(&Effects[listIndex]->OBME->EFME.value.reserved[0], &FieldValue[0], 0xA);
                    break;
                case 26: //reserved2
                    if(nSize != 0x10)
                        return;
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFIX.Load();
                    memcpy(&Effects[listIndex]->OBME->EFIX->reserved[0], &FieldValue[0], 0x10);
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void SPELRecord::SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue)
    {
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                return;
            switch(listField)
                {
                case 13: //full
                    Effects[listIndex]->FULL.Copy(FieldValue);
                    break;
                //OBME Fields
                case 21: //iconPath
                    Effects[listIndex]->OBME.Load();
                    Effects[listIndex]->OBME->EFII.Copy(FieldValue);
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

int SPELRecord::DeleteField(const unsigned int Field)
    {
    SPELSPIT defaultSPIT;
    MAGICOBME defaultOBME;
    unsigned int nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //spellType
            SPIT.value.spellType = defaultSPIT.spellType;
            break;
        case 8: //cost
            SPIT.value.cost = defaultSPIT.cost;
            break;
        case 9: //level
            SPIT.value.level = defaultSPIT.level;
            break;
        case 10: //flags
            SPIT.value.flags = defaultSPIT.flags;
            break;
        case 11: //unused1
            SPIT.value.unused1[0] = defaultSPIT.unused1[0];
            SPIT.value.unused1[1] = defaultSPIT.unused1[1];
            SPIT.value.unused1[2] = defaultSPIT.unused1[2];
            break;
        case 12: //Effects
            nSize = (unsigned int)Effects.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete Effects[x];
            Effects.clear();
            break;
        //OBME Fields
        case 13: //recordVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.recordVersion = defaultOBME.recordVersion;
            break;
        case 14: //betaVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.betaVersion = defaultOBME.betaVersion;
            break;
        case 15: //minorVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.minorVersion = defaultOBME.minorVersion;
            break;
        case 16: //majorVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.majorVersion = defaultOBME.majorVersion;
            break;
        case 17: //reserved
            if(OBME.IsLoaded())
                memcpy(&OBME->OBME.value.reserved[0], &defaultOBME.reserved[0], 0x1C);
            break;
        case 18: //datx_p
            if(OBME.IsLoaded() && OBME->DATX.IsLoaded())
                OBME->DATX.Unload();
            break;
        default:
            return 0;
        }
    return 1;
    }

int SPELRecord::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    GENEFIT defaultEFIT;
    GENSCIT defaultSCIT;
    OBMEEFME defaultEFME;
    OBMEEFIX defaultEFIX;
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                return 0;
            switch(listField)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    Effects[listIndex]->EFID.Unload();
                    Effects[listIndex]->EFIT.value.name = defaultEFIT.name;
                    break;
                case 3: //magnitude
                    Effects[listIndex]->EFIT.value.magnitude = defaultEFIT.magnitude;
                    break;
                case 4: //area
                    Effects[listIndex]->EFIT.value.area = defaultEFIT.area;
                    break;
                case 5: //duration
                    Effects[listIndex]->EFIT.value.duration = defaultEFIT.duration;
                    break;
                case 6: //recipient
                    Effects[listIndex]->EFIT.value.recipient = defaultEFIT.recipient;
                    break;
                case 7: //actorValue
                    Effects[listIndex]->EFIT.value.actorValue = defaultEFIT.actorValue;
                    break;
                case 8: //script
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        Effects[listIndex]->SCIT->script = defaultSCIT.script;
                    break;
                case 9: //school
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        Effects[listIndex]->SCIT->school = defaultSCIT.school;
                    break;
                case 10: //visual
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        Effects[listIndex]->SCIT->visual = defaultSCIT.visual;
                    break;
                case 11: //flags
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        Effects[listIndex]->SCIT->flags = defaultSCIT.flags;
                    break;
                case 12: //unused1
                    if(Effects[listIndex]->SCIT.IsLoaded())
                        {
                        Effects[listIndex]->SCIT->unused1[0] = defaultSCIT.unused1[0];
                        Effects[listIndex]->SCIT->unused1[1] = defaultSCIT.unused1[1];
                        Effects[listIndex]->SCIT->unused1[2] = defaultSCIT.unused1[2];
                        }
                    break;
                case 13: //full
                    Effects[listIndex]->FULL.Unload();
                    break;
                //OBME Fields
                case 14: //recordVersion
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        Effects[listIndex]->OBME->EFME.value.recordVersion = defaultEFME.recordVersion;
                    break;
                case 15: //betaVersion
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        Effects[listIndex]->OBME->EFME.value.betaVersion = defaultEFME.betaVersion;
                    break;
                case 16: //minorVersion
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        Effects[listIndex]->OBME->EFME.value.minorVersion = defaultEFME.minorVersion;
                    break;
                case 17: //majorVersion
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        Effects[listIndex]->OBME->EFME.value.majorVersion = defaultEFME.majorVersion;
                    break;
                case 18: //efitParamInfo
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        Effects[listIndex]->OBME->EFME.value.efitParamInfo = defaultEFME.efitParamInfo;
                    break;
                case 19: //efixParamInfo
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        Effects[listIndex]->OBME->EFME.value.efixParamInfo = defaultEFME.efixParamInfo;
                    break;
                case 20: //reserved1
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFME.IsLoaded())
                        memcpy(&Effects[listIndex]->OBME->EFME.value.reserved[0],&defaultEFME.reserved[0],0xA);
                    break;
                case 21: //iconPath
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFII.IsLoaded())
                        Effects[listIndex]->OBME->EFII.Unload();
                    break;
                case 22: //efixOverrideMask
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        Effects[listIndex]->OBME->EFIX->efixOverrideMask = defaultEFIX.efixOverrideMask;
                    break;
                case 23: //efixFlags
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        Effects[listIndex]->OBME->EFIX->efixFlags = defaultEFIX.efixFlags;
                    break;
                case 24: //baseCost
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        Effects[listIndex]->OBME->EFIX->baseCost = defaultEFIX.baseCost;
                    break;
                case 25: //resistAV
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        Effects[listIndex]->OBME->EFIX->resistAV = defaultEFIX.resistAV;
                    break;
                case 26: //reserved2
                    if(Effects[listIndex]->OBME.IsLoaded() && Effects[listIndex]->OBME->EFIX.IsLoaded())
                        memcpy(&Effects[listIndex]->OBME->EFIX->reserved[0],&defaultEFIX.reserved[0],0x10);
                    break;
                default:
                    return 0;
                }
            break;
        default:
            return 0;
        }
    return 1;
    }
