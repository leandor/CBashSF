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
#include "BPTDRecord.h"

namespace FNV
{
BPTDRecord::BPTDRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

BPTDRecord::BPTDRecord(BPTDRecord *srcRecord):
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
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    BPTN = srcRecord->BPTN;
    BPNN = srcRecord->BPNN;
    BPNT = srcRecord->BPNT;
    BPNI = srcRecord->BPNI;
    BPND = srcRecord->BPND;
    NAM1 = srcRecord->NAM1;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    RAGA = srcRecord->RAGA;
    return;
    }

BPTDRecord::~BPTDRecord()
    {
    //
    }

bool BPTDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    //if(BPND.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(BPND->value);
    if(RAGA.IsLoaded())
        op.Accept(RAGA->value);

    return op.Stop();
    }

UINT32 BPTDRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && !IsChanged())
        return *(UINT32*)&recData[-16];

    UINT32 cSize = 0;
    UINT32 TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
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

    if(BPTN.IsLoaded())
        {
        cSize = BPTN.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(BPNN.IsLoaded())
        {
        cSize = BPNN.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(BPNT.IsLoaded())
        {
        cSize = BPNT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(BPNI.IsLoaded())
        {
        cSize = BPNI.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(BPND.IsLoaded())
        TotSize += BPND.GetSize() + 6;

    if(NAM1.IsLoaded())
        {
        cSize = NAM1.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM4.IsLoaded())
        {
        cSize = NAM4.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM5.IsLoaded())
        {
        cSize = NAM5.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(RAGA.IsLoaded())
        TotSize += RAGA.GetSize() + 6;

    return TotSize;
    }

UINT32 BPTDRecord::GetType()
    {
    return 'DTPB';
    }

STRING BPTDRecord::GetStrType()
    {
    return "BPTD";
    }

SINT32 BPTDRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'NTPB':
                BPTN.Read(buffer, subSize, curPos);
                break;
            case 'NNPB':
                BPNN.Read(buffer, subSize, curPos);
                break;
            case 'TNPB':
                BPNT.Read(buffer, subSize, curPos);
                break;
            case 'INPB':
                BPNI.Read(buffer, subSize, curPos);
                break;
            case 'DNPB':
                BPND.Read(buffer, subSize, curPos);
                break;
            case '1MAN':
                NAM1.Read(buffer, subSize, curPos);
                break;
            case '4MAN':
                NAM4.Read(buffer, subSize, curPos);
                break;
            case '5MAN':
                NAM5.Read(buffer, subSize, curPos);
                break;
            case 'AGAR':
                RAGA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  BPTD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 BPTDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    BPTN.Unload();
    BPNN.Unload();
    BPNT.Unload();
    BPNI.Unload();
    BPND.Unload();
    NAM1.Unload();
    NAM4.Unload();
    NAM5.Unload();
    RAGA.Unload();
    return 1;
    }

SINT32 BPTDRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

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

    if(BPTN.IsLoaded())
        SaveHandler.writeSubRecord('NTPB', BPTN.value, BPTN.GetSize());

    if(BPNN.IsLoaded())
        SaveHandler.writeSubRecord('NNPB', BPNN.value, BPNN.GetSize());

    if(BPNT.IsLoaded())
        SaveHandler.writeSubRecord('TNPB', BPNT.value, BPNT.GetSize());

    if(BPNI.IsLoaded())
        SaveHandler.writeSubRecord('INPB', BPNI.value, BPNI.GetSize());

    if(BPND.IsLoaded())
        SaveHandler.writeSubRecord('DNPB', BPND.value, BPND.GetSize());

    if(NAM1.IsLoaded())
        SaveHandler.writeSubRecord('1MAN', NAM1.value, NAM1.GetSize());

    if(NAM4.IsLoaded())
        SaveHandler.writeSubRecord('4MAN', NAM4.value, NAM4.GetSize());

    if(NAM5.IsLoaded())
        SaveHandler.writeSubRecord('5MAN', NAM5.value, NAM5.GetSize());

    if(RAGA.IsLoaded())
        SaveHandler.writeSubRecord('AGAR', RAGA.value, RAGA.GetSize());

    return -1;
    }

bool BPTDRecord::operator ==(const BPTDRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            BPTN.equalsi(other.BPTN) &&
            BPNN.equalsi(other.BPNN) &&
            BPNT.equalsi(other.BPNT) &&
            BPNI.equalsi(other.BPNI) &&
            BPND == other.BPND &&
            NAM1.equalsi(other.NAM1) &&
            NAM4.equalsi(other.NAM4) &&
            NAM5 == other.NAM5 &&
            RAGA == other.RAGA);
    }

bool BPTDRecord::operator !=(const BPTDRecord &other) const
    {
    return !(*this == other);
    }
}