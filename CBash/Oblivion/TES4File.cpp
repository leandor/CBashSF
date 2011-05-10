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
    PROFILE_FUNC

    if(TES4.IsLoaded() || !Open())
        {
        if(!TES4.IsLoaded() && !Open())
            printf("TES4File::LoadTES4: Error - Unable to load the TES4 record for mod \"%s\". The mod is not open for reading.\n", reader.getModName());
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
    if(TES4.IsLoaded())
        printf("_fIsLoaded Flag used!!!!: %08X\n", TES4.flags);

    //Normally would read the record with the read method
    //However, that requires recData to be set on the record
    // and that can only be set by the constructor
    //TES4 is constructed when the modfile is created
    // so the info isn't available then.
    //Must make sure this mimics the read method as needed
    TES4.ParseRecord(reader.getBuffer(20), recSize);
    TES4.IsLoaded(true);
    TES4.IsChanged(true);
    reader.skip(recSize);
    return 1;
    }

SINT32 TES4File::Load(RecordOp &indexer, std::vector<FormIDResolver *> &Expanders)
    {
    PROFILE_FUNC

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
                printf("TES4File::Load: Error - Unable to load mod \"%s\". The mod is not open.\n", reader.getModName());
            else
                printf("TES4File::Load: Error - Unable to load mod \"%s\". The mod is already loaded.\n", reader.getModName());
            }
        return 0;
        }
    //printf("%08X\n", Flags.GetFlags());
    //printf("Loading %s\n", FileName);
    //for(UINT32 x = 0; x < FormIDHandler.LoadOrder255.size(); ++x)
    //    printf("Master in load order %02X: %s\n", x, FormIDHandler.LoadOrder255[x]);
    Flags.LoadedGRUPs = true;
    UINT32 GRUPSize;
    UINT32 GRUPLabel;
    boost::unordered_set<UINT32> UsedFormIDs;

    RecordReader fullReader(FormIDHandler, Expanders);
    RecordOp skipReader;

    RecordProcessor processor_min(reader, FormIDHandler, skipReader, Flags, UsedFormIDs);
    RecordProcessor processor_full(reader, FormIDHandler, fullReader, Flags, UsedFormIDs);

    RecordProcessor &processor = Flags.IsFullLoad ? processor_full : processor_min;

    //RecordProcessFunc RecordProcessor = (Flags.IsSkipNewRecords || Flags.IsTrackNewTypes) ? (Flags.IsSkipNewRecords ? &ProcessRecord_SkipNew : &ProcessRecord_TrackNew) : &ProcessRecord_Base;

    while(!reader.eof()){
        reader.skip(4); //Skip "GRUP"
        reader.read(&GRUPSize, 4);
        reader.read(&GRUPLabel, 4);
        reader.skip(4); //Skip type (tops will all == 0)
        //printf("%c%c%c%c\n", ((char *)&GRUPLabel)[0], ((char *)&GRUPLabel)[1], ((char *)&GRUPLabel)[2], ((char *)&GRUPLabel)[3]);
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
                WRLD.Skim(reader, GRUPSize, processor, indexer);
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
                    printf("TES4File::Skim: Warning - Unknown record group (%c%c%c%c) encountered in mod \"%s\". Bad file structure, zeros found past end of groups.\n", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], reader.getModName());
                    return 1;
                    }
                else
                    printf("TES4File::Skim: Error - Unknown record group (%c%c%c%c) encountered in mod \"%s\". ", ((STRING)&GRUPLabel)[0], ((STRING)&GRUPLabel)[1], ((STRING)&GRUPLabel)[2], ((STRING)&GRUPLabel)[3], reader.getModName());

                if(GRUPSize == 0)
                    {
                    printf("Unable to continue loading.\n");
                    return 1;
                    }
                else
                    {
                    printf("Attempting to skip and continue loading.\n");
                    reader.skip(GRUPSize - 16); //Skip type (tops will all == 0)
                    }
                break;
            }
        };
    return 1;
    }

