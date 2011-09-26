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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
#include "..\..\Common.h"
#include "ASPCRecord.h"

namespace FNV
{
ASPCRecord::ASPCRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ASPCRecord::ASPCRecord(ASPCRecord *srcRecord):
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
    OBND = srcRecord->OBND;
    DawnSNAM = srcRecord->DawnSNAM;
    AfternoonSNAM = srcRecord->AfternoonSNAM;
    DuskSNAM = srcRecord->DuskSNAM;
    NightSNAM = srcRecord->NightSNAM;
    WallaSNAM = srcRecord->WallaSNAM;
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

    op.Accept(DawnSNAM.value);
    op.Accept(AfternoonSNAM.value);
    op.Accept(DuskSNAM.value);
    op.Accept(NightSNAM.value);
    op.Accept(WallaSNAM.value);

    if(RDAT.IsLoaded())
        op.Accept(RDAT.value);

    return op.Stop();
    }

bool ASPCRecord::IsEnvironmentNone()
    {
    return (ANAM.value == eNone);
    }

void ASPCRecord::IsEnvironmentNone(bool value)
    {
    ANAM.value = value ? eNone : eDefault;
    }

bool ASPCRecord::IsEnvironmentDefault()
    {
    return (ANAM.value == eDefault);
    }

void ASPCRecord::IsEnvironmentDefault(bool value)
    {
    ANAM.value = value ? eDefault : eNone;
    }

bool ASPCRecord::IsEnvironmentGeneric()
    {
    return (ANAM.value == eGeneric);
    }

void ASPCRecord::IsEnvironmentGeneric(bool value)
    {
    ANAM.value = value ? eGeneric : eDefault;
    }

bool ASPCRecord::IsEnvironmentPaddedCell()
    {
    return (ANAM.value == ePaddedCell);
    }

void ASPCRecord::IsEnvironmentPaddedCell(bool value)
    {
    ANAM.value = value ? ePaddedCell : eDefault;
    }

bool ASPCRecord::IsEnvironmentRoom()
    {
    return (ANAM.value == eRoom);
    }

