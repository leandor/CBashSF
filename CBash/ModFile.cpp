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
// ModFile.cpp
#include "ModFile.h"
#include "Common.h"
#include "BaseRecord.h"
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

int ModFile::Open()
    {
    if(IsOpen)
        return 0;
    try
        {
        m_region = new mapped_region(file_mapping(FileName, read_only), read_only);
        }
    catch(...)
        {
        printf("Open Error\n");
        throw;
        return -1;
        }
    fileBuffer = (unsigned char*)m_region->get_address();
    fileEnd = (unsigned int)m_region->get_size();
    IsOpen = true;
    return 0;
    }

int ModFile::Close()
    {
    if(!IsOpen)
        return 0;
    delete m_region;
    m_region = NULL;
    IsOpen = false;
    return 0;
    }

int ModFile::LoadTES4()
    {
    unsigned int curPos = 8;
    if(TES4.IsLoaded())
        return 0;
    Open();
    _readBuffer(&TES4.flags, fileBuffer, 4, curPos);
    _readBuffer(&TES4.formID, fileBuffer, 4, curPos);
    _readBuffer(&TES4.flagsUnk, fileBuffer, 4, curPos);
    if(TES4.IsLoaded())
        printf("Flag used!!!!: %08X\n", TES4.flagsUnk);
    TES4.recStart = 20;
    TES4.Read(fileBuffer, FormIDHandler);
    return 1;
    }

