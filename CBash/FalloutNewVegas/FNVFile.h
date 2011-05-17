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
// FNVFile.h
#include "../Common.h"
#include "../ModFile.h"
#include "../GenericRecord.h"
#include "../GRUPRecord.h"
#include "Records/GMSTRecord.h"
#include "Records/TXSTRecord.h"
#include "Records/MICNRecord.h"
#include "Records/GLOBRecord.h"
#include "Records/CLASRecord.h"
#include "Records/FACTRecord.h"
#include "Records/HDPTRecord.h"
#include "Records/HAIRRecord.h"
#include "Records/EYESRecord.h"
#include "Records/RACERecord.h"
#include "Records/SOUNRecord.h"
#include "Records/ASPCRecord.h"
#include "Records/MGEFRecord.h"
#include "Records/SCPTRecord.h"
#include "Records/LTEXRecord.h"
#include "Records/ENCHRecord.h"
#include "Records/SPELRecord.h"
#include "Records/ACTIRecord.h"
#include "Records/TACTRecord.h"
#include "Records/TERMRecord.h"
#include "Records/ARMORecord.h"
#include "Records/BOOKRecord.h"
#include "Records/CONTRecord.h"
#include "Records/DOORRecord.h"
#include "Records/INGRRecord.h"
#include "Records/LIGHRecord.h"
#include "Records/MISCRecord.h"
#include "Records/STATRecord.h"
#include "Records/SCOLRecord.h"
#include "Records/MSTTRecord.h"
#include "Records/PWATRecord.h"
#include "Records/GRASRecord.h"
#include "Records/TREERecord.h"
#include "Records/FURNRecord.h"
#include "Records/WEAPRecord.h"
#include "Records/AMMORecord.h"
#include "Records/NPC_Record.h"
#include "Records/CREARecord.h"
#include "Records/LVLCRecord.h"
#include "Records/LVLNRecord.h"
#include "Records/KEYMRecord.h"
#include "Records/ALCHRecord.h"
#include "Records/IDLMRecord.h"
#include "Records/NOTERecord.h"
#include "Records/COBJRecord.h"
#include "Records/PROJRecord.h"
#include "Records/LVLIRecord.h"
#include "Records/WTHRRecord.h"
#include "Records/CLMTRecord.h"
#include "Records/REGNRecord.h"
#include "Records/NAVIRecord.h"
#include "Records/CELLRecord.h"
#include "Records/WRLDRecord.h"
#include "Records/DIALRecord.h"
//#include "Records/QUSTRecord.h"
//#include "Records/IDLERecord.h"
//#include "Records/PACKRecord.h"
//#include "Records/CSTYRecord.h"
//#include "Records/LSCRRecord.h"
//#include "Records/ANIORecord.h"
//#include "Records/WATRRecord.h"
//#include "Records/EFSHRecord.h"
//#include "Records/EXPLRecord.h"
//#include "Records/DEBRRecord.h"
//#include "Records/IMGSRecord.h"
//#include "Records/IMADRecord.h"
//#include "Records/FLSTRecord.h"
//#include "Records/PERKRecord.h"
//#include "Records/BPTDRecord.h"
//#include "Records/ADDNRecord.h"
//#include "Records/AVIFRecord.h"
//#include "Records/RADSRecord.h"
//#include "Records/CAMSRecord.h"
//#include "Records/CPTHRecord.h"
//#include "Records/VTYPRecord.h"
//#include "Records/IPCTRecord.h"
//#include "Records/IPDSRecord.h"
//#include "Records/ARMARecord.h"
//#include "Records/ECZNRecord.h"
//#include "Records/MESGRecord.h"
//#include "Records/RGDLRecord.h"
//#include "Records/DOBJRecord.h"
//#include "Records/LGTMRecord.h"
//#include "Records/MUSCRecord.h"
//#include "Records/IMODRecord.h"
//#include "Records/REPURecord.h"
//#include "Records/RCPERecord.h"
//#include "Records/RCCTRecord.h"
//#include "Records/CHIPRecord.h"
//#include "Records/CSNORecord.h"
//#include "Records/LSCTRecord.h"
//#include "Records/MSETRecord.h"
//#include "Records/ALOCRecord.h"
//#include "Records/CHALRecord.h"
//#include "Records/AMEFRecord.h"
//#include "Records/CCRDRecord.h"
//#include "Records/CMNYRecord.h"
//#include "Records/CDCKRecord.h"
//#include "Records/DEHYRecord.h"
//#include "Records/HUNGRecord.h"
//#include "Records/SLPDRecord.h"

