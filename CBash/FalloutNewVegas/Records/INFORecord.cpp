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
    TRDT = srcRecord->TRDT;
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    NAM3 = srcRecord->NAM3;
    SNAM = srcRecord->SNAM;
    LNAM = srcRecord->LNAM;
    CTDA = srcRecord->CTDA;
    TCLT = srcRecord->TCLT;
    TCLF = srcRecord->TCLF;
    TCFU = srcRecord->TCFU;
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
    NEXT = srcRecord->NEXT;
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

    if(QSTI.IsLoaded())
        op.Accept(QSTI->value);
    if(TPIC.IsLoaded())
        op.Accept(TPIC->value);
    if(PNAM.IsLoaded())
        op.Accept(PNAM->value);
    if(NAME.IsLoaded())
        op.Accept(NAME->value);
    //if(TRDT.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(TRDT->value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);
    if(LNAM.IsLoaded())
        op.Accept(LNAM->value);
    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    if(TCLT.IsLoaded())
        op.Accept(TCLT->value);
    if(TCLF.IsLoaded())
        op.Accept(TCLF->value);
    if(TCFU.IsLoaded())
        op.Accept(TCFU->value);
    if(SCHR.IsLoaded() && SCHR->SCRO.IsLoaded())
        op.Accept(SCHR->SCRO->value);
    if(SNDD.IsLoaded())
        op.Accept(SNDD->value);
    if(ANAM.IsLoaded())
        op.Accept(ANAM->value);
    if(KNAM.IsLoaded())
        op.Accept(KNAM->value);

    return op.Stop();
    }

bool INFORecord::IsGoodbye()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsGoodbye) != 0;
    }

void INFORecord::IsGoodbye(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsGoodbye) : (Dummy->flags & ~fIsGoodbye);
    }

bool INFORecord::IsRandom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRandom) != 0;
    }

void INFORecord::IsRandom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRandom) : (Dummy->flags & ~fIsRandom);
    }

bool INFORecord::IsSayOnce()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSayOnce) != 0;
    }

void INFORecord::IsSayOnce(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsSayOnce) : (Dummy->flags & ~fIsSayOnce);
    }

bool INFORecord::IsRunImmediately()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRunImmediately) != 0;
    }

void INFORecord::IsRunImmediately(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRunImmediately) : (Dummy->flags & ~fIsRunImmediately);
    }

bool INFORecord::IsInfoRefusal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsInfoRefusal) != 0;
    }

void INFORecord::IsInfoRefusal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsInfoRefusal) : (Dummy->flags & ~fIsInfoRefusal);
    }

bool INFORecord::IsRandomEnd()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRandomEnd) != 0;
    }

void INFORecord::IsRandomEnd(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRandomEnd) : (Dummy->flags & ~fIsRandomEnd);
    }

bool INFORecord::IsRunForRumors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRunForRumors) != 0;
    }

void INFORecord::IsRunForRumors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRunForRumors) : (Dummy->flags & ~fIsRunForRumors);
    }

bool INFORecord::IsSpeechChallenge()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSpeechChallenge) != 0;
    }

void INFORecord::IsSpeechChallenge(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsSpeechChallenge) : (Dummy->flags & ~fIsSpeechChallenge);
    }

bool INFORecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void INFORecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool INFORecord::IsSayOnceADay()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSayOnceADay) != 0;
    }

void INFORecord::IsSayOnceADay(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsSayOnceADay) : (Dummy->flags & ~fIsSayOnceADay);
    }

bool INFORecord::IsAlwaysDarken()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAlwaysDarken) != 0;
    }

void INFORecord::IsAlwaysDarken(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsAlwaysDarken) : (Dummy->flags & ~fIsAlwaysDarken);
    }

bool INFORecord::IsExtraFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void INFORecord::SetExtraFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool INFORecord::IsTopic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTopic);
    }

void INFORecord::IsTopic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTopic : eDummyDefault;
    }

bool INFORecord::IsConversation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eConversation);
    }

void INFORecord::IsConversation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eConversation : eDummyDefault;
    }

bool INFORecord::IsCombat()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCombat);
    }

void INFORecord::IsCombat(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCombat : eDummyDefault;
    }

bool INFORecord::IsPersuasion()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePersuasion);
    }

void INFORecord::IsPersuasion(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePersuasion : eDummyDefault;
    }

bool INFORecord::IsDetection()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDetection);
    }

void INFORecord::IsDetection(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDetection : eDummyDefault;
    }

bool INFORecord::IsService()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eService);
    }

void INFORecord::IsService(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eService : eDummyDefault;
    }

bool INFORecord::IsMisc()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMisc);
    }

void INFORecord::IsMisc(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMisc : eDummyDefault;
    }

bool INFORecord::IsRadio()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRadio);
    }

void INFORecord::IsRadio(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRadio : eDummyDefault;
    }

