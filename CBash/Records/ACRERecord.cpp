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
#include "ACRERecord.h"

int ACRERecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
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
            case eNAME:
                NAME.Read(buffer, subSize, curPos);
                break;
            case eXOWN:
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize, curPos);
                break;
            case eXRNK:
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize, curPos);
                break;
            case eXGLB:
                Ownership.Load();
                Ownership->XGLB.Read(buffer, subSize, curPos);
                break;
            case eXESP:
                XESP.Read(buffer, subSize, curPos);
                break;
            case eXRGD:
                XRGD.Read(buffer, subSize, curPos);
                break;
            case eXSCL:
                XSCL.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  ACRE: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int ACRERecord::GetSize()
    {
    if(recData != NULL)
        return *(unsigned int*)&recData[-16];
    unsigned int cSize = 0;
    unsigned int TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAME.IsLoaded())
        TotSize += NAME.GetSize() + 6;

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        TotSize += Ownership->XOWN.GetSize() + 6;
        if(Ownership->XRNK.IsLoaded())
            TotSize += Ownership->XRNK.GetSize() + 6;
        if(Ownership->XGLB.IsLoaded())
            TotSize += Ownership->XGLB.GetSize() + 6;
        }

    if(XESP.IsLoaded())
        TotSize += XESP.GetSize() + 6;

    if(XRGD.IsLoaded())
        {
        cSize = XRGD.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XSCL.IsLoaded())
        TotSize += XSCL.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

int ACRERecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    char null = 0;

    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);

    if(NAME.IsLoaded())
        _writeSubRecord(buffer, eNAME, NAME.GetSize(), &NAME.value, usedBuffer);

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        _writeSubRecord(buffer, eXOWN, Ownership->XOWN.GetSize(), &Ownership->XOWN.value, usedBuffer);
        if(Ownership->XRNK.IsLoaded())
            _writeSubRecord(buffer, eXRNK, Ownership->XRNK.GetSize(), Ownership->XRNK.value, usedBuffer);
        if(Ownership->XGLB.IsLoaded())
            _writeSubRecord(buffer, eXGLB, Ownership->XGLB.GetSize(), Ownership->XGLB.value, usedBuffer);
        }

    if(XESP.IsLoaded())
        _writeSubRecord(buffer, eXESP, XESP.GetSize(), XESP.value, usedBuffer);

    if(XRGD.IsLoaded())
        _writeSubRecord(buffer, eXRGD, XRGD.GetSize(), XRGD.value, usedBuffer);

    if(XSCL.IsLoaded())
        _writeSubRecord(buffer, eXSCL, XSCL.GetSize(), XSCL.value, usedBuffer);

    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void ACRERecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  ACRE\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    NAME.Debug("NAME", debugLevel, indentation);

    Ownership.Debug("Ownership", debugLevel, indentation);

    XESP.Debug("XESP", debugLevel, indentation);

    XRGD.Debug("XRGD", debugLevel, indentation);

    XSCL.Debug("XSCL", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);
    }
#endif
