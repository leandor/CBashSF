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
#include "WATRRecord.h"

int WATRRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
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
            case eTNAM:
                TNAM.Read(buffer, subSize, curPos);
                break;
            case eANAM:
                ANAM.Read(buffer, subSize, curPos);
                break;
            case eFNAM:
                FNAM.Read(buffer, subSize, curPos);
                break;
            case eMNAM:
                MNAM.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                SNAM.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eGNAM:
                GNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  WATR: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int WATRRecord::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(TNAM.IsLoaded())
        {
        cSize = TNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ANAM.IsLoaded())
        {
        cSize = ANAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FNAM.IsLoaded())
        {
        cSize = FNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MNAM.IsLoaded())
        {
        cSize = MNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SNAM.IsLoaded())
        {
        cSize = SNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(GNAM.IsLoaded())
        {
        cSize = GNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    return TotSize;
    }

int WATRRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(TNAM.IsLoaded())
        _writeSubRecord(buffer, eTNAM, TNAM.GetSize(), TNAM.value, usedBuffer);
    if(ANAM.IsLoaded())
        _writeSubRecord(buffer, eANAM, ANAM.GetSize(), &ANAM.value, usedBuffer);
    if(FNAM.IsLoaded())
        _writeSubRecord(buffer, eFNAM, FNAM.GetSize(), &FNAM.value, usedBuffer);
    if(MNAM.IsLoaded())
        _writeSubRecord(buffer, eMNAM, MNAM.GetSize(), MNAM.value, usedBuffer);
    if(SNAM.IsLoaded())
        _writeSubRecord(buffer, eSNAM, SNAM.GetSize(), SNAM.value, usedBuffer);
    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), DATA.value, usedBuffer);
    if(GNAM.IsLoaded())
        _writeSubRecord(buffer, eGNAM, GNAM.GetSize(), GNAM.value, usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void WATRRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  WATR\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    TNAM.Debug("TNAM", debugLevel, indentation);

    ANAM.Debug("ANAM", debugLevel, indentation);

    FNAM.Debug("FNAM", debugLevel, indentation);

    MNAM.Debug("MNAM", debugLevel, indentation);

    SNAM.Debug("SNAM", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

    GNAM.Debug("GNAM", debugLevel, indentation);
    }
#endif
