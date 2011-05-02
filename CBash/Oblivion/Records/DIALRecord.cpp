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
#include "DIALRecord.h"
#include <vector>

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

    if(!srcRecord->IsChanged())
        {
        IsLoaded(false);
        recData = srcRecord->recData;
        return;
        }

    EDID = srcRecord->EDID;
    QSTI.resize(srcRecord->QSTI.size());
    for(UINT32 x = 0; x < srcRecord->QSTI.size(); x++)
        QSTI[x] = srcRecord->QSTI[x];
    QSTR.resize(srcRecord->QSTR.size());
    for(UINT32 x = 0; x < srcRecord->QSTR.size(); x++)
        QSTR[x] = srcRecord->QSTR[x];
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    return;
    }

DIALRecord::~DIALRecord()
    {
    for(UINT32 x = 0; x < INFO.size(); x++)
        delete INFO[x];
    }

bool DIALRecord::HasSubRecords()
    {
    return true;
    }

bool DIALRecord::VisitSubRecords(const UINT32 &RecordType, RecordOp &op)
    {
    bool stop;

    if(RecordType == NULL || RecordType == 'OFNI')
        for(UINT32 x = 0; x < INFO.size();++x)
            {
            stop = op.Accept(INFO[x]);
            if(INFO[x] == NULL)
                {
                INFO.erase(INFO.begin() + x);
                --x;
                }
            if(stop)
                return stop;
            }

    return op.Stop();
    }

bool DIALRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < QSTI.size(); x++)
        op.Accept(QSTI[x]);

    for(UINT32 x = 0; x < QSTR.size(); x++)
        op.Accept(QSTR[x]);

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
    return 'LAID';
    }

STRING DIALRecord::GetStrType()
    {
    return "DIAL";
    }

SINT32 DIALRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case 'ITSQ':
                _readBuffer(&curFormID,buffer,subSize,curPos);
                QSTI.push_back(curFormID);
                break;
            case 'RTSQ':
                _readBuffer(&curFormID,buffer,subSize,curPos);
                QSTR.push_back(curFormID);
                break;
            case 'LLUF':
                FULL.Read(buffer, subSize, curPos);
                break;
            case 'ATAD':
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  DIAL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
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

    QSTI.clear();
    QSTR.clear();

    FULL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 DIALRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded())
        writer.record_write_subrecord('DIDE', EDID.value, EDID.GetSize());
    for(UINT32 p = 0; p < QSTI.size(); p++)
        writer.record_write_subrecord('ITSQ', &QSTI[p], sizeof(UINT32));
    for(UINT32 p = 0; p < QSTR.size(); p++)
        writer.record_write_subrecord('RTSQ', &QSTR[p], sizeof(UINT32));
    if(FULL.IsLoaded())
        writer.record_write_subrecord('LLUF', FULL.value, FULL.GetSize());
    if(DATA.IsLoaded())
        writer.record_write_subrecord('ATAD', &DATA.value, DATA.GetSize());
    return -1;
    }

bool DIALRecord::operator ==(const DIALRecord &other) const
    {
    if(EDID.equalsi(other.EDID) &&
        FULL.equals(other.FULL) &&
        DATA == other.DATA &&
        QSTI.size() == other.QSTI.size() &&
        QSTR.size() == other.QSTR.size())
        {
        //Not sure if record order matters on quests, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < QSTI.size(); ++x)
            if(QSTI[x] != other.QSTI[x])
                return false;

        //Not sure if record order matters on removed quests, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < QSTR.size(); ++x)
            if(QSTR[x] != other.QSTR[x])
                return false;
        return true;
        }

    return false;
    }

bool DIALRecord::operator !=(const DIALRecord &other) const
    {
    return !(*this == other);
    }