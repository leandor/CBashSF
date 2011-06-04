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

namespace FNV
{
void DIALRecord::DIALUNK::Write(FileWriter &writer)
    {
    WRITE(INFC);
    WRITE(INFX);
    }

bool DIALRecord::DIALUNK::operator ==(const DIALUNK &other) const
    {
    return (INFC == other.INFC &&
            INFX == other.INFX);
    }

bool DIALRecord::DIALUNK::operator !=(const DIALUNK &other) const
    {
    return !(*this == other);
    }

void DIALRecord::DIALQSTI::Write(FileWriter &writer)
    {
    WRITE(QSTI);
    Unknown.Write(writer);
    }

bool DIALRecord::DIALQSTI::operator ==(const DIALQSTI &other) const
    {
    return (QSTI == other.QSTI &&
            Unknown == other.Unknown);
    }

bool DIALRecord::DIALQSTI::operator !=(const DIALQSTI &other) const
    {
    return !(*this == other);
    }

void DIALRecord::DIALQSTR::Write(FileWriter &writer)
    {
    WRITE(QSTR);
    Unknown.Write(writer);
    }

bool DIALRecord::DIALQSTR::operator ==(const DIALQSTR &other) const
    {
    return (QSTR == other.QSTR &&
            Unknown == other.Unknown);
    }

bool DIALRecord::DIALQSTR::operator !=(const DIALQSTR &other) const
    {
    return !(*this == other);
    }

DIALRecord::DIALDATA::DIALDATA():
    dialType(0),
    flags(0)
    {
    //
    }

DIALRecord::DIALDATA::~DIALDATA()
    {
    //
    }

bool DIALRecord::DIALDATA::operator ==(const DIALDATA &other) const
    {
    return (dialType == other.dialType &&
            flags == other.flags);
    }

bool DIALRecord::DIALDATA::operator !=(const DIALDATA &other) const
    {
    return !(*this == other);
    }

DIALRecord::DIALRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

DIALRecord::DIALRecord(DIALRecord *srcRecord):
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
    QSTI = srcRecord->QSTI;
    QSTR = srcRecord->QSTR;
    FULL = srcRecord->FULL;
    PNAM = srcRecord->PNAM;
    TDUM = srcRecord->TDUM;
    DATA = srcRecord->DATA;
    return;
    }

DIALRecord::~DIALRecord()
    {
    for(UINT32 x = 0; x < INFO.size(); x++)
        delete INFO[x];
    }

bool DIALRecord::VisitSubRecords(const UINT32 &RecordType, RecordOp &op)
    {
    bool stop;

    if(RecordType == NULL || RecordType == REV32(INFO))
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

    for(UINT32 ListIndex = 0; ListIndex < QSTI.value.size(); ListIndex++)
        {
        op.Accept(QSTI.value[ListIndex]->QSTI.value);
        for(UINT32 ListX2Index = 0; ListX2Index < QSTI.value[ListIndex]->Unknown.value.size(); ListX2Index++)
            op.Accept(QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value);
        }
    for(UINT32 ListIndex = 0; ListIndex < QSTR.value.size(); ListIndex++)
        {
        op.Accept(QSTR.value[ListIndex]->QSTR.value);
        for(UINT32 ListX2Index = 0; ListX2Index < QSTR.value[ListIndex]->Unknown.value.size(); ListX2Index++)
            op.Accept(QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value);
        }

    return op.Stop();
    }

bool DIALRecord::IsTopic()
    {
    return (DATA.value.dialType == eTopic);
    }

void DIALRecord::IsTopic(bool value)
    {
    DATA.value.dialType = value ? eTopic : eConversation;
    }

bool DIALRecord::IsConversation()
    {
    return (DATA.value.dialType == eConversation);
    }

void DIALRecord::IsConversation(bool value)
    {
    DATA.value.dialType = value ? eConversation : eTopic;
    }

bool DIALRecord::IsCombat()
    {
    return (DATA.value.dialType == eCombat);
    }

void DIALRecord::IsCombat(bool value)
    {
    DATA.value.dialType = value ? eCombat : eTopic;
    }

bool DIALRecord::IsPersuasion()
    {
    return (DATA.value.dialType == ePersuasion);
    }

void DIALRecord::IsPersuasion(bool value)
    {
    DATA.value.dialType = value ? ePersuasion : eTopic;
    }

bool DIALRecord::IsDetection()
    {
    return (DATA.value.dialType == eDetection);
    }

void DIALRecord::IsDetection(bool value)
    {
    DATA.value.dialType = value ? eDetection : eTopic;
    }

bool DIALRecord::IsService()
    {
    return (DATA.value.dialType == eService);
    }

void DIALRecord::IsService(bool value)
    {
    DATA.value.dialType = value ? eService : eTopic;
    }

bool DIALRecord::IsMisc()
    {
    return (DATA.value.dialType == eMisc);
    }

void DIALRecord::IsMisc(bool value)
    {
    DATA.value.dialType = value ? eMisc : eTopic;
    }

bool DIALRecord::IsRadio()
    {
    return (DATA.value.dialType == eRadio);
    }

