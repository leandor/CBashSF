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

class FURNRecord : public Record
    {
    private:
        enum FURNRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eSCRI = 0x49524353,
            eMNAM = 0x4D414E4D
            };
    public:
        enum flagsFlags
            {
            fIsAnim01     = 0x00000001,
            fIsAnim02     = 0x00000002,
            fIsAnim03     = 0x00000004,
            fIsAnim04     = 0x00000008,
            fIsAnim05     = 0x00000010,
            fIsAnim06     = 0x00000020,
            fIsAnim07     = 0x00000040,
            fIsAnim08     = 0x00000080,
            fIsAnim09     = 0x00000100,
            fIsAnim10     = 0x00000200,
            fIsAnim11     = 0x00000400,
            fIsAnim12     = 0x00000800,
            fIsAnim13     = 0x00001000,
            fIsAnim14     = 0x00002000,
            fIsAnim15     = 0x00004000,
            fIsAnim16     = 0x00008000,
            fIsAnim17     = 0x00010000,
            fIsAnim18     = 0x00020000,
            fIsAnim19     = 0x00040000,
            fIsAnim20     = 0x00080000,
            fIsAnim21     = 0x00100000,
            fIsAnim22     = 0x00200000,
            fIsAnim23     = 0x00400000,
            fIsAnim24     = 0x00800000,
            fIsAnim25     = 0x01000000,
            fIsAnim26     = 0x02000000,
            fIsAnim27     = 0x04000000,
            fIsAnim28     = 0x08000000,
            fIsAnim29     = 0x10000000,
            fIsAnim30     = 0x20000000,
            fIsSitAnim    = 0x40000000,
            fIsSleepAnim  = 0x80000000
            };
        STRING EDID;
        STRING FULL;
        GENMODEL MODL;
        OptRecordField<GENFID> SCRI;
        ReqRecordField<GENUFLAG> MNAM;

        FURNRecord(bool newRecord=false):Record(newRecord) {}
        FURNRecord(const unsigned int &newFormID):Record(newFormID) {}
        FURNRecord(FURNRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            MODL.MODB = srcRecord->MODL.MODB;
            MODL.MODL = srcRecord->MODL.MODL;
            MODL.MODT = srcRecord->MODL.MODT;
            SCRI = srcRecord->SCRI;
            MNAM = srcRecord->MNAM;
            return;
            }
        ~FURNRecord() {}

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(SCRI.IsLoaded())
                FormIDHandler.ExpandFormID(SCRI->fid);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(SCRI.IsLoaded())
                FormIDHandler.CollapseFormID(SCRI->fid);
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


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eFURN;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
        bool IsAnim01()
            {
            return (MNAM.value.flags & fIsAnim01) != 0;
            }
        void IsAnim01(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim01;
            else
                MNAM.value.flags &= ~fIsAnim01;
            }
        bool IsAnim02()
            {
            return (MNAM.value.flags & fIsAnim02) != 0;
            }
        void IsAnim02(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim02;
            else
                MNAM.value.flags &= ~fIsAnim02;
            }
        bool IsAnim03()
            {
            return (MNAM.value.flags & fIsAnim03) != 0;
            }
        void IsAnim03(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim03;
            else
                MNAM.value.flags &= ~fIsAnim03;
            }
        bool IsAnim04()
            {
            return (MNAM.value.flags & fIsAnim04) != 0;
            }
        void IsAnim04(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim04;
            else
                MNAM.value.flags &= ~fIsAnim04;
            }
        bool IsAnim05()
            {
            return (MNAM.value.flags & fIsAnim05) != 0;
            }
        void IsAnim05(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim05;
            else
                MNAM.value.flags &= ~fIsAnim05;
            }
        bool IsAnim06()
            {
            return (MNAM.value.flags & fIsAnim06) != 0;
            }
        void IsAnim06(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim06;
            else
                MNAM.value.flags &= ~fIsAnim06;
            }
        bool IsAnim07()
            {
            return (MNAM.value.flags & fIsAnim07) != 0;
            }
        void IsAnim07(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim07;
            else
                MNAM.value.flags &= ~fIsAnim07;
            }
        bool IsAnim08()
            {
            return (MNAM.value.flags & fIsAnim08) != 0;
            }
        void IsAnim08(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim08;
            else
                MNAM.value.flags &= ~fIsAnim08;
            }
        bool IsAnim09()
            {
            return (MNAM.value.flags & fIsAnim09) != 0;
            }
        void IsAnim09(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim09;
            else
                MNAM.value.flags &= ~fIsAnim09;
            }
        bool IsAnim10()
            {
            return (MNAM.value.flags & fIsAnim10) != 0;
            }
        void IsAnim10(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim10;
            else
                MNAM.value.flags &= ~fIsAnim10;
            }
        bool IsAnim11()
            {
            return (MNAM.value.flags & fIsAnim11) != 0;
            }
        void IsAnim11(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim11;
            else
                MNAM.value.flags &= ~fIsAnim11;
            }
        bool IsAnim12()
            {
            return (MNAM.value.flags & fIsAnim12) != 0;
            }
        void IsAnim12(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim12;
            else
                MNAM.value.flags &= ~fIsAnim12;
            }
        bool IsAnim13()
            {
            return (MNAM.value.flags & fIsAnim13) != 0;
            }
        void IsAnim13(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim13;
            else
                MNAM.value.flags &= ~fIsAnim13;
            }
        bool IsAnim14()
            {
            return (MNAM.value.flags & fIsAnim14) != 0;
            }
        void IsAnim14(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim14;
            else
                MNAM.value.flags &= ~fIsAnim14;
            }
        bool IsAnim15()
            {
            return (MNAM.value.flags & fIsAnim15) != 0;
            }
        void IsAnim15(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim15;
            else
                MNAM.value.flags &= ~fIsAnim15;
            }
        bool IsAnim16()
            {
            return (MNAM.value.flags & fIsAnim16) != 0;
            }
        void IsAnim16(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim16;
            else
                MNAM.value.flags &= ~fIsAnim16;
            }
        bool IsAnim17()
            {
            return (MNAM.value.flags & fIsAnim17) != 0;
            }
        void IsAnim17(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim17;
            else
                MNAM.value.flags &= ~fIsAnim17;
            }
        bool IsAnim18()
            {
            return (MNAM.value.flags & fIsAnim18) != 0;
            }
        void IsAnim18(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim18;
            else
                MNAM.value.flags &= ~fIsAnim18;
            }
        bool IsAnim19()
            {
            return (MNAM.value.flags & fIsAnim19) != 0;
            }
        void IsAnim19(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim19;
            else
                MNAM.value.flags &= ~fIsAnim19;
            }
        bool IsAnim20()
            {
            return (MNAM.value.flags & fIsAnim20) != 0;
            }
        void IsAnim20(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim20;
            else
                MNAM.value.flags &= ~fIsAnim20;
            }
        bool IsAnim21()
            {
            return (MNAM.value.flags & fIsAnim21) != 0;
            }
        void IsAnim21(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim21;
            else
                MNAM.value.flags &= ~fIsAnim21;
            }
        bool IsAnim22()
            {
            return (MNAM.value.flags & fIsAnim22) != 0;
            }
        void IsAnim22(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim22;
            else
                MNAM.value.flags &= ~fIsAnim22;
            }
        bool IsAnim23()
            {
            return (MNAM.value.flags & fIsAnim23) != 0;
            }
        void IsAnim23(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim23;
            else
                MNAM.value.flags &= ~fIsAnim23;
            }
        bool IsAnim24()
            {
            return (MNAM.value.flags & fIsAnim24) != 0;
            }
        void IsAnim24(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim24;
            else
                MNAM.value.flags &= ~fIsAnim24;
            }
        bool IsAnim25()
            {
            return (MNAM.value.flags & fIsAnim25) != 0;
            }
        void IsAnim25(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim25;
            else
                MNAM.value.flags &= ~fIsAnim25;
            }
        bool IsAnim26()
            {
            return (MNAM.value.flags & fIsAnim26) != 0;
            }
        void IsAnim26(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim26;
            else
                MNAM.value.flags &= ~fIsAnim26;
            }
        bool IsAnim27()
            {
            return (MNAM.value.flags & fIsAnim27) != 0;
            }
        void IsAnim27(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim27;
            else
                MNAM.value.flags &= ~fIsAnim27;
            }
        bool IsAnim28()
            {
            return (MNAM.value.flags & fIsAnim28) != 0;
            }
        void IsAnim28(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim28;
            else
                MNAM.value.flags &= ~fIsAnim28;
            }
        bool IsAnim29()
            {
            return (MNAM.value.flags & fIsAnim29) != 0;
            }
        void IsAnim29(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim29;
            else
                MNAM.value.flags &= ~fIsAnim29;
            }
        bool IsAnim30()
            {
            return (MNAM.value.flags & fIsAnim30) != 0;
            }
        void IsAnim30(bool value)
            {
            if(value)
                MNAM.value.flags |= fIsAnim30;
            else
                MNAM.value.flags &= ~fIsAnim30;
            }
        bool IsSitAnim()
            {
            return (MNAM.value.flags & fIsSitAnim) != 0;
            }
        void IsSitAnim(bool value)
            {
            if(value)
                {
                MNAM.value.flags &= ~fIsSleepAnim;
                MNAM.value.flags |= fIsSitAnim;
                }
            else
                {
                MNAM.value.flags &= ~fIsSitAnim;
                MNAM.value.flags |= fIsSleepAnim;
                }
            }
        bool IsSleepAnim()
            {
            return (MNAM.value.flags & fIsSleepAnim) != 0;
            }
        void IsSleepAnim(bool value)
            {
            if(value)
                {
                MNAM.value.flags &= ~fIsSitAnim;
                MNAM.value.flags |= fIsSleepAnim;
                }
            else
                {
                MNAM.value.flags &= ~fIsSleepAnim;
                MNAM.value.flags |= fIsSitAnim;
                }
            }
        bool IsFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (MNAM.value.flags & Mask) == Mask;
            else
                return (MNAM.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned int Mask)
            {
            MNAM.value.flags = Mask;
            }
    };
