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
#include "SCPTRecord.h"
#include <vector>

int SCPTRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    SCPTVARS *newVARS = NULL;
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
            case eSCHR:
                SCHR.Read(buffer, subSize, curPos);
                break;
            case eSCDA:
                SCDA.Read(buffer, subSize, curPos);
                break;
            case eSCTX:
                SCTX.Read(buffer, subSize, curPos);
                break;
            case eSLSD:
                newVARS = new SCPTVARS;
                newVARS->SLSD.Read(buffer, subSize, curPos);
                VARS.push_back(newVARS);
                break;
            case eSCVR:
                if(newVARS == NULL)
                    {
                    newVARS = new SCPTVARS;
                    VARS.push_back(newVARS);
                    }
                newVARS->SCVR.Read(buffer, subSize, curPos);
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
                printf("  SCPT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int SCPTRecord::GetSize(bool forceCalc)
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
    for(unsigned int p = 0; p < VARS.size(); p++)
        {
        if(VARS[p]->SLSD.IsLoaded())
            TotSize += VARS[p]->SLSD.GetSize() + 6;
        if(VARS[p]->SCVR.IsLoaded())
            {
            cSize = VARS[p]->SCVR.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }
    TotSize += (sizeof(unsigned int) + 6) * (unsigned int)SCR_.size();
    return TotSize;
    }

int SCPTRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(SCHR.IsLoaded())
        SaveHandler.writeSubRecord(eSCHR, &SCHR.value, SCHR.GetSize());
    if(SCDA.IsLoaded())
        SaveHandler.writeSubRecord(eSCDA, SCDA.value, SCDA.GetSize());
    if(SCTX.IsLoaded())
        SaveHandler.writeSubRecord(eSCTX, SCTX.value, SCTX.GetSize());
    for(unsigned int p = 0; p < VARS.size(); p++)
        {
        if(VARS[p]->SLSD.IsLoaded())
            SaveHandler.writeSubRecord(eSLSD, &VARS[p]->SLSD.value, VARS[p]->SLSD.GetSize());
        if(VARS[p]->SCVR.IsLoaded())
            SaveHandler.writeSubRecord(eSCVR, VARS[p]->SCVR.value, VARS[p]->SCVR.GetSize());
        }

    for(unsigned int p = 0; p < SCR_.size(); p++)
        if(SCR_[p]->IsLoaded())
            if(SCR_[p]->value.isSCRO)
                SaveHandler.writeSubRecord(eSCRO, &SCR_[p]->value.reference, sizeof(unsigned int));
            else
                SaveHandler.writeSubRecord(eSCRV, &SCR_[p]->value.reference, sizeof(unsigned int));
    return -1;
    }

#ifdef _DEBUG
void SCPTRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  SCPT\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    SCHR.Debug("SCHR", debugLevel, indentation);

    SCDA.Debug("SCDA", debugLevel, indentation);

    SCTX.Debug("SCTX", debugLevel, indentation);

    if(VARS.size())
        {
        PrintIndent(indentation);
        printf("VARS:\n");
        indentation += 2;
        for(unsigned int p = 0;p < VARS.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            VARS[p]->Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }

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

