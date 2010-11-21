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
#include <boost/unordered_set.hpp>
#include <map>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#ifndef UINT8
    #define UINT8 unsigned char
#endif

#ifndef UINT8ARRAY
    #define UINT8ARRAY unsigned char *
#endif

#ifndef UINT16
    #define UINT16 unsigned short
#endif

#ifndef UINT32
    #define UINT32 unsigned long
#endif

#ifndef SINT8
    #define SINT8 signed char
#endif

#ifndef SINT16
    #define SINT16 signed short
#endif

#ifndef SINT32
    #define SINT32 signed long
#endif

#ifndef UINT32ARRAY
    #define UINT32ARRAY unsigned long *
#endif

#ifndef FLOAT32
    #define FLOAT32 float
#endif

#ifndef STRING
    #define STRING char *
#endif

#ifndef STRINGARRAY
    #define STRINGARRAY char **
#endif

#ifndef FORMID
    #define FORMID unsigned long
#endif

#ifndef FORMID_OR_UINT32
    #define FORMID_OR_UINT32 unsigned long
#endif

#ifndef FORMIDARRAY
    #define FORMIDARRAY unsigned long *
#endif

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

#ifndef END_HARDCODED_IDS
    #define END_HARDCODED_IDS    0x00000800
#endif

#ifndef MAJOR_VERSION
    #define MAJOR_VERSION    0
#endif

#ifndef MINOR_VERSION
    #define MINOR_VERSION    5
#endif

#ifndef REVISION_VERSION
    #define REVISION_VERSION    0
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

class Ex_INVALIDFORMID : public std::exception
    {
    public:
        const char * __CLR_OR_THIS_CALL what() const
            {return "Invalid FormID";}
    };

typedef unsigned long * FormID;

extern time_t lastSave;

extern const std::map<unsigned long, std::pair<unsigned long,unsigned long>> Function_Arguments;
extern const std::map<unsigned long, char *> Function_Name;
extern const std::map<unsigned long, char *> Comparison_Name;
extern const std::map<unsigned long, char *> IDLEGroup_Name;
extern const std::map<unsigned long, char *> PACKAIType_Name;
extern const std::map<unsigned long, char *> PACKLocType_Name;
extern const std::map<unsigned long, char *> PACKTargetType_Name;
extern const std::map<unsigned long, char *> HardCodedFormID_EDID;



inline void _readBuffer(void *_DstBuf, const unsigned char *_SrcBuf, const unsigned long &_MaxCharCount, unsigned long &_BufPos)
    {
    memcpy(_DstBuf,_SrcBuf + _BufPos,_MaxCharCount);
    _BufPos += _MaxCharCount;
    }

#ifdef _DEBUG
void PrintIndent(const unsigned long &indentation);
char * PrintFormID(FormID curFormID);
char * PrintFormID(unsigned long curFormID);
#endif

//template <class T>
//class ArrayVisitor
//    {
//    private:
//        const std::vector<T> &VisitedArray;
//    public:
//        ArrayVisitor(const std::vector<T> &cVisitedArray):VisitedArray(cVisitedArray) {}
//
//        template <class Op>
//        void Visit(Op& op) const
//            {
//            for(unsigned long x = 0; x < VisitedArray.size(); ++x)
//                op.Accept(VisitedArray[x]);
//	        }
//    };
//

//typedef ArrayVisitor<FormID> FormIDVisitor;

bool AlmostEqual(float A, float B, int maxUlps);

//Base record field. Vestigial.
//Used when it isn't known if the record is required or optional.
template<class T>
struct SubRecord
    {
    T value;
    bool isLoaded;
    SubRecord():isLoaded(false),value() {}
    unsigned long GetSize() const
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
    bool Read(unsigned char *buffer, unsigned long subSize, unsigned long &curPos)
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
    bool operator ==(const SubRecord<T> &other) const
        {
        return (value == other.value &&
                isLoaded == other.isLoaded);
        }
    bool operator !=(const SubRecord<T> &other) const
        {
        return !(*this == other);
        }
    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned long &indentation)
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

