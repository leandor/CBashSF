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
class INFORecord : public Record //Dialog response
    {
    private:
        struct INFODATA
            {
            UINT8   dialType; //Type
            UINT8   nextSpeaker; //Next Speaker
            UINT8   flags1;
            UINT8   flags2;

            INFODATA();
            ~INFODATA();

            bool operator ==(const INFODATA &other) const;
            bool operator !=(const INFODATA &other) const;
            };

        struct INFOTRDT //Response Data
            {
            UINT32  emotionType; //Emotion Type
            SINT32  emotionValue; //Emotion Value
            UINT8   unused1[4], responseNum, unused2[3]; //Unused, Response Number, Unused
            FORMID  sound; //Sound
            UINT8   flags, unused3[3]; //Flags, Unused

            INFOTRDT();
            ~INFOTRDT();

            bool operator ==(const INFOTRDT &other) const;
            bool operator !=(const INFOTRDT &other) const;
            };

        struct INFOResponse
            {
            ReqSubRecord<INFOTRDT> TRDT; //Response Data
            StringRecord NAM1; //Response Text
            StringRecord NAM2; //Script Notes
            StringRecord NAM3; //Edits
            OptSubRecord<GENFID> SNAM; //Speaker Animation
            OptSubRecord<GENFID> LNAM; //Listener Animation

            enum eEmotionType
                {
                eNeutral  = 0,
                eAnger    = 1,
                eDisgust  = 2,
                eFear     = 3,
                eSad      = 4,
                eHappy    = 5,
                eSurprise = 6,
                ePained   = 7
                };

            enum flagsFlags
                {
                fIsUseEmotionAnim = 0x00000001
                };

            bool   IsNeutral();
            void   IsNeutral(bool value);
            bool   IsAnger();
            void   IsAnger(bool value);
            bool   IsDisgust();
            void   IsDisgust(bool value);
            bool   IsFear();
            void   IsFear(bool value);
            bool   IsSad();
            void   IsSad(bool value);
            bool   IsHappy();
            void   IsHappy(bool value);
            bool   IsSurprise();
            void   IsSurprise(bool value);
            bool   IsPained();
            void   IsPained(bool value);
            bool   IsType(UINT32 Type);
            void   SetType(UINT32 Type);

            bool   IsUseEmotionAnim();
            void   IsUseEmotionAnim(bool value);
            bool   IsFlagMask(UINT8 Mask, bool Exact=false);
            void   SetFlagMask(UINT8 Mask);

            bool operator ==(const INFOResponse &other) const;
            bool operator !=(const INFOResponse &other) const;
            };

        enum eDialogType
            {
            eTopic        = 0,
            eConversation = 1,
            eCombat       = 2,
            ePersuasion   = 3,
            eDetection    = 4,
            eService      = 5,
            eMisc         = 6,
            eRadio        = 7
            };

        enum eSpeakerType
            {
            eTarget = 0,
            eSelf   = 1,
            eEither = 2
            };

        enum flags1Flags
            {
            fIsGoodbye         = 0x00000001,
            fIsRandom          = 0x00000002,
            fIsSayOnce         = 0x00000004,
            fIsRunImmediately  = 0x00000008,
            fIsInfoRefusal     = 0x00000010,
            fIsRandomEnd       = 0x00000020,
            fIsRunForRumors    = 0x00000040,
            fIsSpeechChallenge = 0x00000080
            };

        enum flags2Flags
            {
            fIsSayOnceADay  = 0x00000001,
            fIsAlwaysDarken = 0x00000002
            };

        enum eChallengeLevelType
            {
            eNone = 0,
            eVeryEasy,
            eEasy,
            eAverage,
            eHard,
            eVeryHard
            };
    public:
        OptSubRecord<INFODATA> DATA; //INFO Data
        OptSubRecord<GENFID> QSTI; //Quest
        OptSubRecord<GENFID> TPIC; //Topic
        OptSubRecord<GENFID> PNAM; //Previous INFO
        std::vector<FORMID> NAME; //Topics
        std::vector<INFOResponse *> Responses; //Responses
        std::vector<ReqSubRecord<FNVCTDA> *> CTDA; //Conditions

        std::vector<FORMID> TCLT; //Choices
        std::vector<FORMID> TCLF; //Link From
        std::vector<FORMID> TCFU; //Unknown
        OptSubRecord<GENMINSCRIPT> Script;
        OptSubRecord<GENMINSCRIPT> NextScript;

        OptSubRecord<GENFID> SNDD; //Unused
        StringRecord RNAM; //Prompt
        OptSubRecord<GENFID> ANAM; //Speaker
        OptSubRecord<GENFID> KNAM; //ActorValue/Perk
        OptSubRecord<GENU32> DNAM; //Speech Challenge

        INFORecord(unsigned char *_recData=NULL);
        INFORecord(INFORecord *srcRecord);
        ~INFORecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsGoodbye();
        void   IsGoodbye(bool value);
        bool   IsRandom();
        void   IsRandom(bool value);
        bool   IsSayOnce();
        void   IsSayOnce(bool value);
        bool   IsRunImmediately();
        void   IsRunImmediately(bool value);
        bool   IsInfoRefusal();
        void   IsInfoRefusal(bool value);
        bool   IsRandomEnd();
        void   IsRandomEnd(bool value);
        bool   IsRunForRumors();
        void   IsRunForRumors(bool value);
        bool   IsSpeechChallenge();
        void   IsSpeechChallenge(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsSayOnceADay();
        void   IsSayOnceADay(bool value);
        bool   IsAlwaysDarken();
        void   IsAlwaysDarken(bool value);
        bool   IsExtraFlagMask(UINT8 Mask, bool Exact=false);
        void   SetExtraFlagMask(UINT8 Mask);

        bool   IsTopic();
        void   IsTopic(bool value);
        bool   IsConversation();
        void   IsConversation(bool value);
        bool   IsCombat();
        void   IsCombat(bool value);
        bool   IsPersuasion();
        void   IsPersuasion(bool value);
        bool   IsDetection();
        void   IsDetection(bool value);
        bool   IsService();
        void   IsService(bool value);
        bool   IsMisc();
        void   IsMisc(bool value);
        bool   IsRadio();
        void   IsRadio(bool value);
        bool   IsDialogType(UINT16 Type, bool Exact=false);
        void   SetDialogType(UINT16 Type);

        bool   IsTarget();
        void   IsTarget(bool value);
        bool   IsSelf();
        void   IsSelf(bool value);
        bool   IsEither();
        void   IsEither(bool value);
        bool   IsSpeakerType(UINT8 Type, bool Exact=false);
        void   SetSpeakerType(UINT8 Type);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsVeryEasy();
        void   IsVeryEasy(bool value);
        bool   IsEasy();
        void   IsEasy(bool value);
        bool   IsAverage();
        void   IsAverage(bool value);
        bool   IsHard();
        void   IsHard(bool value);
        bool   IsVeryHard();
        void   IsVeryHard(bool value);
        bool   IsDifficultyType(UINT8 Type, bool Exact=false);
        void   SetDifficultyType(UINT8 Type);

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

        bool operator ==(const INFORecord &other) const;
        bool operator !=(const INFORecord &other) const;
    };
}