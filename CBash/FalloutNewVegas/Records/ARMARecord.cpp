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
#include "ARMARecord.h"

namespace FNV
{
ARMARecord::ARMARecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ARMARecord::ARMARecord(ARMARecord *srcRecord):
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
    BMDT = srcRecord->BMDT;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    if(srcRecord->MOD2.IsLoaded())
        {
        MOD2.Load();
        MOD2->MOD2 = srcRecord->MOD2->MOD2;
        MOD2->MO2T = srcRecord->MOD2->MO2T;
        MOD2->MO2S = srcRecord->MOD2->MO2S;
        }
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    if(srcRecord->MOD3.IsLoaded())
        {
        MOD3.Load();
        MOD3->MOD3 = srcRecord->MOD3->MOD3;
        MOD3->MO3T = srcRecord->MOD3->MO3T;
        MOD3->MO3S = srcRecord->MOD3->MO3S;
        MOD3->MOSD = srcRecord->MOD3->MOSD;
        }
    if(srcRecord->MOD4.IsLoaded())
        {
        MOD4.Load();
        MOD4->MOD4 = srcRecord->MOD4->MOD4;
        MOD4->MO4T = srcRecord->MOD4->MO4T;
        MOD4->MO4S = srcRecord->MOD4->MO4S;
        }
    ICO2 = srcRecord->ICO2;
    MIC2 = srcRecord->MIC2;
    ETYP = srcRecord->ETYP;
    DATA = srcRecord->DATA;
    DNAM = srcRecord->DNAM;
    return;
    }

ARMARecord::~ARMARecord()
    {
    //
    }

bool ARMARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    if(MOD2.IsLoaded() && MOD2->MO2S.IsLoaded())
        op.Accept(MOD2->MO2S->value);
    if(MOD3.IsLoaded() && MOD3->MO3S.IsLoaded())
        op.Accept(MOD3->MO3S->value);
    if(MOD4.IsLoaded() && MOD4->MO4S.IsLoaded())
        op.Accept(MOD4->MO4S->value);

    return op.Stop();
    }

UINT32 ARMARecord::GetSize(bool forceCalc)
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

    if(OBND.IsLoaded())
        TotSize += OBND.GetSize() + 6;

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(BMDT.IsLoaded())
        TotSize += BMDT.GetSize() + 6;

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            {
            cSize = MODL->MODL.GetSize();
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

    if(MOD2.IsLoaded())
        {
        if(MOD2->MOD2.IsLoaded())
            {
            cSize = MOD2->MOD2.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD2->MO2T.IsLoaded())
            {
            cSize = MOD2->MO2T.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD2->MO2S.IsLoaded())
            TotSize += MOD2->MO2S.GetSize() + 6;
        }

    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MICO.IsLoaded())
        {
        cSize = MICO.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD3.IsLoaded())
        {
        if(MOD3->MOD3.IsLoaded())
            {
            cSize = MOD3->MOD3.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD3->MO3T.IsLoaded())
            {
            cSize = MOD3->MO3T.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD3->MO3S.IsLoaded())
            TotSize += MOD3->MO3S.GetSize() + 6;
        if(MOD3->MOSD.IsLoaded())
            TotSize += MOD3->MOSD.GetSize() + 6;
        }

    if(MOD4.IsLoaded())
        {
        if(MOD4->MOD4.IsLoaded())
            {
            cSize = MOD4->MOD4.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD4->MO4T.IsLoaded())
            {
            cSize = MOD4->MO4T.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(MOD4->MO4S.IsLoaded())
            TotSize += MOD4->MO4S.GetSize() + 6;
        }

    if(ICO2.IsLoaded())
        {
        cSize = ICO2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MIC2.IsLoaded())
        {
        cSize = MIC2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ETYP.IsLoaded())
        TotSize += ETYP.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    return TotSize;
    }

UINT32 ARMARecord::GetType()
    {
    return 'AMRA';
    }

STRING ARMARecord::GetStrType()
    {
    return "ARMA";
    }

