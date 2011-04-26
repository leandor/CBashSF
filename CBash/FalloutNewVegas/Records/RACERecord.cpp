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
#include "RACERecord.h"

namespace FNV
{
RACERecord::RACERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

RACERecord::RACERecord(RACERecord *srcRecord):
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
    FULL = srcRecord->FULL;
    DESC = srcRecord->DESC;
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    ONAM = srcRecord->ONAM;
    YNAM = srcRecord->YNAM;
    NAM2 = srcRecord->NAM2;
    VTCK = srcRecord->VTCK;
    DNAM = srcRecord->DNAM;
    CNAM = srcRecord->CNAM;
    PNAM = srcRecord->PNAM;
    UNAM = srcRecord->UNAM;
    ATTR = srcRecord->ATTR;
    NAM0 = srcRecord->NAM0;
    MNAM = srcRecord->MNAM;
    INDX = srcRecord->INDX;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODT = srcRecord->MODL->MODT;
        MODL->MODS = srcRecord->MODL->MODS;
        MODL->MODD = srcRecord->MODL->MODD;
        }
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    FNAM = srcRecord->FNAM;
    NAM1 = srcRecord->NAM1;
    HNAM = srcRecord->HNAM;
    ENAM = srcRecord->ENAM;
    if(srcRecord->FGGS.IsLoaded())
        {
        FGGS.Load();
        FGGS->FGGS = srcRecord->FGGS->FGGS;
        FGGS->FGGA = srcRecord->FGGS->FGGA;
        FGGS->FGTS = srcRecord->FGGS->FGTS;
        }
    SNAM = srcRecord->SNAM;
    return;
    }

RACERecord::~RACERecord()
    {
    //
    }

bool RACERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(XNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(XNAM->value);
    if(ONAM.IsLoaded())
        op.Accept(ONAM->value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    //if(VTCK.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(VTCK->value);
    //if(DNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DNAM->value);
    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    //if(HNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(HNAM->value);
    //if(ENAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(ENAM->value);

    return op.Stop();
    }

bool RACERecord::IsPlayable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPlayable) != 0;
    }

void RACERecord::IsPlayable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsPlayable;
    else
        Dummy->flags &= ~fIsPlayable;
    }

bool RACERecord::IsChild()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsChild) != 0;
    }

void RACERecord::IsChild(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags |= fIsChild;
    else
        Dummy->flags &= ~fIsChild;
    }

