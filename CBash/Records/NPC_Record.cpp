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
#include "NPC_Record.h"
#include <vector>

int NPC_Record::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    FormID curFormID = NULL;
    ReqRecordField<GENSNAM> *newSNAM = NULL;
    ReqRecordField<GENCNTO> *newCNTO = NULL;
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
            case eMODL:
                MODL.MODL.Read(buffer, subSize, curPos);
                break;
            case eMODB:
                MODL.MODB.Read(buffer, subSize, curPos);
                break;
            case eMODT:
                MODL.MODT.Read(buffer, subSize, curPos);
                break;
            case eACBS:
                ACBS.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                newSNAM = new ReqRecordField<GENSNAM>;
                newSNAM->Read(buffer, subSize, curPos);
                SNAM.push_back(newSNAM);
                break;
            case eINAM:
                INAM.Read(buffer, subSize, curPos);
                break;
            case eRNAM:
                RNAM.Read(buffer, subSize, curPos);
                break;
            case eSPLO:
                curFormID = new unsigned int;
                _readBuffer(curFormID,buffer,subSize,curPos);
                SPLO.push_back(curFormID);
                break;
            case eSCRI:
                SCRI.Read(buffer, subSize, curPos);
                break;
            case eCNTO:
                newCNTO = new ReqRecordField<GENCNTO>;
                newCNTO->Read(buffer, subSize, curPos);
                CNTO.push_back(newCNTO);
                break;
            case eAIDT:
                AIDT.Read(buffer, subSize, curPos);
                break;
            case ePKID:
                curFormID = new unsigned int;
                _readBuffer(curFormID, buffer, subSize, curPos);
                PKID.push_back(curFormID);
                break;
            case eKFFZ:
                for(subSize += curPos;curPos < (subSize - 1);curPos += (unsigned int)strlen((char*)&buffer[curPos]) + 1)
                    KFFZ.push_back(STRING((char*)&buffer[curPos]));
                curPos++;
                break;
            case eCNAM:
                CNAM.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eHNAM:
                HNAM.Read(buffer, subSize, curPos);
                break;
            case eLNAM:
                LNAM.Read(buffer, subSize, curPos);
                break;
            case eENAM:
                ENAM.Read(buffer, subSize, curPos);
                break;
            case eHCLR:
                HCLR.Read(buffer, subSize, curPos);
                break;
            case eZNAM:
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case eFGGS:
                FGGS.Read(buffer, subSize, curPos);
                break;
            case eFGGA:
                FGGA.Read(buffer, subSize, curPos);
                break;
            case eFGTS:
                FGTS.Read(buffer, subSize, curPos);
                break;
            case eFNAM:
                FNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  NPC_: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;

            }
        }
    return 0;
    }