void ASPCRecord::IsEnvironmentRoom(bool value)
    {
    ANAM.value = value ? eRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentBathroom()
    {
    return (ANAM.value == eBathroom);
    }

void ASPCRecord::IsEnvironmentBathroom(bool value)
    {
    ANAM.value = value ? eBathroom : eDefault;
    }

bool ASPCRecord::IsEnvironmentLivingroom()
    {
    return (ANAM.value == eLivingroom);
    }

void ASPCRecord::IsEnvironmentLivingroom(bool value)
    {
    ANAM.value = value ? eLivingroom : eDefault;
    }

bool ASPCRecord::IsEnvironmentStoneRoom()
    {
    return (ANAM.value == eStoneRoom);
    }

void ASPCRecord::IsEnvironmentStoneRoom(bool value)
    {
    ANAM.value = value ? eStoneRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentAuditorium()
    {
    return (ANAM.value == eAuditorium);
    }

void ASPCRecord::IsEnvironmentAuditorium(bool value)
    {
    ANAM.value = value ? eAuditorium : eDefault;
    }

bool ASPCRecord::IsEnvironmentConcerthall()
    {
    return (ANAM.value == eConcerthall);
    }

void ASPCRecord::IsEnvironmentConcerthall(bool value)
    {
    ANAM.value = value ? eConcerthall : eDefault;
    }

bool ASPCRecord::IsEnvironmentCave()
    {
    return (ANAM.value == eCave);
    }

void ASPCRecord::IsEnvironmentCave(bool value)
    {
    ANAM.value = value ? eCave : eDefault;
    }

bool ASPCRecord::IsEnvironmentArena()
    {
    return (ANAM.value == eArena);
    }

void ASPCRecord::IsEnvironmentArena(bool value)
    {
    ANAM.value = value ? eArena : eDefault;
    }

bool ASPCRecord::IsEnvironmentHangar()
    {
    return (ANAM.value == eHangar);
    }

void ASPCRecord::IsEnvironmentHangar(bool value)
    {
    ANAM.value = value ? eHangar : eDefault;
    }

bool ASPCRecord::IsEnvironmentCarpetedHallway()
    {
    return (ANAM.value == eCarpetedHallway);
    }

void ASPCRecord::IsEnvironmentCarpetedHallway(bool value)
    {
    ANAM.value = value ? eCarpetedHallway : eDefault;
    }

bool ASPCRecord::IsEnvironmentHallway()
    {
    return (ANAM.value == eHallway);
    }

void ASPCRecord::IsEnvironmentHallway(bool value)
    {
    ANAM.value = value ? eHallway : eDefault;
    }

bool ASPCRecord::IsEnvironmentStoneCorridor()
    {
    return (ANAM.value == eStoneCorridor);
    }

void ASPCRecord::IsEnvironmentStoneCorridor(bool value)
    {
    ANAM.value = value ? eStoneCorridor : eDefault;
    }

bool ASPCRecord::IsEnvironmentAlley()
    {
    return (ANAM.value == eAlley);
    }

void ASPCRecord::IsEnvironmentAlley(bool value)
    {
    ANAM.value = value ? eAlley : eDefault;
    }

bool ASPCRecord::IsEnvironmentForest()
    {
    return (ANAM.value == eForest);
    }

void ASPCRecord::IsEnvironmentForest(bool value)
    {
    ANAM.value = value ? eForest : eDefault;
    }

bool ASPCRecord::IsEnvironmentCity()
    {
    return (ANAM.value == eCity);
    }

void ASPCRecord::IsEnvironmentCity(bool value)
    {
    ANAM.value = value ? eCity : eDefault;
    }

bool ASPCRecord::IsEnvironmentMountains()
    {
    return (ANAM.value == eMountains);
    }

void ASPCRecord::IsEnvironmentMountains(bool value)
    {
    ANAM.value = value ? eMountains : eDefault;
    }

bool ASPCRecord::IsEnvironmentQuarry()
    {
    return (ANAM.value == eQuarry);
    }

void ASPCRecord::IsEnvironmentQuarry(bool value)
    {
    ANAM.value = value ? eQuarry : eDefault;
    }

bool ASPCRecord::IsEnvironmentPlain()
    {
    return (ANAM.value == ePlain);
    }

void ASPCRecord::IsEnvironmentPlain(bool value)
    {
    ANAM.value = value ? ePlain : eDefault;
    }

bool ASPCRecord::IsEnvironmentParkinglot()
    {
    return (ANAM.value == eParkinglot);
    }

void ASPCRecord::IsEnvironmentParkinglot(bool value)
    {
    ANAM.value = value ? eParkinglot : eDefault;
    }

bool ASPCRecord::IsEnvironmentSewerpipe()
    {
    return (ANAM.value == eSewerpipe);
    }

void ASPCRecord::IsEnvironmentSewerpipe(bool value)
    {
    ANAM.value = value ? eSewerpipe : eDefault;
    }

bool ASPCRecord::IsEnvironmentUnderwater()
    {
    return (ANAM.value == eUnderwater);
    }

void ASPCRecord::IsEnvironmentUnderwater(bool value)
    {
    ANAM.value = value ? eUnderwater : eDefault;
    }

bool ASPCRecord::IsEnvironmentSmallRoom()
    {
    return (ANAM.value == eSmallRoom);
    }

void ASPCRecord::IsEnvironmentSmallRoom(bool value)
    {
    ANAM.value = value ? eSmallRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentMediumRoom()
    {
    return (ANAM.value == eMediumRoom);
    }

void ASPCRecord::IsEnvironmentMediumRoom(bool value)
    {
    ANAM.value = value ? eMediumRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentLargeRoom()
    {
    return (ANAM.value == eLargeRoom);
    }

void ASPCRecord::IsEnvironmentLargeRoom(bool value)
    {
    ANAM.value = value ? eLargeRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentMediumHall()
    {
    return (ANAM.value == eMediumHall);
    }

void ASPCRecord::IsEnvironmentMediumHall(bool value)
    {
    ANAM.value = value ? eMediumHall : eDefault;
    }

bool ASPCRecord::IsEnvironmentLargeHall()
    {
    return (ANAM.value == eLargeHall);
    }

void ASPCRecord::IsEnvironmentLargeHall(bool value)
    {
    ANAM.value = value ? eLargeHall : eDefault;
    }

bool ASPCRecord::IsEnvironmentPlate()
    {
    return (ANAM.value == ePlate);
    }

void ASPCRecord::IsEnvironmentPlate(bool value)
    {
    ANAM.value = value ? ePlate : eDefault;
    }

bool ASPCRecord::IsEnvironmentType(UINT32 Type)
    {
    return ANAM.value == Type;
    }

void ASPCRecord::SetEnvironmentType(UINT32 Type)
    {
    ANAM.value = Type;
    }

bool ASPCRecord::IsSpaceExterior()
    {
    return (INAM.value == eIsExterior);
    }

void ASPCRecord::IsSpaceExterior(bool value)
    {
    INAM.value = value ? eIsExterior : eIsInterior;
    }

bool ASPCRecord::IsSpaceInterior()
    {
    return (INAM.value == eIsInterior);
    }

void ASPCRecord::IsSpaceInterior(bool value)
    {
    INAM.value = value ? eIsInterior : eIsExterior;
    }

bool ASPCRecord::IsSpaceType(UINT32 Type)
    {
    return INAM.value == Type;
    }

void ASPCRecord::SetSpaceType(UINT32 Type)
    {
    INAM.value = Type;
    }

UINT32 ASPCRecord::GetType()
    {
    return REV32(ASPC);
    }

STRING ASPCRecord::GetStrType()
    {
    return "ASPC";
    }

SINT32 ASPCRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curSNAM = 0;
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
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                switch(curSNAM)
                    {
                    case 0:
                        DawnSNAM.Read(buffer, subSize);
                        break;
                    case 1:
                        AfternoonSNAM.Read(buffer, subSize);
                        break;
                    case 2:
                        DuskSNAM.Read(buffer, subSize);
                        break;
                    case 3:
                        NightSNAM.Read(buffer, subSize);
                        break;
                    case 4:
                        WallaSNAM.Read(buffer, subSize);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  ASPC: %08X - Unexpected SNAM\n", formID);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                ++curSNAM;
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(RDAT):
                RDAT.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ASPC: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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
    DawnSNAM.Unload();
    AfternoonSNAM.Unload();
    DuskSNAM.Unload();
    NightSNAM.Unload();
    WallaSNAM.Unload();
    WNAM.Unload();
    RDAT.Unload();
    ANAM.Unload();
    INAM.Unload();
    return 1;
    }

SINT32 ASPCRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITEAS(DawnSNAM,SNAM);
    WRITEAS(AfternoonSNAM,SNAM);
    WRITEAS(DuskSNAM,SNAM);
    WRITEAS(NightSNAM,SNAM);
    WRITEAS(WallaSNAM,SNAM);
    WRITE(WNAM);
    WRITE(RDAT);
    WRITE(ANAM);
    WRITE(INAM);
    return -1;
    }

bool ASPCRecord::operator ==(const ASPCRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            DawnSNAM == other.DawnSNAM &&
            AfternoonSNAM == other.AfternoonSNAM &&
            DuskSNAM == other.DuskSNAM &&
            NightSNAM == other.NightSNAM &&
            WallaSNAM == other.WallaSNAM &&
            WNAM == other.WNAM &&
            RDAT == other.RDAT &&
            ANAM == other.ANAM &&
            INAM == other.INAM);
    }

bool ASPCRecord::operator !=(const ASPCRecord &other) const
    {
    return !(*this == other);
    }

bool ASPCRecord::equals(Record *other)
    {
    return *this == *(ASPCRecord *)other;
    }
}