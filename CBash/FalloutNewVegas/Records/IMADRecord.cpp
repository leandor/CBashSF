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
#include "IMADRecord.h"

namespace FNV
{
IMADRecord::IMADRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

IMADRecord::IMADRecord(IMADRecord *srcRecord):
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
    DNAM = srcRecord->DNAM;
    BNAM = srcRecord->BNAM;
    VNAM = srcRecord->VNAM;
    TNAM = srcRecord->TNAM;
    NAM3 = srcRecord->NAM3;
    RNAM = srcRecord->RNAM;
    SNAM = srcRecord->SNAM;
    UNAM = srcRecord->UNAM;
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    WNAM = srcRecord->WNAM;
    XNAM = srcRecord->XNAM;
    YNAM = srcRecord->YNAM;
    NAM4 = srcRecord->NAM4;
    _00_ = srcRecord->_00_;
    _40_ = srcRecord->_40_;
    _01_ = srcRecord->_01_;
    _41_ = srcRecord->_41_;
    _02_ = srcRecord->_02_;
    _42_ = srcRecord->_42_;
    _03_ = srcRecord->_03_;
    _43_ = srcRecord->_43_;
    _04_ = srcRecord->_04_;
    _44_ = srcRecord->_44_;
    _05_ = srcRecord->_05_;
    _45_ = srcRecord->_45_;
    _06_ = srcRecord->_06_;
    _46_ = srcRecord->_46_;
    _07_ = srcRecord->_07_;
    _47_ = srcRecord->_47_;
    _08_ = srcRecord->_08_;
    _48_ = srcRecord->_48_;
    _09_ = srcRecord->_09_;
    _49_ = srcRecord->_49_;
    _0A_ = srcRecord->_0A_;
    _4A_ = srcRecord->_4A_;
    _0B_ = srcRecord->_0B_;
    _4B_ = srcRecord->_4B_;
    _0C_ = srcRecord->_0C_;
    _4C_ = srcRecord->_4C_;
    _0D_ = srcRecord->_0D_;
    _4D_ = srcRecord->_4D_;
    _0E_ = srcRecord->_0E_;
    _4E_ = srcRecord->_4E_;
    _0F_ = srcRecord->_0F_;
    _4F_ = srcRecord->_4F_;
    _10_ = srcRecord->_10_;
    _50_ = srcRecord->_50_;
    _11_ = srcRecord->_11_;
    _51_ = srcRecord->_51_;
    _12_ = srcRecord->_12_;
    _52_ = srcRecord->_52_;
    _13_ = srcRecord->_13_;
    _53_ = srcRecord->_53_;
    _14_ = srcRecord->_14_;
    _54_ = srcRecord->_54_;
    RDSD = srcRecord->RDSD;
    RDSI = srcRecord->RDSI;
    return;
    }

IMADRecord::~IMADRecord()
    {
    //
    }

bool IMADRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(RDSD.IsLoaded())
        op.Accept(RDSD->value);
    if(RDSI.IsLoaded())
        op.Accept(RDSI->value);

    return op.Stop();
    }