bool RACERecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void RACERecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 RACERecord::GetSize(bool forceCalc)
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

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XNAM.IsLoaded())
        TotSize += XNAM.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(ONAM.IsLoaded())
        TotSize += ONAM.GetSize() + 6;

    if(YNAM.IsLoaded())
        TotSize += YNAM.GetSize() + 6;

    if(NAM2.IsLoaded())
        TotSize += NAM2.GetSize() + 6;

    if(VTCK.IsLoaded())
        TotSize += VTCK.GetSize() + 6;

    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;

    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(UNAM.IsLoaded())
        TotSize += UNAM.GetSize() + 6;

    if(ATTR.IsLoaded())
        {
        cSize = ATTR.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM0.IsLoaded())
        TotSize += NAM0.GetSize() + 6;

    if(MNAM.IsLoaded())
        TotSize += MNAM.GetSize() + 6;

    if(INDX.IsLoaded())
        TotSize += INDX.GetSize() + 6;

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

    if(FNAM.IsLoaded())
        TotSize += FNAM.GetSize() + 6;

    if(NAM1.IsLoaded())
        TotSize += NAM1.GetSize() + 6;

    if(HNAM.IsLoaded())
        TotSize += HNAM.GetSize() + 6;

    if(ENAM.IsLoaded())
        TotSize += ENAM.GetSize() + 6;

    if(FGGS.IsLoaded())
        {
        if(FGGS->FGGS.IsLoaded())
            {
            cSize = FGGS->FGGS.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FGGS->FGGA.IsLoaded())
            {
            cSize = FGGS->FGGA.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(FGGS->FGTS.IsLoaded())
            {
            cSize = FGGS->FGTS.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(SNAM.IsLoaded())
        {
        cSize = SNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

UINT32 RACERecord::GetType()
    {
    return 'ECAR';
    }

STRING RACERecord::GetStrType()
    {
    return "RACE";
    }

SINT32 RACERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'CSED':
                DESC.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                ONAM.Read(buffer, subSize, curPos);
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case '2MAN':
                //NAM2.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'KCTV':
                VTCK.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANU':
                UNAM.Read(buffer, subSize, curPos);
                break;
            case 'RTTA':
                ATTR.Read(buffer, subSize, curPos);
                break;
            case '0MAN':
                //NAM0.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MANM':
                //MNAM.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'XDNI':
                INDX.Read(buffer, subSize, curPos);
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
            case 'NOCI':
                ICON.Read(buffer, subSize, curPos);
                break;
            case 'OCIM':
                MICO.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                //FNAM.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case '1MAN':
                //NAM1.Read(buffer, subSize, curPos); //FILL IN MANUALLY
                break;
            case 'MANH':
                HNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANE':
                ENAM.Read(buffer, subSize, curPos);
                break;
            case 'SGGF':
                FGGS.Load();
                FGGS->FGGS.Read(buffer, subSize, curPos);
                break;
            case 'AGGF':
                FGGS.Load();
                FGGS->FGGA.Read(buffer, subSize, curPos);
                break;
            case 'STGF':
                FGGS.Load();
                FGGS->FGTS.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  RACE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 RACERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    XNAM.Unload();
    DATA.Unload();
    ONAM.Unload();
    YNAM.Unload();
    //NAM2.Unload(); //FILL IN MANUALLY
    VTCK.Unload();
    DNAM.Unload();
    CNAM.Unload();
    PNAM.Unload();
    UNAM.Unload();
    ATTR.Unload();
    //NAM0.Unload(); //FILL IN MANUALLY
    //MNAM.Unload(); //FILL IN MANUALLY
    INDX.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    //FNAM.Unload(); //FILL IN MANUALLY
    //NAM1.Unload(); //FILL IN MANUALLY
    HNAM.Unload();
    ENAM.Unload();
    FGGS.Unload();
    SNAM.Unload();
    return 1;
    }

SINT32 RACERecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord('CSED', DESC.value, DESC.GetSize());

    if(XNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANX', XNAM.value, XNAM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    if(ONAM.IsLoaded())
        SaveHandler.writeSubRecord('MANO', ONAM.value, ONAM.GetSize());

    if(YNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANY', YNAM.value, YNAM.GetSize());

    //if(NAM2.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('2MAN', NAM2.value, NAM2.GetSize());

    if(VTCK.IsLoaded())
        SaveHandler.writeSubRecord('KCTV', VTCK.value, VTCK.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANC', CNAM.value, CNAM.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', PNAM.value, PNAM.GetSize());

    if(UNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANU', UNAM.value, UNAM.GetSize());

    if(ATTR.IsLoaded())
        SaveHandler.writeSubRecord('RTTA', ATTR.value, ATTR.GetSize());

    //if(NAM0.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('0MAN', NAM0.value, NAM0.GetSize());

    //if(MNAM.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('MANM', MNAM.value, MNAM.GetSize());

    if(INDX.IsLoaded())
        SaveHandler.writeSubRecord('XDNI', INDX.value, INDX.GetSize());

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

    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord('NOCI', ICON.value, ICON.GetSize());

    if(MICO.IsLoaded())
        SaveHandler.writeSubRecord('OCIM', MICO.value, MICO.GetSize());

    //if(FNAM.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('MANF', FNAM.value, FNAM.GetSize());

    //if(NAM1.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord('1MAN', NAM1.value, NAM1.GetSize());

    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANH', HNAM.value, HNAM.GetSize());

    if(ENAM.IsLoaded())
        SaveHandler.writeSubRecord('MANE', ENAM.value, ENAM.GetSize());

    if(FGGS.IsLoaded())
        {
        if(FGGS->FGGS.IsLoaded())
            SaveHandler.writeSubRecord('SGGF', FGGS->FGGS.value, FGGS->FGGS.GetSize());

        if(FGGS->FGGA.IsLoaded())
            SaveHandler.writeSubRecord('AGGF', FGGS->FGGA.value, FGGS->FGGA.GetSize());

        if(FGGS->FGTS.IsLoaded())
            SaveHandler.writeSubRecord('STGF', FGGS->FGTS.value, FGGS->FGTS.GetSize());

        }

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    return -1;
    }

bool RACERecord::operator ==(const RACERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            XNAM == other.XNAM &&
            DATA == other.DATA &&
            ONAM == other.ONAM &&
            YNAM == other.YNAM &&
            //Empty &&
            VTCK == other.VTCK &&
            DNAM == other.DNAM &&
            CNAM == other.CNAM &&
            PNAM == other.PNAM &&
            UNAM == other.UNAM &&
            ATTR == other.ATTR &&
            //Empty &&
            //Empty &&
            INDX == other.INDX &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            //Empty &&
            //Empty &&
            HNAM == other.HNAM &&
            ENAM == other.ENAM &&
            FGGS == other.FGGS &&
            SNAM == other.SNAM);
    }

bool RACERecord::operator !=(const RACERecord &other) const
    {
    return !(*this == other);
    }
}