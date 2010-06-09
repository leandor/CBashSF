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
#include "CREARecord.h"

int CREARecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
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
    CREASound *newSound = NULL;
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
            case eSPLO:
                curFormID = new unsigned int;
                _readBuffer(curFormID,buffer,subSize,curPos);
                SPLO.push_back(curFormID);
                break;
            case eNIFZ:
                for(subSize += curPos;curPos < (subSize - 1);curPos += (unsigned int)strlen((char*)&buffer[curPos]) + 1)
                    NIFZ.push_back(STRING((char*)&buffer[curPos]));
                curPos++;
                break;
            case eNIFT:
                NIFT.Read(buffer, subSize, curPos);
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
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eRNAM:
                RNAM.Read(buffer, subSize, curPos);
                break;
            case eZNAM:
                ZNAM.Read(buffer, subSize, curPos);
                break;
            case eTNAM:
                TNAM.Read(buffer, subSize, curPos);
                break;
            case eBNAM:
                BNAM.Read(buffer, subSize, curPos);
                break;
            case eWNAM:
                WNAM.Read(buffer, subSize, curPos);
                break;
            case eCSCR:
                CSCR.Read(buffer, subSize, curPos);
                break;
            case eNAM0:
                NAM0.Read(buffer, subSize, curPos);
                break;
            case eNAM1:
                NAM1.Read(buffer, subSize, curPos);
                break;
            case eCSDT:
                newSound = new CREASound;
                newSound->CSDT.Read(buffer, subSize, curPos);
                Sounds.push_back(newSound);
                break;
            case eCSDI:
                if(newSound == NULL)
                    {
                    newSound = new CREASound;
                    Sounds.push_back(newSound);
                    }
                newSound->CSDI.Read(buffer, subSize, curPos);
                break;
            case eCSDC:
                if(newSound == NULL)
                    {
                    newSound = new CREASound;
                    Sounds.push_back(newSound);
                    }
                newSound->CSDC.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CREA: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        }
    return 0;
    }

