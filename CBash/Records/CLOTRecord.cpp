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

            case eMOD2:
                MOD2.Load();
                MOD2->MODL.Read(buffer, subSize, curPos);
                break;
            case eMO2B:
                MOD2.Load();
                MOD2->MODB.Read(buffer, subSize, curPos);
                break;
            case eMO2T:
                MOD2.Load();
                MOD2->MODT.Read(buffer, subSize, curPos);
                break;

            case eMOD3:
                MOD3.Load();
                MOD3->MODL.Read(buffer, subSize, curPos);
                break;
            case eMO3B:
                MOD3.Load();
                MOD3->MODB.Read(buffer, subSize, curPos);
                break;
            case eMO3T:
                MOD3.Load();
                MOD3->MODT.Read(buffer, subSize, curPos);
                break;

            case eMOD4:
                MOD4.Load();
                MOD4->MODL.Read(buffer, subSize, curPos);
                break;
            case eMO4B:
                MOD4.Load();
                MOD4->MODB.Read(buffer, subSize, curPos);
                break;
            case eMO4T:
                MOD4.Load();
                MOD4->MODT.Read(buffer, subSize, curPos);
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
                printf("  CLOT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int CLOTRecord::GetSize(bool forceCalc)
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
    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;
    if(ENAM.IsLoaded())
        TotSize += ENAM.GetSize() + 6;
    if(ANAM.IsLoaded())
        TotSize += ANAM.GetSize() + 6;
    if(BMDT.IsLoaded())
        TotSize += BMDT.GetSize() + 6;
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
    if(MOD2.IsLoaded() && MOD2->MODL.IsLoaded())
        {
        cSize = MOD2->MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        if(MOD2->MODB.IsLoaded())
            TotSize += MOD2->MODB.GetSize() + 6;
        if(MOD2->MODT.IsLoaded())
            {
            cSize = MOD2->MODT.GetSize();
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
    if(MOD3.IsLoaded() && MOD3->MODL.IsLoaded())
        {
        cSize = MOD3->MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        if(MOD3->MODB.IsLoaded())
            TotSize += MOD3->MODB.GetSize() + 6;
        if(MOD3->MODT.IsLoaded())
            {
            cSize = MOD3->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }
    if(MOD4.IsLoaded() && MOD4->MODL.IsLoaded())
        {
        cSize = MOD4->MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        if(MOD4->MODB.IsLoaded())
            TotSize += MOD4->MODB.GetSize() + 6;
        if(MOD4->MODT.IsLoaded())
            {
            cSize = MOD4->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }
    if(ICO2.IsLoaded())
        {
        cSize = ICO2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    return TotSize;
    }

int CLOTRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord(eSCRI, SCRI.value, SCRI.GetSize());
    if(ENAM.IsLoaded())
        SaveHandler.writeSubRecord(eENAM, ENAM.value, ENAM.GetSize());
    if(ANAM.IsLoaded())
        SaveHandler.writeSubRecord(eANAM, ANAM.value, ANAM.GetSize());
    if(BMDT.IsLoaded())
        SaveHandler.writeSubRecord(eBMDT, &BMDT.value, BMDT.GetSize());
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        SaveHandler.writeSubRecord(eMODL, MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord(eMODB, &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord(eMODT, MODL->MODT.value, MODL->MODT.GetSize());
        }
    if(MOD2.IsLoaded() && MOD2->MODL.IsLoaded())
        {
        SaveHandler.writeSubRecord(eMOD2, MOD2->MODL.value, MOD2->MODL.GetSize());
        if(MOD2->MODB.IsLoaded())
            SaveHandler.writeSubRecord(eMO2B, &MOD2->MODB.value, MOD2->MODB.GetSize());
        if(MOD2->MODT.IsLoaded())
            SaveHandler.writeSubRecord(eMO2T, MOD2->MODT.value, MOD2->MODT.GetSize());
        }
    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, ICON.value, ICON.GetSize());

    if(MOD3.IsLoaded() && MOD3->MODL.IsLoaded())
        {
        SaveHandler.writeSubRecord(eMOD3, MOD3->MODL.value, MOD3->MODL.GetSize());
        if(MOD3->MODB.IsLoaded())
            SaveHandler.writeSubRecord(eMO3B, &MOD3->MODB.value, MOD3->MODB.GetSize());
        if(MOD3->MODT.IsLoaded())
            SaveHandler.writeSubRecord(eMO3T, MOD3->MODT.value, MOD3->MODT.GetSize());
        }
    if(MOD4.IsLoaded() && MOD4->MODL.IsLoaded())
        {
        SaveHandler.writeSubRecord(eMOD4, MOD4->MODL.value, MOD4->MODL.GetSize());
        if(MOD4->MODB.IsLoaded())
            SaveHandler.writeSubRecord(eMO4B, &MOD4->MODB.value, MOD4->MODB.GetSize());
        if(MOD4->MODT.IsLoaded())
            SaveHandler.writeSubRecord(eMO4T, MOD4->MODT.value, MOD4->MODT.GetSize());
        }
    if(ICO2.IsLoaded())
        SaveHandler.writeSubRecord(eICO2, ICO2.value, ICO2.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
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
