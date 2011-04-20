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
    Record(_recData)
    {
    //
    }

INFORecord::INFORecord(INFORecord *srcRecord):
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
    if(value)
        Dummy->flags |= fIsGoodbye;
    else
        Dummy->flags &= ~fIsGoodbye;
    }

bool INFORecord::IsRandom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRandom) != 0;
    }

void INFORecord::IsRandom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRandom;
    else
        Dummy->flags &= ~fIsRandom;
    }

bool INFORecord::IsSayOnce()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSayOnce) != 0;
    }

void INFORecord::IsSayOnce(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsSayOnce;
    else
        Dummy->flags &= ~fIsSayOnce;
    }

bool INFORecord::IsRunImmediately()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRunImmediately) != 0;
    }

void INFORecord::IsRunImmediately(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRunImmediately;
    else
        Dummy->flags &= ~fIsRunImmediately;
    }

bool INFORecord::IsInfoRefusal()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsInfoRefusal) != 0;
    }

void INFORecord::IsInfoRefusal(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsInfoRefusal;
    else
        Dummy->flags &= ~fIsInfoRefusal;
    }

bool INFORecord::IsRandomEnd()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRandomEnd) != 0;
    }

void INFORecord::IsRandomEnd(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRandomEnd;
    else
        Dummy->flags &= ~fIsRandomEnd;
    }

bool INFORecord::IsRunForRumors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRunForRumors) != 0;
    }

void INFORecord::IsRunForRumors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsRunForRumors;
    else
        Dummy->flags &= ~fIsRunForRumors;
    }

bool INFORecord::IsSpeechChallenge()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSpeechChallenge) != 0;
    }

void INFORecord::IsSpeechChallenge(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsSpeechChallenge;
    else
        Dummy->flags &= ~fIsSpeechChallenge;
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
    if(value)
        Dummy->flags |= fIsSayOnceADay;
    else
        Dummy->flags &= ~fIsSayOnceADay;
    }

bool INFORecord::IsAlwaysDarken()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAlwaysDarken) != 0;
    }

void INFORecord::IsAlwaysDarken(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsAlwaysDarken;
    else
        Dummy->flags &= ~fIsAlwaysDarken;
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
    if(value)
        Dummy->flags = eTopic;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsConversation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eConversation);
    }

void INFORecord::IsConversation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eConversation;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsCombat()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCombat);
    }

void INFORecord::IsCombat(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCombat;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsPersuasion()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePersuasion);
    }

void INFORecord::IsPersuasion(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = ePersuasion;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsDetection()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDetection);
    }

void INFORecord::IsDetection(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDetection;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsService()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eService);
    }

void INFORecord::IsService(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eService;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsMisc()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMisc);
    }

void INFORecord::IsMisc(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eMisc;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsRadio()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRadio);
    }

void INFORecord::IsRadio(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eRadio;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsDialogType(UINT16 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
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
    if(value)
        Dummy->flags = eTarget;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsSelf()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSelf);
    }

void INFORecord::IsSelf(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eSelf;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsEither()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEither);
    }

void INFORecord::IsEither(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eEither;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsSpeakerType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
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
    if(value)
        Dummy->flags = eNone;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsVeryEasy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryEasy);
    }

void INFORecord::IsVeryEasy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eVeryEasy;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsEasy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEasy);
    }

void INFORecord::IsEasy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eEasy;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsAverage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAverage);
    }

void INFORecord::IsAverage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAverage;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsHard()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHard);
    }

void INFORecord::IsHard(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHard;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsVeryHard()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryHard);
    }

void INFORecord::IsVeryHard(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eVeryHard;
    else
        Dummy->flags = eDummyDefault;
    }

