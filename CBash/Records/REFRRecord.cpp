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
#include "REFRRecord.h"

signed long REFRRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned long subType = 0;
    unsigned long subSize = 0;
    unsigned long curPos = 0;
    unsigned long lastRecord = 0;
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
            case eNAME:
                NAME.Read(buffer, subSize, curPos);
                break;
            case eXTEL:
                XTEL.Read(buffer, subSize, curPos);
                break;
            case eXLOC:
                switch(subSize)
                    {
                    case 12: //unused2 is absent, so shift the values read into it
                        XLOC.Read(buffer, subSize, curPos);
                        XLOC->flags = XLOC->unused2[0];
                        XLOC->unused3[0] = XLOC->unused2[1];
                        XLOC->unused3[1] = XLOC->unused2[2];
                        XLOC->unused3[2] = XLOC->unused2[3];
                        memset(&XLOC->unused2[0], 0x00, 4);
                        break;
                    default:
                        XLOC.Read(buffer, subSize, curPos);
                        break;
                    }
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
            case eXESP:
                XESP.Read(buffer, subSize, curPos);
                break;
            case eXTRG:
                XTRG.Read(buffer, subSize, curPos);
                break;
            case eXSED:
                switch(subSize)
                    {
                    case 1:
                        //if it's a single byte then it's an offset into the list of seed values in the TREE record
                        XSED.Load();
                        XSED->isOffset = true;
                        //XSED.size = 1;
                        _readBuffer(&XSED->offset, buffer, 1, curPos);
                        break;
                    case 4:
                        //if it's 4 byte it's the seed value directly
                        XSED.Load();
                        XSED->isOffset = false;
                        //XSED.size = 4;
                        _readBuffer(&XSED->seed, buffer, 4, curPos);
                        break;
                    default:
                        printf("  REFR: %08X - Unknown XSED size = %u\n", formID, subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case eXLOD:
                XLOD.Read(buffer, subSize, curPos);
                break;
            case eXCHG:
                XCHG.Read(buffer, subSize, curPos);
                break;
            case eXHLT:
                XHLT.Read(buffer, subSize, curPos);
                break;
            case eXPCI:
                XPCI.Load();
                XPCI->XPCI.Read(buffer, subSize, curPos);
                lastRecord = eXPCI;
                break;
            case eFULL:
                switch(lastRecord)
                    {
                    case eXPCI:
                        XPCI.Load();
                        XPCI->FULL.Read(buffer, subSize, curPos);
                        break;
                    case eXMRK:
                        Marker->FULL.Read(buffer, subSize, curPos);
                        break;
                    default:
                        printf("  REFR: %08X - Unexpected FULL record\n", formID);
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos += subSize;
                        break;
                    }
                break;
            case eXLCM:
                XLCM.Read(buffer, subSize, curPos);
                break;
            case eXRTM:
                XRTM.Read(buffer, subSize, curPos);
                break;
            case eXACT:
                XACT.Read(buffer, subSize, curPos);
                break;
            case eXCNT:
                XCNT.Read(buffer, subSize, curPos);
                break;
            case eXMRK:
                Marker.Load();
                curPos += subSize;
                lastRecord = eXMRK;
                break;
            case eFNAM:
                Marker.Load();
                Marker->FNAM.Read(buffer, subSize, curPos);
                break;
            case eTNAM:
                Marker.Load();
                Marker->TNAM.Read(buffer, subSize, curPos);
                break;
            case eONAM:
                IsOpenByDefault(true);
                curPos += subSize;
                break;
            case eXSCL:
                XSCL.Read(buffer, subSize, curPos);
                break;
            case eXSOL:
                XSOL.Read(buffer, subSize, curPos);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  REFR: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long REFRRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && recData != NULL)
        return *(unsigned long*)&recData[-16];
    unsigned long cSize = 0;
    unsigned long TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAME.IsLoaded())
        TotSize += NAME.GetSize() + 6;

    if(XTEL.IsLoaded())
        TotSize += XTEL.GetSize() + 6;

    if(XLOC.IsLoaded())
        TotSize += XLOC.GetSize() + 6;

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        TotSize += Ownership->XOWN.GetSize() + 6;
        if(Ownership->XRNK.IsLoaded())
            TotSize += Ownership->XRNK.GetSize() + 6;
        if(Ownership->XGLB.IsLoaded())
            TotSize += Ownership->XGLB.GetSize() + 6;
        }

    if(XESP.IsLoaded())
        TotSize += XESP.GetSize() + 6;

    if(XTRG.IsLoaded())
        TotSize += XTRG.GetSize() + 6;

    if(XSED.IsLoaded())
        if(XSED->isOffset)
            TotSize += 7;
        else TotSize += 10;

    if(XLOD.IsLoaded())
        TotSize += XLOD.GetSize() + 6;

    if(XCHG.IsLoaded())
        TotSize += XCHG.GetSize() + 6;

    if(XHLT.IsLoaded())
        TotSize += XHLT.GetSize() + 6;

    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        {
        TotSize += XPCI->XPCI.GetSize() + 6;
        if(XPCI->FULL.IsLoaded())
            {
            cSize = XPCI->FULL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        else TotSize += 7;
        }

    if(XLCM.IsLoaded())
        TotSize += XLCM.GetSize() + 6;

    if(XRTM.IsLoaded())
        TotSize += XRTM.GetSize() + 6;

    if(XACT.IsLoaded())
        TotSize += XACT.GetSize() + 6;

    if(XCNT.IsLoaded())
        TotSize += XCNT.GetSize() + 6;

    if(Marker.IsLoaded())
        {
        TotSize += 6;
        if(Marker->FNAM.IsLoaded())
            TotSize += Marker->FNAM.GetSize() + 6;
        if(Marker->FULL.IsLoaded())
            {
            cSize = Marker->FULL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(Marker->TNAM.IsLoaded())
            TotSize += Marker->TNAM.GetSize() + 6;
        }

    if(IsOpenByDefault()) //ONAM
        TotSize += 6;

    if(XSCL.IsLoaded())
        TotSize += XSCL.GetSize() + 6;

    if(XSOL.IsLoaded())
        TotSize += XSOL.GetSize() + 6;

    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;

    return TotSize;
    }

signed long REFRRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    char null = 0;

    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());

    if(NAME.IsLoaded())
        SaveHandler.writeSubRecord(eNAME, &NAME.value, NAME.GetSize());

    if(XTEL.IsLoaded())
        SaveHandler.writeSubRecord(eXTEL, XTEL.value, XTEL.GetSize());

    if(XLOC.IsLoaded())
        SaveHandler.writeSubRecord(eXLOC, XLOC.value, XLOC.GetSize());

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        SaveHandler.writeSubRecord(eXOWN, &Ownership->XOWN.value, Ownership->XOWN.GetSize());
        if(Ownership->XRNK.IsLoaded())
            SaveHandler.writeSubRecord(eXRNK, Ownership->XRNK.value, Ownership->XRNK.GetSize());
        if(Ownership->XGLB.IsLoaded())
            SaveHandler.writeSubRecord(eXGLB, Ownership->XGLB.value, Ownership->XGLB.GetSize());
        }

    if(XESP.IsLoaded())
        SaveHandler.writeSubRecord(eXESP, XESP.value, XESP.GetSize());

    if(XTRG.IsLoaded())
        SaveHandler.writeSubRecord(eXTRG, XTRG.value, XTRG.GetSize());

    if(XSED.IsLoaded())
        if(XSED->isOffset)
            SaveHandler.writeSubRecord(eXSED, &XSED->offset, 1);
        else
            SaveHandler.writeSubRecord(eXSED, &XSED->seed, 4);

    if(XLOD.IsLoaded())
        SaveHandler.writeSubRecord(eXLOD, XLOD.value, XLOD.GetSize());

    if(XCHG.IsLoaded())
        SaveHandler.writeSubRecord(eXCHG, XCHG.value, XCHG.GetSize());

    if(XHLT.IsLoaded())
        SaveHandler.writeSubRecord(eXHLT, XHLT.value, XHLT.GetSize());

    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        {
        SaveHandler.writeSubRecord(eXPCI, XPCI->XPCI.value, XPCI->XPCI.GetSize());
        if(XPCI->FULL.IsLoaded())
            SaveHandler.writeSubRecord(eFULL, XPCI->FULL.value, XPCI->FULL.GetSize());
        else
            SaveHandler.writeSubRecord(eFULL, &null, 1);
        }

    if(XLCM.IsLoaded())
        SaveHandler.writeSubRecord(eXLCM, XLCM.value, XLCM.GetSize());

    if(XRTM.IsLoaded())
        SaveHandler.writeSubRecord(eXRTM, XRTM.value, XRTM.GetSize());

    if(XACT.IsLoaded())
        SaveHandler.writeSubRecord(eXACT, XACT.value, XACT.GetSize());

    if(XCNT.IsLoaded())
        SaveHandler.writeSubRecord(eXCNT, XCNT.value, XCNT.GetSize());

    if(Marker.IsLoaded())
        {
        SaveHandler.writeSubRecord(eXMRK, NULL, 0);
        if(Marker->FNAM.IsLoaded())
            SaveHandler.writeSubRecord(eFNAM, &Marker->FNAM.value, Marker->FNAM.GetSize());
        if(Marker->FULL.IsLoaded())
            SaveHandler.writeSubRecord(eFULL, Marker->FULL.value, Marker->FULL.GetSize());
        if(Marker->TNAM.IsLoaded())
            SaveHandler.writeSubRecord(eTNAM, &Marker->TNAM.value, Marker->TNAM.GetSize());
        }

    if(IsOpenByDefault()) //ONAM
        SaveHandler.writeSubRecord(eONAM, NULL, 0);

    if(XSCL.IsLoaded())
        SaveHandler.writeSubRecord(eXSCL, XSCL.value, XSCL.GetSize());

    if(XSOL.IsLoaded())
        SaveHandler.writeSubRecord(eXSOL, XSOL.value, XSOL.GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());

    return -1;
    }

