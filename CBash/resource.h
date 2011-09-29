// Microsoft Visual C++ generated include file.
// Used by CBash.rc

#include "Version.h"

#ifndef FILE_VERSION
    #define FILE_VERSION        MAJOR_VERSION,MINOR_VERSION,REVISION_VERSION,0
#endif

#ifndef PROD_VERSION
    #define PROD_VERSION        FILE_VERSION
#endif

#define STR1(x) #x
#define STR2(x) STR1(x)

#ifndef FILE_VERSION_STR
    #define FILE_VERSION_STR    STR2(MAJOR_VERSION) "." STR2(MINOR_VERSION) "." STR2(REVISION_VERSION) ".0"
#endif

#ifndef PROD_VERSION_STR
    #define PROD_VERSION_STR    FILE_VERSION_STR
#endif

// Next default values for new objects
// 

#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        101
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