bool INFORecord::IsDialogType(UINT16 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void INFORecord::SetDialogType(UINT16 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool INFORecord::IsTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTarget);
    }

void INFORecord::IsTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTarget : eDummyDefault;
    }

bool INFORecord::IsSelf()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSelf);
    }

void INFORecord::IsSelf(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSelf : eDummyDefault;
    }

bool INFORecord::IsEither()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEither);
    }

void INFORecord::IsEither(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEither : eDummyDefault;
    }

bool INFORecord::IsSpeakerType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void INFORecord::SetSpeakerType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool INFORecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void INFORecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool INFORecord::IsVeryEasy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryEasy);
    }

void INFORecord::IsVeryEasy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVeryEasy : eDummyDefault;
    }

bool INFORecord::IsEasy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEasy);
    }

void INFORecord::IsEasy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEasy : eDummyDefault;
    }

bool INFORecord::IsAverage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAverage);
    }

void INFORecord::IsAverage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAverage : eDummyDefault;
    }

bool INFORecord::IsHard()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHard);
    }

void INFORecord::IsHard(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHard : eDummyDefault;
    }

bool INFORecord::IsVeryHard()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryHard);
    }

void INFORecord::IsVeryHard(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eVeryHard : eDummyDefault;
    }

bool INFORecord::IsDifficultyType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void INFORecord::SetDifficultyType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 INFORecord::GetType()
    {
    return REV32(INFO);
    }

STRING INFORecord::GetStrType()
    {
    return "INFO";
    }

SINT32 INFORecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                TRDT.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize, curPos);
                break;
            case REV32(NAM3):
                NAM3.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize, curPos);
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
                SCHR.Load();
                SCHR->SCHR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCDA):
                SCHR.Load();
                SCHR->SCDA.Read(buffer, subSize, curPos);
                break;
            case REV32(SCTX):
                SCHR.Load();
                SCHR->SCTX.Read(buffer, subSize, curPos);
                break;
            case REV32(SLSD):
                SCHR.Load();
                SCHR->SLSD.Read(buffer, subSize, curPos);
                break;
            case REV32(SCVR):
                SCHR.Load();
                SCHR->SCVR.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRO):
                SCHR.Load();
                SCHR->SCRO.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRV):
                SCHR.Load();
                SCHR->SCRV.Read(buffer, subSize, curPos);
                break;
            case REV32(NEXT):
                //NEXT.Read(buffer, subSize, curPos); //FILL IN MANUALLY
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
    TRDT.Unload();
    NAM1.Unload();
    NAM2.Unload();
    NAM3.Unload();
    SNAM.Unload();
    LNAM.Unload();
    CTDA.Unload();
    TCLT.Unload();
    TCLF.Unload();
    TCFU.Unload();
    SCHR.Unload();
    //NEXT.Unload(); //FILL IN MANUALLY
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
    WRITE(TRDT);
    WRITE(NAM1);
    WRITE(NAM2);
    WRITE(NAM3);
    WRITE(SNAM);
    WRITE(LNAM);
    WRITE(CTDA);
    WRITE(TCLT);
    WRITE(TCLF);
    WRITE(TCFU);

    if(SCHR.IsLoaded())
        {
        if(SCHR->SCHR.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCHR), SCHR->SCHR.value, SCHR->SCHR.GetSize());

        if(SCHR->SCDA.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCDA), SCHR->SCDA.value, SCHR->SCDA.GetSize());

        if(SCHR->SCTX.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCTX), SCHR->SCTX.value, SCHR->SCTX.GetSize());

        if(SCHR->SLSD.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SLSD), SCHR->SLSD.value, SCHR->SLSD.GetSize());

        if(SCHR->SCVR.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCVR), SCHR->SCVR.value, SCHR->SCVR.GetSize());

        if(SCHR->SCRO.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCRO), SCHR->SCRO.value, SCHR->SCRO.GetSize());

        if(SCHR->SCRV.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCRV), SCHR->SCRV.value, SCHR->SCRV.GetSize());

        }

    //if(NEXT.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NEXT), NEXT.value, NEXT.GetSize());
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
            NAME == other.NAME &&
            TRDT == other.TRDT &&
            NAM1.equalsi(other.NAM1) &&
            NAM2.equalsi(other.NAM2) &&
            NAM3.equalsi(other.NAM3) &&
            SNAM == other.SNAM &&
            LNAM == other.LNAM &&
            CTDA == other.CTDA &&
            TCLT == other.TCLT &&
            TCLF == other.TCLF &&
            TCFU == other.TCFU &&
            SCHR == other.SCHR &&
            //Empty &&
            SNDD == other.SNDD &&
            RNAM.equalsi(other.RNAM) &&
            ANAM == other.ANAM &&
            KNAM == other.KNAM &&
            DNAM == other.DNAM);
    }

bool INFORecord::operator !=(const INFORecord &other) const
    {
    return !(*this == other);
    }
}