bool INFORecord::IsDifficultyType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void INFORecord::SetDifficultyType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 INFORecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-16];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(QSTI.IsLoaded())
        TotSize += QSTI.GetSize() + 6;

    if(TPIC.IsLoaded())
        TotSize += TPIC.GetSize() + 6;

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(NAME.IsLoaded())
        TotSize += NAME.GetSize() + 6;

    if(TRDT.IsLoaded())
        TotSize += TRDT.GetSize() + 6;

    if(NAM1.IsLoaded())
        {
        cSize = NAM1.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM2.IsLoaded())
        {
        cSize = NAM2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM3.IsLoaded())
        {
        cSize = NAM3.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(LNAM.IsLoaded())
        TotSize += LNAM.GetSize() + 6;

    if(CTDA.IsLoaded())
        TotSize += CTDA.GetSize() + 6;

    if(TCLT.IsLoaded())
        TotSize += TCLT.GetSize() + 6;

    if(TCLF.IsLoaded())
        TotSize += TCLF.GetSize() + 6;

    if(TCFU.IsLoaded())
        TotSize += TCFU.GetSize() + 6;

    if(SCHR.IsLoaded())
        {
        if(SCHR->SCHR.IsLoaded())
            TotSize += SCHR->SCHR.GetSize() + 6;
        if(SCHR->SCDA.IsLoaded())
            {
            cSize = SCHR->SCDA.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(SCHR->SCTX.IsLoaded())
            {
            cSize = SCHR->SCTX.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(SCHR->SLSD.IsLoaded())
            TotSize += SCHR->SLSD.GetSize() + 6;
        if(SCHR->SCVR.IsLoaded())
            {
            cSize = SCHR->SCVR.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(SCHR->SCRO.IsLoaded())
            TotSize += SCHR->SCRO.GetSize() + 6;
        if(SCHR->SCRV.IsLoaded())
            TotSize += SCHR->SCRV.GetSize() + 6;
        }

    if(NEXT.IsLoaded())
        TotSize += NEXT.GetSize() + 6;

    if(SNDD.IsLoaded())
        TotSize += SNDD.GetSize() + 6;

    if(RNAM.IsLoaded())
        {
        cSize = RNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;

    if(KNAM.IsLoaded())
        TotSize += KNAM.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 INFORecord::GetType()
    {
    return 'OFNI';
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
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'ITSQ':
                QSTI.Read(buffer, subSize, curPos);
                break;
            case 'CIPT':
                TPIC.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'EMAN':
                NAME.Read(buffer, subSize, curPos);
                break;
            case 'TDRT':
                TRDT.Read(buffer, subSize, curPos);
                break;
            case '1MAN':
                NAM1.Read(buffer, subSize, curPos);
                break;
            case '2MAN':
                NAM2.Read(buffer, subSize, curPos);
                break;
            case '3MAN':
                NAM3.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANL':
                LNAM.Read(buffer, subSize, curPos);
                break;
            case 'ADTC':
                CTDA.Read(buffer, subSize, curPos);
                break;
            case 'TLCT':
                TCLT.Read(buffer, subSize, curPos);
                break;
            case 'FLCT':
                TCLF.Read(buffer, subSize, curPos);
                break;
            case 'UFCT':
                TCFU.Read(buffer, subSize, curPos);
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
            case 'TXEN':
                //NEXT.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'DDNS':
                SNDD.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'MANK':
                KNAM.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
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

SINT32 INFORecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(QSTI.IsLoaded())
        SaveHandler.writeSubRecord('ITSQ', QSTI.value, QSTI.GetSize());

    if(TPIC.IsLoaded())
        SaveHandler.writeSubRecord('CIPT', TPIC.value, TPIC.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', PNAM.value, PNAM.GetSize());

    if(NAME.IsLoaded())
        SaveHandler.writeSubRecord('EMAN', NAME.value, NAME.GetSize());

    if(TRDT.IsLoaded())
        SaveHandler.writeSubRecord('TDRT', TRDT.value, TRDT.GetSize());

    if(NAM1.IsLoaded())
        SaveHandler.writeSubRecord('1MAN', NAM1.value, NAM1.GetSize());

    if(NAM2.IsLoaded())
        SaveHandler.writeSubRecord('2MAN', NAM2.value, NAM2.GetSize());

    if(NAM3.IsLoaded())
        SaveHandler.writeSubRecord('3MAN', NAM3.value, NAM3.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(LNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANL', LNAM.value, LNAM.GetSize());

    if(CTDA.IsLoaded())
        SaveHandler.writeSubRecord('ADTC', CTDA.value, CTDA.GetSize());

    if(TCLT.IsLoaded())
        SaveHandler.writeSubRecord('TLCT', TCLT.value, TCLT.GetSize());

    if(TCLF.IsLoaded())
        SaveHandler.writeSubRecord('FLCT', TCLF.value, TCLF.GetSize());

    if(TCFU.IsLoaded())
        SaveHandler.writeSubRecord('UFCT', TCFU.value, TCFU.GetSize());

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

    //if(NEXT.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('TXEN', NEXT.value, NEXT.GetSize());

    if(SNDD.IsLoaded())
        SaveHandler.writeSubRecord('DDNS', SNDD.value, SNDD.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord('MANA', ANAM.value, ANAM.GetSize());

    if(KNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANK', KNAM.value, KNAM.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

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