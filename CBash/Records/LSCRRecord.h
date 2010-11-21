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

class LSCRRecord : public Record
    {
    private:
        enum LSCRSubRecords {
            eEDID = 0x44494445,
            eICON = 0x4E4F4349,
            eDESC = 0x43534544,
            eLNAM = 0x4D414E4C
            };
        struct LSCRLNAM
            {
            unsigned long direct, indirect;
            short gridY, gridX;
            LSCRLNAM():direct(0), indirect(0), gridY(0), gridX(0) {}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("direct   = %s\n", PrintFormID(direct));
                    PrintIndent(indentation);
                    printf("indirect = %s\n", PrintFormID(indirect));
                    PrintIndent(indentation);
                    printf("gridY    = %i\n", gridY);
                    PrintIndent(indentation);
                    printf("gridX    = %i\n", gridX);
                    indentation -= 2;
                    }
                else
                    {
                    PrintIndent(indentation);
                    printf("LNAM\n");
                    }
                }
            #endif
            bool operator ==(const LSCRLNAM &other) const
                {
                return (direct == other.direct &&
                        indirect == other.indirect &&
                        gridY == other.gridY &&
                        gridX == other.gridX);
                }
            bool operator !=(const LSCRLNAM &other) const
                {
                return !(*this == other);
                }
            };
    public:
        StringRecord EDID;
        StringRecord ICON;
        StringRecord DESC;
        std::vector<ReqSubRecord<LSCRLNAM> *> LNAM;

        LSCRRecord(bool newRecord=false):Record(newRecord) {}
        LSCRRecord(LSCRRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eLSCR)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            ICON = srcRecord->ICON;
            DESC = srcRecord->DESC;
            LNAM.clear();
            LNAM.resize(srcRecord->LNAM.size());
            for(unsigned long x = 0; x < srcRecord->LNAM.size(); x++)
                {
                LNAM[x] = new ReqSubRecord<LSCRLNAM>;
                *LNAM[x] = *srcRecord->LNAM[x];
                }
            return;
            }
        ~LSCRRecord()
            {
            for(unsigned long x = 0; x < LNAM.size(); x++)
                delete LNAM[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            ICON.Unload();
            DESC.Unload();
            for(unsigned long x = 0; x < LNAM.size(); x++)
                delete LNAM[x];
            LNAM.clear();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            for(unsigned long x = 0; x < LNAM.size(); x++)
                {
                op.Accept(LNAM[x]->value.direct);
                op.Accept(LNAM[x]->value.indirect);
                }

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
        void * GetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);
        void SetField(const unsigned long Field, char *FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, short FieldValue);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eLSCR;}
        char *GetStrType() {return "LSCR";}
        signed long WriteRecord(_FileHandler &SaveHandler);
    };