void ModFile::UpdateFormCount()
    {
    unsigned int formCount = 0, GRUPCount = 0, childCount = 0;
    GRUPCount = (unsigned int)GMST.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)GLOB.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)CLAS.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)FACT.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)HAIR.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)EYES.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)RACE.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)SOUN.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)SKIL.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)MGEF.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)SCPT.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)LTEX.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)ENCH.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)SPEL.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)BSGN.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)ACTI.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)APPA.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)ARMO.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)BOOK.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)CLOT.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)CONT.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)DOOR.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)INGR.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)LIGH.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)MISC.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)STAT.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)GRAS.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)TREE.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)FLOR.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)FURN.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)WEAP.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)AMMO.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)NPC_.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)CREA.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)LVLC.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)SLGM.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)KEYM.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)ALCH.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)SBSP.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)SGST.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)LVLI.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)WTHR.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)CLMT.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)REGN.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;

    GRUPCount = (unsigned int)CELL.Records.size();
    if(GRUPCount)
        {
        ++formCount += GRUPCount;
        childCount = 0;
        std::vector<unsigned int> BlockHeaders(10, 0);
        std::vector< std::vector<unsigned int> > SubBlockHeaders(10, std::vector<unsigned int>(10, 0));
        int ObjectID, BlockIndex, SubBlockIndex;
        for(unsigned int p = 0; p < GRUPCount; ++p)
            {
            bool hasTemp = false, hasVWD = false, hasPersistent = false;
            if(CELL.Records[p]->PGRD != NULL)
                ++childCount;
            childCount += (unsigned int)CELL.Records[p]->REFR.size();
            for(unsigned int x = 0; x < CELL.Records[p]->REFR.size(); ++x)
                {
                if(hasPersistent == false && CELL.Records[p]->REFR[x]->IsPersistent())
                    hasPersistent = true;
                else if(hasVWD == false && CELL.Records[p]->REFR[x]->IsVWD())
                    hasVWD = true;
                else if(hasTemp == false)
                    hasTemp = true;
                else
                    break;
                }

            childCount += (unsigned int)CELL.Records[p]->ACHR.size();
            for(unsigned int x = 0; x < CELL.Records[p]->ACHR.size(); ++x)
                {
                if(hasPersistent == false && CELL.Records[p]->ACHR[x]->IsPersistent())
                    hasPersistent = true;
                else if(hasVWD == false && CELL.Records[p]->ACHR[x]->IsVWD())
                    hasVWD = true;
                else if(hasTemp == false)
                    hasTemp = true;
                else
                    break;
                }
            childCount += (unsigned int)CELL.Records[p]->ACRE.size();
            for(unsigned int x = 0; x < CELL.Records[p]->ACRE.size(); ++x)
                {
                if(hasPersistent == false && CELL.Records[p]->ACRE[x]->IsPersistent())
                    hasPersistent = true;
                else if(hasVWD == false && CELL.Records[p]->ACRE[x]->IsVWD())
                    hasVWD = true;
                else if(hasTemp == false)
                    hasTemp = true;
                else
                    break;
                }
            //Account for Children GRUPs
            if(hasPersistent) ++childCount;
            if(hasVWD) ++childCount;
            if(hasTemp) ++childCount;
            //Account for Children GRUP
            if(hasPersistent || hasVWD || hasTemp) ++childCount;

            ObjectID = CELL.Records[p]->formID & 0x00FFFFFF;
            BlockIndex = ObjectID % 10;
            SubBlockIndex = (ObjectID / 10) % 10;
            if(BlockHeaders[BlockIndex] == 0)
                {
                ++childCount;
                BlockHeaders[BlockIndex] = 1;
                }
            if(SubBlockHeaders[BlockIndex][SubBlockIndex] == 0)
                {
                ++childCount;
                SubBlockHeaders[BlockIndex][SubBlockIndex] = 1;
                }
            }
        if(childCount) ++formCount += childCount;
        }

    GRUPCount = (unsigned int)WRLD.Records.size();
    if(GRUPCount)
        {
        ++formCount += GRUPCount;
        childCount = 0;
        bool hasTemp = false, hasVWD = false, hasPersistent = false, hasWRLDGRUP = false;

        int gridX, gridY, BlockIndex, SubBlockIndex;
        WritableWorld WriteWorld;
        unsigned int numCELLS;
        for(unsigned int x = 0; x < GRUPCount; ++x)
            {
            if(WRLD.Records[x]->ROAD != NULL)
                {
                ++childCount;
                hasWRLDGRUP = true;
                }
            childCount += numCELLS = (unsigned int)WRLD.Records[x]->CELLS.size();
            for(unsigned int p = 0; p < numCELLS; ++p)
                {
                hasWRLDGRUP = true;
                hasTemp = false;
                hasVWD = false;
                hasPersistent = false;
                if(WRLD.Records[x]->CELLS[p]->PGRD != NULL)
                    ++childCount;
                childCount += (unsigned int)WRLD.Records[x]->CELLS[p]->REFR.size();
                for(unsigned int z = 0; z < WRLD.Records[x]->CELLS[p]->REFR.size(); ++z)
                    {
                    if(hasPersistent == false && WRLD.Records[x]->CELLS[p]->REFR[z]->IsPersistent())
                        hasPersistent = true;
                    else if(hasVWD == false && WRLD.Records[x]->CELLS[p]->REFR[z]->IsVWD())
                        hasVWD = true;
                    else if(hasTemp == false)
                        hasTemp = true;
                    else
                        break;
                    }

                childCount += (unsigned int)WRLD.Records[x]->CELLS[p]->ACHR.size();
                for(unsigned int z = 0; z < WRLD.Records[x]->CELLS[p]->ACHR.size(); ++z)
                    {
                    if(hasPersistent == false && WRLD.Records[x]->CELLS[p]->ACHR[z]->IsPersistent())
                        hasPersistent = true;
                    else if(hasVWD == false && WRLD.Records[x]->CELLS[p]->ACHR[z]->IsVWD())
                        hasVWD = true;
                    else if(hasTemp == false)
                        hasTemp = true;
                    else
                        break;
                    }
                childCount += (unsigned int)WRLD.Records[x]->CELLS[p]->ACRE.size();
                for(unsigned int z = 0; z < WRLD.Records[x]->CELLS[p]->ACRE.size(); ++z)
                    {
                    if(hasPersistent == false && WRLD.Records[x]->CELLS[p]->ACRE[z]->IsPersistent())
                        hasPersistent = true;
                    else if(hasVWD == false && WRLD.Records[x]->CELLS[p]->ACRE[z]->IsVWD())
                        hasVWD = true;
                    else if(hasTemp == false)
                        hasTemp = true;
                    else
                        break;
                    }
                //Account for Children GRUPs
                if(hasPersistent) ++childCount;
                if(hasVWD) ++childCount;
                if(hasTemp) ++childCount;
                //Account for Children GRUP
                if(hasPersistent || hasVWD || hasTemp) ++childCount;

                gridX = (int)floor(WRLD.Records[x]->CELLS[p]->XCLC.value.posX / 8.0);
                gridY = (int)floor(WRLD.Records[x]->CELLS[p]->XCLC.value.posY / 8.0);
                SubBlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                gridX = (int)floor(gridX / 4.0);
                gridY = (int)floor(gridY / 4.0);
                BlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                if(WriteWorld.Block[BlockIndex].size == 0)
                    {
                    ++childCount;
                    WriteWorld.Block[BlockIndex].size = 1;
                    }
                if(WriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size == 0)
                    {
                    ++childCount;
                    WriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size = 1;
                    }
                }
            hasPersistent = false;
            if(WRLD.Records[x]->CELL != NULL || hasPersistent)
                {
                hasWRLDGRUP = true;
                ++childCount;
                if(WRLD.Records[x]->CELL != NULL)
                    {
                    for(unsigned int z = 0; z < WRLD.Records[x]->CELL->ACHR.size(); ++z)
                        {
                        if(WRLD.Records[x]->CELL->ACHR[z]->IsPersistent())
                            {
                            ++childCount;
                            hasPersistent = true;
                            }
                        }

                    for(unsigned int z = 0; z < WRLD.Records[x]->CELL->ACRE.size(); ++z)
                        {
                        if(WRLD.Records[x]->CELL->ACRE[z]->IsPersistent())
                            {
                            ++childCount;
                            hasPersistent = true;
                            }
                        }

                    for(unsigned int z = 0; z < WRLD.Records[x]->CELL->REFR.size(); ++z)
                        {
                        if(WRLD.Records[x]->CELL->REFR[z]->IsPersistent())
                            {
                            ++childCount;
                            hasPersistent = true;
                            }
                        }
                    }
                if(hasPersistent) childCount += 2;
                }
            if(hasWRLDGRUP) ++childCount;
            }

        if(childCount) ++formCount += childCount;
        }

    GRUPCount = (unsigned int)DIAL.Records.size();
    if(GRUPCount)
        {
        ++formCount += GRUPCount;
        childCount = 0;
        for(unsigned int p = 0; p < GRUPCount; ++p)
            childCount += (unsigned int)DIAL.Records[p]->INFO.size();
        if(childCount) ++formCount += childCount;
        }

    GRUPCount = (unsigned int)QUST.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)IDLE.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)PACK.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)CSTY.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)LSCR.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)LVSP.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)ANIO.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)WATR.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;
    GRUPCount = (unsigned int)EFSH.Records.size();
    if(GRUPCount) ++formCount += GRUPCount;

    TES4.HEDR.value.numRecords = formCount;
    }

