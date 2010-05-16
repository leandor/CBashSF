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

class AMMORecord : public Record
    {
    private:
        enum AMMORecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eICON = 0x4E4F4349,
            eENAM = 0x4D414E45,
            eANAM = 0x4D414E41,
            eDATA = 0x41544144
            };
        #pragma pack(push)
        #pragma pack(2)
        struct AMMODATA
            {
            float speed;
            unsigned char flags, unused1[3];
            unsigned int value;
            float weight;
            unsigned short damage;
            AMMODATA():speed(0.0f), flags(0), value(0), weight(0.0f), damage(0)
                {
                memset(&unused1, 0xCD, 3);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("speed  = %f\n", speed);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags   = %u\n", flags);
                        }
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1 = %02X%02X%02X\n", unused1[0], unused1[1], unused1[2]);
                        }
                    PrintIndent(indentation);
                    printf("value   = %u\n", value);
                    PrintIndent(indentation);
                    printf("weight  = %f\n", weight);
                    PrintIndent(indentation);
                    printf("damage  = %u\n", damage);
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
        STRING EDID;
        STRING FULL;
        GENMODEL MODL;
        STRING ICON;
        OptRecordField<GENFID> ENAM;
        OptRecordField<GENANAM> ANAM;
        ReqRecordField<AMMODATA> DATA;

        AMMORecord(bool newRecord=false):Record(newRecord) {}
        AMMORecord(const unsigned int &newFormID):Record(newFormID) {}
        AMMORecord(AMMORecord *srcRecord):Record(true)
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
            ENAM = srcRecord->ENAM;
            ANAM = srcRecord->ANAM;
            DATA = srcRecord->DATA;
            return;
            }
        ~AMMORecord() {}

        void ExpandFormIDs(_FormIDHandler &FormIDHandler)
            {
            if(ENAM.IsLoaded())
                FormIDHandler.ExpandFormID(ENAM->fid);
            }

        void CollapseFormIDs(_FormIDHandler &FormIDHandler)
            {
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
        unsigned int GetType() {return eAMMO;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);
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
