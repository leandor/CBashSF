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
        enum LSCRRecordFields {
            eEDID = 0x44494445,
            eICON = 0x4E4F4349,
            eDESC = 0x43534544,
            eLNAM = 0x4D414E4C
            };
        struct LSCRLNAM
            {
            unsigned int direct, indirect;
            short gridY, gridX;
            LSCRLNAM():direct(0), indirect(0), gridY(0), gridX(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
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
            };
    public:
        STRING EDID;
        STRING ICON;
        STRING DESC;
        std::vector<ReqRecordField<LSCRLNAM> *> LNAM;

        LSCRRecord(bool newRecord=false):Record(newRecord) {}
        LSCRRecord(const unsigned int &newFormID):Record(newFormID) {}
        LSCRRecord(LSCRRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            ICON = srcRecord->ICON;
            DESC = srcRecord->DESC;
            LNAM.clear();
            LNAM.resize(srcRecord->LNAM.size());
            for(unsigned int x = 0; x < srcRecord->LNAM.size(); x++)
                {
                LNAM[x] = new ReqRecordField<LSCRLNAM>;
                *LNAM[x] = *srcRecord->LNAM[x];
                }
            return;
            }
        ~LSCRRecord()
            {
            for(unsigned int x = 0; x < LNAM.size(); x++)
                delete LNAM[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            ICON.Unload();
            DESC.Unload();
            for(unsigned int x = 0; x < LNAM.size(); x++)
                delete LNAM[x];
            LNAM.clear();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            for(unsigned int x = 0; x < LNAM.size(); x++)
                {
                FormIDs.push_back(&LNAM[x]->value.direct);
                FormIDs.push_back(&LNAM[x]->value.indirect);
                }
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
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, short FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eLSCR;}
        char * GetStrType() {return "LSCR";}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
    };
