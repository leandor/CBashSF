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
#include "..\NAVIRecord.h"

namespace FNV
{
UINT32 NAVIRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //version
            return UINT32_FIELD;
        case 8: //NVMI
            if(ListFieldID == 0) //NVMI
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)NVMI.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= NVMI.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //unknown1
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
                case 2: //mesh
                    return FORMID_FIELD;
                case 3: //location
                    return FORMID_FIELD;
                case 4: //xGrid
                    return SINT16_FIELD;
                case 5: //yGrid
                    return SINT16_FIELD;
                case 6: //unknown2_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return NVMI.value[ListIndex]->unknown2Size;
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 9: //NVCI
            if(ListFieldID == 0) //NVCI
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)NVCI.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                return UNKNOWN_FIELD;
                }

            if(ListIndex >= NVCI.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    return FORMID_FIELD;
                case 2: //unknown2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_ARRAY_FIELD;
                        case 1: //fieldSize
                            return (UINT32)NVCI.value[ListIndex]->unknown2.size();
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                case 3: //unknown3
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_ARRAY_FIELD;
                        case 1: //fieldSize
                            return (UINT32)NVCI.value[ListIndex]->unknown3.size();
                        default:
                            return UNKNOWN_FIELD;
                        }
                    return UNKNOWN_FIELD;
                case 4: //doors
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return FORMID_ARRAY_FIELD;
                        case 1: //fieldSize
                            return (UINT32)NVCI.value[ListIndex]->doors.size();
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

void * NAVIRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //version
            return &NVER.value;
        case 8: //NVMI
            if(ListIndex >= NVMI.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    *FieldValues = &NVMI.value[ListIndex]->unknown1[0];
                    return NULL;
                case 2: //mesh
                    return &NVMI.value[ListIndex]->mesh;
                case 3: //location
                    return &NVMI.value[ListIndex]->location;
                case 4: //xGrid
                    return &NVMI.value[ListIndex]->xGrid;
                case 5: //yGrid
                    return &NVMI.value[ListIndex]->yGrid;
                case 6: //unknown2_p
                    *FieldValues = NVMI.value[ListIndex]->unknown2;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 9: //NVCI
            if(ListIndex >= NVCI.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    return &NVCI.value[ListIndex]->unknown1;
                case 2: //unknown2
                    *FieldValues = NVCI.value[ListIndex]->unknown2.size() ? &NVCI.value[ListIndex]->unknown2[0] : NULL;
                    return NULL;
                case 3: //unknown3
                    *FieldValues = NVCI.value[ListIndex]->unknown2.size() ? &NVCI.value[ListIndex]->unknown3[0] : NULL;
                    return NULL;
                case 4: //doors
                    *FieldValues = NVCI.value[ListIndex]->unknown2.size() ? &NVCI.value[ListIndex]->doors[0] : NULL;
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

bool NAVIRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //version
            NVER.value = *(UINT32 *)FieldValue;
            break;
        case 8: //NVMI
            if(ListFieldID == 0) //NVMISize
                {
                NVMI.resize(ArraySize);
                return false;
                }

            if(ListIndex >= NVMI.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    if(ArraySize != 4)
                        break;
                    NVMI.value[ListIndex]->unknown1[0] = ((UINT8ARRAY)FieldValue)[0];
                    NVMI.value[ListIndex]->unknown1[1] = ((UINT8ARRAY)FieldValue)[1];
                    NVMI.value[ListIndex]->unknown1[2] = ((UINT8ARRAY)FieldValue)[2];
                    NVMI.value[ListIndex]->unknown1[3] = ((UINT8ARRAY)FieldValue)[3];
                    break;
                case 2: //mesh
                    NVMI.value[ListIndex]->mesh = *(FORMID *)FieldValue;
                    return true;
                case 3: //location
                    NVMI.value[ListIndex]->location = *(FORMID *)FieldValue;
                    return true;
                case 4: //xGrid
                    NVMI.value[ListIndex]->xGrid = *(SINT16 *)FieldValue;
                    break;
                case 5: //yGrid
                    NVMI.value[ListIndex]->yGrid = *(SINT16 *)FieldValue;
                    break;
                case 6: //unknown2_p
                    //Not recommended...would make read only, but required for copying one NVMI over another
                    delete []NVMI.value[ListIndex]->unknown2;
                    NVMI.value[ListIndex]->unknown2Size = ArraySize;
                    NVMI.value[ListIndex]->unknown2 = new unsigned char[ArraySize];
                    memcpy(NVMI.value[ListIndex]->unknown2, FieldValue, ArraySize);
                    break;
                default:
                    break;
                }
            break;
        case 9: //NVCI
            if(ListFieldID == 0) //NVCISize
                {
                NVCI.resize(ArraySize);
                return false;
                }

            if(ListIndex >= NVCI.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    NVCI.value[ListIndex]->unknown1 = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown2
                    NVCI.value[ListIndex]->unknown2.resize(ArraySize);
                    for(UINT32 x = 0; x < ArraySize; x++)
                        NVCI.value[ListIndex]->unknown2[x] = ((FORMIDARRAY)FieldValue)[x];
                    return true;
                case 3: //unknown3
                    NVCI.value[ListIndex]->unknown3.resize(ArraySize);
                    for(UINT32 x = 0; x < ArraySize; x++)
                        NVCI.value[ListIndex]->unknown3[x] = ((FORMIDARRAY)FieldValue)[x];
                    return true;
                case 4: //doors
                    NVCI.value[ListIndex]->doors.resize(ArraySize);
                    for(UINT32 x = 0; x < ArraySize; x++)
                        NVCI.value[ListIndex]->doors[x] = ((FORMIDARRAY)FieldValue)[x];
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

void NAVIRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    NAVINVMI defaultNVMI;
    NAVINVCI defaultNVCI;
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
        case 7: //version
            NVER.Unload();
            return;
        case 8: //NVMI
            if(ListFieldID == 0) //NVMISize
                {
                NVMI.Unload();
                return;
                }

            if(ListIndex >= NVMI.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    NVMI.value[ListIndex]->unknown1[0] = defaultNVMI.unknown1[0];
                    NVMI.value[ListIndex]->unknown1[1] = defaultNVMI.unknown1[1];
                    NVMI.value[ListIndex]->unknown1[2] = defaultNVMI.unknown1[2];
                    NVMI.value[ListIndex]->unknown1[3] = defaultNVMI.unknown1[3];
                    return;
                case 2: //mesh
                    NVMI.value[ListIndex]->mesh = defaultNVMI.mesh;
                    return;
                case 3: //location
                    NVMI.value[ListIndex]->location = defaultNVMI.location;
                    return;
                case 4: //xGrid
                    NVMI.value[ListIndex]->xGrid = defaultNVMI.xGrid;
                    return;
                case 5: //yGrid
                    NVMI.value[ListIndex]->yGrid = defaultNVMI.yGrid;
                    return;
                case 6: //unknown2_p
                    //Not recommended...would make read only, but required for copying one NVMI over another
                    delete []NVMI.value[ListIndex]->unknown2;
                    NVMI.value[ListIndex]->unknown2 = NULL;
                    return;
                default:
                    return;
                }
            return;
        case 9: //NVCI
            if(ListFieldID == 0) //NVCISize
                {
                NVCI.Unload();
                return;
                }

            if(ListIndex >= NVCI.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    NVCI.value[ListIndex]->unknown1 = defaultNVCI.unknown1;
                    return;
                case 2: //unknown2
                    NVCI.value[ListIndex]->unknown2.clear();
                    return;
                case 3: //unknown3
                    NVCI.value[ListIndex]->unknown3.clear();
                    return;
                case 4: //doors
                    NVCI.value[ListIndex]->doors.clear();
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