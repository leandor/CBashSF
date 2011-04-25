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
#include "CELLRecord.h"

namespace FNV
{
bool CELLRecord::CELLLTMP::IsAmbientInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsAmbientInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsAmbientInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsAmbientInherited;
    else
        Dummy->flags &= ~fIsAmbientInherited;
    }

bool CELLRecord::CELLLTMP::IsDirectionalColorInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDirectionalColorInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsDirectionalColorInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDirectionalColorInherited;
    else
        Dummy->flags &= ~fIsDirectionalColorInherited;
    }

bool CELLRecord::CELLLTMP::IsFogColorInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFogColorInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsFogColorInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsFogColorInherited;
    else
        Dummy->flags &= ~fIsFogColorInherited;
    }

bool CELLRecord::CELLLTMP::IsFogNearInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFogNearInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsFogNearInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsFogNearInherited;
    else
        Dummy->flags &= ~fIsFogNearInherited;
    }

bool CELLRecord::CELLLTMP::IsFogFarInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFogFarInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsFogFarInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsFogFarInherited;
    else
        Dummy->flags &= ~fIsFogFarInherited;
    }

bool CELLRecord::CELLLTMP::IsDirectionalRotationInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDirectionalRotationInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsDirectionalRotationInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDirectionalRotationInherited;
    else
        Dummy->flags &= ~fIsDirectionalRotationInherited;
    }

bool CELLRecord::CELLLTMP::IsDirectionalFadeInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDirectionalFadeInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsDirectionalFadeInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsDirectionalFadeInherited;
    else
        Dummy->flags &= ~fIsDirectionalFadeInherited;
    }

bool CELLRecord::CELLLTMP::IsFogClipInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFogClipInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsFogClipInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsFogClipInherited;
    else
        Dummy->flags &= ~fIsFogClipInherited;
    }

bool CELLRecord::CELLLTMP::IsFogPowerInherited()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFogPowerInherited) != 0;
    }

void CELLRecord::CELLLTMP::IsFogPowerInherited(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsFogPowerInherited;
    else
        Dummy->flags &= ~fIsFogPowerInherited;
    }

bool CELLRecord::CELLLTMP::Is0FlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CELLRecord::CELLLTMP::Set0FlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

CELLRecord::CELLRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CELLRecord::CELLRecord(CELLRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    XCLC = srcRecord->XCLC;
    XCLL = srcRecord->XCLL;
    IMPF = srcRecord->IMPF;
    if(srcRecord->LTMP.IsLoaded())
        {
        LTMP.Load();
        LTMP->LTMP = srcRecord->LTMP->LTMP;
        LTMP->LNAM = srcRecord->LTMP->LNAM;
        }
    XCLW = srcRecord->XCLW;
    XNAM = srcRecord->XNAM;
    XCLR = srcRecord->XCLR;
    XCIM = srcRecord->XCIM;
    XCET = srcRecord->XCET;
    XEZN = srcRecord->XEZN;
    XCCM = srcRecord->XCCM;
    XCWT = srcRecord->XCWT;
    if(srcRecord->XOWN.IsLoaded())
        {
        XOWN.Load();
        XOWN->XOWN = srcRecord->XOWN->XOWN;
        XOWN->XRNK = srcRecord->XOWN->XRNK;
        }
    XCAS = srcRecord->XCAS;
    XCMT = srcRecord->XCMT;
    XCMO = srcRecord->XCMO;
    return;
    }

CELLRecord::~CELLRecord()
    {
    //
    }

bool CELLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(LTMP.IsLoaded() && LTMP->LTMP.IsLoaded())
        op.Accept(LTMP->LTMP->value);
    //if(XCLR.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XCLR->value);
    if(XCIM.IsLoaded())
        op.Accept(XCIM->value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN->value);
    if(XCCM.IsLoaded())
        op.Accept(XCCM->value);
    if(XCWT.IsLoaded())
        op.Accept(XCWT->value);
    if(XOWN.IsLoaded() && XOWN->XOWN.IsLoaded())
        op.Accept(XOWN->XOWN->value);
    if(XCAS.IsLoaded())
        op.Accept(XCAS->value);
    if(XCMO.IsLoaded())
        op.Accept(XCMO->value);

    return op.Stop();
    }

bool CELLRecord::IsInterior()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsInterior) != 0;
    }

void CELLRecord::IsInterior(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsInterior;
    else
        Dummy->flags &= ~fIsInterior;
    }

bool CELLRecord::HasWater()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fHasWater) != 0;
    }

void CELLRecord::HasWater(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fHasWater;
    else
        Dummy->flags &= ~fHasWater;
    }

bool CELLRecord::InvertFastTravel()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fInvertFastTravel) != 0;
    }

void CELLRecord::InvertFastTravel(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fInvertFastTravel;
    else
        Dummy->flags &= ~fInvertFastTravel;
    }

bool CELLRecord::ForceHideLand()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fForceHideLand) != 0;
    }

