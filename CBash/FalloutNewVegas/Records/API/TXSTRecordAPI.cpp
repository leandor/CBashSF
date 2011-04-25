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
#include "..\TXSTRecord.h"

namespace FNV
{
UINT32 TXSTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 6: //eid
            return ISTRING_FIELD;
        case 7: //obnd Object Bounds
            return SINT16_FIELD;
        case 8: //obnd Object Bounds
            return SINT16_FIELD;
        case 9: //obnd Object Bounds
            return SINT16_FIELD;
        case 10: //tx00 Base Image / Transparency
            return ISTRING_FIELD;
        case 11: //tx01 Normal Map / Specular
            return ISTRING_FIELD;
        case 12: //tx02 Environment Map Mask / ?
            return ISTRING_FIELD;
        case 13: //tx03 Glow Map / Unused
            return ISTRING_FIELD;
        case 14: //tx04 Parallax Map / Unused
            return ISTRING_FIELD;
        case 15: //tx05 Environment Map / Unused
            return ISTRING_FIELD;
        case 16: //dodt Decal Data
            return FLOAT32_FIELD;
        case 17: //dodt Decal Data
            return FLOAT32_FIELD;
        case 18: //dodt Decal Data
            return FLOAT32_FIELD;
        case 19: //dodt Decal Data
            return FLOAT32_FIELD;
        case 20: //dodt Decal Data
            return FLOAT32_FIELD;
        case 21: //dodt Decal Data
            return FLOAT32_FIELD;
        case 22: //dodt Decal Data
            return FLOAT32_FIELD;
        case 23: //dodt Decal Data
            return UINT8_FIELD;
        case 24: //dodt Decal Data
            return UINT8_FIELD;
        case 25: //dodt_p Decal Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 26: //dodt Decal Data
            return UINT8_FIELD;
        case 27: //dodt Decal Data
            return UINT8_FIELD;
        case 28: //dodt Decal Data
            return UINT8_FIELD;
        case 29: //dodt_p Decal Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
        case 30: //dnam Flags
            return UINT16_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * TXSTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 6: //eid
            return EDID.value;
        case 7: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value7 : NULL;
        case 8: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value8 : NULL;
        case 9: //obnd Object Bounds
            return OBNDReq.IsLoaded() ? &OBNDReq->value9 : NULL;
        case 10: //tx00 Base Image / Transparency
            return TX00.IsLoaded() ? TX00->TX00.value : NULL;
        case 11: //tx01 Normal Map / Specular
            return TX00.IsLoaded() ? TX00->TX01.value : NULL;
        case 12: //tx02 Environment Map Mask / ?
            return TX00.IsLoaded() ? TX00->TX02.value : NULL;
        case 13: //tx03 Glow Map / Unused
            return TX00.IsLoaded() ? TX00->TX03.value : NULL;
        case 14: //tx04 Parallax Map / Unused
            return TX00.IsLoaded() ? TX00->TX04.value : NULL;
        case 15: //tx05 Environment Map / Unused
            return TX00.IsLoaded() ? TX00->TX05.value : NULL;
        case 16: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value16 : NULL;
        case 17: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value17 : NULL;
        case 18: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value18 : NULL;
        case 19: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value19 : NULL;
        case 20: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value20 : NULL;
        case 21: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value21 : NULL;
        case 22: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value22 : NULL;
        case 23: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value23 : NULL;
        case 24: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value24 : NULL;
        case 25: //dodt_p Decal Data
            *FieldValues = DODT.IsLoaded() ? &DODT->value25[0] : NULL;
            return NULL;
        case 26: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value26 : NULL;
        case 27: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value27 : NULL;
        case 28: //dodt Decal Data
            return DODT.IsLoaded() ? &DODT->value28 : NULL;
        case 29: //dodt_p Decal Data
            *FieldValues = DODT.IsLoaded() ? &DODT->value29[0] : NULL;
            return NULL;
        case 30: //dnam Flags
            return DNAM.IsLoaded() ? &DNAM->value30 : NULL;
        default:
            return NULL;
        }
    }

