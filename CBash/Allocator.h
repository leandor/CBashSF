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
#include "Common.h"
#include "GenericRecord.h"
#include <vector>
#include <malloc.h>

template<class T, UINT32 RecType, UINT32 AllocUnit>
class RecordPoolAllocator
    {
    private:
        unsigned char *freed_position;
        std::vector<unsigned char *> buffers;

    public:
        RecordPoolAllocator():
            freed_position(NULL)
            {
            //reserve(AllocUnit);
            }

        ~RecordPoolAllocator()
            {
            purge_with_destructors();
            }

        void purge_no_destructors()
            {
            for(UINT32 p = 0;p < buffers.size(); p++)
                free(buffers[p]);
            buffers.clear();
            //_heapmin();
            freed_position = NULL;
            }

        void purge_with_destructors()
            {
            boost::unordered_set<unsigned char *> free_set;
            MakeFreeSet(free_set);
            for(UINT32 p = 0;p < buffers.size(); p++)
                {
                UINT32 buffer_size = _msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                unsigned char *end_of_buffer = buffers[p] + buffer_size;
                for(unsigned char *last_position = buffers[p];last_position < end_of_buffer; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        {
                        //printer("Destroying: %08X\n", ((Record *)last_position)->formID);
                        ((Record *)last_position)->~Record();
                        }
                    }
                free(buffers[p]);
                }
            buffers.clear();
            freed_position = NULL;
            }

        void reserve(UINT32 elements)
            {
            //Allocate memory
            UINT32 buffer_size = sizeof(T) * elements;
            unsigned char *buffer = (unsigned char *)malloc(buffer_size);
            if(buffer == 0)
                throw std::bad_alloc();
            //memset(buffer, 0x00, buffer_size);

            //Populate the free linked list in reverse so that the first freed_position is at the beginning of the buffer
            //unsigned char *end_of_buffer = buffer + buffer_size;
            for(unsigned char *last_position = buffer + buffer_size - sizeof(T);last_position >= buffer; last_position -= sizeof(T))
                {
                *(unsigned char **)last_position = freed_position;
                freed_position = last_position;
                }

            //Save the buffer so it can be deallocated later
            buffers.push_back(buffer);
            }

        Record *construct(unsigned char *recData)
            {
            //See if any memory is free
            if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                Record * curRecord = new (freed_position) T(recData);
                freed_position = next_position;
                return curRecord;
                }
            //Otherwise, allocate more memory
            else
                {
                reserve(AllocUnit);
                return construct(recData);
                }
            throw std::bad_alloc();
            return NULL;
            }

        Record *construct(Record *SourceRecord)
            {
            //See if any memory is free
            if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                Record * curRecord = new (freed_position) T((T *)SourceRecord);
                freed_position = next_position;
                return curRecord;
                }
            //Otherwise, allocate more memory
            else
                {
                reserve(AllocUnit);
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

        UINT32 object_capacity()
            {
            UINT32 size = 0;
            for(UINT32 p = 0;p < buffers.size(); p++)
                {
                UINT32 buffer_size = _msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                size += buffer_size / sizeof(T);
                }

            return size;
            }

        UINT32 free_object_capacity()
            {
            UINT32 size = 0;

            if(freed_position)
                {
                size++;
                for(unsigned char *next_position = *(unsigned char **)freed_position; next_position != NULL; next_position = *(unsigned char **)next_position)
                    {
                    size++;
                    }
                }

            return size;
            }

        UINT32 used_object_capacity()
            {
            return object_capacity() - free_object_capacity();
            }

        UINT32 bytes_capacity()
            {
            return object_capacity() * sizeof(T);
            }

        UINT32 free_bytes_capacity()
            {
            return free_object_capacity() * sizeof(T);
            }

        UINT32 used_bytes_capacity()
            {
            return used_object_capacity() * sizeof(T);
            }

        bool VisitRecords(RecordOp &op)
            {
            boost::unordered_set<unsigned char *> free_set;

            MakeFreeSet(free_set);
            for(UINT32 p = 0;p < buffers.size(); p++)
                {
                UINT32 buffer_size = _msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                unsigned char *end_of_buffer = buffers[p] + buffer_size;
                for(unsigned char *last_position = buffers[p];last_position < end_of_buffer; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        {
                        if(op.Accept((Record *&)last_position))
                            return true;
                        }
                    }
                }
            return false;
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
            Records.reserve(object_capacity() - free_set.size());
            for(UINT32 p = 0;p < buffers.size(); p++)
                {
                UINT32 buffer_size = _msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                unsigned char *end_of_buffer = buffers[p] + buffer_size;
                for(unsigned char *last_position = buffers[p];last_position < end_of_buffer; last_position += sizeof(T))
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
                UINT32 buffer_size = _msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                unsigned char *end_of_buffer = buffers[p] + buffer_size;
                for(unsigned char *last_position = buffers[p];last_position < end_of_buffer; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        ((RECORDIDARRAY)Records)[pos++] = (Record *)last_position;
                    }
                }
            }

        template<class U>
        void Take_Ownership(U &rhs)
            {
            if(this != &rhs)
                {
                //purge_with_destructors();
                if(freed_position != NULL && rhs.freed_position != NULL)
                    {
                    //Add the rhs frees to the end of the current frees
                    unsigned char *next_position = *(unsigned char **)freed_position;
                    while(*(unsigned char **)next_position != NULL)
                        {
                        next_position = *(unsigned char **)next_position;
                        };
                    *(unsigned char **)next_position = rhs.freed_position;
                    }
                else if(rhs.freed_position != NULL)
                    freed_position = rhs.freed_position;

                for(UINT32 x = 0; x < rhs.buffers.size(); ++x)
                    buffers.push_back(rhs.buffers[x]);
                rhs.freed_position = NULL;
                rhs.buffers.clear();
                }
            return;
            }

        void add_buffer(unsigned char *buffer)
            {
            buffers.push_back(buffer);
            return;
            }
    };

