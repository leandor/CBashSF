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
#include "..\..\Common.h"
#include "..\REGNRecord.h"

signed long REGNRecord::CreateListElement(const unsigned long subField)
    {
    REGNArea *curArea = NULL;
    REGNEntry *curEntry = NULL;
    switch(subField)
        {
        case 12: //areas
            curArea = new REGNArea;
            Areas.push_back(curArea);
            return (signed long)Areas.size() - 1;
        case 13: //entries
            curEntry = new REGNEntry;
            Entries.push_back(curEntry);
            return (signed long)Entries.size() - 1;
        default:
            return -1;
        }
    }

signed long REGNRecord::DeleteListElement(const unsigned long subField)
    {
    REGNArea *curArea = NULL;
    REGNEntry *curEntry = NULL;
    switch(subField)
        {
        case 12: //areas
            curArea = Areas.back();
            delete curArea;
            Areas.pop_back();
            return (signed long)Areas.size() - 1;
        case 13: //entries
            curEntry = Entries.back();
            delete curEntry;
            Entries.pop_back();
            return (signed long)Entries.size() - 1;
        default:
            return -1;
        }
    }

signed long REGNRecord::CreateListX2Element(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    unsigned long listSize;
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return -1;
            switch(listField)
                {
                case 2: //points
                    listSize = (unsigned long)Areas[listIndex]->RPLD.size();
                    Areas[listIndex]->RPLD.resize(listSize + 1);
                    listSize++;
                    return (signed long)listSize - 1;
                default:
                    return -1;
                }
        case 13: //entries
            if(listIndex >= Entries.size())
                return -1;
            switch(listField)
                {
                case 5: //objects
                    listSize = (unsigned long)Entries[listIndex]->RDOT.size();
                    Entries[listIndex]->RDOT.resize(listSize + 1);
                    listSize++;
                    return (signed long)listSize - 1;
                case 8: //grasses
                    listSize = (unsigned long)Entries[listIndex]->RDGS.size();
                    Entries[listIndex]->RDGS.resize(listSize + 1);
                    listSize++;
                    return (signed long)listSize - 1;
                case 10: //sounds
                    listSize = (unsigned long)Entries[listIndex]->RDSD.size();
                    Entries[listIndex]->RDSD.resize(listSize + 1);
                    listSize++;
                    return (signed long)listSize - 1;
                case 11: //weathers
                    listSize = (unsigned long)Entries[listIndex]->RDWT.size();
                    Entries[listIndex]->RDWT.resize(listSize + 1);
                    listSize++;
                    return (signed long)listSize - 1;
                default:
                    return -1;
                }
        default:
            return -1;
        }
    }

signed long REGNRecord::DeleteListX2Element(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    unsigned long listSize = 0;
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return -1;
            switch(listField)
                {
                case 2: //points
                    listSize = (unsigned long)Areas[listIndex]->RPLD.size();
                    Areas[listIndex]->RPLD.pop_back();
                    listSize--;
                    return (signed long)listSize - 1;
                default:
                    return -1;
                }
        case 13: //entries
            if(listIndex >= Entries.size())
                return -1;
            switch(listField)
                {
                case 5: //objects
                    listSize = (unsigned long)Entries[listIndex]->RDOT.size();
                    Entries[listIndex]->RDOT.pop_back();
                    listSize--;
                    return (signed long)listSize - 1;
                case 8: //grasses
                    listSize = (unsigned long)Entries[listIndex]->RDGS.size();
                    Entries[listIndex]->RDGS.pop_back();
                    listSize--;
                    return (signed long)listSize - 1;
                case 10: //sounds
                    listSize = (unsigned long)Entries[listIndex]->RDSD.size();
                    Entries[listIndex]->RDSD.pop_back();
                    listSize--;
                    return (signed long)listSize - 1;
                case 11: //weathers
                    listSize = (unsigned long)Entries[listIndex]->RDWT.size();
                    Entries[listIndex]->RDWT.pop_back();
                    listSize--;
                    return (signed long)listSize - 1;
                default:
                    return -1;
                }
        default:
            return -1;
        }
    }

