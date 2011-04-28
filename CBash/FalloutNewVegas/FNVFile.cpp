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
// FNVFile.cpp
#include "../Common.h"
#include "../GenericRecord.h"
#include "FNVFile.h"

FNVFile::FNVFile(STRING FileName, STRING ModName, const UINT32 _flags):
    ModFile(FileName, ModName, _flags)
    {
    //
    }

FNVFile::~FNVFile()
    {
    //
    }

SINT32 FNVFile::LoadTES4()
    {
    PROFILE_FUNC

    if(TES4.IsLoaded() || !Open())
        {
        if(!TES4.IsLoaded() && !Open())
            printf("FNVFile::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", ReadHandler.getModName());
        return 0;
        }
    #ifdef CBASH_USE_LOGGING
        CLOGGER;
        BOOST_LOG_FUNCTION();
        BOOST_LOG_SEV(lg, trace) << "LoadTES4: " << FileName;
    #endif

    ReadHandler.set_used(4);
    UINT32 recSize = 0;
    ReadHandler.read(&recSize, 4);
    ReadHandler.read(&TES4.flags, 4);
    ReadHandler.read(&TES4.formID, 4);
    ReadHandler.read(&TES4.flagsUnk, 4);
    ReadHandler.read(&TES4.formVersion, 2);
    ReadHandler.read(&TES4.versionControl2[0], 2);
    if(TES4.IsLoaded())
        printf("_fIsLoaded Flag used!!!!: %08X\n", TES4.flags);

    //Normally would read the record with the read method
    //However, that requires recData to be set on the record
    // and that can only be set by the constructor
    //TES4 is constructed when the modfile is created
    // so the info isn't available then.
    //Must make sure this mimics the read method as needed
    TES4.ParseRecord(ReadHandler.getBuffer(24), recSize);
    TES4.IsLoaded(true);
    TES4.IsChanged(true);
    ReadHandler.set_used(recSize);
    return 1;
    }

