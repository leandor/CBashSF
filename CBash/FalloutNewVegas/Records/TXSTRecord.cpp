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
#include "TXSTRecord.h"

namespace FNV
{
TXSTRecord::TXSTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

TXSTRecord::TXSTRecord(TXSTRecord *srcRecord):
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

    TX00 = srcRecord->TX00;
    TX01 = srcRecord->TX01;
    TX02 = srcRecord->TX02;
    TX03 = srcRecord->TX03;
    TX04 = srcRecord->TX04;
    TX05 = srcRecord->TX05;

    DODT = srcRecord->DODT;
    DNAM = srcRecord->DNAM;
    return;
    }

TXSTRecord::~TXSTRecord()
    {
    //
    }

bool TXSTRecord::IsNoSpecularMap()
    {
    if(!DNAM.IsLoaded()) return false;
    return (*DNAM.value & fIsNoSpecularMap) != 0;
    }

void TXSTRecord::IsNoSpecularMap(bool value)
    {
    if(!DNAM.IsLoaded()) return;
    *DNAM.value = value ? (*DNAM.value | fIsNoSpecularMap) : (*DNAM.value & ~fIsNoSpecularMap);
    }

bool TXSTRecord::IsFlagMask(UINT16 Mask, bool Exact)
    {
    if(!DNAM.IsLoaded()) return false;
    return Exact ? ((*DNAM.value & Mask) == Mask) : ((*DNAM.value & Mask) != 0);
    }

void TXSTRecord::SetFlagMask(UINT16 Mask)
    {
    DNAM.Load();
    *DNAM.value = Mask;
    }

bool TXSTRecord::IsObjectParallax()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsParallax) != 0 : false;
    }

void TXSTRecord::IsObjectParallax(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsParallax) : (DODT->flags & ~fIsParallax);
    }

bool TXSTRecord::IsObjectAlphaBlending()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsAlphaBlending) != 0 : false;
    }

void TXSTRecord::IsObjectAlphaBlending(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsAlphaBlending) : (DODT->flags & ~fIsAlphaBlending);
    }

bool TXSTRecord::IsObjectAlphaTesting()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsAlphaTesting) != 0 : false;
    }

void TXSTRecord::IsObjectAlphaTesting(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsAlphaTesting) : (DODT->flags & ~fIsAlphaTesting);
    }

bool TXSTRecord::IsObjectFlagMask(UINT8 Mask, bool Exact)
    {
    if(!DODT.IsLoaded()) return false;
    return Exact ? ((DODT->flags & Mask) == Mask) : ((DODT->flags & Mask) != 0);
    }

void TXSTRecord::SetObjectFlagMask(UINT8 Mask)
    {
    DODT.Load();
    DODT->flags = Mask;
    }

UINT32 TXSTRecord::GetType()
    {
    return REV32(TXST);
    }

STRING TXSTRecord::GetStrType()
    {
    return "TXST";
    }

SINT32 TXSTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(TX00):
                TX00.Read(buffer, subSize, curPos);
                break;
            case REV32(TX01):
                TX01.Read(buffer, subSize, curPos);
                break;
            case REV32(TX02):
                TX02.Read(buffer, subSize, curPos);
                break;
            case REV32(TX03):
                TX03.Read(buffer, subSize, curPos);
                break;
            case REV32(TX04):
                TX04.Read(buffer, subSize, curPos);
                break;
            case REV32(TX05):
                TX05.Read(buffer, subSize, curPos);
                break;
            case REV32(DODT):
                DODT.Read(buffer, subSize, curPos);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  TXST: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 TXSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    TX00.Unload();
    TX01.Unload();
    TX02.Unload();
    TX03.Unload();
    TX04.Unload();
    TX05.Unload();
    DODT.Unload();
    DNAM.Unload();
    return 1;
    }

SINT32 TXSTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(TX00);
    WRITE(TX01);
    WRITE(TX02);
    WRITE(TX03);
    WRITE(TX04);
    WRITE(TX05);
    WRITE(DODT);
    WRITE(DNAM);
    return -1;
    }

bool TXSTRecord::operator ==(const TXSTRecord &other) const
    {
    return (OBND == other.OBND &&
            DODT == other.DODT &&
            DNAM == other.DNAM &&
            EDID.equalsi(other.EDID) &&
            TX00.equalsi(other.TX00) &&
            TX01.equalsi(other.TX01) &&
            TX02.equalsi(other.TX02) &&
            TX03.equalsi(other.TX03) &&
            TX04.equalsi(other.TX04) &&
            TX05.equalsi(other.TX05)
            );
    }

bool TXSTRecord::operator !=(const TXSTRecord &other) const
    {
    return !(*this == other);
    }
}