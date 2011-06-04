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
#pragma once
// TES4File.h
#include "../Common.h"
#include "../ModFile.h"
#include "../GenericRecord.h"
#include "../GRUPRecord.h"
#include "Records/GMSTRecord.h"
#include "Records/GLOBRecord.h"
#include "Records/CLASRecord.h"
#include "Records/FACTRecord.h"
#include "Records/HAIRRecord.h"
#include "Records/EYESRecord.h"
#include "Records/RACERecord.h"
#include "Records/SOUNRecord.h"
#include "Records/SKILRecord.h"
#include "Records/MGEFRecord.h"
#include "Records/SCPTRecord.h"
#include "Records/LTEXRecord.h"
#include "Records/ENCHRecord.h"
#include "Records/SPELRecord.h"
#include "Records/BSGNRecord.h"
#include "Records/ACTIRecord.h"
#include "Records/APPARecord.h"
#include "Records/ARMORecord.h"
#include "Records/BOOKRecord.h"
#include "Records/CLOTRecord.h"
#include "Records/CONTRecord.h"
#include "Records/DOORRecord.h"
#include "Records/INGRRecord.h"
#include "Records/LIGHRecord.h"
#include "Records/MISCRecord.h"
#include "Records/STATRecord.h"
#include "Records/GRASRecord.h"
#include "Records/TREERecord.h"
#include "Records/FLORRecord.h"
#include "Records/FURNRecord.h"
#include "Records/WEAPRecord.h"
#include "Records/AMMORecord.h"
#include "Records/NPC_Record.h"
#include "Records/CREARecord.h"
#include "Records/LVLIRecord.h"
#include "Records/LVLCRecord.h"
#include "Records/LVSPRecord.h"
#include "Records/SLGMRecord.h"
#include "Records/KEYMRecord.h"
#include "Records/ALCHRecord.h"
#include "Records/SBSPRecord.h"
#include "Records/SGSTRecord.h"
#include "Records/WTHRRecord.h"
#include "Records/CLMTRecord.h"
#include "Records/REGNRecord.h"
#include "Records/CELLRecord.h"
#include "Records/WRLDRecord.h"
#include "Records/DIALRecord.h"
#include "Records/QUSTRecord.h"
#include "Records/IDLERecord.h"
#include "Records/PACKRecord.h"
#include "Records/CSTYRecord.h"
#include "Records/LSCRRecord.h"
#include "Records/ANIORecord.h"
#include "Records/WATRRecord.h"
#include "Records/EFSHRecord.h"
//#include <boost/threadpool.hpp>

