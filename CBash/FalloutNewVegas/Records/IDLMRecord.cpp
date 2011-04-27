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
#include "IDLMRecord.h"

namespace FNV
{
IDLMRecord::IDLMRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IDLMRecord::IDLMRecord(IDLMRecord *srcRecord):
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
    IDLF = srcRecord->IDLF;
    IDLC = srcRecord->IDLC;
    IDLT = srcRecord->IDLT;
    IDLA = srcRecord->IDLA;
    return;
    }

IDLMRecord::~IDLMRecord()
    {
    //
    }

bool IDLMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(IDLA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(IDLA->value);

    return op.Stop();
    }

bool IDLMRecord::IsRunInSequence()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRunInSequence) != 0;
    }

void IDLMRecord::IsRunInSequence(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRunInSequence) : (Dummy->flags & ~fIsRunInSequence);
    }

bool IDLMRecord::IsDoOnce()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDoOnce) != 0;
    }

void IDLMRecord::IsDoOnce(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDoOnce) : (Dummy->flags & ~fIsDoOnce);
    }

bool IDLMRecord::Is0FlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void IDLMRecord::Set0FlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 IDLMRecord::GetSize(bool forceCalc)
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

    if(IDLF.IsLoaded())
        TotSize += IDLF.GetSize() + 6;

    if(IDLC.IsLoaded())
        TotSize += IDLC.GetSize() + 6;

    if(IDLT.IsLoaded())
        TotSize += IDLT.GetSize() + 6;

    if(IDLA.IsLoaded())
        TotSize += IDLA.GetSize() + 6;

    return TotSize;
    }

UINT32 IDLMRecord::GetType()
    {
    return 'MLDI';
    }

STRING IDLMRecord::GetStrType()
    {
    return "IDLM";
    }

SINT32 IDLMRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'FLDI':
                IDLF.Read(buffer, subSize, curPos);
                break;
            case 'CLDI':
                IDLC.Read(buffer, subSize, curPos);
                break;
            case 'TLDI':
                IDLT.Read(buffer, subSize, curPos);
                break;
            case 'ALDI':
                IDLA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IDLM: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 IDLMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    IDLF.Unload();
    IDLC.Unload();
    IDLT.Unload();
    IDLA.Unload();
    return 1;
    }

SINT32 IDLMRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(IDLF.IsLoaded())
        SaveHandler.writeSubRecord('FLDI', IDLF.value, IDLF.GetSize());

    if(IDLC.IsLoaded())
        SaveHandler.writeSubRecord('CLDI', IDLC.value, IDLC.GetSize());

    if(IDLT.IsLoaded())
        SaveHandler.writeSubRecord('TLDI', IDLT.value, IDLT.GetSize());

    if(IDLA.IsLoaded())
        SaveHandler.writeSubRecord('ALDI', IDLA.value, IDLA.GetSize());

    return -1;
    }

bool IDLMRecord::operator ==(const IDLMRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            IDLF == other.IDLF &&
            IDLC == other.IDLC &&
            IDLT == other.IDLT &&
            IDLA == other.IDLA);
    }

bool IDLMRecord::operator !=(const IDLMRecord &other) const
    {
    return !(*this == other);
    }
}