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

class BOOKRecord : public Record
    {
    private:
        enum BOOKRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eDESC = 0x43534544,
            eSCRI = 0x49524353,
            eENAM = 0x4D414E45,
            eANAM = 0x4D414E41,
            eDATA = 0x41544144
            };
        #pragma pack(push)
        #pragma pack(2)
        struct BOOKDATA
            {
            unsigned char flags;
            char teaches;
            unsigned int value;
            float weight;
            BOOKDATA():flags(0), teaches(-1), value(0), weight(10.0f) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags   = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    printf("teaches = %i\n", teaches);
                    PrintIndent(indentation);
                    printf("value   = %u\n", value);
                    PrintIndent(indentation);
                    printf("weight  = %f\n", weight);
                    indentation -= 2;
                    }
                }
            #endif
            };
        #pragma pack(pop)
    public:
        enum flagsFlags
            {
            fIsScroll = 0x00000001,
            fIsFixed  = 0x00000002
            };
        STRING EDID;
        STRING FULL;
        GENMODEL MODL;
        STRING ICON;
        STRING DESC;
        OptRecordField<GENFID> SCRI;
        OptRecordField<GENFID> ENAM;
        OptRecordField<GENANAM> ANAM;
        ReqRecordField<BOOKDATA> DATA;

        BOOKRecord(bool newRecord=false):Record(newRecord) {}
        BOOKRecord(const unsigned int &newFormID):Record(newFormID) {}
        BOOKRecord(BOOKRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            ICON = srcRecord->ICON;
            DESC = srcRecord->DESC;
            SCRI = srcRecord->SCRI;
            ENAM = srcRecord->ENAM;
            ANAM = srcRecord->ANAM;
            DATA = srcRecord->DATA;
            return;
            }
        ~BOOKRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            ICON.Unload();
            DESC.Unload();
            SCRI.Unload();
            ENAM.Unload();
            ANAM.Unload();
            DATA.Unload();
            }

        void GetReferencedFormIDs(std::vector<FormID> &FormIDs)
            {
            if(!IsLoaded())
                return;
            if(SCRI.IsLoaded())
                FormIDs.push_back(&SCRI->fid);
            if(ENAM.IsLoaded())
                FormIDs.push_back(&ENAM->fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eBOOK;}
        char * GetStrType() {return "BOOK";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsScroll()
            {
            return (DATA.value.flags & fIsScroll) != 0;
            }
        void IsScroll(bool value)
            {
            if(value)
                DATA.value.flags |= fIsScroll;
            else
                DATA.value.flags &= ~fIsScroll;
            }
        bool IsFixed()
            {
            return (DATA.value.flags & fIsFixed) != 0;
            }
        void IsFixed(bool value)
            {
            if(value)
                DATA.value.flags |= fIsFixed;
            else
                DATA.value.flags &= ~fIsFixed;
            }
        bool IsCantBeTaken()
            {
            return (DATA.value.flags & fIsFixed) != 0;
            }
        void IsCantBeTaken(bool value)
            {
            if(value)
                DATA.value.flags |= fIsFixed;
            else
                DATA.value.flags &= ~fIsFixed;
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
