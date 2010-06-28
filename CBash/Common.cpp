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

time_t lastSave = time(NULL);

bool AlmostEqual(float A, float B, int maxUlps)
    {
    int aInt = *(int*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    int bInt = *(int*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    // Now we can compare aInt and bInt to find out how far apart A and B
    // are.
    int intDiff = abs(aInt - bInt);
    if (intDiff <= maxUlps)
        return true;
    return false;
    }

void _FormIDHandler::CollapseFormID(unsigned int &curFormID)
    {
    if(curFormID == 0)
        return;
    curFormID = (CollapseIndex[curFormID >> 24] << 24 ) | (curFormID & 0x00FFFFFF);
    return;
    }

void _FormIDHandler::CollapseFormID(unsigned int *&curFormID)
    {
    if(*curFormID == 0)
        return;
    *curFormID = (CollapseIndex[*curFormID >> 24] << 24 ) | (*curFormID & 0x00FFFFFF);
    return;
    }

void _FormIDHandler::ExpandFormID(unsigned int &curFormID)
    {
    if(curFormID == 0)
        return;
    curFormID = (ExpandIndex[curFormID >> 24] << 24 ) | (curFormID & 0x00FFFFFF);
    return;
    }

void _FormIDHandler::ExpandFormID(unsigned int *&curFormID)
    {
    if(*curFormID == 0)
        return;
    *curFormID = (ExpandIndex[*curFormID >> 24] << 24 ) | (*curFormID & 0x00FFFFFF);
    return;
    }

unsigned int _FormIDHandler::AssignToMod(unsigned int curFormID)
    {
    if(curFormID == 0)
        return 0;
    return (ExpandedIndex << 24 ) | (curFormID & 0x00FFFFFF);
    }

unsigned int _FormIDHandler::AssignToMod(unsigned int *curFormID)
    {
    unsigned int newFormID = 0;
    if(*curFormID != 0)
        newFormID = (ExpandedIndex << 24 ) | (*curFormID & 0x00FFFFFF);
    return newFormID;
    }

void _FormIDHandler::SetLoadOrder(std::vector<char *> &cLoadOrder)
    {
    LoadOrder = cLoadOrder;
    return;
    }

unsigned int _FormIDHandler::NextExpandedFID()
    {
    //0x00FFFFFF is the highest formID that can be used.
    //Bug: Doesn't check if formID is already used. Shouldn't be a problem except when it rolls over
    if(nextObject >= 0x01000000)
        nextObject = OBJECT_ID_START;
    return (ExpandedIndex << 24) | ++nextObject;
    }

void _FormIDHandler::UpdateFormIDLookup()
    {
    //Each ModFile maintains a formID resolution lookup table of valid modIndexs
    //both when expanded into a load order corrected format
    //and for when collapsed back into a writable format
    //This function populates that table, and allows much, much faster formID resolution
    //which occurs on every formID that is read, set, and written...

    //The Collapsed lookup table has to be updated anytime the mod's masters change.
    //It also sorts the masters based on the load order
    unsigned char numMods = (unsigned char)LoadOrder.size();
    char *curMaster = NULL;
    CollapsedIndex = (unsigned char)MAST.size();
    for(unsigned char p = 0; p < 255; ++p)
        CollapseIndex[p] = CollapsedIndex;

    std::vector<STRING> sortedMAST;
    sortedMAST.reserve(CollapsedIndex);
    for(unsigned int x = 0; x < LoadOrder.size(); ++x)
        {
        for(unsigned char y = 0; y < CollapsedIndex; ++y)
            {
            if(_stricmp(LoadOrder[x], MAST[y].value) == 0)
                {
                sortedMAST.push_back(MAST[y]);
                break;
                }
            }
        }
    MAST = sortedMAST;

    for(unsigned char p = 0; p < CollapsedIndex; ++p)
        {
        MAST[p] = sortedMAST[p];
        curMaster = MAST[p].value;
        for(unsigned char y = 0; y < numMods; ++y)
            if(_stricmp(LoadOrder[y], curMaster) == 0)
                {
                CollapseIndex[y] = p;
                break;
                }
        }
    sortedMAST.clear();
    return;
    }

void _FormIDHandler::CreateFormIDLookup(const unsigned char expandedIndex)
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
    unsigned char numMods = (unsigned char)LoadOrder.size();
    char *curMaster = NULL;
    CollapsedIndex = (unsigned char)MAST.size();
    ExpandedIndex = expandedIndex;
    for(unsigned char p = 0; p < 255; ++p)
        {
        CollapseIndex[p] = CollapsedIndex;
        ExpandIndex[p] = ExpandedIndex;
        }

    for(unsigned char p = 0; p < CollapsedIndex; ++p)
        {
        curMaster = MAST[p].value;
        for(unsigned char y = 0; y < numMods; ++y)
            if(_stricmp(LoadOrder[y], curMaster) == 0)
                {
                ExpandIndex[p] = y;
                CollapseIndex[y] = p;
                break;
                }
        }
    return;
    }

void _FormIDHandler::AddMaster(unsigned int &recordFID)
    {
    unsigned int modIndex = recordFID >> 24;
    //If formID is not set, or the formID belongs to the mod, or if the master is already present, do nothing
    if((recordFID == 0) || (modIndex == ExpandedIndex) || (CollapseIndex[modIndex] != CollapsedIndex))
        return;
    //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
    if(modIndex >= LoadOrder.size())
        {
        #ifdef _DEBUG
        printf("Something's rotten in AddMasterFromFID. modIndex:%i, ModFiles.Size:%i\n", modIndex, LoadOrder.size());
        #endif
        CollapseFormID(recordFID);
        ExpandFormID(recordFID);
        return;
        }
    //Add the master to the end, and update header size
    //destMod->TES4.MAST.push_back(STRING(*curName));
    MAST.push_back(STRING(LoadOrder[modIndex]));
    bMastersChanged = true;
    //Update the formID resolution lookup table
    UpdateFormIDLookup();
    return;
    }

void _FormIDHandler::AddMaster(unsigned int *&recordFID)
    {
    unsigned int modIndex = *recordFID >> 24;
    //If formID is not set, or the formID belongs to the mod, or if the master is already present, do nothing
    if((*recordFID == 0) || (modIndex == ExpandedIndex) || (CollapseIndex[modIndex] != CollapsedIndex))
        return;
    //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
    if(modIndex >= LoadOrder.size())
        {
        #ifdef _DEBUG
        printf("Something's rotten in AddMasterFromFID. modIndex:%i, ModFiles.Size:%i\n", modIndex, LoadOrder.size());
        #endif
        CollapseFormID(*recordFID);
        ExpandFormID(*recordFID);
        return;
        }
    //Add the master to the end, and update header size
    //destMod->TES4.MAST.push_back(STRING(*curName));
    MAST.push_back(STRING(LoadOrder[modIndex]));
    bMastersChanged = true;
    //Update the formID resolution lookup table
    UpdateFormIDLookup();
    return;
    }

bool _FormIDHandler::MastersChanged()
    {
    return bMastersChanged;
    }

bool _FormIDHandler::UsesMaster(const unsigned int *&recordFID, const unsigned char &MASTIndex)
    {
    return (ExpandIndex[MASTIndex] == (*recordFID >> 24));
    }

bool _FormIDHandler::UsesMaster(const unsigned int &recordFID, const unsigned char &MASTIndex)
    {
    return (ExpandIndex[MASTIndex] == (recordFID >> 24));
    }

bool FileExists(const char *FileName)
    {
    struct stat statBuffer;
    return (stat(FileName, &statBuffer) >= 0 && statBuffer.st_mode & S_IFREG);
    }

int _FileHandler::open_ReadOnly(const char *FileName)
    {
    if(fh != -1 || f_map != NULL || m_region != NULL)
        return -1;
    try
        {
        f_map = new boost::interprocess::file_mapping(FileName, boost::interprocess::read_only);
        m_region = new boost::interprocess::mapped_region(*f_map, boost::interprocess::read_only);
        }
    catch(boost::interprocess::interprocess_exception &ex)
        {
        printf("Exception raised: %s\nUnable to memory map '%s' for read only.\n", ex.what(), FileName);
        throw;
        return -1;
        }
    catch(...)
        {
        printf("Read Only - Open Error\n");
        throw;
        return -1;
        }
    _Buffer = (unsigned char*)m_region->get_address();
    _BufEnd = (unsigned int)m_region->get_size();
    return 0;
    }

int _FileHandler::open_ReadWrite(const char *FileName)
    {
    if(fh != -1 || f_map != NULL || m_region != NULL)
        return -1;
    errno_t err = _sopen_s(&fh, FileName, _O_CREAT | _O_RDWR | _O_BINARY, _SH_DENYWR, _S_IREAD | _S_IWRITE );
    if( err != 0 )
        {
        switch(err)
            {
            case EACCES:
                printf("Given path is a directory, or file is read-only, but an open-for-writing operation was attempted.\n");
                return -1;
            case EEXIST:
                printf("_O_CREAT and _O_EXCL flags were specified, but filename already exists.\n");
                return -1;
            case EINVAL:
                printf("Invalid oflag, shflag, or pmode  argument, or pfh or filename was a null pointer.\n");
                return -1;
            case EMFILE:
                printf("No more file descriptors available.\n");
                return -1;
            case ENOENT:
                printf("File or path not found.\n");
                return -1;
            default:
                printf("Unknown error\n");
                return -1;
            }
        _close(fh);
        return -1;
        }
    return 0;
    }

unsigned long _FileHandler::tell()
    {
    return _BufPos + _TotalWritten;
    }

bool _FileHandler::eof()
    {
    return (_BufPos >= _BufEnd);
    }

unsigned long _FileHandler::set_used(long _Used)
    {
    if(_Used == 0)
        return _BufPos;
    else if(_Used < 0)
        {
        if(((unsigned long)abs(_Used) > _BufPos))
            _BufPos = 0;
        else
            _BufPos += _Used;
        return _BufPos;
        }
    //If in read mode, simply move the position
    if(fh == -1)
        {
        //printf("Before seek:%u\n", _BufPos);
        _BufPos += _Used;
        //printf("After seek:%u\n", _BufPos);
        //if(eof())
        //    printf("End!\n");
        return _BufPos;
        }
    //Flush the buffer if it is getting full
    if((_BufPos + _Used) >= _BufSize)
        flush();
    if((unsigned long)_Used < _BufSize)
        _BufPos += _Used;
    else
        {
        flush();
        printf("Exceeded capacity: Tried to set %u as used in a buffer with a size of %u.\n", _Used, _BufSize);
        }
    return _BufPos;
    }

void _FileHandler::read(void *_DstBuf, unsigned int _MaxCharCount)
    {
    if(_DstBuf == NULL || _Buffer == NULL)
        return;
    memcpy(_DstBuf, _Buffer + _BufPos, _MaxCharCount);
    _BufPos += _MaxCharCount;
    }

unsigned char *_FileHandler::getBuffer(unsigned long _Offset)
    {
    if(IsCached(_Offset))
        return _Buffer + _Offset - _TotalWritten;
    return NULL;
    }

unsigned long _FileHandler::write(const void *_SrcBuf, unsigned int _MaxCharCount)
    {
    if(fh == -1 || _SrcBuf == NULL || _Buffer == NULL || _MaxCharCount == 0)
        return _BufPos;
    //Flush the buffer if it is getting full
    if((_BufPos + _MaxCharCount) >= _BufSize)
        flush();
    //Use the buffer if there's room
    if(_MaxCharCount < _BufSize)
        {
        memcpy(_Buffer + _BufPos, _SrcBuf, _MaxCharCount);
        _BufPos += _MaxCharCount;
        }
    else
        {
        //Otherwise, flush the buffer and write directly to disk.
        flush();
        _write(fh, _SrcBuf, _MaxCharCount);
        _TotalWritten += _MaxCharCount;
        }
    return _BufPos;
    }

void _FileHandler::writeSubRecord(unsigned int _Type, const void *_SrcBuf, unsigned int _MaxCharCount)
    {
    unsigned int _Temp = 0;
    if(_MaxCharCount <= 65535)
        {
        write(&_Type, 4);
        write(&_MaxCharCount, 2);
        }
    else //Requires XXXX SubRecord
        {
        _Temp = 4;
        write("XXXX", 4);
        write(&_Temp, 2);
        write(&_MaxCharCount, 4);
        write(&_Type, 4);
        _Temp = 0;
        write(&_Temp, 2);
        }
    write(_SrcBuf, _MaxCharCount);
    return;
    }

unsigned long _FileHandler::writeAt(unsigned long _Offset, const void *_SrcBuf, unsigned int _MaxCharCount)
    {
    if(fh == -1 || _SrcBuf == NULL || _Buffer == NULL || _MaxCharCount == 0 || _Offset > tell())
        return _Offset;
    //See if the address is still in buffer
    if(IsCached(_Offset))
        {
        memcpy(_Buffer + _Offset - _TotalWritten, _SrcBuf, _MaxCharCount);
        }
    else
        {
        //It has already been written to disk.
        long curPos = _tell(fh);
        _lseek(fh, _Offset, SEEK_SET);
        _write(fh, _SrcBuf, _MaxCharCount);
        _lseek(fh, curPos, SEEK_SET);
        }
    return _Offset + _MaxCharCount;
    }

void _FileHandler::flush()
    {
    if(fh == -1 || _Buffer == NULL || _BufPos == 0)
        return;
    _write(fh, _Buffer, _BufPos);
    _TotalWritten += _BufPos;
    _BufPos = 0;
    return;
    }

unsigned long _FileHandler::UnusedCache()
    {
    return _BufSize - _BufPos;
    }

bool _FileHandler::IsCached(unsigned long _Offset)
    {
    return (_Offset >= _TotalWritten && _Offset <= tell());
    }

int _FileHandler::close()
    {
    flush();
    if(fh != -1)
        _close(fh);
    delete m_region;
    delete f_map;
    m_region = NULL;
    f_map = NULL;
    fh = -1;
    _Buffer = NULL;
    _BufEnd = 0;
    _BufPos = 0;
    return 0;
    }

void _FileHandler::reserveBuffer(unsigned int nSize)
    {
    if(fh == -1 || f_map != NULL || m_region != NULL || nSize <= UnusedCache())
        return;
    flush();
    //There's room in the current buffer if flushed.
    if(nSize < _BufSize)
        return;
    //Otherwise, resize the buffer to fit
    printf("Resizing buffer from: %u to %u\n", _BufSize, nSize);
    delete []_Buffer;
    _BufSize = nSize;
    _Buffer = new unsigned char[_BufSize];
    return;
    }

#ifdef _DEBUG
void PrintIndent(const unsigned int &indentation)
    {
    for(unsigned int x = 0; x < indentation; x++)
        printf(" ");
    }

char * PrintFormID(unsigned int formID)
    {
    static char buff[9] = {'\0'};
    sprintf_s(buff, 9, "%08X", formID);
    return buff;
    }

char * PrintFormID(FormID formID)
    {
    if(formID == NULL)
        return "(null)";
    static char buff[9] = {'\0'};
    sprintf_s(buff, 9, "%08X", *formID);
    return buff;
    }
#endif

typedef std::map<unsigned int, std::pair<varType,varType>>::value_type Function_ArgumentsType;

Function_ArgumentsType Function_ArgumentsInit[] =
    {
    Function_ArgumentsType(153,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(127,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(14,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(61,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(190,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(8,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(81,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(274,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(63,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(264,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(277,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(229,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(41,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(122,std::make_pair(eFID,eInt)),
    Function_ArgumentsType(116,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(110,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(143,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(18,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(148,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(170,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(46,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(84,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(203,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(45,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(180,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(35,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(39,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(76,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(1,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(215,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(182,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(73,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(60,std::make_pair(eFID,eFID)),
    Function_ArgumentsType(128,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(288,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(160,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(74,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(48,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(99,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(318,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(338,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(67,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(230,std::make_pair(eFID,eFID)),
    Function_ArgumentsType(71,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(32,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(305,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(310,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(91,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(68,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(228,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(64,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(161,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(149,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(237,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(72,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(254,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(224,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(69,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(136,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(70,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(246,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(247,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(47,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(107,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(80,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(27,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(5,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(65,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(320,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(255,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(157,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(193,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(199,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(195,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(197,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(201,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(249,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(132,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(251,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(129,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(130,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(131,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(312,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(225,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(98,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(365,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(362,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(6,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(56,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(79,std::make_pair(eFID,eInt)),
    Function_ArgumentsType(77,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(244,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(24,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(53,std::make_pair(eFID,eInt)),
    Function_ArgumentsType(12,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(66,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(159,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(49,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(58,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(59,std::make_pair(eFID,eInt)),
    Function_ArgumentsType(11,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(10,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(50,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(172,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(361,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(315,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(144,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(242,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(259,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(258,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(40,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(142,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(108,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(109,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(147,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(154,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(214,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(227,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(353,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(314,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(313,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(306,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(280,std::make_pair(eFID,eFID)),
    Function_ArgumentsType(267,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(150,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(163,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(162,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(354,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(106,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(125,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(282,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(112,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(289,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(332,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(300,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(146,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(285,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(278,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(176,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(175,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(171,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(358,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(339,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(266,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(62,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(327,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(287,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(103,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(286,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(75,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(223,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(185,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(141,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(265,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(102,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(145,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(329,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(111,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(101,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(309,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(104,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(36,std::make_pair(eInt,eNULL)),
    Function_ArgumentsType(42,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(133,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(43,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(134,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(44,std::make_pair(eFID,eNULL)),
    Function_ArgumentsType(135,std::make_pair(eNULL,eNULL)),
    Function_ArgumentsType(323,std::make_pair(eNULL,eNULL))
    };

typedef std::map<unsigned int, char *>::value_type Function_NameType;
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

const std::map<unsigned int, std::pair<unsigned int,unsigned int>> Function_Arguments(Function_ArgumentsInit, Function_ArgumentsInit + sizeof(Function_ArgumentsInit) / sizeof(Function_ArgumentsInit[0]));

const std::map<unsigned int, char *> Function_Name(Function_NameInit, Function_NameInit + sizeof(Function_NameInit) / sizeof(Function_NameInit[0]));
const std::map<unsigned int, char *> Comparison_Name(Comparison_NameInit, Comparison_NameInit + sizeof(Comparison_NameInit) / sizeof(Comparison_NameInit[0]));
const std::map<unsigned int, char *> IDLEGroup_Name(IDLEGroup_NameInit, IDLEGroup_NameInit + sizeof(IDLEGroup_NameInit) / sizeof(IDLEGroup_NameInit[0]));
const std::map<unsigned int, char *> PACKAIType_Name(PACKAIType_NameInit, PACKAIType_NameInit + sizeof(PACKAIType_NameInit) / sizeof(PACKAIType_NameInit[0]));
const std::map<unsigned int, char *> PACKLocType_Name(PACKLocType_NameInit, PACKLocType_NameInit + sizeof(PACKLocType_NameInit) / sizeof(PACKLocType_NameInit[0]));
const std::map<unsigned int, char *> PACKTargetType_Name(PACKTargetType_NameInit, PACKTargetType_NameInit + sizeof(PACKTargetType_NameInit) / sizeof(PACKTargetType_NameInit[0]));
