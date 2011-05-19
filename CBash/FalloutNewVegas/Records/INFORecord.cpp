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
#include "INFORecord.h"

namespace FNV
{
INFORecord::INFODATA::INFODATA():
    dialType(0),
    nextSpeaker(0),
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
            nextSpeaker == other.nextSpeaker &&
            flags == other.flags);
    }

bool INFORecord::INFODATA::operator !=(const INFODATA &other) const
    {
    return !(*this == other);
    }

INFORecord::INFOTRDT::INFOTRDT():
    emotionType(0),
    emotionValue(0),
    responseNum(0),
    sound(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unused2[0], 0x00, sizeof(unused2));
    memset(&unused3[0], 0x00, sizeof(unused3));
    }

INFORecord::INFOTRDT::~INFOTRDT()
    {
    //
    }

bool INFORecord::INFOTRDT::operator ==(const INFOTRDT &other) const
    {
    return (emotionType == other.emotionType &&
            emotionValue == other.emotionValue &&
            responseNum == other.responseNum &&
            sound == other.sound &&
            flags == other.flags);
    }

bool INFORecord::INFOTRDT::operator !=(const INFOTRDT &other) const
    {
    return !(*this == other);
    }

bool INFORecord::INFOResponse::IsNeutral()
    {
    return TRDT.value.emotionType == eNeutral;
    }

void INFORecord::INFOResponse::IsNeutral(bool value)
    {
    TRDT.value.emotionType = value ? eNeutral : eAnger;
    }

bool INFORecord::INFOResponse::IsAnger()
    {
    return TRDT.value.emotionType == eAnger;
    }

void INFORecord::INFOResponse::IsAnger(bool value)
    {
    TRDT.value.emotionType = value ? eAnger : eNeutral;
    }

bool INFORecord::INFOResponse::IsDisgust()
    {
    return TRDT.value.emotionType == eDisgust;
    }

void INFORecord::INFOResponse::IsDisgust(bool value)
    {
    TRDT.value.emotionType = value ? eDisgust : eNeutral;
    }

bool INFORecord::INFOResponse::IsFear()
    {
    return TRDT.value.emotionType == eFear;
    }

void INFORecord::INFOResponse::IsFear(bool value)
    {
    TRDT.value.emotionType = value ? eFear : eNeutral;
    }

bool INFORecord::INFOResponse::IsSad()
    {
    return TRDT.value.emotionType == eSad;
    }

void INFORecord::INFOResponse::IsSad(bool value)
    {
    TRDT.value.emotionType = value ? eSad : eNeutral;
    }

bool INFORecord::INFOResponse::IsHappy()
    {
    return TRDT.value.emotionType == eHappy;
    }

void INFORecord::INFOResponse::IsHappy(bool value)
    {
    TRDT.value.emotionType = value ? eHappy : eNeutral;
    }

bool INFORecord::INFOResponse::IsSurprise()
    {
    return TRDT.value.emotionType == eSurprise;
    }

void INFORecord::INFOResponse::IsSurprise(bool value)
    {
    TRDT.value.emotionType = value ? eSurprise : eNeutral;
    }

bool INFORecord::INFOResponse::IsPained()
    {
    return TRDT.value.emotionType == ePained;
    }

void INFORecord::INFOResponse::IsPained(bool value)
    {
    TRDT.value.emotionType = value ? ePained : eNeutral;
    }

bool INFORecord::INFOResponse::IsType(UINT32 Type)
    {
    return TRDT.value.emotionType == Type;
    }

void INFORecord::INFOResponse::SetType(UINT32 Type)
    {
    TRDT.value.emotionType = Type;
    }

bool INFORecord::INFOResponse::IsUseEmotionAnim()
    {
    return (TRDT.value.flags & fIsUseEmotionAnim) != 0;
    }

void INFORecord::INFOResponse::IsUseEmotionAnim(bool value)
    {
    TRDT.value.flags = value ? (TRDT.value.flags | fIsUseEmotionAnim) : (TRDT.value.flags & ~fIsUseEmotionAnim);
    }

bool INFORecord::INFOResponse::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((TRDT.value.flags & Mask) == Mask) : ((TRDT.value.flags & Mask) != 0);
    }

void INFORecord::INFOResponse::SetFlagMask(UINT8 Mask)
    {
    TRDT.value.flags = Mask;
    }

