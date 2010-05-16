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
#include "LTEXRecord.h"
#include <vector>

int LTEXRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    FormID curFormID = NULL;
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
            case eICON:
                ICON.Read(buffer, subSize, curPos);
                break;
            case eHNAM:
                HNAM.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                SNAM.Read(buffer, subSize, curPos);
                break;
            case eGNAM:
                curFormID = new unsigned int;
                _readBuffer(curFormID,buffer,subSize,curPos);
                GNAM.push_back(curFormID);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LTEX: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int LTEXRecord::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(HNAM.IsLoaded())
        {
        cSize = HNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SNAM.IsLoaded())
        {
        cSize = SNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(GNAM.size())
        TotSize += (unsigned int)GNAM.size() * (sizeof(unsigned int) + 6);
    return TotSize;
    }

int LTEXRecord::WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, ICON.GetSize(), ICON.value, usedBuffer);
    if(HNAM.IsLoaded())
        _writeSubRecord(buffer, eHNAM, HNAM.GetSize(), &HNAM.value, usedBuffer);
    if(SNAM.IsLoaded())
        _writeSubRecord(buffer, eSNAM, SNAM.GetSize(), &SNAM.value, usedBuffer);
    for(unsigned int p = 0; p < GNAM.size(); p++)
        _writeSubRecord(buffer, eGNAM, sizeof(unsigned int), GNAM[p], usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void LTEXRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  LTEX\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    ICON.Debug("ICON", debugLevel, indentation);

    HNAM.Debug("HNAM", debugLevel, indentation);

    SNAM.Debug("SNAM", debugLevel, indentation);

    if(GNAM.size())
        {
        PrintIndent(indentation);
        printf("GNAM:\n");
        indentation += 2;
        for(unsigned int p = 0;p < GNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(GNAM[p]));
            }
        indentation -= 2;
        }
    }
#endif
