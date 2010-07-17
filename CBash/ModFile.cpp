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

int ModFile::Open()
    {
    if(IsOpen || IsDummy)
        return 0;
    ReadHandler.open_ReadOnly(FileName);
    IsOpen = true;
    return 0;
    }

int ModFile::Close()
    {
    if(!IsOpen || IsDummy)
        return 0;
    ReadHandler.close();
    IsOpen = false;
    return 0;
    }

int ModFile::LoadTES4()
    {
    if(IsDummy || TES4.IsLoaded())
        return 0;
    Open();
    ReadHandler.set_used(8);
    ReadHandler.read(&TES4.flags, 4);
    ReadHandler.read(&TES4.formID, 4);
    ReadHandler.read(&TES4.flagsUnk, 4);
    if(TES4.IsLoaded())
        printf("_fIsLoaded Flag used!!!!: %08X\n", TES4.flags);
    TES4.recData = ReadHandler.getBuffer(20);
    TES4.Read(FormIDHandler);
    ReadHandler.set_used(TES4.GetSize());
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
    //printf("Begin Mod: %s\n", FileName);
    //Open();
    LoadedGRUPs = true;
    unsigned long GRUPSize;
    unsigned long GRUPLabel;
    boost::unordered_set<unsigned int> UsedFormIDs;
    //printf("%u\n", __LINE__);
    while(!ReadHandler.eof()){
        //printf("%u\n", __LINE__);
        ReadHandler.set_used(4); //Skip "GRUP"
        ReadHandler.read(&GRUPSize, 4);
        ReadHandler.read(&GRUPLabel, 4);
        ReadHandler.set_used(4); //Skip type (tops will all == 0)
        switch(GRUPLabel)
            {
            //ADD DEFINITIONS HERE
            case eIgGMST:
            case eGMST:
                ReadHandler.read(&GMST.stamp, 4);
                //printf("%u\n", __LINE__);
                GMST.Skim(Threads, ReadHandler, FormIDHandler, true, GRUPSize, UsedFormIDs);
                //printf("%u\n", __LINE__);
                break;
            case eIgGLOB:
            case eGLOB:
                ReadHandler.read(&GLOB.stamp, 4);
                GLOB.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgCLAS:
            case eCLAS:
                ReadHandler.read(&CLAS.stamp, 4);
                CLAS.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgFACT:
            case eFACT:
                ReadHandler.read(&FACT.stamp, 4);
                FACT.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgHAIR:
            case eHAIR:
                ReadHandler.read(&HAIR.stamp, 4);
                HAIR.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgEYES:
            case eEYES:
                ReadHandler.read(&EYES.stamp, 4);
                EYES.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgRACE:
            case eRACE:
                ReadHandler.read(&RACE.stamp, 4);
                RACE.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgSOUN:
            case eSOUN:
                ReadHandler.read(&SOUN.stamp, 4);
                SOUN.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgSKIL:
            case eSKIL:
                ReadHandler.read(&SKIL.stamp, 4);
                SKIL.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgMGEF:
            case eMGEF:
                ReadHandler.read(&MGEF.stamp, 4);
                MGEF.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgSCPT:
            case eSCPT:
                ReadHandler.read(&SCPT.stamp, 4);
                SCPT.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgLTEX:
            case eLTEX:
                ReadHandler.read(&LTEX.stamp, 4);
                LTEX.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgENCH:
            case eENCH:
                ReadHandler.read(&ENCH.stamp, 4);
                ENCH.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgSPEL:
            case eSPEL:
                ReadHandler.read(&SPEL.stamp, 4);
                SPEL.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgBSGN:
            case eBSGN:
                ReadHandler.read(&BSGN.stamp, 4);
                BSGN.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgACTI:
            case eACTI:
                ReadHandler.read(&ACTI.stamp, 4);
                ACTI.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgAPPA:
            case eAPPA:
                ReadHandler.read(&APPA.stamp, 4);
                APPA.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgARMO:
            case eARMO:
                ReadHandler.read(&ARMO.stamp, 4);
                ARMO.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgBOOK:
            case eBOOK:
                ReadHandler.read(&BOOK.stamp, 4);
                BOOK.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgCLOT:
            case eCLOT:
                ReadHandler.read(&CLOT.stamp, 4);
                CLOT.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgCONT:
            case eCONT:
                ReadHandler.read(&CONT.stamp, 4);
                CONT.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgDOOR:
            case eDOOR:
                ReadHandler.read(&DOOR.stamp, 4);
                DOOR.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgINGR:
            case eINGR:
                ReadHandler.read(&INGR.stamp, 4);
                INGR.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgLIGH:
            case eLIGH:
                ReadHandler.read(&LIGH.stamp, 4);
                LIGH.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgMISC:
            case eMISC:
                ReadHandler.read(&MISC.stamp, 4);
                MISC.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgSTAT:
            case eSTAT:
                ReadHandler.read(&STAT.stamp, 4);
                STAT.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgGRAS:
            case eGRAS:
                ReadHandler.read(&GRAS.stamp, 4);
                GRAS.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgTREE:
            case eTREE:
                ReadHandler.read(&TREE.stamp, 4);
                TREE.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgFLOR:
            case eFLOR:
                ReadHandler.read(&FLOR.stamp, 4);
                FLOR.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgFURN:
            case eFURN:
                ReadHandler.read(&FURN.stamp, 4);
                FURN.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgWEAP:
            case eWEAP:
                ReadHandler.read(&WEAP.stamp, 4);
                WEAP.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgAMMO:
            case eAMMO:
                ReadHandler.read(&AMMO.stamp, 4);
                AMMO.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgNPC_:
            case eNPC_:
                ReadHandler.read(&NPC_.stamp, 4);
                NPC_.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgCREA:
            case eCREA:
                ReadHandler.read(&CREA.stamp, 4);
                CREA.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgLVLC:
            case eLVLC:
                ReadHandler.read(&LVLC.stamp, 4);
                LVLC.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgSLGM:
            case eSLGM:
                ReadHandler.read(&SLGM.stamp, 4);
                SLGM.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgKEYM:
            case eKEYM:
                ReadHandler.read(&KEYM.stamp, 4);
                KEYM.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgALCH:
            case eALCH:
                ReadHandler.read(&ALCH.stamp, 4);
                ALCH.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgSBSP:
            case eSBSP:
                ReadHandler.read(&SBSP.stamp, 4);
                SBSP.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgSGST:
            case eSGST:
                ReadHandler.read(&SGST.stamp, 4);
                SGST.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgLVLI:
            case eLVLI:
                ReadHandler.read(&LVLI.stamp, 4);
                LVLI.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgWTHR:
            case eWTHR:
                ReadHandler.read(&WTHR.stamp, 4);
                WTHR.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgCLMT:
            case eCLMT:
                ReadHandler.read(&CLMT.stamp, 4);
                CLMT.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgREGN:
            case eREGN:
                ReadHandler.read(&REGN.stamp, 4);
                REGN.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgCELL:
            case eCELL:
                ReadHandler.read(&CELL.stamp, 4);
                CELL.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgWRLD:
            case eWRLD:
                ReadHandler.read(&WRLD.stamp, 4);
                WRLD.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgDIAL:
            case eDIAL:
                ReadHandler.read(&DIAL.stamp, 4);
                DIAL.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgQUST:
            case eQUST:
                ReadHandler.read(&QUST.stamp, 4);
                QUST.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgIDLE:
            case eIDLE:
                ReadHandler.read(&IDLE.stamp, 4);
                IDLE.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgPACK:
            case ePACK:
                ReadHandler.read(&PACK.stamp, 4);
                PACK.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgCSTY:
            case eCSTY:
                ReadHandler.read(&CSTY.stamp, 4);
                CSTY.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgLSCR:
            case eLSCR:
                ReadHandler.read(&LSCR.stamp, 4);
                LSCR.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgLVSP:
            case eLVSP:
                ReadHandler.read(&LVSP.stamp, 4);
                LVSP.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgANIO:
            case eANIO:
                ReadHandler.read(&ANIO.stamp, 4);
                ANIO.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgWATR:
            case eWATR:
                ReadHandler.read(&WATR.stamp, 4);
                WATR.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            case eIgEFSH:
            case eEFSH:
                ReadHandler.read(&EFSH.stamp, 4);
                EFSH.Skim(Threads, ReadHandler, FormIDHandler, FullLoad, GRUPSize, UsedFormIDs);
                break;
            default:
                printf("FileName = %s\n", FileName);
                printf("  Unimplemented GRUP = ");
                for(int x = 0;x < 4;x++)
                    printf("%c", ((char*)&GRUPLabel)[x]);
                printf("\n");
                return 0;
            }
        };
    //printf("End Mod: %s\n", FileName);
    return 1;
    }

