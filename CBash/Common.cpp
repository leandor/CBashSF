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
// Common.cpp
#include "Common.h"
#include "zlib/zlib.h"

#ifdef CBASH_CALLTIMING
    std::map<char *, double> CallTime;
#endif

#ifdef CBASH_CALLCOUNT
    std::map<char *, unsigned long> CallCount;
#endif

const STRING Ex_NULL::__CLR_OR_THIS_CALL what() const
    {
    return "NULL Pointer";
    }

const STRING Ex_INVALIDINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Index";
    }

const STRING Ex_INVALIDCOLLECTIONINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Collection Index";
    }

const STRING Ex_INVALIDMODINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Mod Index";
    }

const STRING Ex_INVALIDRECORDINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid RecordID or RecordEditorID. Record not found.";
    }

bool sameStr::operator()( const STRING s1, const STRING s2 ) const
    {
    return _stricmp( s1, s2 ) < 0;
    }

STRING DeGhostModName(STRING const ModName)
    {
    STRING NonGhostName = NULL;
    UINT32 NameLength = strlen(ModName) + 1;
    if(_stricmp(".ghost",ModName + NameLength - 7) == 0)
        {
        NonGhostName = new char[NameLength];
        strcpy_s(NonGhostName, NameLength, ModName);
        NonGhostName[NameLength - 7] = 0x00;
        //printf("DeGhostModName: De-ghosted (%s)(%d) to (%s)(%d)\n", ModName, strlen(ModName), NonGhostName, strlen(NonGhostName));
        return NonGhostName;
        }
    return NULL;
    }

bool FileExists(STRING const FileName)
    {
    struct stat statBuffer;
    return (stat(FileName, &statBuffer) >= 0 && statBuffer.st_mode & S_IFREG);
    }

