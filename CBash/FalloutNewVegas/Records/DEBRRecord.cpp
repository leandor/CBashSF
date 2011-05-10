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
#include "DEBRRecord.h"

namespace FNV
{
bool DEBRRecord::DEBRModel::IsHasCollisionData()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHasCollisionData) != 0;
    }

void DEBRRecord::DEBRModel::IsHasCollisionData(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsHasCollisionData) : (Dummy->flags & ~fIsHasCollisionData);
    }

bool DEBRRecord::DEBRModel::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void DEBRRecord::DEBRModel::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

DEBRRecord::DEBRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

DEBRRecord::DEBRRecord(DEBRRecord *srcRecord):
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
    DATA = srcRecord->DATA;
    MODT = srcRecord->MODT;
    return;
    }

DEBRRecord::~DEBRRecord()
    {
    //
    }

bool DEBRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;


    return op.Stop();
    }

UINT32 DEBRRecord::GetType()
    {
    return REV32(DEBR);
    }

STRING DEBRRecord::GetStrType()
    {
    return "DEBR";
    }

SINT32 DEBRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(MODT):
                MODT.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  DEBR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 DEBRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DATA.Unload();
    MODT.Unload();
    return 1;
    }

SINT32 DEBRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DATA);
    WRITE(MODT);

    return -1;
    }

bool DEBRRecord::operator ==(const DEBRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DATA == other.DATA &&
            MODT == other.MODT);
    }

bool DEBRRecord::operator !=(const DEBRRecord &other) const
    {
    return !(*this == other);
    }
}