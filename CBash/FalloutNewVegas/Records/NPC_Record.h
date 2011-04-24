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
class NPC_Record : public Record //Non-Player Character
    {
    private:
        struct NPC_DATA // Data
            {
            SINT32  baseHealth; // Base Health
            UINT8   strength, perception, endurance,
                    charisma, intelligence,
                    agility, luck;
            //UINT8 unused1; // only present in old record versions

            NPC_DATA();
            ~NPC_DATA();

            bool operator ==(const NPC_DATA &other) const;
            bool operator !=(const NPC_DATA &other) const;
            };

        struct NPC_DNAM // Skill Data
            {
            UINT8   barter, bigGuns, energy, explosives, 
                    lockpick, medicine, melee, repair, 
                    science, guns, sneak, speech, 
                    survival, unarmed; // Big Guns is obsolete for FNV
            UINT8   barterBoost, bigGunsBoost, energyBoost, explosivesBoost, 
                    lockpickBoost, medicineBoost, meleeBoost, repairBoost, 
                    scienceBoost, gunsBoost, sneakBoost, speechBoost, 
                    survivalBoost, unarmedBoost; // Big Guns is obsolete for FNV

            NPC_DNAM();
            ~NPC_DNAM();

            bool operator ==(const NPC_DNAM &other) const;
            bool operator !=(const NPC_DNAM &other) const;
            };

        enum flagsFlags
            {
            fIsFemale           = 0x00000001,
            fIsEssential       = 0x00000002,
            fIsCharGenFacePreset = 0x00000004,
            fIsRespawn         = 0x00000008,
            fIsAutoCalcStats          = 0x00000010,
            //fIsFlies           = 0x00000020, // CREA only?
            //fIsWalks           = 0x00000040, // CREA only?
            fIsPCLevelOffset   = 0x00000080,
            fIsUseTemplate        = 0x00000100,
            fIsNoLowLevel      = 0x00000200,
            fIsNoBloodSpray    = 0x00000800,
            fIsNoBloodDecal    = 0x00001000,
            //fIsSummonable    = 0x00004000, //OBSE
            //fIsNoHead          = 0x00008000, // CREA only?
            //fIsNoRightArm      = 0x00010000, // CREA only?
            //fIsNoLeftArm       = 0x00020000, // CREA only?
            //fIsNoCombatInWater = 0x00040000, // CREA only?
            //fIsNoShadow        = 0x00080000, // CREA only?
            fIsNoVATSMelee     = 0x00100000,
            //fIsAllowPCDialogue = 0x00200000, // CREA only?
            fIsCanBeAllRaces  = 0x00400000,
            fIsAutoCalcService        = 0x00800000,
            //fIsTiltFrontBack   = 0x01000000, // CREA only?
            //fIsTiltLeftRight   = 0x02000000, // CREA only?
            fIsNoKnockdowns    = 0x03000000, //3?
            fIsNotPushable     = 0x08000000,
            //fIsAllowPickpocket = 0x10000000, // CREA only?
            //fIsGhost           = 0x20000000, // CREA only?
            fIsNoHeadTracking  = 0x40000000
            //fIsInvulnerable    = 0x80000000 // CREA only?
            };

        enum templateFlags
            {
            fIsUseTraits     = 0x00000001,
            fIsUseStats      = 0x00000002,
            fIsUseFactions   = 0x00000004
            fIsUseAEList     = 0x00000008,
            fIsUseAIData     = 0x00000010,
            fIsUseAIPackages = 0x00000020,
            fIsUseModelAnim  = 0x00000040,
            fIsUseBaseData   = 0x00000080,
            fIsUseInventory  = 0x00000100,
            fIsUseScript     = 0x00000200
            };

        enum aggressionTypes
            {
            eUnaggressive = 0,
            eAggressive,
            eVeryAggressive,
            eFrenzied
            };

        enum confidenceTypes
            {
            eCowardly = 0,
            eCautious,
            eAverage,
            eBrave,
            eFoolhardy
            };

        enum moodTypes
            {
            eNeutral = 0,
            eAfraid,
            eAnnoyed,
            eCocky,
            eDrugged,
            ePleasant,
            eAngry,
            eSad
            };

        enum assistanceTypes
            {
            eHelpsNobody = 0,
            eHelpsAllies,
            eHelpsFriendsAndAllies
            };

        enum aggroFlags
            {
            fIsAggroRadiusBehavior = 0x01
            };

        enum impactTypes
            {
            eStone = 0,
            eDirt,
            eGrass,
            eGlass,
            eMetal,
            eWood,
            eOrganic,
            eCloth,
            eWater,
            eHollowMetal,
            eOrganicBug,
            eOrganicGlow
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<FNVACBS> ACBS; //Configuration
        std::vector<ReqSubRecord<GENSNAM> *> SNAM; //Factions
        OptSimpleSubRecord<FORMID> INAM; //Death item
        OptSimpleSubRecord<FORMID> VTCK; //Voice
        OptSimpleSubRecord<FORMID> TPLT; //Template
        OptSimpleSubRecord<FORMID> RNAM; //Race
        std::vector<FORMID> SPLO; //Actor Effects
        OptSimpleSubRecord<FORMID> EITM; //Unarmed Attack Effect
        OptSimpleSubRecord<UINT16> EAMT; //Unarmed Attack Animation
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSimpleSubRecord<FORMID> SCRI; //Script
        std::vector<FNVCNTO *> CNTO;  //Items
        OptSubRecord<FNVAIDT> AIDT; //AI Data
        std::vector<FORMID> PKID; //Packages
        OptSimpleSubRecord<FORMID> CNAM; //Class
        OptSubRecord<NPC_DATA> DATA; //Data
        OptSubRecord<NPC_DNAM> DNAM; //Skill Data
        std::vector<FORMID> PNAM; //Head Parts
        OptSimpleSubRecord<FORMID> HNAM; //Hair
        OptSimpleSubRecord<FLOAT32> LNAM; //Hair length
        OptSimpleSubRecord<FORMID> ENAM; //Eyes
        OptSubRecord<GENCLR> HCLR; //Hair Color
        OptSimpleSubRecord<FORMID> ZNAM; //Combat Style
        OptSimpleSubRecord<UINT32> NAM4; //Impact Material Type
        RawRecord FGGS; //FaceGen Geometry-Symmetric
        RawRecord FGGA; //FaceGen Geometry-Asymmetric
        RawRecord FGTS; //FaceGen Texture-Symmetric
        OptSimpleSubRecord<UINT16> NAM5; //Unknown
        OptSimpleSubRecord<FLOAT32> NAM6; //Height
        OptSimpleSubRecord<FLOAT32> NAM7; //Weight

        NPC_Record(unsigned char *_recData=NULL);
        NPC_Record(NPC_Record *srcRecord);
        ~NPC_Record();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsFemale();
        void   IsFemale(bool value);
        bool   IsEssential();
        void   IsEssential(bool value);
        bool   IsCharGenFacePreset();
        void   IsCharGenFacePreset(bool value);
        bool   IsRespawn();
        void   IsRespawn(bool value);
        bool   IsAutoCalcStats();
        void   IsAutoCalcStats(bool value);
        bool   IsPCLevelOffset();
        void   IsPCLevelOffset(bool value);
        bool   IsUseTemplate();
        void   IsUseTemplate(bool value);
        bool   IsNoLowLevel();
        void   IsNoLowLevel(bool value);
        bool   IsNoBloodSpray();
        void   IsNoBloodSpray(bool value);
        bool   IsNoBloodDecal();
        void   IsNoBloodDecal(bool value);
        bool   IsNoVATSMelee();
        void   IsNoVATSMelee(bool value);
        bool   IsCanBeAllRaces();
        void   IsCanBeAllRaces(bool value);
        bool   IsAutoCalcService();
        void   IsAutoCalcService(bool value);
        bool   IsNoKnockdowns();
        void   IsNoKnockdowns(bool value);
        bool   IsNotPushable();
        void   IsNotPushable(bool value);
        bool   IsNoHeadTracking();
        void   IsNoHeadTracking(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsUseTraits();
        void   IsUseTraits(bool value);
        bool   IsUseStats();
        void   IsUseStats(bool value);
        bool   IsUseFactions();
        void   IsUseFactions(bool value);
        bool   IsUseAEList();
        void   IsUseAEList(bool value);
        bool   IsUseAIData();
        void   IsUseAIData(bool value);
        bool   IsUseAIPackages();
        void   IsUseAIPackages(bool value);
        bool   IsUseModelAnim();
        void   IsUseModelAnim(bool value);
        bool   IsUseBaseData();
        void   IsUseBaseData(bool value);
        bool   IsUseInventory();
        void   IsUseInventory(bool value);
        bool   IsUseScript();
        void   IsUseScript(bool value);
        bool   IsTemplateFlagMask(UINT8 Mask, bool Exact=false);
        void   SetTemplateFlagMask(UINT8 Mask);

        bool   IsAggroRadiusBehavior();
        void   IsAggroRadiusBehavior(bool value);
        bool   IsAggroFlagMask(UINT8 Mask, bool Exact=false);
        void   SetAggroFlagMask(UINT8 Mask);

        bool   IsUnaggressive();
        void   IsUnaggressive(bool value);
        bool   IsAggressive();
        void   IsAggressive(bool value);
        bool   IsVeryAggressive();
        void   IsVeryAggressive(bool value);
        bool   IsFrenzied();
        void   IsFrenzied(bool value);
        bool   IsAggressionType(UINT8 Type, bool Exact=false);
        void   SetAggressionType(UINT8 Type);

        bool   IsCowardly();
        void   IsCowardly(bool value);
        bool   IsCautious();
        void   IsCautious(bool value);
        bool   IsAverage();
        void   IsAverage(bool value);
        bool   IsBrave();
        void   IsBrave(bool value);
        bool   IsFoolhardy();
        void   IsFoolhardy(bool value);
        bool   IsConfidenceType(UINT8 Type, bool Exact=false);
        void   SetConfidenceType(UINT8 Type);

        bool   IsNeutral();
        void   IsNeutral(bool value);
        bool   IsAfraid();
        void   IsAfraid(bool value);
        bool   IsAnnoyed();
        void   IsAnnoyed(bool value);
        bool   IsCocky();
        void   IsCocky(bool value);
        bool   IsDrugged();
        void   IsDrugged(bool value);
        bool   IsPleasant();
        void   IsPleasant(bool value);
        bool   IsAngry();
        void   IsAngry(bool value);
        bool   IsSad();
        void   IsSad(bool value);
        bool   IsMoodType(UINT8 Type, bool Exact=false);
        void   SetMoodType(UINT8 Type);

        bool   IsHelpsNobody();
        void   IsHelpsNobody(bool value);
        bool   IsHelpsAllies();
        void   IsHelpsAllies(bool value);
        bool   IsHelpsFriendsAndAllies();
        void   IsHelpsFriendsAndAllies(bool value);
        bool   IsAssistanceType(UINT8 Type, bool Exact=false);
        void   SetAssistanceType(UINT8 Type);

        bool   IsStone();
        void   IsStone(bool value);
        bool   IsDirt();
        void   IsDirt(bool value);
        bool   IsGrass();
        void   IsGrass(bool value);
        bool   IsGlass();
        void   IsGlass(bool value);
        bool   IsMetal();
        void   IsMetal(bool value);
        bool   IsWood();
        void   IsWood(bool value);
        bool   IsOrganic();
        void   IsOrganic(bool value);
        bool   IsCloth();
        void   IsCloth(bool value);
        bool   IsWater();
        void   IsWater(bool value);
        bool   IsHollowMetal();
        void   IsHollowMetal(bool value);
        bool   IsOrganicBug();
        void   IsOrganicBug(bool value);
        bool   IsOrganicGlow();
        void   IsOrganicGlow(bool value);
        bool   IsImpactType(UINT8 Type, bool Exact=false);
        void   SetImpactType(UINT8 Type);

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

        bool operator ==(const NPC_Record &other) const;
        bool operator !=(const NPC_Record &other) const;
    };
}