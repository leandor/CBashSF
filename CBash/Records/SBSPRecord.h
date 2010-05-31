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

class SBSPRecord : public Record
    {
    private:
        enum SBSPRecordFields {
            eEDID = 0x44494445,

            eDNAM = 0x4D414E44
            };
        struct SBSPDNAM
            {
            float sizeX, sizeY, sizeZ;
            SBSPDNAM():sizeX(0.0f), sizeY(0.0f), sizeZ(0.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("sizeX = %f\n", sizeX);
                    PrintIndent(indentation);
                    printf("sizeY = %f\n", sizeY);
                    PrintIndent(indentation);
                    printf("sizeZ = %f\n", sizeZ);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        STRING EDID;
        ReqRecordField<SBSPDNAM> DNAM;

        SBSPRecord(bool newRecord=false):Record(newRecord) {}
        SBSPRecord(const unsigned int &newFormID):Record(newFormID) {}
        SBSPRecord(SBSPRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            DNAM = srcRecord->DNAM;
            return;
            }
        ~SBSPRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            DNAM.Unload();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler) {}
        void CollapseFormIDs(_FormIDHandler &FormIDHandler) {}

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eSBSP;}
        char * GetStrType() {return "SBSP";}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
    };
