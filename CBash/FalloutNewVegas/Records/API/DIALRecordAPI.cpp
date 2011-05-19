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
#include "..\DIALRecord.h"

namespace FNV
{
UINT32 DIALRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //quests
            if(ListFieldID == 0) //quests
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)QSTI.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= QSTI.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //quest
                    return FORMID_FIELD;
                case 2: //unknowns
                    if(ListX2FieldID == 0) //quests
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return LIST_FIELD;
                            case 1: //fieldSize
                                return (UINT32)QSTI.value[ListIndex]->Unknown.value.size();
                            default:
                                return UNKNOWN_FIELD;
                            }
                        return UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        return UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            return FORMID_FIELD;
                        case 2: //unknown
                            return SINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 8: //removedQuests
            if(ListFieldID == 0) //removedQuests
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)QSTR.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= QSTR.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //quest
                    return FORMID_FIELD;
                case 2: //unknowns
                    if(ListX2FieldID == 0) //unknowns
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return LIST_FIELD;
                            case 1: //fieldSize
                                return (UINT32)QSTR.value[ListIndex]->Unknown.value.size();
                            default:
                                return UNKNOWN_FIELD;
                            }
                        return UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= QSTR.value[ListIndex]->Unknown.value.size())
                        return UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            return FORMID_FIELD;
                        case 2: //unknown
                            return SINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 9: //full
            return STRING_FIELD;
        case 10: //priority
            return FLOAT32_FIELD;
        case 11: //unknown
            return STRING_FIELD;
        case 12: //dialType
            return UINT8_TYPE_FIELD;
        case 13: //flags
            return UINT8_FLAG_FIELD;
        case 14: //INFO
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return SUBRECORD_ARRAY_FIELD;
                case 1: //fieldSize
                    return (UINT32)INFO.size();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * DIALRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //quests
            if(ListIndex >= QSTI.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //quest
                    return &QSTI.value[ListIndex]->QSTI.value;
                case 2: //unknown
                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            return &QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value;
                        case 2: //unknown
                            return QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.value;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 8: //removedQuests
            if(ListIndex >= QSTR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //quest
                    return &QSTR.value[ListIndex]->QSTR.value;
                case 2: //unknown
                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            return &QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value;
                        case 2: //unknown
                            return QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.value;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 9: //full
            return FULL.value;
        case 10: //priority
            return &PNAM.value;
        case 11: //unknown
            return TDUM.value;
        case 12: //dialType
            return &DATA.value.dialType;
        case 13: //flags
            return &DATA.value.flags;
        case 14: //INFO
            for(UINT32 p = 0;p < (UINT32)INFO.size();++p)
                ((RECORDIDARRAY)FieldValues)[p] = INFO[p];
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool DIALRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //quests
            if(ListFieldID == 0) //questsSize
                {
                QSTI.resize(ArraySize);
                return false;
                }

            if(ListIndex >= QSTI.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //quest
                    QSTI.value[ListIndex]->QSTI.value = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown
                    if(ListX2FieldID == 0) //unknownsSize
                        {
                        QSTI.value[ListIndex]->Unknown.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value = *(FORMID *)FieldValue;
                            return true;
                        case 2: //unknown
                            QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.Load();
                            *QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.value = *(SINT32 *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 8: //removedQuests
            if(ListFieldID == 0) //removedQuestsSize
                {
                QSTR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= QSTR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //quest
                    QSTR.value[ListIndex]->QSTR.value = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown
                    if(ListX2FieldID == 0) //unknownsSize
                        {
                        QSTR.value[ListIndex]->Unknown.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= QSTR.value[ListIndex]->Unknown.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value = *(FORMID *)FieldValue;
                            return true;
                        case 2: //unknown
                            QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFX.Load();
                            *QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFX.value = *(SINT32 *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 9: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 10: //priority
            PNAM.value = *(FLOAT32 *)FieldValue;
            break;
        case 11: //unknown
            TDUM.Copy((STRING)FieldValue);
            break;
        case 12: //dialType
            SetType(*(UINT8 *)FieldValue);
            break;
        case 13: //flags
            SetFlagMask(*(UINT8 *)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void DIALRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    DIALDATA defaultDATA;
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
        case 7: //quests
            if(ListFieldID == 0) //questsSize
                {
                QSTI.Unload();
                return;
                }

            if(ListIndex >= QSTI.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //quest
                    QSTI.value[ListIndex]->QSTI.Unload();
                    return;
                case 2: //unknowns
                    if(ListX2FieldID == 0) //unknownsSize
                        {
                        QSTI.value[ListIndex]->Unknown.Unload();
                        return;
                        }

                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.Unload();
                            return;
                        case 2: //unknown
                            QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.Unload();
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 8: //removedQuests
            if(ListFieldID == 0) //removedQuestsSize
                {
                QSTR.Unload();
                return;
                }

            if(ListIndex >= QSTR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //quest
                    QSTR.value[ListIndex]->QSTR.Unload();
                    return;
                case 2: //unknowns
                    if(ListX2FieldID == 0) //unknownsSize
                        {
                        QSTR.value[ListIndex]->Unknown.Unload();
                        return;
                        }

                    if(ListX2Index >= QSTR.value[ListIndex]->Unknown.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFC.Unload();
                            return;
                        case 2: //unknown
                            QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFX.Unload();
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 9: //full
            FULL.Unload();
            return;
        case 10: //priority
            PNAM.Unload();
            return;
        case 11: //unknown
            TDUM.Unload();
            return;
        case 12: //dialType
            SetType(defaultDATA.dialType);
            return;
        case 13: //flags
            SetType(defaultDATA.flags);
            return;
        default:
            return;
        }
    }
}