void INFORecord::INFOResponse::Write(FileWriter &writer)
    {
    WRITE(TRDT);
    WRITEREQ(NAM1);
    WRITEREQ(NAM2);
    WRITEREQ(NAM3);
    WRITE(SNAM);
    WRITE(LNAM);
    }

bool INFORecord::INFOResponse::operator ==(const INFOResponse &other) const
    {
    return (TRDT == other.TRDT &&
            NAM1.equals(other.NAM1) &&
            NAM2.equalsi(other.NAM2) &&
            NAM3.equalsi(other.NAM3) &&
            SNAM == other.SNAM &&
            LNAM == other.LNAM);
    }

bool INFORecord::INFOResponse::operator !=(const INFOResponse &other) const
    {
    return !(*this == other);
    }

INFORecord::INFORecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

INFORecord::INFORecord(INFORecord *srcRecord):
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

    DATA = srcRecord->DATA;
    QSTI = srcRecord->QSTI;
    TPIC = srcRecord->TPIC;
    PNAM = srcRecord->PNAM;
    NAME = srcRecord->NAME;
    Responses = srcRecord->Responses;
    CTDA = srcRecord->CTDA;
    TCLT = srcRecord->TCLT;
    TCLF = srcRecord->TCLF;
    TCFU = srcRecord->TCFU;
    BeginSCHR = srcRecord->BeginSCHR;
    BeginSCDA = srcRecord->BeginSCDA;
    BeginSCTX = srcRecord->BeginSCTX;
    BeginVARS = srcRecord->BeginVARS;
    BeginSCR_ = srcRecord->BeginSCR_;
    EndSCHR = srcRecord->EndSCHR;
    EndSCDA = srcRecord->EndSCDA;
    EndSCTX = srcRecord->EndSCTX;
    EndVARS = srcRecord->EndVARS;
    EndSCR_ = srcRecord->EndSCR_;
    SNDD = srcRecord->SNDD;
    RNAM = srcRecord->RNAM;
    ANAM = srcRecord->ANAM;
    KNAM = srcRecord->KNAM;
    DNAM = srcRecord->DNAM;
    return;
    }

INFORecord::~INFORecord()
    {
    //
    }

bool INFORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(QSTI.value);
    if(TPIC.IsLoaded())
        op.Accept(TPIC.value);
    if(PNAM.IsLoaded())
        op.Accept(PNAM.value);
    for(UINT32 ListIndex = 0; ListIndex < NAME.value.size(); ListIndex++)
        op.Accept(NAME.value[ListIndex]);
    for(UINT32 ListIndex = 0; ListIndex < Responses.value.size(); ListIndex++)
        {
        op.Accept(Responses.value[ListIndex]->TRDT.value.sound);
        op.Accept(Responses.value[ListIndex]->SNAM.value);
        op.Accept(Responses.value[ListIndex]->LNAM.value);
        }
    for(UINT32 ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);
    for(UINT32 ListIndex = 0; ListIndex < TCLT.value.size(); ListIndex++)
        op.Accept(TCLT.value[ListIndex]);
    for(UINT32 ListIndex = 0; ListIndex < TCLF.value.size(); ListIndex++)
        op.Accept(TCLF.value[ListIndex]);
    for(UINT32 ListIndex = 0; ListIndex < TCFU.value.size(); ListIndex++)
        op.Accept(TCFU.value[ListIndex]);
    for(UINT32 ListIndex = 0; ListIndex < BeginSCR_.value.size(); ListIndex++)
        {
        if(BeginSCR_.value[ListIndex]->isSCRO)
            op.Accept(BeginSCR_.value[ListIndex]->reference);
        }
    for(UINT32 ListIndex = 0; ListIndex < EndSCR_.value.size(); ListIndex++)
        {
        if(EndSCR_.value[ListIndex]->isSCRO)
            op.Accept(EndSCR_.value[ListIndex]->reference);
        }
    if(SNDD.IsLoaded())
        op.Accept(SNDD.value);
    if(ANAM.IsLoaded())
        op.Accept(ANAM.value);
    if(KNAM.IsLoaded())
        op.Accept(KNAM.value);

    return op.Stop();
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

bool INFORecord::IsSpeechChallenge()
    {
    return (DATA.value.flags & fIsSpeechChallenge) != 0;
    }

void INFORecord::IsSpeechChallenge(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsSpeechChallenge) : (DATA.value.flags & ~fIsSpeechChallenge);
    }

