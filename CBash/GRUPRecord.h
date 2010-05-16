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
#include "BaseRecord.h"
#include "Records/GMSTRecord.h"
#include "Records/DIALRecord.h"
#include "Records/INFORecord.h"
#include "Records/CELLRecord.h"
#include "Records/WRLDRecord.h"
#include <vector>
#include <math.h>

template<class T>
class GRUPRecords
    {
    public:
        unsigned int stamp;
        bool SkimmedGRUP, LoadedGRUP;
        std::vector<T *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false), LoadedGRUP(false) {}
        ~GRUPRecords()
            {
            for(unsigned int p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(boost::threadpool::pool &Threads, unsigned char *fileBuffer, _FormIDHandler &FormIDHandler, const bool &FullLoad, unsigned int &gSize, unsigned int curPos)
            {
            if(SkimmedGRUP || gSize == 0)
                return false;
            SkimmedGRUP = true;
            //LoadedGRUP = FullLoad;
            T * curRecord = NULL;
            unsigned int gEnd = curPos + gSize - 20;
            unsigned int recordSize = 0;
            //boost::threadpool::pool Threads(NUMTHREADS);
            while(curPos < gEnd){
                curRecord = new T();
                curPos += 4; //Skip type field
                recordSize = *(unsigned int*)&fileBuffer[curPos];
                curPos += 4; //size of recordSize
                _readBuffer(&curRecord->flags, fileBuffer, 4, curPos);
                _readBuffer(&curRecord->formID, fileBuffer, 4, curPos);
                _readBuffer(&curRecord->flagsUnk, fileBuffer, 4, curPos);
                if(curRecord->IsLoaded())
                    printf("Flag used!!!!\n");
                curRecord->recStart = curPos;
                FormIDHandler.ExpandFormID(curRecord->formID);
                curPos += recordSize;
                if(FullLoad)
                    {
                    Threads.schedule(boost::bind(&Record::Read, curRecord, fileBuffer, boost::ref(FormIDHandler)));
                    //curRecord->Read(fileBuffer, FormIDHandler);
                    }
                Records.push_back(curRecord);
                };
            return true;
            }
        bool Read(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler)
            {
            if(LoadedGRUP || !SkimmedGRUP)
                return false;
            LoadedGRUP = true;
            for(unsigned int p = 0; p < Records.size(); p++)
                Records[p]->Read(fileBuffer, FormIDHandler);
            return true;
            }
        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                Records[p]->CollapseFormIDs(FormIDHandler);
                }
            return;
            }
        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                Records[p]->ExpandFormIDs(FormIDHandler);
                }
            return;
            }
        void GetSizes(std::vector<unsigned int> &RecordSizes)
            {
            unsigned int numRecords = (unsigned int)Records.size();
            if(numRecords == 0)
                return;
            RecordSizes.resize(numRecords + 1);
            RecordSizes[0] = numRecords * 20; //Accounts for all record headers
            for(unsigned int p = 0; p < numRecords; p++)
                RecordSizes[0] += RecordSizes[p + 1] = Records[p]->GetSize();
            RecordSizes[0] += 20; //Top GRUP
            return;
            }
        void WriteGRUP(std::vector<unsigned int> &RecordSizes, unsigned int TopLabel, int *fh, unsigned char *buffer, unsigned int &usedBuffer)
            {
            if(Records.size() == 0)
                return;
            unsigned int type = eGRUP;
            unsigned int gType = eTop;
            _writeBuffer(buffer, &type, 4, usedBuffer);
            _writeBuffer(buffer, &RecordSizes[0], 4, usedBuffer);
            _writeBuffer(buffer, &TopLabel, 4, usedBuffer);
            _writeBuffer(buffer, &gType, 4, usedBuffer);
            _writeBuffer(buffer, &stamp, 4, usedBuffer);
            for(unsigned int p = 0; p < Records.size(); p++)
                Records[p]->Write(fh, buffer, RecordSizes[1 + p], usedBuffer);
            }
        #ifdef _DEBUG
        void Debug(int debugLevel)
            {
            if(debugLevel > 2)
                for(std::vector<T*>::iterator curRecord = Records.begin();curRecord!=Records.end();curRecord++)
                    (*curRecord)->Debug(debugLevel);
            }
        #endif
    };

template<>
class GRUPRecords<DIALRecord>
    {
    public:
        enum subGRUPs {
            eINFO = 0x4F464E49
            };
        unsigned int stamp;
        bool SkimmedGRUP, LoadedGRUP;
        std::vector<DIALRecord *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false), LoadedGRUP(false) {}
        ~GRUPRecords()
            {
            for(unsigned int p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(boost::threadpool::pool &Threads, unsigned char *fileBuffer, _FormIDHandler &FormIDHandler, const bool &FullLoad, unsigned int &gSize, unsigned int curPos)
            {
            if(SkimmedGRUP || gSize == 0)
                return false;
            SkimmedGRUP = true;
            DIALRecord * curDIALRecord = NULL;
            INFORecord * curINFORecord = NULL;
            unsigned int recordType = 0;
            unsigned int gEnd = curPos + gSize - 20;
            unsigned int recordSize = 0;
            //boost::threadpool::pool Threads(NUMTHREADS);

            while(curPos < gEnd){
                _readBuffer(&recordType, fileBuffer, 4, curPos);
                _readBuffer(&recordSize, fileBuffer, 4, curPos);
                switch(recordType)
                    {
                    case eDIAL:
                        curDIALRecord = new DIALRecord();
                        _readBuffer(&curDIALRecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curDIALRecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curDIALRecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curDIALRecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curDIALRecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curDIALRecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curDIALRecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curDIALRecord->Read(fileBuffer, FormIDHandler);
                            }
                        Records.push_back(curDIALRecord);
                        break;
                    case eGRUP: //All GRUPs will be recreated from scratch on write (saves memory)
                        curPos += 8;
                        _readBuffer(&stamp, fileBuffer, 4, curPos);
                        break;
                    case eINFO:
                        curINFORecord = new INFORecord();
                        _readBuffer(&curINFORecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curINFORecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curINFORecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curINFORecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curINFORecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curINFORecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curINFORecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curINFORecord->Read(fileBuffer, FormIDHandler);
                            }
                        curDIALRecord->INFO.push_back(curINFORecord);
                        break;
                    default:
                        printf("  DIAL: Unexpected Field = %04x\n", recordType);
                        printf("  Size = %u\n", recordSize);
                        printf("  CurPos = %04x\n\n", curPos - 20);
                        curPos += recordSize;
                        break;
                    }
                };
            return true;
            }
        bool Read(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler)
            {
            if(LoadedGRUP || !SkimmedGRUP)
                return false;
            LoadedGRUP = true;
            DIALRecord * curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                curRecord->Read(fileBuffer, FormIDHandler);
                for(unsigned int x = 0; x < curRecord->INFO.size(); ++x)
                    curRecord->INFO[x]->Read(fileBuffer, FormIDHandler);
                }
            return true;
            }
        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            DIALRecord * curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                curRecord->CollapseFormIDs(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->INFO.size(); ++x)
                    curRecord->INFO[x]->CollapseFormIDs(FormIDHandler);
                }
            return;
            }
        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            DIALRecord * curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                curRecord->ExpandFormIDs(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->INFO.size(); ++x)
                    curRecord->INFO[x]->ExpandFormIDs(FormIDHandler);
                }
            return;
            }
        unsigned int GetSizes(std::vector<WritableDialogue> &WriteInfo)
            {
            unsigned int GRUPCount = (unsigned int)Records.size(); //Parent Records
            unsigned int numDIALRecords = GRUPCount;
            unsigned int numINFORecords;
            if(numDIALRecords == 0)
                return 0;
            DIALRecord *curRecord = NULL;
            WriteInfo.resize(numDIALRecords + 1);
            ++GRUPCount; //Top GRUP
            WriteInfo[0].CellSize = 20; //Top GRUP
            WriteInfo[0].CellSize += numDIALRecords * 20; //Accounts for all DIAL record headers
            for(unsigned int p = 0; p < numDIALRecords; ++p)
                {
                curRecord = Records[p];
                WriteInfo[0].CellSize += WriteInfo[p + 1].CellSize = curRecord->GetSize();
                numINFORecords = (unsigned int)curRecord->INFO.size();
                if(numINFORecords)
                    {
                    ++GRUPCount; //Children GRUP
                    GRUPCount += numINFORecords; //Children Records
                    WriteInfo[p + 1].ChildrenSize = 20; //Children GRUP
                    WriteInfo[p + 1].ChildrenSize += numINFORecords * 20; //Accounts for all INFO record headers
                    WriteInfo[p + 1].ChildrenSizes.resize(numINFORecords);
                    for(unsigned int y = 0; y < numINFORecords; ++y)
                        WriteInfo[p + 1].ChildrenSize += WriteInfo[p + 1].ChildrenSizes[y] = curRecord->INFO[y]->GetSize();
                    WriteInfo[0].CellSize += WriteInfo[p + 1].ChildrenSize;
                    }
                }
            return GRUPCount;
            }
        void WriteGRUP(std::vector<WritableDialogue> &WriteInfo, int *fh, unsigned char *buffer, unsigned int &usedBuffer)
            {
            if(Records.size() == 0)
                return;
            DIALRecord *curRecord = NULL;
            unsigned int type = eGRUP;
            unsigned int TopLabel = eDIAL;
            unsigned int gType = eTop;
            _writeBuffer(buffer, &type, 4, usedBuffer);
            _writeBuffer(buffer, &WriteInfo[0].CellSize, 4, usedBuffer);
            _writeBuffer(buffer, &TopLabel, 4, usedBuffer);
            _writeBuffer(buffer, &gType, 4, usedBuffer);
            _writeBuffer(buffer, &stamp, 4, usedBuffer);
            gType = eTopicChildren;
            for(unsigned int p = 0; p < Records.size(); ++p)
                {
                curRecord = Records[p];
                curRecord->Write(fh, buffer, WriteInfo[1 + p].CellSize, usedBuffer);
                if(curRecord->INFO.size())
                    {
                    _writeBuffer(buffer, &type, 4, usedBuffer);
                    _writeBuffer(buffer, &WriteInfo[1 + p].ChildrenSize, 4, usedBuffer);
                    _writeBuffer(buffer, &curRecord->formID, 4, usedBuffer);
                    _writeBuffer(buffer, &gType, 4, usedBuffer);
                    _writeBuffer(buffer, &stamp, 4, usedBuffer);
                    for(unsigned int x = 0; x < curRecord->INFO.size(); ++x)
                        curRecord->INFO[x]->Write(fh, buffer, WriteInfo[1 + p].ChildrenSizes[x], usedBuffer);
                    }
                }
            }
        #ifdef _DEBUG
        void Debug(int debugLevel)
            {
            if(debugLevel > 2)
                for(std::vector<DIALRecord *>::iterator curRecord = Records.begin();curRecord!=Records.end();curRecord++)
                    (*curRecord)->Debug(debugLevel);
            }
        #endif
    };

