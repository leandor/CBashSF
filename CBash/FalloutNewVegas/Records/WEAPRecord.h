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
class WEAPRecord : public Record //Weapon
    {
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<GENICON> ICON; //Large Icon Filename
        OptSubRecord<GENFID> SCRI; //Script
        OptSubRecord<GENFID> EITM; //Object Effect
        OptSubRecord<GENS16> EAMT; //Enchantment Charge Amount
        OptSubRecord<GENFID> NAM0; //Ammo
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSubRecord<GENFID> REPL; //Repair List
        OptSubRecord<GENS32> ETYP; //Equipment Type
        OptSubRecord<GENFID> BIPL; //Biped Model List
        OptSubRecord<GENFID> YNAM; //Sound - Pick Up
        OptSubRecord<GENFID> ZNAM; //Sound - Drop
        OptSubRecord<GENMOD2> MOD2; //Model Filename
        OptSubRecord<GENMOD3> MOD3; //Model Filename
        OptSubRecord<GENFID> EFSD; //Scope Effect
        OptSubRecord<GENMOD4> MOD4; //Model Filename
        StringRecord VANM; //VATS Attack Name
        StringRecord NNAM; //Embedded Weapon Node
        OptSubRecord<GENMWD1> MWD1; //Mod 1
        OptSubRecord<GENFID> INAM; //Impact DataSet
        OptSubRecord<GENFID> WNAM; //1st Person Model
        OptSubRecord<GENWNM1> WNM1; //Mod 1
        OptSubRecord<GENWMI1> WMI1; //Mod 1
        OptSubRecord<GENFID> SNAM; //Sound - Gun - Shoot Dist
        OptSubRecord<GENFID> XNAM; //Sound - Gun - Shoot 2D
        OptSubRecord<GENFID> NAM7; //Sound - Gun - Shoot 3D Looping
        OptSubRecord<GENFID> TNAM; //Sound - Melee - Swing / Gun - No Ammo
        OptSubRecord<GENFID> NAM6; //Sound - Block
        OptSubRecord<GENFID> UNAM; //Sound - Idle
        OptSubRecord<GENFID> NAM9; //Sound - Equip
        OptSubRecord<GENFID> NAM8; //Sound - Unequip
        OptSubRecord<GENFID> WMS1; //Sound - Mod 1 - Shoot Dist
        OptSubRecord<GENFID> WMS2; //Sound - Mod 1 - Shoot 2D
        OptSubRecord<GENDATA> DATA; //DATA ,, Struct
        OptSubRecord<GENDNAM> DNAM; //DNAM ,, Struct
        OptSubRecord<GENCRDT> CRDT; //CRDT ,, Struct
        OptSubRecord<GENVATS> VATS; //VATS ,, Struct
        OptSubRecord<GENU32> VNAM; //Sound Level

        WEAPRecord(unsigned char *_recData=NULL);
        WEAPRecord(WEAPRecord *srcRecord);
        ~WEAPRecord();

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

        bool operator ==(const WEAPRecord &other) const;
        bool operator !=(const WEAPRecord &other) const;
    };
}