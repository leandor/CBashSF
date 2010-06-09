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
#include "CELLRecord.h"
#include <vector>

int CELLRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    FormID curFormID = NULL;
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
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eXCLL:
                XCLL.Read(buffer, subSize, curPos);
                break;
            case eXCMT:
                XCMT.Read(buffer, subSize, curPos);
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
            case eXCCM:
                XCCM.Read(buffer, subSize, curPos);
                break;
            case eXCLW:
                XCLW.Read(buffer, subSize, curPos);
                break;
            case eXCLR:
                if(subSize % sizeof(unsigned int) == 0)
                    {
                    if(subSize == 0)
                        break;
                    XCLR.resize(subSize / sizeof(unsigned int));
                    _readBuffer(&XCLR[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized XCLR size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eXCLC:
                XCLC.Read(buffer, subSize, curPos);
                break;
            case eXCWT:
                XCWT.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CELL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int CELLRecord::GetSize(bool forceCalc)
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
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(XCLL.IsLoaded())
        TotSize += XCLL.GetSize() + 6;
    if(XCMT.IsLoaded())
        TotSize += XCMT.GetSize() + 6;

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        TotSize += Ownership->XOWN.GetSize() + 6;
        if(Ownership->XRNK.IsLoaded())
            TotSize += Ownership->XRNK.GetSize() + 6;
        if(Ownership->XGLB.IsLoaded())
            TotSize += Ownership->XGLB.GetSize() + 6;
        }

    if(XCCM.IsLoaded())
        TotSize += XCCM.GetSize() + 6;
    if(XCLW.IsLoaded())
        TotSize += XCLW.GetSize() + 6;

    if(XCLR.size())
        {
        cSize = (sizeof(unsigned int) * (unsigned int)XCLR.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XCLC.IsLoaded() && !IsInterior())
        TotSize += XCLC.GetSize() + 6;
    if(XCWT.IsLoaded())
        TotSize += XCWT.GetSize() + 6;
    return TotSize;
    }

int CELLRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());

    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
    if(XCLL.IsLoaded())
        SaveHandler.writeSubRecord(eXCLL, XCLL.value, XCLL.GetSize());
    if(XCMT.IsLoaded())
        SaveHandler.writeSubRecord(eXCMT, &XCMT.value, XCMT.GetSize());

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        SaveHandler.writeSubRecord(eXOWN, &Ownership->XOWN.value, Ownership->XOWN.GetSize());
        if(Ownership->XRNK.IsLoaded())
            SaveHandler.writeSubRecord(eXRNK, Ownership->XRNK.value, Ownership->XRNK.GetSize());
        if(Ownership->XGLB.IsLoaded())
            SaveHandler.writeSubRecord(eXGLB, Ownership->XGLB.value, Ownership->XGLB.GetSize());
        }

    if(XCCM.IsLoaded())
        SaveHandler.writeSubRecord(eXCCM, &XCCM.value, XCCM.GetSize());
    if(XCLW.IsLoaded())
        SaveHandler.writeSubRecord(eXCLW, &XCLW.value, XCLW.GetSize());

    if(XCLR.size())
        SaveHandler.writeSubRecord(eXCLR, &XCLR[0], (unsigned int)XCLR.size() * sizeof(unsigned int));
    //else
    //    SaveHandler.writeSubRecord(eXCLR, NULL, 0);

    if(XCLC.IsLoaded() && !IsInterior())
        SaveHandler.writeSubRecord(eXCLC, &XCLC.value, XCLC.GetSize());
    if(XCWT.IsLoaded())
        SaveHandler.writeSubRecord(eXCWT, &XCWT.value, XCWT.GetSize());
    return -1;
    }

#ifdef _DEBUG
void CELLRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  CELL\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

    XCLL.Debug("XCLL", debugLevel, indentation);

    XCMT.Debug("XCMT", debugLevel, indentation);

    Ownership.Debug("Ownership", debugLevel, indentation);

    XCCM.Debug("XCCM", debugLevel, indentation);

    XCLW.Debug("XCLW", debugLevel, indentation);

    if(XCLR.size())
        {
        PrintIndent(indentation);
        printf("XCLR:\n");
        indentation += 2;
        if(debugLevel > 3)
            for(unsigned int p = 0;p < XCLR.size();p++)
                {
                PrintIndent(indentation);
                printf("%u:%s\n", p, PrintFormID(XCLR[p]));
                }
        indentation -= 2;
        }

    XCLC.Debug("XCLC", debugLevel, indentation);

    XCWT.Debug("XCWT", debugLevel, indentation);

    Persistent.Debug(debugLevel);

    Temporary.Debug(debugLevel);

    VisibleWhenDistant.Debug(debugLevel);

    }
#endif