class FNVFile : public ModFile
    {
    public:
        FNVGRUPRecords<FNV::GMSTRecord> GMST;
        FNVGRUPRecords<FNV::TXSTRecord> TXST;
        FNVGRUPRecords<FNV::MICNRecord> MICN;
        FNVGRUPRecords<FNV::GLOBRecord> GLOB;
        FNVGRUPRecords<FNV::CLASRecord> CLAS;
        FNVGRUPRecords<FNV::FACTRecord> FACT;
        FNVGRUPRecords<FNV::HDPTRecord> HDPT;
        FNVGRUPRecords<FNV::HAIRRecord> HAIR;
        FNVGRUPRecords<FNV::EYESRecord> EYES;
        FNVGRUPRecords<FNV::RACERecord> RACE;
        FNVGRUPRecords<FNV::SOUNRecord> SOUN;
        FNVGRUPRecords<FNV::ASPCRecord> ASPC;
        FNVGRUPRecords<FNV::MGEFRecord> MGEF;
        FNVGRUPRecords<FNV::SCPTRecord> SCPT;
        FNVGRUPRecords<FNV::LTEXRecord> LTEX;
        FNVGRUPRecords<FNV::ENCHRecord> ENCH;
        FNVGRUPRecords<FNV::SPELRecord> SPEL;
        FNVGRUPRecords<FNV::ACTIRecord> ACTI;
        FNVGRUPRecords<FNV::TACTRecord> TACT;
        FNVGRUPRecords<FNV::TERMRecord> TERM;
        FNVGRUPRecords<FNV::ARMORecord> ARMO;
        FNVGRUPRecords<FNV::BOOKRecord> BOOK;
        FNVGRUPRecords<FNV::CONTRecord> CONT;
        FNVGRUPRecords<FNV::DOORRecord> DOOR;
        FNVGRUPRecords<FNV::INGRRecord> INGR;
        FNVGRUPRecords<FNV::LIGHRecord> LIGH;
        FNVGRUPRecords<FNV::MISCRecord> MISC;
        FNVGRUPRecords<FNV::STATRecord> STAT;
        FNVGRUPRecords<FNV::SCOLRecord> SCOL;
        FNVGRUPRecords<FNV::MSTTRecord> MSTT;
        FNVGRUPRecords<FNV::PWATRecord> PWAT;
        FNVGRUPRecords<FNV::GRASRecord> GRAS;
        FNVGRUPRecords<FNV::TREERecord> TREE;
        FNVGRUPRecords<FNV::FURNRecord> FURN;
        FNVGRUPRecords<FNV::WEAPRecord> WEAP;
        FNVGRUPRecords<FNV::AMMORecord> AMMO;
        FNVGRUPRecords<FNV::NPC_Record> NPC_;
        FNVGRUPRecords<FNV::CREARecord> CREA;
        FNVGRUPRecords<FNV::LVLCRecord> LVLC;
        FNVGRUPRecords<FNV::LVLNRecord> LVLN;
        FNVGRUPRecords<FNV::KEYMRecord> KEYM;
        FNVGRUPRecords<FNV::ALCHRecord> ALCH;
        FNVGRUPRecords<FNV::IDLMRecord> IDLM;
        FNVGRUPRecords<FNV::NOTERecord> NOTE;
        FNVGRUPRecords<FNV::COBJRecord> COBJ;
        FNVGRUPRecords<FNV::PROJRecord> PROJ;
        FNVGRUPRecords<FNV::LVLIRecord> LVLI;
        FNVGRUPRecords<FNV::WTHRRecord> WTHR;
        FNVGRUPRecords<FNV::CLMTRecord> CLMT;
        FNVGRUPRecords<FNV::REGNRecord> REGN;
        FNVGRUPRecords<FNV::NAVIRecord> NAVI;
        FNVGRUPRecords<FNV::CELLRecord> CELL;
        FNVGRUPRecords<FNV::WRLDRecord> WRLD;
        FNVGRUPRecords<FNV::DIALRecord> DIAL;
        //FNVGRUPRecords<FNV::QUSTRecord> QUST;
        //FNVGRUPRecords<FNV::IDLERecord> IDLE;
        //FNVGRUPRecords<FNV::PACKRecord> PACK;
        //FNVGRUPRecords<FNV::CSTYRecord> CSTY;
        //FNVGRUPRecords<FNV::LSCRRecord> LSCR;
        //FNVGRUPRecords<FNV::ANIORecord> ANIO;
        //FNVGRUPRecords<FNV::WATRRecord> WATR;
        //FNVGRUPRecords<FNV::EFSHRecord> EFSH;
        //FNVGRUPRecords<FNV::EXPLRecord> EXPL;
        //FNVGRUPRecords<FNV::DEBRRecord> DEBR;
        //FNVGRUPRecords<FNV::IMGSRecord> IMGS;
        //FNVGRUPRecords<FNV::IMADRecord> IMAD;
        //FNVGRUPRecords<FNV::FLSTRecord> FLST;
        //FNVGRUPRecords<FNV::PERKRecord> PERK;
        //FNVGRUPRecords<FNV::BPTDRecord> BPTD;
        //FNVGRUPRecords<FNV::ADDNRecord> ADDN;
        //FNVGRUPRecords<FNV::AVIFRecord> AVIF;
        //FNVGRUPRecords<FNV::RADSRecord> RADS;
        //FNVGRUPRecords<FNV::CAMSRecord> CAMS;
        //FNVGRUPRecords<FNV::CPTHRecord> CPTH;
        //FNVGRUPRecords<FNV::VTYPRecord> VTYP;
        //FNVGRUPRecords<FNV::IPCTRecord> IPCT;
        //FNVGRUPRecords<FNV::IPDSRecord> IPDS;
        //FNVGRUPRecords<FNV::ARMARecord> ARMA;
        //FNVGRUPRecords<FNV::ECZNRecord> ECZN;
        //FNVGRUPRecords<FNV::MESGRecord> MESG;
        //FNVGRUPRecords<FNV::RGDLRecord> RGDL;
        //FNVGRUPRecords<FNV::DOBJRecord> DOBJ;
        //FNVGRUPRecords<FNV::LGTMRecord> LGTM;
        //FNVGRUPRecords<FNV::MUSCRecord> MUSC;
        //FNVGRUPRecords<FNV::IMODRecord> IMOD;
        //FNVGRUPRecords<FNV::REPURecord> REPU;
        //FNVGRUPRecords<FNV::RCPERecord> RCPE;
        //FNVGRUPRecords<FNV::RCCTRecord> RCCT;
        //FNVGRUPRecords<FNV::CHIPRecord> CHIP;
        //FNVGRUPRecords<FNV::CSNORecord> CSNO;
        //FNVGRUPRecords<FNV::LSCTRecord> LSCT;
        //FNVGRUPRecords<FNV::MSETRecord> MSET;
        //FNVGRUPRecords<FNV::ALOCRecord> ALOC;
        //FNVGRUPRecords<FNV::CHALRecord> CHAL;
        //FNVGRUPRecords<FNV::AMEFRecord> AMEF;
        //FNVGRUPRecords<FNV::CCRDRecord> CCRD;
        //FNVGRUPRecords<FNV::CMNYRecord> CMNY;
        //FNVGRUPRecords<FNV::CDCKRecord> CDCK;
        //FNVGRUPRecords<FNV::DEHYRecord> DEHY;
        //FNVGRUPRecords<FNV::HUNGRecord> HUNG;
        //FNVGRUPRecords<FNV::SLPDRecord> SLPD;

        FNVFile(STRING FileName, STRING ModName, const UINT32 _flags);
        ~FNVFile();

        Record * GetTES4();
        SINT32   LoadTES4();
        SINT32   Load(RecordOp &indexer, std::vector<FormIDResolver *> &Expanders);
        UINT32   GetNumRecords(const UINT32 &RecordType);
        STRING   GetMasterName(UINT8 &CollapsedIndex);
        Record * CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options);
        SINT32   CleanMasters(std::vector<FormIDResolver *> &Expanders);
        SINT32   Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod);

        void     VisitAllRecords(RecordOp &op);
        void     VisitRecords(const UINT32 &TopRecordType, const UINT32 &RecordType, RecordOp &op, bool DeepVisit=false);
    };