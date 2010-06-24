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
#pragma once

// Common.h
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <share.h>
#include <errno.h>
#include <exception>
#include <vector>
#include <list>
#include <map>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef BUFFERSIZE
#define BUFFERSIZE    65536
#endif

#ifndef OBJECT_ID_START
#define OBJECT_ID_START    0x00000800
#endif

#ifndef MAJOR_VERSION
#define MAJOR_VERSION    0
#endif

#ifndef MINOR_VERSION
#define MINOR_VERSION    4
#endif

#ifndef REVISION_VERSION
#define REVISION_VERSION    2
#endif

class Ex_NULL : public std::exception
    {
    public:
        const char * __CLR_OR_THIS_CALL what() const
            {return "NULL Pointer";}
    };

class Ex_INVALIDINDEX : public std::exception
    {
    public:
        const char * __CLR_OR_THIS_CALL what() const
            {return "Invalid Index";}
    };

typedef unsigned int * FormID;

extern time_t lastSave;

extern const std::map<unsigned int, std::pair<unsigned int,unsigned int>> Function_Arguments;
extern const std::map<unsigned int, char *> Function_Name;
extern const std::map<unsigned int, char *> Comparison_Name;
extern const std::map<unsigned int, char *> IDLEGroup_Name;
extern const std::map<unsigned int, char *> PACKAIType_Name;
extern const std::map<unsigned int, char *> PACKLocType_Name;
extern const std::map<unsigned int, char *> PACKTargetType_Name;

inline void _readBuffer(void *_DstBuf, const unsigned char *_SrcBuf, const unsigned int &_MaxCharCount, unsigned int &_BufPos)
    {
    memcpy(_DstBuf,_SrcBuf + _BufPos,_MaxCharCount);
    _BufPos += _MaxCharCount;
    }

#ifdef _DEBUG
void PrintIndent(const unsigned int &indentation);
char * PrintFormID(FormID curFormID);
char * PrintFormID(unsigned int curFormID);
#endif

bool AlmostEqual(float A, float B, int maxUlps);

template<class T>
struct RecordField
    {
    T value;
    bool isLoaded;
    RecordField():isLoaded(false),value() {}
    unsigned int GetSize() const
        {return sizeof(T);}
    bool IsLoaded() const
        {
        T defaultValue;
        return (isLoaded && value != defaultValue);
        }
    void Load()
        {
        isLoaded = true;
        }
    void Unload()
        {
        T newValue;
        value.~T();
        value = newValue;
        isLoaded = false;
        }
    bool Read(unsigned char *buffer, unsigned int subSize, unsigned int &curPos)
        {
        if(isLoaded)
            {
            curPos += subSize;
            return false;
            }
        if(subSize > sizeof(T))
            {
            printf("Rec? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
            memcpy(&value, buffer + curPos, sizeof(T));
            }
        else
            memcpy(&value, buffer + curPos, subSize);
        isLoaded = true;
        //size = subSize;
        curPos += subSize;
        return true;
        }
    T *operator->() const
        {
        return &value;
        }
    bool operator ==(const RecordField<T> &other) const
        {
        return (value == other.value && 
                isLoaded == other.isLoaded);
        }
    bool operator !=(const RecordField<T> &other) const
        {
        return !(*this == other);
        }
    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned int &indentation)
        {
        if(isLoaded)
            {
            if(name)
                {
                PrintIndent(indentation);
                printf("%s:\n", name);
                }
            value.Debug(debugLevel, indentation);
            }
        }
    #endif
    };