bool INFORecord::IsSayOnceADay()
    {
    return (DATA.value.flags & fIsSayOnceADay) != 0;
    }

void INFORecord::IsSayOnceADay(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsSayOnceADay) : (DATA.value.flags & ~fIsSayOnceADay);
    }

bool INFORecord::IsAlwaysDarken()
    {
    return (DATA.value.flags & fIsAlwaysDarken) != 0;
    }

void INFORecord::IsAlwaysDarken(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsAlwaysDarken) : (DATA.value.flags & ~fIsAlwaysDarken);
    }

bool INFORecord::IsFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (DATA.value.flags & Mask) == Mask : (DATA.value.flags & Mask) != 0;
    }

void INFORecord::SetFlagMask(UINT16 Mask)
    {
    DATA.value.flags = Mask;
    }

bool INFORecord::IsBeginScriptEnabled()
    {
    return (BeginSCHR.value.flags & fIsEnabled) != 0;
    }

void INFORecord::IsBeginScriptEnabled(bool value)
    {
    BeginSCHR.value.flags = value ? (BeginSCHR.value.flags | fIsEnabled) : (BeginSCHR.value.flags & ~fIsEnabled);
    }

bool INFORecord::IsBeginScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (BeginSCHR.value.flags & Mask) == Mask : (BeginSCHR.value.flags & Mask) != 0;
    }

void INFORecord::SetBeginScriptFlagMask(UINT16 Mask)
    {
    BeginSCHR.value.flags = Mask;
    }

bool INFORecord::IsEndScriptEnabled()
    {
    return (EndSCHR.value.flags & fIsEnabled) != 0;
    }

void INFORecord::IsEndScriptEnabled(bool value)
    {
    EndSCHR.value.flags = value ? (EndSCHR.value.flags | fIsEnabled) : (EndSCHR.value.flags & ~fIsEnabled);
    }

bool INFORecord::IsEndScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (EndSCHR.value.flags & Mask) == Mask : (EndSCHR.value.flags & Mask) != 0;
    }

void INFORecord::SetEndScriptFlagMask(UINT16 Mask)
    {
    EndSCHR.value.flags = Mask;
    }

bool INFORecord::IsTopic()
    {
    return DATA.value.dialType == eTopic;
    }

void INFORecord::IsTopic(bool value)
    {       
    DATA.value.dialType = value ? eTopic : eConversation;
    }

bool INFORecord::IsConversation()
    {
    return DATA.value.dialType == eConversation;
    }

void INFORecord::IsConversation(bool value)
    {
    DATA.value.dialType = value ? eConversation : eTopic;
    }

bool INFORecord::IsCombat()
    {
    return DATA.value.dialType == eCombat;
    }

void INFORecord::IsCombat(bool value)
    {
    DATA.value.dialType = value ? eCombat : eTopic;
    }

bool INFORecord::IsPersuasion()
    {
    return DATA.value.dialType == ePersuasion;
    }

void INFORecord::IsPersuasion(bool value)
    {
    DATA.value.dialType = value ? ePersuasion : eTopic;
    }

bool INFORecord::IsDetection()
    {
    return DATA.value.dialType == eDetection;
    }

void INFORecord::IsDetection(bool value)
    {
    DATA.value.dialType = value ? eDetection : eTopic;
    }

bool INFORecord::IsService()
    {
    return DATA.value.dialType == eService;
    }

void INFORecord::IsService(bool value)
    {
    DATA.value.dialType = value ? eService : eTopic;
    }

bool INFORecord::IsMisc()
    {
    return DATA.value.dialType == eMisc;
    }

void INFORecord::IsMisc(bool value)
    {
    DATA.value.dialType = value ? eMisc : eTopic;
    }

bool INFORecord::IsRadio()
    {
    return DATA.value.dialType == eRadio;
    }

void INFORecord::IsRadio(bool value)
    {
    DATA.value.dialType = value ? eRadio : eTopic;
    }

bool INFORecord::IsDialogType(UINT8 Type)
    {
    return DATA.value.dialType == Type;
    }

void INFORecord::SetDialogType(UINT8 Type)
    {
    DATA.value.dialType = Type;
    }

bool INFORecord::IsTarget()
    {
    return DATA.value.nextSpeaker == eTarget;
    }

void INFORecord::IsTarget(bool value)
    {
    DATA.value.nextSpeaker = value ? eTarget : eSelf;
    }