unsigned int ModFile::UpdateReferences(unsigned int origFormID, unsigned int newFormID)
    {
    unsigned int count = 0;
    if(IsDummy)
        return count;
    //Commented out GRUPs don't contain any formIDs that could be updated.
    //count += GMST.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += GLOB.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += CLAS.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += FACT.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += HAIR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += EYES.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += RACE.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += SOUN.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += SKIL.UpdateReferences(origFormID, newFormID, FormIDHandler);
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
    //count += STAT.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += GRAS.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += TREE.UpdateReferences(origFormID, newFormID, FormIDHandler);
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
    //count += SBSP.UpdateReferences(origFormID, newFormID, FormIDHandler);
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
    //count += CSTY.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += LSCR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += LVSP.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += ANIO.UpdateReferences(origFormID, newFormID, FormIDHandler);
    count += WATR.UpdateReferences(origFormID, newFormID, FormIDHandler);
    //count += EFSH.UpdateReferences(origFormID, newFormID, FormIDHandler);
    return count;
    }
int ModFile::CleanMasters()
    {
    unsigned int cleaned = 0;
    _FormIDHandler TempHandler(FileName, TES4.MAST, TES4.HEDR.value.nextObject);
    TempHandler.SetLoadOrder(FormIDHandler.LoadOrder);
    TempHandler.CreateFormIDLookup(FormIDHandler.ExpandedIndex);
    std::vector<int> ToRemove;
    ToRemove.reserve(TES4.MAST.size());
    for(int p = 0; p < (unsigned char)TES4.MAST.size();++p)
        {
        //printf("Checking: %s\n", TES4.MAST[p].value);
        if(GMST.CheckMasters(p, TempHandler)) continue;
        if(GLOB.CheckMasters(p, TempHandler)) continue;
        if(CLAS.CheckMasters(p, TempHandler)) continue;
        if(FACT.CheckMasters(p, TempHandler)) continue;
        if(HAIR.CheckMasters(p, TempHandler)) continue;
        if(EYES.CheckMasters(p, TempHandler)) continue;
        if(RACE.CheckMasters(p, TempHandler)) continue;
        if(SOUN.CheckMasters(p, TempHandler)) continue;
        if(SKIL.CheckMasters(p, TempHandler)) continue;
        if(MGEF.CheckMasters(p, TempHandler)) continue;
        if(SCPT.CheckMasters(p, TempHandler)) continue;
        if(LTEX.CheckMasters(p, TempHandler)) continue;
        if(ENCH.CheckMasters(p, TempHandler)) continue;
        if(SPEL.CheckMasters(p, TempHandler)) continue;
        if(BSGN.CheckMasters(p, TempHandler)) continue;
        if(ACTI.CheckMasters(p, TempHandler)) continue;
        if(APPA.CheckMasters(p, TempHandler)) continue;
        if(ARMO.CheckMasters(p, TempHandler)) continue;
        if(BOOK.CheckMasters(p, TempHandler)) continue;
        if(CLOT.CheckMasters(p, TempHandler)) continue;
        if(CONT.CheckMasters(p, TempHandler)) continue;
        if(DOOR.CheckMasters(p, TempHandler)) continue;
        if(INGR.CheckMasters(p, TempHandler)) continue;
        if(LIGH.CheckMasters(p, TempHandler)) continue;
        if(MISC.CheckMasters(p, TempHandler)) continue;
        if(STAT.CheckMasters(p, TempHandler)) continue;
        if(GRAS.CheckMasters(p, TempHandler)) continue;
        if(TREE.CheckMasters(p, TempHandler)) continue;
        if(FLOR.CheckMasters(p, TempHandler)) continue;
        if(FURN.CheckMasters(p, TempHandler)) continue;
        if(WEAP.CheckMasters(p, TempHandler)) continue;
        if(AMMO.CheckMasters(p, TempHandler)) continue;
        if(NPC_.CheckMasters(p, TempHandler)) continue;
        if(CREA.CheckMasters(p, TempHandler)) continue;
        if(LVLC.CheckMasters(p, TempHandler)) continue;
        if(SLGM.CheckMasters(p, TempHandler)) continue;
        if(KEYM.CheckMasters(p, TempHandler)) continue;
        if(ALCH.CheckMasters(p, TempHandler)) continue;
        if(SBSP.CheckMasters(p, TempHandler)) continue;
        if(SGST.CheckMasters(p, TempHandler)) continue;
        if(LVLI.CheckMasters(p, TempHandler)) continue;
        if(WTHR.CheckMasters(p, TempHandler)) continue;
        if(CLMT.CheckMasters(p, TempHandler)) continue;
        if(REGN.CheckMasters(p, TempHandler)) continue;
        if(CELL.CheckMasters(p, TempHandler)) continue;
        if(WRLD.CheckMasters(p, TempHandler)) continue;
        if(DIAL.CheckMasters(p, TempHandler)) continue;
        if(QUST.CheckMasters(p, TempHandler)) continue;
        if(IDLE.CheckMasters(p, TempHandler)) continue;
        if(PACK.CheckMasters(p, TempHandler)) continue;
        if(CSTY.CheckMasters(p, TempHandler)) continue;
        if(LSCR.CheckMasters(p, TempHandler)) continue;
        if(LVSP.CheckMasters(p, TempHandler)) continue;
        if(ANIO.CheckMasters(p, TempHandler)) continue;
        if(WATR.CheckMasters(p, TempHandler)) continue;
        if(EFSH.CheckMasters(p, TempHandler)) continue;
        //printf("Removing: %s\n", TES4.MAST[p].value);
        //Master not used, so remove it.
        ToRemove.push_back(p);
        //TES4.MAST.erase(TES4.MAST.begin() + p);
        //FormIDHandler.UpdateFormIDLookup();
        //--p; //Keep the value from incrementing
        ++cleaned;
        }
    if(cleaned)
        {
        for(int p = (int)ToRemove.size() - 1; p >= 0; --p)
            TES4.MAST.erase(TES4.MAST.begin() + ToRemove[p]);
        FormIDHandler.UpdateFormIDLookup();
        }
    return cleaned;
    }