void DIALRecord::IsRadio(bool value)
    {
    DATA.value.dialType = value ? eRadio : eTopic;
    }

bool DIALRecord::IsType(UINT8 Type)
    {
    return DATA.value.dialType == Type;
    }

void DIALRecord::SetType(UINT8 Type)
    {
    DATA.value.dialType = Type;
    }

bool DIALRecord::IsRumors()
    {
    return (DATA.value.flags & fIsRumors) != 0;
    }

void DIALRecord::IsRumors(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsRumors) : (DATA.value.flags & ~fIsRumors);
    }

bool DIALRecord::IsTopLevel()
    {
    return (DATA.value.flags & fIsTopLevel) != 0;
    }

void DIALRecord::IsTopLevel(bool value)
    {
    DATA.value.flags = value ? (DATA.value.flags | fIsTopLevel) : (DATA.value.flags & ~fIsTopLevel);
    }

bool DIALRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void DIALRecord::SetFlagMask(UINT8 Mask)
    {
    DATA.value.flags = Mask;
    }

UINT32 DIALRecord::GetType()
    {
    return REV32(DIAL);
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
    UINT32 lastChunk = 0;
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
            case REV32(QSTI):
                QSTI.value.push_back(new DIALQSTI);
                QSTI.value.back()->QSTI.Read(buffer, subSize, curPos);
                lastChunk = REV32(QSTI);
                break;
            case REV32(INFC):
                switch(lastChunk)
                    {
                    case REV32(QSTI):
                        if(QSTI.value.size() == 0)
                            QSTI.value.push_back(new DIALQSTI);
                        QSTI.value.back()->Unknown.value.push_back(new DIALUNK);
                        QSTI.value.back()->Unknown.value.back()->INFC.Read(buffer, subSize, curPos);
                        break;
                    case REV32(QSTR):
                        if(QSTR.value.size() == 0)
                            QSTR.value.push_back(new DIALQSTR);
                        QSTR.value.back()->Unknown.value.push_back(new DIALUNK);
                        QSTR.value.back()->Unknown.value.back()->INFC.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //Occurs a limited number of times in FalloutNV.esm
                        //Presumably the CS was broken when writing these records at some point
                        //May not be ideal to junk them, but not much else can be done while their use is unknown
                        curPos += subSize;
                        break;
                        //printer("  DIAL: %08X - Unexpected INFC chunk\n", formID);
                        //CBASH_CHUNK_DEBUG
                        //printer("  Size = %i\n", subSize);
                        //printer("  CurPos = %04x\n\n", curPos - 6);
                        //curPos += subSize;
                        //break;
                    }
                break;
            case REV32(INFX):
                switch(lastChunk)
                    {
                    case REV32(QSTI):
                        if(QSTI.value.size() == 0)
                            QSTI.value.push_back(new DIALQSTI);
                        if(QSTI.value.back()->Unknown.value.size() == 0)
                            QSTI.value.back()->Unknown.value.push_back(new DIALUNK);
                        QSTI.value.back()->Unknown.value.back()->INFX.Read(buffer, subSize, curPos);
                        break;
                    case REV32(QSTR):
                        if(QSTR.value.size() == 0)
                            QSTR.value.push_back(new DIALQSTR);
                        if(QSTR.value.back()->Unknown.value.size() == 0)
                            QSTR.value.back()->Unknown.value.push_back(new DIALUNK);
                        QSTR.value.back()->Unknown.value.back()->INFX.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //Occurs a limited number of times in FalloutNV.esm
                        //Presumably the CS was broken when writing these records at some point
                        //May not be ideal to junk them, but not much else can be done while their use is unknown
                        curPos += subSize;
                        break;
                        //printer("  DIAL: %08X - Unexpected INFX chunk\n", formID);
                        //CBASH_CHUNK_DEBUG
                        //printer("  Size = %i\n", subSize);
                        //printer("  CurPos = %04x\n\n", curPos - 6);
                        //curPos += subSize;
                        //break;
                    }
                break;
            case REV32(QSTR):
                QSTR.value.push_back(new DIALQSTR);
                QSTR.value.back()->QSTR.Read(buffer, subSize, curPos);
                lastChunk = REV32(QSTR);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, curPos);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize, curPos);
                break;
            case REV32(TDUM):
                TDUM.Read(buffer, subSize, curPos);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  DIAL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", curPos - 6);
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
    QSTI.Unload();
    QSTR.Unload();
    FULL.Unload();
    PNAM.Unload();
    TDUM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 DIALRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    QSTI.Write(writer);
    QSTR.Write(writer);
    WRITE(FULL);
    WRITE(PNAM);
    WRITE(TDUM);
    WRITE(DATA);
    return -1;
    }

bool DIALRecord::operator ==(const DIALRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            QSTI == other.QSTI &&
            QSTR == other.QSTR &&
            FULL.equals(other.FULL) &&
            PNAM == other.PNAM &&
            TDUM.equals(other.TDUM) &&
            DATA == other.DATA);
    }

bool DIALRecord::operator !=(const DIALRecord &other) const
    {
    return !(*this == other);
    }
}