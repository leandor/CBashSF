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
#include "IPCTRecord.h"

namespace FNV
{
IPCTRecord::IPCTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IPCTRecord::IPCTRecord(IPCTRecord *srcRecord):
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

    DATA = srcRecord->DATA;
    DODT = srcRecord->DODT;
    DNAM = srcRecord->DNAM;
    SNAM = srcRecord->SNAM;
    NAM1 = srcRecord->NAM1;
    return;
    }

IPCTRecord::~IPCTRecord()
    {
    //
    }

bool IPCTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(DNAM.IsLoaded())
        op.Accept(DNAM->value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);
    if(NAM1.IsLoaded())
        op.Accept(NAM1->value);

    return op.Stop();
    }

bool IPCTRecord::IsNoDecalData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoDecalData) != 0;
    }

void IPCTRecord::IsNoDecalData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoDecalData) : (Dummy->flags & ~fIsNoDecalData);
    }

bool IPCTRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void IPCTRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool IPCTRecord::IsLoud()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLoud);
    }

void IPCTRecord::IsLoud(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLoud : eDummyDefault;
    }

bool IPCTRecord::IsNormal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNormal);
    }

void IPCTRecord::IsNormal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNormal : eDummyDefault;
    }

bool IPCTRecord::IsSilent()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSilent);
    }

void IPCTRecord::IsSilent(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSilent : eDummyDefault;
    }

bool IPCTRecord::IsObjectParallax()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsParallax) != 0 : false;
    }

void IPCTRecord::IsObjectParallax(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsParallax) : (DODT->flags & ~fIsParallax);
    }

bool IPCTRecord::IsObjectAlphaBlending()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsAlphaBlending) != 0 : false;
    }

void IPCTRecord::IsObjectAlphaBlending(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsAlphaBlending) : (DODT->flags & ~fIsAlphaBlending);
    }

bool IPCTRecord::IsObjectAlphaTesting()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsAlphaTesting) != 0 : false;
    }

void IPCTRecord::IsObjectAlphaTesting(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsAlphaTesting) : (DODT->flags & ~fIsAlphaTesting);
    }

bool IPCTRecord::IsObjectFlagMask(UINT8 Mask, bool Exact)
    {
    if(!DODT.IsLoaded()) return false;
    return Exact ? ((DODT->flags & Mask) == Mask) : ((DODT->flags & Mask) != 0);
    }

void IPCTRecord::SetObjectFlagMask(UINT8 Mask)
    {
    DODT.Load();
    DODT->flags = Mask;
    }

bool IPCTRecord::IsSoundLevelType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void IPCTRecord::SetSoundLevelType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 IPCTRecord::GetType()
    {
    return REV32(IPCT);
    }

STRING IPCTRecord::GetStrType()
    {
    return "IPCT";
    }

SINT32 IPCTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(DODT):
                DODT.Read(buffer, subSize, curPos);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IPCT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 IPCTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    DATA.Unload();
    DODT.Unload();
    DNAM.Unload();
    SNAM.Unload();
    NAM1.Unload();
    return 1;
    }

SINT32 IPCTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);

    MODL.Write(writer);

    WRITE(DATA);
    WRITE(DODT);
    WRITE(DNAM);
    WRITE(SNAM);
    WRITE(NAM1);

    return -1;
    }

bool IPCTRecord::operator ==(const IPCTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            DATA == other.DATA &&
            DODT == other.DODT &&
            DNAM == other.DNAM &&
            SNAM == other.SNAM &&
            NAM1 == other.NAM1);
    }

bool IPCTRecord::operator !=(const IPCTRecord &other) const
    {
    return !(*this == other);
    }
}