template<class T>
struct ReqRecordField
    {
    T value;
    ReqRecordField():value() {}
    unsigned int GetSize() const
        {return sizeof(T);}
    bool IsLoaded() const
        {return true;}
    void Load() {};
    void Unload()
        {
        T newValue;
        value.~T();
        value = newValue;
        }
    bool Read(unsigned char *buffer, unsigned int subSize, unsigned int &curPos)
        {
        if(subSize > sizeof(T))
            {
            printf("Req? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
            memcpy(&value, buffer + curPos, sizeof(T));
            }
        else
            memcpy(&value, buffer + curPos, subSize);
        //size = subSize;
        curPos += subSize;
        return true;
        }
    T *operator->() const
        {
        return &value;
        }
    bool operator ==(const ReqRecordField<T> &other) const
        {
        return (value == other.value);
        }
    bool operator !=(const ReqRecordField<T> &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned int &indentation)
        {
        if(name)
            {
            PrintIndent(indentation);
            printf("%s:\n", name);
            }
        value.Debug(debugLevel, indentation);
        }
    #endif
    };

template<class T>
struct OptRecordField
    {
    T *value;
    OptRecordField():value(NULL) {}
    ~OptRecordField()
        {
        delete value;
        }
    unsigned int GetSize() const
        {return sizeof(T);}
    bool IsLoaded() const
        {
        T defaultValue;
        return (value != NULL && *value != defaultValue);
        }
    void Load()
        {
        if(value == NULL)
            value = new T();
        }
    void Unload()
        {
        delete value;
        value = NULL;
        }
    bool Read(unsigned char *buffer, unsigned int subSize, unsigned int &curPos)
        {
        if(value != NULL)
            {
            curPos += subSize;
            return false;
            }
        value = new T();
        if(subSize > sizeof(T))
            {
            printf("Opt? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
            memcpy(value, buffer + curPos, sizeof(T));
            }
        else
            memcpy(value, buffer + curPos, subSize);
        curPos += subSize;
        return true;
        }
    T *operator->() const
        {
        return value;
        }

    OptRecordField<T>& operator = (const OptRecordField<T> &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                {
                if(value == NULL)
                    {
                    value = new T();
                    }
                else
                    value->~T();
                *value = *rhs.value;
                }
            else
                {
                delete value;
                value = NULL;
                }
        return *this;
        }
    bool operator ==(const OptRecordField<T> &other) const
        {
        if(!IsLoaded())
            {
            if(!other.IsLoaded())
                return true;
            }
        else if(other.IsLoaded() && *value == *other.value)
            return true;
        return false;
        }
    bool operator !=(const OptRecordField<T> &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned int &indentation)
        {
        if(isLoaded)
            {
            if(name)
                {
                PrintIndent(indentation);
                printf("%s:\n", name);
                }
            value->Debug(debugLevel, indentation);
            }
        }
    #endif
    };

struct STRING
    {
    char *value;
    STRING():value(NULL) {}
    STRING(const STRING &p):value(NULL)
        {
        if(!p.IsLoaded())
            return;
        unsigned int size = p.GetSize();
        value = new char[size];
        memcpy(value, p.value, size);
        }
    STRING(const char *p):value(NULL)
        {
        unsigned int size = (unsigned int)strlen(p) + 1;
        value = new char[size];
        strcpy_s(value, size, p);
        }
    ~STRING()
        {
        delete []value;
        }
    unsigned int GetSize() const
        {return (unsigned int)strlen(value) + 1;}
    bool IsLoaded() const
        {return value != NULL;}
    void Load() {};
    void Unload()
        {
        delete []value;
        value = NULL;
        }
    bool Read(unsigned char *buffer, const unsigned int &subSize, unsigned int &curPos)
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
    void Copy(const STRING &FieldValue)
        {
        if(!FieldValue.IsLoaded())
            return;
        delete []value;
        unsigned int size = FieldValue.GetSize();
        value = new char[size];
        strcpy_s(value, size, FieldValue.value);
        }
    void Copy(char *FieldValue)
        {
        delete []value;
        unsigned int size = (unsigned int)strlen(FieldValue) + 1;
        value = new char[size];
        strcpy_s(value, size, FieldValue);
        }
    STRING& operator = (const STRING &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                Copy(rhs);
            else
                {
                delete []value;
                value = NULL;
                }
        return *this;
        }
    bool operator ==(const STRING &other) const
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
    bool operator !=(const STRING &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned int &indentation)
        {
        if(IsLoaded())
            {
            if(name)
                {
                PrintIndent(indentation);
                printf("%s:\n", name);
                }
            if(debugLevel > 3)
                {
                indentation += 2;
                PrintIndent(indentation);
                printf("%s = %s\n", name, value);
                indentation -= 2;
                }
            }
        }
    #endif
    };

struct ISTRING
    {
    char *value;
    ISTRING():value(NULL) {}
    ISTRING(const ISTRING &p):value(NULL)
        {
        if(!p.IsLoaded())
            return;
        unsigned int size = p.GetSize();
        value = new char[size];
        memcpy(value, p.value, size);
        }
    ISTRING(const char *p):value(NULL)
        {
        unsigned int size = (unsigned int)strlen(p) + 1;
        value = new char[size];
        strcpy_s(value, size, p);
        unsigned int len = (unsigned int)strlen(value);
        for (unsigned int i = 0; i < len; ++i)
           value[i] = tolower(value[i]);
        }
    ~ISTRING()
        {
        delete []value;
        }
    unsigned int GetSize() const
        {return (unsigned int)strlen(value) + 1;}
    bool IsLoaded() const
        {return value != NULL;}
    void Load() {};
    void Unload()
        {
        delete []value;
        value = NULL;
        }
    bool Read(unsigned char *buffer, const unsigned int &subSize, unsigned int &curPos)
        {
        if(IsLoaded())
            {
            curPos += subSize;
            return false;
            }
        value = new char[subSize];
        memcpy(value, buffer + curPos, subSize);

        unsigned int len = (unsigned int)strlen(value);
        for (unsigned int i = 0; i < len; ++i)
           value[i] = tolower(value[i]);
        curPos += subSize;
        return true;
        }
    void Copy(const ISTRING &FieldValue)
        {
        if(!FieldValue.IsLoaded())
            return;
        delete []value;
        unsigned int size = FieldValue.GetSize();
        value = new char[size];
        strcpy_s(value, size, FieldValue.value);
        }
    void Copy(char *FieldValue)
        {
        delete []value;
        unsigned int size = (unsigned int)strlen(FieldValue) + 1;
        value = new char[size];
        strcpy_s(value, size, FieldValue);
        unsigned int len = (unsigned int)strlen(value);
        for (unsigned int i = 0; i < len; ++i)
           value[i] = tolower(value[i]);
        }
    ISTRING& operator = (const ISTRING &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                Copy(rhs);
            else
                {
                delete []value;
                value = NULL;
                }
        return *this;
        }
    bool operator ==(const ISTRING &other) const
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
    bool operator !=(const ISTRING &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned int &indentation)
        {
        if(IsLoaded())
            {
            if(name)
                {
                PrintIndent(indentation);
                printf("%s:\n", name);
                }
            if(debugLevel > 3)
                {
                indentation += 2;
                PrintIndent(indentation);
                printf("%s = %s\n", name, value);
                indentation -= 2;
                }
            }
        }
    #endif
    };

struct NONNULLSTRING
    {
    char *value;
    NONNULLSTRING():value(NULL) {}
    NONNULLSTRING(const NONNULLSTRING &p):value(NULL)
        {
        if(!p.IsLoaded())
            return;
        unsigned int size = p.GetSize();
        value = new char[size + 1];
        memcpy(value, p.value, size + 1);
        }
    NONNULLSTRING(const char *p):value(NULL)
        {
        unsigned int size = (unsigned int)strlen(p) + 1;
        value = new char[size];
        strcpy_s(value, size, p);
        }
    ~NONNULLSTRING()
        {
        delete []value;
        }
    unsigned int GetSize() const
        {return (unsigned int)strlen(value);}
    bool IsLoaded() const
        {return value != NULL;}
    void Load() {};
    void Unload()
        {
        delete []value;
        value = NULL;
        }
    bool Read(unsigned char *buffer, const unsigned int &subSize, unsigned int &curPos)
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
    void Copy(const NONNULLSTRING &FieldValue)
        {
        if(!FieldValue.IsLoaded())
            return;
        delete []value;
        unsigned int size = FieldValue.GetSize();
        value = new char[size + 1];
        memcpy(value, FieldValue.value, size);
        value[size] = 0x00;
        }
    void Copy(char *FieldValue)
        {
        delete []value;
        unsigned int size = (unsigned int)strlen(FieldValue) + 1;
        value = new char[size];
        strcpy_s(value, size, FieldValue);
        }
    NONNULLSTRING& operator = (const NONNULLSTRING &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                Copy(rhs);
            else
                {
                delete []value;
                value = NULL;
                }
        return *this;
        }
    bool operator ==(const NONNULLSTRING &other) const
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
    bool operator !=(const NONNULLSTRING &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned int &indentation)
        {
        if(IsLoaded())
            {
            if(name)
                {
                PrintIndent(indentation);
                printf("%s:\n", name);
                }
            if(debugLevel > 3)
                {
                indentation += 2;
                PrintIndent(indentation);
                printf("%s = %s\n", name, value);
                indentation -= 2;
                }
            }
        }
    #endif
    };

struct RAWBYTES
    {
    unsigned int size;
    unsigned char *value;
    RAWBYTES():size(0), value(NULL) {}
    RAWBYTES(const RAWBYTES &p):value(NULL)
        {
        if(!p.IsLoaded())
            return;
        size = p.size;
        value = new unsigned char[size];
        memcpy(value,p.value,size);
        }
    ~RAWBYTES()
        {
        delete []value;
        }
    unsigned int GetSize() const
        {return size;}
    bool IsLoaded() const
        {return value != NULL;}
    void Load() {};
    void Unload()
        {
        size = 0;
        delete []value;
        value = NULL;
        }
    bool Read(unsigned char *buffer, unsigned int subSize, unsigned int &curPos)
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
    void Copy(unsigned char *FieldValue, unsigned int nSize)
        {
        delete []value;
        size = nSize;
        value = new unsigned char[size];
        memcpy(value, FieldValue, size);
        }
    RAWBYTES& operator = (const RAWBYTES &rhs)
        {
        if (this != &rhs)
            if(rhs.value != NULL)
                Copy(rhs.value, rhs.size);
            else
                {
                delete []value;
                value = NULL;
                size = rhs.size;
                }
        return *this;
        }
    bool operator ==(const RAWBYTES &other) const
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
    bool operator !=(const RAWBYTES &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned int &indentation)
        {
        if(IsLoaded())
            {
            if(name)
                {
                PrintIndent(indentation);
                printf("%s:\n", name);
                }
            if(debugLevel > 3)
                if(debugLevel > 5)
                    {
                    for(unsigned int x = 0;x < size;x++)
                        printf("%02X", value[x]);
                    printf("\n");
                    }
            }
        }
    #endif
    };

class _FormIDHandler
    {
    private:
        char *FileName;
        std::vector<STRING> &MAST;
        unsigned int &nextObject;
        unsigned char ExpandIndex[255];
        unsigned char CollapseIndex[255];
        unsigned char CollapsedIndex;
        bool bMastersChanged;
    public:
        std::vector<char *> LoadOrder;
        unsigned char ExpandedIndex;
        _FormIDHandler(char *cFileName, std::vector<STRING> &cMAST, unsigned int &cNextObject):FileName(cFileName), MAST(cMAST), nextObject(cNextObject), ExpandedIndex(0), CollapsedIndex(0), bMastersChanged(false) {}
        ~_FormIDHandler() {}
        void SetLoadOrder(std::vector<char *> &cLoadOrder);
        unsigned int NextExpandedFID();
        void CreateFormIDLookup(const unsigned char expandedIndex);
        void UpdateFormIDLookup();
        void CollapseFormID(unsigned int &curFormID);
        void CollapseFormID(unsigned int *&curFormID);
        void ExpandFormID(unsigned int &curFormID);
        void ExpandFormID(unsigned int *&curFormID);
        unsigned int AssignToMod(unsigned int curFormID);
        unsigned int AssignToMod(unsigned int *curFormID);
        void AddMaster(unsigned int &curFormID);
        void AddMaster(unsigned int *&curFormID);
        bool MastersChanged();
        bool UsesMaster(const unsigned int *&recordFID, const unsigned char &MASTIndex);
        bool UsesMaster(const unsigned int &recordFID, const unsigned char &MASTIndex);
    };

bool FileExists(const char *FileName);

class _FileHandler
    {
    private:
        boost::interprocess::mapped_region *m_region;
        boost::interprocess::file_mapping *f_map;
        unsigned char *_Buffer;
        unsigned long _BufSize;
        unsigned long _BufPos;
        unsigned int _BufEnd;
        unsigned long _TotalWritten;
        int fh;
    public:
        _FileHandler():m_region(NULL), f_map(NULL), _Buffer(NULL), _BufSize(0), _BufPos(0), _BufEnd(0), _TotalWritten(0), fh(-1) {}
        _FileHandler(unsigned int nSize):m_region(NULL), f_map(NULL), _Buffer(NULL), _BufSize(nSize), _BufPos(0), _BufEnd(0), _TotalWritten(0), fh(-1)
            {
            if(_BufSize == 0)
                return;
            _Buffer = new unsigned char[_BufSize];
            }
        ~_FileHandler()
            {
            close();
            if(m_region == NULL && f_map == NULL && _Buffer != NULL)
                delete []_Buffer;
            }
        int open_ReadOnly(const char *FileName);
        int open_ReadWrite(const char *FileName);
        bool eof();
        unsigned long tell();
        unsigned long set_used(long _Used);
        void read(void *_DestBuf, unsigned int _MaxCharCount);
        unsigned char *getBuffer(unsigned long _Offset);
        unsigned long write(const void *_SrcBuf, unsigned int _MaxCharCount);
        void writeSubRecord(unsigned int _Type, const void *_SrcBuf, unsigned int _MaxCharCount);
        unsigned long writeAt(unsigned long _Offset, const void *_SrcBuf, unsigned int _MaxCharCount);
        unsigned long UnusedCache();
        bool IsCached(unsigned long _Offset);
        int close();
        void reserveBuffer(unsigned int nSize);
        void flush();
    };

enum API_FieldTypes {
    UNKNOWN_FIELD = -1,
    JUNK_FIELD = 0,
    INT_FIELD,
    FLOAT_FIELD,
    STRING_FIELD,
    UINT_FIELD,
    BYTES_FIELD,
    STRINGARRAY_FIELD,
    ULONG_FIELD,
    CHAR_FIELD,
    BYTE_FIELD,
    UBYTE_FIELD,
    FID_FIELD,
    LIST_FIELD,
    FIDARRAY_FIELD,
    SHORT_FIELD,
    USHORT_FIELD,
    UINTARRAY_FIELD,
    SUBRECORDS_FIELD,
    SUBRECORD_FIELD
    };

enum TopRecords {
    eUnknown=0,
    eTES4=0x34534554,
    eGRUP=0x50555247,
    eGMST=0x54534D47,
    eGLOB=0x424F4C47,
    eCLAS=0x53414C43,
    eFACT=0x54434146,
    eHAIR=0x52494148,
    eEYES=0x53455945,
    eRACE=0x45434152,
    eSOUN=0x4E554F53,
    eSKIL=0x4C494B53,
    eMGEF=0x4645474D,
    eSCPT=0x54504353,
    eLTEX=0x5845544C,
    eENCH=0x48434E45,
    eSPEL=0x4C455053,
    eBSGN=0x4E475342,
    eACTI=0x49544341,
    eAPPA=0x41505041,
    eARMO=0x4F4D5241,
    eBOOK=0x4B4F4F42,
    eCLOT=0x544F4C43,
    eCONT=0x544E4F43,
    eDOOR=0x524F4F44,
    eINGR=0x52474E49,
    eLIGH=0x4847494C,
    eMISC=0x4353494D,
    eSTAT=0x54415453,
    eGRAS=0x53415247,
    eTREE=0x45455254,
    eFLOR=0x524F4C46,
    eFURN=0x4E525546,
    eWEAP=0x50414557,
    eAMMO=0x4F4D4D41,
    eNPC_=0x5F43504E,
    eCREA=0x41455243,
    eLVLC=0x434C564C,
    eSLGM=0x4D474C53,
    eKEYM=0x4D59454B,
    eALCH=0x48434C41,
    eSBSP=0x50534253,
    eSGST=0x54534753,
    eLVLI=0x494C564C,
    eWTHR=0x52485457,
    eCLMT=0x544D4C43,
    eREGN=0x4E474552,
    eCELL=0x4C4C4543,
    eWRLD=0x444C5257,
    eDIAL=0x4C414944,
    eQUST=0x54535551,
    eIDLE=0x454C4449,
    ePACK=0x4B434150,
    eCSTY=0x59545343,
    eLSCR=0x5243534C,
    eLVSP=0x5053564C,
    eANIO=0x4F494E41,
    eWATR=0x52544157,
    eEFSH=0x48534645
    };

enum TopTypes {
    eTop,
    eWorld,
    eInteriorBlock,
    eInteriorSubBlock,
    eExteriorBlock,
    eExteriorSubBlock,
    eCellChildren,
    eTopicChildren,
    eCellPersistent,
    eCellTemporary,
    eCellVWD
    };

enum subRecords {
    eINFO = 0x4F464E49,
    eACHR = 0x52484341,
    eACRE = 0x45524341,
    eREFR = 0x52464552,
    ePGRD = 0x44524750,
    eROAD = 0x44414F52,
    eLAND = 0x444E414C
    };

enum varType {
    eNULL=0,
    eString,
    eInt,
    eFloat,
    eFID
    };
