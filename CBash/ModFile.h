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
// ModFile.h
#include "Common.h"
//ADD DEFINITIONS HERE
#include "BaseRecord.h"
#include "GRUPRecord.h"
#include "Records/TES4Record.h"
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
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/threadpool.hpp>

using namespace boost::interprocess;

class ModFile
    {
    private:
        mapped_region *m_region;
        unsigned int fileEnd;
        bool IsOpen, LoadedGRUPs, IsNew, IsDummy;
    public:
        _FormIDHandler FormIDHandler;
        unsigned char *fileBuffer;
        char *FileName;
        TES4Record TES4;
        //ADD DEFINITIONS HERE
        GRUPRecords<GMSTRecord> GMST;
        GRUPRecords<GLOBRecord> GLOB;
        GRUPRecords<CLASRecord> CLAS;
        GRUPRecords<FACTRecord> FACT;
        GRUPRecords<HAIRRecord> HAIR;
        GRUPRecords<EYESRecord> EYES;
        GRUPRecords<RACERecord> RACE;
        GRUPRecords<SOUNRecord> SOUN;
        GRUPRecords<SKILRecord> SKIL;
        GRUPRecords<MGEFRecord> MGEF;
        GRUPRecords<SCPTRecord> SCPT;
        GRUPRecords<LTEXRecord> LTEX;
        GRUPRecords<ENCHRecord> ENCH;
        GRUPRecords<SPELRecord> SPEL;
        GRUPRecords<BSGNRecord> BSGN;
        GRUPRecords<ACTIRecord> ACTI;
        GRUPRecords<APPARecord> APPA;
        GRUPRecords<ARMORecord> ARMO;
        GRUPRecords<BOOKRecord> BOOK;
        GRUPRecords<CLOTRecord> CLOT;
        GRUPRecords<CONTRecord> CONT;
        GRUPRecords<DOORRecord> DOOR;
        GRUPRecords<INGRRecord> INGR;
        GRUPRecords<LIGHRecord> LIGH;
        GRUPRecords<MISCRecord> MISC;
        GRUPRecords<STATRecord> STAT;
        GRUPRecords<GRASRecord> GRAS;
        GRUPRecords<TREERecord> TREE;
        GRUPRecords<FLORRecord> FLOR;
        GRUPRecords<FURNRecord> FURN;
        GRUPRecords<WEAPRecord> WEAP;
        GRUPRecords<AMMORecord> AMMO;
        GRUPRecords<NPC_Record> NPC_;
        GRUPRecords<CREARecord> CREA;
        GRUPRecords<LVLCRecord> LVLC;
        GRUPRecords<SLGMRecord> SLGM;
        GRUPRecords<KEYMRecord> KEYM;
        GRUPRecords<ALCHRecord> ALCH;
        GRUPRecords<SBSPRecord> SBSP;
        GRUPRecords<SGSTRecord> SGST;
        GRUPRecords<LVLIRecord> LVLI;
        GRUPRecords<WTHRRecord> WTHR;
        GRUPRecords<CLMTRecord> CLMT;
        GRUPRecords<REGNRecord> REGN;
        GRUPRecords<CELLRecord> CELL;
        GRUPRecords<WRLDRecord> WRLD;
        GRUPRecords<DIALRecord> DIAL;
        GRUPRecords<QUSTRecord> QUST;
        GRUPRecords<IDLERecord> IDLE;
        GRUPRecords<PACKRecord> PACK;
        GRUPRecords<CSTYRecord> CSTY;
        GRUPRecords<LSCRRecord> LSCR;
        GRUPRecords<LVSPRecord> LVSP;
        GRUPRecords<ANIORecord> ANIO;
        GRUPRecords<WATRRecord> WATR;
        GRUPRecords<EFSHRecord> EFSH;

        ModFile(char *ModName, bool newFile=false, bool DummyLoad=false):m_region(NULL), fileBuffer(NULL), fileEnd(0), IsOpen(newFile),
                                                                         LoadedGRUPs(newFile), IsNew(newFile), IsDummy(DummyLoad), FileName(ModName), TES4(DummyLoad || newFile),
                                                                         FormIDHandler(ModName, TES4.MAST, TES4.HEDR.value.nextObject)
            {
            if(newFile || IsDummy)
                TES4.IsESM(_stricmp(".esm",ModName + strlen(ModName)-4) == 0);
            }
        ~ModFile()
            {
            delete m_region;
            delete []FileName;
            }

        int Open();
        int Close();
        int LoadTES4();
        int Load(boost::threadpool::pool &Threads, const bool &FullLoad);
        void CollapseFormIDs();
        void ExpandFormIDs();
        bool IsFake() {return IsDummy;}
        int Save(FileBuffer &buffer, bool CloseMod);
        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif
    };
