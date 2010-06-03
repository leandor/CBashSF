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
#include "REGNRecord.h"
#include <vector>

int REGNRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    REGNArea *newArea = NULL;
    REGNEntry *newEntry = NULL;
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
            case eICON:
                if(newEntry == NULL)
                    ICON.Read(buffer, subSize, curPos);
                else
                    newEntry->ICON.Read(buffer, subSize, curPos);
                break;
            case eRCLR:
                RCLR.Read(buffer, subSize, curPos);
                break;
            case eWNAM:
                WNAM.Read(buffer, subSize, curPos);
                break;
            case eRPLI:
                newArea = new REGNArea;
                newArea->RPLI.Read(buffer, subSize, curPos);
                Areas.push_back(newArea);
                break;
            case eRPLD:
                if(subSize % sizeof(REGNRPLD) == 0)
                    {
                    if(subSize == 0)
                        break;
                    if(newArea == NULL)
                        {
                        newArea = new REGNArea;
                        Areas.push_back(newArea);
                        }
                    newArea->RPLD.resize(subSize / sizeof(REGNRPLD));
                    _readBuffer(&newArea->RPLD[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized RPLD size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eRDAT:
                newEntry = new REGNEntry;
                newEntry->RDAT.Read(buffer, subSize, curPos);
                Entries.push_back(newEntry);
                break;
            case eRDOT:
                if(subSize % sizeof(REGNRDOT) == 0)
                    {
                    if(subSize == 0)
                        break;
                    if(newEntry == NULL)
                        {
                        newEntry = new REGNEntry;
                        Entries.push_back(newEntry);
                        }
                    newEntry->RDOT.resize(subSize / sizeof(REGNRDOT));
                    _readBuffer(&newEntry->RDOT[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized RDOT size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eRDMP:
                if(newEntry == NULL)
                    {
                    newEntry = new REGNEntry;
                    Entries.push_back(newEntry);
                    }
                newEntry->RDMP.Read(buffer, subSize, curPos);
                break;
            case eRDGS:
                if(subSize % sizeof(REGNRDGS) == 0)
                    {
                    if(subSize == 0)
                        break;
                    if(newEntry == NULL)
                        {
                        newEntry = new REGNEntry;
                        Entries.push_back(newEntry);
                        }
                    newEntry->RDGS.resize(subSize / sizeof(REGNRDGS));
                    _readBuffer(&newEntry->RDGS[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized RDOT size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eRDMD:
                if(newEntry == NULL)
                    {
                    newEntry = new REGNEntry;
                    Entries.push_back(newEntry);
                    }
                newEntry->RDMD.Read(buffer, subSize, curPos);
                break;
            case eRDSD:
                if(subSize % sizeof(REGNRDSD) == 0)
                    {
                    if(subSize == 0)
                        break;
                    if(newEntry == NULL)
                        {
                        newEntry = new REGNEntry;
                        Entries.push_back(newEntry);
                        }
                    newEntry->RDSD.resize(subSize / sizeof(REGNRDSD));
                    _readBuffer(&newEntry->RDSD[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized RDSD size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eRDWT:
                if(subSize % sizeof(REGNRDWT) == 0)
                    {
                    if(subSize == 0)
                        break;
                    if(newEntry == NULL)
                        {
                        newEntry = new REGNEntry;
                        Entries.push_back(newEntry);
                        }
                    newEntry->RDWT.resize(subSize / sizeof(REGNRDWT));
                    _readBuffer(&newEntry->RDWT[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized RDWT size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  REGN: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int REGNRecord::GetSize()
    {
    if(recData != NULL)
        return *(unsigned int*)&recData[-16];
    unsigned int cSize = 0;
    unsigned int TotSize = 0;
    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ICON.IsLoaded())
        {
        cSize = ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(RCLR.IsLoaded())
        TotSize += RCLR.GetSize() + 6;
    if(WNAM.IsLoaded())
        TotSize += WNAM.GetSize() + 6;
    if(Areas.size())
        for(unsigned int p = 0; p < Areas.size(); p++)
            {
            if(Areas[p]->RPLI.IsLoaded())
                TotSize += Areas[p]->RPLI.GetSize() + 6;
            if(Areas[p]->RPLD.size())
                {
                cSize = (sizeof(REGNRPLD) * (unsigned int)Areas[p]->RPLD.size());
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            }
    if(Entries.size())
        for(unsigned int p = 0; p < Entries.size(); p++)
            {
            if(Entries[p]->RDAT.IsLoaded())
                TotSize += Entries[p]->RDAT.GetSize() + 6;
            switch(Entries[p]->RDAT.value.entryType)
                {
                case eREGNObjects:
                    TotSize += 6; //RDOT written even if empty
                    if(Entries[p]->RDOT.size())
                        {
                        cSize = (sizeof(REGNRDOT) * (unsigned int)Entries[p]->RDOT.size());
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize;
                        }
                    break;
                case eREGNWeathers:
                    if(Entries[p]->RDWT.size())
                        {
                        cSize = (sizeof(REGNRDWT) * (unsigned int)Entries[p]->RDWT.size());
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    break;
                case eREGNMap:
                    if(Entries[p]->RDMP.IsLoaded())
                        {
                        cSize = Entries[p]->RDMP.GetSize();
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    break;
                case eREGNIcon:
                    if(Entries[p]->ICON.IsLoaded())
                        {
                        cSize = Entries[p]->ICON.GetSize();
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    break;
                case eREGNGrasses:
                    if(Entries[p]->RDGS.size())
                        {
                        cSize = (sizeof(REGNRDGS) * (unsigned int)Entries[p]->RDGS.size());
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize += 6;
                        }
                    break;
                case eREGNSounds:
                    if(Entries[p]->RDMD.IsLoaded())
                        TotSize += Entries[p]->RDMD.GetSize() + 6;
                    TotSize += 6; //RDSD written even if empty
                    if(Entries[p]->RDSD.size())
                        {
                        cSize = (sizeof(REGNRDSD) * (unsigned int)Entries[p]->RDSD.size());
                        if(cSize > 65535) cSize += 10;
                        TotSize += cSize;
                        }
                    break;
                default:
                    printf("!!!%08X: Unknown REGN Entry type: %i, Index:%i!!!\n", formID, Entries[p]->RDAT.value.entryType, p);
                    break;
                }
            }
    return TotSize;
    }

int REGNRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, ICON.GetSize(), ICON.value, usedBuffer);
    if(RCLR.IsLoaded())
        _writeSubRecord(buffer, eRCLR, RCLR.GetSize(), &RCLR.value, usedBuffer);
    if(WNAM.IsLoaded())
        _writeSubRecord(buffer, eWNAM, WNAM.GetSize(), &WNAM.value, usedBuffer);
    if(Areas.size())
        for(unsigned int p = 0; p < Areas.size(); p++)
            {
            if(Areas[p]->RPLI.IsLoaded())
                _writeSubRecord(buffer, eRPLI, Areas[p]->RPLI.GetSize(), &Areas[p]->RPLI.value, usedBuffer);
            if(Areas[p]->RPLD.size())
                _writeSubRecord(buffer, eRPLD, (unsigned int)Areas[p]->RPLD.size() * sizeof(REGNRPLD), &Areas[p]->RPLD[0], usedBuffer);
            //else
            //    _writeSubRecord(buffer, eRPLD, 0, NULL, usedBuffer);
            }
    if(Entries.size())
        for(unsigned int p = 0; p < Entries.size(); p++)
            {
            if(Entries[p]->RDAT.IsLoaded())
                _writeSubRecord(buffer, eRDAT, Entries[p]->RDAT.GetSize(), &Entries[p]->RDAT.value, usedBuffer);
            switch(Entries[p]->RDAT.value.entryType)
                {
                case eREGNObjects:
                    if(Entries[p]->RDOT.size())
                        _writeSubRecord(buffer, eRDOT, (unsigned int)Entries[p]->RDOT.size() * sizeof(REGNRDOT), &Entries[p]->RDOT[0], usedBuffer);
                    else
                        _writeSubRecord(buffer, eRDOT, 0, NULL, usedBuffer);
                    break;
                case eREGNWeathers:
                    if(Entries[p]->RDWT.size())
                        _writeSubRecord(buffer, eRDWT, (unsigned int)Entries[p]->RDWT.size() * sizeof(REGNRDWT), &Entries[p]->RDWT[0], usedBuffer);
                    //else
                    //    _writeSubRecord(buffer, eRDWT, 0, NULL, usedBuffer);
                    break;
                case eREGNMap:
                    if(Entries[p]->RDMP.IsLoaded())
                        _writeSubRecord(buffer, eRDMP, Entries[p]->RDMP.GetSize(), Entries[p]->RDMP.value, usedBuffer);
                    break;
                case eREGNIcon:
                    if(Entries[p]->ICON.IsLoaded())
                        _writeSubRecord(buffer, eICON, Entries[p]->ICON.GetSize(), Entries[p]->ICON.value, usedBuffer);
                    break;
                case eREGNGrasses:
                    if(Entries[p]->RDGS.size())
                        _writeSubRecord(buffer, eRDGS, (unsigned int)Entries[p]->RDGS.size() * sizeof(REGNRDGS), &Entries[p]->RDGS[0], usedBuffer);
                    //else
                    //    _writeSubRecord(buffer, eRDGS, 0, NULL, usedBuffer);
                    break;
                case eREGNSounds:
                    if(Entries[p]->RDMD.IsLoaded())
                        _writeSubRecord(buffer, eRDMD, Entries[p]->RDMD.GetSize(), Entries[p]->RDMD.value, usedBuffer);
                    if(Entries[p]->RDSD.size())
                        _writeSubRecord(buffer, eRDSD, (unsigned int)Entries[p]->RDSD.size() * sizeof(REGNRDSD), &Entries[p]->RDSD[0], usedBuffer);
                    else
                        _writeSubRecord(buffer, eRDSD, 0, NULL, usedBuffer);
                    break;
                default:
                    printf("!!!%08X: Unknown REGN Entry type: %i, Index:%i!!!\n", formID, Entries[p]->RDAT.value.entryType, p);
                    break;
                }
            }
    return -1;
    }

#ifdef _DEBUG
void REGNRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  REGN\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    ICON.Debug("ICON", debugLevel, indentation);

    RCLR.Debug("RCLR", debugLevel, indentation);

    WNAM.Debug("WNAM", debugLevel, indentation);

    if(Areas.size())
        {
        PrintIndent(indentation);
        printf("Areas:\n");
        indentation += 2;
        for(unsigned int p = 0;p < Areas.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Areas[p]->RPLI.Debug("RPLI", debugLevel, indentation);
            if(Areas[p]->RPLD.size())
                {
                PrintIndent(indentation);
                printf("RPLD:\n");
                indentation += 2;
                for(unsigned int x = 0;x < Areas[p]->RPLD.size();x++)
                    {
                    PrintIndent(indentation);
                    printf("Index: %u\n", p);
                    Areas[p]->RPLD[x].Debug(debugLevel, indentation);
                    }
                indentation -= 2;
                }
            }
        indentation -= 2;
        }

    if(Entries.size())
        {
        PrintIndent(indentation);
        printf("Entries:\n");
        indentation += 2;
        for(unsigned int p = 0;p < Entries.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Entries[p]->Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
