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

    for(UINT32 x = 0; x < IDLA.value.size(); x++)
        op.Accept(IDLA.value[x]);

    return op.Stop();
    }

bool IDLMRecord::IsRunInSequence()
    {
    return (IDLF.value & fIsRunInSequence) != 0;
    }

void IDLMRecord::IsRunInSequence(bool value)
    {
    IDLF.value = value ? (IDLF.value | fIsRunInSequence) : (IDLF.value & ~fIsRunInSequence);
    }

bool IDLMRecord::IsDoOnce()
    {
    return (IDLF.value & fIsDoOnce) != 0;
    }

void IDLMRecord::IsDoOnce(bool value)
    {
    IDLF.value = value ? (IDLF.value | fIsDoOnce) : (IDLF.value & ~fIsDoOnce);
    }

bool IDLMRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((IDLF.value & Mask) == Mask) : ((IDLF.value & Mask) != 0);
    }

void IDLMRecord::SetFlagMask(UINT8 Mask)
    {
    IDLF.value = Mask;
    }

UINT32 IDLMRecord::GetType()
    {
    return REV32(IDLM);
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
            case REV32(OBND):
                OBND.Read(buffer, subSize, curPos);
                break;
            case REV32(IDLF):
                IDLF.Read(buffer, subSize, curPos);
                break;
            case REV32(IDLC):
                //may be a UINT32 instead, but only the lower 8 bits are used, so skip extra
                //IDLC.Read(buffer, 1, curPos);
                //curPos += subSize - 1;
                //Testing snippet. Verified that the extra bits aren't in use in FalloutNV.esm
                switch(subSize)
                    {
                    case 1:
                        IDLC.Read(buffer, subSize, curPos);
                        break;
                    case 4:
                        {
                        IDLC.Read(buffer, 1, curPos);
                        UINT32 test = 0;
                        _readBuffer(&test, buffer, 3, curPos);
                        if(test != 0)
                            {
                            printf("  IDLM: %08X - Unexpected IDLC value. Expected (0) and got (%u). IDLC = %u.\n", formID, test, IDLC.value);
                            CBASH_CHUNK_DEBUG
                            printf("  Size = %i\n", subSize);
                            printf("  CurPos = %04x\n\n", curPos - 6);
                            }
                        }
                        break;
                    default:
                        printf("  IDLM: %08X - Unexpected IDLC chunk size. Expected (1 or 4) and got (%u)\n", formID, subSize);
                        CBASH_CHUNK_DEBUG
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case REV32(IDLT):
                IDLT.Read(buffer, subSize, curPos);
                break;
            case REV32(IDLA):
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

SINT32 IDLMRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(IDLF);
    WRITE(IDLC);
    WRITE(IDLT);
    WRITE(IDLA);
    return -1;
    }

bool IDLMRecord::operator ==(const IDLMRecord &other) const
    {
    return (OBND == other.OBND &&
            IDLF == other.IDLF &&
            IDLC == other.IDLC &&
            IDLT == other.IDLT &&
            EDID.equalsi(other.EDID) &&
            IDLA == other.IDLA);
    }

bool IDLMRecord::operator !=(const IDLMRecord &other) const
    {
    return !(*this == other);
    }
}