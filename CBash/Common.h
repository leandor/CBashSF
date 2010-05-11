# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#pragma once

// Common.h
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <vector>
#include <map>
#include <boost/threadpool.hpp>

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


#ifndef NUMTHREADS
#define NUMTHREADS    boost::thread::hardware_concurrency()
#endif

#ifndef OBJECT_ID_START
#define OBJECT_ID_START    0x00000800
#endif

typedef unsigned int * FormID;

extern time_t lastSave;
//extern std::vector<FormID> FormIDsToRegister;
//extern std::vector<FormID> FormIDsToUnregister;
//extern std::vector<FormID> FormIDsToCheckMaster;

#ifdef _DEBUG
void PrintIndent(const unsigned int &indentation);
char * PrintFormID(FormID curFormID);
char * PrintFormID(unsigned int curFormID);
#endif

inline void _assignBuffer(void **_DstBuf, unsigned char *_SrcBuf, unsigned int _MaxCharCount, unsigned int &_BufPos)
    {
    *_DstBuf = &_SrcBuf[_BufPos];
    _BufPos += _MaxCharCount;
    }

inline void _readBuffer(void *_DstBuf, const void *_SrcBuf, unsigned int _MaxCharCount, unsigned int &_BufPos)
    {
    memcpy(_DstBuf,(unsigned char*)_SrcBuf+_BufPos,_MaxCharCount);
    _BufPos += _MaxCharCount;
    }

template<class T>
struct RecordField
    {
    T value;
    bool isLoaded;
    RecordField():isLoaded(false) {}
    unsigned int GetSize() const
        {return sizeof(T);}
    bool IsLoaded() const
        {return isLoaded;}
    bool Read(unsigned char *buffer, unsigned int subSize, unsigned int &curPos)
        {
        if(isLoaded)
            {
            curPos += subSize;
            return false;
            }
        if(subSize > sizeof(T))
            printf("Hug?\n");
        memcpy(&value, buffer + curPos, subSize);
        isLoaded = true;
        //size = subSize;
        curPos += subSize;
        return true;
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
    ReqRecordField() {}
    unsigned int GetSize() const
        {return sizeof(T);}
    bool IsLoaded() const
        {return true;}
    bool Read(unsigned char *buffer, unsigned int subSize, unsigned int &curPos)
        {
        if(subSize > sizeof(T))
            printf("Huh? subSize:%u, sizeof:%u\n", subSize, sizeof(T));
        memcpy(&value, buffer + curPos, subSize);
        //size = subSize;
        curPos += subSize;
        return true;
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
        {return value != NULL;}
    void Load()
        {
        if(value == NULL)
            value = new T();
        }
    bool Read(unsigned char *buffer, unsigned int subSize, unsigned int &curPos)
        {
        if(value != NULL)
            {
            curPos += subSize;
            return false;
            }
        if(subSize > sizeof(T))
            printf("Hui?\n");
        value = new T();
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
                *value = *rhs.value;
                }
            else
                {
                delete value;
                value = NULL;
                }
        return *this;
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
        std::vector<char *> LoadOrder;
        unsigned char ExpandIndex[255];
        unsigned char CollapseIndex[255];
        unsigned char ExpandedIndex;
        unsigned char CollapsedIndex;

    public:
        _FormIDHandler(char *cFileName, std::vector<STRING> &cMAST, unsigned int &cNextObject):FileName(cFileName), MAST(cMAST), nextObject(cNextObject) {}
        void SetLoadOrder(std::vector<char *> &cLoadOrder);
        unsigned int NextExpandedFID();
        void UpdateFormIDLookup();
        void UpdateFormIDLookup(const unsigned char &expandedIndex);
        void CollapseFormID(unsigned int &curFormID);
        void CollapseFormID(unsigned int *&curFormID);
        void ExpandFormID(unsigned int &curFormID);
        void ExpandFormID(unsigned int *&curFormID);
        void AddMaster(unsigned int &curFormID);
        void AddMaster(unsigned int *&curFormID);
    };

extern _FormIDHandler *FormIDHandler;

extern const std::map<unsigned int, std::pair<unsigned int,unsigned int>> Function_Arguments;
extern const std::map<unsigned int, char *> Function_Name;
extern const std::map<unsigned int, char *> Comparison_Name;
extern const std::map<unsigned int, char *> IDLEGroup_Name;
extern const std::map<unsigned int, char *> PACKAIType_Name;
extern const std::map<unsigned int, char *> PACKLocType_Name;
extern const std::map<unsigned int, char *> PACKTargetType_Name;


struct sameStr
    {
	bool operator()( const char* s1, const char* s2 ) const
	    {
		return _stricmp( s1, s2 ) < 0;
	    }
    };

struct sortFormID
    {
     bool operator()(const FormID l, const FormID r) const
        {
        return *l < *r;
        }
    };

//bool sortLoad(const char *l, const char *r);
//bool sameFile(const char *l, const char *r);

bool FileExists(const char *FileName);

void _assignBuffer(void **_DstBuf, unsigned char *_SrcBuf, unsigned int _MaxCharCount, unsigned int &_BufPos);
void _readBuffer(void *_DstBuf, const void *_SrcBuf, unsigned int _MaxCharCount, unsigned int &_BufPos);
void _writeBuffer(void *_DstBuf, const void *_SrcBuf, unsigned int _MaxCharCount, unsigned int &_BufPos);
void _writeSubRecord(void *_DstBuf, unsigned int _Type, unsigned int _MaxCharCount, const void *_SrcBuf, unsigned int &_BufPos);


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
