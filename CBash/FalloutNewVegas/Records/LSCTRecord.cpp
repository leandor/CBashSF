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
#include "LSCTRecord.h"

namespace FNV
{
LSCTRecord::LSCTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

LSCTRecord::LSCTRecord(LSCTRecord *srcRecord):
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
    DATA = srcRecord->DATA;
    return;
    }

LSCTRecord::~LSCTRecord()
    {
    //
    }

bool LSCTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

bool LSCTRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void LSCTRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool LSCTRecord::IsXPProgress()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eXPProgress);
    }

void LSCTRecord::IsXPProgress(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eXPProgress : eDummyDefault;
    }

bool LSCTRecord::IsObjective()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eObjective);
    }

void LSCTRecord::IsObjective(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eObjective : eDummyDefault;
    }

bool LSCTRecord::IsTip()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTip);
    }

void LSCTRecord::IsTip(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTip : eDummyDefault;
    }

bool LSCTRecord::IsStats()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStats);
    }

void LSCTRecord::IsStats(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eStats : eDummyDefault;
    }

bool LSCTRecord::IsType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void LSCTRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 LSCTRecord::GetType()
    {
    return REV32(LSCT);
    }

STRING LSCTRecord::GetStrType()
    {
    return "LSCT";
    }

SINT32 LSCTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LSCT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 LSCTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 LSCTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DATA);

    return -1;
    }

bool LSCTRecord::operator ==(const LSCTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DATA == other.DATA);
    }

bool LSCTRecord::operator !=(const LSCTRecord &other) const
    {
    return !(*this == other);
    }

bool LSCTRecord::equals(const Record *other) const
    {
    return *this == *(LSCTRecord *)other;
    }
}