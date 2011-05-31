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
#include "FURNRecord.h"

FURNRecord::FURNRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

FURNRecord::FURNRecord(FURNRecord *srcRecord):
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
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODT = srcRecord->MODL->MODT;
        }
    SCRI = srcRecord->SCRI;
    MNAM = srcRecord->MNAM;
    return;
    }

FURNRecord::~FURNRecord()
    {
    //
    }

bool FURNRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);

    return op.Stop();
    }

bool FURNRecord::IsAnim01()
    {
    return (MNAM.value & fIsAnim01) != 0;
    }

void FURNRecord::IsAnim01(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim01) : (MNAM.value & ~fIsAnim01);
    }

bool FURNRecord::IsAnim02()
    {
    return (MNAM.value & fIsAnim02) != 0;
    }

void FURNRecord::IsAnim02(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim02) : (MNAM.value & ~fIsAnim02);
    }

bool FURNRecord::IsAnim03()
    {
    return (MNAM.value & fIsAnim03) != 0;
    }

void FURNRecord::IsAnim03(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim03) : (MNAM.value & ~fIsAnim03);
    }

bool FURNRecord::IsAnim04()
    {
    return (MNAM.value & fIsAnim04) != 0;
    }

void FURNRecord::IsAnim04(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim04) : (MNAM.value & ~fIsAnim04);
    }

bool FURNRecord::IsAnim05()
    {
    return (MNAM.value & fIsAnim05) != 0;
    }

void FURNRecord::IsAnim05(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim05) : (MNAM.value & ~fIsAnim05);
    }

bool FURNRecord::IsAnim06()
    {
    return (MNAM.value & fIsAnim06) != 0;
    }

void FURNRecord::IsAnim06(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim06) : (MNAM.value & ~fIsAnim06);
    }

bool FURNRecord::IsAnim07()
    {
    return (MNAM.value & fIsAnim07) != 0;
    }

void FURNRecord::IsAnim07(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim07) : (MNAM.value & ~fIsAnim07);
    }

bool FURNRecord::IsAnim08()
    {
    return (MNAM.value & fIsAnim08) != 0;
    }

void FURNRecord::IsAnim08(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim08) : (MNAM.value & ~fIsAnim08);
    }

bool FURNRecord::IsAnim09()
    {
    return (MNAM.value & fIsAnim09) != 0;
    }

void FURNRecord::IsAnim09(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim09) : (MNAM.value & ~fIsAnim09);
    }

bool FURNRecord::IsAnim10()
    {
    return (MNAM.value & fIsAnim10) != 0;
    }

void FURNRecord::IsAnim10(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim10) : (MNAM.value & ~fIsAnim10);
    }

bool FURNRecord::IsAnim11()
    {
    return (MNAM.value & fIsAnim11) != 0;
    }

void FURNRecord::IsAnim11(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim11) : (MNAM.value & ~fIsAnim11);
    }

bool FURNRecord::IsAnim12()
    {
    return (MNAM.value & fIsAnim12) != 0;
    }

void FURNRecord::IsAnim12(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim12) : (MNAM.value & ~fIsAnim12);
    }

bool FURNRecord::IsAnim13()
    {
    return (MNAM.value & fIsAnim13) != 0;
    }

void FURNRecord::IsAnim13(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim13) : (MNAM.value & ~fIsAnim13);
    }

bool FURNRecord::IsAnim14()
    {
    return (MNAM.value & fIsAnim14) != 0;
    }

void FURNRecord::IsAnim14(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim14) : (MNAM.value & ~fIsAnim14);
    }

bool FURNRecord::IsAnim15()
    {
    return (MNAM.value & fIsAnim15) != 0;
    }

void FURNRecord::IsAnim15(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim15) : (MNAM.value & ~fIsAnim15);
    }

bool FURNRecord::IsAnim16()
    {
    return (MNAM.value & fIsAnim16) != 0;
    }

void FURNRecord::IsAnim16(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim16) : (MNAM.value & ~fIsAnim16);
    }

bool FURNRecord::IsAnim17()
    {
    return (MNAM.value & fIsAnim17) != 0;
    }

void FURNRecord::IsAnim17(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim17) : (MNAM.value & ~fIsAnim17);
    }

bool FURNRecord::IsAnim18()
    {
    return (MNAM.value & fIsAnim18) != 0;
    }

void FURNRecord::IsAnim18(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim18) : (MNAM.value & ~fIsAnim18);
    }

bool FURNRecord::IsAnim19()
    {
    return (MNAM.value & fIsAnim19) != 0;
    }

void FURNRecord::IsAnim19(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim19) : (MNAM.value & ~fIsAnim19);
    }

