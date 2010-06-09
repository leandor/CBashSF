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
                printf("  WATR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int WATRRecord::GetSize(bool forceCalc)
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
    if(TNAM.IsLoaded())
        {
        cSize = TNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;
    if(FNAM.IsLoaded())
        TotSize += FNAM.GetSize() + 6;
    if(MNAM.IsLoaded())
        {
        cSize = MNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(GNAM.IsLoaded())
        TotSize += GNAM.GetSize() + 6;
    return TotSize;
    }

int WATRRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord(eTNAM, TNAM.value, TNAM.GetSize());
    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord(eANAM, &ANAM.value, ANAM.GetSize());
    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord(eFNAM, &FNAM.value, FNAM.GetSize());
    if(MNAM.IsLoaded())
        SaveHandler.writeSubRecord(eMNAM, MNAM.value, MNAM.GetSize());
    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord(eSNAM, SNAM.value, SNAM.GetSize());
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, DATA.value, DATA.GetSize());
    if(GNAM.IsLoaded())
        SaveHandler.writeSubRecord(eGNAM, GNAM.value, GNAM.GetSize());
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
