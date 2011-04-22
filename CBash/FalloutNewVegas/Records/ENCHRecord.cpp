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
#include "ENCHRecord.h"

namespace FNV
{
ENCHRecord::ENCHRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ENCHRecord::ENCHRecord(ENCHRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    ENIT = srcRecord->ENIT;
    if(srcRecord->EFID.IsLoaded())
        {
        EFID.Load();
        EFID->EFID = srcRecord->EFID->EFID;
        EFID->EFIT = srcRecord->EFID->EFIT;
        EFID->CTDA = srcRecord->EFID->CTDA;
        }
    return;
    }

ENCHRecord::~ENCHRecord()
    {
    //
    }

bool ENCHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(EFID.IsLoaded() && EFID->EFID.IsLoaded())
        op.Accept(EFID->EFID->value);
    if(EFID.IsLoaded() && EFID->CTDA.IsLoaded())
        op.Accept(EFID->CTDA->value);

    return op.Stop();
    }

bool ENCHRecord::IsNoAutoCalc()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoAutoCalc) != 0;
    }

void ENCHRecord::IsNoAutoCalc(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsNoAutoCalc;
    else
        Dummy->flags &= ~fIsNoAutoCalc;
    }

bool ENCHRecord::IsHideEffect()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHideEffect) != 0;
    }

void ENCHRecord::IsHideEffect(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHideEffect;
    else
        Dummy->flags &= ~fIsHideEffect;
    }

bool ENCHRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void ENCHRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool ENCHRecord::IsWeapon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eWeapon);
    }

void ENCHRecord::IsWeapon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eWeapon;
    else
        Dummy->flags = eDummyDefault;
    }

bool ENCHRecord::IsApparel()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eApparel);
    }

void ENCHRecord::IsApparel(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eApparel;
    else
        Dummy->flags = eDummyDefault;
    }

bool ENCHRecord::IsType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void ENCHRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 ENCHRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-16];

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

    if(ENIT.IsLoaded())
        TotSize += ENIT.GetSize() + 6;

    if(EFID.IsLoaded())
        {
        if(EFID->EFID.IsLoaded())
            TotSize += EFID->EFID.GetSize() + 6;
        if(EFID->EFIT.IsLoaded())
            TotSize += EFID->EFIT.GetSize() + 6;
        if(EFID->CTDA.IsLoaded())
            TotSize += EFID->CTDA.GetSize() + 6;
        }

    return TotSize;
    }

UINT32 ENCHRecord::GetType()
    {
    return 'HCNE';
    }

STRING ENCHRecord::GetStrType()
    {
    return "ENCH";
    }

SINT32 ENCHRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'TINE':
                ENIT.Read(buffer, subSize, curPos);
                break;
            case 'DIFE':
                EFID.Load();
                EFID->EFID.Read(buffer, subSize, curPos);
                break;
            case 'TIFE':
                EFID.Load();
                EFID->EFIT.Read(buffer, subSize, curPos);
                break;
            case 'ADTC':
                EFID.Load();
                EFID->CTDA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ENCH: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 ENCHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    ENIT.Unload();
    EFID.Unload();
    return 1;
    }

SINT32 ENCHRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(ENIT.IsLoaded())
        SaveHandler.writeSubRecord('TINE', ENIT.value, ENIT.GetSize());

    if(EFID.IsLoaded())
        {
        if(EFID->EFID.IsLoaded())
            SaveHandler.writeSubRecord('DIFE', EFID->EFID.value, EFID->EFID.GetSize());

        if(EFID->EFIT.IsLoaded())
            SaveHandler.writeSubRecord('TIFE', EFID->EFIT.value, EFID->EFIT.GetSize());

        if(EFID->CTDA.IsLoaded())
            SaveHandler.writeSubRecord('ADTC', EFID->CTDA.value, EFID->CTDA.GetSize());

        }

    return -1;
    }

bool ENCHRecord::operator ==(const ENCHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ENIT == other.ENIT &&
            EFID == other.EFID);
    }

bool ENCHRecord::operator !=(const ENCHRecord &other) const
    {
    return !(*this == other);
    }
}