UINT32 IMADRecord::GetSize(bool forceCalc)
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

    if(DNAM.IsLoaded())
        {
        cSize = DNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(BNAM.IsLoaded())
        {
        cSize = BNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(VNAM.IsLoaded())
        {
        cSize = VNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(TNAM.IsLoaded())
        {
        cSize = TNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM3.IsLoaded())
        {
        cSize = NAM3.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(RNAM.IsLoaded())
        {
        cSize = RNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SNAM.IsLoaded())
        {
        cSize = SNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(UNAM.IsLoaded())
        {
        cSize = UNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM1.IsLoaded())
        {
        cSize = NAM1.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM2.IsLoaded())
        {
        cSize = NAM2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(WNAM.IsLoaded())
        {
        cSize = WNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XNAM.IsLoaded())
        {
        cSize = XNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(YNAM.IsLoaded())
        {
        cSize = YNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM4.IsLoaded())
        {
        cSize = NAM4.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_00_.IsLoaded())
        {
        cSize = _00_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_40_.IsLoaded())
        {
        cSize = _40_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_01_.IsLoaded())
        {
        cSize = _01_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_41_.IsLoaded())
        {
        cSize = _41_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_02_.IsLoaded())
        {
        cSize = _02_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_42_.IsLoaded())
        {
        cSize = _42_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_03_.IsLoaded())
        {
        cSize = _03_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_43_.IsLoaded())
        {
        cSize = _43_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_04_.IsLoaded())
        {
        cSize = _04_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_44_.IsLoaded())
        {
        cSize = _44_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_05_.IsLoaded())
        {
        cSize = _05_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_45_.IsLoaded())
        {
        cSize = _45_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_06_.IsLoaded())
        {
        cSize = _06_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_46_.IsLoaded())
        {
        cSize = _46_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_07_.IsLoaded())
        {
        cSize = _07_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_47_.IsLoaded())
        {
        cSize = _47_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_08_.IsLoaded())
        {
        cSize = _08_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_48_.IsLoaded())
        {
        cSize = _48_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_09_.IsLoaded())
        {
        cSize = _09_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_49_.IsLoaded())
        {
        cSize = _49_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_0A_.IsLoaded())
        {
        cSize = _0A_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_4A_.IsLoaded())
        {
        cSize = _4A_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_0B_.IsLoaded())
        {
        cSize = _0B_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_4B_.IsLoaded())
        {
        cSize = _4B_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_0C_.IsLoaded())
        {
        cSize = _0C_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_4C_.IsLoaded())
        {
        cSize = _4C_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_0D_.IsLoaded())
        {
        cSize = _0D_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_4D_.IsLoaded())
        {
        cSize = _4D_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_0E_.IsLoaded())
        {
        cSize = _0E_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_4E_.IsLoaded())
        {
        cSize = _4E_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_0F_.IsLoaded())
        {
        cSize = _0F_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_4F_.IsLoaded())
        {
        cSize = _4F_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_10_.IsLoaded())
        {
        cSize = _10_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_50_.IsLoaded())
        {
        cSize = _50_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_11_.IsLoaded())
        {
        cSize = _11_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_51_.IsLoaded())
        {
        cSize = _51_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_12_.IsLoaded())
        {
        cSize = _12_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_52_.IsLoaded())
        {
        cSize = _52_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_13_.IsLoaded())
        {
        cSize = _13_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_53_.IsLoaded())
        {
        cSize = _53_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_14_.IsLoaded())
        {
        cSize = _14_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(_54_.IsLoaded())
        {
        cSize = _54_.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(RDSD.IsLoaded())
        TotSize += RDSD.GetSize() + 6;

    if(RDSI.IsLoaded())
        TotSize += RDSI.GetSize() + 6;

    return TotSize;
    }

UINT32 IMADRecord::GetType()
    {
    return 'DAMI';
    }

STRING IMADRecord::GetStrType()
    {
    return "IMAD";
    }

SINT32 IMADRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'MAND':
                DNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANB':
                BNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANV':
                VNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                TNAM.Read(buffer, subSize, curPos);
                break;
            case '3MAN':
                NAM3.Read(buffer, subSize, curPos);
                break;
            case 'MANR':
                RNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANU':
                UNAM.Read(buffer, subSize, curPos);
                break;
            case '1MAN':
                NAM1.Read(buffer, subSize, curPos);
                break;
            case '2MAN':
                NAM2.Read(buffer, subSize, curPos);
                break;
            case 'MANW':
                WNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANX':
                XNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANY':
                YNAM.Read(buffer, subSize, curPos);
                break;
            case '4MAN':
                NAM4.Read(buffer, subSize, curPos);
                break;
            case '_00_':
                _00_.Read(buffer, subSize, curPos);
                break;
            case '_04_':
                _40_.Read(buffer, subSize, curPos);
                break;
            case '_10_':
                _01_.Read(buffer, subSize, curPos);
                break;
            case '_14_':
                _41_.Read(buffer, subSize, curPos);
                break;
            case '_20_':
                _02_.Read(buffer, subSize, curPos);
                break;
            case '_24_':
                _42_.Read(buffer, subSize, curPos);
                break;
            case '_30_':
                _03_.Read(buffer, subSize, curPos);
                break;
            case '_34_':
                _43_.Read(buffer, subSize, curPos);
                break;
            case '_40_':
                _04_.Read(buffer, subSize, curPos);
                break;
            case '_44_':
                _44_.Read(buffer, subSize, curPos);
                break;
            case '_50_':
                _05_.Read(buffer, subSize, curPos);
                break;
            case '_54_':
                _45_.Read(buffer, subSize, curPos);
                break;
            case '_60_':
                _06_.Read(buffer, subSize, curPos);
                break;
            case '_64_':
                _46_.Read(buffer, subSize, curPos);
                break;
            case '_70_':
                _07_.Read(buffer, subSize, curPos);
                break;
            case '_74_':
                _47_.Read(buffer, subSize, curPos);
                break;
            case '_80_':
                _08_.Read(buffer, subSize, curPos);
                break;
            case '_84_':
                _48_.Read(buffer, subSize, curPos);
                break;
            case '_90_':
                _09_.Read(buffer, subSize, curPos);
                break;
            case '_94_':
                _49_.Read(buffer, subSize, curPos);
                break;
            case '_A0_':
                _0A_.Read(buffer, subSize, curPos);
                break;
            case '_A4_':
                _4A_.Read(buffer, subSize, curPos);
                break;
            case '_B0_':
                _0B_.Read(buffer, subSize, curPos);
                break;
            case '_B4_':
                _4B_.Read(buffer, subSize, curPos);
                break;
            case '_C0_':
                _0C_.Read(buffer, subSize, curPos);
                break;
            case '_C4_':
                _4C_.Read(buffer, subSize, curPos);
                break;
            case '_D0_':
                _0D_.Read(buffer, subSize, curPos);
                break;
            case '_D4_':
                _4D_.Read(buffer, subSize, curPos);
                break;
            case '_E0_':
                _0E_.Read(buffer, subSize, curPos);
                break;
            case '_E4_':
                _4E_.Read(buffer, subSize, curPos);
                break;
            case '_F0_':
                _0F_.Read(buffer, subSize, curPos);
                break;
            case '_F4_':
                _4F_.Read(buffer, subSize, curPos);
                break;
            case '_01_':
                _10_.Read(buffer, subSize, curPos);
                break;
            case '_05_':
                _50_.Read(buffer, subSize, curPos);
                break;
            case '_11_':
                _11_.Read(buffer, subSize, curPos);
                break;
            case '_15_':
                _51_.Read(buffer, subSize, curPos);
                break;
            case '_21_':
                _12_.Read(buffer, subSize, curPos);
                break;
            case '_25_':
                _52_.Read(buffer, subSize, curPos);
                break;
            case '_31_':
                _13_.Read(buffer, subSize, curPos);
                break;
            case '_35_':
                _53_.Read(buffer, subSize, curPos);
                break;
            case '_41_':
                _14_.Read(buffer, subSize, curPos);
                break;
            case '_45_':
                _54_.Read(buffer, subSize, curPos);
                break;
            case 'DSDR':
                RDSD.Read(buffer, subSize, curPos);
                break;
            case 'ISDR':
                RDSI.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IMAD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 IMADRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DNAM.Unload();
    BNAM.Unload();
    VNAM.Unload();
    TNAM.Unload();
    NAM3.Unload();
    RNAM.Unload();
    SNAM.Unload();
    UNAM.Unload();
    NAM1.Unload();
    NAM2.Unload();
    WNAM.Unload();
    XNAM.Unload();
    YNAM.Unload();
    NAM4.Unload();
    _00_.Unload();
    _40_.Unload();
    _01_.Unload();
    _41_.Unload();
    _02_.Unload();
    _42_.Unload();
    _03_.Unload();
    _43_.Unload();
    _04_.Unload();
    _44_.Unload();
    _05_.Unload();
    _45_.Unload();
    _06_.Unload();
    _46_.Unload();
    _07_.Unload();
    _47_.Unload();
    _08_.Unload();
    _48_.Unload();
    _09_.Unload();
    _49_.Unload();
    _0A_.Unload();
    _4A_.Unload();
    _0B_.Unload();
    _4B_.Unload();
    _0C_.Unload();
    _4C_.Unload();
    _0D_.Unload();
    _4D_.Unload();
    _0E_.Unload();
    _4E_.Unload();
    _0F_.Unload();
    _4F_.Unload();
    _10_.Unload();
    _50_.Unload();
    _11_.Unload();
    _51_.Unload();
    _12_.Unload();
    _52_.Unload();
    _13_.Unload();
    _53_.Unload();
    _14_.Unload();
    _54_.Unload();
    RDSD.Unload();
    RDSI.Unload();
    return 1;
    }

SINT32 IMADRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord('MAND', DNAM.value, DNAM.GetSize());

    if(BNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANB', BNAM.value, BNAM.GetSize());

    if(VNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANV', VNAM.value, VNAM.GetSize());

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANT', TNAM.value, TNAM.GetSize());

    if(NAM3.IsLoaded())
        SaveHandler.writeSubRecord('3MAN', NAM3.value, NAM3.GetSize());

    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANR', RNAM.value, RNAM.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(UNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANU', UNAM.value, UNAM.GetSize());

    if(NAM1.IsLoaded())
        SaveHandler.writeSubRecord('1MAN', NAM1.value, NAM1.GetSize());

    if(NAM2.IsLoaded())
        SaveHandler.writeSubRecord('2MAN', NAM2.value, NAM2.GetSize());

    if(WNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANW', WNAM.value, WNAM.GetSize());

    if(XNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANX', XNAM.value, XNAM.GetSize());

    if(YNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANY', YNAM.value, YNAM.GetSize());

    if(NAM4.IsLoaded())
        SaveHandler.writeSubRecord('4MAN', NAM4.value, NAM4.GetSize());

    if(_00_.IsLoaded())
        SaveHandler.writeSubRecord('_00_', _00_.value, _00_.GetSize());

    if(_40_.IsLoaded())
        SaveHandler.writeSubRecord('_04_', _40_.value, _40_.GetSize());

    if(_01_.IsLoaded())
        SaveHandler.writeSubRecord('_10_', _01_.value, _01_.GetSize());

    if(_41_.IsLoaded())
        SaveHandler.writeSubRecord('_14_', _41_.value, _41_.GetSize());

    if(_02_.IsLoaded())
        SaveHandler.writeSubRecord('_20_', _02_.value, _02_.GetSize());

    if(_42_.IsLoaded())
        SaveHandler.writeSubRecord('_24_', _42_.value, _42_.GetSize());

    if(_03_.IsLoaded())
        SaveHandler.writeSubRecord('_30_', _03_.value, _03_.GetSize());

    if(_43_.IsLoaded())
        SaveHandler.writeSubRecord('_34_', _43_.value, _43_.GetSize());

    if(_04_.IsLoaded())
        SaveHandler.writeSubRecord('_40_', _04_.value, _04_.GetSize());

    if(_44_.IsLoaded())
        SaveHandler.writeSubRecord('_44_', _44_.value, _44_.GetSize());

    if(_05_.IsLoaded())
        SaveHandler.writeSubRecord('_50_', _05_.value, _05_.GetSize());

    if(_45_.IsLoaded())
        SaveHandler.writeSubRecord('_54_', _45_.value, _45_.GetSize());

    if(_06_.IsLoaded())
        SaveHandler.writeSubRecord('_60_', _06_.value, _06_.GetSize());

    if(_46_.IsLoaded())
        SaveHandler.writeSubRecord('_64_', _46_.value, _46_.GetSize());

    if(_07_.IsLoaded())
        SaveHandler.writeSubRecord('_70_', _07_.value, _07_.GetSize());

    if(_47_.IsLoaded())
        SaveHandler.writeSubRecord('_74_', _47_.value, _47_.GetSize());

    if(_08_.IsLoaded())
        SaveHandler.writeSubRecord('_80_', _08_.value, _08_.GetSize());

    if(_48_.IsLoaded())
        SaveHandler.writeSubRecord('_84_', _48_.value, _48_.GetSize());

    if(_09_.IsLoaded())
        SaveHandler.writeSubRecord('_90_', _09_.value, _09_.GetSize());

    if(_49_.IsLoaded())
        SaveHandler.writeSubRecord('_94_', _49_.value, _49_.GetSize());

    if(_0A_.IsLoaded())
        SaveHandler.writeSubRecord('_A0_', _0A_.value, _0A_.GetSize());

    if(_4A_.IsLoaded())
        SaveHandler.writeSubRecord('_A4_', _4A_.value, _4A_.GetSize());

    if(_0B_.IsLoaded())
        SaveHandler.writeSubRecord('_B0_', _0B_.value, _0B_.GetSize());

    if(_4B_.IsLoaded())
        SaveHandler.writeSubRecord('_B4_', _4B_.value, _4B_.GetSize());

    if(_0C_.IsLoaded())
        SaveHandler.writeSubRecord('_C0_', _0C_.value, _0C_.GetSize());

    if(_4C_.IsLoaded())
        SaveHandler.writeSubRecord('_C4_', _4C_.value, _4C_.GetSize());

    if(_0D_.IsLoaded())
        SaveHandler.writeSubRecord('_D0_', _0D_.value, _0D_.GetSize());

    if(_4D_.IsLoaded())
        SaveHandler.writeSubRecord('_D4_', _4D_.value, _4D_.GetSize());

    if(_0E_.IsLoaded())
        SaveHandler.writeSubRecord('_E0_', _0E_.value, _0E_.GetSize());

    if(_4E_.IsLoaded())
        SaveHandler.writeSubRecord('_E4_', _4E_.value, _4E_.GetSize());

    if(_0F_.IsLoaded())
        SaveHandler.writeSubRecord('_F0_', _0F_.value, _0F_.GetSize());

    if(_4F_.IsLoaded())
        SaveHandler.writeSubRecord('_F4_', _4F_.value, _4F_.GetSize());

    if(_10_.IsLoaded())
        SaveHandler.writeSubRecord('_01_', _10_.value, _10_.GetSize());

    if(_50_.IsLoaded())
        SaveHandler.writeSubRecord('_05_', _50_.value, _50_.GetSize());

    if(_11_.IsLoaded())
        SaveHandler.writeSubRecord('_11_', _11_.value, _11_.GetSize());

    if(_51_.IsLoaded())
        SaveHandler.writeSubRecord('_15_', _51_.value, _51_.GetSize());

    if(_12_.IsLoaded())
        SaveHandler.writeSubRecord('_21_', _12_.value, _12_.GetSize());

    if(_52_.IsLoaded())
        SaveHandler.writeSubRecord('_25_', _52_.value, _52_.GetSize());

    if(_13_.IsLoaded())
        SaveHandler.writeSubRecord('_31_', _13_.value, _13_.GetSize());

    if(_53_.IsLoaded())
        SaveHandler.writeSubRecord('_35_', _53_.value, _53_.GetSize());

    if(_14_.IsLoaded())
        SaveHandler.writeSubRecord('_41_', _14_.value, _14_.GetSize());

    if(_54_.IsLoaded())
        SaveHandler.writeSubRecord('_45_', _54_.value, _54_.GetSize());

    if(RDSD.IsLoaded())
        SaveHandler.writeSubRecord('DSDR', RDSD.value, RDSD.GetSize());

    if(RDSI.IsLoaded())
        SaveHandler.writeSubRecord('ISDR', RDSI.value, RDSI.GetSize());

    return -1;
    }

bool IMADRecord::operator ==(const IMADRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DNAM == other.DNAM &&
            BNAM == other.BNAM &&
            VNAM == other.VNAM &&
            TNAM == other.TNAM &&
            NAM3 == other.NAM3 &&
            RNAM == other.RNAM &&
            SNAM == other.SNAM &&
            UNAM == other.UNAM &&
            NAM1 == other.NAM1 &&
            NAM2 == other.NAM2 &&
            WNAM == other.WNAM &&
            XNAM == other.XNAM &&
            YNAM == other.YNAM &&
            NAM4 == other.NAM4 &&
            _00_ == other._00_ &&
            _40_ == other._40_ &&
            _01_ == other._01_ &&
            _41_ == other._41_ &&
            _02_ == other._02_ &&
            _42_ == other._42_ &&
            _03_ == other._03_ &&
            _43_ == other._43_ &&
            _04_ == other._04_ &&
            _44_ == other._44_ &&
            _05_ == other._05_ &&
            _45_ == other._45_ &&
            _06_ == other._06_ &&
            _46_ == other._46_ &&
            _07_ == other._07_ &&
            _47_ == other._47_ &&
            _08_ == other._08_ &&
            _48_ == other._48_ &&
            _09_ == other._09_ &&
            _49_ == other._49_ &&
            _0A_ == other._0A_ &&
            _4A_ == other._4A_ &&
            _0B_ == other._0B_ &&
            _4B_ == other._4B_ &&
            _0C_ == other._0C_ &&
            _4C_ == other._4C_ &&
            _0D_ == other._0D_ &&
            _4D_ == other._4D_ &&
            _0E_ == other._0E_ &&
            _4E_ == other._4E_ &&
            _0F_ == other._0F_ &&
            _4F_ == other._4F_ &&
            _10_ == other._10_ &&
            _50_ == other._50_ &&
            _11_ == other._11_ &&
            _51_ == other._51_ &&
            _12_ == other._12_ &&
            _52_ == other._52_ &&
            _13_ == other._13_ &&
            _53_ == other._53_ &&
            _14_ == other._14_ &&
            _54_ == other._54_ &&
            RDSD == other.RDSD &&
            RDSI == other.RDSI);
    }

bool IMADRecord::operator !=(const IMADRecord &other) const
    {
    return !(*this == other);
    }
}