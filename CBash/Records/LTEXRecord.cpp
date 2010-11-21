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

signed long LTEXRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned long subType = 0;
    unsigned long subSize = 0;
    unsigned long curPos = 0;
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
                curFormID = new unsigned long;
                _readBuffer(curFormID,buffer,subSize,curPos);
                GNAM.push_back(curFormID);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LTEX: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long LTEXRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && recData != NULL)
        return *(unsigned long*)&recData[-16];
    unsigned long cSize = 0;
    unsigned long TotSize = 0;
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
        TotSize += HNAM.GetSize() + 6;
    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;
    if(GNAM.size())
        TotSize += (unsigned long)GNAM.size() * (sizeof(unsigned long) + 6);
    return TotSize;
    }

signed long LTEXRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, ICON.value, ICON.GetSize());
    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord(eHNAM, &HNAM.value, HNAM.GetSize());
    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord(eSNAM, &SNAM.value, SNAM.GetSize());
    for(unsigned long p = 0; p < GNAM.size(); p++)
        SaveHandler.writeSubRecord(eGNAM, GNAM[p], sizeof(unsigned long));
    return -1;
    }

#ifdef _DEBUG
void LTEXRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
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
        for(unsigned long p = 0;p < GNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(GNAM[p]));
            }
        indentation -= 2;
        }
    }
#endif
