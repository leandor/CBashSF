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
#include "WTHRRecord.h"

namespace FNV
{
WTHRRecord::WTHRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

WTHRRecord::WTHRRecord(WTHRRecord *srcRecord):
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
    0IAD = srcRecord->0IAD;
    1IAD = srcRecord->1IAD;
    2IAD = srcRecord->2IAD;
    3IAD = srcRecord->3IAD;
    4IAD = srcRecord->4IAD;
    5IAD = srcRecord->5IAD;
    DNAM = srcRecord->DNAM;
    CNAM = srcRecord->CNAM;
    ANAM = srcRecord->ANAM;
    BNAM = srcRecord->BNAM;

    MODL = srcRecord->MODL;

    LNAM = srcRecord->LNAM;
    ONAM = srcRecord->ONAM;
    PNAM = srcRecord->PNAM;
    NAM0 = srcRecord->NAM0;
    FNAM = srcRecord->FNAM;
    INAM = srcRecord->INAM;
    DATA = srcRecord->DATA;
    SNAM = srcRecord->SNAM;
    return;
    }

WTHRRecord::~WTHRRecord()
    {
    //
    }

bool WTHRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(0IAD.IsLoaded())
        op.Accept(0IAD->value);
    if(1IAD.IsLoaded())
        op.Accept(1IAD->value);
    if(2IAD.IsLoaded())
        op.Accept(2IAD->value);
    if(3IAD.IsLoaded())
        op.Accept(3IAD->value);
    if(4IAD.IsLoaded())
        op.Accept(4IAD->value);
    if(5IAD.IsLoaded())
        op.Accept(5IAD->value);
    if(MODL.IsLoaded() && MODL->MODS.IsLoaded())
        op.Accept(MODL->MODS->value);
    //if(SNAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(SNAM->value);

    return op.Stop();
    }

bool WTHRRecord::IsPleasant()
    {
    return (DATA.value.weatherType & ePleasant) != 0;
    }

void WTHRRecord::IsPleasant(bool value)
    {
    if(value)
        {
        DATA.value.weatherType |= ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsPleasant())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsCloudy()
    {
    return (DATA.value.weatherType & eCloudy) != 0;
    }

void WTHRRecord::IsCloudy(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType |= eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsCloudy())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsRainy()
    {
    return (DATA.value.weatherType & eRainy) != 0;
    }

void WTHRRecord::IsRainy(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType |= eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsRainy())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsSnow()
    {
    return (DATA.value.weatherType & eSnow) != 0;
    }

void WTHRRecord::IsSnow(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType |= eSnow;
        }
    else if(IsSnow())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsNone()
    {
    return IsPleasant() == false && IsCloudy() == false && IsRainy() == false && IsSnow() == false;
    }

void WTHRRecord::IsNone(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsNone())
        {
        DATA.value.weatherType |= ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsUnk1()
    {
    return (DATA.value.weatherType & fUnk1) != 0;
    }

void WTHRRecord::IsUnk1(bool value)
    {
    DATA.value.weatherType = value ? (DATA.value.weatherType | fUnk1) : (DATA.value.weatherType & ~fUnk1);
    }

bool WTHRRecord::IsUnk2()
    {
    return (DATA.value.weatherType & fUnk2) != 0;
    }

void WTHRRecord::IsUnk2(bool value)
    {
    DATA.value.weatherType = value ? (DATA.value.weatherType | fUnk2) : (DATA.value.weatherType & ~fUnk2);
    }

bool WTHRRecord::IsType(UINT8 Type)
    {
    return (DATA.value.weatherType == Type);
    }

void WTHRRecord::SetType(UINT8 Type)
    {
    DATA.value.weatherType = Type;
    }

bool WTHRRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.weatherType & Mask) == Mask) : ((DATA.value.weatherType & Mask) != 0);
    }

void WTHRRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.weatherType = Mask;
    }

UINT32 WTHRRecord::GetType()
    {
    return 'RHTW';
    }

STRING WTHRRecord::GetStrType()
    {
    return "WTHR";
    }

SINT32 WTHRRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'DAI0':
                0IAD.Read(buffer, subSize, curPos);
                break;
            case 'DAI1':
                1IAD.Read(buffer, subSize, curPos);
                break;
            case 'DAI2':
                2IAD.Read(buffer, subSize, curPos);
                break;
            case 'DAI3':
                3IAD.Read(buffer, subSize, curPos);
                break;
            case 'DAI4':
                4IAD.Read(buffer, subSize, curPos);
                break;
            case 'DAI5':
                5IAD.Read(buffer, subSize, curPos);
                break;
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANC':
                CNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'MANB':
                BNAM.Read(buffer, subSize, curPos);
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
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case 'DDOM':
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case 'MANL':
                LNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANO':
                ONAM.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case '0MAN':
                NAM0.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  WTHR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 WTHRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    0IAD.Unload();
    1IAD.Unload();
    2IAD.Unload();
    3IAD.Unload();
    4IAD.Unload();
    5IAD.Unload();
    DNAM.Unload();
    CNAM.Unload();
    ANAM.Unload();
    BNAM.Unload();
    MODL.Unload();
    LNAM.Unload();
    ONAM.Unload();
    PNAM.Unload();
    NAM0.Unload();
    FNAM.Unload();
    INAM.Unload();
    DATA.Unload();
    SNAM.Unload();
    return 1;
    }

SINT32 WTHRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(0IAD);
    WRITE(1IAD);
    WRITE(2IAD);
    WRITE(3IAD);
    WRITE(4IAD);
    WRITE(5IAD);
    WRITE(DNAM);
    WRITE(CNAM);
    WRITE(ANAM);
    WRITE(BNAM);

    MODL.Write(writer);

    WRITE(LNAM);
    WRITE(ONAM);
    WRITE(PNAM);
    WRITE(NAM0);
    WRITE(FNAM);
    WRITE(INAM);
    WRITE(DATA);
    WRITE(SNAM);

    return -1;
    }

bool WTHRRecord::operator ==(const WTHRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            0IAD == other.0IAD &&
            1IAD == other.1IAD &&
            2IAD == other.2IAD &&
            3IAD == other.3IAD &&
            4IAD == other.4IAD &&
            5IAD == other.5IAD &&
            DNAM.equalsi(other.DNAM) &&
            CNAM.equalsi(other.CNAM) &&
            ANAM.equalsi(other.ANAM) &&
            BNAM.equalsi(other.BNAM) &&
            MODL == other.MODL &&
            LNAM == other.LNAM &&
            ONAM == other.ONAM &&
            PNAM == other.PNAM &&
            NAM0 == other.NAM0 &&
            FNAM == other.FNAM &&
            INAM == other.INAM &&
            DATA == other.DATA &&
            SNAM == other.SNAM);
    }

bool WTHRRecord::operator !=(const WTHRRecord &other) const
    {
    return !(*this == other);
    }
}