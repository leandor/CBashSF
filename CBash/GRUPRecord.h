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
// GRUPRecord.h
#include "Common.h"
#include "GenericRecord.h"
#include "Oblivion/Records/DIALRecord.h"
#include "Oblivion/Records/INFORecord.h"
#include "Oblivion/Records/CELLRecord.h"
#include "Oblivion/Records/ACRERecord.h"
#include "Oblivion/Records/ACHRRecord.h"
#include "Oblivion/Records/REFRRecord.h"
#include "Oblivion/Records/PGRDRecord.h"
#include "Oblivion/Records/WRLDRecord.h"
#include "Oblivion/Records/ROADRecord.h"
#include "Oblivion/Records/LANDRecord.h"
#include "FalloutNewVegas/Records/DIALRecord.h"
#include "FalloutNewVegas/Records/INFORecord.h"
#include "FalloutNewVegas/Records/CELLRecord.h"
#include "FalloutNewVegas/Records/ACHRRecord.h"
#include "FalloutNewVegas/Records/ACRERecord.h"
#include "FalloutNewVegas/Records/REFRRecord.h"
#include "FalloutNewVegas/Records/PGRERecord.h"
#include "FalloutNewVegas/Records/PMISRecord.h"
#include "FalloutNewVegas/Records/PBEARecord.h"
#include "FalloutNewVegas/Records/PFLARecord.h"
#include "FalloutNewVegas/Records/PCBERecord.h"
#include "FalloutNewVegas/Records/NAVMRecord.h"
#include "FalloutNewVegas/Records/WRLDRecord.h"
#include "FalloutNewVegas/Records/LANDRecord.h"
#include "Visitors.h"
#include <vector>
#include <math.h>
//#include <boost/threadpool.hpp>

//#include "mmgr.h"

template<class T>
class GRUPRecords
    {
    public:
        UINT32 stamp;
        bool SkimmedGRUP;
        std::vector<Record *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false) {}
        ~GRUPRecords()
            {
            for(UINT32 p = 0;p < Records.size(); p++)
                delete Records[p];
            }

        bool Skim(FileReader &reader, const UINT32 &gSize, RecordProcessor &processor, RecordOp &indexer)
            {
            if(SkimmedGRUP || gSize == 0)
                {
                printer("GRUPRecords::Skim: Error - Unable to load group in file \"%s\". The group has already been loaded or has a size of 0.\n", reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE);
                #endif
                return false;
                }
            SkimmedGRUP = true;
            Record * curRecord = NULL;
            //UINT32 recordType = 0;
            unsigned char *gEnd = reader.tell() + gSize - 20;
            UINT32 recordSize = 0;

            while(reader.tell() < gEnd){
                curRecord = new T(reader.tell() + 20);
                reader.skip(4); //reader.read(&recordType, 4);
                reader.read(&recordSize, 4);
                if(processor(curRecord))
                    {
                    indexer.Accept(curRecord);
                    Records.push_back(curRecord);
                    }
                reader.skip(recordSize);
                };
            if(Records.size())
                processor.IsEmpty(false);
            return true;
            }
        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            Record * curRecord = NULL;

            bool stop = false;

            if(RecordType != NULL && Records.size() > 0 && Records[0]->GetType() != RecordType)
                return false;
            for(UINT32 p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(RecordType == NULL || RecordType == curRecord->GetType())
                    {
                    stop = op.Accept(curRecord);
                    if(curRecord == NULL)
                        {
                        Records.erase(Records.begin() + p);
                        --p;
                        }
                    if(stop)
                        return stop;
                    }

                if(DeepVisit)
                    {
                    stop = curRecord->VisitSubRecords(RecordType, op);
                    if(stop)
                        return stop;
                    }
                }
            return stop;
            }
        UINT32 WriteGRUP(UINT32 TopLabel, FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            UINT32 numRecords = (UINT32)Records.size();
            if(numRecords == 0)
                return 0;
            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 TopSize = 0;
            UINT32 formCount = 0;

            //Top GRUP Header
            writer.file_write(&type, 4);
            UINT32 TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numRecords;
            for(UINT32 p = 0; p < numRecords; p++)
                {
                TopSize += Records[p]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                if(CloseMod)
                    delete Records[p];
                }
            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                Records.clear();
            return formCount;
            }

    };

