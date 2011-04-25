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
#include "TERMRecord.h"

namespace FNV
{
bool TERMRecord::TERMMenu::IsAddNote()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAddNote) != 0;
    }

void TERMRecord::TERMMenu::IsAddNote(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsAddNote;
    else
        Dummy->flags &= ~fIsAddNote;
    }

bool TERMRecord::TERMMenu::IsForceRedraw()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsForceRedraw) != 0;
    }

void TERMRecord::TERMMenu::IsForceRedraw(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsForceRedraw;
    else
        Dummy->flags &= ~fIsForceRedraw;
    }

bool TERMRecord::TERMMenu::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void TERMRecord::TERMMenu::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool TERMRecord::TERMMenu::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void TERMRecord::TERMMenu::IsScriptEnabled(bool value)
    {
    if(value)
        SCHR.value.flags |= fIsEnabled;
    else
        SCHR.value.flags &= ~fIsEnabled;
    }

bool TERMRecord::TERMMenu::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    if(Exact)
        return (SCHR.value.flags & Mask) == Mask;
    else
        return (SCHR.value.flags & Mask) != 0;
    }

void TERMRecord::TERMMenu::SetScriptFlagMask(UINT16 Mask)
    {
    SCHR.value.flags = Mask;
    }

TERMRecord::TERMRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

TERMRecord::TERMRecord(TERMRecord *srcRecord):
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
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    SCRI = srcRecord->SCRI;
    if(srcRecord->DEST.IsLoaded())
        {
        DEST.Load();
        DEST->DEST = srcRecord->DEST->DEST;
        DEST->DSTD = srcRecord->DEST->DSTD;
        DEST->DMDL = srcRecord->DEST->DMDL;
        DEST->DMDT = srcRecord->DEST->DMDT;
        DEST->DSTF = srcRecord->DEST->DSTF;
        }
    DESC = srcRecord->DESC;
    SNAM = srcRecord->SNAM;
    PNAM = srcRecord->PNAM;
    DNAM = srcRecord->DNAM;
    if(srcRecord->ITXT.IsLoaded())
        {
        ITXT.Load();
        ITXT->ITXT = srcRecord->ITXT->ITXT;
        ITXT->RNAM = srcRecord->ITXT->RNAM;
        ITXT->ANAM = srcRecord->ITXT->ANAM;
        }
    INAM = srcRecord->INAM;
    TNAM = srcRecord->TNAM;
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
    CTDA = srcRecord->CTDA;
    return;
    }

TERMRecord::~TERMRecord()
    {
    //
    }

bool TERMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    if(DEST.IsLoaded() && DEST->DSTD.IsLoaded())
        op.Accept(DEST->DSTD->value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);
    if(PNAM.IsLoaded())
        op.Accept(PNAM->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM->value);
    if(SCHR.IsLoaded() && SCHR->SCRO.IsLoaded())
        op.Accept(SCHR->SCRO->value);
    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);

    return op.Stop();
    }

bool TERMRecord::IsLeveled()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsLeveled) != 0;
    }

void TERMRecord::IsLeveled(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsLeveled;
    else
        Dummy->flags &= ~fIsLeveled;
    }

bool TERMRecord::IsUnlocked()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnlocked) != 0;
    }

void TERMRecord::IsUnlocked(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnlocked;
    else
        Dummy->flags &= ~fIsUnlocked;
    }

bool TERMRecord::IsAlternateColors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAlternateColors) != 0;
    }

void TERMRecord::IsAlternateColors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsAlternateColors;
    else
        Dummy->flags &= ~fIsAlternateColors;
    }

bool TERMRecord::IsHideWelcomeTextWhenDisplayingImage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsHideWelcomeTextWhenDisplayingImage) != 0;
    }

void TERMRecord::IsHideWelcomeTextWhenDisplayingImage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsHideWelcomeTextWhenDisplayingImage;
    else
        Dummy->flags &= ~fIsHideWelcomeTextWhenDisplayingImage;
    }

bool TERMRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void TERMRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool TERMRecord::IsVeryEasy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryEasy);
    }

void TERMRecord::IsVeryEasy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eVeryEasy;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsEasy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEasy);
    }

void TERMRecord::IsEasy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eEasy;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsAverage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAverage);
    }

void TERMRecord::IsAverage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAverage;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsHard()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHard);
    }

void TERMRecord::IsHard(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHard;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsVeryHard()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eVeryHard);
    }

void TERMRecord::IsVeryHard(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eVeryHard;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsRequiresKey()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRequiresKey);
    }

void TERMRecord::IsRequiresKey(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eRequiresKey;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsLockType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void TERMRecord::SetLockType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool TERMRecord::IsServer1()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer1);
    }

void TERMRecord::IsServer1(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer1;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer2()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer2);
    }

void TERMRecord::IsServer2(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer2;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer3()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer3);
    }

void TERMRecord::IsServer3(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer3;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer4()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer4);
    }

void TERMRecord::IsServer4(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer4;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer5()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer5);
    }

void TERMRecord::IsServer5(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer5;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer6()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer6);
    }

void TERMRecord::IsServer6(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer6;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer7()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer7);
    }

void TERMRecord::IsServer7(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer7;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer8()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer8);
    }

void TERMRecord::IsServer8(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer8;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer9()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer9);
    }

