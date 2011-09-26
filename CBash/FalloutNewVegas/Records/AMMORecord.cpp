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
#include "..\..\Common.h"
#include "AMMORecord.h"

namespace FNV
{
AMMORecord::AMMODATA::AMMODATA():
    speed(0.0f),
    flags(0),
    value(0),
    clipRounds(0)
    {
    memset(&unused[0], 0x00, sizeof(unused));
    }

AMMORecord::AMMODATA::~AMMODATA()
    {
    //
    }

bool AMMORecord::AMMODATA::operator ==(const AMMODATA &other) const
    {
    return (flags == other.flags &&
            value == other.value &&
            clipRounds == other.clipRounds &&
            AlmostEqual(speed,other.speed,2));
    }

bool AMMORecord::AMMODATA::operator !=(const AMMODATA &other) const
    {
    return !(*this == other);
    }

AMMORecord::AMMODAT2::AMMODAT2():
    projectilesPerShot(0),
    projectile(0),
    weight(0.0f),
    consumedAmmo(0),
    consumedPercentage(0.0f)
    {
    //
    }

AMMORecord::AMMODAT2::~AMMODAT2()
    {
    //
    }

bool AMMORecord::AMMODAT2::operator ==(const AMMODAT2 &other) const
    {
    return (projectilesPerShot == other.projectilesPerShot &&
            projectile == other.projectile &&
            consumedAmmo == other.consumedAmmo &&
            AlmostEqual(weight,other.weight,2) &&
            AlmostEqual(consumedPercentage,other.consumedPercentage,2));
    }

bool AMMORecord::AMMODAT2::operator !=(const AMMODAT2 &other) const
    {
    return !(*this == other);
    }

AMMORecord::AMMORecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

AMMORecord::AMMORecord(AMMORecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SCRI = srcRecord->SCRI;
    Destructable = srcRecord->Destructable;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    DATA = srcRecord->DATA;
    DAT2 = srcRecord->DAT2;
    ONAM = srcRecord->ONAM;
    QNAM = srcRecord->QNAM;
    RCIL = srcRecord->RCIL;
    return;
    }

AMMORecord::~AMMORecord()
    {
    //
    }

bool AMMORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    if(DAT2.IsLoaded())
        {
        op.Accept(DAT2->projectile);
        op.Accept(DAT2->consumedAmmo);
        }
    for(UINT32 x = 0; x < RCIL.value.size(); ++x)
        op.Accept(RCIL.value[x]);

    return op.Stop();
    }

bool AMMORecord::IsNotNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void AMMORecord::IsNotNormalWeapon(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNotNormalWeapon) : (DATA.value.flags & ~fIsNotNormalWeapon);
    }

bool AMMORecord::IsNonPlayable()
    {
    return (DATA.value.flags & fIsNonPlayable) != 0;
    }

void AMMORecord::IsNonPlayable(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNonPlayable) : (DATA.value.flags & ~fIsNonPlayable);
    }

bool AMMORecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void AMMORecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 AMMORecord::GetType()
    {
    return REV32(AMMO);
    }

STRING AMMORecord::GetStrType()
    {
    return "AMMO";
    }

SINT32 AMMORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(DAT2):
                DAT2.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                ONAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(QNAM):
                QNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(RCIL):
                RCIL.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  AMMO: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 AMMORecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    SCRI.Unload();
    Destructable.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    DATA.Unload();
    DAT2.Unload();
    ONAM.Unload();
    QNAM.Unload();
    RCIL.Unload();
    return 1;
    }

SINT32 AMMORecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(SCRI);
    Destructable.Write(writer);
    WRITE(YNAM);
    WRITE(ZNAM);
    WRITE(DATA);
    WRITE(DAT2);
    WRITE(ONAM);
    WRITE(QNAM);
    WRITE(RCIL);
    return -1;
    }

bool AMMORecord::operator ==(const AMMORecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            DATA == other.DATA &&
            DAT2 == other.DAT2 &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            ONAM.equalsi(other.ONAM) &&
            QNAM.equalsi(other.QNAM) &&
            RCIL == other.RCIL &&
            MODL == other.MODL &&
            Destructable == other.Destructable);
    }

bool AMMORecord::operator !=(const AMMORecord &other) const
    {
    return !(*this == other);
    }

bool AMMORecord::equals(Record *other)
    {
    return *this == *(AMMORecord *)other;
    }
}