SINT32 FNVFile::Load(RecordOp &indexer, std::vector<FormIDResolver *> &Expanders)
    {
    PROFILE_FUNC

    enum IgTopRecords {
        eIgGMST = 'TSMG' | 0x00001000, //Record::fIsIgnored
        eIgTXST = 'TSXT' | 0x00001000,
        eIgMICN = 'NCIM' | 0x00001000,
        eIgGLOB = 'BOLG' | 0x00001000,
        eIgCLAS = 'SALC' | 0x00001000,
        eIgFACT = 'TCAF' | 0x00001000,
        eIgHDPT = 'TPDH' | 0x00001000,
        eIgHAIR = 'RIAH' | 0x00001000,
        eIgEYES = 'SEYE' | 0x00001000,
        eIgRACE = 'ECAR' | 0x00001000,
        eIgSOUN = 'NUOS' | 0x00001000,
        eIgASPC = 'CPSA' | 0x00001000,
        eIgMGEF = 'FEGM' | 0x00001000,
        eIgSCPT = 'TPCS' | 0x00001000,
        eIgLTEX = 'XETL' | 0x00001000,
        eIgENCH = 'HCNE' | 0x00001000,
        eIgSPEL = 'LEPS' | 0x00001000,
        eIgACTI = 'ITCA' | 0x00001000,
        eIgTACT = 'TCAT' | 0x00001000,
        eIgTERM = 'MRET' | 0x00001000,
        eIgARMO = 'OMRA' | 0x00001000,
        eIgBOOK = 'KOOB' | 0x00001000,
        eIgCONT = 'TNOC' | 0x00001000,
        eIgDOOR = 'ROOD' | 0x00001000,
        eIgINGR = 'RGNI' | 0x00001000,
        eIgLIGH = 'HGIL' | 0x00001000,
        eIgMISC = 'CSIM' | 0x00001000,
        eIgSTAT = 'TATS' | 0x00001000,
        eIgSCOL = 'LOCS' | 0x00001000,
        eIgMSTT = 'TTSM' | 0x00001000,
        eIgPWAT = 'TAWP' | 0x00001000,
        eIgGRAS = 'SARG' | 0x00001000,
        eIgTREE = 'EERT' | 0x00001000,
        eIgFURN = 'NRUF' | 0x00001000,
        eIgWEAP = 'PAEW' | 0x00001000,
        eIgAMMO = 'OMMA' | 0x00001000,
        eIgNPC_ = '_CPN' | 0x00001000,
        eIgCREA = 'AERC' | 0x00001000,
        eIgLVLC = 'CLVL' | 0x00001000,
        eIgLVLN = 'NLVL' | 0x00001000,
        eIgKEYM = 'MYEK' | 0x00001000,
        eIgALCH = 'HCLA' | 0x00001000,
        eIgIDLM = 'MLDI' | 0x00001000,
        eIgNOTE = 'ETON' | 0x00001000,
        eIgCOBJ = 'JBOC' | 0x00001000,
        eIgPROJ = 'JORP' | 0x00001000,
        eIgLVLI = 'ILVL' | 0x00001000,
        eIgWTHR = 'RHTW' | 0x00001000,
        eIgCLMT = 'TMLC' | 0x00001000,
        eIgREGN = 'NGER' | 0x00001000,
        eIgNAVI = 'IVAN' | 0x00001000,
        eIgCELL = 'LLEC' | 0x00001000,
        eIgWRLD = 'DLRW' | 0x00001000,
        eIgDIAL = 'LAID' | 0x00001000,
        eIgQUST = 'TSUQ' | 0x00001000,
        eIgIDLE = 'ELDI' | 0x00001000,
        eIgPACK = 'KCAP' | 0x00001000,
        eIgCSTY = 'YTSC' | 0x00001000,
        eIgLSCR = 'RCSL' | 0x00001000,
        eIgANIO = 'OINA' | 0x00001000,
        eIgWATR = 'RTAW' | 0x00001000,
        eIgEFSH = 'HSFE' | 0x00001000,
        eIgEXPL = 'LPXE' | 0x00001000,
        eIgDEBR = 'RBED' | 0x00001000,
        eIgIMGS = 'SGMI' | 0x00001000,
        eIgIMAD = 'DAMI' | 0x00001000,
        eIgFLST = 'TSLF' | 0x00001000,
        eIgPERK = 'KREP' | 0x00001000,
        eIgBPTD = 'DTPB' | 0x00001000,
        eIgADDN = 'NDDA' | 0x00001000,
        eIgAVIF = 'FIVA' | 0x00001000,
        eIgRADS = 'SDAR' | 0x00001000,
        eIgCAMS = 'SMAC' | 0x00001000,
        eIgCPTH = 'HTPC' | 0x00001000,
        eIgVTYP = 'PYTV' | 0x00001000,
        eIgIPCT = 'TCPI' | 0x00001000,
        eIgIPDS = 'SDPI' | 0x00001000,
        eIgARMA = 'AMRA' | 0x00001000,
        eIgECZN = 'NZCE' | 0x00001000,
        eIgMESG = 'GSEM' | 0x00001000,
        eIgRGDL = 'LDGR' | 0x00001000,
        eIgDOBJ = 'JBOD' | 0x00001000,
        eIgLGTM = 'MTGL' | 0x00001000,
        eIgMUSC = 'CSUM' | 0x00001000,
        eIgIMOD = 'DOMI' | 0x00001000,
        eIgREPU = 'UPER' | 0x00001000,
        eIgRCPE = 'EPCR' | 0x00001000,
        eIgRCCT = 'TCCR' | 0x00001000,
        eIgCHIP = 'PIHC' | 0x00001000,
        eIgCSNO = 'ONSC' | 0x00001000,
        eIgLSCT = 'TCSL' | 0x00001000,
        eIgMSET = 'TESM' | 0x00001000,
        eIgALOC = 'COLA' | 0x00001000,
        eIgCHAL = 'LAHC' | 0x00001000,
        eIgAMEF = 'FEMA' | 0x00001000,
        eIgCCRD = 'DRCC' | 0x00001000,
        eIgCMNY = 'YNMC' | 0x00001000,
        eIgCDCK = 'KCDC' | 0x00001000,
        eIgDEHY = 'YHED' | 0x00001000,
        eIgHUNG = 'GNUH' | 0x00001000,
        eIgSLPD = 'DPLS' | 0x00001000
        };

    if(Flags.IsIgnoreExisting || !ReadHandler.IsOpen() || Flags.LoadedGRUPs)
        {
        if(!Flags.IsIgnoreExisting)
            {
            if(!ReadHandler.IsOpen())
                printf("FNVFile::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", ReadHandler.getModName());
            else
                printf("FNVFile::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", ReadHandler.getModName());
            }
        return 0;
        }

    Flags.LoadedGRUPs = true;
    UINT32 GRUPSize;
    UINT32 GRUPLabel;
    boost::unordered_set<UINT32> UsedFormIDs;

    RecordReader fullReader(FormIDHandler, Expanders);
    RecordOp skipReader;

    FNVRecordProcessor processor_min(ReadHandler, FormIDHandler, skipReader, Flags, UsedFormIDs);
    FNVRecordProcessor processor_full(ReadHandler, FormIDHandler, fullReader, Flags, UsedFormIDs);

    FNVRecordProcessor &processor = Flags.IsFullLoad ? processor_full : processor_min;

    while(!ReadHandler.eof()){
        ReadHandler.set_used(4); //Skip "GRUP"
        ReadHandler.read(&GRUPSize, 4);
        ReadHandler.read(&GRUPLabel, 4);
        ReadHandler.set_used(4); //Skip type (tops will all == 0)
        //printf("%c%c%c%c\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
        switch(GRUPLabel)
            {
            case eIgGMST:
            case 'TSMG':
                ReadHandler.read(&GMST.stamp, 4);
                ReadHandler.read(&GMST.unknown, 4);
                GMST.Skim(ReadHandler, GRUPSize, processor_full, indexer);
                break;
            //case eIgTXST: //Same as normal
            case 'TSXT':
                ReadHandler.read(&TXST.stamp, 4);
                ReadHandler.read(&TXST.unknown, 4);
                TXST.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            case eIgMICN:
            case 'NCIM':
                ReadHandler.read(&MICN.stamp, 4);
                ReadHandler.read(&MICN.unknown, 4);
                MICN.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            case eIgGLOB:
            case 'BOLG':
                ReadHandler.read(&GLOB.stamp, 4);
                ReadHandler.read(&GLOB.unknown, 4);
                GLOB.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            case eIgCLAS:
            case 'SALC':
                ReadHandler.read(&CLAS.stamp, 4);
                ReadHandler.read(&CLAS.unknown, 4);
                CLAS.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            case eIgFACT:
            case 'TCAF':
                ReadHandler.read(&FACT.stamp, 4);
                ReadHandler.read(&FACT.unknown, 4);
                FACT.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            case eIgHDPT:
            case 'TPDH':
                ReadHandler.read(&HDPT.stamp, 4);
                ReadHandler.read(&HDPT.unknown, 4);
                HDPT.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            case eIgHAIR:
            case 'RIAH':
                ReadHandler.read(&HAIR.stamp, 4);
                ReadHandler.read(&HAIR.unknown, 4);
                HAIR.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            //case eIgEYES: //Same as normal
            case 'SEYE':
                ReadHandler.read(&EYES.stamp, 4);
                ReadHandler.read(&EYES.unknown, 4);
                EYES.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            case eIgRACE:
            case 'ECAR':
                ReadHandler.read(&RACE.stamp, 4);
                ReadHandler.read(&RACE.unknown, 4);
                RACE.Skim(ReadHandler, GRUPSize, processor, indexer);
                break;
            case eIgSOUN:
            case 'NUOS':
                //ReadHandler.read(&SOUN.stamp, 4);
                //ReadHandler.read(&SOUN.unknown, 4);
                //SOUN.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgASPC:  //Same as normal
            case 'CPSA':
                //ReadHandler.read(&ASPC.stamp, 4);
                //ReadHandler.read(&ASPC.unknown, 4);
                //ASPC.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgMGEF:
            case 'FEGM':
                //ReadHandler.read(&MGEF.stamp, 4);
                //ReadHandler.read(&MGEF.unknown, 4);
                //MGEF.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgSCPT:
            case 'TPCS':
                //ReadHandler.read(&SCPT.stamp, 4);
                //ReadHandler.read(&SCPT.unknown, 4);
                //SCPT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgLTEX: //Same as normal
            case 'XETL':
                //ReadHandler.read(&LTEX.stamp, 4);
                //ReadHandler.read(&LTEX.unknown, 4);
                //LTEX.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgENCH:
            case 'HCNE':
                //ReadHandler.read(&ENCH.stamp, 4);
                //ReadHandler.read(&ENCH.unknown, 4);
                //ENCH.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgSPEL: //Same as normal
            case 'LEPS':
                //ReadHandler.read(&SPEL.stamp, 4);
                //ReadHandler.read(&SPEL.unknown, 4);
                //SPEL.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgACTI:
            case 'ITCA':
                //ReadHandler.read(&ACTI.stamp, 4);
                //ReadHandler.read(&ACTI.unknown, 4);
                //ACTI.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgTACT:
            case 'TCAT':
                //ReadHandler.read(&TACT.stamp, 4);
                //ReadHandler.read(&TACT.unknown, 4);
                //TACT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgTERM:
            case 'MRET':
                //ReadHandler.read(&TERM.stamp, 4);
                //ReadHandler.read(&TERM.unknown, 4);
                //TERM.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgARMO: //Same as normal
            case 'OMRA':
                //ReadHandler.read(&ARMO.stamp, 4);
                //ReadHandler.read(&ARMO.unknown, 4);
                //ARMO.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgBOOK:
            case 'KOOB':
                //ReadHandler.read(&BOOK.stamp, 4);
                //ReadHandler.read(&BOOK.unknown, 4);
                //BOOK.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCONT:
            case 'TNOC':
                //ReadHandler.read(&CONT.stamp, 4);
                //ReadHandler.read(&CONT.unknown, 4);
                //CONT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgDOOR:
            case 'ROOD':
                //ReadHandler.read(&DOOR.stamp, 4);
                //ReadHandler.read(&DOOR.unknown, 4);
                //DOOR.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgINGR:
            case 'RGNI':
                //ReadHandler.read(&INGR.stamp, 4);
                //ReadHandler.read(&INGR.unknown, 4);
                //INGR.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgLIGH:
            case 'HGIL':
                //ReadHandler.read(&LIGH.stamp, 4);
                //ReadHandler.read(&LIGH.unknown, 4);
                //LIGH.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgMISC:
            case 'CSIM':
                //ReadHandler.read(&MISC.stamp, 4);
                //ReadHandler.read(&MISC.unknown, 4);
                //MISC.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgSTAT: //Same as normal
            case 'TATS':
                //ReadHandler.read(&STAT.stamp, 4);
                //ReadHandler.read(&STAT.unknown, 4);
                //STAT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgSCOL:
            case 'LOCS':
                //ReadHandler.read(&SCOL.stamp, 4);
                //ReadHandler.read(&SCOL.unknown, 4);
                //SCOL.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgMSTT: //Same as normal
            case 'TTSM':
                //ReadHandler.read(&MSTT.stamp, 4);
                //ReadHandler.read(&MSTT.unknown, 4);
                //MSTT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgPWAT: //Same as normal
            case 'TAWP':
                //ReadHandler.read(&PWAT.stamp, 4);
                //ReadHandler.read(&PWAT.unknown, 4);
                //PWAT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgGRAS: //Same as normal
            case 'SARG':
                //ReadHandler.read(&GRAS.stamp, 4);
                //ReadHandler.read(&GRAS.unknown, 4);
                //GRAS.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgTREE: //Same as normal
            case 'EERT':
                //ReadHandler.read(&TREE.stamp, 4);
                //ReadHandler.read(&TREE.unknown, 4);
                //TREE.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgFURN: //Same as normal
            case 'NRUF':
                //ReadHandler.read(&FURN.stamp, 4);
                //ReadHandler.read(&FURN.unknown, 4);
                //FURN.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgWEAP:
            case 'PAEW':
                //ReadHandler.read(&WEAP.stamp, 4);
                //ReadHandler.read(&WEAP.unknown, 4);
                //WEAP.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgAMMO:
            case 'OMMA':
                //ReadHandler.read(&AMMO.stamp, 4);
                //ReadHandler.read(&AMMO.unknown, 4);
                //AMMO.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgNPC_: //Same as normal
            case '_CPN':
                //ReadHandler.read(&NPC_.stamp, 4);
                //ReadHandler.read(&NPC_.unknown, 4);
                //NPC_.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgCREA: //Same as normal
            case 'AERC':
                //ReadHandler.read(&CREA.stamp, 4);
                //ReadHandler.read(&CREA.unknown, 4);
                //CREA.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgLVLC: //Same as normal
            case 'CLVL':
                //ReadHandler.read(&LVLC.stamp, 4);
                //ReadHandler.read(&LVLC.unknown, 4);
                //LVLC.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgLVLN: //Same as normal
            case 'NLVL':
                //ReadHandler.read(&LVLN.stamp, 4);
                //ReadHandler.read(&LVLN.unknown, 4);
                //LVLN.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgKEYM:
            case 'MYEK':
                //ReadHandler.read(&KEYM.stamp, 4);
                //ReadHandler.read(&KEYM.unknown, 4);
                //KEYM.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgALCH:
            case 'HCLA':
                //ReadHandler.read(&ALCH.stamp, 4);
                //ReadHandler.read(&ALCH.unknown, 4);
                //ALCH.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgIDLM:
            case 'MLDI':
                //ReadHandler.read(&IDLM.stamp, 4);
                //ReadHandler.read(&IDLM.unknown, 4);
                //IDLM.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgNOTE:
            case 'ETON':
                //ReadHandler.read(&NOTE.stamp, 4);
                //ReadHandler.read(&NOTE.unknown, 4);
                //NOTE.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCOBJ:
            case 'JBOC':
                //ReadHandler.read(&COBJ.stamp, 4);
                //ReadHandler.read(&COBJ.unknown, 4);
                //COBJ.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgPROJ: //Same as normal
            case 'JORP':
                //ReadHandler.read(&PROJ.stamp, 4);
                //ReadHandler.read(&PROJ.unknown, 4);
                //PROJ.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgLVLI: //Same as normal
            case 'ILVL':
                //ReadHandler.read(&LVLI.stamp, 4);
                //ReadHandler.read(&LVLI.unknown, 4);
                //LVLI.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgWTHR: //Same as normal
            case 'RHTW':
                //ReadHandler.read(&WTHR.stamp, 4);
                //ReadHandler.read(&WTHR.unknown, 4);
                //WTHR.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCLMT:
            case 'TMLC':
                //ReadHandler.read(&CLMT.stamp, 4);
                //ReadHandler.read(&CLMT.unknown, 4);
                //CLMT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgREGN:
            case 'NGER':
                //ReadHandler.read(&REGN.stamp, 4);
                //ReadHandler.read(&REGN.unknown, 4);
                //REGN.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgNAVI:
            case 'IVAN':
                //ReadHandler.read(&NAVI.stamp, 4);
                //ReadHandler.read(&NAVI.unknown, 4);
                //NAVI.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCELL:
            case 'LLEC':
                //ReadHandler.read(&CELL.stamp, 4);
                //ReadHandler.read(&CELL.unknown, 4);
                //CELL.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgWRLD: //Same as normal
            case 'DLRW':
                //ReadHandler.read(&WRLD.stamp, 4);
                //ReadHandler.read(&WRLD.unknown, 4);
                //WRLD.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgDIAL:
            case 'LAID':
                //ReadHandler.read(&DIAL.stamp, 4);
                //ReadHandler.read(&DIAL.unknown, 4);
                //DIAL.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgQUST: //Same as normal
            case 'TSUQ':
                //ReadHandler.read(&QUST.stamp, 4);
                //ReadHandler.read(&QUST.unknown, 4);
                //QUST.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgIDLE:
            case 'ELDI':
                //ReadHandler.read(&IDLE.stamp, 4);
                //ReadHandler.read(&IDLE.unknown, 4);
                //IDLE.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgPACK:
            case 'KCAP':
                //ReadHandler.read(&PACK.stamp, 4);
                //ReadHandler.read(&PACK.unknown, 4);
                //PACK.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgCSTY: //Same as normal
            case 'YTSC':
                //ReadHandler.read(&CSTY.stamp, 4);
                //ReadHandler.read(&CSTY.unknown, 4);
                //CSTY.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgLSCR: //Same as normal
            case 'RCSL':
                //ReadHandler.read(&LSCR.stamp, 4);
                //ReadHandler.read(&LSCR.unknown, 4);
                //LSCR.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgANIO:
            case 'OINA':
                //ReadHandler.read(&ANIO.stamp, 4);
                //ReadHandler.read(&ANIO.unknown, 4);
                //ANIO.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgWATR:
            case 'RTAW':
                //ReadHandler.read(&WATR.stamp, 4);
                //ReadHandler.read(&WATR.unknown, 4);
                //WATR.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgEFSH:
            case 'HSFE':
                //ReadHandler.read(&EFSH.stamp, 4);
                //ReadHandler.read(&EFSH.unknown, 4);
                //EFSH.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgEXPL: //Same as normal
            case 'LPXE':
                //ReadHandler.read(&EXPL.stamp, 4);
                //ReadHandler.read(&EXPL.unknown, 4);
                //EXPL.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgDEBR:
            case 'RBED':
                //ReadHandler.read(&DEBR.stamp, 4);
                //ReadHandler.read(&DEBR.unknown, 4);
                //DEBR.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgIMGS:
            case 'SGMI':
                //ReadHandler.read(&IMGS.stamp, 4);
                //ReadHandler.read(&IMGS.unknown, 4);
                //IMGS.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgIMAD:
            case 'DAMI':
                //ReadHandler.read(&IMAD.stamp, 4);
                //ReadHandler.read(&IMAD.unknown, 4);
                //IMAD.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgFLST:
            case 'TSLF':
                //ReadHandler.read(&FLST.stamp, 4);
                //ReadHandler.read(&FLST.unknown, 4);
                //FLST.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgPERK:
            case 'KREP':
                //ReadHandler.read(&PERK.stamp, 4);
                //ReadHandler.read(&PERK.unknown, 4);
                //PERK.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgBPTD: //Same as normal
            case 'DTPB':
                //ReadHandler.read(&BPTD.stamp, 4);
                //ReadHandler.read(&BPTD.unknown, 4);
                //BPTD.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgADDN:
            case 'NDDA':
                //ReadHandler.read(&ADDN.stamp, 4);
                //ReadHandler.read(&ADDN.unknown, 4);
                //ADDN.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgAVIF: //Same as normal
            case 'FIVA':
                //ReadHandler.read(&AVIF.stamp, 4);
                //ReadHandler.read(&AVIF.unknown, 4);
                //AVIF.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgRADS:
            case 'SDAR':
                //ReadHandler.read(&RADS.stamp, 4);
                //ReadHandler.read(&RADS.unknown, 4);
                //RADS.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCAMS:
            case 'SMAC':
                //ReadHandler.read(&CAMS.stamp, 4);
                //ReadHandler.read(&CAMS.unknown, 4);
                //CAMS.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgCPTH: //Same as normal
            case 'HTPC':
                //ReadHandler.read(&CPTH.stamp, 4);
                //ReadHandler.read(&CPTH.unknown, 4);
                //CPTH.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgVTYP: //Same as normal
            case 'PYTV':
                //ReadHandler.read(&VTYP.stamp, 4);
                //ReadHandler.read(&VTYP.unknown, 4);
                //VTYP.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgIPCT: //Same as normal
            case 'TCPI':
                //ReadHandler.read(&IPCT.stamp, 4);
                //ReadHandler.read(&IPCT.unknown, 4);
                //IPCT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgIPDS: //Same as normal
            case 'SDPI':
                //ReadHandler.read(&IPDS.stamp, 4);
                //ReadHandler.read(&IPDS.unknown, 4);
                //IPDS.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgARMA: //Same as normal
            case 'AMRA':
                //ReadHandler.read(&ARMA.stamp, 4);
                //ReadHandler.read(&ARMA.unknown, 4);
                //ARMA.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgECZN:
            case 'NZCE':
                //ReadHandler.read(&ECZN.stamp, 4);
                //ReadHandler.read(&ECZN.unknown, 4);
                //ECZN.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgMESG:
            case 'GSEM':
                //ReadHandler.read(&MESG.stamp, 4);
                //ReadHandler.read(&MESG.unknown, 4);
                //MESG.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgRGDL:
            case 'LDGR':
                //ReadHandler.read(&RGDL.stamp, 4);
                //ReadHandler.read(&RGDL.unknown, 4);
                //RGDL.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgDOBJ:
            case 'JBOD':
                //ReadHandler.read(&DOBJ.stamp, 4);
                //ReadHandler.read(&DOBJ.unknown, 4);
                //DOBJ.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgLGTM:
            case 'MTGL':
                //ReadHandler.read(&LGTM.stamp, 4);
                //ReadHandler.read(&LGTM.unknown, 4);
                //LGTM.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgMUSC: //Same as normal
            case 'CSUM':
                //ReadHandler.read(&MUSC.stamp, 4);
                //ReadHandler.read(&MUSC.unknown, 4);
                //MUSC.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgIMOD:
            case 'DOMI':
                //ReadHandler.read(&IMOD.stamp, 4);
                //ReadHandler.read(&IMOD.unknown, 4);
                //IMOD.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgREPU:
            case 'UPER':
                //ReadHandler.read(&REPU.stamp, 4);
                //ReadHandler.read(&REPU.unknown, 4);
                //REPU.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgRCPE:
            case 'EPCR':
                //ReadHandler.read(&RCPE.stamp, 4);
                //ReadHandler.read(&RCPE.unknown, 4);
                //RCPE.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgRCCT:
            case 'TCCR':
                //ReadHandler.read(&RCCT.stamp, 4);
                //ReadHandler.read(&RCCT.unknown, 4);
                //RCCT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCHIP:
            case 'PIHC':
                //ReadHandler.read(&CHIP.stamp, 4);
                //ReadHandler.read(&CHIP.unknown, 4);
                //CHIP.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgCSNO: //Same as normal
            case 'ONSC':
                //ReadHandler.read(&CSNO.stamp, 4);
                //ReadHandler.read(&CSNO.unknown, 4);
                //CSNO.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgLSCT: //Same as normal
            case 'TCSL':
                //ReadHandler.read(&LSCT.stamp, 4);
                //ReadHandler.read(&LSCT.unknown, 4);
                //LSCT.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgMSET: //Same as normal
            case 'TESM':
                //ReadHandler.read(&MSET.stamp, 4);
                //ReadHandler.read(&MSET.unknown, 4);
                //MSET.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgALOC:
            case 'COLA':
                //ReadHandler.read(&ALOC.stamp, 4);
                //ReadHandler.read(&ALOC.unknown, 4);
                //ALOC.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCHAL:
            case 'LAHC':
                //ReadHandler.read(&CHAL.stamp, 4);
                //ReadHandler.read(&CHAL.unknown, 4);
                //CHAL.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgAMEF:
            case 'FEMA':
                //ReadHandler.read(&AMEF.stamp, 4);
                //ReadHandler.read(&AMEF.unknown, 4);
                //AMEF.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCCRD:
            case 'DRCC':
                //ReadHandler.read(&CCRD.stamp, 4);
                //ReadHandler.read(&CCRD.unknown, 4);
                //CCRD.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCMNY:
            case 'YNMC':
                //ReadHandler.read(&CMNY.stamp, 4);
                //ReadHandler.read(&CMNY.unknown, 4);
                //CMNY.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgCDCK:
            case 'KCDC':
                //ReadHandler.read(&CDCK.stamp, 4);
                //ReadHandler.read(&CDCK.unknown, 4);
                //CDCK.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgDEHY:
            case 'YHED':
                //ReadHandler.read(&DEHY.stamp, 4);
                //ReadHandler.read(&DEHY.unknown, 4);
                //DEHY.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            //case eIgHUNG: //Same as normal
            case 'GNUH':
                //ReadHandler.read(&HUNG.stamp, 4);
                //ReadHandler.read(&HUNG.unknown, 4);
                //HUNG.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;
            case eIgSLPD:
            case 'DPLS':
                //ReadHandler.read(&SLPD.stamp, 4);
                //ReadHandler.read(&SLPD.unknown, 4);
                //SLPD.Skim(ReadHandler, GRUPSize, processor, indexer);
                //break;

            default:
                if(GRUPLabel == 0 && GRUPSize == 0)
                    {
                    printf("FNVFile::Skim: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ReadHandler.getModName());
                    return 1;
                    }
                //else
                //    printf("FNVFile::Skim: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ReadHandler.getModName());

                if(GRUPSize == 0)
                    {
                    printf("Unable to continue loading.\n");
                    return 1;
                    }
                else
                    {
                    //printf("Attempting to skip and continue loading.\n");
                    ReadHandler.set_used(GRUPSize - 16); //Skip type (tops will all == 0)
                    }
                break;
            }
        };
    return 1;
    }

UINT32 FNVFile::GetNumRecords(const UINT32 &RecordType)
    {
    PROFILE_FUNC

    switch(RecordType)
        {
        case 'TSMG':
            return (UINT32)GMST.Records.size();
        case 'TSXT':
            return (UINT32)TXST.Records.size();
        case 'NCIM':
            return (UINT32)MICN.Records.size();
        case 'BOLG':
            return (UINT32)GLOB.Records.size();
        case 'SALC':
            return (UINT32)CLAS.Records.size();
        case 'TCAF':
            return (UINT32)FACT.Records.size();
        case 'TPDH':
            return (UINT32)HDPT.Records.size();
        case 'RIAH':
            return (UINT32)HAIR.Records.size();
        case 'SEYE':
            return (UINT32)EYES.Records.size();
        case 'ECAR':
            return (UINT32)RACE.Records.size();
        case 'NUOS':
            //return (UINT32)SOUN.Records.size();
        case 'CPSA':
            //return (UINT32)ASPC.Records.size();
        case 'FEGM':
            //return (UINT32)MGEF.Records.size();
        case 'TPCS':
            //return (UINT32)SCPT.Records.size();
        case 'XETL':
            //return (UINT32)LTEX.Records.size();
        case 'HCNE':
            //return (UINT32)ENCH.Records.size();
        case 'LEPS':
            //return (UINT32)SPEL.Records.size();
        case 'ITCA':
            //return (UINT32)ACTI.Records.size();
        case 'TCAT':
            //return (UINT32)TACT.Records.size();
        case 'MRET':
            //return (UINT32)TERM.Records.size();
        case 'OMRA':
            //return (UINT32)ARMO.Records.size();
        case 'KOOB':
            //return (UINT32)BOOK.Records.size();
        case 'TNOC':
            //return (UINT32)CONT.Records.size();
        case 'ROOD':
            //return (UINT32)DOOR.Records.size();
        case 'RGNI':
            //return (UINT32)INGR.Records.size();
        case 'HGIL':
            //return (UINT32)LIGH.Records.size();
        case 'CSIM':
            //return (UINT32)MISC.Records.size();
        case 'TATS':
            //return (UINT32)STAT.Records.size();
        case 'LOCS':
            //return (UINT32)SCOL.Records.size();
        case 'TTSM':
            //return (UINT32)MSTT.Records.size();
        case 'TAWP':
            //return (UINT32)PWAT.Records.size();
        case 'SARG':
            //return (UINT32)GRAS.Records.size();
        case 'EERT':
            //return (UINT32)TREE.Records.size();
        case 'NRUF':
            //return (UINT32)FURN.Records.size();
        case 'PAEW':
            //return (UINT32)WEAP.Records.size();
        case 'OMMA':
            //return (UINT32)AMMO.Records.size();
        case '_CPN':
            //return (UINT32)NPC_.Records.size();
        case 'AERC':
            //return (UINT32)CREA.Records.size();
        case 'CLVL':
            //return (UINT32)LVLC.Records.size();
        case 'NLVL':
            //return (UINT32)LVLN.Records.size();
        case 'MYEK':
            //return (UINT32)KEYM.Records.size();
        case 'HCLA':
            //return (UINT32)ALCH.Records.size();
        case 'MLDI':
            //return (UINT32)IDLM.Records.size();
        case 'ETON':
            //return (UINT32)NOTE.Records.size();
        case 'JBOC':
            //return (UINT32)COBJ.Records.size();
        case 'JORP':
            //return (UINT32)PROJ.Records.size();
        case 'ILVL':
            //return (UINT32)LVLI.Records.size();
        case 'RHTW':
            //return (UINT32)WTHR.Records.size();
        case 'TMLC':
            //return (UINT32)CLMT.Records.size();
        case 'NGER':
            //return (UINT32)REGN.Records.size();
        case 'IVAN':
            //return (UINT32)NAVI.Records.size();
        case 'LLEC':
            //return (UINT32)CELL.Records.size();
        case 'DLRW':
            //return (UINT32)WRLD.Records.size();
        case 'LAID':
            //return (UINT32)DIAL.Records.size();
        case 'TSUQ':
            //return (UINT32)QUST.Records.size();
        case 'ELDI':
            //return (UINT32)IDLE.Records.size();
        case 'KCAP':
            //return (UINT32)PACK.Records.size();
        case 'YTSC':
            //return (UINT32)CSTY.Records.size();
        case 'RCSL':
            //return (UINT32)LSCR.Records.size();
        case 'OINA':
            //return (UINT32)ANIO.Records.size();
        case 'RTAW':
            //return (UINT32)WATR.Records.size();
        case 'HSFE':
            //return (UINT32)EFSH.Records.size();
        case 'LPXE':
            //return (UINT32)EXPL.Records.size();
        case 'RBED':
            //return (UINT32)DEBR.Records.size();
        case 'SGMI':
            //return (UINT32)IMGS.Records.size();
        case 'DAMI':
            //return (UINT32)IMAD.Records.size();
        case 'TSLF':
            //return (UINT32)FLST.Records.size();
        case 'KREP':
            //return (UINT32)PERK.Records.size();
        case 'DTPB':
            //return (UINT32)BPTD.Records.size();
        case 'NDDA':
            //return (UINT32)ADDN.Records.size();
        case 'FIVA':
            //return (UINT32)AVIF.Records.size();
        case 'SDAR':
            //return (UINT32)RADS.Records.size();
        case 'SMAC':
            //return (UINT32)CAMS.Records.size();
        case 'HTPC':
            //return (UINT32)CPTH.Records.size();
        case 'PYTV':
            //return (UINT32)VTYP.Records.size();
        case 'TCPI':
            //return (UINT32)IPCT.Records.size();
        case 'SDPI':
            //return (UINT32)IPDS.Records.size();
        case 'AMRA':
            //return (UINT32)ARMA.Records.size();
        case 'NZCE':
            //return (UINT32)ECZN.Records.size();
        case 'GSEM':
            //return (UINT32)MESG.Records.size();
        case 'LDGR':
            //return (UINT32)RGDL.Records.size();
        case 'JBOD':
            //return (UINT32)DOBJ.Records.size();
        case 'MTGL':
            //return (UINT32)LGTM.Records.size();
        case 'CSUM':
            //return (UINT32)MUSC.Records.size();
        case 'DOMI':
            //return (UINT32)IMOD.Records.size();
        case 'UPER':
            //return (UINT32)REPU.Records.size();
        case 'EPCR':
            //return (UINT32)RCPE.Records.size();
        case 'TCCR':
            //return (UINT32)RCCT.Records.size();
        case 'PIHC':
            //return (UINT32)CHIP.Records.size();
        case 'ONSC':
            //return (UINT32)CSNO.Records.size();
        case 'TCSL':
            //return (UINT32)LSCT.Records.size();
        case 'TESM':
            //return (UINT32)MSET.Records.size();
        case 'COLA':
            //return (UINT32)ALOC.Records.size();
        case 'LAHC':
            //return (UINT32)CHAL.Records.size();
        case 'FEMA':
            //return (UINT32)AMEF.Records.size();
        case 'DRCC':
            //return (UINT32)CCRD.Records.size();
        case 'YNMC':
            //return (UINT32)CMNY.Records.size();
        case 'KCDC':
            //return (UINT32)CDCK.Records.size();
        case 'YHED':
            //return (UINT32)DEHY.Records.size();
        case 'GNUH':
            //return (UINT32)HUNG.Records.size();
        case 'DPLS':
            //return (UINT32)SLPD.Records.size();
        default:
            printf("FNVFile::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ReadHandler.getModName());
            break;
        }
    return 0;
    }

Record * FNVFile::CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("FNVFile::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", ReadHandler.getModName());
        return NULL;
        }

    Record *newRecord = NULL;

    switch(RecordType)
        {
        case 'TSMG':
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printf("FNVFile::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", ReadHandler.getModName());
                return NULL;
                }

            GMST.Records.push_back(new FNV::GMSTRecord((FNV::GMSTRecord *)SourceRecord));
            newRecord = GMST.Records.back();

            if(RecordEditorID != NULL)
                {
                ((FNV::GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
                ((FNV::GMSTRecord *)newRecord)->DATA.format = ((FNV::GMSTRecord *)newRecord)->EDID.value[0];
                }
            break;
        case 'TSXT':
            TXST.Records.push_back(new FNV::TXSTRecord((FNV::TXSTRecord *)SourceRecord));
            newRecord = TXST.Records.back();
            break;
        case 'NCIM':
            MICN.Records.push_back(new FNV::MICNRecord((FNV::MICNRecord *)SourceRecord));
            newRecord = MICN.Records.back();
            break;
        case 'BOLG':
            GLOB.Records.push_back(new FNV::GLOBRecord((FNV::GLOBRecord *)SourceRecord));
            newRecord = GLOB.Records.back();
            break;
        case 'SALC':
            CLAS.Records.push_back(new FNV::CLASRecord((FNV::CLASRecord *)SourceRecord));
            newRecord = CLAS.Records.back();
            break;
        case 'TCAF':
            FACT.Records.push_back(new FNV::FACTRecord((FNV::FACTRecord *)SourceRecord));
            newRecord = FACT.Records.back();
            break;
        case 'TPDH':
            HDPT.Records.push_back(new FNV::HDPTRecord((FNV::HDPTRecord *)SourceRecord));
            newRecord = HDPT.Records.back();
            break;
        case 'RIAH':
            HAIR.Records.push_back(new FNV::HAIRRecord((FNV::HAIRRecord *)SourceRecord));
            newRecord = HAIR.Records.back();
            break;
        case 'SEYE':
            EYES.Records.push_back(new FNV::EYESRecord((FNV::EYESRecord *)SourceRecord));
            newRecord = EYES.Records.back();
            break;
        case 'ECAR':
            RACE.Records.push_back(new FNV::RACERecord((FNV::RACERecord *)SourceRecord));
            newRecord = RACE.Records.back();
            break;
        case 'NUOS':
            //SOUN.Records.push_back(new FNV::SOUNRecord((FNV::SOUNRecord *)SourceRecord));
            //newRecord = SOUN.Records.back();
            //break;
        case 'CPSA':
            //ASPC.Records.push_back(new FNV::ASPCRecord((FNV::ASPCRecord *)SourceRecord));
            //newRecord = ASPC.Records.back();
            //break;
        case 'FEGM':
            //MGEF.Records.push_back(new FNV::MGEFRecord((FNV::MGEFRecord *)SourceRecord));
            //newRecord = MGEF.Records.back();
            //break;
        case 'TPCS':
            //SCPT.Records.push_back(new FNV::SCPTRecord((FNV::SCPTRecord *)SourceRecord));
            //newRecord = SCPT.Records.back();
            //break;
        case 'XETL':
            //LTEX.Records.push_back(new FNV::LTEXRecord((FNV::LTEXRecord *)SourceRecord));
            //newRecord = LTEX.Records.back();
            //break;
        case 'HCNE':
            //ENCH.Records.push_back(new FNV::ENCHRecord((FNV::ENCHRecord *)SourceRecord));
            //newRecord = ENCH.Records.back();
            //break;
        case 'LEPS':
            //SPEL.Records.push_back(new FNV::SPELRecord((FNV::SPELRecord *)SourceRecord));
            //newRecord = SPEL.Records.back();
            //break;
        case 'ITCA':
            //ACTI.Records.push_back(new FNV::ACTIRecord((FNV::ACTIRecord *)SourceRecord));
            //newRecord = ACTI.Records.back();
            //break;
        case 'TCAT':
            //TACT.Records.push_back(new FNV::TACTRecord((FNV::TACTRecord *)SourceRecord));
            //newRecord = TACT.Records.back();
            //break;
        case 'MRET':
            //TERM.Records.push_back(new FNV::TERMRecord((FNV::TERMRecord *)SourceRecord));
            //newRecord = TERM.Records.back();
            //break;
        case 'OMRA':
            //ARMO.Records.push_back(new FNV::ARMORecord((FNV::ARMORecord *)SourceRecord));
            //newRecord = ARMO.Records.back();
            //break;
        case 'KOOB':
            //BOOK.Records.push_back(new FNV::BOOKRecord((FNV::BOOKRecord *)SourceRecord));
            //newRecord = BOOK.Records.back();
            //break;
        case 'TNOC':
            //CONT.Records.push_back(new FNV::CONTRecord((FNV::CONTRecord *)SourceRecord));
            //newRecord = CONT.Records.back();
            //break;
        case 'ROOD':
            //DOOR.Records.push_back(new FNV::DOORRecord((FNV::DOORRecord *)SourceRecord));
            //newRecord = DOOR.Records.back();
            //break;
        case 'RGNI':
            //INGR.Records.push_back(new FNV::INGRRecord((FNV::INGRRecord *)SourceRecord));
            //newRecord = INGR.Records.back();
            //break;
        case 'HGIL':
            //LIGH.Records.push_back(new FNV::LIGHRecord((FNV::LIGHRecord *)SourceRecord));
            //newRecord = LIGH.Records.back();
            //break;
        case 'CSIM':
            //MISC.Records.push_back(new FNV::MISCRecord((FNV::MISCRecord *)SourceRecord));
            //newRecord = MISC.Records.back();
            //break;
        case 'TATS':
            //STAT.Records.push_back(new FNV::STATRecord((FNV::STATRecord *)SourceRecord));
            //newRecord = STAT.Records.back();
            //break;
        case 'LOCS':
            //SCOL.Records.push_back(new FNV::SCOLRecord((FNV::SCOLRecord *)SourceRecord));
            //newRecord = SCOL.Records.back();
            //break;
        case 'TTSM':
            //MSTT.Records.push_back(new FNV::MSTTRecord((FNV::MSTTRecord *)SourceRecord));
            //newRecord = MSTT.Records.back();
            //break;
        case 'TAWP':
            //PWAT.Records.push_back(new FNV::PWATRecord((FNV::PWATRecord *)SourceRecord));
            //newRecord = PWAT.Records.back();
            //break;
        case 'SARG':
            //GRAS.Records.push_back(new FNV::GRASRecord((FNV::GRASRecord *)SourceRecord));
            //newRecord = GRAS.Records.back();
            //break;
        case 'EERT':
            //TREE.Records.push_back(new FNV::TREERecord((FNV::TREERecord *)SourceRecord));
            //newRecord = TREE.Records.back();
            //break;
        case 'NRUF':
            //FURN.Records.push_back(new FNV::FURNRecord((FNV::FURNRecord *)SourceRecord));
            //newRecord = FURN.Records.back();
            //break;
        case 'PAEW':
            //WEAP.Records.push_back(new FNV::WEAPRecord((FNV::WEAPRecord *)SourceRecord));
            //newRecord = WEAP.Records.back();
            //break;
        case 'OMMA':
            //AMMO.Records.push_back(new FNV::AMMORecord((FNV::AMMORecord *)SourceRecord));
            //newRecord = AMMO.Records.back();
            //break;
        case '_CPN':
            //NPC_.Records.push_back(new FNV::NPC_Record((FNV::NPC_Record *)SourceRecord));
            //newRecord = NPC_.Records.back();
            //break;
        case 'AERC':
            //CREA.Records.push_back(new FNV::CREARecord((FNV::CREARecord *)SourceRecord));
            //newRecord = CREA.Records.back();
            //break;
        case 'CLVL':
            //LVLC.Records.push_back(new FNV::LVLCRecord((FNV::LVLCRecord *)SourceRecord));
            //newRecord = LVLC.Records.back();
            //break;
        case 'NLVL':
            //LVLN.Records.push_back(new FNV::LVLNRecord((FNV::LVLNRecord *)SourceRecord));
            //newRecord = LVLN.Records.back();
            //break;
        case 'MYEK':
            //KEYM.Records.push_back(new FNV::KEYMRecord((FNV::KEYMRecord *)SourceRecord));
            //newRecord = KEYM.Records.back();
            //break;
        case 'HCLA':
            //ALCH.Records.push_back(new FNV::ALCHRecord((FNV::ALCHRecord *)SourceRecord));
            //newRecord = ALCH.Records.back();
            //break;
        case 'MLDI':
            //IDLM.Records.push_back(new FNV::IDLMRecord((FNV::IDLMRecord *)SourceRecord));
            //newRecord = IDLM.Records.back();
            //break;
        case 'ETON':
            //NOTE.Records.push_back(new FNV::NOTERecord((FNV::NOTERecord *)SourceRecord));
            //newRecord = NOTE.Records.back();
            //break;
        case 'JBOC':
            //COBJ.Records.push_back(new FNV::COBJRecord((FNV::COBJRecord *)SourceRecord));
            //newRecord = COBJ.Records.back();
            //break;
        case 'JORP':
            //PROJ.Records.push_back(new FNV::PROJRecord((FNV::PROJRecord *)SourceRecord));
            //newRecord = PROJ.Records.back();
            //break;
        case 'ILVL':
            //LVLI.Records.push_back(new FNV::LVLIRecord((FNV::LVLIRecord *)SourceRecord));
            //newRecord = LVLI.Records.back();
            //break;
        case 'RHTW':
            //WTHR.Records.push_back(new FNV::WTHRRecord((FNV::WTHRRecord *)SourceRecord));
            //newRecord = WTHR.Records.back();
            //break;
        case 'TMLC':
            //CLMT.Records.push_back(new FNV::CLMTRecord((FNV::CLMTRecord *)SourceRecord));
            //newRecord = CLMT.Records.back();
            //break;
        case 'NGER':
            //REGN.Records.push_back(new FNV::REGNRecord((FNV::REGNRecord *)SourceRecord));
            //newRecord = REGN.Records.back();
            //break;
        case 'IVAN':
            //NAVI.Records.push_back(new FNV::NAVIRecord((FNV::NAVIRecord *)SourceRecord));
            //newRecord = NAVI.Records.back();
            //break;
        case 'LLEC':
            //CELL.Records.push_back(new FNV::CELLRecord((FNV::CELLRecord *)SourceRecord));
            //newRecord = CELL.Records.back();
            //break;
        case 'DLRW':
            //WRLD.Records.push_back(new FNV::WRLDRecord((FNV::WRLDRecord *)SourceRecord));
            //newRecord = WRLD.Records.back();
            //break;
        case 'LAID':
            //DIAL.Records.push_back(new FNV::DIALRecord((FNV::DIALRecord *)SourceRecord));
            //newRecord = DIAL.Records.back();
            //break;
        case 'TSUQ':
            //QUST.Records.push_back(new FNV::QUSTRecord((FNV::QUSTRecord *)SourceRecord));
            //newRecord = QUST.Records.back();
            //break;
        case 'ELDI':
            //IDLE.Records.push_back(new FNV::IDLERecord((FNV::IDLERecord *)SourceRecord));
            //newRecord = IDLE.Records.back();
            //break;
        case 'KCAP':
            //PACK.Records.push_back(new FNV::PACKRecord((FNV::PACKRecord *)SourceRecord));
            //newRecord = PACK.Records.back();
            //break;
        case 'YTSC':
            //CSTY.Records.push_back(new FNV::CSTYRecord((FNV::CSTYRecord *)SourceRecord));
            //newRecord = CSTY.Records.back();
            //break;
        case 'RCSL':
            //LSCR.Records.push_back(new FNV::LSCRRecord((FNV::LSCRRecord *)SourceRecord));
            //newRecord = LSCR.Records.back();
            //break;
        case 'OINA':
            //ANIO.Records.push_back(new FNV::ANIORecord((FNV::ANIORecord *)SourceRecord));
            //newRecord = ANIO.Records.back();
            //break;
        case 'RTAW':
            //WATR.Records.push_back(new FNV::WATRRecord((FNV::WATRRecord *)SourceRecord));
            //newRecord = WATR.Records.back();
            //break;
        case 'HSFE':
            //EFSH.Records.push_back(new FNV::EFSHRecord((FNV::EFSHRecord *)SourceRecord));
            //newRecord = EFSH.Records.back();
            //break;
        case 'LPXE':
            //EXPL.Records.push_back(new FNV::EXPLRecord((FNV::EXPLRecord *)SourceRecord));
            //newRecord = EXPL.Records.back();
            //break;
        case 'RBED':
            //DEBR.Records.push_back(new FNV::DEBRRecord((FNV::DEBRRecord *)SourceRecord));
            //newRecord = DEBR.Records.back();
            //break;
        case 'SGMI':
            //IMGS.Records.push_back(new FNV::IMGSRecord((FNV::IMGSRecord *)SourceRecord));
            //newRecord = IMGS.Records.back();
            //break;
        case 'DAMI':
            //IMAD.Records.push_back(new FNV::IMADRecord((FNV::IMADRecord *)SourceRecord));
            //newRecord = IMAD.Records.back();
            //break;
        case 'TSLF':
            //FLST.Records.push_back(new FNV::FLSTRecord((FNV::FLSTRecord *)SourceRecord));
            //newRecord = FLST.Records.back();
            //break;
        case 'KREP':
            //PERK.Records.push_back(new FNV::PERKRecord((FNV::PERKRecord *)SourceRecord));
            //newRecord = PERK.Records.back();
            //break;
        case 'DTPB':
            //BPTD.Records.push_back(new FNV::BPTDRecord((FNV::BPTDRecord *)SourceRecord));
            //newRecord = BPTD.Records.back();
            //break;
        case 'NDDA':
            //ADDN.Records.push_back(new FNV::ADDNRecord((FNV::ADDNRecord *)SourceRecord));
            //newRecord = ADDN.Records.back();
            //break;
        case 'FIVA':
            //AVIF.Records.push_back(new FNV::AVIFRecord((FNV::AVIFRecord *)SourceRecord));
            //newRecord = AVIF.Records.back();
            //break;
        case 'SDAR':
            //RADS.Records.push_back(new FNV::RADSRecord((FNV::RADSRecord *)SourceRecord));
            //newRecord = RADS.Records.back();
            //break;
        case 'SMAC':
            //CAMS.Records.push_back(new FNV::CAMSRecord((FNV::CAMSRecord *)SourceRecord));
            //newRecord = CAMS.Records.back();
            //break;
        case 'HTPC':
            //CPTH.Records.push_back(new FNV::CPTHRecord((FNV::CPTHRecord *)SourceRecord));
            //newRecord = CPTH.Records.back();
            //break;
        case 'PYTV':
            //VTYP.Records.push_back(new FNV::VTYPRecord((FNV::VTYPRecord *)SourceRecord));
            //newRecord = VTYP.Records.back();
            //break;
        case 'TCPI':
            //IPCT.Records.push_back(new FNV::IPCTRecord((FNV::IPCTRecord *)SourceRecord));
            //newRecord = IPCT.Records.back();
            //break;
        case 'SDPI':
            //IPDS.Records.push_back(new FNV::IPDSRecord((FNV::IPDSRecord *)SourceRecord));
            //newRecord = IPDS.Records.back();
            //break;
        case 'AMRA':
            //ARMA.Records.push_back(new FNV::ARMARecord((FNV::ARMARecord *)SourceRecord));
            //newRecord = ARMA.Records.back();
            //break;
        case 'NZCE':
            //ECZN.Records.push_back(new FNV::ECZNRecord((FNV::ECZNRecord *)SourceRecord));
            //newRecord = ECZN.Records.back();
            //break;
        case 'GSEM':
            //MESG.Records.push_back(new FNV::MESGRecord((FNV::MESGRecord *)SourceRecord));
            //newRecord = MESG.Records.back();
            //break;
        case 'LDGR':
            //RGDL.Records.push_back(new FNV::RGDLRecord((FNV::RGDLRecord *)SourceRecord));
            //newRecord = RGDL.Records.back();
            //break;
        case 'JBOD':
            //DOBJ.Records.push_back(new FNV::DOBJRecord((FNV::DOBJRecord *)SourceRecord));
            //newRecord = DOBJ.Records.back();
            //break;
        case 'MTGL':
            //LGTM.Records.push_back(new FNV::LGTMRecord((FNV::LGTMRecord *)SourceRecord));
            //newRecord = LGTM.Records.back();
            //break;
        case 'CSUM':
            //MUSC.Records.push_back(new FNV::MUSCRecord((FNV::MUSCRecord *)SourceRecord));
            //newRecord = MUSC.Records.back();
            //break;
        case 'DOMI':
            //IMOD.Records.push_back(new FNV::IMODRecord((FNV::IMODRecord *)SourceRecord));
            //newRecord = IMOD.Records.back();
            //break;
        case 'UPER':
            //REPU.Records.push_back(new FNV::REPURecord((FNV::REPURecord *)SourceRecord));
            //newRecord = REPU.Records.back();
            //break;
        case 'EPCR':
            //RCPE.Records.push_back(new FNV::RCPERecord((FNV::RCPERecord *)SourceRecord));
            //newRecord = RCPE.Records.back();
            //break;
        case 'TCCR':
            //RCCT.Records.push_back(new FNV::RCCTRecord((FNV::RCCTRecord *)SourceRecord));
            //newRecord = RCCT.Records.back();
            //break;
        case 'PIHC':
            //CHIP.Records.push_back(new FNV::CHIPRecord((FNV::CHIPRecord *)SourceRecord));
            //newRecord = CHIP.Records.back();
            //break;
        case 'ONSC':
            //CSNO.Records.push_back(new FNV::CSNORecord((FNV::CSNORecord *)SourceRecord));
            //newRecord = CSNO.Records.back();
            //break;
        case 'TCSL':
            //LSCT.Records.push_back(new FNV::LSCTRecord((FNV::LSCTRecord *)SourceRecord));
            //newRecord = LSCT.Records.back();
            //break;
        case 'TESM':
            //MSET.Records.push_back(new FNV::MSETRecord((FNV::MSETRecord *)SourceRecord));
            //newRecord = MSET.Records.back();
            //break;
        case 'COLA':
            //ALOC.Records.push_back(new FNV::ALOCRecord((FNV::ALOCRecord *)SourceRecord));
            //newRecord = ALOC.Records.back();
            //break;
        case 'LAHC':
            //CHAL.Records.push_back(new FNV::CHALRecord((FNV::CHALRecord *)SourceRecord));
            //newRecord = CHAL.Records.back();
            //break;
        case 'FEMA':
            //AMEF.Records.push_back(new FNV::AMEFRecord((FNV::AMEFRecord *)SourceRecord));
            //newRecord = AMEF.Records.back();
            //break;
        case 'DRCC':
            //CCRD.Records.push_back(new FNV::CCRDRecord((FNV::CCRDRecord *)SourceRecord));
            //newRecord = CCRD.Records.back();
            //break;
        case 'YNMC':
            //CMNY.Records.push_back(new FNV::CMNYRecord((FNV::CMNYRecord *)SourceRecord));
            //newRecord = CMNY.Records.back();
            //break;
        case 'KCDC':
            //CDCK.Records.push_back(new FNV::CDCKRecord((FNV::CDCKRecord *)SourceRecord));
            //newRecord = CDCK.Records.back();
            //break;
        case 'YHED':
            //DEHY.Records.push_back(new FNV::DEHYRecord((FNV::DEHYRecord *)SourceRecord));
            //newRecord = DEHY.Records.back();
            //break;
        case 'GNUH':
            //HUNG.Records.push_back(new FNV::HUNGRecord((FNV::HUNGRecord *)SourceRecord));
            //newRecord = HUNG.Records.back();
            //break;
        case 'DPLS':
            //SLPD.Records.push_back(new FNV::SLPDRecord((FNV::SLPDRecord *)SourceRecord));
            //newRecord = SLPD.Records.back();
            //break;
        default:
            printf("FNVFile::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ReadHandler.getModName());
            break;
        }
    return newRecord;
    }

SINT32 FNVFile::CleanMasters(std::vector<FormIDResolver *> &Expanders)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("FNVFile::CleanMasters: Error - Unable to clean masters in mod \"%s\". The mod is flagged not to be loaded.\n", ReadHandler.getModName());
        return -1;
        }

    UINT32 cleaned = 0;
    //FormIDHandlerClass TempHandler(FileName, TES4.MAST, TES4.HEDR.value.nextObject);
    //TempHandler.SetLoadOrder(FormIDHandler.LoadOrder255);
    //TempHandler.CreateFormIDLookup(FormIDHandler.ExpandedIndex);
    std::vector<UINT32> ToRemove;
    ToRemove.reserve(TES4.MAST.size());
    Record * topRecord = &TES4;

    for(UINT32 p = 0; p < (UINT8)TES4.MAST.size();++p)
        {
        RecordMasterChecker checker(FormIDHandler, Expanders, p);

        //printf("Checking: %s\n", TES4.MAST[p].value);
        if(checker.Accept(topRecord)) continue;
        if(GMST.VisitRecords(NULL, checker, false)) continue;
        if(TXST.VisitRecords(NULL, checker, false)) continue;
        if(MICN.VisitRecords(NULL, checker, false)) continue;
        if(GLOB.VisitRecords(NULL, checker, false)) continue;
        if(CLAS.VisitRecords(NULL, checker, false)) continue;
        if(FACT.VisitRecords(NULL, checker, false)) continue;
        if(HDPT.VisitRecords(NULL, checker, false)) continue;
        if(HAIR.VisitRecords(NULL, checker, false)) continue;
        if(EYES.VisitRecords(NULL, checker, false)) continue;
        if(RACE.VisitRecords(NULL, checker, false)) continue;
        //if(SOUN.VisitRecords(NULL, checker, false)) continue;
        //if(ASPC.VisitRecords(NULL, checker, false)) continue;
        //if(MGEF.VisitRecords(NULL, checker, false)) continue;
        //if(SCPT.VisitRecords(NULL, checker, false)) continue;
        //if(LTEX.VisitRecords(NULL, checker, false)) continue;
        //if(ENCH.VisitRecords(NULL, checker, false)) continue;
        //if(SPEL.VisitRecords(NULL, checker, false)) continue;
        //if(ACTI.VisitRecords(NULL, checker, false)) continue;
        //if(TACT.VisitRecords(NULL, checker, false)) continue;
        //if(TERM.VisitRecords(NULL, checker, false)) continue;
        //if(ARMO.VisitRecords(NULL, checker, false)) continue;
        //if(BOOK.VisitRecords(NULL, checker, false)) continue;
        //if(CONT.VisitRecords(NULL, checker, false)) continue;
        //if(DOOR.VisitRecords(NULL, checker, false)) continue;
        //if(INGR.VisitRecords(NULL, checker, false)) continue;
        //if(LIGH.VisitRecords(NULL, checker, false)) continue;
        //if(MISC.VisitRecords(NULL, checker, false)) continue;
        //if(STAT.VisitRecords(NULL, checker, false)) continue;
        //if(SCOL.VisitRecords(NULL, checker, false)) continue;
        //if(MSTT.VisitRecords(NULL, checker, false)) continue;
        //if(PWAT.VisitRecords(NULL, checker, false)) continue;
        //if(GRAS.VisitRecords(NULL, checker, false)) continue;
        //if(TREE.VisitRecords(NULL, checker, false)) continue;
        //if(FURN.VisitRecords(NULL, checker, false)) continue;
        //if(WEAP.VisitRecords(NULL, checker, false)) continue;
        //if(AMMO.VisitRecords(NULL, checker, false)) continue;
        //if(NPC_.VisitRecords(NULL, checker, false)) continue;
        //if(CREA.VisitRecords(NULL, checker, false)) continue;
        //if(LVLC.VisitRecords(NULL, checker, false)) continue;
        //if(LVLN.VisitRecords(NULL, checker, false)) continue;
        //if(KEYM.VisitRecords(NULL, checker, false)) continue;
        //if(ALCH.VisitRecords(NULL, checker, false)) continue;
        //if(IDLM.VisitRecords(NULL, checker, false)) continue;
        //if(NOTE.VisitRecords(NULL, checker, false)) continue;
        //if(COBJ.VisitRecords(NULL, checker, false)) continue;
        //if(PROJ.VisitRecords(NULL, checker, false)) continue;
        //if(LVLI.VisitRecords(NULL, checker, false)) continue;
        //if(WTHR.VisitRecords(NULL, checker, false)) continue;
        //if(CLMT.VisitRecords(NULL, checker, false)) continue;
        //if(REGN.VisitRecords(NULL, checker, false)) continue;
        //if(NAVI.VisitRecords(NULL, checker, false)) continue;
        //if(CELL.VisitRecords(NULL, checker, false)) continue;
        //if(WRLD.VisitRecords(NULL, checker, false)) continue;
        //if(DIAL.VisitRecords(NULL, checker, false)) continue;
        //if(QUST.VisitRecords(NULL, checker, false)) continue;
        //if(IDLE.VisitRecords(NULL, checker, false)) continue;
        //if(PACK.VisitRecords(NULL, checker, false)) continue;
        //if(CSTY.VisitRecords(NULL, checker, false)) continue;
        //if(LSCR.VisitRecords(NULL, checker, false)) continue;
        //if(ANIO.VisitRecords(NULL, checker, false)) continue;
        //if(WATR.VisitRecords(NULL, checker, false)) continue;
        //if(EFSH.VisitRecords(NULL, checker, false)) continue;
        //if(EXPL.VisitRecords(NULL, checker, false)) continue;
        //if(DEBR.VisitRecords(NULL, checker, false)) continue;
        //if(IMGS.VisitRecords(NULL, checker, false)) continue;
        //if(IMAD.VisitRecords(NULL, checker, false)) continue;
        //if(FLST.VisitRecords(NULL, checker, false)) continue;
        //if(PERK.VisitRecords(NULL, checker, false)) continue;
        //if(BPTD.VisitRecords(NULL, checker, false)) continue;
        //if(ADDN.VisitRecords(NULL, checker, false)) continue;
        //if(AVIF.VisitRecords(NULL, checker, false)) continue;
        //if(RADS.VisitRecords(NULL, checker, false)) continue;
        //if(CAMS.VisitRecords(NULL, checker, false)) continue;
        //if(CPTH.VisitRecords(NULL, checker, false)) continue;
        //if(VTYP.VisitRecords(NULL, checker, false)) continue;
        //if(IPCT.VisitRecords(NULL, checker, false)) continue;
        //if(IPDS.VisitRecords(NULL, checker, false)) continue;
        //if(ARMA.VisitRecords(NULL, checker, false)) continue;
        //if(ECZN.VisitRecords(NULL, checker, false)) continue;
        //if(MESG.VisitRecords(NULL, checker, false)) continue;
        //if(RGDL.VisitRecords(NULL, checker, false)) continue;
        //if(DOBJ.VisitRecords(NULL, checker, false)) continue;
        //if(LGTM.VisitRecords(NULL, checker, false)) continue;
        //if(MUSC.VisitRecords(NULL, checker, false)) continue;
        //if(IMOD.VisitRecords(NULL, checker, false)) continue;
        //if(REPU.VisitRecords(NULL, checker, false)) continue;
        //if(RCPE.VisitRecords(NULL, checker, false)) continue;
        //if(RCCT.VisitRecords(NULL, checker, false)) continue;
        //if(CHIP.VisitRecords(NULL, checker, false)) continue;
        //if(CSNO.VisitRecords(NULL, checker, false)) continue;
        //if(LSCT.VisitRecords(NULL, checker, false)) continue;
        //if(MSET.VisitRecords(NULL, checker, false)) continue;
        //if(ALOC.VisitRecords(NULL, checker, false)) continue;
        //if(CHAL.VisitRecords(NULL, checker, false)) continue;
        //if(AMEF.VisitRecords(NULL, checker, false)) continue;
        //if(CCRD.VisitRecords(NULL, checker, false)) continue;
        //if(CMNY.VisitRecords(NULL, checker, false)) continue;
        //if(CDCK.VisitRecords(NULL, checker, false)) continue;
        //if(DEHY.VisitRecords(NULL, checker, false)) continue;
        //if(HUNG.VisitRecords(NULL, checker, false)) continue;
        //if(SLPD.VisitRecords(NULL, checker, false)) continue;

        //printf("ToRemove: %s\n", TES4.MAST[p].value);
        ToRemove.push_back(p);
        ++cleaned;
        }
    if(cleaned)
        {
        for(SINT32 p = (SINT32)ToRemove.size() - 1; p >= 0; --p)
            TES4.MAST.erase(TES4.MAST.begin() + ToRemove[p]);
        FormIDHandler.UpdateFormIDLookup();
        }
    return cleaned;
    }

