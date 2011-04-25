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

namespace FNV
{
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

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    if(DEST.IsLoaded() && DEST->DSTD.IsLoaded())
        op.Accept(DEST->DSTD->value);

    return op.Stop();
    }

bool FURNRecord::IsAnim01()
    {
    return (MNAM.value.value & fIsAnim01) != 0;
    }

void FURNRecord::IsAnim01(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim01) : (MNAM.value.value & ~fIsAnim01);
    }

bool FURNRecord::IsAnim02()
    {
    return (MNAM.value.value & fIsAnim02) != 0;
    }

void FURNRecord::IsAnim02(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim02) : (MNAM.value.value & ~fIsAnim02);
    }

bool FURNRecord::IsAnim03()
    {
    return (MNAM.value.value & fIsAnim03) != 0;
    }

void FURNRecord::IsAnim03(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim03) : (MNAM.value.value & ~fIsAnim03);
    }

bool FURNRecord::IsAnim04()
    {
    return (MNAM.value.value & fIsAnim04) != 0;
    }

void FURNRecord::IsAnim04(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim04) : (MNAM.value.value & ~fIsAnim04);
    }

bool FURNRecord::IsAnim05()
    {
    return (MNAM.value.value & fIsAnim05) != 0;
    }

void FURNRecord::IsAnim05(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim05) : (MNAM.value.value & ~fIsAnim05);
    }

bool FURNRecord::IsAnim06()
    {
    return (MNAM.value.value & fIsAnim06) != 0;
    }

void FURNRecord::IsAnim06(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim06) : (MNAM.value.value & ~fIsAnim06);
    }

bool FURNRecord::IsAnim07()
    {
    return (MNAM.value.value & fIsAnim07) != 0;
    }

void FURNRecord::IsAnim07(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim07) : (MNAM.value.value & ~fIsAnim07);
    }

bool FURNRecord::IsAnim08()
    {
    return (MNAM.value.value & fIsAnim08) != 0;
    }

void FURNRecord::IsAnim08(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim08) : (MNAM.value.value & ~fIsAnim08);
    }

bool FURNRecord::IsAnim09()
    {
    return (MNAM.value.value & fIsAnim09) != 0;
    }

void FURNRecord::IsAnim09(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim09) : (MNAM.value.value & ~fIsAnim09);
    }

bool FURNRecord::IsAnim10()
    {
    return (MNAM.value.value & fIsAnim10) != 0;
    }

void FURNRecord::IsAnim10(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim10) : (MNAM.value.value & ~fIsAnim10);
    }

bool FURNRecord::IsAnim11()
    {
    return (MNAM.value.value & fIsAnim11) != 0;
    }

void FURNRecord::IsAnim11(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim11) : (MNAM.value.value & ~fIsAnim11);
    }

bool FURNRecord::IsAnim12()
    {
    return (MNAM.value.value & fIsAnim12) != 0;
    }

void FURNRecord::IsAnim12(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim12) : (MNAM.value.value & ~fIsAnim12);
    }

bool FURNRecord::IsAnim13()
    {
    return (MNAM.value.value & fIsAnim13) != 0;
    }

void FURNRecord::IsAnim13(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim13) : (MNAM.value.value & ~fIsAnim13);
    }

bool FURNRecord::IsAnim14()
    {
    return (MNAM.value.value & fIsAnim14) != 0;
    }

void FURNRecord::IsAnim14(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim14) : (MNAM.value.value & ~fIsAnim14);
    }

bool FURNRecord::IsAnim15()
    {
    return (MNAM.value.value & fIsAnim15) != 0;
    }

void FURNRecord::IsAnim15(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim15) : (MNAM.value.value & ~fIsAnim15);
    }

bool FURNRecord::IsAnim16()
    {
    return (MNAM.value.value & fIsAnim16) != 0;
    }

void FURNRecord::IsAnim16(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim16) : (MNAM.value.value & ~fIsAnim16);
    }

bool FURNRecord::IsAnim17()
    {
    return (MNAM.value.value & fIsAnim17) != 0;
    }

void FURNRecord::IsAnim17(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim17) : (MNAM.value.value & ~fIsAnim17);
    }

bool FURNRecord::IsAnim18()
    {
    return (MNAM.value.value & fIsAnim18) != 0;
    }

void FURNRecord::IsAnim18(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim18) : (MNAM.value.value & ~fIsAnim18);
    }

bool FURNRecord::IsAnim19()
    {
    return (MNAM.value.value & fIsAnim19) != 0;
    }

void FURNRecord::IsAnim19(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim19) : (MNAM.value.value & ~fIsAnim19);
    }

