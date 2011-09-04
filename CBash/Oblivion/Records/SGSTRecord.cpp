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
#include "SGSTRecord.h"

namespace Ob
{
SGSTRecord::SGSTDATA::SGSTDATA():
    uses(0),
    value(0),
    weight(0.0f)
    {
    //
    }

SGSTRecord::SGSTDATA::~SGSTDATA()
    {
    //
    }

bool SGSTRecord::SGSTDATA::operator ==(const SGSTDATA &other) const
    {
    return (uses == other.uses &&
            value == other.value &&
            AlmostEqual(weight,other.weight,2));
    }

bool SGSTRecord::SGSTDATA::operator !=(const SGSTDATA &other) const
    {
    return !(*this == other);
    }

SGSTRecord::SGSTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SGSTRecord::SGSTRecord(SGSTRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        return;
        }

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    SCRI = srcRecord->SCRI;
    Effects = srcRecord->Effects;
    DATA = srcRecord->DATA;
    OBME = srcRecord->OBME;
    }

SGSTRecord::~SGSTRecord()
    {
    //
    }

bool SGSTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);

    for(UINT32 ListIndex = 0; ListIndex < Effects.value.size(); ListIndex++)
        Effects.value[ListIndex]->VisitFormIDs(op);

    return op.Stop();
    }

UINT32 SGSTRecord::GetType()
    {
    return REV32(SGST);
    }

STRING SGSTRecord::GetStrType()
    {
    return "SGST";
    }

SINT32 SGSTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    bool bNoOBME = true;
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
            case REV32(OBME):
                OBME.Load();
                OBME->OBME.Read(buffer, subSize);
                break;
            case REV32(FULL):
                if(Effects.value.size())
                    Effects.value.back()->FULL.Read(buffer, subSize, CompressedOnDisk);
                else
                    FULL.Read(buffer, subSize, CompressedOnDisk);
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(EFME):
                bNoOBME = false;
                Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFME.Read(buffer, subSize);
                break;
            case REV32(EFID):
                if(bNoOBME || Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFID.Read(buffer, subSize);
                bNoOBME = true;
                break;
            case REV32(EFIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFIT.Read(buffer, subSize);
                break;
            case REV32(SCIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->SCIT.Read(buffer, subSize);
                break;
            case REV32(EFII):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFII.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(EFIX):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFIX.Read(buffer, subSize);
                break;
            case REV32(EFXX):
                buffer += subSize;
                break;
            case REV32(DATX):
                OBME.Load();
                OBME->DATX.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SGST: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 SGSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    SCRI.Unload();
    Effects.Unload();
    DATA.Unload();
    OBME.Unload();
    return 1;
    }

SINT32 SGSTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    if(OBME.IsLoaded())
        OBME->WRITE(OBME);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(SCRI);
    Effects.Write(writer);
    if(OBME.IsLoaded())
        {
        if(Effects.value.size())
            WRITEEMPTY(EFXX);
        if(OBME->DATX.IsLoaded())
            OBME->WRITE(DATX);
        }
    WRITE(DATA);
    return -1;
    }

bool SGSTRecord::operator ==(const SGSTRecord &other) const
    {
    return (SCRI == other.SCRI &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            OBME == other.OBME &&
            Effects == other.Effects);
    }

bool SGSTRecord::operator !=(const SGSTRecord &other) const
    {
    return !(*this == other);
    }

bool SGSTRecord::equals(Record *other)
    {
    return *this == *(SGSTRecord *)other;
    }
}