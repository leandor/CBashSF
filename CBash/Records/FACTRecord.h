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
        enum FACTSubRecords {
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
            void Debug(signed long debugLevel, size_t &indentation)
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
            bool operator ==(const FACTCNAM &other) const
                {
                return (AlmostEqual(crimeGoldMultiplier,other.crimeGoldMultiplier,2));
                }
            bool operator !=(const FACTCNAM &other) const
                {
                return !(*this == other);
                }
            };

        struct FACTRNAM
            {
            signed long RNAM;
            StringRecord MNAM, FNAM, INAM;
            FACTRNAM():RNAM(0) {}
            #ifdef _DEBUG
            void Debug(signed long debugLevel, size_t &indentation)
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
            bool operator ==(const FACTRNAM &other) const
                {
                return (RNAM == other.RNAM &&
                        MNAM == other.MNAM &&
                        FNAM == other.FNAM &&
                        INAM == other.INAM);
                }
            bool operator !=(const FACTRNAM &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsFlags
            {
            fIsHiddenFromPC  = 0x00000001,
            fIsEvil          = 0x00000002,
            fIsSpecialCombat = 0x00000004
            };
        StringRecord EDID;
        StringRecord FULL;
        std::vector<ReqSubRecord<GENXNAM> *> XNAM;
        ReqSubRecord<GENFLAG> DATA;
        ReqSubRecord<FACTCNAM> CNAM;
        std::vector<ReqSubRecord<FACTRNAM> *> RNAM;

        FACTRecord(bool newRecord=false):Record(newRecord) {}
        FACTRecord(FACTRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eFACT)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;

            XNAM.clear();
            XNAM.resize(srcRecord->XNAM.size());
            for(unsigned long x = 0; x < srcRecord->XNAM.size(); x++)
                {
                XNAM[x] = new ReqSubRecord<GENXNAM>;
                *XNAM[x] = *srcRecord->XNAM[x];
                }

            DATA = srcRecord->DATA;
            CNAM = srcRecord->CNAM;

            RNAM.clear();
            RNAM.resize(srcRecord->RNAM.size());
            for(unsigned long x = 0; x < srcRecord->RNAM.size(); x++)
                {
                RNAM[x] = new ReqSubRecord<FACTRNAM>;
                *RNAM[x] = *srcRecord->RNAM[x];
                }
            }
        ~FACTRecord()
            {
            for(unsigned long x = 0; x < XNAM.size(); x++)
                delete XNAM[x];
            for(unsigned long x = 0; x < RNAM.size(); x++)
                delete RNAM[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();

            for(unsigned long x = 0; x < XNAM.size(); x++)
                delete XNAM[x];
            XNAM.clear();

            DATA.Unload();
            CNAM.Unload();

            for(unsigned long x = 0; x < RNAM.size(); x++)
                delete RNAM[x];
            RNAM.clear();
            }

        bool VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return false;

            for(unsigned long x = 0; x < XNAM.size(); x++)
                op.Accept(XNAM[x]->value.faction);

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
        void SetField(const unsigned long Field, unsigned char FieldValue);
        void SetField(const unsigned long Field, float FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, signed long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, unsigned long FieldValue);
        void SetListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField, char *FieldValue);

        signed long DeleteField(const unsigned long Field);
        signed long DeleteListField(const unsigned long subField, const unsigned long listIndex, const unsigned long listField);

        signed long ParseRecord(unsigned char *buffer, const unsigned long &recSize);
        unsigned long GetSize(bool forceCalc=false);
        unsigned long GetType() {return eFACT;}
        char *GetStrType() {return "FACT";}
        signed long WriteRecord(_FileHandler &SaveHandler);

        bool IsHiddenFromPC()
            {
            return (DATA.value.flags & fIsHiddenFromPC) != 0;
            }
        void IsHiddenFromPC(bool value)
            {
            if(value)
                DATA.value.flags |= fIsHiddenFromPC;
            else
                DATA.value.flags &= ~fIsHiddenFromPC;
            }
        bool IsEvil()
            {
            return (DATA.value.flags & fIsEvil) != 0;
            }
        void IsEvil(bool value)
            {
            if(value)
                DATA.value.flags |= fIsEvil;
            else
                DATA.value.flags &= ~fIsEvil;
            }
        bool IsSpecialCombat()
            {
            return (DATA.value.flags & fIsSpecialCombat) != 0;
            }
        void IsSpecialCombat(bool value)
            {
            if(value)
                DATA.value.flags |= fIsSpecialCombat;
            else
                DATA.value.flags &= ~fIsSpecialCombat;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            DATA.value.flags = Mask;
            }
    };
