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
                printf("  WRLD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int WRLDRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && recData != NULL)
        return *(unsigned int*)&recData[-16];
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
        TotSize += WNAM.GetSize() + 6;
    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;
    if(NAM2.IsLoaded())
        TotSize += NAM2.GetSize() + 6;

    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MNAM.IsLoaded())
        TotSize += MNAM.GetSize() + 6;
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    if(NAM0.IsLoaded())
        TotSize += NAM0.GetSize() + 6;
    if(NAM9.IsLoaded())
        TotSize += NAM9.GetSize() + 6;

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;
    if(OFST.IsLoaded())
        {
        cSize = OFST.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    return TotSize;
    }

int WRLDRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());

    if(WNAM.IsLoaded())
        SaveHandler.writeSubRecord(eWNAM, WNAM.value, WNAM.GetSize());
    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord(eCNAM, CNAM.value, CNAM.GetSize());
    if(NAM2.IsLoaded())
        SaveHandler.writeSubRecord(eNAM2, NAM2.value, NAM2.GetSize());

    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, ICON.value, ICON.GetSize());

    if(MNAM.IsLoaded())
        SaveHandler.writeSubRecord(eMNAM, MNAM.value, MNAM.GetSize());
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());

    if(NAM0.IsLoaded())
        SaveHandler.writeSubRecord(eNAM0, &NAM0.value, NAM0.GetSize());
    if(NAM9.IsLoaded())
        SaveHandler.writeSubRecord(eNAM9, &NAM9.value, NAM9.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord(eSNAM, SNAM.value, SNAM.GetSize());
    if(OFST.IsLoaded())
        SaveHandler.writeSubRecord(eOFST, OFST.value, OFST.GetSize());

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
