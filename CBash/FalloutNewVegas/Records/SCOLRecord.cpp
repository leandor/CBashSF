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
#include "SCOLRecord.h"

namespace FNV
{
SCOLRecord::SCOLRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SCOLRecord::SCOLRecord(SCOLRecord *srcRecord):
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
    OBND = srcRecord->OBND;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    ONAM = srcRecord->ONAM;
    DATA = srcRecord->DATA;
    return;
    }

SCOLRecord::~SCOLRecord()
    {
    //
    }

bool SCOLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(ONAM.IsLoaded())
        op.Accept(ONAM->value);

    return op.Stop();
    }

UINT32 SCOLRecord::GetSize(bool forceCalc)
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

    if(OBND.IsLoaded())
        TotSize += OBND.GetSize() + 6;

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            {
            cSize = MODL->MODL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODB.IsLoaded())
            {
            cSize = MODL->MODB.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MODL->MODS.IsLoaded())
            TotSize += MODL->MODS.GetSize() + 6;
        if(MODL->MODD.IsLoaded())
            TotSize += MODL->MODD.GetSize() + 6;
        }

    if(ONAM.IsLoaded())
        TotSize += ONAM.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

UINT32 SCOLRecord::GetType()
    {
    return 'LOCS';
    }

STRING SCOLRecord::GetStrType()
    {
    return "SCOL";
    }

SINT32 SCOLRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'DNBO':
                OBND.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case 'BDOM':
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case 'TDOM':
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case 'SDOM':
                MODL.Load();
                MODL->MODS.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                ONAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  SCOL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 SCOLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    ONAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 SCOLRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());

        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord('BDOM', MODL->MODB.value, MODL->MODB.GetSize());

        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());

        if(MODL->MODS.IsLoaded())
            SaveHandler.writeSubRecord('SDOM', MODL->MODS.value, MODL->MODS.GetSize());

        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', MODL->MODD.value, MODL->MODD.GetSize());

        }

    if(ONAM.IsLoaded())
        SaveHandler.writeSubRecord('MANO', ONAM.value, ONAM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    return -1;
    }

bool SCOLRecord::operator ==(const SCOLRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            MODL == other.MODL &&
            ONAM == other.ONAM &&
            DATA == other.DATA);
    }

bool SCOLRecord::operator !=(const SCOLRecord &other) const
    {
    return !(*this == other);
    }
}