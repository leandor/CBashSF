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
                MODL.MODL.Read(buffer, subSize, curPos);
                break;
            case eMODB:
                MODL.MODB.Read(buffer, subSize, curPos);
                break;
            case eMODT:
                MODL.MODT.Read(buffer, subSize, curPos);
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
                printf("  WTHR: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int WTHRRecord::GetSize()
    {
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
    if(MODL.MODL.IsLoaded())
        {
        cSize = MODL.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MODL.MODB.IsLoaded())
        {
        cSize = MODL.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MODL.MODT.IsLoaded())
        {
        cSize = MODL.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(NAM0.IsLoaded())
        {
        cSize = NAM0.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FNAM.IsLoaded())
        {
        cSize = FNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(HNAM.IsLoaded())
        {
        cSize = HNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(Sounds.size())
        for(unsigned int p = 0; p < Sounds.size(); p++)
            {
            cSize = Sounds[p]->GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
    return TotSize;
    }

int WTHRRecord::WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(CNAM.IsLoaded())
        _writeSubRecord(buffer, eCNAM, CNAM.GetSize(), CNAM.value, usedBuffer);
    if(DNAM.IsLoaded())
        _writeSubRecord(buffer, eDNAM, DNAM.GetSize(), DNAM.value, usedBuffer);
    if(MODL.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MODL.MODL.GetSize(), MODL.MODL.value, usedBuffer);
    if(MODL.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MODL.MODB.GetSize(), &MODL.MODB.value, usedBuffer);
    if(MODL.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MODL.MODT.GetSize(), MODL.MODT.value, usedBuffer);
    if(NAM0.IsLoaded())
        _writeSubRecord(buffer, eNAM0, NAM0.GetSize(), &NAM0.value, usedBuffer);
    if(FNAM.IsLoaded())
        _writeSubRecord(buffer, eFNAM, FNAM.GetSize(), &FNAM.value, usedBuffer);
    if(HNAM.IsLoaded())
        _writeSubRecord(buffer, eHNAM, HNAM.GetSize(), &HNAM.value, usedBuffer);
    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    if(Sounds.size())
        for(unsigned int p = 0; p < Sounds.size(); p++)
            _writeSubRecord(buffer, eSNAM, Sounds[p]->GetSize(), &Sounds[p]->value, usedBuffer);
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
