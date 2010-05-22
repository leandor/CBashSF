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
#include "QUSTRecord.h"
#include <vector>

int QUSTRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    int whichCTDA = 0;
    ReqRecordField<GENCTDA> *newCTDA = NULL;
    std::pair<unsigned int, unsigned int> CTDAFunction;
    std::map<unsigned int, std::pair<unsigned int,unsigned int>>::const_iterator curCTDAFunction;
    QUSTStage *newStage = NULL;
    QUSTEntry *newEntry = NULL;
    QUSTTarget *newTarget = NULL;
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
            case eEDID:
                EDID.Read(buffer, subSize, curPos);
                break;
            case eSCRI:
                SCRI.Read(buffer, subSize, curPos);
                break;
            case eFULL:
                FULL.Read(buffer, subSize, curPos);
                break;
            case eICON:
                ICON.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eCTDT:
            case eCTDA:
                newCTDA = new ReqRecordField<GENCTDA>;
                newCTDA->Read(buffer, subSize, curPos);
                switch(whichCTDA)
                    {
                    case 1:
                        if(newStage == NULL)
                            {
                            newStage = new QUSTStage;
                            Stages.push_back(newStage);
                            }
                        if(newEntry == NULL)
                            {
                            newEntry = new QUSTEntry;
                            newStage->Entries.push_back(newEntry);
                            }
                        newEntry->CTDA.push_back(newCTDA);
                        break;
                    case 2:
                        if(newTarget == NULL)
                            {
                            newTarget = new QUSTTarget;
                            Targets.push_back(newTarget);
                            }
                        newTarget->CTDA.push_back(newCTDA);
                        break;
                    default:
                        CTDA.push_back(newCTDA);
                        break;
                    }
                break;
            case eINDX:
                newStage = new QUSTStage;
                newStage->INDX.Read(buffer, subSize, curPos);
                Stages.push_back(newStage);
                whichCTDA = 1;
                break;
            case eQSDT:
                if(newStage == NULL)
                    {
                    newStage = new QUSTStage;
                    Stages.push_back(newStage);
                    }
                newEntry = new QUSTEntry;
                newEntry->QSDT.Read(buffer, subSize, curPos);
                newStage->Entries.push_back(newEntry);
                break;
            case eCNAM:
                if(newStage == NULL)
                    {
                    newStage = new QUSTStage;
                    Stages.push_back(newStage);
                    }
                if(newEntry == NULL)
                    {
                    newEntry = new QUSTEntry;
                    newStage->Entries.push_back(newEntry);
                    }
                newEntry->CNAM.Read(buffer, subSize, curPos);
                break;
            case eSCHR:
                if(newStage == NULL)
                    {
                    newStage = new QUSTStage;
                    Stages.push_back(newStage);
                    }
                if(newEntry == NULL)
                    {
                    newEntry = new QUSTEntry;
                    newStage->Entries.push_back(newEntry);
                    }
                newEntry->SCHR.Read(buffer, subSize, curPos);
                break;
            case eSCDA:
                if(newStage == NULL)
                    {
                    newStage = new QUSTStage;
                    Stages.push_back(newStage);
                    }
                if(newEntry == NULL)
                    {
                    newEntry = new QUSTEntry;
                    newStage->Entries.push_back(newEntry);
                    }
                newEntry->SCDA.Read(buffer, subSize, curPos);
                break;
            case eSCTX:
                if(newStage == NULL)
                    {
                    newStage = new QUSTStage;
                    Stages.push_back(newStage);
                    }
                if(newEntry == NULL)
                    {
                    newEntry = new QUSTEntry;
                    newStage->Entries.push_back(newEntry);
                    }
                newEntry->SCTX.Read(buffer, subSize, curPos);
                break;
            case eSCRV:
                if(newStage == NULL)
                    {
                    newStage = new QUSTStage;
                    Stages.push_back(newStage);
                    }
                if(newEntry == NULL)
                    {
                    newEntry = new QUSTEntry;
                    newStage->Entries.push_back(newEntry);
                    }
                newSCR_ = new ReqRecordField<GENSCR_>;
                newSCR_->Read(buffer, subSize, curPos);
                newSCR_->value.isSCRO = false;
                newEntry->SCR_.push_back(newSCR_);
                break;
            case eSCRO:
                if(newStage == NULL)
                    {
                    newStage = new QUSTStage;
                    Stages.push_back(newStage);
                    }
                if(newEntry == NULL)
                    {
                    newEntry = new QUSTEntry;
                    newStage->Entries.push_back(newEntry);
                    }
                newSCR_ = new ReqRecordField<GENSCR_>;
                newSCR_->Read(buffer, subSize, curPos);
                newSCR_->value.isSCRO = true;
                newEntry->SCR_.push_back(newSCR_);
                break;
            case eQSTA:
                newTarget = new QUSTTarget;
                newTarget->QSTA.Read(buffer, subSize, curPos);
                Targets.push_back(newTarget);
                whichCTDA = 2;
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  QUST: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int QUSTRecord::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SCRI.IsLoaded())
        {
        cSize = SCRI.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FULL.IsLoaded())
        {
        cSize = FULL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
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
    if(Stages.size())
        for(unsigned int p = 0; p < Stages.size(); p++)
            {
            if(Stages[p]->INDX.IsLoaded())
                {
                cSize = Stages[p]->INDX.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(Stages[p]->Entries.size())
                for(unsigned int x = 0; x < Stages[p]->Entries.size(); x++)
                    {
                    if(Stages[p]->Entries[x]->QSDT.IsLoaded())
                        {
                        cSize = Stages[p]->Entries[x]->QSDT.GetSize();
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    if(Stages[p]->Entries[x]->CTDA.size())
                        for(unsigned int y = 0; y < Stages[p]->Entries[x]->CTDA.size(); y++)
                            if(Stages[p]->Entries[x]->CTDA[y]->IsLoaded())
                                {
                                cSize = Stages[p]->Entries[x]->CTDA[y]->GetSize();
                                if(cSize > 65535) cSize += 10;
                                TotSize += cSize += 6;
                                }
                    if(Stages[p]->Entries[x]->CNAM.IsLoaded())
                        {
                        cSize = Stages[p]->Entries[x]->CNAM.GetSize();
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    if(Stages[p]->Entries[x]->SCHR.IsLoaded())
                        {
                        cSize = Stages[p]->Entries[x]->SCHR.GetSize();
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    if(Stages[p]->Entries[x]->SCDA.IsLoaded())
                        {
                        cSize = Stages[p]->Entries[x]->SCDA.GetSize();
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    if(Stages[p]->Entries[x]->SCTX.IsLoaded())
                        {
                        cSize = Stages[p]->Entries[x]->SCTX.GetSize();
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    TotSize += (sizeof(unsigned int) + 6) * (unsigned int)Stages[p]->Entries[x]->SCR_.size();
                    }
            }
    if(Targets.size())
        for(unsigned int p = 0; p < Targets.size(); p++)
            {
            if(Targets[p]->QSTA.IsLoaded())
                {
                cSize = Targets[p]->QSTA.GetSize();
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            if(Targets[p]->CTDA.size())
                for(unsigned int y = 0; y < Targets[p]->CTDA.size(); y++)
                    if(Targets[p]->CTDA[y]->IsLoaded())
                        {
                        cSize = Targets[p]->CTDA[y]->GetSize();
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
            }
    return TotSize;
    }

int QUSTRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(SCRI.IsLoaded())
        _writeSubRecord(buffer, eSCRI, SCRI.GetSize(), SCRI.value, usedBuffer);
    if(FULL.IsLoaded())
        _writeSubRecord(buffer, eFULL, FULL.GetSize(), FULL.value, usedBuffer);
    if(ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, ICON.GetSize(), ICON.value, usedBuffer);
    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    if(CTDA.size())
        for(unsigned int p = 0; p < CTDA.size(); p++)
            if(CTDA[p]->IsLoaded())
                _writeSubRecord(buffer, eCTDA, CTDA[p]->GetSize(), &CTDA[p]->value, usedBuffer);
    if(Stages.size())
        for(unsigned int p = 0; p < Stages.size(); p++)
            {
            if(Stages[p]->INDX.IsLoaded())
                _writeSubRecord(buffer, eINDX, Stages[p]->INDX.GetSize(), &Stages[p]->INDX.value, usedBuffer);
            if(Stages[p]->Entries.size())
                for(unsigned int x = 0; x < Stages[p]->Entries.size(); x++)
                    {
                    if(Stages[p]->Entries[x]->QSDT.IsLoaded())
                        _writeSubRecord(buffer, eQSDT, Stages[p]->Entries[x]->QSDT.GetSize(), &Stages[p]->Entries[x]->QSDT.value, usedBuffer);
                    if(Stages[p]->Entries[x]->CTDA.size())
                        for(unsigned int y = 0; y < Stages[p]->Entries[x]->CTDA.size(); y++)
                            if(Stages[p]->Entries[x]->CTDA[y]->IsLoaded())
                                _writeSubRecord(buffer, eCTDA, Stages[p]->Entries[x]->CTDA[y]->GetSize(), &Stages[p]->Entries[x]->CTDA[y]->value, usedBuffer);
                    if(Stages[p]->Entries[x]->CNAM.IsLoaded())
                        _writeSubRecord(buffer, eCNAM, Stages[p]->Entries[x]->CNAM.GetSize(), Stages[p]->Entries[x]->CNAM.value, usedBuffer);
                    if(Stages[p]->Entries[x]->SCHR.IsLoaded())
                        _writeSubRecord(buffer, eSCHR, Stages[p]->Entries[x]->SCHR.GetSize(), &Stages[p]->Entries[x]->SCHR.value, usedBuffer);
                    if(Stages[p]->Entries[x]->SCDA.IsLoaded())
                        _writeSubRecord(buffer, eSCDA, Stages[p]->Entries[x]->SCDA.GetSize(), Stages[p]->Entries[x]->SCDA.value, usedBuffer);
                    if(Stages[p]->Entries[x]->SCTX.IsLoaded())
                        _writeSubRecord(buffer, eSCTX, Stages[p]->Entries[x]->SCTX.GetSize(), Stages[p]->Entries[x]->SCTX.value, usedBuffer);
                    if(Stages[p]->Entries[x]->SCR_.size())
                        for(unsigned int y = 0; y < Stages[p]->Entries[x]->SCR_.size(); y++)
                            if(Stages[p]->Entries[x]->SCR_[y]->IsLoaded())
                                if(Stages[p]->Entries[x]->SCR_[y]->value.isSCRO)
                                    _writeSubRecord(buffer, eSCRO, sizeof(unsigned int), &Stages[p]->Entries[x]->SCR_[y]->value.reference, usedBuffer);
                                else
                                    _writeSubRecord(buffer, eSCRV, sizeof(unsigned int), &Stages[p]->Entries[x]->SCR_[y]->value.reference, usedBuffer);
                    }
            }
    if(Targets.size())
        for(unsigned int p = 0; p < Targets.size(); p++)
            {
            if(Targets[p]->QSTA.IsLoaded())
                _writeSubRecord(buffer, eQSTA, Targets[p]->QSTA.GetSize(), &Targets[p]->QSTA.value, usedBuffer);
            if(Targets[p]->CTDA.size())
                for(unsigned int y = 0; y < Targets[p]->CTDA.size(); y++)
                    if(Targets[p]->CTDA[y]->IsLoaded())
                        _writeSubRecord(buffer, eCTDA, Targets[p]->CTDA[y]->GetSize(), &Targets[p]->CTDA[y]->value, usedBuffer);
            }
    return -1;
    }

#ifdef _DEBUG
void QUSTRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  QUST\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    SCRI.Debug("SCRI", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    ICON.Debug("ICON", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

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

    if(Stages.size())
        {
        PrintIndent(indentation);
        printf("Stages:\n");
        indentation += 2;
        for(unsigned int p = 0;p < Stages.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Stages[p]->Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }

    if(Targets.size())
        {
        PrintIndent(indentation);
        printf("Targets:\n");
        indentation += 2;
        for(unsigned int p = 0;p < Targets.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Targets[p]->Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
