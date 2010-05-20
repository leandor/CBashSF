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
        enum TREERecordFields {
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
            };
    public:
        STRING EDID;
        GENMODEL MODL;
        STRING ICON;
        std::vector<unsigned int> SNAM;
        ReqRecordField<TREECNAM> CNAM;
        ReqRecordField<TREEBNAM> BNAM;

        TREERecord(bool newRecord=false):Record(newRecord) {}
        TREERecord(const unsigned int &newFormID):Record(newFormID) {}
        TREERecord(TREERecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
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
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            ICON.Unload();
            SNAM.clear();
            CNAM.Unload();
            BNAM.Unload();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler) {}
        void CollapseFormIDs(_FormIDHandler &FormIDHandler) {}

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


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eTREE;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
    };
