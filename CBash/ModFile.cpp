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
// ModFile.cpp
#include "Common.h"
#include "ModFile.h"
#include "GenericRecord.h"

ModFile::ModFile(STRING FileName, STRING ModName, const UINT32 _flags):
    Flags(_flags),
    TES4(),
    reader(FileName, ModName),
    FormIDHandler(TES4.MAST, TES4.HEDR.value.nextObject),
    ModID(0)
    {
    TES4.IsLoaded(false);
    ModTime = reader.mtime();
    if(Flags.IsIgnoreExisting || Flags.IsNoLoad || !reader.exists())
        {
        Flags.IsIgnoreExisting = true;
        TES4.IsLoaded(true);
        STRING const _Name = reader.getModName();
        TES4.IsESM(_stricmp(".esm",_Name + strlen(_Name) - 4) == 0);
        }
    }

ModFile::~ModFile()
    {
    //
    }

bool ModFile::operator <(ModFile &other)
    {
    return ModID < other.ModID;
    }

bool ModFile::operator >(ModFile &other)
    {
    return ModID > other.ModID;
    }

bool ModFile::Open()
    {
    PROFILE_FUNC

    if(Flags.IsIgnoreExisting || Flags.IsNoLoad || reader.IsOpen() || !reader.exists())
        {
        if(!Flags.IsIgnoreExisting)
            {
            if(Flags.IsNoLoad)
                printf("ModFile::Open: Error - Unable to open mod \"%s\". Loading is explicitly disabled via flags.\n", reader.getModName());
            else if(reader.IsOpen())
                printf("ModFile::Open: Error - Unable to open mod \"%s\". It is already open.\n", reader.getModName());
            else if(!reader.exists())
                printf("ModFile::Open: Error - Unable to open mod \"%s\". Unable to locate file.\n", reader.getModName());
            }
        return false;
        }
    reader.open();
    FormIDHandler.FileStart = reader.getBuffer();
    FormIDHandler.FileEnd = FormIDHandler.FileStart + reader.getBufferSize();
    return true;
    }

bool ModFile::Close()
    {
    PROFILE_FUNC

    if(!reader.IsOpen())
        {
        if(!Flags.IsIgnoreExisting)
            printf("ModFile::Close: Error - Unable to close mod \"%s\". It is already closed.\n", reader.getModName());
        return false;
        }
    reader.close();
    return true;
    }