unsigned int CREARecord::GetSize(bool forceCalc)
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
    if(MODL.MODL.IsLoaded())
        {
        cSize = MODL.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MODL.MODB.IsLoaded())
        TotSize += MODL.MODB.GetSize() + 6;
    if(MODL.MODT.IsLoaded())
        {
        cSize = MODL.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SPLO.size())
        TotSize += (unsigned int)SPLO.size() * (sizeof(unsigned int) + 6);
    if(NIFZ.size())
        {
        cSize = 1; //Type, size, and final null terminator
        for(unsigned int p = 0; p < NIFZ.size(); p++)
            if(NIFZ[p].IsLoaded())
                cSize += NIFZ[p].GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(NIFT.IsLoaded())
        {
        cSize = NIFT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ACBS.IsLoaded())
        TotSize += ACBS.GetSize() + 6;
    if(SNAM.size())
        for(unsigned int p = 0; p < SNAM.size(); p++)
            if(SNAM[p]->IsLoaded())
                TotSize += SNAM[p]->GetSize() + 6;
    if(INAM.IsLoaded())
        TotSize += INAM.GetSize() + 6;
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
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(RNAM.IsLoaded())
        TotSize += RNAM.GetSize() + 6;
    if(ZNAM.IsLoaded())
        TotSize += ZNAM.GetSize() + 6;
    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;
    if(BNAM.IsLoaded())
        TotSize += BNAM.GetSize() + 6;
    if(WNAM.IsLoaded())
        TotSize += WNAM.GetSize() + 6;
    if(CSCR.IsLoaded())
        TotSize += CSCR.GetSize() + 6;
    if(NAM0.IsLoaded())
        {
        cSize = NAM0.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(NAM1.IsLoaded())
        {
        cSize = NAM1.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(Sounds.size())
        for(unsigned int p = 0; p < Sounds.size(); p++)
            {
            if(Sounds[p]->CSDT.IsLoaded())
                TotSize += Sounds[p]->CSDT.GetSize() + 6;
            if(Sounds[p]->CSDI.IsLoaded())
                TotSize += Sounds[p]->CSDI.GetSize() + 6;
            if(Sounds[p]->CSDC.IsLoaded())
                TotSize += Sounds[p]->CSDC.GetSize() + 6;
            }
    return TotSize;
    }

int CREARecord::WriteRecord(_FileHandler &SaveHandler)
    {
    unsigned int cSize = 0;
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    if(MODL.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MODL.MODL.value, MODL.MODL.GetSize());
    if(MODL.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MODL.MODB.value, MODL.MODB.GetSize());
    if(MODL.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MODL.MODT.value, MODL.MODT.GetSize());
    if(SPLO.size())
        for(unsigned int p = 0; p < SPLO.size(); p++)
            SaveHandler.writeSubRecord(eSPLO, SPLO[p], sizeof(unsigned int));
    if(NIFZ.size())
        {
        cSize = 1; //final null terminator
        for(unsigned int p = 0; p < NIFZ.size(); p++)
            if(NIFZ[p].IsLoaded())
                cSize += NIFZ[p].GetSize();
        if(cSize > 65535) cSize += 10;
        SaveHandler.writeSubRecord(eNIFZ, NULL, cSize);
        for(unsigned int p = 0; p < NIFZ.size(); p++)
            if(NIFZ[p].IsLoaded())
                SaveHandler.write(NIFZ[p].value, NIFZ[p].GetSize());
        cSize = 0;
        //write final null terminator
        SaveHandler.write(&cSize, 1);
        }
    if(NIFT.IsLoaded())
        SaveHandler.writeSubRecord(eNIFT, NIFT.value, NIFT.GetSize());
    if(ACBS.IsLoaded())
        SaveHandler.writeSubRecord(eACBS, &ACBS.value, ACBS.GetSize());
    if(SNAM.size())
        for(unsigned int p = 0; p < SNAM.size(); p++)
            if(SNAM[p]->IsLoaded())
                SaveHandler.writeSubRecord(eSNAM, &SNAM[p]->value, SNAM[p]->GetSize());
    if(INAM.IsLoaded())
        SaveHandler.writeSubRecord(eINAM, INAM.value, INAM.GetSize());
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
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
    if(RNAM.IsLoaded())
        SaveHandler.writeSubRecord(eRNAM, &RNAM.value, RNAM.GetSize());
    if(ZNAM.IsLoaded())
        SaveHandler.writeSubRecord(eZNAM, ZNAM.value, ZNAM.GetSize());

    if(TNAM.IsLoaded())
        SaveHandler.writeSubRecord(eTNAM, &TNAM.value, TNAM.GetSize());
    if(BNAM.IsLoaded())
        SaveHandler.writeSubRecord(eBNAM, &BNAM.value, BNAM.GetSize());
    if(WNAM.IsLoaded())
        SaveHandler.writeSubRecord(eWNAM, &WNAM.value, WNAM.GetSize());
    if(CSCR.IsLoaded())
        SaveHandler.writeSubRecord(eCSCR, CSCR.value, CSCR.GetSize());
    if(NAM0.IsLoaded())
        SaveHandler.writeSubRecord(eNAM0, NAM0.value, NAM0.GetSize());
    if(NAM1.IsLoaded())
        SaveHandler.writeSubRecord(eNAM1, NAM1.value, NAM1.GetSize());
    if(Sounds.size())
        for(unsigned int p = 0; p < Sounds.size(); p++)
            {
            if(Sounds[p]->CSDT.IsLoaded())
                SaveHandler.writeSubRecord(eCSDT, &Sounds[p]->CSDT.value, Sounds[p]->CSDT.GetSize());
            if(Sounds[p]->CSDI.IsLoaded())
                SaveHandler.writeSubRecord(eCSDI, &Sounds[p]->CSDI.value, Sounds[p]->CSDI.GetSize());
            if(Sounds[p]->CSDC.IsLoaded())
                SaveHandler.writeSubRecord(eCSDC, &Sounds[p]->CSDC.value, Sounds[p]->CSDC.GetSize());
            }
    return -1;
    }

#ifdef _DEBUG
void CREARecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  CREA\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    MODL.Debug("MODL", debugLevel, indentation);

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

    if(NIFZ.size())
        {
        PrintIndent(indentation);
        printf("NIFZ:\n");
        indentation += 2;
        for(unsigned int p = 0;p < NIFZ.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            NIFZ[p].Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }

    NIFT.Debug("NIFT", debugLevel, indentation);

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

    DATA.Debug("DATA", debugLevel, indentation);

    RNAM.Debug("RNAM", debugLevel, indentation);

    ZNAM.Debug("ZNAM", debugLevel, indentation);

    TNAM.Debug("TNAM", debugLevel, indentation);

    BNAM.Debug("BNAM", debugLevel, indentation);

    WNAM.Debug("WNAM", debugLevel, indentation);

    CSCR.Debug("CSCR", debugLevel, indentation);

    NAM0.Debug("NAM0", debugLevel, indentation);

    NAM1.Debug("NAM1", debugLevel, indentation);

    if(Sounds.size())
        {
        PrintIndent(indentation);
        printf("Sounds:\n");
        indentation += 2;
        for(unsigned int p=0;p < Sounds.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Sounds[p]->Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
