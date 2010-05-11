# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
//#pragma once
//// SubGRUPRecord.h
//#include "Common.h"
////ADD DEFINITIONS HERE, IF NEEDED
//#include "ACHRRecord.h"
//#include "ACRERecord.h"
//#include "REFRRecord.h"
//#include "PGRDRecord.h"
//#include "LANDRecord.h"
//#include <vector>
//
//template<class T>
//class SubGRUPRecords
//    {
//    public:
//        GRUPCONTAINER Header;
//        unsigned int gStart, gEnd;
//        bool SkimmedGRUP, LoadedGRUP;
//        std::vector<T *> Records;
//        SubGRUPRecords():SkimmedGRUP(false), LoadedGRUP(false), gStart(0), gEnd(0) {}
//        SubGRUPRecords(GRUPCONTAINER *cParent):Header(cParent), SkimmedGRUP(false), LoadedGRUP(false), gStart(0), gEnd(0) {}
//        ~SubGRUPRecords()
//            {
//            #ifdef _FDEBUG
//            if(Header.IsLoaded())
//                printf("  %c%c%c%c Record Cleaned\n", ((char*)&Header.Header.label)[0], ((char*)&Header.Header.label)[1], ((char*)&Header.Header.label)[2], ((char*)&Header.Header.label)[3]);
//            #endif
//            for(unsigned int p = 0;p < Records.size(); p++)
//                delete Records[p];
//            }
//        void SetHeader(GRUPHEADER &curHeader, const unsigned int &cPos)
//            {
//            Header.Header = curHeader;
//            Header.isLoaded = true;
//            gStart = cPos;
//            gEnd = gStart - 20 + Header.Header.size;
//            }
//        bool Skim(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler, const bool &FullLoad)
//            {
//            if(SkimmedGRUP || !Header.isLoaded || gStart == gEnd)
//                return false;
//            SkimmedGRUP = true;
//            T * curRecord = NULL;
//            unsigned int curPos = gStart;
//
//            while(curPos < gEnd){
//                curRecord = new T(&Header);
//                curRecord->ReadHeader(&fileBuffer[curPos], curPos);
//                FormIDHandler.ExpandFormID(curRecord->Header.Header.formID);
//                curPos += curRecord->Header.Header.size;
//                if(FullLoad) curRecord->Read(fileBuffer, FormIDHandler);
//                Records.push_back(curRecord);
//                };
//            return true;
//            }
//        bool Read(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler)
//            {
//            if(LoadedGRUP || !SkimmedGRUP || !Header.isLoaded || gStart == gEnd)
//                return false;
//            LoadedGRUP = true;
//            for(unsigned int p = 0; p < Records.size(); p++)
//                Records[p]->Read(fileBuffer, FormIDHandler);
//            return true;
//            }
//        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
//            {
//            for(unsigned int p = 0; p < Records.size(); p++)
//                {
//                Records[p]->CollapseFormIDs(FormIDHandler);
//                }
//            return;
//            }
//        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
//            {
//            for(unsigned int p = 0; p < Records.size(); p++)
//                {
//                Records[p]->ExpandFormIDs(FormIDHandler);
//                }
//            return;
//            }
//        T * SetSubRecord(T *newRecord, unsigned int groupType, bool allowMerge, bool asOverride)
//            {
//            unsigned int nRecSize, oRecSize;
//            T *curRecord = NULL;
//            unsigned int vSize = 0;
//            if(newRecord == NULL)
//                return NULL;
//            //If record exists, merge new record onto old
//            if(asOverride)
//                for(unsigned int p = 0; p < Records.size(); p++)
//                    if(Records[p]->Header.Header.formID == newRecord->Header.Header.formID)
//                        {
//                        if(!allowMerge)
//                            {
//                            delete newRecord;
//                            return NULL;
//                            }
//                        curRecord = Records[p];
//                        oRecSize = curRecord->Header.Header.size;
//                        //curRecord->CopyFrom(newRecord);
//                        nRecSize = curRecord->Header.Header.size;
//                        curRecord->Header.UpdateSize(oRecSize, nRecSize);
//                        delete newRecord;
//                        return curRecord;
//                        }
//            //Otherwise, assign the record formID, create GRUP Header if needed and register the record
//            if(!Header.IsLoaded())
//                {
//                Header.Header.type = eGRUP;
//                Header.UpdateSize(sizeof(GRUPHEADER));
//                //Header.Header.size = sizeof(GRUPHEADER);
//                //Header.Header.label = *ParentFormID;
//                Header.Header.gType = groupType;
//                Header.Header.stamp = 134671;
//                Header.isLoaded = true;
//                //newRecord->curGRUP = &Header;
//                gEnd = gStart = 0;
//                }
//            //Add new record size to running group size tally
//            newRecord->Header.ParentHeader = &Header;
//            Header.UpdateSize(newRecord->Header.Header.size);
//            Header.UpdateSize(sizeof(RECHEADER));
//            Records.push_back(newRecord);
//            return newRecord;
//            }
//
//        void WriteGRUP(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
//            {
//            if(Records.size() == 0)
//                return;
//
//            _writeBuffer(buffer, &Header.Header, sizeof(GRUPHEADER), usedBuffer);
//            for(unsigned int p = 0; p < Records.size(); p++)
//                Records[p]->Write(fh, buffer, usedBuffer);
//            }
//        #ifdef _DEBUG
//        void Debug(int debugLevel)
//            {
//            if(Header.IsLoaded())
//                printf("    SubRecords Present: %u\n", Records.size());
//            if(debugLevel > 2)
//                for(std::vector<T*>::iterator curRecord = Records.begin();curRecord!=Records.end();curRecord++)
//                    (*curRecord)->Debug(debugLevel);
//            }
//        #endif
//    };
//
////class CELLChildren
////    {
////    public:
////        enum subGRUPs {
////            eACHR = 0x52484341,
////            eACRE = 0x45524341,
////            eREFR = 0x52464552,
////            ePGRD = 0x44524750,
////            eLAND = 0x444E414C
////            };
////        GRUPCONTAINER Header;
////        unsigned int gStart, gEnd, eChildType;
////        bool SkimmedGRUP, LoadedGRUP;
////        std::vector<ACHRRecord *> ACHRRecords;
////        std::vector<ACRERecord *> ACRERecords;
////        std::vector<REFRRecord *> REFRRecords;
////        PGRDRecord *PGRD;
////        LANDRecord *LAND;
////        std::vector<Record *> Records;
////        CELLChildren(unsigned int eCurChildType):SkimmedGRUP(false), LoadedGRUP(false), gStart(0), gEnd(0), eChildType(eCurChildType), PGRD(NULL), LAND(NULL) {}
////        ~CELLChildren()
////            {
////            #ifdef _FDEBUG
////            if(Header.IsLoaded())
////                printf("  %c%c%c%c Record Cleaned\n", ((char*)&Header.Header.label)[0], ((char*)&Header.Header.label)[1], ((char*)&Header.Header.label)[2], ((char*)&Header.Header.label)[3]);
////            #endif
////            for(unsigned int p = 0;p < Records.size(); p++)
////                delete Records[p];
////            }
////        void SetHeader(GRUPCONTAINER *curParentHeader, GRUPHEADER &curHeader, const unsigned int &cPos)
////            {
////            Header.ParentHeader = curParentHeader;
////            Header.Header = curHeader;
////            Header.isLoaded = true;
////            //Header.Header.label refers to the parent record
////            //Since this implementation directly stores the children with the parent record it isn't necessary to register it.
////            //It will simply use the formID of the parent record (which is registered) as needed.
////            //FormIDHandler->RegisterExplicit(&Header.Header.label);
////            gStart = cPos;
////            gEnd = gStart - 20 + Header.Header.size;
////            }
////        bool Skim(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler, const bool &FullLoad)
////            {
////            if(SkimmedGRUP || !Header.isLoaded || gStart == gEnd)
////                return false;
////            SkimmedGRUP = true;
////            RECHEADER curHeader;
////            ACHRRecord * curACHRRecord = NULL;
////            ACRERecord * curACRERecord = NULL;
////            REFRRecord * curREFRRecord = NULL;
////            unsigned int curPos = gStart;
////
////            while(curPos < gEnd){
////                _readBuffer(&curHeader, fileBuffer, sizeof(RECHEADER), curPos);
////                switch(curHeader.type)
////                    {
////                    case eACHR:
////                        curACHRRecord = new ACHRRecord(&Header);
////                        curACHRRecord->SetHeader(curHeader, curPos);
////                        FormIDHandler.ExpandFormID(curACHRRecord->Header.Header.formID);
////                        curPos += curACHRRecord->Header.Header.size;
////                        if(FullLoad) curACHRRecord->Read(fileBuffer, FormIDHandler);
////                        ACHRRecords.push_back(curACHRRecord);
////                        Records.push_back(curACHRRecord);
////                        break;
////                    case eACRE:
////                        curACRERecord = new ACRERecord(&Header);
////                        curACRERecord->SetHeader(curHeader, curPos);
////                        FormIDHandler.ExpandFormID(curACRERecord->Header.Header.formID);
////                        curPos += curACRERecord->Header.Header.size;
////                        if(FullLoad) curACRERecord->Read(fileBuffer, FormIDHandler);
////                        ACRERecords.push_back(curACRERecord);
////                        Records.push_back(curACRERecord);
////                        break;
////                    case eREFR:
////                        curREFRRecord = new REFRRecord(&Header);
////                        curREFRRecord->SetHeader(curHeader, curPos);
////                        FormIDHandler.ExpandFormID(curREFRRecord->Header.Header.formID);
////                        curPos += curREFRRecord->Header.Header.size;
////                        if(FullLoad) curREFRRecord->Read(fileBuffer, FormIDHandler);
////                        REFRRecords.push_back(curREFRRecord);
////                        Records.push_back(curREFRRecord);
////                        break;
////                    case ePGRD:
////                        delete PGRD;
////                        PGRD = new PGRDRecord(&Header);
////                        PGRD->SetHeader(curHeader, curPos);
////                        FormIDHandler.ExpandFormID(PGRD->Header.Header.formID);
////                        curPos += PGRD->Header.Header.size;
////                        if(FullLoad) PGRD->Read(fileBuffer, FormIDHandler);
////                        Records.push_back(PGRD);
////                        break;
////                    case eLAND:
////                        delete LAND;
////                        LAND = new LANDRecord(&Header);
////                        LAND->SetHeader(curHeader, curPos);
////                        FormIDHandler.ExpandFormID(LAND->Header.Header.formID);
////                        curPos += LAND->Header.Header.size;
////                        if(FullLoad) LAND->Read(fileBuffer, FormIDHandler);
////                        Records.push_back(LAND);
////                        break;
////                    default:
////                        printf("  CELLChildren: Unexpected Record = %04x\n", curHeader.type);
////                        printf("  Size = %u\n", curHeader.size);
////                        printf("  CurPos = %04x\n\n", curPos - 20);
////                        curPos += curHeader.size;
////                        break;
////                    }
////                };
////            return true;
////            }
////        bool Read(unsigned char *fileBuffer, _FormIDHandler &FormIDHandler)
////            {
////            if(LoadedGRUP || !SkimmedGRUP || !Header.isLoaded || gStart == gEnd)
////                return false;
////            LoadedGRUP = true;
////            for(unsigned int p = 0; p < Records.size(); p++)
////                Records[p]->Read(fileBuffer, FormIDHandler);
////            return true;
////            }
////        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
////            {
////            for(unsigned int p = 0; p < Records.size(); p++)
////                {
////                Records[p]->CollapseFormIDs(FormIDHandler);
////                }
////            return;
////            }
////        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
////            {
////            for(unsigned int p = 0; p < Records.size(); p++)
////                {
////                Records[p]->ExpandFormIDs(FormIDHandler);
////                }
////            return;
////            }
////        template<class T>
////        T * SetSubRecord(T *newRecord, unsigned int groupType, bool allowMerge, bool asOverride)
////            {
////            unsigned int nRecSize, oRecSize;//, oCellSize, oChildrenSize;
////            T *curRecord = NULL;
////            unsigned int vSize = 0;
////            if(newRecord == NULL)
////                return NULL;
////            //If record exists, merge new record onto old
////            if(asOverride)
////                for(unsigned int p = 0; p < Records.size(); p++)
////                    if(Records[p]->Header.Header.formID == newRecord->Header.Header.formID)
////                        {
////                        if(!allowMerge)
////                            {
////                            delete newRecord;
////                            return NULL;
////                            }
////                        curRecord = Records[p];
////                        oRecSize = curRecord->Header.Header.size;
////                        //curRecord->CopyFrom(newRecord);
////                        nRecSize = curRecord->Header.Header.size;
////                        curRecord->Header.UpdateSize(oRecSize, nRecSize);
////                        delete newRecord;
////                        return curRecord;
////                        }
////            //Otherwise, assign the record formID, create GRUP Header if needed and register the record
////            if(!Header.IsLoaded())
////                {
////                Header.Header.type = eGRUP;
////                Header.Header.size = sizeof(GRUPHEADER);
////                ParentHeader->Header.size += Header.Header.size;
////                //Header.Header.label = *ParentFormID;
////                Header.Header.gType = groupType;
////                Header.Header.stamp = 134671;
////                Header.isLoaded = true;
////                //newRecord->curGRUP = &Header;
////                gEnd = gStart = 0;
////                }
////            //Add new record size to running group size tally
////            newRecord->Header.ParentHeader = &Header;
////            Header.UpdateSize(newRecord->Header.Header.size);
////            Header.UpdateSize(sizeof(RECHEADER));
////            Records.push_back(newRecord);
////            FormIDHandler->RegisterExplicit(&newRecord->Header.Header.formID);
////            return newRecord;
////            }
////        void WriteGRUP(int *fh, unsigned char *buffer, unsigned int &usedBuffer)
////            {
////            if(Records.size() == 0)
////                return;
////
////            _writeBuffer(buffer, &Header.Header, sizeof(GRUPHEADER), usedBuffer);
////            for(unsigned int p = 0; p < Records.size(); p++)
////                Records[p]->Write(fh, buffer, usedBuffer);
////            }
////        #ifdef _DEBUG
////        void Debug(int debugLevel)
////            {
////            if(Header.IsLoaded())
////                switch(eChildType)
////                    {
////                    case eCellPersistent:
////                        printf("    Persistent SubRecords Present: %u\n", Records.size());
////                        break;
////                    case eCellTemporary:
////                        printf("    Temporary SubRecords Present: %u\n", Records.size());
////                        break;
////                    case eCellVWD:
////                    default:
////                        printf("    VWD SubRecords Present: %u\n", Records.size());
////                        break;
////                    }
////            if(debugLevel > 2)
////                for(std::vector<Record *>::iterator curRecord = Records.begin();curRecord!=Records.end();curRecord++)
////                    (*curRecord)->Debug(debugLevel);
////            }
////        #endif
////    };
//
