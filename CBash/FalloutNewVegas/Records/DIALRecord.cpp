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
#include "DIALRecord.h"

namespace FNV
{
DIALRecord::DIALRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

DIALRecord::DIALRecord(DIALRecord *srcRecord):
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
    QSTI = srcRecord->QSTI;
    INFC = srcRecord->INFC;
    INFX = srcRecord->INFX;
    QSTR = srcRecord->QSTR;
    FULL = srcRecord->FULL;
    PNAM = srcRecord->PNAM;
    TDUM = srcRecord->TDUM;
    DATA = srcRecord->DATA;
    return;
    }

DIALRecord::~DIALRecord()
    {
    //
    }

bool DIALRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(QSTI.IsLoaded())
        op.Accept(QSTI->value);
    if(INFC.IsLoaded())
        op.Accept(INFC->value);
    if(QSTR.IsLoaded())
        op.Accept(QSTR->value);

    return op.Stop();
    }

bool DIALRecord::IsTopic()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTopic);
    }

void DIALRecord::IsTopic(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTopic : eDummyDefault;
    }

bool DIALRecord::IsConversation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eConversation);
    }

void DIALRecord::IsConversation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eConversation : eDummyDefault;
    }

bool DIALRecord::IsCombat()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCombat);
    }

void DIALRecord::IsCombat(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCombat : eDummyDefault;
    }

bool DIALRecord::IsPersuasion()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePersuasion);
    }

void DIALRecord::IsPersuasion(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePersuasion : eDummyDefault;
    }

bool DIALRecord::IsDetection()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDetection);
    }

void DIALRecord::IsDetection(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDetection : eDummyDefault;
    }

bool DIALRecord::IsService()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eService);
    }

void DIALRecord::IsService(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eService : eDummyDefault;
    }

bool DIALRecord::IsMisc()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMisc);
    }

void DIALRecord::IsMisc(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMisc : eDummyDefault;
    }

bool DIALRecord::IsRadio()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRadio);
    }

void DIALRecord::IsRadio(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eRadio : eDummyDefault;
    }

bool DIALRecord::IsType(UINT8 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void DIALRecord::SetType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool DIALRecord::IsRumors()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRumors) != 0;
    }

void DIALRecord::IsRumors(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRumors) : (Dummy->flags & ~fIsRumors);
    }

bool DIALRecord::IsTopLevel()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTopLevel) != 0;
    }

void DIALRecord::IsTopLevel(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsTopLevel) : (Dummy->flags & ~fIsTopLevel);
    }

bool DIALRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void DIALRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 DIALRecord::GetSize(bool forceCalc)
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

    if(QSTI.IsLoaded())
        TotSize += QSTI.GetSize() + 6;

    if(INFC.IsLoaded())
        TotSize += INFC.GetSize() + 6;

    if(INFX.IsLoaded())
        TotSize += INFX.GetSize() + 6;

    if(QSTR.IsLoaded())
        TotSize += QSTR.GetSize() + 6;

    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;

    if(TDUM.IsLoaded())
        {
        cSize = TDUM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

UINT32 DIALRecord::GetType()
    {
    return 'LAID';
    }

STRING DIALRecord::GetStrType()
    {
    return "DIAL";
    }

SINT32 DIALRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'ITSQ':
                QSTI.Read(buffer, subSize, curPos);
                break;
            case 'CFNI':
                INFC.Read(buffer, subSize, curPos);
                break;
            case 'XFNI':
                INFX.Read(buffer, subSize, curPos);
                break;
            case 'RTSQ':
                QSTR.Read(buffer, subSize, curPos);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'MANP':
                PNAM.Read(buffer, subSize, curPos);
                break;
            case 'MUDT':
                TDUM.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  DIAL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 DIALRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    QSTI.Unload();
    INFC.Unload();
    INFX.Unload();
    QSTR.Unload();
    FULL.Unload();
    PNAM.Unload();
    TDUM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 DIALRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(QSTI.IsLoaded())
        SaveHandler.writeSubRecord('ITSQ', QSTI.value, QSTI.GetSize());

    if(INFC.IsLoaded())
        SaveHandler.writeSubRecord('CFNI', INFC.value, INFC.GetSize());

    if(INFX.IsLoaded())
        SaveHandler.writeSubRecord('XFNI', INFX.value, INFX.GetSize());

    if(QSTR.IsLoaded())
        SaveHandler.writeSubRecord('RTSQ', QSTR.value, QSTR.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord('LLUF', FULL.value, FULL.GetSize());

    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANP', PNAM.value, PNAM.GetSize());

    if(TDUM.IsLoaded())
        SaveHandler.writeSubRecord('MUDT', TDUM.value, TDUM.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord('ATAD', DATA.value, DATA.GetSize());

    return -1;
    }

bool DIALRecord::operator ==(const DIALRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            QSTI == other.QSTI &&
            INFC == other.INFC &&
            INFX == other.INFX &&
            QSTR == other.QSTR &&
            FULL.equals(other.FULL) &&
            PNAM == other.PNAM &&
            TDUM.equalsi(other.TDUM) &&
            DATA == other.DATA);
    }

bool DIALRecord::operator !=(const DIALRecord &other) const
    {
    return !(*this == other);
    }
}