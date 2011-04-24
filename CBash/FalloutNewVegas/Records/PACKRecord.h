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
class PACKRecord : public Record //Package
    {
    private:
        struct PACKPKDT //General
            {
            UINT32  flags; // General Flags
            UINT8   aiType, unused1; // Type, Unused
            UINT16  behaviorFlags; // Fallout Behavior Flags
            UINT16  specificFlags; // Type Specific Flags
            UINT8   unused2[2]; // Unused

            PACKPKDT();
            ~PACKPKDT();

            bool operator ==(const PACKPKDT &other) const;
            bool operator !=(const PACKPKDT &other) const;
            };

        struct PACKPLDT
            {
            SINT32  locType;
            FORMID_OR_UINT32  locId;
            SINT32  locRadius;

            PACKPLDT();
            ~PACKPLDT();

            bool operator ==(const PACKPLDT &other) const;
            bool operator !=(const PACKPLDT &other) const;
            };

        struct PACKPSDT // Schedule
            {
            SINT8   month, day;
            UINT8   date;
            SINT8   time;
            SINT32  duration;

            PACKPSDT();
            ~PACKPSDT();

            bool operator ==(const PACKPSDT &other) const;
            bool operator !=(const PACKPSDT &other) const;
            };

        struct PACKPTDT // Target
            {
            SINT32  targetType; // Type
            FORMID_OR_UINT32 targetId; // Reference
            SINT32  targetCountOrDistance; // Count / Distance
            FLOAT32 unknown; // Unknown

            PACKPTDT();
            ~PACKPTDT();

            bool operator ==(const PACKPTDT &other) const;
            bool operator !=(const PACKPTDT &other) const;
            };

        struct PACKIDLC // Idle Animation Count
            {
            UINT8   targetType, unused[3]; // Animation Count, Unused

            PACKIDLC();
            ~PACKIDLC();

            bool operator ==(const PACKIDLC &other) const;
            bool operator !=(const PACKIDLC &other) const;
            };

        struct PACKPKPT // Patrol Flags
            {
            UINT8   repeatableTypes, unused; // Repeatable, Unused

            PACKPKPT();
            ~PACKPKPT();

            bool operator ==(const PACKPKPT &other) const;
            bool operator !=(const PACKPKPT &other) const;
            };

        struct PACKPKW3 // Use Weapon Data
            {
            UINT32  flags; // Flags
            UINT8   fireRate, fireType; // Fire Rate, Fire Count
            UINT16  burstNum, minShots, maxShots; // Number of Bursts, Shoots Per Volleys (Min, Max)
            FLOAT32 minPause, maxPause; // Pause Between Volleys (Min, Max)
            UINT8   unused[4]; // Unused

            PACKPKW3();
            ~PACKPKW3();

            bool operator ==(const PACKPKW3 &other) const;
            bool operator !=(const PACKPKW3 &other) const;
            };

        struct PACKPKDD // Dialogue Data
            {
            FLOAT32 FOV; // FOV
            FORMID  topic; // Topic
            UINT32  flags; // Flags
            UINT8   unused1[4];
            UINT32  dialType;
            UINT8   unknown[4];

            PACKPKDD();
            ~PACKPKDD();

            bool operator ==(const PACKPKDD &other) const;
            bool operator !=(const PACKPKDD &other) const;
            };

        struct PACKSCRI // Script
            {
            ReqSubRecord<GENFID> INAM; // Idle
            ReqSubRecord<FNVSCHR> SCHR;
            RawRecord SCDA;
            NonNullStringRecord SCTX;
            std::vector<GENVARS *> VARS;
            std::vector<ReqSubRecord<GENSCR_> *> SCR_;
            ReqSubRecord<GENFID> TNAM; // Topic

            bool IsScriptEnabled();
            void IsScriptEnabled(bool value);
            bool IsScriptFlagMask(UINT16 Mask, bool Exact=false);
            void SetScriptFlagMask(UINT16 Mask);

            bool   operator ==(const PACKSCRI &other) const;
            bool   operator !=(const PACKSCRI &other) const;
            };

        enum specificFindEscortEatItemFlags
            {
            fIsAllowBuying   = 0x00000100,
            fIsAllowKilling  = 0x00000200,
            fIsAllowStealing = 0x00000400
            };

        enum specificWanderFlags
            {
            fIsNoEating       = 0x00000001,
            fIsNoSleeping     = 0x00000002,
            fIsNoConversation = 0x00000004,
            fIsNoIdleMarkers  = 0x00000008,
            fIsNoFurniture    = 0x00000010,
            fIsNoWandering    = 0x00000020
            };

        enum specificItemFlags
            {
            fIsSitDown = 0x00000002
            };

        enum specificAmbushFlags
            {
            fIsHide = 0x00000001
            };

        enum specificSandboxFlags
            {
            fIsNoEating       = 0x00000001,
            fIsNoSleeping     = 0x00000002,
            fIsNoConversation = 0x00000004,
            fIsNoIdleMarkers  = 0x00000008,
            fIsNoFurniture    = 0x00000010,
            fIsNoWandering    = 0x00000020
            };

        enum specificGuardFlags
            {
            fIsRemainNearReference = 0x00000004
            };

        enum idleFlags
            {
            fIsRunInSequence = 0x00000001,
            fIsDoOnce        = 0x00000004
            };

        enum pkptTypes
            {
            eIsNotRepeatable = 0,
            eIsRepeatable
            };

        enum weaponFlags
            {
            fIsAlwaysHit           = 0x00000001,
            fIsDoNoDamage          = 0x00000100,
            fIsCrouchToReload      = 0x00010000,
            fIsHoldFireWhenBlocked = 0x01000000
            };

        enum weaponRateTypes
            {
            eAutoFire = 0,
            eVolleyFire
            };

        enum weaponFireTypes
            {
            eNumberOfBursts = 0,
            eRepeatFire
            };

        enum dialogueFlags
            {
            fIsNoHeadtracking            = 0x00000001,
            fIsDontControlTargetMovement = 0x00000100
            };

        enum dialogueTypes
            {
            eConversation = 0,
            eSayTo
            };


    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<PACKPKDT> PKDT; //General
        OptSubRecord<PACKPLDT> PLDT; //Location 1
        OptSubRecord<PACKPLDT> PLD2; //Location 2
        OptSubRecord<PACKPSDT> PSDT; //Schedule
        OptSubRecord<PACKPTDT> PTDT; //Target 1
        std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions
        OptSimpleSubRecord<UINT8> IDLF; //Idle Animation Flags
        OptSubRecord<PACKIDLC> IDLC; //Idle Animation Count
        OptSimpleSubRecord<FLOAT32> IDLT; //Idle Timer Setting
        std::vector<FORMID> IDLA; //Animations
        RawRecord IDLB; //Unused
        //OptSubRecord<GENPKED> PKED; //Eat Marker (Empty)
        OptSimpleSubRecord<UINT32> PKE2; //Escort Distance
        OptSimpleSubRecord<FORMID> CNAM; //Combat Style
        OptSimpleSubRecord<FLOAT32> PKFD; //Follow - Start Location - Trigger Radius
        OptSubRecord<PACKPKPT> PKPT; //Patrol Flags
        OptSubRecord<PACKPKW3> PKW3; //Use Weapon Data
        OptSubRecord<PACKPTDT> PTD2; //Target 2
        //OptSubRecord<GENPUID> PUID; //Use Item Marker (Empty)
        //OptSubRecord<GENPKAM> PKAM; //Ambush Marker (Empty)
        OptSubRecord<PACKPKDD> PKDD; //PKDD ,, Struct
        OptSubRecord<PACKPLDT> PLD2b; //Target 2 (again??)
        OptSubRecord<PACKSCRI> POBA; //OnBegin
        OptSubRecord<PACKSCRI> POEA; //OnEnd
        OptSubRecord<PACKSCRI> POCA; //OnChange

        PACKRecord(unsigned char *_recData=NULL);
        PACKRecord(PACKRecord *srcRecord);
        ~PACKRecord();

        bool   VisitFormIDs(FormIDOp &op);

        //Do flags manually

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

        bool operator ==(const PACKRecord &other) const;
        bool operator !=(const PACKRecord &other) const;
    };
}