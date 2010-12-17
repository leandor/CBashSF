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
#include "CBash.h"
#include "Collection.h"
#include <vector>
//#include "mmgr.h"

#ifdef CBASH_USE_LOGGING
    //#include <boost/log/utility/init/common_attributes.hpp>
    //#include <boost/log/attributes/current_process_id.hpp>

    namespace logging = boost::log;
    namespace flt = boost::log::filters;
    namespace fmt = boost::log::formatters;
    namespace sinks = boost::log::sinks;
    namespace attrs = boost::log::attributes;
    namespace src = boost::log::sources;
    namespace keywords = boost::log::keywords;

    // The backend performs a callback to the specified function
    // Primarily used to send messages back to python as they occur

    class callback_backend : public sinks::basic_formatting_sink_backend< char, char > // Character type
        {
        public:
            typedef SINT32 (*CallbackFunc)(const STRING);

        private:
            // The callback for every logged file
            CallbackFunc const LoggingCallback;

        public:
            // The function consumes the log records that come from the frontend
            void do_consume(record_type const& rec, target_string_type const& formatted_message);

            // The constructor initializes the internal data
            explicit callback_backend(CallbackFunc _LoggingCallback):LoggingCallback(_LoggingCallback)
                {
                //
                }
        };

    // The method puts the formatted message to the callback
    void callback_backend::do_consume(record_type const& rec, target_string_type const& formatted_message)
        {
        //printf("%s\n", formatted_message.c_str());
        LoggingCallback(formatted_message.c_str());
        }
#endif

static std::vector<Collection *> Collections;

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Internal Functions
void ValidatePointer(const void *testPointer)
    {
    if(testPointer == NULL)
        throw Ex_NULL();
    }

Collection * ValidateCollectionID(const UINT32 CollectionID)
    {
    //Collections can contain null pointers
    if(CollectionID >= Collections.size() || Collections[CollectionID] == NULL)
        throw Ex_INVALIDCOLLECTIONINDEX();
    return Collections[CollectionID];
    }

ModFile * ValidateModID(Collection *curCollection, const UINT32 ModID)
    {
    //ModFiles will never contain null pointers
    if(ModID >= curCollection->ModFiles.size())
        throw Ex_INVALIDMODINDEX();
    return curCollection->ModFiles[ModID];
    }

ModFile * ValidateModID(Collection *curCollection, STRING const ModName)
    {
    ValidatePointer(ModName);
    //ModFiles will never contain null pointers
    for(UINT32 x = 0; x < curCollection->ModFiles.size();++x)
        if(_stricmp(ModName, curCollection->ModFiles[x]->ReadHandler.getFileName()) == 0)
            return curCollection->ModFiles[x];
    throw Ex_INVALIDMODINDEX();
    return NULL;
    }

ModFile * ValidateLoadOrderIndex(Collection *curCollection, const UINT32 ModIndex)
    {
    //ModFiles will never contain null pointers
    if(ModIndex >= curCollection->LoadOrder255.size())
        throw Ex_INVALIDMODINDEX();
    return curCollection->LoadOrder255[ModIndex];
    }

ModFile * ValidateLoadOrderIndex(Collection *curCollection, STRING const ModName)
    {
    ValidatePointer(ModName);
    //ModFiles will never contain null pointers
    for(UINT32 x = 0; x < curCollection->LoadOrder255.size();++x)
        if(_stricmp(ModName, curCollection->LoadOrder255[x]->ReadHandler.getFileName()) == 0)
            return curCollection->LoadOrder255[x];
    throw Ex_INVALIDMODINDEX();
    return NULL;
    }

void LookupRecord(const UINT32 &CollectionID, const UINT32 &ModID, const FORMID &RecordFormID, STRING const RecordEditorID, Record *&curRecord)
    {
    Collection *curCollection = ValidateCollectionID(CollectionID);
    ModFile *curModFile = ValidateModID(curCollection, ModID);
    if(RecordFormID != 0)
        curCollection->LookupRecord(curModFile, RecordFormID, curRecord);
    else if(RecordEditorID != NULL)
        curCollection->LookupRecord(curModFile, RecordEditorID, curRecord);
    else //If neither is set, lookup the root record
        curRecord = (Record *)&curModFile->TES4;
    if(curRecord == NULL)
        throw Ex_INVALIDRECORDINDEX();
    }

void LookupRecord(const UINT32 &CollectionID, const UINT32 &ModID, const FORMID &RecordFormID, STRING const RecordEditorID, ModFile *&curModFile, Record *&curRecord)
    {
    Collection *curCollection = ValidateCollectionID(CollectionID);
    curModFile = ValidateModID(curCollection, ModID);
    if(RecordFormID != 0)
        curCollection->LookupRecord(curModFile, RecordFormID, curRecord);
    else if(RecordEditorID != NULL)
        curCollection->LookupRecord(curModFile, RecordEditorID, curRecord);
    else //If neither is set, lookup the root record
        curRecord = (Record *)&curModFile->TES4;

    if(curRecord == NULL)
        throw Ex_INVALIDRECORDINDEX();
    }