bool AlmostEqual(FLOAT32 A, FLOAT32 B, SINT32 maxUlps)
    {
    SINT32 aInt = *(SINT32*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    SINT32 bInt = *(SINT32*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    // Now we can compare aInt and bInt to find out how far apart A and B
    // are.
    if (abs(aInt - bInt) <= maxUlps)
        return true;
    return false;
    }

FileWriter::FileWriter(STRING filename, UINT32 size):
    file_buffer(NULL),
    record_buffer(NULL),
    compressed_buffer(NULL),
    file_buffer_used(0),
    record_buffer_used(0),
    compressed_buffer_used(0),
    file_buffer_size(size),
    record_buffer_size(size),
    compressed_buffer_size(size),
    fh(-1),
    FileName(filename)
    {
    if(size == 0)
        return;
    file_buffer = new unsigned char[file_buffer_size];
    record_buffer = new unsigned char[record_buffer_size];
    compressed_buffer = new unsigned char[compressed_buffer_size];
    }

FileWriter::~FileWriter()
    {
    close();
    delete []file_buffer;
    delete []record_buffer;
    delete []compressed_buffer;
    }

SINT32 FileWriter::open()
    {
    if(fh != -1 || FileName == NULL)
        return -1;
    errno_t err = _sopen_s(&fh, FileName, _O_CREAT | _O_RDWR | _O_BINARY, _SH_DENYWR, _S_IREAD | _S_IWRITE );
    if( err != 0 )
        {
        switch(err)
            {
            case EACCES:
                printf("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. Given path is a directory, or file is read-only, but an open-for-writing operation was attempted.\n", FileName);
                return -1;
            case EEXIST:
                printf("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. _O_CREAT and _O_EXCL flags were specified, but filename already exists.\n", FileName);
                return -1;
            case EINVAL:
                printf("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. Invalid oflag, shflag, or pmode  argument, or pfh or filename was a null pointer.\n", FileName);
                return -1;
            case EMFILE:
                printf("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. No more file descriptors available.\n", FileName);
                return -1;
            case ENOENT:
                printf("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. File or path not found.\n", FileName);
                return -1;
            default:
                printf("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. An unknown error occurred.\n", FileName);
                return -1;
            }
        _close(fh);
        return -1;
        }
    return 0;
    }

SINT32 FileWriter::close()
    {
    if(fh != -1)
        {
        if(file_buffer_used)
            {
            _write(fh, file_buffer, file_buffer_used);
            file_buffer_used = 0;
            }
        _close(fh);
        }
    fh = -1;
    return 0;
    }

void FileWriter::record_write(const void *source, UINT32 length)
    {
    if(length == 0)
        return;
    if(source == NULL)
        {
        printf("FileWriter:write: Error - Unable to write. Source buffer is NULL.\n");
        return;
        }

    if((length + record_buffer_used) > record_buffer_size)
        {
        //Should be rare or never occur with a sufficiently large initial buffer size
        record_buffer_size = (length + record_buffer_used) * 2;
        unsigned char *resized_buffer = new unsigned char[record_buffer_size];
        memcpy(resized_buffer, record_buffer, record_buffer_used);
        delete []record_buffer;
        record_buffer = resized_buffer;
        }
        
    memcpy(record_buffer + record_buffer_used, source, length);
    record_buffer_used += length;
    return;
    }

void FileWriter::record_write_subheader(UINT32 signature, UINT32 length)
    {
    if(length <= 65535)
        {
        record_write(&signature, 4);
        record_write(&length, 2);
        }
    else //Requires XXXX SubRecord
        {
        UINT32 _Temp = 4;
        record_write("XXXX", 4);
        record_write(&_Temp, 2);
        record_write(&length, 4);
        record_write(&signature, 4);
        _Temp = 0;
        record_write(&_Temp, 2);
        }
    return;
    }

void FileWriter::record_write_subrecord(UINT32 signature, const void *source, UINT32 length)
    {
    record_write_subheader(signature, length);
    record_write(source, length);
    return;
    }

UINT32 FileWriter::record_compress()
    {
    UINT32 compSize = compressBound(record_buffer_used);
    if(compSize + 4 > compressed_buffer_size)
        {
        delete []compressed_buffer;
        compressed_buffer_size = compSize + 4;
        compressed_buffer = new unsigned char[compressed_buffer_size];
        }
    else
        compSize = compressed_buffer_size;
    compress2(compressed_buffer + 4, &compSize, record_buffer, record_buffer_used, 6);
    memcpy(compressed_buffer, &record_buffer_used, 4);
    std::swap(record_buffer, compressed_buffer);
    std::swap(record_buffer_size, compressed_buffer_size);
    record_buffer_used = compSize + 4;
    return record_buffer_used;
    }
    
UINT32 FileWriter::record_size()
    {
    return record_buffer_used;
    }

void FileWriter::record_flush()
    {
    file_write(record_buffer, record_buffer_used);
    record_buffer_used = 0;
    return;
    }

UINT32 FileWriter::file_tell()
    {
    return file_buffer_used + _tell(fh);
    }

void FileWriter::file_write(const void *source_buffer, UINT32 source_buffer_used)
    {
    if(source_buffer_used == 0)
        return;

    if(fh == -1 || file_buffer == NULL)
        {
        printf("FileWriter::file_write: Error - Unable to write. File buffer or File Handle is invalid.\n");
        return;
        }
    else if(source_buffer == NULL)
        {
        printf("FileWriter::file_write: Error - Unable to write. Source buffer is NULL.\n");
        return;
        }

    //Flush the file buffer if it is getting full
    if((file_buffer_used + source_buffer_used) >= file_buffer_size)
        {
        //file_flush();
        _write(fh, file_buffer, file_buffer_used);
        file_buffer_used = 0;
        }
    //Use the file buffer if there's room
    if(source_buffer_used < file_buffer_size)
        {
        memcpy(file_buffer + file_buffer_used, source_buffer, source_buffer_used);
        file_buffer_used += source_buffer_used;
        }
    else
        {
        //Otherwise, write directly to disk.
        _write(fh, source_buffer, source_buffer_used);
        }
    return;
    }

void FileWriter::file_write(UINT32 position, const void *source_buffer, UINT32 source_buffer_used)
    {
    //Back written data must not advance past the current tell / file_buffer_used
    if(source_buffer_used == 0)
        return;

    if(fh == -1 || file_buffer == NULL)
        {
        printf("FileWriter::file_write: Error - Unable to write. File buffer or File Handle is invalid.\n");
        return;
        }
    else if(source_buffer == NULL)
        {
        printf("FileWriter::file_write: Error - Unable to write. Source buffer is NULL.\n");
        return;
        }
    SINT32 curPos = _tell(fh);
        
    if(position < (UINT32)curPos)
        {
        //It has already been written to disk.
        _lseek(fh, position, SEEK_SET);
        _write(fh, source_buffer, source_buffer_used);
        _lseek(fh, curPos, SEEK_SET);
        }
    else if(position < (file_buffer_used + curPos))
        {
        //Address is still in buffer
        memcpy(file_buffer + (position - curPos), source_buffer, source_buffer_used);
        }
    else
        {
        printf("FileWriter::file_write: Error - Unable to write at offset. Provided offset is greater than the current position.\n");
        return;
        }
    return;
    }

FileReader::FileReader(STRING filename, STRING modname):
    file_map(),
    FileName(filename),
    ModName(modname),
    buffer_position(0),
    start(NULL),
    end(NULL)   
    {
    //
    }

FileReader::~FileReader()
    {
    if(FileName != ModName)
        delete []FileName;
    delete []ModName;
    close();
    }
    
STRING const FileReader::getFileName()
    {
    return FileName;
    }

STRING const FileReader::getModName()
    {
    return ModName;
    }

bool FileReader::IsGhosted()
    {
    return ModName != FileName;
    }

time_t FileReader::mtime()
    {
    struct stat buf;
    if(stat(FileName, &buf) < 0)
        return 0;
    else
        return buf.st_mtime;
    }

bool FileReader::exists()
    {
    struct stat statBuffer;
    return (stat(FileName, &statBuffer) >= 0 && statBuffer.st_mode & S_IFREG);
    }

SINT32 FileReader::open()
    {
    if(FileName == NULL || file_map.is_open())
        return -1;
    try
        {
        file_map.open(FileName);
        }
    catch(...)
        {
        printf("FileReader: Error - Unable to open \"%s\" as read only via memory mapping. An unhandled exception occurred.\n", FileName);
        throw;
        return -1;
        }
    start = (unsigned char *)file_map.data();
    end = start + file_map.size();
    return 0;
    }

SINT32 FileReader::close()
    {
    file_map.close();
    return 0;
    }

bool FileReader::IsOpen()
    {
    return file_map.is_open();
    }

UINT32 FileReader::tell()
    {
    return buffer_position;
    }

bool FileReader::eof()
    {
    return (buffer_position >= file_map.size());
    }

void FileReader::skip(UINT32 length)
    {
    buffer_position += length;
    }
    
bool FileReader::IsInFile(void *buffer)
    {
    return (buffer >= start) && (buffer <= end);
    }

unsigned char *FileReader::getBuffer(UINT32 offset)
    {
    if(IsInFile(start + offset))
        return start + offset;
    return NULL;
    }

UINT32 FileReader::getBufferSize()
    {
    return file_map.size();
    }

void FileReader::read(void *destination, UINT32 length)
    {
    if(destination == NULL || !file_map.is_open())
        {
        if(destination == NULL)
            printf("FileHandler: Error - Unable to read from buffer. Destination pointer is NULL.\n");
        else
            printf("FileHandler: Error - Unable to read from buffer. Source pointer is NULL.\n");
        return;
        }
    memcpy(destination, start + buffer_position, length);
    buffer_position += length;
    }

FormIDHandlerClass::FormIDHandlerClass(std::vector<StringRecord> &_MAST, UINT32 &_NextObject):
    MAST(_MAST),
    nextObject(_NextObject),
    ExpandedIndex(0),
    CollapsedIndex(0),
    IsEmpty(true),
    bMastersChanged(false),
    FileStart(0),
    FileEnd(0)
    {
    //
    }

FormIDHandlerClass::~FormIDHandlerClass()
    {
    //
    }

void FormIDHandlerClass::SetLoadOrder(std::vector<STRING> &cLoadOrder)
    {
    if(cLoadOrder.size() > 0xFF)
        {
        printf("FormIDHandler: Error - Unable to set load order. Tried to set load order > 0xFF. Load order size = %i.\n", cLoadOrder.size());
        throw 1;
        return;
        }
    LoadOrder255 = cLoadOrder;
    return;
    }

UINT32 FormIDHandlerClass::NextExpandedFormID()
    {
    //0x00FFFFFF is the highest formID that can be used.
    if(nextObject >= 0x01000000)
        nextObject = END_HARDCODED_IDS;
    //printf("Assigning new: %08X\n", (ExpandedIndex << 24) | (nextObject + 1));
    return (ExpandedIndex << 24) | ++nextObject;
    }

void FormIDHandlerClass::UpdateFormIDLookup()
    {
    //Each ModFile maintains a formID resolution lookup table of valid modIndexs
    //both when expanded into a load order corrected format
    //and for when collapsed back into a writable format
    //This function populates that table, and allows much, much faster formID resolution
    //which occurs on every formID that is read, set, and written...

    //The Collapsed lookup table has to be updated anytime the mod's masters change.
    //It also sorts the masters based on the load order
    UINT32 numMods = (UINT32)LoadOrder255.size();
    STRING curMaster = NULL;
    CollapsedIndex = (UINT8)MAST.size();
    for(UINT16 p = 0; p <= 0xFF; ++p)
        CollapseTable[(UINT8)p] = CollapsedIndex;

    std::vector<StringRecord> sortedMAST;
    sortedMAST.reserve(CollapsedIndex);
    for(UINT32 x = 0; x < LoadOrder255.size(); ++x)
        {
        for(UINT16 y = 0; y < CollapsedIndex; ++y)
            {
            if(_stricmp(LoadOrder255[(UINT8)x], MAST[(UINT8)y].value) == 0)
                {
                sortedMAST.push_back(MAST[(UINT8)y]);
                break;
                }
            }
        }
    //MAST = sortedMAST;
    MAST.clear();
    MAST.resize(sortedMAST.size());
    //printf("Base collapse table: %02X\n", CollapsedIndex);
    //printf("Updating collapse table\n");
    for(UINT16 p = 0; p < CollapsedIndex; ++p)
        {
        MAST[(UINT8)p] = sortedMAST[(UINT8)p];
        curMaster = MAST[(UINT8)p].value;
        //printf("master %s\n", curMaster);
        for(UINT32 y = 0; y < numMods; ++y)
            if(_stricmp(LoadOrder255[(UINT8)y], curMaster) == 0)
                {
                CollapseTable[(UINT8)y] = (UINT8)p;
                //printf("%02X == %02X\n", (UINT8)y, (UINT8)p);
                break;
                }
        }
    //printf("Collapse table updated.\n");
    //printf("Existing expand table: %02X\n", ExpandedIndex);
    //for(UINT32 y = 0; y <= 0xFF; ++y)
    //    printf("%02X == %02X\n", (UINT8)y, ExpandTable[(UINT8)y]);
    //printf("End expand table.\n");
    sortedMAST.clear();
    return;
    }

void FormIDHandlerClass::CreateFormIDLookup(const UINT8 expandedIndex)
    {
    //Each ModFile maintains a formID resolution lookup table of valid modIndexs
    //both when expanded into a load order corrected format
    //and for when collapsed back into a writable format
    //This function populates that table, and allows much, much faster formID resolution
    //which occurs on every formID that is read, set, and written...

    //The Expanded lookup table is only created once when the mod is first loaded.
    //This allows records to be read even after a master has been added, and have the formID
    //be set to the proper load order corrected value.
    //This can only be done because the load order is finalized once the mods are loaded.

    UINT32 numMods = (UINT32)LoadOrder255.size();
    STRING curMaster = NULL;
    CollapsedIndex = (UINT8)MAST.size();
    ExpandedIndex = expandedIndex;

    for(UINT16 p = 0; p <= 0xFF; ++p)
        {
        CollapseTable[(UINT8)p] = CollapsedIndex;
        ExpandTable[(UINT8)p] = ExpandedIndex;
        }

    for(UINT16 p = 0; p < CollapsedIndex; ++p)
        {
        curMaster = MAST[(UINT8)p].value;
        for(UINT32 y = 0; y < numMods; ++y)
            if(_stricmp(LoadOrder255[(UINT8)y], curMaster) == 0)
                {
                ExpandTable[(UINT8)p] = (UINT8)y;
                CollapseTable[(UINT8)y] = (UINT8)p;
                break;
                }
        }
    return;
    }

void FormIDHandlerClass::AddMaster(STRING const curMaster)
    {
    MAST.push_back(StringRecord(curMaster));
    bMastersChanged = true;
    //Update the formID resolution lookup table
    UpdateFormIDLookup();
    return;
    }

bool FormIDHandlerClass::MastersChanged()
    {
    return bMastersChanged;
    }

bool FormIDHandlerClass::IsNewRecord(const UINT32 *&RecordFormID)
    {
    //if((*RecordFormID >> 24) >= ExpandedIndex)
    //    printf("%02X - %08X - %02X\n", (*RecordFormID >> 24), *RecordFormID, ExpandedIndex);
    return ((*RecordFormID >> 24) >= ExpandedIndex);
    }

bool FormIDHandlerClass::IsNewRecord(const UINT32 &RecordFormID)
    {
    //if((RecordFormID >> 24) >= ExpandedIndex)
    //    printf("%02X - %08X - %02X\n", (RecordFormID >> 24), RecordFormID, ExpandedIndex);
    return ((RecordFormID >> 24) >= ExpandedIndex);
    }

bool FormIDHandlerClass::IsValid(const unsigned char *_SrcBuf)
    {
    return (_SrcBuf >= FileStart && _SrcBuf <= FileEnd);
    }

CreateRecordOptions::CreateRecordOptions():
    SetAsOverride(false),
    SetAsWorldCell(false),
    CopyWorldCellStatus(false)
    {
    //
    }

CreateRecordOptions::CreateRecordOptions(UINT32 nFlags):
    SetAsOverride((nFlags & fSetAsOverride) != 0),
    SetAsWorldCell((nFlags & fSetAsWorldCell) != 0),
    CopyWorldCellStatus((nFlags & fCopyWorldCellStatus) != 0)
    {
    //
    }

CreateRecordOptions::~CreateRecordOptions()
    {
    //
    }

UINT32 CreateRecordOptions::GetFlags()
    {
    UINT32 flags = 0;
    if(SetAsOverride)
        flags |= fSetAsOverride;
    if(SetAsWorldCell)
        flags |= fSetAsWorldCell;
    if(CopyWorldCellStatus)
        flags |= fCopyWorldCellStatus;
    return flags;
    }

ModFlags::ModFlags():
    IsMinLoad(true),
    IsFullLoad(false),
    IsNoLoad(false),
    IsSkipNewRecords(false),
    IsInLoadOrder(true),
    IsSaveable(true),
    IsAddMasters(true),
    IsLoadMasters(true),
    IsExtendedConflicts(true),
    IsTrackNewTypes(false),
    IsIndexLANDs(false),
    IsFixupPlaceables(false),
    IsIgnoreExisting(false),
    IsIgnoreAbsentMasters(false),
    LoadedGRUPs(false)
    {
    //
    }

ModFlags::ModFlags(UINT32 _Flags):
    IsMinLoad((_Flags & fIsMinLoad) != 0 && (_Flags & fIsFullLoad) == 0),
    IsFullLoad((_Flags & fIsFullLoad) != 0),
    IsNoLoad(!(IsMinLoad || IsFullLoad)),
    IsSkipNewRecords((_Flags & fIsSkipNewRecords) != 0),
    IsInLoadOrder((_Flags & fIsInLoadOrder) != 0),
    IsSaveable(((_Flags & fIsInLoadOrder) != 0) ? ((_Flags & fIsSaveable) != 0) : false),
    IsAddMasters(((_Flags & fIsIgnoreAbsentMasters) != 0) ? false : ((_Flags & fIsAddMasters) != 0)),
    IsLoadMasters((_Flags & fIsLoadMasters) != 0),
    IsExtendedConflicts((_Flags & fIsExtendedConflicts) != 0),
    IsTrackNewTypes((_Flags & fIsTrackNewTypes) != 0),
    IsIndexLANDs((_Flags & fIsIndexLANDs) != 0),
    IsFixupPlaceables((_Flags & fIsFixupPlaceables) != 0),
    IsIgnoreExisting((_Flags & fIsIgnoreExisting) != 0),
    IsIgnoreAbsentMasters((_Flags & fIsIgnoreAbsentMasters) != 0),
    LoadedGRUPs(false)
    {
    //
    }

ModFlags::~ModFlags()
    {
    //
    }

UINT32 ModFlags::GetFlags()
    {
    UINT32 flags = 0;
    if(IsMinLoad)
        flags |= fIsMinLoad;
    if(IsFullLoad)
        {
        flags |= fIsFullLoad;
        flags &= ~fIsMinLoad;
        }
    if(IsNoLoad)
        {
        flags &= ~fIsFullLoad;
        flags &= ~fIsMinLoad;
        }
    if(IsSkipNewRecords)
        flags |= fIsSkipNewRecords;
    if(IsInLoadOrder)
        flags |= fIsInLoadOrder;
    if(IsSaveable)
        flags |= fIsSaveable;
    if(IsAddMasters)
        flags |= fIsAddMasters;
    if(IsLoadMasters)
        flags |= fIsLoadMasters;
    if(IsExtendedConflicts)
        flags |= fIsExtendedConflicts;
    if(IsTrackNewTypes)
        flags |= fIsTrackNewTypes;
    if(IsIndexLANDs)
        flags |= fIsIndexLANDs;
    if(IsFixupPlaceables)
        flags |= fIsFixupPlaceables;
    if(IsIgnoreExisting)
        flags |= fIsIgnoreExisting;
    if(IsIgnoreAbsentMasters)
        {
        flags &= ~fIsAddMasters;
        flags |= fIsIgnoreAbsentMasters;
        }
    return flags;
    }

StringRecord::StringRecord():value(NULL)
    {
    //
    }

StringRecord::StringRecord(const StringRecord &p):
    value(NULL)
    {
    if(!p.IsLoaded())
        return;
    UINT32 size = p.GetSize();
    value = new char[size];
    memcpy(value, p.value, size);
    }

StringRecord::StringRecord(const STRING p):
    value(NULL)
    {
    if(p == NULL)
        return;
    UINT32 size = (UINT32)strlen(p) + 1;
    value = new char[size];
    strcpy_s(value, size, p);
    }

StringRecord::~StringRecord()
    {
    Unload();
    }

UINT32 StringRecord::GetSize() const
    {
    return (UINT32)strlen(value) + 1;
    }

UINT32 StringRecord::CalcSize() const
    {
    if(value != NULL)
        {
        UINT32 cSize = GetSize();
        cSize += (cSize > 65535) ? 16 : 6;
        return cSize;
        }
    return 0;
    }

bool StringRecord::IsLoaded() const
    {
    return value != NULL;
    }

void StringRecord::Load()
    {
    //
    }

void StringRecord::Unload()
    {
    delete []value;
    value = NULL;
    }

bool StringRecord::Read(unsigned char *buffer, const UINT32 &subSize, UINT32 &curPos)
    {
    if(IsLoaded())
        {
        curPos += subSize;
        return false;
        }
    value = new char[subSize];
    memcpy(value, buffer + curPos, subSize);
    curPos += subSize;
    return true;
    }

void StringRecord::Write(UINT32 _Type, FileWriter &writer)
    {
    if(value != NULL)
        writer.record_write_subrecord(_Type, value, GetSize());
    }

void StringRecord::Copy(const StringRecord &FieldValue)
    {
    Copy(FieldValue.value);
    }

void StringRecord::Copy(STRING FieldValue)
    {
    Unload();
    if(FieldValue != NULL)
        {
        UINT32 size = (UINT32)strlen(FieldValue) + 1;
        value = new char[size];
        strcpy_s(value, size, FieldValue);
        }
    }

bool StringRecord::equals(const StringRecord &other) const
    {
    if(!IsLoaded())
        {
        if(!other.IsLoaded())
            return true;
        }
    else if(other.IsLoaded() && (strcmp(value, other.value) == 0))
        return true;
    return false;
    }

bool StringRecord::equalsi(const StringRecord &other) const
    {
    if(!IsLoaded())
        {
        if(!other.IsLoaded())
            return true;
        }
    else if(other.IsLoaded() && (_stricmp(value, other.value) == 0))
        return true;
    return false;
    }

StringRecord& StringRecord::operator = (const StringRecord &rhs)
    {
    if(this != &rhs)
        Copy(rhs);
    return *this;
    }

NonNullStringRecord::NonNullStringRecord():
    StringRecord()
    {
    //
    }

NonNullStringRecord::NonNullStringRecord(const NonNullStringRecord &p):
    StringRecord()
    {
    Copy(p.value);
    }

NonNullStringRecord::~NonNullStringRecord()
    {
    //
    }

UINT32 NonNullStringRecord::GetSize() const
    {
    return (UINT32)strlen(value);
    }

bool NonNullStringRecord::Read(unsigned char *buffer, const UINT32 &subSize, UINT32 &curPos)
    {
    if(IsLoaded())
        {
        curPos += subSize;
        return false;
        }
    value = new char[subSize + 1];
    value[subSize] = 0x00;
    memcpy(value, buffer + curPos, subSize);
    curPos += subSize;
    return true;
    }

RawRecord::RawRecord():
    size(0),
    value(NULL)
    {
    //
    }

RawRecord::RawRecord(const RawRecord &p):
    value(NULL)
    {
    if(!p.IsLoaded())
        return;
    size = p.size;
    value = new unsigned char[size];
    memcpy(value,p.value,size);
    }

RawRecord::~RawRecord()
    {
    Unload();
    }

UINT32 RawRecord::GetSize() const
    {
    return size;
    }

UINT32 RawRecord::CalcSize() const
    {
    if(value != NULL)
        {
        UINT32 cSize = GetSize();
        cSize += (cSize > 65535) ? 16 : 6;
        return cSize;
        }
    return 0;
    }

bool RawRecord::IsLoaded() const
    {
    return value != NULL;
    }

void RawRecord::Load()
    {
    //
    }

void RawRecord::Unload()
    {
    size = 0;
    delete []value;
    value = NULL;
    }

bool RawRecord::Read(unsigned char *buffer, UINT32 subSize, UINT32 &curPos)
    {
    if(IsLoaded())
        {
        curPos += subSize;
        return false;
        }
    size = subSize;
    value = new unsigned char[size];
    memcpy(value, buffer + curPos, size);
    curPos += subSize;
    return true;
    }

void RawRecord::Write(UINT32 _Type, FileWriter &writer)
    {
    if(value != NULL)
        writer.record_write_subrecord(_Type, value, size);
    }

void RawRecord::Copy(unsigned char *FieldValue, UINT32 nSize)
    {
    delete []value;
    size = nSize;
    value = new unsigned char[size];
    memcpy(value, FieldValue, size);
    }

RawRecord& RawRecord::operator = (const RawRecord &rhs)
    {
    if(this != &rhs)
        {
        if(rhs.IsLoaded())
            Copy(rhs.value, rhs.size);
        else
            Unload();
        }
    return *this;
    }

bool RawRecord::operator ==(const RawRecord &other) const
    {
    if(!IsLoaded())
        {
        if(!other.IsLoaded())
            return true;
        }
    else if(other.IsLoaded() && size == other.size && (memcmp(value, other.value, size) == 0))
        return true;
    return false;
    }

bool RawRecord::operator !=(const RawRecord &other) const
    {
    return !(*this == other);
    }

Function_ArgumentsType FNVFunction_ArgumentsInit[] =
    {
    Function_ArgumentsType(1,std::make_pair(eFORMID,eNONE)),      //GetDistance
    Function_ArgumentsType(5,std::make_pair(eNONE,eNONE)),        //GetLocked
    Function_ArgumentsType(6,std::make_pair(eUINT32,eNONE)),      //GetPos
    Function_ArgumentsType(8,std::make_pair(eUINT32,eNONE)),      //GetAngle
    Function_ArgumentsType(10,std::make_pair(eUINT32,eNONE)),     //GetStartingPos
    Function_ArgumentsType(11,std::make_pair(eUINT32,eNONE)),     //GetStartingAngle
    Function_ArgumentsType(12,std::make_pair(eNONE,eNONE)),       //GetSecondsPassed
    Function_ArgumentsType(14,std::make_pair(eUINT32,eNONE)),     //GetActorValue
    Function_ArgumentsType(18,std::make_pair(eNONE,eNONE)),       //GetCurrentTime
    Function_ArgumentsType(24,std::make_pair(eNONE,eNONE)),       //GetScale
    Function_ArgumentsType(25,std::make_pair(eNONE,eNONE)),       //IsMoving
    Function_ArgumentsType(26,std::make_pair(eNONE,eNONE)),       //IsTurning
    Function_ArgumentsType(27,std::make_pair(eFORMID,eNONE)),     //GetLineOfSight
    Function_ArgumentsType(32,std::make_pair(eFORMID,eNONE)),     //GetInSameCell
    Function_ArgumentsType(35,std::make_pair(eNONE,eNONE)),       //GetDisabled
    Function_ArgumentsType(36,std::make_pair(eUINT32,eNONE)),     //MenuMode
    Function_ArgumentsType(39,std::make_pair(eNONE,eNONE)),       //GetDisease
    Function_ArgumentsType(40,std::make_pair(eNONE,eNONE)),       //GetVampire
    Function_ArgumentsType(41,std::make_pair(eNONE,eNONE)),       //GetClothingValue
    Function_ArgumentsType(42,std::make_pair(eFORMID,eNONE)),     //SameFaction
    Function_ArgumentsType(43,std::make_pair(eFORMID,eNONE)),     //SameRace
    Function_ArgumentsType(44,std::make_pair(eFORMID,eNONE)),     //SameSex
    Function_ArgumentsType(45,std::make_pair(eFORMID,eNONE)),     //GetDetected
    Function_ArgumentsType(46,std::make_pair(eNONE,eNONE)),       //GetDead
    Function_ArgumentsType(47,std::make_pair(eFORMID,eNONE)),     //GetItemCount
    Function_ArgumentsType(48,std::make_pair(eNONE,eNONE)),       //GetGold
    Function_ArgumentsType(49,std::make_pair(eNONE,eNONE)),       //GetSleeping
    Function_ArgumentsType(50,std::make_pair(eNONE,eNONE)),       //GetTalkedToPC
    Function_ArgumentsType(53,std::make_pair(eFORMID,eUINT32)),   //GetScriptVariable
    Function_ArgumentsType(56,std::make_pair(eFORMID,eNONE)),     //GetQuestRunning
    Function_ArgumentsType(58,std::make_pair(eFORMID,eNONE)),     //GetStage
    Function_ArgumentsType(59,std::make_pair(eFORMID,eUINT32)),   //GetStageDone
    Function_ArgumentsType(60,std::make_pair(eFORMID,eFORMID)),   //GetFactionRankDifference
    Function_ArgumentsType(61,std::make_pair(eNONE,eNONE)),       //GetAlarmed
    Function_ArgumentsType(62,std::make_pair(eNONE,eNONE)),       //IsRaining
    Function_ArgumentsType(63,std::make_pair(eNONE,eNONE)),       //GetAttacked
    Function_ArgumentsType(64,std::make_pair(eNONE,eNONE)),       //GetIsCreature
    Function_ArgumentsType(65,std::make_pair(eNONE,eNONE)),       //GetLockLevel
    Function_ArgumentsType(66,std::make_pair(eFORMID,eNONE)),     //GetShouldAttack
    Function_ArgumentsType(67,std::make_pair(eFORMID,eNONE)),     //GetInCell
    Function_ArgumentsType(68,std::make_pair(eFORMID,eNONE)),     //GetIsClass
    Function_ArgumentsType(69,std::make_pair(eFORMID,eNONE)),     //GetIsRace
    Function_ArgumentsType(70,std::make_pair(eUINT32,eNONE)),     //GetIsSex
    Function_ArgumentsType(71,std::make_pair(eFORMID,eNONE)),     //GetInFaction
    Function_ArgumentsType(72,std::make_pair(eFORMID,eNONE)),     //GetIsID
    Function_ArgumentsType(73,std::make_pair(eFORMID,eNONE)),     //GetFactionRank
    Function_ArgumentsType(74,std::make_pair(eFORMID,eNONE)),     //GetGlobalValue
    Function_ArgumentsType(75,std::make_pair(eNONE,eNONE)),       //IsSnowing
    Function_ArgumentsType(76,std::make_pair(eFORMID,eNONE)),     //GetDisposition
    Function_ArgumentsType(77,std::make_pair(eNONE,eNONE)),       //GetRandomPercent
    Function_ArgumentsType(79,std::make_pair(eFORMID,eUINT32)),   //GetQuestVariable
    Function_ArgumentsType(80,std::make_pair(eNONE,eNONE)),       //GetLevel
    Function_ArgumentsType(81,std::make_pair(eNONE,eNONE)),       //GetArmorRating
    Function_ArgumentsType(84,std::make_pair(eFORMID,eNONE)),     //GetDeadCount
    Function_ArgumentsType(91,std::make_pair(eNONE,eNONE)),       //GetIsAlerted
    Function_ArgumentsType(98,std::make_pair(eUINT32,eUINT32)),   //GetPlayerControlsDisabled
    Function_ArgumentsType(99,std::make_pair(eFORMID,eNONE)),     //GetHeadingAngle
    Function_ArgumentsType(101,std::make_pair(eNONE,eNONE)),      //IsWeaponOut
    Function_ArgumentsType(102,std::make_pair(eNONE,eNONE)),      //IsTorchOut
    Function_ArgumentsType(103,std::make_pair(eNONE,eNONE)),      //IsShieldOut
    Function_ArgumentsType(106,std::make_pair(eNONE,eNONE)),      //IsFacingUp
    Function_ArgumentsType(107,std::make_pair(eNONE,eNONE)),      //GetKnockedState
    Function_ArgumentsType(108,std::make_pair(eNONE,eNONE)),      //GetWeaponAnimType
    Function_ArgumentsType(109,std::make_pair(eUINT32,eNONE)),    //IsWeaponSkillType
    Function_ArgumentsType(110,std::make_pair(eNONE,eNONE)),      //GetCurrentAIPackage
    Function_ArgumentsType(111,std::make_pair(eNONE,eNONE)),      //IsWaiting
    Function_ArgumentsType(112,std::make_pair(eNONE,eNONE)),      //IsIdlePlaying
    Function_ArgumentsType(116,std::make_pair(eNONE,eNONE)),      //GetMinorCrimeCount
    Function_ArgumentsType(117,std::make_pair(eNONE,eNONE)),      //GetMajorCrimeCount
    Function_ArgumentsType(118,std::make_pair(eNONE,eNONE)),      //GetActorAggroRadiusViolated
    Function_ArgumentsType(122,std::make_pair(eFORMID,eUINT32)),  //GetCrime
    Function_ArgumentsType(123,std::make_pair(eNONE,eNONE)),      //IsGreetingPlayer
    Function_ArgumentsType(125,std::make_pair(eNONE,eNONE)),      //IsGuard
    Function_ArgumentsType(127,std::make_pair(eNONE,eNONE)),      //HasBeenEaten
    Function_ArgumentsType(128,std::make_pair(eNONE,eNONE)),      //GetFatiguePercentage
    Function_ArgumentsType(129,std::make_pair(eFORMID,eNONE)),    //GetPCIsClass
    Function_ArgumentsType(130,std::make_pair(eFORMID,eNONE)),    //GetPCIsRace
    Function_ArgumentsType(131,std::make_pair(eUINT32,eNONE)),    //GetPCIsSex
    Function_ArgumentsType(132,std::make_pair(eFORMID,eNONE)),    //GetPCInFaction
    Function_ArgumentsType(133,std::make_pair(eNONE,eNONE)),      //SameFactionAsPC
    Function_ArgumentsType(134,std::make_pair(eNONE,eNONE)),      //SameRaceAsPC
    Function_ArgumentsType(135,std::make_pair(eNONE,eNONE)),      //SameSexAsPC
    Function_ArgumentsType(136,std::make_pair(eFORMID,eNONE)),    //GetIsReference
    Function_ArgumentsType(141,std::make_pair(eNONE,eNONE)),      //IsTalking
    Function_ArgumentsType(142,std::make_pair(eNONE,eNONE)),      //GetWalkSpeed
    Function_ArgumentsType(143,std::make_pair(eNONE,eNONE)),      //GetCurrentAIProcedure
    Function_ArgumentsType(144,std::make_pair(eNONE,eNONE)),      //GetTrespassWarningLevel
    Function_ArgumentsType(145,std::make_pair(eNONE,eNONE)),      //IsTrespassing
    Function_ArgumentsType(146,std::make_pair(eNONE,eNONE)),      //IsInMyOwnedCell
    Function_ArgumentsType(147,std::make_pair(eNONE,eNONE)),      //GetWindSpeed
    Function_ArgumentsType(148,std::make_pair(eNONE,eNONE)),      //GetCurrentWeatherPercent
    Function_ArgumentsType(149,std::make_pair(eFORMID,eNONE)),    //GetIsCurrentWeather
    Function_ArgumentsType(150,std::make_pair(eNONE,eNONE)),      //IsContinuingPackagePCNear
    Function_ArgumentsType(153,std::make_pair(eNONE,eNONE)),      //CanHaveFlames
    Function_ArgumentsType(154,std::make_pair(eNONE,eNONE)),      //HasFlames
    Function_ArgumentsType(157,std::make_pair(eNONE,eNONE)),      //GetOpenState
    Function_ArgumentsType(159,std::make_pair(eNONE,eNONE)),      //GetSitting
    Function_ArgumentsType(160,std::make_pair(eNONE,eNONE)),      //GetFurnitureMarkerID
    Function_ArgumentsType(161,std::make_pair(eFORMID,eNONE)),    //GetIsCurrentPackage
    Function_ArgumentsType(162,std::make_pair(eFORMID,eNONE)),    //IsCurrentFurnitureRef
    Function_ArgumentsType(163,std::make_pair(eFORMID,eNONE)),    //IsCurrentFurnitureObj
    Function_ArgumentsType(170,std::make_pair(eNONE,eNONE)),      //GetDayOfWeek
    Function_ArgumentsType(172,std::make_pair(eFORMID,eNONE)),    //GetTalkedToPCParam
    Function_ArgumentsType(175,std::make_pair(eNONE,eNONE)),      //IsPCSleeping
    Function_ArgumentsType(176,std::make_pair(eNONE,eNONE)),      //IsPCAMurderer
    Function_ArgumentsType(180,std::make_pair(eFORMID,eNONE)),    //GetDetectionLevel
    Function_ArgumentsType(182,std::make_pair(eFORMID,eNONE)),    //GetEquipped
    Function_ArgumentsType(185,std::make_pair(eNONE,eNONE)),      //IsSwimming
    Function_ArgumentsType(190,std::make_pair(eNONE,eNONE)),      //GetAmountSoldStolen
    Function_ArgumentsType(192,std::make_pair(eNONE,eNONE)),      //GetIgnoreCrime
    Function_ArgumentsType(193,std::make_pair(eFORMID,eNONE)),    //GetPCExpelled
    Function_ArgumentsType(195,std::make_pair(eFORMID,eNONE)),    //GetPCFactionMurder
    Function_ArgumentsType(197,std::make_pair(eFORMID,eNONE)),    //GetPCEnemyofFaction
    Function_ArgumentsType(199,std::make_pair(eFORMID,eNONE)),    //GetPCFactionAttack
    Function_ArgumentsType(203,std::make_pair(eNONE,eNONE)),      //GetDestroyed
    Function_ArgumentsType(214,std::make_pair(eFORMID,eNONE)),    //HasMagicEffect
    Function_ArgumentsType(215,std::make_pair(eNONE,eNONE)),      //GetDefaultOpen
    Function_ArgumentsType(219,std::make_pair(eNONE,eNONE)),      //GetAnimAction
    Function_ArgumentsType(223,std::make_pair(eFORMID,eNONE)),    //IsSpellTarget
    Function_ArgumentsType(224,std::make_pair(eNONE,eNONE)),      //GetVATSMode
    Function_ArgumentsType(225,std::make_pair(eNONE,eNONE)),      //GetPersuasionNumber
    Function_ArgumentsType(226,std::make_pair(eNONE,eNONE)),      //GetSandman
    Function_ArgumentsType(227,std::make_pair(eNONE,eNONE)),      //GetCannibal
    Function_ArgumentsType(228,std::make_pair(eFORMID,eNONE)),    //GetIsClassDefault
    Function_ArgumentsType(229,std::make_pair(eNONE,eNONE)),      //GetClassDefaultMatch
    Function_ArgumentsType(230,std::make_pair(eFORMID,eFORMID)),  //GetInCellParam
    Function_ArgumentsType(235,std::make_pair(eNONE,eNONE)),      //GetVatsTargetHeight
    Function_ArgumentsType(237,std::make_pair(eNONE,eNONE)),      //GetIsGhost
    Function_ArgumentsType(242,std::make_pair(eNONE,eNONE)),      //GetUnconscious
    Function_ArgumentsType(244,std::make_pair(eNONE,eNONE)),      //GetRestrained
    Function_ArgumentsType(246,std::make_pair(eFORMID,eNONE)),    //GetIsUsedItem
    Function_ArgumentsType(247,std::make_pair(eUINT32,eNONE)),    //GetIsUsedItemType
    Function_ArgumentsType(254,std::make_pair(eNONE,eNONE)),      //GetIsPlayableRace
    Function_ArgumentsType(255,std::make_pair(eNONE,eNONE)),      //GetOffersServicesNow
    Function_ArgumentsType(258,std::make_pair(eNONE,eNONE)),      //GetUsedItemLevel
    Function_ArgumentsType(259,std::make_pair(eNONE,eNONE)),      //GetUsedItemActivate
    Function_ArgumentsType(264,std::make_pair(eNONE,eNONE)),      //GetBarterGold
    Function_ArgumentsType(265,std::make_pair(eNONE,eNONE)),      //IsTimePassing
    Function_ArgumentsType(266,std::make_pair(eNONE,eNONE)),      //IsPleasant
    Function_ArgumentsType(267,std::make_pair(eNONE,eNONE)),      //IsCloudy
    Function_ArgumentsType(274,std::make_pair(eNONE,eNONE)),      //GetArmorRatingUpperBody
    Function_ArgumentsType(277,std::make_pair(eUINT32,eNONE)),    //GetBaseActorValue
    Function_ArgumentsType(278,std::make_pair(eFORMID,eNONE)),    //IsOwner
    Function_ArgumentsType(280,std::make_pair(eFORMID,eFORMID)),  //IsCellOwner
    Function_ArgumentsType(282,std::make_pair(eNONE,eNONE)),      //IsHorseStolen
    Function_ArgumentsType(285,std::make_pair(eNONE,eNONE)),      //IsLeftUp
    Function_ArgumentsType(286,std::make_pair(eNONE,eNONE)),      //IsSneaking
    Function_ArgumentsType(287,std::make_pair(eNONE,eNONE)),      //IsRunning
    Function_ArgumentsType(288,std::make_pair(eNONE,eNONE)),      //GetFriendHit
    Function_ArgumentsType(289,std::make_pair(eNONE,eNONE)),      //IsInCombat
    Function_ArgumentsType(300,std::make_pair(eNONE,eNONE)),      //IsInInterior
    Function_ArgumentsType(304,std::make_pair(eNONE,eNONE)),      //IsWaterObject
    Function_ArgumentsType(306,std::make_pair(eNONE,eNONE)),      //IsActorUsingATorch
    Function_ArgumentsType(309,std::make_pair(eNONE,eNONE)),      //IsXBox
    Function_ArgumentsType(310,std::make_pair(eFORMID,eNONE)),    //GetInWorldspace
    Function_ArgumentsType(312,std::make_pair(eUINT32,eNONE)),    //GetPCMiscStat
    Function_ArgumentsType(313,std::make_pair(eNONE,eNONE)),      //IsActorEvil
    Function_ArgumentsType(314,std::make_pair(eNONE,eNONE)),      //IsActorAVictim
    Function_ArgumentsType(315,std::make_pair(eNONE,eNONE)),      //GetTotalPersuasionNumber
    Function_ArgumentsType(318,std::make_pair(eNONE,eNONE)),      //GetIdleDoneOnce
    Function_ArgumentsType(320,std::make_pair(eNONE,eNONE)),      //GetNoRumors
    Function_ArgumentsType(323,std::make_pair(eNONE,eNONE)),      //WhichServiceMenu
    Function_ArgumentsType(327,std::make_pair(eNONE,eNONE)),      //IsRidingHorse
    Function_ArgumentsType(332,std::make_pair(eNONE,eNONE)),      //IsInDangerousWater
    Function_ArgumentsType(338,std::make_pair(eNONE,eNONE)),      //GetIgnoreFriendlyHits
    Function_ArgumentsType(339,std::make_pair(eNONE,eNONE)),      //IsPlayersLastRiddenHorse
    Function_ArgumentsType(353,std::make_pair(eNONE,eNONE)),      //IsActor
    Function_ArgumentsType(354,std::make_pair(eNONE,eNONE)),      //IsEssential
    Function_ArgumentsType(358,std::make_pair(eNONE,eNONE)),      //IsPlayerMovingIntoNewSpace
    Function_ArgumentsType(361,std::make_pair(eNONE,eNONE)),      //GetTimeDead
    Function_ArgumentsType(362,std::make_pair(eNONE,eNONE)),      //GetPlayerHasLastRiddenHorse
    Function_ArgumentsType(365,std::make_pair(eNONE,eNONE)),      //IsChild
    Function_ArgumentsType(367,std::make_pair(eNONE,eNONE)),      //GetLastPlayerAction
    Function_ArgumentsType(368,std::make_pair(eUINT32,eNONE)),    //IsPlayerActionActive
    Function_ArgumentsType(370,std::make_pair(eFORMID,eNONE)),    //IsTalkingActivatorActor
    Function_ArgumentsType(372,std::make_pair(eFORMID,eNONE)),    //IsInList
    Function_ArgumentsType(382,std::make_pair(eFORMID,eNONE)),    //GetHasNote
    Function_ArgumentsType(391,std::make_pair(eNONE,eNONE)),      //GetHitLocation
    Function_ArgumentsType(392,std::make_pair(eNONE,eNONE)),      //IsPC1stPerson
    Function_ArgumentsType(397,std::make_pair(eNONE,eNONE)),      //GetCauseofDeath
    Function_ArgumentsType(398,std::make_pair(eUINT32,eNONE)),    //IsLimbGone
    Function_ArgumentsType(399,std::make_pair(eFORMID,eNONE)),    //IsWeaponInList
    Function_ArgumentsType(403,std::make_pair(eNONE,eNONE)),      //HasFriendDisposition
    Function_ArgumentsType(408,std::make_pair(eUINT32,eUINT32)),  //GetVATSValue
    Function_ArgumentsType(409,std::make_pair(eFORMID,eNONE)),    //IsKiller
    Function_ArgumentsType(410,std::make_pair(eFORMID,eNONE)),    //IsKillerObject
    Function_ArgumentsType(411,std::make_pair(eFORMID,eFORMID)),  //GetFactionCombatReaction
    Function_ArgumentsType(415,std::make_pair(eFORMID,eNONE)),    //Exists
    Function_ArgumentsType(416,std::make_pair(eNONE,eNONE)),      //GetGroupMemberCount
    Function_ArgumentsType(417,std::make_pair(eNONE,eNONE)),      //GetGroupTargetCount
    Function_ArgumentsType(420,std::make_pair(eFORMID,eFORMID)),  //GetObjectiveCompleted
    Function_ArgumentsType(421,std::make_pair(eFORMID,eFORMID)),  //GetObjectiveDisplayed
    Function_ArgumentsType(427,std::make_pair(eFORMID,eNONE)),    //GetIsVoiceType
    Function_ArgumentsType(428,std::make_pair(eNONE,eNONE)),      //GetPlantedExplosive
    Function_ArgumentsType(430,std::make_pair(eNONE,eNONE)),      //IsActorTalkingThroughActivator
    Function_ArgumentsType(431,std::make_pair(eNONE,eNONE)),      //GetHealthPercentage
    Function_ArgumentsType(433,std::make_pair(eUINT32,eNONE)),    //GetIsObjectType
    Function_ArgumentsType(435,std::make_pair(eNONE,eNONE)),      //GetDialogueEmotion
    Function_ArgumentsType(436,std::make_pair(eNONE,eNONE)),      //GetDialogueEmotionValue
    Function_ArgumentsType(438,std::make_pair(eUINT32,eNONE)),    //GetIsCreatureType
    Function_ArgumentsType(446,std::make_pair(eFORMID,eNONE)),    //GetInZone
    Function_ArgumentsType(449,std::make_pair(eFORMID,eUINT32)),  //HasPerk
    Function_ArgumentsType(450,std::make_pair(eFORMID,eNONE)),    //GetFactionRelation
    Function_ArgumentsType(451,std::make_pair(eFORMID,eNONE)),    //IsLastIdlePlayed
    Function_ArgumentsType(454,std::make_pair(eNONE,eNONE)),      //GetPlayerTeammate
    Function_ArgumentsType(455,std::make_pair(eNONE,eNONE)),      //GetPlayerTeammateCount
    Function_ArgumentsType(459,std::make_pair(eNONE,eNONE)),      //GetActorCrimePlayerEnemy
    Function_ArgumentsType(460,std::make_pair(eNONE,eNONE)),      //GetActorFactionPlayerEnemy
    Function_ArgumentsType(462,std::make_pair(eUINT32,eNONE)),    //IsPlayerTagSkill
    Function_ArgumentsType(464,std::make_pair(eFORMID,eNONE)),    //IsPlayerGrabbedRef
    Function_ArgumentsType(471,std::make_pair(eNONE,eNONE)),      //GetDestructionStage
    Function_ArgumentsType(474,std::make_pair(eUINT32,eNONE)),    //GetIsAlignment
    Function_ArgumentsType(478,std::make_pair(eFORMID,eNONE)),    //GetThreatRatio
    Function_ArgumentsType(480,std::make_pair(eUINT32,eNONE)),    //GetIsUsedItemEquipType
    Function_ArgumentsType(489,std::make_pair(eNONE,eNONE)),      //GetConcussed
    Function_ArgumentsType(492,std::make_pair(eNONE,eNONE)),      //GetMapMarkerVisible
    Function_ArgumentsType(495,std::make_pair(eUINT32,eNONE)),    //GetPermanentActorValue
    Function_ArgumentsType(496,std::make_pair(eNONE,eNONE)),      //GetKillingBlowLimb
    Function_ArgumentsType(500,std::make_pair(eNONE,eNONE)),      //GetWeaponHealthPerc
    Function_ArgumentsType(503,std::make_pair(eNONE,eNONE)),      //GetRadiationLevel
    Function_ArgumentsType(510,std::make_pair(eNONE,eNONE)),      //GetLastHitCritical
    Function_ArgumentsType(515,std::make_pair(eFORMID,eNONE)),    //IsCombatTarget
    Function_ArgumentsType(518,std::make_pair(eFORMID,eNONE)),    //GetVATSRightAreaFree
    Function_ArgumentsType(519,std::make_pair(eFORMID,eNONE)),    //GetVATSLeftAreaFree
    Function_ArgumentsType(520,std::make_pair(eFORMID,eNONE)),    //GetVATSBackAreaFree
    Function_ArgumentsType(521,std::make_pair(eFORMID,eNONE)),    //GetVATSFrontAreaFree
    Function_ArgumentsType(522,std::make_pair(eNONE,eNONE)),      //GetIsLockBroken
    Function_ArgumentsType(523,std::make_pair(eNONE,eNONE)),      //IsPS3
    Function_ArgumentsType(524,std::make_pair(eNONE,eNONE)),      //IsWin32
    Function_ArgumentsType(525,std::make_pair(eFORMID,eNONE)),    //GetVATSRightTargetVisible
    Function_ArgumentsType(526,std::make_pair(eFORMID,eNONE)),    //GetVATSLeftTargetVisible
    Function_ArgumentsType(527,std::make_pair(eFORMID,eNONE)),    //GetVATSBackTargetVisible
    Function_ArgumentsType(528,std::make_pair(eFORMID,eNONE)),    //GetVATSFrontTargetVisible
    Function_ArgumentsType(531,std::make_pair(eUINT32,eNONE)),    //IsInCriticalStage
    Function_ArgumentsType(533,std::make_pair(eNONE,eNONE)),      //GetXPForNextLevel
    Function_ArgumentsType(546,std::make_pair(eFORMID,eNONE)),    //GetQuestCompleted
    Function_ArgumentsType(550,std::make_pair(eNONE,eNONE)),      //IsGoreDisabled
    Function_ArgumentsType(555,std::make_pair(eFORMID,eNONE)),    //GetSpellUsageNum
    Function_ArgumentsType(557,std::make_pair(eNONE,eNONE)),      //GetActorsInHigh
    Function_ArgumentsType(558,std::make_pair(eNONE,eNONE)),      //HasLoaded3D
    Function_ArgumentsType(573,std::make_pair(eFORMID,eUINT32)),  //GetReputation
    Function_ArgumentsType(574,std::make_pair(eFORMID,eUINT32)),  //GetReputationPct
    Function_ArgumentsType(575,std::make_pair(eFORMID,eUINT32)),  //GetReputationThreshold
    Function_ArgumentsType(586,std::make_pair(eNONE,eNONE)),      //IsHardcore
    Function_ArgumentsType(601,std::make_pair(eNONE,eNONE)),      //GetForceHitReaction
    Function_ArgumentsType(607,std::make_pair(eFORMID,eNONE)),    //ChallengeLocked
    Function_ArgumentsType(610,std::make_pair(eFORMID,eNONE)),    //GetCasinoWinningStage
    Function_ArgumentsType(612,std::make_pair(eFORMID,eNONE)),    //PlayerInRegion
    Function_ArgumentsType(614,std::make_pair(eFORMID,eNONE)),    //GetChallengeCompleted
    Function_ArgumentsType(619,std::make_pair(eNONE,eNONE))      //IsAlwaysHardcore
    };


Function_ArgumentsType Function_ArgumentsInit[] =
    {
    Function_ArgumentsType(1,std::make_pair(eFORMID,eNONE)),     //GetDistance
    Function_ArgumentsType(5,std::make_pair(eNONE,eNONE)),       //GetLocked
    Function_ArgumentsType(6,std::make_pair(eUINT32,eNONE)),     //GetPos
    Function_ArgumentsType(8,std::make_pair(eUINT32,eNONE)),     //GetAngle
    Function_ArgumentsType(10,std::make_pair(eUINT32,eNONE)),    //GetStartingPos
    Function_ArgumentsType(11,std::make_pair(eUINT32,eNONE)),    //GetStartingAngle
    Function_ArgumentsType(12,std::make_pair(eNONE,eNONE)),      //GetSecondsPassed
    Function_ArgumentsType(14,std::make_pair(eUINT32,eNONE)),    //GetActorValue
    Function_ArgumentsType(18,std::make_pair(eNONE,eNONE)),      //GetCurrentTime
    Function_ArgumentsType(24,std::make_pair(eNONE,eNONE)),      //GetScale
    Function_ArgumentsType(27,std::make_pair(eFORMID,eNONE)),    //GetLineOfSight
    Function_ArgumentsType(32,std::make_pair(eFORMID,eNONE)),    //GetInSameCell
    Function_ArgumentsType(35,std::make_pair(eNONE,eNONE)),      //GetDisabled
    Function_ArgumentsType(36,std::make_pair(eUINT32,eNONE)),    //MenuMode
    Function_ArgumentsType(39,std::make_pair(eNONE,eNONE)),      //GetDisease
    Function_ArgumentsType(40,std::make_pair(eNONE,eNONE)),      //GetVampire
    Function_ArgumentsType(41,std::make_pair(eNONE,eNONE)),      //GetClothingValue
    Function_ArgumentsType(42,std::make_pair(eFORMID,eNONE)),    //SameFaction
    Function_ArgumentsType(43,std::make_pair(eFORMID,eNONE)),    //SameRace
    Function_ArgumentsType(44,std::make_pair(eFORMID,eNONE)),    //SameSex
    Function_ArgumentsType(45,std::make_pair(eFORMID,eNONE)),    //GetDetected
    Function_ArgumentsType(46,std::make_pair(eNONE,eNONE)),      //GetDead
    Function_ArgumentsType(47,std::make_pair(eFORMID,eNONE)),    //GetItemCount
    Function_ArgumentsType(48,std::make_pair(eNONE,eNONE)),      //GetGold
    Function_ArgumentsType(49,std::make_pair(eNONE,eNONE)),      //GetSleeping
    Function_ArgumentsType(50,std::make_pair(eNONE,eNONE)),      //GetTalkedToPC
    Function_ArgumentsType(53,std::make_pair(eFORMID,eUINT32)),  //GetScriptVariable
    Function_ArgumentsType(56,std::make_pair(eFORMID,eNONE)),    //GetQuestRunning
    Function_ArgumentsType(58,std::make_pair(eFORMID,eNONE)),    //GetStage
    Function_ArgumentsType(59,std::make_pair(eFORMID,eUINT32)),  //GetStageDone
    Function_ArgumentsType(60,std::make_pair(eFORMID,eFORMID)),  //GetFactionRankDifference
    Function_ArgumentsType(61,std::make_pair(eNONE,eNONE)),      //GetAlarmed
    Function_ArgumentsType(62,std::make_pair(eNONE,eNONE)),      //IsRaining
    Function_ArgumentsType(63,std::make_pair(eNONE,eNONE)),      //GetAttacked
    Function_ArgumentsType(64,std::make_pair(eNONE,eNONE)),      //GetIsCreature
    Function_ArgumentsType(65,std::make_pair(eNONE,eNONE)),      //GetLockLevel
    Function_ArgumentsType(66,std::make_pair(eFORMID,eNONE)),    //GetShouldAttack
    Function_ArgumentsType(67,std::make_pair(eFORMID,eNONE)),    //GetInCell
    Function_ArgumentsType(68,std::make_pair(eFORMID,eNONE)),    //GetIsClass
    Function_ArgumentsType(69,std::make_pair(eFORMID,eNONE)),    //GetIsRace
    Function_ArgumentsType(70,std::make_pair(eUINT32,eNONE)),    //GetIsSex
    Function_ArgumentsType(71,std::make_pair(eFORMID,eNONE)),    //GetInFaction
    Function_ArgumentsType(72,std::make_pair(eFORMID,eNONE)),    //GetIsID
    Function_ArgumentsType(73,std::make_pair(eFORMID,eNONE)),    //GetFactionRank
    Function_ArgumentsType(74,std::make_pair(eFORMID,eNONE)),    //GetGlobalValue
    Function_ArgumentsType(75,std::make_pair(eNONE,eNONE)),      //IsSnowing
    Function_ArgumentsType(76,std::make_pair(eFORMID,eNONE)),    //GetDisposition
    Function_ArgumentsType(77,std::make_pair(eNONE,eNONE)),      //GetRandomPercent
    Function_ArgumentsType(79,std::make_pair(eFORMID,eUINT32)),  //GetQuestVariable
    Function_ArgumentsType(80,std::make_pair(eNONE,eNONE)),      //GetLevel
    Function_ArgumentsType(81,std::make_pair(eNONE,eNONE)),      //GetArmorRating
    Function_ArgumentsType(84,std::make_pair(eFORMID,eNONE)),    //GetDeadCount
    Function_ArgumentsType(91,std::make_pair(eNONE,eNONE)),      //GetIsAlerted
    Function_ArgumentsType(98,std::make_pair(eNONE,eNONE)),      //GetPlayerControlsDisabled
    Function_ArgumentsType(99,std::make_pair(eFORMID,eNONE)),    //GetHeadingAngle
    Function_ArgumentsType(101,std::make_pair(eNONE,eNONE)),     //IsWeaponOut
    Function_ArgumentsType(102,std::make_pair(eNONE,eNONE)),     //IsTorchOut
    Function_ArgumentsType(103,std::make_pair(eNONE,eNONE)),     //IsShieldOut
    Function_ArgumentsType(104,std::make_pair(eNONE,eNONE)),     //IsYielding
    Function_ArgumentsType(106,std::make_pair(eNONE,eNONE)),     //IsFacingUp
    Function_ArgumentsType(107,std::make_pair(eNONE,eNONE)),     //GetKnockedState
    Function_ArgumentsType(108,std::make_pair(eNONE,eNONE)),     //GetWeaponAnimType
    Function_ArgumentsType(109,std::make_pair(eNONE,eNONE)),     //GetWeaponSkillType
    Function_ArgumentsType(110,std::make_pair(eNONE,eNONE)),     //GetCurrentAIPackage
    Function_ArgumentsType(111,std::make_pair(eNONE,eNONE)),     //IsWaiting
    Function_ArgumentsType(112,std::make_pair(eNONE,eNONE)),     //IsIdlePlaying
    Function_ArgumentsType(116,std::make_pair(eNONE,eNONE)),     //GetCrimeGold
    Function_ArgumentsType(122,std::make_pair(eFORMID,eUINT32)), //GetCrime
    Function_ArgumentsType(125,std::make_pair(eNONE,eNONE)),     //IsGuard
    Function_ArgumentsType(127,std::make_pair(eNONE,eNONE)),     //CanPayCrimeGold
    Function_ArgumentsType(128,std::make_pair(eNONE,eNONE)),     //GetFatiguePercentage
    Function_ArgumentsType(129,std::make_pair(eFORMID,eNONE)),   //GetPCIsClass
    Function_ArgumentsType(130,std::make_pair(eFORMID,eNONE)),   //GetPCIsRace
    Function_ArgumentsType(131,std::make_pair(eUINT32,eNONE)),   //GetPCIsSex
    Function_ArgumentsType(132,std::make_pair(eFORMID,eNONE)),   //GetPCInFaction
    Function_ArgumentsType(133,std::make_pair(eNONE,eNONE)),     //SameFactionAsPC
    Function_ArgumentsType(134,std::make_pair(eNONE,eNONE)),     //SameRaceAsPC
    Function_ArgumentsType(135,std::make_pair(eNONE,eNONE)),     //SameSexAsPC
    Function_ArgumentsType(136,std::make_pair(eFORMID,eNONE)),   //GetIsReference
    Function_ArgumentsType(141,std::make_pair(eNONE,eNONE)),     //IsTalking
    Function_ArgumentsType(142,std::make_pair(eNONE,eNONE)),     //GetWalkSpeed
    Function_ArgumentsType(143,std::make_pair(eNONE,eNONE)),     //GetCurrentAIProcedure
    Function_ArgumentsType(144,std::make_pair(eNONE,eNONE)),     //GetTrespassWarningLevel
    Function_ArgumentsType(145,std::make_pair(eNONE,eNONE)),     //IsTrespassing
    Function_ArgumentsType(146,std::make_pair(eNONE,eNONE)),     //IsInMyOwnedCell
    Function_ArgumentsType(147,std::make_pair(eNONE,eNONE)),     //GetWindSpeed
    Function_ArgumentsType(148,std::make_pair(eNONE,eNONE)),     //GetCurrentWeatherPercent
    Function_ArgumentsType(149,std::make_pair(eFORMID,eNONE)),   //GetIsCurrentWeather
    Function_ArgumentsType(150,std::make_pair(eNONE,eNONE)),     //IsContinuingPackagePCNear
    Function_ArgumentsType(153,std::make_pair(eNONE,eNONE)),     //CanHaveFlames
    Function_ArgumentsType(154,std::make_pair(eNONE,eNONE)),     //HasFlames
    Function_ArgumentsType(157,std::make_pair(eNONE,eNONE)),     //GetOpenState
    Function_ArgumentsType(159,std::make_pair(eNONE,eNONE)),     //GetSitting
    Function_ArgumentsType(160,std::make_pair(eNONE,eNONE)),     //GetFurnitureMarkerID
    Function_ArgumentsType(161,std::make_pair(eFORMID,eNONE)),   //GetIsCurrentPackage
    Function_ArgumentsType(162,std::make_pair(eFORMID,eNONE)),   //IsCurrentFurnitureRef
    Function_ArgumentsType(163,std::make_pair(eFORMID,eNONE)),   //IsCurrentFurnitureObj
    Function_ArgumentsType(170,std::make_pair(eNONE,eNONE)),     //GetDayOfWeek
    Function_ArgumentsType(171,std::make_pair(eNONE,eNONE)),     //IsPlayerInJail
    Function_ArgumentsType(172,std::make_pair(eFORMID,eNONE)),   //GetTalkedToPCParam
    Function_ArgumentsType(175,std::make_pair(eNONE,eNONE)),     //IsPCSleeping
    Function_ArgumentsType(176,std::make_pair(eNONE,eNONE)),     //IsPCAMurderer
    Function_ArgumentsType(180,std::make_pair(eFORMID,eNONE)),   //GetDetectionLevel
    Function_ArgumentsType(182,std::make_pair(eFORMID,eNONE)),   //GetEquipped
    Function_ArgumentsType(185,std::make_pair(eNONE,eNONE)),     //IsSwimming
    Function_ArgumentsType(190,std::make_pair(eNONE,eNONE)),     //GetAmountSoldStolen
    Function_ArgumentsType(193,std::make_pair(eFORMID,eNONE)),   //GetPCExpelled
    Function_ArgumentsType(195,std::make_pair(eFORMID,eNONE)),   //GetPCFactionMurder
    Function_ArgumentsType(197,std::make_pair(eFORMID,eNONE)),   //GetPCFactionSteal
    Function_ArgumentsType(199,std::make_pair(eFORMID,eNONE)),   //GetPCFactionAttack
    Function_ArgumentsType(201,std::make_pair(eFORMID,eNONE)),   //GetPCFactionSubmitAuthority
    Function_ArgumentsType(203,std::make_pair(eNONE,eNONE)),     //GetDestroyed
    Function_ArgumentsType(214,std::make_pair(eFORMID,eNONE)),   //HasMagicEffect
    Function_ArgumentsType(215,std::make_pair(eNONE,eNONE)),     //GetDoorDefaultOpen
    Function_ArgumentsType(223,std::make_pair(eFORMID,eNONE)),   //IsSpellTarget
    Function_ArgumentsType(224,std::make_pair(eFORMID,eNONE)),   //GetIsPlayerBirthsign
    Function_ArgumentsType(225,std::make_pair(eNONE,eNONE)),     //GetPersuasionNumber
    Function_ArgumentsType(227,std::make_pair(eNONE,eNONE)),     //HasVampireFed
    Function_ArgumentsType(228,std::make_pair(eFORMID,eNONE)),   //GetIsClassDefault
    Function_ArgumentsType(229,std::make_pair(eNONE,eNONE)),     //GetClassDefaultMatch
    Function_ArgumentsType(230,std::make_pair(eFORMID,eFORMID)), //GetInCellParam
    Function_ArgumentsType(237,std::make_pair(eNONE,eNONE)),     //GetIsGhost
    Function_ArgumentsType(242,std::make_pair(eNONE,eNONE)),     //GetUnconscious
    Function_ArgumentsType(244,std::make_pair(eNONE,eNONE)),     //GetRestrained
    Function_ArgumentsType(246,std::make_pair(eFORMID,eNONE)),   //GetIsUsedItem
    Function_ArgumentsType(247,std::make_pair(eUINT32,eNONE)),   //GetIsUsedItemType
    Function_ArgumentsType(249,std::make_pair(eNONE,eNONE)),     //GetPCFame
    Function_ArgumentsType(251,std::make_pair(eNONE,eNONE)),     //GetPCInfamy
    Function_ArgumentsType(254,std::make_pair(eNONE,eNONE)),     //GetIsPlayableRace
    Function_ArgumentsType(255,std::make_pair(eNONE,eNONE)),     //GetOffersServicesNow
    Function_ArgumentsType(258,std::make_pair(eNONE,eNONE)),     //GetUsedItemLevel
    Function_ArgumentsType(259,std::make_pair(eNONE,eNONE)),     //GetUsedItemActivate
    Function_ArgumentsType(264,std::make_pair(eNONE,eNONE)),     //GetBarterGold
    Function_ArgumentsType(265,std::make_pair(eNONE,eNONE)),     //IsTimePassing
    Function_ArgumentsType(266,std::make_pair(eNONE,eNONE)),     //IsPleasant
    Function_ArgumentsType(267,std::make_pair(eNONE,eNONE)),     //IsCloudy
    Function_ArgumentsType(274,std::make_pair(eNONE,eNONE)),     //GetArmorRatingUpperBody
    Function_ArgumentsType(277,std::make_pair(eUINT32,eNONE)),   //GetBaseActorValue
    Function_ArgumentsType(278,std::make_pair(eFORMID,eNONE)),   //IsOwner
    Function_ArgumentsType(280,std::make_pair(eFORMID,eFORMID)), //IsCellOwner
    Function_ArgumentsType(282,std::make_pair(eNONE,eNONE)),     //IsHorseStolen
    Function_ArgumentsType(285,std::make_pair(eNONE,eNONE)),     //IsLeftUp
    Function_ArgumentsType(286,std::make_pair(eNONE,eNONE)),     //IsSneaking
    Function_ArgumentsType(287,std::make_pair(eNONE,eNONE)),     //IsRunning
    Function_ArgumentsType(288,std::make_pair(eFORMID,eNONE)),   //GetFriendHit
    Function_ArgumentsType(289,std::make_pair(eNONE,eNONE)),     //IsInCombat
    Function_ArgumentsType(300,std::make_pair(eNONE,eNONE)),     //IsInInterior
    Function_ArgumentsType(305,std::make_pair(eNONE,eNONE)),     //GetInvestmentGold
    Function_ArgumentsType(306,std::make_pair(eNONE,eNONE)),     //IsActorUsingATorch
    Function_ArgumentsType(309,std::make_pair(eNONE,eNONE)),     //IsXBox
    Function_ArgumentsType(310,std::make_pair(eFORMID,eNONE)),   //GetInWorldspace
    Function_ArgumentsType(312,std::make_pair(eUINT32,eNONE)),   //GetPCMiscStat
    Function_ArgumentsType(313,std::make_pair(eNONE,eNONE)),     //IsActorEvil
    Function_ArgumentsType(314,std::make_pair(eNONE,eNONE)),     //IsActorAVictim
    Function_ArgumentsType(315,std::make_pair(eNONE,eNONE)),     //GetTotalPersuasionNumber
    Function_ArgumentsType(318,std::make_pair(eNONE,eNONE)),     //GetIdleDoneOnce
    Function_ArgumentsType(320,std::make_pair(eNONE,eNONE)),     //GetNoRumors
    Function_ArgumentsType(323,std::make_pair(eNONE,eNONE)),     //WhichServiceMenu
    Function_ArgumentsType(327,std::make_pair(eNONE,eNONE)),     //IsRidingHorse
    Function_ArgumentsType(329,std::make_pair(eNONE,eNONE)),     //IsTurnArrest
    Function_ArgumentsType(332,std::make_pair(eNONE,eNONE)),     //IsInDangerousWater
    Function_ArgumentsType(338,std::make_pair(eNONE,eNONE)),     //GetIgnoreFriendlyHits
    Function_ArgumentsType(339,std::make_pair(eNONE,eNONE)),     //IsPlayersLastRiddenHorse
    Function_ArgumentsType(353,std::make_pair(eNONE,eNONE)),     //IsActor
    Function_ArgumentsType(354,std::make_pair(eNONE,eNONE)),     //IsEssential
    Function_ArgumentsType(358,std::make_pair(eNONE,eNONE)),     //IsPlayerMovingIntoNewSpace
    Function_ArgumentsType(361,std::make_pair(eNONE,eNONE)),     //GetTimeDead
    Function_ArgumentsType(362,std::make_pair(eNONE,eNONE)),     //GetPlayerHasLastRiddenHorse
    Function_ArgumentsType(365,std::make_pair(eNONE,eNONE))      //GetPlayerInSEWorld
    };

Function_NameType Function_NameInit[] =
    {
    Function_NameType(153,"CanHaveFlames"),
    Function_NameType(127,"CanPayCrimeGold"),
    Function_NameType(14,"GetActorValue"),
    Function_NameType(61,"GetAlarmed"),
    Function_NameType(190,"GetAmountSoldStolen"),
    Function_NameType(8,"GetAngle"),
    Function_NameType(81,"GetArmorRating"),
    Function_NameType(274,"GetArmorRatingUpperBody"),
    Function_NameType(63,"GetAttacked"),
    Function_NameType(264,"GetBarterGold"),
    Function_NameType(277,"GetBaseActorValue"),
    Function_NameType(229,"GetClassDefaultMatch"),
    Function_NameType(41,"GetClothingValue"),
    Function_NameType(122,"GetCrime"),
    Function_NameType(116,"GetCrimeGold"),
    Function_NameType(110,"GetCurrentAIPackage"),
    Function_NameType(143,"GetCurrentAIProcedure"),
    Function_NameType(18,"GetCurrentTime"),
    Function_NameType(148,"GetCurrentWeatherPercent"),
    Function_NameType(170,"GetDayOfWeek"),
    Function_NameType(46,"GetDead"),
    Function_NameType(84,"GetDeadCount"),
    Function_NameType(203,"GetDestroyed"),
    Function_NameType(45,"GetDetected"),
    Function_NameType(180,"GetDetectionLevel"),
    Function_NameType(35,"GetDisabled"),
    Function_NameType(39,"GetDisease"),
    Function_NameType(76,"GetDisposition"),
    Function_NameType(1,"GetDistance"),
    Function_NameType(215,"GetDoorDefaultOpen"),
    Function_NameType(182,"GetEquipped"),
    Function_NameType(73,"GetFactionRank"),
    Function_NameType(60,"GetFactionRankDifference"),
    Function_NameType(128,"GetFatiguePercentage"),
    Function_NameType(288,"GetFriendHit"),
    Function_NameType(160,"GetFurnitureMarkerID"),
    Function_NameType(74,"GetGlobalValue"),
    Function_NameType(48,"GetGold"),
    Function_NameType(99,"GetHeadingAngle"),
    Function_NameType(318,"GetIdleDoneOnce"),
    Function_NameType(338,"GetIgnoreFriendlyHits"),
    Function_NameType(67,"GetInCell"),
    Function_NameType(230,"GetInCellParam"),
    Function_NameType(71,"GetInFaction"),
    Function_NameType(32,"GetInSameCell"),
    Function_NameType(305,"GetInvestmentGold"),
    Function_NameType(310,"GetInWorldspace"),
    Function_NameType(91,"GetIsAlerted"),
    Function_NameType(68,"GetIsClass"),
    Function_NameType(228,"GetIsClassDefault"),
    Function_NameType(64,"GetIsCreature"),
    Function_NameType(161,"GetIsCurrentPackage"),
    Function_NameType(149,"GetIsCurrentWeather"),
    Function_NameType(237,"GetIsGhost"),
    Function_NameType(72,"GetIsID"),
    Function_NameType(254,"GetIsPlayableRace"),
    Function_NameType(224,"GetIsPlayerBirthsign"),
    Function_NameType(69,"GetIsRace"),
    Function_NameType(136,"GetIsReference"),
    Function_NameType(70,"GetIsSex"),
    Function_NameType(246,"GetIsUsedItem"),
    Function_NameType(247,"GetIsUsedItemType"),
    Function_NameType(47,"GetItemCount"),
    Function_NameType(107,"GetKnockedState"),
    Function_NameType(80,"GetLevel"),
    Function_NameType(27,"GetLineOfSight"),
    Function_NameType(5,"GetLocked"),
    Function_NameType(65,"GetLockLevel"),
    Function_NameType(320,"GetNoRumors"),
    Function_NameType(255,"GetOffersServicesNow"),
    Function_NameType(157,"GetOpenState"),
    Function_NameType(193,"GetPCExpelled"),
    Function_NameType(199,"GetPCFactionAttack"),
    Function_NameType(195,"GetPCFactionMurder"),
    Function_NameType(197,"GetPCFactionSteal"),
    Function_NameType(201,"GetPCFactionSubmitAuthority"),
    Function_NameType(249,"GetPCFame"),
    Function_NameType(132,"GetPCInFaction"),
    Function_NameType(251,"GetPCInfamy"),
    Function_NameType(129,"GetPCIsClass"),
    Function_NameType(130,"GetPCIsRace"),
    Function_NameType(131,"GetPCIsSex"),
    Function_NameType(312,"GetPCMiscStat"),
    Function_NameType(225,"GetPersuasionNumber"),
    Function_NameType(98,"GetPlayerControlsDisabled"),
    Function_NameType(365,"GetPlayerInSEWorld"),
    Function_NameType(362,"GetPlayerHasLastRiddenHorse"),
    Function_NameType(6,"GetPos"),
    Function_NameType(56,"GetQuestRunning"),
    Function_NameType(79,"GetQuestVariable"),
    Function_NameType(77,"GetRandomPercent"),
    Function_NameType(244,"GetRestrained"),
    Function_NameType(24,"GetScale"),
    Function_NameType(53,"GetScriptVariable"),
    Function_NameType(12,"GetSecondsPassed"),
    Function_NameType(66,"GetShouldAttack"),
    Function_NameType(159,"GetSitting"),
    Function_NameType(49,"GetSleeping"),
    Function_NameType(58,"GetStage"),
    Function_NameType(59,"GetStageDone"),
    Function_NameType(11,"GetStartingAngle"),
    Function_NameType(10,"GetStartingPos"),
    Function_NameType(50,"GetTalkedToPC"),
    Function_NameType(172,"GetTalkedToPCParam"),
    Function_NameType(361,"GetTimeDead"),
    Function_NameType(315,"GetTotalPersuasionNumber"),
    Function_NameType(144,"GetTrespassWarningLevel"),
    Function_NameType(242,"GetUnconscious"),
    Function_NameType(259,"GetUsedItemActivate"),
    Function_NameType(258,"GetUsedItemLevel"),
    Function_NameType(40,"GetVampire"),
    Function_NameType(142,"GetWalkSpeed"),
    Function_NameType(108,"GetWeaponAnimType"),
    Function_NameType(109,"GetWeaponSkillType"),
    Function_NameType(147,"GetWindSpeed"),
    Function_NameType(154,"HasFlames"),
    Function_NameType(214,"HasMagicEffect"),
    Function_NameType(227,"HasVampireFed"),
    Function_NameType(353,"IsActor"),
    Function_NameType(314,"IsActorAVictim"),
    Function_NameType(313,"IsActorEvil"),
    Function_NameType(306,"IsActorUsingATorch"),
    Function_NameType(280,"IsCellOwner"),
    Function_NameType(267,"IsCloudy"),
    Function_NameType(150,"IsContinuingPackagePCNear"),
    Function_NameType(163,"IsCurrentFurnitureObj"),
    Function_NameType(162,"IsCurrentFurnitureRef"),
    Function_NameType(354,"IsEssential"),
    Function_NameType(106,"IsFacingUp"),
    Function_NameType(125,"IsGuard"),
    Function_NameType(282,"IsHorseStolen"),
    Function_NameType(112,"IsIdlePlaying"),
    Function_NameType(289,"IsInCombat"),
    Function_NameType(332,"IsInDangerousWater"),
    Function_NameType(300,"IsInInterior"),
    Function_NameType(146,"IsInMyOwnedCell"),
    Function_NameType(285,"IsLeftUp"),
    Function_NameType(278,"IsOwner"),
    Function_NameType(176,"IsPCAMurderer"),
    Function_NameType(175,"IsPCSleeping"),
    Function_NameType(171,"IsPlayerInJail"),
    Function_NameType(358,"IsPlayerMovingIntoNewSpace"),
    Function_NameType(339,"IsPlayersLastRiddenHorse"),
    Function_NameType(266,"IsPleasant"),
    Function_NameType(62,"IsRaining"),
    Function_NameType(327,"IsRidingHorse"),
    Function_NameType(287,"IsRunning"),
    Function_NameType(103,"IsShieldOut"),
    Function_NameType(286,"IsSneaking"),
    Function_NameType(75,"IsSnowing"),
    Function_NameType(223,"IsSpellTarget"),
    Function_NameType(185,"IsSwimming"),
    Function_NameType(141,"IsTalking"),
    Function_NameType(265,"IsTimePassing"),
    Function_NameType(102,"IsTorchOut"),
    Function_NameType(145,"IsTrespassing"),
    Function_NameType(329,"IsTurnArrest"),
    Function_NameType(111,"IsWaiting"),
    Function_NameType(101,"IsWeaponOut"),
    Function_NameType(309,"IsXBox"),
    Function_NameType(104,"IsYielding"),
    Function_NameType(36,"MenuMode"),
    Function_NameType(42,"SameFaction"),
    Function_NameType(133,"SameFactionAsPC"),
    Function_NameType(43,"SameRace"),
    Function_NameType(134,"SameRaceAsPC"),
    Function_NameType(44,"SameSex"),
    Function_NameType(135,"SameSexAsPC"),
    Function_NameType(323,"WhichServiceMenu")
    };

Function_NameType Comparison_NameInit[] =
    {
    Function_NameType(0x00,"Equal to"),
    Function_NameType(0x01,"Equal to / Or"),
    Function_NameType(0x02,"Equal to / Run on target"),
    Function_NameType(0x03,"Equal to / Or, Run on target"),
    Function_NameType(0x04,"Equal to / Use global"),
    Function_NameType(0x05,"Equal to / Or, Use global"),
    Function_NameType(0x06,"Equal to / Run on target, Use global"),
    Function_NameType(0x07,"Equal to / Or, Run on target, Use global"),
    Function_NameType(0x20,"Not equal to"),
    Function_NameType(0x21,"Not equal to / Or"),
    Function_NameType(0x22,"Not equal to / Run on target"),
    Function_NameType(0x23,"Not equal to / Or, Run on target"),
    Function_NameType(0x24,"Not equal to / Use global"),
    Function_NameType(0x25,"Not equal to / Or, Use global"),
    Function_NameType(0x26,"Not equal to / Run on target, Use global"),
    Function_NameType(0x27,"Not equal to / Or, Run on target, Use global"),
    Function_NameType(0x40,"Greater than"),
    Function_NameType(0x41,"Greater than / Or"),
    Function_NameType(0x42,"Greater than / Run on target"),
    Function_NameType(0x43,"Greater than / Or, Run on target"),
    Function_NameType(0x44,"Greater than / Use global"),
    Function_NameType(0x45,"Greater than / Or, Use global"),
    Function_NameType(0x46,"Greater than / Run on target, Use global"),
    Function_NameType(0x47,"Greater than / Or, Run on target, Use global"),
    Function_NameType(0x60,"Greater than or equal to"),
    Function_NameType(0x61,"Greater than or equal to / Or"),
    Function_NameType(0x62,"Greater than or equal to / Run on target"),
    Function_NameType(0x63,"Greater than or equal to / Or, Run on target"),
    Function_NameType(0x64,"Greater than or equal to / Use global"),
    Function_NameType(0x65,"Greater than or equal to / Or, Use global"),
    Function_NameType(0x66,"Greater than or equal to / Run on target, Use global"),
    Function_NameType(0x67,"Greater than or equal to / Or, Run on target, Use global"),
    Function_NameType(0x80,"Less than"),
    Function_NameType(0x81,"Less than / Or"),
    Function_NameType(0x82,"Less than / Run on target"),
    Function_NameType(0x83,"Less than / Or, Run on target"),
    Function_NameType(0x84,"Less than / Use global"),
    Function_NameType(0x85,"Less than / Or, Use global"),
    Function_NameType(0x86,"Less than / Run on target, Use global"),
    Function_NameType(0x87,"Less than / Or, Run on target, Use global"),
    Function_NameType(0xA0,"Less than or equal to"),
    Function_NameType(0xA1,"Less than or equal to / Or"),
    Function_NameType(0xA2,"Less than or equal to / Run on target"),
    Function_NameType(0xA3,"Less than or equal to / Or, Run on target"),
    Function_NameType(0xA4,"Less than or equal to / Use global"),
    Function_NameType(0xA5,"Less than or equal to / Or, Use global"),
    Function_NameType(0xA6,"Less than or equal to / Run on target, Use global"),
    Function_NameType(0xA7,"Less than or equal to / Or, Run on target, Use global")
    };

Function_NameType IDLEGroup_NameInit[] =
    {
    Function_NameType(0x80,"Lower Body"),
    Function_NameType(0x00,"Lower Body, Must return a file"),
    Function_NameType(0x81,"Left Arm"),
    Function_NameType(0x01,"Left Arm, Must return a file"),
    Function_NameType(0x82,"Left Hand"),
    Function_NameType(0x02,"Left Hand, Must return a file"),
    Function_NameType(0x83,"Right Arm"),
    Function_NameType(0x03,"Right Arm, Must return a file"),
    Function_NameType(0x84,"Special Idle"),
    Function_NameType(0x04,"Special Idle, Must return a file"),
    Function_NameType(0x85,"Whole Body"),
    Function_NameType(0x05,"Whole Body, Must return a file"),
    Function_NameType(0x86,"Upper Body"),
    Function_NameType(0x06,"Upper Body, Must return a file"),
    };

Function_NameType PACKAIType_NameInit[] =
    {
    Function_NameType(0,"Find"),
    Function_NameType(1,"Follow"),
    Function_NameType(2,"Escort"),
    Function_NameType(3,"Eat"),
    Function_NameType(4,"Sleep"),
    Function_NameType(5,"Wander"),
    Function_NameType(6,"Travel"),
    Function_NameType(7,"Accompany"),
    Function_NameType(8,"Use item at"),
    Function_NameType(9,"Ambush"),
    Function_NameType(10,"Flee not combat"),
    Function_NameType(11,"Cast magic")
    };

Function_NameType PACKLocType_NameInit[] =
    {
    Function_NameType(0,"Near reference"),
    Function_NameType(1,"In cell"),
    Function_NameType(2,"Near current location"),
    Function_NameType(3,"Near editor location"),
    Function_NameType(4,"Object ID"),
    Function_NameType(5,"Object type")
    };

Function_NameType PACKTargetType_NameInit[] =
    {
    Function_NameType(0,"Specific reference"),
    Function_NameType(1,"Object ID"),
    Function_NameType(2,"Object type")
    };

Function_NameType HardCodedFormID_EditorIDInit[] =
    {
    Function_NameType(0x0001,"DoorMarker"),
    Function_NameType(0x0002,"TravelMarker"),
    Function_NameType(0x0003,"NorthMarker"),
    Function_NameType(0x0004,"PrisonMarker"),
    Function_NameType(0x0005,"DivineMarker"),
    Function_NameType(0x0006,"TempleMarker"),
    Function_NameType(0x0007,"Player"),
    Function_NameType(0x000A,"Lockpick"),
    Function_NameType(0x000B,"SkeletonKey"),
    Function_NameType(0x000C,"RepairHammer"),
    Function_NameType(0x000E,"LootBag"),
    Function_NameType(0x000F,"Gold001"),
    Function_NameType(0x0010,"MapMarker"),
    Function_NameType(0x0011,"StolenGoods"),
    Function_NameType(0x0012,"HorseMarker"),
    Function_NameType(0x0013,"CreatureFaction"),
    Function_NameType(0x0014,"PlayerRef"),
    Function_NameType(0x0015,"JailPants"),
    Function_NameType(0x0016,"JailShoes"),
    Function_NameType(0x0017,"JailShirt"),
    Function_NameType(0x0018,"DefaultWater"),
    Function_NameType(0x0019,"VampireRace"),
    Function_NameType(0x001A,"eyeReanimate"),
    Function_NameType(0x001E,"FlameNode0"),
    Function_NameType(0x001F,"FlameNode1"),
    Function_NameType(0x0020,"FlameNode2"),
    Function_NameType(0x0021,"FlameNode3"),
    Function_NameType(0x0022,"FlameNode4"),
    Function_NameType(0x0023,"FlameNode5"),
    Function_NameType(0x0024,"FlameNode6"),
    Function_NameType(0x0025,"FlameNode7"),
    Function_NameType(0x0026,"FlameNode8"),
    Function_NameType(0x0027,"FlameNode9"),
    Function_NameType(0x0028,"FlameNode10"),
    Function_NameType(0x0029,"FlameNode11"),
    Function_NameType(0x002A,"FlameNode12"),
    Function_NameType(0x002B,"FlameNode13"),
    Function_NameType(0x002C,"FlameNode14"),
    Function_NameType(0x002D,"FlameNode15"),
    Function_NameType(0x002E,"FlameNode16"),
    Function_NameType(0x002F,"FlameNode17"),
    Function_NameType(0x0030,"FlameNode18"),
    Function_NameType(0x0031,"FlameNode19"),
    Function_NameType(0x0032,"FlameNode20"),
    Function_NameType(0x0034,"XMarkerHeading"),
    Function_NameType(0x0035,"GameYear"),
    Function_NameType(0x0036,"GameMonth"),
    Function_NameType(0x0037,"GameDay"),
    Function_NameType(0x0038,"GameHour"),
    Function_NameType(0x0039,"GameDaysPassed"),
    Function_NameType(0x003A,"TimeScale"),
    Function_NameType(0x003B,"XMarker"),
    Function_NameType(0x003C,"Tamriel"),
    Function_NameType(0x003D,"SkillArmorer"),
    Function_NameType(0x003E,"SkillAthletics"),
    Function_NameType(0x003F,"SkillBlade"),
    Function_NameType(0x0040,"SkillBlock"),
    Function_NameType(0x0041,"SkillBlunt"),
    Function_NameType(0x0042,"SkillHandToHand"),
    Function_NameType(0x0043,"SkillHeavyArmor"),
    Function_NameType(0x0044,"SkillAlchemy"),
    Function_NameType(0x0045,"SkillAlteration"),
    Function_NameType(0x0046,"SkillConjuration"),
    Function_NameType(0x0047,"SkillDestruction"),
    Function_NameType(0x0048,"SkillIllusion"),
    Function_NameType(0x0049,"SkillMysticism"),
    Function_NameType(0x004A,"SkillRestoration"),
    Function_NameType(0x004B,"SkillAcrobatics"),
    Function_NameType(0x004C,"SkillLightArmor"),
    Function_NameType(0x004D,"SkillMarksman"),
    Function_NameType(0x004E,"SkillMercantile"),
    Function_NameType(0x004F,"SkillSecurity"),
    Function_NameType(0x0050,"SkillSneak"),
    Function_NameType(0x0051,"SkillSpeechcraft"),
    Function_NameType(0x0064,"FurnitureMarker01"),
    Function_NameType(0x0065,"FurnitureMarker02"),
    Function_NameType(0x0066,"FurnitureMarker03"),
    Function_NameType(0x0067,"FurnitureMarker04"),
    Function_NameType(0x0068,"FurnitureMarker05"),
    Function_NameType(0x0069,"FurnitureMarker06"),
    Function_NameType(0x006A,"FurnitureMarker07"),
    Function_NameType(0x006B,"FurnitureMarker08"),
    Function_NameType(0x006C,"FurnitureMarker09"),
    Function_NameType(0x006D,"FurnitureMarker10"),
    Function_NameType(0x006E,"FurnitureMarker11"),
    Function_NameType(0x006F,"FurnitureMarker12"),
    Function_NameType(0x0070,"FurnitureMarker13"),
    Function_NameType(0x0071,"FurnitureMarker14"),
    Function_NameType(0x0072,"FurnitureMarker15"),
    Function_NameType(0x0073,"FurnitureMarker16"),
    Function_NameType(0x0074,"FurnitureMarker17"),
    Function_NameType(0x0075,"FurnitureMarker18"),
    Function_NameType(0x0076,"FurnitureMarker19"),
    Function_NameType(0x0077,"FurnitureMarker20"),
    Function_NameType(0x00AA,"ADMIREHATE"),
    Function_NameType(0x00AB,"ADMIRELOVE"),
    Function_NameType(0x00AC,"ADMIRELIKE"),
    Function_NameType(0x00AD,"ADMIREDISLIKE"),
    Function_NameType(0x00AE,"COERCEHATE"),
    Function_NameType(0x00AF,"COERCELOVE"),
    Function_NameType(0x00B0,"COERCELIKE"),
    Function_NameType(0x00B1,"COERCEDISLIKE"),
    Function_NameType(0x00B2,"BOASTHATE"),
    Function_NameType(0x00B3,"BOASTLOVE"),
    Function_NameType(0x00B4,"BOASTLIKE"),
    Function_NameType(0x00B5,"BOASTDISLIKE"),
    Function_NameType(0x00B6,"JOKEHATE"),
    Function_NameType(0x00B7,"JOKELOVE"),
    Function_NameType(0x00B8,"JOKELIKE"),
    Function_NameType(0x00B9,"JOKEDISLIKE"),
    Function_NameType(0x00BA,"BRIBE"),
    Function_NameType(0x00BB,"PERSUASIONENTER"),
    Function_NameType(0x00BC,"PERSUASIONEXIT"),
    Function_NameType(0x00C8,"GREETING"),
    Function_NameType(0x00D2,"HELLO"),
    Function_NameType(0x00D3,"ANY"),
    Function_NameType(0x00D4,"GOODBYE"),
    Function_NameType(0x00D5,"IdleChatter"),
    Function_NameType(0x00D6,"SPELLHELP"),
    Function_NameType(0x00D7,"INFOGENERAL"),
    Function_NameType(0x00DC,"Attack"),
    Function_NameType(0x00DD,"Hit"),
    Function_NameType(0x00DE,"Flee"),
    Function_NameType(0x00DF,"Steal"),
    Function_NameType(0x00E0,"Trespass"),
    Function_NameType(0x00E1,"Yield"),
    Function_NameType(0x00E2,"AcceptYield"),
    Function_NameType(0x00E3,"Pickpocket"),
    Function_NameType(0x00E4,"Assault"),
    Function_NameType(0x00E5,"Murder"),
    Function_NameType(0x00E6,"PowerAttack"),
    Function_NameType(0x00E7,"AssaultNoCrime"),
    Function_NameType(0x00E8,"MurderNoCrime"),
    Function_NameType(0x00E9,"PickpocketNoCrime"),
    Function_NameType(0x00EA,"StealNoCrime"),
    Function_NameType(0x00EB,"TrespassNoCrime"),
    Function_NameType(0x00F0,"AdmireSuccess"),
    Function_NameType(0x00F1,"AdmireFail"),
    Function_NameType(0x00F2,"AdmireNeutral"),
    Function_NameType(0x00F3,"TauntSuccess"),
    Function_NameType(0x00F4,"TauntFail"),
    Function_NameType(0x00F5,"TauntNeutral"),
    Function_NameType(0x00F6,"BoastSuccess"),
    Function_NameType(0x00F7,"BoastFail"),
    Function_NameType(0x00F8,"BoastNeutral"),
    Function_NameType(0x00F9,"JokeSuccess"),
    Function_NameType(0x00FA,"JokeFail"),
    Function_NameType(0x00FB,"JokeNeutral"),
    Function_NameType(0x00FC,"BribeSuccess"),
    Function_NameType(0x00FD,"BribeFail"),
    Function_NameType(0x00FE,"DemandSuccess"),
    Function_NameType(0x00FF,"DemandFail"),
    Function_NameType(0x0100,"DemandNoMoney"),
    Function_NameType(0x0101,"DemandNoMoreCircle"),
    Function_NameType(0x0102,"BribeNoMoreCircle"),
    Function_NameType(0x0103,"BribeNoMoney"),
    Function_NameType(0x0104,"Noticed"),
    Function_NameType(0x0105,"Seen"),
    Function_NameType(0x0106,"Unseen"),
    Function_NameType(0x0107,"Lost"),
    Function_NameType(0x010E,"ServiceRefusal"),
    Function_NameType(0x010F,"BarterStart"),
    Function_NameType(0x0110,"BarterFail"),
    Function_NameType(0x0111,"Repair"),
    Function_NameType(0x0112,"Travel"),
    Function_NameType(0x0113,"Training"),
    Function_NameType(0x0114,"BarterBuyItem"),
    Function_NameType(0x0115,"BarterSellItem"),
    Function_NameType(0x0116,"BarterExit"),
    Function_NameType(0x0117,"BarterStolen"),
    Function_NameType(0x0118,"InfoRefusal"),
    Function_NameType(0x0119,"Idle"),
    Function_NameType(0x011A,"ObserveCombat"),
    Function_NameType(0x011B,"Corpse"),
    Function_NameType(0x011C,"TimeToGo"),
    Function_NameType(0x011D,"RepairExit"),
    Function_NameType(0x0120,"Recharge"),
    Function_NameType(0x0121,"RechargeExit"),
    Function_NameType(0x0124,"TrainingExit"),
    Function_NameType(0x012C,"MagicFailureSoundAlteration"),
    Function_NameType(0x012D,"MagicFailureSoundConjuration"),
    Function_NameType(0x012E,"MagicFailureSoundDestruction"),
    Function_NameType(0x012F,"MagicFailureSoundIllusion"),
    Function_NameType(0x0130,"MagicFailureSoundMysticism"),
    Function_NameType(0x0131,"MagicFailureSoundRestoration"),
    Function_NameType(0x0136,"DefaultPlayerSpell"),
    Function_NameType(0x0137,"DefaultMarksmanParalyzeSpell"),
    Function_NameType(0x0138,"MagicEnchantDrawSoundAlteration"),
    Function_NameType(0x0139,"MagicEnchantDrawSoundConjuration"),
    Function_NameType(0x013A,"MagicEnchantDrawSoundDestruction"),
    Function_NameType(0x013B,"MagicEnchantDrawSoundIllusion"),
    Function_NameType(0x013C,"MagicEnchantDrawSoundMysticism"),
    Function_NameType(0x013D,"MagicEnchantDrawSoundRestoration"),
    Function_NameType(0x013E,"MagicEnchantHitSoundAlteration"),
    Function_NameType(0x013F,"MagicEnchantHitSoundConjuration"),
    Function_NameType(0x0140,"MagicEnchantHitSoundDestruction"),
    Function_NameType(0x0141,"MagicEnchantHitSoundIllusion"),
    Function_NameType(0x0142,"MagicEnchantHitSoundMysticism"),
    Function_NameType(0x0143,"MagicEnchantHitSoundRestoration"),
    Function_NameType(0x0144,"effectAbsorb"),
    Function_NameType(0x0145,"effectReflect"),
    Function_NameType(0x0146,"LifeDetected"),
    Function_NameType(0x015E,"DefaultWeather"),
    Function_NameType(0x015F,"DefaultClimate"),
    Function_NameType(0x0191,"WelkyndStone"),
    Function_NameType(0x0192,"BlackSoulGem"),
    Function_NameType(0x0193,"AzuraStone"),
    Function_NameType(0x0194,"VarlaStone"),
    Function_NameType(0x0212,"FootSoundDirt"),
    Function_NameType(0x0213,"FootSoundGrass"),
    Function_NameType(0x0214,"FootSoundStone"),
    Function_NameType(0x0215,"FootSoundWater"),
    Function_NameType(0x0216,"FootSoundWood"),
    Function_NameType(0x0217,"FootSoundHeavyArmor"),
    Function_NameType(0x0218,"FootSoundLightArmor"),
    Function_NameType(0x0219,"FootSoundEarthLand"),
    Function_NameType(0x021A,"FootSoundGrassLand"),
    Function_NameType(0x021B,"FootSoundMetalLand"),
    Function_NameType(0x021C,"FootSoundStoneLand"),
    Function_NameType(0x021D,"FootSoundWaterLand"),
    Function_NameType(0x021E,"FootSoundWoodLand"),
    Function_NameType(0x021F,"FSTSnow"),
    Function_NameType(0x0220,"FSTSnowLand"),
    Function_NameType(0x0221,"FSTEarthSneak"),
    Function_NameType(0x0222,"FSTGrassSneak"),
    Function_NameType(0x0223,"FSTMetalSneak"),
    Function_NameType(0x0224,"FSTSnowSneak"),
    Function_NameType(0x0225,"FSTStoneSneak"),
    Function_NameType(0x0226,"FSTWaterSneak"),
    Function_NameType(0x0227,"FSTWoodSneak"),
    Function_NameType(0x0228,"FSTArmorLightSneak"),
    Function_NameType(0x0229,"FSTArmorHeavySneak"),
    Function_NameType(0x022B,"FSTMetal")
    };

Function_NameType EntryPoint_NameInit[] =
    {
    Function_NameType(0,"Calculate Weapon Damage"),
    Function_NameType(1,"Calculate My Critical Hit Chance"),
    Function_NameType(2,"Calculate My Critical Hit Damage"),
    Function_NameType(3,"Calculate Weapon Attack AP Cost"),
    Function_NameType(4,"Calculate Mine Explode Chance"),
    Function_NameType(5,"Adjust Range Penalty"),
    Function_NameType(6,"Adjust Limb Damage"),
    Function_NameType(7,"Calculate Weapon Range"),
    Function_NameType(8,"Calculate To Hit Chance"),
    Function_NameType(9,"Adjust Experience Points"),
    Function_NameType(10,"Adjust Gained Skill Points"),
    Function_NameType(11,"Adjust Book Skill Points"),
    Function_NameType(12,"Modify Recovered Health"),
    Function_NameType(13,"Calculate Inventory AP Cost"),
    Function_NameType(14,"Get Disposition"),
    Function_NameType(15,"Get Should Attack"),
    Function_NameType(16,"Get Should Assist"),
    Function_NameType(17,"Calculate Buy Price"),
    Function_NameType(18,"Get Bad Karma"),
    Function_NameType(19,"Get Good Karma"),
    Function_NameType(20,"Ignore Locked Terminal"),
    Function_NameType(21,"Add Leveled List On Death"),
    Function_NameType(22,"Get Max Carry Weight"),
    Function_NameType(23,"Modify Addiction Chance"),
    Function_NameType(24,"Modify Addiction Duration"),
    Function_NameType(25,"Modify Positive Chem Duration"),
    Function_NameType(26,"Adjust Drinking Radiation"),
    Function_NameType(27,"Activate"),
    Function_NameType(28,"Mysterious Stranger"),
    Function_NameType(29,"Has Paralyzing Palm"),
    Function_NameType(30,"Hacking Science Bonus"),
    Function_NameType(31,"Ignore Running During Detection"),
    Function_NameType(32,"Ignore Broken Lock"),
    Function_NameType(33,"Has Concentrated Fire"),
    Function_NameType(34,"Calculate Gun Spread"),
    Function_NameType(35,"Player Kill AP Reward"),
    Function_NameType(36,"Modify Enemy Critical Hit Chance"),
    Function_NameType(37,"Reload Speed"),
    Function_NameType(38,"Equip Speed"),
    Function_NameType(39,"Action Point Regen"),
    Function_NameType(40,"Action Point Cost"),
    Function_NameType(41,"Miss Fortune"),
    Function_NameType(42,"Modify Run Speed"),
    Function_NameType(43,"Modify Attack Speed"),
    Function_NameType(44,"Modify Radiation Consumed"),
    Function_NameType(45,"Has Pip Hacker"),
    Function_NameType(46,"Has Meltdown"),
    Function_NameType(47,"See Enemy Health"),
    Function_NameType(48,"Has Jury Rigging"),
    Function_NameType(49,"Modify Threat Range"),
    Function_NameType(50,"Modify Thread"),
    Function_NameType(51,"Has Fast Travel Always"),
    Function_NameType(52,"Knockdown Chance"),
    Function_NameType(53,"Modify Weapon Strength Req"),
    Function_NameType(54,"Modify Aiming Move Speed"),
    Function_NameType(55,"Modify Light Items"),
    Function_NameType(56,"Modify Damage Threshold (defender)"),
    Function_NameType(57,"Modify Chance for Ammo Item"),
    Function_NameType(58,"Modify Damage Threshold (attacker)"),
    Function_NameType(59,"Modify Throwing Velocity"),
    Function_NameType(60,"Chance for Item on Fire"),
    Function_NameType(61,"Has Unarmed Forward Power Attack"),
    Function_NameType(62,"Has Unarmed Back Power Attack"),
    Function_NameType(63,"Has Unarmed Crouched Power Attack"),
    Function_NameType(64,"Has Unarmed Counter Attack"),
    Function_NameType(65,"Has Unarmed Left Power Attack"),
    Function_NameType(66,"Has Unarmed Right Power Attack"),
    Function_NameType(67,"VATS HelperChance"),
    Function_NameType(68,"Modify Item Damage"),
    Function_NameType(69,"Has Improved Detection"),
    Function_NameType(70,"Has Improved Spotting"),
    Function_NameType(71,"Has Improved Item Detection"),
    Function_NameType(72,"Adjust Explosion Radius"),
    Function_NameType(73,"Reserved")
    };

UINT32 _AllPossibleGroups[] = {'TCAF', 'ECAR', 'FEGM', 'TPCS', 'XETL', 'HCNE', 'LEPS', 'NGSB',
                       'ITCA', 'APPA', 'OMRA', 'KOOB', 'TOLC', 'TNOC', 'ROOD', 'RGNI',
                       'HGIL', 'CSIM', 'ROLF', 'NRUF', 'PAEW', 'OMMA', '_CPN', 'AERC',
                       'CLVL', 'MGLS', 'MYEK', 'HCLA', 'TSGS', 'ILVL', 'RHTW', 'TMLC',
                       'NGER', 'LLEC', 'DLRW', 'LAID', 'TSUQ', 'ELDI', 'KCAP', 'RCSL',
                       'PSVL', 'OINA', 'RTAW'};

std::vector<UINT32> AllGroups(_AllPossibleGroups, _AllPossibleGroups + (sizeof(_AllPossibleGroups) / sizeof(_AllPossibleGroups[0])));

//All
//'SCPT'
//'QUST'
//'DIAL' -> 'INFO'
//'IDLE'
//'PACK'
//'QUST'
//
//ACHR, REFR, ACRE
//'WRLD' -> 'CELL(s)'
//'CELL'
//'ACHR'
//'REFR'
//'ACRE'
//
//ROAD
//'WRLD'
//
//SCPT
//'NPC_'
//'QUST'
//'CREA'
//'LVLI'
//'DOOR'
//'ALCH'
//'ACTI'
//'ENCH'
//
//SGST
//'NPC_'
//'CONT'
//'CREA'
//'LVLI'
//'REFR'
//
//SKIL
//'none'
//
//SLGM
//'NPC_'
//'CONT'
//'CREA'
//'LVLI'
//'REFR'
//
//SOUN
//'REGN'
//'REFR'
//'WATR'
//'DOOR'
//'ACTI'
//'WTHR'
//'LIGH'
//'CONT'
//
//SPEL
//'NPC_'
//'CREA'
//'RACE'
//'LVSP'
//
//STAT
//'REFR'
//
//TREE
//'REFR'
//'REGN'
//
//WATR
//'WRLD' & 'CELL(s)'
//'CELL'
//'WATR'
//
//WEAP
//'CONT'
//'LVLI'
//'REFR'
//'NPC_'
//'CREA'
//
//WRLD
//'WRLD'
//'REGN'
//'LSCR'
//'DOOR'
//
//WTHR
//'REGN'
//'CLMT'


RecordType_PossibleGroupsType RecordType_PossibleGroupsInit[] =
    {
    RecordType_PossibleGroupsType('TSMG', AllGroups),
    RecordType_PossibleGroupsType('BOLG', AllGroups),
    RecordType_PossibleGroupsType('SALC', AllGroups),
    RecordType_PossibleGroupsType('TCAF', AllGroups),
    RecordType_PossibleGroupsType('RIAH', AllGroups),
    RecordType_PossibleGroupsType('SEYE', AllGroups),
    RecordType_PossibleGroupsType('ECAR', AllGroups),
    RecordType_PossibleGroupsType('NUOS', AllGroups),
    RecordType_PossibleGroupsType('LIKS', AllGroups),
    RecordType_PossibleGroupsType('FEGM', AllGroups),
    RecordType_PossibleGroupsType('TPCS', AllGroups),
    RecordType_PossibleGroupsType('XETL', AllGroups),
    RecordType_PossibleGroupsType('HCNE', AllGroups),
    RecordType_PossibleGroupsType('LEPS', AllGroups),
    RecordType_PossibleGroupsType('NGSB', AllGroups),
    RecordType_PossibleGroupsType('ITCA', AllGroups),
    RecordType_PossibleGroupsType('APPA', AllGroups),
    RecordType_PossibleGroupsType('OMRA', AllGroups),
    RecordType_PossibleGroupsType('KOOB', AllGroups),
    RecordType_PossibleGroupsType('TOLC', AllGroups),
    RecordType_PossibleGroupsType('TNOC', AllGroups),
    RecordType_PossibleGroupsType('ROOD', AllGroups),
    RecordType_PossibleGroupsType('RGNI', AllGroups),
    RecordType_PossibleGroupsType('HGIL', AllGroups),
    RecordType_PossibleGroupsType('CSIM', AllGroups),
    RecordType_PossibleGroupsType('TATS', AllGroups),
    RecordType_PossibleGroupsType('SARG', AllGroups),
    RecordType_PossibleGroupsType('EERT', AllGroups),
    RecordType_PossibleGroupsType('ROLF', AllGroups),
    RecordType_PossibleGroupsType('NRUF', AllGroups),
    RecordType_PossibleGroupsType('PAEW', AllGroups),
    RecordType_PossibleGroupsType('OMMA', AllGroups),
    RecordType_PossibleGroupsType('_CPN', AllGroups),
    RecordType_PossibleGroupsType('AERC', AllGroups),
    RecordType_PossibleGroupsType('CLVL', AllGroups),
    RecordType_PossibleGroupsType('MGLS', AllGroups),
    RecordType_PossibleGroupsType('MYEK', AllGroups),
    RecordType_PossibleGroupsType('HCLA', AllGroups),
    RecordType_PossibleGroupsType('PSBS', AllGroups),
    RecordType_PossibleGroupsType('TSGS', AllGroups),
    RecordType_PossibleGroupsType('ILVL', AllGroups),
    RecordType_PossibleGroupsType('RHTW', AllGroups),
    RecordType_PossibleGroupsType('TMLC', AllGroups),
    RecordType_PossibleGroupsType('NGER', AllGroups),
    RecordType_PossibleGroupsType('LLEC', AllGroups),
    RecordType_PossibleGroupsType('DLRW', AllGroups),
    RecordType_PossibleGroupsType('LAID', AllGroups),
    RecordType_PossibleGroupsType('TSUQ', AllGroups),
    RecordType_PossibleGroupsType('ELDI', AllGroups),
    RecordType_PossibleGroupsType('KCAP', AllGroups),
    RecordType_PossibleGroupsType('YTSC', AllGroups),
    RecordType_PossibleGroupsType('RCSL', AllGroups),
    RecordType_PossibleGroupsType('PSVL', AllGroups),
    RecordType_PossibleGroupsType('OINA', AllGroups),
    RecordType_PossibleGroupsType('RTAW', AllGroups),
    RecordType_PossibleGroupsType('HSFE', AllGroups)
    };

const std::map<UINT32, std::vector<UINT32>> RecordType_PossibleGroups(RecordType_PossibleGroupsInit, RecordType_PossibleGroupsInit + sizeof(RecordType_PossibleGroupsInit) / sizeof(RecordType_PossibleGroupsInit[0]));

const std::map<UINT32, FunctionArguments> Function_Arguments(Function_ArgumentsInit, Function_ArgumentsInit + sizeof(Function_ArgumentsInit) / sizeof(Function_ArgumentsInit[0]));

const std::map<UINT32, STRING> Function_Name(Function_NameInit, Function_NameInit + sizeof(Function_NameInit) / sizeof(Function_NameInit[0]));
const std::map<UINT32, STRING> Comparison_Name(Comparison_NameInit, Comparison_NameInit + sizeof(Comparison_NameInit) / sizeof(Comparison_NameInit[0]));
const std::map<UINT32, STRING> IDLEGroup_Name(IDLEGroup_NameInit, IDLEGroup_NameInit + sizeof(IDLEGroup_NameInit) / sizeof(IDLEGroup_NameInit[0]));
const std::map<UINT32, STRING> PACKAIType_Name(PACKAIType_NameInit, PACKAIType_NameInit + sizeof(PACKAIType_NameInit) / sizeof(PACKAIType_NameInit[0]));
const std::map<UINT32, STRING> PACKLocType_Name(PACKLocType_NameInit, PACKLocType_NameInit + sizeof(PACKLocType_NameInit) / sizeof(PACKLocType_NameInit[0]));
const std::map<UINT32, STRING> PACKTargetType_Name(PACKTargetType_NameInit, PACKTargetType_NameInit + sizeof(PACKTargetType_NameInit) / sizeof(PACKTargetType_NameInit[0]));
const std::map<UINT32, STRING> HardCodedFormID_EditorID(HardCodedFormID_EditorIDInit, HardCodedFormID_EditorIDInit + sizeof(HardCodedFormID_EditorIDInit) / sizeof(HardCodedFormID_EditorIDInit[0]));

const std::map<UINT32, STRING> EntryPoint_Name(EntryPoint_NameInit, EntryPoint_NameInit + sizeof(EntryPoint_NameInit) / sizeof(EntryPoint_NameInit[0]));
const std::map<UINT32, FunctionArguments> FNVFunction_Arguments(FNVFunction_ArgumentsInit, FNVFunction_ArgumentsInit + sizeof(FNVFunction_ArgumentsInit) / sizeof(FNVFunction_ArgumentsInit[0]));