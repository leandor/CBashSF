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
            printf("FNVFile::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", reader.getModName());
        return 0;
        }
    #ifdef CBASH_USE_LOGGING
        CLOGGER;
        BOOST_LOG_FUNCTION();
        BOOST_LOG_SEV(lg, trace) << "LoadTES4: " << FileName;
    #endif

    reader.skip(4);
    UINT32 recSize = 0;
    reader.read(&recSize, 4);
    reader.read(&TES4.flags, 4);
    reader.read(&TES4.formID, 4);
    reader.read(&TES4.flagsUnk, 4);
    reader.read(&TES4.formVersion, 2);
    reader.read(&TES4.versionControl2[0], 2);
    if(TES4.IsLoaded())
        printf("_fIsLoaded Flag used!!!!: %08X\n", TES4.flags);

    //Normally would read the record with the read method
    //However, that requires recData to be set on the record
    // and that can only be set by the constructor
    //TES4 is constructed when the modfile is created
    // so the info isn't available then.
    //Must make sure this mimics the read method as needed
    TES4.ParseRecord(reader.getBuffer(24), recSize);
    TES4.IsLoaded(true);
    TES4.IsChanged(true);
    reader.skip(recSize);
    return 1;
    }

SINT32 FNVFile::Load(RecordOp &indexer, std::vector<FormIDResolver *> &Expanders)
    {
    PROFILE_FUNC

    enum IgTopRecords {
        eIgGMST = REV32(GMST) | 0x00001000, //Record::fIsIgnored
        eIgTXST = REV32(TXST) | 0x00001000,
        eIgMICN = REV32(MICN) | 0x00001000,
        eIgGLOB = REV32(GLOB) | 0x00001000,
        eIgCLAS = REV32(CLAS) | 0x00001000,
        eIgFACT = REV32(FACT) | 0x00001000,
        eIgHDPT = REV32(HDPT) | 0x00001000,
        eIgHAIR = REV32(HAIR) | 0x00001000,
        eIgEYES = REV32(EYES) | 0x00001000,
        eIgRACE = REV32(RACE) | 0x00001000,
        eIgSOUN = REV32(SOUN) | 0x00001000,
        eIgASPC = REV32(ASPC) | 0x00001000,
        eIgMGEF = REV32(MGEF) | 0x00001000,
        eIgSCPT = REV32(SCPT) | 0x00001000,
        eIgLTEX = REV32(LTEX) | 0x00001000,
        eIgENCH = REV32(ENCH) | 0x00001000,
        eIgSPEL = REV32(SPEL) | 0x00001000,
        eIgACTI = REV32(ACTI) | 0x00001000,
        eIgTACT = REV32(TACT) | 0x00001000,
        eIgTERM = REV32(TERM) | 0x00001000,
        eIgARMO = REV32(ARMO) | 0x00001000,
        eIgBOOK = REV32(BOOK) | 0x00001000,
        eIgCONT = REV32(CONT) | 0x00001000,
        eIgDOOR = REV32(DOOR) | 0x00001000,
        eIgINGR = REV32(INGR) | 0x00001000,
        eIgLIGH = REV32(LIGH) | 0x00001000,
        eIgMISC = REV32(MISC) | 0x00001000,
        eIgSTAT = REV32(STAT) | 0x00001000,
        eIgSCOL = REV32(SCOL) | 0x00001000,
        eIgMSTT = REV32(MSTT) | 0x00001000,
        eIgPWAT = REV32(PWAT) | 0x00001000,
        eIgGRAS = REV32(GRAS) | 0x00001000,
        eIgTREE = REV32(TREE) | 0x00001000,
        eIgFURN = REV32(FURN) | 0x00001000,
        eIgWEAP = REV32(WEAP) | 0x00001000,
        eIgAMMO = REV32(AMMO) | 0x00001000,
        eIgNPC_ = REV32(NPC_) | 0x00001000,
        eIgCREA = REV32(CREA) | 0x00001000,
        eIgLVLC = REV32(LVLC) | 0x00001000,
        eIgLVLN = REV32(LVLN) | 0x00001000,
        eIgKEYM = REV32(KEYM) | 0x00001000,
        eIgALCH = REV32(ALCH) | 0x00001000,
        eIgIDLM = REV32(IDLM) | 0x00001000,
        eIgNOTE = REV32(NOTE) | 0x00001000,
        eIgCOBJ = REV32(COBJ) | 0x00001000,
        eIgPROJ = REV32(PROJ) | 0x00001000,
        eIgLVLI = REV32(LVLI) | 0x00001000,
        eIgWTHR = REV32(WTHR) | 0x00001000,
        eIgCLMT = REV32(CLMT) | 0x00001000,
        eIgREGN = REV32(REGN) | 0x00001000,
        eIgNAVI = REV32(NAVI) | 0x00001000,
        eIgCELL = REV32(CELL) | 0x00001000,
        eIgWRLD = REV32(WRLD) | 0x00001000,
        eIgDIAL = REV32(DIAL) | 0x00001000,
        eIgQUST = REV32(QUST) | 0x00001000,
        eIgIDLE = REV32(IDLE) | 0x00001000,
        eIgPACK = REV32(PACK) | 0x00001000,
        eIgCSTY = REV32(CSTY) | 0x00001000,
        eIgLSCR = REV32(LSCR) | 0x00001000,
        eIgANIO = REV32(ANIO) | 0x00001000,
        eIgWATR = REV32(WATR) | 0x00001000,
        eIgEFSH = REV32(EFSH) | 0x00001000,
        eIgEXPL = REV32(EXPL) | 0x00001000,
        eIgDEBR = REV32(DEBR) | 0x00001000,
        eIgIMGS = REV32(IMGS) | 0x00001000,
        eIgIMAD = REV32(IMAD) | 0x00001000,
        eIgFLST = REV32(FLST) | 0x00001000,
        eIgPERK = REV32(PERK) | 0x00001000,
        eIgBPTD = REV32(BPTD) | 0x00001000,
        eIgADDN = REV32(ADDN) | 0x00001000,
        eIgAVIF = REV32(AVIF) | 0x00001000,
        eIgRADS = REV32(RADS) | 0x00001000,
        eIgCAMS = REV32(CAMS) | 0x00001000,
        eIgCPTH = REV32(CPTH) | 0x00001000,
        eIgVTYP = REV32(VTYP) | 0x00001000,
        eIgIPCT = REV32(IPCT) | 0x00001000,
        eIgIPDS = REV32(IPDS) | 0x00001000,
        eIgARMA = REV32(ARMA) | 0x00001000,
        eIgECZN = REV32(ECZN) | 0x00001000,
        eIgMESG = REV32(MESG) | 0x00001000,
        eIgRGDL = REV32(RGDL) | 0x00001000,
        eIgDOBJ = REV32(DOBJ) | 0x00001000,
        eIgLGTM = REV32(LGTM) | 0x00001000,
        eIgMUSC = REV32(MUSC) | 0x00001000,
        eIgIMOD = REV32(IMOD) | 0x00001000,
        eIgREPU = REV32(REPU) | 0x00001000,
        eIgRCPE = REV32(RCPE) | 0x00001000,
        eIgRCCT = REV32(RCCT) | 0x00001000,
        eIgCHIP = REV32(CHIP) | 0x00001000,
        eIgCSNO = REV32(CSNO) | 0x00001000,
        eIgLSCT = REV32(LSCT) | 0x00001000,
        eIgMSET = REV32(MSET) | 0x00001000,
        eIgALOC = REV32(ALOC) | 0x00001000,
        eIgCHAL = REV32(CHAL) | 0x00001000,
        eIgAMEF = REV32(AMEF) | 0x00001000,
        eIgCCRD = REV32(CCRD) | 0x00001000,
        eIgCMNY = REV32(CMNY) | 0x00001000,
        eIgCDCK = REV32(CDCK) | 0x00001000,
        eIgDEHY = REV32(DEHY) | 0x00001000,
        eIgHUNG = REV32(HUNG) | 0x00001000,
        eIgSLPD = REV32(SLPD) | 0x00001000
        };

    if(Flags.IsIgnoreExisting || !reader.IsOpen() || Flags.LoadedGRUPs)
        {
        if(!Flags.IsIgnoreExisting)
            {
            if(!reader.IsOpen())
                printf("FNVFile::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", reader.getModName());
            else
                printf("FNVFile::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", reader.getModName());
            }
        return 0;
        }

    Flags.LoadedGRUPs = true;
    UINT32 GRUPSize;
    UINT32 GRUPLabel;
    boost::unordered_set<UINT32> UsedFormIDs;

    RecordReader fullReader(FormIDHandler, Expanders);
    RecordOp skipReader;

    FNVRecordProcessor processor_min(reader, FormIDHandler, skipReader, Flags, UsedFormIDs);
    FNVRecordProcessor processor_full(reader, FormIDHandler, fullReader, Flags, UsedFormIDs);

    FNVRecordProcessor &processor = Flags.IsFullLoad ? processor_full : processor_min;

    while(!reader.eof()){
        reader.skip(4); //Skip "GRUP"
        reader.read(&GRUPSize, 4);
        reader.read(&GRUPLabel, 4);
        reader.skip(4); //Skip type (tops will all == 0)
        //printf("%c%c%c%c\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
        switch(GRUPLabel)
            {
            case eIgGMST:
            case REV32(GMST):
                reader.read(&GMST.stamp, 4);
                reader.read(&GMST.unknown, 4);
                GMST.Skim(reader, GRUPSize, processor_full, indexer);
                break;
            //case eIgTXST: //Same as normal
            case REV32(TXST):
                reader.read(&TXST.stamp, 4);
                reader.read(&TXST.unknown, 4);
                TXST.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgMICN:
            case REV32(MICN):
                reader.read(&MICN.stamp, 4);
                reader.read(&MICN.unknown, 4);
                MICN.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgGLOB:
            case REV32(GLOB):
                reader.read(&GLOB.stamp, 4);
                reader.read(&GLOB.unknown, 4);
                GLOB.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCLAS:
            case REV32(CLAS):
                reader.read(&CLAS.stamp, 4);
                reader.read(&CLAS.unknown, 4);
                CLAS.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgFACT:
            case REV32(FACT):
                reader.read(&FACT.stamp, 4);
                reader.read(&FACT.unknown, 4);
                FACT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgHDPT:
            case REV32(HDPT):
                reader.read(&HDPT.stamp, 4);
                reader.read(&HDPT.unknown, 4);
                HDPT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgHAIR:
            case REV32(HAIR):
                reader.read(&HAIR.stamp, 4);
                reader.read(&HAIR.unknown, 4);
                HAIR.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgEYES: //Same as normal
            case REV32(EYES):
                reader.read(&EYES.stamp, 4);
                reader.read(&EYES.unknown, 4);
                EYES.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgRACE:
            case REV32(RACE):
                reader.read(&RACE.stamp, 4);
                reader.read(&RACE.unknown, 4);
                RACE.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgSOUN:
            case REV32(SOUN):
                reader.read(&SOUN.stamp, 4);
                reader.read(&SOUN.unknown, 4);
                SOUN.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgASPC:  //Same as normal
            case REV32(ASPC):
                reader.read(&ASPC.stamp, 4);
                reader.read(&ASPC.unknown, 4);
                ASPC.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgMGEF:
            case REV32(MGEF):
                reader.read(&MGEF.stamp, 4);
                reader.read(&MGEF.unknown, 4);
                MGEF.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgSCPT:
            case REV32(SCPT):
                reader.read(&SCPT.stamp, 4);
                reader.read(&SCPT.unknown, 4);
                SCPT.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLTEX: //Same as normal
            case REV32(LTEX):
                reader.read(&LTEX.stamp, 4);
                reader.read(&LTEX.unknown, 4);
                LTEX.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgENCH:
            case REV32(ENCH):
                reader.read(&ENCH.stamp, 4);
                reader.read(&ENCH.unknown, 4);
                ENCH.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgSPEL: //Same as normal
            case REV32(SPEL):
                reader.read(&SPEL.stamp, 4);
                reader.read(&SPEL.unknown, 4);
                SPEL.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgACTI:
            case REV32(ACTI):
                reader.read(&ACTI.stamp, 4);
                reader.read(&ACTI.unknown, 4);
                ACTI.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgTACT:
            case REV32(TACT):
                reader.read(&TACT.stamp, 4);
                reader.read(&TACT.unknown, 4);
                TACT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgTERM:
            case REV32(TERM):
                reader.read(&TERM.stamp, 4);
                reader.read(&TERM.unknown, 4);
                TERM.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgARMO: //Same as normal
            case REV32(ARMO):
                reader.read(&ARMO.stamp, 4);
                reader.read(&ARMO.unknown, 4);
                ARMO.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgBOOK:
            case REV32(BOOK):
                reader.read(&BOOK.stamp, 4);
                reader.read(&BOOK.unknown, 4);
                BOOK.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCONT:
            case REV32(CONT):
                reader.read(&CONT.stamp, 4);
                reader.read(&CONT.unknown, 4);
                CONT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgDOOR:
            case REV32(DOOR):
                reader.read(&DOOR.stamp, 4);
                reader.read(&DOOR.unknown, 4);
                DOOR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgINGR:
            case REV32(INGR):
                reader.read(&INGR.stamp, 4);
                reader.read(&INGR.unknown, 4);
                INGR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgLIGH:
            case REV32(LIGH):
                reader.read(&LIGH.stamp, 4);
                reader.read(&LIGH.unknown, 4);
                LIGH.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgMISC:
            case REV32(MISC):
                reader.read(&MISC.stamp, 4);
                reader.read(&MISC.unknown, 4);
                MISC.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgSTAT: //Same as normal
            case REV32(STAT):
                reader.read(&STAT.stamp, 4);
                reader.read(&STAT.unknown, 4);
                STAT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgSCOL:
            case REV32(SCOL):
                reader.read(&SCOL.stamp, 4);
                reader.read(&SCOL.unknown, 4);
                SCOL.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgMSTT: //Same as normal
            case REV32(MSTT):
                reader.read(&MSTT.stamp, 4);
                reader.read(&MSTT.unknown, 4);
                MSTT.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgPWAT: //Same as normal
            case REV32(PWAT):
                reader.read(&PWAT.stamp, 4);
                reader.read(&PWAT.unknown, 4);
                PWAT.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgGRAS: //Same as normal
            case REV32(GRAS):
                reader.read(&GRAS.stamp, 4);
                reader.read(&GRAS.unknown, 4);
                GRAS.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgTREE: //Same as normal
            case REV32(TREE):
                reader.read(&TREE.stamp, 4);
                reader.read(&TREE.unknown, 4);
                TREE.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgFURN: //Same as normal
            case REV32(FURN):
                reader.read(&FURN.stamp, 4);
                reader.read(&FURN.unknown, 4);
                FURN.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgWEAP:
            case REV32(WEAP):
                reader.read(&WEAP.stamp, 4);
                reader.read(&WEAP.unknown, 4);
                WEAP.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgAMMO:
            case REV32(AMMO):
                reader.read(&AMMO.stamp, 4);
                reader.read(&AMMO.unknown, 4);
                AMMO.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgNPC_: //Same as normal
            case REV32(NPC_):
                reader.read(&NPC_.stamp, 4);
                reader.read(&NPC_.unknown, 4);
                NPC_.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgCREA: //Same as normal
            case REV32(CREA):
                reader.read(&CREA.stamp, 4);
                reader.read(&CREA.unknown, 4);
                CREA.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLVLC: //Same as normal
            case REV32(LVLC):
                reader.read(&LVLC.stamp, 4);
                reader.read(&LVLC.unknown, 4);
                LVLC.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLVLN: //Same as normal
            case REV32(LVLN):
                reader.read(&LVLN.stamp, 4);
                reader.read(&LVLN.unknown, 4);
                LVLN.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgKEYM:
            case REV32(KEYM):
                reader.read(&KEYM.stamp, 4);
                reader.read(&KEYM.unknown, 4);
                KEYM.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgALCH:
            case REV32(ALCH):
                reader.read(&ALCH.stamp, 4);
                reader.read(&ALCH.unknown, 4);
                ALCH.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgIDLM:
            case REV32(IDLM):
                reader.read(&IDLM.stamp, 4);
                reader.read(&IDLM.unknown, 4);
                IDLM.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgNOTE:
            case REV32(NOTE):
                reader.read(&NOTE.stamp, 4);
                reader.read(&NOTE.unknown, 4);
                NOTE.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCOBJ:
            case REV32(COBJ):
                reader.read(&COBJ.stamp, 4);
                reader.read(&COBJ.unknown, 4);
                COBJ.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgPROJ: //Same as normal
            case REV32(PROJ):
                reader.read(&PROJ.stamp, 4);
                reader.read(&PROJ.unknown, 4);
                PROJ.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLVLI: //Same as normal
            case REV32(LVLI):
                reader.read(&LVLI.stamp, 4);
                reader.read(&LVLI.unknown, 4);
                LVLI.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgWTHR: //Same as normal
            case REV32(WTHR):
                reader.read(&WTHR.stamp, 4);
                reader.read(&WTHR.unknown, 4);
                WTHR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCLMT:
            case REV32(CLMT):
                reader.read(&CLMT.stamp, 4);
                reader.read(&CLMT.unknown, 4);
                CLMT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgREGN:
            case REV32(REGN):
                reader.read(&REGN.stamp, 4);
                reader.read(&REGN.unknown, 4);
                REGN.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgNAVI:
            case REV32(NAVI):
                reader.read(&NAVI.stamp, 4);
                reader.read(&NAVI.unknown, 4);
                NAVI.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCELL:
            case REV32(CELL):
                reader.read(&CELL.stamp, 4);
                reader.read(&CELL.unknown, 4);
                CELL.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgWRLD: //Same as normal
            case REV32(WRLD):
                reader.read(&WRLD.stamp, 4);
                reader.read(&WRLD.unknown, 4);
                WRLD.Skim(reader, GRUPSize, processor, indexer, fullReader);
                break;
            case eIgDIAL:
            case REV32(DIAL):
                reader.read(&DIAL.stamp, 4);
                reader.read(&DIAL.unknown, 4);
                DIAL.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgQUST: //Same as normal
            case REV32(QUST):
                reader.read(&QUST.stamp, 4);
                reader.read(&QUST.unknown, 4);
                QUST.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgIDLE:
            case REV32(IDLE):
                reader.read(&IDLE.stamp, 4);
                reader.read(&IDLE.unknown, 4);
                IDLE.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgPACK:
            case REV32(PACK):
                reader.read(&PACK.stamp, 4);
                reader.read(&PACK.unknown, 4);
                PACK.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgCSTY: //Same as normal
            case REV32(CSTY):
                reader.read(&CSTY.stamp, 4);
                reader.read(&CSTY.unknown, 4);
                CSTY.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLSCR: //Same as normal
            case REV32(LSCR):
                reader.read(&LSCR.stamp, 4);
                reader.read(&LSCR.unknown, 4);
                LSCR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgANIO:
            case REV32(ANIO):
                reader.read(&ANIO.stamp, 4);
                reader.read(&ANIO.unknown, 4);
                ANIO.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgWATR:
            case REV32(WATR):
                reader.read(&WATR.stamp, 4);
                reader.read(&WATR.unknown, 4);
                WATR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgEFSH:
            case REV32(EFSH):
                reader.read(&EFSH.stamp, 4);
                reader.read(&EFSH.unknown, 4);
                EFSH.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgEXPL: //Same as normal
            case REV32(EXPL):
                reader.read(&EXPL.stamp, 4);
                reader.read(&EXPL.unknown, 4);
                EXPL.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgDEBR:
            case REV32(DEBR):
                reader.read(&DEBR.stamp, 4);
                reader.read(&DEBR.unknown, 4);
                DEBR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgIMGS:
            case REV32(IMGS):
                //reader.read(&IMGS.stamp, 4);
                //reader.read(&IMGS.unknown, 4);
                //IMGS.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgIMAD:
            case REV32(IMAD):
                //reader.read(&IMAD.stamp, 4);
                //reader.read(&IMAD.unknown, 4);
                //IMAD.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgFLST:
            case REV32(FLST):
                //reader.read(&FLST.stamp, 4);
                //reader.read(&FLST.unknown, 4);
                //FLST.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgPERK:
            case REV32(PERK):
                //reader.read(&PERK.stamp, 4);
                //reader.read(&PERK.unknown, 4);
                //PERK.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgBPTD: //Same as normal
            case REV32(BPTD):
                //reader.read(&BPTD.stamp, 4);
                //reader.read(&BPTD.unknown, 4);
                //BPTD.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgADDN:
            case REV32(ADDN):
                //reader.read(&ADDN.stamp, 4);
                //reader.read(&ADDN.unknown, 4);
                //ADDN.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgAVIF: //Same as normal
            case REV32(AVIF):
                //reader.read(&AVIF.stamp, 4);
                //reader.read(&AVIF.unknown, 4);
                //AVIF.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgRADS:
            case REV32(RADS):
                //reader.read(&RADS.stamp, 4);
                //reader.read(&RADS.unknown, 4);
                //RADS.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgCAMS:
            case REV32(CAMS):
                //reader.read(&CAMS.stamp, 4);
                //reader.read(&CAMS.unknown, 4);
                //CAMS.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgCPTH: //Same as normal
            case REV32(CPTH):
                //reader.read(&CPTH.stamp, 4);
                //reader.read(&CPTH.unknown, 4);
                //CPTH.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgVTYP: //Same as normal
            case REV32(VTYP):
                //reader.read(&VTYP.stamp, 4);
                //reader.read(&VTYP.unknown, 4);
                //VTYP.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgIPCT: //Same as normal
            case REV32(IPCT):
                //reader.read(&IPCT.stamp, 4);
                //reader.read(&IPCT.unknown, 4);
                //IPCT.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgIPDS: //Same as normal
            case REV32(IPDS):
                //reader.read(&IPDS.stamp, 4);
                //reader.read(&IPDS.unknown, 4);
                //IPDS.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgARMA: //Same as normal
            case REV32(ARMA):
                //reader.read(&ARMA.stamp, 4);
                //reader.read(&ARMA.unknown, 4);
                //ARMA.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgECZN:
            case REV32(ECZN):
                //reader.read(&ECZN.stamp, 4);
                //reader.read(&ECZN.unknown, 4);
                //ECZN.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgMESG:
            case REV32(MESG):
                //reader.read(&MESG.stamp, 4);
                //reader.read(&MESG.unknown, 4);
                //MESG.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgRGDL:
            case REV32(RGDL):
                //reader.read(&RGDL.stamp, 4);
                //reader.read(&RGDL.unknown, 4);
                //RGDL.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgDOBJ:
            case REV32(DOBJ):
                //reader.read(&DOBJ.stamp, 4);
                //reader.read(&DOBJ.unknown, 4);
                //DOBJ.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgLGTM:
            case REV32(LGTM):
                //reader.read(&LGTM.stamp, 4);
                //reader.read(&LGTM.unknown, 4);
                //LGTM.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgMUSC: //Same as normal
            case REV32(MUSC):
                //reader.read(&MUSC.stamp, 4);
                //reader.read(&MUSC.unknown, 4);
                //MUSC.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgIMOD:
            case REV32(IMOD):
                //reader.read(&IMOD.stamp, 4);
                //reader.read(&IMOD.unknown, 4);
                //IMOD.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgREPU:
            case REV32(REPU):
                //reader.read(&REPU.stamp, 4);
                //reader.read(&REPU.unknown, 4);
                //REPU.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgRCPE:
            case REV32(RCPE):
                //reader.read(&RCPE.stamp, 4);
                //reader.read(&RCPE.unknown, 4);
                //RCPE.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgRCCT:
            case REV32(RCCT):
                //reader.read(&RCCT.stamp, 4);
                //reader.read(&RCCT.unknown, 4);
                //RCCT.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgCHIP:
            case REV32(CHIP):
                //reader.read(&CHIP.stamp, 4);
                //reader.read(&CHIP.unknown, 4);
                //CHIP.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgCSNO: //Same as normal
            case REV32(CSNO):
                //reader.read(&CSNO.stamp, 4);
                //reader.read(&CSNO.unknown, 4);
                //CSNO.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgLSCT: //Same as normal
            case REV32(LSCT):
                //reader.read(&LSCT.stamp, 4);
                //reader.read(&LSCT.unknown, 4);
                //LSCT.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgMSET: //Same as normal
            case REV32(MSET):
                //reader.read(&MSET.stamp, 4);
                //reader.read(&MSET.unknown, 4);
                //MSET.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgALOC:
            case REV32(ALOC):
                //reader.read(&ALOC.stamp, 4);
                //reader.read(&ALOC.unknown, 4);
                //ALOC.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgCHAL:
            case REV32(CHAL):
                //reader.read(&CHAL.stamp, 4);
                //reader.read(&CHAL.unknown, 4);
                //CHAL.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgAMEF:
            case REV32(AMEF):
                //reader.read(&AMEF.stamp, 4);
                //reader.read(&AMEF.unknown, 4);
                //AMEF.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgCCRD:
            case REV32(CCRD):
                //reader.read(&CCRD.stamp, 4);
                //reader.read(&CCRD.unknown, 4);
                //CCRD.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgCMNY:
            case REV32(CMNY):
                //reader.read(&CMNY.stamp, 4);
                //reader.read(&CMNY.unknown, 4);
                //CMNY.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgCDCK:
            case REV32(CDCK):
                //reader.read(&CDCK.stamp, 4);
                //reader.read(&CDCK.unknown, 4);
                //CDCK.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgDEHY:
            case REV32(DEHY):
                //reader.read(&DEHY.stamp, 4);
                //reader.read(&DEHY.unknown, 4);
                //DEHY.Skim(reader, GRUPSize, processor, indexer);
                //break;
            //case eIgHUNG: //Same as normal
            case REV32(HUNG):
                //reader.read(&HUNG.stamp, 4);
                //reader.read(&HUNG.unknown, 4);
                //HUNG.Skim(reader, GRUPSize, processor, indexer);
                //break;
            case eIgSLPD:
            case REV32(SLPD):
                //reader.read(&SLPD.stamp, 4);
                //reader.read(&SLPD.unknown, 4);
                //SLPD.Skim(reader, GRUPSize, processor, indexer);
                //break;

            default:
                if(GRUPLabel == 0 && GRUPSize == 0)
                    {
                    printf("FNVFile::Skim: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], reader.getModName());
                    return 1;
                    }
                //else
                //    printf("FNVFile::Skim: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], reader.getModName());

                if(GRUPSize == 0)
                    {
                    printf("Unable to continue loading.\n");
                    return 1;
                    }
                else
                    {
                    //printf("Attempting to skip and continue loading.\n");
                    reader.skip(GRUPSize - 16); //Skip type (tops will all == 0)
                    }
                break;
            }
        };
    //Testing snippet
    //if(Flags.IsFullLoad)
    //    {
    //    RecordChanger changer(FormIDHandler, Expanders);
    //    VisitAllRecords(changer);
    //    }
    return 1;
    }

UINT32 FNVFile::GetNumRecords(const UINT32 &RecordType)
    {
    PROFILE_FUNC

    switch(RecordType)
        {
        case REV32(GMST):
            return (UINT32)GMST.Records.size();
        case REV32(TXST):
            return (UINT32)TXST.Records.size();
        case REV32(MICN):
            return (UINT32)MICN.Records.size();
        case REV32(GLOB):
            return (UINT32)GLOB.Records.size();
        case REV32(CLAS):
            return (UINT32)CLAS.Records.size();
        case REV32(FACT):
            return (UINT32)FACT.Records.size();
        case REV32(HDPT):
            return (UINT32)HDPT.Records.size();
        case REV32(HAIR):
            return (UINT32)HAIR.Records.size();
        case REV32(EYES):
            return (UINT32)EYES.Records.size();
        case REV32(RACE):
            return (UINT32)RACE.Records.size();
        case REV32(SOUN):
            return (UINT32)SOUN.Records.size();
        case REV32(ASPC):
            return (UINT32)ASPC.Records.size();
        case REV32(MGEF):
            return (UINT32)MGEF.Records.size();
        case REV32(SCPT):
            return (UINT32)SCPT.Records.size();
        case REV32(LTEX):
            return (UINT32)LTEX.Records.size();
        case REV32(ENCH):
            return (UINT32)ENCH.Records.size();
        case REV32(SPEL):
            return (UINT32)SPEL.Records.size();
        case REV32(ACTI):
            return (UINT32)ACTI.Records.size();
        case REV32(TACT):
            return (UINT32)TACT.Records.size();
        case REV32(TERM):
            return (UINT32)TERM.Records.size();
        case REV32(ARMO):
            return (UINT32)ARMO.Records.size();
        case REV32(BOOK):
            return (UINT32)BOOK.Records.size();
        case REV32(CONT):
            return (UINT32)CONT.Records.size();
        case REV32(DOOR):
            return (UINT32)DOOR.Records.size();
        case REV32(INGR):
            return (UINT32)INGR.Records.size();
        case REV32(LIGH):
            return (UINT32)LIGH.Records.size();
        case REV32(MISC):
            return (UINT32)MISC.Records.size();
        case REV32(STAT):
            return (UINT32)STAT.Records.size();
        case REV32(SCOL):
            return (UINT32)SCOL.Records.size();
        case REV32(MSTT):
            return (UINT32)MSTT.Records.size();
        case REV32(PWAT):
            return (UINT32)PWAT.Records.size();
        case REV32(GRAS):
            return (UINT32)GRAS.Records.size();
        case REV32(TREE):
            return (UINT32)TREE.Records.size();
        case REV32(FURN):
            return (UINT32)FURN.Records.size();
        case REV32(WEAP):
            return (UINT32)WEAP.Records.size();
        case REV32(AMMO):
            return (UINT32)AMMO.Records.size();
        case REV32(NPC_):
            return (UINT32)NPC_.Records.size();
        case REV32(CREA):
            return (UINT32)CREA.Records.size();
        case REV32(LVLC):
            return (UINT32)LVLC.Records.size();
        case REV32(LVLN):
            return (UINT32)LVLN.Records.size();
        case REV32(KEYM):
            return (UINT32)KEYM.Records.size();
        case REV32(ALCH):
            return (UINT32)ALCH.Records.size();
        case REV32(IDLM):
            return (UINT32)IDLM.Records.size();
        case REV32(NOTE):
            return (UINT32)NOTE.Records.size();
        case REV32(COBJ):
            return (UINT32)COBJ.Records.size();
        case REV32(PROJ):
            return (UINT32)PROJ.Records.size();
        case REV32(LVLI):
            return (UINT32)LVLI.Records.size();
        case REV32(WTHR):
            return (UINT32)WTHR.Records.size();
        case REV32(CLMT):
            return (UINT32)CLMT.Records.size();
        case REV32(REGN):
            return (UINT32)REGN.Records.size();
        case REV32(NAVI):
            return (UINT32)NAVI.Records.size();
        case REV32(CELL):
            return (UINT32)CELL.Records.size();
        ///////////////////////////////////////////////
        //SubRecords are counted via GetFieldAttribute API function
        //Fallthroughs are intentional
        case REV32(INFO):
        case REV32(ACHR):
        case REV32(ACRE):
        case REV32(REFR):
        case REV32(PGRE):
        case REV32(PMIS):
        case REV32(PBEA):
        case REV32(PFLA):
        case REV32(PCBE):
        case REV32(NAVM):
        case REV32(LAND):
            printf("FNVFile::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". SubRecords are counted via GetFieldAttribute API function.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        ///////////////////////////////////////////////
        case REV32(WRLD):
            return (UINT32)WRLD.Records.size();
        case REV32(DIAL):
            return (UINT32)DIAL.Records.size();
        case REV32(QUST):
            return (UINT32)QUST.Records.size();
        case REV32(IDLE):
            return (UINT32)IDLE.Records.size();
        case REV32(PACK):
            return (UINT32)PACK.Records.size();
        case REV32(CSTY):
            return (UINT32)CSTY.Records.size();
        case REV32(LSCR):
            return (UINT32)LSCR.Records.size();
        case REV32(ANIO):
            return (UINT32)ANIO.Records.size();
        case REV32(WATR):
            return (UINT32)WATR.Records.size();
        case REV32(EFSH):
            return (UINT32)EFSH.Records.size();
        case REV32(EXPL):
            return (UINT32)EXPL.Records.size();
        case REV32(DEBR):
            return (UINT32)DEBR.Records.size();
        case REV32(IMGS):
            //return (UINT32)IMGS.Records.size();
        case REV32(IMAD):
            //return (UINT32)IMAD.Records.size();
        case REV32(FLST):
            //return (UINT32)FLST.Records.size();
        case REV32(PERK):
            //return (UINT32)PERK.Records.size();
        case REV32(BPTD):
            //return (UINT32)BPTD.Records.size();
        case REV32(ADDN):
            //return (UINT32)ADDN.Records.size();
        case REV32(AVIF):
            //return (UINT32)AVIF.Records.size();
        case REV32(RADS):
            //return (UINT32)RADS.Records.size();
        case REV32(CAMS):
            //return (UINT32)CAMS.Records.size();
        case REV32(CPTH):
            //return (UINT32)CPTH.Records.size();
        case REV32(VTYP):
            //return (UINT32)VTYP.Records.size();
        case REV32(IPCT):
            //return (UINT32)IPCT.Records.size();
        case REV32(IPDS):
            //return (UINT32)IPDS.Records.size();
        case REV32(ARMA):
            //return (UINT32)ARMA.Records.size();
        case REV32(ECZN):
            //return (UINT32)ECZN.Records.size();
        case REV32(MESG):
            //return (UINT32)MESG.Records.size();
        case REV32(RGDL):
            //return (UINT32)RGDL.Records.size();
        case REV32(DOBJ):
            //return (UINT32)DOBJ.Records.size();
        case REV32(LGTM):
            //return (UINT32)LGTM.Records.size();
        case REV32(MUSC):
            //return (UINT32)MUSC.Records.size();
        case REV32(IMOD):
            //return (UINT32)IMOD.Records.size();
        case REV32(REPU):
            //return (UINT32)REPU.Records.size();
        case REV32(RCPE):
            //return (UINT32)RCPE.Records.size();
        case REV32(RCCT):
            //return (UINT32)RCCT.Records.size();
        case REV32(CHIP):
            //return (UINT32)CHIP.Records.size();
        case REV32(CSNO):
            //return (UINT32)CSNO.Records.size();
        case REV32(LSCT):
            //return (UINT32)LSCT.Records.size();
        case REV32(MSET):
            //return (UINT32)MSET.Records.size();
        case REV32(ALOC):
            //return (UINT32)ALOC.Records.size();
        case REV32(CHAL):
            //return (UINT32)CHAL.Records.size();
        case REV32(AMEF):
            //return (UINT32)AMEF.Records.size();
        case REV32(CCRD):
            //return (UINT32)CCRD.Records.size();
        case REV32(CMNY):
            //return (UINT32)CMNY.Records.size();
        case REV32(CDCK):
            //return (UINT32)CDCK.Records.size();
        case REV32(DEHY):
            //return (UINT32)DEHY.Records.size();
        case REV32(HUNG):
            //return (UINT32)HUNG.Records.size();
        case REV32(SLPD):
            //return (UINT32)SLPD.Records.size();
        default:
            printf("FNVFile::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        }
    return 0;
    }

Record * FNVFile::CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("FNVFile::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
        return NULL;
        }

    Record *newRecord = NULL;

    switch(RecordType)
        {
        case REV32(GMST):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printf("FNVFile::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", reader.getModName());
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
        case REV32(TXST):
            TXST.Records.push_back(new FNV::TXSTRecord((FNV::TXSTRecord *)SourceRecord));
            newRecord = TXST.Records.back();
            break;
        case REV32(MICN):
            MICN.Records.push_back(new FNV::MICNRecord((FNV::MICNRecord *)SourceRecord));
            newRecord = MICN.Records.back();
            break;
        case REV32(GLOB):
            GLOB.Records.push_back(new FNV::GLOBRecord((FNV::GLOBRecord *)SourceRecord));
            newRecord = GLOB.Records.back();
            break;
        case REV32(CLAS):
            CLAS.Records.push_back(new FNV::CLASRecord((FNV::CLASRecord *)SourceRecord));
            newRecord = CLAS.Records.back();
            break;
        case REV32(FACT):
            FACT.Records.push_back(new FNV::FACTRecord((FNV::FACTRecord *)SourceRecord));
            newRecord = FACT.Records.back();
            break;
        case REV32(HDPT):
            HDPT.Records.push_back(new FNV::HDPTRecord((FNV::HDPTRecord *)SourceRecord));
            newRecord = HDPT.Records.back();
            break;
        case REV32(HAIR):
            HAIR.Records.push_back(new FNV::HAIRRecord((FNV::HAIRRecord *)SourceRecord));
            newRecord = HAIR.Records.back();
            break;
        case REV32(EYES):
            EYES.Records.push_back(new FNV::EYESRecord((FNV::EYESRecord *)SourceRecord));
            newRecord = EYES.Records.back();
            break;
        case REV32(RACE):
            RACE.Records.push_back(new FNV::RACERecord((FNV::RACERecord *)SourceRecord));
            newRecord = RACE.Records.back();
            break;
        case REV32(SOUN):
            SOUN.Records.push_back(new FNV::SOUNRecord((FNV::SOUNRecord *)SourceRecord));
            newRecord = SOUN.Records.back();
            break;
        case REV32(ASPC):
            ASPC.Records.push_back(new FNV::ASPCRecord((FNV::ASPCRecord *)SourceRecord));
            newRecord = ASPC.Records.back();
            break;
        case REV32(MGEF):
            MGEF.Records.push_back(new FNV::MGEFRecord((FNV::MGEFRecord *)SourceRecord));
            newRecord = MGEF.Records.back();
            break;
        case REV32(SCPT):
            SCPT.Records.push_back(new FNV::SCPTRecord((FNV::SCPTRecord *)SourceRecord));
            newRecord = SCPT.Records.back();
            break;
        case REV32(LTEX):
            LTEX.Records.push_back(new FNV::LTEXRecord((FNV::LTEXRecord *)SourceRecord));
            newRecord = LTEX.Records.back();
            break;
        case REV32(ENCH):
            ENCH.Records.push_back(new FNV::ENCHRecord((FNV::ENCHRecord *)SourceRecord));
            newRecord = ENCH.Records.back();
            break;
        case REV32(SPEL):
            SPEL.Records.push_back(new FNV::SPELRecord((FNV::SPELRecord *)SourceRecord));
            newRecord = SPEL.Records.back();
            break;
        case REV32(ACTI):
            ACTI.Records.push_back(new FNV::ACTIRecord((FNV::ACTIRecord *)SourceRecord));
            newRecord = ACTI.Records.back();
            break;
        case REV32(TACT):
            TACT.Records.push_back(new FNV::TACTRecord((FNV::TACTRecord *)SourceRecord));
            newRecord = TACT.Records.back();
            break;
        case REV32(TERM):
            TERM.Records.push_back(new FNV::TERMRecord((FNV::TERMRecord *)SourceRecord));
            newRecord = TERM.Records.back();
            break;
        case REV32(ARMO):
            ARMO.Records.push_back(new FNV::ARMORecord((FNV::ARMORecord *)SourceRecord));
            newRecord = ARMO.Records.back();
            break;
        case REV32(BOOK):
            BOOK.Records.push_back(new FNV::BOOKRecord((FNV::BOOKRecord *)SourceRecord));
            newRecord = BOOK.Records.back();
            break;
        case REV32(CONT):
            CONT.Records.push_back(new FNV::CONTRecord((FNV::CONTRecord *)SourceRecord));
            newRecord = CONT.Records.back();
            break;
        case REV32(DOOR):
            DOOR.Records.push_back(new FNV::DOORRecord((FNV::DOORRecord *)SourceRecord));
            newRecord = DOOR.Records.back();
            break;
        case REV32(INGR):
            INGR.Records.push_back(new FNV::INGRRecord((FNV::INGRRecord *)SourceRecord));
            newRecord = INGR.Records.back();
            break;
        case REV32(LIGH):
            LIGH.Records.push_back(new FNV::LIGHRecord((FNV::LIGHRecord *)SourceRecord));
            newRecord = LIGH.Records.back();
            break;
        case REV32(MISC):
            MISC.Records.push_back(new FNV::MISCRecord((FNV::MISCRecord *)SourceRecord));
            newRecord = MISC.Records.back();
            break;
        case REV32(STAT):
            STAT.Records.push_back(new FNV::STATRecord((FNV::STATRecord *)SourceRecord));
            newRecord = STAT.Records.back();
            break;
        case REV32(SCOL):
            SCOL.Records.push_back(new FNV::SCOLRecord((FNV::SCOLRecord *)SourceRecord));
            newRecord = SCOL.Records.back();
            break;
        case REV32(MSTT):
            MSTT.Records.push_back(new FNV::MSTTRecord((FNV::MSTTRecord *)SourceRecord));
            newRecord = MSTT.Records.back();
            break;
        case REV32(PWAT):
            PWAT.Records.push_back(new FNV::PWATRecord((FNV::PWATRecord *)SourceRecord));
            newRecord = PWAT.Records.back();
            break;
        case REV32(GRAS):
            GRAS.Records.push_back(new FNV::GRASRecord((FNV::GRASRecord *)SourceRecord));
            newRecord = GRAS.Records.back();
            break;
        case REV32(TREE):
            TREE.Records.push_back(new FNV::TREERecord((FNV::TREERecord *)SourceRecord));
            newRecord = TREE.Records.back();
            break;
        case REV32(FURN):
            FURN.Records.push_back(new FNV::FURNRecord((FNV::FURNRecord *)SourceRecord));
            newRecord = FURN.Records.back();
            break;
        case REV32(WEAP):
            WEAP.Records.push_back(new FNV::WEAPRecord((FNV::WEAPRecord *)SourceRecord));
            newRecord = WEAP.Records.back();
            break;
        case REV32(AMMO):
            AMMO.Records.push_back(new FNV::AMMORecord((FNV::AMMORecord *)SourceRecord));
            newRecord = AMMO.Records.back();
            break;
        case REV32(NPC_):
            NPC_.Records.push_back(new FNV::NPC_Record((FNV::NPC_Record *)SourceRecord));
            newRecord = NPC_.Records.back();
            break;
        case REV32(CREA):
            CREA.Records.push_back(new FNV::CREARecord((FNV::CREARecord *)SourceRecord));
            newRecord = CREA.Records.back();
            break;
        case REV32(LVLC):
            LVLC.Records.push_back(new FNV::LVLCRecord((FNV::LVLCRecord *)SourceRecord));
            newRecord = LVLC.Records.back();
            break;
        case REV32(LVLN):
            LVLN.Records.push_back(new FNV::LVLNRecord((FNV::LVLNRecord *)SourceRecord));
            newRecord = LVLN.Records.back();
            break;
        case REV32(KEYM):
            KEYM.Records.push_back(new FNV::KEYMRecord((FNV::KEYMRecord *)SourceRecord));
            newRecord = KEYM.Records.back();
            break;
        case REV32(ALCH):
            ALCH.Records.push_back(new FNV::ALCHRecord((FNV::ALCHRecord *)SourceRecord));
            newRecord = ALCH.Records.back();
            break;
        case REV32(IDLM):
            IDLM.Records.push_back(new FNV::IDLMRecord((FNV::IDLMRecord *)SourceRecord));
            newRecord = IDLM.Records.back();
            break;
        case REV32(NOTE):
            NOTE.Records.push_back(new FNV::NOTERecord((FNV::NOTERecord *)SourceRecord));
            newRecord = NOTE.Records.back();
            break;
        case REV32(COBJ):
            COBJ.Records.push_back(new FNV::COBJRecord((FNV::COBJRecord *)SourceRecord));
            newRecord = COBJ.Records.back();
            break;
        case REV32(PROJ):
            PROJ.Records.push_back(new FNV::PROJRecord((FNV::PROJRecord *)SourceRecord));
            newRecord = PROJ.Records.back();
            break;
        case REV32(LVLI):
            LVLI.Records.push_back(new FNV::LVLIRecord((FNV::LVLIRecord *)SourceRecord));
            newRecord = LVLI.Records.back();
            break;
        case REV32(WTHR):
            WTHR.Records.push_back(new FNV::WTHRRecord((FNV::WTHRRecord *)SourceRecord));
            newRecord = WTHR.Records.back();
            break;
        case REV32(CLMT):
            CLMT.Records.push_back(new FNV::CLMTRecord((FNV::CLMTRecord *)SourceRecord));
            newRecord = CLMT.Records.back();
            break;
        case REV32(REGN):
            REGN.Records.push_back(new FNV::REGNRecord((FNV::REGNRecord *)SourceRecord));
            newRecord = REGN.Records.back();
            break;
        case REV32(NAVI):
            NAVI.Records.push_back(new FNV::NAVIRecord((FNV::NAVIRecord *)SourceRecord));
            newRecord = NAVI.Records.back();
            break;
        case REV32(CELL):
            if(ParentRecord == NULL)
                {
                CELL.Records.push_back(new FNV::CELLRecord((FNV::CELLRecord *)SourceRecord));
                newRecord = CELL.Records.back();

                ((FNV::CELLRecord *)newRecord)->IsInterior(true);
                }
            else
                {
                if(ParentRecord->GetType() != REV32(WRLD))
                    {
                    printf("FNVFile::CreateRecord: Error - Unable to create CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be CELL parents.\n", reader.getModName(), ParentRecord->GetStrType());
                    return NULL;
                    }

                if(options.CopyWorldCellStatus)
                    {
                    if(((FNV::WRLDRecord *)((FNV::CELLRecord *)SourceRecord)->Parent)->CELL->formID == SourceRecord->formID)
                        options.SetAsWorldCell = true;
                    else
                        options.SetAsWorldCell = false;
                    }

                if(options.SetAsWorldCell)
                    {
                    //If a world cell already exists, return it instead of making a new one
                    if(((FNV::WRLDRecord *)ParentRecord)->CELL != NULL)
                        {
                        options.ExistingReturned = true;
                        return ((FNV::WRLDRecord *)ParentRecord)->CELL;
                        }
                    newRecord = ((FNV::WRLDRecord *)ParentRecord)->CELL = new FNV::CELLRecord((FNV::CELLRecord *)SourceRecord);
                    }
                else
                    {
                    ((FNV::WRLDRecord *)ParentRecord)->CELLS.push_back(new FNV::CELLRecord((FNV::CELLRecord *)SourceRecord));
                    newRecord = ((FNV::WRLDRecord *)ParentRecord)->CELLS.back();
                    }

                ((FNV::CELLRecord *)newRecord)->IsInterior(false);
                ((FNV::CELLRecord *)newRecord)->Parent = ParentRecord;
                }
            break;
        case REV32(WRLD):
            WRLD.Records.push_back(new FNV::WRLDRecord((FNV::WRLDRecord *)SourceRecord));
            newRecord = WRLD.Records.back();
            break;
        case REV32(DIAL):
            DIAL.Records.push_back(new FNV::DIALRecord((FNV::DIALRecord *)SourceRecord));
            newRecord = DIAL.Records.back();
            break;
        case REV32(INFO):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(DIAL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create INFO record in mod \"%s\". Parent record type (%s) is invalid, only DIAL records can be INFO parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::DIALRecord *)ParentRecord)->INFO.push_back(new FNV::INFORecord((FNV::INFORecord *)SourceRecord));
            newRecord = ((FNV::DIALRecord *)ParentRecord)->INFO.back();
            break;
        case REV32(ACHR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create ACHR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACHR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->ACHR.push_back(new FNV::ACHRRecord((FNV::ACHRRecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->ACHR.back();
            break;
        case REV32(ACRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create ACRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACRE parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->ACRE.push_back(new FNV::ACRERecord((FNV::ACRERecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->ACRE.back();
            break;
        case REV32(REFR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create REFR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->REFR.push_back(new FNV::REFRRecord((FNV::REFRRecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->REFR.back();
            break;
        case REV32(PGRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create PGRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PGRE.push_back(new FNV::PGRERecord((FNV::PGRERecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->PGRE.back();
            break;
        case REV32(PMIS):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create PMIS record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PMIS.push_back(new FNV::PMISRecord((FNV::PMISRecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->PMIS.back();
            break;
        case REV32(PBEA):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create PBEA record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PBEA.push_back(new FNV::PBEARecord((FNV::PBEARecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->PBEA.back();
            break;
        case REV32(PFLA):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create PFLA record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PFLA.push_back(new FNV::PFLARecord((FNV::PFLARecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->PFLA.back();
            break;
        case REV32(PCBE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create PCBE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PCBE.push_back(new FNV::PCBERecord((FNV::PCBERecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->PCBE.back();
            break;
        case REV32(NAVM):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create NAVM record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->NAVM.push_back(new FNV::NAVMRecord((FNV::NAVMRecord *)SourceRecord));
            newRecord = ((FNV::CELLRecord *)ParentRecord)->NAVM.back();
            break;
        case REV32(LAND):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("FNVFile::CreateRecord: Error - Unable to create LAND record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be LAND parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            //If a cell land already exists, return it instead of making a new one
            if(((FNV::CELLRecord *)ParentRecord)->LAND != NULL)
                {
                options.ExistingReturned = true;
                return ((FNV::CELLRecord *)ParentRecord)->LAND;
                }

            ((FNV::CELLRecord *)ParentRecord)->LAND = new FNV::LANDRecord((FNV::LANDRecord *)SourceRecord);
            newRecord = ((FNV::CELLRecord *)ParentRecord)->LAND;
            break;
        case REV32(QUST):
            QUST.Records.push_back(new FNV::QUSTRecord((FNV::QUSTRecord *)SourceRecord));
            newRecord = QUST.Records.back();
            break;
        case REV32(IDLE):
            IDLE.Records.push_back(new FNV::IDLERecord((FNV::IDLERecord *)SourceRecord));
            newRecord = IDLE.Records.back();
            break;
        case REV32(PACK):
            PACK.Records.push_back(new FNV::PACKRecord((FNV::PACKRecord *)SourceRecord));
            newRecord = PACK.Records.back();
            break;
        case REV32(CSTY):
            CSTY.Records.push_back(new FNV::CSTYRecord((FNV::CSTYRecord *)SourceRecord));
            newRecord = CSTY.Records.back();
            break;
        case REV32(LSCR):
            LSCR.Records.push_back(new FNV::LSCRRecord((FNV::LSCRRecord *)SourceRecord));
            newRecord = LSCR.Records.back();
            break;
        case REV32(ANIO):
            ANIO.Records.push_back(new FNV::ANIORecord((FNV::ANIORecord *)SourceRecord));
            newRecord = ANIO.Records.back();
            break;
        case REV32(WATR):
            WATR.Records.push_back(new FNV::WATRRecord((FNV::WATRRecord *)SourceRecord));
            newRecord = WATR.Records.back();
            break;
        case REV32(EFSH):
            EFSH.Records.push_back(new FNV::EFSHRecord((FNV::EFSHRecord *)SourceRecord));
            newRecord = EFSH.Records.back();
            break;
        case REV32(EXPL):
            EXPL.Records.push_back(new FNV::EXPLRecord((FNV::EXPLRecord *)SourceRecord));
            newRecord = EXPL.Records.back();
            break;
        case REV32(DEBR):
            DEBR.Records.push_back(new FNV::DEBRRecord((FNV::DEBRRecord *)SourceRecord));
            newRecord = DEBR.Records.back();
            break;
        case REV32(IMGS):
            //IMGS.Records.push_back(new FNV::IMGSRecord((FNV::IMGSRecord *)SourceRecord));
            //newRecord = IMGS.Records.back();
            //break;
        case REV32(IMAD):
            //IMAD.Records.push_back(new FNV::IMADRecord((FNV::IMADRecord *)SourceRecord));
            //newRecord = IMAD.Records.back();
            //break;
        case REV32(FLST):
            //FLST.Records.push_back(new FNV::FLSTRecord((FNV::FLSTRecord *)SourceRecord));
            //newRecord = FLST.Records.back();
            //break;
        case REV32(PERK):
            //PERK.Records.push_back(new FNV::PERKRecord((FNV::PERKRecord *)SourceRecord));
            //newRecord = PERK.Records.back();
            //break;
        case REV32(BPTD):
            //BPTD.Records.push_back(new FNV::BPTDRecord((FNV::BPTDRecord *)SourceRecord));
            //newRecord = BPTD.Records.back();
            //break;
        case REV32(ADDN):
            //ADDN.Records.push_back(new FNV::ADDNRecord((FNV::ADDNRecord *)SourceRecord));
            //newRecord = ADDN.Records.back();
            //break;
        case REV32(AVIF):
            //AVIF.Records.push_back(new FNV::AVIFRecord((FNV::AVIFRecord *)SourceRecord));
            //newRecord = AVIF.Records.back();
            //break;
        case REV32(RADS):
            //RADS.Records.push_back(new FNV::RADSRecord((FNV::RADSRecord *)SourceRecord));
            //newRecord = RADS.Records.back();
            //break;
        case REV32(CAMS):
            //CAMS.Records.push_back(new FNV::CAMSRecord((FNV::CAMSRecord *)SourceRecord));
            //newRecord = CAMS.Records.back();
            //break;
        case REV32(CPTH):
            //CPTH.Records.push_back(new FNV::CPTHRecord((FNV::CPTHRecord *)SourceRecord));
            //newRecord = CPTH.Records.back();
            //break;
        case REV32(VTYP):
            //VTYP.Records.push_back(new FNV::VTYPRecord((FNV::VTYPRecord *)SourceRecord));
            //newRecord = VTYP.Records.back();
            //break;
        case REV32(IPCT):
            //IPCT.Records.push_back(new FNV::IPCTRecord((FNV::IPCTRecord *)SourceRecord));
            //newRecord = IPCT.Records.back();
            //break;
        case REV32(IPDS):
            //IPDS.Records.push_back(new FNV::IPDSRecord((FNV::IPDSRecord *)SourceRecord));
            //newRecord = IPDS.Records.back();
            //break;
        case REV32(ARMA):
            //ARMA.Records.push_back(new FNV::ARMARecord((FNV::ARMARecord *)SourceRecord));
            //newRecord = ARMA.Records.back();
            //break;
        case REV32(ECZN):
            //ECZN.Records.push_back(new FNV::ECZNRecord((FNV::ECZNRecord *)SourceRecord));
            //newRecord = ECZN.Records.back();
            //break;
        case REV32(MESG):
            //MESG.Records.push_back(new FNV::MESGRecord((FNV::MESGRecord *)SourceRecord));
            //newRecord = MESG.Records.back();
            //break;
        case REV32(RGDL):
            //RGDL.Records.push_back(new FNV::RGDLRecord((FNV::RGDLRecord *)SourceRecord));
            //newRecord = RGDL.Records.back();
            //break;
        case REV32(DOBJ):
            //DOBJ.Records.push_back(new FNV::DOBJRecord((FNV::DOBJRecord *)SourceRecord));
            //newRecord = DOBJ.Records.back();
            //break;
        case REV32(LGTM):
            //LGTM.Records.push_back(new FNV::LGTMRecord((FNV::LGTMRecord *)SourceRecord));
            //newRecord = LGTM.Records.back();
            //break;
        case REV32(MUSC):
            //MUSC.Records.push_back(new FNV::MUSCRecord((FNV::MUSCRecord *)SourceRecord));
            //newRecord = MUSC.Records.back();
            //break;
        case REV32(IMOD):
            //IMOD.Records.push_back(new FNV::IMODRecord((FNV::IMODRecord *)SourceRecord));
            //newRecord = IMOD.Records.back();
            //break;
        case REV32(REPU):
            //REPU.Records.push_back(new FNV::REPURecord((FNV::REPURecord *)SourceRecord));
            //newRecord = REPU.Records.back();
            //break;
        case REV32(RCPE):
            //RCPE.Records.push_back(new FNV::RCPERecord((FNV::RCPERecord *)SourceRecord));
            //newRecord = RCPE.Records.back();
            //break;
        case REV32(RCCT):
            //RCCT.Records.push_back(new FNV::RCCTRecord((FNV::RCCTRecord *)SourceRecord));
            //newRecord = RCCT.Records.back();
            //break;
        case REV32(CHIP):
            //CHIP.Records.push_back(new FNV::CHIPRecord((FNV::CHIPRecord *)SourceRecord));
            //newRecord = CHIP.Records.back();
            //break;
        case REV32(CSNO):
            //CSNO.Records.push_back(new FNV::CSNORecord((FNV::CSNORecord *)SourceRecord));
            //newRecord = CSNO.Records.back();
            //break;
        case REV32(LSCT):
            //LSCT.Records.push_back(new FNV::LSCTRecord((FNV::LSCTRecord *)SourceRecord));
            //newRecord = LSCT.Records.back();
            //break;
        case REV32(MSET):
            //MSET.Records.push_back(new FNV::MSETRecord((FNV::MSETRecord *)SourceRecord));
            //newRecord = MSET.Records.back();
            //break;
        case REV32(ALOC):
            //ALOC.Records.push_back(new FNV::ALOCRecord((FNV::ALOCRecord *)SourceRecord));
            //newRecord = ALOC.Records.back();
            //break;
        case REV32(CHAL):
            //CHAL.Records.push_back(new FNV::CHALRecord((FNV::CHALRecord *)SourceRecord));
            //newRecord = CHAL.Records.back();
            //break;
        case REV32(AMEF):
            //AMEF.Records.push_back(new FNV::AMEFRecord((FNV::AMEFRecord *)SourceRecord));
            //newRecord = AMEF.Records.back();
            //break;
        case REV32(CCRD):
            //CCRD.Records.push_back(new FNV::CCRDRecord((FNV::CCRDRecord *)SourceRecord));
            //newRecord = CCRD.Records.back();
            //break;
        case REV32(CMNY):
            //CMNY.Records.push_back(new FNV::CMNYRecord((FNV::CMNYRecord *)SourceRecord));
            //newRecord = CMNY.Records.back();
            //break;
        case REV32(CDCK):
            //CDCK.Records.push_back(new FNV::CDCKRecord((FNV::CDCKRecord *)SourceRecord));
            //newRecord = CDCK.Records.back();
            //break;
        case REV32(DEHY):
            //DEHY.Records.push_back(new FNV::DEHYRecord((FNV::DEHYRecord *)SourceRecord));
            //newRecord = DEHY.Records.back();
            //break;
        case REV32(HUNG):
            //HUNG.Records.push_back(new FNV::HUNGRecord((FNV::HUNGRecord *)SourceRecord));
            //newRecord = HUNG.Records.back();
            //break;
        case REV32(SLPD):
            //SLPD.Records.push_back(new FNV::SLPDRecord((FNV::SLPDRecord *)SourceRecord));
            //newRecord = SLPD.Records.back();
            //break;
        default:
            printf("FNVFile::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        }
    return newRecord;
    }

SINT32 FNVFile::CleanMasters(std::vector<FormIDResolver *> &Expanders)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("FNVFile::CleanMasters: Error - Unable to clean masters in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
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
        if(SOUN.VisitRecords(NULL, checker, false)) continue;
        if(ASPC.VisitRecords(NULL, checker, false)) continue;
        if(MGEF.VisitRecords(NULL, checker, false)) continue;
        if(SCPT.VisitRecords(NULL, checker, false)) continue;
        if(LTEX.VisitRecords(NULL, checker, false)) continue;
        if(ENCH.VisitRecords(NULL, checker, false)) continue;
        if(SPEL.VisitRecords(NULL, checker, false)) continue;
        if(ACTI.VisitRecords(NULL, checker, false)) continue;
        if(TACT.VisitRecords(NULL, checker, false)) continue;
        if(TERM.VisitRecords(NULL, checker, false)) continue;
        if(ARMO.VisitRecords(NULL, checker, false)) continue;
        if(BOOK.VisitRecords(NULL, checker, false)) continue;
        if(CONT.VisitRecords(NULL, checker, false)) continue;
        if(DOOR.VisitRecords(NULL, checker, false)) continue;
        if(INGR.VisitRecords(NULL, checker, false)) continue;
        if(LIGH.VisitRecords(NULL, checker, false)) continue;
        if(MISC.VisitRecords(NULL, checker, false)) continue;
        if(STAT.VisitRecords(NULL, checker, false)) continue;
        if(SCOL.VisitRecords(NULL, checker, false)) continue;
        if(MSTT.VisitRecords(NULL, checker, false)) continue;
        if(PWAT.VisitRecords(NULL, checker, false)) continue;
        if(GRAS.VisitRecords(NULL, checker, false)) continue;
        if(TREE.VisitRecords(NULL, checker, false)) continue;
        if(FURN.VisitRecords(NULL, checker, false)) continue;
        if(WEAP.VisitRecords(NULL, checker, false)) continue;
        if(AMMO.VisitRecords(NULL, checker, false)) continue;
        if(NPC_.VisitRecords(NULL, checker, false)) continue;
        if(CREA.VisitRecords(NULL, checker, false)) continue;
        if(LVLC.VisitRecords(NULL, checker, false)) continue;
        if(LVLN.VisitRecords(NULL, checker, false)) continue;
        if(KEYM.VisitRecords(NULL, checker, false)) continue;
        if(ALCH.VisitRecords(NULL, checker, false)) continue;
        if(IDLM.VisitRecords(NULL, checker, false)) continue;
        if(NOTE.VisitRecords(NULL, checker, false)) continue;
        if(COBJ.VisitRecords(NULL, checker, false)) continue;
        if(PROJ.VisitRecords(NULL, checker, false)) continue;
        if(LVLI.VisitRecords(NULL, checker, false)) continue;
        if(WTHR.VisitRecords(NULL, checker, false)) continue;
        if(CLMT.VisitRecords(NULL, checker, false)) continue;
        if(REGN.VisitRecords(NULL, checker, false)) continue;
        if(NAVI.VisitRecords(NULL, checker, false)) continue;
        if(CELL.VisitRecords(NULL, checker, true)) continue;
        if(WRLD.VisitRecords(NULL, checker, true)) continue;
        if(DIAL.VisitRecords(NULL, checker, true)) continue;
        if(QUST.VisitRecords(NULL, checker, false)) continue;
        if(IDLE.VisitRecords(NULL, checker, false)) continue;
        if(PACK.VisitRecords(NULL, checker, false)) continue;
        if(CSTY.VisitRecords(NULL, checker, false)) continue;
        if(LSCR.VisitRecords(NULL, checker, false)) continue;
        if(ANIO.VisitRecords(NULL, checker, false)) continue;
        if(WATR.VisitRecords(NULL, checker, false)) continue;
        if(EFSH.VisitRecords(NULL, checker, false)) continue;
        if(EXPL.VisitRecords(NULL, checker, false)) continue;
        if(DEBR.VisitRecords(NULL, checker, false)) continue;
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
        printf("FNVFile::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", reader.getModName());
        return -1;
        }

    FileWriter writer(SaveName, BUFFERSIZE);
    if(writer.open() == -1)
        throw std::exception("Unable to open temporary file for writing\n");

    UINT32 formCount = 0;
    FormIDResolver expander(FormIDHandler.ExpandTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    FormIDResolver collapser(FormIDHandler.CollapseTable, FormIDHandler.FileStart, FormIDHandler.FileEnd);
    //RecordReader reader(FormIDHandler);
    const bool bMastersChanged = FormIDHandler.MastersChanged();

    TES4.Write(writer, bMastersChanged, expander, collapser, Expanders);

    //ADD DEFINITIONS HERE
    formCount += GMST.WriteGRUP(REV32(GMST), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TXST.WriteGRUP(REV32(TXST), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MICN.WriteGRUP(REV32(MICN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GLOB.WriteGRUP(REV32(GLOB), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLAS.WriteGRUP(REV32(CLAS), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FACT.WriteGRUP(REV32(FACT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HDPT.WriteGRUP(REV32(HDPT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HAIR.WriteGRUP(REV32(HAIR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EYES.WriteGRUP(REV32(EYES), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += RACE.WriteGRUP(REV32(RACE), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SOUN.WriteGRUP(REV32(SOUN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ASPC.WriteGRUP(REV32(ASPC), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MGEF.WriteGRUP(REV32(MGEF), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCPT.WriteGRUP(REV32(SCPT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LTEX.WriteGRUP(REV32(LTEX), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ENCH.WriteGRUP(REV32(ENCH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SPEL.WriteGRUP(REV32(SPEL), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ACTI.WriteGRUP(REV32(ACTI), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TACT.WriteGRUP(REV32(TACT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TERM.WriteGRUP(REV32(TERM), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ARMO.WriteGRUP(REV32(ARMO), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BOOK.WriteGRUP(REV32(BOOK), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CONT.WriteGRUP(REV32(CONT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DOOR.WriteGRUP(REV32(DOOR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += INGR.WriteGRUP(REV32(INGR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LIGH.WriteGRUP(REV32(LIGH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MISC.WriteGRUP(REV32(MISC), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += STAT.WriteGRUP(REV32(STAT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCOL.WriteGRUP(REV32(SCOL), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MSTT.WriteGRUP(REV32(MSTT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PWAT.WriteGRUP(REV32(PWAT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GRAS.WriteGRUP(REV32(GRAS), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TREE.WriteGRUP(REV32(TREE), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FURN.WriteGRUP(REV32(FURN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WEAP.WriteGRUP(REV32(WEAP), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += AMMO.WriteGRUP(REV32(AMMO), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NPC_.WriteGRUP(REV32(NPC_), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CREA.WriteGRUP(REV32(CREA), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLC.WriteGRUP(REV32(LVLC), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLN.WriteGRUP(REV32(LVLN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += KEYM.WriteGRUP(REV32(KEYM), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ALCH.WriteGRUP(REV32(ALCH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLM.WriteGRUP(REV32(IDLM), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NOTE.WriteGRUP(REV32(NOTE), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += COBJ.WriteGRUP(REV32(COBJ), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PROJ.WriteGRUP(REV32(PROJ), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLI.WriteGRUP(REV32(LVLI), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WTHR.WriteGRUP(REV32(WTHR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLMT.WriteGRUP(REV32(CLMT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += REGN.WriteGRUP(REV32(REGN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NAVI.WriteGRUP(REV32(NAVI), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CELL.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WRLD.WriteGRUP(writer, FormIDHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DIAL.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += QUST.WriteGRUP(REV32(QUST), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLE.WriteGRUP(REV32(IDLE), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PACK.WriteGRUP(REV32(PACK), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CSTY.WriteGRUP(REV32(CSTY), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LSCR.WriteGRUP(REV32(LSCR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ANIO.WriteGRUP(REV32(ANIO), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WATR.WriteGRUP(REV32(WATR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EFSH.WriteGRUP(REV32(EFSH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EXPL.WriteGRUP(REV32(EXPL), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DEBR.WriteGRUP(REV32(DEBR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMGS.WriteGRUP(REV32(IMGS), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMAD.WriteGRUP(REV32(IMAD), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += FLST.WriteGRUP(REV32(FLST), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += PERK.WriteGRUP(REV32(PERK), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += BPTD.WriteGRUP(REV32(BPTD), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ADDN.WriteGRUP(REV32(ADDN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AVIF.WriteGRUP(REV32(AVIF), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RADS.WriteGRUP(REV32(RADS), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CAMS.WriteGRUP(REV32(CAMS), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CPTH.WriteGRUP(REV32(CPTH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += VTYP.WriteGRUP(REV32(VTYP), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IPCT.WriteGRUP(REV32(IPCT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IPDS.WriteGRUP(REV32(IPDS), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ARMA.WriteGRUP(REV32(ARMA), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ECZN.WriteGRUP(REV32(ECZN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MESG.WriteGRUP(REV32(MESG), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RGDL.WriteGRUP(REV32(RGDL), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DOBJ.WriteGRUP(REV32(DOBJ), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LGTM.WriteGRUP(REV32(LGTM), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MUSC.WriteGRUP(REV32(MUSC), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMOD.WriteGRUP(REV32(IMOD), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += REPU.WriteGRUP(REV32(REPU), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RCPE.WriteGRUP(REV32(RCPE), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RCCT.WriteGRUP(REV32(RCCT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CHIP.WriteGRUP(REV32(CHIP), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CSNO.WriteGRUP(REV32(CSNO), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LSCT.WriteGRUP(REV32(LSCT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MSET.WriteGRUP(REV32(MSET), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ALOC.WriteGRUP(REV32(ALOC), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CHAL.WriteGRUP(REV32(CHAL), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AMEF.WriteGRUP(REV32(AMEF), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CCRD.WriteGRUP(REV32(CCRD), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CMNY.WriteGRUP(REV32(CMNY), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CDCK.WriteGRUP(REV32(CDCK), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DEHY.WriteGRUP(REV32(DEHY), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += HUNG.WriteGRUP(REV32(HUNG), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += SLPD.WriteGRUP(REV32(SLPD), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    writer.file_write(34, &formCount, 4);
    writer.close();
    if(CloseMod)
        Close();
    return 0;
    }

void FNVFile::VisitAllRecords(RecordOp &op)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("FNVFile::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
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
    SOUN.VisitRecords(NULL, op, true);
    ASPC.VisitRecords(NULL, op, true);
    MGEF.VisitRecords(NULL, op, true);
    SCPT.VisitRecords(NULL, op, true);
    LTEX.VisitRecords(NULL, op, true);
    ENCH.VisitRecords(NULL, op, true);
    SPEL.VisitRecords(NULL, op, true);
    ACTI.VisitRecords(NULL, op, true);
    TACT.VisitRecords(NULL, op, true);
    TERM.VisitRecords(NULL, op, true);
    ARMO.VisitRecords(NULL, op, true);
    BOOK.VisitRecords(NULL, op, true);
    CONT.VisitRecords(NULL, op, true);
    DOOR.VisitRecords(NULL, op, true);
    INGR.VisitRecords(NULL, op, true);
    LIGH.VisitRecords(NULL, op, true);
    MISC.VisitRecords(NULL, op, true);
    STAT.VisitRecords(NULL, op, true);
    SCOL.VisitRecords(NULL, op, true);
    MSTT.VisitRecords(NULL, op, true);
    PWAT.VisitRecords(NULL, op, true);
    GRAS.VisitRecords(NULL, op, true);
    TREE.VisitRecords(NULL, op, true);
    FURN.VisitRecords(NULL, op, true);
    WEAP.VisitRecords(NULL, op, true);
    AMMO.VisitRecords(NULL, op, true);
    NPC_.VisitRecords(NULL, op, true);
    CREA.VisitRecords(NULL, op, true);
    LVLC.VisitRecords(NULL, op, true);
    LVLN.VisitRecords(NULL, op, true);
    KEYM.VisitRecords(NULL, op, true);
    ALCH.VisitRecords(NULL, op, true);
    IDLM.VisitRecords(NULL, op, true);
    NOTE.VisitRecords(NULL, op, true);
    COBJ.VisitRecords(NULL, op, true);
    PROJ.VisitRecords(NULL, op, true);
    LVLI.VisitRecords(NULL, op, true);
    WTHR.VisitRecords(NULL, op, true);
    CLMT.VisitRecords(NULL, op, true);
    REGN.VisitRecords(NULL, op, true);
    NAVI.VisitRecords(NULL, op, true);
    CELL.VisitRecords(NULL, op, true);
    WRLD.VisitRecords(NULL, op, true);
    DIAL.VisitRecords(NULL, op, true);
    QUST.VisitRecords(NULL, op, true);
    IDLE.VisitRecords(NULL, op, true);
    PACK.VisitRecords(NULL, op, true);
    CSTY.VisitRecords(NULL, op, true);
    LSCR.VisitRecords(NULL, op, true);
    ANIO.VisitRecords(NULL, op, true);
    WATR.VisitRecords(NULL, op, true);
    EFSH.VisitRecords(NULL, op, true);
    EXPL.VisitRecords(NULL, op, true);
    DEBR.VisitRecords(NULL, op, true);
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
        printf("FNVFile::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
        return;
        }

    //This visits only the top records specified.
    Record * topRecord = &TES4;
    switch(TopRecordType)
        {
        case REV32(TES4):
            op.Accept(topRecord);
            break;
        case REV32(GMST):
            GMST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(TXST):
            TXST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(MICN):
            MICN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(GLOB):
            GLOB.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CLAS):
            CLAS.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(FACT):
            FACT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(HDPT):
            HDPT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(HAIR):
            HAIR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(EYES):
            EYES.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(RACE):
            RACE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SOUN):
            SOUN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ASPC):
            ASPC.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(MGEF):
            MGEF.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SCPT):
            SCPT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LTEX):
            LTEX.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ENCH):
            ENCH.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SPEL):
            SPEL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ACTI):
            ACTI.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(TACT):
            TACT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(TERM):
            TERM.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ARMO):
            ARMO.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(BOOK):
            BOOK.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CONT):
            CONT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(DOOR):
            DOOR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(INGR):
            INGR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LIGH):
            LIGH.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(MISC):
            MISC.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(STAT):
            STAT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SCOL):
            SCOL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(MSTT):
            MSTT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(PWAT):
            PWAT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(GRAS):
            GRAS.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(TREE):
            TREE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(FURN):
            FURN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(WEAP):
            WEAP.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(AMMO):
            AMMO.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(NPC_):
            NPC_.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CREA):
            CREA.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LVLC):
            LVLC.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LVLN):
            LVLN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(KEYM):
            KEYM.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ALCH):
            ALCH.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(IDLM):
            IDLM.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(NOTE):
            NOTE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(COBJ):
            COBJ.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(PROJ):
            PROJ.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LVLI):
            LVLI.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(WTHR):
            WTHR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CLMT):
            CLMT.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(REGN):
            REGN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(NAVI):
            NAVI.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CELL):
            CELL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(WRLD):
            WRLD.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(DIAL):
            DIAL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(QUST):
            QUST.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(IDLE):
            IDLE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(PACK):
            PACK.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CSTY):
            CSTY.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LSCR):
            LSCR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ANIO):
            ANIO.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(WATR):
            WATR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(EFSH):
            EFSH.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(EXPL):
            EXPL.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(DEBR):
            DEBR.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(IMGS):
            //IMGS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(IMAD):
            //IMAD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(FLST):
            //FLST.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(PERK):
            //PERK.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(BPTD):
            //BPTD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(ADDN):
            //ADDN.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(AVIF):
            //AVIF.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(RADS):
            //RADS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(CAMS):
            //CAMS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(CPTH):
            //CPTH.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(VTYP):
            //VTYP.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(IPCT):
            //IPCT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(IPDS):
            //IPDS.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(ARMA):
            //ARMA.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(ECZN):
            //ECZN.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(MESG):
            //MESG.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(RGDL):
            //RGDL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(DOBJ):
            //DOBJ.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(LGTM):
            //LGTM.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(MUSC):
            //MUSC.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(IMOD):
            //IMOD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(REPU):
            //REPU.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(RCPE):
            //RCPE.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(RCCT):
            //RCCT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(CHIP):
            //CHIP.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(CSNO):
            //CSNO.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(LSCT):
            //LSCT.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(MSET):
            //MSET.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(ALOC):
            //ALOC.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(CHAL):
            //CHAL.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(AMEF):
            //AMEF.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(CCRD):
            //CCRD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(CMNY):
            //CMNY.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(CDCK):
            //CDCK.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(DEHY):
            //DEHY.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(HUNG):
            //HUNG.VisitRecords(RecordType, op, DeepVisit);
            //break;
        case REV32(SLPD):
            //SLPD.VisitRecords(RecordType, op, DeepVisit);
            //break;
        default:
            if(RecordType)
                printf("FNVFile::VisitRecords: Error - Unable to visit record type (%c%c%c%c) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ((STRING)&TopRecordType)[0], ((STRING)&TopRecordType)[1], ((STRING)&TopRecordType)[2], ((STRING)&TopRecordType)[3], reader.getModName());
            else
                printf("FNVFile::VisitRecords: Error - Unable to visit record type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&TopRecordType)[0], ((STRING)&TopRecordType)[1], ((STRING)&TopRecordType)[2], ((STRING)&TopRecordType)[3], reader.getModName());
            break;
        }
    return;
    }