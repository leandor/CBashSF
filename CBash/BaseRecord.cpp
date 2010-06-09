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

int Record::Read(_FormIDHandler &FormIDHandler)
    {
    if(IsLoaded() || recData == NULL)
        return -1;
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
    ExpandFormIDs(FormIDHandler);
    return 0;
    }

void Record::ExpandFormIDs(_FormIDHandler &FormIDHandler)
    {
    std::vector<FormID> FormIDs;
    GetReferencedFormIDs(FormIDs);
    for(unsigned int x = 0; x < FormIDs.size(); ++x)
        FormIDHandler.ExpandFormID(FormIDs[x]);
    return;
    }

void Record::CollapseFormIDs(_FormIDHandler &FormIDHandler)
    {
    std::vector<FormID> FormIDs;
    GetReferencedFormIDs(FormIDs);
    for(unsigned int x = 0; x < FormIDs.size(); ++x)
        FormIDHandler.CollapseFormID(FormIDs[x]);
    return;
    }


void Record::AddMasters(_FormIDHandler &FormIDHandler)
    {
    FormIDHandler.AddMaster(formID);
    std::vector<FormID> FormIDs;
    GetReferencedFormIDs(FormIDs);
    for(unsigned int x = 0; x < FormIDs.size(); ++x)
        FormIDHandler.AddMaster(FormIDs[x]);
    return;
    }

unsigned int Record::UpdateReferences(unsigned int origFormID, unsigned int newFormID, _FormIDHandler &FormIDHandler)
    {
    unsigned int count = 0;
    std::vector<FormID> FormIDs;
    Read(FormIDHandler);
    GetReferencedFormIDs(FormIDs);
    for(unsigned int x = 0; x < FormIDs.size(); ++x)
        if(*FormIDs[x] == origFormID)
            {
            *FormIDs[x] = newFormID;
            FormIDHandler.AddMaster(newFormID);
            ++count;
            }
    if(count)
        recData = NULL;
    //if(recData != NULL)
    //    Unload();
    return count;
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
    Read(FormIDHandler);
    recSize = GetSize(true);
    FormIDHandler.CollapseFormID(formID);
    CollapseFormIDs(FormIDHandler);

    IsLoaded(false);
    unsigned int recType = GetType();
    SaveHandler.write(&recType, 4);
    SaveHandler.write(&recSize, 4);
    SaveHandler.write(&flags, 4);
    SaveHandler.write(&formID, 4);
    SaveHandler.write(&flagsUnk, 4);
    IsLoaded(true);

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

    FormIDHandler.ExpandFormID(formID);
    if(recData == NULL)
        ExpandFormIDs(FormIDHandler);
    else
        Unload();
    return recSize + 20;
    }

//int Record::Write(WritableRecord &writeRecord, _FormIDHandler &FormIDHandler, bool CloseMod)
//    {
//    //if masters have changed, all formIDs have to be updated...
//    //so the record can't just be written as is.
//    if(!FormIDHandler.MastersChanged() && recData != NULL)
//        {
//        writeRecord.recSize = GetSize();
//        writeRecord.deleteBuffer = false;
//        writeRecord.recBuffer = recData - 20;
//        Unload();
//        return 0;
//        }
//    Read(FormIDHandler);
//    writeRecord.recSize = GetSize(true);
//    FormIDHandler.CollapseFormID(formID);
//    CollapseFormIDs(FormIDHandler);
//    writeRecord.deleteBuffer = true;
//    //Make the new buffer.
//    writeRecord.recBuffer = new unsigned char[writeRecord.recSize + 20];
//    //Write the record to the new buffer
//    WriteRecord(writeRecord.recBuffer + 20);
//    //IsCompressed(true); //Test code
//    if(IsCompressed())
//        {
//        unsigned long compSize = compressBound(writeRecord.recSize);
//        unsigned char *compBuffer = new unsigned char[compSize + 24];
//        memcpy(compBuffer + 20, &writeRecord.recSize, 4);
//        compress2(compBuffer + 24, &compSize, writeRecord.recBuffer +20, writeRecord.recSize, 6);
//        delete []writeRecord.recBuffer;
//        writeRecord.recBuffer = compBuffer;
//        writeRecord.recSize = compSize + 4;
//        }
//
//    IsLoaded(false);
//    unsigned int recType = GetType();
//    memcpy(writeRecord.recBuffer, &recType, 4);
//    memcpy(writeRecord.recBuffer + 4, &writeRecord.recSize, 4);
//    memcpy(writeRecord.recBuffer + 8, &flags, 4);
//    memcpy(writeRecord.recBuffer + 12, &formID, 4);
//    memcpy(writeRecord.recBuffer + 16, &flagsUnk, 4);
//    IsLoaded(true);
//    if(!CloseMod)
//        {
//        FormIDHandler.ExpandFormID(formID);
//        if(recData == NULL)
//            ExpandFormIDs(FormIDHandler);
//        else
//            Unload();
//        }
//    else
//        delete this;
//    return 0;
//    }
