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

 CBash copyright (C) 2010-2011 Waruddar
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
    if(TES4.IsLoaded() || !Open())
        {
        if(!TES4.IsLoaded() && !Open())
            printer("FNVFile::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", ModName);
        return 0;
        }
    buffer_position = buffer_start + 4;

    UINT32 recSize = 0;
    recSize = *(UINT32 *)buffer_position;
    buffer_position += 4;

    TES4.flags = *(UINT32 *)buffer_position;
    buffer_position += 4;

    TES4.formID = *(FORMID *)buffer_position;
    buffer_position += 4;

    TES4.flagsUnk = *(UINT32 *)buffer_position;
    buffer_position += 4;

    TES4.formVersion = *(UINT16 *)buffer_position;
    buffer_position += 2;

    TES4.versionControl2[0] = *(UINT8 *)buffer_position;
    buffer_position++;

    TES4.versionControl2[1] = *(UINT8 *)buffer_position;
    buffer_position++;

    if(TES4.IsLoaded())
        printer("_fIsLoaded Flag used!!!!: %08X\n", TES4.flags);

    TES4.SetData(buffer_position);
    TES4.Read();
    TES4.IsChanged(true); //prevents the record from ever being unloaded
    buffer_position += recSize;
    return 1;
    }

SINT32 FNVFile::Load(RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords)
    {
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

    if(Flags.IsIgnoreExisting || !file_map.is_open() || Flags.LoadedGRUPs)
        {
        if(!Flags.IsIgnoreExisting)
            {
            if(!file_map.is_open())
                printer("FNVFile::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", ModName);
            else
                printer("FNVFile::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", ModName);
            }
        return 0;
        }

    Flags.LoadedGRUPs = true;
    unsigned char *group_buffer_end = NULL;
    UINT32 GRUPSize;
    UINT32 GRUPLabel;
    boost::unordered_set<UINT32> UsedFormIDs;

    RecordReader read_parser(FormIDHandler, Expanders);
    RecordOp skip_parser;
    RecordOp &parser = Flags.IsFullLoad ? read_parser : skip_parser;

    RecordProcessor processor(FormIDHandler, Flags, UsedFormIDs);

    while(buffer_position < buffer_end){
        buffer_position += 4; //Skip "GRUP"
        GRUPSize = *(UINT32 *)buffer_position;
        group_buffer_end = buffer_position + GRUPSize - 4;
        buffer_position += 4;
        GRUPLabel = *(UINT32 *)buffer_position;
        buffer_position += 8; //Skip type (tops will all == 0)

        //printer("%c%c%c%c\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
        switch(GRUPLabel)
            {
            case eIgGMST:
            case REV32(GMST):
                GMST.Read(buffer_start, buffer_position, group_buffer_end, indexer, read_parser, DeletedRecords, processor, FileName);
                break;
            //case eIgTXST: //Same as normal
            case REV32(TXST):
                TXST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgMICN:
            case REV32(MICN):
                MICN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgGLOB:
            case REV32(GLOB):
                GLOB.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCLAS:
            case REV32(CLAS):
                CLAS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgFACT:
            case REV32(FACT):
                FACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgHDPT:
            case REV32(HDPT):
                HDPT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgHAIR:
            case REV32(HAIR):
                HAIR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgEYES: //Same as normal
            case REV32(EYES):
                EYES.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgRACE:
            case REV32(RACE):
                RACE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSOUN:
            case REV32(SOUN):
                SOUN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgASPC:  //Same as normal
            case REV32(ASPC):
                ASPC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgMGEF:
            case REV32(MGEF):
                MGEF.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSCPT:
            case REV32(SCPT):
                SCPT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLTEX: //Same as normal
            case REV32(LTEX):
                LTEX.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgENCH:
            case REV32(ENCH):
                ENCH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgSPEL: //Same as normal
            case REV32(SPEL):
                SPEL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgACTI:
            case REV32(ACTI):
                ACTI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgTACT:
            case REV32(TACT):
                TACT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgTERM:
            case REV32(TERM):
                TERM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgARMO: //Same as normal
            case REV32(ARMO):
                ARMO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgBOOK:
            case REV32(BOOK):
                BOOK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCONT:
            case REV32(CONT):
                CONT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgDOOR:
            case REV32(DOOR):
                DOOR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgINGR:
            case REV32(INGR):
                INGR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgLIGH:
            case REV32(LIGH):
                LIGH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgMISC:
            case REV32(MISC):
                MISC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgSTAT: //Same as normal
            case REV32(STAT):
                STAT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgSCOL:
            case REV32(SCOL):
                SCOL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgMSTT: //Same as normal
            case REV32(MSTT):
                MSTT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgPWAT: //Same as normal
            case REV32(PWAT):
                PWAT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgGRAS: //Same as normal
            case REV32(GRAS):
                GRAS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgTREE: //Same as normal
            case REV32(TREE):
                TREE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgFURN: //Same as normal
            case REV32(FURN):
                FURN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgWEAP:
            case REV32(WEAP):
                WEAP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgAMMO:
            case REV32(AMMO):
                AMMO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgNPC_: //Same as normal
            case REV32(NPC_):
                NPC_.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgCREA: //Same as normal
            case REV32(CREA):
                CREA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVLC: //Same as normal
            case REV32(LVLC):
                LVLC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVLN: //Same as normal
            case REV32(LVLN):
                LVLN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgKEYM:
            case REV32(KEYM):
                KEYM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgALCH:
            case REV32(ALCH):
                ALCH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgIDLM:
            case REV32(IDLM):
                IDLM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgNOTE:
            case REV32(NOTE):
                NOTE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCOBJ:
            case REV32(COBJ):
                COBJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgPROJ: //Same as normal
            case REV32(PROJ):
                PROJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLVLI: //Same as normal
            case REV32(LVLI):
                LVLI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgWTHR: //Same as normal
            case REV32(WTHR):
                WTHR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCLMT:
            case REV32(CLMT):
                CLMT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgREGN:
            case REV32(REGN):
                REGN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgNAVI:
            case REV32(NAVI):
                NAVI.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgCELL:
            case REV32(CELL):
                CELL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgWRLD: //Same as normal
            case REV32(WRLD):
                WRLD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName, read_parser, CELL);
                break;
            case eIgDIAL:
            case REV32(DIAL):
                DIAL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgQUST: //Same as normal
            case REV32(QUST):
                QUST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgIDLE:
            case REV32(IDLE):
                IDLE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgPACK:
            case REV32(PACK):
                PACK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgCSTY: //Same as normal
            case REV32(CSTY):
                CSTY.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgLSCR: //Same as normal
            case REV32(LSCR):
                LSCR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgANIO:
            case REV32(ANIO):
                ANIO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgWATR:
            case REV32(WATR):
                WATR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgEFSH:
            case REV32(EFSH):
                EFSH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            //case eIgEXPL: //Same as normal
            case REV32(EXPL):
                EXPL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgDEBR:
            case REV32(DEBR):
                DEBR.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                break;
            case eIgIMGS:
            case REV32(IMGS):
                //IMGS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgIMAD:
            case REV32(IMAD):
                //IMAD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgFLST:
            case REV32(FLST):
                //FLST.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgPERK:
            case REV32(PERK):
                //PERK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgBPTD: //Same as normal
            case REV32(BPTD):
                //BPTD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgADDN:
            case REV32(ADDN):
                //ADDN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgAVIF: //Same as normal
            case REV32(AVIF):
                //AVIF.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgRADS:
            case REV32(RADS):
                //RADS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCAMS:
            case REV32(CAMS):
                //CAMS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgCPTH: //Same as normal
            case REV32(CPTH):
                //CPTH.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgVTYP: //Same as normal
            case REV32(VTYP):
                //VTYP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgIPCT: //Same as normal
            case REV32(IPCT):
                //IPCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgIPDS: //Same as normal
            case REV32(IPDS):
                //IPDS.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgARMA: //Same as normal
            case REV32(ARMA):
                //ARMA.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgECZN:
            case REV32(ECZN):
                //ECZN.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgMESG:
            case REV32(MESG):
                //MESG.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgRGDL:
            case REV32(RGDL):
                //RGDL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgDOBJ:
            case REV32(DOBJ):
                //DOBJ.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgLGTM:
            case REV32(LGTM):
                //LGTM.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgMUSC: //Same as normal
            case REV32(MUSC):
                //MUSC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgIMOD:
            case REV32(IMOD):
                //IMOD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgREPU:
            case REV32(REPU):
                //REPU.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgRCPE:
            case REV32(RCPE):
                //RCPE.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgRCCT:
            case REV32(RCCT):
                //RCCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCHIP:
            case REV32(CHIP):
                //CHIP.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgCSNO: //Same as normal
            case REV32(CSNO):
                //CSNO.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgLSCT: //Same as normal
            case REV32(LSCT):
                //LSCT.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgMSET: //Same as normal
            case REV32(MSET):
                //MSET.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgALOC:
            case REV32(ALOC):
                //ALOC.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCHAL:
            case REV32(CHAL):
                //CHAL.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgAMEF:
            case REV32(AMEF):
                //AMEF.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCCRD:
            case REV32(CCRD):
                //CCRD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCMNY:
            case REV32(CMNY):
                //CMNY.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgCDCK:
            case REV32(CDCK):
                //CDCK.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgDEHY:
            case REV32(DEHY):
                //DEHY.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            //case eIgHUNG: //Same as normal
            case REV32(HUNG):
                //HUNG.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            case eIgSLPD:
            case REV32(SLPD):
                //SLPD.Read(buffer_start, buffer_position, group_buffer_end, indexer, parser, DeletedRecords, processor, FileName);
                //break;
            default:
                if(GRUPLabel == 0 && GRUPSize == 0)
                    {
                    printer("FNVFile::Read: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ModName);
                    return 1;
                    }
                //else
                //    printer("FNVFile::Read: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], ModName);

                if(GRUPSize == 0)
                    {
                    printer("Unable to continue loading.\n");
                    return 1;
                    }
                else
                    {
                    //printer("Attempting to skip and continue loading.\n");
                    buffer_position = group_buffer_end;
                    }
                break;
            }
        };

    FormIDHandler.IsEmpty = UsedFormIDs.empty();
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
    switch(RecordType)
        {
        case REV32(GMST):
            return (UINT32)GMST.pool.used_object_capacity();
        case REV32(TXST):
            return (UINT32)TXST.pool.used_object_capacity();
        case REV32(MICN):
            return (UINT32)MICN.pool.used_object_capacity();
        case REV32(GLOB):
            return (UINT32)GLOB.pool.used_object_capacity();
        case REV32(CLAS):
            return (UINT32)CLAS.pool.used_object_capacity();
        case REV32(FACT):
            return (UINT32)FACT.pool.used_object_capacity();
        case REV32(HDPT):
            return (UINT32)HDPT.pool.used_object_capacity();
        case REV32(HAIR):
            return (UINT32)HAIR.pool.used_object_capacity();
        case REV32(EYES):
            return (UINT32)EYES.pool.used_object_capacity();
        case REV32(RACE):
            return (UINT32)RACE.pool.used_object_capacity();
        case REV32(SOUN):
            return (UINT32)SOUN.pool.used_object_capacity();
        case REV32(ASPC):
            return (UINT32)ASPC.pool.used_object_capacity();
        case REV32(MGEF):
            return (UINT32)MGEF.pool.used_object_capacity();
        case REV32(SCPT):
            return (UINT32)SCPT.pool.used_object_capacity();
        case REV32(LTEX):
            return (UINT32)LTEX.pool.used_object_capacity();
        case REV32(ENCH):
            return (UINT32)ENCH.pool.used_object_capacity();
        case REV32(SPEL):
            return (UINT32)SPEL.pool.used_object_capacity();
        case REV32(ACTI):
            return (UINT32)ACTI.pool.used_object_capacity();
        case REV32(TACT):
            return (UINT32)TACT.pool.used_object_capacity();
        case REV32(TERM):
            return (UINT32)TERM.pool.used_object_capacity();
        case REV32(ARMO):
            return (UINT32)ARMO.pool.used_object_capacity();
        case REV32(BOOK):
            return (UINT32)BOOK.pool.used_object_capacity();
        case REV32(CONT):
            return (UINT32)CONT.pool.used_object_capacity();
        case REV32(DOOR):
            return (UINT32)DOOR.pool.used_object_capacity();
        case REV32(INGR):
            return (UINT32)INGR.pool.used_object_capacity();
        case REV32(LIGH):
            return (UINT32)LIGH.pool.used_object_capacity();
        case REV32(MISC):
            return (UINT32)MISC.pool.used_object_capacity();
        case REV32(STAT):
            return (UINT32)STAT.pool.used_object_capacity();
        case REV32(SCOL):
            return (UINT32)SCOL.pool.used_object_capacity();
        case REV32(MSTT):
            return (UINT32)MSTT.pool.used_object_capacity();
        case REV32(PWAT):
            return (UINT32)PWAT.pool.used_object_capacity();
        case REV32(GRAS):
            return (UINT32)GRAS.pool.used_object_capacity();
        case REV32(TREE):
            return (UINT32)TREE.pool.used_object_capacity();
        case REV32(FURN):
            return (UINT32)FURN.pool.used_object_capacity();
        case REV32(WEAP):
            return (UINT32)WEAP.pool.used_object_capacity();
        case REV32(AMMO):
            return (UINT32)AMMO.pool.used_object_capacity();
        case REV32(NPC_):
            return (UINT32)NPC_.pool.used_object_capacity();
        case REV32(CREA):
            return (UINT32)CREA.pool.used_object_capacity();
        case REV32(LVLC):
            return (UINT32)LVLC.pool.used_object_capacity();
        case REV32(LVLN):
            return (UINT32)LVLN.pool.used_object_capacity();
        case REV32(KEYM):
            return (UINT32)KEYM.pool.used_object_capacity();
        case REV32(ALCH):
            return (UINT32)ALCH.pool.used_object_capacity();
        case REV32(IDLM):
            return (UINT32)IDLM.pool.used_object_capacity();
        case REV32(NOTE):
            return (UINT32)NOTE.pool.used_object_capacity();
        case REV32(COBJ):
            return (UINT32)COBJ.pool.used_object_capacity();
        case REV32(PROJ):
            return (UINT32)PROJ.pool.used_object_capacity();
        case REV32(LVLI):
            return (UINT32)LVLI.pool.used_object_capacity();
        case REV32(WTHR):
            return (UINT32)WTHR.pool.used_object_capacity();
        case REV32(CLMT):
            return (UINT32)CLMT.pool.used_object_capacity();
        case REV32(REGN):
            return (UINT32)REGN.pool.used_object_capacity();
        case REV32(NAVI):
            return (UINT32)NAVI.pool.used_object_capacity();
        case REV32(CELL):
            return (UINT32)CELL.cell_pool.used_object_capacity();
        ///////////////////////////////////////////////
        //These return the absolute total number of these SubRecords
        //Use the GetFieldAttribute API instead if you want the number
        // of SubRecords associated with a specific parent record
        case REV32(INFO):
            return (UINT32)DIAL.info_pool.used_object_capacity();
        case REV32(ACHR):
            return (UINT32)CELL.achr_pool.used_object_capacity();
        case REV32(ACRE):
            return (UINT32)CELL.acre_pool.used_object_capacity();
        case REV32(REFR):
            return (UINT32)CELL.refr_pool.used_object_capacity();
        case REV32(PGRE):
            return (UINT32)CELL.pgre_pool.used_object_capacity();
        case REV32(PMIS):
            return (UINT32)CELL.pmis_pool.used_object_capacity();
        case REV32(PBEA):
            return (UINT32)CELL.pbea_pool.used_object_capacity();
        case REV32(PFLA):
            return (UINT32)CELL.pfla_pool.used_object_capacity();
        case REV32(PCBE):
            return (UINT32)CELL.pcbe_pool.used_object_capacity();
        case REV32(NAVM):
            return (UINT32)CELL.navm_pool.used_object_capacity();
        case REV32(LAND):
            return (UINT32)WRLD.land_pool.used_object_capacity();
        case REV32(WCEL):
            return (UINT32)WRLD.cell_pool.used_object_capacity();
        case REV32(CLLS):
            return (UINT32)CELL.cell_pool.used_object_capacity() + (UINT32)WRLD.cell_pool.used_object_capacity();
        ///////////////////////////////////////////////
        case REV32(WRLD):
            return (UINT32)WRLD.wrld_pool.used_object_capacity();
        case REV32(DIAL):
            return (UINT32)DIAL.dial_pool.used_object_capacity();
        case REV32(QUST):
            return (UINT32)QUST.pool.used_object_capacity();
        case REV32(IDLE):
            return (UINT32)IDLE.pool.used_object_capacity();
        case REV32(PACK):
            return (UINT32)PACK.pool.used_object_capacity();
        case REV32(CSTY):
            return (UINT32)CSTY.pool.used_object_capacity();
        case REV32(LSCR):
            return (UINT32)LSCR.pool.used_object_capacity();
        case REV32(ANIO):
            return (UINT32)ANIO.pool.used_object_capacity();
        case REV32(WATR):
            return (UINT32)WATR.pool.used_object_capacity();
        case REV32(EFSH):
            return (UINT32)EFSH.pool.used_object_capacity();
        case REV32(EXPL):
            return (UINT32)EXPL.pool.used_object_capacity();
        case REV32(DEBR):
            return (UINT32)DEBR.pool.used_object_capacity();
        case REV32(IMGS):
            //return (UINT32)IMGS.pool.used_object_capacity();
        case REV32(IMAD):
            //return (UINT32)IMAD.pool.used_object_capacity();
        case REV32(FLST):
            //return (UINT32)FLST.pool.used_object_capacity();
        case REV32(PERK):
            //return (UINT32)PERK.pool.used_object_capacity();
        case REV32(BPTD):
            //return (UINT32)BPTD.pool.used_object_capacity();
        case REV32(ADDN):
            //return (UINT32)ADDN.pool.used_object_capacity();
        case REV32(AVIF):
            //return (UINT32)AVIF.pool.used_object_capacity();
        case REV32(RADS):
            //return (UINT32)RADS.pool.used_object_capacity();
        case REV32(CAMS):
            //return (UINT32)CAMS.pool.used_object_capacity();
        case REV32(CPTH):
            //return (UINT32)CPTH.pool.used_object_capacity();
        case REV32(VTYP):
            //return (UINT32)VTYP.pool.used_object_capacity();
        case REV32(IPCT):
            //return (UINT32)IPCT.pool.used_object_capacity();
        case REV32(IPDS):
            //return (UINT32)IPDS.pool.used_object_capacity();
        case REV32(ARMA):
            //return (UINT32)ARMA.pool.used_object_capacity();
        case REV32(ECZN):
            //return (UINT32)ECZN.pool.used_object_capacity();
        case REV32(MESG):
            //return (UINT32)MESG.pool.used_object_capacity();
        case REV32(RGDL):
            //return (UINT32)RGDL.pool.used_object_capacity();
        case REV32(DOBJ):
            //return (UINT32)DOBJ.pool.used_object_capacity();
        case REV32(LGTM):
            //return (UINT32)LGTM.pool.used_object_capacity();
        case REV32(MUSC):
            //return (UINT32)MUSC.pool.used_object_capacity();
        case REV32(IMOD):
            //return (UINT32)IMOD.pool.used_object_capacity();
        case REV32(REPU):
            //return (UINT32)REPU.pool.used_object_capacity();
        case REV32(RCPE):
            //return (UINT32)RCPE.pool.used_object_capacity();
        case REV32(RCCT):
            //return (UINT32)RCCT.pool.used_object_capacity();
        case REV32(CHIP):
            //return (UINT32)CHIP.pool.used_object_capacity();
        case REV32(CSNO):
            //return (UINT32)CSNO.pool.used_object_capacity();
        case REV32(LSCT):
            //return (UINT32)LSCT.pool.used_object_capacity();
        case REV32(MSET):
            //return (UINT32)MSET.pool.used_object_capacity();
        case REV32(ALOC):
            //return (UINT32)ALOC.pool.used_object_capacity();
        case REV32(CHAL):
            //return (UINT32)CHAL.pool.used_object_capacity();
        case REV32(AMEF):
            //return (UINT32)AMEF.pool.used_object_capacity();
        case REV32(CCRD):
            //return (UINT32)CCRD.pool.used_object_capacity();
        case REV32(CMNY):
            //return (UINT32)CMNY.pool.used_object_capacity();
        case REV32(CDCK):
            //return (UINT32)CDCK.pool.used_object_capacity();
        case REV32(DEHY):
            //return (UINT32)DEHY.pool.used_object_capacity();
        case REV32(HUNG):
            //return (UINT32)HUNG.pool.used_object_capacity();
        case REV32(SLPD):
            //return (UINT32)SLPD.pool.used_object_capacity();
        default:
            printer("FNVFile::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ModName);
            break;
        }
    return 0;
    }

Record * FNVFile::CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options)
    {
    if(Flags.IsNoLoad)
        {
        printer("FNVFile::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return NULL;
        }

    Record *newRecord = NULL;

    switch(RecordType)
        {
        case REV32(GMST):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printer("FNVFile::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", ModName);
                return NULL;
                }
            newRecord = GMST.pool.construct(SourceRecord);

            if(RecordEditorID != NULL)
                {
                ((FNV::GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
                ((FNV::GMSTRecord *)newRecord)->DATA.format = ((FNV::GMSTRecord *)newRecord)->EDID.value[0];
                }
            break;
        case REV32(TXST):
            return TXST.pool.construct(SourceRecord);
        case REV32(MICN):
            return MICN.pool.construct(SourceRecord);
        case REV32(GLOB):
            return GLOB.pool.construct(SourceRecord);
        case REV32(CLAS):
            return CLAS.pool.construct(SourceRecord);
        case REV32(FACT):
            return FACT.pool.construct(SourceRecord);
        case REV32(HDPT):
            return HDPT.pool.construct(SourceRecord);
        case REV32(HAIR):
            return HAIR.pool.construct(SourceRecord);
        case REV32(EYES):
            return EYES.pool.construct(SourceRecord);
        case REV32(RACE):
            return RACE.pool.construct(SourceRecord);
        case REV32(SOUN):
            return SOUN.pool.construct(SourceRecord);
        case REV32(ASPC):
            return ASPC.pool.construct(SourceRecord);
        case REV32(MGEF):
            return MGEF.pool.construct(SourceRecord);
        case REV32(SCPT):
            return SCPT.pool.construct(SourceRecord);
        case REV32(LTEX):
            return LTEX.pool.construct(SourceRecord);
        case REV32(ENCH):
            return ENCH.pool.construct(SourceRecord);
        case REV32(SPEL):
            return SPEL.pool.construct(SourceRecord);
        case REV32(ACTI):
            return ACTI.pool.construct(SourceRecord);
        case REV32(TACT):
            return TACT.pool.construct(SourceRecord);
        case REV32(TERM):
            return TERM.pool.construct(SourceRecord);
        case REV32(ARMO):
            return ARMO.pool.construct(SourceRecord);
        case REV32(BOOK):
            return BOOK.pool.construct(SourceRecord);
        case REV32(CONT):
            return CONT.pool.construct(SourceRecord);
        case REV32(DOOR):
            return DOOR.pool.construct(SourceRecord);
        case REV32(INGR):
            return INGR.pool.construct(SourceRecord);
        case REV32(LIGH):
            return LIGH.pool.construct(SourceRecord);
        case REV32(MISC):
            return MISC.pool.construct(SourceRecord);
        case REV32(STAT):
            return STAT.pool.construct(SourceRecord);
        case REV32(SCOL):
            return SCOL.pool.construct(SourceRecord);
        case REV32(MSTT):
            return MSTT.pool.construct(SourceRecord);
        case REV32(PWAT):
            return PWAT.pool.construct(SourceRecord);
        case REV32(GRAS):
            return GRAS.pool.construct(SourceRecord);
        case REV32(TREE):
            return TREE.pool.construct(SourceRecord);
        case REV32(FURN):
            return FURN.pool.construct(SourceRecord);
        case REV32(WEAP):
            return WEAP.pool.construct(SourceRecord);
        case REV32(AMMO):
            return AMMO.pool.construct(SourceRecord);
        case REV32(NPC_):
            return NPC_.pool.construct(SourceRecord);
        case REV32(CREA):
            return CREA.pool.construct(SourceRecord);
        case REV32(LVLC):
            return LVLC.pool.construct(SourceRecord);
        case REV32(LVLN):
            return LVLN.pool.construct(SourceRecord);
        case REV32(KEYM):
            return KEYM.pool.construct(SourceRecord);
        case REV32(ALCH):
            return ALCH.pool.construct(SourceRecord);
        case REV32(IDLM):
            return IDLM.pool.construct(SourceRecord);
        case REV32(NOTE):
            return NOTE.pool.construct(SourceRecord);
        case REV32(COBJ):
            return COBJ.pool.construct(SourceRecord);
        case REV32(PROJ):
            return PROJ.pool.construct(SourceRecord);
        case REV32(LVLI):
            return LVLI.pool.construct(SourceRecord);
        case REV32(WTHR):
            return WTHR.pool.construct(SourceRecord);
        case REV32(CLMT):
            return CLMT.pool.construct(SourceRecord);
        case REV32(REGN):
            return REGN.pool.construct(SourceRecord);
        case REV32(NAVI):
            return NAVI.pool.construct(SourceRecord);
        case REV32(WCEL):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(WRLD))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create world CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be world CELL parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            //If a world cell already exists, return it instead of making a new one
            if(((FNV::WRLDRecord *)ParentRecord)->CELL != NULL)
                {
                options.ExistingReturned = true;
                return ((FNV::WRLDRecord *)ParentRecord)->CELL;
                }

            ((FNV::WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord);
            ((FNV::CELLRecord *)((FNV::WRLDRecord *)ParentRecord)->CELL)->IsInterior(false);
            ((FNV::CELLRecord *)((FNV::WRLDRecord *)ParentRecord)->CELL)->Parent = ParentRecord;
            return ((FNV::WRLDRecord *)ParentRecord)->CELL;
        case REV32(CELL):
            if(ParentRecord == NULL)
                {
                newRecord = CELL.cell_pool.construct(SourceRecord);
                ((FNV::CELLRecord *)newRecord)->IsInterior(true);
                return newRecord;
                }
            else
                {
                if(ParentRecord->GetType() != REV32(WRLD))
                    {
                    printer("FNVFile::CreateRecord: Error - Unable to create CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be CELL parents.\n", ModName, ParentRecord->GetStrType());
                    return NULL;
                    }

                //If the SourceRecord is a world cell, then the copy will be a world cell
                if(SourceRecord != NULL && ((FNV::WRLDRecord *)((FNV::CELLRecord *)SourceRecord)->Parent)->CELL == SourceRecord)
                    {
                    //If a world cell already exists, return it instead of making a new one
                    if(((FNV::WRLDRecord *)ParentRecord)->CELL != NULL)
                        {
                        options.ExistingReturned = true;
                        return ((FNV::WRLDRecord *)ParentRecord)->CELL;
                        }

                    newRecord = ((FNV::WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord);
                    }
                else
                    {
                    newRecord = WRLD.cell_pool.construct(SourceRecord);
                    ((FNV::WRLDRecord *)ParentRecord)->CELLS.push_back(newRecord);
                    }

                ((FNV::CELLRecord *)newRecord)->IsInterior(false);
                ((FNV::CELLRecord *)newRecord)->Parent = ParentRecord;
                return newRecord;
                }
        case REV32(WRLD):
            return WRLD.wrld_pool.construct(SourceRecord);
        case REV32(DIAL):
            return DIAL.dial_pool.construct(SourceRecord);
        case REV32(INFO):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(DIAL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create INFO record in mod \"%s\". Parent record type (%s) is invalid, only DIAL records can be INFO parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::DIALRecord *)ParentRecord)->INFO.push_back(DIAL.info_pool.construct(SourceRecord));
            ((FNV::INFORecord *)((FNV::DIALRecord *)ParentRecord)->INFO.back())->Parent = ParentRecord;
            return ((FNV::DIALRecord *)ParentRecord)->INFO.back();
        case REV32(ACHR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create ACHR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACHR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->ACHR.push_back(CELL.achr_pool.construct(SourceRecord));
            ((FNV::ACHRRecord *)((FNV::CELLRecord *)ParentRecord)->ACHR.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->ACHR.back();
        case REV32(ACRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create ACRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACRE parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->ACRE.push_back(CELL.acre_pool.construct(SourceRecord));
            ((FNV::ACRERecord *)((FNV::CELLRecord *)ParentRecord)->ACRE.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->ACRE.back();
        case REV32(REFR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create REFR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->REFR.push_back(CELL.refr_pool.construct(SourceRecord));
            ((FNV::REFRRecord *)((FNV::CELLRecord *)ParentRecord)->REFR.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->REFR.back();
        case REV32(PGRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create PGRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PGRE.push_back(CELL.pgre_pool.construct(SourceRecord));
            ((FNV::PGRERecord *)((FNV::CELLRecord *)ParentRecord)->PGRE.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->PGRE.back();
        case REV32(PMIS):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create PMIS record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PMIS.push_back(CELL.pmis_pool.construct(SourceRecord));
            ((FNV::PMISRecord *)((FNV::CELLRecord *)ParentRecord)->PMIS.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->PMIS.back();
        case REV32(PBEA):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create PBEA record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PBEA.push_back(CELL.pbea_pool.construct(SourceRecord));
            ((FNV::PBEARecord *)((FNV::CELLRecord *)ParentRecord)->PBEA.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->PBEA.back();
        case REV32(PFLA):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create PFLA record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PFLA.push_back(CELL.pfla_pool.construct(SourceRecord));
            ((FNV::PFLARecord *)((FNV::CELLRecord *)ParentRecord)->PFLA.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->PFLA.back();
        case REV32(PCBE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create PCBE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->PCBE.push_back(CELL.pcbe_pool.construct(SourceRecord));
            ((FNV::PCBERecord *)((FNV::CELLRecord *)ParentRecord)->PCBE.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->PCBE.back();
        case REV32(NAVM):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create NAVM record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            ((FNV::CELLRecord *)ParentRecord)->NAVM.push_back(CELL.navm_pool.construct(SourceRecord));
            ((FNV::NAVMRecord *)((FNV::CELLRecord *)ParentRecord)->NAVM.back())->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->NAVM.back();
        case REV32(LAND):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("FNVFile::CreateRecord: Error - Unable to create LAND record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be LAND parents.\n", ModName, ParentRecord->GetStrType());
                return NULL;
                }

            //If a cell land already exists, return it instead of making a new one
            if(((FNV::CELLRecord *)ParentRecord)->LAND != NULL)
                {
                options.ExistingReturned = true;
                return ((FNV::CELLRecord *)ParentRecord)->LAND;
                }

            ((FNV::CELLRecord *)ParentRecord)->LAND = WRLD.land_pool.construct(SourceRecord);
            ((FNV::LANDRecord *)((FNV::CELLRecord *)ParentRecord)->LAND)->Parent = ParentRecord;
            return ((FNV::CELLRecord *)ParentRecord)->LAND;
        case REV32(QUST):
            return QUST.pool.construct(SourceRecord);
        case REV32(IDLE):
            return IDLE.pool.construct(SourceRecord);
        case REV32(PACK):
            return PACK.pool.construct(SourceRecord);
        case REV32(CSTY):
            return CSTY.pool.construct(SourceRecord);
        case REV32(LSCR):
            return LSCR.pool.construct(SourceRecord);
        case REV32(ANIO):
            return ANIO.pool.construct(SourceRecord);
        case REV32(WATR):
            return WATR.pool.construct(SourceRecord);
        case REV32(EFSH):
            return EFSH.pool.construct(SourceRecord);
        case REV32(EXPL):
            return EXPL.pool.construct(SourceRecord);
        case REV32(DEBR):
            return DEBR.pool.construct(SourceRecord);
        case REV32(IMGS):
            //return IMGS.pool.construct(SourceRecord);
        case REV32(IMAD):
            //return IMAD.pool.construct(SourceRecord);
        case REV32(FLST):
            //return FLST.pool.construct(SourceRecord);
        case REV32(PERK):
            //return PERK.pool.construct(SourceRecord);
        case REV32(BPTD):
            //return BPTD.pool.construct(SourceRecord);
        case REV32(ADDN):
            //return ADDN.pool.construct(SourceRecord);
        case REV32(AVIF):
            //return AVIF.pool.construct(SourceRecord);
        case REV32(RADS):
            //return RADS.pool.construct(SourceRecord);
        case REV32(CAMS):
            //return CAMS.pool.construct(SourceRecord);
        case REV32(CPTH):
            //return CPTH.pool.construct(SourceRecord);
        case REV32(VTYP):
            //return VTYP.pool.construct(SourceRecord);
        case REV32(IPCT):
            //return IPCT.pool.construct(SourceRecord);
        case REV32(IPDS):
            //return IPDS.pool.construct(SourceRecord);
        case REV32(ARMA):
            //return ARMA.pool.construct(SourceRecord);
        case REV32(ECZN):
            //return ECZN.pool.construct(SourceRecord);
        case REV32(MESG):
            //return MESG.pool.construct(SourceRecord);
        case REV32(RGDL):
            //return RGDL.pool.construct(SourceRecord);
        case REV32(DOBJ):
            //return DOBJ.pool.construct(SourceRecord);
        case REV32(LGTM):
            //return LGTM.pool.construct(SourceRecord);
        case REV32(MUSC):
            //return MUSC.pool.construct(SourceRecord);
        case REV32(IMOD):
            //return IMOD.pool.construct(SourceRecord);
        case REV32(REPU):
            //return REPU.pool.construct(SourceRecord);
        case REV32(RCPE):
            //return RCPE.pool.construct(SourceRecord);
        case REV32(RCCT):
            //return RCCT.pool.construct(SourceRecord);
        case REV32(CHIP):
            //return CHIP.pool.construct(SourceRecord);
        case REV32(CSNO):
            //return CSNO.pool.construct(SourceRecord);
        case REV32(LSCT):
            //return LSCT.pool.construct(SourceRecord);
        case REV32(MSET):
            //return MSET.pool.construct(SourceRecord);
        case REV32(ALOC):
            //return ALOC.pool.construct(SourceRecord);
        case REV32(CHAL):
            //return CHAL.pool.construct(SourceRecord);
        case REV32(AMEF):
            //return AMEF.pool.construct(SourceRecord);
        case REV32(CCRD):
            //return CCRD.pool.construct(SourceRecord);
        case REV32(CMNY):
            //return CMNY.pool.construct(SourceRecord);
        case REV32(CDCK):
            //return CDCK.pool.construct(SourceRecord);
        case REV32(DEHY):
            //return DEHY.pool.construct(SourceRecord);
        case REV32(HUNG):
            //return HUNG.pool.construct(SourceRecord);
        case REV32(SLPD):
            //return SLPD.pool.construct(SourceRecord);
        default:
            printer("FNVFile::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ModName);
            break;
        }
    return newRecord;
    }

SINT32 FNVFile::DeleteRecord(Record *&curRecord, RecordOp &deindexer)
    {
    switch(curRecord->GetType())
        {
        case REV32(GMST):
            deindexer.Accept(curRecord);
            GMST.pool.destroy(curRecord);
            return 1;
        case REV32(TXST):
            deindexer.Accept(curRecord);
            TXST.pool.destroy(curRecord);
            return 1;
        case REV32(MICN):
            deindexer.Accept(curRecord);
            MICN.pool.destroy(curRecord);
            return 1;
        case REV32(GLOB):
            deindexer.Accept(curRecord);
            GLOB.pool.destroy(curRecord);
            return 1;
        case REV32(CLAS):
            deindexer.Accept(curRecord);
            CLAS.pool.destroy(curRecord);
            return 1;
        case REV32(FACT):
            deindexer.Accept(curRecord);
            FACT.pool.destroy(curRecord);
            return 1;
        case REV32(HDPT):
            deindexer.Accept(curRecord);
            HDPT.pool.destroy(curRecord);
            return 1;
        case REV32(HAIR):
            deindexer.Accept(curRecord);
            HAIR.pool.destroy(curRecord);
            return 1;
        case REV32(EYES):
            deindexer.Accept(curRecord);
            EYES.pool.destroy(curRecord);
            return 1;
        case REV32(RACE):
            deindexer.Accept(curRecord);
            RACE.pool.destroy(curRecord);
            return 1;
        case REV32(SOUN):
            deindexer.Accept(curRecord);
            SOUN.pool.destroy(curRecord);
            return 1;
        case REV32(ASPC):
            deindexer.Accept(curRecord);
            ASPC.pool.destroy(curRecord);
            return 1;
        case REV32(MGEF):
            deindexer.Accept(curRecord);
            MGEF.pool.destroy(curRecord);
            return 1;
        case REV32(SCPT):
            deindexer.Accept(curRecord);
            SCPT.pool.destroy(curRecord);
            return 1;
        case REV32(LTEX):
            deindexer.Accept(curRecord);
            LTEX.pool.destroy(curRecord);
            return 1;
        case REV32(ENCH):
            deindexer.Accept(curRecord);
            ENCH.pool.destroy(curRecord);
            return 1;
        case REV32(SPEL):
            deindexer.Accept(curRecord);
            SPEL.pool.destroy(curRecord);
            return 1;
        case REV32(ACTI):
            deindexer.Accept(curRecord);
            ACTI.pool.destroy(curRecord);
            return 1;
        case REV32(TACT):
            deindexer.Accept(curRecord);
            TACT.pool.destroy(curRecord);
            return 1;
        case REV32(TERM):
            deindexer.Accept(curRecord);
            TERM.pool.destroy(curRecord);
            return 1;
        case REV32(ARMO):
            deindexer.Accept(curRecord);
            ARMO.pool.destroy(curRecord);
            return 1;
        case REV32(BOOK):
            deindexer.Accept(curRecord);
            BOOK.pool.destroy(curRecord);
            return 1;
        case REV32(CONT):
            deindexer.Accept(curRecord);
            CONT.pool.destroy(curRecord);
            return 1;
        case REV32(DOOR):
            deindexer.Accept(curRecord);
            DOOR.pool.destroy(curRecord);
            return 1;
        case REV32(INGR):
            deindexer.Accept(curRecord);
            INGR.pool.destroy(curRecord);
            return 1;
        case REV32(LIGH):
            deindexer.Accept(curRecord);
            LIGH.pool.destroy(curRecord);
            return 1;
        case REV32(MISC):
            deindexer.Accept(curRecord);
            MISC.pool.destroy(curRecord);
            return 1;
        case REV32(STAT):
            deindexer.Accept(curRecord);
            STAT.pool.destroy(curRecord);
            return 1;
        case REV32(SCOL):
            deindexer.Accept(curRecord);
            SCOL.pool.destroy(curRecord);
            return 1;
        case REV32(MSTT):
            deindexer.Accept(curRecord);
            MSTT.pool.destroy(curRecord);
            return 1;
        case REV32(PWAT):
            deindexer.Accept(curRecord);
            PWAT.pool.destroy(curRecord);
            return 1;
        case REV32(GRAS):
            deindexer.Accept(curRecord);
            GRAS.pool.destroy(curRecord);
            return 1;
        case REV32(TREE):
            deindexer.Accept(curRecord);
            TREE.pool.destroy(curRecord);
            return 1;
        case REV32(FURN):
            deindexer.Accept(curRecord);
            FURN.pool.destroy(curRecord);
            return 1;
        case REV32(WEAP):
            deindexer.Accept(curRecord);
            WEAP.pool.destroy(curRecord);
            return 1;
        case REV32(AMMO):
            deindexer.Accept(curRecord);
            AMMO.pool.destroy(curRecord);
            return 1;
        case REV32(NPC_):
            deindexer.Accept(curRecord);
            NPC_.pool.destroy(curRecord);
            return 1;
        case REV32(CREA):
            deindexer.Accept(curRecord);
            CREA.pool.destroy(curRecord);
            return 1;
        case REV32(LVLC):
            deindexer.Accept(curRecord);
            LVLC.pool.destroy(curRecord);
            return 1;
        case REV32(LVLN):
            deindexer.Accept(curRecord);
            LVLN.pool.destroy(curRecord);
            return 1;
        case REV32(KEYM):
            deindexer.Accept(curRecord);
            KEYM.pool.destroy(curRecord);
            return 1;
        case REV32(ALCH):
            deindexer.Accept(curRecord);
            ALCH.pool.destroy(curRecord);
            return 1;
        case REV32(IDLM):
            deindexer.Accept(curRecord);
            IDLM.pool.destroy(curRecord);
            return 1;
        case REV32(NOTE):
            deindexer.Accept(curRecord);
            NOTE.pool.destroy(curRecord);
            return 1;
        case REV32(COBJ):
            deindexer.Accept(curRecord);
            COBJ.pool.destroy(curRecord);
            return 1;
        case REV32(PROJ):
            deindexer.Accept(curRecord);
            PROJ.pool.destroy(curRecord);
            return 1;
        case REV32(LVLI):
            deindexer.Accept(curRecord);
            LVLI.pool.destroy(curRecord);
            return 1;
        case REV32(WTHR):
            deindexer.Accept(curRecord);
            WTHR.pool.destroy(curRecord);
            return 1;
        case REV32(CLMT):
            deindexer.Accept(curRecord);
            CLMT.pool.destroy(curRecord);
            return 1;
        case REV32(REGN):
            deindexer.Accept(curRecord);
            REGN.pool.destroy(curRecord);
            return 1;
        case REV32(NAVI):
            deindexer.Accept(curRecord);
            NAVI.pool.destroy(curRecord);
            return 1;
        case REV32(CELL):
            {
            FNV::WRLDRecord *wrld_record = (FNV::WRLDRecord *)curRecord->GetParent();
            bool cell_found = false;
            if(wrld_record != NULL)
                {
                if(wrld_record->CELL == curRecord)
                    {
                    wrld_record->CELL = NULL;
                    cell_found = true;
                    }
                else
                    {
                    for(UINT32 ListIndex = 0; ListIndex < wrld_record->CELLS.size(); ++ListIndex)
                        {
                        if(wrld_record->CELLS[ListIndex] == curRecord)
                            {
                            wrld_record->CELLS.erase(wrld_record->CELLS.begin() + ListIndex);
                            cell_found = true;
                            break;
                            }
                        }
                    }
                if(!cell_found)
                    {
                    printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                    return 0;
                    }
                }
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->ACHR.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->ACHR[ListIndex]);
                CELL.achr_pool.destroy(cell_record->ACHR[ListIndex]);
                }

            for(UINT32 ListIndex = 0; ListIndex < cell_record->ACRE.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->ACRE[ListIndex]);
                CELL.acre_pool.destroy(cell_record->ACRE[ListIndex]);
                }

            for(UINT32 ListIndex = 0; ListIndex < cell_record->REFR.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->REFR[ListIndex]);
                CELL.refr_pool.destroy(cell_record->REFR[ListIndex]);
                }

            for(UINT32 ListIndex = 0; ListIndex < cell_record->PGRE.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->PGRE[ListIndex]);
                CELL.pgre_pool.destroy(cell_record->PGRE[ListIndex]);
                }

            for(UINT32 ListIndex = 0; ListIndex < cell_record->PMIS.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->PMIS[ListIndex]);
                CELL.pmis_pool.destroy(cell_record->PMIS[ListIndex]);
                }

            for(UINT32 ListIndex = 0; ListIndex < cell_record->PBEA.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->PBEA[ListIndex]);
                CELL.pbea_pool.destroy(cell_record->PBEA[ListIndex]);
                }

            for(UINT32 ListIndex = 0; ListIndex < cell_record->PFLA.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->PFLA[ListIndex]);
                CELL.pfla_pool.destroy(cell_record->PFLA[ListIndex]);
                }

            for(UINT32 ListIndex = 0; ListIndex < cell_record->PCBE.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->PCBE[ListIndex]);
                CELL.pcbe_pool.destroy(cell_record->PCBE[ListIndex]);
                }

            for(UINT32 ListIndex = 0; ListIndex < cell_record->NAVM.size(); ++ListIndex)
                {
                deindexer.Accept(cell_record->NAVM[ListIndex]);
                CELL.navm_pool.destroy(cell_record->NAVM[ListIndex]);
                }

            deindexer.Accept(cell_record->LAND);
            WRLD.land_pool.destroy(cell_record->LAND);

            deindexer.Accept(curRecord);
            if(cell_found)
                WRLD.cell_pool.destroy(curRecord);
            else
                CELL.cell_pool.destroy(curRecord);
            }
            return 1;
        case REV32(WRLD):
            {
            FNV::WRLDRecord *wrld_record = (FNV::WRLDRecord *)curRecord;

            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)wrld_record->CELL;
            if(cell_record != NULL) //Add it to list of cells to be deleted
                wrld_record->CELLS.push_back(cell_record);

            for(UINT32 ListIndex = 0; ListIndex < wrld_record->CELLS.size(); ++ListIndex)
                {
                cell_record = (FNV::CELLRecord *)wrld_record->CELLS[ListIndex];
                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->ACHR.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->ACHR[ListX2Index]);
                    CELL.achr_pool.destroy(cell_record->ACHR[ListX2Index]);
                    }

                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->ACRE.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->ACRE[ListX2Index]);
                    CELL.acre_pool.destroy(cell_record->ACRE[ListX2Index]);
                    }

                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->REFR.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->REFR[ListX2Index]);
                    CELL.refr_pool.destroy(cell_record->REFR[ListX2Index]);
                    }

                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PGRE.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->PGRE[ListX2Index]);
                    CELL.pgre_pool.destroy(cell_record->PGRE[ListX2Index]);
                    }

                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PMIS.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->PMIS[ListX2Index]);
                    CELL.pmis_pool.destroy(cell_record->PMIS[ListX2Index]);
                    }

                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PBEA.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->PBEA[ListX2Index]);
                    CELL.pbea_pool.destroy(cell_record->PBEA[ListX2Index]);
                    }

                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PFLA.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->PFLA[ListX2Index]);
                    CELL.pfla_pool.destroy(cell_record->PFLA[ListX2Index]);
                    }

                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->PCBE.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->PCBE[ListX2Index]);
                    CELL.pcbe_pool.destroy(cell_record->PCBE[ListX2Index]);
                    }

                for(UINT32 ListX2Index = 0; ListX2Index < cell_record->NAVM.size(); ++ListX2Index)
                    {
                    deindexer.Accept(cell_record->NAVM[ListX2Index]);
                    CELL.navm_pool.destroy(cell_record->NAVM[ListX2Index]);
                    }

                deindexer.Accept(cell_record->LAND);
                WRLD.land_pool.destroy(cell_record->LAND);

                deindexer.Accept((Record *&)cell_record);
                WRLD.cell_pool.destroy(cell_record);
                }

            deindexer.Accept(curRecord);
            WRLD.wrld_pool.destroy(curRecord);
            }
            return 1;
        case REV32(DIAL):
            {
            FNV::DIALRecord *dial_record = (FNV::DIALRecord *)curRecord;
            for(UINT32 ListIndex = 0; ListIndex < dial_record->INFO.size(); ++ListIndex)
                {
                deindexer.Accept(dial_record->INFO[ListIndex]);
                DIAL.info_pool.destroy(dial_record->INFO[ListIndex]);
                }

            deindexer.Accept(curRecord);
            DIAL.dial_pool.destroy(curRecord);
            }
            return 1;
        case REV32(INFO):
            {
            FNV::DIALRecord *dial_record = (FNV::DIALRecord *)curRecord->GetParent();
            bool info_found = false;
            for(UINT32 ListIndex = 0; ListIndex < dial_record->INFO.size(); ++ListIndex)
                {
                if(dial_record->INFO[ListIndex] == curRecord)
                    {
                    dial_record->INFO.erase(dial_record->INFO.begin() + ListIndex);
                    info_found = true;
                    break;
                    }
                }
            if(!info_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            DIAL.info_pool.destroy(curRecord);
            }
            return 1;
        case REV32(ACHR):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool achr_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->ACHR.size(); ++ListIndex)
                {
                if(cell_record->ACHR[ListIndex] == curRecord)
                    {
                    cell_record->ACHR.erase(cell_record->ACHR.begin() + ListIndex);
                    achr_found = true;
                    break;
                    }
                }
            if(!achr_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.achr_pool.destroy(curRecord);
            }
            return 1;
        case REV32(ACRE):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->ACRE.size(); ++ListIndex)
                {
                if(cell_record->ACRE[ListIndex] == curRecord)
                    {
                    cell_record->ACRE.erase(cell_record->ACRE.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.acre_pool.destroy(curRecord);
            }
            return 1;
        case REV32(REFR):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->REFR.size(); ++ListIndex)
                {
                if(cell_record->REFR[ListIndex] == curRecord)
                    {
                    cell_record->REFR.erase(cell_record->REFR.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.refr_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PGRE):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PGRE.size(); ++ListIndex)
                {
                if(cell_record->PGRE[ListIndex] == curRecord)
                    {
                    cell_record->PGRE.erase(cell_record->PGRE.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pgre_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PMIS):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PMIS.size(); ++ListIndex)
                {
                if(cell_record->PMIS[ListIndex] == curRecord)
                    {
                    cell_record->PMIS.erase(cell_record->PMIS.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pmis_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PBEA):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PBEA.size(); ++ListIndex)
                {
                if(cell_record->PBEA[ListIndex] == curRecord)
                    {
                    cell_record->PBEA.erase(cell_record->PBEA.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pbea_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PFLA):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PFLA.size(); ++ListIndex)
                {
                if(cell_record->PFLA[ListIndex] == curRecord)
                    {
                    cell_record->PFLA.erase(cell_record->PFLA.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pfla_pool.destroy(curRecord);
            }
            return 1;
        case REV32(PCBE):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->PCBE.size(); ++ListIndex)
                {
                if(cell_record->PCBE[ListIndex] == curRecord)
                    {
                    cell_record->PCBE.erase(cell_record->PCBE.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.pcbe_pool.destroy(curRecord);
            }
            return 1;
        case REV32(NAVM):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();
            bool child_found = false;
            for(UINT32 ListIndex = 0; ListIndex < cell_record->NAVM.size(); ++ListIndex)
                {
                if(cell_record->NAVM[ListIndex] == curRecord)
                    {
                    cell_record->NAVM.erase(cell_record->NAVM.begin() + ListIndex);
                    child_found = true;
                    break;
                    }
                }
            if(!child_found)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            deindexer.Accept(curRecord);
            CELL.navm_pool.destroy(curRecord);
            }
            return 1;
        case REV32(LAND):
            {
            FNV::CELLRecord *cell_record = (FNV::CELLRecord *)curRecord->GetParent();

            if(cell_record->LAND != curRecord)
                {
                printer("FNVFile::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetParent()->GetStrType(), ModName, curRecord->GetParent()->formID, curRecord->formID);
                return 0;
                }

            cell_record->LAND = NULL;
            deindexer.Accept(curRecord);
            WRLD.land_pool.destroy(curRecord);
            }
            return 1;
        case REV32(QUST):
            deindexer.Accept(curRecord);
            QUST.pool.destroy(curRecord);
            return 1;
        case REV32(IDLE):
            deindexer.Accept(curRecord);
            IDLE.pool.destroy(curRecord);
            return 1;
        case REV32(PACK):
            deindexer.Accept(curRecord);
            PACK.pool.destroy(curRecord);
            return 1;
        case REV32(CSTY):
            deindexer.Accept(curRecord);
            CSTY.pool.destroy(curRecord);
            return 1;
        case REV32(LSCR):
            deindexer.Accept(curRecord);
            LSCR.pool.destroy(curRecord);
            return 1;
        case REV32(ANIO):
            deindexer.Accept(curRecord);
            ANIO.pool.destroy(curRecord);
            return 1;
        case REV32(WATR):
            deindexer.Accept(curRecord);
            WATR.pool.destroy(curRecord);
            return 1;
        case REV32(EFSH):
            deindexer.Accept(curRecord);
            EFSH.pool.destroy(curRecord);
            return 1;
        case REV32(EXPL):
            deindexer.Accept(curRecord);
            EXPL.pool.destroy(curRecord);
            return 1;
        case REV32(DEBR):
            deindexer.Accept(curRecord);
            DEBR.pool.destroy(curRecord);
            return 1;
        //case REV32(IMGS):
        //    deindexer.Accept(curRecord);
        //    IMGS.pool.destroy(curRecord);
        //    return 1;
        //case REV32(IMAD):
        //    deindexer.Accept(curRecord);
        //    IMAD.pool.destroy(curRecord);
        //    return 1;
        //case REV32(FLST):
        //    deindexer.Accept(curRecord);
        //    FLST.pool.destroy(curRecord);
        //    return 1;
        //case REV32(PERK):
        //    deindexer.Accept(curRecord);
        //    PERK.pool.destroy(curRecord);
        //    return 1;
        //case REV32(BPTD):
        //    deindexer.Accept(curRecord);
        //    BPTD.pool.destroy(curRecord);
        //    return 1;
        //case REV32(ADDN):
        //    deindexer.Accept(curRecord);
        //    ADDN.pool.destroy(curRecord);
        //    return 1;
        //case REV32(AVIF):
        //    deindexer.Accept(curRecord);
        //    AVIF.pool.destroy(curRecord);
        //    return 1;
        //case REV32(RADS):
        //    deindexer.Accept(curRecord);
        //    RADS.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CAMS):
        //    deindexer.Accept(curRecord);
        //    CAMS.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CPTH):
        //    deindexer.Accept(curRecord);
        //    CPTH.pool.destroy(curRecord);
        //    return 1;
        //case REV32(VTYP):
        //    deindexer.Accept(curRecord);
        //    VTYP.pool.destroy(curRecord);
        //    return 1;
        //case REV32(IPCT):
        //    deindexer.Accept(curRecord);
        //    IPCT.pool.destroy(curRecord);
        //    return 1;
        //case REV32(IPDS):
        //    deindexer.Accept(curRecord);
        //    IPDS.pool.destroy(curRecord);
        //    return 1;
        //case REV32(ARMA):
        //    deindexer.Accept(curRecord);
        //    ARMA.pool.destroy(curRecord);
        //    return 1;
        //case REV32(ECZN):
        //    deindexer.Accept(curRecord);
        //    ECZN.pool.destroy(curRecord);
        //    return 1;
        //case REV32(MESG):
        //    deindexer.Accept(curRecord);
        //    MESG.pool.destroy(curRecord);
        //    return 1;
        //case REV32(RGDL):
        //    deindexer.Accept(curRecord);
        //    RGDL.pool.destroy(curRecord);
        //    return 1;
        //case REV32(DOBJ):
        //    deindexer.Accept(curRecord);
        //    DOBJ.pool.destroy(curRecord);
        //    return 1;
        //case REV32(LGTM):
        //    deindexer.Accept(curRecord);
        //    LGTM.pool.destroy(curRecord);
        //    return 1;
        //case REV32(MUSC):
        //    deindexer.Accept(curRecord);
        //    MUSC.pool.destroy(curRecord);
        //    return 1;
        //case REV32(IMOD):
        //    deindexer.Accept(curRecord);
        //    IMOD.pool.destroy(curRecord);
        //    return 1;
        //case REV32(REPU):
        //    deindexer.Accept(curRecord);
        //    REPU.pool.destroy(curRecord);
        //    return 1;
        //case REV32(RCPE):
        //    deindexer.Accept(curRecord);
        //    RCPE.pool.destroy(curRecord);
        //    return 1;
        //case REV32(RCCT):
        //    deindexer.Accept(curRecord);
        //    RCCT.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CHIP):
        //    deindexer.Accept(curRecord);
        //    CHIP.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CSNO):
        //    deindexer.Accept(curRecord);
        //    CSNO.pool.destroy(curRecord);
        //    return 1;
        //case REV32(LSCT):
        //    deindexer.Accept(curRecord);
        //    LSCT.pool.destroy(curRecord);
        //    return 1;
        //case REV32(MSET):
        //    deindexer.Accept(curRecord);
        //    MSET.pool.destroy(curRecord);
        //    return 1;
        //case REV32(ALOC):
        //    deindexer.Accept(curRecord);
        //    ALOC.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CHAL):
        //    deindexer.Accept(curRecord);
        //    CHAL.pool.destroy(curRecord);
        //    return 1;
        //case REV32(AMEF):
        //    deindexer.Accept(curRecord);
        //    AMEF.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CCRD):
        //    deindexer.Accept(curRecord);
        //    CCRD.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CMNY):
        //    deindexer.Accept(curRecord);
        //    CMNY.pool.destroy(curRecord);
        //    return 1;
        //case REV32(CDCK):
        //    deindexer.Accept(curRecord);
        //    CDCK.pool.destroy(curRecord);
        //    return 1;
        //case REV32(DEHY):
        //    deindexer.Accept(curRecord);
        //    DEHY.pool.destroy(curRecord);
        //    return 1;
        //case REV32(HUNG):
        //    deindexer.Accept(curRecord);
        //    HUNG.pool.destroy(curRecord);
        //    return 1;
        //case REV32(SLPD):
        //    deindexer.Accept(curRecord);
        //    SLPD.pool.destroy(curRecord);
        //    return 1;
        default:
            {
            Record *Parent = curRecord->GetParent();
            if(Parent != NULL)
                {
                Record *TopParent = Parent->GetParent();
                if(TopParent != NULL)
                    printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) with parent type (%s) in group (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), Parent->GetStrType(), TopParent->GetStrType(), ModName, Parent->formID, curRecord->formID);
                else
                    printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) in group (%s) in mod \"%s\". The parent record (%08X) does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), Parent->GetStrType(), ModName, Parent->formID, curRecord->formID);
                }
            else
                printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) in group (%s) in mod \"%s\". The group does not contain the record to be deleted (%08X).\n", curRecord->GetStrType(), curRecord->GetStrType(), ModName, curRecord->formID);
            }
            return 0;
        }
    return 0;
    }

SINT32 FNVFile::CleanMasters(std::vector<FormIDResolver *> &Expanders)
    {
    if(Flags.IsNoLoad)
        {
        printer("FNVFile::CleanMasters: Error - Unable to clean masters in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
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
        RecordMasterChecker checker(FormIDHandler, Expanders, (UINT8)p);

        //printer("Checking: %s\n", TES4.MAST[p].value);
        if(checker.Accept(topRecord)) continue;
        if(GMST.pool.VisitRecords(checker)) continue;
        if(TXST.pool.VisitRecords(checker)) continue;
        if(MICN.pool.VisitRecords(checker)) continue;
        if(GLOB.pool.VisitRecords(checker)) continue;
        if(CLAS.pool.VisitRecords(checker)) continue;
        if(FACT.pool.VisitRecords(checker)) continue;
        if(HDPT.pool.VisitRecords(checker)) continue;
        if(HAIR.pool.VisitRecords(checker)) continue;
        if(EYES.pool.VisitRecords(checker)) continue;
        if(RACE.pool.VisitRecords(checker)) continue;
        if(SOUN.pool.VisitRecords(checker)) continue;
        if(ASPC.pool.VisitRecords(checker)) continue;
        if(MGEF.pool.VisitRecords(checker)) continue;
        if(SCPT.pool.VisitRecords(checker)) continue;
        if(LTEX.pool.VisitRecords(checker)) continue;
        if(ENCH.pool.VisitRecords(checker)) continue;
        if(SPEL.pool.VisitRecords(checker)) continue;
        if(ACTI.pool.VisitRecords(checker)) continue;
        if(TACT.pool.VisitRecords(checker)) continue;
        if(TERM.pool.VisitRecords(checker)) continue;
        if(ARMO.pool.VisitRecords(checker)) continue;
        if(BOOK.pool.VisitRecords(checker)) continue;
        if(CONT.pool.VisitRecords(checker)) continue;
        if(DOOR.pool.VisitRecords(checker)) continue;
        if(INGR.pool.VisitRecords(checker)) continue;
        if(LIGH.pool.VisitRecords(checker)) continue;
        if(MISC.pool.VisitRecords(checker)) continue;
        if(STAT.pool.VisitRecords(checker)) continue;
        if(SCOL.pool.VisitRecords(checker)) continue;
        if(MSTT.pool.VisitRecords(checker)) continue;
        if(PWAT.pool.VisitRecords(checker)) continue;
        if(GRAS.pool.VisitRecords(checker)) continue;
        if(TREE.pool.VisitRecords(checker)) continue;
        if(FURN.pool.VisitRecords(checker)) continue;
        if(WEAP.pool.VisitRecords(checker)) continue;
        if(AMMO.pool.VisitRecords(checker)) continue;
        if(NPC_.pool.VisitRecords(checker)) continue;
        if(CREA.pool.VisitRecords(checker)) continue;
        if(LVLC.pool.VisitRecords(checker)) continue;
        if(LVLN.pool.VisitRecords(checker)) continue;
        if(KEYM.pool.VisitRecords(checker)) continue;
        if(ALCH.pool.VisitRecords(checker)) continue;
        if(IDLM.pool.VisitRecords(checker)) continue;
        if(NOTE.pool.VisitRecords(checker)) continue;
        if(COBJ.pool.VisitRecords(checker)) continue;
        if(PROJ.pool.VisitRecords(checker)) continue;
        if(LVLI.pool.VisitRecords(checker)) continue;
        if(WTHR.pool.VisitRecords(checker)) continue;
        if(CLMT.pool.VisitRecords(checker)) continue;
        if(REGN.pool.VisitRecords(checker)) continue;
        if(NAVI.pool.VisitRecords(checker)) continue;
        if(QUST.pool.VisitRecords(checker)) continue;
        if(IDLE.pool.VisitRecords(checker)) continue;
        if(PACK.pool.VisitRecords(checker)) continue;
        if(CSTY.pool.VisitRecords(checker)) continue;
        if(LSCR.pool.VisitRecords(checker)) continue;
        if(ANIO.pool.VisitRecords(checker)) continue;
        if(WATR.pool.VisitRecords(checker)) continue;
        if(EFSH.pool.VisitRecords(checker)) continue;
        if(EXPL.pool.VisitRecords(checker)) continue;
        if(DEBR.pool.VisitRecords(checker)) continue;
        //if(IMGS.pool.VisitRecords(checker)) continue;
        //if(IMAD.pool.VisitRecords(checker)) continue;
        //if(FLST.pool.VisitRecords(checker)) continue;
        //if(PERK.pool.VisitRecords(checker)) continue;
        //if(BPTD.pool.VisitRecords(checker)) continue;
        //if(ADDN.pool.VisitRecords(checker)) continue;
        //if(AVIF.pool.VisitRecords(checker)) continue;
        //if(RADS.pool.VisitRecords(checker)) continue;
        //if(CAMS.pool.VisitRecords(checker)) continue;
        //if(CPTH.pool.VisitRecords(checker)) continue;
        //if(VTYP.pool.VisitRecords(checker)) continue;
        //if(IPCT.pool.VisitRecords(checker)) continue;
        //if(IPDS.pool.VisitRecords(checker)) continue;
        //if(ARMA.pool.VisitRecords(checker)) continue;
        //if(ECZN.pool.VisitRecords(checker)) continue;
        //if(MESG.pool.VisitRecords(checker)) continue;
        //if(RGDL.pool.VisitRecords(checker)) continue;
        //if(DOBJ.pool.VisitRecords(checker)) continue;
        //if(LGTM.pool.VisitRecords(checker)) continue;
        //if(MUSC.pool.VisitRecords(checker)) continue;
        //if(IMOD.pool.VisitRecords(checker)) continue;
        //if(REPU.pool.VisitRecords(checker)) continue;
        //if(RCPE.pool.VisitRecords(checker)) continue;
        //if(RCCT.pool.VisitRecords(checker)) continue;
        //if(CHIP.pool.VisitRecords(checker)) continue;
        //if(CSNO.pool.VisitRecords(checker)) continue;
        //if(LSCT.pool.VisitRecords(checker)) continue;
        //if(MSET.pool.VisitRecords(checker)) continue;
        //if(ALOC.pool.VisitRecords(checker)) continue;
        //if(CHAL.pool.VisitRecords(checker)) continue;
        //if(AMEF.pool.VisitRecords(checker)) continue;
        //if(CCRD.pool.VisitRecords(checker)) continue;
        //if(CMNY.pool.VisitRecords(checker)) continue;
        //if(CDCK.pool.VisitRecords(checker)) continue;
        //if(DEHY.pool.VisitRecords(checker)) continue;
        //if(HUNG.pool.VisitRecords(checker)) continue;
        //if(SLPD.pool.VisitRecords(checker)) continue;
        if(CELL.cell_pool.VisitRecords(checker)) continue;
        if(WRLD.wrld_pool.VisitRecords(checker)) continue;
        if(WRLD.cell_pool.VisitRecords(checker)) continue;
        if(WRLD.land_pool.VisitRecords(checker)) continue;
        if(DIAL.dial_pool.VisitRecords(checker)) continue;
        if(DIAL.info_pool.VisitRecords(checker)) continue;
        if(CELL.pgre_pool.VisitRecords(checker)) continue;
        if(CELL.pmis_pool.VisitRecords(checker)) continue;
        if(CELL.pbea_pool.VisitRecords(checker)) continue;
        if(CELL.pfla_pool.VisitRecords(checker)) continue;
        if(CELL.pcbe_pool.VisitRecords(checker)) continue;
        if(CELL.navm_pool.VisitRecords(checker)) continue;
        if(CELL.achr_pool.VisitRecords(checker)) continue;
        if(CELL.acre_pool.VisitRecords(checker)) continue;
        if(CELL.refr_pool.VisitRecords(checker)) continue;

        //printer("ToRemove: %s\n", TES4.MAST[p].value);
        ToRemove.push_back(p);
        ++cleaned;
        }
    if(cleaned)
        {
        for(SINT32 p = (SINT32)ToRemove.size() - 1; p >= 0; --p)
            {
            delete []TES4.MAST[ToRemove[p]];
            TES4.MAST.erase(TES4.MAST.begin() + ToRemove[p]);
            }
        FormIDHandler.UpdateFormIDLookup();
        }
    return cleaned;
    }

SINT32 FNVFile::Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod, RecordOp &indexer)
    {
    if(!Flags.IsSaveable)
        {
        printer("FNVFile::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", ModName);
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
    formCount += GMST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TXST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MICN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GLOB.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLAS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FACT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HDPT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HAIR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EYES.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += RACE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SOUN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ASPC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MGEF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCPT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LTEX.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ENCH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SPEL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ACTI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TACT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TERM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ARMO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BOOK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CONT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DOOR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += INGR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LIGH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MISC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += STAT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCOL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MSTT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PWAT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GRAS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TREE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FURN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WEAP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += AMMO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NPC_.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CREA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += KEYM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ALCH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NOTE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += COBJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PROJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WTHR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLMT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += REGN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NAVI.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CELL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WRLD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod, FormIDHandler, CELL, indexer);
    formCount += DIAL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += QUST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PACK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CSTY.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LSCR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ANIO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WATR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EFSH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EXPL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DEBR.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMGS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMAD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += FLST.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += PERK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += BPTD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ADDN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AVIF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RADS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CAMS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CPTH.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += VTYP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IPCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IPDS.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ARMA.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ECZN.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MESG.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RGDL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DOBJ.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LGTM.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MUSC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += IMOD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += REPU.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RCPE.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += RCCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CHIP.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CSNO.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += LSCT.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += MSET.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += ALOC.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CHAL.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += AMEF.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CCRD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CMNY.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += CDCK.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += DEHY.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += HUNG.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    //formCount += SLPD.Write(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    writer.file_write(34, &formCount, 4);
    writer.close();
    if(CloseMod)
        Close();
    return 0;
    }

void FNVFile::VisitAllRecords(RecordOp &op)
    {
    if(Flags.IsNoLoad)
        {
        printer("FNVFile::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return;
        }

    //This visits every record and subrecord
    {
    Record *temp = &TES4;
    op.Accept(temp);
    }
    GMST.pool.VisitRecords(op);
    TXST.pool.VisitRecords(op);
    MICN.pool.VisitRecords(op);
    GLOB.pool.VisitRecords(op);
    CLAS.pool.VisitRecords(op);
    FACT.pool.VisitRecords(op);
    HDPT.pool.VisitRecords(op);
    HAIR.pool.VisitRecords(op);
    EYES.pool.VisitRecords(op);
    RACE.pool.VisitRecords(op);
    SOUN.pool.VisitRecords(op);
    ASPC.pool.VisitRecords(op);
    MGEF.pool.VisitRecords(op);
    SCPT.pool.VisitRecords(op);
    LTEX.pool.VisitRecords(op);
    ENCH.pool.VisitRecords(op);
    SPEL.pool.VisitRecords(op);
    ACTI.pool.VisitRecords(op);
    TACT.pool.VisitRecords(op);
    TERM.pool.VisitRecords(op);
    ARMO.pool.VisitRecords(op);
    BOOK.pool.VisitRecords(op);
    CONT.pool.VisitRecords(op);
    DOOR.pool.VisitRecords(op);
    INGR.pool.VisitRecords(op);
    LIGH.pool.VisitRecords(op);
    MISC.pool.VisitRecords(op);
    STAT.pool.VisitRecords(op);
    SCOL.pool.VisitRecords(op);
    MSTT.pool.VisitRecords(op);
    PWAT.pool.VisitRecords(op);
    GRAS.pool.VisitRecords(op);
    TREE.pool.VisitRecords(op);
    FURN.pool.VisitRecords(op);
    WEAP.pool.VisitRecords(op);
    AMMO.pool.VisitRecords(op);
    NPC_.pool.VisitRecords(op);
    CREA.pool.VisitRecords(op);
    LVLC.pool.VisitRecords(op);
    LVLN.pool.VisitRecords(op);
    KEYM.pool.VisitRecords(op);
    ALCH.pool.VisitRecords(op);
    IDLM.pool.VisitRecords(op);
    NOTE.pool.VisitRecords(op);
    COBJ.pool.VisitRecords(op);
    PROJ.pool.VisitRecords(op);
    LVLI.pool.VisitRecords(op);
    WTHR.pool.VisitRecords(op);
    CLMT.pool.VisitRecords(op);
    REGN.pool.VisitRecords(op);
    NAVI.pool.VisitRecords(op);
    //Child records need to be visited prior to the parent in order for identical to master cleaning to work nicely
    CELL.achr_pool.VisitRecords(op);
    CELL.acre_pool.VisitRecords(op);
    CELL.refr_pool.VisitRecords(op);
    CELL.pgre_pool.VisitRecords(op);
    CELL.pmis_pool.VisitRecords(op);
    CELL.pbea_pool.VisitRecords(op);
    CELL.pfla_pool.VisitRecords(op);
    CELL.pcbe_pool.VisitRecords(op);
    CELL.navm_pool.VisitRecords(op);
    WRLD.land_pool.VisitRecords(op);
    DIAL.info_pool.VisitRecords(op);

    CELL.cell_pool.VisitRecords(op);
    WRLD.cell_pool.VisitRecords(op);
    WRLD.wrld_pool.VisitRecords(op);
    DIAL.dial_pool.VisitRecords(op);
    QUST.pool.VisitRecords(op);
    IDLE.pool.VisitRecords(op);
    PACK.pool.VisitRecords(op);
    CSTY.pool.VisitRecords(op);
    LSCR.pool.VisitRecords(op);
    ANIO.pool.VisitRecords(op);
    WATR.pool.VisitRecords(op);
    EFSH.pool.VisitRecords(op);
    EXPL.pool.VisitRecords(op);
    DEBR.pool.VisitRecords(op);
    //IMGS.pool.VisitRecords(op);
    //IMAD.pool.VisitRecords(op);
    //FLST.pool.VisitRecords(op);
    //PERK.pool.VisitRecords(op);
    //BPTD.pool.VisitRecords(op);
    //ADDN.pool.VisitRecords(op);
    //AVIF.pool.VisitRecords(op);
    //RADS.pool.VisitRecords(op);
    //CAMS.pool.VisitRecords(op);
    //CPTH.pool.VisitRecords(op);
    //VTYP.pool.VisitRecords(op);
    //IPCT.pool.VisitRecords(op);
    //IPDS.pool.VisitRecords(op);
    //ARMA.pool.VisitRecords(op);
    //ECZN.pool.VisitRecords(op);
    //MESG.pool.VisitRecords(op);
    //RGDL.pool.VisitRecords(op);
    //DOBJ.pool.VisitRecords(op);
    //LGTM.pool.VisitRecords(op);
    //MUSC.pool.VisitRecords(op);
    //IMOD.pool.VisitRecords(op);
    //REPU.pool.VisitRecords(op);
    //RCPE.pool.VisitRecords(op);
    //RCCT.pool.VisitRecords(op);
    //CHIP.pool.VisitRecords(op);
    //CSNO.pool.VisitRecords(op);
    //LSCT.pool.VisitRecords(op);
    //MSET.pool.VisitRecords(op);
    //ALOC.pool.VisitRecords(op);
    //CHAL.pool.VisitRecords(op);
    //AMEF.pool.VisitRecords(op);
    //CCRD.pool.VisitRecords(op);
    //CMNY.pool.VisitRecords(op);
    //CDCK.pool.VisitRecords(op);
    //DEHY.pool.VisitRecords(op);
    //HUNG.pool.VisitRecords(op);
    //SLPD.pool.VisitRecords(op);

    return;
    }

void FNVFile::VisitRecords(const UINT32 &RecordType, RecordOp &op)
    {
    if(Flags.IsNoLoad)
        {
        printer("FNVFile::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", ModName);
        return;
        }

    switch(RecordType)
        {
        case REV32(TES4):
            {
            Record *temp = &TES4;
            op.Accept(temp);
            }
            break;
        case REV32(GMST):
            GMST.pool.VisitRecords(op);
            break;
        case REV32(TXST):
            TXST.pool.VisitRecords(op);
            break;
        case REV32(MICN):
            MICN.pool.VisitRecords(op);
            break;
        case REV32(GLOB):
            GLOB.pool.VisitRecords(op);
            break;
        case REV32(CLAS):
            CLAS.pool.VisitRecords(op);
            break;
        case REV32(FACT):
            FACT.pool.VisitRecords(op);
            break;
        case REV32(HDPT):
            HDPT.pool.VisitRecords(op);
            break;
        case REV32(HAIR):
            HAIR.pool.VisitRecords(op);
            break;
        case REV32(EYES):
            EYES.pool.VisitRecords(op);
            break;
        case REV32(RACE):
            RACE.pool.VisitRecords(op);
            break;
        case REV32(SOUN):
            SOUN.pool.VisitRecords(op);
            break;
        case REV32(ASPC):
            ASPC.pool.VisitRecords(op);
            break;
        case REV32(MGEF):
            MGEF.pool.VisitRecords(op);
            break;
        case REV32(SCPT):
            SCPT.pool.VisitRecords(op);
            break;
        case REV32(LTEX):
            LTEX.pool.VisitRecords(op);
            break;
        case REV32(ENCH):
            ENCH.pool.VisitRecords(op);
            break;
        case REV32(SPEL):
            SPEL.pool.VisitRecords(op);
            break;
        case REV32(ACTI):
            ACTI.pool.VisitRecords(op);
            break;
        case REV32(TACT):
            TACT.pool.VisitRecords(op);
            break;
        case REV32(TERM):
            TERM.pool.VisitRecords(op);
            break;
        case REV32(ARMO):
            ARMO.pool.VisitRecords(op);
            break;
        case REV32(BOOK):
            BOOK.pool.VisitRecords(op);
            break;
        case REV32(CONT):
            CONT.pool.VisitRecords(op);
            break;
        case REV32(DOOR):
            DOOR.pool.VisitRecords(op);
            break;
        case REV32(INGR):
            INGR.pool.VisitRecords(op);
            break;
        case REV32(LIGH):
            LIGH.pool.VisitRecords(op);
            break;
        case REV32(MISC):
            MISC.pool.VisitRecords(op);
            break;
        case REV32(STAT):
            STAT.pool.VisitRecords(op);
            break;
        case REV32(SCOL):
            SCOL.pool.VisitRecords(op);
            break;
        case REV32(MSTT):
            MSTT.pool.VisitRecords(op);
            break;
        case REV32(PWAT):
            PWAT.pool.VisitRecords(op);
            break;
        case REV32(GRAS):
            GRAS.pool.VisitRecords(op);
            break;
        case REV32(TREE):
            TREE.pool.VisitRecords(op);
            break;
        case REV32(FURN):
            FURN.pool.VisitRecords(op);
            break;
        case REV32(WEAP):
            WEAP.pool.VisitRecords(op);
            break;
        case REV32(AMMO):
            AMMO.pool.VisitRecords(op);
            break;
        case REV32(NPC_):
            NPC_.pool.VisitRecords(op);
            break;
        case REV32(CREA):
            CREA.pool.VisitRecords(op);
            break;
        case REV32(LVLC):
            LVLC.pool.VisitRecords(op);
            break;
        case REV32(LVLN):
            LVLN.pool.VisitRecords(op);
            break;
        case REV32(KEYM):
            KEYM.pool.VisitRecords(op);
            break;
        case REV32(ALCH):
            ALCH.pool.VisitRecords(op);
            break;
        case REV32(IDLM):
            IDLM.pool.VisitRecords(op);
            break;
        case REV32(NOTE):
            NOTE.pool.VisitRecords(op);
            break;
        case REV32(COBJ):
            COBJ.pool.VisitRecords(op);
            break;
        case REV32(PROJ):
            PROJ.pool.VisitRecords(op);
            break;
        case REV32(LVLI):
            LVLI.pool.VisitRecords(op);
            break;
        case REV32(WTHR):
            WTHR.pool.VisitRecords(op);
            break;
        case REV32(CLMT):
            CLMT.pool.VisitRecords(op);
            break;
        case REV32(REGN):
            REGN.pool.VisitRecords(op);
            break;
        case REV32(NAVI):
            NAVI.pool.VisitRecords(op);
            break;
        case REV32(CELL):
            CELL.cell_pool.VisitRecords(op);
            break;
        case REV32(ACHR):
            CELL.achr_pool.VisitRecords(op);
            break;
        case REV32(ACRE):
            CELL.acre_pool.VisitRecords(op);
            break;
        case REV32(REFR):
            CELL.refr_pool.VisitRecords(op);
            break;
        case REV32(PGRE):
            CELL.pgre_pool.VisitRecords(op);
            break;
        case REV32(PMIS):
            CELL.pmis_pool.VisitRecords(op);
            break;
        case REV32(PBEA):
            CELL.pbea_pool.VisitRecords(op);
            break;
        case REV32(PFLA):
            CELL.pfla_pool.VisitRecords(op);
            break;
        case REV32(PCBE):
            CELL.pcbe_pool.VisitRecords(op);
            break;
        case REV32(NAVM):
            CELL.navm_pool.VisitRecords(op);
            break;
        case REV32(WRLD):
            WRLD.wrld_pool.VisitRecords(op);
            break;
        case REV32(LAND):
            WRLD.land_pool.VisitRecords(op);
            break;
        case REV32(WCEL):
            WRLD.cell_pool.VisitRecords(op);
            break;
        case REV32(CLLS):
            CELL.cell_pool.VisitRecords(op);
            WRLD.cell_pool.VisitRecords(op);
            break;
        case REV32(DIAL):
            DIAL.dial_pool.VisitRecords(op);
            break;
        case REV32(INFO):
            DIAL.info_pool.VisitRecords(op);
            break;
        case REV32(QUST):
            QUST.pool.VisitRecords(op);
            break;
        case REV32(IDLE):
            IDLE.pool.VisitRecords(op);
            break;
        case REV32(PACK):
            PACK.pool.VisitRecords(op);
            break;
        case REV32(CSTY):
            CSTY.pool.VisitRecords(op);
            break;
        case REV32(LSCR):
            LSCR.pool.VisitRecords(op);
            break;
        case REV32(ANIO):
            ANIO.pool.VisitRecords(op);
            break;
        case REV32(WATR):
            WATR.pool.VisitRecords(op);
            break;
        case REV32(EFSH):
            EFSH.pool.VisitRecords(op);
            break;
        case REV32(EXPL):
            EXPL.pool.VisitRecords(op);
            break;
        case REV32(DEBR):
            DEBR.pool.VisitRecords(op);
            break;
        case REV32(IMGS):
            //IMGS.pool.VisitRecords(op);
            //break;
        case REV32(IMAD):
            //IMAD.pool.VisitRecords(op);
            //break;
        case REV32(FLST):
            //FLST.pool.VisitRecords(op);
            //break;
        case REV32(PERK):
            //PERK.pool.VisitRecords(op);
            //break;
        case REV32(BPTD):
            //BPTD.pool.VisitRecords(op);
            //break;
        case REV32(ADDN):
            //ADDN.pool.VisitRecords(op);
            //break;
        case REV32(AVIF):
            //AVIF.pool.VisitRecords(op);
            //break;
        case REV32(RADS):
            //RADS.pool.VisitRecords(op);
            //break;
        case REV32(CAMS):
            //CAMS.pool.VisitRecords(op);
            //break;
        case REV32(CPTH):
            //CPTH.pool.VisitRecords(op);
            //break;
        case REV32(VTYP):
            //VTYP.pool.VisitRecords(op);
            //break;
        case REV32(IPCT):
            //IPCT.pool.VisitRecords(op);
            //break;
        case REV32(IPDS):
            //IPDS.pool.VisitRecords(op);
            //break;
        case REV32(ARMA):
            //ARMA.pool.VisitRecords(op);
            //break;
        case REV32(ECZN):
            //ECZN.pool.VisitRecords(op);
            //break;
        case REV32(MESG):
            //MESG.pool.VisitRecords(op);
            //break;
        case REV32(RGDL):
            //RGDL.pool.VisitRecords(op);
            //break;
        case REV32(DOBJ):
            //DOBJ.pool.VisitRecords(op);
            //break;
        case REV32(LGTM):
            //LGTM.pool.VisitRecords(op);
            //break;
        case REV32(MUSC):
            //MUSC.pool.VisitRecords(op);
            //break;
        case REV32(IMOD):
            //IMOD.pool.VisitRecords(op);
            //break;
        case REV32(REPU):
            //REPU.pool.VisitRecords(op);
            //break;
        case REV32(RCPE):
            //RCPE.pool.VisitRecords(op);
            //break;
        case REV32(RCCT):
            //RCCT.pool.VisitRecords(op);
            //break;
        case REV32(CHIP):
            //CHIP.pool.VisitRecords(op);
            //break;
        case REV32(CSNO):
            //CSNO.pool.VisitRecords(op);
            //break;
        case REV32(LSCT):
            //LSCT.pool.VisitRecords(op);
            //break;
        case REV32(MSET):
            //MSET.pool.VisitRecords(op);
            //break;
        case REV32(ALOC):
            //ALOC.pool.VisitRecords(op);
            //break;
        case REV32(CHAL):
            //CHAL.pool.VisitRecords(op);
            //break;
        case REV32(AMEF):
            //AMEF.pool.VisitRecords(op);
            //break;
        case REV32(CCRD):
            //CCRD.pool.VisitRecords(op);
            //break;
        case REV32(CMNY):
            //CMNY.pool.VisitRecords(op);
            //break;
        case REV32(CDCK):
            //CDCK.pool.VisitRecords(op);
            //break;
        case REV32(DEHY):
            //DEHY.pool.VisitRecords(op);
            //break;
        case REV32(HUNG):
            //HUNG.pool.VisitRecords(op);
            //break;
        case REV32(SLPD):
            //SLPD.pool.VisitRecords(op);
            //break;
        default:
            printer("FNVFile::VisitRecords: Error - Unable to visit record type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ModName);
            break;
        }
    return;
    }