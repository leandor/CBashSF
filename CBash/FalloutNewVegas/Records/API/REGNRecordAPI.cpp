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
#include "..\REGNRecord.h"

namespace FNV
{
UINT32 REGNRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //iconPath
            return ISTRING_FIELD;
        case 8: //smallIconPath
            return ISTRING_FIELD;
        case 9: //mapRed
            return UINT8_FIELD;
        case 10: //mapGreen
            return UINT8_FIELD;
        case 11: //mapBlue
            return UINT8_FIELD;
        case 12: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 13: //worldspace
            return FORMID_FIELD;
        case 14: //areas
            if(ListFieldID == 0) //areas
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)Areas.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Areas.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //edgeFalloff
                    return FORMID_FIELD;
                case 2: //points
                    if(ListX2FieldID == 0) //points
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return LIST_FIELD;
                            case 1: //fieldSize
                                return (UINT32)Areas.value[ListIndex]->RPLD.value.size();
                            default:
                                return UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Areas.value[ListIndex]->RPLD.value.size())
                        return UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            return FLOAT32_FIELD;
                        case 2: //posY
                            return FLOAT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 15: //entries
            if(ListFieldID == 0) //entries
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)Entries.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Entries.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //entryType
                    return UINT32_TYPE_FIELD;
                case 2: //flags
                    return UINT8_FLAG_FIELD;
                case 3: //priority
                    return UINT8_FIELD;
                case 4: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 2;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 5: //objects
                    if(ListX2FieldID == 0) //points
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return LIST_FIELD;
                            case 1: //fieldSize
                                return (UINT32)Entries.value[ListIndex]->RDOT.value.size();
                            default:
                                return UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDOT.value.size())
                        return UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //objectId
                            return FORMID_FIELD;
                        case 2: //parentIndex
                            return UINT16_FIELD;
                        case 3: //unused1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 2;
                                default:
                                    return UNKNOWN_FIELD;
                                }
                        case 4: //density
                            return FLOAT32_FIELD;
                        case 5: //clustering
                            return UINT8_FIELD;
                        case 6: //minSlope
                            return UINT8_FIELD;
                        case 7: //maxSlope
                            return UINT8_FIELD;
                        case 8: //flags
                            return UINT8_FLAG_FIELD;
                        case 9: //radiusWRTParent
                            return UINT16_FIELD;
                        case 10: //radius
                            return UINT16_FIELD;
                        case 11: //unk1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 4;
                                default:
                                    return UNKNOWN_FIELD;
                                }
                        case 12: //maxHeight
                            return FLOAT32_FIELD;
                        case 13: //sink
                            return FLOAT32_FIELD;
                        case 14: //sinkVar
                            return FLOAT32_FIELD;
                        case 15: //sizeVar
                            return FLOAT32_FIELD;
                        case 16: //angleVarX
                            return UINT16_FIELD;
                        case 17: //angleVarY
                            return UINT16_FIELD;
                        case 18: //angleVarZ
                            return UINT16_FIELD;
                        case 19: //unused2
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 2;
                                default:
                                    return UNKNOWN_FIELD;
                                }
                        case 20: //unk2
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 4;
                                default:
                                    return UNKNOWN_FIELD;
                                }
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 6: //mapName
                    return STRING_FIELD;
                case 7: //iconPath
                    return ISTRING_FIELD;
                case 8: //grasses
                    if(ListX2FieldID == 0) //grasses
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return LIST_FIELD;
                            case 1: //fieldSize
                                return (UINT32)Entries.value[ListIndex]->RDGS.value.size();
                            default:
                                return UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDGS.value.size())
                        return UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //grass
                            return FORMID_FIELD;
                        case 2: //unk1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 4;
                                default:
                                    return UNKNOWN_FIELD;
                                }
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 9: //musicType
                    return UINT32_TYPE_FIELD;
                case 10: //music
                    return FORMID_FIELD;
                case 11: //incidentalMedia
                    return FORMID_FIELD;
                case 12: //battleMedias
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_ARRAY_FIELD;
                        case 1: //fieldSize
                            return (UINT32)Entries.value[ListIndex]->RDSB.value.size();
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                case 13: //sounds
                    if(ListX2FieldID == 0) //sounds
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return LIST_FIELD;
                            case 1: //fieldSize
                                return (UINT32)Entries.value[ListIndex]->RDSD.value.size();
                            default:
                                return UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDSD.value.size())
                        return UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            return FORMID_FIELD;
                        case 2: //flags
                            return UINT32_FLAG_FIELD;
                        case 3: //chance
                            return UINT32_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 14: //weathers
                    if(ListX2FieldID == 0) //weathers
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return LIST_FIELD;
                            case 1: //fieldSize
                                return (UINT32)Entries.value[ListIndex]->RDWT.value.size();
                            default:
                                return UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDWT.value.size())
                        return UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //weather
                            return FORMID_FIELD;
                        case 2: //chance
                            return UINT32_FIELD;
                        case 3: //globalId
                            return FORMID_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 15: //imposters
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_ARRAY_FIELD;
                        case 1: //fieldSize
                            return (UINT32)Entries.value[ListIndex]->RDID.value.size();
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * REGNRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //iconPath
            return ICON.value;
        case 8: //smallIconPath
            return MICO.value;
        case 9: //mapRed
            return &RCLR.value.red;
        case 10: //mapGreen
            return &RCLR.value.green;
        case 11: //mapBlue
            return &RCLR.value.blue;
        case 12: //unused1
            *FieldValues = &RCLR.value.unused1;
            return NULL;
        case 13: //worldspace
            return WNAM.IsLoaded() ? &WNAM.value : NULL;
        case 14: //areas
            if(ListIndex >= Areas.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //edgeFalloff
                    return &Areas.value[ListIndex]->RPLI.value;
                case 2: //points
                    if(ListX2Index >= Areas.value[ListIndex]->RPLD.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            return &Areas.value[ListIndex]->RPLD.value[ListX2Index].posX;
                        case 2: //posY
                            return &Areas.value[ListIndex]->RPLD.value[ListX2Index].posY;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 15: //entries
            if(ListIndex >= Entries.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //entryType
                    return &Entries.value[ListIndex]->RDAT.value.entryType;
                case 2: //flags
                    return &Entries.value[ListIndex]->RDAT.value.flags;
                case 3: //priority
                    return &Entries.value[ListIndex]->RDAT.value.priority;
                case 4: //unused1
                    *FieldValues = &Entries.value[ListIndex]->RDAT.value.unused1[0];
                    return NULL;
                case 5: //objects
                    if(ListX2Index >= Entries.value[ListIndex]->RDOT.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //objectId
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].objectId;
                        case 2: //parentIndex
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].parentIndex;
                        case 3: //unused1
                            *FieldValues = &Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[0];
                            return NULL;
                        case 4: //density
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].density;
                        case 5: //clustering
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].clustering;
                        case 6: //minSlope
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].minSlope;
                        case 7: //maxSlope
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].maxSlope;
                        case 8: //flags
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].flags;
                        case 9: //radiusWRTParent
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].radiusWRTParent;
                        case 10: //radius
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].radius;
                        case 11: //unk1
                            *FieldValues = &Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[0];
                            return NULL;
                        case 12: //maxHeight
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].maxHeight;
                        case 13: //sink
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].sink;
                        case 14: //sinkVar
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].sinkVar;
                        case 15: //sizeVar
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].sizeVar;
                        case 16: //angleVarX
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarX;
                        case 17: //angleVarY
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarY;
                        case 18: //angleVarZ
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarZ;
                        case 19: //unused2
                            *FieldValues = &Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[0];
                            return NULL;
                        case 20: //unk2
                            *FieldValues = &Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[0];
                            return NULL;
                        default:
                            return NULL;
                        }
                    return NULL;
                case 6: //mapName
                    return Entries.value[ListIndex]->RDMP.value;
                case 7: //iconPath
                    return Entries.value[ListIndex]->ICON.value;
                case 8: //grasses
                    if(ListX2Index >= Entries.value[ListIndex]->RDGS.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //grass
                            return &Entries.value[ListIndex]->RDGS.value[ListX2Index].grass;
                        case 2: //unk1
                            *FieldValues = &Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[0];
                            return NULL;
                        default:
                            return NULL;
                        }
                    return NULL;
                case 9: //musicType
                    return Entries.value[ListIndex]->RDMD.value;
                case 10: //music
                    return &Entries.value[ListIndex]->RDMO.value;
                case 11: //incidentalMedia
                    return &Entries.value[ListIndex]->RDSI.value;
                case 12: //battleMedias
                    *FieldValues = Entries.value[ListIndex]->RDSB.IsLoaded() ? &Entries.value[ListIndex]->RDSB.value[0] : NULL;
                    return NULL;
                case 13: //sounds
                    if(ListX2Index >= Entries.value[ListIndex]->RDSD.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            return &Entries.value[ListIndex]->RDSD.value[ListX2Index].sound;
                        case 2: //flags
                            return &Entries.value[ListIndex]->RDSD.value[ListX2Index].flags;
                        case 3: //chance
                            return &Entries.value[ListIndex]->RDSD.value[ListX2Index].chance;
                        default:
                            return NULL;
                        }
                    return NULL;
                case 14: //weathers
                    if(ListX2Index >= Entries.value[ListIndex]->RDWT.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //weather
                            return &Entries.value[ListIndex]->RDWT.value[ListX2Index].weather;
                        case 2: //chance
                            return &Entries.value[ListIndex]->RDWT.value[ListX2Index].chance;
                        case 3: //globalId
                            return &Entries.value[ListIndex]->RDWT.value[ListX2Index].globalId;
                        default:
                            return NULL;
                        }
                    return NULL;
                case 15: //imposters
                    *FieldValues = Entries.value[ListIndex]->RDID.IsLoaded() ? &Entries.value[ListIndex]->RDID.value[0] : NULL;
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