template<>
class GRUPRecords<CELLRecord>
    {
    public:
        enum subGRUPs {
            eACHR = 0x52484341,
            eACRE = 0x45524341,
            eREFR = 0x52464552,
            ePGRD = 0x44524750
            };
        unsigned int stamp;
        bool SkimmedGRUP, LoadedGRUP;
        std::vector<CELLRecord *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false), LoadedGRUP(false) {}
        ~GRUPRecords()
            {
            for(unsigned int p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(boost::threadpool::pool &Threads, unsigned char *fileBuffer, _FormIDHandler &FormIDHandler, const bool &FullLoad, unsigned int &gSize, unsigned int curPos)
            {
            if(SkimmedGRUP || gSize == 0)
                return false;
            SkimmedGRUP = true;
            CELLRecord *curCELLRecord = NULL;
            ACHRRecord *curACHRRecord = NULL;
            ACRERecord *curACRERecord = NULL;
            REFRRecord *curREFRRecord = NULL;
            unsigned int recordType = 0;
            unsigned int gEnd = curPos + gSize - 20;
            unsigned int recordSize = 0;
            //boost::threadpool::pool Threads(NUMTHREADS);

            while(curPos < gEnd){
                _readBuffer(&recordType, fileBuffer, 4, curPos);
                _readBuffer(&recordSize, fileBuffer, 4, curPos);
                switch(recordType)
                    {
                    case eCELL:
                        curCELLRecord = new CELLRecord();
                        _readBuffer(&curCELLRecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curCELLRecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curCELLRecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curCELLRecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curCELLRecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curCELLRecord->Read(fileBuffer, FormIDHandler);
                            }
                        Records.push_back(curCELLRecord);
                        break;
                    case eGRUP: //All GRUPs will be recreated from scratch on write (saves memory)
                        curPos += 12;
                        break;
                    case eACHR:
                        curACHRRecord = new ACHRRecord();
                        _readBuffer(&curACHRRecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curACHRRecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curACHRRecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curACHRRecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curACHRRecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curACHRRecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curACHRRecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curACHRRecord->Read(fileBuffer, FormIDHandler);
                            }
                        curCELLRecord->ACHR.push_back(curACHRRecord);
                        break;
                    case eACRE:
                        curACRERecord = new ACRERecord();
                        _readBuffer(&curACRERecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curACRERecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curACRERecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curACRERecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curACRERecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curACRERecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curACRERecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curACRERecord->Read(fileBuffer, FormIDHandler);
                            }
                        curCELLRecord->ACRE.push_back(curACRERecord);
                        break;
                    case eREFR:
                        curREFRRecord = new REFRRecord();
                        _readBuffer(&curREFRRecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curREFRRecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curREFRRecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curREFRRecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curREFRRecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curREFRRecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curREFRRecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curREFRRecord->Read(fileBuffer, FormIDHandler);
                            }
                        curCELLRecord->REFR.push_back(curREFRRecord);
                        break;
                    case ePGRD:
                        delete curCELLRecord->PGRD;
                        curCELLRecord->PGRD = new PGRDRecord();
                        _readBuffer(&curCELLRecord->PGRD->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->PGRD->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->PGRD->flagsUnk, fileBuffer, 4, curPos);
                        if(curCELLRecord->PGRD->IsLoaded())
                            printf("Flag used!!!!\n");
                        curCELLRecord->PGRD->recStart = curPos;
                        FormIDHandler.ExpandFormID(curCELLRecord->PGRD->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curCELLRecord->PGRD, fileBuffer, boost::ref(FormIDHandler)));
                            //curCELLRecord->PGRD->Read(fileBuffer, FormIDHandler);
                            }
                        break;
                    default:
                        printf("  CELL: Unexpected Record = %04x\n", recordType);
                        printf("  Size = %u\n", recordSize);
                        printf("  CurPos = %04x\n\n", curPos - 20);
                        curPos += recordSize;
                        break;
                    }
                };
            return true;
            }
        bool Read(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler)
            {
            if(LoadedGRUP || !SkimmedGRUP)
                return false;
            LoadedGRUP = true;
            CELLRecord *curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                curRecord->Read(fileBuffer, FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACHR.size(); ++x)
                    curRecord->ACHR[x]->Read(fileBuffer, FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACRE.size(); ++x)
                    curRecord->ACRE[x]->Read(fileBuffer, FormIDHandler);
                for(unsigned int x = 0; x < curRecord->REFR.size(); ++x)
                    curRecord->REFR[x]->Read(fileBuffer, FormIDHandler);
                if(curRecord->PGRD != NULL)
                    curRecord->PGRD->Read(fileBuffer, FormIDHandler);
                }
            return true;
            }
        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            CELLRecord *curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                curRecord->CollapseFormIDs(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACHR.size(); ++x)
                    curRecord->ACHR[x]->CollapseFormIDs(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACRE.size(); ++x)
                    curRecord->ACRE[x]->CollapseFormIDs(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->REFR.size(); ++x)
                    curRecord->REFR[x]->CollapseFormIDs(FormIDHandler);
                if(curRecord->PGRD != NULL)
                    curRecord->PGRD->CollapseFormIDs(FormIDHandler);
                }
            return;
            }
        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            CELLRecord *curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                curRecord->ExpandFormIDs(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACHR.size(); ++x)
                    curRecord->ACHR[x]->ExpandFormIDs(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACRE.size(); ++x)
                    curRecord->ACRE[x]->ExpandFormIDs(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->REFR.size(); ++x)
                    curRecord->REFR[x]->ExpandFormIDs(FormIDHandler);
                if(curRecord->PGRD != NULL)
                    curRecord->PGRD->ExpandFormIDs(FormIDHandler);
                }
            return;
            }
        unsigned int GetSizes(unsigned int &TopSize, std::vector< std::vector< std::vector<WritableCell> > > &BlockedRecords, std::vector<unsigned int> &BlockHeaders, std::vector< std::vector<unsigned int> > &SubBlockHeaders)
            {
            unsigned int numRecords = (unsigned int)Records.size();
            if(numRecords == 0)
                return 0;
            unsigned int GRUPCount = numRecords;
            unsigned int curSize = 0;
            int ObjectID, BlockIndex, SubBlockIndex;
            CELLRecord *curRecord = NULL;
            WritableCell curICELL;
            BlockedRecords.reserve(numRecords);
            TopSize = (numRecords * 20) + 20; //Accounts for all Cell record headers and itself
            ++GRUPCount; //Top GRUP
            for(unsigned int x = 0; x < numRecords; ++x)
                {
                curICELL.curRecord = curRecord = Records[x];
                curICELL.CellSize = curRecord->GetSize();
                curICELL.ChildrenSize = 0;
                curICELL.PersistentSize = 0;
                curICELL.Persistent.clear();
                curICELL.PersistentSizes.clear();
                curICELL.VWDSize = 0;
                curICELL.VWD.clear();
                curICELL.VWDSizes.clear();
                curICELL.TemporarySize = 0;
                curICELL.Temporary.clear();
                curICELL.TemporarySizes.clear();

                TopSize += curICELL.CellSize; //Record Header

                if(curRecord->PGRD != NULL)
                    {
                    curICELL.TemporarySize += 20; //Record Header
                    curICELL.TemporarySize += curSize = curRecord->PGRD->GetSize();
                    curICELL.Temporary.push_back(curRecord->PGRD);
                    curICELL.TemporarySizes.push_back(curSize);
                    }

                for(unsigned int y = 0; y < curRecord->ACHR.size(); ++y)
                    {
                    if(curRecord->ACHR[y]->IsPersistent())
                        {
                        curICELL.PersistentSize += 20; //Record Header
                        curICELL.PersistentSize += curSize = curRecord->ACHR[y]->GetSize();
                        curICELL.Persistent.push_back(curRecord->ACHR[y]);
                        curICELL.PersistentSizes.push_back(curSize);
                        }
                    else if(curRecord->ACHR[y]->IsVWD())
                        {
                        curICELL.VWDSize += 20; //Record Header
                        curICELL.VWDSize += curSize = curRecord->ACHR[y]->GetSize();
                        curICELL.VWD.push_back(curRecord->ACHR[y]);
                        curICELL.VWDSizes.push_back(curSize);
                        }
                    else
                        {
                        curICELL.TemporarySize += 20; //Record Header
                        curICELL.TemporarySize += curSize = curRecord->ACHR[y]->GetSize();
                        curICELL.Temporary.push_back(curRecord->ACHR[y]);
                        curICELL.TemporarySizes.push_back(curSize);
                        }
                    }

                for(unsigned int y = 0; y < curRecord->ACRE.size(); ++y)
                    {
                    if(curRecord->ACRE[y]->IsPersistent())
                        {
                        curICELL.PersistentSize += 20; //Record Header
                        curICELL.PersistentSize += curSize = curRecord->ACRE[y]->GetSize();
                        curICELL.Persistent.push_back(curRecord->ACRE[y]);
                        curICELL.PersistentSizes.push_back(curSize);
                        }
                    else if(curRecord->ACRE[y]->IsVWD())
                        {
                        curICELL.VWDSize += 20; //Record Header
                        curICELL.VWDSize += curSize = curRecord->ACRE[y]->GetSize();
                        curICELL.VWD.push_back(curRecord->ACRE[y]);
                        curICELL.VWDSizes.push_back(curSize);
                        }
                    else
                        {
                        curICELL.TemporarySize += 20; //Record Header
                        curICELL.TemporarySize += curSize = curRecord->ACRE[y]->GetSize();
                        curICELL.Temporary.push_back(curRecord->ACRE[y]);
                        curICELL.TemporarySizes.push_back(curSize);
                        }
                    }

                for(unsigned int y = 0; y < curRecord->REFR.size(); ++y)
                    {
                    if(curRecord->REFR[y]->IsPersistent())
                        {
                        curICELL.PersistentSize += 20; //Record Header
                        curICELL.PersistentSize += curSize = curRecord->REFR[y]->GetSize();
                        curICELL.Persistent.push_back(curRecord->REFR[y]);
                        curICELL.PersistentSizes.push_back(curSize);
                        }
                    else if(curRecord->REFR[y]->IsVWD())
                        {
                        curICELL.VWDSize += 20; //Record Header
                        curICELL.VWDSize += curSize = curRecord->REFR[y]->GetSize();
                        curICELL.VWD.push_back(curRecord->REFR[y]);
                        curICELL.VWDSizes.push_back(curSize);
                        }
                    else
                        {
                        curICELL.TemporarySize += 20; //Record Header
                        curICELL.TemporarySize += curSize = curRecord->REFR[y]->GetSize();
                        curICELL.Temporary.push_back(curRecord->REFR[y]);
                        curICELL.TemporarySizes.push_back(curSize);
                        }
                    }
                //Account for GRUPs
                GRUPCount += (unsigned int)curRecord->ACHR.size();
                GRUPCount += (unsigned int)curRecord->ACRE.size();
                GRUPCount += (unsigned int)curRecord->REFR.size();
                if(curICELL.PersistentSize)
                    ++GRUPCount, curICELL.PersistentSize += 20;
                if(curICELL.VWDSize)
                    ++GRUPCount, curICELL.VWDSize += 20;
                if(curICELL.TemporarySize)
                    ++GRUPCount, curICELL.TemporarySize += 20;
                curICELL.ChildrenSize += curICELL.PersistentSize + curICELL.VWDSize + curICELL.TemporarySize;
                if(curICELL.ChildrenSize)
                    ++GRUPCount, curICELL.ChildrenSize += 20;
                TopSize += curICELL.ChildrenSize;

                ObjectID = curRecord->formID & 0x00FFFFFF;
                BlockIndex = ObjectID % 10;
                SubBlockIndex = (ObjectID / 10) % 10;
                if(BlockHeaders[BlockIndex] == 0)
                    {
                    ++GRUPCount;
                    TopSize += 20;
                    BlockHeaders[BlockIndex] = 20;
                    }
                if(SubBlockHeaders[BlockIndex][SubBlockIndex] == 0)
                    {
                    ++GRUPCount;
                    TopSize += 20;
                    BlockHeaders[BlockIndex] += 20;
                    SubBlockHeaders[BlockIndex][SubBlockIndex] = 20;
                    }
                BlockHeaders[BlockIndex] += 20; //Cell Record Header
                SubBlockHeaders[BlockIndex][SubBlockIndex] += 20; //Cell Record Header
                BlockHeaders[BlockIndex] += curICELL.CellSize;
                BlockHeaders[BlockIndex] += curICELL.ChildrenSize;
                SubBlockHeaders[BlockIndex][SubBlockIndex] += curICELL.CellSize;
                SubBlockHeaders[BlockIndex][SubBlockIndex] += curICELL.ChildrenSize;

                BlockedRecords[BlockIndex][SubBlockIndex].push_back(curICELL);
                }
            return GRUPCount;
            }
        void WriteGRUP(unsigned int TopSize, std::vector< std::vector< std::vector<WritableCell> > > &BlockedRecords, std::vector<unsigned int> &BlockHeaders, std::vector< std::vector<unsigned int> > &SubBlockHeaders, int *fh, unsigned char *buffer, unsigned int &usedBuffer)
            {
            if(Records.size() == 0)
                return;

            CELLRecord *curRecord = NULL;
            WritableCell *curICELL = NULL;
            unsigned int type = eGRUP;
            unsigned int gLabel = eCELL;
            unsigned int gType = eTop;
            unsigned int gSize = 0;
            _writeBuffer(buffer, &type, 4, usedBuffer);
            _writeBuffer(buffer, &TopSize, 4, usedBuffer);
            _writeBuffer(buffer, &gLabel, 4, usedBuffer);
            _writeBuffer(buffer, &gType, 4, usedBuffer);
            _writeBuffer(buffer, &stamp, 4, usedBuffer);

            for(unsigned int curBlock = 0; curBlock < 10; ++curBlock)
                {
                gType = eInteriorBlock;
                for(unsigned int curSubBlock = 0; curSubBlock < 10; ++curSubBlock)
                    {
                    gSize = (unsigned int)BlockedRecords[curBlock][curSubBlock].size();
                    if(gSize != 0)
                        {
                        if(gType == eInteriorBlock)
                            {
                            _writeBuffer(buffer, &type, 4, usedBuffer);
                            _writeBuffer(buffer, &BlockHeaders[curBlock], 4, usedBuffer);
                            _writeBuffer(buffer, &curBlock, 4, usedBuffer);
                            _writeBuffer(buffer, &gType, 4, usedBuffer);
                            _writeBuffer(buffer, &stamp, 4, usedBuffer);
                            }
                        gType = eInteriorSubBlock;
                        _writeBuffer(buffer, &type, 4, usedBuffer);
                        _writeBuffer(buffer, &SubBlockHeaders[curBlock][curSubBlock], 4, usedBuffer);
                        _writeBuffer(buffer, &curSubBlock, 4, usedBuffer);
                        _writeBuffer(buffer, &gType, 4, usedBuffer);
                        _writeBuffer(buffer, &stamp, 4, usedBuffer);
                        for(unsigned int p = 0; p < gSize; ++p)
                            {
                            curICELL = &BlockedRecords[curBlock][curSubBlock][p];
                            curRecord = curICELL->curRecord;
                            curRecord->Write(fh, buffer, curICELL->CellSize, usedBuffer);

                            if(curICELL->ChildrenSize)
                                {
                                gType = eCellChildren;
                                _writeBuffer(buffer, &type, 4, usedBuffer);
                                _writeBuffer(buffer, &curICELL->ChildrenSize, 4, usedBuffer);
                                _writeBuffer(buffer, &curRecord->formID, 4, usedBuffer);
                                _writeBuffer(buffer, &gType, 4, usedBuffer);
                                _writeBuffer(buffer, &stamp, 4, usedBuffer);

                                if(curICELL->PersistentSize)
                                    {
                                    gType = eCellPersistent;
                                    _writeBuffer(buffer, &type, 4, usedBuffer);
                                    _writeBuffer(buffer, &curICELL->PersistentSize, 4, usedBuffer);
                                    _writeBuffer(buffer, &curRecord->formID, 4, usedBuffer);
                                    _writeBuffer(buffer, &gType, 4, usedBuffer);
                                    _writeBuffer(buffer, &stamp, 4, usedBuffer);
                                    for(unsigned int x = 0; x < curICELL->Persistent.size(); ++x)
                                        curICELL->Persistent[x]->Write(fh, buffer, curICELL->PersistentSizes[x], usedBuffer);
                                    }

                                if(curICELL->VWDSize)
                                    {
                                    gType = eCellVWD;
                                    _writeBuffer(buffer, &type, 4, usedBuffer);
                                    _writeBuffer(buffer, &curICELL->VWDSize, 4, usedBuffer);
                                    _writeBuffer(buffer, &curRecord->formID, 4, usedBuffer);
                                    _writeBuffer(buffer, &gType, 4, usedBuffer);
                                    _writeBuffer(buffer, &stamp, 4, usedBuffer);
                                    for(unsigned int x = 0; x < curICELL->VWD.size(); ++x)
                                        curICELL->VWD[x]->Write(fh, buffer, curICELL->VWDSizes[x], usedBuffer);
                                    }

                                if(curICELL->TemporarySize)
                                    {
                                    gType = eCellTemporary;
                                    _writeBuffer(buffer, &type, 4, usedBuffer);
                                    _writeBuffer(buffer, &curICELL->TemporarySize, 4, usedBuffer);
                                    _writeBuffer(buffer, &curRecord->formID, 4, usedBuffer);
                                    _writeBuffer(buffer, &gType, 4, usedBuffer);
                                    _writeBuffer(buffer, &stamp, 4, usedBuffer);
                                    for(unsigned int x = 0; x < curICELL->Temporary.size(); ++x)
                                        curICELL->Temporary[x]->Write(fh, buffer, curICELL->TemporarySizes[x], usedBuffer);
                                    }
                                }
                            }
                        }
                    }
                }
            return;
            }
        #ifdef _DEBUG
        void Debug(int debugLevel)
            {
            if(debugLevel > 2)
                for(std::vector<CELLRecord *>::iterator curRecord = Records.begin();curRecord!=Records.end();curRecord++)
                    (*curRecord)->Debug(debugLevel);
            }
        #endif
    };

