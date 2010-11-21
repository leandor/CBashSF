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
#include "DIALRecord.h"
#include <vector>

signed long DIALRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
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
            case eQSTI:
                curFormID = new unsigned long;
                _readBuffer(curFormID,buffer,subSize,curPos);
                QSTI.push_back(curFormID);
                break;
            case eQSTR:
                curFormID = new unsigned long;
                _readBuffer(curFormID,buffer,subSize,curPos);
                QSTR.push_back(curFormID);
                break;
            case eFULL:
                FULL.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  DIAL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long DIALRecord::GetSize(bool forceCalc)
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
    if(QSTI.size())
        TotSize += (unsigned long)QSTI.size() * (sizeof(unsigned long) + 6);
    if(QSTR.size())
        TotSize += (unsigned long)QSTR.size() * (sizeof(unsigned long) + 6);
    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    return TotSize;
    }

signed long DIALRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(QSTI.size())
        for(unsigned long p = 0; p < QSTI.size(); p++)
            SaveHandler.writeSubRecord(eQSTI, QSTI[p], sizeof(unsigned long));
    if(QSTR.size())
        for(unsigned long p = 0; p < QSTR.size(); p++)
            SaveHandler.writeSubRecord(eQSTR, QSTR[p], sizeof(unsigned long));
    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
    return -1;
    }

#ifdef _DEBUG
void DIALRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
    printf("  DIAL\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    if(QSTI.size())
        {
        PrintIndent(indentation);
        printf("QSTI:\n");
        indentation += 2;
        for(unsigned long p = 0;p < QSTI.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(QSTI[p]));
            }
        indentation -= 2;
        }

    if(QSTR.size())
        {
        PrintIndent(indentation);
        printf("QSTR:\n");
        indentation += 2;
        for(unsigned long p = 0;p < QSTR.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(QSTR[p]));
            }
        indentation -= 2;
        }

    FULL.Debug("FULL", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

    INFO.Debug(debugLevel);
    }
#endif