void LookupRecord(const UINT32 &CollectionID, const UINT32 &ModID, const FORMID &RecordFormID, Record *&curRecord)
    {
    Collection *curCollection = ValidateCollectionID(CollectionID);
    ModFile *curModFile = ValidateModID(curCollection, ModID);
    if(RecordFormID != 0)
        curCollection->LookupRecord(curModFile, RecordFormID, curRecord);
    else //If neither is set, lookup the root record
        curRecord = (Record *)&curModFile->TES4;

    if(curRecord == NULL)
        throw Ex_INVALIDRECORDINDEX();
    }

void LookupRecord(const UINT32 &CollectionID, const UINT32 &ModID, const FORMID &RecordFormID, ModFile *&curModFile, Record *&curRecord)
    {
    Collection *curCollection = ValidateCollectionID(CollectionID);
    curModFile = ValidateModID(curCollection, ModID);
    if(RecordFormID != 0)
        curCollection->LookupRecord(curModFile, RecordFormID, curRecord);
    else //If neither is set, lookup the root record
        curRecord = (Record *)&curModFile->TES4;
    if(curRecord == NULL)
        throw Ex_INVALIDRECORDINDEX();
    }

void LookupRecord(const UINT32 &CollectionID, const UINT32 &ModID, STRING const RecordEditorID, Record *&curRecord)
    {
    Collection *curCollection = ValidateCollectionID(CollectionID);
    ModFile *curModFile = ValidateModID(curCollection, ModID);
    if(RecordEditorID != NULL)
        curCollection->LookupRecord(curModFile, RecordEditorID, curRecord);
    else //If neither is set, lookup the root record
        curRecord = (Record *)&curModFile->TES4;
    if(curRecord == NULL)
        throw Ex_INVALIDRECORDINDEX();
    }

void LookupRecord(const UINT32 &CollectionID, const UINT32 &ModID, STRING const RecordEditorID, ModFile *&curModFile, Record *&curRecord)
    {
    Collection *curCollection = ValidateCollectionID(CollectionID);
    curModFile = ValidateModID(curCollection, ModID);
    if(RecordEditorID != NULL)
        curCollection->LookupRecord(curModFile, RecordEditorID, curRecord);
    else //If neither is set, lookup the root record
        curRecord = (Record *)&curModFile->TES4;
    if(curRecord == NULL)
        throw Ex_INVALIDRECORDINDEX();
    }


