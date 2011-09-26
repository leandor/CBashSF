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
#include "CHALRecord.h"

namespace FNV
{
CHALRecord::CHALRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CHALRecord::CHALRecord(CHALRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    SCRI = srcRecord->SCRI;
    DESC = srcRecord->DESC;
    DATA = srcRecord->DATA;
    SNAM = srcRecord->SNAM;
    XNAM = srcRecord->XNAM;
    return;
    }

CHALRecord::~CHALRecord()
    {
    //
    }

bool CHALRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);
    if(XNAM.IsLoaded())
        op.Accept(XNAM->value);

    return op.Stop();
    }

bool CHALRecord::IsStartDisabled()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsStartDisabled) != 0;
    }

void CHALRecord::IsStartDisabled(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsStartDisabled) : (Dummy->flags & ~fIsStartDisabled);
    }

bool CHALRecord::IsRecurring()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRecurring) != 0;
    }

void CHALRecord::IsRecurring(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRecurring) : (Dummy->flags & ~fIsRecurring);
    }

bool CHALRecord::IsShowZeroProgress()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsShowZeroProgress) != 0;
    }

void CHALRecord::IsShowZeroProgress(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsShowZeroProgress) : (Dummy->flags & ~fIsShowZeroProgress);
    }

bool CHALRecord::Is0FlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CHALRecord::Set0FlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CHALRecord::IsKillFromList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eKillFromList);
    }

void CHALRecord::IsKillFromList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eKillFromList : eDummyDefault;
    }

bool CHALRecord::IsKillFormID()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eKillFormID);
    }

void CHALRecord::IsKillFormID(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eKillFormID : eDummyDefault;
    }

bool CHALRecord::IsKillInCategory()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eKillInCategory);
    }

void CHALRecord::IsKillInCategory(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eKillInCategory : eDummyDefault;
    }

bool CHALRecord::IsHitEnemy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHitEnemy);
    }

void CHALRecord::IsHitEnemy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHitEnemy : eDummyDefault;
    }

bool CHALRecord::IsDiscoverMapMarker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDiscoverMapMarker);
    }

void CHALRecord::IsDiscoverMapMarker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDiscoverMapMarker : eDummyDefault;
    }

bool CHALRecord::IsUseItem()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUseItem);
    }

void CHALRecord::IsUseItem(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUseItem : eDummyDefault;
    }

bool CHALRecord::IsGetItem()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGetItem);
    }

void CHALRecord::IsGetItem(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGetItem : eDummyDefault;
    }

bool CHALRecord::IsUseSkill()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUseSkill);
    }

void CHALRecord::IsUseSkill(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUseSkill : eDummyDefault;
    }

bool CHALRecord::IsDoDamage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDoDamage);
    }

void CHALRecord::IsDoDamage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDoDamage : eDummyDefault;
    }

bool CHALRecord::IsUseItemFromList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUseItemFromList);
    }

void CHALRecord::IsUseItemFromList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eUseItemFromList : eDummyDefault;
    }

bool CHALRecord::IsGetItemFromList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGetItemFromList);
    }

void CHALRecord::IsGetItemFromList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGetItemFromList : eDummyDefault;
    }

bool CHALRecord::IsMiscStat()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMiscStat);
    }

void CHALRecord::IsMiscStat(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMiscStat : eDummyDefault;
    }

bool CHALRecord::Is0Type(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void CHALRecord::Set0Type(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CHALRecord::GetType()
    {
    return REV32(CHAL);
    }

STRING CHALRecord::GetStrType()
    {
    return "CHAL";
    }

SINT32 CHALRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                EDID.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CHAL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 CHALRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    SCRI.Unload();
    DESC.Unload();
    DATA.Unload();
    SNAM.Unload();
    XNAM.Unload();
    return 1;
    }

SINT32 CHALRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(SCRI);
    WRITE(DESC);
    WRITE(DATA);
    WRITE(SNAM);
    WRITE(XNAM);

    return -1;
    }

bool CHALRecord::operator ==(const CHALRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            SCRI == other.SCRI &&
            DESC.equals(other.DESC) &&
            DATA == other.DATA &&
            SNAM == other.SNAM &&
            XNAM == other.XNAM);
    }

bool CHALRecord::operator !=(const CHALRecord &other) const
    {
    return !(*this == other);
    }

bool CHALRecord::equals(const Record *other) const
    {
    return *this == *(CHALRecord *)other;
    }
}