bool INFORecord::IsSelf()
    {
    return DATA.value.nextSpeaker == eSelf;
    }

void INFORecord::IsSelf(bool value)
    {
    DATA.value.nextSpeaker = value ? eSelf : eTarget;
    }

bool INFORecord::IsEither()
    {
    return DATA.value.nextSpeaker == eEither;
    }

void INFORecord::IsEither(bool value)
    {
    DATA.value.nextSpeaker = value ? eEither : eTarget;
    }

bool INFORecord::IsSpeakerType(UINT8 Type)
    {
    return DATA.value.nextSpeaker == Type;
    }

void INFORecord::SetSpeakerType(UINT8 Type)
    {
    DATA.value.nextSpeaker = Type;
    }

bool INFORecord::IsNone()
    {
    return DNAM.value == eNone;
    }

void INFORecord::IsNone(bool value)
    {
    DNAM.value = value ? eNone : eVeryEasy;
    }

bool INFORecord::IsVeryEasy()
    {
    return DNAM.value == eVeryEasy;
    }

void INFORecord::IsVeryEasy(bool value)
    {
    DNAM.value = value ? eVeryEasy : eNone;
    }

bool INFORecord::IsEasy()
    {
    return DNAM.value == eEasy;
    }

void INFORecord::IsEasy(bool value)
    {
    DNAM.value = value ? eEasy : eNone;
    }

bool INFORecord::IsAverage()
    {
    return DNAM.value == eAverage;
    }

void INFORecord::IsAverage(bool value)
    {
    DNAM.value = value ? eAverage : eNone;
    }

bool INFORecord::IsHard()
    {
    return DNAM.value == eHard;
    }

void INFORecord::IsHard(bool value)
    {
    DNAM.value = value ? eHard : eNone;
    }

bool INFORecord::IsVeryHard()
    {
    return DNAM.value == eVeryHard;
    }

void INFORecord::IsVeryHard(bool value)
    {
    DNAM.value = value ? eVeryHard : eNone;
    }

bool INFORecord::IsDifficultyType(UINT8 Type)
    {
    return DNAM.value == Type;
    }

void INFORecord::SetDifficultyType(UINT8 Type)
    {
    DNAM.value = Type;
    }

bool INFORecord::IsBeginObject()
    {
    return BeginSCHR.value.scriptType == eObject;
    }

void INFORecord::IsBeginObject(bool value)
    {
    BeginSCHR.value.scriptType = value ? eObject : eQuest;
    }

bool INFORecord::IsBeginQuest()
    {
    return BeginSCHR.value.scriptType == eQuest;
    }

void INFORecord::IsBeginQuest(bool value)
    {
    BeginSCHR.value.scriptType = value ? eQuest : eObject;
    }

bool INFORecord::IsBeginEffect()
    {
    return BeginSCHR.value.scriptType == eEffect;
    }

void INFORecord::IsBeginEffect(bool value)
    {
    BeginSCHR.value.scriptType = value ? eEffect : eObject;
    }

bool INFORecord::IsBeginType(UINT16 Type)
    {
    return BeginSCHR.value.scriptType == Type;
    }

void INFORecord::SetBeginType(UINT16 Type)
    {
    BeginSCHR.value.scriptType = Type;
    }

bool INFORecord::IsEndObject()
    {
    return EndSCHR.value.scriptType == eObject;
    }

void INFORecord::IsEndObject(bool value)
    {
    EndSCHR.value.scriptType = value ? eObject : eQuest;
    }

bool INFORecord::IsEndQuest()
    {
    return EndSCHR.value.scriptType == eQuest;
    }

void INFORecord::IsEndQuest(bool value)
    {
    EndSCHR.value.scriptType = value ? eQuest : eObject;
    }

bool INFORecord::IsEndEffect()
    {
    return EndSCHR.value.scriptType == eEffect;
    }

void INFORecord::IsEndEffect(bool value)
    {
    EndSCHR.value.scriptType = value ? eEffect : eObject;
    }

bool INFORecord::IsEndType(UINT16 Type)
    {
    return EndSCHR.value.scriptType == Type;
    }

void INFORecord::SetEndType(UINT16 Type)
    {
    EndSCHR.value.scriptType = Type;
    }

UINT32 INFORecord::GetType()
    {
    return REV32(INFO);
    }

STRING INFORecord::GetStrType()
    {
    return "INFO";
    }