int ModFile::Load(boost::threadpool::pool &Threads, const bool &FullLoad)
    {
    enum IgTopRecords {
        eIgGMST=0x54535D47,
        eIgGLOB=0x424F5C47,
        eIgCLAS=0x53415C43,
        eIgFACT=0x54435146,
        eIgHAIR=0x52495148,
        eIgEYES=0x53456945,
        eIgRACE=0x45435152,
        eIgSOUN=0x4E555F53,
        eIgSKIL=0x4C495B53,
        eIgMGEF=0x4645574D,
        eIgSCPT=0x54505353,
        eIgLTEX=0x5845644C,
        eIgENCH=0x48435E45,
        eIgSPEL=0x4C456053,
        eIgBSGN=0x4E476342,
        eIgACTI=0x49545341,
        eIgAPPA=0x41506041,
        eIgARMO=0x4F4D6241,
        eIgBOOK=0x4B4F5F42,
        eIgCLOT=0x544F5C43,
        eIgCONT=0x544E5F43,
        eIgDOOR=0x524F5F44,
        eIgINGR=0x52475E49,
        eIgLIGH=0x4847594C,
        eIgMISC=0x4353594D,
        eIgSTAT=0x54416453,
        eIgGRAS=0x53416247,
        eIgTREE=0x45456254,
        eIgFLOR=0x524F5C46,
        eIgFURN=0x4E526546,
        eIgWEAP=0x50415557,
        eIgAMMO=0x4F4D5D41,
        eIgNPC_=0x5F43604E,
        eIgCREA=0x41456243,
        eIgLVLC=0x434C664C,
        eIgSLGM=0x4D475C53,
        eIgKEYM=0x4D59554B,
        eIgALCH=0x48435C41,
        eIgSBSP=0x50535253,
        eIgSGST=0x54535753,
        eIgLVLI=0x494C664C,
        eIgWTHR=0x52486457,
        eIgCLMT=0x544D5C43,
        eIgREGN=0x4E475552,
        eIgCELL=0x4C4C5543,
        eIgWRLD=0x444C6257,
        eIgDIAL=0x4C415944,
        eIgQUST=0x54536551,
        eIgIDLE=0x454C5449,
        eIgPACK=0x4B435150,
        eIgCSTY=0x59546343,
        eIgLSCR=0x5243634C,
        eIgLVSP=0x5053664C,
        eIgANIO=0x4F495E41,
        eIgWATR=0x52545157,
        eIgEFSH=0x48535645
        };
    if(!TES4.IsLoaded() || LoadedGRUPs)
        return 0;
    Open();
    LoadedGRUPs = true;
    unsigned int GRUPSize;
    unsigned int GRUPLabel;
    unsigned int curPos = TES4.GetSize() + 20;
    curPos += 4;
    while(curPos < fileEnd){
        _readBuffer(&GRUPSize, fileBuffer, 4, curPos);
        _readBuffer(&GRUPLabel, fileBuffer, 4, curPos);
        curPos += 4;
        switch(GRUPLabel)
            {
            //ADD DEFINITIONS HERE
            case eIgGMST:
            case eGMST:
                _readBuffer(&GMST.stamp, fileBuffer, 4, curPos);
                //Threads.schedule(boost::bind(&GRUPRecords<GMSTRecord>::Skim, GMST, boost::ref(Threads), fileBuffer, boost::ref(FormIDHandler), true, GRUPSize, curPos));
                GMST.Skim(Threads, fileBuffer, FormIDHandler, true, GRUPSize, curPos);
                break;
            case eIgGLOB:
            case eGLOB:
                _readBuffer(&GLOB.stamp, fileBuffer, 4, curPos);
                GLOB.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgCLAS:
            case eCLAS:
                _readBuffer(&CLAS.stamp, fileBuffer, 4, curPos);
                CLAS.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgFACT:
            case eFACT:
                _readBuffer(&FACT.stamp, fileBuffer, 4, curPos);
                FACT.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgHAIR:
            case eHAIR:
                _readBuffer(&HAIR.stamp, fileBuffer, 4, curPos);
                HAIR.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgEYES:
            case eEYES:
                _readBuffer(&EYES.stamp, fileBuffer, 4, curPos);
                EYES.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgRACE:
            case eRACE:
                _readBuffer(&RACE.stamp, fileBuffer, 4, curPos);
                RACE.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgSOUN:
            case eSOUN:
                _readBuffer(&SOUN.stamp, fileBuffer, 4, curPos);
                SOUN.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgSKIL:
            case eSKIL:
                _readBuffer(&SKIL.stamp, fileBuffer, 4, curPos);
                SKIL.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgMGEF:
            case eMGEF:
                _readBuffer(&MGEF.stamp, fileBuffer, 4, curPos);
                MGEF.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgSCPT:
            case eSCPT:
                _readBuffer(&SCPT.stamp, fileBuffer, 4, curPos);
                SCPT.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgLTEX:
            case eLTEX:
                _readBuffer(&LTEX.stamp, fileBuffer, 4, curPos);
                LTEX.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgENCH:
            case eENCH:
                _readBuffer(&ENCH.stamp, fileBuffer, 4, curPos);
                ENCH.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgSPEL:
            case eSPEL:
                _readBuffer(&SPEL.stamp, fileBuffer, 4, curPos);
                SPEL.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgBSGN:
            case eBSGN:
                _readBuffer(&BSGN.stamp, fileBuffer, 4, curPos);
                BSGN.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgACTI:
            case eACTI:
                _readBuffer(&ACTI.stamp, fileBuffer, 4, curPos);
                ACTI.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgAPPA:
            case eAPPA:
                _readBuffer(&APPA.stamp, fileBuffer, 4, curPos);
                APPA.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgARMO:
            case eARMO:
                _readBuffer(&ARMO.stamp, fileBuffer, 4, curPos);
                ARMO.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgBOOK:
            case eBOOK:
                _readBuffer(&BOOK.stamp, fileBuffer, 4, curPos);
                BOOK.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgCLOT:
            case eCLOT:
                _readBuffer(&CLOT.stamp, fileBuffer, 4, curPos);
                CLOT.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgCONT:
            case eCONT:
                _readBuffer(&CONT.stamp, fileBuffer, 4, curPos);
                CONT.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgDOOR:
            case eDOOR:
                _readBuffer(&DOOR.stamp, fileBuffer, 4, curPos);
                DOOR.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgINGR:
            case eINGR:
                _readBuffer(&INGR.stamp, fileBuffer, 4, curPos);
                INGR.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgLIGH:
            case eLIGH:
                _readBuffer(&LIGH.stamp, fileBuffer, 4, curPos);
                LIGH.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgMISC:
            case eMISC:
                _readBuffer(&MISC.stamp, fileBuffer, 4, curPos);
                MISC.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgSTAT:
            case eSTAT:
                _readBuffer(&STAT.stamp, fileBuffer, 4, curPos);
                STAT.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgGRAS:
            case eGRAS:
                _readBuffer(&GRAS.stamp, fileBuffer, 4, curPos);
                GRAS.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgTREE:
            case eTREE:
                _readBuffer(&TREE.stamp, fileBuffer, 4, curPos);
                TREE.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgFLOR:
            case eFLOR:
                _readBuffer(&FLOR.stamp, fileBuffer, 4, curPos);
                FLOR.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgFURN:
            case eFURN:
                _readBuffer(&FURN.stamp, fileBuffer, 4, curPos);
                FURN.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgWEAP:
            case eWEAP:
                _readBuffer(&WEAP.stamp, fileBuffer, 4, curPos);
                WEAP.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgAMMO:
            case eAMMO:
                _readBuffer(&AMMO.stamp, fileBuffer, 4, curPos);
                AMMO.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgNPC_:
            case eNPC_:
                _readBuffer(&NPC_.stamp, fileBuffer, 4, curPos);
                NPC_.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgCREA:
            case eCREA:
                _readBuffer(&CREA.stamp, fileBuffer, 4, curPos);
                CREA.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgLVLC:
            case eLVLC:
                _readBuffer(&LVLC.stamp, fileBuffer, 4, curPos);
                LVLC.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgSLGM:
            case eSLGM:
                _readBuffer(&SLGM.stamp, fileBuffer, 4, curPos);
                SLGM.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgKEYM:
            case eKEYM:
                _readBuffer(&KEYM.stamp, fileBuffer, 4, curPos);
                KEYM.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgALCH:
            case eALCH:
                _readBuffer(&ALCH.stamp, fileBuffer, 4, curPos);
                ALCH.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgSBSP:
            case eSBSP:
                _readBuffer(&SBSP.stamp, fileBuffer, 4, curPos);
                SBSP.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgSGST:
            case eSGST:
                _readBuffer(&SGST.stamp, fileBuffer, 4, curPos);
                SGST.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgLVLI:
            case eLVLI:
                _readBuffer(&LVLI.stamp, fileBuffer, 4, curPos);
                LVLI.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgWTHR:
            case eWTHR:
                _readBuffer(&WTHR.stamp, fileBuffer, 4, curPos);
                WTHR.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgCLMT:
            case eCLMT:
                _readBuffer(&CLMT.stamp, fileBuffer, 4, curPos);
                CLMT.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgREGN:
            case eREGN:
                _readBuffer(&REGN.stamp, fileBuffer, 4, curPos);
                REGN.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgCELL:
            case eCELL:
                _readBuffer(&CELL.stamp, fileBuffer, 4, curPos);
                CELL.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgWRLD:
            case eWRLD:
                _readBuffer(&WRLD.stamp, fileBuffer, 4, curPos);
                WRLD.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgDIAL:
            case eDIAL:
                _readBuffer(&DIAL.stamp, fileBuffer, 4, curPos);
                DIAL.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgQUST:
            case eQUST:
                _readBuffer(&QUST.stamp, fileBuffer, 4, curPos);
                QUST.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgIDLE:
            case eIDLE:
                _readBuffer(&IDLE.stamp, fileBuffer, 4, curPos);
                IDLE.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgPACK:
            case ePACK:
                _readBuffer(&PACK.stamp, fileBuffer, 4, curPos);
                PACK.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgCSTY:
            case eCSTY:
                _readBuffer(&CSTY.stamp, fileBuffer, 4, curPos);
                CSTY.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgLSCR:
            case eLSCR:
                _readBuffer(&LSCR.stamp, fileBuffer, 4, curPos);
                LSCR.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgLVSP:
            case eLVSP:
                _readBuffer(&LVSP.stamp, fileBuffer, 4, curPos);
                LVSP.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgANIO:
            case eANIO:
                _readBuffer(&ANIO.stamp, fileBuffer, 4, curPos);
                ANIO.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgWATR:
            case eWATR:
                _readBuffer(&WATR.stamp, fileBuffer, 4, curPos);
                WATR.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            case eIgEFSH:
            case eEFSH:
                _readBuffer(&EFSH.stamp, fileBuffer, 4, curPos);
                EFSH.Skim(Threads, fileBuffer, FormIDHandler, FullLoad, GRUPSize, curPos);
                break;
            default:
                curPos += 4;
                printf("FileName = %s\n", FileName);
                printf("  Unimplemented GRUP = ");
                for(int x = 0;x < 4;x++)
                    printf("%c", ((char*)&GRUPLabel)[x]);
                printf("\n  size  = %i\n", GRUPSize);
                printf("  gStart = %i\n", curPos - 20);
                printf("  gEnd   = %i\n", curPos - 20 + GRUPSize);
                printf("  CurPos = %04x\n\n", curPos);
                break;
            }
        curPos += GRUPSize - 16;
        };
    return 1;
    }


