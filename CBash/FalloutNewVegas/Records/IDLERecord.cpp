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
#include "IDLERecord.h"

namespace FNV
{
IDLERecord::IDLEDATA::IDLEDATA():
    group(0),
    minLooping(0),
    maxLooping(0),
    unused1(0),
    replayDelay(0),
    flags(0),
    unused2(0)
    {
    //
    }

IDLERecord::IDLEDATA::~IDLEDATA()
    {
    //
    }

bool IDLERecord::IDLEDATA::operator ==(const IDLEDATA &other) const
    {
    return (group == other.group &&
            minLooping == other.minLooping &&
            maxLooping == other.maxLooping &&
            replayDelay == other.replayDelay &&
            flags == other.flags);
    }

bool IDLERecord::IDLEDATA::operator !=(const IDLEDATA &other) const
    {
    return !(*this == other);
    }

IDLERecord::IDLERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IDLERecord::IDLERecord(IDLERecord *srcRecord):
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

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    MODL = srcRecord->MODL;
    CTDA = srcRecord->CTDA;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    return;
    }

IDLERecord::~IDLERecord()
    {
    //
    }

bool IDLERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(UINT32 ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);
    for(UINT32 ListIndex = 0; ListIndex < ANAM.value.size(); ListIndex++)
        op.Accept(ANAM.value[ListIndex]);

    return op.Stop();
    }

bool IDLERecord::IsNoAttacking()
    {
    return (DATA.value.flags & fIsNoAttacking) != 0;
    }

void IDLERecord::IsNoAttacking(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsNoAttacking) : (DATA.value.flags & ~fIsNoAttacking);
    }

bool IDLERecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void IDLERecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

bool IDLERecord::IsIdle()
    {
    return ((DATA.value.group & ~0xC0) == eIdle);
    }

void IDLERecord::IsIdle(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    else if(IsIdle())
        DATA.value.group = DATA.value.group & 0xC0 | eMovement;
    }

bool IDLERecord::IsMovement()
    {
    return ((DATA.value.group & ~0xC0) == eMovement);
    }

void IDLERecord::IsMovement(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eMovement;
    else if(IsMovement())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsLeftArm()
    {
    return ((DATA.value.group & ~0xC0) == eLeftArm);
    }

void IDLERecord::IsLeftArm(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eLeftArm;
    else if(IsLeftArm())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsLeftHand()
    {
    return ((DATA.value.group & ~0xC0) == eLeftHand);
    }

void IDLERecord::IsLeftHand(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eLeftHand;
    else if(IsLeftHand())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsWeapon()
    {
    return ((DATA.value.group & ~0xC0) == eWeapon);
    }

void IDLERecord::IsWeapon(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eWeapon;
    else if(IsWeapon())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsWeaponUp()
    {
    return ((DATA.value.group & ~0xC0) == eWeaponUp);
    }

void IDLERecord::IsWeaponUp(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eWeaponUp;
    else if(IsWeaponUp())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsWeaponDown()
    {
    return ((DATA.value.group & ~0xC0) == eWeaponDown);
    }

void IDLERecord::IsWeaponDown(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eWeaponDown;
    else if(IsWeaponDown())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsSpecialIdle()
    {
    return ((DATA.value.group & ~0xC0) == eSpecialIdle);
    }

void IDLERecord::IsSpecialIdle(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eSpecialIdle;
    else if(IsLeftArm())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsWholeBody()
    {
    return ((DATA.value.group & ~0xC0) == eWholeBody);
    }

void IDLERecord::IsWholeBody(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eWholeBody;
    else if(IsWholeBody())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsUpperBody()
    {
    return ((DATA.value.group & ~0xC0) == eUpperBody);
    }

void IDLERecord::IsUpperBody(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eUpperBody;
    else if(IsUpperBody())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsType(UINT8 Type)
    {
    return ((DATA.value.group & ~0xC0) == (Type & ~0xC0));
    }

void IDLERecord::SetType(UINT8 Type)
    {
    DATA.value.group = DATA.value.group & 0xC0 | (Type & ~0xC0);
    }

bool IDLERecord::IsUnknown1()
    {
    return (DATA.value.group & fIsUnknown1) != 0;
    }

void IDLERecord::IsUnknown1(bool value)
    {
    DATA.value.group = value ? (DATA.value.group | fIsUnknown1) : (DATA.value.group & ~fIsUnknown1);
    }

bool IDLERecord::IsNotReturnFile()
    {
    return (DATA.value.group & fIsNotReturnFile) != 0;
    }

void IDLERecord::IsNotReturnFile(bool value)
    {
    DATA.value.group = value ? (DATA.value.group | fIsNotReturnFile) : (DATA.value.group & ~fIsNotReturnFile);
    }

bool IDLERecord::IsReturnFile()
    {
    return !(IsNotReturnFile());
    }

void IDLERecord::IsReturnFile(bool value)
    {
    IsNotReturnFile(!value);
    }

bool IDLERecord::IsIdleFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? (((DATA.value.group & 0xC0) & (Mask & 0xC0)) == Mask) : (((DATA.value.group & 0xC0) & (Mask & 0xC0)) != 0);
    }

void IDLERecord::SetIdleFlagMask(UINT8 Mask)
    {
    DATA.value.group = DATA.value.group & ~0xC0 | (Mask & 0xC0);
    }

UINT32 IDLERecord::GetType()
    {
    return REV32(IDLE);
    }

STRING IDLERecord::GetStrType()
    {
    return "IDLE";
    }

SINT32 IDLERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case REV32(XXXX):
                curPos += 2;
                _readBuffer(&subSize, buffer, 4, curPos);
                _readBuffer(&subType, buffer, 4, curPos);
                curPos += 2;
                break;
            default:
                subSize = 0;
                _readBuffer(&subSize, buffer, 2, curPos);
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, curPos);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize, curPos);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IDLE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 IDLERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    MODL.Unload();
    CTDA.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 IDLERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    MODL.Write(writer);
    CTDA.Write(REV32(CTDA), writer, true);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool IDLERecord::operator ==(const IDLERecord &other) const
    {
    return (ANAM == other.ANAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            CTDA == other.CTDA);
    }

bool IDLERecord::operator !=(const IDLERecord &other) const
    {
    return !(*this == other);
    }
}