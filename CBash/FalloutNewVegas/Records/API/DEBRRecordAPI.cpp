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
#include "..\DEBRRecord.h"

namespace FNV
{
UINT32 DEBRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //models
            if(ListFieldID == 0) //models
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)Models.MODS.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= Models.MODS.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //percentage
                    return UINT8_FIELD;
                case 2: //modPath
                    return ISTRING_FIELD;
                case 3: //flags
                    return UINT8_FLAG_FIELD;
                case 4: //modt_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Models.MODS[ListIndex]->MODT.GetSize();
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * DEBRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return cleaned_flag1();
        case 2: //fid
            return &formID;
        case 3: //versionControl1
            *FieldValues = cleaned_flag2();
            return NULL;
        case 4: //eid
            return EDID.value;
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //models
            if(ListIndex >= Models.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //percentage
                    return &Models.MODS[ListIndex]->percentage;
                case 2: //modPath
                    return Models.MODS[ListIndex]->modPath;
                case 3: //flags
                    return &Models.MODS[ListIndex]->flags;
                case 4: //modt_p
                    *FieldValues = Models.MODS[ListIndex]->MODT.value;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool DEBRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //models
            if(ListFieldID == 0) //modelsSize
                {
                Models.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Models.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //percentage
                    Models.MODS[ListIndex]->percentage = *(UINT8 *)FieldValue;
                    break;
                case 2: //modPath
                    delete []Models.MODS[ListIndex]->modPath;
                    Models.MODS[ListIndex]->modPath = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (UINT32)strlen((STRING)FieldValue) + 1;
                        Models.MODS[ListIndex]->modPath = new char[ArraySize];
                        strcpy_s(Models.MODS[ListIndex]->modPath, ArraySize, (STRING)FieldValue);
                        }
                    break;
                case 3: //flags
                    Models.MODS[ListIndex]->SetFlagMask(*(UINT8 *)FieldValue);
                    break;
                case 4: //modt_p
                    Models.MODS[ListIndex]->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
                    break;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void DEBRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    DEBRModel defaultModel;
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
        case 7: //models
            if(ListFieldID == 0) //modelsSize
                {
                Models.Unload();
                return;
                }

            if(ListIndex >= Models.MODS.size())
                return;

            switch(ListFieldID)
                {
                case 1: //percentage
                    Models.MODS[ListIndex]->percentage = defaultModel.percentage;
                    return;
                case 2: //modPath
                    delete []Models.MODS[ListIndex]->modPath;
                    Models.MODS[ListIndex]->modPath = NULL;
                    return;
                case 3: //flags
                    Models.MODS[ListIndex]->SetFlagMask(defaultModel.flags);
                    return;
                case 4: //modt_p
                    Models.MODS[ListIndex]->MODT.Unload();
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    }
}