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
#include "MESGRecord.h"

namespace FNV
{
MESGRecord::MESGRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

MESGRecord::MESGRecord(MESGRecord *srcRecord):
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
    DESC = srcRecord->DESC;
    FULL = srcRecord->FULL;
    INAM = srcRecord->INAM;
    NAM0 = srcRecord->NAM0;
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    NAM3 = srcRecord->NAM3;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    NAM6 = srcRecord->NAM6;
    NAM7 = srcRecord->NAM7;
    NAM8 = srcRecord->NAM8;
    NAM9 = srcRecord->NAM9;
    DNAM = srcRecord->DNAM;
    TNAM = srcRecord->TNAM;
    ITXT = srcRecord->ITXT;
    CTDA = srcRecord->CTDA;
    return;
    }

MESGRecord::~MESGRecord()
    {
    //
    }

bool MESGRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(INAM.IsLoaded())
        op.Accept(INAM->value);
    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);

    return op.Stop();
    }

UINT32 MESGRecord::GetType()
    {
    return REV32(MESG);
    }

STRING MESGRecord::GetStrType()
    {
    return "MESG";
    }

SINT32 MESGRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(NAM0):
                //NAM0.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM1):
                //NAM1.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM2):
                //NAM2.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM3):
                //NAM3.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM4):
                //NAM4.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM5):
                //NAM5.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM6):
                //NAM6.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM7):
                //NAM7.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM8):
                //NAM8.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM9):
                //NAM9.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            case REV32(ITXT):
                ITXT.Read(buffer, subSize);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  MESG: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 MESGRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DESC.Unload();
    FULL.Unload();
    INAM.Unload();
    //NAM0.Unload(); //FILL IN MANUALLY
    //NAM1.Unload(); //FILL IN MANUALLY
    //NAM2.Unload(); //FILL IN MANUALLY
    //NAM3.Unload(); //FILL IN MANUALLY
    //NAM4.Unload(); //FILL IN MANUALLY
    //NAM5.Unload(); //FILL IN MANUALLY
    //NAM6.Unload(); //FILL IN MANUALLY
    //NAM7.Unload(); //FILL IN MANUALLY
    //NAM8.Unload(); //FILL IN MANUALLY
    //NAM9.Unload(); //FILL IN MANUALLY
    DNAM.Unload();
    TNAM.Unload();
    ITXT.Unload();
    CTDA.Unload();
    return 1;
    }

SINT32 MESGRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DESC);
    WRITE(FULL);
    WRITE(INAM);

    //if(NAM0.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM0), NAM0.value, NAM0.GetSize());

    //if(NAM1.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM1), NAM1.value, NAM1.GetSize());

    //if(NAM2.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM2), NAM2.value, NAM2.GetSize());

    //if(NAM3.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM3), NAM3.value, NAM3.GetSize());

    //if(NAM4.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM4), NAM4.value, NAM4.GetSize());

    //if(NAM5.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM5), NAM5.value, NAM5.GetSize());

    //if(NAM6.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM6), NAM6.value, NAM6.GetSize());

    //if(NAM7.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM7), NAM7.value, NAM7.GetSize());

    //if(NAM8.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM8), NAM8.value, NAM8.GetSize());

    //if(NAM9.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM9), NAM9.value, NAM9.GetSize());
    WRITE(DNAM);
    WRITE(TNAM);
    WRITE(ITXT);
    WRITE(CTDA);

    return -1;
    }

bool MESGRecord::operator ==(const MESGRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DESC.equals(other.DESC) &&
            FULL.equals(other.FULL) &&
            INAM == other.INAM &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            DNAM == other.DNAM &&
            TNAM == other.TNAM &&
            ITXT.equalsi(other.ITXT) &&
            CTDA == other.CTDA);
    }

bool MESGRecord::operator !=(const MESGRecord &other) const
    {
    return !(*this == other);
    }

bool MESGRecord::equals(const Record *other) const
    {
    return *this == *(MESGRecord *)other;
    }
}