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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
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
    Dummy->flags = value ? (Dummy->flags | fIsSaturation) : (Dummy->flags & ~fIsSaturation);
    }

bool IMGSRecord::IsContrast()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsContrast) != 0;
    }

void IMGSRecord::IsContrast(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsContrast) : (Dummy->flags & ~fIsContrast);
    }

bool IMGSRecord::IsTint()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTint) != 0;
    }

void IMGSRecord::IsTint(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsTint) : (Dummy->flags & ~fIsTint);
    }

bool IMGSRecord::IsBrightness()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBrightness) != 0;
    }

void IMGSRecord::IsBrightness(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsBrightness) : (Dummy->flags & ~fIsBrightness);
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

UINT32 IMGSRecord::GetType()
    {
    return REV32(IMGS);
    }

STRING IMGSRecord::GetStrType()
    {
    return "IMGS";
    }

SINT32 IMGSRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IMGS: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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

SINT32 IMGSRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DNAM);

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

bool IMGSRecord::equals(const Record *other) const
    {
    return *this == *(IMGSRecord *)other;
    }
}