SINT32 FNVFile::Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod)
    {
    PROFILE_FUNC

    if(!Flags.IsSaveable)
        {
        printf("FNVFile::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", ReadHandler.getModName());
        return -1;
        }

    _FileHandler SaveHandler(SaveName, BUFFERSIZE);
    if(SaveHandler.open_ReadWrite() == -1)
        throw std::exception("Unable to open temporary file for writing\n");

    UINT32 formCount = 0;
    FormIDResolver expander(FormIDHandler.ExpandTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    FormIDResolver collapser(FormIDHandler.CollapseTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    //RecordReader reader(FormIDHandler);
    const bool bMastersChanged = FormIDHandler.MastersChanged();

    TES4.Write(SaveHandler, bMastersChanged, expander, collapser, Expanders);

    //ADD DEFINITIONS HERE
    formCount += GMST.WriteGRUP('TSMG', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TXST.WriteGRUP('TSXT', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MICN.WriteGRUP('NCIM', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GLOB.WriteGRUP('BOLG', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLAS.WriteGRUP('SALC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FACT.WriteGRUP('TCAF', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HDPT.WriteGRUP('TPDH', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HAIR.WriteGRUP('RIAH', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EYES.WriteGRUP('SEYE', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += RACE.WriteGRUP('ECAR', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += SOUN.WriteGRUP('NUOS', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ASPC.WriteGRUP('CPSA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MGEF.WriteGRUP('FEGM', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += SCPT.WriteGRUP('TPCS', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LTEX.WriteGRUP('XETL', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ENCH.WriteGRUP('HCNE', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += SPEL.WriteGRUP('LEPS', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ACTI.WriteGRUP('ITCA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += TACT.WriteGRUP('TCAT', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += TERM.WriteGRUP('MRET', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ARMO.WriteGRUP('OMRA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += BOOK.WriteGRUP('KOOB', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CONT.WriteGRUP('TNOC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DOOR.WriteGRUP('ROOD', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += INGR.WriteGRUP('RGNI', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LIGH.WriteGRUP('HGIL', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MISC.WriteGRUP('CSIM', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += STAT.WriteGRUP('TATS', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += SCOL.WriteGRUP('LOCS', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MSTT.WriteGRUP('TTSM', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += PWAT.WriteGRUP('TAWP', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += GRAS.WriteGRUP('SARG', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += TREE.WriteGRUP('EERT', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += FURN.WriteGRUP('NRUF', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += WEAP.WriteGRUP('PAEW', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AMMO.WriteGRUP('OMMA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += NPC_.WriteGRUP('_CPN', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CREA.WriteGRUP('AERC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LVLC.WriteGRUP('CLVL', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LVLN.WriteGRUP('NLVL', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += KEYM.WriteGRUP('MYEK', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ALCH.WriteGRUP('HCLA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IDLM.WriteGRUP('MLDI', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += NOTE.WriteGRUP('ETON', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += COBJ.WriteGRUP('JBOC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += PROJ.WriteGRUP('JORP', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LVLI.WriteGRUP('ILVL', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += WTHR.WriteGRUP('RHTW', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CLMT.WriteGRUP('TMLC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += REGN.WriteGRUP('NGER', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += NAVI.WriteGRUP('IVAN', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CELL.WriteGRUP('LLEC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += WRLD.WriteGRUP('DLRW', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DIAL.WriteGRUP('LAID', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += QUST.WriteGRUP('TSUQ', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IDLE.WriteGRUP('ELDI', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += PACK.WriteGRUP('KCAP', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CSTY.WriteGRUP('YTSC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LSCR.WriteGRUP('RCSL', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ANIO.WriteGRUP('OINA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += WATR.WriteGRUP('RTAW', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += EFSH.WriteGRUP('HSFE', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += EXPL.WriteGRUP('LPXE', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DEBR.WriteGRUP('RBED', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMGS.WriteGRUP('SGMI', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMAD.WriteGRUP('DAMI', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += FLST.WriteGRUP('TSLF', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += PERK.WriteGRUP('KREP', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += BPTD.WriteGRUP('DTPB', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ADDN.WriteGRUP('NDDA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AVIF.WriteGRUP('FIVA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RADS.WriteGRUP('SDAR', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CAMS.WriteGRUP('SMAC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CPTH.WriteGRUP('HTPC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += VTYP.WriteGRUP('PYTV', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IPCT.WriteGRUP('TCPI', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IPDS.WriteGRUP('SDPI', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ARMA.WriteGRUP('AMRA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ECZN.WriteGRUP('NZCE', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MESG.WriteGRUP('GSEM', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RGDL.WriteGRUP('LDGR', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DOBJ.WriteGRUP('JBOD', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LGTM.WriteGRUP('MTGL', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MUSC.WriteGRUP('CSUM', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMOD.WriteGRUP('DOMI', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += REPU.WriteGRUP('UPER', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RCPE.WriteGRUP('EPCR', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RCCT.WriteGRUP('TCCR', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CHIP.WriteGRUP('PIHC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CSNO.WriteGRUP('ONSC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LSCT.WriteGRUP('TCSL', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MSET.WriteGRUP('TESM', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ALOC.WriteGRUP('COLA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CHAL.WriteGRUP('LAHC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AMEF.WriteGRUP('FEMA', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CCRD.WriteGRUP('DRCC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CMNY.WriteGRUP('YNMC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CDCK.WriteGRUP('KCDC', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DEHY.WriteGRUP('YHED', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += HUNG.WriteGRUP('GNUH', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += SLPD.WriteGRUP('DPLS', SaveHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    SaveHandler.writeAt(34, &formCount, 4);
    SaveHandler.close();
    if(CloseMod)
        Close();
    return 0;
    }

void FNVFile::VisitAllRecords(RecordOp &op)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("FNVFile::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ReadHandler.getModName());
        return;
        }

    //This visits every record and subrecord
    Record * topRecord = &TES4;
    op.Accept(topRecord);
    GMST.VisitRecords(NULL, op, true);
    TXST.VisitRecords(NULL, op, true);
    MICN.VisitRecords(NULL, op, true);
    GLOB.VisitRecords(NULL, op, true);
    CLAS.VisitRecords(NULL, op, true);
    FACT.VisitRecords(NULL, op, true);
    HDPT.VisitRecords(NULL, op, true);
    HAIR.VisitRecords(NULL, op, true);
    EYES.VisitRecords(NULL, op, true);
    RACE.VisitRecords(NULL, op, true);
    //SOUN.VisitRecords(NULL, op, true);
    //ASPC.VisitRecords(NULL, op, true);
    //MGEF.VisitRecords(NULL, op, true);
    //SCPT.VisitRecords(NULL, op, true);
    //LTEX.VisitRecords(NULL, op, true);
    //ENCH.VisitRecords(NULL, op, true);
    //SPEL.VisitRecords(NULL, op, true);
    //ACTI.VisitRecords(NULL, op, true);
    //TACT.VisitRecords(NULL, op, true);
    //TERM.VisitRecords(NULL, op, true);
    //ARMO.VisitRecords(NULL, op, true);
    //BOOK.VisitRecords(NULL, op, true);
    //CONT.VisitRecords(NULL, op, true);
    //DOOR.VisitRecords(NULL, op, true);
    //INGR.VisitRecords(NULL, op, true);
    //LIGH.VisitRecords(NULL, op, true);
    //MISC.VisitRecords(NULL, op, true);
    //STAT.VisitRecords(NULL, op, true);
    //SCOL.VisitRecords(NULL, op, true);
    //MSTT.VisitRecords(NULL, op, true);
    //PWAT.VisitRecords(NULL, op, true);
    //GRAS.VisitRecords(NULL, op, true);
    //TREE.VisitRecords(NULL, op, true);
    //FURN.VisitRecords(NULL, op, true);
    //WEAP.VisitRecords(NULL, op, true);
    //AMMO.VisitRecords(NULL, op, true);
    //NPC_.VisitRecords(NULL, op, true);
    //CREA.VisitRecords(NULL, op, true);
    //LVLC.VisitRecords(NULL, op, true);
    //LVLN.VisitRecords(NULL, op, true);
    //KEYM.VisitRecords(NULL, op, true);
    //ALCH.VisitRecords(NULL, op, true);
    //IDLM.VisitRecords(NULL, op, true);
    //NOTE.VisitRecords(NULL, op, true);
    //COBJ.VisitRecords(NULL, op, true);
    //PROJ.VisitRecords(NULL, op, true);
    //LVLI.VisitRecords(NULL, op, true);
    //WTHR.VisitRecords(NULL, op, true);
    //CLMT.VisitRecords(NULL, op, true);
    //REGN.VisitRecords(NULL, op, true);
    //NAVI.VisitRecords(NULL, op, true);
    //CELL.VisitRecords(NULL, op, true);
    //WRLD.VisitRecords(NULL, op, true);
    //DIAL.VisitRecords(NULL, op, true);
    //QUST.VisitRecords(NULL, op, true);
    //IDLE.VisitRecords(NULL, op, true);
    //PACK.VisitRecords(NULL, op, true);
    //CSTY.VisitRecords(NULL, op, true);
    //LSCR.VisitRecords(NULL, op, true);
    //ANIO.VisitRecords(NULL, op, true);
    //WATR.VisitRecords(NULL, op, true);
    //EFSH.VisitRecords(NULL, op, true);
    //EXPL.VisitRecords(NULL, op, true);
    //DEBR.VisitRecords(NULL, op, true);
    //IMGS.VisitRecords(NULL, op, true);
    //IMAD.VisitRecords(NULL, op, true);
    //FLST.VisitRecords(NULL, op, true);
    //PERK.VisitRecords(NULL, op, true);
    //BPTD.VisitRecords(NULL, op, true);
    //ADDN.VisitRecords(NULL, op, true);
    //AVIF.VisitRecords(NULL, op, true);
    //RADS.VisitRecords(NULL, op, true);
    //CAMS.VisitRecords(NULL, op, true);
    //CPTH.VisitRecords(NULL, op, true);
    //VTYP.VisitRecords(NULL, op, true);
    //IPCT.VisitRecords(NULL, op, true);
    //IPDS.VisitRecords(NULL, op, true);
    //ARMA.VisitRecords(NULL, op, true);
    //ECZN.VisitRecords(NULL, op, true);
    //MESG.VisitRecords(NULL, op, true);
    //RGDL.VisitRecords(NULL, op, true);
    //DOBJ.VisitRecords(NULL, op, true);
    //LGTM.VisitRecords(NULL, op, true);
    //MUSC.VisitRecords(NULL, op, true);
    //IMOD.VisitRecords(NULL, op, true);
    //REPU.VisitRecords(NULL, op, true);
    //RCPE.VisitRecords(NULL, op, true);
    //RCCT.VisitRecords(NULL, op, true);
    //CHIP.VisitRecords(NULL, op, true);
    //CSNO.VisitRecords(NULL, op, true);
    //LSCT.VisitRecords(NULL, op, true);
    //MSET.VisitRecords(NULL, op, true);
    //ALOC.VisitRecords(NULL, op, true);
    //CHAL.VisitRecords(NULL, op, true);
    //AMEF.VisitRecords(NULL, op, true);
    //CCRD.VisitRecords(NULL, op, true);
    //CMNY.VisitRecords(NULL, op, true);
    //CDCK.VisitRecords(NULL, op, true);
    //DEHY.VisitRecords(NULL, op, true);
    //HUNG.VisitRecords(NULL, op, true);
    //SLPD.VisitRecords(NULL, op, true);

    return;
    }

void FNVFile::VisitRecords(const UINT32 &TopRecordType, const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("FNVFile::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ReadHandler.getModName());
        return;
        }

    //This visits only the top records specified.
    Record * topRecord = &TES4;
    switch(TopRecordType)
        {
        case '4SET':
            op.Accept(topRecord);
            break;
        case 'TSMG':
            GMST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'TSXT':
            TXST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'NCIM':
            MICN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'BOLG':
            GLOB.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'SALC':
            CLAS.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'TCAF':
            FACT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'TPDH':
            HDPT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'RIAH':
            HAIR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'SEYE':
            EYES.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'ECAR':
            RACE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case 'NUOS':
            //SOUN.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'CPSA':
            //ASPC.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'FEGM':
            //MGEF.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TPCS':
            //SCPT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'XETL':
            //LTEX.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'HCNE':
            //ENCH.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'LEPS':
            //SPEL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'ITCA':
            //ACTI.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TCAT':
            //TACT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'MRET':
            //TERM.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'OMRA':
            //ARMO.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'KOOB':
            //BOOK.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TNOC':
            //CONT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'ROOD':
            //DOOR.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'RGNI':
            //INGR.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'HGIL':
            //LIGH.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'CSIM':
            //MISC.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TATS':
            //STAT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'LOCS':
            //SCOL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TTSM':
            //MSTT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TAWP':
            //PWAT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'SARG':
            //GRAS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'EERT':
            //TREE.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'NRUF':
            //FURN.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'PAEW':
            //WEAP.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'OMMA':
            //AMMO.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case '_CPN':
            //NPC_.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'AERC':
            //CREA.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'CLVL':
            //LVLC.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'NLVL':
            //LVLN.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'MYEK':
            //KEYM.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'HCLA':
            //ALCH.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'MLDI':
            //IDLM.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'ETON':
            //NOTE.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'JBOC':
            //COBJ.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'JORP':
            //PROJ.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'ILVL':
            //LVLI.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'RHTW':
            //WTHR.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TMLC':
            //CLMT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'NGER':
            //REGN.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'IVAN':
            //NAVI.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'LLEC':
            //CELL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'DLRW':
            //WRLD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'LAID':
            //DIAL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TSUQ':
            //QUST.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'ELDI':
            //IDLE.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'KCAP':
            //PACK.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'YTSC':
            //CSTY.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'RCSL':
            //LSCR.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'OINA':
            //ANIO.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'RTAW':
            //WATR.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'HSFE':
            //EFSH.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'LPXE':
            //EXPL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'RBED':
            //DEBR.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'SGMI':
            //IMGS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'DAMI':
            //IMAD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TSLF':
            //FLST.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'KREP':
            //PERK.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'DTPB':
            //BPTD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'NDDA':
            //ADDN.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'FIVA':
            //AVIF.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'SDAR':
            //RADS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'SMAC':
            //CAMS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'HTPC':
            //CPTH.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'PYTV':
            //VTYP.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TCPI':
            //IPCT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'SDPI':
            //IPDS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'AMRA':
            //ARMA.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'NZCE':
            //ECZN.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'GSEM':
            //MESG.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'LDGR':
            //RGDL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'JBOD':
            //DOBJ.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'MTGL':
            //LGTM.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'CSUM':
            //MUSC.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'DOMI':
            //IMOD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'UPER':
            //REPU.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'EPCR':
            //RCPE.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TCCR':
            //RCCT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'PIHC':
            //CHIP.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'ONSC':
            //CSNO.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TCSL':
            //LSCT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'TESM':
            //MSET.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'COLA':
            //ALOC.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'LAHC':
            //CHAL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'FEMA':
            //AMEF.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'DRCC':
            //CCRD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'YNMC':
            //CMNY.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'KCDC':
            //CDCK.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'YHED':
            //DEHY.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'GNUH':
            //HUNG.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case 'DPLS':
            //SLPD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        default:
            if(RecordType)
                printf("FNVFile::VisitRecords: Error - Unable to visit record type (%c%c%c%c) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ((STRING)&TopRecordType)[0], ((STRING)&TopRecordType)[1], ((STRING)&TopRecordType)[2], ((STRING)&TopRecordType)[3], ReadHandler.getModName());
            else
                printf("FNVFile::VisitRecords: Error - Unable to visit record type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&TopRecordType)[0], ((STRING)&TopRecordType)[1], ((STRING)&TopRecordType)[2], ((STRING)&TopRecordType)[3], ReadHandler.getModName());
            break;
        }
    return;
    }