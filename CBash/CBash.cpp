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
// CBash.cpp
//#define CBASH_PYTHON
//#ifdef CBASH_PYTHON
//   #include "Python.h"
//    //#define BOOST_PYTHON_STATIC_LIB
//    //#include <boost/python.hpp>
//#endif

#include "CBash.h"
#include <vector>
#include <stdarg.h>
//#include "mmgr.h"

static std::vector<Collection *> Collections;
#ifdef CBASH_CALLTIMING
    extern std::map<char *, double> CallTime;
#endif
#ifdef CBASH_CALLCOUNT
    extern std::map<char *, unsigned long> CallCount;
#endif
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Internal Functions
inline void ValidatePointer(const void *testPointer)
    {
    if(testPointer == NULL)
        throw Ex_NULL();
    }

ModFile *ValidateModName(Collection *curCollection, STRING const ModName)
    {
    //ValidatePointer(ModName);
    STRING NonGhostName = DeGhostModName(ModName);
    STRING const &CompName = NonGhostName ? NonGhostName : ModName;
    //ModFiles will never contain null pointers
    for(UINT32 x = 0; x < curCollection->ModFiles.size();++x)
        if(icmps(CompName, curCollection->ModFiles[x]->reader.getModName()) == 0)
            {
            delete []NonGhostName;
            return curCollection->ModFiles[x];
            }
    delete []NonGhostName;
    throw Ex_INVALIDMODINDEX();
    return NULL;
    }

ModFile *ValidateLoadOrderIndex(Collection *curCollection, const UINT32 ModIndex)
    {
    //ModFiles will never contain null pointers
    if(ModIndex >= curCollection->LoadOrder255.size())
        throw Ex_INVALIDMODINDEX();
    return curCollection->LoadOrder255[ModIndex];
    }

ModFile *ValidateLoadOrderIndex(Collection *curCollection, STRING const ModName)
    {
    //ValidatePointer(ModName);
    STRING NonGhostName = DeGhostModName(ModName);
    STRING const &CompName = NonGhostName ? NonGhostName : ModName;
    //ModFiles will never contain null pointers
    for(UINT32 x = 0; x < curCollection->LoadOrder255.size();++x)
        if(icmps(CompName, curCollection->LoadOrder255[x]->reader.getModName()) == 0)
            {
            delete []NonGhostName;
            return curCollection->LoadOrder255[x];
            }
    delete []NonGhostName;
    throw Ex_INVALIDMODINDEX();
    return NULL;
    }

//Exported Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Exported Python
//#ifdef CBASH_PYTHON

//PyMODINIT_FUNC
//init_CBashTest(void)

//class CBashUINT32
//    {
//    private:
//        UINT32 _FieldID;
//    public:
//        CBashUINT32(UINT32 FieldID):_FieldID(FieldID) {}
//        UINT32 get()
//            {
//            return 0;
//            }
//        UINT32 set()
//            {
//            return 0;
//            }
//    };

//BOOST_PYTHON_MODULE(CBashTest)
//    {
//    using namespace boost::python;
//
//    class_<CBashUINT32>("CBashUINT32", init<UINT32>())
//        .def("__get__", &CBashUINT32::get)
//        .def("__set__", &CBashUINT32::set);
//    }

//#endif
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Exported DLL
//Version info functions
UINT32 GetVersionMajor()
    {
    return MAJOR_VERSION;
    }

UINT32 GetVersionMinor()
    {
    return MINOR_VERSION;
    }

