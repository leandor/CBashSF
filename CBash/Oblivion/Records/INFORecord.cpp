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
#include "INFORecord.h"

namespace Ob
{
INFORecord::INFODATA::INFODATA():
    dialType(0),
    flags(0)
    {
    //
    }

INFORecord::INFODATA::~INFODATA()
    {
    //
    }

bool INFORecord::INFODATA::operator ==(const INFODATA &other) const
    {
    return (dialType == other.dialType &&
            flags == other.flags);
    }

bool INFORecord::INFODATA::operator !=(const INFODATA &other) const
    {
    return !(*this == other);
    }

INFORecord::INFOTRDT::INFOTRDT():
    emotionType(0),
    emotionValue(0),
    responseNum(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unused2[0], 0x00, sizeof(unused2));
    }

INFORecord::INFOTRDT::~INFOTRDT()
    {
    //
    }

bool INFORecord::INFOTRDT::operator ==(const INFOTRDT &other) const
    {
    return (emotionType == other.emotionType &&
            emotionValue == other.emotionValue &&
            responseNum == other.responseNum);
    }

bool INFORecord::INFOTRDT::operator !=(const INFOTRDT &other) const
    {
    return !(*this == other);
    }

bool INFORecord::INFOResponse::IsNeutral()
    {
    return (TRDT.value.emotionType == eNeutral);
    }

void INFORecord::INFOResponse::IsNeutral(bool value)
    {
    if(value)
        TRDT.value.emotionType = eNeutral;
    else if(IsNeutral())
        TRDT.value.emotionType = eAnger;
    }

bool INFORecord::INFOResponse::IsAnger()
    {
    return (TRDT.value.emotionType == eAnger);
    }

void INFORecord::INFOResponse::IsAnger(bool value)
    {
    if(value)
        TRDT.value.emotionType = eAnger;
    else if(IsAnger())
        TRDT.value.emotionType = eNeutral;
    }

bool INFORecord::INFOResponse::IsDisgust()
    {
    return (TRDT.value.emotionType == eDisgust);
    }

void INFORecord::INFOResponse::IsDisgust(bool value)
    {
    if(value)
        TRDT.value.emotionType = eDisgust;
    else if(IsDisgust())
        TRDT.value.emotionType = eNeutral;
    }

bool INFORecord::INFOResponse::IsFear()
    {
    return (TRDT.value.emotionType == eFear);
    }

void INFORecord::INFOResponse::IsFear(bool value)
    {
    if(value)
        TRDT.value.emotionType = eFear;
    else if(IsFear())
        TRDT.value.emotionType = eNeutral;
    }

bool INFORecord::INFOResponse::IsSad()
    {
    return (TRDT.value.emotionType == eSad);
    }

void INFORecord::INFOResponse::IsSad(bool value)
    {
    if(value)
        TRDT.value.emotionType = eSad;
    else if(IsSad())
        TRDT.value.emotionType = eNeutral;
    }

bool INFORecord::INFOResponse::IsHappy()
    {
    return (TRDT.value.emotionType == eHappy);
    }

void INFORecord::INFOResponse::IsHappy(bool value)
    {
    if(value)
        TRDT.value.emotionType = eHappy;
    else if(IsHappy())
        TRDT.value.emotionType = eNeutral;
    }

bool INFORecord::INFOResponse::IsSurprise()
    {
    return (TRDT.value.emotionType == eSurprise);
    }

void INFORecord::INFOResponse::IsSurprise(bool value)
    {
    if(value)
        TRDT.value.emotionType = eSurprise;
    else if(IsSurprise())
        TRDT.value.emotionType = eNeutral;
    }

bool INFORecord::INFOResponse::IsType(UINT32 Type)
    {
    return (TRDT.value.emotionType == Type);
    }

void INFORecord::INFOResponse::SetType(UINT32 Type)
    {
    TRDT.value.emotionType = Type;
    }

void INFORecord::INFOResponse::Write(FileWriter &writer)
    {
    WRITE(TRDT);
    WRITE(NAM1);
    WRITE(NAM2);
    }

bool INFORecord::INFOResponse::operator ==(const INFOResponse &other) const
    {
    return (TRDT == other.TRDT &&
            NAM1.equals(other.NAM1) &&
            NAM2.equalsi(other.NAM2));
    }

bool INFORecord::INFOResponse::operator !=(const INFOResponse &other) const
    {
    return !(*this == other);
    }

INFORecord::INFORecord(unsigned char *_recData):
    Record(_recData),
    Parent(NULL)
    {
    //
    }

INFORecord::INFORecord(INFORecord *srcRecord):
    Record(),
    Parent(NULL)
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

    DATA = srcRecord->DATA;
    QSTI = srcRecord->QSTI;
    TPIC = srcRecord->TPIC;
    PNAM = srcRecord->PNAM;
    NAME = srcRecord->NAME;
    Responses = srcRecord->Responses;
    CTDA = srcRecord->CTDA;
    TCLT = srcRecord->TCLT;
    TCLF = srcRecord->TCLF;
    SCHR = srcRecord->SCHR;
    SCDA = srcRecord->SCDA;
    SCTX = srcRecord->SCTX;
    SCR_ = srcRecord->SCR_;
    return;
    }