unsigned int NPC_Record::GetSize()
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
    if(ACBS.IsLoaded())
        {
        cSize = ACBS.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SNAM.size())
        for(unsigned int p = 0; p < SNAM.size(); p++)
            if(SNAM[p]->IsLoaded())
                {
                cSize = SNAM[p]->GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
    if(INAM.IsLoaded())
        {
        cSize = INAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(RNAM.IsLoaded())
        {
        cSize = RNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SPLO.size())
        TotSize += (unsigned int)SPLO.size() * (sizeof(unsigned int) + 6);
    if(SCRI.IsLoaded())
        {
        cSize = SCRI.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CNTO.size())
        for(unsigned int p = 0; p < CNTO.size(); p++)
            if(CNTO[p]->IsLoaded())
                {
                cSize = CNTO[p]->GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
    if(AIDT.IsLoaded())
        {
        cSize = AIDT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(PKID.size())
        {
        cSize = (unsigned int)PKID.size() * (sizeof(unsigned int) + 6);
        if(cSize > 65535) cSize += 10;
        TotSize += cSize;
        }
    if(KFFZ.size())
        {
        cSize = 1; //Type, size, and final null terminator
        for(unsigned int p = 0; p < KFFZ.size(); p++)
            if(KFFZ[p].IsLoaded())
                cSize += KFFZ[p].GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CNAM.IsLoaded())
        {
        cSize = CNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(HNAM.IsLoaded())
        {
        cSize = HNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(LNAM.IsLoaded())
        {
        cSize = LNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ENAM.IsLoaded())
        {
        cSize = ENAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(HCLR.IsLoaded())
        {
        cSize = HCLR.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ZNAM.IsLoaded())
        {
        cSize = ZNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FGGS.IsLoaded())
        {
        cSize = FGGS.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FGGA.IsLoaded())
        {
        cSize = FGGA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FGTS.IsLoaded())
        {
        cSize = FGTS.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FNAM.IsLoaded())
        {
        cSize = FNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    return TotSize;
    }

int NPC_Record::WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
    {
    unsigned int cSize = 0;
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(FULL.IsLoaded())
        _writeSubRecord(buffer, eFULL, FULL.GetSize(), FULL.value, usedBuffer);
    if(MODL.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MODL.MODL.GetSize(), MODL.MODL.value, usedBuffer);
    if(MODL.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MODL.MODB.GetSize(), &MODL.MODB.value, usedBuffer);
    if(MODL.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MODL.MODT.GetSize(), MODL.MODT.value, usedBuffer);

    if(ACBS.IsLoaded())
        _writeSubRecord(buffer, eACBS, ACBS.GetSize(), &ACBS.value, usedBuffer);
    if(SNAM.size())
        for(unsigned int p = 0; p < SNAM.size(); p++)
            if(SNAM[p]->IsLoaded())
                _writeSubRecord(buffer, eSNAM, SNAM[p]->GetSize(), &SNAM[p]->value, usedBuffer);
    if(INAM.IsLoaded())
        _writeSubRecord(buffer, eINAM, INAM.GetSize(), INAM.value, usedBuffer);
    if(RNAM.IsLoaded())
        _writeSubRecord(buffer, eRNAM, RNAM.GetSize(), RNAM.value, usedBuffer);
    if(SPLO.size())
        for(unsigned int p = 0; p < SPLO.size(); p++)
            _writeSubRecord(buffer, eSPLO, sizeof(unsigned int), SPLO[p], usedBuffer);
    if(SCRI.IsLoaded())
        _writeSubRecord(buffer, eSCRI, SCRI.GetSize(), SCRI.value, usedBuffer);
    if(CNTO.size())
        for(unsigned int p = 0; p < CNTO.size(); p++)
            if(CNTO[p]->IsLoaded())
                _writeSubRecord(buffer, eCNTO, sizeof(GENCNTO), &CNTO[p]->value, usedBuffer);
    if(AIDT.IsLoaded())
        _writeSubRecord(buffer, eAIDT, AIDT.GetSize(), &AIDT.value, usedBuffer);
    if(PKID.size())
        for(unsigned int p = 0; p < PKID.size(); p++)
            _writeSubRecord(buffer, ePKID, sizeof(unsigned int), PKID[p], usedBuffer);
    if(KFFZ.size())
        {
        cSize = 1; //final null terminator
        for(unsigned int p = 0; p < KFFZ.size(); p++)
            if(KFFZ[p].IsLoaded())
                cSize += KFFZ[p].GetSize();
        _writeSubRecord(buffer, eKFFZ, cSize, NULL, usedBuffer);
        for(unsigned int p = 0; p < KFFZ.size(); p++)
            if(KFFZ[p].IsLoaded())
                _writeSubRecord(buffer, NULL, KFFZ[p].GetSize(), KFFZ[p].value, usedBuffer);
        cSize = 0;
        //write final null terminator
        _writeSubRecord(buffer, NULL, 1, &cSize, usedBuffer);
        }
    if(CNAM.IsLoaded())
        _writeSubRecord(buffer, eCNAM, CNAM.GetSize(), &CNAM.value, usedBuffer);
    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    if(HNAM.IsLoaded())
        _writeSubRecord(buffer, eHNAM, HNAM.GetSize(), &HNAM.value, usedBuffer);
    if(LNAM.IsLoaded())
        _writeSubRecord(buffer, eLNAM, LNAM.GetSize(), LNAM.value, usedBuffer);
    if(ENAM.IsLoaded())
        _writeSubRecord(buffer, eENAM, ENAM.GetSize(), ENAM.value, usedBuffer);
    if(HCLR.IsLoaded())
        _writeSubRecord(buffer, eHCLR, HCLR.GetSize(), &HCLR.value, usedBuffer);
    if(ZNAM.IsLoaded())
        _writeSubRecord(buffer, eZNAM, ZNAM.GetSize(), ZNAM.value, usedBuffer);
    if(FGGS.IsLoaded())
        _writeSubRecord(buffer, eFGGS, FGGS.GetSize(), FGGS.value, usedBuffer);
    if(FGGA.IsLoaded())
        _writeSubRecord(buffer, eFGGA, FGGA.GetSize(), FGGA.value, usedBuffer);
    if(FGTS.IsLoaded())
        _writeSubRecord(buffer, eFGTS, FGTS.GetSize(), FGTS.value, usedBuffer);
    if(FNAM.IsLoaded())
        _writeSubRecord(buffer, eFNAM, FNAM.GetSize(), &FNAM.value, usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void NPC_Record::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  NPC_\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    MODL.Debug("MODL", debugLevel, indentation);

    ACBS.Debug("ACBS", debugLevel, indentation);

    if(SNAM.size())
        {
        PrintIndent(indentation);
        printf("SNAM:\n");
        indentation += 2;
        for(unsigned int p = 0;p < SNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            SNAM[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }

    INAM.Debug("INAM", debugLevel, indentation);

    RNAM.Debug("RNAM", debugLevel, indentation);

    if(SPLO.size())
        {
        PrintIndent(indentation);
        printf("SPLO:\n");
        indentation += 2;
        for(unsigned int p = 0;p < SPLO.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(SPLO[p]));
            }
        indentation -= 2;
        }

    SCRI.Debug("SCRI", debugLevel, indentation);

    if(CNTO.size())
        {
        PrintIndent(indentation);
        printf("CNTO:\n");
        indentation += 2;
        for(unsigned int p = 0;p < CNTO.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            CNTO[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }

    AIDT.Debug("AIDT", debugLevel, indentation);

    if(PKID.size())
        {
        PrintIndent(indentation);
        printf("PKID:\n");
        indentation += 2;
        for(unsigned int p = 0;p < PKID.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(PKID[p]));
            }
        indentation -= 2;
        }

    if(KFFZ.size())
        {
        PrintIndent(indentation);
        printf("KFFZ:\n");
        indentation += 2;
        for(unsigned int p = 0;p < KFFZ.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            KFFZ[p].Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }

    CNAM.Debug("CNAM", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

    HNAM.Debug("HNAM", debugLevel, indentation);

    LNAM.Debug("LNAM", debugLevel, indentation);

    ENAM.Debug("ENAM", debugLevel, indentation);

    HCLR.Debug("HCLR", debugLevel, indentation);

    ZNAM.Debug("ZNAM", debugLevel, indentation);

    FGGS.Debug("FGGS", debugLevel, indentation);

    FGGA.Debug("FGGA", debugLevel, indentation);

    FGTS.Debug("FGTS", debugLevel, indentation);

    FNAM.Debug("FNAM", debugLevel, indentation);
    }
#endif
