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
#include "LSCRRecord.h"

namespace FNV
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
    FNVRecord(_recData)
    {
    //
    }

LSCRRecord::LSCRRecord(LSCRRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    DESC = srcRecord->DESC;
    LNAM = srcRecord->LNAM;
    WMI1 = srcRecord->WMI1;
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
    if(WMI1.IsLoaded())
        op.Accept(WMI1.value);

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

SINT32 LSCRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, curPos);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, curPos);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, curPos);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(WMI1):
                WMI1.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LSCR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    MICO.Unload();
    DESC.Unload();
    LNAM.Unload();
    WMI1.Unload();
    return 1;
    }

SINT32 LSCRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(DESC);
    WRITE(LNAM);
    WRITE(WMI1);
    return -1;
    }

bool LSCRRecord::operator ==(const LSCRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            DESC.equals(other.DESC) &&
            LNAM == other.LNAM &&
            WMI1 == other.WMI1);
    }

bool LSCRRecord::operator !=(const LSCRRecord &other) const
    {
    return !(*this == other);
    }
}