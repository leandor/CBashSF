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
#include "SPELRecord.h"

int SPELRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    GENEffect *newEffect = NULL;
    bool bNoOBME = true;
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
            case eOBME:
                OBME.Load();
                OBME->OBME.Read(buffer, subSize, curPos);
                break;
            case eFULL:
                if(newEffect == NULL)
                    FULL.Read(buffer, subSize, curPos);
                else
                    newEffect->FULL.Read(buffer, subSize, curPos);
                break;
            case eSPIT:
                SPIT.Read(buffer, subSize, curPos);
                break;
            case eEFME:
                bNoOBME = false;
                newEffect = new GENEffect;
                newEffect->OBME.Load();
                newEffect->OBME->EFME.Read(buffer, subSize, curPos);
                break;
            case eEFID:
                if(bNoOBME)
                    newEffect = new GENEffect;
                newEffect->EFID.Read(buffer, subSize, curPos);
                Effects.push_back(newEffect);
                bNoOBME = true;
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
                if(newEffect->SCIT->script == eBadScript)
                    newEffect->SCIT->script = 0x00000000;
                break;
            case eEFII:
                if(newEffect == NULL)
                    {
                    newEffect = new GENEffect;
                    Effects.push_back(newEffect);
                    }
                newEffect->OBME.Load();
                newEffect->OBME->EFII.Read(buffer, subSize, curPos);
                break;
            case eEFIX:
                if(newEffect == NULL)
                    {
                    newEffect = new GENEffect;
                    Effects.push_back(newEffect);
                    }
                newEffect->OBME.Load();
                newEffect->OBME->EFIX.Read(buffer, subSize, curPos);
                break;
            case eEFXX:
                curPos += subSize;
                break;
            case eDATX:
                OBME.Load();
                OBME->DATX.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  SPEL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int SPELRecord::GetSize(bool forceCalc)
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
    if(OBME.IsLoaded())
        {
        if(OBME->OBME.IsLoaded())
            TotSize += OBME->OBME.GetSize() + 6;
        if(OBME->DATX.IsLoaded())
            {
            cSize = OBME->DATX.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(Effects.size())
            TotSize += 6; //EFXX chunk
        }
    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SPIT.IsLoaded())
        {
        cSize = SPIT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(Effects.size())
        for(unsigned int p = 0; p < Effects.size(); p++)
            {
            if(Effects[p]->EFID.IsLoaded())
                TotSize += Effects[p]->EFID.GetSize() + 6;
            if(Effects[p]->EFIT.IsLoaded())
                TotSize += Effects[p]->EFIT.GetSize() + 6;
            if(Effects[p]->SCIT.IsLoaded() || Effects[p]->FULL.IsLoaded())
                TotSize += Effects[p]->SCIT.GetSize() + 6;
            if(Effects[p]->FULL.IsLoaded())
                {
                cSize = Effects[p]->FULL.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(Effects[p]->OBME.IsLoaded())
                {
                if(Effects[p]->OBME->EFME.IsLoaded())
                    TotSize += Effects[p]->OBME->EFME.GetSize() + 6;
                if(Effects[p]->OBME->EFII.IsLoaded())
                    {
                    cSize = Effects[p]->OBME->EFII.GetSize();
                    if(cSize > 65535) cSize += 10;
                    TotSize += cSize += 6;
                    }
                if(Effects[p]->OBME->EFIX.IsLoaded())
                    TotSize += Effects[p]->OBME->EFIX.GetSize() + 6;
                }
            }
    return TotSize;
    }

int SPELRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(OBME.IsLoaded() && OBME->OBME.IsLoaded())
        SaveHandler.writeSubRecord(eOBME, &OBME->OBME.value, OBME->OBME.GetSize());
    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    if(SPIT.IsLoaded())
        SaveHandler.writeSubRecord(eSPIT, &SPIT.value, SPIT.GetSize());
    if(Effects.size())
        for(unsigned int p = 0; p < Effects.size(); p++)
            {
            if(Effects[p]->OBME.IsLoaded() && Effects[p]->OBME->EFME.IsLoaded())
                SaveHandler.writeSubRecord(eEFME, &Effects[p]->OBME->EFME.value, Effects[p]->OBME->EFME.GetSize());
            if(Effects[p]->EFID.IsLoaded())
                SaveHandler.writeSubRecord(eEFID, &Effects[p]->EFID.value, Effects[p]->EFID.GetSize());
            if(Effects[p]->EFIT.IsLoaded())
                SaveHandler.writeSubRecord(eEFIT, &Effects[p]->EFIT.value, Effects[p]->EFIT.GetSize());
            if(Effects[p]->SCIT.IsLoaded() || Effects[p]->FULL.IsLoaded())
                SaveHandler.writeSubRecord(eSCIT, Effects[p]->SCIT.value, Effects[p]->SCIT.GetSize());
            if(Effects[p]->FULL.IsLoaded())
                SaveHandler.writeSubRecord(eFULL, Effects[p]->FULL.value, Effects[p]->FULL.GetSize());
            if(Effects[p]->OBME.IsLoaded() && Effects[p]->OBME->EFII.IsLoaded())
                SaveHandler.writeSubRecord(eEFII, Effects[p]->OBME->EFII.value, Effects[p]->OBME->EFII.GetSize());
            if(Effects[p]->OBME.IsLoaded() && Effects[p]->OBME->EFIX.IsLoaded())
                SaveHandler.writeSubRecord(eEFIX, Effects[p]->OBME->EFIX.value, Effects[p]->OBME->EFIX.GetSize());
            }
    if(Effects.size() && OBME.IsLoaded())
        SaveHandler.writeSubRecord(eEFXX, NULL, 0);
    if(OBME.IsLoaded() && OBME->DATX.IsLoaded())
        SaveHandler.writeSubRecord(eDATX, OBME->DATX.value, OBME->DATX.GetSize());
    return -1;
    }

#ifdef _DEBUG
void SPELRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  SPEL\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    SPIT.Debug("SPIT", debugLevel, indentation);

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