//template<class T, UINT32 AllocUnit>
//class PODPoolAllocator
//    {
//    private:
//        unsigned char *freed_position;
//        std::vector<unsigned char *> buffers;
//
//    public:
//        PODPoolAllocator():
//            freed_position(NULL)
//            {
//            //reserve(AllocUnit);
//            }
//
//        ~PODPoolAllocator()
//            {
//            purge_no_destructors();
//            }
//
//        void purge_no_destructors()
//            {
//            for(UINT32 p = 0;p < buffers.size(); p++)
//                free(buffers[p]);
//            buffers.clear();
//            //_heapmin();
//            freed_position = NULL;
//            }
//
//        void reserve(UINT32 elements)
//            {
//            //Allocate memory
//            UINT32 buffer_size = sizeof(T) * elements;
//            unsigned char *buffer = (unsigned char *)malloc(buffer_size);
//            if(buffer == 0)
//                throw std::bad_alloc();
//            //memset(buffer, 0x00, buffer_size);
//
//            //Populate the free linked list in reverse so that the first freed_position is at the beginning of the buffer
//            //unsigned char *end_of_buffer = buffer + buffer_size;
//            for(unsigned char *last_position = buffer + buffer_size - sizeof(T);last_position >= buffer; last_position -= sizeof(T))
//                {
//                *(unsigned char **)last_position = freed_position;
//                freed_position = last_position;
//                }
//
//            //Save the buffer so it can be deallocated later
//            buffers.push_back(buffer);
//            }
//
//        Record *construct()
//            {
//            //See if any memory is free
//            if(freed_position)
//                {
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                Record * curRecord = new (freed_position) T();
//                freed_position = next_position;
//                return curRecord;
//                }
//            //Otherwise, allocate more memory
//            else
//                {
//                reserve(AllocUnit);
//                return construct(recData);
//                }
//            throw std::bad_alloc();
//            return NULL;
//            }
//
//        void deallocate(T *curPOD)
//            {
//            if(curPOD == NULL)
//                return;
//            *(unsigned char **)curPOD = freed_position;
//            freed_position = (unsigned char *)curPOD;
//            }
//
//        UINT32 object_capacity()
//            {
//            UINT32 size = 0;
//            for(UINT32 p = 0;p < buffers.size(); p++)
//                {
//                UINT32 buffer_size = _msize(buffers[p]);
//                //in case malloc returned more than the requested amount
//                buffer_size -= buffer_size % sizeof(T);
//                size += buffer_size / sizeof(T);
//                }
//
//            return size;
//            }
//
//        UINT32 free_object_capacity()
//            {
//            UINT32 size = 0;
//
//            if(freed_position)
//                {
//                size++;
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                while(next_position != NULL)
//                    {
//                    size++;
//                    next_position = *(unsigned char **)next_position;
//                    };
//                }
//
//            return size;
//            }
//
//        UINT32 used_object_capacity()
//            {
//            return object_capacity() - free_object_capacity();
//            }
//
//        UINT32 bytes_capacity()
//            {
//            UINT32 size = 0;
//            for(UINT32 p = 0;p < buffers.size(); p++)
//                {
//                UINT32 buffer_size = _msize(buffers[p]);
//                //in case malloc returned more than the requested amount
//                buffer_size -= buffer_size % sizeof(T);
//                size += buffer_size;
//                }
//
//            return size;
//            }
//
//        UINT32 free_bytes_capacity()
//            {
//            UINT32 size = 0;
//
//            if(freed_position)
//                {
//                size++;
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                while(next_position != NULL)
//                    {
//                    size++;
//                    next_position = *(unsigned char **)next_position;
//                    };
//                }
//
//            return size * sizeof(T);
//            }
//
//        UINT32 used_bytes_capacity()
//            {
//            return bytes_capacity() - free_bytes_capacity();
//            }
//    };

