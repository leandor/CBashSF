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
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //boundX
            return SINT16_FIELD;
        case 6: //boundY
            return SINT16_FIELD;
        case 7: //boundZ
            return SINT16_FIELD;
        case 8: //baseImageOrTransparency
            return ISTRING_FIELD;
        case 9: //normalMapOrSpecular
            return ISTRING_FIELD;
        case 10: //environmentMapMaskOrUnknown
            return ISTRING_FIELD;
        case 11: //glowMapOrUnused
            return ISTRING_FIELD;
        case 12: //parallaxMapOrUnused
            return ISTRING_FIELD;
        case 13: //environmentMapOrUnused
            return ISTRING_FIELD;
        case 14: //decalMinWidth
            return FLOAT32_FIELD;
        case 15: //decalMaxWidth
            return FLOAT32_FIELD;
        case 16: //decalMinHeight
            return FLOAT32_FIELD;
        case 17: //decalMaxHeight
            return FLOAT32_FIELD;
        case 18: //decalDepth
            return FLOAT32_FIELD;
        case 19: //decalShininess
            return FLOAT32_FIELD;
        case 20: //decalScale
            return FLOAT32_FIELD;
        case 21: //decalPasses
            return UINT8_FIELD;
        case 22: //decalFlags
            return UINT8_FLAG_FIELD;
        case 23: //decalUnused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 24: //decalRed
            return UINT8_FIELD;
        case 25: //decalGreen
            return UINT8_FIELD;
        case 26: //decalBlue
            return UINT8_FIELD;
        case 27: //decalUnused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }            
        case 28: //flags
            return UINT16_FLAG_FIELD;
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
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //boundX
            return OBND.IsLoaded() ? &OBND.value.x : NULL;
        case 6: //boundY
            return OBND.IsLoaded() ? &OBND.value.y : NULL;
        case 7: //boundZ
            return OBND.IsLoaded() ? &OBND.value.z : NULL;
        case 8: //baseImageOrTransparency
            return TX00.value;
        case 9: //normalMapOrSpecular
            return TX01.value;
        case 10: //environmentMapMaskOrUnknown
            return TX02.value;
        case 11: //glowMapOrUnused
            return TX03.value;
        case 12: //parallaxMapOrUnused
            return TX04.value;
        case 13: //environmentMapOrUnused
            return TX05.value;
        case 14: //decalMinWidth
            return DODT.IsLoaded() ? &DODT->minWidth : NULL;
        case 15: //decalMaxWidth
            return DODT.IsLoaded() ? &DODT->maxWidth : NULL;
        case 16: //decalMinHeight
            return DODT.IsLoaded() ? &DODT->minHeight : NULL;
        case 17: //decalMaxHeight
            return DODT.IsLoaded() ? &DODT->maxHeight : NULL;
        case 18: //decalDepth
            return DODT.IsLoaded() ? &DODT->depth : NULL;
        case 19: //decalShininess
            return DODT.IsLoaded() ? &DODT->shininess : NULL;
        case 20: //decalScale
            return DODT.IsLoaded() ? &DODT->scale : NULL;
        case 21: //decalPasses
            return DODT.IsLoaded() ? &DODT->passes : NULL;
        case 22: //decalFlags
            return DODT.IsLoaded() ? &DODT->flags : NULL;
        case 23: //decalUnused1
            return DODT.IsLoaded() ? &DODT->unused1[0] : NULL;
        case 24: //decalRed
            return DODT.IsLoaded() ? &DODT->red : NULL;
        case 25: //decalGreen
            return DODT.IsLoaded() ? &DODT->green : NULL;
        case 26: //decalBlue
            return DODT.IsLoaded() ? &DODT->blue : NULL;
        case 27: //decalUnused2
            return DODT.IsLoaded() ? &DODT->unused2 : NULL;
        case 28: //flags
            return DNAM.IsLoaded() ? &DNAM.value.flags : NULL;
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
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(UINT32 *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //boundX
            OBND.Load();
            OBND.value.x = *(SINT16 *)FieldValue;
            break;
        case 6: //boundY
            OBND.Load();
            OBND.value.y = *(SINT16 *)FieldValue;
            break;
        case 7: //boundZ
            OBND.Load();
            OBND.value.z = *(SINT16 *)FieldValue;
            break;
        case 8: //baseImageOrTransparency
            TX00.Copy((STRING)FieldValue);
            break;
        case 9: //normalMapOrSpecular
            TX01.Copy((STRING)FieldValue);
            break;
        case 10: //environmentMapMaskOrUnknown
            TX02.Copy((STRING)FieldValue);
            break;
        case 11: //glowMapOrUnused
            TX03.Copy((STRING)FieldValue);
            break;
        case 12: //parallaxMapOrUnused
            TX04.Copy((STRING)FieldValue);
            break;
        case 13: //environmentMapOrUnused
            TX05.Copy((STRING)FieldValue);
            break;
        case 14: //decalMinWidth
            DODT.Load();
            DODT->minWidth = *(FLOAT32 *)FieldValue;
            break;
        case 15: //decalMaxWidth
            DODT.Load();
            DODT->maxWidth = *(FLOAT32 *)FieldValue;
            break;
        case 16: //decalMinHeight
            DODT.Load();
            DODT->minHeight = *(FLOAT32 *)FieldValue;
            break;
        case 17: //decalMaxHeight
            DODT.Load();
            DODT->maxHeight = *(FLOAT32 *)FieldValue;
            break;
        case 18: //decalDepth
            DODT.Load();
            DODT->depth = *(FLOAT32 *)FieldValue;
            break;
        case 19: //decalShininess
            DODT.Load();
            DODT->shininess = *(FLOAT32 *)FieldValue;
            break;
        case 20: //decalScale
            DODT.Load();
            DODT->scale = *(FLOAT32 *)FieldValue;
            break;
        case 21: //decalPasses
            DODT.Load();
            DODT->passes = *(UINT8 *)FieldValue;
            break;
        case 22: //decalFlags
            DODT.Load();
            DODT->SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 23: //decalUnused1
            if(ArraySize != 2)
                break;
            DODT.Load();
            DODT->unused1[0] = ((UINT8 *)FieldValue)[0];
            DODT->unused1[1] = ((UINT8 *)FieldValue)[1];
            break;
        case 24: //decalRed
            DODT.Load();
            DODT->red = *(UINT8 *)FieldValue;
            break;
        case 25: //decalGreen
            DODT.Load();
            DODT->green = *(UINT8 *)FieldValue;
            break;
        case 26: //decalBlue
            DODT.Load();
            DODT->blue = *(UINT8 *)FieldValue;
            break;
        case 27: //decalUnused2
            if(ArraySize != 1)
                break;
            DODT.Load();
            DODT->unused2 = *(UINT8 *)FieldValue;
            break;
        case 28: //flags
            SetFlagMask(*(UINT16 *)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void TXSTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    GENU16FLAG defaultU16FLAG;
    GENDODT defaultDODT;
    
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //boundX
            if(OBND.IsLoaded())
                OBND.value.x = defaultOBND.x;
            return;
        case 6: //boundY
            if(OBND.IsLoaded())
                OBND.value.y = defaultOBND.y;
            return;
        case 7: //boundZ
            if(OBND.IsLoaded())
                OBND.value.z = defaultOBND.z;
            return;
        case 8: //baseImageOrTransparency
            TX00.Unload();
            return;
        case 9: //normalMapOrSpecular
            TX01.Unload();
            return;
        case 10: //environmentMapMaskOrUnknown
            TX02.Unload();
            return;
        case 11: //glowMapOrUnused
            TX03.Unload();
            return;
        case 12: //parallaxMapOrUnused
            TX04.Unload();
            return;
        case 13: //environmentMapOrUnused
            TX05.Unload();
            return;
        case 14: //decalMinWidth
            if(DODT.IsLoaded())
                DODT->minWidth = defaultDODT.minWidth;
            return;
        case 15: //decalMaxWidth
            if(DODT.IsLoaded())
                DODT->maxWidth = defaultDODT.maxWidth;
            return;
        case 16: //decalMinHeight
            if(DODT.IsLoaded())
                DODT->minHeight = defaultDODT.minHeight;
            return;
        case 17: //decalMaxHeight
            if(DODT.IsLoaded())
                DODT->maxHeight = defaultDODT.maxHeight;
            return;
        case 18: //decalDepth
            if(DODT.IsLoaded())
                DODT->depth = defaultDODT.depth;
            return;
        case 19: //decalShininess
            if(DODT.IsLoaded())
                DODT->shininess = defaultDODT.shininess;
            return;
        case 20: //decalScale
            if(DODT.IsLoaded())
                DODT->scale = defaultDODT.scale;
            return;
        case 21: //decalPasses
            if(DODT.IsLoaded())
                DODT->passes = defaultDODT.passes;
            return;
        case 22: //decalFlags
            if(DODT.IsLoaded())
                DODT->SetFlagMask(defaultDODT.flags);
            return;
        case 23: //decalUnused1
            if(DODT.IsLoaded())
                {
                DODT->unused1[0] = defaultDODT.unused1[0];
                DODT->unused1[1] = defaultDODT.unused1[1];
                }                                
            return;
        case 24: //decalRed
            if(DODT.IsLoaded())
                DODT->red = defaultDODT.red;
            return;
        case 25: //decalGreen
            if(DODT.IsLoaded())
                DODT->green = defaultDODT.green;
            return;
        case 26: //decalBlue
            if(DODT.IsLoaded())
                DODT->blue = defaultDODT.blue;
            return;
        case 27: //decalUnused2
            if(DODT.IsLoaded())
                DODT->unused2 = defaultDODT.unused2;
            return;
        case 28: //flags
            SetFlagMask(defaultU16FLAG.flags);
            return;
        default:
            return;
        }
    }
}