template<>
class GRUPRecords<WRLDRecord>
    {
    public:
        //enum subGRUPs {
        //    eROAD = 0x44414F52
        //    };
        enum subGRUPs {
            eACHR = 0x52484341,
            eACRE = 0x45524341,
            eREFR = 0x52464552,
            eROAD = 0x44414F52,
            eLAND = 0x444E414C,
            ePGRD = 0x44524750
            };
        unsigned int stamp;
        bool SkimmedGRUP, LoadedGRUP;
        std::vector<WRLDRecord *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false), LoadedGRUP(false) {}
        ~GRUPRecords()
            {
            for(unsigned int p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(boost::threadpool::pool &Threads, unsigned char *fileBuffer, _FormIDHandler &FormIDHandler, const bool &FullLoad, unsigned int &gSize, unsigned int curPos)
            {
            if(SkimmedGRUP || gSize == 0)
                return false;
            SkimmedGRUP = true;
            WRLDRecord *curWRLDRecord = NULL;
            CELLRecord *curCELLRecord = NULL;
            CELLRecord *tempCELLRecord = NULL;
            ACHRRecord *curACHRRecord = NULL;
            ACRERecord *curACRERecord = NULL;
            REFRRecord *curREFRRecord = NULL;
            //std::vector< std::vector<LANDRecord *> > GridXY_LAND1;
            std::map<int, std::map<int, LANDRecord *> > GridXY_LAND;
            unsigned int lastGRUP = 0;
            unsigned int recordType = 0;
            unsigned int gEnd = curPos + gSize - 20;
            unsigned int recordSize = 0;
            //boost::threadpool::pool Threads(NUMTHREADS);

            while(curPos < gEnd){
                _readBuffer(&recordType, fileBuffer, 4, curPos);
                _readBuffer(&recordSize, fileBuffer, 4, curPos);
                switch(recordType)
                    {
                    case eWRLD:
                        curWRLDRecord = new WRLDRecord();
                        _readBuffer(&curWRLDRecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curWRLDRecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curWRLDRecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curWRLDRecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curWRLDRecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curWRLDRecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curWRLDRecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curWRLDRecord->Read(fileBuffer, FormIDHandler);
                            }
                        Records.push_back(curWRLDRecord);
                        break;
                    case eCELL:
                        switch(lastGRUP)
                            {
                            case eWorld:
                                delete curWRLDRecord->CELL;
                                curCELLRecord = curWRLDRecord->CELL = new CELLRecord();
                                break;
                            default:
                                curCELLRecord = new CELLRecord();
                                curWRLDRecord->CELLS.push_back(curCELLRecord);
                                break;
                            }
                        _readBuffer(&curCELLRecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curCELLRecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curCELLRecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curCELLRecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curCELLRecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curCELLRecord->Read(fileBuffer, FormIDHandler);
                            }
                        break;
                    case eGRUP: //All GRUPs will be recreated from scratch on write (saves memory)
                        curPos += 4;
                        _readBuffer(&lastGRUP, fileBuffer, 4, curPos);
                        curPos += 4;
                        break;
                    case eROAD:
                        delete curWRLDRecord->ROAD;
                        curWRLDRecord->ROAD = new ROADRecord();
                        _readBuffer(&curWRLDRecord->ROAD->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curWRLDRecord->ROAD->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curWRLDRecord->ROAD->flagsUnk, fileBuffer, 4, curPos);
                        if(curWRLDRecord->ROAD->IsLoaded())
                            printf("Flag used!!!!\n");
                        curWRLDRecord->ROAD->recStart = curPos;
                        FormIDHandler.ExpandFormID(curWRLDRecord->ROAD->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curWRLDRecord->ROAD, fileBuffer, boost::ref(FormIDHandler)));
                            //curWRLDRecord->ROAD->Read(fileBuffer, FormIDHandler);
                            }
                        break;
                    case eLAND:
                        delete curCELLRecord->LAND;
                        curCELLRecord->LAND = new LANDRecord();
                        _readBuffer(&curCELLRecord->LAND->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->LAND->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->LAND->flagsUnk, fileBuffer, 4, curPos);
                        if(curCELLRecord->LAND->IsLoaded())
                            printf("Flag used!!!!\n");
                        curCELLRecord->LAND->recStart = curPos;
                        FormIDHandler.ExpandFormID(curCELLRecord->LAND->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curCELLRecord->LAND, fileBuffer, boost::ref(FormIDHandler)));
                            GridXY_LAND[curCELLRecord->XCLC.value.posX][curCELLRecord->XCLC.value.posY] = curCELLRecord->LAND;
                            //curCELLRecord->LAND->Read(fileBuffer, FormIDHandler);
                            }
                        else //Parent CELL is not loaded, so load a temp record for indexing
                            {
                            tempCELLRecord = new CELLRecord();
                            tempCELLRecord->recStart = curCELLRecord->recStart;
                            tempCELLRecord->flags = curCELLRecord->flags;
                            tempCELLRecord->formID = curCELLRecord->formID;
                            tempCELLRecord->flagsUnk = curCELLRecord->flagsUnk;
                            tempCELLRecord->Read(fileBuffer, FormIDHandler);
                            GridXY_LAND[tempCELLRecord->XCLC.value.posX][tempCELLRecord->XCLC.value.posY] = curCELLRecord->LAND;
                            delete tempCELLRecord;
                            tempCELLRecord = NULL;
                            }
                        break;
                    case ePGRD:
                        delete curCELLRecord->PGRD;
                        curCELLRecord->PGRD = new PGRDRecord();
                        _readBuffer(&curCELLRecord->PGRD->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->PGRD->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curCELLRecord->PGRD->flagsUnk, fileBuffer, 4, curPos);
                        if(curCELLRecord->PGRD->IsLoaded())
                            printf("Flag used!!!!\n");
                        curCELLRecord->PGRD->recStart = curPos;
                        FormIDHandler.ExpandFormID(curCELLRecord->PGRD->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curCELLRecord->PGRD, fileBuffer, boost::ref(FormIDHandler)));
                            //curCELLRecord->PGRD->Read(fileBuffer, FormIDHandler);
                            }
                        break;
                    case eACHR:
                        curACHRRecord = new ACHRRecord();
                        _readBuffer(&curACHRRecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curACHRRecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curACHRRecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curACHRRecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curACHRRecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curACHRRecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curACHRRecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curACHRRecord->Read(fileBuffer, FormIDHandler);
                            }
                        curCELLRecord->ACHR.push_back(curACHRRecord);
                        break;
                    case eACRE:
                        curACRERecord = new ACRERecord();
                        _readBuffer(&curACRERecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curACRERecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curACRERecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curACRERecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curACRERecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curACRERecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curACRERecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curACRERecord->Read(fileBuffer, FormIDHandler);
                            }
                        curCELLRecord->ACRE.push_back(curACRERecord);
                        break;
                    case eREFR:
                        curREFRRecord = new REFRRecord();
                        _readBuffer(&curREFRRecord->flags, fileBuffer, 4, curPos);
                        _readBuffer(&curREFRRecord->formID, fileBuffer, 4, curPos);
                        _readBuffer(&curREFRRecord->flagsUnk, fileBuffer, 4, curPos);
                        if(curREFRRecord->IsLoaded())
                            printf("Flag used!!!!\n");
                        curREFRRecord->recStart = curPos;
                        FormIDHandler.ExpandFormID(curREFRRecord->formID);
                        curPos += recordSize;
                        if(FullLoad)
                            {
                            Threads.schedule(boost::bind(&Record::Read, curREFRRecord, fileBuffer, boost::ref(FormIDHandler)));
                            //curREFRRecord->Read(fileBuffer, FormIDHandler);
                            }
                        curCELLRecord->REFR.push_back(curREFRRecord);
                        break;
                    default:
                        printf("  WRLD: Unexpected Field = %04x\n", recordType);
                        printf("  Size = %u\n", recordSize);
                        printf("  CurPos = %04x\n\n", curPos - 20);
                        curPos = gSize;
                        break;
                    }
                };
            //Index LAND records by grid
            for(unsigned int x = 0; x < Records.size(); ++x)
                for(unsigned int y = 0; y < Records[x]->CELLS.size(); ++y)
                    if(Records[x]->CELLS[y]->LAND != NULL)
                        {
                        Records[x]->CELLS[y]->LAND->NorthLand = GridXY_LAND[Records[x]->CELLS[y]->XCLC.value.posX][Records[x]->CELLS[y]->XCLC.value.posY + 1];
                        Records[x]->CELLS[y]->LAND->SouthLand = GridXY_LAND[Records[x]->CELLS[y]->XCLC.value.posX][Records[x]->CELLS[y]->XCLC.value.posY - 1];
                        Records[x]->CELLS[y]->LAND->EastLand = GridXY_LAND[Records[x]->CELLS[y]->XCLC.value.posX + 1][Records[x]->CELLS[y]->XCLC.value.posY];
                        Records[x]->CELLS[y]->LAND->WestLand = GridXY_LAND[Records[x]->CELLS[y]->XCLC.value.posX - 1][Records[x]->CELLS[y]->XCLC.value.posY];
                        }
            return true;
            }
        bool Read(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler)
            {
            if(LoadedGRUP || !SkimmedGRUP)
                return false;
            LoadedGRUP = true;
            WRLDRecord *curWRLDRecord = NULL;
            CELLRecord *curCELLRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curWRLDRecord = Records[p];
                curWRLDRecord->Read(fileBuffer, FormIDHandler);
                if(curWRLDRecord->ROAD != NULL)
                    curWRLDRecord->ROAD->Read(fileBuffer, FormIDHandler);
                if(curWRLDRecord->CELL != NULL)
                    {
                    curCELLRecord = curWRLDRecord->CELL;
                    curCELLRecord->Read(fileBuffer, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        curCELLRecord->ACHR[y]->Read(fileBuffer, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        curCELLRecord->ACRE[y]->Read(fileBuffer, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        curCELLRecord->REFR[y]->Read(fileBuffer, FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        curCELLRecord->PGRD->Read(fileBuffer, FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        curCELLRecord->LAND->Read(fileBuffer, FormIDHandler);
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELLS.size(); x++)
                    {
                    curCELLRecord = curWRLDRecord->CELLS[x];
                    curCELLRecord->Read(fileBuffer, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        curCELLRecord->ACHR[y]->Read(fileBuffer, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        curCELLRecord->ACRE[y]->Read(fileBuffer, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        curCELLRecord->REFR[y]->Read(fileBuffer, FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        curCELLRecord->PGRD->Read(fileBuffer, FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        curCELLRecord->LAND->Read(fileBuffer, FormIDHandler);
                    }
                }
            return true;
            }
        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            WRLDRecord *curWRLDRecord = NULL;
            CELLRecord *curCELLRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curWRLDRecord = Records[p];
                curWRLDRecord->CollapseFormIDs(FormIDHandler);
                if(curWRLDRecord->ROAD != NULL)
                    curWRLDRecord->ROAD->CollapseFormIDs(FormIDHandler);
                if(curWRLDRecord->CELL != NULL)
                    {
                    curCELLRecord = curWRLDRecord->CELL;
                    curCELLRecord->CollapseFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        curCELLRecord->ACHR[y]->CollapseFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        curCELLRecord->ACRE[y]->CollapseFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        curCELLRecord->REFR[y]->CollapseFormIDs(FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        curCELLRecord->PGRD->CollapseFormIDs(FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        curCELLRecord->LAND->CollapseFormIDs(FormIDHandler);
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELLS.size(); x++)
                    {
                    curCELLRecord = curWRLDRecord->CELLS[x];
                    curCELLRecord->CollapseFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        curCELLRecord->ACHR[y]->CollapseFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        curCELLRecord->ACRE[y]->CollapseFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        curCELLRecord->REFR[y]->CollapseFormIDs(FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        curCELLRecord->PGRD->CollapseFormIDs(FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        curCELLRecord->LAND->CollapseFormIDs(FormIDHandler);
                    }
                }
            return;
            }
        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            WRLDRecord *curWRLDRecord = NULL;
            CELLRecord *curCELLRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curWRLDRecord = Records[p];
                curWRLDRecord->ExpandFormIDs(FormIDHandler);
                if(curWRLDRecord->ROAD != NULL)
                    curWRLDRecord->ROAD->ExpandFormIDs(FormIDHandler);
                if(curWRLDRecord->CELL != NULL)
                    {
                    curCELLRecord = curWRLDRecord->CELL;
                    curCELLRecord->ExpandFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        curCELLRecord->ACHR[y]->ExpandFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        curCELLRecord->ACRE[y]->ExpandFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        curCELLRecord->REFR[y]->ExpandFormIDs(FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        curCELLRecord->PGRD->ExpandFormIDs(FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        curCELLRecord->LAND->ExpandFormIDs(FormIDHandler);
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELLS.size(); x++)
                    {
                    curCELLRecord = curWRLDRecord->CELLS[x];
                    curCELLRecord->ExpandFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        curCELLRecord->ACHR[y]->ExpandFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        curCELLRecord->ACRE[y]->ExpandFormIDs(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        curCELLRecord->REFR[y]->ExpandFormIDs(FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        curCELLRecord->PGRD->ExpandFormIDs(FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        curCELLRecord->LAND->ExpandFormIDs(FormIDHandler);
                    }
                }
            return;
            }
        unsigned int GetSizes(unsigned int &TopSize, std::vector<WritableWorld> &WritableWorlds, _FormIDHandler &FormIDHandler)
            {
            unsigned int numWrldRecords = (unsigned int)Records.size();
            if(numWrldRecords == 0)
                return 0;
            unsigned int numCellRecords;
            unsigned int GRUPCount = numWrldRecords;
            unsigned int curSize = 0;
            int gridX, gridY;
            unsigned int BlockIndex, SubBlockIndex;
            WRLDRecord *curWorld;
            CELLRecord *curCell;
            WritableCell curWriteCell;
            WritableWorld curWriteWorld;
            WritableWorlds.reserve(numWrldRecords);
            TopSize = (numWrldRecords * 20) + 20; //Accounts for all World record headers and itself
            ++GRUPCount; //Top GRUP

            for(unsigned int x = 0; x < numWrldRecords; ++x)
                {
                curWorld = Records[x];
                curWriteWorld.WorldSize = curWorld->GetSize();
                TopSize += curWriteWorld.WorldSize;
                curWriteWorld.WorldGRUPSize = 0;
                curWriteWorld.RoadSize = 0;
                curWriteWorld.CellSize = 0;
                curWriteWorld.ChildrenSize = 0;
                curWriteWorld.PersistentSize = 0;
                curWriteWorld.Persistent.clear();
                curWriteWorld.PersistentSizes.clear();
                curWriteWorld.Block.clear();

                if(curWorld->ROAD != NULL)
                    {
                    curWriteWorld.WorldGRUPSize += 20; //Record Header
                    ++GRUPCount; //Record Header
                    curWriteWorld.WorldGRUPSize += curWriteWorld.RoadSize = curWorld->ROAD->GetSize();
                    }

                GRUPCount += numCellRecords = (unsigned int)curWorld->CELLS.size();
                curWriteWorld.WorldGRUPSize += (numCellRecords * 20); //All cell record headers
                for(unsigned int y = 0; y < numCellRecords; ++y)
                    {
                    curWriteCell.curRecord = curCell = curWorld->CELLS[y];
                    curWriteWorld.WorldGRUPSize += curWriteCell.CellSize = curCell->GetSize();
                    curWriteCell.ChildrenSize = 0;
                    curWriteCell.PersistentSize = 0;
                    curWriteCell.Persistent.clear();
                    curWriteCell.PersistentSizes.clear();
                    curWriteCell.VWDSize = 0;
                    curWriteCell.VWD.clear();
                    curWriteCell.VWDSizes.clear();
                    curWriteCell.TemporarySize = 0;
                    curWriteCell.Temporary.clear();
                    curWriteCell.TemporarySizes.clear();

                    if(curCell->LAND != NULL)
                        {
                        curWriteCell.TemporarySize += 20; //Record Header
                        curWriteCell.TemporarySize += curSize = curCell->LAND->GetSize();
                        curWriteCell.Temporary.push_back(curCell->LAND);
                        curWriteCell.TemporarySizes.push_back(curSize);
                        }

                    if(curCell->PGRD != NULL)
                        {
                        curWriteCell.TemporarySize += 20; //Record Header
                        curWriteCell.TemporarySize += curSize = curCell->PGRD->GetSize();
                        curWriteCell.Temporary.push_back(curCell->PGRD);
                        curWriteCell.TemporarySizes.push_back(curSize);
                        }

                    for(unsigned int z = 0; z < curCell->ACHR.size(); ++z)
                        {
                        if(curCell->ACHR[z]->IsPersistent())
                            {
                            curWriteWorld.PersistentSize += 20; //Record Header
                            curWriteWorld.PersistentSize += curSize = curCell->ACHR[z]->GetSize();
                            curWriteWorld.Persistent.push_back(curCell->ACHR[z]);
                            curWriteWorld.PersistentSizes.push_back(curSize);
                            }
                        else if(curCell->ACHR[z]->IsVWD())
                            {
                            curWriteCell.VWDSize += 20; //Record Header
                            curWriteCell.VWDSize += curSize = curCell->ACHR[z]->GetSize();
                            curWriteCell.VWD.push_back(curCell->ACHR[z]);
                            curWriteCell.VWDSizes.push_back(curSize);
                            }
                        else
                            {
                            curWriteCell.TemporarySize += 20; //Record Header
                            curWriteCell.TemporarySize += curSize = curCell->ACHR[z]->GetSize();
                            curWriteCell.Temporary.push_back(curCell->ACHR[z]);
                            curWriteCell.TemporarySizes.push_back(curSize);
                            }
                        }

                    for(unsigned int z = 0; z < curCell->ACRE.size(); ++z)
                        {
                        if(curCell->ACRE[z]->IsPersistent())
                            {
                            curWriteWorld.PersistentSize += 20; //Record Header
                            curWriteWorld.PersistentSize += curSize = curCell->ACRE[z]->GetSize();
                            curWriteWorld.Persistent.push_back(curCell->ACRE[z]);
                            curWriteWorld.PersistentSizes.push_back(curSize);
                            }
                        else if(curCell->ACRE[z]->IsVWD())
                            {
                            curWriteCell.VWDSize += 20; //Record Header
                            curWriteCell.VWDSize += curSize = curCell->ACRE[z]->GetSize();
                            curWriteCell.VWD.push_back(curCell->ACRE[z]);
                            curWriteCell.VWDSizes.push_back(curSize);
                            }
                        else
                            {
                            curWriteCell.TemporarySize += 20; //Record Header
                            curWriteCell.TemporarySize += curSize = curCell->ACRE[z]->GetSize();
                            curWriteCell.Temporary.push_back(curCell->ACRE[z]);
                            curWriteCell.TemporarySizes.push_back(curSize);
                            }
                        }

                    for(unsigned int z = 0; z < curCell->REFR.size(); ++z)
                        {
                        if(curCell->REFR[z]->IsPersistent())
                            {
                            curWriteWorld.PersistentSize += 20; //Record Header
                            curWriteWorld.PersistentSize += curSize = curCell->REFR[z]->GetSize();
                            curWriteWorld.Persistent.push_back(curCell->REFR[z]);
                            curWriteWorld.PersistentSizes.push_back(curSize);
                            }
                        else if(curCell->REFR[z]->IsVWD())
                            {
                            curWriteCell.VWDSize += 20; //Record Header
                            curWriteCell.VWDSize += curSize = curCell->REFR[z]->GetSize();
                            curWriteCell.VWD.push_back(curCell->REFR[z]);
                            curWriteCell.VWDSizes.push_back(curSize);
                            }
                        else
                            {
                            curWriteCell.TemporarySize += 20; //Record Header
                            curWriteCell.TemporarySize += curSize = curCell->REFR[z]->GetSize();
                            curWriteCell.Temporary.push_back(curCell->REFR[z]);
                            curWriteCell.TemporarySizes.push_back(curSize);
                            }
                        }

                    //Account for GRUPs
                    GRUPCount += (unsigned int)curCell->ACHR.size();
                    GRUPCount += (unsigned int)curCell->ACRE.size();
                    GRUPCount += (unsigned int)curCell->REFR.size();
                    if(curWriteCell.VWDSize)
                        ++GRUPCount, curWriteCell.VWDSize += 20;
                    if(curWriteCell.TemporarySize)
                        ++GRUPCount, curWriteCell.TemporarySize += 20;
                    curWriteCell.ChildrenSize += curWriteCell.VWDSize + curWriteCell.TemporarySize;
                    if(curWriteCell.ChildrenSize)
                        ++GRUPCount, curWriteCell.ChildrenSize += 20;
                    curWriteWorld.WorldGRUPSize += curWriteCell.ChildrenSize;

                    gridX = (int)floor(curCell->XCLC.value.posX / 8.0);
                    gridY = (int)floor(curCell->XCLC.value.posY / 8.0);
                    SubBlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                    gridX = (int)floor(gridX / 4.0);
                    gridY = (int)floor(gridY / 4.0);
                    BlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);

                    if(curWriteWorld.Block[BlockIndex].SubBlock.size() == 0)
                        {
                        ++GRUPCount;
                        curWriteWorld.WorldGRUPSize += 20;
                        curWriteWorld.Block[BlockIndex].size = 20;
                        }
                    if(curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].WritableRecords.size() == 0)
                        {
                        ++GRUPCount;
                        curWriteWorld.WorldGRUPSize += 20;
                        curWriteWorld.Block[BlockIndex].size += 20;
                        curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size = 20;
                        }

                    curWriteWorld.Block[BlockIndex].size += 20; //Cell Record Header
                    curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size += 20; //Cell Record Header
                    curWriteWorld.Block[BlockIndex].size += curWriteCell.CellSize;
                    curWriteWorld.Block[BlockIndex].size += curWriteCell.ChildrenSize;
                    curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size += curWriteCell.CellSize;
                    curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size += curWriteCell.ChildrenSize;

                    curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].WritableRecords.push_back(curWriteCell);
                    }
                if(curWriteWorld.PersistentSize != 0)
                    {
                    if(curWorld->CELL == NULL) //create a default dummy cell for persistents
                        {
                        curWorld->CELL = new CELLRecord(FormIDHandler.NextExpandedFID());
                        curWorld->CELL->IsHasWater(true);
                        curWorld->CELL->IsPersistent(true);
                        curWorld->CELL->XCLC.value.posX = 0;
                        curWorld->CELL->XCLC.value.posY = 0;
                        curWorld->CELL->XCLC.isLoaded = true;
                        }
                    }

                if(curWorld->CELL != NULL)
                    {
                    curWriteWorld.WorldGRUPSize += 20; //Record Header
                    ++GRUPCount; //Record Header
                    curCell = curWorld->CELL;
                    //Only persistent references will be saved in the dummy cell.
                    //Others will be silently discarded.  Could resolve them to their proper cell...
                    //But, it'd add another order of complexity. This's good enough, for now.
                    for(unsigned int z = 0; z < curCell->ACHR.size(); ++z)
                        {
                        if(curCell->ACHR[z]->IsPersistent())
                            {
                            ++GRUPCount; //Record Header
                            curWriteWorld.PersistentSize += 20; //Record Header
                            curWriteWorld.PersistentSize += curSize = curCell->ACHR[z]->GetSize();
                            curWriteWorld.Persistent.push_back(curCell->ACHR[z]);
                            curWriteWorld.PersistentSizes.push_back(curSize);
                            }
                        }

                    for(unsigned int z = 0; z < curCell->ACRE.size(); ++z)
                        {
                        if(curCell->ACRE[z]->IsPersistent())
                            {
                            ++GRUPCount; //Record Header
                            curWriteWorld.PersistentSize += 20; //Record Header
                            curWriteWorld.PersistentSize += curSize = curCell->ACRE[z]->GetSize();
                            curWriteWorld.Persistent.push_back(curCell->ACRE[z]);
                            curWriteWorld.PersistentSizes.push_back(curSize);
                            }
                        }

                    for(unsigned int z = 0; z < curCell->REFR.size(); ++z)
                        {
                        if(curCell->REFR[z]->IsPersistent())
                            {
                            ++GRUPCount; //Record Header
                            curWriteWorld.PersistentSize += 20; //Record Header
                            curWriteWorld.PersistentSize += curSize = curCell->REFR[z]->GetSize();
                            curWriteWorld.Persistent.push_back(curCell->REFR[z]);
                            curWriteWorld.PersistentSizes.push_back(curSize);
                            }
                        }

                    //Account for GRUPs
                    if(curWriteWorld.PersistentSize)
                        ++GRUPCount, curWriteWorld.PersistentSize += 20;
                    curWriteWorld.ChildrenSize += curWriteWorld.PersistentSize;
                    if(curWriteWorld.ChildrenSize)
                        ++GRUPCount, curWriteWorld.ChildrenSize += 20;
                    curWriteWorld.WorldGRUPSize += curWriteWorld.ChildrenSize;
                    curWriteWorld.WorldGRUPSize += curWriteWorld.CellSize = curWorld->CELL->GetSize();
                    }

                if(curWriteWorld.WorldGRUPSize != 0)
                    ++GRUPCount, curWriteWorld.WorldGRUPSize += 20;
                TopSize += curWriteWorld.WorldGRUPSize;
                WritableWorlds.push_back(curWriteWorld);
                }
            return GRUPCount;
            }
        void WriteGRUP(unsigned int &TopSize, std::vector<WritableWorld> &WritableWorlds, int *fh, unsigned char *buffer, unsigned int &usedBuffer)
            {
            unsigned int numWrldRecords = (unsigned int)Records.size();
            if(numWrldRecords == 0)
                return;

            CELLRecord *curCellRecord = NULL;
            WRLDRecord *curWorldRecord = NULL;
            WritableWorld *curWRLD = NULL;
            WritableCell *curCELL = NULL;
            unsigned int type = eGRUP;
            unsigned int gLabel = eWRLD;
            unsigned int gType = eTop;
            unsigned int gSize = 0;
            _writeBuffer(buffer, &type, 4, usedBuffer);
            _writeBuffer(buffer, &TopSize, 4, usedBuffer);
            _writeBuffer(buffer, &gLabel, 4, usedBuffer);
            _writeBuffer(buffer, &gType, 4, usedBuffer);
            _writeBuffer(buffer, &stamp, 4, usedBuffer);

            for(unsigned int z = 0; z < numWrldRecords; ++z)
                {
                curWorldRecord = Records[z];
                curWRLD = &WritableWorlds[z];
                curWorldRecord->Write(fh, buffer, curWRLD->WorldSize, usedBuffer);
                if(curWRLD->WorldGRUPSize != 0)
                    {
                    gType = eWorld;
                    _writeBuffer(buffer, &type, 4, usedBuffer);
                    _writeBuffer(buffer, &curWRLD->WorldGRUPSize, 4, usedBuffer);
                    _writeBuffer(buffer, &curWorldRecord->formID, 4, usedBuffer);
                    _writeBuffer(buffer, &gType, 4, usedBuffer);
                    _writeBuffer(buffer, &stamp, 4, usedBuffer);
                    if(curWorldRecord->ROAD != NULL)
                        curWorldRecord->ROAD->Write(fh, buffer, curWRLD->RoadSize, usedBuffer);
                    if(curWorldRecord->CELL != NULL)
                        {
                        curWorldRecord->CELL->Write(fh, buffer, curWRLD->CellSize, usedBuffer);
                        if(curWRLD->ChildrenSize != 0)
                            {
                            gType = eCellChildren;
                            _writeBuffer(buffer, &type, 4, usedBuffer);
                            _writeBuffer(buffer, &curWRLD->ChildrenSize, 4, usedBuffer);
                            _writeBuffer(buffer, &curWorldRecord->CELL->formID, 4, usedBuffer);
                            _writeBuffer(buffer, &gType, 4, usedBuffer);
                            _writeBuffer(buffer, &stamp, 4, usedBuffer);
                            if(curWRLD->PersistentSize != 0)
                                {
                                gType = eCellPersistent;
                                _writeBuffer(buffer, &type, 4, usedBuffer);
                                _writeBuffer(buffer, &curWRLD->PersistentSize, 4, usedBuffer);
                                _writeBuffer(buffer, &curWorldRecord->CELL->formID, 4, usedBuffer);
                                _writeBuffer(buffer, &gType, 4, usedBuffer);
                                _writeBuffer(buffer, &stamp, 4, usedBuffer);
                                for(unsigned int x = 0; x < curWRLD->Persistent.size(); ++x)
                                    curWRLD->Persistent[x]->Write(fh, buffer, curWRLD->PersistentSizes[x], usedBuffer);
                                }
                            }
                        }
                    for(std::map<unsigned int, WritableBlock, sortBlocks>::iterator curBlock = curWRLD->Block.begin(); curBlock != curWRLD->Block.end(); ++curBlock)
                        {
                        gType = eExteriorBlock;
                        _writeBuffer(buffer, &type, 4, usedBuffer);
                        _writeBuffer(buffer, &curBlock->second.size, 4, usedBuffer);
                        _writeBuffer(buffer, &curBlock->first, 4, usedBuffer);
                        _writeBuffer(buffer, &gType, 4, usedBuffer);
                        _writeBuffer(buffer, &stamp, 4, usedBuffer);
                        for(std::map<unsigned int, WritableSubBlock, sortBlocks>::iterator curSubBlock = curBlock->second.SubBlock.begin(); curSubBlock != curBlock->second.SubBlock.end(); ++curSubBlock)
                            {
                            gSize = (unsigned int)curSubBlock->second.WritableRecords.size();
                            gType = eExteriorSubBlock;
                            _writeBuffer(buffer, &type, 4, usedBuffer);
                            _writeBuffer(buffer, &curSubBlock->second.size, 4, usedBuffer);
                            _writeBuffer(buffer, &curSubBlock->first, 4, usedBuffer);
                            _writeBuffer(buffer, &gType, 4, usedBuffer);
                            _writeBuffer(buffer, &stamp, 4, usedBuffer);
                            for(unsigned int p = 0; p < gSize; ++p)
                                {
                                curCELL = &curSubBlock->second.WritableRecords[p];
                                curCellRecord = curCELL->curRecord;
                                curCellRecord->Write(fh, buffer, curCELL->CellSize, usedBuffer);
                                if(curCELL->ChildrenSize)
                                    {
                                    gType = eCellChildren;
                                    _writeBuffer(buffer, &type, 4, usedBuffer);
                                    _writeBuffer(buffer, &curCELL->ChildrenSize, 4, usedBuffer);
                                    _writeBuffer(buffer, &curCellRecord->formID, 4, usedBuffer);
                                    _writeBuffer(buffer, &gType, 4, usedBuffer);
                                    _writeBuffer(buffer, &stamp, 4, usedBuffer);
                                    if(curCELL->VWDSize)
                                        {
                                        gType = eCellVWD;
                                        _writeBuffer(buffer, &type, 4, usedBuffer);
                                        _writeBuffer(buffer, &curCELL->VWDSize, 4, usedBuffer);
                                        _writeBuffer(buffer, &curCellRecord->formID, 4, usedBuffer);
                                        _writeBuffer(buffer, &gType, 4, usedBuffer);
                                        _writeBuffer(buffer, &stamp, 4, usedBuffer);
                                        for(unsigned int x = 0; x < curCELL->VWD.size(); ++x)
                                            curCELL->VWD[x]->Write(fh, buffer, curCELL->VWDSizes[x], usedBuffer);
                                        }
                                    if(curCELL->TemporarySize)
                                        {
                                        gType = eCellTemporary;
                                        _writeBuffer(buffer, &type, 4, usedBuffer);
                                        _writeBuffer(buffer, &curCELL->TemporarySize, 4, usedBuffer);
                                        _writeBuffer(buffer, &curCellRecord->formID, 4, usedBuffer);
                                        _writeBuffer(buffer, &gType, 4, usedBuffer);
                                        _writeBuffer(buffer, &stamp, 4, usedBuffer);
                                        for(unsigned int x = 0; x < curCELL->Temporary.size(); ++x)
                                            curCELL->Temporary[x]->Write(fh, buffer, curCELL->TemporarySizes[x], usedBuffer);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            return;
            }

        #ifdef _DEBUG
        void Debug(int debugLevel)
            {
            if(debugLevel > 2)
                for(std::vector<WRLDRecord *>::iterator curRecord = Records.begin();curRecord!=Records.end();curRecord++)
                    (*curRecord)->Debug(debugLevel);
            }
        #endif
    };