SINT32 ARMARecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'TDMB':
                BMDT.Read(buffer, subSize, curPos);
                break;
            case 'LDOM':
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
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
            case '2DOM':
                MOD2.Load();
                MOD2->MOD2.Read(buffer, subSize, curPos);
                break;
            case 'T2OM':
                MOD2.Load();
                MOD2->MO2T.Read(buffer, subSize, curPos);
                break;
            case 'S2OM':
                MOD2.Load();
                MOD2->MO2S.Read(buffer, subSize, curPos);
                break;
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case '3DOM':
                MOD3.Load();
                MOD3->MOD3.Read(buffer, subSize, curPos);
                break;
            case 'T3OM':
                MOD3.Load();
                MOD3->MO3T.Read(buffer, subSize, curPos);
                break;
            case 'S3OM':
                MOD3.Load();
                MOD3->MO3S.Read(buffer, subSize, curPos);
                break;
            case 'DSOM':
                MOD3.Load();
                MOD3->MOSD.Read(buffer, subSize, curPos);
                break;
            case '4DOM':
                MOD4.Load();
                MOD4->MOD4.Read(buffer, subSize, curPos);
                break;
            case 'T4OM':
                MOD4.Load();
                MOD4->MO4T.Read(buffer, subSize, curPos);
                break;
            case 'S4OM':
                MOD4.Load();
                MOD4->MO4S.Read(buffer, subSize, curPos);
                break;
            case '2OCI':
                ICO2.Read(buffer, subSize, curPos);
                break;
            case '2CIM':
                MIC2.Read(buffer, subSize, curPos);
                break;
            case 'PYTE':
                ETYP.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ARMA: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 ARMARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    BMDT.Unload();
    MODL.Unload();
    MOD2.Unload();
    ICON.Unload();
    MICO.Unload();
    MOD3.Unload();
    MOD4.Unload();
    ICO2.Unload();
    MIC2.Unload();
    ETYP.Unload();
    DATA.Unload();
    DNAM.Unload();
    return 1;
    }

SINT32 ARMARecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(BMDT.IsLoaded())
        SaveHandler.writeSubRecord('TDMB', BMDT.value, BMDT.GetSize());

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());

        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());

        if(MODL->MODS.IsLoaded())
            SaveHandler.writeSubRecord('SDOM', MODL->MODS.value, MODL->MODS.GetSize());

        if(MODL->MODD.IsLoaded())
            SaveHandler.writeSubRecord('DDOM', MODL->MODD.value, MODL->MODD.GetSize());

        }

    if(MOD2.IsLoaded())
        {
        if(MOD2->MOD2.IsLoaded())
            SaveHandler.writeSubRecord('2DOM', MOD2->MOD2.value, MOD2->MOD2.GetSize());

        if(MOD2->MO2T.IsLoaded())
            SaveHandler.writeSubRecord('T2OM', MOD2->MO2T.value, MOD2->MO2T.GetSize());

        if(MOD2->MO2S.IsLoaded())
            SaveHandler.writeSubRecord('S2OM', MOD2->MO2S.value, MOD2->MO2S.GetSize());

        }

    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', ICON.value, ICON.GetSize());

    if(MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MICO.value, MICO.GetSize());

    if(MOD3.IsLoaded())
        {
        if(MOD3->MOD3.IsLoaded())
            SaveHandler.writeSubRecord('3DOM', MOD3->MOD3.value, MOD3->MOD3.GetSize());

        if(MOD3->MO3T.IsLoaded())
            SaveHandler.writeSubRecord('T3OM', MOD3->MO3T.value, MOD3->MO3T.GetSize());

        if(MOD3->MO3S.IsLoaded())
            SaveHandler.writeSubRecord('S3OM', MOD3->MO3S.value, MOD3->MO3S.GetSize());

        if(MOD3->MOSD.IsLoaded())
            SaveHandler.writeSubRecord('DSOM', MOD3->MOSD.value, MOD3->MOSD.GetSize());

        }

    if(MOD4.IsLoaded())
        {
        if(MOD4->MOD4.IsLoaded())
            SaveHandler.writeSubRecord('4DOM', MOD4->MOD4.value, MOD4->MOD4.GetSize());

        if(MOD4->MO4T.IsLoaded())
            SaveHandler.writeSubRecord('T4OM', MOD4->MO4T.value, MOD4->MO4T.GetSize());

        if(MOD4->MO4S.IsLoaded())
            SaveHandler.writeSubRecord('S4OM', MOD4->MO4S.value, MOD4->MO4S.GetSize());

        }

    if(ICO2.IsLoaded())
        SaveHandler.writeSubRecord('2OCI', ICO2.value, ICO2.GetSize());

    if(MIC2.IsLoaded())
        SaveHandler.writeSubRecord('2CIM', MIC2.value, MIC2.GetSize());

    if(ETYP.IsLoaded())
        SaveHandler.writeSubRecord('PYTE', ETYP.value, ETYP.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    return -1;
    }

bool ARMARecord::operator ==(const ARMARecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            BMDT == other.BMDT &&
            MODL == other.MODL &&
            MOD2 == other.MOD2 &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4 &&
            ICO2.equalsi(other.ICO2) &&
            MIC2.equalsi(other.MIC2) &&
            ETYP == other.ETYP &&
            DATA == other.DATA &&
            DNAM == other.DNAM);
    }

bool ARMARecord::operator !=(const ARMARecord &other) const
    {
    return !(*this == other);
    }
}