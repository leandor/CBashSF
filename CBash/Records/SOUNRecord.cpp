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
#include "SOUNRecord.h"

signed long SOUNRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned long subType = 0;
    unsigned long subSize = 0;
    unsigned long curPos = 0;
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
            case eFNAM:
                FNAM.Read(buffer, subSize, curPos);
                break;
            case eSNDD:
            case eSNDX:
                SNDX.Read(buffer, subSize, curPos);
                //SNDX->minDistance *= 5;
                //SNDX->maxDistance *= 100;
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  SOUN: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long SOUNRecord::GetSize(bool forceCalc)
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
    if(FNAM.IsLoaded())
        {
        cSize = FNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SNDX.IsLoaded())
        TotSize += SNDX.GetSize() + 6;
    return TotSize;
    }

signed long SOUNRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord(eFNAM, FNAM.value, FNAM.GetSize());
    if(SNDX.IsLoaded())
        if(SNDX.GetSize() == 8)
            SaveHandler.writeSubRecord(eSNDD, &SNDX.value, SNDX.GetSize());
        else
            SaveHandler.writeSubRecord(eSNDX, &SNDX.value, SNDX.GetSize());
    return -1;
    }

#ifdef _DEBUG
void SOUNRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
    printf("  SOUN\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FNAM.Debug("FNAM", debugLevel, indentation);

    SNDX.Debug("SNDX", debugLevel, indentation);
    }
#endif
