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
#include "..\Common.h"
#include "GMSTRecord.h"

int GMSTRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    while(curPos < recSize){
        _readBuffer(&subType,buffer,4,curPos);
        switch(subType)
            {
            case eXXXX:
                curPos += 2;
                _readBuffer(&subSize,buffer,4,curPos);
                _readBuffer(&subType,buffer,4,curPos);
                curPos += 2;
                break;
            default:
                subSize = 0;
                _readBuffer(&subSize,buffer,2,curPos);
                break;
            }
        switch(subType)
            {
            case eEDID:
                EDID.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.format = EDID.value[0];
                switch(DATA.format)
                    {
                    case 's':
                        DATA.s = new char [subSize];
                        memcpy(DATA.s,buffer+curPos,subSize);
                        curPos += subSize;
                        break;
                    case 'i':
                        memcpy(&DATA.i,buffer+curPos,subSize);
                        curPos += subSize;
                        break;
                    case 'f':
                        memcpy(&DATA.f,buffer+curPos,subSize);
                        curPos += subSize;
                        break;
                    default:
                        //printf("FileName = %s\n", FileName);
                        printf("  GMST: Unknown type = %c\n", DATA.format);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  GMST: Unknown subType = %04X\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int GMSTRecord::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    switch(DATA.format)
        {
        case 'i':
        case 'f':
            TotSize += 10;
            break;
        case 's':
            if(DATA.s != NULL)
                {
                cSize = (unsigned int)strlen(DATA.s) + 1;
                if(cSize > 65535) cSize += 10;
                }
            else
                cSize = 1;
            TotSize += cSize += 6;
            break;
        default:
            printf("Unknown GMST format in GetSize(): %s\n", EDID.value);
            break;
        }
    return TotSize;
    }

int GMSTRecord::WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    switch(DATA.format)
        {
        case 'i':
            _writeSubRecord(buffer, eDATA, 4, &DATA.i, usedBuffer);
            break;
        case 'f':
            _writeSubRecord(buffer, eDATA, 4, &DATA.f, usedBuffer);
            break;
        case 's':
            if(DATA.s != NULL)
                _writeSubRecord(buffer, eDATA, (unsigned int)strlen(DATA.s) + 1, DATA.s, usedBuffer);
            else
                _writeSubRecord(buffer, eDATA, 0, DATA.s, usedBuffer);
            break;
        default:
            printf("Unknown GMST format when writing: %s\n", EDID.value);
        }
    return -1;
    }

#ifdef _DEBUG
void GMSTRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  GMST\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);
    }
#endif