void ModFile::CollapseFormIDs()
    {
    GMST.CollapseFormIDs(FormIDHandler);
    GLOB.CollapseFormIDs(FormIDHandler);
    CLAS.CollapseFormIDs(FormIDHandler);
    FACT.CollapseFormIDs(FormIDHandler);
    HAIR.CollapseFormIDs(FormIDHandler);
    EYES.CollapseFormIDs(FormIDHandler);
    RACE.CollapseFormIDs(FormIDHandler);
    SOUN.CollapseFormIDs(FormIDHandler);
    SKIL.CollapseFormIDs(FormIDHandler);
    MGEF.CollapseFormIDs(FormIDHandler);
    SCPT.CollapseFormIDs(FormIDHandler);
    LTEX.CollapseFormIDs(FormIDHandler);
    ENCH.CollapseFormIDs(FormIDHandler);
    SPEL.CollapseFormIDs(FormIDHandler);
    BSGN.CollapseFormIDs(FormIDHandler);
    ACTI.CollapseFormIDs(FormIDHandler);
    APPA.CollapseFormIDs(FormIDHandler);
    ARMO.CollapseFormIDs(FormIDHandler);
    BOOK.CollapseFormIDs(FormIDHandler);
    CLOT.CollapseFormIDs(FormIDHandler);
    CONT.CollapseFormIDs(FormIDHandler);
    DOOR.CollapseFormIDs(FormIDHandler);
    INGR.CollapseFormIDs(FormIDHandler);
    LIGH.CollapseFormIDs(FormIDHandler);
    MISC.CollapseFormIDs(FormIDHandler);
    STAT.CollapseFormIDs(FormIDHandler);
    GRAS.CollapseFormIDs(FormIDHandler);
    TREE.CollapseFormIDs(FormIDHandler);
    FLOR.CollapseFormIDs(FormIDHandler);
    FURN.CollapseFormIDs(FormIDHandler);
    WEAP.CollapseFormIDs(FormIDHandler);
    AMMO.CollapseFormIDs(FormIDHandler);
    NPC_.CollapseFormIDs(FormIDHandler);
    CREA.CollapseFormIDs(FormIDHandler);
    LVLC.CollapseFormIDs(FormIDHandler);
    SLGM.CollapseFormIDs(FormIDHandler);
    KEYM.CollapseFormIDs(FormIDHandler);
    ALCH.CollapseFormIDs(FormIDHandler);
    SBSP.CollapseFormIDs(FormIDHandler);
    SGST.CollapseFormIDs(FormIDHandler);
    LVLI.CollapseFormIDs(FormIDHandler);
    WTHR.CollapseFormIDs(FormIDHandler);
    CLMT.CollapseFormIDs(FormIDHandler);
    REGN.CollapseFormIDs(FormIDHandler);
    CELL.CollapseFormIDs(FormIDHandler);
    WRLD.CollapseFormIDs(FormIDHandler);
    DIAL.CollapseFormIDs(FormIDHandler);
    QUST.CollapseFormIDs(FormIDHandler);
    IDLE.CollapseFormIDs(FormIDHandler);
    PACK.CollapseFormIDs(FormIDHandler);
    CSTY.CollapseFormIDs(FormIDHandler);
    LSCR.CollapseFormIDs(FormIDHandler);
    LVSP.CollapseFormIDs(FormIDHandler);
    ANIO.CollapseFormIDs(FormIDHandler);
    WATR.CollapseFormIDs(FormIDHandler);
    EFSH.CollapseFormIDs(FormIDHandler);
    }
