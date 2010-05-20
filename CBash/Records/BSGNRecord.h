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

class BSGNRecord : public Record
    {
    private:
        enum BSGNRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eICON = 0x4E4F4349,
            eDESC = 0x43534544,
            eSPLO = 0x4F4C5053
            };
    public:
        STRING EDID;
        STRING FULL;
        STRING ICON;
        STRING DESC;
        std::vector<unsigned int *> SPLO;
        BSGNRecord(bool newRecord=false):Record(newRecord) {}
        BSGNRecord(const unsigned int &newFormID):Record(newFormID) {}
        BSGNRecord(BSGNRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            ICON = srcRecord->ICON;
            DESC = srcRecord->DESC;
            SPLO.clear();
            SPLO.resize(srcRecord->SPLO.size());
            for(unsigned int x = 0; x < srcRecord->SPLO.size(); x++)
                SPLO[x] = new unsigned int(*srcRecord->SPLO[x]);
            return;
            }
        ~BSGNRecord()
            {
            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            ICON.Unload();
            DESC.Unload();

            for(unsigned int x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            SPLO.clear();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < SPLO.size(); x++)
                FormIDHandler.ExpandFormID(SPLO[x]);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < SPLO.size(); x++)
                FormIDHandler.CollapseFormID(SPLO[x]);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue[], unsigned int nSize);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eBSGN;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
    };
