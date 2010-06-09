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
#include "RACERecord.h"
#include <vector>

int RACERecord::ParseRecord(unsigned char *buffer, const unsigned int &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned int subType = 0;
    unsigned int subSize = 0;
    int curNAM = -1;
    int curINDX = -1;
    unsigned int curPos = 0;
    FormID curFormID = NULL;
    ReqRecordField<GENXNAM> *newXNAM = NULL;
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
            case eDESC:
                DESC.Read(buffer, subSize, curPos);
                break;
            case eSPLO:
                curFormID = new unsigned int;
                _readBuffer(curFormID,buffer,subSize,curPos);
                SPLO.push_back(curFormID);
                break;
            case eXNAM:
                newXNAM = new ReqRecordField<GENXNAM>;
                newXNAM->Read(buffer, subSize, curPos);
                XNAM.push_back(newXNAM);
                break;
            case eDATA:
                DATA.Read(buffer, subSize, curPos);
                break;
            case eVNAM:
                if(VNAM.Read(buffer, subSize, curPos))
                    {
                    if(formID == VNAM.value.maleVoice)
                        VNAM.value.maleVoice = 0;
                    if(formID == VNAM.value.femaleVoice)
                        VNAM.value.femaleVoice = 0;
                    }
                break;
            case eDNAM:
                DNAM.Read(buffer, subSize, curPos);
                break;
            case eCNAM:
                CNAM.Read(buffer, subSize, curPos);
                break;
            case ePNAM:
                PNAM.Read(buffer, subSize, curPos);
                break;
            case eUNAM:
                UNAM.Read(buffer, subSize, curPos);
                break;
            case eATTR:
                ATTR.Read(buffer, subSize, curPos);
                break;
            case eNAM0:
                curNAM = 0;
                curINDX = -1;
                break;
            case eNAM1:
                curNAM = 1;
                break;
            case eINDX:
                _readBuffer(&curINDX,buffer,subSize,curPos);
                break;
            case eMNAM:
                curNAM = 2;
                curINDX = -1;
                break;
            case eFNAM:
                curNAM = 3;
                curINDX = -1;
                break;
            case eMODL:
                switch(curNAM)
                    {
                    case 0:
                        switch(curINDX)
                            {
                            case 0:
                                MOD0.MODL.Read(buffer, subSize, curPos);
                                break;
                            case 1:
                                MOD1.MODL.Read(buffer, subSize, curPos);
                                break;
                            case 2:
                                MOD2.MODL.Read(buffer, subSize, curPos);
                                break;
                            case 3:
                                MOD3.MODL.Read(buffer, subSize, curPos);
                                break;
                            case 4:
                                MOD4.MODL.Read(buffer, subSize, curPos);
                                break;
                            case 5:
                                MOD5.MODL.Read(buffer, subSize, curPos);
                                break;
                            case 6:
                                MOD6.MODL.Read(buffer, subSize, curPos);
                                break;
                            case 7:
                                MOD7.MODL.Read(buffer, subSize, curPos);
                                break;
                            case 8:
                                MOD8.MODL.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected INDX %I under NAM%01I: %i\n", formID, curINDX, curNAM);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        MMODL.MODL.Read(buffer, subSize, curPos);
                        break;
                    case 3:
                        FMODL.MODL.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected NAM%01I: %i\n", formID, curNAM);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case eICON:
                switch(curNAM)
                    {
                    case 0:
                        switch(curINDX)
                            {
                            case 0:
                                MOD0.ICON.Read(buffer, subSize, curPos);
                                break;
                            case 1:
                                MOD1.ICON.Read(buffer, subSize, curPos);
                                break;
                            case 2:
                                MOD2.ICON.Read(buffer, subSize, curPos);
                                break;
                            case 3:
                                MOD3.ICON.Read(buffer, subSize, curPos);
                                break;
                            case 4:
                                MOD4.ICON.Read(buffer, subSize, curPos);
                                break;
                            case 5:
                                MOD5.ICON.Read(buffer, subSize, curPos);
                                break;
                            case 6:
                                MOD6.ICON.Read(buffer, subSize, curPos);
                                break;
                            case 7:
                                MOD7.ICON.Read(buffer, subSize, curPos);
                                break;
                            case 8:
                                MOD8.ICON.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected INDX %I under NAM%01I: %i\n", formID, curINDX, curNAM);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        switch(curINDX)
                            {
                            case 0:
                                MICON0.Read(buffer, subSize, curPos);
                                break;
                            case 1:
                                MICON1.Read(buffer, subSize, curPos);
                                break;
                            case 2:
                                MICON2.Read(buffer, subSize, curPos);
                                break;
                            case 3:
                                MICON3.Read(buffer, subSize, curPos);
                                break;
                            case 4:
                                MICON4.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON under NAM%01I: %i\n", formID, curNAM);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 3:
                        switch(curINDX)
                            {
                            case 0:
                                FICON0.Read(buffer, subSize, curPos);
                                break;
                            case 1:
                                FICON1.Read(buffer, subSize, curPos);
                                break;
                            case 2:
                                FICON2.Read(buffer, subSize, curPos);
                                break;
                            case 3:
                                FICON3.Read(buffer, subSize, curPos);
                                break;
                            case 4:
                                FICON4.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected ICON under NAM%01i: indx = %i\n", formID, curNAM, curINDX);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected ICON under NAM%01i\n", formID, curNAM);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case eMODB:
                switch(curNAM)
                    {
                    case 0:
                        switch(curINDX)
                            {
                            case 0:
                                MOD0.MODB.Read(buffer, subSize, curPos);
                                break;
                            case 1:
                                MOD1.MODB.Read(buffer, subSize, curPos);
                                break;
                            case 2:
                                MOD2.MODB.Read(buffer, subSize, curPos);
                                break;
                            case 3:
                                MOD3.MODB.Read(buffer, subSize, curPos);
                                break;
                            case 4:
                                MOD4.MODB.Read(buffer, subSize, curPos);
                                break;
                            case 5:
                                MOD5.MODB.Read(buffer, subSize, curPos);
                                break;
                            case 6:
                                MOD6.MODB.Read(buffer, subSize, curPos);
                                break;
                            case 7:
                                MOD7.MODB.Read(buffer, subSize, curPos);
                                break;
                            case 8:
                                MOD8.MODB.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected INDX %I under NAM%01I: %i\n", formID, curINDX, curNAM);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        MMODL.MODB.Read(buffer, subSize, curPos);
                        break;
                     case 3:
                        FMODL.MODB.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected MODB under NAM%01I: %i\n", formID, curNAM);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case eMODT:
                switch(curNAM)
                    {
                    case 0:
                        switch(curINDX)
                            {
                            case 0:
                                MOD0.MODT.Read(buffer, subSize, curPos);
                                break;
                            case 1:
                                MOD1.MODT.Read(buffer, subSize, curPos);
                                break;
                            case 2:
                                MOD2.MODT.Read(buffer, subSize, curPos);
                                break;
                            case 3:
                                MOD3.MODT.Read(buffer, subSize, curPos);
                                break;
                            case 4:
                                MOD4.MODT.Read(buffer, subSize, curPos);
                                break;
                            case 5:
                                MOD5.MODT.Read(buffer, subSize, curPos);
                                break;
                            case 6:
                                MOD6.MODT.Read(buffer, subSize, curPos);
                                break;
                            case 7:
                                MOD7.MODT.Read(buffer, subSize, curPos);
                                break;
                            case 8:
                                MOD8.MODT.Read(buffer, subSize, curPos);
                                break;
                            default:
                                //ERROR
                                //printf("FileName = %s\n", FileName);
                                printf("  RACE: %08X - Unexpected INDX %I under NAM%01I: %i\n", formID, curINDX, curNAM);
                                printf("  CurPos = %04x\n\n", curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    case 2:
                        MMODL.MODT.Read(buffer, subSize, curPos);
                        break;
                    case 3:
                        FMODL.MODT.Read(buffer, subSize, curPos);
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: %08X - Unexpected MODT under NAM%01I: %i\n", formID, curNAM);
                        printf("  CurPos = %04x\n\n", curPos - 6);
                        curPos = recSize;
                        break;
                    }
                break;
            case eHNAM:
                if(subSize % sizeof(unsigned int) == 0)
                    {
                    if(subSize == 0)
                        break;
                    HNAM.resize(subSize / sizeof(unsigned int));
                    _readBuffer(&HNAM[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized HNAM size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eENAM:
                if(subSize % sizeof(unsigned int) == 0)
                    {
                    if(subSize == 0)
                        break;
                    ENAM.resize(subSize / sizeof(unsigned int));
                    _readBuffer(&ENAM[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized ENAM size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            case eFGGS:
                FGGS.Read(buffer, subSize, curPos);
                break;
            case eFGGA:
                FGGA.Read(buffer, subSize, curPos);
                break;
            case eFGTS:
                FGTS.Read(buffer, subSize, curPos);
                break;
            case eSNAM:
                SNAM.Read(buffer, subSize, curPos);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  RACE: Unknown subType = %04X\n", subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int RACERecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && recData != NULL)
        return *(unsigned int*)&recData[-16];
    unsigned int cSize = 0;
    unsigned int TotSize = 226;
    //TotSize += 96; //NAM0, INDX 0, INDX 1, INDX 2, INDX 3, INDX 4, INDX 5, INDX 6, INDX 7, INDX 8
    //TotSize += 62; //NAM1, MNAM, INDX 0, INDX 1, INDX 2, INDX 3, INDX 4
    //TotSize += 56; //FNAM, INDX 0, INDX 1, INDX 2, INDX 3, INDX 4
    //TotSize += 6; //ENAM, written even if empty
    //TotSize += 6; //HNAM, written even if empty
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
    if(DESC.IsLoaded())
        {
        cSize = DESC.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SPLO.size())
        TotSize += (unsigned int)SPLO.size() * (sizeof(unsigned int) + 6);

    for(unsigned int p = 0; p < XNAM.size(); p++)
        TotSize += XNAM[p]->GetSize() + 6;
    if(DATA.IsLoaded())
        TotSize += DATA.GetSize() + 6;
    if(VNAM.IsLoaded())
        TotSize += VNAM.GetSize() + 6;
    if(DNAM.IsLoaded())
        TotSize += DNAM.GetSize() + 6;
    if(CNAM.IsLoaded())
        TotSize += CNAM.GetSize() + 6;
    if(PNAM.IsLoaded())
        TotSize += PNAM.GetSize() + 6;
    if(UNAM.IsLoaded())
        TotSize += UNAM.GetSize() + 6;
    if(ATTR.IsLoaded())
        TotSize += ATTR.GetSize() + 6;

    if(MOD0.MODL.IsLoaded())
        {
        cSize = MOD0.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD0.MODB.IsLoaded())
        TotSize += MOD0.MODB.GetSize() + 6;
    if(MOD0.MODT.IsLoaded())
        {
        cSize = MOD0.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD0.ICON.IsLoaded())
        {
        cSize = MOD0.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD1.MODL.IsLoaded())
        {
        cSize = MOD1.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD1.MODB.IsLoaded())
        TotSize += MOD1.MODB.GetSize() + 6;
    if(MOD1.MODT.IsLoaded())
        {
        cSize = MOD1.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD1.ICON.IsLoaded())
        {
        cSize = MOD1.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD2.MODL.IsLoaded())
        {
        cSize = MOD2.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD2.MODB.IsLoaded())
        TotSize += MOD2.MODB.GetSize() + 6;
    if(MOD2.MODT.IsLoaded())
        {
        cSize = MOD2.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD2.ICON.IsLoaded())
        {
        cSize = MOD2.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD3.MODL.IsLoaded())
        {
        cSize = MOD3.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD3.MODB.IsLoaded())
        TotSize += MOD3.MODB.GetSize() + 6;
    if(MOD3.MODT.IsLoaded())
        {
        cSize = MOD3.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD3.ICON.IsLoaded())
        {
        cSize = MOD3.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD4.MODL.IsLoaded())
        {
        cSize = MOD4.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD4.MODB.IsLoaded())
        TotSize += MOD4.MODB.GetSize() + 6;
    if(MOD4.MODT.IsLoaded())
        {
        cSize = MOD4.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD4.ICON.IsLoaded())
        {
        cSize = MOD4.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD5.MODL.IsLoaded())
        {
        cSize = MOD5.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD5.MODB.IsLoaded())
        TotSize += MOD5.MODB.GetSize() + 6;
    if(MOD5.MODT.IsLoaded())
        {
        cSize = MOD5.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD5.ICON.IsLoaded())
        {
        cSize = MOD5.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD6.MODL.IsLoaded())
        {
        cSize = MOD6.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD6.MODB.IsLoaded())
        TotSize += MOD6.MODB.GetSize() + 6;
    if(MOD6.MODT.IsLoaded())
        {
        cSize = MOD6.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD6.ICON.IsLoaded())
        {
        cSize = MOD6.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD7.MODL.IsLoaded())
        {
        cSize = MOD7.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD7.MODB.IsLoaded())
        TotSize += MOD7.MODB.GetSize() + 6;
    if(MOD7.MODT.IsLoaded())
        {
        cSize = MOD7.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD7.ICON.IsLoaded())
        {
        cSize = MOD7.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD8.MODL.IsLoaded())
        {
        cSize = MOD8.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD8.MODB.IsLoaded())
        TotSize += MOD8.MODB.GetSize() + 6;
    if(MOD8.MODT.IsLoaded())
        {
        cSize = MOD8.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD8.ICON.IsLoaded())
        {
        cSize = MOD8.ICON.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MMODL.MODL.IsLoaded())
        {
        cSize = MMODL.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MMODL.MODB.IsLoaded())
        TotSize += MMODL.MODB.GetSize() + 6;
    if(MMODL.MODT.IsLoaded())
        {
        cSize = MMODL.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MICON0.IsLoaded())
        {
        cSize = MICON0.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MICON1.IsLoaded())
        {
        cSize = MICON1.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MICON2.IsLoaded())
        {
        cSize = MICON2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MICON3.IsLoaded())
        {
        cSize = MICON3.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MICON4.IsLoaded())
        {
        cSize = MICON4.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FMODL.MODL.IsLoaded())
        {
        cSize = FMODL.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FMODL.MODB.IsLoaded())
        TotSize += FMODL.MODB.GetSize() + 6;
    if(FMODL.MODT.IsLoaded())
        {
        cSize = FMODL.MODT.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(FICON0.IsLoaded())
        {
        cSize = FICON0.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FICON1.IsLoaded())
        {
        cSize = FICON1.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FICON2.IsLoaded())
        {
        cSize = FICON2.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FICON3.IsLoaded())
        {
        cSize = FICON3.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FICON4.IsLoaded())
        {
        cSize = FICON4.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(HNAM.size())
        {
        cSize = (sizeof(unsigned int) * (unsigned int)HNAM.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize;
        }

    if(ENAM.size())
        {
        cSize = (sizeof(unsigned int) * (unsigned int)ENAM.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize;
        }

    if(FGGS.IsLoaded())
        TotSize += FGGS.GetSize() + 6;
    if(FGGA.IsLoaded())
        TotSize += FGGA.GetSize() + 6;
    if(FGTS.IsLoaded())
        TotSize += FGTS.GetSize() + 6;

    if(SNAM.IsLoaded())
        TotSize += SNAM.GetSize() + 6;

    return TotSize;
    }

int RACERecord::WriteRecord(_FileHandler &SaveHandler)
    {
    unsigned int curINDX = 0;
    if(EDID.IsLoaded())
        SaveHandler.writeSubRecord(eEDID, EDID.value, EDID.GetSize());
    if(FULL.IsLoaded())
        SaveHandler.writeSubRecord(eFULL, FULL.value, FULL.GetSize());
    if(DESC.IsLoaded())
        SaveHandler.writeSubRecord(eDESC, DESC.value, DESC.GetSize());

    for(unsigned int p = 0; p < SPLO.size(); p++)
        SaveHandler.writeSubRecord(eSPLO, SPLO[p], sizeof(unsigned int));

    for(unsigned int p = 0; p < XNAM.size(); p++)
        if(XNAM[p]->IsLoaded())
            SaveHandler.writeSubRecord(eXNAM, &XNAM[p]->value, XNAM[p]->GetSize());

    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, &DATA.value, DATA.GetSize());
    if(VNAM.IsLoaded())
        SaveHandler.writeSubRecord(eVNAM, &VNAM.value, VNAM.GetSize());
    if(DNAM.IsLoaded())
        SaveHandler.writeSubRecord(eDNAM, &DNAM.value, DNAM.GetSize());
    if(CNAM.IsLoaded())
        SaveHandler.writeSubRecord(eCNAM, &CNAM.value, CNAM.GetSize());
    if(PNAM.IsLoaded())
        SaveHandler.writeSubRecord(ePNAM, &PNAM.value, PNAM.GetSize());
    if(UNAM.IsLoaded())
        SaveHandler.writeSubRecord(eUNAM, &UNAM.value, UNAM.GetSize());
    if(ATTR.IsLoaded())
        SaveHandler.writeSubRecord(eATTR, &ATTR.value, ATTR.GetSize());

    SaveHandler.writeSubRecord(eNAM0, NULL, 0);

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD0.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD0.MODL.value, MOD0.MODL.GetSize());
    if(MOD0.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD0.MODB.value, MOD0.MODB.GetSize());
    if(MOD0.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD0.MODT.value, MOD0.MODT.GetSize());
    if(MOD0.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD0.ICON.value, MOD0.ICON.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD1.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD1.MODL.value, MOD1.MODL.GetSize());
    if(MOD1.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD1.MODB.value, MOD1.MODB.GetSize());
    if(MOD1.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD1.MODT.value, MOD1.MODT.GetSize());
    if(MOD1.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD1.ICON.value, MOD1.ICON.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD2.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD2.MODL.value, MOD2.MODL.GetSize());
    if(MOD2.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD2.MODB.value, MOD2.MODB.GetSize());
    if(MOD2.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD2.MODT.value, MOD2.MODT.GetSize());
    if(MOD2.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD2.ICON.value, MOD2.ICON.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD3.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD3.MODL.value, MOD3.MODL.GetSize());
    if(MOD3.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD3.MODB.value, MOD3.MODB.GetSize());
    if(MOD3.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD3.MODT.value, MOD3.MODT.GetSize());
    if(MOD3.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD3.ICON.value, MOD3.ICON.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD4.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD4.MODL.value, MOD4.MODL.GetSize());
    if(MOD4.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD4.MODB.value, MOD4.MODB.GetSize());
    if(MOD4.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD4.MODT.value, MOD4.MODT.GetSize());
    if(MOD4.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD4.ICON.value, MOD4.ICON.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD5.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD5.MODL.value, MOD5.MODL.GetSize());
    if(MOD5.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD5.MODB.value, MOD5.MODB.GetSize());
    if(MOD5.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD5.MODT.value, MOD5.MODT.GetSize());
    if(MOD5.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD5.ICON.value, MOD5.ICON.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD6.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD6.MODL.value, MOD6.MODL.GetSize());
    if(MOD6.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD6.MODB.value, MOD6.MODB.GetSize());
    if(MOD6.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD6.MODT.value, MOD6.MODT.GetSize());
    if(MOD6.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD6.ICON.value, MOD6.ICON.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD7.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD7.MODL.value, MOD7.MODL.GetSize());
    if(MOD7.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD7.MODB.value, MOD7.MODB.GetSize());
    if(MOD7.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD7.MODT.value, MOD7.MODT.GetSize());
    if(MOD7.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD7.ICON.value, MOD7.ICON.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MOD8.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MOD8.MODL.value, MOD8.MODL.GetSize());
    if(MOD8.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MOD8.MODB.value, MOD8.MODB.GetSize());
    if(MOD8.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MOD8.MODT.value, MOD8.MODT.GetSize());
    if(MOD8.ICON.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MOD8.ICON.value, MOD8.ICON.GetSize());

    curINDX = 0;
    SaveHandler.writeSubRecord(eNAM1, NULL, 0);
    SaveHandler.writeSubRecord(eMNAM, NULL, 0);
    if(MMODL.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, MMODL.MODL.value, MMODL.MODL.GetSize());
    if(MMODL.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &MMODL.MODB.value, MMODL.MODB.GetSize());
    if(MMODL.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, MMODL.MODT.value, MMODL.MODT.GetSize());

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MICON0.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MICON0.value, MICON0.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MICON1.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MICON1.value, MICON1.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MICON2.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MICON2.value, MICON2.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MICON3.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MICON3.value, MICON3.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(MICON4.IsLoaded())
        SaveHandler.writeSubRecord(eICON, MICON4.value, MICON4.GetSize());

    curINDX = 0;
    SaveHandler.writeSubRecord(eFNAM, NULL, 0);
    if(FMODL.MODL.IsLoaded())
        SaveHandler.writeSubRecord(eMODL, FMODL.MODL.value, FMODL.MODL.GetSize());
    if(FMODL.MODB.IsLoaded())
        SaveHandler.writeSubRecord(eMODB, &FMODL.MODB.value, FMODL.MODB.GetSize());
    if(FMODL.MODT.IsLoaded())
        SaveHandler.writeSubRecord(eMODT, FMODL.MODT.value, FMODL.MODT.GetSize());

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(FICON0.IsLoaded())
        SaveHandler.writeSubRecord(eICON, FICON0.value, FICON0.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(FICON1.IsLoaded())
        SaveHandler.writeSubRecord(eICON, FICON1.value, FICON1.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(FICON2.IsLoaded())
        SaveHandler.writeSubRecord(eICON, FICON2.value, FICON2.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(FICON3.IsLoaded())
        SaveHandler.writeSubRecord(eICON, FICON3.value, FICON3.GetSize());
    curINDX++;

    SaveHandler.writeSubRecord(eINDX, &curINDX, 4);
    if(FICON4.IsLoaded())
        SaveHandler.writeSubRecord(eICON, FICON4.value, FICON4.GetSize());

    if(HNAM.size())
        SaveHandler.writeSubRecord(eHNAM, &HNAM[0], (unsigned int)HNAM.size() * sizeof(unsigned int));
    else
        SaveHandler.writeSubRecord(eHNAM, NULL, 0);

    if(ENAM.size())
        SaveHandler.writeSubRecord(eENAM, &ENAM[0], (unsigned int)ENAM.size() * sizeof(unsigned int));
    else
        SaveHandler.writeSubRecord(eENAM, NULL, 0);

    if(FGGS.IsLoaded())
        SaveHandler.writeSubRecord(eFGGS, FGGS.value, FGGS.GetSize());
    if(FGGA.IsLoaded())
        SaveHandler.writeSubRecord(eFGGA, FGGA.value, FGGA.GetSize());
    if(FGTS.IsLoaded())
        SaveHandler.writeSubRecord(eFGTS, FGTS.value, FGTS.GetSize());

    if(SNAM.IsLoaded())
        SaveHandler.writeSubRecord(eSNAM, &SNAM.value, SNAM.GetSize());

    return -1;
    }

#ifdef _DEBUG
void RACERecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned int indentation = 4;
    printf("  RACE\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    EDID.Debug("EDID", debugLevel, indentation);

    FULL.Debug("FULL", debugLevel, indentation);

    DESC.Debug("DESC", debugLevel, indentation);

    if(SPLO.size())
        {
        PrintIndent(indentation);
        printf("SPLO:\n");
        indentation += 2;
        if(debugLevel > 3)
            for(unsigned int p = 0;p < SPLO.size();p++)
                {
                PrintIndent(indentation);
                printf("%u:%s\n", p, PrintFormID(SPLO[p]));
                }
        indentation -= 2;
        }

    if(XNAM.size())
        {
        PrintIndent(indentation);
        printf("XNAM:\n");
        indentation += 2;
        for(unsigned int p = 0;p < XNAM.size();p++)
            {
            PrintIndent(indentation);
            printf("Index: %u\n", p);
            XNAM[p]->Debug(NULL, debugLevel, indentation);
            }
        indentation -= 2;
        }

    DATA.Debug("DATA", debugLevel, indentation);

    VNAM.Debug("VNAM", debugLevel, indentation);

    DNAM.Debug("DNAM", debugLevel, indentation);

    CNAM.Debug("CNAM", debugLevel, indentation);

    PNAM.Debug("PNAM", debugLevel, indentation);

    UNAM.Debug("UNAM", debugLevel, indentation);

    ATTR.Debug("UNAM", debugLevel, indentation);

    MOD0.Debug("MOD0", debugLevel, indentation);

    MOD1.Debug("MOD1", debugLevel, indentation);

    MOD2.Debug("MOD2", debugLevel, indentation);

    MOD3.Debug("MOD3", debugLevel, indentation);

    MOD4.Debug("MOD4", debugLevel, indentation);

    MOD5.Debug("MOD5", debugLevel, indentation);

    MOD6.Debug("MOD6", debugLevel, indentation);

    MOD7.Debug("MOD7", debugLevel, indentation);

    MOD8.Debug("MOD8", debugLevel, indentation);

    MMODL.Debug("MMODL", debugLevel, indentation);

    MICON0.Debug("MICON0", debugLevel, indentation);

    MICON1.Debug("MICON1", debugLevel, indentation);

    MICON2.Debug("MICON2", debugLevel, indentation);

    MICON3.Debug("MICON3", debugLevel, indentation);

    MICON4.Debug("MICON4", debugLevel, indentation);

    FMODL.Debug("FMODL", debugLevel, indentation);

    FICON0.Debug("FICON0", debugLevel, indentation);

    FICON1.Debug("FICON1", debugLevel, indentation);

    FICON2.Debug("FICON2", debugLevel, indentation);

    FICON3.Debug("FICON3", debugLevel, indentation);

    FICON4.Debug("FICON4", debugLevel, indentation);

    if(HNAM.size())
        {
        PrintIndent(indentation);
        printf("HNAM:\n");
        indentation += 2;
        if(debugLevel > 3)
            for(unsigned int p = 0;p < HNAM.size();p++)
                {
                PrintIndent(indentation);
                printf("%u:%s\n", p, PrintFormID(HNAM[p]));
                }
        indentation -= 2;
        }

    if(ENAM.size())
        {
        PrintIndent(indentation);
        printf("ENAM:\n");
        indentation += 2;
        if(debugLevel > 3)
            for(unsigned int p = 0;p < ENAM.size();p++)
                {
                PrintIndent(indentation);
                printf("%u:%s\n", p, PrintFormID(ENAM[p]));
                }
        indentation -= 2;
        }

    FGGS.Debug("FGGS", debugLevel, indentation);

    FGGA.Debug("FGGA", debugLevel, indentation);

    FGTS.Debug("FGTS", debugLevel, indentation);

    SNAM.Debug("SNAM", debugLevel, indentation);
    }
#endif
