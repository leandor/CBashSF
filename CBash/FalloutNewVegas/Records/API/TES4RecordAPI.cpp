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
#include "..\TES4Record.h"

namespace FNV
{
UINT32 TES4Record::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 4: //formVersion
            return UINT16_FIELD;
        case 5: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 6: //hedr HEDR ,, Struct
            return FLOAT32_FIELD;
        case 7: //hedr HEDR ,, Struct
            return UINT32_FIELD;
        case 8: //hedr HEDR ,, Struct
            return UINT32_FIELD;
        case 9: //ofst_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return OFST.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //dele_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DELE.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 11: //cnam Author
            return ISTRING_FIELD;
        case 12: //snam Description
            return ISTRING_FIELD;
        case 13: //mast Filename
            return ISTRING_FIELD;
        case 14: //data_p Unused
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 8;
                default:
                    return UNKNOWN_FIELD;
                }
        case 15: //onam Overriden Forms
            return UNPARSED_FIELD;
        case 16: //scrn_p Screenshot
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCRN.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

void * TES4Record::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 4: //formVersion
            return &formVersion;
        case 5: //versionControl2
            *FieldValues = &versionControl2;
            return NULL;
        case 6: //hedr HEDR ,, Struct
            return HEDR.IsLoaded() ? &HEDR->value6 : NULL;
        case 7: //hedr HEDR ,, Struct
            return HEDR.IsLoaded() ? &HEDR->value7 : NULL;
        case 8: //hedr HEDR ,, Struct
            return HEDR.IsLoaded() ? &HEDR->value8 : NULL;
        case 9: //ofst_p Unknown
            *FieldValues = OFST.value;
            return NULL;
        case 10: //dele_p Unknown
            *FieldValues = DELE.value;
            return NULL;
        case 11: //cnam Author
            return CNAM.value;
        case 12: //snam Description
            return SNAM.value;
        case 13: //mast Filename
            return MAST.value;
        case 14: //data_p Unused
            *FieldValues = DATA.IsLoaded() ? &DATA->value14[0] : NULL;
            return NULL;
        case 15: //onam Overriden Forms
            return UNPARSEDGET_FIELD15;
        case 16: //scrn_p Screenshot
            *FieldValues = SCRN.value;
            return NULL;
        default:
            return NULL;
        }
    }

bool TES4Record::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8 *)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8 *)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8 *)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8 *)FieldValue)[3];
            break;
        case 4: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 5: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8 *)FieldValue)[0];
            versionControl2[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 6: //hedr HEDR ,, Struct
            HEDR.Load();
            HEDR->value6 = *(FLOAT32 *)FieldValue;
            break;
        case 7: //hedr HEDR ,, Struct
            HEDR.Load();
            HEDR->value7 = *(UINT32 *)FieldValue;
            break;
        case 8: //hedr HEDR ,, Struct
            HEDR.Load();
            HEDR->value8 = *(UINT32 *)FieldValue;
            break;
        case 9: //ofst_p Unknown
            OFST.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //dele_p Unknown
            DELE.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //cnam Author
            CNAM.Copy((STRING)FieldValue);
            break;
        case 12: //snam Description
            SNAM.Copy((STRING)FieldValue);
            break;
        case 13: //mast Filename
            MAST.Copy((STRING)FieldValue);
            break;
        case 14: //data_p Unused
            if(ArraySize != 8)
                break;
            DATA.Load();
            DATA->value14[0] = ((UINT8 *)FieldValue)[0];
            DATA->value14[1] = ((UINT8 *)FieldValue)[1];
            DATA->value14[2] = ((UINT8 *)FieldValue)[2];
            DATA->value14[3] = ((UINT8 *)FieldValue)[3];
            DATA->value14[4] = ((UINT8 *)FieldValue)[4];
            DATA->value14[5] = ((UINT8 *)FieldValue)[5];
            DATA->value14[6] = ((UINT8 *)FieldValue)[6];
            DATA->value14[7] = ((UINT8 *)FieldValue)[7];
            break;
        case 15: //onam Overriden Forms
            return UNPARSEDGET_FIELD15;
        case 16: //scrn_p Screenshot
            SCRN.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void TES4Record::DeleteField(FIELD_IDENTIFIERS)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //formVersion
            formVersion = 0;
            return;
        case 5: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 6: //hedr HEDR ,, Struct
            HEDR.Unload();
            return;
        case 7: //hedr HEDR ,, Struct
            HEDR.Unload();
            return;
        case 8: //hedr HEDR ,, Struct
            HEDR.Unload();
            return;
        case 9: //ofst_p Unknown
            OFST.Unload();
            return;
        case 10: //dele_p Unknown
            DELE.Unload();
            return;
        case 11: //cnam Author
            CNAM.Unload();
            return;
        case 12: //snam Description
            SNAM.Unload();
            return;
        case 13: //mast Filename
            MAST.Unload();
            return;
        case 14: //data_p Unused
            DATA.Unload();
            return;
        case 15: //onam Overriden Forms
            return UNPARSEDDEL_FIELD15;
        case 16: //scrn_p Screenshot
            SCRN.Unload();
            return;
        default:
            return;
        }
    }
}