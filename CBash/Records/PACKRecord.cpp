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
#include "PACKRecord.h"
#include <vector>

int PACKRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    ReqRecordField<GENCTDA> *newCTDA = NULL;
    std::pair<unsigned int, unsigned int> CTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
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
            case ePKDT:
                switch(subSize)
                    {
                    case 4:
                        //old format (flags was originally a short, but changed to a uint; this change also affected the padding)
                        //PKDT.size = 8; //Force it to write out the updated version
                        _readBuffer(&PKDT.value.flags, buffer, 2, curPos);
                        _readBuffer(&PKDT.value.aiType, buffer, 1, curPos);
                        curPos++; //Skip over junk value. unused padding will default to 0
                        break;
                    default:
                        PKDT.Read(buffer, subSize, curPos);
                        break;
                    }
                break;
            case ePLDT:
                PLDT.Read(buffer, subSize, curPos);
                break;
            case ePSDT:
                PSDT.Read(buffer, subSize, curPos);
                break;
            case ePTDT:
                PTDT.Read(buffer, subSize, curPos);
                break;
            case eCTDT:
            case eCTDA:
                newCTDA = new ReqRecordField<GENCTDA>;
                newCTDA->Read(buffer, subSize, curPos);
                CTDA.push_back(newCTDA);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  PACK: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int PACKRecord::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(PKDT.IsLoaded())
        {
        cSize = PKDT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(PLDT.IsLoaded())
        {
        cSize = PLDT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(PSDT.IsLoaded())
        {
        cSize = PSDT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(PTDT.IsLoaded())
        {
        cSize = PTDT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CTDA.size())
        for(unsigned int p = 0; p < CTDA.size(); p++)
            if(CTDA[p]->IsLoaded())
                {
                cSize = CTDA[p]->GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
    return TotSize;
    }

int PACKRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(PKDT.IsLoaded())
        _writeSubRecord(buffer, ePKDT, PKDT.GetSize(), &PKDT.value, usedBuffer);
    if(PLDT.IsLoaded())
        _writeSubRecord(buffer, ePLDT, PLDT.GetSize(), PLDT.value, usedBuffer);
    if(PSDT.IsLoaded())
        _writeSubRecord(buffer, ePSDT, PSDT.GetSize(), &PSDT.value, usedBuffer);
    if(PTDT.IsLoaded())
        _writeSubRecord(buffer, ePTDT, PTDT.GetSize(), PTDT.value, usedBuffer);
    if(CTDA.size())
        for(unsigned int p = 0; p < CTDA.size(); p++)
            if(CTDA[p]->IsLoaded())
                _writeSubRecord(buffer, eCTDA, CTDA[p]->GetSize(), &CTDA[p]->value, usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void PACKRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  PACK\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    PKDT.Debug("PKDT", debugLevel, indentation);

    PLDT.Debug("PLDT", debugLevel, indentation);

    PSDT.Debug("PSDT", debugLevel, indentation);

    PTDT.Debug("PTDT", debugLevel, indentation);

    if(CTDA.size())
        {
        PrintIndent(indentation);
        printf("CTDA:\n");
        indentation += 2;
        for(unsigned int p = 0;p < CTDA.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            CTDA[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
