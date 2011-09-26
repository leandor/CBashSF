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
#include "RGDLRecord.h"

namespace FNV
{
RGDLRecord::RGDLRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

RGDLRecord::RGDLRecord(RGDLRecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    NVER = srcRecord->NVER;
    DATA = srcRecord->DATA;
    XNAM = srcRecord->XNAM;
    TNAM = srcRecord->TNAM;
    RAFD = srcRecord->RAFD;
    RAFB = srcRecord->RAFB;
    RAPS = srcRecord->RAPS;
    ANAM = srcRecord->ANAM;
    return;
    }

RGDLRecord::~RGDLRecord()
    {
    //
    }

bool RGDLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(XNAM.IsLoaded())
        op.Accept(XNAM->value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM->value);

    return op.Stop();
    }

bool RGDLRecord::IsDisableOnMove()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDisableOnMove) != 0;
    }

void RGDLRecord::IsDisableOnMove(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDisableOnMove) : (Dummy->flags & ~fIsDisableOnMove);
    }

bool RGDLRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void RGDLRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoFeedback()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoFeedback);
    }

void RGDLRecord::IsNoFeedback(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoFeedback : eDummyDefault;
    }

bool RGDLRecord::IsFeedback()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFeedback);
    }

void RGDLRecord::IsFeedback(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFeedback : eDummyDefault;
    }

bool RGDLRecord::IsFeedbackType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetFeedbackType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoFootIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoFootIK);
    }

void RGDLRecord::IsNoFootIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoFootIK : eDummyDefault;
    }

bool RGDLRecord::IsFootIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFootIK);
    }

void RGDLRecord::IsFootIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFootIK : eDummyDefault;
    }

bool RGDLRecord::IsFootType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetFootType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoLookIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoLookIK);
    }

void RGDLRecord::IsNoLookIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoLookIK : eDummyDefault;
    }

bool RGDLRecord::IsLookIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLookIK);
    }

void RGDLRecord::IsLookIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLookIK : eDummyDefault;
    }

bool RGDLRecord::IsLookType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetLookType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoGrabIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoGrabIK);
    }

void RGDLRecord::IsNoGrabIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoGrabIK : eDummyDefault;
    }

bool RGDLRecord::IsGrabIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGrabIK);
    }

void RGDLRecord::IsGrabIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGrabIK : eDummyDefault;
    }

bool RGDLRecord::IsGrabType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetGrabType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoMatchPose()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoMatchPose);
    }

void RGDLRecord::IsNoMatchPose(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoMatchPose : eDummyDefault;
    }

bool RGDLRecord::IsMatchPose()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMatchPose);
    }

void RGDLRecord::IsMatchPose(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMatchPose : eDummyDefault;
    }

bool RGDLRecord::IsMatchType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetMatchType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 RGDLRecord::GetType()
    {
    return REV32(RGDL);
    }

STRING RGDLRecord::GetStrType()
    {
    return "RGDL";
    }

SINT32 RGDLRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                EDID.Read(buffer, subSize);
                break;
            case REV32(NVER):
                NVER.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            case REV32(RAFD):
                RAFD.Read(buffer, subSize);
                break;
            case REV32(RAFB):
                RAFB.Read(buffer, subSize);
                break;
            case REV32(RAPS):
                RAPS.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  RGDL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 RGDLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NVER.Unload();
    DATA.Unload();
    XNAM.Unload();
    TNAM.Unload();
    RAFD.Unload();
    RAFB.Unload();
    RAPS.Unload();
    ANAM.Unload();
    return 1;
    }

SINT32 RGDLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NVER);
    WRITE(DATA);
    WRITE(XNAM);
    WRITE(TNAM);
    WRITE(RAFD);
    WRITE(RAFB);
    WRITE(RAPS);
    WRITE(ANAM);

    return -1;
    }

bool RGDLRecord::operator ==(const RGDLRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            DATA == other.DATA &&
            XNAM == other.XNAM &&
            TNAM == other.TNAM &&
            RAFD == other.RAFD &&
            RAFB == other.RAFB &&
            RAPS == other.RAPS &&
            ANAM.equalsi(other.ANAM));
    }

bool RGDLRecord::operator !=(const RGDLRecord &other) const
    {
    return !(*this == other);
    }

bool RGDLRecord::equals(const Record *other) const
    {
    return *this == *(RGDLRecord *)other;
    }
}