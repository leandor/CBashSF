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
#include "SCPTRecord.h"

namespace FNV
{
SCPTRecord::SCPTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

SCPTRecord::SCPTRecord(SCPTRecord *srcRecord):
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
    if(srcRecord->SCHR.IsLoaded())
        {
        SCHR.Load();
        SCHR->SCHR = srcRecord->SCHR->SCHR;
        SCHR->SCDA = srcRecord->SCHR->SCDA;
        SCHR->SCTX = srcRecord->SCHR->SCTX;
        SCHR->SLSD = srcRecord->SCHR->SLSD;
        SCHR->SCVR = srcRecord->SCHR->SCVR;
        SCHR->SCRO = srcRecord->SCHR->SCRO;
        SCHR->SCRV = srcRecord->SCHR->SCRV;
        }
    return;
    }

SCPTRecord::~SCPTRecord()
    {
    //
    }

bool SCPTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCHR.IsLoaded() && SCHR->SCRO.IsLoaded())
        op.Accept(SCHR->SCRO->value);

    return op.Stop();
    }

bool SCPTRecord::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void SCPTRecord::IsScriptEnabled(bool value)
    {
    SCHR.value.flags = value ? (SCHR.value.flags | fIsEnabled) : (SCHR.value.flags & ~fIsEnabled);
    }

bool SCPTRecord::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    if(Exact)
        return (SCHR.value.flags & Mask) == Mask;
    else
        return (SCHR.value.flags & Mask) != 0;
    }

void SCPTRecord::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

UINT32 SCPTRecord::GetType()
    {
    return 'TPCS';
    }

STRING SCPTRecord::GetStrType()
    {
    return "SCPT";
    }

SINT32 SCPTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'RHCS':
                SCHR.Load();
                SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case 'ADCS':
                SCHR.Load();
                SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case 'XTCS':
                SCHR.Load();
                SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case 'DSLS':
                SCHR.Load();
                SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case 'RVCS':
                SCHR.Load();
                SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case 'ORCS':
                SCHR.Load();
                SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case 'VRCS':
                SCHR.Load();
                SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  SCPT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 SCPTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    SCHR.Unload();
    return 1;
    }

SINT32 SCPTRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    WRITE(EDID);

    if(SCHR.IsLoaded())
        {
        if(SCHR->SCHR.IsLoaded())
            SaveHandler.writeSubRecord('RHCS', SCHR->SCHR.value, SCHR->SCHR.GetSize());

        if(SCHR->SCDA.IsLoaded())
            SaveHandler.writeSubRecord('ADCS', SCHR->SCDA.value, SCHR->SCDA.GetSize());

        if(SCHR->SCTX.IsLoaded())
            SaveHandler.writeSubRecord('XTCS', SCHR->SCTX.value, SCHR->SCTX.GetSize());

        if(SCHR->SLSD.IsLoaded())
            SaveHandler.writeSubRecord('DSLS', SCHR->SLSD.value, SCHR->SLSD.GetSize());

        if(SCHR->SCVR.IsLoaded())
            SaveHandler.writeSubRecord('RVCS', SCHR->SCVR.value, SCHR->SCVR.GetSize());

        if(SCHR->SCRO.IsLoaded())
            SaveHandler.writeSubRecord('ORCS', SCHR->SCRO.value, SCHR->SCRO.GetSize());

        if(SCHR->SCRV.IsLoaded())
            SaveHandler.writeSubRecord('VRCS', SCHR->SCRV.value, SCHR->SCRV.GetSize());

        }

    return -1;
    }

bool SCPTRecord::operator ==(const SCPTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            SCHR == other.SCHR);
    }

bool SCPTRecord::operator !=(const SCPTRecord &other) const
    {
    return !(*this == other);
    }
}