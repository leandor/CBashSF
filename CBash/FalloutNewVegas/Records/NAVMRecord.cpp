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
#include "NAVMRecord.h"

namespace FNV
{
bool NAVMRecord::NAVMNVTR::IsTriangle0External()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTriangle0External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle0External(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsTriangle0External;
    else
        Dummy->flags &= ~fIsTriangle0External;
    }

bool NAVMRecord::NAVMNVTR::IsTriangle1External()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTriangle1External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle1External(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsTriangle1External;
    else
        Dummy->flags &= ~fIsTriangle1External;
    }

bool NAVMRecord::NAVMNVTR::IsTriangle2External()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTriangle2External) != 0;
    }

void NAVMRecord::NAVMNVTR::IsTriangle2External(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsTriangle2External;
    else
        Dummy->flags &= ~fIsTriangle2External;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown4()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown4) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown4(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown4;
    else
        Dummy->flags &= ~fIsUnknown4;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown5()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown5) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown5(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown5;
    else
        Dummy->flags &= ~fIsUnknown5;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown6()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown6) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown6(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown6;
    else
        Dummy->flags &= ~fIsUnknown6;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown7()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown7) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown7(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown7;
    else
        Dummy->flags &= ~fIsUnknown7;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown8()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown8) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown8(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown8;
    else
        Dummy->flags &= ~fIsUnknown8;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown9()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown9) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown9(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown9;
    else
        Dummy->flags &= ~fIsUnknown9;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown10()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown10) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown10(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown10;
    else
        Dummy->flags &= ~fIsUnknown10;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown11()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown11) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown11(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown11;
    else
        Dummy->flags &= ~fIsUnknown11;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown12()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown12) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown12(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown12;
    else
        Dummy->flags &= ~fIsUnknown12;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown13()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown13) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown13(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown13;
    else
        Dummy->flags &= ~fIsUnknown13;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown14()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown14) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown14(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown14;
    else
        Dummy->flags &= ~fIsUnknown14;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown15()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown15) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown15(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown15;
    else
        Dummy->flags &= ~fIsUnknown15;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown16()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown16) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown16(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown16;
    else
        Dummy->flags &= ~fIsUnknown16;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown17()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown17) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown17(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown17;
    else
        Dummy->flags &= ~fIsUnknown17;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown18()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown18) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown18(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown18;
    else
        Dummy->flags &= ~fIsUnknown18;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown19()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown19) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown19(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown19;
    else
        Dummy->flags &= ~fIsUnknown19;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown20()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown20) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown20(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown20;
    else
        Dummy->flags &= ~fIsUnknown20;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown21()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown21) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown21(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown21;
    else
        Dummy->flags &= ~fIsUnknown21;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown22()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown22) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown22(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown22;
    else
        Dummy->flags &= ~fIsUnknown22;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown23()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown23) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown23(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown23;
    else
        Dummy->flags &= ~fIsUnknown23;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown24()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown24) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown24(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown24;
    else
        Dummy->flags &= ~fIsUnknown24;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown25()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown25) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown25(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown25;
    else
        Dummy->flags &= ~fIsUnknown25;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown26()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown26) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown26(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown26;
    else
        Dummy->flags &= ~fIsUnknown26;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown27()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown27) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown27(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown27;
    else
        Dummy->flags &= ~fIsUnknown27;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown28()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown28) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown28(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown28;
    else
        Dummy->flags &= ~fIsUnknown28;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown29()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown29) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown29(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown29;
    else
        Dummy->flags &= ~fIsUnknown29;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown30()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown30) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown30(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown30;
    else
        Dummy->flags &= ~fIsUnknown30;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown31()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown31) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown31(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown31;
    else
        Dummy->flags &= ~fIsUnknown31;
    }

bool NAVMRecord::NAVMNVTR::IsUnknown32()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsUnknown32) != 0;
    }

void NAVMRecord::NAVMNVTR::IsUnknown32(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsUnknown32;
    else
        Dummy->flags &= ~fIsUnknown32;
    }

