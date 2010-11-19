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

class SLGMRecord : public Record
    {
    private:
        enum SLGMSubRecords {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eSCRI = 0x49524353,
            eDATA = 0x41544144,
            eSOUL = 0x4C554F53,
            eSLCP = 0x50434C53
            };
        struct SLGMSOUL
            {
            unsigned char soul;
            SLGMSOUL():soul(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("soul = %u\n", soul);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const SLGMSOUL &other) const
                {
                return (soul == other.soul);
                }
            bool operator !=(const SLGMSOUL &other) const
                {
                return !(*this == other);
                }
            };
        struct SLGMSLCP
            {
            unsigned char capacity;
            SLGMSLCP():capacity(1) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("capacity = %u\n", capacity);
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const SLGMSLCP &other) const
                {
                return (capacity == other.capacity);
                }
            bool operator !=(const SLGMSLCP &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum eSoulType
            {
            eNone    = 0,
            ePetty   = 1,
            eLesser  = 2,
            eCommon  = 3,
            eGreater = 4,
            eGrand   = 5
            };
        STRING EDID;
        STRING FULL;
        OptSubRecord<GENMODEL> MODL;
        STRING ICON;
        OptSubRecord<GENFID> SCRI;
        ReqSubRecord<GENVALUEWEIGHT> DATA;
        ReqSubRecord<SLGMSOUL> SOUL;
        ReqSubRecord<SLGMSLCP> SLCP;

        SLGMRecord(bool newRecord=false):Record(newRecord) {}
        SLGMRecord(SLGMRecord *srcRecord):Record(true)
            {
            if(srcRecord == NULL || srcRecord->GetType() != eSLGM)
                return;

            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            if(srcRecord->MODL.IsLoaded())
                {
                MODL.Load();
                MODL->MODB = srcRecord->MODL->MODB;
                MODL->MODL = srcRecord->MODL->MODL;
                MODL->MODT = srcRecord->MODL->MODT;
                }
            ICON = srcRecord->ICON;
            SCRI = srcRecord->SCRI;
            DATA = srcRecord->DATA;
            SOUL = srcRecord->SOUL;
            SLCP = srcRecord->SLCP;
            return;
            }
        ~SLGMRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.Unload();
            ICON.Unload();
            SCRI.Unload();
            DATA.Unload();
            SOUL.Unload();
            SLCP.Unload();
            }

        void VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return;

            if(SCRI.IsLoaded())
                op.Accept(SCRI->fid);
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(const unsigned int Field, char *FieldValue);
        void SetField(const unsigned int Field, float FieldValue);
        void SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetOtherField(const unsigned int Field, unsigned int FieldValue);
        void SetField(const unsigned int Field, unsigned char FieldValue);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eSLGM;}
        char * GetStrType() {return "SLGM";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsNoSoul()
            {
            return (SOUL.value.soul == eNone);
            }
        void IsNoSoul(bool value)
            {
            if(value)
                SOUL.value.soul = eNone;
            else if(IsNoSoul())
                SOUL.value.soul = ePetty;
            }
        bool IsPettySoul()
            {
            return (SOUL.value.soul == ePetty);
            }
        void IsPettySoul(bool value)
            {
            if(value)
                SOUL.value.soul = ePetty;
            else if(IsPettySoul())
                SOUL.value.soul = eNone;
            }
        bool IsLesserSoul()
            {
            return (SOUL.value.soul == eLesser);
            }
        void IsLesserSoul(bool value)
            {
            if(value)
                SOUL.value.soul = eLesser;
            else if(IsLesserSoul())
                SOUL.value.soul = eNone;
            }
        bool IsCommonSoul()
            {
            return (SOUL.value.soul == eCommon);
            }
        void IsCommonSoul(bool value)
            {
            if(value)
                SOUL.value.soul = eCommon;
            else if(IsCommonSoul())
                SOUL.value.soul = eNone;
            }
        bool IsGreaterSoul()
            {
            return (SOUL.value.soul == eGreater);
            }
        void IsGreaterSoul(bool value)
            {
            if(value)
                SOUL.value.soul = eGreater;
            else if(IsGreaterSoul())
                SOUL.value.soul = eNone;
            }
        bool IsGrandSoul()
            {
            return (SOUL.value.soul == eGrand);
            }
        void IsGrandSoul(bool value)
            {
            if(value)
                SOUL.value.soul = eGrand;
            else if(IsGrandSoul())
                SOUL.value.soul = eNone;
            }
        bool IsSoul(unsigned char Type)
            {
            return (SOUL.value.soul == Type);
            }
        void SetSoul(unsigned char Type)
            {
            SOUL.value.soul = Type;
            }

        bool IsNoCapacity()
            {
            return (SLCP.value.capacity == eNone);
            }
        void IsNoCapacity(bool value)
            {
            if(value)
                SLCP.value.capacity = eNone;
            else if(IsNoCapacity())
                SLCP.value.capacity = ePetty;
            }
        bool IsPettyCapacity()
            {
            return (SLCP.value.capacity == ePetty);
            }
        void IsPettyCapacity(bool value)
            {
            if(value)
                SLCP.value.capacity = ePetty;
            else if(IsPettyCapacity())
                SLCP.value.capacity = eNone;
            }
        bool IsLesserCapacity()
            {
            return (SLCP.value.capacity == eLesser);
            }
        void IsLesserCapacity(bool value)
            {
            if(value)
                SLCP.value.capacity = eLesser;
            else if(IsLesserCapacity())
                SLCP.value.capacity = eNone;
            }
        bool IsCommonCapacity()
            {
            return (SLCP.value.capacity == eCommon);
            }
        void IsCommonCapacity(bool value)
            {
            if(value)
                SLCP.value.capacity = eCommon;
            else if(IsCommonCapacity())
                SLCP.value.capacity = eNone;
            }
        bool IsGreaterCapacity()
            {
            return (SLCP.value.capacity == eGreater);
            }
        void IsGreaterCapacity(bool value)
            {
            if(value)
                SLCP.value.capacity = eGreater;
            else if(IsGreaterCapacity())
                SLCP.value.capacity = eNone;
            }
        bool IsGrandCapacity()
            {
            return (SLCP.value.capacity == eGrand);
            }
        void IsGrandCapacity(bool value)
            {
            if(value)
                SLCP.value.capacity = eGrand;
            else if(IsGrandCapacity())
                SLCP.value.capacity = eNone;
            }
        bool IsCapacity(unsigned char Type)
            {
            return (SLCP.value.capacity == Type);
            }
        void SetCapacity(unsigned char Type)
            {
            SLCP.value.capacity = Type;
            }

    };
