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
#include "DOORRecord.h"
#include <vector>

DOORRecord::DOORRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

DOORRecord::DOORRecord(DOORRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODT = srcRecord->MODL->MODT;
        }
    SCRI = srcRecord->SCRI;
    SNAM = srcRecord->SNAM;
    ANAM = srcRecord->ANAM;
    BNAM = srcRecord->BNAM;
    FNAM = srcRecord->FNAM;
    TNAM.resize(srcRecord->TNAM.size());
    for(UINT32 x = 0; x < srcRecord->TNAM.size(); x++)
        TNAM[x] = srcRecord->TNAM[x];
    return;
    }

DOORRecord::~DOORRecord()
    {
    //
    }

bool DOORRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(ANAM.IsLoaded())
        op.Accept(ANAM.value);
    if(BNAM.IsLoaded())
        op.Accept(BNAM.value);
    for(UINT32 x = 0; x < TNAM.size(); x++)
        op.Accept(TNAM[x]);

    return op.Stop();
    }

bool DOORRecord::IsOblivionGate()
    {
    return (FNAM.value & fIsOblivionGate) != 0;
    }

void DOORRecord::IsOblivionGate(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsOblivionGate) : (FNAM.value & ~fIsOblivionGate);
    }

bool DOORRecord::IsAutomatic()
    {
    return (FNAM.value & fIsAutomatic) != 0;
    }

void DOORRecord::IsAutomatic(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsAutomatic) : (FNAM.value & ~fIsAutomatic);
    }

bool DOORRecord::IsHidden()
    {
    return (FNAM.value & fIsHidden) != 0;
    }

void DOORRecord::IsHidden(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsHidden) : (FNAM.value & ~fIsHidden);
    }

bool DOORRecord::IsMinimalUse()
    {
    return (FNAM.value & fIsMinimalUse) != 0;
    }

void DOORRecord::IsMinimalUse(bool value)
    {
    FNAM.value = value ? (FNAM.value | fIsMinimalUse) : (FNAM.value & ~fIsMinimalUse);
    }

bool DOORRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((FNAM.value & Mask) == Mask) : ((FNAM.value & Mask) != 0);
    }

void DOORRecord::SetFlagMask(UINT8 Mask)
    {
    FNAM.value = Mask;
    }

UINT32 DOORRecord::GetType()
    {
    return 'ROOD';
    }

STRING DOORRecord::GetStrType()
    {
    return "DOOR";
    }

SINT32 DOORRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    FORMID curFormID = 0;
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
            case 'IRCS':
                SCRI.Read(buffer, subSize, curPos);
                break;
            case 'MANS':
                SNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANA':
                ANAM.Read(buffer, subSize, curPos);
                break;
            case 'MANB':
                BNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANF':
                FNAM.Read(buffer, subSize, curPos);
                break;
            case 'MANT':
                _readBuffer(&curFormID, buffer, subSize, curPos);
                TNAM.push_back(curFormID);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  DOOR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 DOORRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    SNAM.Unload();
    ANAM.Unload();
    BNAM.Unload();
    FNAM.Unload();
    TNAM.clear();
    return 1;
    }

SINT32 DOORRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord('DIDE', EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        writer.record_write_subrecord('LLUF', FULL.value, FULL.GetSize());
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        writer.record_write_subrecord('LDOM', MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            writer.record_write_subrecord('BDOM', &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            writer.record_write_subrecord('TDOM', MODL->MODT.value, MODL->MODT.GetSize());
        }
    if(SCRI.IsLoaded())
        writer.record_write_subrecord('IRCS', &SCRI.value, SCRI.GetSize());
    if(SNAM.IsLoaded())
        writer.record_write_subrecord('MANS', &SNAM.value, SNAM.GetSize());
    if(ANAM.IsLoaded())
        writer.record_write_subrecord('MANA', &ANAM.value, ANAM.GetSize());
    if(BNAM.IsLoaded())
        writer.record_write_subrecord('MANB', &BNAM.value, BNAM.GetSize());
    if(FNAM.IsLoaded())
        writer.record_write_subrecord('MANF', &FNAM.value, FNAM.GetSize());
    for(UINT32 p = 0; p < TNAM.size(); p++)
        writer.record_write_subrecord('MANT', &TNAM[p], sizeof(UINT32));
    return -1;
    }

bool DOORRecord::operator ==(const DOORRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        FULL.equals(other.FULL) &&
        MODL == other.MODL &&
        SCRI == other.SCRI &&
        SNAM == other.SNAM &&
        ANAM == other.ANAM &&
        BNAM == other.BNAM &&
        FNAM == other.FNAM &&
        TNAM.size() == other.TNAM.size())
        {
        //Not sure if record order matters on destinations, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < TNAM.size(); ++x)
            if(TNAM[x] != other.TNAM[x])
                return false;
        return true;
        }

    return false;
    }

bool DOORRecord::operator !=(const DOORRecord &other) const
    {
    return !(*this == other);
    }