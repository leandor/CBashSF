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
#include "INFORecord.h"
#include <vector>

int INFORecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    FormID curFormID = NULL;
    INFOResponse *newResponse = NULL;
    ReqRecordField<GENCTDA> *newCTDA = NULL;
    std::pair<unsigned int, unsigned int> CTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
    ReqRecordField<GENSCR_> *newSCR_ = NULL;
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
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eQSTI:
                QSTI.Read(buffer, subSize, curPos);
                break;
            case eTPIC:
                TPIC.Read(buffer, subSize, curPos);
                break;
            case ePNAM:
                PNAM.Read(buffer, subSize, curPos);
                break;
            case eNAME:
                curFormID = new unsigned int;
                _readBuffer(curFormID,buffer,subSize,curPos);
                NAME.push_back(curFormID);
                break;
            case eTRDT:
                newResponse = new INFOResponse;
                newResponse->TRDT.Read(buffer, subSize, curPos);
                Responses.push_back(newResponse);
                break;
            case eNAM1:
                if(newResponse == NULL)
                    {
                    newResponse = new INFOResponse;
                    Responses.push_back(newResponse);
                    }
                newResponse->NAM1.Read(buffer, subSize, curPos);
                break;
            case eNAM2:
                if(newResponse == NULL)
                    {
                    newResponse = new INFOResponse;
                    Responses.push_back(newResponse);
                    }
                newResponse->NAM2.Read(buffer, subSize, curPos);
                break;
            case eCTDT:
            case eCTDA:
                newCTDA = new ReqRecordField<GENCTDA>;
                newCTDA->Read(buffer, subSize, curPos);
                CTDA.push_back(newCTDA);
                break;
            case eTCLT:
                curFormID = new unsigned int;
                _readBuffer(curFormID,buffer,subSize,curPos);
                TCLT.push_back(curFormID);
                break;
            case eTCLF:
                curFormID = new unsigned int;
                _readBuffer(curFormID,buffer,subSize,curPos);
                TCLF.push_back(curFormID);
                break;
            case eSCHD: //replace it with SCHR. SCHDs are always zero filled in oblivion.esm...
                curPos += subSize;
                break;
            case eSCHR: //SCHDs are also larger than SCHRs, so the end will be truncated.
                SCHR.Read(buffer, subSize, curPos);
                break;
            case eSCDA:
                SCDA.Read(buffer, subSize, curPos);
                break;
            case eSCTX:
                SCTX.Read(buffer, subSize, curPos);
                break;
            case eSCRV:
                newSCR_ = new ReqRecordField<GENSCR_>;
                newSCR_->Read(buffer, subSize, curPos);
                newSCR_->value.isSCRO = false;
                SCR_.push_back(newSCR_);
                break;
            case eSCRO:
                newSCR_ = new ReqRecordField<GENSCR_>;
                newSCR_->Read(buffer, subSize, curPos);
                newSCR_->value.isSCRO = true;
                SCR_.push_back(newSCR_);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  INFO: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int INFORecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && recData != NULL)
        return *(unsigned int*)&recData[-16];
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(QSTI.IsLoaded())
        TotSize += QSTI.GetSize() + 6;
    if(TPIC.IsLoaded())
        TotSize += TPIC.GetSize() + 6;
    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;
    if(NAME.size())
        TotSize += (unsigned int)NAME.size() * (sizeof(unsigned int) + 6);

    if(Responses.size())
        {
        for(unsigned int p = 0; p < Responses.size(); p++)
            {
            if(Responses[p]->TRDT.IsLoaded())
                TotSize += Responses[p]->TRDT.GetSize() + 6;
            if(Responses[p]->NAM1.IsLoaded())
                {
                cSize = Responses[p]->NAM1.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(Responses[p]->NAM2.IsLoaded())
                {
                cSize = Responses[p]->NAM2.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            }
        }
    if(CTDA.size())
        for(unsigned int p = 0; p < CTDA.size(); p++)
            if(CTDA[p]->IsLoaded())
                TotSize += CTDA[p]->GetSize() + 6;
    if(TCLT.size())
        TotSize += (unsigned int)TCLT.size() * (sizeof(unsigned int) + 6);
    if(TCLF.size())
        TotSize += (unsigned int)TCLF.size() * (sizeof(unsigned int) + 6);
    //if(SCHD.IsLoaded())
    //    cSize += SCHD.GetSize() + 6;
    if(SCHR.IsLoaded())
        TotSize += SCHR.GetSize() + 6;
    if(SCDA.IsLoaded())
        {
        cSize = SCDA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SCTX.IsLoaded())
        {
        cSize = SCTX.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    TotSize += (sizeof(unsigned int) + 6) * (unsigned int)SCR_.size();
    return TotSize;
    }

int INFORecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    if(QSTI.IsLoaded())
        _writeSubRecord(buffer, eQSTI, QSTI.GetSize(), &QSTI.value, usedBuffer);
    if(TPIC.IsLoaded())
        _writeSubRecord(buffer, eTPIC, TPIC.GetSize(), TPIC.value, usedBuffer);
    if(PNAM.IsLoaded())
        _writeSubRecord(buffer, ePNAM, PNAM.GetSize(), PNAM.value, usedBuffer);
    if(NAME.size())
        for(unsigned int p = 0; p < NAME.size(); p++)
            _writeSubRecord(buffer, eNAME, sizeof(unsigned int), NAME[p], usedBuffer);
    if(Responses.size())
        {
        for(unsigned int p = 0; p < Responses.size(); p++)
            {
            if(Responses[p]->TRDT.IsLoaded())
                _writeSubRecord(buffer, eTRDT, Responses[p]->TRDT.GetSize(), &Responses[p]->TRDT.value, usedBuffer);
            if(Responses[p]->NAM1.IsLoaded())
                _writeSubRecord(buffer, eNAM1, Responses[p]->NAM1.GetSize(), Responses[p]->NAM1.value, usedBuffer);
            if(Responses[p]->NAM2.IsLoaded())
                _writeSubRecord(buffer, eNAM2, Responses[p]->NAM2.GetSize(), Responses[p]->NAM2.value, usedBuffer);
            }
        }
    if(CTDA.size())
        for(unsigned int p = 0; p < CTDA.size(); p++)
            if(CTDA[p]->IsLoaded())
                _writeSubRecord(buffer, eCTDA, CTDA[p]->GetSize(), &CTDA[p]->value, usedBuffer);
    if(TCLT.size())
        for(unsigned int p = 0; p < TCLT.size(); p++)
            _writeSubRecord(buffer, eTCLT, sizeof(unsigned int), TCLT[p], usedBuffer);
    if(TCLF.size())
        for(unsigned int p = 0; p < TCLF.size(); p++)
            _writeSubRecord(buffer, eTCLF, sizeof(unsigned int), TCLF[p], usedBuffer);
    //if(SCHD.IsLoaded())
    //    _writeSubRecord(buffer, eSCHD, SCHD.GetSize(), SCHD.value, usedBuffer);
    if(SCHR.IsLoaded())
        _writeSubRecord(buffer, eSCHR, SCHR.GetSize(), &SCHR.value, usedBuffer);
    if(SCDA.IsLoaded())
        _writeSubRecord(buffer, eSCDA, SCDA.GetSize(), SCDA.value, usedBuffer);
    if(SCTX.IsLoaded())
        _writeSubRecord(buffer, eSCTX, SCTX.GetSize(), SCTX.value, usedBuffer);
    for(unsigned int p = 0; p < SCR_.size(); p++)
        if(SCR_[p]->IsLoaded())
            if(SCR_[p]->value.isSCRO)
                _writeSubRecord(buffer, eSCRO, sizeof(unsigned int), &SCR_[p]->value.reference, usedBuffer);
            else
                _writeSubRecord(buffer, eSCRV, sizeof(unsigned int), &SCR_[p]->value.reference, usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void INFORecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  INFO\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

    QSTI.Debug("QSTI", debugLevel, indentation);

    TPIC.Debug("TPIC", debugLevel, indentation);

    PNAM.Debug("PNAM", debugLevel, indentation);

    if(NAME.size())
        {
        PrintIndent(indentation);
        printf("NAME:\n");
        indentation += 2;
        for(unsigned int p = 0;p < NAME.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(NAME[p]));
            }
        indentation -= 2;
        }

    if(Responses.size())
        {
        PrintIndent(indentation);
        printf("Responses:\n");
        indentation += 2;
        for(unsigned int p = 0;p < Responses.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Responses[p]->Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }

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

    if(TCLT.size())
        {
        PrintIndent(indentation);
        printf("TCLT:\n");
        indentation += 2;
        for(unsigned int p = 0;p < TCLT.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(TCLT[p]));
            }
        indentation -= 2;
        }

    if(TCLF.size())
        {
        PrintIndent(indentation);
        printf("TCLF:\n");
        indentation += 2;
        for(unsigned int p = 0;p < TCLF.size();p++)
            {
            PrintIndent(indentation);
            printf("%u:%s\n", p, PrintFormID(TCLF[p]));
            }
        indentation -= 2;
        }

    SCHD.Debug("SCHD", debugLevel, indentation);

    SCHR.Debug("SCHR", debugLevel, indentation);

    SCDA.Debug("SCDA", debugLevel, indentation);

    SCTX.Debug("SCTX", debugLevel, indentation);

    if(SCR_.size())
        {
        PrintIndent(indentation);
        printf("SCR_:\n");
        indentation += 2;
        for(unsigned int p = 0;p < SCR_.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            SCR_[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