UINT32 GetVersionRevision()
    {
    return REVISION_VERSION;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Logging action functions
int logback_printer(const char * _Format, ...)
    {
    int nSize = 0;
    char buff[1024];
    va_list args;
    va_start(args, _Format);
    nSize = vsnprintf_s(buff, sizeof(buff), _TRUNCATE, _Format, args);
    va_end(args);
    LoggingCallback(buff);
    return nSize;
    }

void RedirectMessages(SINT32 (*_LoggingCallback)(const STRING))
    {
    if(_LoggingCallback)
        {
        LoggingCallback = _LoggingCallback;
        printer = &logback_printer;
        }
    else
        {
        LoggingCallback = NULL;
        printer = &printf;
        }
    }

void AllowRaising(void (*_RaiseCallback)())
    {
    RaiseCallback = _RaiseCallback;
    }

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Collection action functions
Collection * CreateCollection(STRING const ModsPath, const UINT32 CollectionType)
    {
    PROFILE_FUNC

    try
        {
        ValidatePointer(ModsPath);
        for(UINT32 p = 0; p < Collections.size(); ++p)
            {
            if(Collections[p] == NULL)
                {
                Collections[p] = new Collection(ModsPath, CollectionType);
                return Collections[p];
                }
            }
        Collections.push_back(new Collection(ModsPath, CollectionType));
        return Collections.back();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

SINT32 DeleteCollection(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        for(UINT32 p = 0; p < Collections.size(); ++p)
            {
            if(Collections[p] == CollectionID)
                {
                delete Collections[p];
                Collections[p] = NULL;
                }
            }
        for(UINT32 p = 0; p < Collections.size(); ++p)
            {
            if(Collections[p] != NULL)
                return 0;
            }
        Collections.clear();

        #ifdef CBASH_CALLCOUNT
            printer("counts = [");
            for(std::map<char *, unsigned long>::iterator it = CallCount.begin(); it != CallCount.end(); ++it)
                printer("(%d, '%s'),", it->second, it->first);
            printer("]\n");
            #ifndef CBASH_CALLTIMING
                CallCount.clear();
            #endif
        #endif
        #ifdef CBASH_CALLTIMING
            double TotTime = 0.0f;
            printer("times = [");
            for(std::map<char *, double>::iterator it = CallTime.begin(); it != CallTime.end(); ++it)
                {
                TotTime += it->second;
                printer("(%.10f, '%s'),", it->second, it->first);
                }
            printer("]\n\n");
            #ifdef CBASH_CALLCOUNT
                printer("Time in CBash = %.10f\n\n", TotTime);
                printer("Time in CBash = sum(total time)\n");
                printer("Total %% = Time in CBash / total time * 100%%\n");
                printer("avg execution = total time / times called\n\n");
                printer("Total %%,avg execution,total time,function,times called\n");
                std::multimap<double, char *> CBashProfiling;
                for(std::map<char *, double>::iterator it = CallTime.begin(); it != CallTime.end(); ++it)
                    CBashProfiling.insert(std::make_pair((it->second / TotTime) * 100, it->first));
                for(std::multimap<double, char *>::iterator it = CBashProfiling.end(); it != CBashProfiling.begin();)
                    {
                    --it;
                    if(it->first < 10.0)
                        printer("0");
                    printer("%02.2f%%,%.10f,%.10f,%s,%d\n", it->first, CallTime[it->second] / CallCount[it->second], CallTime[it->second], it->second, CallCount[it->second]);
                    }
                printer("\n\n");
                CBashProfiling.clear();
                CallCount.clear();
            #endif
            CallTime.clear();
        #endif
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 LoadCollection(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        CollectionID->Load();
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 UnloadCollection(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        CollectionID->Unload();
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 DeleteAllCollections()
    {
    PROFILE_FUNC

    try
        {
        for(UINT32 p = 0; p < Collections.size(); ++p)
            delete Collections[p];
        Collections.clear();
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Mod action functions
SINT32 AddMod(Collection *CollectionID, STRING const ModName, const UINT32 ModFlagsField)
    {
    PROFILE_FUNC

    ModFlags flags(ModFlagsField);

    try
        {
        //ValidatePointer(CollectionID);
        ValidatePointer(ModName);
        return CollectionID->AddMod(ModName, flags);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 LoadMod(Collection *CollectionID, ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        RecordReader reader(ModID->FormIDHandler, CollectionID->Expanders);
        ModID->VisitAllRecords(reader);
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 UnloadMod(Collection *CollectionID, ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        RecordUnloader unloader;
        ModID->VisitAllRecords(unloader);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return 0;
    }

SINT32 CleanModMasters(Collection *CollectionID, ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        return ModID->CleanMasters(CollectionID->Expanders);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 SaveMod(Collection *CollectionID, ModFile *ModID, const bool CloseCollection)
    {
    SINT32 err = 0;
    try
        {
        //Profiling is in try block so that the timer gets destructed before DeleteCollection is called
        PROFILE_FUNC
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        err = CollectionID->SaveMod(ModID, CloseCollection);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }

    if(CloseCollection)
        err = DeleteCollection(CollectionID) != 0 ? -1 : err;
    if(err == -1)
        {
        printer("\n\n");
        if(RaiseCallback != NULL)
            RaiseCallback();
        }
    return err;
    }
////////////////////////////////////////////////////////////////////////
//Mod info functions
SINT32 GetAllNumMods(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return CollectionID->ModFiles.size();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetAllModIDs(Collection *CollectionID, MODIDARRAY ModIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        UINT32 numMods = CollectionID->ModFiles.size();
        for(UINT32 x = 0; x < numMods; ++x)
            ModIDs[x] = CollectionID->ModFiles[x];
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetLoadOrderNumMods(Collection *CollectionID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return CollectionID->LoadOrder255.size();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetLoadOrderModIDs(Collection *CollectionID, MODIDARRAY ModIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        UINT32 numMods = CollectionID->LoadOrder255.size();
        for(UINT32 x = 0; x < numMods; ++x)
            ModIDs[x] = CollectionID->LoadOrder255[x];
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

STRING GetFileNameByID(Collection *CollectionID, ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->reader.getFileName();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

STRING GetFileNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateLoadOrderIndex(CollectionID, ModIndex)->reader.getFileName();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

STRING GetModNameByID(Collection *CollectionID, ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->reader.getModName();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

STRING GetModNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateLoadOrderIndex(CollectionID, ModIndex)->reader.getModName();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

ModFile * GetModIDByName(Collection *CollectionID, STRING const ModName)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateModName(CollectionID, ModName);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

ModFile * GetModIDByLoadOrder(Collection *CollectionID, const UINT32 ModIndex)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateLoadOrderIndex(CollectionID, ModIndex);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        printer("\n\n");
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

SINT32 GetModLoadOrderByName(Collection *CollectionID, STRING const ModName)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return ValidateLoadOrderIndex(CollectionID, ModName)->FormIDHandler.ExpandedIndex;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetModLoadOrderByID(Collection *CollectionID, ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        if(ModID->Flags.IsInLoadOrder)
            return ModID->FormIDHandler.ExpandedIndex;
        if(RaiseCallback != NULL)
            RaiseCallback();
        return -1;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

STRING GetLongIDName(Collection *CollectionID, ModFile *ModID, const UINT8 ModIndex)
    {
    PROFILE_FUNC

    if(ModIndex == 0xFF)
        return NULL;
    try
        {
        //ValidatePointer(ModID);
        UINT8 CollapsedIndex = ModID->FormIDHandler.CollapseTable[ModIndex];
        if(CollapsedIndex >= ModID->TES4.MAST.size())
            return ModID->reader.getModName();
        return ModID->TES4.MAST[CollapsedIndex].value;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

//SINT32 GetShortIDIndex(Collection *CollectionID, const SINT32 ModID, STRING const ModName)
//    {
//    if(ModID == -1)
//        return GetModLoadOrderByName(CollectionID, ModName);
//    try
//        {
//        ModFile *curModFile = ValidateModID(ValidateCollectionID(CollectionID), ModID);
//        for(UINT16 x = 0; x < curModFile->TES4.MAST.size(); ++x)
//            if(icmps(curModFile->TES4.MAST[x].value, ModName) == 0)
//                return curModFile->FormIDHandler.ExpandTable[(UINT8)x] << 24;
//        printer("GetShortIDIndex: Error\n  %s not found in %s's master list!\n", ModName, curModFile->reader.getModName());
//        return -1;
//        }
//    catch(std::exception &ex)
//        {
//        PRINT_EXCEPTION(ex);
//        }
//    catch(...)
//        {
//        PRINT_ERROR;
//        }
//    printer("\n\n");
//    if(RaiseCallback != NULL)
//        RaiseCallback();
//    return -1;
//    }

UINT32 IsModEmpty(Collection *CollectionID, ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->FormIDHandler.IsEmpty;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return 0;
    }

SINT32 GetModNumTypes(Collection *CollectionID, ModFile *ModID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        if(!ModID->Flags.IsTrackNewTypes)
            {
            printer("GetModNumTypes: Warning - Unable to report record types for mod \"%s\". Tracking is disabled via flag.\n", ModID->reader.getModName());
            if(RaiseCallback != NULL)
                RaiseCallback();
            return -1;
            }

        return ModID->FormIDHandler.NewTypes.size();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetModTypes(Collection *CollectionID, ModFile *ModID, UINT32ARRAY RecordTypes)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        if(!ModID->Flags.IsTrackNewTypes)
            {
            printer("GetModTypes: Warning - Unable to report record types for mod \"%s\". Tracking is disabled via flag.\n", ModID->reader.getModName());
            if(RaiseCallback != NULL)
                RaiseCallback();
            return -1;
            }

        UINT32 x = 0;
        for(boost::unordered_set<UINT32>::iterator it = ModID->FormIDHandler.NewTypes.begin(); it != ModID->FormIDHandler.NewTypes.end(); ++it, ++x)
            RecordTypes[x] = *it;
        return 0;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Record action functions
Record * CreateRecord(Collection *CollectionID, ModFile *ModID, const UINT32 RecordType, const FORMID RecordFormID, STRING const RecordEditorID, Record *ParentID, const UINT32 CreateFlags)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);

        return CollectionID->CreateRecord(ModID, RecordType, RecordFormID, RecordEditorID, (ParentID != NULL ? ParentID->formID: NULL), CreateFlags);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return 0;
    }

SINT32 DeleteRecord(Collection *CollectionID, ModFile *ModID, Record *RecordID, Record *ParentID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        return CollectionID->DeleteRecord(ModID, RecordID, ParentID);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return 0;
    }

Record * CopyRecord(Collection *CollectionID, ModFile *ModID, Record *RecordID, ModFile *DestModID, Record *DestParentID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, const UINT32 CreateFlags)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);
        //ValidatePointer(DestModID);
        return CollectionID->CopyRecord(ModID, RecordID, DestModID, (DestParentID != NULL) ? DestParentID->formID : NULL, DestRecordFormID, DestRecordEditorID, CreateFlags);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

SINT32 UnloadRecord(Collection *CollectionID, ModFile *ModID, Record *RecordID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(RecordID);
        return RecordID->IsChanged() ? 0 : RecordID->Unload();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return 0;
    }

SINT32 SetRecordIdentifiers(Collection *CollectionID, ModFile *ModID, Record *RecordID, const FORMID FormID, STRING const EditorID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);
        return CollectionID->SetRecordIDs(ModID, RecordID, FormID, EditorID);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }
////////////////////////////////////////////////////////////////////////
//Record info functions
Record * GetRecordID(Collection *CollectionID, ModFile *ModID, const FORMID RecordFormID, STRING const RecordEditorID)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        Record * curRecord = NULL;
        if(RecordFormID == 0 && RecordEditorID == 0)
            return &ModID->TES4;
        if(RecordFormID != 0)
            CollectionID->LookupRecord(ModID, RecordFormID, curRecord);
        if(curRecord != NULL)
            return curRecord;
        if(RecordEditorID != 0)
            CollectionID->LookupRecord(ModID, RecordEditorID, curRecord);
        return curRecord;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }

SINT32 GetNumRecords(Collection *CollectionID, ModFile *ModID, const UINT32 RecordType)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        return ModID->GetNumRecords(RecordType);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetRecordIDs(Collection *CollectionID, ModFile *ModID, const UINT32 RecordType, RECORDIDARRAY RecordIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(ModID);
        RecordIDRetriever retriever(RecordIDs);
        ModID->VisitRecords(RecordType, NULL, retriever, false);
        return retriever.GetCount();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 IsRecordWinning(Collection *CollectionID, ModFile *ModID, Record *RecordID, const bool GetExtendedConflicts)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        return CollectionID->IsRecordWinning(ModID, RecordID, GetExtendedConflicts);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetNumRecordConflicts(Collection *CollectionID, Record *RecordID, const bool GetExtendedConflicts)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return CollectionID->GetNumRecordConflicts(RecordID, GetExtendedConflicts);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetRecordConflicts(Collection *CollectionID, Record *RecordID, MODIDARRAY ModIDs, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        return CollectionID->GetRecordConflicts(RecordID, ModIDs, RecordIDs, GetExtendedConflicts);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }

SINT32 GetRecordHistory(Collection *CollectionID, ModFile *ModID, Record *RecordID, MODIDARRAY ModIDs, RECORDIDARRAY RecordIDs)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        return CollectionID->GetRecordHistory(ModID, RecordID, ModIDs, RecordIDs);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }
////////////////////////////////////////////////////////////////////////
//Mod or Record action functions
SINT32 UpdateReferences(Collection *CollectionID, ModFile *ModID, Record *RecordID, const FORMID FormIDToReplace, const FORMID ReplacementFormID)
    {
    PROFILE_FUNC

    //Sanity check.
    if(FormIDToReplace == ReplacementFormID)
        return -1;
    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        RecordFormIDSwapper swapper(FormIDToReplace, ReplacementFormID, ModID->FormIDHandler, CollectionID->Expanders);

        if(RecordID != NULL) //Swap possible uses of FormIDToReplace in a specific record only
            {
            swapper.Accept(RecordID);
            }
        else //Swap all possible uses of FormIDToReplace
            {
            ModID->VisitAllRecords(swapper);
            //Can't get the record type when it's a NULL pointer....stupid me
            //RecordType_PossibleGroups_Iterator curTypes = RecordType_PossibleGroups.find(RecordID->GetType());
            //if(curTypes != RecordType_PossibleGroups.end())
            //    {
            //    for(std::vector<UINT32>::const_iterator x = curTypes->second.begin(); x != curTypes->second.end(); ++x)
            //        {
            //        ModID->VisitRecords(*x, NULL, swapper, true);
            //        }
            //    }
            }
        return swapper.GetCount();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }
////////////////////////////////////////////////////////////////////////
//Mod or Record info functions
SINT32 GetNumReferences(Collection *CollectionID, ModFile *ModID, Record *RecordID, const FORMID FormIDToMatch)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        //Ensure the record is fully loaded
        RecordReader reader(ModID->FormIDHandler, CollectionID->Expanders);
        reader.Accept(RecordID);

        FormIDMatchCounter counter(FormIDToMatch);
        RecordID->VisitFormIDs(counter);
        return counter.GetCount();
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return -1;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Field action functions
void SetField(Collection *CollectionID, ModFile *ModID, Record *RecordID, FIELD_IDENTIFIERS, void *FieldValue, const UINT32 ArraySize)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        //Ensure the record is fully loaded
        RecordReader reader(ModID->FormIDHandler, CollectionID->Expanders);
        reader.Accept(RecordID);

        if(RecordID->SetField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, FieldValue, ArraySize))
            {
            //returns true if formIDs need to be checked
            //Update the master list if needed
            FormIDMasterUpdater checker(ModID->FormIDHandler);
            //checker.Accept(curRecord->formID); //FormID can only be changed through SetRecordIDs, so no need to check
            RecordID->VisitFormIDs(checker);
            }

        RecordID->IsChanged(true);
        return;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    //PRINT_RECORD_IDENTIFIERS;
    PRINT_FIELD_IDENTIFIERS;
    printer("ArraySize: %i\n\n", ArraySize);
    if(RaiseCallback != NULL)
        RaiseCallback();
    return;
    }

void DeleteField(Collection *CollectionID, ModFile *ModID, Record *RecordID, FIELD_IDENTIFIERS)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        //Ensure the record is fully loaded
        RecordReader reader(ModID->FormIDHandler, CollectionID->Expanders);
        reader.Accept(RecordID);

        RecordID->DeleteField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID);

        RecordID->IsChanged(true);
        return;
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    //PRINT_RECORD_IDENTIFIERS;
    PRINT_FIELD_IDENTIFIERS;
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return;
    }
////////////////////////////////////////////////////////////////////////
//Field info functions
UINT32 GetFieldAttribute(Collection *CollectionID, ModFile *ModID, Record *RecordID, FIELD_IDENTIFIERS, const UINT32 WhichAttribute)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        if(WhichAttribute > 0)
            {
            //Any attribute other than type requires the record to be read
            //Ensure the record is fully loaded
            RecordReader reader(ModID->FormIDHandler, CollectionID->Expanders);
            reader.Accept(RecordID);
            }

        return RecordID->GetFieldAttribute(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, WhichAttribute);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    //PRINT_RECORD_IDENTIFIERS;
    PRINT_FIELD_IDENTIFIERS;
    printer("WhichAttribute: %i\n\n", WhichAttribute);
    if(RaiseCallback != NULL)
        RaiseCallback();
    return UNKNOWN_FIELD;
    }

void * GetField(Collection *CollectionID, ModFile *ModID, Record *RecordID, FIELD_IDENTIFIERS, void **FieldValues)
    {
    PROFILE_FUNC

    try
        {
        //ValidatePointer(CollectionID);
        //ValidatePointer(ModID);
        //ValidatePointer(RecordID);

        //Ensure the record is fully loaded
        RecordReader reader(ModID->FormIDHandler, CollectionID->Expanders);
        reader.Accept(RecordID);

        return RecordID->GetField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, FieldValues);
        }
    catch(std::exception &ex)
        {
        PRINT_EXCEPTION(ex);
        }
    catch(...)
        {
        PRINT_ERROR;
        }
    //PRINT_RECORD_IDENTIFIERS;
    PRINT_FIELD_IDENTIFIERS;
    printer("\n\n");
    if(RaiseCallback != NULL)
        RaiseCallback();
    return NULL;
    }
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////