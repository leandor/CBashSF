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
            void Debug(signed long debugLevel, size_t &indentation)
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
        //    void Debug(signed long debugLevel, size_t &indentation)
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
            void Debug(signed long debugLevel, size_t &indentation)
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
            std::vector<unsigned long> points;
            PGRDPGRL() {}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("reference   = %s\n", PrintFormID(points[0]));
                    if(debugLevel > 5)
                        {
                        indentation += 2;
                        for(unsigned long x = 1; x < points.size(); ++x)
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
        ReqSubRecord<PGRDDATA> DATA;
        std::vector<GENPGRP> PGRP;
        RawRecord PGAG;
        RawRecord PGRR;
        std::vector<PGRDPGRI> PGRI;
        std::vector<PGRDPGRL *> PGRL;

        PGRDRecord(bool newRecord=false):Record(newRecord) {IsCompressed(true);}
        PGRDRecord(PGRDRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != ePGRD)
                return;

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
            for(unsigned long x = 0; x < srcRecord->PGRL.size(); x++)
                {
                PGRL[x] = new PGRDPGRL;
                *PGRL[x] = *srcRecord->PGRL[x];
                }
            return;
            }
        ~PGRDRecord()
            {
            for(unsigned long x = 0; x < PGRL.size(); x++)
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
            for(unsigned long x = 0; x < PGRL.size(); x++)
                delete PGRL[x];
            PGRL.clear();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            for(unsigned long x = 0; x < PGRL.size(); x++)
                op.Accept(PGRL[x]->points[0]);

            return op.Stop();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long CreateListElement(const unsigned long subField);
        signed long DeleteListElement(const unsigned long subField);
        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        signed long GetListFieldType(const unsigned long subField, const unsigned long listField);
        unsigned long GetListSize(const unsigned long Field);
        unsigned long GetListArraySize(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        unsigned long GetFieldArraySize(const unsigned long Field);
        void GetFieldArray(const unsigned long Field, void **FieldValues);
        void GetListArray(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, void **FieldValues);
        void * GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void SetField(const unsigned long Field, unsigned short FieldValue);
        void SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, float FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned char *FieldValue, unsigned long nSize);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned short FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue[], unsigned long nSize);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return ePGRD;}
        char *GetStrType() {return "PGRD";}
        unsigned long GetParentType() {return eCELL;}
        signed long WriteRecord(_FileHandler &SaveHandler);
    };