int ModFile::Unload()
    {
    //GMSTs are always loaded.
    //GMST.Unload();
    GLOB.Unload();
    CLAS.Unload();
    FACT.Unload();
    HAIR.Unload();
    EYES.Unload();
    RACE.Unload();
    SOUN.Unload();
    SKIL.Unload();
    MGEF.Unload();
    SCPT.Unload();
    LTEX.Unload();
    ENCH.Unload();
    SPEL.Unload();
    BSGN.Unload();
    ACTI.Unload();
    APPA.Unload();
    ARMO.Unload();
    BOOK.Unload();
    CLOT.Unload();
    CONT.Unload();
    DOOR.Unload();
    INGR.Unload();
    LIGH.Unload();
    MISC.Unload();
    STAT.Unload();
    GRAS.Unload();
    TREE.Unload();
    FLOR.Unload();
    FURN.Unload();
    WEAP.Unload();
    AMMO.Unload();
    NPC_.Unload();
    CREA.Unload();
    LVLC.Unload();
    SLGM.Unload();
    KEYM.Unload();
    ALCH.Unload();
    SBSP.Unload();
    SGST.Unload();
    LVLI.Unload();
    WTHR.Unload();
    CLMT.Unload();
    REGN.Unload();
    CELL.Unload();
    WRLD.Unload();
    DIAL.Unload();
    QUST.Unload();
    IDLE.Unload();
    PACK.Unload();
    CSTY.Unload();
    LSCR.Unload();
    LVSP.Unload();
    ANIO.Unload();
    WATR.Unload();
    EFSH.Unload();
    return 0;
    }