bool NAVMRecord::NAVMNVTR::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void NAVMRecord::NAVMNVTR::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

NAVMRecord::NAVMRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

NAVMRecord::NAVMRecord(NAVMRecord *srcRecord):
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
    NVER = srcRecord->NVER;
    DATA = srcRecord->DATA;
    NVVX = srcRecord->NVVX;
    NVTR = srcRecord->NVTR;
    NVCA = srcRecord->NVCA;
    NVDP = srcRecord->NVDP;
    NVGD = srcRecord->NVGD;
    NVEX = srcRecord->NVEX;
    return;
    }

NAVMRecord::~NAVMRecord()
    {
    //
    }

bool NAVMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);
    //if(NVDP.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(NVDP->value);
    //if(NVEX.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(NVEX->value);

    return op.Stop();
    }

UINT32 NAVMRecord::GetSize(bool forceCalc)
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

    if(NVER.IsLoaded())
        TotSize += NVER.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(NVVX.IsLoaded())
        TotSize += NVVX.GetSize() + 6;

    if(NVTR.IsLoaded())
        TotSize += NVTR.GetSize() + 6;

    if(NVCA.IsLoaded())
        TotSize += NVCA.GetSize() + 6;

    if(NVDP.IsLoaded())
        TotSize += NVDP.GetSize() + 6;

    if(NVGD.IsLoaded())
        TotSize += NVGD.GetSize() + 6;

    if(NVEX.IsLoaded())
        TotSize += NVEX.GetSize() + 6;

    return TotSize;
    }

UINT32 NAVMRecord::GetType()
    {
    return 'MVAN';
    }

STRING NAVMRecord::GetStrType()
    {
    return "NAVM";
    }

SINT32 NAVMRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'REVN':
                NVER.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'XVVN':
                NVVX.Read(buffer, subSize, curPos);
                break;
            case 'RTVN':
                NVTR.Read(buffer, subSize, curPos);
                break;
            case 'ACVN':
                NVCA.Read(buffer, subSize, curPos);
                break;
            case 'PDVN':
                NVDP.Read(buffer, subSize, curPos);
                break;
            case 'DGVN':
                NVGD.Read(buffer, subSize, curPos);
                break;
            case 'XEVN':
                NVEX.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  NAVM: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 NAVMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NVER.Unload();
    DATA.Unload();
    NVVX.Unload();
    NVTR.Unload();
    NVCA.Unload();
    NVDP.Unload();
    NVGD.Unload();
    NVEX.Unload();
    return 1;
    }

SINT32 NAVMRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(NVER.IsLoaded())
        SaveHandler.writeSubRecord('REVN', NVER.value, NVER.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(NVVX.IsLoaded())
        SaveHandler.writeSubRecord('XVVN', NVVX.value, NVVX.GetSize());

    if(NVTR.IsLoaded())
        SaveHandler.writeSubRecord('RTVN', NVTR.value, NVTR.GetSize());

    if(NVCA.IsLoaded())
        SaveHandler.writeSubRecord('ACVN', NVCA.value, NVCA.GetSize());

    if(NVDP.IsLoaded())
        SaveHandler.writeSubRecord('PDVN', NVDP.value, NVDP.GetSize());

    if(NVGD.IsLoaded())
        SaveHandler.writeSubRecord('DGVN', NVGD.value, NVGD.GetSize());

    if(NVEX.IsLoaded())
        SaveHandler.writeSubRecord('XEVN', NVEX.value, NVEX.GetSize());

    return -1;
    }

bool NAVMRecord::operator ==(const NAVMRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            DATA == other.DATA &&
            NVVX == other.NVVX &&
            NVTR == other.NVTR &&
            NVCA == other.NVCA &&
            NVDP == other.NVDP &&
            NVGD == other.NVGD &&
            NVEX == other.NVEX);
    }

bool NAVMRecord::operator !=(const NAVMRecord &other) const
    {
    return !(*this == other);
    }
}