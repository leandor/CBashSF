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

ModFile::ModFile(STRING ModName, const UINT32 _flags):
    Flags(_flags), 
    FileName(ModName), 
    TES4(),
    FormIDHandler(ModName, TES4.MAST, TES4.HEDR.value.nextObject),
    ModID(0)
    {
    TES4.IsLoaded(false);
    struct stat buf;
    if(stat(FileName, &buf) < 0)
        ModTime = 0;
    else
        ModTime = buf.st_mtime;
    if(Flags.IsIgnoreExisting || Flags.IsNoLoad || !FileExists(ModName))
        {
        TES4.IsESM(_stricmp(".esm",ModName + strlen(ModName) - 4) == 0 || _stricmp(".esm.ghost",ModName + strlen(ModName) - 10) == 0);
        TES4.IsLoaded(true);
        }
    }

ModFile::~ModFile()
    {
    delete []FileName;
    }

bool ModFile::operator <(ModFile &other)
    {
    return ModID < other.ModID;
    }

bool ModFile::operator >(ModFile &other)
    {
    return !(*this < other);
    }

bool ModFile::Open()
    {
    if(Flags.IsIgnoreExisting || Flags.IsNoLoad || ReadHandler.IsOpen() || !FileExists(FileName))
        return false;
    ReadHandler.open_ReadOnly(FileName);
    FormIDHandler.FileStart = ReadHandler.getBuffer(0);
    FormIDHandler.FileEnd = FormIDHandler.FileStart + ReadHandler.getBufferSize();
    return true;
    }

bool ModFile::Close()
    {
    if(!ReadHandler.IsOpen())
        return false;
    ReadHandler.close();
    return true;
    }