INFORecord::~INFORecord()
    {
    //Parent is a shared pointer that's deleted when the DIAL group is deleted
    }

bool INFORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(QSTI.value);
    if(TPIC.IsLoaded())
        op.Accept(TPIC.value);
    if(PNAM.IsLoaded())
        op.Accept(*PNAM.value);
    for(UINT32 ListIndex = 0; ListIndex < NAME.value.size(); ListIndex++)
        op.Accept(NAME.value[ListIndex]);
    for(UINT32 ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);
    for(UINT32 ListIndex = 0; ListIndex < TCLT.value.size(); ListIndex++)
        op.Accept(TCLT.value[ListIndex]);
    for(UINT32 ListIndex = 0; ListIndex < TCLF.value.size(); ListIndex++)
        op.Accept(TCLF.value[ListIndex]);
    for(UINT32 ListIndex = 0; ListIndex < SCR_.value.size(); ListIndex++)
        {
        if(SCR_.value[ListIndex]->isSCRO)
            op.Accept(SCR_.value[ListIndex]->reference);
        }

    return op.Stop();
    }

bool INFORecord::IsTopic()
    {
    return (DATA.value.dialType == eTopic);
    }

void INFORecord::IsTopic(bool value)
    {
    if(value)
        DATA.value.dialType = eTopic;
    else if(IsTopic())
        DATA.value.dialType = eConversation;
    }

bool INFORecord::IsConversation()
    {
    return (DATA.value.dialType == eConversation);
    }

void INFORecord::IsConversation(bool value)
    {
    if(value)
        DATA.value.dialType = eConversation;
    else if(IsConversation())
        DATA.value.dialType = eTopic;
    }

bool INFORecord::IsCombat()
    {
    return (DATA.value.dialType == eCombat);
    }

void INFORecord::IsCombat(bool value)
    {
    if(value)
        DATA.value.dialType = eCombat;
    else if(IsCombat())
        DATA.value.dialType = eTopic;
    }

bool INFORecord::IsPersuasion()
    {
    return (DATA.value.dialType == ePersuasion);
    }

void INFORecord::IsPersuasion(bool value)
    {
    if(value)
        DATA.value.dialType = ePersuasion;
    else if(IsPersuasion())
        DATA.value.dialType = eTopic;
    }

bool INFORecord::IsDetection()
    {
    return (DATA.value.dialType == eDetection);
    }

void INFORecord::IsDetection(bool value)
    {
    if(value)
        DATA.value.dialType = eDetection;
    else if(IsDetection())
        DATA.value.dialType = eTopic;
    }

bool INFORecord::IsService()
    {
    return (DATA.value.dialType == eService);
    }

void INFORecord::IsService(bool value)
    {
    if(value)
        DATA.value.dialType = eService;
    else if(IsService())
        DATA.value.dialType = eTopic;
    }

bool INFORecord::IsMisc()
    {
    return (DATA.value.dialType == eMisc);
    }

void INFORecord::IsMisc(bool value)
    {
    if(value)
        DATA.value.dialType = eMisc;
    else if(IsMisc())
        DATA.value.dialType = eTopic;
    }

bool INFORecord::IsDialogType(UINT16 Type)
    {
    return (DATA.value.dialType == Type);
    }

void INFORecord::SetDialogType(UINT16 Type)
    {
    DATA.value.dialType = Type;
    }

bool INFORecord::IsGoodbye()
    {
    return (DATA.value.flags & fIsGoodbye) != 0;
    }

void INFORecord::IsGoodbye(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsGoodbye) : (DATA.value.flags & ~fIsGoodbye);
    }

bool INFORecord::IsRandom()
    {
    return (DATA.value.flags & fIsRandom) != 0;
    }

void INFORecord::IsRandom(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsRandom) : (DATA.value.flags & ~fIsRandom);
    }

bool INFORecord::IsSayOnce()
    {
    return (DATA.value.flags & fIsSayOnce) != 0;
    }

void INFORecord::IsSayOnce(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsSayOnce) : (DATA.value.flags & ~fIsSayOnce);
    }

bool INFORecord::IsRunImmediately()
    {
    return (DATA.value.flags & fIsRunImmediately) != 0;
    }

void INFORecord::IsRunImmediately(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsRunImmediately) : (DATA.value.flags & ~fIsRunImmediately);
    }

bool INFORecord::IsInfoRefusal()
    {
    return (DATA.value.flags & fIsInfoRefusal) != 0;
    }

void INFORecord::IsInfoRefusal(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsInfoRefusal) : (DATA.value.flags & ~fIsInfoRefusal);
    }

bool INFORecord::IsRandomEnd()
    {
    return (DATA.value.flags & fIsRandomEnd) != 0;
    }