int ModFile::Save(_FileHandler &SaveHandler, bool CloseMod)
    {
    unsigned int formCount = 0;
    if(IsDummy)
        return -1;

    TES4.Write(SaveHandler, FormIDHandler);

    //ADD DEFINITIONS HERE
    formCount += GMST.WriteGRUP(eGMST, SaveHandler, FormIDHandler, CloseMod);
    formCount += GLOB.WriteGRUP(eGLOB, SaveHandler, FormIDHandler, CloseMod);
    formCount += CLAS.WriteGRUP(eCLAS, SaveHandler, FormIDHandler, CloseMod);
    formCount += FACT.WriteGRUP(eFACT, SaveHandler, FormIDHandler, CloseMod);
    formCount += HAIR.WriteGRUP(eHAIR, SaveHandler, FormIDHandler, CloseMod);
    formCount += EYES.WriteGRUP(eEYES, SaveHandler, FormIDHandler, CloseMod);
    formCount += RACE.WriteGRUP(eRACE, SaveHandler, FormIDHandler, CloseMod);
    formCount += SOUN.WriteGRUP(eSOUN, SaveHandler, FormIDHandler, CloseMod);
    formCount += SKIL.WriteGRUP(eSKIL, SaveHandler, FormIDHandler, CloseMod);
    formCount += MGEF.WriteGRUP(eMGEF, SaveHandler, FormIDHandler, CloseMod);
    formCount += SCPT.WriteGRUP(eSCPT, SaveHandler, FormIDHandler, CloseMod);
    formCount += LTEX.WriteGRUP(eLTEX, SaveHandler, FormIDHandler, CloseMod);
    formCount += ENCH.WriteGRUP(eENCH, SaveHandler, FormIDHandler, CloseMod);
    formCount += SPEL.WriteGRUP(eSPEL, SaveHandler, FormIDHandler, CloseMod);
    formCount += BSGN.WriteGRUP(eBSGN, SaveHandler, FormIDHandler, CloseMod);
    formCount += ACTI.WriteGRUP(eACTI, SaveHandler, FormIDHandler, CloseMod);
    formCount += APPA.WriteGRUP(eAPPA, SaveHandler, FormIDHandler, CloseMod);
    formCount += ARMO.WriteGRUP(eARMO, SaveHandler, FormIDHandler, CloseMod);
    formCount += BOOK.WriteGRUP(eBOOK, SaveHandler, FormIDHandler, CloseMod);
    formCount += CLOT.WriteGRUP(eCLOT, SaveHandler, FormIDHandler, CloseMod);
    formCount += CONT.WriteGRUP(eCONT, SaveHandler, FormIDHandler, CloseMod);
    formCount += DOOR.WriteGRUP(eDOOR, SaveHandler, FormIDHandler, CloseMod);
    formCount += INGR.WriteGRUP(eINGR, SaveHandler, FormIDHandler, CloseMod);
    formCount += LIGH.WriteGRUP(eLIGH, SaveHandler, FormIDHandler, CloseMod);
    formCount += MISC.WriteGRUP(eMISC, SaveHandler, FormIDHandler, CloseMod);
    formCount += STAT.WriteGRUP(eSTAT, SaveHandler, FormIDHandler, CloseMod);
    formCount += GRAS.WriteGRUP(eGRAS, SaveHandler, FormIDHandler, CloseMod);
    formCount += TREE.WriteGRUP(eTREE, SaveHandler, FormIDHandler, CloseMod);
    formCount += FLOR.WriteGRUP(eFLOR, SaveHandler, FormIDHandler, CloseMod);
    formCount += FURN.WriteGRUP(eFURN, SaveHandler, FormIDHandler, CloseMod);
    formCount += WEAP.WriteGRUP(eWEAP, SaveHandler, FormIDHandler, CloseMod);
    formCount += AMMO.WriteGRUP(eAMMO, SaveHandler, FormIDHandler, CloseMod);
    formCount += NPC_.WriteGRUP(eNPC_, SaveHandler, FormIDHandler, CloseMod);
    formCount += CREA.WriteGRUP(eCREA, SaveHandler, FormIDHandler, CloseMod);
    formCount += LVLC.WriteGRUP(eLVLC, SaveHandler, FormIDHandler, CloseMod);
    formCount += SLGM.WriteGRUP(eSLGM, SaveHandler, FormIDHandler, CloseMod);
    formCount += KEYM.WriteGRUP(eKEYM, SaveHandler, FormIDHandler, CloseMod);
    formCount += ALCH.WriteGRUP(eALCH, SaveHandler, FormIDHandler, CloseMod);
    formCount += SBSP.WriteGRUP(eSBSP, SaveHandler, FormIDHandler, CloseMod);
    formCount += SGST.WriteGRUP(eSGST, SaveHandler, FormIDHandler, CloseMod);
    formCount += LVLI.WriteGRUP(eLVLI, SaveHandler, FormIDHandler, CloseMod);
    formCount += WTHR.WriteGRUP(eWTHR, SaveHandler, FormIDHandler, CloseMod);
    formCount += CLMT.WriteGRUP(eCLMT, SaveHandler, FormIDHandler, CloseMod);
    formCount += REGN.WriteGRUP(eREGN, SaveHandler, FormIDHandler, CloseMod);
    formCount += CELL.WriteGRUP(SaveHandler, FormIDHandler, CloseMod);
    formCount += WRLD.WriteGRUP(SaveHandler, FormIDHandler, CloseMod);
    formCount += DIAL.WriteGRUP(SaveHandler, FormIDHandler, CloseMod);
    formCount += QUST.WriteGRUP(eQUST, SaveHandler, FormIDHandler, CloseMod);
    formCount += IDLE.WriteGRUP(eIDLE, SaveHandler, FormIDHandler, CloseMod);
    formCount += PACK.WriteGRUP(ePACK, SaveHandler, FormIDHandler, CloseMod);
    formCount += CSTY.WriteGRUP(eCSTY, SaveHandler, FormIDHandler, CloseMod);
    formCount += LSCR.WriteGRUP(eLSCR, SaveHandler, FormIDHandler, CloseMod);
    formCount += LVSP.WriteGRUP(eLVSP, SaveHandler, FormIDHandler, CloseMod);
    formCount += ANIO.WriteGRUP(eANIO, SaveHandler, FormIDHandler, CloseMod);
    formCount += WATR.WriteGRUP(eWATR, SaveHandler, FormIDHandler, CloseMod);
    formCount += EFSH.WriteGRUP(eEFSH, SaveHandler, FormIDHandler, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    SaveHandler.writeAt(30, &formCount, 4);
    if(CloseMod)
        Close();
    return 0;
    }
