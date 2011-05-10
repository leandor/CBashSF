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
class REFRRecord : public FNVRecord //Placed Object
    {
    private:
        enum xprmTypes
            {
            eNone = 0,
            eBox,
            eSphere,
            ePortalBox
            };

        enum xtriTypes
            {
            eUnidentified = 0,
            eStatic,
            eAnimStatic,
            eTransparent,
            eClutter,
            eWeapon,
            eProjectile,
            eSpell,
            eBiped,
            eTrees,
            eProps,
            eWater,
            eTrigger,
            eTerrain,
            eTrap,
            eNonCollidable,
            eCloudTrap,
            eGround,
            ePortal,
            eDebrisSmall,
            eDebrisLarge,
            eAcousticSpace,
            eActorZone,
            eProjectileZone,
            eGasTrap,
            eShellCasing,
            eTransparentSmall,
            eInvisibleWall,
            eTransparentSmallAnim,
            eDeadBip,
            eCharController,
            eAvoidBox,
            eCollisionBox,
            eCameraSphere,
            eDoorDetection,
            eCameraPick,
            eItemPick,
            eLineOfSight,
            ePathPick,
            eCustomPick1,
            eCustomPick2,
            eSpellExplosion,
            eDroppingPick
            };

        enum xtelFlags
            {
            fIsNoAlarm = 0x00000001
            };

        enum fnamFlags
            {
            fIsVisible     = 0x00000001,
            fIsCanTravelTo = 0x00000002
            };

        enum markerTypeTypes
            {
            eMarkerNone = 0,
            eCity,
            eSettlement,
            eEncampment,
            eNaturalLandmark,
            eCave,
            eFactory,
            eMonument,
            eMilitary,
            eOffice,
            eTownRuins,
            eUrbanRuins,
            eSewerRuins,
            eMetro,
            eVault
            };

        enum xrdoTypes
            {
            eRadius = 0,
            eEverywhere,
            eWorldAndLinkedInteriors,
            eLinkedInteriors,
            eCurrentCellOnly
            };

        enum xpwrTypes
            {
            eReflection = 0,
            eRefraction
            };

        enum xactFlags
            {
            fIsUseDefault    = 0x00000001,
            fIsActivate      = 0x00000002,
            fIsOpen          = 0x00000004,
            fIsOpenByDefault = 0x00000008
            };

        enum xespFlags
            {
            fIsOppositeParent = 0x00000001,
            fIsPopIn          = 0x00000002
            };
    public:
        StringRecord EDID; //Editor ID
        RawRecord RCLR; //Unused Linked Reference Color (Old Format?)
        OptSimpleSubRecord<FORMID> NAME; //Base
        OptSimpleSubRecord<FORMID> XEZN; //Encounter Zone
        RawRecord XRGD; //Ragdoll Data
        RawRecord XRGB; //Ragdoll Biped Data
        OptSubRecord<GENXPRM> XPRM; //Primitive
        OptSimpleSubRecord<UINT32> XTRI; //Collision Layer
        //OptSubRecord<GENXMBP> XMBP; //MultiBound Primitive Marker (Empty)
        OptSubRecord<GENXMBO> XMBO; //BoundHalfExtents
        OptSubRecord<GENXTEL> XTEL; //Teleport Destination
        OptSubRecord<GENXMRK> XMRK; //Map Data
        OptSubRecord<GENMMRK> MMRK; //Audio Data
        RawRecord XSRF; //Unknown
        RawRecord XSRD; //Unknown
        OptSimpleSubRecord<FORMID> XTRG; //Target
        OptSimpleSubRecord<SINT32> XLCM; //Level Modifier
        OptSubRecord<GENPATROL> Patrol; //Patrol Data
        OptSubRecord<GENXRDO> XRDO; //Radio Data
        OptSubRecord<FNVXOWN> Ownership; //Owner
        OptSubRecord<FNVXLOC> XLOC; //Lock Data
        OptSimpleSubRecord<SINT32> XCNT; //Count
        OptSimpleFloatSubRecord<flt_0> XRDS; //Radius
        OptSimpleFloatSubRecord<flt_0> XHLP; //Health
        OptSimpleFloatSubRecord<flt_0> XRAD; //Radiation
        OptSimpleFloatSubRecord<flt_0> XCHG; //Charge
        OptSubRecord<GENAMMO> Ammo; //Ammo
        std::vector<ReqSubRecord<GENXPWR> *> Reflections; //Reflected/Refracted By
        std::vector<FORMID> XLTW; //Lit Water
        std::vector<ReqSubRecord<GENXDCR> *> Decals; //Linked Decals
        OptSimpleSubRecord<FORMID> XLKR; //Linked Reference
        OptSubRecord<GENXCLP> XCLP; //Linked Reference Color
        OptSubRecord<GENACTPARENT> ActivateParents; //Activate Parents
        StringRecord XATO; //Activation Prompt
        OptSubRecord<GENXESP> XESP; //Enable Parent
        OptSimpleSubRecord<FORMID> XEMI; //Emittance
        OptSimpleSubRecord<FORMID> XMBR; //MultiBound Reference
        OptSimpleSubRecord<UINT32> XACT; //Action Flag
        //OptSubRecord<GENONAM> ONAM; //Open by Default (Empty)
        //OptSubRecord<GENXIBS> XIBS; //Ignored By Sandbox (Empty)
        OptSubRecord<GENXNDP> XNDP; //Navigation Door Link
        std::vector<FORMID> XPOD; //Portal Data
        OptSubRecord<GENPOSITION> XPTL; //Portal Data
        OptSimpleSubRecord<UINT8> XSED; //SpeedTree Seed
        OptSubRecord<GENROOM> Room; //Room Data
        OptSubRecord<GENPOSITION> XOCP; //Occlusion Plane Data
        std::vector<FORMID> XORD; //Linked Occlusion Planes (4 only?)
        OptSubRecord<GENXLOD> XLOD; //Distant LOD Data
        OptSimpleFloatSubRecord<flt_1> XSCL; //Scale
        OptSubRecord<GENPOSDATA> DATA; //Position/Rotation

        REFRRecord(unsigned char *_recData=NULL);
        REFRRecord(REFRRecord *srcRecord);
        ~REFRRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNoAlarm();
        void   IsNoAlarm(bool value);
        bool   Is0FlagMask(UINT8 Mask, bool Exact=false);
        void   Set0FlagMask(UINT8 Mask);

        bool   IsVisible();
        void   IsVisible(bool value);
        bool   IsCanTravelTo();
        void   IsCanTravelTo(bool value);
        bool   Is1FlagMask(UINT8 Mask, bool Exact=false);
        void   Set1FlagMask(UINT8 Mask);

        bool   IsUseDefault();
        void   IsUseDefault(bool value);
        bool   IsActivate();
        void   IsActivate(bool value);
        bool   IsOpen();
        void   IsOpen(bool value);
        bool   IsOpenByDefault();
        void   IsOpenByDefault(bool value);
        bool   Is3FlagMask(UINT8 Mask, bool Exact=false);
        void   Set3FlagMask(UINT8 Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsBox();
        void   IsBox(bool value);
        bool   IsSphere();
        void   IsSphere(bool value);
        bool   IsPortalBox();
        void   IsPortalBox(bool value);
        bool   Is0Type(UINT8 Type);
        void   Set0Type(UINT8 Type);

        bool   IsUnidentified();
        void   IsUnidentified(bool value);
        bool   IsStatic();
        void   IsStatic(bool value);
        bool   IsAnimStatic();
        void   IsAnimStatic(bool value);
        bool   IsTransparent();
        void   IsTransparent(bool value);
        bool   IsClutter();
        void   IsClutter(bool value);
        bool   IsWeapon();
        void   IsWeapon(bool value);
        bool   IsProjectile();
        void   IsProjectile(bool value);
        bool   IsSpell();
        void   IsSpell(bool value);
        bool   IsBiped();
        void   IsBiped(bool value);
        bool   IsTrees();
        void   IsTrees(bool value);
        bool   IsProps();
        void   IsProps(bool value);
        bool   IsWater();
        void   IsWater(bool value);
        bool   IsTrigger();
        void   IsTrigger(bool value);
        bool   IsTerrain();
        void   IsTerrain(bool value);
        bool   IsTrap();
        void   IsTrap(bool value);
        bool   IsNonCollidable();
        void   IsNonCollidable(bool value);
        bool   IsCloudTrap();
        void   IsCloudTrap(bool value);
        bool   IsGround();
        void   IsGround(bool value);
        bool   IsPortal();
        void   IsPortal(bool value);
        bool   IsDebrisSmall();
        void   IsDebrisSmall(bool value);
        bool   IsDebrisLarge();
        void   IsDebrisLarge(bool value);
        bool   IsAcousticSpace();
        void   IsAcousticSpace(bool value);
        bool   IsActorZone();
        void   IsActorZone(bool value);
        bool   IsProjectileZone();
        void   IsProjectileZone(bool value);
        bool   IsGasTrap();
        void   IsGasTrap(bool value);
        bool   IsShellCasing();
        void   IsShellCasing(bool value);
        bool   IsTransparentSmall();
        void   IsTransparentSmall(bool value);
        bool   IsInvisibleWall();
        void   IsInvisibleWall(bool value);
        bool   IsTransparentSmallAnim();
        void   IsTransparentSmallAnim(bool value);
        bool   IsDeadBip();
        void   IsDeadBip(bool value);
        bool   IsCharController();
        void   IsCharController(bool value);
        bool   IsAvoidBox();
        void   IsAvoidBox(bool value);
        bool   IsCollisionBox();
        void   IsCollisionBox(bool value);
        bool   IsCameraSphere();
        void   IsCameraSphere(bool value);
        bool   IsDoorDetection();
        void   IsDoorDetection(bool value);
        bool   IsCameraPick();
        void   IsCameraPick(bool value);
        bool   IsItemPick();
        void   IsItemPick(bool value);
        bool   IsLineOfSight();
        void   IsLineOfSight(bool value);
        bool   IsPathPick();
        void   IsPathPick(bool value);
        bool   IsCustomPick1();
        void   IsCustomPick1(bool value);
        bool   IsCustomPick2();
        void   IsCustomPick2(bool value);
        bool   IsSpellExplosion();
        void   IsSpellExplosion(bool value);
        bool   IsDroppingPick();
        void   IsDroppingPick(bool value);
        bool   Is1Type(UINT8 Type);
        void   Set1Type(UINT8 Type);

        bool   IsMarkerNone();
        void   IsMarkerNone(bool value);
        bool   IsCity();
        void   IsCity(bool value);
        bool   IsSettlement();
        void   IsSettlement(bool value);
        bool   IsEncampment();
        void   IsEncampment(bool value);
        bool   IsNaturalLandmark();
        void   IsNaturalLandmark(bool value);
        bool   IsCave();
        void   IsCave(bool value);
        bool   IsFactory();
        void   IsFactory(bool value);
        bool   IsMonument();
        void   IsMonument(bool value);
        bool   IsMilitary();
        void   IsMilitary(bool value);
        bool   IsOffice();
        void   IsOffice(bool value);
        bool   IsTownRuins();
        void   IsTownRuins(bool value);
        bool   IsUrbanRuins();
        void   IsUrbanRuins(bool value);
        bool   IsSewerRuins();
        void   IsSewerRuins(bool value);
        bool   IsMetro();
        void   IsMetro(bool value);
        bool   IsVault();
        void   IsVault(bool value);
        bool   Is2Type(UINT8 Type);
        void   Set2Type(UINT8 Type);

        bool   IsRadius();
        void   IsRadius(bool value);
        bool   IsEverywhere();
        void   IsEverywhere(bool value);
        bool   IsWorldAndLinkedInteriors();
        void   IsWorldAndLinkedInteriors(bool value);
        bool   IsLinkedInteriors();
        void   IsLinkedInteriors(bool value);
        bool   IsCurrentCellOnly();
        void   IsCurrentCellOnly(bool value);
        bool   Is3Type(UINT8 Type);
        void   Set3Type(UINT8 Type);

        bool   IsReflection();
        void   IsReflection(bool value);
        bool   IsRefraction();
        void   IsRefraction(bool value);
        bool   Is4Type(UINT8 Type);
        void   Set4Type(UINT8 Type);

        bool   IsOppositeParent();
        void   IsOppositeParent(bool value);
        bool   IsPopIn();
        void   IsPopIn(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const REFRRecord &other) const;
        bool operator !=(const REFRRecord &other) const;
    };
}