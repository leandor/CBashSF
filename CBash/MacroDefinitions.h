#pragma once

//define or undef as desired
#undef CBASH_PROFILING
#undef CBASH_USE_LOGGING
#define CBASH_CHUNK_WARN
#undef CBASH_CHUNK_LCHECK

#define CBASH_DEBUG_CHUNK

//Peek into the data before and after to see what's up
#ifdef CBASH_DEBUG_CHUNK
    #define CBASH_CHUNK_DEBUG   for(SINT32 x = 32; x > 0; x--) \
                                    printf("%02X ", (buffer + curPos)[-x]); \
                                for(UINT32 x = 0; x < 32; x++) \
                                    printf("%02X ", (buffer + curPos)[x]); \
                                printf("\n\n"); \
                                for(SINT32 x = 32; x > 0; x--) \
                                    printf("%c", (buffer + curPos)[-x]); \
                                for(UINT32 x = 0; x < 32; x++) \
                                    printf("%c", (buffer + curPos)[x]); \
                                printf("\n");
#else
    //don't touch
    #define CBASH_CHUNK_DEBUG
#endif

#ifndef PEEK_SIZE
    #define PEEK_SIZE 32
#endif

//These require CBASH_PROFILING to be defined
#ifdef CBASH_PROFILING
    //define or undef as desired
    #define CBASH_CALLTIMING
    #define CBASH_CALLCOUNT
    #undef CBASH_TRACE
#else
    //don't touch
    #undef CBASH_CALLTIMING
    #undef CBASH_CALLCOUNT
    #undef CBASH_TRACE
#endif

#ifdef CBASH_TRACE
    #define TRACE_FUNC printf("%s\n", __FUNCTION__)
#else
    #define TRACE_FUNC
#endif

#ifdef CBASH_PROFILING
    #define PROFILE_FUNC TRACE_FUNC;COUNT_FUNC;TIME_FUNC;
#else
    #define PROFILE_FUNC
#endif

#ifdef CBASH_CALLTIMING
    #include <windows.h>
    #include <map>

    extern std::map<char *, double> CallTime;

    typedef struct
        {
        LARGE_INTEGER start;
        LARGE_INTEGER stop;
        } stopWatch;

    class CStopWatch
        {
        private:
            stopWatch timer;
            LARGE_INTEGER frequency;
            char *FunctionName;

        public:
            CStopWatch(char *FName):FunctionName(FName)
                {
                timer.start.QuadPart=0;
                timer.stop.QuadPart=0;
                QueryPerformanceFrequency(&frequency);
                QueryPerformanceCounter(&timer.start);
                }

            ~CStopWatch()
                {
                QueryPerformanceCounter(&timer.stop);
                LARGE_INTEGER time;
                time.QuadPart = timer.stop.QuadPart - timer.start.QuadPart;
                CallTime[FunctionName] = CallTime[FunctionName] + ((double)time.QuadPart / (double)frequency.QuadPart);
                }
        };
    #define TIME_FUNC CStopWatch cbtimer(__FUNCTION__)
#else
    #define TIME_FUNC
#endif

#ifdef CBASH_CALLCOUNT
    #include <map>
    extern std::map<char *, unsigned long> CallCount;

    class CCounter
        {
        public:
            CCounter(char *FName)
                {
                CallCount[FName] = ++CallCount[FName];
                }
        };

    #define COUNT_FUNC CCounter cbcounter(__FUNCTION__)
#else
    #define COUNT_FUNC
#endif

#ifdef CBASH_USE_LOGGING
    #ifndef CLOGGER
        #define CLOGGER    boost::log::sources::severity_logger< severity_level > lg
    #endif
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

#ifndef NULL
    #ifdef __cplusplus
        #define NULL    0
    #else
        #define NULL    ((void *)0)
    #endif
#endif

#ifndef FLT_MAX
    #define FLT_MAX         3.402823466e+38F        /* max value */
#endif
#ifndef FLT_MIN
    #define FLT_MIN         1.175494351e-38F        /* min positive value */
#endif

#ifndef PRINT_RECORD_IDENTIFIERS
    #define PRINT_RECORD_IDENTIFIERS printf("CollectionID: %08X, ModID: %08X, RecordID: %08X\n", CollectionID, ModID, RecordID)
#endif

