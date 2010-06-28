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
    ReqSubRecord<GENSNAM> *newSNAM = NULL;
    ReqSubRecord<GENCNTO> *newCNTO = NULL;
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
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, curPos);
                break;
            case eMODB:
                MODL.Load();
                MODL->MODB.Read(buffer, subSize, curPos);
                break;
            case eMODT:
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, curPos);
                break;
            case eACBS:
                ACBS.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                newSNAM = new ReqSubRecord<GENSNAM>;
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
                newCNTO = new ReqSubRecord<GENCNTO>;
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
                printf("  NPC_: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;

            }
        }
    return 0;
    }

unsigned int NPC_Record::GetSize(bool forceCalc)
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
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        cSize = MODL->MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        if(MODL->MODB.IsLoaded())
            TotSize += MODL->MODB.GetSize() + 6;
        if(MODL->MODT.IsLoaded())
            {
            cSize = MODL->MODT.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }
    if(ACBS.IsLoaded())
        TotSize += ACBS.GetSize() + 6;
    if(SNAM.size())
        for(unsigned int p = 0; p < SNAM.size(); p++)
            if(SNAM[p]->IsLoaded())
                TotSize += SNAM[p]->GetSize() + 6;
    if(INAM.IsLoaded())
        TotSize += INAM.GetSize() + 6;
    if(RNAM.IsLoaded())
        TotSize += RNAM.GetSize() + 6;
    if(SPLO.size())
        TotSize += (unsigned int)SPLO.size() * (sizeof(unsigned int) + 6);
    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;
    if(CNTO.size())
        for(unsigned int p = 0; p < CNTO.size(); p++)
            if(CNTO[p]->IsLoaded())
                TotSize += CNTO[p]->GetSize() + 6;
    if(AIDT.IsLoaded())
        TotSize += AIDT.GetSize() + 6;
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
        TotSize += CNAM.GetSize() + 6;
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(HNAM.IsLoaded())
        TotSize += HNAM.GetSize() + 6;
    if(LNAM.IsLoaded())
        TotSize += LNAM.GetSize() + 6;
    if(ENAM.IsLoaded())
        TotSize += ENAM.GetSize() + 6;
    if(HCLR.IsLoaded())
        TotSize += HCLR.GetSize() + 6;
    if(ZNAM.IsLoaded())
        TotSize += ZNAM.GetSize() + 6;
    if(FGGS.IsLoaded())
        TotSize += FGGS.GetSize() + 6;
    if(FGGA.IsLoaded())
        TotSize += FGGA.GetSize() + 6;
    if(FGTS.IsLoaded())
        TotSize += FGTS.GetSize() + 6;
    if(FNAM.IsLoaded())
        TotSize += FNAM.GetSize() + 6;
    return TotSize;
    }

int NPC_Record::WriteRecord(_FileHandler &SaveHandler)
    {
    unsigned int cSize = 0;
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    if(MODL.IsLoaded() && MODL->MODL.IsLoaded())
        {
        SaveHandler.writeSubRecord(eMODL, MODL->MODL.value, MODL->MODL.GetSize());
        if(MODL->MODB.IsLoaded())
            SaveHandler.writeSubRecord(eMODB, &MODL->MODB.value, MODL->MODB.GetSize());
        if(MODL->MODT.IsLoaded())
            SaveHandler.writeSubRecord(eMODT, MODL->MODT.value, MODL->MODT.GetSize());
        }

    if(ACBS.IsLoaded())
        SaveHandler.writeSubRecord(eACBS, &ACBS.value, ACBS.GetSize());
    if(SNAM.size())
        for(unsigned int p = 0; p < SNAM.size(); p++)
            if(SNAM[p]->IsLoaded())
                SaveHandler.writeSubRecord(eSNAM, &SNAM[p]->value, SNAM[p]->GetSize());
    if(INAM.IsLoaded())
        SaveHandler.writeSubRecord(eINAM, INAM.value, INAM.GetSize());
    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord(eRNAM, RNAM.value, RNAM.GetSize());
    if(SPLO.size())
        for(unsigned int p = 0; p < SPLO.size(); p++)
            SaveHandler.writeSubRecord(eSPLO, SPLO[p], sizeof(unsigned int));
    if(SCRI.IsLoaded())
        SaveHandler.writeSubRecord(eSCRI, SCRI.value, SCRI.GetSize());
    if(CNTO.size())
        for(unsigned int p = 0; p < CNTO.size(); p++)
            if(CNTO[p]->IsLoaded())
                SaveHandler.writeSubRecord(eCNTO, &CNTO[p]->value, sizeof(GENCNTO));
    if(AIDT.IsLoaded())
        SaveHandler.writeSubRecord(eAIDT, &AIDT.value, AIDT.GetSize());
    if(PKID.size())
        for(unsigned int p = 0; p < PKID.size(); p++)
            SaveHandler.writeSubRecord(ePKID, PKID[p], sizeof(unsigned int));
    if(KFFZ.size())
        {
        cSize = 1; //final null terminator
        for(unsigned int p = 0; p < KFFZ.size(); p++)
            if(KFFZ[p].IsLoaded())
                cSize += KFFZ[p].GetSize();
        SaveHandler.writeSubRecord(eKFFZ, NULL, cSize);
        for(unsigned int p = 0; p < KFFZ.size(); p++)
            if(KFFZ[p].IsLoaded())
                SaveHandler.write(KFFZ[p].value, KFFZ[p].GetSize());
        cSize = 0;
        //write final null terminator
        SaveHandler.write(&cSize, 1);
        }
    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord(eCNAM, &CNAM.value, CNAM.GetSize());
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
    if(HNAM.IsLoaded())
        SaveHandler.writeSubRecord(eHNAM, HNAM.value, HNAM.GetSize());
    if(LNAM.IsLoaded())
        SaveHandler.writeSubRecord(eLNAM, LNAM.value, LNAM.GetSize());
    if(ENAM.IsLoaded())
        SaveHandler.writeSubRecord(eENAM, ENAM.value, ENAM.GetSize());
    if(HCLR.IsLoaded())
        SaveHandler.writeSubRecord(eHCLR, &HCLR.value, HCLR.GetSize());
    if(ZNAM.IsLoaded())
        SaveHandler.writeSubRecord(eZNAM, ZNAM.value, ZNAM.GetSize());
    if(FGGS.IsLoaded())
        SaveHandler.writeSubRecord(eFGGS, FGGS.value, FGGS.GetSize());
    if(FGGA.IsLoaded())
        SaveHandler.writeSubRecord(eFGGA, FGGA.value, FGGA.GetSize());
    if(FGTS.IsLoaded())
        SaveHandler.writeSubRecord(eFGTS, FGTS.value, FGTS.GetSize());
    if(FNAM.IsLoaded())
        SaveHandler.writeSubRecord(eFNAM, &FNAM.value, FNAM.GetSize());
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