UINT32 INFORecord::GetParentType()
    {
    return REV32(DIAL);
    }

SINT32 INFORecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    UINT32 lastChunk = REV32(NONE);
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
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(QSTI):
                QSTI.Read(buffer, subSize, curPos);
                break;
            case REV32(TPIC):
                TPIC.Read(buffer, subSize, curPos);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(NAME):
                NAME.Read(buffer, subSize, curPos);
                break;
            case REV32(TRDT):
                Responses.value.push_back(new INFOResponse);
                Responses.value.back()->TRDT.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM1):
                if(Responses.value.size() == 0)
                    Responses.value.push_back(new INFOResponse);
                Responses.value.back()->NAM1.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM2):
                if(Responses.value.size() == 0)
                    Responses.value.push_back(new INFOResponse);
                Responses.value.back()->NAM2.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM3):
                if(Responses.value.size() == 0)
                    Responses.value.push_back(new INFOResponse);
                Responses.value.back()->NAM3.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                if(Responses.value.size() == 0)
                    Responses.value.push_back(new INFOResponse);
                Responses.value.back()->SNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(LNAM):
                if(Responses.value.size() == 0)
                    Responses.value.push_back(new INFOResponse);
                Responses.value.back()->LNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize, curPos);
                break;
            case REV32(TCLT):
                TCLT.Read(buffer, subSize, curPos);
                break;
            case REV32(TCLF):
                TCLF.Read(buffer, subSize, curPos);
                break;
            case REV32(TCFU):
                TCFU.Read(buffer, subSize, curPos);
                break;
            case REV32(SCHR):
                switch(lastChunk)
                    {
                    case REV32(NONE):
                        BeginSCHR.Read(buffer, subSize, curPos);
                        break;
                    case REV32(NEXT):
                        EndSCHR.Read(buffer, subSize, curPos);
                        break;
                    default:
                        printf("  INFO: %08X - Unexpected SCHR chunk\n", formID);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(SCDA):
                switch(lastChunk)
                    {
                    case REV32(NONE):
                        BeginSCDA.Read(buffer, subSize, curPos);
                        break;
                    case REV32(NEXT):
                        EndSCDA.Read(buffer, subSize, curPos);
                        break;
                    default:
                        printf("  INFO: %08X - Unexpected SCDA chunk\n", formID);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(SCTX):
                switch(lastChunk)
                    {
                    case REV32(NONE):
                        BeginSCTX.Read(buffer, subSize, curPos);
                        break;
                    case REV32(NEXT):
                        EndSCTX.Read(buffer, subSize, curPos);
                        break;
                    default:
                        printf("  INFO: %08X - Unexpected SCTX chunk\n", formID);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(SLSD):      
                switch(lastChunk)
                    {
                    case REV32(NONE):
                        BeginVARS.value.push_back(new GENVARS);
                        BeginVARS.value.back()->SLSD.Read(buffer, subSize, curPos);
                        break;
                    case REV32(NEXT):
                        EndVARS.value.push_back(new GENVARS);
                        EndVARS.value.back()->SLSD.Read(buffer, subSize, curPos);
                        break;
                    default:
                        printf("  INFO: %08X - Unexpected SLSD chunk\n", formID);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(SCVR):
                switch(lastChunk)
                    {
                    case REV32(NONE):
                        if(BeginVARS.value.size() == 0)
                            BeginVARS.value.push_back(new GENVARS);
                        BeginVARS.value.back()->SCVR.Read(buffer, subSize, curPos);
                        break;
                    case REV32(NEXT):
                        if(EndVARS.value.size() == 0)
                            EndVARS.value.push_back(new GENVARS);
                        EndVARS.value.back()->SCVR.Read(buffer, subSize, curPos);
                        break;
                    default:
                        printf("  INFO: %08X - Unexpected SCVR chunk\n", formID);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(SCRV):
                switch(lastChunk)
                    {
                    case REV32(NONE):
                        BeginSCR_.Read(buffer, subSize, curPos);
                        BeginSCR_.value.back()->isSCRO = false;
                        break;
                    case REV32(NEXT):
                        EndSCR_.Read(buffer, subSize, curPos);
                        EndSCR_.value.back()->isSCRO = false;
                        break;
                    default:
                        printf("  INFO: %08X - Unexpected SCRV chunk\n", formID);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(SCRO):
                switch(lastChunk)
                    {
                    case REV32(NONE):
                        BeginSCR_.Read(buffer, subSize, curPos);
                        BeginSCR_.value.back()->isSCRO = true;
                        break;
                    case REV32(NEXT):
                        EndSCR_.Read(buffer, subSize, curPos);
                        EndSCR_.value.back()->isSCRO = true;
                        break;
                    default:
                        printf("  INFO: %08X - Unexpected SCRO chunk\n", formID);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(NEXT):
                lastChunk = REV32(NEXT);
                break;
            case REV32(SNDD):
                SNDD.Read(buffer, subSize, curPos);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize, curPos);
                break;
            case REV32(KNAM):
                KNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  INFO: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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
    TCFU.Unload();
    BeginSCHR.Unload();
    BeginSCDA.Unload();
    BeginSCTX.Unload();
    BeginVARS.Unload();
    BeginSCR_.Unload();
    EndSCHR.Unload();
    EndSCDA.Unload();
    EndSCTX.Unload();
    EndVARS.Unload();
    EndSCR_.Unload();
    SNDD.Unload();
    RNAM.Unload();
    ANAM.Unload();
    KNAM.Unload();
    DNAM.Unload();
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
    CTDA.Write(REV32(CTDA), writer, true);
    WRITE(TCLT);
    WRITE(TCLF);
    WRITE(TCFU);
    BeginSCHR.value.numRefs = BeginSCR_.value.size(); //Just to ensure that the value is correct
    BeginSCHR.value.compiledSize = BeginSCDA.GetSize(); //Just to ensure that the value is correct
    //for(UINT32 x = 0; x < BeginVARS.value.size(); ++x) //Just to ensure that the value is correct
    //    BeginSCHR.value.lastIndex = (BeginSCHR.value.lastIndex > BeginVARS.value[x]->SLSD.value.index) ? BeginSCHR.value.lastIndex : BeginVARS.value[x]->SLSD.value.index;
    WRITEAS(BeginSCHR, SCHR);
    WRITEAS(BeginSCDA, SCDA);
    WRITEAS(BeginSCTX, SCTX);
    BeginVARS.Write(writer);
    BeginSCR_.Write(writer, true);
    WRITEEMPTY(NEXT);
    EndSCHR.value.numRefs = EndSCR_.value.size(); //Just to ensure that the value is correct
    EndSCHR.value.compiledSize = EndSCDA.GetSize(); //Just to ensure that the value is correct
    //for(UINT32 x = 0; x < EndVARS.value.size(); ++x) //Just to ensure that the value is correct
    //    EndSCHR.value.lastIndex = (EndSCHR.value.lastIndex > EndVARS.value[x]->SLSD.value.index) ? EndSCHR.value.lastIndex : EndVARS.value[x]->SLSD.value.index;
    WRITEAS(EndSCHR, SCHR);
    WRITEAS(EndSCDA, SCDA);
    WRITEAS(EndSCTX, SCTX);
    EndVARS.Write(writer);
    EndSCR_.Write(writer, true);

    WRITE(SNDD);
    WRITE(RNAM);
    WRITE(ANAM);
    WRITE(KNAM);
    WRITE(DNAM);
    return -1;
    }

bool INFORecord::operator ==(const INFORecord &other) const
    {
    return (DATA == other.DATA &&
            QSTI == other.QSTI &&
            TPIC == other.TPIC &&
            PNAM == other.PNAM &&
            SNDD == other.SNDD &&
            ANAM == other.ANAM &&
            KNAM == other.KNAM &&
            DNAM == other.DNAM &&
            TCLT == other.TCLT &&
            TCLF == other.TCLF &&
            TCFU == other.TCFU &&
            NAME == other.NAME &&
            RNAM.equals(other.RNAM) &&
            Responses == other.Responses &&
            BeginSCHR == other.BeginSCHR &&
            BeginSCDA == other.BeginSCDA &&
            BeginSCTX.equalsi(other.BeginSCTX) &&
            BeginVARS == other.BeginVARS &&
            BeginSCR_ == other.BeginSCR_ &&
            EndSCHR == other.EndSCHR &&
            EndSCDA == other.EndSCDA &&
            EndSCTX.equalsi(other.EndSCTX) &&
            EndVARS == other.EndVARS &&
            EndSCR_ == other.EndSCR_ &&
            CTDA == other.CTDA);
    }

bool INFORecord::operator !=(const INFORecord &other) const
    {
    return !(*this == other);
    }
}