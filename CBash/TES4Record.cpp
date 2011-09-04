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
#include "Common.h"
#include "TES4Record.h"
#include "zlib/zlib.h"

TES4Record::TES4HEDR::TES4HEDR(FLOAT32 _version, UINT32 _numRecords, UINT32 _nextObject):
    version(_version),
    numRecords(_numRecords),
    nextObject(_nextObject)
    {
    //
    }

TES4Record::TES4HEDR::~TES4HEDR()
    {
    //
    }

bool TES4Record::TES4HEDR::operator ==(const TES4HEDR &other) const
    {
    return (AlmostEqual(version,other.version,2) &&
            numRecords == other.numRecords &&
            nextObject == other.nextObject);
    }

bool TES4Record::TES4HEDR::operator !=(const TES4HEDR &other) const
    {
    return !(*this == other);
    }

TES4Record::TES4Record(unsigned char *_recData):
    Record(_recData),
    formVersion(0)
    {
    memset(&versionControl2[0], 0x00, 2);
    }

TES4Record::TES4Record(TES4Record *srcRecord):
    Record()
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
        {
        IsLoaded(false);
        return;
        }

    //EDID = srcRecord->EDID;
    HEDR = srcRecord->HEDR;
    OFST = srcRecord->OFST;
    DELE = srcRecord->DELE;
    CNAM = srcRecord->CNAM;
    SNAM = srcRecord->SNAM;
    MAST.resize(srcRecord->MAST.size());
    for(UINT32 x = 0; x < srcRecord->MAST.size();++x)
        {
        UINT32 size = (UINT32)strlen(srcRecord->MAST[x]) + 1;
        MAST[x] = new char[size];
        memcpy(MAST[x], srcRecord->MAST[x], size);
        }
    ONAM = srcRecord->ONAM;
    SCRN = srcRecord->SCRN;
    return;
    }

TES4Record::~TES4Record()
    {
    //
    }

bool TES4Record::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 x = 0; x < ONAM.value.size(); x++)
        op.Accept(ONAM.value[x]);

    return op.Stop();
    }

bool TES4Record::IsESM()
    {
    if(!IsLoaded()) return false;
    return (flags & fIsESM) != 0;
    }

void TES4Record::IsESM(bool value)
    {
    if(!IsLoaded()) return;
    flags = value ? (flags | fIsESM) : (flags & ~fIsESM);
    }

UINT32 TES4Record::GetType()
    {
    return REV32(TES4);
    }

STRING TES4Record::GetStrType()
    {
    return "TES4";
    }

SINT32 TES4Record::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(HEDR):
                HEDR.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MAST):
                MAST.push_back(new char[subSize]);
                memcpy(MAST.back(), buffer, subSize);
                buffer += subSize;
                break;
            case REV32(DATA):
                buffer += subSize;
                break;
            case REV32(OFST):
                OFST.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DELE):
                DELE.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ONAM):
                ONAM.Read(buffer, subSize);
                break;
            case REV32(SCRN):
                SCRN.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  TES4: %08X - Unknown subType = %04x\n", formID, subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 TES4Record::Unload()
    {
    //TES4 should never be unloaded, so do nothing
    return 1;
    }

SINT32 TES4Record::WriteRecord(FileWriter &writer)
    {
    UINT8 DATA[8] = {0};
    switch(whichGame)
        {
        case eIsOblivion:
            WRITE(HEDR);
            WRITE(OFST);
            WRITE(DELE);
            WRITE(CNAM);
            WRITE(SNAM);
            for(UINT32 p = 0; p < MAST.size(); p++)
                {
                writer.record_write_subrecord(REV32(MAST), MAST[p], (UINT32)strlen(MAST[p]) + 1);
                writer.record_write_subrecord(REV32(DATA), &DATA[0], sizeof(DATA));
                }
            break;
        case eIsFallout3:
            printer("TES4Record::WriteRecord: Error - Unable to write TES4 record. Fallout 3 support not yet implemented.\n");
            return -1;
        case eIsFalloutNewVegas:
            WRITE(HEDR);
            WRITE(OFST);
            WRITE(DELE);
            WRITE(CNAM);
            WRITE(SNAM);
            for(UINT32 p = 0; p < MAST.size(); p++)
                {
                writer.record_write_subrecord(REV32(MAST), MAST[p], (UINT32)strlen(MAST[p]) + 1);
                writer.record_write_subrecord(REV32(DATA), &DATA[0], sizeof(DATA));
                }
            WRITE(ONAM);
            WRITE(SCRN);
            break;
        }

    return -1;
    }

UINT32 TES4Record::Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
    {
    IsCompressed(false);
    UINT32 recSize = 0;
    UINT32 recType = GetType();
    UINT32 cleanFlags = 0;
    //IsLoaded is used by CBash internally and is not part of the file format but shares the flags field to save space.
    //So it has to be cleaned before being written.
    if(IsLoaded())
        {
        IsLoaded(false);
        cleanFlags = flags;
        IsLoaded(true);
        }
    else
        cleanFlags = flags;

    collapser.Accept(formID);

    VisitFormIDs(collapser);
    WriteRecord(writer);
    recSize = writer.record_size();
    writer.file_write(&recType, 4);
    writer.file_write(&recSize, 4);
    writer.file_write(&cleanFlags, 4);
    writer.file_write(&formID, 4);
    writer.file_write(cleaned_flag2(), 4);
    if(whichGame == eIsFalloutNewVegas)
        {
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        }
    writer.record_flush();

    expander.Accept(formID);
    if(IsChanged())
        VisitFormIDs(expander);
    else
        Unload();
    if(whichGame == eIsFalloutNewVegas)
        return recSize + 24;
    else
        return recSize + 20;
    }

bool TES4Record::operator ==(const TES4Record &other) const
    {
    if(OFST == other.OFST &&
        DELE == other.DELE &&
        CNAM.equals(other.CNAM) &&
        SNAM.equals(other.SNAM) &&
        formVersion == other.formVersion &&
        versionControl2[0] == other.versionControl2[0] &&
        versionControl2[1] == other.versionControl2[1] &&
        SCRN == other.SCRN &&
        MAST.size() == other.MAST.size() &&
        ONAM == other.ONAM)
        {
        //Record order kinda sorta but doesn't really matter on masters, so equality testing is easy
        //The order determines the mod index of all formIDs in the mod file
        //If both records have the same masters in the same orders, the formIDs will have the same master indexing
        //If both records have the same masters in different orders, the formIDs will have different indexing but be logically equivalent
        //The ordering has no effect on load order in game or in the editor
        for(UINT32 x = 0; x < MAST.size(); ++x)
            if(icmps(MAST[x], other.MAST[x]) != 0)
                return false;
        return true;
        }

    return false;
    }

bool TES4Record::operator !=(const TES4Record &other) const
    {
    return !(*this == other);
    }

bool TES4Record::equals(Record *other)
    {
    return *this == *(TES4Record *)other;
    }