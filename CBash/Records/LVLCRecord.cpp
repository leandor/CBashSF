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
#include "LVLCRecord.h"
#include <vector>

int LVLCRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    ReqRecordField<LVLLVLO> *newEntry = NULL;
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
            case eLVLD:
                LVLD.Read(buffer, subSize, curPos);
                break;
            case eLVLF:
                LVLF.Read(buffer, subSize, curPos);
                break;
            case eSCRI:
                SCRI.Read(buffer, subSize, curPos);
                break;
            case eTNAM:
                TNAM.Read(buffer, subSize, curPos);
                break;
            case eLVLO:
                newEntry = new ReqRecordField<LVLLVLO>;
                newEntry->Read(buffer, subSize, curPos);
                Entries.push_back(newEntry);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LVL?: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int LVLCRecord::GetSize()
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
    if(LVLD.IsLoaded())
        TotSize += LVLD.GetSize() + 6;
    if(LVLF.IsLoaded())
        TotSize += LVLF.GetSize() + 6;
    if(SCRI.IsLoaded())
        TotSize += SCRI.GetSize() + 6;
    if(TNAM.IsLoaded())
        TotSize += TNAM.GetSize() + 6;
    if(Entries.size())
        for(unsigned int p = 0; p < Entries.size(); p++)
            if(Entries[p]->IsLoaded())
                TotSize += Entries[p]->GetSize() + 6;
    return TotSize;
    }

int LVLCRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(LVLD.IsLoaded())
        _writeSubRecord(buffer, eLVLD, LVLD.GetSize(), &LVLD.value, usedBuffer);
    if(LVLF.IsLoaded())
        _writeSubRecord(buffer, eLVLF, LVLF.GetSize(), &LVLF.value, usedBuffer);
    if(SCRI.IsLoaded())
        _writeSubRecord(buffer, eSCRI, SCRI.GetSize(), SCRI.value, usedBuffer);
    if(TNAM.IsLoaded())
        _writeSubRecord(buffer, eTNAM, TNAM.GetSize(), TNAM.value, usedBuffer);
    if(Entries.size())
        for(unsigned int p = 0; p < Entries.size(); p++)
            if(Entries[p]->IsLoaded())
                _writeSubRecord(buffer, eLVLO, Entries[p]->GetSize(), &Entries[p]->value, usedBuffer);
    return -1;
    }

#ifdef _DEBUG
void LVLCRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    if(Header.Header.type == eLVLC)
        printf("  LVLC\n");
    else if(Header.Header.type == eLVLI)
        printf("  LVLI\n");
    else if(Header.Header.type == eLVSP)
        printf("  LVSP\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    LVLD.Debug("LVLD", debugLevel, indentation);

    LVLF.Debug("LVLF", debugLevel, indentation);

    SCRI.Debug("SCRI", debugLevel, indentation);

    TNAM.Debug("TNAM", debugLevel, indentation);

    if(Entries.size())
        {
        PrintIndent(indentation);
        printf("Entries:\n");
        indentation += 2;
        for(unsigned int p = 0;p < Entries.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            Entries[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }
    }
#endif
