# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#include "..\Common.h"
#include "..\Records\REGNRecord.h"

int REGNRecord::CreateListElement(const unsigned int subField)
    {
    REGNArea *curArea = NULL;
    REGNEntry *curEntry = NULL;
    switch(subField)
        {
        case 12: //areas
            curArea = new REGNArea;
            Areas.push_back(curArea);
            return (int)Areas.size() - 1;
        case 13: //entries
            curEntry = new REGNEntry;
            Entries.push_back(curEntry);
            return (int)Entries.size() - 1;
        default:
            return -1;
        }
    }

int REGNRecord::DeleteListElement(const unsigned int subField)
    {
    REGNArea *curArea = NULL;
    REGNEntry *curEntry = NULL;
    switch(subField)
        {
        case 12: //areas
            curArea = Areas.back();
            delete curArea;
            Areas.pop_back();
            return (int)Areas.size() - 1;
        case 13: //entries
            curEntry = Entries.back();
            delete curEntry;
            Entries.pop_back();
            return (int)Entries.size() - 1;
        default:
            return -1;
        }
    }

int REGNRecord::CreateListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    unsigned int listSize;
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return -1;
            switch(listField)
                {
                case 2: //points
                    listSize = (unsigned int)Areas[listIndex]->RPLD.size();
                    Areas[listIndex]->RPLD.resize(listSize + 1);
                    listSize++;
                    return (int)listSize - 1;
                default:
                    return -1;
                }
        case 13: //entries
            if(listIndex >= Entries.size())
                return -1;
            switch(listField)
                {
                case 5: //objects
                    listSize = (unsigned int)Entries[listIndex]->RDOT.size();
                    Entries[listIndex]->RDOT.resize(listSize + 1);
                    listSize++;
                    return (int)listSize - 1;
                case 8: //grasses
                    listSize = (unsigned int)Entries[listIndex]->RDGS.size();
                    Entries[listIndex]->RDGS.resize(listSize + 1);
                    listSize++;
                    return (int)listSize - 1;
                case 10: //sounds
                    listSize = (unsigned int)Entries[listIndex]->RDSD.size();
                    Entries[listIndex]->RDSD.resize(listSize + 1);
                    listSize++;
                    return (int)listSize - 1;
                case 11: //weathers
                    listSize = (unsigned int)Entries[listIndex]->RDWT.size();
                    Entries[listIndex]->RDWT.resize(listSize + 1);
                    listSize++;
                    return (int)listSize - 1;
                default:
                    return -1;
                }
        default:
            return -1;
        }
    }

int REGNRecord::DeleteListX2Element(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    unsigned int listSize = 0;
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return -1;
            switch(listField)
                {
                case 2: //points
                    listSize = (unsigned int)Areas[listIndex]->RPLD.size();
                    Areas[listIndex]->RPLD.pop_back();
                    listSize--;
                    return (int)listSize - 1;
                default:
                    return -1;
                }
        case 13: //entries
            if(listIndex >= Entries.size())
                return -1;
            switch(listField)
                {
                case 5: //objects
                    listSize = (unsigned int)Entries[listIndex]->RDOT.size();
                    Entries[listIndex]->RDOT.pop_back();
                    listSize--;
                    return (int)listSize - 1;
                case 8: //grasses
                    listSize = (unsigned int)Entries[listIndex]->RDGS.size();
                    Entries[listIndex]->RDGS.pop_back();
                    listSize--;
                    return (int)listSize - 1;
                case 10: //sounds
                    listSize = (unsigned int)Entries[listIndex]->RDSD.size();
                    Entries[listIndex]->RDSD.pop_back();
                    listSize--;
                    return (int)listSize - 1;
                case 11: //weathers
                    listSize = (unsigned int)Entries[listIndex]->RDWT.size();
                    Entries[listIndex]->RDWT.pop_back();
                    listSize--;
                    return (int)listSize - 1;
                default:
                    return -1;
                }
        default:
            return -1;
        }
    }

int REGNRecord::GetOtherFieldType(const unsigned int Field)
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

void * REGNRecord::GetOtherField(const unsigned int Field)
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

unsigned int REGNRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 10: //unused1
            return 1;
        default:
            return 0;
        }
    }

void REGNRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
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

int REGNRecord::GetListFieldType(const unsigned int subField, const unsigned int listField)
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

int REGNRecord::GetListX2FieldType(const unsigned int subField, const unsigned int listField, const unsigned int listX2Field)
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

unsigned int REGNRecord::GetListSize(const unsigned int Field)
    {
    switch(Field)
        {
        case 12: //areas
            return (unsigned int)Areas.size();
        case 13: //entries
            return (unsigned int)Entries.size();
        default:
            return 0;
        }
    }

unsigned int REGNRecord::GetListX2Size(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
    {
    switch(subField)
        {
        case 12: //areas
            if(listIndex >= Areas.size())
                return 0;
            switch(listField)
                {
                case 2: //points
                    return (unsigned int)Areas[listIndex]->RPLD.size();
                default:
                    return 0;
                }
        case 13: //entries
            if(listIndex >= Entries.size())
                return 0;
            switch(listField)
                {
                case 5: //objects
                    return (unsigned int)Entries[listIndex]->RDOT.size();
                case 8: //grasses
                    return (unsigned int)Entries[listIndex]->RDGS.size();
                case 10: //sounds
                    return (unsigned int)Entries[listIndex]->RDSD.size();
                case 11: //weathers
                    return (unsigned int)Entries[listIndex]->RDWT.size();
                default:
                    return 0;
                }
        default:
            return 0;
        }
    }

unsigned int REGNRecord::GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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

unsigned int REGNRecord::GetListX2ArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
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

void REGNRecord::GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues)
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

void REGNRecord::GetListX2Array(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, void **FieldValues)
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

void * REGNRecord::GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField)
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

void * REGNRecord::GetListX2Field(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field)
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

void REGNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
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

void REGNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue)
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

void REGNRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
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

void REGNRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 11: //worldspace
            WNAM.value.fid = FieldValue;
            FormIDHandler.AddMaster(WNAM.value.fid);
            break;
        default:
            return;
        }
    return;
    }

void REGNRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue)
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

void REGNRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue)
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

void REGNRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize)
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

void REGNRecord::SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue)
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

void REGNRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, float FieldValue)
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

void REGNRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned int FieldValue)
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
                            FormIDHandler.AddMaster(Entries[listIndex]->RDOT[listX2Index].objectId);
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
                            FormIDHandler.AddMaster(Entries[listIndex]->RDGS[listX2Index].grass);
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
                            FormIDHandler.AddMaster(Entries[listIndex]->RDSD[listX2Index].sound);
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
                            FormIDHandler.AddMaster(Entries[listIndex]->RDWT[listX2Index].weather);
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

void REGNRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned short FieldValue)
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

void REGNRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char *FieldValue, unsigned int nSize)
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

void REGNRecord::SetListX2Field(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, const unsigned listX2Index, const unsigned int listX2Field, unsigned char FieldValue)
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