void CELLRecord::ForceHideLand(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fForceHideLand;
    else
        Dummy->flags &= ~fForceHideLand;
    }

bool CELLRecord::IsOblivionInterior()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsOblivionInterior) != 0;
    }

void CELLRecord::IsOblivionInterior(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsOblivionInterior;
    else
        Dummy->flags &= ~fIsOblivionInterior;
    }

bool CELLRecord::PublicPlace()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fPublicPlace) != 0;
    }

void CELLRecord::PublicPlace(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fPublicPlace;
    else
        Dummy->flags &= ~fPublicPlace;
    }

bool CELLRecord::HandChanged()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fHandChanged) != 0;
    }

void CELLRecord::HandChanged(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fHandChanged;
    else
        Dummy->flags &= ~fHandChanged;
    }

bool CELLRecord::BehaveLikeExterior()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fBehaveLikeExterior) != 0;
    }

void CELLRecord::BehaveLikeExterior(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fBehaveLikeExterior;
    else
        Dummy->flags &= ~fBehaveLikeExterior;
    }

bool CELLRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CELLRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CELLRecord::IsQuad1ForceHidden()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsQuad1ForceHidden) != 0;
    }

void CELLRecord::IsQuad1ForceHidden(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsQuad1ForceHidden;
    else
        Dummy->flags &= ~fIsQuad1ForceHidden;
    }

bool CELLRecord::IsQuad2ForceHidden()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsQuad2ForceHidden) != 0;
    }

void CELLRecord::IsQuad2ForceHidden(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsQuad2ForceHidden;
    else
        Dummy->flags &= ~fIsQuad2ForceHidden;
    }

bool CELLRecord::IsQuad3ForceHidden()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsQuad3ForceHidden) != 0;
    }

void CELLRecord::IsQuad3ForceHidden(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsQuad3ForceHidden;
    else
        Dummy->flags &= ~fIsQuad3ForceHidden;
    }

bool CELLRecord::IsQuad4ForceHidden()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsQuad4ForceHidden) != 0;
    }

void CELLRecord::IsQuad4ForceHidden(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsQuad4ForceHidden;
    else
        Dummy->flags &= ~fIsQuad4ForceHidden;
    }

bool CELLRecord::IsHiddenFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CELLRecord::SetHiddenFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CELLRecord::GetSize(bool forceCalc)
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

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(XCLC.IsLoaded())
        TotSize += XCLC.GetSize() + 6;

    if(XCLL.IsLoaded())
        TotSize += XCLL.GetSize() + 6;

    if(IMPF.IsLoaded())
        TotSize += IMPF.GetSize() + 6;

    if(LTMP.IsLoaded())
        {
        if(LTMP->LTMP.IsLoaded())
            TotSize += LTMP->LTMP.GetSize() + 6;
        if(LTMP->LNAM.IsLoaded())
            TotSize += LTMP->LNAM.GetSize() + 6;
        }

    if(XCLW.IsLoaded())
        TotSize += XCLW.GetSize() + 6;

    if(XNAM.IsLoaded())
        {
        cSize = XNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XCLR.IsLoaded())
        TotSize += XCLR.GetSize() + 6;

    if(XCIM.IsLoaded())
        TotSize += XCIM.GetSize() + 6;

    if(XCET.IsLoaded())
        TotSize += XCET.GetSize() + 6;

    if(XEZN.IsLoaded())
        TotSize += XEZN.GetSize() + 6;

    if(XCCM.IsLoaded())
        TotSize += XCCM.GetSize() + 6;

    if(XCWT.IsLoaded())
        TotSize += XCWT.GetSize() + 6;

    if(XOWN.IsLoaded())
        {
        if(XOWN->XOWN.IsLoaded())
            TotSize += XOWN->XOWN.GetSize() + 6;
        if(XOWN->XRNK.IsLoaded())
            TotSize += XOWN->XRNK.GetSize() + 6;
        }

    if(XCAS.IsLoaded())
        TotSize += XCAS.GetSize() + 6;

    if(XCMT.IsLoaded())
        TotSize += XCMT.GetSize() + 6;

    if(XCMO.IsLoaded())
        TotSize += XCMO.GetSize() + 6;

    return TotSize;
    }

UINT32 CELLRecord::GetType()
    {
    return 'LLEC';
    }

STRING CELLRecord::GetStrType()
    {
    return "CELL";
    }

