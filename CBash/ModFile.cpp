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
    reader.Accept((Record **)&TES4);
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
    boost::unordered_set<unsigned long> UsedFormIDs;
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

unsigned long ModFile::GetNumRecords(const unsigned long &RecordType)
    {
    switch(RecordType)
        {
        case eGMST:
            return (unsigned long)GMST.Records.size();
        case eGLOB:
            return (unsigned long)GLOB.Records.size();
        case eCLAS:
            return (unsigned long)CLAS.Records.size();
        case eFACT:
            return (unsigned long)FACT.Records.size();
        case eHAIR:
            return (unsigned long)HAIR.Records.size();
        case eEYES:
            return (unsigned long)EYES.Records.size();
        case eRACE:
            return (unsigned long)RACE.Records.size();
        case eSOUN:
            return (unsigned long)SOUN.Records.size();
        case eSKIL:
            return (unsigned long)SKIL.Records.size();
        case eMGEF:
            return (unsigned long)MGEF.Records.size();
        case eSCPT:
            return (unsigned long)SCPT.Records.size();
        case eLTEX:
            return (unsigned long)LTEX.Records.size();
        case eENCH:
            return (unsigned long)ENCH.Records.size();
        case eSPEL:
            return (unsigned long)SPEL.Records.size();
        case eBSGN:
            return (unsigned long)BSGN.Records.size();
        case eACTI:
            return (unsigned long)ACTI.Records.size();
        case eAPPA:
            return (unsigned long)APPA.Records.size();
        case eARMO:
            return (unsigned long)ARMO.Records.size();
        case eBOOK:
            return (unsigned long)BOOK.Records.size();
        case eCLOT:
            return (unsigned long)CLOT.Records.size();
        case eCONT:
            return (unsigned long)CONT.Records.size();
        case eDOOR:
            return (unsigned long)DOOR.Records.size();
        case eINGR:
            return (unsigned long)INGR.Records.size();
        case eLIGH:
            return (unsigned long)LIGH.Records.size();
        case eMISC:
            return (unsigned long)MISC.Records.size();
        case eSTAT:
            return (unsigned long)STAT.Records.size();
        case eGRAS:
            return (unsigned long)GRAS.Records.size();
        case eTREE:
            return (unsigned long)TREE.Records.size();
        case eFLOR:
            return (unsigned long)FLOR.Records.size();
        case eFURN:
            return (unsigned long)FURN.Records.size();
        case eWEAP:
            return (unsigned long)WEAP.Records.size();
        case eAMMO:
            return (unsigned long)AMMO.Records.size();
        case eNPC_:
            return (unsigned long)NPC_.Records.size();
        case eCREA:
            return (unsigned long)CREA.Records.size();
        case eLVLC:
            return (unsigned long)LVLC.Records.size();
        case eSLGM:
            return (unsigned long)SLGM.Records.size();
        case eKEYM:
            return (unsigned long)KEYM.Records.size();
        case eALCH:
            return (unsigned long)ALCH.Records.size();
        case eSBSP:
            return (unsigned long)SBSP.Records.size();
        case eSGST:
            return (unsigned long)SGST.Records.size();
        case eLVLI:
            return (unsigned long)LVLI.Records.size();
        case eWTHR:
            return (unsigned long)WTHR.Records.size();
        case eCLMT:
            return (unsigned long)CLMT.Records.size();
        case eREGN:
            return (unsigned long)REGN.Records.size();
        case eCELL:
            return (unsigned long)CELL.Records.size();
        case eWRLD:
            return (unsigned long)WRLD.Records.size();
        case eDIAL:
            return (unsigned long)DIAL.Records.size();
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
            return (unsigned long)QUST.Records.size();
        case eIDLE:
            return (unsigned long)IDLE.Records.size();
        case ePACK:
            return (unsigned long)PACK.Records.size();
        case eCSTY:
            return (unsigned long)CSTY.Records.size();
        case eLSCR:
            return (unsigned long)LSCR.Records.size();
        case eLVSP:
            return (unsigned long)LVSP.Records.size();
        case eANIO:
            return (unsigned long)ANIO.Records.size();
        case eWATR:
            return (unsigned long)WATR.Records.size();
        case eEFSH:
            return (unsigned long)EFSH.Records.size();
        default:
            printf("Error counting records: %i\n", RecordType);
            break;
        }
    return 0;
    }

