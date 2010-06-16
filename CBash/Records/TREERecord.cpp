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
#include "TREERecord.h"
#include <vector>

int TREERecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
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
            case eMODL:
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case eMODB:
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case eMODT:
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case eICON:
                ICON.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                if(subSize % sizeof(unsigned int) == 0)
                    {
                    if(subSize == 0)
                        break;
                    SNAM.resize(subSize / sizeof(unsigned int));
                    _readBuffer(&SNAM[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized SNAM size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eCNAM:
                CNAM.Read(buffer, subSize, curPos);
                break;
            case eBNAM:
                BNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  TREE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int TREERecord::GetSize(bool forceCalc)
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
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        cSize = MODL->MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        if(MODL->MODB.IsLoaded())
            TotSize += MODL->MODB.GetSize() + 6;
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }
    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SNAM.size())
        {
        cSize = (sizeof(unsigned int) * (unsigned int)SNAM.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;
    if(BNAM.IsLoaded())
        TotSize += BNAM.GetSize() + 6;
    return TotSize;
    }

int TREERecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        SaveHandler.writeSubRecord(eMODL, MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord(eMODB, &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord(eMODT, MODL->MODT.value, MODL->MODT.GetSize());
        }
    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, ICON.value, ICON.GetSize());
    if(SNAM.size())
        SaveHandler.writeSubRecord(eSNAM, &SNAM[0], (unsigned int)SNAM.size() * sizeof(unsigned int));
    //else
    //    SaveHandler.writeSubRecord(eSNAM, NULL, 0);
    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord(eCNAM, &CNAM.value, CNAM.GetSize());
    if(BNAM.IsLoaded())
        SaveHandler.writeSubRecord(eBNAM, &BNAM.value, BNAM.GetSize());
    return -1;
    }

#ifdef _DEBUG
void TREERecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  TREE\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    MODL.Debug("MODL", debugLevel, indentation);

    ICON.Debug("ICON", debugLevel, indentation);

    if(SNAM.size())
        {
        PrintIndent(indentation);
        printf("SNAM:\n");
        indentation += 2;
        for(unsigned int p = 0;p < SNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%u\n", p, SNAM[p]);
            }
        indentation -= 2;
        }

    CNAM.Debug("CNAM", debugLevel, indentation);

    BNAM.Debug("BNAM", debugLevel, indentation);
    }
#endif
