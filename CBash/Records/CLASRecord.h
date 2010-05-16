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

class CLASRecord : public Record
    {
    private:
        enum CLASRecordFields {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eDESC = 0x43534544,
            eICON = 0x4E4F4349,
            eDATA = 0x41544144
            };
        struct CLASDATA
            {
            int primary[2];
            unsigned int specialization;
            int major[7];
            unsigned int flags, services;
            char trainSkill;
            unsigned char trainLevel;
            char unused1[2];
            CLASDATA():specialization(0), flags(0), services(0),
                trainSkill(0), trainLevel(0)
                {
                primary[0]=0;
                primary[1]=1;
                major[0]=12;
                major[1]=13;
                major[2]=14;
                major[3]=15;
                major[4]=16;
                major[5]=17;
                major[6]=18;
                memset(&unused1, 0x00, 2);
                }
            #ifdef _DEBUG
            void Debug(int debugLevel, size_t &indentation)
                {
                if(debugLevel > 3)
                    {
                    indentation += 2;
                    PrintIndent(indentation);
                    printf("primary1       = %i\n", primary[0]);
                    PrintIndent(indentation);
                    printf("primary2       = %i\n", primary[1]);
                    PrintIndent(indentation);
                    printf("specialization = %u\n", specialization);
                    PrintIndent(indentation);
                    printf("major1         = %i\n", major[0]);
                    PrintIndent(indentation);
                    printf("major2         = %i\n", major[1]);
                    PrintIndent(indentation);
                    printf("major3         = %i\n", major[2]);
                    PrintIndent(indentation);
                    printf("major4         = %i\n", major[3]);
                    PrintIndent(indentation);
                    printf("major5         = %i\n", major[4]);
                    PrintIndent(indentation);
                    printf("major6         = %i\n", major[5]);
                    PrintIndent(indentation);
                    printf("major7         = %i\n", major[6]);
                    if(debugLevel > 4)
                        {
                        PrintIndent(indentation);
                        printf("flags          = %u\n", flags);
                        PrintIndent(indentation);
                        printf("services       = %u\n", services);
                        }
                    PrintIndent(indentation);
                    printf("trainSkill     = %i\n", trainSkill);
                    PrintIndent(indentation);
                    printf("trainLevel     = %i\n", trainLevel);
                    if(debugLevel > 5)
                        {
                        PrintIndent(indentation);
                        printf("unused1        = %02X%02X\n", unused1[0], unused1[1]);
                        }
                    indentation -= 2;
                    }
                }
            #endif
            };
    public:
        enum flagsFlags
            {
            fIsPlayable = 0x00000001,
            fIsGuard    = 0x00000002
            };
        enum servicesFlags
            {
            fWeapons     = 0x00000001,
            fArmor       = 0x00000002,
            fClothing    = 0x00000004,
            fBooks       = 0x00000008,
            fIngredients = 0x00000010,
            fLights      = 0x00000080,
            fApparatus   = 0x00000100,
            fMiscItems   = 0x00000400,
            fSpells      = 0x00000800,
            fMagicItems  = 0x00001000,
            fPotions     = 0x00002000,
            fTraining    = 0x00004000,
            fRecharge    = 0x00010000,
            fRepair      = 0x00020000
            };
        STRING EDID;
        STRING FULL;
        STRING DESC;
        STRING ICON;
        ReqRecordField<CLASDATA> DATA;
        CLASRecord(bool newRecord=false):Record(newRecord) {}
        CLASRecord(const unsigned int &newFormID):Record(newFormID) {}
        CLASRecord(CLASRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            DESC = srcRecord->DESC;
            ICON = srcRecord->ICON;
            DATA = srcRecord->DATA;
            return;
            }
        ~CLASRecord() {}

        void ExpandFormIDs(_FormIDHandler &FormIDHandler) {}
        void CollapseFormIDs(_FormIDHandler &FormIDHandler) {}

        #ifdef _DEBUG
        void Debug(int debugLevel);
        #endif

        int GetOtherFieldType(const unsigned int Field);
        void * GetOtherField(const unsigned int Field);
        unsigned int GetFieldArraySize(const unsigned int Field);
        void GetFieldArray(const unsigned int Field, void **FieldValues);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char *FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, int FieldValue);
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);


        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize();
        unsigned int GetType() {return eCLAS;}
        int WriteRecord(int *fh, unsigned char *buffer, unsigned int &usedBuffer);

        bool IsPlayable()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fIsPlayable) != 0;
            }
        void IsPlayable(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fIsPlayable;
            else
                DATA.value.flags &= ~fIsPlayable;
            }
        bool IsGuard()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.flags & fIsGuard) != 0;
            }
        void IsGuard(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.flags |= fIsGuard;
            else
                DATA.value.flags &= ~fIsGuard;
            }
        bool IsServicesWeapons()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fWeapons) != 0;
            }
        void IsServicesWeapons(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fWeapons;
            else
                DATA.value.services &= ~fWeapons;
            }
        bool IsServicesArmor()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fArmor) != 0;
            }
        void IsServicesArmor(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fArmor;
            else
                DATA.value.services &= ~fArmor;
            }
        bool IsServicesClothing()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fClothing) != 0;
            }
        void IsServicesClothing(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fClothing;
            else
                DATA.value.services &= ~fClothing;
            }
        bool IsServicesBooks()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fBooks) != 0;
            }
        void IsServicesBooks(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fBooks;
            else
                DATA.value.services &= ~fBooks;
            }
        bool IsServicesIngredients()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fIngredients) != 0;
            }
        void IsServicesIngredients(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fIngredients;
            else
                DATA.value.services &= ~fIngredients;
            }
        bool IsServicesLights()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fLights) != 0;
            }
        void IsServicesLights(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fLights;
            else
                DATA.value.services &= ~fLights;
            }
        bool IsServicesApparatus()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fApparatus) != 0;
            }
        void IsServicesApparatus(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fApparatus;
            else
                DATA.value.services &= ~fApparatus;
            }
        bool IsServicesMiscItems()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fMiscItems) != 0;
            }
        void IsServicesMiscItems(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fMiscItems;
            else
                DATA.value.services &= ~fMiscItems;
            }
        bool IsServicesSpells()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fSpells) != 0;
            }
        void IsServicesSpells(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fSpells;
            else
                DATA.value.services &= ~fSpells;
            }
        bool IsServicesMagicItems()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fMagicItems) != 0;
            }
        void IsServicesMagicItems(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fMagicItems;
            else
                DATA.value.services &= ~fMagicItems;
            }
        bool IsServicesPotions()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fPotions) != 0;
            }
        void IsServicesPotions(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fPotions;
            else
                DATA.value.services &= ~fPotions;
            }
        bool IsServicesTraining()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fTraining) != 0;
            }
        void IsServicesTraining(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fTraining;
            else
                DATA.value.services &= ~fTraining;
            }
        bool IsServicesRecharge()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fRecharge) != 0;
            }
        void IsServicesRecharge(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fRecharge;
            else
                DATA.value.services &= ~fRecharge;
            }
        bool IsServicesRepair()
            {
            if(!DATA.IsLoaded()) return false;
            return (DATA.value.services & fRepair) != 0;
            }
        void IsServicesRepair(bool value)
            {
            if(!DATA.IsLoaded()) return;
            if(value)
                DATA.value.services |= fRepair;
            else
                DATA.value.services &= ~fRepair;
            }
        bool IsFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(!DATA.IsLoaded()) return false;
            if(Exact)
                return (DATA.value.flags & Mask) == Mask;
            else
                return (DATA.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned int Mask)
            {
            if(!DATA.IsLoaded()) return;
            DATA.value.flags = Mask;
            }
        bool IsServicesFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(!DATA.IsLoaded()) return false;
            if(Exact)
                return (DATA.value.services & Mask) == Mask;
            else
                return (DATA.value.services & Mask) != 0;
            }
        void SetServicesFlagMask(unsigned int Mask)
            {
            if(!DATA.IsLoaded()) return;
            DATA.value.services = Mask;
            }
    };
