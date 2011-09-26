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
        GRUPRecords<Ob::GMSTRecord, REV32(GMST), 20, true> GMST;
        GRUPRecords<Ob::GLOBRecord, REV32(GLOB), 20> GLOB;
        GRUPRecords<Ob::CLASRecord, REV32(CLAS), 20> CLAS;
        GRUPRecords<Ob::FACTRecord, REV32(FACT), 20> FACT;
        GRUPRecords<Ob::HAIRRecord, REV32(HAIR), 20> HAIR;
        GRUPRecords<Ob::EYESRecord, REV32(EYES), 20> EYES;
        GRUPRecords<Ob::RACERecord, REV32(RACE), 20> RACE;
        GRUPRecords<Ob::SOUNRecord, REV32(SOUN), 20> SOUN;
        GRUPRecords<Ob::SKILRecord, REV32(SKIL), 20> SKIL;
        GRUPRecords<Ob::MGEFRecord, REV32(MGEF), 20, true> MGEF;
        GRUPRecords<Ob::SCPTRecord, REV32(SCPT), 20> SCPT;
        GRUPRecords<Ob::LTEXRecord, REV32(LTEX), 20> LTEX;
        GRUPRecords<Ob::ENCHRecord, REV32(ENCH), 20> ENCH;
        GRUPRecords<Ob::SPELRecord, REV32(SPEL), 20> SPEL;
        GRUPRecords<Ob::BSGNRecord, REV32(BSGN), 20> BSGN;
        GRUPRecords<Ob::ACTIRecord, REV32(ACTI), 20> ACTI;
        GRUPRecords<Ob::APPARecord, REV32(APPA), 20> APPA;
        GRUPRecords<Ob::ARMORecord, REV32(ARMO), 20> ARMO;
        GRUPRecords<Ob::BOOKRecord, REV32(BOOK), 20> BOOK;
        GRUPRecords<Ob::CLOTRecord, REV32(CLOT), 20> CLOT;
        GRUPRecords<Ob::CONTRecord, REV32(CONT), 20> CONT;
        GRUPRecords<Ob::DOORRecord, REV32(DOOR), 20> DOOR;
        GRUPRecords<Ob::INGRRecord, REV32(INGR), 20> INGR;
        GRUPRecords<Ob::LIGHRecord, REV32(LIGH), 20> LIGH;
        GRUPRecords<Ob::MISCRecord, REV32(MISC), 20> MISC;
        GRUPRecords<Ob::STATRecord, REV32(STAT), 20> STAT;
        GRUPRecords<Ob::GRASRecord, REV32(GRAS), 20> GRAS;
        GRUPRecords<Ob::TREERecord, REV32(TREE), 20> TREE;
        GRUPRecords<Ob::FLORRecord, REV32(FLOR), 20> FLOR;
        GRUPRecords<Ob::FURNRecord, REV32(FURN), 20> FURN;
        GRUPRecords<Ob::WEAPRecord, REV32(WEAP), 20> WEAP;
        GRUPRecords<Ob::AMMORecord, REV32(AMMO), 20> AMMO;
        GRUPRecords<Ob::NPC_Record, REV32(NPC_), 20> NPC_;
        GRUPRecords<Ob::CREARecord, REV32(CREA), 20> CREA;
        GRUPRecords<Ob::LVLCRecord, REV32(LVLC), 20> LVLC;
        GRUPRecords<Ob::SLGMRecord, REV32(SLGM), 20> SLGM;
        GRUPRecords<Ob::KEYMRecord, REV32(KEYM), 20> KEYM;
        GRUPRecords<Ob::ALCHRecord, REV32(ALCH), 20> ALCH;
        GRUPRecords<Ob::SBSPRecord, REV32(SBSP), 20> SBSP;
        GRUPRecords<Ob::SGSTRecord, REV32(SGST), 20> SGST;
        GRUPRecords<Ob::LVLIRecord, REV32(LVLI), 20> LVLI;
        GRUPRecords<Ob::WTHRRecord, REV32(WTHR), 20> WTHR;
        GRUPRecords<Ob::CLMTRecord, REV32(CLMT), 20> CLMT;
        GRUPRecords<Ob::REGNRecord, REV32(REGN), 20> REGN;
        GRUPRecords<Ob::CELLRecord, REV32(CELL), 20> CELL;
        GRUPRecords<Ob::WRLDRecord, REV32(WRLD), 20> WRLD;
        GRUPRecords<Ob::DIALRecord, REV32(DIAL), 20> DIAL;
        GRUPRecords<Ob::QUSTRecord, REV32(QUST), 20> QUST;
        GRUPRecords<Ob::IDLERecord, REV32(IDLE), 20> IDLE;
        GRUPRecords<Ob::PACKRecord, REV32(PACK), 20> PACK;
        GRUPRecords<Ob::CSTYRecord, REV32(CSTY), 20> CSTY;
        GRUPRecords<Ob::LSCRRecord, REV32(LSCR), 20> LSCR;
        GRUPRecords<Ob::LVSPRecord, REV32(LVSP), 20> LVSP;
        GRUPRecords<Ob::ANIORecord, REV32(ANIO), 20> ANIO;
        GRUPRecords<Ob::WATRRecord, REV32(WATR), 20> WATR;
        GRUPRecords<Ob::EFSHRecord, REV32(EFSH), 20> EFSH;

        TES4File(Collection *_Parent, STRING FileName, STRING ModName, const UINT32 _flags);
        ~TES4File();

        SINT32   LoadTES4();
        SINT32   Load(RecordOp &read_parser, RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords);
        UINT32   GetNumRecords(const UINT32 &RecordType);
        Record * CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options);
        SINT32   DeleteRecord(Record *&curRecord, RecordOp &deindexer);
        SINT32   Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod, RecordOp &indexer);

        void     VisitAllRecords(RecordOp &op);
        void     VisitRecords(const UINT32 &RecordType, RecordOp &op);
    };