bool REGNRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 8: //smallIconPath
            MICO.Copy((STRING)FieldValue);
            break;
        case 9: //mapRed
            RCLR.value.red = *(UINT8 *)FieldValue;
            break;
        case 10: //mapGreen
            RCLR.value.green = *(UINT8 *)FieldValue;
            break;
        case 11: //mapBlue
            RCLR.value.blue = *(UINT8 *)FieldValue;
            break;
        case 12: //unused1
            if(ArraySize != 1)
                break;
            RCLR.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 13: //worldspace
            WNAM.Load();
            WNAM.value = *(FORMID *)FieldValue;
            return true;
        case 14: //areas
            if(ListFieldID == 0) //areasSize
                {
                Areas.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Areas.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //edgeFalloff
                    Areas.value[ListIndex]->RPLI.value = *(UINT32 *)FieldValue;
                    break;
                case 2: //points
                    if(ListX2FieldID == 0) //pointsSize
                        {
                        Areas.value[ListIndex]->RPLD.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Areas.value[ListIndex]->RPLD.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            Areas.value[ListIndex]->RPLD.value[ListX2Index].posX = *(FLOAT32 *)FieldValue;
                            break;
                        case 2: //posY
                            Areas.value[ListIndex]->RPLD.value[ListX2Index].posY = *(FLOAT32 *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 15: //entries
            if(ListFieldID == 0) //areasSize
                {
                Entries.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Entries.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //entryType
                    Entries.value[ListIndex]->SetType(*(UINT32 *)FieldValue);
                    return true;
                case 2: //flags
                    Entries.value[ListIndex]->SetFlagMask(*(UINT8 *)FieldValue);
                    break;
                case 3: //priority
                    Entries.value[ListIndex]->RDAT.value.priority = *(UINT8 *)FieldValue;
                    break;
                case 4: //unused1
                    if(ArraySize != 2)
                        break;
                    Entries.value[ListIndex]->RDAT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Entries.value[ListIndex]->RDAT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 5: //objects
                    if(ListX2FieldID == 0) //objectsSize
                        {
                        Entries.value[ListIndex]->RDOT.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDOT.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //objectId
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].objectId = *(FORMID *)FieldValue;
                            return true;
                        case 2: //parentIndex
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].parentIndex = *(UINT16 *)FieldValue;
                            break;
                        case 3: //unused1
                            if(ArraySize != 2)
                                break;
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            break;
                        case 4: //density
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].density = *(FLOAT32 *)FieldValue;
                            break;
                        case 5: //clustering
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].clustering = *(UINT8 *)FieldValue;
                            break;
                        case 6: //minSlope
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].minSlope = *(UINT8 *)FieldValue;
                            break;
                        case 7: //maxSlope
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].maxSlope = *(UINT8 *)FieldValue;
                            break;
                        case 8: //flags
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].SetFlagMask(*(UINT8 *)FieldValue);
                            break;
                        case 9: //radiusWRTParent
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].radiusWRTParent = *(UINT16 *)FieldValue;
                            break;
                        case 10: //radius
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].radius = *(UINT16 *)FieldValue;
                            break;
                        case 11: //unk1
                            if(ArraySize != 4)
                                break;
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[2] = ((UINT8ARRAY)FieldValue)[2];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[3] = ((UINT8ARRAY)FieldValue)[3];
                            break;
                        case 12: //maxHeight
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].maxHeight = *(FLOAT32 *)FieldValue;
                            break;
                        case 13: //sink
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sink = *(FLOAT32 *)FieldValue;
                            break;
                        case 14: //sinkVar
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sinkVar = *(FLOAT32 *)FieldValue;
                            break;
                        case 15: //sizeVar
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sizeVar = *(FLOAT32 *)FieldValue;
                            break;
                        case 16: //angleVarX
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarX = *(UINT16 *)FieldValue;
                            break;
                        case 17: //angleVarY
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarY = *(UINT16 *)FieldValue;
                            break;
                        case 18: //angleVarZ
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarZ = *(UINT16 *)FieldValue;
                            break;
                        case 19: //unused2
                            if(ArraySize != 2)
                                break;
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                            break;
                        case 20: //unk2
                            if(ArraySize != 4)
                                break;
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[1] = ((UINT8ARRAY)FieldValue)[1];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[2] = ((UINT8ARRAY)FieldValue)[2];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[3] = ((UINT8ARRAY)FieldValue)[3];
                            break;
                        default:
                            break;
                        }
                    break;
                case 6: //mapName
                    Entries.value[ListIndex]->RDMP.Copy((STRING)FieldValue);
                    break;
                case 7: //iconPath
                    Entries.value[ListIndex]->ICON.Copy((STRING)FieldValue);
                    break;
                case 8: //grasses
                    if(ListX2FieldID == 0) //grassesSize
                        {
                        Entries.value[ListIndex]->RDGS.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDGS.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //grass
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].grass = *(FORMID *)FieldValue;
                            return true;
                        case 2: //unk1
                            if(ArraySize != 4)
                                break;
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[2] = ((UINT8ARRAY)FieldValue)[2];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[3] = ((UINT8ARRAY)FieldValue)[3];
                            break;
                        default:
                            break;
                        }
                    break;
                case 9: //musicType
                    Entries.value[ListIndex]->SetMusicType(*(UINT32 *)FieldValue);
                    break;
                case 10: //music
                    Entries.value[ListIndex]->RDMO.value = *(FORMID *)FieldValue;
                    return true;
                case 11: //incidentalMedia
                    Entries.value[ListIndex]->RDSI.value = *(FORMID *)FieldValue;
                    return true;
                case 12: //battleMedias
                    Entries.value[ListIndex]->RDSB.value.resize(ArraySize);
                    for(UINT32 x = 0; x < ArraySize; x++)
                        Entries.value[ListIndex]->RDSB.value[x] = ((FORMIDARRAY)FieldValue)[x];
                    return true;
                case 13: //sounds
                    if(ListX2FieldID == 0) //soundsSize
                        {
                        Entries.value[ListIndex]->RDSD.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDSD.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].sound = *(FORMID *)FieldValue;
                            return true;
                        case 2: //flags
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].SetFlagMask(*(UINT32 *)FieldValue);
                            break;
                        case 3: //chance
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].chance = *(UINT32 *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                case 14: //weathers
                    if(ListX2FieldID == 0) //weathersSize
                        {
                        Entries.value[ListIndex]->RDWT.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDWT.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //weather
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].weather = *(FORMID *)FieldValue;
                            return true;
                        case 2: //chance
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].chance = *(UINT32 *)FieldValue;
                            break;
                        case 3: //globalId
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].globalId = *(FORMID *)FieldValue;
                            return true;
                        default:
                            break;
                        }
                    break;
                case 15: //imposters
                    Entries.value[ListIndex]->RDID.value.resize(ArraySize);
                    for(UINT32 x = 0; x < ArraySize; x++)
                        Entries.value[ListIndex]->RDID.value[x] = ((FORMIDARRAY)FieldValue)[x];
                    return true;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void REGNRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENCLR defaultCLR;

    REGNRDAT defaultRDAT;

    REGNRPLD defaultRPLD;
    REGNRDOT defaultRDOT;
    REGNRDGS defaultRDGS;
    REGNRDSD defaultRDSD;
    REGNRDWT defaultRDWT;

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
        case 7: //iconPath
            ICON.Unload();
            return;
        case 8: //smallIconPath
            MICO.Unload();
            return;
        case 9: //mapRed
            RCLR.value.red = defaultCLR.red;
            return;
        case 10: //mapGreen
            RCLR.value.green = defaultCLR.green;
            return;
        case 11: //mapBlue
            RCLR.value.blue = defaultCLR.blue;
            return;
        case 12: //unused1
            RCLR.value.unused1 = defaultCLR.unused1;
            return;
        case 13: //worldspace
            WNAM.Unload();
            return;
        case 14: //areas
            if(ListFieldID == 0) //areas
                {
                Areas.Unload();
                return;
                }

            if(ListIndex >= Areas.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //edgeFalloff
                    Areas.value[ListIndex]->RPLI.Unload();
                    return;
                case 2: //points
                    if(ListX2FieldID == 0) //points
                        {
                        Areas.value[ListIndex]->RPLD.Unload();
                        return;
                        }

                    if(ListX2Index >= Areas.value[ListIndex]->RPLD.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            Areas.value[ListIndex]->RPLD.value[ListX2Index].posX = defaultRPLD.posX;
                            return;
                        case 2: //posY
                            Areas.value[ListIndex]->RPLD.value[ListX2Index].posY = defaultRPLD.posY;
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 15: //entries
            if(ListFieldID == 0) //entries
                {
                Entries.Unload();
                return;
                }

            if(ListIndex >= Entries.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //entryType
                    Entries.value[ListIndex]->RDAT.value.entryType = defaultRDAT.entryType;
                    return;
                case 2: //flags
                    Entries.value[ListIndex]->RDAT.value.flags = defaultRDAT.flags;
                    return;
                case 3: //priority
                    Entries.value[ListIndex]->RDAT.value.priority = defaultRDAT.priority;
                    return;
                case 4: //unused1
                    Entries.value[ListIndex]->RDAT.value.unused1[0] = defaultRDAT.unused1[0];
                    Entries.value[ListIndex]->RDAT.value.unused1[1] = defaultRDAT.unused1[1];
                    return;
                case 5: //objects
                    if(ListX2FieldID == 0) //objects
                        {
                        Entries.value[ListIndex]->RDOT.Unload();
                        return;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDOT.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //objectId
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].objectId = defaultRDOT.objectId;
                            return;
                        case 2: //parentIndex
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].parentIndex = defaultRDOT.parentIndex;
                            return;
                        case 3: //unused1
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[0] = defaultRDOT.unused1[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[1] = defaultRDOT.unused1[1];
                            return;
                        case 4: //density
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].density = defaultRDOT.density;
                            return;
                        case 5: //clustering
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].clustering = defaultRDOT.clustering;
                            return;
                        case 6: //minSlope
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].minSlope = defaultRDOT.minSlope;
                            return;
                        case 7: //maxSlope
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].maxSlope = defaultRDOT.maxSlope;
                            return;
                        case 8: //flags
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].flags = defaultRDOT.flags;
                            return;
                        case 9: //radiusWRTParent
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].radiusWRTParent = defaultRDOT.radiusWRTParent;
                            return;
                        case 10: //radius
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].radius = defaultRDOT.radius;
                            return;
                        case 11: //unk1
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[0] = defaultRDOT.unk1[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[1] = defaultRDOT.unk1[1];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[2] = defaultRDOT.unk1[2];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[3] = defaultRDOT.unk1[3];
                            return;
                        case 12: //maxHeight
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].maxHeight = defaultRDOT.maxHeight;
                            return;
                        case 13: //sink
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sink = defaultRDOT.sink;
                            return;
                        case 14: //sinkVar
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sinkVar = defaultRDOT.sinkVar;
                            return;
                        case 15: //sizeVar
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sizeVar = defaultRDOT.sizeVar;
                            return;
                        case 16: //angleVarX
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarX = defaultRDOT.angleVarX;
                            return;
                        case 17: //angleVarY
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarY = defaultRDOT.angleVarY;
                            return;
                        case 18: //angleVarZ
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarZ = defaultRDOT.angleVarZ;
                            return;
                        case 19: //unused2
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[0] = defaultRDOT.unused2[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[1] = defaultRDOT.unused2[1];
                            return;
                        case 20: //unk2
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[0] = defaultRDOT.unk2[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[1] = defaultRDOT.unk2[1];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[2] = defaultRDOT.unk2[2];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[3] = defaultRDOT.unk2[3];
                            return;
                        default:
                            return;
                        }
                    return;
                case 6: //mapName
                    Entries.value[ListIndex]->RDMP.Unload();
                    return;
                case 7: //iconPath
                    Entries.value[ListIndex]->ICON.Unload();
                    return;
                case 8: //grasses
                    if(ListX2FieldID == 0) //grasses
                        {
                        Entries.value[ListIndex]->RDGS.Unload();
                        return;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDGS.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //grass
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].grass = defaultRDGS.grass;
                            return;
                        case 2: //unk1
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[0] = defaultRDGS.unk1[0];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[1] = defaultRDGS.unk1[1];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[2] = defaultRDGS.unk1[2];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unk1[3] = defaultRDGS.unk1[3];
                            return;
                        default:
                            return;
                        }
                    return;
                case 9: //musicType
                    Entries.value[ListIndex]->RDMD.Unload();
                    return;
                case 10: //music
                    Entries.value[ListIndex]->RDMO.Unload();
                    return;
                case 11: //incidentalMedia
                    Entries.value[ListIndex]->RDSI.Unload();
                    return;
                case 12: //battleMedias
                    Entries.value[ListIndex]->RDSB.Unload();
                    return;
                case 13: //sounds
                    if(ListX2FieldID == 0) //sounds
                        {
                        Entries.value[ListIndex]->RDSD.Unload();
                        return;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDSD.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].sound = defaultRDSD.sound;
                            return;
                        case 2: //flags
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].flags = defaultRDSD.flags;
                            return;
                        case 3: //chance
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].chance = defaultRDSD.chance;
                            return;
                        default:
                            return;
                        }
                    return;
                case 14: //weathers
                    if(ListX2FieldID == 0) //weathers
                        {
                        Entries.value[ListIndex]->RDWT.Unload();
                        return;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDWT.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //weather
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].weather = defaultRDWT.weather;
                            return;
                        case 2: //chance
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].chance = defaultRDWT.chance;
                            return;
                        case 3: //globalId
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].globalId = defaultRDWT.globalId;
                            return;
                        default:
                            return;
                        }
                    return;
                case 15: //imposters
                    Entries.value[ListIndex]->RDWT.Unload();
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    return;
    }
}