#ifndef PRINT_FIELD_IDENTIFIERS
    #define PRINT_FIELD_IDENTIFIERS printf("FieldID: %i, ListIndex: %i, ListFieldID: %i, ListX2Index: %i, ListX2FieldID: %i, ListX3Index: %i, ListX3FieldID: %i \n", FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID)
#endif

#ifndef PRINT_EXCEPTION
    #define PRINT_EXCEPTION(ex) printf("%s: Error - General error. %s\n", __FUNCTION__, ex.what())
#endif

#ifndef PRINT_ERROR
#define PRINT_ERROR printf("%s: Error - General error. An unhandled exception occurred.\n", __FUNCTION__)
#endif

#ifndef NUMTHREADS
    #define NUMTHREADS    boost::thread::hardware_concurrency()
#endif

//Using 64KB buffers
#ifndef BUFFERSIZE
    #define BUFFERSIZE    65536
#endif

#ifndef END_HARDCODED_IDS
    #define END_HARDCODED_IDS    0x00000800
#endif

#ifndef VATSFUNCTIONSIZE
    #define VATSFUNCTIONSIZE 18
#endif

#ifndef EXPORT_FUNC
    #define EXPORT_FUNC extern "C" __declspec(dllexport)
#endif

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

#ifndef SINT16ARRAY
    #define SINT16ARRAY signed short *
#endif

#ifndef SINT32
    #define SINT32 signed long
#endif

#ifndef UINT32ARRAY
    #define UINT32ARRAY unsigned long *
#endif

#ifndef SINT32ARRAY
    #define SINT32ARRAY signed long *
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

#ifndef MODIDARRAY
    #define MODIDARRAY ModFile **
#endif

#ifndef RECORDIDARRAY
    #define RECORDIDARRAY Record **
#endif

#ifndef FORMID
    #define FORMID unsigned long
#endif

#ifndef MGEFCODE
    #define MGEFCODE unsigned long
#endif

#ifndef FORMID_OR_UINT32
    #define FORMID_OR_UINT32 unsigned long
#endif

#ifndef FORMID_OR_FLOAT32
    #define FORMID_OR_FLOAT32 unsigned long
#endif

#ifndef MGEFCODE_OR_UINT32
    #define MGEFCODE_OR_UINT32 unsigned long
#endif

#ifndef FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32
    #define FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 unsigned long
#endif

#ifndef ACTORVALUE
    #define ACTORVALUE unsigned long
#endif

#ifndef FORMID_OR_ACTORVALUE_OR_UINT32
    #define FORMID_OR_ACTORVALUE_OR_UINT32 unsigned long
#endif

#ifndef FORMIDARRAY
    #define FORMIDARRAY unsigned long *
#endif

#ifndef MGEFCODEARRAY
    #define MGEFCODEARRAY unsigned long *
#endif

#ifndef DEFAULTED_FIELD_IDENTIFIERS
    #define DEFAULTED_FIELD_IDENTIFIERS const UINT32 FieldID=0, const UINT32 ListIndex=0, const UINT32 ListFieldID=0, const UINT32 ListX2Index=0, const UINT32 ListX2FieldID=0, const UINT32 ListX3Index=0, const UINT32 ListX3FieldID=0
#endif

#ifndef FIELD_IDENTIFIERS
    #define FIELD_IDENTIFIERS const UINT32 FieldID, const UINT32 ListIndex, const UINT32 ListFieldID, const UINT32 ListX2Index, const UINT32 ListX2FieldID, const UINT32 ListX3Index, const UINT32 ListX3FieldID
#endif

#define WHERESTR  "%d: [file %s, line %d]: "
#define WHEREARG  __COUNTER__, __FILE__, __LINE__
#define DEBUGPRINT2(...)       fprintf(stderr, __VA_ARGS__)
#define DPRINT(_fmt, ...)  DEBUGPRINT2(WHERESTR _fmt "\n", WHEREARG, __VA_ARGS__)

#define REV32(x)((#@x & 0x000000FFU) << 24 | (#@x & 0x0000FF00U) << 8 | (#@x & 0x00FF0000U) >> 8 | (#@x & 0xFF000000U) >> 24)
#define WRITE(x) x.Write(REV32(x), writer)
#define WRITEREQ(x) x.ReqWrite(REV32(x), writer)
#define WRITEAS(x,y) x.Write(REV32(y), writer)
#define WRITEEMPTY(x) writer.record_write_subheader(REV32(x), 0);