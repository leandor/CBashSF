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

class WEAPRecord : public Record
    {
    private:
        enum WEAPRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eSCRI = 0x49524353,
            eENAM = 0x4D414E45,
            eANAM = 0x4D414E41,
            eDATA = 0x41544144
            };
        #pragma pack(push)
        #pragma pack(2)
        struct WEAPDATA
            {
            unsigned int weaponType;
            float speed, reach;
            unsigned int flags, value, health;
            float weight;
            unsigned short damage;
            WEAPDATA():weaponType(0), speed(0.0f), reach(0.0f),
                flags(0), value(0), health(0), weight(0.0f),
                damage(0) {}
            #ifdef _DEBUG
            void Debug(int debugLevel, unsigned int &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("weaponType = %u\n", weaponType);
                    PrintIndent(indentation);
                    printf("speed      = %f\n", speed);
                    PrintIndent(indentation);
                    printf("reach      = %f\n", reach);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags      = %u\n", flags);
                        }
                    PrintIndent(indentation);
                    printf("value      = %u\n", value);
                    PrintIndent(indentation);
                    printf("health     = %u\n", health);
                    PrintIndent(indentation);
                    printf("weight     = %f\n", weight);
                    PrintIndent(indentation);
                    printf("damage     = %u\n", damage);
                    indentation -= 2;
                    }
                }
            #endif
            };
        #pragma pack(pop)
    public:
        enum flagsFlags
            {
            fIsNotNormalWeapon = 0x00000001
            };
        enum eWeaponType
            {
            eBlade1Hand = 0,
            eBlade2Hand = 1,
            eBlunt1Hand = 2,
            eBlunt2Hand = 3,
            eStaff      = 4,
            eBow        = 5
            };
        STRING EDID;
        STRING FULL;
        GENMODEL MODL;
        STRING ICON;
        OptRecordField<GENFID> SCRI;
        OptRecordField<GENFID> ENAM;
        OptRecordField<GENANAM> ANAM;
        ReqRecordField<WEAPDATA> DATA;

        WEAPRecord(bool newRecord=false):Record(newRecord) {}
        WEAPRecord(const unsigned int &newFormID):Record(newFormID) {}
        WEAPRecord(WEAPRecord *srcRecord):Record(true)
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
            SCRI = srcRecord->SCRI;
            ENAM = srcRecord->ENAM;
            ANAM = srcRecord->ANAM;
            DATA = srcRecord->DATA;
            return;
            }
        ~WEAPRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            MODL.MODB.Unload();
            MODL.MODL.Unload();
            MODL.MODT.Unload();
            ICON.Unload();
            SCRI.Unload();
            ENAM.Unload();
            ANAM.Unload();
            DATA.Unload();
            }

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(SCRI.IsLoaded())
                FormIDHandler.ExpandFormID(SCRI->fid);
            if(ENAM.IsLoaded())
                FormIDHandler.ExpandFormID(ENAM->fid);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(SCRI.IsLoaded())
                FormIDHandler.CollapseFormID(SCRI->fid);
            if(ENAM.IsLoaded())
                FormIDHandler.CollapseFormID(ENAM->fid);
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

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eWEAP;}
        int WriteRecord(unsigned char *buffer, unsigned int &usedBuffer);
        bool IsNotNormalWeapon()
            {
            return (DATA.value.flags & fIsNotNormalWeapon) != 0;
            }
        void IsNotNormalWeapon(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNotNormalWeapon;
            else
                DATA.value.flags &= ~fIsNotNormalWeapon;
            }
        bool IsNotNormal()
            {
            return (DATA.value.flags & fIsNotNormalWeapon) != 0;
            }
        void IsNotNormal(bool value)
            {
            if(value)
                DATA.value.flags |= fIsNotNormalWeapon;
            else
                DATA.value.flags &= ~fIsNotNormalWeapon;
            }
        bool IsNormalWeapon()
            {
            return (DATA.value.flags & fIsNotNormalWeapon) == 0;
            }
        void IsNormalWeapon(bool value)
            {
            if(value)
                DATA.value.flags &= ~fIsNotNormalWeapon;
            else
                DATA.value.flags |= fIsNotNormalWeapon;
            }
        bool IsNormal()
            {
            return (DATA.value.flags & fIsNotNormalWeapon) == 0;
            }
        void IsNormal(bool value)
            {
            if(value)
                DATA.value.flags &= ~fIsNotNormalWeapon;
            else
                DATA.value.flags |= fIsNotNormalWeapon;
            }
        bool IsFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned int Mask)
            {
            DATA.value.flags = Mask;
            }
        bool IsBlade1Hand()
            {
            return (DATA.value.weaponType == eBlade1Hand);
            }
        void IsBlade1Hand(bool value)
            {
            if(value)
                DATA.value.weaponType = eBlade1Hand;
            else if(IsBlade1Hand())
                DATA.value.weaponType = eBlade2Hand;
            }
        bool IsBlade2Hand()
            {
            return (DATA.value.weaponType == eBlade2Hand);
            }
        void IsBlade2Hand(bool value)
            {
            if(value)
                DATA.value.weaponType = eBlade2Hand;
            else if(IsBlade2Hand())
                DATA.value.weaponType = eBlade1Hand;
            }
        bool IsBlunt1Hand()
            {
            return (DATA.value.weaponType == eBlunt1Hand);
            }
        void IsBlunt1Hand(bool value)
            {
            if(value)
                DATA.value.weaponType = eBlunt1Hand;
            else if(IsBlunt1Hand())
                DATA.value.weaponType = eBlade1Hand;
            }
        bool IsBlunt2Hand()
            {
            return (DATA.value.weaponType == eBlunt2Hand);
            }
        void IsBlunt2Hand(bool value)
            {
            if(value)
                DATA.value.weaponType = eBlunt2Hand;
            else if(IsBlunt2Hand())
                DATA.value.weaponType = eBlade1Hand;
            }
        bool IsStaff()
            {
            return (DATA.value.weaponType == eStaff);
            }
        void IsStaff(bool value)
            {
            if(value)
                DATA.value.weaponType = eStaff;
            else if(IsStaff())
                DATA.value.weaponType = eBlade1Hand;
            }
        bool IsBow()
            {
            return (DATA.value.weaponType == eBow);
            }
        void IsBow(bool value)
            {
            if(value)
                DATA.value.weaponType = eBow;
            else if(IsBow())
                DATA.value.weaponType = eBlade1Hand;
            }
        bool IsType(unsigned int Type)
            {
            return (DATA.value.weaponType == Type);
            }
        void SetType(unsigned int Type)
            {
            DATA.value.weaponType = Type;
            }
    };
