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
#include "CLMTRecord.h"

namespace Ob
{
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

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    Weathers = srcRecord->Weathers;
    FNAM = srcRecord->FNAM;
    GNAM = srcRecord->GNAM;
    MODL = srcRecord->MODL;
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

    for(UINT32 ListIndex = 0; ListIndex < Weathers.value.size(); ListIndex++)
        op.Accept(Weathers.value[ListIndex].weather);

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

SINT32 CLMTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(WLST):
                Weathers.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CLMT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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
    Weathers.Unload();
    FNAM.Unload();
    GNAM.Unload();
    MODL.Unload();
    TNAM.Unload();
    return 1;
    }

SINT32 CLMTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITEAS(Weathers,WLST);
    WRITE(FNAM);
    WRITE(GNAM);
    MODL.Write(writer);
    WRITE(TNAM);
    return -1;
    }

bool CLMTRecord::operator ==(const CLMTRecord &other) const
    {
    return (TNAM == other.TNAM &&
            EDID.equalsi(other.EDID) &&
            FNAM.equalsi(other.FNAM) &&
            GNAM.equalsi(other.GNAM) &&
            Weathers == other.Weathers &&
            MODL == other.MODL);
    }

bool CLMTRecord::operator !=(const CLMTRecord &other) const
    {
    return !(*this == other);
    }

bool CLMTRecord::equals(Record *other)
    {
    return *this == *(CLMTRecord *)other;
    }
}