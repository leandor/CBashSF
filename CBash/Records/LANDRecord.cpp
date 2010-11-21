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
#include "LANDRecord.h"

signed long LANDRecord::ParseRecord(unsigned char *buffer, const unsigned long &recSize)
    {
    if(IsLoaded())
        return -1;
    IsLoaded(true);
    unsigned long subType = 0;
    unsigned long subSize = 0;
    unsigned long curPos = 0;
    ReqSubRecord<LANDGENTXT> *curTexture = NULL;
    LANDLAYERS *curLayer = NULL;
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
            case eVNML:
                VNML.Read(buffer, subSize, curPos);
                break;
            case eVHGT:
                VHGT.Read(buffer, subSize, curPos);
                break;
            case eVCLR:
                VCLR.Read(buffer, subSize, curPos);
                break;
            case eBTXT:
                curTexture = new ReqSubRecord<LANDGENTXT>;
                curTexture->Read(buffer, subSize, curPos);
                BTXT.push_back(curTexture);
                break;
            case eATXT:
                curLayer = new LANDLAYERS;
                curLayer->ATXT.Read(buffer, subSize, curPos);
                Layers.push_back(curLayer);
                break;
            case eVTXT:
                if(subSize % sizeof(LANDVTXT) == 0)
                    {
                    if(subSize == 0)
                        break;
                    curLayer->VTXT.resize(subSize / sizeof(LANDVTXT));
                    _readBuffer(&curLayer->VTXT[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized VTXT size: %i\n", subSize);
                    curPos += subSize;
                    }
                //switch(curTexture.value.quadrant)
                //    {
                //    case eBottomLeft:
                //        for(unsigned long x = 0; x < VTXT.size(); ++x)
                //            Merged->Points[(VTXT[x].position % 17)][(VTXT[x].position / 17)].AlphaLayer[curTexture.value.layer] = VTXT[x].opacity;
                //        break;
                //    case eBottomRight:
                //        for(unsigned long x = 0; x < VTXT.size(); ++x)
                //            Merged->Points[(VTXT[x].position % 17) + 16][(VTXT[x].position / 17)].AlphaLayer[curTexture.value.layer] = VTXT[x].opacity;
                //        break;
                //    case eTopLeft:
                //        for(unsigned long x = 0; x < VTXT.size(); ++x)
                //            Merged->Points[(VTXT[x].position % 17)][(VTXT[x].position / 17) + 16].AlphaLayer[curTexture.value.layer] = VTXT[x].opacity;
                //        break;
                //    case eTopRight:
                //        for(unsigned long x = 0; x < VTXT.size(); ++x)
                //            Merged->Points[(VTXT[x].position % 17) + 16][(VTXT[x].position / 17) + 16].AlphaLayer[curTexture.value.layer] = VTXT[x].opacity;
                //        break;
                //    default:
                //        printf("Invalid ATXT quadrant when parsing VTXT: %u\n", curTexture.value.quadrant);
                //        break;
                //    }
                break;
            case eVTEX:
                if(subSize % sizeof(unsigned long) == 0)
                    {
                    if(subSize == 0)
                        break;
                    VTEX.resize(subSize / sizeof(unsigned long));
                    _readBuffer(&VTEX[0], buffer, subSize, curPos);
                    }
                else
                    {
                    printf("  Unrecognized VTEX size: %i\n", subSize);
                    curPos += subSize;
                    }
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LAND: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", curPos - 6);
                curPos = recSize;
                break;
            }
        };
    return 0;
    }

