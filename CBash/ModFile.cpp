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
    if(IsOpen || IsDummy)
        return 0;
    try
        {
        m_region = new mapped_region(file_mapping(FileName, read_only), read_only);
        }
    catch(interprocess_exception &ex)
        {
        printf("Exception raised: %s\nUnable to memory map '%s'.\n", ex.what(), FileName);
        throw;
        return -1;
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
    if(!IsOpen || IsDummy)
        return 0;
    delete m_region;
    m_region = NULL;
    IsOpen = false;
    return 0;
    }

int ModFile::LoadTES4()
    {
    unsigned int curPos = 8;
    if(IsDummy || TES4.IsLoaded())
        return 0;
    Open();
    _readBuffer(&TES4.flags, fileBuffer, 4, curPos);
    _readBuffer(&TES4.formID, fileBuffer, 4, curPos);
    _readBuffer(&TES4.flagsUnk, fileBuffer, 4, curPos);
    if(TES4.IsLoaded())
        printf("Flag used!!!!: %08X\n", TES4.flagsUnk);
    TES4.recData = &fileBuffer[20];
    TES4.Read(FormIDHandler);
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
    if(IsDummy || !TES4.IsLoaded() || LoadedGRUPs)
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

unsigned int ModFile::UpdateReferences(unsigned int origFormID, unsigned int newFormID)
    {
    unsigned int count = 0;
    if(IsDummy)
        return count;
    count += GMST.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += GLOB.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += CLAS.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += FACT.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += HAIR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += EYES.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += RACE.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += SOUN.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += SKIL.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += MGEF.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += SCPT.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += LTEX.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += ENCH.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += SPEL.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += BSGN.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += ACTI.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += APPA.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += ARMO.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += BOOK.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += CLOT.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += CONT.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += DOOR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += INGR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += LIGH.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += MISC.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += STAT.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += GRAS.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += TREE.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += FLOR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += FURN.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += WEAP.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += AMMO.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += NPC_.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += CREA.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += LVLC.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += SLGM.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += KEYM.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += ALCH.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += SBSP.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += SGST.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += LVLI.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += WTHR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += CLMT.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += REGN.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += CELL.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += WRLD.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += DIAL.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += QUST.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += IDLE.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += PACK.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += CSTY.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += LSCR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += LVSP.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += ANIO.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += WATR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += EFSH.UpdateReferences(origFormID, newFormID, FormIDHandler);
    return count;
    }
int ModFile::CleanMasters()
    {
    unsigned int cleaned = 0;
    for(unsigned char p = 0; p < (unsigned char)TES4.MAST.size();++p)
        {
        if(GMST.CheckMasters(p, FormIDHandler)) break;
        if(GLOB.CheckMasters(p, FormIDHandler)) break;
        if(CLAS.CheckMasters(p, FormIDHandler)) break;
        if(FACT.CheckMasters(p, FormIDHandler)) break;
        if(HAIR.CheckMasters(p, FormIDHandler)) break;
        if(EYES.CheckMasters(p, FormIDHandler)) break;
        if(RACE.CheckMasters(p, FormIDHandler)) break;
        if(SOUN.CheckMasters(p, FormIDHandler)) break;
        if(SKIL.CheckMasters(p, FormIDHandler)) break;
        if(MGEF.CheckMasters(p, FormIDHandler)) break;
        if(SCPT.CheckMasters(p, FormIDHandler)) break;
        if(LTEX.CheckMasters(p, FormIDHandler)) break;
        if(ENCH.CheckMasters(p, FormIDHandler)) break;
        if(SPEL.CheckMasters(p, FormIDHandler)) break;
        if(BSGN.CheckMasters(p, FormIDHandler)) break;
        if(ACTI.CheckMasters(p, FormIDHandler)) break;
        if(APPA.CheckMasters(p, FormIDHandler)) break;
        if(ARMO.CheckMasters(p, FormIDHandler)) break;
        if(BOOK.CheckMasters(p, FormIDHandler)) break;
        if(CLOT.CheckMasters(p, FormIDHandler)) break;
        if(CONT.CheckMasters(p, FormIDHandler)) break;
        if(DOOR.CheckMasters(p, FormIDHandler)) break;
        if(INGR.CheckMasters(p, FormIDHandler)) break;
        if(LIGH.CheckMasters(p, FormIDHandler)) break;
        if(MISC.CheckMasters(p, FormIDHandler)) break;
        if(STAT.CheckMasters(p, FormIDHandler)) break;
        if(GRAS.CheckMasters(p, FormIDHandler)) break;
        if(TREE.CheckMasters(p, FormIDHandler)) break;
        if(FLOR.CheckMasters(p, FormIDHandler)) break;
        if(FURN.CheckMasters(p, FormIDHandler)) break;
        if(WEAP.CheckMasters(p, FormIDHandler)) break;
        if(AMMO.CheckMasters(p, FormIDHandler)) break;
        if(NPC_.CheckMasters(p, FormIDHandler)) break;
        if(CREA.CheckMasters(p, FormIDHandler)) break;
        if(LVLC.CheckMasters(p, FormIDHandler)) break;
        if(SLGM.CheckMasters(p, FormIDHandler)) break;
        if(KEYM.CheckMasters(p, FormIDHandler)) break;
        if(ALCH.CheckMasters(p, FormIDHandler)) break;
        if(SBSP.CheckMasters(p, FormIDHandler)) break;
        if(SGST.CheckMasters(p, FormIDHandler)) break;
        if(LVLI.CheckMasters(p, FormIDHandler)) break;
        if(WTHR.CheckMasters(p, FormIDHandler)) break;
        if(CLMT.CheckMasters(p, FormIDHandler)) break;
        if(REGN.CheckMasters(p, FormIDHandler)) break;
        if(CELL.CheckMasters(p, FormIDHandler)) break;
        if(WRLD.CheckMasters(p, FormIDHandler)) break;
        if(DIAL.CheckMasters(p, FormIDHandler)) break;
        if(QUST.CheckMasters(p, FormIDHandler)) break;
        if(IDLE.CheckMasters(p, FormIDHandler)) break;
        if(PACK.CheckMasters(p, FormIDHandler)) break;
        if(CSTY.CheckMasters(p, FormIDHandler)) break;
        if(LSCR.CheckMasters(p, FormIDHandler)) break;
        if(LVSP.CheckMasters(p, FormIDHandler)) break;
        if(ANIO.CheckMasters(p, FormIDHandler)) break;
        if(WATR.CheckMasters(p, FormIDHandler)) break;
        if(EFSH.CheckMasters(p, FormIDHandler)) break;
        //Master not used, so remove it.
        TES4.MAST.erase(TES4.MAST.begin() + p);
        --p; //Keep the value from incrementing
        ++cleaned;
        }
    return cleaned;
    }

int ModFile::Save(FileBuffer &buffer, bool CloseMod)
    {
    unsigned int formCount = 0;
    if(IsDummy)
        return -1;

    {
    WritableRecord WriteTES4;
    TES4.Write(WriteTES4, FormIDHandler);
    buffer.write(WriteTES4);
    }

    //ADD DEFINITIONS HERE
    formCount += GMST.WriteGRUP(eGMST, buffer, CloseMod, FormIDHandler);
    formCount += GLOB.WriteGRUP(eGLOB, buffer, CloseMod, FormIDHandler);
    formCount += CLAS.WriteGRUP(eCLAS, buffer, CloseMod, FormIDHandler);
    formCount += FACT.WriteGRUP(eFACT, buffer, CloseMod, FormIDHandler);
    formCount += HAIR.WriteGRUP(eHAIR, buffer, CloseMod, FormIDHandler);
    formCount += EYES.WriteGRUP(eEYES, buffer, CloseMod, FormIDHandler);
    formCount += RACE.WriteGRUP(eRACE, buffer, CloseMod, FormIDHandler);
    formCount += SOUN.WriteGRUP(eSOUN, buffer, CloseMod, FormIDHandler);
    formCount += SKIL.WriteGRUP(eSKIL, buffer, CloseMod, FormIDHandler);
    formCount += MGEF.WriteGRUP(eMGEF, buffer, CloseMod, FormIDHandler);
    formCount += SCPT.WriteGRUP(eSCPT, buffer, CloseMod, FormIDHandler);
    formCount += LTEX.WriteGRUP(eLTEX, buffer, CloseMod, FormIDHandler);
    formCount += ENCH.WriteGRUP(eENCH, buffer, CloseMod, FormIDHandler);
    formCount += SPEL.WriteGRUP(eSPEL, buffer, CloseMod, FormIDHandler);
    formCount += BSGN.WriteGRUP(eBSGN, buffer, CloseMod, FormIDHandler);
    formCount += ACTI.WriteGRUP(eACTI, buffer, CloseMod, FormIDHandler);
    formCount += APPA.WriteGRUP(eAPPA, buffer, CloseMod, FormIDHandler);
    formCount += ARMO.WriteGRUP(eARMO, buffer, CloseMod, FormIDHandler);
    formCount += BOOK.WriteGRUP(eBOOK, buffer, CloseMod, FormIDHandler);
    formCount += CLOT.WriteGRUP(eCLOT, buffer, CloseMod, FormIDHandler);
    formCount += CONT.WriteGRUP(eCONT, buffer, CloseMod, FormIDHandler);
    formCount += DOOR.WriteGRUP(eDOOR, buffer, CloseMod, FormIDHandler);
    formCount += INGR.WriteGRUP(eINGR, buffer, CloseMod, FormIDHandler);
    formCount += LIGH.WriteGRUP(eLIGH, buffer, CloseMod, FormIDHandler);
    formCount += MISC.WriteGRUP(eMISC, buffer, CloseMod, FormIDHandler);
    formCount += STAT.WriteGRUP(eSTAT, buffer, CloseMod, FormIDHandler);
    formCount += GRAS.WriteGRUP(eGRAS, buffer, CloseMod, FormIDHandler);
    formCount += TREE.WriteGRUP(eTREE, buffer, CloseMod, FormIDHandler);
    formCount += FLOR.WriteGRUP(eFLOR, buffer, CloseMod, FormIDHandler);
    formCount += FURN.WriteGRUP(eFURN, buffer, CloseMod, FormIDHandler);
    formCount += WEAP.WriteGRUP(eWEAP, buffer, CloseMod, FormIDHandler);
    formCount += AMMO.WriteGRUP(eAMMO, buffer, CloseMod, FormIDHandler);
    formCount += NPC_.WriteGRUP(eNPC_, buffer, CloseMod, FormIDHandler);
    formCount += CREA.WriteGRUP(eCREA, buffer, CloseMod, FormIDHandler);
    formCount += LVLC.WriteGRUP(eLVLC, buffer, CloseMod, FormIDHandler);
    formCount += SLGM.WriteGRUP(eSLGM, buffer, CloseMod, FormIDHandler);
    formCount += KEYM.WriteGRUP(eKEYM, buffer, CloseMod, FormIDHandler);
    formCount += ALCH.WriteGRUP(eALCH, buffer, CloseMod, FormIDHandler);
    formCount += SBSP.WriteGRUP(eSBSP, buffer, CloseMod, FormIDHandler);
    formCount += SGST.WriteGRUP(eSGST, buffer, CloseMod, FormIDHandler);
    formCount += LVLI.WriteGRUP(eLVLI, buffer, CloseMod, FormIDHandler);
    formCount += WTHR.WriteGRUP(eWTHR, buffer, CloseMod, FormIDHandler);
    formCount += CLMT.WriteGRUP(eCLMT, buffer, CloseMod, FormIDHandler);
    formCount += REGN.WriteGRUP(eREGN, buffer, CloseMod, FormIDHandler);
    formCount += CELL.WriteGRUP(buffer, CloseMod, FormIDHandler);
    formCount += WRLD.WriteGRUP(buffer, CloseMod, FormIDHandler);
    formCount += DIAL.WriteGRUP(buffer, CloseMod, FormIDHandler);
    formCount += QUST.WriteGRUP(eQUST, buffer, CloseMod, FormIDHandler);
    formCount += IDLE.WriteGRUP(eIDLE, buffer, CloseMod, FormIDHandler);
    formCount += PACK.WriteGRUP(ePACK, buffer, CloseMod, FormIDHandler);
    formCount += CSTY.WriteGRUP(eCSTY, buffer, CloseMod, FormIDHandler);
    formCount += LSCR.WriteGRUP(eLSCR, buffer, CloseMod, FormIDHandler);
    formCount += LVSP.WriteGRUP(eLVSP, buffer, CloseMod, FormIDHandler);
    formCount += ANIO.WriteGRUP(eANIO, buffer, CloseMod, FormIDHandler);
    formCount += WATR.WriteGRUP(eWATR, buffer, CloseMod, FormIDHandler);
    formCount += EFSH.WriteGRUP(eEFSH, buffer, CloseMod, FormIDHandler);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    buffer.seek(30 , SEEK_SET);
    buffer.write(&formCount, 4);
    buffer.flush();
    if(CloseMod)
        Close();

    return 0;
    }
