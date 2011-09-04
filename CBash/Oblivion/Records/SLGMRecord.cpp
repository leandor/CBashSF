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
#include "SLGMRecord.h"

namespace Ob
{
SLGMRecord::SLGMRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SLGMRecord::SLGMRecord(SLGMRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    SCRI = srcRecord->SCRI;
    DATA = srcRecord->DATA;
    SOUL = srcRecord->SOUL;
    SLCP = srcRecord->SLCP;
    }

SLGMRecord::~SLGMRecord()
    {
    //
    }

bool SLGMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);

    return op.Stop();
    }

bool SLGMRecord::IsNoSoul()
    {
    return (SOUL.value == eNone);
    }

void SLGMRecord::IsNoSoul(bool value)
    {
    if(value)
        SOUL.value = eNone;
    else if(IsNoSoul())
        SOUL.value = ePetty;
    }

bool SLGMRecord::IsPettySoul()
    {
    return (SOUL.value == ePetty);
    }

void SLGMRecord::IsPettySoul(bool value)
    {
    if(value)
        SOUL.value = ePetty;
    else if(IsPettySoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsLesserSoul()
    {
    return (SOUL.value == eLesser);
    }

void SLGMRecord::IsLesserSoul(bool value)
    {
    if(value)
        SOUL.value = eLesser;
    else if(IsLesserSoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsCommonSoul()
    {
    return (SOUL.value == eCommon);
    }

void SLGMRecord::IsCommonSoul(bool value)
    {
    if(value)
        SOUL.value = eCommon;
    else if(IsCommonSoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsGreaterSoul()
    {
    return (SOUL.value == eGreater);
    }

void SLGMRecord::IsGreaterSoul(bool value)
    {
    if(value)
        SOUL.value = eGreater;
    else if(IsGreaterSoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsGrandSoul()
    {
    return (SOUL.value == eGrand);
    }

void SLGMRecord::IsGrandSoul(bool value)
    {
    if(value)
        SOUL.value = eGrand;
    else if(IsGrandSoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsSoul(UINT8 Type)
    {
    return (SOUL.value == Type);
    }

void SLGMRecord::SetSoul(UINT8 Type)
    {
    SOUL.value = Type;
    }

bool SLGMRecord::IsNoCapacity()
    {
    return (SLCP.value== eNone);
    }

void SLGMRecord::IsNoCapacity(bool value)
    {
    if(value)
        SLCP.value= eNone;
    else if(IsNoCapacity())
        SLCP.value= ePetty;
    }

bool SLGMRecord::IsPettyCapacity()
    {
    return (SLCP.value== ePetty);
    }

void SLGMRecord::IsPettyCapacity(bool value)
    {
    if(value)
        SLCP.value= ePetty;
    else if(IsPettyCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsLesserCapacity()
    {
    return (SLCP.value== eLesser);
    }

void SLGMRecord::IsLesserCapacity(bool value)
    {
    if(value)
        SLCP.value= eLesser;
    else if(IsLesserCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsCommonCapacity()
    {
    return (SLCP.value== eCommon);
    }

void SLGMRecord::IsCommonCapacity(bool value)
    {
    if(value)
        SLCP.value= eCommon;
    else if(IsCommonCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsGreaterCapacity()
    {
    return (SLCP.value== eGreater);
    }

void SLGMRecord::IsGreaterCapacity(bool value)
    {
    if(value)
        SLCP.value= eGreater;
    else if(IsGreaterCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsGrandCapacity()
    {
    return (SLCP.value== eGrand);
    }

void SLGMRecord::IsGrandCapacity(bool value)
    {
    if(value)
        SLCP.value= eGrand;
    else if(IsGrandCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsCapacity(UINT8 Type)
    {
    return (SLCP.value== Type);
    }

void SLGMRecord::SetCapacity(UINT8 Type)
    {
    SLCP.value= Type;
    }

UINT32 SLGMRecord::GetType()
    {
    return REV32(SLGM);
    }

STRING SLGMRecord::GetStrType()
    {
    return "SLGM";
    }

SINT32 SLGMRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(SOUL):
                SOUL.Read(buffer, subSize);
                break;
            case REV32(SLCP):
                SLCP.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SLGM: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 SLGMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    SCRI.Unload();
    DATA.Unload();
    SOUL.Unload();
    SLCP.Unload();
    return 1;
    }

SINT32 SLGMRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(SCRI);
    WRITE(DATA);
    WRITE(SOUL);
    WRITE(SLCP);
    return -1;
    }

bool SLGMRecord::operator ==(const SLGMRecord &other) const
    {
    return (SCRI == other.SCRI &&
            SOUL == other.SOUL &&
            SLCP == other.SLCP &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MODL == other.MODL);
    }

bool SLGMRecord::operator !=(const SLGMRecord &other) const
    {
    return !(*this == other);
    }

bool SLGMRecord::equals(Record *other)
    {
    return *this == *(SLGMRecord *)other;
    }
}