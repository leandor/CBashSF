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

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

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
    if(value)
        Dummy->flags |= fIsStartDisabled;
    else
        Dummy->flags &= ~fIsStartDisabled;
    }

bool CHALRecord::IsRecurring()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRecurring) != 0;
    }

void CHALRecord::IsRecurring(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRecurring;
    else
        Dummy->flags &= ~fIsRecurring;
    }

bool CHALRecord::IsShowZeroProgress()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsShowZeroProgress) != 0;
    }

void CHALRecord::IsShowZeroProgress(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsShowZeroProgress;
    else
        Dummy->flags &= ~fIsShowZeroProgress;
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
    if(value)
        Dummy->flags = eKillFromList;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsKillFormID()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eKillFormID);
    }

void CHALRecord::IsKillFormID(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eKillFormID;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsKillInCategory()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eKillInCategory);
    }

void CHALRecord::IsKillInCategory(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eKillInCategory;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsHitEnemy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHitEnemy);
    }

void CHALRecord::IsHitEnemy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHitEnemy;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsDiscoverMapMarker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDiscoverMapMarker);
    }

void CHALRecord::IsDiscoverMapMarker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDiscoverMapMarker;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsUseItem()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUseItem);
    }

void CHALRecord::IsUseItem(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eUseItem;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsGetItem()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGetItem);
    }

void CHALRecord::IsGetItem(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eGetItem;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsUseSkill()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUseSkill);
    }

void CHALRecord::IsUseSkill(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eUseSkill;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsDoDamage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDoDamage);
    }

void CHALRecord::IsDoDamage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDoDamage;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsUseItemFromList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUseItemFromList);
    }

void CHALRecord::IsUseItemFromList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eUseItemFromList;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsGetItemFromList()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGetItemFromList);
    }

void CHALRecord::IsGetItemFromList(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eGetItemFromList;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::IsMiscStat()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMiscStat);
    }

void CHALRecord::IsMiscStat(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eMiscStat;
    else
        Dummy->flags = eDummyDefault;
    }

bool CHALRecord::Is0Type(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CHALRecord::Set0Type(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CHALRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;

    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(XNAM.IsLoaded())
        TotSize += XNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 CHALRecord::GetType()
    {
    return 'LAHC';
    }

STRING CHALRecord::GetStrType()
    {
    return "CHAL";
    }

SINT32 CHALRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case 'XXXX':
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
            case 'DIDE':
                EDID.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'CSED':
                DESC.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CHAL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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

SINT32 CHALRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord('IRCS', SCRI.value, SCRI.GetSize());

    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord('CSED', DESC.value, DESC.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(XNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANX', XNAM.value, XNAM.GetSize());

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
}