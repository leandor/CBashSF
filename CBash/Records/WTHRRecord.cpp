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
#include "WTHRRecord.h"
#include <vector>

int WTHRRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    ReqRecordField<WTHRSNAM> *newSNAM = NULL;
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
            case eCNAM:
                CNAM.Read(buffer, subSize, curPos);
                break;
            case eDNAM:
                DNAM.Read(buffer, subSize, curPos);
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
            case eNAM0:
                NAM0.Read(buffer, subSize, curPos);
                break;
            case eFNAM:
                FNAM.Read(buffer, subSize, curPos);
                break;
            case eHNAM:
                HNAM.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                newSNAM = new ReqRecordField<WTHRSNAM>;
                newSNAM->Read(buffer, subSize, curPos);
                Sounds.push_back(newSNAM);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  WTHR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int WTHRRecord::GetSize(bool forceCalc)
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
    if(CNAM.IsLoaded())
        {
        cSize = CNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DNAM.IsLoaded())
        {
        cSize = DNAM.GetSize();
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
    if(NAM0.IsLoaded())
        TotSize += NAM0.GetSize() + 6;
    if(FNAM.IsLoaded())
        TotSize += FNAM.GetSize() + 6;
    if(HNAM.IsLoaded())
        TotSize += HNAM.GetSize() + 6;
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(Sounds.size())
        for(unsigned int p = 0; p < Sounds.size(); p++)
            TotSize += Sounds[p]->GetSize() + 6;
    return TotSize;
    }

int WTHRRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord(eCNAM, CNAM.value, CNAM.GetSize());
    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord(eDNAM, DNAM.value, DNAM.GetSize());
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        SaveHandler.writeSubRecord(eMODL, MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord(eMODB, &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord(eMODT, MODL->MODT.value, MODL->MODT.GetSize());
        }
    if(NAM0.IsLoaded())
        SaveHandler.writeSubRecord(eNAM0, &NAM0.value, NAM0.GetSize());
    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord(eFNAM, &FNAM.value, FNAM.GetSize());
    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord(eHNAM, &HNAM.value, HNAM.GetSize());
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
    if(Sounds.size())
        for(unsigned int p = 0; p < Sounds.size(); p++)
            SaveHandler.writeSubRecord(eSNAM, &Sounds[p]->value, Sounds[p]->GetSize());
    return -1;
    }

#ifdef _DEBUG
void WTHRRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  WTHR\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    CNAM.Debug("CNAM", debugLevel, indentation);

    DNAM.Debug("DNAM", debugLevel, indentation);

    MODL.Debug("MODL", debugLevel, indentation);

    NAM0.Debug("NAM0", debugLevel, indentation);

    FNAM.Debug("FNAM", debugLevel, indentation);

    HNAM.Debug("HNAM", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

    if(Sounds.size())
        {
        PrintIndent(indentation);
        printf("Sounds:\n");
        indentation += 2;
        for(unsigned int p = 0;p < Sounds.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Sounds[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
