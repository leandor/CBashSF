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
#include "Common.h"
#include "GenericRecord.h"
#include <vector>

struct MemoryBuffer
    {
    unsigned char *buffer_start, *buffer_position, *buffer_end;

    MemoryBuffer():
      buffer_start(NULL),
      buffer_position(NULL),
      buffer_end(NULL)
      {
      //
      }

    ~MemoryBuffer()
        {
        //
        }
    };

template<class T, UINT32 RecType, UINT32 InitAlloc>
class RecordPoolAllocator
    {
    private:
        unsigned char *freed_position;
        std::vector<MemoryBuffer> buffers;
        UINT32 curBuffer;

    public:
        RecordPoolAllocator():
            freed_position(NULL),
            curBuffer(0)
            {
            reserve(InitAlloc);
            }

        ~RecordPoolAllocator()
            {
            purge_with_destructors(false);
            }

        void purge_no_destructors(bool reserve_one=true)
            {
            for(UINT32 p = 0;p < buffers.size(); p++)
                delete []buffers[p].buffer_start;
            buffers.clear();
            freed_position = NULL;
            if(reserve_one)
                reserve(1);
            }

        void purge_with_destructors(bool reserve_one=true)
            {
            boost::unordered_set<unsigned char *> free_set;
            MakeFreeSet(free_set);
            for(UINT32 p = 0;p < buffers.size(); p++)
                {
            //if(RecType == REV32(REFR)) QDPRINT;
                for(unsigned char *last_position = buffers[p].buffer_start;last_position < buffers[p].buffer_position; last_position += sizeof(T))
                    {
            //if(RecType == REV32(REFR)) QDPRINT;
                    if(free_set.find(last_position) == free_set.end())
                        ((Record *)last_position)->~Record();
            //if(RecType == REV32(REFR)) QDPRINT;
                    }
            //if(RecType == REV32(REFR)) QDPRINT;
                }
            //if(RecType == REV32(REFR)) QDPRINT;
            for(UINT32 p = 0;p < buffers.size(); p++)
                delete []buffers[p].buffer_start;
            buffers.clear();
            freed_position = NULL;
            if(reserve_one)
                reserve(1);
            }

        UINT32 GetSize()
            {
            UINT32 size = 0;
            for(UINT32 p = 0;p < buffers.size(); p++)
                size += (UINT32)(buffers[p].buffer_position - buffers[p].buffer_start) / sizeof(T);

            if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                size--;
                while(next_position != NULL)
                    {
                    size--;
                    next_position = *(unsigned char **)next_position;
                    };
                }

            return size;
            }

        bool VisitRecords(const UINT32 &RecordType, RecordOp &op, bool DeepVisit)
            {
            bool stop = false;
            Record * curRecord = NULL;
            boost::unordered_set<unsigned char *> free_set;

            MakeFreeSet(free_set);
            for(UINT32 p = 0;p < buffers.size(); p++)
                for(unsigned char *last_position = buffers[p].buffer_start;last_position < buffers[p].buffer_position; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        {
                        curRecord = (Record *)last_position;
                        if(RecordType == NULL || RecordType == RecType)
                            {
                            stop = op.Accept(curRecord);
                            if(curRecord == NULL)
                                {
                                destroy(curRecord);
                                if(stop)
                                    return stop;
                                continue;
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
                    }
            return stop;
            }

        void MakeFreeSet(boost::unordered_set<unsigned char *> &free_set)
            {
            if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                free_set.insert(freed_position);
                while(next_position != NULL)
                    {
                    free_set.insert(next_position);
                    next_position = *(unsigned char **)next_position;
                    };
                }
            }

        void MakeFreeVector(std::vector<unsigned char *> &free_vector)
            {
            if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                free_vector.push_back(freed_position);
                while(next_position != NULL)
                    {
                    free_vector.push_back(next_position);
                    next_position = *(unsigned char **)next_position;
                    };
                std::sort(free_vector.begin(), free_vector.end());
                }
            }

        void MakeRecordsVector(std::vector<Record *> &Records)
            {
            boost::unordered_set<unsigned char *> free_set;
            MakeFreeSet(free_set);
            for(UINT32 p = 0;p < buffers.size(); p++)
                {
                Records.reserve(Records.size() + (((buffers[p].buffer_position - buffers[p].buffer_start) / sizeof(T)) - ((UINT32)free_set.size() * sizeof(T))));
                for(unsigned char *last_position = buffers[p].buffer_start;last_position < buffers[p].buffer_position; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        Records.push_back((Record *)last_position);
                    }
                }
            }

        void MakeRecordsArray(RECORDIDARRAY Records)
            {
            boost::unordered_set<unsigned char *> free_set;
            MakeFreeSet(free_set);
            UINT32 pos = 0;
            for(UINT32 p = 0;p < buffers.size(); p++)
                {
                //Records.reserve(Records.size() + (((buffers[p].buffer_position - buffers[p].buffer_start) / sizeof(T)) - ((UINT32)free_set.size() * sizeof(T))));
                for(unsigned char *last_position = buffers[p].buffer_start;last_position < buffers[p].buffer_position; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        ((RECORDIDARRAY)Records)[pos++] = (Record *)last_position;
                    }
                }
            }

        void reserve(UINT32 elements)
            {
            buffers.push_back(MemoryBuffer());
            buffers.back().buffer_position = buffers.back().buffer_start = new unsigned char[(sizeof(T) * elements)];
            buffers.back().buffer_end = buffers.back().buffer_start + sizeof(T) * elements;
            //memset(buffers.back().buffer_start, 0x00, sizeof(T) * elements);
            }

        void consolidate()
            {
            //consolidates all memory pools into one large pool, removing any freed positions and unused memory
            //invalidates any python records, so it can only be safely done after loading and
            //before control is returned to python
            //this improves locality of records, so iterating through them should be faster
            //consolidate never leaves the pool completely empty (tries to leave InitAlloc amount available)

            if(buffers.size() == 1 && buffers[0].buffer_end == buffers[0].buffer_position && freed_position == NULL)
                return;
            if(buffers.size() == 1 && buffers[0].buffer_start == buffers[0].buffer_position && freed_position == NULL)
                {
                //no memory was ever allocated
                //reset the pool to a minimal amount
                purge_no_destructors(false);
                reserve(1);
                return;
                }
            if(buffers.size() == 0)
                {
                //Should never hit size == 0
                //reset the pool to a minimal amount
                freed_position = NULL;
                reserve(1);
                return;
                }

            SINT32 size = 0;
            for(UINT32 p = 0;p < buffers.size(); p++)
                size += (UINT32)(buffers[p].buffer_position - buffers[p].buffer_start);
            if(size == 0)
                {
                //no memory was ever allocated
                //reset the pool to a minimal amount
                purge_no_destructors(false);
                reserve(1);
                return;
                }

            std::vector<unsigned char *> free_vector;
            MakeFreeVector(free_vector);
            size -= sizeof(T) * (UINT32)free_vector.size();
            if(size <= 0)
                {
                //memory was allocated, but later all freed
                //reset the pool to a minimal amount
                purge_no_destructors(false);
                reserve(1);
                return;
                }
            unsigned char *buffer_start, *buffer_position, *buffer_end, *last_position;
            buffer_position = buffer_start = new unsigned char[size];
            buffer_end = buffer_start + size;
            for(UINT32 p = 0;p < buffers.size(); p++)
                {
                last_position = buffers[p].buffer_start;
                for(UINT32 x = 0;x < free_vector.size(); x++)
                    {
                    //Gotta copy it piecemeal to skip the freed positions
                    if(last_position <= free_vector[x] && free_vector[x] < buffers[p].buffer_end)
                        {
                        memcpy(buffer_position, last_position, free_vector[x] - last_position);
                        buffer_position += free_vector[x] - last_position;
                        last_position = free_vector[x] + sizeof(T); //skip the freed section
                        free_vector.erase(free_vector.begin() + x--);
                        }
                    }
                if(last_position < buffers[p].buffer_position)
                    {
                    memcpy(buffer_position, last_position, buffers[p].buffer_position - last_position);
                    buffer_position += buffers[p].buffer_position - last_position;
                    }
                }
            for(UINT32 p = 0;p < buffers.size(); p++)
                delete []buffers[p].buffer_start;
            buffers.clear();
            freed_position = NULL;
            buffers.push_back(MemoryBuffer());
            curBuffer = 0;
            buffers[curBuffer].buffer_start = buffer_start;
            buffers[curBuffer].buffer_position = buffer_position;
            buffers[curBuffer].buffer_end = buffer_end;
            }

        Record *construct(unsigned char *recData)
            {
            //Check the current pool first, and use up all preallocated memory
            if(buffers[curBuffer].buffer_position < buffers[curBuffer].buffer_end)
                {
                Record * curRecord = new (buffers[curBuffer].buffer_position) T(recData);
                buffers[curBuffer].buffer_position += sizeof(T);
                return curRecord;
                }
            //If all preallocated memory has been used, see if any memory was freed and can be reused
            else if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                Record * curRecord = new (freed_position) T(recData);
                freed_position = next_position;
                return curRecord;
                }
            //All else fails, allocate more memory
            else
                {
                ++curBuffer;
                if(curBuffer >= (UINT32)buffers.size())
                    {
                    //No buffers were reserved, so add a new one
                    curBuffer = (UINT32)buffers.size();
                    reserve(InitAlloc);
                    }
                return construct(recData);
                }
            throw std::bad_alloc();
            return NULL;
            }

        Record *construct(Record *SourceRecord)
            {
            //Check the current pool first, and use up all preallocated memory
            if(buffers[curBuffer].buffer_position < buffers[curBuffer].buffer_end)
                {
                Record * curRecord = new (buffers[curBuffer].buffer_position) T((T *)SourceRecord);
                buffers[curBuffer].buffer_position += sizeof(T);
                return curRecord;
                }
            //If all preallocated memory has been used, see if any memory was freed and can be reused
            else if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                Record * curRecord = new (freed_position) T((T *)SourceRecord);
                freed_position = next_position;
                return curRecord;
                }
            //All else fails, allocate more memory
            else
                {
                ++curBuffer;
                if(curBuffer >= (UINT32)buffers.size())
                    {
                    //No buffers were reserved, so add a new one
                    curBuffer = (UINT32)buffers.size();
                    reserve(InitAlloc);
                    }
                return construct(SourceRecord);
                }
            throw std::bad_alloc();
            return NULL;
            }

        void destroy(Record *curRecord)
            {
            if(curRecord == NULL)
                return;
            curRecord->~Record();
            *(unsigned char **)curRecord = freed_position;
            freed_position = (unsigned char *)curRecord;
            }
        void deallocate(Record *curRecord)
            {
            if(curRecord == NULL)
                return;
            *(unsigned char **)curRecord = freed_position;
            freed_position = (unsigned char *)curRecord;
            }
        UINT32 free_capacity()
            {
            UINT32 size = 0;
            for(UINT32 p = 0;p < buffers.size(); p++)
                size += (buffers[p].buffer_end - buffers[p].buffer_position) / sizeof(T);

            if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                size++;
                while(next_position != NULL)
                    {
                    size++;
                    next_position = *(unsigned char **)next_position;
                    };
                }

            return size;
            }
    };