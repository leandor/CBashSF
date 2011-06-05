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
// TES4File.cpp
#include "../Common.h"
#include "../GenericRecord.h"
#include "TES4File.h"

TES4File::TES4File(STRING FileName, STRING ModName, const UINT32 _flags):
    ModFile(FileName, ModName, _flags)
    {
    //
    }

TES4File::~TES4File()
    {
    //
    }

SINT32 TES4File::LoadTES4()
    {
    if(TES4.IsLoaded() || !Open())
        {
        if(!TES4.IsLoaded() && !Open())
            printer("TES4File::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", reader.getModName());
        return 0;
        }

    reader.skip(4);
    UINT32 recSize = 0;
    reader.read(&recSize, 4);
    reader.read(&TES4.flags, 4);
    reader.read(&TES4.formID, 4);
    reader.read(&TES4.flagsUnk, 4);
    if(TES4.IsLoaded())
        printer("_fIsLoaded Flag used!!!!: %08X\n", TES4.flags);

    //Normally would read the record with the read method
    //However, that requires recData to be set on the record
    // and that can only be set by the constructor
    //TES4 is constructed when the modfile is created
    // so the info isn't available then.
    //Must make sure this mimics the read method as needed
    TES4.ParseRecord(reader.tell(), recSize);
    TES4.IsLoaded(true);
    TES4.IsChanged(true);
    reader.skip(recSize);
    return 1;
    }

