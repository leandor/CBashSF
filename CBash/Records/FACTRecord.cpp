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
#include "FACTRecord.h"

signed long FACTRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned long subType = 0;
    unsigned long subSize = 0;
    unsigned long curPos = 0;
    ReqSubRecord<GENXNAM> *newXNAM = NULL;
    ReqSubRecord<FACTRNAM> *newRNAM = NULL;
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
            case eXNAM:
                newXNAM = new ReqSubRecord<GENXNAM>;
                newXNAM->Read(buffer, subSize, curPos);
                XNAM.push_back(newXNAM);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eCNAM:
                CNAM.Read(buffer, subSize, curPos);
                break;
            case eRNAM:
                newRNAM = new ReqSubRecord<FACTRNAM>;
                newRNAM->Read(buffer, subSize, curPos);
                RNAM.push_back(newRNAM);
                break;
            case eMNAM:
                if(newRNAM == NULL)
                    {
                    newRNAM = new ReqSubRecord<FACTRNAM>;
                    RNAM.push_back(newRNAM);
                    }
                newRNAM->value.MNAM.Read(buffer, subSize, curPos);
                break;
            case eFNAM:
                if(newRNAM == NULL)
                    {
                    newRNAM = new ReqSubRecord<FACTRNAM>;
                    RNAM.push_back(newRNAM);
                    }
                newRNAM->value.FNAM.Read(buffer, subSize, curPos);
                break;
            case eINAM:
                if(newRNAM == NULL)
                    {
                    newRNAM = new ReqSubRecord<FACTRNAM>;
                    RNAM.push_back(newRNAM);
                    }
                newRNAM->value.INAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  FACT: Unknown subType = %04X\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long FACTRecord::GetSize(bool forceCalc)
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
    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    for(unsigned long p = 0; p < XNAM.size(); p++)
        TotSize += XNAM[p]->GetSize() + 6;
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;
    for(unsigned long p = 0; p < RNAM.size(); p++)
        {
        TotSize += sizeof(RNAM[p]->value.RNAM) + 6;
        if(RNAM[p]->value.MNAM.IsLoaded())
            {
            cSize = RNAM[p]->value.MNAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(RNAM[p]->value.FNAM.IsLoaded())
            {
            cSize = RNAM[p]->value.FNAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(RNAM[p]->value.INAM.IsLoaded())
            {
            cSize = RNAM[p]->value.INAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }
    return TotSize;
    }

signed long FACTRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    for(unsigned long p = 0; p < XNAM.size(); p++)
        if(XNAM[p]->IsLoaded())
            SaveHandler.writeSubRecord(eXNAM, &XNAM[p]->value, XNAM[p]->GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord(eCNAM, &CNAM.value, CNAM.GetSize());

    for(unsigned long p = 0; p < RNAM.size(); p++)
        {
        if(RNAM[p]->IsLoaded())
            SaveHandler.writeSubRecord(eRNAM, &RNAM[p]->value.RNAM, sizeof(RNAM[p]->value.RNAM));
        if(RNAM[p]->value.MNAM.IsLoaded())
            SaveHandler.writeSubRecord(eMNAM, RNAM[p]->value.MNAM.value, RNAM[p]->value.MNAM.GetSize());
        if(RNAM[p]->value.FNAM.IsLoaded())
            SaveHandler.writeSubRecord(eFNAM, RNAM[p]->value.FNAM.value, RNAM[p]->value.FNAM.GetSize());
        if(RNAM[p]->value.INAM.IsLoaded())
            SaveHandler.writeSubRecord(eINAM, RNAM[p]->value.INAM.value, RNAM[p]->value.INAM.GetSize());
        }
    return -1;
    }

#ifdef _DEBUG
void FACTRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
    printf("  FACT\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    if(XNAM.size())
        {
        PrintIndent(indentation);
        printf("XNAM:\n");
        indentation += 2;
        for(unsigned long p=0;p < XNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            XNAM[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }

    DATA.Debug("DATA", debugLevel, indentation);

    CNAM.Debug("CNAM", debugLevel, indentation);

    if(RNAM.size())
        {
        PrintIndent(indentation);
        printf("RNAM:\n");
        indentation += 2;
        for(unsigned long p=0;p < RNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            RNAM[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }

    }
#endif