//class StringPoolAllocator
//    {
//    private:
//        static char null_term;
//        PODPoolAllocator<4, 1024>   pool4;
//        PODPoolAllocator<6, 1024>   pool6;
//        PODPoolAllocator<8, 1024>   pool8;
//        PODPoolAllocator<10, 1024>  pool10;
//        PODPoolAllocator<12, 1024>  pool12;
//        PODPoolAllocator<14, 1024>  pool14;
//        PODPoolAllocator<16, 1024>  pool16;
//        PODPoolAllocator<18, 1024>  pool18;
//        PODPoolAllocator<20, 1024>  pool20;
//        PODPoolAllocator<22, 1024>  pool22;
//        PODPoolAllocator<24, 1024>  pool24;
//        PODPoolAllocator<26, 1024>  pool26;
//        PODPoolAllocator<28, 1024>  pool28;
//        PODPoolAllocator<30, 1024>  pool30;
//        PODPoolAllocator<32, 1024>  pool32;
//        PODPoolAllocator<34, 1024>  pool34;
//        PODPoolAllocator<36, 1024>  pool36;
//        PODPoolAllocator<38, 1024>  pool38;
//        PODPoolAllocator<40, 1024>  pool40;
//        PODPoolAllocator<48, 1024>  pool48;
//        PODPoolAllocator<56, 1024>  pool56;
//        PODPoolAllocator<64, 1024>  pool64;
//        PODPoolAllocator<128, 1024>  pool128;
//        PODPoolAllocator<256, 1024>  pool256;
//        unsigned char *freed_position;
//        std::vector<char *> buffers;
//
//    public:
//        StringPoolAllocator():
//            freed_position(NULL),
//            null_term(0x00)
//            {
//            //reserve(AllocUnit);
//            }
//
//        ~StringPoolAllocator()
//            {
//            purge_no_destructors();
//            }
//
//        void purge_no_destructors()
//            {
//            for(UINT32 p = 0;p < buffers.size(); p++)
//                free(buffers[p]);
//            buffers.clear();
//            //_heapmin();
//            freed_position = NULL;
//            }
//
//        void reserve(UINT32 elements)
//            {
//            //Allocate memory
//            UINT32 buffer_size = sizeof(T) * elements;
//            unsigned char *buffer = (unsigned char *)malloc(buffer_size);
//            if(buffer == 0)
//                throw std::bad_alloc();
//            //memset(buffer, 0x00, buffer_size);
//
//            //Populate the free linked list in reverse so that the first freed_position is at the beginning of the buffer
//            //unsigned char *end_of_buffer = buffer + buffer_size;
//            for(unsigned char *last_position = buffer + buffer_size - sizeof(T);last_position >= buffer; last_position -= sizeof(T))
//                {
//                *(unsigned char **)last_position = freed_position;
//                freed_position = last_position;
//                }
//
//            //Save the buffer so it can be deallocated later
//            buffers.push_back(buffer);
//            }
//
//        Record *construct()
//            {
//            //See if any memory is free
//            if(freed_position)
//                {
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                Record * curRecord = new (freed_position) T();
//                freed_position = next_position;
//                return curRecord;
//                }
//            //Otherwise, allocate more memory
//            else
//                {
//                reserve(AllocUnit);
//                return construct(recData);
//                }
//            throw std::bad_alloc();
//            return NULL;
//            }
//
//        void deallocate(T *curPOD)
//            {
//            if(curPOD == NULL)
//                return;
//            *(unsigned char **)curPOD = freed_position;
//            freed_position = (unsigned char *)curPOD;
//            }
//
//        UINT32 object_capacity()
//            {
//            UINT32 size = 0;
//            for(UINT32 p = 0;p < buffers.size(); p++)
//                {
//                UINT32 buffer_size = _msize(buffers[p]);
//                //in case malloc returned more than the requested amount
//                buffer_size -= buffer_size % sizeof(T);
//                size += buffer_size / sizeof(T);
//                }
//
//            return size;
//            }
//
//        UINT32 free_object_capacity()
//            {
//            UINT32 size = 0;
//
//            if(freed_position)
//                {
//                size++;
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                while(next_position != NULL)
//                    {
//                    size++;
//                    next_position = *(unsigned char **)next_position;
//                    };
//                }
//
//            return size;
//            }
//
//        UINT32 used_object_capacity()
//            {
//            return object_capacity() - free_object_capacity();
//            }
//
//        UINT32 bytes_capacity()
//            {
//            UINT32 size = 0;
//            for(UINT32 p = 0;p < buffers.size(); p++)
//                {
//                UINT32 buffer_size = _msize(buffers[p]);
//                //in case malloc returned more than the requested amount
//                buffer_size -= buffer_size % sizeof(T);
//                size += buffer_size;
//                }
//
//            return size;
//            }
//
//        UINT32 free_bytes_capacity()
//            {
//            UINT32 size = 0;
//
//            if(freed_position)
//                {
//                size++;
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                while(next_position != NULL)
//                    {
//                    size++;
//                    next_position = *(unsigned char **)next_position;
//                    };
//                }
//
//            return size * sizeof(T);
//            }
//
//        UINT32 used_bytes_capacity()
//            {
//            return bytes_capacity() - free_bytes_capacity();
//            }
//    };