void ModFile::ExpandFormIDs()
    {
    GMST.ExpandFormIDs(FormIDHandler);
    GLOB.ExpandFormIDs(FormIDHandler);
    CLAS.ExpandFormIDs(FormIDHandler);
    FACT.ExpandFormIDs(FormIDHandler);
    HAIR.ExpandFormIDs(FormIDHandler);
    EYES.ExpandFormIDs(FormIDHandler);
    RACE.ExpandFormIDs(FormIDHandler);
    SOUN.ExpandFormIDs(FormIDHandler);
    SKIL.ExpandFormIDs(FormIDHandler);
    MGEF.ExpandFormIDs(FormIDHandler);
    SCPT.ExpandFormIDs(FormIDHandler);
    LTEX.ExpandFormIDs(FormIDHandler);
    ENCH.ExpandFormIDs(FormIDHandler);
    SPEL.ExpandFormIDs(FormIDHandler);
    BSGN.ExpandFormIDs(FormIDHandler);
    ACTI.ExpandFormIDs(FormIDHandler);
    APPA.ExpandFormIDs(FormIDHandler);
    ARMO.ExpandFormIDs(FormIDHandler);
    BOOK.ExpandFormIDs(FormIDHandler);
    CLOT.ExpandFormIDs(FormIDHandler);
    CONT.ExpandFormIDs(FormIDHandler);
    DOOR.ExpandFormIDs(FormIDHandler);
    INGR.ExpandFormIDs(FormIDHandler);
    LIGH.ExpandFormIDs(FormIDHandler);
    MISC.ExpandFormIDs(FormIDHandler);
    STAT.ExpandFormIDs(FormIDHandler);
    GRAS.ExpandFormIDs(FormIDHandler);
    TREE.ExpandFormIDs(FormIDHandler);
    FLOR.ExpandFormIDs(FormIDHandler);
    FURN.ExpandFormIDs(FormIDHandler);
    WEAP.ExpandFormIDs(FormIDHandler);
    AMMO.ExpandFormIDs(FormIDHandler);
    NPC_.ExpandFormIDs(FormIDHandler);
    CREA.ExpandFormIDs(FormIDHandler);
    LVLC.ExpandFormIDs(FormIDHandler);
    SLGM.ExpandFormIDs(FormIDHandler);
    KEYM.ExpandFormIDs(FormIDHandler);
    ALCH.ExpandFormIDs(FormIDHandler);
    SBSP.ExpandFormIDs(FormIDHandler);
    SGST.ExpandFormIDs(FormIDHandler);
    LVLI.ExpandFormIDs(FormIDHandler);
    WTHR.ExpandFormIDs(FormIDHandler);
    CLMT.ExpandFormIDs(FormIDHandler);
    REGN.ExpandFormIDs(FormIDHandler);
    CELL.ExpandFormIDs(FormIDHandler);
    WRLD.ExpandFormIDs(FormIDHandler);
    DIAL.ExpandFormIDs(FormIDHandler);
    QUST.ExpandFormIDs(FormIDHandler);
    IDLE.ExpandFormIDs(FormIDHandler);
    PACK.ExpandFormIDs(FormIDHandler);
    CSTY.ExpandFormIDs(FormIDHandler);
    LSCR.ExpandFormIDs(FormIDHandler);
    LVSP.ExpandFormIDs(FormIDHandler);
    ANIO.ExpandFormIDs(FormIDHandler);
    WATR.ExpandFormIDs(FormIDHandler);
    EFSH.ExpandFormIDs(FormIDHandler);
    }

