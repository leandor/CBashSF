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

class GMSTRecord : public Record
    {
    private:
        enum GMSTSubRecords {
            eEDID = 0x44494445,
            eDATA = 0x41544144
            };
        struct GMSTDATA
            {
            union
                {
                float f;
                signed long i;
                };
            char *s;
            char format;
            GMSTDATA(char *sDATA):s(sDATA), format('s') {}
            GMSTDATA(signed long iDATA):s(NULL), format('i'), i(iDATA) {}
            GMSTDATA(float fDATA):s(NULL), format('f'), f(fDATA) {}
            GMSTDATA():format(0), s(NULL), i(0) {}
            ~GMSTDATA()
                {
                delete []s;
                }
            #ifdef _DEBUG
            void Debug(char *name, signed long debugLevel, unsigned long &indentation)
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
                            printf("char *= %s\n", s);
                            break;
                        case 'i':
                            printf("signed long    = %i\n", i);
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
            bool operator ==(const GMSTDATA &other) const
                {
                if(format != other.format)
                    return false;
                switch(format)
                    {
                    case 's':
                        return strcmp(s, other.s) == 0;
                    case 'i':
                        return i == other.i;
                    case 'f':
                        return AlmostEqual(f,other.f,2);
                    default:
                        return false;
                    }
                }
            bool operator !=(const GMSTDATA &other) const
                {
                return !(*this == other);
                }
            };
    public:
        StringRecord EDID;
        GMSTDATA DATA;

        GMSTRecord(bool newRecord=false):Record(newRecord) {}
        GMSTRecord(GMSTRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eGMST)
                return;

            unsigned long vSize;
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
                    vSize = (unsigned long)strlen(srcRecord->DATA.s) + 1;
                    DATA.s = new char [vSize];
                    strcpy_s(DATA.s, vSize, srcRecord->DATA.s);
                    break;
                default:
                    break;
                }
            return;
            }
        ~GMSTRecord() {}
        void Unload() //GMSTs should always be loaded, so do nothing.
            {return;}

        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        void SetField(const unsigned long Field, signed long FieldValue);
        void SetField(const unsigned long Field, float FieldValue);
        void SetField(const unsigned long Field, char *FieldValue);

        signed long DeleteField(const unsigned long Field);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eGMST;}
        char *GetStrType() {return "GMST";}
        bool IsKeyedByEditorID() {return true;}
        signed long WriteRecord(_FileHandler &SaveHandler);
    };
