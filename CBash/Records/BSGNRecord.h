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
        enum BSGNSubRecords {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eICON = 0x4E4F4349,
            eDESC = 0x43534544,
            eSPLO = 0x4F4C5053
            };
    public:
        StringRecord EDID;
        StringRecord FULL;
        StringRecord ICON;
        StringRecord DESC;
        std::vector<unsigned long *> SPLO;

        BSGNRecord(bool newRecord=false):Record(newRecord) {}
        BSGNRecord(BSGNRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eBSGN)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            ICON = srcRecord->ICON;
            DESC = srcRecord->DESC;
            SPLO.clear();
            SPLO.resize(srcRecord->SPLO.size());
            for(unsigned long x = 0; x < srcRecord->SPLO.size(); x++)
                SPLO[x] = new unsigned long(*srcRecord->SPLO[x]);
            return;
            }
        ~BSGNRecord()
            {
            for(unsigned long x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            ICON.Unload();
            DESC.Unload();

            for(unsigned long x = 0; x < SPLO.size(); x++)
                delete SPLO[x];
            SPLO.clear();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            for(unsigned long x = 0; x < SPLO.size(); x++)
                op.Accept(*SPLO[x]);

            return op.Stop();
            }

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        unsigned long GetFieldArraySize(const unsigned long Field);
        void GetFieldArray(const unsigned long Field, void **FieldValues);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetField(const unsigned long Field, unsigned long FieldValue[], unsigned long nSize);

        signed long DeleteField(const unsigned long Field);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eBSGN;}
        char *GetStrType() {return "BSGN";}
        signed long WriteRecord(_FileHandler &SaveHandler);
    };