unsigned long LANDRecord::GetSize(bool forceCalc)
    {
    if(!forceCalc && recData != NULL)
        return *(unsigned long*)&recData[-16];
    unsigned long cSize = 0;
    unsigned long TotSize = 0;
    if(DATA.IsLoaded())
        {
        cSize = DATA.GetSize();
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }
    if(VNML.IsLoaded())
        TotSize += VNML.GetSize() + 6;
    if(VHGT.IsLoaded())
        TotSize += VHGT.GetSize() + 6;
    if(VCLR.IsLoaded())
        TotSize += VCLR.GetSize() + 6;

    if(BTXT.size())
        for(unsigned long p = 0; p < BTXT.size(); p++)
            if(BTXT[p] != NULL && BTXT[p]->IsLoaded())
                TotSize += BTXT[p]->GetSize() + 6;

    if(Layers.size())
        for(unsigned long p = 0; p < Layers.size(); p++)
            {
            if(Layers[p]->ATXT.IsLoaded())
                TotSize += Layers[p]->ATXT.GetSize() + 6;
            if(Layers[p]->VTXT.size())
                {
                cSize = (sizeof(LANDVTXT) * (unsigned long)Layers[p]->VTXT.size());
                if(cSize > 65535) cSize += 10;
                TotSize += cSize += 6;
                }
            }

    if(VTEX.size())
        {
        cSize = (sizeof(unsigned long) * (unsigned long)VTEX.size());
        if(cSize > 65535) cSize += 10;
        TotSize += cSize += 6;
        }

    return TotSize;
    }

signed long LANDRecord::WriteRecord(_FileHandler &SaveHandler)
    {
    if(DATA.IsLoaded())
        SaveHandler.writeSubRecord(eDATA, DATA.value, DATA.GetSize());
    if(VNML.IsLoaded())
        SaveHandler.writeSubRecord(eVNML, VNML.value, VNML.GetSize());
    if(VHGT.IsLoaded())
        SaveHandler.writeSubRecord(eVHGT, VHGT.value, VHGT.GetSize());
    if(VCLR.IsLoaded())
        SaveHandler.writeSubRecord(eVCLR, VCLR.value, VCLR.GetSize());
    if(BTXT.size())
        for(unsigned long p = 0; p < BTXT.size(); p++)
            if(BTXT[p]->IsLoaded())
                SaveHandler.writeSubRecord(eBTXT, &BTXT[p]->value, BTXT[p]->GetSize());

    if(Layers.size())
        for(unsigned long p = 0; p < Layers.size(); p++)
            {
            if(Layers[p]->ATXT.IsLoaded())
                SaveHandler.writeSubRecord(eATXT, &Layers[p]->ATXT.value, Layers[p]->ATXT.GetSize());
            if(Layers[p]->VTXT.size())
                SaveHandler.writeSubRecord(eVTXT, &Layers[p]->VTXT[0], (unsigned long)Layers[p]->VTXT.size() * sizeof(LANDVTXT));
            }
    if(VTEX.size())
        SaveHandler.writeSubRecord(eVTEX, &VTEX[0], (unsigned long)VTEX.size() * sizeof(unsigned long));

    return -1;
    }

#ifdef _DEBUG
void LANDRecord::Debug(int debugLevel)
    {
    if(!IsLoaded())
        return;
    unsigned long indentation = 4;
    printf("  LAND\n");
    if(Header.IsLoaded())
        Header.Debug(debugLevel, indentation);

    DATA.Debug("DATA", debugLevel, indentation);

    }
#endif

unsigned char LANDRecord::CalcQuadrant(const unsigned long &row, const unsigned long &column)
    {
    if(column > 16)
        {
        if(row > 16) return eTopRight;
        else return eBottomRight;
        }
    else
        {
        if(row > 16) return eTopLeft;
        else return eBottomLeft;
        }
    }

unsigned short LANDRecord::CalcPosition(const unsigned char &curQuadrant, const unsigned long &row, const unsigned long &column)
    {
    switch(curQuadrant)
        {
        case eTopRight:
            return (unsigned short)((column - 16) + ((row - 16) * 17));
        case eBottomRight:
            return (unsigned short)((column - 16) + ((row) * 17));
        case eTopLeft:
            return (unsigned short)((column) + ((row - 16) * 17));
        case eBottomLeft:
            return (unsigned short)(column + (row * 17));
        default:
            return 0;
        }
    }

float LANDRecord::CalcHeight(const unsigned long &row, const unsigned long &column)
    {
    if(!VHGT.IsLoaded())
        return 0.0f;
    float fRetValue = VHGT->offset * 8.0f;
    for(unsigned long curRow = 0; curRow <= row; ++curRow)
        fRetValue += (VHGT->VHGT[curRow][0] * 8.0f);
    for(unsigned long curColumn = 1; curColumn <= column; ++curColumn)
        fRetValue += (VHGT->VHGT[row][curColumn] * 8.0f);
    return fRetValue;
    }