template<>
class GRUPRecords<DIALRecord>
    {
    public:
        UINT32 stamp;
        bool SkimmedGRUP;
        std::vector<Record *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false) {}
        ~GRUPRecords()
            {
            for(UINT32 p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(FileReader &reader, const UINT32 &gSize, RecordProcessor &processor, RecordOp &indexer)
            {
            if(SkimmedGRUP || gSize == 0)
                {
                printer("GRUPRecords<DIALRecord>::Skim: Error - Unable to load group in file \"%s\". The group has already been loaded or has a size of 0.\n", reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE);
                #endif
                return false;
                }
            SkimmedGRUP = true;
            Record *curDIALRecord = NULL, *curRecord = NULL, *orphans = NULL;
            UINT32 recordType = 0;
            unsigned char *gEnd = reader.tell() + gSize - 20;
            UINT32 recordSize = 0;

            curDIALRecord = orphans = new DIALRecord();
            while(reader.tell() < gEnd){
                reader.read(&recordType, 4);
                reader.read(&recordSize, 4);
                switch(recordType)
                    {
                    case REV32(DIAL):
                        curDIALRecord = new DIALRecord(reader.tell() + 12);
                        if(processor(curDIALRecord))
                            {
                            indexer.Accept(curDIALRecord);
                            Records.push_back(curDIALRecord);
                            }
                        break;
                    case REV32(GRUP): //All GRUPs will be recreated from scratch on write (saves memory)
                        reader.skip(8); //Skip label and type fields
                        reader.read(&stamp, 4);
                        continue;
                    case REV32(INFO):
                        curRecord = new INFORecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            ((DIALRecord *)curDIALRecord)->INFO.push_back(curRecord);
                            }
                        break;
                    default:
                        printer("GRUPRecords<DIALRecord>::Skim: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((STRING)&recordType)[0], ((STRING)&recordType)[1], ((STRING)&recordType)[2], ((STRING)&recordType)[3], reader.getFileName());
                        #ifdef CBASH_DEBUG_CHUNK
                            reader.peek_around(PEEK_SIZE);
                        #endif
                        break;
                    }
                reader.skip(recordSize);
                };
            if(Records.size())
                processor.IsEmpty(false);

            for(UINT32 x = 0; x < ((DIALRecord *)orphans)->INFO.size(); ++x)
                {
                printer("GRUPRecords<DIALRecord>::Skim: Warning - Parsing error. Skipped orphan INFO (%08X) at %08X in file \"%s\"\n", ((DIALRecord *)orphans)->INFO[x]->formID, ((DIALRecord *)orphans)->INFO[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, ((DIALRecord *)orphans)->INFO[x]->recData);
                #endif
                }
            delete orphans;
            return true;
            }
        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            Record * curRecord = NULL;
            bool stop = false;

            if(RecordType != NULL && RecordType != REV32(DIAL) && RecordType != REV32(INFO))
                return false;

            for(UINT32 p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(RecordType == NULL || RecordType == curRecord->GetType())
                    {
                    stop = op.Accept(curRecord);
                    if(curRecord == NULL)
                        {
                        Records.erase(Records.begin() + p);
                        --p;
                        }
                    if(stop)
                        return stop;
                    }

                if(DeepVisit)
                    {
                    stop = curRecord->VisitSubRecords(RecordType, op);
                    if(stop)
                        return stop;
                    }
                }
            return stop;
            }
        UINT32 WriteGRUP(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            UINT32 numDIALRecords = (UINT32)Records.size(); //Parent Records
            if(numDIALRecords == 0)
                return 0;
            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 TopSize =0;
            UINT32 ChildrenSize =0;
            UINT32 formCount = 0;
            UINT32 TopLabel = REV32(DIAL);
            UINT32 numINFORecords = 0;
            UINT32 parentFormID = 0;
            DIALRecord *curRecord = NULL;

            //Top GRUP Header
            writer.file_write(&type, 4);
            UINT32 TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            gType = eTopicChildren;
            formCount += numDIALRecords;
            for(UINT32 p = 0; p < numDIALRecords; ++p)
                {
                curRecord = (DIALRecord *)Records[p];
                parentFormID = curRecord->formID;
                collapser.Accept(parentFormID);
                TopSize += curRecord->Write(writer, bMastersChanged, expander, collapser, Expanders);

                numINFORecords = (UINT32)curRecord->INFO.size();
                if(numINFORecords)
                    {
                    writer.file_write(&type, 4);
                    UINT32 ChildrenSizePos = writer.file_tell();
                    writer.file_write(&ChildrenSize, 4); //Placeholder: will be overwritten with correct value later.
                    writer.file_write(&parentFormID, 4);
                    writer.file_write(&gType, 4);
                    writer.file_write(&stamp, 4);
                    ++formCount;
                    ChildrenSize = 20;

                    formCount += numINFORecords;
                    for(UINT32 y = 0; y < curRecord->INFO.size(); ++y)
                        {
                        ChildrenSize += curRecord->INFO[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                        if(CloseMod)
                            delete curRecord->INFO[y];
                        }
                    writer.file_write(ChildrenSizePos, &ChildrenSize, 4);
                    TopSize += ChildrenSize;
                    if(CloseMod)
                        curRecord->INFO.clear();
                    }
                if(CloseMod)
                    delete curRecord;
                }
            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                Records.clear();
            return formCount;
            }

    };

template<>
class GRUPRecords<CELLRecord>
    {
    public:
        UINT32 stamp;
        bool SkimmedGRUP;
        std::vector<Record *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false) {}
        ~GRUPRecords()
            {
            for(UINT32 p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(FileReader &reader, const UINT32 &gSize, RecordProcessor &processor, RecordOp &indexer)
            {
            if(SkimmedGRUP || gSize == 0)
                {
                printer("GRUPRecords<CELLRecord>::Skim: Error - Unable to load group in file \"%s\". The group has already been loaded or has a size of 0.\n", reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE);
                #endif
                return false;
                }
            SkimmedGRUP = true;
            Record *curCELLRecord = NULL, *curRecord = NULL, *orphans = NULL;
            UINT32 recordType = 0;
            unsigned char *gEnd = reader.tell() + gSize - 20;
            UINT32 recordSize = 0;

            curCELLRecord = orphans = new CELLRecord();
            while(reader.tell() < gEnd){
                reader.read(&recordType, 4);
                reader.read(&recordSize, 4);
                switch(recordType)
                    {
                    case REV32(CELL):
                        curCELLRecord = new CELLRecord(reader.tell() + 12);
                        if(processor(curCELLRecord))
                            {
                            indexer.Accept(curCELLRecord);
                            Records.push_back(curCELLRecord);
                            }
                        break;
                    case REV32(GRUP): //All GRUPs will be recreated from scratch on write (saves memory)
                        reader.skip(12); //skip the rest of the header
                        continue;
                    case REV32(ACHR):
                        curRecord = new ACHRRecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            ((CELLRecord *)curCELLRecord)->ACHR.push_back(curRecord);
                            }
                        break;
                    case REV32(ACRE):
                        curRecord = new ACRERecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            ((CELLRecord *)curCELLRecord)->ACRE.push_back(curRecord);
                            }
                        break;
                    case REV32(REFR):
                        curRecord = new REFRRecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            ((CELLRecord *)curCELLRecord)->REFR.push_back(curRecord);
                            }
                        break;
                    case REV32(PGRD):
                        curRecord = new PGRDRecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            if(curCELLRecord == orphans)
                                {
                                printer("GRUPRecords<CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PGRD (%08X) at %08X in file \"%s\"\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName());
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else if(((CELLRecord *)curCELLRecord)->PGRD != NULL)
                                {
                                printer("GRUPRecords<CELLRecord>::Skim: Warning - Parsing error. Skipped extra PGRD (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has PGRD (%08X)\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName(), curCELLRecord->formID, ((CELLRecord *)curCELLRecord)->PGRD->formID);
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else
                                {
                                indexer.Accept(curRecord);
                                ((CELLRecord *)curCELLRecord)->PGRD = curRecord;
                                }
                            }
                        break;
                    default:
                        printer("GRUPRecords<CELLRecord>::Skim: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((STRING)&recordType)[0], ((STRING)&recordType)[1], ((STRING)&recordType)[2], ((STRING)&recordType)[3], reader.getFileName());
                        #ifdef CBASH_DEBUG_CHUNK
                            reader.peek_around(PEEK_SIZE);
                        #endif
                        break;
                    }
                reader.skip(recordSize);
                };
            if(Records.size())
                processor.IsEmpty(false);

            for(UINT32 x = 0; x < ((CELLRecord *)orphans)->ACHR.size(); ++x)
                {
                printer("GRUPRecords<CELLRecord>::Skim: Warning - Parsing error. Skipped orphan ACHR (%08X) at %08X in file \"%s\"\n", ((CELLRecord *)orphans)->ACHR[x]->formID, ((CELLRecord *)orphans)->ACHR[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, ((CELLRecord *)orphans)->ACHR[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < ((CELLRecord *)orphans)->ACRE.size(); ++x)
                {
                printer("GRUPRecords<CELLRecord>::Skim: Warning - Parsing error. Skipped orphan ACRE (%08X) at %08X in file \"%s\"\n", ((CELLRecord *)orphans)->ACRE[x]->formID, ((CELLRecord *)orphans)->ACRE[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, ((CELLRecord *)orphans)->ACRE[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < ((CELLRecord *)orphans)->REFR.size(); ++x)
                {
                printer("GRUPRecords<CELLRecord>::Skim: Warning - Parsing error. Skipped orphan REFR (%08X) at %08X in file \"%s\"\n", ((CELLRecord *)orphans)->REFR[x]->formID, ((CELLRecord *)orphans)->REFR[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, ((CELLRecord *)orphans)->REFR[x]->recData);
                #endif
                }
            delete orphans;
            return true;
            }
        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            Record * curRecord = NULL;
            bool stop = false;

            if(RecordType != NULL && RecordType != REV32(CELL) && RecordType != REV32(PGRD) && RecordType != REV32(LAND) && RecordType != REV32(REFR) && RecordType != REV32(ACHR) && RecordType != REV32(ACRE))
                return false;

            for(UINT32 p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(RecordType == NULL || RecordType == curRecord->GetType())
                    {
                    stop = op.Accept(curRecord);
                    if(curRecord == NULL)
                        {
                        Records.erase(Records.begin() + p);
                        --p;
                        }
                    if(stop)
                        return stop;
                    }

                if(DeepVisit)
                    {
                    stop = curRecord->VisitSubRecords(RecordType, op);
                    if(stop)
                        return stop;
                    }
                }
            return stop;
            }
        UINT32 WriteGRUP(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            UINT32 numCELLRecords = (UINT32)Records.size();
            if(numCELLRecords == 0)
                return 0;
            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 TopSize = 0;
            UINT32 TopSizePos = 0;
            UINT32 blockSize = 0;
            UINT32 blockSizePos = 0;
            UINT32 subBlockSize = 0;
            UINT32 subBlockSizePos = 0;
            UINT32 childrenSize = 0;
            UINT32 childrenSizePos = 0;
            UINT32 childSize = 0;
            UINT32 childSizePos = 0;

            UINT32 formCount = 0;

            UINT32 gLabel = REV32(CELL);
            UINT32 numSubBlocks = 0;
            UINT32 numChildren = 0;
            UINT32 numChild = 0;

            UINT32 parentFormID = 0;
            CELLRecord *curRecord = NULL;
            int ObjectID, BlockIndex, SubBlockIndex;

            std::vector< std::vector< std::vector<CELLRecord *> > > BlockedRecords(10, std::vector< std::vector<CELLRecord *> > (10, std::vector<CELLRecord *>()));
            std::vector<Record *> Persistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;
            BlockedRecords.reserve(numCELLRecords);
            for(UINT32 p = 0; p < numCELLRecords; ++p)
                {
                curRecord = (CELLRecord *)Records[p];

                ObjectID = curRecord->formID & 0x00FFFFFF;
                BlockIndex = ObjectID % 10;
                SubBlockIndex = (ObjectID / 10) % 10;

                BlockedRecords[BlockIndex][SubBlockIndex].push_back(curRecord);
                }

            //Top GRUP Header
            writer.file_write(&type, 4);
            TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&gLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numCELLRecords;
            for(UINT32 curBlock = 0; curBlock < 10; ++curBlock)
                {
                gType = eInteriorBlock;
                for(UINT32 curSubBlock = 0; curSubBlock < 10; ++curSubBlock)
                    {
                    numSubBlocks = (UINT32)BlockedRecords[curBlock][curSubBlock].size();
                    if(numSubBlocks != 0)
                        {
                        if(gType == eInteriorBlock)
                            {
                            writer.file_write(&type, 4);
                            blockSizePos = writer.file_tell();
                            writer.file_write(&blockSizePos, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&curBlock, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            ++formCount;
                            blockSize = 20;
                            }
                        gType = eInteriorSubBlock;
                        writer.file_write(&type, 4);
                        subBlockSizePos = writer.file_tell();
                        writer.file_write(&subBlockSize, 4); //Placeholder: will be overwritten with correct value later.
                        writer.file_write(&curSubBlock, 4);
                        writer.file_write(&gType, 4);
                        writer.file_write(&stamp, 4);
                        ++formCount;
                        subBlockSize = 20;
                        for(UINT32 p = 0; p < numSubBlocks; ++p)
                            {
                            curRecord = BlockedRecords[curBlock][curSubBlock][p];
                            parentFormID = curRecord->formID;
                            collapser.Accept(parentFormID);
                            subBlockSize += curRecord->Write(writer, bMastersChanged, expander, collapser, Expanders);
                            //Place the PGRD, ACHR, ACRE, and REFR records into their proper GRUP
                            if(curRecord->PGRD != NULL)
                                Temporary.push_back(curRecord->PGRD);
                            if(CloseMod)
                                curRecord->PGRD = NULL;

                            for(UINT32 y = 0; y < curRecord->ACHR.size(); ++y)
                                {
                                if(curRecord->ACHR[y]->IsPersistent())
                                    Persistent.push_back(curRecord->ACHR[y]);
                                else if(curRecord->ACHR[y]->IsVWD())
                                    VWD.push_back(curRecord->ACHR[y]);
                                else
                                    Temporary.push_back(curRecord->ACHR[y]);
                                }
                            if(CloseMod)
                                curRecord->ACHR.clear();

                            for(UINT32 y = 0; y < curRecord->ACRE.size(); ++y)
                                {
                                if(curRecord->ACRE[y]->IsPersistent())
                                    Persistent.push_back(curRecord->ACRE[y]);
                                else if(curRecord->ACRE[y]->IsVWD())
                                    VWD.push_back(curRecord->ACRE[y]);
                                else
                                    Temporary.push_back(curRecord->ACRE[y]);
                                }
                            if(CloseMod)
                                curRecord->ACRE.clear();

                            for(UINT32 y = 0; y < curRecord->REFR.size(); ++y)
                                {
                                if(curRecord->REFR[y]->IsPersistent())
                                    Persistent.push_back(curRecord->REFR[y]);
                                else if(curRecord->REFR[y]->IsVWD())
                                    VWD.push_back(curRecord->REFR[y]);
                                else
                                    Temporary.push_back(curRecord->REFR[y]);
                                }
                            if(CloseMod)
                                curRecord->REFR.clear();

                            numChildren = (UINT32)Persistent.size() + (UINT32)VWD.size() + (UINT32)Temporary.size();
                            if(numChildren)
                                {
                                formCount += numChildren;
                                gType = eCellChildren;
                                writer.file_write(&type, 4);
                                childrenSizePos = writer.file_tell();
                                writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                                writer.file_write(&parentFormID, 4);
                                writer.file_write(&gType, 4);
                                writer.file_write(&stamp, 4);
                                ++formCount;
                                childrenSize = 20;

                                numChild = (UINT32)Persistent.size();
                                if(numChild)
                                    {
                                    gType = eCellPersistent;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(UINT32 x = 0; x < numChild; ++x)
                                        {
                                        childSize += Persistent[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                        if(CloseMod)
                                            delete Persistent[x];
                                        }
                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    Persistent.clear();
                                    }

                                numChild = (UINT32)VWD.size();
                                if(numChild)
                                    {
                                    gType = eCellVWD;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(UINT32 x = 0; x < numChild; ++x)
                                        {
                                        childSize += VWD[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                        if(CloseMod)
                                            delete VWD[x];
                                        }
                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    VWD.clear();
                                    }

                                numChild = (UINT32)Temporary.size();
                                if(numChild)
                                    {
                                    gType = eCellTemporary;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(UINT32 x = 0; x < numChild; ++x)
                                        {
                                        childSize += Temporary[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                        if(CloseMod)
                                            delete Temporary[x];
                                        }
                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    Temporary.clear();
                                    }
                                subBlockSize += childrenSize;
                                writer.file_write(childrenSizePos, &childrenSize, 4);
                                }
                            if(CloseMod)
                                delete curRecord;
                            }
                        blockSize += subBlockSize;
                        writer.file_write(subBlockSizePos, &subBlockSize, 4);
                        BlockedRecords[curBlock][curSubBlock].clear();
                        }
                    }
                if(gType != eInteriorBlock)
                    {
                    TopSize += blockSize;
                    writer.file_write(blockSizePos, &blockSize, 4);
                    }
                BlockedRecords[curBlock].clear();
                }
            if(CloseMod)
                Records.clear();
            writer.file_write(TopSizePos, &TopSize, 4);
            BlockedRecords.clear();
            return formCount;
            }

    };

template<>
class GRUPRecords<WRLDRecord>
    {
    public:
        UINT32 stamp;
        bool SkimmedGRUP;
        std::vector<Record *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false) {}
        ~GRUPRecords()
            {
            for(UINT32 p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(FileReader &reader, const UINT32 &gSize, RecordProcessor &processor, RecordOp &indexer, RecordOp &fullReader)
            {
            if(SkimmedGRUP || gSize == 0)
                {
                printer("GRUPRecords<WRLDRecord>::Skim: Error - Unable to load group in file \"%s\". The group has already been loaded or has a size of 0.\n", reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE);
                #endif
                return false;
                }
            SkimmedGRUP = true;
            Record *curWRLDRecord = NULL, *curCELLRecord = NULL, *curRecord = NULL, *orphans = NULL;

            std::map<SINT32, std::map<SINT32, LANDRecord *> > GridXY_LAND;
            std::vector<std::pair<UINT32, unsigned char *> > GRUPs;
            std::pair<UINT32, unsigned char *> GRUP_End;
            UINT32 recordType = 0;
            unsigned char *gEnd = reader.tell() + gSize - 20;
            GRUP_End.first = eTop;
            GRUP_End.second = gEnd;
            GRUPs.push_back(GRUP_End);
            UINT32 recordSize = 0;

            curCELLRecord = orphans = new CELLRecord();
            while(reader.tell() < gEnd){
                while(reader.tell() >= GRUP_End.second)
                    {
                    //Better tracking of the last GRUP
                    //Mainly fixes cases where the world cell isn't located before the cell blocks
                    //One example of this is Windfall.esp
                    GRUPs.pop_back();
                    GRUP_End = GRUPs.back();
                    };
                reader.read(&recordType, 4);
                reader.read(&recordSize, 4);
                switch(recordType)
                    {
                    case REV32(WRLD):
                        curWRLDRecord = new WRLDRecord(reader.tell() + 12);
                        if(processor(curWRLDRecord))
                            {
                            indexer.Accept(curWRLDRecord);
                            Records.push_back(curWRLDRecord);
                            }
                        break;
                    case REV32(CELL):
                        curCELLRecord = new CELLRecord(reader.tell() + 12);
                        if(processor(curCELLRecord))
                            {
                            ((CELLRecord *)curCELLRecord)->Parent = curWRLDRecord;
                            switch(GRUP_End.first)
                                {
                                case eWorld:
                                    if(curWRLDRecord == NULL)
                                        {
                                        printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped orphan World CELL (%08X) at %08X in file \"%s\"\n", curCELLRecord->formID, reader.tell() - reader.start(), reader.getFileName());
                                        delete curCELLRecord;
                                        #ifdef CBASH_DEBUG_CHUNK
                                            reader.peek_around(PEEK_SIZE);
                                        #endif
                                        }
                                    else if(((WRLDRecord *)curWRLDRecord)->CELL != NULL)
                                        {
                                        printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped extra World CELL (%08X) at %08X in file \"%s\"\n  WRLD (%08X) already has CELL (%08X)\n", curCELLRecord->formID, reader.tell() - reader.start(), reader.getFileName(), curWRLDRecord->formID, ((WRLDRecord *)curWRLDRecord)->CELL->formID);
                                        delete curCELLRecord;
                                        #ifdef CBASH_DEBUG_CHUNK
                                            reader.peek_around(PEEK_SIZE);
                                        #endif
                                        }
                                    else
                                        {
                                        indexer.Accept(curCELLRecord);
                                        ((WRLDRecord *)curWRLDRecord)->CELL = curCELLRecord;
                                        }
                                    break;
                                default:
                                    indexer.Accept(curCELLRecord);
                                    ((WRLDRecord *)curWRLDRecord)->CELLS.push_back(curCELLRecord);
                                    break;
                                }
                            }
                        break;
                    case REV32(GRUP): //All GRUPs will be recreated from scratch on write (saves memory)
                        reader.skip(4);
                        reader.read(&GRUP_End.first, 4);
                        reader.skip(4);
                        GRUP_End.second = reader.tell() + recordSize - 20;
                        GRUPs.push_back(GRUP_End);
                        continue;
                    case REV32(ROAD):
                        curRecord = new ROADRecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            if(curWRLDRecord == NULL)
                                {
                                printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped orphan ROAD (%08X) at %08X in file \"%s\"\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName());
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else if(((WRLDRecord *)curWRLDRecord)->ROAD != NULL)
                                {
                                printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped extra ROAD (%08X) at %08X in file \"%s\"\n  WRLD (%08X) already has ROAD (%08X)\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName(), curWRLDRecord->formID, ((WRLDRecord *)curWRLDRecord)->ROAD->formID);
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else
                                {
                                indexer.Accept(curRecord);
                                ((WRLDRecord *)curWRLDRecord)->ROAD = curRecord;
                                }
                            }
                        break;
                    case REV32(LAND):
                        curRecord = new LANDRecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            if(curCELLRecord == orphans)
                                {
                                printer("GRUPRecords<CELLRecord>::Skim: Warning - Parsing error. Skipped orphan LAND (%08X) at %08X in file \"%s\"\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName());
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else if(((CELLRecord *)curCELLRecord)->LAND != NULL)
                                {
                                printer("GRUPRecords<CELLRecord>::Skim: Warning - Parsing error. Skipped extra LAND (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has LAND (%08X)\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName(), curCELLRecord->formID, ((CELLRecord *)curCELLRecord)->LAND->formID);
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else
                                {
                                indexer.Accept(curRecord);
                                ((CELLRecord *)curCELLRecord)->LAND = curRecord;
                                if(processor.Flags.IsIndexLANDs)
                                    {
                                    fullReader.Accept(curCELLRecord); //may already be loaded, but just to be sure.
                                    //CELL will be unloaded if needed after a second round of indexing when all records are loaded
                                    ((CELLRecord *)curCELLRecord)->XCLC.Load();
                                    GridXY_LAND[((CELLRecord *)curCELLRecord)->XCLC->posX][((CELLRecord *)curCELLRecord)->XCLC->posY] = (LANDRecord *)curRecord;
                                    }
                                }
                            }
                        break;
                    case REV32(PGRD):
                        curRecord = new PGRDRecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            if(curCELLRecord == orphans)
                                {
                                printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped orphan PGRD (%08X) at %08X in file \"%s\"\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName());
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else if(((CELLRecord *)curCELLRecord)->PGRD != NULL)
                                {
                                printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped extra PGRD (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has PGRD (%08X)\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName(), curCELLRecord->formID, ((CELLRecord *)curCELLRecord)->PGRD->formID);
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else
                                {
                                indexer.Accept(curRecord);
                                ((CELLRecord *)curCELLRecord)->PGRD = curRecord;
                                }
                            }
                        break;
                    case REV32(ACHR):
                        curRecord = new ACHRRecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            ((CELLRecord *)curCELLRecord)->ACHR.push_back(curRecord);
                            }
                        break;
                    case REV32(ACRE):
                        curRecord = new ACRERecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            ((CELLRecord *)curCELLRecord)->ACRE.push_back(curRecord);
                            }
                        break;
                    case REV32(REFR):
                        curRecord = new REFRRecord(reader.tell() + 12);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            ((CELLRecord *)curCELLRecord)->REFR.push_back(curRecord);
                            }
                        break;
                    default:
                        printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((STRING)&recordType)[0], ((STRING)&recordType)[1], ((STRING)&recordType)[2], ((STRING)&recordType)[3], reader.getFileName());
                        #ifdef CBASH_DEBUG_CHUNK
                            reader.peek_around(PEEK_SIZE);
                        #endif
                        break;
                    }
                reader.skip(recordSize);
                };

            //Index LAND records by grid
            //There might be ACHR, ACRE, or REFR records in the World CELL
            if(processor.Flags.IsIndexLANDs || processor.Flags.IsFixupPlaceables)
                {
                SINT32 posX = 0, posY = 0;
                SINT32 gridX = 0, gridY = 0;
                WRLDRecord *curWRLD = NULL;
                CELLRecord *curCELL = NULL, *curWRLDCELL = NULL;
                LANDRecord *curLAND = NULL;
                for(UINT32 x = 0; x < Records.size(); ++x)
                    {
                    curWRLD = (WRLDRecord *)Records[x];
                    for(UINT32 y = 0; y < curWRLD->CELLS.size(); ++y)
                        {
                        curCELL = (CELLRecord *)curWRLD->CELLS[y];
                        //reader.Accept((Record **)&curCELL); //already read when loaded
                        //curCELLRecord->XCLC.Load();  //already loaded when CELL loaded
                        posX = curCELL->XCLC->posX;
                        posY = curCELL->XCLC->posY;

                        curWRLDCELL = (CELLRecord *)curWRLD->CELL;
                        if(processor.Flags.IsFixupPlaceables && curWRLDCELL != NULL)
                            {
                            for(UINT32 x = 0; x < curWRLDCELL->ACHR.size();)
                                {
                                //Have to test each record to see if it belongs to the cell. This is determined by its positioning.
                                curRecord = curWRLDCELL->ACHR[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((ACHRRecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((ACHRRecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    //For easier use later on, go ahead and move it to the parent cell.
                                    //It will get moved back later during the save process if need be.
                                    curCELL->ACHR.push_back(curRecord);
                                    curWRLDCELL->ACHR.erase(curWRLDCELL->ACHR.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->ACRE.size();)
                                {
                                curRecord = curWRLDCELL->ACRE[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((ACRERecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((ACRERecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->ACRE.push_back(curRecord);
                                    curWRLDCELL->ACRE.erase(curWRLDCELL->ACRE.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->REFR.size();)
                                {
                                curRecord = curWRLDCELL->REFR[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((REFRRecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((REFRRecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->REFR.push_back(curRecord);
                                    curWRLDCELL->REFR.erase(curWRLDCELL->REFR.begin() + x);
                                    }
                                else ++x;
                                }
                            }

                        if(processor.Flags.IsIndexLANDs)
                            {
                            curLAND = (LANDRecord *)curCELL->LAND;
                            if(curLAND != NULL)
                                {
                                curLAND->NorthLand = GridXY_LAND[posX][posY + 1];
                                curLAND->SouthLand = GridXY_LAND[posX][posY - 1];
                                curLAND->EastLand = GridXY_LAND[posX + 1][posY];
                                curLAND->WestLand = GridXY_LAND[posX - 1][posY];
                                }
                            }

                        if(processor.Flags.IsMinLoad)
                            curCELL->Unload();
                        }
                    }
                }

            if(Records.size())
                processor.IsEmpty(false);

            for(UINT32 x = 0; x < ((CELLRecord *)orphans)->ACHR.size(); ++x)
                {
                printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped orphan ACHR (%08X) at %08X in file \"%s\"\n", ((CELLRecord *)orphans)->ACHR[x]->formID, ((CELLRecord *)orphans)->ACHR[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, ((CELLRecord *)orphans)->ACHR[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < ((CELLRecord *)orphans)->ACRE.size(); ++x)
                {
                printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped orphan ACRE (%08X) at %08X in file \"%s\"\n", ((CELLRecord *)orphans)->ACRE[x]->formID, ((CELLRecord *)orphans)->ACRE[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, ((CELLRecord *)orphans)->ACRE[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < ((CELLRecord *)orphans)->REFR.size(); ++x)
                {
                printer("GRUPRecords<WRLDRecord>::Skim: Warning - Parsing error. Skipped orphan REFR (%08X) at %08X in file \"%s\"\n", ((CELLRecord *)orphans)->REFR[x]->formID, ((CELLRecord *)orphans)->REFR[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, ((CELLRecord *)orphans)->REFR[x]->recData);
                #endif
                }
            delete orphans;

            return true;
            }
        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            Record *curRecord = NULL;
            bool stop = false;

            if(RecordType != NULL && RecordType != REV32(WRLD) &&
                RecordType != REV32(ROAD) && RecordType != REV32(CELL) &&
                RecordType != REV32(PGRD) && RecordType != REV32(LAND) &&
                RecordType != REV32(REFR) && RecordType != REV32(ACHR) &&
                RecordType != REV32(ACRE))
                {
                return false;
                }

            for(UINT32 p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(RecordType == NULL || RecordType == curRecord->GetType())
                    {
                    stop = op.Accept(curRecord);
                    if(curRecord == NULL)
                        {
                        Records.erase(Records.begin() + p);
                        --p;
                        }
                    if(stop)
                        return stop;
                    }

                if(DeepVisit)
                    {
                    stop = curRecord->VisitSubRecords(RecordType, op);
                    if(stop)
                        return stop;
                    }
                }
            return stop;
            }
        UINT32 WriteGRUP(FileWriter &writer, FormIDHandlerClass &FormIDHandler, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            UINT32 numWrldRecords = (UINT32)Records.size();
            if(numWrldRecords == 0)
                return 0;
            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 gLabel = REV32(WRLD);
            UINT32 TopSize = 0;
            UINT32 TopSizePos = 0;
            UINT32 worldSize = 0;
            UINT32 worldSizePos = 0;
            UINT32 blockSize = 0;
            UINT32 blockSizePos = 0;
            UINT32 subBlockSize = 0;
            UINT32 subBlockSizePos = 0;
            UINT32 childrenSize = 0;
            UINT32 childrenSizePos = 0;
            UINT32 childSize = 0;
            UINT32 childSizePos = 0;

            UINT32 formCount = 0;

            UINT32 numCellRecords = 0;
            UINT32 numSubBlocks = 0;
            UINT32 numChildren = 0;
            UINT32 numChild = 0;

            WRLDRecord *curWorld = NULL;
            CELLRecord *curCell = NULL;
            CELLRecord *curWorldCell = NULL;
            UINT32 worldFormID = 0;
            UINT32 cellFormID = 0;
            int gridX, gridY;
            UINT32 BlockIndex, SubBlockIndex;

            std::map<UINT32, std::map<UINT32, std::vector<CELLRecord *> > > BlockedRecords;
            std::vector<Record *> Persistent;
            std::vector<Record *> FixedPersistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;

            //Top GRUP Header
            writer.file_write(&type, 4);
            TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&gLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numWrldRecords;
            for(UINT32 x = 0; x < numWrldRecords; ++x)
                {
                curWorld = (WRLDRecord *)Records[x];
                worldFormID = curWorld->formID;
                collapser.Accept(worldFormID);
                TopSize += curWorld->Write(writer, bMastersChanged, expander, collapser, Expanders);

                curWorldCell = (CELLRecord *)curWorld->CELL;

                numCellRecords = (UINT32)curWorld->CELLS.size();
                for(UINT32 p = 0; p < numCellRecords; ++p)
                    {
                    curCell = (CELLRecord *)curWorld->CELLS[p];

                    //All persistent references must be moved to the world cell
                    for(UINT32 y = 0; y < curCell->ACRE.size(); ++y)
                        if(curCell->ACRE[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->ACRE[y]);

                    for(UINT32 y = 0; y < curCell->ACHR.size(); ++y)
                        if(curCell->ACHR[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->ACHR[y]);

                    for(UINT32 y = 0; y < curCell->REFR.size(); ++y)
                        if(curCell->REFR[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->REFR[y]);

                    if(curCell->Read())
                        curCell->VisitFormIDs(expander);
                    curCell->XCLC.Load();
                    gridX = (int)floor(curCell->XCLC->posX / 8.0);
                    gridY = (int)floor(curCell->XCLC->posY / 8.0);
                    if(!curCell->IsChanged())
                        curCell->Unload();
                    SubBlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                    gridX = (int)floor(gridX / 4.0);
                    gridY = (int)floor(gridY / 4.0);
                    BlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);

                    BlockedRecords[BlockIndex][SubBlockIndex].push_back(curCell);
                    }

                if(curWorldCell == NULL && FixedPersistent.size()) //create a default dummy cell for persistents
                    {
                    curWorldCell = new CELLRecord();
                    curWorldCell->formID = FormIDHandler.NextExpandedFormID();
                    curWorldCell->Parent = curWorld;
                    curWorldCell->IsHasWater(true);
                    curWorldCell->IsPersistent(true);
                    curWorldCell->XCLC.Load();
                    }

                if(curWorld->ROAD != NULL || curWorldCell != NULL || curWorld->CELLS.size() > 0)
                    {
                    gType = eWorld;
                    writer.file_write(&type, 4);
                    worldSizePos = writer.file_tell();
                    writer.file_write(&worldSize, 4); //Placeholder: will be overwritten with correct value later.
                    writer.file_write(&worldFormID, 4);
                    writer.file_write(&gType, 4);
                    writer.file_write(&stamp, 4);
                    ++formCount;
                    worldSize = 20;

                    if(curWorld->ROAD != NULL)
                        {
                        worldSize += curWorld->ROAD->Write(writer, bMastersChanged, expander, collapser, Expanders);
                        ++formCount;
                        if(CloseMod)
                            {
                            delete curWorld->ROAD;
                            curWorld->ROAD = NULL;
                            }
                        }

                    if(curWorldCell != NULL)
                        {
                        curCell = curWorldCell;
                        cellFormID = curCell->formID;
                        collapser.Accept(cellFormID);
                        worldSize += curCell->Write(writer, bMastersChanged, expander, collapser, Expanders);
                        ++formCount;

                        if(curCell->LAND != NULL)
                            Temporary.push_back(curCell->LAND);
                        if(CloseMod)
                            curCell->LAND = NULL;

                        if(curCell->PGRD != NULL)
                            Temporary.push_back(curCell->PGRD);
                        if(CloseMod)
                            curCell->PGRD = NULL;

                        for(UINT32 y = 0; y < curCell->ACHR.size(); ++y)
                            {
                            if(curCell->ACHR[y]->IsPersistent())
                                Persistent.push_back(curCell->ACHR[y]);
                            else if(curCell->ACHR[y]->IsVWD())
                                {
                                VWD.push_back(curCell->ACHR[y]);
                                delete curCell->ACHR[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->ACHR[y]);
                                delete curCell->ACHR[y];
                                }
                            }
                        if(CloseMod)
                            curCell->ACHR.clear();

                        for(UINT32 y = 0; y < curCell->ACRE.size(); ++y)
                            {
                            if(curCell->ACRE[y]->IsPersistent())
                                Persistent.push_back(curCell->ACRE[y]);
                            else if(curCell->ACRE[y]->IsVWD())
                                {
                                VWD.push_back(curCell->ACRE[y]);
                                delete curCell->ACRE[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->ACRE[y]);
                                delete curCell->ACRE[y];
                                }
                            }
                        if(CloseMod)
                            curCell->ACRE.clear();

                        for(UINT32 y = 0; y < curCell->REFR.size(); ++y)
                            {
                            if(curCell->REFR[y]->IsPersistent())
                                Persistent.push_back(curCell->REFR[y]);
                            else if(curCell->REFR[y]->IsVWD())
                                {
                                VWD.push_back(curCell->REFR[y]);
                                delete curCell->REFR[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->REFR[y]);
                                delete curCell->REFR[y];
                                }
                            }
                        if(CloseMod)
                            curCell->REFR.clear();

                        if(VWD.size() || Temporary.size())
                            printer("GRUPRecords<WRLDRecord>::WriteGRUP: Warning - Information lost. Ignored %u VWD or Temporary records in the world cell: %08X", VWD.size() + Temporary.size(), worldFormID);

                        VWD.clear();
                        Temporary.clear();

                        numChildren = (UINT32)Persistent.size() + (UINT32)FixedPersistent.size();
                        if(numChildren)
                            {
                            formCount += numChildren;
                            gType = eCellChildren;
                            writer.file_write(&type, 4);
                            childrenSizePos = writer.file_tell();
                            writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&cellFormID, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            ++formCount;
                            childrenSize = 20;

                            //World CELL should only have persistent objects in it
                            gType = eCellPersistent;
                            writer.file_write(&type, 4);
                            childSizePos = writer.file_tell();
                            writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&cellFormID, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            ++formCount;
                            childSize = 20;

                            numChild = (UINT32)Persistent.size();
                            for(UINT32 y = 0; y < numChild; ++y)
                                {
                                childSize += Persistent[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                if(CloseMod)
                                    delete Persistent[y];
                                }

                            //The moved persistents will be deleted by their owning cell when its indexed
                            numChild = (UINT32)FixedPersistent.size();
                            for(UINT32 y = 0; y < numChild; ++y)
                                childSize += FixedPersistent[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                            childrenSize += childSize;
                            writer.file_write(childSizePos, &childSize, 4);
                            Persistent.clear();
                            FixedPersistent.clear();
                            worldSize += childrenSize;
                            writer.file_write(childrenSizePos, &childrenSize, 4);
                            }
                        if(CloseMod)
                            delete curCell;
                        }

                    formCount += (UINT32)curWorld->CELLS.size();
                    for(std::map<UINT32, std::map<UINT32, std::vector<CELLRecord *> > >::iterator curBlock = BlockedRecords.begin(); curBlock != BlockedRecords.end(); ++curBlock)
                        {
                        gType = eExteriorBlock;
                        writer.file_write(&type, 4);
                        blockSizePos = writer.file_tell();
                        writer.file_write(&blockSize, 4); //Placeholder: will be overwritten with correct value later.
                        writer.file_write(&curBlock->first, 4);
                        writer.file_write(&gType, 4);
                        writer.file_write(&stamp, 4);
                        ++formCount;
                        blockSize = 20;

                        for(std::map<UINT32, std::vector<CELLRecord *> >::iterator curSubBlock = curBlock->second.begin(); curSubBlock != curBlock->second.end(); ++curSubBlock)
                            {
                            gType = eExteriorSubBlock;
                            writer.file_write(&type, 4);
                            subBlockSizePos = writer.file_tell();
                            writer.file_write(&subBlockSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&curSubBlock->first, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            ++formCount;
                            subBlockSize = 20;

                            numSubBlocks = (UINT32)curSubBlock->second.size();
                            for(UINT32 p = 0; p < numSubBlocks; ++p)
                                {
                                curCell = curSubBlock->second[p];
                                cellFormID = curCell->formID;
                                collapser.Accept(cellFormID);
                                subBlockSize += curCell->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                //Place the PGRD, ACHR, ACRE, and REFR records into their proper GRUP

                                if(curCell->LAND != NULL)
                                    Temporary.push_back(curCell->LAND);
                                if(CloseMod)
                                    curCell->LAND = NULL;

                                if(curCell->PGRD != NULL)
                                    Temporary.push_back(curCell->PGRD);
                                if(CloseMod)
                                    curCell->PGRD = NULL;

                                for(UINT32 y = 0; y < curCell->ACHR.size(); ++y)
                                    {
                                    if(curCell->ACHR[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->ACHR[y];
                                        }
                                    else if(curCell->ACHR[y]->IsVWD())
                                        VWD.push_back(curCell->ACHR[y]);
                                    else
                                        Temporary.push_back(curCell->ACHR[y]);
                                    }
                                if(CloseMod)
                                    curCell->ACHR.clear();

                                for(UINT32 y = 0; y < curCell->ACRE.size(); ++y)
                                    {
                                    if(curCell->ACRE[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->ACRE[y];
                                        }
                                    else if(curCell->ACRE[y]->IsVWD())
                                        VWD.push_back(curCell->ACRE[y]);
                                    else
                                        Temporary.push_back(curCell->ACRE[y]);
                                    }
                                if(CloseMod)
                                    curCell->ACRE.clear();

                                for(UINT32 y = 0; y < curCell->REFR.size(); ++y)
                                    {
                                    if(curCell->REFR[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->REFR[y];
                                        }
                                    else if(curCell->REFR[y]->IsVWD())
                                        VWD.push_back(curCell->REFR[y]);
                                    else
                                        Temporary.push_back(curCell->REFR[y]);
                                    }
                                if(CloseMod)
                                    curCell->REFR.clear();

                                numChildren = (UINT32)VWD.size() + (UINT32)Temporary.size();
                                if(numChildren)
                                    {
                                    formCount += numChildren;
                                    gType = eCellChildren;
                                    writer.file_write(&type, 4);
                                    childrenSizePos = writer.file_tell();
                                    writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&cellFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    ++formCount;
                                    childrenSize = 20;

                                    numChild = (UINT32)VWD.size();
                                    if(numChild)
                                        {
                                        gType = eCellVWD;
                                        writer.file_write(&type, 4);
                                        childSizePos = writer.file_tell();
                                        writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                        writer.file_write(&cellFormID, 4);
                                        writer.file_write(&gType, 4);
                                        writer.file_write(&stamp, 4);
                                        ++formCount;
                                        childSize = 20;

                                        for(UINT32 x = 0; x < numChild; ++x)
                                            {
                                            childSize += VWD[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                            if(CloseMod)
                                                delete VWD[x];
                                            }
                                        childrenSize += childSize;
                                        writer.file_write(childSizePos, &childSize, 4);
                                        VWD.clear();
                                        }

                                    numChild = (UINT32)Temporary.size();
                                    if(numChild)
                                        {
                                        gType = eCellTemporary;
                                        writer.file_write(&type, 4);
                                        childSizePos = writer.file_tell();
                                        writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                        writer.file_write(&cellFormID, 4);
                                        writer.file_write(&gType, 4);
                                        writer.file_write(&stamp, 4);
                                        ++formCount;
                                        childSize = 20;

                                        for(UINT32 x = 0; x < numChild; ++x)
                                            {
                                            childSize += Temporary[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                            if(CloseMod)
                                                delete Temporary[x];
                                            }
                                        childrenSize += childSize;
                                        writer.file_write(childSizePos, &childSize, 4);
                                        Temporary.clear();
                                        }
                                    subBlockSize += childrenSize;
                                    writer.file_write(childrenSizePos, &childrenSize, 4);
                                    }
                                if(CloseMod)
                                    delete curCell;
                                }
                            blockSize += subBlockSize;
                            writer.file_write(subBlockSizePos, &subBlockSize, 4);
                            curSubBlock->second.clear();
                            }
                        worldSize += blockSize;
                        writer.file_write(blockSizePos, &blockSize, 4);
                        curBlock->second.clear();
                        }
                    TopSize += worldSize;
                    writer.file_write(worldSizePos, &worldSize, 4);
                    }
                BlockedRecords.clear();
                }
            if(CloseMod)
                Records.clear();
            writer.file_write(TopSizePos, &TopSize, 4);

            return formCount;
            }
    };

template<class T>
class FNVGRUPRecords
    {
    public:
        UINT32 stamp, unknown;
        std::vector<Record *> Records;
        FNVGRUPRecords():stamp(134671), unknown(0) {}
        ~FNVGRUPRecords()
            {
            for(UINT32 p = 0;p < Records.size(); p++)
                delete Records[p];
            }

        bool Skim(FileReader &reader, const UINT32 &gSize, FNVRecordProcessor &processor, RecordOp &indexer)
            {
            if(gSize == 0)
                {
                printer("FNVGRUPRecords::Skim: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE);
                #endif
                return false;
                }
            Record * curRecord = NULL;
            //UINT32 recordType = 0;
            unsigned char *gEnd = reader.tell() + gSize - 24;
            UINT32 recordSize = 0;

            while(reader.tell() < gEnd){
                curRecord = new T(reader.tell() + 24);
                reader.skip(4); //reader.read(&recordType, 4);
                reader.read(&recordSize, 4);
                if(processor(curRecord))
                    {
                    indexer.Accept(curRecord);
                    Records.push_back(curRecord);
                    }
                reader.skip(recordSize);
                };
            if(Records.size())
                processor.IsEmpty(false);
            return true;
            }
        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            Record * curRecord = NULL;

            bool stop = false;

            if(RecordType != NULL && Records.size() > 0 && Records[0]->GetType() != RecordType)
                return false;
            for(UINT32 p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(RecordType == NULL || RecordType == curRecord->GetType())
                    {
                    stop = op.Accept(curRecord);
                    if(curRecord == NULL)
                        {
                        Records.erase(Records.begin() + p);
                        --p;
                        }
                    if(stop)
                        return stop;
                    }

                if(DeepVisit)
                    {
                    stop = curRecord->VisitSubRecords(RecordType, op);
                    if(stop)
                        return stop;
                    }
                }
            return stop;
            }
        UINT32 WriteGRUP(UINT32 TopLabel, FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            UINT32 numRecords = (UINT32)Records.size();
            if(numRecords == 0)
                return 0;
            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 TopSize = 0;
            UINT32 formCount = 0;

            //Top GRUP Header
            writer.file_write(&type, 4);
            UINT32 TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            //writer.file_write(&TopSize, 4);
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            writer.file_write(&unknown, 4);
            ++formCount;
            TopSize = 24;

            formCount += numRecords;
            for(UINT32 p = 0; p < numRecords; p++)
                {
                TopSize += Records[p]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                if(CloseMod)
                    delete Records[p];
                }
            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                Records.clear();
            return formCount;
            }
    };


template<>
class FNVGRUPRecords<FNV::DIALRecord>
    {
    public:
        UINT32 stamp, unknown;
        std::vector<Record *> Records;
        FNVGRUPRecords():stamp(134671), unknown(0) {}
        ~FNVGRUPRecords()
            {
            for(UINT32 p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(FileReader &reader, const UINT32 &gSize, FNVRecordProcessor &processor, RecordOp &indexer)
            {
            if(gSize == 0)
                {
                printer("GRUPRecords<DIALRecord>::Skim: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE);
                #endif
                return false;
                }
            FNV::DIALRecord *curDIALRecord = NULL, *orphans = NULL;
            Record *curRecord = NULL;
            UINT32 recordType = 0;
            unsigned char *gEnd = reader.tell() + gSize - 24;
            UINT32 recordSize = 0;

            curDIALRecord = orphans = new FNV::DIALRecord();
            while(reader.tell() < gEnd){
                reader.read(&recordType, 4);
                reader.read(&recordSize, 4);
                switch(recordType)
                    {
                    case REV32(DIAL):
                        curDIALRecord = new FNV::DIALRecord(reader.tell() + 16);
                        if(processor((Record *&)curDIALRecord))
                            {
                            indexer.Accept((Record *&)curDIALRecord);
                            Records.push_back(curDIALRecord);
                            }
                        break;
                    case REV32(GRUP): //All GRUPs will be recreated from scratch on write (saves memory)
                        reader.skip(16); //Skip label and type fields
                        //reader.read(&stamp, 4);
                        continue;
                    case REV32(INFO):
                        curRecord = new FNV::INFORecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curDIALRecord->INFO.push_back(curRecord);
                            }
                        break;
                    default:
                        printer("FNVGRUPRecords<FNV::DIALRecord>::Skim: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((STRING)&recordType)[0], ((STRING)&recordType)[1], ((STRING)&recordType)[2], ((STRING)&recordType)[3], reader.getFileName());
                        #ifdef CBASH_DEBUG_CHUNK
                            reader.peek_around(PEEK_SIZE);
                        #endif
                        break;
                    }
                reader.skip(recordSize);
                };
            if(Records.size())
                processor.IsEmpty(false);

            for(UINT32 x = 0; x < orphans->INFO.size(); ++x)
                {
                printer("FNVGRUPRecords<FNV::DIALRecord>::Skim: Warning - Parsing error. Skipped orphan INFO (%08X) at %08X in file \"%s\"\n", orphans->INFO[x]->formID, orphans->INFO[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, ((FNV::DIALRecord *)orphans)->INFO[x]->recData);
                #endif
                }
            delete orphans;
            return true;
            }
        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            Record * curRecord = NULL;
            bool stop = false;

            if(RecordType != NULL && RecordType != REV32(DIAL) && RecordType != REV32(INFO))
                return false;

            for(UINT32 p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(RecordType == NULL || RecordType == curRecord->GetType())
                    {
                    stop = op.Accept(curRecord);
                    if(curRecord == NULL)
                        {
                        Records.erase(Records.begin() + p);
                        --p;
                        }
                    if(stop)
                        return stop;
                    }

                if(DeepVisit)
                    {
                    stop = curRecord->VisitSubRecords(RecordType, op);
                    if(stop)
                        return stop;
                    }
                }
            return stop;
            }
        UINT32 WriteGRUP(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            UINT32 numDIALRecords = (UINT32)Records.size(); //Parent Records
            if(numDIALRecords == 0)
                return 0;
            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 TopSize =0;
            UINT32 ChildrenSize =0;
            UINT32 formCount = 0;
            UINT32 TopLabel = REV32(DIAL);
            UINT32 numINFORecords = 0;
            UINT32 parentFormID = 0;
            FNV::DIALRecord *curRecord = NULL;

            //Top GRUP Header
            writer.file_write(&type, 4);
            UINT32 TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            writer.file_write(&unknown, 4);
            ++formCount;
            TopSize = 24;

            gType = eTopicChildren;
            formCount += numDIALRecords;
            for(UINT32 p = 0; p < numDIALRecords; ++p)
                {
                curRecord = (FNV::DIALRecord *)Records[p];
                parentFormID = curRecord->formID;
                collapser.Accept(parentFormID);
                TopSize += curRecord->Write(writer, bMastersChanged, expander, collapser, Expanders);

                numINFORecords = (UINT32)curRecord->INFO.size();
                if(numINFORecords)
                    {
                    writer.file_write(&type, 4);
                    UINT32 ChildrenSizePos = writer.file_tell();
                    writer.file_write(&ChildrenSize, 4); //Placeholder: will be overwritten with correct value later.
                    writer.file_write(&parentFormID, 4);
                    writer.file_write(&gType, 4);
                    writer.file_write(&stamp, 4);
                    writer.file_write(&unknown, 4);
                    ++formCount;
                    ChildrenSize = 24;

                    formCount += numINFORecords;
                    for(UINT32 y = 0; y < curRecord->INFO.size(); ++y)
                        {
                        ChildrenSize += curRecord->INFO[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                        if(CloseMod)
                            delete curRecord->INFO[y];
                        }
                    writer.file_write(ChildrenSizePos, &ChildrenSize, 4);
                    TopSize += ChildrenSize;
                    if(CloseMod)
                        curRecord->INFO.clear();
                    }
                if(CloseMod)
                    delete curRecord;
                }
            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                Records.clear();
            return formCount;
            }

    };

template<>
class FNVGRUPRecords<FNV::CELLRecord>
    {
    public:
        UINT32 stamp, unknown;
        std::vector<Record *> Records;
        FNVGRUPRecords():stamp(134671), unknown(0) {}
        ~FNVGRUPRecords()
            {
            for(UINT32 p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(FileReader &reader, const UINT32 &gSize, FNVRecordProcessor &processor, RecordOp &indexer)
            {
            if(gSize == 0)
                {
                printer("FNVGRUPRecords<FNV::CELLRecord>::Skim: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE);
                #endif
                return false;
                }
            FNV::CELLRecord *curCELLRecord = NULL, *orphans = NULL;
            Record * curRecord = NULL;
            UINT32 recordType = 0;
            unsigned char *gEnd = reader.tell() + gSize - 24;
            UINT32 recordSize = 0;

            curCELLRecord = orphans = new FNV::CELLRecord();
            while(reader.tell() < gEnd){
                reader.read(&recordType, 4);
                reader.read(&recordSize, 4);
                switch(recordType)
                    {
                    case REV32(CELL):
                        curCELLRecord = new FNV::CELLRecord(reader.tell() + 16);
                        if(processor((Record *&)curCELLRecord))
                            {
                            indexer.Accept((Record *&)curCELLRecord);
                            Records.push_back(curCELLRecord);
                            }
                        break;
                    case REV32(GRUP): //All GRUPs will be recreated from scratch on write (saves memory)
                        reader.skip(16); //skip the rest of the header
                        continue;
                    case REV32(ACHR):
                        curRecord = new FNV::ACHRRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->ACHR.push_back(curRecord);
                            }
                        break;
                    case REV32(ACRE):
                        curRecord = new FNV::ACRERecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->ACRE.push_back(curRecord);
                            }
                        break;
                    case REV32(REFR):
                        curRecord = new FNV::REFRRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->REFR.push_back(curRecord);
                            }
                        break;
                    case REV32(PGRE):
                        curRecord = new FNV::PGRERecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PGRE.push_back(curRecord);
                            }
                        break;
                    case REV32(PMIS):
                        curRecord = new FNV::PMISRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PMIS.push_back(curRecord);
                            }
                        break;
                    case REV32(PBEA):
                        curRecord = new FNV::PBEARecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PBEA.push_back(curRecord);
                            }
                        break;
                    case REV32(PFLA):
                        curRecord = new FNV::PFLARecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PFLA.push_back(curRecord);
                            }
                        break;
                    case REV32(PCBE):
                        curRecord = new FNV::PCBERecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PCBE.push_back(curRecord);
                            }
                        break;
                    case REV32(NAVM):
                        curRecord = new FNV::NAVMRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->NAVM.push_back(curRecord);
                            }
                        break;
                    default:
                        printer("FNVGRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((STRING)&recordType)[0], ((STRING)&recordType)[1], ((STRING)&recordType)[2], ((STRING)&recordType)[3], reader.getFileName());
                        #ifdef CBASH_DEBUG_CHUNK
                            reader.peek_around(PEEK_SIZE);
                        #endif
                        reader.skip(16); //skip the rest of the header since it isn't implemented
                        break;
                    }
                reader.skip(recordSize);
                };
            if(Records.size())
                processor.IsEmpty(false);

            for(UINT32 x = 0; x < orphans->ACHR.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan ACHR (%08X) at %08X in file \"%s\"\n", orphans->ACHR[x]->formID, orphans->ACHR[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->ACHR[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->ACRE.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan ACRE (%08X) at %08X in file \"%s\"\n", orphans->ACRE[x]->formID, orphans->ACRE[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->ACRE[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->REFR.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan REFR (%08X) at %08X in file \"%s\"\n", orphans->REFR[x]->formID, orphans->REFR[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->REFR[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PGRE.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PGRE (%08X) at %08X in file \"%s\"\n", orphans->PGRE[x]->formID, orphans->PGRE[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PGRE[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PMIS.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PMIS (%08X) at %08X in file \"%s\"\n", orphans->PMIS[x]->formID, orphans->PMIS[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PMIS[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PBEA.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PBEA (%08X) at %08X in file \"%s\"\n", orphans->PBEA[x]->formID, orphans->PBEA[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PBEA[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PFLA.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PFLA (%08X) at %08X in file \"%s\"\n", orphans->PFLA[x]->formID, orphans->PFLA[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PFLA[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PCBE.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PCBE (%08X) at %08X in file \"%s\"\n", orphans->PCBE[x]->formID, orphans->PCBE[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PCBE[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->NAVM.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan NAVM (%08X) at %08X in file \"%s\"\n", orphans->NAVM[x]->formID, orphans->NAVM[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->NAVM[x]->recData);
                #endif
                }
            delete orphans;

            return true;
            }
        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            Record * curRecord = NULL;
            bool stop = false;

            if(RecordType != NULL &&
                RecordType != REV32(CELL) &&
                RecordType != REV32(ACHR) &&
                RecordType != REV32(ACRE) &&
                RecordType != REV32(REFR) &&
                RecordType != REV32(PGRE) &&
                RecordType != REV32(PMIS) &&
                RecordType != REV32(PBEA) &&
                RecordType != REV32(PFLA) &&
                RecordType != REV32(PCBE) &&
                RecordType != REV32(NAVM))
                return false;

            for(UINT32 p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(RecordType == NULL || RecordType == curRecord->GetType())
                    {
                    stop = op.Accept(curRecord);
                    if(curRecord == NULL)
                        {
                        Records.erase(Records.begin() + p);
                        --p;
                        }
                    if(stop)
                        return stop;
                    }

                if(DeepVisit)
                    {
                    stop = curRecord->VisitSubRecords(RecordType, op);
                    if(stop)
                        return stop;
                    }
                }
            return stop;
            }
        UINT32 WriteGRUP(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            UINT32 numRecords = (UINT32)Records.size();
            if(numRecords == 0)
                return 0;
            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 TopSize = 0;
            UINT32 TopSizePos = 0;
            UINT32 blockSize = 0;
            UINT32 blockSizePos = 0;
            UINT32 subBlockSize = 0;
            UINT32 subBlockSizePos = 0;
            UINT32 childrenSize = 0;
            UINT32 childrenSizePos = 0;
            UINT32 childSize = 0;
            UINT32 childSizePos = 0;

            UINT32 formCount = 0;

            UINT32 gLabel = REV32(CELL);
            UINT32 numSubBlocks = 0;
            UINT32 numChildren = 0;
            UINT32 numChild = 0;

            UINT32 parentFormID = 0;
            FNV::CELLRecord *curRecord = NULL;
            int ObjectID, BlockIndex, SubBlockIndex;

            std::vector< std::vector< std::vector<FNV::CELLRecord *> > > BlockedRecords(10, std::vector< std::vector<FNV::CELLRecord *> > (10, std::vector<FNV::CELLRecord *>()));
            std::vector<Record *> Persistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;
            BlockedRecords.reserve(numRecords);
            for(UINT32 p = 0; p < numRecords; ++p)
                {
                curRecord = (FNV::CELLRecord *)Records[p];

                ObjectID = curRecord->formID & 0x00FFFFFF;
                BlockIndex = ObjectID % 10;
                SubBlockIndex = (ObjectID / 10) % 10;

                BlockedRecords[BlockIndex][SubBlockIndex].push_back(curRecord);
                }

            //Top GRUP Header
            writer.file_write(&type, 4);
            TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&gLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            writer.file_write(&unknown, 4);

            ++formCount;
            TopSize = 24;

            formCount += numRecords;
            for(UINT32 curBlock = 0; curBlock < 10; ++curBlock)
                {
                gType = eInteriorBlock;
                for(UINT32 curSubBlock = 0; curSubBlock < 10; ++curSubBlock)
                    {
                    numSubBlocks = (UINT32)BlockedRecords[curBlock][curSubBlock].size();
                    if(numSubBlocks != 0)
                        {
                        if(gType == eInteriorBlock)
                            {
                            writer.file_write(&type, 4);
                            blockSizePos = writer.file_tell();
                            writer.file_write(&blockSizePos, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&curBlock, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            writer.file_write(&unknown, 4);
                            ++formCount;
                            blockSize = 24;
                            }
                        gType = eInteriorSubBlock;
                        writer.file_write(&type, 4);
                        subBlockSizePos = writer.file_tell();
                        writer.file_write(&subBlockSize, 4); //Placeholder: will be overwritten with correct value later.
                        writer.file_write(&curSubBlock, 4);
                        writer.file_write(&gType, 4);
                        writer.file_write(&stamp, 4);
                        writer.file_write(&unknown, 4);
                        ++formCount;
                        subBlockSize = 24;
                        for(UINT32 p = 0; p < numSubBlocks; ++p)
                            {
                            curRecord = BlockedRecords[curBlock][curSubBlock][p];
                            parentFormID = curRecord->formID;
                            collapser.Accept(parentFormID);
                            subBlockSize += curRecord->Write(writer, bMastersChanged, expander, collapser, Expanders);
                            //Place the ACHR, ACRE, REFR, PGRE, PMIS, PBEA, PFLA, PCBE, NAVM records into their proper GRUP

                            for(UINT32 y = 0; y < curRecord->ACHR.size(); ++y)
                                {
                                if(curRecord->ACHR[y]->IsPersistent())
                                    Persistent.push_back(curRecord->ACHR[y]);
                                else if(curRecord->ACHR[y]->IsVWD())
                                    VWD.push_back(curRecord->ACHR[y]);
                                else
                                    Temporary.push_back(curRecord->ACHR[y]);
                                }
                            if(CloseMod)
                                curRecord->ACHR.clear();

                            for(UINT32 y = 0; y < curRecord->ACRE.size(); ++y)
                                {
                                if(curRecord->ACRE[y]->IsPersistent())
                                    Persistent.push_back(curRecord->ACRE[y]);
                                else if(curRecord->ACRE[y]->IsVWD())
                                    VWD.push_back(curRecord->ACRE[y]);
                                else
                                    Temporary.push_back(curRecord->ACRE[y]);
                                }
                            if(CloseMod)
                                curRecord->ACRE.clear();

                            for(UINT32 y = 0; y < curRecord->REFR.size(); ++y)
                                {
                                if(curRecord->REFR[y]->IsPersistent())
                                    Persistent.push_back(curRecord->REFR[y]);
                                else if(curRecord->REFR[y]->IsVWD())
                                    VWD.push_back(curRecord->REFR[y]);
                                else
                                    Temporary.push_back(curRecord->REFR[y]);
                                }
                            if(CloseMod)
                                curRecord->REFR.clear();


                            for(UINT32 y = 0; y < curRecord->PGRE.size(); ++y)
                                {
                                if(curRecord->PGRE[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PGRE[y]);
                                else if(curRecord->PGRE[y]->IsVWD())
                                    VWD.push_back(curRecord->PGRE[y]);
                                else
                                    Temporary.push_back(curRecord->PGRE[y]);
                                }
                            if(CloseMod)
                                curRecord->PGRE.clear();

                            for(UINT32 y = 0; y < curRecord->PMIS.size(); ++y)
                                {
                                if(curRecord->PMIS[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PMIS[y]);
                                else if(curRecord->PMIS[y]->IsVWD())
                                    VWD.push_back(curRecord->PMIS[y]);
                                else
                                    Temporary.push_back(curRecord->PMIS[y]);
                                }
                            if(CloseMod)
                                curRecord->PMIS.clear();

                            for(UINT32 y = 0; y < curRecord->PBEA.size(); ++y)
                                {
                                if(curRecord->PBEA[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PBEA[y]);
                                else if(curRecord->PBEA[y]->IsVWD())
                                    VWD.push_back(curRecord->PBEA[y]);
                                else
                                    Temporary.push_back(curRecord->PBEA[y]);
                                }
                            if(CloseMod)
                                curRecord->PBEA.clear();

                            for(UINT32 y = 0; y < curRecord->PFLA.size(); ++y)
                                {
                                if(curRecord->PFLA[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PFLA[y]);
                                else if(curRecord->PFLA[y]->IsVWD())
                                    VWD.push_back(curRecord->PFLA[y]);
                                else
                                    Temporary.push_back(curRecord->PFLA[y]);
                                }
                            if(CloseMod)
                                curRecord->PFLA.clear();

                            for(UINT32 y = 0; y < curRecord->PCBE.size(); ++y)
                                {
                                if(curRecord->PCBE[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PCBE[y]);
                                else if(curRecord->PCBE[y]->IsVWD())
                                    VWD.push_back(curRecord->PCBE[y]);
                                else
                                    Temporary.push_back(curRecord->PCBE[y]);
                                }
                            if(CloseMod)
                                curRecord->PCBE.clear();

                            for(UINT32 y = 0; y < curRecord->NAVM.size(); ++y)
                                 Temporary.push_back(curRecord->NAVM[y]);
                            if(CloseMod)
                                curRecord->NAVM.clear();

                            numChildren = (UINT32)Persistent.size() + (UINT32)VWD.size() + (UINT32)Temporary.size();
                            if(numChildren)
                                {
                                formCount += numChildren;
                                gType = eCellChildren;
                                writer.file_write(&type, 4);
                                childrenSizePos = writer.file_tell();
                                writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                                writer.file_write(&parentFormID, 4);
                                writer.file_write(&gType, 4);
                                writer.file_write(&stamp, 4);
                                writer.file_write(&unknown, 4);
                                ++formCount;
                                childrenSize = 24;

                                numChild = (UINT32)Persistent.size();
                                if(numChild)
                                    {
                                    gType = eCellPersistent;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    writer.file_write(&unknown, 4);
                                    ++formCount;
                                    childSize = 24;

                                    for(UINT32 x = 0; x < numChild; ++x)
                                        {
                                        childSize += Persistent[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                        if(CloseMod)
                                            delete Persistent[x];
                                        }
                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    Persistent.clear();
                                    }

                                numChild = (UINT32)VWD.size();
                                if(numChild)
                                    {
                                    gType = eCellVWD;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    writer.file_write(&unknown, 4);
                                    ++formCount;
                                    childSize = 24;

                                    for(UINT32 x = 0; x < numChild; ++x)
                                        {
                                        childSize += VWD[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                        if(CloseMod)
                                            delete VWD[x];
                                        }
                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    VWD.clear();
                                    }

                                numChild = (UINT32)Temporary.size();
                                if(numChild)
                                    {
                                    gType = eCellTemporary;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    writer.file_write(&unknown, 4);
                                    ++formCount;
                                    childSize = 24;

                                    for(UINT32 x = 0; x < numChild; ++x)
                                        {
                                        childSize += Temporary[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                        if(CloseMod)
                                            delete Temporary[x];
                                        }
                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    Temporary.clear();
                                    }
                                subBlockSize += childrenSize;
                                writer.file_write(childrenSizePos, &childrenSize, 4);
                                }
                            if(CloseMod)
                                delete curRecord;
                            }
                        blockSize += subBlockSize;
                        writer.file_write(subBlockSizePos, &subBlockSize, 4);
                        BlockedRecords[curBlock][curSubBlock].clear();
                        }
                    }
                if(gType != eInteriorBlock)
                    {
                    TopSize += blockSize;
                    writer.file_write(blockSizePos, &blockSize, 4);
                    }
                BlockedRecords[curBlock].clear();
                }
            if(CloseMod)
                Records.clear();
            writer.file_write(TopSizePos, &TopSize, 4);
            BlockedRecords.clear();
            return formCount;
            }
    };

template<>
class FNVGRUPRecords<FNV::WRLDRecord>
    {
    public:
        UINT32 stamp, unknown;
        std::vector<Record *> Records;
        FNVGRUPRecords():stamp(134671), unknown(0) {}
        ~FNVGRUPRecords()
            {
            for(UINT32 p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(FileReader &reader, const UINT32 &gSize, FNVRecordProcessor &processor, RecordOp &indexer, RecordOp &fullReader)
            {
            if(gSize == 0)
                {
                printer("FNVGRUPRecords<FNV::WRLDRecord>::Skim: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE);
                #endif
                return false;
                }
            std::map<SINT32, std::map<SINT32, FNV::LANDRecord *> > GridXY_LAND;
            std::vector<std::pair<UINT32, unsigned char *> > GRUPs;
            std::pair<UINT32, unsigned char *> GRUP_End;
            UINT32 recordType = 0;
            unsigned char *gEnd = reader.tell() + gSize - 24;
            GRUP_End.first = eTop;
            GRUP_End.second = gEnd;
            GRUPs.push_back(GRUP_End);
            UINT32 recordSize = 0;
            FNV::WRLDRecord *curWRLDRecord = NULL;
            FNV::CELLRecord *curCELLRecord = NULL, *orphans = NULL;
            Record * curRecord = NULL;

            curCELLRecord = orphans = new FNV::CELLRecord();
            while(reader.tell() < gEnd){
                while(reader.tell() >= GRUP_End.second)
                    {
                    //Better tracking of the last GRUP
                    //Mainly fixes cases where the world cell isn't located before the cell blocks
                    //One example of this is Windfall.esp
                    GRUPs.pop_back();
                    GRUP_End = GRUPs.back();
                    };
                reader.read(&recordType, 4);
                reader.read(&recordSize, 4);
                switch(recordType)
                    {
                    case REV32(WRLD):
                        curWRLDRecord = new FNV::WRLDRecord(reader.tell() + 16);
                        if(processor((Record *&)curWRLDRecord))
                            {
                            indexer.Accept((Record *&)curWRLDRecord);
                            Records.push_back(curWRLDRecord);
                            }
                        break;
                    case REV32(CELL):
                        curCELLRecord = new FNV::CELLRecord(reader.tell() + 16);
                        if(processor((Record *&)curCELLRecord))
                            {
                            curCELLRecord->Parent = curWRLDRecord;
                            switch(GRUP_End.first)
                                {
                                case eWorld:
                                    if(curWRLDRecord == NULL)
                                        {
                                        printer("FNVGRUPRecords<FNV::WRLDRecord>::Skim: Warning - Parsing error. Skipped orphan World CELL (%08X) at %08X in file \"%s\"\n", curCELLRecord->formID, reader.tell() - reader.start(), reader.getFileName());
                                        delete curCELLRecord;
                                        #ifdef CBASH_DEBUG_CHUNK
                                            reader.peek_around(PEEK_SIZE);
                                        #endif
                                        }
                                    else if(curWRLDRecord->CELL != NULL)
                                        {
                                        printer("FNVGRUPRecords<FNV::WRLDRecord>::Skim: Warning - Parsing error. Skipped extra World CELL (%08X) at %08X in file \"%s\"\n  WRLD (%08X) already has CELL (%08X)\n", curCELLRecord->formID, reader.tell() - reader.start(), reader.getFileName(), curWRLDRecord->formID, curWRLDRecord->CELL->formID);
                                        delete curCELLRecord;
                                        #ifdef CBASH_DEBUG_CHUNK
                                            reader.peek_around(PEEK_SIZE);
                                        #endif
                                        }
                                    else
                                        {
                                        indexer.Accept((Record *&)curCELLRecord);
                                        curWRLDRecord->CELL = curCELLRecord;
                                        }
                                    break;
                                default:
                                    indexer.Accept((Record *&)curCELLRecord);
                                    curWRLDRecord->CELLS.push_back(curCELLRecord);
                                    break;
                                }
                            }
                        break;
                    case REV32(GRUP): //All GRUPs will be recreated from scratch on write (saves memory)
                        reader.skip(4);
                        reader.read(&GRUP_End.first, 4);
                        reader.skip(8);
                        GRUP_End.second = reader.tell() + recordSize - 24;
                        GRUPs.push_back(GRUP_End);
                        continue;
                    case REV32(LAND):
                        curRecord = new FNV::LANDRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            if(curCELLRecord == orphans)
                                {
                                printer("FNVGRUPRecords<FNV::WRLDRecord>::Skim: Warning - Parsing error. Skipped orphan LAND (%08X) at %08X in file \"%s\"\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName());
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else if(curCELLRecord->LAND != NULL)
                                {
                                printer("FNVGRUPRecords<FNV::WRLDRecord>::Skim: Warning - Parsing error. Skipped extra LAND (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has LAND (%08X)\n", curRecord->formID, reader.tell() - reader.start(), reader.getFileName(), curCELLRecord->formID, curCELLRecord->LAND->formID);
                                delete curRecord;
                                #ifdef CBASH_DEBUG_CHUNK
                                    reader.peek_around(PEEK_SIZE);
                                #endif
                                }
                            else
                                {
                                indexer.Accept(curRecord);
                                curCELLRecord->LAND = curRecord;
                                if(processor.Flags.IsIndexLANDs)
                                    {
                                    //Record *temp = curCELLRecord;
                                    fullReader.Accept((Record *&)curCELLRecord); //may already be loaded, but just to be sure.
                                    //CELL will be unloaded if needed after a second round of indexing when all records are loaded
                                    curCELLRecord->XCLC.Load();
                                    GridXY_LAND[curCELLRecord->XCLC->posX][curCELLRecord->XCLC->posY] = (FNV::LANDRecord *)curRecord;
                                    }
                                }
                            }
                        break;
                    case REV32(ACHR):
                        curRecord = new FNV::ACHRRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->ACHR.push_back(curRecord);
                            }
                        break;
                    case REV32(ACRE):
                        curRecord = new FNV::ACRERecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->ACRE.push_back(curRecord);
                            }
                        break;
                    case REV32(REFR):
                        curRecord = new FNV::REFRRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->REFR.push_back(curRecord);
                            }
                        break;
                    case REV32(PGRE):
                        curRecord = new FNV::PGRERecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PGRE.push_back(curRecord);
                            }
                        break;
                    case REV32(PMIS):
                        curRecord = new FNV::PMISRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PMIS.push_back(curRecord);
                            }
                        break;
                    case REV32(PBEA):
                        curRecord = new FNV::PBEARecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PBEA.push_back(curRecord);
                            }
                        break;
                    case REV32(PFLA):
                        curRecord = new FNV::PFLARecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PFLA.push_back(curRecord);
                            }
                        break;
                    case REV32(PCBE):
                        curRecord = new FNV::PCBERecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->PCBE.push_back(curRecord);
                            }
                        break;
                    case REV32(NAVM):
                        curRecord = new FNV::NAVMRecord(reader.tell() + 16);
                        if(processor(curRecord))
                            {
                            indexer.Accept(curRecord);
                            curCELLRecord->NAVM.push_back(curRecord);
                            }
                        break;
                    default:
                        printer("FNVGRUPRecords<FNV::WRLDRecord>::Skim: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((STRING)&recordType)[0], ((STRING)&recordType)[1], ((STRING)&recordType)[2], ((STRING)&recordType)[3], reader.getFileName());
                        #ifdef CBASH_DEBUG_CHUNK
                            reader.peek_around(PEEK_SIZE);
                        #endif
                        reader.skip(16); //skip the rest of the header since it isn't implemented
                        break;
                    }
                reader.skip(recordSize);
                };

            //Index LAND records by grid
            //There might be ACHR, ACRE, or REFR records in the World CELL
            if(processor.Flags.IsIndexLANDs || processor.Flags.IsFixupPlaceables)
                {
                SINT32 posX = 0, posY = 0;
                SINT32 gridX = 0, gridY = 0;
                FNV::WRLDRecord *curWRLD = NULL;
                FNV::CELLRecord *curCELL = NULL;
                FNV::CELLRecord *curWRLDCELL = NULL;
                FNV::LANDRecord *curLAND = NULL;
                for(UINT32 x = 0; x < Records.size(); ++x)
                    {
                    curWRLD = (FNV::WRLDRecord *)Records[x];
                    for(UINT32 y = 0; y < curWRLD->CELLS.size(); ++y)
                        {
                        curCELL = (FNV::CELLRecord *)curWRLD->CELLS[y];
                        //reader.Accept((Record **)&curCELL); //already read when loaded
                        //curCELLRecord->XCLC.Load();  //already loaded when CELL loaded
                        posX = curCELL->XCLC->posX;
                        posY = curCELL->XCLC->posY;

                        curWRLDCELL = (FNV::CELLRecord *)curWRLD->CELL;
                        if(processor.Flags.IsFixupPlaceables && curWRLDCELL != NULL)
                            {
                            for(UINT32 x = 0; x < curWRLDCELL->ACHR.size();)
                                {
                                //Have to test each record to see if it belongs to the cell. This is determined by its positioning.
                                curRecord = curWRLDCELL->ACHR[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((FNV::ACHRRecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((FNV::ACHRRecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    //For easier use later on, go ahead and move it to the parent cell.
                                    //It will get moved back later during the save process if need be.
                                    curCELL->ACHR.push_back(curRecord);
                                    curWRLDCELL->ACHR.erase(curWRLDCELL->ACHR.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->ACRE.size();)
                                {
                                curRecord = curWRLDCELL->ACRE[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((FNV::ACRERecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((FNV::ACRERecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->ACRE.push_back(curRecord);
                                    curWRLDCELL->ACRE.erase(curWRLDCELL->ACRE.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->REFR.size();)
                                {
                                curRecord = curWRLDCELL->REFR[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((FNV::REFRRecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((FNV::REFRRecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->REFR.push_back(curRecord);
                                    curWRLDCELL->REFR.erase(curWRLDCELL->REFR.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->PGRE.size();)
                                {
                                curRecord = curWRLDCELL->PGRE[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((FNV::PGRERecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((FNV::PGRERecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->PGRE.push_back(curRecord);
                                    curWRLDCELL->PGRE.erase(curWRLDCELL->PGRE.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->PMIS.size();)
                                {
                                curRecord = curWRLDCELL->PMIS[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((FNV::PMISRecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((FNV::PMISRecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->PMIS.push_back(curRecord);
                                    curWRLDCELL->PMIS.erase(curWRLDCELL->PMIS.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->PBEA.size();)
                                {
                                curRecord = curWRLDCELL->PBEA[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((FNV::PBEARecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((FNV::PBEARecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->PBEA.push_back(curRecord);
                                    curWRLDCELL->PBEA.erase(curWRLDCELL->PBEA.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->PFLA.size();)
                                {
                                curRecord = curWRLDCELL->PFLA[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((FNV::PFLARecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((FNV::PFLARecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->PFLA.push_back(curRecord);
                                    curWRLDCELL->PFLA.erase(curWRLDCELL->PFLA.begin() + x);
                                    }
                                else ++x;
                                }

                            for(UINT32 x = 0; x < curWRLDCELL->PCBE.size();)
                                {
                                curRecord = curWRLDCELL->PCBE[x];
                                fullReader.Accept(curRecord);

                                gridX = (SINT32)floor(((FNV::PCBERecord *)curRecord)->DATA.value.posX / 4096.0);
                                gridY = (SINT32)floor(((FNV::PCBERecord *)curRecord)->DATA.value.posY / 4096.0);

                                if(processor.Flags.IsMinLoad)
                                    curRecord->Unload();

                                if(gridX == posX && gridY == posY)
                                    {
                                    curCELL->PCBE.push_back(curRecord);
                                    curWRLDCELL->PCBE.erase(curWRLDCELL->PCBE.begin() + x);
                                    }
                                else ++x;
                                }

                            //NAVM's probably shouldn't ever show up in the world cell since they aren't persistent
                            //for(UINT32 x = 0; x < curWRLDCELL->NAVM.size();)
                            //    {
                            //    curRecord = curWRLDCELL->NAVM[x];
                            //    fullReader.Accept(curRecord);

                            //    gridX = (SINT32)floor(((FNV::NAVMRecord *)curRecord)->DATA.value.posX / 4096.0);
                            //    gridY = (SINT32)floor(((FNV::NAVMRecord *)curRecord)->DATA.value.posY / 4096.0);

                            //    if(processor.Flags.IsMinLoad)
                            //        curRecord->Unload();

                            //    if(gridX == posX && gridY == posY)
                            //        {
                            //        curCELL->NAVM.push_back(curRecord);
                            //        curWRLDCELL->NAVM.erase(curWRLDCELL->NAVM.begin() + x);
                            //        }
                            //    else ++x;
                            //    }
                            }

                        if(processor.Flags.IsIndexLANDs)
                            {
                            curLAND = (FNV::LANDRecord *)curCELL->LAND;
                            if(curLAND != NULL)
                                {
                                curLAND->NorthLand = GridXY_LAND[posX][posY + 1];
                                curLAND->SouthLand = GridXY_LAND[posX][posY - 1];
                                curLAND->EastLand = GridXY_LAND[posX + 1][posY];
                                curLAND->WestLand = GridXY_LAND[posX - 1][posY];
                                }
                            }

                        if(processor.Flags.IsMinLoad)
                            curCELL->Unload();
                        }
                    }
                }

            if(Records.size())
                processor.IsEmpty(false);

            for(UINT32 x = 0; x < orphans->ACHR.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan ACHR (%08X) at %08X in file \"%s\"\n", orphans->ACHR[x]->formID, orphans->ACHR[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->ACHR[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->ACRE.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan ACRE (%08X) at %08X in file \"%s\"\n", orphans->ACRE[x]->formID, orphans->ACRE[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->ACRE[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->REFR.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan REFR (%08X) at %08X in file \"%s\"\n", orphans->REFR[x]->formID, orphans->REFR[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->REFR[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PGRE.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PGRE (%08X) at %08X in file \"%s\"\n", orphans->PGRE[x]->formID, orphans->PGRE[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PGRE[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PMIS.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PMIS (%08X) at %08X in file \"%s\"\n", orphans->PMIS[x]->formID, orphans->PMIS[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PMIS[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PBEA.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PBEA (%08X) at %08X in file \"%s\"\n", orphans->PBEA[x]->formID, orphans->PBEA[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PBEA[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PFLA.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PFLA (%08X) at %08X in file \"%s\"\n", orphans->PFLA[x]->formID, orphans->PFLA[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PFLA[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->PCBE.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan PCBE (%08X) at %08X in file \"%s\"\n", orphans->PCBE[x]->formID, orphans->PCBE[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->PCBE[x]->recData);
                #endif
                }

            for(UINT32 x = 0; x < orphans->NAVM.size(); ++x)
                {
                printer("GRUPRecords<FNV::CELLRecord>::Skim: Warning - Parsing error. Skipped orphan NAVM (%08X) at %08X in file \"%s\"\n", orphans->NAVM[x]->formID, orphans->NAVM[x]->recData - reader.start(), reader.getFileName());
                #ifdef CBASH_DEBUG_CHUNK
                    reader.peek_around(PEEK_SIZE, orphans->NAVM[x]->recData);
                #endif
                }
            delete orphans;

            return true;
            }
        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            Record *curRecord = NULL;
            bool stop = false;

            if(RecordType != NULL &&
                RecordType != REV32(WRLD) &&
                RecordType != REV32(CELL) &&
                RecordType != REV32(LAND) &&
                RecordType != REV32(ACHR) &&
                RecordType != REV32(ACRE) &&
                RecordType != REV32(REFR) &&
                RecordType != REV32(PGRE) &&
                RecordType != REV32(PMIS) &&
                RecordType != REV32(PBEA) &&
                RecordType != REV32(PFLA) &&
                RecordType != REV32(PCBE) &&
                RecordType != REV32(NAVM))
                return false;

            for(UINT32 p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(RecordType == NULL || RecordType == curRecord->GetType())
                    {
                    stop = op.Accept(curRecord);
                    if(curRecord == NULL)
                        {
                        Records.erase(Records.begin() + p);
                        --p;
                        }
                    if(stop)
                        return stop;
                    }

                if(DeepVisit)
                    {
                    stop = curRecord->VisitSubRecords(RecordType, op);
                    if(stop)
                        return stop;
                    }
                }
            return stop;
            }
        UINT32 WriteGRUP(FileWriter &writer, FormIDHandlerClass &FormIDHandler, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            UINT32 numWrldRecords = (UINT32)Records.size();
            if(numWrldRecords == 0)
                return 0;
            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 gLabel = REV32(WRLD);
            UINT32 TopSize = 0;
            UINT32 TopSizePos = 0;
            UINT32 worldSize = 0;
            UINT32 worldSizePos = 0;
            UINT32 blockSize = 0;
            UINT32 blockSizePos = 0;
            UINT32 subBlockSize = 0;
            UINT32 subBlockSizePos = 0;
            UINT32 childrenSize = 0;
            UINT32 childrenSizePos = 0;
            UINT32 childSize = 0;
            UINT32 childSizePos = 0;

            UINT32 formCount = 0;

            UINT32 numCellRecords = 0;
            UINT32 numSubBlocks = 0;
            UINT32 numChildren = 0;
            UINT32 numChild = 0;

            FNV::WRLDRecord *curWorld = NULL;
            FNV::CELLRecord *curCell = NULL;
            FNV::CELLRecord *curWorldCell = NULL;
            UINT32 worldFormID = 0;
            UINT32 cellFormID = 0;
            int gridX, gridY;
            UINT32 BlockIndex, SubBlockIndex;

            std::map<UINT32, std::map<UINT32, std::vector<FNV::CELLRecord *> > > BlockedRecords;
            std::vector<Record *> Persistent;
            std::vector<Record *> FixedPersistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;

            //Top GRUP Header
            writer.file_write(&type, 4);
            TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&gLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            writer.file_write(&unknown, 4);
            ++formCount;
            TopSize = 24;

            formCount += numWrldRecords;
            for(UINT32 x = 0; x < numWrldRecords; ++x)
                {
                curWorld = (FNV::WRLDRecord *)Records[x];
                worldFormID = curWorld->formID;
                collapser.Accept(worldFormID);
                TopSize += curWorld->Write(writer, bMastersChanged, expander, collapser, Expanders);

                curWorldCell = (FNV::CELLRecord *)curWorld->CELL;

                numCellRecords = (UINT32)curWorld->CELLS.size();
                for(UINT32 p = 0; p < numCellRecords; ++p)
                    {
                    curCell = (FNV::CELLRecord *)curWorld->CELLS[p];

                    //All persistent references must be moved to the world cell
                    for(UINT32 y = 0; y < curCell->ACRE.size(); ++y)
                        if(curCell->ACRE[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->ACRE[y]);

                    for(UINT32 y = 0; y < curCell->ACHR.size(); ++y)
                        if(curCell->ACHR[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->ACHR[y]);

                    for(UINT32 y = 0; y < curCell->REFR.size(); ++y)
                        if(curCell->REFR[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->REFR[y]);

                    for(UINT32 y = 0; y < curCell->PGRE.size(); ++y)
                        if(curCell->PGRE[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PGRE[y]);

                    for(UINT32 y = 0; y < curCell->PMIS.size(); ++y)
                        if(curCell->PMIS[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PMIS[y]);

                    for(UINT32 y = 0; y < curCell->PBEA.size(); ++y)
                        if(curCell->PBEA[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PBEA[y]);

                    for(UINT32 y = 0; y < curCell->PFLA.size(); ++y)
                        if(curCell->PFLA[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PFLA[y]);

                    for(UINT32 y = 0; y < curCell->PCBE.size(); ++y)
                        if(curCell->PCBE[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PCBE[y]);

                    //for(UINT32 y = 0; y < curCell->NAVM.size(); ++y)
                    //    if(curCell->NAVM[y]->IsPersistent())
                    //        FixedPersistent.push_back(curCell->NAVM[y]);

                    if(curCell->Read())
                        curCell->VisitFormIDs(expander);
                    curCell->XCLC.Load();
                    gridX = (int)floor(curCell->XCLC->posX / 8.0);
                    gridY = (int)floor(curCell->XCLC->posY / 8.0);
                    if(!curCell->IsChanged())
                        curCell->Unload();
                    SubBlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                    gridX = (int)floor(gridX / 4.0);
                    gridY = (int)floor(gridY / 4.0);
                    BlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);

                    BlockedRecords[BlockIndex][SubBlockIndex].push_back(curCell);
                    }

                if(curWorldCell == NULL && FixedPersistent.size()) //create a default dummy cell for persistents
                    {
                    curWorldCell = new FNV::CELLRecord();
                    curWorldCell->formID = FormIDHandler.NextExpandedFormID();
                    curWorldCell->Parent = curWorld;
                    curWorldCell->IsHasWater(true);
                    curWorldCell->IsPersistent(true);
                    curWorldCell->XCLC.Load();
                    }

                if(curWorldCell != NULL || curWorld->CELLS.size() > 0)
                    {
                    gType = eWorld;
                    writer.file_write(&type, 4);
                    worldSizePos = writer.file_tell();
                    writer.file_write(&worldSize, 4); //Placeholder: will be overwritten with correct value later.
                    writer.file_write(&worldFormID, 4);
                    writer.file_write(&gType, 4);
                    writer.file_write(&stamp, 4);
                    writer.file_write(&unknown, 4);
                    ++formCount;
                    worldSize = 24;

                    if(curWorldCell != NULL)
                        {
                        curCell = curWorldCell;
                        cellFormID = curCell->formID;
                        collapser.Accept(cellFormID);
                        worldSize += curCell->Write(writer, bMastersChanged, expander, collapser, Expanders);
                        ++formCount;

                        if(curCell->LAND != NULL)
                            Temporary.push_back(curCell->LAND);
                        if(CloseMod)
                            curCell->LAND = NULL;

                        for(UINT32 y = 0; y < curCell->ACHR.size(); ++y)
                            {
                            if(curCell->ACHR[y]->IsPersistent())
                                Persistent.push_back(curCell->ACHR[y]);
                            else if(curCell->ACHR[y]->IsVWD())
                                {
                                VWD.push_back(curCell->ACHR[y]);
                                delete curCell->ACHR[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->ACHR[y]);
                                delete curCell->ACHR[y];
                                }
                            }
                        if(CloseMod)
                            curCell->ACHR.clear();

                        for(UINT32 y = 0; y < curCell->ACRE.size(); ++y)
                            {
                            if(curCell->ACRE[y]->IsPersistent())
                                Persistent.push_back(curCell->ACRE[y]);
                            else if(curCell->ACRE[y]->IsVWD())
                                {
                                VWD.push_back(curCell->ACRE[y]);
                                delete curCell->ACRE[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->ACRE[y]);
                                delete curCell->ACRE[y];
                                }
                            }
                        if(CloseMod)
                            curCell->ACRE.clear();

                        for(UINT32 y = 0; y < curCell->REFR.size(); ++y)
                            {
                            if(curCell->REFR[y]->IsPersistent())
                                Persistent.push_back(curCell->REFR[y]);
                            else if(curCell->REFR[y]->IsVWD())
                                {
                                VWD.push_back(curCell->REFR[y]);
                                delete curCell->REFR[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->REFR[y]);
                                delete curCell->REFR[y];
                                }
                            }
                        if(CloseMod)
                            curCell->REFR.clear();

                        for(UINT32 y = 0; y < curCell->PGRE.size(); ++y)
                            {
                            if(curCell->PGRE[y]->IsPersistent())
                                Persistent.push_back(curCell->PGRE[y]);
                            else if(curCell->PGRE[y]->IsVWD())
                                {
                                VWD.push_back(curCell->PGRE[y]);
                                delete curCell->PGRE[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->PGRE[y]);
                                delete curCell->PGRE[y];
                                }
                            }
                        if(CloseMod)
                            curCell->PGRE.clear();

                        for(UINT32 y = 0; y < curCell->PMIS.size(); ++y)
                            {
                            if(curCell->PMIS[y]->IsPersistent())
                                Persistent.push_back(curCell->PMIS[y]);
                            else if(curCell->PMIS[y]->IsVWD())
                                {
                                VWD.push_back(curCell->PMIS[y]);
                                delete curCell->PMIS[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->PMIS[y]);
                                delete curCell->PMIS[y];
                                }
                            }
                        if(CloseMod)
                            curCell->PMIS.clear();

                        for(UINT32 y = 0; y < curCell->PBEA.size(); ++y)
                            {
                            if(curCell->PBEA[y]->IsPersistent())
                                Persistent.push_back(curCell->PBEA[y]);
                            else if(curCell->PBEA[y]->IsVWD())
                                {
                                VWD.push_back(curCell->PBEA[y]);
                                delete curCell->PBEA[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->PBEA[y]);
                                delete curCell->PBEA[y];
                                }
                            }
                        if(CloseMod)
                            curCell->PBEA.clear();

                        for(UINT32 y = 0; y < curCell->PFLA.size(); ++y)
                            {
                            if(curCell->PFLA[y]->IsPersistent())
                                Persistent.push_back(curCell->PFLA[y]);
                            else if(curCell->PFLA[y]->IsVWD())
                                {
                                VWD.push_back(curCell->PFLA[y]);
                                delete curCell->PFLA[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->PFLA[y]);
                                delete curCell->PFLA[y];
                                }
                            }
                        if(CloseMod)
                            curCell->PFLA.clear();

                        for(UINT32 y = 0; y < curCell->PCBE.size(); ++y)
                            {
                            if(curCell->PCBE[y]->IsPersistent())
                                Persistent.push_back(curCell->PCBE[y]);
                            else if(curCell->PCBE[y]->IsVWD())
                                {
                                VWD.push_back(curCell->PCBE[y]);
                                delete curCell->PCBE[y];
                                }
                            else
                                {
                                Temporary.push_back(curCell->PCBE[y]);
                                delete curCell->PCBE[y];
                                }
                            }
                        if(CloseMod)
                            curCell->PCBE.clear();

                        for(UINT32 y = 0; y < curCell->NAVM.size(); ++y)
                            {
                            Temporary.push_back(curCell->NAVM[y]);
                            delete curCell->NAVM[y];
                            }
                        if(CloseMod)
                            curCell->NAVM.clear();

                        if(VWD.size() || Temporary.size())
                            printer("FNVGRUPRecords<FNV::WRLDRecord>::WriteGRUP: Warning - Information lost. Ignored %u VWD or Temporary records in the world cell: %08X", VWD.size() + Temporary.size(), worldFormID);

                        VWD.clear();
                        Temporary.clear();

                        numChildren = (UINT32)Persistent.size() + (UINT32)FixedPersistent.size();
                        if(numChildren)
                            {
                            formCount += numChildren;
                            gType = eCellChildren;
                            writer.file_write(&type, 4);
                            childrenSizePos = writer.file_tell();
                            writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&cellFormID, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            writer.file_write(&unknown, 4);
                            ++formCount;
                            childrenSize = 24;

                            //World CELL should only have persistent objects in it
                            gType = eCellPersistent;
                            writer.file_write(&type, 4);
                            childSizePos = writer.file_tell();
                            writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&cellFormID, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            writer.file_write(&unknown, 4);
                            ++formCount;
                            childSize = 24;

                            numChild = (UINT32)Persistent.size();
                            for(UINT32 y = 0; y < numChild; ++y)
                                {
                                childSize += Persistent[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                if(CloseMod)
                                    delete Persistent[y];
                                }

                            //The moved persistents will be deleted by their owning cell when its indexed
                            numChild = (UINT32)FixedPersistent.size();
                            for(UINT32 y = 0; y < numChild; ++y)
                                childSize += FixedPersistent[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                            childrenSize += childSize;
                            writer.file_write(childSizePos, &childSize, 4);
                            Persistent.clear();
                            FixedPersistent.clear();
                            worldSize += childrenSize;
                            writer.file_write(childrenSizePos, &childrenSize, 4);
                            }
                        if(CloseMod)
                            delete curCell;
                        }

                    formCount += (UINT32)curWorld->CELLS.size();
                    for(std::map<UINT32, std::map<UINT32, std::vector<FNV::CELLRecord *> > >::iterator curBlock = BlockedRecords.begin(); curBlock != BlockedRecords.end(); ++curBlock)
                        {
                        gType = eExteriorBlock;
                        writer.file_write(&type, 4);
                        blockSizePos = writer.file_tell();
                        writer.file_write(&blockSize, 4); //Placeholder: will be overwritten with correct value later.
                        writer.file_write(&curBlock->first, 4);
                        writer.file_write(&gType, 4);
                        writer.file_write(&stamp, 4);
                        writer.file_write(&unknown, 4);
                        ++formCount;
                        blockSize = 24;

                        for(std::map<UINT32, std::vector<FNV::CELLRecord *> >::iterator curSubBlock = curBlock->second.begin(); curSubBlock != curBlock->second.end(); ++curSubBlock)
                            {
                            gType = eExteriorSubBlock;
                            writer.file_write(&type, 4);
                            subBlockSizePos = writer.file_tell();
                            writer.file_write(&subBlockSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&curSubBlock->first, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            writer.file_write(&unknown, 4);
                            ++formCount;
                            subBlockSize = 24;

                            numSubBlocks = (UINT32)curSubBlock->second.size();
                            for(UINT32 p = 0; p < numSubBlocks; ++p)
                                {
                                curCell = curSubBlock->second[p];
                                cellFormID = curCell->formID;
                                collapser.Accept(cellFormID);
                                subBlockSize += curCell->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                //Place the PGRD, ACHR, ACRE, and REFR records into their proper GRUP

                                if(curCell->LAND != NULL)
                                    Temporary.push_back(curCell->LAND);
                                if(CloseMod)
                                    curCell->LAND = NULL;

                                for(UINT32 y = 0; y < curCell->ACHR.size(); ++y)
                                    {
                                    if(curCell->ACHR[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->ACHR[y];
                                        }
                                    else if(curCell->ACHR[y]->IsVWD())
                                        VWD.push_back(curCell->ACHR[y]);
                                    else
                                        Temporary.push_back(curCell->ACHR[y]);
                                    }
                                if(CloseMod)
                                    curCell->ACHR.clear();

                                for(UINT32 y = 0; y < curCell->ACRE.size(); ++y)
                                    {
                                    if(curCell->ACRE[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->ACRE[y];
                                        }
                                    else if(curCell->ACRE[y]->IsVWD())
                                        VWD.push_back(curCell->ACRE[y]);
                                    else
                                        Temporary.push_back(curCell->ACRE[y]);
                                    }
                                if(CloseMod)
                                    curCell->ACRE.clear();

                                for(UINT32 y = 0; y < curCell->REFR.size(); ++y)
                                    {
                                    if(curCell->REFR[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->REFR[y];
                                        }
                                    else if(curCell->REFR[y]->IsVWD())
                                        VWD.push_back(curCell->REFR[y]);
                                    else
                                        Temporary.push_back(curCell->REFR[y]);
                                    }
                                if(CloseMod)
                                    curCell->REFR.clear();

                                for(UINT32 y = 0; y < curCell->PGRE.size(); ++y)
                                    {
                                    if(curCell->PGRE[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->PGRE[y];
                                        }
                                    else if(curCell->PGRE[y]->IsVWD())
                                        VWD.push_back(curCell->PGRE[y]);
                                    else
                                        Temporary.push_back(curCell->PGRE[y]);
                                    }
                                if(CloseMod)
                                    curCell->PGRE.clear();

                                for(UINT32 y = 0; y < curCell->PMIS.size(); ++y)
                                    {
                                    if(curCell->PMIS[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->PMIS[y];
                                        }
                                    else if(curCell->PMIS[y]->IsVWD())
                                        VWD.push_back(curCell->PMIS[y]);
                                    else
                                        Temporary.push_back(curCell->PMIS[y]);
                                    }
                                if(CloseMod)
                                    curCell->PMIS.clear();

                                for(UINT32 y = 0; y < curCell->PBEA.size(); ++y)
                                    {
                                    if(curCell->PBEA[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->PBEA[y];
                                        }
                                    else if(curCell->PBEA[y]->IsVWD())
                                        VWD.push_back(curCell->PBEA[y]);
                                    else
                                        Temporary.push_back(curCell->PBEA[y]);
                                    }
                                if(CloseMod)
                                    curCell->PBEA.clear();

                                for(UINT32 y = 0; y < curCell->PFLA.size(); ++y)
                                    {
                                    if(curCell->PFLA[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->PFLA[y];
                                        }
                                    else if(curCell->PFLA[y]->IsVWD())
                                        VWD.push_back(curCell->PFLA[y]);
                                    else
                                        Temporary.push_back(curCell->PFLA[y]);
                                    }
                                if(CloseMod)
                                    curCell->PFLA.clear();

                                for(UINT32 y = 0; y < curCell->PCBE.size(); ++y)
                                    {
                                    if(curCell->PCBE[y]->IsPersistent())
                                        {
                                        if(CloseMod)
                                            delete curCell->PCBE[y];
                                        }
                                    else if(curCell->PCBE[y]->IsVWD())
                                        VWD.push_back(curCell->PCBE[y]);
                                    else
                                        Temporary.push_back(curCell->PCBE[y]);
                                    }
                                if(CloseMod)
                                    curCell->PCBE.clear();

                                for(UINT32 y = 0; y < curCell->NAVM.size(); ++y)
                                    Temporary.push_back(curCell->NAVM[y]);
                                if(CloseMod)
                                    curCell->NAVM.clear();

                                numChildren = (UINT32)VWD.size() + (UINT32)Temporary.size();
                                if(numChildren)
                                    {
                                    formCount += numChildren;
                                    gType = eCellChildren;
                                    writer.file_write(&type, 4);
                                    childrenSizePos = writer.file_tell();
                                    writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&cellFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    writer.file_write(&unknown, 4);
                                    ++formCount;
                                    childrenSize = 24;

                                    numChild = (UINT32)VWD.size();
                                    if(numChild)
                                        {
                                        gType = eCellVWD;
                                        writer.file_write(&type, 4);
                                        childSizePos = writer.file_tell();
                                        writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                        writer.file_write(&cellFormID, 4);
                                        writer.file_write(&gType, 4);
                                        writer.file_write(&stamp, 4);
                                        writer.file_write(&unknown, 4);
                                        ++formCount;
                                        childSize = 24;

                                        for(UINT32 x = 0; x < numChild; ++x)
                                            {
                                            childSize += VWD[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                            if(CloseMod)
                                                delete VWD[x];
                                            }
                                        childrenSize += childSize;
                                        writer.file_write(childSizePos, &childSize, 4);
                                        VWD.clear();
                                        }

                                    numChild = (UINT32)Temporary.size();
                                    if(numChild)
                                        {
                                        gType = eCellTemporary;
                                        writer.file_write(&type, 4);
                                        childSizePos = writer.file_tell();
                                        writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                        writer.file_write(&cellFormID, 4);
                                        writer.file_write(&gType, 4);
                                        writer.file_write(&stamp, 4);
                                        writer.file_write(&unknown, 4);
                                        ++formCount;
                                        childSize = 24;

                                        for(UINT32 x = 0; x < numChild; ++x)
                                            {
                                            childSize += Temporary[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                            if(CloseMod)
                                                delete Temporary[x];
                                            }
                                        childrenSize += childSize;
                                        writer.file_write(childSizePos, &childSize, 4);
                                        Temporary.clear();
                                        }
                                    subBlockSize += childrenSize;
                                    writer.file_write(childrenSizePos, &childrenSize, 4);
                                    }
                                if(CloseMod)
                                    delete curCell;
                                }
                            blockSize += subBlockSize;
                            writer.file_write(subBlockSizePos, &subBlockSize, 4);
                            curSubBlock->second.clear();
                            }
                        worldSize += blockSize;
                        writer.file_write(blockSizePos, &blockSize, 4);
                        curBlock->second.clear();
                        }
                    TopSize += worldSize;
                    writer.file_write(worldSizePos, &worldSize, 4);
                    }
                BlockedRecords.clear();
                }
            if(CloseMod)
                Records.clear();
            writer.file_write(TopSizePos, &TopSize, 4);

            return formCount;
            }
    };