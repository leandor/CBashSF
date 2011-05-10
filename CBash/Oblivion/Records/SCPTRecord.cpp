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
#include <vector>

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

    VARS.resize(srcRecord->VARS.size());
    for(UINT32 x = 0; x < srcRecord->VARS.size(); x++)
        {
        VARS[x] = new GENVARS;
        VARS[x]->SLSD = srcRecord->VARS[x]->SLSD;
        VARS[x]->SCVR = srcRecord->VARS[x]->SCVR;
        }

    SCR_.resize(srcRecord->SCR_.size());
    for(UINT32 x = 0; x < srcRecord->SCR_.size(); x++)
        {
        SCR_[x] = new ReqSubRecord<GENSCR_>;
        *SCR_[x] = *srcRecord->SCR_[x];
        }
    }

SCPTRecord::~SCPTRecord()
    {
    for(UINT32 x = 0; x < VARS.size(); x++)
        delete VARS[x];
    for(UINT32 x = 0; x < SCR_.size(); x++)
        delete SCR_[x];
    }

bool SCPTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < SCR_.size(); x++)
        if(SCR_[x]->value.isSCRO)
            op.Accept(SCR_[x]->value.reference);

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
                VARS.push_back(new GENVARS);
                VARS.back()->SLSD.Read(buffer, subSize, curPos);
                break;
            case REV32(SCVR):
                if(VARS.size() == 0)
                    VARS.push_back(new GENVARS);
                VARS.back()->SCVR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRV):
                SCR_.push_back(new ReqSubRecord<GENSCR_>);
                SCR_.back()->Read(buffer, subSize, curPos);
                SCR_.back()->value.isSCRO = false;
                break;
            case REV32(SCRO):
                SCR_.push_back(new ReqSubRecord<GENSCR_>);
                SCR_.back()->Read(buffer, subSize, curPos);
                SCR_.back()->value.isSCRO = true;
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
    SCDA.Unload();
    SCTX.Unload();
    for(UINT32 x = 0; x < VARS.size(); x++)
        delete VARS[x];
    VARS.clear();
    for(UINT32 x = 0; x < SCR_.size(); x++)
        delete SCR_[x];
    SCR_.clear();
    return 1;
    }

SINT32 SCPTRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());
    if(SCHR.IsLoaded())
        {
        SCHR.value.compiledSize = SCDA.GetSize(); //Just to ensure that the value is correct
        writer.record_write_subrecord(REV32(SCHR), &SCHR.value, SCHR.GetSize());
        }
    if(SCDA.IsLoaded())
        writer.record_write_subrecord(REV32(SCDA), SCDA.value, SCDA.GetSize());
    if(SCTX.IsLoaded())
        writer.record_write_subrecord(REV32(SCTX), SCTX.value, SCTX.GetSize());
    for(UINT32 p = 0; p < VARS.size(); p++)
        {
        if(VARS[p]->SLSD.IsLoaded())
            writer.record_write_subrecord(REV32(SLSD), &VARS[p]->SLSD.value, VARS[p]->SLSD.GetSize());
        if(VARS[p]->SCVR.IsLoaded())
            writer.record_write_subrecord(REV32(SCVR), VARS[p]->SCVR.value, VARS[p]->SCVR.GetSize());
        }

    for(UINT32 p = 0; p < SCR_.size(); p++)
        if(SCR_[p]->IsLoaded())
            if(SCR_[p]->value.isSCRO)
                writer.record_write_subrecord(REV32(SCRO), &SCR_[p]->value.reference, sizeof(UINT32));
            else
                writer.record_write_subrecord(REV32(SCRV), &SCR_[p]->value.reference, sizeof(UINT32));
    return -1;
    }

bool SCPTRecord::operator ==(const SCPTRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        SCHR == other.SCHR &&
        SCDA == other.SCDA &&
        SCTX.equalsi(other.SCTX) &&
        VARS.size() == other.VARS.size() &&
        SCR_.size() == other.SCR_.size())
        {
        //Record order doesn't matter on vars, so equality testing isn't easy
        //Instead, they're keyed by var index (SLSD.value.index)
        //The proper solution would be to see if each indexed var matches the other
        //But they're usually ordered, so the lazy approach is to not bother
        //Fix-up later
        for(UINT32 x = 0; x < VARS.size(); ++x)
            if(*VARS[x] != *other.VARS[x])
                return false;

        //Record order matters on references, so equality testing is easy
        for(UINT32 x = 0; x < SCR_.size(); ++x)
            if(*SCR_[x] != *other.SCR_[x])
                return false;
        return true;
        }

    return false;
    }

bool SCPTRecord::operator !=(const SCPTRecord &other) const
    {
    return !(*this == other);
    }