SINT32 CELLRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'CLCX':
                XCLC.Read(buffer, subSize, curPos);
                break;
            case 'LLCX':
                XCLL.Read(buffer, subSize, curPos);
                break;
            case 'FPMI':
                IMPF.Read(buffer, subSize, curPos);
                break;
            case 'PMTL':
                LTMP.Load();
                LTMP->LTMP.Read(buffer, subSize, curPos);
                break;
            case 'MANL':
                LTMP.Load();
                LTMP->LNAM.Read(buffer, subSize, curPos);
                break;
            case 'WLCX':
                XCLW.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'RLCX':
                XCLR.Read(buffer, subSize, curPos);
                break;
            case 'MICX':
                XCIM.Read(buffer, subSize, curPos);
                break;
            case 'TECX':
                XCET.Read(buffer, subSize, curPos);
                break;
            case 'NZEX':
                XEZN.Read(buffer, subSize, curPos);
                break;
            case 'MCCX':
                XCCM.Read(buffer, subSize, curPos);
                break;
            case 'TWCX':
                XCWT.Read(buffer, subSize, curPos);
                break;
            case 'NWOX':
                XOWN.Load();
                XOWN->XOWN.Read(buffer, subSize, curPos);
                break;
            case 'KNRX':
                XOWN.Load();
                XOWN->XRNK.Read(buffer, subSize, curPos);
                break;
            case 'SACX':
                XCAS.Read(buffer, subSize, curPos);
                break;
            case 'TMCX':
                XCMT.Read(buffer, subSize, curPos);
                break;
            case 'OMCX':
                XCMO.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CELL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CELLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    XCLC.Unload();
    XCLL.Unload();
    IMPF.Unload();
    LTMP.Unload();
    XCLW.Unload();
    XNAM.Unload();
    XCLR.Unload();
    XCIM.Unload();
    XCET.Unload();
    XEZN.Unload();
    XCCM.Unload();
    XCWT.Unload();
    XOWN.Unload();
    XCAS.Unload();
    XCMT.Unload();
    XCMO.Unload();
    return 1;
    }

SINT32 CELLRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(XCLC.IsLoaded())
        SaveHandler.writeSubRecord('CLCX', XCLC.value, XCLC.GetSize());

    if(XCLL.IsLoaded())
        SaveHandler.writeSubRecord('LLCX', XCLL.value, XCLL.GetSize());

    if(IMPF.IsLoaded())
        SaveHandler.writeSubRecord('FPMI', IMPF.value, IMPF.GetSize());

    if(LTMP.IsLoaded())
        {
        if(LTMP->LTMP.IsLoaded())
            SaveHandler.writeSubRecord('PMTL', LTMP->LTMP.value, LTMP->LTMP.GetSize());

        if(LTMP->LNAM.IsLoaded())
            SaveHandler.writeSubRecord('MANL', LTMP->LNAM.value, LTMP->LNAM.GetSize());

        }

    if(XCLW.IsLoaded())
        SaveHandler.writeSubRecord('WLCX', XCLW.value, XCLW.GetSize());

    if(XNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANX', XNAM.value, XNAM.GetSize());

    if(XCLR.IsLoaded())
        SaveHandler.writeSubRecord('RLCX', XCLR.value, XCLR.GetSize());

    if(XCIM.IsLoaded())
        SaveHandler.writeSubRecord('MICX', XCIM.value, XCIM.GetSize());

    if(XCET.IsLoaded())
        SaveHandler.writeSubRecord('TECX', XCET.value, XCET.GetSize());

    if(XEZN.IsLoaded())
        SaveHandler.writeSubRecord('NZEX', XEZN.value, XEZN.GetSize());

    if(XCCM.IsLoaded())
        SaveHandler.writeSubRecord('MCCX', XCCM.value, XCCM.GetSize());

    if(XCWT.IsLoaded())
        SaveHandler.writeSubRecord('TWCX', XCWT.value, XCWT.GetSize());

    if(XOWN.IsLoaded())
        {
        if(XOWN->XOWN.IsLoaded())
            SaveHandler.writeSubRecord('NWOX', XOWN->XOWN.value, XOWN->XOWN.GetSize());

        if(XOWN->XRNK.IsLoaded())
            SaveHandler.writeSubRecord('KNRX', XOWN->XRNK.value, XOWN->XRNK.GetSize());

        }

    if(XCAS.IsLoaded())
        SaveHandler.writeSubRecord('SACX', XCAS.value, XCAS.GetSize());

    if(XCMT.IsLoaded())
        SaveHandler.writeSubRecord('TMCX', XCMT.value, XCMT.GetSize());

    if(XCMO.IsLoaded())
        SaveHandler.writeSubRecord('OMCX', XCMO.value, XCMO.GetSize());

    return -1;
    }

bool CELLRecord::operator ==(const CELLRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA &&
            XCLC == other.XCLC &&
            XCLL == other.XCLL &&
            IMPF == other.IMPF &&
            LTMP == other.LTMP &&
            XCLW == other.XCLW &&
            XNAM.equalsi(other.XNAM) &&
            XCLR == other.XCLR &&
            XCIM == other.XCIM &&
            XCET == other.XCET &&
            XEZN == other.XEZN &&
            XCCM == other.XCCM &&
            XCWT == other.XCWT &&
            XOWN == other.XOWN &&
            XCAS == other.XCAS &&
            XCMT == other.XCMT &&
            XCMO == other.XCMO);
    }

bool CELLRecord::operator !=(const CELLRecord &other) const
    {
    return !(*this == other);
    }
}