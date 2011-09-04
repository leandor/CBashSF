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
#include "LSCRRecord.h"

namespace Ob
{
LSCRRecord::LSCRLNAM::LSCRLNAM():
    direct(0),
    indirect(0),
    gridY(0),
    gridX(0)
    {
    //
    }

LSCRRecord::LSCRLNAM::~LSCRLNAM()
    {
    //
    }

bool LSCRRecord::LSCRLNAM::operator ==(const LSCRLNAM &other) const
    {
    return (direct == other.direct &&
            indirect == other.indirect &&
            gridY == other.gridY &&
            gridX == other.gridX);
    }

bool LSCRRecord::LSCRLNAM::operator !=(const LSCRLNAM &other) const
    {
    return !(*this == other);
    }

LSCRRecord::LSCRRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LSCRRecord::LSCRRecord(LSCRRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    DESC = srcRecord->DESC;
    LNAM = srcRecord->LNAM;
    return;
    }

LSCRRecord::~LSCRRecord()
    {
    //
    }

bool LSCRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < LNAM.value.size(); ListIndex++)
        {
        op.Accept(LNAM.value[ListIndex]->direct);
        op.Accept(LNAM.value[ListIndex]->indirect);
        }

    return op.Stop();
    }

UINT32 LSCRRecord::GetType()
    {
    return REV32(LSCR);
    }

STRING LSCRRecord::GetStrType()
    {
    return "LSCR";
    }

SINT32 LSCRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LSCR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 LSCRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    DESC.Unload();
    LNAM.Unload();
    return 1;
    }

SINT32 LSCRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(DESC);
    WRITE(LNAM);
    return -1;
    }

bool LSCRRecord::operator ==(const LSCRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            DESC.equals(other.DESC) &&
            LNAM == other.LNAM);
    }

bool LSCRRecord::operator !=(const LSCRRecord &other) const
    {
    return !(*this == other);
    }

bool LSCRRecord::equals(Record *other)
    {
    return *this == *(LSCRRecord *)other;
    }
}