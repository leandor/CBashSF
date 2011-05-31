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
#include <vector>

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

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    ICON = srcRecord->ICON;
    DESC = srcRecord->DESC;
    LNAM.clear();
    LNAM.resize(srcRecord->LNAM.size());
    for(UINT32 x = 0; x < srcRecord->LNAM.size(); x++)
        {
        LNAM[x] = new ReqSubRecord<LSCRLNAM>;
        *LNAM[x] = *srcRecord->LNAM[x];
        }
    return;
    }

LSCRRecord::~LSCRRecord()
    {
    for(UINT32 x = 0; x < LNAM.size(); x++)
        delete LNAM[x];
    }

bool LSCRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < LNAM.size(); x++)
        {
        op.Accept(LNAM[x]->value.direct);
        op.Accept(LNAM[x]->value.indirect);
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

SINT32 LSCRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    ReqSubRecord<LSCRLNAM> *newLNAM = NULL;
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
            case REV32(DESC):
                DESC.Read(buffer, subSize, curPos);
                break;
            case REV32(LNAM):
                newLNAM = new ReqSubRecord<LSCRLNAM>;
                newLNAM->Read(buffer, subSize, curPos);
                LNAM.push_back(newLNAM);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LSCR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
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
    DESC.Unload();
    for(UINT32 x = 0; x < LNAM.size(); x++)
        delete LNAM[x];
    LNAM.clear();
    return 1;
    }

SINT32 LSCRRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());
    if(ICON.IsLoaded())
        writer.record_write_subrecord(REV32(ICON), ICON.value, ICON.GetSize());
    if(DESC.IsLoaded())
        writer.record_write_subrecord(REV32(DESC), DESC.value, DESC.GetSize());
    for(UINT32 p = 0; p < LNAM.size(); p++)
        if(LNAM[p]->IsLoaded())
            writer.record_write_subrecord(REV32(LNAM), &LNAM[p]->value, LNAM[p]->GetSize());
    return -1;
    }

bool LSCRRecord::operator ==(const LSCRRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        ICON.equalsi(other.ICON) &&
        DESC.equals(other.DESC) &&
        LNAM.size() == other.LNAM.size())
        {
        //Not sure if record order matters on locations, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < LNAM.size(); ++x)
            if(*LNAM[x] != *other.LNAM[x])
                return false;
        return true;
        }

    return false;
    }

bool LSCRRecord::operator !=(const LSCRRecord &other) const
    {
    return !(*this == other);
    }