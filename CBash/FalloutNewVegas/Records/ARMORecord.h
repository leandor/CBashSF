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
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class ARMORecord : public Record //Armor
    {
    private:
        

        struct GENBMDT
            {
            UINT32  bipedFlags; //Type
            UINT8   generalFlags; //Flags

            GENBMDT();
            ~GENBMDT();

            bool operator ==(const GENBMDT &other) const;
            bool operator !=(const GENBMDT &other) const;
            };

        enum bmdtBipedFlags
            {
            fIsHead        = 0x00000001,
            fIsHair        = 0x00000002,
            fIsUpperBody   = 0x00000004,
            fIsLeftHand    = 0x00000008,
            fIsRightHand   = 0x00000010,
            fIsWeapon      = 0x00000020,
            fIsPipBoy      = 0x00000040,
            fIsBackpack    = 0x00000080,
            fIsNecklace    = 0x00000100,
            fIsHeadband    = 0x00000200,
            fIsHat         = 0x00000400,
            fIsEyeGlasses  = 0x00000800,
            fIsNoseRing    = 0x00001000,
            fIsEarrings    = 0x00002000,
            fIsMask        = 0x00004000,
            fIsChoker      = 0x00008000,
            fIsMouthObject = 0x00010000,
            fIsBodyAddon1  = 0x00020000,
            fIsBodyAddon2  = 0x00040000,
            fIsBodyAddon3  = 0x00080000
            };

        enum bmdtGeneralFlags
            {
            fIsUnknown1    = 0x0001,
            fIsUnknown2    = 0x0002,
            fIsHasBackpack = 0x0004,
            fIsMedium      = 0x0008,
            fIsUnknown3    = 0x0010,
            fIsPowerArmor  = 0x0020,
            fIsNonPlayable = 0x0040,
            fIsHeavy       = 0x0080
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<GENFID> SCRI; //Script
        OptSubRecord<GENFID> EITM; //Object Effect
        OptSubRecord<GENBMDT> BMDT; //Biped Data
        OptSubRecord<GENMODEL> MODL; //Model Filename
        OptSubRecord<GENMOD2> MOD2; //Model Filename
        StringRecord ICON; //Male icon filename
        StringRecord MICO; //Male mico filename
        OptSubRecord<GENMOD3> MOD3; //Model Filename
        OptSubRecord<GENMOD4> MOD4; //Model Filename
        StringRecord ICO2; //Female icon filename
        StringRecord MIC2; //Female mico filename
        StringRecord BMCT; //Ragdoll Constraint Template
        OptSubRecord<GENFID> REPL; //Repair List
        OptSubRecord<GENFID> BIPL; //Biped Model List
        OptSubRecord<GENS32> ETYP; //Equipment Type
        OptSubRecord<GENFID> YNAM; //Sound - Pick Up
        OptSubRecord<GENFID> ZNAM; //Sound - Drop
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct
        OptSubRecord<GENDNAM> DNAM; //DNAM ,, Struct
        OptSubRecord<GENU32> BNAM; //Overrides Animation Sounds
        OptSubRecord<GENSNAM> SNAM; //SNAM ,, Struct
        OptSubRecord<GENFID> TNAM; //Anmation Sounds Template

        ARMORecord(unsigned char *_recData=NULL);
        ARMORecord(ARMORecord *srcRecord);
        ~ARMORecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetSize(bool forceCalc=false);
        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(_FileHandler &SaveHandler);

        bool operator ==(const ARMORecord &other) const;
        bool operator !=(const ARMORecord &other) const;
    };
}