bool FURNRecord::IsAnim20()
    {
    return (MNAM.value & fIsAnim20) != 0;
    }

void FURNRecord::IsAnim20(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim20) : (MNAM.value & ~fIsAnim20);
    }

bool FURNRecord::IsAnim21()
    {
    return (MNAM.value & fIsAnim21) != 0;
    }

void FURNRecord::IsAnim21(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim21) : (MNAM.value & ~fIsAnim21);
    }

bool FURNRecord::IsAnim22()
    {
    return (MNAM.value & fIsAnim22) != 0;
    }

void FURNRecord::IsAnim22(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim22) : (MNAM.value & ~fIsAnim22);
    }

bool FURNRecord::IsAnim23()
    {
    return (MNAM.value & fIsAnim23) != 0;
    }

void FURNRecord::IsAnim23(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim23) : (MNAM.value & ~fIsAnim23);
    }

bool FURNRecord::IsAnim24()
    {
    return (MNAM.value & fIsAnim24) != 0;
    }

void FURNRecord::IsAnim24(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim24) : (MNAM.value & ~fIsAnim24);
    }

bool FURNRecord::IsAnim25()
    {
    return (MNAM.value & fIsAnim25) != 0;
    }

void FURNRecord::IsAnim25(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim25) : (MNAM.value & ~fIsAnim25);
    }

bool FURNRecord::IsAnim26()
    {
    return (MNAM.value & fIsAnim26) != 0;
    }

void FURNRecord::IsAnim26(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim26) : (MNAM.value & ~fIsAnim26);
    }

bool FURNRecord::IsAnim27()
    {
    return (MNAM.value & fIsAnim27) != 0;
    }

void FURNRecord::IsAnim27(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim27) : (MNAM.value & ~fIsAnim27);
    }

bool FURNRecord::IsAnim28()
    {
    return (MNAM.value & fIsAnim28) != 0;
    }

void FURNRecord::IsAnim28(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim28) : (MNAM.value & ~fIsAnim28);
    }

bool FURNRecord::IsAnim29()
    {
    return (MNAM.value & fIsAnim29) != 0;
    }

void FURNRecord::IsAnim29(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim29) : (MNAM.value & ~fIsAnim29);
    }

bool FURNRecord::IsAnim30()
    {
    return (MNAM.value & fIsAnim30) != 0;
    }

void FURNRecord::IsAnim30(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim30) : (MNAM.value & ~fIsAnim30);
    }

bool FURNRecord::IsSitAnim()
    {
    return (MNAM.value & fIsSitAnim) != 0;
    }

void FURNRecord::IsSitAnim(bool value)
    {
    if(value)
        {
        MNAM.value &= ~fIsSleepAnim;
        MNAM.value |= fIsSitAnim;
        }
    else
        {
        MNAM.value &= ~fIsSitAnim;
        MNAM.value |= fIsSleepAnim;
        }
    }

bool FURNRecord::IsSleepAnim()
    {
    return (MNAM.value & fIsSleepAnim) != 0;
    }

void FURNRecord::IsSleepAnim(bool value)
    {
    if(value)
        {
        MNAM.value &= ~fIsSitAnim;
        MNAM.value |= fIsSleepAnim;
        }
    else
        {
        MNAM.value &= ~fIsSleepAnim;
        MNAM.value |= fIsSitAnim;
        }
    }

bool FURNRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((MNAM.value & Mask) == Mask) : ((MNAM.value & Mask) != 0);
    }

void FURNRecord::SetFlagMask(UINT32 Mask)
    {
    MNAM.value = Mask;
    }

UINT32 FURNRecord::GetType()
    {
    return REV32(FURN);
    }

STRING FURNRecord::GetStrType()
    {
    return "FURN";
    }

SINT32 FURNRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize, curPos);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  FURN: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 FURNRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    MNAM.Unload();
    return 1;
    }

SINT32 FURNRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        writer.record_write_subrecord(REV32(FULL), FULL.value, FULL.GetSize());
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        writer.record_write_subrecord(REV32(MODL), MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            writer.record_write_subrecord(REV32(MODB), &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            writer.record_write_subrecord(REV32(MODT), MODL->MODT.value, MODL->MODT.GetSize());
        }
    if(SCRI.IsLoaded())
        writer.record_write_subrecord(REV32(SCRI), &SCRI.value, SCRI.GetSize());
    if(MNAM.IsLoaded())
        writer.record_write_subrecord(REV32(MNAM), &MNAM.value, MNAM.GetSize());
    return -1;
    }

bool FURNRecord::operator ==(const FURNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            SCRI == other.SCRI &&
            MNAM == other.MNAM);
    }

bool FURNRecord::operator !=(const FURNRecord &other) const
    {
    return !(*this == other);
    }