void TERMRecord::IsServer9(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer9;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServer10()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eServer10);
    }

void TERMRecord::IsServer10(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eServer10;
    else
        Dummy->flags = eDummyDefault;
    }

bool TERMRecord::IsServerType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void TERMRecord::SetServerType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 TERMRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-20];

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

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

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

    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;

    if(DEST.IsLoaded())
        {
        if(DEST->DEST.IsLoaded())
            TotSize += DEST->DEST.GetSize() + 6;
        if(DEST->DSTD.IsLoaded())
            TotSize += DEST->DSTD.GetSize() + 6;
        if(DEST->DMDL.IsLoaded())
            {
            cSize = DEST->DMDL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(DEST->DMDT.IsLoaded())
            {
            cSize = DEST->DMDT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(DEST->DSTF.IsLoaded())
            TotSize += DEST->DSTF.GetSize() + 6;
        }

    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    if(ITXT.IsLoaded())
        {
        if(ITXT->ITXT.IsLoaded())
            {
            cSize = ITXT->ITXT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(ITXT->RNAM.IsLoaded())
            {
            cSize = ITXT->RNAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(ITXT->ANAM.IsLoaded())
            TotSize += ITXT->ANAM.GetSize() + 6;
        }

    if(INAM.IsLoaded())
        TotSize += INAM.GetSize() + 6;

    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;

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

    if(CTDA.IsLoaded())
        TotSize += CTDA.GetSize() + 6;

    return TotSize;
    }

UINT32 TERMRecord::GetType()
    {
    return 'MRET';
    }

STRING TERMRecord::GetStrType()
    {
    return "TERM";
    }

SINT32 TERMRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
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
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'TSED':
                DEST.Load();
                DEST->DEST.Read(buffer, subSize, curPos);
                break;
            case 'DTSD':
                DEST.Load();
                DEST->DSTD.Read(buffer, subSize, curPos);
                break;
            case 'LDMD':
                DEST.Load();
                DEST->DMDL.Read(buffer, subSize, curPos);
                break;
            case 'TDMD':
                DEST.Load();
                DEST->DMDT.Read(buffer, subSize, curPos);
                break;
            case 'FTSD':
                //DEST.Load();
                //DEST->DSTF.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'CSED':
                DESC.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'TXTI':
                ITXT.Load();
                ITXT->ITXT.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                ITXT.Load();
                ITXT->RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ITXT.Load();
                ITXT->ANAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
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
            case 'ADTC':
                CTDA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  TERM: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 TERMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    DEST.Unload();
    DESC.Unload();
    SNAM.Unload();
    PNAM.Unload();
    DNAM.Unload();
    ITXT.Unload();
    INAM.Unload();
    TNAM.Unload();
    SCHR.Unload();
    CTDA.Unload();
    return 1;
    }

SINT32 TERMRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

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

    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord('IRCS', SCRI.value, SCRI.GetSize());

    if(DEST.IsLoaded())
        {
        if(DEST->DEST.IsLoaded())
            SaveHandler.writeSubRecord('TSED', DEST->DEST.value, DEST->DEST.GetSize());

        if(DEST->DSTD.IsLoaded())
            SaveHandler.writeSubRecord('DTSD', DEST->DSTD.value, DEST->DSTD.GetSize());

        if(DEST->DMDL.IsLoaded())
            SaveHandler.writeSubRecord('LDMD', DEST->DMDL.value, DEST->DMDL.GetSize());

        if(DEST->DMDT.IsLoaded())
            SaveHandler.writeSubRecord('TDMD', DEST->DMDT.value, DEST->DMDT.GetSize());

        //if(DEST->DSTF.IsLoaded()) //FILL IN MANUALLY
            //SaveHandler.writeSubRecord('FTSD', DEST->DSTF.value, DEST->DSTF.GetSize());

        }

    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord('CSED', DESC.value, DESC.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', PNAM.value, PNAM.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    if(ITXT.IsLoaded())
        {
        if(ITXT->ITXT.IsLoaded())
            SaveHandler.writeSubRecord('TXTI', ITXT->ITXT.value, ITXT->ITXT.GetSize());

        if(ITXT->RNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANR', ITXT->RNAM.value, ITXT->RNAM.GetSize());

        if(ITXT->ANAM.IsLoaded())
            SaveHandler.writeSubRecord('MANA', ITXT->ANAM.value, ITXT->ANAM.GetSize());

        }

    if(INAM.IsLoaded())
        SaveHandler.writeSubRecord('MANI', INAM.value, INAM.GetSize());

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANT', TNAM.value, TNAM.GetSize());

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

    if(CTDA.IsLoaded())
        SaveHandler.writeSubRecord('ADTC', CTDA.value, CTDA.GetSize());

    return -1;
    }

bool TERMRecord::operator ==(const TERMRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            SCRI == other.SCRI &&
            DEST == other.DEST &&
            DESC.equals(other.DESC) &&
            SNAM == other.SNAM &&
            PNAM == other.PNAM &&
            DNAM == other.DNAM &&
            ITXT == other.ITXT &&
            INAM == other.INAM &&
            TNAM == other.TNAM &&
            SCHR == other.SCHR &&
            CTDA == other.CTDA);
    }

bool TERMRecord::operator !=(const TERMRecord &other) const
    {
    return !(*this == other);
    }
}