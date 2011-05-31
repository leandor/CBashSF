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
#include "CONTRecord.h"

CONTRecord::CONTDATA::CONTDATA():
    flags(0),
    weight(0.0f)
    {
    //
    }

CONTRecord::CONTDATA::~CONTDATA()
    {
    //
    }

bool CONTRecord::CONTDATA::operator ==(const CONTDATA &other) const
    {
    return (flags == other.flags &&
            AlmostEqual(weight,other.weight,2));
    }

bool CONTRecord::CONTDATA::operator !=(const CONTDATA &other) const
    {
    return !(*this == other);
    }

CONTRecord::CONTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CONTRecord::CONTRecord(CONTRecord *srcRecord):
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

    CNTO.resize(srcRecord->CNTO.size());
    for(UINT32 x = 0; x < srcRecord->CNTO.size(); x++)
        {
        CNTO[x] = new ReqSubRecord<GENCNTO>;
        *CNTO[x] = *srcRecord->CNTO[x];
        }

    DATA = srcRecord->DATA;
    SNAM = srcRecord->SNAM;
    QNAM = srcRecord->QNAM;
    return;
    }

CONTRecord::~CONTRecord()
    {
    for(UINT32 x = 0; x < CNTO.size(); ++x)
        delete CNTO[x];
    }

bool CONTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(UINT32 x = 0; x < CNTO.size(); x++)
        op.Accept(CNTO[x]->value.item);
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(QNAM.IsLoaded())
        op.Accept(QNAM.value);

    return op.Stop();
    }

bool CONTRecord::IsRespawn()
    {
    return (DATA.value.flags & fIsRespawn) != 0;
    }

void CONTRecord::IsRespawn(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsRespawn) : (DATA.value.flags & ~fIsRespawn);
    }

bool CONTRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void CONTRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 CONTRecord::GetType()
    {
    return REV32(CONT);
    }

STRING CONTRecord::GetStrType()
    {
    return "CONT";
    }

SINT32 CONTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    UINT32 curPos = 0;
    ReqSubRecord<GENCNTO> *newCNTO = NULL;
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, curPos);
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize, curPos);
                break;
            case REV32(CNTO):
                newCNTO = new ReqSubRecord<GENCNTO>;
                newCNTO->Read(buffer, subSize, curPos);
                CNTO.push_back(newCNTO);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(QNAM):
                QNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CONT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CONTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();

    for(UINT32 x = 0; x < CNTO.size(); x++)
        delete CNTO[x];
    CNTO.clear();

    DATA.Unload();
    SNAM.Unload();
    QNAM.Unload();
    return 1;
    }

SINT32 CONTRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        writer.record_write_subrecord(REV32(FULL), FULL.value, FULL.GetSize());
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        writer.record_write_subrecord(REV32(MODL), MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            writer.record_write_subrecord(REV32(MODB), &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            writer.record_write_subrecord(REV32(MODT), MODL->MODT.value, MODL->MODT.GetSize());
        }
    if(SCRI.IsLoaded())
        writer.record_write_subrecord(REV32(SCRI), &SCRI.value, SCRI.GetSize());
    if(CNTO.size())
        for(UINT32 p = 0; p < CNTO.size(); p++)
            if(CNTO[p]->IsLoaded())
                writer.record_write_subrecord(REV32(CNTO), &CNTO[p]->value, sizeof(GENCNTO));
    if(DATA.IsLoaded())
        writer.record_write_subrecord(REV32(DATA), &DATA.value, DATA.GetSize());
    if(SNAM.IsLoaded())
        writer.record_write_subrecord(REV32(SNAM), &SNAM.value, SNAM.GetSize());
    if(QNAM.IsLoaded())
        writer.record_write_subrecord(REV32(QNAM), &QNAM.value, QNAM.GetSize());
    return -1;
    }

bool CONTRecord::operator ==(const CONTRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        FULL.equals(other.FULL) &&
        MODL == other.MODL &&
        SCRI == other.SCRI &&
        DATA == other.DATA &&
        SNAM == other.SNAM &&
        QNAM == other.QNAM &&
        CNTO.size() == other.CNTO.size())
        {
        //Record order doesn't matter on items, so equality testing isn't easy
        //The proper solution would be to check each item against every other item to see if there's a one-to-one match
        //Fix-up later
        for(UINT32 x = 0; x < CNTO.size(); ++x)
            if(*CNTO[x] != *other.CNTO[x])
                return false;
        return true;
        }

    return false;
    }

bool CONTRecord::operator !=(const CONTRecord &other) const
    {
    return !(*this == other);
    }