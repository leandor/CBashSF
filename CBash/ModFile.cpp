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
    if(Settings.IsOpen || Settings.IsDummy)
        return 0;
    ReadHandler.open_ReadOnly(FileName);
    Settings.IsOpen = true;
    return 0;
    }

int ModFile::Close()
    {
    if(!Settings.IsOpen || Settings.IsDummy)
        return 0;
    ReadHandler.close();
    Settings.IsOpen = false;
    return 0;
    }

int ModFile::LoadTES4()
    {
    if(Settings.IsDummy || TES4.IsLoaded())
        return 0;
    Open();
    ReadHandler.set_used(8);
    ReadHandler.read(&TES4.flags, 4);
    ReadHandler.read(&TES4.formID, 4);
    ReadHandler.read(&TES4.flagsUnk, 4);
    if(TES4.IsLoaded())
        printf("_fIsLoaded Flag used!!!!: %08X\n", TES4.flags);
    TES4.recData = ReadHandler.getBuffer(20);
    RecordReader reader(FormIDHandler);
    reader.Accept(TES4);
    ReadHandler.set_used(TES4.GetSize());
    TES4.recData = NULL;
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
    if(Settings.IsDummy || !TES4.IsLoaded() || Settings.LoadedGRUPs)
        return 0;
    //printf("Begin Mod: %s\n", FileName);
    //Open();
    Settings.LoadedGRUPs = true;
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

unsigned int ModFile::GetNumRecords(const unsigned int &RecordType)
    {
    switch(RecordType)
        {
        case eGLOB:
            return (unsigned int)GLOB.Records.size();
        case eCLAS:
            return (unsigned int)CLAS.Records.size();
        case eFACT:
            return (unsigned int)FACT.Records.size();
        case eHAIR:
            return (unsigned int)HAIR.Records.size();
        case eEYES:
            return (unsigned int)EYES.Records.size();
        case eRACE:
            return (unsigned int)RACE.Records.size();
        case eSOUN:
            return (unsigned int)SOUN.Records.size();
        case eSKIL:
            return (unsigned int)SKIL.Records.size();
        case eMGEF:
            return (unsigned int)MGEF.Records.size();
        case eSCPT:
            return (unsigned int)SCPT.Records.size();
        case eLTEX:
            return (unsigned int)LTEX.Records.size();
        case eENCH:
            return (unsigned int)ENCH.Records.size();
        case eSPEL:
            return (unsigned int)SPEL.Records.size();
        case eBSGN:
            return (unsigned int)BSGN.Records.size();
        case eACTI:
            return (unsigned int)ACTI.Records.size();
        case eAPPA:
            return (unsigned int)APPA.Records.size();
        case eARMO:
            return (unsigned int)ARMO.Records.size();
        case eBOOK:
            return (unsigned int)BOOK.Records.size();
        case eCLOT:
            return (unsigned int)CLOT.Records.size();
        case eCONT:
            return (unsigned int)CONT.Records.size();
        case eDOOR:
            return (unsigned int)DOOR.Records.size();
        case eINGR:
            return (unsigned int)INGR.Records.size();
        case eLIGH:
            return (unsigned int)LIGH.Records.size();
        case eMISC:
            return (unsigned int)MISC.Records.size();
        case eSTAT:
            return (unsigned int)STAT.Records.size();
        case eGRAS:
            return (unsigned int)GRAS.Records.size();
        case eTREE:
            return (unsigned int)TREE.Records.size();
        case eFLOR:
            return (unsigned int)FLOR.Records.size();
        case eFURN:
            return (unsigned int)FURN.Records.size();
        case eWEAP:
            return (unsigned int)WEAP.Records.size();
        case eAMMO:
            return (unsigned int)AMMO.Records.size();
        case eNPC_:
            return (unsigned int)NPC_.Records.size();
        case eCREA:
            return (unsigned int)CREA.Records.size();
        case eLVLC:
            return (unsigned int)LVLC.Records.size();
        case eSLGM:
            return (unsigned int)SLGM.Records.size();
        case eKEYM:
            return (unsigned int)KEYM.Records.size();
        case eALCH:
            return (unsigned int)ALCH.Records.size();
        case eSBSP:
            return (unsigned int)SBSP.Records.size();
        case eSGST:
            return (unsigned int)SGST.Records.size();
        case eLVLI:
            return (unsigned int)LVLI.Records.size();
        case eWTHR:
            return (unsigned int)WTHR.Records.size();
        case eCLMT:
            return (unsigned int)CLMT.Records.size();
        case eREGN:
            return (unsigned int)REGN.Records.size();
        case eCELL:
            return (unsigned int)CELL.Records.size();
        case eWRLD:
            return (unsigned int)WRLD.Records.size();
        case eDIAL:
            return (unsigned int)DIAL.Records.size();
        ///////////////////////////////////////////////
        //SubRecords are counted via GetFIDFieldArraySize API function(s)
        //case ePGRD:
        //    break;
        //case eLAND:
        //    break;
        //case eACHR:
        //    break;
        //case eACRE:
        //    break;
        //case eREFR:
        //    break;
        //case eROAD:
        //    break;
        //case eINFO:
        //    break;
        ///////////////////////////////////////////////
        case eQUST:
            return (unsigned int)QUST.Records.size();
        case eIDLE:
            return (unsigned int)IDLE.Records.size();
        case ePACK:
            return (unsigned int)PACK.Records.size();
        case eCSTY:
            return (unsigned int)CSTY.Records.size();
        case eLSCR:
            return (unsigned int)LSCR.Records.size();
        case eLVSP:
            return (unsigned int)LVSP.Records.size();
        case eANIO:
            return (unsigned int)ANIO.Records.size();
        case eWATR:
            return (unsigned int)WATR.Records.size();
        case eEFSH:
            return (unsigned int)EFSH.Records.size();
        default:
            printf("Error counting records: %i\n", RecordType);
            break;
        }
    return 0;
    }

Record * ModFile::CreateRecord(const unsigned int &RecordType, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options)
    {
    Record *newRecord = NULL;

    switch(RecordType)
        {
        case eGLOB:
            GLOB.Records.push_back(new GLOBRecord((GLOBRecord *)SourceRecord));
            newRecord = GLOB.Records.back();
            break;
        case eCLAS:
            CLAS.Records.push_back(new CLASRecord((CLASRecord *)SourceRecord));
            newRecord = CLAS.Records.back();
            break;
        case eFACT:
            FACT.Records.push_back(new FACTRecord((FACTRecord *)SourceRecord));
            newRecord = FACT.Records.back();
            break;
        case eHAIR:
            HAIR.Records.push_back(new HAIRRecord((HAIRRecord *)SourceRecord));
            newRecord = HAIR.Records.back();
            break;
        case eEYES:
            EYES.Records.push_back(new EYESRecord((EYESRecord *)SourceRecord));
            newRecord = EYES.Records.back();
            break;
        case eRACE:
            RACE.Records.push_back(new RACERecord((RACERecord *)SourceRecord));
            newRecord = RACE.Records.back();
            break;
        case eSOUN:
            SOUN.Records.push_back(new SOUNRecord((SOUNRecord *)SourceRecord));
            newRecord = SOUN.Records.back();
            break;
        case eSKIL:
            SKIL.Records.push_back(new SKILRecord((SKILRecord *)SourceRecord));
            newRecord = SKIL.Records.back();
            break;
        case eMGEF:
            MGEF.Records.push_back(new MGEFRecord((MGEFRecord *)SourceRecord));
            newRecord = MGEF.Records.back();
            break;
        case eSCPT:
            SCPT.Records.push_back(new SCPTRecord((SCPTRecord *)SourceRecord));
            newRecord = SCPT.Records.back();
            break;
        case eLTEX:
            LTEX.Records.push_back(new LTEXRecord((LTEXRecord *)SourceRecord));
            newRecord = LTEX.Records.back();
            break;
        case eENCH:
            ENCH.Records.push_back(new ENCHRecord((ENCHRecord *)SourceRecord));
            newRecord = ENCH.Records.back();
            break;
        case eSPEL:
            SPEL.Records.push_back(new SPELRecord((SPELRecord *)SourceRecord));
            newRecord = SPEL.Records.back();
            break;
        case eBSGN:
            BSGN.Records.push_back(new BSGNRecord((BSGNRecord *)SourceRecord));
            newRecord = BSGN.Records.back();
            break;
        case eACTI:
            ACTI.Records.push_back(new ACTIRecord((ACTIRecord *)SourceRecord));
            newRecord = ACTI.Records.back();
            break;
        case eAPPA:
            APPA.Records.push_back(new APPARecord((APPARecord *)SourceRecord));
            newRecord = APPA.Records.back();
            break;
        case eARMO:
            ARMO.Records.push_back(new ARMORecord((ARMORecord *)SourceRecord));
            newRecord = ARMO.Records.back();
            break;
        case eBOOK:
            BOOK.Records.push_back(new BOOKRecord((BOOKRecord *)SourceRecord));
            newRecord = BOOK.Records.back();
            break;
        case eCLOT:
            CLOT.Records.push_back(new CLOTRecord((CLOTRecord *)SourceRecord));
            newRecord = CLOT.Records.back();
            break;
        case eCONT:
            CONT.Records.push_back(new CONTRecord((CONTRecord *)SourceRecord));
            newRecord = CONT.Records.back();
            break;
        case eDOOR:
            DOOR.Records.push_back(new DOORRecord((DOORRecord *)SourceRecord));
            newRecord = DOOR.Records.back();
            break;
        case eINGR:
            INGR.Records.push_back(new INGRRecord((INGRRecord *)SourceRecord));
            newRecord = INGR.Records.back();
            break;
        case eLIGH:
            LIGH.Records.push_back(new LIGHRecord((LIGHRecord *)SourceRecord));
            newRecord = LIGH.Records.back();
            break;
        case eMISC:
            MISC.Records.push_back(new MISCRecord((MISCRecord *)SourceRecord));
            newRecord = MISC.Records.back();
            break;
        case eSTAT:
            STAT.Records.push_back(new STATRecord((STATRecord *)SourceRecord));
            newRecord = STAT.Records.back();
            break;
        case eGRAS:
            GRAS.Records.push_back(new GRASRecord((GRASRecord *)SourceRecord));
            newRecord = GRAS.Records.back();
            break;
        case eTREE:
            TREE.Records.push_back(new TREERecord((TREERecord *)SourceRecord));
            newRecord = TREE.Records.back();
            break;
        case eFLOR:
            FLOR.Records.push_back(new FLORRecord((FLORRecord *)SourceRecord));
            newRecord = FLOR.Records.back();
            break;
        case eFURN:
            FURN.Records.push_back(new FURNRecord((FURNRecord *)SourceRecord));
            newRecord = FURN.Records.back();
            break;
        case eWEAP:
            WEAP.Records.push_back(new WEAPRecord((WEAPRecord *)SourceRecord));
            newRecord = WEAP.Records.back();
            break;
        case eAMMO:
            AMMO.Records.push_back(new AMMORecord((AMMORecord *)SourceRecord));
            newRecord = AMMO.Records.back();
            break;
        case eNPC_:
            NPC_.Records.push_back(new NPC_Record((NPC_Record *)SourceRecord));
            newRecord = NPC_.Records.back();
            break;
        case eCREA:
            CREA.Records.push_back(new CREARecord((CREARecord *)SourceRecord));
            newRecord = CREA.Records.back();
            break;
        case eLVLC:
            LVLC.Records.push_back(new LVLCRecord((LVLCRecord *)SourceRecord));
            newRecord = LVLC.Records.back();
            break;
        case eSLGM:
            SLGM.Records.push_back(new SLGMRecord((SLGMRecord *)SourceRecord));
            newRecord = SLGM.Records.back();
            break;
        case eKEYM:
            KEYM.Records.push_back(new KEYMRecord((KEYMRecord *)SourceRecord));
            newRecord = KEYM.Records.back();
            break;
        case eALCH:
            ALCH.Records.push_back(new ALCHRecord((ALCHRecord *)SourceRecord));
            newRecord = ALCH.Records.back();
            break;
        case eSBSP:
            SBSP.Records.push_back(new SBSPRecord((SBSPRecord *)SourceRecord));
            newRecord = SBSP.Records.back();
            break;
        case eSGST:
            SGST.Records.push_back(new SGSTRecord((SGSTRecord *)SourceRecord));
            newRecord = SGST.Records.back();
            break;
        case eLVLI:
            LVLI.Records.push_back(new LVLIRecord((LVLIRecord *)SourceRecord));
            newRecord = LVLI.Records.back();
            break;
        case eWTHR:
            WTHR.Records.push_back(new WTHRRecord((WTHRRecord *)SourceRecord));
            newRecord = WTHR.Records.back();
            break;
        case eCLMT:
            CLMT.Records.push_back(new CLMTRecord((CLMTRecord *)SourceRecord));
            newRecord = CLMT.Records.back();
            break;
        case eREGN:
            REGN.Records.push_back(new REGNRecord((REGNRecord *)SourceRecord));
            newRecord = REGN.Records.back();
            break;
        case eCELL:
            if(ParentRecord == NULL)
                {
                CELL.Records.push_back(new CELLRecord((CELLRecord *)SourceRecord));
                newRecord = CELL.Records.back();

                ((CELLRecord *)newRecord)->IsInterior(true);
                }
            else
                {
                if(ParentRecord->GetType() != eWRLD)
                    return NULL;

                if(options.CopyWorldCellStatus)
                    {
                    if(((WRLDRecord *)((CELLRecord *)SourceRecord)->Parent)->CELL->formID == SourceRecord->formID)
                        options.SetAsWorldCell = true;
                    else
                        options.SetAsWorldCell = false;
                    }

                if(options.SetAsWorldCell)
                    {
                    //If a world cell already exists, return it instead of making a new one
                    if(((WRLDRecord *)ParentRecord)->CELL != NULL)
                        return ((WRLDRecord *)ParentRecord)->CELL;

                    ((WRLDRecord *)ParentRecord)->CELL = new CELLRecord((CELLRecord *)SourceRecord);
                    newRecord = ((WRLDRecord *)ParentRecord)->CELL;
                    }
                else
                    {
                    ((WRLDRecord *)ParentRecord)->CELLS.push_back(new CELLRecord((CELLRecord *)SourceRecord));
                    newRecord = ((WRLDRecord *)ParentRecord)->CELLS.back();
                    }

                ((CELLRecord *)newRecord)->IsInterior(false);
                ((CELLRecord *)newRecord)->Parent = ParentRecord;
                }
            break;
        case eWRLD:
            WRLD.Records.push_back(new WRLDRecord((WRLDRecord *)SourceRecord));
            newRecord = WRLD.Records.back();
            break;
        case eDIAL:
            DIAL.Records.push_back(new DIALRecord((DIALRecord *)SourceRecord));
            newRecord = DIAL.Records.back();
            break;
        case ePGRD:
            if(ParentRecord == NULL || ParentRecord->GetType() != eCELL)
                return NULL;

            //If a cell pathgrid already exists, return it instead of making a new one
            if(((CELLRecord *)ParentRecord)->PGRD != NULL)
                return ((CELLRecord *)ParentRecord)->PGRD;

            ((CELLRecord *)ParentRecord)->PGRD = new PGRDRecord((PGRDRecord *)SourceRecord);
            newRecord = ((CELLRecord *)ParentRecord)->PGRD;
            break;
        case eLAND:
            if(ParentRecord == NULL || ParentRecord->GetType() != eCELL)
                return NULL;

            //If a cell land already exists, return it instead of making a new one
            if(((CELLRecord *)ParentRecord)->LAND != NULL)
                return ((CELLRecord *)ParentRecord)->LAND;

            ((CELLRecord *)ParentRecord)->LAND = new LANDRecord((LANDRecord *)SourceRecord);
            newRecord = ((CELLRecord *)ParentRecord)->LAND;
            break;
        case eACHR:
            if(ParentRecord == NULL || ParentRecord->GetType() != eCELL)
                return NULL;

            ((CELLRecord *)ParentRecord)->ACHR.push_back(new ACHRRecord((ACHRRecord *)SourceRecord));
            newRecord = ((CELLRecord *)ParentRecord)->ACHR.back();
            break;
        case eACRE:
            if(ParentRecord == NULL || ParentRecord->GetType() != eCELL)
                return NULL;

            ((CELLRecord *)ParentRecord)->ACRE.push_back(new ACRERecord((ACRERecord *)SourceRecord));
            newRecord = ((CELLRecord *)ParentRecord)->ACRE.back();
            break;
        case eREFR:
            if(ParentRecord == NULL || ParentRecord->GetType() != eCELL)
                return NULL;
            ((CELLRecord *)ParentRecord)->REFR.push_back(new REFRRecord((REFRRecord *)SourceRecord));
            newRecord = ((CELLRecord *)ParentRecord)->REFR.back();
            break;
        case eROAD:
            if(ParentRecord == NULL || ParentRecord->GetType() != eWRLD)
                return NULL;

            //If a world road already exists, return it instead of making a new one
            if(((WRLDRecord *)ParentRecord)->ROAD != NULL)
                return ((WRLDRecord *)ParentRecord)->ROAD;

            ((WRLDRecord *)ParentRecord)->ROAD = new ROADRecord((ROADRecord *)SourceRecord);
            newRecord = ((WRLDRecord *)ParentRecord)->ROAD;
            break;
        case eINFO:
            if(ParentRecord == NULL || ParentRecord->GetType() != eDIAL)
                return NULL;

            ((DIALRecord *)ParentRecord)->INFO.push_back(new INFORecord((INFORecord *)SourceRecord));
            newRecord = ((DIALRecord *)ParentRecord)->INFO.back();
            break;
        case eQUST:
            QUST.Records.push_back(new QUSTRecord((QUSTRecord *)SourceRecord));
            newRecord = QUST.Records.back();
            break;
        case eIDLE:
            IDLE.Records.push_back(new IDLERecord((IDLERecord *)SourceRecord));
            newRecord = IDLE.Records.back();
            break;
        case ePACK:
            PACK.Records.push_back(new PACKRecord((PACKRecord *)SourceRecord));
            newRecord = PACK.Records.back();
            break;
        case eCSTY:
            CSTY.Records.push_back(new CSTYRecord((CSTYRecord *)SourceRecord));
            newRecord = CSTY.Records.back();
            break;
        case eLSCR:
            LSCR.Records.push_back(new LSCRRecord((LSCRRecord *)SourceRecord));
            newRecord = LSCR.Records.back();
            break;
        case eLVSP:
            LVSP.Records.push_back(new LVSPRecord((LVSPRecord *)SourceRecord));
            newRecord = LVSP.Records.back();
            break;
        case eANIO:
            ANIO.Records.push_back(new ANIORecord((ANIORecord *)SourceRecord));
            newRecord = ANIO.Records.back();
            break;
        case eWATR:
            WATR.Records.push_back(new WATRRecord((WATRRecord *)SourceRecord));
            newRecord = WATR.Records.back();
            break;
        case eEFSH:
            EFSH.Records.push_back(new EFSHRecord((EFSHRecord *)SourceRecord));
            newRecord = EFSH.Records.back();
            break;
        default:
            printf("Error creating record: %i\n", RecordType);
            break;
        }
    return newRecord;
    }

int ModFile::CleanMasters()
    {
    unsigned int cleaned = 0;
    _FormIDHandler TempHandler(FileName, TES4.MAST, TES4.HEDR.value.nextObject);
    TempHandler.SetLoadOrder(FormIDHandler.LoadOrder255);
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
        ToRemove.push_back(p);
        ++cleaned;
        }
    if(cleaned)
        {
        for(int p = (int)ToRemove.size() - 1; p >= 0; --p)
            {
            //printf("Removing: %s\n", TES4.MAST[p].value);
            TES4.MAST.erase(TES4.MAST.begin() + ToRemove[p]);
            }
        FormIDHandler.UpdateFormIDLookup();
        }
    return cleaned;
    }

