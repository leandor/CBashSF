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
    SCHR = srcRecord->SCHR;
    SCDA = srcRecord->SCDA;
    SCTX = srcRecord->SCTX;
    VARS = srcRecord->VARS;
    SCR_ = srcRecord->SCR_;
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

    for(UINT32 x = 0; x < SCR_.value.size(); x++)
        if(SCR_.value[x]->isSCRO)
            op.Accept(SCR_.value[x]->reference);

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
    return Exact ? (SCHR.value.flags & Mask) == Mask : (SCHR.value.flags & Mask) != 0;
    }

void SCPTRecord::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

bool SCPTRecord::IsObject()
    {
    return SCHR.value.scriptType == eObject;
    }

void SCPTRecord::IsObject(bool value)
    {
    SCHR.value.scriptType = value ? eObject : eQuest;
    }

bool SCPTRecord::IsQuest()
    {
    return SCHR.value.scriptType == eQuest;
    }

void SCPTRecord::IsQuest(bool value)
    {
    SCHR.value.scriptType = value ? eQuest : eObject;
    }

bool SCPTRecord::IsEffect()
    {
    return SCHR.value.scriptType == eEffect;
    }

void SCPTRecord::IsEffect(bool value)
    {
    SCHR.value.scriptType = value ? eEffect : eObject;
    }

bool SCPTRecord::IsType(UINT16 Type)
    {
    return SCHR.value.scriptType == Type;
    }

void SCPTRecord::SetType(UINT16 Type)
    {
    SCHR.value.scriptType = Type;
    }

UINT32 SCPTRecord::GetType()
    {
    return REV32(SCPT);
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
            case REV32(SCHR):
                SCHR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCDA):
                SCDA.Read(buffer, subSize, curPos);
                break;
            case REV32(SCTX):
                SCTX.Read(buffer, subSize, curPos);
                break;
            case REV32(SLSD):
                VARS.value.push_back(new GENVARS);
                VARS.value.back()->SLSD.Read(buffer, subSize, curPos);
                break;
            case REV32(SCVR):
                if(VARS.value.size() == 0)
                    VARS.value.push_back(new GENVARS);
                VARS.value.back()->SCVR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRV):
                SCR_.Read(buffer, subSize, curPos);
                SCR_.value.back()->isSCRO = false;
                break;
            case REV32(SCRO):
                SCR_.Read(buffer, subSize, curPos);
                SCR_.value.back()->isSCRO = true;
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SCPT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
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
    SCDA.Unload();
    SCTX.Unload();
    VARS.Unload();
    SCR_.Unload();
    return 1;
    }

SINT32 SCPTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    SCHR.value.numRefs = (UINT32)SCR_.value.size(); //Just to ensure that the value is correct
    SCHR.value.compiledSize = SCDA.GetSize(); //Just to ensure that the value is correct
    //for(UINT32 x = 0; x < VARS.value.size(); ++x) //Just to ensure that the value is correct
    //    SCHR.value.lastIndex = (SCHR.value.lastIndex > VARS.value[x]->SLSD.value.index) ? SCHR.value.lastIndex : VARS.value[x]->SLSD.value.index;
    WRITE(SCHR);
    WRITE(SCDA);
    WRITE(SCTX);
    VARS.Write(writer);
    SCR_.Write(writer, true);
    return -1;
    }

bool SCPTRecord::operator ==(const SCPTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            SCHR == other.SCHR &&
            SCDA == other.SCDA &&
            SCTX.equalsi(other.SCTX) &&
            VARS == other.VARS &&
            SCR_ == other.SCR_);
    }

bool SCPTRecord::operator !=(const SCPTRecord &other) const
    {
    return !(*this == other);
    }
}