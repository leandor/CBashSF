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
#include "DOORRecord.h"
#include <vector>

int DOORRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
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
            case eMODL:
                MODL.MODL.Read(buffer, subSize, curPos);
                break;
            case eMODB:
                MODL.MODB.Read(buffer, subSize, curPos);
                break;
            case eMODT:
                MODL.MODT.Read(buffer, subSize, curPos);
                break;
            case eSCRI:
                SCRI.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                SNAM.Read(buffer, subSize, curPos);
                break;
            case eANAM:
                ANAM.Read(buffer, subSize, curPos);
                break;
            case eBNAM:
                BNAM.Read(buffer, subSize, curPos);
                break;
            case eFNAM:
                FNAM.Read(buffer, subSize, curPos);
                break;
            case eTNAM:
                curFormID = new unsigned int;
                _readBuffer(curFormID,buffer,subSize,curPos);
                TNAM.push_back(curFormID);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  DOOR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int DOORRecord::GetSize(bool forceCalc)
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
    if(MODL.MODL.IsLoaded())
        {
        cSize = MODL.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MODL.MODB.IsLoaded())
        TotSize += MODL.MODB.GetSize() + 6;
    if(MODL.MODT.IsLoaded())
        {
        cSize = MODL.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;
    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;
    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;
    if(BNAM.IsLoaded())
        TotSize += BNAM.GetSize() + 6;
    if(FNAM.IsLoaded())
        TotSize += FNAM.GetSize() + 6;
    if(TNAM.size())
        TotSize += (unsigned int)TNAM.size() * (sizeof(unsigned int) + 6);
    return TotSize;
    }

int DOORRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    if(MODL.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MODL.MODL.value, MODL.MODL.GetSize());
    if(MODL.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MODL.MODB.value, MODL.MODB.GetSize());
    if(MODL.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MODL.MODT.value, MODL.MODT.GetSize());
    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord(eSCRI, SCRI.value, SCRI.GetSize());
    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord(eSNAM, SNAM.value, SNAM.GetSize());
    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord(eANAM, ANAM.value, ANAM.GetSize());
    if(BNAM.IsLoaded())
        SaveHandler.writeSubRecord(eBNAM, BNAM.value, BNAM.GetSize());
    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord(eFNAM, &FNAM.value, FNAM.GetSize());
    if(TNAM.size())
        for(unsigned int p = 0; p < TNAM.size(); p++)
            SaveHandler.writeSubRecord(eTNAM, TNAM[p], sizeof(unsigned int));
    return -1;
    }

#ifdef _DEBUG
void DOORRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  DOOR\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    MODL.Debug("MODL", debugLevel, indentation);

    SCRI.Debug("SCRI", debugLevel, indentation);

    SNAM.Debug("SNAM", debugLevel, indentation);

    ANAM.Debug("ANAM", debugLevel, indentation);

    BNAM.Debug("BNAM", debugLevel, indentation);

    FNAM.Debug("FNAM", debugLevel, indentation);

    if(TNAM.size())
        {
        PrintIndent(indentation);
        printf("TNAM:\n");
        indentation += 2;
        for(unsigned int p = 0;p < TNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(TNAM[p]));
            }
        indentation -= 2;
        }
    }
#endif