int ModFile::Save(_FileHandler &SaveHandler, bool CloseMod)
    {
    unsigned int formCount = 0;
    if(Settings.IsDummy)
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

void ModFile::VisitRecords(RecordOp &op)
    {
    //This visits every record and subrecord
    GMST.VisitRecords(op);
    GLOB.VisitRecords(op);
    CLAS.VisitRecords(op);
    FACT.VisitRecords(op);
    HAIR.VisitRecords(op);
    EYES.VisitRecords(op);
    RACE.VisitRecords(op);
    SOUN.VisitRecords(op);
    SKIL.VisitRecords(op);
    MGEF.VisitRecords(op);
    SCPT.VisitRecords(op);
    LTEX.VisitRecords(op);
    ENCH.VisitRecords(op);
    SPEL.VisitRecords(op);
    BSGN.VisitRecords(op);
    ACTI.VisitRecords(op);
    APPA.VisitRecords(op);
    ARMO.VisitRecords(op);
    BOOK.VisitRecords(op);
    CLOT.VisitRecords(op);
    CONT.VisitRecords(op);
    DOOR.VisitRecords(op);
    INGR.VisitRecords(op);
    LIGH.VisitRecords(op);
    MISC.VisitRecords(op);
    STAT.VisitRecords(op);
    GRAS.VisitRecords(op);
    TREE.VisitRecords(op);
    FLOR.VisitRecords(op);
    FURN.VisitRecords(op);
    WEAP.VisitRecords(op);
    AMMO.VisitRecords(op);
    NPC_.VisitRecords(op);
    CREA.VisitRecords(op);
    LVLC.VisitRecords(op);
    SLGM.VisitRecords(op);
    KEYM.VisitRecords(op);
    ALCH.VisitRecords(op);
    SBSP.VisitRecords(op);
    SGST.VisitRecords(op);
    LVLI.VisitRecords(op);
    WTHR.VisitRecords(op);
    CLMT.VisitRecords(op);
    REGN.VisitRecords(op);
    CELL.VisitRecords(op);
    WRLD.VisitRecords(op);
    DIAL.VisitRecords(op);
    QUST.VisitRecords(op);
    IDLE.VisitRecords(op);
    PACK.VisitRecords(op);
    CSTY.VisitRecords(op);
    LSCR.VisitRecords(op);
    LVSP.VisitRecords(op);
    ANIO.VisitRecords(op);
    WATR.VisitRecords(op);
    EFSH.VisitRecords(op);
    return;
    }

void ModFile::VisitTopRecords(const unsigned int &RecordType, RecordOp &op)
    {
    //This visits only the top records specified.
    //Any subrecords are NOT visited.
    switch(RecordType)
        {
        case eGMST:
            GMST.VisitRecords(op);
            break;
        case eGLOB:
            GLOB.VisitRecords(op);
            break;
        case eCLAS:
            CLAS.VisitRecords(op);
            break;
        case eFACT:
            FACT.VisitRecords(op);
            break;
        case eHAIR:
            HAIR.VisitRecords(op);
            break;
        case eEYES:
            EYES.VisitRecords(op);
            break;
        case eRACE:
            RACE.VisitRecords(op);
            break;
        case eSOUN:
            SOUN.VisitRecords(op);
            break;
        case eSKIL:
            SKIL.VisitRecords(op);
            break;
        case eMGEF:
            MGEF.VisitRecords(op);
            break;
        case eSCPT:
            SCPT.VisitRecords(op);
            break;
        case eLTEX:
            LTEX.VisitRecords(op);
            break;
        case eENCH:
            ENCH.VisitRecords(op);
            break;
        case eSPEL:
            SPEL.VisitRecords(op);
            break;
        case eBSGN:
            BSGN.VisitRecords(op);
            break;
        case eACTI:
            ACTI.VisitRecords(op);
            break;
        case eAPPA:
            APPA.VisitRecords(op);
            break;
        case eARMO:
            ARMO.VisitRecords(op);
            break;
        case eBOOK:
            BOOK.VisitRecords(op);
            break;
        case eCLOT:
            CLOT.VisitRecords(op);
            break;
        case eCONT:
            CONT.VisitRecords(op);
            break;
        case eDOOR:
            DOOR.VisitRecords(op);
            break;
        case eINGR:
            INGR.VisitRecords(op);
            break;
        case eLIGH:
            LIGH.VisitRecords(op);
            break;
        case eMISC:
            MISC.VisitRecords(op);
            break;
        case eSTAT:
            STAT.VisitRecords(op);
            break;
        case eGRAS:
            GRAS.VisitRecords(op);
            break;
        case eTREE:
            TREE.VisitRecords(op);
            break;
        case eFLOR:
            FLOR.VisitRecords(op);
            break;
        case eFURN:
            FURN.VisitRecords(op);
            break;
        case eWEAP:
            WEAP.VisitRecords(op);
            break;
        case eAMMO:
            AMMO.VisitRecords(op);
            break;
        case eNPC_:
            NPC_.VisitRecords(op);
            break;
        case eCREA:
            CREA.VisitRecords(op);
            break;
        case eLVLC:
            LVLC.VisitRecords(op);
            break;
        case eSLGM:
            SLGM.VisitRecords(op);
            break;
        case eKEYM:
            KEYM.VisitRecords(op);
            break;
        case eALCH:
            ALCH.VisitRecords(op);
            break;
        case eSBSP:
            SBSP.VisitRecords(op);
            break;
        case eSGST:
            SGST.VisitRecords(op);
            break;
        case eLVLI:
            LVLI.VisitRecords(op);
            break;
        case eWTHR:
            WTHR.VisitRecords(op);
            break;
        case eCLMT:
            CLMT.VisitRecords(op);
            break;
        case eREGN:
            REGN.VisitRecords(op);
            break;
        case eCELL:
            CELL.VisitTopRecords(op);
            break;
        case eWRLD:
            WRLD.VisitTopRecords(op);
            break;
        case eDIAL:
            DIAL.VisitTopRecords(op);
            break;
        case eQUST:
            QUST.VisitRecords(op);
            break;
        case eIDLE:
            IDLE.VisitRecords(op);
            break;
        case ePACK:
            PACK.VisitRecords(op);
            break;
        case eCSTY:
            CSTY.VisitRecords(op);
            break;
        case eLSCR:
            LSCR.VisitRecords(op);
            break;
        case eLVSP:
            LVSP.VisitRecords(op);
            break;
        case eANIO:
            ANIO.VisitRecords(op);
            break;
        case eWATR:
            WATR.VisitRecords(op);
            break;
        case eEFSH:
            EFSH.VisitRecords(op);
            break;
        default:
            printf("Error visiting records: %i\n", RecordType);
            break;
        }
    return;
    }
