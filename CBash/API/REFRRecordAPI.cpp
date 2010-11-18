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
#include "..\Records\REFRRecord.h"

int REFRRecord::GetOtherFieldType(const unsigned int Field)
    {
    switch(Field)
        {
        case 6: //base
            return FID_FIELD;
        case 7: //destination
            return FID_FIELD;
        case 8: //destinationPosX
            return FLOAT_FIELD;
        case 9: //destinationPosY
            return FLOAT_FIELD;
        case 10: //destinationPosZ
            return FLOAT_FIELD;
        case 11: //destinationRotX
            return RADIAN_FIELD;
        case 12: //destinationRotY
            return RADIAN_FIELD;
        case 13: //destinationRotZ
            return RADIAN_FIELD;
        case 14: //lockLevel
            return UBYTE_FIELD;
        case 15: //unused1
            return BYTES_FIELD;
        case 16: //lockKey
            return FID_FIELD;
        case 17: //unused2
            return BYTES_FIELD;
        case 18: //lockFlags
            return UBYTE_FIELD;
        case 19: //unused3
            return BYTES_FIELD;
        case 20: //owner
            return FID_FIELD;
        case 21: //rank
            return INT_FIELD;
        case 22: //globalVariable
            return FID_FIELD;
        case 23: //parent
            return FID_FIELD;
        case 24: //parentFlags
            return UBYTE_FIELD;
        case 25: //unused4
            return BYTES_FIELD;
        case 26: //target
            return FID_FIELD;
        case 27: //seed
            if(XSED->isOffset)
                return UBYTE_FIELD;
            return UINT_FIELD;
        case 28: //lod1
            return FLOAT_FIELD;
        case 29: //lod2
            return FLOAT_FIELD;
        case 30: //lod3
            return FLOAT_FIELD;
        case 31: //charge
            return FLOAT_FIELD;
        case 32: //health
            return INT_FIELD;
        case 33: //unknownXPCIFormID
            return FID_FIELD;
        case 34: //unknownXPCIString
            return STRING_FIELD;
        case 35: //levelMod
            return INT_FIELD;
        case 36: //unknownXRTMFormID
            return FID_FIELD;
        case 37: //actionFlags
            return UINT_FIELD;
        case 38: //count
            return INT_FIELD;
        case 39: //markerFlags
            return UBYTE_FIELD;
        case 40: //markerName
            return STRING_FIELD;
        case 41: //markerType
            return UBYTE_FIELD;
        case 42: //markerUnused
            return BYTES_FIELD;
        case 43: //scale
            return FLOAT_FIELD;
        case 44: //soul
            return UBYTE_FIELD;
        case 45: //posX
            return FLOAT_FIELD;
        case 46: //posY
            return FLOAT_FIELD;
        case 47: //posZ
            return FLOAT_FIELD;
        case 48: //rotX
            return RADIAN_FIELD;
        case 49: //rotY
            return RADIAN_FIELD;
        case 50: //rotZ
            return RADIAN_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    }

void * REFRRecord::GetOtherField(const unsigned int Field)
    {
    switch(Field)
        {
        case 5: //eid
            return EDID.value;
        case 6: //base
            return &NAME.value.fid;
        case 7: //destination
            if(XTEL.IsLoaded())
                return &XTEL->destinationFid;
            return NULL;
        case 8: //destinationPosX
            if(XTEL.IsLoaded())
                return &XTEL->destination.posX;
            return NULL;
        case 9: //destinationPosY
            if(XTEL.IsLoaded())
                return &XTEL->destination.posY;
            return NULL;
        case 10: //destinationPosZ
            if(XTEL.IsLoaded())
                return &XTEL->destination.posZ;
            return NULL;
        case 11: //destinationRotX
            if(XTEL.IsLoaded())
                return &XTEL->destination.rotX;
            return NULL;
        case 12: //destinationRotY
            if(XTEL.IsLoaded())
                return &XTEL->destination.rotY;
            return NULL;
        case 13: //destinationRotZ
            if(XTEL.IsLoaded())
                return &XTEL->destination.rotZ;
            return NULL;
        case 14: //lockLevel
            if(XLOC.IsLoaded())
                return &XLOC->level;
            return NULL;
        case 16: //lockKey
            if(XLOC.IsLoaded())
                return &XLOC->key;
            return NULL;
        case 18: //lockFlags
            if(XLOC.IsLoaded())
                return &XLOC->flags;
            return NULL;
        case 20: //owner
            if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
                return &Ownership->XOWN.value.fid;
            return NULL;
        case 21: //rank
            if(Ownership.IsLoaded() && Ownership->XRNK.IsLoaded())
                return &Ownership->XRNK->rank;
            return NULL;
        case 22: //globalVariable
            if(Ownership.IsLoaded() && Ownership->XGLB.IsLoaded())
                return &Ownership->XGLB->fid;
            return NULL;
        case 23: //parent
            if(XESP.IsLoaded())
                return &XESP->parent;
            return NULL;
        case 24: //parentFlags
            if(XESP.IsLoaded())
                return &XESP->flags;
            return NULL;
        case 26: //target
            if(XTRG.IsLoaded())
                return &XTRG->fid;
            return NULL;
        case 27: //seed
            if(XSED.IsLoaded())
                {
                if(XSED->isOffset)
                    return &XSED->offset;
                return &XSED->seed;
                }
            return NULL;
        case 28: //lod1
            if(XLOD.IsLoaded())
                return &XLOD->lod1;
            return NULL;
        case 29: //lod2
            if(XLOD.IsLoaded())
                return &XLOD->lod2;
            return NULL;
        case 30: //lod3
            if(XLOD.IsLoaded())
                return &XLOD->lod3;
            return NULL;
        case 31: //charge
            if(XCHG.IsLoaded())
                return &XCHG->charge;
            return NULL;
        case 32: //health
            if(XHLT.IsLoaded())
                return &XHLT->health;
            return NULL;
        case 33: //unknownXPCIFormID
            if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
                return &XPCI->XPCI->fid;
            return NULL;
        case 34: //unknownXPCIString
            if(XPCI.IsLoaded() && XPCI->FULL.IsLoaded())
                return XPCI->FULL.value;
            return NULL;
        case 35: //levelMod
            if(XLCM.IsLoaded())
                return &XLCM->levelMod;
            return NULL;
        case 36: //unknownXRTMFormID
            if(XRTM.IsLoaded())
                return &XRTM->fid;
            return NULL;
        case 37: //actionFlags
            if(XACT.IsLoaded())
                return &XACT->flags;
            return NULL;
        case 38: //count
            if(XCNT.IsLoaded())
                return &XCNT->count;
            return NULL;
        case 39: //markerFlags
            if(Marker.IsLoaded() && Marker->FNAM.IsLoaded())
                return &Marker->FNAM.value.flags;
            return NULL;
        case 40: //markerName
            if(Marker.IsLoaded() && Marker->FULL.IsLoaded())
                return Marker->FULL.value;
            return NULL;
        case 41: //markerType
            if(Marker.IsLoaded() && Marker->TNAM.IsLoaded())
                return &Marker->TNAM.value.markerType;
            return NULL;
        case 43: //scale
            if(XSCL.IsLoaded())
                return &XSCL->scale;
            return NULL;
        case 44: //soul
            if(XSOL.IsLoaded())
                return &XSOL->flags;
            return NULL;
        case 45: //posX
            return &DATA.value.posX;
        case 46: //posY
            return &DATA.value.posY;
        case 47: //posZ
            return &DATA.value.posZ;
        case 48: //rotX
            return &DATA.value.rotX;
        case 49: //rotY
            return &DATA.value.rotY;
        case 50: //rotZ
            return &DATA.value.rotZ;
        default:
            return NULL;
        }
    }

unsigned int REFRRecord::GetFieldArraySize(const unsigned int Field)
    {
    switch(Field)
        {
        case 15: //unused1
            if(XLOC.IsLoaded())
                return 3;
            return 0;
        case 17: //unused2
            if(XLOC.IsLoaded())
                return 4;
            return 0;
        case 19: //unused3
            if(XLOC.IsLoaded())
                return 3;
            return 0;
        case 25: //unused4
            if(XESP.IsLoaded())
                return 3;
            return 0;
        case 42: //markerUnused
            if(Marker.IsLoaded() && Marker->TNAM.IsLoaded())
                return 1;
            return 0;
        default:
            return 0;
        }
    }

void REFRRecord::GetFieldArray(const unsigned int Field, void **FieldValues)
    {
    switch(Field)
        {
        case 15: //unused1
            if(XLOC.IsLoaded())
                *FieldValues = &XLOC->unused1[0];
            else
                *FieldValues = NULL;
            return;
        case 17: //unused2
            if(XLOC.IsLoaded())
                *FieldValues = &XLOC->unused2[0];
            else
                *FieldValues = NULL;
            return;
        case 19: //unused3
            if(XLOC.IsLoaded())
                *FieldValues = &XLOC->unused3[0];
            else
                *FieldValues = NULL;
            return;
        case 25: //unused4
            if(XESP.IsLoaded())
                *FieldValues = &XESP->unused1[0];
            else
                *FieldValues = NULL;
            return;
        case 42: //markerUnused
            if(Marker.IsLoaded() && Marker->TNAM.IsLoaded())
                *FieldValues = &Marker->TNAM.value.unused1;
            else
                *FieldValues = NULL;
            return;
        default:
            *FieldValues = NULL;
            return;
        }
    }

void REFRRecord::SetField(const unsigned int Field, char *FieldValue)
    {
    switch(Field)
        {
        case 5: //eid
            EDID.Copy(FieldValue);
            break;
        case 34: //unknownXPCIString
            XPCI.Load();
            XPCI->FULL.Copy(FieldValue);
            break;
        case 40: //markerName
            Marker.Load();
            Marker->FULL.Copy(FieldValue);
            break;
        default:
            return;
        }
    return;
    }

void REFRRecord::SetOtherField(const unsigned int Field, unsigned int FieldValue)
    {
    switch(Field)
        {
        case 6: //base
            NAME.value.fid = FieldValue;
            break;
        case 7: //destination
            XTEL.Load();
            XTEL->destinationFid = FieldValue;
            break;
        case 16: //lockKey
            XLOC.Load();
            XLOC->key = FieldValue;
            break;
        case 20: //owner
            Ownership.Load();
            Ownership->XOWN.value.fid = FieldValue;
            break;
        case 22: //globalVariable
            Ownership.Load();
            Ownership->XGLB.Load();
            Ownership->XGLB->fid = FieldValue;
            break;
        case 23: //parent
            XESP.Load();
            XESP->parent = FieldValue;
            break;
        case 26: //target
            XTRG.Load();
            XTRG->fid = FieldValue;
            break;
        case 27: //seed
            XSED.Load();
            XSED->isOffset = false;
            XSED->seed = FieldValue;
            break;
        case 33: //unknownXPCIFormID
            XPCI.Load();
            XPCI->XPCI.Load();
            XPCI->XPCI->fid = FieldValue;
            break;
        case 36: //unknownXRTMFormID
            XRTM.Load();
            XRTM->fid = FieldValue;
            break;
        case 37: //actionFlags
            XACT.Load();
            XACT->flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void REFRRecord::SetField(const unsigned int Field, float FieldValue)
    {
    switch(Field)
        {
        case 8: //destinationPosX
            XTEL.Load();
            XTEL->destination.posX = FieldValue;
            break;
        case 9: //destinationPosY
            XTEL.Load();
            XTEL->destination.posY = FieldValue;
            break;
        case 10: //destinationPosZ
            XTEL.Load();
            XTEL->destination.posZ = FieldValue;
            break;
        case 11: //destinationRotX
            XTEL.Load();
            XTEL->destination.rotX = FieldValue;
            break;
        case 12: //destinationRotY
            XTEL.Load();
            XTEL->destination.rotY = FieldValue;
            break;
        case 13: //destinationRotZ
            XTEL.Load();
            XTEL->destination.rotZ = FieldValue;
            break;
        case 28: //lod1
            XLOD.Load();
            XLOD->lod1 = FieldValue;
            break;
        case 29: //lod2
            XLOD.Load();
            XLOD->lod2 = FieldValue;
            break;
        case 30: //lod3
            XLOD.Load();
            XLOD->lod3 = FieldValue;
            break;
        case 31: //charge
            XCHG.Load();
            XCHG->charge = FieldValue;
            break;
        case 43: //scale
            XSCL.Load();
            XSCL->scale = FieldValue;
            break;
        case 45: //posX
            DATA.value.posX = FieldValue;
            break;
        case 46: //posY
            DATA.value.posY = FieldValue;
            break;
        case 47: //posZ
            DATA.value.posZ = FieldValue;
            break;
        case 48: //rotX
            DATA.value.rotX = FieldValue;
            break;
        case 49: //rotY
            DATA.value.rotY = FieldValue;
            break;
        case 50: //rotZ
            DATA.value.rotZ = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void REFRRecord::SetField(const unsigned int Field, unsigned char FieldValue)
    {
    switch(Field)
        {
        case 14: //lockLevel
            XLOC.Load();
            XLOC->level = FieldValue;
            break;
        case 18: //lockFlags
            XLOC.Load();
            XLOC->flags = FieldValue;
            break;
        case 24: //parentFlags
            XESP.Load();
            XESP->flags = FieldValue;
            break;
        case 27: //seed
            XSED.Load();
            XSED->isOffset = true;
            XSED->offset = FieldValue;
            break;
        case 39: //markerFlags
            Marker.Load();
            Marker->FNAM.value.flags = FieldValue;
            break;
        case 41: //markerType
            Marker.Load();
            Marker->TNAM.value.markerType = FieldValue;
            break;
        case 44: //soul
            XSOL.Load();
            XSOL->flags = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

void REFRRecord::SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize)
    {
    switch(Field)
        {
        case 15: //unused1
            if(nSize != 3)
                return;
            XLOC.Load();
            XLOC->unused1[0] = FieldValue[0];
            XLOC->unused1[1] = FieldValue[1];
            XLOC->unused1[2] = FieldValue[2];
            break;
        case 17: //unused2
            if(nSize != 4)
                return;
            XLOC.Load();
            XLOC->unused2[0] = FieldValue[0];
            XLOC->unused2[1] = FieldValue[1];
            XLOC->unused2[2] = FieldValue[2];
            XLOC->unused2[3] = FieldValue[3];
            break;
        case 19: //unused3
            if(nSize != 3)
                return;
            XLOC.Load();
            XLOC->unused3[0] = FieldValue[0];
            XLOC->unused3[1] = FieldValue[1];
            XLOC->unused3[2] = FieldValue[2];
            break;
        case 25: //unused4
            if(nSize != 3)
                return;
            XESP.Load();
            XESP->unused1[0] = FieldValue[0];
            XESP->unused1[1] = FieldValue[1];
            XESP->unused1[2] = FieldValue[2];
            break;
        case 42: //markerUnused
            if(nSize != 1)
                return;
            Marker.Load();
            Marker->TNAM.value.unused1 = FieldValue[0];
            break;
        default:
            return;
        }
    return;
    }

void REFRRecord::SetField(const unsigned int Field, int FieldValue)
    {
    switch(Field)
        {
        case 21: //rank
            Ownership.Load();
            Ownership->XRNK.Load();
            Ownership->XRNK->rank = FieldValue;
            break;
        case 32: //health
            XHLT.Load();
            XHLT->health = FieldValue;
            break;
        case 35: //levelMod
            XLCM.Load();
            XLCM->levelMod = FieldValue;
            break;
        case 38: //count
            XCNT.Load();
            XCNT->count = FieldValue;
            break;
        default:
            return;
        }
    return;
    }

int REFRRecord::DeleteField(const unsigned int Field)
    {
    REFRXTEL defaultXTEL;
    REFRXLOC defaultXLOC;
    GENXESP defaultXESP;
    GENXLOD defaultXLOD;
    REFRTNAM defaultTNAM;
    GENPOSDATA defaultDATA;
    switch(Field)
        {
        case 5: //eid
            EDID.Unload();
            break;
        case 6: //base
            NAME.Unload();
            break;
        case 7: //destination
            if(XTEL.IsLoaded())
                XTEL->destinationFid = defaultXTEL.destinationFid;
            break;
        case 8: //destinationPosX
            if(XTEL.IsLoaded())
                XTEL->destination.posX = defaultXTEL.destination.posX;
            break;
        case 9: //destinationPosY
            if(XTEL.IsLoaded())
                XTEL->destination.posY = defaultXTEL.destination.posY;
            break;
        case 10: //destinationPosZ
            if(XTEL.IsLoaded())
                XTEL->destination.posZ = defaultXTEL.destination.posZ;
            break;
        case 11: //destinationRotX
            if(XTEL.IsLoaded())
                XTEL->destination.rotX = defaultXTEL.destination.rotX;
            break;
        case 12: //destinationRotY
            if(XTEL.IsLoaded())
                XTEL->destination.rotY = defaultXTEL.destination.rotY;
            break;
        case 13: //destinationRotZ
            if(XTEL.IsLoaded())
                XTEL->destination.rotZ = defaultXTEL.destination.rotZ;
            break;
        case 14: //lockLevel
            if(XLOC.IsLoaded())
                XLOC->level = defaultXLOC.level;
            break;
        case 15: //unused1
            if(XLOC.IsLoaded())
                {
                XLOC->unused1[0] = defaultXLOC.unused1[0];
                XLOC->unused1[1] = defaultXLOC.unused1[1];
                XLOC->unused1[2] = defaultXLOC.unused1[2];
                }
            break;
        case 16: //lockKey
            if(XLOC.IsLoaded())
                XLOC->key = defaultXLOC.key;
            break;
        case 17: //unused2
            if(XLOC.IsLoaded())
                {
                XLOC->unused2[0] = defaultXLOC.unused2[0];
                XLOC->unused2[1] = defaultXLOC.unused2[1];
                XLOC->unused2[2] = defaultXLOC.unused2[2];
                XLOC->unused2[3] = defaultXLOC.unused2[3];
                }
            break;
        case 18: //lockFlags
            if(XLOC.IsLoaded())
                XLOC->flags = defaultXLOC.flags;
            break;
        case 19: //unused3
            if(XLOC.IsLoaded())
                {
                XLOC->unused3[0] = defaultXLOC.unused3[0];
                XLOC->unused3[1] = defaultXLOC.unused3[1];
                XLOC->unused3[2] = defaultXLOC.unused3[2];
                }
            break;
        case 20: //owner
            if(Ownership.IsLoaded())
                Ownership->XOWN.Unload();
            break;
        case 21: //rank
            if(Ownership.IsLoaded())
                Ownership->XRNK.Unload();
            break;
        case 22: //globalVariable
            if(Ownership.IsLoaded())
                Ownership->XGLB.Unload();
            break;
        case 23: //parent
            if(XESP.IsLoaded())
                XESP->parent = defaultXESP.parent;
            break;
        case 24: //parentFlags
            if(XESP.IsLoaded())
                XESP->flags = defaultXESP.flags;
            break;
        case 25: //unused4
            if(XESP.IsLoaded())
                {
                XESP->unused1[0] = defaultXESP.unused1[0];
                XESP->unused1[1] = defaultXESP.unused1[1];
                XESP->unused1[2] = defaultXESP.unused1[2];
                }
            break;
        case 26: //target
            XTRG.Unload();
            break;
        case 27: //seed
            XSED.Unload();
            break;
        case 28: //lod1
            if(XLOD.IsLoaded())
                XLOD->lod1 = defaultXLOD.lod1;
            break;
        case 29: //lod2
            if(XLOD.IsLoaded())
                XLOD->lod2 = defaultXLOD.lod2;
            break;
        case 30: //lod3
            if(XLOD.IsLoaded())
                XLOD->lod3 = defaultXLOD.lod3;
            break;
        case 31: //charge
            XCHG.Unload();
            break;
        case 32: //health
            XHLT.Unload();
            break;
        case 33: //unknownXPCIFormID
            if(XPCI.IsLoaded())
                XPCI->XPCI.Unload();
            break;
        case 34: //unknownXPCIString
            if(XPCI.IsLoaded())
                XPCI->FULL.Unload();
            break;
        case 35: //levelMod
            XLCM.Unload();
            break;
        case 36: //unknownXRTMFormID
            XRTM.Unload();
            break;
        case 37: //actionFlags
            XACT.Unload();
            break;
        case 38: //count
            XCNT.Unload();
            break;
        case 39: //markerFlags
            if(Marker.IsLoaded())
                Marker->FNAM.Unload();
            break;
        case 40: //markerName
            if(Marker.IsLoaded())
                Marker->FULL.Unload();
            break;
        case 41: //markerType
            if(Marker.IsLoaded())
                Marker->TNAM.value.markerType = defaultTNAM.markerType;
            break;
        case 42: //markerUnused
            if(Marker.IsLoaded())
                Marker->TNAM.value.unused1 = defaultTNAM.unused1;
            break;
        case 43: //scale
            XSCL.Unload();
            break;
        case 44: //soul
            XSOL.Unload();
            break;
        case 45: //posX
            DATA.value.posX = defaultDATA.posX;
            break;
        case 46: //posY
            DATA.value.posY = defaultDATA.posY;
            break;
        case 47: //posZ
            DATA.value.posZ = defaultDATA.posZ;
            break;
        case 48: //rotX
            DATA.value.rotX = defaultDATA.rotX;
            break;
        case 49: //rotY
            DATA.value.rotY = defaultDATA.rotY;
            break;
        case 50: //rotZ
            DATA.value.rotZ = defaultDATA.rotZ;
            break;
        default:
            return 0;
        }
    return 1;
    }