//Exported Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
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
#ifdef CBASH_USE_LOGGING
    // This function registers my_backend sink in the logging library
    // Complete sink type
    typedef sinks::synchronous_sink< callback_backend > sink_t;

    void init_logging(SINT32 (*_LoggingCallback)(const STRING))
    {
        boost::shared_ptr< logging::core > core = logging::core::get();

        attrs::named_scope Scope;
        core->add_thread_attribute("Scope", Scope);

        // Also let's add some commonly used attributes, like timestamp and record counter.
        //logging::add_common_attributes();

        attrs::counter< unsigned int > RecordID(1);

        // Since we intend to count all logging records ever made by the application,
        // this attribute should clearly be global.
        core->add_global_attribute("RecordID", RecordID);

        // One can construct backend separately and pass it to the frontend
        boost::shared_ptr< callback_backend > backend(new callback_backend(_LoggingCallback));
        boost::shared_ptr< sink_t > sink1(new sink_t(backend));
        core->add_sink(sink1);

        boost::shared_ptr< sink_t > sink2(new sink_t(backend));
        core->add_sink(sink2);

        sink2->set_filter
            (
                flt::attr< severity_level >("Severity", std::nothrow) >= warning
            );

        sink2->locked_backend()->set_formatter
            (
                fmt::stream
                //<< "PID = " << fmt::attr< boost::log::aux::process::id >("ProcessID") // First an attribute "RecordID" is written to the log
                << fmt::attr("RecordID") << ": " // First an attribute "RecordID" is written to the log
                //<< fmt::if_(flt::has_attr("ThreadID"))
                //    [
                //        fmt::stream << "<" << fmt::attr< attrs::current_thread_id::value_type >("ThreadID") // First an attribute "RecordID" is written to the log
                //    ]
                 << fmt::attr< severity_level >("Severity", std::nothrow) << " - "
                << fmt::date_time< boost::posix_time::ptime >("TimeStamp", "%m.%d.%Y %H:%M:%S.%f") << "]"
                << "] [" // then this delimiter separates it from the rest of the line
                << fmt::if_(flt::has_attr("Tag"))
                   [
                       fmt::stream << fmt::attr< std::string >("Tag") << "] [" // yet another delimiter
                   ]
                << fmt::named_scope("Scope", keywords::iteration = fmt::forward) << "] "
                << fmt::message() // here goes the log record text
            );
    }

    SINT32 SetLogging(const UINT32 CollectionID, SINT32 (*_LoggingCallback)(const STRING), UINT32 LoggingLevel, UINT32 LoggingFlags)
        {
        try
            {
            ValidatePointer(_LoggingCallback);
            if(LoggingFlags == 0)
                {
                init_logging(_LoggingCallback);
                }
            else
                {
                BOOST_LOG_NAMED_SCOPE("SetLogging scope");
                src::logger lg;
                BOOST_LOG(lg) << "Hello World";

                // Now, let's try logging with severity
                src::severity_logger< severity_level > slg;

                BOOST_LOG_SEV(slg, normal) << "A normal severity message, will not pass to the file";
                BOOST_LOG_SEV(slg, warning) << "A warning severity message, will pass to the file";
                BOOST_LOG_SEV(slg, error) << "An error severity message, will pass to the file";

                // Ok, remember the "Tag" attribute we added in the formatter? It is absent in these
                // two lines above, so it is empty in the output. Let's try to tag some log records with it.
                {
                    BOOST_LOG_NAMED_SCOPE("Tagging scope");

                    // Here we add a temporary attribute to the logger lg.
                    // Every log record being written in the current scope with logger lg
                    // will have a string attribute "Tag" with value "Tagged line" attached.
                    BOOST_LOG_SCOPED_LOGGER_TAG(lg, "Tag", std::string, "Tagged line");

                    // The above line is roughly equivalent to the following:
                    // attrs::constant< std::string > TagAttr("Tagged line");
                    // logging::scoped_attribute _ =
                    //     logging::add_scoped_logger_attribute(lg, "Tag", TagAttr);

                    // Now these lines will be highlighted with the tag
                    BOOST_LOG(lg) << "Some tagged log line";
                    BOOST_LOG(lg) << "Another tagged log line";
                }

                // And this line is not highlighted anymore
                BOOST_LOG(lg) << "Now the tag is removed";
                }
            //LOG("Level = %03i, Flags = %08X\n", LoggingLevel, LoggingFlags)
            }
        catch(std::exception &ex)
            {
            printf("Error LoggingTest\n  %s\n", ex.what());
            return -1;
            }
        catch(...)
            {
            printf("Error LoggingTest\n  Unhandled Exception\n");
            return -1;
            }
        return 0;
        }
#endif
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Collection action functions
SINT32 CreateCollection(STRING const ModsPath, const UINT32 CollectionType)
    {
    try
        {
        ValidatePointer(ModsPath);
        for(UINT32 p = 0; p < Collections.size(); ++p)
            {
            if(Collections[p] == NULL)
                {
                Collections[p] = new Collection(ModsPath, CollectionType);
                return p;
                }
            }
        Collections.push_back(new Collection(ModsPath, CollectionType));
        }
    catch(std::exception &ex)
        {
        printf("Error creating collection\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error creating collection\n  Unhandled Exception\n");
        return -1;
        }
    return (int)Collections.size() - 1;
    }

