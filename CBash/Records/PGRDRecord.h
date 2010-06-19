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
#include "..\Common.h"
#include "..\BaseRecord.h"

class PGRDRecord : public Record
    {
    private:
        enum PGRDSubrecords {
            eDATA = 0x41544144,
            ePGRP = 0x50524750,
            ePGAG = 0x47414750,
            ePGRR = 0x52524750,
            ePGRI = 0x49524750,
            ePGRL = 0x4C524750
            };
        struct PGRDDATA
            {
            unsigned short count;
            PGRDDATA():count(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("count = %u\n", count);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const PGRDDATA &other) const
                {
                return (count == other.count);
                }
            bool operator !=(const PGRDDATA &other) const
                {
                return !(*this == other);
                }
            };

        //struct PGRDPGRR
        //    {
        //    unsigned short start, end;
        //    PGRDPGRR():start(0), end(0) {}
        //    #ifdef _DEBUG
        //    void Debug(int debugLevel, size_t &indentation)
        //        {
        //        if(debugLevel > 3)
        //            {
        //            indentation += 2;
        //            PrintIndent(indentation);
        //            printf("start = %u\n", start);
        //            PrintIndent(indentation);
        //            printf("end   = %u\n", end);
        //            indentation -= 2;
        //            }
        //        }
        //    #endif
        //    };

        struct PGRDPGRI
            {
            unsigned short point;
            unsigned char unused1[2];
            float x, y, z;
            PGRDPGRI():point(0), x(0.0f), y(0.0f), z(0.0f)
                {
                memset(&unused1, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("point   = %u\n", point);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1 = %c%c\n", unused1[0], unused1[1]);
                        }
                    PrintIndent(indentation);
                    printf("x       = %f\n", x);
                    PrintIndent(indentation);
                    printf("y       = %f\n", y);
                    PrintIndent(indentation);
                    printf("z       = %f\n", z);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const PGRDPGRI &other) const
                {
                return (point == other.point && 
                        AlmostEqual(x,other.x,2) && 
                        AlmostEqual(y,other.y,2) && 
                        AlmostEqual(z,other.z,2));
                }
            bool operator !=(const PGRDPGRI &other) const
                {
                return !(*this == other);
                }
            };

        struct PGRDPGRL
            {
            std::vector<unsigned int> points;
            PGRDPGRL() {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("reference   = %s\n", PrintFormID(points[0]));
                    if(debugLevel > 5)
                        {
                        indentation += 2;
                        for(unsigned int x = 1; x < points.size(); ++x)
                            {
                            PrintIndent(indentation);
                            printf("Point %u = %u\n", x - 1, points[x]);
                            }
                        indentation -= 2;
                        }
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const PGRDPGRL &other) const
                {
                return (points == other.points);
                }
            bool operator !=(const PGRDPGRL &other) const
                {
                return !(*this == other);
                }
            };
    public:
        ReqRecordField<PGRDDATA> DATA;
        std::vector<GENPGRP> PGRP;
        RAWBYTES PGAG;
        RAWBYTES PGRR;
        std::vector<PGRDPGRI> PGRI;
        std::vector<PGRDPGRL *> PGRL;

        PGRDRecord(bool newRecord=false):Record(newRecord) {IsCompressed(true);}
        PGRDRecord(const unsigned int &newFormID):Record(newFormID) {IsCompressed(true);}
        PGRDRecord(PGRDRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;

            DATA = srcRecord->DATA;
            PGRP = srcRecord->PGRP;
            PGAG = srcRecord->PGAG;
            PGRR = srcRecord->PGRR;
            PGRI = srcRecord->PGRI;

            PGRL.clear();
            PGRL.resize(srcRecord->PGRL.size());
            for(unsigned int x = 0; x < srcRecord->PGRL.size(); x++)
                {
                PGRL[x] = new PGRDPGRL;
                *PGRL[x] = *srcRecord->PGRL[x];
                }
            return;
            }
        ~PGRDRecord()
            {
            for(unsigned int x = 0; x < PGRL.size(); x++)
                delete PGRL[x];
            }
        void Unload()
            {
            IsLoaded(false);
            DATA.Unload();
            PGRP.clear();
            PGAG.Unload();
            PGRR.Unload();
            PGRI.clear();
            for(unsigned int x = 0; x < PGRL.size(); x++)
                delete PGRL[x];
            PGRL.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            for(unsigned int x = 0; x < PGRL.size(); x++)
                FormIDs.push_back(&PGRL[x]->points[0]);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned short FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue[], unsigned int nSize);

        int DeleteField(const unsigned int Field);
        int DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return ePGRD;}
        char * GetStrType() {return "PGRD";}
        int WriteRecord(_FileHandler &SaveHandler);
    };
