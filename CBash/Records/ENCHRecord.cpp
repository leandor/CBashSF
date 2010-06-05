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
#include "ENCHRecord.h"
#include <vector>

int ENCHRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    GENEffect *newEffect = NULL;
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
                if(newEffect == NULL)
                    FULL.Read(buffer, subSize, curPos);
                else
                    newEffect->FULL.Read(buffer, subSize, curPos);
                break;
            case eENIT:
                ENIT.Read(buffer, subSize, curPos);
                break;
            case eEFID:
                newEffect = new GENEffect;
                newEffect->EFID.Read(buffer, subSize, curPos);
                Effects.push_back(newEffect);
                break;
            case eEFIT:
                if(newEffect == NULL)
                    {
                    newEffect = new GENEffect;
                    Effects.push_back(newEffect);
                    }
                newEffect->EFIT.Read(buffer, subSize, curPos);
                break;
            case eSCIT:
                if(newEffect == NULL)
                    {
                    newEffect = new GENEffect;
                    Effects.push_back(newEffect);
                    }
                newEffect->SCIT.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ENCH: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int ENCHRecord::GetSize(bool forceCalc)
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
    if(ENIT.IsLoaded())
        TotSize += ENIT.GetSize() + 6;
    if(Effects.size())
        for(unsigned int p = 0; p < Effects.size(); p++)
            {
            if(Effects[p]->EFID.IsLoaded())
                TotSize += Effects[p]->EFID.GetSize() + 6;
            if(Effects[p]->EFIT.IsLoaded())
                TotSize += Effects[p]->EFIT.GetSize() + 6;
            if(Effects[p]->SCIT.IsLoaded())
                TotSize += Effects[p]->SCIT.GetSize() + 6;
            if(Effects[p]->FULL.IsLoaded())
                {
                cSize = Effects[p]->FULL.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            }
    return TotSize;
    }

int ENCHRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(FULL.IsLoaded())
        _writeSubRecord(buffer, eFULL, FULL.GetSize(), FULL.value, usedBuffer);
    if(ENIT.IsLoaded())
        _writeSubRecord(buffer, eENIT, ENIT.GetSize(), &ENIT.value, usedBuffer);
    if(Effects.size())
        for(unsigned int p = 0; p < Effects.size(); p++)
            {
            if(Effects[p]->EFID.IsLoaded())
                _writeSubRecord(buffer, eEFID, Effects[p]->EFID.GetSize(), &Effects[p]->EFID.value, usedBuffer);
            if(Effects[p]->EFIT.IsLoaded())
                _writeSubRecord(buffer, eEFIT, Effects[p]->EFIT.GetSize(), &Effects[p]->EFIT.value, usedBuffer);
            if(Effects[p]->SCIT.IsLoaded())
                _writeSubRecord(buffer, eSCIT, Effects[p]->SCIT.GetSize(), Effects[p]->SCIT.value, usedBuffer);
            if(Effects[p]->FULL.IsLoaded())
                _writeSubRecord(buffer, eFULL, Effects[p]->FULL.GetSize(), Effects[p]->FULL.value, usedBuffer);
            }
    return -1;
    }

#ifdef _DEBUG
void ENCHRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  ENCH\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    ENIT.Debug("ENIT", debugLevel, indentation);

    if(Effects.size())
        {
        PrintIndent(indentation);
        printf("Effects:\n");
        indentation += 2;
        for(unsigned int p = 0;p < Effects.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Effects[p]->Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