#pragma warning( push )
#pragma warning( disable : 4101 ) //Disable warning about deliberately unused variable (Ex_INVALIDCOLLECTIONINDEX &ex)
SINT32 DeleteCollection(const UINT32 CollectionID)
    {
    try
        {
        ValidateCollectionID(CollectionID);
        delete Collections[CollectionID];
        Collections[CollectionID] = NULL;
        for(UINT32 p = 0; p < Collections.size(); ++p)
            {
            if(Collections[p] != NULL)
                return 0;
            }
        Collections.clear();
        }
    catch(Ex_INVALIDCOLLECTIONINDEX &ex) {} //Silently fail if deleting an already deleted collection
    catch(std::exception &ex)
        {
        printf("Error erasing collection at pos %i\n  %s\n", CollectionID, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error erasing collection at pos %i\n  Unhandled Exception\n", CollectionID);
        return -1;
        }
    return 0;
    }
#pragma warning( pop )

SINT32 LoadCollection(const UINT32 CollectionID)
    {
    #ifdef CBASH_USE_LOGGING
        CLOGGER;
        BOOST_LOG_FUNCTION();
        BOOST_LOG_SEV(lg, trace) << "CollectionID = " << CollectionID;
    #endif
    try
        {
        ValidateCollectionID(CollectionID)->Load();
        }
    catch(std::exception &ex)
        {
        printf("LoadCollection: Error loading records\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("LoadCollection: Error loading records\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }

SINT32 UnloadCollection(const UINT32 CollectionID)
    {
    try
        {
        ValidateCollectionID(CollectionID)->Unload();
        }
    catch(std::exception &ex)
        {
        printf("Error unloading all records from collection: %i\n  %s\n", CollectionID, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error unloading all records from collection: %i\n  Unhandled Exception\n", CollectionID);
        return -1;
        }
    return 0;
    }

SINT32 DeleteAllCollections()
    {
    try
        {
        for(UINT32 p = 0; p < Collections.size(); ++p)
            delete Collections[p];
        Collections.clear();
        }
    catch(std::exception &ex)
        {
        printf("Error erasing collections\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error erasing collections\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Mod action functions
SINT32 AddMod(const UINT32 CollectionID, STRING const ModName, const UINT32 ModFlagsField)
    {
    #ifdef CBASH_USE_LOGGING
        CLOGGER;
        BOOST_LOG_FUNCTION();
        BOOST_LOG_SEV(lg, trace) << "Adding " << ModName;
    #endif
    ModFlags flags(ModFlagsField);

    try
        {
        ValidatePointer(ModName);
        return ValidateCollectionID(CollectionID)->AddMod(ModName, flags);
        }
    catch(std::exception &ex)
        {
        printf("Error adding mod:%s\n  %s\n", ModName, ex.what());
        }
    catch(...)
        {
        printf("Error adding mod:%s\n  Unhandled Exception\n", ModName);
        }
    return -1;
    }

SINT32 LoadMod(const UINT32 CollectionID, const UINT32 ModID)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        ModFile *curModFile = ValidateModID(curCollection, ModID);
        RecordReader reader(curModFile->FormIDHandler, curCollection->Expanders);
        curModFile->VisitAllRecords(reader);
        }
    catch(std::exception &ex)
        {
        printf("Error unloading records from modID: %i in collection: %i\n  %s\n", ModID, CollectionID, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error unloading records from modID: %i in collection: %i\n  Unhandled Exception\n", ModID, CollectionID);
        return -1;
        }
    return 0;
    }

SINT32 UnloadMod(const UINT32 CollectionID, const UINT32 ModID)
    {
    try
        {
        RecordUnloader unloader;
        ValidateModID(ValidateCollectionID(CollectionID), ModID)->VisitAllRecords(unloader);
        }
    catch(std::exception &ex)
        {
        printf("Error unloading records from modID: %i in collection: %i\n  %s\n", ModID, CollectionID, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error unloading records from modID: %i in collection: %i\n  Unhandled Exception\n", ModID, CollectionID);
        return -1;
        }
    return 0;
    }

SINT32 CleanModMasters(const UINT32 CollectionID, const UINT32 ModID)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        return ValidateModID(curCollection, ModID)->CleanMasters(curCollection->Expanders);
        }
    catch(std::exception &ex)
        {
        printf("CleanModMasters: Error loading records\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CleanModMasters: Error loading records\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

SINT32 SaveMod(const UINT32 CollectionID, const UINT32 ModID, const bool CloseCollection)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        curCollection->SaveMod(ValidateModID(curCollection, ModID), CloseCollection);

        if(CloseCollection)
            DeleteCollection(CollectionID);
        }
    catch(std::exception &ex)
        {
        printf("Error saving mod:%i\n  %s\n", ModID, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error saving mod:%i\n  Unhandled Exception\n", ModID);
        return -1;
        }
    return 0;
    }
////////////////////////////////////////////////////////////////////////
//Mod info functions
SINT32 GetNumMods(const UINT32 CollectionID)
    {
    try
        {
        return ValidateCollectionID(CollectionID)->LoadOrder255.size();
        }
    catch(std::exception &ex)
        {
        printf("GetNumMods: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("GetNumMods: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }

SINT32 GetModIDs(const UINT32 CollectionID, UINT32ARRAY ModIDs)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        UINT32 numMods = curCollection->LoadOrder255.size();
        for(UINT32 x = 0; x < numMods; ++x)
            ModIDs[x] = curCollection->LoadOrder255[x]->ModID;
        return 0;
        }
    catch(std::exception &ex)
        {
        printf("GetModIDs: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("GetModIDs: Error\n  Unhandled Exception\n");
        return -1;
        }
    return 0;
    }

STRING GetModNameByID(const UINT32 CollectionID, const UINT32 ModID)
    {
    try
        {
        return ValidateModID(ValidateCollectionID(CollectionID), ModID)->ReadHandler.getFileName();
        }
    catch(std::exception &ex)
        {
        printf("GetModNameByID: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("GetModNameByID: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }

STRING GetModNameByLoadOrder(const UINT32 CollectionID, const UINT32 ModIndex)
    {
    try
        {
        return ValidateLoadOrderIndex(ValidateCollectionID(CollectionID), ModIndex)->ReadHandler.getFileName();
        }
    catch(std::exception &ex)
        {
        printf("GetModNameByLoadOrder: Error\n  %s\n", ex.what());
        return NULL;
        }
    catch(...)
        {
        printf("GetModNameByLoadOrder: Error\n  Unhandled Exception\n");
        return NULL;
        }
    return NULL;
    }

SINT32 GetModIDByName(const UINT32 CollectionID, STRING const ModName)
    {
    try
        {
        return ValidateModID(ValidateCollectionID(CollectionID), ModName)->ModID;
        }
    catch(std::exception &ex)
        {
        printf("GetModIDByName: Error\n  %s\n", ex.what());
        return 1;
        }
    catch(...)
        {
        printf("GetModIDByName: Error\n  Unhandled Exception\n");
        return 1;
        }
    return 1;
    }

SINT32 GetModIDByLoadOrder(const UINT32 CollectionID, const UINT32 ModIndex)
    {
    try
        {
        return ValidateLoadOrderIndex(ValidateCollectionID(CollectionID), ModIndex)->ModID;
        }
    catch(std::exception &ex)
        {
        printf("GetModIDByLoadOrder: Error\n  %s\n", ex.what());
        return 1;
        }
    catch(...)
        {
        printf("GetModIDByLoadOrder: Error\n  Unhandled Exception\n");
        return 1;
        }
    return 1;
    }

SINT32 GetModLoadOrderByName(const UINT32 CollectionID, STRING const ModName)
    {
    try
        {
        return ValidateLoadOrderIndex(ValidateCollectionID(CollectionID), ModName)->FormIDHandler.ExpandedIndex;
        }
    catch(std::exception &ex)
        {
        printf("GetModLoadOrderByName: Error\n  %s\n", ex.what());
        return 1;
        }
    catch(...)
        {
        printf("GetModLoadOrderByName: Error\n  Unhandled Exception\n");
        return 1;
        }
    return 1;
    }

SINT32 GetModLoadOrderByID(const UINT32 CollectionID, const UINT32 ModID)
    {
    try
        {
        return ValidateModID(ValidateCollectionID(CollectionID), ModID)->FormIDHandler.ExpandedIndex;
        }
    catch(std::exception &ex)
        {
        printf("GetModLoadOrderByID: Error\n  %s\n", ex.what());
        return 1;
        }
    catch(...)
        {
        printf("GetModLoadOrderByID: Error\n  Unhandled Exception\n");
        return 1;
        }
    return 1;
    }

UINT32 IsModEmpty(const UINT32 CollectionID, const UINT32 ModID)
    {
    try
        {
        return ValidateModID(ValidateCollectionID(CollectionID), ModID)->FormIDHandler.IsEmpty;
        }
    catch(std::exception &ex)
        {
        printf("IsModEmpty: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("IsModEmpty: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

SINT32 GetModNumTypes(const UINT32 CollectionID, const UINT32 ModID)
    {
    try
        {
        ModFile *curModFile = ValidateModID(ValidateCollectionID(CollectionID), ModID);
        if(!curModFile->Flags.IsTrackNewTypes)
            return -1;

        return curModFile->FormIDHandler.NewTypes.size();
        }
    catch(std::exception &ex)
        {
        printf("GetNumNewRecordTypes: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("GetNumNewRecordTypes: Error\n  Unhandled Exception\n");
        return -1;
        }
    return -1;
    }

void GetModTypes(const UINT32 CollectionID, const UINT32 ModID, UINT32ARRAY RecordTypes)
    {
    try
        {
        ModFile *curModFile = ValidateModID(ValidateCollectionID(CollectionID), ModID);
        if(!curModFile->Flags.IsTrackNewTypes)
            return;

        UINT32 x = 0;
        for(boost::unordered_set<UINT32>::iterator it = curModFile->FormIDHandler.NewTypes.begin(); it != curModFile->FormIDHandler.NewTypes.end(); ++it, ++x)
            RecordTypes[x] = *it;
        }
    catch(std::exception &ex)
        {
        printf("GetNewRecordTypes: Error\n  %s\n", ex.what());
        }
    catch(...)
        {
        printf("GetNewRecordTypes: Error\n  Unhandled Exception\n");
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Record action functions
UINT32 CreateRecord(const UINT32 CollectionID, const UINT32 ModID, const UINT32 RecordType, const FORMID RecordFormID, STRING const RecordEditorID, const FORMID ParentFormID, const UINT32 CreateFlags)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        return curCollection->CreateRecord(ValidateModID(curCollection, ModID), RecordType, RecordFormID, RecordEditorID, ParentFormID, CreateFlags);
        }
    catch(std::exception &ex)
        {
        printf("CreateRecord: Error\n  %s\n", ex.what());
        return 0;
        }
    catch(...)
        {
        printf("CreateRecord: Error\n  Unhandled Exception\n");
        return 0;
        }
    return 0;
    }

SINT32 DeleteRecord(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, const FORMID ParentFormID)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        return curCollection->DeleteRecord(ValidateModID(curCollection, ModID), RecordFormID, RecordEditorID, ParentFormID);
        }
    catch(std::exception &ex)
        {
        printf("Error deleting record: %08X from mod:%i in collection: %i\n  %s\n", RecordFormID, ModID, CollectionID, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error deleting record: %08X from mod:%i in collection: %i\n  Unhandled Exception\n", RecordFormID, ModID, CollectionID);
        return -1;
        }
    return 0;
    }

UINT32 CopyRecord(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, const UINT32 DestModID, const UINT32 DestParentFormID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, const UINT32 CreateFlags)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        return curCollection->CopyRecord(ValidateModID(curCollection, ModID), RecordFormID, RecordEditorID, ValidateModID(curCollection, DestModID), DestParentFormID, DestRecordFormID, DestRecordEditorID, CreateFlags);
        }
    catch(std::exception &ex)
        {
        printf("CopyRecord: Error\n  %s\n", ex.what());
        PRINT_RECORD_IDENTIFIERS;
        printf("DestModID: %i, DestParentFormID: %08X, DestRecordFormID: %08X, DestRecordEditorID: %s, CreateFlags:%08X\n", DestModID, DestParentFormID, DestRecordFormID, DestRecordEditorID, CreateFlags);
        printf("\n\n");
        return 0;
        }
    catch(...)
        {
        printf("CopyRecord: Error\n  Unhandled Exception\n");
        PRINT_RECORD_IDENTIFIERS;
        printf("DestModID: %i, DestParentFormID: %08X, DestRecordFormID: %08X, DestRecordEditorID: %s, CreateFlags:%08X\n", DestModID, DestParentFormID, DestRecordFormID, DestRecordEditorID, CreateFlags);
        printf("\n\n");
        return 0;
        }
    return 0;
    }

SINT32 UnloadRecord(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID)
    {
    try
        {
        Record *curRecord = NULL;
        LookupRecord(CollectionID, ModID, RecordFormID, RecordEditorID, curRecord);
        return curRecord->IsChanged() ? false : curRecord->Unload();
        }
    catch(std::exception &ex)
        {
        printf("Error unloading record: %08X from mod:%i in collection: %i\n  %s\n", RecordFormID, ModID, CollectionID, ex.what());
        return -1;
        }
    catch(...)
        {
        printf("Error unloading record: %08X from mod:%i in collection: %i\n  Unhandled Exception\n", RecordFormID, ModID, CollectionID);
        return -1;
        }
    return 0;
    }

SINT32 SetRecordIDs(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, const FORMID FormIDValue, STRING const EditorIDValue)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        return curCollection->SetRecordIDs(ValidateModID(curCollection, ModID), RecordFormID, RecordEditorID, FormIDValue, EditorIDValue);
        }
    catch(std::exception &ex)
        {
        printf("SetRecordIDs: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("SetRecordIDs: Error\n  Unhandled Exception\n");
        return -1;
        }
    return -1;
    }
////////////////////////////////////////////////////////////////////////
//Record info functions
SINT32 GetNumRecords(const UINT32 CollectionID, const UINT32 ModID, const UINT32 RecordType)
    {
    try
        {
        return ValidateModID(ValidateCollectionID(CollectionID), ModID)->GetNumRecords(RecordType);
        }
    catch(std::exception &ex)
        {
        printf("GetNumRecords: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("GetNumRecords: Error\n  Unhandled Exception\n");
        return -1;
        }
    return -1;
    }

void GetRecordFormIDs(const UINT32 CollectionID, const UINT32 ModID, const UINT32 RecordType, FORMIDARRAY RecordFormIDs)
    {
    try
        {
        FormIDRecordRetriever retriever(RecordFormIDs);
        ValidateModID(ValidateCollectionID(CollectionID), ModID)->VisitRecords(RecordType, NULL, retriever, false);
        }
    catch(std::exception &ex)
        {
        printf("GetRecordFormIDs: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetRecordFormIDs: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }

void GetRecordEditorIDs(const UINT32 CollectionID, const UINT32 ModID, const UINT32 RecordType, STRINGARRAY RecordEditorIDs)
    {
    try
        {
        EditorIDRecordRetriever retriever(RecordEditorIDs);
        ValidateModID(ValidateCollectionID(CollectionID), ModID)->VisitRecords(RecordType, NULL, retriever, false);
        }
    catch(std::exception &ex)
        {
        printf("GetRecordEditorIDs: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetRecordEditorIDs: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }

SINT32 IsRecordWinning(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, const bool GetExtendedConflicts)
    {
    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        return curCollection->IsRecordWinning(ValidateModID(curCollection, ModID), RecordFormID, RecordEditorID, GetExtendedConflicts);
        }
    catch(std::exception &ex)
        {
        printf("IsRecordWinning: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("IsRecordWinning: Error\n  Unhandled Exception\n");
        return -1;
        }
    return -1;
    }

SINT32 GetNumRecordConflicts(const UINT32 CollectionID, const FORMID RecordFormID, STRING const RecordEditorID, const bool GetExtendedConflicts)
    {
    try
        {
        return ValidateCollectionID(CollectionID)->GetNumRecordConflicts(RecordFormID, RecordEditorID, GetExtendedConflicts);
        }
    catch(std::exception &ex)
        {
        printf("GetNumRecordConflicts: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("GetNumRecordConflicts: Error\n  Unhandled Exception\n");
        return -1;
        }
    return -1;
    }

void GetRecordConflicts(const UINT32 CollectionID, const FORMID RecordFormID, STRING const RecordEditorID, UINT32ARRAY ModIDs, const bool GetExtendedConflicts)
    {
    try
        {
        ValidateCollectionID(CollectionID)->GetRecordConflicts(RecordFormID, RecordEditorID, ModIDs, GetExtendedConflicts);
        return;
        }
    catch(std::exception &ex)
        {
        printf("GetRecordConflicts: Error\n  %s\n", ex.what());
        return;
        }
    catch(...)
        {
        printf("GetRecordConflicts: Error\n  Unhandled Exception\n");
        return;
        }
    return;
    }
////////////////////////////////////////////////////////////////////////
//Mod or Record action functions
SINT32 UpdateReferences(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, const FORMID FormIDToReplace, const FORMID ReplacementFormID)
    {
    //Sanity check.
    if(FormIDToReplace == ReplacementFormID)
        return -1;

    try
        {
        Collection *curCollection = ValidateCollectionID(CollectionID);
        ModFile *curModFile = ValidateModID(curCollection, ModID);
        Record *curRecord = NULL;
        RecordFormIDSwapper swapper(FormIDToReplace, ReplacementFormID, curModFile->FormIDHandler, curCollection->Expanders);

        if(RecordFormID != 0) //Swap possible uses of FormIDToReplace in a specific record only
            {
            LookupRecord(CollectionID, ModID, RecordFormID, curRecord);
            swapper.Accept(&curRecord);
            }
        else //Swap all possible uses of FormIDToReplace
            {
            UINT32 SourceModLoadOrderID = FormIDToReplace >> 24;
            if(SourceModLoadOrderID >= curCollection->LoadOrder255.size())
                throw Ex_INVALIDINDEX();
            UINT32 SourceModID = curCollection->LoadOrder255[SourceModLoadOrderID]->ModID;
            LookupRecord(CollectionID, SourceModID, FormIDToReplace, curRecord); //Lookup the original definition of the record
            RecordType_PossibleGroups_Iterator curTypes = RecordType_PossibleGroups.find(curRecord->GetType());
            if(curTypes != RecordType_PossibleGroups.end())
                {
                for(std::vector<UINT32>::const_iterator x = curTypes->second.begin(); x != curTypes->second.end(); ++x)
                    curModFile->VisitRecords(*x, NULL, swapper, true);
                }
            }
        return swapper.GetCount();
        }
    catch(std::exception &ex)
        {
        printf("UpdateReferences: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("UpdateReferences: Error\n  Unhandled Exception\n");
        return -1;
        }
    return -1;
    }
////////////////////////////////////////////////////////////////////////
//Mod or Record info functions
SINT32 GetNumReferences(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, const FORMID FormIDToMatch)
    {
    try
        {
        ModFile *curModFile = NULL;
        Record *curRecord = NULL;
        Collection *curCollection = ValidateCollectionID(CollectionID);
        LookupRecord(CollectionID, ModID, RecordFormID, curModFile, curRecord);
        
        //Ensure the record is fully loaded
        RecordReader reader(curModFile->FormIDHandler, curCollection->Expanders);
        reader.Accept(&curRecord);

        FormIDMatchCounter counter(FormIDToMatch);
        curRecord->VisitFormIDs(counter);
        return counter.GetCount();
        }
    catch(std::exception &ex)
        {
        printf("GetNumReferences: Error\n  %s\n", ex.what());
        return -1;
        }
    catch(...)
        {
        printf("GetNumReferences: Error\n  Unhandled Exception\n");
        return -1;
        }
    return -1;
    }
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Field action functions
void SetField(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, FIELD_IDENTIFIERS, void *FieldValue, const UINT32 ArraySize)
    {
    try
        {
        ModFile *curModFile = NULL;
        Record *curRecord = NULL;
        Collection *curCollection = ValidateCollectionID(CollectionID);
        LookupRecord(CollectionID, ModID, RecordFormID, RecordEditorID, curModFile, curRecord);
        
        //Ensure the record is fully loaded
        RecordReader reader(curModFile->FormIDHandler, curCollection->Expanders);
        reader.Accept(&curRecord);

        if(curRecord->SetField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, FieldValue, ArraySize))
            {
            //returns true if formIDs need to be checked
            //Update the master list if needed
            FormIDMasterUpdater checker(curModFile->FormIDHandler);
            //checker.Accept(curRecord->formID); //FormID can only be changed through SetRecordIDs, so no need to check
            curRecord->VisitFormIDs(checker);
            }

        curRecord->IsChanged(true);
        return;
        }
    catch(std::exception &ex)
        {
        printf("SetField: Error\n  %s\n", ex.what());
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("ArraySize: %i\n\n", ArraySize);
        }
    catch(...)
        {
        printf("SetField: Error\n  Unhandled Exception\n");
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("ArraySize: %i\n\n", ArraySize);
        }
    }

void DeleteField(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, FIELD_IDENTIFIERS)
    {
    try
        {
        ModFile *curModFile = NULL;
        Record *curRecord = NULL;
        Collection *curCollection = ValidateCollectionID(CollectionID);
        LookupRecord(CollectionID, ModID, RecordFormID, RecordEditorID, curModFile, curRecord);
        
        //Ensure the record is fully loaded
        RecordReader reader(curModFile->FormIDHandler, curCollection->Expanders);
        reader.Accept(&curRecord);

        curRecord->DeleteField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID);

        curRecord->IsChanged(true);
        return;
        }
    catch(std::exception &ex)
        {
        printf("DeleteField: Error\n  %s\n", ex.what());
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("\n\n");
        }
    catch(...)
        {
        printf("DeleteField: Error\n  Unhandled Exception\n");
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("\n\n");
        }
    }
////////////////////////////////////////////////////////////////////////
//Field info functions
UINT32 GetFieldAttribute(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, FIELD_IDENTIFIERS, const UINT32 WhichAttribute)
    {
    try
        {
        ModFile *curModFile = NULL;
        Record *curRecord = NULL;
        Collection *curCollection = ValidateCollectionID(CollectionID);
        LookupRecord(CollectionID, ModID, RecordFormID, RecordEditorID, curModFile, curRecord);
        
        if(WhichAttribute > 0)
            {
            //Any attribute other than type requires the record to be read
            //Ensure the record is fully loaded
            RecordReader reader(curModFile->FormIDHandler, curCollection->Expanders);
            reader.Accept(&curRecord);
            }

        return curRecord->GetFieldAttribute(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, WhichAttribute);
        }
    catch(Ex_INVALIDRECORDINDEX &ex)
        {
        if(FieldID == 0) //Was testing if the record exists by check recType (only field with id of 0)
            return UNKNOWN_FIELD;
        printf("GetFieldAttribute: Error\n  %s\n", ex.what());
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("WhichAttribute: %i\n\n", WhichAttribute);
        return UNKNOWN_FIELD;
        }
    catch(std::exception &ex)
        {
        printf("GetFieldAttribute: Error\n  %s\n", ex.what());
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("WhichAttribute: %i\n\n", WhichAttribute);
        return UNKNOWN_FIELD;
        }
    catch(...)
        {
        printf("GetFieldAttribute: Error\n  Unhandled Exception\n");
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("WhichAttribute: %i\n\n", WhichAttribute);
        return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * GetField(const UINT32 CollectionID, const UINT32 ModID, const FORMID RecordFormID, STRING const RecordEditorID, FIELD_IDENTIFIERS, void **FieldValues)
    {
    try
        {
        ModFile *curModFile = NULL;
        Record *curRecord = NULL;
        Collection *curCollection = ValidateCollectionID(CollectionID);
        LookupRecord(CollectionID, ModID, RecordFormID, RecordEditorID, curModFile, curRecord);
        
        //Ensure the record is fully loaded
        RecordReader reader(curModFile->FormIDHandler, curCollection->Expanders);
        reader.Accept(&curRecord);

        return curRecord->GetField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, FieldValues);
        }
    catch(std::exception &ex)
        {
        printf("GetField: Error\n  %s\n", ex.what());
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("\n\n");
        return NULL;
        }
    catch(...)
        {
        printf("GetField: Error\n  Unhandled Exception\n");
        PRINT_RECORD_IDENTIFIERS;
        PRINT_FIELD_IDENTIFIERS;
        printf("\n\n");
        return NULL;
        }
    return NULL;
    }
//////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////