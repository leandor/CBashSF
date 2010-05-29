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
        void WriteGRUP(unsigned int TopLabel, FileBuffer &buffer, bool CloseMod)
            {
            unsigned int numRecords = (unsigned int)Records.size();
            if(numRecords == 0)
                return;
            unsigned int type = eGRUP;
            unsigned int gType = eTop;
            unsigned int TopSize = (numRecords * 20) + 20; //Accounts for all record headers and Top GRUP
            std::vector<WritableRecord> WritableRecords;
            WritableRecords.resize(numRecords);
            for(unsigned int p = 0; p < numRecords; p++)
                {
                Records[p]->Write(WritableRecords[p]);
                TopSize += WritableRecords[p].recSize;
                if(CloseMod)
                    delete Records[p];
                }
            if(CloseMod)
                Records.clear();
            buffer.write(&type, 4);
            buffer.write(&TopSize, 4);
            buffer.write(&TopLabel, 4);
            buffer.write(&gType, 4);
            buffer.write(&stamp, 4);
            for(unsigned int p = 0; p < numRecords; p++)
                buffer.write(WritableRecords[p]);
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
        void WriteGRUP(FileBuffer &buffer, bool CloseMod)
            {
            unsigned int numDIALRecords = (unsigned int)Records.size(); //Parent Records
            if(numDIALRecords == 0)
                return;
            unsigned int type = eGRUP;
            unsigned int TopLabel = eDIAL;
            unsigned int gType = eTop;
            std::vector<WritableDialogue> WriteDial;
            unsigned int numINFORecords;
            unsigned int TopSize = (numDIALRecords * 20) + 20; //Top GRUP & accounts for all DIAL record headers
            WriteDial.resize(numDIALRecords);
            for(unsigned int p = 0; p < numDIALRecords; ++p)
                {
                Records[p]->Write(WriteDial[p]);
                TopSize += WriteDial[p].recSize;

                numINFORecords = (unsigned int)Records[p]->INFO.size(); //Children Records
                if(numINFORecords)
                    {
                    WriteDial[p].ChildrenSize = (numINFORecords * 20) + 20; //Children GRUP & accounts for all INFO record headers
                    WriteDial[p].Children.resize(numINFORecords);
                    for(unsigned int y = 0; y < numINFORecords; ++y)
                        {
                        Records[p]->INFO[y]->Write(WriteDial[p].Children[y]);
                        WriteDial[p].ChildrenSize += WriteDial[p].Children[y].recSize;
                        if(CloseMod)
                            delete Records[p]->INFO[y];
                        }
                    TopSize += WriteDial[p].ChildrenSize;
                    }
                if(CloseMod)
                    {
                    Records[p]->INFO.clear();
                    delete Records[p];
                    }
                }
            if(CloseMod)
                Records.clear();

            buffer.write(&type, 4);
            buffer.write(&TopSize, 4);
            buffer.write(&TopLabel, 4);
            buffer.write(&gType, 4);
            buffer.write(&stamp, 4);
            gType = eTopicChildren;
            for(unsigned int p = 0; p < numDIALRecords; ++p)
                {
                buffer.write(WriteDial[p]);

                if(WriteDial[p].Children.size())
                    {
                    buffer.write(&type, 4);
                    buffer.write(&WriteDial[p].ChildrenSize, 4);
                    buffer.write(&Records[p]->formID, 4);
                    buffer.write(&gType, 4);
                    buffer.write(&stamp, 4);
                    for(unsigned int y = 0; y < WriteDial[p].Children.size(); ++y)
                        buffer.write(WriteDial[p].Children[y]);
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
        void WriteGRUP(FileBuffer &buffer, bool CloseMod)
            {
            unsigned int numCELLRecords = (unsigned int)Records.size();
            if(numCELLRecords == 0)
                return;

            unsigned int TopSize = (numCELLRecords * 20) + 20; //Accounts for all Cell record headers and itself
            std::vector< std::vector< std::vector<WritableCell> > > BlockedRecords(10, std::vector< std::vector<WritableCell> > (10, std::vector<WritableCell>()));
            std::vector<unsigned int> BlockHeaders(10, 0);
            std::vector< std::vector<unsigned int> > SubBlockHeaders(10, std::vector<unsigned int>(10, 0));

            int ObjectID, BlockIndex, SubBlockIndex;
            CELLRecord *curRecord = NULL;
            WritableCell curICELL;
            WritableRecord curWriteRecord;
            BlockedRecords.reserve(numCELLRecords);
            for(unsigned int p = 0; p < numCELLRecords; ++p)
                {
                curRecord = Records[p];
                curRecord->Write(curICELL);
                TopSize += curICELL.recSize;

                curICELL.formID = curRecord->formID;
                curICELL.ChildrenSize = 0;
                curICELL.PersistentSize = 0;
                curICELL.Persistent.clear();
                curICELL.VWDSize = 0;
                curICELL.VWD.clear();
                curICELL.TemporarySize = 0;
                curICELL.Temporary.clear();

                if(curRecord->PGRD != NULL)
                    {
                    curRecord->PGRD->Write(curWriteRecord);
                    curICELL.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                    curICELL.Temporary.push_back(curWriteRecord);
                    if(CloseMod)
                        {
                        delete curRecord->PGRD;
                        curRecord->PGRD = NULL;
                        }
                    }

                for(unsigned int y = 0; y < curRecord->ACHR.size(); ++y)
                    {
                    curRecord->ACHR[y]->Write(curWriteRecord);
                    if(curRecord->ACHR[y]->IsPersistent())
                        {
                        curICELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.Persistent.push_back(curWriteRecord);
                        }
                    else if(curRecord->ACHR[y]->IsVWD())
                        {
                        curICELL.VWDSize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.VWD.push_back(curWriteRecord);
                        }
                    else
                        {
                        curICELL.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.Temporary.push_back(curWriteRecord);
                        }
                    if(CloseMod)
                        delete curRecord->ACHR[y];
                    }
                if(CloseMod)
                    curRecord->ACHR.clear();

                for(unsigned int y = 0; y < curRecord->ACRE.size(); ++y)
                    {
                    curRecord->ACRE[y]->Write(curWriteRecord);
                    if(curRecord->ACRE[y]->IsPersistent())
                        {
                        curICELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.Persistent.push_back(curWriteRecord);
                        }
                    else if(curRecord->ACRE[y]->IsVWD())
                        {
                        curICELL.VWDSize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.VWD.push_back(curWriteRecord);
                        }
                    else
                        {
                        curICELL.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.Temporary.push_back(curWriteRecord);
                        }
                    if(CloseMod)
                        delete curRecord->ACRE[y];
                    }
                if(CloseMod)
                    curRecord->ACRE.clear();

                for(unsigned int y = 0; y < curRecord->REFR.size(); ++y)
                    {
                    curRecord->REFR[y]->Write(curWriteRecord);
                    if(curRecord->REFR[y]->IsPersistent())
                        {
                        curICELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.Persistent.push_back(curWriteRecord);
                        }
                    else if(curRecord->REFR[y]->IsVWD())
                        {
                        curICELL.VWDSize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.VWD.push_back(curWriteRecord);
                        }
                    else
                        {
                        curICELL.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                        curICELL.Temporary.push_back(curWriteRecord);
                        }
                    if(CloseMod)
                        delete curRecord->REFR[y];
                    }
                if(CloseMod)
                    curRecord->REFR.clear();

                //Account for GRUPs
                if(curICELL.PersistentSize) curICELL.PersistentSize += 20;
                if(curICELL.VWDSize) curICELL.VWDSize += 20;
                if(curICELL.TemporarySize) curICELL.TemporarySize += 20;

                curICELL.ChildrenSize += curICELL.PersistentSize + curICELL.VWDSize + curICELL.TemporarySize;

                if(curICELL.ChildrenSize) curICELL.ChildrenSize += 20;

                TopSize += curICELL.ChildrenSize;

                ObjectID = curRecord->formID & 0x00FFFFFF;
                BlockIndex = ObjectID % 10;
                SubBlockIndex = (ObjectID / 10) % 10;
                if(BlockHeaders[BlockIndex] == 0)
                    {
                    TopSize += 20;
                    BlockHeaders[BlockIndex] = 20;
                    }
                if(SubBlockHeaders[BlockIndex][SubBlockIndex] == 0)
                    {
                    TopSize += 20;
                    BlockHeaders[BlockIndex] += 20;
                    SubBlockHeaders[BlockIndex][SubBlockIndex] = 20;
                    }
                BlockHeaders[BlockIndex] += 20; //Cell Record Header
                SubBlockHeaders[BlockIndex][SubBlockIndex] += 20; //Cell Record Header
                BlockHeaders[BlockIndex] += curICELL.recSize;
                BlockHeaders[BlockIndex] += curICELL.ChildrenSize;
                SubBlockHeaders[BlockIndex][SubBlockIndex] += curICELL.recSize;
                SubBlockHeaders[BlockIndex][SubBlockIndex] += curICELL.ChildrenSize;

                BlockedRecords[BlockIndex][SubBlockIndex].push_back(curICELL);
                if(CloseMod)
                    delete curRecord;
                }
            if(CloseMod)
                Records.clear();;
                
            unsigned int type = eGRUP;
            unsigned int gLabel = eCELL;
            unsigned int gType = eTop;
            unsigned int gSize = 0;
            buffer.write(&type, 4);
            buffer.write(&TopSize, 4);
            buffer.write(&gLabel, 4);
            buffer.write(&gType, 4);
            buffer.write(&stamp, 4);

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
                            buffer.write(&type, 4);
                            buffer.write(&BlockHeaders[curBlock], 4);
                            buffer.write(&curBlock, 4);
                            buffer.write(&gType, 4);
                            buffer.write(&stamp, 4);
                            }
                        gType = eInteriorSubBlock;
                        buffer.write(&type, 4);
                        buffer.write(&SubBlockHeaders[curBlock][curSubBlock], 4);
                        buffer.write(&curSubBlock, 4);
                        buffer.write(&gType, 4);
                        buffer.write(&stamp, 4);
                        for(unsigned int p = 0; p < gSize; ++p)
                            {
                            curICELL = BlockedRecords[curBlock][curSubBlock][p];
                            buffer.write(curICELL);
                            if(curICELL.ChildrenSize)
                                {
                                gType = eCellChildren;
                                buffer.write(&type, 4);
                                buffer.write(&curICELL.ChildrenSize, 4);
                                buffer.write(&curICELL.formID, 4);
                                buffer.write(&gType, 4);
                                buffer.write(&stamp, 4);
                                if(curICELL.PersistentSize)
                                    {
                                    gType = eCellPersistent;
                                    buffer.write(&type, 4);
                                    buffer.write(&curICELL.PersistentSize, 4);
                                    buffer.write(&curICELL.formID, 4);
                                    buffer.write(&gType, 4);
                                    buffer.write(&stamp, 4);
                                    for(unsigned int x = 0; x < curICELL.Persistent.size(); ++x)
                                        buffer.write(curICELL.Persistent[x]);
                                    }

                                if(curICELL.VWDSize)
                                    {
                                    gType = eCellVWD;
                                    buffer.write(&type, 4);
                                    buffer.write(&curICELL.VWDSize, 4);
                                    buffer.write(&curICELL.formID, 4);
                                    buffer.write(&gType, 4);
                                    buffer.write(&stamp, 4);
                                    for(unsigned int x = 0; x < curICELL.VWD.size(); ++x)
                                        buffer.write(curICELL.VWD[x]);
                                    }

                                if(curICELL.TemporarySize)
                                    {
                                    gType = eCellTemporary;
                                    buffer.write(&type, 4);
                                    buffer.write(&curICELL.TemporarySize, 4);
                                    buffer.write(&curICELL.formID, 4);
                                    buffer.write(&gType, 4);
                                    buffer.write(&stamp, 4);
                                    for(unsigned int x = 0; x < curICELL.Temporary.size(); ++x)
                                        buffer.write(curICELL.Temporary[x]);
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

        void WriteGRUP(FileBuffer &buffer, bool CloseMod, _FormIDHandler &FormIDHandler)
            {
            unsigned int numWrldRecords = (unsigned int)Records.size();
            if(numWrldRecords == 0)
                return;
            unsigned int numCellRecords;
            int gridX, gridY;
            unsigned int BlockIndex, SubBlockIndex;
            WRLDRecord *curWorld;
            CELLRecord *curCell;
            WritableRecord curWriteRecord;
            WritableCell curWriteCell;
            WritableWorld curWriteWorld;
            std::vector<WritableWorld> WritableWorlds;
            WritableWorlds.reserve(numWrldRecords);
            unsigned int TopSize = (numWrldRecords * 20) + 20; //Accounts for all World record headers and itself

            for(unsigned int x = 0; x < numWrldRecords; ++x)
                {
                curWorld = Records[x];
                curWorld->Write(curWriteWorld);
                TopSize += curWriteWorld.recSize;
                curWriteWorld.WorldGRUPSize = 0;
                curWriteWorld.formID = curWorld->formID;
                curWriteWorld.ROAD.recBuffer = NULL;
                curWriteWorld.ROAD.recSize = 0;
                curWriteWorld.CELL.recBuffer = NULL;
                curWriteWorld.CELL.recSize = 0;
                curWriteWorld.CELL.ChildrenSize = 0;
                curWriteWorld.CELL.PersistentSize = 0;
                curWriteWorld.CELL.Persistent.clear();
                curWriteWorld.Block.clear();

                if(curWorld->ROAD != NULL)
                    {
                    curWorld->ROAD->Write(curWriteWorld.ROAD);
                    curWriteWorld.WorldGRUPSize += curWriteWorld.ROAD.recSize + 20; //Record Header
                    if(CloseMod)
                        {
                        delete curWorld->ROAD;
                        curWorld->ROAD = NULL;
                        }
                    }

                numCellRecords = (unsigned int)curWorld->CELLS.size();
                curWriteWorld.WorldGRUPSize += (numCellRecords * 20); //All cell record headers
                for(unsigned int p = 0; p < numCellRecords; ++p)
                    {
                    curCell = curWorld->CELLS[p];
                    curCell->Write(curWriteCell);
                    curWriteWorld.WorldGRUPSize += curWriteCell.recSize;

                    curWriteCell.formID = curCell->formID;
                    curWriteCell.ChildrenSize = 0;
                    curWriteCell.PersistentSize = 0;
                    curWriteCell.Persistent.clear();
                    curWriteCell.VWDSize = 0;
                    curWriteCell.VWD.clear();
                    curWriteCell.TemporarySize = 0;
                    curWriteCell.Temporary.clear();

                    if(curCell->LAND != NULL)
                        {
                        curCell->LAND->Write(curWriteRecord);
                        curWriteCell.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                        curWriteCell.Temporary.push_back(curWriteRecord);
                        if(CloseMod)
                            {
                            delete curCell->LAND;
                            curCell->LAND = NULL;
                            }
                        }

                    if(curCell->PGRD != NULL)
                        {
                        curCell->PGRD->Write(curWriteRecord);
                        curWriteCell.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                        curWriteCell.Temporary.push_back(curWriteRecord);
                        if(CloseMod)
                            {
                            delete curCell->PGRD;
                            curCell->PGRD = NULL;
                            }
                        }

                    for(unsigned int y = 0; y < curCell->ACHR.size(); ++y)
                        {
                        curCell->ACHR[y]->Write(curWriteRecord);
                        if(curCell->ACHR[y]->IsPersistent())
                            {
                            curWriteWorld.CELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteWorld.CELL.Persistent.push_back(curWriteRecord);
                            }
                        else if(curCell->ACHR[y]->IsVWD())
                            {
                            curWriteCell.VWDSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteCell.VWD.push_back(curWriteRecord);
                            }
                        else
                            {
                            curWriteCell.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                            curWriteCell.Temporary.push_back(curWriteRecord);
                            }
                        if(CloseMod)
                            delete curCell->ACHR[y];
                        }
                    if(CloseMod)
                        curCell->ACHR.clear();

                    for(unsigned int y = 0; y < curCell->ACRE.size(); ++y)
                        {
                        curCell->ACRE[y]->Write(curWriteRecord);
                        if(curCell->ACRE[y]->IsPersistent())
                            {
                            curWriteWorld.CELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteWorld.CELL.Persistent.push_back(curWriteRecord);
                            }
                        else if(curCell->ACRE[y]->IsVWD())
                            {
                            curWriteCell.VWDSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteCell.VWD.push_back(curWriteRecord);
                            }
                        else
                            {
                            curWriteCell.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                            curWriteCell.Temporary.push_back(curWriteRecord);
                            }
                        if(CloseMod)
                            delete curCell->ACRE[y];
                        }
                    if(CloseMod)
                        curCell->ACRE.clear();

                    for(unsigned int y = 0; y < curCell->REFR.size(); ++y)
                        {
                        curCell->REFR[y]->Write(curWriteRecord);
                        if(curCell->REFR[y]->IsPersistent())
                            {
                            curWriteWorld.CELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteWorld.CELL.Persistent.push_back(curWriteRecord);
                            }
                        else if(curCell->REFR[y]->IsVWD())
                            {
                            curWriteCell.VWDSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteCell.VWD.push_back(curWriteRecord);
                            }
                        else
                            {
                            curWriteCell.TemporarySize += curWriteRecord.recSize + 20; //Record Header
                            curWriteCell.Temporary.push_back(curWriteRecord);
                            }
                        if(CloseMod)
                            delete curCell->REFR[y];
                        }
                    if(CloseMod)
                        curCell->REFR.clear();
                    //Account for GRUPs
                    //if(curWriteCell.PersistentSize) curWriteCell.PersistentSize += 20;
                    if(curWriteCell.VWDSize) curWriteCell.VWDSize += 20;
                    if(curWriteCell.TemporarySize) curWriteCell.TemporarySize += 20;

                    curWriteCell.ChildrenSize += curWriteCell.VWDSize + curWriteCell.TemporarySize;

                    if(curWriteCell.ChildrenSize) curWriteCell.ChildrenSize += 20;

                    curWriteWorld.WorldGRUPSize += curWriteCell.ChildrenSize;


                    gridX = (int)floor(curCell->XCLC.value.posX / 8.0);
                    gridY = (int)floor(curCell->XCLC.value.posY / 8.0);
                    SubBlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                    gridX = (int)floor(gridX / 4.0);
                    gridY = (int)floor(gridY / 4.0);
                    BlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                    if(curWriteWorld.Block[BlockIndex].SubBlock.size() == 0)
                        {
                        curWriteWorld.WorldGRUPSize += 20;
                        curWriteWorld.Block[BlockIndex].size = 20;
                        }
                    if(curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].CELLS.size() == 0)
                        {
                        curWriteWorld.WorldGRUPSize += 20;
                        curWriteWorld.Block[BlockIndex].size += 20;
                        curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size = 20;
                        }

                    curWriteWorld.Block[BlockIndex].size += 20; //Cell Record Header
                    curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size += 20; //Cell Record Header
                    curWriteWorld.Block[BlockIndex].size += curWriteCell.recSize;
                    curWriteWorld.Block[BlockIndex].size += curWriteCell.ChildrenSize;
                    curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size += curWriteCell.recSize;
                    curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].size += curWriteCell.ChildrenSize;

                    curWriteWorld.Block[BlockIndex].SubBlock[SubBlockIndex].CELLS.push_back(curWriteCell);

                    if(CloseMod)
                        delete curCell;
                    }
                if(CloseMod)
                    curWorld->CELLS.clear();

                if(curWriteWorld.CELL.PersistentSize != 0)
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
                    curCell = curWorld->CELL;
                    curCell->Write(curWriteWorld.CELL);
                    curWriteWorld.CELL.formID = curCell->formID;
                    curWriteWorld.CELL.ChildrenSize = 0;
                    curWriteWorld.CELL.PersistentSize = 0;
                    curWriteWorld.CELL.Persistent.clear();
                    curWriteWorld.CELL.VWDSize = 0;
                    curWriteWorld.CELL.VWD.clear();
                    curWriteWorld.CELL.TemporarySize = 0;
                    curWriteWorld.CELL.Temporary.clear();

                    curWriteWorld.WorldGRUPSize += 20; //Record Header
                    //Only persistent references will be saved in the dummy cell.
                    //Others will be silently discarded.  Could resolve them to their proper cell...
                    //But, it'd add another order of complexity. This's good enough, for now.
                    for(unsigned int z = 0; z < curCell->ACHR.size(); ++z)
                        {
                        if(curCell->ACHR[z]->IsPersistent())
                            {
                            curCell->ACHR[z]->Write(curWriteRecord);
                            curWriteWorld.CELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteWorld.CELL.Persistent.push_back(curWriteRecord);
                            }
                        if(CloseMod)
                            delete curCell->ACHR[z];
                        }
                    if(CloseMod)
                        curCell->ACHR.clear();

                    for(unsigned int z = 0; z < curCell->ACRE.size(); ++z)
                        {
                        if(curCell->ACRE[z]->IsPersistent())
                            {
                            curCell->ACRE[z]->Write(curWriteRecord);
                            curWriteWorld.CELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteWorld.CELL.Persistent.push_back(curWriteRecord);
                            }
                        if(CloseMod)
                            delete curCell->ACRE[z];
                        }
                    if(CloseMod)
                        curCell->ACRE.clear();

                    for(unsigned int z = 0; z < curCell->REFR.size(); ++z)
                        {
                        if(curCell->REFR[z]->IsPersistent())
                            {
                            curCell->REFR[z]->Write(curWriteRecord);
                            curWriteWorld.CELL.PersistentSize += curWriteRecord.recSize + 20; //Record Header
                            curWriteWorld.CELL.Persistent.push_back(curWriteRecord);
                            }
                        if(CloseMod)
                            delete curCell->REFR[z];
                        }
                    if(CloseMod)
                        curCell->REFR.clear();

                    //Account for GRUPs
                    if(curWriteWorld.CELL.PersistentSize)
                        curWriteWorld.CELL.PersistentSize += 20;
                    curWriteWorld.CELL.ChildrenSize += curWriteWorld.CELL.PersistentSize;
                    if(curWriteWorld.CELL.ChildrenSize)
                        curWriteWorld.CELL.ChildrenSize += 20;
                    curWriteWorld.WorldGRUPSize += curWriteWorld.CELL.ChildrenSize;
                    curWriteWorld.WorldGRUPSize += curWriteWorld.CELL.recSize;

                    if(CloseMod)
                        {
                        delete curCell;
                        curWorld->CELL = NULL;
                        }
                    }

                if(curWriteWorld.WorldGRUPSize != 0)
                    curWriteWorld.WorldGRUPSize += 20;
                TopSize += curWriteWorld.WorldGRUPSize;
                WritableWorlds.push_back(curWriteWorld);

                if(CloseMod)
                    delete curWorld;
                }

            if(CloseMod)
                Records.clear();

            unsigned int type = eGRUP;
            unsigned int gLabel = eWRLD;
            unsigned int gType = eTop;
            unsigned int gSize = 0;

            buffer.write(&type, 4);
            buffer.write(&TopSize, 4);
            buffer.write(&gLabel, 4);
            buffer.write(&gType, 4);
            buffer.write(&stamp, 4);
            for(unsigned int z = 0; z < numWrldRecords; ++z)
                {
                buffer.flush();
                buffer.write(WritableWorlds[z]);

                if(WritableWorlds[z].WorldGRUPSize != 0)
                    {
                    gType = eWorld;
                    buffer.write(&type, 4);
                    buffer.write(&WritableWorlds[z].WorldGRUPSize, 4);
                    buffer.write(&WritableWorlds[z].formID, 4);
                    buffer.write(&gType, 4);
                    buffer.write(&stamp, 4);
                    buffer.write(WritableWorlds[z].ROAD);
                    buffer.write(WritableWorlds[z].CELL);
                    if(WritableWorlds[z].CELL.ChildrenSize != 0)
                        {
                        gType = eCellChildren;
                        buffer.write(&type, 4);
                        buffer.write(&WritableWorlds[z].CELL.ChildrenSize, 4);
                        buffer.write(&WritableWorlds[z].CELL.formID, 4);
                        buffer.write(&gType, 4);
                        buffer.write(&stamp, 4);
                        if(WritableWorlds[z].CELL.PersistentSize != 0)
                            {
                            gType = eCellPersistent;
                            buffer.write(&type, 4);
                            buffer.write(&WritableWorlds[z].CELL.PersistentSize, 4);
                            buffer.write(&WritableWorlds[z].CELL.formID, 4);
                            buffer.write(&gType, 4);
                            buffer.write(&stamp, 4);
                            for(unsigned int x = 0; x < WritableWorlds[z].CELL.Persistent.size(); ++x)
                                buffer.write(WritableWorlds[z].CELL.Persistent[x]);
                            }
                        }

                    for(std::map<unsigned int, WritableWorld::WritableBlock, WritableWorld::sortBlocks>::iterator curBlock = WritableWorlds[z].Block.begin(); curBlock != WritableWorlds[z].Block.end(); ++curBlock)
                        {
                        gType = eExteriorBlock;
                        buffer.write(&type, 4);
                        buffer.write(&curBlock->second.size, 4);
                        buffer.write(&curBlock->first, 4);
                        buffer.write(&gType, 4);
                        buffer.write(&stamp, 4);
                        for(std::map<unsigned int, WritableWorld::WritableBlock::WritableSubBlock, WritableWorld::sortBlocks>::iterator curSubBlock = curBlock->second.SubBlock.begin(); curSubBlock != curBlock->second.SubBlock.end(); ++curSubBlock)
                            {
                            gSize = (unsigned int)curSubBlock->second.CELLS.size();
                            gType = eExteriorSubBlock;
                            buffer.write(&type, 4);
                            buffer.write(&curSubBlock->second.size, 4);
                            buffer.write(&curSubBlock->first, 4);
                            buffer.write(&gType, 4);
                            buffer.write(&stamp, 4);
                            for(unsigned int p = 0; p < gSize; ++p)
                                {
                                buffer.write(curSubBlock->second.CELLS[p]);
                                if(curSubBlock->second.CELLS[p].ChildrenSize)
                                    {
                                    gType = eCellChildren;
                                    buffer.write(&type, 4);
                                    buffer.write(&curSubBlock->second.CELLS[p].ChildrenSize, 4);
                                    buffer.write(&curSubBlock->second.CELLS[p].formID, 4);
                                    buffer.write(&gType, 4);
                                    buffer.write(&stamp, 4);
                                    if(curSubBlock->second.CELLS[p].VWDSize)
                                        {
                                        gType = eCellVWD;
                                        buffer.write(&type, 4);
                                        buffer.write(&curSubBlock->second.CELLS[p].VWDSize, 4);
                                        buffer.write(&curSubBlock->second.CELLS[p].formID, 4);
                                        buffer.write(&gType, 4);
                                        buffer.write(&stamp, 4);
                                        for(unsigned int x = 0; x < curSubBlock->second.CELLS[p].VWD.size(); ++x)
                                            buffer.write(curSubBlock->second.CELLS[p].VWD[x]);
                                        }
                                    if(curSubBlock->second.CELLS[p].TemporarySize)
                                        {
                                        gType = eCellTemporary;
                                        buffer.write(&type, 4);
                                        buffer.write(&curSubBlock->second.CELLS[p].TemporarySize, 4);
                                        buffer.write(&curSubBlock->second.CELLS[p].formID, 4);
                                        buffer.write(&gType, 4);
                                        buffer.write(&stamp, 4);
                                        for(unsigned int x = 0; x < curSubBlock->second.CELLS[p].Temporary.size(); ++x)
                                            buffer.write(curSubBlock->second.CELLS[p].Temporary[x]);
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
