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
#include "IDLERecord.h"

namespace FNV
{
IDLERecord::IDLERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IDLERecord::IDLERecord(IDLERecord *srcRecord):
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

    MODL = srcRecord->MODL;

    CTDA = srcRecord->CTDA;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    return;
    }

IDLERecord::~IDLERecord()
    {
    //
    }

bool IDLERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    //if(ANAM.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(ANAM->value);

    return op.Stop();
    }

bool IDLERecord::IsNoAttacking()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoAttacking) != 0;
    }

void IDLERecord::IsNoAttacking(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoAttacking) : (Dummy->flags & ~fIsNoAttacking);
    }

bool IDLERecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void IDLERecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 IDLERecord::GetType()
    {
    return REV32(IDLE);
    }

STRING IDLERecord::GetStrType()
    {
    return "IDLE";
    }

SINT32 IDLERecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType, buffer, 4, curPos);
        switch(subType)
            {
            case REV32(XXXX):
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
            case REV32(EDID):
                EDID.Read(buffer, subSize, curPos);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize, curPos);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize, curPos);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize, curPos);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IDLE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 IDLERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    CTDA.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 IDLERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);

    MODL.Write(writer);

    WRITE(CTDA);
    WRITE(ANAM);
    WRITE(DATA);

    return -1;
    }

bool IDLERecord::operator ==(const IDLERecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            CTDA == other.CTDA &&
            ANAM == other.ANAM &&
            DATA == other.DATA);
    }

bool IDLERecord::operator !=(const IDLERecord &other) const
    {
    return !(*this == other);
    }
}