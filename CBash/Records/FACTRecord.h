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

class FACTRecord : public Record
    {
    private:
        enum FACTRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eXNAM = 0x4D414E58,
            eDATA = 0x41544144,
            eCNAM = 0x4D414E43,
            eRNAM = 0x4D414E52,
            eMNAM = 0x4D414E4D,
            eFNAM = 0x4D414E46,
            eINAM = 0x4D414E49
            };
        struct FACTCNAM
            {
            float crimeGoldMultiplier;
            FACTCNAM():crimeGoldMultiplier(1.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("crimeGoldMultiplier = %f\n", crimeGoldMultiplier);
                    indentation -= 2;
                    }
                }
            #endif
            };

        struct FACTRNAM
            {
            int RNAM;
            STRING MNAM, FNAM, INAM;
            FACTRNAM():RNAM(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("RNAM = %i\n", RNAM);
                    MNAM.Debug("MNAM", debugLevel, indentation);
                    FNAM.Debug("FNAM", debugLevel, indentation);
                    INAM.Debug("INAM", debugLevel, indentation);
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum flagsFlags
            {
            fIsHiddenFromPC  = 0x00000001,
            fIsEvil          = 0x00000002,
            fIsSpecialCombat = 0x00000004
            };
        STRING EDID;
        STRING FULL;
        std::vector<ReqRecordField<GENXNAM> *> XNAM;
        ReqRecordField<GENFLAG> DATA;
        RecordField<FACTCNAM> CNAM;
        std::vector<ReqRecordField<FACTRNAM> *> RNAM;

        FACTRecord(bool newRecord=false):Record(newRecord) {}
        FACTRecord(const unsigned int &newFormID):Record(newFormID) {}
        FACTRecord(FACTRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;

            XNAM.clear();
            XNAM.resize(srcRecord->XNAM.size());
            for(unsigned int x = 0; x < srcRecord->XNAM.size(); x++)
                {
                XNAM[x] = new ReqRecordField<GENXNAM>;
                *XNAM[x] = *srcRecord->XNAM[x];
                }

            DATA = srcRecord->DATA;
            CNAM = srcRecord->CNAM;

            RNAM.clear();
            RNAM.resize(srcRecord->RNAM.size());
            for(unsigned int x = 0; x < srcRecord->RNAM.size(); x++)
                {
                RNAM[x] = new ReqRecordField<FACTRNAM>;
                *RNAM[x] = *srcRecord->RNAM[x];
                }
            }
        ~FACTRecord()
            {
            for(unsigned int x = 0; x < XNAM.size(); x++)
                delete XNAM[x];
            for(unsigned int x = 0; x < RNAM.size(); x++)
                delete RNAM[x];
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < XNAM.size(); x++)
                FormIDHandler.ExpandFormID(XNAM[x]->value.faction);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            for(unsigned int x = 0; x < XNAM.size(); x++)
                FormIDHandler.CollapseFormID(XNAM[x]->value.faction);
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
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(_FormIDHandler &FormIDHandler, const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eFACT;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);

        bool IsHiddenFromPC()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fIsHiddenFromPC) != 0;
            }
        void IsHiddenFromPC(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fIsHiddenFromPC;
            else
                DATA.value.flags &= ~fIsHiddenFromPC;
            }
        bool IsEvil()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fIsEvil) != 0;
            }
        void IsEvil(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fIsEvil;
            else
                DATA.value.flags &= ~fIsEvil;
            }
        bool IsSpecialCombat()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fIsSpecialCombat) != 0;
            }
        void IsSpecialCombat(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fIsSpecialCombat;
            else
                DATA.value.flags &= ~fIsSpecialCombat;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(!DATA.IsLoaded()) return false;
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            if(!DATA.IsLoaded()) return;
            DATA.value.flags = Mask;
            }
    };
