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

int Record::Read(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler)
    {
    if(IsLoaded())
        return -1;
    unsigned char localBuffer[BUFFERSIZE];
    unsigned char *buffer = NULL;
    unsigned int recSize = *(unsigned int*)&fileBuffer[recStart - 16];
    unsigned int expandedRecSize = *(unsigned int*)&fileBuffer[recStart];
    if (IsCompressed())
        {
        if(expandedRecSize >= BUFFERSIZE)
            {
            #ifdef _DEBUG
            printf("!!!COMPRESSED RECORD: recStart: %u, formID: %08X, hSize:%u, recSize:%u\n", recStart, formID, Header.Header.size, recSize);
            printf("New Buffer:%u\n", recSize);
            #endif
            buffer = new unsigned char[expandedRecSize];
            }
        else
            {
            buffer = &localBuffer[0];
            }
        uncompress(buffer, (uLongf*)&expandedRecSize, &fileBuffer[recStart + 4], recSize - 4);
        ParseRecord(buffer, expandedRecSize);
        if(buffer != &localBuffer[0])
            delete [] buffer;
        IsCompressed(false);
        }
    else
        ParseRecord(&fileBuffer[recStart], recSize);
    ExpandFormIDs(FormIDHandler);
    return 0;
    }

void Record::WriteHeader(int *fh, unsigned char *buffer, unsigned int curRecType, unsigned int &recSize, unsigned int &usedBuffer)
    {
    IsLoaded(false);
    _writeBuffer(buffer, &curRecType, 4, usedBuffer);
    _writeBuffer(buffer, &recSize, 4, usedBuffer);
    _writeBuffer(buffer, &flags, 4, usedBuffer);
    _writeBuffer(buffer, &formID, 4, usedBuffer);
    _writeBuffer(buffer, &flagsUnk, 4, usedBuffer);
    IsLoaded(true);
    return;
    }

int Record::Write(int *fh, unsigned char *buffer, unsigned int &recSize, unsigned int &usedBuffer)
    {
    unsigned char *fileBuffer = NULL;
    unsigned int buffTemp = recSize + 620;
    if((usedBuffer + buffTemp) > BUFFERSIZE) //600 should give enough space for any XXXX records that might be made
        {
        //Flush the buffer if it is getting full
        _write(*fh, buffer, usedBuffer);
        usedBuffer = 0;
        }
    if(buffTemp < BUFFERSIZE)
        {
        WriteHeader(fh, buffer, GetType(), recSize, usedBuffer);
        WriteRecord(fh, buffer, usedBuffer);
        }
    else
        {
        #ifdef _DEBUG
        printf("!!!LARGE RECORD FOUND!!!: %s, %i\n", PrintFormID(formID), buffTemp);
        #endif
        //If the record is larger than an empty buffer, allocate one and use that instead.
        //First, flush the existing buffer
        _write(*fh, buffer, usedBuffer);
        usedBuffer = 0;
        //Make the new buffer. It is given extra space in case of excess XXXX records
        fileBuffer = new unsigned char[buffTemp + 1800];
        buffTemp = 0;
        //Write the record to the new buffer
        WriteHeader(fh, fileBuffer, GetType(), recSize, buffTemp);
        WriteRecord(fh, fileBuffer, buffTemp);
        //Flush the new buffer, and delete it
        _write(*fh, fileBuffer, buffTemp);
        delete []fileBuffer;
        }
    return 0;
    }
