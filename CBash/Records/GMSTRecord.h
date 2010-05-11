# GPL License and Copyright Notice ============================================
#  This file is part of CBash.
#
#  CBash is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  CBash is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with CBash; if not, write to the Free Software Foundation,
#  Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
#  CBash copyright (C) 2010 Waruddar
#
# =============================================================================
#pragma once
#include "..\Common.h"
#include "..\BaseRecord.h"

class GMSTRecord : public Record
    {
    private:
        enum GMSTRecordFields {
            eEDID = 0x44494445,
            eDATA = 0x41544144
            };
        struct GMSTDATA
            {
            union
                {
                float f;
                int i;
                };
            char *s;
            char format;
            GMSTDATA(char *sDATA):s(sDATA), format('s') {}
            GMSTDATA(int iDATA):s(NULL), format('i'), i(iDATA) {}
            GMSTDATA(float fDATA):s(NULL), format('f'), f(fDATA) {}
            GMSTDATA():format(0), s(NULL), i(0) {}
            ~GMSTDATA()
                {
                delete []s;
                }
            #ifdef _DEBUG
            void Debug(char *name, int debugLevel, unsigned int &indentation)
                {
                if(name)
                    {
                    PrintIndent(indentation);
                    printf("%s:\n", name);
                    }
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    switch(format)
                        {
                        case 's':
                            printf("string = %s\n", s);
                            break;
                        case 'i':
                            printf("int    = %i\n", i);
                            break;
                        case 'f':
                            printf("float  = %f\n", f);
                            break;
                        default:
                            printf("Unknown format: %c\n", format);
                            break;
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        STRING EDID;
        GMSTDATA DATA;
        GMSTRecord(bool newRecord=false):Record(newRecord) {}
        GMSTRecord(const unsigned int &newFormID):Record(newFormID) {}
        GMSTRecord(GMSTRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL)
                return;
            unsigned int vSize;
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            DATA.format = srcRecord->DATA.format;
            switch(DATA.format)
                {
                case 'f':
                    DATA.f = srcRecord->DATA.f;
                    break;
                case 'i':
                    DATA.i = srcRecord->DATA.i;
                    break;
                case 's':
                    vSize = (unsigned int)strlen(srcRecord->DATA.s) + 1;
                    DATA.s = new char [vSize];
                    strcpy_s(DATA.s, vSize, srcRecord->DATA.s);
                    break;
                default:
                    break;
                }
            return;
            }
        GMSTRecord(const unsigned int &newFormID, char *newRecordEDID):Record(true)
            {
            EDID.Copy(newRecordEDID);
            DATA.format = EDID.value[0];
            flags = 0;
            formID = newFormID;
            flagsUnk = 0;
            }
        ~GMSTRecord() {}

        void ExpandFormIDs(_FormIDHandler &FormIDHandler) {}
        void CollapseFormIDs(_FormIDHandler &FormIDHandler) {}

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eGMST;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
    };
