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
#include "..\Records\SGSTRecord.h"

int SGSTRecord::CreateListElement(const unsigned int subField)
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

int SGSTRecord::DeleteListElement(const unsigned int subField)
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

int SGSTRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //modPath
            return STRING_FIELD;
        case 8: //modb
            return FLOAT_FIELD;
        case 9: //modt_p
            return BYTES_FIELD;
        case 10: //iconPath
            return STRING_FIELD;
        case 11: //script
            return FID_FIELD;
        case 12: //Effects
            return LIST_FIELD;
        case 13: //uses
            return UBYTE_FIELD;
        case 14: //value
            return INT_FIELD;
        case 15: //weight
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * SGSTRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //modPath
            if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
                return MODL->MODL.value;
            return NULL;
        case 8: //modb
            if(MODL.IsLoaded() && MODL->MODB.IsLoaded())
                return &MODL->MODB.value.MODB;
            return NULL;
        case 10: //iconPath
            return ICON.value;
        case 11: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 13: //uses
            return &DATA.value.uses;
        case 14: //value
            return &DATA.value.value;
        case 15: //weight
            return &DATA.value.weight;
        default:
            return NULL;
        }
    }

unsigned int SGSTRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        default:
            return 0;
        }
    }

void SGSTRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 9: //modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

int SGSTRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
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
                    return INT_FIELD;
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
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned int SGSTRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 12: //Effects
            return (unsigned int)Effects.size();
        default:
            return 0;
        }
    }

unsigned int SGSTRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

void SGSTRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
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
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void * SGSTRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void SGSTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 7: //modPath
            MODL.Load();
            MODL->MODL.Copy(FieldValue);
            break;
        case 10: //iconPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void SGSTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 15: //weight
            DATA.value.weight = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SGSTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }

void SGSTRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 11: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        default:
            return;
        }
    return;
    }

void SGSTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 14: //value
            DATA.value.value = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SGSTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 13: //uses
            DATA.value.uses = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void SGSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
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
                case 8: //script
                    Effects[listIndex]->SCIT.Load();
                    Effects[listIndex]->SCIT->script = FieldValue;
                    FormIDHandler.AddMaster(Effects[listIndex]->SCIT->script);
                    break;
                case 9: //school
                    Effects[listIndex]->SCIT.Load();
                    Effects[listIndex]->SCIT->school = FieldValue;
                    break;
                case 10: //visual
                    Effects[listIndex]->SCIT.Load();
                    Effects[listIndex]->SCIT->visual = FieldValue;
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

void SGSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue)
    {
    switch(subField)
        {
        case 12: //Effects
            if(listIndex >= Effects.size())
                return;
            switch(listField)
                {
                case 7: //actorValue
                    Effects[listIndex]->EFIT.value.actorValue = FieldValue;
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

void SGSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
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
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void SGSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
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
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

void SGSTRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue)
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
                default:
                    return;
                }
            break;
        default:
            return;
        }
    return;
    }

int SGSTRecord::DeleteField(const unsigned int Field)
    {
    SGSTDATA defaultDATA;
    unsigned int nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            break;
        case 8: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            break;
        case 9: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            break;
        case 10: //iconPath
            ICON.Unload();
            break;
        case 11: //script
            SCRI.Unload();
            break;
        case 12: //Effects
            nSize = (unsigned int)Effects.size();
            for(unsigned int x = 0; x < nSize; x++)
                delete Effects[x];
            Effects.clear();
            break;
        case 13: //uses
            DATA.value.uses = defaultDATA.uses;
            break;
        case 14: //value
            DATA.value.value = defaultDATA.value;
            break;
        case 15: //weight
            DATA.value.weight = defaultDATA.weight;
            break;
        default:
            return 0;
        }
    return 1;
    }
    
int SGSTRecord::DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    GENEFIT defaultEFIT;
    GENSCIT defaultSCIT;
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
                default:
                    return 0;
                }
            break;
        default:
            return 0;
        }
    return 1;
    }