int ModFile::Save(FileBuffer &buffer, bool CloseMod)
    {
    UpdateFormCount();
    {
    WritableRecord WriteTES4;
    TES4.Write(WriteTES4);
    buffer.write(WriteTES4);
    }

    //ADD DEFINITIONS HERE
    GMST.WriteGRUP(eGMST, buffer, CloseMod);
    GLOB.WriteGRUP(eGLOB, buffer, CloseMod);
    CLAS.WriteGRUP(eCLAS, buffer, CloseMod);
    FACT.WriteGRUP(eFACT, buffer, CloseMod);
    HAIR.WriteGRUP(eHAIR, buffer, CloseMod);
    EYES.WriteGRUP(eEYES, buffer, CloseMod);
    RACE.WriteGRUP(eRACE, buffer, CloseMod);
    SOUN.WriteGRUP(eSOUN, buffer, CloseMod);
    SKIL.WriteGRUP(eSKIL, buffer, CloseMod);
    MGEF.WriteGRUP(eMGEF, buffer, CloseMod);
    SCPT.WriteGRUP(eSCPT, buffer, CloseMod);
    LTEX.WriteGRUP(eLTEX, buffer, CloseMod);
    ENCH.WriteGRUP(eENCH, buffer, CloseMod);
    SPEL.WriteGRUP(eSPEL, buffer, CloseMod);
    BSGN.WriteGRUP(eBSGN, buffer, CloseMod);
    ACTI.WriteGRUP(eACTI, buffer, CloseMod);
    APPA.WriteGRUP(eAPPA, buffer, CloseMod);
    ARMO.WriteGRUP(eARMO, buffer, CloseMod);
    BOOK.WriteGRUP(eBOOK, buffer, CloseMod);
    CLOT.WriteGRUP(eCLOT, buffer, CloseMod);
    CONT.WriteGRUP(eCONT, buffer, CloseMod);
    DOOR.WriteGRUP(eDOOR, buffer, CloseMod);
    INGR.WriteGRUP(eINGR, buffer, CloseMod);
    LIGH.WriteGRUP(eLIGH, buffer, CloseMod);
    MISC.WriteGRUP(eMISC, buffer, CloseMod);
    STAT.WriteGRUP(eSTAT, buffer, CloseMod);
    GRAS.WriteGRUP(eGRAS, buffer, CloseMod);
    TREE.WriteGRUP(eTREE, buffer, CloseMod);
    FLOR.WriteGRUP(eFLOR, buffer, CloseMod);
    FURN.WriteGRUP(eFURN, buffer, CloseMod);
    WEAP.WriteGRUP(eWEAP, buffer, CloseMod);
    AMMO.WriteGRUP(eAMMO, buffer, CloseMod);
    NPC_.WriteGRUP(eNPC_, buffer, CloseMod);
    CREA.WriteGRUP(eCREA, buffer, CloseMod);
    LVLC.WriteGRUP(eLVLC, buffer, CloseMod);
    SLGM.WriteGRUP(eSLGM, buffer, CloseMod);
    KEYM.WriteGRUP(eKEYM, buffer, CloseMod);
    ALCH.WriteGRUP(eALCH, buffer, CloseMod);
    SBSP.WriteGRUP(eSBSP, buffer, CloseMod);
    SGST.WriteGRUP(eSGST, buffer, CloseMod);
    LVLI.WriteGRUP(eLVLI, buffer, CloseMod);
    WTHR.WriteGRUP(eWTHR, buffer, CloseMod);
    CLMT.WriteGRUP(eCLMT, buffer, CloseMod);
    REGN.WriteGRUP(eREGN, buffer, CloseMod);
    CELL.WriteGRUP(buffer, CloseMod);
    WRLD.WriteGRUP(buffer, CloseMod, FormIDHandler);
    DIAL.WriteGRUP(buffer, CloseMod);
    QUST.WriteGRUP(eQUST, buffer, CloseMod);
    IDLE.WriteGRUP(eIDLE, buffer, CloseMod);
    PACK.WriteGRUP(ePACK, buffer, CloseMod);
    CSTY.WriteGRUP(eCSTY, buffer, CloseMod);
    LSCR.WriteGRUP(eLSCR, buffer, CloseMod);
    LVSP.WriteGRUP(eLVSP, buffer, CloseMod);
    ANIO.WriteGRUP(eANIO, buffer, CloseMod);
    WATR.WriteGRUP(eWATR, buffer, CloseMod);
    EFSH.WriteGRUP(eEFSH, buffer, CloseMod);
    
    if(CloseMod)
        Close();
    return -1;
    }