signed long REGNRecord::GetOtherFieldType(const unsigned long Field)
    {
    switch(Field)
        {
        case 6: //iconPath
            return STRING_FIELD;
        case 7: //mapRed
            return UBYTE_FIELD;
        case 8: //mapGreen
            return UBYTE_FIELD;
        case 9: //mapBlue
            return UBYTE_FIELD;
        case 10: //unused1
            return BYTES_FIELD;
        case 11: //worldspace
            return FID_FIELD;
        case 12: //areas
            return LIST_FIELD;
        case 13: //entries
            return LIST_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * REGNRecord::GetOtherField(const unsigned long Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //iconPath
            return ICON.value;
        case 7: //mapRed
            return &RCLR.value.red;
        case 8: //mapGreen
            return &RCLR.value.green;
        case 9: //mapBlue
            return &RCLR.value.blue;
        case 11: //worldspace
            return &WNAM.value.fid;
        default:
            return NULL;
        }
    }

unsigned long REGNRecord::GetFieldArraySize(const unsigned long Field)
    {
    switch(Field)
        {
        case 10: //unused1
            return 1;
        default:
            return 0;
        }
    }

void REGNRecord::GetFieldArray(const unsigned long Field, void **FieldValues)
    {
    switch(Field)
        {
        case 10: //unused1
            *FieldValues = &RCLR.value.unused1;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

signed long REGNRecord::GetListFieldType(const unsigned long subField, const unsigned long listField)
    {
    switch(subField)
        {
        case 12: //areas
            switch(listField)
                {
                case 1: //edgeFalloff
                    return FID_FIELD;
                case 2: //points
                    return LIST_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //entries
            switch(listField)
                {
                case 1: //entryType
                    return UINT_FIELD;
                case 2: //flags
                    return UBYTE_FIELD;
                case 3: //priority
                    return UBYTE_FIELD;
                case 4: //unused1
                    return BYTES_FIELD;
                case 5: //objects
                    return LIST_FIELD;
                case 6: //mapName
                    return STRING_FIELD;
                case 7: //iconPath
                    return STRING_FIELD;
                case 8: //grasses
                    return LIST_FIELD;
                case 9: //musicType
                    return UINT_FIELD;
                case 10: //sounds
                    return LIST_FIELD;
                case 11: //weathers
                    return LIST_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

signed long REGNRecord::GetListX2FieldType(const unsigned long subField, const unsigned long listField, const unsigned long listX2Field)
    {
    switch(subField)
        {
        case 12: //areas
            switch(listField)
                {
                case 2: //points
                    switch(listX2Field)
                        {
                        case 1: //posX
                            return FLOAT_FIELD;
                        case 2: //posY
                            return FLOAT_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //entries
            switch(listField)
                {
                case 5: //objects
                    switch(listX2Field)
                        {
                        case 1: //objectId
                            return FID_FIELD;
                        case 2: //parentIndex
                            return USHORT_FIELD;
                        case 3: //unused1
                            return BYTES_FIELD;
                        case 4: //density
                            return FLOAT_FIELD;
                        case 5: //clustering
                            return UBYTE_FIELD;
                        case 6: //minSlope
                            return UBYTE_FIELD;
                        case 7: //maxSlope
                            return UBYTE_FIELD;
                        case 8: //flags
                            return UBYTE_FIELD;
                        case 9: //radiusWRTParent
                            return USHORT_FIELD;
                        case 10: //radius
                            return USHORT_FIELD;
                        case 11: //unk1
                            return BYTES_FIELD;
                        case 12: //maxHeight
                            return FLOAT_FIELD;
                        case 13: //sink
                            return FLOAT_FIELD;
                        case 14: //sinkVar
                            return FLOAT_FIELD;
                        case 15: //sizeVar
                            return FLOAT_FIELD;
                        case 16: //angleVarX
                            return USHORT_FIELD;
                        case 17: //angleVarY
                            return USHORT_FIELD;
                        case 18: //angleVarZ
                            return USHORT_FIELD;
                        case 19: //unused2
                            return BYTES_FIELD;
                        case 20: //unk2
                            return BYTES_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 8: //grasses
                    switch(listX2Field)
                        {
                        case 1: //grass
                            return FID_FIELD;
                        case 2: //unk1
                            return BYTES_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 10: //sounds
                    switch(listX2Field)
                        {
                        case 1: //sound
                            return FID_FIELD;
                        case 2: //flags
                            return UINT_FIELD;
                        case 3: //chance
                            return UINT_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                case 11: //weathers
                    switch(listX2Field)
                        {
                        case 1: //weather
                            return FID_FIELD;
                        case 2: //chance
                            return UINT_FIELD;
                        default:
                            return UNKNOWN_FIELD;
                        }
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

unsigned long REGNRecord::GetListSize(const unsigned long Field)
    {
    switch(Field)
        {
        case 12: //areas
            return (unsigned long)Areas.size();
        case 13: //entries
            return (unsigned long)Entries.size();
        default:
            return 0;
        }
    }

unsigned long REGNRecord::GetListX2Size(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return 0;
            switch(listField)
                {
                case 2: //points
                    return (unsigned long)Areas[listIndex]->RPLD.size();
                default:
                    return 0;
                }
        case 13: //entries
            if(listIndex >= Entries.size())
                return 0;
            switch(listField)
                {
                case 5: //objects
                    return (unsigned long)Entries[listIndex]->RDOT.size();
                case 8: //grasses
                    return (unsigned long)Entries[listIndex]->RDGS.size();
                case 10: //sounds
                    return (unsigned long)Entries[listIndex]->RDSD.size();
                case 11: //weathers
                    return (unsigned long)Entries[listIndex]->RDWT.size();
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned long REGNRecord::GetListArraySize(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    switch(subField)
        {
        case 13: //entries
            switch(listField)
                {
                case 4: //unused1
                    return 2;
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned long REGNRecord::GetListX2ArraySize(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    switch(subField)
        {
        case 13: //entries
            switch(listField)
                {
                case 5: //objects
                    switch(listX2Field)
                        {
                        case 3: //unused1
                            return 2;
                        case 11: //unk1
                            return 4;
                        case 19: //unused2
                            return 2;
                        case 20: //unk2
                            return 4;
                        default:
                            return 0;
                        }
                case 8: //grasses
                    switch(listX2Field)
                        {
                        case 2: //unk1
                            return 4;
                        default:
                            return 0;
                        }
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

void REGNRecord::GetListArray(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues)
    {
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 4: //unused1
                    *FieldValues = &Entries[listIndex]->RDAT.value.unused1[0];
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

void REGNRecord::GetListX2Array(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, void **FieldValues)
    {
    //printf("get, subField:%u, listIndex:%u, listField:%u, listX2Index:%u, listX2Field:%u\n", subField, listIndex, listField, listX2Index, listX2Field);
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                {
                *FieldValues = NULL;
                return;
                }
            switch(listField)
                {
                case 5: //objects
                    if(listX2Index >= Entries[listIndex]->RDOT.size())
                        {
                        *FieldValues = NULL;
                        return;
                        }
                    switch(listX2Field)
                        {
                        case 3: //unused1
                            *FieldValues = &Entries[listIndex]->RDOT[listX2Index].unused1[0];
                            return;
                        case 11: //unk1
                            *FieldValues = &Entries[listIndex]->RDOT[listX2Index].unk1[0];
                            return;
                        case 19: //unused2
                            *FieldValues = &Entries[listIndex]->RDOT[listX2Index].unused2[0];
                            return;
                        case 20: //unk2
                            *FieldValues = &Entries[listIndex]->RDOT[listX2Index].unk2[0];
                            return;
                        default:
                            *FieldValues = NULL;
                            return;
                        }
                case 8: //grasses
                    if(listX2Index >= Entries[listIndex]->RDGS.size())
                        {
                        *FieldValues = NULL;
                        return;
                        }
                    switch(listX2Field)
                        {
                        case 2: //unk1
                            *FieldValues = &Entries[listIndex]->RDGS[listX2Index].unk1[0];
                            return;
                        default:
                            *FieldValues = NULL;
                            return;
                        }
                default:
                    *FieldValues = NULL;
                    return;
                }
        default:
            *FieldValues = NULL;
            return;
        }
    }

void * REGNRecord::GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return NULL;
            switch(listField)
                {
                case 1: //edgeFalloff
                    return &Areas[listIndex]->RPLI.value.edgeFalloff;
                default:
                    return NULL;
                }
        case 13: //entries
            if(listIndex >= Entries.size())
                return NULL;
            switch(listField)
                {
                case 1: //entryType
                    return &Entries[listIndex]->RDAT.value.entryType;
                case 2: //flags
                    return &Entries[listIndex]->RDAT.value.flags;
                case 3: //priority
                    return &Entries[listIndex]->RDAT.value.priority;
                case 6: //mapName
                    return Entries[listIndex]->RDMP.value;
                case 7: //iconPath
                    return Entries[listIndex]->ICON.value;
                case 9: //musicType
                    if(Entries[listIndex]->RDMD.IsLoaded())
                        return &Entries[listIndex]->RDMD->type;
                    return NULL;
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void * REGNRecord::GetListX2Field(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return NULL;
            switch(listField)
                {
                case 2: //points
                    if(listX2Index >= Areas[listIndex]->RPLD.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 1: //posX
                            return &Areas[listIndex]->RPLD[listX2Index].posX;
                        case 2: //posY
                            return &Areas[listIndex]->RPLD[listX2Index].posY;
                        default:
                            return NULL;
                        }
                default:
                    return NULL;
                }
        case 13: //entries
            if(listIndex >= Entries.size())
                return NULL;
            switch(listField)
                {
                case 5: //objects
                    if(listX2Index >= Entries[listIndex]->RDOT.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 1: //objectId
                            return &Entries[listIndex]->RDOT[listX2Index].objectId;
                        case 2: //parentIndex
                            return &Entries[listIndex]->RDOT[listX2Index].parentIndex;
                        case 4: //density
                            return &Entries[listIndex]->RDOT[listX2Index].density;
                        case 5: //clustering
                            return &Entries[listIndex]->RDOT[listX2Index].clustering;
                        case 6: //minSlope
                            return &Entries[listIndex]->RDOT[listX2Index].minSlope;
                        case 7: //maxSlope
                            return &Entries[listIndex]->RDOT[listX2Index].maxSlope;
                        case 8: //flags
                            return &Entries[listIndex]->RDOT[listX2Index].flags;
                        case 9: //radiusWRTParent
                            return &Entries[listIndex]->RDOT[listX2Index].radiusWRTParent;
                        case 10: //radius
                            return &Entries[listIndex]->RDOT[listX2Index].radius;
                        case 12: //maxHeight
                            return &Entries[listIndex]->RDOT[listX2Index].maxHeight;
                        case 13: //sink
                            return &Entries[listIndex]->RDOT[listX2Index].sink;
                        case 14: //sinkVar
                            return &Entries[listIndex]->RDOT[listX2Index].sinkVar;
                        case 15: //sizeVar
                            return &Entries[listIndex]->RDOT[listX2Index].sizeVar;
                        case 16: //angleVarX
                            return &Entries[listIndex]->RDOT[listX2Index].angleVarX;
                        case 17: //angleVarY
                            return &Entries[listIndex]->RDOT[listX2Index].angleVarY;
                        case 18: //angleVarZ
                            return &Entries[listIndex]->RDOT[listX2Index].angleVarZ;
                        default:
                            return NULL;
                        }
                case 8: //grasses
                    if(listX2Index >= Entries[listIndex]->RDGS.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 1: //grass
                            return &Entries[listIndex]->RDGS[listX2Index].grass;
                        default:
                            return NULL;
                        }
                case 10: //sounds
                    if(listX2Index >= Entries[listIndex]->RDSD.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 1: //sound
                            return &Entries[listIndex]->RDSD[listX2Index].sound;
                        case 2: //flags
                            return &Entries[listIndex]->RDSD[listX2Index].flags;
                        case 3: //chance
                            return &Entries[listIndex]->RDSD[listX2Index].chance;
                        default:
                            return NULL;
                        }
                case 11: //weathers
                    if(listX2Index >= Entries[listIndex]->RDWT.size())
                        return NULL;
                    switch(listX2Field)
                        {
                        case 1: //weather
                            return &Entries[listIndex]->RDWT[listX2Index].weather;
                        case 2: //chance
                            return &Entries[listIndex]->RDWT[listX2Index].chance;
                        default:
                            return NULL;
                        }
                default:
                    return NULL;
                }
        default:
            return NULL;
        }
    }

void REGNRecord::SetField(const unsigned long Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //iconPath
            ICON.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void REGNRecord::SetField(const unsigned long Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 7: //mapRed
            RCLR.value.red = FieldValue;
        case 8: //mapGreen
            RCLR.value.green = FieldValue;
            break;
        case 9: //mapBlue
            RCLR.value.blue = FieldValue;
        default:
            return;
        }
    return;
    }

void REGNRecord::SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize)
    {
    switch(Field)
        {
        case 10: //unused1
            if(nSize != 1)
                return;
            RCLR.value.unused1 = FieldValue[0];
            break;
        default:
            return;
        }
    return;
    }

void REGNRecord::SetOtherField(const unsigned long Field, unsigned long FieldValue)
    {
    switch(Field)
        {
        case 11: //worldspace
            WNAM.value.fid = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void REGNRecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue)
    {
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return;
            switch(listField)
                {
                case 1: //edgeFalloff
                    Areas[listIndex]->RPLI.value.edgeFalloff = FieldValue;
                    break;
                default:
                    return;
                }
            break;
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 1: //entryType
                    Entries[listIndex]->RDAT.value.entryType = FieldValue;
                    break;
                case 9: //musicType
                    Entries[listIndex]->RDMD.Load();
                    Entries[listIndex]->RDMD->type = FieldValue;
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

void REGNRecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 2: //flags
                    Entries[listIndex]->RDAT.value.flags = FieldValue;
                    break;
                case 3: //priority
                    Entries[listIndex]->RDAT.value.priority = FieldValue;
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

void REGNRecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize)
    {
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 4: //unused1
                    if(nSize != 2)
                        return;
                    Entries[listIndex]->RDAT.value.unused1[0] = FieldValue[0];
                    Entries[listIndex]->RDAT.value.unused1[1] = FieldValue[1];
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

void REGNRecord::SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, char *FieldValue)
    {
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 6: //mapName
                    Entries[listIndex]->RDMP.Copy(FieldValue);
                    break;
                case 7: //iconPath
                    Entries[listIndex]->ICON.Copy(FieldValue);
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

void REGNRecord::SetListX2Field(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, float FieldValue)
    {
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return;
            switch(listField)
                {
                case 2: //points
                    if(listX2Index >= Areas[listIndex]->RPLD.size())
                        return;
                    switch(listX2Field)
                        {
                        case 1: //posX
                            Areas[listIndex]->RPLD[listX2Index].posX = FieldValue;
                            break;
                        case 2: //posY
                            Areas[listIndex]->RPLD[listX2Index].posY = FieldValue;
                            break;
                        default:
                            return;
                        }
                    break;
                default:
                    return;
                }
            break;
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 5: //objects
                    if(listX2Index >= Entries[listIndex]->RDOT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 4: //density
                            Entries[listIndex]->RDOT[listX2Index].density = FieldValue;
                            break;
                        case 12: //maxHeight
                            Entries[listIndex]->RDOT[listX2Index].maxHeight = FieldValue;
                            break;
                        case 13: //sink
                            Entries[listIndex]->RDOT[listX2Index].sink = FieldValue;
                            break;
                        case 14: //sinkVar
                            Entries[listIndex]->RDOT[listX2Index].sinkVar = FieldValue;
                            break;
                        case 15: //sizeVar
                            Entries[listIndex]->RDOT[listX2Index].sizeVar = FieldValue;
                            break;
                        default:
                            return;
                        }
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    }

void REGNRecord::SetListX2Field(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned long FieldValue)
    {
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 5: //objects
                    if(listX2Index >= Entries[listIndex]->RDOT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 1: //objectId
                            Entries[listIndex]->RDOT[listX2Index].objectId = FieldValue;
                            break;
                        default:
                            return;
                        }
                    break;
                case 8: //grasses
                    if(listX2Index >= Entries[listIndex]->RDGS.size())
                        return;
                    switch(listX2Field)
                        {
                        case 1: //grass
                            Entries[listIndex]->RDGS[listX2Index].grass = FieldValue;
                            break;
                        default:
                            return;
                        }
                case 10: //sounds
                    if(listX2Index >= Entries[listIndex]->RDSD.size())
                        return;
                    switch(listX2Field)
                        {
                        case 1: //sound
                            Entries[listIndex]->RDSD[listX2Index].sound = FieldValue;
                            break;
                        case 2: //flags
                            Entries[listIndex]->RDSD[listX2Index].flags = FieldValue;
                            break;
                        case 3: //chance
                            Entries[listIndex]->RDSD[listX2Index].chance = FieldValue;
                            break;
                        default:
                            return;
                        }
                case 11: //weathers
                    if(listX2Index >= Entries[listIndex]->RDWT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 1: //weather
                            Entries[listIndex]->RDWT[listX2Index].weather = FieldValue;
                            break;
                        case 2: //chance
                            Entries[listIndex]->RDWT[listX2Index].chance = FieldValue;
                            break;
                        default:
                            return;
                        }
                default:
                    return;
                }
            break;
        default:
            return;
        }
    }

void REGNRecord::SetListX2Field(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned short FieldValue)
    {
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 5: //objects
                    if(listX2Index >= Entries[listIndex]->RDOT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 2: //parentIndex
                            Entries[listIndex]->RDOT[listX2Index].parentIndex = FieldValue;
                            break;
                        case 9: //radiusWRTParent
                            Entries[listIndex]->RDOT[listX2Index].radiusWRTParent = FieldValue;
                            break;
                        case 10: //radius
                            Entries[listIndex]->RDOT[listX2Index].radius = FieldValue;
                            break;
                        case 16: //angleVarX
                            Entries[listIndex]->RDOT[listX2Index].angleVarX = FieldValue;
                            break;
                        case 17: //angleVarY
                            Entries[listIndex]->RDOT[listX2Index].angleVarY = FieldValue;
                            break;
                        case 18: //angleVarZ
                            Entries[listIndex]->RDOT[listX2Index].angleVarZ = FieldValue;
                            break;
                        default:
                            return;
                        }
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    }

void REGNRecord::SetListX2Field(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned char *FieldValue, unsigned long nSize)
    {
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 5: //objects
                    if(listX2Index >= Entries[listIndex]->RDOT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 3: //unused1
                            if(nSize != 2)
                                return;
                            Entries[listIndex]->RDOT[listX2Index].unused1[0] = FieldValue[0];
                            Entries[listIndex]->RDOT[listX2Index].unused1[1] = FieldValue[1];
                            break;
                        case 11: //unk1
                            if(nSize != 4)
                                return;
                            Entries[listIndex]->RDOT[listX2Index].unk1[0] = FieldValue[0];
                            Entries[listIndex]->RDOT[listX2Index].unk1[1] = FieldValue[1];
                            Entries[listIndex]->RDOT[listX2Index].unk1[2] = FieldValue[2];
                            Entries[listIndex]->RDOT[listX2Index].unk1[3] = FieldValue[3];
                            break;
                        case 19: //unused2
                            if(nSize != 2)
                                return;
                            Entries[listIndex]->RDOT[listX2Index].unused2[0] = FieldValue[0];
                            Entries[listIndex]->RDOT[listX2Index].unused2[1] = FieldValue[1];
                            break;
                        case 20: //unk2
                            if(nSize != 4)
                                return;
                            Entries[listIndex]->RDOT[listX2Index].unk2[0] = FieldValue[0];
                            Entries[listIndex]->RDOT[listX2Index].unk2[1] = FieldValue[1];
                            Entries[listIndex]->RDOT[listX2Index].unk2[2] = FieldValue[2];
                            Entries[listIndex]->RDOT[listX2Index].unk2[3] = FieldValue[3];
                            break;
                        default:
                            return;
                        }
                    break;
                case 8: //grasses
                    if(listX2Index >= Entries[listIndex]->RDGS.size())
                        return;
                    switch(listX2Field)
                        {
                        case 2: //unk1
                            if(nSize != 4)
                                return;
                            Entries[listIndex]->RDGS[listX2Index].unk1[0] = FieldValue[0];
                            Entries[listIndex]->RDGS[listX2Index].unk1[1] = FieldValue[1];
                            Entries[listIndex]->RDGS[listX2Index].unk1[2] = FieldValue[2];
                            Entries[listIndex]->RDGS[listX2Index].unk1[3] = FieldValue[3];
                        default:
                            return;
                        }
                default:
                    return;
                }
            break;
        default:
            return;
        }
    }

void REGNRecord::SetListX2Field(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field, unsigned char FieldValue)
    {
    switch(subField)
        {
        case 13: //entries
            if(listIndex >= Entries.size())
                return;
            switch(listField)
                {
                case 5: //objects
                    if(listX2Index >= Entries[listIndex]->RDOT.size())
                        return;
                    switch(listX2Field)
                        {
                        case 5: //clustering
                            Entries[listIndex]->RDOT[listX2Index].clustering = FieldValue;
                            break;
                        case 6: //minSlope
                            Entries[listIndex]->RDOT[listX2Index].minSlope = FieldValue;
                            break;
                        case 7: //maxSlope
                            Entries[listIndex]->RDOT[listX2Index].maxSlope = FieldValue;
                            break;
                        case 8: //flags
                            Entries[listIndex]->RDOT[listX2Index].flags = FieldValue;
                            break;
                        default:
                            return;
                        }
                    break;
                default:
                    return;
                }
            break;
        default:
            return;
        }
    }

signed long REGNRecord::DeleteField(const unsigned long Field)
    {
    GENCLR defaultCLR;
    unsigned long nSize;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //iconPath
            ICON.Unload();
            break;
        case 7: //mapRed
            RCLR.value.red = defaultCLR.red;
            break;
        case 8: //mapGreen
            RCLR.value.green = defaultCLR.green;
            break;
        case 9: //mapBlue
            RCLR.value.blue = defaultCLR.blue;
            break;
        case 10: //unused1
            RCLR.value.unused1 = defaultCLR.unused1;
            break;
        case 11: //worldspace
            WNAM.Unload();
            break;
        case 12: //areas
            nSize = (unsigned long)Areas.size();
            for(unsigned long x = 0; x < nSize; x++)
                delete Areas[x];
            Areas.clear();
            break;
        case 13: //entries
            nSize = (unsigned long)Entries.size();
            for(unsigned long x = 0; x < nSize; x++)
                delete Entries[x];
            Entries.clear();
            break;
        default:
            return 0;
        }
    return 1;
    }

signed long REGNRecord::DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField)
    {
    REGNRDAT defaultRDAT;
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return 0;
            switch(listField)
                {
                case 1: //edgeFalloff
                    Areas[listIndex]->RPLI.Unload();
                    break;
                case 2: //points
                    Areas[listIndex]->RPLD.clear();
                    break;
                default:
                    return 0;
                }
            break;
        case 13: //entries
            if(listIndex >= Entries.size())
                return 0;
            switch(listField)
                {
                case 1: //entryType
                    Entries[listIndex]->RDAT.value.entryType = defaultRDAT.entryType;
                    break;
                case 2: //flags
                    Entries[listIndex]->RDAT.value.flags = defaultRDAT.flags;
                    break;
                case 3: //priority
                    Entries[listIndex]->RDAT.value.priority = defaultRDAT.priority;
                    break;
                case 4: //unused1
                    Entries[listIndex]->RDAT.value.unused1[0] = defaultRDAT.unused1[0];
                    Entries[listIndex]->RDAT.value.unused1[1] = defaultRDAT.unused1[1];
                    break;
                case 5: //objects
                    Entries[listIndex]->RDOT.clear();
                    break;
                case 6: //mapName
                    Entries[listIndex]->RDMP.Unload();
                    break;
                case 7: //iconPath
                    Entries[listIndex]->ICON.Unload();
                    break;
                case 8: //grasses
                    Entries[listIndex]->RDGS.clear();
                    break;
                case 9: //musicType
                    Entries[listIndex]->RDMD.Unload();
                    break;
                case 10: //sounds
                    Entries[listIndex]->RDSD.clear();
                    break;
                case 11: //weathers
                    Entries[listIndex]->RDWT.clear();
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

signed long REGNRecord::DeleteListX2Field(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, const unsigned long listX2Index, const unsigned long listX2Field)
    {
    REGNRPLD defaultRPLD;
    REGNRDOT defaultRDOT;
    REGNRDGS defaultRDGS;
    REGNRDSD defaultRDSD;
    REGNRDWT defaultRDWT;
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return 0;
            switch(listField)
                {
                case 2: //points
                    if(listX2Index >= Areas[listIndex]->RPLD.size())
                        return 0;
                    switch(listX2Field)
                        {
                        case 1: //posX
                            Areas[listIndex]->RPLD[listX2Index].posX = defaultRPLD.posX;
                            break;
                        case 2: //posY
                            Areas[listIndex]->RPLD[listX2Index].posY = defaultRPLD.posY;
                            break;
                        default:
                            return 0;
                        }
                    break;
                default:
                    return 0;
                }
            break;
        case 13: //entries
            if(listIndex >= Entries.size())
                return 0;
            switch(listField)
                {
                case 5: //objects
                    if(listX2Index >= Entries[listIndex]->RDOT.size())
                        return 0;
                    switch(listX2Field)
                        {
                        case 1: //objectId
                            Entries[listIndex]->RDOT[listX2Index].objectId = defaultRDOT.objectId;
                            break;
                        case 2: //parentIndex
                            Entries[listIndex]->RDOT[listX2Index].parentIndex = defaultRDOT.parentIndex;
                            break;
                        case 3: //unused1
                            Entries[listIndex]->RDOT[listX2Index].unused1[0] = defaultRDOT.unused1[0];
                            Entries[listIndex]->RDOT[listX2Index].unused1[1] = defaultRDOT.unused1[1];
                            break;
                        case 4: //density
                            Entries[listIndex]->RDOT[listX2Index].density = defaultRDOT.density;
                            break;
                        case 5: //clustering
                            Entries[listIndex]->RDOT[listX2Index].clustering = defaultRDOT.clustering;
                            break;
                        case 6: //minSlope
                            Entries[listIndex]->RDOT[listX2Index].minSlope = defaultRDOT.minSlope;
                            break;
                        case 7: //maxSlope
                            Entries[listIndex]->RDOT[listX2Index].maxSlope = defaultRDOT.maxSlope;
                            break;
                        case 8: //flags
                            Entries[listIndex]->RDOT[listX2Index].flags = defaultRDOT.flags;
                            break;
                        case 9: //radiusWRTParent
                            Entries[listIndex]->RDOT[listX2Index].radiusWRTParent = defaultRDOT.radiusWRTParent;
                            break;
                        case 10: //radius
                            Entries[listIndex]->RDOT[listX2Index].radius = defaultRDOT.radius;
                            break;
                        case 11: //unk1
                            Entries[listIndex]->RDOT[listX2Index].unk1[0] = defaultRDOT.unk1[0];
                            Entries[listIndex]->RDOT[listX2Index].unk1[1] = defaultRDOT.unk1[1];
                            Entries[listIndex]->RDOT[listX2Index].unk1[2] = defaultRDOT.unk1[2];
                            Entries[listIndex]->RDOT[listX2Index].unk1[3] = defaultRDOT.unk1[3];
                            break;
                        case 12: //maxHeight
                            Entries[listIndex]->RDOT[listX2Index].maxHeight = defaultRDOT.maxHeight;
                            break;
                        case 13: //sink
                            Entries[listIndex]->RDOT[listX2Index].sink = defaultRDOT.sink;
                            break;
                        case 14: //sinkVar
                            Entries[listIndex]->RDOT[listX2Index].sinkVar = defaultRDOT.sinkVar;
                            break;
                        case 15: //sizeVar
                            Entries[listIndex]->RDOT[listX2Index].sizeVar = defaultRDOT.sizeVar;
                            break;
                        case 16: //angleVarX
                            Entries[listIndex]->RDOT[listX2Index].angleVarX = defaultRDOT.angleVarX;
                            break;
                        case 17: //angleVarY
                            Entries[listIndex]->RDOT[listX2Index].angleVarY = defaultRDOT.angleVarY;
                            break;
                        case 18: //angleVarZ
                            Entries[listIndex]->RDOT[listX2Index].angleVarZ = defaultRDOT.angleVarZ;
                            break;
                        case 19: //unused2
                            Entries[listIndex]->RDOT[listX2Index].unused2[0] = defaultRDOT.unused2[0];
                            Entries[listIndex]->RDOT[listX2Index].unused2[1] = defaultRDOT.unused2[1];
                            break;
                        case 20: //unk2
                            Entries[listIndex]->RDOT[listX2Index].unk2[0] = defaultRDOT.unk2[0];
                            Entries[listIndex]->RDOT[listX2Index].unk2[1] = defaultRDOT.unk2[1];
                            Entries[listIndex]->RDOT[listX2Index].unk2[2] = defaultRDOT.unk2[2];
                            Entries[listIndex]->RDOT[listX2Index].unk2[3] = defaultRDOT.unk2[3];
                            break;
                        default:
                            return 0;
                        }
                    break;
                case 8: //grasses
                    if(listX2Index >= Entries[listIndex]->RDGS.size())
                        return 0;
                    switch(listX2Field)
                        {
                        case 1: //grass
                            Entries[listIndex]->RDGS[listX2Index].grass = defaultRDGS.grass;
                            break;
                        case 2: //unk1
                            Entries[listIndex]->RDGS[listX2Index].unk1[0] = defaultRDGS.unk1[0];
                            Entries[listIndex]->RDGS[listX2Index].unk1[1] = defaultRDGS.unk1[1];
                            Entries[listIndex]->RDGS[listX2Index].unk1[2] = defaultRDGS.unk1[2];
                            Entries[listIndex]->RDGS[listX2Index].unk1[3] = defaultRDGS.unk1[3];
                            break;
                        default:
                            return 0;
                        }
                    break;
                case 10: //sounds
                    if(listX2Index >= Entries[listIndex]->RDSD.size())
                        return 0;
                    switch(listX2Field)
                        {
                        case 1: //sound
                            Entries[listIndex]->RDSD[listX2Index].sound = defaultRDSD.sound;
                            break;
                        case 2: //flags
                            Entries[listIndex]->RDSD[listX2Index].flags = defaultRDSD.flags;
                            break;
                        case 3: //chance
                            Entries[listIndex]->RDSD[listX2Index].chance = defaultRDSD.chance;
                            break;
                        default:
                            return 0;
                        }
                    break;
                case 11: //weathers
                    if(listX2Index >= Entries[listIndex]->RDWT.size())
                        return 0;
                    switch(listX2Field)
                        {
                        case 1: //weather
                            Entries[listIndex]->RDWT[listX2Index].weather = defaultRDWT.weather;
                            break;
                        case 2: //chance
                            Entries[listIndex]->RDWT[listX2Index].chance = defaultRDWT.chance;
                            break;
                        default:
                            return 0;
                        }
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
