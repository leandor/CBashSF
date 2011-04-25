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
#include "IMGSRecord.h"

namespace FNV
{
IMGSRecord::IMGSRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IMGSRecord::IMGSRecord(IMGSRecord *srcRecord):
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
    DNAM = srcRecord->DNAM;
    return;
    }

IMGSRecord::~IMGSRecord()
    {
    //
    }

bool IMGSRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;


    return op.Stop();
    }

bool IMGSRecord::IsSaturation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSaturation) != 0;
    }

void IMGSRecord::IsSaturation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsSaturation;
    else
        Dummy->flags &= ~fIsSaturation;
    }

bool IMGSRecord::IsContrast()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsContrast) != 0;
    }

void IMGSRecord::IsContrast(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsContrast;
    else
        Dummy->flags &= ~fIsContrast;
    }

bool IMGSRecord::IsTint()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTint) != 0;
    }

void IMGSRecord::IsTint(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsTint;
    else
        Dummy->flags &= ~fIsTint;
    }

bool IMGSRecord::IsBrightness()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBrightness) != 0;
    }

void IMGSRecord::IsBrightness(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsBrightness;
    else
        Dummy->flags &= ~fIsBrightness;
    }

bool IMGSRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void IMGSRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 IMGSRecord::GetSize(bool forceCalc)
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

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 IMGSRecord::GetType()
    {
    return 'SGMI';
    }

STRING IMGSRecord::GetStrType()
    {
    return "IMGS";
    }

SINT32 IMGSRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IMGS: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 IMGSRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DNAM.Unload();
    return 1;
    }

SINT32 IMGSRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    return -1;
    }

bool IMGSRecord::operator ==(const IMGSRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DNAM == other.DNAM);
    }

bool IMGSRecord::operator !=(const IMGSRecord &other) const
    {
    return !(*this == other);
    }
}