#ifdef _DEBUG
void REFRRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
    printf("  REFR\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    NAME.Debug("NAME", debugLevel, indentation);

    XTEL.Debug("XTEL", debugLevel, indentation);

    XLOC.Debug("XLOC", debugLevel, indentation);

    Ownership.Debug("Ownership", debugLevel, indentation);

    XESP.Debug("XESP", debugLevel, indentation);

    XTRG.Debug("XTRG", debugLevel, indentation);

    XSED.Debug("XSED", debugLevel, indentation);

    XLOD.Debug("XLOD", debugLevel, indentation);

    XCHG.Debug("XCHG", debugLevel, indentation);

    XHLT.Debug("XHLT", debugLevel, indentation);

    XPCI.Debug("XPCI", debugLevel, indentation);

    XLCM.Debug("XLCM", debugLevel, indentation);

    XRTM.Debug("XRTM", debugLevel, indentation);

    XACT.Debug("XACT", debugLevel, indentation);

    XCNT.Debug("XCNT", debugLevel, indentation);

    Marker.Debug("Map Marker", debugLevel, indentation);

    XACT.Debug("XACT", debugLevel, indentation);

    XACT.Debug("XACT", debugLevel, indentation);

    if(IsOpenByDefault())
        {
        PrintIndent(indentation);
        printf("ONAM Present\n");
        }

    XSCL.Debug("XSCL", debugLevel, indentation);

    XSOL.Debug("XSOL", debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);
    }
#endif
