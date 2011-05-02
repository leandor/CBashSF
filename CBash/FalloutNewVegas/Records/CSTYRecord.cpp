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
#include "CSTYRecord.h"

namespace FNV
{
CSTYRecord::CSTYRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CSTYRecord::CSTYRecord(CSTYRecord *srcRecord):
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
    CSTD = srcRecord->CSTD;
    CSAD = srcRecord->CSAD;
    CSSD = srcRecord->CSSD;
    return;
    }

CSTYRecord::~CSTYRecord()
    {
    //
    }

bool CSTYRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;


    return op.Stop();
    }

bool CSTYRecord::IsUseChanceForAttack()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUseChanceForAttack) != 0;
    }

void CSTYRecord::IsUseChanceForAttack(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsUseChanceForAttack) : (Dummy->flags & ~fIsUseChanceForAttack);
    }

bool CSTYRecord::IsMeleeAlertOK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsMeleeAlertOK) != 0;
    }

void CSTYRecord::IsMeleeAlertOK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsMeleeAlertOK) : (Dummy->flags & ~fIsMeleeAlertOK);
    }

bool CSTYRecord::IsFleeForSurvival()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFleeForSurvival) != 0;
    }

void CSTYRecord::IsFleeForSurvival(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsFleeForSurvival) : (Dummy->flags & ~fIsFleeForSurvival);
    }

bool CSTYRecord::IsIgnoreThreats()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIgnoreThreats) != 0;
    }

void CSTYRecord::IsIgnoreThreats(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIgnoreThreats) : (Dummy->flags & ~fIsIgnoreThreats);
    }

bool CSTYRecord::IsIgnoreDamagingSelf=()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIgnoreDamagingSelf=) != 0;
    }

void CSTYRecord::IsIgnoreDamagingSelf=(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIgnoreDamagingSelf=) : (Dummy->flags & ~fIsIgnoreDamagingSelf=);
    }

bool CSTYRecord::IsIgnoreDamagingGroup=()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIgnoreDamagingGroup=) != 0;
    }

void CSTYRecord::IsIgnoreDamagingGroup=(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIgnoreDamagingGroup=) : (Dummy->flags & ~fIsIgnoreDamagingGroup=);
    }

bool CSTYRecord::IsIgnoreDamagingSpectator()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsIgnoreDamagingSpectator) != 0;
    }

void CSTYRecord::IsIgnoreDamagingSpectator(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsIgnoreDamagingSpectator) : (Dummy->flags & ~fIsIgnoreDamagingSpectator);
    }

bool CSTYRecord::IsNoUseStealthboy()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoUseStealthboy) != 0;
    }

void CSTYRecord::IsNoUseStealthboy(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoUseStealthboy) : (Dummy->flags & ~fIsNoUseStealthboy);
    }

bool CSTYRecord::IsFlagMask(UINT16 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CSTYRecord::SetFlagMask(UINT16 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CSTYRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void CSTYRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool CSTYRecord::IsMeleeOnly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMeleeOnly);
    }

void CSTYRecord::IsMeleeOnly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMeleeOnly : eDummyDefault;
    }

bool CSTYRecord::IsRangedOnly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRangedOnly);
    }

void CSTYRecord::IsRangedOnly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRangedOnly : eDummyDefault;
    }

bool CSTYRecord::IsType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void CSTYRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CSTYRecord::GetType()
    {
    return 'YTSC';
    }

STRING CSTYRecord::GetStrType()
    {
    return "CSTY";
    }

SINT32 CSTYRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'DTSC':
                CSTD.Read(buffer, subSize, curPos);
                break;
            case 'DASC':
                CSAD.Read(buffer, subSize, curPos);
                break;
            case 'DSSC':
                CSSD.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CSTY: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CSTYRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    CSTD.Unload();
    CSAD.Unload();
    CSSD.Unload();
    return 1;
    }

SINT32 CSTYRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    WRITE(EDID);
    WRITE(CSTD);
    WRITE(CSAD);
    WRITE(CSSD);

    return -1;
    }

bool CSTYRecord::operator ==(const CSTYRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            CSTD == other.CSTD &&
            CSAD == other.CSAD &&
            CSSD == other.CSSD);
    }

bool CSTYRecord::operator !=(const CSTYRecord &other) const
    {
    return !(*this == other);
    }
}