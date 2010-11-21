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

class TES4Record : public Record
    {
    private:
        enum TES4SubRecords {
            eHEDR = 0x52444548,
            eCNAM = 0x4D414E43,
            eSNAM = 0x4D414E53,
            eMAST = 0x5453414D,
            eDATA = 0x41544144,
            eOFST = 0x5453464F,
            eDELE = 0x454C4544
            };
        struct TES4HEDR
            {
            float version;
            unsigned long numRecords, nextObject;
            TES4HEDR(float nVersion, unsigned long nNumRecords, unsigned long nNextObject):
                version(nVersion),numRecords(nNumRecords),nextObject(nNextObject) {}
            TES4HEDR():version(0.8f),numRecords(0),nextObject(END_HARDCODED_IDS) {}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, unsigned long &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("version    = %f\n", version);
                    PrintIndent(indentation);
                    printf("numRecords = %u\n", numRecords);
                    PrintIndent(indentation);
                    printf("nextObject = %s\n", PrintFormID(nextObject));
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const TES4HEDR &other) const
                {
                return (AlmostEqual(version,other.version,2) &&
                        numRecords == other.numRecords &&
                        nextObject == other.nextObject);
                }
            bool operator !=(const TES4HEDR &other) const
                {
                return !(*this == other);
                }
            };
        struct TES4DATA //Placeholder for writing. Otherwise not used.
            {
            unsigned long unk1, unk2;
            TES4DATA():unk1(0), unk2(0) {}
            };
    public:
        ReqSubRecord<TES4HEDR> HEDR;
        RawRecord OFST;
        RawRecord DELE;
        StringRecord CNAM;
        StringRecord SNAM;
        std::vector<StringRecord> MAST;

        TES4Record(bool newFile=false):Record(newFile) {}
        TES4Record(TES4Record *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eTES4)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            //EDID = srcRecord->EDID;
            HEDR = srcRecord->HEDR;
            OFST = srcRecord->OFST;
            DELE = srcRecord->DELE;
            CNAM = srcRecord->CNAM;
            SNAM = srcRecord->SNAM;
            MAST = srcRecord->MAST;
            return;
            }
        ~TES4Record() {}
        void Unload() //TES4 should never be unloaded, so do nothing
            {return;}

        signed long GetOtherFieldType(const unsigned long Field);
        void * GetOtherField(const unsigned long Field);
        void SetField(const unsigned long Field, char **FieldValue, unsigned long nSize);
        void SetField(const unsigned long Field, unsigned char *FieldValue, unsigned long nSize);
        void SetField(const unsigned long Field, float FieldValue);
        void SetOtherField(const unsigned long Field, unsigned long FieldValue);
        void SetField(const unsigned long Field, char *FieldValue);
        unsigned long GetFieldArraySize(const unsigned long Field);
        void GetFieldArray(const unsigned long Field, void **FieldValues);

        signed long DeleteField(const unsigned long Field);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eTES4;}
        char *GetStrType() {return "TES4";}
        signed long WriteRecord(_FileHandler &SaveHandler);
        #ifdef _DEBUG
        void Debug(signed long debugLevel);
        #endif

        bool IsESM()
            {
            if(!IsLoaded()) return false;
            return (flags & fIsESM) != 0;
            }
        void IsESM(bool value)
            {
            if(!IsLoaded()) return;
            if(value)
                flags |= fIsESM;
            else
                flags &= ~fIsESM;
            }
    };
