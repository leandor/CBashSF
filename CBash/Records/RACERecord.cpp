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
                                printf("  RACE: Unexpected INDX %I under NAM%01I: %i\n", curINDX, curNAM);
                                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                        printf("  RACE: Unexpected NAM%01I: %i\n", curNAM);
                        printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                                printf("  RACE: Unexpected INDX %I under NAM%01I: %i\n", curINDX, curNAM);
                                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                                printf("  RACE: Unexpected ICON under NAM%01I: %i\n", curNAM);
                                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                                printf("  RACE: Unexpected ICON under NAM%01i: indx = %i\n", curNAM, curINDX);
                                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                                curPos = recSize;
                                break;
                            }
                        break;
                    default:
                        //ERROR
                        //printf("FileName = %s\n", FileName);
                        printf("  RACE: Unexpected ICON under NAM%01i\n", curNAM);
                        printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                                printf("  RACE: Unexpected INDX %I under NAM%01I: %i\n", curINDX, curNAM);
                                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                        printf("  RACE: Unexpected MODB under NAM%01I: %i\n", curNAM);
                        printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                                printf("  RACE: Unexpected INDX %I under NAM%01I: %i\n", curINDX, curNAM);
                                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                        printf("  RACE: Unexpected MODT under NAM%01I: %i\n", curNAM);
                        printf("  CurPos = %04x\n\n", recStart + curPos - 6);
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
                printf("  CurPos = %04x\n\n", recStart + curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned int RACERecord::GetSize()
    {
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
        {
        cSize = XNAM[p]->GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(VNAM.IsLoaded())
        {
        cSize = VNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(DNAM.IsLoaded())
        {
        cSize = DNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(CNAM.IsLoaded())
        {
        cSize = CNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(PNAM.IsLoaded())
        {
        cSize = PNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(UNAM.IsLoaded())
        {
        cSize = UNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(ATTR.IsLoaded())
        {
        cSize = ATTR.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(MOD0.MODL.IsLoaded())
        {
        cSize = MOD0.MODL.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(MOD0.MODB.IsLoaded())
        {
        cSize = MOD0.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MOD1.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MOD2.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MOD3.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MOD4.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MOD5.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MOD6.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MOD7.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MOD8.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = MMODL.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = FMODL.MODB.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
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
        {
        cSize = FGGS.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FGGA.IsLoaded())
        {
        cSize = FGGA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(FGTS.IsLoaded())
        {
        cSize = FGTS.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    if(SNAM.IsLoaded())
        {
        cSize = SNAM.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

int RACERecord::WriteRecord(unsigned char *buffer, unsigned int &usedBuffer)
    {
    unsigned int curINDX = 0;
    if(EDID.IsLoaded())
        _writeSubRecord(buffer, eEDID, EDID.GetSize(), EDID.value, usedBuffer);
    if(FULL.IsLoaded())
        _writeSubRecord(buffer, eFULL, FULL.GetSize(), FULL.value, usedBuffer);
    if(DESC.IsLoaded())
        _writeSubRecord(buffer, eDESC, DESC.GetSize(), DESC.value, usedBuffer);

    for(unsigned int p = 0; p < SPLO.size(); p++)
        _writeSubRecord(buffer, eSPLO, sizeof(unsigned int), SPLO[p], usedBuffer);

    for(unsigned int p = 0; p < XNAM.size(); p++)
        if(XNAM[p]->IsLoaded())
            _writeSubRecord(buffer, eXNAM, XNAM[p]->GetSize(), &XNAM[p]->value, usedBuffer);

    if(DATA.IsLoaded())
        _writeSubRecord(buffer, eDATA, DATA.GetSize(), &DATA.value, usedBuffer);
    if(VNAM.IsLoaded())
        _writeSubRecord(buffer, eVNAM, VNAM.GetSize(), &VNAM.value, usedBuffer);
    if(DNAM.IsLoaded())
        _writeSubRecord(buffer, eDNAM, DNAM.GetSize(), &DNAM.value, usedBuffer);
    if(CNAM.IsLoaded())
        _writeSubRecord(buffer, eCNAM, CNAM.GetSize(), &CNAM.value, usedBuffer);
    if(PNAM.IsLoaded())
        _writeSubRecord(buffer, ePNAM, PNAM.GetSize(), &PNAM.value, usedBuffer);
    if(UNAM.IsLoaded())
        _writeSubRecord(buffer, eUNAM, UNAM.GetSize(), &UNAM.value, usedBuffer);
    if(ATTR.IsLoaded())
        _writeSubRecord(buffer, eATTR, ATTR.GetSize(), &ATTR.value, usedBuffer);

    _writeSubRecord(buffer, eNAM0, 0, NULL, usedBuffer);

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD0.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD0.MODL.GetSize(), MOD0.MODL.value, usedBuffer);
    if(MOD0.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD0.MODB.GetSize(), &MOD0.MODB.value, usedBuffer);
    if(MOD0.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD0.MODT.GetSize(), MOD0.MODT.value, usedBuffer);
    if(MOD0.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD0.ICON.GetSize(), MOD0.ICON.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD1.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD1.MODL.GetSize(), MOD1.MODL.value, usedBuffer);
    if(MOD1.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD1.MODB.GetSize(), &MOD1.MODB.value, usedBuffer);
    if(MOD1.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD1.MODT.GetSize(), MOD1.MODT.value, usedBuffer);
    if(MOD1.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD1.ICON.GetSize(), MOD1.ICON.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD2.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD2.MODL.GetSize(), MOD2.MODL.value, usedBuffer);
    if(MOD2.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD2.MODB.GetSize(), &MOD2.MODB.value, usedBuffer);
    if(MOD2.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD2.MODT.GetSize(), MOD2.MODT.value, usedBuffer);
    if(MOD2.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD2.ICON.GetSize(), MOD2.ICON.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD3.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD3.MODL.GetSize(), MOD3.MODL.value, usedBuffer);
    if(MOD3.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD3.MODB.GetSize(), &MOD3.MODB.value, usedBuffer);
    if(MOD3.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD3.MODT.GetSize(), MOD3.MODT.value, usedBuffer);
    if(MOD3.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD3.ICON.GetSize(), MOD3.ICON.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD4.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD4.MODL.GetSize(), MOD4.MODL.value, usedBuffer);
    if(MOD4.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD4.MODB.GetSize(), &MOD4.MODB.value, usedBuffer);
    if(MOD4.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD4.MODT.GetSize(), MOD4.MODT.value, usedBuffer);
    if(MOD4.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD4.ICON.GetSize(), MOD4.ICON.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD5.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD5.MODL.GetSize(), MOD5.MODL.value, usedBuffer);
    if(MOD5.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD5.MODB.GetSize(), &MOD5.MODB.value, usedBuffer);
    if(MOD5.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD5.MODT.GetSize(), MOD5.MODT.value, usedBuffer);
    if(MOD5.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD5.ICON.GetSize(), MOD5.ICON.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD6.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD6.MODL.GetSize(), MOD6.MODL.value, usedBuffer);
    if(MOD6.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD6.MODB.GetSize(), &MOD6.MODB.value, usedBuffer);
    if(MOD6.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD6.MODT.GetSize(), MOD6.MODT.value, usedBuffer);
    if(MOD6.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD6.ICON.GetSize(), MOD6.ICON.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD7.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD7.MODL.GetSize(), MOD7.MODL.value, usedBuffer);
    if(MOD7.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD7.MODB.GetSize(), &MOD7.MODB.value, usedBuffer);
    if(MOD7.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD7.MODT.GetSize(), MOD7.MODT.value, usedBuffer);
    if(MOD7.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD7.ICON.GetSize(), MOD7.ICON.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MOD8.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MOD8.MODL.GetSize(), MOD8.MODL.value, usedBuffer);
    if(MOD8.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MOD8.MODB.GetSize(), &MOD8.MODB.value, usedBuffer);
    if(MOD8.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MOD8.MODT.GetSize(), MOD8.MODT.value, usedBuffer);
    if(MOD8.ICON.IsLoaded())
        _writeSubRecord(buffer, eICON, MOD8.ICON.GetSize(), MOD8.ICON.value, usedBuffer);

    curINDX = 0;
    _writeSubRecord(buffer, eNAM1, 0, NULL, usedBuffer);
    _writeSubRecord(buffer, eMNAM, 0, NULL, usedBuffer);
    if(MMODL.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, MMODL.MODL.GetSize(), MMODL.MODL.value, usedBuffer);
    if(MMODL.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, MMODL.MODB.GetSize(), &MMODL.MODB.value, usedBuffer);
    if(MMODL.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, MMODL.MODT.GetSize(), MMODL.MODT.value, usedBuffer);

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MICON0.IsLoaded())
        _writeSubRecord(buffer, eICON, MICON0.GetSize(), MICON0.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MICON1.IsLoaded())
        _writeSubRecord(buffer, eICON, MICON1.GetSize(), MICON1.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MICON2.IsLoaded())
        _writeSubRecord(buffer, eICON, MICON2.GetSize(), MICON2.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MICON3.IsLoaded())
        _writeSubRecord(buffer, eICON, MICON3.GetSize(), MICON3.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(MICON4.IsLoaded())
        _writeSubRecord(buffer, eICON, MICON4.GetSize(), MICON4.value, usedBuffer);

    curINDX = 0;
    _writeSubRecord(buffer, eFNAM, 0, NULL, usedBuffer);
    if(FMODL.MODL.IsLoaded())
        _writeSubRecord(buffer, eMODL, FMODL.MODL.GetSize(), FMODL.MODL.value, usedBuffer);
    if(FMODL.MODB.IsLoaded())
        _writeSubRecord(buffer, eMODB, FMODL.MODB.GetSize(), &FMODL.MODB.value, usedBuffer);
    if(FMODL.MODT.IsLoaded())
        _writeSubRecord(buffer, eMODT, FMODL.MODT.GetSize(), FMODL.MODT.value, usedBuffer);

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(FICON0.IsLoaded())
        _writeSubRecord(buffer, eICON, FICON0.GetSize(), FICON0.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(FICON1.IsLoaded())
        _writeSubRecord(buffer, eICON, FICON1.GetSize(), FICON1.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(FICON2.IsLoaded())
        _writeSubRecord(buffer, eICON, FICON2.GetSize(), FICON2.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(FICON3.IsLoaded())
        _writeSubRecord(buffer, eICON, FICON3.GetSize(), FICON3.value, usedBuffer);
    curINDX++;

    _writeSubRecord(buffer, eINDX, 4, &curINDX, usedBuffer);
    if(FICON4.IsLoaded())
        _writeSubRecord(buffer, eICON, FICON4.GetSize(), FICON4.value, usedBuffer);

    if(HNAM.size())
        _writeSubRecord(buffer, eHNAM, (unsigned int)HNAM.size() * sizeof(unsigned int), &HNAM[0], usedBuffer);
    else
        _writeSubRecord(buffer, eHNAM, 0, NULL, usedBuffer);

    if(ENAM.size())
        _writeSubRecord(buffer, eENAM, (unsigned int)ENAM.size() * sizeof(unsigned int), &ENAM[0], usedBuffer);
    else
        _writeSubRecord(buffer, eENAM, 0, NULL, usedBuffer);

    if(FGGS.IsLoaded())
        _writeSubRecord(buffer, eFGGS, FGGS.GetSize(), FGGS.value, usedBuffer);
    if(FGGA.IsLoaded())
        _writeSubRecord(buffer, eFGGA, FGGA.GetSize(), FGGA.value, usedBuffer);
    if(FGTS.IsLoaded())
        _writeSubRecord(buffer, eFGTS, FGTS.GetSize(), FGTS.value, usedBuffer);

    if(SNAM.IsLoaded())
        _writeSubRecord(buffer, eSNAM, SNAM.GetSize(), &SNAM.value, usedBuffer);

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
