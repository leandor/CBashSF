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
#include "SCPTRecord.h"

namespace Ob
{
SCPTRecord::SCPTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SCPTRecord::SCPTRecord(SCPTRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    SCHR = srcRecord->SCHR;
    SCDA = srcRecord->SCDA;
    SCTX = srcRecord->SCTX;
    VARS = srcRecord->VARS;
    SCR_ = srcRecord->SCR_;
    }

SCPTRecord::~SCPTRecord()
    {
    //
    }

bool SCPTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < SCR_.value.size(); ListIndex++)
        if(SCR_.value[ListIndex]->isSCRO)
            op.Accept(SCR_.value[ListIndex]->reference);

    return op.Stop();
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

bool SCPTRecord::IsMagicEffect()
    {
    return SCHR.value.scriptType == eMagicEffect;
    }

void SCPTRecord::IsMagicEffect(bool value)
    {
    SCHR.value.scriptType = value ? eMagicEffect : eObject;
    }

bool SCPTRecord::IsType(UINT32 Type)
    {
    return SCHR.value.scriptType == Type;
    }

void SCPTRecord::SetType(UINT32 Type)
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

SINT32 SCPTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(SCHR):
                SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                SCDA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCTX):
                SCTX.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SLSD):
                VARS.value.push_back(new GENVARS);
                VARS.value.back()->SLSD.Read(buffer, subSize);
                break;
            case REV32(SCVR):
                if(VARS.value.size() == 0)
                    VARS.value.push_back(new GENVARS);
                VARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRV):
                SCR_.Read(buffer, subSize);
                SCR_.value.back()->isSCRO = false;
                break;
            case REV32(SCRO):
                SCR_.Read(buffer, subSize);
                SCR_.value.back()->isSCRO = true;
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SCPT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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
    return (SCHR == other.SCHR &&
            EDID.equalsi(other.EDID) &&
            SCDA == other.SCDA &&
            VARS == other.VARS &&
            SCR_ == other.SCR_ &&
            SCTX.equalsi(other.SCTX));
    }

bool SCPTRecord::operator !=(const SCPTRecord &other) const
    {
    return !(*this == other);
    }

bool SCPTRecord::equals(Record *other)
    {
    return *this == *(SCPTRecord *)other;
    }
}