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
#include "DIALRecord.h"

namespace Ob
{
DIALRecord::DIALRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

DIALRecord::DIALRecord(DIALRecord *srcRecord):
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
    QSTI = srcRecord->QSTI;
    QSTR = srcRecord->QSTR;
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    return;
    }

DIALRecord::~DIALRecord()
    {
    //INFOs are owned at the mod level, so must be destroyed there
    }

bool DIALRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < QSTI.value.size(); ListIndex++)
        op.Accept(QSTI.value[ListIndex]);

    for(UINT32 ListIndex = 0; ListIndex < QSTR.value.size(); ListIndex++)
        op.Accept(QSTR.value[ListIndex]);

    return op.Stop();
    }

bool DIALRecord::IsTopic()
    {
    return (DATA.value == eTopic);
    }

void DIALRecord::IsTopic(bool value)
    {
    if(value)
        DATA.value = eTopic;
    else if(IsTopic())
        DATA.value = eConversation;
    }

bool DIALRecord::IsConversation()
    {
    return (DATA.value == eConversation);
    }

void DIALRecord::IsConversation(bool value)
    {
    if(value)
        DATA.value = eConversation;
    else if(IsConversation())
        DATA.value = eTopic;
    }

bool DIALRecord::IsCombat()
    {
    return (DATA.value == eCombat);
    }

void DIALRecord::IsCombat(bool value)
    {
    if(value)
        DATA.value = eCombat;
    else if(IsCombat())
        DATA.value = eTopic;
    }

bool DIALRecord::IsPersuasion()
    {
    return (DATA.value == ePersuasion);
    }

void DIALRecord::IsPersuasion(bool value)
    {
    if(value)
        DATA.value = ePersuasion;
    else if(IsPersuasion())
        DATA.value = eTopic;
    }

bool DIALRecord::IsDetection()
    {
    return (DATA.value == eDetection);
    }

void DIALRecord::IsDetection(bool value)
    {
    if(value)
        DATA.value = eDetection;
    else if(IsDetection())
        DATA.value = eTopic;
    }

bool DIALRecord::IsService()
    {
    return (DATA.value == eService);
    }

void DIALRecord::IsService(bool value)
    {
    if(value)
        DATA.value = eService;
    else if(IsService())
        DATA.value = eTopic;
    }

bool DIALRecord::IsMisc()
    {
    return (DATA.value == eMisc);
    }

void DIALRecord::IsMisc(bool value)
    {
    if(value)
        DATA.value = eMisc;
    else if(IsMisc())
        DATA.value = eTopic;
    }

bool DIALRecord::IsType(UINT8 Type)
    {
    return (DATA.value == Type);
    }

void DIALRecord::SetType(UINT8 Type)
    {
    DATA.value = Type;
    }

UINT32 DIALRecord::GetType()
    {
    return REV32(DIAL);
    }

STRING DIALRecord::GetStrType()
    {
    return "DIAL";
    }

SINT32 DIALRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(QSTI):
                QSTI.Read(buffer, subSize);
                break;
            case REV32(QSTR):
                QSTR.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  DIAL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
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
    QSTR.Unload();
    FULL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 DIALRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(QSTI);
    WRITE(QSTR);
    WRITE(FULL);
    WRITE(DATA);
    return -1;
    }

bool DIALRecord::operator ==(const DIALRecord &other) const
    {
    return (DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            QSTI == other.QSTI &&
            QSTR == other.QSTR);
    }

bool DIALRecord::operator !=(const DIALRecord &other) const
    {
    return !(*this == other);
    }

bool DIALRecord::equals(Record *other)
    {
    return *this == *(DIALRecord *)other;
    }

bool DIALRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //              all child records have been visited
    const DIALRecord *master_dial = (DIALRecord *)master;

    if(INFO.size() > master_dial->INFO.size())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < INFO.size(); ++ListIndex)
        if(identical_records.count(INFO[ListIndex]) == 0)
                return false;
    return true;
    }
}