UINT32 TES4File::GetNumRecords(const UINT32 &RecordType)
    {
    PROFILE_FUNC

    switch(RecordType)
        {
        case REV32(GMST):
            return (UINT32)GMST.Records.size();
        case REV32(GLOB):
            return (UINT32)GLOB.Records.size();
        case REV32(CLAS):
            return (UINT32)CLAS.Records.size();
        case REV32(FACT):
            return (UINT32)FACT.Records.size();
        case REV32(HAIR):
            return (UINT32)HAIR.Records.size();
        case REV32(EYES):
            return (UINT32)EYES.Records.size();
        case REV32(RACE):
            return (UINT32)RACE.Records.size();
        case REV32(SOUN):
            return (UINT32)SOUN.Records.size();
        case REV32(SKIL):
            return (UINT32)SKIL.Records.size();
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
        case REV32(BSGN):
            return (UINT32)BSGN.Records.size();
        case REV32(ACTI):
            return (UINT32)ACTI.Records.size();
        case REV32(APPA):
            return (UINT32)APPA.Records.size();
        case REV32(ARMO):
            return (UINT32)ARMO.Records.size();
        case REV32(BOOK):
            return (UINT32)BOOK.Records.size();
        case REV32(CLOT):
            return (UINT32)CLOT.Records.size();
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
        case REV32(GRAS):
            return (UINT32)GRAS.Records.size();
        case REV32(TREE):
            return (UINT32)TREE.Records.size();
        case REV32(FLOR):
            return (UINT32)FLOR.Records.size();
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
        case REV32(SLGM):
            return (UINT32)SLGM.Records.size();
        case REV32(KEYM):
            return (UINT32)KEYM.Records.size();
        case REV32(ALCH):
            return (UINT32)ALCH.Records.size();
        case REV32(SBSP):
            return (UINT32)SBSP.Records.size();
        case REV32(SGST):
            return (UINT32)SGST.Records.size();
        case REV32(LVLI):
            return (UINT32)LVLI.Records.size();
        case REV32(WTHR):
            return (UINT32)WTHR.Records.size();
        case REV32(CLMT):
            return (UINT32)CLMT.Records.size();
        case REV32(REGN):
            return (UINT32)REGN.Records.size();
        case REV32(CELL):
            return (UINT32)CELL.Records.size();
        case REV32(WRLD):
            return (UINT32)WRLD.Records.size();
        case REV32(DIAL):
            return (UINT32)DIAL.Records.size();
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
            printf("TES4File::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". SubRecords are counted via GetFieldAttribute API function.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        ///////////////////////////////////////////////
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
        case REV32(LVSP):
            return (UINT32)LVSP.Records.size();
        case REV32(ANIO):
            return (UINT32)ANIO.Records.size();
        case REV32(WATR):
            return (UINT32)WATR.Records.size();
        case REV32(EFSH):
            return (UINT32)EFSH.Records.size();
        default:
            printf("TES4File::GetNumRecords: Warning - Unable to count records (%c%c%c%c) in mod \"%s\". Unrecognized record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        }
    return 0;
    }

Record * TES4File::CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("TES4File::CreateRecord: Error - Unable to create any records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
        return NULL;
        }

    Record *newRecord = NULL;

    switch(RecordType)
        {
        case REV32(GMST):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printf("TES4File::CreateRecord: Error - Unable to create GMST record in mod \"%s\". No valid editorID is available.\n", reader.getModName());
                return NULL;
                }

            GMST.Records.push_back(new GMSTRecord((GMSTRecord *)SourceRecord));
            newRecord = GMST.Records.back();

            if(RecordEditorID != NULL)
                {
                ((GMSTRecord *)newRecord)->EDID.Copy(RecordEditorID);
                ((GMSTRecord *)newRecord)->DATA.format = ((GMSTRecord *)newRecord)->EDID.value[0];
                }
            break;
        case REV32(GLOB):
            GLOB.Records.push_back(new GLOBRecord((GLOBRecord *)SourceRecord));
            newRecord = GLOB.Records.back();
            break;
        case REV32(CLAS):
            CLAS.Records.push_back(new CLASRecord((CLASRecord *)SourceRecord));
            newRecord = CLAS.Records.back();
            break;
        case REV32(FACT):
            FACT.Records.push_back(new FACTRecord((FACTRecord *)SourceRecord));
            newRecord = FACT.Records.back();
            break;
        case REV32(HAIR):
            HAIR.Records.push_back(new HAIRRecord((HAIRRecord *)SourceRecord));
            newRecord = HAIR.Records.back();
            break;
        case REV32(EYES):
            EYES.Records.push_back(new EYESRecord((EYESRecord *)SourceRecord));
            newRecord = EYES.Records.back();
            break;
        case REV32(RACE):
            RACE.Records.push_back(new RACERecord((RACERecord *)SourceRecord));
            newRecord = RACE.Records.back();
            break;
        case REV32(SOUN):
            SOUN.Records.push_back(new SOUNRecord((SOUNRecord *)SourceRecord));
            newRecord = SOUN.Records.back();
            break;
        case REV32(SKIL):
            SKIL.Records.push_back(new SKILRecord((SKILRecord *)SourceRecord));
            newRecord = SKIL.Records.back();
            break;
        case REV32(MGEF):
            if(RecordEditorID == NULL && SourceRecord == NULL)
                {
                printf("TES4File::CreateRecord: Error - Unable to create MGEF record in mod \"%s\". No valid editorID is available.\n", reader.getModName());
                return NULL;
                }

            MGEF.Records.push_back(new MGEFRecord((MGEFRecord *)SourceRecord));
            newRecord = MGEF.Records.back();

            if(RecordEditorID != NULL)
                {
                if(((MGEFRecord *)newRecord)->OBME.IsLoaded())
                    {
                    memcpy(&(((MGEFRecord *)newRecord)->OBME->EDDX.value.mgefCode)[0], RecordEditorID, 4);
                    ((MGEFRecord *)newRecord)->OBME->EDDX.value.mgefCode[4] = 0x00;
                    }
                else
                    ((MGEFRecord *)newRecord)->EDID.Copy(RecordEditorID);
                }
            break;
        case REV32(SCPT):
            SCPT.Records.push_back(new SCPTRecord((SCPTRecord *)SourceRecord));
            newRecord = SCPT.Records.back();
            break;
        case REV32(LTEX):
            LTEX.Records.push_back(new LTEXRecord((LTEXRecord *)SourceRecord));
            newRecord = LTEX.Records.back();
            break;
        case REV32(ENCH):
            ENCH.Records.push_back(new ENCHRecord((ENCHRecord *)SourceRecord));
            newRecord = ENCH.Records.back();
            break;
        case REV32(SPEL):
            SPEL.Records.push_back(new SPELRecord((SPELRecord *)SourceRecord));
            newRecord = SPEL.Records.back();
            break;
        case REV32(BSGN):
            BSGN.Records.push_back(new BSGNRecord((BSGNRecord *)SourceRecord));
            newRecord = BSGN.Records.back();
            break;
        case REV32(ACTI):
            ACTI.Records.push_back(new ACTIRecord((ACTIRecord *)SourceRecord));
            newRecord = ACTI.Records.back();
            break;
        case REV32(APPA):
            APPA.Records.push_back(new APPARecord((APPARecord *)SourceRecord));
            newRecord = APPA.Records.back();
            break;
        case REV32(ARMO):
            ARMO.Records.push_back(new ARMORecord((ARMORecord *)SourceRecord));
            newRecord = ARMO.Records.back();
            break;
        case REV32(BOOK):
            BOOK.Records.push_back(new BOOKRecord((BOOKRecord *)SourceRecord));
            newRecord = BOOK.Records.back();
            break;
        case REV32(CLOT):
            CLOT.Records.push_back(new CLOTRecord((CLOTRecord *)SourceRecord));
            newRecord = CLOT.Records.back();
            break;
        case REV32(CONT):
            CONT.Records.push_back(new CONTRecord((CONTRecord *)SourceRecord));
            newRecord = CONT.Records.back();
            break;
        case REV32(DOOR):
            DOOR.Records.push_back(new DOORRecord((DOORRecord *)SourceRecord));
            newRecord = DOOR.Records.back();
            break;
        case REV32(INGR):
            INGR.Records.push_back(new INGRRecord((INGRRecord *)SourceRecord));
            newRecord = INGR.Records.back();
            break;
        case REV32(LIGH):
            LIGH.Records.push_back(new LIGHRecord((LIGHRecord *)SourceRecord));
            newRecord = LIGH.Records.back();
            break;
        case REV32(MISC):
            MISC.Records.push_back(new MISCRecord((MISCRecord *)SourceRecord));
            newRecord = MISC.Records.back();
            break;
        case REV32(STAT):
            STAT.Records.push_back(new STATRecord((STATRecord *)SourceRecord));
            newRecord = STAT.Records.back();
            break;
        case REV32(GRAS):
            GRAS.Records.push_back(new GRASRecord((GRASRecord *)SourceRecord));
            newRecord = GRAS.Records.back();
            break;
        case REV32(TREE):
            TREE.Records.push_back(new TREERecord((TREERecord *)SourceRecord));
            newRecord = TREE.Records.back();
            break;
        case REV32(FLOR):
            FLOR.Records.push_back(new FLORRecord((FLORRecord *)SourceRecord));
            newRecord = FLOR.Records.back();
            break;
        case REV32(FURN):
            FURN.Records.push_back(new FURNRecord((FURNRecord *)SourceRecord));
            newRecord = FURN.Records.back();
            break;
        case REV32(WEAP):
            WEAP.Records.push_back(new WEAPRecord((WEAPRecord *)SourceRecord));
            newRecord = WEAP.Records.back();
            break;
        case REV32(AMMO):
            AMMO.Records.push_back(new AMMORecord((AMMORecord *)SourceRecord));
            newRecord = AMMO.Records.back();
            break;
        case REV32(NPC_):
            NPC_.Records.push_back(new NPC_Record((NPC_Record *)SourceRecord));
            newRecord = NPC_.Records.back();
            break;
        case REV32(CREA):
            CREA.Records.push_back(new CREARecord((CREARecord *)SourceRecord));
            newRecord = CREA.Records.back();
            break;
        case REV32(LVLC):
            LVLC.Records.push_back(new LVLCRecord((LVLCRecord *)SourceRecord));
            newRecord = LVLC.Records.back();
            break;
        case REV32(SLGM):
            SLGM.Records.push_back(new SLGMRecord((SLGMRecord *)SourceRecord));
            newRecord = SLGM.Records.back();
            break;
        case REV32(KEYM):
            KEYM.Records.push_back(new KEYMRecord((KEYMRecord *)SourceRecord));
            newRecord = KEYM.Records.back();
            break;
        case REV32(ALCH):
            ALCH.Records.push_back(new ALCHRecord((ALCHRecord *)SourceRecord));
            newRecord = ALCH.Records.back();
            break;
        case REV32(SBSP):
            SBSP.Records.push_back(new SBSPRecord((SBSPRecord *)SourceRecord));
            newRecord = SBSP.Records.back();
            break;
        case REV32(SGST):
            SGST.Records.push_back(new SGSTRecord((SGSTRecord *)SourceRecord));
            newRecord = SGST.Records.back();
            break;
        case REV32(LVLI):
            LVLI.Records.push_back(new LVLIRecord((LVLIRecord *)SourceRecord));
            newRecord = LVLI.Records.back();
            break;
        case REV32(WTHR):
            WTHR.Records.push_back(new WTHRRecord((WTHRRecord *)SourceRecord));
            newRecord = WTHR.Records.back();
            break;
        case REV32(CLMT):
            CLMT.Records.push_back(new CLMTRecord((CLMTRecord *)SourceRecord));
            newRecord = CLMT.Records.back();
            break;
        case REV32(REGN):
            REGN.Records.push_back(new REGNRecord((REGNRecord *)SourceRecord));
            newRecord = REGN.Records.back();
            break;
        case REV32(CELL):
            if(ParentRecord == NULL)
                {
                CELL.Records.push_back(new CELLRecord((CELLRecord *)SourceRecord));
                newRecord = CELL.Records.back();

                ((CELLRecord *)newRecord)->IsInterior(true);
                }
            else
                {
                if(ParentRecord->GetType() != REV32(WRLD))
                    {
                    printf("TES4File::CreateRecord: Error - Unable to create CELL record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be CELL parents.\n", reader.getModName(), ParentRecord->GetStrType());
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
        case REV32(WRLD):
            WRLD.Records.push_back(new WRLDRecord((WRLDRecord *)SourceRecord));
            newRecord = WRLD.Records.back();
            break;
        case REV32(DIAL):
            DIAL.Records.push_back(new DIALRecord((DIALRecord *)SourceRecord));
            newRecord = DIAL.Records.back();
            break;
        case REV32(PGRD):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("TES4File::CreateRecord: Error - Unable to create PGRD record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be PGRD parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            //If a cell pathgrid already exists, return it instead of making a new one
            if(((CELLRecord *)ParentRecord)->PGRD != NULL)
                return ((CELLRecord *)ParentRecord)->PGRD;

            ((CELLRecord *)ParentRecord)->PGRD = new PGRDRecord((PGRDRecord *)SourceRecord);
            newRecord = ((CELLRecord *)ParentRecord)->PGRD;
            break;
        case REV32(LAND):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("TES4File::CreateRecord: Error - Unable to create LAND record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be LAND parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            //If a cell land already exists, return it instead of making a new one
            if(((CELLRecord *)ParentRecord)->LAND != NULL)
                return ((CELLRecord *)ParentRecord)->LAND;

            ((CELLRecord *)ParentRecord)->LAND = new LANDRecord((LANDRecord *)SourceRecord);
            newRecord = ((CELLRecord *)ParentRecord)->LAND;
            break;
        case REV32(ACHR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("TES4File::CreateRecord: Error - Unable to create ACHR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACHR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((CELLRecord *)ParentRecord)->ACHR.push_back(new ACHRRecord((ACHRRecord *)SourceRecord));
            newRecord = ((CELLRecord *)ParentRecord)->ACHR.back();
            break;
        case REV32(ACRE):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("TES4File::CreateRecord: Error - Unable to create ACRE record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be ACRE parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((CELLRecord *)ParentRecord)->ACRE.push_back(new ACRERecord((ACRERecord *)SourceRecord));
            newRecord = ((CELLRecord *)ParentRecord)->ACRE.back();
            break;
        case REV32(REFR):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(CELL))
                {
                printf("TES4File::CreateRecord: Error - Unable to create REFR record in mod \"%s\". Parent record type (%s) is invalid, only CELL records can be REFR parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((CELLRecord *)ParentRecord)->REFR.push_back(new REFRRecord((REFRRecord *)SourceRecord));
            newRecord = ((CELLRecord *)ParentRecord)->REFR.back();
            break;
        case REV32(ROAD):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(WRLD))
                {
                printf("TES4File::CreateRecord: Error - Unable to create ROAD record in mod \"%s\". Parent record type (%s) is invalid, only WRLD records can be ROAD parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            //If a world road already exists, return it instead of making a new one
            if(((WRLDRecord *)ParentRecord)->ROAD != NULL)
                return ((WRLDRecord *)ParentRecord)->ROAD;

            ((WRLDRecord *)ParentRecord)->ROAD = new ROADRecord((ROADRecord *)SourceRecord);
            newRecord = ((WRLDRecord *)ParentRecord)->ROAD;
            break;
        case REV32(INFO):
            if(ParentRecord == NULL || ParentRecord->GetType() != REV32(DIAL))
                {
                printf("TES4File::CreateRecord: Error - Unable to create INFO record in mod \"%s\". Parent record type (%s) is invalid, only DIAL records can be INFO parents.\n", reader.getModName(), ParentRecord->GetStrType());
                return NULL;
                }

            ((DIALRecord *)ParentRecord)->INFO.push_back(new INFORecord((INFORecord *)SourceRecord));
            newRecord = ((DIALRecord *)ParentRecord)->INFO.back();
            break;
        case REV32(QUST):
            QUST.Records.push_back(new QUSTRecord((QUSTRecord *)SourceRecord));
            newRecord = QUST.Records.back();
            break;
        case REV32(IDLE):
            IDLE.Records.push_back(new IDLERecord((IDLERecord *)SourceRecord));
            newRecord = IDLE.Records.back();
            break;
        case REV32(PACK):
            PACK.Records.push_back(new PACKRecord((PACKRecord *)SourceRecord));
            newRecord = PACK.Records.back();
            break;
        case REV32(CSTY):
            CSTY.Records.push_back(new CSTYRecord((CSTYRecord *)SourceRecord));
            newRecord = CSTY.Records.back();
            break;
        case REV32(LSCR):
            LSCR.Records.push_back(new LSCRRecord((LSCRRecord *)SourceRecord));
            newRecord = LSCR.Records.back();
            break;
        case REV32(LVSP):
            LVSP.Records.push_back(new LVSPRecord((LVSPRecord *)SourceRecord));
            newRecord = LVSP.Records.back();
            break;
        case REV32(ANIO):
            ANIO.Records.push_back(new ANIORecord((ANIORecord *)SourceRecord));
            newRecord = ANIO.Records.back();
            break;
        case REV32(WATR):
            WATR.Records.push_back(new WATRRecord((WATRRecord *)SourceRecord));
            newRecord = WATR.Records.back();
            break;
        case REV32(EFSH):
            EFSH.Records.push_back(new EFSHRecord((EFSHRecord *)SourceRecord));
            newRecord = EFSH.Records.back();
            break;
        default:
            printf("TES4File::CreateRecord: Error - Unable to create (%c%c%c%c) record in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], reader.getModName());
            break;
        }
    return newRecord;
    }

SINT32 TES4File::CleanMasters(std::vector<FormIDResolver *> &Expanders)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("TES4File::CleanMasters: Error - Unable to clean masters in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
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

SINT32 TES4File::Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod)
    {
    PROFILE_FUNC

    if(!Flags.IsSaveable)
        {
        printf("TES4File::Save: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", reader.getModName());
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
    formCount += GLOB.WriteGRUP(REV32(GLOB), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLAS.WriteGRUP(REV32(CLAS), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FACT.WriteGRUP(REV32(FACT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += HAIR.WriteGRUP(REV32(HAIR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EYES.WriteGRUP(REV32(EYES), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += RACE.WriteGRUP(REV32(RACE), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SOUN.WriteGRUP(REV32(SOUN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SKIL.WriteGRUP(REV32(SKIL), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MGEF.WriteGRUP(REV32(MGEF), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SCPT.WriteGRUP(REV32(SCPT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LTEX.WriteGRUP(REV32(LTEX), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ENCH.WriteGRUP(REV32(ENCH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SPEL.WriteGRUP(REV32(SPEL), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BSGN.WriteGRUP(REV32(BSGN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ACTI.WriteGRUP(REV32(ACTI), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += APPA.WriteGRUP(REV32(APPA), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ARMO.WriteGRUP(REV32(ARMO), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += BOOK.WriteGRUP(REV32(BOOK), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLOT.WriteGRUP(REV32(CLOT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CONT.WriteGRUP(REV32(CONT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DOOR.WriteGRUP(REV32(DOOR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += INGR.WriteGRUP(REV32(INGR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LIGH.WriteGRUP(REV32(LIGH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += MISC.WriteGRUP(REV32(MISC), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += STAT.WriteGRUP(REV32(STAT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += GRAS.WriteGRUP(REV32(GRAS), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += TREE.WriteGRUP(REV32(TREE), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FLOR.WriteGRUP(REV32(FLOR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += FURN.WriteGRUP(REV32(FURN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WEAP.WriteGRUP(REV32(WEAP), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += AMMO.WriteGRUP(REV32(AMMO), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += NPC_.WriteGRUP(REV32(NPC_), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CREA.WriteGRUP(REV32(CREA), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLC.WriteGRUP(REV32(LVLC), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SLGM.WriteGRUP(REV32(SLGM), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += KEYM.WriteGRUP(REV32(KEYM), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ALCH.WriteGRUP(REV32(ALCH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SBSP.WriteGRUP(REV32(SBSP), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += SGST.WriteGRUP(REV32(SGST), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVLI.WriteGRUP(REV32(LVLI), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WTHR.WriteGRUP(REV32(WTHR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CLMT.WriteGRUP(REV32(CLMT), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += REGN.WriteGRUP(REV32(REGN), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CELL.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WRLD.WriteGRUP(writer, FormIDHandler, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += DIAL.WriteGRUP(writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += QUST.WriteGRUP(REV32(QUST), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += IDLE.WriteGRUP(REV32(IDLE), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += PACK.WriteGRUP(REV32(PACK), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += CSTY.WriteGRUP(REV32(CSTY), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LSCR.WriteGRUP(REV32(LSCR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += LVSP.WriteGRUP(REV32(LVSP), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += ANIO.WriteGRUP(REV32(ANIO), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += WATR.WriteGRUP(REV32(WATR), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);
    formCount += EFSH.WriteGRUP(REV32(EFSH), writer, Expanders, expander, collapser, bMastersChanged, CloseMod);

    //update formCount. Cheaper to go back and write it at the end than to calculate it before any writing.
    writer.file_write(30, &formCount, 4);
    writer.close();
    if(CloseMod)
        Close();
    return 0;
    }

void TES4File::VisitAllRecords(RecordOp &op)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("TES4File::VisitAllRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
        return;
        }

    Record * topRecord = &TES4;

    //This visits every record and subrecord
    op.Accept(topRecord);
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

void TES4File::VisitRecords(const UINT32 &TopRecordType, const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
    {
    PROFILE_FUNC

    if(Flags.IsNoLoad)
        {
        printf("TES4File::VisitRecords: Error - Unable to visit records in mod \"%s\". The mod is flagged not to be loaded.\n", reader.getModName());
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
            GMST.VisitRecords(RecordType, op, DeepVisit);
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
        case REV32(SKIL):
            SKIL.VisitRecords(RecordType, op, DeepVisit);
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
        case REV32(BSGN):
            BSGN.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ACTI):
            ACTI.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(APPA):
            APPA.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ARMO):
            ARMO.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(BOOK):
            BOOK.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(CLOT):
            CLOT.VisitRecords(RecordType, op, DeepVisit);
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
        case REV32(GRAS):
            GRAS.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(TREE):
            TREE.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(FLOR):
            FLOR.VisitRecords(RecordType, op, DeepVisit);
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
        case REV32(SLGM):
            SLGM.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(KEYM):
            KEYM.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(ALCH):
            ALCH.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SBSP):
            SBSP.VisitRecords(RecordType, op, DeepVisit);
            break;
        case REV32(SGST):
            SGST.VisitRecords(RecordType, op, DeepVisit);
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
        case REV32(LVSP):
            LVSP.VisitRecords(RecordType, op, DeepVisit);
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
        default:
            if(RecordType)
                printf("TES4File::VisitRecords: Error - Unable to visit record type (%c%c%c%c) under top level type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&RecordType)[0], ((STRING)&RecordType)[1], ((STRING)&RecordType)[2], ((STRING)&RecordType)[3], ((STRING)&TopRecordType)[0], ((STRING)&TopRecordType)[1], ((STRING)&TopRecordType)[2], ((STRING)&TopRecordType)[3], reader.getModName());
            else
                printf("TES4File::VisitRecords: Error - Unable to visit record type (%c%c%c%c) in mod \"%s\". Unknown record type.\n", ((STRING)&TopRecordType)[0], ((STRING)&TopRecordType)[1], ((STRING)&TopRecordType)[2], ((STRING)&TopRecordType)[3], reader.getModName());
            break;
        }
    return;
    }