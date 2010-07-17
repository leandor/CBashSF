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
#include <boost/threadpool.hpp>

//#include "mmgr.h"

template<class T>
class GRUPRecords
    {
    public:
        unsigned int stamp;
        bool SkimmedGRUP;
        std::vector<T *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false) {}
        ~GRUPRecords()
            {
            for(unsigned int p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(boost::threadpool::pool &Threads, _FileHandler &ReadHandler, _FormIDHandler &FormIDHandler, const bool &FullLoad, const unsigned long &gSize, boost::unordered_set<unsigned int> &UsedFormIDs)
            {
            if(SkimmedGRUP || gSize == 0)
                return false;
            SkimmedGRUP = true;
            T * curRecord = NULL;
            unsigned long recordType = 0;
            unsigned long gEnd = ReadHandler.tell() + gSize - 20;
            unsigned long recordSize = 0;
            std::pair<boost::unordered_set<unsigned int>::iterator,bool> ret;

            while(ReadHandler.tell() < gEnd){
                curRecord = new T();
                ReadHandler.read(&recordType, 4);
                ReadHandler.read(&recordSize, 4);
                ReadHandler.read(&curRecord->flags, 4);
                ReadHandler.read(&curRecord->formID, 4);
                ReadHandler.read(&curRecord->flagsUnk, 4);
                FormIDHandler.ExpandFormID(curRecord->formID);
                ret = UsedFormIDs.insert(curRecord->formID);
                if(curRecord->IsLoaded())
                    printf("_fIsLoaded Flag used!!!! %s - %08X\n", curRecord->GetStrType(), curRecord->formID);
                if((curRecord->flags & 0x4000) != 0)
                    printf("0x4000 used: %08X!!!!\n", curRecord->formID);
                //Make sure the formID is unique within the mod
                if(ret.second == true)
                    {
                    curRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                    if(FullLoad)
                        Threads.schedule(boost::bind(&Record::Read, curRecord, boost::ref(FormIDHandler)));
                    if(recordType != eGMST && !FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curRecord->formID))
                        FormIDHandler.NewTypes.insert(recordType);
                    Records.push_back(curRecord);
                    }
                else
                    {
                    printf("Record skipped with duplicate formID: %08X\n", curRecord->formID);
                    delete curRecord;
                    }
                ReadHandler.set_used(recordSize);
                };
            if(Records.size())
                FormIDHandler.IsEmpty = false;
            return true;
            }
        bool Read(_FormIDHandler &FormIDHandler)
            {
            if(!SkimmedGRUP)
                return false;
            for(unsigned int p = 0; p < Records.size(); p++)
                Records[p]->Read(FormIDHandler);
            return true;
            }
        void DeleteRecord(Record *curRecord)
            {
            std::vector<T *>::iterator it;
            it = std::find(Records.begin(), Records.end(), curRecord);
            if(it == Records.end())
                {
                printf("Record %08X not found in %s\n", curRecord->formID, curRecord->GetStrType());
                throw 1;
                return;
                }
            delete curRecord;
            Records.erase(it);
            }
        unsigned int UpdateReferences(unsigned int origFormID, unsigned int newFormID, _FormIDHandler &FormIDHandler)
            {
            unsigned int count = 0;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                count += Records[p]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                }
            return count;
            }
        int Unload()
            {
            for(unsigned int p = 0; p < Records.size(); p++)
                if(Records[p]->recData != NULL)
                    Records[p]->Unload();
            return 0;
            }
        bool CheckMasters(unsigned char MASTIndex, _FormIDHandler &FormIDHandler)
            {
            T *curRecord;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(FormIDHandler.UsesMaster(curRecord->formID, MASTIndex))
                    return true;
                if(curRecord->CheckMasters(MASTIndex, FormIDHandler))
                    return true;
                }
            return false;
            }
        unsigned int WriteGRUP(unsigned int TopLabel, _FileHandler &SaveHandler, _FormIDHandler &FormIDHandler, bool CloseMod)
            {
            unsigned int numRecords = (unsigned int)Records.size();
            if(numRecords == 0)
                return 0;
            unsigned int type = eGRUP;
            unsigned int gType = eTop;
            unsigned int TopSize = 0;
            unsigned int formCount = 0;

            //Top GRUP Header
            SaveHandler.write(&type, 4);
            unsigned int TopSizePos = SaveHandler.tell();
            SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
            //SaveHandler.write(&TopSize, 4);
            SaveHandler.write(&TopLabel, 4);
            SaveHandler.write(&gType, 4);
            SaveHandler.write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numRecords;
            for(unsigned int p = 0; p < numRecords; p++)
                {
                TopSize += Records[p]->Write(SaveHandler, FormIDHandler);
                if(CloseMod)
                    delete Records[p];
                }
            SaveHandler.writeAt(TopSizePos, &TopSize, 4);
            if(CloseMod)
                Records.clear();
            return formCount;
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
        bool SkimmedGRUP;
        std::vector<DIALRecord *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false) {}
        ~GRUPRecords()
            {
            for(unsigned int p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(boost::threadpool::pool &Threads, _FileHandler &ReadHandler, _FormIDHandler &FormIDHandler, const bool &FullLoad, const unsigned long &gSize, boost::unordered_set<unsigned int> &UsedFormIDs)
            {
            if(SkimmedGRUP || gSize == 0)
                return false;
            SkimmedGRUP = true;
            DIALRecord * curDIALRecord = NULL;
            INFORecord * curINFORecord = NULL;
            unsigned long recordType = 0;
            unsigned long gEnd = ReadHandler.tell() + gSize - 20;
            unsigned long recordSize = 0;
            std::pair<boost::unordered_set<unsigned int>::iterator,bool> ret;

            while(ReadHandler.tell() < gEnd){
                ReadHandler.read(&recordType, 4);
                ReadHandler.read(&recordSize, 4);
                switch(recordType)
                    {
                    case eDIAL:
                        curDIALRecord = new DIALRecord();
                        ReadHandler.read(&curDIALRecord->flags, 4);
                        ReadHandler.read(&curDIALRecord->formID, 4);
                        ReadHandler.read(&curDIALRecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curDIALRecord->formID);
                        ret = UsedFormIDs.insert(curDIALRecord->formID);
                        if(curDIALRecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curDIALRecord->GetStrType(), curDIALRecord->formID);
                        if((curDIALRecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curDIALRecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curDIALRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curDIALRecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curDIALRecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            Records.push_back(curDIALRecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curDIALRecord->formID);
                            delete curDIALRecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eGRUP: //All GRUPs will be recreated from scratch on write (saves memory)
                        ReadHandler.set_used(8); //Skip label and type fields
                        ReadHandler.read(&stamp, 4);
                        break;
                    case eINFO:
                        curINFORecord = new INFORecord();
                        ReadHandler.read(&curINFORecord->flags, 4);
                        ReadHandler.read(&curINFORecord->formID, 4);
                        ReadHandler.read(&curINFORecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curINFORecord->formID);
                        ret = UsedFormIDs.insert(curINFORecord->formID);
                        if(curINFORecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curINFORecord->GetStrType(), curINFORecord->formID);
                        if((curINFORecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curINFORecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curINFORecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curINFORecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curINFORecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            curDIALRecord->INFO.push_back(curINFORecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curINFORecord->formID);
                            delete curINFORecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    default:
                        printf("  DIAL: Unexpected Field = %04x\n", recordType);
                        ReadHandler.set_used(recordSize);
                        break;
                    }
                };
            if(Records.size())
                FormIDHandler.IsEmpty = false;
            return true;
            }
        bool Read(_FormIDHandler &FormIDHandler)
            {
            if(!SkimmedGRUP)
                return false;
            DIALRecord * curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                curRecord->Read(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->INFO.size(); ++x)
                    curRecord->INFO[x]->Read(FormIDHandler);
                }
            return true;
            }
        void DeleteRecord(Record *curParentRecord, Record *curRecord)
            {
            std::vector<DIALRecord *>::iterator it;
            it = std::find(Records.begin(), Records.end(), curParentRecord);
            if(it == Records.end())
                {
                printf("Record %08X not found in %s\n", curParentRecord->formID, curParentRecord->GetStrType());
                throw 1;
                return;
                }
            if(curRecord == NULL)
                {
                Records.erase(it);
                delete curParentRecord;
                }
            else
                {
                std::vector<INFORecord *>::iterator INFO_it;
                DIALRecord *curDial = *it;
                INFO_it = std::find(curDial->INFO.begin(), curDial->INFO.end(), curRecord);
                if(INFO_it != curDial->INFO.end())
                    curDial->INFO.erase(INFO_it);
                else
                    {
                    printf("Record %08X with parent %08X not found in %s\n", curRecord->formID, curParentRecord->formID, curParentRecord->GetStrType());
                    throw 1;
                    return;
                    }
                delete curRecord;
                }
            return;
            }
        unsigned int UpdateReferences(unsigned int origFormID, unsigned int newFormID, _FormIDHandler &FormIDHandler)
            {
            unsigned int count = 0;
            DIALRecord * curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                count += curRecord->UpdateReferences(origFormID, newFormID, FormIDHandler);
                for(unsigned int x = 0; x < curRecord->INFO.size(); ++x)
                    count += curRecord->INFO[x]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                }
            return count;
            }
        int Unload()
            {
            DIALRecord * curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                for(unsigned int x = 0; x < curRecord->INFO.size(); ++x)
                    if(curRecord->INFO[x]->recData != NULL)
                        curRecord->INFO[x]->Unload();
                if(curRecord->recData != NULL)
                    curRecord->Unload();
                }
            return 0;
            }
        unsigned int CheckMasters(unsigned char MASTIndex, _FormIDHandler &FormIDHandler)
            {
            DIALRecord * curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(FormIDHandler.UsesMaster(curRecord->formID, MASTIndex))
                    return true;
                if(curRecord->CheckMasters(MASTIndex, FormIDHandler))
                    return true;
                for(unsigned int x = 0; x < curRecord->INFO.size(); ++x)
                    {
                    if(FormIDHandler.UsesMaster(curRecord->INFO[x]->formID, MASTIndex))
                        return true;
                    if(curRecord->INFO[x]->CheckMasters(MASTIndex, FormIDHandler))
                        return true;
                    }
                }
            return false;
            }
        unsigned int WriteGRUP(_FileHandler &SaveHandler, _FormIDHandler &FormIDHandler, bool CloseMod)
            {
            unsigned int numDIALRecords = (unsigned int)Records.size(); //Parent Records
            if(numDIALRecords == 0)
                return 0;
            unsigned int type = eGRUP;
            unsigned int gType = eTop;
            unsigned int TopSize =0;
            unsigned int ChildrenSize =0;
            unsigned int formCount = 0;
            unsigned int TopLabel = eDIAL;
            unsigned int numINFORecords = 0;
            unsigned int parentFormID = 0;
            DIALRecord *curRecord = NULL;

            //Top GRUP Header
            SaveHandler.write(&type, 4);
            unsigned int TopSizePos = SaveHandler.tell();
            SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
            //SaveHandler.write(&TopSize, 4);
            SaveHandler.write(&TopLabel, 4);
            SaveHandler.write(&gType, 4);
            SaveHandler.write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            gType = eTopicChildren;
            formCount += numDIALRecords;
            for(unsigned int p = 0; p < numDIALRecords; ++p)
                {
                curRecord = Records[p];
                parentFormID = curRecord->formID;
                FormIDHandler.CollapseFormID(parentFormID);
                TopSize += curRecord->Write(SaveHandler, FormIDHandler);

                numINFORecords = (unsigned int)curRecord->INFO.size();
                if(numINFORecords)
                    {
                    SaveHandler.write(&type, 4);
                    unsigned int ChildrenSizePos = SaveHandler.tell();
                    SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                    SaveHandler.write(&parentFormID, 4);
                    SaveHandler.write(&gType, 4);
                    SaveHandler.write(&stamp, 4);
                    ++formCount;
                    ChildrenSize = 20;

                    formCount += numINFORecords;
                    for(unsigned int y = 0; y < curRecord->INFO.size(); ++y)
                        {
                        ChildrenSize += curRecord->INFO[y]->Write(SaveHandler, FormIDHandler);
                        if(CloseMod)
                            delete curRecord->INFO[y];
                        }
                    SaveHandler.writeAt(ChildrenSizePos, &ChildrenSize, 4);
                    TopSize += ChildrenSize;
                    if(CloseMod)
                        curRecord->INFO.clear();
                    }
                if(CloseMod)
                    delete curRecord;
                }
            SaveHandler.writeAt(TopSizePos, &TopSize, 4);
            if(CloseMod)
                Records.clear();
            return formCount;
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
        bool SkimmedGRUP;
        std::vector<CELLRecord *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false) {}
        ~GRUPRecords()
            {
            for(unsigned int p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(boost::threadpool::pool &Threads, _FileHandler &ReadHandler, _FormIDHandler &FormIDHandler, const bool &FullLoad, const unsigned long &gSize, boost::unordered_set<unsigned int> &UsedFormIDs)
            {
            if(SkimmedGRUP || gSize == 0)
                return false;
            SkimmedGRUP = true;
            CELLRecord *curCELLRecord = NULL;
            ACHRRecord *curACHRRecord = NULL;
            ACRERecord *curACRERecord = NULL;
            REFRRecord *curREFRRecord = NULL;
            unsigned long recordType = 0;
            unsigned long gEnd = ReadHandler.tell() + gSize - 20;
            unsigned long recordSize = 0;
            std::pair<boost::unordered_set<unsigned int>::iterator,bool> ret;

            while(ReadHandler.tell() < gEnd){
                ReadHandler.read(&recordType, 4);
                ReadHandler.read(&recordSize, 4);
                switch(recordType)
                    {
                    case eCELL:
                        curCELLRecord = new CELLRecord();
                        ReadHandler.read(&curCELLRecord->flags, 4);
                        ReadHandler.read(&curCELLRecord->formID, 4);
                        ReadHandler.read(&curCELLRecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curCELLRecord->formID);
                        ret = UsedFormIDs.insert(curCELLRecord->formID);
                        if(curCELLRecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curCELLRecord->GetStrType(), curCELLRecord->formID);
                        if((curCELLRecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curCELLRecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curCELLRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curCELLRecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curCELLRecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            Records.push_back(curCELLRecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curCELLRecord->formID);
                            delete curCELLRecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eGRUP: //All GRUPs will be recreated from scratch on write (saves memory)
                        ReadHandler.set_used(12); //skip the rest of the header
                        break;
                    case eACHR:
                        curACHRRecord = new ACHRRecord();
                        ReadHandler.read(&curACHRRecord->flags, 4);
                        ReadHandler.read(&curACHRRecord->formID, 4);
                        ReadHandler.read(&curACHRRecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curACHRRecord->formID);
                        ret = UsedFormIDs.insert(curACHRRecord->formID);
                        if(curACHRRecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curACHRRecord->GetStrType(), curACHRRecord->formID);
                        if((curACHRRecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curACHRRecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curACHRRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curACHRRecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curACHRRecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            curCELLRecord->ACHR.push_back(curACHRRecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curACHRRecord->formID);
                            delete curACHRRecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eACRE:
                        curACRERecord = new ACRERecord();
                        ReadHandler.read(&curACRERecord->flags, 4);
                        ReadHandler.read(&curACRERecord->formID, 4);
                        ReadHandler.read(&curACRERecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curACRERecord->formID);
                        ret = UsedFormIDs.insert(curACRERecord->formID);
                        if(curACRERecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curACRERecord->GetStrType(), curACRERecord->formID);
                        if((curACRERecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curACRERecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curACRERecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curACRERecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curACRERecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            curCELLRecord->ACRE.push_back(curACRERecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curACRERecord->formID);
                            delete curACRERecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eREFR:
                        curREFRRecord = new REFRRecord();
                        ReadHandler.read(&curREFRRecord->flags, 4);
                        ReadHandler.read(&curREFRRecord->formID, 4);
                        ReadHandler.read(&curREFRRecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curREFRRecord->formID);
                        ret = UsedFormIDs.insert(curREFRRecord->formID);
                        if(curREFRRecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curREFRRecord->GetStrType(), curREFRRecord->formID);
                        if((curREFRRecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curREFRRecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curREFRRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curREFRRecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curREFRRecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            curCELLRecord->REFR.push_back(curREFRRecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curREFRRecord->formID);
                            delete curREFRRecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case ePGRD:
                        delete curCELLRecord->PGRD;
                        curCELLRecord->PGRD = new PGRDRecord();
                        ReadHandler.read(&curCELLRecord->PGRD->flags, 4);
                        ReadHandler.read(&curCELLRecord->PGRD->formID, 4);
                        ReadHandler.read(&curCELLRecord->PGRD->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curCELLRecord->PGRD->formID);
                        ret = UsedFormIDs.insert(curCELLRecord->PGRD->formID);
                        if(curCELLRecord->PGRD->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curCELLRecord->PGRD->GetStrType(), curCELLRecord->PGRD->formID);
                        if((curCELLRecord->PGRD->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curCELLRecord->PGRD->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curCELLRecord->PGRD->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curCELLRecord->PGRD, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curCELLRecord->PGRD->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curCELLRecord->PGRD->formID);
                            delete curCELLRecord->PGRD;
                            curCELLRecord->PGRD = NULL;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    default:
                        printf("  CELL: Unexpected Record = %04x\n", recordType);
                        ReadHandler.set_used(recordSize);
                        break;
                    }
                };
            if(Records.size())
                FormIDHandler.IsEmpty = false;
            return true;
            }
        bool Read(_FormIDHandler &FormIDHandler)
            {
            if(!SkimmedGRUP)
                return false;
            CELLRecord *curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                curRecord->Read(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACHR.size(); ++x)
                    curRecord->ACHR[x]->Read(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACRE.size(); ++x)
                    curRecord->ACRE[x]->Read(FormIDHandler);
                for(unsigned int x = 0; x < curRecord->REFR.size(); ++x)
                    curRecord->REFR[x]->Read(FormIDHandler);
                if(curRecord->PGRD != NULL)
                    curRecord->PGRD->Read(FormIDHandler);
                }
            return true;
            }
        void DeleteRecord(Record *curParentRecord, Record *curRecord)
            {
            CELLRecord *curCell = NULL;
            std::vector<CELLRecord *>::iterator it;
            it = std::find(Records.begin(), Records.end(), curParentRecord);
            if(it == Records.end())
                {
                printf("CELL: Parent Record %08X not found in %s\n", curParentRecord->formID, curParentRecord->GetStrType());
                throw 1;
                return;
                }
            curCell = *it;
            if(curRecord == NULL)
                {
                Records.erase(it);
                delete curParentRecord;
                }
            else
                {
                if(curRecord == (Record *)curCell->PGRD)
                    curCell->PGRD = NULL;
                else if(curRecord == (Record *)curCell->LAND)
                    curCell->LAND = NULL;
                else
                    {
                    std::vector<ACHRRecord *>::iterator ACHR_it;
                    std::vector<ACRERecord *>::iterator ACRE_it;
                    std::vector<REFRRecord *>::iterator REFR_it;
                    ACHR_it = std::find(curCell->ACHR.begin(), curCell->ACHR.end(), curRecord);
                    if(ACHR_it != curCell->ACHR.end())
                        curCell->ACHR.erase(ACHR_it);
                    else
                        {
                        ACRE_it = std::find(curCell->ACRE.begin(), curCell->ACRE.end(), curRecord);
                        if(ACRE_it != curCell->ACRE.end())
                            curCell->ACRE.erase(ACRE_it);
                        else
                            {
                            REFR_it = std::find(curCell->REFR.begin(), curCell->REFR.end(), curRecord);
                            if(REFR_it != curCell->REFR.end())
                                curCell->REFR.erase(REFR_it);
                            else
                                {
                                printf("Record %08X with parent %08X not found in %s\n", curRecord->formID, curParentRecord->formID, curParentRecord->GetStrType());
                                throw 1;
                                return;
                                }
                            }
                        }
                    }
                delete curRecord;
                }
            return;
            }
        unsigned int UpdateReferences(unsigned int origFormID, unsigned int newFormID, _FormIDHandler &FormIDHandler)
            {
            unsigned int count = 0;
            CELLRecord *curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                count += curRecord->UpdateReferences(origFormID, newFormID, FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACHR.size(); ++x)
                    count += curRecord->ACHR[x]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                for(unsigned int x = 0; x < curRecord->ACRE.size(); ++x)
                    count += curRecord->ACRE[x]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                for(unsigned int x = 0; x < curRecord->REFR.size(); ++x)
                    count += curRecord->REFR[x]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                if(curRecord->PGRD != NULL)
                    count += curRecord->PGRD->UpdateReferences(origFormID, newFormID, FormIDHandler);
                }
            return count;
            }

        int Unload()
            {
            CELLRecord *curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                for(unsigned int x = 0; x < curRecord->ACHR.size(); ++x)
                    if(curRecord->ACHR[x]->recData != NULL)
                        curRecord->ACHR[x]->Unload();
                for(unsigned int x = 0; x < curRecord->ACRE.size(); ++x)
                    if(curRecord->ACRE[x]->recData != NULL)
                        curRecord->ACRE[x]->Unload();
                for(unsigned int x = 0; x < curRecord->REFR.size(); ++x)
                    if(curRecord->REFR[x]->recData != NULL)
                        curRecord->REFR[x]->Unload();
                if(curRecord->PGRD != NULL && curRecord->PGRD->recData != NULL)
                    curRecord->PGRD->Unload();
                if(curRecord->recData != NULL)
                    curRecord->Unload();
                }
            return 0;
            }
        bool CheckMasters(unsigned char MASTIndex, _FormIDHandler &FormIDHandler)
            {
            CELLRecord *curRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curRecord = Records[p];
                if(FormIDHandler.UsesMaster(curRecord->formID, MASTIndex))
                    return true;
                if(curRecord->CheckMasters(MASTIndex, FormIDHandler))
                    return true;
                for(unsigned int x = 0; x < curRecord->ACHR.size(); ++x)
                    {
                    if(FormIDHandler.UsesMaster(curRecord->ACHR[x]->formID, MASTIndex))
                        return true;
                    if(curRecord->ACHR[x]->CheckMasters(MASTIndex, FormIDHandler))
                        return true;
                    }
                for(unsigned int x = 0; x < curRecord->ACRE.size(); ++x)
                    {
                    if(FormIDHandler.UsesMaster(curRecord->ACRE[x]->formID, MASTIndex))
                        return true;
                    if(curRecord->ACRE[x]->CheckMasters(MASTIndex, FormIDHandler))
                        return true;
                    }
                for(unsigned int x = 0; x < curRecord->REFR.size(); ++x)
                    {
                    if(FormIDHandler.UsesMaster(curRecord->REFR[x]->formID, MASTIndex))
                        return true;
                    if(curRecord->REFR[x]->CheckMasters(MASTIndex, FormIDHandler))
                        return true;
                    }
                if(curRecord->PGRD != NULL)
                    {
                    if(FormIDHandler.UsesMaster(curRecord->PGRD->formID, MASTIndex))
                        return true;
                    if(curRecord->PGRD->CheckMasters(MASTIndex, FormIDHandler))
                        return true;
                    }
                }
            return false;
            }
        unsigned int WriteGRUP(_FileHandler &SaveHandler, _FormIDHandler &FormIDHandler, bool CloseMod)
            {
            unsigned int numCELLRecords = (unsigned int)Records.size();
            if(numCELLRecords == 0)
                return 0;
            unsigned int type = eGRUP;
            unsigned int gType = eTop;
            unsigned int TopSize = 0;
            unsigned int TopSizePos = 0;
            unsigned int blockSize = 0;
            unsigned int blockSizePos = 0;
            unsigned int subBlockSize = 0;
            unsigned int subBlockSizePos = 0;
            unsigned int childrenSize = 0;
            unsigned int childrenSizePos = 0;
            unsigned int childSize = 0;
            unsigned int childSizePos = 0;

            unsigned int formCount = 0;

            unsigned int gLabel = eCELL;
            unsigned int numSubBlocks = 0;
            unsigned int numChildren = 0;
            unsigned int numChild = 0;

            unsigned int parentFormID = 0;
            CELLRecord *curRecord = NULL;
            int ObjectID, BlockIndex, SubBlockIndex;

            std::vector< std::vector< std::vector<CELLRecord *> > > BlockedRecords(10, std::vector< std::vector<CELLRecord *> > (10, std::vector<CELLRecord *>()));
            std::vector<Record *> Persistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;
            BlockedRecords.reserve(numCELLRecords);
            for(unsigned int p = 0; p < numCELLRecords; ++p)
                {
                curRecord = Records[p];

                ObjectID = curRecord->formID & 0x00FFFFFF;
                BlockIndex = ObjectID % 10;
                SubBlockIndex = (ObjectID / 10) % 10;

                BlockedRecords[BlockIndex][SubBlockIndex].push_back(curRecord);
                }

            //Top GRUP Header
            SaveHandler.write(&type, 4);
            TopSizePos = SaveHandler.tell();
            SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
            //SaveHandler.write(&TopSize, 4);
            SaveHandler.write(&gLabel, 4);
            SaveHandler.write(&gType, 4);
            SaveHandler.write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numCELLRecords;
            for(unsigned int curBlock = 0; curBlock < 10; ++curBlock)
                {
                gType = eInteriorBlock;
                for(unsigned int curSubBlock = 0; curSubBlock < 10; ++curSubBlock)
                    {
                    numSubBlocks = (unsigned int)BlockedRecords[curBlock][curSubBlock].size();
                    if(numSubBlocks != 0)
                        {
                        if(gType == eInteriorBlock)
                            {
                            SaveHandler.write(&type, 4);
                            blockSizePos = SaveHandler.tell();
                            SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                            SaveHandler.write(&curBlock, 4);
                            SaveHandler.write(&gType, 4);
                            SaveHandler.write(&stamp, 4);
                            ++formCount;
                            blockSize = 20;
                            }
                        gType = eInteriorSubBlock;
                        SaveHandler.write(&type, 4);
                        subBlockSizePos = SaveHandler.tell();
                        SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                        SaveHandler.write(&curSubBlock, 4);
                        SaveHandler.write(&gType, 4);
                        SaveHandler.write(&stamp, 4);
                        ++formCount;
                        subBlockSize = 20;
                        for(unsigned int p = 0; p < numSubBlocks; ++p)
                            {
                            curRecord = BlockedRecords[curBlock][curSubBlock][p];
                            parentFormID = curRecord->formID;
                            FormIDHandler.CollapseFormID(parentFormID);
                            subBlockSize += curRecord->Write(SaveHandler, FormIDHandler);
                            //Place the PGRD, ACHR, ACRE, and REFR records into their proper GRUP
                            if(curRecord->PGRD != NULL)
                                Temporary.push_back(curRecord->PGRD);
                            if(CloseMod)
                                curRecord->PGRD = NULL;

                            for(unsigned int y = 0; y < curRecord->ACHR.size(); ++y)
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

                            for(unsigned int y = 0; y < curRecord->ACRE.size(); ++y)
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

                            for(unsigned int y = 0; y < curRecord->REFR.size(); ++y)
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

                            numChildren = (unsigned int)Persistent.size() + (unsigned int)VWD.size() + (unsigned int)Temporary.size();
                            if(numChildren)
                                {
                                formCount += numChildren;
                                gType = eCellChildren;
                                SaveHandler.write(&type, 4);
                                childrenSizePos = SaveHandler.tell();
                                SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                                SaveHandler.write(&parentFormID, 4);
                                SaveHandler.write(&gType, 4);
                                SaveHandler.write(&stamp, 4);
                                ++formCount;
                                childrenSize = 20;

                                numChild = (unsigned int)Persistent.size();
                                if(numChild)
                                    {
                                    gType = eCellPersistent;
                                    SaveHandler.write(&type, 4);
                                    childSizePos = SaveHandler.tell();
                                    SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                                    SaveHandler.write(&parentFormID, 4);
                                    SaveHandler.write(&gType, 4);
                                    SaveHandler.write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(unsigned int x = 0; x < numChild; ++x)
                                        {
                                        childSize += Persistent[x]->Write(SaveHandler, FormIDHandler);
                                        if(CloseMod)
                                            delete Persistent[x];
                                        }
                                    childrenSize += childSize;
                                    SaveHandler.writeAt(childSizePos, &childSize, 4);
                                    Persistent.clear();
                                    }

                                numChild = (unsigned int)VWD.size();
                                if(numChild)
                                    {
                                    gType = eCellVWD;
                                    SaveHandler.write(&type, 4);
                                    childSizePos = SaveHandler.tell();
                                    SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                                    SaveHandler.write(&parentFormID, 4);
                                    SaveHandler.write(&gType, 4);
                                    SaveHandler.write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(unsigned int x = 0; x < numChild; ++x)
                                        {
                                        childSize += VWD[x]->Write(SaveHandler, FormIDHandler);
                                        if(CloseMod)
                                            delete VWD[x];
                                        }
                                    childrenSize += childSize;
                                    SaveHandler.writeAt(childSizePos, &childSize, 4);
                                    VWD.clear();
                                    }

                                numChild = (unsigned int)Temporary.size();
                                if(numChild)
                                    {
                                    gType = eCellTemporary;
                                    SaveHandler.write(&type, 4);
                                    childSizePos = SaveHandler.tell();
                                    SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                                    SaveHandler.write(&parentFormID, 4);
                                    SaveHandler.write(&gType, 4);
                                    SaveHandler.write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(unsigned int x = 0; x < numChild; ++x)
                                        {
                                        childSize += Temporary[x]->Write(SaveHandler, FormIDHandler);
                                        if(CloseMod)
                                            delete Temporary[x];
                                        }
                                    childrenSize += childSize;
                                    SaveHandler.writeAt(childSizePos, &childSize, 4);
                                    Temporary.clear();
                                    }
                                subBlockSize += childrenSize;
                                SaveHandler.writeAt(childrenSizePos, &childrenSize, 4);
                                }
                            if(CloseMod)
                                delete curRecord;
                            }
                        blockSize += subBlockSize;
                        SaveHandler.writeAt(subBlockSizePos, &subBlockSize, 4);
                        BlockedRecords[curBlock][curSubBlock].clear();
                        }
                    }
                if(gType != eInteriorBlock)
                    {
                    TopSize += blockSize;
                    SaveHandler.writeAt(blockSizePos, &blockSize, 4);
                    }
                BlockedRecords[curBlock].clear();
                }
            if(CloseMod)
                Records.clear();
            SaveHandler.writeAt(TopSizePos, &TopSize, 4);
            BlockedRecords.clear();
            return formCount;
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
        bool SkimmedGRUP;
        std::vector<WRLDRecord *> Records;
        GRUPRecords():stamp(134671), SkimmedGRUP(false) {}
        ~GRUPRecords()
            {
            for(unsigned int p = 0;p < Records.size(); p++)
                delete Records[p];
            }
        bool Skim(boost::threadpool::pool &Threads, _FileHandler &ReadHandler, _FormIDHandler &FormIDHandler, const bool &FullLoad, const unsigned long &gSize, boost::unordered_set<unsigned int> &UsedFormIDs)
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
            std::map<int, std::map<int, LANDRecord *> > GridXY_LAND;
            unsigned int lastGRUP = 0;
            unsigned long recordType = 0;
            unsigned long gEnd = ReadHandler.tell() + gSize - 20;
            unsigned long recordSize = 0;
            std::pair<boost::unordered_set<unsigned int>::iterator,bool> ret;

            while(ReadHandler.tell() < gEnd){
                ReadHandler.read(&recordType, 4);
                ReadHandler.read(&recordSize, 4);
                switch(recordType)
                    {
                    case eWRLD:
                        curWRLDRecord = new WRLDRecord();
                        ReadHandler.read(&curWRLDRecord->flags, 4);
                        ReadHandler.read(&curWRLDRecord->formID, 4);
                        ReadHandler.read(&curWRLDRecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curWRLDRecord->formID);
                        ret = UsedFormIDs.insert(curWRLDRecord->formID);
                        if(curWRLDRecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curWRLDRecord->GetStrType(), curWRLDRecord->formID);
                        if((curWRLDRecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curWRLDRecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curWRLDRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curWRLDRecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curWRLDRecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            Records.push_back(curWRLDRecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curWRLDRecord->formID);
                            delete curWRLDRecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eCELL:
                        curCELLRecord = new CELLRecord();
                        curCELLRecord->Parent = curWRLDRecord;
                        ReadHandler.read(&curCELLRecord->flags, 4);
                        ReadHandler.read(&curCELLRecord->formID, 4);
                        ReadHandler.read(&curCELLRecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curCELLRecord->formID);
                        ret = UsedFormIDs.insert(curCELLRecord->formID);
                        if(curCELLRecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curCELLRecord->GetStrType(), curCELLRecord->formID);
                        if((curCELLRecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curCELLRecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curCELLRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                curCELLRecord->Read(FormIDHandler); //Can't thread this due to LAND's needing access to XCLC for indexing
                                //Threads.schedule(boost::bind(&Record::Read, curCELLRecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curCELLRecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            switch(lastGRUP)
                                {
                                case eWorld:
                                    delete curWRLDRecord->CELL;
                                    curWRLDRecord->CELL = curCELLRecord;
                                    break;
                                default:
                                    curWRLDRecord->CELLS.push_back(curCELLRecord);
                                    break;
                                }
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curCELLRecord->formID);
                            delete curCELLRecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eGRUP: //All GRUPs will be recreated from scratch on write (saves memory)
                        ReadHandler.set_used(4);
                        ReadHandler.read(&lastGRUP, 4);
                        ReadHandler.set_used(4);
                        break;
                    case eROAD:
                        delete curWRLDRecord->ROAD;
                        curWRLDRecord->ROAD = new ROADRecord();
                        ReadHandler.read(&curWRLDRecord->ROAD->flags, 4);
                        ReadHandler.read(&curWRLDRecord->ROAD->formID, 4);
                        ReadHandler.read(&curWRLDRecord->ROAD->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curWRLDRecord->ROAD->formID);
                        ret = UsedFormIDs.insert(curWRLDRecord->ROAD->formID);
                        if(curWRLDRecord->ROAD->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curWRLDRecord->ROAD->GetStrType(), curWRLDRecord->ROAD->formID);
                        if((curWRLDRecord->ROAD->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curWRLDRecord->ROAD->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curWRLDRecord->ROAD->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curWRLDRecord->ROAD, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curWRLDRecord->ROAD->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curWRLDRecord->ROAD->formID);
                            delete curWRLDRecord->ROAD;
                            curWRLDRecord->ROAD = NULL;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eLAND:
                        delete curCELLRecord->LAND;
                        curCELLRecord->LAND = new LANDRecord();
                        ReadHandler.read(&curCELLRecord->LAND->flags, 4);
                        ReadHandler.read(&curCELLRecord->LAND->formID, 4);
                        ReadHandler.read(&curCELLRecord->LAND->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curCELLRecord->LAND->formID);
                        ret = UsedFormIDs.insert(curCELLRecord->LAND->formID);
                        if(curCELLRecord->LAND->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curCELLRecord->LAND->GetStrType(), curCELLRecord->LAND->formID);
                        if((curCELLRecord->LAND->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curCELLRecord->LAND->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curCELLRecord->LAND->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            curCELLRecord->Read(FormIDHandler); //may already be loaded, but just to be sure.
                            curCELLRecord->XCLC.Load();
                            GridXY_LAND[curCELLRecord->XCLC->posX][curCELLRecord->XCLC->posY] = curCELLRecord->LAND;
                            if(FullLoad)
                                {
                                Threads.schedule(boost::bind(&Record::Read, curCELLRecord->LAND, boost::ref(FormIDHandler)));
                                //curCELLRecord->LAND->Read(fileBuffer, FormIDHandler);
                                }
                            else //Parent CELL is not loaded, so load temporarily for indexing
                                {
                                curCELLRecord->Unload();
                                }
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curCELLRecord->LAND->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curCELLRecord->LAND->formID);
                            delete curCELLRecord->LAND;
                            curCELLRecord->LAND = NULL;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case ePGRD:
                        delete curCELLRecord->PGRD;
                        curCELLRecord->PGRD = new PGRDRecord();
                        ReadHandler.read(&curCELLRecord->PGRD->flags, 4);
                        ReadHandler.read(&curCELLRecord->PGRD->formID, 4);
                        ReadHandler.read(&curCELLRecord->PGRD->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curCELLRecord->PGRD->formID);
                        ret = UsedFormIDs.insert(curCELLRecord->PGRD->formID);
                        if(curCELLRecord->PGRD->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curCELLRecord->PGRD->GetStrType(), curCELLRecord->PGRD->formID);
                        if((curCELLRecord->PGRD->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curCELLRecord->PGRD->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curCELLRecord->PGRD->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curCELLRecord->PGRD, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curCELLRecord->PGRD->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curCELLRecord->PGRD->formID);
                            delete curCELLRecord->PGRD;
                            curCELLRecord->PGRD = NULL;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eACHR:
                        curACHRRecord = new ACHRRecord();
                        ReadHandler.read(&curACHRRecord->flags, 4);
                        ReadHandler.read(&curACHRRecord->formID, 4);
                        ReadHandler.read(&curACHRRecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curACHRRecord->formID);
                        ret = UsedFormIDs.insert(curACHRRecord->formID);
                        if(curACHRRecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curACHRRecord->GetStrType(), curACHRRecord->formID);
                        if((curACHRRecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curACHRRecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curACHRRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curACHRRecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curACHRRecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            curCELLRecord->ACHR.push_back(curACHRRecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curACHRRecord->formID);
                            delete curACHRRecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eACRE:
                        curACRERecord = new ACRERecord();
                        ReadHandler.read(&curACRERecord->flags, 4);
                        ReadHandler.read(&curACRERecord->formID, 4);
                        ReadHandler.read(&curACRERecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curACRERecord->formID);
                        ret = UsedFormIDs.insert(curACRERecord->formID);
                        if(curACRERecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curACRERecord->GetStrType(), curACRERecord->formID);
                        if((curACRERecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curACRERecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curACRERecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curACRERecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curACRERecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            curCELLRecord->ACRE.push_back(curACRERecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curACRERecord->formID);
                            delete curACRERecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    case eREFR:
                        curREFRRecord = new REFRRecord();
                        ReadHandler.read(&curREFRRecord->flags, 4);
                        ReadHandler.read(&curREFRRecord->formID, 4);
                        ReadHandler.read(&curREFRRecord->flagsUnk, 4);
                        FormIDHandler.ExpandFormID(curREFRRecord->formID);
                        ret = UsedFormIDs.insert(curREFRRecord->formID);
                        if(curREFRRecord->IsLoaded())
                            printf("_fIsLoaded Flag used!!!!\n %s - %08X\n", curREFRRecord->GetStrType(), curREFRRecord->formID);
                        if((curREFRRecord->flags & 0x4000) != 0)
                            printf("0x4000 used: %08X!!!!\n", curREFRRecord->formID);
                        //Make sure the formID is unique within the mod
                        if(ret.second == true)
                            {
                            curREFRRecord->recData = ReadHandler.getBuffer(ReadHandler.tell());
                            if(FullLoad)
                                Threads.schedule(boost::bind(&Record::Read, curREFRRecord, boost::ref(FormIDHandler)));
                            if(!FormIDHandler.NewTypes.count(recordType) && FormIDHandler.IsNewRecord(curREFRRecord->formID))
                                FormIDHandler.NewTypes.insert(recordType);
                            curCELLRecord->REFR.push_back(curREFRRecord);
                            }
                        else
                            {
                            printf("Record skipped with duplicate formID: %08X\n", curREFRRecord->formID);
                            delete curREFRRecord;
                            }
                        ReadHandler.set_used(recordSize);
                        break;
                    default:
                        printf("  WRLD: Unexpected Field = %04x\n", recordType);
                        ReadHandler.set_used(gEnd - ReadHandler.tell());
                        break;
                    }
                };
            //Index LAND records by grid
            for(unsigned int x = 0; x < Records.size(); ++x)
                for(unsigned int y = 0; y < Records[x]->CELLS.size(); ++y)
                    if(Records[x]->CELLS[y]->LAND != NULL)
                        {
                        Records[x]->CELLS[y]->XCLC.Load();
                        Records[x]->CELLS[y]->LAND->NorthLand = GridXY_LAND[Records[x]->CELLS[y]->XCLC->posX][Records[x]->CELLS[y]->XCLC->posY + 1];
                        Records[x]->CELLS[y]->LAND->SouthLand = GridXY_LAND[Records[x]->CELLS[y]->XCLC->posX][Records[x]->CELLS[y]->XCLC->posY - 1];
                        Records[x]->CELLS[y]->LAND->EastLand = GridXY_LAND[Records[x]->CELLS[y]->XCLC->posX + 1][Records[x]->CELLS[y]->XCLC->posY];
                        Records[x]->CELLS[y]->LAND->WestLand = GridXY_LAND[Records[x]->CELLS[y]->XCLC->posX - 1][Records[x]->CELLS[y]->XCLC->posY];
                        }
            if(Records.size())
                FormIDHandler.IsEmpty = false;
            return true;
            }
        bool Read(_FormIDHandler &FormIDHandler)
            {
            if(!SkimmedGRUP)
                return false;
            WRLDRecord *curWRLDRecord = NULL;
            CELLRecord *curCELLRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curWRLDRecord = Records[p];
                curWRLDRecord->Read(FormIDHandler);
                if(curWRLDRecord->ROAD != NULL)
                    curWRLDRecord->ROAD->Read(FormIDHandler);
                if(curWRLDRecord->CELL != NULL)
                    {
                    curCELLRecord = curWRLDRecord->CELL;
                    curCELLRecord->Read(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        curCELLRecord->ACHR[y]->Read(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        curCELLRecord->ACRE[y]->Read(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        curCELLRecord->REFR[y]->Read(FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        curCELLRecord->PGRD->Read(FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        curCELLRecord->LAND->Read(FormIDHandler);
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELLS.size(); x++)
                    {
                    curCELLRecord = curWRLDRecord->CELLS[x];
                    curCELLRecord->Read(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        curCELLRecord->ACHR[y]->Read(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        curCELLRecord->ACRE[y]->Read(FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        curCELLRecord->REFR[y]->Read(FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        curCELLRecord->PGRD->Read(FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        curCELLRecord->LAND->Read(FormIDHandler);
                    }
                }
            return true;
            }
        void DeleteRecord(Record *curParentRecord, Record *curRecord)
            {
            WRLDRecord *curWorld = NULL;
            std::vector<WRLDRecord *>::iterator it;
            std::vector<CELLRecord *>::iterator CELL_it;
            it = std::find(Records.begin(), Records.end(), curParentRecord);
            if(it == Records.end())
                {
                for(it = Records.begin(); it != Records.end(); it++)
                    {
                    curWorld = *it;
                    if(curParentRecord == (Record *)(curWorld->CELL))
                        break;
                    else
                        {
                        CELL_it = std::find(curWorld->CELLS.begin(), curWorld->CELLS.end(), curParentRecord);
                        if(CELL_it == curWorld->CELLS.end())
                            {
                            printf("WRLD:First: Parent %s Record %08X not found\n",  curParentRecord->GetStrType(), curParentRecord->formID);
                            throw 1;
                            return;
                            }
                        break;
                        }
                    }
                }
            else
                curWorld = *it;
            if(curRecord == NULL)
                {
                Records.erase(it);
                delete curParentRecord;
                }
            else
                {
                if(curRecord == (Record *)(curWorld->CELL))
                    curWorld->CELL = NULL;
                else if(curRecord == (Record *)(curWorld->ROAD))
                    curWorld->ROAD = NULL;
                else
                    {
                    CELL_it = std::find(curWorld->CELLS.begin(), curWorld->CELLS.end(), curRecord);
                    if(CELL_it == curWorld->CELLS.end())
                        {
                        CELLRecord *curCell = curWorld->CELL;
                        if(curParentRecord != (Record *)curCell)
                            {
                            CELL_it = std::find(curWorld->CELLS.begin(), curWorld->CELLS.end(), curParentRecord);
                            if(CELL_it == curWorld->CELLS.end())
                                {
                                printf("WRLD:Next: Record %08X with parent %08X not found in %s\n", curRecord->formID, curParentRecord->formID, curParentRecord->GetStrType());
                                throw 1;
                                return;
                                }
                            curCell = *CELL_it;
                            }
                        if(curRecord == (Record *)curCell->PGRD)
                            curCell->PGRD = NULL;
                        else if(curRecord == (Record *)curCell->LAND)
                            curCell->LAND = NULL;
                        else
                            {
                            std::vector<ACHRRecord *>::iterator ACHR_it;
                            std::vector<ACRERecord *>::iterator ACRE_it;
                            std::vector<REFRRecord *>::iterator REFR_it;
                            ACHR_it = std::find(curCell->ACHR.begin(), curCell->ACHR.end(), curRecord);
                            if(ACHR_it != curCell->ACHR.end())
                                curCell->ACHR.erase(ACHR_it);
                            else
                                {
                                ACRE_it = std::find(curCell->ACRE.begin(), curCell->ACRE.end(), curRecord);
                                if(ACRE_it != curCell->ACRE.end())
                                    curCell->ACRE.erase(ACRE_it);
                                else
                                    {
                                    REFR_it = std::find(curCell->REFR.begin(), curCell->REFR.end(), curRecord);
                                    if(REFR_it != curCell->REFR.end())
                                        curCell->REFR.erase(REFR_it);
                                    else
                                        {
                                        printf("WRLD:Last: Record %08X with parent %08X not found in %s\n", curRecord->formID, curParentRecord->formID, curParentRecord->GetStrType());
                                        throw 1;
                                        return;
                                        }
                                    }
                                }
                            }
                        }
                    else
                        curWorld->CELLS.erase(CELL_it);
                    }
                delete curRecord;
                }
            return;
            }
        unsigned int UpdateReferences(unsigned int origFormID, unsigned int newFormID, _FormIDHandler &FormIDHandler)
            {
            unsigned int count = 0;
            WRLDRecord *curWRLDRecord = NULL;
            CELLRecord *curCELLRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curWRLDRecord = Records[p];
                count += curWRLDRecord->UpdateReferences(origFormID, newFormID, FormIDHandler);
                if(curWRLDRecord->ROAD != NULL)
                    count += curWRLDRecord->ROAD->UpdateReferences(origFormID, newFormID, FormIDHandler);
                if(curWRLDRecord->CELL != NULL)
                    {
                    curCELLRecord = curWRLDRecord->CELL;
                    count += curCELLRecord->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        count += curCELLRecord->ACHR[y]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        count += curCELLRecord->ACRE[y]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        count += curCELLRecord->REFR[y]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        count += curCELLRecord->PGRD->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        count += curCELLRecord->LAND->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELLS.size(); x++)
                    {
                    curCELLRecord = curWRLDRecord->CELLS[x];
                    count += curCELLRecord->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        count += curCELLRecord->ACHR[y]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        count += curCELLRecord->ACRE[y]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        count += curCELLRecord->REFR[y]->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    if(curCELLRecord->PGRD != NULL)
                        count += curCELLRecord->PGRD->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    if(curCELLRecord->LAND != NULL)
                        count += curCELLRecord->LAND->UpdateReferences(origFormID, newFormID, FormIDHandler);
                    }
                }
            return count;
            }

        int Unload()
            {
            WRLDRecord *curWRLDRecord = NULL;
            CELLRecord *curCELLRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curWRLDRecord = Records[p];
                if(curWRLDRecord->ROAD != NULL && curWRLDRecord->ROAD->recData != NULL)
                    curWRLDRecord->ROAD->Unload();
                if(curWRLDRecord->CELL != NULL)
                    {
                    curCELLRecord = curWRLDRecord->CELL;
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        if(curCELLRecord->ACHR[y]->recData != NULL)
                            curCELLRecord->ACHR[y]->Unload();
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        if(curCELLRecord->ACRE[y]->recData != NULL)
                            curCELLRecord->ACRE[y]->Unload();
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        if(curCELLRecord->REFR[y]->recData != NULL)
                            curCELLRecord->REFR[y]->Unload();
                    if(curCELLRecord->PGRD != NULL && curCELLRecord->PGRD->recData != NULL)
                        curCELLRecord->PGRD->Unload();
                    if(curCELLRecord->LAND != NULL && curCELLRecord->LAND->recData != NULL)
                        curCELLRecord->LAND->Unload();
                    if(curCELLRecord->recData != NULL)
                        curCELLRecord->Unload();
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELLS.size(); x++)
                    {
                    curCELLRecord = curWRLDRecord->CELLS[x];
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        if(curCELLRecord->ACHR[y]->recData != NULL)
                            curCELLRecord->ACHR[y]->Unload();
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        if(curCELLRecord->ACRE[y]->recData != NULL)
                            curCELLRecord->ACRE[y]->Unload();
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        if(curCELLRecord->REFR[y]->recData != NULL)
                            curCELLRecord->REFR[y]->Unload();
                    if(curCELLRecord->PGRD != NULL && curCELLRecord->PGRD->recData != NULL)
                        curCELLRecord->PGRD->Unload();
                    if(curCELLRecord->LAND != NULL && curCELLRecord->LAND->recData != NULL)
                        curCELLRecord->LAND->Unload();
                    if(curCELLRecord->recData != NULL)
                        curCELLRecord->Unload();
                    }
                if(curWRLDRecord->recData != NULL)
                    curWRLDRecord->Unload();
                }
            return 0;
            }
        bool CheckMasters(unsigned char MASTIndex, _FormIDHandler &FormIDHandler)
            {
            WRLDRecord *curWRLDRecord = NULL;
            CELLRecord *curCELLRecord = NULL;
            for(unsigned int p = 0; p < Records.size(); p++)
                {
                curWRLDRecord = Records[p];
                if(FormIDHandler.UsesMaster(curWRLDRecord->formID, MASTIndex))
                    return true;
                if(curWRLDRecord->CheckMasters(MASTIndex, FormIDHandler))
                    return true;
                if(curWRLDRecord->ROAD != NULL)
                    {
                    if(FormIDHandler.UsesMaster(curWRLDRecord->ROAD->formID, MASTIndex))
                        return true;
                    if(curWRLDRecord->ROAD->CheckMasters(MASTIndex, FormIDHandler))
                        return true;
                    }
                if(curWRLDRecord->CELL != NULL)
                    {
                    curCELLRecord = curWRLDRecord->CELL;
                    if(FormIDHandler.UsesMaster(curCELLRecord->formID, MASTIndex))
                        return true;
                    if(curCELLRecord->CheckMasters(MASTIndex, FormIDHandler))
                        return true;
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->ACHR[y]->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->ACHR[y]->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->ACRE[y]->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->ACRE[y]->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->REFR[y]->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->REFR[y]->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    if(curCELLRecord->PGRD != NULL)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->PGRD->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->PGRD->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    if(curCELLRecord->LAND != NULL)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->LAND->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->LAND->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    }
                for(unsigned int x = 0; x < curWRLDRecord->CELLS.size(); x++)
                    {
                    curCELLRecord = curWRLDRecord->CELLS[x];
                    if(FormIDHandler.UsesMaster(curCELLRecord->formID, MASTIndex))
                        return true;
                    if(curCELLRecord->CheckMasters(MASTIndex, FormIDHandler))
                        return true;
                    for(unsigned int y = 0; y < curCELLRecord->ACHR.size(); ++y)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->ACHR[y]->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->ACHR[y]->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    for(unsigned int y = 0; y < curCELLRecord->ACRE.size(); ++y)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->ACRE[y]->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->ACRE[y]->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    for(unsigned int y = 0; y < curCELLRecord->REFR.size(); ++y)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->REFR[y]->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->REFR[y]->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    if(curCELLRecord->PGRD != NULL)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->PGRD->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->PGRD->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    if(curCELLRecord->LAND != NULL)
                        {
                        if(FormIDHandler.UsesMaster(curCELLRecord->LAND->formID, MASTIndex))
                            return true;
                        if(curCELLRecord->LAND->CheckMasters(MASTIndex, FormIDHandler))
                            return true;
                        }
                    }
                }
            return false;
            }
        unsigned int WriteGRUP(_FileHandler &SaveHandler, _FormIDHandler &FormIDHandler, bool CloseMod)
            {
            unsigned int numWrldRecords = (unsigned int)Records.size();
            if(numWrldRecords == 0)
                return 0;
            unsigned int type = eGRUP;
            unsigned int gType = eTop;
            unsigned int gLabel = eWRLD;
            unsigned int TopSize = 0;
            unsigned int TopSizePos = 0;
            unsigned int worldSize = 0;
            unsigned int worldSizePos = 0;
            unsigned int blockSize = 0;
            unsigned int blockSizePos = 0;
            unsigned int subBlockSize = 0;
            unsigned int subBlockSizePos = 0;
            unsigned int childrenSize = 0;
            unsigned int childrenSizePos = 0;
            unsigned int childSize = 0;
            unsigned int childSizePos = 0;

            unsigned int formCount = 0;

            unsigned int numCellRecords = 0;
            unsigned int numSubBlocks = 0;
            unsigned int numChildren = 0;
            unsigned int numChild = 0;

            WRLDRecord *curWorld = NULL;
            CELLRecord *curCell = NULL;
            unsigned int worldFormID = 0;
            unsigned int cellFormID = 0;
            int gridX, gridY;
            unsigned int BlockIndex, SubBlockIndex;

            std::map<unsigned int, std::map<unsigned int, std::vector<CELLRecord *> > > BlockedRecords;
            std::vector<Record *> Persistent;
            std::vector<Record *> FixedPersistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;

            //Top GRUP Header
            SaveHandler.write(&type, 4);
            TopSizePos = SaveHandler.tell();
            SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
            //SaveHandler.write(&TopSize, 4);
            SaveHandler.write(&gLabel, 4);
            SaveHandler.write(&gType, 4);
            SaveHandler.write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numWrldRecords;
            for(unsigned int x = 0; x < numWrldRecords; ++x)
                {
                curWorld = Records[x];
                worldFormID = curWorld->formID;
                FormIDHandler.CollapseFormID(worldFormID);
                TopSize += curWorld->Write(SaveHandler, FormIDHandler);

                numCellRecords = (unsigned int)curWorld->CELLS.size();
                for(unsigned int p = 0; p < numCellRecords; ++p)
                    {
                    curCell = curWorld->CELLS[p];

                    //All persistent references must be moved to the world cell
                    for(unsigned int y = 0; y < curCell->ACRE.size(); ++y)
                        if(curCell->ACRE[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->ACRE[y]);

                    for(unsigned int y = 0; y < curCell->ACHR.size(); ++y)
                        if(curCell->ACHR[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->ACHR[y]);

                    for(unsigned int y = 0; y < curCell->REFR.size(); ++y)
                        if(curCell->REFR[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->REFR[y]);

                    curCell->Read(FormIDHandler);
                    curCell->XCLC.Load();
                    gridX = (int)floor(curCell->XCLC->posX / 8.0);
                    gridY = (int)floor(curCell->XCLC->posY / 8.0);
                    if(curCell->recData != NULL)
                        curCell->Unload();
                    SubBlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                    gridX = (int)floor(gridX / 4.0);
                    gridY = (int)floor(gridY / 4.0);
                    BlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);

                    BlockedRecords[BlockIndex][SubBlockIndex].push_back(curCell);
                    }

                if(curWorld->CELL == NULL && FixedPersistent.size()) //create a default dummy cell for persistents
                    {
                    curWorld->CELL = new CELLRecord(FormIDHandler.NextExpandedFID());
                    curWorld->CELL->Parent = curWorld;
                    curWorld->CELL->IsHasWater(true);
                    curWorld->CELL->IsPersistent(true);
                    curWorld->CELL->XCLC.Load();
                    }

                if(curWorld->ROAD != NULL || curWorld->CELL != NULL || curWorld->CELLS.size() > 0)
                    {
                    gType = eWorld;
                    SaveHandler.write(&type, 4);
                    worldSizePos = SaveHandler.tell();
                    SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                    SaveHandler.write(&worldFormID, 4);
                    SaveHandler.write(&gType, 4);
                    SaveHandler.write(&stamp, 4);
                    ++formCount;
                    worldSize = 20;
                    
                    if(curWorld->ROAD != NULL)
                        {
                        worldSize += curWorld->ROAD->Write(SaveHandler, FormIDHandler);
                        ++formCount;
                        if(CloseMod)
                            {
                            delete curWorld->ROAD;
                            curWorld->ROAD = NULL;
                            }
                        }

                    if(curWorld->CELL != NULL)
                        {
                        curCell = curWorld->CELL;
                        cellFormID = curCell->formID;
                        FormIDHandler.CollapseFormID(cellFormID);
                        worldSize += curCell->Write(SaveHandler, FormIDHandler);
                        ++formCount;

                        if(curCell->LAND != NULL)
                            Temporary.push_back(curCell->LAND);
                        if(CloseMod)
                            curCell->LAND = NULL;

                        if(curCell->PGRD != NULL)
                            Temporary.push_back(curCell->PGRD);
                        if(CloseMod)
                            curCell->PGRD = NULL;

                        for(unsigned int y = 0; y < curCell->ACHR.size(); ++y)
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

                        for(unsigned int y = 0; y < curCell->ACRE.size(); ++y)
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

                        for(unsigned int y = 0; y < curCell->REFR.size(); ++y)
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
                            printf("Ignored %u VWD or Temporary records in the world cell: %08X", VWD.size() + Temporary.size(), worldFormID);
                            
                        VWD.clear();
                        Temporary.clear();

                        numChildren = (unsigned int)Persistent.size() + (unsigned int)FixedPersistent.size();
                        if(numChildren)
                            {
                            formCount += numChildren;
                            gType = eCellChildren;
                            SaveHandler.write(&type, 4);
                            childrenSizePos = SaveHandler.tell();
                            SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                            SaveHandler.write(&cellFormID, 4);
                            SaveHandler.write(&gType, 4);
                            SaveHandler.write(&stamp, 4);
                            ++formCount;
                            childrenSize = 20;

                            //World CELL should only have persistent objects in it
                            gType = eCellPersistent;
                            SaveHandler.write(&type, 4);
                            childSizePos = SaveHandler.tell();
                            SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                            SaveHandler.write(&cellFormID, 4);
                            SaveHandler.write(&gType, 4);
                            SaveHandler.write(&stamp, 4);
                            ++formCount;
                            childSize = 20;
                            
                            numChild = (unsigned int)Persistent.size();
                            for(unsigned int y = 0; y < numChild; ++y)
                                {
                                childSize += Persistent[y]->Write(SaveHandler, FormIDHandler);
                                if(CloseMod)
                                    delete Persistent[y];
                                }

                            //The moved persistents will be deleted by their owning cell when its indexed
                            numChild = (unsigned int)FixedPersistent.size();
                            for(unsigned int y = 0; y < numChild; ++y)
                                childSize += FixedPersistent[y]->Write(SaveHandler, FormIDHandler);

                            childrenSize += childSize;
                            SaveHandler.writeAt(childSizePos, &childSize, 4);
                            Persistent.clear();
                            FixedPersistent.clear();
                            worldSize += childrenSize;
                            SaveHandler.writeAt(childrenSizePos, &childrenSize, 4);
                            }
                        if(CloseMod)
                            delete curCell;
                        }

                    formCount += (unsigned int)curWorld->CELLS.size();
                    for(std::map<unsigned int, std::map<unsigned int, std::vector<CELLRecord *> > >::iterator curBlock = BlockedRecords.begin(); curBlock != BlockedRecords.end(); ++curBlock)
                        {
                        gType = eExteriorBlock;
                        SaveHandler.write(&type, 4);
                        blockSizePos = SaveHandler.tell();
                        SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                        SaveHandler.write(&curBlock->first, 4);
                        SaveHandler.write(&gType, 4);
                        SaveHandler.write(&stamp, 4);
                        ++formCount;
                        blockSize = 20;
                        
                        for(std::map<unsigned int, std::vector<CELLRecord *> >::iterator curSubBlock = curBlock->second.begin(); curSubBlock != curBlock->second.end(); ++curSubBlock)
                            {
                            gType = eExteriorSubBlock;
                            SaveHandler.write(&type, 4);
                            subBlockSizePos = SaveHandler.tell();
                            SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                            SaveHandler.write(&curSubBlock->first, 4);
                            SaveHandler.write(&gType, 4);
                            SaveHandler.write(&stamp, 4);
                            ++formCount;
                            subBlockSize = 20;

                            numSubBlocks = (unsigned int)curSubBlock->second.size();
                            for(unsigned int p = 0; p < numSubBlocks; ++p)
                                {
                                curCell = curSubBlock->second[p];
                                cellFormID = curCell->formID;
                                FormIDHandler.CollapseFormID(cellFormID);
                                subBlockSize += curCell->Write(SaveHandler, FormIDHandler);
                                //Place the PGRD, ACHR, ACRE, and REFR records into their proper GRUP

                                if(curCell->LAND != NULL)
                                    Temporary.push_back(curCell->LAND);
                                if(CloseMod)
                                    curCell->LAND = NULL;

                                if(curCell->PGRD != NULL)
                                    Temporary.push_back(curCell->PGRD);
                                if(CloseMod)
                                    curCell->PGRD = NULL;

                                for(unsigned int y = 0; y < curCell->ACHR.size(); ++y)
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

                                for(unsigned int y = 0; y < curCell->ACRE.size(); ++y)
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

                                for(unsigned int y = 0; y < curCell->REFR.size(); ++y)
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

                                numChildren = (unsigned int)VWD.size() + (unsigned int)Temporary.size();
                                if(numChildren)
                                    {
                                    formCount += numChildren;
                                    gType = eCellChildren;
                                    SaveHandler.write(&type, 4);
                                    childrenSizePos = SaveHandler.tell();
                                    SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                                    SaveHandler.write(&cellFormID, 4);
                                    SaveHandler.write(&gType, 4);
                                    SaveHandler.write(&stamp, 4);
                                    ++formCount;
                                    childrenSize = 20;

                                    numChild = (unsigned int)VWD.size();
                                    if(numChild)
                                        {
                                        gType = eCellVWD;
                                        SaveHandler.write(&type, 4);
                                        childSizePos = SaveHandler.tell();
                                        SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                                        SaveHandler.write(&cellFormID, 4);
                                        SaveHandler.write(&gType, 4);
                                        SaveHandler.write(&stamp, 4);
                                        ++formCount;
                                        childSize = 20;

                                        for(unsigned int x = 0; x < numChild; ++x)
                                            {
                                            childSize += VWD[x]->Write(SaveHandler, FormIDHandler);
                                            if(CloseMod)
                                                delete VWD[x];
                                            }
                                        childrenSize += childSize;
                                        SaveHandler.writeAt(childSizePos, &childSize, 4);
                                        VWD.clear();
                                        }

                                    numChild = (unsigned int)Temporary.size();
                                    if(numChild)
                                        {
                                        gType = eCellTemporary;
                                        SaveHandler.write(&type, 4);
                                        childSizePos = SaveHandler.tell();
                                        SaveHandler.set_used(4); //Placeholder: will be overwritten with correct value later.
                                        SaveHandler.write(&cellFormID, 4);
                                        SaveHandler.write(&gType, 4);
                                        SaveHandler.write(&stamp, 4);
                                        ++formCount;
                                        childSize = 20;

                                        for(unsigned int x = 0; x < numChild; ++x)
                                            {
                                            childSize += Temporary[x]->Write(SaveHandler, FormIDHandler);
                                            if(CloseMod)
                                                delete Temporary[x];
                                            }
                                        childrenSize += childSize;
                                        SaveHandler.writeAt(childSizePos, &childSize, 4);
                                        Temporary.clear();
                                        }
                                    subBlockSize += childrenSize;
                                    SaveHandler.writeAt(childrenSizePos, &childrenSize, 4);
                                    }
                                if(CloseMod)
                                    delete curCell;
                                }
                            blockSize += subBlockSize;
                            SaveHandler.writeAt(subBlockSizePos, &subBlockSize, 4);
                            curSubBlock->second.clear();
                            }
                        worldSize += blockSize;
                        SaveHandler.writeAt(blockSizePos, &blockSize, 4);
                        curBlock->second.clear();
                        }
                    TopSize += worldSize;
                    SaveHandler.writeAt(worldSizePos, &worldSize, 4);
                    }
                BlockedRecords.clear();
                }
            if(CloseMod)
                Records.clear();
            SaveHandler.writeAt(TopSizePos, &TopSize, 4);
                
            return formCount;
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
