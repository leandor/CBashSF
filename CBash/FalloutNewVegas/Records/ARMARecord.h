/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is CBash code.
 *
 * The Initial Developer of the Original Code is
 * Waruddar.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class ARMARecord : public FNVRecord //Armor Addon
    {
    private:
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

        enum eEquipTypes
            {
            eNone    = -1,
            eBigGuns = 0,
            eEnergyWeapons,
            eSmallGuns,
            eMeleeWeapons,
            eUnarmedWeapon,
            eThrownWeapons,
            eMine,
            eBodyWear,
            eHeadWear,
            eHandWear,
            eChems,
            eStimpack,
            eEdible,
            eAlcohol
            };
    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<GENBMDT> BMDT; //Biped Data
        OptSubRecord<FNVBIPEDMODEL> MODL; //Male Biped Model
        OptSubRecord<FNVWORLDMODEL> MOD2; //Male World Model
        StringRecord ICON; //Male icon filename
        StringRecord MICO; //Male mico filename
        OptSubRecord<FNVBIPEDMODEL> MOD3; //Female Biped Model
        OptSubRecord<FNVWORLDMODEL> MOD4; //Female World Model
        StringRecord ICO2; //Female icon filename
        StringRecord MIC2; //Female mico filename
        OptSimpleSubRecord<SINT32> ETYP; //Equipment Type
        OptSubRecord<FNVEQUIPDATA> DATA; //Equipment Data
        OptSubRecord<FNVEQUIPDNAM> DNAM; //Extra Equipment Data

        ARMARecord(unsigned char *_recData=NULL);
        ARMARecord(ARMARecord *srcRecord);
        ~ARMARecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHead();
        void   IsHead(bool value);
        bool   IsHair();
        void   IsHair(bool value);
        bool   IsUpperBody();
        void   IsUpperBody(bool value);
        bool   IsLeftHand();
        void   IsLeftHand(bool value);
        bool   IsRightHand();
        void   IsRightHand(bool value);
        bool   IsWeapon();
        void   IsWeapon(bool value);
        bool   IsPipBoy();
        void   IsPipBoy(bool value);
        bool   IsBackpack();
        void   IsBackpack(bool value);
        bool   IsNecklace();
        void   IsNecklace(bool value);
        bool   IsHeadband();
        void   IsHeadband(bool value);
        bool   IsHat();
        void   IsHat(bool value);
        bool   IsEyeGlasses();
        void   IsEyeGlasses(bool value);
        bool   IsNoseRing();
        void   IsNoseRing(bool value);
        bool   IsEarrings();
        void   IsEarrings(bool value);
        bool   IsMask();
        void   IsMask(bool value);
        bool   IsChoker();
        void   IsChoker(bool value);
        bool   IsMouthObject();
        void   IsMouthObject(bool value);
        bool   IsBodyAddon1();
        void   IsBodyAddon1(bool value);
        bool   IsBodyAddon2();
        void   IsBodyAddon2(bool value);
        bool   IsBodyAddon3();
        void   IsBodyAddon3(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsUnknown1();
        void   IsUnknown1(bool value);
        bool   IsUnknown2();
        void   IsUnknown2(bool value);
        bool   IsHasBackpack();
        void   IsHasBackpack(bool value);
        bool   IsMedium();
        void   IsMedium(bool value);
        bool   IsUnknown3();
        void   IsUnknown3(bool value);
        bool   IsPowerArmor();
        void   IsPowerArmor(bool value);
        bool   IsNonPlayable();
        void   IsNonPlayable(bool value);
        bool   IsHeavy();
        void   IsHeavy(bool value);
        bool   IsExtraFlagMask(UINT8 Mask, bool Exact=false);
        void   SetExtraFlagMask(UINT8 Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsBigGuns();
        void   IsBigGuns(bool value);
        bool   IsEnergyWeapons();
        void   IsEnergyWeapons(bool value);
        bool   IsSmallGuns();
        void   IsSmallGuns(bool value);
        bool   IsMeleeWeapons();
        void   IsMeleeWeapons(bool value);
        bool   IsUnarmedWeapon();
        void   IsUnarmedWeapon(bool value);
        bool   IsThrownWeapons();
        void   IsThrownWeapons(bool value);
        bool   IsMine();
        void   IsMine(bool value);
        bool   IsBodyWear();
        void   IsBodyWear(bool value);
        bool   IsHeadWear();
        void   IsHeadWear(bool value);
        bool   IsHandWear();
        void   IsHandWear(bool value);
        bool   IsChems();
        void   IsChems(bool value);
        bool   IsStimpack();
        void   IsStimpack(bool value);
        bool   IsEdible();
        void   IsEdible(bool value);
        bool   IsAlcohol();
        void   IsAlcohol(bool value);
        bool   IsEquipmentType(SINT32 Type);
        void   SetEquipmentType(SINT32 Type);

        bool   IsModulatesVoice();
        void   IsModulatesVoice(bool value);
        bool   IsDNAMFlagMask(UINT16 Mask, bool Exact=false);
        void   SetDNAMFlagMask(UINT16 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const ARMARecord &other) const;
        bool operator !=(const ARMARecord &other) const;
        bool equals(Record *other);
    };
}