# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#include "..\Common.h"
#include "FACTRecord.h"

int FACTRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    ReqRecordField<GENXNAM> *newXNAM = NULL;
    ReqRecordField<FACTRNAM> *newRNAM = NULL;
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
                newXNAM = new ReqRecordField<GENXNAM>;
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
                newRNAM = new ReqRecordField<FACTRNAM>;
                newRNAM->Read(buffer, subSize, curPos);
                RNAM.push_back(newRNAM);
                break;
            case eMNAM:
                if(newRNAM == NULL)
                    {
                    newRNAM = new ReqRecordField<FACTRNAM>;
                    RNAM.push_back(newRNAM);
                    }
                newRNAM->value.MNAM.Read(buffer, subSize, curPos);
                break;
            case eFNAM:
                if(newRNAM == NULL)
                    {
                    newRNAM = new ReqRecordField<FACTRNAM>;
                    RNAM.push_back(newRNAM);
                    }
                newRNAM->value.FNAM.Read(buffer, subSize, curPos);
                break;
            case eINAM:
                if(newRNAM == NULL)
                    {
                    newRNAM = new ReqRecordField<FACTRNAM>;
                    RNAM.push_back(newRNAM);
                    }
                newRNAM->value.INAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  FACT: Unknown subType = %04X\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int FACTRecord::GetSize()
    {
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
    for(unsigned int p = 0; p < XNAM.size(); p++)
        {
        cSize = XNAM[p]->GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CNAM.IsLoaded())
        {
        cSize = CNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    for(unsigned int p = 0; p < RNAM.size(); p++)
        {
        cSize = sizeof(RNAM[p]->value.RNAM);
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
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

int FACTRecord::WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(FULL.IsLoaded())
        _writeSubRecord(buffer, eFULL, FULL.GetSize(), FULL.value, usedBuffer);
    for(unsigned int p = 0; p < XNAM.size(); p++)
        if(XNAM[p]->IsLoaded())
            _writeSubRecord(buffer, eXNAM, XNAM[p]->GetSize(), &XNAM[p]->value, usedBuffer);

    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    if(CNAM.IsLoaded())
        _writeSubRecord(buffer, eCNAM, CNAM.GetSize(), &CNAM.value, usedBuffer);

    for(unsigned int p = 0; p < RNAM.size(); p++)
        {
        if(RNAM[p]->IsLoaded())
            _writeSubRecord(buffer, eRNAM, sizeof(RNAM[p]->value.RNAM), &RNAM[p]->value.RNAM, usedBuffer);
        if(RNAM[p]->value.MNAM.IsLoaded())
            _writeSubRecord(buffer, eMNAM, RNAM[p]->value.MNAM.GetSize(), RNAM[p]->value.MNAM.value, usedBuffer);
        if(RNAM[p]->value.FNAM.IsLoaded())
            _writeSubRecord(buffer, eFNAM, RNAM[p]->value.FNAM.GetSize(), RNAM[p]->value.FNAM.value, usedBuffer);
        if(RNAM[p]->value.INAM.IsLoaded())
            _writeSubRecord(buffer, eINAM, RNAM[p]->value.INAM.GetSize(), RNAM[p]->value.INAM.value, usedBuffer);
        }
    return -1;
    }

#ifdef _DEBUG
void FACTRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
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
        for(unsigned int p=0;p < XNAM.size();p++)
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
        for(unsigned int p=0;p < RNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            RNAM[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }

    }
#endif
