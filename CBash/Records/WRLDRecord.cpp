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
#include "WRLDRecord.h"
#include <vector>

int WRLDRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
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
            case eFULL:
                FULL.Read(buffer, subSize, curPos);
                break;
            case eWNAM:
                WNAM.Read(buffer, subSize, curPos);
                break;
            case eCNAM:
                CNAM.Read(buffer, subSize, curPos);
                break;
            case eNAM2:
                NAM2.Read(buffer, subSize, curPos);
                break;
            case eICON:
                ICON.Read(buffer, subSize, curPos);
                break;
            case eMNAM:
                MNAM.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eNAM0:
                NAM0.Read(buffer, subSize, curPos);
                break;
            case eNAM9:
                NAM9.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                SNAM.Read(buffer, subSize, curPos);
                break;
            case eOFST:
                OFST.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  WRLD: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int WRLDRecord::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(WNAM.IsLoaded())
        {
        cSize = WNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CNAM.IsLoaded())
        {
        cSize = CNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(NAM2.IsLoaded())
        {
        cSize = NAM2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MNAM.IsLoaded())
        {
        cSize = MNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAM0.IsLoaded())
        {
        cSize = NAM0.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(NAM9.IsLoaded())
        {
        cSize = NAM9.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SNAM.IsLoaded())
        {
        cSize = SNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(OFST.IsLoaded())
        {
        cSize = OFST.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    return TotSize;
    }

int WRLDRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);

    if(FULL.IsLoaded())
        _writeSubRecord(buffer, eFULL, FULL.GetSize(), FULL.value, usedBuffer);

    if(WNAM.IsLoaded())
        _writeSubRecord(buffer, eWNAM, WNAM.GetSize(), WNAM.value, usedBuffer);
    if(CNAM.IsLoaded())
        _writeSubRecord(buffer, eCNAM, CNAM.GetSize(), CNAM.value, usedBuffer);
    if(NAM2.IsLoaded())
        _writeSubRecord(buffer, eNAM2, NAM2.GetSize(), NAM2.value, usedBuffer);

    if(ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, ICON.GetSize(), ICON.value, usedBuffer);

    if(MNAM.IsLoaded())
        _writeSubRecord(buffer, eMNAM, MNAM.GetSize(), MNAM.value, usedBuffer);
    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);

    if(NAM0.IsLoaded())
        _writeSubRecord(buffer, eNAM0, NAM0.GetSize(), &NAM0.value, usedBuffer);
    if(NAM9.IsLoaded())
        _writeSubRecord(buffer, eNAM9, NAM9.GetSize(), &NAM9.value, usedBuffer);

    if(SNAM.IsLoaded())
        _writeSubRecord(buffer, eSNAM, SNAM.GetSize(), SNAM.value, usedBuffer);
    if(OFST.IsLoaded())
        _writeSubRecord(buffer, eOFST, OFST.GetSize(), OFST.value, usedBuffer);

    return -1;
    }

#ifdef _DEBUG
void WRLDRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  WRLD\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    WNAM.Debug("WNAM", debugLevel, indentation);
    CNAM.Debug("CNAM", debugLevel, indentation);
    NAM2.Debug("NAM2", debugLevel, indentation);

    ICON.Debug("ICON", debugLevel, indentation);

    MNAM.Debug("MNAM", debugLevel, indentation);
    DATA.Debug("DATA", debugLevel, indentation);

    NAM0.Debug("NAM0", debugLevel, indentation);
    NAM9.Debug("NAM9", debugLevel, indentation);

    SNAM.Debug("SNAM", debugLevel, indentation);
    OFST.Debug("OFST", debugLevel, indentation);
    }
#endif