void INFORecord::IsRandomEnd(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsRandomEnd) : (DATA.value.flags & ~fIsRandomEnd);
    }

bool INFORecord::IsRunForRumors()
    {
    return (DATA.value.flags & fIsRunForRumors) != 0;
    }

void INFORecord::IsRunForRumors(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsRunForRumors) : (DATA.value.flags & ~fIsRunForRumors);
    }

bool INFORecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void INFORecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

bool INFORecord::IsScriptObject()
    {
    return SCHR.value.scriptType == eObject;
    }

void INFORecord::IsScriptObject(bool value)
    {
    SCHR.value.scriptType = value ? eObject : eQuest;
    }

bool INFORecord::IsScriptQuest()
    {
    return SCHR.value.scriptType == eQuest;
    }

void INFORecord::IsScriptQuest(bool value)
    {
    SCHR.value.scriptType = value ? eQuest : eObject;
    }

bool INFORecord::IsScriptEffect()
    {
    return SCHR.value.scriptType == eEffect;
    }

void INFORecord::IsScriptEffect(bool value)
    {
    SCHR.value.scriptType = value ? eEffect : eObject;
    }

bool INFORecord::IsScriptType(UINT32 Type)
    {
    return SCHR.value.scriptType == Type;
    }

void INFORecord::SetScriptType(UINT32 Type)
    {
    SCHR.value.scriptType = Type;
    }

UINT32 INFORecord::GetType()
    {
    return REV32(INFO);
    }

STRING INFORecord::GetStrType()
    {
    return "INFO";
    }

Record * INFORecord::GetParent()
    {
    return Parent;
    }

SINT32 INFORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(QSTI):
                QSTI.Read(buffer, subSize);
                break;
            case REV32(TPIC):
                TPIC.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(NAME):
                NAME.Read(buffer, subSize);
                break;
            case REV32(TRDT):
                Responses.value.push_back(new INFOResponse);
                Responses.value.back()->TRDT.Read(buffer, subSize);
                break;
            case REV32(NAM1):
                if(Responses.value.size() == 0)
                    Responses.value.push_back(new INFOResponse);
                Responses.value.back()->NAM1.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM2):
                if(Responses.value.size() == 0)
                    Responses.value.push_back(new INFOResponse);
                Responses.value.back()->NAM2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(CTDT):
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(TCLT):
                TCLT.Read(buffer, subSize);
                break;
            case REV32(TCLF):
                TCLF.Read(buffer, subSize);
                break;
            case REV32(SCHD): //replace it with SCHR. SCHDs are always zero filled in oblivion.esm...
                buffer += subSize;
                break;
            case REV32(SCHR): //SCHDs are also larger than SCHRs, so the end will be truncated.
                SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                SCDA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCTX):
                SCTX.Read(buffer, subSize, CompressedOnDisk);
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
                printer("  INFO: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 INFORecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    DATA.Unload();
    QSTI.Unload();
    TPIC.Unload();
    PNAM.Unload();
    NAME.Unload();
    Responses.Unload();
    CTDA.Unload();
    TCLT.Unload();
    TCLF.Unload();
    SCHR.Unload();
    SCDA.Unload();
    SCTX.Unload();
    SCR_.Unload();
    return 1;
    }

SINT32 INFORecord::WriteRecord(FileWriter &writer)
    {
    WRITE(DATA);
    WRITE(QSTI);
    WRITE(TPIC);
    WRITE(PNAM);
    WRITE(NAME);
    Responses.Write(writer);
    CTDA.Write(writer, true);
    WRITE(TCLT);
    WRITE(TCLF);
    SCHR.value.numRefs = (UINT32)SCR_.value.size(); //Just to ensure that the value is correct
    SCHR.value.compiledSize = SCDA.GetSize(); //Just to ensure that the value is correct
    WRITE(SCHR);
    WRITE(SCDA);
    WRITE(SCTX);
    SCR_.Write(writer, true);

    return -1;
    }

bool INFORecord::operator ==(const INFORecord &other) const
    {
    return (DATA == other.DATA &&
            QSTI == other.QSTI &&
            TPIC == other.TPIC &&
            PNAM == other.PNAM &&
            SCHR == other.SCHR &&
            SCDA == other.SCDA &&
            SCTX.equalsi(other.SCTX) &&
            NAME == other.NAME &&
            Responses == other.Responses &&
            CTDA == other.CTDA &&
            TCLT == other.TCLT &&
            TCLF == other.TCLF &&
            SCR_ == other.SCR_);
    }

bool INFORecord::operator !=(const INFORecord &other) const
    {
    return !(*this == other);
    }

bool INFORecord::equals(Record *other)
    {
    return *this == *(INFORecord *)other;
    }

bool INFORecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    const INFORecord *master_info = (INFORecord *)master;
    //Check to make sure the info is attached at the same spot
    if(Parent->formID != master_info->Parent->formID)
        return false;
    return true;
    }
}