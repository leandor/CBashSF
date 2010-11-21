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
#include "PGRDRecord.h"

signed long PGRDRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned long subType = 0;
    unsigned long subSize = 0;
    unsigned long curPos = 0;
    PGRDPGRL *curPGRL = NULL;
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
            case ePGRP:
                if(subSize % sizeof(GENPGRP) == 0)
                    {
                    if(subSize == 0)
                        break;
                    PGRP.resize(subSize / sizeof(GENPGRP));
                    _readBuffer(&PGRP[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized PGRP size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case ePGAG:
                PGAG.Read(buffer, subSize, curPos);
                break;
            case ePGRR:
                PGRR.Read(buffer, subSize, curPos);
                break;
                //if(subSize % sizeof(PGRDPGRR) == 0)
                //    {
                //    if(subSize == 0)
                //        break;
                //    PGRR.resize(subSize / sizeof(PGRDPGRR));
                //    _readBuffer(&PGRR[0], buffer, subSize, curPos);
                //    }
                //else
                //    {
                //    printf("  Unrecognized PGRR size: %i\n", subSize);
                //    curPos += subSize;
                //    }
                //break;
            case ePGRI:
                if(subSize % sizeof(PGRDPGRI) == 0)
                    {
                    if(subSize == 0)
                        break;
                    PGRI.resize(subSize / sizeof(PGRDPGRI));
                    _readBuffer(&PGRI[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized PGRI size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case ePGRL:
                if(subSize % sizeof(unsigned long) == 0)
                    {
                    if(subSize == 0)
                        break;
                    curPGRL = new PGRDPGRL;
                    curPGRL->points.resize(subSize / sizeof(unsigned long));
                    _readBuffer(&curPGRL->points[0], buffer, subSize, curPos);
                    PGRL.push_back(curPGRL);
                    }
                else
                    {
                    printf("  Unrecognized PGRL size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  PGRD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long PGRDRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && recData != NULL)
        return *(unsigned long*)&recData[-16];
    unsigned long cSize = 0;
    unsigned long TotSize = 0;
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(PGRP.size())
        {
        cSize = (sizeof(GENPGRP) * (unsigned long)PGRP.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(PGAG.IsLoaded())
        {
        cSize = PGAG.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(PGRR.IsLoaded())
        {
        cSize = PGRR.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    //if(PGRR.size())
    //    cSize += 6 + (sizeof(PGRDPGRR) * (unsigned long)PGRR.size());
    if(PGRI.size())
        {
        cSize = (sizeof(PGRDPGRI) * (unsigned long)PGRI.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    for(unsigned long x = 0; x < PGRL.size(); ++x)
        {
        cSize = (sizeof(unsigned long) * (unsigned long)PGRL[x]->points.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    return TotSize;
    }

signed long PGRDRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
    if(PGRP.size())
        SaveHandler.writeSubRecord(ePGRP, &PGRP[0], sizeof(GENPGRP) * (unsigned long)PGRP.size());
    if(PGAG.IsLoaded())
        SaveHandler.writeSubRecord(ePGAG, PGAG.value, PGAG.GetSize());
    if(PGRR.IsLoaded())
        SaveHandler.writeSubRecord(ePGRR, PGRR.value, PGRR.GetSize());
    //if(PGRR.size())
    //    SaveHandler.writeSubRecord(ePGRR, &PGRR[0], sizeof(PGRDPGRR) * (unsigned long)PGRR.size());
    if(PGRI.size())
        SaveHandler.writeSubRecord(ePGRI, &PGRI[0], sizeof(PGRDPGRI) * (unsigned long)PGRI.size());
    for(unsigned long x = 0; x < PGRL.size(); ++x)
        SaveHandler.writeSubRecord(ePGRL, &PGRL[x]->points[0], (sizeof(unsigned long) * (unsigned long)PGRL[x]->points.size()));
    return -1;
    }

#ifdef _DEBUG
void PGRDRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
    printf("  PGRD\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

    if(PGRP.size())
        {
        PrintIndent(indentation);
        printf("PGRP:\n");
        indentation += 2;
        for(unsigned long p = 0;p < PGRP.size();p++)
            {
            PrintIndent(indentation);
            PGRP[p].Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }

    PGAG.Debug("PGAG", debugLevel, indentation);

    if(PGRR.size())
        {
        PrintIndent(indentation);
        printf("PGRR:\n");
        indentation += 2;
        for(unsigned long p = 0;p < PGRR.size();p++)
            {
            PrintIndent(indentation);
            PGRR[p].Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }

    if(PGRI.size())
        {
        PrintIndent(indentation);
        printf("PGRI:\n");
        indentation += 2;
        for(unsigned long p = 0;p < PGRI.size();p++)
            {
            PrintIndent(indentation);
            PGRI[p].Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }

    if(PGRL.size())
        {
        PrintIndent(indentation);
        printf("PGRL:\n");
        indentation += 2;
        for(unsigned long p = 0;p < PGRL.size();p++)
            {
            PrintIndent(indentation);
            PGRL[p]->Debug(debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
