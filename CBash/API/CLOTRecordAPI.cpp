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
#include "..\Common.h"
#include "..\Records\CLOTRecord.h"

int CLOTRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //full
            return STRING_FIELD;
        case 7: //script
            return FID_FIELD;
        case 8: //enchantment
            return FID_FIELD;
        case 9: //enchantPoints
            return USHORT_FIELD;
        case 10: //flags
            return UINT_FIELD;
        case 11: //maleBody_modPath
            return STRING_FIELD;
        case 12: //maleBody_modb
            return FLOAT_FIELD;
        case 13: //maleBody_modt_p
            return BYTES_FIELD;
        case 14: //maleWorld_modPath
            return STRING_FIELD;
        case 15: //maleWorld_modb
            return FLOAT_FIELD;
        case 16: //maleWorld_modt_p
            return BYTES_FIELD;
        case 17: //maleIconPath
            return STRING_FIELD;
        case 18: //femaleBody_modPath
            return STRING_FIELD;
        case 19: //femaleBody_modb
            return FLOAT_FIELD;
        case 20: //femaleBody_modt_p
            return BYTES_FIELD;
        case 21: //femaleWorld_modPath
            return STRING_FIELD;
        case 22: //femaleWorld_modb
            return FLOAT_FIELD;
        case 23: //femaleWorld_modt_p
            return BYTES_FIELD;
        case 24: //femaleIconPath
            return STRING_FIELD;
        case 25: //value
            return UINT_FIELD;
        case 26: //weight
            return FLOAT_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * CLOTRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //full
            return FULL.value;
        case 7: //script
            if(SCRI.IsLoaded())
                return &SCRI->fid;
            return NULL;
        case 8: //enchantment
            if(ENAM.IsLoaded())
                return &ENAM->fid;
            return NULL;
        case 9: //enchantPoints
            if(ANAM.IsLoaded())
                return &ANAM->enchantPoints;
            return NULL;
        case 10: //flags
            return &BMDT.value.flags;
        case 11: //maleBody_modPath
            if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
                return MODL->MODL.value;
            return NULL;
        case 12: //maleBody_modb
            if(MODL.IsLoaded() && MODL->MODB.IsLoaded())
                return &MODL->MODB.value.MODB;
            return NULL;
        case 14: //maleWorld_modPath
            if(MOD2.IsLoaded() && MOD2->MODL.IsLoaded())
                return MOD2->MODL.value;
            return NULL;
        case 15: //maleWorld_modb
            if(MOD2.IsLoaded() && MOD2->MODB.IsLoaded())
                return &MOD2->MODB.value.MODB;
            return NULL;
        case 17: //maleIconPath
            return ICON.value;
        case 18: //femaleBody_modPath
            if(MOD3.IsLoaded() && MOD3->MODL.IsLoaded())
                return MOD3->MODL.value;
            return NULL;
        case 19: //femaleBody_modb
            if(MOD3.IsLoaded() && MOD3->MODB.IsLoaded())
                return &MOD3->MODB.value.MODB;
            return NULL;
        case 21: //femaleWorld_modPath
            if(MOD4.IsLoaded() && MOD4->MODL.IsLoaded())
                return MOD4->MODL.value;
            return NULL;
        case 22: //femaleWorld_modb
            if(MOD4.IsLoaded() && MOD4->MODB.IsLoaded())
                return &MOD4->MODB.value.MODB;
            return NULL;
        case 24: //femaleIconPath
            return ICO2.value;
        case 25: //value
            return &DATA.value.value;
        case 26: //weight
            return &DATA.value.weight;
        default:
            return NULL;
        }
    }

unsigned int CLOTRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 13: //maleBody_modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                return MODL->MODT.size;
            return 0;
        case 16: //maleWorld_modt_p
            if(MOD2.IsLoaded() && MOD2->MODT.IsLoaded())
                return MOD2->MODT.size;
            return 0;
        case 20: //femaleBody_modt_p
            if(MOD3.IsLoaded() && MOD3->MODT.IsLoaded())
                return MOD3->MODT.size;
            return 0;
        case 23: //femaleWorld_modt_p
            if(MOD4.IsLoaded() && MOD4->MODT.IsLoaded())
                return MOD4->MODT.size;
            return 0;
        default:
            return 0;
        }
    }

void CLOTRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 13: //maleBody_modt_p
            if(MODL.IsLoaded() && MODL->MODT.IsLoaded())
                *FieldValues = MODL->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 16: //maleWorld_modt_p
            if(MOD2.IsLoaded() && MOD2->MODT.IsLoaded())
                *FieldValues = MOD2->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 20: //femaleBody_modt_p
            if(MOD3.IsLoaded() && MOD3->MODT.IsLoaded())
                *FieldValues = MOD3->MODT.value;
            else
                *FieldValues = NULL;
            return;
        case 23: //femaleWorld_modt_p
            if(MOD4.IsLoaded() && MOD4->MODT.IsLoaded())
                *FieldValues = MOD4->MODT.value;
            else
                *FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void CLOTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 6: //full
            FULL.Copy(FieldValue);
            break;
        case 11: //maleBody_modPath
            MODL.Load();
            MODL->MODL.Copy(FieldValue);
            break;
        case 14: //maleWorld_modPath
            MOD2.Load();
            MOD2->MODL.Copy(FieldValue);
            break;
        case 17: //maleIconPath
            ICON.Copy(FieldValue);
            break;
        case 18: //femaleBody_modPath
            MOD3.Load();
            MOD3->MODL.Copy(FieldValue);
            break;
        case 21: //femaleWorld_modPath
            MOD4.Load();
            MOD4->MODL.Copy(FieldValue);
            break;
        case 24: //femaleIconPath
            ICO2.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void CLOTRecord::SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 7: //script
            SCRI.Load();
            SCRI->fid = FieldValue;
            FormIDHandler.AddMaster(SCRI->fid);
            break;
        case 8: //enchantment
            ENAM.Load();
            ENAM->fid = FieldValue;
            FormIDHandler.AddMaster(ENAM->fid);
            break;
        case 10: //flags
            BMDT.value.flags = FieldValue;
            break;
        case 25: //value
            DATA.value.value = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CLOTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue)
    {
    switch(Field)
        {
        case 9: //enchantPoints
            ANAM.Load();
            ANAM->enchantPoints = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CLOTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 12: //maleBody_modb
            MODL.Load();
            MODL->MODB.Load();
            MODL->MODB.value.MODB = FieldValue;
            break;
        case 15: //maleWorld_modb
            MOD2.Load();
            MOD2->MODB.Load();
            MOD2->MODB.value.MODB = FieldValue;
            break;
        case 19: //femaleBody_modb
            MOD3.Load();
            MOD3->MODB.Load();
            MOD3->MODB.value.MODB = FieldValue;
            break;
        case 22: //femaleWorld_modb
            MOD4.Load();
            MOD4->MODB.Load();
            MOD4->MODB.value.MODB = FieldValue;
            break;
        case 26: //weight
            DATA.value.weight = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void CLOTRecord::SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 13: //maleBody_modt_p
            MODL.Load();
            MODL->MODT.Load();
            MODL->MODT.Copy(FieldValue, nSize);
            break;
        case 16: //maleWorld_modt_p
            MOD2.Load();
            MOD2->MODT.Load();
            MOD2->MODT.Copy(FieldValue, nSize);
            break;
        case 20: //femaleBody_modt_p
            MOD3.Load();
            MOD3->MODT.Load();
            MOD3->MODT.Copy(FieldValue, nSize);
            break;
        case 23: //femaleWorld_modt_p
            MOD4.Load();
            MOD4->MODT.Load();
            MOD4->MODT.Copy(FieldValue, nSize);
            break;
        default:
            return;
        }
    return;
    }


int CLOTRecord::DeleteField(const unsigned int Field)
    {
    GENVALUEWEIGHT defaultDATA;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //full
            FULL.Unload();
            break;
        case 7: //script
            SCRI.Unload();
            break;
        case 8: //enchantment
            ENAM.Unload();
            break;
        case 9: //enchantPoints
            ANAM.Unload();
            break;
        case 10: //flags
            BMDT.Unload();
            break;
        case 11: //maleBody_modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            break;
        case 12: //maleBody_modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            break;
        case 13: //maleBody_modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            break;
        case 14: //maleWorld_modPath
            if(MOD2.IsLoaded())
                MOD2->MODL.Unload();
            break;
        case 15: //maleWorld_modb
            if(MOD2.IsLoaded())
                MOD2->MODB.Unload();
            break;
        case 16: //maleWorld_modt_p
            if(MOD2.IsLoaded())
                MOD2->MODT.Unload();
            break;
        case 17: //maleIconPath
            ICON.Unload();
            break;
        case 18: //femaleBody_modPath
            if(MOD3.IsLoaded())
                MOD3->MODL.Unload();
            break;
        case 19: //femaleBody_modb
            if(MOD3.IsLoaded())
                MOD3->MODB.Unload();
            break;
        case 20: //femaleBody_modt_p
            if(MOD3.IsLoaded())
                MOD3->MODT.Unload();
            break;
        case 21: //femaleWorld_modPath
            if(MOD4.IsLoaded())
                MOD4->MODL.Unload();
            break;
        case 22: //femaleWorld_modb
            if(MOD4.IsLoaded())
                MOD4->MODB.Unload();
            break;
        case 23: //femaleWorld_modt_p
            if(MOD4.IsLoaded())
                MOD4->MODT.Unload();
            break;
        case 24: //femaleIconPath
            ICO2.Unload();
            break;
        case 25: //value
            DATA.value.value = defaultDATA.value;
            break;
        case 26: //weight
            DATA.value.weight = defaultDATA.weight;
            break;
        default:
            return 0;
        }
    return 0;
    }
