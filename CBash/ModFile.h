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
#include <boost/threadpool.hpp>

class ModFile
    {
    private:
        _FileHandler ReadHandler;
        time_t ModTime;
    public:
        ModFlags Settings;
        FormIDHandlerClass FormIDHandler;
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

        ModFile(char *ModName, ModFlags &_settings):Settings(_settings.GetFlagField()), FileName(ModName), TES4(_settings.IsNew || _settings.IsDummy),
                                                       FormIDHandler(ModName, TES4.MAST, TES4.HEDR.value.nextObject)
            {
            struct stat buf;
            if(stat(FileName, &buf) < 0)
                ModTime = 0;
            else
                ModTime = buf.st_mtime;

            if(Settings.IsNew || Settings.IsDummy)
                TES4.IsESM(_stricmp(".esm",ModName + strlen(ModName)-4) == 0);
            }
        ~ModFile()
            {
            delete []FileName;
            }
        bool operator <(ModFile &other)
            {
            if(TES4.IsESM())
                {
                if(other.TES4.IsESM())
                    {
                    if(ModTime == 0)
                        {
                        if(other.ModTime == 0)
                            return true;
                        return false;
                        }
                    if(other.ModTime == 0)
                        return true;
                    return ModTime < other.ModTime;
                    }
                return true;
                }
            if(other.TES4.IsESM())
                return false;
            //Esp's sort after esp's
            //Non-existent esps sort before existing esps
            //Non-existent esps retain their relative load order
            //Existing esps sort by modified date
            //New esps load last
            //if(lhs->Settings.IsNew)
            //    printf("New mod: %s\n", lhs->FileName);
            //if(rhs->Settings.IsNew)
            //    printf("New mod: %s\n", rhs->FileName);
            if(Settings.IsNew)
                {
                if(other.Settings.IsNew)
                    return true;
                return false;
                }
            if(other.Settings.IsNew)
                return false;
            if(ModTime == 0)
                {
                if(other.ModTime == 0)
                    return false;
                return true;
                }
            if(other.ModTime == 0)
                return false;
            return ModTime < other.ModTime;
            }
        bool operator >(ModFile &other)
            {
            return !(*this < other);
            }

        int Open();
        int Close();
        int LoadTES4();
        int Load(boost::threadpool::pool &Threads, const bool &FullLoad);
        bool IsEmpty() {return FormIDHandler.IsEmpty;}
        unsigned long GetNumRecords(const unsigned long &RecordType);
        Record * CreateRecord(const unsigned long &RecordType, char *RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreateRecordOptions &options);
        int CleanMasters();
        int Save(_FileHandler &SaveHandler, bool CloseMod);
        void VisitAllRecords(RecordOp &op);
        void VisitRecords(const unsigned long &TopRecordType, const unsigned long &RecordType, RecordOp &op, bool DeepVisit=false);
        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif
    };
