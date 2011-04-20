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
#include "ASPCRecord.h"

namespace FNV
{
ASPCRecord::ASPCRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ASPCRecord::ASPCRecord(ASPCRecord *srcRecord):
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
    SNAM = srcRecord->SNAM;
    WNAM = srcRecord->WNAM;
    RDAT = srcRecord->RDAT;
    ANAM = srcRecord->ANAM;
    INAM = srcRecord->INAM;
    return;
    }

ASPCRecord::~ASPCRecord()
    {
    //
    }

bool ASPCRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SNAM.IsLoaded())
        op.Accept(SNAM->value);
    if(RDAT.IsLoaded())
        op.Accept(RDAT->value);

    return op.Stop();
    }

bool ASPCRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void ASPCRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eNone;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsDefault()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDefault);
    }

void ASPCRecord::IsDefault(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eDefault;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsGeneric()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGeneric);
    }

void ASPCRecord::IsGeneric(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eGeneric;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsPaddedCell()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePaddedCell);
    }

void ASPCRecord::IsPaddedCell(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = ePaddedCell;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsRoom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eRoom);
    }

void ASPCRecord::IsRoom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eRoom;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsBathroom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBathroom);
    }

void ASPCRecord::IsBathroom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eBathroom;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsLivingroom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLivingroom);
    }

void ASPCRecord::IsLivingroom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eLivingroom;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsStoneRoom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStoneRoom);
    }

void ASPCRecord::IsStoneRoom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eStoneRoom;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsAuditorium()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAuditorium);
    }

void ASPCRecord::IsAuditorium(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAuditorium;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsConcerthall()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eConcerthall);
    }

void ASPCRecord::IsConcerthall(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eConcerthall;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsCave()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCave);
    }

void ASPCRecord::IsCave(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCave;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsArena()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eArena);
    }

void ASPCRecord::IsArena(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eArena;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsHangar()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHangar);
    }

void ASPCRecord::IsHangar(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHangar;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsCarpetedHallway()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCarpetedHallway);
    }

void ASPCRecord::IsCarpetedHallway(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCarpetedHallway;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsHallway()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHallway);
    }

void ASPCRecord::IsHallway(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eHallway;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsStoneCorridor()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eStoneCorridor);
    }

void ASPCRecord::IsStoneCorridor(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eStoneCorridor;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsAlley()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAlley);
    }

void ASPCRecord::IsAlley(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eAlley;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsForest()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eForest);
    }

void ASPCRecord::IsForest(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eForest;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsCity()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCity);
    }

void ASPCRecord::IsCity(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eCity;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsMountains()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMountains);
    }

void ASPCRecord::IsMountains(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eMountains;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsQuarry()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eQuarry);
    }

void ASPCRecord::IsQuarry(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eQuarry;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsPlain()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlain);
    }

void ASPCRecord::IsPlain(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = ePlain;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsParkinglot()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eParkinglot);
    }

void ASPCRecord::IsParkinglot(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eParkinglot;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsSewerpipe()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSewerpipe);
    }

void ASPCRecord::IsSewerpipe(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eSewerpipe;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsUnderwater()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eUnderwater);
    }

void ASPCRecord::IsUnderwater(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eUnderwater;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsSmallRoom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSmallRoom);
    }

void ASPCRecord::IsSmallRoom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eSmallRoom;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsMediumRoom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMediumRoom);
    }

void ASPCRecord::IsMediumRoom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eMediumRoom;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsLargeRoom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLargeRoom);
    }

void ASPCRecord::IsLargeRoom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eLargeRoom;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsMediumHall()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMediumHall);
    }

void ASPCRecord::IsMediumHall(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eMediumHall;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsLargeHall()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLargeHall);
    }

void ASPCRecord::IsLargeHall(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eLargeHall;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsPlate()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlate);
    }

void ASPCRecord::IsPlate(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = ePlate;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsnvironmentType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void ASPCRecord::SetEnvironmentType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool ASPCRecord::IsIsExterior()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIsExterior);
    }

void ASPCRecord::IsIsExterior(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eIsExterior;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsIsInterior()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIsInterior);
    }

void ASPCRecord::IsIsInterior(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    if(value)
        Dummy->flags = eIsInterior;
    else
        Dummy->flags = eDummyDefault;
    }

bool ASPCRecord::IsSpaceType(UINT32 Type, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Type) == Mask) : ((Dummy->flags & Type) != 0);
    }

void ASPCRecord::SetSpaceType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 ASPCRecord::GetSize(bool forceCalc)
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

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    if(WNAM.IsLoaded())
        TotSize += WNAM.GetSize() + 6;

    if(RDAT.IsLoaded())
        TotSize += RDAT.GetSize() + 6;

    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;

    if(INAM.IsLoaded())
        TotSize += INAM.GetSize() + 6;

    return TotSize;
    }

UINT32 ASPCRecord::GetType()
    {
    return 'CPSA';
    }

STRING ASPCRecord::GetStrType()
    {
    return "ASPC";
    }

SINT32 ASPCRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANW':
                WNAM.Read(buffer, subSize, curPos);
                break;
            case 'TADR':
                RDAT.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'MANI':
                INAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ASPC: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 ASPCRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    SNAM.Unload();
    WNAM.Unload();
    RDAT.Unload();
    ANAM.Unload();
    INAM.Unload();
    return 1;
    }

SINT32 ASPCRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord('DIDE', EDID.value, EDID.GetSize());

    if(OBND.IsLoaded())
        SaveHandler.writeSubRecord('DNBO', OBND.value, OBND.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANS', SNAM.value, SNAM.GetSize());

    if(WNAM.IsLoaded())
        SaveHandler.writeSubRecord('MANW', WNAM.value, WNAM.GetSize());

    if(RDAT.IsLoaded())
        SaveHandler.writeSubRecord('TADR', RDAT.value, RDAT.GetSize());

    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord('MANA', ANAM.value, ANAM.GetSize());

    if(INAM.IsLoaded())
        SaveHandler.writeSubRecord('MANI', INAM.value, INAM.GetSize());

    return -1;
    }

bool ASPCRecord::operator ==(const ASPCRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            SNAM == other.SNAM &&
            WNAM == other.WNAM &&
            RDAT == other.RDAT &&
            ANAM == other.ANAM &&
            INAM == other.INAM);
    }

bool ASPCRecord::operator !=(const ASPCRecord &other) const
    {
    return !(*this == other);
    }
}