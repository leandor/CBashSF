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
    FNVRecord(_recData)
    {
    //
    }

IMADRecord::IMADRecord(IMADRecord *srcRecord):
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

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

UINT32 IMADRecord::GetType()
    {
    return REV32(IMAD);
    }

STRING IMADRecord::GetStrType()
    {
    return "IMAD";
    }

SINT32 IMADRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize);
                break;
            case REV32(VNAM):
                VNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            case REV32(NAM3):
                NAM3.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(UNAM):
                UNAM.Read(buffer, subSize);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize);
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize);
                break;
            case REV32(_00_):
                _00_.Read(buffer, subSize);
                break;
            case REV32(_40_):
                _40_.Read(buffer, subSize);
                break;
            case REV32(_01_):
                _01_.Read(buffer, subSize);
                break;
            case REV32(_41_):
                _41_.Read(buffer, subSize);
                break;
            case REV32(_02_):
                _02_.Read(buffer, subSize);
                break;
            case REV32(_42_):
                _42_.Read(buffer, subSize);
                break;
            case REV32(_03_):
                _03_.Read(buffer, subSize);
                break;
            case REV32(_43_):
                _43_.Read(buffer, subSize);
                break;
            case REV32(_04_):
                _04_.Read(buffer, subSize);
                break;
            case REV32(_44_):
                _44_.Read(buffer, subSize);
                break;
            case REV32(_05_):
                _05_.Read(buffer, subSize);
                break;
            case REV32(_45_):
                _45_.Read(buffer, subSize);
                break;
            case REV32(_06_):
                _06_.Read(buffer, subSize);
                break;
            case REV32(_46_):
                _46_.Read(buffer, subSize);
                break;
            case REV32(_07_):
                _07_.Read(buffer, subSize);
                break;
            case REV32(_47_):
                _47_.Read(buffer, subSize);
                break;
            case REV32(_08_):
                _08_.Read(buffer, subSize);
                break;
            case REV32(_48_):
                _48_.Read(buffer, subSize);
                break;
            case REV32(_09_):
                _09_.Read(buffer, subSize);
                break;
            case REV32(_49_):
                _49_.Read(buffer, subSize);
                break;
            case REV32(_0A_):
                _0A_.Read(buffer, subSize);
                break;
            case REV32(_4A_):
                _4A_.Read(buffer, subSize);
                break;
            case REV32(_0B_):
                _0B_.Read(buffer, subSize);
                break;
            case REV32(_4B_):
                _4B_.Read(buffer, subSize);
                break;
            case REV32(_0C_):
                _0C_.Read(buffer, subSize);
                break;
            case REV32(_4C_):
                _4C_.Read(buffer, subSize);
                break;
            case REV32(_0D_):
                _0D_.Read(buffer, subSize);
                break;
            case REV32(_4D_):
                _4D_.Read(buffer, subSize);
                break;
            case REV32(_0E_):
                _0E_.Read(buffer, subSize);
                break;
            case REV32(_4E_):
                _4E_.Read(buffer, subSize);
                break;
            case REV32(_0F_):
                _0F_.Read(buffer, subSize);
                break;
            case REV32(_4F_):
                _4F_.Read(buffer, subSize);
                break;
            case REV32(_10_):
                _10_.Read(buffer, subSize);
                break;
            case REV32(_50_):
                _50_.Read(buffer, subSize);
                break;
            case REV32(_11_):
                _11_.Read(buffer, subSize);
                break;
            case REV32(_51_):
                _51_.Read(buffer, subSize);
                break;
            case REV32(_12_):
                _12_.Read(buffer, subSize);
                break;
            case REV32(_52_):
                _52_.Read(buffer, subSize);
                break;
            case REV32(_13_):
                _13_.Read(buffer, subSize);
                break;
            case REV32(_53_):
                _53_.Read(buffer, subSize);
                break;
            case REV32(_14_):
                _14_.Read(buffer, subSize);
                break;
            case REV32(_54_):
                _54_.Read(buffer, subSize);
                break;
            case REV32(RDSD):
                RDSD.Read(buffer, subSize);
                break;
            case REV32(RDSI):
                RDSI.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IMAD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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

SINT32 IMADRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DNAM);
    WRITE(BNAM);
    WRITE(VNAM);
    WRITE(TNAM);
    WRITE(NAM3);
    WRITE(RNAM);
    WRITE(SNAM);
    WRITE(UNAM);
    WRITE(NAM1);
    WRITE(NAM2);
    WRITE(WNAM);
    WRITE(XNAM);
    WRITE(YNAM);
    WRITE(NAM4);
    WRITE(_00_);
    WRITE(_40_);
    WRITE(_01_);
    WRITE(_41_);
    WRITE(_02_);
    WRITE(_42_);
    WRITE(_03_);
    WRITE(_43_);
    WRITE(_04_);
    WRITE(_44_);
    WRITE(_05_);
    WRITE(_45_);
    WRITE(_06_);
    WRITE(_46_);
    WRITE(_07_);
    WRITE(_47_);
    WRITE(_08_);
    WRITE(_48_);
    WRITE(_09_);
    WRITE(_49_);
    WRITE(_0A_);
    WRITE(_4A_);
    WRITE(_0B_);
    WRITE(_4B_);
    WRITE(_0C_);
    WRITE(_4C_);
    WRITE(_0D_);
    WRITE(_4D_);
    WRITE(_0E_);
    WRITE(_4E_);
    WRITE(_0F_);
    WRITE(_4F_);
    WRITE(_10_);
    WRITE(_50_);
    WRITE(_11_);
    WRITE(_51_);
    WRITE(_12_);
    WRITE(_52_);
    WRITE(_13_);
    WRITE(_53_);
    WRITE(_14_);
    WRITE(_54_);
    WRITE(RDSD);
    WRITE(RDSI);

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

bool IMADRecord::equals(const Record *other) const
    {
    return *this == *(IMADRecord *)other;
    }
}