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

int REFRRecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    unsigned int curPos = 0;
    unsigned int lastRecord = 0;
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
                        printf("  REFR: Unknown XSED size = %u\n", subSize);
                        printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                        printf("  REFR: Unexpected FULL record\n");
                        printf("  Size = %i\n", subSize);
                        printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                printf("  REFR: Unknown subType = %04x\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int REFRRecord::GetSize()
    {
    unsigned int cSize = 0;
    unsigned int TotSize = 0;

    if(EDID.IsLoaded())
        {
        cSize = EDID.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(NAME.IsLoaded())
        {
        cSize = NAME.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XTEL.IsLoaded())
        {
        cSize = XTEL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XLOC.IsLoaded())
        {
        cSize = XLOC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        cSize = Ownership->XOWN.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        if(Ownership->XRNK.IsLoaded())
            {
            cSize = Ownership->XRNK.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(Ownership->XGLB.IsLoaded())
            {
            cSize = Ownership->XGLB.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(XESP.IsLoaded())
        {
        cSize = XESP.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XTRG.IsLoaded())
        {
        cSize = XTRG.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XSED.IsLoaded())
        if(XSED->isOffset)
            TotSize += 7;
        else TotSize += 10;

    if(XLOD.IsLoaded())
        {
        cSize = XLOD.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XCHG.IsLoaded())
        {
        cSize = XCHG.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XHLT.IsLoaded())
        {
        cSize = XHLT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        {
        cSize = XPCI->XPCI.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        if(XPCI->FULL.IsLoaded())
            {
            cSize = XPCI->FULL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        else TotSize += 7;
        }

    if(XLCM.IsLoaded())
        {
        cSize = XLCM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XRTM.IsLoaded())
        {
        cSize = XRTM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XACT.IsLoaded())
        {
        cSize = XACT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XCNT.IsLoaded())
        {
        cSize = XCNT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(Marker.IsLoaded())
        {
        TotSize += 6;
        if(Marker->FNAM.IsLoaded())
            {
            cSize = Marker->FNAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(Marker->FULL.IsLoaded())
            {
            cSize = Marker->FULL.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        if(Marker->TNAM.IsLoaded())
            {
            cSize = Marker->TNAM.GetSize();
            if(cSize > 65535) cSize += 10;
            TotSize += cSize += 6;
            }
        }

    if(IsOpenByDefault()) //ONAM
        TotSize += 6;

    if(XSCL.IsLoaded())
        {
        cSize = XSCL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(XSOL.IsLoaded())
        {
        cSize = XSOL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

int REFRRecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    char null = 0;

    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);

    if(NAME.IsLoaded())
        _writeSubRecord(buffer, eNAME, NAME.GetSize(), &NAME.value, usedBuffer);

    if(XTEL.IsLoaded())
        _writeSubRecord(buffer, eXTEL, XTEL.GetSize(), XTEL.value, usedBuffer);

    if(XLOC.IsLoaded())
        _writeSubRecord(buffer, eXLOC, XLOC.GetSize(), XLOC.value, usedBuffer);

    if(Ownership.IsLoaded() && Ownership->XOWN.IsLoaded())
        {
        _writeSubRecord(buffer, eXOWN, Ownership->XOWN.GetSize(), &Ownership->XOWN.value, usedBuffer);
        if(Ownership->XRNK.IsLoaded())
            _writeSubRecord(buffer, eXRNK, Ownership->XRNK.GetSize(), Ownership->XRNK.value, usedBuffer);
        if(Ownership->XGLB.IsLoaded())
            _writeSubRecord(buffer, eXGLB, Ownership->XGLB.GetSize(), Ownership->XGLB.value, usedBuffer);
        }

    if(XESP.IsLoaded())
        _writeSubRecord(buffer, eXESP, XESP.GetSize(), XESP.value, usedBuffer);

    if(XTRG.IsLoaded())
        _writeSubRecord(buffer, eXTRG, XTRG.GetSize(), XTRG.value, usedBuffer);

    if(XSED.IsLoaded())
        if(XSED->isOffset)
            _writeSubRecord(buffer, eXSED, 1, &XSED->offset, usedBuffer);
        else
            _writeSubRecord(buffer, eXSED, 4, &XSED->seed, usedBuffer);

    if(XLOD.IsLoaded())
        _writeSubRecord(buffer, eXLOD, XLOD.GetSize(), XLOD.value, usedBuffer);

    if(XCHG.IsLoaded())
        _writeSubRecord(buffer, eXCHG, XCHG.GetSize(), XCHG.value, usedBuffer);

    if(XHLT.IsLoaded())
        _writeSubRecord(buffer, eXHLT, XHLT.GetSize(), XHLT.value, usedBuffer);

    if(XPCI.IsLoaded() && XPCI->XPCI.IsLoaded())
        {
        _writeSubRecord(buffer, eXPCI, XPCI->XPCI.GetSize(), XPCI->XPCI.value, usedBuffer);
        if(XPCI->FULL.IsLoaded())
            _writeSubRecord(buffer, eFULL, XPCI->FULL.GetSize(), XPCI->FULL.value, usedBuffer);
        else
            _writeSubRecord(buffer, eFULL, 1, &null, usedBuffer);
        }

    if(XLCM.IsLoaded())
        _writeSubRecord(buffer, eXLCM, XLCM.GetSize(), XLCM.value, usedBuffer);

    if(XRTM.IsLoaded())
        _writeSubRecord(buffer, eXRTM, XRTM.GetSize(), XRTM.value, usedBuffer);

    if(XACT.IsLoaded())
        _writeSubRecord(buffer, eXACT, XACT.GetSize(), XACT.value, usedBuffer);

    if(XCNT.IsLoaded())
        _writeSubRecord(buffer, eXCNT, XCNT.GetSize(), XCNT.value, usedBuffer);

    if(Marker.IsLoaded())
        {
        _writeSubRecord(buffer, eXMRK, 0, NULL, usedBuffer);
        if(Marker->FNAM.IsLoaded())
            _writeSubRecord(buffer, eFNAM, Marker->FNAM.GetSize(), &Marker->FNAM.value, usedBuffer);
        if(Marker->FULL.IsLoaded())
            _writeSubRecord(buffer, eFULL, Marker->FULL.GetSize(), Marker->FULL.value, usedBuffer);
        if(Marker->TNAM.IsLoaded())
            _writeSubRecord(buffer, eTNAM, Marker->TNAM.GetSize(), &Marker->TNAM.value, usedBuffer);
        }

    if(IsOpenByDefault()) //ONAM
        _writeSubRecord(buffer, eONAM, 0, NULL, usedBuffer);

    if(XSCL.IsLoaded())
        _writeSubRecord(buffer, eXSCL, XSCL.GetSize(), XSCL.value, usedBuffer);

    if(XSOL.IsLoaded())
        _writeSubRecord(buffer, eXSOL, XSOL.GetSize(), XSOL.value, usedBuffer);

    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);

    return -1;
    }

#ifdef _DEBUG
void REFRRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
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
