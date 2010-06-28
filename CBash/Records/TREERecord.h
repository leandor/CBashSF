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
#include <vector>

class TREERecord : public Record
    {
    private:
        enum TREESubRecords {
            eEDID = 0x44494445,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eSNAM = 0x4D414E53,
            eCNAM = 0x4D414E43,
            eBNAM = 0x4D414E42
            };
        struct TREECNAM
            {
            float curvature, minAngle, maxAngle, branchDim, leafDim;
            int shadowRadius;
            float rockSpeed, rustleSpeed;
            TREECNAM():curvature(0.0f), minAngle(0.0f), maxAngle(0.0f),
                branchDim(0.0f), leafDim(0.0f), shadowRadius(0),
                rockSpeed(0.0f), rustleSpeed(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("curvature    = %f\n", curvature);
                    PrintIndent(indentation);
                    printf("minAngle     = %f\n", minAngle);
                    PrintIndent(indentation);
                    printf("maxAngle     = %f\n", maxAngle);
                    PrintIndent(indentation);
                    printf("branchDim    = %f\n", branchDim);
                    PrintIndent(indentation);
                    printf("leafDim      = %f\n", leafDim);
                    PrintIndent(indentation);
                    printf("shadowRadius = %i\n", shadowRadius);
                    PrintIndent(indentation);
                    printf("rockSpeed    = %f\n", rockSpeed);
                    PrintIndent(indentation);
                    printf("rustleSpeed  = %f\n", rustleSpeed);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const TREECNAM &other) const
                {
                return (AlmostEqual(curvature,other.curvature,2) && 
                        AlmostEqual(minAngle,other.minAngle,2) && 
                        AlmostEqual(maxAngle,other.maxAngle,2) && 
                        AlmostEqual(branchDim,other.branchDim,2) && 
                        AlmostEqual(leafDim,other.leafDim,2) && 
                        shadowRadius == other.shadowRadius && 
                        AlmostEqual(rockSpeed,other.rockSpeed,2) && 
                        AlmostEqual(rustleSpeed,other.rustleSpeed,2));
                }
            bool operator !=(const TREECNAM &other) const
                {
                return !(*this == other);
                }
            };
        struct TREEBNAM
            {
            float widthBill, heightBill;
            TREEBNAM():widthBill(0.0f), heightBill(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("widthBill  = %f\n", widthBill);
                    PrintIndent(indentation);
                    printf("heightBill = %f\n", heightBill);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const TREEBNAM &other) const
                {
                return (AlmostEqual(widthBill,other.widthBill,2) && 
                        AlmostEqual(heightBill,other.heightBill,2));
                }
            bool operator !=(const TREEBNAM &other) const
                {
                return !(*this == other);
                }
            };
    public:
        STRING EDID;
        OptSubRecord<GENMODEL> MODL;
        STRING ICON;
        std::vector<unsigned int> SNAM;
        ReqSubRecord<TREECNAM> CNAM;
        ReqSubRecord<TREEBNAM> BNAM;

        TREERecord(bool newRecord=false):Record(newRecord) {}
        TREERecord(const unsigned int &newFormID):Record(newFormID) {}
        TREERecord(TREERecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            if(srcRecord->MODL.IsLoaded())
                {
                MODL.Load();
                MODL->MODB = srcRecord->MODL->MODB;
                MODL->MODL = srcRecord->MODL->MODL;
                MODL->MODT = srcRecord->MODL->MODT;
                }
            ICON = srcRecord->ICON;
            SNAM = srcRecord->SNAM;
            CNAM = srcRecord->CNAM;
            BNAM = srcRecord->BNAM;
            return;
            }
        ~TREERecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            MODL.Unload();
            ICON.Unload();
            SNAM.clear();
            CNAM.Unload();
            BNAM.Unload();
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eTREE;}
        char * GetStrType() {return "TREE";}
        int WriteRecord(_FileHandler &SaveHandler);
    };
