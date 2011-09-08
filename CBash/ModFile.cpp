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

 CBash copyright (C) 2010-2011 Waruddar
=============================================================================
*/
// ModFile.cpp
#include "Common.h"
#include "ModFile.h"
#include "GenericRecord.h"

ModFile::ModFile(Collection *_Parent, STRING filename, STRING modname, const UINT32 _flags):
    Parent(_Parent),
    Flags(_flags),
    TES4(),
    FormIDHandler(TES4.MAST, TES4.HEDR.value.nextObject),
    ModID(0),
    FileName(filename),
    ModName(modname),
    file_map(),
    buffer_position(NULL),
    buffer_start(NULL),
    buffer_end(NULL)
    {
    TES4.IsLoaded(false);
    TES4.SetParent(this, true);
    ModTime = mtime();
    if(Flags.IsIgnoreExisting || Flags.IsNoLoad || !exists())
        {
        Flags.IsIgnoreExisting = true;
        TES4.IsLoaded(true);
        STRING const _Name = ModName;
        TES4.IsESM(icmps(".esm",_Name + strlen(_Name) - 4) == 0);
        }
    }

ModFile::~ModFile()
    {
    if(FileName != ModName)
        delete []FileName;
    delete []ModName;
    Close();
    }

bool ModFile::operator <(ModFile &other)
    {
    return ModID < other.ModID;
    }

bool ModFile::operator >(ModFile &other)
    {
    return ModID > other.ModID;
    }

time_t ModFile::mtime()
    {
    struct stat buf;
    if(stat(FileName, &buf) < 0)
        return 0;
    else
        return buf.st_mtime;
    }

bool ModFile::exists()
    {
    struct stat statBuffer;
    return (stat(FileName, &statBuffer) >= 0 && statBuffer.st_mode & S_IFREG);
    }

bool ModFile::Open()
    {
    PROFILE_FUNC

    if(Flags.IsIgnoreExisting || Flags.IsNoLoad || file_map.is_open() || !exists())
        {
        if(!Flags.IsIgnoreExisting)
            {
            if(Flags.IsNoLoad)
                printer("ModFile::Open: Error - Unable to open mod \"%s\". Loading is explicitly disabled via flags.\n", ModName);
            else if(file_map.is_open())
                printer("ModFile::Open: Error - Unable to open mod \"%s\". It is already open.\n", ModName);
            else if(!exists())
                printer("ModFile::Open: Error - Unable to open mod \"%s\". Unable to locate file.\n", ModName);
            }
        return false;
        }

    if(FileName == NULL || file_map.is_open())
        return false;
    try
        {
        file_map.open(FileName);
        }
    catch(std::ios::failure const & e)
        {
        printer("ModFile: Error - Unable to open \"%s\" as read only via memory mapping.\n", FileName);
        throw e;
        }
    catch(...)
        {
        printer("ModFile: Error - Unable to open \"%s\" as read only via memory mapping. An unhandled exception occurred.\n", FileName);
        throw;
        }
    buffer_position = buffer_start = (unsigned char *)file_map.data();
    buffer_end = buffer_start + file_map.size();

    FormIDHandler.FileStart = buffer_start;
    FormIDHandler.FileEnd = buffer_end;
    return true;
    }

bool ModFile::Close()
    {
    PROFILE_FUNC

    if(!file_map.is_open())
        return false;

    file_map.close();
    return true;
    }

FormIDMasterUpdater::FormIDMasterUpdater(FormIDHandlerClass &_FormIDHandler):
    FormIDOp(),
    FormIDHandler(_FormIDHandler),
    ExpandedIndex(_FormIDHandler.ExpandedIndex),
    CollapsedIndex(_FormIDHandler.CollapsedIndex),
    ExpandTable(_FormIDHandler.ExpandTable),
    CollapseTable(_FormIDHandler.CollapseTable)
    {
    //
    }

FormIDMasterUpdater::FormIDMasterUpdater(ModFile *ModID):
    FormIDOp(),
    FormIDHandler(ModID->FormIDHandler),
    ExpandedIndex(ModID->FormIDHandler.ExpandedIndex),
    CollapsedIndex(ModID->FormIDHandler.CollapsedIndex),
    ExpandTable(ModID->FormIDHandler.ExpandTable),
    CollapseTable(ModID->FormIDHandler.CollapseTable)
    {
    //
    }

FormIDMasterUpdater::FormIDMasterUpdater(Record *RecordID):
    FormIDOp(),
    FormIDHandler(RecordID->GetParentMod()->FormIDHandler),
    ExpandedIndex(RecordID->GetParentMod()->FormIDHandler.ExpandedIndex),
    CollapsedIndex(RecordID->GetParentMod()->FormIDHandler.CollapsedIndex),
    ExpandTable(RecordID->GetParentMod()->FormIDHandler.ExpandTable),
    CollapseTable(RecordID->GetParentMod()->FormIDHandler.CollapseTable)
    {
    //
    }

FormIDMasterUpdater::~FormIDMasterUpdater()
    {
    //
    }

bool FormIDMasterUpdater::Accept(UINT32 &curFormID)
    {
    //If formID is not set, or the formID belongs to the engine, do nothing
    //Any formID whose objectID is less than END_HARDCODED_IDS is given the 00 modIndex by the engine regardless of what it actually is
    //I.e. the CS will complain of duplicate formIDs if a mod has both 0x00000042 and 0x01000042
    //In short, formIDs with an objectID < END_HARDCODED_IDS all collide. They don't use the modIndex.
    if((curFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        {
        curFormID &= 0x00FFFFFF;
        return stop;
        }

    UINT32 modIndex = curFormID >> 24;
    //printer("Checking %08X against %02X, %02X, %02X\n", curFormID, ExpandedIndex, CollapseTable[modIndex], CollapsedIndex);
    //If the formID belongs to the mod, or if the master is already present, do nothing
    if((modIndex == ExpandedIndex) || (CollapseTable[modIndex] != CollapsedIndex))
        return stop;

    //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
    if(modIndex >= FormIDHandler.LoadOrder255.size())
        {
        curFormID = (ExpandTable[CollapseTable[modIndex]] << 24) | (curFormID & 0x00FFFFFF);
        return stop;
        }
    FormIDHandler.AddMaster(FormIDHandler.LoadOrder255[modIndex]);
    ++count;
    return stop;
    }

bool FormIDMasterUpdater::AcceptMGEF(UINT32 &curMgefCode)
    {
    //If MgefCode is not set, do nothing
    if(curMgefCode == 0)
        return stop;

    UINT32 modIndex = curMgefCode & 0x000000FF;
    //If the MgefCode belongs to the mod, or if the master is already present, do nothing
    if((modIndex == ExpandedIndex) || (CollapseTable[modIndex] != CollapsedIndex))
        return stop;

    //If the modIndex doesn't match to a loaded mod, it gets assigned to the mod that it is in.
    if(modIndex >= FormIDHandler.LoadOrder255.size())
        {
        curMgefCode = (ExpandTable[CollapseTable[modIndex]]) | (curMgefCode & 0xFFFFFF00);
        return stop;
        }

    FormIDHandler.AddMaster(FormIDHandler.LoadOrder255[modIndex]);
    ++count;
    return stop;
    }