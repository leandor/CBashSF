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

class CLOTRecord : public Record
    {
    private:
        enum CLOTSubRecords {
            eEDID = 0x44494445,
            eFULL = 0x4C4C5546,
            eSCRI = 0x49524353,
            eENAM = 0x4D414E45,
            eANAM = 0x4D414E41,
            eBMDT = 0x54444D42,

            eMODL = 0x4C444F4D,
            eMODB = 0x42444F4D,
            eMODT = 0x54444F4D,

            eMOD2 = 0x32444F4D,
            eMO2B = 0x42324F4D,
            eMO2T = 0x54324F4D,

            eMOD3 = 0x33444F4D,
            eMO3B = 0x42334F4D,
            eMO3T = 0x54334F4D,

            eMOD4 = 0x34444F4D,
            eMO4B = 0x42344F4D,
            eMO4T = 0x54344F4D,

            eICON = 0x4E4F4349,
            eICO2 = 0x324F4349,

            eDATA = 0x41544144
            };
    public:
        enum flagsFlags
            {
            fIsHead        = 0x00000001,
            fIsHair        = 0x00000002,
            fIsUpperBody   = 0x00000004,
            fIsLowerBody   = 0x00000008,
            fIsHand        = 0x00000010,
            fIsFoot        = 0x00000020,
            fIsRightRing   = 0x00000040,
            fIsLeftRing    = 0x00000080,
            fIsAmulet      = 0x00000100,
            fIsWeapon      = 0x00000200,
            fIsBackWeapon  = 0x00000400,
            fIsSideWeapon  = 0x00000800,
            fIsQuiver      = 0x00001000,
            fIsShield      = 0x00002000,
            fIsTorch       = 0x00004000,
            fIsTail        = 0x00008000,
            fIsHideRings   = 0x00010000,
            fIsHideAmulets = 0x00020000,
            fIsNonPlayable = 0x00400000
            };
        STRING EDID;
        STRING FULL;
        OptSubRecord<GENFID> SCRI;
        OptSubRecord<GENFID> ENAM;
        OptSubRecord<GENANAM> ANAM;
        ReqSubRecord<GENUFLAG> BMDT;
        OptSubRecord<GENMODEL> MODL;
        OptSubRecord<GENMODEL> MOD2;
        STRING ICON;
        OptSubRecord<GENMODEL> MOD3;
        OptSubRecord<GENMODEL> MOD4;
        STRING ICO2;
        ReqSubRecord<GENVALUEWEIGHT> DATA;
        CLOTRecord(bool newRecord=false):Record(newRecord) {}
        CLOTRecord(const unsigned int &newFormID):Record(newFormID) {}
        CLOTRecord(CLOTRecord *srcRecord):Record(true)
            {
            flags = srcRecord->flags;
            formID = srcRecord->formID;
            flagsUnk = srcRecord->flagsUnk;
            EDID = srcRecord->EDID;
            FULL = srcRecord->FULL;
            SCRI = srcRecord->SCRI;
            ENAM = srcRecord->ENAM;
            ANAM = srcRecord->ANAM;
            BMDT = srcRecord->BMDT;
            if(srcRecord->MODL.IsLoaded())
                {
                MODL.Load();
                MODL->MODB = srcRecord->MODL->MODB;
                MODL->MODL = srcRecord->MODL->MODL;
                MODL->MODT = srcRecord->MODL->MODT;
                }
            if(srcRecord->MOD2.IsLoaded())
                {
                MOD2.Load();
                MOD2->MODB = srcRecord->MOD2->MODB;
                MOD2->MODL = srcRecord->MOD2->MODL;
                MOD2->MODT = srcRecord->MOD2->MODT;
                }
            ICON = srcRecord->ICON;
            if(srcRecord->MOD3.IsLoaded())
                {
                MOD3.Load();
                MOD3->MODB = srcRecord->MOD3->MODB;
                MOD3->MODL = srcRecord->MOD3->MODL;
                MOD3->MODT = srcRecord->MOD3->MODT;
                }
            if(srcRecord->MOD4.IsLoaded())
                {
                MOD4.Load();
                MOD4->MODB = srcRecord->MOD4->MODB;
                MOD4->MODL = srcRecord->MOD4->MODL;
                MOD4->MODT = srcRecord->MOD4->MODT;
                }
            ICO2 = srcRecord->ICO2;
            DATA = srcRecord->DATA;
            return;
            }
        ~CLOTRecord() {}
        void Unload()
            {
            IsLoaded(false);
            EDID.Unload();
            FULL.Unload();
            SCRI.Unload();
            ENAM.Unload();
            ANAM.Unload();
            BMDT.Unload();
            MODL.Unload();
            MOD2.Unload();
            ICON.Unload();
            MOD3.Unload();
            MOD4.Unload();
            ICO2.Unload();
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
        void SetOtherField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned int FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned short FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, float FieldValue);
        void SetField(_FormIDHandler &FormIDHandler, const unsigned int Field, unsigned char *FieldValue, unsigned int nSize);

        int DeleteField(const unsigned int Field);

        int ParseRecord(unsigned char *buffer, const unsigned int &recSize);
        unsigned int GetSize(bool forceCalc=false);
        unsigned int GetType() {return eCLOT;}
        char * GetStrType() {return "CLOT";}
        int WriteRecord(_FileHandler &SaveHandler);
        bool IsHead()
            {
            return (BMDT.value.flags & fIsHead) != 0;
            }
        void IsHead(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsHead;
            else
                BMDT.value.flags &= ~fIsHead;
            }
        bool IsHair()
            {
            return (BMDT.value.flags & fIsHair) != 0;
            }
        void IsHair(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsHair;
            else
                BMDT.value.flags &= ~fIsHair;
            }
        bool IsUpperBody()
            {
            return (BMDT.value.flags & fIsUpperBody) != 0;
            }
        void IsUpperBody(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsUpperBody;
            else
                BMDT.value.flags &= ~fIsUpperBody;
            }
        bool IsLowerBody()
            {
            return (BMDT.value.flags & fIsLowerBody) != 0;
            }
        void IsLowerBody(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsLowerBody;
            else
                BMDT.value.flags &= ~fIsLowerBody;
            }
        bool IsHand()
            {
            return (BMDT.value.flags & fIsHand) != 0;
            }
        void IsHand(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsHand;
            else
                BMDT.value.flags &= ~fIsHand;
            }
        bool IsFoot()
            {
            return (BMDT.value.flags & fIsFoot) != 0;
            }
        void IsFoot(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsFoot;
            else
                BMDT.value.flags &= ~fIsFoot;
            }
        bool IsRightRing()
            {
            return (BMDT.value.flags & fIsRightRing) != 0;
            }
        void IsRightRing(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsRightRing;
            else
                BMDT.value.flags &= ~fIsRightRing;
            }
        bool IsLeftRing()
            {
            return (BMDT.value.flags & fIsLeftRing) != 0;
            }
        void IsLeftRing(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsLeftRing;
            else
                BMDT.value.flags &= ~fIsLeftRing;
            }
        bool IsAmulet()
            {
            return (BMDT.value.flags & fIsAmulet) != 0;
            }
        void IsAmulet(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsAmulet;
            else
                BMDT.value.flags &= ~fIsAmulet;
            }
        bool IsWeapon()
            {
            return (BMDT.value.flags & fIsWeapon) != 0;
            }
        void IsWeapon(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsWeapon;
            else
                BMDT.value.flags &= ~fIsWeapon;
            }
        bool IsBackWeapon()
            {
            return (BMDT.value.flags & fIsBackWeapon) != 0;
            }
        void IsBackWeapon(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsBackWeapon;
            else
                BMDT.value.flags &= ~fIsBackWeapon;
            }
        bool IsSideWeapon()
            {
            return (BMDT.value.flags & fIsSideWeapon) != 0;
            }
        void IsSideWeapon(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsSideWeapon;
            else
                BMDT.value.flags &= ~fIsSideWeapon;
            }
        bool IsQuiver()
            {
            return (BMDT.value.flags & fIsQuiver) != 0;
            }
        void IsQuiver(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsQuiver;
            else
                BMDT.value.flags &= ~fIsQuiver;
            }
        bool IsShield()
            {
            return (BMDT.value.flags & fIsShield) != 0;
            }
        void IsShield(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsShield;
            else
                BMDT.value.flags &= ~fIsShield;
            }
        bool IsTorch()
            {
            return (BMDT.value.flags & fIsTorch) != 0;
            }
        void IsTorch(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsTorch;
            else
                BMDT.value.flags &= ~fIsTorch;
            }
        bool IsTail()
            {
            return (BMDT.value.flags & fIsTail) != 0;
            }
        void IsTail(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsTail;
            else
                BMDT.value.flags &= ~fIsTail;
            }
        bool IsHideRings()
            {
            return (BMDT.value.flags & fIsHideRings) != 0;
            }
        void IsHideRings(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsHideRings;
            else
                BMDT.value.flags &= ~fIsHideRings;
            }
        bool IsHideAmulets()
            {
            return (BMDT.value.flags & fIsHideAmulets) != 0;
            }
        void IsHideAmulets(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsHideAmulets;
            else
                BMDT.value.flags &= ~fIsHideAmulets;
            }
        bool IsNonPlayable()
            {
            return (BMDT.value.flags & fIsNonPlayable) != 0;
            }
        void IsNonPlayable(bool value)
            {
            if(value)
                BMDT.value.flags |= fIsNonPlayable;
            else
                BMDT.value.flags &= ~fIsNonPlayable;
            }
        bool IsFlagMask(unsigned int Mask, bool Exact=false)
            {
            if(Exact)
                return (BMDT.value.flags & Mask) == Mask;
            else
                return (BMDT.value.flags & Mask) != 0;
            }
        void SetFlagMask(unsigned int Mask)
            {
            BMDT.value.flags = Mask;
            }
    };