bool FURNRecord::IsAnim20()
    {
    return (MNAM.value.value & fIsAnim20) != 0;
    }

void FURNRecord::IsAnim20(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim20) : (MNAM.value.value & ~fIsAnim20);
    }

bool FURNRecord::IsAnim21()
    {
    return (MNAM.value.value & fIsAnim21) != 0;
    }

void FURNRecord::IsAnim21(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim21) : (MNAM.value.value & ~fIsAnim21);
    }

bool FURNRecord::IsAnim22()
    {
    return (MNAM.value.value & fIsAnim22) != 0;
    }

void FURNRecord::IsAnim22(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim22) : (MNAM.value.value & ~fIsAnim22);
    }

bool FURNRecord::IsAnim23()
    {
    return (MNAM.value.value & fIsAnim23) != 0;
    }

void FURNRecord::IsAnim23(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim23) : (MNAM.value.value & ~fIsAnim23);
    }

bool FURNRecord::IsAnim24()
    {
    return (MNAM.value.value & fIsAnim24) != 0;
    }

void FURNRecord::IsAnim24(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim24) : (MNAM.value.value & ~fIsAnim24);
    }

bool FURNRecord::IsAnim25()
    {
    return (MNAM.value.value & fIsAnim25) != 0;
    }

void FURNRecord::IsAnim25(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim25) : (MNAM.value.value & ~fIsAnim25);
    }

bool FURNRecord::IsAnim26()
    {
    return (MNAM.value.value & fIsAnim26) != 0;
    }

void FURNRecord::IsAnim26(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim26) : (MNAM.value.value & ~fIsAnim26);
    }

bool FURNRecord::IsAnim27()
    {
    return (MNAM.value.value & fIsAnim27) != 0;
    }

void FURNRecord::IsAnim27(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim27) : (MNAM.value.value & ~fIsAnim27);
    }

bool FURNRecord::IsAnim28()
    {
    return (MNAM.value.value & fIsAnim28) != 0;
    }

void FURNRecord::IsAnim28(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim28) : (MNAM.value.value & ~fIsAnim28);
    }

bool FURNRecord::IsAnim29()
    {
    return (MNAM.value.value & fIsAnim29) != 0;
    }

void FURNRecord::IsAnim29(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim29) : (MNAM.value.value & ~fIsAnim29);
    }

bool FURNRecord::IsAnim30()
    {
    return (MNAM.value.value & fIsAnim30) != 0;
    }

void FURNRecord::IsAnim30(bool value)
    {
    MNAM.value.value = value ? (MNAM.value.value | fIsAnim30) : (MNAM.value.value & ~fIsAnim30);
    }

bool FURNRecord::IsSitAnim()
    {
    return (MNAM.value.value & fIsSitAnim) != 0;
    }

void FURNRecord::IsSitAnim(bool value)
    {
    if(value)
        {
        MNAM.value.value &= ~fIsSleepAnim;
        MNAM.value.value |= fIsSitAnim;
        }
    else
        {
        MNAM.value.value &= ~fIsSitAnim;
        MNAM.value.value |= fIsSleepAnim;
        }
    }

bool FURNRecord::IsSleepAnim()
    {
    return (MNAM.value.value & fIsSleepAnim) != 0;
    }

void FURNRecord::IsSleepAnim(bool value)
    {
    if(value)
        {
        MNAM.value.value &= ~fIsSitAnim;
        MNAM.value.value |= fIsSleepAnim;
        }
    else
        {
        MNAM.value.value &= ~fIsSleepAnim;
        MNAM.value.value |= fIsSitAnim;
        }
    }

bool FURNRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((MNAM.value.value & Mask) == Mask) : ((MNAM.value.value & Mask) != 0);
    }

void FURNRecord::SetFlagMask(UINT32 Mask)
    {
    MNAM.value.value = Mask;
    }

UINT32 FURNRecord::GetSize(bool forceCalc)
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

    if(MNAM.IsLoaded())
        {
        cSize = MNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

UINT32 FURNRecord::GetType()
    {
    return 'NRUF';
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
            case 'MANM':
                MNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  FURN: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
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
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    DEST.Unload();
    MNAM.Unload();
    return 1;
    }

SINT32 FURNRecord::WriteRecord(_FileHandler &SaveHandler)
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

    if(MNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANM', MNAM.value, MNAM.GetSize());

    return -1;
    }

bool FURNRecord::operator ==(const FURNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            SCRI == other.SCRI &&
            DEST == other.DEST &&
            MNAM == other.MNAM);
    }

bool FURNRecord::operator !=(const FURNRecord &other) const
    {
    return !(*this == other);
    }
}