SINT32 TES4File::Load(RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords)
    {
    enum IgTopRecords {
        eIgGMST = REV32(GMST) | 0x00001000, //Record::fIsIgnored
        eIgGLOB = REV32(GLOB) | 0x00001000,
        eIgCLAS = REV32(CLAS) | 0x00001000,
        eIgFACT = REV32(FACT) | 0x00001000,
        eIgHAIR = REV32(HAIR) | 0x00001000,
        eIgEYES = REV32(EYES) | 0x00001000,
        eIgRACE = REV32(RACE) | 0x00001000,
        eIgSOUN = REV32(SOUN) | 0x00001000,
        eIgSKIL = REV32(SKIL) | 0x00001000,
        eIgMGEF = REV32(MGEF) | 0x00001000,
        eIgSCPT = REV32(SCPT) | 0x00001000,
        eIgLTEX = REV32(LTEX) | 0x00001000,
        eIgENCH = REV32(ENCH) | 0x00001000,
        eIgSPEL = REV32(SPEL) | 0x00001000,
        eIgBSGN = REV32(BSGN) | 0x00001000,
        eIgACTI = REV32(ACTI) | 0x00001000,
        eIgAPPA = REV32(APPA) | 0x00001000,
        eIgARMO = REV32(ARMO) | 0x00001000,
        eIgBOOK = REV32(BOOK) | 0x00001000,
        eIgCLOT = REV32(CLOT) | 0x00001000,
        eIgCONT = REV32(CONT) | 0x00001000,
        eIgDOOR = REV32(DOOR) | 0x00001000,
        eIgINGR = REV32(INGR) | 0x00001000,
        eIgLIGH = REV32(LIGH) | 0x00001000,
        eIgMISC = REV32(MISC) | 0x00001000,
        eIgSTAT = REV32(STAT) | 0x00001000,
        eIgGRAS = REV32(GRAS) | 0x00001000,
        eIgTREE = REV32(TREE) | 0x00001000,
        eIgFLOR = REV32(FLOR) | 0x00001000,
        eIgFURN = REV32(FURN) | 0x00001000,
        eIgWEAP = REV32(WEAP) | 0x00001000,
        eIgAMMO = REV32(AMMO) | 0x00001000,
        eIgNPC_ = REV32(NPC_) | 0x00001000,
        eIgCREA = REV32(CREA) | 0x00001000,
        eIgLVLC = REV32(LVLC) | 0x00001000,
        eIgSLGM = REV32(SLGM) | 0x00001000,
        eIgKEYM = REV32(KEYM) | 0x00001000,
        eIgALCH = REV32(ALCH) | 0x00001000,
        eIgSBSP = REV32(SBSP) | 0x00001000,
        eIgSGST = REV32(SGST) | 0x00001000,
        eIgLVLI = REV32(LVLI) | 0x00001000,
        eIgWTHR = REV32(WTHR) | 0x00001000,
        eIgCLMT = REV32(CLMT) | 0x00001000,
        eIgREGN = REV32(REGN) | 0x00001000,
        eIgCELL = REV32(CELL) | 0x00001000,
        eIgWRLD = REV32(WRLD) | 0x00001000,
        eIgDIAL = REV32(DIAL) | 0x00001000,
        eIgQUST = REV32(QUST) | 0x00001000,
        eIgIDLE = REV32(IDLE) | 0x00001000,
        eIgPACK = REV32(PACK) | 0x00001000,
        eIgCSTY = REV32(CSTY) | 0x00001000,
        eIgLSCR = REV32(LSCR) | 0x00001000,
        eIgLVSP = REV32(LVSP) | 0x00001000,
        eIgANIO = REV32(ANIO) | 0x00001000,
        eIgWATR = REV32(WATR) | 0x00001000,
        eIgEFSH = REV32(EFSH) | 0x00001000
        };
    if(Flags.IsIgnoreExisting || !reader.IsOpen() || Flags.LoadedGRUPs)
        {
        if(!Flags.IsIgnoreExisting)
            {
            if(!reader.IsOpen())
                printer("TES4File::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", reader.getModName());
            else
                printer("TES4File::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", reader.getModName());
            }
        return 0;
        }
    //printer("%08X\n", Flags.GetFlags());
    //printer("Loading %s\n", FileName);
    //for(UINT32 x = 0; x < FormIDHandler.LoadOrder255.size(); ++x)
    //    printer("Master in load order %02X: %s\n", x, FormIDHandler.LoadOrder255[x]);
    Flags.LoadedGRUPs = true;
    UINT32 GRUPSize;
    UINT32 GRUPLabel;
    boost::unordered_set<UINT32> UsedFormIDs;

    RecordReader fullReader(FormIDHandler, Expanders);
    RecordOp skipReader;

    RecordProcessor processor_min(reader, FormIDHandler, skipReader, Flags, UsedFormIDs, DeletedRecords);
    RecordProcessor processor_full(reader, FormIDHandler, fullReader, Flags, UsedFormIDs, DeletedRecords);

    RecordProcessor &processor = Flags.IsFullLoad ? processor_full : processor_min;

    //RecordProcessFunc RecordProcessor = (Flags.IsSkipNewRecords || Flags.IsTrackNewTypes) ? (Flags.IsSkipNewRecords ? &ProcessRecord_SkipNew : &ProcessRecord_TrackNew) : &ProcessRecord_Base;

    if(TES4.HEDR.value.numRecords == 1252095 && icmps(reader.getModName(), "Oblivion.esm") == 0)
        {
        //Override the default pool allocations with those tailored for Oblivion.esm
        //ACHR.pool.purge_no_destructors();
        //ACHR.pool.reserve(2190);
        //ACRE.pool.purge_no_destructors();
        //ACRE.pool.reserve(1473);
        ACTI.pool.purge_no_destructors();
        ACTI.pool.reserve(1252);
        ALCH.pool.purge_no_destructors();
        ALCH.pool.reserve(253);
        AMMO.pool.purge_no_destructors();
        AMMO.pool.reserve(128);
        ANIO.pool.purge_no_destructors();
        ANIO.pool.reserve(34);
        APPA.pool.purge_no_destructors();
        APPA.pool.reserve(23);
        ARMO.pool.purge_no_destructors();
        ARMO.pool.reserve(996);
        BOOK.pool.purge_no_destructors();
        BOOK.pool.reserve(887);
        BSGN.pool.purge_no_destructors();
        BSGN.pool.reserve(13);
        CELL.pool.purge_no_destructors();
        CELL.pool.reserve(1855);
        CELL.pgrd_pool.purge_no_destructors();
        CELL.pgrd_pool.reserve(8228);
        CLAS.pool.purge_no_destructors();
        CLAS.pool.reserve(111);
        CLMT.pool.purge_no_destructors();
        CLMT.pool.reserve(19);
        CLOT.pool.purge_no_destructors();
        CLOT.pool.reserve(604);
        CONT.pool.purge_no_destructors();
        CONT.pool.reserve(873);
        CREA.pool.purge_no_destructors();
        CREA.pool.reserve(914);
        CSTY.pool.purge_no_destructors();
        CSTY.pool.reserve(126);
        DIAL.pool.purge_no_destructors();
        DIAL.pool.reserve(3817);
        DOOR.pool.purge_no_destructors();
        DOOR.pool.reserve(501);
        EFSH.pool.purge_no_destructors();
        EFSH.pool.reserve(102);
        ENCH.pool.purge_no_destructors();
        ENCH.pool.reserve(1542);
        EYES.pool.purge_no_destructors();
        EYES.pool.reserve(13);
        FACT.pool.purge_no_destructors();
        FACT.pool.reserve(476);
        FLOR.pool.purge_no_destructors();
        FLOR.pool.reserve(155);
        FURN.pool.purge_no_destructors();
        FURN.pool.reserve(186);
        GLOB.pool.purge_no_destructors();
        GLOB.pool.reserve(94);
        GMST.pool.purge_no_destructors();
        GMST.pool.reserve(382);
        GRAS.pool.purge_no_destructors();
        GRAS.pool.reserve(108);
        HAIR.pool.purge_no_destructors();
        HAIR.pool.reserve(57);
        IDLE.pool.purge_no_destructors();
        IDLE.pool.reserve(650);
        //INFO.pool.purge_no_destructors();
        //INFO.pool.reserve(19278);
        INGR.pool.purge_no_destructors();
        INGR.pool.reserve(173);
        KEYM.pool.purge_no_destructors();
        KEYM.pool.reserve(464);
        LIGH.pool.purge_no_destructors();
        LIGH.pool.reserve(1625);
        LSCR.pool.purge_no_destructors();
        LSCR.pool.reserve(337);
        LTEX.pool.purge_no_destructors();
        LTEX.pool.reserve(229);
        LVLC.pool.purge_no_destructors();
        LVLC.pool.reserve(682);
        LVLI.pool.purge_no_destructors();
        LVLI.pool.reserve(1398);
        LVSP.pool.purge_no_destructors();
        LVSP.pool.reserve(306);
        MGEF.pool.purge_no_destructors();
        MGEF.pool.reserve(145);
        MISC.pool.purge_no_destructors();
        MISC.pool.reserve(407);
        NPC_.pool.purge_no_destructors();
        NPC_.pool.reserve(2482);
        PACK.pool.purge_no_destructors();
        PACK.pool.reserve(7209);
        QUST.pool.purge_no_destructors();
        QUST.pool.reserve(390);
        RACE.pool.purge_no_destructors();
        RACE.pool.reserve(15);
        //REFR.pool.purge_no_destructors();
        //REFR.pool.reserve(1025617);
        REGN.pool.purge_no_destructors();
        REGN.pool.reserve(211);
        SBSP.pool.purge_no_destructors();
        SBSP.pool.reserve(33);
        SCPT.pool.purge_no_destructors();
        SCPT.pool.reserve(2393);
        SGST.pool.purge_no_destructors();
        SGST.pool.reserve(150);
        SKIL.pool.purge_no_destructors();
        SKIL.pool.reserve(21);
        SLGM.pool.purge_no_destructors();
        SLGM.pool.reserve(29);
        SOUN.pool.purge_no_destructors();
        SOUN.pool.reserve(1140);
        SPEL.pool.purge_no_destructors();
        SPEL.pool.reserve(1137);
        STAT.pool.purge_no_destructors();
        STAT.pool.reserve(6014);
        TREE.pool.purge_no_destructors();
        TREE.pool.reserve(142);
        WATR.pool.purge_no_destructors();
        WATR.pool.reserve(23);
        WEAP.pool.purge_no_destructors();
        WEAP.pool.reserve(1319);
        WRLD.pool.purge_no_destructors();
        WRLD.pool.reserve(84);
        WRLD.land_pool.purge_no_destructors();
        WRLD.land_pool.reserve(31823);
        WRLD.cell_pool.purge_no_destructors();
        WRLD.cell_pool.reserve(69);
        WRLD.road_pool.purge_no_destructors();
        WRLD.road_pool.reserve(2);
        WTHR.pool.purge_no_destructors();
        WTHR.pool.reserve(37);
        }

    while(!reader.eof()){
        reader.skip(4); //Skip "GRUP"
        reader.read(&GRUPSize, 4);
        reader.read(&GRUPLabel, 4);
        reader.skip(4); //Skip type (tops will all == 0)
        //printer("%c%c%c%c\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
        switch(GRUPLabel)
            {
            //ADD DEFINITIONS HERE
            case eIgGMST:
            case REV32(GMST):
                reader.read(&GMST.stamp, 4);
                GMST.Skim(reader, GRUPSize, processor_full, indexer);
                break;
            case eIgGLOB:
            case REV32(GLOB):
                reader.read(&GLOB.stamp, 4);
                GLOB.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCLAS:
            case REV32(CLAS):
                reader.read(&CLAS.stamp, 4);
                CLAS.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgFACT:
            case REV32(FACT):
                reader.read(&FACT.stamp, 4);
                FACT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgHAIR:
            case REV32(HAIR):
                reader.read(&HAIR.stamp, 4);
                HAIR.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgEYES: //Same as normal
            case REV32(EYES):
                reader.read(&EYES.stamp, 4);
                EYES.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgRACE:
            case REV32(RACE):
                reader.read(&RACE.stamp, 4);
                RACE.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgSOUN:
            case REV32(SOUN):
                reader.read(&SOUN.stamp, 4);
                SOUN.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgSKIL:
            case REV32(SKIL):
                reader.read(&SKIL.stamp, 4);
                SKIL.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgMGEF:
            case REV32(MGEF):
                reader.read(&MGEF.stamp, 4);
                MGEF.Skim(reader, GRUPSize, processor_full, indexer);
                break;
            case eIgSCPT:
            case REV32(SCPT):
                reader.read(&SCPT.stamp, 4);
                SCPT.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLTEX: //Same as normal
            case REV32(LTEX):
                reader.read(&LTEX.stamp, 4);
                LTEX.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgENCH:
            case REV32(ENCH):
                reader.read(&ENCH.stamp, 4);
                ENCH.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgSPEL: //Same as normal
            case REV32(SPEL):
                reader.read(&SPEL.stamp, 4);
                SPEL.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgBSGN: //Same as normal
            case REV32(BSGN):
                reader.read(&BSGN.stamp, 4);
                BSGN.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgACTI:
            case REV32(ACTI):
                reader.read(&ACTI.stamp, 4);
                ACTI.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgAPPA: //Same as normal
            case REV32(APPA):
                reader.read(&APPA.stamp, 4);
                APPA.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgARMO: //Same as normal
            case REV32(ARMO):
                reader.read(&ARMO.stamp, 4);
                ARMO.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgBOOK:
            case REV32(BOOK):
                reader.read(&BOOK.stamp, 4);
                BOOK.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCLOT:
            case REV32(CLOT):
                reader.read(&CLOT.stamp, 4);
                CLOT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCONT:
            case REV32(CONT):
                reader.read(&CONT.stamp, 4);
                CONT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgDOOR:
            case REV32(DOOR):
                reader.read(&DOOR.stamp, 4);
                DOOR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgINGR:
            case REV32(INGR):
                reader.read(&INGR.stamp, 4);
                INGR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgLIGH:
            case REV32(LIGH):
                reader.read(&LIGH.stamp, 4);
                LIGH.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgMISC:
            case REV32(MISC):
                reader.read(&MISC.stamp, 4);
                MISC.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgSTAT: //Same as normal
            case REV32(STAT):
                reader.read(&STAT.stamp, 4);
                STAT.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgGRAS: //Same as normal
            case REV32(GRAS):
                reader.read(&GRAS.stamp, 4);
                GRAS.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgTREE: //Same as normal
            case REV32(TREE):
                reader.read(&TREE.stamp, 4);
                TREE.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgFLOR:
            case REV32(FLOR):
                reader.read(&FLOR.stamp, 4);
                FLOR.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgFURN: //Same as normal
            case REV32(FURN):
                reader.read(&FURN.stamp, 4);
                FURN.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgWEAP:
            case REV32(WEAP):
                reader.read(&WEAP.stamp, 4);
                WEAP.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgAMMO:
            case REV32(AMMO):
                reader.read(&AMMO.stamp, 4);
                AMMO.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgNPC_: //Same as normal
            case REV32(NPC_):
                reader.read(&NPC_.stamp, 4);
                NPC_.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgCREA: //Same as normal
            case REV32(CREA):
                reader.read(&CREA.stamp, 4);
                CREA.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLVLC: //Same as normal
            case REV32(LVLC):
                reader.read(&LVLC.stamp, 4);
                LVLC.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgSLGM:
            case REV32(SLGM):
                reader.read(&SLGM.stamp, 4);
                SLGM.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgKEYM:
            case REV32(KEYM):
                reader.read(&KEYM.stamp, 4);
                KEYM.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgALCH:
            case REV32(ALCH):
                reader.read(&ALCH.stamp, 4);
                ALCH.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgSBSP:
            case REV32(SBSP):
                reader.read(&SBSP.stamp, 4);
                SBSP.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgSGST:
            case REV32(SGST):
                reader.read(&SGST.stamp, 4);
                SGST.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLVLI: //Same as normal
            case REV32(LVLI):
                reader.read(&LVLI.stamp, 4);
                LVLI.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgWTHR: //Same as normal
            case REV32(WTHR):
                reader.read(&WTHR.stamp, 4);
                WTHR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCLMT:
            case REV32(CLMT):
                reader.read(&CLMT.stamp, 4);
                CLMT.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgREGN:
            case REV32(REGN):
                reader.read(&REGN.stamp, 4);
                REGN.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgCELL:
            case REV32(CELL):
                reader.read(&CELL.stamp, 4);
                CELL.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgWRLD: //Same as normal
            case REV32(WRLD):
                reader.read(&WRLD.stamp, 4);
                WRLD.Skim(reader, GRUPSize, processor, indexer, fullReader, CELL.pgrd_pool);
                break;
            case eIgDIAL:
            case REV32(DIAL):
                reader.read(&DIAL.stamp, 4);
                DIAL.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgQUST: //Same as normal
            case REV32(QUST):
                reader.read(&QUST.stamp, 4);
                QUST.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgIDLE:
            case REV32(IDLE):
                reader.read(&IDLE.stamp, 4);
                IDLE.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgPACK:
            case REV32(PACK):
                reader.read(&PACK.stamp, 4);
                PACK.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgCSTY: //Same as normal
            case REV32(CSTY):
                reader.read(&CSTY.stamp, 4);
                CSTY.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLSCR: //Same as normal
            case REV32(LSCR):
                reader.read(&LSCR.stamp, 4);
                LSCR.Skim(reader, GRUPSize, processor, indexer);
                break;
            //case eIgLVSP: //Same as normal
            case REV32(LVSP):
                reader.read(&LVSP.stamp, 4);
                LVSP.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgANIO:
            case REV32(ANIO):
                reader.read(&ANIO.stamp, 4);
                ANIO.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgWATR:
            case REV32(WATR):
                reader.read(&WATR.stamp, 4);
                WATR.Skim(reader, GRUPSize, processor, indexer);
                break;
            case eIgEFSH:
            case REV32(EFSH):
                reader.read(&EFSH.stamp, 4);
                EFSH.Skim(reader, GRUPSize, processor, indexer);
                break;
            default:
                if(GRUPLabel == 0 && GRUPSize == 0)
                    {
                    printer("TES4File::Skim: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], reader.getModName());
                    return 1;
                    }
                else
                    printer("TES4File::Skim: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], reader.getModName());

                if(GRUPSize == 0)
                    {
                    printer("Unable to continue loading.\n");
                    return 1;
                    }
                else
                    {
                    printer("Attempting to skip and continue loading.\n");
                    reader.skip(GRUPSize - 16); //Skip type (tops will all == 0)
                    }
                break;
            }
        };

    //ACHR.pool.consolidate();
    //ACRE.pool.consolidate();
    //REFR.pool.consolidate();
    //INFO.pool.consolidate();
    ACTI.pool.consolidate();
    ALCH.pool.consolidate();
    AMMO.pool.consolidate();
    ANIO.pool.consolidate();
    APPA.pool.consolidate();
    ARMO.pool.consolidate();
    BOOK.pool.consolidate();
    BSGN.pool.consolidate();
    CELL.pool.consolidate();
    CELL.pgrd_pool.consolidate();
    CLAS.pool.consolidate();
    CLMT.pool.consolidate();
    CLOT.pool.consolidate();
    CONT.pool.consolidate();
    CREA.pool.consolidate();
    CSTY.pool.consolidate();
    DIAL.pool.consolidate();
    DOOR.pool.consolidate();
    EFSH.pool.consolidate();
    ENCH.pool.consolidate();
    EYES.pool.consolidate();
    FACT.pool.consolidate();
    FLOR.pool.consolidate();
    FURN.pool.consolidate();
    GLOB.pool.consolidate();
    GMST.pool.consolidate();
    GRAS.pool.consolidate();
    HAIR.pool.consolidate();
    IDLE.pool.consolidate();
    INGR.pool.consolidate();
    KEYM.pool.consolidate();
    LIGH.pool.consolidate();
    LSCR.pool.consolidate();
    LTEX.pool.consolidate();
    LVLC.pool.consolidate();
    LVLI.pool.consolidate();
    LVSP.pool.consolidate();
    MGEF.pool.consolidate();
    MISC.pool.consolidate();
    NPC_.pool.consolidate();
    PACK.pool.consolidate();
    QUST.pool.consolidate();
    RACE.pool.consolidate();
    REGN.pool.consolidate();
    SBSP.pool.consolidate();
    SCPT.pool.consolidate();
    SGST.pool.consolidate();
    SKIL.pool.consolidate();
    SLGM.pool.consolidate();
    SOUN.pool.consolidate();
    SPEL.pool.consolidate();
    STAT.pool.consolidate();
    TREE.pool.consolidate();
    WATR.pool.consolidate();
    WEAP.pool.consolidate();
    WRLD.pool.consolidate();
    WRLD.land_pool.consolidate();
    WRLD.road_pool.consolidate();
    WRLD.cell_pool.consolidate();
    WTHR.pool.consolidate();

    return 1;
    }

UINT32 TES4File::GetNumRecords(const UINT32 &RecordType)
    {
    switch(RecordType)
        {
        case REV32(GMST):
            return (UINT32)GMST.pool.used_object_capacity();
        case REV32(GLOB):
            return (UINT32)GLOB.pool.used_object_capacity();
        case REV32(CLAS):
            return (UINT32)CLAS.pool.used_object_capacity();
        case REV32(FACT):
            return (UINT32)FACT.pool.used_object_capacity();
        case REV32(HAIR):
            return (UINT32)HAIR.pool.used_object_capacity();
        case REV32(EYES):
            return (UINT32)EYES.pool.used_object_capacity();
        case REV32(RACE):
            return (UINT32)RACE.pool.used_object_capacity();
        case REV32(SOUN):
            return (UINT32)SOUN.pool.used_object_capacity();
        case REV32(SKIL):
            return (UINT32)SKIL.pool.used_object_capacity();
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
        case REV32(BSGN):
            return (UINT32)BSGN.pool.used_object_capacity();
        case REV32(ACTI):
            return (UINT32)ACTI.pool.used_object_capacity();
        case REV32(APPA):
            return (UINT32)APPA.pool.used_object_capacity();
        case REV32(ARMO):
            return (UINT32)ARMO.pool.used_object_capacity();
        case REV32(BOOK):
            return (UINT32)BOOK.pool.used_object_capacity();
        case REV32(CLOT):
            return (UINT32)CLOT.pool.used_object_capacity();
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
        case REV32(GRAS):
            return (UINT32)GRAS.pool.used_object_capacity();
        case REV32(TREE):
            return (UINT32)TREE.pool.used_object_capacity();
        case REV32(FLOR):
            return (UINT32)FLOR.pool.used_object_capacity();
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
        case REV32(SLGM):
            return (UINT32)SLGM.pool.used_object_capacity();
        case REV32(KEYM):
            return (UINT32)KEYM.pool.used_object_capacity();
        case REV32(ALCH):
            return (UINT32)ALCH.pool.used_object_capacity();
        case REV32(SBSP):
            return (UINT32)SBSP.pool.used_object_capacity();
        case REV32(SGST):
            return (UINT32)SGST.pool.used_object_capacity();
        case REV32(LVLI):
            return (UINT32)LVLI.pool.used_object_capacity();
        case REV32(WTHR):
            return (UINT32)WTHR.pool.used_object_capacity();
        case REV32(CLMT):
            return (UINT32)CLMT.pool.used_object_capacity();
        case REV32(REGN):
            return (UINT32)REGN.pool.used_object_capacity();
        case REV32(CELL):
            return (UINT32)CELL.pool.used_object_capacity();
        case REV32(WRLD):
            return (UINT32)WRLD.pool.used_object_capacity();
        case REV32(DIAL):
            return (UINT32)DIAL.pool.used_object_capacity();
        ///////////////////////////////////////////////
        //SubRecords are counted via GetFieldAttribute API function
        //Fallthroughs are intentional
        case REV32(PGRD):
        case REV32(LAND):
        case REV32(ACHR):
        case REV32(ACRE):
        case REV32(REFR):
        case REV32(ROAD):
        case REV32(INFO):
            printer("TES4File::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". SubRecords are counted via GetFieldAttribute API function.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        ///////////////////////////////////////////////
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
        case REV32(LVSP):
            return (UINT32)LVSP.pool.used_object_capacity();
        case REV32(ANIO):
            return (UINT32)ANIO.pool.used_object_capacity();
        case REV32(WATR):
            return (UINT32)WATR.pool.used_object_capacity();
        case REV32(EFSH):
            return (UINT32)EFSH.pool.used_object_capacity();
        default:
            printer("TES4File::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        }
    return 0;
    }

Record * TES4File::CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES4File::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
        return NULL;
        }

    Record *newRecord = NULL;

    switch(RecordType)
        {
        case REV32(GMST):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printer("TES4File::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", reader.getModName());
                return NULL;
                }
            newRecord = GMST.pool.construct(SourceRecord);

            if(RecordEditorID != NULL)
                {
                ((GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
                ((GMSTRecord *)newRecord)->DATA.format = ((GMSTRecord *)newRecord)->EDID.value[0];
                }
            return newRecord;
        case REV32(GLOB):
            return GLOB.pool.construct(SourceRecord);
        case REV32(CLAS):
            return CLAS.pool.construct(SourceRecord);
        case REV32(FACT):
            return FACT.pool.construct(SourceRecord);
        case REV32(HAIR):
            return HAIR.pool.construct(SourceRecord);
        case REV32(EYES):
            return EYES.pool.construct(SourceRecord);
        case REV32(RACE):
            return RACE.pool.construct(SourceRecord);
        case REV32(SOUN):
            return SOUN.pool.construct(SourceRecord);
        case REV32(SKIL):
            return SKIL.pool.construct(SourceRecord);
        case REV32(MGEF):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printer("TES4File::CreateRecord: Error - Unable to create MGEF record in mod \"%s\". No valid editorID is available.\n", reader.getModName());
                return NULL;
                }

            newRecord = MGEF.pool.construct(SourceRecord);

            if(RecordEditorID != NULL)
                ((MGEFRecord *)newRecord)->EDID.Copy(RecordEditorID);
            return newRecord;
        case REV32(SCPT):
            return SCPT.pool.construct(SourceRecord);
        case REV32(LTEX):
            return LTEX.pool.construct(SourceRecord);
        case REV32(ENCH):
            return ENCH.pool.construct(SourceRecord);
        case REV32(SPEL):
            return SPEL.pool.construct(SourceRecord);
        case REV32(BSGN):
            return BSGN.pool.construct(SourceRecord);
        case REV32(ACTI):
            return ACTI.pool.construct(SourceRecord);
        case REV32(APPA):
            return APPA.pool.construct(SourceRecord);
        case REV32(ARMO):
            return ARMO.pool.construct(SourceRecord);
        case REV32(BOOK):
            return BOOK.pool.construct(SourceRecord);
        case REV32(CLOT):
            return CLOT.pool.construct(SourceRecord);
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
        case REV32(GRAS):
            return GRAS.pool.construct(SourceRecord);
        case REV32(TREE):
            return TREE.pool.construct(SourceRecord);
        case REV32(FLOR):
            return FLOR.pool.construct(SourceRecord);
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
        case REV32(SLGM):
            return SLGM.pool.construct(SourceRecord);
        case REV32(KEYM):
            return KEYM.pool.construct(SourceRecord);
        case REV32(ALCH):
            return ALCH.pool.construct(SourceRecord);
        case REV32(SBSP):
            return SBSP.pool.construct(SourceRecord);
        case REV32(SGST):
            return SGST.pool.construct(SourceRecord);
        case REV32(LVLI):
            return LVLI.pool.construct(SourceRecord);
        case REV32(WTHR):
            return WTHR.pool.construct(SourceRecord);
        case REV32(CLMT):
            return CLMT.pool.construct(SourceRecord);
        case REV32(REGN):
            return REGN.pool.construct(SourceRecord);
        case REV32(CELL):
            if(ParentRecord == NULL)
                {
                newRecord = CELL.pool.construct(SourceRecord);
                ((CELLRecord *)newRecord)->IsInterior(true);
                return newRecord;
                }
            else
                {
                if(ParentRecord->GetType() != REV32(WRLD))
                    {
                    printer("TES4File::CreateRecord: Error - Unable to create CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be CELL parents.\n", reader.getModName(), ParentRecord->GetStrType());
                    return NULL;
                    }

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
                        {
                        options.ExistingReturned = true;
                        return ((WRLDRecord *)ParentRecord)->CELL;
                        }

                    newRecord = ((WRLDRecord *)ParentRecord)->CELL = WRLD.cell_pool.construct(SourceRecord);
                    }
                else
                    {
                    newRecord = ((WRLDRecord *)ParentRecord)->cell_pool.construct(SourceRecord);
                    }

                ((CELLRecord *)newRecord)->IsInterior(false);
                ((CELLRecord *)newRecord)->Parent = ParentRecord;
                return newRecord;
                }
        case REV32(WRLD):
            return WRLD.pool.construct(SourceRecord);
        case REV32(DIAL):
            return DIAL.pool.construct(SourceRecord);
        case REV32(PGRD):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create PGRD record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be PGRD parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            //If a cell pathgrid already exists, return it instead of making a new one
            if(((CELLRecord *)ParentRecord)->PGRD != NULL)
                {
                options.ExistingReturned = true;
                return ((CELLRecord *)ParentRecord)->PGRD;
                }
            return ((CELLRecord *)ParentRecord)->PGRD = CELL.pgrd_pool.construct(SourceRecord);
        case REV32(LAND):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create LAND record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be LAND parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            //If a cell land already exists, return it instead of making a new one
            if(((CELLRecord *)ParentRecord)->LAND != NULL)
                {
                options.ExistingReturned = true;
                return ((CELLRecord *)ParentRecord)->LAND;
                }

            return ((CELLRecord *)ParentRecord)->LAND = WRLD.land_pool.construct(SourceRecord);
        case REV32(ACHR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create ACHR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACHR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            return ((CELLRecord *)ParentRecord)->achr_pool.construct(SourceRecord);
        case REV32(ACRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create ACRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACRE parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            return ((CELLRecord *)ParentRecord)->acre_pool.construct(SourceRecord);
        case REV32(REFR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create REFR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            return ((CELLRecord *)ParentRecord)->refr_pool.construct(SourceRecord);
        case REV32(ROAD):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(WRLD))
                {
                printer("TES4File::CreateRecord: Error - Unable to create ROAD record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be ROAD parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            //If a world road already exists, return it instead of making a new one
            if(((WRLDRecord *)ParentRecord)->ROAD != NULL)
                return ((WRLDRecord *)ParentRecord)->ROAD;

            return ((WRLDRecord *)ParentRecord)->ROAD = WRLD.road_pool.construct(SourceRecord);
        case REV32(INFO):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(DIAL))
                {
                printer("TES4File::CreateRecord: Error - Unable to create INFO record in mod \"%s\". Parent record type (%s) is invalid, only DIAL records can be INFO parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            return ((DIALRecord *)ParentRecord)->info_pool.construct(SourceRecord);
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
        case REV32(LVSP):
            return LVSP.pool.construct(SourceRecord);
        case REV32(ANIO):
            return ANIO.pool.construct(SourceRecord);
        case REV32(WATR):
            return WATR.pool.construct(SourceRecord);
        case REV32(EFSH):
            return EFSH.pool.construct(SourceRecord);
        default:
            printer("TES4File::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        }
    return NULL;
    }

SINT32 TES4File::DeleteRecord(Record *&curRecord, Record *&ParentRecord)
    {
    UINT32 LowType, TopType, MidType;
    TopType = MidType = LowType = curRecord->GetType();

    if(ParentRecord != NULL)
        {
        TopType = ParentRecord->GetParentType();
        if(TopType)
            MidType = ParentRecord->GetType();
        else
            TopType = ParentRecord->GetType();
        }

    switch(TopType)
        {
        case REV32(GMST):
            GMST.pool.destroy(curRecord);
            return 1;
        case REV32(GLOB):
            GLOB.pool.destroy(curRecord);
            return 1;
        case REV32(CLAS):
            CLAS.pool.destroy(curRecord);
            return 1;
        case REV32(FACT):
            FACT.pool.destroy(curRecord);
            return 1;
        case REV32(HAIR):
            HAIR.pool.destroy(curRecord);
            return 1;
        case REV32(EYES):
            EYES.pool.destroy(curRecord);
            return 1;
        case REV32(RACE):
            RACE.pool.destroy(curRecord);
            return 1;
        case REV32(SOUN):
            SOUN.pool.destroy(curRecord);
            return 1;
        case REV32(SKIL):
            SKIL.pool.destroy(curRecord);
            return 1;
        case REV32(MGEF):
            MGEF.pool.destroy(curRecord);
            return 1;
        case REV32(SCPT):
            SCPT.pool.destroy(curRecord);
            return 1;
        case REV32(LTEX):
            LTEX.pool.destroy(curRecord);
            return 1;
        case REV32(ENCH):
            ENCH.pool.destroy(curRecord);
            return 1;
        case REV32(SPEL):
            SPEL.pool.destroy(curRecord);
            return 1;
        case REV32(BSGN):
            BSGN.pool.destroy(curRecord);
            return 1;
        case REV32(ACTI):
            ACTI.pool.destroy(curRecord);
            return 1;
        case REV32(APPA):
            APPA.pool.destroy(curRecord);
            return 1;
        case REV32(ARMO):
            ARMO.pool.destroy(curRecord);
            return 1;
        case REV32(BOOK):
            BOOK.pool.destroy(curRecord);
            return 1;
        case REV32(CLOT):
            CLOT.pool.destroy(curRecord);
            return 1;
        case REV32(CONT):
            CONT.pool.destroy(curRecord);
            return 1;
        case REV32(DOOR):
            DOOR.pool.destroy(curRecord);
            return 1;
        case REV32(INGR):
            INGR.pool.destroy(curRecord);
            return 1;
        case REV32(LIGH):
            LIGH.pool.destroy(curRecord);
            return 1;
        case REV32(MISC):
            MISC.pool.destroy(curRecord);
            return 1;
        case REV32(STAT):
            STAT.pool.destroy(curRecord);
            return 1;
        case REV32(GRAS):
            GRAS.pool.destroy(curRecord);
            return 1;
        case REV32(TREE):
            TREE.pool.destroy(curRecord);
            return 1;
        case REV32(FLOR):
            FLOR.pool.destroy(curRecord);
            return 1;
        case REV32(FURN):
            FURN.pool.destroy(curRecord);
            return 1;
        case REV32(WEAP):
            WEAP.pool.destroy(curRecord);
            return 1;
        case REV32(AMMO):
            AMMO.pool.destroy(curRecord);
            return 1;
        case REV32(NPC_):
            NPC_.pool.destroy(curRecord);
            return 1;
        case REV32(CREA):
            CREA.pool.destroy(curRecord);
            return 1;
        case REV32(LVLC):
            LVLC.pool.destroy(curRecord);
            return 1;
        case REV32(SLGM):
            SLGM.pool.destroy(curRecord);
            return 1;
        case REV32(KEYM):
            KEYM.pool.destroy(curRecord);
            return 1;
        case REV32(ALCH):
            ALCH.pool.destroy(curRecord);
            return 1;
        case REV32(SBSP):
            SBSP.pool.destroy(curRecord);
            return 1;
        case REV32(SGST):
            SGST.pool.destroy(curRecord);
            return 1;
        case REV32(LVLI):
            LVLI.pool.destroy(curRecord);
            return 1;
        case REV32(WTHR):
            WTHR.pool.destroy(curRecord);
            return 1;
        case REV32(CLMT):
            CLMT.pool.destroy(curRecord);
            return 1;
        case REV32(REGN):
            REGN.pool.destroy(curRecord);
            return 1;
        case REV32(CELL):
            switch(LowType)
                {
                case REV32(CELL):
                    CELL.pool.destroy(curRecord);
                    return 1;
                case REV32(ACHR):
                    ((CELLRecord *)ParentRecord)->achr_pool.destroy(curRecord);
                    return 1;
                case REV32(ACRE):
                    ((CELLRecord *)ParentRecord)->acre_pool.destroy(curRecord);
                    return 1;
                case REV32(REFR):
                    ((CELLRecord *)ParentRecord)->refr_pool.destroy(curRecord);
                    return 1;
                case REV32(PGRD):
                    CELL.pgrd_pool.destroy(curRecord);
                    ((CELLRecord *)ParentRecord)->PGRD = NULL;
                    return 1;
                default:
                    printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", curRecord->GetStrType(), ((STRING)&TopType)[0], ((STRING)&TopType)[1], ((STRING)&TopType)[2], ((STRING)&TopType)[3], reader.getModName());
                    return 0;
                }
            return 0;
        case REV32(WRLD):
            switch(MidType)
                {
                case REV32(WRLD):
                    WRLD.pool.destroy(curRecord);
                    return 1;
                case REV32(CELL):
                    switch(LowType)
                        {
                        case REV32(CELL):
                            if(((WRLDRecord *)ParentRecord)->CELL == curRecord)
                                {
                                WRLD.cell_pool.destroy(curRecord);
                                ((WRLDRecord *)ParentRecord)->CELL = NULL;
                                }
                            else
                                ((WRLDRecord *)ParentRecord)->cell_pool.destroy(curRecord);
                            return 1;
                        case REV32(ACHR):
                            ((CELLRecord *)ParentRecord)->achr_pool.destroy(curRecord);
                            return 1;
                        case REV32(ACRE):
                            ((CELLRecord *)ParentRecord)->acre_pool.destroy(curRecord);
                            return 1;
                        case REV32(REFR):
                            ((CELLRecord *)ParentRecord)->refr_pool.destroy(curRecord);
                            return 1;
                        case REV32(PGRD):
                            CELL.pgrd_pool.destroy(curRecord);
                            ((CELLRecord *)ParentRecord)->PGRD = NULL;
                            return 1;
                        case REV32(LAND):
                            WRLD.land_pool.destroy(curRecord);
                            ((CELLRecord *)ParentRecord)->LAND = NULL;
                            return 1;
                        default:
                            printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", curRecord->GetStrType(), ((STRING)&TopType)[0], ((STRING)&TopType)[1], ((STRING)&TopType)[2], ((STRING)&TopType)[3], reader.getModName());
                            return 0;
                        }
                    return 0;
                case REV32(ROAD):
                    WRLD.road_pool.destroy(curRecord);
                    ((WRLDRecord *)ParentRecord)->ROAD = NULL;
                    return 1;
                default:
                    printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", curRecord->GetStrType(), ((STRING)&TopType)[0], ((STRING)&TopType)[1], ((STRING)&TopType)[2], ((STRING)&TopType)[3], reader.getModName());
                    return 0;
                }
            return 0;
        case REV32(DIAL):
            switch(LowType)
                {
                case REV32(DIAL):
                    DIAL.pool.destroy(curRecord);
                    return 1;
                case REV32(INFO):
                    ((DIALRecord *)ParentRecord)->info_pool.destroy(curRecord);
                    return 1;
                default:
                    printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", curRecord->GetStrType(), ((STRING)&TopType)[0], ((STRING)&TopType)[1], ((STRING)&TopType)[2], ((STRING)&TopType)[3], reader.getModName());
                    return 0;
                }
            return 0;
        case REV32(QUST):
            QUST.pool.destroy(curRecord);
            return 1;
        case REV32(IDLE):
            IDLE.pool.destroy(curRecord);
            return 1;
        case REV32(PACK):
            PACK.pool.destroy(curRecord);
            return 1;
        case REV32(CSTY):
            CSTY.pool.destroy(curRecord);
            return 1;
        case REV32(LSCR):
            LSCR.pool.destroy(curRecord);
            return 1;
        case REV32(LVSP):
            LVSP.pool.destroy(curRecord);
            return 1;
        case REV32(ANIO):
            ANIO.pool.destroy(curRecord);
            return 1;
        case REV32(WATR):
            WATR.pool.destroy(curRecord);
            return 1;
        case REV32(EFSH):
            EFSH.pool.destroy(curRecord);
            return 1;
        default:
            printer("TES4File::DeleteRecord: Error - Unable to delete record type (%s) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", curRecord->GetStrType(), ((STRING)&TopType)[0], ((STRING)&TopType)[1], ((STRING)&TopType)[2], ((STRING)&TopType)[3], reader.getModName());
            return 0;
        }
    return 0;
    }

SINT32 TES4File::CleanMasters(std::vector<FormIDResolver *> &Expanders)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES4File::CleanMasters: Error - Unable to clean masters in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
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
        if(GMST.pool.VisitRecords(NULL, checker, false)) continue;
        if(GLOB.pool.VisitRecords(NULL, checker, false)) continue;
        if(CLAS.pool.VisitRecords(NULL, checker, false)) continue;
        if(FACT.pool.VisitRecords(NULL, checker, false)) continue;
        if(HAIR.pool.VisitRecords(NULL, checker, false)) continue;
        if(EYES.pool.VisitRecords(NULL, checker, false)) continue;
        if(RACE.pool.VisitRecords(NULL, checker, false)) continue;
        if(SOUN.pool.VisitRecords(NULL, checker, false)) continue;
        if(SKIL.pool.VisitRecords(NULL, checker, false)) continue;
        if(MGEF.pool.VisitRecords(NULL, checker, false)) continue;
        if(SCPT.pool.VisitRecords(NULL, checker, false)) continue;
        if(LTEX.pool.VisitRecords(NULL, checker, false)) continue;
        if(ENCH.pool.VisitRecords(NULL, checker, false)) continue;
        if(SPEL.pool.VisitRecords(NULL, checker, false)) continue;
        if(BSGN.pool.VisitRecords(NULL, checker, false)) continue;
        if(ACTI.pool.VisitRecords(NULL, checker, false)) continue;
        if(APPA.pool.VisitRecords(NULL, checker, false)) continue;
        if(ARMO.pool.VisitRecords(NULL, checker, false)) continue;
        if(BOOK.pool.VisitRecords(NULL, checker, false)) continue;
        if(CLOT.pool.VisitRecords(NULL, checker, false)) continue;
        if(CONT.pool.VisitRecords(NULL, checker, false)) continue;
        if(DOOR.pool.VisitRecords(NULL, checker, false)) continue;
        if(INGR.pool.VisitRecords(NULL, checker, false)) continue;
        if(LIGH.pool.VisitRecords(NULL, checker, false)) continue;
        if(MISC.pool.VisitRecords(NULL, checker, false)) continue;
        if(STAT.pool.VisitRecords(NULL, checker, false)) continue;
        if(GRAS.pool.VisitRecords(NULL, checker, false)) continue;
        if(TREE.pool.VisitRecords(NULL, checker, false)) continue;
        if(FLOR.pool.VisitRecords(NULL, checker, false)) continue;
        if(FURN.pool.VisitRecords(NULL, checker, false)) continue;
        if(WEAP.pool.VisitRecords(NULL, checker, false)) continue;
        if(AMMO.pool.VisitRecords(NULL, checker, false)) continue;
        if(NPC_.pool.VisitRecords(NULL, checker, false)) continue;
        if(CREA.pool.VisitRecords(NULL, checker, false)) continue;
        if(LVLC.pool.VisitRecords(NULL, checker, false)) continue;
        if(SLGM.pool.VisitRecords(NULL, checker, false)) continue;
        if(KEYM.pool.VisitRecords(NULL, checker, false)) continue;
        if(ALCH.pool.VisitRecords(NULL, checker, false)) continue;
        if(SBSP.pool.VisitRecords(NULL, checker, false)) continue;
        if(SGST.pool.VisitRecords(NULL, checker, false)) continue;
        if(LVLI.pool.VisitRecords(NULL, checker, false)) continue;
        if(WTHR.pool.VisitRecords(NULL, checker, false)) continue;
        if(CLMT.pool.VisitRecords(NULL, checker, false)) continue;
        if(REGN.pool.VisitRecords(NULL, checker, false)) continue;
        if(CELL.pool.VisitRecords(NULL, checker, true)) continue;
        if(WRLD.pool.VisitRecords(NULL, checker, true)) continue;
        if(DIAL.pool.VisitRecords(NULL, checker, true)) continue;
        if(QUST.pool.VisitRecords(NULL, checker, false)) continue;
        if(IDLE.pool.VisitRecords(NULL, checker, false)) continue;
        if(PACK.pool.VisitRecords(NULL, checker, false)) continue;
        if(CSTY.pool.VisitRecords(NULL, checker, false)) continue;
        if(LSCR.pool.VisitRecords(NULL, checker, false)) continue;
        if(LVSP.pool.VisitRecords(NULL, checker, false)) continue;
        if(ANIO.pool.VisitRecords(NULL, checker, false)) continue;
        if(WATR.pool.VisitRecords(NULL, checker, false)) continue;
        if(EFSH.pool.VisitRecords(NULL, checker, false)) continue;
        //printer("ToRemove: %s\n", TES4.MAST[p].value);
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

SINT32 TES4File::Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod)
    {
    if(!Flags.IsSaveable)
        {
        printer("TES4File::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", reader.getModName());
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
    formCount += GMST.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GLOB.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLAS.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FACT.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HAIR.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EYES.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += RACE.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SOUN.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SKIL.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MGEF.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCPT.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LTEX.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ENCH.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SPEL.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BSGN.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ACTI.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += APPA.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ARMO.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BOOK.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLOT.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CONT.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DOOR.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += INGR.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LIGH.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MISC.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += STAT.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GRAS.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TREE.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FLOR.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FURN.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WEAP.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += AMMO.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NPC_.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CREA.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLC.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SLGM.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += KEYM.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ALCH.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SBSP.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SGST.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLI.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WTHR.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLMT.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += REGN.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CELL.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WRLD.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod, FormIDHandler);
    formCount += DIAL.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += QUST.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLE.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PACK.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CSTY.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LSCR.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVSP.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ANIO.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WATR.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EFSH.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    writer.file_write(30, &formCount, 4);
    writer.close();
    if(CloseMod)
        Close();
    return 0;
    }

void TES4File::VisitAllRecords(RecordOp &op)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES4File::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
        return;
        }

    Record * topRecord = &TES4;

    //This visits every record and subrecord
    op.Accept(topRecord);
    GMST.pool.VisitRecords(NULL, op, true);
    GLOB.pool.VisitRecords(NULL, op, true);
    CLAS.pool.VisitRecords(NULL, op, true);
    FACT.pool.VisitRecords(NULL, op, true);
    HAIR.pool.VisitRecords(NULL, op, true);
    EYES.pool.VisitRecords(NULL, op, true);
    RACE.pool.VisitRecords(NULL, op, true);
    SOUN.pool.VisitRecords(NULL, op, true);
    SKIL.pool.VisitRecords(NULL, op, true);
    MGEF.pool.VisitRecords(NULL, op, true);
    SCPT.pool.VisitRecords(NULL, op, true);
    LTEX.pool.VisitRecords(NULL, op, true);
    ENCH.pool.VisitRecords(NULL, op, true);
    SPEL.pool.VisitRecords(NULL, op, true);
    BSGN.pool.VisitRecords(NULL, op, true);
    ACTI.pool.VisitRecords(NULL, op, true);
    APPA.pool.VisitRecords(NULL, op, true);
    ARMO.pool.VisitRecords(NULL, op, true);
    BOOK.pool.VisitRecords(NULL, op, true);
    CLOT.pool.VisitRecords(NULL, op, true);
    CONT.pool.VisitRecords(NULL, op, true);
    DOOR.pool.VisitRecords(NULL, op, true);
    INGR.pool.VisitRecords(NULL, op, true);
    LIGH.pool.VisitRecords(NULL, op, true);
    MISC.pool.VisitRecords(NULL, op, true);
    STAT.pool.VisitRecords(NULL, op, true);
    GRAS.pool.VisitRecords(NULL, op, true);
    TREE.pool.VisitRecords(NULL, op, true);
    FLOR.pool.VisitRecords(NULL, op, true);
    FURN.pool.VisitRecords(NULL, op, true);
    WEAP.pool.VisitRecords(NULL, op, true);
    AMMO.pool.VisitRecords(NULL, op, true);
    NPC_.pool.VisitRecords(NULL, op, true);
    CREA.pool.VisitRecords(NULL, op, true);
    LVLC.pool.VisitRecords(NULL, op, true);
    SLGM.pool.VisitRecords(NULL, op, true);
    KEYM.pool.VisitRecords(NULL, op, true);
    ALCH.pool.VisitRecords(NULL, op, true);
    SBSP.pool.VisitRecords(NULL, op, true);
    SGST.pool.VisitRecords(NULL, op, true);
    LVLI.pool.VisitRecords(NULL, op, true);
    WTHR.pool.VisitRecords(NULL, op, true);
    CLMT.pool.VisitRecords(NULL, op, true);
    REGN.pool.VisitRecords(NULL, op, true);
    CELL.pool.VisitRecords(NULL, op, true);
    WRLD.pool.VisitRecords(NULL, op, true);
    DIAL.pool.VisitRecords(NULL, op, true);
    QUST.pool.VisitRecords(NULL, op, true);
    IDLE.pool.VisitRecords(NULL, op, true);
    PACK.pool.VisitRecords(NULL, op, true);
    CSTY.pool.VisitRecords(NULL, op, true);
    LSCR.pool.VisitRecords(NULL, op, true);
    LVSP.pool.VisitRecords(NULL, op, true);
    ANIO.pool.VisitRecords(NULL, op, true);
    WATR.pool.VisitRecords(NULL, op, true);
    EFSH.pool.VisitRecords(NULL, op, true);
    return;
    }

void TES4File::VisitRecords(const UINT32 &TopRecordType, const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
    {
    if(Flags.IsNoLoad)
        {
        printer("TES4File::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
        return;
        }

    Record * topRecord = &TES4;

    //This visits only the top records specified.
    switch(TopRecordType)
        {
        case REV32(TES4):
            op.Accept(topRecord);
            break;
        case REV32(GMST):
            GMST.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(GLOB):
            GLOB.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CLAS):
            CLAS.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(FACT):
            FACT.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(HAIR):
            HAIR.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(EYES):
            EYES.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(RACE):
            RACE.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SOUN):
            SOUN.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SKIL):
            SKIL.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(MGEF):
            MGEF.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SCPT):
            SCPT.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LTEX):
            LTEX.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ENCH):
            ENCH.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SPEL):
            SPEL.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(BSGN):
            BSGN.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ACTI):
            ACTI.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(APPA):
            APPA.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ARMO):
            ARMO.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(BOOK):
            BOOK.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CLOT):
            CLOT.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CONT):
            CONT.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(DOOR):
            DOOR.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(INGR):
            INGR.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LIGH):
            LIGH.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(MISC):
            MISC.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(STAT):
            STAT.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(GRAS):
            GRAS.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(TREE):
            TREE.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(FLOR):
            FLOR.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(FURN):
            FURN.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(WEAP):
            WEAP.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(AMMO):
            AMMO.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(NPC_):
            NPC_.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CREA):
            CREA.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LVLC):
            LVLC.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SLGM):
            SLGM.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(KEYM):
            KEYM.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ALCH):
            ALCH.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SBSP):
            SBSP.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SGST):
            SGST.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LVLI):
            LVLI.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(WTHR):
            WTHR.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CLMT):
            CLMT.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(REGN):
            REGN.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CELL):
            CELL.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(WRLD):
            WRLD.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(DIAL):
            DIAL.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(QUST):
            QUST.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(IDLE):
            IDLE.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(PACK):
            PACK.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CSTY):
            CSTY.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LSCR):
            LSCR.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(LVSP):
            LVSP.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ANIO):
            ANIO.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(WATR):
            WATR.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(EFSH):
            EFSH.pool.VisitRecords(RecordType, op, DeepVisit);
            break;
        default:
            if(RecordType)
                printer("TES4File::VisitRecords: Error - Unable to visit record type (%c%c%c%c) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ((STRING)&TopRecordType)[0], ((STRING)&TopRecordType)[1], ((STRING)&TopRecordType)[2], ((STRING)&TopRecordType)[3], reader.getModName());
            else
                printer("TES4File::VisitRecords: Error - Unable to visit record type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&TopRecordType)[0], ((STRING)&TopRecordType)[1], ((STRING)&TopRecordType)[2], ((STRING)&TopRecordType)[3], reader.getModName());
            break;
        }
    return;
    }