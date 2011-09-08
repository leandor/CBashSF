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
        GRUPRecords<Ob::GMSTRecord, REV32(GMST), 5, true> GMST;
        GRUPRecords<Ob::GLOBRecord, REV32(GLOB), 5> GLOB;
        GRUPRecords<Ob::CLASRecord, REV32(CLAS), 5> CLAS;
        GRUPRecords<Ob::FACTRecord, REV32(FACT), 5> FACT;
        GRUPRecords<Ob::HAIRRecord, REV32(HAIR), 5> HAIR;
        GRUPRecords<Ob::EYESRecord, REV32(EYES), 5> EYES;
        GRUPRecords<Ob::RACERecord, REV32(RACE), 5> RACE;
        GRUPRecords<Ob::SOUNRecord, REV32(SOUN), 5> SOUN;
        GRUPRecords<Ob::SKILRecord, REV32(SKIL), 5> SKIL;
        GRUPRecords<Ob::MGEFRecord, REV32(MGEF), 5, true> MGEF;
        GRUPRecords<Ob::SCPTRecord, REV32(SCPT), 5> SCPT;
        GRUPRecords<Ob::LTEXRecord, REV32(LTEX), 5> LTEX;
        GRUPRecords<Ob::ENCHRecord, REV32(ENCH), 5> ENCH;
        GRUPRecords<Ob::SPELRecord, REV32(SPEL), 5> SPEL;
        GRUPRecords<Ob::BSGNRecord, REV32(BSGN), 5> BSGN;
        GRUPRecords<Ob::ACTIRecord, REV32(ACTI), 5> ACTI;
        GRUPRecords<Ob::APPARecord, REV32(APPA), 5> APPA;
        GRUPRecords<Ob::ARMORecord, REV32(ARMO), 5> ARMO;
        GRUPRecords<Ob::BOOKRecord, REV32(BOOK), 5> BOOK;
        GRUPRecords<Ob::CLOTRecord, REV32(CLOT), 5> CLOT;
        GRUPRecords<Ob::CONTRecord, REV32(CONT), 5> CONT;
        GRUPRecords<Ob::DOORRecord, REV32(DOOR), 5> DOOR;
        GRUPRecords<Ob::INGRRecord, REV32(INGR), 5> INGR;
        GRUPRecords<Ob::LIGHRecord, REV32(LIGH), 5> LIGH;
        GRUPRecords<Ob::MISCRecord, REV32(MISC), 5> MISC;
        GRUPRecords<Ob::STATRecord, REV32(STAT), 5> STAT;
        GRUPRecords<Ob::GRASRecord, REV32(GRAS), 5> GRAS;
        GRUPRecords<Ob::TREERecord, REV32(TREE), 5> TREE;
        GRUPRecords<Ob::FLORRecord, REV32(FLOR), 5> FLOR;
        GRUPRecords<Ob::FURNRecord, REV32(FURN), 5> FURN;
        GRUPRecords<Ob::WEAPRecord, REV32(WEAP), 5> WEAP;
        GRUPRecords<Ob::AMMORecord, REV32(AMMO), 5> AMMO;
        GRUPRecords<Ob::NPC_Record, REV32(NPC_), 5> NPC_;
        GRUPRecords<Ob::CREARecord, REV32(CREA), 5> CREA;
        GRUPRecords<Ob::LVLCRecord, REV32(LVLC), 5> LVLC;
        GRUPRecords<Ob::SLGMRecord, REV32(SLGM), 5> SLGM;
        GRUPRecords<Ob::KEYMRecord, REV32(KEYM), 5> KEYM;
        GRUPRecords<Ob::ALCHRecord, REV32(ALCH), 5> ALCH;
        GRUPRecords<Ob::SBSPRecord, REV32(SBSP), 5> SBSP;
        GRUPRecords<Ob::SGSTRecord, REV32(SGST), 5> SGST;
        GRUPRecords<Ob::LVLIRecord, REV32(LVLI), 5> LVLI;
        GRUPRecords<Ob::WTHRRecord, REV32(WTHR), 5> WTHR;
        GRUPRecords<Ob::CLMTRecord, REV32(CLMT), 5> CLMT;
        GRUPRecords<Ob::REGNRecord, REV32(REGN), 5> REGN;
        GRUPRecords<Ob::CELLRecord, REV32(CELL), 5> CELL;
        GRUPRecords<Ob::WRLDRecord, REV32(WRLD), 5> WRLD;
        GRUPRecords<Ob::DIALRecord, REV32(DIAL), 5> DIAL;
        GRUPRecords<Ob::QUSTRecord, REV32(QUST), 5> QUST;
        GRUPRecords<Ob::IDLERecord, REV32(IDLE), 5> IDLE;
        GRUPRecords<Ob::PACKRecord, REV32(PACK), 5> PACK;
        GRUPRecords<Ob::CSTYRecord, REV32(CSTY), 5> CSTY;
        GRUPRecords<Ob::LSCRRecord, REV32(LSCR), 5> LSCR;
        GRUPRecords<Ob::LVSPRecord, REV32(LVSP), 5> LVSP;
        GRUPRecords<Ob::ANIORecord, REV32(ANIO), 5> ANIO;
        GRUPRecords<Ob::WATRRecord, REV32(WATR), 5> WATR;
        GRUPRecords<Ob::EFSHRecord, REV32(EFSH), 5> EFSH;

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