//Used for subrecords that are required
//Even if not actually loaded from disk, they are always considered loaded even if they're explicitly unloaded.
//Unloading them simply resets the values to default.
template<class T>
struct ReqSubRecord
    {
    T value;
    ReqSubRecord():value() {}
    unsigned long GetSize() const
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
    bool Read(unsigned char *buffer, unsigned long subSize, unsigned long &curPos)
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
    bool operator ==(const ReqSubRecord<T> &other) const
        {
        return (value == other.value);
        }
    bool operator !=(const ReqSubRecord<T> &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned long &indentation)
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

//Used for subrecords that are optional
//Even if loaded, they are considered unloaded if they're equal to their defaults
template<class T>
struct OptSubRecord
    {
    T *value;
    OptSubRecord():value(NULL) {}
    ~OptSubRecord()
        {
        delete value;
        }
    unsigned long GetSize() const
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
    bool Read(unsigned char *buffer, unsigned long subSize, unsigned long &curPos)
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

    OptSubRecord<T>& operator = (const OptSubRecord<T> &rhs)
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
    bool operator ==(const OptSubRecord<T> &other) const
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
    bool operator !=(const OptSubRecord<T> &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned long &indentation)
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

//Identical to OptSubRecord except for IsLoaded
//Once loaded, they are always considered loaded unless they're explicitly unloaded.
//They don't compare to the default value to see if they're
// still considered loaded.
template<class T>
struct SemiOptSubRecord
    {
    T *value;
    SemiOptSubRecord():value(NULL) {}
    ~SemiOptSubRecord()
        {
        delete value;
        }
    unsigned long GetSize() const
        {return sizeof(T);}
    bool IsLoaded() const
        {
        T defaultValue;
        return (value != NULL);
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
    bool Read(unsigned char *buffer, unsigned long subSize, unsigned long &curPos)
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

    SemiOptSubRecord<T>& operator = (const SemiOptSubRecord<T> &rhs)
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
    bool operator ==(const SemiOptSubRecord<T> &other) const
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
    bool operator !=(const SemiOptSubRecord<T> &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned long &indentation)
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

struct StringRecord
    {
    char *value;
    StringRecord():value(NULL) {}
    StringRecord(const StringRecord &p):value(NULL)
        {
        if(!p.IsLoaded())
            return;
        unsigned long size = p.GetSize();
        value = new char[size];
        memcpy(value, p.value, size);
        }
    StringRecord(const char *p):value(NULL)
        {
        unsigned long size = (unsigned long)strlen(p) + 1;
        value = new char[size];
        strcpy_s(value, size, p);
        }
    ~StringRecord()
        {
        delete []value;
        }
    unsigned long GetSize() const
        {return (unsigned long)strlen(value) + 1;}
    bool IsLoaded() const
        {return value != NULL;}
    void Load() {};
    void Unload()
        {
        delete []value;
        value = NULL;
        }
    bool Read(unsigned char *buffer, const unsigned long &subSize, unsigned long &curPos)
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
    void Copy(const StringRecord &FieldValue)
        {
        if(!FieldValue.IsLoaded())
            return;
        delete []value;
        unsigned long size = FieldValue.GetSize();
        value = new char[size];
        strcpy_s(value, size, FieldValue.value);
        }
    void Copy(char *FieldValue)
        {
        delete []value;
        unsigned long size = (unsigned long)strlen(FieldValue) + 1;
        value = new char[size];
        strcpy_s(value, size, FieldValue);
        }
    StringRecord& operator = (const StringRecord &rhs)
        {
        if(this != &rhs)
            {
            if(rhs.IsLoaded())
                Copy(rhs);
            else
                Unload();
            }
        return *this;
        }
    bool operator ==(const StringRecord &other) const
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
    bool operator !=(const StringRecord &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned long &indentation)
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

struct InsensitiveStringRecord
    {
    char *value;
    InsensitiveStringRecord():value(NULL) {}
    InsensitiveStringRecord(const InsensitiveStringRecord &p):value(NULL)
        {
        if(!p.IsLoaded())
            return;
        unsigned long size = p.GetSize();
        value = new char[size];
        memcpy(value, p.value, size);
        }
    InsensitiveStringRecord(const char *p):value(NULL)
        {
        unsigned long size = (unsigned long)strlen(p) + 1;
        value = new char[size];
        strcpy_s(value, size, p);
        unsigned long len = (unsigned long)strlen(value);
        for (unsigned long i = 0; i < len; ++i)
           value[i] = tolower(value[i]);
        }
    ~InsensitiveStringRecord()
        {
        delete []value;
        }
    unsigned long GetSize() const
        {return (unsigned long)strlen(value) + 1;}
    bool IsLoaded() const
        {return value != NULL;}
    void Load() {};
    void Unload()
        {
        delete []value;
        value = NULL;
        }
    bool Read(unsigned char *buffer, const unsigned long &subSize, unsigned long &curPos)
        {
        if(IsLoaded())
            {
            curPos += subSize;
            return false;
            }
        value = new char[subSize];
        memcpy(value, buffer + curPos, subSize);

        unsigned long len = (unsigned long)strlen(value);
        for (unsigned long i = 0; i < len; ++i)
           value[i] = tolower(value[i]);
        curPos += subSize;
        return true;
        }
    void Copy(const InsensitiveStringRecord &FieldValue)
        {
        if(!FieldValue.IsLoaded())
            return;
        delete []value;
        unsigned long size = FieldValue.GetSize();
        value = new char[size];
        strcpy_s(value, size, FieldValue.value);
        }
    void Copy(char *FieldValue)
        {
        delete []value;
        unsigned long size = (unsigned long)strlen(FieldValue) + 1;
        value = new char[size];
        strcpy_s(value, size, FieldValue);
        unsigned long len = (unsigned long)strlen(value);
        for (unsigned long i = 0; i < len; ++i)
           value[i] = tolower(value[i]);
        }
    InsensitiveStringRecord& operator = (const InsensitiveStringRecord &rhs)
        {
        if(this != &rhs)
            {
            if(rhs.IsLoaded())
                Copy(rhs);
            else
                Unload();
            }
        return *this;
        }
    bool operator ==(const InsensitiveStringRecord &other) const
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
    bool operator !=(const InsensitiveStringRecord &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned long &indentation)
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

struct NonNullStringRecord
    {
    char *value;
    NonNullStringRecord():value(NULL) {}
    NonNullStringRecord(const NonNullStringRecord &p):value(NULL)
        {
        if(!p.IsLoaded())
            return;
        unsigned long size = p.GetSize();
        value = new char[size + 1];
        memcpy(value, p.value, size + 1);
        }
    NonNullStringRecord(const char *p):value(NULL)
        {
        unsigned long size = (unsigned long)strlen(p) + 1;
        value = new char[size];
        strcpy_s(value, size, p);
        }
    ~NonNullStringRecord()
        {
        delete []value;
        }
    unsigned long GetSize() const
        {return (unsigned long)strlen(value);}
    bool IsLoaded() const
        {return value != NULL;}
    void Load() {};
    void Unload()
        {
        delete []value;
        value = NULL;
        }
    bool Read(unsigned char *buffer, const unsigned long &subSize, unsigned long &curPos)
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
    void Copy(const NonNullStringRecord &FieldValue)
        {
        if(!FieldValue.IsLoaded())
            return;
        delete []value;
        unsigned long size = FieldValue.GetSize();
        value = new char[size + 1];
        memcpy(value, FieldValue.value, size);
        value[size] = 0x00;
        }
    void Copy(char *FieldValue)
        {
        delete []value;
        unsigned long size = (unsigned long)strlen(FieldValue) + 1;
        value = new char[size];
        strcpy_s(value, size, FieldValue);
        }
    NonNullStringRecord& operator = (const NonNullStringRecord &rhs)
        {
        if(this != &rhs)
            {
            if(rhs.IsLoaded())
                Copy(rhs);
            else
                Unload();
            }
        return *this;
        }
    bool operator ==(const NonNullStringRecord &other) const
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
    bool operator !=(const NonNullStringRecord &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned long &indentation)
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

struct RawRecord
    {
    unsigned long size;
    unsigned char *value;
    RawRecord():size(0), value(NULL) {}
    RawRecord(const RawRecord &p):value(NULL)
        {
        if(!p.IsLoaded())
            return;
        size = p.size;
        value = new unsigned char[size];
        memcpy(value,p.value,size);
        }
    ~RawRecord()
        {
        delete []value;
        }
    unsigned long GetSize() const
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
    bool Read(unsigned char *buffer, unsigned long subSize, unsigned long &curPos)
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
    void Copy(unsigned char *FieldValue, unsigned long nSize)
        {
        delete []value;
        size = nSize;
        value = new unsigned char[size];
        memcpy(value, FieldValue, size);
        }
    RawRecord& operator = (const RawRecord &rhs)
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
    bool operator ==(const RawRecord &other) const
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
    bool operator !=(const RawRecord &other) const
        {
        return !(*this == other);
        }

    #ifdef _DEBUG
    void Debug(const char *name, int debugLevel, unsigned long &indentation)
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
                    for(unsigned long x = 0;x < size;x++)
                        printf("%02X", value[x]);
                    printf("\n");
                    }
            }
        }
    #endif
    };

class FormIDHandlerClass
    {
    public:
        char *FileName;
        std::vector<StringRecord> &MAST;
        unsigned long &nextObject;
        unsigned char CollapsedIndex;
        bool bMastersChanged;
        unsigned char ExpandTable[255];
        unsigned char CollapseTable[255];
        bool IsEmpty;

        boost::unordered_set<unsigned long> NewTypes;
        std::vector<char *> LoadOrder255;
        unsigned char ExpandedIndex;
        FormIDHandlerClass(char *cFileName, std::vector<StringRecord> &cMAST, unsigned long &cNextObject):FileName(cFileName), MAST(cMAST), nextObject(cNextObject),
                                                                                               ExpandedIndex(0), CollapsedIndex(0), bMastersChanged(false),
                                                                                               IsEmpty(true) {}
        ~FormIDHandlerClass() {}
        void SetLoadOrder(std::vector<char *> &cLoadOrder);
        unsigned long NextExpandedFID();
        void CreateFormIDLookup(const unsigned char expandedIndex);
        void UpdateFormIDLookup();
        unsigned long AssignToMod(unsigned long curFormID);
        unsigned long AssignToMod(unsigned long *curFormID);
        void AddMaster(const char *curMaster);
        bool MastersChanged();
        bool IsNewRecord(const unsigned long *&recordFID);
        bool IsNewRecord(const unsigned long &recordFID);
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
        unsigned long _BufEnd;
        unsigned long _TotalWritten;
        int fh;
    public:
        _FileHandler():m_region(NULL), f_map(NULL), _Buffer(NULL), _BufSize(0), _BufPos(0), _BufEnd(0), _TotalWritten(0), fh(-1) {}
        _FileHandler(unsigned long nSize):m_region(NULL), f_map(NULL), _Buffer(NULL), _BufSize(nSize), _BufPos(0), _BufEnd(0), _TotalWritten(0), fh(-1)
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
        void read(void *_DestBuf, unsigned long _MaxCharCount);
        unsigned char *getBuffer(unsigned long _Offset);
        unsigned long write(const void *_SrcBuf, unsigned long _MaxCharCount);
        void writeSubRecord(unsigned long _Type, const void *_SrcBuf, unsigned long _MaxCharCount);
        unsigned long writeAt(unsigned long _Offset, const void *_SrcBuf, unsigned long _MaxCharCount);
        unsigned long UnusedCache();
        bool IsCached(unsigned long _Offset);
        int close();
        void reserveBuffer(unsigned long nSize);
        void flush();
    };

enum API_FieldTypes {
    UNKNOWN_FIELD = 0,
    JUNK_FIELD,
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
    SUBRECORD_FIELD,
    PARENTRECORD_FIELD,
    RADIAN_FIELD,
    FID_OR_UINT_FIELD,
    BOOL_FIELD
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

class CreateRecordOptions
    {
    private:
        enum createFlags
            {
            fSetAsOverride       = 0x00000001,
            fSetAsWorldCell      = 0x00000002,
            fCopyWorldCellStatus = 0x00000004
            };
    public:
        CreateRecordOptions();
        CreateRecordOptions(unsigned long nFlags);
        ~CreateRecordOptions();

        bool SetAsOverride;
        bool SetAsWorldCell;
        bool CopyWorldCellStatus;

        unsigned long GetFlagField();
    };

class ModFlags
    {
    private:
        enum addModFlags
            {
            fMerge             = 0x00000001,
            fScan              = 0x00000002,
            fCreateIfNotExist  = 0x00000004
            };
    public:
        ModFlags();
        ModFlags(unsigned long nFlags);
        ~ModFlags();

        bool Merge;
        bool Scan;
        bool CreateIfNotExist;

        bool IsDummy, IsOpen, LoadedGRUPs, IsNew;

        unsigned long GetFlagField();
    };
