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
#include "TES4Record.h"

int TES4Record::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    STRING curMAST;
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
            case eHEDR:
                HEDR.Read(buffer, subSize, curPos);
                break;
            case eCNAM:
                CNAM.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                SNAM.Read(buffer, subSize, curPos);
                break;
            case eMAST:
                curMAST.Read(buffer, subSize, curPos);
                MAST.push_back(curMAST);
                break;
            case eDATA:
                curPos += subSize;
                break;
            case eOFST:
                OFST.Read(buffer, subSize, curPos);
                break;
            case eDELE:
                DELE.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  TES4: Unknown subType = %04X\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int TES4Record::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(HEDR.IsLoaded())
        {
        cSize = HEDR.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(OFST.IsLoaded())
        {
        cSize = OFST.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DELE.IsLoaded())
        {
        cSize = DELE.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CNAM.IsLoaded())
        {
        cSize = CNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(SNAM.IsLoaded())
        {
        cSize = SNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    for(unsigned int p = 0; p < MAST.size(); p++)
        {
        cSize = MAST[p].GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 20;//accounts for associated DATA element, subTypes and sizes
        }
    return TotSize;
    }

int TES4Record::WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
    {
    TES4DATA DATA;

    _writeSubRecord(buffer, eHEDR, sizeof(TES4HEDR), &HEDR.value, usedBuffer);
    if(OFST.IsLoaded())
        _writeSubRecord(buffer, eOFST, OFST.GetSize(), OFST.value, usedBuffer);
    if(DELE.IsLoaded())
        _writeSubRecord(buffer, eDELE, DELE.GetSize(), DELE.value, usedBuffer);
    if(CNAM.IsLoaded())
        _writeSubRecord(buffer, eCNAM, CNAM.GetSize(), CNAM.value, usedBuffer);
    if(SNAM.IsLoaded())
        _writeSubRecord(buffer, eSNAM, SNAM.GetSize(), SNAM.value, usedBuffer);
    for(unsigned int p = 0; p < MAST.size(); p++)
        {
        _writeSubRecord(buffer, eMAST, MAST[p].GetSize(), MAST[p].value, usedBuffer);
        _writeSubRecord(buffer, eDATA, sizeof(TES4DATA), &DATA, usedBuffer);
        }
    return -1;
    }

#ifdef _DEBUG
void TES4Record::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  TES4\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);
    HEDR.Debug("HEDR", debugLevel, indentation);
    OFST.Debug("OFST", debugLevel, indentation);
    DELE.Debug("DELE", debugLevel, indentation);
    CNAM.Debug("CNAM", debugLevel, indentation);
    SNAM.Debug("SNAM", debugLevel, indentation);
    if(MAST.size())
        {
        PrintIndent(indentation);
        printf("MAST:\n");
        if(debugLevel > 3)
            {
            indentation += 2;
            for(unsigned int p = 0;p < MAST.size();p++)
                {
                PrintIndent(indentation);
                printf("%02x: %s\n", p, MAST[p].value);
                }
            indentation -= 2;
            }
        }
    }
#endif