Record * ModFile::CreateRecord(const unsigned long &RecordType, char *RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options)
    {
    Record *newRecord = NULL;

    switch(RecordType)
        {
        case eGMST:
            if(RecordEditorID == NULL && SourceRecord == NULL)
                return NULL;

            GMST.Records.push_back(new GMSTRecord((GMSTRecord *)SourceRecord));
            newRecord = GMST.Records.back();

            if(RecordEditorID != NULL && SourceRecord == NULL)
                {
                ((GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
                ((GMSTRecord *)newRecord)->DATA.format = ((GMSTRecord *)newRecord)->EDID.value[0];
                }
            break;
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
    unsigned long cleaned = 0;
    FormIDHandlerClass TempHandler(FileName, TES4.MAST, TES4.HEDR.value.nextObject);
    TempHandler.SetLoadOrder(FormIDHandler.LoadOrder255);
    TempHandler.CreateFormIDLookup(FormIDHandler.ExpandedIndex);
    std::vector<int> ToRemove;
    ToRemove.reserve(TES4.MAST.size());

    for(int p = 0; p < (unsigned char)TES4.MAST.size();++p)
        {
        RecordMasterChecker checker(FormIDHandler, p);

        //printf("Checking: %s\n", TES4.MAST[p].value);
        if(GMST.VisitRecords(NULL, checker, false)) continue;
        if(GLOB.VisitRecords(NULL, checker, false)) continue;
        if(CLAS.VisitRecords(NULL, checker, false)) continue;
        if(FACT.VisitRecords(NULL, checker, false)) continue;
        if(HAIR.VisitRecords(NULL, checker, false)) continue;
        if(EYES.VisitRecords(NULL, checker, false)) continue;
        if(RACE.VisitRecords(NULL, checker, false)) continue;
        if(SOUN.VisitRecords(NULL, checker, false)) continue;
        if(SKIL.VisitRecords(NULL, checker, false)) continue;
        if(MGEF.VisitRecords(NULL, checker, false)) continue;
        if(SCPT.VisitRecords(NULL, checker, false)) continue;
        if(LTEX.VisitRecords(NULL, checker, false)) continue;
        if(ENCH.VisitRecords(NULL, checker, false)) continue;
        if(SPEL.VisitRecords(NULL, checker, false)) continue;
        if(BSGN.VisitRecords(NULL, checker, false)) continue;
        if(ACTI.VisitRecords(NULL, checker, false)) continue;
        if(APPA.VisitRecords(NULL, checker, false)) continue;
        if(ARMO.VisitRecords(NULL, checker, false)) continue;
        if(BOOK.VisitRecords(NULL, checker, false)) continue;
        if(CLOT.VisitRecords(NULL, checker, false)) continue;
        if(CONT.VisitRecords(NULL, checker, false)) continue;
        if(DOOR.VisitRecords(NULL, checker, false)) continue;
        if(INGR.VisitRecords(NULL, checker, false)) continue;
        if(LIGH.VisitRecords(NULL, checker, false)) continue;
        if(MISC.VisitRecords(NULL, checker, false)) continue;
        if(STAT.VisitRecords(NULL, checker, false)) continue;
        if(GRAS.VisitRecords(NULL, checker, false)) continue;
        if(TREE.VisitRecords(NULL, checker, false)) continue;
        if(FLOR.VisitRecords(NULL, checker, false)) continue;
        if(FURN.VisitRecords(NULL, checker, false)) continue;
        if(WEAP.VisitRecords(NULL, checker, false)) continue;
        if(AMMO.VisitRecords(NULL, checker, false)) continue;
        if(NPC_.VisitRecords(NULL, checker, false)) continue;
        if(CREA.VisitRecords(NULL, checker, false)) continue;
        if(LVLC.VisitRecords(NULL, checker, false)) continue;
        if(SLGM.VisitRecords(NULL, checker, false)) continue;
        if(KEYM.VisitRecords(NULL, checker, false)) continue;
        if(ALCH.VisitRecords(NULL, checker, false)) continue;
        if(SBSP.VisitRecords(NULL, checker, false)) continue;
        if(SGST.VisitRecords(NULL, checker, false)) continue;
        if(LVLI.VisitRecords(NULL, checker, false)) continue;
        if(WTHR.VisitRecords(NULL, checker, false)) continue;
        if(CLMT.VisitRecords(NULL, checker, false)) continue;
        if(REGN.VisitRecords(NULL, checker, false)) continue;
        if(CELL.VisitRecords(NULL, checker, true)) continue;
        if(WRLD.VisitRecords(NULL, checker, true)) continue;
        if(DIAL.VisitRecords(NULL, checker, true)) continue;
        if(QUST.VisitRecords(NULL, checker, false)) continue;
        if(IDLE.VisitRecords(NULL, checker, false)) continue;
        if(PACK.VisitRecords(NULL, checker, false)) continue;
        if(CSTY.VisitRecords(NULL, checker, false)) continue;
        if(LSCR.VisitRecords(NULL, checker, false)) continue;
        if(LVSP.VisitRecords(NULL, checker, false)) continue;
        if(ANIO.VisitRecords(NULL, checker, false)) continue;
        if(WATR.VisitRecords(NULL, checker, false)) continue;
        if(EFSH.VisitRecords(NULL, checker, false)) continue;
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
    unsigned long formCount = 0;
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

void ModFile::VisitAllRecords(RecordOp &op)
    {
    //This visits every record and subrecord
    GMST.VisitRecords(NULL, op, true);
    GLOB.VisitRecords(NULL, op, true);
    CLAS.VisitRecords(NULL, op, true);
    FACT.VisitRecords(NULL, op, true);
    HAIR.VisitRecords(NULL, op, true);
    EYES.VisitRecords(NULL, op, true);
    RACE.VisitRecords(NULL, op, true);
    SOUN.VisitRecords(NULL, op, true);
    SKIL.VisitRecords(NULL, op, true);
    MGEF.VisitRecords(NULL, op, true);
    SCPT.VisitRecords(NULL, op, true);
    LTEX.VisitRecords(NULL, op, true);
    ENCH.VisitRecords(NULL, op, true);
    SPEL.VisitRecords(NULL, op, true);
    BSGN.VisitRecords(NULL, op, true);
    ACTI.VisitRecords(NULL, op, true);
    APPA.VisitRecords(NULL, op, true);
    ARMO.VisitRecords(NULL, op, true);
    BOOK.VisitRecords(NULL, op, true);
    CLOT.VisitRecords(NULL, op, true);
    CONT.VisitRecords(NULL, op, true);
    DOOR.VisitRecords(NULL, op, true);
    INGR.VisitRecords(NULL, op, true);
    LIGH.VisitRecords(NULL, op, true);
    MISC.VisitRecords(NULL, op, true);
    STAT.VisitRecords(NULL, op, true);
    GRAS.VisitRecords(NULL, op, true);
    TREE.VisitRecords(NULL, op, true);
    FLOR.VisitRecords(NULL, op, true);
    FURN.VisitRecords(NULL, op, true);
    WEAP.VisitRecords(NULL, op, true);
    AMMO.VisitRecords(NULL, op, true);
    NPC_.VisitRecords(NULL, op, true);
    CREA.VisitRecords(NULL, op, true);
    LVLC.VisitRecords(NULL, op, true);
    SLGM.VisitRecords(NULL, op, true);
    KEYM.VisitRecords(NULL, op, true);
    ALCH.VisitRecords(NULL, op, true);
    SBSP.VisitRecords(NULL, op, true);
    SGST.VisitRecords(NULL, op, true);
    LVLI.VisitRecords(NULL, op, true);
    WTHR.VisitRecords(NULL, op, true);
    CLMT.VisitRecords(NULL, op, true);
    REGN.VisitRecords(NULL, op, true);
    CELL.VisitRecords(NULL, op, true);
    WRLD.VisitRecords(NULL, op, true);
    DIAL.VisitRecords(NULL, op, true);
    QUST.VisitRecords(NULL, op, true);
    IDLE.VisitRecords(NULL, op, true);
    PACK.VisitRecords(NULL, op, true);
    CSTY.VisitRecords(NULL, op, true);
    LSCR.VisitRecords(NULL, op, true);
    LVSP.VisitRecords(NULL, op, true);
    ANIO.VisitRecords(NULL, op, true);
    WATR.VisitRecords(NULL, op, true);
    EFSH.VisitRecords(NULL, op, true);
    return;
    }

void ModFile::VisitRecords(const unsigned long &TopRecordType, const unsigned long &RecordType, RecordOp &op, bool DeepVisit)
    {
    //This visits only the top records specified.
    switch(TopRecordType)
        {
        case eGMST:
            GMST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eGLOB:
            GLOB.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eCLAS:
            CLAS.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eFACT:
            FACT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eHAIR:
            HAIR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eEYES:
            EYES.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eRACE:
            RACE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eSOUN:
            SOUN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eSKIL:
            SKIL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eMGEF:
            MGEF.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eSCPT:
            SCPT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eLTEX:
            LTEX.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eENCH:
            ENCH.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eSPEL:
            SPEL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eBSGN:
            BSGN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eACTI:
            ACTI.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eAPPA:
            APPA.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eARMO:
            ARMO.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eBOOK:
            BOOK.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eCLOT:
            CLOT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eCONT:
            CONT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eDOOR:
            DOOR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eINGR:
            INGR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eLIGH:
            LIGH.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eMISC:
            MISC.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eSTAT:
            STAT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eGRAS:
            GRAS.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eTREE:
            TREE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eFLOR:
            FLOR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eFURN:
            FURN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eWEAP:
            WEAP.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eAMMO:
            AMMO.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eNPC_:
            NPC_.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eCREA:
            CREA.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eLVLC:
            LVLC.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eSLGM:
            SLGM.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eKEYM:
            KEYM.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eALCH:
            ALCH.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eSBSP:
            SBSP.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eSGST:
            SGST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eLVLI:
            LVLI.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eWTHR:
            WTHR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eCLMT:
            CLMT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eREGN:
            REGN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eCELL:
            CELL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eWRLD:
            WRLD.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eDIAL:
            DIAL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eQUST:
            QUST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eIDLE:
            IDLE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case ePACK:
            PACK.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eCSTY:
            CSTY.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eLSCR:
            LSCR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eLVSP:
            LVSP.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eANIO:
            ANIO.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eWATR:
            WATR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case eEFSH:
            EFSH.VisitRecords(RecordType, op, DeepVisit);
            break;
        default:
            printf("Error visiting records: %i\n", RecordType);
            break;
        }
    return;
    }
