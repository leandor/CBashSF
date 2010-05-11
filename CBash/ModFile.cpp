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

int ModFile::Save(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
    {
    unsigned int formCount = 0, GRUPCount = 0, CELLSizes = 0, WRLDSizes = 0;
    std::vector<WritableDialogue> DIALSizes;
    std::vector< std::vector< std::vector<WritableCell> > > BlockedRecords(10, std::vector< std::vector<WritableCell> > (10, std::vector<WritableCell>()));
    std::vector<unsigned int> BlockHeaders(10, 0);
    std::vector< std::vector<unsigned int> > SubBlockHeaders(10, std::vector<unsigned int>(10, 0));
    std::vector<WritableWorld> WritableWorlds;
    std::vector<unsigned int> GMSTSizes;
    std::vector<unsigned int> GLOBSizes;
    std::vector<unsigned int> CLASSizes;
    std::vector<unsigned int> FACTSizes;
    std::vector<unsigned int> HAIRSizes;
    std::vector<unsigned int> EYESSizes;
    std::vector<unsigned int> RACESizes;
    std::vector<unsigned int> SOUNSizes;
    std::vector<unsigned int> SKILSizes;
    std::vector<unsigned int> MGEFSizes;
    std::vector<unsigned int> SCPTSizes;
    std::vector<unsigned int> LTEXSizes;
    std::vector<unsigned int> ENCHSizes;
    std::vector<unsigned int> SPELSizes;
    std::vector<unsigned int> BSGNSizes;
    std::vector<unsigned int> ACTISizes;
    std::vector<unsigned int> APPASizes;
    std::vector<unsigned int> ARMOSizes;
    std::vector<unsigned int> BOOKSizes;
    std::vector<unsigned int> CLOTSizes;
    std::vector<unsigned int> CONTSizes;
    std::vector<unsigned int> DOORSizes;
    std::vector<unsigned int> INGRSizes;
    std::vector<unsigned int> LIGHSizes;
    std::vector<unsigned int> MISCSizes;
    std::vector<unsigned int> STATSizes;
    std::vector<unsigned int> GRASSizes;
    std::vector<unsigned int> TREESizes;
    std::vector<unsigned int> FLORSizes;
    std::vector<unsigned int> FURNSizes;
    std::vector<unsigned int> WEAPSizes;
    std::vector<unsigned int> AMMOSizes;
    std::vector<unsigned int> NPC_Sizes;
    std::vector<unsigned int> CREASizes;
    std::vector<unsigned int> LVLCSizes;
    std::vector<unsigned int> SLGMSizes;
    std::vector<unsigned int> KEYMSizes;
    std::vector<unsigned int> ALCHSizes;
    std::vector<unsigned int> SBSPSizes;
    std::vector<unsigned int> SGSTSizes;
    std::vector<unsigned int> LVLISizes;
    std::vector<unsigned int> WTHRSizes;
    std::vector<unsigned int> CLMTSizes;
    std::vector<unsigned int> REGNSizes;
    std::vector<unsigned int> QUSTSizes;
    std::vector<unsigned int> IDLESizes;
    std::vector<unsigned int> PACKSizes;
    std::vector<unsigned int> CSTYSizes;
    std::vector<unsigned int> LSCRSizes;
    std::vector<unsigned int> LVSPSizes;
    std::vector<unsigned int> ANIOSizes;
    std::vector<unsigned int> WATRSizes;
    std::vector<unsigned int> EFSHSizes;
    GRUPCount = (unsigned int)GMST.Records.size();
    if(GRUPCount)
        {
        GMST.GetSizes(GMSTSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)GLOB.Records.size();
    if(GRUPCount)
        {
        GLOB.GetSizes(GLOBSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)CLAS.Records.size();
    if(GRUPCount)
        {
        CLAS.GetSizes(CLASSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)FACT.Records.size();
    if(GRUPCount)
        {
        FACT.GetSizes(FACTSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)HAIR.Records.size();
    if(GRUPCount)
        {
        HAIR.GetSizes(HAIRSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)EYES.Records.size();
    if(GRUPCount)
        {
        EYES.GetSizes(EYESSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)RACE.Records.size();
    if(GRUPCount)
        {
        RACE.GetSizes(RACESizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)SOUN.Records.size();
    if(GRUPCount)
        {
        SOUN.GetSizes(SOUNSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)SKIL.Records.size();
    if(GRUPCount)
        {
        SKIL.GetSizes(SKILSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)MGEF.Records.size();
    if(GRUPCount)
        {
        MGEF.GetSizes(MGEFSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)SCPT.Records.size();
    if(GRUPCount)
        {
        SCPT.GetSizes(SCPTSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)LTEX.Records.size();
    if(GRUPCount)
        {
        LTEX.GetSizes(LTEXSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)ENCH.Records.size();
    if(GRUPCount)
        {
        ENCH.GetSizes(ENCHSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)SPEL.Records.size();
    if(GRUPCount)
        {
        SPEL.GetSizes(SPELSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)BSGN.Records.size();
    if(GRUPCount)
        {
        BSGN.GetSizes(BSGNSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)ACTI.Records.size();
    if(GRUPCount)
        {
        ACTI.GetSizes(ACTISizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)APPA.Records.size();
    if(GRUPCount)
        {
        APPA.GetSizes(APPASizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)ARMO.Records.size();
    if(GRUPCount)
        {
        ARMO.GetSizes(ARMOSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)BOOK.Records.size();
    if(GRUPCount)
        {
        BOOK.GetSizes(BOOKSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)CLOT.Records.size();
    if(GRUPCount)
        {
        CLOT.GetSizes(CLOTSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)CONT.Records.size();
    if(GRUPCount)
        {
        CONT.GetSizes(CONTSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)DOOR.Records.size();
    if(GRUPCount)
        {
        DOOR.GetSizes(DOORSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)INGR.Records.size();
    if(GRUPCount)
        {
        INGR.GetSizes(INGRSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)LIGH.Records.size();
    if(GRUPCount)
        {
        LIGH.GetSizes(LIGHSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)MISC.Records.size();
    if(GRUPCount)
        {
        MISC.GetSizes(MISCSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)STAT.Records.size();
    if(GRUPCount)
        {
        STAT.GetSizes(STATSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)GRAS.Records.size();
    if(GRUPCount)
        {
        GRAS.GetSizes(GRASSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)TREE.Records.size();
    if(GRUPCount)
        {
        TREE.GetSizes(TREESizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)FLOR.Records.size();
    if(GRUPCount)
        {
        FLOR.GetSizes(FLORSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)FURN.Records.size();
    if(GRUPCount)
        {
        FURN.GetSizes(FURNSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)WEAP.Records.size();
    if(GRUPCount)
        {
        WEAP.GetSizes(WEAPSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)AMMO.Records.size();
    if(GRUPCount)
        {
        AMMO.GetSizes(AMMOSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)NPC_.Records.size();
    if(GRUPCount)
        {
        NPC_.GetSizes(NPC_Sizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)CREA.Records.size();
    if(GRUPCount)
        {
        CREA.GetSizes(CREASizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)LVLC.Records.size();
    if(GRUPCount)
        {
        LVLC.GetSizes(LVLCSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)SLGM.Records.size();
    if(GRUPCount)
        {
        SLGM.GetSizes(SLGMSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)KEYM.Records.size();
    if(GRUPCount)
        {
        KEYM.GetSizes(KEYMSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)ALCH.Records.size();
    if(GRUPCount)
        {
        ALCH.GetSizes(ALCHSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)SBSP.Records.size();
    if(GRUPCount)
        {
        SBSP.GetSizes(SBSPSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)SGST.Records.size();
    if(GRUPCount)
        {
        SGST.GetSizes(SGSTSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)LVLI.Records.size();
    if(GRUPCount)
        {
        LVLI.GetSizes(LVLISizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)WTHR.Records.size();
    if(GRUPCount)
        {
        WTHR.GetSizes(WTHRSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)CLMT.Records.size();
    if(GRUPCount)
        {
        CLMT.GetSizes(CLMTSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)REGN.Records.size();
    if(GRUPCount)
        {
        REGN.GetSizes(REGNSizes);
        ++formCount;
        formCount += GRUPCount;
        }

    GRUPCount = (unsigned int)CELL.Records.size();
    if(GRUPCount)
        {
        GRUPCount = CELL.GetSizes(CELLSizes, BlockedRecords, BlockHeaders, SubBlockHeaders);
        formCount += GRUPCount;
        }

    GRUPCount = (unsigned int)WRLD.Records.size();
    if(GRUPCount)
        {
        GRUPCount = WRLD.GetSizes(WRLDSizes, WritableWorlds, FormIDHandler);
        formCount += GRUPCount;
        }

    GRUPCount = (unsigned int)DIAL.Records.size();
    if(GRUPCount)
        {
        GRUPCount = DIAL.GetSizes(DIALSizes);
        formCount += GRUPCount;
        }
    if(GRUPCount) ++formCount, formCount += GRUPCount;

    GRUPCount = (unsigned int)QUST.Records.size();
    if(GRUPCount)
        {
        QUST.GetSizes(QUSTSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)IDLE.Records.size();
    if(GRUPCount)
        {
        IDLE.GetSizes(IDLESizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)PACK.Records.size();
    if(GRUPCount)
        {
        PACK.GetSizes(PACKSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)CSTY.Records.size();
    if(GRUPCount)
        {
        CSTY.GetSizes(CSTYSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)LSCR.Records.size();
    if(GRUPCount)
        {
        LSCR.GetSizes(LSCRSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)LVSP.Records.size();
    if(GRUPCount)
        {
        LVSP.GetSizes(LVSPSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)ANIO.Records.size();
    if(GRUPCount)
        {
        ANIO.GetSizes(ANIOSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)WATR.Records.size();
    if(GRUPCount)
        {
        WATR.GetSizes(WATRSizes);
        ++formCount;
        formCount += GRUPCount;
        }
    GRUPCount = (unsigned int)EFSH.Records.size();
    if(GRUPCount)
        {
        EFSH.GetSizes(EFSHSizes);
        ++formCount;
        formCount += GRUPCount;
        }

    //ADD DEFINITIONS HERE
    TES4.HEDR.value.numRecords = formCount;
    //reusing variables
    GRUPCount = TES4.GetSize();
    TES4.Write(fh, buffer, GRUPCount, usedBuffer);
    GMST.WriteGRUP(GMSTSizes, eGMST, fh, buffer, usedBuffer);
    GLOB.WriteGRUP(GLOBSizes, eGLOB, fh, buffer, usedBuffer);
    CLAS.WriteGRUP(CLASSizes, eCLAS, fh, buffer, usedBuffer);
    FACT.WriteGRUP(FACTSizes, eFACT, fh, buffer, usedBuffer);
    HAIR.WriteGRUP(HAIRSizes, eHAIR, fh, buffer, usedBuffer);
    EYES.WriteGRUP(EYESSizes, eEYES, fh, buffer, usedBuffer);
    RACE.WriteGRUP(RACESizes, eRACE, fh, buffer, usedBuffer);
    SOUN.WriteGRUP(SOUNSizes, eSOUN, fh, buffer, usedBuffer);
    SKIL.WriteGRUP(SKILSizes, eSKIL, fh, buffer, usedBuffer);
    MGEF.WriteGRUP(MGEFSizes, eMGEF, fh, buffer, usedBuffer);
    SCPT.WriteGRUP(SCPTSizes, eSCPT, fh, buffer, usedBuffer);
    LTEX.WriteGRUP(LTEXSizes, eLTEX, fh, buffer, usedBuffer);
    ENCH.WriteGRUP(ENCHSizes, eENCH, fh, buffer, usedBuffer);
    SPEL.WriteGRUP(SPELSizes, eSPEL, fh, buffer, usedBuffer);
    BSGN.WriteGRUP(BSGNSizes, eBSGN, fh, buffer, usedBuffer);
    ACTI.WriteGRUP(ACTISizes, eACTI, fh, buffer, usedBuffer);
    APPA.WriteGRUP(APPASizes, eAPPA, fh, buffer, usedBuffer);
    ARMO.WriteGRUP(ARMOSizes, eARMO, fh, buffer, usedBuffer);
    BOOK.WriteGRUP(BOOKSizes, eBOOK, fh, buffer, usedBuffer);
    CLOT.WriteGRUP(CLOTSizes, eCLOT, fh, buffer, usedBuffer);
    CONT.WriteGRUP(CONTSizes, eCONT, fh, buffer, usedBuffer);
    DOOR.WriteGRUP(DOORSizes, eDOOR, fh, buffer, usedBuffer);
    INGR.WriteGRUP(INGRSizes, eINGR, fh, buffer, usedBuffer);
    LIGH.WriteGRUP(LIGHSizes, eLIGH, fh, buffer, usedBuffer);
    MISC.WriteGRUP(MISCSizes, eMISC, fh, buffer, usedBuffer);
    STAT.WriteGRUP(STATSizes, eSTAT, fh, buffer, usedBuffer);
    GRAS.WriteGRUP(GRASSizes, eGRAS, fh, buffer, usedBuffer);
    TREE.WriteGRUP(TREESizes, eTREE, fh, buffer, usedBuffer);
    FLOR.WriteGRUP(FLORSizes, eFLOR, fh, buffer, usedBuffer);
    FURN.WriteGRUP(FURNSizes, eFURN, fh, buffer, usedBuffer);
    WEAP.WriteGRUP(WEAPSizes, eWEAP, fh, buffer, usedBuffer);
    AMMO.WriteGRUP(AMMOSizes, eAMMO, fh, buffer, usedBuffer);
    NPC_.WriteGRUP(NPC_Sizes, eNPC_, fh, buffer, usedBuffer);
    CREA.WriteGRUP(CREASizes, eCREA, fh, buffer, usedBuffer);
    LVLC.WriteGRUP(LVLCSizes, eLVLC, fh, buffer, usedBuffer);
    SLGM.WriteGRUP(SLGMSizes, eSLGM, fh, buffer, usedBuffer);
    KEYM.WriteGRUP(KEYMSizes, eKEYM, fh, buffer, usedBuffer);
    ALCH.WriteGRUP(ALCHSizes, eALCH, fh, buffer, usedBuffer);
    SBSP.WriteGRUP(SBSPSizes, eSBSP, fh, buffer, usedBuffer);
    SGST.WriteGRUP(SGSTSizes, eSGST, fh, buffer, usedBuffer);
    LVLI.WriteGRUP(LVLISizes, eLVLI, fh, buffer, usedBuffer);
    WTHR.WriteGRUP(WTHRSizes, eWTHR, fh, buffer, usedBuffer);
    CLMT.WriteGRUP(CLMTSizes, eCLMT, fh, buffer, usedBuffer);
    REGN.WriteGRUP(REGNSizes, eREGN, fh, buffer, usedBuffer);
    CELL.WriteGRUP(CELLSizes, BlockedRecords, BlockHeaders, SubBlockHeaders, fh, buffer, usedBuffer);
    WRLD.WriteGRUP(WRLDSizes, WritableWorlds, fh, buffer, usedBuffer);
    DIAL.WriteGRUP(DIALSizes, fh, buffer, usedBuffer);
    QUST.WriteGRUP(QUSTSizes, eQUST, fh, buffer, usedBuffer);
    IDLE.WriteGRUP(IDLESizes, eIDLE, fh, buffer, usedBuffer);
    PACK.WriteGRUP(PACKSizes, ePACK, fh, buffer, usedBuffer);
    CSTY.WriteGRUP(CSTYSizes, eCSTY, fh, buffer, usedBuffer);
    LSCR.WriteGRUP(LSCRSizes, eLSCR, fh, buffer, usedBuffer);
    LVSP.WriteGRUP(LVSPSizes, eLVSP, fh, buffer, usedBuffer);
    ANIO.WriteGRUP(ANIOSizes, eANIO, fh, buffer, usedBuffer);
    WATR.WriteGRUP(WATRSizes, eWATR, fh, buffer, usedBuffer);
    EFSH.WriteGRUP(EFSHSizes, eEFSH, fh, buffer, usedBuffer);
    return -1;
    }