class TES4File : public ModFile
    {
    public:
        GRUPRecords<GMSTRecord, REV32(GMST), 5> GMST;
        GRUPRecords<GLOBRecord, REV32(GLOB), 5> GLOB;
        GRUPRecords<CLASRecord, REV32(CLAS), 5> CLAS;
        GRUPRecords<FACTRecord, REV32(FACT), 5> FACT;
        GRUPRecords<HAIRRecord, REV32(HAIR), 5> HAIR;
        GRUPRecords<EYESRecord, REV32(EYES), 5> EYES;
        GRUPRecords<RACERecord, REV32(RACE), 5> RACE;
        GRUPRecords<SOUNRecord, REV32(SOUN), 5> SOUN;
        GRUPRecords<SKILRecord, REV32(SKIL), 5> SKIL;
        GRUPRecords<MGEFRecord, REV32(MGEF), 5> MGEF;
        GRUPRecords<SCPTRecord, REV32(SCPT), 5> SCPT;
        GRUPRecords<LTEXRecord, REV32(LTEX), 5> LTEX;
        GRUPRecords<ENCHRecord, REV32(ENCH), 5> ENCH;
        GRUPRecords<SPELRecord, REV32(SPEL), 5> SPEL;
        GRUPRecords<BSGNRecord, REV32(BSGN), 5> BSGN;
        GRUPRecords<ACTIRecord, REV32(ACTI), 5> ACTI;
        GRUPRecords<APPARecord, REV32(APPA), 5> APPA;
        GRUPRecords<ARMORecord, REV32(ARMO), 5> ARMO;
        GRUPRecords<BOOKRecord, REV32(BOOK), 5> BOOK;
        GRUPRecords<CLOTRecord, REV32(CLOT), 5> CLOT;
        GRUPRecords<CONTRecord, REV32(CONT), 5> CONT;
        GRUPRecords<DOORRecord, REV32(DOOR), 5> DOOR;
        GRUPRecords<INGRRecord, REV32(INGR), 5> INGR;
        GRUPRecords<LIGHRecord, REV32(LIGH), 5> LIGH;
        GRUPRecords<MISCRecord, REV32(MISC), 5> MISC;
        GRUPRecords<STATRecord, REV32(STAT), 5> STAT;
        GRUPRecords<GRASRecord, REV32(GRAS), 5> GRAS;
        GRUPRecords<TREERecord, REV32(TREE), 5> TREE;
        GRUPRecords<FLORRecord, REV32(FLOR), 5> FLOR;
        GRUPRecords<FURNRecord, REV32(FURN), 5> FURN;
        GRUPRecords<WEAPRecord, REV32(WEAP), 5> WEAP;
        GRUPRecords<AMMORecord, REV32(AMMO), 5> AMMO;
        GRUPRecords<NPC_Record, REV32(NPC_), 5> NPC_;
        GRUPRecords<CREARecord, REV32(CREA), 5> CREA;
        GRUPRecords<LVLCRecord, REV32(LVLC), 5> LVLC;
        GRUPRecords<SLGMRecord, REV32(SLGM), 5> SLGM;
        GRUPRecords<KEYMRecord, REV32(KEYM), 5> KEYM;
        GRUPRecords<ALCHRecord, REV32(ALCH), 5> ALCH;
        GRUPRecords<SBSPRecord, REV32(SBSP), 5> SBSP;
        GRUPRecords<SGSTRecord, REV32(SGST), 5> SGST;
        GRUPRecords<LVLIRecord, REV32(LVLI), 5> LVLI;
        GRUPRecords<WTHRRecord, REV32(WTHR), 5> WTHR;
        GRUPRecords<CLMTRecord, REV32(CLMT), 5> CLMT;
        GRUPRecords<REGNRecord, REV32(REGN), 5> REGN;
        GRUPRecords<CELLRecord, REV32(CELL), 5> CELL;
        GRUPRecords<WRLDRecord, REV32(WRLD), 5> WRLD;
        GRUPRecords<DIALRecord, REV32(DIAL), 5> DIAL;
        GRUPRecords<QUSTRecord, REV32(QUST), 5> QUST;
        GRUPRecords<IDLERecord, REV32(IDLE), 5> IDLE;
        GRUPRecords<PACKRecord, REV32(PACK), 5> PACK;
        GRUPRecords<CSTYRecord, REV32(CSTY), 5> CSTY;
        GRUPRecords<LSCRRecord, REV32(LSCR), 5> LSCR;
        GRUPRecords<LVSPRecord, REV32(LVSP), 5> LVSP;
        GRUPRecords<ANIORecord, REV32(ANIO), 5> ANIO;
        GRUPRecords<WATRRecord, REV32(WATR), 5> WATR;
        GRUPRecords<EFSHRecord, REV32(EFSH), 5> EFSH;

        TES4File(STRING FileName, STRING ModName, const UINT32 _flags);
        ~TES4File();

        SINT32   LoadTES4();
        SINT32   Load(RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords);
        UINT32   GetNumRecords(const UINT32 &RecordType);
        Record * CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options);
        SINT32   DeleteRecord(Record *&curRecord, Record *&ParentRecord);
        SINT32   CleanMasters(std::vector<FormIDResolver *> &Expanders);
        SINT32   Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod);

        void     VisitAllRecords(RecordOp &op);
        void     VisitRecords(const UINT32 &TopRecordType, const UINT32 &RecordType, RecordOp &op, bool DeepVisit=false);
    };