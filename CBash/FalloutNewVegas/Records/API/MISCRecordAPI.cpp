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
#include "..\MISCRecord.h"

namespace FNV
{
UINT32 MISCRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //boundX1
            return SINT16_FIELD;
        case 8: //boundY1
            return SINT16_FIELD;
        case 9: //boundZ1
            return SINT16_FIELD;
        case 10: //boundX2
            return SINT16_FIELD;
        case 11: //boundY2
            return SINT16_FIELD;
        case 12: //boundZ2
            return SINT16_FIELD;
        case 13: //full
            return STRING_FIELD;
        case 14: //modPath
            return ISTRING_FIELD;
        case 15: //modb
            return FLOAT32_FIELD;
        case 16: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 17: //altTextures
            if(!MODL.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return MODL->Textures.MODS.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return STRING_FIELD;
                case 2: //texture
                    return FORMID_FIELD;
                case 3: //index
                    return SINT32_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 18: //modelFlags
            return UINT8_FLAG_FIELD;
        case 19: //iconPath
            return ISTRING_FIELD;
        case 20: //smallIconPath
            return ISTRING_FIELD;
        case 21: //script
            return FORMID_FIELD;
        case 22: //destructableHealth
            return SINT32_FIELD;
        case 23: //destructableCount
            return UINT8_FIELD;
        case 24: //destructableFlags
            return UINT8_FLAG_FIELD;
        case 25: //destructableUnused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Destructable.IsLoaded() ? 2 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 26: //destructableStages
            if(!Destructable.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //destructableStages
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return Destructable->Stages.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Destructable->Stages.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //health
                    return UINT8_FIELD;
                case 2: //index
                    return UINT8_FIELD;
                case 3: //stage
                    return UINT8_FIELD;
                case 4: //flags
                    return UINT8_FLAG_FIELD;
                case 5: //dps
                    return SINT32_FIELD;
                case 6: //explosion
                    return FORMID_FIELD;
                case 7: //debris
                    return FORMID_FIELD;
                case 8: //debrisCount
                    return SINT32_FIELD;
                case 9: //modPath
                    return ISTRING_FIELD;
                case 10: //modt_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Destructable->Stages.value[ListIndex]->DMDT.GetSize();
                        default:
                            return UNKNOWN_FIELD;
                        }
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 27: //pickupSound
            return FORMID_FIELD;
        case 28: //dropSound
            return FORMID_FIELD;
        case 29: //value
            return SINT32_FIELD;
        case 30: //weight
            return FLOAT32_FIELD;
        case 31: //loopSound
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * MISCRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //boundX1
            return &OBND.value.x1;
        case 8: //boundY1
            return &OBND.value.y1;
        case 9: //boundZ1
            return &OBND.value.z1;
        case 10: //boundX2
            return &OBND.value.x2;
        case 11: //boundY2
            return &OBND.value.y2;
        case 12: //boundZ2
            return &OBND.value.z2;
        case 13: //full
            return FULL.value;
        case 14: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 15: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 16: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 17: //altTextures
            if(!MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 18: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 19: //iconPath
            return ICON.value;
        case 20: //smallIconPath
            return MICO.value;
        case 21: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 22: //destructableHealth
            return Destructable.IsLoaded() ? &Destructable->DEST.value.health : NULL;
        case 23: //destructableCount
            return Destructable.IsLoaded() ? &Destructable->DEST.value.count : NULL;
        case 24: //destructableFlags
            return Destructable.IsLoaded() ? &Destructable->DEST.value.flags : NULL;
        case 25: //destructableUnused1
            *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST.value.unused1[0] : NULL;
            return NULL;
        case 26: //destructableStages
            if(!Destructable.IsLoaded())
                return NULL;

            if(ListIndex >= Destructable->Stages.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //health
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.health;
                case 2: //index
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.index;
                case 3: //stage
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.stage;
                case 4: //flags
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.flags;
                case 5: //dps
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.dps;
                case 6: //explosion
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.explosion;
                case 7: //debris
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.debris;
                case 8: //debrisCount
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount;
                case 9: //modPath
                    return Destructable->Stages.value[ListIndex]->DMDL.value;
                case 10: //modt_p
                    *FieldValues = Destructable->Stages.value[ListIndex]->DMDT.value;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 27: //pickupSound
            return YNAM.IsLoaded() ? &YNAM.value : NULL;
        case 28: //dropSound
            return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
        case 29: //value
            return &DATA.value.value;
        case 30: //weight
            return &DATA.value.weight;
        case 31: //loopSound
            return RNAM.IsLoaded() ? &RNAM.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool MISCRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //boundX1
            OBND.value.x1 = *(SINT16 *)FieldValue;
            break;
        case 8: //boundY1
            OBND.value.y1 = *(SINT16 *)FieldValue;
            break;
        case 9: //boundZ1
            OBND.value.z1 = *(SINT16 *)FieldValue;
            break;
        case 10: //boundX2
            OBND.value.x2 = *(SINT16 *)FieldValue;
            break;
        case 11: //boundY2
            OBND.value.y2 = *(SINT16 *)FieldValue;
            break;
        case 12: //boundZ2
            OBND.value.z2 = *(SINT16 *)FieldValue;
            break;
        case 13: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 14: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 15: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 16: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 17: //altTextures
            MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MODL->Textures.MODS[ListIndex]->name;
                    MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (UINT32)strlen((STRING)FieldValue) + 1;
                        MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MODL->Textures.MODS[ListIndex]->name, ArraySize, (STRING)FieldValue);
                        }
                    break;
                case 2: //texture
                    MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MODL->Textures.MODS[ListIndex]->index = *(SINT32 *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 18: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 19: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 20: //smallIconPath
            MICO.Copy((STRING)FieldValue);
            break;
        case 21: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 22: //destructableHealth
            Destructable.Load();
            Destructable->DEST.value.health = *(SINT32 *)FieldValue;
            break;
        case 23: //destructableCount
            Destructable.Load();
            Destructable->DEST.value.count = *(UINT8 *)FieldValue;
            break;
        case 24: //destructableFlags
            Destructable.Load();
            Destructable->SetFlagMask(*(UINT8 *)FieldValue);
            break;
        case 25: //destructableUnused1
            if(ArraySize != 2)
                break;
            Destructable.Load();
            Destructable->DEST.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Destructable->DEST.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 26: //destructableStages
            Destructable.Load();
            if(ListFieldID == 0) //destructableStagesSize
                {
                Destructable->Stages.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Destructable->Stages.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //health
                    Destructable->Stages.value[ListIndex]->DSTD.value.health = *(UINT8 *)FieldValue;
                    break;
                case 2: //index
                    Destructable->Stages.value[ListIndex]->DSTD.value.index = *(UINT8 *)FieldValue;
                    break;
                case 3: //stage
                    Destructable->Stages.value[ListIndex]->DSTD.value.stage = *(UINT8 *)FieldValue;
                    break;
                case 4: //flags
                    Destructable->Stages.value[ListIndex]->SetFlagMask(*(UINT8 *)FieldValue);
                    break;
                case 5: //dps
                    Destructable->Stages.value[ListIndex]->DSTD.value.dps = *(SINT32 *)FieldValue;
                    break;
                case 6: //explosion
                    Destructable->Stages.value[ListIndex]->DSTD.value.explosion = *(FORMID *)FieldValue;
                    return true;
                case 7: //debris
                    Destructable->Stages.value[ListIndex]->DSTD.value.debris = *(FORMID *)FieldValue;
                    return true;
                case 8: //debrisCount
                    Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount = *(SINT32 *)FieldValue;
                    break;
                case 9: //modPath
                    Destructable->Stages.value[ListIndex]->DMDL.Copy((STRING)FieldValue);
                    break;
                case 10: //modt_p
                    Destructable->Stages.value[ListIndex]->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
                    break;
                default:
                    break;
                }
            break;
        case 27: //pickupSound
            YNAM.value = *(FORMID *)FieldValue; 
            return true;
        case 28: //dropSound
            ZNAM.value = *(FORMID *)FieldValue; 
            return true;
        case 29: //value
            DATA.value.value = *(UINT32 *)FieldValue;
            break;
        case 30: //weight
            DATA.value.weight = *(FLOAT32 *)FieldValue;
            break;
        case 31: //loopSound
            RNAM.value = *(FORMID *)FieldValue; 
            return true;
        default:
            break;
        }
    return false;
    }

void MISCRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    GENDEST defaultDEST;
    DESTDSTD defaultDSTD;
    GENVALUEWEIGHT defaultDATA;
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
        case 7: //boundX1
            OBND.value.x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            OBND.value.y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            OBND.value.z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            OBND.value.x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            OBND.value.y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            OBND.value.z2 = defaultOBND.z2;
            return;
        case 13: //full
            FULL.Unload();
            return;
        case 14: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 15: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 16: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 17: //altTextures
            if(MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MODL->Textures.MODS[ListIndex]->name;
                        MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 18: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 19: //iconPath
            ICON.Unload();
            return;
        case 20: //smallIconPath
            MICO.Unload();
            return;
        case 21: //script
            SCRI.Unload();
            return;
        case 22: //destructableHealth
            if(Destructable.IsLoaded())
                Destructable->DEST.value.health = defaultDEST.health;
            return;
        case 23: //destructableCount
            if(Destructable.IsLoaded())
                Destructable->DEST.value.count = defaultDEST.count;
            return;
        case 24: //destructableFlags
            if(Destructable.IsLoaded())
                Destructable->SetFlagMask(defaultDEST.flags);
            return;
        case 25: //destructableUnused1
            if(Destructable.IsLoaded())
                {
                Destructable->DEST.value.unused1[0] = defaultDSTD.health;
                }
            return;
        case 26: //destructableStages
            if(Destructable.IsLoaded())
                {
                if(ListFieldID == 0) //destructableStages
                    {
                    Destructable->Stages.Unload();
                    return;
                    }

                if(ListIndex >= Destructable->Stages.value.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //health
                        Destructable->Stages.value[ListIndex]->DSTD.value.health = defaultDSTD.health;
                        return;
                    case 2: //index
                        Destructable->Stages.value[ListIndex]->DSTD.value.index = defaultDSTD.index;
                        return;
                    case 3: //stage
                        Destructable->Stages.value[ListIndex]->DSTD.value.stage = defaultDSTD.stage;
                        return;
                    case 4: //flags
                        Destructable->Stages.value[ListIndex]->SetFlagMask(defaultDSTD.flags);
                        return;
                    case 5: //dps
                        Destructable->Stages.value[ListIndex]->DSTD.value.dps = defaultDSTD.dps;
                        return;
                    case 6: //explosion
                        Destructable->Stages.value[ListIndex]->DSTD.value.explosion = defaultDSTD.explosion;
                        return;
                    case 7: //debris
                        Destructable->Stages.value[ListIndex]->DSTD.value.debris = defaultDSTD.debris;
                        return;
                    case 8: //debrisCount
                        Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount = defaultDSTD.debrisCount;
                        return;
                    case 9: //modPath
                        Destructable->Stages.value[ListIndex]->DMDL.Unload();
                        return;
                    case 10: //modt_p
                        Destructable->Stages.value[ListIndex]->DMDT.Unload();
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 27: //pickupSound
            YNAM.Unload();
            return;
        case 28: //dropSound
            ZNAM.Unload();
            return;
        case 29: //value
            DATA.value.value = defaultDATA.value;
            return;
        case 30: //weight
            DATA.value.weight = defaultDATA.weight;
            return;
        case 31: //loopSound
            RNAM.Unload();
            return;
        default:
            return;
        }
    return;
    }
}