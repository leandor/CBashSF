#include <stdio.h>

#undef COMPILING_CBASH
#include "..\CBash\CBash.h"

#pragma message("automatic link to CBash.lib")
#ifdef _DEBUG
    #pragma comment(lib, "..\\debug\\CBash.lib")
#else
    #pragma comment(lib, "..\\release\\CBash.lib")
#endif

int main()
    {
    Collection *col = CreateCollection(".", 0);
    AddMod(col, "Oblivion.esm", 0x00000078);
    LoadCollection(col);
    DeleteCollection(col);
    
    col = CreateCollection(".", 0);
    AddMod(col, "Oblivion.esm", 0x00000078);
    LoadCollection(col);
    DeleteCollection(col);
    return 0;
    }