bool TXSTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 6: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 7: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value7 = *(SINT16 *)FieldValue;
            break;
        case 8: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value8 = *(SINT16 *)FieldValue;
            break;
        case 9: //obnd Object Bounds
            OBNDReq.Load();
            OBNDReq->value9 = *(SINT16 *)FieldValue;
            break;
        case 10: //tx00 Base Image / Transparency
            TX00.Load();
            TX00->TX00.Copy((STRING)FieldValue);
            break;
        case 11: //tx01 Normal Map / Specular
            TX00.Load();
            TX00->TX01.Copy((STRING)FieldValue);
            break;
        case 12: //tx02 Environment Map Mask / ?
            TX00.Load();
            TX00->TX02.Copy((STRING)FieldValue);
            break;
        case 13: //tx03 Glow Map / Unused
            TX00.Load();
            TX00->TX03.Copy((STRING)FieldValue);
            break;
        case 14: //tx04 Parallax Map / Unused
            TX00.Load();
            TX00->TX04.Copy((STRING)FieldValue);
            break;
        case 15: //tx05 Environment Map / Unused
            TX00.Load();
            TX00->TX05.Copy((STRING)FieldValue);
            break;
        case 16: //dodt Decal Data
            DODT.Load();
            DODT->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //dodt Decal Data
            DODT.Load();
            DODT->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //dodt Decal Data
            DODT.Load();
            DODT->value18 = *(FLOAT32 *)FieldValue;
            break;
        case 19: //dodt Decal Data
            DODT.Load();
            DODT->value19 = *(FLOAT32 *)FieldValue;
            break;
        case 20: //dodt Decal Data
            DODT.Load();
            DODT->value20 = *(FLOAT32 *)FieldValue;
            break;
        case 21: //dodt Decal Data
            DODT.Load();
            DODT->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //dodt Decal Data
            DODT.Load();
            DODT->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //dodt Decal Data
            DODT.Load();
            DODT->value23 = *(UINT8 *)FieldValue;
            break;
        case 24: //dodt Decal Data
            DODT.Load();
            DODT->value24 = *(UINT8 *)FieldValue;
            break;
        case 25: //dodt_p Decal Data
            if(ArraySize != 2)
                break;
            DODT.Load();
            DODT->value25[0] = ((UINT8 *)FieldValue)[0];
            DODT->value25[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 26: //dodt Decal Data
            DODT.Load();
            DODT->value26 = *(UINT8 *)FieldValue;
            break;
        case 27: //dodt Decal Data
            DODT.Load();
            DODT->value27 = *(UINT8 *)FieldValue;
            break;
        case 28: //dodt Decal Data
            DODT.Load();
            DODT->value28 = *(UINT8 *)FieldValue;
            break;
        case 29: //dodt_p Decal Data
            if(ArraySize != 1)
                break;
            DODT.Load();
            DODT->value29[0] = ((UINT8 *)FieldValue)[0];
            break;
        case 30: //dnam Flags
            DNAM.Load();
            DNAM->value30 = *(UINT16 *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void TXSTRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 6: //eid
            EDID.Unload();
            return;
        case 7: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 8: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 9: //obnd Object Bounds
            OBNDReq.Unload();
            return;
        case 10: //tx00 Base Image / Transparency
            if(TX00.IsLoaded())
                TX00->TX00.Unload();
            return;
        case 11: //tx01 Normal Map / Specular
            if(TX00.IsLoaded())
                TX00->TX01.Unload();
            return;
        case 12: //tx02 Environment Map Mask / ?
            if(TX00.IsLoaded())
                TX00->TX02.Unload();
            return;
        case 13: //tx03 Glow Map / Unused
            if(TX00.IsLoaded())
                TX00->TX03.Unload();
            return;
        case 14: //tx04 Parallax Map / Unused
            if(TX00.IsLoaded())
                TX00->TX04.Unload();
            return;
        case 15: //tx05 Environment Map / Unused
            if(TX00.IsLoaded())
                TX00->TX05.Unload();
            return;
        case 16: //dodt Decal Data
            DODT.Unload();
            return;
        case 17: //dodt Decal Data
            DODT.Unload();
            return;
        case 18: //dodt Decal Data
            DODT.Unload();
            return;
        case 19: //dodt Decal Data
            DODT.Unload();
            return;
        case 20: //dodt Decal Data
            DODT.Unload();
            return;
        case 21: //dodt Decal Data
            DODT.Unload();
            return;
        case 22: //dodt Decal Data
            DODT.Unload();
            return;
        case 23: //dodt Decal Data
            DODT.Unload();
            return;
        case 24: //dodt Decal Data
            DODT.Unload();
            return;
        case 25: //dodt_p Decal Data
            DODT.Unload();
            return;
        case 26: //dodt Decal Data
            DODT.Unload();
            return;
        case 27: //dodt Decal Data
            DODT.Unload();
            return;
        case 28: //dodt Decal Data
            DODT.Unload();
            return;
        case 29: //dodt_p Decal Data
            DODT.Unload();
            return;
        case 30: //dnam Flags
            DNAM.Unload();
            return;
        default:
            return;
        }
    }
}