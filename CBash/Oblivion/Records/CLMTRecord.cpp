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
#include "CLMTRecord.h"
#include <vector>

CLMTRecord::CLMTWLST::CLMTWLST():
    weather(0),
    chance(0)
    {
    //
    }

CLMTRecord::CLMTWLST::~CLMTWLST()
    {
    //
    }

bool CLMTRecord::CLMTWLST::operator ==(const CLMTWLST &other) const
    {
    return (weather == other.weather &&
            chance == other.chance);
    }

bool CLMTRecord::CLMTWLST::operator !=(const CLMTWLST &other) const
    {
    return !(*this == other);
    }

CLMTRecord::CLMTTNAM::CLMTTNAM():
    riseBegin(0),
    riseEnd(0),
    setBegin(0),
    setEnd(0),
    volatility(0),
    phaseLength(0)
    {
    //
    }

CLMTRecord::CLMTTNAM::~CLMTTNAM()
    {
    //
    }

bool CLMTRecord::CLMTTNAM::operator ==(const CLMTTNAM &other) const
    {
    return (riseBegin == other.riseBegin &&
            riseEnd == other.riseEnd &&
            setBegin == other.setBegin &&
            setEnd == other.setEnd &&
            volatility == other.volatility &&
            phaseLength == other.phaseLength);
    }

bool CLMTRecord::CLMTTNAM::operator !=(const CLMTTNAM &other) const
    {
    return !(*this == other);
    }

CLMTRecord::CLMTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CLMTRecord::CLMTRecord(CLMTRecord *srcRecord):
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
    Weathers = srcRecord->Weathers;
    FNAM = srcRecord->FNAM;
    GNAM = srcRecord->GNAM;
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODB = srcRecord->MODL->MODB;
        MODL->MODL = srcRecord->MODL->MODL;
        MODL->MODT = srcRecord->MODL->MODT;
        }
    TNAM = srcRecord->TNAM;
    return;
    }

CLMTRecord::~CLMTRecord()
    {
    //
    }

bool CLMTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < Weathers.size(); x++)
        op.Accept(Weathers[x].weather);

    return op.Stop();
    }

UINT32 CLMTRecord::GetType()
    {
    return REV32(CLMT);
    }

STRING CLMTRecord::GetStrType()
    {
    return "CLMT";
    }

SINT32 CLMTRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(WLST):
                if(subSize % sizeof(CLMTWLST) == 0)
                    {
                    if(subSize == 0)
                        break;
                    Weathers.resize(subSize / sizeof(CLMTWLST));
                    _readBuffer(&Weathers[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized Weathers size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize, curPos);
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
            case REV32(TNAM):
                TNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CLMT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

SINT32 CLMTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    Weathers.clear();
    FNAM.Unload();
    GNAM.Unload();
    MODL.Unload();
    TNAM.Unload();
    return 1;
    }

SINT32 CLMTRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord(REV32(EDID), EDID.value, EDID.GetSize());
    if(Weathers.size())
        writer.record_write_subrecord(REV32(WLST), &Weathers[0], (UINT32)Weathers.size() * sizeof(CLMTWLST));
    //else
    //    writer.record_write_subheader(REV32(WLST), 0);

    if(FNAM.IsLoaded())
        writer.record_write_subrecord(REV32(FNAM), FNAM.value, FNAM.GetSize());
    if(GNAM.IsLoaded())
        writer.record_write_subrecord(REV32(GNAM), GNAM.value, GNAM.GetSize());

    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        writer.record_write_subrecord(REV32(MODL), MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            writer.record_write_subrecord(REV32(MODB), &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            writer.record_write_subrecord(REV32(MODT), MODL->MODT.value, MODL->MODT.GetSize());
        }

    if(TNAM.IsLoaded())
        writer.record_write_subrecord(REV32(TNAM), &TNAM.value, TNAM.GetSize());
    return -1;
    }

bool CLMTRecord::operator ==(const CLMTRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        FNAM.equalsi(other.FNAM) &&
        GNAM.equalsi(other.GNAM) &&
        MODL == other.MODL &&
        TNAM == other.TNAM &&
        Weathers.size() == other.Weathers.size())
        {
        //Not sure if record order matters on weathers, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < Weathers.size(); ++x)
            if(Weathers[x] != other.Weathers[x])
                return false;
        return true;
        }

    return false;
    }

bool CLMTRecord::operator !=(const CLMTRecord &other) const
    {
    return !(*this == other);
    }