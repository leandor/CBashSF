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
#include "CLOTRecord.h"
#include <vector>

int CLOTRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
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
            case eFULL:
                FULL.Read(buffer, subSize, curPos);
                break;
            case eSCRI:
                SCRI.Read(buffer, subSize, curPos);
                break;
            case eENAM:
                ENAM.Read(buffer, subSize, curPos);
                break;
            case eANAM:
                ANAM.Read(buffer, subSize, curPos);
                break;
            case eBMDT:
                BMDT.Read(buffer, subSize, curPos);
                break;

            case eMODL:
                MODL.MODL.Read(buffer, subSize, curPos);
                break;
            case eMODB:
                MODL.MODB.Read(buffer, subSize, curPos);
                break;
            case eMODT:
                MODL.MODT.Read(buffer, subSize, curPos);
                break;

            case eMOD2:
                MOD2.MODL.Read(buffer, subSize, curPos);
                break;
            case eMO2B:
                MOD2.MODB.Read(buffer, subSize, curPos);
                break;
            case eMO2T:
                MOD2.MODT.Read(buffer, subSize, curPos);
                break;

            case eMOD3:
                MOD3.MODL.Read(buffer, subSize, curPos);
                break;
            case eMO3B:
                MOD3.MODB.Read(buffer, subSize, curPos);
                break;
            case eMO3T:
                MOD3.MODT.Read(buffer, subSize, curPos);
                break;

            case eMOD4:
                MOD4.MODL.Read(buffer, subSize, curPos);
                break;
            case eMO4B:
                MOD4.MODB.Read(buffer, subSize, curPos);
                break;
            case eMO4T:
                MOD4.MODT.Read(buffer, subSize, curPos);
                break;

            case eICON:
                ICON.Read(buffer, subSize, curPos);
                break;
            case eICO2:
                ICO2.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CLOT: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int CLOTRecord::GetSize()
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
    if(SCRI.IsLoaded())
        {
        cSize = SCRI.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ENAM.IsLoaded())
        {
        cSize = ENAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ANAM.IsLoaded())
        {
        cSize = ANAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(BMDT.IsLoaded())
        {
        cSize = BMDT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MODL.MODL.IsLoaded())
        {
        cSize = MODL.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MODL.MODB.IsLoaded())
        {
        cSize = MODL.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MODL.MODT.IsLoaded())
        {
        cSize = MODL.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD2.MODL.IsLoaded())
        {
        cSize = MOD2.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD2.MODB.IsLoaded())
        {
        cSize = MOD2.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD2.MODT.IsLoaded())
        {
        cSize = MOD2.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD3.MODL.IsLoaded())
        {
        cSize = MOD3.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD3.MODB.IsLoaded())
        {
        cSize = MOD3.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD3.MODT.IsLoaded())
        {
        cSize = MOD3.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD4.MODL.IsLoaded())
        {
        cSize = MOD4.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD4.MODB.IsLoaded())
        {
        cSize = MOD4.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD4.MODT.IsLoaded())
        {
        cSize = MOD4.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ICO2.IsLoaded())
        {
        cSize = ICO2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    return TotSize;
    }

int CLOTRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(FULL.IsLoaded())
        _writeSubRecord(buffer, eFULL, FULL.GetSize(), FULL.value, usedBuffer);
    if(SCRI.IsLoaded())
        _writeSubRecord(buffer, eSCRI, SCRI.GetSize(), SCRI.value, usedBuffer);
    if(ENAM.IsLoaded())
        _writeSubRecord(buffer, eENAM, ENAM.GetSize(), ENAM.value, usedBuffer);
    if(ANAM.IsLoaded())
        _writeSubRecord(buffer, eANAM, ANAM.GetSize(), ANAM.value, usedBuffer);
    if(BMDT.IsLoaded())
        _writeSubRecord(buffer, eBMDT, BMDT.GetSize(), &BMDT.value, usedBuffer);

    if(MODL.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MODL.MODL.GetSize(), MODL.MODL.value, usedBuffer);
    if(MODL.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MODL.MODB.GetSize(), &MODL.MODB.value, usedBuffer);
    if(MODL.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MODL.MODT.GetSize(), MODL.MODT.value, usedBuffer);

    if(MOD2.MODL.IsLoaded())
        _writeSubRecord(buffer, eMOD2, MOD2.MODL.GetSize(), MOD2.MODL.value, usedBuffer);
    if(MOD2.MODB.IsLoaded())
        _writeSubRecord(buffer, eMO2B, MOD2.MODB.GetSize(), &MOD2.MODB.value, usedBuffer);
    if(MOD2.MODT.IsLoaded())
        _writeSubRecord(buffer, eMO2T, MOD2.MODT.GetSize(), MOD2.MODT.value, usedBuffer);
    if(ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, ICON.GetSize(), ICON.value, usedBuffer);

    if(MOD3.MODL.IsLoaded())
        _writeSubRecord(buffer, eMOD3, MOD3.MODL.GetSize(), MOD3.MODL.value, usedBuffer);
    if(MOD3.MODB.IsLoaded())
        _writeSubRecord(buffer, eMO3B, MOD3.MODB.GetSize(), &MOD3.MODB.value, usedBuffer);
    if(MOD3.MODT.IsLoaded())
        _writeSubRecord(buffer, eMO3T, MOD3.MODT.GetSize(), MOD3.MODT.value, usedBuffer);

    if(MOD4.MODL.IsLoaded())
        _writeSubRecord(buffer, eMOD4, MOD4.MODL.GetSize(), MOD4.MODL.value, usedBuffer);
    if(MOD4.MODB.IsLoaded())
        _writeSubRecord(buffer, eMO4B, MOD4.MODB.GetSize(), &MOD4.MODB.value, usedBuffer);
    if(MOD4.MODT.IsLoaded())
        _writeSubRecord(buffer, eMO4T, MOD4.MODT.GetSize(), MOD4.MODT.value, usedBuffer);
    if(ICO2.IsLoaded())
        _writeSubRecord(buffer, eICO2, ICO2.GetSize(), ICO2.value, usedBuffer);

    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void CLOTRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  CLOT\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    SCRI.Debug("SCRI", debugLevel, indentation);

    ENAM.Debug("ENAM", debugLevel, indentation);

    ANAM.Debug("ANAM", debugLevel, indentation);

    BMDT.Debug("BMDT", debugLevel, indentation);

    MODL.Debug("MODL", debugLevel, indentation);

    MOD2.Debug("MOD2", debugLevel, indentation);

    ICON.Debug("ICON", debugLevel, indentation);

    MOD3.Debug("MOD3", debugLevel, indentation);

    MOD4.Debug("MOD4", debugLevel, indentation);

    ICO2.Debug("ICO2", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);
    }
#endif
