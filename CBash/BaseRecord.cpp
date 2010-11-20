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

#include "Common.h"
#include "BaseRecord.h"
#include "zlib/zlib.h"

bool Record::Read()
    {
    if(IsLoaded() || recData == NULL)
        return false;
    unsigned int recSize = GetSize();
    if (IsCompressed())
        {
        unsigned char localBuffer[BUFFERSIZE];
        unsigned char *buffer = NULL;
        unsigned int expandedRecSize = *(unsigned int*)recData;
        if(expandedRecSize >= BUFFERSIZE)
            buffer = new unsigned char[expandedRecSize];
        else
            buffer = &localBuffer[0];
        uncompress(buffer, (uLongf*)&expandedRecSize, &recData[4], recSize - 4);
        ParseRecord(buffer, expandedRecSize);
        if(buffer != &localBuffer[0])
            delete [] buffer;
        }
    else
        ParseRecord(recData, recSize);
    return true;
    }

unsigned int Record::Write(_FileHandler &SaveHandler, _FormIDHandler &FormIDHandler)
    {
    //if masters have changed, all formIDs have to be updated...
    //so the record can't just be written as is.
    unsigned int recSize = 0;
    if(!FormIDHandler.MastersChanged() && recData != NULL)
        {
        recSize = GetSize();
        SaveHandler.write(recData - 20, recSize + 20);
        Unload();
        return recSize + 20;
        }
    RecordReader reader(FormIDHandler);
    reader.Accept(*this);
    if(IsDeleted())
        recSize = 0;
    else
        recSize = GetSize(true);
    FormIDResolver collapser(FormIDHandler.CollapseTable);
    collapser.Accept(formID);
    VisitFormIDs(collapser);

    IsLoaded(false);
    unsigned int recType = GetType();
    SaveHandler.write(&recType, 4);
    SaveHandler.write(&recSize, 4);
    SaveHandler.write(&flags, 4);
    SaveHandler.write(&formID, 4);
    SaveHandler.write(&flagsUnk, 4);
    IsLoaded(true);

    if(!IsDeleted())
        {
        //IsCompressed(true); //Test code
        if(IsCompressed())
            {
            //printf("Compressed: %08X\n", formID);
            unsigned long recStart = SaveHandler.tell();
            unsigned long compSize = compressBound(recSize);
            unsigned char *compBuffer = new unsigned char[compSize + 4];
            SaveHandler.reserveBuffer(compSize + 4);
            WriteRecord(SaveHandler);
            memcpy(compBuffer, &recSize, 4);
            if(SaveHandler.IsCached(recStart) && ((SaveHandler.UnusedCache() + recSize) >= compSize))
                compress2(compBuffer + 4, &compSize, SaveHandler.getBuffer(recStart), recSize, 6);
            else
                {
                SaveHandler.flush();
                printf("Not in cache, written improperly!\n  Size: %u\n", recSize);
                return recSize + 20;
                }
            SaveHandler.set_used((compSize + 4) - recSize);
            recSize = compSize + 4;
            SaveHandler.writeAt(recStart - 16, &recSize, 4);
            SaveHandler.writeAt(recStart, compBuffer, recSize);
            delete []compBuffer;
            }
        else
            WriteRecord(SaveHandler);
        }
    FormIDResolver expander(FormIDHandler.ExpandTable);
    expander.Accept(formID);
    if(recData == NULL)
        VisitFormIDs(expander);
    else
        Unload();
    return recSize + 20;
    }
