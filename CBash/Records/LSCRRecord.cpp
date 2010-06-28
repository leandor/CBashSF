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
#include "LSCRRecord.h"
#include <vector>

int LSCRRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    ReqSubRecord<LSCRLNAM> *newLNAM = NULL;
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
            case eICON:
                ICON.Read(buffer, subSize, curPos);
                break;
            case eDESC:
                DESC.Read(buffer, subSize, curPos);
                break;
            case eLNAM:
                newLNAM = new ReqSubRecord<LSCRLNAM>;
                newLNAM->Read(buffer, subSize, curPos);
                LNAM.push_back(newLNAM);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LSCR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int LSCRRecord::GetSize(bool forceCalc)
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
    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    for(unsigned int p = 0; p < LNAM.size(); p++)
        if(LNAM[p]->IsLoaded())
            TotSize += LNAM[p]->GetSize() + 6;
    return TotSize;
    }

int LSCRRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, ICON.value, ICON.GetSize());
    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord(eDESC, DESC.value, DESC.GetSize());
    for(unsigned int p = 0; p < LNAM.size(); p++)
        if(LNAM[p]->IsLoaded())
            SaveHandler.writeSubRecord(eLNAM, &LNAM[p]->value, LNAM[p]->GetSize());
    return -1;
    }

#ifdef _DEBUG
void LSCRRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  LSCR\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    ICON.Debug("ICON", debugLevel, indentation);

    DESC.Debug("DESC", debugLevel, indentation);

    if(LNAM.size())
        {
        PrintIndent(indentation);
        printf("LNAM:\n");
        indentation += 2;
        for(unsigned int p=0;p < LNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            LNAM[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
