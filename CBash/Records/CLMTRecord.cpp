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
#include "CLMTRecord.h"
#include <vector>

signed long CLMTRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
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
            case eWLST:
                if(subSize % sizeof(CLMTWLST) == 0)
                    {
                    if(subSize == 0)
                        break;
                    Weathers.resize(subSize / sizeof(CLMTWLST));
                    _readBuffer(&Weathers[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized Weathers size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eFNAM:
                FNAM.Read(buffer, subSize, curPos);
                break;
            case eGNAM:
                GNAM.Read(buffer, subSize, curPos);
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
            case eTNAM:
                TNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CLMT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long CLMTRecord::GetSize(bool forceCalc)
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
    if(Weathers.size())
        {
        cSize = (sizeof(CLMTWLST) * (unsigned long)Weathers.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FNAM.IsLoaded())
        {
        cSize = FNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(GNAM.IsLoaded())
        {
        cSize = GNAM.GetSize();
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

    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;
    return TotSize;
    }

signed long CLMTRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(Weathers.size())
        SaveHandler.writeSubRecord(eWLST, &Weathers[0], (unsigned long)Weathers.size() * sizeof(CLMTWLST));
    //else
    //    SaveHandler.writeSubRecord(eWLST, NULL, 0);

    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord(eFNAM, FNAM.value, FNAM.GetSize());
    if(GNAM.IsLoaded())
        SaveHandler.writeSubRecord(eGNAM, GNAM.value, GNAM.GetSize());

    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        SaveHandler.writeSubRecord(eMODL, MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord(eMODB, &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord(eMODT, MODL->MODT.value, MODL->MODT.GetSize());
        }

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord(eTNAM, &TNAM.value, TNAM.GetSize());
    return -1;
    }

#ifdef _DEBUG
void CLMTRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
    printf("  CLMT\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    if(Weathers.size())
        {
        PrintIndent(indentation);
        printf("Weathers:\n");
        indentation += 2;
        for(unsigned long p = 0;p < Weathers.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Weathers[p].Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }

    FNAM.Debug("FNAM", debugLevel, indentation);

    GNAM.Debug("GNAM", debugLevel, indentation);

    MODL.Debug("MODL", debugLevel, indentation);

    TNAM.Debug("TNAM", debugLevel, indentation);
    }
#endif
