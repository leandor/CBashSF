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

class ENCHRecord : public Record
    {
    private:
        enum ENCHSubRecords {
            eEDID = 0x44494445,
            eOBME = 0x454D424F,
            eFULL = 0x4C4C5546,
            eENIT = 0x54494E45,

            eEFME = 0x454D4645,
            eEFID = 0x44494645,
            eEFIT = 0x54494645,
            eSCIT = 0x54494353,
            eEFII = 0x49494645,
            eEFIX = 0x58494645,
            eEFXX = 0x58584645,

            eDATX = 0x58544144
            };
        struct ENCHENIT
            {
            unsigned int itemType, chargeAmount, enchantCost;
            unsigned char flags, unused1[3];
            ENCHENIT():itemType(0), chargeAmount(0), enchantCost(0), flags(0)
                {
                memset(&unused1, 0x00, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("itemType     = %u\n", itemType);
                    PrintIndent(indentation);
                    printf("chargeAmount = %u\n", chargeAmount);
                    PrintIndent(indentation);
                    printf("enchantCost  = %u\n", enchantCost);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags        = %u\n", flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1      = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            bool operator ==(const ENCHENIT &other) const
                {
                return (itemType == other.itemType &&
                        chargeAmount == other.chargeAmount &&
                        enchantCost == other.enchantCost &&
                        flags == other.flags);
                }
            bool operator !=(const ENCHENIT &other) const
                {
                return !(*this == other);
                }
            };
    public:
        enum flagsFlags
            {
            fIsNoAutoCalc = 0x00000001
            };
        enum eItemType
            {
            eScroll  = 0,
            eStaff   = 1,
            eWeapon  = 2,
            eApparel = 3
            };
        STRING EDID;
        STRING FULL;
        ReqSubRecord<ENCHENIT> ENIT;
        std::vector<GENEffect *> Effects;
        OptSubRecord<OBMEMAGIC> OBME;

        ENCHRecord(bool newRecord=false):Record(newRecord) {}
        ENCHRecord(const unsigned int &newFormID):Record(newFormID) {}
        ENCHRecord(ENCHRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            ENIT = srcRecord->ENIT;
            Effects.clear();
            Effects.resize(srcRecord->Effects.size());
            for(unsigned int x = 0; x < srcRecord->Effects.size(); x++)
                {
                Effects[x] = new GENEffect;
                Effects[x]->EFID = srcRecord->Effects[x]->EFID;
                Effects[x]->EFIT = srcRecord->Effects[x]->EFIT;
                Effects[x]->SCIT = srcRecord->Effects[x]->SCIT;
                Effects[x]->FULL = srcRecord->Effects[x]->FULL;
                if(srcRecord->Effects[x]->OBME.IsLoaded())
                    {
                    Effects[x]->OBME.Load();
                    Effects[x]->OBME->EFME = srcRecord->Effects[x]->OBME->EFME;
                    Effects[x]->OBME->EFII = srcRecord->Effects[x]->OBME->EFII;
                    Effects[x]->OBME->EFIX = srcRecord->Effects[x]->OBME->EFIX;
                    }
                }
            if(srcRecord->OBME.IsLoaded())
                {
                OBME.Load();
                OBME->OBME = srcRecord->OBME->OBME;
                OBME->DATX = srcRecord->OBME->DATX;
                }
            return;
            }
        ~ENCHRecord()
            {
            for(unsigned int x = 0; x < Effects.size(); x++)
                delete Effects[x];
            }
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            ENIT.Unload();
            for(unsigned int x = 0; x < Effects.size(); x++)
                delete Effects[x];
            Effects.clear();
            OBME.Unload();
            }

        void VisitFormIDs(FormIDOp &op)
            {
            if(!IsLoaded())
                return;
            for(unsigned int x = 0; x < Effects.size(); x++)
                {
                if(Effects[x]->OBME.IsLoaded())
                    {
                    if(Effects[x]->EFID.value.name >= 0x80000000)
                        op.AcceptMGEF(Effects[x]->EFID.value.name);
                    if(Effects[x]->EFIT.value.name >= 0x80000000)
                        op.AcceptMGEF(Effects[x]->EFIT.value.name);
                    switch(Effects[x]->OBME->EFME.value.efitParamInfo)
                        {
                        case 1: //It's a regular formID, so nothing fancy.
                            op.Accept(Effects[x]->EFIT.value.actorValue);
                            break;
                        case 2: //It's a mgefCode, and not a formID at all.
                            //Conditional resolution of mgefCode's based on JRoush's OBME mod
                            //It's resolved just like a formID, except it uses the lower byte instead of the upper
                            if(Effects[x]->EFIT.value.actorValue >= 0x80000000)
                                op.AcceptMGEF(Effects[x]->EFIT.value.actorValue);
                            break;
                        case 3: //It's an actor value, and not a formID at all.
                            //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                            //It's resolved just like a formID
                            if(Effects[x]->EFIT.value.actorValue >= 0x800)
                                op.Accept(Effects[x]->EFIT.value.actorValue);
                            break;
                        default: //It's not a formID, mgefCode, or fancied up actor value
                            //so do nothing
                            break;
                        }
                    if(Effects[x]->SCIT.IsLoaded())
                        {
                        if(Effects[x]->SCIT->visual >= 0x80000000)
                            op.AcceptMGEF(Effects[x]->SCIT->visual);
                        switch(Effects[x]->OBME->EFME.value.efixParamInfo)
                            {
                            case 1: //It's a regular formID, so nothing fancy.
                                op.Accept(Effects[x]->SCIT->script);
                                break;
                            case 2: //It's a mgefCode, and not a formID at all.
                                //Conditional resolution of mgefCode's based on JRoush's OBME mod
                                //It's resolved just like a formID, except it uses the lower byte instead of the upper
                                if(Effects[x]->SCIT->script >= 0x80000000)
                                    op.AcceptMGEF(Effects[x]->SCIT->script);
                                break;
                            case 3: //It's an actor value, and not a formID at all.
                                //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                                //It's resolved just like a formID
                                if(Effects[x]->SCIT->script >= 0x800)
                                    op.Accept(Effects[x]->SCIT->script);
                                break;
                            default: //It's not a formID, mgefCode, or fancied up actor value
                                //so do nothing
                                break;
                            }
                        }
                    if(Effects[x]->OBME->EFIX.IsLoaded())
                        if(Effects[x]->OBME->EFIX->resistAV >= 0x800)
                            op.Accept(Effects[x]->OBME->EFIX->resistAV);
                    }
                else
                    {
                    if(Effects[x]->SCIT.IsLoaded())
                        op.Accept(Effects[x]->SCIT->script);
                    }
                }
            }

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int CreateListElement(const unsigned int subField);
        int DeleteListElement(const unsigned int subField);
        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        int GetListFieldType(const unsigned int subField, const unsigned int listField);
        unsigned int GetListSize(const unsigned int Field);
        unsigned int GetListArraySize(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void GetListArray(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, void **FieldValues);
        void * GetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);
        void SetField(const unsigned int Field, char *FieldValue);
        void SetOtherField(const unsigned int Field, unsigned int FieldValue);
        void SetField(const unsigned int Field, unsigned char FieldValue);
        void SetField(const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned int FieldValue);
        void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, float FieldValue);
        void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char FieldValue);
        void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, unsigned char *FieldValue, unsigned int nSize);
        void SetListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField, char *FieldValue);

        int DeleteField(const unsigned int Field);
        int DeleteListField(const unsigned int subField, const unsigned int listIndex, const unsigned int listField);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eENCH;}
        char * GetStrType() {return "ENCH";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsNoAutoCalc()
            {
            return (ENIT.value.flags & fIsNoAutoCalc) != 0;
            }
        void IsNoAutoCalc(bool value)
            {
            if(value)
                ENIT.value.flags |= fIsNoAutoCalc;
            else
                ENIT.value.flags &= ~fIsNoAutoCalc;
            }
        bool IsFlagMask(unsigned char Mask, bool Exact=false)
            {
            if(Exact)
                return (ENIT.value.flags & Mask) == Mask;
            else
                return (ENIT.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned char Mask)
            {
            ENIT.value.flags = Mask;
            }
        bool IsScroll()
            {
            return (ENIT.value.itemType == eScroll);
            }
        void IsScroll(bool value)
            {
            if(value)
                ENIT.value.itemType = eScroll;
            else
                ENIT.value.itemType = eStaff;
            }
        bool IsStaff()
            {
            return (ENIT.value.itemType == eStaff);
            }
        void IsStaff(bool value)
            {
            if(value)
                ENIT.value.itemType = eStaff;
            else
                ENIT.value.itemType = eScroll;
            }
        bool IsWeapon()
            {
            return (ENIT.value.itemType == eWeapon);
            }
        void IsWeapon(bool value)
            {
            if(value)
                ENIT.value.itemType = eWeapon;
            else
                ENIT.value.itemType = eScroll;
            }
        bool IsApparel()
            {
            return (ENIT.value.itemType == eApparel);
            }
        void IsApparel(bool value)
            {
            if(value)
                ENIT.value.itemType = eApparel;
            else
                ENIT.value.itemType = eScroll;
            }
        bool IsType(unsigned int Type)
            {
            return (ENIT.value.itemType == Type);
            }
        void SetType(unsigned int Type)
            {
            ENIT.value.itemType = Type;
            }
    };
