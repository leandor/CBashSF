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
#include "ACHRRecord.h"

int ACHRRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
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
            case eXPCI:
                XPCI.Load();
                XPCI->XPCI.Read(buffer, subSize, curPos);
                break;
            case eFULL:
                XPCI.Load();
                XPCI->FULL.Read(buffer, subSize, curPos);
                break;
            case eXLOD:
                XLOD.Read(buffer, subSize, curPos);
                break;
            case eXESP:
                XESP.Read(buffer, subSize, curPos);
                break;
            case eXMRC:
                XMRC.Read(buffer, subSize, curPos);
                break;
            case eXHRS:
                XHRS.Read(buffer, subSize, curPos);
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
                printf("  ACHR: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int ACHRRecord::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAME.IsLoaded())
        {
        cSize = NAME.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        {
        cSize = XPCI->XPCI.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        if(XPCI->FULL.IsLoaded())
            {
            cSize = XPCI->FULL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        else TotSize += 7;
        }

    if(XLOD.IsLoaded())
        {
        cSize = XLOD.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XESP.IsLoaded())
        {
        cSize = XESP.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XMRC.IsLoaded())
        {
        cSize = XMRC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XHRS.IsLoaded())
        {
        cSize = XHRS.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XRGD.IsLoaded())
        {
        cSize = XRGD.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XSCL.IsLoaded())
        {
        cSize = XSCL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

int ACHRRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    char null = 0;

    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);

    if(NAME.IsLoaded())
        _writeSubRecord(buffer, eNAME, NAME.GetSize(), &NAME.value, usedBuffer);

    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        {
        _writeSubRecord(buffer, eXPCI, XPCI->XPCI.GetSize(), XPCI->XPCI.value, usedBuffer);
        if(XPCI->FULL.IsLoaded())
            _writeSubRecord(buffer, eFULL, XPCI->FULL.GetSize(), XPCI->FULL.value, usedBuffer);
        else
            _writeSubRecord(buffer, eFULL, 1, &null, usedBuffer);
        }

    if(XLOD.IsLoaded())
        _writeSubRecord(buffer, eXLOD, XLOD.GetSize(), XLOD.value, usedBuffer);

    if(XESP.IsLoaded())
        _writeSubRecord(buffer, eXESP, XESP.GetSize(), XESP.value, usedBuffer);

    if(XMRC.IsLoaded())
        _writeSubRecord(buffer, eXMRC, XMRC.GetSize(), XMRC.value, usedBuffer);

    if(XHRS.IsLoaded())
        _writeSubRecord(buffer, eXHRS, XHRS.GetSize(), &XHRS.value, usedBuffer);

    if(XRGD.IsLoaded())
        _writeSubRecord(buffer, eXRGD, XRGD.GetSize(), XRGD.value, usedBuffer);

    if(XSCL.IsLoaded())
        _writeSubRecord(buffer, eXSCL, XSCL.GetSize(), XSCL.value, usedBuffer);

    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void ACHRRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  ACHR\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    NAME.Debug("NAME", debugLevel, indentation);

    XPCI.Debug("XPCI", debugLevel, indentation);

    XLOD.Debug("XLOD", debugLevel, indentation);

    XESP.Debug("XESP", debugLevel, indentation);

    XMRC.Debug("XMRC", debugLevel, indentation);

    XHRS.Debug("XHRS", debugLevel, indentation);

    XRGD.Debug("XRGD", debugLevel, indentation);

    XSCL.Debug("XSCL", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);
    }
#endif
